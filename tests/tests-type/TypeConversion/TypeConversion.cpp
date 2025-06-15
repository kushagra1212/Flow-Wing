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
    var x:char = Int8(65)
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
// String to Int32 additional cases
TEST_F(TypeConversion, Int32FromStringOfNegativeInt) {
  I(R"(print(Int32(String(-5))))");
  EXPECT_EQ(getOutput(), "-5");
}

TEST_F(TypeConversion, Int32FromStringOfBooleanFalse) {
  I(R"(print(Int32(String(false))))");
  EXPECT_EQ(getOutput(), "0");
}

TEST_F(TypeConversion, Int32FromStringWithWhitespace) {
  I(R"(print(Int32(String("  42  "))))");
  EXPECT_EQ(getOutput(), "42");
}

// String to Decimal32 additional cases
TEST_F(TypeConversion, Decimal32FromStringOfScientificNotation) {
  I(R"(print(Decimal32(String("2.5e1"))))");
  EXPECT_EQ(getOutput(), "25.0000000");
}

TEST_F(TypeConversion, Decimal32FromStringOfNegativeDecimal) {
  I(R"(print(Decimal32(String(-1 * 3.14))))");
  EXPECT_EQ(getOutput(), "-3.1400001");
}

// String to Decimal additional cases
TEST_F(TypeConversion, DecimalFromStringOfHighPrecision) {
  I(R"(print(Decimal(String("123.456789012345"))))");
  EXPECT_EQ(getOutput(), "123.45678901234500");
}

