#ifndef __MULTIDIM__CONTAINER_TEST_H__
#define __MULTIDIM__CONTAINER_TEST_H__

#include "../../../helpers/handlers/IOHandler.h"

class MultiDimContainer : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __MULTIDIM__CONTAINER_TEST_H__