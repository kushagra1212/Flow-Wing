#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration() {
  repl = std::make_unique<Repl>(true);
}

void VariableDeclaration::SetUp() {
  cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());
}

void VariableDeclaration::TearDown() { std::cout.rdbuf(cout_backup); }

std::string VariableDeclaration::runReplWithInput(const std::string &input) {

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return captured_output.str();
}
std::string VariableDeclaration::runReplWithInputPrint(std::string input) {

  testing::internal::CaptureStdout();

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return testing::internal::GetCapturedStdout();
}

// Variable Declaration

// REPL TESTS

// Variable Declaration
TEST_F(VariableDeclaration, BasicVariableDeclaration) {
  std::string input = R"(var a = 2)";
  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Variable Re-Declaration in the same scope
TEST_F(VariableDeclaration, BasicVariableReDeclarationInSameScope) {
  std::string input = "var a = 2 var a = 3";

  std::string expected_error = "Variable x already exists";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("already exists") != std::string::npos);
}

// Variable Re-Declaration in the Different scope
TEST_F(VariableDeclaration, BasicVariableReDeclarationInDifferentScope) {
  std::string input = R"(var a = 2 { var a = 3 })";
  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Variable Declaration with Different Identifier
TEST_F(VariableDeclaration, BasicVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(var a = 2 var b = 3)";

  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Variable Declaration with Different Initializer
TEST_F(VariableDeclaration, BasicVariableDeclarationWithDifferentInitializer) {
  std::string input = R"(var a = 2 + 3)";

  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Declaration
TEST_F(VariableDeclaration, BasicConstantVariableDeclaration) {
  std::string input = R"(const a = 2)";

  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Re-Declaration
TEST_F(VariableDeclaration, BasicConstantVariableReDeclaration) {
  std::string input = R"(const a = 2 const a = 3)";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("already exists") != std::string::npos);
}

// Constant Variable Re-Declaration in Different Scope
TEST_F(VariableDeclaration,
       BasicConstantVariableReDeclarationInDifferentScope) {
  std::string input = R"(const a = 2 { const a = 3 })";

  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Declaration with Different Identifier
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(const a = 2 const b = 3)";

  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Declaration and again assign it to a different value
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationAndAssignToDifferentValue) {
  std::string input = R"(const a = 2 a = 3)";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Can not assign") != std::string::npos &&
              output.find("const variable") != std::string::npos);
}

// Constant Variable Declaration and again assign it to a different value in
// Different Scope
TEST_F(
    VariableDeclaration,
    BasicConstantVariableDeclarationAndAssignToDifferentValueInDifferentScope) {
  std::string input = R"(const a = 2 { a = 3 })";

  // Expected output should be in the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Can not assign") != std::string::npos &&
              output.find("const variable") != std::string::npos);
}

// Constant Variable Declaration and again assign it to a different value in
// Different Block Scope
TEST_F(
    VariableDeclaration,
    BasicConstantVariableDeclarationAndAssignToDifferentValueInDifferentScope2) {
  std::string input = R"({ const a = 2 { a = 3 } })";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);

  EXPECT_TRUE(output.find("Can not assign") != std::string::npos &&
              output.find("const variable") != std::string::npos);
}

// Constant Variable Declaration and Re-Declaration using var
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationAndReDeclarationUsingVar) {
  std::string input = R"(const a = 2 var a = 3)";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("already exists") != std::string::npos);
}
