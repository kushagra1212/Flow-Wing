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

  Repl *repl = nullptr;
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
    repl = new Repl();
    repl->runForTest(input_stream, output_stream);
    delete repl;
  }
};

// Test case for Repl::handleSpecialCommands

TEST_F(IORedirectionTest, TestHandleShowSyntaxTree) {
  setInput(":st");
  runEvaluator();
  ASSERT_TRUE(repl->isSyntaxTreeVisible());
}

// Test case for Repl::handleSpecialCommands

TEST_F(IORedirectionTest, TestHandleShowBoundTree) {
  setInput(":bt");
  runEvaluator();
  ASSERT_TRUE(repl->isBoundTreeVisible());
}

// Test case for Repl::countBraces

TEST_F(IORedirectionTest, TestCountBraces) {
  ASSERT_EQ(repl->countBraces("{}", '{'), 1);
  ASSERT_EQ(repl->countBraces("{}", '}'), 1);
  ASSERT_EQ(repl->countBraces("{{}}", '{'), 2);
  ASSERT_EQ(repl->countBraces("{{}}", '}'), 2);
}

// Test case for Repl::compileAndEvaluate

TEST_F(IORedirectionTest, TestCompileAndEvaluate) {
  setInput("1 + 2");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3\n");
}

// Test case for Repl::printWelcomeMessage

TEST_F(IORedirectionTest, TestPrintWelcomeMessage) {
  runEvaluator();
  ASSERT_EQ(getOutput(), "");
}

// Test case for evaluating a single expression

TEST_F(IORedirectionTest, TestSingleExpression) {
  setInput("1 + 2");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3\n");
}

// Test case for evaluating multiple expressions

TEST_F(IORedirectionTest, TestMultipleExpressions) {
  setInput("var x = 1+2");
  setInput("var y = 3+4");
  runEvaluator();
  ASSERT_EQ(getOutput(), "7\n");
}

// Test case for evaluating a single expression with a variable

TEST_F(IORedirectionTest, TestSingleExpressionWithVariable) {
  setInput("var x = 1 + 2");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3\n");
}

// Test case for executing a single expression with a different type

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType) {
  setInput("var x = 1 + 2");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3\n");
}

// Test case for executing a single expression with a different type

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType2) {
  setInput("var x = 1 + 2.0");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3\n");
}

// Test case for executing a single expression with a commbianation of types and
// expressions

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType3) {
  setInput("var y = 3 * true");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3\n");
}

// Test case for executing a single expression with a commbianation of types

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType4) {
  setInput("var y = 3 * false");
  runEvaluator();
  ASSERT_EQ(getOutput(), "0\n");
}

// Test case for executing a single expression with a commbianation of  double &
// int

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType6) {
  setInput("var y = 3 * 2.0");
  runEvaluator();
  ASSERT_EQ(getOutput(), "6\n");
}

// Test case for executing a single expression with a commbianation of  double &
// int

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType7) {
  setInput("var y = 3.1 * 2");
  runEvaluator();
  ASSERT_EQ(getOutput(), "6.2\n");
}

// Test case for executing a single expression with a commbianation of string &
// double

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType9) {
  setInput("var y = 3.1 + \"Hello\"");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3.100000Hello\n");
}

// Test Case for String concatenation

TEST_F(IORedirectionTest, TestStringConcatenation) {
  setInput("var y = \"Hello\" + \"World\"");
  runEvaluator();
  ASSERT_EQ(getOutput(), "HelloWorld\n");
}

// Test Case for String  concatenation with integer

TEST_F(IORedirectionTest, TestStringConcatenationWithInteger) {
  setInput("var y = \"Hello\" + 1");
  runEvaluator();
  ASSERT_EQ(getOutput(), "Hello1\n");
}

// Test Case for String  concatenation with double

TEST_F(IORedirectionTest, TestStringConcatenationWithDouble) {
  setInput("var y = \"Hello\" + 1.0");
  runEvaluator();
  ASSERT_EQ(getOutput(), "Hello1.000000\n");
}

// Bitwise operators

// Test case for executing a single expression with a commbianation of string

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType11) {
  setInput("var y = 3 & 2");
  runEvaluator();
  ASSERT_EQ(getOutput(), "2\n");
}

// Test case for executing a single expression with a commbianation of string

// bool

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType12) {
  setInput("var y = 3 & true");
  runEvaluator();
  ASSERT_EQ(getOutput(), "1\n");
}

