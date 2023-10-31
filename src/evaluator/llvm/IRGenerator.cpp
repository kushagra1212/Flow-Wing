#include "IRGenerator.h"

IRGenerator::IRGenerator(
    int environment, DiagnosticHandler *diagnosticHandler,
    std::map<std::string, BoundFunctionDeclaration *> boundedUserFunctions,
    const std::string sourceFileName) {

  TheContext = std::make_unique<llvm::LLVMContext>();
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
  TheModule = std::make_unique<llvm::Module>("FlowWing", *TheContext);
  _environment = environment;
  this->_diagnosticHandler = diagnosticHandler;
  this->_irParser = std::make_unique<IRParser>();

  this->_irUtils = std::make_unique<IRUtils>(
      TheModule.get(), Builder.get(), TheContext.get(),
      this->_diagnosticHandler, sourceFileName);

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  this->declareDependencyFunctions();
  this->initializeGlobalVariables();

  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());

  this->_boundedUserFunctions = boundedUserFunctions;
}

void IRGenerator::updateModule() {
  std::vector<std::string> irFilePaths = {
      "../../../src/evaluator/BuiltinIRs/built_in_module.ll"};

  for (const std::string &path : irFilePaths) {
    llvm::SMDiagnostic err;
    bool LinkResult = llvm::Linker::linkModules(
        *TheModule, llvm::parseIRFile(path, err, *TheContext));
    if (LinkResult) {
      llvm::errs() << "Error linking " + path + ":" << err.getMessage() << "\n";
    }
  }
}

void IRGenerator::declareDependencyFunctions() {
  // Declare the function types
  llvm::FunctionType *printFnType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt1Ty(*TheContext)},
                              false);
  llvm::FunctionType *concatStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *stringLengthFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);
  llvm::FunctionType *itosFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt32Ty(*TheContext)}, false);
  llvm::FunctionType *dtosFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getDoubleTy(*TheContext)}, false);
  llvm::FunctionType *getMallocPtrOfStringConstantFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);
  llvm::FunctionType *getMallocPtrofIntConstantFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt32Ty(*TheContext)}, false);
  llvm::FunctionType *compareStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *lessThanStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *lessThanOrEqualStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *greaterThanStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *greaterThanOrEqualStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *equalStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);
  llvm::FunctionType *getInputFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext), {}, false);
  llvm::FunctionType *stringToIntFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);
  llvm::FunctionType *stringToLongFnType =
      llvm::FunctionType::get(llvm::Type::getInt64Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);
  llvm::FunctionType *stringToDoubleFnType =
      llvm::FunctionType::get(llvm::Type::getDoubleTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  // Declare the functions
  llvm::Function *printFn =
      llvm::Function::Create(printFnType, llvm::Function::ExternalLinkage,
                             INNERS::FUNCTIONS::PRINT, *TheModule);
  llvm::Function *concatStringsFn = llvm::Function::Create(
      concatStringsFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::CONCAT_STRINGS, *TheModule);
  llvm::Function *stringLengthFn = llvm::Function::Create(
      stringLengthFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::STRING_LENGTH, *TheModule);
  llvm::Function *itosFn =
      llvm::Function::Create(itosFnType, llvm::Function::ExternalLinkage,
                             INNERS::FUNCTIONS::ITOS, *TheModule);
  llvm::Function *dtosFn =
      llvm::Function::Create(dtosFnType, llvm::Function::ExternalLinkage,
                             INNERS::FUNCTIONS::DTOS, *TheModule);
  llvm::Function *getMallocPtrOfStringConstantFn = llvm::Function::Create(
      getMallocPtrOfStringConstantFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::GET_MALLOC_PTR_OF_STRING_CONSTANT, *TheModule);
  llvm::Function *getMallocPtrofIntConstantFn = llvm::Function::Create(
      getMallocPtrofIntConstantFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::GET_MALLOC_PTR_OF_INT_CONSTANT, *TheModule);
  llvm::Function *compareStringsFn = llvm::Function::Create(
      compareStringsFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::COMPARE_STRINGS, *TheModule);
  llvm::Function *lessThanStringsFn = llvm::Function::Create(
      lessThanStringsFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::LESS_THAN_STRINGS, *TheModule);
  llvm::Function *lessThanOrEqualStringsFn = llvm::Function::Create(
      lessThanOrEqualStringsFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::LESS_THAN_OR_EQUAL_STRINGS, *TheModule);
  llvm::Function *greaterThanStringsFn = llvm::Function::Create(
      greaterThanStringsFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::GREATER_THAN_STRINGS, *TheModule);

  llvm::Function::Create(
      greaterThanOrEqualStringsFnType, llvm::Function::ExternalLinkage,
      INNERS::FUNCTIONS::GREATER_THAN_OR_EQUAL_STRINGS, *TheModule);
  llvm::Function::Create(equalStringsFnType, llvm::Function::ExternalLinkage,
                         INNERS::FUNCTIONS::EQUAL_STRINGS, *TheModule);

  llvm::Function::Create(getInputFnType, llvm::Function::ExternalLinkage,
                         INNERS::FUNCTIONS::GET_INPUT, *TheModule);
  llvm::Function::Create(stringToIntFnType, llvm::Function::ExternalLinkage,
                         "string_to_int", *TheModule);
  llvm::Function::Create(stringToLongFnType, llvm::Function::ExternalLinkage,
                         INNERS::FUNCTIONS::STRING_TO_INT, *TheModule);
  llvm::Function::Create(stringToDoubleFnType, llvm::Function::ExternalLinkage,
                         INNERS::FUNCTIONS::STRING_TO_DOUBLE, *TheModule);
}

void IRGenerator::initializeGlobalVariables() {
  llvm::Type *i8Type = llvm::Type::getInt8Ty(*TheContext);
  llvm::Type *i32Type = llvm::Type::getInt32Ty(*TheContext);

  // Create the private global variables.
  new llvm::GlobalVariable(
      *TheModule, llvm::ArrayType::get(i8Type, 5),
      true, // isConstant
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantDataArray::getString(*TheContext, "true\00"),
      this->_irUtils->addPrefixToVariableName(FLOWWING_GLOBAL_TRUE));

  new llvm::GlobalVariable(
      *TheModule, llvm::ArrayType::get(i8Type, 6), true,
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantDataArray::getString(*TheContext, "false\00"),
      this->_irUtils->addPrefixToVariableName(FLOWWING_GLOBAL_FALSE));
  new llvm::GlobalVariable(
      *TheModule, i8Type, false, llvm::GlobalValue::ExternalLinkage,
      nullptr, // For null, you can pass nullptr as the initializer
      this->_irUtils->addPrefixToVariableName(FLOWWING_GLOBAL_NULL));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      this->_irUtils->addPrefixToVariableName(FLOWWING_CONTINUE_COUNT));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      this->_irUtils->addPrefixToVariableName(FLOWWING_GLOBAL_ZERO));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      this->_irUtils->addPrefixToVariableName(FLOWWING_GLOBAL_ERROR_COUNT));
}

