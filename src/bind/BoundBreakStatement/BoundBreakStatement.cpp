#include "BoundBreakStatement.h"

BoundBreakStatement::BoundBreakStatement(const std::string &lineAndColumn) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundBreakStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BreakStatement;
}

std::vector<std::shared_ptr<BoundNode>> BoundBreakStatement::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{};
}

std::string BoundBreakStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
