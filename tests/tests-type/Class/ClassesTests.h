#ifndef __CLASS_TEST_H__
#define __CLASS_TEST_H__

#include "../../helpers/handlers/IOHandler.h"
#include <chrono>
#include <thread>

class ClassesTests : public IOHandler, public ::testing::Test {
public:
  void SetUp() override;
  void TearDown() override;
};
#endif // __OBJECT_ARRAY_TEST_H__