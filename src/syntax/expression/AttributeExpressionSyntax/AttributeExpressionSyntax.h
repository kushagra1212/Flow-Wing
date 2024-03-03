#ifndef __FLOWWING_ATTRIBUTE_EXPRESSION_SYNTAX_H__
#define __FLOWWING_ATTRIBUTE_EXPRESSION_SYNTAX_H__
#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class AttributeExpressionSyntax : public ExpressionSyntax {
 private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _key;
  std::unique_ptr<ExpressionSyntax> _value;

 public:
  // Overrides
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  inline auto setAttribute(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
      std::unique_ptr<ExpressionSyntax> value) -> void {
    this->_key = std::move(key);
    this->_value = std::move(value);
  }

  // Getters
  inline auto getKey()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_key;
  }

  inline auto getValue() -> const std::unique_ptr<ExpressionSyntax> & {
    return this->_value;
  }
};

#endif  // __FLOWWING_ATTRIBUTE_EXPRESSION_SYNTAX_H__
