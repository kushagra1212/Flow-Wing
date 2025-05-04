#ifndef FILESAVESTRATEGY_H
#define FILESAVESTRATEGY_H

#include "../../logger/LLVMLogger.h"
#include <llvm/Support/FileSystem.h>
#include <string>
template <typename ContentType, typename LoggerType> class FileSaveStrategy {
public:
  LoggerType logger = nullptr;
  virtual bool saveToFile(const std::string &path,
                          ContentType content) const = 0;
};

#endif // FILESAVESTRATEGY_H
