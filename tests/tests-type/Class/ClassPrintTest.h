#pragma once
#include "../../helpers/handlers/IOHandler.h"

class ClassPrintTest : public IOHandler, public ::testing::Test {
public:
  void SetUp() override;
  void TearDown() override;
};