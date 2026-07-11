#include "fw_gc.h"
#include "test_harness.h"
#include <stddef.h>
#include <string.h>

/* A dummy descriptor; contents don't matter for packing. */
static const FWTypeDescriptor g_dummy = { .name = "dummy", .kind = FW_KIND_BLOB };

static void test_shared_descriptors(void) {
  /* fw_blob_desc: a plain byte buffer with no interior pointers. */
  CHECK(fw_blob_desc.kind == FW_KIND_BLOB);

  /* fw_dyn_desc: boxed { i32 tag; i64 value } with value at offset 8 (the
     int64 aligns past 4 bytes of padding). Three pointer-meaning tags. */
  CHECK(fw_dyn_desc.kind == FW_KIND_TAGGED);
  CHECK(fw_dyn_desc.value_offset == 8);
  CHECK(fw_dyn_desc.num_ptr_tags == 3);
  CHECK(fw_dyn_desc.ptr_tags[1] == 9);   /* OBJECT */
}

static void test_word_packing(void) {
  uintptr_t w = fw_word_pack(&g_dummy);
  CHECK(fw_word_desc(w) == &g_dummy);   /* descriptor recovered */
  CHECK(fw_word_marked(w) == 0);        /* starts unmarked */

  w = fw_word_set_mark(w);
  CHECK(fw_word_marked(w) == 1);
  CHECK(fw_word_desc(w) == &g_dummy);   /* mark did not corrupt descriptor */

  w = fw_word_clear_mark(w);
  CHECK(fw_word_marked(w) == 0);
  CHECK(fw_word_desc(w) == &g_dummy);
}

static const FWTypeDescriptor g_blob = { .name = "blob", .kind = FW_KIND_BLOB };

static void test_alloc_basics(void) {
  fw_gc_init();
  fw_gc_set_stress(0);

  char *p = (char *)fw_gc_alloc(32, &g_blob);
  CHECK(p != NULL);
  for (int i = 0; i < 32; i++) CHECK(p[i] == 0);   /* zeroed */

  FWGCStats s = fw_gc_stats();
  CHECK(s.live_objects == 1);
  CHECK(s.live_bytes == 32);
  CHECK(s.total_allocs == 1);

  /* pointer is 8-aligned so header math and packing stay valid */
  CHECK(((uintptr_t)p & 0x7) == 0);
}

static void test_roots_registration(void) {
  fw_gc_init();
  void *a = fw_gc_alloc(8, &g_blob);
  void *b = fw_gc_alloc(8, &g_blob);

  fw_gc_add_root(&a);
  fw_gc_add_root(&b);
  fw_gc_remove_root(&a);
  /* No crash, and shadow stack starts empty. */
  CHECK(fw_gc_shadow_top == NULL);
  (void)b;
}

/* A node with two pointer fields at offsets 0 and 8. */
typedef struct { void *a; void *b; } Node;
static const uint32_t g_node_offsets[2] = { 0, 8 };
static const FWTypeDescriptor g_node_desc = {
  .name = "Node", .kind = FW_KIND_PLAIN,
  .num_ptrs = 2, .ptr_offsets = g_node_offsets
};

static void test_collect_plain(void) {
  fw_gc_init();

  /* Build: root -> n1 -> n2 ; and an unrooted garbage blob. */
  Node *n1 = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  Node *n2 = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  n1->a = n2;                 /* n1 points at n2 */
  (void)fw_gc_alloc(16, &g_blob);   /* garbage: nothing references it */

  void *root = n1;
  fw_gc_add_root(&root);

  CHECK(fw_gc_stats().live_objects == 3);
  fw_gc_collect();
  /* n1 and n2 reachable, blob collected */
  CHECK(fw_gc_stats().live_objects == 2);
  CHECK(fw_gc_stats().total_frees == 1);

  /* Drop the root; everything becomes garbage. */
  fw_gc_remove_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);
}

/* Mirror of the runtime DynamicValue: { i32 tag; i64 value }.
   Tag values match DynamicValueHandler.h: INT64=2, STRING=5. */
typedef struct { int32_t tag; int64_t value; } DynVal;
#define TAG_INT64  2
#define TAG_STRING 5
#define TAG_OBJECT 9
static const int32_t g_ptr_tags[2] = { TAG_STRING, TAG_OBJECT };
static const FWTypeDescriptor g_dyn_desc = {
  .name = "dynamic", .kind = FW_KIND_TAGGED,
  .tag_offset = 0,
  .value_offset = offsetof(DynVal, value),
  .num_ptr_tags = 2, .ptr_tags = g_ptr_tags
};

