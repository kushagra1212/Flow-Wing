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

    return contDecGenStrat->generateGlobalStatement(variableDeclaration);
  }
  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {

    BoundObjectTypeExpression *objectTypeExpression =
        static_cast<BoundObjectTypeExpression *>(
            variableDeclaration->getTypeExpression().get());

    llvm::StructType *structType =
        _codeGenerationContext->getTypeChain()->getType(
            objectTypeExpression->getTypeName());

    std::pair<llvm::Value *, llvm::Type *> cl =
        _codeGenerationContext->getAllocaChain()->getPtr("self");
    if (cl.first && cl.second && llvm::isa<llvm::StructType>(cl.second)) {
      llvm::StructType *ct = llvm::cast<llvm::StructType>(cl.second);
      structType = _codeGenerationContext->getTypeChain()->getType(
          ct->getStructName().str() +
          FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
          objectTypeExpression->getTypeName());
    }

    if (!structType && _codeGenerationContext->_classTypes.find(
                           objectTypeExpression->getTypeName()) !=
                           this->_codeGenerationContext->_classTypes.end()) {
      structType = _codeGenerationContext
                       ->_classTypes[objectTypeExpression->getTypeName()]
                       ->getClassType();
    }

    if (!structType) {
      _codeGenerationContext->getLogger()->LogError(
          "Object type " + objectTypeExpression->getTypeName() + " not found");
      return nullptr;
    }
    if (_codeGenerationContext->_classTypes.find(
            structType->getStructName().str()) !=
        _codeGenerationContext->_classTypes.end()) {

      if (variableDeclaration->getInitializerPtr()->getKind() ==
          BinderKindUtils::CallExpression) {

        std::unique_ptr<ExpressionGenerationFactory>
            expressionGenerationFactory =
                std::make_unique<ExpressionGenerationFactory>(
                    _codeGenerationContext);
        llvm::Value *ptr =
            expressionGenerationFactory
                ->createStrategy(BinderKindUtils::CallExpression)
                ->generateExpression(
                    variableDeclaration->getInitializerPtr().get());
        // _codeGenerationContext->_classTypes[objectTypeExpression->getTypeName()]
        //     ->setObjectPtr(ptr);
        _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
                                                         {ptr, structType});
        return ptr;
      }

      llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
          structType, _variableName, variableDeclaration->getMemoryKind());

      _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
                                                       {ptr, structType});
      assignmentEGS->initDefaultValue(structType, ptr);

      _codeGenerationContext->_classTypes[structType->getStructName().str()]
          ->setObjectPtr(ptr);

      if (!variableDeclaration->getInitializerPtr().get())
        return ptr;

      return assignmentEGS->handleAssignExpression(
          ptr, structType, _variableName,
          variableDeclaration->getInitializerPtr().get());
    }

    llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
        structType, _variableName, variableDeclaration->getMemoryKind());

    assignmentEGS->initDefaultValue(structType, ptr);
    _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
                                                     {ptr, structType});
    if (!variableDeclaration->getInitializerPtr().get())
      return ptr;
    return assignmentEGS->handleAssignExpression(
        ptr, structType, _variableName,
        variableDeclaration->getInitializerPtr().get());
  }

  // Handle Global Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {
    llvm::Type *llvmType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            _variableType);

    llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
        llvmType, _variableName, variableDeclaration->getMemoryKind());

    assignmentEGS->initDefaultValue(llvmType, ptr);
    _codeGenerationContext->getAllocaChain()->setPtr(_variableName,
                                                     {ptr, llvmType});
    if (!_rhsValue)
      return ptr;
    Builder->CreateStore(_rhsValue, ptr);

    return _rhsValue;
  }

  if (!_rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected a right hand side value in the expression, but found "
        "nothing");
    return nullptr;
  }

  llvm::Value *dynVarPtr = _codeGenerationContext->createMemoryGetPtr(
      _codeGenerationContext->getDynamicType()->get(), _variableName,
      variableDeclaration->getMemoryKind());

  _codeGenerationContext->getAllocaChain()->setPtr(
      _variableName,
      {dynVarPtr, _codeGenerationContext->getDynamicType()->get()});

  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      dynVarPtr, _rhsValue, _rhsValue->getType(), _variableName);

  return _rhsValue;
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);
  if (variableDeclaration->getMemoryKind() == BinderKindUtils::MemoryKind::None)
    variableDeclaration->setMemoryKind(BinderKindUtils::MemoryKind::Stack);

  return this->generateCommonStatement(variableDeclaration);
}
llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);
  if (variableDeclaration->getMemoryKind() == BinderKindUtils::MemoryKind::None)
    variableDeclaration->setMemoryKind(BinderKindUtils::MemoryKind::Global);

  return this->generateCommonStatement(variableDeclaration);
}

bool VariableDeclarationStatementGenerationStrategy::canGenerateStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);

  _variableName = variableDeclaration->getVariableName();

  BoundExpression *initializerExp =
      variableDeclaration->getInitializerPtr().get();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableDeclaration->getLocation());

  _variableType = variableDeclaration->getTypeExpression()->getSyntaxType();

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE ||
      _variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return true;
  }
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