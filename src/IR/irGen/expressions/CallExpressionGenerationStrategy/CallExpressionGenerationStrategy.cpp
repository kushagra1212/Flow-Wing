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
  } else if (callExpression->getCallerNameRef() == FW::BI::FUNCTION::Input) {
    if (arguments_size == 0) {

      llvm::ArrayRef<llvm::Value *> Args = {};

      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
    } else if (arguments_size == 1) {

      llvm::Value *val =
          _expressionGenerationFactory
              ->createStrategy(
                  callExpression->getArgumentsRef()[0].get()->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[0].get());

      Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                          {_stringTypeConverter->convertExplicit(val),
                           Builder->getInt1(false)});

      llvm::ArrayRef<llvm::Value *> Args = {};
      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
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

  std::vector<llvm::Value *> args;

  for (int i = 0; i < arguments_size; i++) {

    llvm::Value *arg = nullptr;

    arg = _expressionGenerationFactory
              ->createStrategy(callExpression->getArgumentsRef()[i]->getKind())
              ->generateExpression(callExpression->getArgumentsRef()[i].get());

    if (!arg) {
      _codeGenerationContext->getLogger()->LogError(
          "Argument not found in function call expression ");
      return nullptr;
    }
    args.push_back(arg);
  }

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

    std::unique_ptr<FunctionStatementGenerationStrategy> fgst =
        std::make_unique<FunctionStatementGenerationStrategy>(
            _codeGenerationContext);

    fgst->generateStatementOnFly(definedFunction, args);

    Builder->SetInsertPoint(currentBlock);
  }

  calleeFunction = TheModule->getFunction(callExpression->getCallerNameRef());

  _codeGenerationContext
      ->getRecursiveFunctionsMap()[callExpression->getCallerNameRef()] = 0;

  llvm::FunctionType *functionType = calleeFunction->getFunctionType();
  std::vector<llvm::Type *> paramTypes(functionType->param_begin(),
                                       functionType->param_end());

  // Callefunction param types and args check for type are same or not
  // Meata data
  for (unsigned i = 0; i < calleeFunction->arg_size(); ++i) {
    // Create the metadata key that includes the argument index
    std::string argKey = "argInfo" + std::to_string(i);

    // Get the metadata
    llvm::MDNode *metadata = calleeFunction->getMetadata(argKey);
    if (metadata) {
      // If the metadata exists,
      llvm::MDString *argInfoMD =
          llvm::cast<llvm::MDString>(metadata->getOperand(0));
      std::vector<std::string> vars;
      Utils::split(argInfoMD->getString().str(), ":", vars);

      if (vars[2] == "Array") {

        llvm::Type *_res = isGlobalArray(args[i]);
        _res = _res ? _res : isLocalArray(args[i]);

        if (!_res) {
          _codeGenerationContext->getLogger()->LogError(
              "Expected Array of " + Utils::CE(vars[3]) +
              " in function call expression " +
              Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
              Utils::CE(vars[0]) + ", but found " +
              _codeGenerationContext->getMapper()->getLLVMTypeName(
                  args[i]->getType()));
          return nullptr;
        }
        llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(_res);

        if (vars[3] != _codeGenerationContext->getMapper()->getLLVMTypeName(
                           arrayType->getElementType())) {
          _codeGenerationContext->getLogger()->LogError(
              "Expected Array of " + Utils::CE(vars[3]) +
              " in function call expression " +
              Utils::CE(callExpression->getCallerNameRef()) + " as parameter " +
              Utils::CE(vars[0]) + ", but found Array of " +
              Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
                  arrayType->getElementType())));

          return nullptr;
        }

      } else {
        if (_codeGenerationContext->getDynamicType()->isDyn(
                args[i]->getType()) &&
            vars[2] != _codeGenerationContext->getMapper()->getLLVMTypeName(
                           args[i]->getType())) {
          _codeGenerationContext->getLogger()->LogError(
              "Argument Type " +
              _codeGenerationContext->getMapper()->getLLVMTypeName(
                  args[i]->getType()) +
              " does not match with " + vars[2] + " for parameter " + vars[0]);
          return nullptr;
        }
      }
    }
    // END
  }

  return Builder->CreateCall(calleeFunction, args);
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
    // The global variable doesn't exist, so create it
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
    const std::vector<size_t> &sizes, std::vector<llvm::Value *> &indices,
    int64_t index, llvm::Type *&elementType) {

  if (index < sizes.size()) {

    printUnit("[", "openBracket");
    for (int64_t i = 0; i < sizes[index]; i++) {
      indices.push_back(Builder->getInt32(i));

      printArrayAtom(arrayType, v, sizes, indices, index + 1, elementType);

      if (i != sizes[index] - 1)
        printUnit(", ", "comma");
      indices.pop_back();
    }
    printUnit("]", "closeBracket");
    return nullptr;
  }

  llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);
  llvm::Value *innerValue = nullptr;

  // Untyped Container Element
  if (_codeGenerationContext->getDynamicType()->isDyn(elementType)) {

    innerValue =
        _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
            elementPtr, FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX +
                            v->getName().str() + "_" + std::to_string(index));
  } else {
    // Typed Container Element
    innerValue = Builder->CreateLoad(elementType, elementPtr);
  }
  Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
                      {_stringTypeConverter->convertExplicit(innerValue),
                       Builder->getInt1(false)});

  // llvm::Value *size = Builder->getInt32(sizes[index]);

  // llvm::Value *arrayPtr = v;

  // std::string arrayName = v->getName().str();

  // llvm::Value *commaPtr = Builder->CreateGlobalStringPtr(", ");

  // Builder->CreateCall(
  //     TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
  //     {Builder->CreateGlobalStringPtr("["), Builder->getInt1(false)});

  // llvm::Function *TheFunction = Builder->GetInsertBlock()->getParent();

  // // Create blocks
  // llvm::BasicBlock *loopStart =
  //     llvm::BasicBlock::Create(*TheContext, "loopStart", TheFunction);
  // llvm::BasicBlock *loopBody =
  //     llvm::BasicBlock::Create(*TheContext, "loopBody", TheFunction);
  // llvm::BasicBlock *loopEnd =
  //     llvm::BasicBlock::Create(*TheContext, "loopEnd", TheFunction);

  // // Initialize counter
  // llvm::AllocaInst *i = Builder->CreateAlloca(Builder->getInt32Ty());
  // Builder->CreateStore(Builder->getInt32(0), i);

  // // Jump to the loop start block
  // Builder->CreateBr(loopStart);
  // // Iterate over each element of the array

  // // Loop start block
  // Builder->SetInsertPoint(loopStart);
  // llvm::Value *iVal =
  //     Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), i);
  // llvm::Value *cond = Builder->CreateICmpSLT(iVal, size);
  // Builder->CreateCondBr(cond, loopBody, loopEnd);

  // // Loop body block
  // Builder->SetInsertPoint(loopBody);
  // llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);

  // llvm::Value *innerValue = nullptr;

  // // Untyped Container Element
  // if (_codeGenerationContext->getDynamicType()->isDyn(elementType)) {
  //   llvm::ConstantInt *index = llvm::cast<llvm::ConstantInt>(iVal);

  //   innerValue =
  //       _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
  //           elementPtr, FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX +
  //                           arrayName + "_" +
  //                           std::to_string(index->getSExtValue()));
  // } else {
  //   // Typed Container Element
  //   innerValue = Builder->CreateLoad(elementType, elementPtr);
  // }
  // Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
  //                     {_stringTypeConverter->convertExplicit(innerValue),
  //                      Builder->getInt1(false)});

  // llvm::Value *iNext = Builder->CreateAdd(iVal, Builder->getInt32(1));
  // Builder->CreateStore(iNext, i);
  // llvm::Value *isNotLast = Builder->CreateICmpSLT(iNext, size);
  // llvm::BasicBlock *ifBlock =
  //     llvm::BasicBlock::Create(*TheContext, "ifBlock", TheFunction);

  // Builder->CreateCondBr(isNotLast, ifBlock, loopStart);

  // Builder->SetInsertPoint(ifBlock);
  // Builder->CreateCall(TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
  //                     {commaPtr, Builder->getInt1(false)});

  // Builder->CreateBr(loopStart);

  // // Loop end block
  // Builder->SetInsertPoint(loopEnd);
  // Builder->CreateCall(
  //     TheModule->getFunction(INNERS::FUNCTIONS::PRINT),
  //     {Builder->CreateGlobalStringPtr("]"), Builder->getInt1(true)});

  return nullptr;
}

llvm::Value *CallExpressionGenerationStrategy::printArray(
    llvm::ArrayType *arrayType, llvm::Type *elementType, llvm::Value *v) {
  std::vector<size_t> sizes;
  _codeGenerationContext->getArraySizeMetadata(v, sizes);
  std::vector<llvm::Value *> indices = {Builder->getInt32(0)};

  llvm::Type *elt = _codeGenerationContext->getArrayElementTypeMetadata(v);
  printArrayAtom(arrayType, v, sizes, indices, 0, elt);

  return nullptr;
}
