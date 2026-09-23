// The playground: edit Flow-Wing, watch the compiler work on it, run it.
//
//   every edit ─▶ FrontendAnalyzer (in the browser)   tokens, syntax tree,
//                  frontend.ts                         semantic tree, problems
//
//   Run, browser mode ─▶ server /compile?target=wasm32 ─▶ runProgram (Web Worker)
//                         server.ts                         runner.ts
//   Run, server mode  ─▶ server /run: compiled and run natively on the server
//
//   LLVM IR tab       ─▶ server /compile (either target), when not current
//
// Only the latest run may touch the page; starting another, or Stop, ends the
// one before. Every step is written to the Logs tab.

import React, { useCallback, useEffect, useMemo, useRef, useState } from "react";
import useBaseUrl from "@docusaurus/useBaseUrl";
import useDocusaurusContext from "@docusaurus/useDocusaurusContext";
import Editor, { type EditorHandle, type LineMark } from "./Editor";
import { EXAMPLES } from "./examples";
import { FrontendAnalyzer, type Analysis, type StageResult } from "./frontend";
import { PlaygroundServer, ServerUnreachable, type Build, type Exchange, type Target } from "./server";
import { runProgram } from "./runner";
import { parseDiagnostics } from "./diagnostics";
import { SourceMap, type Range } from "./source";
import { decodeSource, encodeSource, sourceFromHash } from "./share";
import Pipeline, { panelId, tabId, type StageState, type Tab, type TabId } from "./Pipeline";
import TreeView, { countNodes } from "./TreeView";
import TokensView from "./TokensView";
import SemanticView from "./SemanticView";
import CodeView, { formatBytes } from "./CodeView";
import WasmView from "./WasmView";
import {
  appendChunks, LogsPanel, OutputPanel, ProblemsPanel,
  type Chunk, type LogEntry, type LogLevel, type SourcedProblem,
} from "./Panels";
import styles from "./Playground.module.css";

// A program that prints forever would otherwise grow the page until the tab
// runs out of memory. About 5000 lines; at 1 MB a flood stalled the page for
// over half a second while it rendered.
const OUTPUT_LIMIT = 256 * 1024;
const ANALYSIS_DELAY_MS = 250;
const LOG_LIMIT = 500;
const STORAGE = "flowwing.playground";

type Mode = "browser" | "server";

type BuildState =
  | { state: "idle" }
  | { state: "working"; source: string; target: Target; opt: number }
  | { state: "done"; source: string; target: Target; opt: number; build: Build }
  | { state: "error"; source: string; target: Target; opt: number; message: string };

type RunState =
  | { state: "idle" }
  | { state: "compiling" }
  | { state: "running"; mode: Mode }
  | { state: "exited"; code: number; ms: number; mode: Mode }
  | { state: "crashed" }
  | { state: "failed" }
  | { state: "stopped" };

type WatState = { state: "idle" | "loading" | "done" | "error"; text: string; truncated: boolean; error?: string; key: string };

function ms(value: number): string {
  return value < 10 ? `${value.toFixed(1)} ms` : `${Math.round(value)} ms`;
}

function stage(analysis: Analysis | null, emit: StageResult["emit"]): StageResult | undefined {
  return analysis && "stages" in analysis ? analysis.stages.find((s) => s.emit === emit) : undefined;
}

