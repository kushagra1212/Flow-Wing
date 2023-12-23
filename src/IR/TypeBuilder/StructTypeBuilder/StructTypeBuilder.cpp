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

const bool StructTypeBuilder::isDyn(llvm::Type *type) const {
  return type == this->_dynamicType;
}

llvm::Value *StructTypeBuilder::getMemberValueofDynGlVar(
    llvm::Value *structValue, const std::string &variableName) const {

  // check if GlobalVariable (DynamicType)

  if (llvm::isa<llvm::GlobalVariable>(structValue)) {

    llvm::GlobalVariable *variable =
        llvm::cast<llvm::GlobalVariable>(structValue);

    llvm::Value *elementPtr =
        _codeGenerationContext->getBuilder()->CreateStructGEP(
            this->_dynamicType, variable,
            _codeGenerationContext->getGlobalTypeMap()[variableName]);

    return _codeGenerationContext->getBuilder()->CreateLoad(
        this->getMemberTypeofDynGlVar(variableName), elementPtr);
  }
  _codeGenerationContext->getLogger()->LogError("value is not a "
                                                "GlobalVariable");

  return nullptr;
}

llvm::Value *
StructTypeBuilder::getMemberValueOfDynlcVar(llvm::AllocaInst *v,
                                            llvm::Value *variableValue) const {

  return _codeGenerationContext->getBuilder()->CreateLoad(
      variableValue->getType(),
      _codeGenerationContext->getBuilder()->CreateStructGEP(
          _codeGenerationContext->getDynamicType()->get(), v,
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              variableValue->getType())));
}

llvm::Type *StructTypeBuilder::getMemberTypeofDynGlVar(
    const std::string &variableName) const {

  return this->getMemberTypes()[_codeGenerationContext
                                    ->getGlobalTypeMap()[variableName]];
}