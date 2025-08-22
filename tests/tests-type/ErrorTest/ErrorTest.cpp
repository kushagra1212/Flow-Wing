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


#include "ErrorTest.h"
#include "../../../src/diagnostics/Diagnostic/DiagnosticCodeData.h"

void ErrorTest::SetUp() { _test->SetUp(true); }

void ErrorTest::TearDown() { _test->TearDown(); }

TEST_F(ErrorTest, PassingByReferenceWithAsKeywordIsNotAllowed) {
  IE(R"(
fun testFun(inout a: as int) -> nthg {
  print(a, "\n")
  a = 30 
  print(a, "\n")
}

var x:int  = 20
testFun(x)
  )");

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                        PassingByReferenceWithAsKeywordIsNotAllowed);
}

TEST_F(ErrorTest, PassingNonArrayVariableToFunctionThatExpectsArray) {
  IE(R"(
fun testFun(x: int[2]) -> nthg {
  print(x, "\n")
}

var y: int = 2
testFun(y)
  )");

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                        VariablePassedAsAnArgumentToFunctionIsNotAnArray);
}

TEST_F(ErrorTest, PassingArrayOfDifferentTypeToFunctionThatExpectsArray) {
  IE(R"(

fun testFun(x: int[2]) -> nthg {
  print(x, "\n")
}

var y: deci[3] = [1.0, 2.0, 3.0]
testFun(y)
  )");

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                        ArrayPassedInFunctionArgumentMismatch);
}

TEST_F(
    ErrorTest,
    ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeAndHavingSameDimensionButSizeMismatch) {
  IE(R"(

fun testFun(x: int[2]) -> nthg {
  print(x, "\n")
}

var y: int[3] = [1, 2]
testFun(y)
  )");

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::
          ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeAndHavingSameDimensionButSizeMismatch);
}

TEST_F(
    ErrorTest,
    ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeButArrayDimensionMismatch) {
  IE(R"(
fun testFun(x: int[2]) -> nthg {
  print(x, "\n")
}

var y: int[2][3] = [[1, 2, 3], [4, 5, 6]]
testFun(y)
  )");

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::
          ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeButArrayDimensionMismatch);
}

TEST_F(ErrorTest, FunctionArgumentCountMismatch) {
  IE(R"(
  
  fun testFun(x: int[2], y: int) -> nthg {
  print(x, "\n")
}

var y: int[2] = [1, 2]
testFun(y)
  )");

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::FunctionArgumentCountMismatch);
}

TEST_F(ErrorTest, UnexpectedTypeExpression) {
  IE(R"(
  var x: 
  )");

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedTypeExpression);
}

TEST_F(ErrorTest, UnexpectedToken) {
  IE(R"(
  var x: int = fun
  )");

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken);
}

TEST_F(ErrorTest, UnexpectedTokenInBringStatement) {
  IE(R"(
bring {a
  )");

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken);
}

TEST_F(ErrorTest, UnexpectedTokenInBringStatementExpectedStringToken) {
  IE(R"(
bring {a} from 
  )");

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken);
}

TEST_F(ErrorTest, ModuleNotFound) {
  writeFile("test2-module.fg", R"(module [test2]

    var x:int = 2

 fun main2(x:int,s:str) -> nthg {
    print("Printing from Module Test "+x+s)
}
  )");

  writeFile("temp2.fg", R"(
bring test3

test2::main2(2,"s")
  )");

  std::system(createBuildAndRunCmd("temp2.fg").c_str());

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleNotFound);
}

TEST_F(ErrorTest, CircularReference) {
  writeFile("test1.fg", R"(
  bring "test2.fg"

  )");

  writeFile("test2.fg", R"(
bring "test1.fg"

  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::CircularReference);
}

TEST_F(ErrorTest, PassingObjectToFunctionWithDynamicParam) {
  IE(R"(
fun testFun(a) -> nthg {
  print(a, "\n")
}

type Test = {
  x: int,
  y: str,
  z: deci,
  w: deci32,
  v: bool,
}
var t: Test = {
  x: 10,
  y: "Hello",
  z: 10.2,
  w: 10.2d,
  v: true
}

testFun(t)
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::PassingMismatchedTypeToFunction);
}
TEST_F(ErrorTest, PassingArrayToFunctionWithDynamicParam) {
  IE(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
}

var a: int[5] = [1, 2]
testFun(a)
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::PassingMismatchedTypeToFunction);
}

