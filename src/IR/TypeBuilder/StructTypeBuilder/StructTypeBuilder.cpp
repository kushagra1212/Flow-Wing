// StructTypeBuilder.cpp
#include "StructTypeBuilder.h"

#include "../../context/CodeGenerationContext.h"

StructTypeBuilder::StructTypeBuilder(
    CodeGenerationContext *_codeGenerationContext)
    : TypeBuilderInterface(_codeGenerationContext) {
  _context = _codeGenerationContext->getContext().get();
  _memberTypesForDynamicTypes = {
      llvm::Type::getInt32Ty(*_context),
      llvm::Type::getDoubleTy(*_context),
      llvm::Type::getInt1Ty(*_context),
      llvm::Type::getInt8PtrTy(*_context),
  };
}

void StructTypeBuilder::buildType() {
  this->_dynamicType = llvm::StructType::create(*_context, "DynamicType");
  this->_dynamicType->setBody(_memberTypesForDynamicTypes);
}

llvm::StructType *StructTypeBuilder::get() const { return _dynamicType; }

const std::vector<llvm::Type *> &StructTypeBuilder::getMemberTypes() const {
  return _memberTypesForDynamicTypes;
}

const uint64_t
StructTypeBuilder::getMemberTypeofDynVar(llvm::Type *type) const {
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

llvm::Value *StructTypeBuilder::getMemberValueOfDynVar(
    llvm::Value *v, const std::string &variableName) const {

  uint64_t index = 0;

  if (isGlobalVar(variableName)) {
    index = _codeGenerationContext->getAllocaChain()->getGlobalTypeIndex(
        variableName);
  } else {
    index =
        _codeGenerationContext->getAllocaChain()->getTypeIndex(variableName);
  }

  llvm::Value *elementPtr =
      _codeGenerationContext->getBuilder()->CreateStructGEP(this->_dynamicType,
                                                            v, index);

  return _codeGenerationContext->getBuilder()->CreateLoad(
      this->getMemberTypes()[index], elementPtr);
}

llvm::Value *StructTypeBuilder::setMemberValueOfDynVar(
    llvm::Value *v, llvm::Value *value, llvm::Type *variableType,
    const std::string &variableName) const {

  uint64_t index = this->getMemberTypeofDynVar(variableType);

  if (isGlobalVar(variableName)) {
    _codeGenerationContext->getAllocaChain()->setGlobalTypeIndex(variableName,
                                                                 index);
  } else {
    _codeGenerationContext->getAllocaChain()->setTypeIndex(variableName, index);
  }

  llvm::Value *elementPtr =
      _codeGenerationContext->getBuilder()->CreateStructGEP(this->_dynamicType,
                                                            v, index);

  return _codeGenerationContext->getBuilder()->CreateStore(value, elementPtr);
}

const bool StructTypeBuilder::isGlobalVar(const std::string &varName) const {
  return varName.find(FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX) == 0;
}