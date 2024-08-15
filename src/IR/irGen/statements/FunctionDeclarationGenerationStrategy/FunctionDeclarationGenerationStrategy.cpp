#include "FunctionDeclarationGenerationStrategy.h"

#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"

FunctionDeclarationGenerationStrategy::FunctionDeclarationGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *FunctionDeclarationGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundFunctionDeclaration *node =
      static_cast<BoundFunctionDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      node->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Function Declaration is not allowed in global scope ");

  return nullptr;
}

llvm::Value *FunctionDeclarationGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  this->generate(statement);
  return nullptr;
}

llvm::Function *FunctionDeclarationGenerationStrategy::generate(
    BoundStatement *statement, std::vector<llvm::Type *> classArgs,
    std::string className) {
  BoundFunctionDeclaration *fd =
      static_cast<BoundFunctionDeclaration *>(statement);
  const std::string FUNCTION_NAME = fd->getFunctionNameRef();

  Utils::DEBUG_LOG("Declaring Function: " + FUNCTION_NAME);

  bool isFunctionAlreadyDeclared = TheModule->getFunction(FUNCTION_NAME);
  _codeGenerationContext->_functionTypes[FUNCTION_NAME] =
      std::make_unique<FlowWing::Function>();
  _codeGenerationContext->_functionTypes[FUNCTION_NAME]->setFunctionName(
      FUNCTION_NAME);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      fd->getLocation());
  std::unique_ptr<LiteralExpressionGenerationStrategy>
      literalExpressionGenerationStrategy =
          std::make_unique<LiteralExpressionGenerationStrategy>(
              _codeGenerationContext);
  std::vector<llvm::Type *> argTypes;
  std::vector<std::pair<uint64_t, llvm::Type *>> attributeTypes;

  //? Taking value to return as parameter
  if (!fd->hasAsReturnType()) {
    std::vector<llvm::Type *> returnStructTypeList = {};
    for (const auto &rTypeExpr : fd->getReturnTypeExprListRef()) {
      BoundTypeExpression *bTE =
          static_cast<BoundTypeExpression *>(rTypeExpr.get());

      switch (bTE->getKind()) {
      case BinderKindUtils::BoundArrayTypeExpression: {
        std::unique_ptr<CustomTypeStatementGenerationStrategy>
            customTypeStatementGenerationStrategy =
                std::make_unique<CustomTypeStatementGenerationStrategy>(
                    _codeGenerationContext);
        returnStructTypeList.push_back(
            customTypeStatementGenerationStrategy->getType(bTE));

        break;
      }
      case BinderKindUtils::BoundObjectTypeExpression: {

        returnStructTypeList.push_back(getStructType(
            static_cast<BoundObjectTypeExpression *>(bTE), className));
        break;
      }

      case BinderKindUtils::BoundTypeExpression: {

        if (bTE->getSyntaxType() != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
          returnStructTypeList.push_back(
              _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
                  bTE->getSyntaxType()));
        }

        break;
      }
      default: {
        break;
      }
      }
    }

    if (fd->getReturnTypeExprListRef().size() > 1) {

      std::vector<llvm::Type *> returnStructTypePtrList(
          returnStructTypeList.size(), llvm::Type::getInt8PtrTy(*TheContext));

      llvm::Type *StructType =
          llvm::StructType::create(*TheContext, returnStructTypePtrList);

      argTypes.push_back(llvm::PointerType::get(StructType, 0));
      _codeGenerationContext->getArgsTypeHandler()->addArgsType(
          FUNCTION_NAME,
          std::make_unique<LLVMType>(StructType, returnStructTypeList));
    } else if (fd->getReturnTypeExprListRef().size() &&
               returnStructTypeList.size()) {

      argTypes.push_back(llvm::PointerType::get(returnStructTypeList[0], 0));
      _codeGenerationContext->getArgsTypeHandler()->addArgsType(
          FUNCTION_NAME, std::make_unique<LLVMType>(returnStructTypeList[0]));
    }
  }

  _codeGenerationContext->_functionTypes[FUNCTION_NAME]
      ->setOptionalParameterStartIndex(fd->getOptionalParameterStartIndex());

  for (int i = 0; i < fd->getParametersRef().size(); i++) {
    llvm::Type *parmType = nullptr;
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        fd->getParametersRef()[i]->getLocation());

    _codeGenerationContext->_functionTypes[FUNCTION_NAME]->addParameter(
        fd->getParametersRef()[i].get());

    llvm::Type *_argType = nullptr;
    std::unique_ptr<LLVMType> argLLVMType = nullptr;

    if (fd->getParametersRef()[i]->getTypeExpression()->getSyntaxType() ==
        SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
      parmType = (_codeGenerationContext->getDynamicType()->get());

      _argType = llvm::PointerType::get(parmType, 0);
      argLLVMType = std::make_unique<LLVMType>(parmType);
      attributeTypes.push_back({argTypes.size(), parmType});
    } else if (fd->getParametersRef()[i]
                   ->getTypeExpression()
                   ->getSyntaxType() ==
               SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
      BoundArrayTypeExpression *arrayTypeExpression =
          static_cast<BoundArrayTypeExpression *>(
              fd->getParametersRef()[i]->getTypeExpression().get());

      SyntaxKindUtils::SyntaxKind containerElementType =
          arrayTypeExpression->getElementType();

      BoundVariableDeclaration *boundArrayVariable =
          static_cast<BoundVariableDeclaration *>(
              fd->getParametersRef()[i].get());

      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          boundArrayVariable->getLocation());

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

      if (fd->getParametersRef()[i]->getHasAsKeyword()) {
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
      attributeTypes.push_back({argTypes.size(), parmType});
    } else if (fd->getParametersRef()[i]
                   ->getTypeExpression()
                   ->getSyntaxType() ==
               SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
      BoundObjectTypeExpression *objectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(
              fd->getParametersRef()[i]->getTypeExpression().get());

      llvm::StructType *structType =
          getStructType(objectTypeExpression, className);

      if (!structType) {
        _codeGenerationContext->getLogger()->LogError(
            "Object type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(structType) +
            " was not found when calling function " + FUNCTION_NAME);
        return nullptr;
      }

      if (fd->getParametersRef()[i]->getHasAsKeyword()) {
        _argType = structType;
        argLLVMType = std::make_unique<LLVMType>(structType);
      } else {
        _argType = llvm::PointerType::get(structType, 0);
        argLLVMType = std::make_unique<LLVMObjectType>(_argType, structType);
      }

    } else {
      parmType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          fd->getParametersRef()[i]->getTypeExpression()->getSyntaxType());

      if (fd->getParametersRef()[i]->getHasAsKeyword()) {
        _argType = parmType;
        argLLVMType = std::make_unique<LLVMType>(parmType);
      } else {
        _argType = llvm::PointerType::get(parmType, 0);
        argLLVMType = std::make_unique<LLVMPrimitiveType>(_argType, parmType);
      }
      attributeTypes.push_back({argTypes.size(), parmType});
    }
    argTypes.push_back(_argType);

    if (!isFunctionAlreadyDeclared)
      _codeGenerationContext->getArgsTypeHandler()->addArgsType(
          FUNCTION_NAME, std::move(argLLVMType));
  }

  if (_codeGenerationContext->_classTypes.find(FUNCTION_NAME.substr(
          0,
          FUNCTION_NAME.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX))) !=
      _codeGenerationContext->_classTypes.end()) {
    classArgs = {llvm::Type::getInt8PtrTy(*TheContext)};
  }
  for (auto arg : classArgs) {
    argTypes.push_back(arg);
    _codeGenerationContext->getArgsTypeHandler()->addArgsType(
        FUNCTION_NAME, std::make_unique<LLVMType>(arg));
  }
  llvm::FunctionType *FT = nullptr;
  llvm::Function *F = nullptr;
  std::string returnInfo = "";

  for (auto &rTypeExpr : fd->getReturnTypeExprListRef()) {
    llvm::Type *returnType = nullptr;
    BoundTypeExpression *bTE =
        static_cast<BoundTypeExpression *>(rTypeExpr.get());

    switch (bTE->getKind()) {
    case BinderKindUtils::BoundTypeExpression: {
      llvm::Type *elementType =
          _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
              bTE->getSyntaxType());
      returnType = llvm::PointerType::get(elementType, 0);

      FT = llvm::FunctionType::get(fd->hasAsReturnType()
                                       ? elementType
                                       : llvm::Type::getVoidTy(*TheContext),
                                   argTypes, false);
      F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                                 FUNCTION_NAME, *TheModule);

      _codeGenerationContext->getReturnTypeHandler()->addReturnType(
          FUNCTION_NAME,
          std::make_unique<LLVMPrimitiveType>(returnType, elementType),
          fd->hasAsReturnType());
      _codeGenerationContext->_functionTypes[FUNCTION_NAME]->setReturnType(
          elementType, fd->hasAsReturnType());
      returnInfo =
          FUNCTION_NAME + ":rt:pr:" +
          std::to_string(
              _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
                  elementType));
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
        returnInfo =
            FUNCTION_NAME + ":rt:ay:" +
            std::to_string(
                _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
                    elementType)) +
            ":sz:";
      } else {
        BoundObjectTypeExpression *objectTypeExpression =
            static_cast<BoundObjectTypeExpression *>(
                boundArrayTypeExpression->getNonTrivialElementType().get());

        elementType = _codeGenerationContext
                          ->getFlowWingType(objectTypeExpression->getTypeName())
                          .getType();
        returnInfo = FUNCTION_NAME +
                     ":rt:ay:" + objectTypeExpression->getTypeName().c_str() +
                     ":sz:";
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
      FT = llvm::FunctionType::get(fd->hasAsReturnType()
                                       ? returnType
                                       : llvm::Type::getVoidTy(*TheContext),
                                   argTypes, false);
      F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                                 FUNCTION_NAME, *TheModule);

      _codeGenerationContext->getReturnTypeHandler()->addReturnType(
          FUNCTION_NAME,
          std::make_unique<LLVMArrayType>(returnType, arrayType, elementType,
                                          returnDimentions,
                                          boundArrayTypeExpression),
          fd->hasAsReturnType());
      _codeGenerationContext->_functionTypes[FUNCTION_NAME]->setReturnType(
          arrayType, fd->hasAsReturnType());
      for (int64_t k = 0; k < returnDimentions.size(); k++) {
        returnInfo += std::to_string(returnDimentions[k]) + ":";
      }

      attributeTypes.push_back({argTypes.size(), arrayType});
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

      if (!structType) {

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
      FT = llvm::FunctionType::get(fd->hasAsReturnType()
                                       ? returnType
                                       : llvm::Type::getVoidTy(*TheContext),
                                   argTypes, false);
      F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                                 FUNCTION_NAME, *TheModule);

      _codeGenerationContext->getReturnTypeHandler()->addReturnType(
          FUNCTION_NAME,
          std::make_unique<LLVMObjectType>(returnType, structType),
          fd->hasAsReturnType());
      _codeGenerationContext->_functionTypes[FUNCTION_NAME]->setReturnType(
          structType, fd->hasAsReturnType());
      returnInfo =
          FUNCTION_NAME + ":rt:ob:" + boundObjectTypeExpression->getTypeName();
      if (_codeGenerationContext->_classTypes.find(FUNCTION_NAME.substr(
              0, FUNCTION_NAME.find(
                     FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX))) ==
          _codeGenerationContext->_classTypes.end()) {
        //        llvm::Attribute::AttrKind kind = ;
        if (!_codeGenerationContext->isValidClassType(structType)) {

          llvm::AttrBuilder attribute(*TheContext);
          attribute.addTypeAttr(llvm::Attribute::AttrKind::StructRet,
                                structType);
          F->addParamAttrs(0, attribute);
          attributeTypes.push_back({argTypes.size(), structType});
        }
      }
      break;
    }
    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Invalid return type for function");
      return nullptr;
    }
    }
  }

  // Return type metadata
  F->setMetadata(
      "rt", llvm::MDNode::get(*TheContext,
                              llvm::MDString::get(*TheContext, returnInfo)));

  _codeGenerationContext->verifyFunction(F, FUNCTION_NAME);
  _codeGenerationContext->addBoundedUserFunction(FUNCTION_NAME, fd);

  return F;
}

llvm::StructType *FunctionDeclarationGenerationStrategy::getStructType(
    BoundObjectTypeExpression *objectTypeExpression,
    std::__1::string &className) {

  llvm::StructType *structType =
      _codeGenerationContext
          ->_classLLVMTypes[objectTypeExpression->getTypeName()];

  std::string typeName = "";
  if (!structType) {
    typeName = objectTypeExpression->getTypeName();

    structType =
        _codeGenerationContext->getFlowWingType(typeName).getStructType();
    if (!structType) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected an object type " + Utils::getActualTypeName(typeName) +
          " but, got " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(structType));
      return nullptr;
    }
  }

  return structType;
}
