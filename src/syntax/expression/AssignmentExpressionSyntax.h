#pragma once
#include "../../Common.h"
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class AssignmentExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<ExpressionSyntax> _left;
  std::unique_ptr<ExpressionSyntax> _right;
  SyntaxKindUtils::SyntaxKind _operatorTokenKind;
  bool _needDefaultInitialize = false;

public:
  AssignmentExpressionSyntax(std::unique_ptr<ExpressionSyntax> left,
                             SyntaxKindUtils::SyntaxKind operatorTokenKind,
                             std::unique_ptr<ExpressionSyntax> right,
                             bool needDefaultInitialize = false);

  std::unique_ptr<ExpressionSyntax> getRight();
  std::unique_ptr<ExpressionSyntax> getLeft();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<ExpressionSyntax> &getRightPtr();
  std::unique_ptr<ExpressionSyntax> &getLeftPtr();

  auto inline getNeedDefaulInitilization() -> bool {
    return _needDefaultInitialize;
  }

  inline auto getOperatorTokenKind() const -> SyntaxKindUtils::SyntaxKind {
    return _operatorTokenKind;
  }
};
