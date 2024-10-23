#ifndef FLOWWING_TYPE_TABLE_H
#define FLOWWING_TYPE_TABLE_H

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>

#include "../../../../common/Common.h"

class TypeTable {
private:
  std::unordered_map<std::string, llvm::StructType *> _type_map;
  std::unordered_map<std::string, size_t> _key_index_map;
  std::unordered_map<std::string, llvm::Type *> _element_map;

public:
  llvm::StructType *getType(const std::string &name);
  bool updateType(const std::string &name, llvm::StructType *type);
  void setType(const std::string &name, llvm::StructType *type);

  inline size_t getIndex(const std::string &name) {
    if (_key_index_map.find(name) != _key_index_map.end()) {
      return _key_index_map[name];
    }
    return -1; // Not found
  }

  inline void setIndex(const std::string &name, size_t value) {
    _key_index_map[name] = value;
  }

  inline llvm::Type *getElementType(const std::string &name) {
    if (_element_map.find(name) != _element_map.end()) {
      return _element_map[name];
    }
    return nullptr; // Not found
  }

  inline void setElementType(const std::string &name, llvm::Type *value) {
    _element_map[name] = value;
  }
};

#endif // FLOWWING_TYPE_TABLE_H