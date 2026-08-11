#include "fw_gc.h"
#include "fw_gc_container.h"
#include "test_harness.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* setenv/unsetenv are POSIX; the MSVC CRT ships neither, so the Windows AOT
   build failed to link test_gc with two unresolved externals. _putenv_s is the
   MSVC equivalent, and passing an empty value there deletes the variable —
   which is exactly what unsetenv does. The overwrite flag is dropped because
   _putenv_s always overwrites, and every call site here passes 1. */
#ifdef _WIN32
#define setenv(name, value, overwrite) _putenv_s((name), (value))
#define unsetenv(name) _putenv_s((name), "")
#endif

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

  /* Slot-address model: roots[i] holds &local; GC reads *roots[i]. */
  void *foo_slots[1] = { (void *)&keep };
  FWFrame foo_frame = { .prev = NULL, .n = 1, .roots = foo_slots };

  void *main_slots[1];
  FWFrame main_frame = { .prev = NULL, .n = 0, .roots = main_slots };

  fw_gc_shadow_top = &main_frame;          /* push main */
  foo_frame.prev = fw_gc_shadow_top;
  fw_gc_shadow_top = &foo_frame;           /* push foo */

  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);  /* keep survived, garbage freed */

  /* Reassign the rooted local; the frame slot is unchanged (slot-address),
     so the GC must see the NEW object and free the old one. */
  keep = fw_gc_alloc(8, &g_blob);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);  /* only the new object survives */

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

static void test_stress_env_toggle(void) {
  setenv("FW_GC_STRESS", "1", 1);
  fw_gc_init();                      /* should pick up the env and enable stress */
  size_t before = fw_gc_stats().total_frees;
  void *a = fw_gc_alloc(8, &g_blob); /* unrooted */
  (void)a;
  void *b = fw_gc_alloc(8, &g_blob); /* under stress, this alloc forces a collect
                                        that frees the unrooted `a` */
  (void)b;
  CHECK(fw_gc_stats().total_frees > before);
  unsetenv("FW_GC_STRESS");
  fw_gc_init();                      /* reset stress off for later tests */
}

/* ==========================================================================
   Root bookkeeping
   ========================================================================== */

/* fw_gc_remove_root swap-removes: the LAST root is moved into the removed
   slot. If that move were wrong, the moved root would stop protecting its
   object — a silent use-after-free. Remove from the MIDDLE so the swap is
   actually exercised. */
static void test_remove_root_swap_keeps_others(void) {
  fw_gc_init();
  char *a = (char *)fw_gc_alloc(8, &g_blob); a[0] = 'A';
  char *b = (char *)fw_gc_alloc(8, &g_blob); b[0] = 'B';
  char *c = (char *)fw_gc_alloc(8, &g_blob); c[0] = 'C';

  void *ra = a, *rb = b, *rc = c;
  fw_gc_add_root(&ra);
  fw_gc_add_root(&rb);
  fw_gc_add_root(&rc);

  fw_gc_remove_root(&rb);          /* middle slot: `rc` gets swapped into it */
  rb = NULL;                       /* b is now unreachable */
  fw_gc_collect();

  CHECK(fw_gc_stats().live_objects == 2);   /* a and c survive */
  CHECK(fw_gc_stats().total_frees == 1);
  CHECK(a[0] == 'A');                       /* the swapped-over root still works */
  CHECK(c[0] == 'C');                       /* the swapped-IN root still works */
}

/* Removing a slot that was never registered must be a no-op, not a corruption
   of the root array (e.g. shrinking the length and dropping a real root). */
static void test_remove_root_unknown_slot_is_noop(void) {
  fw_gc_init();
  char *a = (char *)fw_gc_alloc(8, &g_blob); a[0] = 'A';
  void *ra = a; fw_gc_add_root(&ra);

  void *never_registered = NULL;
  fw_gc_remove_root(&never_registered);

  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);
  CHECK(a[0] == 'A');
}

/* The global root array starts at capacity 8 and doubles. Register more than
   that so the realloc path runs and verify every root still protects. */
static void test_global_roots_grow_beyond_initial_capacity(void) {
  fw_gc_init();
  enum { N = 40 };
  static void *slots[N];
  for (int i = 0; i < N; i++) {
    char *p = (char *)fw_gc_alloc(8, &g_blob);
    p[0] = (char)('a' + (i % 26));
    slots[i] = p;
    fw_gc_add_root(&slots[i]);
  }
  (void)fw_gc_alloc(8, &g_blob);            /* one unrooted object */
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == N);
  for (int i = 0; i < N; i++)
    CHECK(((char *)slots[i])[0] == (char)('a' + (i % 26)));
}

/* Global roots use the same slot-address model as shadow frames: reassigning
   the rooted variable must make the GC see the NEW object and free the old. */
