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
#include <iostream>
#include <typeinfo>

#include "../BoundExpression/BoundExpression.h"

template <typename T> class BoundLiteralExpression : public BoundExpression {
private:
  T value;
  SyntaxKindUtils::SyntaxKind _syntaxKind;

public:
  BoundLiteralExpression(const DiagnosticUtils::SourceLocation &location,
                         T value);

  BoundLiteralExpression(const DiagnosticUtils::SourceLocation &location,
                         T value, SyntaxKindUtils::SyntaxKind syntaxKind);

  const std::type_info &getType() override;

  T getValue();

  void setValue(T value);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getSyntaxKind();
};

template <typename T>
BoundLiteralExpression<T>::BoundLiteralExpression(
    const DiagnosticUtils::SourceLocation &location, T value)
    : BoundExpression(location) {
  this->value = value;
}
template <typename T>
BoundLiteralExpression<T>::BoundLiteralExpression(
    const DiagnosticUtils::SourceLocation &location, T value,
    SyntaxKindUtils::SyntaxKind syntaxKind)
    : BoundLiteralExpression(location, value) {
  this->_syntaxKind = syntaxKind;
}
template <typename T>
const std::type_info &BoundLiteralExpression<T>::getType() {
  const std::type_info &type1 = typeid(this->value);
  return type1;
}

template <typename T> T BoundLiteralExpression<T>::getValue() { return value; }

template <typename T> void BoundLiteralExpression<T>::setValue(T value) {

  this->value = value;
}

template <typename T>
BinderKindUtils::BoundNodeKind BoundLiteralExpression<T>::getKind() const {
  return BinderKindUtils::BoundNodeKind::LiteralExpression;
}

template <typename T>
std::vector<BoundNode *> BoundLiteralExpression<T>::getChildren() {
  return this->_children;
}

template <typename T>
SyntaxKindUtils::SyntaxKind BoundLiteralExpression<T>::getSyntaxKind() {
  return this->_syntaxKind;
}