# Debugging the Flow-Wing LSP

## If F5 does nothing

1. **Open the Run and Debug panel**: Press `Cmd+Shift+D` (Mac) or `Ctrl+Shift+D` (Windows/Linux).

2. **Select a configuration**: In the dropdown at the top, choose **"Launch Flow-Wing LSP"**.

3. **Start debugging**: Press F5 or click the green play button.

4. **Ensure the workspace is the repo root**: File → Open Folder → select the Flow-Wing root (the folder containing `src/`, `tests/`, etc.). The launch config is in `.vscode/launch.json` at the root.

## Alternative: Run from terminal

```bash
# Compile and launch (opens new window with extension loaded)
make run-lsp
```

This uses `cursor` or `code` from your PATH. If that fails, install the CLI from the editor's Command Palette: **"Shell Command: Install 'code' command in PATH"** (or equivalent for Cursor).

## First-time setup

Before launching, install and compile the LSP once:

```bash
cd src/lsp && yarn install && yarn compile
```
