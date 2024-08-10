#ifndef __FLOWWING_STATEMENT_GENERATION_FACTORY_STRATEGY_H__
#define __FLOWWING_STATEMENT_GENERATION_FACTORY_STRATEGY_H__

class StatementGenerationStrategy;
class CodeGenerationContext;
#include "../../../bind/BinderKindUtils.h"

class StatementGenerationFactory {
public:
  CodeGenerationContext *_codeGenerationContext;

  StatementGenerationFactory(CodeGenerationContext *context);

  std::unique_ptr<StatementGenerationStrategy>
  createStrategy(BinderKindUtils::BoundNodeKind kind);
};

#endif // __FLOWWING_STATEMENT_GENERATION_FACTORY_STRATEGY_H__