void IRGenerator::setModuleCount(int count) { this->_moduleCount = count; }

llvm::Value *
IRGenerator::generateEvaluateLiteralExpressionFunction(BoundExpression *node) {
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)node;
  std::any value = literalExpression->getValue();

  this->_irUtils->setCurrentSourceLocation(literalExpression->getLocation());

  llvm::Value *val =
      this->_irUtils->getLLVMValue(value, literalExpression->getSyntaxKind());

  if (val == nullptr) {
    this->_irUtils->logError("Unsupported Literal Type ");
    return nullptr;
  }

  return val;
}

std::unique_ptr<IRParser> &IRGenerator::getIRParserPtr() {
  return this->_irParser;
}

llvm::Value *
IRGenerator::generateEvaluateUnaryExpressionFunction(BoundExpression *node) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
  llvm::Value *val = this->generateEvaluateExpressionStatement(
      unaryExpression->getOperandPtr().get());

  this->_irUtils->setCurrentSourceLocation(unaryExpression->getLocation());

  if (val == nullptr) {

    this->_irUtils->logError("Unsupported Unary Expression Type ");

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
               val->getType()->isIntegerTy(8)) {
      // Get the string length

      llvm::ArrayRef<llvm::Value *> Args = {
          this->_irUtils->explicitConvertToString(val)};
      llvm::Value *length = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::STRING_LENGTH), Args);
      val = length;

      // Compare the string Length to Zero
      result = Builder->CreateICmpEQ(
          length, llvm::ConstantInt::get(length->getType(), 0));
    } else if (val->getType()->isIntegerTy(1)) {
      // For boolean values, perform logical NOT
      result = Builder->CreateNot(val);
    } else {

      this->_irUtils->logError("Unsupported Unary Expression Type ");

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

    this->_irUtils->logError("Unsupported Unary Expression Type ");

    return nullptr;
  }
  }

  return result;
}

void IRGenerator::printIR() {
  // Print LLVM IR to console
  TheModule->print(llvm::outs(), nullptr);
}

std::unique_ptr<llvm::Module> &IRGenerator::getModulePtr() { return TheModule; }

llvm::Value *
IRGenerator::handleGlobalVariableExpression(const std::string &variableName,
                                            llvm::GlobalVariable *variable) {
  if (variable->getValueType()->isIntegerTy(32) ||
      variable->getValueType()->isIntegerTy(64) ||
      variable->getValueType()->isIntegerTy(1) ||
      variable->getValueType()->isFloatTy() ||
      variable->getValueType()->isDoubleTy() ||
      variable->getValueType()->isIntegerTy(8) ||
      variable->getValueType()->isBFloatTy() ||
      variable->getValueType()->isHalfTy() ||
      variable->getValueType()->isFP128Ty() ||
      variable->getValueType()->isX86_FP80Ty() ||
      variable->getValueType()->isPPC_FP128Ty()) {
    llvm::Value *loaded =
        Builder->CreateLoad(variable->getValueType(), variable, variableName);

    return loaded;
  }

  llvm::Value *loaded =
      Builder->CreateLoad(variable->getValueType(), variable, variableName);
  llvm::Value *zero =
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0);
  llvm::Value *indices[] = {zero, zero};
  llvm::Value *strPtr = Builder->CreateInBoundsGEP(
      variable->getValueType(), variable, indices, "str_ptr");

  llvm::Value *elementPtr = Builder->CreateBitCast(
      strPtr, llvm::IntegerType::getInt8PtrTy((*TheContext)), "element_ptr");

  return elementPtr;
}

llvm::Value *
IRGenerator::generateEvaluateVariableExpressionFunction(BoundExpression *node) {
  BoundVariableExpression *variableExpression = (BoundVariableExpression *)node;

  this->_irUtils->setCurrentSourceLocation(variableExpression->getLocation());
  std::string variableName = this->_irUtils->getString(
      variableExpression->getIdentifierExpressionPtr().get());

  llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

  llvm::Value *variableValue =
      this->_irUtils->getNamedValue(variableName, this->_NamedValuesStack);

  if (!variableValue) {
    if (variable) {
      return handleGlobalVariableExpression(variableName, variable);
    }
    this->_irUtils->logError("Variable not found in variable expression ");
    return nullptr;
  }

  llvm::AllocaInst *v = this->_irUtils->getNamedValueAlloca(
      variableName, this->_NamedValuesAllocaStack);

  llvm::Value *value = Builder->CreateLoad(
      variableValue->getType(),
      Builder->CreateStructGEP(
          this->_dynamicType, v,
          this->_irUtils->getIndexofMemberType(variableValue->getType())));
  this->_irUtils->setCurrentSourceLocation(variableExpression->getLocation());

  return value;
}
llvm::Value *IRGenerator::generateEvaluateAssignmentExpressionFunction(
    BoundExpression *node) {

  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)node;
  this->_irUtils->setCurrentSourceLocation(assignmentExpression->getLocation());

  std::string variableName =
      this->_irUtils->getString(assignmentExpression->getLeftPtr().get());
  llvm::Value *oldValue =
      this->_irUtils->getNamedValue(variableName, this->_NamedValuesStack);
  if (!oldValue) {
    // Variable not found, handle error

    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {
      handleGlobalAssignmentExpression(assignmentExpression);
      return nullptr;
    }

    this->_irUtils->logError("Variable not found in assignment expression ");

    return nullptr;
  }

  llvm::Value *rhsValue = generateEvaluateExpressionStatement(
      assignmentExpression->getRightPtr().get());

  if (!rhsValue) {
    // Error generating IR for the right-hand side expression

    this->_irUtils->logError(
        "Right hand side value not found in assignment expression ");

    return nullptr;
  }

  llvm::AllocaInst *v = this->_irUtils->getNamedValueAlloca(
      variableName, this->_NamedValuesAllocaStack);

  this->_irUtils->updateNamedValue(variableName, rhsValue,
                                   this->_NamedValuesStack);

  Builder->CreateStore(
      rhsValue, Builder->CreateStructGEP(
                    this->_dynamicType, v,
                    this->_irUtils->getIndexofMemberType(rhsValue->getType())));

  return rhsValue;
}

