#pragma once

#include "src/SemanticAnalyzer/BoundNode.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include <vector>
#include <memory>

namespace flow_wing {
namespace binding {

class BoundCompilationUnit : public BoundNode {
public:
  BoundCompilationUnit(
      std::vector<std::unique_ptr<BoundStatement>> statements,
      const flow_wing::diagnostic::SourceLocation &location,
      std::shared_ptr<analysis::ScopedSymbolTable> symbol_table);
  ~BoundCompilationUnit();

  // Overrides
  NodeKind getKind() const override;

  // Accept
  void accept(visitor::BoundTreeVisitor *visitor);

  // Getters
  const std::vector<std::unique_ptr<BoundStatement>> &getStatements() const;
  const std::shared_ptr<analysis::ScopedSymbolTable> &getSymbolTable() const;

private:
  std::vector<std::unique_ptr<BoundStatement>> m_statements;
  std::shared_ptr<analysis::ScopedSymbolTable> m_symbol_table;
};
} // namespace binding
} // namespace flow_wing