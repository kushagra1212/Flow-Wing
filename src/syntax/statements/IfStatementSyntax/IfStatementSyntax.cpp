#include "IfStatementSyntax.h"

IfStatementSyntax::IfStatementSyntax(SyntaxToken<std::any> *ifKeyword,
                                     ExpressionSyntax *condition,
                                     BlockStatementSyntax *statement,
                                     ElseClauseSyntax *elseClause)
    : ifKeyword(ifKeyword), condition(condition), statement(statement),
      elseClause(elseClause) {}

SyntaxToken<std::any> *IfStatementSyntax::getIfKeyword() const {
  return ifKeyword;
}

ExpressionSyntax *IfStatementSyntax::getCondition() const { return condition; }

BlockStatementSyntax *IfStatementSyntax::getStatement() const {
  return statement;
}

ElseClauseSyntax *IfStatementSyntax::getElseClause() const {
  return elseClause;
}

SyntaxKindUtils::SyntaxKind IfStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::IfStatement;
}

std::string IfStatementSyntax::getLineNumberAndColumn() const {
  return ifKeyword->getLineNumberAndColumn();
}

std::vector<SyntaxNode *> IfStatementSyntax::getChildren() {
  std::vector<SyntaxNode *> children = {ifKeyword, condition,
                                        (SyntaxNode *)statement};
  if (elseClause != nullptr) {
    children.push_back(elseClause);
  }
  return children;
}

IfStatementSyntax::~IfStatementSyntax() {
  if (ifKeyword != nullptr) {
    delete ifKeyword;
    ifKeyword = nullptr;
  }

  if (condition != nullptr) {
    delete condition;
    condition = nullptr;
  }

  if (statement != nullptr) {
    delete statement;
    statement = nullptr;
  }

  if (elseClause != nullptr) {
    delete elseClause;
    elseClause = nullptr;
  }
}
