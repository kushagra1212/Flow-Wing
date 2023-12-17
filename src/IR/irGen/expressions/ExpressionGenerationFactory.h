#ifndef __FLOWWING_EXPRESSION_GENERATION_FACTORY_STRATEGY_H__
#define __FLOWWING_EXPRESSION_GENERATION_FACTORY_STRATEGY_H__

class ExpressionGenerationStrategy;
class CodeGenerationContext;
#include "../../../bind/BinderKindUtils.h"

class ExpressionGenerationFactory {
public:
  CodeGenerationContext *_codeGenerationContext;

  ExpressionGenerationFactory(CodeGenerationContext *context);

  template <typename... Args>
  std::unique_ptr<ExpressionGenerationStrategy>
  createStrategy(BinderKindUtils::BoundNodeKind kind, Args... args);
};

#endif // __FLOWWING_EXPRESSION_GENERATION_FACTORY_STRATEGY_H__