#pragma once

#include "../BoundTypeExpression.h"

class BoundFunctionTypeExpression : public BoundTypeExpression {
private:
  std::vector<std::unique_ptr<BoundTypeExpression>> _parameterTypes;
  std::vector<std::unique_ptr<BoundTypeExpression>> _returnTypes;
  std::vector<bool> _hasAsParamList;
  bool _hasAsReturnType = false;

public:
  BoundFunctionTypeExpression(const DiagnosticUtils::SourceLocation &location,
                              const SyntaxKindUtils::SyntaxKind &type);

  virtual std::vector<BoundNode *> getChildren() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;

  inline auto
  addParameterType(std::unique_ptr<BoundTypeExpression> parameterType) -> void {
    this->_parameterTypes.push_back(std::move(parameterType));
  }

  inline auto setHasAsReturnType(bool hasAsReturnTypeKeyword) -> void {
    this->_hasAsReturnType = hasAsReturnTypeKeyword;
  }

  inline auto addReturnType(std::unique_ptr<BoundTypeExpression> returnType)
      -> void {
    this->_returnTypes.push_back(std::move(returnType));
  }

  inline auto addAsParam(bool hasAsParam) {
    _hasAsParamList.push_back(hasAsParam);
  }

  inline auto getParameterTypes()
      -> const std::vector<std::unique_ptr<BoundTypeExpression>> & {
    return this->_parameterTypes;
  }

  inline auto getReturnTypes()
      -> const std::vector<std::unique_ptr<BoundTypeExpression>> & {
    return this->_returnTypes;
  }

  inline auto hasAsReturnType() -> const bool & {
    return this->_hasAsReturnType;
  }

  inline auto getHasAsParamListRef() const -> const std::vector<bool> & {
    return _hasAsParamList;
  }
};
