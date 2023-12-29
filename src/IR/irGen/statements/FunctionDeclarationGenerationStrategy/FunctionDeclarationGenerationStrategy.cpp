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
  BoundFunctionDeclaration *fd =
      static_cast<BoundFunctionDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      fd->getLocation());

  if (fd->getParametersRef().size()) {

    std::vector<llvm::Type *> argTypes;
    for (int i = 0; i < fd->getParametersRef().size(); i++) {

      llvm::Type *parmType = nullptr;

      if (fd->getParametersRef()[i]->getVariableTypeRef() ==
          Utils::type::UNKNOWN) {

        parmType = (_codeGenerationContext->getDynamicType()->get());
        argTypes.push_back(parmType);

        _codeGenerationContext->getArgsTypeHandler()->addArgsType(
            fd->getFunctionNameRef(), std::make_unique<LLVMType>(parmType));

      } else if (Utils::isContainerType(
                     fd->getParametersRef()[i]->getVariableTypeRef())) {

        Utils::type containerElementType = Utils::toContainerElementType(
            fd->getParametersRef()[i]->getVariableTypeRef());

        BoundArrayVariableExpression *boundArrayVariable =
            static_cast<BoundArrayVariableExpression *>(
                fd->getParametersRef()[i].get());

        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            boundArrayVariable->getLocation());

        size_t multiDimSize =
            boundArrayVariable->getSizeExpressionsRef().size();

        parmType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            containerElementType);

        std::unique_ptr<LiteralExpressionGenerationStrategy>
            literalExpressionGenerationStrategy =
                std::make_unique<LiteralExpressionGenerationStrategy>(
                    _codeGenerationContext);
        for (int64_t k = multiDimSize - 1; k >= 0; k--) {

          llvm::Value *arraySize =
              literalExpressionGenerationStrategy->generateExpression(
                  boundArrayVariable->getSizeExpressionsRef()[k].get());

          if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
            _codeGenerationContext->getLogger()->LogError(
                "Array size must be a constant integer");
          }

          llvm::ConstantInt *arraySizeConst =
              llvm::cast<llvm::ConstantInt>(arraySize);

          parmType =
              llvm::ArrayType::get(parmType, arraySizeConst->getSExtValue());
        }

        llvm::Type *parmTypePointer = llvm::PointerType::get(parmType, 0);
        argTypes.push_back(parmTypePointer);

        _codeGenerationContext->getArgsTypeHandler()->addArgsType(
            fd->getFunctionNameRef(),
            std::make_unique<LLVMArrayType>(parmTypePointer, parmType));

      } else {

        parmType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            fd->getParametersRef()[i]->getVariableTypeRef());
        argTypes.push_back(parmType);
        _codeGenerationContext->getArgsTypeHandler()->addArgsType(
            fd->getFunctionNameRef(), std::make_unique<LLVMType>(parmType));
      }
    }
    llvm::Type *returnType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            fd->getReturnType());

    llvm::FunctionType *FT =
        llvm::FunctionType::get(returnType, argTypes, false);

    llvm::Function *F =
        llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                               fd->getFunctionNameRef(), *TheModule);

    const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs =
        _codeGenerationContext->getArgsTypeHandler()->getArgsType(
            fd->getFunctionNameRef());

    for (unsigned i = 0; i < F->arg_size(); ++i) {
      std::string argInfo = "";
      llvm::Argument *arg = F->getArg(i);

      if (llvmArrayArgs[i]->isPointerToArray()) {
        LLVMArrayType *llvmArrayType =
            static_cast<LLVMArrayType *>(llvmArrayArgs[i].get());
        llvm::ArrayType *arrayType =
            static_cast<llvm::ArrayType *>(llvmArrayType->getElementType());

        arg->setName("arg" + std::to_string(i) + "_ptr");

        uint64_t arraySize = arrayType->getNumElements();

        // Create a metadata string that describes the argument

        argInfo = fd->getParametersRef()[i]->getVariableNameRef() + ":" +
                  std::to_string(i) + ":Array:" +
                  _codeGenerationContext->getMapper()->getLLVMTypeName(
                      arrayType->getElementType()) +
                  ":size:" + std::to_string(arraySize);
      } else {

        arg->setName("arg" + std::to_string(i));

        // Create a metadata string that describes the argument
        argInfo = fd->getParametersRef()[i]->getVariableNameRef() + ":" +
                  std::to_string(i) + ":" +
                  _codeGenerationContext->getMapper()->getLLVMTypeName(
                      llvmArrayArgs[i]->getType());
      }

      llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext, argInfo);
      llvm::StringRef Kind = "argInfo" + std::to_string(i);
      // Attach the metadata to the argument
      F->setMetadata(Kind, llvm::MDNode::get(*TheContext, argInfoMD));
    }

    _codeGenerationContext->addBoundedUserFunction(fd->getFunctionNameRef(),
                                                   fd);
  }
  return nullptr;
}