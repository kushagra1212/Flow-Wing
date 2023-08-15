#include "BoundLiteralExpression.h"

template class BoundLiteralExpression<std::any>;
template class BoundLiteralExpression<int>;
template class BoundLiteralExpression<double>;
template class BoundLiteralExpression<bool>;
template class BoundLiteralExpression<std::string>;
template class BoundLiteralExpression<char>;

template <typename T>
BoundLiteralExpression<T>::BoundLiteralExpression(std::string lineAndColumn,
                                                  T value) {
  this->value = value;
  this->_lineAndColumn = lineAndColumn;
}

template <typename T>
const std::type_info &BoundLiteralExpression<T>::getType() {
  const std::type_info &type1 = typeid(this->value);
  return type1;
}

template <typename T> T BoundLiteralExpression<T>::getValue() { return value; }

template <typename T>
BinderKindUtils::BoundNodeKind BoundLiteralExpression<T>::getKind() const {
  return BinderKindUtils::BoundNodeKind::LiteralExpression;
}

template <typename T>
std::vector<BoundNode *> BoundLiteralExpression<T>::getChildren() {
  return this->_children;
}
template <typename T>
std::string BoundLiteralExpression<T>::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