llvm::Value *IRGenerator::generateEvaluateBinaryExpressionFunction(
    BoundBinaryExpression *node) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;

  llvm::Value *lhsValue =
      generateEvaluateExpressionStatement(binaryExpression->getLeftPtr().get());

  llvm::Value *rhsValue = generateEvaluateExpressionStatement(
      binaryExpression->getRightPtr().get());

  this->_irUtils->setCurrentSourceLocation(binaryExpression->getLocation());

  if (!lhsValue || !rhsValue) {

    this->_irUtils->logError("Error in generating IR for operands ");

    return nullptr;
  }

  llvm::Type *lhsType = lhsValue->getType();
  llvm::Type *rhsType = rhsValue->getType();

  llvm::Value *result = nullptr;
  if (this->_irUtils->isStringType(lhsType) ||
      this->_irUtils->isStringType(rhsType)) {

    result = this->_irUtils->getResultFromBinaryOperationOnString(
        this->_irUtils->explicitConvertToString(lhsValue),
        this->_irUtils->explicitConvertToString(rhsValue), binaryExpression);
  } else if (this->_irUtils->isDoubleType(lhsType) ||
             this->_irUtils->isDoubleType(rhsType)) {

    result = this->_irUtils->getResultFromBinaryOperationOnDouble(
        this->_irUtils->explicitConvertToDouble(lhsValue),
        this->_irUtils->explicitConvertToDouble(rhsValue), binaryExpression);
  } else if (this->_irUtils->isBoolType(lhsType) &&
             this->_irUtils->isBoolType(rhsType)) {

    result = this->_irUtils->getResultFromBinaryOperationOnBool(
        lhsValue, rhsValue, binaryExpression);
  } else {

    result = this->_irUtils->getResultFromBinaryOperationOnInt(
        this->_irUtils->explicitConvertToInt(lhsValue),
        this->_irUtils->explicitConvertToInt(rhsValue), binaryExpression);
  }
  return result;
}

llvm::Value *
IRGenerator::handleBuiltInfuntions(BoundCallExpression *callExpression) {

  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();

  const std::string &functionName = function.name;
  std::size_t arguments_size = callExpression->getArguments().size();

  this->_irUtils->setCurrentSourceLocation(callExpression->getLocation());

  const std::string errorMessage =
      "Unexpected Function Call Arguments Does Not Match in " + functionName;

  if (functionName == Utils::BuiltInFunctions::print.name) {
    if (arguments_size == 1) {

      llvm::Value *value = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());

      if (this->_irUtils->getReturnType(value->getType()) ==
          Utils::type::NOTHING) {
        return nullptr;
      }
      this->_irUtils->printFunction(value, false);
      return nullptr;
    }

    this->_irUtils->logError(errorMessage);

    return nullptr;
  } else if (function.name == Utils::BuiltInFunctions::input.name) {
    if (arguments_size == 0) {

      llvm::ArrayRef<llvm::Value *> Args = {};

      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
    } else if (arguments_size == 1) {

      llvm::Value *strPtri8 = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());

      this->_irUtils->printFunction(strPtri8, false);

      llvm::ArrayRef<llvm::Value *> Args = {};
      llvm::CallInst *callInst = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::GET_INPUT), Args);

      return callInst;
    }

    this->_irUtils->logError(errorMessage);

    return nullptr;
  } else if (function.name == Utils::BuiltInFunctions::String.name) {
    if (arguments_size == 1) {
      llvm::Value *val = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());

      return this->_irUtils->explicitConvertToString(val);
    }

    this->_irUtils->logError(errorMessage);
  } else if (function.name == Utils::BuiltInFunctions::Int32.name) {
    if (arguments_size == 1) {

      llvm::Value *res = nullptr;
      llvm::Value *val = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());
      res = this->_irUtils->explicitConvertToInt(val);
      return res;
    }

    this->_irUtils->logError(errorMessage);
  } else if (function.name == Utils::BuiltInFunctions::Bool.name) {
    if (arguments_size == 1) {
      llvm::Value *val = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());

      return this->_irUtils->explicitConvertToBool(val);
    }

    this->_irUtils->logError(errorMessage);
  } else if (function.name == Utils::BuiltInFunctions::Decimal.name) {
    if (arguments_size == 1) {
      llvm::Value *val = this->generateEvaluateExpressionStatement(
          (BoundExpression *)callExpression->getArguments()[0].get());

      return this->_irUtils->explicitConvertToDouble(val);
    }

    this->_irUtils->logError(errorMessage);
  }
  this->_irUtils->logError("Unexpected Function Call ");

  return nullptr;
}

llvm::Value *IRGenerator::generateCallExpressionForUserDefinedFunction(
    BoundCallExpression *callExpression) {

  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();

  const std::string &functionName = function.name;
  std::size_t arguments_size = callExpression->getArguments().size();

  this->_irUtils->setCurrentSourceLocation(callExpression->getLocation());

  std::vector<llvm::Value *> args;

  for (int i = 0; i < arguments_size; i++) {

    llvm::Value *arg = nullptr;

    arg = this->generateEvaluateExpressionStatement(
        (BoundExpression *)callExpression->getArguments()[i].get());

    if (!arg) {

      this->_irUtils->logError("Error in generating IR for arguments ");

      return nullptr;
    }
    args.push_back(arg);
  }

  llvm::Function *calleeFunction = TheModule->getFunction(functionName);

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  if (!calleeFunction && !this->_recursiveFunctionsMap[function.name]) {
    this->_recursiveFunctionsMap[function.name] = true;
    this->generateUserDefinedFunctionOnFly(
        this->_boundedUserFunctions[functionName], args);
    Builder->SetInsertPoint(currentBlock);
  }

  calleeFunction = TheModule->getFunction(functionName);

  this->_recursiveFunctionsMap[function.name] = false;

  llvm::FunctionType *functionType = calleeFunction->getFunctionType();
  std::vector<llvm::Type *> paramTypes(functionType->param_begin(),
                                       functionType->param_end());

  // Callefunction param types and args check for type are same or not

  for (int i = 0; i < paramTypes.size(); i++) {
    if (paramTypes[i] != args[i]->getType()) {

      const std::string parameterName =
          this->_boundedUserFunctions[functionName]
              ->getFunctionSymbol()
              .parameters[i]
              .name;
      const std::string argumentType = Utils::typeToString(
          this->_irUtils->getReturnType(args[i]->getType()));

      const std::string parameterType =
          Utils::typeToString(this->_irUtils->getReturnType(paramTypes[i]));

      const std::string errorMessage = "Argument Type " + argumentType +
                                       " does not match with " + parameterType +
                                       " for parameter " + parameterName;

      this->_irUtils->logError(errorMessage);

      return nullptr;
    }
  }
  return Builder->CreateCall(calleeFunction, args);
}

