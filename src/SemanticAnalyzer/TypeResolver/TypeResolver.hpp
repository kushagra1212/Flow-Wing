#pragma once

#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include <any>

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
} // namespace syntax
namespace analysis {

class TypeResolver {
public:
  explicit TypeResolver(binding::BinderContext *ctx);

  std::shared_ptr<types::Type>
  resolveType(const syntax::ExpressionSyntax *syntax);

  std::shared_ptr<types::Type>
  resolveObjectType(const syntax::ObjectTypeExpressionSyntax *syntax);

  std::shared_ptr<types::Type>
  resolveArrayType(const syntax::ArrayTypeExpressionSyntax *syntax);

  std::shared_ptr<types::ParameterType>
  resolveParameterExpression(const syntax::ParameterExpressionSyntax *syntax);

  std::vector<std::shared_ptr<types::ReturnType>>
  resolveReturnType(const syntax::FunctionReturnTypeExpressionSyntax *syntax);

  std::shared_ptr<types::Type> resolveModuleAccessType(
      const syntax::ModuleAccessTypeExpressionSyntax *syntax);

  std::shared_ptr<types::Type>
  resolveFunctionType(const syntax::FunctionTypeExpressionSyntax *syntax);

  static types::ValueKind getValueKind(const bool has_inout_keyword);
  static types::Constness getConstness(const bool has_const_keyword);
  static types::TypeConvention getTypeConvention(const bool has_as_keyword);

private:
  binding::BinderContext *m_ctx;

  bool
  populateDimensionValue(const syntax::DimensionClauseExpressionSyntax *syntax,
                         int64_t &value);
};

} // namespace analysis
} // namespace flow_wing