TEST_F(TypeConversion, DecimalFromStringOfBooleanString) {
  I(R"(print(Decimal(String("true"))))");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

// String to Bool additional cases
TEST_F(TypeConversion, BoolFromStringOfTrueString) {
  I(R"(print(Bool(String("true"))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, BoolFromStringOfFalseString) {
  I(R"(print(Bool(String("false"))))");
  EXPECT_EQ(getOutput(), "true"); // Non-empty string is true
}

TEST_F(TypeConversion, BoolFromStringOfWhitespace) {
  I(R"(print(Bool(String("   "))))");
  EXPECT_EQ(getOutput(), "true"); // Non-empty string
}

// String to Int8 additional cases
TEST_F(TypeConversion, Int8FromStringOfNegativeNumber) {
  I(R"(print(Int8(String(-1*90))))");
  EXPECT_EQ(getOutput(),
            std::string(1, static_cast<char>(
                               166))); // Depends on signed char representation
}

TEST_F(TypeConversion, Int8FromStringOfOverflowNumber) {
  I(R"(print(Int8(String(300))))");
  EXPECT_EQ(getOutput(), std::string(1, static_cast<char>(300 % 256)));
}

// Multi-step conversion chains
TEST_F(TypeConversion, Decimal32FromIntViaString) {
  I(R"(print(Decimal32(String(Int32("42")))))");
  EXPECT_EQ(getOutput(), "42.0000000");
}

TEST_F(TypeConversion, BoolFromDecimalViaString) {
  I(R"(print(Bool(String(Decimal(0.0)))))");
  EXPECT_EQ(getOutput(), "true"); // String "0.00000000000000" is non-empty
}

TEST_F(TypeConversion, NestedConversionsWithOperations) {
  I(R"(print(Decimal(String(Int32(2.9) + Int32(3.1)))))");
  EXPECT_EQ(getOutput(), "5.00000000000000");
}

TEST_F(TypeConversion, StringToDecimalToInt32) {
  I(R"(print(Int32(Decimal(String("12.99")))))");
  EXPECT_EQ(getOutput(), "12");
}

// Edge case conversions
TEST_F(TypeConversion, Int32FromMaxIntString) {
  I(R"(print(Int32(String("2147483647"))))");
  EXPECT_EQ(getOutput(), "2147483647");
}

TEST_F(TypeConversion, DecimalFromMinValueString) {
  I(R"(print(Decimal(String("-999999.99999999999999"))))");
  EXPECT_EQ(getOutput(), "-1000000.00000000000000");
}

TEST_F(TypeConversion, BoolFromNonAsciiString) {
  I(R"(print(Bool(String("é"))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, Int8FromEmptyString) {
  I(R"(print(Int8(String(""))))");
  EXPECT_EQ(getOutput(), std::string(1, '\0'));
}

// Intermediate Explicit Conversion Tests
TEST_F(TypeConversion, IntermediateConversion_IntToStringToInt32) {
  I(R"(print(Int32(String(2))))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, IntermediateConversion_FloatToStringToDecimal) {
  I(R"(print(Decimal(String(2.2))))");
  EXPECT_EQ(getOutput(), "2.20000000000000");
}

TEST_F(TypeConversion, IntermediateConversion_StringToInt32ToBool) {
  I(R"(print(Bool(Int32("1"))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, IntermediateConversion_FloatToInt32ToString) {
  I(R"(print(String(Int32(2.7))))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, IntermediateConversion_BoolToDecimal32) {
  I(R"(print(Decimal32(Bool(true))))");
  EXPECT_EQ(getOutput(), "1.0000000");
}

TEST_F(TypeConversion, IntermediateConversion_FloatToDecimalToInt32) {
  I(R"(print(Int32(Decimal(2.9))))");
  EXPECT_EQ(getOutput(), "2");
}

TEST_F(TypeConversion, IntermediateConversion_IntToBoolToString) {
  I(R"(print(String(Bool(0))))");
  EXPECT_EQ(getOutput(), "false");
}

TEST_F(TypeConversion, IntermediateConversion_StringToBool) {
  I(R"(print(Bool(String("true"))))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, IntermediateConversion_FloatToDecimal32ToInt32) {
  I(R"(print(Int32(Decimal32(3.14))))");
  EXPECT_EQ(getOutput(), "3");
}

TEST_F(TypeConversion, IntermediateConversion_IntToInt8ToString) {
  I(R"(print(String(Int8(65))))");
  EXPECT_EQ(getOutput(), "65");
}

// Additional Edge Case Tests
TEST_F(TypeConversion, StringConversion_NegativeInt) {
  I(R"(print(String(-5)))");
  EXPECT_EQ(getOutput(), "-5");
}

TEST_F(TypeConversion, Int32Conversion_NegativeFloat) {
  I(R"(print(Int32(-1*2.8)))");
  EXPECT_EQ(getOutput(), "-2");
}

TEST_F(TypeConversion, Decimal32Conversion_LargeNumber) {
  I(R"(print(Decimal32(123456789.123456)))");
  EXPECT_EQ(getOutput(), "123456792.0000000");
}

TEST_F(TypeConversion, BoolConversion_StringTrue) {
  I(R"(print(Bool("true")))");
  EXPECT_EQ(getOutput(), "true");
}

// TEST_F(TypeConversion, Int8Conversion_Zero) {
//   I(R"(print(Int8(0)))");
//   EXPECT_EQ(getOutput(), "");
// }

TEST_F(TypeConversion, StringConversion_EmptyString) {
  I(R"(print(String("")))");
  EXPECT_EQ(getOutput(), "");
}

TEST_F(TypeConversion, Int32Conversion_StringZero) {
  I(R"(print(Int32("0")))");
  EXPECT_EQ(getOutput(), "0");
}

TEST_F(TypeConversion, DecimalConversion_StringZero) {
  I(R"(print(Decimal("0.0")))");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

TEST_F(TypeConversion, BoolConversion_StringFalse) {
  I(R"(print(Bool("false")))");
  EXPECT_EQ(getOutput(), "true");
}

// TEST_F(TypeConversion, Int8Conversion_MaxValue) {
//   I(R"(print(Int8(255)))");
//   EXPECT_EQ(getOutput(), "ÿ");
// }

// More Tests to Reach 100
TEST_F(TypeConversion, StringConversion_NegativeFloat) {
  I(R"(print(String(-1*3.14)))");
  EXPECT_EQ(getOutput(), "-3.14000000000000");
}

TEST_F(TypeConversion, Int32Conversion_MaxInt) {
  I(R"(print(Int32(2147483647)))");
  EXPECT_EQ(getOutput(), "2147483647");
}

TEST_F(TypeConversion, Int32Conversion_MinInt) {
  I(R"(print(Int32(-2147483648)))");
  EXPECT_EQ(getOutput(), "-2147483648");
}

TEST_F(TypeConversion, Decimal32Conversion_NegativeFloat) {
  I(R"(print(Decimal32(-1*2.5)))");
  EXPECT_EQ(getOutput(), "-2.5000000");
}

TEST_F(TypeConversion, DecimalConversion_NegativeDouble) {
  I(R"(print(Decimal(-1*2.2d)))");
  EXPECT_EQ(getOutput(), "-2.20000004768372");
}

TEST_F(TypeConversion, BoolConversion_NegativeInt) {
  I(R"(print(Bool(-1)))");
  EXPECT_EQ(getOutput(), "true");
}

// TEST_F(TypeConversion, Int8Conversion_NegativeInt) {
//   I(R"(print(Int8(-65)))");
//   EXPECT_EQ(getOutput(), "ŷ");
// }

TEST_F(TypeConversion, StringConversion_LargeInt) {
  I(R"(print(String(1000000)))");
  EXPECT_EQ(getOutput(), "1000000");
}

TEST_F(TypeConversion, Int32Conversion_LargeFloat) {
  I(R"(print(Int32(9999.9)))");
  EXPECT_EQ(getOutput(), "9999");
}

TEST_F(TypeConversion, Decimal32Conversion_SmallFloat) {
  I(R"(print(Decimal32(0.0001)))");
  EXPECT_EQ(getOutput(), "0.0001000");
}

TEST_F(TypeConversion, DecimalConversion_LargeString) {
  I(R"(print(Decimal("12345.6789")))");
  EXPECT_EQ(getOutput(), "12345.67890000000079");
}

TEST_F(TypeConversion, BoolConversion_LargeFloat) {
  I(R"(print(Bool(1000.0)))");
  EXPECT_EQ(getOutput(), "true");
}

// TEST_F(TypeConversion, Int8Conversion_SmallNegative) {
//   I(R"(print(Int8(-1)))");
//   EXPECT_EQ(getOutput(), "ÿ");
// }

TEST_F(TypeConversion, StringConversion_SpaceString) {
  I(R"(print(String(" ")))");
  EXPECT_EQ(getOutput(), " ");
}

TEST_F(TypeConversion, Int32Conversion_SpaceString) {
  I(R"(print(Int32(" ")))");
  EXPECT_EQ(getOutput(), "0");
}

TEST_F(TypeConversion, Decimal32Conversion_ZeroString) {
  I(R"(print(Decimal32("0")))");
  EXPECT_EQ(getOutput(), "0.0000000");
}

TEST_F(TypeConversion, DecimalConversion_NegativeString) {
  I(R"(print(Decimal("-1*5.5")))");
  EXPECT_EQ(getOutput(), "-1.00000000000000");
}

TEST_F(TypeConversion, BoolConversion_SpaceString) {
  I(R"(print(Bool(" ")))");
  EXPECT_EQ(getOutput(), "true");
}

TEST_F(TypeConversion, Int8Conversion_LowercaseChar) {
  I(R"(print(Int8('z')))");
  EXPECT_EQ(getOutput(), "z");
}

TEST_F(TypeConversion, StringConversion_MultiWordString) {
  I(R"(print(String("Hello World")))");
  EXPECT_EQ(getOutput(), "Hello World");
}

// Function return value conversions
TEST_F(TypeConversion, FunctionReturnToDecimalToString) {
  I(R"(
    fun getC(d: deci32) -> str { return "100" }
    print(String(Decimal(getC(2.2d))))
  )");
  EXPECT_EQ(getOutput(), "100.00000000000000");
}

TEST_F(TypeConversion, FunctionReturnToDecimal32Chain) {
  I(R"(
    fun getC(d: deci32) -> str { return "42.5" }
    print(Decimal32(getC(3.14d)))
  )");
  EXPECT_EQ(getOutput(), "42.5000000");
}

TEST_F(TypeConversion, FunctionPassthroughWithConversion) {
  I(R"(
    fun getD(s: str) -> str { return s }
    print(Int32(getD("65")))
  )");
  EXPECT_EQ(getOutput(), "65");
}

// Multiple function conversion chain
TEST_F(TypeConversion, NestedFunctionConversionChain) {
  I(R"(
    fun getD(s: str) -> str { return "200" }
    fun getC(d: deci32) -> str { return getD("ignore") }
    print(Decimal(getC(9.99d)))
  )");
  EXPECT_EQ(getOutput(), "200.00000000000000");
}

// Function arguments with implicit conversions
TEST_F(TypeConversion, FunctionArgConversionFromInt) {
  I(R"(
    fun getC(d: deci32) -> str { return String(d) }
    print(getC(42.0d))
  )");
  EXPECT_EQ(getOutput(), "42.00000000000000");
}

TEST_F(TypeConversion, FunctionArgConversionFromString) {
  I(R"(
    fun getC(d: deci32) -> str { return String(d) }
    print(getC(Decimal32("3.14")))
  )");
  EXPECT_EQ(getOutput(), "3.14000010490417");
}

// Complex type flows
TEST_F(TypeConversion, MultiStepFunctionConversion) {
  I(R"(
    fun getD(s: str) -> str { return "123.45" }
    fun process(n: deci) -> str { return String(n + 1.0d) }
    print(process(Decimal(getD("ignored"))))
  )");
  EXPECT_EQ(getOutput(), "124.44999694824219");
}

TEST_F(TypeConversion, FunctionReturnToInt8Conversion) {
  I(R"(
    fun getCharCode(s: str) -> str { return "66" }
    print(Int8(getCharCode("any")))
  )");
  EXPECT_EQ(getOutput(), "B");
}

// Edge case function conversions
TEST_F(TypeConversion, FunctionReturnEmptyStringConversion) {
  I(R"(
    fun getD(s: str) -> str { return "" }
    print(Decimal(getD("test")))
  )");
  EXPECT_EQ(getOutput(), "0.00000000000000");
}

TEST_F(TypeConversion, FunctionReturnBooleanStringConversion) {
  I(R"(
    fun getFlag(b: bool) -> str { return String(b) }
    print(Int32(getFlag(true)))
  )");
  EXPECT_EQ(getOutput(), "0");
}

// Type conversion through multiple functions
TEST_F(TypeConversion, TripleFunctionConversionChain) {
  I(R"(
fun A() -> deci32 {
  return 5.5d
}


fun B(d: deci) -> str {
  return String(d * 2)
}


fun C(s: str) -> int {
  return Int32(s)
}

    print(C(B(Decimal(A()))))
  )");
  EXPECT_EQ(getOutput(), "11");
} // Type conversion through multiple functions
TEST_F(TypeConversion, TripleFunctionConversionChainLocalVariable) {
  I(R"(
fun A() -> deci32 {
  return 5.5d
}


fun B(d: deci) -> str {
  return String(d * 2)
}


fun C(s: str) -> int {
  return Int32(s)
}

    var x: int = C(B(Decimal(A())))
    print(x)
  )");
  EXPECT_EQ(getOutput(), "11");
}
TEST_F(TypeConversion, TripleFunctionConversionChainLocalVariable2) {
  I(R"(
fun A() -> deci32 {
  return 5.5d
}


fun B(d: deci, d2: deci, d3: deci) -> str {
  print(d, d2, d3)
  return String(d * 2)
}


fun C(s: str) -> int {
  return Int32(s)
}

var x: int = C(B(Decimal(A()), Decimal(A()), Decimal(A())))
print(x)
  )");
  EXPECT_EQ(getOutput(), "5.500000000000005.500000000000005.5000000000000011");
}
#endif // __TYPE_CONVERSION_H__