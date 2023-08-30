#include "IRGenerator.h"

IRGenerator::IRGenerator(int environment) {

  TheContext = std::make_unique<llvm::LLVMContext>();
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
  TheModule = std::make_unique<llvm::Module>("Elang", *TheContext);
  _environment = environment;
  this->_irUtils = std::make_unique<IRUtils>(TheModule.get(), Builder.get(),
                                             TheContext.get());

  this->updateModule();
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  this->defineStandardFunctions();

  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());
}

void IRGenerator::updateModule() {
  std::vector<std::string> irFilePaths = {
      "../../../src/evaluator/BuiltinIRs/built_in_module.ll",
      "../../../src/evaluator/BuiltinIRs/functions.ll"};

  for (const std::string &path : irFilePaths) {
    llvm::SMDiagnostic err;
    bool LinkResult = llvm::Linker::linkModules(
        *TheModule, llvm::parseIRFile(path, err, *TheContext));
    if (LinkResult) {
      llvm::errs() << "Error linking " + path + ":" << err.getMessage() << "\n";
    }
  }
}

llvm::Value *
IRGenerator::generateEvaluateLiteralExpressionFunction(BoundExpression *node) {

  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();

  llvm::Value *val = this->_irUtils->getLLVMValue(value);

  if (val == nullptr) {
    return nullptr;
  }

  return val;
}

llvm::Value *
IRGenerator::generateEvaluateUnaryExpressionFunction(BoundExpression *node) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
  llvm::Value *val = this->generateEvaluateExpressionStatement(
      unaryExpression->getOperandPtr().get());
  if (val == nullptr) {
    return nullptr;
  }

  llvm::Value *result = nullptr;

  switch (unaryExpression->getOperatorPtr()) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {

    result = Builder->CreateAdd(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {

    result = Builder->CreateSub(
        llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)), val);
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {

    if (val->getType()->isIntegerTy() || val->getType()->isFloatingPointTy()) {
      // Convert non-boolean values to boolean (true if zero, false if non-zero)
      result = Builder->CreateICmpEQ(
          val, llvm::Constant::getNullValue(val->getType()));
    } else if (val->getType()->isPointerTy() &&
               val->getType()->getPointerElementType()->isIntegerTy(8)) {
      // Get the string length
      llvm::Value *length =
          Builder->CreateCall(TheModule->getFunction("stringLength"), val);
      val = length;

      // Compare the string Length to Zero
      result = Builder->CreateICmpEQ(
          length, llvm::ConstantInt::get(length->getType(), 0));
    } else if (val->getType()->isIntegerTy(1)) {
      // For boolean values, perform logical NOT
      result = Builder->CreateNot(val);
    } else {
      // Unsupported type
      return nullptr;
    }
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation: {

    result = Builder->CreateXor(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, -1, true)));
    break;
  }
  default: {

    return nullptr;
  }
  }

  return result;
}

void IRGenerator::printIR() {
  // Print LLVM IR to console
  TheModule->print(llvm::outs(), nullptr);
}

std::unique_ptr<llvm::Module>
IRGenerator::_getModule(const std::vector<std::string> &irFilePaths) {
  llvm::SMDiagnostic err;
  llvm::SourceMgr sourceMgr;

  if (irFilePaths.size() == 0) {
    llvm::errs() << "No IR files provided\n";
    return nullptr;
  }

  std::string filePath = irFilePaths[0];

  llvm::Expected<std::unique_ptr<llvm::Module>> parsedModule =
      llvm::parseIRFile(filePath, err, *TheContext);

  if (!parsedModule->get()) {
    llvm::errs() << "Error parsing IR file " << filePath << ": "
                 << llvm::toString(parsedModule.takeError()) << "\n";
    return nullptr; // Skip this file and continue with the next one
  }
  std::unique_ptr<llvm::Module> parsedModulePtr = std::move(parsedModule.get());

  return std::move(parsedModulePtr);
}

