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
  std::unique_ptr<ExpressionSyntax> _stepExpression;

 public:
  ForStatementSyntax(std::unique_ptr<StatementSyntax> initialization,
                     std::unique_ptr<ExpressionSyntax> upperBound,
                     std::unique_ptr<BlockStatementSyntax> statement,
                     std::unique_ptr<ExpressionSyntax> stepExpression);

  std::unique_ptr<BlockStatementSyntax> getStatement();
  std::unique_ptr<StatementSyntax> getInitialization();
  std::unique_ptr<ExpressionSyntax> getUpperBound();
  std::unique_ptr<ExpressionSyntax> getStepExpression();

  std::vector<SyntaxNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() const override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<BlockStatementSyntax> &getStatementPtr();
  std::unique_ptr<StatementSyntax> &getInitializationPtr();
  std::unique_ptr<ExpressionSyntax> &getUpperBoundPtr();
  std::unique_ptr<ExpressionSyntax> &getStepExpressionPtr();
};

#endif  // FOR_STATEMENT_SYNTAX_H