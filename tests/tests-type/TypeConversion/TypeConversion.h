#ifndef __TYPE_CONVERSION_H__
#define __TYPE_CONVERSION_H__

#include "../../helpers/handlers/IOHandler.h"

class TypeConversion : public ::testing::Test, public IOHandler {
protected:
  void SetUp() override;
  void TearDown() override;
};
#endif // __TYPE_CONVERSION_H__