#pragma once
#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"
class BlockStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _openBraceToken;
  std::vector<std::unique_ptr<StatementSyntax>> _statements;
  std::unique_ptr<SyntaxToken<std::any>> _closeBraceToken;

 public:
  BlockStatementSyntax();

  void addStatement(std::unique_ptr<StatementSyntax> statement);
  void setOpenBraceToken(std::unique_ptr<SyntaxToken<std::any>> openBraceToken);
  void setCloseBraceToken(
      std::unique_ptr<SyntaxToken<std::any>> closeBraceToken);

  std::unique_ptr<SyntaxToken<std::any>> getOpenBraceToken();
  std::vector<std::unique_ptr<StatementSyntax>> &getStatements();
  std::unique_ptr<SyntaxToken<std::any>> getCloseBraceToken();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOpenBraceTokenPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseBraceTokenPtr();
};