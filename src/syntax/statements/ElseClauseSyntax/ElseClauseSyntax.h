#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementSyntax.h"
class ElseClauseSyntax : public SyntaxNode {
private:
  std::unique_ptr<SyntaxToken<std::any>> _elseKeyword;
  std::unique_ptr<BlockStatementSyntax> _statement;

public:
  ElseClauseSyntax(std::unique_ptr<SyntaxToken<std::any>> elseKeyword,
                   std::unique_ptr<BlockStatementSyntax> statement);

  std::unique_ptr<SyntaxToken<std::any>> getElseKeyword();
  std::unique_ptr<BlockStatementSyntax> getStatement();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getElseKeywordPtr();
  std::unique_ptr<BlockStatementSyntax> &getStatementPtr();
};
