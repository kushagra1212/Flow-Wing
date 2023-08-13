#include "IRGenerator.h"

IRGenerator::IRGenerator(IRGenerator *previous,
                         CompilationUnitSyntax *_compilationUnit) {

  this->compilation_unit = _compilationUnit;

  this->previous = previous;
  TheContext = std::make_unique<llvm::LLVMContext>();
  TheModule = std::move(this->_getModule());
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  this->defineStandardFunctions();
}
BoundScopeGlobal *IRGenerator::getRoot() {
  if (root == nullptr) {
    if (previous != nullptr) {
      root = Binder::bindGlobalScope(previous->root, compilation_unit);
    } else {

      root = Binder::bindGlobalScope(nullptr, compilation_unit);
    }

    // this->variable_stack.push(this->root->variables);
    // this->function_stack.push(this->root->functions);
  }
  return root;
}

llvm::Value *
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

  return val;
}

llvm::Value *
IRGenerator::generateEvaluateUnaryExpressionFunction(BoundExpression *node) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
  llvm::Value *val =
      this->generateEvaluateExpressionStatement(unaryExpression->getOperand());
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

  switch (unaryExpression->getOperator()) {
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

  return result;
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

std::unique_ptr<llvm::Module> IRGenerator::_getModule() {
  std::string irCode = R"(
    declare i8* @malloc(i64)

    define i8* @concat_strings(i8* %str1, i8* %str2) {
        ; Get the lengths of the input strings
        %len1 = call i64 @strlen(i8* %str1)
        %len2 = call i64 @strlen(i8* %str2)
        
        ; Allocate memory for the concatenated string
        %totalLen = add i64 %len1, %len2
        %concatStr = call i8* @malloc(i64 %totalLen)
        
        ; Copy characters from the first string to the concatenated string
        %ptr1 = bitcast i8* %concatStr to i8*
        call void @memcpy(i8* %ptr1, i8* %str1, i64 %len1, i1 false)
        
        ; Copy characters from the second string to the concatenated string
        %ptr2 = getelementptr i8, i8* %ptr1, i64 %len1
        call void @memcpy(i8* %ptr2, i8* %str2, i64 %len2, i1 false)
        
        ret i8* %concatStr
    }

    declare i64 @strlen(i8*)
    declare void @memcpy(i8*, i8*, i64, i1)
)";

  llvm::SMDiagnostic err;
  std::unique_ptr<llvm::MemoryBuffer> buffer =
      llvm::MemoryBuffer::getMemBuffer(irCode);
  llvm::Expected<std::unique_ptr<llvm::Module>> parsedModule =
      llvm::parseIR(*buffer, err, *TheContext);

  if (!parsedModule) {
    llvm::errs() << "Error parsing IR: "
                 << llvm::toString(parsedModule.takeError()) << "\n";
    return nullptr;
  }

  std::unique_ptr<llvm::Module> module = std::move(*parsedModule);
  module->setSourceFileName("ElangModule");
  return std::move(module);
}

void IRGenerator::defineStandardFunctions() { this->define_StringLength(); }

llvm::Value *
IRGenerator::generateEvaluateVariableExpressionFunction(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  std::string variableName =
      IRUtils::getString(variableExpression->getIdentifierExpression());

  llvm::Value *variableValue = NamedValues[variableName];
  if (!variableValue) {
    // Variable not found, handle error
    return nullptr;
  }

  llvm::FunctionType *variableFunctionType =
      llvm::FunctionType::get(variableValue->getType(), false);

  llvm::Function *variableFunction = llvm::Function::Create(
      variableFunctionType, llvm::Function::ExternalLinkage,
      "evaluateVariableExpression", *TheModule);

  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", variableFunction);
  Builder->SetInsertPoint(entryBB);

  llvm::Value *returnValue = Builder->CreateRet(variableValue);

  llvm::verifyFunction(*variableFunction);

  return variableValue;
}

llvm::Value *IRGenerator::generateEvaluateAssignmentExpressionFunction(
    BoundExpression *node) {

  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;

  std::string variableName =
      IRUtils::getString(assignmentExpression->getLeft());

  llvm::Value *variableValue = NamedValues[variableName];
  if (!variableValue) {
    // Variable not found, handle error
    return nullptr;
  }

  llvm::Value *rhsValue =
      generateEvaluateExpressionStatement(assignmentExpression->getRight());
  if (!rhsValue) {
    // Error generating IR for the right-hand side expression
    return nullptr;
  }

  NamedValues[variableName] = rhsValue;

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

  return rhsValue;
}

