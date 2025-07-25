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


#ifndef __FLOW__WING__VARIABLE_H__
#define __FLOW__WING__VARIABLE_H__

#include "../../../common/Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../TypeExpressionSyntax/TypeExpressionSyntax.h"

class VariableExpressionSyntax : public ExpressionSyntax {
public:
  VariableExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression,
      const bool isConstant,
      std::unique_ptr<TypeExpressionSyntax> variableTypeExpr);

  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation
  getSourceLocation() const override;

  inline void
  addDotExpression(std::unique_ptr<ExpressionSyntax> dotExpression) {
    _dotExpressionList.push_back(std::move(dotExpression));
  }

  inline auto getDotExpressionList() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _dotExpressionList;
  }

  inline auto getIdentifierTokenRef() const
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return _identifierExpression;
  }

  inline auto getVariableTypeExprRef() const
      -> const std::unique_ptr<TypeExpressionSyntax> & {
    return _variableTypeExpr;
  }

  inline auto
  setVariableTypeExprRef(std::unique_ptr<TypeExpressionSyntax> variableTypeExpr)
      -> void {
    _variableTypeExpr = std::move(variableTypeExpr);
  }

  inline auto setNewKeyword(std::unique_ptr<SyntaxToken<std::any>> newKeyword)
      -> void {
    _hasNewKeyword = true;
    _newKeyword = std::move(newKeyword);
  }

  inline auto isConstant() const -> const bool & { return _isConstant; }

  inline auto getVariableName() const -> std::string {
    return std::any_cast<std::string>(
        _identifierExpression->getTokenPtr()->getText());
  }
  inline auto getHasNewKeyword() -> bool { return _hasNewKeyword; }
  inline auto getIsSelf() -> bool { return _selfKeyword != nullptr; }

  inline auto setSelfKeyword(std::unique_ptr<SyntaxToken<std::any>> selfKeyword)
      -> void {
    _selfKeyword = std::move(selfKeyword);
  }
  inline auto setModuleNameorCallExpression(
      std::unique_ptr<ExpressionSyntax> moduleNameorCallExpression) -> void {
    _moduleNameorCallExpression = std::move(moduleNameorCallExpression);
  }

  inline auto getModuleNameorCallExpression() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _moduleNameorCallExpression;
  }
  inline auto hasModuleNameorCallExpression() const -> bool {
    return _moduleNameorCallExpression != nullptr;
  }

private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;
  std::unique_ptr<SyntaxToken<std::any>> _newKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _selfKeyword;
  std::unique_ptr<TypeExpressionSyntax> _variableTypeExpr;
  std::vector<std::unique_ptr<ExpressionSyntax>> _dotExpressionList;

  std::unique_ptr<ExpressionSyntax> _moduleNameorCallExpression;

  bool _isConstant;
  bool _hasNewKeyword = false;
};

#endif // __FLOW__WING__VARIABLE_H__