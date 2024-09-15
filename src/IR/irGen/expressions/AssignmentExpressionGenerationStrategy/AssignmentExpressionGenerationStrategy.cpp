#include "AssignmentExpressionGenerationStrategy.h"

AssignmentExpressionGenerationStrategy::AssignmentExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *AssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);
  _isGlobal = false;
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());
  return handleAssignmentExpression(assignmentExpression);
}

void AssignmentExpressionGenerationStrategy::declare(
    BoundExpression *expression) {

  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);

  if (assignmentExpression->getNeedDefaulInitilization() &&
      assignmentExpression->getRightPtr() &&
      assignmentExpression->getRightPtr()->getKind() ==
          BinderKindUtils::CallExpression &&
      assignmentExpression->getLeftPtr() &&
      assignmentExpression->getLeftPtr()->getKind() ==
          BinderKindUtils::VariableExpression) {

    BoundVariableExpression *variableExpression =
        static_cast<BoundVariableExpression *>(
            assignmentExpression->getLeftPtr().get());

    BoundCallExpression *callExpression = static_cast<BoundCallExpression *>(
        assignmentExpression->getRightPtr().get());

    std::string variableName = std::any_cast<std::string>(
        ((BoundLiteralExpression<std::any> *)_variableExpression
             ->getIdentifierExpressionPtr()
             .get())
            ->getValue());
    auto [ptr, type] =
        _codeGenerationContext->getAllocaChain()->getPtr(variableName);

    if (Utils::isClassInit(callExpression->getCallerNameRef())) {
      callExpression->setArgumentAlloca(
          callExpression->getArgumentsRef().size(), {ptr, type});
    } else if (_codeGenerationContext->_functionTypes.find(
                   callExpression->getCallerNameRef()) !=
                   _codeGenerationContext->_functionTypes.end() &&
               _codeGenerationContext
                   ->_functionTypes[callExpression->getCallerNameRef()]
                   ->isHavingReturnTypeAsParamater()) {
      callExpression->setArgumentAlloca(0, {ptr, type});
    }
  }
}

llvm::Value *AssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());
  _isGlobal = true;
  return handleAssignmentExpression(assignmentExpression);
}

int8_t AssignmentExpressionGenerationStrategy::populateLHS(
    BoundAssignmentExpression *&assignmentExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  _lhsTypeKind =
      assignmentExpression->getVariable()->getTypeExpression()->getSyntaxType();

  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getLeftPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getLeftPtr().get());
  _lhsPtr = _codeGenerationContext->getValueStackHandler()->getValue();
  _lhsType = _codeGenerationContext->getValueStackHandler()->getLLVMType();
  _lhsDynamicPtr =
      _codeGenerationContext->getValueStackHandler()->getDynamicValue();
  _codeGenerationContext->getValueStackHandler()->popAll();

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    _codeGenerationContext->getLogger()->LogError(
        "Assignment to constant  is not supported in assignment expression ");
    return EXIT_FAILURE;
  }
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLeftPtr()->getLocation());
  if (assignmentExpression->getLeftPtr()->getKind() ==
      BinderKindUtils::VariableExpression) {
    BoundVariableExpression *variableExpression =
        static_cast<BoundVariableExpression *>(
            assignmentExpression->getLeftPtr().get());

    _lhsVariableName = variableExpression->getVariableNameRef();

    return EXIT_SUCCESS;
  }

  if (assignmentExpression->getLeftPtr()->getKind() ==
      BinderKindUtils::IndexExpression) {

    BoundIndexExpression *indexExp = static_cast<BoundIndexExpression *>(
        assignmentExpression->getLeftPtr().get());

    _lhsVariableName = std::any_cast<std::string>(
        indexExp->getBoundIdentifierExpression().get()->getValue());

    return EXIT_SUCCESS;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Left hand side value must be a variable or index Expression in "
      "assignment expression ");
  return EXIT_FAILURE;
}