void IRGenerator::defineStandardFunctions() {
  // Create global constant strings
  llvm::Constant *trueStr =
      llvm::ConstantDataArray::getString(*TheContext, "true");
  llvm::GlobalVariable *globalTrueStr = new llvm::GlobalVariable(
      *TheModule, trueStr->getType(), true, llvm::GlobalValue::ExternalLinkage,
      trueStr, ELANG_GLOBAL_TRUE);

  llvm::Constant *falseStr =
      llvm::ConstantDataArray::getString(*TheContext, "false");
  llvm::GlobalVariable *globalFalseStr = new llvm::GlobalVariable(
      *TheModule, falseStr->getType(), true, llvm::GlobalValue::ExternalLinkage,
      falseStr, ELANG_GLOBAL_FALSE);

  llvm::PointerType *int8PtrType = llvm::Type::getInt8PtrTy(*TheContext);
  llvm::GlobalVariable *globalNullPtr = new llvm::GlobalVariable(
      *TheModule, int8PtrType, true, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantPointerNull::get(int8PtrType), ELANG_GLOBAL_NULL);

  // Break keyword count

  llvm::Constant *breakCount =
      llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));

  llvm::GlobalVariable *globalBreakCount = new llvm::GlobalVariable(
      *TheModule, breakCount->getType(), false,
      llvm::GlobalValue::ExternalLinkage, breakCount, ELANG_BREAK_COUNT);

  llvm::GlobalVariable *globalContinueCount = new llvm::GlobalVariable(
      *TheModule, breakCount->getType(), false,
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)),
      ELANG_CONTINUE_COUNT);

  llvm::Constant *zero =
      llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));

  llvm::GlobalVariable *globalZero = new llvm::GlobalVariable(
      *TheModule, breakCount->getType(), true,
      llvm::GlobalValue::ExternalLinkage, zero, ELANG_GLOBAL_ZERO);

  llvm::Constant *errorCount =
      llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true));

  llvm::GlobalVariable *globalErrorCount = new llvm::GlobalVariable(
      *TheModule, errorCount->getType(), false,
      llvm::GlobalValue::ExternalLinkage, errorCount, ELANG_GLOBAL_ERROR);
}

llvm::Value *
IRGenerator::generateEvaluateVariableExpressionFunction(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  std::string variableName = this->_irUtils->getString(
      variableExpression->getIdentifierExpressionPtr().get());

  llvm::Value *variableValue =
      this->_irUtils->getNamedValue(variableName, this->_NamedValuesStack);

  llvm::AllocaInst *v = this->_irUtils->getNamedValueAlloca(
      variableName, this->_NamedValuesAllocaStack);

  llvm::Value *value = Builder->CreateLoad(variableValue->getType(), v);

  if (!variableValue) {
    // Variable not found, handle error

    llvm::errs() << "Variable not found\n";
    return nullptr;
  }

  return value;
}
llvm::Value *IRGenerator::generateEvaluateAssignmentExpressionFunction(
    BoundExpression *node) {

  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;

  std::string variableName =
      this->_irUtils->getString(assignmentExpression->getLeftPtr().get());

  if (!this->_irUtils->getNamedValue(variableName, this->_NamedValuesStack)) {
    // Variable not found, handle error
    llvm::errs() << "Variable not found in assignment expression\n";
    return nullptr;
  }

  llvm::Value *rhsValue = generateEvaluateExpressionStatement(
      assignmentExpression->getRightPtr().get());

  if (!rhsValue) {
    // Error generating IR for the right-hand side expression

    llvm::errs()
        << "Right hand side value not found in assignment expression\n";
    return nullptr;
  }

  // Update the variable value

  this->_irUtils->updateNamedValue(variableName, rhsValue,
                                   this->_NamedValuesStack);

  Builder->CreateStore(rhsValue,
                       this->_irUtils->getNamedValueAlloca(
                           variableName, this->_NamedValuesAllocaStack));

  return rhsValue;
}

