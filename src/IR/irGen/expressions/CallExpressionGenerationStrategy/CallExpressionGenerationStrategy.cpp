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

      if (!value) {
        return nullptr;
      }

      // check if value is element pointer
      if (llvm::isa<llvm::GetElementPtrInst>(value)) {
        auto v = static_cast<llvm::GetElementPtrInst *>(value);
        value = Builder->CreateLoad(v->getResultElementType(), v);
      }

      // check if value is alloca inst
      if (llvm::isa<llvm::AllocaInst>(value)) {

        auto v = static_cast<llvm::AllocaInst *>(value);

        // local array
        if (llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {

          llvm::ArrayType *arrayType =
              llvm::cast<llvm::ArrayType>(v->getAllocatedType());
          llvm::Type *elementType = arrayType->getElementType();

          if (!elementType->isIntegerTy(8)) {
            return printArray(arrayType, elementType, v);
          }
        }

        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                            {_stringTypeConverter->convertExplicit(value),
                             Builder->getInt1(false)});

        return nullptr;
      }

      // check if is Global Variable
      if (llvm::isa<llvm::GlobalVariable>(value)) {
        auto v = static_cast<llvm::GlobalVariable *>(value);

        // global array
        if (llvm::isa<llvm::ArrayType>(v->getValueType())) {

          llvm::ArrayType *arrayType =
              llvm::cast<llvm::ArrayType>(v->getValueType());
          llvm::Type *elementType = arrayType->getElementType();

          if (!elementType->isIntegerTy(8)) {
            return printArray(arrayType, elementType, v);
          }
        }
      }

      if (_codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
              value->getType()) != Utils::type::NOTHING) {
        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                            {_stringTypeConverter->convertExplicit(value),
                             Builder->getInt1(false)});
        return nullptr;
      }
      // _codeGenerationContext->getLogger()->LogError("Something went wrong in
      // "
      //                                               "print function call ");

      return nullptr;
    }
  } else if (function.name == Utils::BuiltInFunctions::input.name) {
    if (arguments_size == 0) {

      llvm::ArrayRef<llvm::Value *> Args = {};

      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
    } else if (arguments_size == 1) {

      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArguments()[0].get()->getKind())
              ->generateExpression(callExpression->getArguments()[0].get());

      Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                          {_stringTypeConverter->convertExplicit(val),
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

  BoundFunctionDeclaration *definedFunction =
      _codeGenerationContext->getBoundedUserFunctions()[function.name];

  if (!calleeFunction &&
      !_codeGenerationContext->getRecursiveFunctionsMap()[function.name]) {

    _codeGenerationContext->getRecursiveFunctionsMap()[function.name] = 1;

    std::unique_ptr<FunctionStatementGenerationStrategy> fgst =
        std::make_unique<FunctionStatementGenerationStrategy>(
            _codeGenerationContext);

    fgst->generateStatementOnFly(definedFunction, args);

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

llvm::Value *CallExpressionGenerationStrategy::printArray(
    llvm::ArrayType *arrayType, llvm::Type *elementType, llvm::Value *v) {

  llvm::Value *size = llvm::ConstantInt::get(
      llvm::Type::getInt32Ty(*TheContext), arrayType->getNumElements());

  llvm::Value *arrayPtr = v;

  std::string arrayName = v->getName().str();

  llvm::Value *commaPtr = _stringTypeConverter->convertExplicit(
      Builder->CreateGlobalStringPtr(", "));

  Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                      {_stringTypeConverter->convertExplicit(
                           Builder->CreateGlobalStringPtr("[")),
                       Builder->getInt1(false)});

  llvm::Function *TheFunction = Builder->GetInsertBlock()->getParent();

  // Create blocks
  llvm::BasicBlock *loopStart =
      llvm::BasicBlock::Create(*TheContext, "loopStart", TheFunction);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "loopBody", TheFunction);
  llvm::BasicBlock *loopEnd =
      llvm::BasicBlock::Create(*TheContext, "loopEnd", TheFunction);

  // Initialize counter
  llvm::AllocaInst *i = Builder->CreateAlloca(Builder->getInt32Ty());
  Builder->CreateStore(Builder->getInt32(0), i);

  // Jump to the loop start block
  Builder->CreateBr(loopStart);
  // Iterate over each element of the array

  // Loop start block
  Builder->SetInsertPoint(loopStart);
  llvm::Value *iVal =
      Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), i);
  llvm::Value *cond = Builder->CreateICmpSLT(iVal, size);
  Builder->CreateCondBr(cond, loopBody, loopEnd);

  // Loop body block
  Builder->SetInsertPoint(loopBody);
  llvm::Value *elementPtr =
      Builder->CreateGEP(arrayType, v, {Builder->getInt32(0), iVal});

  llvm::Value *innerValue = nullptr;

  // Untyped Container Element
  if (_codeGenerationContext->getDynamicType()->isDyn(elementType)) {
    llvm::ConstantInt *index = llvm::cast<llvm::ConstantInt>(iVal);

    innerValue =
        _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
            elementPtr, FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX +
                            arrayName + "_" +
                            std::to_string(index->getSExtValue()));
  } else {
    // Typed Container Element
    innerValue = Builder->CreateLoad(elementType, elementPtr);
  }
  Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                      {_stringTypeConverter->convertExplicit(innerValue),
                       Builder->getInt1(false)});

  llvm::Value *iNext = Builder->CreateAdd(iVal, Builder->getInt32(1));
  Builder->CreateStore(iNext, i);
  llvm::Value *isNotLast = Builder->CreateICmpSLT(iNext, size);
  llvm::BasicBlock *ifBlock =
      llvm::BasicBlock::Create(*TheContext, "ifBlock", TheFunction);

  Builder->CreateCondBr(isNotLast, ifBlock, loopStart);

  Builder->SetInsertPoint(ifBlock);
  Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                      {commaPtr, Builder->getInt1(false)});

  Builder->CreateBr(loopStart);

  // Loop end block
  Builder->SetInsertPoint(loopEnd);
  Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                      {_stringTypeConverter->convertExplicit(
                           Builder->CreateGlobalStringPtr("]")),
                       Builder->getInt1(false)});

  return nullptr;
}
