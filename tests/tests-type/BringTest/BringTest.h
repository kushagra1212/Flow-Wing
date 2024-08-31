#ifndef __BRINGTEST_H__
#define __BRINGTEST_H__

#include "../../helpers/handlers/FileHandler.h"
#include "../../helpers/handlers/IOHandler.h"

class BringTest : public ::testing::Test, public FileHandler, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __BRINGTEST_H__