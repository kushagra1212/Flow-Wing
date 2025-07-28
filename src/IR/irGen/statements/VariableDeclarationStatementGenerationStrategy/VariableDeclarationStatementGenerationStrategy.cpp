/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "VariableDeclarationStatementGenerationStrategy.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"

VariableDeclarationStatementGenerationStrategy::
    VariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handleTypedPrimitiveLocalVariableDeclaration(
        const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
        llvm::Value *rhsValue) {

  CODEGEN_DEBUG_LOG("Var Type ", Utils::typeToString(variableType));

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
    handleDynamicValuePrimitiveLocalVariableDeclare(
        const std::string &variableName, llvm::Value *rhsValue) {

  llvm::StructType *dynamicValueStructType =
      llvm::StructType::getTypeByName(*_codeGenerationContext->getContext(),
                                      DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

  llvm::AllocaInst *dynamicValueVariableAddress = Builder->CreateAlloca(
      dynamicValueStructType, nullptr, variableName.c_str());

  dynamicValueVariableAddress->setAlignment(llvm::Align(8));

  _codeGenerationContext->getAllocaChain()->setPtr(
      variableName, {dynamicValueVariableAddress, dynamicValueStructType});

  if (m_isLHSDynamicValue) {
    DYNAMIC_VALUE_HANDLER::assignRHSDynamicValueToLHSDynamicValue(
        dynamicValueVariableAddress, rhsValue, _codeGenerationContext, Builder);

  } else {
    DYNAMIC_VALUE_HANDLER::assignRHSValueToLHSDynamicValue(
        dynamicValueVariableAddress, variableName, rhsValue,
        _codeGenerationContext, Builder);
  }
  return rhsValue;
}

llvm::Value *VariableDeclarationStatementGenerationStrategy::
    handlePrimitiveLocalVariableDeclaration(
        const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
        llvm::Value *rhsValue) {

  // Handle Local Static Typed Variable
  if (_codeGenerationContext->getMapper()->isPrimitiveType(variableType)) {
    return handleTypedPrimitiveLocalVariableDeclaration(variableName,
                                                        variableType, rhsValue);
  }

  // Handle Local Dynamic Typed Variable
  return handleDynamicValuePrimitiveLocalVariableDeclare(variableName,
                                                         rhsValue);
}

llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateCommonStatement(
    BoundVariableDeclaration *variableDeclaration) {
  DEBUG_LOG("Generating Common Statement for Variable: ", _variableName);
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

  auto [ptr, type] = variableDeclaration->getLLVMVariable();

  // Handle Global Static Typed Variable

  CODEGEN_DEBUG_LOG(SyntaxKindUtils::to_string(_variableType), "Var Type",
                    _variableName);
  if (_codeGenerationContext->getMapper()->isPrimitiveType(type)) {

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

  assert(type == llvm::StructType::getTypeByName(
                     *_codeGenerationContext->getContext(),
                     DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) &&
         "Type is not a dynamic value type");

  _codeGenerationContext->getAllocaChain()->setPtr(_variableName, {ptr, type});

  // _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
  //     ptr, _rhsValue, _rhsValue->getType(), _variableName);
  handleDynamicValuePrimitiveLocalVariableDeclare(_variableName, _rhsValue);
  return _rhsValue;
}
llvm::Value *VariableDeclarationStatementGenerationStrategy::declare() {

  CODEGEN_DEBUG_LOG("Declaring Variable: ", _variableName);
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
    CODEGEN_DEBUG_LOG(
        "_variableType " + SyntaxKindUtils::to_string(_variableType),
        _variableName,
        _codeGenerationContext->getMapper()->getLLVMTypeName(ptrType));

    ptr = _codeGenerationContext->createMemoryGetPtr(
        ptrType, _variableName, _variableDeclaration->getMemoryKind());

    assignmentEGS->initDefaultValue(ptrType, ptr, *Builder);

  } else {
    // Dynamic Type

    ptr = _codeGenerationContext->createMemoryGetPtr(
        _codeGenerationContext->getDynamicType()->get(), _variableName,
        _variableDeclaration->getMemoryKind());

    ptrType = llvm::StructType::getTypeByName(
        *_codeGenerationContext->getContext(),
        DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);
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

  populateVariables(statement, BinderKindUtils::MemoryKind::Stack);
  _isGlobal = false;
  return this->declare();
}
llvm::Value *VariableDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) {

  populateVariables(statement, BinderKindUtils::MemoryKind::Global);
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

  populateVariables(statement);

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE ||
      _variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE ||
      _codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {
    return true;
  }

  if (!_variableDeclaration->getInitializerPtr()) {
    return true;
  }

  BoundExpression *initializerExp =
      _variableDeclaration->getInitializerPtr().get();

  if (initializerExp->getKind() ==
          BinderKindUtils::BoundNodeKind::LiteralExpression &&
      _variableType != SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    std::unique_ptr<LiteralExpressionGenerationStrategy>
        literalExpressionGenerationStrategy =
            std::make_unique<LiteralExpressionGenerationStrategy>(
                _codeGenerationContext);

    _rhsValue = literalExpressionGenerationStrategy->generateTypedExpression(
        initializerExp, _variableType);
  } else if (initializerExp->getKind() ==
                 BinderKindUtils::BoundNodeKind::BoundBracketedExpression &&
             _variableType == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    _codeGenerationContext->getLogger()->logError(
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::
            ArrayInitializerNotAllowedForDynamicType,
        {_variableName});
    return false;
  } else if (initializerExp->getKind() ==
                 BinderKindUtils::BoundNodeKind::BoundObjectExpression &&
             _variableType == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
    _codeGenerationContext->getLogger()->logError(
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::
            ObjectInitializerNotAllowedForDynamicType,
        {_variableName});
    return false;
  } else {

    _rhsValue =
        _expressionGenerationFactory->createStrategy(initializerExp->getKind())
            ->generateExpression(initializerExp);
  }

  m_isLHSDynamicValue =
      _codeGenerationContext->getValueStackHandler()->isDynamicValueType();

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

void VariableDeclarationStatementGenerationStrategy::populateVariables(
    BoundStatement *statement, BinderKindUtils::MemoryKind memoryKind) {

  DEBUG_LOG("Populating Variable: ", _variableName);
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
  DEBUG_LOG("Populated Variable: ", _variableName);
}
