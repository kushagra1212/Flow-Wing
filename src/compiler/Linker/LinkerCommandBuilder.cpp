/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */

#include "src/compiler/Linker/LinkerCommandBuilder.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/common/LibUtils/LibUtils.h"
#include "src/common/io/FileUtils.h"
#include "src/common/io/PathUtils.hpp"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/utils/LogConfig.h"
#include "src/utils/PathUtils.h"
#include <sstream>

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
  args.push_back(AOT_LINKER_PATH);
}

void LinkerCommandBuilder::addPlatformPreamble(std::vector<std::string> &args) {
#if defined(__APPLE__)
  args.push_back(MACOS_SDK_SYSROOT_FLAG);
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
  args.push_back(getOutputFlag() + getBinaryFilePath());
}

void LinkerCommandBuilder::addObjectFiles(std::vector<std::string> &args) {
  m_object_files = io::getFiles(
      std::string(flow_wing::ir_gen::constants::paths::kObject_files_dir),
      std::string(flow_wing::ir_gen::constants::paths::kObject_file_extension));

  args.insert(args.end(), m_object_files.begin(), m_object_files.end());
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
    args.push_back(getLibPathFlag(io::PathUtils::getLibrariesPath().c_str()));
    args.push_back(getLibLinkFlag("flowwing_vortex"));
  }

  if (!m_context.getOptions().entry_point.empty()) {
    args.push_back(getEntryPointFlag(
        std::string(flow_wing::ir_gen::constants::functions::kMain_fn)));
  }
}

void LinkerCommandBuilder::addRuntimeLibraries(std::vector<std::string> &args) {
  std::string runtimePath = io::PathUtils::getLibrariesPath().c_str();
  LINKING_DEBUG_LOG("runtimeLibPath", runtimePath);

  args.push_back(getLibPathFlag(runtimePath));

  for (const auto &lib : STATIC_LINKING_LIBRARIES) {
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
  return ""; // Linux/Windows handle this differently or don't support -e flag
             // the same way
#endif
}

std::string LinkerCommandBuilder::getBinaryFilePath() const {

  std::string output_file_path =
      m_context.getOptions().output_file_path.value();

  if (output_file_path.empty()) {
    output_file_path =
        std::string(flow_wing::ir_gen::constants::paths::kBin_files_dir) +
        m_context.getOptions().input_file_path;
  }

  std::string binary_file_path =
      utils::PathUtils::removeExtension(output_file_path);

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