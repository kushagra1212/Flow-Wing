#include "CallExpressionGenerationStrategy.h"

#include "../../declaration/IRCodeGenerator/IRCodeGenerator.h"
#include "../../expressions/VariableExpressionGenerationStrategy/VariableExpressionGenerationStrategy.h"
#include <memory>

CallExpressionGenerationStrategy::CallExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *CallExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundCallExpression *callExpression =
      static_cast<BoundCallExpression *>(expression);
  _isDeclarationNeeded = false;
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getLocation());

  if (BuiltInFunction::isBuiltInFunction(callExpression->getCallerNameRef())) {
    return this->buildInFunctionCall(callExpression);
  }
  return this->userDefinedFunctionCall(callExpression);
}

void CallExpressionGenerationStrategy::declare(BoundExpression *expression) {
  _isDeclarationNeeded = true;

  BoundCallExpression *callExpression =
      static_cast<BoundCallExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getLocation());

  if (BuiltInFunction::isBuiltInFunction(callExpression->getCallerNameRef())) {
    uint64_t argIndex = 0;

    llvm::Type *builtinReturnType = nullptr;
    const std::string &callerName = callExpression->getCallerNameRef();
    if (callerName == FW::BI::FUNCTION::Int32) {
      builtinReturnType = llvm::Type::getInt32Ty(*TheContext);
    } else if (callerName == FW::BI::FUNCTION::Bool) {
      builtinReturnType = llvm::Type::getInt1Ty(*TheContext);
    } else if (callerName == FW::BI::FUNCTION::Decimal32) {
      builtinReturnType = llvm::Type::getFloatTy(*TheContext);
    } else if (callerName == FW::BI::FUNCTION::Decimal) {
      builtinReturnType = llvm::Type::getDoubleTy(*TheContext);
    } else if (callerName == FW::BI::FUNCTION::Int8) {
      builtinReturnType = llvm::Type::getInt8Ty(*TheContext);
    } else if (callerName == FW::BI::FUNCTION::String ||
               callerName == FW::BI::FUNCTION::Input) {
      //? Default Return Type (String, Print, Input)
      DEBUG_LOG("Builtin Return Type Default",
                "builtinReturnType:" + callExpression->getCallerNameRef());
      builtinReturnType = llvm::Type::getInt8PtrTy(*TheContext);
    }

    DEBUG_LOG("Builtin Return Type",
              "builtinReturnType:" + callExpression->getCallerNameRef());
    DEBUG_LOG("Call Expresssion arg size",
              std::to_string(callExpression->getArgumentPtrList().size()));

    for (auto &arg : callExpression->getArgumentPtrList()) {
      if (!callExpression->doesArgumentAllocaExist(argIndex) &&
          builtinReturnType != nullptr) {
        callExpression->setArgumentAlloca(
            argIndex,
            {_codeGenerationContext->createMemoryGetPtr(
                 builtinReturnType,
                 "builtinReturnType:" + callExpression->getCallerNameRef(),
                 BinderKindUtils::MemoryKind::Stack),
             builtinReturnType});
      }

      if (arg->getKind() == BinderKindUtils::CallExpression) {
        std::unique_ptr<CallExpressionGenerationStrategy>
            callExpressionGenerationStrategy =
                std::make_unique<CallExpressionGenerationStrategy>(
                    _codeGenerationContext);
        callExpressionGenerationStrategy->declare(arg);
      }
      IRCodeGenerator irCodeGen(_codeGenerationContext);
      irCodeGen.declareVariables(arg, false);

      argIndex++;
    }
    return;
  }

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  BoundFunctionDeclaration *definedFunction =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];

  std::vector<llvm::Value *> functionArgs;

  llvm::Function *calleeFunction =
      TheModule->getFunction(callExpression->getCallerNameRef());
  llvm::FunctionType *functionType = nullptr;
  if (!calleeFunction) {
    std::unique_ptr<VariableExpressionGenerationStrategy> varExp =
        std::make_unique<VariableExpressionGenerationStrategy>(
            _codeGenerationContext);

    _codeGenerationContext->getValueStackHandler()->popAll();
    varExp->getVariableValue(callExpression->getCallerNameRef());

    if (_codeGenerationContext->getValueStackHandler()->isFunctionType()) {

      functionType = llvm::cast<llvm::FunctionType>(
          _codeGenerationContext->getValueStackHandler()->getLLVMType());
      _codeGenerationContext->getValueStackHandler()->popAll();
    } else {

      _codeGenerationContext->getLogger()->LogError(
          "Calling undefined function " + callExpression->getCallerNameRef());
      return;
    }
  }

  if (!functionType) {
    if (!calleeFunction) {
      _codeGenerationContext->getLogger()->LogError(
          "Calling undefined function " + callExpression->getCallerNameRef());
      return;
    }
    functionType = calleeFunction->getFunctionType();
  }

  _codeGenerationContext
      ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 0;

  const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(
          callExpression->getCallerNameRef());

  uint64_t funArgsCount = functionType->getNumParams(),
           callArgsCount = callExpression->getArgumentPtrList().size();

  auto funTypePtr =
      _codeGenerationContext->funcPtr(callExpression->getCallerNameRef());

  if (!funTypePtr) {
    _codeGenerationContext->getLogger()->LogError(
        "Calling undefined function " + callExpression->getCallerNameRef() +
        " function not found ");
    return;
  }

  while (funTypePtr && callArgsCount < ((funTypePtr)->getParameterListSize()) &&
         (funTypePtr)->hasOptionalParameters()) {
    callExpression->getArgumentPtrList().push_back(
        (funTypePtr)
            ->getParameterListRef()[callArgsCount]
            ->getInitializerPtr()
            .get());

    callArgsCount++;
  }

  if (_codeGenerationContext->isClassMemberFunction(
          callExpression->getCallerNameRef())) {
    // Its A class Function
    //? (A1, ClassPtr) | (A1) -> Case 1
    //? (ReturnType, A1, ClassPtr) | (A1) -> Case 2

    // ClassPtr removed from the args count

    funArgsCount--;
    if (Utils::isClassInit(callExpression->getCallerNameRef())) {
      // Its the Initilizer Function
      //? (A1, ClassPtr) | (A1) -> Case 1
      if (funArgsCount != callArgsCount) {
        _codeGenerationContext->getLogger()->LogError(
            "Calling Class Initializer " + callExpression->getCallerNameRef() +
            " with " + std::to_string(funArgsCount) +
            " arguments but Expected " + std::to_string(callArgsCount));

        return;
      }
    }
  }

  if ((funTypePtr)->isHavingReturnTypeAsParamater()) {
    // If it memeber function of class or a normal function but has the non
    // primitive return type
    //? (ReturnType, A1, ClassPtr) | (A1) -> Case 2
    //? (ReturnType, A1) | (A1) -> Case 3
    funArgsCount--;
  } else {
    //? (A1) | (A1) -> Case 4
  }

  if (funArgsCount != callArgsCount) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function Expected " +
        std::to_string(funArgsCount) + " arguments but got " +
        std::to_string(callArgsCount));
    return;
  }
  llvm::Value *rhsValue = nullptr;
  uint64_t initialLLVMArgIndex = 0;
  if ((funTypePtr)->isHavingReturnTypeAsParamater()) {
    if (!callExpression->doesArgumentAllocaExist(0)) {
      llvm::Type *rtType = (funTypePtr)->getReturnType();
      callExpression->setArgumentAlloca(
          0, {_codeGenerationContext->createMemoryGetPtr(
                  rtType, "rtPtr", BinderKindUtils::MemoryKind::Stack),
              rtType});
    }
    if (callExpression->getArgumentAlloca(0).second !=
        _codeGenerationContext->getDynamicType()->get()) {
      if (callExpression->getReturnTypeList().size()) {
        if (_codeGenerationContext->verifyType(
                callExpression->getReturnTypeList(),
                llvmArrayArgs[0]->getStructTypeListRef(),
                " in assignment expression") == EXIT_FAILURE) {
          return;
        }
      }
      // else if (_codeGenerationContext->verifyType(
      //                callExpression->getArgumentAlloca(0).second,
      //                llvmArrayArgs[0]->getLLVMType(),
      //                " in '" + callExpression->getCallerNameRef() +
      //                    "' function") == EXIT_FAILURE) {
      //   return;
      // }
    }
    initialLLVMArgIndex++;
    rhsValue = callExpression->getArgumentAlloca(0).first;
  }

  CODEGEN_DEBUG_LOG("Declaring Call Expression ",
                    callExpression->getCallerNameRef(), initialLLVMArgIndex);
  for (uint64_t i = 0; i < callExpression->getArgumentPtrList().size(); i++) {
    uint64_t callArgIndex = i;
    bool retFlag;

    llvm::Value *retVal = handleExpression(
        callArgIndex, initialLLVMArgIndex + callArgIndex, callExpression,
        rhsValue, functionType, llvmArrayArgs, retFlag);
  }

  if (Utils::isClassInit(callExpression->getCallerNameRef())) {
    if (!callExpression->doesArgumentAllocaExist(
            callExpression->getArgumentPtrList().size())) {
      callExpression->setArgumentAlloca(
          callExpression->getArgumentPtrList().size(),
          {_codeGenerationContext->createMemoryGetPtr(
               llvm::Type::getInt8PtrTy(*TheContext), "clPtr",
               BinderKindUtils::MemoryKind::Stack),
           llvm::Type::getInt8PtrTy(*TheContext)});
    }
  }
}

