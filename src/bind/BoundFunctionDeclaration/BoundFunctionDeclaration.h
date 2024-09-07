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
  std::vector<std::unique_ptr<BoundExpression>> _returnTypeExprList;
  std::unique_ptr<BoundTypeExpression> _functionType;
  bool _isOnlyDeclared = false;
  bool _isMemberFunction = false;
  bool _isVariadicFunction = false;
  bool _hasAsReturnType = false;
  int64_t _minNumberOfParametersNeeded = 0;
  int64_t _optionalParameterStartIndex = -1;

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

  inline void addReturnExpr(std::unique_ptr<BoundExpression> retrunExprType) {
    _returnTypeExprList.push_back(std::move(retrunExprType));
  }

  inline void setIsMemberFunction(bool isMemberFunction) {
    _isMemberFunction = isMemberFunction;
  }

  inline auto setFunctionType(std::unique_ptr<BoundTypeExpression> type) {
    _functionType = std::move(type);
  }

  inline auto setHasAsReturnType(const bool hasAsReturnType) {
    _hasAsReturnType = hasAsReturnType;
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
  inline auto setIsVariadicFunction(bool isVariadicFunction) {
    this->_isVariadicFunction = isVariadicFunction;
  }

  inline auto isVariadicFunction() const { return _isVariadicFunction; }

  inline auto getReturnTypeExprListRef() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _returnTypeExprList;
  }

  inline auto getMinNumberOfParametersNeeded() const -> int64_t {
    return _minNumberOfParametersNeeded;
  }

  inline auto
  setOptionalParameterStartIndex(int64_t optionalParameterStartIndex) {
    _optionalParameterStartIndex = optionalParameterStartIndex;
  }

  inline auto getOptionalParameterStartIndex() const -> int64_t {
    return _optionalParameterStartIndex;
  }

  inline auto hasOptionalParameters() const -> bool {
    return _optionalParameterStartIndex >= 0;
  }

  inline auto isMemberFunction() const -> bool { return _isMemberFunction; }

  inline auto isOnlyDeclared() const -> bool { return _isOnlyDeclared; }

  inline auto isExposed() const -> bool { return _isExposed; }

  inline auto hasAsReturnType() const -> bool { return _hasAsReturnType; }

  inline auto getFunctionTypeRef() const
      -> const std::unique_ptr<BoundTypeExpression> & {
    return _functionType;
  }
};

#endif