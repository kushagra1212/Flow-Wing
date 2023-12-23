#include "VariableDeclarationStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

VariableDeclarationStatementGenerationStrategy::
    VariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handleTypedPrimitiveLocalVariableDeclr(const std::string &variableName,
                                           const Utils::type &variableType,
                                           llvm::Value *rhsValue) {
  llvm::Type *llvmType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          variableType);

  llvm::AllocaInst *v =
      Builder->CreateAlloca(llvmType, nullptr, variableName.c_str());

  _codeGenerationContext->getAllocaChain()->setAllocaInst(variableName, v);

  Builder->CreateStore(rhsValue, v);

  return rhsValue;
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handleUnTypedPrimitiveLocalVariableDeclr(const std::string &variableName,
                                             llvm::Value *rhsValue) {
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

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handlePrimitiveLocalVariableDeclr(const std::string &variableName,
                                      const Utils::type &variableType,
                                      llvm::Value *rhsValue) {

  _codeGenerationContext->getNamedValueChain()->setNamedValue(variableName,
                                                              rhsValue);
  // Handle Local Static Typed Variable
  if (Utils::isStaticTypedPrimitiveType(variableType)) {
    return handleTypedPrimitiveLocalVariableDeclr(variableName, variableType,
                                                  rhsValue);
  }

  // Handle Local Dynamic Typed Variable
  return handleUnTypedPrimitiveLocalVariableDeclr(variableName, rhsValue);
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {

  if (!canGenerateStatement(statement)) {
    return nullptr;
  }

  _codeGenerationContext->getNamedValueChain()->setNamedValue(_variableName,
                                                              _rhsValue);

  // Handle Primitive Local Variable
  return handlePrimitiveLocalVariableDeclr(_variableName, _variableType,
                                           _rhsValue);
}

llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  if (!canGenerateStatement(statement)) {
    return nullptr;
  }

  // Handle Global Static Typed Variable
  if (Utils::isStaticTypedPrimitiveType(_variableType)) {

    llvm::Type *llvmType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            _variableType);

    llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
        *TheModule, llvmType, false, llvm::GlobalValue::ExternalLinkage,
        llvm::Constant::getNullValue(llvmType), _variableName);

    Builder->CreateStore(_rhsValue, _globalVariable);

    return _rhsValue;
  }

  // Handle Global Dynamic Typed Variable
  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, _codeGenerationContext->getDynamicType()->get(), false,
      llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(
          _codeGenerationContext->getDynamicType()->get()),
      _variableName);

  const uint64_t memberIndex =
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          _rhsValue->getType());

  _codeGenerationContext->getGlobalTypeMap()[_variableName] = memberIndex;

  llvm::Value *elementPtr =
      Builder->CreateStructGEP(_codeGenerationContext->getDynamicType()->get(),
                               _globalVariable, memberIndex);

  Builder->CreateStore(_rhsValue, elementPtr);

  return _rhsValue;
}

bool VariableDeclarationStatementGenerationStrategy::canGenerateStatement(
    BoundStatement *statement) {

  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);

  _variableName = variableDeclaration->getVariable();

  BoundExpression *initializerExp =
      variableDeclaration->getInitializerPtr().get();

  if (!initializerExp) {
    _codeGenerationContext->getLogger()->LogError(
        "Rhs of variable " + _variableName + " is not an expression");
    return false;
  }

  _rhsValue =
      _expressionGenerationFactory->createStrategy(initializerExp->getKind())
          ->generateExpression(initializerExp);

  if (!_rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Rhs of variable " + _variableName + " is not an expression");
    return false;
  }

  _variableType = variableDeclaration->getType();

  if (Utils::isStaticTypedPrimitiveType(_variableType)) {
    if (!_codeGenerationContext->getMapper()->isEquivalentType(
            _variableType, _rhsValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Type mismatch in variable declaration " + _variableName +
          " Expected type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(_variableType) +
          " but got type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              _rhsValue->getType()));
      return false;
    }

    return true;
  }

  if (Utils::isDynamicTypedPrimitiveType(_variableType)) {
    return true;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Type mismatch in variable declaration " + _variableName +
      " Expected type " +
      _codeGenerationContext->getMapper()->getLLVMTypeName(_variableType) +
      " but got type " +
      _codeGenerationContext->getMapper()->getLLVMTypeName(
          _rhsValue->getType()));

  return false;
}