export default function Playground() {
  const { siteConfig } = useDocusaurusContext();
  const configured = siteConfig.customFields?.playgroundServerUrl as string;
  const serverUrl = useMemo(
    () => new URLSearchParams(window.location.search).get("server") || configured,
    [configured]);
  const server = useMemo(() => new PlaygroundServer(serverUrl), [serverUrl]);
  const workerUrl = useBaseUrl("/playground/worker.js");
  const frontendUrl = useBaseUrl("/playground/frontend-worker.js");
  const analyzer = useMemo(() => new FrontendAnalyzer(frontendUrl), [frontendUrl]);
  useEffect(() => () => analyzer.dispose(), [analyzer]);

  const editor = useRef<EditorHandle>(null);

  // ---- settings, kept between visits ----
  const saved = useMemo(() => {
    try {
      return JSON.parse(localStorage.getItem(STORAGE) ?? "{}");
    } catch {
      return {};
    }
  }, []);
  const [source, setSource] = useState<string>(saved.source ?? EXAMPLES[0].source);
  const [input, setInput] = useState<string>(saved.input ?? "");
  const [mode, setMode] = useState<Mode>(saved.mode === "server" ? "server" : "browser");
  const [opt, setOpt] = useState<number>([0, 1, 2, 3].includes(saved.opt) ? saved.opt : 0);
  const [tab, setTab] = useState<TabId>("output");
  const [inputOpen, setInputOpen] = useState<boolean>(Boolean(saved.input));

  useEffect(() => {
    const timer = setTimeout(() => {
      localStorage.setItem(STORAGE, JSON.stringify({ source, input, mode, opt }));
    }, 400);
    return () => clearTimeout(timer);
  }, [source, input, mode, opt]);

  // ---- logs ----
  const [logs, setLogs] = useState<LogEntry[]>([]);
  const log = useCallback((level: LogLevel, from: string, text: string) => {
    setLogs((entries) => [...entries.slice(-(LOG_LIMIT - 1)), { at: Date.now(), level, source: from, text }]);
  }, []);

  // A shared link wins over the saved program.
  useEffect(() => {
    const data = sourceFromHash(window.location.hash);
    if (!data) return;
    decodeSource(data).then((shared) => {
      if (shared !== null) {
        setSource(shared);
        log("info", "page", "Opened the program from the link.");
      } else {
        log("warn", "page", "The link's program could not be read; kept the last one.");
      }
    });
  }, [log]);

  // ---- live analysis ----
  const [analysis, setAnalysis] = useState<Analysis | null>(null);
  const lastOutcome = useRef("");
  useEffect(() => {
    const timer = setTimeout(() => {
      const started = performance.now();
      analyzer.analyse(source, mode === "browser" ? "wasm32" : "native").then((result) => {
        if (!result) return; // replaced by a newer edit
        setAnalysis(result);
        // Logged when the outcome changes, not on every keystroke.
        let outcome: string;
        let level: LogLevel;
        let timing = "";
        if ("unavailable" in result) {
          outcome = `Live analysis unavailable: ${result.unavailable}`;
          level = "warn";
        } else {
          const failed = result.stages.find((s) => !s.ok);
          const total = result.stages.reduce((sum, s) => sum + s.ms, 0);
          timing = ` (${result.stages.map((s) => `${s.emit} ${ms(s.ms)}`).join(", ")}; ` +
            `${ms(total)} in the compiler, ${ms(performance.now() - started)} round trip)`;
          if (failed) {
            const first = parseDiagnostics(failed.output)[0];
            outcome = `${{ tokens: "Lexer", ast: "Parser", sem: "Semantic analysis" }[failed.emit]} ` +
              `found a problem: ${first?.message ?? "see Problems"}`;
            level = "error";
          } else {
            outcome = "Program checks out: lexer, parser and semantic analysis passed.";
            level = "ok";
          }
        }
        if (outcome !== lastOutcome.current) {
          lastOutcome.current = outcome;
          log(level, "front end", outcome + timing);
        }
      });
    }, ANALYSIS_DELAY_MS);
    return () => clearTimeout(timer);
  }, [source, mode, analyzer, log]);

  const current = analysis?.source === source ? analysis : null;
  const map = useMemo(() => new SourceMap(source), [source]);
  // Trees and tokens stay on screen while the next analysis runs; ranges into
  // an older text are resolved against that text.
  const shownMap = useMemo(
    () => (analysis && analysis.source !== source ? new SourceMap(analysis.source) : map),
    [analysis, source, map]);

  // ---- build (server /compile) ----
  const [build, setBuild] = useState<BuildState>({ state: "idle" });
  const buildAbort = useRef<AbortController | null>(null);

  const compile = useCallback(async (target: Target, signal: AbortSignal): Promise<Exchange<Build> | null> => {
    setBuild({ state: "working", source, target, opt });
    log("info", "server", `POST /compile target=${target} -O${opt} → ${server.host}`);
    try {
      const exchange = await server.compile(source, { target, opt }, signal);
      const b = exchange.value;
      setBuild({ state: "done", source, target, opt, build: b });
      const steps = b.log.filter((s) => s.ms !== undefined).map((s) => `${s.step} ${ms(s.ms!)}`).join(", ");
      const sizes = b.log.find((s) => s.step === "sizes");
      log(b.ok ? "ok" : "error", "server",
        `${exchange.status} in ${ms(exchange.ms)}, ${formatBytes(exchange.bytes)}` +
        (b.compiler ? ` · ${b.compiler}` : "") +
        (steps ? ` · ${steps}` : "") +
        (sizes ? ` · main.wasm ${formatBytes(sizes.wasm!)}, main.js ${formatBytes(sizes.js!)}` : "") +
        (b.ok ? "" : ` · stopped at ${b.stage}`));
      return exchange;
    } catch (error) {
      if (signal.aborted) return null;
      const message = error instanceof ServerUnreachable ? error.message : String(error);
      setBuild({ state: "error", source, target, opt, message });
      log("error", "server", message);
      return null;
    }
  }, [source, opt, server, log]);

  const buildTarget: Target = mode === "browser" ? "wasm32" : "native";
  const buildIsCurrent = build.state !== "idle" && build.source === source &&
    build.opt === opt && build.target === buildTarget;

  const rebuild = () => {
    buildAbort.current?.abort();
    const abort = new AbortController();
    buildAbort.current = abort;
    compile(buildTarget, abort.signal);
  };

  // Opening the IR or WebAssembly tab, or changing the mode or -O while on
  // one, builds the program if what is shown is not current. Not on every
  // edit: that would be a server compile per keystroke.
  const latest = useRef({ buildIsCurrent, working: build.state === "working", rebuild });
  latest.current = { buildIsCurrent, working: build.state === "working", rebuild };
  useEffect(() => {
    const wanted = tab === "ir" || (tab === "wasm" && mode === "browser");
    if (wanted && !latest.current.buildIsCurrent && !latest.current.working) latest.current.rebuild();
  }, [tab, mode, opt]);

  // ---- WebAssembly text format ----
  const [wat, setWat] = useState<WatState>({ state: "idle", text: "", truncated: false, key: "" });
  const watKey = `${opt}\n${source}`;
  const requestWat = async () => {
    setWat({ state: "loading", text: "", truncated: false, key: watKey });
    log("info", "server", `POST /compile target=wasm32 -O${opt} wat → ${server.host}`);
    try {
      const exchange = await server.compile(source, { target: "wasm32", opt, wat: true }, new AbortController().signal);
      const b = exchange.value;
      if (b.ok && b.wat) {
        setWat({ state: "done", text: b.wat, truncated: b.watTruncated, key: watKey });
        log("ok", "server", `${exchange.status} in ${ms(exchange.ms)} · WAT ${formatBytes(b.wat.length)}`);
      } else {
        setWat({ state: "error", text: "", truncated: false, key: watKey, error: "The server did not return the text format." });
        log("error", "server", `WAT not returned (${exchange.status}, stopped at ${b.stage})`);
      }
    } catch (error) {
      const message = error instanceof ServerUnreachable ? error.message : String(error);
      setWat({ state: "error", text: "", truncated: false, key: watKey, error: message });
      log("error", "server", message);
    }
  };
  const shownWat = wat.key === watKey ? wat : { ...wat, state: "idle" as const };

  // ---- run ----
  const [run, setRun] = useState<RunState>({ state: "idle" });
  const [chunks, setChunks] = useState<Chunk[]>([]);
  const currentRun = useRef(0);
  const stopCurrent = useRef<() => void>(() => {});
  const running = run.state === "compiling" || run.state === "running";

  const stop = () => {
    stopCurrent.current();
    currentRun.current++;
    setRun({ state: "stopped" });
    log("warn", "page", "Stopped.");
  };

  const start = async () => {
    stopCurrent.current();
    const runId = ++currentRun.current;
    const isCurrent = () => runId === currentRun.current;
    setTab("output");

    // A program can print thousands of lines a second. They reach the page at
    // most once per frame; one render per line stalled the tab long before
    // OUTPUT_LIMIT was reached.
    let pending: Chunk[] = [];
    let frame = 0;
    const flush = () => {
      frame = 0;
      const batch = pending;
      pending = [];
      if (isCurrent()) setChunks((existing) => appendChunks(existing, batch));
    };
    const append = (chunk: Chunk) => {
      pending.push(chunk);
      if (!frame) frame = requestAnimationFrame(flush);
    };
    setChunks([]);

    const abort = new AbortController();
    stopCurrent.current = () => abort.abort();
    buildAbort.current?.abort();

    if (mode === "server") {
      setRun({ state: "running", mode });
      log("info", "server", `POST /run → ${server.host} (compiled and run natively, time limit 20 s)`);
      try {
        const { value, status, ms: took } = await server.run(source, input, abort.signal);
        if (!isCurrent()) return;
        append({ stream: "stdout", text: value.output });
        if (value.exitCode === 124) append({ stream: "notice", text: "\n[Stopped: the program ran longer than the server's 20 s limit.]\n" });
        if (value.exitCode === 137) append({ stream: "notice", text: "\n[Killed: the program went over the server's memory limit.]\n" });
        setRun({ state: "exited", code: value.exitCode, ms: took, mode });
        log(value.exitCode === 0 ? "ok" : "error", "server",
          `${status} in ${ms(took)} · exit code ${value.exitCode} · ${formatBytes(value.output.length)} of output`);
      } catch (error) {
        if (!isCurrent() || abort.signal.aborted) return;
        const message = error instanceof ServerUnreachable ? error.message : String(error);
        append({ stream: "stderr", text: message + "\n" });
        setRun({ state: "failed" });
        log("error", "server", message);
      }
      return;
    }

    setRun({ state: "compiling" });
    const exchange = await compile("wasm32", abort.signal);
    if (!isCurrent() || !exchange) {
      if (isCurrent()) {
        append({ stream: "stderr", text: `Could not reach the Flow-Wing server at ${server.host}.\n` });
        setRun({ state: "failed" });
      }
      return;
    }
    const result = exchange.value;
    if (!result.ok || !result.wasm) {
      append({ stream: "diagnostics", text: result.diagnostics });
      setRun({ state: "failed" });
      return;
    }

    const started = performance.now();
    let printed = 0;
    setRun({ state: "running", mode });
    log("info", "browser", "Running main.wasm in a Web Worker.");
    stopCurrent.current = runProgram(workerUrl, { js: result.js, wasm: result.wasm }, input, (event) => {
      if (!isCurrent()) return;
      if (event.type === "output") {
        printed += event.text.length;
        if (printed > OUTPUT_LIMIT) {
          stopCurrent.current();
          append({ stream: "notice", text: "\n[Stopped: the program printed more than 256 KB.]\n" });
          setRun({ state: "stopped" });
          log("warn", "browser", "Stopped: more than 256 KB of output.");
          return;
        }
        append({ stream: event.fd === 1 ? "stdout" : "stderr", text: event.text });
      } else if (event.type === "exit") {
        const took = performance.now() - started;
        setRun({ state: "exited", code: event.code, ms: took, mode });
        log(event.code === 0 ? "ok" : "error", "browser", `Exited with code ${event.code} after ${ms(took)}.`);
      } else {
        append({ stream: "stderr", text: `\n${event.message}\n` });
        setRun({ state: "crashed" });
        log("error", "browser", `Crashed: ${event.message}`);
      }
    });
  };

  // ---- problems ----
  const problems = useMemo<SourcedProblem[]>(() => {
    const found: SourcedProblem[] = [];
    const failed = current && "stages" in current ? current.stages.find((s) => !s.ok) : undefined;
    if (failed) {
      for (const problem of parseDiagnostics(failed.output)) found.push({ ...problem, from: "live check" });
    }
    // The server's own errors, unless they repeat what the live check found.
    if (build.state === "done" && build.source === source && !build.build.ok &&
        !(failed && build.build.stage === "compile")) {
      const code = build.build.stage === "link" ? "LinkError" : "ServerError";
      for (const problem of parseDiagnostics(build.build.diagnostics, code)) found.push({ ...problem, from: "server" });
    }
    return found;
  }, [current, build, source]);

  const marks = useMemo<LineMark[]>(
    () => problems.filter((p) => p.at).map((p) => ({ line: p.at![0], severity: p.severity, message: p.message })),
    [problems]);

  // ---- highlight: what a token, node or problem stands for ----
  const [picked, setPicked] = useState<Range | null>(null);
  const [hovered, setHovered] = useState<Range | null>(null);
  useEffect(() => setPicked(null), [source]);
  const shown = hovered ?? picked;
  const highlight = useMemo(
    () => (shown && (!analysis || analysis.source === source) ? map.span(shown) : null),
    [shown, analysis, source, map]);

  const pick = useCallback((range: Range) => {
    setPicked(range);
    if (!analysis || analysis.source === source) editor.current?.reveal(map.span(range));
  }, [analysis, source, map]);

  const pickProblem = (problem: SourcedProblem) => {
    if (!problem.at) return;
    // The token that starts there, if the lexer got that far.
    const tokens = stage(current, "tokens")?.json?.tokens ?? [];
    const token = tokens.find((t: any) => t.range.start[0] === problem.at![0] && t.range.start[1] === problem.at![1]);
    pick(token?.range ?? { start: problem.at, end: [problem.at[0], problem.at[1] + 1] });
    editor.current?.focus();
  };

  // ---- the pipeline's tabs ----
  const tokensStage = stage(analysis, "tokens");
  const astStage = stage(analysis, "ast");
  const semStage = stage(analysis, "sem");
  const unavailable = analysis && "unavailable" in analysis ? analysis.unavailable : null;
  const analysing = !current && !unavailable;

  const frontTab = (id: TabId, label: string, result: StageResult | undefined, detail: (r: StageResult) => string,
                    previousFailed: boolean): Tab => {
    let state: StageState;
    let text = "";
    if (unavailable) {
      state = "skipped";
      text = "offline";
    } else if (analysing && !result) {
      state = "working";
    } else if (!result) {
      state = previousFailed ? "idle" : "working";
      text = previousFailed ? "not reached" : "";
    } else if (result.ok) {
      state = analysing ? "stale" : "ok";
      text = detail(result);
    } else {
      state = "error";
      text = "error";
    }
    return { id, label, state, detail: text, stage: true };
  };

  const irTab = (): Tab => {
    if (build.state === "working") return { id: "ir", label: "LLVM IR", state: "working", detail: "compiling", stage: true };
    if (build.state === "error") return { id: "ir", label: "LLVM IR", state: "error", detail: "no server", stage: true };
    if (build.state === "done") {
      const b = build.build;
      const state: StageState = b.ir ? (buildIsCurrent ? "ok" : "stale") : "error";
      return { id: "ir", label: "LLVM IR", state, detail: b.ir ? `${formatBytes(b.ir.length)} · ${build.target}` : "error", stage: true };
    }
    return { id: "ir", label: "LLVM IR", state: "idle", detail: "on the server", stage: true };
  };

  const wasmTab = (): Tab => {
    if (mode === "server") return { id: "wasm", label: "WebAssembly", state: "skipped", detail: "native run", stage: true };
    if (build.state === "working" && build.target === "wasm32") {
      return { id: "wasm", label: "WebAssembly", state: "working", detail: "linking", stage: true };
    }
    if (build.state === "done" && build.target === "wasm32") {
      const b = build.build;
      if (b.wasm) {
        return { id: "wasm", label: "WebAssembly", state: buildIsCurrent ? "ok" : "stale", detail: formatBytes(b.wasm.byteLength), stage: true };
      }
      if (b.stage !== "compile") return { id: "wasm", label: "WebAssembly", state: "error", detail: "link failed", stage: true };
    }
    return { id: "wasm", label: "WebAssembly", state: "idle", detail: "", stage: true };
  };

  const outputTab = (): Tab => {
    switch (run.state) {
      case "compiling": return { id: "output", label: "Output", state: "working", detail: "compiling", stage: true };
      case "running": return { id: "output", label: "Output", state: "working", detail: run.mode === "server" ? "on the server" : "running", stage: true };
      case "exited": return { id: "output", label: "Output", state: run.code === 0 ? "ok" : "error", detail: `exit ${run.code} · ${ms(run.ms)}`, stage: true };
      case "crashed": return { id: "output", label: "Output", state: "error", detail: "crashed", stage: true };
      case "failed": return { id: "output", label: "Output", state: "error", detail: "not run", stage: true };
      case "stopped": return { id: "output", label: "Output", state: "idle", detail: "stopped", stage: true };
      default: return { id: "output", label: "Output", state: "idle", detail: "Ctrl+Enter", stage: true };
    }
  };

  const errors = problems.filter((p) => p.severity === "error").length;
  const tabs: Tab[] = [
    frontTab("tokens", "Tokens", tokensStage, (r) => `${r.json?.tokens?.length ?? 0} · ${ms(r.ms)}`, false),
    frontTab("ast", "Syntax tree", astStage, (r) => `${countNodes(r.json?.tree)} nodes`, tokensStage ? !tokensStage.ok : false),
    frontTab("sem", "Semantic tree", semStage, (r) => `${Object.keys(r.json?.sem?.symbols ?? {}).length} symbols`,
      (tokensStage ? !tokensStage.ok : false) || (astStage ? !astStage.ok : false)),
    irTab(),
    wasmTab(),
    outputTab(),
    { id: "problems", label: "Problems", state: errors ? "error" : problems.length ? "stale" : "ok", detail: String(problems.length), stage: false },
    { id: "logs", label: "Logs", state: "idle", detail: String(logs.length), stage: false },
  ];

  // ---- share ----
  const [shared, setShared] = useState("");
  const share = async () => {
    const url = `${window.location.origin}${window.location.pathname}${window.location.search}#code=${await encodeSource(source)}`;
    window.history.replaceState(null, "", url);
    try {
      await navigator.clipboard.writeText(url);
      setShared("Link copied");
    } catch {
      setShared("Link is in the address bar");
    }
    log("info", "page", `Share link made (${formatBytes(url.length)}).`);
    setTimeout(() => setShared(""), 2500);
  };

  // ---- panels ----
  const notAvailable = (what: string) => (
    <p className={styles.empty}>
      {unavailable
        ? <>Live analysis is not available ({unavailable}). Programs still compile and run on the server.</>
        : <>{what}</>}
    </p>
  );

  const stageFailure = () => (
    <div className={styles.empty}>
      <p>This stage found a problem, so there is nothing to show.</p>
      <button type="button" className={styles.miniButton} onClick={() => setTab("problems")}>Show problems</button>
    </div>
  );

  let panel: React.ReactNode;
  switch (tab) {
    case "tokens":
      panel = !tokensStage ? notAvailable("Reading the program…")
        : tokensStage.ok
          ? <TokensView tokens={tokensStage.json.tokens} map={shownMap} onPick={pick} onHover={setHovered} />
          : stageFailure();
      break;
    case "ast":
      panel = !astStage ? notAvailable(tokensStage && !tokensStage.ok ? "The lexer found a problem first." : "Parsing…")
        : astStage.ok
          ? <TreeView root={astStage.json.tree} map={shownMap} label="Syntax tree" onPick={pick} onHover={setHovered} />
          : stageFailure();
      break;
    case "sem":
      panel = !semStage ? notAvailable("An earlier stage found a problem first.")
        : semStage.ok
          ? <SemanticView sem={semStage.json.sem} map={shownMap} onPick={pick} onHover={setHovered} />
          : stageFailure();
      break;
    case "ir":
      panel = build.state === "done" && build.build.ir
        ? (
          <>
            {!buildIsCurrent && (
              <p className={styles.stale}>
                This IR is for an earlier version of the program.{" "}
                <button type="button" className={styles.miniButton} onClick={rebuild}>Compile again</button>
              </p>
            )}
            <p className={styles.explain}>
              {build.target === "wasm32" ? "For WebAssembly (wasm32): pointers are 4 bytes." : "For the server's own machine (native)."}{" "}
              As IR generation made it, before the optimiser runs (-O changes the WebAssembly, not this).
              Only your program's own module: the modules it brings are compiled separately.
            </p>
            <CodeView text={build.build.ir} language="llvm" fileName="main.ll" />
          </>
        )
        : build.state === "done"
          ? <p className={styles.empty}>No IR: the program did not compile. See Problems.</p>
          : build.state === "error"
            ? <p className={styles.empty}>{build.message}</p>
            : <p className={styles.empty}>Compiling on the server…</p>;
      break;
    case "wasm":
      panel = mode === "server"
        ? <p className={styles.empty}>In server mode the program is compiled for the server's own machine, not WebAssembly. Switch to “Run in browser” to see the module.</p>
        : build.state === "done" && build.target === "wasm32" && build.build.wasm
          ? (
            <>
              {!buildIsCurrent && (
                <p className={styles.stale}>
                  This module is from an earlier version of the program.{" "}
                  <button type="button" className={styles.miniButton} onClick={rebuild}>Build again</button>
                </p>
              )}
              <WasmView wasm={build.build.wasm} js={build.build.js} wat={shownWat} onRequestWat={requestWat} />
            </>
          )
          : build.state === "error"
            ? <p className={styles.empty}>{build.message}</p>
            : build.state === "done"
              ? <p className={styles.empty}>No module: the program did not build. See Problems.</p>
              : <p className={styles.empty}>Building on the server…</p>;
      break;
    case "output": {
      let footer = "";
      if (run.state === "exited") {
        footer = `Exited with code ${run.code} · ${ms(run.ms)} · ${run.mode === "server" ? "ran natively on the server" : "ran as WebAssembly in your browser"}`;
      } else if (run.state === "failed") footer = "Did not run.";
      else if (run.state === "crashed") footer = "Crashed.";
      panel = <OutputPanel chunks={chunks} footer={footer} />;
      break;
    }
    case "problems":
      panel = <ProblemsPanel problems={problems} map={map} onPick={pickProblem} />;
      break;
    case "logs":
      panel = <LogsPanel entries={logs} onClear={() => setLogs([])} />;
      break;
  }

  const compilerVersion = build.state === "done" ? build.build.compiler : "";

  return (
    <div className={styles.workbench}>
      <div className={styles.toolbar}>
        <label className={styles.control}>
          <span className={styles.controlLabel}>Example</span>
          <select
            className={styles.select}
            defaultValue=""
            onChange={(event) => {
              const example = EXAMPLES[Number(event.target.value)];
              if (example) {
                setSource(example.source);
                log("info", "page", `Loaded the “${example.title}” example.`);
              }
              event.target.value = "";
            }}
          >
            <option value="" disabled>Choose…</option>
            {EXAMPLES.map((example, index) => (
              <option key={example.title} value={index}>{example.title}</option>
            ))}
          </select>
        </label>

        <div className={styles.segmented} role="radiogroup" aria-label="Where the program runs">
          {([
            ["browser", "Run in browser", "Compiled to WebAssembly on the server, run here in your browser"],
            ["server", "Run on server", "Compiled and run natively on the Flow-Wing server, in a sandbox"],
          ] as [Mode, string, string][]).map(([id, label, title]) => (
            <button
              key={id}
              type="button"
              role="radio"
              aria-checked={mode === id}
              title={title}
              className={mode === id ? styles.segmentOn : styles.segment}
              onClick={() => {
                setMode(id);
                log("info", "page", `Mode: ${label.toLowerCase()}.`);
              }}
            >
              {label}
            </button>
          ))}
        </div>

        <label className={styles.control} title="Optimisation level for the WebAssembly build">
          <span className={styles.controlLabel}>Opt</span>
          <select className={styles.select} value={opt} onChange={(event) => setOpt(Number(event.target.value))}>
            {[0, 1, 2, 3].map((level) => <option key={level} value={level}>-O{level}</option>)}
          </select>
        </label>

        <span className={styles.spacer} />

        <button type="button" className={styles.ghostButton} onClick={share}>
          {shared || "Share"}
        </button>
        <button type="button" className={styles.ghostButton} onClick={stop} disabled={!running}>
          Stop
        </button>
        <button type="button" className={styles.runButton} onClick={start} title="Ctrl+Enter">
          <span aria-hidden="true">▶</span> Run
        </button>
      </div>

      <Pipeline tabs={tabs} selected={tab} onSelect={setTab} />

      <div className={styles.body}>
        <div className={styles.left}>
          <Editor
            ref={editor}
            value={source}
            onChange={setSource}
            onRun={start}
            marks={marks}
            highlight={highlight}
          />
          <div className={styles.stdin}>
            <button
              type="button"
              className={styles.stdinToggle}
              aria-expanded={inputOpen}
              onClick={() => setInputOpen(!inputOpen)}
            >
              {inputOpen ? "▾" : "▸"} Input <span className={styles.muted}>(standard input{input ? `, ${input.split("\n").length} lines` : ""})</span>
            </button>
            {inputOpen && (
              <textarea
                className={styles.stdinBox}
                value={input}
                onChange={(event) => setInput(event.target.value)}
                placeholder="What the program reads with io::readLine(), one line per line."
                aria-label="Standard input"
                spellCheck={false}
              />
            )}
          </div>
        </div>

        <div className={styles.panel} role="tabpanel" id={panelId(tab)} aria-labelledby={tabId(tab)}>
          {panel}
        </div>
      </div>

      <div className={styles.statusbar} role="status">
        <span className={unavailable ? styles.statusOff : styles.statusOn}>
          Live check {unavailable ? "offline" : "on"}
        </span>
        <span>Server <code>{server.host}</code></span>
        {compilerVersion && <span>{compilerVersion}</span>}
        <span className={styles.spacer} />
        <span>
          {run.state === "compiling" ? "Compiling…"
            : run.state === "running" ? (run.mode === "server" ? "Running on the server…" : "Running…")
            : errors ? `${errors} problem${errors > 1 ? "s" : ""}` : "Ready"}
        </span>
      </div>
    </div>
  );
}
