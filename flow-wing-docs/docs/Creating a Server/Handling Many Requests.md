---
sidebar_position: 9
title: Handling many requests
sidebar_label: Handling many requests
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Handling many requests at once

A server that answers one request at a time is easy to write by accident. This
page is a **lab**: you copy two files, run them, and watch five one-second
requests take five seconds. Then you change **two lines** and watch them take
one second.

Every number on this page came from running these exact files.

| | five requests, one second of work each |
|---|---|
| one at a time | **5004 ms** |
| all at once | **1002 ms** |

Both on a single thread. No thread pool, no locks.

---

## Step 1 — the server

Save this as **`server.fg`**. Hover the block and press **Copy**.

<CodeBlock code={
`bring vortex
bring Err
bring json
bring sys

fun handler(res: vortex::Response) -> nthg {
    sys::sleep(1000)          /; pretend this is a database call
    var node: json::JsonNode = json::newObject()
    node.put("lang", json::newString("Flow-Wing"))
    res.status(200).json(node)
}

fun serverLoop(app: vortex::Server) -> nthg {
    while true {
        var req: vortex::Request, res: vortex::Response = app.accept()
        println("got " + req.getPath())
        spawn handler(res)
    }
}

fun fg_main() -> nthg {
    var app: vortex::Server = new vortex::Server()
    var err: Err::Result = app.listen(8190)
    if Err::isErr(err) {
        println(err.getMessage())
        return:
    }
    println("listening on 8190")
    spawn serverLoop(app)
}

fg_main()
`} language="fg"/>

## Step 2 — the client

Save this as **`client.fg`**. It fires five requests and prints when each one
finishes.

<CodeBlock code={
`bring vortex
bring sys

fun fetch(id: int, t0: int64) -> nthg {
    var c: vortex::Client = new vortex::Client("http://127.0.0.1:8190/json", \`{"id":1}\`)

    var body: str = ""
    while !c.isDone() {
        var chunk: str = c.readChunk()
        if chunk != "" {
            body = body + chunk
        }
    }

    var ok: bool = c.isOk()   /; read the status BEFORE close()
    c.close()

    println("request " + String(id)
          + "  finished at " + String(Int64(sys::elapsedNanos(t0) / 1000000l)) + " ms"
          + "  ok=" + String(ok))
}

fun fg_main() -> nthg {
    var t0: int64 = sys::nanos()
    for var i: int = 0 to 4 {
        spawn fetch(i, t0)
    }
    println("5 requests queued")
}

fg_main()
`} language="fg"/>

## Step 3 — run them

Two terminals. Server first:

```bash
# terminal 1
FlowWing server.fg --emit=exe -o server && ./server
```

```bash
# terminal 2
FlowWing client.fg --emit=exe -o client && ./client
```

You should see:

```
request 0  finished at 1002 ms  ok=true
request 1  finished at 1003 ms  ok=true
request 2  finished at 1003 ms  ok=true
request 3  finished at 1003 ms  ok=true
request 4  finished at 1003 ms  ok=true
```

All five at about **one second**, not five. Stop the server with `Ctrl-C`.

---

## Now break it, on purpose

Four shapes are possible. Only one is correct, and the two broken ones look
perfectly reasonable. Try each — the numbers tell you which you have.

| Shape | Server | Client | Result |
|---|---|---|---|
| **A** | `handler(res)` | `spawn fetch()` | 1002, 2002, 3003, 4003, **5004 ms** |
| **B** | `spawn handler(res)` in a **top-level** loop | `spawn fetch()` | **hangs**, then `ok=false` |
| **C** | `spawn handler(res)` in a **top-level** loop | `fetch()` | **hangs**, then `ok=false` |
| **D** | loop in a **task** + `spawn handler(res)` | `spawn fetch()` | all at **1002 ms** ✅ |

### Shape A — forget `spawn` on the handler

In `server.fg`, change one line:

<CodeBlock code={
`        spawn handler(res)       /; before
        handler(res)             /; after`} language="fg"/>

```
request 0  finished at 1002 ms
request 1  finished at 2002 ms
request 2  finished at 3003 ms
request 3  finished at 4003 ms
request 4  finished at 5004 ms
```

One second apart. The loop cannot call `accept()` again until the handler has
finished, so requests queue up behind each other. **This is correct code — just
serial.**

### Shape B and C — the trap

Put the accept loop back at the top level, keeping `spawn` on the handler:

