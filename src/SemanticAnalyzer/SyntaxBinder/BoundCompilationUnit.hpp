#pragma once

#include "src/SemanticAnalyzer/BoundNode.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <vector>

namespace flow_wing {
namespace binding {

class BoundCompilationUnit : public BoundNode {
public:
  BoundCompilationUnit(std::vector<std::unique_ptr<BoundStatement>> statements,
                       const flow_wing::diagnostic::SourceLocation &location);
  ~BoundCompilationUnit();

  // Overrides
  NodeKind getKind() const override;

  // Getters
  const std::vector<std::unique_ptr<BoundStatement>> &getStatements() const;

private:
  std::vector<std::unique_ptr<BoundStatement>> m_statements;
};
} // namespace binding
} // namespace flow_wing