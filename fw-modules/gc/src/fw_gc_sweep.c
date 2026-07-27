#include "fw_gc.h"
#include "fw_gc_internal.h"
#include <stdlib.h>
#include <string.h>

/* Walk the all-objects list: free unmarked, clear marks on survivors. */
static void fw_gc_sweep(void) {
  FWObjHeader **link = &g_all_objects;
  while (*link) {
    FWObjHeader *h = *link;
    if (fw_word_marked(h->desc_and_flags)) {
      h->desc_and_flags = fw_word_clear_mark(h->desc_and_flags);  /* reset for next cycle */
      link = &h->next;
    } else {
      *link = h->next;                       /* unlink */
      fw_gc_run_finalizer_if_any(fw_payload(h));
      g_stats.live_objects--;
      g_stats.live_bytes -= h->size;
      g_stats.total_frees++;
      memset(h, 0xDD, FW_HEADER_SIZE + h->size);  /* poison to catch use-after-free */
      free(h);
    }
  }
}

void fw_gc_collect(void) {
  /* Snapshot the (stable) live set into a sorted index so resolve_object is
     O(log N) during marking; drop it before the sweep frees objects. */
  fw_gc_build_object_index();
  fw_gc_mark_from_roots();
  fw_gc_free_object_index();
  fw_gc_sweep();

  /* Heap-growth policy: schedule the next collection relative to how much
     survived this cycle. Without this, an all-live workload keeps live_bytes
     pinned just over a fixed threshold and collects on every alloc -> O(N^2).
     Doubling gives O(log N) collections and amortized-linear total work.
     Floor at 1 MiB so tiny heaps don't collect too eagerly. */
  size_t grown = g_stats.live_bytes * 2;
  size_t floor = (size_t)1 << 20;
  g_threshold = grown > floor ? grown : floor;
}
