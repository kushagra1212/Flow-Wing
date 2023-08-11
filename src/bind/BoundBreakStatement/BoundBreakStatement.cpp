#include "BoundBreakStatement.h"

BoundBreakStatement::BoundBreakStatement(const std::string &lineAndColumn) {
  this->_lineAndColumn = lineAndColumn;
}

BoundBreakStatement::~BoundBreakStatement() = default;

BinderKindUtils::BoundNodeKind BoundBreakStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BreakStatement;
}

std::vector<BoundNode *> BoundBreakStatement::getChildren() {
  return std::vector<BoundNode *>{};
}

std::string BoundBreakStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