llvm::Type *
CallExpressionGenerationStrategy::isGlobalArray(llvm::Value *value) {
  if (!llvm::isa<llvm::GlobalVariable>(value)) {
    return nullptr;
  }

  auto v = static_cast<llvm::GlobalVariable *>(value);

  // global array
  if (!llvm::isa<llvm::ArrayType>(v->getValueType())) {
    return nullptr;
  }

  llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(v->getValueType());
  llvm::Type *elementType = arrayType->getElementType();

  if (elementType->isIntegerTy(8)) {
    return nullptr;
  }

  return arrayType;
}
llvm::Type *CallExpressionGenerationStrategy::isLocalArray(llvm::Value *value) {
  if (!llvm::isa<llvm::AllocaInst>(value)) {
    return nullptr;
  }

  auto v = static_cast<llvm::AllocaInst *>(value);

  // local array
  if (!llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {
    return nullptr;
  }

  llvm::ArrayType *arrayType =
      llvm::cast<llvm::ArrayType>(v->getAllocatedType());
  llvm::Type *elementType = arrayType->getElementType();

  if (elementType->isIntegerTy(8)) {
    return nullptr;
  }
  return arrayType;
}

llvm::Value *CallExpressionGenerationStrategy::buildInFunctionCall(
    BoundCallExpression *callExpression) {
  std::size_t arguments_size = callExpression->getArgumentPtrList().size();

  const std::string errorMessage =
      "Unexpected Function Call Arguments Does Not Match in " +
      callExpression->getCallerNameRef();

  if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Print) {
    for (auto &callexp : callExpression->getArgumentPtrList()) {
      _codeGenerationContext->getValueStackHandler()->popAll();
      llvm::Value *value =
          _expressionGenerationFactory->createStrategy(callexp->getKind())
              ->generateExpression(callexp);

      handlePrintFunction(value);
    }

    return nullptr;
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Input) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentPtrList()[0]->getKind())
              ->generateExpression(callExpression->getArgumentPtrList()[0]);

      if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
        val = Builder->CreateLoad(
            _codeGenerationContext->getValueStackHandler()->getLLVMType(),
            _codeGenerationContext->getValueStackHandler()->getValue());

        _codeGenerationContext->getValueStackHandler()->popAll();
      }

      printPremitives(val, *Builder);
    }
    llvm::Value *res = Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT));

    return handleInBuiltFunctionReturnValue(res, callExpression);

  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::String) {
    if (arguments_size == 1) {
      llvm::Value *val = nullptr;
      handleInBuiltFunctionCall(callExpression, val);

      llvm::Value *res = _stringTypeConverter->convertExplicit(val);

      return handleInBuiltFunctionReturnValue(res, callExpression);
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Int32) {
    if (arguments_size == 1) {
      llvm::Value *val = nullptr;
      handleInBuiltFunctionCall(callExpression, val);

      llvm::Value *res = _int32TypeConverter->convertExplicit(val);

      return handleInBuiltFunctionReturnValue(res, callExpression);
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Bool) {
    if (arguments_size == 1) {
      llvm::Value *val = nullptr;
      handleInBuiltFunctionCall(callExpression, val);

      llvm::Value *res = _boolTypeConverter->convertExplicit(val);

      return handleInBuiltFunctionReturnValue(res, callExpression);
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Decimal) {
    if (arguments_size == 1) {
      llvm::Value *val = nullptr;
      handleInBuiltFunctionCall(callExpression, val);

      llvm::Value *res = _doubleTypeConverter->convertExplicit(val);

      return handleInBuiltFunctionReturnValue(res, callExpression);
    }
  } else if (callExpression->getCallerNameRef() ==
             FW::BI::FUNCTION::Decimal32) {
    if (arguments_size == 1) {
      llvm::Value *val = nullptr;
      handleInBuiltFunctionCall(callExpression, val);

      llvm::Value *res = _floatTypeConverter->convertExplicit(val);

      return handleInBuiltFunctionReturnValue(res, callExpression);
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Int8) {
    llvm::Value *val = nullptr;
    handleInBuiltFunctionCall(callExpression, val);

    llvm::Value *res = _int8TypeConverter->convertExplicit(val);

    return handleInBuiltFunctionReturnValue(res, callExpression);
  }

  _codeGenerationContext->getLogger()->LogError(errorMessage);
  _codeGenerationContext->getLogger()->LogError("Unexpected Function Call ");

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleInBuiltFunctionReturnValue(
    llvm::Value *res, BoundCallExpression *callExpression) {
  if (callExpression->doesArgumentAllocaExist(0)) {
    auto [ptr, type] = callExpression->getArgumentAlloca(0);

    if (_codeGenerationContext->verifyType(
            type, res->getType(),
            " when calling " + callExpression->getCallerNameRef() +
                " function") == EXIT_FAILURE) {
      return nullptr;
    }
    _codeGenerationContext->getValueStackHandler()->push("", ptr, "primary",
                                                         type);

    Builder->CreateStore(res, ptr);

    return ptr;
  } else {
    _codeGenerationContext->getValueStackHandler()->push("", res, "constant",
                                                         res->getType());
    return res;
  }
}

void CallExpressionGenerationStrategy::handleInBuiltFunctionCall(
    BoundCallExpression *callExpression, llvm::Value *&val) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getLocation());

  val = _expressionGenerationFactory
            ->createStrategy(callExpression->getArgumentPtrList()[0]->getKind())
            ->generateExpression(callExpression->getArgumentPtrList()[0]);

  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    val = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }
}

llvm::Value *
CallExpressionGenerationStrategy::handlePrintFunction(llvm::Value *&value) {
  if (!value) {
    return nullptr;
  }

  if (!_codeGenerationContext->getValueStackHandler()->isEmpty() &&
      (_codeGenerationContext->getValueStackHandler()->isDynamicType() ||
       _codeGenerationContext->getValueStackHandler()->isPrimaryType())) {
    llvm::Value *loaded = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());

    _codeGenerationContext->getValueStackHandler()->popAll();

    printPremitives(loaded, *Builder);
    return nullptr;
  }

  if (llvm::isa<llvm::CallInst>(value)) {
    llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(value);
    auto *calledFunction = calledInst->getCalledFunction();

    llvm::Type *type =
        _codeGenerationContext->getValueStackHandler()->getLLVMType();
    llvm::Value *value =
        _codeGenerationContext->getValueStackHandler()->getValue();

    if (llvm::isa<llvm::StructType>(type)) {
      _codeGenerationContext->getValueStackHandler()->popAll();
      llvm::StructType *structType = nullptr;
      _codeGenerationContext->getReturnedObjectType(calledFunction, structType);
      if (structType) {
        // llvm::LoadInst *loaded = Builder->CreateLoad(structType, value);
        // llvm::Value *localVariable = Builder->CreateAlloca(structType,
        // nullptr); Builder->CreateStore(loaded, localVariable);
        return printObject(value, structType, *Builder);
      }

      return printObject(value, llvm::cast<llvm::StructType>(type), *Builder);
    } else if (llvm::isa<llvm::ArrayType>(type)) {
      _codeGenerationContext->getValueStackHandler()->popAll();
      llvm::Type *elementType = nullptr;
      llvm::ArrayType *arrayType = nullptr;
      std::vector<uint64_t> actualSizes;

      _codeGenerationContext->getRetrunedArrayType(calledFunction, arrayType,
                                                   elementType, actualSizes);
      if (actualSizes.size()) {
        // llvm::LoadInst *loaded = Builder->CreateLoad(type, value);
        // llvm::Value *localVariable = Builder->CreateAlloca(type, nullptr);
        // Builder->CreateStore(loaded, localVariable);
        return printArrayAtom(arrayType, value, actualSizes, elementType,
                              *Builder);
      } else {
        llvm::Type *currentType = type;
        while (true) {
          llvm::ArrayType *at = llvm::cast<llvm::ArrayType>(currentType);
          actualSizes.push_back(at->getNumElements());
          currentType = at->getElementType();
          if (!llvm::isa<llvm::ArrayType>(currentType)) {
            break;
          }
        }

        arrayType = llvm::cast<llvm::ArrayType>(type);
        elementType = arrayType->getElementType();

        return printArrayAtom(arrayType, value, actualSizes, elementType,
                              *Builder);
      }
    }
  }
  if (_codeGenerationContext->getValueStackHandler()->isStructType() &&
      llvm::isa<llvm::PointerType>(value->getType())) {
    std::string typeName =
        _codeGenerationContext->getValueStackHandler()->getTypeName();
    llvm::StructType *structType = llvm::cast<llvm::StructType>(
        _codeGenerationContext->getValueStackHandler()->getLLVMType());
    value = _codeGenerationContext->getValueStackHandler()->getValue();
    _codeGenerationContext->getValueStackHandler()->popAll();

    return printObject(value, structType, *Builder);
  }

  if (_codeGenerationContext->getValueStackHandler()->isArrayType()) {
    llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(
        _codeGenerationContext->getValueStackHandler()->getLLVMType());
    llvm::Value *innerElementPtr =
        _codeGenerationContext->getValueStackHandler()->getValue();
    _codeGenerationContext->getValueStackHandler()->popAll();
    llvm::Type *elementType = arrayType->getElementType();
    llvm::Type *type = arrayType;

    std::vector<uint64_t> sizes;
    while (llvm::ArrayType *arrayType = llvm::dyn_cast<llvm::ArrayType>(type)) {
      sizes.push_back(arrayType->getNumElements());
      type = arrayType->getElementType();
    }
    return printArrayAtom(arrayType, innerElementPtr, sizes, type, *Builder);
  }

  if (llvm::isa<llvm::ArrayType>(value->getType())) {
    llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(value->getType());
    llvm::Type *elementType = arrayType->getElementType();

    if (!elementType->isIntegerTy(8)) {
      return printArray(arrayType, elementType, value, *Builder);
    }
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
        return printArray(arrayType, elementType, v, *Builder);
      }
    }

    if (llvm::isa<llvm::StructType>(v->getAllocatedType())) {
      llvm::StructType *structType =
          llvm::cast<llvm::StructType>(v->getAllocatedType());

      return printObject(value, structType, *Builder);
    }

    printPremitives(value, *Builder);

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
        return printArray(arrayType, elementType, v, *Builder);
      }
    }
    if (llvm::isa<llvm::StructType>(v->getValueType())) {
      llvm::StructType *structType =
          llvm::cast<llvm::StructType>(v->getValueType());

      return printObject(value, structType, *Builder);
    }
  }
  // if (value->getType()->isPointerTy()) {
  //   printString(value, value->getType());
  //   return nullptr;
  // }
  if (_codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          value->getType()) != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
    printPremitives(value, *Builder);
    return nullptr;
  }

  return nullptr;
}