static void test_global_root_slot_reassignment(void) {
  fw_gc_init();
  void *slot = fw_gc_alloc(8, &g_blob);
  fw_gc_add_root(&slot);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);

  slot = fw_gc_alloc(8, &g_blob);           /* old object now unreachable */
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);
  CHECK(fw_gc_stats().total_frees == 1);
}

/* A root slot holding NULL is legal (an uninitialised local) and must not
   crash or be treated as an object. */
static void test_null_root_slot(void) {
  fw_gc_init();
  void *empty = NULL;
  fw_gc_add_root(&empty);
  void *live = fw_gc_alloc(8, &g_blob);
  fw_gc_add_root(&live);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);
}

/* ==========================================================================
   Pointer resolution: interior, non-heap, one-past-the-end
   ========================================================================== */

/* An interior pointer (`&buf[32]`, e.g. `&arr[i]` in generated code) must keep
   the WHOLE containing object alive. A one-past-the-end pointer belongs to no
   object and must not. */
static void test_interior_pointer_keeps_object_alive(void) {
  fw_gc_init();
  char *buf = (char *)fw_gc_alloc(64, &g_blob);
  buf[0] = 'X'; buf[63] = 'Z';

  void *mid = buf + 32;
  fw_gc_add_root(&mid);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);
  CHECK(buf[0] == 'X' && buf[63] == 'Z');   /* not poisoned */

  /* Last byte still resolves. */
  fw_gc_remove_root(&mid);
  void *last = buf + 63;
  fw_gc_add_root(&last);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);

  /* One past the end resolves to no object -> collected. */
  fw_gc_remove_root(&last);
  void *end = buf + 64;
  fw_gc_add_root(&end);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);
}

static const char g_static_text[] = "not-a-heap-object";

/* Roots and object fields may legitimately hold non-heap pointers: a static
   string constant, a stack address, or an unaligned junk value. Marking must
   skip them rather than read a garbage header. */
static void test_non_heap_pointers_are_skipped(void) {
  fw_gc_init();
  int on_stack = 7;
  void *r_static = (void *)g_static_text;
  void *r_stack  = (void *)&on_stack;
  void *r_junk   = (void *)(uintptr_t)0x1;
  fw_gc_add_root(&r_static);
  fw_gc_add_root(&r_stack);
  fw_gc_add_root(&r_junk);

  /* A PLAIN object whose pointer fields also point outside the heap. */
  Node *n = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  n->a = (void *)g_static_text;
  n->b = (void *)&on_stack;
  void *root = n; fw_gc_add_root(&root);

  fw_gc_collect();                          /* must not crash */
  CHECK(fw_gc_stats().live_objects == 1);   /* only the Node itself */
  CHECK(on_stack == 7);
}

/* ==========================================================================
   Precision: the collector must NOT treat arbitrary bytes as pointers
   ========================================================================== */

/* A BLOB payload holding the bit pattern of a live object address must NOT
   keep that object alive — that is exactly the difference between the precise
   collector and the deleted conservative scanner. */
static void test_blob_bytes_are_not_scanned(void) {
  fw_gc_init();
  void  *victim = fw_gc_alloc(8, &g_blob);
  void **hidden = (void **)fw_gc_alloc(sizeof(void *), &g_blob);
  *hidden = victim;                         /* a real pointer, in a BLOB */

  void *root = hidden; fw_gc_add_root(&root);
  fw_gc_collect();

  CHECK(fw_gc_stats().live_objects == 1);   /* only `hidden` */
  CHECK(fw_gc_stats().total_frees == 1);    /* `victim` was collected */
}

/* Mirror of the same rule for TAGGED: a non-pointer tag whose value word holds
   a real heap address must not keep it alive. */
static void test_tagged_non_pointer_tag_does_not_retain(void) {
  fw_gc_init();
  DynVal *d = (DynVal *)fw_gc_alloc(sizeof(DynVal), &g_dyn_desc);
  void   *target = fw_gc_alloc(8, &g_blob);
  d->tag = TAG_INT64;                       /* NOT in ptr_tags */
  d->value = (int64_t)(intptr_t)target;

  void *root = d; fw_gc_add_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);   /* d only; target freed */
}

/* ==========================================================================
   Descriptor shapes: nested arrays, mixed tags, degenerate element size
   ========================================================================== */

/* ARRAY whose elements are PLAIN structs with pointer fields. */
typedef struct { void *p; int64_t pad; } Cell;
static const uint32_t g_cell_offsets[1] = { 0 };
static const FWTypeDescriptor g_cell_desc = {
  .name = "Cell", .kind = FW_KIND_PLAIN,
  .num_ptrs = 1, .ptr_offsets = g_cell_offsets
};
static const FWTypeDescriptor g_cellarr_desc = {
  .name = "Cell[]", .kind = FW_KIND_ARRAY,
  .elem_desc = &g_cell_desc, .elem_size = sizeof(Cell)
};