llvm::Value *IRGenerator::generateEvaluateBinaryExpressionFunction(
    BoundBinaryExpression *node) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;

  llvm::Value *lhsValue =
      generateEvaluateExpressionStatement(binaryExpression->getLeftPtr().get());

  llvm::Value *rhsValue = generateEvaluateExpressionStatement(
      binaryExpression->getRightPtr().get());

  if (!lhsValue || !rhsValue) {
    llvm::errs() << "Error in generating IR for operands\n";
    return nullptr;
  }

  llvm::Type *lhsType = lhsValue->getType();
  llvm::Type *rhsType = rhsValue->getType();

  llvm::Value *result = nullptr;
  if (this->_irUtils->isStringType(lhsType) ||
      this->_irUtils->isStringType(rhsType)) {

    result = this->_irUtils->getResultFromBinaryOperationOnString(
        this->_irUtils->convertToString(lhsValue),
        this->_irUtils->convertToString(rhsValue), binaryExpression);
  } else if (this->_irUtils->isDoubleType(lhsType) ||
             this->_irUtils->isDoubleType(rhsType)) {

    result = this->_irUtils->getResultFromBinaryOperationOnDouble(
        this->_irUtils->convertToDouble(lhsValue),
        this->_irUtils->convertToDouble(rhsValue), binaryExpression);
  } else if (this->_irUtils->isBoolType(lhsType) &&
             this->_irUtils->isBoolType(rhsType)) {

    result = this->_irUtils->getResultFromBinaryOperationOnBool(
        lhsValue, rhsValue, binaryExpression);
  } else {

    result = this->_irUtils->getResultFromBinaryOperationOnInt(
        this->_irUtils->convertToInt(lhsValue),
        this->_irUtils->convertToInt(rhsValue), binaryExpression);
  }
  return result;
}

llvm::Value *
IRGenerator::handleBuiltInfuntions(BoundCallExpression *callExpression) {

  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();

  const std::string &functionName = function.name;
  std::size_t arguments_size = callExpression->getArguments().size();
  if (functionName == Utils::BuiltInFunctions::print.name) {
    if (arguments_size == 1) {

      llvm::Value *strPtri8 = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());

      this->_irUtils->printFunction(strPtri8, false);

      return this->getNull();
    }

    llvm::errs() << "Error: Unexpected function cal: arguments does  not match";
    return this->getNull();
  }
  llvm::errs() << "Error: Unexpected function call ";
  return this->getNull();
}

llvm::Value *IRGenerator::generateEvaluateCallExpression(
    BoundCallExpression *callExpression) {

  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();
  if (Utils::BuiltInFunctions::getFunctionSymbol(function.name).name ==
      function.name) {
    return this->handleBuiltInfuntions(callExpression);
  }

  return this->getNull();
}

