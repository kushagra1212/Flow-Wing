
#pragma once
#include "../bind/Binder/Binder.h"
#include "../syntax/SyntaxKindUtils.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/ExpressionSyntax.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../syntax/expression/UnaryExpressionSyntax.h"

#include "../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../bind/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../bind/BoundExpression.h"
#include "../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../utils/Utils.h"
#include <any>
#include <map>
#include <string>

class Evaluator {

public:
  BoundScopeGlobal *root = nullptr;
  std::any last_value = nullptr;
  CompilationUnitSyntax *compilation_unit = nullptr;
  Evaluator *previous = nullptr;
  std::stack<std::map<std::string, Utils::Variable>> variable_stack;
  std::stack<std::map<std::string, BoundFunctionDeclaration *>> function_stack;
  std::stack<int> return_count_stack;
  int break_count = 0, continue_count = 0;

  Evaluator(Evaluator *previous, CompilationUnitSyntax *compilation_unit);
  ~Evaluator();

public:
  BoundScopeGlobal *getRoot();

public:
  template <typename T> T evaluate(BoundExpression *node);

  template <typename T> T evaluateLiteralExpression(BoundExpression *node);

  template <typename T> T evaluateUnaryExpression(BoundExpression *node);

  template <typename T> T evaluateBinaryExpression(BoundExpression *node);

  template <typename T> T evaluateAssignmentExpression(BoundExpression *node);

  template <typename T> T evaluateVariableExpression(BoundExpression *node);

public:
  void declareVariable(std::string name, Utils::Variable variable);

  void defineFunction(std::string name,
                      BoundFunctionDeclaration *functionDeclaration);
  BoundFunctionDeclaration *getFunction(std::string name);

  Utils::Variable getVariable(std::string name);

  void assignVariable(std::string name, Utils::Variable variable);

  void evaluateStatement(BoundStatement *node);

  void evaluateExpressionStatement(BoundExpressionStatement *node);
  void evaluateBlockStatement(BoundBlockStatement *node);

  void evaluateVariableDeclaration(BoundVariableDeclaration *node);

  void evaluateIfStatement(BoundIfStatement *node);
  void evaluateWhileStatement(BoundWhileStatement *node);
  void evaluateForStatement(BoundForStatement *node);

  static std::vector<std::string> logs;
  template <typename T>
  static T
  binaryExpressionEvaluator(BinderKindUtils::BoundBinaryOperatorKind op, T left,
                            T right);

  template <typename T>
  static T unaryExpressionEvaluator(BinderKindUtils::BoundUnaryOperatorKind op,
                                    T operand);

  template <typename V, typename U>
  static U
  unaryExpressionEvaluatorHandler(BinderKindUtils::BoundUnaryOperatorKind op,
                                  V operand);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorIntIntHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorIntDoubleHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorDoubleIntHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorDoubleDoubleHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorStringStringHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorStringIntHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorIntStringHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorStringDoubleHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorDoubleStringHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorStringBoolHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorBoolStringHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorBoolBoolHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorBoolIntHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorIntBoolHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  // DoubleBool
  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorDoubleBoolHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);

  // BoolDouble
  template <typename V, typename U, typename Z>
  static Z binaryExpressionEvaluatorBoolDoubleHandler(
      BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
      const U &right);
};