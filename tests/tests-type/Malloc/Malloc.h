#ifndef __MALLOC_TEST_H__
#define __MALLOC_TEST_H__

#include "../../helpers/handlers/IOHandler.h"

class Malloc : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __MALLOC_TEST_H__