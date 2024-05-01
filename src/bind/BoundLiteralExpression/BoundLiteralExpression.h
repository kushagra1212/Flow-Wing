#pragma once
#include <any>
#include <iostream>
#include <typeinfo>

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

template <typename T>
class BoundLiteralExpression : public BoundExpression {
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

template <typename T>
T BoundLiteralExpression<T>::getValue() {
  return value;
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