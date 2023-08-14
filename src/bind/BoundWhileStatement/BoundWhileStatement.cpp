#include "BoundWhileStatement.h"

BoundWhileStatement::BoundWhileStatement(

    const std::string &lineAndColumn,
    std::shared_ptr<BoundExpression> condition,
    std::shared_ptr<BoundStatement> body)
    : _condition(condition), _body(body) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundWhileStatement::getKind() {

  return BinderKindUtils::BoundNodeKind::WhileStatement;
}

std::shared_ptr<BoundExpression> BoundWhileStatement::getCondition() const {
  return _condition;
}

std::shared_ptr<BoundStatement> BoundWhileStatement::getBody() const {
  return _body;
}

std::vector<std::shared_ptr<BoundNode>> BoundWhileStatement::getChildren() {
  std::vector<std::shared_ptr<BoundNode>> children;
  children.push_back(_condition);
  children.push_back(_body);
  return children;
}

std::string BoundWhileStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
