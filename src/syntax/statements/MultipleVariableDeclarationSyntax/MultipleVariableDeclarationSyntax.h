#ifndef MULTIPLE_VARIABLE_DECLARATION_SYNTAX_H
#define MULTIPLE_VARIABLE_DECLARATION_SYNTAX_H
#include "../StatementSyntax.h"
#include "../VariableDeclarationSyntax/VariableDeclarationSyntax.h"
class MultipleVariableDeclarationSyntax : public StatementSyntax {
  std::vector<std::unique_ptr<VariableDeclarationSyntax>>
      _variableDeclarationList;

public:
  MultipleVariableDeclarationSyntax();

  /*
      Overrides
  */
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
      Setters
*/

  inline auto addVariableDeclaration(
      std::unique_ptr<VariableDeclarationSyntax> variableDeclaration) -> void {
    _variableDeclarationList.push_back(std::move(variableDeclaration));
  }

  /*
      Getters
  */

  inline auto getVariableDeclarationListRef() const
      -> const std::vector<std::unique_ptr<VariableDeclarationSyntax>> & {
    return _variableDeclarationList;
  }
};

#endif