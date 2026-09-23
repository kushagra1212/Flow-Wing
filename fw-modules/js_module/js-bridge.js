// The JavaScript half of Flow-Wing's js module (js-module.fg, js_bridge.c).
//
// An Emscripten JavaScript library, passed to every wasm32 link with
// --js-library (WasmLinkPass). Emscripten includes a function from it only
// when the program calls it, which only a program that brings js does.
//
//   Flow-Wing  js::Value.get("title")
//      │
//   C          fw_js_get          js_bridge.c: strings, errors
//      │
//   here       fwjs_get           the value itself, from the handle table
//
// Handles. A JavaScript value cannot live in wasm memory, so Flow-Wing holds a
// handle: a small number indexing `values`. Handle 0 is undefined. An object
// keeps one handle however often it is looked up (`ids` finds it again), with
// a count of the Flow-Wing values holding it; release() frees it at zero.
//
// Errors. Every call is guarded: an exception is kept in `error` and the call
// returns a neutral value. The C half then ends the program with a runtime
// error, or, inside js::try, hands the message to Flow-Wing as an Err.
//
// Waiting. Events and settled promises are queued here. While the program has
// nothing to run, the scheduler's waiter sleeps in fwjs_sleep through Asyncify,
// so the page stays responsive; notify() wakes it.

