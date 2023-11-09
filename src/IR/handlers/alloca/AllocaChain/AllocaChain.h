#ifndef FLOWWING_ALLOCACHAIN_H
#define FLOWWING_ALLOCACHAIN_H

#include "../../../../Common.h"
#include "../AllocaHandler.h"

class AllocaChain {
private:
  std::stack<AllocaHandler *> handlers;

public:
  void addHandler(AllocaHandler *handler);

  void removeHandler();

  llvm::AllocaInst *getAllocaInst(const std::string &name);

  bool updateAllocaInst(const std::string &name, llvm::AllocaInst *value);

  void setAllocaInst(const std::string &name, llvm::AllocaInst *value);
};

#endif // FLOWWING_ALLOCACHAIN_H