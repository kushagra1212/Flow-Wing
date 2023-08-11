#include "BoundExpressionStatement.h"

BoundExpressionStatement::BoundExpressionStatement(
    const std::string &lineAndColumn, BoundExpression *expression) {

  this->expression = expression;
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundExpressionStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ExpressionStatement;
}

BoundExpression *BoundExpressionStatement::getExpression() {
  return expression;
}

std::vector<BoundNode *> BoundExpressionStatement::getChildren() {
  return std::vector<BoundNode *>{expression};
}

std::string BoundExpressionStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundExpressionStatement::~BoundExpressionStatement() {
  if (expression != nullptr) {
    delete expression;
    expression = nullptr;
  }
}
