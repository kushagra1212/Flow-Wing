#pragma once

#include "ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"
#include <memory>

namespace flow_wing {

namespace binding {
class BoundExpression;
} // namespace binding

namespace analysis {

class ModuleSymbol : public Symbol {
public:
  ModuleSymbol(std::string module_name,
               std::shared_ptr<ScopedSymbolTable> module_symbol_table)
      : Symbol(std::move(module_name), SymbolKind::kModule,
               std::make_shared<types::Type>(module_name,
                                             types::TypeKind::kModule)),
        m_module_symbol_table(std::move(module_symbol_table)) {
    BINDER_DEBUG_LOG("Creating ModuleSymbol: " + getName(), "ModuleSymbol");
  }

  ~ModuleSymbol() = default;

  std::shared_ptr<ScopedSymbolTable> getModuleSymbolTable() const {
    return m_module_symbol_table;
  }

private:
  std::shared_ptr<ScopedSymbolTable> m_module_symbol_table;
};
} // namespace analysis
} // namespace flow_wing