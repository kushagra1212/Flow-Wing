#ifndef FLOWWING_ALLOCACHAIN_H
#define FLOWWING_ALLOCACHAIN_H

#include "../../../../common/Common.h"
#include "../AllocaTable/AllocaTable.h"

class AllocaChain {
private:
  std::stack<std::unique_ptr<AllocaTable>> handlers;
  std::unique_ptr<AllocaTable> _globalTable;

public:
  AllocaChain();
  void addHandler(std::unique_ptr<AllocaTable> handler);

  void removeHandler();

  llvm::AllocaInst *getAllocaInst(const std::string &name);

  bool updateAllocaInst(const std::string &name, llvm::AllocaInst *value);

  void setAllocaInst(const std::string &name, llvm::AllocaInst *value);

  void setTypeIndex(const std::string &name, uint64_t index);
  uint64_t getTypeIndex(const std::string &name);

  bool hasTypeIndex(const std::string &name);

  void setGlobalTypeIndex(const std::string &name, uint64_t index);
  uint64_t getGlobalTypeIndex(const std::string &name);
  std::pair<llvm::Value *, llvm::Type *> getPtr(const std::string name);

  bool updatePtr(const std::string &name,
                 std::pair<llvm::Value *, llvm::Type *> ptr);

  void setPtr(const std::string &name,
              std::pair<llvm::Value *, llvm::Type *> ptr);
};

#endif // FLOWWING_ALLOCACHAIN_H