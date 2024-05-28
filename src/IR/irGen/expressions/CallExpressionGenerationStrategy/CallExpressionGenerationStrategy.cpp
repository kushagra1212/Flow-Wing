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

  if (BuiltInFunction::isBuiltInFunction(callExpression->getCallerNameRef())) {
    return this->buildInFunctionCall(callExpression);
  }
  return this->userDefinedFunctionCall(callExpression);
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
  std::size_t arguments_size = callExpression->getArgumentsRef().size();

  const std::string errorMessage =
      "Unexpected Function Call Arguments Does Not Match in " +
      callExpression->getCallerNameRef();

  if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Print) {

    for (auto &callexp : callExpression->getArgumentsRef()) {

      llvm::Value *value =
          _expressionGenerationFactory->createStrategy(callexp->getKind())
              ->generateExpression(callexp.get());

      handlePrintFunction(value);
    }

    return nullptr;
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Input) {
    if (arguments_size == 0) {

      return Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT));
    } else if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                          {_stringTypeConverter->convertExplicit(val),
                           Builder->getInt1(false)});

      return Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT));
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::String) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      return _stringTypeConverter->convertExplicit(val);
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Int32) {
    if (arguments_size == 1) {
      llvm::Value *res = nullptr;
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      res = _int32TypeConverter->convertExplicit(val);
      return res;
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Bool) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      return _boolTypeConverter->convertExplicit(val);
    }
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Decimal) {
    if (arguments_size == 1) {
      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      return _doubleTypeConverter->convertExplicit(val);
    }
  }

  _codeGenerationContext->getLogger()->LogError(errorMessage);
  _codeGenerationContext->getLogger()->LogError("Unexpected Function Call ");

  return nullptr;
}

