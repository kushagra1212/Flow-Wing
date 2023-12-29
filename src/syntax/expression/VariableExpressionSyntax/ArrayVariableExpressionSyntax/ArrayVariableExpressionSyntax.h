#ifndef __FLOW__WING__ARRAYVARIABLE_H__
#define __FLOW__WING__ARRAYVARIABLE_H__

#include "../../ExpressionSyntax.h"
#include "../VariableExpressionSyntax.h"

class ArrayVariableExpressionSyntax : public VariableExpressionSyntax {
public:
  ArrayVariableExpressionSyntax(
      std::unique_ptr<ExpressionSyntax> identifierExpression,
      const bool isConstant, const Utils::type &variableType);

  virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  virtual std::vector<SyntaxNode *> getChildren() override;
  virtual DiagnosticUtils::SourceLocation getSourceLocation() const override;

  void addSizeExpression(std::unique_ptr<ExpressionSyntax> sizeExpression);

  inline auto getSizeExpresionsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _sizeExpressions;
  }

private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _sizeExpressions;
};

#endif // __FLOW__WING__ARRAYVARIABLE_H__
