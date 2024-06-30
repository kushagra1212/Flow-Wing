#ifndef _FLOW_WING_TYPE_H__
#define _FLOW_WING_TYPE_H__

#include "llvm/IR/Module.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

namespace FlowWing {
class Type {
  std::string name;
  llvm::Type *type;
  int64_t index = -1;
  BoundCustomTypeStatement *customType;

public:
  Type() = default;
  Type(const std::string &name, llvm::Type *type, int64_t index,
       BoundCustomTypeStatement *customType)
      : name(name), type(type), index(index), customType(customType) {
#ifdef DEBUG
    std::cout << "Type: " << name << " " << type << " " << index << " "
              << customType << std::endl;
#endif
  }

  const std::string &getName() const { return name; }
  llvm::Type *getType() const { return type; }

  llvm::StructType *getStructType() const {
    if (type && llvm::isa<llvm::StructType>(type)) {
      return llvm::cast<llvm::StructType>(type);
    }

    return nullptr;
  }
  int64_t getIndex() const { return index; }
  BoundCustomTypeStatement *getCustomType() const { return customType; }

  class TypeBuilder {
    std::string name;
    llvm::Type *type = nullptr;
    int64_t index = -1;
    BoundCustomTypeStatement *customType = nullptr;

  public:
    TypeBuilder &setName(const std::string &name) {
      this->name = name;
      return *this;
    }

    TypeBuilder &setType(llvm::Type *type) {
      this->type = type;
      return *this;
    }

    TypeBuilder &setIndex(int64_t index) {
      this->index = index;
      return *this;
    }

    TypeBuilder &setCustomType(BoundCustomTypeStatement *customType) {
      this->customType = customType;
      return *this;
    }

    Type build() { return Type(name, type, index, customType); }
  };
};

} // namespace FlowWing

#endif //_FLOW_WING_TYPE_H__
