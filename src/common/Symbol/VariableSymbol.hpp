#pragma once

#include "src/common/Symbol/Symbol.hpp"
#include "src/utils/LogConfig.h"
#include <memory>

namespace flow_wing {

namespace binding {
class BoundExpression;
} // namespace binding

namespace analysis {

class VariableSymbol : public Symbol {
public:
  VariableSymbol(std::string name, std::shared_ptr<types::Type> type,
                 bool isConst)
      : Symbol(std::move(name), SymbolKind::kVariable, std::move(type)),
        m_initializer_expression(nullptr), m_isConst(isConst) {
    BINDER_DEBUG_LOG("Creating VariableSymbol: " + getName(), "VariableSymbol");
  }

  ~VariableSymbol() = default;

  void setInitializerExpression(
      std::unique_ptr<binding::BoundExpression> initializer_expression) {
    m_initializer_expression = std::move(initializer_expression);
  }

  const std::unique_ptr<binding::BoundExpression> &
  getInitializerExpression() const {
    return m_initializer_expression;
  }

  bool isConst() const { return m_isConst; }

private:
  std::unique_ptr<binding::BoundExpression> m_initializer_expression;
  bool m_isConst;
};
} // namespace analysis
} // namespace flow_wing