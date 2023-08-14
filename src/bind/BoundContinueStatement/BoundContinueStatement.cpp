#include "BoundContinueStatement.h"

BoundContinueStatement::BoundContinueStatement(
    const std::string &lineAndColumn) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundContinueStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ContinueStatement;
}

std::vector<std::shared_ptr<BoundNode>> BoundContinueStatement::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{};
}

std::string BoundContinueStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