void CallExpressionGenerationStrategy::printPremitives(
    llvm::Value *&value, llvm::IRBuilder<> &Builder) {
  llvm::Value *formatPtr = getUnit("%s", "%s", Builder);

  if (value->getType()->isIntegerTy(32)) {
    formatPtr = getUnit("%d", "%d", Builder);
  } else if (value->getType()->isIntegerTy(64)) {
    formatPtr = getUnit("%ld", "%lld", Builder);
  } else if (value->getType()->isFloatTy()) {
    _doubleTypeConverter->setBuilder(&Builder);
    value = _doubleTypeConverter->convertExplicit(value);
    formatPtr = getUnit("%0.7f", "%0.7f", Builder);
    _doubleTypeConverter->resetBuilder();
  } else if (value->getType()->isDoubleTy()) {
    formatPtr = getUnit("%0.14f", "%0.14f", Builder);
  } else if (value->getType()->isIntegerTy(1)) {
    formatPtr = getUnit("%s", "%s", Builder);
    _stringTypeConverter->setBuilder(&Builder);
    value = _stringTypeConverter->convertExplicit(value);
    _stringTypeConverter->resetBuilder();
  } else if (value->getType()->isIntegerTy(8)) {
    Builder.CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::PUT_CHAR),
        {(Builder.CreateSExt(value, llvm::Type::getInt32Ty(*TheContext)))});
    return;
  }

  Builder.CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT_F),
                     {formatPtr, (value)});
}

llvm::Value *CallExpressionGenerationStrategy::userDefinedFunctionCall(
    BoundCallExpression *callExpression) {
  std::size_t arguments_size = callExpression->getArgumentPtrList().size();

  llvm::Function *calleeFunction =
      TheModule->getFunction(callExpression->getCallerNameRef());
  std::vector<llvm::Value *> classArg = {};
  llvm::Value *classPtr = nullptr;
  llvm::Type *_classType = nullptr;

  {
    auto [value, classType] =
        _codeGenerationContext->getAllocaChain()->getPtr("self");

    const bool IS_SUPER_IS_CALLED_INSIDE_INIT_FUNCTION =
        classType && callExpression->getIsSuperFunctionCall() &&
        Utils::isClassInit(callExpression->getCallerNameRef()) &&
        _codeGenerationContext->_classTypes.find(
            Utils::getActualTypeName(classType->getStructName().str())) !=
            _codeGenerationContext->_classTypes.end() &&
        _codeGenerationContext
            ->_classTypes[Utils::getActualTypeName(
                classType->getStructName().str())]
            ->isChildOf(callExpression->getCallerNameRef().substr(
                0, callExpression->getCallerNameRef().find(
                       FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
                       std::to_string(
                           callExpression->getArgumentPtrList().size()))));

    if (value && classType && llvm::isa<llvm::StructType>(classType) &&
        (!Utils::isClassInit(callExpression->getCallerNameRef()) ||
         IS_SUPER_IS_CALLED_INSIDE_INIT_FUNCTION)) {
      llvm::StructType *structType = llvm::cast<llvm::StructType>(classType);
      std::string funName = callExpression->getCallerNameRef();

      if (funName.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) !=
          std::string::npos) {
        classArg = {value};
      }
      DEBUG_LOG("ITS is CLASS INIT", callExpression->getCallerNameRef(),
                Utils::isClassInit(callExpression->getCallerNameRef()));
    } else if (Utils::isClassInit(callExpression->getCallerNameRef())) {
      std::string className = callExpression->getCallerNameRef();

      className = className.substr(
          0, className.find(
                 FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
                 std::to_string(callExpression->getArgumentPtrList().size())));

      if (_codeGenerationContext->_classTypes.find(className) !=
          _codeGenerationContext->_classTypes.end()) {
        std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
            std::make_unique<AssignmentExpressionGenerationStrategy>(
                _codeGenerationContext);

        {
          classPtr = _codeGenerationContext->createMemoryGetPtr(
              _codeGenerationContext->_classTypes[className]->getClassType(),
              "", BinderKindUtils::MemoryKind::Heap);

          assignmentEGS->initDefaultValue(
              _codeGenerationContext->_classTypes[className]->getClassType(),
              classPtr, *Builder);

          {
            llvm::Value *ptrPtr = Builder->CreateStructGEP(
                _codeGenerationContext->_classTypes[className]->getClassType(),
                classPtr, 0);

            // llvm::Value *vTableGV =
            // _codeGenerationContext->createMemoryGetPtr(
            //     _codeGenerationContext->_classTypes[className]->getVTableType(),
            //     _codeGenerationContext->_classTypes[className]->getVTableName(),
            //     BinderKindUtils::MemoryKind::Global);

            DEBUG_LOG("VTABLE VAR NAME CLASS NAME ", className);
            DEBUG_LOG("VTABLE VAR NAME ",
                      _codeGenerationContext->_classTypes[className]
                          ->getVTableName());
            Builder->CreateStore(_codeGenerationContext->_classTypes[className]
                                     ->getVTableGlobalVariable(),
                                 ptrPtr);

            _codeGenerationContext->_classTypes[className]->populateVTable(
                Builder, TheModule, TheContext, ptrPtr);
          }
        }

        classType =
            _codeGenerationContext->_classTypes[className]->getClassType();
        {
          BoundClassStatement *classStatement =
              _codeGenerationContext->_classTypes[className]
                  ->getBoundClassStatement();

          for (auto &varDec : classStatement->getMemberVariablesRef()) {
            if (_codeGenerationContext->_classTypes[className]
                    ->doesElementExist(varDec->getVariableName())) {
              auto [elementType, index, elementName, _classType] =
                  _codeGenerationContext->_classTypes[className]->getElement(
                      varDec->getVariableName());
              llvm::Value *elementPtr =
                  Builder->CreateStructGEP(_classType, classPtr, index);
              if (varDec->getInitializerPtr().get()) {
                assignmentEGS->handleAssignExpression(
                    elementPtr, elementType, varDec->getVariableName(),
                    varDec->getInitializerPtr().get());
              } else {
                assignmentEGS->initDefaultValue(elementType, elementPtr,
                                                *Builder);
              }
            }
          }
        }
        value =
            callExpression
                ->getArgumentAlloca(callExpression->getArgumentPtrList().size())
                .first;

        Builder->CreateStore(classPtr, value);

        classArg = {value};
        _classType = classType;
        _codeGenerationContext->_classTypes[className]
            ->callAllParentsConstructor(Builder, TheModule, classArg, classPtr,
                                        className);
      }
    }
  }

  return generateCommonCallExpression(callExpression, calleeFunction, classArg,
                                      _classType, classPtr);
}

