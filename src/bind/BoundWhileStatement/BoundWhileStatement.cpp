#include "BoundWhileStatement.h"

BoundWhileStatement::BoundWhileStatement(

    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> condition,
    std::unique_ptr<BoundStatement> body)
    : BoundSourceLocation(location), _condition(std::move(condition)),
      _body(std::move(body)) {

  this->_children.push_back(this->_condition.get());
  this->_children.push_back(this->_body.get());
}

std::unique_ptr<BoundExpression> BoundWhileStatement::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BoundStatement> BoundWhileStatement::getBody() {
  return std::move(_body);
}

BinderKindUtils::BoundNodeKind BoundWhileStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::WhileStatement;
}

std::vector<BoundNode *> BoundWhileStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundWhileStatement::getConditionPtr() {
  return this->_condition;
}
std::unique_ptr<BoundStatement> &BoundWhileStatement::getBodyPtr() {
  return this->_body;
}