#include "Evaluator.h"

std::unordered_map<std::string, std::any> Evaluator::variables;
template <typename T> T Evaluator::evaluate(BoundExpression *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression: {

    if (auto literalExpression =
            dynamic_cast<BoundLiteralExpression<int> *>(node))
      return (literalExpression->getValue());
    else if (auto literalExpression =
                 dynamic_cast<BoundLiteralExpression<bool> *>(node)) {

      return (literalExpression->getValue());
    } else if (auto literalExpression =
                   dynamic_cast<BoundLiteralExpression<std::string> *>(node)) {

      return (literalExpression->getValue());
    } else {
      throw "Unexpected literal expression";
    }

    return 0;
  }
  case BinderKindUtils::BoundNodeKind::UnaryExpression: {
    BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
    std::any operand_any =
        (Evaluator::evaluate<std::any>(unaryExpression->getOperand()));
    int operand = 1;

    if (operand_any.type() == typeid(std::string)) {

      throw "Unexpected string in unary expression";
      return 0;
    }

    if (operand_any.type() == typeid(bool)) {
      bool operand_bool = std::any_cast<bool>(operand_any);
      operand = operand_bool ? 1 : 0;
    } else {
      operand = std::any_cast<int>(operand_any);
    }

    switch (unaryExpression->getOperator()) {
    case BinderKindUtils::BoundUnaryOperatorKind::Identity:
      return operand;
    case BinderKindUtils::BoundUnaryOperatorKind::Negation:
      return -operand;
    default:
      throw "Unexpected unary operator";
    }
  }
  case BinderKindUtils::BoundNodeKind::VariableExpression: {
    BoundVariableExpression *variableExpression =
        (BoundVariableExpression *)node;

    std::any variable = Evaluator::evaluate<std::any>(
        variableExpression->getIdentifierExpression());
    if (variable.type() != typeid(std::string)) {
      throw "Unexpected variable name";
    }

    std::string variable_name = std::any_cast<std::string>(variable);
    switch (variableExpression->getKind()) {
    case BinderKindUtils::BoundNodeKind::VariableExpression: {
      if (Evaluator::variables.find(variable_name) !=
          Evaluator::variables.end()) {
        return Evaluator::variables[variable_name];
      } else {
        throw "variable is undefined";
      }
    }
    default:
      throw "Unexpected Variable found";
    }
  }

  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {
    BoundAssignmentExpression *assignmentExpression =
        (BoundAssignmentExpression *)node;

    std::any variable =
        Evaluator::evaluate<std::any>(assignmentExpression->getLeft());
    if (variable.type() != typeid(std::string)) {
      throw "Unexpected variable name";
    }
    std::string variable_name = std::any_cast<std::string>(variable);
    Evaluator::variables[variable_name] = 0;
    switch (assignmentExpression->getOperator()) {
    case BinderKindUtils::BoundBinaryOperatorKind::Assignment: {
      Evaluator::variables[variable_name] =
          Evaluator::evaluate<std::any>(assignmentExpression->getRight());
      break;
    }
    default:
      throw "Unexpected assignment operator";
    }
    return Evaluator::variables[variable_name];
  }
  case BinderKindUtils::BoundNodeKind::BinaryExpression: {
    BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;
    std::any left_any =
        (Evaluator::evaluate<std::any>(binaryExpression->getLeft()));
    std::any right_any =
        (Evaluator::evaluate<std::any>(binaryExpression->getRight()));

    int left = 1, right = 1;
    if (left_any.type() == typeid(std::string) ||
        right_any.type() == typeid(std::string)) {

      throw "Unexpected string in binary expression";
      return 0;
    }

    if (left_any.type() == typeid(bool)) {
      bool left_bool = std::any_cast<bool>(left_any);
      left = left_bool ? 1 : 0;
    } else {
      left = std::any_cast<int>(left_any);
    }

    if (right_any.type() == typeid(bool)) {
      bool right_bool = std::any_cast<bool>(right_any);
      right = right_bool ? 1 : 0;
    } else {
      right = std::any_cast<int>(right_any);
    }

    return Evaluator::binaryExpressionEvaluator<T>(
        binaryExpression->getOperator(), left, right);
  }
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {
    BoundParenthesizedExpression *parenthesizedExpression =
        (BoundParenthesizedExpression *)node;
    return Evaluator::evaluate<T>(parenthesizedExpression->getExpression());
  }
  default:
    throw "Unexpected node";
  }
}

template <typename T>
T Evaluator::binaryExpressionEvaluator(
    BinderKindUtils::BoundBinaryOperatorKind op, int left, int right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + right;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return left - right;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return left * right;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
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
  case BinderKindUtils::BoundBinaryOperatorKind::Assignment:
    return right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return left & right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return left | right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return left ^ right;
  default:
    throw "Unexpected binary operator";
  }
}
template std::any Evaluator::evaluate<std::any>(BoundExpression *node);