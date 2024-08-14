#include "MDCInFunction.h"

void MDCInFunction::SetUp() { _test->SetUp(); }

void MDCInFunction::TearDown() { _test->TearDown(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

TEST_F(MDCInFunction, Int1DArrayAsParam) {

  I(R"(
        fun foo(a:int[3]) -> nthg {
            print(a)
        }

        var a:int[3] = [1,2,3]

        foo(a)
    )");

  EXPECT_EQ(getOutput(), "[1, 2, 3]");
}

TEST_F(MDCInFunction, Str1DArrayAsParam) {

  I(R"(
            fun foo(a:str[3]) -> nthg {
                print(a)
            }
    
            var a:str[3] = ["a","b","c"]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(), "['a', 'b', 'c']");
}

// 1D Deci Param

TEST_F(MDCInFunction, Deci1DArrayAsParam) {

  I(R"(
            fun foo(a:deci[3]) -> nthg {
                print(a)
            }
    
            var a:deci[3] = [1.1,2.2,3.3]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(),
            "[1.10000000000000, 2.20000000000000, 3.30000000000000]");
}

// 1D Bool Param

TEST_F(MDCInFunction, Bool1DArrayAsParam) {

  I(R"(
            fun foo(a:bool[3]) -> nthg {
                print(a)
            }
    
            var a:bool[3] = [true,false,true]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(), "[true, false, true]");
}

TEST_F(MDCInFunction, Int2DArrayAsParam) {

  I(R"(
            fun foo(a:int[2][3]) -> nthg {
                print(a)
            }
    
            var a:int[2][3] = [[1,2,3],[4,5,6]]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(), "[[1, 2, 3], [4, 5, 6]]");
}

TEST_F(MDCInFunction, Str2DArrayAsParam) {

  I(R"(
            fun foo(a:str[2][3]) -> nthg {
                print(a)
            }
    
            var a:str[2][3] = [["a","b","c"],["d","e","f"]]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(), "[['a', 'b', 'c'], ['d', 'e', 'f']]");
}

// 2D Deci Param

TEST_F(MDCInFunction, Deci2DArrayAsParam) {

  I(R"(
            fun foo(a:deci[2][3]) -> nthg {
                print(a)
            }
    
            var a:deci[2][3] = [[1.1,2.2,3.3],[4.4,5.5,6.6]]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(),
            "[[1.10000000000000, 2.20000000000000, 3.30000000000000], "
            "[4.40000000000000, 5.50000000000000, 6.60000000000000]]");
}

// 2D Bool Param

TEST_F(MDCInFunction, Bool2DArrayAsParam) {

  I(R"(
            fun foo(a:bool[2][3]) -> nthg {
                print(a)
            }
    
            var a:bool[2][3] = [[true,false,true],[false,true,false]]
    
            foo(a)
        )");

  EXPECT_EQ(getOutput(), "[[true, false, true], [false, true, false]]");
}

// One Array and Other Normal Param

TEST_F(MDCInFunction, Int2DArrayAsParamAndNormalParam) {

  I(R"(
            fun foo(a:int[2][3],x:int) -> nthg {
                a[0][1] = x
                print(a)
            }

            var x:int = 1

            var a:int[2][3] = [[1,2,3],[4,5,6]]

            foo(a,x)
        )");

  EXPECT_EQ(getOutput(), "[[1, 1, 3], [4, 5, 6]]");
}

TEST_F(MDCInFunction, Str2DArrayAsParamAndNormalParam) {

  I(R"(
            fun foo(a:str[2][3],x:str) -> nthg {
                a[0][1] = x
                print(a)
            }

            var x:str = "a"

            var a:str[2][3] = [["a","b","c"],["d","e","f"]]

            foo(a,x)
        )");

  EXPECT_EQ(getOutput(), "[['a', 'a', 'c'], ['d', 'e', 'f']]");
}

TEST_F(MDCInFunction, Int2DArrayAsParamAndNormalParamConstant) {

  I(R"(
            fun foo(a:int[2][3],x:int) -> nthg {
                a[0][1] = x
                print(a)
            }

            var a:int[2][3] = [[1,2,3],[4,5,6]]

            foo(a,1)
        )");

  EXPECT_EQ(getOutput(), "[[1, 1, 3], [4, 5, 6]]");
}

// In Scope

TEST_F(MDCInFunction, Int1DArrayAsParamLOCAL) {

  I(R"(
        fun foo(a:int[3]) -> nthg {
            print(a)
        }

{        var a:int[3] = [1,2,3]

        foo(a)}
    )");

  EXPECT_EQ(getOutput(), "[1, 2, 3]");
}

TEST_F(MDCInFunction, Str1DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:str[3]) -> nthg {
                print(a)
            }
    
{            var a:str[3] = ["a","b","c"]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(), "['a', 'b', 'c']");
}

// 1D Deci Param

TEST_F(MDCInFunction, Deci1DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:deci[3]) -> nthg {
                print(a)
            }
    
{            var a:deci[3] = [1.1,2.2,3.3]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(),
            "[1.10000000000000, 2.20000000000000, 3.30000000000000]");
}

