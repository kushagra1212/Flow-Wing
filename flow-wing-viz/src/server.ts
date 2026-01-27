import { join } from "path";
import { serve, file } from "bun";
import { writeFile, readFile, unlink } from "fs/promises";
import { existsSync, readdirSync } from "fs";

// Helper function to strip ANSI escape codes
function stripAnsiCodes(text: string): string {
  // Remove ANSI escape sequences (CSI sequences, color codes, etc.)
  return text
    .replace(/\x1b\[[0-9;]*[a-zA-Z]/g, "")
    .replace(/\x1b\]8;;.*?\x1b\\/g, "");
}

// Helper function to read all data from a stream
async function readStream(stream: ReadableStream<Uint8Array>): Promise<string> {
  const reader = stream.getReader();
  const chunks: Uint8Array[] = [];
  let totalBytes = 0;

  try {
    while (true) {
      const { done, value } = await reader.read();
      if (done) {
        // Stream is closed, but check if there's any remaining data
        break;
      }
      if (value && value.length > 0) {
        chunks.push(value);
        totalBytes += value.length;
      }
    }
  } catch (error) {
    // If there's an error reading, try to return what we have so far
    console.error("Error reading stream:", error);
  } finally {
    try {
      reader.releaseLock();
    } catch (e) {
      // Ignore errors releasing lock
    }
  }

  // Combine all chunks
  if (chunks.length === 0) return "";

  const result = new Uint8Array(totalBytes);
  let offset = 0;
  for (const chunk of chunks) {
    result.set(chunk, offset);
    offset += chunk.length;
  }

  const text = new TextDecoder("utf-8", { fatal: false }).decode(result);
  // Strip ANSI codes for cleaner output
  return stripAnsiCodes(text);
}

// CONFIG: Adjust path relative to where you run this script
const BUILD_DIR = join(process.cwd(), "../build");
const PUBLIC_DIR = join(process.cwd(), "public");
const SOURCE_FILE = join(process.cwd(), "../tests/local/dyn.fg");
const TEMP_SOURCE_FILE = join(BUILD_DIR, "temp_source.fg");
const LOGS_FILE = join(BUILD_DIR, "compiler_logs.txt");

// Store compilation logs in memory for quick access
let compilationLogs = "";

// Helper function to delete old compilation artifacts
async function deleteOldArtifacts() {
  const artifacts = [
    "tokens.json",
    "ast.json",
    "semantic_tree.json",
    "llvm_ir.ll",
    "compiler_logs.txt",
  ];

  for (const artifact of artifacts) {
    const filePath = join(BUILD_DIR, artifact);
    try {
      if (existsSync(filePath)) {
        await unlink(filePath);
        console.log(`Deleted old artifact: ${artifact}`);
      }
    } catch (error) {
      // Ignore errors deleting files (they might not exist)
      console.warn(`Could not delete ${artifact}:`, error);
    }
  }
  
  // Also clear in-memory logs
  compilationLogs = "";
}

