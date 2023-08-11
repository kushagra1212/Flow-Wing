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
  ForStatementSyntax(StatementSyntax *initialization,
                     ExpressionSyntax *upperBound,
                     BlockStatementSyntax *statement);

  ~ForStatementSyntax();

  BlockStatementSyntax *getStatement() const;

  StatementSyntax *getInitialization() const;

  std::vector<SyntaxNode *> getChildren() override;

  SyntaxKindUtils::SyntaxKind getKind() override;

  ExpressionSyntax *getUpperBound() const;

  std::string getLineNumberAndColumn() const override;

private:
  StatementSyntax *initialization;
  BlockStatementSyntax *statement;
  ExpressionSyntax *upperBound;
};

#endif // FOR_STATEMENT_SYNTAX_H