#ifndef PARAMETER_SYNTAX_H
#define PARAMETER_SYNTAX_H

#include "../../../common/Common.h"
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"

class ParameterSyntax : public SyntaxNode {
private:
  std::unique_ptr<SyntaxToken<std::any>> _identifierToken;

public:
  ParameterSyntax() = default;
  ParameterSyntax(std::unique_ptr<SyntaxToken<std::any>> identifierToken);

  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation
  getSourceLocation() const override;

  virtual std::unique_ptr<SyntaxToken<std::any>> &getIdentifierTokenPtr();
};

#endif // PARAMETER_SYNTAX_H