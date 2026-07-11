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

void fw_gc_init(void) {
  g_all_objects = NULL;
  memset(&g_stats, 0, sizeof(g_stats));
  g_stress = 0;
  g_threshold = 1u << 20;
  fw_gc_shadow_top = NULL;
  free(g_global_roots);
  g_global_roots = NULL;
  g_global_roots_len = 0;
  g_global_roots_cap = 0;
  while (g_finalizers) { FWFinalizer *n = g_finalizers->next; free(g_finalizers); g_finalizers = n; }
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
