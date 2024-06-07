#include "ForStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ForStatementGenerationStrategy::ForStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *
ForStatementGenerationStrategy::generateStatement(BoundStatement *statement) {
  BoundForStatement *forStatement = static_cast<BoundForStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      forStatement->getLocation());

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());

  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());

  _codeGenerationContext->getTypeChain()->addHandler(
      std::make_unique<TypeTable>());

  _codeGenerationContext->getCustomTypeChain()->addHandler(
      std::make_unique<CustomTypeStatementTable>());

  std::string variableName = "";

  // Step Value

  llvm::Value *stepValue =
      llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 1, true)); // default

  BoundExpression *forStepExp = forStatement->getStepExpressionPtr().get();
  if (forStepExp) {
    llvm::Value *r =
        _expressionGenerationFactory->createStrategy(forStepExp->getKind())
            ->generateExpression(forStepExp);
    if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
      r = Builder->CreateLoad(
          _codeGenerationContext->getValueStackHandler()->getLLVMType(),
          _codeGenerationContext->getValueStackHandler()->getValue());
      _codeGenerationContext->getValueStackHandler()->popAll();
    }
    stepValue = _int32TypeConverter->convertImplicit(r);
  }

  // Upper Bound
  BoundExpression *upperBoundExp = forStatement->getUpperBoundPtr().get();

  llvm::Value *upperBound =
      _expressionGenerationFactory->createStrategy(upperBoundExp->getKind())
          ->generateExpression(upperBoundExp);
  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    upperBound = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }
  // Declare Loop Variable

  if (forStatement->getInitializationPtr()->getKind() ==
      BinderKindUtils::BoundNodeKind::VariableDeclaration) {
    BoundVariableDeclaration *variableDeclaration =
        (BoundVariableDeclaration *)forStatement->getInitializationPtr().get();

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        variableDeclaration->getLocation());

    variableName = variableDeclaration->getVariableName();

    _statementGenerationFactory->createStrategy(variableDeclaration->getKind())
        ->generateStatement(variableDeclaration);
  } else {
    // Loop Variable

    variableName = "ForLoop::loopVariable";

    std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
        variableDeclarationStatementGenerationStrategy =
            std::make_unique<VariableDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    BoundStatement *initializationStat =
        forStatement->getInitializationPtr().get();

    llvm::Value *initializationStatResult =
        _statementGenerationFactory
            ->createStrategy(initializationStat->getKind())
            ->generateStatement(initializationStat);

    variableDeclarationStatementGenerationStrategy
        ->handlePrimitiveLocalVariableDeclr(
            variableName,
            _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
                initializationStatResult->getType()),
            initializationStatResult);
  }

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      forStatement->getLocation());

  if (variableName == "") {
    _codeGenerationContext->getLogger()->LogError(
        "Variable name is not found in for statement");

    return nullptr;
  }
  std::unique_ptr<VariableExpressionGenerationStrategy>
      variableExpressionGenerationStrategy =
          std::make_unique<VariableExpressionGenerationStrategy>(
              _codeGenerationContext);

  std::unique_ptr<AssignmentExpressionGenerationStrategy>
      assignmentExpressionGenerationStrategy =
          std::make_unique<AssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();
  llvm::Value *exitValue = nullptr;
  llvm::BasicBlock *loopCondition =
      llvm::BasicBlock::Create(*TheContext, "ForLoop::loopCondition", function);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "ForLoop::loopBody", function);
  llvm::BasicBlock *afterLoop =
      llvm::BasicBlock::Create(*TheContext, "ForLoop::afterLoop", function);

  llvm::BasicBlock *breakLoop =
      llvm::BasicBlock::Create(*TheContext, "ForLoop::breakLoop", function);

  Builder->CreateBr(loopCondition);

  // Loop Condition

  Builder->SetInsertPoint(loopCondition);

  _codeGenerationContext->decrementCountIfNotZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT));

  llvm::Value *value =
      variableExpressionGenerationStrategy->getVariableValue(variableName);

  llvm::PHINode *conditionPHI =
      generateLoopCondition(stepValue, value, upperBound);

  if (conditionPHI == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Condition value is not found in for statement");

    return nullptr;
  }

  Builder->CreateCondBr(conditionPHI, breakLoop, afterLoop);

  Builder->SetInsertPoint(breakLoop);

  Builder->CreateCondBr(
      _codeGenerationContext->isCountZero(
          _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT),
          llvm::Type::getInt32Ty(*TheContext)),
      loopBody, afterLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);

  BoundStatement *bodyStat = forStatement->getStatementPtr().get();

  llvm::Value *result =
      _statementGenerationFactory->createStrategy(bodyStat->getKind())
          ->generateStatement(bodyStat);

  // Value incremented by Step

  llvm::Value *incrementedValue = Builder->CreateAdd(value, stepValue);

  //   assignmentExpressionGenerationStrategy
  //       ->handlePrimitiveLocalVariableAssignment(
  //           variableName, SyntaxKindUtils::SyntaxKind::Int32Keyword,
  //           incrementedValue);

  {
    llvm::Value *v =
        _codeGenerationContext->getAllocaChain()->getPtr(variableName).first;
    _codeGenerationContext->getNamedValueChain()->updateNamedValue(
        variableName, incrementedValue);
    Builder->CreateStore(incrementedValue, v);
  }

  Builder->CreateBr(loopCondition);

  Builder->SetInsertPoint(afterLoop);

  _codeGenerationContext->decrementCountIfNotZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));

  // Exit

  _codeGenerationContext->getAllocaChain()->removeHandler();
  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getTypeChain()->removeHandler();
  _codeGenerationContext->getCustomTypeChain()->removeHandler();
  return exitValue;
}

llvm::Value *ForStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}

llvm::PHINode *ForStatementGenerationStrategy::generateLoopCondition(
    llvm::Value *stepValue, llvm::Value *value, llvm::Value *upperBound) {
  llvm::Value *isStepNegative =
      Builder->CreateICmpSLT(stepValue, Builder->getInt32(0));

  llvm::BasicBlock *trueBlock = llvm::BasicBlock::Create(
      value->getContext(), "ForLoop::Conditon::trueBlock",
      Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *falseBlock = llvm::BasicBlock::Create(
      value->getContext(), "ForLoop::Conditon::falseBlock",
      Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
      value->getContext(), "ForLoop::Conditon::mergeBlock",
      Builder->GetInsertBlock()->getParent());

  Builder->CreateCondBr(isStepNegative, trueBlock, falseBlock);

  Builder->SetInsertPoint(trueBlock);

  llvm::Value *oppositeCondition = Builder->CreateICmpSGE(value, upperBound);

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(falseBlock);

  llvm::Value *normalCondition = Builder->CreateICmpSLE(value, upperBound);

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(mergeBlock);

  llvm::PHINode *conditionPHI = Builder->CreatePHI(Builder->getInt1Ty(), 2);
  conditionPHI->addIncoming(oppositeCondition, trueBlock);
  conditionPHI->addIncoming(normalCondition, falseBlock);

  return conditionPHI;
}
