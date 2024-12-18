#include "CallExpressionBinder.h"
#include <memory>

#include "../ExpressionBinderFactory.h"

std::unique_ptr<BoundExpression>
CallExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                     ExpressionSyntax *expression) {
  CallExpressionSyntax *callExpression =
      static_cast<CallExpressionSyntax *>(expression);

  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifier(
      (BoundLiteralExpression<std::any> *)ExpressionBinderFactory::create(
          callExpression->getIdentifierPtr()->getKind())
          ->bindExpression(ctx, callExpression->getIdentifierPtr().get())
          .release());

  const std::string CALLER_NAME =
      std::any_cast<std::string>(boundIdentifier->getValue());

  const bool IS_CALLING_SUPPER_OUT_SIDEOF_INIT_FUNCTION =
      CALLER_NAME == "super" && !ctx->getRootRef()->isInsideInitFunction();

  if (IS_CALLING_SUPPER_OUT_SIDEOF_INIT_FUNCTION) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        "Can not call 'super' function directly inside any member function "
        "other than init function",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(
            callExpression->getIdentifierPtr()->getTokenPtr().get())));

    return std::move(boundIdentifier);
  }

  const bool IS_CALLING_INIT_FUNCTION_OUTSIDE_OR_INSIDE_CLASS =
      CALLER_NAME == "init";

  if (IS_CALLING_INIT_FUNCTION_OUTSIDE_OR_INSIDE_CLASS) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        "Can not call 'init' function directly inside or outside of class",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(
            callExpression->getIdentifierPtr()->getTokenPtr().get())));

    return std::move(boundIdentifier);
  }

  const bool IS_A_BUILTIN_FUNCTION_CALL =
      BuiltInFunction::isBuiltInFunction(CALLER_NAME);

  if (IS_A_BUILTIN_FUNCTION_CALL) {
    const std::unique_ptr<BoundFunctionDeclaration> &boundBuiltinFunction =
        BuiltInFunction::getBuiltInFunction(CALLER_NAME);

    const bool IS_AGUMENT_MISMATCHED_OF_NON_VARIADIC_BUILTIN_FUNCTION_CALL =
        !boundBuiltinFunction->isVariadicFunction() &&
        callExpression->getArguments().size() !=
            boundBuiltinFunction->getParametersRef().size();

    if (IS_AGUMENT_MISMATCHED_OF_NON_VARIADIC_BUILTIN_FUNCTION_CALL) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          "Function " + boundBuiltinFunction->getFunctionNameRef() +
              " requires " +
              std::to_string(boundBuiltinFunction->getParametersRef().size()) +
              " arguments but " +
              std::to_string(callExpression->getArguments().size()) +
              " arguments were given",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          Utils::getSourceLocation(
              callExpression->getIdentifierPtr()->getTokenPtr().get())));
    }
  }

  BoundFunctionDeclaration *declared_fd = nullptr;
  std::string updatedCallerName = CALLER_NAME;
  bool isSuperFunctionCall = false;
  if (!IS_A_BUILTIN_FUNCTION_CALL) {
    const std::string CLASS_NAME = ctx->getRootRef()->getClassName();
    const bool IS_INSIDE_CURRENT_CLASS = CLASS_NAME != "";
    if (IS_INSIDE_CURRENT_CLASS) {
      BoundClassStatement *boundClassStatement =
          ctx->getRootRef()->tryGetClass(CLASS_NAME);

      const bool IS_SUPPER_INIT_CALL = CALLER_NAME == "super";
      if (IS_SUPPER_INIT_CALL && !declared_fd) {
        const bool IS_CURRENT_CLASS_HAS_NO_PARENT_CLASS =
            boundClassStatement->getParentClassName() == "";

        if (IS_CURRENT_CLASS_HAS_NO_PARENT_CLASS) {
          ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
              "Could not find super class of class " + CLASS_NAME +
                  ", "
                  "Add super class to class declaration",
              DiagnosticUtils::DiagnosticLevel::Error,
              DiagnosticUtils::DiagnosticType::Semantic,
              Utils::getSourceLocation(
                  callExpression->getIdentifierPtr()->getTokenPtr().get())));

          return std::move(boundIdentifier);
        }

        updatedCallerName =
            boundClassStatement->getParentClassName() +
            FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
            std::to_string(callExpression->getArguments().size());
        declared_fd = boundClassStatement->getParentClass()->getMemberFunction(
            updatedCallerName);
        isSuperFunctionCall = true;
      }
      if (boundClassStatement) {
        const std::string CLASS_MEMBER_FUNCTION_NAME =
            boundClassStatement->getActualFunctionNameIfExists(CALLER_NAME);

        const auto CURRENT_CLASS_MEMEBER_FUNCTION_CALL =
            boundClassStatement->getMemberFunction(CLASS_MEMBER_FUNCTION_NAME);

        if (CURRENT_CLASS_MEMEBER_FUNCTION_CALL && !declared_fd) {
          updatedCallerName = CLASS_MEMBER_FUNCTION_NAME;
          declared_fd = CURRENT_CLASS_MEMEBER_FUNCTION_CALL;
        }
      }
    }
  }

  //! Is Init function
  auto callStatement = ctx->getRootRef()->tryGetClass(CALLER_NAME);

  if (callStatement && !declared_fd) {
    updatedCallerName = CALLER_NAME +
                        FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
                        std::to_string(callExpression->getArguments().size());
    declared_fd = callStatement->getMemberFunction(updatedCallerName);

    if (!declared_fd) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          "Class " + CALLER_NAME +
              " does not have an initializer, Add Default or "
              "Parameterized Initializer in Class Body ",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          Utils::getSourceLocation(
              callExpression->getIdentifierPtr()->getTokenPtr().get())));
      return std::move(boundIdentifier);
    }
  }

  //? calling a class member functon outside of a class e.g "a.callMe()"
  {
    const std::string CLASS_NAME = CALLER_NAME.substr(0, CALLER_NAME.find("."));
    std::string fLastName = CALLER_NAME.substr(CALLER_NAME.find(".") + 1);
    PARSER_DEBUG_LOG("Class Name: " + CLASS_NAME);
    PARSER_DEBUG_LOG("Caller Name: " + CALLER_NAME);
    BoundClassStatement *boundClassStatement =
        ctx->getRootRef()->tryGetClass(CLASS_NAME);

    if (boundClassStatement) {
      fLastName = boundClassStatement->getActualFunctionNameIfExists(fLastName);
    }

    if (fLastName != "" && boundClassStatement) {
      updatedCallerName = fLastName;
      std::unique_ptr<BoundCallExpression> boundCallExpression =
          std::make_unique<BoundCallExpression>(
              callExpression->getSourceLocation());

      boundIdentifier->setValue(updatedCallerName);
      boundCallExpression->setHasNewKeyword(callExpression->hasNewKeyword());
      boundCallExpression->setCallerIdentifier(std::move(boundIdentifier));

      boundCallExpression->setSuperFunctionCall(isSuperFunctionCall);
      for (int i = 0; i < callExpression->getArguments().size(); i++) {
        boundCallExpression->addArgument(
            std::move(ExpressionBinderFactory::create(
                          callExpression->getArguments()[i]->getKind())
                          ->bindExpression(
                              ctx, callExpression->getArguments()[i].get())));
      }

      return std::move(boundCallExpression);
    }
  }

  //? Calling a Moudle Function e.g Test::callMe()

  if (!declared_fd) {
    const std::string MODULE_NAME = CALLER_NAME.substr(
        0, CALLER_NAME.find(FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX));
    std::string mLastName = CALLER_NAME.substr(
        CALLER_NAME.find(FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX) + 1);

    BoundModuleStatement *boundModuleStatement =
        ctx->getRootRef()->tryGetModule(MODULE_NAME);
    if (boundModuleStatement) {
      updatedCallerName = CALLER_NAME;
      declared_fd = ctx->getRootRef()->tryGetFunction(updatedCallerName);
    }
  }

  // if in class -> b, cf, nf
  // not in class -> b, nf

  if (!declared_fd && !IS_A_BUILTIN_FUNCTION_CALL) {
    updatedCallerName = CALLER_NAME;
    declared_fd = ctx->getRootRef()->tryGetFunction(updatedCallerName);
  }

  if (!ctx->getRootRef()->tryGetVariable((CALLER_NAME))) {
    if (!declared_fd && !IS_A_BUILTIN_FUNCTION_CALL) {
      std::string type = "Function";

      if (!ctx->getRootRef()->tryGetClass(CALLER_NAME)) {
        ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
            type + " " + CALLER_NAME + " does not exist",
            DiagnosticUtils::DiagnosticLevel::Error,
            DiagnosticUtils::DiagnosticType::Semantic,
            callExpression->getIdentifierPtr()->getSourceLocation()));
      }
    }

    if (declared_fd &&
        callExpression->getArguments().size() <
            declared_fd->getMinNumberOfParametersNeeded() &&
        !IS_A_BUILTIN_FUNCTION_CALL) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          "Function " + CALLER_NAME + " requires minimum " +
              std::to_string(declared_fd->getMinNumberOfParametersNeeded()) +
              " arguments",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          callExpression->getOpenParenthesisTokenPtr()->getSourceLocation()));
      return std::move(boundIdentifier);
    }
  }

  std::unique_ptr<BoundCallExpression> boundCallExpression =
      std::make_unique<BoundCallExpression>(
          callExpression->getSourceLocation());

  boundIdentifier->setValue(updatedCallerName);
  boundCallExpression->setHasNewKeyword(callExpression->hasNewKeyword());
  boundCallExpression->setCallerIdentifier(std::move(boundIdentifier));
  boundCallExpression->setSuperFunctionCall(isSuperFunctionCall);
  for (int i = 0; i < callExpression->getArguments().size(); i++) {
    boundCallExpression->addArgument(std::move(
        ExpressionBinderFactory::create(
            callExpression->getArguments()[i]->getKind())
            ->bindExpression(ctx, callExpression->getArguments()[i].get())));
  }

  return std::move(boundCallExpression);
}