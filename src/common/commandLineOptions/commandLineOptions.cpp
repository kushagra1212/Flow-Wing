/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

#include "commandLineOptions.h"
#include "src/utils/Utils.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sys/unistd.h>
#include <unistd.h>

namespace FlowWing {
namespace Cli {

argh::parser *cmdl = nullptr;
// Version Options
Option<bool> OPTIONS::Version{
    "--version", "When this flag is set, the version will be printed"};
Option<bool> OPTIONS::ShortVersion{"-V", "Short hand flag for --version"};

// File Options
Option<std::string> OPTIONS::File{
    "--file", "Use --file=<filename.fg/filePath.fg> to specify a file"};
Option<std::string> OPTIONS::ShortFile{"-F", "Short hand flag for --file"};

// Format Options
Option<bool> OPTIONS::Format{"--format",
                             "When this flag is set, the output will be in a "
                             "format that is easier to read"};
Option<bool> OPTIONS::ShortFormat{"-FM", "Short hand flag for --format"};

// Format Print Options
Option<bool> OPTIONS::FormatPrint{
    "--format-print", "When this flag is set, the output will be printed to "
                      "the console in a format that is easier to read"};
Option<bool> OPTIONS::ShortFormatPrint{"-FMP",
                                       "Short hand flag for --format-print"};

// Output File Options
Option<std::string> OPTIONS::OutputFile{
    "--out", "Use --out=<filename.fg> to specify an output file"};
Option<std::string> OPTIONS::ShortOutputFile{"-O", "Short hand flag for --out"};

// Code Options
Option<std::string> OPTIONS::Code{
    "--code", "Use --code=<code> to specify a code as input"};
Option<std::string> OPTIONS::ShortCode{"-C", "Short hand flag for --code"};

// Optimization Options
Option<int> OPTIONS::OptimizationLevel0{"-O0", "No optimization"};
Option<int> OPTIONS::OptimizationLevel1{"-O1", "Optimize for speed"};
Option<int> OPTIONS::OptimizationLevel2{"-O2", "Further optimize for speed"};
Option<int> OPTIONS::OptimizationLevel3{"-O3", "Full optimization"};

// Library Path Option
Option<std::string> OPTIONS::LibraryPath{
    "-L", "Specify the path to library directories"};

// Linking Library Option
Option<std::string> OPTIONS::LinkLibrary{"-l",
                                         "Specify libraries to link with"};

// Framework Option
Option<std::string> OPTIONS::Framework{"-framework",
                                       "Specify frameworks to link with"};

// Entry Point
Option<std::string> OPTIONS::EntryPoint{"-e",
                                        "Specify the entry point function"};

Option<bool> OPTIONS::Help{"--help", "Displays this help page"};
Option<bool> OPTIONS::ShortHelp{"-h", "Short hand flag for --help"};

// Format Options
Option<bool> OPTIONS::Server{
    "--server", "Use --server to include FlowWing Vortex Server library"};
Option<bool> OPTIONS::ShortServer{"-S", "Short hand flag for --server"};

Option<bool> OPTIONS::LinkerWarnings{"--linker-warnings",
                                     "Enable linker warnings"};

namespace isFlag {
int8_t versionName() {
  return ((*cmdl)[{FlowWing::Cli::OPTIONS::Version.name.c_str(),
                   FlowWing::Cli::OPTIONS::ShortVersion.name.c_str()}]);
}

int8_t OptimizationLevel0() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::OptimizationLevel0.name.c_str(),
  }]);
}
int8_t OptimizationLevel1() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::OptimizationLevel1.name.c_str(),
  }]);
}
int8_t OptimizationLevel2() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::OptimizationLevel2.name.c_str(),
  }]);
}
int8_t OptimizationLevel3() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::OptimizationLevel3.name.c_str(),
  }]);
}

int8_t format() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::Format.name.c_str(),
  }]);
}
int8_t shortFormat() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::ShortFormat.name.c_str(),
  }]);
}

int8_t formatPrint() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::FormatPrint.name.c_str(),
  }]);
}
int8_t ShortFormatPrint() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::ShortFormatPrint.name.c_str(),
  }]);
}

