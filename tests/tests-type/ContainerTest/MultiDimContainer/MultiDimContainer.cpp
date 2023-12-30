#include "MultiDimContainer.h"

MultiDimContainer::MultiDimContainer() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void MultiDimContainer::SetUp() { _test->SetUp(); }

void MultiDimContainer::TearDown() { _test->TearDown(); }

void MultiDimContainer::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string MultiDimContainer::getOutput() const { return _test->getOutput(); }

void MultiDimContainer::runEvaluator() { _test->runEvaluator(); }

#ifdef JIT_TEST_MODE
TEST_F(MultiDimContainer, BasicContainerIntDeclaration) {
  I("var x:int[2] = [1,2] print(x)");
  O("[1, 2]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment) {
  I(R"(    var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] x[0][0] =
        5 print(x) )");

  O("[[5, 2], [3, 4]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] x[0][1] =
        5 print(x) 
        
    )");

  O("[[1, 5], [3, 4]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFill) {
  I(R"(
        var x : int[2][2] = [3 fill 4]
        print(x)
        
    )");

  O("[[4, 4], [4, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFill2) {
  I(R"(
        var x : int[2][5] = [5 fill 10]
        print(x)
        
    )");

  O("[[10, 10, 10, 10, 10], [0, 0, 0, 0, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFillAll) {
  I(R"(
        var x : int[5][3] = [15 fill 2]
        print(x)
        
    )");

  O("[[2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2]]");
}

TEST_F(MultiDimContainer, 3DContainerAssignment) {
  I(R"(
        var x : int[5][3][2] = [15 fill 2]
        print(x)
        
    )");

  O("[[[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 0], [0, "
    "0]], [[0, 0], [0, 0], [0, 0]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerAssignmentAccess) {
  I(R"(
        var x : int[5][3][2] = [15 fill 2]
        x[0][0][0] = 5
        print(x)
        
    )");

  O("[[[5, 2], [2, 2], [2, 2]], [[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 0], [0, "
    "0]], [[0, 0], [0, 0], [0, 0]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 2DContainerInit) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ] ]
        print(x)
        
    )");

  O("[[1, 2], [0, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerInit2) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ],[ 3] ]
        print(x)
        
    )");

  O("[[1, 2], [3, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerInit2DiffDim) {

  I(R"(
            var x : int[2][3] = [ [ 1, 2 ],[ 3, 4, 5] ]
            print(x)
            
        )");

  O("[[1, 2, 0], [3, 4, 5]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFill) {

  I(R"(
            var x : int[2][3][2] = [6 fill 5] 
            print(x)
            
        )");

  O("[[[5, 5], [5, 5], [5, 5]], [[0, 0], [0, 0], [0, 0]]]");
}
TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillWithVar) {

  I(R"(     
            var y:int = 5
            var x : int[2][3][2] = [6 fill y] 
            print(x)
            
        )");

  O("[[[5, 5], [5, 5], [5, 5]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillWithVar2) {

  I(R"(     
            var y:int = 5
            var x : int[2][3][2] = [6 fill y + 1] 
            print(x)
            
        )");

  O("[[[6, 6], [6, 6], [6, 6]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithVar2) {

  I(R"(     
            var y:int = 5
            var x : int[2][3][2] = [ y, y + 1 ] 
            print(x)
            
        )");

  O("[[[5, 0], [0, 0], [0, 0]], [[6, 0], [0, 0], [0, 0]]]");
}
TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithVar3) {

  I(R"(     
            var y:int = 5
            var x : int[2][3][2] = [ y, [y + 1,y+2] ] 
            print(x)
            
        )");

  O("[[[5, 0], [0, 0], [0, 0]], [[6, 0], [7, 0], [0, 0]]]");
}

// Indexing

TEST_F(MultiDimContainer, 2DContainerIndexing) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
        print(x[0][0])
        
    )");

  O("1");
}

TEST_F(MultiDimContainer, 2DContainerIndexing2) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
        print(x[0][1])
        
    )");

  O("2");
}

// Indexing with variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithVar) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
        var y : int = 0
        print(x[y][y])
        
    )");

  O("1");
}

// Indexing 3D

TEST_F(MultiDimContainer, 3DContainerIndexing) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        print(x[0][0][0])
        
    )");

  O("1");
}

// Indexing 3D multiple

TEST_F(MultiDimContainer, 3DContainerIndexing2) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        print(x[0][0][1])
        
    )");

  O("2");
}

// Indexing 3D with variable

TEST_F(MultiDimContainer, 3DContainerIndexingWithVar) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        var y : int = 0
        print(x[y][y][y])
        
    )");

  O("1");
}

// Indexing 3D with variable y = 1

