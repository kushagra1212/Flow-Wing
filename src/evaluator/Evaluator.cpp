#include "Evaluator.h"
template class BoundLiteralExpression<std::any>;
template class BoundLiteralExpression<int>;
template class BoundLiteralExpression<double>;
template class BoundLiteralExpression<bool>;
template class BoundLiteralExpression<std::string>;
template class BoundLiteralExpression<char>;

Evaluator::Evaluator(Evaluator *previous,
                     CompilationUnitSyntax *compilation_unit) {
  this->compilation_unit = compilation_unit;

  this->previous = previous;
}

bool Evaluator::hasError() { return this->root->logs.size() > 0; }

Evaluator::~Evaluator() {
  // if (this->root != nullptr) {
  //   delete this->root;
  //   this->root = nullptr;
  // }

  // if (this->compilation_unit != nullptr) {
  //   delete this->compilation_unit;
  //   this->compilation_unit = nullptr;
  // }

  // if (this->previous != nullptr) {
  //   delete this->previous;
  //   this->previous = nullptr;
  // }
}

BoundScopeGlobal *Evaluator::getRoot() {
  if (root == nullptr) {
    if (previous != nullptr)
      root = Binder::bindGlobalScope(previous->root, compilation_unit);
    else
      root = Binder::bindGlobalScope(nullptr, compilation_unit);

    this->variable_stack.push(this->root->variables);
    this->function_stack.push(this->root->functions);
  }
  return root;
}

void Evaluator::declareVariable(std::string name, Utils::Variable variable) {
  std::map<std::string, Utils::Variable> &current_scope =
      this->variable_stack.top();

  current_scope[name] = variable;
}

Utils::Variable Evaluator::getVariable(std::string name) {
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

  this->root->logs.push_back("Error: Variable '" + name + "' is not declared");
  return Utils::Variable();
}

void Evaluator::defineFunction(std::string name,
                               BoundFunctionDeclaration *functionDeclaration) {
  std::map<std::string, BoundFunctionDeclaration *> &current_scope =
      this->function_stack.top();
  current_scope[name] = functionDeclaration;
}

BoundFunctionDeclaration *Evaluator::_getFunction(std::string name) {
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

  this->root->logs.push_back("Error: Function '" + name + "' is not declared");
  return nullptr;
}

void Evaluator::assignVariable(std::string name, Utils::Variable variable) {
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
    this->root->logs.push_back("Error: Variable '" + name +
                               "' is not declared");
  }
}

void Evaluator::evaluateExpressionStatement(BoundExpressionStatement *node) {

  last_value = this->evaluate<std::any>(node->getExpression());
}

void Evaluator::evaluateBlockStatement(BoundBlockStatement *node) {
  BoundBlockStatement *blockStatement = (BoundBlockStatement *)node;
  std::vector<BoundStatement *> statements = blockStatement->getStatements();

  if (!blockStatement->getGlobal())
    this->variable_stack.push(std::map<std::string, Utils::Variable>());

  for (BoundStatement *statement : statements) {
    if (this->hasError())
      break;
    this->evaluateStatement(statement);
    if (break_count || continue_count ||
        (!return_count_stack.empty() && return_count_stack.top())) {
      break;
    }
  }

  if (!blockStatement->getGlobal())
    this->variable_stack.pop();
}

void Evaluator::evaluateVariableDeclaration(BoundVariableDeclaration *node) {
  BoundVariableDeclaration *variableDeclaration =
      (BoundVariableDeclaration *)node;
  std::string variable_name = variableDeclaration->getVariable();

  this->declareVariable(
      variable_name, Utils::Variable(this->evaluate<std::any>(
                                         variableDeclaration->getInitializer()),
                                     variableDeclaration->isConst()));

  last_value = this->getVariable(variable_name).value;
}