llvm::Value *
IRGenerator::generateEvaluateExpressionStatement(BoundExpression *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression: {

    return this->generateEvaluateLiteralExpressionFunction(node);
  }
  case BinderKindUtils::BoundNodeKind::UnaryExpression: {

    return this->generateEvaluateUnaryExpressionFunction(node);
  }
  case BinderKindUtils::BoundNodeKind::VariableExpression: {
    return this->generateEvaluateVariableExpressionFunction(node);
  }

  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {
    return this->generateEvaluateAssignmentExpressionFunction(node);
  }
  case BinderKindUtils::BoundNodeKind::BinaryExpression: {
    return this->generateEvaluateBinaryExpressionFunction(
        (BoundBinaryExpression *)node);
  }
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {
    BoundParenthesizedExpression *parenthesizedExpression =
        (BoundParenthesizedExpression *)node;
    return this->generateEvaluateExpressionStatement(
        parenthesizedExpression->getExpressionPtr().get());
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {
    return this->generateEvaluateCallExpression((BoundCallExpression *)node);
  }

  default: {

    return nullptr;
  }
  }
}
llvm::Value *IRGenerator::generateEvaluateVariableDeclaration(
    BoundVariableDeclaration *node) {

  std::string variable_name = node->getVariable();
  llvm::Value *result = this->generateEvaluateExpressionStatement(
      node->getInitializerPtr().get());

  this->_irUtils->setNamedValue(variable_name, result, this->_NamedValuesStack);

  // create and load variable

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(result->getType(), nullptr, variable_name.c_str());

  this->_irUtils->setNamedValueAlloca(variable_name, variable,
                                      this->_NamedValuesAllocaStack);

  Builder->CreateStore(result, variable);

  return result;
}
llvm::Constant *IRGenerator::getNull() {
  llvm::Type *int8PtrType = llvm::Type::getInt8PtrTy(*TheContext);
  return llvm::ConstantExpr::getBitCast(this->_irUtils->getNullValue(),
                                        int8PtrType);
}

llvm::Value *IRGenerator::generateEvaluateBlockStatement(
    BoundBlockStatement *blockStatement) {

  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // create and load variable

  llvm::BasicBlock *afterNestedBlock = llvm::BasicBlock::Create(
      *TheContext, "afterNestedBlock", currentBlock->getParent());

  std::vector<llvm::BasicBlock *> nestedBlocks, checkContinueBlocks;
  int statementSize = blockStatement->getStatements().size();
  int indexForStatements = 0;

  while (indexForStatements < statementSize) {

    llvm::BasicBlock *nestedBlock = llvm::BasicBlock::Create(
        *TheContext, "nestedBlock", currentBlock->getParent());
    nestedBlocks.push_back(nestedBlock);

    llvm::BasicBlock *checkContinueBlock = llvm::BasicBlock::Create(
        *TheContext, "checkContinueBlock", currentBlock->getParent());

    checkContinueBlocks.push_back(checkContinueBlock);

    indexForStatements++;
  }

  // Nested Block

  if (blockStatement->getStatements().size() == 0) {
    Builder->CreateBr(afterNestedBlock);
  } else {
    Builder->CreateBr(nestedBlocks[0]);
  }

  for (int i = 0; i < statementSize; i++) {

    // i th nested block

    Builder->SetInsertPoint(nestedBlocks[i]);

    llvm::Value *res = this->generateEvaluateStatement(
        blockStatement->getStatements()[i].get());

    Builder->CreateCondBr(
        this->_irUtils->isCountZero(ELANG_BREAK_COUNT,
                                    llvm::Type::getInt32Ty(*TheContext)),
        checkContinueBlocks[i], afterNestedBlock);

    //  i th Check continue Block

    Builder->SetInsertPoint(checkContinueBlocks[i]);

    if (i == blockStatement->getStatements().size() - 1)
      Builder->CreateBr(afterNestedBlock);
    else {
      Builder->CreateCondBr(
          this->_irUtils->isCountZero(ELANG_CONTINUE_COUNT,
                                      llvm::Type::getInt32Ty(*TheContext)),
          nestedBlocks[i + 1], afterNestedBlock);
    }
  }

  Builder->SetInsertPoint(afterNestedBlock);

  this->_NamedValuesStack.pop();
  this->_NamedValuesAllocaStack.pop();
  return getNull();
}

