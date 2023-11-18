#include "VariableDeclarationStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

VariableDeclarationStatementGenerationStrategy::
    VariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *VariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *node =
      static_cast<BoundVariableDeclaration *>(statement);

  std::string variableName = node->getVariable();

  BoundExpression *initializerExp = node->getInitializerPtr().get();

  llvm::Value *result =
      _expressionGenerationFactory->createStrategy(initializerExp->getKind())
          ->generateExpression(initializerExp);
  Utils::type variableType = node->getType();

  if (variableType != Utils::type::UNKNOWN &&
      _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          result->getType()) != variableType) {

    std::string errorStr = _codeGenerationContext->getLogger()->getLLVMErrorMsg(
        "Type mismatch in variable declaration " + variableName +
            " Expected type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
            " but got type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(
                result->getType()),
        node->getLocation());
    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
        {Builder->CreateGlobalStringPtr(errorStr)});
    return nullptr;
  }

  _codeGenerationContext->getNamedValueChain()->setNamedValue(variableName,
                                                              result);

  // create and load variable

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(_codeGenerationContext->getDynamicType()->get(),
                            nullptr, variableName.c_str());

  _codeGenerationContext->getAllocaChain()->setAllocaInst(variableName,
                                                          variable);

  Builder->CreateStore(
      result,
      Builder->CreateStructGEP(
          _codeGenerationContext->getDynamicType()->get(), variable,
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              result->getType())));

  return result;
}

llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableDeclaration->getLocation());

  std::string variableName = variableDeclaration->getVariable();

  BoundExpression *expression = variableDeclaration->getInitializerPtr().get();
  llvm::Value *result =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (!result) {
    _codeGenerationContext->getLogger()->LogError(
        "Rhs of variable " + variableName + " is notthing");
    return nullptr;
  }
  Utils::type variableType = variableDeclaration->getType();
  if (variableType != Utils::type::UNKNOWN &&
      _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          result->getType()) != variableType) {

    std::string errorStr = _codeGenerationContext->getLogger()->getLLVMErrorMsg(
        "Type mismatch in variable declaration " + variableName +
            " Expected type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
            " but got type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(
                result->getType()),
        variableDeclaration->getLocation());
    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
        {Builder->CreateGlobalStringPtr(errorStr)});
    return nullptr;
  }
  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, _codeGenerationContext->getDynamicType()->get(), false,
      llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(
          _codeGenerationContext->getDynamicType()->get()),
      variableName);

  llvm::Value *loadedValue = Builder->CreateLoad(
      _codeGenerationContext->getDynamicType()->get(), _globalVariable);

  llvm::Value *updatedValue = Builder->CreateInsertValue(
      loadedValue, result,
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          result->getType()));

  _codeGenerationContext->getGlobalTypeMap()[variableName] =
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          result->getType());

  Builder->CreateStore(updatedValue, _globalVariable);
  return result;
}