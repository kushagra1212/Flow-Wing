#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include "../../helpers/handlers/IOHandler.h"
class VariableDeclaration : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // VARIABLE_DECLARATION_H