
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <any>
#include <map>
#include <string>

#include "../SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundParenthesizedExpression/BoundParenthesizedExpression.h"

#include "../SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../SemanticAnalyzer/BoundStatements/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundForStatement/BoundForStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundReturnStatement/BoundReturnStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.h"
#include "../SemanticAnalyzer/SemanticAnalyzer.h"
#include "../diagnostics/Diagnostic/Diagnostic.h"
#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "../syntax/SyntaxKindUtils.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/ExpressionSyntax.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../syntax/expression/UnaryExpressionSyntax.h"
#include "../utils/Utils.h"
#include "InterpreterUtils/InterpreterConversions/InterpreterConversion.h"
#include "InterpreterUtils/InterpreterUtils.h"

class Interpreter {
private:
public:
  Interpreter(BoundGlobalScope *globalScope,
              FlowWing::DiagnosticHandler *diagnosticHandler);

  void execute(BoundBlockStatement *node);
  std::string getResult();

private:
  std::any last_value = nullptr;
  CompilationUnitSyntax *compilation_unit = nullptr;
  Interpreter *previous = nullptr;
  std::stack<std::unordered_map<std::string, BoundVariableDeclaration *>>
      variable_stack;
  std::stack<std::unordered_map<std::string, std::any>> value_stack;

  std::stack<std::unordered_map<std::string, BoundFunctionDeclaration *>>
      function_stack;
  std::stack<std::pair<SyntaxKindUtils::SyntaxKind, int>> return_type_stack;
  BoundGlobalScope *_globalScope = nullptr;
  std::unique_ptr<InterpreterUtils> _interpreterUtils;
  int break_count = 0, continue_count = 0, showResult = 1;

  void evaluateExpressionStatement(BoundExpressionStatement *node);
  void evaluateBlockStatement(BoundBlockStatement *node);
  void evaluateVariableDeclaration(BoundVariableDeclaration *node);
  void evaluateIfStatement(BoundIfStatement *node);
  void evaluateWhileStatement(BoundWhileStatement *node);
  void evaluateForStatement(BoundForStatement *node);
  void assignVariable(std::string name, std::any val);
  void evaluateStatement(BoundStatement *node);
  void declareVariable(std::string name, BoundVariableDeclaration *variable);
  void defineFunction(std::string name,
                      BoundFunctionDeclaration *functionDeclaration);

  BoundFunctionDeclaration *getFunction(std::string name);
  std::any getVariable(const std::string &name);
  template <typename T> T evaluateLiteralExpression(BoundExpression *node);
  template <typename T> T evaluateUnaryExpression(BoundExpression *node);
  template <typename T> T evaluateBinaryExpression(BoundExpression *node);
  template <typename T> T evaluateAssignmentExpression(BoundExpression *node);
  template <typename T> T evaluateVariableExpression(BoundExpression *node);
  template <typename T> T evaluateIndexExpression(BoundExpression *node);
  template <typename T> T evaluate(BoundExpression *node);

  std::any handleBuiltInFunction(BoundCallExpression *node);

  std::any unaryExpressionEvaluator(BoundUnaryExpression *unaryExpression,
                                    std::any operand);

  template <typename T>
  T binaryExpressionEvaluator(BoundBinaryExpression *binaryExpression, T left,
                              T right);
};

#endif // INTERPRETER_H