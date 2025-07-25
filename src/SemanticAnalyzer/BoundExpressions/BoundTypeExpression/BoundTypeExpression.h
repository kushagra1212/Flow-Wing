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
#include "../../../utils/Utils.h"
#include "../../BinderKindUtils.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundExpression/BoundExpression.h"

class BoundTypeExpression : public BoundExpression {
private:
  SyntaxKindUtils::SyntaxKind _type;
  std::string _variableNameItBelongsTo = "";

public:
  BoundTypeExpression(const DiagnosticUtils::SourceLocation &location,
                      const SyntaxKindUtils::SyntaxKind &type);

  const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  inline auto setVariableNameitBelongsTo(std::string variableName) -> void {
    this->_variableNameItBelongsTo = variableName;
  }

  inline auto getSyntaxType() const -> const SyntaxKindUtils::SyntaxKind & {
    return _type;
  }

  inline auto getVariableNameItBelongsTo() -> std::string {
    return _variableNameItBelongsTo;
  }
};