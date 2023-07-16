#include "Evaluator.h"

template class BoundLiteralExpression<std::any>;
template class BoundLiteralExpression<int>;
template class BoundLiteralExpression<double>;
template class BoundLiteralExpression<bool>;
template class BoundLiteralExpression<std::string>;
template class BoundLiteralExpression<char>;

template std::any Evaluator::evaluate<std::any>(BoundExpression *node);
std::unordered_map<std::string, std::any> Evaluator::variables;

template <typename T> T Evaluator::evaluate(BoundExpression *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression: {
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
      throw "Error: Unexpected literal expression";
    }
  }
  case BinderKindUtils::BoundNodeKind::UnaryExpression: {
    BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
    std::any operand_any =
        (Evaluator::evaluate<std::any>(unaryExpression->getOperand()));
    return Evaluator::unaryExpressionEvaluator<std::any>(
        unaryExpression->getOperator(), operand_any);
  }
  case BinderKindUtils::BoundNodeKind::VariableExpression: {
    BoundVariableExpression *variableExpression =
        (BoundVariableExpression *)node;

    std::any variable = Evaluator::evaluate<std::any>(
        variableExpression->getIdentifierExpression());
    if (variable.type() != typeid(std::string)) {
      throw "Error: Unexpected variable name";
    }

    std::string variable_name = std::any_cast<std::string>(variable);
    switch (variableExpression->getKind()) {
    case BinderKindUtils::BoundNodeKind::VariableExpression: {
      if (Evaluator::variables.find(variable_name) !=
          Evaluator::variables.end()) {
        return Evaluator::variables[variable_name];
      } else {
        throw "Error: variable is undefined";
      }
    }
    default:
      throw "Error: Unexpected Variable found";
    }
  }

  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {
    BoundAssignmentExpression *assignmentExpression =
        (BoundAssignmentExpression *)node;

    std::any variable =
        Evaluator::evaluate<std::any>(assignmentExpression->getLeft());
    if (variable.type() != typeid(std::string)) {
      throw "Error Unexpected variable name";
    }
    std::string variable_name = std::any_cast<std::string>(variable);

    switch (assignmentExpression->getOperator()) {
    case BinderKindUtils::BoundBinaryOperatorKind::Assignment: {

      Evaluator::variables[variable_name] =
          Evaluator::evaluate<std::any>(assignmentExpression->getRight());

      break;
    }
    default:
      throw "Error: Unexpected assignment operator";
    }
    return Evaluator::variables[variable_name];
  }
  case BinderKindUtils::BoundNodeKind::BinaryExpression: {
    BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;
    std::any left_any =
        (Evaluator::evaluate<std::any>(binaryExpression->getLeft()));
    std::any right_any =
        (Evaluator::evaluate<std::any>(binaryExpression->getRight()));

    return Evaluator::binaryExpressionEvaluator<std::any>(
        binaryExpression->getOperator(), left_any, right_any);
  }
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {
    BoundParenthesizedExpression *parenthesizedExpression =
        (BoundParenthesizedExpression *)node;
    return Evaluator::evaluate<T>(parenthesizedExpression->getExpression());
  }
  default:
    throw "Error: Unexpected node";
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
    throw "Error: Unexpected operand type";
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
//   throw "Error: Unexpected unary operator";
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
  default:
    throw "Error: Unexpected unary operator";
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

  } else if (left.type() == typeid(std::string) &&
             right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorStringStringHandler<std::string,
                                                        std::string, std::any>(
        op, std::any_cast<std::string>(left),
        std::any_cast<std::string>(right));
  } else if (left.type() == typeid(std::string) &&
             right.type() == typeid(int)) {
    return binaryExpressionEvaluatorStringIntHandler<std::string, int,
                                                     std::any>(
        op, std::any_cast<std::string>(left), std::any_cast<int>(right));
  } else if (left.type() == typeid(int) &&
             right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorIntStringHandler<int, std::string,
                                                     std::any>(
        op, std::any_cast<int>(left), std::any_cast<std::string>(right));
  } else if (left.type() == typeid(std::string) &&
             right.type() == typeid(double)) {
    return binaryExpressionEvaluatorStringDoubleHandler<std::string, double,
                                                        std::any>(
        op, std::any_cast<std::string>(left), std::any_cast<double>(right));
  } else if (left.type() == typeid(double) &&
             right.type() == typeid(std::string)) {
    return binaryExpressionEvaluatorDoubleStringHandler<double, std::string,
                                                        std::any>(
        op, std::any_cast<double>(left), std::any_cast<std::string>(right));
  } else if (left.type() == typeid(std::string) &&
             right.type() == typeid(bool)) {
    return binaryExpressionEvaluatorStringBoolHandler<std::string, bool,
                                                      std::any>(
        op, std::any_cast<std::string>(left), std::any_cast<bool>(right));
  } else if (left.type() == typeid(bool) &&
             right.type() == typeid(std::string)) {
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
    throw("Error: Incompatible operand types");
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
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != right;
  default:
    throw("Error: Incompatible operand types");
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
    return left % right;
  default:
    throw("Error: Unexpected binary operator");
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
    throw("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for double");
  default:
    throw("Error: Unexpected binary operator");
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
    throw("Error: Less not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    throw("Error: Less or equals not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    throw("Error: Greater not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    throw("Error: Greater or equals not supported for bool");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return left & right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return left | right;
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return left ^ right;
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for bool");
  default:
    throw("Error: Unexpected binary operator");
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
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
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
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for string");
  default:
    throw("Error: Unexpected binary operator");
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
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
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
    throw("Error: Assignment not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for string");
  default:
    throw("Error: Unexpected binary operator");
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
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
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
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for string");
  default:
    throw("Error: Unexpected binary operator");
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
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for double");
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
    throw("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for double");
  default:
    throw("Error: Unexpected binary operator");
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
    return left / right;
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for double");
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
    throw("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for double");
  default:
    throw("Error: Unexpected binary operator");
  }
}

template <typename V, typename U, typename Z> // StringDouble
Z Evaluator::binaryExpressionEvaluatorStringDoubleHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return left + std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
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
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for string");
  default:
    throw("Error: Unexpected binary operator"); // TODO: add error message
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
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
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
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Modulus not supported for string");
  default:
    throw("Error:  Unexpected binary operator"); // TODO: add error message
  }
}

