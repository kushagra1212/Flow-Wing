#include "Interpreter.h"

Interpreter::Interpreter(BoundScopeGlobal *globalScope,
                         DiagnosticHandler *diagnosticHandler) {

  this->_globalScope = globalScope;
  this->_interpreterUtils =
      std::make_unique<InterpreterUtils>(diagnosticHandler);

  this->variable_stack.push(this->_globalScope->variables);
  this->function_stack.push(this->_globalScope->functions);
}

std::string Interpreter::getResult() {
  return InterpreterConversion::explicitConvertAnyToString(this->last_value);
}

void Interpreter::declareVariable(std::string name, Utils::Variable variable) {
  std::map<std::string, Utils::Variable> &current_scope =
      this->variable_stack.top();

  current_scope[name] = variable;
}

Utils::Variable Interpreter::getVariable(std::string name) {
  std::stack<std::map<std::string, Utils::Variable>> variable_stack_copy =
      this->variable_stack;

  while (!variable_stack_copy.empty()) {
    std::map<std::string, Utils::Variable> current_scope =
        variable_stack_copy.top();

    if (current_scope.find(name) != current_scope.end()) {
      return current_scope[name];
    }

    variable_stack_copy.pop();
  }

  this->_interpreterUtils->logError("Variable '" + name + "' Is Not Declared");

  return Utils::Variable();
}

void Interpreter::defineFunction(
    std::string name, BoundFunctionDeclaration *functionDeclaration) {
  std::map<std::string, BoundFunctionDeclaration *> &current_scope =
      this->function_stack.top();
  current_scope[name] = functionDeclaration;
}

BoundFunctionDeclaration *Interpreter::getFunction(std::string name) {
  std::stack<std::map<std::string, BoundFunctionDeclaration *>>
      function_stack_rest;

  while (!function_stack.empty()) {
    std::map<std::string, BoundFunctionDeclaration *> current_scope =
        function_stack.top();

    if (current_scope.find(name) != current_scope.end()) {

      while (!function_stack_rest.empty()) {
        function_stack.push(function_stack_rest.top());
        function_stack_rest.pop();
      }
      return current_scope[name];
    }
    function_stack_rest.push(current_scope);
    function_stack.pop();
  }
  while (!function_stack_rest.empty()) {
    function_stack.push(function_stack_rest.top());
    function_stack_rest.pop();
  }

  this->_interpreterUtils->logError("Function '" + name + "' Is Not Declared");

  return nullptr;
}

void Interpreter::assignVariable(std::string name, Utils::Variable variable) {
  std::stack<std::map<std::string, Utils::Variable>> variable_stack_copy;
  bool found = false;
  while (!this->variable_stack.empty()) {
    std::map<std::string, Utils::Variable> &current_scope =
        this->variable_stack.top();

    if (current_scope.find(name) != current_scope.end()) {
      current_scope[name] = variable;

      found = true;
      break;
    }

    variable_stack_copy.push(current_scope);

    this->variable_stack.pop();
  }
  while (!variable_stack_copy.empty()) {
    this->variable_stack.push(variable_stack_copy.top());
    variable_stack_copy.pop();
  }
  if (!found) {

    this->_interpreterUtils->logError("Variable '" + name +
                                      "' is not declared");
  }
}

void Interpreter::evaluateExpressionStatement(BoundExpressionStatement *node) {
  BoundExpressionStatement *expressionStatement =
      (BoundExpressionStatement *)node;
  this->_interpreterUtils->setCurrentSourceLocation(
      expressionStatement->getLocation());

  this->last_value =
      this->evaluate<std::any>(expressionStatement->getExpressionPtr().get());
}

