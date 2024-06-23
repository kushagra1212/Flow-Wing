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

      if (llvm::isa<llvm::StructType>(_lhsType) &&
          _codeGenerationContext->isValidClassType(
              llvm::cast<llvm::StructType>(_lhsType))) {
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

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {

    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {
    rhsValue = Builder->CreateLoad(rhsType, rhsPtr);
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
    return handleAssignmentByVariable(
        static_cast<BoundVariableExpression *>(expression));

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
    initDefaultValue(_lhsType, _lhsPtr);
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

  _expressionGenerationFactory->createStrategy(expression->getKind())
      ->generateExpression(expression);

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
    _codeGenerationContext->getValueStackHandler()->popAll();
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

  return handleRHSExpression(expression);
}

void AssignmentExpressionGenerationStrategy::initDefaultValue(
    llvm::Type *type, llvm::Value *alloca) {

  if (llvm::isa<llvm::StructType>(type)) {
    initObjectWithDefaultValue(llvm::cast<llvm::StructType>(type), alloca);
  } else if (llvm::isa<llvm::ArrayType>(type)) {
    initArrayWithDefaultValue(llvm::cast<llvm::ArrayType>(type), alloca);
  } else {
    Builder->CreateStore(
        _codeGenerationContext->getMapper()->getDefaultValue(type), alloca);
  }
}

void AssignmentExpressionGenerationStrategy::initArrayWithDefaultValue(
    llvm::ArrayType *arrayType, llvm::Value *alloca) {
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  std::vector<std::vector<llvm::BasicBlock *>> loopBlocks;
  std::vector<llvm::AllocaInst *> indices;

  llvm::Type *elementType = arrayType;
  std::vector<uint64_t> dimensions;
  _codeGenerationContext->createArraySizesAndArrayElementType(dimensions,
                                                              elementType);

  const int64_t sizeToFillVal = std::accumulate(
      dimensions.begin(), dimensions.end(), 1, std::multiplies<uint64_t>());

  for (int i = 0; i < dimensions.size(); i++) {
    std::vector<llvm::BasicBlock *> blocks = {
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopStart-" + std::to_string(i),
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopCmp-" + std::to_string(i),
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopBody-" + std::to_string(i),
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopEnd-" + std::to_string(i),
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

  for (int i = 0; i < dimensions.size(); i++) {
    // start
    Builder->SetInsertPoint(loopBlocks[i][0]);
    Builder->CreateStore(Builder->getInt32(0), indices[i]);
    Builder->CreateBr(loopBlocks[i][1]);

    // cmp
    Builder->SetInsertPoint(loopBlocks[i][1]);
    llvm::Value *currentIndex =
        Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
    llvm::Value *isLessThan =
        Builder->CreateICmpSLT(currentIndex, Builder->getInt32(dimensions[i]));
    //?------Comparison Count Increment------
    llvm::Value *isAllElementsFilled = Builder->CreateICmpSLT(
        Builder->CreateLoad(Builder->getInt32Ty(), numberOfElementsFilled),
        Builder->getInt32(sizeToFillVal));
    //?

    llvm::Value *success = Builder->CreateAnd(isLessThan, isAllElementsFilled);

    Builder->CreateCondBr(success, loopBlocks[i][2], loopBlocks[i][3]);

    // body
    Builder->SetInsertPoint(loopBlocks[i][2]);
    if (i == dimensions.size() - 1) {
      std::vector<llvm::Value *> indexList = {Builder->getInt32(0)};

      for (int j = 0; j < dimensions.size(); j++) {
        indexList.push_back(
            Builder->CreateLoad(Builder->getInt32Ty(), indices[j]));
      }

      llvm::Value *elementPtr =
          Builder->CreateGEP(arrayType, alloca, indexList);

      initDefaultValue(elementType, elementPtr);

      llvm::Value *_currentIndex =
          Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
      llvm::Value *nextIndex =
          Builder->CreateAdd(_currentIndex, Builder->getInt32(1));
      Builder->CreateStore(nextIndex, indices[i]);

      //?------Elements filled Count Increment------
      Builder->CreateStore(
          Builder->CreateAdd(Builder->CreateLoad(Builder->getInt32Ty(),
                                                 numberOfElementsFilled),
                             Builder->getInt32(1)),
          numberOfElementsFilled);
      //?------End------

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

      Builder->CreateBr(loopBlocks[i - 1][1]);
    } else {
      Builder->CreateBr(exit);
    }
  }

  Builder->SetInsertPoint(exit);
}

void AssignmentExpressionGenerationStrategy::initObjectWithDefaultValue(
    llvm::StructType *objectType, llvm::Value *alloca) {
  std::string typeName = objectType->getStructName().str();

  uint64_t index = 0;
  for (const auto &items : objectType->elements()) {

    llvm::Value *innerElementPtr =
        Builder->CreateStructGEP(objectType, alloca, index);

    initDefaultValue(objectType->getElementType(index), innerElementPtr);

    index++;
  }
}