#include "StatementGenerationFactory.h"

#include "BlockStatementGenerationStrategy/BlockStatementGenerationStrategy.h"
#include "BreakStatementGenerationStrategy/BreakStatementGenerationStrategy.h"
#include "BringStatementGenerationStrategy/BringStatementGenerationStrategy.h"
#include "ContinueStatementGenerationStrategy/ContinueStatementGenerationStrategy.h"
#include "ExpressionStatementGenerationStrategy/ExpressionStatementGenerationStrategy.h"
#include "ForStatementGenerationStrategy/ForStatementGenerationStrategy.h"
#include "FunctionDeclarationGenerationStrategy/FunctionDeclarationGenerationStrategy.h"
#include "IfStatementGenerationStrategy/IfStatementGenerationStrategy.h"
#include "ReturnStatementGenerationStrategy/ReturnStatementGenerationStrategy.h"
#include "VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
#include "WhileStatementGenerationStrategy/WhileStatementGenerationStrategy.h"

StatementGenerationFactory::StatementGenerationFactory(
    CodeGenerationContext *context)
    : _codeGenerationContext(context){};

std::unique_ptr<StatementGenerationStrategy>
StatementGenerationFactory::createStrategy(
    BinderKindUtils::BoundNodeKind kind) {
  switch (kind) {
    case BinderKindUtils::BoundNodeKind::ExpressionStatement:
      return std::make_unique<ExpressionStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::BlockStatement:
      return std::make_unique<BlockStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::VariableDeclaration:
      return std::make_unique<VariableDeclarationStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::IfStatement:
      return std::make_unique<IfStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::WhileStatement:
      return std::make_unique<WhileStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::ForStatement:
      return std::make_unique<ForStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::FunctionDeclaration:
      return std::make_unique<FunctionDeclarationGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::BreakStatement:
      return std::make_unique<BreakStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::ContinueStatement:
      return std::make_unique<ContinueStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::ReturnStatement:
      return std::make_unique<ReturnStatementGenerationStrategy>(
          _codeGenerationContext);
    case BinderKindUtils::BoundNodeKind::BringStatement:
      return std::make_unique<BringStatementGenerationStrategy>(
          _codeGenerationContext);
    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Statement Type ");
      return nullptr;
    }
  }
}