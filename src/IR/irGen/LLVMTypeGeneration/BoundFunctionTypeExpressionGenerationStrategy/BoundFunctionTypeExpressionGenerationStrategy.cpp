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

#include "BoundFunctionTypeExpressionGenerationStrategy.h"

llvm::Type *BoundFunctionTypeExpressionGenerationStrategy::getType(
    BoundTypeExpression *expression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  BoundFunctionTypeExpression *bfT =
      static_cast<BoundFunctionTypeExpression *>(expression);

  DEBUG_LOG("Function Type Expression: %s", "");

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bfT->getLocation());

  _codeGenerationContext
      ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()] =
      std::make_unique<FlowWing::Function>();
  _codeGenerationContext->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
      ->setFunctionName(bfT->getVariableNameItBelongsTo());

  std::vector<llvm::Type *> argTypes;
  std::unique_ptr<LiteralExpressionGenerationStrategy>
      literalExpressionGenerationStrategy =
          std::make_unique<LiteralExpressionGenerationStrategy>(
              _codeGenerationContext);

  //? Taking value to return as parameter
  if (!bfT->hasAsReturnType()) {
    std::vector<llvm::Type *> returnStructTypeList = {};
    for (const auto &rTypeExpr : bfT->getReturnTypes()) {
      BoundTypeExpression *bTE =
          static_cast<BoundTypeExpression *>(rTypeExpr.get());

      if (bTE->getSyntaxType() == SyntaxKindUtils::SyntaxKind::NthgKeyword) {
        //? Not returning anything, so no need to add return parameter
        continue;
      }

      llvm::Type *type =
          _typeGenerationFactory->createStrategy(bTE->getKind())->getType(bTE);

      if (type) {
        returnStructTypeList.push_back(type);
      }
    }

    //? Handling the case when multiple return type () -> T1, T2, T3
    if (bfT->getReturnTypes().size() > 1) {
      std::vector<llvm::Type *> returnStructTypePtrList(
          returnStructTypeList.size(), llvm::Type::getInt8PtrTy(*TheContext));

      llvm::Type *StructType =
          llvm::StructType::create(*TheContext, returnStructTypePtrList);

      argTypes.push_back(llvm::PointerType::get(StructType, 0));

      _codeGenerationContext->getArgsTypeHandler()->addArgsType(
          bfT->getVariableNameItBelongsTo(),
          std::make_unique<LLVMType>(StructType, returnStructTypeList));

    } else if (bfT->getReturnTypes().size() && returnStructTypeList.size()) {
      argTypes.push_back(llvm::PointerType::get(returnStructTypeList[0], 0));
      _codeGenerationContext->getArgsTypeHandler()->addArgsType(
          bfT->getVariableNameItBelongsTo(),
          std::make_unique<LLVMType>(returnStructTypeList[0]));
    }
  }

  for (size_t i = 0; i < bfT->getParameterTypes().size(); i++) {
    llvm::Type *parmType = nullptr;
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bfT->getParameterTypes()[i]->getLocation());
    _codeGenerationContext
        ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
        ->addAsParam(bfT->getHasAsParamListRef()[i]);

    llvm::Type *_argType = nullptr;
    std::unique_ptr<LLVMType> argLLVMType = nullptr;

    if (bfT->getParameterTypes()[i]->getSyntaxType() ==
        SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
      parmType = llvm::StructType::getTypeByName(
          *_codeGenerationContext->getContext(),
          DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

      _argType = llvm::PointerType::get(parmType, 0);
      argLLVMType = std::make_unique<LLVMType>(parmType);
    } else if (bfT->getParameterTypes()[i]->getSyntaxType() ==
               SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
      BoundArrayTypeExpression *arrayTypeExpression =
          static_cast<BoundArrayTypeExpression *>(
              bfT->getParameterTypes()[i].get());

      SyntaxKindUtils::SyntaxKind containerElementType =
          arrayTypeExpression->getElementType();

      size_t multiDimSize = arrayTypeExpression->getDimensions().size();

      if (arrayTypeExpression->isTrivialType()) {
        parmType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            arrayTypeExpression->getElementType());

      } else {
        BoundObjectTypeExpression *objectTypeExpression =
            static_cast<BoundObjectTypeExpression *>(
                arrayTypeExpression->getNonTrivialElementType().get());

        parmType = _codeGenerationContext
                       ->getFlowWingType(objectTypeExpression->getTypeName())
                       .getType();
      }

      std::vector<uint64_t> dimensions(multiDimSize, 0);
      for (int64_t k = multiDimSize - 1; k >= 0; k--) {
        llvm::Value *arraySize =
            literalExpressionGenerationStrategy->generateExpression(
                arrayTypeExpression->getDimensions()[k].get());

        if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
          _codeGenerationContext->getLogger()->LogError(
              "Array size must be a constant integer");
        }

        dimensions[k] =
            llvm::cast<llvm::ConstantInt>(arraySize)->getSExtValue();

        parmType = llvm::ArrayType::get(parmType, dimensions[k]);
      }

      if (bfT->getHasAsParamListRef()[i]) {
        _argType = parmType;
        argLLVMType = std::make_unique<LLVMType>(parmType);
      } else {
        _argType = llvm::PointerType::get(parmType, 0);
        argLLVMType = std::make_unique<LLVMArrayType>(
            _argType, parmType,
            _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
                containerElementType),
            dimensions, arrayTypeExpression);
      }
    } else if (bfT->getParameterTypes()[i]->getSyntaxType() ==
               SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
      BoundObjectTypeExpression *objectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(
              bfT->getParameterTypes()[i].get());

      llvm::StructType *structType = llvm::cast<llvm::StructType>(
          _typeGenerationFactory
              ->createStrategy(objectTypeExpression->getKind())
              ->getType(objectTypeExpression));

      if (!structType) {
        _codeGenerationContext->getLogger()->LogError(
            "Object type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(structType) +
            " was not found when calling function ");
        return nullptr;
      }

      if (bfT->getHasAsParamListRef()[i]) {
        _argType = structType;
        argLLVMType = std::make_unique<LLVMType>(structType);
      } else {
        _argType = llvm::PointerType::get(structType, 0);
        argLLVMType = std::make_unique<LLVMObjectType>(_argType, structType);
      }

    } else if (bfT->getParameterTypes()[i]->getSyntaxType() ==
               SyntaxKindUtils::SyntaxKind::NBU_FUNCTION_TYPE) {
      BoundFunctionTypeExpression *functionTypeExpr =
          static_cast<BoundFunctionTypeExpression *>(
              bfT->getParameterTypes()[i].get());

      llvm::FunctionType *functionType = static_cast<llvm::FunctionType *>(
          _typeGenerationFactory->createStrategy(functionTypeExpr->getKind())
              ->getType(functionTypeExpr));

      if (!functionType) {
        _codeGenerationContext->getLogger()->LogError(
            "Function type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(functionType) +
            " was not found when calling function ");
        return nullptr;
      }

      if (bfT->getHasAsParamListRef()[i]) {
        _argType = functionType;
        argLLVMType = std::make_unique<LLVMType>(functionType);
      } else {
        _argType = llvm::PointerType::get(functionType, 0);
        argLLVMType =
            std::make_unique<LLVMFunctionType>(_argType, functionType);
      }

    } else {
      parmType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          bfT->getParameterTypes()[i]->getSyntaxType());

      if (bfT->getHasAsParamListRef()[i]) {
        _argType = parmType;
        argLLVMType = std::make_unique<LLVMType>(parmType);
      } else {
        _argType = llvm::PointerType::get(parmType, 0);
        argLLVMType = std::make_unique<LLVMPrimitiveType>(_argType, parmType);
      }
    }

    _codeGenerationContext->getArgsTypeHandler()->addArgsType(
        bfT->getVariableNameItBelongsTo(), std::move(argLLVMType));
    argTypes.push_back(_argType);
  }

  llvm::FunctionType *FT = nullptr;
  std::string returnInfo = "";
  _hasAsReturnType = bfT->hasAsReturnType();
  for (auto &rTypeExpr : bfT->getReturnTypes()) {
    llvm::Type *returnType = nullptr;
    BoundTypeExpression *bTE =
        static_cast<BoundTypeExpression *>(rTypeExpr.get());

    switch (bTE->getKind()) {
    case BinderKindUtils::BoundTypeExpression: {
      llvm::Type *elementType =
          _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
              bTE->getSyntaxType());
      if (bTE->getSyntaxType() != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
        returnType = llvm::PointerType::get(elementType, 0);
      }

      FT = llvm::FunctionType::get(bfT->hasAsReturnType()
                                       ? elementType
                                       : llvm::Type::getVoidTy(*TheContext),
                                   argTypes, false);
      _llvmReturnType =
          std::make_unique<LLVMPrimitiveType>(returnType, elementType);
      _codeGenerationContext
          ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
          ->setReturnType(elementType, bfT->hasAsReturnType());

      _codeGenerationContext
          ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
          ->setReturnType(elementType, bfT->hasAsReturnType());
      break;
    }
    case BinderKindUtils::BoundArrayTypeExpression: {
      BoundArrayTypeExpression *boundArrayTypeExpression =
          static_cast<BoundArrayTypeExpression *>(bTE);

      llvm::Type *elementType = nullptr;
      if (boundArrayTypeExpression->isTrivialType()) {
        elementType =
            _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
                boundArrayTypeExpression->getElementType());

      } else {
        BoundObjectTypeExpression *objectTypeExpression =
            static_cast<BoundObjectTypeExpression *>(
                boundArrayTypeExpression->getNonTrivialElementType().get());

        elementType = _codeGenerationContext
                          ->getFlowWingType(objectTypeExpression->getTypeName())
                          .getType();
      }

      llvm::Type *arrayType = elementType;

      std::vector<uint64_t> returnDimentions(
          boundArrayTypeExpression->getDimensions().size(), 0);
      for (int64_t k = boundArrayTypeExpression->getDimensions().size() - 1;
           k >= 0; k--) {
        llvm::Value *arraySize =
            literalExpressionGenerationStrategy->generateExpression(
                boundArrayTypeExpression->getDimensions()[k].get());

        if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
          _codeGenerationContext->getLogger()->LogError(
              "Array size must be a constant integer");
        }

        returnDimentions[k] =
            llvm::cast<llvm::ConstantInt>(arraySize)->getSExtValue();

        arrayType = llvm::ArrayType::get(arrayType, returnDimentions[k]);
      }
      llvm::Type *returnType = llvm::PointerType::get(arrayType, 0);

      //! Returning Void for Array Type and settting the value in parameter
      //! where we have the pointer to array
      FT = llvm::FunctionType::get(bfT->hasAsReturnType()
                                       ? returnType
                                       : llvm::Type::getVoidTy(*TheContext),
                                   argTypes, false);

      _llvmReturnType = std::make_unique<LLVMArrayType>(
          returnType, arrayType, elementType, returnDimentions,
          boundArrayTypeExpression);
      _codeGenerationContext
          ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
          ->setReturnType(arrayType, bfT->hasAsReturnType());

      _codeGenerationContext
          ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
          ->setReturnType(arrayType, bfT->hasAsReturnType());
      break;
    }
    case BinderKindUtils::BoundObjectTypeExpression: {
      BoundObjectTypeExpression *boundObjectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(bTE);

      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          boundObjectTypeExpression->getLocation());
      llvm::StructType *structType =
          (_codeGenerationContext
               ->getFlowWingType(boundObjectTypeExpression->getTypeName())
               .getStructType());

      if (!structType && _codeGenerationContext->_classTypes.find(
                             boundObjectTypeExpression->getTypeName()) !=
                             _codeGenerationContext->_classTypes.end()) {
        structType = _codeGenerationContext
                         ->_classTypes[boundObjectTypeExpression->getTypeName()]
                         ->getClassType();
      }

      if (!structType) {
        _codeGenerationContext->getLogger()->LogError(
            "Expected an object of type " +
            Utils::getActualTypeName(boundObjectTypeExpression->getTypeName()));
        return nullptr;
      }
      llvm::Type *returnType = llvm::PointerType::get(structType, 0);
      //! Returning Void for struct Type and settting the value in parameter
      //! where we have the pointer to struct
      FT = llvm::FunctionType::get(bfT->hasAsReturnType()
                                       ? returnType
                                       : llvm::Type::getVoidTy(*TheContext),
                                   argTypes, false);

      _llvmReturnType =
          std::make_unique<LLVMObjectType>(returnType, structType);
      _codeGenerationContext
          ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
          ->setReturnType(structType, bfT->hasAsReturnType());
      _codeGenerationContext
          ->_functionLocalTypes[bfT->getVariableNameItBelongsTo()]
          ->setReturnType(structType, bfT->hasAsReturnType());
      break;
    }
    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Invalid return type for function");
      return nullptr;
    }
    }
  }

  return FT;
}
