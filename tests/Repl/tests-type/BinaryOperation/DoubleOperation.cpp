#include "DoubleOperation.h"

/*

  DOUBLE OPERATION

*/

// Double Operation on Double ( Arithmetic )

TEST_F(ReplTest, BasicDoubleOperationAddition) {
  std::string input = "1.0+1.0";
  std::string expected_output = "2.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ReplTest, BasicDoubleOperationSubtraction) {
  std::string input = "1.0-1.0";
  std::string expected_output = "0.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ReplTest, BasicDoubleOperationMultiplication) {
  std::string input = "1.0*1.0";
  std::string expected_output = "1.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ReplTest, BasicDoubleOperationDivision) {
  std::string input = "1.0/1.0";
  std::string expected_output = "1.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Double Operation on Double ( Comparison )

TEST_F(ReplTest, BasicDoubleOperationLessThan) {
  std::string input = "1.0<1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ReplTest, BasicDoubleOperationLessThanOrEqual) {
  std::string input = "1.0<=1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Double Operation on Double ( Equality )

TEST_F(ReplTest, BasicDoubleOperationEqual) {
  std::string input = "1.0==1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ReplTest, BasicDoubleOperationNotEqual) {
  std::string input = "1.0!=1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
