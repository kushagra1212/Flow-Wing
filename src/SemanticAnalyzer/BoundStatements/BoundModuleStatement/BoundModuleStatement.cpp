/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "BoundModuleStatement.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"

namespace flow_wing {
namespace binding {

BoundModuleStatement::BoundModuleStatement(
    std::vector<std::unique_ptr<BoundStatement>> statements,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundStatement(location), m_statements(std::move(statements)) {}

NodeKind BoundModuleStatement::getKind() const {
  return NodeKind::kModuleStatement;
}

void BoundModuleStatement::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<BoundStatement>> &
BoundModuleStatement::getStatements() const {
  return m_statements;
}

} // namespace binding
} // namespace flow_wing