TEST_F(MultiDimContainer, 3DContainerIndexingWithVar2) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        var y : int = 1
        print(x[y][y][y])
        
    )");

  O("8");
}

// Indexing 2D when fill is used

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill) {
  I(R"(
        var x : int[2][2] = [ 2 fill 5 ] 
        print(x[0][0])
        
    )");

  O("5");
}

// Indexing 3D when fill is used

TEST_F(MultiDimContainer, 3DContainerIndexingWithFill) {
  I(R"(
        var x : int[2][2][2] = [ 2 fill 5 ] 
        print(x[0][0][0])
        
    )");

  O("5");
}

// Indexing 3D when fill is used dofferent index

TEST_F(MultiDimContainer, 3DContainerIndexingWithFill2) {
  I(R"(
        var x : int[2][2][2] = [ 2 fill 5 ] 
        print(x[1][1][1])
        
    )");

  O("0");
}

// Indexing 2D when fill is used different variable index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill2) {
  I(R"(
        var x : int[2][2] = [ 2 fill 5 ] 
        var y : int = 1
        print(x[y][y])
        
    )");

  O("0");
}

// Adding 2D containers values found using index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill3) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        print(x[y][y] + x[y][y])
        
    )");

  O("10");
}

// Updating 2D containers values found using index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill4) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        x[y][y] = 10
        print(x[y][y])
        
    )");

  O("10");
}

// Updating 2D containers values found using index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill5) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        x[y][y] = 10
        print(x)
        
    )");

  O("[[5, 5], [5, 10]]");
}

// Updating 2D containers values from another container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill6) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill 10 ] 
        x[y][y] = z[y][y]
        print(x)
        
    )");

  O("[[5, 5], [5, 10]]");
}

// Update and printing before and after

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill7) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill 10 ] 
        print(x)
        x[y][y] = z[y][y]
        print(x)
        
    )");

  O("[[5, 5], [5, 5]][[5, 5], [5, 10]]");
}

// Update and 2D container when init with fill and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill8) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill y ] 
        print(x)
        x[y][y] = z[y][y]
        print(x)
        
    )");

  O("[[5, 5], [5, 5]][[5, 5], [5, 1]]");
}

// Update and 2D container when init normal and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill9) {
  I(R"(
        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
        print(x)
        x[y][y] = z[y][y]
        print(x)
        print(z)     
    )");

  O("[[4, 0], [6, 0]][[4, 0], [6, 6]][[4, 1], [5, 6]]");
}

// Accessing 2D container using container of same dim directly

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill10) {
  I(R"(
        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
        print(x)
        x = z
        print(x)
        print(z)     
    )");

  O("[[4, 0], [6, 0]][[4, 1], [5, 6]][[4, 1], [5, 6]]");
}

// Accessing 2D container using container of with different dim directly 5x3 and
// rhs 2x3

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill11) {
  I(R"(
        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        x = z
        print(x)
        print(z)     
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, "
    "2], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

// Filling 2D container using fill of with different dim directly 5x3 and
// TODO: // rhs 2x3
// TEST_F(MultiDimContainer, 2DContainerIndexingWithFill12) {
//   I(R"(
//         var x : int[5][3] = [ 4, 6 ]
//         var y : int = 1
//         var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
//         print(x)
//         x = [ 2 fill 5 ]
//         print(x)
//         print(z)
//     )");

//   O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[5, 5, 5], [5,
//   5, "
//     "5], [5, 5, 5], [5, 5, 5], [5, 5, 5]][[4, 1, 1], [5, 6, 2]]");
// }

// For loop with 2D container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill13) {
  I(R"(
        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 1 {
                x[i][j] = z[i][j]
            }
        }
            
        
        print(x)
        print(z)     
    )");

  O("[[4, 0], [6, 0]][[4, 1], [5, 6]][[4, 1], [5, 6]]");
}

