#include "FunctionDeclarationGenerationStrategy.h"

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
  BoundFunctionDeclaration *node =
      static_cast<BoundFunctionDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      node->getLocation());

  if (node->hasParameterTypes()) {

    std::string functionName = node->getFunctionSymbol().name;

    std::vector<llvm::Type *> argTypes;
    for (int i = 0; i < node->getFunctionSymbol().parameters.size(); i++) {
      argTypes.push_back(
          _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
              node->getFunctionSymbol().parameters[i].type));
    }
    llvm::Type *returnType =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            node->getFunctionSymbol().getReturnType());

    llvm::FunctionType *FT =
        llvm::FunctionType::get(returnType, argTypes, false);

    llvm::Function *F = llvm::Function::Create(
        FT, llvm::Function::ExternalLinkage, functionName, *TheModule);

    _codeGenerationContext->addBoundedUserFunction(functionName, node);
  }
  return nullptr;
}