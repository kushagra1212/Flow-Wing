// StructTypeBuilder.cpp
#include "StructTypeBuilder.h"

#include "../../context/CodeGenerationContext.h"

StructTypeBuilder::StructTypeBuilder(
    CodeGenerationContext *_codeGenerationContext)
    : TypeBuilderInterface(_codeGenerationContext) {

  _memberTypesForDynamicTypes = {
      llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getDoubleTy(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt1Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt8PtrTy(*_codeGenerationContext->getContext().get()),
  };
}

void StructTypeBuilder::buildType() {
  this->_dynamicType = llvm::StructType::create(
      *_codeGenerationContext->getContext().get(), "DynamicType");
  this->_dynamicType->setBody(_memberTypesForDynamicTypes);
}

llvm::StructType *StructTypeBuilder::get() const { return _dynamicType; }

const std::vector<llvm::Type *> &StructTypeBuilder::getMemberTypes() const {
  return _memberTypesForDynamicTypes;
}

const uint64_t StructTypeBuilder::getIndexofMemberType(llvm::Type *type) const {
  int index = -1;
  for (uint64_t i = 0; i < this->_memberTypesForDynamicTypes.size(); i++) {
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
