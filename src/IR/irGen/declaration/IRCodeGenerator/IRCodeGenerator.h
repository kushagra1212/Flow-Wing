#ifndef __FLOWWING_IR__CODE_GENERATOR_H__
#define __FLOWWING_IR__CODE_GENERATOR_H__

#include "../../expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "../../statements/ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "../../statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../../statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"

class IRCodeGenerator {
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      _variableDeclarationStatementGenerationStrategy;
  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      _customTypeStatementGenerationStrategy;
  std::unique_ptr<ClassStatementGenerationStrategy>
      _classStatementGenerationStrategy;
  std::unique_ptr<CallExpressionGenerationStrategy>
      _callExpressionGenerationStrategy;

  void processChildForDeclaration(BoundNode *child, bool isGlobal);
  void processChildForCustomType(BoundNode *child);

public:
  IRCodeGenerator(CodeGenerationContext *context);
  void declareVariables(BoundStatement *statement, bool isGlobal);
  void declareVariables(BoundNode *node, bool isGlobal);
  void declareCustomType(BoundStatement *statement);
  void declareCustomType(BoundNode *node);
};

#endif
