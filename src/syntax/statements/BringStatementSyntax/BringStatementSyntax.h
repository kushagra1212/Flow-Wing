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

#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <any>
#include <memory>
#include <vector>

template <typename T> class SyntaxToken;
template <typename T> class LiteralExpressionSyntax;
class CompilationUnitSyntax;

namespace FlowWing {
class DiagnosticHandler;
}
class BringStatementSyntax : public StatementSyntax {
  std::vector<std::unique_ptr<LiteralExpressionSyntax<std::any>>> expressions;
  std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler;
  std::unique_ptr<SyntaxToken<std::any>> _openBraceToken;
  std::unique_ptr<SyntaxToken<std::any>> _pathToken;
  std::string absoluteFilePath;
  std::string relativeFilePath;
  std::unique_ptr<SyntaxToken<std::any>> _bringKeyword;
  std::unique_ptr<CompilationUnitSyntax> _compilationUnit;
  bool _isModuleImport = false;
  std::string _moduleName = "";

public:
  void
  addExpression(std::unique_ptr<LiteralExpressionSyntax<std::any>> expression);
  void addBringKeyword(std::unique_ptr<SyntaxToken<std::any>> bringKeyword);

  void addOpenBraceToken(std::unique_ptr<SyntaxToken<std::any>> openBraceToken);
  void addPathToken(std::unique_ptr<SyntaxToken<std::any>> pathToken);
  void setAbsoluteFilePath(const std::string &absoluteFilePath);
  void setDiagnosticHandler(
      std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler);
  void setRelativeFilePath(const std::string &relativeFilePath);
  void
  setCompilationUnit(std::unique_ptr<CompilationUnitSyntax> compilationUnit);

  const std::string &getAbsoluteFilePath() const;

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  const std::vector<std::unique_ptr<LiteralExpressionSyntax<std::any>>> &
  getExpressionsPtr();
  const std::unique_ptr<CompilationUnitSyntax> &getCompilationUnitPtr();

  inline auto setModuleName(const std::string &moduleName) -> void {
    _moduleName = moduleName;
  }

  const bool getIsChoosyImportPtr();
  const std::string &getAbsoluteFilePathPtr();
  std::unique_ptr<FlowWing::DiagnosticHandler> &getDiagnosticHandlerPtr();
  const std::string &getRelativeFilePathPtr();
  const std::unique_ptr<SyntaxToken<std::any>> &getBringKeywordPtr();

  const std::unique_ptr<SyntaxToken<std::any>> &getPathTokenPtr();

  inline auto setIsModuleImport(const bool &isModuleImport) -> void {
    _isModuleImport = isModuleImport;
  }

  inline auto getIsModuleImport() -> bool { return _isModuleImport; }

  inline auto getModuleName() -> std::string { return _moduleName; }
};
