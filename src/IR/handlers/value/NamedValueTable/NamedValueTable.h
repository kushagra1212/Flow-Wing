#ifndef FLOWWING_NAMEDVALUETABLE_H
#define FLOWWING_NAMEDVALUETABLE_H

#include "../../../../Common.h"
#include "../ValueHandler.h"

class NamedValueTable : public ValueHandler {
 private:
  std::map<std::string, llvm::Value *> namedValues;

 public:
  llvm::Value *getValue(const std::string &name) override;
  bool updateValue(const std::string &name, llvm::Value *value) override;
  void setValue(const std::string &name, llvm::Value *value) override;
};

#endif  // FLOWWING_NAMEDVALUETABLE_H