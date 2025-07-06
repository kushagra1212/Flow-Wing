
#include "FunctionDeclarationBinder.h"
#include <memory>

std::unique_ptr<BoundStatement>
FunctionDeclarationBinder::bindMember(SyntaxBinderContext *ctx,
                                      MemberSyntax *statement) {
  FunctionDeclarationSyntax *syntax =
      static_cast<FunctionDeclarationSyntax *>(statement);
  std::unique_ptr<BoundFunctionDeclaration> fd =
      std::make_unique<BoundFunctionDeclaration>(syntax->getSourceLocation(),
                                                 syntax->isExposed());

  handleFunctionDefAndDec(ctx, syntax, fd.get());

  if (syntax->isOnlyDeclared()) {
    const std::string &function_name =
        syntax->getIdentifierTokenPtr()->getText();
    if (syntax->isMemberFunction() &&
        !ctx->getRootRef()->tryDeclareFunctionGlobal(fd.get())) {
      ctx->getDiagnosticHandler()->addDiagnostic(
          Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic, {function_name},
                     syntax->getSourceLocation(),
                     FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                         MemberFunctionOfClassAlreadyDeclared));

    } else if (!syntax->isMemberFunction() &&
               !ctx->getRootRef()->tryDeclareMemberFunction(fd.get())) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic, {function_name},
          Utils::getSourceLocation(syntax->getFunctionKeywordPtr().get()),
          FLOW_WING::DIAGNOSTIC::DiagnosticCode::FunctionAlreadyDeclared));
    }
  }

  return std::move(fd);
}

void FunctionDeclarationBinder::handleFunctionDefAndDec(
    SyntaxBinderContext *ctx, FunctionDeclarationSyntax *syntax,
    BoundFunctionDeclaration *fd) {

  ctx->insertScope();

  std::string function_name =
      _prefix != "" ? _prefix + syntax->getIdentifierTokenPtr()->getText()
                    : syntax->getIdentifierTokenPtr()->getText();

  DEBUG_LOG("Binder:: Declaring function: " + function_name);

  if (BuiltInFunction::isBuiltInFunction(function_name)) {

    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {function_name},
        Utils::getSourceLocation(syntax->getIdentifierTokenPtr().get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::
            FunctionNameConflictsWithBuiltin));
  }

  fd->setIsMemberFunction(syntax->isMemberFunction());

  std::unique_ptr<BoundTypeExpression> fType(static_cast<BoundTypeExpression *>(
      ExpressionBinderFactory::create(syntax->getFunctionTypeRef()->getKind())
          ->bindExpression(ctx, syntax->getFunctionTypeRef().get())
          .release()));

  fd->setFunctionType(std::move(fType));

  if (syntax->getAsKeyword()) {
    fd->setHasAsReturnType(true);
  }

  if (function_name.substr(
          function_name.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) +
          1) == "init") {
    function_name += std::to_string(syntax->getParametersPtr().size());
    ctx->getRootRef()->setInsideInitFunction(true);
  }

  fd->setFunctionName(function_name);

  for (int64_t i = 0; i < syntax->getParametersPtr().size(); i++) {
    const std::string &variable_str =
        syntax->getParametersPtr()[i]->getIdentifierRef()->getText();

    std::unique_ptr<BoundVariableDeclaration> varDeclaration(
        static_cast<BoundVariableDeclaration *>(
            StatementBinderFactory::create(
                syntax->getParametersPtr()[i]->getKind())
                ->bindStatement(ctx, syntax->getParametersPtr()[i].get())
                .release()));

    if (varDeclaration->getInitializerPtr() && !fd->hasOptionalParameters()) {
      fd->setOptionalParameterStartIndex(i);
    } else if (!varDeclaration->getInitializerPtr() &&
               fd->hasOptionalParameters()) {

      ctx->getDiagnosticHandler()->addDiagnostic(
          Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     {variable_str, function_name},
                     syntax->getParametersPtr()[i]->getSourceLocation(),
                     FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                         MissingDefaultValueForOptionalParameter));
    }

    fd->addParameter(std::move(varDeclaration));
  }

  for (const auto &expr : syntax->getReturnTypeExpressionListRef()) {

    std::unique_ptr<BoundTypeExpression> rType(
        static_cast<BoundTypeExpression *>(
            ExpressionBinderFactory::create(expr->getKind())
                ->bindExpression(ctx, expr.get())
                .release()));

    fd->addReturnExpr(std::move(rType));
  }

  if (syntax->isOnlyDeclared()) {
    fd->setOnlyDeclared(true);
  } else {
    ctx->getRootRef()->incrementFunctionCount();
    std::unique_ptr<BoundBlockStatement> boundBody(
        (BoundBlockStatement *)StatementBinderFactory::create(
            syntax->getBodyPtr()->getKind())
            ->bindStatement(ctx, syntax->getBodyPtr().get())
            .release());

    fd->setFunctionBody(std::move(boundBody));

    ctx->getRootRef()->decrementFunctionCount();
  }

  ctx->getRootRef()->setInsideInitFunction(false);
  ctx->removeScope();
}

void FunctionDeclarationBinder::setPrefix(const std::string &prefix) {
  _prefix = prefix;
}
