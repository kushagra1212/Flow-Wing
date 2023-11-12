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

  std::string variable_name = node->getVariable();

  BoundExpression *initializerExp = node->getInitializerPtr().get();

  llvm::Value *result =
      _expressionGenerationFactory->createStrategy(initializerExp->getKind())
          ->generateExpression(initializerExp);

  _codeGenerationContext->getNamedValueChain()->setNamedValue(variable_name,
                                                              result);

  // create and load variable

  llvm::AllocaInst *variable =
      Builder->CreateAlloca(_codeGenerationContext->getDynamicType()->get(),
                            nullptr, variable_name.c_str());

  _codeGenerationContext->getAllocaChain()->setAllocaInst(variable_name,
                                                          variable);

  Builder->CreateStore(
      result,
      Builder->CreateStructGEP(
          _codeGenerationContext->getDynamicType()->get(), variable,
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              result->getType())));

  return result;
}

void VariableDeclarationStatementGenerationStrategy::
    handleGlobalVariableDeclaration(BoundStatement *statement) {

  BoundVariableDeclaration *variableDeclaration =
      static_cast<BoundVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableDeclaration->getLocation());

  std::string variableName = variableDeclaration->getVariable();

  BoundExpression *expression = variableDeclaration->getInitializerPtr().get();
  llvm::Value *result =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (result == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Error in generating IR for variable declaration ");
    return;
  }
  llvm::GlobalVariable *_globalVariable = nullptr;
  llvm::AllocaInst *v = nullptr;
  if (auto constDataArray = llvm::dyn_cast<llvm::ConstantDataArray>(result)) {

    std::string str = constDataArray->getAsCString().str();

    _globalVariable = new llvm::GlobalVariable(
        *TheModule,
        llvm::ArrayType::get(llvm::IntegerType::getInt8Ty((*TheContext)),
                             str.length() + 1),
        true, llvm::GlobalValue::ExternalLinkage, constDataArray, variableName);

  } else {
    llvm::Constant *constant =
        _codeGenerationContext->createConstantFromValue(result);

    if (constant) {
      _globalVariable = new llvm::GlobalVariable(
          *TheModule, result->getType(), false,
          llvm::GlobalValue::ExternalLinkage, constant, variableName);
    } else {
      _globalVariable = new llvm::GlobalVariable(
          *TheModule, result->getType(), false,
          llvm::GlobalValue::ExternalLinkage,
          llvm::Constant::getNullValue(result->getType()), variableName);
    }
  }
}

llvm::Value *
VariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}