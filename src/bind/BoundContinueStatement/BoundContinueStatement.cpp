#include "BoundContinueStatement.h"

BoundContinueStatement::BoundContinueStatement(ContinueStatementSyntax *syntax)
    : _syntax(syntax) {}

BoundContinueStatement::~BoundContinueStatement() {
  if (_syntax != nullptr) {
    delete _syntax;
    _syntax = nullptr;
  }
}

BinderKindUtils::BoundNodeKind BoundContinueStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ContinueStatement;
}

std::vector<BoundNode *> BoundContinueStatement::getChildren() {
  return std::vector<BoundNode *>{};
}

ContinueStatementSyntax *BoundContinueStatement::getContinueStatement() const {
  return _syntax;
}
