#ifndef __FLOWWING_STATEMENT_GENERATION_STRATEGY_H__
#define __FLOWWING_STATEMENT_GENERATION_STRATEGY_H__
#include "../../GenerationStrategy.h"

class StatementGenerationStrategy : public GenerationStrategy {
public:
  CodeGenerationContext *_codeGenerationContext;

  StatementGenerationStrategy(CodeGenerationContext *context)
      : GenerationStrategy(context) {}

  virtual llvm::Value *generateStatement(BoundStatement *statement) = 0;
  virtual llvm::Value *generateGlobalStatement(BoundStatement *statement) = 0;
};

#endif // __FLOWWING_STATEMENT_GENERATION_STRATEGY_H__
