#ifndef FOR_STATEMENT_SYNTAX_H
#define FOR_STATEMENT_SYNTAX_H
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../VariableDeclarationSyntax/VariableDeclarationSyntax.h"

class ForStatementSyntax : public StatementSyntax {

public:
  ForStatementSyntax(VariableDeclarationSyntax *variableDeclaration,
                     ExpressionSyntax *upperBound,
                     BlockStatementSyntax *statement);

  BlockStatementSyntax *getStatement() const;

  VariableDeclarationSyntax *getVariableDeclaration() const;

  std::vector<SyntaxNode *> getChildren() override;

  SyntaxKindUtils::SyntaxKind getKind() override;

  ExpressionSyntax *getUpperBound() const;

private:
  VariableDeclarationSyntax *variableDeclaration;
  BlockStatementSyntax *statement;
  ExpressionSyntax *upperBound;
};

#endif // FOR_STATEMENT_SYNTAX_H