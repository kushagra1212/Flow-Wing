#ifndef __GLOBAL_TYPE_CONVERTER_H__
#define __GLOBAL_TYPE_CONVERTER_H__

#include "../../context/CodeGenerationContext.h"
#include "../StringTypeConverter/StringTypeConverter.h"
#include "../TypeConverterBase.h"

class GStringTypeConverter : public TypeConverterBase {
 public:
  GStringTypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *value) override;
  llvm::Value *convertImplicit(llvm::Value *value) override;
};

#endif  // __GLOBAL_TYPE_CONVERTER_H__
