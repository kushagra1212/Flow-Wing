#ifndef __FLOAT_TYPE_CONVERTER_H__
#define __FLOAT_TYPE_CONVERTER_H__

#include "../TypeConverterBase.h"

class FloatTypeConverter : public TypeConverterBase {
public:
  FloatTypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *&value) override;
  llvm::Value *convertImplicit(llvm::Value *&value) override;
};

#endif // __FLOAT_TYPE_CONVERTER_H__
