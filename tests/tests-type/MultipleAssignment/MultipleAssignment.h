#ifndef __MULTIPLE_ASSIGNMENT_H__
#define __MULTIPLE_ASSIGNMENT_H__

#include "../../helpers/handlers/IOHandler.h"

class MultipleAssignment : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __MULTIPLE_ASSIGNMENT_H__