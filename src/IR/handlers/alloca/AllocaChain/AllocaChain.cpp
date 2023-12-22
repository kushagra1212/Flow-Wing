#include "AllocaChain.h"
void AllocaChain::addHandler(AllocaHandler *handler) { handlers.push(handler); }

void AllocaChain::removeHandler() { handlers.pop(); }

llvm::AllocaInst *AllocaChain::getAllocaInst(const std::string &name) {
  llvm::AllocaInst *alloca = nullptr;

  std::stack<AllocaHandler *> currentHandler;
  while (!handlers.empty()) {
    AllocaHandler *handler = handlers.top();
    alloca = handler->getAlloca(name);
    if (alloca) {
      break;
    }
    currentHandler.push(handler);
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(currentHandler.top());
    currentHandler.pop();
  }

  return alloca;
}

bool AllocaChain::updateAllocaInst(const std::string &name,
                                   llvm::AllocaInst *alloca) {
  bool updated = false;
  std::stack<AllocaHandler *> currentHandler;
  while (!handlers.empty()) {
    AllocaHandler *handler = handlers.top();
    if (handler->updateAlloca(name, alloca)) {
      updated = true;
      break;
    }
    currentHandler.push(handler);
    handlers.pop();
  }
  while (!currentHandler.empty()) {
    handlers.push(currentHandler.top());
    currentHandler.pop();
  }

  return updated; // Not found in the chain
}

void AllocaChain::setAllocaInst(const std::string &name,
                                llvm::AllocaInst *alloca) {
  if (!handlers.empty()) {
    AllocaHandler *handler = handlers.top();
    handler->setAlloca(name, alloca);
  }
}