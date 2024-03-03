#ifndef FLOWWING_ALLOCATABLE_H
#define FLOWWING_ALLOCATABLE_H

#include "../../../../Common.h"
#include "../AllocaHandler.h"
#include "../AllocaIndexHandler.h"

class AllocaTable : public AllocaHandler, public AllocaIndexHandler {
 private:
  std::map<std::string, llvm::AllocaInst *> _allocas;
  std::unordered_map<std::string, uint64_t> _typeMap;

 public:
  llvm::AllocaInst *getAlloca(const std::string &name) override;
  bool updateAlloca(const std::string &name, llvm::AllocaInst *alloca) override;
  void setAlloca(const std::string &name, llvm::AllocaInst *alloca) override;

  void setTypeIndex(const std::string &name, uint64_t index) override;
  uint64_t getTypeIndex(const std::string &name) override;
  bool hasTypeIndex(const std::string &name) override;
};

#endif  // FLOWWING_ALLOCATABLE_H