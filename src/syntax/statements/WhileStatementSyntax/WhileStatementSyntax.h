#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
class WhileStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _whileKeyword;
  std::unique_ptr<ExpressionSyntax> _condition;
  std::unique_ptr<BlockStatementSyntax> _body;

public:
  WhileStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> whileKeyword,
                       std::unique_ptr<ExpressionSyntax> condition,
                       std::unique_ptr<BlockStatementSyntax> body);

  std::unique_ptr<SyntaxToken<std::any>> getWhileKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getBody();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getWhileKeywordRef();
  std::unique_ptr<ExpressionSyntax> &getConditionRef();
  std::unique_ptr<BlockStatementSyntax> &getBodyRef();
};