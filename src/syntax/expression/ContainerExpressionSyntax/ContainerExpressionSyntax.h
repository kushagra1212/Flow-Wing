#ifndef __FLOWWING_CONTAINER_EXPRESSION_SYNTAX_H__
#define __FLOWWING_CONTAINER_EXPRESSION_SYNTAX_H__

#include "../../../common/Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"

class ContainerExpressionSyntax : public ExpressionSyntax {
private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _elements;
  std::unique_ptr<SyntaxToken<std::any>> _openBracket;
  std::unique_ptr<SyntaxToken<std::any>> _closeBracket;

public:
  // Overrides
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  auto setElement(std::unique_ptr<ExpressionSyntax> element) -> void;

  // Getters
  auto getElementsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> &;

  inline auto
  setOpenBracketToken(std::unique_ptr<SyntaxToken<std::any>> openBracket)
      -> void {
    _openBracket = std::move(openBracket);
  }

  inline auto
  setCloseBracketToken(std::unique_ptr<SyntaxToken<std::any>> closeBracket)
      -> void {
    _closeBracket = std::move(closeBracket);
  }
};

#endif // __FLOWWING_CONTAINER_EXPRESSION_SYNTAX_H__
