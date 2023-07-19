#include "../StatementSyntax.h"
#include "../expression/ExpressionSyntax.h"

class ExpressionStatementSyntax : public StatementSyntax {
private:
  ExpressionSyntax *expression;

public:
  ExpressionStatementSyntax(ExpressionSyntax *expression);

  SyntaxKindUtils::SyntaxKind getKind() {
    return SyntaxKindUtils::SyntaxKind::ExpressionStatement;
  }

  std::vector<SyntaxNode *> getChildren() {
    return std::vector<SyntaxNode *>{this->expression};
  }
};