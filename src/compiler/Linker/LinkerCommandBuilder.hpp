/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */

#pragma once

#include "src/compiler/CompilationContext/CompilationContext.h"
#include <string>
#include <vector>

namespace flow_wing {
namespace linker {

class LinkerCommandBuilder {
public:
  explicit LinkerCommandBuilder(CompilationContext &context);
  ~LinkerCommandBuilder();

  std::string generateLinkCommand();

private:
  CompilationContext &m_context;
  std::vector<std::string> m_object_files;

  void addLinkerBinary(std::vector<std::string> &args);
  void addPlatformPreamble(std::vector<std::string> &args);
  void addOutputConfig(std::vector<std::string> &args);
  void addObjectFiles(std::vector<std::string> &args);
  void addUserArguments(std::vector<std::string> &args);
  void addRuntimeLibraries(std::vector<std::string> &args);
  void addSystemLibraries(std::vector<std::string> &args);

  std::string getLibPathFlag(const std::string &path) const;
  std::string getLibLinkFlag(const std::string &libName) const;
  std::string getOutputFlag() const;
  std::string getEntryPointFlag(const std::string &entry) const;
  std::string getBinaryFilePath() const;
};
} // namespace linker
} // namespace flow_wing