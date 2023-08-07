#include "BoundBreakStatement.h"

BoundBreakStatement::BoundBreakStatement(BreakStatementSyntax *syntax)
    : _syntax(syntax) {}

BoundBreakStatement::~BoundBreakStatement() {
  if (_syntax != nullptr) {
    delete _syntax;
    _syntax = nullptr;
  }
}

BinderKindUtils::BoundNodeKind BoundBreakStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BreakStatement;
}

std::vector<BoundNode *> BoundBreakStatement::getChildren() {
  return std::vector<BoundNode *>{};
}

BreakStatementSyntax *BoundBreakStatement::getBreakStatement() const {
  return _syntax;
}
