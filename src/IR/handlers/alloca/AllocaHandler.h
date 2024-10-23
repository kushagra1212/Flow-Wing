#ifndef FLOWWING_ALLOCAHANDLER_H
#define FLOWWING_ALLOCAHANDLER_H

#include "../../../common/Common.h"
#include "llvm/IR/Instructions.h"

class AllocaHandler {
public:
  virtual llvm::AllocaInst *getAlloca(const std::string &name) = 0;
  virtual bool updateAlloca(const std::string &name,
                            llvm::AllocaInst *alloca) = 0;
  virtual void setAlloca(const std::string &name, llvm::AllocaInst *alloca) = 0;
};

#endif // FLOWWING_ALLOCAHANDLER_H