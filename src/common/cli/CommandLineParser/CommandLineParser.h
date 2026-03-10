/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#pragma once

#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include <memory>
#include <string>

namespace flow_wing {
namespace cli {
// Enum to represent the explicit result states of the parser.
enum class ParseStatus {
  kSuccess,  // Parsing succeeded, options are available.
  kFailure,  // Parsing failed, an error message is available.
  kCleanExit // A flag like --help or --version was used; exit gracefully.
};

struct ParseResult {
  ParseStatus status;
  std::optional<CompilerOptions> options; // Has value on Success
  std::optional<std::string> message;     // Has value on Failure
};

class CommandLineParser {
public:
  CommandLineParser();
  ~CommandLineParser();

  // The primary method to parse command-line arguments.
  // or if an early exit is requested (e.g., --help).
  ParseResult parse(int argc, char *argv[]);

private:
  class Impl;
  std::unique_ptr<Impl> m_pimpl;

  CompilerOptions::OutputType getOutputType(const std::string &value);
};
} // namespace cli

} // namespace flow_wing