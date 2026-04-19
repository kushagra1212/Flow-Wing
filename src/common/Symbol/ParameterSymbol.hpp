#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"

#include "src/common/Symbol/Symbol.hpp"
#include "src/utils/LogConfig.h"
#include <memory>

namespace flow_wing {

namespace analysis {
class FunctionSymbol;
class ParameterSymbol : public Symbol {
public:
  ParameterSymbol(
      std::string name, std::shared_ptr<types::Type> type,
      std::unique_ptr<binding::BoundExpression> default_value_expression);

  ~ParameterSymbol() = default;

  const std::unique_ptr<binding::BoundExpression> &
  getDefaultValueExpression() const ;
  const std::shared_ptr<analysis::FunctionSymbol> &
  getFunctionSymbol();

private:
  std::unique_ptr<binding::BoundExpression> m_default_value_expression = nullptr;
  std::shared_ptr<analysis::FunctionSymbol> m_function_symbol = nullptr;
};
} // namespace analysis
} // namespace flow_wing