int8_t help() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::Help.name.c_str(),
  }]);
}
int8_t shortHelp() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::ShortHelp.name.c_str(),
  }]);
}

int8_t server() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::Server.name.c_str(),
  }]);
}

int8_t shortServer() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::ShortServer.name.c_str(),
  }]);
}

int8_t linkerWarnings() {
  return ((*cmdl)[{
      FlowWing::Cli::OPTIONS::LinkerWarnings.name.c_str(),
  }]);
}

} // namespace isFlag

namespace isParam {
int8_t file() {
  return !(*cmdl)(FlowWing::Cli::OPTIONS::File.name.c_str()).str().empty();
}

int8_t shortFile() {
  return !(*cmdl)(FlowWing::Cli::OPTIONS::ShortFile.name.c_str()).str().empty();
}

int8_t code() {
  return !(*cmdl)(FlowWing::Cli::OPTIONS::Code.name.c_str()).str().empty();
}

int8_t shortCode() {
  return !(*cmdl)(FlowWing::Cli::OPTIONS::ShortCode.name.c_str()).str().empty();
}

int8_t outputFile() {
  return !(*cmdl)(FlowWing::Cli::OPTIONS::OutputFile.name.c_str())
              .str()
              .empty();
}

int8_t shortOutputFile() {
  return !(*cmdl)(FlowWing::Cli::OPTIONS::ShortOutputFile.name.c_str())
              .str()
              .empty();
}
} // namespace isParam

namespace Get {
std::string file() {
  return (*cmdl)(FlowWing::Cli::OPTIONS::File.name.c_str()).str();
}

std::string shortFile() {
  return (*cmdl)(FlowWing::Cli::OPTIONS::ShortFile.name.c_str()).str();
}

std::string code() {
  return (*cmdl)(FlowWing::Cli::OPTIONS::Code.name.c_str()).str();
}

std::string shortCode() {
  return (*cmdl)(FlowWing::Cli::OPTIONS::ShortCode.name.c_str()).str();
}

std::string outputFile() {
  return (*cmdl)(FlowWing::Cli::OPTIONS::OutputFile.name.c_str()).str();
}

std::string shortOutputFile() {
  return (*cmdl)(FlowWing::Cli::OPTIONS::ShortOutputFile.name.c_str()).str();
}

std::string filePath() {
  for (auto &path : (*cmdl).pos_args()) {
    if (path.length() > 3 && path[path.length() - 3] == '.' &&
        path[path.length() - 2] == 'f' && path[path.length() - 1] == 'g') {
      return path;
    }
  }

  return "";
}
} // namespace Get
enum FlowWing::Cli::STATUS handleBasicArgs() {
  if (FlowWing::Cli::isFlag::versionName()) {
#if defined(AOT_MODE)
    std::cout << "Flowwing Compiler" << std::endl;
#elif defined(JIT_MODE)
    std::cout << "Flowwing Just-In-Time Compiler" << std::endl;
#else
    std::cout << "Flowwing REPL" << std::endl;
#endif

    std::cout << "Version: " << VERSION_INFO << std::endl;
    return FlowWing::Cli::STATUS::DONE;
  }

  if (FlowWing::Cli::isFlag::help() || FlowWing::Cli::isFlag::shortHelp()) {
    FlowWing::Cli::printHelp();

    return FlowWing::Cli::STATUS::DONE;
  }

  if (FlowWing::Cli::Get::filePath() != "") {
    return FlowWing::Cli::STATUS::PROCEED;
  }

  if (!FlowWing::Cli::isParam::file() && !FlowWing::Cli::isParam::shortFile()) {
    Utils::printErrors(
        {"Usage: FlowWing  -F=<filename.fg/filePath.fg> or "
         "--file=<filename.fg/filePath.fg> or FlowWing filePath.fg"},
        std::cerr, true);
    return FlowWing::Cli::STATUS::FAILURE;
  }

  return FlowWing::Cli::STATUS::PROCEED;
}

