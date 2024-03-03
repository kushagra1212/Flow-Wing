#ifndef __INT_TYPE_CONVERTER_H__
#define __INT_TYPE_CONVERTER_H__

#include "../TypeConverterBase.h"

class Int32TypeConverter : public TypeConverterBase {
 public:
  Int32TypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *value) override;
  llvm::Value *convertImplicit(llvm::Value *value) override;
};

#endif  // __INT_TYPE_CONVERTER_H__