// Test case for executing a single expression with a commbianation of string

// dobule , bool & int in same expression

TEST_F(IORedirectionTest, TestSingleExpressionWithDifferentType14) {
  setInput("var y = 3 & false & true");
  runEvaluator();
  ASSERT_EQ(getOutput(), "0\n");
}

TEST_F(IORedirectionTest, TestForForLoop) {
  setInput("for(var i = 0 to 10) { print(i) }");
  runEvaluator();
  ASSERT_EQ(getOutput(), "012345678910");
}
TEST_F(IORedirectionTest, TestForForLoop2) {
  setInput("for var x = 0 to 2 { for var x = 3 to 5 { print(x) if (x == 4) { "
           "break } } if(x==1) {continue }print(x)}");
  runEvaluator();
  ASSERT_EQ(getOutput(), "34034342");
}

TEST_F(IORedirectionTest, TestForFunction) {
  setInput("fun add(a,b) { return (a+b) } var ans = add(1,2) print(ans)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3");
}
TEST_F(IORedirectionTest, TestForFunctionFactorial) {
  setInput(
      "fun fact(n) { if(n==0) { return (1) } else { return (n*fact(n-1))   } } "
      "var ans = fact(5) print(ans)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "120");
}

// Test for inbuilt function print

TEST_F(IORedirectionTest, TestForInbuiltFunctionPrint) {
  setInput("var x = 20  print(x)");
  runEvaluator();

  ASSERT_EQ(getOutput(), "20");
}

// /*
//     Statements
// */
// Test Case for evaluating a single statement

TEST_F(IORedirectionTest, TestSingleStatement) {
  setInput("{var x=1+2 print(x)}");
  runEvaluator();
  ASSERT_EQ(getOutput(), "3");
}

// Test Case for evaluating multiple statements

TEST_F(IORedirectionTest, TestMultipleStatements) {
  setInput("{var x = 1 + 2 var y = 3 + 4 print(y)} ");
  runEvaluator();
  ASSERT_EQ(getOutput(), "7");
}

// Test Case for evaluating a single statement with a variable

// TEST_F(IORedirectionTest, TestSingleStatementWithVariable) {
//   setInput("{var x = 1 + 2 \n print(x)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "3");
// }

// // Test Case for evaluating a single statement with a variable

// TEST_F(IORedirectionTest, TestSingleStatementWithVariable2) {

//   setInput("{var y = 2 var x = 2+1  y = Int32(y) y = y + 1} print(y)");

//   runEvaluator();
//   ASSERT_EQ(getOutput(), "3");
// }

// // Test Case for evaluating a single statement with a variable

// TEST_F(IORedirectionTest, TestSingleStatementWithVariable3) {
//   setInput("{var x = 1 + 2 var y = x + 3 var z = y + 4 print(z)}");

//   runEvaluator();
//   ASSERT_EQ(getOutput(), "10");
// }

// // Test Case for evaluating a If statement with a variable

// TEST_F(IORedirectionTest, TestIfStatementWithVariable) {
//   setInput("{var x = 1 + 2 var y = x + 3 var z = y + 4 var a = z + "
//            "5 if(a == 15) {print(a)} else {print(x)}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "15");
// }

// // Test Case for evaluating a If statement  with boolean

// TEST_F(IORedirectionTest, TestIfStatementWithBoolean) {
//   setInput("{var x = 1 + 2var y = x + 3var z = y + 4var a = z + "
//            "5if(a == 15) {print(true)}else {print(false)}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "true");
// }

// // Test Case for evaluating a If statement  with  integer

// TEST_F(IORedirectionTest, TestIfStatementWithInteger) {
//   setInput("{var x = 1 + 2 var y = x + 3 var z = y + 4 var a = z + "
//            "5 if(a == 15) {print(1)} else {print(0)} }");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// /*
//     BlockStatements
// */
// // Test Case for evaluating a Block statement  with  integer

// TEST_F(IORedirectionTest, TestBlockStatementWithInteger) {
//   setInput("{var x = 1 + 2var y = x + 3var z = y + 4var a = z + "
//            "5if(a == 15) {print(1)}else {print(0)}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// // Test Case for evaluating a Nested Block statement  with  integer

// TEST_F(IORedirectionTest, TestNestedBlockStatementWithInteger) {
//   setInput("{var x = 1 + 2var y = x + 3var z = y + 4var a = z + "
//            "5if(a == 15) {print(1)}else {print(0)}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// // Test Case for evaluating a Nested Block statement  with  different types

// TEST_F(IORedirectionTest, TestNestedBlockStatementWithDifferentTypes) {
//   setInput("{var x = 1 + 2 var y = x + 3 var z = y + 4 var a = z + "
//            "5 if(a == 15) {print(1)} else {print(0)} }");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// // Test Case for evaluating a Nested Block statement  with  different data

// // & expressions

// TEST_F(IORedirectionTest, TestNestedBlockStatementWithDifferentTypes2) {
//   setInput("{var x = 1 + 2var y = x + 3var z = y + 4var a = z + "
//            "5if(a == 15) {print(1)}else {print(0)}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// // Test Case for const statement with  different data types & expressions

// TEST_F(IORedirectionTest, TestConstStatementWithDifferentTypes) {
//   setInput("{const x = 1 + 2const y = x + 3const z = y + 4 const a = z + 5 "
//            "if(a == 15) {print(1)} else {print(0)} }");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// // Test Case for var variable reassignment

// TEST_F(IORedirectionTest, TestVarVariableReassignment) {
//   setInput("{var x = 1 + 2 x = 3 print(x)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "3");
// }

// // Test Case for var variable redeclaration in different scope

// TEST_F(IORedirectionTest, TestVarVariableRedeclaration2) {
//   setInput("{var x = 1 + 2{var x = 3} print(x)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "3");
// }

// // Test Case for If statement with  different data types & expressions

// TEST_F(IORedirectionTest, TestIfStatementWithDifferentTypes) {
//   setInput("{const x = 1 + 2 const y = x + 3 const z = y + 4 const a = z if(a
//   "
//            "== 15) {print(1)} else {print(0)}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "0");
// }

// // Test Case for Nested while statement condition with  different int data

// TEST_F(IORedirectionTest,
// TestNestedWhileStatementConditionWithDifferentTypes) {
//   setInput("{const x = 1 + 2 const y = x + 3 const z = y + 4 const a = z + "
//            "5 while(a) {while(a == 15) {print(1) break} break}  }");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "1");
// }

// // Sum of first 10 numbers

// TEST_F(IORedirectionTest, TestSumOfFirst10Numbers) {
//   setInput(
//       "{var x =0 var y =0  while(x<= 10) {y = y + x  x = x + 1} print(y)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "45");
// }

// // multiplication of first 10 numbers in while loop where condition is true

// TEST_F(IORedirectionTest, TestMultiplicationOfFirst10Numbers) {
//   setInput("{var x = 1 var y = 1 while(x < 10) {y = y * x x = x +
//   1}print(y)}"); runEvaluator(); ASSERT_EQ(getOutput(), " 362880");
// }

// // complex while loop

// TEST_F(IORedirectionTest, TestComplexWhileLoop) {
//   setInput("{var x = 1 var y = 1 while(x < 10) {y = y * x x = x
//   +1}print(y)}"); runEvaluator(); ASSERT_EQ(getOutput(), " 362880");
// }

// // Complex multiple while loop with fizzbuzz  problem

// TEST_F(IORedirectionTest, TestComplexMultipleWhileLoop) {
//   setInput(
//       "{var x = 1 var y = 1 while(x < 10) {y = y * x x = x + 1}var "
//       "z=1 while(z<100) {if(z%3==0){if(z%5==0){z=z+1}else{z=z+1}}else { if "
//       "(z % 5 == 0) { z = z + 1 } else { z = z + 1}}}}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "100\n");
// }

// // Test for for loop

// TEST_F(IORedirectionTest, TestForLoop) {
//   setInput("{var x = 0 for(var i = 0 to 9) {x = x + i} print(x)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "45");
// }

// TEST_F(IORedirectionTest,
//        TestForLoopAndVariableAssignmentInConditionNoVariableDeclaration) {
//   setInput("{var x = 10 for 2 to 5 {x=x+1} print(x)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "14");
// }

// TEST_F(IORedirectionTest,
//        TestForLoopAndVariableAssignmentInConditionWithVariableDeclaration) {
//   setInput("{var x = 20 for var y = 0 to 3 {x=x+1}print(x)}");
//   runEvaluator();
//   ASSERT_EQ(getOutput(), "24");
// }

// Test For Conversion  Int32 to String

TEST_F(IORedirectionTest, TestForConversionInt32ToString) {
  setInput("String(10)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "10\n");
}

// Test For Conversion  Double to String

TEST_F(IORedirectionTest, TestForConversionDoubleToString) {
  setInput("String(10.0)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "10.000000\n");
}

// Test For Conversion  Bool to String

TEST_F(IORedirectionTest, TestForConversionBoolToString) {
  setInput("String(true)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "1\n");
}

// Test For Conversion  String to Int32

TEST_F(IORedirectionTest, TestForConversionStringToInt32) {
  setInput("Int32(\"10\")");
  runEvaluator();
  ASSERT_EQ(getOutput(), "10\n");
}

// Test For Conversion  Double to Int32

TEST_F(IORedirectionTest, TestForConversionDoubleToInt32) {
  setInput("Int32(10.0)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "10\n");
}

// Test For Conversion  Bool to Int32

TEST_F(IORedirectionTest, TestForConversionBoolToInt32) {
  setInput("Int32(true)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "1\n");
}

// Test For Conversion  String to Double

TEST_F(IORedirectionTest, TestForConversionStringToDouble) {
  setInput("Double(\"10.1\")");
  runEvaluator();
  ASSERT_EQ(getOutput(), "10.1\n");
}

// Test For Conversion  Int32 to Double

TEST_F(IORedirectionTest, TestForConversionInt32ToDouble) {
  setInput("Double(10)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "10\n");
}

// Test For Conversion  Bool to Double

TEST_F(IORedirectionTest, TestForConversionBoolToDouble) {
  setInput("Double(true)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "1\n");
}

// Test For Conversion  Int32 to Bool

TEST_F(IORedirectionTest, TestForConversionInt32ToBool) {
  setInput("Bool(10)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "true\n");
}

// Test For Conversion  Double to Bool

TEST_F(IORedirectionTest, TestForConversionDoubleToBool) {
  setInput("Bool(10.0)");
  runEvaluator();
  ASSERT_EQ(getOutput(), "true\n");
}

// Test For Conversion  String to Bool

TEST_F(IORedirectionTest, TestForConversionStringToBool) {
  setInput("Bool(\"10\")");
  runEvaluator();
  ASSERT_EQ(getOutput(), "true\n");
}

// Test For Conversion  String to String

// Test fixture for Lexer class
class LexerTest : public ::testing::Test {
protected:
  Lexer lexer;

public:
  void setInput(const std::string &input) {
    lexer = Lexer(std::vector<std::string>{input});
  }

  void setInput(const std::vector<std::string> &input) { lexer = Lexer(input); }

  SyntaxToken<std::any> *readString() { return lexer.readString(); }

  LexerTest() : lexer(std::vector<std::string>{}) {}
};

// Test case for valid string literals
// TEST_F(LexerTest, TestValidStringLiteral) {
//   std::string input = "Hello, world!";
//   setInput(input);
//   SyntaxToken<std::any> *token = LexerTest::lexer.readString();

//   ASSERT_EQ(token->getKind(), SyntaxKindUtils::SyntaxKind::StringToken);
//   ASSERT_EQ(std::any_cast<std::string>(token->getValue()), "Hello, world!");
// }

// Test case for unterminated string literals
// TEST_F(LexerTest, TestUnterminatedStringLiteral) {
//   std::string input = "Hello, world!";
//   setInput(input);
//   SyntaxToken<std::any> *token = readString();

//   ASSERT_EQ(token->getKind(), SyntaxKindUtils::SyntaxKind::BadToken);
//   ASSERT_TRUE(token->getText().find("ERROR: unterminated string literal") !=
//               std::string::npos);
// }

// // Test case for invalid escape sequences
// TEST_F(LexerTest, TestInvalidEscapeSequence) {
//   std::string input = "Hello, \\world!";
//   setInput(input);
//   SyntaxToken<std::any> *token = readString();

//   ASSERT_EQ(token->getKind(), SyntaxKindUtils::SyntaxKind::BadToken);
//   ASSERT_TRUE(token->getText().find("ERROR: bad character escape sequence")
//   !=
//               std::string::npos);
// }

// Add more test cases as needed to cover other scenarios

// Don't forget to deallocate memory to avoid memory leaks.
// TEST_F(LexerTest, TestMemoryDeallocation) {

//   std::string input = "Hello, world!";
//   setInput(input);
//   SyntaxToken<std::any> *token = readString();
//   delete token;
// }

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}