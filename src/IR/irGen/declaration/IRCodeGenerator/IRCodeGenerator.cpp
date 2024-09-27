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
          std::make_unique<ClassStatementGenerationStrategy>(context)),
      _multipleVariableDeclarationStatementGenerationStrategy(
          std::make_unique<
              MultipleVariableDeclarationStatementGenerationStrategy>(context)),
      _multipleAssignmentExpressionGenerationStrategy(
          std::make_unique<MultipleAssignmentExpressionGenerationStrategy>(
              context)) {}

void IRCodeGenerator::processChildForDeclaration(BoundNode *child,
                                                 bool isGlobal) {
  if (!child)
    return;

  switch (child->getKind()) {
  case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {

    break;
  }
  case BinderKindUtils::BoundNodeKind::BringStatement: {
    BoundBringStatement *bringStatement =
        static_cast<BoundBringStatement *>(child);

    if (bringStatement->isModuleImport()) {
      declareVariables(bringStatement, isGlobal);
    }

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
  case BinderKindUtils::BoundNodeKind::
      BoundMultipleVariableDeclarationStatement: {
    BoundMultipleVariableDeclaration *boundMultipleVariableDeclaration =
        static_cast<BoundMultipleVariableDeclaration *>(child);

    declareVariables(child, isGlobal);
    if (isGlobal) {
      _multipleVariableDeclarationStatementGenerationStrategy->declareGlobal(
          boundMultipleVariableDeclaration);
    } else {
      _multipleVariableDeclarationStatementGenerationStrategy->declareLocal(
          boundMultipleVariableDeclaration);
    }

    break;
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {

    _callExpressionGenerationStrategy->declare(
        static_cast<BoundCallExpression *>(child));
    break;
  }
  case BinderKindUtils::BoundNodeKind::BoundModuleStatement: {

    BoundModuleStatement *moduleStatement =
        static_cast<BoundModuleStatement *>(child);

    for (const auto &variable :
         moduleStatement->getVariableDeclarationStatementsRef()) {
      processChildForDeclaration(variable.get(), isGlobal);
    }

    for (const auto &callExpr : moduleStatement->getCallerExpressionsRef()) {
      processChildForDeclaration(callExpr.get(), isGlobal);
    }

    break;
  }
  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {
    _assignmentExpressionGenerationStrategy->declare(
        static_cast<BoundAssignmentExpression *>(child));

    declareVariables(child, isGlobal);
    break;
  }
  case BinderKindUtils::BoundNodeKind::BoundMultipleAssignmentExpression: {

    declareVariables(child, isGlobal);
    _multipleAssignmentExpressionGenerationStrategy->declare(
        static_cast<BoundAssignmentExpression *>(child));

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

void IRCodeGenerator::declareVariables(BoundNode *node, bool isGlobal) {
  for (auto &child : node->getChildren()) {
    processChildForDeclaration(child, isGlobal);
  }
}

void IRCodeGenerator::declareCustomType(BoundNode *node) {
  for (auto &child : node->getChildren()) {
    processChildForCustomType(child);
  }
}