llvm::Value *
CallExpressionGenerationStrategy::handlePrintFunction(llvm::Value *&value) {
  if (!value) {
    return nullptr;
  }

  if (!_codeGenerationContext->getValueStackHandler()->isEmpty() &&
      _codeGenerationContext->getValueStackHandler()->isDynamicType()) {

    llvm::Value *loaded = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());

    _codeGenerationContext->getValueStackHandler()->popAll();

    Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                        {_stringTypeConverter->convertExplicit(loaded),
                         Builder->getInt1(false)});
    return nullptr;
  }

  // if (!_codeGenerationContext->getValueStackHandler()->isEmpty()) {
  //   llvm::Value *ptr =
  //       _codeGenerationContext->getValueStackHandler()->getValue();
  //   llvm::Type *type =
  //       _codeGenerationContext->getValueStackHandler()->getLLVMType();

  //   _codeGenerationContext->getValueStackHandler()->popAll();

  //   if (llvm::isa<llvm::StructType>(type))
  //     return printObject(Builder->CreateLoad(type, ptr),
  //                        llvm::cast<llvm::StructType>(type));

  //   if (llvm::isa<llvm::ArrayType>(type)) {
  //     llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
  //     _codeGenerationContext->getValueStackHandler()->popAll();
  //     llvm::Type *elementType = arrayType->getElementType();
  //     llvm::Type *type = arrayType;

  //     std::vector<uint64_t> sizes;
  //     while (llvm::ArrayType *arrayType =
  //                llvm::dyn_cast<llvm::ArrayType>(type)) {
  //       sizes.push_back(arrayType->getNumElements());
  //       type = arrayType->getElementType();
  //     }
  //     return printArrayAtom(arrayType, ptr, sizes, type);
  //   }
  // }

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
        llvm::LoadInst *loaded = Builder->CreateLoad(structType, value);
        llvm::Value *localVariable = Builder->CreateAlloca(structType, nullptr);
        Builder->CreateStore(loaded, localVariable);
        return printObject(localVariable, structType);
      }

      return printObject(value, llvm::cast<llvm::StructType>(type));
    } else if (llvm::isa<llvm::ArrayType>(type)) {
      _codeGenerationContext->getValueStackHandler()->popAll();
      llvm::Type *elementType = nullptr;
      llvm::ArrayType *arrayType = nullptr;
      std::vector<uint64_t> actualSizes;

      _codeGenerationContext->getRetrunedArrayType(calledFunction, arrayType,
                                                   elementType, actualSizes);
      if (actualSizes.size()) {

        llvm::LoadInst *loaded = Builder->CreateLoad(type, value);
        llvm::Value *localVariable = Builder->CreateAlloca(type, nullptr);
        Builder->CreateStore(loaded, localVariable);
        return printArrayAtom(arrayType, localVariable, actualSizes,
                              elementType);
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

        return printArrayAtom(arrayType, value, actualSizes, elementType);
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

    return printObject(value, structType);
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
    return printArrayAtom(arrayType, innerElementPtr, sizes, type);
  }

  if (llvm::isa<llvm::ArrayType>(value->getType())) {
    llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(value->getType());
    llvm::Type *elementType = arrayType->getElementType();

    if (!elementType->isIntegerTy(8)) {
      return printArray(arrayType, elementType, value);
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
        return printArray(arrayType, elementType, v);
      }
    }

    if (llvm::isa<llvm::StructType>(v->getAllocatedType())) {
      llvm::StructType *structType =
          llvm::cast<llvm::StructType>(v->getAllocatedType());

      return printObject(value, structType);
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
    if (llvm::isa<llvm::StructType>(v->getValueType())) {
      llvm::StructType *structType =
          llvm::cast<llvm::StructType>(v->getValueType());

      return printObject(value, structType);
    }
  }
  // if (value->getType()->isPointerTy()) {
  //   printString(value, value->getType());
  //   return nullptr;
  // }
  if (_codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          value->getType()) != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
    Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                        {_stringTypeConverter->convertExplicit(value),
                         Builder->getInt1(false)});
    return nullptr;
  }

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::userDefinedFunctionCall(
    BoundCallExpression *callExpression) {
  std::size_t arguments_size = callExpression->getArgumentsRef().size();

  llvm::Function *calleeFunction =
      TheModule->getFunction(callExpression->getCallerNameRef());
  std::vector<llvm::Value *> classArg = {};
  llvm::Value *_classPtr = nullptr;
  llvm::Type *_classType = nullptr;

  {
    auto [value, classType] =
        _codeGenerationContext->getAllocaChain()->getPtr("self");

    if (value && classType && llvm::isa<llvm::StructType>(classType)) {
      llvm::StructType *structType = llvm::cast<llvm::StructType>(classType);
      std::string funName = callExpression->getCallerNameRef();

      if (funName.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) !=
          std::string::npos) {

        calleeFunction =
            TheModule->getFunction(callExpression->getCallerNameRef());
        classArg = {value};
      }
    } else if (!value && !classType &&
               callExpression->getCallerNameRef().find(
                   FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init") !=
                   std::string::npos) {

      std::string className = callExpression->getCallerNameRef();

      className = className.substr(
          0, className.find(
                 FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
                 std::to_string(callExpression->getArgumentsRef().size())));
      if (_codeGenerationContext->_classTypes.find(className) !=
          _codeGenerationContext->_classTypes.end()) {

        if (_codeGenerationContext->getValueStackHandler()->isStructType()) {
          value = _codeGenerationContext->getValueStackHandler()->getValue();
          _codeGenerationContext->getValueStackHandler()->popAll();
        } else {
          std::unique_ptr<AssignmentExpressionGenerationStrategy>
              assignmentEGS =
                  std::make_unique<AssignmentExpressionGenerationStrategy>(
                      _codeGenerationContext);

          value = _codeGenerationContext->createMemoryGetPtr(
              _codeGenerationContext->_classTypes[className]->getClassType(),
              "", BinderKindUtils::MemoryKind::Heap);

          assignmentEGS->initDefaultValue(
              _codeGenerationContext->_classTypes[className]->getClassType(),
              value);

          {
            llvm::Value *ptrPtr = Builder->CreateStructGEP(
                _codeGenerationContext->_classTypes[className]->getClassType(),
                value, 0);
            Builder->CreateStore(
                TheModule->getOrInsertGlobal(
                    _codeGenerationContext->_classTypes[className]
                        ->getVTableName(),
                    _codeGenerationContext->_classTypes[className]
                        ->getVTableType()),
                ptrPtr);

            _codeGenerationContext->_classTypes[className]->populateVTable(
                Builder, TheModule, TheContext, ptrPtr);
          }
        }

        classType =
            _codeGenerationContext->_classTypes[className]->getClassType();

        calleeFunction =
            TheModule->getFunction(callExpression->getCallerNameRef());
        classArg = {value};
        _classPtr = value;
        _classType = classType;
        _codeGenerationContext->_classTypes[className]
            ->callAllParentsConstructor(Builder, TheModule, classArg, _classPtr,
                                        className);
      }
    }
  }

  return generateCommonCallExpression(callExpression, calleeFunction, classArg,
                                      _classType, _classPtr);
}