void Interpreter::evaluateBlockStatement(BoundBlockStatement *node) {
  BoundBlockStatement *blockStatement = (BoundBlockStatement *)node;

  if (!blockStatement->getGlobal())
    this->variable_stack.push(std::map<std::string, Utils::Variable>());

  for (const auto &statement : blockStatement->getStatements()) {
    if (this->_interpreterUtils->getDiagnosticHandler()->hasError(
            DiagnosticUtils::DiagnosticType::Runtime))
      break;

    this->evaluateStatement(statement.get());
    if (break_count || continue_count ||
        (!return_type_stack.empty() && return_type_stack.top().second)) {
      break;
    }
  }

  if (!blockStatement->getGlobal())
    this->variable_stack.pop();
}

void Interpreter::evaluateVariableDeclaration(BoundVariableDeclaration *node) {
  BoundVariableDeclaration *variableDeclaration =
      (BoundVariableDeclaration *)node;

  this->_interpreterUtils->setCurrentSourceLocation(
      variableDeclaration->getLocation());

  std::string variable_name = variableDeclaration->getVariable();

  this->declareVariable(
      variable_name,
      Utils::Variable(this->evaluate<std::any>(
                          variableDeclaration->getInitializerPtr().get()),
                      variableDeclaration->isConst()));
}

void Interpreter::evaluateIfStatement(BoundIfStatement *node) {
  BoundIfStatement *ifStatement = (BoundIfStatement *)node;

  this->_interpreterUtils->setCurrentSourceLocation(ifStatement->getLocation());

  bool conditionDone = false;
  bool ifCondition = InterpreterConversion::explicitConvertAnyToBool(
      this->evaluate<std::any>(ifStatement->getConditionPtr().get()));

  if (ifCondition) {
    this->evaluateStatement(ifStatement->getThenStatementPtr().get());
    conditionDone = true;
  }

  if (!conditionDone) {
    for (const auto &elseIfStatement : ifStatement->getOrIfStatementsPtr()) {
      if (InterpreterConversion::explicitConvertAnyToBool(
              this->evaluate<std::any>(
                  elseIfStatement->getConditionPtr().get()))) {
        this->evaluateStatement(elseIfStatement->getThenStatementPtr().get());
        conditionDone = true;
        break;
      }
    }
  }

  if (ifStatement->getElseStatementPtr() != nullptr && !conditionDone) {
    this->evaluateStatement(ifStatement->getElseStatementPtr().get());
  }
}
void Interpreter::evaluateWhileStatement(BoundWhileStatement *node) {
  BoundWhileStatement *whileStatement = (BoundWhileStatement *)node;

  this->_interpreterUtils->setCurrentSourceLocation(
      whileStatement->getLocation());

  this->variable_stack.push(std::map<std::string, Utils::Variable>());

  while (true) {
    bool condition = InterpreterConversion::explicitConvertAnyToBool(
        this->evaluate<std::any>(whileStatement->getConditionPtr().get()));
    if (!condition)
      break;

    this->evaluateStatement(whileStatement->getBodyPtr().get());
    if (break_count) {
      break_count--;
      break;
    }
    if (continue_count) {
      continue_count--;
    }
    if (this->_interpreterUtils->getDiagnosticHandler()->hasError(
            DiagnosticUtils::DiagnosticType::Runtime)) {
      break;
    }
  }
  this->variable_stack.pop();
}
void Interpreter::execute(BoundBlockStatement *node) {

  for (const auto &statement : node->getStatements()) {
    if (this->_interpreterUtils->getDiagnosticHandler()->hasError(
            DiagnosticUtils::DiagnosticType::Runtime))
      break;

    if (statement.get()->getKind() == BinderKindUtils::BlockStatement) {

      showResult = 0;
    }

    this->evaluateStatement(statement.get());
    if (break_count || continue_count ||
        (!return_type_stack.empty() && return_type_stack.top().second)) {
      break;
    }
  }

  if (showResult && this->getResult() != "") {
    std::cout << this->getResult();
  }
}

