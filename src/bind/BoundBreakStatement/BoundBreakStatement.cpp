#include "BoundBreakStatement.h"

BoundBreakStatement::BoundBreakStatement(std::string lineAndColumn) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundBreakStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BreakStatement;
}

std::vector<BoundNode *> BoundBreakStatement::getChildren() {
  return this->_children;
}

std::string BoundBreakStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
