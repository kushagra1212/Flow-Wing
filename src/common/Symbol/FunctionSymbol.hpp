#pragma once

#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/utils/LogConfig.h"
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
            std::vector<std::shared_ptr<analysis::ParameterSymbol>>()) {
    BINDER_DEBUG_LOG("Creating FunctionSymbol: " + getName(), "FunctionSymbol");
  }

  void setMangledName(std::string mangled) {
    m_mangled_name = std::move(mangled);
  }
  const std::string &getMangledName() const {
    return m_mangled_name.empty() ? getName() : m_mangled_name;
  }

  ~FunctionSymbol() = default;

  // Setters
  void setBody(std::unique_ptr<binding::BoundStatement> body) {
    m_body = std::move(body);
  }

  void addParameter(std::shared_ptr<analysis::ParameterSymbol> parameter) {
    m_parameters.push_back(std::move(parameter));
  }

  void setHideTrailingParamsForDisplay(uint32_t count) {
    m_hide_trailing_params_for_display = count;
  }
  uint32_t getHideTrailingParamsForDisplay() const {
    return m_hide_trailing_params_for_display;
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
  std::string m_mangled_name;
  /// Number of trailing parameters to hide in IDE signatures (e.g. implicit
  /// self).
  uint32_t m_hide_trailing_params_for_display = 0;
};
} // namespace analysis
} // namespace flow_wing