// For loop with 2D container with different dim

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill14) {
  I(R"(
        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 2 {
                x[i][j] = z[i][j]
            }
        }
            
        
        print(x)
        print(z)     
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, "
    "2], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

// For loop with 2D container with different dim and fill

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill15) {
  I(R"(
        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 2 {
                x[i][j] = 5
            }
        }
            
        
        print(x)
        print(z)     
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[5, 5, 5], [5, 5, "
    "5], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

// Container of containers
// TODO: Implement
// TEST_F(MultiDimContainer, 2DContainerIndexingWithFill16) {
//   I(R"(
//         var x : int[2][2] = [ 4, 6 ]
//         var y : int = 1
//         var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
//         var a : int[2][2][2] = [ x, z ]
//         print(a)
//         print(a[0][0][0])
//         print(a[1][1][1])
//         print(a[1][1][0])
//         print(a[1][0][1])
//         print(a[0][1][0])
//         print(a[0][0][1])
//         print(a[0][1][1])
//         print(a[1][0][0])
//     )");

//   O("[[[4, 0], [6, 0]], [[4, 1], [5, 6]]]4\n6\n6\n1\n0\n0\n0\n0\n");
// }

// Str container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill17) {
  I(R"(
        var x : str[2][2] = [ "4", "6" ]
        var y : int = 1
        var z : str[2][2] = [ [ "4", "y" ], [ "5", "6" ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
    )");

  O("[[4, ], [6, ]][[4, y], [5, 6]]464y56");
}

// Str container  with fill expression and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill18) {
  I(R"(
        var x : str[2][2] = [ "4", "6" ]
        var y : str[1][2] = [2 fill "Hello"]
        var z : str[2][2] = [ [ "4", "y" ], [ "5", "6" ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)
    )");

  O("[[4, ], [6, ]][[4, y], [5, 6]]464y56[[Hello, "
    "Hello]]");
}

// Deci Container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill19) {
  I(R"(
        var x : deci[2][2] = [ 4.0, 6.0 ]
        var y : deci = 1.0
        var z : deci[2][2] = [ [ 4.0, y ], [ 5.0, 6.0 ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
    )");

  O("[[4.00000000000000, 0.00000000000000], [6.00000000000000, "
    "0.00000000000000]][[4.00000000000000, 1.00000000000000], "
    "[5.00000000000000, "
    "6.00000000000000]]4.000000000000000.000000000000006.000000000000000."
    "000000000000004.000000000000001.000000000000005.000000000000006."
    "00000000000000");
}

// Deci Container  with fill expression and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill20) {
  I(R"(
        var x : deci[2][2] = [ 4.0, 6.0 ]
        var y : deci = 1.0
        var z : deci[2][2] = [ [ 4.0, y ], [ 5.0, 6.0 ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)
    )");

  O("[[4.00000000000000, 0.00000000000000], [6.00000000000000, "
    "0.00000000000000]][[4.00000000000000, 1.00000000000000], "
    "[5.00000000000000, "
    "6.00000000000000]]4.000000000000000.000000000000006.000000000000000."
    "000000000000004.000000000000001.000000000000005.000000000000006."
    "000000000000001.00000000000000");
}

// Bool Container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill21) {
  I(R"(
        var x : bool[2][2] = [ true, false ]
        var y : bool = true
        var z : bool[2][2] = [ [ true, y ], [ false, false ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
    )");

  O("[[true, false], [false, false]][[true, true], [false, "
    "false]]truefalsefalsefalsetruetruefalsefalse");
}

// Bool Container  with fill expression and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill22) {
  I(R"(
        var x : bool[2][2] = [ true, false ]
        var y : bool = true
        var z : bool[2][2] = [ [ true, y ], [ false, false ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)
    )");

  O("[[true, false], [false, false]][[true, true], [false, "
    "false]]truefalsefalsefalsetruetruefalsefalsetrue");
}

// SCOPE

TEST_F(MultiDimContainer, BasicContainerIntDeclarationLOCAL) {
  I("{var x:int[2] = [1,2] print(x)}");
  O("[1, 2]");
}

TEST_F(MultiDimContainer, BasicContainerIntDeclarationGL) {
  I("var x:int[2] = [1,2]{ print(x)}");
  O("[1, 2]");
}

TEST_F(MultiDimContainer, 2DContainerAssignmentLOCAL) {
  I(R"(   { var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] x[0][0] =
        5 print(x)} )");

  O("[[5, 2], [3, 4]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignmentGL) {
  I(R"(    var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ]{ x[0][0] =
        5 print(x)} )");

  O("[[5, 2], [3, 4]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2LOCAL) {
  I(R"(
 {       var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] x[0][1] =
        5 print(x) }
        
    )");

  O("[[1, 5], [3, 4]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2GL) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] {x[0][1] =
        5 print(x) }
        
    )");

  O("[[1, 5], [3, 4]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFillLOCAL) {
  I(R"(
{        var x : int[2][2] = [3 fill 4]
        print(x)}
        
    )");

  O("[[4, 4], [4, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFillGL) {
  I(R"(
        var x : int[2][2] = [3 fill 4]
  {      print(x)}
        
    )");

  O("[[4, 4], [4, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFill2LOCAL) {
  I(R"(
{        var x : int[2][5] = [5 fill 10]
        print(x)
        }
    )");

  O("[[10, 10, 10, 10, 10], [0, 0, 0, 0, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFill2GL) {
  I(R"(
        var x : int[2][5] = [5 fill 10]
      {  print(x)}
        
    )");

  O("[[10, 10, 10, 10, 10], [0, 0, 0, 0, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFillAllLOCAL) {
  I(R"(
{        var x : int[5][3] = [15 fill 2]
        print(x)
        }
    )");

  O("[[2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2]]");
}

TEST_F(MultiDimContainer, 2DContainerAssignment2WithFillAllGL) {
  I(R"(
        var x : int[5][3] = [15 fill 2]
{        print(x)}
        
    )");

  O("[[2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2], [2, 2, 2]]");
}

TEST_F(MultiDimContainer, 3DContainerAssignmentLOCAL) {
  I(R"(
{        var x : int[5][3][2] = [15 fill 2]
        print(x)
        }
    )");

  O("[[[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 0], [0, "
    "0]], [[0, 0], [0, 0], [0, 0]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerAssignmentGL) {
  I(R"(
        var x : int[5][3][2] = [15 fill 2]
        {print(x)}
        
    )");

  O("[[[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 0], [0, "
    "0]], [[0, 0], [0, 0], [0, 0]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerAssignmentAccessLOCAL) {
  I(R"(
{        var x : int[5][3][2] = [15 fill 2]
        x[0][0][0] = 5
        print(x)}
        
    )");

  O("[[[5, 2], [2, 2], [2, 2]], [[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 0], [0, "
    "0]], [[0, 0], [0, 0], [0, 0]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerAssignmentAccessGL) {
  I(R"(
        var x : int[5][3][2] = [15 fill 2]
      {  x[0][0][0] = 5}
        print(x)
        
    )");

  O("[[[5, 2], [2, 2], [2, 2]], [[2, 2], [2, 2], [2, 2]], [[2, 2], [2, 0], [0, "
    "0]], [[0, 0], [0, 0], [0, 0]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 2DContainerInitLOCAL) {
  I(R"(
{        var x : int[2][2] = [ [ 1, 2 ] ]
        print(x)}
        
    )");

  O("[[1, 2], [0, 0]]");
}
TEST_F(MultiDimContainer, 2DContainerInitGL) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ] ]
{        print(x)}
        
    )");

  O("[[1, 2], [0, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerInit2LOCAL) {
  I(R"(
{{        var x : int[2][2] = [ [ 1, 2 ],[ 3] ]
        print(x)}}
        
    )");

  O("[[1, 2], [3, 0]]");
}
TEST_F(MultiDimContainer, 2DContainerInit2GL) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ],[ 3] ]
{        print(x)}
        
    )");

  O("[[1, 2], [3, 0]]");
}

TEST_F(MultiDimContainer, 2DContainerInit2DiffDimLOCAL) {

  I(R"(
    {        var x : int[2][3] = [ [ 1, 2 ],[ 3, 4, 5] ]
            print(x)}
            
        )");

  O("[[1, 2, 0], [3, 4, 5]]");
}
TEST_F(MultiDimContainer, 2DContainerInit2DiffDimGL) {

  I(R"(
            var x : int[2][3] = [ [ 1, 2 ],[ 3, 4, 5] ]
    {        print(x)}
            
        )");

  O("[[1, 2, 0], [3, 4, 5]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillLOCAL) {

  I(R"(
{            var x : int[2][3][2] = [6 fill 5] 
            print(x)}
            
        )");

  O("[[[5, 5], [5, 5], [5, 5]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillGL) {

  I(R"(
            var x : int[2][3][2] = [6 fill 5] 
     {       print(x)}
            
        )");

  O("[[[5, 5], [5, 5], [5, 5]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillWithVarLOCAL) {

  I(R"(     
{            var y:int = 5
            var x : int[2][3][2] = [6 fill y] 
            print(x)}
            
        )");

  O("[[[5, 5], [5, 5], [5, 5]], [[0, 0], [0, 0], [0, 0]]]");
}
TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillWithVarGL) {

  I(R"(     
            var y:int = 5
    {        var x : int[2][3][2] = [6 fill y] 
            print(x)}
            
        )");

  O("[[[5, 5], [5, 5], [5, 5]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillWithVar2LOCAL) {

  I(R"(     
{            var y:int = 5
            var x : int[2][3][2] = [6 fill y + 1] 
            print(x)}
            
        )");

  O("[[[6, 6], [6, 6], [6, 6]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithFillWithVar2GL) {

  I(R"(     
            var y:int = 5
          {  var x : int[2][3][2] = [6 fill y + 1] 
            print(x)}
            
        )");

  O("[[[6, 6], [6, 6], [6, 6]], [[0, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithVar2LOCAL) {

  I(R"(     
  {          var y:int = 5
            var x : int[2][3][2] = [ y, y + 1 ] 
            print(x)}
            
        )");

  O("[[[5, 0], [0, 0], [0, 0]], [[6, 0], [0, 0], [0, 0]]]");
}
TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithVar2GL) {

  I(R"(     
            var y:int = 5
            var x : int[2][3][2] = [ y, y + 1 ] 
            print(x)
            
        )");

  O("[[[5, 0], [0, 0], [0, 0]], [[6, 0], [0, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithVar3LOCAL) {

  I(R"(     
{            var y:int = 5
            var x : int[2][3][2] = [ y, [y + 1,y+2] ] 
            print(x)}
            
        )");

  O("[[[5, 0], [0, 0], [0, 0]], [[6, 0], [7, 0], [0, 0]]]");
}

TEST_F(MultiDimContainer, 3DContainerInit2DiffDimWithVar3GL) {

  I(R"(     
            var y:int = 5
{            var x : int[2][3][2] = [ y, [y + 1,y+2] ] 
            print(x)}
            
        )");

  O("[[[5, 0], [0, 0], [0, 0]], [[6, 0], [7, 0], [0, 0]]]");
}

// Indexing

TEST_F(MultiDimContainer, 2DContainerIndexingLOCAL) {
  I(R"(
{        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
        print(x[0][0])}
        
    )");

  O("1");
}

TEST_F(MultiDimContainer, 2DContainerIndexingGL) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
{        print(x[0][0])}
        
    )");

  O("1");
}

TEST_F(MultiDimContainer, 2DContainerIndexing2LOCAL) {
  I(R"(
{        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
        print(x[0][1])
        }
    )");

  O("2");
}

TEST_F(MultiDimContainer, 2DContainerIndexing2GL) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
{        print(x[0][1])}
        
    )");

  O("2");
}

// Indexing with variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithVarLOCAL) {
  I(R"(
{        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
        var y : int = 0
        print(x[y][y])}
        
    )");

  O("1");
}

TEST_F(MultiDimContainer, 2DContainerIndexingWithVarGL) {
  I(R"(
        var x : int[2][2] = [ [ 1, 2 ], [ 3, 4 ] ] 
{        var y : int = 0
        print(x[y][y])}
        
    )");

  O("1");
}

// Indexing 3D

TEST_F(MultiDimContainer, 3DContainerIndexingLOCAL) {
  I(R"(
{        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        print(x[0][0][0])}
        
    )");

  O("1");
}
TEST_F(MultiDimContainer, 3DContainerIndexingGL) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        {print(x[0][0][0])}
        
    )");

  O("1");
}

// Indexing 3D multiple

TEST_F(MultiDimContainer, 3DContainerIndexing2LOCAL) {
  I(R"(
{        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        print(x[0][0][1])
        }
    )");

  O("2");
}

TEST_F(MultiDimContainer, 3DContainerIndexing2GL) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
{        print(x[0][0][1])}
        
    )");

  O("2");
}
// Indexing 3D with variable

TEST_F(MultiDimContainer, 3DContainerIndexingWithVarLOCAL) {
  I(R"(
{        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        var y : int = 0
        print(x[y][y][y])}
        
    )");

  O("1");
}
TEST_F(MultiDimContainer, 3DContainerIndexingWithVarGL) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        var y : int = 0
{        print(x[y][y][y])}
        
    )");

  O("1");
}

