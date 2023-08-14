#ifndef BOUND_FUNCTION_DECLARATION_H
#define BOUND_FUNCTION_DECLARATION_H

#include "../../utils/Utils.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundStatement/BoundStatement.h"

class BoundFunctionDeclaration : public BoundStatement {
public:
  std::shared_ptr<BoundBlockStatement> _body;
  Utils::FunctionSymbol _functionSymbol;

  BoundFunctionDeclaration(const std::string &lineAndColumn,
                           Utils::FunctionSymbol functionSymbol,
                           std::shared_ptr<BoundBlockStatement> body);

  BinderKindUtils::BoundNodeKind getKind() override;

  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

  std::shared_ptr<BoundBlockStatement> getBody() const;

  Utils::FunctionSymbol getFunctionSymbol() const;

  std::string getLineNumberAndColumn() const override;
};

#endif