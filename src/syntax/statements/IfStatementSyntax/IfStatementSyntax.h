#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../ElseClauseSyntax/ElseClauseSyntax.h"
#include "../StatementSyntax.h"
class IfStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> ifKeyword;
  std::unique_ptr<ExpressionSyntax> condition;
  std::unique_ptr<BlockStatementSyntax> statement;
  std::unique_ptr<ElseClauseSyntax> elseClause;

public:
  IfStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> ifKeyword,
                    std::unique_ptr<ExpressionSyntax> condition,
                    std::unique_ptr<BlockStatementSyntax> statement,
                    std::unique_ptr<ElseClauseSyntax> elseClause);

  std::unique_ptr<SyntaxToken<std::any>> getIfKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getStatement();
  std::unique_ptr<ElseClauseSyntax> getElseClause();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};
