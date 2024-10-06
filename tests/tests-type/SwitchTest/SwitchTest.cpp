#include "SwitchTest.h"

void SwitchTest::SetUp() { _test->SetUp(); }

void SwitchTest::TearDown() { _test->TearDown(); }

TEST_F(SwitchTest, StringTest) {
  I(R"(
var a:str = "s"

switch a {
    case "s":{
    print("Print s")
    }
    case "d":{
    print("Print d")
    }default: { 
    print("default")

    }
}

    )");

  EXPECT_EQ(getOutput(), R"(Print s)");
}

TEST_F(SwitchTest, IntTest) {
  I(R"(
var a:int = 2

switch a {
    case 1:{
    print("Print 1")
    }
    case 2:{
    print("Print 2")
    }default: { 
    print("default")

    }
}   

    )");

  EXPECT_EQ(getOutput(), R"(Print 2)");
}

TEST_F(SwitchTest, DeciTest) {
  I(R"(
var a:deci = 2.0

switch a {
    case 1.0:{
    print("Print 1.0")
    }
    case 2.0:{
    print("Print 2.0")
    }default: { 
    print("default")

    }
}   

    )");

  EXPECT_EQ(getOutput(), R"(Print 2.0)");
}

TEST_F(SwitchTest, BoolTest) {
  I(R"(
var a:bool = true

switch a {
    case true:{
    print("Print true")
    }
    case false:{
    print("Print false")
    }default: { 
    print("default")

    }
}   

    )");

  EXPECT_EQ(getOutput(), R"(Print true)");
}

TEST_F(SwitchTest, NestedTest) {
  I(R"(
var a:int = 1

switch a {
    case 1:{
    print("Print 1")
    switch a {
        case 1:{
        print("Print 1")
        }
        case 2:{
        print("Print 2")
        }default: { 
        print("default")

        }
    }
    }
    case 2:{
    print("Print 2")
    }default: { 
    print("default")

    }
}


    )");

  EXPECT_EQ(getOutput(), R"(Print 1Print 1)");
}

