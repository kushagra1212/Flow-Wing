#include "FunctionStatementGenerationStrategy.h"

FunctionStatementGenerationStrategy::FunctionStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *FunctionStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generate(statement);
}

llvm::Value *FunctionStatementGenerationStrategy::generate(
    BoundStatement *statement, std::vector<std::string> classParams,
    llvm::Type *classType, std::vector<std::string> classVariables) {
  BoundFunctionDeclaration *functionDeclaration =
      static_cast<BoundFunctionDeclaration *>(statement);

  //   if (!functionDeclaration->getParametersRef().size()) {
  //     return nullptr;
  //   }
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      functionDeclaration->getLocation());

  _codeGenerationContext->getReturnAllocaStack().push(0);
  llvm::Function *F =
      TheModule->getFunction(functionDeclaration->getFunctionNameRef());

  if (!F) {
    _codeGenerationContext->getLogger()->LogError(
        "Function " + functionDeclaration->getFunctionNameRef() +
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
  _codeGenerationContext->getTypeChain()->addHandler(
      std::make_unique<TypeTable>());
  _codeGenerationContext->getCustomTypeChain()->addHandler(
      std::make_unique<CustomTypeStatementTable>());
  std::vector<std::string> parameterNames;

  for (size_t i = 0; i < functionDeclaration->getParametersRef().size(); i++) {
    parameterNames.push_back(
        functionDeclaration->getParametersRef()[i]->getVariableName());
  }
  size_t paramsSize = parameterNames.size();

  for (auto &classParam : classParams) {
    parameterNames.push_back(classParam);
  }

  std::unique_ptr<ContainerAssignmentExpressionGenerationStrategy>
      containerAssignmentExpressionGenerationStrategy(
          new ContainerAssignmentExpressionGenerationStrategy(
              _codeGenerationContext));
  llvm::LLVMContext *TheContext = _codeGenerationContext->getContext().get();

  const std::vector<std::unique_ptr<LLVMType>> &llvmArgsTypes =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(
          functionDeclaration->getFunctionNameRef());

  for (size_t i = 0; i < parameterNames.size(); i++) {

    llvm::Value *argValue = F->arg_begin() + i;

    if (i >= paramsSize) {

      llvm::StructType *structT = llvm::cast<llvm::StructType>(classType);

      for (int j = 0; j < structT->getNumElements(); j++) {
        llvm::Type *type = structT->getElementType(j);

        llvm::Value *elementPtr = Builder->CreateGEP(
            structT, argValue, {Builder->getInt32(0), Builder->getInt32(j)});
        _codeGenerationContext->getAllocaChain()->setPtr(classVariables[j],
                                                         {elementPtr, type});
      }

      //   llvm::AllocaInst *Alloca =
      //       Builder->CreateAlloca(structT, nullptr, parameterNames[i]);
      //   Builder->CreateStore(argValue, Alloca);

      //   llvm::Value *loaded =
      //       Builder->CreateGEP(llvm::Type::getInt32Ty(*TheContext), Alloca,
      //                          {Builder->getInt32(0), Builder->getInt32(0)});

      //   Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), loaded);
      //   llvm::Value *intPtr = Builder->CreateBitCast(
      //       argValue, llvm::PointerType::get(classType, 0));
      //   llvm::Value *ptr = Builder->CreateGEP(
      //       classType, argValue, {Builder->getInt32(0),
      //       Builder->getInt32(0)});
      //   llvm::Value *load = Builder->CreateLoad(
      //       llvm::Type::getInt32Ty(*TheContext),
      //       );

      _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                       {argValue, classType});
      continue;
    }

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        functionDeclaration->getParametersRef()[i]->getLocation());
    if (llvmArgsTypes[i]->isPointer() &&
        !llvm::isa<llvm::PointerType>(argValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Type mismatch in function parameter " + parameterNames[i]);
    }

    if (llvm::isa<llvm::PointerType>(argValue->getType()) &&
        llvmArgsTypes[i]->isPointerToArray()) {
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
          llvmArrayPtrType->getDimensions(), llvmArrayPtrType->getDimensions());

      _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                       {variable, arrayType});

    } else if (llvmArgsTypes[i]->isPointerToObject()) {
      LLVMObjectType *llvmObjectType =
          static_cast<LLVMObjectType *>(llvmArgsTypes[i].get());

      llvm::StructType *structType =
          llvm::cast<llvm::StructType>(llvmObjectType->getStructType());

      std::unique_ptr<ObjectAssignmentExpressionGenerationStrategy>
          objAssignSt =
              std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
                  _codeGenerationContext);

      llvm::Value *structPtr =
          Builder->CreateAlloca(structType, nullptr, parameterNames[i]);

      _codeGenerationContext->getAllocaChain()->setPtr(parameterNames[i],
                                                       {structPtr, structType});

      objAssignSt->copyOject(structType, structPtr, argValue);

    } else if (_codeGenerationContext->getDynamicType()->isDyn(
                   llvmArgsTypes[i]->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Dynamic type is not supported in function parameter " +
          parameterNames[i].substr(0, parameterNames[i].find_first_of("[")));
      return nullptr;
    } else {
      llvm::AllocaInst *variable = Builder->CreateAlloca(
          argValue->getType(), nullptr, parameterNames[i]);
      Builder->CreateStore(argValue, variable);
      _codeGenerationContext->getAllocaChain()->setPtr(
          parameterNames[i], {variable, argValue->getType()});
      _codeGenerationContext->getNamedValueChain()->setNamedValue(
          parameterNames[i], argValue);
    }
  }

  _statementGenerationFactory
      ->createStrategy(functionDeclaration->getBodyRef().get()->getKind())
      ->generateStatement(functionDeclaration->getBodyRef().get());

  llvm::Type *returnType =
      _codeGenerationContext->getReturnTypeHandler()
          ->getReturnType(functionDeclaration->getFunctionNameRef())
          ->getType();
  if (returnType != llvm::Type::getVoidTy(*TheContext) &&
      _codeGenerationContext->getReturnAllocaStack().top() == 0) {
    _codeGenerationContext->getLogger()->LogError(
        "Function return type is not Nothing, return expression not found in "
        "function " +
        functionDeclaration->getFunctionNameRef());

    return nullptr;
  }

  if (returnType == llvm::Type::getVoidTy(*TheContext)) {
    Builder->CreateRetVoid();
  } else {
    Builder->CreateRet(
        _codeGenerationContext->getMapper()->getDefaultValue(returnType));
  }

  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();
  _codeGenerationContext->getTypeChain()->removeHandler();
  _codeGenerationContext->getCustomTypeChain()->removeHandler();

  _codeGenerationContext->getReturnAllocaStack().pop();

  _codeGenerationContext->getNamedValueChain()->setNamedValue(
      functionDeclaration->getFunctionNameRef(), F);

  _codeGenerationContext->getAllocaChain()->setAllocaInst(
      functionDeclaration->getFunctionNameRef(), nullptr);

  return nullptr;
}