static void test_tagged_scanning(void) {
  fw_gc_init();

  /* d1 boxes a heap string pointer -> the string must survive. */
  DynVal *d1 = (DynVal *)fw_gc_alloc(sizeof(DynVal), &g_dyn_desc);
  char   *str = (char *)fw_gc_alloc(4, &g_blob);
  str[0]='h'; str[1]='i'; str[2]=0;
  d1->tag = TAG_STRING;
  d1->value = (int64_t)(intptr_t)str;

  /* d2 boxes a plain integer that happens to look like an address. */
  DynVal *d2 = (DynVal *)fw_gc_alloc(sizeof(DynVal), &g_dyn_desc);
  d2->tag = TAG_INT64;
  d2->value = (int64_t)(intptr_t)str;   /* same bits, but tag says NOT a pointer */

  void *r1 = d1; fw_gc_add_root(&r1);   /* only d1 is rooted */
  fw_gc_collect();

  /* Alive: d1 + str = 2. d2 is unrooted garbage and was freed;
     str is kept ONLY because d1's tag marks value as a pointer. */
  CHECK(fw_gc_stats().live_objects == 2);
  CHECK(str[0] == 'h' && str[1] == 'i');   /* not poisoned */
  (void)d2;
}

/* An ARRAY of DynVal, element scanning delegated to g_dyn_desc. */
static const FWTypeDescriptor g_dynarray_desc = {
  .name = "dyn[]", .kind = FW_KIND_ARRAY,
  .elem_desc = &g_dyn_desc, .elem_size = sizeof(DynVal)
};

static void test_array_scanning(void) {
  fw_gc_init();

  /* Backing buffer of 3 dynamic values, each boxing a heap string. */
  DynVal *buf = (DynVal *)fw_gc_alloc_array(&g_dynarray_desc, 3);
  for (int i = 0; i < 3; i++) {
    char *s = (char *)fw_gc_alloc(2, &g_blob);
    s[0] = 'a' + i; s[1] = 0;
    buf[i].tag = TAG_STRING;
    buf[i].value = (int64_t)(intptr_t)s;
  }

  void *root = buf; fw_gc_add_root(&root);
  fw_gc_collect();

  /* Alive: the array + 3 strings = 4. All strings reachable only via the array. */
  CHECK(fw_gc_stats().live_objects == 4);
  CHECK(((char *)(intptr_t)buf[0].value)[0] == 'a');
  CHECK(((char *)(intptr_t)buf[2].value)[0] == 'c');
}

static void test_shadow_stack_roots(void) {
  fw_gc_init();

  void *keep = fw_gc_alloc(8, &g_blob);   /* reachable only via a shadow frame */
  (void)fw_gc_alloc(8, &g_blob);          /* garbage */

  /* Simulate main() -> foo(): two nested frames. foo holds `keep`. */
  void *foo_slots[1] = { keep };
  FWFrame foo_frame = { .prev = NULL, .n = 1, .roots = foo_slots };

  void *main_slots[0];
  FWFrame main_frame = { .prev = NULL, .n = 0, .roots = main_slots };

  fw_gc_shadow_top = &main_frame;          /* push main */
  foo_frame.prev = fw_gc_shadow_top;
  fw_gc_shadow_top = &foo_frame;           /* push foo */

  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);  /* keep survived, garbage freed */

  fw_gc_shadow_top = foo_frame.prev;       /* pop foo */
  fw_gc_shadow_top = main_frame.prev;      /* pop main -> NULL */
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);  /* now everything is garbage */
}

static int g_finalized = 0;
static void my_finalizer(void *obj) { (void)obj; g_finalized++; }

static void test_finalizers(void) {
  fw_gc_init();
  g_finalized = 0;

  void *res = fw_gc_alloc(8, &g_blob);
  fw_gc_register_finalizer(res, my_finalizer);
  /* not rooted -> collected -> finalizer must run exactly once */
  fw_gc_collect();
  CHECK(g_finalized == 1);
  CHECK(fw_gc_stats().live_objects == 0);
}

static void test_cycle_is_collected(void) {
  fw_gc_init();
  Node *x = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  Node *y = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  x->a = y; y->a = x;                 /* cycle, but unrooted */
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);   /* cycles ARE collected (mark-sweep) */
}

static void test_deep_chain_no_overflow(void) {
  fw_gc_init();
  Node *head = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  void *root = head; fw_gc_add_root(&root);   /* root BEFORE building: mid-build
                                                 threshold collections must not
                                                 free the chain we're growing */
  Node *cur = head;
  for (int i = 0; i < 1000000; i++) {       /* 1M-deep chain */
    Node *n = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
    cur->a = n; cur = n;
  }
  fw_gc_collect();                          /* must NOT stack-overflow */
  CHECK(fw_gc_stats().live_objects == 1000001);
}

