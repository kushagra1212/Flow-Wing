#include "IfStatementSyntax.h"

IfStatementSyntax::IfStatementSyntax() {}

std::unique_ptr<SyntaxToken<std::any>> IfStatementSyntax::getIfKeyword() {
  return std::move(ifKeyword);
}

std::unique_ptr<ExpressionSyntax> IfStatementSyntax::getCondition() {
  return std::move(condition);
}

std::unique_ptr<BlockStatementSyntax> IfStatementSyntax::getStatement() {
  return std::move(statement);
}

std::unique_ptr<ElseClauseSyntax> IfStatementSyntax::getElseClause() {
  return std::move(elseClause);
}

const SyntaxKindUtils::SyntaxKind IfStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::IfStatement;
}

const DiagnosticUtils::SourceLocation
IfStatementSyntax::getSourceLocation() const {
  return this->ifKeyword->getSourceLocation();
}

const std::vector<SyntaxNode *> &IfStatementSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(this->ifKeyword.get());
    _children.push_back(this->condition.get());
    _children.push_back(this->statement.get());

    for (auto &orIfStatement : this->orIfStatements) {
      _children.push_back(orIfStatement.get());
    }

    if (this->elseClause != nullptr) {
      _children.push_back(this->elseClause.get());
    }
  }

  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &IfStatementSyntax::getIfKeywordRef() {
  return this->ifKeyword;
}
std::unique_ptr<ExpressionSyntax> &IfStatementSyntax::getConditionRef() {
  return this->condition;
}
std::unique_ptr<BlockStatementSyntax> &IfStatementSyntax::getStatementRef() {
  return this->statement;
}
std::unique_ptr<ElseClauseSyntax> &IfStatementSyntax::getElseClauseRef() {
  return this->elseClause;
}

void IfStatementSyntax::addIfKeyword(
    std::unique_ptr<SyntaxToken<std::any>> ifKeyword) {
  this->ifKeyword = std::move(ifKeyword);
}

void IfStatementSyntax::addCondition(
    std::unique_ptr<ExpressionSyntax> condition) {
  this->condition = std::move(condition);
}

void IfStatementSyntax::addStatement(
    std::unique_ptr<BlockStatementSyntax> statement) {
  this->statement = std::move(statement);
}

void IfStatementSyntax::addOrIfStatement(
    std::unique_ptr<OrIfStatementSyntax> orIfStatement) {
  this->orIfStatements.push_back(std::move(orIfStatement));
}
void IfStatementSyntax::addElseClause(
    std::unique_ptr<ElseClauseSyntax> elseClause) {
  this->elseClause = std::move(elseClause);
}
std::vector<std::unique_ptr<OrIfStatementSyntax>> &
IfStatementSyntax::getOrIfStatementsRef() {
  return this->orIfStatements;
}