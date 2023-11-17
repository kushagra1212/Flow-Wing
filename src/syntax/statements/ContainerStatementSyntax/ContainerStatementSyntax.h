#ifndef __CONTAINER_STATEMENT_SYNTAX_H__
#define __CONTAINER_STATEMENT_SYNTAX_H__

#include "../../../utils/Utils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../StatementSyntax.h"

class ContainerStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;
  std::vector<std::unique_ptr<ExpressionSyntax>> _items;
  Utils::type _type;

public:
  ContainerStatementSyntax(
      Utils::type type,
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

  std::vector<SyntaxNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() const override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  void addItem(std::unique_ptr<ExpressionSyntax> item);

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &getIdentifierExpression();
  std::vector<std::unique_ptr<ExpressionSyntax>> &getItems();
  Utils::type getType() const;
};

#endif // __CONTAINER_STATEMENT_SYNTAX_H__