#include "BoundContinueStatement.h"

BoundContinueStatement::BoundContinueStatement(
    const std::string &lineAndColumn) {
  this->_lineAndColumn = lineAndColumn;
}
BoundContinueStatement::~BoundContinueStatement() = default;

BinderKindUtils::BoundNodeKind BoundContinueStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ContinueStatement;
}

std::vector<BoundNode *> BoundContinueStatement::getChildren() {
  return std::vector<BoundNode *>{};
}

std::string BoundContinueStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
