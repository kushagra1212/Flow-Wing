#include "CustomTypeStatementChain.h"

BoundCustomTypeStatement *
CustomTypeStatementChain::getExpr(const std::string &name) {
  std::stack<std::unique_ptr<CustomTypeStatementTable>> currentHandler;
  BoundCustomTypeStatement *exp = nullptr;

  std::string typeName = name.substr(0, name.find('.'));
  while (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    exp = handler->getExp(typeName);
    if (exp) {
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return exp;
}

void CustomTypeStatementChain::setExpr(const std::string &name,
                                       BoundCustomTypeStatement *value) {
  if (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    handler->setExp(name, value);
  }
}

void CustomTypeStatementChain::setGlobalExpr(const std::string &name,
                                             BoundCustomTypeStatement *value) {
  std::stack<std::unique_ptr<CustomTypeStatementTable>> currentHandler;
  while (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  currentHandler.top()->setExp(name, value);

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }
}