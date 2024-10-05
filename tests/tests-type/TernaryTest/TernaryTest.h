#pragma once

#include "../../helpers/handlers/IOHandler.h"

class TernaryTest : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
