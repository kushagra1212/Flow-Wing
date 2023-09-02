#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration() { repl = nullptr; }

void VariableDeclaration::SetUp() {
  saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
}
void VariableDeclaration::TearDown() { std::cout.rdbuf(saved_cout_buf); }

void VariableDeclaration::setInput(const std::string &input) {
  input_stream.str(input);
}

std::string VariableDeclaration::getOutput() const {
  return output_stream.str();
}

void VariableDeclaration::runEvaluator() {
  repl = new Repl();
  repl->runForTest(input_stream, output_stream);
  delete repl;
}

// Variable Declaration

// REPL TESTS

// Variable Declaration
TEST_F(VariableDeclaration, BasicVariableDeclaration) {
  std::string input = R"(var a = 2)";
  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Variable Re-Declaration in the same scope
TEST_F(VariableDeclaration, BasicVariableReDeclarationInSameScope) {
  std::string input = "var a = 2 var a = 3";

  std::string expected_error = "Variable x Already Exists";

  // Expected output should be in the of the output

  setInput(input);
  runEvaluator();

  std::string output = getOutput();
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("Already Exists") != std::string::npos);
}

// Variable Re-Declaration in the Different scope
TEST_F(VariableDeclaration, BasicVariableReDeclarationInDifferentScope) {
  std::string input = R"(var a = 2 { var a = 3 })";
  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Variable Declaration with Different Identifier
TEST_F(VariableDeclaration, BasicVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(var a = 2 var b = 3)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Variable Declaration with Different Initializer
TEST_F(VariableDeclaration, BasicVariableDeclarationWithDifferentInitializer) {
  std::string input = R"(var a = 2 + 3)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Declaration
TEST_F(VariableDeclaration, BasicConstantVariableDeclaration) {
  std::string input = R"(const a = 2)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Re-Declaration
TEST_F(VariableDeclaration, BasicConstantVariableReDeclaration) {
  std::string input = R"(const a = 2 const a = 3)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string output = getOutput();

  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("Already Exists") != std::string::npos);
}

// Constant Variable Re-Declaration in Different Scope
TEST_F(VariableDeclaration,
       BasicConstantVariableReDeclarationInDifferentScope) {
  std::string input = R"(const a = 2 { const a = 3 })";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Declaration with Different Identifier
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(const a = 2 const b = 3)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Declaration and again assign it to a different value
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationAndAssignToDifferentValue) {
  std::string input = R"(const a = 2 a = 3)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string output = getOutput();
  EXPECT_TRUE(output.find("Can Not Assign") != std::string::npos &&
              output.find("Constant Variable") != std::string::npos);
}

// Constant Variable Declaration and again assign it to a different value in
// Different Scope
TEST_F(
    VariableDeclaration,
    BasicConstantVariableDeclarationAndAssignToDifferentValueInDifferentScope) {
  std::string input = R"(const a = 2 { a = 3 })";

  setInput(input);
  runEvaluator();
  // Expected output should be in the output
  std::string output = getOutput();
  EXPECT_TRUE(output.find("Can Not Assign") != std::string::npos &&
              output.find("Constant Variable") != std::string::npos);
}

// Constant Variable Declaration and again assign it to a different value in
// Different Block Scope
TEST_F(
    VariableDeclaration,
    BasicConstantVariableDeclarationAndAssignToDifferentValueInDifferentScope2) {
  std::string input = R"({ const a = 2 { a = 3 } })";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string output = getOutput();

  EXPECT_TRUE(output.find("Can Not Assign") != std::string::npos &&
              output.find("Constant Variable") != std::string::npos);
}

// Constant Variable Declaration and Re-Declaration using var
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationAndReDeclarationUsingVar) {
  std::string input = R"(const a = 2 var a = 3)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string output = getOutput();
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("Already Exists") != std::string::npos);
}

TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENT) {
  std::string input =
      R"(var x = 2 print(2) print(x) print(x+2) print(x+true) print(x+false)
      print(x+1.1) x = 2.2 print(x+2) print(x+false) print(x+true)
      x  =  true print(x==false) print(x+false)
      print(x+true) print(x+1) print(x+1.1)
      print(x+"Hello"))";

  std::string expected_output =
      "224323.1000004.2000002.2000003.200000falsetruetrue22.100000trueHello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}