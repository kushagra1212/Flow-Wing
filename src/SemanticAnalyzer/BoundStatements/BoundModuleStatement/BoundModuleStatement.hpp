/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <memory>
#include <vector>

namespace flow_wing {
namespace binding {

/// Body of `module [name] ...` through end of file. Does not introduce an IR
/// scope so module-level variables share the entry function's global scope for
/// symbol lookup (same as other top-level statements).
class BoundModuleStatement : public BoundStatement {

public:
  BoundModuleStatement(std::vector<std::unique_ptr<BoundStatement>> statements,
                       const flow_wing::diagnostic::SourceLocation &location);
  ~BoundModuleStatement() override = default;

  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  const std::vector<std::unique_ptr<BoundStatement>> &getStatements() const;

private:
  std::vector<std::unique_ptr<BoundStatement>> m_statements;
};
} // namespace binding
} // namespace flow_wing