// 1D Bool Param

TEST_F(MDCInFunction, Bool1DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:bool[3]) -> nthg {
                print(a)
            }
    
{            var a:bool[3] = [true,false,true]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(), "[true, false, true]");
}

TEST_F(MDCInFunction, Int2DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:int[2][3]) -> nthg {
                print(a)
            }
    
{            var a:int[2][3] = [[1,2,3],[4,5,6]]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(), "[[1, 2, 3], [4, 5, 6]]");
}

TEST_F(MDCInFunction, Str2DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:str[2][3]) -> nthg {
                print(a)
            }
    
{            var a:str[2][3] = [["a","b","c"],["d","e","f"]]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(), "[['a', 'b', 'c'], ['d', 'e', 'f']]");
}

// 2D Deci Param

TEST_F(MDCInFunction, Deci2DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:deci[2][3]) -> nthg {
                print(a)
            }
    
{            var a:deci[2][3] = [[1.1,2.2,3.3],[4.4,5.5,6.6]]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(),
            "[[1.10000000000000, 2.20000000000000, 3.30000000000000], "
            "[4.40000000000000, 5.50000000000000, 6.60000000000000]]");
}

// 2D Bool Param

TEST_F(MDCInFunction, Bool2DArrayAsParamLOCAL) {

  I(R"(
            fun foo(a:bool[2][3]) -> nthg {
                print(a)
            }
    
{            var a:bool[2][3] = [[true,false,true],[false,true,false]]
    
            foo(a)}
        )");

  EXPECT_EQ(getOutput(), "[[true, false, true], [false, true, false]]");
}

// One Array and Other Normal Param

TEST_F(MDCInFunction, Int2DArrayAsParamAndNormalParamLOCAL) {

  I(R"(
            fun foo(a:int[2][3],x:int) -> nthg {
                a[0][1] = x
                print(a)
            }
{
            var x:int = 1

            var a:int[2][3] = [[1,2,3],[4,5,6]]

            foo(a,x)}
        )");

  EXPECT_EQ(getOutput(), "[[1, 1, 3], [4, 5, 6]]");
}

TEST_F(MDCInFunction, Str2DArrayAsParamAndNormalParamLOCAL) {

  I(R"(
            fun foo(a:str[2][3],x:str) -> nthg {
                a[0][1] = x
                print(a)
            }

{            var x:str = "a"

            var a:str[2][3] = [["a","b","c"],["d","e","f"]]

            foo(a,x)}
        )");

  EXPECT_EQ(getOutput(), "[['a', 'a', 'c'], ['d', 'e', 'f']]");
}

