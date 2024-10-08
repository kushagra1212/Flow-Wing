#include "FunctionStatementGenerationStrategy.h"

FunctionStatementGenerationStrategy::FunctionStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context),
      _irCodeGenerator(std::make_unique<IRCodeGenerator>(context)) {}

llvm::Value *FunctionStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generate(statement);
}

llvm::Value *FunctionStatementGenerationStrategy::generate(
    BoundStatement *statement, std::vector<std::string> classParams,
    llvm::Type *classType, std::vector<std::string> classVariables) {

  BoundFunctionDeclaration *functionDeclaration =
      static_cast<BoundFunctionDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      functionDeclaration->getLocation());

  _codeGenerationContext->getReturnAllocaStack().push(0);

  std::string FUNCTION_NAME = functionDeclaration->getFunctionNameRef();

  CODEGEN_DEBUG_LOG("Defining Function : " + FUNCTION_NAME);

  llvm::Function *F = TheModule->getFunction(FUNCTION_NAME);

  if (!F && functionDeclaration->isMemberFunction()) {
    auto [value, type] =
        _codeGenerationContext->getAllocaChain()->getPtr("self");

    if (type && value && llvm::isa<llvm::StructType>(type)) {
      auto structType = llvm::cast<llvm::StructType>(type);
      functionDeclaration->setFunctionName(FUNCTION_NAME);
      F = TheModule->getFunction(FUNCTION_NAME);
    }
  }

  if (!F) {

    _codeGenerationContext->getLogger()->LogError("Function " + FUNCTION_NAME +
                                                  " is not declared");

    return nullptr;
  }

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());
  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());

  std::vector<std::string> parameterNames;

  llvm::Type *returnType = _codeGenerationContext->getReturnTypeHandler()
                               ->getReturnType(FUNCTION_NAME, 0)
                               ->getLLVMType();

  if (_codeGenerationContext->getReturnTypeHandler()
          ->isHavingReturnTypeAsParameter(FUNCTION_NAME, 0)) {
    parameterNames.push_back(FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME);
  }

  for (size_t i = 0; i < functionDeclaration->getParametersRef().size(); i++) {
    parameterNames.push_back(
        functionDeclaration->getParametersRef()[i]->getVariableName());
  }
  size_t paramsSize = parameterNames.size();

  for (auto &classParam : classParams) {
    parameterNames.push_back(classParam);
  }

  llvm::LLVMContext *TheContext = _codeGenerationContext->getContext().get();

  const std::vector<std::unique_ptr<LLVMType>> &llvmArgsTypes =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(FUNCTION_NAME);

  if (parameterNames.size() > paramsSize && classVariables.size()) {

    llvm::Value *argValue = F->arg_begin() + paramsSize;
    llvm::StructType *structT = llvm::cast<llvm::StructType>(classType);

    llvm::Value *classPtr =
        Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), argValue);

    for (int j = 1; j < structT->getNumElements(); j++) {
      llvm::Type *type = structT->getElementType(j);
      if (!type) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            functionDeclaration->getParametersRef()[j - 1]->getLocation());
        _codeGenerationContext->getLogger()->LogError(
            "Type not found for variable " + classVariables[j - 1]);
        return nullptr;
      }
      llvm::Value *elementPtr = Builder->CreateStructGEP(structT, classPtr, j);
      _codeGenerationContext->getAllocaChain()->setPtr(classVariables[j - 1],
                                                       {elementPtr, type});
    }

    _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[paramsSize],
                                                     {argValue, classType});
  }

  for (size_t i = 0; i < parameterNames.size(); i++) {
    size_t callIndex = i;
    llvm::Value *argValue = F->arg_begin() + i;
    if (i >= paramsSize) {
      break;
    }

    if (parameterNames[i] == FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME) {

      _codeGenerationContext->getAllocaChain()->setPtr(
          parameterNames[i], {argValue, llvmArgsTypes[i]->getLLVMType()});

      continue;
    }

    if (parameterNames[0] == FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME) {
      callIndex = i - 1;
    }

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        functionDeclaration->getParametersRef()[callIndex]->getLocation());
    if (i < llvmArgsTypes.size() && llvmArgsTypes[i]->isPointer() &&
        !llvm::isa<llvm::PointerType>(argValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Type mismatch in function parameter " + parameterNames[i]);
    }

    if (functionDeclaration->getParametersRef()[callIndex]
            ->getHasInOutKeyword()) {

      if (llvm::isa<llvm::PointerType>(argValue->getType()) &&
          llvmArgsTypes[i]->isPointerToArray()) {

        llvm::ArrayType *arrayType =
            llvm::cast<llvm::ArrayType>(llvmArgsTypes[i]->getLLVMType());
        _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                         {argValue, arrayType});
      } else if (llvmArgsTypes[i]->isPointerToObject()) {
        llvm::StructType *structType =
            llvm::cast<llvm::StructType>(llvmArgsTypes[i]->getLLVMType());

        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i], {argValue, structType});

      } else if (llvmArgsTypes[i]->isPointerToPrimitive()) {

        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i], {argValue, llvmArgsTypes[i]->getLLVMType()});
      } else if (llvmArgsTypes[i]->isPointerToFunction()) {

        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i], {argValue, llvmArgsTypes[i]->getLLVMType()});
      } else {
        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i],
            {argValue, _codeGenerationContext->getDynamicType()->get()});
      }
    } else {
      if (llvmArgsTypes.size() > i &&
          llvm::isa<llvm::PointerType>(argValue->getType()) &&
          llvmArgsTypes[i]->isPointerToArray()) {
        std::unique_ptr<ContainerAssignmentExpressionGenerationStrategy>
            containerAssignmentExpressionGenerationStrategy = std::make_unique<
                ContainerAssignmentExpressionGenerationStrategy>(
                _codeGenerationContext);

        LLVMArrayType *llvmArrayPtrType =
            static_cast<LLVMArrayType *>(llvmArgsTypes[i].get());

        llvm::ArrayType *arrayType =
            llvm::cast<llvm::ArrayType>(llvmArrayPtrType->getElementType());

        llvm::Value *variable =
            Builder->CreateAlloca(arrayType, nullptr, parameterNames[i]);

        _codeGenerationContext->setArrayElementTypeMetadata(
            variable, llvmArrayPtrType->getArrayElementType());

        _codeGenerationContext->setArraySizeMetadata(
            variable, llvmArrayPtrType->getDimensions());

        containerAssignmentExpressionGenerationStrategy->createExpression(
            arrayType, variable, argValue, arrayType,
            llvmArrayPtrType->getArrayElementType(),
            llvmArrayPtrType->getDimensions(),
            llvmArrayPtrType->getDimensions());

        _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                         {variable, arrayType});

      } else if (i < llvmArgsTypes.size() &&
                 llvmArgsTypes[i]->isPointerToObject()) {
        LLVMObjectType *llvmObjectType =
            static_cast<LLVMObjectType *>(llvmArgsTypes[i].get());

        llvm::StructType *structType =
            llvm::cast<llvm::StructType>(llvmObjectType->getStructType());

        llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
            structType, parameterNames[i],
            _codeGenerationContext->isValidClassType(structType)
                ? BinderKindUtils::MemoryKind::Heap
                : BinderKindUtils::MemoryKind::Stack);

        if (_codeGenerationContext->isValidClassType(structType)) {

          llvm::Value *classPtr = Builder->CreateLoad(
              llvm::Type::getInt8PtrTy(*TheContext), argValue);

          Builder->CreateStore(Builder->CreateLoad(structType, classPtr), ptr);

          llvm::Value *lVar = _codeGenerationContext->createMemoryGetPtr(
              llvm::Type::getInt8PtrTy(*TheContext), parameterNames[i],
              BinderKindUtils::MemoryKind::Stack);

          Builder->CreateStore(ptr, lVar);

          _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                           {lVar, structType});
        } else {

          Builder->CreateStore(Builder->CreateLoad(structType, argValue), ptr);

          _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                           {ptr, structType});
        }

      } else if (i < llvmArgsTypes.size() &&
                 llvmArgsTypes[i]->isPointerToFunction()) {
        LLVMFunctionType *llvmFunctionType =
            static_cast<LLVMFunctionType *>(llvmArgsTypes[i].get());

        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i], {argValue, llvmArgsTypes[i]->getLLVMType()});

      } else if (i < llvmArgsTypes.size() &&
                 llvmArgsTypes[i]->isPointerToPrimitive()) {
        LLVMPrimitiveType *llvmPrimitiveType =
            static_cast<LLVMPrimitiveType *>(llvmArgsTypes[i].get());

        llvm::AllocaInst *variable = Builder->CreateAlloca(
            llvmPrimitiveType->getPrimitiveType(), nullptr, parameterNames[i]);

        llvm::Value *loaded = Builder->CreateLoad(
            llvmPrimitiveType->getPrimitiveType(), argValue);
        Builder->CreateStore(loaded, variable);
        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i],
            {variable, llvmPrimitiveType->getPrimitiveType()});

        // _codeGenerationContext->getNamedValueChain()->setNamedValue(
        //     parameterNames[i], loaded);
      } else if (i < llvmArgsTypes.size()) {

        llvm::Value *alloca = Builder->CreateAlloca(
            llvmArgsTypes[i]->getLLVMType(), nullptr, parameterNames[i]);
        Builder->CreateStore(argValue, alloca);
        argValue = alloca;
        _codeGenerationContext->getAllocaChain()->setPtr(
            parameterNames[i], {
                                   argValue,
                                   llvmArgsTypes[i]->getType(),
                               });
      }
    }
  }

  _irCodeGenerator->declareVariables(functionDeclaration->getBodyRef().get(),
                                     false);
  _statementGenerationFactory
      ->createStrategy(functionDeclaration->getBodyRef().get()->getKind())
      ->generateStatement(functionDeclaration->getBodyRef().get());

  if (returnType != llvm::Type::getVoidTy(*TheContext) &&
      _codeGenerationContext->getReturnAllocaStack().top() == 0) {
    _codeGenerationContext->getLogger()->LogError(
        "Function return type is not Nothing, return expression not found in "
        "function " +
        FUNCTION_NAME);

    return nullptr;
  }

  if ((parameterNames.size() &&
       parameterNames[0] == FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME) ||
      returnType == llvm::Type::getVoidTy(*TheContext)) {
    Builder->CreateRetVoid();
  } else {
    Builder->CreateRet(
        _codeGenerationContext->getMapper()->getDefaultValue(returnType));
  }

  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();

  _codeGenerationContext->getReturnAllocaStack().pop();

  //   _codeGenerationContext->getNamedValueChain()->setNamedValue(FUNCTION_NAME,
  //   F);

  _codeGenerationContext->getAllocaChain()->setAllocaInst(FUNCTION_NAME,
                                                          nullptr);

  return F;
}

