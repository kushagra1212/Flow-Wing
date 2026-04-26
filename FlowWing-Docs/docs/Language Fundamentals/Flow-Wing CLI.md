---
id: flow-wing-cli
title: Flow-Wing CLI Documentation
sidebar_label: Flow-Wing CLI
---

# Flow-Wing Compiler Help

The Flow-Wing CLI provides several options for compiling and managing your Flow-Wing programs. This page documents the available options, including example commands.

## Options and Descriptions

| **Option**               | **Description**                                                                          |
|--------------------------|------------------------------------------------------------------------------------------|
| `--version`, `-V`         | Prints the current version of the Flow-Wing compiler.                                    |
| `--file`, `-F`            | Specify a file to compile with `--file=<filename.fg/filePath.fg>`.                       |
| `--format`, `-FM`         | Outputs the result in a more readable format.                                            |
| `--format-print`, `-FMP`  | Prints the output to the console in a more readable format.                              |
| `--out`, `-O`             | Specify the output file with `--out=<filename.fg>`.                                      |
| `--code`, `-C`            | Pass code directly as input with `--code=<code>`.                                        |
| `-O0`                     | No optimization.                                                                         |
| `-O1`                     | Optimize for speed.                                                                      |
| `-O2`                     | Further optimize for speed.                                                              |
| `-O3`                     | Full optimization.                                                                       |
| `-L`                      | Specify the path to library directories.                                                 |
| `-l`                      | Specify libraries to link with.                                                          |
| `--framework`             | Specify frameworks to link with.                                                         |
| `-e`                      | Specify the entry point function.                                                        |
| `--help`, `-h`            | Displays the help page for the Flow-Wing CLI.                                            |
| `--server`                | Include the Flow-Wing Vortex Server library with `--server`.                             |
| `--linker-warnings`       | Enable linker warnings during compilation.                                               |

## Example Usage

Here are some example commands using the Flow-Wing CLI:

### Printing Version

```bash
flowwing --version
