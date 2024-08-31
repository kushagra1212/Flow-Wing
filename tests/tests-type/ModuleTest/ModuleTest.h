#ifndef __MODULETEST_H__
#define __MODULETEST_H__

#include "../../helpers/handlers/FileHandler.h"
#include "../../helpers/handlers/IOHandler.h"

class ModuleTest : public ::testing::Test,
                   public FileHandler,
                   public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __MODULETEST_H__