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

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "src/SemanticAnalyzer/BoundSourceLocation/BoundSourceLocation.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/MemoryNode.h"
#include <any>

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
#include <llvm/IR/DerivedTypes.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

class BoundMultipleVariableDeclaration;

class BoundVariableDeclaration : public BoundStatement,
                                 public BoundSourceLocation,
                                 public MemoryNode {
private:
  std::string _variableName;
  std::unique_ptr<BoundExpression> _initializer;
  std::unique_ptr<BoundLiteralExpression<std::any>> _identifier;
  bool _isConst;
  std::unique_ptr<BoundTypeExpression> _typeExp;
  bool _isExposed;
  bool _hasInOutKeyword = false;
  bool _hasAsKeyword = false;
  std::string _classItBelongsTo;
  BinderKindUtils::MemoryKind _memoryKind = BinderKindUtils::MemoryKind::None;
  std::pair<llvm::Value *, llvm::Type *> _llvmVariable;
  BoundMultipleVariableDeclaration *_parentMultipleVariableDeclaration =
      nullptr;

public:
  BoundVariableDeclaration(const DiagnosticUtils::SourceLocation &location,
                           const std::string &variableName, bool isConst,
                           bool isExposed);

  BinderKindUtils::MemoryKind getMemoryKind() const override;

  std::unique_ptr<BoundExpression> getInitializer();

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  bool isConst() const;

  std::unique_ptr<BoundExpression> &getInitializerPtr();

  const std::string &getVariableName() const;

  inline auto getTypeExpression() -> std::unique_ptr<BoundTypeExpression> & {
    return _typeExp;
  }

  inline auto isExposed() const -> bool { return _isExposed; }

  // Setters
  inline auto setInitializer(std::unique_ptr<BoundExpression> initializer)
      -> void {
    _initializer = std::move(initializer);
  }

  inline auto setHasInOutKeyword(bool hasInOutKeyword) {
    _hasInOutKeyword = hasInOutKeyword;
  }

  inline auto setMemoryKind(BinderKindUtils::MemoryKind memoryKind) {
    _memoryKind = memoryKind;
  }

  inline auto setClassItBelongsTo(const std::string &classItBelongsTo) {
    _classItBelongsTo = classItBelongsTo;
  }

  inline auto setHasAsKeyword(bool hasAsKeyword) {
    _hasAsKeyword = hasAsKeyword;
  }

  inline auto
  setLLVMVariable(std::pair<llvm::Value *, llvm::Type *> llvmVariable) {
    _llvmVariable = (llvmVariable);
  }

  inline auto
  setIdentifier(std::unique_ptr<BoundLiteralExpression<std::any>> identifier) {
    _identifier = std::move(identifier);
  }
  inline auto setTypeExpression(std::unique_ptr<BoundTypeExpression> typeExp) {
    _typeExp = std::move(typeExp);
  }

  inline auto getHasInOutKeyword() -> bool { return _hasInOutKeyword; }

  inline auto getIdentifierRef()
      -> std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return _identifier;
  }

  inline auto getClassItBelongsTo() -> const std::string & {
    return _classItBelongsTo;
  }

  inline auto getHasAsKeyword() -> bool { return _hasAsKeyword; }

  inline auto getLLVMVariable() -> std::pair<llvm::Value *, llvm::Type *> {
    return _llvmVariable;
  }

  inline auto setIsConst(bool isConst) { _isConst = isConst; }

  inline auto setIsExposed(bool isExposed) { _isExposed = isExposed; }

  inline auto setParentMultipleVariableDeclaration(
      BoundMultipleVariableDeclaration *parentMultipleVariableDeclaration) {
    _parentMultipleVariableDeclaration = parentMultipleVariableDeclaration;
  }

  inline auto getParentMultipleVariableDeclaration()
      -> BoundMultipleVariableDeclaration * {
    return _parentMultipleVariableDeclaration;
  }
};
