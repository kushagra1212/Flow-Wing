#include "ContainerDeclarationStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../../expressions/FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

ContainerDeclarationStatementGenerationStrategy::
    ContainerDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  auto contVarDec = static_cast<BoundVariableDeclaration *>(statement);

  BoundArrayTypeExpression *arrayTypeExpression =
      static_cast<BoundArrayTypeExpression *>(
          contVarDec->getTypeExpression().get());

  return generateCommonStatement(arrayTypeExpression,
                                 contVarDec->getVariableName(),
                                 contVarDec->getInitializerPtr().get());
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateCommonStatement(
    BoundArrayTypeExpression *arrayTypeExpression,
    const std::string &containerName, BoundExpression *initializer) {
  const SyntaxKindUtils::SyntaxKind &containerElementType =
      arrayTypeExpression->getElementType();

  this->calcActualContainerSize(arrayTypeExpression);
  _containerName = containerName;

  _elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
      arrayTypeExpression->getElementType());

  BinderKindUtils::BoundNodeKind kind = initializer->getKind();

  switch (kind) {
    case BinderKindUtils::BoundNodeKind::BoundBracketedExpression: {
      return generateBracketLocalExpression(
          (BoundBracketedExpression *)initializer);
    }
    case BinderKindUtils::BoundNodeKind::CallExpression: {
      if (!canGenerateCallExpression(initializer)) {
        return nullptr;
      }
      llvm::ArrayType *arrayType = nullptr;

      llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

      _codeGenerationContext->getMultiArrayType(arrayType, _defaultVal,
                                                _actualSizes, _elementType);

      llvm::AllocaInst *arrayAlloca =
          Builder->CreateAlloca(arrayType, nullptr, _containerName);

      // Fill the array with default values

      _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                              arrayAlloca);

      // Store the result of the call in the localVariable variable
      Builder->CreateStore(_loadedValue, arrayAlloca);

      return nullptr;
    }

    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Container Expression Type ");
      break;
    }
  }
  return nullptr;
}

const bool
ContainerDeclarationStatementGenerationStrategy::canGenerateCallExpression(
    BoundExpression *callExp) {
  llvm::Value *value =
      _expressionGenerationFactory->createStrategy(callExp->getKind())
          ->generateExpression(callExp);

  llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(value);
  auto *calledFunction = calledInst->getCalledFunction();
  llvm::ArrayType *arrayType = nullptr;
  llvm::Type *elementType = nullptr;
  std::vector<uint64_t> actualSizes;
  _codeGenerationContext->getRetrunedArrayType(calledFunction, arrayType,
                                               elementType, actualSizes);

  if (elementType != _elementType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType) +
        " but function " + calledFunction->getName().str() +
        " is returning array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(elementType));

    return false;
  }

  if (actualSizes.size() != _actualSizes.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Dimensions of the Containers Must Be same, Expected array to be "
        "of " +
        std::to_string(_actualSizes.size()) + " Dimension but found " +
        "array of " + std::to_string(actualSizes.size()) + " Dimension");

    return false;
  }

  for (uint64_t i = 0; i < actualSizes.size(); i++) {
    if (actualSizes[i] != _actualSizes[i]) {
      _codeGenerationContext->getLogger()->LogError(
          "Dimensions of the Containers must be same, Expected array's " +
          std::to_string(i) +
          " th Dimension  to "
          "be "
          "equal to " +
          std::to_string(_actualSizes[i]) + ", but found " +
          std::to_string(actualSizes[i]));

      return false;
    }
  }

  _loadedValue = Builder->CreateLoad(arrayType, calledInst);

  return true;
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::
    generateBracketGlobalExpression(
        BoundBracketedExpression *bracketedExpression) {
  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {
    case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
      std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
          std::make_unique<ContainerExpressionGenerationStrategy>(
              _codeGenerationContext, _actualSizes, _elementType,
              _containerName);

      return specificStrategy->generateGlobalExpression(
          bracketedExpression->getExpressionRef().get());
    }

    case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
      std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
          std::make_unique<FillExpressionGenerationStrategy>(
              _codeGenerationContext, _actualSizes, _elementType,
              _containerName);

      return specificStrategy->generateGlobalExpression(
          bracketedExpression->getExpressionRef().get());
    }

    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Container Expression Type ");
      break;
    }
  }

  return nullptr;
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateBracketLocalExpression(
    BoundBracketedExpression *bracketedExpression) {
  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {
    case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
      std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
          std::make_unique<ContainerExpressionGenerationStrategy>(
              _codeGenerationContext, _actualSizes, _elementType,
              _containerName);

      return specificStrategy->generateExpression(
          bracketedExpression->getExpressionRef().get());
    }

    case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
      std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
          std::make_unique<FillExpressionGenerationStrategy>(
              _codeGenerationContext, _actualSizes, _elementType,
              _containerName);

      return specificStrategy->generateExpression(
          bracketedExpression->getExpressionRef().get());
    }

    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Container Expression Type ");
      break;
    }
  }

  return nullptr;
}
llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  auto contVarDec = static_cast<BoundVariableDeclaration *>(statement);

  BoundArrayTypeExpression *arrayTypeExpression =
      static_cast<BoundArrayTypeExpression *>(
          contVarDec->getTypeExpression().get());

  const SyntaxKindUtils::SyntaxKind &containerElementType =
      arrayTypeExpression->getElementType();

  this->calcActualContainerSize(arrayTypeExpression);
  _containerName = contVarDec->getVariableName();

  _elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
      arrayTypeExpression->getElementType());

  BinderKindUtils::BoundNodeKind kind =
      contVarDec->getInitializerPtr()->getKind();

  switch (kind) {
    case BinderKindUtils::BoundNodeKind::BoundBracketedExpression: {
      return generateBracketGlobalExpression(
          (BoundBracketedExpression *)contVarDec->getInitializerPtr().get());
    }
    case BinderKindUtils::BoundNodeKind::CallExpression: {
      if (!canGenerateCallExpression(contVarDec->getInitializerPtr().get())) {
        return nullptr;
      }

      llvm::ArrayType *arrayType = nullptr;

      // Create a default value for the array

      llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

      _codeGenerationContext->getMultiArrayType(arrayType, _defaultVal,
                                                _actualSizes, _elementType);
      llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
          *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
          _defaultVal, _containerName);

      _codeGenerationContext->setArraySizeMetadata(_globalVariable,
                                                   _actualSizes);
      _codeGenerationContext->setArrayElementTypeMetadata(_globalVariable,
                                                          _elementType);

      // Store the result of the call in the _globalVariable variable
      Builder->CreateStore(_loadedValue, _globalVariable);
      return nullptr;
    }

    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Container Expression Type ");
      break;
    }
  }
  return nullptr;
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
