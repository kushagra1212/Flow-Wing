#include "NamedValueTable.h"

llvm::Value *NamedValueTable::getValue(const std::string &name) {
  if (namedValues.find(name) != namedValues.end()) {
    return namedValues[name];
  }
  return nullptr; // Not found
}

bool NamedValueTable::updateValue(const std::string &name, llvm::Value *value) {
  if (namedValues.find(name) != namedValues.end()) {
    namedValues[name] = value;
    return true; // Updated
  }
  return false; // Not found
}

void NamedValueTable::setValue(const std::string &name, llvm::Value *value) {
  namedValues[name] = value;
}