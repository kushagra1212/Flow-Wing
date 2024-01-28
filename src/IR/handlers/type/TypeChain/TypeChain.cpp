#include "TypeChain.h"

void TypeChain::addHandler(std::unique_ptr<TypeTable> handler) {
  handlers.push(std::move(handler));
}

void TypeChain::removeHandler() { handlers.pop(); }

llvm::StructType *TypeChain::getType(const std::string &name) {
  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  llvm::StructType *typeValue = nullptr;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    typeValue = handler->getType(name);
    if (typeValue) {
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return typeValue;
}

bool TypeChain::updateType(const std::string &name,
                           llvm::StructType *typeValue) {
  bool updated = false;
  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    if (handler->updateType(name, std::move(typeValue))) {
      updated = true;
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }
  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return updated;  // Not found in the chain
}

void TypeChain::setType(const std::string &name, llvm::StructType *typeValue) {
  if (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    handler->setType(name, typeValue);
  }
}

size_t TypeChain::getIndex(const std::string &name) {
  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  size_t index = -1;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    index = handler->getIndex(name);
    if (index != -1) {
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return index;
}
void TypeChain::setIndex(const std::string &name, size_t index) {
  if (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    handler->setIndex(name, index);
  }
}

llvm::Type *TypeChain::getElementType(const std::string &name) {
  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  llvm::Type *type = nullptr;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    type = handler->getElementType(name);
    if (type) {
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return type;
}
void TypeChain::setElementType(const std::string &name, llvm::Type *type) {
  if (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    handler->setElementType(name, type);
  }
}