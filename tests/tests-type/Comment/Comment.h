#ifndef COMMENT_TEST_H
#define COMMENT_TEST_H

#include "../../helpers/handlers/IOHandler.h"

class CommentTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // FOR_LOOP_H