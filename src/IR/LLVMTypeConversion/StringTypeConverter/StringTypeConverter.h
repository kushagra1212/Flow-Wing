#ifndef __STRING_TYPE_CONVERTER_H__
#define __STRING_TYPE_CONVERTER_H__

#include "../GlobalTypeConverter/GStringTypeConverter.h"
#include "../TypeConverterBase.h"

class StringTypeConverter : public TypeConverterBase {

public:
  StringTypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *value) override;
  llvm::Value *convertImplicit(llvm::Value *value) override;
};

#endif // __STRING_TYPE_CONVERTER_H__
