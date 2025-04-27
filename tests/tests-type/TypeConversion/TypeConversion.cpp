#include "TypeConversion.h"

void TypeConversion::SetUp() { _test->SetUp(); }

void TypeConversion::TearDown() { _test->TearDown(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
// String Conversion Tests
TEST_F(TypeConversion, StringFromInt) {
  I(R"(print(String(2)))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, StringFromDouble) {
  I(R"(print(String(2.2)))");
  EXPECT_EQ(getOutput(), "2.20000000000000");
}

TEST_F(TypeConversion, StringFromDoubleD) {
  I(R"(print(String(2.2d)))");
  EXPECT_EQ(getOutput(), "2.20000004768372");
}

TEST_F(TypeConversion, StringFromChar) {
  I(R"(print(String('a')))");
  EXPECT_EQ(getOutput(), "97");
}

TEST_F(TypeConversion, StringFromBoolTrue) {
  I(R"(print(String(true)))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, StringFromBoolFalse) {
  I(R"(print(String(false)))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, StringNestedConversion) {
  I(R"(print(String(String("Hello"))))");
  EXPECT_EQ(getOutput(), "Hello");
}

TEST_F(TypeConversion, StringFromStringLiteral) {
  I(R"(print(String("Hello")))");
  EXPECT_EQ(getOutput(), "Hello");
}

TEST_F(TypeConversion, StringFromDivision) {
  I(R"(print(String(2 / 2)))");
  EXPECT_EQ(getOutput(), "1.00000000000000");
}

TEST_F(TypeConversion, StringFromNumericString) {
  I(R"(print(String("25")))");
  EXPECT_EQ(getOutput(), "25");
}

TEST_F(TypeConversion, StringFromDecimalString) {
  I(R"(print(String("25.2")))");
  EXPECT_EQ(getOutput(), "25.2");
}

// Int32 Conversion Tests
TEST_F(TypeConversion, Int32FromInt) {
  I(R"(print(Int32(2)))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromDouble) {
  I(R"(print(Int32(2.2)))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromDoubleD) {
  I(R"(print(Int32(2.2d)))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromTrue) {
  I(R"(print(Int32(true)))");
  EXPECT_EQ(getOutput(), "1");
}

TEST_F(TypeConversion, Int32FromFalse) {
  I(R"(print(Int32(false)))");
  EXPECT_EQ(getOutput(), "0");
}

TEST_F(TypeConversion, Int32FromDecimalString) {
  I(R"(print(Int32("2.7")))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromDecimalDString) {
  I(R"(print(Int32("2.7d")))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromInvalidString) {
  I(R"(print(Int32("S")))");
  EXPECT_EQ(getOutput(), "0");
}

TEST_F(TypeConversion, Int32FromChar) {
  I(R"(print(Int32('a')))");
  EXPECT_EQ(getOutput(), "97");
}

TEST_F(TypeConversion, Int32FromEmptyString) {
  I(R"(print(Int32("")))");
  EXPECT_EQ(getOutput(), "0");
}

// Decimal32 Conversion Tests
TEST_F(TypeConversion, Decimal32FromInt) {
  I(R"(print(Decimal32(2)))");
  EXPECT_EQ(getOutput(), "2.0000000");
}

TEST_F(TypeConversion, Decimal32FromDouble) {
  I(R"(print(Decimal32(2.2)))");
  EXPECT_EQ(getOutput(), "2.2000000");
}

TEST_F(TypeConversion, Decimal32FromString) {
  I(R"(print(Decimal32("2.5")))");
  EXPECT_EQ(getOutput(), "2.5000000");
}

TEST_F(TypeConversion, Decimal32FromTrue) {
  I(R"(print(Decimal32(true)))");
  EXPECT_EQ(getOutput(), "1.0000000");
}

TEST_F(TypeConversion, Decimal32FromFalse) {
  I(R"(print(Decimal32(false)))");
  EXPECT_EQ(getOutput(), "0.0000000");
}

TEST_F(TypeConversion, Decimal32FromInvalidString) {
  I(R"(print(Decimal32("S")))");
  EXPECT_EQ(getOutput(), "0.0000000");
}

TEST_F(TypeConversion, Decimal32FromChar) {
  I(R"(print(Decimal32('a')))");
  EXPECT_EQ(getOutput(), "97.0000000");
}

TEST_F(TypeConversion, Decimal32FromDoubleD) {
  I(R"(print(Decimal32(2.2d)))");
  EXPECT_EQ(getOutput(), "2.2000000");
}

TEST_F(TypeConversion, Decimal32FromEmptyString) {
  I(R"(print(Decimal32("")))");
  EXPECT_EQ(getOutput(), "0.0000000");
}

// Decimal Conversion Tests
TEST_F(TypeConversion, DecimalFromInt) {
  I(R"(print(Decimal(2)))");
  EXPECT_EQ(getOutput(), "2.00000000000000");
}

TEST_F(TypeConversion, DecimalFromDouble) {
  I(R"(print(Decimal(2.2)))");
  EXPECT_EQ(getOutput(), "2.20000000000000");
}

TEST_F(TypeConversion, DecimalFromString) {
  I(R"(print(Decimal("2.5")))");
  EXPECT_EQ(getOutput(), "2.50000000000000");
}

TEST_F(TypeConversion, DecimalFromTrue) {
  I(R"(print(Decimal(true)))");
  EXPECT_EQ(getOutput(), "1.00000000000000");
}

TEST_F(TypeConversion, DecimalFromFalse) {
  I(R"(print(Decimal(false)))");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

TEST_F(TypeConversion, DecimalFromInvalidString) {
  I(R"(print(Decimal("S")))");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

TEST_F(TypeConversion, DecimalFromChar) {
  I(R"(print(Decimal('a')))");
  EXPECT_EQ(getOutput(), "97.00000000000000");
}

TEST_F(TypeConversion, DecimalFromEmptyString) {
  I(R"(print(Decimal("")))");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

TEST_F(TypeConversion, DecimalFromDoubleD) {
  I(R"(print(Decimal(2.2d)))");
  EXPECT_EQ(getOutput(), "2.20000004768372");
}

// Bool Conversion Tests
TEST_F(TypeConversion, BoolFromNonZeroInt) {
  I(R"(print(Bool(2)))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromZeroInt) {
  I(R"(print(Bool(0)))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, BoolFromNonZeroDouble) {
  I(R"(print(Bool(2.2)))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromZeroDouble) {
  I(R"(print(Bool(0.0)))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, BoolFromNumericString) {
  I(R"(print(Bool("2")))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromZeroString) {
  I(R"(print(Bool("0")))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromNonNumericString) {
  I(R"(print(Bool("S")))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromChar) {
  I(R"(print(Bool('a')))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromTrueLiteral) {
  I(R"(print(Bool(true)))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromFalseLiteral) {
  I(R"(print(Bool(false)))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, BoolFromEmptyString) {
  I(R"(print(Bool("")))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, BoolFromDoubleDNonZero) {
  I(R"(print(Bool(2.2d)))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromDoubleDZero) {
  I(R"(print(Bool(0.0d)))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, BoolFromHelloString) {
  I(R"(print(Bool("Hello")))");
  EXPECT_EQ(getOutput(), "true");
}

// Int8 Conversion Test (existing example)
TEST_F(TypeConversion, Int8Conversion) {
  I(R"(
    var x:int8 = Int8(65)
    print(x)
  )");
  EXPECT_EQ(getOutput(), "A");
}
// Inter Explicit Conversion Tests
// String to Int32 conversions
TEST_F(TypeConversion, Int32FromStringOfInt) {
  I(R"(print(Int32(String(2))))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromStringOfDouble) {
  I(R"(print(Int32(String(2.2))))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromStringOfDoubleD) {
  I(R"(print(Int32(String(2.2d))))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, Int32FromStringOfTrue) {
  I(R"(print(Int32(String(true))))");
  EXPECT_EQ(getOutput(), "0");
}

TEST_F(TypeConversion, Int32FromStringOfChar) {
  I(R"(print(Int32(String('a'))))");
  EXPECT_EQ(getOutput(), "97");
}

TEST_F(TypeConversion, Int32FromStringOfNumericString) {
  I(R"(print(Int32(String("25"))))");
  EXPECT_EQ(getOutput(), "25");
}

// String to Decimal32 conversions
TEST_F(TypeConversion, Decimal32FromStringOfDouble) {
  I(R"(print(Decimal32(String(2.2))))");
  EXPECT_EQ(getOutput(), "2.2000000");
}

TEST_F(TypeConversion, Decimal32FromStringOfDoubleD) {
  I(R"(print(Decimal32(String(2.2d))))");
  EXPECT_EQ(getOutput(), "2.2000000");
}

TEST_F(TypeConversion, Decimal32FromStringOfChar) {
  I(R"(print(Decimal32(String('a'))))");
  EXPECT_EQ(getOutput(), "97.0000000");
}

TEST_F(TypeConversion, Decimal32FromStringOfDecimalString) {
  I(R"(print(Decimal32(String("25.2"))))");
  EXPECT_EQ(getOutput(), "25.2000008");
}

// String to Decimal conversions
TEST_F(TypeConversion, DecimalFromStringOfDouble) {
  I(R"(print(Decimal(String(2.2))))");
  EXPECT_EQ(getOutput(), "2.20000000000000");
}

TEST_F(TypeConversion, DecimalFromStringOfDoubleD) {
  I(R"(print(Decimal(String(2.2d))))");
  EXPECT_EQ(getOutput(), "2.20000004768372");
}

TEST_F(TypeConversion, DecimalFromStringOfChar) {
  I(R"(print(Decimal(String('a'))))");
  EXPECT_EQ(getOutput(), "97.00000000000000");
}

TEST_F(TypeConversion, DecimalFromStringOfDecimalString) {
  I(R"(print(Decimal(String("25.2"))))");
  EXPECT_EQ(getOutput(), "25.20000000000000");
}

// String to Bool conversions
TEST_F(TypeConversion, BoolFromStringOfZeroDouble) {
  I(R"(print(Bool(String(0.0))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromStringOfFalse) {
  I(R"(print(Bool(String(false))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromStringOfEmpty) {
  I(R"(print(Bool(String(""))))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, BoolFromStringOfZeroString) {
  I(R"(print(Bool(String("0"))))");
  EXPECT_EQ(getOutput(), "true");
}

// String to Int8 conversions

// Multi-step conversions
TEST_F(TypeConversion, DecimalFromStringOfBool) {
  I(R"(print(Decimal(String(true))))");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

TEST_F(TypeConversion, BoolFromStringOfDecimal) {
  I(R"(print(Bool(String(0.00000000000000))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, NestedStringConversions) {
  I(R"(print(String(Decimal32(Int32("12.3")))))");
  EXPECT_EQ(getOutput(), "12.00000000000000");
}

TEST_F(TypeConversion, WithFunctions) {
  I(R"(
  fun getD(s: str) -> str {
  return "2.3"
}


fun getC(d: deci32) -> str {
  return "100"
}

print(1, "\n")
print("H", 2.5, false, "\n")
print(Int32(String(2)), "\n")
print(getD("H"), "\n")
print((getD(getC(Decimal32(String(2.2d))))), "\n")
print(String(Int32("2")))
print(String(2.2d))
  )");
  EXPECT_EQ(getOutput(), R"(1
H2.50000000000000false
2
2.3
2.3
22.20000004768372)");
}
#endif // __TYPE_CONVERSION_H__