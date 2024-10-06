#include "SwitchStatementGenerationStrategy.h"
#include <cstdint>
#include <memory>
#include <sys/types.h>

SwitchStatementGenerationStrategy::SwitchStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *SwitchStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundSwitchStatement *boundSwitchStatement =
      static_cast<BoundSwitchStatement *>(statement);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundSwitchStatement->getLocation());

  std::unique_ptr<BinaryExpressionGenerationStrategy>
      binaryExpressionGenerationStrategy =
          std::make_unique<BinaryExpressionGenerationStrategy>(
              _codeGenerationContext);

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();

  const uint64_t casesSize =
      boundSwitchStatement->getCaseStatementsRef().size();

  std::vector<llvm::BasicBlock *> casesCondtionBB;
  this->populateSwitchStatementsBasicBlock(casesCondtionBB, casesSize,
                                           function);

  std::vector<llvm::BasicBlock *> casesBodyBB;
  this->populateSwitchStatementsBasicBlock(casesBodyBB, casesSize, function);
  llvm::BasicBlock *defaultSwitchBB =
      llvm::BasicBlock::Create(*TheContext, "defaultSwitchBB", function);

  llvm::BasicBlock *afterSwitchBB =
      llvm::BasicBlock::Create(*TheContext, "afterSwitchBB", function);

  Builder->CreateBr(casesCondtionBB[0]);

  for (uint64_t i = 0; i < casesSize; i++) {
    BoundCaseStatement *boundCaseStatement =
        boundSwitchStatement->getCaseStatementsRef()[i].get();

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundCaseStatement->getLocation());

    {
      Builder->SetInsertPoint(casesCondtionBB[i]);

      llvm::Value *conditionExpressionValue = nullptr;

      this->populateSwitchExpressionValue(
          conditionExpressionValue,
          boundSwitchStatement->getSwitchExpressionRef().get());

      if (conditionExpressionValue == nullptr) {

        _codeGenerationContext->getLogger()->LogError(
            "Expected an switch value in "
            "switch statement");

        return nullptr;
      }

      llvm::Value *conditionValue = nullptr;

      this->populateSwitchExpressionValue(
          conditionValue, boundCaseStatement->getCaseExpressionRef().get());

      if (conditionValue == nullptr) {
        _codeGenerationContext->getLogger()->LogError(
            "Expected an value in switch case statement");
        return nullptr;
      }

      llvm::Value *condResult =
          binaryExpressionGenerationStrategy->performOperation(
              conditionValue, conditionExpressionValue,
              BinderKindUtils::BoundBinaryOperatorKind::Equals);

      condResult = _boolTypeConverter->convertExplicit(condResult);

      if (i == casesBodyBB.size() - 1) {
        Builder->CreateCondBr(condResult, casesBodyBB[i], defaultSwitchBB);
      } else {
        Builder->CreateCondBr(condResult, casesBodyBB[i],
                              casesCondtionBB[i + 1]);
      }
    }

    {
      Builder->SetInsertPoint(casesBodyBB[i]);

      _statementGenerationFactory
          ->createStrategy(boundCaseStatement->getBodyStatementRef()->getKind())
          ->generateStatement(boundCaseStatement->getBodyStatementRef().get());

      Builder->CreateBr(afterSwitchBB);
    }
  }

  //? Default case

  {
    Builder->SetInsertPoint(defaultSwitchBB);

    _statementGenerationFactory
        ->createStrategy(boundSwitchStatement->getDefaultCaseStatementRef()
                             ->getBodyStatementRef()
                             ->getKind())
        ->generateStatement(boundSwitchStatement->getDefaultCaseStatementRef()
                                ->getBodyStatementRef()
                                .get());

    Builder->CreateBr(afterSwitchBB);
  }

  Builder->SetInsertPoint(afterSwitchBB);

  return nullptr;
}
llvm::Value *SwitchStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}

void SwitchStatementGenerationStrategy::populateSwitchStatementsBasicBlock(
    std::vector<llvm::BasicBlock *> &casesBB, const uint64_t &casesSize,
    llvm::Function *&function) {
  for (int i = 1; i <= casesSize; i++) {
    std::string caseName = "case:";

    if (i != casesSize) {
      caseName += std::to_string(i) + ":";
    } else {
      caseName += "default:";
    }

    casesBB.emplace_back(llvm::BasicBlock::Create(
        *TheContext, "case:" + std::to_string(i) + ":", function));
  }
}

void SwitchStatementGenerationStrategy::populateSwitchExpressionValue(
    llvm::Value *&expressionValue, BoundExpression *expression) {
  expressionValue =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (_codeGenerationContext->getValueStackHandler()->isStructType() ||
      _codeGenerationContext->getValueStackHandler()->isArrayType()) {
    _codeGenerationContext->getValueStackHandler()->popAll();

    _codeGenerationContext->getLogger()->LogError(
        "Switch expression value should not be a struct or array type");

    expressionValue = nullptr;
    return;
  }

  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    expressionValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }
}
