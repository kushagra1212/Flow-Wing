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

#include "CallExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"

CallExpressionSyntax::CallExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifier) {
  this->_identifier = std::move(identifier);
}

std::unique_ptr<LiteralExpressionSyntax<std::any>>
CallExpressionSyntax::getIdentifier() {
  return std::move(_identifier);
}

std::unique_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getOpenParenthesisToken() {
  return std::move(_openParenthesisToken);
}

std::vector<std::unique_ptr<ExpressionSyntax>> &
CallExpressionSyntax::getArguments() {
  return _arguments;
}
std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
CallExpressionSyntax::getSeparators() {
  return _separators;
}

void CallExpressionSyntax::setOpenParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) {
  this->_openParenthesisToken = std::move(openParenthesisToken);
}

void CallExpressionSyntax::addArgument(
    std::unique_ptr<ExpressionSyntax> argument) {
  this->_arguments.push_back(std::move(argument));
}

void CallExpressionSyntax::addSeparator(
    std::unique_ptr<SyntaxToken<std::any>> separator) {
  this->_separators.push_back(std::move(separator));
}

void CallExpressionSyntax::setCloseParenthesisToken(
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_closeParenthesisToken = std::move(closeParenthesisToken);
}

std::unique_ptr<SyntaxToken<std::any>>
CallExpressionSyntax::getCloseParenthesisToken() {
  return std::move(_closeParenthesisToken);
}

const SyntaxKindUtils::SyntaxKind CallExpressionSyntax::getKind() const {
  return SyntaxKindUtils::CallExpression;
}

const std::vector<SyntaxNode *> &CallExpressionSyntax::getChildren() {
  if (this->_children.size() == 0) {

    if (this->_newKeyword) {
      this->_children.emplace_back(_newKeyword.get());
    }
    this->_children.emplace_back(_identifier.get());

    //? Not used
    // this->_children.push_back(_openParenthesisToken.get());

    for (int i = 0; i < _arguments.size(); i++) {
      this->_children.emplace_back(_arguments[i].get());
      //? Not used
      // if (i < _separators.size()) {
      //   this->_children.push_back(_separators[i].get());
      // }
    }
    //? Not used
    // this->_children.push_back(_closeParenthesisToken.get());
  }
  return this->_children;
}

const DiagnosticUtils::SourceLocation
CallExpressionSyntax::getSourceLocation() const {
  return this->_identifier->getSourceLocation();
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
CallExpressionSyntax::getIdentifierPtr() {
  return _identifier;
}
std::unique_ptr<SyntaxToken<std::any>> &
CallExpressionSyntax::getOpenParenthesisTokenPtr() {
  return _openParenthesisToken;
}
std::unique_ptr<SyntaxToken<std::any>> &
CallExpressionSyntax::getCloseParenthesisTokenPtr() {
  return _closeParenthesisToken;
}
