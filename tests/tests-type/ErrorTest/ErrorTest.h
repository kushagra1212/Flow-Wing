
#pragma once

#include "../../helpers/handlers/FileHandler.h"
#include "../../helpers/handlers/IOHandler.h"
#include "gtest/gtest.h"

class ErrorTest : public ::testing::Test, public FileHandler, public IOHandler {
protected:
  ErrorTest() { this->initialize(); }
  void SetUp() override;
  void TearDown() override;
};