template <typename V, typename U, typename Z> // StringBool
Z Evaluator::binaryExpressionEvaluatorStringBoolHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw("Error: Addition not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return left == std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return left != std::to_string(right);
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    throw("Error: Less not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    throw("Error: Less or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    throw("Error: Greater not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    throw("Error: Greater or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Mod not supported for string");
  default:
    throw("Error: Unexpected binary operator"); // TODO: add error message
  }
}

template <typename V, typename U, typename Z> // BoolString
Z Evaluator::binaryExpressionEvaluatorBoolStringHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw("Error: Addition not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw("Error: Subtraction not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    throw("Error: Logical and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    throw("Error: Logical or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return std::to_string(left) == right;
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return std::to_string(left) != right;
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    throw("Error: Less not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    throw("Error: Less or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    throw("Error: Greater not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    throw("Error: Greater or equals not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Assignment:
    throw("Error: Assignment not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    throw("Error: Bitwise and not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for string");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Mod not supported for string");
  default:
    throw("Error: Unexpected binary operator"); // TODO: add error message
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
    return left % right;
  default:
    throw("Error: Unexpected binary operator"); // TODO: add error message
  }
}

template <typename V, typename U, typename Z> // BoolInt
Z Evaluator::binaryExpressionEvaluatorBoolIntHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw("Error: Addition not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw("Error: Subtraction not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for int");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for int");
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
    return left % right;
  default:
    throw("Error: Unexpected binary operator"); // TODO: add error message
  }
}

template <typename V, typename U, typename Z> // DoubleBool
Z Evaluator::binaryExpressionEvaluatorDoubleBoolHandler(
    BinderKindUtils::BoundBinaryOperatorKind op, const V &left,
    const U &right) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    throw("Error: Addition not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    throw("Error: Subtraction not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    throw("Error: Multiplication not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    throw("Error: Division not supported for double");
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
    throw("Error: Bitwise and not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    throw("Error: Bitwise or not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    throw("Error: Bitwise xor not supported for double");
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    throw("Error: Mod not supported for double");
  default:
    throw("Error: Unexpected binary operator"); // TODO: add error message
  }
}