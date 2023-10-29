#include "BoundBlockStatement.h"
BoundBlockStatement::BoundBlockStatement(
    const DiagnosticUtils::SourceLocation &location, bool global)
    : BoundSourceLocation(location) {
  this->_global = global;
}
BoundBlockStatement::BoundBlockStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {
  BoundBlockStatement(location, false);
}

std::vector<std::unique_ptr<BoundStatement>> &
BoundBlockStatement::getStatements() {
  return _statements;
}

void BoundBlockStatement::addStatement(
    std::unique_ptr<BoundStatement> statement) {
  this->_statements.push_back(std::move(statement));
}

bool BoundBlockStatement::getGlobal() const { return this->_global; }

BinderKindUtils::BoundNodeKind BoundBlockStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BlockStatement;
}

std::vector<BoundNode *> BoundBlockStatement::getChildren() {
  if (this->_children.size() == 0) {
    for (const auto &st : this->_statements) {
      this->_children.push_back((BoundNode *)(st.get()));
    }
  }
  return this->_children;
}
