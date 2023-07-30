#ifndef PARAMETER_SYNTAX_H
#define PARAMETER_SYNTAX_H

#include "../../../Common.h"

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"

class ParameterSyntax : public SyntaxNode {

private:
  SyntaxToken<std::any> *_identifierToken;

public:
  ParameterSyntax(SyntaxToken<std::any> *identifierToken);

  SyntaxToken<std::any> *getIdentifierToken() const;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<SyntaxNode *> getChildren() override;
};

#endif // PARAMETER_SYNTAX_H