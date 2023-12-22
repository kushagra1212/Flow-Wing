// StructTypeBuilder.h
#ifndef __FLOWWING_STRUCT_TYPE_BUILDER_H__
#define __FLOWWING_STRUCT_TYPE_BUILDER_H__

#include "../TypeBuilderInterface.h"
#include "llvm/IR/Instructions.h"

class StructTypeBuilder : public TypeBuilderInterface {
public:
  StructTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;
  const std::vector<llvm::Type *> &getMemberTypes() const;

  const uint64_t getIndexofMemberType(llvm::Type *type) const;

  const bool isDyn(llvm::Type *type) const;

  llvm::Value *getMemberValueofDynGlVar(llvm::Value *structValue,
                                        const std::string &variableName) const;

  llvm::Value *getMemberValueOfDynlcVar(llvm::AllocaInst *v,
                                        llvm::Value *variableValue) const;

private:
  llvm::StructType *_dynamicType;
  std::vector<llvm::Type *> _memberTypesForDynamicTypes;
};

#endif // __FLOWWING_STRUCT_TYPE_BUILDER_H__