static void test_array_of_plain_structs(void) {
  fw_gc_init();
  Cell *cells = (Cell *)fw_gc_alloc_array(&g_cellarr_desc, 4);
  CHECK(fw_gc_stats().live_bytes == 4 * sizeof(Cell));
  for (int i = 0; i < 4; i++) {
    char *s = (char *)fw_gc_alloc(2, &g_blob);
    s[0] = (char)('a' + i);
    cells[i].p = s;
  }
  void *root = cells; fw_gc_add_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 5);   /* array + 4 strings */
  for (int i = 0; i < 4; i++)
    CHECK(((char *)cells[i].p)[0] == (char)('a' + i));
}

/* ARRAY of ARRAY: a 3x2 grid of Cells. Descriptor nesting (not graph depth)
   drives the recursion in scan_fields, so two levels must work. */
static const FWTypeDescriptor g_row_desc = {
  .name = "Cell[2]", .kind = FW_KIND_ARRAY,
  .elem_desc = &g_cell_desc, .elem_size = sizeof(Cell)
};
static const FWTypeDescriptor g_grid_desc = {
  .name = "Cell[2][]", .kind = FW_KIND_ARRAY,
  .elem_desc = &g_row_desc, .elem_size = 2 * sizeof(Cell)
};

static void test_nested_array_descriptor(void) {
  fw_gc_init();
  Cell *grid = (Cell *)fw_gc_alloc_array(&g_grid_desc, 3);   /* 3 rows x 2 cells */
  for (int i = 0; i < 6; i++) {
    char *s = (char *)fw_gc_alloc(2, &g_blob);
    s[0] = (char)('0' + i);
    grid[i].p = s;
  }
  void *root = grid; fw_gc_add_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 7);   /* grid + 6 leaves */
  for (int i = 0; i < 6; i++)
    CHECK(((char *)grid[i].p)[0] == (char)('0' + i));
}

/* An ARRAY of TAGGED where only SOME elements carry a pointer tag: the
   pointer-tagged ones survive, the others' look-alike values do not. */
static void test_array_of_mixed_tags(void) {
  fw_gc_init();
  DynVal *buf = (DynVal *)fw_gc_alloc_array(&g_dynarray_desc, 4);
  char *kept = (char *)fw_gc_alloc(2, &g_blob); kept[0] = 'k';
  char *dead = (char *)fw_gc_alloc(2, &g_blob); dead[0] = 'd';

  buf[0].tag = TAG_STRING; buf[0].value = (int64_t)(intptr_t)kept;
  buf[1].tag = TAG_INT64;  buf[1].value = (int64_t)(intptr_t)dead;  /* not a ptr */
  buf[2].tag = TAG_INT64;  buf[2].value = 42;
  buf[3].tag = TAG_OBJECT; buf[3].value = 0;                        /* NULL ptr */

  void *root = buf; fw_gc_add_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 2);   /* array + kept */
  CHECK(kept[0] == 'k');
}

/* A malformed ARRAY descriptor with elem_size 0 must terminate (n = 0), not
   divide by zero or loop forever. */
static const FWTypeDescriptor g_zero_elem_desc = {
  .name = "zero[]", .kind = FW_KIND_ARRAY,
  .elem_desc = &g_blob, .elem_size = 0
};

static void test_array_zero_elem_size_is_safe(void) {
  fw_gc_init();
  void *a = fw_gc_alloc(32, &g_zero_elem_desc);
  void *root = a; fw_gc_add_root(&root);
  fw_gc_collect();                          /* must return */
  CHECK(fw_gc_stats().live_objects == 1);
}

/* ==========================================================================
   Zero-sized objects
   ========================================================================== */

/* An empty container backing store (`fw_gc_alloc_array(desc, 0)`) or a
   zero-byte allocation still has a header and a distinct payload address that
   the program holds in a root. It must survive while rooted: resolving its
   payload address has to succeed even though its payload range is empty. */
static void test_zero_size_object_rooted_survives(void) {
  fw_gc_init();
  void *z = fw_gc_alloc(0, &g_blob);
  CHECK(z != NULL);
  void *root = z; fw_gc_add_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);
  CHECK(fw_gc_stats().total_frees == 0);

  fw_gc_remove_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);   /* and still collectible when dead */
}

static void test_empty_array_rooted_survives(void) {
  fw_gc_init();
  DynVal *empty = (DynVal *)fw_gc_alloc_array(&g_dynarray_desc, 0);
  CHECK(empty != NULL);
  CHECK(fw_gc_stats().live_bytes == 0);
  void *root = empty; fw_gc_add_root(&root);

  /* Another live object right next to it must not be confused with the
     zero-sized one in either direction. */
  char *neighbour = (char *)fw_gc_alloc(8, &g_blob); neighbour[0] = 'n';
  void *nroot = neighbour; fw_gc_add_root(&nroot);

  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 2);
  CHECK(neighbour[0] == 'n');
}

