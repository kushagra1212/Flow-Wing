#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include <any>
#include <memory>

namespace flow_wing {
namespace binding {
class BinderContext;
}
namespace syntax {
class ParameterExpressionSyntax;
class ExpressionSyntax;
class ObjectTypeExpressionSyntax;
class ArrayTypeExpressionSyntax;
class DimensionClauseExpressionSyntax;
class ModuleAccessTypeExpressionSyntax;
class FunctionReturnTypeExpressionSyntax;
class FunctionTypeExpressionSyntax;
class BlockStatementSyntax;
} // namespace syntax
namespace analysis {

class TypeResolver {
public:
  explicit TypeResolver(binding::BinderContext *ctx);

  std::pair<std::shared_ptr<types::Type>,
            std::unique_ptr<binding::BoundErrorExpression>>
  resolveType(const syntax::ExpressionSyntax *syntax);

  std::pair<std::shared_ptr<types::Type>,
            std::unique_ptr<binding::BoundErrorExpression>>
  resolveObjectType(const syntax::ObjectTypeExpressionSyntax *syntax);

  std::pair<std::shared_ptr<types::Type>,
            std::unique_ptr<binding::BoundErrorExpression>>
  resolveArrayType(const syntax::ArrayTypeExpressionSyntax *syntax);

  std::shared_ptr<types::ParameterType>
  resolveParameterExpression(const syntax::ParameterExpressionSyntax *syntax);

  std::pair<std::vector<std::shared_ptr<types::ReturnType>>,
            std::unique_ptr<binding::BoundErrorExpression>>
  resolveReturnType(const syntax::FunctionReturnTypeExpressionSyntax *syntax);

  /// When a function/method omits `-> Type`, infer return type: `nthg` if there
  /// is no return statement, otherwise `dynamic` (same as
  /// resolveType(nullptr)).
  std::shared_ptr<types::Type>
  inferImplicitReturnTypeFromBody(syntax::BlockStatementSyntax *body);

  std::pair<std::shared_ptr<types::Type>,
            std::unique_ptr<binding::BoundErrorExpression>>
  resolveModuleAccessType(
      const syntax::ModuleAccessTypeExpressionSyntax *syntax);

  std::pair<std::shared_ptr<types::Type>,
            std::unique_ptr<binding::BoundErrorExpression>>
  resolveFunctionType(const syntax::FunctionTypeExpressionSyntax *syntax);

  static types::ValueKind getValueKind(const bool has_inout_keyword);
  static types::Constness getConstness(const bool has_const_keyword);
  static types::TypeConvention getTypeConvention(const bool has_as_keyword);

private:
  binding::BinderContext *m_ctx;

  std::unique_ptr<binding::BoundErrorExpression>
  populateDimensionValue(const syntax::DimensionClauseExpressionSyntax *syntax,
                         int64_t &value);
};

} // namespace analysis
} // namespace flow_wing
