---
sidebar_position: 1
title: Garbage Collector
---

# The garbage collector

Flow-Wing manages heap memory for you. There is no `free`, no ownership, no
lifetimes. This page explains what runs underneath.

:::tip Interactive version
Everything below has a **step-through visualisation** — watch marking propagate
through a live heap graph, toggle the flag bits inside an object header, and
compare descriptor kinds.

**[▶ Open the interactive GC walkthrough](pathname:///internals/gc.html)**
:::

<iframe
  src="/internals/gc.html"
  title="Interactive walkthrough of the Flow-Wing garbage collector"
  style={{width:'100%', height:'760px', border:'1px solid #30363d', borderRadius:'8px'}}
/>

## The short version

| Property | What it means |
|---|---|
| **Precise** | The collector knows exactly which words are pointers, from a per-type descriptor. It never guesses from bit patterns. |
| **Non-moving** | A live object never changes address, so no read or write barriers are needed. |
| **Mark and sweep** | Find everything reachable, free the rest. Two phases, stop-the-world. |
| **Single-threaded** | No locks anywhere. This is precisely why `spawn` uses coroutines instead of threads. |

## When a collection happens

Allocation is the only trigger — there is no background thread:

```c
if (g_stress || g_stats.live_bytes + size > g_threshold) {
    fw_gc_collect();
}
```

After each collection the threshold becomes `live_bytes * 2` (floor 1 MiB). A
fixed threshold would make an all-live workload collect on every allocation,
walking the whole heap each time — O(N²). Doubling gives O(log N) collections.

## Testing your program under pressure

```bash
FW_GC_STRESS=1 ./myprogram
```

That collects on **every single allocation**. If the output is identical to a
normal run, every value your program holds is properly rooted. If it changes,
something was reachable only by luck.

Every fixture under `tests/fixtures/LatestTests/GcTests/` runs with stress on
automatically. A fixture elsewhere opts in with a `/; FW_GC_STRESS` header line.

## Tasks and the collector

A suspended task's variables live on that task's own stack, which the normal
root chain does not point at. A queued task's arguments are referenced by
nothing at all. The scheduler registers an **auxiliary root scanner** so the
collector reaches both:

```c
fw_gc_set_aux_root_scanner(fn);      /* scheduler registers itself     */
fw_gc_mark_shadow_chain(top);        /* one parked task's frames       */
fw_gc_push_root_object(obj);         /* a queued task's argument block */
```

See *[Concurrency and the Event Loop](./Concurrency%20and%20the%20Event%20Loop.md)*
for the other side of that handshake.

## Where the code lives

| File | Contains |
|---|---|
| `fw-modules/gc/src/fw_gc_core.c` | allocation, roots, finalizers, the object index |
| `fw-modules/gc/src/fw_gc_mark.c` | work-list, `scan_fields`, root seeding |
| `fw-modules/gc/src/fw_gc_sweep.c` | sweep, poisoning, threshold growth |
| `fw-modules/gc/src/fw_gc_header.c` | packing the descriptor word and its flag bits |
| `fw-modules/gc/tests/test_gc.c` | 982 checks — run with `make test-gc` |
