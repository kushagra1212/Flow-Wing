#ifndef BOUND_FUNCTION_DECLARATION_H
#define BOUND_FUNCTION_DECLARATION_H

#include "../../utils/Utils.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundStatement/BoundStatement.h"

class BoundFunctionDeclaration : public BoundStatement {
public:
  std::unique_ptr<BoundBlockStatement> _body;
  Utils::FunctionSymbol _functionSymbol;

  BoundFunctionDeclaration(std::string lineAndColumn,
                           Utils::FunctionSymbol functionSymbol,
                           std::unique_ptr<BoundBlockStatement> body);

  std::unique_ptr<BoundBlockStatement> getBody();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<BoundBlockStatement> &getBodyPtr();
};

#endif