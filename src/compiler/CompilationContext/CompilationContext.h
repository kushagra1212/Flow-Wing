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
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/CompilationUnitBinder.hpp"
#include "src/common/io/FileUtils.h"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/compiler/BuildProgress/BuildProgress.hpp"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace flow_wing {
namespace ir_gen {
class LLVMBackendContext;
}
namespace syntax {
class SyntaxToken;
}

class CompilationContext {
public:
  explicit CompilationContext(const CompilerOptions &options, std::string &entry_file_path)
      : m_options(options),
        m_diagnostics(std::make_unique<diagnostic::DiagnosticHandler>()),
        m_absolute_source_file_path(
            utils::PathUtils::getAbsoluteFilePath(options.input_file_path)), m_entry_file_path(entry_file_path),
        m_build_progress(options, m_absolute_source_file_path) {


    std::filesystem::path temp_root(flow_wing::io::getTempDirectoryPath());

    m_tmp_dir =
        (temp_root / flow_wing::ir_gen::constants::paths::kFG_tmp_dir).string();
  }

  // Getters
  const CompilerOptions &getOptions() const { return m_options; }

  // The Compiling / Linking / Finished lines. Silent unless this is the root
  // build and progress is shown; dependency contexts are built with
  // ProgressMode::kNever.
  compiler::BuildProgress &getBuildProgress() { return m_build_progress; }
  const std::string &getAbsoluteSourceFilePath() const {
    return m_absolute_source_file_path;
  }
  const std::string &getEntryFilePath() const {
    return m_entry_file_path;
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

  // Created and destroyed by IR generation, which supplies the deleter, so
  // this header needs no LLVM and the front end builds without it.
  using BackendContextPtr =
      std::unique_ptr<ir_gen::LLVMBackendContext,
                      void (*)(ir_gen::LLVMBackendContext *)>;

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
  void setBackendContext(BackendContextPtr llvm_backend_context) {
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

  /// For `emit_brought_dependency_object` TUs only: index in
  /// `getBroughtSourcePaths()` order. Currently it has no effect:
  /// broughtInitFunctionName ignores it, and module init order comes only
  /// from the order in which the root's `main` calls each init function,
  /// which is that same list order.
  void setBroughtCtorPriority(int priority) { m_brought_ctor_priority = priority; }
  int getBroughtCtorPriority() const { return m_brought_ctor_priority; }

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
  BackendContextPtr m_llvm_backend_context{nullptr, nullptr};
  std::vector<std::string> m_brought_source_paths;
  std::vector<std::string> m_brought_object_files;
  int m_brought_ctor_priority = -1;
  std::string m_entry_file_path;
  compiler::BuildProgress m_build_progress;
};

inline void
CompilationContext::addBroughtSourceFile(std::string absolute_path) {
  // Normalised, because the same file arrives spelled differently:
  // `bring "framework/x.fg"` from main.fg and `bring "../framework/x.fg"` from
  // suites/a.fg. Compared raw, the two spellings missed each other and the
  // file was listed twice: compiled twice, and main called its init function
  // twice, so the module's top-level code ran twice.
  // BringTests/init_runs_once guards this.
  //
  // lexically_normal, not weakly_canonical: resolving symlinks (macOS /tmp is
  // /private/tmp) would stop brought paths from sharing a prefix with an entry
  // path that was not resolved.
  absolute_path = std::filesystem::path(
                      utils::PathUtils::getAbsoluteFilePath(absolute_path))
                      .lexically_normal()
                      .string();
  if (std::find(m_brought_source_paths.begin(), m_brought_source_paths.end(),
                absolute_path) != m_brought_source_paths.end()) {
    return;
  }
  m_brought_source_paths.push_back(std::move(absolute_path));
}
} // namespace flow_wing