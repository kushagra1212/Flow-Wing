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


#include "FunctionTypeExpressionSyntax.h"

FunctionTypeExpressionSyntax::FunctionTypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : TypeExpressionSyntax(std::move(type)) {}

const SyntaxKindUtils::SyntaxKind
FunctionTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FunctionTypeExpression;
}

const std::vector<SyntaxNode *> &FunctionTypeExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (this->_openBracketToken)
    _children.push_back(_openBracketToken.get());

  if (this->_openParenthesisToken)
    _children.push_back(_openParenthesisToken.get());

  for (auto &parameterType : _parameterTypes)
    _children.push_back(parameterType.get());

  for (auto &asType : _asParametersKeywords) {
    _children.push_back(asType.second.get());
  }

  if (this->_closeParenthesisToken)
    _children.push_back(_closeParenthesisToken.get());

  if (this->_asKeyword)
    _children.push_back(_asKeyword.get());

  for (auto &returnType : _returnTypes) {
    _children.push_back(returnType.get());
  }

  if (this->_closeBracketToken)
    _children.push_back(_closeBracketToken.get());

  return _children;
}

const DiagnosticUtils::SourceLocation
FunctionTypeExpressionSyntax::getSourceLocation() const {

  if (_openParenthesisToken)
    return _openParenthesisToken->getSourceLocation();

  for (auto &parameterType : _parameterTypes) {
    if (parameterType)
      return parameterType->getSourceLocation();
  }
  for (auto &asType : _asParametersKeywords) {
    return (asType.second->getSourceLocation());
  }

  if (_closeParenthesisToken)
    return _closeParenthesisToken->getSourceLocation();

  if (_asKeyword)
    return _asKeyword->getSourceLocation();

  for (auto &returnType : _returnTypes)
    return returnType->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}