// ReferenceTypeBuilder.h
#ifndef __FLOWWING_REFERENCE_TYPE_BUILDER_H__
#define __FLOWWING_REFERENCE_TYPE_BUILDER_H__

#include "../TypeBuilderInterface.h"

class TypeBuilderInterface;

class ReferenceTypeBuilder : public TypeBuilderInterface {
 public:
  ReferenceTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;

  llvm::Type *getReferencedType() const;

  const bool isRef(llvm::Type *type) const;

  llvm::Value *getReferencedValue(llvm::Value *refValue) const;

  const std::vector<llvm::Type *> &getMemberTypes() const;

 private:
  llvm::StructType *_referenceType;
  std::vector<llvm::Type *> _memberTypes;
};

#endif  // __FLOWWING_REFERENCE_TYPE_BUILDER_H__