/* ==========================================================================
   Finalizers
   ========================================================================== */

static int   g_fin_calls = 0;
static void *g_fin_last  = NULL;
static void counting_finalizer(void *obj) { g_fin_calls++; g_fin_last = obj; }

/* A finalizer must not run while the object is reachable, must run exactly
   once when it dies, and must not run again on the next cycle (the entry is
   unregistered when it fires). */
static void test_finalizer_runs_once_when_unreachable(void) {
  fw_gc_init();
  g_fin_calls = 0; g_fin_last = NULL;

  void *obj = fw_gc_alloc(8, &g_blob);
  fw_gc_register_finalizer(obj, counting_finalizer);
  void *root = obj; fw_gc_add_root(&root);

  fw_gc_collect();
  CHECK(g_fin_calls == 0);                  /* still reachable */

  void *expected = obj;
  fw_gc_remove_root(&root);
  fw_gc_collect();
  CHECK(g_fin_calls == 1);
  CHECK(g_fin_last == expected);            /* called with the payload pointer */

  fw_gc_collect();
  CHECK(g_fin_calls == 1);                  /* not re-run */
}

/* Only the finalizers of the objects that actually die may run. */
static void test_finalizers_are_per_object(void) {
  fw_gc_init();
  g_fin_calls = 0;

  void *keep = fw_gc_alloc(8, &g_blob);
  void *die1 = fw_gc_alloc(8, &g_blob);
  void *die2 = fw_gc_alloc(8, &g_blob);
  fw_gc_register_finalizer(keep, counting_finalizer);
  fw_gc_register_finalizer(die1, counting_finalizer);
  fw_gc_register_finalizer(die2, counting_finalizer);

  void *root = keep; fw_gc_add_root(&root);
  (void)die1; (void)die2;

  fw_gc_collect();
  CHECK(g_fin_calls == 2);                  /* die1 + die2 only */
  CHECK(fw_gc_stats().live_objects == 1);
}

/* An object with no finalizer must not pick up someone else's. */
static void test_finalizer_absent_is_noop(void) {
  fw_gc_init();
  g_fin_calls = 0;
  (void)fw_gc_alloc(8, &g_blob);            /* garbage, no finalizer */
  fw_gc_collect();
  CHECK(g_fin_calls == 0);
  CHECK(fw_gc_stats().total_frees == 1);
}

/* fw_gc_init drops pending finalizers without running them (a fresh heap has
   no objects to finalize). */
static void test_init_drops_pending_finalizers(void) {
  fw_gc_init();
  g_fin_calls = 0;
  void *obj = fw_gc_alloc(8, &g_blob);
  fw_gc_register_finalizer(obj, counting_finalizer);

  fw_gc_init();                             /* re-init */
  CHECK(g_fin_calls == 0);

  void *fresh = fw_gc_alloc(8, &g_blob);
  (void)fresh;
  fw_gc_collect();
  CHECK(g_fin_calls == 0);                  /* the stale entry is gone */
}

/* ==========================================================================
   FFI containers: the descriptor `trace` hook
   ========================================================================== */

/* Stand-in for a native container (vec::Vec / map::Map): the GC-visible handle
   holds only a pointer to malloc'd storage, which the layout scan cannot walk.
   The `trace` hook marks each element. */
typedef struct { void **elems; size_t n; } NativeVec;

static int g_trace_calls = 0;
static void *g_trace_last_obj = NULL;

static void nativevec_trace(void *obj, void (*mark)(void *ptr)) {
  NativeVec *v = (NativeVec *)obj;
  g_trace_calls++;
  g_trace_last_obj = obj;
  for (size_t i = 0; i < v->n; i++)
    mark(v->elems[i]);
}

static void test_trace_hook_keeps_native_elements_alive(void) {
  fw_gc_init();
  g_trace_calls = 0;

  /* BLOB + trace: exactly what fw_make_container_desc builds. */
  static FWTypeDescriptor vec_desc;
  vec_desc = fw_make_container_desc("NativeVec", nativevec_trace);

  NativeVec *v = (NativeVec *)fw_gc_alloc(sizeof(NativeVec), &vec_desc);
  void *root = v; fw_gc_add_root(&root);
  v->elems = (void **)malloc(3 * sizeof(void *));
  v->n = 0;
  for (int i = 0; i < 3; i++) {
    char *s = (char *)fw_gc_alloc(2, &g_blob);
    s[0] = (char)('x' + i);
    v->elems[i] = s;                        /* store BEFORE the next alloc */
    v->n = (size_t)(i + 1);
  }
  (void)fw_gc_alloc(8, &g_blob);            /* unrelated garbage */

  fw_gc_collect();
  CHECK(g_trace_calls == 1);                /* hook ran once for the handle */
  CHECK(g_trace_last_obj == (void *)v);     /* called with the payload pointer */
  CHECK(fw_gc_stats().live_objects == 4);   /* handle + 3 elements */
  for (int i = 0; i < 3; i++)
    CHECK(((char *)v->elems[i])[0] == (char)('x' + i));

  /* Dropping the handle drops the elements with it. */
  fw_gc_remove_root(&root);
  free(v->elems);                           /* native storage is not GC memory */
  v->elems = NULL; v->n = 0;
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);
}

