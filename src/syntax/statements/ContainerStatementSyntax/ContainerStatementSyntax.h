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
  std::unique_ptr<SyntaxToken<std::any>> _keyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifierToken;
  std::unique_ptr<ExpressionSyntax> _containerSizeExpression;
  std::vector<std::unique_ptr<ExpressionSyntax>> _values;
  Utils::type _type;

public:
  ContainerStatementSyntax() = default;

  // Overrides
  std::vector<SyntaxNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() const override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  auto setValue(std::unique_ptr<ExpressionSyntax> values) -> void;
  auto
  setIdentifierToken(std::unique_ptr<SyntaxToken<std::any>> identifierToken)
      -> void;
  auto setType(Utils::type type) -> void;
  auto setContainerSizeExpression(std::unique_ptr<ExpressionSyntax> item)
      -> void;
  auto setKeyword(std::unique_ptr<SyntaxToken<std::any>> keyword) -> void;

  // Getters
  const std::unique_ptr<SyntaxToken<std::any>> &getIdentifierTokenRef() const;
  const std::vector<std::unique_ptr<ExpressionSyntax>> &getValuesRef() const;
  const std::unique_ptr<ExpressionSyntax> &
  getContainerSizeExpressionRef() const;
  const Utils::type &getType() const;
};

#endif // __CONTAINER_STATEMENT_SYNTAX_H__