void Evaluator::evaluateIfStatement(BoundIfStatement *node) {
  BoundIfStatement *ifStatement = (BoundIfStatement *)node;
  std::any condition = this->evaluate<std::any>(ifStatement->getCondition());

  if (condition.type() == typeid(bool)) {
    if (std::any_cast<bool>(condition)) {
      this->evaluateStatement(ifStatement->getThenStatement());
    } else if (ifStatement->getElseStatement() != nullptr) {
      this->evaluateStatement(ifStatement->getElseStatement());
    }
  } else if (condition.type() == typeid(int)) {
    if (std::any_cast<int>(condition)) {
      this->evaluateStatement(ifStatement->getThenStatement());
    } else if (ifStatement->getElseStatement() != nullptr) {
      this->evaluateStatement(ifStatement->getElseStatement());
    }
  } else {
    this->root->logs.push_back(
        ifStatement->getCondition()->getLineNumberAndColumn() +
        "Error: Unexpected condition type");
    return;
  }
}
void Evaluator::evaluateWhileStatement(BoundWhileStatement *node) {
  BoundWhileStatement *whileStatement = (BoundWhileStatement *)node;

  this->variable_stack.push(std::map<std::string, Utils::Variable>());
  std::any condition = this->evaluate<std::any>(whileStatement->getCondition());

  if (condition.type() == typeid(bool)) {
    while (std::any_cast<bool>(condition)) {
      this->evaluateStatement(whileStatement->getBody());
      condition = this->evaluate<std::any>(whileStatement->getCondition());
      if (break_count) {
        break_count--;
        break;
      }
      if (continue_count) {
        continue_count--;
      }
      if (this->hasError()) {
        break;
      }
    }
  } else if (condition.type() == typeid(int)) {
    while (std::any_cast<int>(condition)) {

      this->evaluateStatement(whileStatement->getBody());
      condition = this->evaluate<std::any>(whileStatement->getCondition());
      if (break_count) {
        break_count--;
        break;
      }
      if (continue_count) {
        continue_count--;
      }
      if (this->hasError()) {
        break;
      }
    }
  } else {
    this->root->logs.push_back(
        whileStatement->getCondition()->getLineNumberAndColumn() +
        "Error: Unexpected condition type");
  }
  this->variable_stack.pop();
}

void Evaluator::evaluateForStatement(BoundForStatement *node) {
  BoundForStatement *forStatement = (BoundForStatement *)node;
  std::string variable_name = "";

  this->variable_stack.push(std::map<std::string, Utils::Variable>());
  std::any lowerBound = 0;
  if (forStatement->getInitialization()->getKind() ==
      BinderKindUtils::BoundNodeKind::VariableDeclaration) {
    BoundVariableDeclaration *variableDeclaration =
        (BoundVariableDeclaration *)forStatement->getInitialization();

    variable_name = variableDeclaration->getVariable();
    this->evaluateStatement(variableDeclaration);

    lowerBound = this->getVariable(variable_name).value;
  } else {
    this->evaluateStatement(forStatement->getInitialization());

    lowerBound = this->last_value;
  }

  std::any upperBound = this->evaluate<std::any>(forStatement->getUpperBound());

  if (lowerBound.type() != upperBound.type()) {
    this->root->logs.push_back(
        forStatement->getUpperBound()->getLineNumberAndColumn() +
        "Error: Incompatible types");
    return;
  }

  if (lowerBound.type() == typeid(int)) {
    for (int i = std::any_cast<int>(lowerBound);
         i <= std::any_cast<int>(upperBound); i++) {
      if (variable_name != "") {
        this->assignVariable(
            variable_name,
            Utils::Variable(i, (this->getVariable(variable_name)).isConst));
      }
      this->evaluateStatement(forStatement->getStatement());

      if (continue_count) {
        continue_count--;
      }
      if (break_count) {
        break_count--;
        break;
      }
      if (this->hasError()) {
        break;
      }
    }
  } else {
    this->root->logs.push_back(
        forStatement->getInitialization()->getLineNumberAndColumn() +
        "Error: Unexpected condition type");
  }

  this->variable_stack.pop();
}