// Indexing 3D with variable y = 1

TEST_F(MultiDimContainer, 3DContainerIndexingWithVar2LOCAL) {
  I(R"(
{        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
        var y : int = 1
        print(x[y][y][y])}
        
    )");

  O("8");
}
TEST_F(MultiDimContainer, 3DContainerIndexingWithVar2GL) {
  I(R"(
        var x : int[2][2][2] = [ [ [ 1, 2 ], [ 3, 4 ] ], [ [ 5, 6 ], [ 7, 8 ] ] ] 
{        var y : int = 1
        print(x[y][y][y])}
        
    )");

  O("8");
}

// Indexing 2D when fill is used

TEST_F(MultiDimContainer, 2DContainerIndexingWithFillLOCAL) {
  I(R"(
{        var x : int[2][2] = [ 2 fill 5 ] 
        print(x[0][0])}
        
    )");

  O("5");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFillGL) {
  I(R"(
        var x : int[2][2] = [ 2 fill 5 ] 
     {   print(x[0][0])}
        
    )");

  O("5");
}

// Indexing 3D when fill is used

TEST_F(MultiDimContainer, 3DContainerIndexingWithFillLOCAL) {
  I(R"(
{        var x : int[2][2][2] = [ 2 fill 5 ] 
        print(x[0][0][0])
        }
    )");

  O("5");
}

