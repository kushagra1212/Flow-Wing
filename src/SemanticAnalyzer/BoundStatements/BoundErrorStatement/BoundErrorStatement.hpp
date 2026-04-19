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

#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include <memory>
namespace flow_wing {
namespace binding {

class BoundErrorStatement : public BoundStatement {

public:
  BoundErrorStatement(
      const flow_wing::diagnostic::SourceLocation &location,
      flow_wing::diagnostic::DiagnosticCode code,
      const std::vector<flow_wing::diagnostic::DiagnosticArg> &args);

  BoundErrorStatement(std::unique_ptr<BoundExpression> expression);
  ~BoundErrorStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  flow_wing::diagnostic::DiagnosticCode getCode() const;
  const std::vector<flow_wing::diagnostic::DiagnosticArg> &getArgs() const;

private:
  flow_wing::diagnostic::DiagnosticCode m_code;
  std::vector<flow_wing::diagnostic::DiagnosticArg> m_args;
};
} // namespace binding
} // namespace flow_wing