void Evaluator::evaluator(BoundStatement *node) {

  this->evaluateStatement(node);
}

void Evaluator::evaluateStatement(BoundStatement *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    // Print the generated IR

    this->evaluateExpressionStatement((BoundExpressionStatement *)node);

    break;
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

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
    this->defineFunction(functionDeclaration->functionSymbol.name,
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

    int &return_count = this->return_count_stack.top();
    return_count = return_count + 1;
    if (returnStatement->getReturnExpression() != nullptr) {
      this->last_value =
          this->evaluate<std::any>(returnStatement->getReturnExpression());
    }
    break;
  }
  default: {
    this->root->logs.push_back(node->getLineNumberAndColumn() +
                               "Error: Unexpected node" +
                               BinderKindUtils::to_string(node->getKind()));
  }
  }

  this->root->variables = this->variable_stack.top();
  this->root->functions = this->function_stack.top();
}

template <typename T>
T Evaluator::evaluateLiteralExpression(BoundExpression *node) {
  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();
  if (value.type() == typeid(int)) {
    return std::any_cast<int>(value);
  } else if (value.type() == typeid(bool)) {
    return std::any_cast<bool>(value);
  } else if (value.type() == typeid(std::string)) {
    return std::any_cast<std::string>(value);
  } else if (value.type() == typeid(double)) {
    return std::any_cast<double>(value);
  } else {
    this->root->logs.push_back(node->getLineNumberAndColumn() +
                               "Error: Unexpected literal expression");
    return nullptr;
  }
}

template <typename T>
T Evaluator::evaluateUnaryExpression(BoundExpression *node) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
  std::any operand_any =
      (this->evaluate<std::any>(unaryExpression->getOperand()));

  return Evaluator::unaryExpressionEvaluator<std::any>(
      unaryExpression->getOperator(), operand_any);
}

template <typename T>
T Evaluator::evaluateVariableExpression(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  std::any variable =
      this->evaluate<std::any>(variableExpression->getIdentifierExpression());
  if (variable.type() != typeid(std::string)) {
    this->root->logs.push_back(variableExpression->getIdentifierExpression()
                                   ->getLineNumberAndColumn() +
                               "Error: Unexpected variable name");
    return nullptr;
  }

  std::string variable_name = std::any_cast<std::string>(variable);
  switch (variableExpression->getKind()) {
  case BinderKindUtils::BoundNodeKind::VariableExpression: {
    return this->getVariable(variable_name).value;
  }
  default:
    this->root->logs.push_back(variableExpression->getIdentifierExpression()
                                   ->getLineNumberAndColumn() +
                               "Error: Unexpected Variable found");
    return nullptr;
  }
}

template <typename T>
T Evaluator::evaluateAssignmentExpression(BoundExpression *node) {
  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;

  std::any variable = this->evaluate<std::any>(assignmentExpression->getLeft());

  if (variable.type() != typeid(std::string)) {
    this->root->logs.push_back(
        assignmentExpression->getLeft()->getLineNumberAndColumn() +
        "Error Unexpected variable name");
    return nullptr;
  }
  std::string variable_name = std::any_cast<std::string>(variable);

  std::any evaluatedRight =
      this->evaluate<std::any>(assignmentExpression->getRight());

  bool isConst = this->getVariable(variable_name).isConst;
  switch (assignmentExpression->getOperator()) {
  case BinderKindUtils::BoundBinaryOperatorKind::Assignment: {

    this->assignVariable(variable_name,
                         Utils::Variable(evaluatedRight, isConst));

    this->last_value = this->getVariable(variable_name).value;
    return this->getVariable(variable_name).value;
  }
  default:
    this->root->logs.push_back(assignmentExpression->getLineNumberAndColumn() +
                               "Error: Unexpected assignment operator");
    return nullptr;
  }
}