void Interpreter::evaluateForStatement(BoundForStatement *node) {
  BoundForStatement *forStatement = (BoundForStatement *)node;

  this->_interpreterUtils->setCurrentSourceLocation(
      forStatement->getLocation());
  std::string variable_name = "";

  int stepValue = 1;

  if (forStatement->getStepExpressionPtr().get()) {

    stepValue = InterpreterConversion::explicitConvertAnyToInt(
        this->evaluate<std::any>(forStatement->getStepExpressionPtr().get()));
  }

  this->variable_stack.push(std::map<std::string, Utils::Variable>());
  std::any lowerBound = 0;
  if (forStatement->getInitializationPtr().get()->getKind() ==
      BinderKindUtils::BoundNodeKind::VariableDeclaration) {
    BoundVariableDeclaration *variableDeclaration =
        (BoundVariableDeclaration *)forStatement->getInitializationPtr().get();

    this->_interpreterUtils->setCurrentSourceLocation(
        variableDeclaration->getLocation());

    variable_name = variableDeclaration->getVariable();
    this->evaluateStatement(variableDeclaration);

    lowerBound = this->getVariable(variable_name).value;
  } else {
    this->evaluateStatement(forStatement->getInitializationPtr().get());

    lowerBound = this->last_value;
  }

  std::any upperBound =
      this->evaluate<std::any>(forStatement->getUpperBoundPtr().get());

  if (lowerBound.type() != upperBound.type()) {

    this->_interpreterUtils->logError(
        "Incompatible types in for statement condition " +
        std::to_string(lowerBound.type().hash_code()) + " and " +
        std::to_string(upperBound.type().hash_code()));

    return;
  }

  if (lowerBound.type() == typeid(int)) {
    int i = InterpreterConversion::explicitConvertAnyToInt(lowerBound);
    int ub = InterpreterConversion::explicitConvertAnyToInt(upperBound);
    while (true) {
      bool condition = stepValue < 0 ? i >= ub : i <= ub;
      if (!condition)
        break;

      if (variable_name != "") {
        this->assignVariable(
            variable_name,
            Utils::Variable(i, (this->getVariable(variable_name)).isConst));
      }
      this->evaluateStatement(forStatement->getStatementPtr().get());

      if (continue_count) {
        continue_count--;
      }
      if (break_count) {
        break_count--;
        break;
      }
      if (this->_interpreterUtils->getDiagnosticHandler()->hasError(
              DiagnosticUtils::DiagnosticType::Runtime)) {
        break;
      }
      i += stepValue;
    }
  } else {

    this->_interpreterUtils->logError(
        "Unexpected condition type in for statement condition " +
        std::to_string(lowerBound.type().hash_code()) + " and " +
        std::to_string(upperBound.type().hash_code()));
  }

  this->variable_stack.pop();
}

void Interpreter::evaluateStatement(BoundStatement *node) {
  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    this->evaluateExpressionStatement((BoundExpressionStatement *)node);
    break;
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

    showResult = 0;
    this->evaluateBlockStatement((BoundBlockStatement *)node);
    break;
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

    this->evaluateVariableDeclaration((BoundVariableDeclaration *)node);

    break;
  }
  case BinderKindUtils::BoundNodeKind::IfStatement: {

    this->evaluateIfStatement((BoundIfStatement *)node);
    break;
  }

  case BinderKindUtils::BoundNodeKind::WhileStatement: {

    this->evaluateWhileStatement((BoundWhileStatement *)node);
    break;
  }

  case BinderKindUtils::BoundNodeKind::ForStatement: {

    this->evaluateForStatement((BoundForStatement *)node);
    break;
  }

  case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {

    BoundFunctionDeclaration *functionDeclaration =
        (BoundFunctionDeclaration *)node;

    this->defineFunction(functionDeclaration->getFunctionNameRef(),
                         functionDeclaration);

    break;
  }

  case BinderKindUtils::BoundNodeKind::BreakStatement: {
    break_count++;
    break;
  }
  case BinderKindUtils::BoundNodeKind::ContinueStatement: {
    continue_count++;
    break;
  }
  case BinderKindUtils::BoundNodeKind::ReturnStatement: {
    BoundReturnStatement *returnStatement = (BoundReturnStatement *)node;

    this->_interpreterUtils->setCurrentSourceLocation(
        returnStatement->getLocation());

    Utils::type return_type = this->return_type_stack.top().first;

    if (return_type != Utils::type::NOTHING &&
        returnStatement->getReturnExpressionPtr() == nullptr) {

      this->_interpreterUtils->logError(
          "Function return type is not Nothing, return "
          "expression is not found");
    }

    else if (return_type == Utils::type::NOTHING &&
             returnStatement->getReturnExpressionPtr() != nullptr) {
      this->_interpreterUtils->logError(
          "Function return type is Nothing, return "
          "expression is found");
    } else {
      if (returnStatement->getReturnExpressionPtr() != nullptr) {
        this->last_value = this->evaluate<std::any>(
            returnStatement->getReturnExpressionPtr().get());

        if (Utils::getTypeFromAny(this->last_value) != return_type) {
          this->_interpreterUtils->logError(
              "Return Type Mismatch " + Utils::typeToString(return_type) +
              " is expected but " +
              Utils::typeToString(Utils::getTypeFromAny(this->last_value)) +
              " is found");
        } else {
          this->return_type_stack.top().second =
              this->return_type_stack.top().second + 1;
        }
      }
      break;
    }
  }
  default: {

    this->_interpreterUtils->logError(
        "Unexpected " + BinderKindUtils::to_string(node->getKind()));

    break;
  }
  }

  this->_globalScope->variables = this->variable_stack.top();
  this->_globalScope->functions = this->function_stack.top();
}