llvm::Value *CallExpressionGenerationStrategy::generateCommonCallExpression(
    BoundCallExpression *callExpression, llvm::Function *calleeFunction,
    std::__1::vector<llvm::Value *> &classArg, llvm::Type *_classType,
    llvm::Value *_classPtr, llvm::Value *calleeValue) {
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  BoundFunctionDeclaration *definedFunction =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];

  if (!calleeValue && !calleeFunction &&
      !_codeGenerationContext
           ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()]) {
    _codeGenerationContext
        ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 1;

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        callExpression->getLocation());

    _codeGenerationContext->getLogger()->LogError(
        "Function call " + callExpression->getCallerNameRef() + " not found");
    return nullptr;

    // std::unique_ptr<FunctionStatementGenerationStrategy> fgst =
    //     std::make_unique<FunctionStatementGenerationStrategy>(
    //         _codeGenerationContext);

    // fgst->generateStatementOnFly(definedFunction, args);

    Builder->SetInsertPoint(currentBlock);
  }
  std::vector<llvm::Value *> functionArgs;

  llvm::FunctionType *functionType = calleeFunction->getFunctionType();

  _codeGenerationContext
      ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 0;

  const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(
          callExpression->getCallerNameRef());

  if ((classArg.size()) &&
      functionType->getNumParams() != llvmArrayArgs.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Calling Class Initializer " + callExpression->getCallerNameRef() +
        " with " +
        std::to_string(functionType->getNumParams() - classArg.size()) +
        " arguments but Expected " + std::to_string(llvmArrayArgs.size()));

    return nullptr;
  }

  if (!classArg.size() &&
      functionType->getNumParams() != llvmArrayArgs.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function Expected " +
        std::to_string(functionType->getNumParams()) + " arguments but got " +
        std::to_string(llvmArrayArgs.size()));
    return nullptr;
  }
  llvm::Value *rhsValue = nullptr;

  for (uint64_t i = 0; i < llvmArrayArgs.size() - classArg.size(); i++) {
    bool retFlag;
    llvm::Value *retVal =
        handleExpression(calleeFunction, i, callExpression, rhsValue,
                         functionType, llvmArrayArgs, retFlag);
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

  if (callExpression->getCallerNameRef().find(
          FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init") !=
      std::string::npos) {
    _codeGenerationContext->getValueStackHandler()->push("", _classPtr,
                                                         "struct", _classType);
    return _classPtr;
  }

  // if (!_classType) {
  llvm::ArrayType *arrayType = nullptr;
  llvm::Type *elementType = nullptr;
  std::vector<uint64_t> actualSizes;
  _codeGenerationContext->getRetrunedArrayType(calleeFunction, arrayType,
                                               elementType, actualSizes);

  if (arrayType != nullptr) {

    _codeGenerationContext->getValueStackHandler()->push("", callIn, "array",
                                                         arrayType);

    return callIn;
  }

  llvm::StructType *structType = nullptr;
  _codeGenerationContext->getReturnedObjectType(calleeFunction, structType);
  if (structType != nullptr) {

    _codeGenerationContext->getValueStackHandler()->push("", callIn, "struct",
                                                         structType);
    return callIn;
  }

  llvm::Type *retType = nullptr;
  _codeGenerationContext->getReturnedPrimitiveType(calleeFunction, retType);

  _codeGenerationContext->getValueStackHandler()->push("", callIn, "constant",
                                                       retType);
  // } else {
  //   if (callExpression->hasNewKeyword()) {
  //     _codeGenerationContext->getValueStackHandler()->push(
  //         "", _classPtr, "struct", _classType);
  //     return _classPtr;
  //   } else {
  //     _codeGenerationContext->getValueStackHandler()->push(
  //         "", _classPtr, "struct", _classType);
  //   }
  // }

  return callIn;
}

llvm::Value *CallExpressionGenerationStrategy::handleExpression(
    llvm::Function *calleeFunction, uint64_t i,
    BoundCallExpression *callExpression, llvm::Value *&rhsValue,
    llvm::FunctionType *functionType,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    bool &retFlag) {
  llvm::Argument *arg = calleeFunction->getArg(i);

  BinderKindUtils::BoundNodeKind kind =
      callExpression->getArgumentsRef()[i]->getKind();

  llvm::Value *retVal = nullptr;
  switch (kind) {
    //!!! INDEX EXPRESSION AND CALL EXPRESSION ARE NOT IMPLEMENTED !!! REMAINING
  case BinderKindUtils::VariableExpression: {
    retVal = handleVariableExpression(rhsValue, callExpression, i, functionType,
                                      llvmArrayArgs, arg, retFlag);
    break;
  }
  case BinderKindUtils::IndexExpression: {
    retVal = handleIndexExpression(rhsValue, callExpression, i, functionType,
                                   llvmArrayArgs, arg, retFlag);
    break;
  }
  case BinderKindUtils::BoundObjectExpression: {
    retVal = handleObjectExpression(llvmArrayArgs, i, callExpression, arg,
                                    rhsValue, retFlag);
    break;
  }
  case BinderKindUtils::BoundBracketedExpression: {
    retVal = handleBracketExpression(llvmArrayArgs, i, callExpression, arg,
                                     rhsValue, retFlag);
    break;
  }
  case BinderKindUtils::CallExpression: {
    llvm::Value *value =
        _expressionGenerationFactory
            ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
            ->generateExpression(callExpression->getArgumentsRef()[i].get());
    llvm::Type *type =
        _codeGenerationContext->getValueStackHandler()->getLLVMType();

    if (llvm::isa<llvm::StructType>(type) || llvm::isa<llvm::ArrayType>(type)) {

      rhsValue = Builder->CreateAlloca(type, nullptr);
      Builder->CreateStore(Builder->CreateLoad(type, value), rhsValue);
    } else {

      BoundFunctionDeclaration *functionDeclaration =
          _codeGenerationContext
              ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
      if (functionDeclaration->getParametersRef()[i]->getHasAsKeyword()) {
        rhsValue = Builder->CreateLoad(
            type, _codeGenerationContext->getValueStackHandler()->getValue());
      } else {
        rhsValue = Builder->CreateAlloca(type, nullptr);
        Builder->CreateStore(value, rhsValue);
      }
    }
    _codeGenerationContext->getValueStackHandler()->popAll();
    break;
  }
  default: {
    retVal = handlePremitive(rhsValue, callExpression, i, llvmArrayArgs, arg,
                             retFlag);
    break;
  }
  }
  if (retFlag)
    return retVal;

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handlePremitive(
    llvm::Value *&rhsValue, BoundCallExpression *callExpression, uint64_t i,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    llvm::Argument *arg, bool &retFlag) {
  retFlag = true;

  _expressionGenerationFactory
      ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
      ->generateExpression(callExpression->getArgumentsRef()[i].get());
  BoundFunctionDeclaration *functionDeclaration =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];

  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();

  if (functionDeclaration->getParametersRef()[i]->getHasAsKeyword()) {

    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {
    rhsValue = Builder->CreateAlloca(rhsType, nullptr);
    Builder->CreateStore(
        _codeGenerationContext->getValueStackHandler()->getValue(), rhsValue);
  }
  _codeGenerationContext->getValueStackHandler()->popAll();

  // if (functionDeclaration->getParametersRef()[i]->getHasInOutKeyword()) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Type mismatch in '" + callExpression->getCallerNameRef() +
  //       "' function call expression , Expected 'VARIABLE' of type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[i]->getLLVMType()) +
  //       " in order to work with inout parameters but found a 'CONSTANT' of "
  //       "type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType));
  //   return nullptr;
  // }

  if (!_codeGenerationContext->getDynamicType()->isDyn(
          llvmArrayArgs[i]->getType()) &&
      llvmArrayArgs[i]->getLLVMType() != rhsType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected type " +
        Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
            llvmArrayArgs[i]->getLLVMType())) +
        " in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str()) + ", but found type " +
        Utils::CE(
            _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType)));
    return rhsValue;
  } else if (_codeGenerationContext->getDynamicType()->isDyn(
                 llvmArrayArgs[i]->getLLVMType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Dynamic type not supported in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str())

    );
    return rhsValue;
  }
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleBracketExpression(
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs, uint64_t i,
    BoundCallExpression *callExpression, llvm::Argument *arg,
    llvm::Value *&rhsValue, bool &retFlag) {
  retFlag = true;
  if (!llvmArrayArgs[i]->isPointerToArray()) {
    _codeGenerationContext->getLogger()->LogError(
        "You are passing Array to function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str()) + ", but it is not an Array");

    return nullptr;
  }

  // BoundFunctionDeclaration *functionDeclaration =
  //     _codeGenerationContext
  //         ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  // if (functionDeclaration->getParametersRef()[i]->getHasInOutKeyword()) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Type mismatch in '" + callExpression->getCallerNameRef() +
  //       "' function call expression , Expected 'VARIABLE' of type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[i]->getLLVMType()) +
  //       " in order to work with inout parameters but found a 'EXPRESSION' of
  //       " "type " + _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[i]->getLLVMType()));
  //   return nullptr;
  // }

  LLVMArrayType *llvmArrayType =
      static_cast<LLVMArrayType *>(llvmArrayArgs[i].get());

  auto contStrategy =
      std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
          _codeGenerationContext);

  contStrategy->generateCommonStatement(
      llvmArrayType->getArrayTypeExpression(), arg->getName().str(),
      callExpression->getArgumentsRef()[i].get());

  rhsValue = _codeGenerationContext->getAllocaChain()
                 ->getPtr(arg->getName().str())
                 .first;
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleObjectExpression(
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs, uint64_t i,
    BoundCallExpression *callExpression, llvm::Argument *arg,
    llvm::Value *&rhsValue, bool &retFlag) {
  retFlag = true;
  if (!llvmArrayArgs[i]->isPointerToObject()) {
    _codeGenerationContext->getLogger()->LogError(
        "You are passing Object to function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str()) + ", but it is not an Object");

    return nullptr;
  }

  LLVMObjectType *llvmObjectType =
      static_cast<LLVMObjectType *>(llvmArrayArgs[i].get());
  BoundFunctionDeclaration *functionDeclaration =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  // if (functionDeclaration->getParametersRef()[i]->getHasInOutKeyword()) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Type mismatch in '" + callExpression->getCallerNameRef() +
  //       "' function call expression , Expected 'VARIABLE' of type " +
  //       _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmArrayArgs[i]->getLLVMType()) +
  //       " in order to work with inout parameters but found an 'EXPRESSION' of
  //       " "type " + _codeGenerationContext->getMapper()->getLLVMTypeName(
  //           llvmObjectType->getLLVMType()));
  //   return nullptr;
  // }

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignExpGenStrat =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
      std::make_unique<ObjectExpressionGenerationStrategy>(
          _codeGenerationContext);

  std::string objectTypeName =
      llvmObjectType->getStructType()->getName().str().substr(
          0, llvmObjectType->getStructType()->getName().str().find('.'));
  objExpGenStrat->setTypeName(objectTypeName);
  if (_codeGenerationContext->_classTypes.find(objectTypeName) !=
      _codeGenerationContext->_classTypes.end()) {
    std::cout << objectTypeName << std::endl;
    llvm::StructType *classType =
        _codeGenerationContext->_classTypes[objectTypeName]->getClassType();
    auto fun = TheModule->getFunction(INNERS::FUNCTIONS::MALLOC);

    llvm::CallInst *malloc_call = Builder->CreateCall(
        fun, llvm::ConstantInt::get(
                 llvm::Type::getInt64Ty(*TheContext),
                 _codeGenerationContext->getMapper()->getSizeOf(classType)));
    malloc_call->setTailCall(false);

    // Cast the result of 'malloc' to a pointer to int
    llvm::Value *intPtr = Builder->CreateBitCast(
        malloc_call,
        llvm::PointerType::getUnqual(llvm::Type::getInt32Ty(*TheContext)));
    _codeGenerationContext->getAllocaChain()->setPtr(objectTypeName,
                                                     {intPtr, classType});
    assignExpGenStrat->initDefaultValue(classType, intPtr);

    objExpGenStrat->setVariable(intPtr);
    objExpGenStrat->generateGlobalExpression(
        callExpression->getArgumentsRef()[i].get());
  } else {
    // if (_isGlobal) {
    //   rhsValue = new llvm::GlobalVariable(
    //       *TheModule, llvmObjectType->getStructType(), false,
    //       llvm::GlobalValue::ExternalLinkage,
    //       llvm::Constant::getNullValue(llvmObjectType->getStructType()));

    //   assignExpGenStrat->initDefaultValue(llvmObjectType->getStructType(),
    //                                       rhsValue);
    //   objExpGenStrat->setVariable(rhsValue);
    //   objExpGenStrat->generateGlobalExpression(
    //       callExpression->getArgumentsRef()[i].get());

    // } else {
    rhsValue = Builder->CreateAlloca(llvmObjectType->getStructType(), nullptr);
    _codeGenerationContext->getAllocaChain()->setPtr(
        rhsValue->getName().str(), {rhsValue, rhsValue->getType()});

    assignExpGenStrat->initDefaultValue(llvmObjectType->getStructType(),
                                        rhsValue);

    objExpGenStrat->setVariable(rhsValue);
    objExpGenStrat->generateExpression(
        callExpression->getArgumentsRef()[i].get());
    // }
  }
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleVariableExpression(
    llvm::Value *&rhsValue, BoundCallExpression *callExpression, uint64_t i,
    llvm::FunctionType *functionType,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    llvm::Argument *arg, bool &retFlag) {
  retFlag = true;

  _expressionGenerationFactory
      ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
      ->generateExpression(callExpression->getArgumentsRef()[i].get());
  rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();

  BoundFunctionDeclaration *functionDeclaration =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  if (functionDeclaration->getParametersRef()[i]->getHasAsKeyword()) {

    rhsValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  } else {

    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  }

  llvm ::Type *varType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  _codeGenerationContext->getValueStackHandler()->popAll();
  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(
          callExpression->getArgumentsRef()[i].get());

  if (!variableExpression) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function Expected " +
        std::to_string(functionType->getNumParams()) + " arguments but got " +
        std::to_string(llvmArrayArgs.size()));
    return nullptr;
  }

  if (llvmArrayArgs[i]->isPointerToArray() &&
      variableExpression->getVariableTypeRef()->getSyntaxType() !=
          SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected Array in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str()) + ", but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            variableExpression->getVariableTypeRef()->getSyntaxType()));
    return nullptr;
  }

  if (llvmArrayArgs[i]->isPointerToObject() &&
      variableExpression->getVariableTypeRef()->getSyntaxType() !=
          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected Object in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str()) + ", but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            variableExpression->getVariableTypeRef()->getSyntaxType()));
    return nullptr;
  }

  if (llvmArrayArgs[i]->isPointerToArray()) {
    BoundArrayTypeExpression *arrayTypeExpression =
        static_cast<BoundArrayTypeExpression *>(
            variableExpression->getVariableTypeRef());

    llvm::Type *varElementType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            arrayTypeExpression->getElementType());
    LLVMArrayType *llvmArrayType =
        static_cast<LLVMArrayType *>(llvmArrayArgs[i].get());
    llvm::ArrayType *arrayType =
        static_cast<llvm::ArrayType *>(llvmArrayType->getElementType());

    uint64_t arraySize = arrayType->getNumElements();

    llvm::Type *_res = isGlobalArray(rhsValue);
    _res = _res ? _res : isLocalArray(rhsValue);

    if (!_res) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Array of " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmArrayType->getArrayElementType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          Utils::CE(arg->getName().str()) + ", but found " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType()));
      return nullptr;
    }
    if (varElementType != llvmArrayType->getArrayElementType()) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Array of " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmArrayType->getArrayElementType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          Utils::CE(arg->getName().str()) + ", but found Array of " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              varElementType)));

      return nullptr;
    }

    if (arrayTypeExpression->getDimensions().size() !=
        llvmArrayType->getDimensions().size()) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Array of size " +
          std::to_string(llvmArrayType->getDimensions().size()) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          Utils::CE(arg->getName().str()) + ", but found Array of size " +
          std::to_string(arrayTypeExpression->getDimensions().size()));
      return nullptr;
    }
    std::unique_ptr<LiteralExpressionGenerationStrategy>
        literalExpressionGenerationStrategy =
            std::make_unique<LiteralExpressionGenerationStrategy>(
                _codeGenerationContext);

    for (int64_t k = 0; k < llvmArrayType->getDimensions().size(); k++) {
      llvm::Value *arraySize =
          literalExpressionGenerationStrategy->generateExpression(
              arrayTypeExpression->getDimensions()[k].get());

      if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
        _codeGenerationContext->getLogger()->LogError(
            "Array size must be a constant integer");
        return nullptr;
      }

      int64_t size = llvm::cast<llvm::ConstantInt>(arraySize)->getSExtValue();
      if (size != llvmArrayType->getDimensions()[k]) {
        _codeGenerationContext->getLogger()->LogError(
            "Expected Array's Dimension " + std::to_string(k + 1) +
            " size to be " + std::to_string(llvmArrayType->getDimensions()[k]) +
            " in function call expression " +
            Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
            Utils::CE(arg->getName().str()) + ", but found " +
            std::to_string(size));

        return nullptr;
      }
    }
  } else if (llvmArrayArgs[i]->isPointerToObject()) {
    BoundObjectTypeExpression *objTypeExpr =
        static_cast<BoundObjectTypeExpression *>(
            variableExpression->getVariableTypeRef());

    LLVMObjectType *llvmObjType =
        static_cast<LLVMObjectType *>(llvmArrayArgs[i].get());
    std::string structTypeName =
        llvmObjType->getStructType()->getName().str().substr(
            0, llvmObjType->getStructType()->getName().str().find('.'));

    if (_codeGenerationContext->_classTypes.find(structTypeName) !=
        _codeGenerationContext->_classTypes.end()) {

      if (!_codeGenerationContext
               ->_classTypes[objTypeExpr->getTypeName().substr(
                   0, objTypeExpr->getTypeName().find("."))]
               ->isChildOf(structTypeName)) {

        _codeGenerationContext->getLogger()->LogError(
            "Expected Object of type " + Utils::CE(structTypeName) +
            " in function call expression " +
            Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
            ", but found object of type " +
            Utils::CE(objTypeExpr->getTypeName().substr(
                0, objTypeExpr->getTypeName().find("."))));
        return nullptr;
      }

    } else if (objTypeExpr->getTypeName() != structTypeName) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Object of type " + Utils::CE(structTypeName) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          ", but found object of type " +
          Utils::CE(objTypeExpr->getTypeName().substr(
              0, objTypeExpr->getTypeName().find("."))));
      return nullptr;
    }

    // std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
    //     std::make_unique<ObjectExpressionGenerationStrategy>(
    //         _codeGenerationContext);

    // llvm::Value *structPtr = nullptr;

    // if (_isGlobal) {
    //   structPtr = new llvm::GlobalVariable(
    //       *TheModule, llvmObjType->getStructType(), false,
    //       llvm::GlobalValue::ExternalLinkage,
    //       llvm::Constant::getNullValue(llvmObjType->getStructType()));

    // } else {
    //   structPtr =
    //       Builder->CreateAlloca(llvmObjType->getStructType(), nullptr);
    //   _codeGenerationContext->getAllocaChain()->setAllocaInst(
    //       structPtr->getName().str(), (llvm::AllocaInst *)structPtr);
    // }

    // objExpGenStrat->generateVariable(structPtr,
    // structType->getName().str(),
    //                                  rhsValue, false);

    // rhsValue = structPtr;

  } else {
    if (llvmArrayArgs[i]->getType() != rhsValue->getType()) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected type " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              llvmArrayArgs[i]->getType())) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          Utils::CE(arg->getName().str()) + ", but found type " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType())));
      return nullptr;
    }
  }
  retFlag = false;
  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::handleIndexExpression(
    llvm::Value *&rhsValue, BoundCallExpression *callExpression, uint64_t i,
    llvm::FunctionType *functionType,
    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
    llvm::Argument *arg, bool &retFlag) {
  retFlag = false;

  _expressionGenerationFactory
      ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
      ->generateExpression(callExpression->getArgumentsRef()[i].get());
  rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  BoundFunctionDeclaration *functionDeclaration =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];
  if (functionDeclaration->getParametersRef()[i]->getHasAsKeyword()) {

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
                                                 const std::string &unitName) {
  Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                      {getUnit(unit, unitName), Builder->getInt1(false)});
}

