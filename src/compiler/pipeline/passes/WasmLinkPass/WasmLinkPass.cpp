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

#include "WasmLinkPass.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/io/ObjectUtils.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/Linker/EmscriptenToolchain.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/MemoryBuffer.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace compiler {
namespace pipeline {

namespace {

namespace fs = std::filesystem;

// One argument, quoted for the platform shell that std::system runs.
std::string quoted(const std::string &argument) {
#if defined(_WIN32)
  return "\"" + argument + "\"";
#else
  std::string out = "'";
  for (const char c : argument) {
    if (c == '\'') {
      out += "'\\''";
    } else {
      out += c;
    }
  }
  return out + "'";
#endif
}

void setEnvironment(const char *name, const std::string &value) {
#if defined(_WIN32)
  _putenv_s(name, value.c_str());
#else
  setenv(name, value.c_str(), 1);
#endif
}

// -o as given, with .js added when it has no extension, since emcc picks its
// output format from the extension. Without -o: <output-dir>/bin/<hash>.js,
// the wasm32 counterpart of the native default.
fs::path outputPath(const CompilationContext &context) {
  const auto &options = context.getOptions();
  fs::path out = options.output_executable_path;
  if (out.empty()) {
    out = fs::path(options.output_dir) / "bin" /
          (utils::PathUtils::shortHashedHex16ForPath(
               context.getAbsoluteSourceFilePath()) +
           ".js");
  } else if (!out.has_extension()) {
    out += ".js";
  }
  return out;
}

std::string optimizationFlag(OptimizationLevel level) {
  switch (level) {
  case OptimizationLevel::O0:
    return "-O0";
  case OptimizationLevel::O1:
    return "-O1";
  case OptimizationLevel::O2:
    return "-O2";
  case OptimizationLevel::O3:
    return "-O3";
  }
  return "-O0";
}

// Whether any unit spawns a task, the only way a task switch can happen. Only
// such a program is linked with Asyncify, which fw_sched.c needs to switch
// stacks on wasm and which makes every program about 40% bigger and
// collection-heavy ones up to a third slower. Read from each unit's bitcode,
// so brought units count as well as the entry.
bool spawnsTasks(const std::vector<std::string> &units) {
  namespace functions = ir_gen::constants::functions;
  llvm::LLVMContext llvm_context;
  for (const auto &unit : units) {
    auto buffer = llvm::MemoryBuffer::getFile(unit);
    if (!buffer) {
      continue; // em++ reports the missing file
    }
    auto module =
        llvm::parseBitcodeFile((*buffer)->getMemBufferRef(), llvm_context);
    if (!module) {
      llvm::consumeError(module.takeError());
      continue;
    }
    for (const auto name :
         {functions::kSched_spawn_fn, functions::kSched_spawn_args_fn}) {
      const llvm::Function *fn = (*module)->getFunction(name);
      if (fn != nullptr && !fn->use_empty()) {
        return true;
      }
    }
  }
  return false;
}

std::string readFile(const fs::path &path) {
  std::ifstream in(path);
  std::stringstream text;
  text << in.rdbuf();
  return text.str();
}

} // namespace

std::string WasmLinkPass::getName() const { return "Wasm Link"; }

// The wasm32 counterpart of LinkerPass: hands every unit's bitcode and the
// wasm build of the runtime to em++ (emcc's C++ driver, see
// EmscriptenToolchain::linkerDriver), which writes <out>.js + <out>.wasm, or a
// page when -o ends in .html.
ReturnStatus WasmLinkPass::run(CompilationContext &context) {
  const auto toolchain = linker::EmscriptenToolchain::find();
  if (!toolchain.problem.empty()) {
    cli::Reporter::error(toolchain.problem);
    return ReturnStatus::kFailure;
  }
  if (!fs::exists(toolchain.runtimeArchive())) {
    cli::Reporter::error(
        "The Flow-Wing runtime for wasm32 is not built (no " +
        toolchain.runtimeArchive().string() +
        ").\nBuild it once with: make build-wasm-runtime");
    return ReturnStatus::kFailure;
  }

  const fs::path out = outputPath(context);
  const bool browser = out.extension() == ".html";
  std::error_code error;
  fs::create_directories(out.parent_path(), error);

  std::vector<std::string> units = context.getBroughtObjectFiles();
  units.push_back(ir_gen::ObjectUtils::getObjectFilePath(
      context.getAbsoluteSourceFilePath(), context.getOptions().output_dir));

  std::vector<std::string> args = {toolchain.linkerDriver()};
  args.insert(args.end(), units.begin(), units.end());
  args.push_back(toolchain.runtimeArchive().string());
  args.push_back(optimizationFlag(context.getOptions().optimization_level));

  // Without it the runtime never shuts down, stdout is never flushed, and
  // output with no trailing newline, such as print("x"), is lost.
  args.push_back("-sEXIT_RUNTIME=1");
  // The GC heap grows as the program allocates; the default is a fixed 16 MB.
  args.push_back("-sALLOW_MEMORY_GROWTH=1");
  // The same 8 MB a native main gets, instead of emscripten's 64 KB, so deep
  // recursion behaves the same on both.
  args.push_back("-sSTACK_SIZE=8388608");
  if (spawnsTasks(units)) {
    // Emscripten fibers switch stacks through Asyncify. wasm has no guard
    // pages, so a task's stack overflow is caught instead by a stack-pointer
    // check at every function entry, against the running fiber's limits.
    args.push_back("-sASYNCIFY");
    args.push_back("-sSTACK_OVERFLOW_CHECK=2");
  }
  if (!browser) {
    // Under Node: byte-exact stdout and the real environment. See
    // node-host.js.
    args.push_back("-sFORCE_FILESYSTEM=1");
    args.push_back("--pre-js");
    args.push_back(toolchain.nodeHostScript().string());
  }
  args.push_back("-o");
  args.push_back(out.string());

  if (!toolchain.emsdk_python.empty()) {
    setEnvironment("EMSDK_PYTHON", toolchain.emsdk_python);
  }

  // em++ prints warnings even on success. They go to a log that is shown
  // only when the link fails, so a good build prints nothing but progress.
  const fs::path log = out.parent_path() / (out.stem().string() + ".link.log");
  std::string command;
  for (const auto &arg : args) {
    command += quoted(arg) + " ";
  }
  command += "> " + quoted(log.string()) + " 2>&1";
#if defined(_WIN32)
  // cmd /c strips the first and last quote of a line that starts with one.
  command = "\"" + command + "\"";
#endif

  context.getBuildProgress().linking(out.string());
  if (std::system(command.c_str()) != 0) {
    cli::Reporter::error("em++ failed to link " + out.string() + ":\n" +
                         readFile(log));
    return ReturnStatus::kFailure;
  }
  fs::remove(log, error);
  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