template <typename T>
T Evaluator::evaluateBinaryExpression(BoundExpression *node) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;
  std::any left_any = (this->evaluate<std::any>(binaryExpression->getLeft()));
  std::any right_any = (this->evaluate<std::any>(binaryExpression->getRight()));

  try {
    return this->binaryExpressionEvaluator<std::any>(
        binaryExpression->getOperator(), left_any, right_any);
  } catch (const std::exception &e) {
    this->root->logs.push_back(binaryExpression->getLineNumberAndColumn() +
                               e.what());
    return nullptr;
  }
}

template <typename T> T Evaluator::evaluate(BoundExpression *node) {

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
    return this->evaluate<T>(parenthesizedExpression->getExpression());
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {
    BoundCallExpression *callExpression = (BoundCallExpression *)node;

    Utils::FunctionSymbol function = callExpression->getFunctionSymbol();

    std::size_t arguments_size = callExpression->getArguments().size();

    if (function.name == Utils::BuiltInFunctions::input.name) {

      if (arguments_size == 0) {
        std::string input;
        std::getline(std::cin, input);
        return input;
      } else if (arguments_size == 1) {
        std::cout << std::any_cast<std::string>(
            this->evaluate<std::any>(callExpression->getArguments()[0]));
        std::string input;
        std::getline(std::cin, input);
        return input;
      } else {
        this->root->logs.push_back(
            callExpression->getArguments()[0]->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      }

    } else if (function.name == Utils::BuiltInFunctions::print.name) {

      if (arguments_size == 0) {

        this->root->logs.push_back(
            callExpression->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      } else if (arguments_size == 1) {

        std::any value = (this->evaluate<std::any>(
            (BoundExpression *)callExpression->getArguments()[0]));

        try {
          std::cout << Utils::convertAnyToString(value);
        } catch (const std::exception &e) {
          this->root->logs.push_back(
              callExpression->getArguments()[0]->getLineNumberAndColumn() +
              e.what());
        }
        return nullptr;
      } else {
        this->root->logs.push_back(
            callExpression->getArguments()[0]->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      }
      return nullptr;
    } else if (function.name == Utils::BuiltInFunctions::String.name) {
      if (arguments_size == 1) {
        std::any value = (this->evaluate<std::any>(
            (BoundExpression *)callExpression->getArguments()[0]));
        if (value.type() == typeid(std::string)) {
          return std::any_cast<std::string>(value);
        } else if (value.type() == typeid(int)) {
          return std::to_string(std::any_cast<int>(value));
        } else if (value.type() == typeid(double)) {
          return std::to_string(std::any_cast<double>(value));
        } else if (value.type() == typeid(bool)) {
          return std::to_string(std::any_cast<bool>(value));
        } else {
          this->root->logs.push_back(
              callExpression->getArguments()[0]->getLineNumberAndColumn() +
              "Error: Unexpected function call "
              "argument: required string");
          return nullptr;
        }
      } else {
        this->root->logs.push_back(
            callExpression->getArguments()[0]->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      }
    } else if (function.name == Utils::BuiltInFunctions::Int32.name) {
      if (arguments_size == 1) {
        std::any value = (this->evaluate<std::any>(
            (BoundExpression *)callExpression->getArguments()[0]));
        if (value.type() == typeid(std::string)) {
          return std::stoi(std::any_cast<std::string>(value));
        } else if (value.type() == typeid(int)) {
          return std::any_cast<int>(value);
        } else if (value.type() == typeid(double)) {
          return int(std::any_cast<double>(value));
        } else if (value.type() == typeid(bool)) {
          return int(std::any_cast<bool>(value));
        } else {
          this->root->logs.push_back(
              callExpression->getArguments()[0]->getLineNumberAndColumn() +
              "Error: Unexpected function call argument: required int");
          return nullptr;
        }
      } else {
        this->root->logs.push_back(
            callExpression->getArguments()[0]->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      }
    } else if (function.name == Utils::BuiltInFunctions::Double.name) {
      if (arguments_size == 1) {
        std::any value = (this->evaluate<std::any>(
            (BoundExpression *)callExpression->getArguments()[0]));
        if (value.type() == typeid(std::string)) {
          return std::stod(std::any_cast<std::string>(value));
        } else if (value.type() == typeid(int)) {
          return double(std::any_cast<int>(value));
        } else if (value.type() == typeid(double)) {
          return std::any_cast<double>(value);
        } else if (value.type() == typeid(bool)) {
          return double(std::any_cast<bool>(value));
        } else {
          this->root->logs.push_back(
              callExpression->getArguments()[0]->getLineNumberAndColumn() +
              "Error: Unexpected function call argument: required double");
          return nullptr;
        }
      } else {
        this->root->logs.push_back(
            callExpression->getArguments()[0]->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      }
    } else if (function.name == Utils::BuiltInFunctions::Bool.name) {
      if (arguments_size == 1) {
        std::any value = (this->evaluate<std::any>(
            (BoundExpression *)callExpression->getArguments()[0]));
        if (value.type() == typeid(std::string)) {
          bool is = std::any_cast<std::string>(value) == "false" ||
                    std::any_cast<std::string>(value) == "0";
          return !is;
        } else if (value.type() == typeid(int)) {
          return std::any_cast<int>(value) != 0;
        } else if (value.type() == typeid(double)) {
          return std::any_cast<double>(value) != 0;
        } else if (value.type() == typeid(bool)) {
          return std::any_cast<bool>(value);
        } else {
          this->root->logs.push_back(
              callExpression->getArguments()[0]->getLineNumberAndColumn() +
              "Error: Unexpected function call argument: required bool");
          return nullptr;
        }
      } else {
        this->root->logs.push_back(
            callExpression->getArguments()[0]->getLineNumberAndColumn() +
            "Error: Unexpected function cal: arguments does  not match");
        return nullptr;
      }
    }

    BoundFunctionDeclaration *functionDefination =
        this->_getFunction(function.name);
    if (functionDefination != nullptr) {

      if (functionDefination->functionSymbol.parameters.size() !=
          arguments_size) {
        this->root->logs.push_back(
            callExpression->getCallerIdentifier()->getLineNumberAndColumn() +
            "Error: Function arguments does not match");
        return nullptr;
      }

      this->variable_stack.push(std::map<std::string, Utils::Variable>());

      this->return_count_stack.push(0);

      std::map<std::string, Utils::Variable> &function_Variables =
          this->variable_stack.top();

      for (int i = 0; i < arguments_size; i++) {
        std::any value = (this->evaluate<std::any>(
            (BoundExpression *)callExpression->getArguments()[i]));
        function_Variables[functionDefination->functionSymbol.parameters[i]
                               .name] =
            Utils::Variable(
                value,
                functionDefination->functionSymbol.parameters[i].isConst);
        if (this->hasError())
          break;
      }

      this->evaluateStatement(functionDefination->body);

      this->return_count_stack.pop();

      this->variable_stack.pop();

      return this->last_value;
    } else {
      this->root->logs.push_back(
          callExpression->getCallerIdentifier()->getLineNumberAndColumn() +
          "Error: Function not found");
      return nullptr;
    }
  }

  default: {
    this->root->logs.push_back(node->getLineNumberAndColumn() +
                               "Error: Unexpected node");
    return nullptr;
  }
  }
}
template <typename T>
T Evaluator::unaryExpressionEvaluator(
    BinderKindUtils::BoundUnaryOperatorKind op, T operand) {

  if (operand.type() == typeid(int)) {
    return Evaluator::unaryExpressionEvaluatorHandler<int, std::any>(
        op, std::any_cast<int>(operand));
  } else if (operand.type() == typeid(double)) {
    return Evaluator::unaryExpressionEvaluatorHandler<double, std::any>(
        op, std::any_cast<double>(operand));
  } else if (operand.type() == typeid(bool)) {
    return Evaluator::unaryExpressionEvaluatorHandler<bool, std::any>(
        op, std::any_cast<bool>(operand));
  } else {
    throw std::runtime_error("Error: Unexpected operand type");
    return operand;
  }
}

// switch (unaryExpression->getOperator()) {
// case BinderKindUtils::BoundUnaryOperatorKind::Identity:
//   return operand;
// case BinderKindUtils::BoundUnaryOperatorKind::Negation:
//   return -operand;
// case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
//   return !operand;
// default:
//   this->root->logs.push_back "Error: Unexpected unary operator";
// }

template <typename V, typename U> // Int
U Evaluator::unaryExpressionEvaluatorHandler(
    BinderKindUtils::BoundUnaryOperatorKind op, V operand) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
    return operand;
  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
    return -operand;
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return !operand;
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
    return ~int(operand);
  default:
    throw std::runtime_error("Error: Unexpected unary operator");
    return operand;
  }
}

template <typename T>
T Evaluator::binaryExpressionEvaluator(
    BinderKindUtils::BoundBinaryOperatorKind op, T left, T right) {
  if (left.type() == typeid(int) && right.type() == typeid(int)) {
    return binaryExpressionEvaluatorIntIntHandler<int, int, int>(
        op, std::any_cast<int>(left), std::any_cast<int>(right));
  } else if (left.type() == typeid(double) && right.type() == typeid(double)) {

    return binaryExpressionEvaluatorDoubleDoubleHandler<double, double, double>(
        op, std::any_cast<double>(left), std::any_cast<double>(right));
  } else if (left.type() == typeid(double) && right.type() == typeid(int)) {

    return binaryExpressionEvaluatorDoubleIntHandler<double, int, double>(
        op, std::any_cast<double>(left), std::any_cast<int>(right));
  } else if (left.type() == typeid(int) && right.type() == typeid(double)) {

    return binaryExpressionEvaluatorIntDoubleHandler<int, double, double>(
        op, std::any_cast<int>(left), std::any_cast<double>(right));
  } else if (left.type() == typeid(bool) && right.type() == typeid(bool)) {

    return binaryExpressionEvaluatorBoolBoolHandler<bool, bool, std::any>(
        op, std::any_cast<bool>(left), std::any_cast<bool>(right));

  }
  // stringstring
  else if (left.type() == typeid(std::string) &&
           right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorStringStringHandler<std::string,
                                                        std::string, std::any>(
        op, std::any_cast<std::string>(left),
        std::any_cast<std::string>(right));
  }
  // stringint
  else if (left.type() == typeid(std::string) && right.type() == typeid(int)) {
    return binaryExpressionEvaluatorStringIntHandler<std::string, int,
                                                     std::any>(
        op, std::any_cast<std::string>(left), std::any_cast<int>(right));
  }
  // intstring
  else if (left.type() == typeid(int) && right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorIntStringHandler<int, std::string,
                                                     std::any>(
        op, std::any_cast<int>(left), std::any_cast<std::string>(right));
  }
  // stringdouble
  else if (left.type() == typeid(std::string) &&
           right.type() == typeid(double)) {
    return binaryExpressionEvaluatorStringDoubleHandler<std::string, double,
                                                        std::any>(
        op, std::any_cast<std::string>(left), std::any_cast<double>(right));
  }
  // doublestring
  else if (left.type() == typeid(double) &&
           right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorDoubleStringHandler<double, std::string,
                                                        std::any>(
        op, std::any_cast<double>(left), std::any_cast<std::string>(right));
  }
  // stringbool
  else if (left.type() == typeid(std::string) && right.type() == typeid(bool)) {
    return binaryExpressionEvaluatorStringBoolHandler<std::string, bool,
                                                      std::any>(
        op, std::any_cast<std::string>(left), std::any_cast<bool>(right));
  }
  // boolstring
  else if (left.type() == typeid(bool) && right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorBoolStringHandler<bool, std::string,
                                                      std::any>(
        op, std::any_cast<bool>(left), std::any_cast<std::string>(right));
  }
  // intbool
  else if (left.type() == typeid(int) && right.type() == typeid(bool)) {
    return binaryExpressionEvaluatorIntBoolHandler<int, bool, int>(
        op, std::any_cast<int>(left), std::any_cast<bool>(right));
  }
  // boolint
  else if (left.type() == typeid(bool) && right.type() == typeid(int)) {
    return binaryExpressionEvaluatorBoolIntHandler<bool, int, int>(
        op, std::any_cast<bool>(left), std::any_cast<int>(right));
  }

  // doublebool
  else if (left.type() == typeid(double) && right.type() == typeid(bool)) {
    return binaryExpressionEvaluatorDoubleBoolHandler<double, bool, double>(
        op, std::any_cast<double>(left), std::any_cast<bool>(right));
  }
  // booldouble
  else if (left.type() == typeid(bool) && right.type() == typeid(double)) {
    return binaryExpressionEvaluatorBoolDoubleHandler<bool, double, double>(
        op, std::any_cast<bool>(left), std::any_cast<double>(right));
  } else {
    throw std::runtime_error("Error: Incompatible operand types");
    return left;
  }
}

template <typename V, typename U, typename Z> // BoolDouble
Z Evaluator::binaryExpressionEvaluatorBoolDoubleHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Bool Division by zero");
      return left;
    }
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    if (!right) {
      throw std::runtime_error("Error: Bool Modulus by zero");
      return left;
    }
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error("Error: Incompatible operand types");
    return left;
  }
}

