#pragma once

#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include <cstdint>
#include <vector>
#include <memory>

namespace flow_wing {

namespace analysis {
class TypeResolver;
} // namespace analysis

class CompilationContext;

namespace diagnostic {
enum class DiagnosticCode : int16_t;
struct SourceLocation;
} // namespace diagnostic

namespace analysis {
class ScopedSymbolTable;
} // namespace analysis

namespace binding {

class BinderContext {
public:
  BinderContext(CompilationContext &context);
  ~BinderContext();

  //? Error Reporting
  void
  reportError(flow_wing::diagnostic::DiagnosticCode code,
              const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
              const flow_wing::diagnostic::SourceLocation &location);

  void reportError(binding::BoundErrorExpression *error_expression);
  void reportError(binding::BoundErrorStatement *error_statement);

  // Setters
  void
  switchSymbolTable(std::shared_ptr<analysis::ScopedSymbolTable> symbol_table);

  // Getters
  const CompilationContext &getCompilationContext() const;
  const std::shared_ptr<analysis::ScopedSymbolTable> &getSymbolTable() const;
  const std::unique_ptr<analysis::TypeResolver> &getTypeResolver() const;

  static std::unique_ptr<BoundExpression>
  createDefaultValueExpression(types::Type *type,
                               const diagnostic::SourceLocation &location);

private:
  CompilationContext &m_context;
  std::unique_ptr<analysis::TypeResolver> m_type_resolver;
  std::shared_ptr<analysis::ScopedSymbolTable> m_symbol_table;
};
} // namespace binding
} // namespace flow_wing
