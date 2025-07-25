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
#include <any>
#include <string>

#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"

template <typename T> class LiteralExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _token;
  T _value;

public:
  LiteralExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> token,
                          T value);
  const std::string getKindText();
  const SyntaxKindUtils::SyntaxKind getSyntaxKind();
  const T &getValue();
  void setValue(T value);
  void setText(std::string text);

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getTokenPtr();
};

template <typename T>
LiteralExpressionSyntax<T>::LiteralExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> token, T value) {
  this->_token = std::move(token);
  this->_value = value;

  // Add children
}

template <typename T>
const SyntaxKindUtils::SyntaxKind LiteralExpressionSyntax<T>::getSyntaxKind() {
  return this->_token->getKind();
}

template <typename T>
const std::string LiteralExpressionSyntax<T>::getKindText() {
  return SyntaxKindUtils::to_string(this->getKind());
}

template <typename T> const T &LiteralExpressionSyntax<T>::getValue() {
  return this->_value;
}
template <typename T> void LiteralExpressionSyntax<T>::setValue(T value) {
  // this->_token->setValue(value);
  // if constexpr (std::is_same_v<T, std::string>) {
  //   this->_token->setText(value);
  // }
  this->_value = value;
}

template <typename T>
void LiteralExpressionSyntax<T>::setText(std::string text) {
  this->_token->setText(text);
}

template <typename T>
const SyntaxKindUtils::SyntaxKind LiteralExpressionSyntax<T>::getKind() const {
  return SyntaxKindUtils::SyntaxKind::LiteralExpression;
}
template <typename T>
const std::vector<SyntaxNode *> &LiteralExpressionSyntax<T>::getChildren() {
  if (_children.empty()) {
    this->_children.push_back(_token.get());
  }

  return this->_children;
}

template <typename T>
const DiagnosticUtils::SourceLocation
LiteralExpressionSyntax<T>::getSourceLocation() const {
  return this->_token->getSourceLocation();
}

template <typename T>
std::unique_ptr<SyntaxToken<std::any>> &
LiteralExpressionSyntax<T>::getTokenPtr() {
  return this->_token;
}