TEST_F(ErrorTest, PassingArrayInitializerToDynamicType) {
  IE(R"(
var a = [1, 2]
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ArrayInitializerNotAllowedForDynamicType);
}

TEST_F(ErrorTest, PassingObjectInitializerToDynamicType) {
  IE(R"(
var a = {x:10}
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ObjectInitializerNotAllowedForDynamicType);
}

TEST_F(ErrorTest, PassingObjectToFunction) {
  IE(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
}

testFun({
  x: 2
})
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::PassingObjectToNonObjectParam);
}

TEST_F(ErrorTest, PassingArrayToFunction) {
  IE(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
}

testFun([2,3,4])
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::PassingArrayToNonArrayParam);
}

TEST_F(ErrorTest, InvalidAssignmentToConstantVariable) {
  IE(R"(
const x: int = 2

x=2
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::InvalidAssignmentToConstantVariable);
}
TEST_F(ErrorTest, InvalidAssignmentToConstantVariableInsideScope) {
  IE(R"(
const x: int = 2
{

x=2
}
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::InvalidAssignmentToConstantVariable);
}

TEST_F(ErrorTest, SuperCallOutsideConstructor) {
  IE(R"(
super()
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::SuperCallOutsideConstructor);
}

TEST_F(ErrorTest, InvalidInitFunctionCall) {
  IE(R"(
init()
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::InvalidInitFunctionCall);
}