llvm::Value *CallExpressionGenerationStrategy::generateCommonCallExpression(
    BoundCallExpression *callExpression, llvm::Function *calleeFunction,
    std::vector<llvm::Value *> &classArg, llvm::Type *_classType,
    llvm::Value *_classPtr, llvm::Value *calleeValue) {
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  BoundFunctionDeclaration *definedFunction =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  llvm::FunctionType *functionType = nullptr;
  if (!calleeValue && !calleeFunction &&
      !_codeGenerationContext
           ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()]) {
    _codeGenerationContext
        ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 1;

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        callExpression->getLocation());

    std::unique_ptr<VariableExpressionGenerationStrategy> varExp =
        std::make_unique<VariableExpressionGenerationStrategy>(
            _codeGenerationContext);

    _codeGenerationContext->getValueStackHandler()->popAll();
    llvm::Value *v =
        varExp->getVariableValue(callExpression->getCallerNameRef());

    if (_codeGenerationContext->getValueStackHandler()->isFunctionType()) {

      functionType = llvm::cast<llvm::FunctionType>(
          _codeGenerationContext->getValueStackHandler()->getLLVMType());
      calleeValue = v;
      _codeGenerationContext->getValueStackHandler()->popAll();
    } else {

      _codeGenerationContext->getLogger()->LogError(
          "Function call " + callExpression->getCallerNameRef() + " not found");
      return nullptr;
    }
  }
  std::vector<llvm::Value *> functionArgs;

  if (!functionType) {
    if (!calleeFunction) {
      _codeGenerationContext->getLogger()->LogError(
          "Function call " + callExpression->getCallerNameRef() + " not found");
    }

    functionType = calleeFunction->getFunctionType();
  }

  _codeGenerationContext
      ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 0;

  const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(
          callExpression->getCallerNameRef());

  uint64_t funArgsCount = functionType->getNumParams(),
           callArgsCount = callExpression->getArgumentPtrList().size();

  auto funTypePtr =
      _codeGenerationContext->funcPtr(callExpression->getCallerNameRef());

  while (callArgsCount < (funTypePtr)->getParameterListRef().size() &&
         (funTypePtr)->hasOptionalParameters()) {
    callExpression->getArgumentPtrList().push_back(
        (funTypePtr)
            ->getParameterListRef()[callArgsCount]
            ->getInitializerPtr()
            .get());

    callArgsCount++;
  }

  if (_codeGenerationContext->isClassMemberFunction(
          callExpression->getCallerNameRef())) {
    // Its A class Function
    //? (A1, ClassPtr) | (A1) -> Case 1
    //? (A0, A1, ClassPtr) | (A1) -> Case 2

    // ClassPtr removed from the args count

    funArgsCount--;
    if (Utils::isClassInit(callExpression->getCallerNameRef())) {
      // Its the Initilizer Function
      //? (A1, ClassPtr) | (A1) -> Case 1
      if (funArgsCount != callArgsCount) {
        _codeGenerationContext->getLogger()->LogError(
            "Calling Class Initializer " + callExpression->getCallerNameRef() +
            " with " + std::to_string(funArgsCount) +
            " arguments but Expected " + std::to_string(callArgsCount));

        return nullptr;
      }
    }
  }

  if ((funTypePtr)->isHavingReturnTypeAsParamater()) {
    // If it memeber function of class or a normal function but has the non
    // primitive return type
    //? (A0, A1, ClassPtr) | (A1) -> Case 2
    //? (A0, A1) | (A1) -> Case 3
    //? (A1) | (A1) -> Case 4
    funArgsCount--;
  }

  if (funArgsCount != callArgsCount) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function Expected " +
        std::to_string(funArgsCount) + " arguments but got " +
        std::to_string(callArgsCount));
    return nullptr;
  }
  llvm::Value *rhsValue = nullptr;
  uint64_t initialLLVMArgIndex = 0;
  if ((funTypePtr)->isHavingReturnTypeAsParamater()) {
    if (callExpression->getArgumentAlloca(0).second !=
        _codeGenerationContext->getDynamicType()->get()) {
      if (callExpression->getReturnTypeList().size()) {
        if (_codeGenerationContext->verifyType(
                callExpression->getReturnTypeList(),
                llvmArrayArgs[0]->getStructTypeListRef(),
                " in " + callExpression->getCallerNameRef() +
                    " call expression") == EXIT_FAILURE) {
          return nullptr;
        }
      } else if (_codeGenerationContext->verifyType(
                     callExpression->getArgumentAlloca(0).second,
                     llvmArrayArgs[0]->getLLVMType(),
                     " in '" + callExpression->getCallerNameRef() +
                         "' function") == EXIT_FAILURE) {
        return nullptr;
      }
    }
    initialLLVMArgIndex++;
    rhsValue = callExpression->getArgumentAlloca(0).first;
    functionArgs.push_back(rhsValue);
  }

  for (uint64_t i = 0; i < callExpression->getArgumentPtrList().size(); i++) {
    uint64_t callArgIndex = i;
    bool retFlag;

    llvm::Value *retVal = handleExpression(
        callArgIndex, initialLLVMArgIndex + callArgIndex, callExpression,
        rhsValue, functionType, llvmArrayArgs, retFlag);

    if (retFlag)
      return retVal;
    functionArgs.push_back(rhsValue);
  }

  for (auto &arg : classArg) {
    functionArgs.push_back(arg);
  }
  llvm::CallInst *callIn = nullptr;

  if (calleeValue && functionType)
    callIn = Builder->CreateCall(functionType, calleeValue, functionArgs);
  else
    callIn = Builder->CreateCall(calleeFunction, functionArgs);
  _codeGenerationContext->getValueStackHandler()->popAll();

  if (Utils::isClassInit(callExpression->getCallerNameRef())) {
    _codeGenerationContext->getValueStackHandler()->push("", classArg[0],
                                                         "struct", _classType);
    return classArg[0];
  }

  if (!(funTypePtr)->isHavingReturnTypeAsParamater()) {
    _codeGenerationContext->getValueStackHandler()->push("", callIn, "constant",
                                                         callIn->getType());
    return callIn;
  }

  llvm::Value *res = callExpression->getArgumentAlloca(0).first;
  llvm::Type *type = callExpression->getArgumentAlloca(0).second;

  if (type && type->isArrayTy())
    _codeGenerationContext->getValueStackHandler()->push("", res, "array",
                                                         type);
  else if (type && type->isStructTy())
    _codeGenerationContext->getValueStackHandler()->push("", res, "struct",
                                                         type);
  else if (type) {
    _codeGenerationContext->getValueStackHandler()->push("", res, "primary",
                                                         type);
  } else
    _codeGenerationContext->getValueStackHandler()->push(
        "", nullptr, "nothing", llvm::Type::getVoidTy(*TheContext));

  return res;
}