llvm::Value *
CallExpressionGenerationStrategy::getUnit(const std::string &unit,
                                          const std::string &unitName) {
  llvm::GlobalVariable *variable = TheModule->getGlobalVariable(unitName);
  if (!variable) {
    // The global variable doesn't exist
    llvm::Constant *initializer = Builder->CreateGlobalStringPtr(unit);
    variable = new llvm::GlobalVariable(
        /*Module=*/*TheModule,
        /*Type=*/initializer->getType(),
        /*isConstant=*/true,
        /*Linkage=*/llvm::GlobalValue::PrivateLinkage,
        /*Initializer=*/initializer,
        /*Name=*/unitName);
  }

  return Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), variable);
}

void CallExpressionGenerationStrategy::printString(llvm::Value *value,
                                                   llvm::Type *type) {
  printUnit("'", "'");
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::BasicBlock *isNullBlock = llvm::BasicBlock::Create(
      *TheContext, "IsNull", currentBlock->getParent());
  llvm::BasicBlock *endBlock =
      llvm::BasicBlock::Create(*TheContext, "End", currentBlock->getParent());
  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(*TheContext, "Merge", currentBlock->getParent());

  // Create a null pointer constant of the same type as yourValue
  llvm::Constant *nullPtr = llvm::Constant::getNullValue(type);

  // Compare yourValue with the null pointer constant
  llvm::Value *isNullValue = Builder->CreateICmpNE(value, nullPtr);

  Builder->CreateCondBr(isNullValue, endBlock, isNullBlock);

  Builder->SetInsertPoint(isNullBlock);

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(endBlock);

  Builder->CreateCall(
      TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
      {_stringTypeConverter->convertExplicit(value), Builder->getInt1(false)});

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(mergeBlock);
  printUnit("'", "'");
}

