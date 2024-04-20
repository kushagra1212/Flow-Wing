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
    if (arguments_size == 1) {
      llvm::Value *value =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      if (!value) {
        return nullptr;
      }

      if (llvm::isa<llvm::CallInst>(value)) {
        llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(value);
        auto *calledFunction = calledInst->getCalledFunction();
        llvm::ArrayType *arrayType = nullptr;
        llvm::Type *elementType = nullptr;
        std::vector<uint64_t> actualSizes;
        _codeGenerationContext->getRetrunedArrayType(calledFunction, arrayType,
                                                     elementType, actualSizes);

        if (arrayType != nullptr) {
          llvm::LoadInst *loaded = Builder->CreateLoad(arrayType, calledInst);
          llvm::Value *localVariable =
              Builder->CreateAlloca(arrayType, nullptr);

          // Store the result of the call in the local variable
          Builder->CreateStore(loaded, localVariable);

          printArrayAtom(arrayType, localVariable, actualSizes, elementType);
          return nullptr;
        } else {
          llvm::StructType *structType = nullptr;
          _codeGenerationContext->getReturnedObjectType(calledFunction,
                                                        structType);

          if (structType != nullptr) {
            llvm::LoadInst *loaded =
                Builder->CreateLoad(structType, calledInst);
            llvm::Value *localVariable =
                Builder->CreateAlloca(structType, nullptr);

            // Store the result of the call in the local variable
            Builder->CreateStore(loaded, localVariable);
            return printObject(localVariable, structType);
          }
        }
      }

      if (_codeGenerationContext->getValueStackHandler()->isStructType() &&
          llvm::isa<llvm::PointerType>(value->getType())) {
        std::string typeName =
            _codeGenerationContext->getValueStackHandler()->getTypeName();
        _codeGenerationContext->getValueStackHandler()->popAll();

        return printObject(
            value, _codeGenerationContext->getTypeChain()->getType(typeName));
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
        while (llvm::ArrayType *arrayType =
                   llvm::dyn_cast<llvm::ArrayType>(type)) {
          sizes.push_back(arrayType->getNumElements());
          type = arrayType->getElementType();
        }
        return printArrayAtom(arrayType, innerElementPtr, sizes, type);
      }

      if (llvm::isa<llvm::ArrayType>(value->getType())) {
        llvm::ArrayType *arrayType =
            llvm::cast<llvm::ArrayType>(value->getType());
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

      if (_codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
              value->getType()) != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                            {_stringTypeConverter->convertExplicit(value),
                             Builder->getInt1(false)});
        return nullptr;
      }

      return nullptr;
    }
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

