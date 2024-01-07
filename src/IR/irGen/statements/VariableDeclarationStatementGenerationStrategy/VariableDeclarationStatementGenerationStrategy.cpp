#include "VariableDeclarationStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../ContainerDeclarationStatementGenerationStrategy/ContainerDeclarationStatementGenerationStrategy.h"

VariableDeclarationStatementGenerationStrategy::
    VariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handleTypedPrimitiveLocalVariableDeclr(
        const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
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

  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      variable, rhsValue, rhsValue->getType(), variableName);

  return rhsValue;
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handlePrimitiveLocalVariableDeclr(
        const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
        llvm::Value *rhsValue) {
  _codeGenerationContext->getNamedValueChain()->setNamedValue(variableName,
                                                              rhsValue);

  // Handle Local Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(variableType)) {
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

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    std::unique_ptr<ContainerDeclarationStatementGenerationStrategy>
        contDecGenStrat =
            std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    return contDecGenStrat->generateStatement(statement);
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

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    std::unique_ptr<ContainerDeclarationStatementGenerationStrategy>
        contDecGenStrat =
            std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    return contDecGenStrat->generateGlobalStatement(statement);
  }

  // Handle Global Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {
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

  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      _globalVariable, _rhsValue, _rhsValue->getType(),
      FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX + _variableName);

  return _rhsValue;
}

bool VariableDeclarationStatementGenerationStrategy::canGenerateStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);

  _variableName = variableDeclaration->getVariableName();

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

  _variableType = variableDeclaration->getTypeExpression()->getSyntaxType();

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE ||
      _variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE ||
      _variableType == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    return true;
  }

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