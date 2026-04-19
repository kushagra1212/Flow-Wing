#pragma once

#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/CompilationUnitBinder.hpp"
#include <memory>

namespace flow_wing {
namespace binding {
class BoundStatement;
} // namespace binding

namespace analysis {

class Binder {
public:
  Binder(binding::BinderContext &binder_context);

  std::unique_ptr<binding::BoundCompilationUnit> bindRoot();

private:
  binding::BinderContext &m_binder_context;
};

} // namespace analysis
} // namespace flow_wing