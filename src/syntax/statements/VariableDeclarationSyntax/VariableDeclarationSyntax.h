#pragma once
#include "../../../Common.h"
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class VariableDeclarationSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _keyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifier;
  std::unique_ptr<SyntaxToken<std::any>> _equalsToken;
  std::unique_ptr<ExpressionSyntax> _initializer;

public:
  VariableDeclarationSyntax(std::unique_ptr<SyntaxToken<std::any>> keyword,
                            std::unique_ptr<SyntaxToken<std::any>> identifier,
                            std::unique_ptr<SyntaxToken<std::any>> equalsToken,
                            std::unique_ptr<ExpressionSyntax> initializer);

  std::unique_ptr<SyntaxToken<std::any>> getIdentifier();
  std::unique_ptr<SyntaxToken<std::any>> getEqualsToken();
  std::unique_ptr<ExpressionSyntax> getInitializer();
  std::unique_ptr<SyntaxToken<std::any>> getKeyword();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  std::string getLineNumberAndColumn() override;
};