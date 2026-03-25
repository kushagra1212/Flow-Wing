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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/LLVMBackendContext/LLVMBackendContext.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/CompilationUnitBinder.hpp"
#include "src/common/io/FileUtils.h"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace flow_wing {
namespace syntax {
class SyntaxToken;
}

class CompilationContext {
public:
  explicit CompilationContext(const CompilerOptions &options)
      : m_options(options),
        m_diagnostics(std::make_unique<diagnostic::DiagnosticHandler>()),
        m_absolute_source_file_path(
            utils::PathUtils::getAbsoluteFilePath(options.input_file_path)) {

    std::filesystem::path temp_root(flow_wing::io::getTempDirectoryPath());

    m_tmp_dir =
        (temp_root / flow_wing::ir_gen::constants::paths::kFG_tmp_dir).string();
  }

  // Getters
  const CompilerOptions &getOptions() const { return m_options; }
  const std::string &getAbsoluteSourceFilePath() const {
    return m_absolute_source_file_path;
  }
  const std::vector<std::string> &getSourceLines() const {
    return m_source_lines;
  }
  const std::vector<std::unique_ptr<syntax::SyntaxToken>> &getTokens() const {
    return m_tokens;
  }

  const std::unique_ptr<diagnostic::DiagnosticHandler> &getDiagnostics() const {
    return m_diagnostics;
  }

  const std::unique_ptr<syntax::CompilationUnitSyntax> &getAst() const {
    return m_ast;
  }

  const std::unique_ptr<binding::BoundCompilationUnit> &getBoundTree() const {
    return m_bound_tree;
  }

  const std::string &getTempDirectoryPath() const { return m_tmp_dir; }
  const std::string &getLLVMIr() const { return m_llvm_ir; }

  ir_gen::LLVMBackendContext *getBackendContext() const {
    return m_llvm_backend_context.get();
  }

  // Setters
  void setSourceLines(const std::vector<std::string> &source_lines) {
    m_source_lines = std::move(source_lines);
  }
  void setTokens(std::vector<std::unique_ptr<syntax::SyntaxToken>> tokens) {
    m_tokens = std::move(tokens);
  }
  void setAst(std::unique_ptr<syntax::CompilationUnitSyntax> ast) {
    m_ast = std::move(ast);
  }
  void setBoundTree(std::unique_ptr<binding::BoundCompilationUnit> bound_tree) {
    m_bound_tree = std::move(bound_tree);
  }
  void setLLVMIr(const std::string &llvm_ir) { m_llvm_ir = llvm_ir; }
  void setBackendContext(
      std::unique_ptr<ir_gen::LLVMBackendContext> llvm_backend_context) {
    m_llvm_backend_context = std::move(llvm_backend_context);
  }

  /// Absolute source paths for `bring` dependencies; compiled to .o at the
  /// start of IR generation (after semantic analysis, avoids re-entrant
  /// codegen).
  void addBroughtSourceFile(std::string absolute_path);
  const std::vector<std::string> &getBroughtSourcePaths() const {
    return m_brought_source_paths;
  }

  /// Object files produced for `bring` dependencies (filled when compiling
  /// brought sources to .o). The linker merges these with the primary object.
  void addBroughtObjectFile(std::string object_path) {
    m_brought_object_files.push_back(std::move(object_path));
  }
  const std::vector<std::string> &getBroughtObjectFiles() const {
    return m_brought_object_files;
  }

private:
  const CompilerOptions m_options;
  std::unique_ptr<diagnostic::DiagnosticHandler> m_diagnostics;
  std::vector<std::string> m_source_lines = {};
  std::string m_absolute_source_file_path;
  std::vector<std::unique_ptr<syntax::SyntaxToken>> m_tokens;
  std::unique_ptr<syntax::CompilationUnitSyntax> m_ast;
  std::unique_ptr<binding::BoundCompilationUnit> m_bound_tree;
  std::string m_llvm_ir;
  std::string m_tmp_dir;
  std::unique_ptr<ir_gen::LLVMBackendContext> m_llvm_backend_context = nullptr;
  std::vector<std::string> m_brought_source_paths;
  std::vector<std::string> m_brought_object_files;
};

inline void
CompilationContext::addBroughtSourceFile(std::string absolute_path) {
  absolute_path = utils::PathUtils::getAbsoluteFilePath(absolute_path);
  if (std::find(m_brought_source_paths.begin(), m_brought_source_paths.end(),
                absolute_path) != m_brought_source_paths.end()) {
    return;
  }
  m_brought_source_paths.push_back(std::move(absolute_path));
}
} // namespace flow_wing