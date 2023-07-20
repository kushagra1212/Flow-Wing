#pragma once
#include "../../../Common.h"
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class VariableDeclarationSyntax : public StatementSyntax {
private:
  SyntaxToken<std::any> *_keyword;
  SyntaxToken<std::any> *_identifier;
  SyntaxToken<std::any> *_equalsToken;
  ExpressionSyntax *_initializer;

public:
  VariableDeclarationSyntax(SyntaxToken<std::any> *keyword,
                            SyntaxToken<std::any> *identifier,
                            SyntaxToken<std::any> *equalsToken,
                            ExpressionSyntax *initializer);
  SyntaxKindUtils::SyntaxKind getKind() override;
  std::vector<SyntaxNode *> getChildren() override;
  SyntaxToken<std::any> *getIdentifier() const;
  SyntaxToken<std::any> *getEqualsToken() const;
  ExpressionSyntax *getInitializer() const;
  SyntaxToken<std::any> *getKeyword() const;
};