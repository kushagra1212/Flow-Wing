
#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementSyntax.h"
class OrIfStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> orKeyword;
  std::unique_ptr<SyntaxToken<std::any>> ifKeyword;
  std::unique_ptr<ExpressionSyntax> condition;
  std::unique_ptr<BlockStatementSyntax> statement;

public:
  OrIfStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> orKeyword,
                      std::unique_ptr<SyntaxToken<std::any>> ifKeyword,
                      std::unique_ptr<ExpressionSyntax> condition,
                      std::unique_ptr<BlockStatementSyntax> statement);

  std::unique_ptr<SyntaxToken<std::any>> getOrKeyword();
  std::unique_ptr<SyntaxToken<std::any>> getIfKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getStatement();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOrKeywordPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getIfKeywordPtr();
  std::unique_ptr<ExpressionSyntax> &getConditionPtr();
  std::unique_ptr<BlockStatementSyntax> &getStatementPtr();
};