addToLibrary({
  // Every function below depends on $FWJS, so these come with any of them.
  $FWJS__deps: ['$stringToNewUTF8', '$UTF8ToString'],
  $FWJS: {
    // Index 0 stays empty: handle 0 means undefined. (Not [undefined]: the
    // library is written out as source, and that comes out as [].)
    values: [],
    refs: [0],
    free: [],
    ids: new Map(),
    error: null,
    // Listener id → { target, type, fn }, and events waiting to be handled.
    listeners: new Map(),
    nextListener: 1,
    events: [],
    current: 0,
    // Await id → { state: 1 fulfilled | 2 rejected, value }.
    awaits: new Map(),
    nextAwait: 1,
    // Set while the program sleeps in fwjs_sleep; calling it wakes it.
    wake: null,
    pending: false,

    isObject(value) {
      return (typeof value === 'object' && value !== null) || typeof value === 'function';
    },

    handle(value) {
      if (value === undefined) return 0;
      const object = FWJS.isObject(value);
      if (object) {
        const known = FWJS.ids.get(value);
        if (known !== undefined) {
          FWJS.refs[known]++;
          return known;
        }
      }
      const h = FWJS.free.length ? FWJS.free.pop() : Math.max(1, FWJS.values.length);
      FWJS.values[h] = value;
      FWJS.refs[h] = 1;
      if (object) FWJS.ids.set(value, h);
      return h;
    },

    release(h) {
      if (h <= 0 || !(FWJS.refs[h] > 0)) return;
      if (--FWJS.refs[h] > 0) return;
      const value = FWJS.values[h];
      if (FWJS.isObject(value)) FWJS.ids.delete(value);
      FWJS.values[h] = undefined;
      FWJS.free.push(h);
    },

    guard(fn, fallback) {
      try {
        return fn();
      } catch (e) {
        FWJS.error = e && e.message !== undefined ? String(e.message) : String(e);
        return fallback;
      }
    },

    // A string for C, as fresh UTF-8 in the wasm heap. C copies it into a
    // Flow-Wing string and frees this one.
    text(value) {
      return stringToNewUTF8(value === undefined || value === null ? '' : String(value));
    },

    notify() {
      FWJS.pending = true;
      if (FWJS.wake) FWJS.wake();
    },
  },

  // ---- values ---------------------------------------------------------------

  fwjs_global__deps: ['$FWJS'],
  fwjs_global: () => FWJS.handle(globalThis),

  fwjs_null__deps: ['$FWJS'],
  fwjs_null: () => FWJS.handle(null),

  fwjs_from_str__deps: ['$FWJS'],
  fwjs_from_str: (s) => FWJS.handle(UTF8ToString(s)),

  fwjs_from_num__deps: ['$FWJS'],
  fwjs_from_num: (n) => FWJS.handle(n),

  fwjs_from_bool__deps: ['$FWJS'],
  fwjs_from_bool: (b) => FWJS.handle(!!b),

  fwjs_release__deps: ['$FWJS'],
  fwjs_release: (h) => FWJS.release(h),

  fwjs_retain__deps: ['$FWJS'],
  fwjs_retain: (h) => {
    if (h > 0 && FWJS.refs[h] > 0) FWJS.refs[h]++;
    return h;
  },

  fwjs_to_str__deps: ['$FWJS'],
  fwjs_to_str: (h) => FWJS.text(FWJS.guard(() => String(FWJS.values[h]), '')),

  fwjs_to_num__deps: ['$FWJS'],
  fwjs_to_num: (h) => FWJS.guard(() => Number(FWJS.values[h]), NaN),

  fwjs_to_bool__deps: ['$FWJS'],
  fwjs_to_bool: (h) => (FWJS.values[h] ? 1 : 0),

  fwjs_type__deps: ['$FWJS'],
  fwjs_type: (h) => {
    const value = FWJS.values[h];
    return FWJS.text(value === null ? 'null' : Array.isArray(value) ? 'array' : typeof value);
  },

  fwjs_same__deps: ['$FWJS'],
  fwjs_same: (a, b) => (FWJS.values[a] === FWJS.values[b] ? 1 : 0),

  // ---- properties -----------------------------------------------------------

  fwjs_get__deps: ['$FWJS'],
  fwjs_get: (h, name) => FWJS.guard(() => FWJS.handle(FWJS.values[h][UTF8ToString(name)]), 0),

  fwjs_get_str__deps: ['$FWJS'],
  fwjs_get_str: (h, name) => FWJS.text(FWJS.guard(() => FWJS.values[h][UTF8ToString(name)], '')),

  fwjs_get_num__deps: ['$FWJS'],
  fwjs_get_num: (h, name) => FWJS.guard(() => Number(FWJS.values[h][UTF8ToString(name)]), NaN),

  fwjs_get_bool__deps: ['$FWJS'],
  fwjs_get_bool: (h, name) => FWJS.guard(() => (FWJS.values[h][UTF8ToString(name)] ? 1 : 0), 0),

  fwjs_at__deps: ['$FWJS'],
  fwjs_at: (h, index) => FWJS.guard(() => FWJS.handle(FWJS.values[h][index]), 0),

  fwjs_set__deps: ['$FWJS'],
  fwjs_set: (h, name, v) => FWJS.guard(() => {
    FWJS.values[h][UTF8ToString(name)] = FWJS.values[v];
  }),

  fwjs_set_str__deps: ['$FWJS'],
  fwjs_set_str: (h, name, s) => FWJS.guard(() => {
    FWJS.values[h][UTF8ToString(name)] = UTF8ToString(s);
  }),

  fwjs_set_num__deps: ['$FWJS'],
  fwjs_set_num: (h, name, n) => FWJS.guard(() => {
    FWJS.values[h][UTF8ToString(name)] = n;
  }),

  fwjs_set_bool__deps: ['$FWJS'],
  fwjs_set_bool: (h, name, b) => FWJS.guard(() => {
    FWJS.values[h][UTF8ToString(name)] = !!b;
  }),

  // ---- calls ----------------------------------------------------------------

  // args: a handle to a JavaScript array (js::Args), or 0 for none.
  fwjs_call__deps: ['$FWJS'],
  fwjs_call: (h, method, args) => FWJS.guard(() => {
    const target = FWJS.values[h];
    const name = UTF8ToString(method);
    const fn = target[name];
    if (typeof fn !== 'function') throw new TypeError(`${name} is not a function`);
    return FWJS.handle(fn.apply(target, args ? FWJS.values[args] : []));
  }, 0),

  fwjs_invoke__deps: ['$FWJS'],
  fwjs_invoke: (h, args) => FWJS.guard(() => {
    const fn = FWJS.values[h];
    if (typeof fn !== 'function') throw new TypeError('the value is not a function');
    return FWJS.handle(fn.apply(undefined, args ? FWJS.values[args] : []));
  }, 0),

  fwjs_new__deps: ['$FWJS'],
  fwjs_new: (h, args) => FWJS.guard(() => {
    const Ctor = FWJS.values[h];
    return FWJS.handle(new Ctor(...(args ? FWJS.values[args] : [])));
  }, 0),

  fwjs_eval__deps: ['$FWJS'],
  // Indirect eval: global scope, not this function's.
  fwjs_eval: (code) => FWJS.guard(() => FWJS.handle((0, eval)(UTF8ToString(code))), 0),

  fwjs_array__deps: ['$FWJS'],
  fwjs_array: () => FWJS.handle([]),

  fwjs_push__deps: ['$FWJS'],
  fwjs_push: (a, v) => {
    FWJS.values[a].push(FWJS.values[v]);
  },

  fwjs_push_str__deps: ['$FWJS'],
  fwjs_push_str: (a, s) => {
    FWJS.values[a].push(UTF8ToString(s));
  },

  fwjs_push_num__deps: ['$FWJS'],
  fwjs_push_num: (a, n) => {
    FWJS.values[a].push(n);
  },

  fwjs_push_bool__deps: ['$FWJS'],
  fwjs_push_bool: (a, b) => {
    FWJS.values[a].push(!!b);
  },

  // ---- errors ---------------------------------------------------------------

  fwjs_threw__deps: ['$FWJS'],
  fwjs_threw: () => (FWJS.error !== null ? 1 : 0),

  fwjs_take_error__deps: ['$FWJS'],
  fwjs_take_error: () => {
    const message = FWJS.error === null ? '' : FWJS.error;
    FWJS.error = null;
    return FWJS.text(message);
  },

  // ---- events ---------------------------------------------------------------

  // flags: 1 preventDefault, 2 stopPropagation. Done here, in the listener:
  // by the time the Flow-Wing handler runs, the browser may have acted.
  fwjs_listen__deps: ['$FWJS'],
  fwjs_listen: (h, type, flags) => FWJS.guard(() => {
    const target = FWJS.values[h];
    const name = UTF8ToString(type);
    const id = FWJS.nextListener++;
    const fn = (event) => {
      if (flags & 1) event.preventDefault();
      if (flags & 2) event.stopPropagation();
      FWJS.events.push([id, event]);
      FWJS.notify();
    };
    target.addEventListener(name, fn);
    FWJS.listeners.set(id, { target, type: name, fn });
    return id;
  }, 0),

  // A timer is a listener with no target: it queues an event (undefined) after
  // ms, and every ms after that when repeat is set. A one-shot timer forgets
  // itself when it fires; fwjs_alive tells Flow-Wing so.
  fwjs_timer__deps: ['$FWJS'],
  fwjs_timer: (ms, repeat) => {
    const id = FWJS.nextListener++;
    const fire = () => {
      if (!repeat) FWJS.listeners.delete(id);
      FWJS.events.push([id, undefined]);
      FWJS.notify();
    };
    const timer = repeat ? setInterval(fire, ms) : setTimeout(fire, ms);
    FWJS.listeners.set(id, { timer, repeat: !!repeat });
    return id;
  },

  fwjs_unlisten__deps: ['$FWJS'],
  fwjs_unlisten: (id) => {
    const listener = FWJS.listeners.get(id);
    if (!listener) return;
    if (listener.timer !== undefined) {
      (listener.repeat ? clearInterval : clearTimeout)(listener.timer);
    } else {
      listener.target.removeEventListener(listener.type, listener.fn);
    }
    FWJS.listeners.delete(id);
  },

  fwjs_alive__deps: ['$FWJS'],
  fwjs_alive: (id) => (FWJS.listeners.has(id) ? 1 : 0),

  // Handles in use, for tests that check values are released.
  fwjs_live_handles__deps: ['$FWJS'],
  fwjs_live_handles: () => FWJS.refs.filter((count) => count > 0).length,

  // The listener id of the next event, 0 when there is none. Its event object
  // is then fwjs_event(). Events of a listener removed since are dropped.
  fwjs_next_event__deps: ['$FWJS'],
  fwjs_next_event: () => {
    while (FWJS.events.length) {
      const [id, event] = FWJS.events.shift();
      // Dropped if removed since, unless it is a one-shot timer's own event
      // (the timer forgot itself as it fired).
      if (!FWJS.listeners.has(id) && event !== undefined) continue;
      FWJS.current = FWJS.handle(event);
      return id;
    }
    return 0;
  },

  fwjs_event__deps: ['$FWJS'],
  fwjs_event: () => FWJS.current,

  // ---- promises -------------------------------------------------------------

  fwjs_await__deps: ['$FWJS'],
  fwjs_await: (h) => {
    const id = FWJS.nextAwait++;
    Promise.resolve(FWJS.values[h]).then(
      (value) => { FWJS.awaits.set(id, { state: 1, value }); FWJS.notify(); },
      (reason) => { FWJS.awaits.set(id, { state: 2, value: reason }); FWJS.notify(); },
    );
    return id;
  },

  // 0 while pending, 1 fulfilled, 2 rejected.
  fwjs_await_state__deps: ['$FWJS'],
  fwjs_await_state: (id) => {
    const settled = FWJS.awaits.get(id);
    return settled ? settled.state : 0;
  },

  // The result, and forget the promise. A rejection's reason becomes the
  // error message, as a thrown exception's does.
  fwjs_await_take__deps: ['$FWJS'],
  fwjs_await_take: (id) => {
    const settled = FWJS.awaits.get(id);
    FWJS.awaits.delete(id);
    if (!settled) return 0;
    if (settled.state === 2) {
      const reason = settled.value;
      FWJS.error = reason && reason.message !== undefined ? String(reason.message) : String(reason);
      return 0;
    }
    return FWJS.handle(settled.value);
  },

  // ---- waiting --------------------------------------------------------------

  fwjs_pending__deps: ['$FWJS'],
  fwjs_pending: () => (FWJS.pending ? 1 : 0),

  fwjs_take_pending__deps: ['$FWJS'],
  fwjs_take_pending: () => {
    const was = FWJS.pending;
    FWJS.pending = false;
    return was ? 1 : 0;
  },

  // Sleeps until notify() or, when ms >= 0, until ms have passed. Asyncify
  // unwinds the program meanwhile, so the page handles input and paints.
  fwjs_sleep__deps: ['$FWJS'],
  fwjs_sleep__async: true,
  fwjs_sleep: (ms) => Asyncify.handleSleep((wakeUp) => {
    let timer = null;
    const done = () => {
      FWJS.wake = null;
      if (timer !== null) clearTimeout(timer);
      wakeUp();
    };
    if (FWJS.pending) {
      done();
      return;
    }
    FWJS.wake = done;
    if (ms >= 0) timer = setTimeout(done, ms);
  }),
});
