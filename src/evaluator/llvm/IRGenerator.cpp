#include "IRGenerator.h"

IRGenerator::IRGenerator() {

  TheContext = std::make_unique<llvm::LLVMContext>();
  std::vector<std::string> irFilePaths = {
      "../../../src/evaluator/IRFiles/functions.ll"};
  TheModule = std::move(this->_getModule(irFilePaths));
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  this->defineStandardFunctions();
}

llvm::Function *
IRGenerator::generateEvaluateLiteralExpressionFunction(BoundExpression *node) {

  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();

  llvm::Value *val = IRUtils::getLLVMValue(value, TheModule.get(),
                                           TheContext.get(), Builder.get());
  if (val == nullptr) {
    return nullptr;
  }
  llvm::FunctionType *FT = llvm::FunctionType::get(val->getType(), false);
  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateLiteralExpression", *TheModule);
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(BB);

  llvm::Value *V = Builder->CreateRet(val);
  llvm::verifyFunction(*F);
  // Print LLVM IR to console

  return F;
}

llvm::Function *
IRGenerator::generateEvaluateUnaryExpressionFunction(BoundExpression *node) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
  llvm::Value *val = this->generateEvaluateExpressionStatement(
      unaryExpression->getOperandPtr().get());
  if (val == nullptr) {
    return nullptr;
  }

  llvm::FunctionType *FT = nullptr;

  switch (unaryExpression->getOperator()) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
    FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), false);
    break;
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    FT = llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext), false);
    break;
  default:
    return nullptr;
  }

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateUnaryExpression", *TheModule);

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(BB);

  llvm::Value *result = nullptr;

  switch (unaryExpression->getOperatorPtr()) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
    result = Builder->CreateAdd(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));
    break;

  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
    result = Builder->CreateSub(
        llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)), val);
    break;

  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    FT = llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext), false);

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
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
    result = Builder->CreateXor(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, -1, true)));
    break;

  default:

    return nullptr;
  }

  llvm::Value *V = Builder->CreateRet(result);

  llvm::verifyFunction(*F);

  return F;
}

void IRGenerator::printIR() {
  // Print LLVM IR to console
  TheModule->print(llvm::outs(), nullptr);
}

void IRGenerator::define_StringLength() {
  llvm::Type *int32Type = llvm::Type::getInt32Ty(*TheContext);
  llvm::Type *int8PointerType = llvm::Type::getInt8PtrTy(*TheContext);

  std::vector<llvm::Type *> args = {int8PointerType};
  llvm::FunctionType *stringLengthFuncType =
      llvm::FunctionType::get(int32Type, args, false);

  llvm::Function *stringLengthFunc = llvm::Function::Create(
      stringLengthFuncType, llvm::Function::ExternalLinkage, "stringLength",
      *TheModule);

  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", stringLengthFunc);
  Builder->SetInsertPoint(entryBB);

  llvm::Argument *strArg = stringLengthFunc->arg_begin();
  strArg->setName("str");

  // Implement the rest of the string length calculation here
  llvm::AllocaInst *length = Builder->CreateAlloca(int32Type);
  Builder->CreateStore(llvm::ConstantInt::get(int32Type, 0), length);

  // Return the final length
  llvm::LoadInst *finalLength = Builder->CreateLoad(int32Type, length);
  Builder->CreateRet(finalLength);
}

std::unique_ptr<llvm::Module>
IRGenerator::_getModule(const std::vector<std::string> &irFilePaths) {
  llvm::SMDiagnostic err;
  llvm::SourceMgr sourceMgr;

  std::unique_ptr<llvm::Module> module = nullptr;

  for (const std::string &filePath : irFilePaths) {
    llvm::Expected<std::unique_ptr<llvm::Module>> parsedModule =
        llvm::parseIRFile(filePath, err, *TheContext);

    if (!parsedModule->get()) {
      llvm::errs() << "Error parsing IR file " << filePath << ": "
                   << llvm::toString(parsedModule.takeError()) << "\n";
      continue; // Skip this file and continue with the next one
    }
    std::unique_ptr<llvm::Module> parsedModulePtr =
        std::move(parsedModule.get());

    module = std::move(parsedModulePtr);
    return std::move(module);

    // Append functions from the parsed module to the current module
    llvm::Module::FunctionListType &funcList =
        parsedModulePtr->getFunctionList();

    while (!funcList.empty()) {
      llvm::Function &func = funcList.front();
      funcList.pop_front();

      module->getFunctionList().push_back(&func);
    }

    // Append global variables from the parsed module to the current module
    llvm::Module::GlobalListType &globalList = parsedModulePtr->getGlobalList();

    while (!globalList.empty()) {
      llvm::GlobalVariable &global = globalList.front();
      globalList.pop_front();

      module->getGlobalList().push_back(&global);
    }
  }

  return std::move(module);
}