llvm::Value *CallExpressionGenerationStrategy::userDefinedFunctionCall(
    BoundCallExpression *callExpression) {
  std::size_t arguments_size = callExpression->getArgumentsRef().size();

  llvm::Function *calleeFunction =
      TheModule->getFunction(callExpression->getCallerNameRef());

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  BoundFunctionDeclaration *definedFunction =
      _codeGenerationContext
          ->getBoundedUserFunctions()[callExpression->getCallerNameRef()];

  if (!calleeFunction &&
      !_codeGenerationContext
           ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()]) {
    _codeGenerationContext
        ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 1;

    std::vector<llvm::Value *> args;

    for (int i = 0; i < arguments_size; i++) {
      llvm::Value *arg = nullptr;

      arg =
          _expressionGenerationFactory
              ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[i].get());

      if (!arg) {
        _codeGenerationContext->getLogger()->LogError(
            "Argument not found in function call expression ");
        return nullptr;
      }

      args.push_back(arg);
    }

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

  calleeFunction = TheModule->getFunction(callExpression->getCallerNameRef());

  _codeGenerationContext
      ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 0;

  llvm::FunctionType *functionType = calleeFunction->getFunctionType();

  const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(
          callExpression->getCallerNameRef());

  if (functionType->getNumParams() != llvmArrayArgs.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function" + "Expected " +
        std::to_string(functionType->getNumParams()) + " arguments but got " +
        std::to_string(llvmArrayArgs.size()));
    return nullptr;
  }
  llvm::Value *rhsValue = nullptr;

  for (uint64_t i = 0; i < llvmArrayArgs.size(); i++) {
    bool retFlag;
    llvm::Value *retVal =
        handleExpression(calleeFunction, i, callExpression, rhsValue,
                         functionType, llvmArrayArgs, retFlag);
    if (retFlag)
      return retVal;
    functionArgs.push_back(rhsValue);
  }

  // // Callefunction param types and args check for type are same or not
  // // Meata data
  // for (unsigned i = 0; i < calleeFunction->arg_size(); ++i) {
  //   // Create the metadata key that includes the argument index
  //   std::string argKey = "argInfo" + std::to_string(i);
  //   llvm::Value *argValue = calleeFunction->getArg(i);

  //   // Get the metadata
  //   llvm::MDNode *metadata = calleeFunction->getMetadata(argKey);
  //   if (metadata) {
  //     // If the metadata exists,
  //     llvm::MDString *argInfoMD =
  //         llvm::cast<llvm::MDString>(metadata->getOperand(0));
  //     std::vector<std::string> vars;
  //     Utils::split(argInfoMD->getString().str(), ":", vars);

  //     if (vars.size() >= 4 && vars[1] == "ay") {
  //       llvm::Type *_res = isGlobalArray(args[i]);
  //       _res = _res ? _res : isLocalArray(args[i]);

  //       if (!_res) {
  //         _codeGenerationContext->getLogger()->LogError(
  //             "Expected Array of " + Utils::CE(vars[2]) +
  //             " in function call expression " +
  //             Utils::CE(callExpression->getCallerNameRef()) + " as parameter
  //             " + Utils::CE(argValue->getName().str()) + ", but found " +
  //             _codeGenerationContext->getMapper()->getLLVMTypeName(
  //                 args[i]->getType()));
  //         return nullptr;
  //       }
  //       llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(_res);

  //       llvm::Type *argArrayElementType =
  //           _codeGenerationContext->getArrayElementTypeMetadata(args[i]);

  //       std::vector<size_t> argArraySizes;
  //       _codeGenerationContext->getArraySizeMetadata(args[i], argArraySizes);

  //       std::vector<size_t> paramArraySizes;

  //       for (int j = 4; j < vars.size(); j++) {
  //         paramArraySizes.push_back(std::stoll(vars[j]));
  //       }

  //       if (paramArraySizes.size() != argArraySizes.size()) {
  //         _codeGenerationContext->getLogger()->LogError(
  //             "Expected Array of Dimension " +
  //             std::to_string(paramArraySizes.size()) +
  //             " in function call expression " +
  //             Utils::CE(callExpression->getCallerNameRef()) + " as parameter
  //             " + Utils::CE(argValue->getName().str()) +
  //             ", but found Array of Dimension " +
  //             std::to_string(argArraySizes.size()));

  //         return nullptr;
  //       }

  //       for (int j = 0; j < paramArraySizes.size(); j++) {
  //         if (paramArraySizes[j] != argArraySizes[j]) {
  //           _codeGenerationContext->getLogger()->LogError(
  //               "Expected Array's Dimension " + std::to_string(j) +
  //               " size to be " + std::to_string(paramArraySizes[j]) +
  //               " in function call expression " +
  //               Utils::CE(callExpression->getCallerNameRef()) +
  //               " as parameter " + Utils::CE(argValue->getName().str()) +
  //               ", but found " + std::to_string(argArraySizes[j]));

  //           return nullptr;
  //         }
  //       }

  //       if (vars[2] != _codeGenerationContext->getMapper()->getLLVMTypeName(
  //                          argArrayElementType)) {
  //         _codeGenerationContext->getLogger()->LogError(
  //             "Expected Array of " + Utils::CE(vars[2]) +
  //             " in function call expression " +
  //             Utils::CE(callExpression->getCallerNameRef()) + " as parameter
  //             " + Utils::CE(argValue->getName().str()) + ", but found Array
  //             of " +
  //             Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
  //                 argArrayElementType)));

  //         return nullptr;
  //       }

  //     } else if (vars.size() == 3 && vars[0] == "obj") {
  //       std::string typeName = vars[2];
  //     } else {
  //       if (_codeGenerationContext->getDynamicType()->isDyn(
  //               args[i]->getType()) &&
  //           vars[2] != _codeGenerationContext->getMapper()->getLLVMTypeName(
  //                          args[i]->getType())) {
  //         _codeGenerationContext->getLogger()->LogError(
  //             "Argument Type " +
  //             _codeGenerationContext->getMapper()->getLLVMTypeName(
  //                 args[i]->getType()) +
  //             " does not match with " + vars[2] + " for parameter " +
  //             Utils::CE(argValue->getName().str()));
  //         return nullptr;
  //       }
  //     }
  //   }
  //   // END
  // }

  llvm::Value *callIn = Builder->CreateCall(calleeFunction, functionArgs);

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

  _codeGenerationContext->getValueStackHandler()->push(
      "", callIn, "primitive", calleeFunction->getReturnType());
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
  case BinderKindUtils::VariableExpression: {
    retVal = handleVariableExpression(rhsValue, callExpression, i, functionType,
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
  rhsValue =
      _expressionGenerationFactory
          ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
          ->generateExpression(callExpression->getArgumentsRef()[i].get());

  if (!_codeGenerationContext->getDynamicType()->isDyn(
          llvmArrayArgs[i]->getType()) &&
      llvmArrayArgs[i]->getType() != rhsValue->getType()) {
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
  } else if (_codeGenerationContext->getDynamicType()->isDyn(
                 llvmArrayArgs[i]->getType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Dynamic type not supported in function call expression " +
        Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
        Utils::CE(arg->getName().str())

    );
    return nullptr;
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

  LLVMArrayType *llvmArrayType =
      static_cast<LLVMArrayType *>(llvmArrayArgs[i].get());

  auto contStrategy =
      std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
          _codeGenerationContext);

  contStrategy->generateCommonStatement(
      llvmArrayType->getArrayTypeExpression(), arg->getName().str(),
      callExpression->getArgumentsRef()[i].get());

  rhsValue = _codeGenerationContext->getAllocaChain()->getAllocaInst(
      arg->getName().str());
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

  std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
      std::make_unique<ObjectExpressionGenerationStrategy>(
          _codeGenerationContext);
  objExpGenStrat->setTypeName(llvmObjectType->getStructType()->getName().str());
  if (_isGlobal) {
    rhsValue = new llvm::GlobalVariable(
        *TheModule, llvmObjectType->getStructType(), false,
        llvm::GlobalValue::ExternalLinkage,
        llvm::Constant::getNullValue(llvmObjectType->getStructType()));

    objExpGenStrat->setVariable(rhsValue);
    objExpGenStrat->generateGlobalExpression(
        callExpression->getArgumentsRef()[i].get());

  } else {
    rhsValue = Builder->CreateAlloca(llvmObjectType->getStructType(), nullptr);
    _codeGenerationContext->getAllocaChain()->setAllocaInst(
        rhsValue->getName().str(), (llvm::AllocaInst *)rhsValue);
    objExpGenStrat->setVariable(rhsValue);
    objExpGenStrat->generateExpression(
        callExpression->getArgumentsRef()[i].get());
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
  rhsValue =
      _expressionGenerationFactory
          ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
          ->generateExpression(callExpression->getArgumentsRef()[i].get());

  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(
          callExpression->getArgumentsRef()[i].get());

  if (!variableExpression) {
    _codeGenerationContext->getLogger()->LogError(
        "Function call argument mismatch in " +
        callExpression->getCallerNameRef() + " function" + "Expected " +
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

    if (objTypeExpr->getTypeName() !=
        llvmObjType->getStructType()->getName().str()) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected Object of type " + Utils::CE(objTypeExpr->getTypeName()) +
          " in function call expression " +
          Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
          Utils::CE(arg->getName().str()) + ", but found object of type " +
          Utils::CE(llvmObjType->getStructType()->getName().str()));
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
        /*Linkage=*/llvm::GlobalValue::ExternalLinkage,
        /*Initializer=*/initializer,
        /*Name=*/unitName);
  }

  return Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), variable);
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
                elementPtr, FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX +
                                v->getName().str());
      } else if (llvm::isa<llvm::StructType>(arrayType->getElementType())) {

        printObject(elementPtr,
                    llvm::cast<llvm::StructType>(arrayType->getElementType()));
      } else {
        // Typed Container Element
        innerValue = Builder->CreateLoad(elementType, elementPtr);
        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
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
          parObjType->getStructName().str());

  uint64_t i = 0;

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string typeName = std::any_cast<std::string>(bLE->getValue());
    std::string propertyKey = std::any_cast<std::string>(bLE->getValue());

    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
        {Builder->CreateGlobalStringPtr(propertyKey), Builder->getInt1(false)});
    printUnit(" : ", " : ");
    std::string key =
        boundCustomTypeStatement->getTypeNameAsString() + "." + propertyKey;
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
        printUnit("'", "'");
        llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
        llvm::BasicBlock *isNullBlock = llvm::BasicBlock::Create(
            *TheContext, "IsNull", currentBlock->getParent());
        llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(
            *TheContext, "End", currentBlock->getParent());
        llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
            *TheContext, "Merge", currentBlock->getParent());

        // Create a null pointer constant of the same type as yourValue
        llvm::Constant *nullPtr = llvm::Constant::getNullValue(type);

        // Compare yourValue with the null pointer constant
        llvm::Value *isNullValue = Builder->CreateICmpNE(loaded, nullPtr);

        Builder->CreateCondBr(isNullValue, endBlock, isNullBlock);

        Builder->SetInsertPoint(isNullBlock);

        Builder->CreateBr(mergeBlock);

        Builder->SetInsertPoint(endBlock);

        Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                            {_stringTypeConverter->convertExplicit(loadedVal),
                             Builder->getInt1(false)});

        Builder->CreateBr(mergeBlock);

        Builder->SetInsertPoint(mergeBlock);
        printUnit("'", "'");

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