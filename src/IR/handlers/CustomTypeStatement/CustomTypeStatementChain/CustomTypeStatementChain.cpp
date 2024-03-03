#include "CustomTypeStatementChain.h"

BoundCustomTypeStatement *CustomTypeStatementChain::getExpr(
    const std::string &name) {
  std::stack<std::unique_ptr<CustomTypeStatementTable>> currentHandler;
  BoundCustomTypeStatement *exp = nullptr;
  while (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    exp = handler->getExp(name);
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