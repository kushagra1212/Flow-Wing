#pragma once

#include "src/common/Symbol/Symbol.hpp"
#include <functional>
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

  bool define(std::shared_ptr<Symbol> symbol);

  bool defineInEnclosingScope(std::shared_ptr<Symbol> symbol);

  std::shared_ptr<Symbol> lookup(const std::string &name) const;
  void lookupSymbol(std::function<bool(const Symbol *symbol)> predicate,
                    SymbolKind kind) const;

  void pushBreakScope();
  void popBreakScope();
  bool isInBreakScope() const;
  bool isInReturnScope() const;

  void setCurrentFunctionSymbol(const FunctionSymbol *function);

  const FunctionSymbol *getCurrentFunctionSymbol() const;

private:
  std::vector<std::unique_ptr<SymbolTable>> m_scope_stack;
  const FunctionSymbol *m_current_function_symbol = nullptr;
  int64_t m_break_scope_depth = 0;
};

} // namespace analysis
} // namespace flow_wing