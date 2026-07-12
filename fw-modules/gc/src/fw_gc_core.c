#include "fw_gc.h"
#include "fw_gc_internal.h"
#include <stdlib.h>
#include <string.h>

FWObjHeader *g_all_objects = NULL;
FWGCStats    g_stats;
int          g_stress = 0;
size_t       g_threshold = 1u << 20;   /* 1 MiB default */

FWFrame *fw_gc_shadow_top = NULL;
void   **g_global_roots = NULL;
size_t   g_global_roots_len = 0;
size_t   g_global_roots_cap = 0;

FWFinalizer *g_finalizers = NULL;

void fw_gc_register_finalizer(void *obj, void (*fn)(void *)) {
  FWFinalizer *f = (FWFinalizer *)malloc(sizeof(FWFinalizer));
  f->obj = obj; f->fn = fn; f->next = g_finalizers;
  g_finalizers = f;
}

/* Strong definition — overrides the weak default in fw_gc_sweep.c.
   Called with the payload pointer just before an object is freed. */
void fw_gc_run_finalizer_if_any(void *obj) {
  FWFinalizer **link = &g_finalizers;
  while (*link) {
    if ((*link)->obj == obj) {
      FWFinalizer *hit = *link;
      hit->fn(obj);
      *link = hit->next;
      free(hit);
      return;
    }
    link = &(*link)->next;
  }
}

/* forward-declared; implemented in Task 5 */
void fw_gc_collect(void);

/* ---- Per-collection object index ---------------------------------------
   fw_gc_resolve_object is called for every candidate pointer while marking.
   A linear scan of g_all_objects makes marking O(objects^2), which is fatal
   for large live heaps. Since no allocation happens during a collection, the
   set of live objects is stable, so we snapshot their payload ranges into a
   sorted array once per collection and binary-search it — O(log N) per lookup,
   O(N log N) marking overall. Interior pointers (e.g. `&arr[i]` into an inline
   array) are supported via the range check. */
typedef struct {
  uintptr_t lo;   /* payload base */
  uintptr_t hi;   /* one past the last payload byte */
} FWObjRange;

static FWObjRange *g_index = NULL;
static size_t      g_index_n = 0;

static int fw_range_cmp(const void *a, const void *b) {
  uintptr_t la = ((const FWObjRange *)a)->lo;
  uintptr_t lb = ((const FWObjRange *)b)->lo;
  return (la < lb) ? -1 : (la > lb) ? 1 : 0;
}

void fw_gc_build_object_index(void) {
  size_t n = 0;
  for (FWObjHeader *h = g_all_objects; h != NULL; h = h->next) n++;
  g_index = n ? (FWObjRange *)malloc(n * sizeof(FWObjRange)) : NULL;
  if (g_index == NULL) { g_index_n = 0; return; } /* OOM -> linear fallback */
  size_t i = 0;
  for (FWObjHeader *h = g_all_objects; h != NULL && i < n; h = h->next) {
    uintptr_t lo = (uintptr_t)fw_payload(h);
    g_index[i].lo = lo;
    g_index[i].hi = lo + h->size;
    i++;
  }
  g_index_n = i;
  qsort(g_index, g_index_n, sizeof(FWObjRange), fw_range_cmp);
}

void fw_gc_free_object_index(void) {
  free(g_index);
  g_index = NULL;
  g_index_n = 0;
}

/* Resolve an arbitrary pointer to the base of the live heap object that
   contains it (interior pointers included), or NULL if it points at no live
   object. A precise root or object field normally points at an exact object
   base, but a string value may legitimately point at a static string constant
   (e.g. the empty string) that is NOT GC-managed and has no object header;
   marking must skip such pointers instead of reading a garbage header. */