TEST_F(MultiDimContainer, 3DContainerIndexingWithFillGL) {
  I(R"(
        var x : int[2][2][2] = [ 2 fill 5 ] 
{        print(x[0][0][0])
        }
    )");

  O("5");
}

// Indexing 3D when fill is used dofferent index

TEST_F(MultiDimContainer, 3DContainerIndexingWithFill2LOCAL) {
  I(R"(
{        var x : int[2][2][2] = [ 2 fill 5 ] 
        print(x[1][1][1])}
        
    )");

  O("0");
}
TEST_F(MultiDimContainer, 3DContainerIndexingWithFill2GL) {
  I(R"(
        var x : int[2][2][2] = [ 2 fill 5 ] 
{        print(x[1][1][1])}
        
    )");

  O("0");
}

// Indexing 2D when fill is used different variable index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill2LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 2 fill 5 ] 
        var y : int = 1
        print(x[y][y])}
        
    )");

  O("0");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill2GL) {
  I(R"(
        var x : int[2][2] = [ 2 fill 5 ] 
{        var y : int = 1
        print(x[y][y])}
        
    )");

  O("0");
}
// Adding 2D containers values found using index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill3LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        print(x[y][y] + x[y][y])}
        
    )");

  O("10");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill3GL) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        {var y : int = 1
        print(x[y][y] + x[y][y])}
        
    )");

  O("10");
}

