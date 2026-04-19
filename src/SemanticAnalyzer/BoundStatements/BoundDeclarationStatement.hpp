#pragma once
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <vector>

namespace flow_wing {
namespace binding {

class BoundDeclarationStatement : public BoundStatement {
public:
  virtual ~BoundDeclarationStatement() = default;

  virtual const std::vector<std::shared_ptr<analysis::Symbol>> &
  getSymbols() const = 0;

protected:
  explicit BoundDeclarationStatement(
      const flow_wing::diagnostic::SourceLocation &location)
      : BoundStatement(location) {}

  BoundDeclarationStatement() = default;
};

} // namespace binding
} // namespace flow_wing