TEST_F(MDCInFunction, Int2DArrayAsParamAndNormalParamConstantLOCAL) {

  I(R"(
            fun foo(a:int[2][3],x:int) -> nthg {
                a[0][1] = x
                print(a)
            }

{            var a:int[2][3] = [[1,2,3],[4,5,6]]

            foo(a,1)}
        )");

  EXPECT_EQ(getOutput(), "[[1, 1, 3], [4, 5, 6]]");
}

TEST_F(MDCInFunction, COMPLEX1) {

  I(R"(
fun mainTest(arr:int[2][2],arr2:int[2][4]) -> nthg {

     arr = [2 fill 10]
      print(arr)
      print(arr2)      
}
var arr:int[2][2] =  [ 2 fill 2]
var arr2:int[2][4] =  [2 fill 3]
arr2 = arr
print(arr2)
print(arr)
mainTest(arr,arr2)
        )");

  EXPECT_EQ(getOutput(), "[[2, 2, 0, 0], [0, 0, 0, 0]][[2, 2], [0, 0]][[10, "
                         "10], [0, 0]][[2, 2, 0, "
                         "0], [0, 0, 0, 0]]");
}

TEST_F(MDCInFunction, COMPLEX1LOCAL) {

  I(R"(
fun mainTest(arr:int[2][2],arr2:int[2][4]) -> nthg {

     arr = [2 fill 10]
      print(arr)
      print(arr2)      
}
{var arr:int[2][2] =  [ 2 fill 2]
var arr2:int[2][4] =  [2 fill 3]
arr2 = arr
print(arr2)
print(arr)
mainTest(arr,arr2)}
        )");

  EXPECT_EQ(getOutput(), "[[2, 2, 0, 0], [0, 0, 0, 0]][[2, 2], [0, 0]][[10, "
                         "10], [0, 0]][[2, 2, 0, "
                         "0], [0, 0, 0, 0]]");
}
TEST_F(MDCInFunction, COMPLEX1GL) {

  I(R"(
fun mainTest(arr:int[2][2],arr2:int[2][4]) -> nthg {

     arr = [2 fill 10]
      print(arr)
      print(arr2)      
}
var arr:int[2][2] =  [ 2 fill 2]
var arr2:int[2][4] =  [2 fill 3]
arr2 = arr
print(arr2)
print(arr)
{mainTest(arr,arr2)}
        )");

  EXPECT_EQ(getOutput(), "[[2, 2, 0, 0], [0, 0, 0, 0]][[2, 2], [0, 0]][[10, "
                         "10], [0, 0]][[2, 2, 0, "
                         "0], [0, 0, 0, 0]]");
}

TEST_F(MDCInFunction, ReturnContainerFromFunction) {

  I(R"(
    fun mainTest() -> int[2][5] {
      var x:int[2][5] = [6 fill 10]
      return x
}
print(mainTest())
        )");

  EXPECT_EQ(getOutput(), "[[10, 10, 10, 10, 10], [10, 0, 0, 0, 0]]");
}

// Test case for mainTest() function
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArray) {
  I(R"(
    fun mainTest() -> int[2][5] {
      var x:int[2][5] = [10 fill 10]
      return x
    }

    var result:int[2][5] = mainTest()
    print(result)
  )");

  EXPECT_EQ(getOutput(), "[[10, 10, 10, 10, 10], [10, 10, 10, 10, 10]]");
}

// Test case for checking that mainTest() and main2() have different outputs
TEST_F(MDCInFunction, MainAndMain2HaveDifferentOutputs) {
  I(R"(
    fun mainTest() -> int[2][5] {
      var x:int[2][5] = [10 fill 10]
      return x
    }

    fun main2() -> int[2][5] {
      var x:int[2][5] = [10 fill 11]
      return x
    }

    var result1:int[2][5] = mainTest()
    var result2:int[2][5] = main2()
    print(result1)
    print(result2)
  )");

  EXPECT_EQ(
      getOutput(),
      "[[10, 10, 10, 10, 10], [10, 10, 10, 10, 10]][[11, 11, 11, 11, 11], [11, "
      "11, 11, 11, 11]]");
}