llvm::Value *CallExpressionGenerationStrategy::handleExpression(
    uint64_t callArgIndex, uint64_t llvmArgsIndex,
    BoundCallExpression *callExpression, llvm::Value *&rhsValue,
    llvm::FunctionType *functionType,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    bool &retFlag) {
  BinderKindUtils::BoundNodeKind kind =
      callExpression->getArgumentPtrList()[callArgIndex]->getKind();
  std::unique_ptr<CallExpressionGenerationStrategy>
      callExpressionGenerationStrategy =
          std::make_unique<CallExpressionGenerationStrategy>(
              _codeGenerationContext);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getArgumentPtrList()[callArgIndex]->getLocation());
  llvm::Value *retVal = nullptr;
  switch (kind) {
    //!!! INDEX EXPRESSION AND CALL EXPRESSION ARE NOT IMPLEMENTED
    //!!!! REMAINING
  case BinderKindUtils::VariableExpression: {
    if (!_isDeclarationNeeded) {
      retVal = handleVariableExpression(rhsValue, callExpression, callArgIndex,
                                        llvmArgsIndex, functionType,
                                        llvmArrayArgs, retFlag);
    } else {
      BoundVariableExpression *variableExpression =
          static_cast<BoundVariableExpression *>(
              callExpression->getArgumentPtrList()[callArgIndex]);

      if (variableExpression->getDotExpressionList().size() > 0 &&
          variableExpression->getDotExpressionList()[0]->getKind() ==
              BinderKindUtils::BoundNodeKind::CallExpression) {
        callExpression->setArgumentAlloca(
            llvmArgsIndex, {_codeGenerationContext->createMemoryGetPtr(
                                llvmArrayArgs[llvmArgsIndex]->getLLVMType(), "",
                                BinderKindUtils::MemoryKind::Stack),
                            llvmArrayArgs[llvmArgsIndex]->getLLVMType()});

        BoundCallExpression *cE = static_cast<BoundCallExpression *>(
            variableExpression->getDotExpressionList()[0].get());
        cE->setArgumentAlloca(0,
                              callExpression->getArgumentAlloca(llvmArgsIndex));
        callExpressionGenerationStrategy->declare(cE);
      }
      retFlag = false;
    }
    break;
  }
  case BinderKindUtils::IndexExpression: {
    if (!_isDeclarationNeeded) {
      retVal = handleIndexExpression(rhsValue, callExpression, callArgIndex,
                                     llvmArgsIndex, functionType, llvmArrayArgs,
                                     retFlag);
    } else {
      // callExpression->setArgumentAlloca(
      //     llvmArgsIndex,
      //     {_codeGenerationContext->createMemoryGetPtr(
      //          llvmArrayArgs[llvmArgsIndex]->getLLVMType(),
      //          arg->getName().str(),
      //          BinderKindUtils::MemoryKind::Stack),
      //      llvmArrayArgs[llvmArgsIndex]->getLLVMType()});
      retFlag = false;
    }
    break;
  }
  case BinderKindUtils::BoundObjectExpression: {
    retVal = handleObjectExpression(llvmArrayArgs, callArgIndex, llvmArgsIndex,
                                    callExpression, rhsValue, retFlag);
    break;
  }
  case BinderKindUtils::BoundBracketedExpression: {
    retVal = handleBracketExpression(llvmArrayArgs, callArgIndex, llvmArgsIndex,
                                     callExpression, rhsValue, retFlag);
    break;
  }
  case BinderKindUtils::CallExpression: {
    BoundCallExpression *cE = static_cast<BoundCallExpression *>(
        callExpression->getArgumentPtrList()[callArgIndex]);

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        cE->getLocation());

    if (BuiltInFunction::isBuiltInFunction(cE->getCallerNameRef())) {
      if (_isDeclarationNeeded) {
        callExpression->setArgumentAlloca(
            llvmArgsIndex, {_codeGenerationContext->createMemoryGetPtr(
                                llvmArrayArgs[llvmArgsIndex]->getLLVMType(), "",
                                BinderKindUtils::MemoryKind::Stack),
                            llvmArrayArgs[llvmArgsIndex]->getLLVMType()});

        cE->setArgumentAlloca(0,
                              callExpression->getArgumentAlloca(llvmArgsIndex));

        callExpressionGenerationStrategy->declare(cE);

      } else {
        callExpressionGenerationStrategy->generateExpression(cE);
        rhsValue = callExpression->getArgumentAlloca(llvmArgsIndex).first;

        _codeGenerationContext->getValueStackHandler()->popAll();
      }
      retFlag = false;
      return nullptr;
    }

    bool isCassInit = cE->getCallerNameRef().find(".init") != std::string::npos;

    if (!isCassInit) {
      if (_isDeclarationNeeded) {
        callExpression->setArgumentAlloca(
            llvmArgsIndex, {_codeGenerationContext->createMemoryGetPtr(
                                llvmArrayArgs[llvmArgsIndex]->getLLVMType(), "",
                                BinderKindUtils::MemoryKind::Stack),
                            llvmArrayArgs[llvmArgsIndex]->getLLVMType()});

        cE->setArgumentAlloca(0,
                              callExpression->getArgumentAlloca(llvmArgsIndex));

        callExpressionGenerationStrategy->declare(cE);

      } else {
        llvm::Value *value =
            callExpressionGenerationStrategy->generateExpression(cE);

        llvm::Type *type =
            _codeGenerationContext->getValueStackHandler()->getLLVMType();

        if (type->isVoidTy()) {
          _codeGenerationContext->getLogger()->LogError(
              "Function " + cE->getCallerNameRef() +
              " does not return a value");

          return nullptr;
        }

        if (_codeGenerationContext->funcPtr(
                callExpression->getCallerNameRef()) &&
            _codeGenerationContext->funcPtr(callExpression->getCallerNameRef())
                ->hasAsParamsRef()[callArgIndex]) {
          rhsValue = Builder->CreateLoad(
              callExpression->getArgumentAlloca(llvmArgsIndex).second,
              callExpression->getArgumentAlloca(llvmArgsIndex).first);
        } else {
          rhsValue = callExpression->getArgumentAlloca(llvmArgsIndex).first;
        }

        _codeGenerationContext->getValueStackHandler()->popAll();
      }
      retFlag = false;
      return nullptr;
    }

    if (_isDeclarationNeeded) {
      callExpression->setArgumentAlloca(
          llvmArgsIndex, {_codeGenerationContext->createMemoryGetPtr(
                              llvm::Type::getInt8PtrTy(*TheContext), "",
                              BinderKindUtils::MemoryKind::Stack),
                          llvmArrayArgs[llvmArgsIndex]->getLLVMType()});

      cE->setArgumentAlloca(cE->getArgumentPtrList().size(),
                            callExpression->getArgumentAlloca(llvmArgsIndex));

      callExpressionGenerationStrategy->declare(cE);
      retFlag = false;
      return nullptr;
    }

    llvm::Value *value =
        callExpressionGenerationStrategy->generateExpression(cE);
    llvm::Type *type =
        _codeGenerationContext->getValueStackHandler()->getLLVMType();

    if (isCassInit) {
      rhsValue = value;
      // Builder->CreateStore(Builder->CreateLoad(type, value),
      // rhsValue);
    } else {
      rhsValue = callExpression->getArgumentAlloca(llvmArgsIndex).first;
    }
    _codeGenerationContext->getValueStackHandler()->popAll();
    retFlag = false;
    break;
  }
  default: {
    retVal = handlePremitive(rhsValue, callExpression, callArgIndex,
                             llvmArgsIndex, llvmArrayArgs, retFlag);
    break;
  }
  }
  if (retFlag)
    return retVal;

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handlePremitive(
    llvm::Value *&rhsValue, BoundCallExpression *callExpression,
    uint64_t callArgIndex, uint64_t llvmArgsIndex,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    bool &retFlag) {
  retFlag = true;

  auto funTypePtr =
      _codeGenerationContext->funcPtr(callExpression->getCallerNameRef());

  if (_isDeclarationNeeded) {
    if ((funTypePtr) && !(funTypePtr)->hasAsParamsRef()[callArgIndex]) {
      llvm::Type *type = llvmArrayArgs[llvmArgsIndex]->getLLVMType();
      callExpression->setArgumentAlloca(
          llvmArgsIndex, {_codeGenerationContext->createMemoryGetPtr(
                              type, "", BinderKindUtils::MemoryKind::Stack),
                          type});
    }
    retFlag = false;
    return nullptr;
  }

  _expressionGenerationFactory
      ->createStrategy(
          callExpression->getArgumentPtrList()[callArgIndex]->getKind())
      ->generateExpression(callExpression->getArgumentPtrList()[callArgIndex]);

  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();

  if ((funTypePtr) && (funTypePtr)->hasAsParamsRef()[callArgIndex]) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {
    rhsValue = callExpression->getArgumentAlloca(llvmArgsIndex).first;
    Builder->CreateStore(
        _codeGenerationContext->getValueStackHandler()->getValue(), rhsValue);
  }
  _codeGenerationContext->getValueStackHandler()->popAll();

  // TODO
  //  if (functionDeclaration->getParametersRef()[i]->getHasInOutKeyword()) {
  //    _codeGenerationContext->getLogger()->LogError(
  //        "Type mismatch in '" + callExpression->getCallerNameRef() +
  //        "' function call expression , Expected 'VARIABLE' of type " +
  //        _codeGenerationContext->getMapper()->getLLVMTypeName(
  //            llvmArrayArgs[i]->getLLVMType()) +
  //        " in order to work with inout parameters but found a 'CONSTANT' of
  //        " "type " +
  //        _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType));
  //    return nullptr;
  //  }

  if (llvmArrayArgs.size() &&
      !_codeGenerationContext->getDynamicType()->isDyn(
          llvmArrayArgs[llvmArgsIndex]->getType()) &&
      llvmArrayArgs[llvmArgsIndex]->getLLVMType() != rhsType &&
      !rhsType->isFunctionTy()) {

    if (_codeGenerationContext->verifyType(
            llvmArrayArgs[llvmArgsIndex]->getLLVMType(), rhsType,
            " in function call expression " +
                Utils::CE(callExpression->getCallerNameRef()) +
                " as parameter") == EXIT_FAILURE) {

      return rhsValue;
    }

  } else if (llvmArrayArgs.size() &&
             _codeGenerationContext->getDynamicType()->isDyn(
                 llvmArrayArgs[llvmArgsIndex]->getLLVMType()) &&
             !rhsType->isFunctionTy()) {
    _codeGenerationContext->getLogger()->LogError(
        "Dynamic type not supported in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter ");
    return rhsValue;
  }
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleBracketExpression(
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    uint64_t callArgIndex, uint64_t llvmArgsIndex,
    BoundCallExpression *callExpression, llvm::Value *&rhsValue,
    bool &retFlag) {
  retFlag = true;
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getArgumentPtrList()[callArgIndex]->getLocation());
  if (!llvmArrayArgs[llvmArgsIndex]->isPointerToArray() &&
      !llvm::isa<llvm::ArrayType>(
          llvmArrayArgs[llvmArgsIndex]->getLLVMType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + "  parameter " +
        " is not an Array");

    return nullptr;
  }
  // TODO
  // BoundFunctionDeclaration *functionDeclaration =
  //     _codeGenerationContext
  //         ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  // if (functionDeclaration->getParametersRef()[i]->getHasInOutKeyword()) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Type mismatch in '" + callExpression->getCallerNameRef() +
  //       "' function call expression , Expected 'VARIABLE' of type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[i]->getLLVMType()) +
  //       " in order to work with inout parameters but found a 'EXPRESSION'
  //       of " "type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[i]->getLLVMType()));
  //   return nullptr;
  // }
  auto assignStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);
  if (_isDeclarationNeeded) {
    llvm::Type *arrayType = llvmArrayArgs[llvmArgsIndex]->getLLVMType();

    llvm::Type *arrayElementType = arrayType;
    std::vector<uint64_t> sizes;
    _codeGenerationContext->createArraySizesAndArrayElementType(
        sizes, arrayElementType);
    llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
        arrayType, "", BinderKindUtils::MemoryKind::Stack);
    callExpression->setArgumentAlloca(llvmArgsIndex, {ptr, arrayType});

    assignStrategy->initDefaultValue(arrayType, ptr, *Builder);
    IRCodeGenerator irCodeGen(_codeGenerationContext);
    irCodeGen.declareVariables(callExpression, false);
  } else {
    llvm::Value *clPtr = callExpression->getArgumentAlloca(llvmArgsIndex).first;
    llvm::Type *arrayType =
        callExpression->getArgumentAlloca(llvmArgsIndex).second;

    assignStrategy->handleAssignExpression(
        clPtr, arrayType, "",
        callExpression->getArgumentPtrList()[callArgIndex]);

    rhsValue = clPtr;
    auto funTypePtr =
        _codeGenerationContext->funcPtr(callExpression->getCallerNameRef());

    if (funTypePtr && (funTypePtr)->hasAsParamsRef()[callArgIndex]) {
      rhsValue = Builder->CreateLoad(arrayType, rhsValue);
    }
  }
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleObjectExpression(
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    uint64_t callArgIndex, uint64_t llvmArgsIndex,
    BoundCallExpression *callExpression, llvm::Value *&rhsValue,
    bool &retFlag) {
  retFlag = true;
  if (!llvmArrayArgs[llvmArgsIndex]->isPointerToObject()) {
    _codeGenerationContext->getLogger()->LogError(
        "You are passing Object to function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        ", but it is not an Object");

    return nullptr;
  }

  LLVMObjectType *llvmObjectType =
      static_cast<LLVMObjectType *>(llvmArrayArgs[llvmArgsIndex].get());

  // TODO !
  //! Will Include this restriction in next update
  // BoundFunctionDeclaration *functionDeclaration =
  //     _codeGenerationContext
  //         ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  // if (functionDeclaration->getParametersRef()[callArgIndex]
  //         ->getHasInOutKeyword()) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Type mismatch in '" + callExpression->getCallerNameRef() +
  //       "' function call expression , Expected 'VARIABLE' of type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[callArgIndex]->getLLVMType()) +
  //       " in order to work with inout parameters but found an 'EXPRESSION'
  //       of " " type " +
  //       _codeGenerationContext->getMapper()
  //           ->getLLVMTypeName(llvmObjectType->getLLVMType()));
  //   return nullptr;
  // }

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignExpGenStrat =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
      std::make_unique<ObjectExpressionGenerationStrategy>(
          _codeGenerationContext);

  std::string objectTypeName =
      llvmObjectType->getStructType()->getStructName().str();
  objExpGenStrat->setTypeName(objectTypeName);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getArgumentPtrList()[callArgIndex]->getLocation());

  if (_codeGenerationContext->_classTypes.find(objectTypeName) !=
          _codeGenerationContext->_classTypes.end() &&
      _codeGenerationContext->_classTypes[objectTypeName]) {
    _codeGenerationContext->getLogger()->LogError(
        "You are passing Object to function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +

        ", but it is not an Object, it is a " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            _codeGenerationContext->_classTypes[objectTypeName]
                ->getClassType()));

    return nullptr;

    // llvm::StructType *classType =
    //     _codeGenerationContext->_classTypes[objectTypeName]->getClassType();

    // llvm::Value *classPtr = _codeGenerationContext->createMemoryGetPtr(
    //     classType, arg->getName().str(),
    //     BinderKindUtils::MemoryKind::Heap);

    // _codeGenerationContext->getAllocaChain()->setPtr(objectTypeName,
    //                                                  {classPtr,
    //                                                  classType});

    // assignExpGenStrat->initDefaultValue(classType, classPtr);

    // objExpGenStrat->setVariable(classPtr);
    // objExpGenStrat->generateGlobalExpression(
    //     callExpression->getArgumentPtrList()[callArgIndex].get());
  }

  if (_isDeclarationNeeded) {
    llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
        llvmObjectType->getStructType(), "",
        BinderKindUtils::MemoryKind::Stack);
    callExpression->setArgumentAlloca(llvmArgsIndex,
                                      {ptr, llvmObjectType->getStructType()});

    assignExpGenStrat->initDefaultValue(llvmObjectType->getStructType(), ptr,
                                        *Builder);

    IRCodeGenerator irCodeGen(_codeGenerationContext);
    irCodeGen.declareVariables(callExpression, false);
  } else {
    rhsValue = callExpression->getArgumentAlloca(llvmArgsIndex).first;

    _codeGenerationContext->getAllocaChain()->setPtr(
        rhsValue->getName().str(), {rhsValue, rhsValue->getType()});

    objExpGenStrat->setVariable(rhsValue);
    objExpGenStrat->generateExpression(
        callExpression->getArgumentPtrList()[callArgIndex]);
  }

  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleVariableExpression(
    llvm::Value *&rhsValue, BoundCallExpression *callExpression,
    uint64_t callArgIndex, uint64_t llvmArgsIndex,
    llvm::FunctionType *functionType,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    bool &retFlag) {
  retFlag = true;

  if (!callExpression->getArgumentPtrList()[callArgIndex]) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function Expected " +
        std::to_string(functionType->getNumParams()) + " arguments but got " +
        std::to_string(llvmArrayArgs.size()));
    return nullptr;
  }

  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(
          callExpression->getArgumentPtrList()[callArgIndex]);

  _expressionGenerationFactory
      ->createStrategy(
          callExpression->getArgumentPtrList()[callArgIndex]->getKind())
      ->generateExpression(callExpression->getArgumentPtrList()[callArgIndex]);

  rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();

  llvm ::Type *varType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();

  _codeGenerationContext->getValueStackHandler()->popAll();

  // if (llvmArrayArgs[llvmArgsIndex]->isPointerToArray() &&
  //     variableExpression->getVariableTypeRef()->getSyntaxType() !=
  //         SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Expected Array in function call expression " +
  //       Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
  //       Utils::CE(arg->getName().str()) + ", but found " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           variableExpression->getVariableTypeRef()->getSyntaxType()));
  //   return nullptr;
  // }

  // if (llvmArrayArgs[llvmArgsIndex]->isPointerToObject() &&
  //     variableExpression->getVariableTypeRef()->getSyntaxType() !=
  //         SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Expected Object in function call expression " +
  //       Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
  //       Utils::CE(arg->getName().str()) + ", but found " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           variableExpression->getVariableTypeRef()->getSyntaxType()));
  //   return nullptr;
  // }

  if (llvmArrayArgs.size() &&
      llvmArrayArgs[llvmArgsIndex]->isPointerToArray()) {
    LLVMArrayType *llvmArrayType =
        static_cast<LLVMArrayType *>(llvmArrayArgs[llvmArgsIndex].get());
    llvm::ArrayType *FArrayType =
        static_cast<llvm::ArrayType *>(llvmArrayType->getLLVMType());
    llvm::ArrayType *arrayType = static_cast<llvm::ArrayType *>(varType);

    llvm::Type *_res = isGlobalArray(rhsValue);
    _res = _res ? _res : isLocalArray(rhsValue);

    if (!_res) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Array of " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmArrayType->getArrayElementType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          ", but found " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType()));
      return nullptr;
    }

    if (_codeGenerationContext->verifyArrayType(
            FArrayType, arrayType,
            " in function call expression " +
                callExpression->getCallerNameRef()) == EXIT_FAILURE) {
      return nullptr;
    }
  } else if (llvmArrayArgs[llvmArgsIndex]->isPointerToObject() &&
             llvm::isa<llvm::StructType>(varType)) {
    LLVMObjectType *llvmObjType =
        static_cast<LLVMObjectType *>(llvmArrayArgs[llvmArgsIndex].get());
    llvm::StructType *fParamStructType = llvmObjType->getStructType();

    llvm::StructType *structType = llvm::cast<llvm::StructType>(varType);
    std::string structName = structType->getStructName().str();
    if (_codeGenerationContext->_classTypes.find(
            structType->getStructName().str().substr(
                0, structType->getStructName().str().find(
                       FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX))) !=
        _codeGenerationContext->_classTypes.end()) {
      if (!_codeGenerationContext
               ->_classTypes[structName.substr(
                   0, structName.find(
                          FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX))]
               ->isChildOf(fParamStructType->getStructName().str().substr(
                   0, fParamStructType->getStructName().str().find(
                          FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX)))) {
        _codeGenerationContext->getLogger()->LogError(
            "Expected Object of type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(
                fParamStructType) +
            " in function call expression " +
            Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
            ", but found object of type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(structType));
        return nullptr;
      }
    } else if (Utils::getActualTypeName(
                   fParamStructType->getStructName().str()) !=
               Utils::getActualTypeName(structName)) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Object of type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(structType) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          ", but found object of type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              fParamStructType));
      return nullptr;
    }

  } else if (llvmArrayArgs[llvmArgsIndex]->isPointerToFunction()) {
    LLVMFunctionType *llvmFunctionType =
        static_cast<LLVMFunctionType *>(llvmArrayArgs[llvmArgsIndex].get());

    if (llvmFunctionType->getLLVMType() != varType) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected type " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmFunctionType->getLLVMType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          ", but found type " +
          Utils::CE(
              _codeGenerationContext->getMapper()->getLLVMTypeName(varType)));
      return nullptr;
    }
  } else if (llvmArrayArgs[llvmArgsIndex]->isPointerToPrimitive()) {
    LLVMPrimitiveType *llvmPrimitiveType =
        static_cast<LLVMPrimitiveType *>(llvmArrayArgs[llvmArgsIndex].get());

    if (llvmPrimitiveType->getLLVMType() != varType) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected type " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmPrimitiveType->getLLVMType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          ", but found type " +
          Utils::CE(
              _codeGenerationContext->getMapper()->getLLVMTypeName(varType)));
      return nullptr;
    }
  } else {
    if (llvmArrayArgs[llvmArgsIndex]->getLLVMType() != varType &&
        !varType->isFunctionTy()) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected type " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmArrayArgs[llvmArgsIndex]->getLLVMType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          ", but found type " +
          Utils::CE(
              _codeGenerationContext->getMapper()->getLLVMTypeName(varType)));
      return nullptr;
    }
  }

  if (_codeGenerationContext->funcPtr(callExpression->getCallerNameRef()) &&
      _codeGenerationContext->funcPtr(callExpression->getCallerNameRef())
          ->hasAsParamsRef()[callArgIndex]) {
    rhsValue = Builder->CreateLoad(varType, rhsValue);
  }
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleIndexExpression(
    llvm::Value *&rhsValue, BoundCallExpression *callExpression,
    uint64_t callArgIndex, uint64_t llvmArgsIndex,
    llvm::FunctionType *functionType,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    bool &retFlag) {
  retFlag = false;
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      callExpression->getArgumentPtrList()[callArgIndex]->getLocation());
  _expressionGenerationFactory
      ->createStrategy(
          callExpression->getArgumentPtrList()[callArgIndex]->getKind())
      ->generateExpression(callExpression->getArgumentPtrList()[callArgIndex]);
  rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();

  auto funTypePtr =
      _codeGenerationContext->funcPtr(callExpression->getCallerNameRef());
  if (funTypePtr && (funTypePtr)->hasAsParamsRef()[callArgIndex]) {
    rhsValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  }
  llvm::Type *varType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  _codeGenerationContext->getValueStackHandler()->popAll();

  return nullptr;
}

