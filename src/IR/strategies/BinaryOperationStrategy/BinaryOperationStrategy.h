#ifndef FLOWWING_BINARYOPERATIONSTRATEGY_H
#define FLOWWING_BINARYOPERATIONSTRATEGY_H

#include "../../../Common.h"
#include "../../../SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../../LLVMTypeConversion/BoolTypeConverter/BoolTypeConverter.h"
#include "../../LLVMTypeConversion/DoubleTypeConverter/DoubleTypeConverter.h"
#include "../../LLVMTypeConversion/Int32TypeConverter/Int32TypeConverter.h"
#include "../../LLVMTypeConversion/Int8TypeConverter/Int8TypeConverter.h"
#include "../../LLVMTypeConversion/StringTypeConverter/StringTypeConverter.h"
#include "../../LLVMTypeConversion/TypeSpecificValueVisitor.h"
#include "llvm/IR/Value.h"

class BinaryOperationStrategy {
public:
  std::unique_ptr<BoolTypeConverter> _boolTypeConverter;
  std::unique_ptr<DoubleTypeConverter> _doubleTypeConverter;
  std::unique_ptr<Int32TypeConverter> _int32TypeConverter;
  std::unique_ptr<StringTypeConverter> _stringTypeConverter;
  std::unique_ptr<Int8TypeConverter> _int8TypeConverter;
  std::unique_ptr<FloatTypeConverter> _floatTypeConverter;
  std::unique_ptr<TypeSpecificValueVisitor> _typeSpecificValueVisitor;

  CodeGenerationContext *_codeGenerationContext;

  llvm::Module *TheModule = nullptr;
  llvm::IRBuilder<> *Builder = nullptr;
  llvm::LLVMContext *TheContext = nullptr;

  BinaryOperationStrategy(CodeGenerationContext *context)
      : _boolTypeConverter(std::make_unique<BoolTypeConverter>(context)),
        _doubleTypeConverter(std::make_unique<DoubleTypeConverter>(context)),
        _int32TypeConverter(std::make_unique<Int32TypeConverter>(context)),
        _stringTypeConverter(std::make_unique<StringTypeConverter>(context)),
        _floatTypeConverter(std::make_unique<FloatTypeConverter>(context)),
        _int8TypeConverter(std::make_unique<Int8TypeConverter>(context)),
        _typeSpecificValueVisitor(std::make_unique<TypeSpecificValueVisitor>()),
        _codeGenerationContext(context), TheModule(context->getModule().get()),
        Builder(context->getBuilder().get()),
        TheContext(context->getContext().get()){};

  virtual llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) = 0;

  virtual llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BinderKindUtils::BoundBinaryOperatorKind binaryOp) = 0;

  virtual ~BinaryOperationStrategy() = default;
};

#endif // FLOWWING_BINARYOPERATIONSTRATEGY_H