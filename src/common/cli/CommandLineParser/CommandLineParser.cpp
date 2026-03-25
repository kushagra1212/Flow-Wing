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

#include "CommandLineParser.h"
#include "src/common/cli/CliInfo.h"
#include "src/common/cli/CliReporter.h"
#include "src/common/version.h" // For VERSION_INFO
#include "src/compiler/CompilerInfo.h"
#include "src/external/include/argh.h"
#include "src/utils/LogConfig.h"
#include <iomanip>
#include <iostream>
#include <sstream> // Required for std::stringstream

namespace flow_wing {
namespace cli {

struct CliOption {
  std::vector<const char *> names;
  const char *help_text;
  const char *help_format;
};

class CommandLineParser::Impl {
public:
  const CliOption kOptHelp = {
      {"-h", "--help"}, "Display this help message", "-h, --help"};
  const CliOption kOptVersion = {{"-V", "--version"},
                                 "Display compiler version information",
                                 "-V, --version"};
  const CliOption kOptFile = {
      {"-F", "--file"}, "Input source file path", "-F, --file=<path>"};

  const CliOption kOptCode = {{"-C", "--code"},
                              "Provide source code directly as a string",
                              "-C, --code=<code>"};
  const CliOption kOptFormat = {
      {"-FM", "--format"}, "Format the source file in-place", "-FM, --format"};
  const CliOption kOptFormatPrint = {
      {"-FMP", "--format-print"},
      "Print the formatted source code to the console",
      "-FMP, --format-print"};
  const CliOption kOptOptLevels = {{"-O0", "-O1", "-O2", "-O3"},
                                   "Set optimization level (default: -O0)",
                                   "-O0, -O1, -O2, -O3"};
  const CliOption kOptEntry = {
      {"-e", "--entry-point"},
      "Specify the entry point function (default: main)",
      "-e, --entry-point=<name>"};
  const CliOption kOptLibPath = {
      {"-L"}, "Add a directory to the library search path", "-L <path>"};
  const CliOption kOptLinkLib = {
      {"-l"}, "Link with a specific library", "-l <library>"};
  const CliOption kOptFramework = {{"--framework"},
                                   "Link with a specific framework (macOS)",
                                   "--framework <name>"};
  const CliOption kOptServer = {{"-S", "--server"},
                                "Include FlowWing Vortex Server library",
                                "-S, --server"};
  const CliOption kOptLinkWarn = {
      {"--linker-warnings"}, "Enable linker warnings", "--linker-warnings"};

  const CliOption kOptEmit = {
      {"-E", "--emit"},
      "Emit the output in a specific format (tokens, ast, sem, ir)",
      "-E, --emit=<tokens|ast|sem|ir>"};

  const CliOption kDump = {{"-D", "--dump"}, "Dump the output", "-D, --dump"};

  const CliOption kOutDir = {
      {"-OD", "--output-dir"},
      "Output directory for the generated files (default: ./build)",
      "-OD, --output-dir=<path>"};

  const std::vector<CliOption> cli_options = {
      kOptHelp,        kOptVersion,   kOptFile,     kOptCode,    kOptFormat,
      kOptFormatPrint, kOptOptLevels, kOptEntry,    kOptLibPath, kOptLinkLib,
      kOptFramework,   kOptServer,    kOptLinkWarn, kOptEmit,    kOutDir};

  void printHelp() {
    flow_wing::cli::Reporter::message("FlowWing Compiler Help");
    flow_wing::cli::Reporter::message("======================\n");
    flow_wing::cli::Reporter::message(flow_wing::cli::CliInfo::kUsageString +
                                      "\n");

    size_t maxFlagLength = 0;
    for (const auto &option : cli_options) {
      maxFlagLength =
          std::max(maxFlagLength, std::string(option.help_format).length());
    }

    for (const auto &option : cli_options) {
      std::stringstream ss;
      ss << "  " << std::left << std::setw(static_cast<int>(maxFlagLength) + 2)
         << option.help_format << option.help_text << "\n";
      flow_wing::cli::Reporter::message(ss.str());
    }
  }

