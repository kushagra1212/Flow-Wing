#ifndef FLOWWING_UNARYOPERATIONSTRATEGY_H
#define FLOWWING_UNARYOPERATIONSTRATEGY_H

#include "../../../Common.h"
#include "../../../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../../LLVMTypeConversion/BoolTypeConverter/BoolTypeConverter.h"
#include "../../LLVMTypeConversion/DoubleTypeConverter/DoubleTypeConverter.h"
#include "../../LLVMTypeConversion/Int32TypeConverter/Int32TypeConverter.h"
#include "../../LLVMTypeConversion/StringTypeConverter/StringTypeConverter.h"
#include "../../LLVMTypeConversion/TypeSpecificValueVisitor.h"
#include "llvm/IR/Value.h"

class UnaryOperationStrategy {
public:
  std::unique_ptr<BoolTypeConverter> _boolTypeConverter;
  std::unique_ptr<DoubleTypeConverter> _doubleTypeConverter;
  std::unique_ptr<Int32TypeConverter> _int32TypeConverter;
  std::unique_ptr<StringTypeConverter> _stringTypeConverter;
  std::unique_ptr<TypeSpecificValueVisitor> _typeSpecificValueVisitor;

  CodeGenerationContext *_codeGenerationContext;

  llvm::Module *TheModule = nullptr;
  llvm::IRBuilder<> *Builder = nullptr;
  llvm::LLVMContext *TheContext = nullptr;

  UnaryOperationStrategy(CodeGenerationContext *context)
      : _boolTypeConverter(std::make_unique<BoolTypeConverter>(context)),
        _doubleTypeConverter(std::make_unique<DoubleTypeConverter>(context)),
        _int32TypeConverter(std::make_unique<Int32TypeConverter>(context)),
        _stringTypeConverter(std::make_unique<StringTypeConverter>(context)),
        _typeSpecificValueVisitor(std::make_unique<TypeSpecificValueVisitor>()),
        _codeGenerationContext(context), TheModule(context->getModule().get()),
        Builder(context->getBuilder().get()),
        TheContext(context->getContext().get()){};

  llvm::Value *performOperation(llvm::Value *val,
                                BoundUnaryExpression *unaryExpression);
};

#endif // FLOWWING_BINARYOPERATIONSTRATEGY_H