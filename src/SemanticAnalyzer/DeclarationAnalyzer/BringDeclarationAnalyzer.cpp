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

#include "DeclarationAnalyzer.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/diagnostics/Diagnostic.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/compiler/pipeline/CompilationPipeline.h"
#include "src/compiler/pipeline/passes/LexerPass/LexerPass.h"
#include "src/compiler/pipeline/passes/ParsingPass/ParsingPass.h"
#include "src/compiler/pipeline/passes/SemanticAnalysisPass/SemanticAnalysisPass.hpp"
#include "src/compiler/pipeline/passes/SourceLoaderPass.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "src/common/io/PathUtils.hpp"
#include <algorithm>
#include <filesystem>
#include <optional>
#include <queue>
#include <system_error>
#include <vector>

namespace flow_wing {

namespace {

/// If `base_dir / relative_path` is missing, search breadth-first under
/// `base_dir` for a regular file whose name equals `relative_path`'s filename
/// (e.g. `bring "local-module.fg"` or `bring local` → `local-module.fg` in a
/// subdirectory).
std::optional<std::string>
tryResolveBringPath(const std::filesystem::path &base_dir,
                    const std::filesystem::path &relative_path) {
  std::error_code ec;
  const auto direct = std::filesystem::absolute(base_dir / relative_path, ec);
  if (!ec && std::filesystem::is_regular_file(direct)) {
    return direct.string();
  }
  const std::string leaf = relative_path.filename().string();
  if (leaf.empty()) {
    return std::nullopt;
  }
  std::queue<std::filesystem::path> q;
  q.push(base_dir);
  while (!q.empty()) {
    const auto cur = q.front();
    q.pop();
    std::error_code ec_dir;
    if (!std::filesystem::exists(cur, ec_dir) || ec_dir) {
      continue;
    }
    std::filesystem::directory_iterator it(cur, ec_dir);
    if (ec_dir) {
      continue;
    }
    for (const auto &entry : it) {
      std::error_code ec_ent;
      if (entry.is_directory(ec_ent)) {
        if (!ec_ent) {
          q.push(entry.path());
        }
      } else if (entry.is_regular_file(ec_ent) && !ec_ent &&
                 entry.path().filename() == leaf) {
        std::error_code ec_abs;
        auto abs = std::filesystem::absolute(entry.path(), ec_abs);
        if (!ec_abs) {
          return abs.string();
        }
      }
    }
  }

  std::filesystem::path cur = base_dir;
  while (true) {
    std::error_code ec_candidate;
    const auto candidate = cur / "fw-modules";
    if (!std::filesystem::exists(candidate, ec_candidate) || ec_candidate) {
      // not present here; move up
    } else if (std::filesystem::is_directory(candidate)) {
      // Try direct path first
      std::error_code ec_direct2;
      const auto direct2 =
          std::filesystem::absolute(candidate / relative_path, ec_direct2);
      if (!ec_direct2 && std::filesystem::is_regular_file(direct2)) {
        return direct2.string();
      }

      // BFS under the candidate directory
      std::queue<std::filesystem::path> q2;
      q2.push(candidate);
      const std::string leaf2 = relative_path.filename().string();
      while (!q2.empty()) {
        const auto cur2 = q2.front();
        q2.pop();
        std::error_code ec_dir2;
        if (!std::filesystem::exists(cur2, ec_dir2) || ec_dir2) {
          continue;
        }
        std::filesystem::directory_iterator it2(cur2, ec_dir2);
        if (ec_dir2) {
          continue;
        }
        for (const auto &entry2 : it2) {
          std::error_code ec_ent2;
          if (entry2.is_directory(ec_ent2)) {
            if (!ec_ent2) {
              q2.push(entry2.path());
            }
          } else if (entry2.is_regular_file(ec_ent2) && !ec_ent2 &&
                     entry2.path().filename() == leaf2) {
            std::error_code ec_abs2;
            auto abs2 = std::filesystem::absolute(entry2.path(), ec_abs2);
            if (!ec_abs2) {
              return abs2.string();
            }
          }
        }
      }
    }

    if (cur == cur.root_path()) {
      break;
    }
    cur = cur.parent_path();
  }

  return std::nullopt;
}

/// Tracks nested `bring` paths during semantic analysis so A→B→A is rejected
/// instead of overflowing the stack.
thread_local std::vector<std::string> g_bring_path_stack;

bool nestedDiagnosticsHasCircularReference(
    const CompilationContext &nested_ctx) {
  for (const auto &d : nested_ctx.getDiagnostics()->getDiagnostics()) {
    if (d.getLevel() == diagnostic::DiagnosticLevel::kError &&
        d.getCode() == diagnostic::DiagnosticCode::kCircularReference) {
      return true;
    }
  }
  return false;
}

void reportDuplicateImportedName(
    binding::BinderContext &binder_context,
    const std::shared_ptr<analysis::Symbol> &symbol,
    const flow_wing::diagnostic::SourceLocation &location) {

  using analysis::SymbolKind;
  using diagnostic::DiagnosticCode;

  switch (symbol->getKind()) {
  case SymbolKind::kVariable:
    binder_context.reportError(DiagnosticCode::kVariableAlreadyDeclared,
                               diagnostic::DiagnosticArgs{symbol->getName()},
                               location);
    break;
  case SymbolKind::kFunction:
    binder_context.reportError(DiagnosticCode::kFunctionAlreadyDeclared,
                               diagnostic::DiagnosticArgs{symbol->getName()},
                               location);
    break;
  case SymbolKind::kType:
    binder_context.reportError(DiagnosticCode::kTypeAlreadyDeclared,
                               diagnostic::DiagnosticArgs{symbol->getName()},
                               location);
    break;
  case SymbolKind::kClass:
    binder_context.reportError(DiagnosticCode::kClassAlreadyDeclared,
                               diagnostic::DiagnosticArgs{symbol->getName()},
                               location);
    break;
  default:
    binder_context.reportError(DiagnosticCode::kVariableAlreadyDeclared,
                               diagnostic::DiagnosticArgs{symbol->getName()},
                               location);
    break;
  }
}

bool defineImportedSymbol(
    binding::BinderContext &binder_context,
    const std::shared_ptr<analysis::Symbol> &symbol,
    const flow_wing::diagnostic::SourceLocation &location) {
  if (binder_context.getSymbolTable()->define(symbol)) {
    symbol->setImportedViaBring(true);
    return true;
  }
  reportDuplicateImportedName(binder_context, symbol, location);
  return false;
}

} // namespace

void analysis::DeclarationAnalyzer::visit(syntax::BringStatementSyntax *node) {

  const std::string raw_path = node->getStringLiteralExpression()->getValue();
  std::filesystem::path path_obj(raw_path);
  std::string absolute_file_path;
  if (path_obj.is_absolute()) {
    absolute_file_path = std::filesystem::absolute(path_obj).string();
  } else {
    const std::string &main_path =
        m_binder_context.getCompilationContext().getAbsoluteSourceFilePath();
    const std::filesystem::path base =
        std::filesystem::path(main_path).parent_path();
    if (auto resolved = tryResolveBringPath(base, path_obj)) {
      absolute_file_path = *resolved;
    } else {
      const auto modules_root = flow_wing::io::PathUtils::getModulesPath();
      std::error_code ec_mod;
      if (!modules_root.empty() &&
          std::filesystem::exists(modules_root, ec_mod) && !ec_mod) {
        if (auto resolved = tryResolveBringPath(modules_root, path_obj)) {
          absolute_file_path = *resolved;
        } else {
          absolute_file_path = std::filesystem::absolute(base / path_obj).string();
        }
      } else {
        absolute_file_path = std::filesystem::absolute(base / path_obj).string();
      }
    }
  }

  {
    std::error_code ec;
    const bool exists = std::filesystem::exists(absolute_file_path, ec);
    const bool regular =
        exists && std::filesystem::is_regular_file(absolute_file_path, ec);
    if (!exists || ec || !regular) {
      m_binder_context.reportError(
          flow_wing::diagnostic::DiagnosticCode::kFileNotFound,
          {absolute_file_path},
          node->getStringLiteralExpression()->getSourceLocation());
      return;
    }
  }

  if (std::find(g_bring_path_stack.begin(), g_bring_path_stack.end(),
                absolute_file_path) != g_bring_path_stack.end()) {
    m_binder_context.reportError(
        diagnostic::DiagnosticCode::kCircularReference, {absolute_file_path},
        node->getStringLiteralExpression()->getSourceLocation());
    return;
  }

  g_bring_path_stack.push_back(absolute_file_path);
  struct BringStackPop {
    ~BringStackPop() {
      if (!g_bring_path_stack.empty()) {
        g_bring_path_stack.pop_back();
      }
    }
  } bring_stack_pop;

  CompilerOptions nested_opts;
  nested_opts.input_file_path = absolute_file_path;
  std::string entry_file_path = m_binder_context.getCompilationContext().getEntryFilePath();

  flow_wing::CompilationContext nested_ctx(nested_opts, entry_file_path);
  flow_wing::compiler::pipeline::CompilationPipeline pipeline;
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::SourceLoaderPass>());
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::LexerPass>());
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::ParsingPass>());
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::SemanticAnalysisPass>());

  auto pipeline_status = pipeline.run(nested_ctx);

  if (pipeline_status ==
      flow_wing::compiler::pipeline::ReturnStatus::kFailure) {
    // Nested compile already recorded CircularReference on its binder;
    // re-report on the parent so the user-visible error is not masked by
    // FileContainsErrors.
    if (nestedDiagnosticsHasCircularReference(nested_ctx)) {
      m_binder_context.reportError(
          diagnostic::DiagnosticCode::kCircularReference, {absolute_file_path},
          node->getStringLiteralExpression()->getSourceLocation());
      return;
    }
    m_binder_context.reportError(
        diagnostic::DiagnosticCode::kFileContainsErrors, {absolute_file_path},
        node->getStringLiteralExpression()->getSourceLocation());
    return;
  }

  // Record sources to compile to .o later in IR generation (non-reentrant).
  auto &root_ctx = m_binder_context.getCompilationContext();
  for (const auto &p : nested_ctx.getBroughtSourcePaths()) {
    root_ctx.addBroughtSourceFile(p);
  }
  root_ctx.addBroughtSourceFile(absolute_file_path);

  const auto &bound_tree = nested_ctx.getBoundTree();
  if (!bound_tree) {
    return;
  }

  auto imported_table = bound_tree->getSymbolTable();
  if (!imported_table) {
    return;
  }

  const auto &bring_path_loc =
      node->getStringLiteralExpression()->getSourceLocation();

  const auto &identifier_expressions = node->getIdentifierExpressions();
  if (!identifier_expressions.empty()) {
    // bring { a, b, c } from "file.fg"
    for (const auto &expr : identifier_expressions) {
      if (!expr || expr->getKind() != syntax::NodeKind::kIdentifierExpression) {
        continue;
      }
      auto *id_expr =
          static_cast<syntax::IdentifierExpressionSyntax *>(expr.get());
      const std::string &name = id_expr->getValue();
      auto symbol = imported_table->lookupInGlobalScope(name);
      if (!symbol) {
        m_binder_context.reportError(
            diagnostic::DiagnosticCode::kIdentifierNotFoundInFileOrModule,
            diagnostic::DiagnosticArgs{name, absolute_file_path},
            id_expr->getSourceLocation());
        continue;
      }
      // Names brought into that file from a nested `bring` are not re-exported.
      if (symbol->isImportedViaBring()) {
        m_binder_context.reportError(
            diagnostic::DiagnosticCode::kIdentifierNotFoundInFileOrModule,
            diagnostic::DiagnosticArgs{name, absolute_file_path},
            id_expr->getSourceLocation());
        continue;
      }
      defineImportedSymbol(m_binder_context, symbol,
                           id_expr->getSourceLocation());
    }
  } else {
    // bring "file.fg" — merge globals **defined** in that file only (not
    // symbols it obtained via its own nested `bring`). Use `bring { name } from
    // "f.fg"` for a subset.
    imported_table->forEachGlobalSymbol(
        [&](const std::string &name,
            const std::shared_ptr<analysis::Symbol> &symbol) {
          if (analysis::Builtins::isBuiltInFunction(name) ||
              analysis::Builtins::isBuiltInType(name) ||
              analysis::Builtins::isCompilerInternalFunction(name)) {
            return;
          }
          if (symbol->isImportedViaBring()) {
            return;
          }
          defineImportedSymbol(m_binder_context, symbol, bring_path_loc);
        });
  }
}
} // namespace flow_wing
