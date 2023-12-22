#ifndef FLOWWING_VALUEHANDLER_H
#define FLOWWING_VALUEHANDLER_H

#include "../../../Common.h"
#include <llvm/IR/Value.h>

class ValueHandler {
public:
  virtual llvm::Value *getValue(const std::string &name) = 0;
  virtual bool updateValue(const std::string &name, llvm::Value *value) = 0;
  virtual void setValue(const std::string &name, llvm::Value *value) = 0;
};

#endif // FLOWWING_VALUEHANDLER_H