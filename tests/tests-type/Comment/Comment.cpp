/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


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
