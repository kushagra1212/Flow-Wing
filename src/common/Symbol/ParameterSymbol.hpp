#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/common/Symbol/Symbol.hpp"
#include <memory>

namespace flow_wing {

namespace analysis {

class ParameterSymbol : public Symbol {
public:
  ParameterSymbol(
      std::string name, std::shared_ptr<types::Type> type,
      std::unique_ptr<binding::BoundExpression> default_value_expression)
      : Symbol(std::move(name), SymbolKind::kParameter, std::move(type)),
        m_default_value_expression(std::move(default_value_expression)) {}

  ~ParameterSymbol() = default;

  const std::unique_ptr<binding::BoundExpression> &
  getDefaultValueExpression() const {
    return m_default_value_expression;
  }

private:
  std::unique_ptr<binding::BoundExpression> m_default_value_expression;
};
} // namespace analysis
} // namespace flow_wing