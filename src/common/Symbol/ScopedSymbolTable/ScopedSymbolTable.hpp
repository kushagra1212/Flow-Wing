#pragma once

#include "src/common/Symbol/Symbol.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace flow_wing {

namespace analysis {
class FunctionSymbol;

using SymbolTable = std::unordered_map<std::string, std::shared_ptr<Symbol>>;

class ScopedSymbolTable {
public:
  ScopedSymbolTable();

  void enterScope();
  void leaveScope();

  // Defines a symbol in the current (innermost) scope.
  // Returns false if the symbol is already defined in this scope.
  bool define(std::shared_ptr<Symbol> symbol);

  // Looks up a symbol, searching from the innermost scope outwards.
  std::shared_ptr<Symbol> lookup(const std::string &name) const;

  bool isInBreakScope() const;
  bool isInReturnScope() const;

  void setCurrentFunctionSymbol(const FunctionSymbol *function);

  const FunctionSymbol *getCurrentFunctionSymbol() const;

private:
  std::vector<std::unique_ptr<SymbolTable>> m_scope_stack;
  const FunctionSymbol *m_current_function_symbol;
};

} // namespace analysis
} // namespace flow_wing