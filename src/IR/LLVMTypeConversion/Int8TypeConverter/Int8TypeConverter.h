#pragma once

#include "../TypeConverterBase.h"

class Int8TypeConverter : public TypeConverterBase {
public:
  Int8TypeConverter(CodeGenerationContext *context);

  llvm::Value *convertExplicit(llvm::Value *&value) override;
  llvm::Value *convertImplicit(llvm::Value *&value) override;
};