/* The hook is independent of `kind`: a PLAIN descriptor's pointer fields AND
   its trace hook must both be honoured. */
typedef struct { void *field; void **elems; size_t n; } Hybrid;
static const uint32_t g_hybrid_offsets[1] = { 0 };

static void hybrid_trace(void *obj, void (*mark)(void *ptr)) {
  Hybrid *h = (Hybrid *)obj;
  for (size_t i = 0; i < h->n; i++) mark(h->elems[i]);
}

static void test_trace_hook_runs_alongside_plain_scan(void) {
  fw_gc_init();
  static FWTypeDescriptor hybrid_desc;
  memset(&hybrid_desc, 0, sizeof(hybrid_desc));
  hybrid_desc.name = "Hybrid";
  hybrid_desc.kind = FW_KIND_PLAIN;
  hybrid_desc.num_ptrs = 1;
  hybrid_desc.ptr_offsets = g_hybrid_offsets;
  hybrid_desc.trace = hybrid_trace;

  Hybrid *h = (Hybrid *)fw_gc_alloc(sizeof(Hybrid), &hybrid_desc);
  void *root = h; fw_gc_add_root(&root);
  h->elems = (void **)malloc(2 * sizeof(void *));
  h->n = 0;

  char *by_field = (char *)fw_gc_alloc(2, &g_blob); by_field[0] = 'f';
  h->field = by_field;
  for (int i = 0; i < 2; i++) {
    char *s = (char *)fw_gc_alloc(2, &g_blob);
    s[0] = (char)('0' + i);
    h->elems[i] = s;
    h->n = (size_t)(i + 1);
  }

  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 4);   /* handle + field + 2 traced */
  CHECK(((char *)h->field)[0] == 'f');
  CHECK(((char *)h->elems[0])[0] == '0');
  CHECK(((char *)h->elems[1])[0] == '1');
  free(h->elems);
}

/* Traced elements must survive under maximal collection pressure — the shape
   of a Vec being filled inside a loop in generated code. */
static void test_trace_hook_under_stress(void) {
  fw_gc_init();
  static FWTypeDescriptor vec_desc;
  vec_desc = fw_make_container_desc("NativeVec", nativevec_trace);

  NativeVec *v = (NativeVec *)fw_gc_alloc(sizeof(NativeVec), &vec_desc);
  void *root = v; fw_gc_add_root(&root);
  v->elems = (void **)malloc(50 * sizeof(void *));
  v->n = 0;

  fw_gc_set_stress(1);                      /* collect on EVERY alloc */
  for (int i = 0; i < 50; i++) {
    char *s = (char *)fw_gc_alloc(4, &g_blob);
    s[0] = (char)('a' + (i % 26)); s[1] = 0;
    v->elems[i] = s;
    v->n = (size_t)(i + 1);
  }
  fw_gc_set_stress(0);

  CHECK(fw_gc_stats().live_objects == 51);  /* handle + 50 elements */
  for (int i = 0; i < 50; i++)
    CHECK(((char *)v->elems[i])[0] == (char)('a' + (i % 26)));
  free(v->elems);
}

