#include "VariableDeclaration.h"

// Variable Declaration

// REPL TESTS

TEST_F(ReplTest, BasicVariableDeclaration) {
  std::string input = R"(var a = 2)";
  std::string expected_output = "";

  std::string output = runReplWithInput(input);

  EXPECT_EQ(output, expected_output);
}

// Variable Re-Declaration in the same scope

TEST_F(ReplTest, BasicVariableReDeclarationInSameScope) {
  std::string input = R"(
        var a = 2
        var a = 3 
   )";

  std::string expected_error = "Variable x already exists";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("already exists") != std::string::npos);
}

// Variable Re-Declaration in the Different scope

TEST_F(ReplTest, BasicVariableReDeclarationInDifferentScope) {
  std::string input = R"(
        var a = 2 
        {
            var a = 3 
        }
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Variable Declaration with Different Identifier

TEST_F(ReplTest, BasicVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(
        var a = 2 
        var b = 3 
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Variable Declaration with Different Initializer

TEST_F(ReplTest, BasicVariableDeclarationWithDifferentInitializer) {
  std::string input = R"(
        var a = 2 + 3
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Declaration

TEST_F(ReplTest, BasicConstantVariableDeclaration) {
  std::string input = R"(
        const a = 2 
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Re-Declaration

TEST_F(ReplTest, BasicConstantVariableReDeclaration) {
  std::string input = R"(
        const a = 2 
        const a = 3
   )";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("already exists") != std::string::npos);
}

// Constant Variable Re-Declaration in Different Scope

TEST_F(ReplTest, BasicConstantVariableReDeclarationInDifferentScope) {
  std::string input = R"(
        const a = 2 
        {
            const a = 3
        }
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Declaration with Different Identifier

TEST_F(ReplTest, BasicConstantVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(
        const a = 2 
        const b = 3
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Constant Variable Declaration and again assign it to a different value

TEST_F(ReplTest, BasicConstantVariableDeclarationAndAssignToDifferentValue) {
  std::string input = R"(
        const a = 2 
        a = 3
   )";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Can not assign") != std::string::npos &&
              output.find("const variable") != std::string::npos);
}

// Constant Variable Declaration and again assign it to a different value in
// Different Scope

TEST_F(
    ReplTest,
    BasicConstantVariableDeclarationAndAssignToDifferentValueInDifferentScope) {
  std::string input = R"(
        const a = 2 
        {
            a = 3
        }
   )";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Can not assign") != std::string::npos &&
              output.find("const variable") != std::string::npos);
}

// Constant Variable Declaration and again assign it to a different value in
// Different Block Scope

TEST_F(
    ReplTest,
    BasicConstantVariableDeclarationAndAssignToDifferentValueInDifferentScope2) {
  std::string input = R"(
     {   
        const a = 2 
        {
            a = 3
        }
     }
   )";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);

  EXPECT_TRUE(output.find("Can not assign") != std::string::npos &&
              output.find("const variable") != std::string::npos);
}

// Constant Variable Declaration and Re-Declaration using var

TEST_F(ReplTest, BasicConstantVariableDeclarationAndReDeclarationUsingVar) {
  std::string input = R"(
        const a = 2 
        var a = 3
   )";

  // Expected output should be in the of the output
  std::string output = runReplWithInput(input);
  EXPECT_TRUE(output.find("Variable") != std::string::npos &&
              output.find("already exists") != std::string::npos);
}