#ifndef __CONTAINER_TEST_H__
#define __CONTAINER_TEST_H__

#include "../../helpers/handlers/IOHandler.h"

class ContainerTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __CONTAINER_TEST_H__