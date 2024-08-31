#ifndef FOR_LOOP_TEST_H
#define FOR_LOOP_TEST_H

#include "../../helpers/handlers/IOHandler.h"

class ForLoopReplTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // FOR_LOOP_H