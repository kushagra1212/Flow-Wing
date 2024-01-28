#ifndef FLOWWING_OBJECT_TYPE_CHAIN_H
#define FLOWWING_OBJECT_TYPE_CHAIN_H

#include "../../../../Common.h"
#include "../CustomTypeStatementTable/CustomTypeStatementTable.h"

class CustomTypeStatementChain {
 private:
  std::stack<std::unique_ptr<CustomTypeStatementTable>> handlers;

 public:
  inline void addHandler(std::unique_ptr<CustomTypeStatementTable> handler) {
    handlers.push(std::move(handler));
  }

  inline void removeHandler() {
    if (!handlers.empty()) handlers.pop();
  }

  BoundCustomTypeStatement *getExpr(const std::string &name);
  void setExpr(const std::string &name, BoundCustomTypeStatement *value);
};

#endif  // FLOWWING_OBJECT_TYPE_CHAIN_H