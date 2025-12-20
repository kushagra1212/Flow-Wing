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

#pragma once

#include "src/IRGen/LLVMBackendContext/LLVMBackendContext.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/CompilationUnitBinder.hpp"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include <memory>
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
            utils::PathUtils::getAbsoluteFilePath(options.input_file_path)) {}

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

private:
  const CompilerOptions m_options;
  std::unique_ptr<diagnostic::DiagnosticHandler> m_diagnostics;
  std::vector<std::string> m_source_lines = {};
  std::string m_absolute_source_file_path;
  std::vector<std::unique_ptr<syntax::SyntaxToken>> m_tokens;
  std::unique_ptr<syntax::CompilationUnitSyntax> m_ast;
  std::unique_ptr<binding::BoundCompilationUnit> m_bound_tree;
  std::string m_llvm_ir;
  std::unique_ptr<ir_gen::LLVMBackendContext> m_llvm_backend_context = nullptr;
};
} // namespace flow_wing