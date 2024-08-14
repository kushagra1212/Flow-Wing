#ifndef __OBJECT_GLOBAL_TEST_H__
#define __OBJECT_GLOBAL_TEST_H__

#include "../../../helpers/handlers/IOHandler.h"

class ObjectLocalTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __OBJECT_GLOBAL_TEST_H__