// StructTypeBuilder.h
#ifndef __FLOWWING_STRUCT_TYPE_BUILDER_H__
#define __FLOWWING_STRUCT_TYPE_BUILDER_H__

#include "../../../IR/constants/FlowWingUtilsConstants.h"
#include "../ReferenceTypeBuilder/ReferenceTypeBuilder.h"
#include "../TypeBuilderInterface.h"

class StructTypeBuilder : public TypeBuilderInterface {
public:
  StructTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;
  const std::vector<llvm::Type *> &getMemberTypes() const;

  const uint64_t getMemberTypeofDynVar(llvm::Type *type) const;

  const bool isDyn(llvm::Type *type) const;

  const bool isGlobalVar(const std::string &varName) const;

  llvm::Value *getMemberValueOfDynVar(llvm::Value *v,
                                      const std::string &varName) const;

  llvm::Value *setMemberValueOfDynVar(llvm::Value *v, llvm::Value *value,
                                      llvm::Type *variableType,
                                      const std::string &variableName) const;

private:
  llvm::StructType *_dynamicType;
  std::vector<llvm::Type *> _memberTypesForDynamicTypes;
  llvm::LLVMContext *_context;
};

#endif // __FLOWWING_STRUCT_TYPE_BUILDER_H__