template <typename T>
T Interpreter::evaluateLiteralExpression(BoundExpression *node) {

  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)node;

  std::any value = literalExpression->getValue();

  this->_interpreterUtils->setCurrentSourceLocation(
      literalExpression->getLocation());

  if (value.type() == typeid(int)) {
    return std::any_cast<int>(value);
  } else if (value.type() == typeid(bool)) {
    return std::any_cast<bool>(value);
  } else if (value.type() == typeid(std::string)) {
    std::string str = std::any_cast<std::string>(value);
    if (Utils::isInteger(str)) {
      return InterpreterConversion::explicitConvertStringToInt(str);
    } else if (Utils::isDouble(str)) {
      return InterpreterConversion::explicitConvertStringToDouble(str);
    }
    return str;
  } else if (value.type() == typeid(double)) {
    return std::any_cast<double>(value);
  } else {

    this->_interpreterUtils->logError("Unexpected literal expression");
    return nullptr;
  }
}

template <typename T>
T Interpreter::evaluateUnaryExpression(BoundExpression *node) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
  std::any operand_any =
      (this->evaluate<std::any>(unaryExpression->getOperandPtr().get()));
  return this->unaryExpressionEvaluator(unaryExpression, operand_any);
}

template <typename T>
T Interpreter::evaluateVariableExpression(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  std::any variable = this->evaluate<std::any>(
      variableExpression->getIdentifierExpressionPtr().get());
  if (variable.type() != typeid(std::string)) {

    this->_interpreterUtils->logError("Unexpected variable name");
    return nullptr;
  }

  std::string variable_name = std::any_cast<std::string>(variable);
  switch (variableExpression->getKind()) {
  case BinderKindUtils::BoundNodeKind::VariableExpression: {
    return this->getVariable(variable_name).value;
  }
  default: {

    this->_interpreterUtils->logError("Unexpected variable name");
    return nullptr;
  }
  }
}

template <typename T>
T Interpreter::evaluateAssignmentExpression(BoundExpression *node) {
  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;

  this->_interpreterUtils->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  std::any variable =
      this->evaluate<std::any>(assignmentExpression->getLeftPtr().get());

  if (variable.type() != typeid(std::string)) {

    return nullptr;
  }
  std::string variable_name = std::any_cast<std::string>(variable);

  std::any evaluatedRight =
      this->evaluate<std::any>(assignmentExpression->getRightPtr().get());
  bool isConst = this->getVariable(variable_name).isConst;
  switch (assignmentExpression->getOperator()) {
  case BinderKindUtils::BoundBinaryOperatorKind::Assignment: {

    this->assignVariable(variable_name,
                         Utils::Variable(evaluatedRight, isConst));

    return this->getVariable(variable_name).value;
  }
  default: {

    this->_interpreterUtils->logError("Unexpected assignment operator");

    return nullptr;
  }
  }
}

