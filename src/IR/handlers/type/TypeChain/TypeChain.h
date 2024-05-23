#ifndef FLOWWING_TYPE_CHAIN_H
#define FLOWWING_TYPE_CHAIN_H

#include "../../../../Common.h"
#include "../TypeTable/TypeTable.h"

class TypeChain {
private:
  std::stack<std::unique_ptr<TypeTable>> handlers;

public:
  void addHandler(std::unique_ptr<TypeTable> handler);

  void removeHandler();

  llvm::StructType *getType(const std::string &name,
                            std::string typeNameFromClass);
  bool updateType(const std::string &name, llvm::StructType *typeValue);
  void setType(const std::string &name, llvm::StructType *typeValue);

  size_t getIndex(const std::string &name);
  void setIndex(const std::string &name, size_t index);

  // Global

  void setGlobalType(const std::string &name, llvm::StructType *typeValue);
  void setGlobalIndex(const std::string &name, size_t index);
};

#endif // FLOWWING_TYPE_CHAIN_H