void CallExpressionGenerationStrategy::handleArrayArgs(
    const std::vector<llvm::Type *> &paramTypes, const int &i,
    const std::vector<llvm::Value *> &args, BoundCallExpression *callExpression,
    int &retFlag) {
  retFlag = 1;
  llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(paramTypes[i]);
  llvm::ArrayType *argArrayType = nullptr;

  // Local Array
  if (llvm::isa<llvm::AllocaInst>(args[i])) {
    llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(args[i]);
    if (llvm::isa<llvm::ArrayType>(allocaInst->getAllocatedType())) {
      argArrayType =
          llvm::cast<llvm::ArrayType>(allocaInst->getAllocatedType());
    }
  }

  // Global Array
  if (llvm::isa<llvm::GlobalVariable>(args[i])) {
    llvm::GlobalVariable *globalVariable =
        llvm::cast<llvm::GlobalVariable>(args[i]);
    if (llvm::isa<llvm::ArrayType>(globalVariable->getValueType())) {
      argArrayType =
          llvm::cast<llvm::ArrayType>(globalVariable->getValueType());
    }
  }

  if (!argArrayType) {
    _codeGenerationContext->getLogger()->LogError(
        "Type Mismatch in " + callExpression->getCallerNameRef() +
        " Expected  Array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            arrayType->getElementType()) +
        " Found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            args[i]->getType()));

    return;
  }

  if (argArrayType->getElementType() != arrayType->getElementType()) {
    _codeGenerationContext->getLogger()->LogError(
        "Type of Array Element is not same in function call "
        "expression " +
        callExpression->getCallerNameRef() + " Expected " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            arrayType->getElementType()) +
        " Found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            argArrayType->getElementType()));
    return;
  }
  { retFlag = 3; };
}

llvm::Value *CallExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  _isGlobal = true;
  return this->generateExpression(expression);
}