enum FlowWing::Cli::STATUS handleFileArgs(std::vector<std::string> &text,
                                          std::string &filePath, char *argv[]) {

  if (FlowWing::Cli::Get::filePath() != "") {
    filePath = FlowWing::Cli::Get::filePath();
  } else {
    filePath = FlowWing::Cli::isParam::file() ? FlowWing::Cli::Get::file()
                                              : FlowWing::Cli::Get::shortFile();
  }
  // Opens the file using the provided file path

  std::ifstream file;

  file.open(filePath);

  if (!file.is_open()) {
    Utils::printErrors({"Unable to open file: " + std::string(filePath),
                        "Usage: " + std::string(argv[0]) + " <file_path> "},
                       std::cerr);

    if (access(filePath.c_str(), R_OK) != 0) {
      Utils::printErrors({"Please check if the file exists and you have "
                          "read permissions."},
                         std::cerr);
    }

    return FlowWing::Cli::STATUS::FAILURE;
  }
  //! Close the file
  file.close();

  Utils::Node::addPath(Utils::getAbsoluteFilePath(filePath));

  if (FlowWing::Cli::isParam::code()) {
    text = Utils::readLinesFromText(FlowWing::Cli::Get::code());
  } else if (FlowWing::Cli::isParam::shortCode()) {
    text = Utils::readLinesFromText(FlowWing::Cli::Get::shortCode());
  } else {
    text = Utils::readLines(Utils::getAbsoluteFilePath(filePath));
  }

  return FlowWing::Cli::STATUS::PROCEED;
}

void printHelp() {
  std::cout << "FlowWing Compiler Help\n";
  std::cout << "======================\n\n";

  std::vector<std::pair<std::string, std::string>> options = {
      {OPTIONS::Version.name + ", " + OPTIONS::ShortVersion.name,
       OPTIONS::Version.description},
      {OPTIONS::File.name + ", " + OPTIONS::ShortFile.name,
       OPTIONS::File.description},
      {OPTIONS::Format.name + ", " + OPTIONS::ShortFormat.name,
       OPTIONS::Format.description},
      {OPTIONS::FormatPrint.name + ", " + OPTIONS::ShortFormatPrint.name,
       OPTIONS::FormatPrint.description},
      {OPTIONS::OutputFile.name + ", " + OPTIONS::ShortOutputFile.name,
       OPTIONS::OutputFile.description},
      {OPTIONS::Code.name + ", " + OPTIONS::ShortCode.name,
       OPTIONS::Code.description},
      {OPTIONS::OptimizationLevel0.name,
       OPTIONS::OptimizationLevel0.description},
      {OPTIONS::OptimizationLevel1.name,
       OPTIONS::OptimizationLevel1.description},
      {OPTIONS::OptimizationLevel2.name,
       OPTIONS::OptimizationLevel2.description},
      {OPTIONS::OptimizationLevel3.name,
       OPTIONS::OptimizationLevel3.description},
      {OPTIONS::LibraryPath.name, OPTIONS::LibraryPath.description},
      {OPTIONS::LinkLibrary.name, OPTIONS::LinkLibrary.description},
      {OPTIONS::Framework.name, OPTIONS::Framework.description},
      {OPTIONS::EntryPoint.name, OPTIONS::EntryPoint.description},
      {OPTIONS::Help.name + ", " + OPTIONS::ShortHelp.name,
       OPTIONS::Help.description},
      {OPTIONS::Server.name, OPTIONS::Server.description},
      {OPTIONS::LinkerWarnings.name, OPTIONS::LinkerWarnings.description},
  };

  size_t maxFlagLength = 0;
  for (const auto &option : options) {
    maxFlagLength = std::max(maxFlagLength, option.first.length());
  }

  // Print options with formatted alignment
  std::cout << std::left << std::setw(static_cast<int>(maxFlagLength) + 2)
            << "Options"
            << "Description\n";
  std::cout << std::string(maxFlagLength + 2 + 20, '-') << "\n";

  for (const auto &option : options) {
    std::cout << std::left << std::setw(static_cast<int>(maxFlagLength) + 2)
              << option.first << option.second << "\n";
  }

  std::cout << "\nUse " << OPTIONS::Help.name << " or "
            << OPTIONS::ShortHelp.name << " for more details.\n";
}

} // namespace Cli

} // namespace FlowWing
