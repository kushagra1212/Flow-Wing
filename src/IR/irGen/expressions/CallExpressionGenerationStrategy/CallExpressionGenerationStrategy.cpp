#include "CallExpressionGenerationStrategy.h"

#include "../../statements/FunctionStatementGenerationStrategy/FunctionStatementGenerationStrategy.h"

CallExpressionGenerationStrategy::CallExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *CallExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundCallExpression *callExpression =
      static_cast<BoundCallExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getLocation());

  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();
  if (Utils::BuiltInFunctions::getFunctionSymbol(function.name).name ==
      function.name) {
    return this->buildInFunctionCall(callExpression);
  }

  return this->userDefinedFunctionCall(callExpression);
}

llvm::Value *CallExpressionGenerationStrategy::buildInFunctionCall(
    BoundCallExpression *callExpression) {
  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();

  const std::string &functionName = function.name;
  std::size_t arguments_size = callExpression->getArguments().size();

  const std::string errorMessage =
      "Unexpected Function Call Arguments Does Not Match in " + functionName;

  if (functionName == Utils::BuiltInFunctions::print.name) {
    if (arguments_size == 1) {

      llvm::Value *value =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      if (_codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
              value->getType()) != Utils::type::NOTHING) {
        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                            {_stringTypeConverter->convertExplicit(value),
                             Builder->getInt1(false)});
      }
    }
  } else if (function.name == Utils::BuiltInFunctions::input.name) {
    if (arguments_size == 0) {

      llvm::ArrayRef<llvm::Value *> Args = {};

      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
    } else if (arguments_size == 1) {

      llvm::Value *strPtri8 =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                          {_stringTypeConverter->convertExplicit(strPtri8),
                           Builder->getInt1(false)});

      llvm::ArrayRef<llvm::Value *> Args = {};
      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
    }
  } else if (function.name == Utils::BuiltInFunctions::String.name) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      return _stringTypeConverter->convertExplicit(val);
    }
  } else if (function.name == Utils::BuiltInFunctions::Int32.name) {
    if (arguments_size == 1) {

      llvm::Value *res = nullptr;
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      res = _int32TypeConverter->convertExplicit(val);
      return res;
    }
  } else if (function.name == Utils::BuiltInFunctions::Bool.name) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      return _boolTypeConverter->convertExplicit(val);
    }

  } else if (function.name == Utils::BuiltInFunctions::Decimal.name) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      return _doubleTypeConverter->convertExplicit(val);
    }
  }

  _codeGenerationContext->getLogger()->LogError(errorMessage);
  _codeGenerationContext->getLogger()->LogError("Unexpected Function Call ");

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::userDefinedFunctionCall(
    BoundCallExpression *callExpression) {
  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();

  const std::string &functionName = function.name;
  std::size_t arguments_size = callExpression->getArguments().size();

  std::vector<llvm::Value *> args;

  for (int i = 0; i < arguments_size; i++) {

    llvm::Value *arg = nullptr;

    arg = _expressionGenerationFactory
              ->createStrategy(callExpression->getArguments()[i]->getKind())
              ->generateExpression(callExpression->getArguments()[i].get());

    if (!arg) {
      _codeGenerationContext->getLogger()->LogError(
          "Argument not found in function call expression ");
      return nullptr;
    }
    args.push_back(arg);
  }

  llvm::Function *calleeFunction = TheModule->getFunction(functionName);

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  auto definedFunction =
      _codeGenerationContext->getBoundedUserFunctions()[function.name];

  if (!calleeFunction &&
      !_codeGenerationContext->getRecursiveFunctionsMap()[function.name]) {

    _codeGenerationContext->getRecursiveFunctionsMap()[function.name] = 1;

    auto functionStatementGenerationStrategy =
        static_cast<FunctionStatementGenerationStrategy *>(
            _statementGenerationFactory
                ->createStrategy(definedFunction->getKind())
                .get());
    functionStatementGenerationStrategy->generateStatementOnFly(definedFunction,
                                                                args);

    Builder->SetInsertPoint(currentBlock);
  }

  calleeFunction = TheModule->getFunction(functionName);

  _codeGenerationContext->getRecursiveFunctionsMap()[function.name] = 0;

  llvm::FunctionType *functionType = calleeFunction->getFunctionType();
  std::vector<llvm::Type *> paramTypes(functionType->param_begin(),
                                       functionType->param_end());

  // Callefunction param types and args check for type are same or not

  for (int i = 0; i < paramTypes.size(); i++) {
    if (paramTypes[i] != args[i]->getType()) {

      const std::string parameterName =
          definedFunction->getFunctionSymbol().parameters[i].name;
      const std::string argumentType =
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              args[i]->getType());

      const std::string parameterType =
          _codeGenerationContext->getMapper()->getLLVMTypeName(paramTypes[i]);

      const std::string errorMessage = "Argument Type " + argumentType +
                                       " does not match with " + parameterType +
                                       " for parameter " + parameterName;

      _codeGenerationContext->getLogger()->LogError(errorMessage);
      return nullptr;
    }
  }
  return Builder->CreateCall(calleeFunction, args);
}

llvm::Value *CallExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->generateExpression(expression);
}