void CallExpressionGenerationStrategy::printUnit(const std::string &unit,
                                                 const std::string &unitName,
                                                 llvm::IRBuilder<> &Builder) {
  Builder.CreateCall(
      TheModule->getFunction(INNERS::FUNCTIONS::PRINT_F),
      {getUnit("%s", "%s", Builder), getUnit(unit, unitName, Builder)});
}

llvm::Value *
CallExpressionGenerationStrategy::getUnit(const std::string &unit,
                                          const std::string &unitName,
                                          llvm::IRBuilder<> &Builder) {
  llvm::GlobalVariable *variable = TheModule->getGlobalVariable(unitName);
  if (!variable) {
    // The global variable doesn't exist
    llvm::Constant *initializer = Builder.CreateGlobalStringPtr(unit);
    variable = new llvm::GlobalVariable(
        /*Module=*/*TheModule,
        /*Type=*/initializer->getType(),
        /*isConstant=*/true,
        /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
        /*Initializer=*/initializer,
        /*Name=*/unitName);
  }

  return Builder.CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), variable);
}

void CallExpressionGenerationStrategy::printString(llvm::Value *value,
                                                   llvm::Type *type,
                                                   llvm::IRBuilder<> &Builder) {
  printUnit("'", "'", Builder);
  llvm::BasicBlock *currentBlock = Builder.GetInsertBlock();
  llvm::BasicBlock *isNullBlock = llvm::BasicBlock::Create(
      *TheContext, "IsNull", currentBlock->getParent());
  llvm::BasicBlock *endBlock =
      llvm::BasicBlock::Create(*TheContext, "End", currentBlock->getParent());
  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(*TheContext, "Merge", currentBlock->getParent());

  // Create a null pointer constant of the same type as yourValue
  llvm::Constant *nullPtr = llvm::Constant::getNullValue(type);

  // Compare yourValue with the null pointer constant
  llvm::Value *isNullValue = Builder.CreateICmpNE(value, nullPtr);

  Builder.CreateCondBr(isNullValue, endBlock, isNullBlock);

  Builder.SetInsertPoint(isNullBlock);

  Builder.CreateBr(mergeBlock);

  Builder.SetInsertPoint(endBlock);

  printPremitives(value, Builder);

  Builder.CreateBr(mergeBlock);

  Builder.SetInsertPoint(mergeBlock);
  printUnit("'", "'", Builder);
}

