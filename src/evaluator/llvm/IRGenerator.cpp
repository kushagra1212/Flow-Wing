#include "IRGenerator.h"

IRGenerator::IRGenerator() {

  TheContext = std::make_unique<llvm::LLVMContext>();
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
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
      "../../../src/evaluator/IRFiles/functions.ll"};
  TheModule = std::move(this->_getModule(irFilePaths));
}

llvm::Value *
IRGenerator::generateEvaluateLiteralExpressionFunction(BoundExpression *node) {

  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();

  llvm::Value *val = IRUtils::getLLVMValue(value, TheModule.get(),
                                           TheContext.get(), Builder.get());
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

void IRGenerator::defineStandardFunctions() {}

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

llvm::Function *IRGenerator::getFunction(llvm::Type *Result, std::string name,
                                         bool isVarArg = false) {
  llvm::FunctionType *functionType = llvm::FunctionType::get(Result, isVarArg);

  llvm::Function *function = llvm::Function::Create(
      functionType, llvm::Function::ExternalLinkage, name, *TheModule);

  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", function);
  Builder->SetInsertPoint(entryBB);

  return function;
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

    result = IRUtils::concatenateStrings(
        IRUtils::convertToString(lhsValue, Builder.get()),
        IRUtils::convertToString(rhsValue, Builder.get()), TheModule.get(),
        Builder.get());
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

llvm::Value *IRGenerator::generateEvaluateBlockStatement(
    llvm::BasicBlock *currentBlock, BoundBlockStatement *blockStatement) {
  llvm::Value *returnValue = nullptr;
  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());

  llvm::BasicBlock *nestedBlock = llvm::BasicBlock::Create(
      *TheContext, "nestedBlock", currentBlock->getParent());

  // create and load variable
  Builder->SetInsertPoint(currentBlock);
  Builder->CreateBr(nestedBlock);
  Builder->SetInsertPoint(nestedBlock);
  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    llvm::Value *res = this->generateEvaluateStatement(
        nestedBlock, blockStatement->getStatements()[i].get());

    if (blockStatement->getStatements()[i].get()->getKind() !=
        BinderKindUtils::BoundNodeKind::BlockStatement) {
      llvm::AllocaInst *allocaInst =
          Builder->CreateAlloca(res->getType(), nullptr, "toReturn");
      Builder->CreateStore(res, allocaInst);
    }
    returnValue = res;
  }
  Builder->SetInsertPoint(currentBlock);
  this->_NamedValuesStack.pop();
  this->_NamedValuesAllocaStack.pop();

  return returnValue;
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

void IRGenerator::generateEvaluateGlobalStatement(BoundStatement *node) {

  BoundBlockStatement *blockStatement = (BoundBlockStatement *)node;
  llvm::Value *returnValue = nullptr;
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateBlockStatement", *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  // Builder->SetInsertPoint(entryBlock);
  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    llvm::Value *res = this->generateEvaluateStatement(
        entryBlock, blockStatement->getStatements()[i].get());
    returnValue = res;
  }
  Builder->CreateRet(returnValue);
}

llvm::Value *
IRGenerator::generateEvaluateStatement(llvm::BasicBlock *basicBlock,
                                       BoundStatement *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    return this->generateEvaluateExpressionStatement(
        ((BoundExpressionStatement *)node)->getExpressionPtr().get());
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

    return this->generateEvaluateBlockStatement(basicBlock,
                                                (BoundBlockStatement *)node);
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

    return this->generateEvaluateVariableDeclaration(
        (BoundVariableDeclaration *)node);
  }
  case BinderKindUtils::BoundNodeKind::IfStatement: {

    // this->evaluateIfStatement((BoundIfStatement *)node);
    // break;
  }

  case BinderKindUtils::BoundNodeKind::WhileStatement: {

    // this->evaluateWhileStatement((BoundWhileStatement *)node);
    // break;
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
    // break_count++;
    // break;
  }
  case BinderKindUtils::BoundNodeKind::ContinueStatement: {
    // continue_count++;
    // break;
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

void IRGenerator::executeGeneratedCode() {

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
    return;
  }

  // Step 2: Look up the function pointer
  if (!evaluateBlockStatement) {
    llvm::errs() << "Function not found in module.\n";
    return;
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

  // Result Can be of Any Data Type

  // Print the result based on its data type

  if (returnType->isIntegerTy()) {
    if (returnType->getIntegerBitWidth() == 1) {
      llvm::outs() << "Boolean Value: "
                   << (resultValue.IntVal != 0 ? "true" : "false") << "\n";
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
      llvm::outs() << "String Value: " << stringValue << "\n";
    } else {
      llvm::outs() << "Null Pointer Value\n";
    }
  } else {
    llvm::outs() << "Unknown Value Type\n";
  }
  delete executionEngine;
}
