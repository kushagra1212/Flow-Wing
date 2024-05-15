#ifndef FLOWWING_VALUECHAIN_H
#define FLOWWING_VALUECHAIN_H

#include "../../../../Common.h"
#include "../ValueHandler.h"

class ValueChain {
private:
  std::stack<ValueHandler *> handlers;

public:
  void addHandler(ValueHandler *handler);

  void removeHandler();

  // llvm::Value *getNamedValue(const std::string &name);

  bool updateNamedValue(const std::string &name, llvm::Value *value);

  // void setNamedValue(const std::string &name, llvm::Value *value);
};

#endif // FLOWWING_VALUECHAIN_H