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

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
#include <llvm/IR/IRBuilder.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

namespace BinderKindUtils {
enum BoundBinaryOperatorKind : int;
}

class BoundBinaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _left;
  std::unique_ptr<BoundExpression> _right;
  llvm::AllocaInst *_dynamicValueVariableAddress = nullptr;

public:
  BoundBinaryExpression(const DiagnosticUtils::SourceLocation &location,
                        std::unique_ptr<BoundExpression> left,
                        BinderKindUtils::BoundBinaryOperatorKind op,
                        std::unique_ptr<BoundExpression> right);

  BinderKindUtils::BoundBinaryOperatorKind getOperator();

  std::unique_ptr<BoundExpression> getLeft();

  std::unique_ptr<BoundExpression> getRight();

  const std::type_info &getType() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getLeftPtr();

  std::unique_ptr<BoundExpression> &getRightPtr();

  llvm::AllocaInst *getDynamicValueVariableAddress();

  void
  setDynamicValueVariableAddress(llvm::AllocaInst *dynamicValueVariableAddress);
};
