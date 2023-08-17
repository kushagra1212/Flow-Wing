#include "../src/REPL/Repl.h"
#include "../src/lexer/Lexer.h"
#include <gtest/gtest.h>
#include <sstream>

// Test fixture for I/O redirection
class IORedirectionTest : public ::testing::Test {
protected:
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;

  void SetUp() override {
    // Redirect cout to the stringstream

    saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
  }

  void TearDown() override {
    // Restore cout back to the standard output

    std::cout.rdbuf(saved_cout_buf);
  }

  void setInput(const std::string &input) { input_stream.str(input); }

  std::string getOutput() const { return output_stream.str(); }

  void runEvaluator() {
    Repl *repl = new Repl(true);
    repl->runForTest(input_stream, output_stream);
    delete repl;
  }
};

// Test fixture for I/O redirection

// TEST_F(IORedirectionTest, Test1) {
//   setInput("{1 + 2}");
//   runEvaluator();
//   EXPECT_EQ(getOutput(), ">> 3\n");
// }

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}