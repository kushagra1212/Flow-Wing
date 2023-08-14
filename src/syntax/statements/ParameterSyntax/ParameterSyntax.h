#ifndef PARAMETER_SYNTAX_H
#define PARAMETER_SYNTAX_H

#include "../../../Common.h"

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"

class ParameterSyntax : public SyntaxNode {

private:
  std::shared_ptr<SyntaxToken<std::any>> _identifierToken;

public:
  ParameterSyntax(std::shared_ptr<SyntaxToken<std::any>> identifierToken);

  std::shared_ptr<SyntaxToken<std::any>> getIdentifierToken() const;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // PARAMETER_SYNTAX_H