llvm::Value *IRGenerator::generateEvaluateCallExpression(
    BoundCallExpression *callExpression) {
  this->_irUtils->setCurrentSourceLocation(callExpression->getLocation());
  Utils::FunctionSymbol function = callExpression->getFunctionSymbol();
  if (Utils::BuiltInFunctions::getFunctionSymbol(function.name).name ==
      function.name) {
    return this->handleBuiltInfuntions(callExpression);
  } else {
    return this->generateCallExpressionForUserDefinedFunction(callExpression);
  }

  return nullptr;
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
  this->_irUtils->setCurrentSourceLocation(node->getLocation());
  this->_irUtils->setNamedValue(variable_name, result, this->_NamedValuesStack);

  // create and load variable

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(this->_dynamicType, nullptr, variable_name.c_str());

  this->_irUtils->setNamedValueAlloca(variable_name, variable,
                                      this->_NamedValuesAllocaStack);

  Builder->CreateStore(
      result, Builder->CreateStructGEP(
                  this->_dynamicType, variable,
                  this->_irUtils->getIndexofMemberType(result->getType())));

  return result;
}

llvm::Value *IRGenerator::generateEvaluateBlockStatement(
    BoundBlockStatement *blockStatement) {
  this->_irUtils->setCurrentSourceLocation(blockStatement->getLocation());
  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // create and load variable

  llvm::BasicBlock *afterNestedBlock = llvm::BasicBlock::Create(
      *TheContext, "afterNestedBlock", currentBlock->getParent());

  std::vector<llvm::BasicBlock *> nestedBlocks, checkContinueBlocks,
      checkReturnBlocks;
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
        this->_irUtils->isCountZero(
            this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT),
            llvm::Type::getInt32Ty(*TheContext)),
        checkContinueBlocks[i], afterNestedBlock);

    //  i th Check continue Block

    Builder->SetInsertPoint(checkContinueBlocks[i]);

    if (i == blockStatement->getStatements().size() - 1)
      Builder->CreateBr(afterNestedBlock);
    else {
      Builder->CreateCondBr(
          this->_irUtils->isCountZero(
              this->_irUtils->addPrefixToVariableName(FLOWWING_CONTINUE_COUNT),
              llvm::Type::getInt32Ty(*TheContext)),
          nestedBlocks[i + 1], afterNestedBlock);
    }
  }

  Builder->SetInsertPoint(afterNestedBlock);

  this->_NamedValuesStack.pop();
  this->_NamedValuesAllocaStack.pop();
  return nullptr;
}

void IRGenerator::mergeModules(llvm::Module *sourceModule,
                               llvm::Module *destinationModule) {
  llvm::LLVMContext &context = destinationModule->getContext();
  llvm::ValueToValueMapTy vmap;

  // Iterate through functions in the source module and clone them to the
  // destination module
  for (llvm::Function &sourceFunction : *sourceModule) {
    llvm::Function *clonedFunction = llvm::CloneFunction(&sourceFunction, vmap);
    clonedFunction->setName(sourceFunction.getName() + ".clone");
    destinationModule->getFunctionList().push_back(clonedFunction);
  }
}

const int IRGenerator::hasErrors() const { return this->_irUtils->hasError(); }

void IRGenerator::handleGlobalFunctionDefinition(
    BoundFunctionDeclaration *userFunction) {

  this->_irUtils->setCurrentSourceLocation(userFunction->getLocation());

  if (userFunction->hasParameterTypes()) {
    this->generateUserDefinedFunction(userFunction);
  }
}

void IRGenerator::handleGlobalBringStatement(
    BoundBringStatement *bringStatementSyntax) {
  this->_irUtils->setCurrentSourceLocation(bringStatementSyntax->getLocation());

  for (const auto &_function :
       bringStatementSyntax->getGlobalScopePtr()->functions) {
    handleGlobalFunctionDeclaration(_function.second);
  }

  for (const auto &variable :
       bringStatementSyntax->getGlobalScopePtr()->variables) {

    if (variable.second.type == Utils::type::UNKNOWN) {
      this->_irUtils->logError("Multifile UNKOWN type not allowed, Please "
                               "specify the type of variable " +
                               variable.first);
      continue;
    }

    llvm::Type *type = this->_irUtils->getReturnType(variable.second.type);
    llvm::GlobalVariable *variableLLVM = new llvm::GlobalVariable(
        *TheModule, type, false, llvm::GlobalValue::ExternalLinkage, nullptr,
        variable.first);

    // Builder->CreateStore(llvm::Constant::getNullValue(type),
    // variableLLVM);
  }

  const std::string onlyFileName = Utils::getNameExtension(
      bringStatementSyntax->getDiagnosticHandlerPtr()->getAbsoluteFilePath());
  std::string removedExtenstionFromAbsolutePath =
      Utils::removeExtensionFromString(
          bringStatementSyntax->getDiagnosticHandlerPtr()
              ->getAbsoluteFilePath());

  std::replace(removedExtenstionFromAbsolutePath.begin(),
               removedExtenstionFromAbsolutePath.end(), '/', '-');
  std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
      ENVIRONMENT::SOURCE_FILE, bringStatementSyntax->getDiagnosticHandlerPtr(),
      bringStatementSyntax->getGlobalScopePtr()->functions,
      removedExtenstionFromAbsolutePath);

  _evaluator->generateEvaluateGlobalStatement(
      bringStatementSyntax->getGlobalScopePtr()->globalStatement.get(),
      onlyFileName);
  this->_irUtils->setCurrentSourceLocation(bringStatementSyntax->getLocation());
  if (_evaluator->hasErrors()) {
    this->_irUtils->logError(
        "Error in importing file " +
        bringStatementSyntax->getDiagnosticHandlerPtr()->getAbsoluteFilePath());
  }
}

