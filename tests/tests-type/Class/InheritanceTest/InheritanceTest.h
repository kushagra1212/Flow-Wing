#ifndef __INHERITANCE_TEST_H__
#define __INHERITANCE_TEST_H__

#include "../../../helpers/handlers/IOHandler.h"

class InheritanceTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __INHERITANCE_TEST_H__