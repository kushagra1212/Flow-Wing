#include "DoubleOperation.h"

/*

  DOUBLE OPERATION

*/

// Double Operation on Double ( Arithmetic )

TEST_F(BinaryOperationTest, BasicDoubleOperationAddition) {
  std::string input = "1.0+1.0";
  std::string expected_output = "2.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationSubtraction) {
  std::string input = "1.0-1.0";
  std::string expected_output = "0.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationMultiplication) {
  std::string input = "1.0*1.0";
  std::string expected_output = "1.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationDivision) {
  std::string input = "1.0/1.0";
  std::string expected_output = "1.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Double Operation on Double ( Comparison )

TEST_F(BinaryOperationTest, BasicDoubleOperationLessThan) {
  std::string input = "1.0<1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationLessThanOrEqual) {
  std::string input = "1.0<=1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Double Operation on Double ( Equality )

TEST_F(BinaryOperationTest, BasicDoubleOperationEqual) {
  std::string input = "1.0==1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationNotEqual) {
  std::string input = "1.0!=1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
