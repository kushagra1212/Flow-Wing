#include "ReferenceTypeBuilder.h"

#include "../../context/CodeGenerationContext.h"

ReferenceTypeBuilder::ReferenceTypeBuilder(CodeGenerationContext *context)
    : TypeBuilderInterface(context) {
  _memberTypes = {
      llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get()),
  };
}

void ReferenceTypeBuilder::buildType() {
  this->_referenceType = llvm::StructType::create(
      *_codeGenerationContext->getContext().get(), "referenceType");

  this->_referenceType->setBody(_memberTypes);
}

llvm::StructType *ReferenceTypeBuilder::get() const { return _referenceType; }

llvm::Type *ReferenceTypeBuilder::getReferencedType() const {
  return llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get());
}

const bool ReferenceTypeBuilder::isRef(llvm::Type *type) const {
  return type == this->_referenceType;
}

llvm::Value *
ReferenceTypeBuilder::getReferencedValue(llvm::Value *refValue) const {
  return _codeGenerationContext->getBuilder()->CreateStructGEP(
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          Utils::type::INT32),
      refValue, 0);
}

const std::vector<llvm::Type *> &ReferenceTypeBuilder::getMemberTypes() const {
  return _memberTypes;
}
