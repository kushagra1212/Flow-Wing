#include "While-loop.h"

TEST_F(ReplTest, BasicWhileLoop) {
  std::string input = R"(
        var x = 0
        while(x < 5) {
            x = x + 1
        }
        print(x)
    )";

  std::string expected_output = "5";

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

  std::string expected_output = "6";

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

  std::string expected_output = "01234";

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

  std::string expected_output = "024";

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

  std::string expected_output = "034";

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

  std::string expected_output = "0012341012342012"
                                "34301234401234";

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
      "While Loop - Default:0While Loop - x is 3:3While Loop - "
      "Default:4If-Else - Greater than 5 or less than 0If-Else - Less than "
      "5 and greater than 0"
      "Constant value:42";
  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// test with Break

TEST_F(ReplTest, BasicWhileLoopWithBreak) {
  std::string input = R"(
        var x = 0

        while(x<5) {
            x=x+1
            print(x)
            break
        }

    )";

  std::string expected_output = "1";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopWithBreakAndIf) {
  std::string input = R"(
        var x = 0

        while(x<10) {
            x=x+1
            if(x==5) {
                print(x)
                break
            }
        }

    )";

  std::string expected_output = "5";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopWithBreakAndIfElse) {
  std::string input = R"(
        var x = 0

        while(x<10) {
            x=x+1
            if(x==5) {
                print(x)
            }else{
                if(x==2) {
                    print(2)
                }or if(x==7) {
                    print(7)
                    break
                }
            }
        }

    )";

  std::string expected_output = "257";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopNumber1to5Break) {
  std::string input = R"(
        var x = 0

        while(x<10) {
            x=x+1
            if(x==6) {
                break
            }
            print(x)
        }

    )";

  std::string expected_output = "12345";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopNestedBreak) {
  std::string input = R"(
        var x = 0

        while(x<3) {
            x=x+1
            while(x<3) {
                if(x==2) {
                    break
                }
                print(x)
                x=x+1
            }
            print(x)
        }

    )";

  std::string expected_output = "123";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopNestedBreak2) {
  std::string input = R"(
        var x = 0

        while(x<3) {
            x=x+1
            while(x<3) {
                print(x)
                break
                x=x+1
                print(x)
            }
        }

    )";

  std::string expected_output = "12";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicWhileLoopNestedBreak3) {
  std::string input = R"(
        var x = 0

        while(x<3) {
            x=x+1
            var y = 0
            while(y<3) {
                print(y)
                break
                x=x+1
                print(x)
            }
        }

    )";

  std::string expected_output = "000";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue statement

TEST_F(ReplTest, BasicWhileLoopContinue) {
  std::string input = R"(
        var x = 0

        while(x<5) {
            x=x+1
            if(x==3){
                continue
            }
            print(x)
        }

    )";

  std::string expected_output = "1245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue statement

TEST_F(ReplTest, BasicWhileLoopContinue2) {
  std::string input = R"(
        var x = 0

        while(x<5) {
            x=x+1
            print(x)
            if(x==3){
                continue
            }
            print(x)
        }

    )";

  std::string expected_output = "112234455";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue statement

TEST_F(ReplTest, BasicWhileLoopContinueNested) {
  std::string input = R"(
        var x = 0
        while(x<5) {
            x=x+1
            print(x)
            var z = x
            while(x<5) {
                if(x==0) {
                    print(0) 
                }or if(x==1){
                    x=x+1
                    continue
                }or if(x==2) {
                    print(2)
                }else{
                    print(x);
                }
                x=x+1
            }
            x=z+5
        }

    )";

  std::string expected_output = "1234";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue and break statement

TEST_F(ReplTest, BasicWhileLoopContinueBreak) {
  std::string input = R"(
        var x = 0

        while(x<5) {
            x=x+1
            if(x==3){
                continue
            }
            print(x)
            if(x==4){
                break
            }
        }

    )";

  std::string expected_output = "124";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue and break statement nested

TEST_F(ReplTest, BasicWhileLoopContinueBreakNested) {
  std::string input = R"(
        var x = 0

        while(x<5) {
            x=x+1
            if(x==3){
                continue
            }
            print(x)
            if(x==4){
                break
            }
            var y = 0
            while(y<5) {
                if(y==0) {
                    print(0) 
                }or if(y==1){
                    y=y+1
                    continue
                }or if(y==2) {
                    print(2)
                }else{
                    print(y);
                }
                y=y+1
            }
        }

    )";

  std::string expected_output = "10234202344";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic while loop with continue and break statement nested Break and continue

TEST_F(ReplTest, BasicWhileLoopContinueBreakNestedBreakContinue) {
  std::string input = R"(
        var x = 0

        while(x<5) {
            x=x+1
            if(x==3){
                continue
            }
            print(x+"\n")
            if(x==4){
                break
            }
            var y = 0
            while(y<5) {
                if(y==0) {
                    print("ZERO"+"\n") 
                }or if(y==1){
                    y=y+1
                    continue
                }or if(y==2) {
                    print(2+"\n")
                }else{
                    print(y+"\n");
                }
                y=y+1
                if(y==4){
                    break
                }
            }
        }
    )";

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

TEST_F(ReplTest, BasicWhileLoopFactorial) {
  std::string input = R"(
        var x = 5
        var factorial = 1
        while(x>0) {
            factorial = factorial * x
            x = x - 1
        }
        print(factorial)
    )";

  std::string expected_output = "120";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Factorial 2

TEST_F(ReplTest, BasicWhileLoopFactorial2) {
  std::string input = R"(
var x = 0

const num = 5
var factorial = 1
var current = 1

while (current <= num) {
    factorial = factorial * current
    current = current + 1

    if (current == 3) {
        continue
    }

    if (current > 7) {
        break
    }
}
print(factorial)
    )";

  std::string expected_output = "120";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}