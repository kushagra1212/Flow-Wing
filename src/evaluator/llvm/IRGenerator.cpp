#include "IRGenerator.h"

IRGenerator::IRGenerator() {

  TheContext = std::make_unique<llvm::LLVMContext>();
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
  TheModule = std::make_unique<llvm::Module>("Elang", *TheContext);

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

  llvm::Value *val = IRUtils::getLLVMValue(value, TheModule.get(),
                                           TheContext.get(), Builder.get());

  // create and Store

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(val->getType(), nullptr, "literal");

  Builder->CreateStore(val, variable);
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
      trueStr, "true_string");

  llvm::Constant *falseStr =
      llvm::ConstantDataArray::getString(*TheContext, "false");
  llvm::GlobalVariable *globalFalseStr = new llvm::GlobalVariable(
      *TheModule, falseStr->getType(), true, llvm::GlobalValue::ExternalLinkage,
      falseStr, "false_string");

  llvm::PointerType *int8PtrType = llvm::Type::getInt8PtrTy(*TheContext);
  llvm::GlobalVariable *globalNullPtr = new llvm::GlobalVariable(
      *TheModule, int8PtrType, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantPointerNull::get(int8PtrType), "null_ptr");
}

llvm::Value *
IRGenerator::generateEvaluateVariableExpressionFunction(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  std::string variableName = IRUtils::getString(
      variableExpression->getIdentifierExpressionPtr().get());

  llvm::Value *variableValue =
      IRUtils::getNamedValue(variableName, this->_NamedValuesStack);

  if (!variableValue) {
    // Variable not found, handle error

    llvm::errs() << "Variable not found\n";
    return nullptr;
  }

  return variableValue;
}
llvm::Value *IRGenerator::generateEvaluateAssignmentExpressionFunction(
    BoundExpression *node) {

  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;

  std::string variableName =
      IRUtils::getString(assignmentExpression->getLeftPtr().get());

  if (!IRUtils::getNamedValue(variableName, this->_NamedValuesStack)) {
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

  IRUtils::updateNamedValue(variableName, rhsValue, this->_NamedValuesStack);

  Builder->CreateStore(
      rhsValue, IRUtils::getNamedValueAlloca(variableName,
                                             this->_NamedValuesAllocaStack));

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
  if (IRUtils::isStringType(lhsType) || IRUtils::isStringType(rhsType)) {

    result = IRUtils::getResultFromBinaryOperationOnString(
        IRUtils::convertToString(lhsValue, Builder.get()),
        IRUtils::convertToString(rhsValue, Builder.get()), Builder.get(),
        TheModule.get(), TheContext.get(), binaryExpression);
  } else if (IRUtils::isDoubleType(lhsType) || IRUtils::isDoubleType(rhsType)) {

    result = IRUtils::getResultFromBinaryOperationOnDouble(
        IRUtils::convertToDouble(lhsValue, Builder.get()),
        IRUtils::convertToDouble(rhsValue, Builder.get()), Builder.get(),
        TheModule.get(), binaryExpression);
  } else if (IRUtils::isBoolType(lhsType) && IRUtils::isBoolType(rhsType)) {

    result = IRUtils::getResultFromBinaryOperationOnBool(
        lhsValue, rhsValue, Builder.get(), TheModule.get(), binaryExpression);
  } else {

    result = IRUtils::getResultFromBinaryOperationOnInt(
        IRUtils::convertToInt(lhsValue, Builder.get()),
        IRUtils::convertToInt(rhsValue, Builder.get()), Builder.get(),
        TheModule.get(), binaryExpression);
  }
  return result;
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
    return nullptr;
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

  IRUtils::setNamedValue(variable_name, result, this->_NamedValuesStack);

  // create and load variable

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(result->getType(), nullptr, variable_name.c_str());

  IRUtils::setNamedValueAlloca(variable_name, variable,
                               this->_NamedValuesAllocaStack);

  Builder->CreateStore(result, variable);

  return result;
}
llvm::Constant *IRGenerator::getNull() {
  llvm::Type *int8PtrType = llvm::Type::getInt8PtrTy(*TheContext);
  return llvm::ConstantExpr::getBitCast(
      IRUtils::getNullValue(TheModule.get(), TheContext.get(), Builder.get()),
      int8PtrType);
}

llvm::Value *IRGenerator::generateEvaluateBlockStatement(
    llvm::BasicBlock *currentBlock, llvm::BasicBlock *returnBlock,
    BoundBlockStatement *blockStatement) {
  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());

  // create and load variable
  llvm::BasicBlock *nestedBlock = llvm::BasicBlock::Create(
      *TheContext, "nestedBlock", currentBlock->getParent());

  llvm::BasicBlock *exitBlock = llvm::BasicBlock::Create(
      *TheContext, "exitBlock", nestedBlock->getParent());
  Builder->CreateBr(nestedBlock);
  Builder->SetInsertPoint(nestedBlock);
  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    llvm::Value *res = this->generateEvaluateStatement(
        nestedBlock, exitBlock, blockStatement->getStatements()[i].get());
  }
  Builder->CreateBr(exitBlock);
  this->_NamedValuesStack.pop();
  this->_NamedValuesAllocaStack.pop();

  Builder->SetInsertPoint(exitBlock);

  return getNull();
}

