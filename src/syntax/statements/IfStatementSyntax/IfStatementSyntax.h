#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../ElseClauseSyntax/ElseClauseSyntax.h"
#include "../OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "../StatementSyntax.h"
class IfStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> ifKeyword;
  std::unique_ptr<ExpressionSyntax> condition;
  std::unique_ptr<BlockStatementSyntax> statement;
  std::unique_ptr<ElseClauseSyntax> elseClause;

  std::vector<std::unique_ptr<OrIfStatementSyntax>> orIfStatements;

 public:
  IfStatementSyntax();

  std::unique_ptr<SyntaxToken<std::any>> getIfKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getStatement();
  std::unique_ptr<ElseClauseSyntax> getElseClause();

  void addIfKeyword(std::unique_ptr<SyntaxToken<std::any>> ifKeyword);
  void addCondition(std::unique_ptr<ExpressionSyntax> condition);
  void addStatement(std::unique_ptr<BlockStatementSyntax> statement);
  void addOrIfStatement(std::unique_ptr<OrIfStatementSyntax> orIfStatement);
  void addElseClause(std::unique_ptr<ElseClauseSyntax> elseClause);

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getIfKeywordPtr();
  std::unique_ptr<ExpressionSyntax> &getConditionPtr();
  std::unique_ptr<BlockStatementSyntax> &getStatementPtr();
  std::unique_ptr<ElseClauseSyntax> &getElseClausePtr();
  std::vector<std::unique_ptr<OrIfStatementSyntax>> &getOrIfStatementsPtr();
};
