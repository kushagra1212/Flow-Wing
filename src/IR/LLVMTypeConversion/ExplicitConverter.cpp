#include "ExplicitConverter.h"

namespace FlowWing {

namespace EXPLICIT_CONVERTER {
llvm::Value *explicitConvertLLVMValueTo(llvm::Value *value, llvm::Type *type,
                                        CodeGenerationContext *context) {
  std::unique_ptr<GenerationStrategy> generationStrategy =
      std::make_unique<GenerationStrategy>(context);

  TypeMapper *_typeMapper = context->getMapper().get();

  if (_typeMapper->isStringType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_stringTypeConverter.get(), value);
  } else if (_typeMapper->isInt32Type(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_int32TypeConverter.get(), value);
  } else if (_typeMapper->isInt8Type(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_int8TypeConverter.get(), value);
  } else if (_typeMapper->isDoubleType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_doubleTypeConverter.get(), value);
  } else if (_typeMapper->isFloatType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_floatTypeConverter.get(), value);
  } else if (_typeMapper->isBoolType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_boolTypeConverter.get(), value);
  }

  return value;
}
} // namespace EXPLICIT_CONVERTER

} // namespace FlowWing