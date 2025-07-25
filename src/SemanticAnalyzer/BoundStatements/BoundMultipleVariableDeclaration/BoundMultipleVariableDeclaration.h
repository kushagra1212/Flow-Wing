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


#ifndef __BOUND_MULTIPLE_VARIABLE_DECLARATION_H__
#define __BOUND_MULTIPLE_VARIABLE_DECLARATION_H__

#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundMultipleVariableDeclaration : public BoundStatement,
                                         public BoundSourceLocation {

  std::vector<std::unique_ptr<BoundVariableDeclaration>>
      _variableDeclarationList;

public:
  BoundMultipleVariableDeclaration(
      const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline auto addVariableDeclaration(
      std::unique_ptr<BoundVariableDeclaration> variableDeclaration) -> void {
    _variableDeclarationList.push_back(std::move(variableDeclaration));
  }

  /*
    Getters
  */
  inline auto getVariableDeclarationListRef() const
      -> const std::vector<std::unique_ptr<BoundVariableDeclaration>> & {
    return _variableDeclarationList;
  }
};

#endif