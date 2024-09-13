#ifndef __FLOWWING_STATEMENT_GENERATION_STRATEGY_H__
#define __FLOWWING_STATEMENT_GENERATION_STRATEGY_H__
#include "../../GenerationStrategy.h"

class LLVMTypeGenerationFactory;
class StatementGenerationStrategy : public GenerationStrategy {
 public:
  StatementGenerationStrategy(CodeGenerationContext *context)
      : GenerationStrategy(context) {}

  virtual llvm::Value *generateStatement(BoundStatement *statement) = 0;
  virtual llvm::Value *generateGlobalStatement(BoundStatement *statement) = 0;
  virtual ~StatementGenerationStrategy() = default;
};

#endif  // __FLOWWING_STATEMENT_GENERATION_STRATEGY_H__
