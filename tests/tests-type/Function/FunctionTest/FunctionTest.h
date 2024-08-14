#ifndef __FUNCTION_TEST_LOCAL_TEST_H__
#define __FUNCTION_TEST_LOCAL_TEST_H__

#include "../../../helpers/handlers/IOHandler.h"

class FunctionTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __OBJECT_ARRAY_TEST_H__