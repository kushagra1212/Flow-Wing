// ContainerTypeBuilder.h
#ifndef __FLOWWING_CONTAINER_TYPE_BUILDER_H__
#define __FLOWWING_CONTAINER_TYPE_BUILDER_H__

#include "../TypeBuilderInterface.h"

class ContainerTypeBuilder : public TypeBuilderInterface {
public:
  ContainerTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;
  const std::vector<llvm::Type *> &getMemberTypes() const;

  const uint64_t getIndexofMemberType(llvm::Type *type) const;

private:
  llvm::StructType *_dynamicType;
  std::vector<llvm::Type *> _body;
};

#endif // __FLOWWING_CONTAINER_TYPE_BUILDER_H__
