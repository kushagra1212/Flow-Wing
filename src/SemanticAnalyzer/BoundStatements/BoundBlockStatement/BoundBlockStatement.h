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

#include "../../../common/Common.h"
#include "../../BinderKindUtils.h"
#include "../../BoundNode.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"

class BoundBlockStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::vector<std::unique_ptr<BoundStatement>> _statements;
  bool _global;

public:
  BoundBlockStatement(const DiagnosticUtils::SourceLocation &location,
                      bool global);
  BoundBlockStatement(const DiagnosticUtils::SourceLocation &location);

  std::vector<std::unique_ptr<BoundStatement>> &getStatements();
  void addStatement(std::unique_ptr<BoundStatement> statement);
  bool getGlobal() const;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
};
