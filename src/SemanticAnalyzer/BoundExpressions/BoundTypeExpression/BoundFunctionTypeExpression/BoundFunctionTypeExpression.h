/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#pragma once

#include "../BoundTypeExpression.h"
#include <cstdint>
#include <sys/types.h>

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
  inline auto setAsParam(uint64_t index, bool hasAsParam) {
    _hasAsParamList[index] = (hasAsParam);
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