void IRGenerator::generateEvaluateGlobalStatement(BoundStatement *node) {

  BoundBlockStatement *blockStatement = (BoundBlockStatement *)node;
  llvm::Value *returnValue = getNull(); // default return value
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateBlockStatement", *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", F);

  // Entry Block

  Builder->SetInsertPoint(entryBlock);

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {

    llvm::Value *res = this->generateEvaluateStatement(
        blockStatement->getStatements()[i].get());

    if (i == blockStatement->getStatements().size() - 1 &&
        blockStatement->getStatements()[i].get()->getKind() ==
            BinderKindUtils::BoundNodeKind::ExpressionStatement) {
      returnValue = res;
    }
  }

  // Return Block

  if (returnValue != getNull()) {

    llvm::Value *isZero = this->_irUtils->isCountZero(
        ELANG_GLOBAL_ERROR, llvm::Type::getInt32Ty(*TheContext));

    llvm::BasicBlock *printBlock =
        llvm::BasicBlock::Create(*TheContext, "printBlock", F);

    llvm::BasicBlock *errorBlock =
        llvm::BasicBlock::Create(*TheContext, "errorBlock", F);

    Builder->CreateCondBr(isZero, printBlock, errorBlock);

    Builder->SetInsertPoint(printBlock);

    this->_irUtils->printFunction(returnValue, false);

    Builder->CreateBr(returnBlock);

    Builder->SetInsertPoint(errorBlock);

    Builder->CreateBr(returnBlock);

  } else {

    Builder->CreateBr(returnBlock);
  }
  Builder->SetInsertPoint(returnBlock);
  Builder->CreateRet(this->_irUtils->getGlobalVarAndLoad(
      ELANG_GLOBAL_ERROR, llvm::Type::getInt32Ty(*TheContext)));
}

llvm::Value *IRGenerator::evaluateIfStatement(BoundStatement *node) {

  BoundIfStatement *ifStatement = (BoundIfStatement *)node;
  llvm::Value *exitValue = getNull();
  llvm::Value *conditionValue = this->generateEvaluateExpressionStatement(
      ifStatement->getConditionPtr().get());

  if (conditionValue == nullptr) {
    llvm::errs() << "Error in Compiling for if condition\n";
    return nullptr;
  }

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  llvm::Function *function = currentBlock->getParent();

  llvm::BasicBlock *thenBlock =
      llvm::BasicBlock::Create(*TheContext, "then", function);

  std::vector<llvm::BasicBlock *> orIfBlock;

  for (int i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    orIfBlock.push_back(
        llvm::BasicBlock::Create(*TheContext, "orIf" + i, function));
  }

  std::vector<llvm::BasicBlock *> orIfThenBlocks;

  for (int i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    orIfThenBlocks.push_back(
        llvm::BasicBlock::Create(*TheContext, "orIfThen" + i, function));
  }

  llvm::BasicBlock *elseBlock =
      llvm::BasicBlock::Create(*TheContext, "else", function);

  llvm::BasicBlock *afterIfElse =
      llvm::BasicBlock::Create(*TheContext, "afterIfElse", function);

  if (ifStatement->getOrIfStatementsPtr().size()) {
    Builder->CreateCondBr(conditionValue, thenBlock, orIfBlock[0]);
  } else {
    Builder->CreateCondBr(conditionValue, thenBlock, elseBlock);
  }

  for (int i = 0; i < orIfBlock.size(); i++) {
    Builder->SetInsertPoint(orIfBlock[i]);
    llvm::Value *orIfConditionValue = this->generateEvaluateExpressionStatement(
        ifStatement->getOrIfStatementsPtr()[i]->getConditionPtr().get());

    if (orIfConditionValue == nullptr) {
      llvm::errs() << "Error in Compiling for or if condition\n";
      return nullptr;
    }

    if (i == orIfBlock.size() - 1) {
      Builder->CreateCondBr(orIfConditionValue, orIfThenBlocks[i], elseBlock);
    } else {
      Builder->CreateCondBr(orIfConditionValue, orIfThenBlocks[i],
                            orIfBlock[i + 1]);
    }
  }

  // Then Block

  Builder->SetInsertPoint(thenBlock);

  llvm::Value *thenValue =
      this->generateEvaluateStatement(ifStatement->getThenStatementPtr().get());

  Builder->CreateBr(afterIfElse);

  // Or If Then Block

  for (int i = 0; i < orIfThenBlocks.size(); i++) {
    Builder->SetInsertPoint(orIfThenBlocks[i]);

    llvm::Value *orIfThenValue =
        this->generateEvaluateStatement(ifStatement->getOrIfStatementsPtr()[i]
                                            .get()
                                            ->getThenStatementPtr()
                                            .get());

    Builder->CreateBr(afterIfElse);
  }

  // Else Block

  Builder->SetInsertPoint(elseBlock);

  if (ifStatement->getElseStatementPtr().get()) {
    llvm::Value *elseValue = this->generateEvaluateStatement(
        ifStatement->getElseStatementPtr().get());
  }

  Builder->CreateBr(afterIfElse);

  Builder->SetInsertPoint(afterIfElse);

  return exitValue;
}

