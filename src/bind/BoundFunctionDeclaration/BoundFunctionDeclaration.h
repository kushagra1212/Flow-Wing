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

  std::unique_ptr<BoundExpression> _returnType;

public:
  BoundFunctionDeclaration(const DiagnosticUtils::SourceLocation &location);

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  void addParameter(std::unique_ptr<BoundVariableExpression> parameter);
  void setFunctionName(const std::string &functionName);
  void setFunctionBody(std::unique_ptr<BoundBlockStatement> body);
  inline void setReturnType(std::unique_ptr<BoundExpression> returnType) {
    _returnType = std::move(returnType);
  }

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
  inline auto getReturnType() const
      -> const std::unique_ptr<BoundExpression> & {
    return _returnType;
  }
};

#endif