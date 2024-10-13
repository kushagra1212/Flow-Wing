#ifndef __BOUND_MULTIPLE_VARIABLE_DECLARATION_H__
#define __BOUND_MULTIPLE_VARIABLE_DECLARATION_H__

#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundMultipleVariableDeclaration : public BoundStatement,
                                         public BoundSourceLocation {

  std::vector<std::unique_ptr<BoundVariableDeclaration>>
      _variableDeclarationList;

public:
  BoundMultipleVariableDeclaration(
      const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline auto addVariableDeclaration(
      std::unique_ptr<BoundVariableDeclaration> variableDeclaration) -> void {
    _variableDeclarationList.push_back(std::move(variableDeclaration));
  }

  /*
    Getters
  */
  inline auto getVariableDeclarationListRef() const
      -> const std::vector<std::unique_ptr<BoundVariableDeclaration>> & {
    return _variableDeclarationList;
  }
};

#endif