void *fw_gc_resolve_object(void *p) {
  if (p == NULL) return NULL;
  uintptr_t q = (uintptr_t)p;

  /* Fast path: binary-search the per-collection sorted index. Find the
     rightmost range whose base <= q, then range-check it. */
  if (g_index != NULL) {
    size_t lo = 0, hi = g_index_n;               /* search over [lo, hi)     */
    while (lo < hi) {
      size_t mid = lo + (hi - lo) / 2;
      if (g_index[mid].lo <= q) lo = mid + 1; else hi = mid;
    }
    if (lo > 0) {                                /* candidate is g_index[lo-1] */
      const FWObjRange *r = &g_index[lo - 1];
      if (q >= r->lo && q < r->hi) return (void *)r->lo;
    }
    return NULL;
  }

  /* Fallback (no active index, e.g. a call outside a collection): linear. */
  for (FWObjHeader *h = g_all_objects; h != NULL; h = h->next) {
    uintptr_t lo = (uintptr_t)fw_payload(h);
    uintptr_t hi = lo + h->size;                 /* one past the last byte */
    if (q >= lo && q < hi) return (void *)lo;
  }
  return NULL;
}

void fw_gc_init(void) {
  g_all_objects = NULL;
  memset(&g_stats, 0, sizeof(g_stats));
  g_stress = 0;
  g_threshold = 1u << 20;
  /* Do NOT reset fw_gc_shadow_top here. The compiled `main` pushes its own
     shadow frame at entry (before it calls fw_gc_init via the runtime-init
     preamble), so clearing the top would orphan main's frame and leave its
     roots invisible for the rest of the program. The shadow stack is
     compiler-managed and push/pop balanced; at true process start it is
     already NULL (BSS), so no reset is needed. */
  free(g_global_roots);
  g_global_roots = NULL;
  g_global_roots_len = 0;
  g_global_roots_cap = 0;
  while (g_finalizers) { FWFinalizer *n = g_finalizers->next; free(g_finalizers); g_finalizers = n; }
  const char *stress = getenv("FW_GC_STRESS");
  if (stress && stress[0] == '1' && stress[1] == '\0') g_stress = 1;
}

void fw_gc_add_root(void **slot) {
  if (g_global_roots_len == g_global_roots_cap) {
    size_t cap = g_global_roots_cap ? g_global_roots_cap * 2 : 8;
    g_global_roots = (void **)realloc(g_global_roots, cap * sizeof(void *));
    g_global_roots_cap = cap;
  }
  g_global_roots[g_global_roots_len++] = (void *)slot;
}

void fw_gc_remove_root(void **slot) {
  for (size_t i = 0; i < g_global_roots_len; i++) {
    if (g_global_roots[i] == (void *)slot) {
      g_global_roots[i] = g_global_roots[--g_global_roots_len];  /* swap-remove */
      return;
    }
  }
}

void fw_gc_set_stress(int on) { g_stress = on; }

FWGCStats fw_gc_stats(void) { return g_stats; }

void *fw_gc_alloc(size_t size, const FWTypeDescriptor *desc) {
  /* Collect first if stressing or over threshold (Task 5 defines collect). */
  if (g_stress || g_stats.live_bytes + size > g_threshold) {
    fw_gc_collect();
  }

  FWObjHeader *h = (FWObjHeader *)malloc(FW_HEADER_SIZE + size);
  if (!h) {                       /* one retry after a forced collect (OOM path) */
    fw_gc_collect();
    h = (FWObjHeader *)malloc(FW_HEADER_SIZE + size);
    if (!h) return NULL;
  }
  memset(fw_payload(h), 0, size);            /* zero the payload */
  h->desc_and_flags = fw_word_pack(desc);    /* mark bit clear */
  h->size = size;
  h->next = g_all_objects;                   /* thread onto all-objects list */
  g_all_objects = h;

  g_stats.live_objects++;
  g_stats.live_bytes += size;
  g_stats.total_allocs++;
  return fw_payload(h);
}

void *fw_gc_alloc_array(const FWTypeDescriptor *array_desc, size_t n) {
  size_t bytes = array_desc->elem_size * n;
  return fw_gc_alloc(bytes, array_desc);   /* header desc = the ARRAY descriptor */
}
