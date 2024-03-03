#ifndef FLOWWING_ALLOCINDEXAHANDLER_H
#define FLOWWING_ALLOCINDEXAHANDLER_H

#include "../../../Common.h"

class AllocaIndexHandler {
 public:
  virtual void setTypeIndex(const std::string &name, uint64_t index) = 0;
  virtual uint64_t getTypeIndex(const std::string &name) = 0;
  virtual bool hasTypeIndex(const std::string &name) = 0;
};

#endif  // FLOWWING_ALLOCINDEXAHANDLER_H