static void test_stress_survives(void) {
  fw_gc_init();
  fw_gc_set_stress(1);                       /* collect on EVERY alloc */
  Node *n1 = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  void *root = n1; fw_gc_add_root(&root);
  /* Under stress, each alloc triggers a full collect; n1 must survive
     because it is rooted. Allocate a chain hanging off n1. */
  Node *cur = n1;
  for (int i = 0; i < 100; i++) {
    Node *n = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
    cur->a = n; cur = n;
  }
  fw_gc_set_stress(0);
  CHECK(fw_gc_stats().live_objects == 101);  /* n1 + 100, nothing lost */
}

/* --- Conservative C-stack scanning ------------------------------------ */

/* Allocate a blob, hold it only in a plain (non-root-registered) local, and
   collect. The conservative scanner must find the pointer on this frame's
   stack (or in a callee-saved register) and keep the object alive. Marked
   noinline so the frame really exists; `volatile` reads stop the compiler
   dropping the local before the collect. */
__attribute__((noinline)) static void conservative_keep_helper(void) {
  void *p = fw_gc_alloc(32, &fw_blob_desc);
  volatile void *sink = p;          /* force `p` to stay materialized */
  fw_gc_collect();
  CHECK(fw_gc_stats().total_frees == 0);   /* object survived via stack root */
  (void)sink;
  ((volatile char *)p)[0] = 1;      /* touch after collect: still valid */
}

static void test_conservative_stack_root(void) {
  fw_gc_init();
  int anchor = 0;
  fw_gc_set_stack_base(&anchor);    /* high end of the stack for this test */
  conservative_keep_helper();
  fw_gc_set_stack_base(NULL);       /* disable so later tests are unaffected */
}

/* Like above, but the only live reference is an INTERIOR pointer (p + 8).
   fw_gc_object_containing must accept interior pointers. */
__attribute__((noinline)) static void conservative_interior_helper(void) {
  char *p = (char *)fw_gc_alloc(32, &fw_blob_desc);
  volatile char *interior = p + 8;  /* keep only a mid-object pointer */
  fw_gc_collect();
  CHECK(fw_gc_stats().total_frees == 0);   /* interior pointer kept it alive */
  interior[0] = 2;                  /* still valid memory */
  (void)interior;
}

static void test_conservative_interior_pointer(void) {
  fw_gc_init();
  int anchor = 0;
  fw_gc_set_stack_base(&anchor);
  conservative_interior_helper();
  fw_gc_set_stack_base(NULL);
}

/* Allocate an object in a callee frame and let the only reference die with
   that frame. Because the pointer never returns to the caller, it is not a
   live local once this returns. Kept noinline so the frame (and its spill
   slots) are real and separate from the caller. */
__attribute__((noinline)) static void alloc_and_drop(void) {
  void *garbage = fw_gc_alloc(16, &fw_blob_desc);
  volatile void *sink = garbage;   /* force it live only within THIS frame */
  (void)sink;
}

/* Overwrite the stack region just vacated by alloc_and_drop with non-pointer
   values, so any stale copy of the dropped pointer left in a spill slot is
   genuinely gone — mimicking how real generated code reuses that space. */
__attribute__((noinline)) static void scrub_stack(void) {
  volatile uintptr_t buf[64];
  for (int i = 0; i < 64; i++) buf[i] = (uintptr_t)(0xA5A50000u + i);
  uintptr_t acc = 0;
  for (int i = 0; i < 64; i++) acc += buf[i];
  CHECK(acc != 0);                 /* keep buf alive; not a pointer pattern */
}

/* An unrelated non-pointer int local must neither crash the scan nor corrupt
   the local, and a genuinely-unreachable object (no live copy of its address
   anywhere on the stack) must be freed. */
static void test_conservative_negative(void) {
  fw_gc_init();
  int anchor = 0;
  volatile int junk = 0x12345678;   /* arbitrary non-pointer bit pattern */
  fw_gc_set_stack_base(&anchor);

  alloc_and_drop();                 /* object becomes unreachable */
  scrub_stack();                    /* erase any stale pointer bits */
  fw_gc_collect();

  CHECK((int)junk == 0x12345678);   /* scan did not corrupt the local */
  CHECK(fw_gc_stats().total_frees == 1);   /* unreachable object WAS freed */

  fw_gc_set_stack_base(NULL);
}

int main(void) {
  RUN_TEST(test_shared_descriptors);
  RUN_TEST(test_word_packing);
  RUN_TEST(test_alloc_basics);
  RUN_TEST(test_roots_registration);
  RUN_TEST(test_collect_plain);
  RUN_TEST(test_tagged_scanning);
  RUN_TEST(test_array_scanning);
  RUN_TEST(test_shadow_stack_roots);
  RUN_TEST(test_finalizers);
  RUN_TEST(test_cycle_is_collected);
  RUN_TEST(test_deep_chain_no_overflow);
  RUN_TEST(test_stress_survives);
  RUN_TEST(test_conservative_stack_root);
  RUN_TEST(test_conservative_interior_pointer);
  RUN_TEST(test_conservative_negative);
  return TEST_SUMMARY();
}
