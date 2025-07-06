
#pragma once

#include "../../helpers/handlers/FileHandler.h"
#include "../../helpers/handlers/IOHandler.h"
#include "gtest/gtest.h"

class WarningTest : public ::testing::Test,
                    public FileHandler,
                    public IOHandler {
protected:
  WarningTest() { this->initialize(); }
  void SetUp() override;
  void TearDown() override;
};
