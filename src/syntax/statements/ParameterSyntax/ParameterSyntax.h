#ifndef PARAMETER_SYNTAX_H
#define PARAMETER_SYNTAX_H

#include "../../../Common.h"

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"

class ParameterSyntax : public SyntaxNode {

private:
  std::unique_ptr<SyntaxToken<std::any>> _identifierToken;

public:
  ParameterSyntax(std::unique_ptr<SyntaxToken<std::any>> identifierToken);

  std::unique_ptr<SyntaxToken<std::any>> getIdentifierToken();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<SyntaxToken<std::any>> &getIdentifierTokenPtr();
};

#endif // PARAMETER_SYNTAX_H