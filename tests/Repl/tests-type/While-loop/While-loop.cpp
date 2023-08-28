#include "While-loop.h"
WhileLoop::WhileLoop() { repl = std::make_unique<Repl>(true); }

void WhileLoop::SetUp() {
  cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());
}

void WhileLoop::TearDown() { std::cout.rdbuf(cout_backup); }

std::string WhileLoop::runReplWithInput(const std::string &input) {

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return captured_output.str();
}
std::string WhileLoop::runReplWithInputPrint(std::string input) {

  testing::internal::CaptureStdout();

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return testing::internal::GetCapturedStdout();
}
TEST_F(WhileLoop, BasicWhileLoop) {
  std::string input = R"(var x = 0 while(x < 5) { x = x + 1 } print(x))";
  std::string expected_output = "5";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(WhileLoop, BasicWhileLoopWithIf) {
  std::string input =
      R"(var x = 0 while(x < 5) { if(x == 3) { x = x + 1 } else { x = x + 2 } } print(x))";
  std::string expected_output = "6";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Print inside while loop
TEST_F(WhileLoop, BasicWhileLoopWithPrint) {
  std::string input = R"(var x = 0 while(x < 5) { print(x) x = x + 1 })";
  std::string expected_output = "01234";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Print inside while loop with if
TEST_F(WhileLoop, BasicWhileLoopWithPrintAndIf) {
  std::string input =
      R"(var x = 0 while(x < 5) { if(x == 3) { print(x) x = x + 1 } else { print(x) x = x + 2 } })";
  std::string expected_output = "024";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Print inside while loop nested if-else
TEST_F(WhileLoop, BasicWhileLoopWithPrintAndNestedIfElse) {
  std::string input =
      R"(var x = 0 while(x < 5) { if(x == 3) { print(x) x = x + 1 } else { if(x == 2) { print(x) x = x + 2 } else { print(x) x = x + 3 } } })";
  std::string expected_output = "034";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Print inside nested while loop
TEST_F(WhileLoop, BasicWhileLoopWithPrintAndNestedWhileLoop) {
  std::string input =
      R"(var x = 0 while(x < 5) { print(x) x = x + 1 var y = 0 while(y < 5) { print(y) y = y + 1 } })";
  std::string expected_output = "001234101234201234301234401234";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// // Print inside nested while loop using the same variable name and more
// TEST_F(WhileLoop, BasicWhileLoopWithPrinLoop2) {
//   std::string input =
//       R"(var x = 0 while (x < 5) { if (x == 3) { print("While Loop - x is
//       3:"+ x) x = x + 1 } else { if (x == 2) { print("While Loop - x is 2:"+
//       x) x = x + 2 } else { print("While Loop - Default:"+ x) x = x + 3 } } }
//       var testVariable = 7 const constantValue = 42 if (testVariable > 5 ||
//       testVariable < 0) { print("If-Else - Greater than 5 or less than 0") }
//       else { if (testVariable == 5) { print("If-Else - Equal to 5") } else {
//       print("If-Else - Less than 5 and greater than 0") } } print("Constant
//       value:"+ constantValue) )";
//   std::string expected_output =
//       R"(While Loop - Default:0While Loop - x is 3:3While Loop -
//       Default:4If-Else - Greater than 5 or less than 0Constant value:42)";

//   std::string capturedOutput = runReplWithInputPrint(input);

//   ASSERT_EQ(capturedOutput, expected_output);
// }

// Test with Break
TEST_F(WhileLoop, BasicWhileLoopWithBreak) {
  std::string input = R"(var x = 0 while(x<5) { x=x+1 print(x) break })";
  std::string expected_output = "1";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with break and if statement
TEST_F(WhileLoop, BasicWhileLoopWithBreakAndIf) {
  std::string input =
      R"(var x = 0 while(x<10) { x=x+1 if(x==5) { print(x) break } })";
  std::string expected_output = "5";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with break and if-else statement
TEST_F(WhileLoop, BasicWhileLoopWithBreakAndIfElse) {
  std::string input =
      R"(var x = 0 while(x<10) { x=x+1 if(x==5) { print(x) }else{ if(x==2) { print(2) }or if(x==7) { print(7) break } } })";
  std::string expected_output = "257";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop from number 1 to 5 with break
TEST_F(WhileLoop, BasicWhileLoopNumber1to5Break) {
  std::string input =
      R"(var x = 0 while(x<10) { x=x+1 if(x==6) { break } print(x) })";
  std::string expected_output = "12345";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with nested break
TEST_F(WhileLoop, BasicWhileLoopNestedBreak) {
  std::string input =
      R"(var x = 0 while(x<3) { x=x+1 while(x<3) { if(x==2) { break } print(x) x=x+1 } print(x) })";
  std::string expected_output = "123";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with nested break
TEST_F(WhileLoop, BasicWhileLoopNestedBreak2) {
  std::string input =
      R"(var x = 0 while(x<3) { x=x+1 while(x<3) { print(x) break x=x+1 print(x) } })";
  std::string expected_output = "12";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with nested break and continue
TEST_F(WhileLoop, BasicWhileLoopNestedBreak3) {
  std::string input =
      R"(var x = 0 while(x<3) { x=x+1 var y = 0 while(y<3) { print(y) break x=x+1 print(x) } })";
  std::string expected_output = "000";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue statement
TEST_F(WhileLoop, BasicWhileLoopContinue) {
  std::string input =
      R"(var x = 0 while(x<5) { x=x+1 if(x==3){ continue } print(x) })";
  std::string expected_output = "1245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue statement
TEST_F(WhileLoop, BasicWhileLoopContinue2) {
  std::string input =
      R"(var x = 0 while(x<5) { x=x+1 print(x) if(x==3){ continue } print(x) })";
  std::string expected_output = "112234455";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue statement nested
TEST_F(WhileLoop, BasicWhileLoopContinueNested) {
  std::string input =
      R"(var x = 0 while(x<5) { x=x+1 print(x) var z = x while(x<5) { if(x==0) { print(0) }or if(x==1){ x=x+1 continue }or if(x==2) { print(2) }else{ print(x); } x=x+1 } x=z+5 })";
  std::string expected_output = "1234";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue and break statement
TEST_F(WhileLoop, BasicWhileLoopContinueBreak) {
  std::string input =
      R"(var x = 0 while(x<5) { x=x+1 if(x==3){ continue } print(x) if(x==4){ break } })";
  std::string expected_output = "124";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue and break statement nested
TEST_F(WhileLoop, BasicWhileLoopContinueBreakNested) {
  std::string input =
      R"(var x = 0 while(x<5) { x=x+1 if(x==3){ continue } print(x) if(x==4){ break } var y = 0 while(y<5) { if(y==0) { print(0) }or if(y==1){ y=y+1 continue }or if(y==2) { print(2) }else{ print(y); } y=y+1 } })";
  std::string expected_output = "10234202344";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue and break statement nested Break and continue
TEST_F(WhileLoop, BasicWhileLoopContinueBreakNestedBreakContinue) {
  std::string input =
      R"(var x = 0 while(x<5) { x=x+1 if(x==3){ continue } print(x+"\n") if(x==4){ break } var y = 0 while(y<5) { if(y==0) { print("ZERO"+"\n") }or if(y==1){ y=y+1 continue }or if(y==2) { print(2+"\n") }else{ print(y+"\n"); } y=y+1 if(y==4){ break } } })";
  std::string expected_output = R"(1
ZERO
2
3
2
ZERO
2
3
4
)";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Factorial
TEST_F(WhileLoop, BasicWhileLoopFactorial) {
  std::string input =
      R"(var x = 5 var factorial = 1 while(x>0) { factorial = factorial * x x = x - 1 } print(factorial))";
  std::string expected_output = "120";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Factorial 2
TEST_F(WhileLoop, BasicWhileLoopFactorial2) {
  std::string input =
      R"(var x = 0 const num = 5 var factorial = 1 var current = 1 while (current <= num) { factorial = factorial * current current = current + 1 if (current == 3) { continue } if (current > 7) { break } } print(factorial))";
  std::string expected_output = "120";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}