llvm::Value *AssignmentExpressionGenerationStrategy::handleAssignmentByVariable(
    BoundExpression *exp) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      exp->getLocation());

  if (exp->getKind() == BinderKindUtils::CallExpression) {

    BoundCallExpression *callExp = static_cast<BoundCallExpression *>(exp);

    if (callExp->getCallerNameRef().find(".init") != std::string::npos ||
        (_codeGenerationContext->_functionTypes.find(
             callExp->getCallerNameRef()) !=
             _codeGenerationContext->_functionTypes.end() &&
         _codeGenerationContext->_functionTypes[callExp->getCallerNameRef()]
             ->isHavingReturnTypeAsParamater())) {
      std::unique_ptr<CallExpressionGenerationStrategy> callStrategy =
          std::make_unique<CallExpressionGenerationStrategy>(
              _codeGenerationContext);

      if (_codeGenerationContext->isClassMemberFunction(
              callExp->getCallerNameRef())) {
        callExp->setArgumentAlloca(callExp->getArgumentsRef().size(),
                                   {_lhsPtr, _lhsType});
      } else {
        callExp->setArgumentAlloca(0, {_lhsPtr, _lhsType});
      }

      return callStrategy->generateExpression(exp);
    }
  }

  _expressionGenerationFactory->createStrategy(exp->getKind())
      ->generateExpression(exp);

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (!rhsType) {
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        exp->getLocation());
    _codeGenerationContext->getLogger()->LogError(
        "No right expression found in assignment expression");

    return nullptr;
  }

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {

    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {

    if (llvm::isa<llvm::StructType>(rhsType) &&
        _codeGenerationContext->isValidClassType(
            llvm::cast<llvm::StructType>(rhsType))) {

      rhsValue =
          Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), rhsPtr);
    } else {
      rhsValue = Builder->CreateLoad(rhsType, rhsPtr);
    }
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  if (_lhsDynamicPtr) {

    return handleDynamicPrimitiveVariableAssignment(_lhsDynamicPtr,
                                                    _lhsVariableName, rhsValue);
  }

  if (llvm::isa<llvm::StructType>(_lhsType) &&
      llvm::isa<llvm::StructType>(rhsType)) {
    if (_codeGenerationContext->verifyStructType(
            llvm::cast<llvm::StructType>(_lhsType),
            llvm::cast<llvm::StructType>(rhsType)) == EXIT_FAILURE) {
      return nullptr;
    }

    llvm::StructType *lhsStructType = llvm::cast<llvm::StructType>(_lhsType);
    llvm::StructType *rhsStructType = llvm::cast<llvm::StructType>(rhsType);

    return Builder->CreateStore(rhsValue, _lhsPtr);
  }

  if (llvm::isa<llvm::ArrayType>(_lhsType) &&
      llvm::isa<llvm::ArrayType>(rhsType)) {

    if (_codeGenerationContext->verifyArrayType(
            llvm::cast<llvm::ArrayType>(_lhsType),
            llvm::cast<llvm::ArrayType>(rhsType)) == EXIT_FAILURE)
      return nullptr;

    return Builder->CreateStore(rhsValue, _lhsPtr);
  }

  if (_lhsType != rhsType) {

    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in variable Assignment " + _lhsVariableName +
        " Expected type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_lhsType) +
        " but got type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType));

    return nullptr;
  }

  return Builder->CreateStore(rhsValue, _lhsPtr);
}

llvm::Value *AssignmentExpressionGenerationStrategy::handleRHSExpression(
    BoundExpression *expression) {
  BinderKindUtils::BoundNodeKind rhsKind = expression->getKind();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  switch (rhsKind) {
  case BinderKindUtils::VariableExpression:
  case BinderKindUtils::IndexExpression:
  case BinderKindUtils::CallExpression:
    return handleAssignmentByVariable((expression));

  case BinderKindUtils::BoundBracketedExpression:
    return handleAssignmentByBracketedExpression(
        static_cast<BoundBracketedExpression *>(expression));

  case BinderKindUtils::BoundObjectExpression:
    return handleAssignmentByObjectExpression(
        static_cast<BoundObjectExpression *>(expression));

  default:
    break;
  }

  if (handleWhenRHSIsConstant(expression) == EXIT_SUCCESS)
    return nullptr;

  if (expression->getKind() ==
      BinderKindUtils::BoundNodeKind::BoundNirastExpression) {

    std::unique_ptr<NirastExpressionGenerationStrategy>
        nirastExpressionGenerationStrategy =
            std::make_unique<NirastExpressionGenerationStrategy>(
                _codeGenerationContext);
    return nirastExpressionGenerationStrategy->generateExpression(
        static_cast<BoundNirastExpression *>(expression));
  }

  _codeGenerationContext->getLogger()->LogError("Invalid Expression found ");

  return nullptr;
}

llvm::Value *AssignmentExpressionGenerationStrategy::handleAssignmentExpression(
    BoundAssignmentExpression *assignmentExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  if (populateLHS(assignmentExpression) == EXIT_FAILURE)
    return nullptr;

  if (assignmentExpression->getNeedDefaulInitilization()) {
    initDefaultValue(_lhsType, _lhsPtr, *Builder);
  }

  return handleRHSExpression(assignmentExpression->getRightPtr().get());
}
llvm::Value *AssignmentExpressionGenerationStrategy::
    handleDynamicPrimitiveVariableAssignment(llvm::Value *variable,
                                             const std::string &variableName,
                                             llvm::Value *rhsValue) {
  if (llvm::isa<llvm::GlobalVariable>(variable)) {
    _isGlobal = true;
  } else {
    _isGlobal = false;
  }
  std::string varName = _isGlobal ? variableName : variableName;
  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      variable, rhsValue, rhsValue->getType(), variableName);

  return nullptr;
}

