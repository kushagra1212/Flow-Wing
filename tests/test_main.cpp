#include "../src/REPL/Repl.h"
#include "../src/lexer/Lexer.h"
#include <gtest/gtest.h>
#include <sstream>

class ReplTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Set up common objects or resources here
    // For example, initialize your REPL instance
    repl = std::make_unique<Repl>(true);
  }

  void TearDown() override {
    // Clean up common objects or resources
    repl.reset();
  }

  // Common methods
  std::string runReplWithInput(const std::string &input) {
    std::stringstream captured_output;
    std::streambuf *cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(captured_output.rdbuf());

    repl->addTextString(input);
    std::string output = repl->runForTest(std::cin, std::cout);

    std::cout.rdbuf(cout_backup);

    return output;
  }

  std::unique_ptr<Repl> repl;
};

TEST_F(ReplTest, BasicInput) {
  std::string input = "2";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperation) {
  std::string input = R"("Hello")";
  std::string expected_output = "Hello";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcatWithNumber) {
  std::string input = R"("Hello"+2)";
  std::string expected_output = "Hello2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcat) {
  std::string input = R"("Hello"+"Elang")";
  std::string expected_output = "HelloElang";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcatWithDouble) {
  std::string input = R"("Hello"+2.0)";
  std::string expected_output = "Hello2.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringOperationConcatWithBoolean) {
  std::string input = R"("Hello"+true)";
  std::string expected_output = "Hellotrue";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Operations with Integer

TEST_F(ReplTest, BasicIntegerOperationAddition) {
  std::string input = "2+2";
  std::string expected_output = "4";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationSubtraction) {
  std::string input = "2-2";
  std::string expected_output = "0";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationMultiplication) {
  std::string input = "2*2";
  std::string expected_output = "4";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationDivision) {
  std::string input = "2/2";
  std::string expected_output = "1";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Operations between Integer and Double

TEST_F(ReplTest, BasicIntegerDoubleOperationAddition) {
  std::string input = "2+2.0";
  std::string expected_output = "4.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerDoubleOperationSubtraction) {
  std::string input = "2-2.0";
  std::string expected_output = "0.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerDoubleOperationMultiplication) {
  std::string input = "2*2.0";
  std::string expected_output = "4.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerDoubleOperationDivision) {
  std::string input = "2/2.0";
  std::string expected_output = "1.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Operations between Integer and Boolean

TEST_F(ReplTest, BasicIntegerBooleanOperationAddition) {
  std::string input = "2+true";
  std::string expected_output = "3";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerBooleanOperationSubtraction) {
  std::string input = "2-true";
  std::string expected_output = "1";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerBooleanOperationMultiplication) {
  std::string input = "2*true";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerBooleanOperationDivision) {
  std::string input = "2/true";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Operations between Double and Boolean

TEST_F(ReplTest, BasicDoubleBooleanOperationAddition) {
  std::string input = "2.0+true";
  std::string expected_output = "3.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicDoubleBooleanOperationSubtraction) {
  std::string input = "2.0-true";
  std::string expected_output = "1.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicDoubleBooleanOperationMultiplication) {
  std::string input = "2.0*true";
  std::string expected_output = "2.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicDoubleBooleanOperationDivision) {
  std::string input = "2.0/true";
  std::string expected_output = "2.000000";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Operations between Boolean and Boolean

TEST_F(ReplTest, BasicBooleanBooleanOperationAddition) {
  std::string input = "true+true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanBooleanOperationSubtraction) {
  std::string input = "true-true";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanBooleanOperationMultiplication2) {
  std::string input = "true*true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanBooleanOperationDivision) {
  std::string input = "true/true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Logical Operations

TEST_F(ReplTest, BasicBooleanLogicalOperationAnd) {
  std::string input = "true&&true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanLogicalOperationOr) {
  std::string input = "true||true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Comparison Operations

TEST_F(ReplTest, BasicBooleanComparisonOperationEqual) {
  std::string input = "true==true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanComparisonOperationNotEqual) {
  std::string input = "true!=true";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanComparisonOperationLessThan) {
  std::string input = "true<true";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanComparisonOperationLessThanOrEqual) {
  std::string input = "true<=true";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Logical Operations with Integer

TEST_F(ReplTest, BasicIntegerLogicalOperationAnd) {
  std::string input = "2&&2";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerLogicalOperationOr) {
  std::string input = "2||2";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Logical Not

TEST_F(ReplTest, BasicBooleanLogicalNot) {
  std::string input = "!true";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Comparison Operations with Integer

TEST_F(ReplTest, BasicIntegerComparisonOperationEqual) {
  std::string input = "2==2";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Comparison Operations with Double

TEST_F(ReplTest, BasicDoubleComparisonOperationEqual) {
  std::string input = "2.0==2.0";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Logical Operations with String

// Comparison Operations with String

TEST_F(ReplTest, BasicStringComparisonOperationEqual) {
  std::string input = R"("Hello"=="Hello")";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringComparisonOperationNotEqual) {
  std::string input = R"("Hello"!="Hello")";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringComparisonOperationLessThan) {
  std::string input = R"("Hello"<"Hello")";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicStringComparisonOperationLessThanOrEqual) {
  std::string input = R"("Hello"<="Hello")";
  std::string expected_output = "true";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Comparison Operations with String and Integer

TEST_F(ReplTest, BasicStringIntegerComparisonOperationEqual) {
  std::string input = R"("Hello"==2)";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Comparison Operations with String and Double

TEST_F(ReplTest, BasicStringDoubleComparisonOperationEqual) {
  std::string input = R"("Hello"==2.0)";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Comparison Operations with String and Boolean

TEST_F(ReplTest, BasicStringBooleanComparisonOperationEqual) {
  std::string input = R"("Hello"==true)";
  std::string expected_output = "false";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Bitwise Operations with Integer

TEST_F(ReplTest, BasicIntegerBitwiseOperationAnd) {
  std::string input = "2&2";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerBitwiseOperationOr) {
  std::string input = "2|2";
  std::string expected_output = "2";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerBitwiseOperationXor) {
  std::string input = "2^2";
  std::string expected_output = "0";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