TEST_F(SwitchTest, TrueTest) {
  I(R"(
var a:deci = 3.0

switch true {
    case a ==1.0:{
    print("Print 1.0")
    }
    case a == 2.0:{
    print("Print 2.0")
    }default: { 
    print("default")

    }
}   

    )");

  EXPECT_EQ(getOutput(), R"(default)");
}
TEST_F(SwitchTest, LocalTrueTest) {
  I(R"(
{
var a:deci = 3.0

switch true {
    case a ==1.0:{
    print("Print 1.0")
    }
    case a == 2.0:{
    print("Print 2.0")
    }default: { 
    print("default")

    }
}   
}
    )");

  EXPECT_EQ(getOutput(), R"(default)");
}
TEST_F(SwitchTest, SemiLocalTrueTest) {
  I(R"(
var a:deci = 3.0

{

switch true {
    case a ==1.0:{
    print("Print 1.0")
    }
    case a == 2.0:{
    print("Print 2.0")
    }default: { 
    print("default")

    }
}   
}
    )");

  EXPECT_EQ(getOutput(), R"(default)");
}
TEST_F(SwitchTest, ExpressionCaseTest) {
  I(R"(
var a:int = 4

switch a {
    case 1 + 2:{
    print("Print 3")
    }
    case 2 + 2:{
    print("Print 4")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Print 4)");
}

TEST_F(SwitchTest, ConstantExpressionTest) {
  I(R"(
const b:int = 2
var a:int = 2

switch a {
    case b:{
    print("Print constant 2")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Print constant 2)");
}

TEST_F(SwitchTest, DefaultFirstTest) {
  I(R"(
var a:int = 1

switch a {
    default: { 
    print("default")
    }
    case 1:{
    print("Print 1")
    }
    case 2:{
    print("Print 2")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Print 1)");
}

TEST_F(SwitchTest, NestedSwitchWithDefaultTest) {
  I(R"(
var a:int = 1
var b:int = 3

switch a {
    case 1:{
    print("Print 1")
    switch b {
        case 2:{
        print("Print 2")
        }
        default: { 
        print("Inner default")
        }
    }
    }
    case 2:{
    print("Print 2")
    }
    default: { 
    print("Outer default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Print 1Inner default)");
}

TEST_F(SwitchTest, EnumLikeTest) {
  I(R"(
const RED:int = 1
const GREEN:int = 2
const BLUE:int = 3

var color:int = 2

switch color {
    case RED:{
    print("Color is red")
    }
    case GREEN:{
    print("Color is green")
    }
    case BLUE:{
    print("Color is blue")
    }
    default: { 
    print("Unknown color")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Color is green)");
}

TEST_F(SwitchTest, EmptyCasesTest) {
  I(R"(
var a:int = 1

switch a {
    case 1:{
    }
    case 2:{
    print("Print 2")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"()");
}

TEST_F(SwitchTest, ReturnInSwitchTest) {
  I(R"(
fun testSwitch() -> str {
    var a:int = 1
    switch a {
        case 1:{
        return "Return 1"
        }
        case 2:{
        return "Return 2"
        }
        default: {
        return "default"
        }
    }
}

print(testSwitch())
    )");

  EXPECT_EQ(getOutput(), R"(Return 1)");
}

TEST_F(SwitchTest, MultipleConditionsTest) {
  I(R"(
var a:int = 5

switch true {
    case a > 0 && a < 10:{
    print("a is between 0 and 10")
    }
    case a > 10 && a < 20:{
    print("a is between 10 and 20")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a is between 0 and 10)");
}

TEST_F(SwitchTest, VariablesInCaseTest) {
  I(R"(
var a:int = 2
var b:int = 2

switch a {
    case b:{
    print("a matches b")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a matches b)");
}

TEST_F(SwitchTest, FunctionCallInCaseTest) {
  I(R"(
fun getValue() -> int {
    return 3
}

var a:int = 3

switch a {
    case getValue():{
    print("a matches getValue")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a matches getValue)");
}

TEST_F(SwitchTest, ComplexConditionTest) {
  I(R"(
var a:int = 4
var b:int = 2

switch true {
    case a % 2 == 0 && b % 2 == 0:{
    print("Both are even")
    }
    case a % 2 == 0 && b % 2 != 0:{
    print("a is even, b is odd")
    }
    case a % 2 != 0 && b % 2 == 0:{
    print("a is odd, b is even")
    }
    default: { 
    print("Both are odd")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Both are even)");
}

TEST_F(SwitchTest, DuplicateCaseTest) {
  I(R"(
var a:int = 3

switch a {
    case 3:{
    print("First case for 3")
    }
    case 3:{ 
    print("Second case for 3")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(First case for 3)");
}

TEST_F(SwitchTest, SwitchOnArrayElementTest) {
  I(R"(
var arr:int[3] = [10, 20, 30]
var index:int = 1

switch arr[index] {
    case 10:{
    print("Element is 10")
    }
    case 20:{
    print("Element is 20")
    }
    case 30:{
    print("Element is 30")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Element is 20)");
}

TEST_F(SwitchTest, MixedTypesSwitchTest) {
  I(R"(
var a:deci = 5.2

switch a {
    case 5:{
    print("a matches int 5")
    }
    case 5.2:{
    print("a matches deci 5.2")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a matches deci 5.2)");
}

TEST_F(SwitchTest, SideEffectsInCaseTest) {
  I(R"(
fun increment(x:int) -> int {
    return x + 1
}

var a:int = 2

switch increment(a) {
    case 2:{
    print("a is 2")
    }
    case 3:{
    print("a is 3")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a is 3)");
}

TEST_F(SwitchTest, BooleanConditionsInCaseTest) {
  I(R"(
var a:int = 5

switch true {
    case a > 3 && a < 7:{
    print("a is between 3 and 7")
    }
    case a == 5:{
    print("a is exactly 5")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a is between 3 and 7)");
}

TEST_F(SwitchTest, SwitchOnObjectPropertyTest) {
  I(R"(
type Person = { name: str, age: int }

var p: Person = { name: "Alice", age: 30 }

switch p.age {
    case 20:{
    print("Age is 20")
    }
    case 30:{
    print("Age is 30")
    }
    default: { 
    print("Unknown age")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Age is 30)");
}

TEST_F(SwitchTest, SwitchOnCharTest) {
  I(R"(
var ch:int8 = 'a'

switch ch {
    case 'a':{
    print("Character is a")
    }
    case 'b':{
    print("Character is b")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(Character is a)");
}

TEST_F(SwitchTest, NoMatchingCasesIntTest) {
  I(R"(
var a:int = 100

switch a {
    case 1:{
    print("Print 1")
    }
    case 2:{
    print("Print 2")
    }
    default: { 
    print("No match")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(No match)");
}

TEST_F(SwitchTest, FloatPrecisionSwitchTest) {
  I(R"(
var a:deci = 2.0000000001

switch a {
    case 2.0000000000:{
    print("a matches 2.0")
    }
    case 2.0000000001:{
    print("a matches 2.0000000001")
    }
    default: { 
    print("default")
    }
}
    )");

  EXPECT_EQ(getOutput(), R"(a matches 2.0000000001)");
}