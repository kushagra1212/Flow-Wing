#ifndef BOUND_FUNCTION_DECLARATION_H
#define BOUND_FUNCTION_DECLARATION_H

#include "../../utils/Utils.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundFunctionDeclaration : public BoundStatement,
                                 public BoundSourceLocation {
  std::unique_ptr<BoundBlockStatement> _body;
  std::vector<std::unique_ptr<BoundVariableDeclaration>> _parameters;
  std::string _functionName;
  bool _isExposed;
  std::unique_ptr<BoundExpression> _returnType;
  bool _isOnlyDeclared = false;
  bool _isMemberFunction = false;

public:
  BoundFunctionDeclaration(const DiagnosticUtils::SourceLocation &location,
                           bool isExposed);

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  void addParameter(std::unique_ptr<BoundVariableDeclaration> parameter);
  void setFunctionName(const std::string &functionName);
  void setFunctionBody(std::unique_ptr<BoundBlockStatement> body);

  inline void setOnlyDeclared(bool isOnlyDeclared) {
    _isOnlyDeclared = isOnlyDeclared;
  }

  inline void setReturnType(std::unique_ptr<BoundExpression> returnType) {
    _returnType = std::move(returnType);
  }

  inline void setIsMemberFunction(bool isMemberFunction) {
    _isMemberFunction = isMemberFunction;
  }

  inline auto getParametersRef() const
      -> const std::vector<std::unique_ptr<BoundVariableDeclaration>> & {
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

  inline auto isMemberFunction() const -> bool { return _isMemberFunction; }

  inline auto isOnlyDeclared() const -> bool { return _isOnlyDeclared; }

  inline auto isExposed() const -> bool { return _isExposed; }
};

#endif