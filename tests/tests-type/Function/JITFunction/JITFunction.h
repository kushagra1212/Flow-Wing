#ifndef __JIT__FUNCTION_TEST_H__
#define __JIT__FUNCTION_TEST_H__

#include "../../../helpers/handlers/IOHandler.h"

class JITFunction : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __JIT__FUNCTION_TEST_H__