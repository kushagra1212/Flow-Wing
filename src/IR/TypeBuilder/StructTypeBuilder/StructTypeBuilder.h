// StructTypeBuilder.h
#ifndef __FLOWWING_STRUCT_TYPE_BUILDER_H__
#define __FLOWWING_STRUCT_TYPE_BUILDER_H__

#include "../TypeBuilderInterface.h"

class StructTypeBuilder : public TypeBuilderInterface {
public:
  StructTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;
  const std::vector<llvm::Type *> &getMemberTypes() const;

  const int getIndexofMemberType(llvm::Type *type) const;

private:
  llvm::StructType *_dynamicType;
  std::vector<llvm::Type *> _memberTypesForDynamicTypes;
};

#endif // __FLOWWING_STRUCT_TYPE_BUILDER_H__
