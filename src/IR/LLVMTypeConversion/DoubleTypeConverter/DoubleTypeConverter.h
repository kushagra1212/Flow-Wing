#ifndef __DOUBLE_TYPE_CONVERTER_H__
#define __DOUBLE_TYPE_CONVERTER_H__

#include "../TypeConverterBase.h"

class DoubleTypeConverter : public TypeConverterBase {
 public:
  DoubleTypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *value) override;
  llvm::Value *convertImplicit(llvm::Value *value) override;
};

#endif  // __DOUBLE_TYPE_CONVERTER_H__
