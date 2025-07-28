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

#include "FunctionDeclarationSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getFunctionKeyword() {
  return std::move(_functionKeyword);
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getIdentifierToken() {
  return std::move(_identifierToken);
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getOpenParenthesisToken() {
  return std::move(_openParenthesisToken);
}

std::unique_ptr<SyntaxToken<std::any>>
FunctionDeclarationSyntax::getCloseParenthesisToken() {
  return std::move(_closeParenthesisToken);
}

std::unique_ptr<BlockStatementSyntax> FunctionDeclarationSyntax::getBody() {
  return std::move(_body);
}

SyntaxKindUtils::SyntaxKind FunctionDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax;
}

const DiagnosticUtils::SourceLocation
FunctionDeclarationSyntax::getSourceLocation() const {
  if (_exposedKeyword)
    return _exposedKeyword->getSourceLocation();
  if (_functionKeyword)
    return _functionKeyword->getSourceLocation();
  if (_identifierToken)
    return _identifierToken->getSourceLocation();

  if (_openParenthesisToken)
    return _openParenthesisToken->getSourceLocation();
  if (_closeParenthesisToken)
    return _closeParenthesisToken->getSourceLocation();

  if (_asKeyword)
    return _asKeyword->getSourceLocation();

  if (_declKeyword)
    return _declKeyword->getSourceLocation();

  if (_body)
    return _body->getSourceLocation();

  for (const auto &expr : _returnTypeExpressionList)
    return expr->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}

const std::vector<SyntaxNode *> &FunctionDeclarationSyntax::getChildren() {
  if (this->_children.empty()) {
    // Add children
    if (_exposedKeyword)
      _children.push_back(_exposedKeyword.get());
    if (_functionKeyword)
      _children.push_back(_functionKeyword.get());
    if (_identifierToken)
      _children.push_back(_identifierToken.get());
    //? Not used
    // if (_openParenthesisToken)
    //   _children.push_back(_openParenthesisToken.get());

    for (size_t i = 0; i < _parameters.size(); i++) {
      _children.push_back(_parameters[i].get());

      //? Not used
      // if (i < _separators.size()) {
      //   _children.push_back(_separators[i].get());
      // }
    }
    //? Not used
    // _children.push_back(_closeParenthesisToken.get());

    if (_asKeyword)
      _children.push_back(_asKeyword.get());

    if (_declKeyword)
      _children.push_back(_declKeyword.get());

    if (_body)
      _children.push_back(_body.get());

    for (auto &expr : _returnTypeExpressionList)
      _children.push_back(expr.get());
  }
  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getFunctionKeywordPtr() {
  return _functionKeyword;
}
std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getIdentifierTokenPtr() {
  return _identifierToken;
}
std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getOpenParenthesisTokenPtr() {
  return _openParenthesisToken;
}
std::vector<std::unique_ptr<VariableDeclarationSyntax>> &
FunctionDeclarationSyntax::getParametersPtr() {
  return _parameters;
}

std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
FunctionDeclarationSyntax::getSeparatorsPtr() {
  return _separators;
}

std::unique_ptr<SyntaxToken<std::any>> &
FunctionDeclarationSyntax::getCloseParenthesisTokenPtr() {
  return _closeParenthesisToken;
}
std::unique_ptr<BlockStatementSyntax> &FunctionDeclarationSyntax::getBodyPtr() {
  return _body;
}

void FunctionDeclarationSyntax::setFunctionKeyword(
    std::unique_ptr<SyntaxToken<std::any>> functionKeyword) {
  _functionKeyword = std::move(functionKeyword);
}

void FunctionDeclarationSyntax::setIdentifierToken(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) {
  _identifierToken = std::move(identifierToken);
}

void FunctionDeclarationSyntax::setOpenParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) {
  _openParenthesisToken = std::move(openParenthesisToken);
}

void FunctionDeclarationSyntax::addParameter(
    std::unique_ptr<VariableDeclarationSyntax> parameter) {
  _parameters.push_back(std::move(parameter));
}

void FunctionDeclarationSyntax::setCloseParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  _closeParenthesisToken = std::move(closeParenthesisToken);
}

void FunctionDeclarationSyntax::setBody(
    std::unique_ptr<BlockStatementSyntax> body) {
  _body = std::move(body);
}

void FunctionDeclarationSyntax::addReturnExpression(
    std::unique_ptr<ExpressionSyntax> returnExpression) {
  _returnTypeExpressionList.push_back(std::move(returnExpression));
}

void FunctionDeclarationSyntax::addSeparator(
    std::unique_ptr<SyntaxToken<std::any>> separator) {
  _separators.push_back(std::move(separator));
}