void IRGenerator::generateEvaluateGlobalStatement(BoundStatement *node) {

  BoundBlockStatement *blockStatement = (BoundBlockStatement *)node;
  llvm::Value *returnValue = getNull();
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateBlockStatement", *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", F);
  Builder->SetInsertPoint(entryBlock);
  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    llvm::Value *res = this->generateEvaluateStatement(
        entryBlock, returnBlock, blockStatement->getStatements()[i].get());

    if (i == blockStatement->getStatements().size() - 1 &&
        blockStatement->getStatements()[i].get()->getKind() ==
            BinderKindUtils::BoundNodeKind::ExpressionStatement) {
      returnValue = res;
    }
  }

  Builder->CreateBr(returnBlock);

  Builder->SetInsertPoint(returnBlock);
  Builder->CreateRet(IRUtils::convertToString(returnValue, Builder.get()));
}

llvm::Value *IRGenerator::evaluateIfStatement(llvm::BasicBlock *basicBlock,
                                              llvm::BasicBlock *returnBlock,
                                              BoundStatement *node) {
  BoundIfStatement *ifStatement = (BoundIfStatement *)node;

  llvm::Value *conditionValue = this->generateEvaluateExpressionStatement(
      ifStatement->getConditionPtr().get());

  if (conditionValue == nullptr) {
    llvm::errs() << "Error in Compiling for if condition\n";
    return nullptr;
  }

  llvm::Function *function = basicBlock->getParent();

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

  llvm::BasicBlock *endBlock =
      llvm::BasicBlock::Create(*TheContext, "end", function);

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

  llvm::Value *thenValue = this->generateEvaluateStatement(
      thenBlock, returnBlock, ifStatement->getThenStatementPtr().get());

  Builder->CreateBr(endBlock);

  // Or If Then Block

  std::vector<llvm::Value *> orIfThenValues;

  for (int i = 0; i < orIfThenBlocks.size(); i++) {
    Builder->SetInsertPoint(orIfThenBlocks[i]);

    llvm::Value *orIfThenValue =
        this->generateEvaluateStatement(orIfThenBlocks[i], returnBlock,
                                        ifStatement->getOrIfStatementsPtr()[i]
                                            .get()
                                            ->getThenStatementPtr()
                                            .get());

    orIfThenValues.push_back(orIfThenValue);

    Builder->CreateBr(endBlock);
  }

  // ELSE BLOCK

  Builder->SetInsertPoint(elseBlock);

  llvm::Value *elseValue = nullptr;
  if (ifStatement->getElseStatementPtr().get()) {
    elseValue = this->generateEvaluateStatement(
        elseBlock, returnBlock, ifStatement->getElseStatementPtr().get());
  } else {
    llvm::Type *int8PtrType = llvm::Type::getInt8PtrTy(*TheContext);
    elseValue = llvm::ConstantExpr::getBitCast(
        IRUtils::getNullValue(TheModule.get(), TheContext.get(), Builder.get()),
        int8PtrType);
  }
  Builder->CreateBr(endBlock);

  // END BLOCK

  Builder->SetInsertPoint(endBlock);
  // llvm::PHINode *phiNode = Builder->CreatePHI(
  //     llvm::Type::getInt8PtrTy(*TheContext), 2 + orIfBlock.size());

  // phiNode->addIncoming(IRUtils::convertToString(thenValue, Builder.get()),
  //                      thenBlock);

  // for (int i = 0; i < orIfThenBlocks.size(); i++) {
  //   phiNode->addIncoming(
  //       IRUtils::convertToString(orIfThenValues[i], Builder.get()),
  //       orIfThenBlocks[i]);
  // }

  // phiNode->addIncoming(IRUtils::convertToString(elseValue, Builder.get()),
  //                      elseBlock);
  return getNull();
}