llvm::Value *FunctionStatementGenerationStrategy::generateStatementOnFly(
    BoundFunctionDeclaration *fd, std::vector<llvm::Value *> callArgs) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      fd->getLocation());

  std::vector<llvm::Type *> argTypes;
  for (int i = 0; i < callArgs.size(); i++) {
    argTypes.push_back(callArgs[i]->getType());
  }

  llvm::Type *returnType = nullptr;

  llvm::FunctionType *FT = llvm::FunctionType::get(returnType, argTypes, false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             fd->getFunctionNameRef(), *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());

  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());

  _codeGenerationContext->getTypeChain()->addHandler(
      std::make_unique<TypeTable>());

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

    _codeGenerationContext->getNamedValueChain()->setNamedValue(
        parameterNames[i], argValue);
  }

  _statementGenerationFactory->createStrategy(fd->getBodyRef().get()->getKind())
      ->generateStatement(fd->getBodyRef().get());

  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();
  _codeGenerationContext->getTypeChain()->removeHandler();
  _codeGenerationContext->getCustomTypeChain()->removeHandler();

  _codeGenerationContext->getNamedValueChain()->setNamedValue(
      fd->getFunctionNameRef(), F);
  _codeGenerationContext->getAllocaChain()->setAllocaInst(
      fd->getFunctionNameRef(), nullptr);

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