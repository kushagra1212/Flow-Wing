#include "ValueChain.h"

void ValueChain::addHandler(ValueHandler *handler) { handlers.push(handler); }

llvm::Value *ValueChain::getNamedValue(const std::string &name) {
  llvm::Value *value = nullptr;

  std::stack<ValueHandler *> currentHandler;
  while (!handlers.empty()) {
    ValueHandler *handler = handlers.top();
    value = handler->getValue(name);
    if (value) {
      break;
    }
    currentHandler.push(handler);
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(currentHandler.top());
    currentHandler.pop();
  }

  return value;
}

bool ValueChain::updateNamedValue(const std::string &name, llvm::Value *value) {
  bool updated = false;
  std::stack<ValueHandler *> currentHandler;
  while (!handlers.empty()) {
    ValueHandler *handler = handlers.top();
    if (handler->updateValue(name, value)) {
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

void ValueChain::setNamedValue(const std::string &name, llvm::Value *value) {
  if (!handlers.empty()) {
    ValueHandler *handler = handlers.top();
    handler->setValue(name, value);
  }
}

void ValueChain::removeHandler() { handlers.pop(); }