#ifndef __FLOWWING_IR__CODE_GENERATOR_H__
#define __FLOWWING_IR__CODE_GENERATOR_H__

#include "../../expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "../../expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "../../expressions/MultipleAssignmentExpressionGenerationStrategy/MultipleAssignmentExpressionGenerationStrategy.h"
#include "../../statements/BringStatementGenerationStrategy/BringStatementGenerationStrategy.h"
#include "../../statements/ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "../../statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../../statements/MultipleVariableDeclarationStatementGenerationStrategy/MultipleVariableDeclarationStatementGenerationStrategy.h"
#include "../../statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"

class IRCodeGenerator {
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      _variableDeclarationStatementGenerationStrategy;
  std::unique_ptr<MultipleVariableDeclarationStatementGenerationStrategy>
      _multipleVariableDeclarationStatementGenerationStrategy;

  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      _customTypeStatementGenerationStrategy;
  std::unique_ptr<ClassStatementGenerationStrategy>
      _classStatementGenerationStrategy;
  std::unique_ptr<CallExpressionGenerationStrategy>
      _callExpressionGenerationStrategy;
  std::unique_ptr<AssignmentExpressionGenerationStrategy>
      _assignmentExpressionGenerationStrategy;

  std::unique_ptr<MultipleAssignmentExpressionGenerationStrategy>
      _multipleAssignmentExpressionGenerationStrategy;

  void processChildForDeclaration(BoundNode *child, bool isGlobal);
  void processChildForCustomType(BoundNode *child);

public:
  IRCodeGenerator(CodeGenerationContext *context);
  void declareVariables(BoundNode *node, bool isGlobal);
  void declareCustomType(BoundNode *node);
  CodeGenerationContext *_codeGenerationContext;
};

#endif
