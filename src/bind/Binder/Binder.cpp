
#include "Binder.h"

BoundExpression *Binder::bindExpression(ExpressionSyntax *syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::LiteralExpression: {

    std::any value = ((LiteralExpressionSyntax<std::any> *)syntax)->getValue();
    return new BoundLiteralExpression<std::any>(value);
  }
  case SyntaxKindUtils::SyntaxKind::UnaryExpression: {
    UnaryExpressionSyntax *unaryExpression = (UnaryExpressionSyntax *)syntax;
    BoundExpression *operand = bindExpression(unaryExpression->getOperand());
    BinderKindUtils::BoundUnaryOperatorKind op;

    switch (unaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::Identity;
      break;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::Negation;
      break;
    case SyntaxKindUtils::SyntaxKind::BangToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;
      break;
    default:
      throw "Unexpected unary operator";
    }
    return new BoundUnaryExpression(op, operand);
  }
  case SyntaxKindUtils::SyntaxKind::BinaryExpression: {
    BinaryExpressionSyntax *binaryExpression = (BinaryExpressionSyntax *)syntax;
    BoundExpression *left = bindExpression(binaryExpression->getLeft());
    BoundExpression *right = bindExpression(binaryExpression->getRight());
    BinderKindUtils::BoundBinaryOperatorKind op;

    // if (left->getType() != typeid(int) || right->getType() != typeid(int)) {
    //   logs.push_back("Binary operator can only be applied to numbers");
    //   return left;
    // }

    switch (binaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Addition;
      break;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Subtraction;
      break;
    case SyntaxKindUtils::SyntaxKind::StarToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Multiplication;
      break;
    case SyntaxKindUtils::SyntaxKind::SlashToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Division;
      break;
    case SyntaxKindUtils::SyntaxKind::PercentToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Modulus;
      break;
    case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Equals;
      break;
    case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::NotEquals;
      break;
    case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd;
      break;
    case SyntaxKindUtils::SyntaxKind::PipePipeToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::LogicalOr;
      break;
    case SyntaxKindUtils::SyntaxKind::LessToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Less;
      break;
    case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals;
      break;
    case SyntaxKindUtils::SyntaxKind::GreaterToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Greater;
      break;
    case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals;
      break;
    case SyntaxKindUtils::SyntaxKind::EqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Assignment;
      break;
    case SyntaxKindUtils::SyntaxKind::AmpersandToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd;
      break;
    case SyntaxKindUtils::SyntaxKind::PipeToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr;
      break;
    case SyntaxKindUtils::SyntaxKind::CaretToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor;
      break;
    default:
      throw "Unexpected binary operator";
    }
    return new BoundBinaryExpression(left, op, right);
  }

    // Assignment Expression

  case SyntaxKindUtils::SyntaxKind::AssignmentExpression: {
    AssignmentExpressionSyntax *assignmentExpression =
        (AssignmentExpressionSyntax *)syntax;
    BoundLiteralExpression<std::any> *identifierExpression =
        (BoundLiteralExpression<std::any> *)bindExpression(
            assignmentExpression->getLeft());
    BoundExpression *right = bindExpression(assignmentExpression->getRight());
    std::string variable_str =
        std::any_cast<std::string>(identifierExpression->getValue());
    BinderKindUtils::BoundBinaryOperatorKind op;
    if (!root->tryDeclareVariable(variable_str)) {
      logs.push_back("Error: Variable " + variable_str + " does not exist");
    }
    switch (assignmentExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::EqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Assignment;
      break;
    default:
      throw "Unexpected assignment operator";
    }
    return new BoundAssignmentExpression(identifierExpression, op, right);
  }

  case SyntaxKindUtils::SyntaxKind::VariableExpression: {
    VariableExpressionSyntax *variableExpressionSyntax =
        (VariableExpressionSyntax *)syntax;

    BoundLiteralExpression<std::any> *identifierExpression =
        (BoundLiteralExpression<std::any> *)bindExpression(
            variableExpressionSyntax->getIdentifier());
    std::string variable_str =
        std::any_cast<std::string>(identifierExpression->getValue());
    if (!root->tryLookupVariable(variable_str)) {
      logs.push_back("Error: Variable " + variable_str + " does not exist");
      return identifierExpression;
    }
    return new BoundVariableExpression(identifierExpression);
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    ParenthesizedExpressionSyntax *parenthesizedExpression =
        (ParenthesizedExpressionSyntax *)syntax;
    return bindExpression(parenthesizedExpression->getExpression());
  }
  default:
    throw "Unexpected syntax";
  }
}
BoundScope *Binder::CreateParentScope(BoundScopeGlobal *parent) {
  std::stack<BoundScopeGlobal *> stack = std::stack<BoundScopeGlobal *>();

  while (parent != nullptr) {
    stack.push(parent);
    parent = parent->previous;
  }

  BoundScope *current = nullptr;

  while (!stack.empty()) {
    parent = stack.top();
    stack.pop();
    BoundScope *scope = new BoundScope(current);
    for (auto &pair : parent->variables) {
      scope->variables[pair.first] = pair.second;
    }
    current = scope;
  }

  return current;
}

Binder::Binder(BoundScope *parent) { this->root = new BoundScope(parent); }

BoundScopeGlobal *Binder::bindGlobalScope(BoundScopeGlobal *previous,
                                          CompilationUnitSyntax *syntax) {

  Binder *binder = new Binder(Binder::CreateParentScope(previous));
  BoundExpression *expression = binder->bindExpression(syntax->getExpression());
  std::vector<std::string> logs = binder->logs;
  std::unordered_map<std::string, std::any> variables = binder->root->variables;
  return new BoundScopeGlobal(previous, variables, logs, expression);
}
