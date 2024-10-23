#ifndef __FLOWWING_OBJECT_EXPRESSION_SYNTAX_H__
#define __FLOWWING_OBJECT_EXPRESSION_SYNTAX_H__

#include "../../../common/Common.h"
#include "../../SyntaxToken.h"
#include "../AttributeExpressionSyntax/AttributeExpressionSyntax.h"
#include "../ExpressionSyntax.h"

class ObjectExpressionSyntax : public ExpressionSyntax {
private:
  std::vector<std::unique_ptr<AttributeExpressionSyntax>> _attributes;
  std::unique_ptr<SyntaxToken<std::any>> _openBraceToken;
  std::unique_ptr<SyntaxToken<std::any>> _closeBraceToken;

public:
  // Overrides
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  inline auto
  addAttribute(std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
               std::unique_ptr<ExpressionSyntax> value) -> void {
    std::unique_ptr<AttributeExpressionSyntax> attribute =
        std::make_unique<AttributeExpressionSyntax>();

    attribute->setAttribute(std::move(key), std::move(value));
    _attributes.push_back(std::move(attribute));
  }

  // Getters
  auto getAttributes()
      -> const std::vector<std::unique_ptr<AttributeExpressionSyntax>> & {
    return _attributes;
  }

  auto setOpenBraceToken(std::unique_ptr<SyntaxToken<std::any>> openBraceToken)
      -> void {
    _openBraceToken = std::move(openBraceToken);
  }

  auto
  setCloseBraceToken(std::unique_ptr<SyntaxToken<std::any>> closeBraceToken)
      -> void {
    _closeBraceToken = std::move(closeBraceToken);
  }
};

#endif // __FLOWWING_OBJECT_EXPRESSION_SYNTAX_H__
