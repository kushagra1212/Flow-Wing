#pragma once
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementSyntax.h"
class ElseClauseSyntax : public SyntaxNode {
private:
  std::shared_ptr<SyntaxToken<std::any>> _elseKeyword;
  std::shared_ptr<BlockStatementSyntax> _statement;

public:
  ElseClauseSyntax(std::shared_ptr<SyntaxToken<std::any>> elseKeyword,
                   std::shared_ptr<BlockStatementSyntax> statement);

  std::shared_ptr<SyntaxToken<std::any>> getElseKeyword() const;
  std::shared_ptr<BlockStatementSyntax> getStatement() const;
  SyntaxKindUtils::SyntaxKind getKind() override;
  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};
