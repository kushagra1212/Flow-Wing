# Testing the Flow-Wing LSP

## Prerequisites (run once)

1. **Build the FlowWing compiler** (from repo root):
   ```bash
   make build-aot-debug
   ```
   This produces `build/sdk/bin/FlowWing` (use `FlowWing.exe` on Windows).

2. **Install and compile the LSP** (from repo root):
   ```bash
   cd src/lsp && yarn install && yarn compile
   ```
   This creates `client/out/` and `server/out/` with the compiled extension.

## Configure the compiler path

Set the path to the FlowWing executable in VS Code settings:

- **If FlowWing is in PATH**: Use `"FlowWing"` (default).
- **Otherwise**: Use the absolute path, e.g.:
  ```json
  "FlowWing.compilerPath": "/Users/you/code/per/Flow-Wing/build/sdk/bin/FlowWing"
  ```

## Test the LSP in VS Code

1. Open the **Flow-Wing repo root** in VS Code.
2. Press **F5** (or Run → Start Debugging).
3. Choose **"Launch Flow-Wing LSP"** (it will compile first).
   - If compile fails, run `cd src/lsp && yarn install && yarn compile` manually, then use **"Launch Flow-Wing LSP (no build)"**.
4. A new VS Code window (Extension Development Host) opens.
5. In that window, open a `.fg` file (e.g. `tests/fixtures/LatestTests/01_basics/hello-world.fg`).
6. The extension activates on `.fg` files. Check diagnostics, completions, hover, etc.

## Test files

Use files under `tests/fixtures/LatestTests/` for supported features, for example:

- `01_basics/hello-world.fg` – valid program
- `VariableDeclarationTests/errors/assignment_to_const_int8.fg` – semantic error (diagnostics)
- `FunctionTests/` – functions
- `ObjectTests/` – objects

## Run LSP unit tests

From repo root:

```bash
make lsp-test
```

Or from `src/lsp`:

```bash
yarn test
```

Tests cover: semService (completion, hover, definitions, signature help), function autosuggestion, and sem format detection.

## Debug logging

To see verbose logs (completion flow, symbol resolution, document paths):

```bash
# Run tests with debug output
FLOWWING_LSP_DEBUG=1 make lsp-test
# or
yarn test:debug
```

When running the LSP from VS Code (F5), set `FLOWWING_LSP_DEBUG=1` in the launch config's `env` to see logs in the Debug Console.

## Quick CLI test (without VS Code)

To verify the compiler and error format:

```bash
# Valid file
./build/sdk/bin/FlowWing --file=tests/fixtures/LatestTests/01_basics/hello-world.fg

# File with error (should show diagnostic on stderr)
./build/sdk/bin/FlowWing --file=tests/fixtures/LatestTests/VariableDeclarationTests/errors/assignment_to_const_int8.fg
```
