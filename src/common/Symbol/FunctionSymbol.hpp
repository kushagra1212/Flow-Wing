#pragma once

#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include <memory>
#include <vector>

namespace flow_wing {

namespace analysis {
class FunctionSymbol : public Symbol {
public:
  FunctionSymbol(std::string name, std::shared_ptr<types::Type> type)
      : Symbol(std::move(name), SymbolKind::kFunction, std::move(type)),
        m_body(nullptr),
        m_parameters(
            std::vector<std::shared_ptr<analysis::ParameterSymbol>>()) {}

  ~FunctionSymbol() = default;

  // Setters
  void setBody(std::unique_ptr<binding::BoundStatement> body) {
    m_body = std::move(body);
  }

  void addParameter(std::shared_ptr<analysis::ParameterSymbol> parameter) {
    m_parameters.push_back(std::move(parameter));
  }

  // Getters
  const std::unique_ptr<binding::BoundStatement> &getBody() const {
    return m_body;
  }
  const std::vector<std::shared_ptr<analysis::ParameterSymbol>> &
  getParameters() const {
    return m_parameters;
  }

private:
  std::unique_ptr<binding::BoundStatement> m_body;
  std::vector<std::shared_ptr<analysis::ParameterSymbol>> m_parameters;
};
} // namespace analysis
} // namespace flow_wing