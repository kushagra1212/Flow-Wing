#ifndef __FLOWWING_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING_EXPRESSION_GENERATION_STRATEGY_H__
#include "../../../../bind/BoundExpression.h"
#include "../../../../syntax/SyntaxKindUtils.h"
#include "../../../LLVMTypeConversion/LLVMValueConverter/LLVMValueConverter.h"
#include "../../../context/CodeGenerationContext.h"
#include "../../../strategies/UnaryOperationStrategy/UnaryOperationStrategy.h"

class ExpressionGenerationStrategy {
public:
  CodeGenerationContext *_codeGenerationContext;

  llvm::Module *TheModule = nullptr;
  llvm::IRBuilder<> *Builder = nullptr;
  llvm::LLVMContext *TheContext = nullptr;

  std::unique_ptr<LLVMValueConverter> _llvmValueConverter;
  std::unique_ptr<UnaryOperationStrategy> _unaryOperationStrategy;

  ExpressionGenerationStrategy(CodeGenerationContext *context)
      : _codeGenerationContext(context), TheModule(context->getModule().get()),
        Builder(context->getBuilder().get()),
        TheContext(context->getContext().get()),
        _llvmValueConverter(std::make_unique<LLVMValueConverter>(context)),
        _unaryOperationStrategy(
            std::make_unique<UnaryOperationStrategy>(context)){};
  ExpressionGenerationStrategy *
  createStrategy(BinderKindUtils::BoundNodeKind kind);

  virtual llvm::Value *generateExpression(BoundExpression *expression) = 0;
};

#endif // __FLOWWING_EXPRESSION_GENERATION_STRATEGY_H__