// Updating 2D containers values found using index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill4LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        x[y][y] = 10
        print(x[y][y])}
        
    )");

  O("10");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill4GL) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
{        x[y][y] = 10
        print(x[y][y])}
        
    )");

  O("10");
}

// Updating 2D containers values found using index

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill5LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        x[y][y] = 10
        print(x)}
        
    )");

  O("[[5, 5], [5, 10]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill5GL) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
{        var y : int = 1
        x[y][y] = 10
        print(x)}
        
    )");

  O("[[5, 5], [5, 10]]");
}

// Updating 2D containers values from another container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill6LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill 10 ] 
        x[y][y] = z[y][y]
        print(x)}
        
    )");

  O("[[5, 5], [5, 10]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill6GL) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
{        var z : int[2][2] = [ 4 fill 10 ] 
        x[y][y] = z[y][y]
        print(x)}
        
    )");

  O("[[5, 5], [5, 10]]");
}

// Update and printing before and after

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill7LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill 10 ] 
        print(x)
        x[y][y] = z[y][y]
        print(x)}
        
    )");

  O("[[5, 5], [5, 5]][[5, 5], [5, 10]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill7GL) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill 10 ] 
{        print(x)
        x[y][y] = z[y][y]
        print(x)}
        
    )");

  O("[[5, 5], [5, 5]][[5, 5], [5, 10]]");
}

// Update and 2D container when init with fill and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill8LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill y ] 
        print(x)
        x[y][y] = z[y][y]
        print(x)}
        
    )");

  O("[[5, 5], [5, 5]][[5, 5], [5, 1]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill8GL) {
  I(R"(
        var x : int[2][2] = [ 4 fill 5 ] 
        var y : int = 1
        var z : int[2][2] = [ 4 fill y ] 
{        print(x)
        x[y][y] = z[y][y]
        print(x)}
        
    )");

  O("[[5, 5], [5, 5]][[5, 5], [5, 1]]");
}

// Update and 2D container when init normal and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill9LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
        print(x)
        x[y][y] = z[y][y]
        print(x)
        print(z)     }
    )");

  O("[[4, 0], [6, 0]][[4, 0], [6, 6]][[4, 1], [5, 6]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill9GL) {
  I(R"(
        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
 {       print(x)
        x[y][y] = z[y][y]
        print(x)
        print(z)     }
    )");

  O("[[4, 0], [6, 0]][[4, 0], [6, 6]][[4, 1], [5, 6]]");
}

// Accessing 2D container using container of same dim directly

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill10LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
        print(x)
        x = z
        print(x)
        print(z)    } 
    )");

  O("[[4, 0], [6, 0]][[4, 1], [5, 6]][[4, 1], [5, 6]]");
}

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill10GL) {
  I(R"(
        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
{        print(x)
        x = z
        print(x)
        print(z)  }   
    )");

  O("[[4, 0], [6, 0]][[4, 1], [5, 6]][[4, 1], [5, 6]]");
}