// Test case for mainTest() function Str
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayStr) {
  I(R"(
   fun mainTest() -> str[2][5] {
      var x:str[2][5] = [6 fill "Hello"]
      return x
    }

    var result:str[2][5] = mainTest()
    print(result)
  )");

  EXPECT_EQ(
      getOutput(),
      "[['Hello', 'Hello', 'Hello', 'Hello', 'Hello'], ['Hello', '', '', '', "
      "'']]");
}

// Test case for mainTest() function bool
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayBool) {
  I(R"(
   fun mainTest() -> bool[2][5] {
      var x:bool[2][5] = [6 fill true]
      return x
    }

    var result:bool[2][5] = mainTest()
    print(result)
  )");

  EXPECT_EQ(
      getOutput(),
      "[[true, true, true, true, true], [true, false, false, false, false]]");
}

// Test case for mainTest() function deci
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayDeci) {
  I(R"(
   fun mainTest() -> deci[2][5] {
      var x:deci[2][5] = [6 fill 1.23]
      return x
    }

    var result:deci[2][5] = mainTest()
    print(result)
  )");

  EXPECT_EQ(getOutput(), "[[1.23000000000000, 1.23000000000000, "
                         "1.23000000000000, 1.23000000000000, "
                         "1.23000000000000], [1.23000000000000, "
                         "0.00000000000000, 0.00000000000000, "
                         "0.00000000000000, 0.00000000000000]]");
}

// Test case for mainTest() function
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayAssign) {
  I(R"(
    fun mainTest() -> int[2][5] {
      var x:int[2][5] = [6 fill 10]
      return x
    }

    var result:int[2][5] = [7 fill 1]
    result = mainTest()
    print(result)
  )");

  EXPECT_EQ(getOutput(), "[[10, 10, 10, 10, 10], [10, 0, 0, 0, 0]]");
}

// Test case for mainTest() function Str
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayStrAssign) {
  I(R"(
   fun mainTest() -> str[2][5] {
      var x:str[2][5] = [6 fill "Hello"]
      return x
    }

    var result:str[2][5] =[7 fill "Hi"]
    result = mainTest()
    print(result)
  )");

  EXPECT_EQ(
      getOutput(),
      "[['Hello', 'Hello', 'Hello', 'Hello', 'Hello'], ['Hello', '', '', '', "
      "'']]");
}

// Test case for mainTest() function bool
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayBoolAssign) {
  I(R"(
   fun mainTest() -> bool[2][5] {
      var x:bool[2][5] = [6 fill true]
      return x
    }

    var result:bool[2][5] = [7 fill true]
    result = mainTest()
    print(result)
  )");

  EXPECT_EQ(
      getOutput(),
      "[[true, true, true, true, true], [true, false, false, false, false]]");
}

// Test case for mainTest() function deci
TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayDeciAssign) {
  I(R"(
   fun mainTest() -> deci[2][5] {
      var x:deci[2][5] = [6 fill 1.23]
      return x
    }

    var result:deci[2][5] = [7 fill 1.5]
    result = mainTest()
    print(result)
  )");

  EXPECT_EQ(getOutput(), "[[1.23000000000000, 1.23000000000000, "
                         "1.23000000000000, 1.23000000000000, "
                         "1.23000000000000], [1.23000000000000, "
                         "0.00000000000000, 0.00000000000000, "
                         "0.00000000000000, 0.00000000000000]]");
}

TEST_F(MDCInFunction, MainFunctionReturnsCorrectArrayAssign2) {
  I(R"(
    fun mainTest() -> int[2][5] {
      var x:int[2][5] = [6 fill 1]

      x = [7 fill 10]

      return x
    }

    var result:int[2][5] = mainTest()

    print(result)
)");

  EXPECT_EQ(getOutput(), "[[10, 10, 10, 10, 10], [10, 10, 0, 0, 0]]");
}

#endif // JIT_TEST_MODE