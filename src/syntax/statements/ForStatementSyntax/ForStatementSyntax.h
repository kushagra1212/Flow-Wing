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
  std::shared_ptr<StatementSyntax> _initialization;
  std::shared_ptr<BlockStatementSyntax> _statement;
  std::shared_ptr<ExpressionSyntax> _upperBound;

public:
  ForStatementSyntax(std::shared_ptr<StatementSyntax> initialization,
                     std::shared_ptr<ExpressionSyntax> upperBound,
                     std::shared_ptr<BlockStatementSyntax> statement);

  std::shared_ptr<BlockStatementSyntax> getStatement() const;

  std::shared_ptr<StatementSyntax> getInitialization() const;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::shared_ptr<ExpressionSyntax> getUpperBound() const;

  std::string getLineNumberAndColumn() const override;
};

#endif // FOR_STATEMENT_SYNTAX_H