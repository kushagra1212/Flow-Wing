#ifndef __FLOWWING_CONTAINER_EXPRESSION_SYNTAX_H__
#define __FLOWWING_CONTAINER_EXPRESSION_SYNTAX_H__

#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"

class ContainerExpressionSyntax : public ExpressionSyntax {
 private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _elements;

 public:
  // Overrides
  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  auto setElement(std::unique_ptr<ExpressionSyntax> element) -> void;

  // Getters
  auto getElementsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> &;
};

#endif  // __FLOWWING_CONTAINER_EXPRESSION_SYNTAX_H__