<CodeBlock code={
`fun fg_main() -> nthg {
    var app: vortex::Server = new vortex::Server()
    var err: Err::Result = app.listen(8190)
    if Err::isErr(err) {
        println(err.getMessage())
        return:
    }
    println("listening on 8190")

    while true {                 /; loop at the TOP LEVEL
        var req: vortex::Request, res: vortex::Response = app.accept()
        spawn handler(res)       /; looks like the fix. it is not.
    }
}

fg_main()
`} language="fg"/>

```
request 0  finished at 30002 ms  ok=false
request 1  finished at 30004 ms  ok=false
...
```

**Thirty seconds and no reply.** This shape is worse than shape A, and it is
the one people write when they hear "use `spawn` to go faster".

:::tip Do not wait 30 seconds
Shorten the timeout to see the failure straight away:

```bash
FW_HTTP_IDLE_TIMEOUT_MS=4000 ./server
```

The requests then fail at 4003 ms instead of 30002 ms — same cause, less
waiting. That the failure lands exactly on the timeout is the proof: the server
never answered at all.
:::

:::danger The most common mistake
`spawn` **queues** work. The queue only drains once the top-level body has
finished. A `while true` loop at the top level never finishes — so the handlers
you queued never run at all. Your clients wait until the server's 30-second
idle timeout drops the connection.
:::

### Shape D — the fix

Move the loop into its own task:

<CodeBlock code={
`fun serverLoop(app: vortex::Server) -> nthg {
    while true {
        var req: vortex::Request, res: vortex::Response = app.accept()
        spawn handler(res)
    }
}

fun fg_main() -> nthg {
    /; ... listen ...
    spawn serverLoop(app)        /; <- the whole difference
}
`} language="fg"/>

Once the loop is **itself a task**, `accept()` can suspend it. While it waits
for the next connection, the scheduler runs the handlers that are queued. At
the top level `accept()` has nothing to suspend, so nothing else ever gets a
turn.

---

## The client matters too

Both sides have to cooperate. Drop `spawn` in the client:

<CodeBlock code={
`    for var i: int = 0 to 4 {
        fetch(i, t0)             /; sequential: waits for each reply
    }`} language="fg"/>

```
request 0  finished at 1004 ms
request 1  finished at 2005 ms
request 2  finished at 3007 ms
request 3  finished at 4009 ms
request 4  finished at 5009 ms
```

Five seconds again — even though the server is perfectly concurrent. A
sequential client cannot have two requests in flight, so there is nothing for
the server to overlap.

---

## Why one thread is enough

`sys::sleep(1000)` inside a task **suspends that task**; it does not block the
thread. While one handler waits out its second, the scheduler runs the others.
Five handlers sleeping at the same time still cost one thread.

The same is true of a socket read. That is why the numbers above are ~1002 ms
and not 5×1000 ms, with no thread pool anywhere.

Because tasks are cooperative, a switch happens **only** where you suspend — a
`sys::sleep`, a `sys::yield`, or an I/O wait. Two handlers can never be inside
the same function at the same instant, so shared state needs no lock:

<CodeBlock code={
`var hits: int = 0

fun handler(res: vortex::Response) -> nthg {
    hits = hits + 1              /; safe. no lock needed.
    sys::sleep(1000)
    res.status(200).send("ok\\n")
}
`} language="fg"/>

---

## Troubleshooting

**Every request returns `ok=false` immediately (0 ms)**
Nothing is listening. Check the port matches on both sides, and that the port
is free:

```bash
lsof -nP -iTCP:8190 -sTCP:LISTEN
```

An old server from a previous run is the usual culprit. The server prints
`Vortex failed to bind to port 8190` when that happens — but only if you check
`Err::isErr(err)` **before** printing your "listening" message.

**Every request takes 30 seconds, then `ok=false`**
You have shape B or C: the accept loop is at the top level with a spawned
handler. Move the loop into a task.

**`ok=false` but a body did arrive**
The server answered, just not with a 2xx. A `404` looks the same as a
connection failure through `isOk()` — print the body to tell them apart.

**I get one more request than I asked for**
`for var i: int = 0 to 5` is **inclusive** — that is six iterations. Use
`0 to 4` for five.

**`isOk()` returns nonsense**
Read it **before** `close()`. `close()` releases the request.

---

## See also

- *[HTTP server (Vortex)](./Creating%20a%20Server.md)* — the full server API
- *Advanced → Concurrency with spawn* — the language rules for `spawn`,
  including how arguments are copied
- *Under the Hood → Concurrency and the Event Loop* — what `accept()` does when
  it suspends
