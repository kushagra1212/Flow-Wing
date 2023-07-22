#include <gtest/gtest.h>
#include <sstream>

#include "../compiler/Evaluator.h"

// Test fixture for I/O redirection
class IORedirectionTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Redirect cout to the stringstream
    output_stream.str("");
    saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
  }

  void TearDown() override {
    // Restore cout back to the standard output
    std::cout.rdbuf(saved_cout_buf);
  }

  void setInput(const std::string &input) { input_stream.str(input); }

  std::string getOutput() const { return output_stream.str(); }

  void runEvaluator() {

    std::stringstream console_input_stream;
    std::stringstream console_output_stream;

    console_input_stream << input_stream.rdbuf();
    console_output_stream << std::cout.rdbuf();

    // Run your console application with the provided input
    runConsole(console_input_stream, console_output_stream);
  }

private:
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};

// Example test case
TEST_F(IORedirectionTest, TestExample) {
  // Set the input for the test case
  setInput("1 + 2\n"); // Replace with the input you want to test

  // Run the evaluator
  runEvaluator();

  // Check the output
  std::string expected_output = "3\n"; // Replace with the expected output
  EXPECT_EQ(getOutput(), expected_output);
}
