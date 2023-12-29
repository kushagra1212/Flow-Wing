#ifndef BOUND_FUNCTION_DECLARATION_H
#define BOUND_FUNCTION_DECLARATION_H

#include "../../utils/Utils.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableExpression/BoundVariableExpression.h"

class BoundFunctionDeclaration : public BoundStatement,
                                 public BoundSourceLocation {

  std::unique_ptr<BoundBlockStatement> _body;
  std::vector<std::unique_ptr<BoundVariableExpression>> _parameters;
  std::string _functionName;
  Utils::type _returnType;

public:
  BoundFunctionDeclaration(const DiagnosticUtils::SourceLocation &location);

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  void addParameter(std::unique_ptr<BoundVariableExpression> parameter);
  void setFunctionName(const std::string &functionName);
  void setFunctionBody(std::unique_ptr<BoundBlockStatement> body);
  void setReturnType(Utils::type returnType);

  inline auto getParametersRef() const
      -> const std::vector<std::unique_ptr<BoundVariableExpression>> & {
    return _parameters;
  }
  inline auto getFunctionNameRef() const -> const std::string & {
    return _functionName;
  }
  inline auto getBodyRef() const
      -> const std::unique_ptr<BoundBlockStatement> & {
    return _body;
  }
  inline auto getReturnType() const -> const Utils::type & {
    return _returnType;
  }
};

#endif