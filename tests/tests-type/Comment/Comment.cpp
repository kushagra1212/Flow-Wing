#include "Comment.h"

void CommentTest::SetUp() { _test->SetUp(); }

void CommentTest::TearDown() { _test->TearDown(); }

TEST_F(CommentTest, BasicSingleLineComment) {
  std::string input = R"(print(5)
/; print(2) print(3)
    
)";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
// TEST_F(CommentTest, BasicSingleLineCommentScoped) {
//   std::string input = R"(
//     print(5)
// if(true){
//   /; print(2) print(3)
// }
// )";
//   std::string expected_output = "5";
//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }
TEST_F(CommentTest, BasicMultiLineComment) {
  std::string input = R"(/# Calulate sum  of natural number
fun main() {
    var num = 10
    var sum = 0
    var i = 1
    for (i to num) {
        sum = sum + i
        i = i - 1
    }

    print("Sum = "+ sum + sum)
}

main()

#/
print(2))";
  std::string expected_output = "2";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
