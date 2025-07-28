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

#include "ReturnStatementGenerationStrategy.h"

#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ReturnStatementGenerationStrategy::ReturnStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ReturnStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundReturnStatement *returnStatement =
      static_cast<BoundReturnStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      returnStatement->getLocation());

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", function);

  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(*TheContext, "mergeBlock", function);

  Builder->CreateBr(returnBlock);

  Builder->SetInsertPoint(returnBlock);

  std::string errorMessage = "";
  llvm::Function *currentFunction = Builder->GetInsertBlock()->getParent();
  std::string functionName = currentFunction->getName().str();

  auto [rtPtr, rtType] = _codeGenerationContext->getAllocaChain()->getPtr(
      FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME);

  if (rtPtr && rtType) {

    if (returnStatement->getReturnExpressionListRef().size() == 0) {
      _codeGenerationContext->getLogger()->LogError(
          "Function expects a return expression but no return expression "
          "found");
      return nullptr;
    }

    uint64_t offset = 0;
    if (returnStatement->getReturnExpressionListRef().size() == 1) {
      auto returnStat = returnStatement->getReturnExpressionListRef()[0].get();

      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          returnStatement->getLocation());

      LLVMType *returnType = _codeGenerationContext->getReturnTypeHandler()
                                 ->getReturnType(functionName, 0)
                                 .get();

      SyntaxKindUtils::SyntaxKind returnTypeCustomType =
          _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
              returnType->getLLVMType());

      if (returnTypeCustomType == SyntaxKindUtils::SyntaxKind::NthgKeyword) {

        _codeGenerationContext->getLogger()->LogError(
            "Function return type is Nothing, return "
            "expression is found");
        return nullptr;
      }

      std::unique_ptr<AssignmentExpressionGenerationStrategy>
          assignmentExpressionGenerationStrategy =
              std::make_unique<AssignmentExpressionGenerationStrategy>(
                  _codeGenerationContext);

      if (returnStat->getKind() == BinderKindUtils::CallExpression) {
        BoundCallExpression *boundCallExpression =
            static_cast<BoundCallExpression *>(returnStat);

        if (Utils::isClassInit(boundCallExpression->getCallerNameRef())) {
          boundCallExpression->setArgumentAlloca(
              boundCallExpression->getArgumentsRef().size(), {rtPtr, rtType});
        } else {
          const std::vector<std::unique_ptr<LLVMType>> &currentFunctionArgs =
              _codeGenerationContext->getArgsTypeHandler()->getArgsType(
                  functionName);

          const std::vector<std::unique_ptr<LLVMType>> &callingFunctionArg =
              _codeGenerationContext->getArgsTypeHandler()->getArgsType(
                  functionName);
          if (_codeGenerationContext->verifyType(
                  currentFunctionArgs[0]->getStructTypeListRef(),
                  callingFunctionArg[0]->getStructTypeListRef(),
                  " in Return Expression") == EXIT_FAILURE) {
            return nullptr;
          }

          for (const auto &type :
               currentFunctionArgs[0]->getStructTypeListRef()) {
            boundCallExpression->addReturnTypeToList(type);
          }

          boundCallExpression->setArgumentAlloca(0, {rtPtr, rtType});
        }
      }

      assignmentExpressionGenerationStrategy->handleAssignExpression(
          rtPtr, rtType, FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME,
          returnStat);
    } else {
      if (returnStatement->getReturnExpressionListRef().size() !=
          _codeGenerationContext->getReturnTypeHandler()
              ->getReturnTypeListRef(functionName)
              .size()) {

        _codeGenerationContext->getLogger()->LogError(
            "Function expects " +
            std::to_string(_codeGenerationContext->getReturnTypeHandler()
                               ->getReturnTypeListRef(functionName)
                               .size()) +
            " return expression but " +
            std::to_string(
                returnStatement->getReturnExpressionListRef().size()) +
            " return expression found");
        return nullptr;
      }
      for (auto &returnStat : returnStatement->getReturnExpressionListRef()) {

        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            returnStat->getLocation());

        LLVMType *returnType = _codeGenerationContext->getReturnTypeHandler()
                                   ->getReturnType(functionName, offset)
                                   .get();

        SyntaxKindUtils::SyntaxKind returnTypeCustomType =
            _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
                returnType->getLLVMType());

        if (returnTypeCustomType == SyntaxKindUtils::SyntaxKind::NthgKeyword) {

          _codeGenerationContext->getLogger()->LogError(
              "Function return type is Nothing, return "
              "expression is found");
          return nullptr;
        }
        _codeGenerationContext->getValueStackHandler()->popAll();

        llvm::Value *rtElementGEP =
            Builder->CreateStructGEP(rtType, rtPtr, offset);

        llvm::Value *rtElementPtr = Builder->CreateLoad(
            llvm::Type::getInt8PtrTy(*TheContext), rtElementGEP);

        std::unique_ptr<AssignmentExpressionGenerationStrategy>
            assignmentExpressionGenerationStrategy =
                std::make_unique<AssignmentExpressionGenerationStrategy>(
                    _codeGenerationContext);

        if (returnStat->getKind() == BinderKindUtils::CallExpression) {
          BoundCallExpression *boundCallExpression =
              static_cast<BoundCallExpression *>(returnStat.get());

          if (Utils::isClassInit(boundCallExpression->getCallerNameRef())) {
            boundCallExpression->setArgumentAlloca(
                boundCallExpression->getArgumentsRef().size(),
                {rtElementPtr, returnType->getLLVMType()});

          } else {
            boundCallExpression->setArgumentAlloca(
                0, {rtElementPtr, returnType->getLLVMType()});
          }
        }
        assignmentExpressionGenerationStrategy->handleAssignExpression(
            rtElementPtr, returnType->getLLVMType(),
            FLOWWING::UTILS::CONSTANTS::RETURN_VAR_NAME +
                std::to_string(offset),
            returnStat.get());
        offset++;
      }
    }

    Builder->CreateRetVoid();
  } else if (returnStatement->getReturnExpressionListRef().size()) {
    //? This is the case when the return type is not a paramater
    //? So, first element of getReturnExpressionListRef is the return value

    const uint64_t firstElementIndex = 0;

    BoundExpression *directReturnStat =
        returnStatement->getReturnExpressionListRef()[firstElementIndex].get();

    LLVMType *returnType = _codeGenerationContext->getReturnTypeHandler()
                               ->getReturnType(functionName, firstElementIndex)
                               .get();

    SyntaxKindUtils::SyntaxKind returnTypeCustomType =
        _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
            returnType->getLLVMType());

    if (returnTypeCustomType == SyntaxKindUtils::SyntaxKind::NthgKeyword) {
      _codeGenerationContext->getLogger()->LogError(
          "Function return type is Nothing, return "
          "expression is found");
      return nullptr;
    }
    // default return value =

    _codeGenerationContext->getValueStackHandler()->popAll();

    // TODO: Return Value Can be Nir
    llvm::Value *returnValue = _expressionGenerationFactory
                                   ->createStrategy(directReturnStat->getKind())
                                   ->generateExpression(directReturnStat);

    llvm::Type *rtypeLLVM =
        _codeGenerationContext->getValueStackHandler()->getLLVMType();

    if (returnType->isPointerToObject()) {
      LLVMObjectType *llvmObjectType =
          static_cast<LLVMObjectType *>(returnType);

      if (_codeGenerationContext->verifyType(
              llvmObjectType->getStructType(), rtypeLLVM,
              " in Return Expression") == EXIT_FAILURE)
        return nullptr;

    } else if (returnType->isPointerToArray()) {
      LLVMArrayType *llvmArrayType = static_cast<LLVMArrayType *>(returnType);

      if (_codeGenerationContext->verifyType(
              llvmArrayType->getElementType(), rtypeLLVM,
              " in Return Expression") == EXIT_FAILURE)
        return nullptr;

    } else {

      if (_codeGenerationContext->verifyType(
              returnType->getLLVMType(), rtypeLLVM, " in Return Expression") ==
          EXIT_FAILURE)
        return nullptr;
    }

    _codeGenerationContext->getValueStackHandler()->popAll();

    Builder->CreateRet(returnValue);
  } else {

    LLVMType *returnType = _codeGenerationContext->getReturnTypeHandler()
                               ->getReturnType(functionName, 0)
                               .get();

    SyntaxKindUtils::SyntaxKind returnTypeCustomType =
        _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
            returnType->getLLVMType());

    if (returnTypeCustomType != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
      _codeGenerationContext->getLogger()->LogError(
          "Function expects a return expression but no return expression "
          "found");
      return nullptr;
    }

    Builder->CreateRetVoid();
  }

  _codeGenerationContext->getReturnAllocaStack().top() = 1;
  Builder->SetInsertPoint(mergeBlock);

  return nullptr;
}

llvm::Value *ReturnStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundReturnStatement *returnStatement =
      static_cast<BoundReturnStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      returnStatement->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Return Statement is not allowed in global scope ");

  return nullptr;
}
