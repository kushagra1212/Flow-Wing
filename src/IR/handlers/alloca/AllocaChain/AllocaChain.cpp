#include "AllocaChain.h"

AllocaChain::AllocaChain() { _globalTable = std::make_unique<AllocaTable>(); }

void AllocaChain::addHandler(AllocaTable *handler) { handlers.push(handler); }

void AllocaChain::removeHandler() { handlers.pop(); }

llvm::AllocaInst *AllocaChain::getAllocaInst(const std::string &name) {
  llvm::AllocaInst *alloca = nullptr;

  std::stack<AllocaTable *> currentHandler;
  while (!handlers.empty()) {
    AllocaTable *handler = handlers.top();
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
  std::stack<AllocaTable *> currentHandler;
  while (!handlers.empty()) {
    AllocaTable *handler = handlers.top();
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
    AllocaTable *handler = handlers.top();
    handler->setAlloca(name, alloca);
  }
}

void AllocaChain::setTypeIndex(const std::string &name, uint64_t index) {
  if (!handlers.empty()) {
    AllocaTable *handler = handlers.top();
    handler->setTypeIndex(name, index);
  }
}

uint64_t AllocaChain::getTypeIndex(const std::string &name) {
  uint64_t index = 0;
  std::stack<AllocaTable *> currentHandler;
  while (!handlers.empty()) {
    AllocaTable *handler = handlers.top();
    if (handler->hasTypeIndex(name)) {
      index = handler->getTypeIndex(name);
      break;
    }
    currentHandler.push(handler);
    handlers.pop();
  }
  while (!currentHandler.empty()) {
    handlers.push(currentHandler.top());
    currentHandler.pop();
  }

  return index;
}

bool AllocaChain::hasTypeIndex(const std::string &name) {
  bool hasIndex = false;
  std::stack<AllocaTable *> currentHandler;
  while (!handlers.empty()) {
    AllocaTable *handler = handlers.top();
    if (handler->hasTypeIndex(name)) {
      hasIndex = true;
      break;
    }
    currentHandler.push(handler);
    handlers.pop();
  }
  while (!currentHandler.empty()) {
    handlers.push(currentHandler.top());
    currentHandler.pop();
  }

  return hasIndex;
}

void AllocaChain::setGlobalTypeIndex(const std::string &name, uint64_t index) {
  _globalTable->setTypeIndex(name, index);
}

uint64_t AllocaChain::getGlobalTypeIndex(const std::string &name) {
  return _globalTable->getTypeIndex(name);
}