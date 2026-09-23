// Runs a compiled program in a Web Worker (static/playground/worker.js) and
// reports what it does. Returns a function that stops it.

export type RunEvent =
  | { type: "output"; fd: 1 | 2; text: string }
  | { type: "exit"; code: number }
  | { type: "crash"; message: string };

export function runProgram(
  workerUrl: string,
  program: { js: string; wasm: ArrayBuffer },
  input: string,
  onEvent: (event: RunEvent) => void,
): () => void {
  const worker = new Worker(workerUrl);
  let finished = false;
  const stop = () => {
    finished = true;
    worker.terminate();
  };

  worker.onmessage = ({ data }: MessageEvent<RunEvent>) => {
    if (finished) {
      return;
    }
    if (data.type !== "output") {
      stop();
    }
    onEvent(data);
  };
  worker.onerror = (event) => {
    event.preventDefault();
    if (finished) {
      return;
    }
    stop();
    onEvent({
      type: "crash",
      message: event.message || "The program could not be started.",
    });
  };

  worker.postMessage({ js: program.js, wasm: program.wasm, input });
  return stop;
}
