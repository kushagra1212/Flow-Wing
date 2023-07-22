#include "../src/REPL/Repl.h"
#include <gtest/gtest.h>

#include <sstream>

// Test fixture for I/O redirection
class IORedirectionTest : public ::testing::Test {
protected:
  std::unique_ptr<Repl> repl = std::make_unique<Repl>();
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

  void runEvaluator() { repl->runForTest(input_stream, output_stream); }

private:
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};

// Test case for Repl::handleSpecialCommands
TEST_F(IORedirectionTest, TestHandleSpecialCommands) {
  // setInput(":cls");
  // runEvaluator();
  std::string expected_output = "";
  // EXPECT_EQ(getOutput(), expected_output);

  // Test the ":tree" command
  // setInput(":tree");
  // runEvaluator();
  // EXPECT_TRUE(repl->isTreeVisible()); // Assuming you have a getter for
  // seeTree

  // Test a normal input line
  setInput("\"hello\"");
  runEvaluator();
  expected_output = "hello\n";
  try {
    ASSERT_EQ(getOutput(), expected_output);

  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}