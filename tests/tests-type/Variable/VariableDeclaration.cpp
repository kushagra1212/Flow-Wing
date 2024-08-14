#include "VariableDeclaration.h"

void VariableDeclaration::SetUp() { _test->SetUp(); }

void VariableDeclaration::TearDown() { _test->TearDown(); }

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
      R"(fun main2() -> int {
      var x = 2
      print(2) print(x) print(x+2) print(x+true) print(x+false)
      print(x+1.1) x = 2.2 print(x+2) print(x+false) print(x+true)
      x  =  true
      print(x==false) print(x+false)
      print(x+true) print(x+1) print(x+1.1)
      print(x+"Hello")
      return (0)
      }
      var y = main2()
      )";

  std::string expected_output =
      "224323.100000000000004.200000000000002.200000000000003."
      "20000000000000falsetruetrue22.10000000000000trueHello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENTForGlobalVariable) {
  std::string input =
      R"(
      var x = 2
      print(2) print(x) print(x+2) print(x+true) print(x+false)
      print(x+1.1) x = 2.2 print(x+2) print(x+false) print(x+true)
      x  =  true
      print(x==false) print(x+false)
      print(x+true) print(x+1) print(x+1.1)
      print(x+"Hello")
      )";

  std::string expected_output =
      "224323.100000000000004.200000000000002.200000000000003."
      "20000000000000falsetruetrue22.10000000000000trueHello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENT2) {
  std::string input =
      R"(
print("String"+"\n")
var x = "This is a string"
print(x+"\n")
x = 2
print(x+"\n")
x = true
print(x+"\n")
x = 2.0
print(x+"\n")

print("Int"+"\n")
var y = 2
print(y+"\n")
y = 2.0
print(y+"\n")
y = true
print(y+"\n")
y = "This is a string"
print(y+"\n")

print("Bool"+"\n")
var z = true
print(z+"\n")
z = 2
print(z+"\n")
z = 2.0
print(z+"\n")
z = "This is a string"
print(z+"\n")

print("Float"+"\n")
var a = 2.0
print(a+"\n")
a = 2
print(a+"\n")
a = true
print(a+"\n")
a = "This is a string"
print(a+"\n"))";

  std::string expected_output =
      R"(String
This is a string
2
true
2.00000000000000
Int
2
2.00000000000000
true
This is a string
Bool
true
2
2.00000000000000
This is a string
Float
2.00000000000000
2
true
This is a string
)";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TODO: Fix this test and Also add test for other types combinations

// TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENTError) {

//   try {
//     std::string input =
//         R"(
// var x:str = 1
//       )";

//     std::string expected_output = "Type mismatch in variable declaration x "
//                                   "Expected type String but got type
//                                   Integer";

//     setInput(input);
//     runEvaluator();
//     EXPECT_EQ(getOutput(), expected_output);
//     // If the function does not throw an exception, fail the test
//     FAIL() << "Expected exception not thrown";
//   } catch (const std::runtime_error &e) {
//     // Compare the error message with the expected error message
//     EXPECT_STREQ(e.what(), "Type mismatch in variable declaration x Expected
//     "
//                            "type String but got type Integer");
//   } catch (...) {
//     // If the thrown exception is not of type std::runtime_error, fail the
//     test FAIL() << "Unexpected exception type thrown";
//   }
// }