llvm::Value *IRGenerator::evaluateWhileStatement(BoundWhileStatement *node) {
  BoundWhileStatement *whileStatement = (BoundWhileStatement *)node;

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();
  llvm::Value *exitValue = getNull();
  llvm::BasicBlock *loopCondition =
      llvm::BasicBlock::Create(*TheContext, "loopCondition", function);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "loopBody", function);
  llvm::BasicBlock *afterLoop =
      llvm::BasicBlock::Create(*TheContext, "afterLoop", function);

  llvm::BasicBlock *breakLoop =
      llvm::BasicBlock::Create(*TheContext, "breakLoop", function);

  Builder->CreateBr(loopCondition);

  // Loop Condition

  Builder->SetInsertPoint(loopCondition);

  this->_irUtils->decrementCountIfNotZero(ELANG_CONTINUE_COUNT);
  llvm::Value *conditionValue = this->generateEvaluateExpressionStatement(
      whileStatement->getConditionPtr().get());

  // Load the condition

  if (conditionValue == nullptr) {
    llvm::errs() << "Error in Compiling for While condition\n";
    return this->_irUtils->getNullValue();
  }

  Builder->CreateCondBr(conditionValue, breakLoop, afterLoop);

  Builder->SetInsertPoint(breakLoop);

  Builder->CreateCondBr(
      this->_irUtils->isCountZero(ELANG_BREAK_COUNT,
                                  llvm::Type::getInt32Ty(*TheContext)),
      loopBody, afterLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);
  llvm::Value *result =
      this->generateEvaluateStatement(whileStatement->getBodyPtr().get());

  Builder->CreateBr(loopCondition);

  // After Loop

  Builder->SetInsertPoint(afterLoop);

  this->_irUtils->decrementCountIfNotZero(ELANG_BREAK_COUNT);

  return exitValue;
}

