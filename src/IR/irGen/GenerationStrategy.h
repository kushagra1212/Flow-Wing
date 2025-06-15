#ifndef __FLOWWING_GENERATION_STRATEGY_H__
#define __FLOWWING_GENERATION_STRATEGY_H__

#include "../../SemanticAnalyzer/BinderKindUtils.h"
#include "../../SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../syntax/SyntaxKindUtils.h"
#include "../LLVMTypeConversion/BoolTypeConverter/BoolTypeConverter.h"
#include "../LLVMTypeConversion/DoubleTypeConverter/DoubleTypeConverter.h"
#include "../LLVMTypeConversion/Int32TypeConverter/Int32TypeConverter.h"
#include "../LLVMTypeConversion/Int8TypeConverter/Int8TypeConverter.h"
#include "../LLVMTypeConversion/LLVMValueConverter/LLVMValueConverter.h"
#include "../LLVMTypeConversion/StringTypeConverter/StringTypeConverter.h"
#include "../LLVMTypeConversion/TypeSpecificValueVisitor.h"
#include "../context/CodeGenerationContext.h"
#include "../strategies/BinaryOperationStrategy/BoolBinaryOperationStrategy/BoolBinaryOperationStrategy.h"
#include "../strategies/BinaryOperationStrategy/ClassBinaryOperationStrategy/ClassBinaryOperationStrategy.h"
#include "../strategies/BinaryOperationStrategy/DoubleBinaryOperationStrategy/DoubleBinaryOperationStrategy.h"
#include "../strategies/BinaryOperationStrategy/FloatBinaryOperationStrategy/FloatBinaryOperationStrategy.h"
#include "../strategies/BinaryOperationStrategy/Int32BinaryOperationStrategy/Int32BinaryOperationStrategy.h"
#include "../strategies/BinaryOperationStrategy/NirastBinaryOperationStrategy/NirastBinaryOperationStrategy.h"
#include "../strategies/BinaryOperationStrategy/StringBinaryOperationStrategy/StringBinaryOperationStrategy.h"
#include "../strategies/UnaryOperationStrategy/UnaryOperationStrategy.h"
#include "LLVMTypeGeneration/LLVMTypeGenerationFactory.h"
#include "expressions/ExpressionGenerationFactory.h"
#include "statements/StatementGenerationFactory.h"

class GenerationStrategy {
public:
  GenerationStrategy(CodeGenerationContext *context)
      : _codeGenerationContext(context), TheModule(context->getModule().get()),
        Builder(context->getBuilder().get()),
        TheContext(context->getContext().get()),
        _llvmValueConverter(std::make_unique<LLVMValueConverter>(context)),

        // Initialize the expression generation factory

        // Initialize the unary operation strategies
        _unaryOperationStrategy(
            std::make_unique<UnaryOperationStrategy>(context)),

        // Initialize the binary operation strategies
        _int32BinaryOperationStrategy(
            std::make_unique<Int32BinaryOperationStrategy>(context)),
        _boolBinaryOperationStrategy(
            std::make_unique<BoolBinaryOperationStrategy>(context)),
        _doubleBinaryOperationStrategy(
            std::make_unique<DoubleBinaryOperationStrategy>(context)),
        _stringBinaryOperationStrategy(
            std::make_unique<StringBinaryOperationStrategy>(context)),
        _floatBinaryOperationStrategy(
            std::make_unique<FloatBinaryOperationStrategy>(context)),
        _nirastBinaryOperationStrategy(
            std::make_unique<NirastBinaryOperationStrategy>(context)),

        // Initialize the type converters
        _boolTypeConverter(std::make_unique<BoolTypeConverter>(context)),
        _doubleTypeConverter(std::make_unique<DoubleTypeConverter>(context)),
        _int32TypeConverter(std::make_unique<Int32TypeConverter>(context)),
        _int8TypeConverter(std::make_unique<Int8TypeConverter>(context)),
        _stringTypeConverter(std::make_unique<StringTypeConverter>(context)),
        _floatTypeConverter(std::make_unique<FloatTypeConverter>(context)),
        _classBinaryOperationStrategy(
            std::make_unique<ClassBinaryOperationStrategy>(context)),

        // Initialize the value visitor
        _typeSpecificValueVisitor(std::make_unique<TypeSpecificValueVisitor>()),

        _expressionGenerationFactory(
            std::make_unique<ExpressionGenerationFactory>(context)),
        _statementGenerationFactory(
            std::make_unique<StatementGenerationFactory>(context)),
        _typeGenerationFactory(
            std::make_unique<LLVMTypeGenerationFactory>(context)){};
  CodeGenerationContext *_codeGenerationContext;

  llvm::Module *TheModule = nullptr;
  llvm::IRBuilder<> *Builder = nullptr;
  llvm::LLVMContext *TheContext = nullptr;
  std::unique_ptr<LLVMValueConverter> _llvmValueConverter;

  // Value Visitor
  std::unique_ptr<TypeSpecificValueVisitor> _typeSpecificValueVisitor;

  // Binary Operation Strategy
  std::unique_ptr<Int32BinaryOperationStrategy> _int32BinaryOperationStrategy;
  std::unique_ptr<BoolBinaryOperationStrategy> _boolBinaryOperationStrategy;
  std::unique_ptr<DoubleBinaryOperationStrategy> _doubleBinaryOperationStrategy;
  std::unique_ptr<FloatBinaryOperationStrategy> _floatBinaryOperationStrategy;
  std::unique_ptr<StringBinaryOperationStrategy> _stringBinaryOperationStrategy;
  std::unique_ptr<NirastBinaryOperationStrategy> _nirastBinaryOperationStrategy;
  std::unique_ptr<ClassBinaryOperationStrategy> _classBinaryOperationStrategy;

  // Unary Operation Strategy
  std::unique_ptr<UnaryOperationStrategy> _unaryOperationStrategy;

  // Convertors

  std::unique_ptr<BoolTypeConverter> _boolTypeConverter;
  std::unique_ptr<DoubleTypeConverter> _doubleTypeConverter;
  std::unique_ptr<FloatTypeConverter> _floatTypeConverter;
  std::unique_ptr<Int8TypeConverter> _int8TypeConverter;
  std::unique_ptr<Int32TypeConverter> _int32TypeConverter;
  std::unique_ptr<StringTypeConverter> _stringTypeConverter;

  // Factories

  std::unique_ptr<ExpressionGenerationFactory> _expressionGenerationFactory;
  std::unique_ptr<StatementGenerationFactory> _statementGenerationFactory;
  std::unique_ptr<LLVMTypeGenerationFactory> _typeGenerationFactory;
};

#endif // __FLOWWING_GENERATION_STRATEGY_H__
