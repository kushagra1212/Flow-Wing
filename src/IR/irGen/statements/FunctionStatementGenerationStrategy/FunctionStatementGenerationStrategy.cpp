#include "FunctionStatementGenerationStrategy.h"

FunctionStatementGenerationStrategy::FunctionStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *FunctionStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  BoundFunctionDeclaration *functionDeclaration =
      static_cast<BoundFunctionDeclaration *>(statement);

  if (!functionDeclaration->getParametersRef().size()) {
    return nullptr;
  }
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      functionDeclaration->getLocation());

  llvm::Type *returnType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          functionDeclaration->getReturnType());

  _codeGenerationContext->getReturnAllocaStack().push(
      {functionDeclaration->getReturnType(), 0});

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

  _codeGenerationContext->getAllocaChain()->addHandler(new AllocaTable());

  std::vector<std::string> parameterNames;

  for (size_t i = 0; i < functionDeclaration->getParametersRef().size(); i++) {
    parameterNames.push_back(
        functionDeclaration->getParametersRef()[i]->getVariableNameRef());
  }
  std::unique_ptr<ContainerAssignmentExpressionGenerationStrategy>
      containerAssignmentExpressionGenerationStrategy(
          new ContainerAssignmentExpressionGenerationStrategy(
              _codeGenerationContext));
  llvm::LLVMContext *TheContext = _codeGenerationContext->getContext().get();

  const std::vector<std::unique_ptr<LLVMType>> &llvmArgsTypes =
      _codeGenerationContext->getArgsTypeHandler()->getArgsType(
          functionDeclaration->getFunctionNameRef());

  for (size_t i = 0; i < functionDeclaration->getParametersRef().size(); i++) {

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        functionDeclaration->getParametersRef()[i]
            ->getIdentifierExpressionPtr()
            ->getLocation());

    llvm::Value *argValue = F->arg_begin() + i;
    argValue->setName(parameterNames[i]);

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

      llvm::AllocaInst *variable =
          Builder->CreateAlloca(arrayType, nullptr, parameterNames[i]);

      containerAssignmentExpressionGenerationStrategy->createExpression(
          arrayType, variable, Builder->getInt32(arrayType->getNumElements()),
          Builder->getInt32(arrayType->getNumElements()), argValue, arrayType);

      _codeGenerationContext->getAllocaChain()->setAllocaInst(parameterNames[i],
                                                              variable);

    } else {

      llvm::AllocaInst *variable = Builder->CreateAlloca(
          argValue->getType(), nullptr, parameterNames[i]);
      Builder->CreateStore(argValue, variable);
      _codeGenerationContext->getAllocaChain()->setAllocaInst(parameterNames[i],
                                                              variable);
      _codeGenerationContext->getNamedValueChain()->setNamedValue(
          parameterNames[i], argValue);
    }
  }

  _statementGenerationFactory
      ->createStrategy(functionDeclaration->getBodyRef().get()->getKind())
      ->generateStatement(functionDeclaration->getBodyRef().get());

  if (_codeGenerationContext->getReturnAllocaStack().top().first !=
          Utils::type::NOTHING &&
      _codeGenerationContext->getReturnAllocaStack().top().second == 0) {

    _codeGenerationContext->getLogger()->LogError(
        "Function return type is not Nothing, return expression not found");
  }

  if (functionDeclaration->getReturnType() == Utils::type::NOTHING) {
    Builder->CreateRetVoid();
  } else {
    Builder->CreateRet(_codeGenerationContext->getMapper()->getDefaultValue(
        functionDeclaration->getReturnType()));
  }

  _codeGenerationContext->getReturnAllocaStack().pop();

  _codeGenerationContext->getNamedValueChain()->removeHandler();

  _codeGenerationContext->getAllocaChain()->removeHandler();

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
  llvm::Type *returnType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          fd->getReturnType());

  _codeGenerationContext->getReturnAllocaStack().push({fd->getReturnType(), 0});

  llvm::FunctionType *FT = llvm::FunctionType::get(returnType, argTypes, false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             fd->getFunctionNameRef(), *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());

  _codeGenerationContext->getAllocaChain()->addHandler(new AllocaTable());

  std::vector<std::string> parameterNames;

  for (int i = 0; i < fd->getParametersRef().size(); i++) {
    parameterNames.push_back(fd->getParametersRef()[i]->getVariableNameRef());
  }

  for (int i = 0; i < fd->getParametersRef().size(); i++) {
    llvm::Value *argValue = F->arg_begin() + i;
    argValue->setName(parameterNames[i]);

    llvm::AllocaInst *variable =
        Builder->CreateAlloca(_codeGenerationContext->getDynamicType()->get(),
                              nullptr, parameterNames[i]);

    _codeGenerationContext->getAllocaChain()->setAllocaInst(parameterNames[i],
                                                            variable);

    _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
        variable, argValue, argValue->getType(), parameterNames[i]);

    _codeGenerationContext->getNamedValueChain()->setNamedValue(
        parameterNames[i], argValue);
  }

  _statementGenerationFactory->createStrategy(fd->getBodyRef().get()->getKind())
      ->generateStatement(fd->getBodyRef().get());

  if (_codeGenerationContext->getReturnAllocaStack().top().first !=
          Utils::type::NOTHING &&
      _codeGenerationContext->getReturnAllocaStack().top().second == 0) {

    _codeGenerationContext->getLogger()->LogError(
        "Function return type is not Nothing, return expression is not found");

    return nullptr;
  }

  Builder->CreateRet(_codeGenerationContext->getMapper()->getDefaultValue(
      fd->getReturnType()));

  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();

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