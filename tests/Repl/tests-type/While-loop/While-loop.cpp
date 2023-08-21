#include "While-loop.h"

TEST_F(ReplTest, BasicWhileLoop) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            x = x + 1
        }
        print(x)
    )";

  std::string expected_output = "5\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopWithIf) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            if(x == 3) {
                x = x + 1
            } else {
                x = x + 2
            }
        }
        print(x)
    )";

  std::string expected_output = "6\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// print inside while loop

TEST_F(ReplTest, BasicWhileLoopWithPrint) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            print(x)
            x = x + 1
        }
    )";

  std::string expected_output = "0\n1\n2\n3\n4\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// print inside while loop with if

TEST_F(ReplTest, BasicWhileLoopWithPrintAndIf) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            if(x == 3) {
                print(x)
                x = x + 1
            } else {
                print(x)
                x = x + 2
            }
        }
    )";

  std::string expected_output = "0\n2\n4\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// print inside while loop nested if else

TEST_F(ReplTest, BasicWhileLoopWithPrintAndNestedIfElse) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            if(x == 3) {
                print(x)
                x = x + 1
            } else {
                if(x == 2) {
                    print(x)
                    x = x + 2
                } else {
                    print(x)
                    x = x + 3
                }
            }
        }
    )";

  std::string expected_output = "0\n3\n4\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// print inside nested while loop

TEST_F(ReplTest, BasicWhileLoopWithPrintAndNestedWhileLoop) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            print(x)
            x = x + 1
            var y = 0
            while(y < 5) {
                print(y)
                y = y + 1
            }
        }
    )";

  std::string expected_output = "0\n0\n1\n2\n3\n4\n1\n0\n1\n2\n3\n4\n2\n0\n1\n2"
                                "\n3\n4\n3\n0\n1\n2\n3\n4\n4\n0\n1\n2\n3\n4\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// print inside nested while loop use the same variable name and more

TEST_F(ReplTest, BasicWhileLoopWithPrinLoop2) {
  std::string input = R"(
var x = 0
while (x < 5) {
    if (x == 3) {
        print("While Loop - x is 3:"+ x)
        x = x + 1
    } else {
        if (x == 2) {
            print("While Loop - x is 2:"+ x)
            x = x + 2
        } else {
            print("While Loop - Default:"+ x)
            x = x + 3
        }
    }
}

var testVariable = 7
const constantValue = 42

if (testVariable > 5 or testVariable < 0) {
    print("If-Else - Greater than 5 or less than 0")
} else {
    if (testVariable == 5) {
        print("If-Else - Equal to 5")
    } else {
        print("If-Else - Less than 5 and greater than 0")
    }
}

print("Constant value:"+ constantValue)

    )";

  std::string expected_output =
      "While Loop - Default:0\nWhile Loop - x is 3:3\nWhile Loop - "
      "Default:4\nIf-Else - Greater than 5 or less than 0\nIf-Else - Less than "
      "5 and greater than 0\n"
      "Constant value:42\n\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}