template <typename T>
T Interpreter::evaluateBinaryExpression(BoundExpression *node) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;

  this->_interpreterUtils->setCurrentSourceLocation(
      binaryExpression->getLocation());

  std::any left_any =
      (this->evaluate<std::any>(binaryExpression->getLeftPtr().get()));
  std::any right_any =
      (this->evaluate<std::any>(binaryExpression->getRightPtr().get()));

  try {
    return this->binaryExpressionEvaluator<std::any>(binaryExpression, left_any,
                                                     right_any);
  } catch (const std::exception &e) {

    this->_interpreterUtils->logError(
        "Unexpected Binary Expression " +
        std::to_string(left_any.type().hash_code()) + " " +
        std::to_string(right_any.type().hash_code()));

    return nullptr;
  }
}

std::any
Interpreter::handleBuiltInFunction(BoundCallExpression *callExpression) {

  std::size_t arguments_size = callExpression->getArgumentsRef().size();
  const std::unique_ptr<BoundFunctionDeclaration> &fd =
      BuiltInFunction::getBuiltInFunction(callExpression->getCallerNameRef());

  if (fd->getFunctionNameRef() == FW::BI::FUNCTION::Input) {
    if (arguments_size == 0) {
      std::string input;
      std::getline(std::cin, input);
      return input;
    } else if (arguments_size == 1) {
      std::cout << InterpreterConversion::explicitConvertAnyToString(
          this->evaluate<std::any>(callExpression->getArgumentsRef()[0].get()));
      std::string input;
      std::getline(std::cin, input);
      return input;
    } else {

      this->_interpreterUtils->logError("Unexpected Function Call" +
                                        FW::BI::FUNCTION::Int32 +
                                        "Arguments Does  Not Match");

      return nullptr;
    }
  } else if (fd->getFunctionNameRef() == FW::BI::FUNCTION::Print) {
    if (arguments_size != 1) {

      this->_interpreterUtils->logError("Unexpected Function Call" +
                                        FW::BI::FUNCTION::Print +
                                        "Arguments Does  Not Match");

      return nullptr;
    } else {

      std::any value = (this->evaluate<std::any>(
          (BoundExpression *)callExpression->getArgumentsRef()[0].get()));

      try {
        std::cout << InterpreterConversion::explicitConvertAnyToString(value);
      } catch (const std::exception &e) {

        this->_interpreterUtils->logError(
            "Unexpected Function Call" + FW::BI::FUNCTION::Print +
            "Arguments Does  Not Match" + e.what());
      }
      return nullptr;
    }
    return nullptr;
  } else if (fd->getFunctionNameRef() == FW::BI::FUNCTION::String) {
    if (arguments_size == 1) {
      std::any value = (this->evaluate<std::any>(
          (BoundExpression *)callExpression->getArgumentsRef()[0].get()));
      return InterpreterConversion::explicitConvertAnyToString(value);
    }

    this->_interpreterUtils->logError("Unexpected Function Call" +
                                      FW::BI::FUNCTION::String +
                                      "Arguments Does  Not Match");
    return nullptr;
  } else if (fd->getFunctionNameRef() == FW::BI::FUNCTION::Int32) {
    if (arguments_size == 1) {
      std::any value = (this->evaluate<std::any>(
          (BoundExpression *)callExpression->getArgumentsRef()[0].get()));
      return InterpreterConversion::explicitConvertAnyToInt(value);
    }

    this->_interpreterUtils->logError("Unexpected Function Call" +
                                      FW::BI::FUNCTION::Int32 +
                                      "Arguments Does  Not Match");

    return nullptr;
  } else if (fd->getFunctionNameRef() == FW::BI::FUNCTION::Decimal) {
    if (arguments_size == 1) {
      std::any value = (this->evaluate<std::any>(
          (BoundExpression *)callExpression->getArgumentsRef()[0].get()));
      return InterpreterConversion::explicitConvertToAnyToDouble(value);
    }

    this->_interpreterUtils->logError("Unexpected Function Call" +
                                      FW::BI::FUNCTION::Decimal +
                                      "Arguments Does  Not Match");

    return nullptr;
  } else if (fd->getFunctionNameRef() == FW::BI::FUNCTION::Bool) {
    if (arguments_size == 1) {
      std::any value = (this->evaluate<std::any>(
          (BoundExpression *)callExpression->getArgumentsRef()[0].get()));
      return InterpreterConversion::explicitConvertAnyToBool(value);
    }

    this->_interpreterUtils->logError("Unexpected Function Call" +
                                      FW::BI::FUNCTION::Bool +
                                      "Arguments Does  Not Match");
    return nullptr;
  }
  return nullptr;
}

