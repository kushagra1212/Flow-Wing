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


#include "MultipleAssignmentExpressionGenerationStrategy.h"

MultipleAssignmentExpressionGenerationStrategy::
    MultipleAssignmentExpressionGenerationStrategy(
        CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *MultipleAssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression =
      static_cast<BoundMultipleAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundMultipleAssignmentExpression->getLocation());

  if (this->hasSingleCallExpr(boundMultipleAssignmentExpression)) {
    handleMultipleVarAssignCallExprGen(boundMultipleAssignmentExpression);
  } else {
    std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
        std::make_unique<AssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);
    for (auto &expr :
         boundMultipleAssignmentExpression->getAssignmentListRef()) {
      assignmentStrategy->generateExpression(expr.get());
    }
  }

  return nullptr;
}
llvm::Value *
MultipleAssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression =
      static_cast<BoundMultipleAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundMultipleAssignmentExpression->getLocation());

  if (this->hasSingleCallExpr(boundMultipleAssignmentExpression)) {
    handleMultipleVarAssignCallExprGen(boundMultipleAssignmentExpression);
  } else {
    std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
        std::make_unique<AssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);
    for (auto &expr :
         boundMultipleAssignmentExpression->getAssignmentListRef()) {
      assignmentStrategy->generateGlobalExpression(expr.get());
    }
  }

  return nullptr;
}

void MultipleAssignmentExpressionGenerationStrategy::
    handleMultipleVarAssignCallExprGen(
        BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression) {
  auto firstVariableAssignment =
      boundMultipleAssignmentExpression->getAssignmentListRef()[0].get();

  if (!firstVariableAssignment->getRightPtr().get()) {
    return;
  }

  BoundCallExpression *callExpression = BoundUtils::getCallExpression(
      firstVariableAssignment->getRightPtr().get());

  if (callExpression) {

    std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
        std::make_unique<AssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);

    uint64_t offset = 0;
    for (const auto &expr :
         boundMultipleAssignmentExpression->getAssignmentListRef()) {
      BoundVariableExpression *variableExpression =
          static_cast<BoundVariableExpression *>(expr->getLeftPtr().get());

      std::string variableName = std::any_cast<std::string>(
          ((BoundLiteralExpression<std::any> *)variableExpression
               ->getIdentifierExpressionPtr()
               .get())
              ->getValue());

      auto [ptr, ptrType] =
          _codeGenerationContext->getAllocaChain()->getPtr(variableName);

      callExpression->addReturnTypeToList(ptrType);

      Builder->CreateStore(ptr, Builder->CreateStructGEP(
                                    callExpression->getArgumentAlloca(0).second,
                                    callExpression->getArgumentAlloca(0).first,
                                    offset++));
    }

    assignmentEGS->handleAssignExpression(
        callExpression->getArgumentAlloca(0).first,
        callExpression->getArgumentAlloca(0).second, "_retrunArg",
        firstVariableAssignment->getRightPtr().get());
  }
}

void MultipleAssignmentExpressionGenerationStrategy::declare(
    BoundExpression *expression) {

  BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression =
      static_cast<BoundMultipleAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundMultipleAssignmentExpression->getLocation());

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  if (this->hasSingleCallExpr(boundMultipleAssignmentExpression)) {
    auto firstAssignmentExpr =
        boundMultipleAssignmentExpression->getAssignmentListRef()[0].get();
    BoundCallExpression *callExpression =
        BoundUtils::getCallExpression(firstAssignmentExpr->getRightPtr().get());

    if (!(_codeGenerationContext->funcPtr(callExpression->getCallerNameRef()) &&
          (_codeGenerationContext->funcPtr(callExpression->getCallerNameRef()))
              ->isHavingReturnTypeAsParamater())) {
      return;
    }

    std::vector<llvm::Type *> _structElementTypes(
        boundMultipleAssignmentExpression->getAssignmentListRef().size(),
        llvm::Type::getInt8PtrTy(*TheContext));
    llvm::StructType *_structType =
        llvm::StructType::create(*TheContext, _structElementTypes);

    llvm::Value *_stPtr = _codeGenerationContext->createMemoryGetPtr(
        _structType, "rtStructPtrForAssignment",
        BinderKindUtils::MemoryKind::Stack);

    callExpression->setArgumentAlloca(0, {_stPtr, _structType});
  } else {
    for (auto &expr :
         boundMultipleAssignmentExpression->getAssignmentListRef()) {
      assignmentStrategy->declare(expr.get());
    }
  }
}

bool MultipleAssignmentExpressionGenerationStrategy::hasSingleCallExpr(
    BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression) {

  for (uint64_t i = 0;
       i < boundMultipleAssignmentExpression->getAssignmentListRef().size();
       i++) {
    if (i == 0) {
      if (!boundMultipleAssignmentExpression->getAssignmentListRef()[i]
               ->getRightPtr()) {
        return false;
      }

      BoundCallExpression *callExpression = BoundUtils::getCallExpression(
          boundMultipleAssignmentExpression->getAssignmentListRef()[i]
              ->getRightPtr()
              .get());

      if (!callExpression) {
        return false;
      }
    }

    if (i != 0 && boundMultipleAssignmentExpression->getAssignmentListRef()[i]
                      ->getRightPtr()) {
      return false;
    }
  }

  return boundMultipleAssignmentExpression->getAssignmentListRef().size()
             ? true
             : false;
}