/* The two helpers every FFI module uses (fw_gc_container.h). */
static void test_container_header_helpers(void) {
  /* Pointer-carrying dynamic tags, mirroring fw_dyn_desc's ptr_tags. */
  CHECK(fw_dyn_tag_is_gc_ptr(5) == 1);      /* STRING */
  CHECK(fw_dyn_tag_is_gc_ptr(9) == 1);      /* OBJECT */
  CHECK(fw_dyn_tag_is_gc_ptr(10) == 1);     /* ARRAY  */
  CHECK(fw_dyn_tag_is_gc_ptr(0) == 0);
  CHECK(fw_dyn_tag_is_gc_ptr(2) == 0);      /* INT64  */
  CHECK(fw_dyn_tag_is_gc_ptr(11) == 0);
  CHECK(fw_dyn_tag_is_gc_ptr(-1) == 0);
  /* Must agree with the shared descriptor the runtime actually uses. */
  for (uint32_t i = 0; i < fw_dyn_desc.num_ptr_tags; i++)
    CHECK(fw_dyn_tag_is_gc_ptr(fw_dyn_desc.ptr_tags[i]) == 1);

  /* fw_make_container_desc: BLOB layout + hook, every other field zeroed. */
  FWTypeDescriptor d = fw_make_container_desc("MyContainer", nativevec_trace);
  CHECK(strcmp(d.name, "MyContainer") == 0);
  CHECK(d.kind == FW_KIND_BLOB);
  CHECK(d.trace == nativevec_trace);
  CHECK(d.num_ptrs == 0);
  CHECK(d.ptr_offsets == NULL);
  CHECK(d.tag_offset == 0);
  CHECK(d.value_offset == 0);
  CHECK(d.num_ptr_tags == 0);
  CHECK(d.ptr_tags == NULL);
  CHECK(d.elem_desc == NULL);
  CHECK(d.elem_size == 0);
}

/* ==========================================================================
   Shadow stack
   ========================================================================== */

/* Empty frames (n = 0), NULL slot values, and a deep frame chain must all be
   walked correctly. */
static void test_shadow_frame_edge_cases(void) {
  fw_gc_init();

  void *live = fw_gc_alloc(8, &g_blob);
  void *nothing = NULL;

  FWFrame empty_frame = { .prev = NULL, .n = 0, .roots = NULL };
  void *null_slots[1] = { (void *)&nothing };
  FWFrame null_frame  = { .prev = &empty_frame, .n = 1, .roots = null_slots };
  void *live_slots[1] = { (void *)&live };
  FWFrame live_frame  = { .prev = &null_frame, .n = 1, .roots = live_slots };

  fw_gc_shadow_top = &live_frame;
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);
  fw_gc_shadow_top = NULL;
}

/* A deep chain of frames (deep recursion in generated code) must all be
   visited — the walker follows `prev` to the very bottom. */
static void test_deep_shadow_frame_chain(void) {
  fw_gc_init();
  enum { DEPTH = 200 };
  static FWFrame frames[DEPTH];
  static void   *objs[DEPTH];
  static void   *slots[DEPTH][1];

  for (int i = 0; i < DEPTH; i++) {
    char *p = (char *)fw_gc_alloc(8, &g_blob);
    p[0] = (char)('a' + (i % 26));
    objs[i] = p;
    slots[i][0] = (void *)&objs[i];
    frames[i].prev  = (i == 0) ? NULL : &frames[i - 1];
    frames[i].n     = 1;
    frames[i].roots = slots[i];
    fw_gc_shadow_top = &frames[i];          /* push as we go, like real calls */
  }
  (void)fw_gc_alloc(8, &g_blob);            /* garbage */
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == DEPTH);
  for (int i = 0; i < DEPTH; i++)
    CHECK(((char *)objs[i])[0] == (char)('a' + (i % 26)));

  /* Popping every frame makes them all garbage. */
  fw_gc_shadow_top = NULL;
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);
}

/* Popping to a caller's frame must free only what the callee alone kept. */
static void test_shadow_frame_pop_frees_callee_only(void) {
  fw_gc_init();
  void *caller_obj = fw_gc_alloc(8, &g_blob);
  void *caller_slots[1] = { (void *)&caller_obj };
  FWFrame caller = { .prev = NULL, .n = 1, .roots = caller_slots };
  fw_gc_shadow_top = &caller;

  void *callee_obj = fw_gc_alloc(8, &g_blob);
  void *callee_slots[1] = { (void *)&callee_obj };
  FWFrame callee = { .prev = fw_gc_shadow_top, .n = 1, .roots = callee_slots };
  fw_gc_shadow_top = &callee;

  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 2);

  fw_gc_shadow_top = callee.prev;           /* return from callee */
  callee_obj = NULL;
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 1);   /* caller's object still rooted */

  fw_gc_shadow_top = NULL;
}

/* Shadow-stack roots and global roots must both be honoured in one cycle. */
static void test_shadow_and_global_roots_together(void) {
  fw_gc_init();
  void *global_obj = fw_gc_alloc(8, &g_blob);
  fw_gc_add_root(&global_obj);

  void *frame_obj = fw_gc_alloc(8, &g_blob);
  void *slots[1] = { (void *)&frame_obj };
  FWFrame f = { .prev = NULL, .n = 1, .roots = slots };
  fw_gc_shadow_top = &f;

  (void)fw_gc_alloc(8, &g_blob);            /* garbage */
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 2);
  fw_gc_shadow_top = NULL;
}

/* fw_gc_init deliberately does NOT clear the shadow stack: the compiled `main`
   pushes its frame before calling fw_gc_init, and clearing would orphan it. */