template <typename T>
T Interpreter::evaluateIndexExpression(BoundExpression *node) {
  BoundIndexExpression *indexExpression =
      static_cast<BoundIndexExpression *>(node);

  std::any value = this->evaluateVariableExpression<std::any>(
      (BoundExpression *)indexExpression->getBoundIdentifierExpression().get());

  std::any index = this->evaluate<std::any>(
      indexExpression->getBoundIndexExpression().get());

  int index_value = std::any_cast<int>(index);

  if (value.type() != typeid(std::string)) {
    this->_interpreterUtils->logError("String expected but " +
                                      Utils::getTypeString(value) + " found");
    return nullptr;
  }

  std::string var_value = std::any_cast<std::string>(value);

  if (index_value < 0 || index_value >= var_value.length()) {
    this->_interpreterUtils->logError("Index out of bound");
    return nullptr;
  }

  std::string result = "";
  result += var_value[index_value];
  return result;
}

template <typename T> T Interpreter::evaluate(BoundExpression *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression: {
    return this->evaluateLiteralExpression<T>(node);
  }
  case BinderKindUtils::BoundNodeKind::UnaryExpression: {
    return this->evaluateUnaryExpression<T>(node);
  }
  case BinderKindUtils::BoundNodeKind::VariableExpression: {
    return this->evaluateVariableExpression<T>(node);
  }

  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {
    return this->evaluateAssignmentExpression<T>(node);
  }
  case BinderKindUtils::BoundNodeKind::BinaryExpression: {
    return this->evaluateBinaryExpression<T>(node);
  }

  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {
    BoundParenthesizedExpression *parenthesizedExpression =
        (BoundParenthesizedExpression *)node;
    return this->evaluate<T>(parenthesizedExpression->getExpressionPtr().get());
  }
  case BinderKindUtils::BoundNodeKind::IndexExpression: {
    return this->evaluateIndexExpression<T>(node);
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {
    BoundCallExpression *callExpression = (BoundCallExpression *)node;

    this->_interpreterUtils->setCurrentSourceLocation(
        callExpression->getLocation());

    std::size_t arguments_size = callExpression->getArgumentsRef().size();

    // Built In Functions
    if (BuiltInFunction::isBuiltInFunction(
            callExpression->getCallerNameRef())) {
      return this->handleBuiltInFunction(callExpression);
    }

    BoundFunctionDeclaration *functionDefination =
        this->getFunction(callExpression->getCallerNameRef());

    if (functionDefination != nullptr) {

      this->_interpreterUtils->setCurrentSourceLocation(
          callExpression->getCallerIdentifierPtr().get()->getLocation());

      if (functionDefination->getParametersRef().size() != arguments_size) {

        this->_interpreterUtils->logError(
            "Unexpected Function Call" +
            functionDefination->getFunctionNameRef() +
            "Arguments Does  Not Match");

        return nullptr;
      }
      std::map<std::string, Utils::Variable> function_Variables;

      this->return_type_stack.push({functionDefination->getReturnType(), 0});

      for (int i = 0; i < arguments_size; i++) {
        std::any value = this->evaluate<std::any>(
            callExpression->getArgumentsRef()[i].get());

        function_Variables[functionDefination->getParametersRef()[i]
                               ->getVariableNameRef()] =
            Utils::Variable(
                value, functionDefination->getParametersRef()[i]->isConstant());
        if (this->_interpreterUtils->getDiagnosticHandler()->hasError(
                DiagnosticUtils::DiagnosticType::Runtime))
          break;
      }
      this->variable_stack.push(function_Variables);

      this->evaluateStatement(functionDefination->getBodyRef().get());

      if (this->return_type_stack.top().second == 0 &&
          Utils::type::NOTHING != functionDefination->getReturnType()) {
        this->_interpreterUtils->logError(
            "Function return type is not Nothing, return expression is not "
            "found");
      }

      this->return_type_stack.pop();

      this->variable_stack.pop();

      return this->last_value;
    } else {

      this->_interpreterUtils->logError(
          "Unexpected Function Call" +
          functionDefination->getFunctionNameRef() + "Not Found");

      return nullptr;
    }
  }

  default:
    break;
  }

  this->_interpreterUtils->logError(
      "Unexpected " + BinderKindUtils::to_string(node->getKind()));

  return nullptr;
}
std::any
Interpreter::unaryExpressionEvaluator(BoundUnaryExpression *unaryExpression,
                                      std::any operand) {

  BinderKindUtils::BoundUnaryOperatorKind op =
      unaryExpression->getOperatorPtr();
  if (operand.type() == typeid(int)) {
    return this->_interpreterUtils
        ->getResultFromUnaryExpressionEvaluatorHandlerForInt(
            op, std::any_cast<int>(operand));
  } else if (operand.type() == typeid(double)) {
    return this->_interpreterUtils
        ->getResultFromUnaryExpressionEvaluatorHandlerForDouble(
            op, std::any_cast<double>(operand));
  } else if (operand.type() == typeid(bool)) {
    return this->_interpreterUtils
        ->getResultFromUnaryExpressionEvaluatorHandlerForBool(
            op, std::any_cast<bool>(operand));
  } else if (operand.type() == typeid(std::string)) {
    return this->_interpreterUtils
        ->getResultFromUnaryExpressionEvaluatorHandlerForString(
            op, std::any_cast<std::string>(operand));
  }

  this->_interpreterUtils->logError("Unexpected operand type" +
                                    std::to_string(operand.type().hash_code()) +
                                    " for unary operator");
  return nullptr;
}

