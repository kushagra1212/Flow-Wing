#pragma once
#include "../../helpers/handlers/IOHandler.h"

class FunctionTypeTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};