#include "StringOperation.h"
/*

    STRING OPERATIONS

*/

// Binary Operations on Strings

TEST_F(ReplTest, BasicStringOperationConcatWithNumber) {
  std::string input = R"("Hello"+2)";
  std::string expected_output = "Hello2\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcat) {
  std::string input = R"("Hello"+"Elang")";
  std::string expected_output = "HelloElang\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcatWithDouble) {
  std::string input = R"("Hello"+2.0)";
  std::string expected_output = "Hello2.000000\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcatWithBoolean) {
  std::string input = R"("Hello"+true)";
  std::string expected_output = "Hellotrue\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Strings with Strings

TEST_F(ReplTest, BasicStringOperationConcatWithStrings) {
  std::string input = R"("Hello"+"Elang")";
  std::string expected_output = "HelloElang\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Strings with Strings ( Comparison Operations )

TEST_F(ReplTest, BasicStringOperationComparisonEqual) {
  std::string input = R"("Hello"=="Hello")";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationComparisonNotEqual) {
  std::string input = R"("Hello"!="Hello")";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationComparisonLessThan) {
  std::string input = R"("Hello"<"Hello")";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationComparisonLessThanOrEqual) {
  std::string input = R"("Hello"<="Hello")";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationComparisonGreaterThan) {
  std::string input = R"("Hello">"Hello")";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationComparisonGreaterThanOrEqual) {
  std::string input = R"("Hello">="Hello")";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}
