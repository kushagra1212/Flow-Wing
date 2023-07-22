#include "../src/REPL/Repl.h"
#include <gtest/gtest.h>

#include <sstream>

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
  Repl repl;
  void runEvaluator() {
    // Run the evaluator

    repl.runForTest(input_stream, output_stream);
  }

private:
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};

// Test case for Repl::handleSpecialCommands
TEST_F(IORedirectionTest, TestHandleSpecialCommands) {
  setInput("");

  runEvaluator();

  // Check the output
  std::string expected_output =
      std::string(YELLOW) + "Welcome to the " + std::string(GREEN) + "C++" +
      std::string(YELLOW) + " REPL!" + std::string(RESET) + "\n" +
      std::string(YELLOW) +
      "Type `:exit` to exit, `:cls` to clear the "
      "screen, and `:tree` to see the AST.\n" +
      std::string(GREEN) + ">>> " + std::string(RESET) + std::string(GREEN) +
      ">>> " + std::string(RESET);

  EXPECT_EQ(getOutput(), expected_output);
}

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}