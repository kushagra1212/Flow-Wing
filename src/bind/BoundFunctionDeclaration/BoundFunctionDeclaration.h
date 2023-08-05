#ifndef BOUND_FUNCTION_DECLARATION_H
#define BOUND_FUNCTION_DECLARATION_H

#include "../../utils/Utils.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundStatement/BoundStatement.h"

class BoundFunctionDeclaration : public BoundStatement {
public:
  BoundBlockStatement *body;
  Utils::FunctionSymbol functionSymbol;

  BoundFunctionDeclaration(Utils::FunctionSymbol functionSymbol,
                           BoundBlockStatement *body);

  ~BoundFunctionDeclaration();

  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<BoundNode *> getChildren() override;

  BoundBlockStatement *getBody() const;

  Utils::FunctionSymbol getFunctionSymbol() const;
};

#endif