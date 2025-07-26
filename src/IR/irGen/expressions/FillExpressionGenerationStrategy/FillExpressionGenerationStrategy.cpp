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


#include "FillExpressionGenerationStrategy.h"

#include "src/IR/irGen/expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"

FillExpressionGenerationStrategy::FillExpressionGenerationStrategy(
    CodeGenerationContext *context, std::vector<uint64_t> actualSizes,
    llvm::Type *elementType, const std::string &containerName)
    : ExpressionGenerationStrategy(context), _actualSizes(actualSizes),
      _elementType(elementType), _containerName(containerName) {
  _totalSize = std::accumulate(_actualSizes.begin(), _actualSizes.end(), 1,
                               std::multiplies<uint64_t>());
}

llvm::Value *FillExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  if (!canGenerateExpression(expression))
    return nullptr;

  // Allocate memory on the stack for the array
  llvm::ArrayType *arrayType = nullptr;

  llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  _codeGenerationContext->getMultiArrayType(arrayType, _actualSizes,
                                            _elementType);

  if (!_allocaInst) {
    llvm::AllocaInst *alloca =
        Builder->CreateAlloca(arrayType, nullptr, _containerName);
    _codeGenerationContext->getAllocaChain()->setPtr(_containerName,
                                                     {alloca, arrayType});
    _codeGenerationContext->setArraySizeMetadata(alloca, _actualSizes);
    _codeGenerationContext->setArrayElementTypeMetadata(alloca, _elementType);
    _allocaInst = alloca;
  }

  // Fill the array with default values

  createExpressionLoop(arrayType, _allocaInst, _defaultVal, _totalSize);

  return createExpressionLoop(arrayType, _allocaInst, _elementToFill,
                              _sizeToFillInt);
}

llvm::Value *FillExpressionGenerationStrategy::createLocalExpression(
    llvm::Type *arrayType, llvm::AllocaInst *arrayAlloca) {
  // Get And Set Default Value

  createExpressionLoop(arrayType, arrayAlloca, _elementToFill, _sizeToFillInt);

  _codeGenerationContext->getAllocaChain()->setPtr(_containerName,
                                                   {arrayAlloca, arrayType});

  return arrayAlloca;
}

llvm::Value *FillExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  if (!canGenerateExpression(expression))
    return nullptr;

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = nullptr;

  // Create a default value for the array

  llvm::Constant *_defaultVal = nullptr;

  _defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  _codeGenerationContext->getMultiArrayTypeForGlobal(
      arrayType, _defaultVal, _actualSizes, _elementType);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalWeakLinkage,
      _defaultVal, _containerName);

  _codeGenerationContext->setArraySizeMetadata(_globalVariable, _actualSizes);
  _codeGenerationContext->setArrayElementTypeMetadata(_globalVariable,
                                                      _elementType);

  // Builder->CreateMemSet(_globalVariable, _elementToFill,
  // Builder->getInt32(2),
  //                       (llvm::Align)4);
  return createGlobalExpression(arrayType, _globalVariable);
}