// Accessing 2D container using container of with different dim directly 5x3 and
// rhs 2x3

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill11LOCAL) {
  I(R"(
{        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        x = z
        print(x)
        print(z)     }
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, "
    "2], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill11GL) {
  I(R"(
        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
{        print(x)
        x = z
        print(x)
        print(z)  }   
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, "
    "2], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

// Filling 2D container using fill of with different dim directly 5x3 and
// TODO: // rhs 2x3
// TEST_F(MultiDimContainer, 2DContainerIndexingWithFill12) {
//   I(R"(
//         var x : int[5][3] = [ 4, 6 ]
//         var y : int = 1
//         var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
//         print(x)
//         x = [ 2 fill 5 ]
//         print(x)
//         print(z)
//     )");

//   O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[5, 5, 5], [5,
//   5, "
//     "5], [5, 5, 5], [5, 5, 5], [5, 5, 5]][[4, 1, 1], [5, 6, 2]]");
// }

// For loop with 2D container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill13LOCAL) {
  I(R"(
{        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 1 {
                x[i][j] = z[i][j]
            }
        }
            
        
        print(x)
        print(z)     }
    )");

  O("[[4, 0], [6, 0]][[4, 1], [5, 6]][[4, 1], [5, 6]]");
}

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill13GL) {
  I(R"(
        var x : int[2][2] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
{        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 1 {
                x[i][j] = z[i][j]
            }
        }
            
        
        print(x)}
        print(z)     
    )");

  O("[[4, 0], [6, 0]][[4, 1], [5, 6]][[4, 1], [5, 6]]");
}

