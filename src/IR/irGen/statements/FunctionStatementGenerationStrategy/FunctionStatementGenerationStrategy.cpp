#include "FunctionStatementGenerationStrategy.h"

FunctionStatementGenerationStrategy::FunctionStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *FunctionStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  BoundFunctionDeclaration *functionDeclaration =
      static_cast<BoundFunctionDeclaration *>(statement);

  if (!functionDeclaration->hasParameterTypes()) {
    return nullptr;
  }
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      functionDeclaration->getLocation());

  std::string functionName = functionDeclaration->getFunctionSymbol().name;

  std::vector<llvm::Type *> argTypes;
  for (int i = 0;
       i < functionDeclaration->getFunctionSymbol().parameters.size(); i++) {
    llvm::Type *type =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            functionDeclaration->getFunctionSymbol().parameters[i].type);
    argTypes.push_back(type);
  }
  llvm::Type *returnType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          functionDeclaration->getFunctionSymbol().getReturnType());

  _codeGenerationContext->getReturnAllocaStack().push(
      {functionDeclaration->getFunctionSymbol().getReturnType(), 0});

  llvm::Function *F = TheModule->getFunction(functionName);
  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());

  _codeGenerationContext->getAllocaChain()->addHandler(new AllocaTable());

  std::vector<std::string> parameterNames;

  for (int i = 0;
       i < functionDeclaration->getFunctionSymbol().parameters.size(); i++) {
    parameterNames.push_back(
        functionDeclaration->getFunctionSymbol().parameters[i].name);
  }

  for (int i = 0;
       i < functionDeclaration->getFunctionSymbol().parameters.size(); i++) {
    llvm::Value *argValue = F->arg_begin() + i;
    argValue->setName(parameterNames[i]);

    if (argValue->getType() != argTypes[i]) {
      _codeGenerationContext->getLogger()->LogError(
          "Argument type mismatch in function " + functionName +
          " for parameter " + parameterNames[i] + " expected " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(argTypes[i]) +
          " but found " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              argValue->getType()));
    }

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

  _statementGenerationFactory
      ->createStrategy(functionDeclaration->getBodyPtr().get()->getKind())
      ->generateStatement(functionDeclaration->getBodyPtr().get());

  if (_codeGenerationContext->getReturnAllocaStack().top().first !=
          Utils::type::NOTHING &&
      _codeGenerationContext->getReturnAllocaStack().top().second == 0) {

    _codeGenerationContext->getLogger()->LogError(
        "Function return type is not Nothing, return expression not found");
  }

  if (functionDeclaration->getFunctionSymbol().getReturnType() ==
      Utils::type::NOTHING) {
    Builder->CreateRetVoid();
  } else {
    Builder->CreateRet(_codeGenerationContext->getMapper()->getDefaultValue(
        functionDeclaration->getFunctionSymbol().getReturnType()));
  }

  _codeGenerationContext->getReturnAllocaStack().pop();

  _codeGenerationContext->getNamedValueChain()->removeHandler();

  _codeGenerationContext->getAllocaChain()->removeHandler();

  _codeGenerationContext->getNamedValueChain()->setNamedValue(functionName, F);

  _codeGenerationContext->getAllocaChain()->setAllocaInst(functionName,
                                                          nullptr);

  return nullptr;
}

llvm::Value *FunctionStatementGenerationStrategy::generateStatementOnFly(
    BoundFunctionDeclaration *node, std::vector<llvm::Value *> callArgs) {

  std::string functionName = node->_functionSymbol.name;

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      node->getLocation());

  std::vector<llvm::Type *> argTypes;
  for (int i = 0; i < callArgs.size(); i++) {
    argTypes.push_back(callArgs[i]->getType());
  }
  llvm::Type *returnType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          node->_functionSymbol.getReturnType());

  _codeGenerationContext->getReturnAllocaStack().push(
      {node->getFunctionSymbol().getReturnType(), 0});

  llvm::FunctionType *FT = llvm::FunctionType::get(returnType, argTypes, false);

  llvm::Function *F = llvm::Function::Create(
      FT, llvm::Function::ExternalLinkage, functionName, *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  Builder->SetInsertPoint(entryBlock);

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());

  _codeGenerationContext->getAllocaChain()->addHandler(new AllocaTable());

  std::vector<std::string> parameterNames;

  for (int i = 0; i < node->_functionSymbol.parameters.size(); i++) {
    parameterNames.push_back(node->_functionSymbol.parameters[i].name);
  }

  for (int i = 0; i < node->_functionSymbol.parameters.size(); i++) {
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

  _statementGenerationFactory
      ->createStrategy(node->getBodyPtr().get()->getKind())
      ->generateStatement(node->getBodyPtr().get());

  if (_codeGenerationContext->getReturnAllocaStack().top().first !=
          Utils::type::NOTHING &&
      _codeGenerationContext->getReturnAllocaStack().top().second == 0) {

    _codeGenerationContext->getLogger()->LogError(
        "Function return type is not Nothing, return expression is not found");

    return nullptr;
  }

  Builder->CreateRet(_codeGenerationContext->getMapper()->getDefaultValue(
      node->_functionSymbol.return_type));

  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();

  _codeGenerationContext->getNamedValueChain()->setNamedValue(functionName, F);
  _codeGenerationContext->getAllocaChain()->setAllocaInst(functionName,
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