template <typename V, typename U, typename Z> // IntInt
Z Evaluator::binaryExpressionEvaluatorIntIntHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Integer Division by zero");
      return left;
    }
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return left && right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return left || right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return left & right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return left | right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return left ^ right;
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    if (!right) {
      throw std::runtime_error("Error: Integer Modulus by zero");
      return left;
    }
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // DoubleDouble
Z Evaluator::binaryExpressionEvaluatorDoubleDoubleHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Double Division by zero");
      return left;
    }
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return left && right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return left || right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    if (!right) {
      throw std::runtime_error("Error: Double Modulus by zero");
      return left;
    }
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // BoolBool
Z Evaluator::binaryExpressionEvaluatorBoolBoolHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Bool Division by zero");
      return left;
    }
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return left && right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return left || right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    throw std::runtime_error("Error: Less not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    throw std::runtime_error("Error: Less or equals not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    throw std::runtime_error("Error: Greater not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    throw std::runtime_error("Error: Greater or equals not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return left & right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return left | right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return left ^ right;
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    if (!right) {
      throw std::runtime_error("Error: Bool Modulus by zero");
      return left;
    }
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // StringString
Z Evaluator::binaryExpressionEvaluatorStringStringHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Modulus not supported for string");
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // IntString
Z Evaluator::binaryExpressionEvaluatorIntStringHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return std::to_string(left) + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == std::stoi(right);
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != std::stoi(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < std::stoi(right);
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= std::stoi(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > std::stoi(right);
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= std::stoi(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Assignment:
    throw std::runtime_error("Error: Assignment not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Modulus not supported for string");
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // StringInt
Z Evaluator::binaryExpressionEvaluatorStringIntHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return std::stoi(left) == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return std::stoi(left) != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return std::stoi(left) < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return std::stoi(left) <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return std::stoi(left) > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return std::stoi(left) >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Modulus not supported for string");
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // DoubleInt
Z Evaluator::binaryExpressionEvaluatorDoubleIntHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Double Division by zero");
      return left;
    }
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    if (!right) {
      throw std::runtime_error("Error: Double Modulus by zero");
      return left;
    }
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z> // IntDouble
Z Evaluator::binaryExpressionEvaluatorIntDoubleHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Double Division by zero");
      return left;
    };
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Modulus not supported for double");
  default:
    throw std::runtime_error("Error: Unexpected binary operator");
    return left;
  }
}

template <typename V, typename U, typename Z>
Z // StringBool
Evaluator::binaryExpressionEvaluatorStringDoubleHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return std::stod(left) == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return std::stod(left) != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return std::stod(left) < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return std::stod(left) <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return std::stod(left) > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return std::stod(left) >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Modulus not supported for string");
  default:
    throw std::runtime_error(
        "Error: Unexpected binary operator"); // TODO: add error message
    return left;
  }
}