llvm::Value *IRGenerator::evaluateForStatement(BoundForStatement *node) {
  BoundForStatement *forStatement = (BoundForStatement *)node;
  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());

  std::string variableName = "";

  // Step Value

  llvm::Value *stepValue =
      llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 1, true)); // default

  if (forStatement->getStepExpressionPtr().get()) {
    stepValue =
        this->_irUtils->convertToInt(this->generateEvaluateExpressionStatement(
            forStatement->getStepExpressionPtr().get()));
  }

  // Upper Bound

  llvm::Value *upperBound = this->generateEvaluateExpressionStatement(
      forStatement->getUpperBoundPtr().get());

  // Declare Loop Variable

  if (forStatement->getInitializationPtr()->getKind() ==
      BinderKindUtils::BoundNodeKind::VariableDeclaration) {
    BoundVariableDeclaration *variableDeclaration =
        (BoundVariableDeclaration *)forStatement->getInitializationPtr().get();

    variableName = variableDeclaration->getVariable();

    this->generateEvaluateStatement(variableDeclaration);
  } else {

    // Loop Variable

    variableName = "loopVariable";

    llvm::AllocaInst *variable = Builder->CreateAlloca(
        llvm::Type::getInt32Ty(*TheContext), nullptr, variableName.c_str());

    this->_irUtils->setNamedValueAlloca(variableName, variable,
                                        this->_NamedValuesAllocaStack);

    llvm::Value *result = this->generateEvaluateStatement(
        forStatement->getInitializationPtr().get());

    Builder->CreateStore(result, variable);

    this->_irUtils->setNamedValue(variableName, result,
                                  this->_NamedValuesStack);
  }

  if (variableName == "") {
    llvm::errs() << "Empty Variable Name: Error in for statement\n";
    return getNull();
  }

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();
  llvm::Value *exitValue = getNull();
  llvm::BasicBlock *loopCondition =
      llvm::BasicBlock::Create(*TheContext, "loopCondition", function);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "loopBody", function);
  llvm::BasicBlock *afterLoop =
      llvm::BasicBlock::Create(*TheContext, "afterLoop", function);

  llvm::BasicBlock *breakLoop =
      llvm::BasicBlock::Create(*TheContext, "breakLoop", function);

  Builder->CreateBr(loopCondition);

  // Loop Condition

  Builder->SetInsertPoint(loopCondition);

  this->_irUtils->decrementCountIfNotZero(ELANG_CONTINUE_COUNT);

  llvm::Value *variableValue =
      this->_irUtils->getNamedValue(variableName, this->_NamedValuesStack);

  llvm::AllocaInst *v = this->_irUtils->getNamedValueAlloca(
      variableName, this->_NamedValuesAllocaStack);

  llvm::Value *value = Builder->CreateLoad(variableValue->getType(), v);

  llvm::PHINode *conditionPHI =
      this->_irUtils->handleForLoopCondition(stepValue, value, upperBound);

  if (conditionPHI == nullptr) {

    llvm::errs() << "Error in Compiling for While condition\n";
    return this->_irUtils->getNullValue();
  }

  Builder->CreateCondBr(conditionPHI, breakLoop, afterLoop);

  Builder->SetInsertPoint(breakLoop);

  Builder->CreateCondBr(
      this->_irUtils->isCountZero(ELANG_BREAK_COUNT,
                                  llvm::Type::getInt32Ty(*TheContext)),
      loopBody, afterLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);
  llvm::Value *result =
      this->generateEvaluateStatement(forStatement->getStatementPtr().get());

  // Value incremented by Step

  llvm::Value *incrementedValue = Builder->CreateAdd(value, stepValue);

  this->_irUtils->updateNamedValue(variableName, incrementedValue,
                                   this->_NamedValuesStack);

  Builder->CreateStore(incrementedValue, v);

  Builder->CreateBr(loopCondition);

  // After Loop

  Builder->SetInsertPoint(afterLoop);

  this->_irUtils->decrementCountIfNotZero(ELANG_BREAK_COUNT);

  this->_NamedValuesAllocaStack.pop();
  this->_NamedValuesStack.pop();

  return exitValue;
}

