#include "AllocaTable.h"

llvm::AllocaInst *AllocaTable::getAlloca(const std::string &name) {
  if (_allocas.find(name) != _allocas.end()) {
    return _allocas[name];
  }
  return nullptr; // Not found
}

bool AllocaTable::updateAlloca(const std::string &name,
                               llvm::AllocaInst *alloca) {
  if (_allocas.find(name) != _allocas.end()) {
    _allocas[name] = alloca;
    return true; // Updated
  }
  return false; // Not found
}

void AllocaTable::setAlloca(const std::string &name, llvm::AllocaInst *alloca) {
  _allocas[name] = alloca;
}

void AllocaTable::setTypeIndex(const std::string &name, uint64_t index) {
  _typeMap[name] = index;
}
uint64_t AllocaTable::getTypeIndex(const std::string &name) {
  return _typeMap[name];
}

bool AllocaTable::hasTypeIndex(const std::string &name) {
  return _typeMap.find(name) != _typeMap.end();
}