llvm::Value *CallExpressionGenerationStrategy::printArrayAtom(
    llvm::ArrayType *&arrayType, llvm::Value *&v,
    const std::vector<uint64_t> &actualSizes, llvm::Type *&elementType) {
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  std::vector<std::vector<llvm::BasicBlock *>> loopBlocks;
  std::vector<llvm::AllocaInst *> indices;

  for (int i = 0; i < actualSizes.size(); i++) {
    std::vector<llvm::BasicBlock *> blocks = {
        llvm::BasicBlock::Create(*TheContext, "FillExpr.loopStart",
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext, "FillExpr.loopCmp",
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext, "FillExpr.loopBody",
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext, "FillExpr.loopEnd",
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext, "FillExpr.print.lobby",
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext, "FillExpr.stage",
                                 currentBlock->getParent())};

    llvm::AllocaInst *index = Builder->CreateAlloca(Builder->getInt32Ty());
    indices.push_back(index);
    loopBlocks.push_back(blocks);
  }

  llvm::AllocaInst *numberOfElementsFilled =
      Builder->CreateAlloca(Builder->getInt32Ty());
  Builder->CreateStore(Builder->getInt32(0), numberOfElementsFilled);

  llvm::BasicBlock *exit = llvm::BasicBlock::Create(
      *TheContext, "FillExpr.exit", currentBlock->getParent());

  Builder->CreateBr(loopBlocks[0][0]);

  for (int i = 0; i < actualSizes.size(); i++) {
    // start
    Builder->SetInsertPoint(loopBlocks[i][0]);
    Builder->CreateStore(Builder->getInt32(0), indices[i]);
    printUnit("[", "openBracket");
    Builder->CreateBr(loopBlocks[i][1]);

    // cmp
    Builder->SetInsertPoint(loopBlocks[i][1]);
    llvm::Value *currentIndex =
        Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
    llvm::Value *isLessThanActualSize =
        Builder->CreateICmpSLT(currentIndex, Builder->getInt32(actualSizes[i]));
    //!
    llvm::Value *isGreaterThanZero =
        Builder->CreateICmpSGT(currentIndex, Builder->getInt32(0));
    llvm::Value *showPrintLobby =
        Builder->CreateAnd(isLessThanActualSize, isGreaterThanZero);
    //!

    Builder->CreateCondBr(showPrintLobby, loopBlocks[i][4], loopBlocks[i][5]);

    //? print Lobby
    Builder->SetInsertPoint(loopBlocks[i][4]);
    printUnit(", ", "comma");
    Builder->CreateBr(loopBlocks[i][2]);
    //?

    //! Stage
    Builder->SetInsertPoint(loopBlocks[i][5]);
    llvm::Value *currentIndex_stage =
        Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
    llvm::Value *isLessThanActualSize_Stage = Builder->CreateICmpSLT(
        currentIndex_stage, Builder->getInt32(actualSizes[i]));
    Builder->CreateCondBr(isLessThanActualSize_Stage, loopBlocks[i][2],
                          loopBlocks[i][3]);

    // body
    Builder->SetInsertPoint(loopBlocks[i][2]);
    if (i == actualSizes.size() - 1) {
      std::vector<llvm::Value *> indexList = {Builder->getInt32(0)};

      for (int j = 0; j < actualSizes.size(); j++) {
        indexList.push_back(
            Builder->CreateLoad(Builder->getInt32Ty(), indices[j]));
      }

      llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indexList);

      //! Printing Starts
      llvm::Value *innerValue = nullptr;
      // Untyped Container Element
      if (_codeGenerationContext->getDynamicType()->isDyn(elementType)) {
        innerValue =
            _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
                elementPtr, v->getName().str());
      } else if (llvm::isa<llvm::StructType>(elementType)) {

        printObject(elementPtr, llvm::cast<llvm::StructType>(elementType));
      } else {
        // Typed Container Element
        innerValue = Builder->CreateLoad(elementType, elementPtr);

        if (innerValue->getType()->isPointerTy()) {
          printString(innerValue, elementType);
        } else

          Builder->CreateCall(
              TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
              {_stringTypeConverter->convertExplicit(innerValue),
               Builder->getInt1(false)});
      }

      //! Printing Ends
      llvm::Value *_currentIndex =
          Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
      llvm::Value *nextIndex =
          Builder->CreateAdd(_currentIndex, Builder->getInt32(1));
      Builder->CreateStore(nextIndex, indices[i]);

      Builder->CreateBr(loopBlocks[i][1]);
    } else {
      Builder->CreateBr(loopBlocks[i + 1][0]);
    }

    // end
    Builder->SetInsertPoint(loopBlocks[i][3]);
    if (i != 0) {
      llvm::Value *_currentIndex =
          Builder->CreateLoad(Builder->getInt32Ty(), indices[i - 1]);
      llvm::Value *nextIndex =
          Builder->CreateAdd(_currentIndex, Builder->getInt32(1));
      Builder->CreateStore(nextIndex, indices[i - 1]);

      printUnit("]", "closeBracket");
      Builder->CreateBr(loopBlocks[i - 1][1]);
    } else {
      printUnit("]", "closeBracket");
      Builder->CreateBr(exit);
    }
  }

  Builder->SetInsertPoint(exit);

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::printArray(
    llvm::ArrayType *arrayType, llvm::Type *elementType, llvm::Value *v) {
  std::vector<uint64_t> sizes;
  _codeGenerationContext->getArraySizeMetadata(v, sizes);
  llvm::Type *elt = _codeGenerationContext->getArrayElementTypeMetadata(v);
  printArrayAtom(arrayType, v, sizes, elt);

  return nullptr;
}

