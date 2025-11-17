#pragma once

#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/syntax/CompilationUnitSyntax.h"
#include <memory>

namespace flow_wing {

namespace binding {

class BinderContext;

class CompilationUnitBinder {
public:
  CompilationUnitBinder(BinderContext *context);

  std::unique_ptr<binding::BoundCompilationUnit>
  bind(syntax::CompilationUnitSyntax *syntax);

private:
  BinderContext *m_context;
};
} // namespace binding
} // namespace flow_wing