llvm::Value *IRGenerator::evaluateWhileStatement(llvm::BasicBlock *basicBlock,
                                                 llvm::BasicBlock *returnBlock,
                                                 BoundWhileStatement *node) {
  BoundWhileStatement *whileStatement = (BoundWhileStatement *)node;

  llvm::Function *function = basicBlock->getParent();

  llvm::BasicBlock *loopCondition =
      llvm::BasicBlock::Create(*TheContext, "loopCondition", function);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "loopBody", function);
  llvm::BasicBlock *afterLoop =
      llvm::BasicBlock::Create(*TheContext, "afterLoop", function);

  Builder->CreateBr(loopCondition);

  // Loop Condition

  Builder->SetInsertPoint(loopCondition);
  llvm::Value *conditionValue = this->generateEvaluateExpressionStatement(
      whileStatement->getConditionPtr().get());

  if (conditionValue == nullptr) {
    llvm::errs() << "Error in Compiling for While condition\n";
    return IRUtils::getNullValue(TheModule.get(), TheContext.get(),
                                 Builder.get());
  }

  Builder->CreateCondBr(conditionValue, loopBody, afterLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);
  llvm::Value *result = this->generateEvaluateStatement(
      basicBlock, returnBlock, whileStatement->getBodyPtr().get());

  Builder->CreateBr(loopCondition);

  // After Loop

  Builder->SetInsertPoint(afterLoop);

  return result;
}

llvm::Value *
IRGenerator::generateEvaluateStatement(llvm::BasicBlock *basicBlock,
                                       llvm::BasicBlock *returnBlock,
                                       BoundStatement *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    return this->generateEvaluateExpressionStatement(
        ((BoundExpressionStatement *)node)->getExpressionPtr().get());
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

    return this->generateEvaluateBlockStatement(basicBlock, returnBlock,
                                                (BoundBlockStatement *)node);
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

    return this->generateEvaluateVariableDeclaration(
        (BoundVariableDeclaration *)node);
  }
  case BinderKindUtils::BoundNodeKind::IfStatement: {

    return this->evaluateIfStatement(basicBlock, returnBlock,
                                     (BoundIfStatement *)node);
  }

  case BinderKindUtils::BoundNodeKind::WhileStatement: {

    return this->evaluateWhileStatement(basicBlock, returnBlock,
                                        (BoundWhileStatement *)node);
  }

  case BinderKindUtils::BoundNodeKind::ForStatement: {

    // this->evaluateForStatement((BoundForStatement *)node);
    // break;
  }

  case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {

    // BoundFunctionDeclaration *functionDeclaration =
    //     (BoundFunctionDeclaration *)node;
    // this->defineFunction(functionDeclaration->functionSymbol.name,
    //                      functionDeclaration);

    // break;
  }

  case BinderKindUtils::BoundNodeKind::BreakStatement: {

    Builder->CreateBr(returnBlock);

    return IRUtils::getNullValue(TheModule.get(), TheContext.get(),
                                 Builder.get());
  }
  case BinderKindUtils::BoundNodeKind::ContinueStatement: {

    return IRUtils::getNullValue(TheModule.get(), TheContext.get(),
                                 Builder.get());
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
  return nullptr;
}

std::string IRGenerator::executeGeneratedCode() {
  std::string output = "";

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
    return "Failed to create Execution Engine: " + errorMessage + "\n";
  }

  // Step 2: Look up the function pointer
  if (!evaluateBlockStatement) {
    llvm::errs() << "Function not found in module.\n";
    return "Function not found in module.\n";
  }
  llvm::GenericValue resultValue = llvm::GenericValue();

  // Step 3: Call the function
  std::vector<llvm::GenericValue> noArgs;
  try {
    resultValue = executionEngine->runFunction(evaluateBlockStatement, noArgs);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  llvm::Type *returnType = evaluateBlockStatement->getReturnType();

  if (returnType->isIntegerTy()) {
    if (returnType->getIntegerBitWidth() == 1) {
      //  llvm::outs() << "Boolean Value: "
      //   << (resultValue.IntVal != 0 ? "true" : "false") << "\n";

      output += (resultValue.IntVal != 0 ? "true" : "false");
    } else {
      llvm::outs() << "Integer Value: " << resultValue.IntVal << "\n";
    }

  } else if (returnType->isFloatingPointTy()) {
    if (returnType->isFloatTy()) {
      llvm::outs() << "Float Value: " << resultValue.FloatVal << "\n";

    } else {
      llvm::outs() << "Double Value: " << resultValue.DoubleVal << "\n";
    }
  } else if (returnType->isPointerTy()) {
    if (resultValue.PointerVal) {
      const char *stringValue =
          static_cast<const char *>(resultValue.PointerVal);
      output += stringValue;
    } else {
      // llvm::outs() << "Null Pointer Value\n";
      output += "Null Pointer Value\n";
    }
  } else {
    //   llvm::outs() << "Unknown Value Type\n";
    output += "Unknown Value Type\n";
  }
  delete executionEngine;

  return output;
}