llvm::Value *CallExpressionGenerationStrategy::printArrayAtom(
    llvm::ArrayType *&arrayType, llvm::Value *&v,
    const std::vector<uint64_t> &actualSizes, llvm::Type *&elementType,
    llvm::IRBuilder<> &Builder) {
  const std::string FUNCTION_NAME =
      "print_" + _codeGenerationContext->getArrayTypeAsString(arrayType);

  llvm::Function *fun = TheModule->getFunction(FUNCTION_NAME);

  if (!fun) {
    llvm::FunctionType *FT = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*TheContext),
        {llvm::PointerType::getUnqual(arrayType)}, false);
    fun = llvm::Function::Create(FT,
                                 llvm::Function::LinkageTypes::InternalLinkage,
                                 FUNCTION_NAME, *TheModule);

    llvm::BasicBlock *entry =
        llvm::BasicBlock::Create(*TheContext, "entry", fun);
    llvm::IRBuilder<> builder(entry);

    llvm::BasicBlock *currentBlock = builder.GetInsertBlock();

    std::vector<std::vector<llvm::BasicBlock *>> loopBlocks;
    std::vector<llvm::Value *> indices;

    for (int i = 0; i < actualSizes.size(); i++) {
      std::vector<llvm::BasicBlock *> blocks = {
          llvm::BasicBlock::Create(*TheContext, "con_print.loopStart",
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext, "con_print.loopCmp",
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext, "con_print.loopBody",
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext, "con_print.loopEnd",
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext, "con_print.print.lobby",
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext, "con_print.stage",
                                   currentBlock->getParent())};

      llvm::Value *index = builder.CreateAlloca(builder.getInt32Ty(), nullptr,
                                                std::to_string(i) + "_i");
      indices.push_back(index);
      loopBlocks.push_back(blocks);
    }

    llvm::Value *numberOfElementsFilled = builder.CreateAlloca(
        builder.getInt32Ty(), nullptr, "numberOfElementsFilled");

    builder.CreateStore(builder.getInt32(0), numberOfElementsFilled);

    llvm::BasicBlock *exit = llvm::BasicBlock::Create(
        *TheContext, "con_print.exit", currentBlock->getParent());

    builder.CreateBr(loopBlocks[0][0]);

    for (int i = 0; i < actualSizes.size(); i++) {
      // start
      builder.SetInsertPoint(loopBlocks[i][0]);
      builder.CreateStore(builder.getInt32(0), indices[i]);
      printUnit("[", "openBracket", builder);
      builder.CreateBr(loopBlocks[i][1]);

      // cmp
      builder.SetInsertPoint(loopBlocks[i][1]);
      llvm::Value *currentIndex =
          builder.CreateLoad(builder.getInt32Ty(), indices[i]);
      llvm::Value *isLessThanActualSize =
          builder.CreateICmpSLT(currentIndex, builder.getInt32(actualSizes[i]));
      //!
      llvm::Value *isGreaterThanZero =
          builder.CreateICmpSGT(currentIndex, builder.getInt32(0));
      llvm::Value *showPrintLobby =
          builder.CreateAnd(isLessThanActualSize, isGreaterThanZero);
      //!

      builder.CreateCondBr(showPrintLobby, loopBlocks[i][4], loopBlocks[i][5]);

      //? print Lobby
      builder.SetInsertPoint(loopBlocks[i][4]);
      printUnit(", ", "comma", builder);
      builder.CreateBr(loopBlocks[i][2]);
      //?

      //! Stage
      builder.SetInsertPoint(loopBlocks[i][5]);
      llvm::Value *currentIndex_stage =
          builder.CreateLoad(builder.getInt32Ty(), indices[i]);
      llvm::Value *isLessThanActualSize_Stage = builder.CreateICmpSLT(
          currentIndex_stage, builder.getInt32(actualSizes[i]));
      builder.CreateCondBr(isLessThanActualSize_Stage, loopBlocks[i][2],
                           loopBlocks[i][3]);

      // body
      builder.SetInsertPoint(loopBlocks[i][2]);
      if (i == actualSizes.size() - 1) {
        std::vector<llvm::Value *> indexList = {builder.getInt32(0)};

        for (int j = 0; j < actualSizes.size(); j++) {
          indexList.push_back(
              builder.CreateLoad(builder.getInt32Ty(), indices[j]));
        }

        llvm::Value *elementPtr =
            builder.CreateGEP(arrayType, fun->getArg(0), indexList);

        //! Printing Starts
        llvm::Value *innerValue = nullptr;
        // Untyped Container Element
        if (_codeGenerationContext->getDynamicType()->isDyn(elementType)) {
          innerValue =
              _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
                  elementPtr, v->getName().str());
        } else if (llvm::isa<llvm::StructType>(elementType)) {
          printObject(elementPtr, llvm::cast<llvm::StructType>(elementType),
                      builder);
        } else {
          // Typed Container Element
          innerValue = builder.CreateLoad(elementType, elementPtr);

          if (innerValue->getType()->isPointerTy()) {
            printString(innerValue, elementType, builder);
          } else {
            // builder.CreateCall(
            //     TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
            //     {_stringTypeConverter->convertExplicit(innerValue),
            //      builder.getInt1(false)});

            printPremitives(innerValue, builder);
          }
        }

        //! Printing Ends
        llvm::Value *_currentIndex =
            builder.CreateLoad(builder.getInt32Ty(), indices[i]);
        llvm::Value *nextIndex =
            builder.CreateAdd(_currentIndex, builder.getInt32(1));
        builder.CreateStore(nextIndex, indices[i]);

        builder.CreateBr(loopBlocks[i][1]);
      } else {
        builder.CreateBr(loopBlocks[i + 1][0]);
      }

      // end
      builder.SetInsertPoint(loopBlocks[i][3]);
      if (i != 0) {
        llvm::Value *_currentIndex =
            builder.CreateLoad(builder.getInt32Ty(), indices[i - 1]);
        llvm::Value *nextIndex =
            builder.CreateAdd(_currentIndex, builder.getInt32(1));
        builder.CreateStore(nextIndex, indices[i - 1]);

        printUnit("]", "closeBracket", builder);
        builder.CreateBr(loopBlocks[i - 1][1]);
      } else {
        printUnit("]", "closeBracket", builder);
        builder.CreateBr(exit);
      }
    }

    builder.SetInsertPoint(exit);
    builder.CreateRetVoid();
  }

  Builder.CreateCall(fun, {v});
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::printArray(
    llvm::ArrayType *arrayType, llvm::Type *elementType, llvm::Value *v,
    llvm::IRBuilder<> &Builder) {
  std::vector<uint64_t> sizes;
  _codeGenerationContext->getArraySizeMetadata(v, sizes);
  llvm::Type *elt = _codeGenerationContext->getArrayElementTypeMetadata(v);
  printArrayAtom(arrayType, v, sizes, elt, Builder);

  return nullptr;
}

llvm::Value *
CallExpressionGenerationStrategy::printObject(llvm::Value *outerElementPtr,
                                              llvm::StructType *parObjType,
                                              llvm::IRBuilder<> &Builder) {
  const std::string FUNCTION_NAME =
      "print_" + parObjType->getStructName().str();

  llvm::Function *fun = TheModule->getFunction(FUNCTION_NAME);

  if (!fun) {
    llvm::FunctionType *FT = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*TheContext),
        {llvm::PointerType::getUnqual(parObjType)}, false);
    fun = llvm::Function::Create(FT,
                                 llvm::Function::LinkageTypes::InternalLinkage,
                                 FUNCTION_NAME, *TheModule);

    llvm::BasicBlock *entry =
        llvm::BasicBlock::Create(*TheContext, "entry", fun);
    llvm::IRBuilder<> builder(entry);

    printUnit("{ ", "{ ", builder);

    BoundCustomTypeStatement *boundCustomTypeStatement =
        _codeGenerationContext
            ->getFlowWingType(parObjType->getStructName().str())
            .getCustomType();

    if (!boundCustomTypeStatement) {
      if (_codeGenerationContext->isValidClassType(parObjType)) {
        _codeGenerationContext->getLogger()->LogError(
            "variable of class " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(parObjType) +
            " can not be printed directly, use member functions instead");
        return nullptr;
      }

      _codeGenerationContext->getLogger()->LogError(
          "variable of type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(parObjType) +
          " not found in variable expression ");
      return nullptr;
    }

    uint64_t i = 0;
    const std::string KEY_PRIFIX =
        boundCustomTypeStatement->getTypeNameAsString();
    for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
      std::string typeName = std::any_cast<std::string>(bLE->getValue());
      std::string propertyKey = std::any_cast<std::string>(bLE->getValue());

      builder.CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
          {builder.CreateGlobalStringPtr(propertyKey), builder.getInt1(false)});
      printUnit(" : ", " : ", builder);
      std::string key = KEY_PRIFIX + "." + propertyKey;
      size_t index = _codeGenerationContext->getFlowWingType(key).getIndex();

      if (index == -1) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + key + " not found in variable expression ");

        return nullptr;
      }

      llvm::Value *innerElementPtr =
          builder.CreateStructGEP(parObjType, fun->getArg(0), i);

      llvm::Type *type = parObjType->getElementType(i);
      if (bTE->getSyntaxType() ==
          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
        llvm::StructType *structType = llvm::cast<llvm::StructType>(type);

        printObject(innerElementPtr, structType, builder);
      } else if (bTE->getSyntaxType() ==
                 SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
        llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
        llvm::Type *elementType = arrayType->getElementType();
        llvm::Type *type = arrayType;
        std::vector<uint64_t> sizes;
        _codeGenerationContext->createArraySizesAndArrayElementType(sizes,
                                                                    type);
        printArrayAtom(arrayType, innerElementPtr, sizes, type, builder);
      } else {
        llvm::LoadInst *loaded = builder.CreateLoad(type, innerElementPtr);

        llvm::Value *loadedVal = llvm::cast<llvm::Value>(loaded);
        if (loaded->getType()->isPointerTy()) {
          printString(loadedVal, type, builder);
        } else {
          printPremitives(loadedVal, builder);
          //    builder.CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
          //                     {_stringTypeConverter->convertExplicit(loadedVal),
          //                         builder.getInt1(false)});
        }
      }
      if (i != boundCustomTypeStatement->getKeyPairs().size() - 1)
        printUnit(", ", " , ", builder);

      i++;
    }

    printUnit(" }", "}", builder);

    builder.CreateRetVoid();
  }

  Builder.CreateCall(fun, {outerElementPtr});

  return nullptr;
}