llvm::Value *FunctionStatementGenerationStrategy::generateStatementOnFly(
    BoundFunctionDeclaration *fd, std::vector<llvm::Value *> callArgs) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      fd->getLocation());

  std::string FUNCTION_NAME = fd->getFunctionNameRef();
  std::vector<llvm::Type *> argTypes;
  for (int i = 0; i < callArgs.size(); i++) {
    argTypes.push_back(callArgs[i]->getType());
  }

  llvm::Type *returnType = nullptr;

  llvm::FunctionType *FT = llvm::FunctionType::get(returnType, argTypes, false);

  llvm::Function *F = llvm::Function::Create(
      FT, llvm::Function::ExternalLinkage, FUNCTION_NAME, *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());

  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());

  std::vector<std::string> parameterNames;

  for (int i = 0; i < fd->getParametersRef().size(); i++) {
    parameterNames.push_back(fd->getParametersRef()[i]->getVariableName());
  }

  for (int i = 0; i < fd->getParametersRef().size(); i++) {
    llvm::Value *argValue = F->arg_begin() + i;
    argValue->setName(parameterNames[i]);

    llvm::AllocaInst *variable =
        Builder->CreateAlloca(_codeGenerationContext->getDynamicType()->get(),
                              nullptr, parameterNames[i]);

    _codeGenerationContext->getAllocaChain()->setPtr(
        parameterNames[i],
        {variable, _codeGenerationContext->getDynamicType()->get()});

    _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
        variable, argValue, argValue->getType(), parameterNames[i]);
  }

  _statementGenerationFactory->createStrategy(fd->getBodyRef().get()->getKind())
      ->generateStatement(fd->getBodyRef().get());

  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();

  _codeGenerationContext->getAllocaChain()->setAllocaInst(FUNCTION_NAME,
                                                          nullptr);

  return nullptr;
}

llvm::Value *FunctionStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundFunctionDeclaration *functionDeclaration =
      static_cast<BoundFunctionDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      functionDeclaration->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Function Declaration is only allowed in global "
      "scope in this version of the compiler");

  return nullptr;
}