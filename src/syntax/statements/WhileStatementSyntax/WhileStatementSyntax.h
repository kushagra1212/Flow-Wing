#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
class WhileStatementSyntax : public StatementSyntax {
private:
  SyntaxToken<std::any> *_whileKeyword;
  ExpressionSyntax *_condition;
  BlockStatementSyntax *_body;

public:
  WhileStatementSyntax(SyntaxToken<std::any> *whileKeyword,
                       ExpressionSyntax *condition, BlockStatementSyntax *body);

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<SyntaxNode *> getChildren() override;

  SyntaxToken<std::any> *getWhileKeyword() const;

  ExpressionSyntax *getCondition() const;

  BlockStatementSyntax *getBody() const;
};