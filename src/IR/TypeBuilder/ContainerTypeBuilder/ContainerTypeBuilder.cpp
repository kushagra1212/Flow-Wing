// ContainerTypeBuilder.cpp
#include "ContainerTypeBuilder.h"

#include "../../context/CodeGenerationContext.h"

ContainerTypeBuilder::ContainerTypeBuilder(
    CodeGenerationContext *_codeGenerationContext)
    : TypeBuilderInterface(_codeGenerationContext) {

  _body = {
      llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getDoubleTy(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt1Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt8PtrTy(*_codeGenerationContext->getContext().get()),
  };
}

void ContainerTypeBuilder::buildType() {
  this->_dynamicType = llvm::StructType::create(
      *_codeGenerationContext->getContext().get(), "DynamicTypeContainer");
  this->_dynamicType->setBody(_body);
}

llvm::StructType *ContainerTypeBuilder::get() const { return _dynamicType; }

const std::vector<llvm::Type *> &ContainerTypeBuilder::getMemberTypes() const {
  return _body;
}

const uint64_t
ContainerTypeBuilder::getIndexofMemberType(llvm::Type *type) const {
  int index = -1;
  for (uint64_t i = 0; i < this->_body.size(); i++) {
    if (this->_body[i] == type) {
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