int8_t AssignmentExpressionGenerationStrategy::handleWhenRHSIsConstant(
    BoundExpression *expression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());
  _codeGenerationContext->getValueStackHandler()->popAll();
  _expressionGenerationFactory->createStrategy(expression->getKind())
      ->generateExpression(expression);

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();

    if (_lhsDynamicPtr) {
      handleDynamicPrimitiveVariableAssignment(_lhsDynamicPtr, _lhsVariableName,
                                               rhsValue);
    } else {
      if (_lhsType != rhsType) {

        _codeGenerationContext->getLogger()->LogError(
            "Type mismatch in variable Assignment " + _lhsVariableName +
            " Expected type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(_lhsType) +
            " but got type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType));

        return EXIT_FAILURE;
      }

      Builder->CreateStore(rhsValue, _lhsPtr);
    }

    return EXIT_SUCCESS;
  }
  _codeGenerationContext->getValueStackHandler()->popAll();

  return EXIT_FAILURE;
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleAssignmentByObjectExpression(
    BoundObjectExpression *boundObjExp) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundObjExp->getLocation());

  if (!llvm::isa<llvm::StructType>(_lhsType)) {
    _codeGenerationContext->getLogger()->LogError(
        "Left hand side value must be an object in assignment expression, "
        "but "
        "found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_lhsType));
    return nullptr;
  }

  std::unique_ptr<ObjectAssignmentExpressionGenerationStrategy>
      objectAssignmentGES =
          std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

  return objectAssignmentGES->assignObject(
      boundObjExp, _lhsPtr, llvm::cast<llvm::StructType>(_lhsType),
      _lhsVariableName);
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleAssignmentByBracketedExpression(
    BoundBracketedExpression *bracketedExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bracketedExpression->getLocation());

  if (!llvm::isa<llvm::ArrayType>(_lhsType)) {
    _codeGenerationContext->getLogger()->LogError(
        "Left hand side value must be an array in assignment expression, but "
        "found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_lhsType));
    return nullptr;
  }

  std::unique_ptr<BracketedExpressionGenerationStrategy>
      bracketedExpressionGenerationStrategy =
          std::make_unique<BracketedExpressionGenerationStrategy>(
              _codeGenerationContext);

  return bracketedExpressionGenerationStrategy->assignBracketExpression(
      bracketedExpression, _lhsPtr, llvm::cast<llvm::ArrayType>(_lhsType),
      _lhsVariableName);
}

llvm::Value *AssignmentExpressionGenerationStrategy ::handleAssignExpression(
    llvm::Value *lshPtr, llvm::Type *lhsType, std::string lhsVarName,
    BoundExpression *expression) {
  _lhsPtr = lshPtr;
  _lhsType = lhsType;
  _lhsVariableName = lhsVarName;
  _lhsDynamicPtr = nullptr;

  return handleRHSExpression(expression);
}

void AssignmentExpressionGenerationStrategy::initDefaultValue(
    llvm::Type *type, llvm::Value *alloca, llvm::IRBuilder<> &builder) {

  if (llvm::isa<llvm::StructType>(type)) {
    initObjectWithDefaultValue(llvm::cast<llvm::StructType>(type), alloca,
                               builder);
  } else if (llvm::isa<llvm::ArrayType>(type)) {
    initArrayWithDefaultValue(llvm::cast<llvm::ArrayType>(type), alloca,
                              builder);
  } else {
    _codeGenerationContext->getMapper()->setBuilder(Builder);
    builder.CreateStore(
        _codeGenerationContext->getMapper()->getDefaultValue(type), alloca);
    _codeGenerationContext->getMapper()->restoreBuilder();
  }
}

void AssignmentExpressionGenerationStrategy::initArrayWithDefaultValue(
    llvm::ArrayType *arrayType, llvm::Value *alloca,
    llvm::IRBuilder<> &Builder) {

  const std::string FUNCTION_NAME =
      "assign_" + _codeGenerationContext->getArrayTypeAsString(arrayType);

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

    llvm::Type *elementType = arrayType;
    std::vector<uint64_t> dimensions;
    _codeGenerationContext->createArraySizesAndArrayElementType(dimensions,
                                                                elementType);

    const int64_t sizeToFillVal = std::accumulate(
        dimensions.begin(), dimensions.end(), 1, std::multiplies<uint64_t>());

    for (int i = 0; i < dimensions.size(); i++) {
      std::vector<llvm::BasicBlock *> blocks = {
          llvm::BasicBlock::Create(*TheContext,
                                   "AssignExpr.loopStart-" + std::to_string(i),
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext,
                                   "AssignExpr.loopCmp-" + std::to_string(i),
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext,
                                   "AssignExpr.loopBody-" + std::to_string(i),
                                   currentBlock->getParent()),
          llvm::BasicBlock::Create(*TheContext,
                                   "AssignExpr.loopEnd-" + std::to_string(i),
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
        *TheContext, "AssignExpr.exit", currentBlock->getParent());

    builder.CreateBr(loopBlocks[0][0]);

    for (int i = 0; i < dimensions.size(); i++) {
      // start
      builder.SetInsertPoint(loopBlocks[i][0]);
      builder.CreateStore(builder.getInt32(0), indices[i]);
      builder.CreateBr(loopBlocks[i][1]);

      // cmp
      builder.SetInsertPoint(loopBlocks[i][1]);
      llvm::Value *currentIndex =
          builder.CreateLoad(builder.getInt32Ty(), indices[i]);
      llvm::Value *isLessThan =
          builder.CreateICmpSLT(currentIndex, builder.getInt32(dimensions[i]));
      //?------Comparison Count Increment------
      llvm::Value *isAllElementsFilled = builder.CreateICmpSLT(
          builder.CreateLoad(builder.getInt32Ty(), numberOfElementsFilled),
          builder.getInt32(sizeToFillVal));
      //?

      llvm::Value *success = builder.CreateAnd(isLessThan, isAllElementsFilled);

      builder.CreateCondBr(success, loopBlocks[i][2], loopBlocks[i][3]);

      // body
      builder.SetInsertPoint(loopBlocks[i][2]);
      if (i == dimensions.size() - 1) {
        std::vector<llvm::Value *> indexList = {builder.getInt32(0)};

        for (int j = 0; j < dimensions.size(); j++) {
          indexList.push_back(
              builder.CreateLoad(builder.getInt32Ty(), indices[j]));
        }

        llvm::Value *elementPtr =
            builder.CreateGEP(arrayType, fun->getArg(0), indexList);

        initDefaultValue(elementType, elementPtr, builder);

        llvm::Value *_currentIndex =
            builder.CreateLoad(builder.getInt32Ty(), indices[i]);
        llvm::Value *nextIndex =
            builder.CreateAdd(_currentIndex, builder.getInt32(1));
        builder.CreateStore(nextIndex, indices[i]);

        //?------Elements filled Count Increment------
        builder.CreateStore(
            builder.CreateAdd(builder.CreateLoad(builder.getInt32Ty(),
                                                 numberOfElementsFilled),
                              builder.getInt32(1)),
            numberOfElementsFilled);
        //?------End------

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

        builder.CreateBr(loopBlocks[i - 1][1]);
      } else {
        builder.CreateBr(exit);
      }
    }

    builder.SetInsertPoint(exit);
    builder.CreateRetVoid();
  }

  Builder.CreateCall(fun, {alloca});
}

void AssignmentExpressionGenerationStrategy::initObjectWithDefaultValue(
    llvm::StructType *objectType, llvm::Value *alloca,
    llvm::IRBuilder<> &Builder) {

  std::string typeName = objectType->getStructName().str();
  const std::string FUNCTION_NAME =
      "assign_" +
      _codeGenerationContext->getMapper()->getLLVMTypeName(objectType, false);

  llvm::Function *fun = TheModule->getFunction(FUNCTION_NAME);
  if (!fun) {

    llvm::FunctionType *FT = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*TheContext),
        {llvm::PointerType::getUnqual(objectType)}, false);
    fun = llvm::Function::Create(FT,
                                 llvm::Function::LinkageTypes::InternalLinkage,
                                 FUNCTION_NAME, *TheModule);
    llvm::BasicBlock *entry =
        llvm::BasicBlock::Create(*TheContext, "entry", fun);
    llvm::IRBuilder<> builder(entry);

    uint64_t index = 0;
    for (const auto &items : objectType->elements()) {

      llvm::Value *innerElementPtr =
          builder.CreateStructGEP(objectType, fun->getArg(0), index);

      initDefaultValue(objectType->getElementType(index), innerElementPtr,
                       builder);

      index++;
    }
    builder.CreateRetVoid();
  }

  Builder.CreateCall(fun, {alloca});
}