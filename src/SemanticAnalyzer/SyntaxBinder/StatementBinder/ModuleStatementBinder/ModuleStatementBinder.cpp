
#include "ModuleStatementBinder.h"
#include <memory>

std::unique_ptr<BoundStatement>
ModuleStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                     StatementSyntax *statement) {

  ModuleStatementSyntax *moduleStatement =
      static_cast<ModuleStatementSyntax *>(statement);

  std::unique_ptr<BoundModuleStatement> boundModuleStat =
      std::make_unique<BoundModuleStatement>(
          moduleStatement->getSourceLocation());

  std::unique_ptr<BoundLiteralExpression<std::any>> moduleNameIdef(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              moduleStatement->getModuleNameRef()->getKind())
              ->bindExpression(ctx, moduleStatement->getModuleNameRef().get())
              .release()));

  boundModuleStat->addModuleNameIdentifier(std::move(moduleNameIdef));

  ctx->setCurrentModuleName(boundModuleStat->getModuleName());

  ctx->getRootRef()->tryDeclareModuleGlobal(boundModuleStat.get());

  for (auto &stat : moduleStatement->getStatementsRef()) {

    ctx->setCurrentModuleName(boundModuleStat->getModuleName());

    switch (stat->getKind()) {
    case SyntaxKindUtils::SyntaxKind::CustomTypeStatement: {
      CustomTypeStatementSyntax *customTypeStatement =
          static_cast<CustomTypeStatementSyntax *>(stat.get());

      boundModuleStat->addCustomTypeStatement(std::move(
          StatementBinderFactory::create(customTypeStatement->getKind())
              ->bindStatement(ctx, customTypeStatement)));

      break;
    }
    case SyntaxKindUtils::SyntaxKind::ClassStatement: {
      ClassStatementSyntax *classStatement =
          static_cast<ClassStatementSyntax *>(stat.get());

      boundModuleStat->addClassStatement(
          std::move(StatementBinderFactory::create(classStatement->getKind())
                        ->bindStatement(ctx, classStatement)));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::VariableDeclaration: {
      VariableDeclarationSyntax *var =
          static_cast<VariableDeclarationSyntax *>(stat.get());

      std::unique_ptr<VariableDeclarationBinder> varBinder =
          std::make_unique<VariableDeclarationBinder>();

      varBinder->setClassName(boundModuleStat->getModuleName());

      std::unique_ptr<BoundVariableDeclaration> boundMemberVariable(
          static_cast<BoundVariableDeclaration *>(
              varBinder->bindStatement(ctx, var).release()));

      ctx->getRootRef()->tryDeclareVariableGlobal(
          boundMemberVariable->getVariableName(), boundMemberVariable.get());

      boundModuleStat->addVariableStatement(std::move(boundMemberVariable));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax: {
      FunctionDeclarationSyntax *fun =
          static_cast<FunctionDeclarationSyntax *>(stat.get());

      std::unique_ptr<FunctionDeclarationBinder> funBinder =
          std::make_unique<FunctionDeclarationBinder>();

      if (fun->isOnlyDeclared()) {
        funBinder->setPrefix("");
        boundModuleStat->addFunctionStatement(funBinder->bindMember(ctx, fun));

        break;
      }

      funBinder->setPrefix(boundModuleStat->getModuleName() +
                           FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX);
      fun->setIsOnlyDeclared(true);

      boundModuleStat->addFunctionStatement(funBinder->bindMember(ctx, fun));

      // Define Functions
      fun->setIsOnlyDeclared(false);
      break;
    }
    case SyntaxKindUtils::SyntaxKind::CallExpression: {
      CallExpressionSyntax *call =
          static_cast<CallExpressionSyntax *>(stat.get());

      boundModuleStat->addCallerExpression(
          std::move(ExpressionBinderFactory::create(stat->getKind())
                        ->bindExpression(ctx, call)));
      break;
    }
    default: {
      ctx->getDiagnosticHandler()->addDiagnostic(
          Diagnostic("Unsupported Expression or Statement used in Module [" +
                         ctx->getCurrentModuleName() + "]",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     stat->getSourceLocation()));

      break;
    }
    }
  }

  for (auto &stat : moduleStatement->getStatementsRef()) {
    if (stat->getKind() ==
        SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax) {
      FunctionDeclarationSyntax *fun =
          static_cast<FunctionDeclarationSyntax *>(stat.get());
      if (fun->isOnlyDeclared()) {
        continue;
      }

      ctx->setCurrentModuleName(boundModuleStat->getModuleName());

      std::unique_ptr<FunctionDeclarationBinder> funBinder =
          std::make_unique<FunctionDeclarationBinder>();

      funBinder->setPrefix(boundModuleStat->getModuleName() +
                           FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX);

      boundModuleStat->addFunctionStatement(
          std::move(funBinder->bindMember(ctx, fun)));
    }
  }

  ctx->setCurrentModuleName("");

  return std::move(boundModuleStat);
}