llvm::Value *IRGenerator::generateEvaluateStatement(BoundStatement *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    return this->generateEvaluateExpressionStatement(
        ((BoundExpressionStatement *)node)->getExpressionPtr().get());
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

    return this->generateEvaluateBlockStatement((BoundBlockStatement *)node);
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

    return this->generateEvaluateVariableDeclaration(
        (BoundVariableDeclaration *)node);
  }
  case BinderKindUtils::BoundNodeKind::IfStatement: {

    return this->evaluateIfStatement((BoundIfStatement *)node);
  }

  case BinderKindUtils::BoundNodeKind::WhileStatement: {

    return this->evaluateWhileStatement((BoundWhileStatement *)node);
  }

  case BinderKindUtils::BoundNodeKind::ForStatement: {

    return this->evaluateForStatement((BoundForStatement *)node);
  }

  case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {

    // BoundFunctionDeclaration *functionDeclaration =
    //     (BoundFunctionDeclaration *)node;
    // this->defineFunction(functionDeclaration->functionSymbol.name,
    //                      functionDeclaration);

    // break;
  }

  case BinderKindUtils::BoundNodeKind::BreakStatement: {

    this->_irUtils->incrementCount(ELANG_BREAK_COUNT);

    return getNull();
  }
  case BinderKindUtils::BoundNodeKind::ContinueStatement: {

    this->_irUtils->incrementCount(ELANG_CONTINUE_COUNT);
    return getNull();
  }
  case BinderKindUtils::BoundNodeKind::ReturnStatement: {
    // BoundReturnStatement *returnStatement = (BoundReturnStatement *)node;

    // int &return_count = this->return_count_stack.top();
    // return_count = return_count + 1;
    // if (returnStatement->getReturnExpression() != nullptr) {
    //   this->last_value =
    //       this->evaluate<std::any>(returnStatement->getReturnExpression());
    // }
    break;
  }
  default: {
    // this->root->logs.push_back(node->getLineNumberAndColumn() +
    //                            "Error: Unexpected node" +
    //                            BinderKindUtils::to_string(node->getKind()));
  }
  }

  // this->root->variables = this->variable_stack.top();
  // this->root->functions = this->function_stack.top();
  return getNull();
}

int IRGenerator::executeGeneratedCode() {

  llvm::Function *evaluateBlockStatement =
      TheModule->getFunction("evaluateBlockStatement");

  std::string errorMessage;
  llvm::ExecutionEngine *executionEngine =
      llvm::EngineBuilder(std::move(TheModule))
          .setErrorStr(&errorMessage)
          .create();
  if (!executionEngine) {
    llvm::errs() << "Failed to create Execution Engine: " << errorMessage
                 << "\n";
  }

  // Step 2: Look up the function pointer
  if (!evaluateBlockStatement) {
    llvm::errs() << "Function not found in module.\n";
  }
  int hasError = 1;
  llvm::Type *returnType = evaluateBlockStatement->getReturnType();
  llvm::GenericValue resultValue = llvm::GenericValue();
  llvm::ArrayRef<llvm::GenericValue> ArgValues;
  try {
    resultValue =
        executionEngine->runFunction(evaluateBlockStatement, ArgValues);

    if (returnType->isIntegerTy()) {
      hasError = (resultValue.IntVal != 0) ? 1 : 0;
    }

    if (_environment == ENVIRONMENT::REPL) {
      std::cout << "\n";
    }

  } catch (const std::exception &e) {
    std::cerr << e.what();
  }

  // llvm::Type *returnType = evaluateBlockStatement->getReturnType();

  // if (returnType->isIntegerTy()) {
  //   if (returnType->getIntegerBitWidth() == 1) {
  //     //  llvm::outs() << "Boolean Value: "
  //     //   << (resultValue.IntVal != 0 ? "true" : "false") << "\n";

  //     output += (resultValue.IntVal != 0 ? "true" : "false");
  //   } else {
  //    // llvm::outs() << "Integer Value: " << resultValue.IntVal << "\n";
  //   }

  // } else if (returnType->isFloatingPointTy()) {
  //   if (returnType->isFloatTy()) {
  //     //llvm::outs() << "Float Value: " << resultValue.FloatVal << "\n";

  //   } else {
  //     llvm::outs() << "Double Value: " << resultValue.DoubleVal << "\n";
  //   }
  // } else if (returnType->isPointerTy()) {
  //   if (resultValue.PointerVal) {
  //     const char *stringValue =
  //         static_cast<const char *>(resultValue.PointerVal);
  //     output += stringValue;
  //   } else {
  //     // llvm::outs() << "Null Pointer Value\n";
  //     output += "Null Pointer Value\n";
  //   }
  // } else {
  //   //   llvm::outs() << "Unknown Value Type\n";
  //   output += "Unknown Value Type\n";
  // }
  delete executionEngine;
  return hasError;
}
