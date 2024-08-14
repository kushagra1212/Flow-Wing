#ifndef __MDC_FUNCTION_TEST_H__
#define __MDC_FUNCTION_TEST_H__

#include "../../../../helpers/handlers/IOHandler.h"

class MDCInFunction : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __MDC_FUNCTION_TEST_H__