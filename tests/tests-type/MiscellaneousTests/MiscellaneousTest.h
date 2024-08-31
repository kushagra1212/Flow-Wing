#ifndef __MISCELLANEOUSTEST_H__
#define __MISCELLANEOUSTEST_H__

#include "../../helpers/handlers/IOHandler.h"

class MiscellaneousTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __MISCELLANEOUSTEST_H__