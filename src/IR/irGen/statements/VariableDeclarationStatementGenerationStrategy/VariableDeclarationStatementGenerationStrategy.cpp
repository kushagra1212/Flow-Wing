#include "VariableDeclarationStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

VariableDeclarationStatementGenerationStrategy::
    VariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *VariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *node =
      static_cast<BoundVariableDeclaration *>(statement);

  std::string variableName = node->getVariable();

  BoundExpression *initializerExp = node->getInitializerPtr().get();

  llvm::Value *rhsValue =
      _expressionGenerationFactory->createStrategy(initializerExp->getKind())
          ->generateExpression(initializerExp);
  Utils::type variableType = node->getType();

  // Handle Type Local Variable
  if (variableType != Utils::type::UNKNOWN) {

    llvm::Type *llvmType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            variableType);

    if (variableType !=
        _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
            rhsValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Type mismatch in variable declaration " + variableName +
          " Expected type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
          " but got type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType()));
      return nullptr;
    }

    _codeGenerationContext->getNamedValueChain()->setNamedValue(variableName,
                                                                rhsValue);

    llvm::AllocaInst *variable =
        Builder->CreateAlloca(llvmType, nullptr, variableName.c_str());

    _codeGenerationContext->getAllocaChain()->setAllocaInst(variableName,
                                                            variable);

    Builder->CreateStore(rhsValue, variable);

    return rhsValue;
  }

  if (variableType != Utils::type::UNKNOWN &&
      _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          rhsValue->getType()) != variableType) {

    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in variable declaration " + variableName +
        " Expected type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
        " but got type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()));
    return nullptr;
  }

  _codeGenerationContext->getNamedValueChain()->setNamedValue(variableName,
                                                              rhsValue);

  // create and load variable

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(_codeGenerationContext->getDynamicType()->get(),
                            nullptr, variableName.c_str());

  _codeGenerationContext->getAllocaChain()->setAllocaInst(variableName,
                                                          variable);

  Builder->CreateStore(
      rhsValue,
      Builder->CreateStructGEP(
          _codeGenerationContext->getDynamicType()->get(), variable,
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              rhsValue->getType())));

  return rhsValue;
}

llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableDeclaration->getLocation());

  std::string variableName = variableDeclaration->getVariable();

  BoundExpression *expression = variableDeclaration->getInitializerPtr().get();
  llvm::Value *rhsValue =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (!rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Rhs of variable " + variableName + " is notthing");
    return nullptr;
  }
  Utils::type variableType = variableDeclaration->getType();

  // Handle Type Global Variable
  if (variableType != Utils::type::UNKNOWN) {

    if (variableType !=
        _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
            rhsValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Type mismatch in variable declaration " + variableName +
          " Expected type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
          " but got type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType()));
      return nullptr;
    }

    llvm::Type *llvmType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            variableType);

    llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
        *TheModule, llvmType, false, llvm::GlobalValue::ExternalLinkage,
        llvm::Constant::getNullValue(llvmType), variableName);

    Builder->CreateStore(rhsValue, _globalVariable);

    return rhsValue;
  }

  if (variableType != Utils::type::UNKNOWN &&
      _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          rhsValue->getType()) != variableType) {

    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in variable declaration " + variableName +
        " Expected type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
        " but got type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()));
    return nullptr;
  }

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, _codeGenerationContext->getDynamicType()->get(), false,
      llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(
          _codeGenerationContext->getDynamicType()->get()),
      variableName);

  llvm::Value *loadedValue = Builder->CreateLoad(
      _codeGenerationContext->getDynamicType()->get(), _globalVariable);

  llvm::Value *updatedValue = Builder->CreateInsertValue(
      loadedValue, rhsValue,
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          rhsValue->getType()));

  _codeGenerationContext->getGlobalTypeMap()[variableName] =
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          rhsValue->getType());

  Builder->CreateStore(updatedValue, _globalVariable);

  return rhsValue;
}