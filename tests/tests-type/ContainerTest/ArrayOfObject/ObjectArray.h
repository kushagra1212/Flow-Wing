#ifndef __OBJECT_ARRAY_TEST_H__
#define __OBJECT_ARRAY_TEST_H__

#include "../../../helpers/handlers/IOHandler.h"

class ObjectArray : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __OBJECT_ARRAY_TEST_H__