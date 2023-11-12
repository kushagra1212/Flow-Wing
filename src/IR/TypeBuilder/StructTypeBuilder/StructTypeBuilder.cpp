// StructTypeBuilder.cpp
#include "StructTypeBuilder.h"

#include "../../context/CodeGenerationContext.h"

StructTypeBuilder::StructTypeBuilder(
    CodeGenerationContext *_codeGenerationContext)
    : TypeBuilderInterface(_codeGenerationContext) {}

void StructTypeBuilder::buildType() {
  this->_dynamicType = llvm::StructType::create(
      *_codeGenerationContext->getContext().get(), "DynamicType");
  this->_dynamicType->setBody(_memberTypesForDynamicTypes);
}

llvm::StructType *StructTypeBuilder::get() const { return _dynamicType; }

const std::vector<llvm::Type *> &StructTypeBuilder::getMemberTypes() const {
  return _memberTypesForDynamicTypes;
}

const int StructTypeBuilder::getIndexofMemberType(llvm::Type *type) const {
  int index = -1;
  for (int i = 0; i < this->_memberTypesForDynamicTypes.size(); i++) {
    if (this->_memberTypesForDynamicTypes[i] == type) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    std::string typeUsedByUser =
        _codeGenerationContext->getMapper()->getLLVMTypeName(type);

    _codeGenerationContext->getLogger()->LogError(
        "Unsupported type for dynamic type: " + typeUsedByUser);

    index = 0;
  }

  return index;
}
