#ifndef __FLOWWING_FILL_EXPRESSION_SYNTAX_H__
#define __FLOWWING_FILL_EXPRESSION_SYNTAX_H__

#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"

class FillExpressionSyntax : public ExpressionSyntax {
 private:
  std::unique_ptr<ExpressionSyntax> _sizeToFillExpression;
  std::unique_ptr<ExpressionSyntax> _elementExpression;

 public:
  // Overrides
  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters

  void setSizeToFillExpression(
      std::unique_ptr<ExpressionSyntax> sizeToFillExpression);

  void setElementExpression(
      std::unique_ptr<ExpressionSyntax> elementExpression);

  // Getters
  auto getSizeToFillExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> &;

  auto getElementExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> &;
};

#endif  //  __FLOWWING_FILL_EXPRESSION_SYNTAX_H__