//! NOT IN USE
llvm::Value *FillExpressionGenerationStrategy::createExpressionAtom(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill,
    uint64_t &sizeToFillVal, std::vector<llvm::Value *> &indices,
    uint64_t index) {
  if (sizeToFillVal == 0)
    return nullptr;

  if (index < (_actualSizes.size())) {
    for (int64_t i = 0; i < _actualSizes[index]; i++) {
      indices.push_back(Builder->getInt32(i));
      createExpressionAtom(arrayType, v, elementToFill, sizeToFillVal, indices,
                           index + 1);
      indices.pop_back();
      if (sizeToFillVal == 0)
        return nullptr;
    }
    return nullptr;
  }
  llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);

  Builder->CreateStore(elementToFill, elementPtr);
  sizeToFillVal--;

  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createExpression(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill,
    uint64_t sizeToFillVal) {
  std::vector<llvm::Value *> indices = {Builder->getInt32(0)};

  createExpressionAtom(arrayType, v, elementToFill, sizeToFillVal, indices, 0);

  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createGlobalExpression(
    llvm::Type *arrayType, llvm::GlobalVariable *_globalVariable) {
  _isGlobal = true;
  return this->createExpressionLoop(arrayType, _globalVariable, _elementToFill,
                                    _sizeToFillInt);
}

bool FillExpressionGenerationStrategy::canGenerateExpression(
    BoundExpression *expression) {
  _fillExpression = static_cast<BoundFillExpression *>(expression);

  llvm::Value *sizeToFillVal = nullptr;

  if (_fillExpression->getSizeToFillRef().get())
    sizeToFillVal =
        _expressionGenerationFactory
            ->createStrategy(_fillExpression->getSizeToFillRef()->getKind())
            ->generateExpression(_fillExpression->getSizeToFillRef().get());

  if (llvm::isa<llvm::ConstantInt>(sizeToFillVal)) {
    llvm::ConstantInt *c = llvm::cast<llvm::ConstantInt>(sizeToFillVal);

    _sizeToFillInt = c->getSExtValue();

    if (_sizeToFillInt > _totalSize || _sizeToFillInt < 0) {
      _codeGenerationContext->getLogger()->LogError(
          "Element to fill is out of bound.  Size to "
          "fill must be less than to the "
          "actual size of the container and greater"
          "than or equal to zero in " +
          _containerName);

      return false;
    }

  } else {
    _sizeToFillInt = _totalSize;
  }

  if (_fillExpression->getElementToFillRef()->getKind() ==
          BinderKindUtils::BoundObjectExpression &&
      !llvm::isa<llvm::StructType>(_elementType)) {
    _codeGenerationContext->getLogger()->LogError(
        "Attempting to fill an array " + _containerName +
        " of non object type with a object type Expression.");
    return false;
  }

  if (_fillExpression->getElementToFillRef()->getKind() !=
          BinderKindUtils::VariableExpression &&
      _fillExpression->getElementToFillRef()->getKind() !=
          BinderKindUtils::BoundObjectExpression &&
      llvm::isa<llvm::StructType>(_elementType)) {
    _codeGenerationContext->getLogger()->LogError(
        "Attempting to fill an array " + _containerName +
        " of object type with a non object type Expression.");
    return false;
  }

  if (_fillExpression->getElementToFillRef()->getKind() ==
          BinderKindUtils::BoundObjectExpression &&
      llvm::isa<llvm::StructType>(_elementType)) {
    _objectExpression = _fillExpression->getElementToFillRef().get();
    return true;
  }

  //! Handle Case for BoundContainerExpression

  _elementToFill =
      _expressionGenerationFactory
          ->createStrategy(_fillExpression->getElementToFillRef()->getKind())
          ->generateExpression(_fillExpression->getElementToFillRef().get());

  if (_codeGenerationContext->getValueStackHandler()->isDynamicValueType()) {
    _isElementToFillDynamicValue = 1;
    _elementToFill = _codeGenerationContext->getValueStackHandler()->getValue();
  } else if (_codeGenerationContext->getValueStackHandler()->isStructType() &&
             llvm::isa<llvm::StructType>(_elementType)) {
    _elementToFill = _codeGenerationContext->getValueStackHandler()->getValue();
    _elementToFillType =
        _codeGenerationContext->getValueStackHandler()->getLLVMType();
    _codeGenerationContext->getValueStackHandler()->popAll();
    _variableExpression = _fillExpression->getElementToFillRef().get();
    return true;
  }

  //! Handle Case for isArrayType

  if (!_elementToFill) {
    _codeGenerationContext->getLogger()->LogError(
        "Element to fill must be a Value.");
    return false;
  }

  if (_elementType && _elementType != _elementToFill->getType() &&
      !_isElementToFillDynamicValue) {
    std::string elementTypeName =
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType);

    std::string itemValueTypeName =
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            _elementToFill->getType());

    _codeGenerationContext->getLogger()->LogError(
        _containerName + " Container item type mismatch. Expected " +
        elementTypeName + " but got " + itemValueTypeName);

    return false;
  }

  return true;
}
llvm::Value *
FillExpressionGenerationStrategy::createExpressionLoopWithTotalSize(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill) {
  return createExpressionLoop(arrayType, v, elementToFill, _totalSize);
}

