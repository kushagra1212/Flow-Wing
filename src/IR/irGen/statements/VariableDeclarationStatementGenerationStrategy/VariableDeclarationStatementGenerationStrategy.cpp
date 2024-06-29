#include "VariableDeclarationStatementGenerationStrategy.h"
#include "../../declaration/IRCodeGenerator/IRCodeGenerator.h"

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

  _codeGenerationContext->getAllocaChain()->setPtr(variableName, {v, llvmType});

  Builder->CreateStore(rhsValue, v);

  return rhsValue;
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handleUnTypedPrimitiveLocalVariableDeclr(const std::string &variableName,
                                             llvm::Value *rhsValue) {
  llvm::AllocaInst *variable =
      Builder->CreateAlloca(_codeGenerationContext->getDynamicType()->get(),
                            nullptr, variableName.c_str());

  _codeGenerationContext->getAllocaChain()->setPtr(
      variableName,
      {variable, _codeGenerationContext->getDynamicType()->get()});

  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      variable, rhsValue, rhsValue->getType(), variableName);

  return rhsValue;
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handlePrimitiveLocalVariableDeclr(
        const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
        llvm::Value *rhsValue) {

  // Handle Local Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(variableType)) {
    return handleTypedPrimitiveLocalVariableDeclr(variableName, variableType,
                                                  rhsValue);
  }

  // Handle Local Dynamic Typed Variable
  return handleUnTypedPrimitiveLocalVariableDeclr(variableName, rhsValue);
}

llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateCommonStatement(
    BoundVariableDeclaration *variableDeclaration) {

  if (!canGenerateStatement(variableDeclaration)) {
    return nullptr;
  }

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    std::unique_ptr<ContainerDeclarationStatementGenerationStrategy>
        contDecGenStrat =
            std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    return _isGlobal
               ? contDecGenStrat->generateGlobalStatement(variableDeclaration)
               : contDecGenStrat->generateStatement(variableDeclaration);
  }

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    std::unique_ptr<ObjectDeclarationStatementGenerationStrategy>
        objDecGenStrat =
            std::make_unique<ObjectDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    return _isGlobal
               ? objDecGenStrat->generateGlobalStatement(variableDeclaration)
               : objDecGenStrat->generateStatement(variableDeclaration);
  }

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  auto [ptr, type] = _variableDeclaration->getLLVMVariable();

  // Handle Global Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {

    _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
                                                     {ptr, type});

    if (!variableDeclaration->getInitializerPtr().get())
      return ptr;

    return assignmentEGS->handleAssignExpression(
        ptr, type, _variableName,
        variableDeclaration->getInitializerPtr().get());
  }

  if (!_rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected a right hand side value in the expression, but found "
        "nothing");
    return nullptr;
  }

  _codeGenerationContext->getAllocaChain()->setPtr(_variableName, {ptr, type});

  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      ptr, _rhsValue, _rhsValue->getType(), _variableName);

  return _rhsValue;
}
llvm::Value *VariableDeclarationStatementGenerationStrategy::declare() {
  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    std::unique_ptr<ContainerDeclarationStatementGenerationStrategy>
        contDecGenStrat =
            std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    return _isGlobal ? contDecGenStrat->declareGlobal(_variableDeclaration)
                     : contDecGenStrat->declareLocal(_variableDeclaration);
  }

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    std::unique_ptr<ObjectDeclarationStatementGenerationStrategy>
        objDecGenStrat =
            std::make_unique<ObjectDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    return _isGlobal ? objDecGenStrat->declareGlobal(_variableDeclaration)
                     : objDecGenStrat->declareLocal(_variableDeclaration);
  }
  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);
  llvm::Type *ptrType = nullptr;
  llvm::Value *ptr = nullptr;
  // Handle Global Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {

    ptrType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        _variableType);

    ptr = _codeGenerationContext->createMemoryGetPtr(
        ptrType, _variableName, _variableDeclaration->getMemoryKind());

    assignmentEGS->initDefaultValue(ptrType, ptr, *Builder);

  } else {
    // Dynamic Type

    ptr = _codeGenerationContext->createMemoryGetPtr(
        _codeGenerationContext->getDynamicType()->get(), _variableName,
        _variableDeclaration->getMemoryKind());

    ptrType = _codeGenerationContext->getDynamicType()->get();
  }

  if (_variableDeclaration->getInitializerPtr().get() &&
      _variableDeclaration->getInitializerPtr()->getKind() ==
          BinderKindUtils::BoundNodeKind::CallExpression) {
    BoundCallExpression *callExpression = static_cast<BoundCallExpression *>(
        _variableDeclaration->getInitializerPtr().get());

    callExpression->setArgumentAlloca(0, {ptr, ptrType});
  }

  _variableDeclaration->setLLVMVariable({ptr, ptrType});
  return ptr;
}
llvm::Value *VariableDeclarationStatementGenerationStrategy::declareLocal(
    BoundStatement *statement) {

  populateLocalVariables(statement, BinderKindUtils::MemoryKind::Stack);
  _isGlobal = false;
  return this->declare();
}
llvm::Value *VariableDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) {

  populateLocalVariables(statement, BinderKindUtils::MemoryKind::Global);
  _isGlobal = true;
  return this->declare();
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);
  if (variableDeclaration->getMemoryKind() == BinderKindUtils::MemoryKind::None)
    variableDeclaration->setMemoryKind(BinderKindUtils::MemoryKind::Stack);
  _isGlobal = false;
  return this->generateCommonStatement(variableDeclaration);
}
llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);
  if (variableDeclaration->getMemoryKind() == BinderKindUtils::MemoryKind::None)
    variableDeclaration->setMemoryKind(BinderKindUtils::MemoryKind::Global);
  _isGlobal = true;
  return this->generateCommonStatement(variableDeclaration);
}

bool VariableDeclarationStatementGenerationStrategy::canGenerateStatement(
    BoundStatement *statement) {

  populateLocalVariables(statement);

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE ||
      _variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE ||
      _codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {
    return true;
  }

  BoundExpression *initializerExp =
      _variableDeclaration->getInitializerPtr().get();

  if (!initializerExp) {
    return true;
  }

  if (initializerExp->getKind() ==
          BinderKindUtils::BoundNodeKind::LiteralExpression &&
      _variableType != SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    std::unique_ptr<LiteralExpressionGenerationStrategy>
        literalExpressionGenerationStrategy =
            std::make_unique<LiteralExpressionGenerationStrategy>(
                _codeGenerationContext);

    _rhsValue = literalExpressionGenerationStrategy->generateTypedExpression(
        initializerExp, _variableType);
  } else {

    _rhsValue =
        _expressionGenerationFactory->createStrategy(initializerExp->getKind())
            ->generateExpression(initializerExp);
  }

  if (!_rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Rhs of variable " + _variableName + " is not an expression");
    return false;
  }

  if (_variableType != SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE &&
      !_codeGenerationContext->getMapper()->isEquivalentType(
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

void VariableDeclarationStatementGenerationStrategy::populateLocalVariables(
    BoundStatement *statement, BinderKindUtils::MemoryKind memoryKind) {

  _variableDeclaration = static_cast<BoundVariableDeclaration *>(statement);

  if (_variableDeclaration->getMemoryKind() ==
      BinderKindUtils::MemoryKind::None) {
    _variableDeclaration->setMemoryKind(memoryKind);
  }

  _variableName = _variableDeclaration->getVariableName();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableDeclaration->getLocation());

  _variableType =
      _variableDeclaration->getTypeExpression().get()->getSyntaxType();
}
