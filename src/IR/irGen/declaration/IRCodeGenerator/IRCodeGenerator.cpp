#include "IRCodeGenerator.h"

IRCodeGenerator::IRCodeGenerator(CodeGenerationContext *context)
    : _variableDeclarationStatementGenerationStrategy(
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              context)),
      _callExpressionGenerationStrategy(
          std::make_unique<CallExpressionGenerationStrategy>(context)),
      _customTypeStatementGenerationStrategy(
          std::make_unique<CustomTypeStatementGenerationStrategy>(context)),
      _classStatementGenerationStrategy(
          std::make_unique<ClassStatementGenerationStrategy>(context)) {}

void IRCodeGenerator::processChildForDeclaration(BoundNode *child,
                                                 bool isGlobal) {
  if (!child)
    return;

  switch (child->getKind()) {
  case BinderKindUtils::BoundNodeKind::FunctionDeclaration:
  case BinderKindUtils::BoundNodeKind::BringStatement: {

    break;
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

    if (isGlobal) {
      _variableDeclarationStatementGenerationStrategy->declareGlobal(
          static_cast<BoundVariableDeclaration *>(child));
    } else {
      _variableDeclarationStatementGenerationStrategy->declareLocal(
          static_cast<BoundVariableDeclaration *>(child));
    }

    declareVariables(child, isGlobal);
    break;
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {

    _callExpressionGenerationStrategy->declare(
        static_cast<BoundCallExpression *>(child));
    break;
  }
  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {
    _assignmentExpressionGenerationStrategy->declare(
        static_cast<BoundAssignmentExpression *>(child));

    declareVariables(child, isGlobal);
    break;
  }
  default:
    declareVariables(child, false);
    break;
  }
}

void IRCodeGenerator::processChildForCustomType(BoundNode *child) {
  if (!child)
    return;

  switch (child->getKind()) {
  case BinderKindUtils::BoundNodeKind::CustomTypeStatement: {
    _customTypeStatementGenerationStrategy->generateCustomType(
        static_cast<BoundCustomTypeStatement *>(child));
    break;
  }
  case BinderKindUtils::BoundNodeKind::ClassStatement: {

    auto classStmt = static_cast<BoundClassStatement *>(child);
    for (auto &memberFunc : classStmt->getMemberFunctionsRef()) {
      declareCustomType(memberFunc.get());
    }
    _classStatementGenerationStrategy->generateClassType(classStmt);
    break;
  }
  default:
    declareCustomType(child);
  }
}

void IRCodeGenerator::declareVariables(BoundStatement *statement,
                                       bool isGlobal) {
  for (auto &child : statement->getChildren()) {
    processChildForDeclaration(child, isGlobal);
  }
}

void IRCodeGenerator::declareVariables(BoundNode *node, bool isGlobal) {
  for (auto &child : node->getChildren()) {
    processChildForDeclaration(child, isGlobal);
  }
}

void IRCodeGenerator::declareCustomType(BoundStatement *statement) {
  for (auto &child : statement->getChildren()) {
    processChildForCustomType(child);
  }
}

void IRCodeGenerator::declareCustomType(BoundNode *node) {
  for (auto &child : node->getChildren()) {
    processChildForCustomType(child);
  }
}