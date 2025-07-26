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

#include "src/syntax/expression/ExpressionSyntax.h"

class AssignmentExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<ExpressionSyntax> _left;
  std::unique_ptr<ExpressionSyntax> _right;
  SyntaxKindUtils::SyntaxKind _operatorTokenKind;
  bool _needDefaultInitialize = false;

public:
  AssignmentExpressionSyntax(std::unique_ptr<ExpressionSyntax> left,
                             SyntaxKindUtils::SyntaxKind operatorTokenKind,
                             std::unique_ptr<ExpressionSyntax> right,
                             bool needDefaultInitialize = false);

  std::unique_ptr<ExpressionSyntax> getRight();
  std::unique_ptr<ExpressionSyntax> getLeft();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<ExpressionSyntax> &getRightRef();
  std::unique_ptr<ExpressionSyntax> &getLeftRef();

  auto inline getNeedDefaultInitialization() -> bool {
    return _needDefaultInitialize;
  }

  inline auto getOperatorTokenKind() const -> SyntaxKindUtils::SyntaxKind {
    return _operatorTokenKind;
  }
};