template <typename T>
T Interpreter::binaryExpressionEvaluator(
    BoundBinaryExpression *binaryExpression, T left, T right) {

  if (left.type() == typeid(std::string) ||
      right.type() == typeid(std::string)) {
    return this->_interpreterUtils->getResultFromBinaryOperationOnString(
        InterpreterConversion::explicitConvertAnyToString(left),
        InterpreterConversion::explicitConvertAnyToString(right),
        binaryExpression);
  } else if (left.type() == typeid(double) || right.type() == typeid(double)) {

    return this->_interpreterUtils->getResultFromBinaryOperationOnDouble(
        InterpreterConversion::explicitConvertToAnyToDouble(left),
        InterpreterConversion::explicitConvertToAnyToDouble(right),
        binaryExpression);
  } else if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
    return this->_interpreterUtils->getResultFromBinaryOperationOnBool(
        InterpreterConversion::explicitConvertAnyToBool(left),
        InterpreterConversion::explicitConvertAnyToBool(right),
        binaryExpression);
  } else {
    return this->_interpreterUtils->getResultFromBinaryOperationOnInt(
        InterpreterConversion::explicitConvertAnyToInt(left),
        InterpreterConversion::explicitConvertAnyToInt(right),
        binaryExpression);
  }

  this->_interpreterUtils->logError(
      "Unexpected operand type" + std::to_string(left.type().hash_code()) +
      " " + std::to_string(right.type().hash_code()) + " for binary operator");

  return nullptr;
}
