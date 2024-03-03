#ifndef __BOOL_TYPE_CONVERTER_H__
#define __BOOL_TYPE_CONVERTER_H__
#include "../StringTypeConverter/StringTypeConverter.h"
#include "../TypeConverterBase.h"

class BoolTypeConverter : public TypeConverterBase {
 public:
  BoolTypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *value) override;
  llvm::Value *convertImplicit(llvm::Value *value) override;
};

#endif  // __BOOL_TYPE_CONVERTER_H__