static void test_init_preserves_shadow_top(void) {
  void *dummy_slots[1];
  FWFrame frame = { .prev = NULL, .n = 0, .roots = dummy_slots };
  fw_gc_shadow_top = &frame;
  fw_gc_init();
  CHECK(fw_gc_shadow_top == &frame);
  fw_gc_shadow_top = NULL;
}

/* ==========================================================================
   Reachability shapes
   ========================================================================== */

/* A cycle that IS reachable must survive, and keep surviving: the mark bits
   have to be cleared by the sweep or the second cycle would collect it. */
static void test_rooted_cycle_survives_repeated_collections(void) {
  fw_gc_init();
  Node *x = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  Node *y = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  x->a = y; y->a = x;                       /* cycle */
  void *root = x; fw_gc_add_root(&root);

  for (int i = 0; i < 5; i++) {
    fw_gc_collect();
    CHECK(fw_gc_stats().live_objects == 2);
  }
  CHECK(((Node *)((Node *)root)->a)->a == root);   /* graph intact */

  fw_gc_remove_root(&root);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);
}

/* Two roots reaching the same object: it is marked once and freed only when
   BOTH roots are gone (no premature free, no double free). */
static void test_shared_object_two_roots(void) {
  fw_gc_init();
  char *shared = (char *)fw_gc_alloc(8, &g_blob); shared[0] = 's';
  Node *n1 = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  Node *n2 = (Node *)fw_gc_alloc(sizeof(Node), &g_node_desc);
  n1->a = shared; n2->a = shared;

  void *r1 = n1, *r2 = n2;
  fw_gc_add_root(&r1);
  fw_gc_add_root(&r2);
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 3);

  fw_gc_remove_root(&r1); r1 = NULL;
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 2);   /* n1 gone, shared still held by n2 */
  CHECK(shared[0] == 's');

  fw_gc_remove_root(&r2); r2 = NULL;
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == 0);
}

/* A wide fan-out (one root, many children) exercises the work-list growth
   path, which reallocs from an initial capacity of 64. */
static void test_wide_fanout(void) {
  fw_gc_init();
  enum { WIDTH = 500 };
  Cell *cells = (Cell *)fw_gc_alloc_array(&g_cellarr_desc, WIDTH);
  void *root = cells; fw_gc_add_root(&root);
  for (int i = 0; i < WIDTH; i++) {
    char *s = (char *)fw_gc_alloc(4, &g_blob);
    s[0] = (char)('a' + (i % 26));
    cells[i].p = s;
  }
  fw_gc_collect();
  CHECK(fw_gc_stats().live_objects == WIDTH + 1);
  for (int i = 0; i < WIDTH; i++)
    CHECK(((char *)cells[i].p)[0] == (char)('a' + (i % 26)));
}

/* ==========================================================================
   Statistics and the heap-growth policy
   ========================================================================== */

static void test_stats_accounting(void) {
  fw_gc_init();
  FWGCStats s = fw_gc_stats();
  CHECK(s.live_objects == 0 && s.live_bytes == 0);
  CHECK(s.total_allocs == 0 && s.total_frees == 0);

  void *keep = fw_gc_alloc(100, &g_blob);
  fw_gc_add_root(&keep);
  (void)fw_gc_alloc(200, &g_blob);          /* garbage */

  s = fw_gc_stats();
  CHECK(s.live_objects == 2);
  CHECK(s.live_bytes == 300);
  CHECK(s.total_allocs == 2);
  CHECK(s.total_frees == 0);

  fw_gc_collect();
  s = fw_gc_stats();
  CHECK(s.live_objects == 1);
  CHECK(s.live_bytes == 100);               /* exactly the freed size removed */
  CHECK(s.total_allocs == 2);               /* cumulative: never decreases */
  CHECK(s.total_frees == 1);

  /* fw_gc_init resets every counter. */
  fw_gc_init();
  s = fw_gc_stats();
  CHECK(s.live_objects == 0 && s.live_bytes == 0);
  CHECK(s.total_allocs == 0 && s.total_frees == 0);
}

/* Crossing the 1 MiB default threshold triggers a collection on allocation,
   with no explicit fw_gc_collect call. */
static void test_threshold_triggers_automatic_collection(void) {
  fw_gc_init();
  fw_gc_set_stress(0);
  for (int i = 0; i < 24; i++)
    (void)fw_gc_alloc(64 * 1024, &g_blob);  /* 1.5 MiB of pure garbage */
  CHECK(fw_gc_stats().total_frees > 0);     /* collected without being asked */
  CHECK(fw_gc_stats().live_bytes < (size_t)1 << 21);
}

/* After a collection the threshold grows to 2x the surviving bytes, so an
   all-live heap does NOT collect on every subsequent allocation (that would be
   O(N^2)). Detected with a canary: if a collection ran, the unrooted canary
   would have been freed. */
