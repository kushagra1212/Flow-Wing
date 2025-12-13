#pragma once

#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/syntax/CompilationUnitSyntax.h"
#include <memory>

namespace flow_wing {
namespace analysis {
class ScopedSymbolTable;
} // namespace analysis

namespace binding {

class BinderContext;

class CompilationUnitBinder {
public:
  CompilationUnitBinder(BinderContext *context);

  std::unique_ptr<binding::BoundCompilationUnit>
  bind(syntax::CompilationUnitSyntax *syntax);

  // Getters
  std::shared_ptr<analysis::ScopedSymbolTable> getSymbolTable() const;

private:
  BinderContext *m_context;

  std::shared_ptr<analysis::ScopedSymbolTable> m_symbol_table;
};
} // namespace binding
} // namespace flow_wing