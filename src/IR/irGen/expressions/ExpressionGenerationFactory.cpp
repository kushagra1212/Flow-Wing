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


#include "ExpressionGenerationFactory.h"

#include "AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "BinaryExpressionGenerationStrategy/BinaryExpressionGenerationStrategy.h"
#include "BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "IndexExpressionGenerationStrategy/IndexExpressionGenerationStrategy.h"
#include "LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "MultipleAssignmentExpressionGenerationStrategy/MultipleAssignmentExpressionGenerationStrategy.h"
#include "NirastExpressionGenerationStrategy/NirastExpressionGenerationStrategy.h"
#include "ParenthesizedExpressionGenerationStrategy/ParenthesizedExpressionGenerationStrategy.h"
#include "TernaryExpressionGenerationStrategy/TernaryExpressionGenerationStrategy.h"
#include "UnaryExpressionGenerationStrategy/UnaryExpressionGenerationStrategy.h"
#include "VariableExpressionGenerationStrategy/VariableExpressionGenerationStrategy.h"

ExpressionGenerationFactory::ExpressionGenerationFactory(
    CodeGenerationContext *context)
    : _codeGenerationContext(context){};

std::unique_ptr<ExpressionGenerationStrategy>
ExpressionGenerationFactory::createStrategy(
    BinderKindUtils::BoundNodeKind kind) {
  switch (kind) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression:
    return std::make_unique<LiteralExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::UnaryExpression:
    return std::make_unique<UnaryExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::VariableExpression:
    return std::make_unique<VariableExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::AssignmentExpression:
    return std::make_unique<AssignmentExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BinaryExpression:
    return std::make_unique<BinaryExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression:
    return std::make_unique<ParenthesizedExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::CallExpression:
    return std::make_unique<CallExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::IndexExpression:
    return std::make_unique<IndexExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BoundBracketedExpression:
    return std::make_unique<BracketedExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BoundNirastExpression:
    return std::make_unique<NirastExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BoundMultipleAssignmentExpression:
    return std::make_unique<MultipleAssignmentExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BoundTernaryExpression:
    return std::make_unique<TernaryExpressionGenerationStrategy>(
        _codeGenerationContext);
  default: {

    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Expression Type ");
    return nullptr;
  }
  }
}