static void test_threshold_grows_with_live_heap(void) {
  fw_gc_init();
  fw_gc_set_stress(0);

  void *big = fw_gc_alloc(2u << 20, &g_blob);   /* 2 MiB, kept alive */
  fw_gc_add_root(&big);
  fw_gc_collect();                              /* threshold now ~4 MiB */
  CHECK(fw_gc_stats().live_bytes == (size_t)(2u << 20));

  size_t frees_before = fw_gc_stats().total_frees;
  (void)fw_gc_alloc(8, &g_blob);                /* unrooted canary */
  for (int i = 0; i < 10; i++)
    (void)fw_gc_alloc(1024, &g_blob);           /* well under the threshold */
  CHECK(fw_gc_stats().total_frees == frees_before);  /* no collection happened */
}

/* fw_gc_set_stress(0) must actually stop the collect-on-every-alloc behaviour
   turned on by fw_gc_set_stress(1). */
static void test_stress_toggle_off(void) {
  fw_gc_init();
  fw_gc_set_stress(1);
  (void)fw_gc_alloc(8, &g_blob);
  (void)fw_gc_alloc(8, &g_blob);
  CHECK(fw_gc_stats().total_frees > 0);

  fw_gc_set_stress(0);
  size_t frees_before = fw_gc_stats().total_frees;
  for (int i = 0; i < 10; i++)
    (void)fw_gc_alloc(8, &g_blob);
  CHECK(fw_gc_stats().total_frees == frees_before);
}

/* fw_gc_init must forget the previous heap's roots: a slot registered before
   the re-init must not be consulted afterwards (it may point at freed memory). */
static void test_init_clears_global_roots(void) {
  fw_gc_init();
  void *stale = fw_gc_alloc(8, &g_blob);
  fw_gc_add_root(&stale);

  fw_gc_init();                             /* drops the old root list */
  void *fresh = fw_gc_alloc(8, &g_blob);
  (void)fresh;
  fw_gc_collect();                          /* must not follow `stale` */
  CHECK(fw_gc_stats().live_objects == 0);
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
  RUN_TEST(test_stress_env_toggle);

  /* Root bookkeeping */
  RUN_TEST(test_remove_root_swap_keeps_others);
  RUN_TEST(test_remove_root_unknown_slot_is_noop);
  RUN_TEST(test_global_roots_grow_beyond_initial_capacity);
  RUN_TEST(test_global_root_slot_reassignment);
  RUN_TEST(test_null_root_slot);

  /* Pointer resolution */
  RUN_TEST(test_interior_pointer_keeps_object_alive);
  RUN_TEST(test_non_heap_pointers_are_skipped);

  /* Precision */
  RUN_TEST(test_blob_bytes_are_not_scanned);
  RUN_TEST(test_tagged_non_pointer_tag_does_not_retain);

  /* Descriptor shapes */
  RUN_TEST(test_array_of_plain_structs);
  RUN_TEST(test_nested_array_descriptor);
  RUN_TEST(test_array_of_mixed_tags);
  RUN_TEST(test_array_zero_elem_size_is_safe);

  /* Zero-sized objects */
  RUN_TEST(test_zero_size_object_rooted_survives);
  RUN_TEST(test_empty_array_rooted_survives);

  /* Finalizers */
  RUN_TEST(test_finalizer_runs_once_when_unreachable);
  RUN_TEST(test_finalizers_are_per_object);
  RUN_TEST(test_finalizer_absent_is_noop);
  RUN_TEST(test_init_drops_pending_finalizers);

  /* FFI trace hook */
  RUN_TEST(test_trace_hook_keeps_native_elements_alive);
  RUN_TEST(test_trace_hook_runs_alongside_plain_scan);
  RUN_TEST(test_trace_hook_under_stress);
  RUN_TEST(test_container_header_helpers);

  /* Shadow stack */
  RUN_TEST(test_shadow_frame_edge_cases);
  RUN_TEST(test_deep_shadow_frame_chain);
  RUN_TEST(test_shadow_frame_pop_frees_callee_only);
  RUN_TEST(test_shadow_and_global_roots_together);
  RUN_TEST(test_init_preserves_shadow_top);

  /* Reachability shapes */
  RUN_TEST(test_rooted_cycle_survives_repeated_collections);
  RUN_TEST(test_shared_object_two_roots);
  RUN_TEST(test_wide_fanout);

  /* Stats and growth policy */
  RUN_TEST(test_stats_accounting);
  RUN_TEST(test_threshold_triggers_automatic_collection);
  RUN_TEST(test_threshold_grows_with_live_heap);
  RUN_TEST(test_stress_toggle_off);
  RUN_TEST(test_init_clears_global_roots);
  return TEST_SUMMARY();
}
