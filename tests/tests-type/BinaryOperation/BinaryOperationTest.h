#ifndef BINARY_OPERATION_TESTS_H
#define BINARY_OPERATION_TESTS_H

#include "../../helpers/handlers/FileHandler.h"
#include "../../helpers/handlers/IOHandler.h"

class BinaryOperationTest : public ::testing::Test,
                            public FileHandler,
                            public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input) override;
};
#endif // BINARY_OPERATION_H