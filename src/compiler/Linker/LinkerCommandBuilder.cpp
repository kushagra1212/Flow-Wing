/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */

#include "src/compiler/Linker/LinkerCommandBuilder.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/io/ObjectUtils.hpp"
#include "src/IRGen/io/Utils.hpp"
#include "src/common/LibUtils/LibUtils.h"
#include "src/common/io/PathUtils.hpp"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/utils/LogConfig.h"
#include <sstream>
#include <string>
#include <unordered_set>

namespace flow_wing {
namespace linker {

static std::string joinArgs(const std::vector<std::string> &args) {
  std::ostringstream oss;
  for (size_t i = 0; i < args.size(); ++i) {
    oss << args[i] << (i == args.size() - 1 ? "" : " ");
  }
  return oss.str();
}

LinkerCommandBuilder::LinkerCommandBuilder(CompilationContext &context)
    : m_context(context) {}

std::string LinkerCommandBuilder::generateLinkCommand() {
  std::vector<std::string> cmd;

  addLinkerBinary(cmd);

  addPlatformPreamble(cmd);

  // 3. Output file configuration (-o /OUT:)
  addOutputConfig(cmd);

  // 4. Input Object Files
  addObjectFiles(cmd);

  // 5. User Flags (Entry point, Frameworks, extra libs)
  addUserArguments(cmd);

  // 6. FlowWing Runtime Libraries
  addRuntimeLibraries(cmd);

  // 7. System Libraries (libc++, msvcrt, etc)
  addSystemLibraries(cmd);

  return joinArgs(cmd);
}

// ========================================================
// Logic Implementation
// ========================================================

void LinkerCommandBuilder::addLinkerBinary(std::vector<std::string> &args) {
  std::string linker = AOT_LINKER_PATH;
  if (linker.empty()) {
    linker = "clang++";
  }
  args.push_back(std::move(linker));
}

void LinkerCommandBuilder::addPlatformPreamble(std::vector<std::string> &args) {
#if defined(__APPLE__)
  {
    std::string sysroot_flag = MACOS_SDK_SYSROOT_FLAG;
    const size_t sp = sysroot_flag.find(' ');
    if (sp != std::string::npos) {
      args.push_back(sysroot_flag.substr(0, sp));
      args.push_back(sysroot_flag.substr(sp + 1));
    } else if (!sysroot_flag.empty()) {
      args.push_back(std::move(sysroot_flag));
    }
  }
  // Suppress warnings
  if (!m_context.getOptions().enable_linker_warnings) {
    args.push_back("-Wl,-w");
  }
#elif defined(__linux__)
  args.push_back("-fuse-ld=lld");
#elif defined(_WIN32)
  args.push_back("/nologo");
#endif
}

void LinkerCommandBuilder::addOutputConfig(std::vector<std::string> &args) {
  auto binary_file_path = getBinaryFilePath();

  std::filesystem::path output_directory =
      std::filesystem::path(binary_file_path).parent_path();
  flow_wing::ir_gen::Utils::createDirectories(output_directory.string());

  args.push_back(getOutputFlag() + binary_file_path);
}

void LinkerCommandBuilder::addObjectFiles(std::vector<std::string> &args) {
  // Link only this TU's object plus brought dependency objects — not every .o
  // under build/objects (that would duplicate brought TUs and pull unrelated
  // objects from other compilations).
  std::unordered_set<std::string> seen;
  const std::string primary = ir_gen::ObjectUtils::getObjectFilePath(
      m_context.getAbsoluteSourceFilePath(),
      m_context.getOptions().output_dir);
  m_object_files.clear();
  m_object_files.push_back(primary);
  seen.insert(primary);
  args.push_back(primary);

  for (const auto &extra : m_context.getBroughtObjectFiles()) {
    if (seen.insert(extra).second) {
      m_object_files.push_back(extra);
      args.push_back(extra);
    }
  }
}

void LinkerCommandBuilder::addUserArguments(std::vector<std::string> &args) {

  for (const auto &path : m_context.getOptions().library_paths) {
    args.push_back(getLibPathFlag(path));
  }
  for (const auto &lib : m_context.getOptions().link_libraries) {
    args.push_back(getLibLinkFlag(lib));
  }
  for (const auto &framework : m_context.getOptions().frameworks) {
    args.push_back("-framework " + framework);
  }

  // Handle Server Flags
  if (m_context.getOptions().enable_server) {
    args.push_back(getLibPathFlag(io::PathUtils::getLibrariesPath().string()));
    args.push_back(getLibLinkFlag("flowwing_vortex"));
  }

  if (!m_context.getOptions().entry_point.empty()) {
    args.push_back(getEntryPointFlag(
        std::string(flow_wing::ir_gen::constants::functions::kMain_fn)));
  }
}

void LinkerCommandBuilder::addRuntimeLibraries(std::vector<std::string> &args) {
  std::string runtimePath = io::PathUtils::getLibrariesPath().string();
  LINKING_DEBUG_LOG("runtimeLibPath", runtimePath);

  args.push_back(getLibPathFlag(runtimePath));

  std::vector<std::string> runtime_libraries;
  std::unordered_set<std::string> seen_libraries;
  auto add_library = [&](const std::string &lib) {
    if (!lib.empty() && seen_libraries.insert(lib).second) {
      runtime_libraries.push_back(lib);
    }
  };

  for (const auto &lib : STATIC_LINKING_LIBRARIES) {
    add_library(lib);
  }

  auto add_source_libraries = [&](const std::string &source_path) {
    for (const auto &lib : getRuntimeLibrariesForSourceFile(source_path)) {
      add_library(lib);
    }
  };

  add_source_libraries(m_context.getAbsoluteSourceFilePath());
  for (const auto &brought_source : m_context.getBroughtSourcePaths()) {
    add_source_libraries(brought_source);
  }

  for (const auto &lib : runtime_libraries) {
    args.push_back(getLibLinkFlag(lib));
  }
}

void LinkerCommandBuilder::addSystemLibraries(
    [[maybe_unused]] std::vector<std::string> &args) {
#if defined(__linux__)
  args.push_back("-lstdc++");
#elif defined(_WIN32)

  for (const auto &lib :
       {"ucrt.lib", "vcruntime.lib", "kernel32.lib", "user32.lib",
        "advapi32.lib", "msvcrt.lib", "legacy_stdio_definitions.lib",
        "/SUBSYSTEM:CONSOLE", "/IGNORE:4210"}) {
    args.push_back(lib);
  }
#endif
}

// Platform Abstractors

std::string
LinkerCommandBuilder::getLibPathFlag(const std::string &path) const {
#if defined(_WIN32)
  return "/LIBPATH:\"" + path + "\"";
#else
  return "-L\"" + path + "\"";
#endif
}

std::string
LinkerCommandBuilder::getLibLinkFlag(const std::string &libName) const {
#if defined(_WIN32)
  return libName + ".lib";
#else
  return "-l" + libName;
#endif
}

std::string LinkerCommandBuilder::getOutputFlag() const {
#if defined(_WIN32)
  return "/OUT:";
#else
  return "-o ";
#endif
}

std::string
LinkerCommandBuilder::getEntryPointFlag(const std::string &entry) const {
#if defined(__APPLE__)
  return "-e _" + entry;
#else
  (void)entry; // Linux/Windows handle this differently or don't support -e flag
  return "";   // the same way
#endif
}

std::string LinkerCommandBuilder::getBinaryFilePath() const {
  const std::string &explicit_out =
      m_context.getOptions().output_executable_path;
  // Development: Makefile passes `-o build/bin/<stem>` so the run target can execute a stable path.
  if (!explicit_out.empty()) {
    std::string binary_file_path = explicit_out;
#if defined(_WIN32)
    if (binary_file_path.find(".exe") == std::string::npos)
      binary_file_path += ".exe";
#endif
    return binary_file_path;
  }

  // Default (incl. test-aot): unique hashed basename under bin/ — runner never passes `-o`.
  const std::string short_base = utils::PathUtils::shortHashedHex16ForPath(
      m_context.getAbsoluteSourceFilePath());
  std::string binary_file_path = "";
  // handle windows and ma
#if defined(_WIN32)
  binary_file_path =
      m_context.getOptions().output_dir + "\\bin\\" + short_base;
#else
  binary_file_path =
      m_context.getOptions().output_dir + "/bin/" + short_base;
#endif

  if (binary_file_path.empty()) {
    binary_file_path =
        std::string(flow_wing::ir_gen::constants::paths::kBin_files_dir) +
        short_base;
  }

  LINKING_DEBUG_LOG("binary_file_path", binary_file_path);

#if defined(_WIN32)
  if (binary_file_path.find(".exe") == std::string::npos)
    binary_file_path += ".exe";
#endif

  LINKING_DEBUG_LOG("binary_file_path", binary_file_path);

  return binary_file_path;
}

LinkerCommandBuilder::~LinkerCommandBuilder() {
  for (const auto &objectFile : m_object_files) {
    LINKING_DEBUG_LOG("Removing object file: ", objectFile);
    std::filesystem::remove(objectFile);
  }
}

} // namespace linker
} // namespace flow_wing