void IRGenerator::handleGlobalAssignmentExpression(
    BoundAssignmentExpression *assignmentExpression) {

  std::string variableName =
      this->_irUtils->getString(assignmentExpression->getLeftPtr().get());

  llvm::Value *rhsValue = generateEvaluateExpressionStatement(
      assignmentExpression->getRightPtr().get());
  this->_irUtils->setCurrentSourceLocation(assignmentExpression->getLocation());
  if (!rhsValue) {

    this->_irUtils->logError(
        "Right hand side value not found in assignment expression ");
    return;
  }

  // llvm::Value *variableValue = this->_irUtils->getNamedValue(
  //     variableName, this->_GlobalNamedValuesStack);

  // if (!variableValue) {
  //   // Variable not found,  error

  //   this->_irUtils->logError("Variable not found in assignment expression
  //   "); return;
  // }

  llvm::GlobalVariable *oldVariable =
      TheModule->getGlobalVariable(variableName);

  if (!oldVariable) {
    this->_irUtils->logError("Variable not found in assignment expression ");
    return;
  }

  if (auto constDataArray = llvm::dyn_cast<llvm::ConstantDataArray>(rhsValue)) {
    Utils::type rhsType = this->_irUtils->getReturnType(rhsValue->getType());
    if (rhsType == Utils::type::STRING)
      Builder->CreateStore(rhsValue, oldVariable);
    else {

      this->_irUtils->logError(
          "Assigning " +
          Utils::typeToString(
              this->_irUtils->getReturnType(rhsValue->getType())) +
          " to String is not allowed in Global "
          "assignment expression ");
    }

  } else {

    if (rhsValue->getType() == oldVariable->getValueType())
      Builder->CreateStore(rhsValue, oldVariable);
    else {
      this->_irUtils->logError(
          "Assigning " +
          Utils::typeToString(
              this->_irUtils->getReturnType(rhsValue->getType())) +
          " to " +
          Utils::typeToString(
              this->_irUtils->getReturnType(oldVariable->getValueType())) +
          " is not allowed in Global "
          "assignment expression ");
    }
  }
}

void IRGenerator::handleGlobalVariableDeclaration(
    BoundVariableDeclaration *variableDeclaration) {
  std::string variableName = variableDeclaration->getVariable();
  llvm::Value *result = this->generateEvaluateExpressionStatement(
      variableDeclaration->getInitializerPtr().get());
  this->_irUtils->setCurrentSourceLocation(variableDeclaration->getLocation());
  if (result == nullptr) {
    this->_irUtils->logError(
        "Error in generating IR for variable declaration ");
    return;
  }
  llvm::GlobalVariable *_globalVariable = nullptr;
  llvm::AllocaInst *v = nullptr;
  if (auto constDataArray = llvm::dyn_cast<llvm::ConstantDataArray>(result)) {

    std::string str = constDataArray->getAsCString().str();

    _globalVariable = new llvm::GlobalVariable(
        *TheModule,
        llvm::ArrayType::get(llvm::IntegerType::getInt8Ty((*TheContext)),
                             str.length() + 1),
        true, llvm::GlobalValue::ExternalLinkage, constDataArray, variableName);

    // v = Builder->CreateAlloca(
    //     llvm::ArrayType::get(llvm::IntegerType::getInt8Ty((*TheContext)),
    //                          str.length() + 1),
    //     nullptr, variableName.c_str());

  } else {
    llvm::Constant *constant = this->_irUtils->createConstantFromValue(result);

    if (constant) {
      _globalVariable = new llvm::GlobalVariable(
          *TheModule, result->getType(), false,
          llvm::GlobalValue::ExternalLinkage, constant, variableName);
    } else {
      _globalVariable = new llvm::GlobalVariable(
          *TheModule, result->getType(), false,
          llvm::GlobalValue::ExternalLinkage,
          llvm::Constant::getNullValue(result->getType()), variableName);
    }
    // v = Builder->CreateAlloca(_globalVariable->getType(), nullptr,
    //                           variableName.c_str());
  }
  // Builder->CreateStore(_globalVariable, v);
  //  this->_irUtils->setNamedValue(variableName, _globalVariable,
  //                                this->_GlobalNamedValuesStack);

  // this->_irUtils->setNamedValueAlloca(variableName, v,
  //                                     this->_GlobalNamedValuesAllocaStack);
}
void IRGenerator::handleGlobalExpressionStatement(
    BoundExpressionStatement *expressionStatement) {
  this->_irUtils->setCurrentSourceLocation(expressionStatement->getLocation());

  BinderKindUtils::BoundNodeKind innerKind =
      expressionStatement->getExpressionPtr().get()->getKind();

  switch (innerKind) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression: {

    this->_irUtils->logError(
        "Literal Expression is not allowed in global scope ");
    return;
  }
  case BinderKindUtils::BoundNodeKind::UnaryExpression: {

    this->_irUtils->logError(
        "Unary Expression is not allowed in global scope ");
    return;
  }
  case BinderKindUtils::BoundNodeKind::VariableExpression: {

    this->_irUtils->logError(
        "Variable Expression is not allowed in global scope ");
    return;
  }
  case BinderKindUtils::BoundNodeKind::AssignmentExpression: {

    BoundAssignmentExpression *assignmentExpression =
        (BoundAssignmentExpression *)expressionStatement->getExpressionPtr()
            .get();
    this->_irUtils->setCurrentSourceLocation(
        assignmentExpression->getLocation());
    this->handleGlobalAssignmentExpression(assignmentExpression);
    break;
  }
  case BinderKindUtils::BoundNodeKind::VariableDeclaration: {
    BoundVariableDeclaration *variableDeclaration =
        (BoundVariableDeclaration *)expressionStatement->getExpressionPtr()
            .get();
    this->_irUtils->setCurrentSourceLocation(
        variableDeclaration->getLocation());
    this->handleGlobalVariableDeclaration(variableDeclaration);
    break;
  }
  case BinderKindUtils::BoundNodeKind::BinaryExpression: {

    this->_irUtils->logError(
        "Binary Expression is not allowed in global scope ");
    return;
  }
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {

    this->_irUtils->logError(
        "Parenthesized Expression is not allowed in global scope ");
    return;
  }

  case BinderKindUtils::BoundNodeKind::CallExpression: {
    BoundCallExpression *callExpression =
        (BoundCallExpression *)expressionStatement->getExpressionPtr().get();

    this->_irUtils->setCurrentSourceLocation(callExpression->getLocation());
    this->generateEvaluateCallExpression(callExpression);
    break;
  }
  default: {
    break;
  }
  }
}

