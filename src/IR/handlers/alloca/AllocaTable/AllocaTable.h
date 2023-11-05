#ifndef FLOWWING_ALLOCATABLE_H
#define FLOWWING_ALLOCATABLE_H

#include "../../../../Common.h"
#include "../AllocaHandler.h"

class AllocaTable : public AllocaHandler {
private:
  std::map<std::string, llvm::AllocaInst *> _allocas;

public:
  llvm::AllocaInst *getAlloca(const std::string &name) override;
  bool updateAlloca(const std::string &name, llvm::AllocaInst *alloca) override;
  void setAlloca(const std::string &name, llvm::AllocaInst *alloca) override;
};

#endif // FLOWWING_ALLOCATABLE_H