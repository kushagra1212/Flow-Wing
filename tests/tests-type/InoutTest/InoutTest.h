#ifndef __INOUT_TEST_H__
#define __INOUT_TEST_H__

#include "../../helpers/handlers/IOHandler.h"

class InoutTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __INOUT_TEST_H__