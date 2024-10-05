#pragma once

#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include <memory>
class TernaryExpressionSyntax : public ExpressionSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _questionToken;
  std::unique_ptr<SyntaxToken<std::any>> _colonToken;

  std::unique_ptr<ExpressionSyntax> _conditionExpression;
  std::unique_ptr<ExpressionSyntax> _trueExpression;
  std::unique_ptr<ExpressionSyntax> _falseExpression;

public:
  TernaryExpressionSyntax() = default;
  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation
  getSourceLocation() const override;

  inline auto
  addConditionExpression(std::unique_ptr<ExpressionSyntax> conditionExpression)
      -> void {
    _conditionExpression = std::move(conditionExpression);
  }

  inline auto
  addQuestionToken(std::unique_ptr<SyntaxToken<std::any>> questionToken)
      -> void {
    _questionToken = std::move(questionToken);
  }

  inline auto
  addTrueExpression(std::unique_ptr<ExpressionSyntax> trueExpression) -> void {
    _trueExpression = std::move(trueExpression);
  }

  inline auto addColonToken(std::unique_ptr<SyntaxToken<std::any>> colonToken)
      -> void {
    _colonToken = std::move(colonToken);
  }

  inline auto
  addFalseExpression(std::unique_ptr<ExpressionSyntax> falseExpression)
      -> void {
    _falseExpression = std::move(falseExpression);
  }

  inline auto getConditionExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _conditionExpression;
  }

  inline auto getTrueExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _trueExpression;
  }

  inline auto getFalseExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _falseExpression;
  }
};