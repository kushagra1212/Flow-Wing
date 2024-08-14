#ifndef IN_BUILT_FUNCTIONS_H
#define IN_BUILT_FUNCTIONS_H

#include "../../helpers/handlers/IOHandler.h"

class InBuiltFunction : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};

#endif // IN_BUILT_FUNCTIONS_H