const server = serve({
  port: 3000,
  async fetch(req) {
    const url = new URL(req.url);

    // 1. API: Serve Source File
    if (url.pathname === "/api/source") {
      const sourceFile = file(SOURCE_FILE);
      if (await sourceFile.exists()) {
        return new Response(sourceFile, {
          headers: {
            "Content-Type": "text/plain",
            "Access-Control-Allow-Origin": "*",
          },
        });
      }
      return new Response(JSON.stringify({ error: "Source file not found" }), {
        status: 404,
        headers: { "Content-Type": "application/json" },
      });
    }

    // 2.1 API: Clear old artifacts
    if (url.pathname === "/api/clear-artifacts" && req.method === "POST") {
      try {
        await deleteOldArtifacts();
        return new Response(
          JSON.stringify({ success: true, message: "Artifacts cleared" }),
          {
            headers: {
              "Content-Type": "application/json",
              "Access-Control-Allow-Origin": "*",
            },
          }
        );
      } catch (error: any) {
        return new Response(JSON.stringify({ error: error.message }), {
          status: 500,
          headers: { "Content-Type": "application/json" },
        });
      }
    }

    // 2. API: Save source code
    if (url.pathname === "/api/save-source" && req.method === "POST") {
      try {
        const body = await req.json();
        const code = body.code || "";
        await writeFile(TEMP_SOURCE_FILE, code, "utf-8");
        return new Response(
          JSON.stringify({ success: true, message: "Code saved" }),
          {
            headers: {
              "Content-Type": "application/json",
              "Access-Control-Allow-Origin": "*",
            },
          }
        );
      } catch (error: any) {
        return new Response(JSON.stringify({ error: error.message }), {
          status: 500,
          headers: { "Content-Type": "application/json" },
        });
      }
    }

    // 3. API: Compile and generate artifacts
    if (url.pathname === "/api/compile" && req.method === "POST") {
      try {
        const body = await req.json();
        const binaryPath = body.binaryPath;
        if (!binaryPath) {
          return new Response(
            JSON.stringify({ error: "Binary path not provided" }),
            { status: 400, headers: { "Content-Type": "application/json" } }
          );
        }

        const sourceFile = TEMP_SOURCE_FILE;
        if (!existsSync(sourceFile)) {
          return new Response(
            JSON.stringify({ error: "Source file not found" }),
            { status: 404, headers: { "Content-Type": "application/json" } }
          );
        }

        // Delete old artifacts before starting new compilation
        await deleteOldArtifacts();

        // Run compilation commands
        const commands = [
          { emit: "tokens", output: "tokens.json" },
          { emit: "ast", output: "ast.json" },
          { emit: "sem", output: "semantic_tree.json" },
          { emit: "ir", output: "llvm_ir.ll" },
        ];

        const results = [];
        let allLogs = "";
        
        for (const cmd of commands) {
          const proc = Bun.spawn(
            [binaryPath, sourceFile, `--emit=${cmd.emit}`, `-OD=${BUILD_DIR}`],
            {
              stdout: "pipe",
              stderr: "pipe",
            }
          );

          // Read streams concurrently while process runs, then wait for process to exit
          // This ensures we capture all output even if process exits quickly
          const stdoutPromise = readStream(proc.stdout);
          const stderrPromise = readStream(proc.stderr);
          const exitCodePromise = proc.exited;

          // Wait for all to complete - streams will finish reading when process exits
          const [text, error, exitCode] = await Promise.all([
            stdoutPromise,
            stderrPromise,
            exitCodePromise,
          ]);

          // Collect logs from stdout and stderr (debug logs go to stdout)
          if (text) allLogs += text;
          if (error) allLogs += error;

          results.push({
            emit: cmd.emit,
            success: exitCode === 0,
            stdout: text,
            stderr: error,
            exitCode,
          });
        }

        // Store logs in memory and save to file
        compilationLogs = allLogs;
        await writeFile(LOGS_FILE, allLogs, "utf-8");

        return new Response(JSON.stringify({ success: true, results }), {
          headers: {
            "Content-Type": "application/json",
            "Access-Control-Allow-Origin": "*",
          },
        });
      } catch (error: any) {
        return new Response(JSON.stringify({ error: error.message }), {
          status: 500,
          headers: { "Content-Type": "application/json" },
        });
      }
    }

    // 3.1 API: Get compilation logs
    if (url.pathname === "/api/logs") {
      // Try to read from file first, then fall back to memory
      let logs = compilationLogs;
      if (existsSync(LOGS_FILE)) {
        try {
          logs = await readFile(LOGS_FILE, "utf-8");
        } catch (e) {
          // Use in-memory logs if file read fails
        }
      }
      return new Response(JSON.stringify({ logs }), {
        headers: {
          "Content-Type": "application/json",
          "Access-Control-Allow-Origin": "*",
        },
      });
    }

    // 4. API: Run the compiled binary
    if (url.pathname === "/api/run" && req.method === "POST") {
      try {
        const body = await req.json();
        const binaryPath = body.binaryPath;
        if (!binaryPath) {
          return new Response(
            JSON.stringify({ error: "Binary path not provided" }),
            { status: 400, headers: { "Content-Type": "application/json" } }
          );
        }

        const sourceFile = TEMP_SOURCE_FILE;
        if (!existsSync(sourceFile)) {
          return new Response(
            JSON.stringify({ error: "Source file not found" }),
            { status: 404, headers: { "Content-Type": "application/json" } }
          );
        }

        // First compile to create binary (without --emit flags, this creates the executable)
        const compileProc = Bun.spawn(
          [binaryPath, sourceFile, `-OD=${BUILD_DIR}`],
          {
            cwd: BUILD_DIR,
            stdout: "pipe",
            stderr: "pipe",
          }
        );

        // Read streams concurrently while process runs, then wait for process to exit
        // This ensures we capture all output even if process exits quickly
        const compileStdoutPromise = readStream(compileProc.stdout);
        const compileErrorPromise = readStream(compileProc.stderr);
        const compileExitCodePromise = compileProc.exited;

        // Wait for all to complete - streams will finish reading when process exits
        const [compileStdout, compileError, compileExitCode] =
          await Promise.all([
            compileStdoutPromise,
            compileErrorPromise,
            compileExitCodePromise,
          ]);

        if (compileExitCode !== 0) {
          return new Response(
            JSON.stringify({
              success: false,
              error: compileError || compileStdout || "Compilation failed",
              exitCode: compileExitCode,
              stdout: compileStdout,
              stderr: compileError,
            }),
            {
              headers: {
                "Content-Type": "application/json",
                "Access-Control-Allow-Origin": "*",
              },
            }
          );
        }

        // Find the generated binary
        // The binary could be in BUILD_DIR/bin/ or BUILD_DIR/
        // Try multiple possible locations
        const sourceName =
          sourceFile.split("/").pop()?.replace(/\.fg$/, "") || "temp_source";

        const possibleBinaryPaths = [
          join(BUILD_DIR, "bin", sourceName), // Most common: build/bin/filename
          join(BUILD_DIR, sourceName), // Direct in build: build/filename
          join(BUILD_DIR, "bin", "dyn"), // Fallback to dyn
          join(BUILD_DIR, "dyn"), // Fallback to dyn in build
        ];

        // Also check if bin directory exists and list files
        const binDir = join(BUILD_DIR, "bin");
        if (existsSync(binDir)) {
          try {
            const binFiles = readdirSync(binDir);
            // Add any executable files found
            binFiles.forEach((file) => {
              const fullPath = join(binDir, file);
              if (!possibleBinaryPaths.includes(fullPath)) {
                possibleBinaryPaths.push(fullPath);
              }
            });
          } catch (err) {
            // Ignore readdir errors
          }
        }

        // Find the first existing binary
        let execBinary: string | null = null;
        for (const path of possibleBinaryPaths) {
          if (existsSync(path)) {
            execBinary = path;
            break;
          }
        }

        if (!execBinary) {
          // List available files for debugging
          let availableFiles = "";
          try {
            if (existsSync(binDir)) {
              availableFiles = `\nFiles in bin/: ${readdirSync(binDir).join(
                ", "
              )}`;
            }
            availableFiles += `\nFiles in build/: ${readdirSync(BUILD_DIR).join(
              ", "
            )}`;
          } catch (err) {
            availableFiles = "\nCould not list directory contents";
          }

          return new Response(
            JSON.stringify({
              success: false,
              error: `Compiled binary not found. Expected: ${sourceName}${availableFiles}`,
            }),
            {
              headers: {
                "Content-Type": "application/json",
                "Access-Control-Allow-Origin": "*",
              },
            }
          );
        }

        // Run the binary
        const runProc = Bun.spawn([execBinary], {
          cwd: BUILD_DIR,
          stdout: "pipe",
          stderr: "pipe",
        });

        // Read streams concurrently while process runs, then wait for process to exit
        // This ensures we capture all output even if process exits quickly
        const stdoutPromise = readStream(runProc.stdout);
        const stderrPromise = readStream(runProc.stderr);
        const exitCodePromise = runProc.exited;

        // Wait for all to complete - streams will finish reading when process exits
        const [stdout, stderr, exitCode] = await Promise.all([
          stdoutPromise,
          stderrPromise,
          exitCodePromise,
        ]);

        return new Response(
          JSON.stringify({
            success: exitCode === 0,
            stdout,
            stderr,
            exitCode,
          }),
          {
            headers: {
              "Content-Type": "application/json",
              "Access-Control-Allow-Origin": "*",
            },
          }
        );
      } catch (error: any) {
        return new Response(JSON.stringify({ error: error.message }), {
          status: 500,
          headers: { "Content-Type": "application/json" },
        });
      }
    }

    // 5. API: Serve Compiler Artifacts
    if (url.pathname.startsWith("/api/")) {
      const filename = url.pathname.replace("/api/", ""); // e.g., "ast.json"
      const filePath = join(BUILD_DIR, filename);
      const f = file(filePath);

      if (await f.exists()) {
        // Determine content type based on file extension
        let contentType = "application/json";
        if (filename.endsWith(".ll")) {
          contentType = "text/plain; charset=utf-8";
        } else if (filename.endsWith(".txt")) {
          contentType = "text/plain; charset=utf-8";
        } else if (filename.endsWith(".json")) {
          contentType = "application/json";
        }

        return new Response(f, {
          headers: {
            "Content-Type": contentType,
            "Access-Control-Allow-Origin": "*",
          },
        });
      }

      // Log for debugging
      if (filename.endsWith(".ll")) {
        console.log(`LLVM IR file not found: ${filePath}`);
      }

      return new Response(
        JSON.stringify({ error: `File ${filename} not found` }),
        { status: 404, headers: { "Content-Type": "application/json" } }
      );
    }

    // 2. Serve Static Assets
    let filePath = join(
      PUBLIC_DIR,
      url.pathname === "/" ? "index.html" : url.pathname
    );
    const staticFile = file(filePath);

    if (await staticFile.exists()) {
      return new Response(staticFile);
    }

    return new Response("Not Found", { status: 404 });
  },
});

console.log(`\n🚀 Flow-Wing Viz running at http://localhost:${server.port}`);
console.log(`📂 Watching artifacts in: ${BUILD_DIR}`);