void IRGenerator::handleGlobalFunctionDeclaration(
    BoundFunctionDeclaration *node) {

  this->_irUtils->setCurrentSourceLocation(node->getLocation());

  if (node->hasParameterTypes()) {

    std::string functionName = node->getFunctionSymbol().name;

    this->_irUtils->setCurrentSourceLocation(node->getLocation());

    std::vector<llvm::Type *> argTypes;
    for (int i = 0; i < node->getFunctionSymbol().parameters.size(); i++) {
      argTypes.push_back(this->_irUtils->getReturnType(
          node->getFunctionSymbol().parameters[i].type));
    }
    llvm::Type *returnType = this->_irUtils->getReturnType(
        node->getFunctionSymbol().getReturnType());

    llvm::FunctionType *FT =
        llvm::FunctionType::get(returnType, argTypes, false);

    llvm::Function *F = llvm::Function::Create(
        FT, llvm::Function::ExternalLinkage, functionName, *TheModule);

    this->_boundedUserFunctions[node->getFunctionSymbol().name] = node;
  }
}

void IRGenerator::generateEvaluateGlobalStatement(
    BoundBlockStatement *blockStatement, std::string blockName) {
  this->_irUtils->setCurrentSourceLocation(blockStatement->getLocation());
  this->_irUtils->setInitializingGlobals(0);

  llvm::Value *returnValue = nullptr; // default return value
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), false);

  llvm::Function *F = llvm::Function::Create(
      FT, llvm::Function::ExternalLinkage, blockName, *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", F);

  // Entry Block

  Builder->SetInsertPoint(entryBlock);

  this->_dynamicType = llvm::StructType::create(*TheContext, "DynamicType");

  this->_dynamicType->setBody(this->_irUtils->getMemberTypesForDynamicTypes());

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    BinderKindUtils::BoundNodeKind kind =
        blockStatement->getStatements()[i].get()->getKind();
    this->_irUtils->setInitializingGlobals(1);
    if (kind == BinderKindUtils::BoundNodeKind::FunctionDeclaration) {

      BoundFunctionDeclaration *userFunction =
          (BoundFunctionDeclaration *)blockStatement->getStatements()[i].get();

      // Declaration of function

      this->_irUtils->setCurrentSourceLocation(userFunction->getLocation());

      this->handleGlobalFunctionDeclaration(userFunction);

    } else if (kind == BinderKindUtils::BoundNodeKind::BringStatement) {
      this->_irUtils->setInitializingGlobals(0);
      BoundBringStatement *bringStatementSyntax =
          (BoundBringStatement *)blockStatement->getStatements()[i].get();

      this->handleGlobalBringStatement(bringStatementSyntax);

    } else if (kind == BinderKindUtils::BoundNodeKind::ExpressionStatement) {
      BoundExpressionStatement *expressionStatement =
          (BoundExpressionStatement *)blockStatement->getStatements()[i].get();
      this->_irUtils->setCurrentSourceLocation(
          expressionStatement->getLocation());
      this->handleGlobalExpressionStatement(expressionStatement);
    } else if (kind == BinderKindUtils::BoundNodeKind::VariableDeclaration) {
      BoundVariableDeclaration *variableDeclaration =
          (BoundVariableDeclaration *)blockStatement->getStatements()[i].get();
      this->_irUtils->setCurrentSourceLocation(
          variableDeclaration->getLocation());
      this->handleGlobalVariableDeclaration(variableDeclaration);
    } else if (kind == BinderKindUtils::BoundNodeKind::AssignmentExpression) {
      BoundAssignmentExpression *assignmentExpression =
          (BoundAssignmentExpression *)blockStatement->getStatements()[i].get();
      this->_irUtils->setCurrentSourceLocation(
          assignmentExpression->getLocation());
      this->handleGlobalAssignmentExpression(assignmentExpression);
    } else {
      this->_irUtils->setInitializingGlobals(0);
      llvm::Value *res = this->generateEvaluateStatement(
          blockStatement->getStatements()[i].get());

      if (i == blockStatement->getStatements().size() - 1 &&
          blockStatement->getStatements()[i].get()->getKind() ==
              BinderKindUtils::BoundNodeKind::ExpressionStatement) {
        returnValue = res;
      }
    }
  }

  Builder->CreateBr(returnBlock);
  Builder->SetInsertPoint(returnBlock);
  Builder->CreateRet(this->_irUtils->getGlobalVarAndLoad(
      this->_irUtils->addPrefixToVariableName(FLOWWING_GLOBAL_ERROR_COUNT),
      llvm::Type::getInt32Ty(*TheContext)));

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    BinderKindUtils::BoundNodeKind kind =
        blockStatement->getStatements()[i].get()->getKind();
    if (kind == BinderKindUtils::BoundNodeKind::FunctionDeclaration) {

      BoundFunctionDeclaration *userFunction =
          (BoundFunctionDeclaration *)blockStatement->getStatements()[i].get();

      this->_irUtils->setCurrentSourceLocation(userFunction->getLocation());

      this->handleGlobalFunctionDefinition(userFunction);
    }
  }
  this->_irUtils->saveLLVMModuleToFile(
      TheModule.get(), this->_irUtils->getSourceFileName() + ".ll");
  // this->_irParser->mergeIR(TheModule.get());

  // this->_irParser->removeDuplicates();

#ifdef JIT_MODE
  if (this->_irUtils->hasError()) {
    llvm::SMDiagnostic Err;
    Err.print("FLowWing", llvm::errs());
  }
#endif
}