template <typename V, typename U, typename Z> // DoubleString
Z Evaluator::binaryExpressionEvaluatorDoubleStringHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return std::to_string(left) + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == std::stod(right);
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != std::stod(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < std::stod(right);
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= std::stod(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > std::stod(right);
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= std::stod(right);
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Modulus not supported for string");
  default:
    throw std::runtime_error(
        "Error:  Unexpected binary operator"); // TODO: add error message
    return left;
  }
}

template <typename V, typename U, typename Z> // StringBool
Z Evaluator::binaryExpressionEvaluatorStringBoolHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw std::runtime_error("Error: Addition not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    throw std::runtime_error("Error: Less not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    throw std::runtime_error("Error: Less or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    throw std::runtime_error("Error: Greater not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    throw std::runtime_error(
        "Error: Greater or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Mod not supported for string");
  default:
    throw std::runtime_error(
        "Error: Unexpected binary operator"); // TODO: add error message
    return left;
  }
}

template <typename V, typename U, typename Z> // BoolString
Z Evaluator::binaryExpressionEvaluatorBoolStringHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw std::runtime_error("Error: Addition not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw std::runtime_error("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw std::runtime_error("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return std::to_string(left) == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return std::to_string(left) != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    throw std::runtime_error("Error: Less not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    throw std::runtime_error("Error: Less or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    throw std::runtime_error("Error: Greater not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    throw std::runtime_error(
        "Error: Greater or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Assignment:
    throw std::runtime_error("Error: Assignment not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Mod not supported for string");
  default:
    throw std::runtime_error(
        "Error: Unexpected binary operator"); // TODO: add error message
    return left;
  }
}

template <typename V, typename U, typename Z> // IntBool
Z Evaluator::binaryExpressionEvaluatorIntBoolHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    if (!right) {
      throw std::runtime_error("Error: Integer Division by zero");
      return left;
    }
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return left && right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return left || right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return left & right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return left | right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return left ^ right;
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    if (!right) {
      throw std::runtime_error("Error: Integer Modulus by zero");
      return left;
    }
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error(
        "Error: Unexpected binary operator"); // TODO: add error message
    return left;
  }
}

template <typename V, typename U, typename Z> // BoolInt
Z Evaluator::binaryExpressionEvaluatorBoolIntHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw std::runtime_error("Error: Addition not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return left && right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return left || right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return left & right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return left | right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return left ^ right;
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    return static_cast<int>(left) % static_cast<int>(right);
  default:
    throw std::runtime_error(
        "Error: Unexpected binary operator"); // TODO: add error message
    return left;
  }
}

template <typename V, typename U, typename Z> // DoubleBool
Z Evaluator::binaryExpressionEvaluatorDoubleBoolHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw std::runtime_error("Error: Addition not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw std::runtime_error("Error: Subtraction not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw std::runtime_error("Error: Multiplication not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw std::runtime_error("Error: Division not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return left && right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return left || right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return left < right;
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return left <= right;
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return left > right;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return left >= right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw std::runtime_error("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw std::runtime_error("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw std::runtime_error("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw std::runtime_error("Error: Mod not supported for double");
  default:
    throw std::runtime_error(
        "Error: Unexpected binary operator"); // TODO: add error message
    return left;
  }
}