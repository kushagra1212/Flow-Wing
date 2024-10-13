#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementSyntax.h"
class ElseClauseSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _elseKeyword;
  std::unique_ptr<BlockStatementSyntax> _statement;

public:
  ElseClauseSyntax(std::unique_ptr<SyntaxToken<std::any>> elseKeyword,
                   std::unique_ptr<BlockStatementSyntax> statement);

  std::unique_ptr<SyntaxToken<std::any>> getElseKeyword();
  std::unique_ptr<BlockStatementSyntax> getStatement();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getElseKeywordRef();
  std::unique_ptr<BlockStatementSyntax> &getStatementRef();
};
