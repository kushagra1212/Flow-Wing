#ifndef FLOWWING_ALLOCATABLE_H
#define FLOWWING_ALLOCATABLE_H

#include "../../../../Common.h"
#include "../AllocaHandler.h"
#include "../AllocaIndexHandler.h"

class AllocaTable : public AllocaHandler, public AllocaIndexHandler {
private:
  std::map<std::string, llvm::AllocaInst *> _allocas;

  std::map<std::string, std::pair<llvm::Value *, llvm::Type *>> _ptrs;
  std::unordered_map<std::string, uint64_t> _typeMap;

public:
  llvm::AllocaInst *getAlloca(const std::string &name) override;
  bool updateAlloca(const std::string &name, llvm::AllocaInst *alloca) override;
  void setAlloca(const std::string &name, llvm::AllocaInst *alloca) override;

  void setTypeIndex(const std::string &name, uint64_t index) override;
  uint64_t getTypeIndex(const std::string &name) override;
  bool hasTypeIndex(const std::string &name) override;

  std::pair<llvm::Value *, llvm::Type *> getPtr(const std::string &name);
  bool updatePtr(const std::string &name,
                 std::pair<llvm::Value *, llvm::Type *> ptr);
  void setPtr(const std::string &name,
              std::pair<llvm::Value *, llvm::Type *> ptr);
};

#endif // FLOWWING_ALLOCATABLE_H