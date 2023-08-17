#include "Repl/ReplTest/ReplTest.h"

#include "Repl/tests-type/BinaryOperation/BinaryOperation.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
