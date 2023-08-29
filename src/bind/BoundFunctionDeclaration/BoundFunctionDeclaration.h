#ifndef BOUND_FUNCTION_DECLARATION_H
#define BOUND_FUNCTION_DECLARATION_H

#include "../../utils/Utils.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
class BoundFunctionDeclaration : public BoundStatement,
                                 public BoundSourceLocation {
public:
  std::unique_ptr<BoundBlockStatement> _body;
  Utils::FunctionSymbol _functionSymbol;

  BoundFunctionDeclaration(const DiagnosticUtils::SourceLocation &location,
                           Utils::FunctionSymbol functionSymbol,
                           std::unique_ptr<BoundBlockStatement> body);

  std::unique_ptr<BoundBlockStatement> getBody();

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  std::unique_ptr<BoundBlockStatement> &getBodyPtr();
};

#endif