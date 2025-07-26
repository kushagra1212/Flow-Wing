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


#include "ContainerDeclarationStatementGenerationStrategy.h"

#include "src/IR/irGen/expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ContainerDeclarationStatementGenerationStrategy::
    ContainerDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::declare() {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _arrayTypeExpression->getLocation());

  this->calcActualContainerSize(_arrayTypeExpression);

  if (_arrayTypeExpression->isTrivialType()) {
    _elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        _arrayTypeExpression->getElementType());

  } else {
    BoundObjectTypeExpression *objectTypeExpression =
        static_cast<BoundObjectTypeExpression *>(
            _arrayTypeExpression->getNonTrivialElementType().get());

    _elementType = _codeGenerationContext
                       ->getFlowWingType(objectTypeExpression->getTypeName())
                       .getStructType();
  }

  llvm::ArrayType *arrayType = nullptr;

  _codeGenerationContext->getMultiArrayType(arrayType, _actualSizes,
                                            _elementType);

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  llvm::Value *ptr = _codeGenerationContext->createMemoryGetPtr(
      arrayType, _containerName, _memoryKind);

  assignmentStrategy->initDefaultValue(arrayType, ptr, *Builder);

  _variableDeclExpr->setLLVMVariable({ptr, arrayType});

  if (_initializer && _initializer->getKind() ==
                          BinderKindUtils::BoundNodeKind::CallExpression) {
    BoundCallExpression *callExpression =
        static_cast<BoundCallExpression *>(_initializer);
    callExpression->setArgumentAlloca(0, {ptr, arrayType});
  }

  return ptr;
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::declareLocal(
    BoundStatement *statement) {

  initialize(statement, BinderKindUtils::MemoryKind::Stack);

  return this->declare();
}
llvm::Value *ContainerDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) {

  initialize(statement, BinderKindUtils::MemoryKind::Global);

  return this->declare();
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::assignExpression() {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableDeclExpr->getLocation());

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  auto [ptr, arrayType] = _variableDeclExpr->getLLVMVariable();

  _codeGenerationContext->getAllocaChain()->setPtr(_containerName,
                                                   {ptr, arrayType});

  if (!_initializer)
    return ptr;

  return assignmentStrategy->handleAssignExpression(
      ptr, arrayType, _containerName, _initializer);
}

void ContainerDeclarationStatementGenerationStrategy::initialize(
    BoundStatement *statement, BinderKindUtils::MemoryKind memoryKind) {
  DEBUG_LOG("Initializing Container Declaration Statement");
  _variableDeclExpr = static_cast<BoundVariableDeclaration *>(statement);

  // set memory kind
  if (_variableDeclExpr->getMemoryKind() == BinderKindUtils::MemoryKind::None) {
    _variableDeclExpr->setMemoryKind(memoryKind);
  }

  _containerName = _variableDeclExpr->getVariableName();
  _initializer = _variableDeclExpr->getInitializerPtr().get();
  _arrayTypeExpression = static_cast<BoundArrayTypeExpression *>(
      _variableDeclExpr->getTypeExpression().get());
  _memoryKind = _variableDeclExpr->getMemoryKind();
  DEBUG_LOG("Initialized Container Declaration Statement");
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  initialize(statement);

  return this->assignExpression();
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}

void ContainerDeclarationStatementGenerationStrategy::calcActualContainerSize(
    BoundArrayTypeExpression *arrayTypeExpression) {
  for (uint64_t i = 0; i < arrayTypeExpression->getDimensions().size(); i++) {
    llvm::Value *sizeValue =
        _expressionGenerationFactory
            ->createStrategy(
                arrayTypeExpression->getDimensions()[i].get()->getKind())
            ->generateExpression(arrayTypeExpression->getDimensions()[i].get());

    llvm::ConstantInt *sizeConstInt =
        llvm::dyn_cast<llvm::ConstantInt>(sizeValue);
    if (!sizeConstInt) {
      _codeGenerationContext->getLogger()->LogError(
          "Container size must be an integer");
      return;
    }

    _actualSizes.push_back(sizeConstInt->getZExtValue());
  }
}
