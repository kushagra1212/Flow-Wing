# Flow-Wing

![repl](https://github.com/user-attachments/assets/ae3ef362-769d-475e-96ba-3142851d2404)

Flow-Wing language support for [Visual Studio Code](https://code.visualstudio.com/), [Cursor](https://cursor.com/), and other editors that use the Open VSX Registry (e.g. [VSCodium](https://vscodium.com/)). It provides syntax highlighting, a bundled dark theme, diagnostics, IntelliSense, and format-on-save by running the **Flow-Wing compiler** you configure locally (`FlowWing.compilerPath`).

**Source repository:** [github.com/kushagra1212/Flow-Wing](https://github.com/kushagra1212/Flow-Wing) (extension lives under `src/lsp/`). **Publisher ID** on marketplaces must match `publisher` in `package.json` (e.g. `Kushagra` on the Visual Studio Marketplace).

## Features

- **IntelliSense**: Get context-aware code completions as you type.
- **Code Completion**: Easily complete statements and expressions with suggested options.
- **Error Reporting (Diagnostics)**: Receive instant feedback on code errors and issues directly within the editor.
- **Code Browsing**: Navigate through your codebase effortlessly with enhanced code browsing capabilities.

### DEMO

## IntelliSense

<img src="https://github.com/user-attachments/assets/7137dcc5-c3bc-47d9-a460-77ec5bf9ff8d" />

<img src="https://github.com/user-attachments/assets/a15514ac-2c0a-4cd6-9c39-4d188f351a6b" />

## Code Browsing

<img src="https://github.com/user-attachments/assets/e90050e5-7bc0-4736-b4c8-0fea238b5491" />

## Error Reporting

<img src="https://github.com/user-attachments/assets/93d7a8f3-1a38-4317-9cdc-9e0239a2ad3d" />


## REPL

<img src="https://github.com/user-attachments/assets/12db4897-5659-42f4-969b-166de9179f6d" />


## Installation

1. Open Visual Studio Code.
2. Go to the Extensions view by clicking on the Extensions icon in the Activity Bar on the side or by pressing `Ctrl+Shift+X`.
3. Search for **Flow-Wing** (or **Flow-Wing IntelliSense**).
4. Click on the install button.

## Usage

Once installed, the Flow-Wing IntelliSense extension will automatically activate when you open a Flow-Wing file. Begin typing in your Flow-Wing code, and enjoy real-time suggestions and diagnostics.

## Configuration

Settings are under the **`FlowWing`** section (User or Workspace `settings.json`):

| Setting | Default | Purpose |
|--------|---------|--------|
| `FlowWing.enable` | `true` | When `false`, the extension does not start the language server. |
| `FlowWing.compilerPath` | `FlowWing` | Executable name on `PATH`, or absolute path to the Flow-Wing compiler. In an open workspace, the extension may fall back to `build/sdk/bin/FlowWing` under the workspace root. |
| `FlowWing.modulePath` | _(empty)_ | Directory for standard modules (e.g. `build/sdk/lib/modules`). Empty uses the workspace `build/sdk/lib/modules` when possible. |
| `FlowWing.maxNumberOfProblems` | `100` | Reserved cap for diagnostics (the compiler currently surfaces one primary error per validation). |
| `FlowWing.trace.server` | `off` | LSP message tracing: `off`, `messages`, or `verbose`. |

## Contributing

If you would like to contribute to Flow-Wing IntelliSense, feel free to fork the repository and submit a pull request. Your contributions and feedback are welcome!

## Privacy and data

This extension **does not** ship analytics, advertising, or third-party telemetry. It starts a **local** Language Server Protocol (LSP) process and, for analysis and formatting, invokes the **Flow-Wing compiler binary** you configure (default: `FlowWing` on your `PATH`). Your source files and workspace paths remain on your machine.

Optional editor settings can increase logging (for example `FlowWing.trace.server`), which may print LSP traffic to your editor’s output panel—still **local**, not sent to Flow-Wing or Eclipse servers.

## Trademarks

**Flow-Wing** naming and project icons in this repo refer to the Flow-Wing open-source project. **Visual Studio Code**, **VS Code**, and related marks are trademarks of Microsoft Corporation. **Cursor** is a trademark of its owner. **Open VSX** and related Eclipse marks are trademarks of their respective owners. This extension is not endorsed by those organizations unless they say so explicitly.

## Changelog

### [1.0.0] - 2024-10-16

- Initial release of Flow-Wing IntelliSense.
- Added IntelliSense, code completion, and error reporting features.

## License

This extension uses the **same license as the Flow-Wing compiler** and the rest of this repository: **GNU General Public License v2.0 only** (GPL-2.0) — see [`LICENSE.txt`](https://github.com/kushagra1212/Flow-Wing/blob/main/LICENSE.txt) in the repository root. SPDX: `GPL-2.0-only`.

## Support

If you encounter any issues or have questions about using the Flow-Wing IntelliSense extension, please open an issue on the [GitHub repository](https://github.com/kushagra1212/Flow-Wing).

Thank you for using Flow-Wing IntelliSense! Happy coding!
