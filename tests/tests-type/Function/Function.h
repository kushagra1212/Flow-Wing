#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H

#include "../../helpers/handlers/IOHandler.h"
namespace Tests {
namespace FlowWing {

class Function : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
} // namespace FlowWing
} // namespace Tests

#endif // IN_BUILT_FUNCTIONS_H