// For loop with 2D container with different dim

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill14LOCAL) {
  I(R"(
{        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 2 {
                x[i][j] = z[i][j]
            }
        }
            
        
        print(x)
        print(z) }    
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, "
    "2], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill14GL) {
  I(R"(
        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
{        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 2 {
                x[i][j] = z[i][j]
            }
        }
            
        
        print(x)
        print(z)   }  
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, "
    "2], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

// For loop with 2D container with different dim and fill

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill15LOCAL) {
  I(R"(
{        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 2 {
                x[i][j] = 5
            }
        }
            
        
        print(x)
        print(z)     }
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[5, 5, 5], [5, 5, "
    "5], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill15GL) {
  I(R"(
        var x : int[5][3] = [ 4, 6 ]
        var y : int = 1
        var z : int[2][3] = [ [ 4, y, 1 ], [ 5, 6, 2 ] ]
{        print(x)
        for var i = 0 to 1 {
            for var j = 0 to 2 {
                x[i][j] = 5
            }
        }
            
        
        print(x)}
        print(z)     
    )");

  O("[[4, 0, 0], [6, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[5, 5, 5], [5, 5, "
    "5], [0, 0, 0], [0, 0, 0], [0, 0, 0]][[4, 1, 1], [5, 6, 2]]");
}

// Container of containers
// TODO: Implement
// TEST_F(MultiDimContainer, 2DContainerIndexingWithFill16) {
//   I(R"(
//         var x : int[2][2] = [ 4, 6 ]
//         var y : int = 1
//         var z : int[2][2] = [ [ 4, y ], [ 5, 6 ] ]
//         var a : int[2][2][2] = [ x, z ]
//         print(a)
//         print(a[0][0][0])
//         print(a[1][1][1])
//         print(a[1][1][0])
//         print(a[1][0][1])
//         print(a[0][1][0])
//         print(a[0][0][1])
//         print(a[0][1][1])
//         print(a[1][0][0])
//     )");

//   O("[[[4, 0], [6, 0]], [[4, 1], [5, 6]]]4\n6\n6\n1\n0\n0\n0\n0\n");
// }

// Str container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill17LOCAL) {
  I(R"(
{        var x : str[2][2] = [ "4", "6" ]
        var y : int = 1
        var z : str[2][2] = [ [ "4", "y" ], [ "5", "6" ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
    )");

  O("[[4, ], [6, ]][[4, y], [5, 6]]464y56");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill17GL) {
  I(R"(
        var x : str[2][2] = [ "4", "6" ]
        var y : int = 1
{        var z : str[2][2] = [ [ "4", "y" ], [ "5", "6" ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
    )");

  O("[[4, ], [6, ]][[4, y], [5, 6]]464y56");
}

// Str container  with fill expression and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill18LOCAL) {
  I(R"(
{        var x : str[2][2] = [ "4", "6" ]
        var y : str[1][2] = [2 fill "Hello"]
        var z : str[2][2] = [ [ "4", "y" ], [ "5", "6" ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)}
    )");

  O("[[4, ], [6, ]][[4, y], [5, 6]]464y56[[Hello, "
    "Hello]]");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill18GL) {
  I(R"(
        var x : str[2][2] = [ "4", "6" ]
        var y : str[1][2] = [2 fill "Hello"]
        var z : str[2][2] = [ [ "4", "y" ], [ "5", "6" ] ]
    {    print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
        print(y)
    )");

  O("[[4, ], [6, ]][[4, y], [5, 6]]464y56[[Hello, "
    "Hello]]");
}

// Deci Container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill19LOCAL) {
  I(R"(
{        var x : deci[2][2] = [ 4.0, 6.0 ]
        var y : deci = 1.0
        var z : deci[2][2] = [ [ 4.0, y ], [ 5.0, 6.0 ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
    )");

  O("[[4.00000000000000, 0.00000000000000], [6.00000000000000, "
    "0.00000000000000]][[4.00000000000000, 1.00000000000000], "
    "[5.00000000000000, "
    "6.00000000000000]]4.000000000000000.000000000000006.000000000000000."
    "000000000000004.000000000000001.000000000000005.000000000000006."
    "00000000000000");
}

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill19GL) {
  I(R"(
        var x : deci[2][2] = [ 4.0, 6.0 ]
        var y : deci = 1.0
        var z : deci[2][2] = [ [ 4.0, y ], [ 5.0, 6.0 ] ]
        print(x)
        print(z)
  {      print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
    )");

  O("[[4.00000000000000, 0.00000000000000], [6.00000000000000, "
    "0.00000000000000]][[4.00000000000000, 1.00000000000000], "
    "[5.00000000000000, "
    "6.00000000000000]]4.000000000000000.000000000000006.000000000000000."
    "000000000000004.000000000000001.000000000000005.000000000000006."
    "00000000000000");
}

// Deci Container  with fill expression and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill20LOCAL) {
  I(R"(
{        var x : deci[2][2] = [ 4.0, 6.0 ]
        var y : deci = 1.0
        var z : deci[2][2] = [ [ 4.0, y ], [ 5.0, 6.0 ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)}
    )");

  O("[[4.00000000000000, 0.00000000000000], [6.00000000000000, "
    "0.00000000000000]][[4.00000000000000, 1.00000000000000], "
    "[5.00000000000000, "
    "6.00000000000000]]4.000000000000000.000000000000006.000000000000000."
    "000000000000004.000000000000001.000000000000005.000000000000006."
    "000000000000001.00000000000000");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill20GL) {
  I(R"(
        var x : deci[2][2] = [ 4.0, 6.0 ]
        var y : deci = 1.0
        var z : deci[2][2] = [ [ 4.0, y ], [ 5.0, 6.0 ] ]
{        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)}
    )");

  O("[[4.00000000000000, 0.00000000000000], [6.00000000000000, "
    "0.00000000000000]][[4.00000000000000, 1.00000000000000], "
    "[5.00000000000000, "
    "6.00000000000000]]4.000000000000000.000000000000006.000000000000000."
    "000000000000004.000000000000001.000000000000005.000000000000006."
    "000000000000001.00000000000000");
}

// Bool Container

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill21LOCAL) {
  I(R"(
{        var x : bool[2][2] = [ true, false ]
        var y : bool = true
        var z : bool[2][2] = [ [ true, y ], [ false, false ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
    )");

  O("[[true, false], [false, false]][[true, true], [false, "
    "false]]truefalsefalsefalsetruetruefalsefalse");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill21GL) {
  I(R"(
        var x : bool[2][2] = [ true, false ]
        var y : bool = true
{        var z : bool[2][2] = [ [ true, y ], [ false, false ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])}
    )");

  O("[[true, false], [false, false]][[true, true], [false, "
    "false]]truefalsefalsefalsetruetruefalsefalse");
}

// Bool Container  with fill expression and variable

TEST_F(MultiDimContainer, 2DContainerIndexingWithFill22LOCAL) {
  I(R"(
{        var x : bool[2][2] = [ true, false ]
        var y : bool = true
        var z : bool[2][2] = [ [ true, y ], [ false, false ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)}
    )");

  O("[[true, false], [false, false]][[true, true], [false, "
    "false]]truefalsefalsefalsetruetruefalsefalsetrue");
}
TEST_F(MultiDimContainer, 2DContainerIndexingWithFill22GL) {
  I(R"(
        var x : bool[2][2] = [ true, false ]
{        var y : bool = true
        var z : bool[2][2] = [ [ true, y ], [ false, false ] ]
        print(x)
        print(z)
        print(x[0][0])
        print(x[0][1])
        print(x[1][0])
        print(x[1][1])
        print(z[0][0])
        print(z[0][1])
        print(z[1][0])
        print(z[1][1])
        print(y)}
    )");

  O("[[true, false], [false, false]][[true, true], [false, "
    "false]]truefalsefalsefalsetruetruefalsefalsetrue");
}

#endif