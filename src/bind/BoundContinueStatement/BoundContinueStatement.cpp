#include "BoundContinueStatement.h"

BoundContinueStatement::BoundContinueStatement(std::string lineAndColumn) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundContinueStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ContinueStatement;
}

std::vector<BoundNode *> BoundContinueStatement::getChildren() {
  return this->_children;
}

std::string BoundContinueStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