void IRGenerator::defineStandardFunctions() { this->define_StringLength(); }
llvm::Function *
IRGenerator::generateEvaluateVariableExpressionFunction(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  std::string variableName = IRUtils::getString(
      variableExpression->getIdentifierExpressionPtr().get());

  llvm::Value *variableValue = _NamedValues[variableName];
  if (!variableValue) {
    // Variable not found, handle error

    llvm::errs() << "Variable not found\n";
    return nullptr;
  }

  llvm::FunctionType *variableFunctionType =
      llvm::FunctionType::get(variableValue->getType(), false);

  llvm::Function *variableFunction = llvm::Function::Create(
      variableFunctionType, llvm::Function::ExternalLinkage,
      "evaluateVariableExpression", *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", variableFunction);

  Builder->SetInsertPoint(entryBlock);

  llvm::Value *loadedValue = Builder->CreateLoad(
      variableValue->getType(), TheModule->getGlobalVariable(variableName),
      variableName.c_str());
  Builder->CreateRet(loadedValue);

  llvm::verifyFunction(*variableFunction);

  return variableFunction;
}
llvm::Function *IRGenerator::generateEvaluateAssignmentExpressionFunction(
    BoundExpression *node) {

  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;

  std::string variableName =
      IRUtils::getString(assignmentExpression->getLeftPtr().get());

  llvm::Value *variableValue = _NamedValues[variableName];
  if (!variableValue) {
    // Variable not found, handle error
    return nullptr;
  }

  llvm::Value *rhsValue = generateEvaluateExpressionStatement(
      assignmentExpression->getRightPtr().get());
  if (!rhsValue) {
    // Error generating IR for the right-hand side expression
    return nullptr;
  }

  _NamedValues[variableName] = rhsValue;

  llvm::FunctionType *assignmentFunctionType =
      llvm::FunctionType::get(rhsValue->getType(), false);

  llvm::Function *assignmentFunction = llvm::Function::Create(
      assignmentFunctionType, llvm::Function::ExternalLinkage,
      "evaluateAssignmentExpression", *TheModule);

  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", assignmentFunction);
  Builder->SetInsertPoint(entryBB);

  llvm::Value *returnValue = Builder->CreateRet(rhsValue);

  llvm::verifyFunction(*assignmentFunction);

  return assignmentFunction;
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

llvm::Function *IRGenerator::generateEvaluateBinaryExpressionFunction(
    BoundBinaryExpression *node) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;

  llvm::Function *lhsFun =
      generateEvaluateExpressionStatement(binaryExpression->getLeftPtr().get());
  llvm::Function *rhsFun = generateEvaluateExpressionStatement(
      binaryExpression->getRightPtr().get());

  if (!lhsFun || !rhsFun) {
    llvm::errs() << "Error in generating IR for operands\n";
    return nullptr;
  }

  llvm::Type *lhsType = lhsFun->getReturnType();
  llvm::Type *rhsType = rhsFun->getReturnType();
  llvm::Function *binaryFunction = nullptr;
  const std::string &functionName = "evaluateBinaryExpression";
  llvm::Value *lhsValue = nullptr;
  llvm::Value *rhsValue = nullptr;

  auto assignValues = [&](llvm::Type *_type) {
    binaryFunction = getFunction(_type, functionName);
    lhsValue = Builder->CreateCall(lhsFun);
    rhsValue = Builder->CreateCall(rhsFun);

    if (!lhsValue || !rhsValue) {
      llvm::errs() << "Error in generating IR for operands\n";
      return false;
    }
    return true;
  };
  llvm::Value *result = nullptr;
  if (IRUtils::isStringType(lhsType) || IRUtils::isStringType(rhsType)) {

    if (!assignValues(llvm::Type::getInt8PtrTy(*TheContext))) {
      return nullptr;
    }
    result = IRUtils::concatenateStrings(
        IRUtils::convertToString(lhsValue, Builder.get()),
        IRUtils::convertToString(rhsValue, Builder.get()), TheModule.get(),
        Builder.get());
  } else if (IRUtils::isDoubleType(lhsType) || IRUtils::isDoubleType(rhsType)) {

    if (!assignValues(llvm::Type::getDoubleTy(*TheContext))) {
      return nullptr;
    }

    result = IRUtils::getResultFromBinaryOperationOnDouble(
        IRUtils::convertToDouble(lhsValue, Builder.get()),
        IRUtils::convertToDouble(rhsValue, Builder.get()), Builder.get(),
        TheModule.get(), binaryExpression);
  } else if (IRUtils::isBoolType(lhsType) && IRUtils::isBoolType(rhsType)) {

    if (!assignValues(llvm::Type::getInt1Ty(*TheContext))) {
      return nullptr;
    }
    result = IRUtils::getResultFromBinaryOperationOnBool(
        lhsValue, rhsValue, Builder.get(), TheModule.get(), binaryExpression);
  } else {
    if (!assignValues(llvm::Type::getInt32Ty(*TheContext))) {
      return nullptr;
    }
    result = IRUtils::getResultFromBinaryOperationOnInt(
        IRUtils::convertToInt(lhsValue, Builder.get()),
        IRUtils::convertToInt(rhsValue, Builder.get()), Builder.get(),
        TheModule.get(), binaryExpression);
  }
  llvm::Value *returnValue = Builder->CreateRet(result);
  llvm::verifyFunction(*binaryFunction);
  return binaryFunction;
}
llvm::Function *
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

llvm::Function *
IRGenerator::generateEvaluateBlockStatement(BoundBlockStatement *node) {

  std::map<std::string, llvm::Value *> originalNamedValues = _NamedValues;
  std::vector<llvm::Function *> functions;

  llvm::Value *returnValue = nullptr;

  for (int i = 0; i < node->getStatements().size(); i++) {

    llvm::Function *f =
        this->generateEvaluateStatement(node->getStatements()[i].get());

    functions.push_back(f);
  }

  llvm::FunctionType *FT = llvm::FunctionType::get(
      functions[functions.size() - 1]->getReturnType(), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateBlockStatement", *TheModule);

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(BB);
  for (int i = 0; i < functions.size(); i++) {
    llvm::Value *res = Builder->CreateCall(functions[i]);
    returnValue = res;
  }

  Builder->CreateRet(returnValue);
  if (!node->getGlobal())
    _NamedValues = originalNamedValues;
  llvm::verifyFunction(*F);
  return F;
}

llvm::Function *IRGenerator::generateEvaluateVariableDeclaration(
    BoundVariableDeclaration *node) {

  std::string variable_name = node->getVariable();
  llvm::Function *initilizerFunction =
      this->generateEvaluateExpressionStatement(
          node->getInitializerPtr().get());

  llvm::FunctionType *FT =
      llvm::FunctionType::get(initilizerFunction->getReturnType(), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             "evaluateVariableDeclaration", *TheModule);

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(BB);
  llvm::Value *result = Builder->CreateCall(initilizerFunction);

  _NamedValues[variable_name] = result;

  // create and load variable

  llvm::Value *variable =
      Builder->CreateAlloca(result->getType(), nullptr, variable_name.c_str());

  Builder->CreateStore(result, variable);

  llvm::Value *returnValue = Builder->CreateRet(result);

  llvm::verifyFunction(*F);
  return F;
}

llvm::Function *IRGenerator::generateEvaluateStatement(BoundStatement *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    return this->generateEvaluateExpressionStatement(
        ((BoundExpressionStatement *)node)->getExpressionPtr().get());
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

    return this->generateEvaluateBlockStatement(((BoundBlockStatement *)node));
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
