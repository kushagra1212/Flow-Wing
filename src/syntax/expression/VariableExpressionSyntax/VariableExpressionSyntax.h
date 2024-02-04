#ifndef __FLOW__WING__VARIABLE_H__
#define __FLOW__WING__VARIABLE_H__

#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../TypeExpressionSyntax/TypeExpressionSyntax.h"

class VariableExpressionSyntax : public ExpressionSyntax {
 public:
  VariableExpressionSyntax(
      std::unique_ptr<ExpressionSyntax> identifierExpression,
      const bool isConstant,
      std::unique_ptr<TypeExpressionSyntax> variableTypeExpr);

  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation getSourceLocation()
      const override;

  inline void addDotExpression(
      std::unique_ptr<ExpressionSyntax> dotExpression) {
    _dotExpressionList.push_back(std::move(dotExpression));
  }

  inline auto getDotExpressionList() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _dotExpressionList;
  }

  inline auto getIdentifierTokenRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _identifierExpression;
  }

  inline auto getVariableTypeExprRef() const
      -> const std::unique_ptr<TypeExpressionSyntax> & {
    return _variableTypeExpr;
  }

  inline auto setVariableTypeExprRef(
      std::unique_ptr<TypeExpressionSyntax> variableTypeExpr) -> void {
    _variableTypeExpr = std::move(variableTypeExpr);
  }

  inline auto isConstant() const -> const bool & { return _isConstant; }

  inline auto getVariableName() const -> std::string {
    LiteralExpressionSyntax<std::any> *literalExpressionSyntax =
        static_cast<LiteralExpressionSyntax<std::any> *>(
            _identifierExpression.get());
    return std::any_cast<std::string>(
        literalExpressionSyntax->getTokenPtr()->getText());
  }

 private:
  std::unique_ptr<ExpressionSyntax> _identifierExpression;
  std::unique_ptr<TypeExpressionSyntax> _variableTypeExpr;
  std::vector<std::unique_ptr<ExpressionSyntax>> _dotExpressionList;
  bool _isConstant;
  std::string _variableName;
};

#endif  // __FLOW__WING__VARIABLE_H__