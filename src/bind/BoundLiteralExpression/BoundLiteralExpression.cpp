#include "BoundLiteralExpression.h"

template class BoundLiteralExpression<std::any>;
template class BoundLiteralExpression<int>;
template class BoundLiteralExpression<double>;
template class BoundLiteralExpression<bool>;
template class BoundLiteralExpression<std::string>;
template class BoundLiteralExpression<char>;

template <typename T>
BoundLiteralExpression<T>::BoundLiteralExpression(T value) {
  this->value = value;
}

template <typename T>
BinderKindUtils::BoundNodeKind BoundLiteralExpression<T>::getKind() {
  return BinderKindUtils::BoundNodeKind::LiteralExpression;
}

template <typename T>
const std::type_info &BoundLiteralExpression<T>::getType() {
  const std::type_info &type1 = typeid(this->value);
  return type1;
}

template <typename T> T BoundLiteralExpression<T>::getValue() { return value; }

template <typename T> BoundLiteralExpression<T>::~BoundLiteralExpression() {}
