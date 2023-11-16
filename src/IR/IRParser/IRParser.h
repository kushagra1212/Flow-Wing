#ifndef IR_PARSER_H
#define IR_PARSER_H

#include "../../Common.h"
#include "llvm/IR/AssemblyAnnotationWriter.h"
#include <llvm/IR/Module.h>

class IRParser {

public:
  IRParser();
  void mergeIR(const std::string &ir);
  void mergeIR(llvm::Module *module);

  const std::string &getIR() const;
  std::string getIR(llvm::Module *module);
  void removeDuplicates();
  std::string removeDuplicatesStartWithAndEndWith(const std::string &startWith,
                                                  const std::string &endWith);

  void printIR();

private:
  std::string _ir;
};

#endif // IR_PARSER_H