TEST_F(ErrorTest, InitFunctionCallInMemberFunctionWithSelf) {
  IE(R"(
class A {
  init() -> nthg {
  }
  getX() -> int {
    self.init()
    return 2
  }
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::InvalidInitFunctionCall);
}

TEST_F(ErrorTest, InitFunctionCallInMemberFunctionWithOutSelf) {
  IE(R"(

class A {
  init() -> nthg {
  }
  getX() -> int {
    init()
    return 2
  }
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::InvalidInitFunctionCall);
}

TEST_F(ErrorTest, IncorrectArgumentCount) {
  IE(R"(
var age: int = Int32(2.2,2)

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::IncorrectArgumentCount);
}

TEST_F(ErrorTest, ClassMissingSuperclass) {
  IE(R"(
class A {
  init() -> nthg {
    super()
  }


}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ClassMissingSuperclass);
}

TEST_F(ErrorTest, ClassMissingInitializer) {
  IE(R"(
class A {
}

var a:A = new A()

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ClassMissingInitializer);
}

TEST_F(ErrorTest, FunctionNotFound) {
  IE(R"(
A()
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::FunctionNotFound);
}

TEST_F(ErrorTest, VariableNotFoundInIndexExpression) {
  IE(R"(
x[0]
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableNotFound);
}

TEST_F(ErrorTest, IndexingNonArrayVariable) {
  IE(R"(
var x:int = 2
print(x[0])
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::IndexingNonArrayVariable);
}

TEST_F(ErrorTest, TypeOrClassNotFound) {
  IE(R"(
var x:Test = 2
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::TypeOrClassNotFound);
}

TEST_F(ErrorTest, VariableNotFoundBasic) {
  IE(R"(
print(x)
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableNotFound);
}

TEST_F(ErrorTest, FunctionAlreadyDeclared) {
  IE(R"(

fun test2() -> nthg {
}


fun test2() -> nthg {
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::FunctionAlreadyDeclared);
}

TEST_F(ErrorTest, MemberFunctionOfClassAlreadyDeclared) {
  IE(R"(
class A {
  init() -> nthg {
  }


  test2() -> nthg {
    print("Hello from A")
  }

  test2() -> nthg {
  }
  }

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::MemberFunctionOfClassAlreadyDeclared);
}

TEST_F(ErrorTest, FunctionNameConflictsWithBuiltin) {
  IE(R"(
fun Int32()->nthg{
    
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::FunctionNameConflictsWithBuiltin);
}

TEST_F(ErrorTest, MissingDefaultValueForOptionalParameter) {
  IE(R"(
fun test2(a: int, b: str, c: int = 3, d) -> nthg {
  print("A ", a, "\n")
  print("B ", b, "\n")
  print("C ", c, "\n")
}

test2(2, "3", 2)

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::MissingDefaultValueForOptionalParameter);
}

TEST_F(ErrorTest, InvalidBreakStatementUsage) {
  IE(R"(
{break}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::InvalidBreakStatementUsage);
}

TEST_F(ErrorTest, FileNotFound) {
  IE(R"(
bring "ssssswwwwxdwd.fg"

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::FileNotFound);
}
TEST_F(ErrorTest, IdentifierNotFoundInFileOrModule) {
  writeFile("test1.fg", R"(


  )");

  writeFile("test2.fg", R"(
bring {xx} from "test1.fg"

  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::IdentifierNotFoundInFileOrModule);
}

TEST_F(ErrorTest, ModuleAlreadyDeclared) {
  writeFile("test1-module.fg", R"(
module [test1]


var x:int

  )");

  writeFile("test2.fg", R"(
bring test1
bring test1

  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleAlreadyDeclared);
}

TEST_F(ErrorTest, ModuleAlreadyDeclaredWithFullName) {
  writeFile("test1-module.fg", R"(
module [test1]


var x:int

  )");

  writeFile("test2.fg", R"(
bring "test1-module.fg"
bring test1

  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleAlreadyDeclared);
}

TEST_F(ErrorTest, ModuleAlreadyDeclaredWithFullName2) {
  writeFile("test1-module.fg", R"(
module [test1]


var x:int

  )");

  writeFile("test2.fg", R"(
bring "test1-module.fg"
bring "test1-module.fg"

  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleAlreadyDeclared);
}

TEST_F(ErrorTest, FunctionAlreadyDeclaredBringTest) {
  writeFile("test1.fg", R"(
var xx: int = 2

fun helloWorld() -> nthg {
  print("Hello World From test1")
}

  )");

  writeFile("test2.fg", R"(
fun helloWorld() -> nthg {
  print("Hello World From Current")
}

bring "test1.fg"
helloWorld()
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::FunctionAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredBringTest) {
  writeFile("test1.fg", R"(
var xx: int = 2


  )");

  writeFile("test2.fg", R"(
var xx: int = 2
bring "test1.fg"
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, TypeAlreadyDeclaredBringTest) {
  writeFile("test1.fg", R"(
type T = {
  a: int,
  c: str,
  d: deci
}


  )");

  writeFile("test2.fg", R"(

type T = {
  a: int,
  c: str,
  d: deci
}
bring "test1.fg"
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(FLOW_WING::DIAGNOSTIC::DiagnosticCode::TypeAlreadyDeclared);
}

TEST_F(ErrorTest, ClassAlreadyDeclaredBringTest) {
  writeFile("test1.fg", R"(
class A {
  init() -> nthg {
  }


}

  )");

  writeFile("test2.fg", R"(
class A {
  init() -> nthg {
  }


}
bring "test1.fg"
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassAlreadyDeclared);
}

TEST_F(ErrorTest, ClassAlreadyDeclaredBringTest2) {
  writeFile("test1.fg", R"(
class A {
  init() -> nthg {
  }


}

  )");

  writeFile("test2.fg", R"(

bring "test1.fg"
class A {
  init() -> nthg {
  }


}
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassAlreadyDeclared);
}

TEST_F(ErrorTest, ParentClassNotFound) {
  IE(R"(
class A extends B {
  init() -> nthg  {


  }
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ParentClassNotFound);
}

TEST_F(ErrorTest, ContinueStatementOutsideOfLoop) {
  IE(R"(
{continue}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ContinueStatementOutsideOfLoop);
}

TEST_F(ErrorTest, DuplicateAttributeKeyInCustomType) {
  IE(R"(
type CustomType1 = {
  a: int,
  b: int,
  a:int
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::DuplicateAttributeKeyInCustomType);
}

TEST_F(ErrorTest, DuplicateCustomTypeDeclaration) {
  IE(R"(
type CustomType1 = {
  a: int,
  b: int,
}
type CustomType1 = {
  a: int,
  b: int,
}


  )");

  EXPECT_ERROR_CODE(DiagnosticCode::DuplicateCustomTypeDeclaration);
}

TEST_F(ErrorTest, DuplicateModuleDeclaration) {
  IE(R"(
var x = 2 + 2
module [My_Module_3]


module [My_Module_3]



  )");

  EXPECT_ERROR_CODE(DiagnosticCode::DuplicateModuleDeclaration);
}

TEST_F(ErrorTest, ReturnStatementOutsideOfFunction) {
  IE(R"(
return :

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ReturnStatementOutsideOfFunction);
}

TEST_F(ErrorTest, ReturnStatementOutsideOfFunctionInsideBlock) {
  IE(R"(
{
    return :
}
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::ReturnStatementOutsideOfFunction);
}

TEST_F(ErrorTest, NoDefaultCaseInSwitchStatement) {
  IE(R"(

    switch 2 {
      case 0 : {
        print("a is 0")
      }
      case 1 : {
        print("a is 1")
      }
      case 2 : {
        print("a is 2")
      }
      case 3 : {
        print("a is 3")
      }
      case "Hello" : {
        print("a is Hello")
      }
    }
    
    
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::NoDefaultCaseInSwitchStatement);
}

TEST_F(ErrorTest, MoreThanOneDefaultCaseInSwitchStatement) {
  IE(R"(

 
switch 2 {
  case 0 : {
    print("a is 0")
  }
  case 1 : {
    print("a is 1")
  }
  case 2 : {
    print("a is 2")
  }
  case 3 : {
    print("a is 3")
  }
  case "Hello" : {
    print("a is Hello")
  }
  default : {
    print("default 1")
  }
  default : {
    print("default 2")
  }
}


  )");

  EXPECT_ERROR_CODE(DiagnosticCode::MoreThanOneDefaultCaseInSwitchStatement);
}

TEST_F(ErrorTest, NoCaseStatementInSwitchStatement) {
  IE(R"(
 
switch 2 {
  default:{}
}

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::NoCaseStatementInSwitchStatement);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredGlobalTest) {
  IE(R"(
 
var x = 2

var x =2
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredGlobalConstTest) {
  IE(R"(
 
var x = 2

const x =2
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredGlobalConstTest2) {
  IE(R"(
 
const x =3

const x =2
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredGlobalTestDifferentType) {
  IE(R"(
 
var x = 2

var x = "D"
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredGlobalTestDifferentType2) {
  IE(R"(
 
var x:int = 2

var x = "D"
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredGlobalTestDifferentType3) {
  IE(R"(
 
var x:int = 2

var x:deci = 2.0
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, VariableAlreadyDeclaredLocalTest) {
  IE(R"(
{

var x = 2

var x =2    
}
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::VariableAlreadyDeclared);
}

TEST_F(ErrorTest, UnTerminatedSingleQuote) {
  IE(R"(
    '
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::UnTerminatedSingleQuote);
}

TEST_F(ErrorTest, UnTerminatedSingleQuoteVariableDeclaration) {
  IE(R"(
var x='
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::UnTerminatedSingleQuote);
}

TEST_F(ErrorTest, BadCharacterEscapeSequence) {
  IE(R"(
var x = '\j'
print(x)

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::BadCharacterEscapeSequence);
}

TEST_F(ErrorTest, NumberTooLargeForInt) {
  IE(R"(
var x: int = 100000000000000000000
print(x)
       
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::NumberTooLargeForInt);
}

TEST_F(ErrorTest, UnTerminatedStringLiteral) {
  IE(R"(
"

       
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::UnTerminatedStringLiteral);
}

TEST_F(ErrorTest, UnTerminatedStringLiteralWithPrint) {
  IE(R"(
print("

       
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::UnTerminatedStringLiteral);
}

TEST_F(ErrorTest, BadCharacterEscapeSequenceInStringLiteral) {
  IE(R"(
"\e"
       
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::BadCharacterEscapeSequenceInStringLiteral);
}

TEST_F(ErrorTest, BadCharacterInput) {
  IE(R"(
sss@
  )");

  EXPECT_ERROR_CODE(DiagnosticCode::BadCharacterInput);
}

TEST_F(ErrorTest, UnTerminatedTemplateStringLiteral) {
  IE(R"(
var s = `

This is the template string


Very long string


                funny string

weird string
{char}



print(s)

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::UnTerminatedTemplateStringLiteral);
}

TEST_F(ErrorTest, UnTerminatedTemplateStringLiteral2) {
  IE(R"(
var s = `

This is the template string


Very long string


                funny string

weird string
{char}

``

print(s)

  )");

  EXPECT_ERROR_CODE(DiagnosticCode::UnTerminatedTemplateStringLiteral);
}