llvm::Value *FillExpressionGenerationStrategy::createExpressionLoop(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill,
    uint64_t &sizeToFillVal) {

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  std::vector<std::vector<llvm::BasicBlock *>> loopBlocks;
  std::vector<llvm::Value *> indices;
  std::unique_ptr<AssignmentExpressionGenerationStrategy>
      assignmentExpressionGenerationStrategy =
          std::make_unique<AssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

  for (int i = 0; i < _actualSizes.size(); i++) {
    std::vector<llvm::BasicBlock *> blocks = {
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopStart-" + std::to_string(i),
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopCmp-" + std::to_string(i),
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopBody-" + std::to_string(i),
                                 currentBlock->getParent()),
        llvm::BasicBlock::Create(*TheContext,
                                 "FillExpr.loopEnd-" + std::to_string(i),
                                 currentBlock->getParent())};
    const std::string INDEX_NAME = "_fg_i:" + std::to_string(i);

    llvm::Value *index = _codeGenerationContext->createMemoryGetPtr(
        Builder->getInt32Ty(), INDEX_NAME, BinderKindUtils::MemoryKind::Global);

    assignmentExpressionGenerationStrategy->initDefaultValue(
        Builder->getInt32Ty(), index, *Builder);

    indices.push_back(index);
    loopBlocks.push_back(blocks);
  }

  llvm::Value *numberOfElementsFilled =
      _codeGenerationContext->createMemoryGetPtr(
          Builder->getInt32Ty(),
          "_fg_numberOfElementsFilled:", BinderKindUtils::MemoryKind::Global);

  Builder->CreateStore(Builder->getInt32(0), numberOfElementsFilled);

  llvm::BasicBlock *exit = llvm::BasicBlock::Create(
      *TheContext, "FillExpr.exit", currentBlock->getParent());

  Builder->CreateBr(loopBlocks[0][0]);

  for (int i = 0; i < _actualSizes.size(); i++) {
    // start
    Builder->SetInsertPoint(loopBlocks[i][0]);
    Builder->CreateStore(Builder->getInt32(0), indices[i]);
    Builder->CreateBr(loopBlocks[i][1]);

    // cmp
    Builder->SetInsertPoint(loopBlocks[i][1]);
    llvm::Value *currentIndex =
        Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
    llvm::Value *isLessThan = Builder->CreateICmpSLT(
        currentIndex, Builder->getInt32(_actualSizes[i]));
    //?------Comparison Count Increment------
    llvm::Value *isAllElementsFilled = Builder->CreateICmpSLT(
        Builder->CreateLoad(Builder->getInt32Ty(), numberOfElementsFilled),
        Builder->getInt32(sizeToFillVal));
    //?

    llvm::Value *success = Builder->CreateAnd(isLessThan, isAllElementsFilled);

    Builder->CreateCondBr(success, loopBlocks[i][2], loopBlocks[i][3]);

    // body
    Builder->SetInsertPoint(loopBlocks[i][2]);
    if (i == _actualSizes.size() - 1) {
      std::vector<llvm::Value *> indexList = {Builder->getInt32(0)};

      for (int j = 0; j < _actualSizes.size(); j++) {
        indexList.push_back(
            Builder->CreateLoad(Builder->getInt32Ty(), indices[j]));
      }

      llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indexList);

      //! USE AssignmentExpressionGenerationStrategy for All CASES
      if (_objectExpression) {
        std::unique_ptr<ObjectAssignmentExpressionGenerationStrategy>
            objectAssignmentGES =
                std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
                    _codeGenerationContext);

        objectAssignmentGES->assignObject(
            static_cast<BoundObjectExpression *>(_objectExpression), elementPtr,
            llvm::cast<llvm::StructType>(_elementType),
            elementPtr->getName().str());

      }
      //! It is temp here use _assignmentExpressionGenerationStrategy for
      //! both Array,Struct, and primitives
      else if (llvm::isa<llvm::StructType>(_elementType) &&
               _variableExpression) {
        std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrategy =
            std::make_unique<ObjectExpressionGenerationStrategy>(
                _codeGenerationContext);

        objExpGenStrategy->generateVariable(elementPtr,
                                            _elementType->getStructName().str(),
                                            _elementToFill, _isGlobal);
      } else {

        if (_isElementToFillDynamicValue) {
          DYNAMIC_VALUE_HANDLER::assignRHSDynamicValueToLHSVariable(
              elementPtr, _elementType, elementToFill, _codeGenerationContext,
              Builder);
        } else {
          Builder->CreateStore(elementToFill, elementPtr);
        }
      }

      llvm::Value *_currentIndex =
          Builder->CreateLoad(Builder->getInt32Ty(), indices[i]);
      llvm::Value *nextIndex =
          Builder->CreateAdd(_currentIndex, Builder->getInt32(1));
      Builder->CreateStore(nextIndex, indices[i]);

      //?------Elements filled Count Increment------
      Builder->CreateStore(
          Builder->CreateAdd(Builder->CreateLoad(Builder->getInt32Ty(),
                                                 numberOfElementsFilled),
                             Builder->getInt32(1)),
          numberOfElementsFilled);
      //?------End------

      Builder->CreateBr(loopBlocks[i][1]);
    } else {
      Builder->CreateBr(loopBlocks[i + 1][0]);
    }

    // end
    Builder->SetInsertPoint(loopBlocks[i][3]);
    if (i != 0) {
      llvm::Value *_currentIndex =
          Builder->CreateLoad(Builder->getInt32Ty(), indices[i - 1]);
      llvm::Value *nextIndex =
          Builder->CreateAdd(_currentIndex, Builder->getInt32(1));
      Builder->CreateStore(nextIndex, indices[i - 1]);

      Builder->CreateBr(loopBlocks[i - 1][1]);
    } else {
      Builder->CreateBr(exit);
    }
  }

  Builder->SetInsertPoint(exit);
  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createExpressionLoopWrapper(
    llvm::Type *arrayType, llvm::Value *ptr) {
  return this->createExpressionLoop(arrayType, ptr, _elementToFill,
                                    _sizeToFillInt);
}