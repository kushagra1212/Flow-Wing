#ifndef FOR_STATEMENT_SYNTAX_H
#define FOR_STATEMENT_SYNTAX_H
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../VariableDeclarationSyntax/VariableDeclarationSyntax.h"

class ForStatementSyntax : public StatementSyntax {

private:
  std::unique_ptr<StatementSyntax> _initialization;
  std::unique_ptr<BlockStatementSyntax> _statement;
  std::unique_ptr<ExpressionSyntax> _upperBound;

public:
  ForStatementSyntax(std::unique_ptr<StatementSyntax> initialization,
                     std::unique_ptr<ExpressionSyntax> upperBound,
                     std::unique_ptr<BlockStatementSyntax> statement);

  std::unique_ptr<BlockStatementSyntax> getStatement();

  std::unique_ptr<StatementSyntax> getInitialization();

  std::unique_ptr<ExpressionSyntax> getUpperBound();

  std::vector<SyntaxNode *> getChildren() override;

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<BlockStatementSyntax> &getStatementPtr();

  std::unique_ptr<StatementSyntax> &getInitializationPtr();

  std::unique_ptr<ExpressionSyntax> &getUpperBoundPtr();
};

#endif // FOR_STATEMENT_SYNTAX_H