llvm::Value *IRGenerator::generateEvaluateBinaryExpressionFunction(
    BoundBinaryExpression *node) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;

  llvm::Value *lhsValue = generateEvaluateExpressionStatement(node->getLeft());
  llvm::Value *rhsValue = generateEvaluateExpressionStatement(node->getRight());

  if (!lhsValue || !rhsValue) {
    // Handle error in generating IR for operands
    return nullptr;
  }

  llvm::FunctionType *binaryFunctionType =
      llvm::FunctionType::get(lhsValue->getType(), false);

  llvm::Function *binaryFunction = llvm::Function::Create(
      binaryFunctionType, llvm::Function::ExternalLinkage,
      "evaluateBinaryExpression", *TheModule);

  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", binaryFunction);
  Builder->SetInsertPoint(entryBB);
  llvm::Value *result = nullptr;

  if (IRUtils::isStringType(lhsValue->getType()) ||
      IRUtils::isStringType(rhsValue->getType())) {
    if (IRUtils::isStringType(lhsValue->getType()) &&
        IRUtils::isStringType(rhsValue->getType()))
      result = IRUtils::concatenateStrings(lhsValue, rhsValue, TheModule.get(),
                                           Builder.get());
    else if (IRUtils::isStringType(lhsValue->getType())) {

      // convert rhsValue is of llvm::Value type convert it to llvm::Value
      // string

      result = IRUtils::concatenateStrings(
          lhsValue, IRUtils::convertToI8Pointer(rhsValue, Builder.get()),
          TheModule.get(), Builder.get());
    } else {
      result = IRUtils::concatenateStrings(
          IRUtils::convertToI8Pointer(lhsValue, Builder.get()), rhsValue,
          TheModule.get(), Builder.get());
    }

  } else {
    switch (node->getOperator()) {
    case BinderKindUtils::BoundBinaryOperatorKind::Addition:
      result = Builder->CreateAdd(lhsValue, rhsValue);
      break;
    case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
      result = Builder->CreateSub(lhsValue, rhsValue);
      break;
    case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
      result = Builder->CreateMul(lhsValue, rhsValue);
      break;
    case BinderKindUtils::BoundBinaryOperatorKind::Division:
      result = Builder->CreateSDiv(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
      result = Builder->CreateSRem(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
      result = Builder->CreateAnd(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
      result = Builder->CreateOr(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
      result = Builder->CreateXor(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
      result = Builder->CreateAnd(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
      result = Builder->CreateOr(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::Equals:
      result = Builder->CreateICmpEQ(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
      result = Builder->CreateICmpNE(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::Less:
      result = Builder->CreateICmpSLT(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

      result = Builder->CreateICmpSLE(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::Greater:
      result = Builder->CreateICmpSGT(lhsValue, rhsValue);
      break;

    case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
      result = Builder->CreateICmpSGE(lhsValue, rhsValue);
      break;

    // Add more cases for other binary operators
    default:
      // Handle unsupported binary operator
      return nullptr;
    }
  }
  llvm::Value *returnValue = Builder->CreateRet(result);

  llvm::verifyFunction(*binaryFunction);

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
    BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;
    return this->generateEvaluateBinaryExpressionFunction(binaryExpression);
  }
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {
    BoundParenthesizedExpression *parenthesizedExpression =
        (BoundParenthesizedExpression *)node;
    return this->generateEvaluateExpressionStatement(
        parenthesizedExpression->getExpression());
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {
    return nullptr;
  }

  default: {

    return nullptr;
  }
  }
}

llvm::Value *
IRGenerator::generateEvaluateBlockStatement(BoundBlockStatement *node) {

  llvm::Value *result = nullptr;
  std::map<std::string, llvm::Value *> originalNamedValues = NamedValues;

  for (int i = 0; i < node->getStatements().size(); i++) {
    result = this->generateEvaluateStatement(node->getStatements()[i]);
  }
  NamedValues = originalNamedValues;

  return result;
}

llvm::Value *IRGenerator::generateEvaluateStatement(BoundStatement *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::ExpressionStatement: {

    return this->generateEvaluateExpressionStatement(
        ((BoundExpressionStatement *)node)->getExpression());
    break;
  }
  case BinderKindUtils::BoundNodeKind::BlockStatement: {

    return this->generateEvaluateBlockStatement((BoundBlockStatement *)node);
    break;
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

    // this->evaluateVariableDeclaration((BoundVariableDeclaration *)node);

    // break;
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
  // Initialize LLVM
  // std::vector<std::string> functionNames = {"malloc", "concat_strings",
  //                                           "strlen", "memcpy"};

  // for (const std::string &funcName : functionNames) {
  //   llvm::Function *function = TheModule->getFunction(funcName);

  //   if (function) {
  //     std::cout << "Function " << funcName << " is defined in the module.\n";
  //     std::cout << "Function IR:\n";
  //     function->print(llvm::errs());
  //   } else {
  //     std::cout << "Function " << funcName
  //               << " is not defined in the module.\n";
  //   }
  // }
  llvm::Function *evaluateBlockStatement =
      TheModule->getFunction("evaluateBinaryExpression");
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
    llvm::outs() << "Integer Value: " << resultValue.IntVal << "\n";
  } else if (returnType->isFloatingPointTy()) {
    llvm::outs() << "Floating-Point Value: " << resultValue.FloatVal << "\n";
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