  CompilerOptions::OutputType
  getOutputType(const std::string &value,
                CompilerOptions::OutputType default_value) const {
    if (value == "tokens") {
      return CompilerOptions::OutputType::kTokensJson;
    } else if (value == "ast") {
      return CompilerOptions::OutputType::kAstJson;
    } else if (value == "sem") {
      return CompilerOptions::OutputType::kSemJson;
    } else if (value == "ir") {
      return CompilerOptions::OutputType::kLLVM_IR;
    } else if (value == "obj") {
      return CompilerOptions::OutputType::kObj;
    } else if (value == "exe") {
      return CompilerOptions::OutputType::kExe;
    } else if (value == "jit") {
      return CompilerOptions::OutputType::kJIT;
    } else {
      return default_value;
    }
  };

  ParseResult parse(int argc, char *argv[]) {
    argh::parser cmdl(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);
    CompilerOptions opts;

    auto parseParam = [](argh::parser &cmdl, const CliOption &option,
                         const std::string &default_value = "") -> std::string {
      std::string temp_value;
      if (cmdl({option.names[0], option.names[1]}) >> temp_value) {
        return temp_value;
      }
      return default_value;
    };

    // Input file: from parameter or first positional argument
    opts.input_file_path = parseParam(cmdl, kOptFile, "");

    if (opts.input_file_path.empty() && cmdl.pos_args().size() > 1) {
      opts.input_file_path = cmdl.pos_args()[1]; // argv[0] is program name
    }

    opts.code_content = parseParam(cmdl, kOptCode, "");

    opts.entry_point = parseParam(cmdl, kOptEntry);

    // Boolean flags
    if (cmdl[{kOptFormat.names[0], kOptFormat.names[1]}])
      opts.format_source = 1;
    if (cmdl[{kOptFormatPrint.names[0], kOptFormatPrint.names[1]}])
      opts.format_print = 1;
    if (cmdl[{kOptServer.names[0], kOptServer.names[1]}])
      opts.enable_server = 1;
    if (cmdl[{kOptLinkWarn.names[0]}])
      opts.enable_linker_warnings = 1;

    // Handle optimization levels
    if (cmdl[kOptOptLevels.names[3]])
      opts.optimization_level = OptimizationLevel::O3;
    else if (cmdl[kOptOptLevels.names[2]])
      opts.optimization_level = OptimizationLevel::O2;
    else if (cmdl[kOptOptLevels.names[1]])
      opts.optimization_level = OptimizationLevel::O1;
    else
      opts.optimization_level = OptimizationLevel::O0; // Default

    // Handle multi-value options
    for (const auto &path : cmdl.params("L"))
      opts.library_paths.emplace_back(path.second);
    for (const auto &lib : cmdl.params("l"))
      opts.link_libraries.emplace_back(lib.second);
    for (const auto &fw : cmdl.params("framework"))
      opts.frameworks.emplace_back(fw.second);

    // Handle emit options

    auto emit_value = parseParam(cmdl, kOptEmit, "");

    if (!emit_value.empty()) {
      opts.output_type = getOutputType(emit_value, opts.output_type);
    }

    // Handle output directory

    opts.output_dir = parseParam(cmdl, kOutDir, "./build");

    if (cmdl[{kDump.names[0], kDump.names[1]}]) {
      opts.dump = 1;
    }

    if (cmdl[{kOptHelp.names[0], kOptHelp.names[1]}]) {
      opts.show_help = 1;
      this->printHelp();
      return {ParseStatus::kCleanExit, opts, std::nullopt};
    }

    if (cmdl[{kOptVersion.names[0], kOptVersion.names[1]}]) {
      std::stringstream version_message;
      version_message << flow_wing::utils::getCompilerDisplayName() << "\n";
      version_message << "Version: " << VERSION_INFO << "\n";
      flow_wing::cli::Reporter::message(version_message.str());
      opts.show_version = 1;

      return {ParseStatus::kCleanExit, opts, std::nullopt};
    }

    // Check for mandatory input file
    if (opts.input_file_path.empty()) {

      std::stringstream error_message;
      error_message << "No input file provided.\n"
                    << flow_wing::cli::CliInfo::kUsageString;

      return {ParseStatus::kFailure, opts, error_message.str()};
    }

    return {ParseStatus::kSuccess, opts, std::nullopt};
  }
};

CommandLineParser::CommandLineParser() : m_pimpl(std::make_unique<Impl>()) {}
CommandLineParser::~CommandLineParser() = default;

ParseResult CommandLineParser::parse(int argc, char *argv[]) {
  auto result = m_pimpl->parse(argc, argv);

  CLI_PARSER_DEBUG_LOG("Parsed options ", result.options->toString().c_str());

  return result;
}
} // namespace cli

} // namespace flow_wing