llvm::Value *
CallExpressionGenerationStrategy::printObject(llvm::Value *outerElementPtr,
                                              llvm::StructType *parObjType) {
  printUnit("{ ", "{ ");

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          parObjType->getStructName().str().substr(
              0, parObjType->getStructName().str().find(".")));

  if (!boundCustomTypeStatement) {

    if (_codeGenerationContext->_classTypes.find(
            parObjType->getStructName().str().substr(
                0, parObjType->getStructName().str().find("."))) !=
        _codeGenerationContext->_classTypes.end()) {
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

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string typeName = std::any_cast<std::string>(bLE->getValue());
    std::string propertyKey = std::any_cast<std::string>(bLE->getValue());

    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
        {Builder->CreateGlobalStringPtr(propertyKey), Builder->getInt1(false)});
    printUnit(" : ", " : ");
    std::string key =
        boundCustomTypeStatement->getTypeNameAsString().substr(
            0, boundCustomTypeStatement->getTypeNameAsString().find(".")) +
        "." + propertyKey;
    size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

    if (index == -1) {
      _codeGenerationContext->getLogger()->LogError(
          "Variable " + key + " not found in variable expression ");

      return nullptr;
    }

    llvm::Value *innerElementPtr =
        Builder->CreateStructGEP(parObjType, outerElementPtr, i);

    llvm::Type *type = parObjType->getElementType(i);
    if (bTE->getSyntaxType() == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
      llvm::StructType *structType = llvm::cast<llvm::StructType>(type);

      printObject(innerElementPtr, structType);
    } else if (bTE->getSyntaxType() ==
               SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
      llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
      llvm::Type *elementType = arrayType->getElementType();
      llvm::Type *type = arrayType;
      std::vector<uint64_t> sizes;
      _codeGenerationContext->createArraySizesAndArrayElementType(sizes, type);
      printArrayAtom(arrayType, innerElementPtr, sizes, type);
    } else {
      llvm::LoadInst *loaded = Builder->CreateLoad(type, innerElementPtr);

      llvm::Value *loadedVal = llvm::cast<llvm::Value>(loaded);
      if (loaded->getType()->isPointerTy()) {
        printString(loadedVal, type);
      } else {
        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                            {_stringTypeConverter->convertExplicit(loadedVal),
                             Builder->getInt1(false)});
      }
    }
    if (i != boundCustomTypeStatement->getKeyPairs().size() - 1)
      printUnit(", ", " , ");

    i++;
  }

  printUnit(" }", "}");

  return nullptr;
}