llvm::Value *IRGenerator::evaluateIfStatement(BoundStatement *node) {

  BoundIfStatement *ifStatement = (BoundIfStatement *)node;
  llvm::Value *exitValue = nullptr;
  llvm::Value *conditionValue = this->generateEvaluateExpressionStatement(
      ifStatement->getConditionPtr().get());

  this->_irUtils->setCurrentSourceLocation(ifStatement->getLocation());

  if (conditionValue == nullptr) {

    this->_irUtils->logError("Condition Value is not found in if statement");

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

    this->_irUtils->setCurrentSourceLocation(
        ifStatement->getOrIfStatementsPtr()[i]->getLocation());

    if (orIfConditionValue == nullptr) {

      this->_irUtils->logError(
          "Condition Value is not found in or if statement");

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

  this->_irUtils->setCurrentSourceLocation(whileStatement->getLocation());

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();
  llvm::Value *exitValue = nullptr;
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

  this->_irUtils->decrementCountIfNotZero(
      this->_irUtils->addPrefixToVariableName(FLOWWING_CONTINUE_COUNT));
  llvm::Value *conditionValue = this->generateEvaluateExpressionStatement(
      whileStatement->getConditionPtr().get());

  // Load the condition

  if (conditionValue == nullptr) {

    this->_irUtils->logError("Condition Value is not found in while statement");

    return nullptr;
  }

  Builder->CreateCondBr(conditionValue, breakLoop, afterLoop);

  Builder->SetInsertPoint(breakLoop);

  Builder->CreateCondBr(
      this->_irUtils->isCountZero(
          this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT),
          llvm::Type::getInt32Ty(*TheContext)),
      loopBody, afterLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);
  llvm::Value *result =
      this->generateEvaluateStatement(whileStatement->getBodyPtr().get());

  Builder->CreateBr(loopCondition);

  // After Loop

  Builder->SetInsertPoint(afterLoop);

  this->_irUtils->decrementCountIfNotZero(
      this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT));

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
    stepValue = this->_irUtils->implicitConvertToInt(
        this->generateEvaluateExpressionStatement(
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

    this->_irUtils->setCurrentSourceLocation(
        variableDeclaration->getLocation());
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

  this->_irUtils->setCurrentSourceLocation(forStatement->getLocation());

  if (variableName == "") {

    this->_irUtils->logError("Variable Name is not found in for statement");
    return nullptr;
  }

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();
  llvm::Value *exitValue = nullptr;
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

  this->_irUtils->decrementCountIfNotZero(
      this->_irUtils->addPrefixToVariableName(FLOWWING_CONTINUE_COUNT));

  llvm::Value *variableValue =
      this->_irUtils->getNamedValue(variableName, this->_NamedValuesStack);

  llvm::AllocaInst *v = this->_irUtils->getNamedValueAlloca(
      variableName, this->_NamedValuesAllocaStack);

  llvm::Value *value = Builder->CreateLoad(variableValue->getType(), v);

  llvm::PHINode *conditionPHI =
      this->_irUtils->handleForLoopCondition(stepValue, value, upperBound);

  if (conditionPHI == nullptr) {
    this->_irUtils->logError("Condition Value is not found in for statement");

    return nullptr;
  }

  Builder->CreateCondBr(conditionPHI, breakLoop, afterLoop);

  Builder->SetInsertPoint(breakLoop);

  Builder->CreateCondBr(
      this->_irUtils->isCountZero(
          this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT),
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

  this->_irUtils->decrementCountIfNotZero(
      this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT));

  this->_NamedValuesAllocaStack.pop();
  this->_NamedValuesStack.pop();

  return exitValue;
}

void IRGenerator::generateUserDefinedFunction(BoundFunctionDeclaration *node) {

  std::string functionName = node->getFunctionSymbol().name;

  this->_irUtils->setCurrentSourceLocation(node->getLocation());

  std::vector<llvm::Type *> argTypes;
  for (int i = 0; i < node->getFunctionSymbol().parameters.size(); i++) {
    argTypes.push_back(this->_irUtils->getReturnType(
        node->getFunctionSymbol().parameters[i].type));
  }
  llvm::Type *returnType =
      this->_irUtils->getReturnType(node->getFunctionSymbol().getReturnType());

  this->_returnAllocaStack.push({node->getFunctionSymbol().getReturnType(), 0});

  llvm::Function *F = TheModule->getFunction(functionName);
  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());

  std::vector<std::string> parameterNames;

  for (int i = 0; i < node->getFunctionSymbol().parameters.size(); i++) {
    parameterNames.push_back(node->getFunctionSymbol().parameters[i].name);
  }

  for (int i = 0; i < node->getFunctionSymbol().parameters.size(); i++) {
    llvm::Value *argValue = F->arg_begin() + i;
    argValue->setName(parameterNames[i]);

    if (argValue->getType() != argTypes[i]) {
      this->_irUtils->logError("Argument type mismatch in function " +
                               functionName);
    }

    llvm::AllocaInst *variable =
        Builder->CreateAlloca(argTypes[i], nullptr, parameterNames[i]);

    this->_irUtils->setNamedValueAlloca(parameterNames[i], variable,
                                        this->_NamedValuesAllocaStack);

    Builder->CreateStore(argValue, variable);

    this->_irUtils->setNamedValue(parameterNames[i], argValue,
                                  this->_NamedValuesStack);
  }

  this->generateEvaluateStatement(node->getBodyPtr().get());

  if (this->_returnAllocaStack.top().first != Utils::type::NOTHING &&
      this->_returnAllocaStack.top().second == 0) {

    this->_irUtils->logError("Function return type is not Nothing, return "
                             "expression not found");
  }

  if (node->getFunctionSymbol().getReturnType() == Utils::type::NOTHING) {
    Builder->CreateRetVoid();
  } else {
    Builder->CreateRet(this->_irUtils->getDefaultValue(
        node->getFunctionSymbol().getReturnType()));
  }

  this->_returnAllocaStack.pop();
  this->_NamedValuesStack.pop();
  this->_NamedValuesAllocaStack.pop();

  llvm::verifyFunction(*F);

  this->_irUtils->setNamedValue(functionName, F, this->_NamedValuesStack);

  this->_irUtils->setNamedValueAlloca(functionName, nullptr,
                                      this->_NamedValuesAllocaStack);

  this->_irUtils->setNamedValueAlloca(functionName, nullptr,
                                      this->_NamedValuesAllocaStack);
}
void IRGenerator::generateUserDefinedFunctionOnFly(
    BoundFunctionDeclaration *node, std::vector<llvm::Value *> callArgs) {

  std::string functionName = node->_functionSymbol.name;

  this->_irUtils->setCurrentSourceLocation(node->getLocation());

  std::vector<llvm::Type *> argTypes;
  for (int i = 0; i < node->_functionSymbol.parameters.size(); i++) {
    argTypes.push_back(callArgs[i]->getType());
  }
  llvm::Type *returnType =
      this->_irUtils->getReturnType(node->getFunctionSymbol().getReturnType());

  this->_returnAllocaStack.push({node->getFunctionSymbol().getReturnType(), 0});

  llvm::FunctionType *FT = llvm::FunctionType::get(returnType, argTypes, false);

  llvm::Function *F = llvm::Function::Create(
      FT, llvm::Function::ExternalLinkage, functionName, *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  this->_NamedValuesStack.push(std::map<std::string, llvm::Value *>());
  this->_NamedValuesAllocaStack.push(
      std::map<std::string, llvm::AllocaInst *>());

  std::vector<std::string> parameterNames;

  for (int i = 0; i < node->_functionSymbol.parameters.size(); i++) {
    parameterNames.push_back(node->_functionSymbol.parameters[i].name);
  }

  for (int i = 0; i < node->_functionSymbol.parameters.size(); i++) {
    llvm::Value *argValue = F->arg_begin() + i;
    argValue->setName(parameterNames[i]);

    llvm::AllocaInst *variable = Builder->CreateAlloca(
        callArgs[i]->getType(), nullptr, parameterNames[i]);

    this->_irUtils->setNamedValueAlloca(parameterNames[i], variable,
                                        this->_NamedValuesAllocaStack);

    Builder->CreateStore(argValue, variable);

    this->_irUtils->setNamedValue(parameterNames[i], argValue,
                                  this->_NamedValuesStack);
  }

  this->generateEvaluateStatement(node->getBodyPtr().get());

  if (this->_returnAllocaStack.top().first != Utils::type::NOTHING &&
      this->_returnAllocaStack.top().second == 0) {

    this->_irUtils->logError("Function return type is not Nothing, return "
                             "expression is not found");
  }

  Builder->CreateRet(
      this->_irUtils->getDefaultValue(node->_functionSymbol.return_type));
  this->_NamedValuesStack.pop();
  this->_NamedValuesAllocaStack.pop();

  llvm::verifyFunction(*F);

  this->_irUtils->setNamedValue(functionName, F, this->_NamedValuesStack);

  this->_irUtils->setNamedValueAlloca(functionName, nullptr,
                                      this->_NamedValuesAllocaStack);

  this->_irUtils->setNamedValueAlloca(functionName, nullptr,
                                      this->_NamedValuesAllocaStack);
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
    // this->declareUserDefinedFunction(functionDeclaration);

    this->_irUtils->logError("Function Declaration is only allowed in global "
                             "scope in this version of the compiler");

    break;
  }

  case BinderKindUtils::BoundNodeKind::BreakStatement: {

    this->_irUtils->incrementCount(
        this->_irUtils->addPrefixToVariableName(FLOWWING_BREAK_COUNT));

    return nullptr;
  }
  case BinderKindUtils::BoundNodeKind::ContinueStatement: {

    this->_irUtils->incrementCount(
        this->_irUtils->addPrefixToVariableName(FLOWWING_CONTINUE_COUNT));

    return nullptr;
  }
  case BinderKindUtils::BoundNodeKind::ReturnStatement: {
    BoundReturnStatement *returnStatement = (BoundReturnStatement *)node;

    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    llvm::Function *function = currentBlock->getParent();

    llvm::BasicBlock *returnBlock =
        llvm::BasicBlock::Create(*TheContext, "returnBlock", function);

    llvm::BasicBlock *mergeBlock =
        llvm::BasicBlock::Create(*TheContext, "mergeBlock", function);

    Builder->CreateBr(returnBlock);

    Builder->SetInsertPoint(returnBlock);

    this->_irUtils->setCurrentSourceLocation(returnStatement->getLocation());

    llvm::Value *returnValue = nullptr; // default return value

    llvm::Value *hasError = Builder->getFalse();
    std::string errorMessage = "";

    if (this->_returnAllocaStack.top().first != Utils::type::NOTHING &&
        returnStatement->getReturnExpressionPtr() == nullptr) {

      errorMessage = "Function return type is not Nothing, return "
                     "expression is not found";
      this->_irUtils->logError(errorMessage);
    } else if (this->_returnAllocaStack.top().first == Utils::type::NOTHING &&
               returnStatement->getReturnExpressionPtr() != nullptr) {

      errorMessage = "Function return type is Nothing, return "
                     "expression is found";
      this->_irUtils->logError(errorMessage);
    } else if (returnStatement->getReturnExpressionPtr() != nullptr) {
      returnValue = this->generateEvaluateExpressionStatement(
          returnStatement->getReturnExpressionPtr().get());

      if (this->_returnAllocaStack.top().first !=
          this->_irUtils->getReturnType(returnValue->getType())) {
        errorMessage =
            "Return Type Mismatch " +
            Utils::typeToString(this->_returnAllocaStack.top().first) +
            " is expected but " +
            Utils::typeToString(
                this->_irUtils->getReturnType(returnValue->getType())) +
            " is found";
        this->_irUtils->logError(errorMessage);
      }
    }

    if (returnStatement->getReturnExpressionPtr() != nullptr &&
        this->_returnAllocaStack.top().first != Utils::type::NOTHING) {

      returnValue = this->generateEvaluateExpressionStatement(
          returnStatement->getReturnExpressionPtr().get());

      this->_returnAllocaStack.top().second += 1;

      // create alloca for return value

      Builder->CreateRet(returnValue);

    } else {
      Builder->CreateRetVoid();
    }

    Builder->SetInsertPoint(mergeBlock);

    return returnValue;
    break;
  }
  default: {
    break;
  }
  }

  return nullptr;
}

int IRGenerator::executeGeneratedCode() {

  llvm::Function *evaluateBlockStatement =
      TheModule->getFunction(FLOWWING_GLOBAL_ENTRY_POINT);

  std::string errorMessage;
  llvm::ExecutionEngine *executionEngine =
      llvm::EngineBuilder(std::move(TheModule))
          .setErrorStr(&errorMessage)
          .setEngineKind(llvm::EngineKind::JIT)
          .create();
  if (!executionEngine) {
    llvm::errs() << "Failed to create Execution Engine: " << errorMessage
                 << "\n";
  }

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

  } catch (const std::exception &e) {
    std::cerr << e.what();
  }
  delete executionEngine;
  return hasError;
}
