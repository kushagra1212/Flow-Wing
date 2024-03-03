#include "TypeTable.h"

llvm::StructType *TypeTable::getType(const std::string &name) {
  if (_type_map.find(name) != _type_map.end()) {
    return _type_map[name];
  }
  return nullptr;  // Not found
}

bool TypeTable::updateType(const std::string &name,
                           llvm::StructType *typeValue) {
  if (_type_map.find(name) != _type_map.end()) {
    _type_map[name] = typeValue;
    return true;  // Updated
  }
  return false;  // Not found
}
void TypeTable::setType(const std::string &name, llvm::StructType *typeValue) {
  _type_map[name] = typeValue;
}
