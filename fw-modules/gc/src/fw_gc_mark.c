#include "fw_gc.h"
#include "fw_gc_internal.h"
#include <stdlib.h>

/* A growable work-list of object pointers (NEVER recurse over the heap graph). */
static void **s_work = NULL;
static size_t s_work_len = 0, s_work_cap = 0;

static void work_push(void *p) {
  /* Precise roots and object fields normally hold exact object bases, but a
     string value may point at a static constant (empty string / literal) that
     is not GC-managed. Resolve through the all-objects list so such pointers
     (and any junk) are skipped instead of having a garbage header read. */
  void *obj = fw_gc_resolve_object(p);
  if (obj == NULL) return;
  if (s_work_len == s_work_cap) {
    s_work_cap = s_work_cap ? s_work_cap * 2 : 64;
    s_work = (void **)realloc(s_work, s_work_cap * sizeof(void *));
  }
  s_work[s_work_len++] = obj;
}

/* Seed a root object onto the work-list, using the exact same path as the
   global-root / shadow-stack seeding below. */
void fw_gc_push_root_object(void *obj) {
  work_push(obj);
}

/* Scan the pointer slots described by `desc` over the memory at `base`
   (size bytes), pushing every referenced heap object onto the work-list.
   Recursion here is bounded by descriptor NESTING depth (ARRAY of TAGGED),
   not by the object graph, so it cannot overflow the stack. */
static void scan_fields(char *base, const FWTypeDescriptor *desc, size_t size) {
  /* Custom deep-scan hook (independent of `kind`): lets a native container mark
     GC pointers held in memory the layout fields cannot describe (e.g. a C++
     std::vector on the malloc heap). `work_push` is the enqueue primitive and
     already resolves/skips non-heap pointers, so it is the `mark` callback. */
  if (desc->trace != NULL)
    desc->trace((void *)base, work_push);

  switch (desc->kind) {
    case FW_KIND_BLOB:
      break;                                  /* no pointers */
    case FW_KIND_PLAIN:
      for (uint32_t i = 0; i < desc->num_ptrs; i++) {
        void *p = *(void **)(base + desc->ptr_offsets[i]);
        work_push(p);
      }
      break;
    case FW_KIND_TAGGED: {                     /* implemented fully in Task 5 */
      int32_t tag = *(int32_t *)(base + desc->tag_offset);
      for (uint32_t i = 0; i < desc->num_ptr_tags; i++) {
        if (tag == desc->ptr_tags[i]) {
          work_push(*(void **)(base + desc->value_offset));
          break;
        }
      }
      break;
    }
    case FW_KIND_ARRAY: {                       /* implemented fully in Task 6 */
      size_t n = desc->elem_size ? size / desc->elem_size : 0;
      for (size_t i = 0; i < n; i++) {
        scan_fields(base + i * desc->elem_size, desc->elem_desc, desc->elem_size);
      }
      break;
    }
  }
}

/* Set the mark bit and scan the object's fields. */
static void mark_object(void *obj) {
  FWObjHeader *h = fw_header(obj);
  if (fw_word_marked(h->desc_and_flags)) return;      /* already done (handles cycles) */
  h->desc_and_flags = fw_word_set_mark(h->desc_and_flags);
  const FWTypeDescriptor *desc = fw_word_desc(h->desc_and_flags);
  scan_fields((char *)obj, desc, h->size);
}

/* Push a root slot's current target, if any. */
static void push_root_slot(void **slot) {
  if (slot && *slot) fw_gc_push_root_object(*slot);
}

/* Mark everything reachable from all roots. Called by fw_gc_collect. */
void fw_gc_mark_from_roots(void) {
  s_work_len = 0;

  /* Global roots. */
  extern void **g_global_roots; extern size_t g_global_roots_len;
  for (size_t i = 0; i < g_global_roots_len; i++)
    push_root_slot((void **)g_global_roots[i]);

  /* Shadow-stack roots: walk frames, then each frame's slots. */
  for (FWFrame *f = fw_gc_shadow_top; f != NULL; f = f->prev)
    for (uint32_t i = 0; i < f->n; i++)
      push_root_slot((void **)f->roots[i]);

  /* Precise-only (M2): every live GC pointer is reachable through a global root,
     a shadow-stack slot (locals/params/args), a traced descriptor field, or a
     container trace hook. Conservative C-stack scanning is being removed — its
     call is disabled here while the remaining codegen temp-safety gaps are
     closed. Once precise-only stress is fully green the scanner code is deleted. */

  /* Drain the work-list. */
  while (s_work_len > 0) {
    void *obj = s_work[--s_work_len];
    mark_object(obj);
  }
}
