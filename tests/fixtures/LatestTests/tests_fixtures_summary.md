# Flow-Wing Test Cases Summary

This document contains a collection of test cases (source code and expected output) for the Flow-Wing language.

# Directory: DynamicVariableTests/interactions

## Test: dynamic_copy

### dynamic_copy.fg
```javascript
var x = 5
var y = x
print(y, "\n")
y = 10
print(x, " ", y, "\n")
```

### dynamic_copy.expect
```
5
5 10
```

## Test: dynamic_to_typed

### dynamic_to_typed.fg
```javascript
var x = 5
var y: int = x
print(y, "\n")
```

### dynamic_to_typed.expect
```
5
```

## Test: dynamic_to_typed_deci

### dynamic_to_typed_deci.fg
```javascript
var x = 3.14
var y: deci = x
print(y, "\n")
```

### dynamic_to_typed_deci.expect
```
3.14
```

## Test: mixed_operations

### mixed_operations.fg
```javascript
var x = 5
var y: int = 10
var z = x + y
print(z, "\n")
```

### mixed_operations.expect
```
15
```

## Test: multiple_dynamic_ops

### multiple_dynamic_ops.fg
```javascript
var x = 10
var y = 20
var z = x + y
print(z, "\n")
z = x * y
print(z, "\n")
z = y / x
print(z, "\n")
z = x < y
print(z, "\n")
```

### multiple_dynamic_ops.expect
```
30
200
2
true
```

## Test: typed_to_dynamic

### typed_to_dynamic.fg
```javascript
var x: int = 10
var y = x
print(y, "\n")
```

### typed_to_dynamic.expect
```
10
```

## Test: typed_to_dynamic_str

### typed_to_dynamic_str.fg
```javascript
var x: str = "Hello"
var y = x
print(y, "\n")
```

### typed_to_dynamic_str.expect
```
"Hello"
```

---

# Directory: DynamicVariableTests/unary_operations

## Test: bitwise_not

### bitwise_not.fg
```javascript
var x = 5
var y = ~x
print(y, "\n")
```

### bitwise_not.expect
```
-6
```

## Test: char_bitwise_not

### char_bitwise_not.fg
```javascript
var x = 'a'
var y = ~x
print(y, "\n")
```

### char_bitwise_not.expect
```
-98
```

## Test: char_negation

### char_negation.fg
```javascript
var x = 'a'
var y = -x
print(y, "\n")
```

### char_negation.expect
```
-97
```

## Test: logical_not

### logical_not.fg
```javascript
var x = true
var y = !x
print(y, "\n")
```

### logical_not.expect
```
false
```

## Test: logical_not_string

### logical_not_string.fg
```javascript
var x = "hello"
var y = !x
print(y, "\n")
```

### logical_not_string.expect
```
false
```

## Test: logical_not_zero

### logical_not_zero.fg
```javascript
var x = 0
var y = !x
print(y, "\n")
var z = 0.0
var w = !z
print(w, "\n")
```

### logical_not_zero.expect
```
true
true
```

## Test: negation

### negation.fg
```javascript
var x = 5
var y = -x
print(y, "\n")
```

### negation.expect
```
-5
```

## Test: unary_plus

### unary_plus.fg
```javascript
var x = 5
var y = +x
print(y, "\n")
```

### unary_plus.expect
```
5
```

---

# Directory: DynamicVariableTests/reassignment

## Test: basic

### basic.fg
```javascript
var x = 2
print(x, "\n")
x = 3
print(x, "\n")
```

### basic.expect
```
2
3
```

## Test: change_type_int_to_str

### change_type_int_to_str.fg
```javascript
var x = 2
print(x, "\n")
x = "Hello"
print(x, "\n")
```

### change_type_int_to_str.expect
```
2
"Hello"
```

## Test: change_type_str_to_int

### change_type_str_to_int.fg
```javascript
var x = "Hello"
print(x, "\n")
x = 42
print(x, "\n")
```

### change_type_str_to_int.expect
```
"Hello"
42
```

## Test: multiple_changes

### multiple_changes.fg
```javascript
var x = 2
print(x, "\n")
x = 3.14
print(x, "\n")
x = "test"
print(x, "\n")
x = true
print(x, "\n")
x = 'z'
print(x, "\n")
x = 100l
print(x, "\n")
```

### multiple_changes.expect
```
2
3.14
"test"
true
'z'
100
```

## Test: with_expression

### with_expression.fg
```javascript
var x = 5
x = x + 3
print(x, "\n")
```

### with_expression.expect
```
8
```

---

# Directory: DynamicVariableTests/edge_cases

## Test: boundary_int64

### boundary_int64.fg
```javascript
var x = 9223372036854775807l
print(x, "\n")
x = -9223372036854775808l
print(x, "\n")
```

### boundary_int64.expect
```
9223372036854775807
-9223372036854775808
```

## Test: boundary_int8

### boundary_int8.fg
```javascript
var x = 127
print(x, "\n")
x = -128
print(x, "\n")
```

### boundary_int8.expect
```
127
-128
```

## Test: char_boundary

### char_boundary.fg
```javascript
var x = 'a'
print(x, "\n")
x = 'Z'
print(x, "\n")
x = '0'
print(x, "\n")
```

### char_boundary.expect
```
'a'
'Z'
'0'
```

## Test: complex_nested

### complex_nested.fg
```javascript
var x = 10
var y = (x + 5) * 2
print(y, "\n")
```

### complex_nested.expect
```
30
```

## Test: type_changes

### type_changes.fg
```javascript
var x = 10
print(x, "\n")
x = "hello"
print(x, "\n")
x = 3.14
print(x, "\n")
x = true
print(x, "\n")
x = 'x'
print(x, "\n")
x = 100l
print(x, "\n")
```

### type_changes.expect
```
10
"hello"
3.14
true
'x'
100
```

## Test: uninitialized

### uninitialized.fg
```javascript
var x
print(x, "\n")
```

### uninitialized.expect
```
0
```

---

# Directory: DynamicVariableTests/scope

## Test: global_basic

### global_basic.fg
```javascript
var x = 10
print(x, "\n")
{
  print(x, "\n")
}
print(x, "\n")
```

### global_basic.expect
```
10
10
10
```

## Test: global_reassignment

### global_reassignment.fg
```javascript
var x = 10
print(x, "\n")
{
  x = 20
  print(x, "\n")
}
print(x, "\n")
```

### global_reassignment.expect
```
10
20
20
```

## Test: local_basic

### local_basic.fg
```javascript
{
  var x = 10
  print(x, "\n")
}
print("done", "\n")
```

### local_basic.expect
```
10
done
```

## Test: local_reassignment

### local_reassignment.fg
```javascript
{
  var x = 10
  print(x, "\n")
  x = 20
  print(x, "\n")
}
print("done", "\n")
```

### local_reassignment.expect
```
10
20
done
```

## Test: multiple_globals

### multiple_globals.fg
```javascript
var x = 10
var y = "hello"
var z = true
print(x, " ", y, " ", z, "\n")
{
  print(x, " ", y, " ", z, "\n")
  var w = 3.14
  print(w, "\n")
}
print(x, " ", y, " ", z, "\n")
```

### multiple_globals.expect
```
10 "hello" true
10 "hello" true
3.14
10 "hello" true
```

## Test: shadowing

### shadowing.fg
```javascript
var x = 100
print(x, "\n")
{
  var x = 200
  print(x, "\n")
}
print(x, "\n")
```

### shadowing.expect
```
100
200
100
```

## Test: shadowing_type_change

### shadowing_type_change.fg
```javascript
var x = 100
print(x, "\n")
{
  var x = "local"
  print(x, "\n")
}
print(x, "\n")
```

### shadowing_type_change.expect
```
100
"local"
100
```

---

# Directory: DynamicVariableTests/print

## Test: basic

### basic.fg
```javascript
var x = 42
print(x, "\n")
```

### basic.expect
```
42
```

## Test: complex_expression

### complex_expression.fg
```javascript
var x = 2
var k = x + 2
print(k, "\n")
print((k + 2), "\n")
```

### complex_expression.expect
```
4
6
```

## Test: multiple_types

### multiple_types.fg
```javascript
var x = 2
print(x, "\n")
x = "Hello"
print(x, "\n")
x = true
print(x, "\n")
x = 3.14
print(x, "\n")
```

### multiple_types.expect
```
2
"Hello"
true
3.14
```

## Test: nested_expression

### nested_expression.fg
```javascript
var x = 2
var k = x + 2
print(k, "\n")
print(k + 2, "\n")
```

### nested_expression.expect
```
4
6
```

## Test: with_expression

### with_expression.fg
```javascript
var x = 5
print(x + 3, "\n")
```

### with_expression.expect
```
8
```

---

# Directory: DynamicVariableTests/binary_operations

## Test: addition

### addition.fg
```javascript
var x = 2
var y = x + 3
print(y, "\n")
```

### addition.expect
```
5
```

## Test: bitwise_and

### bitwise_and.fg
```javascript
var x = 5
var y = x & 3
print(y, "\n")
```

### bitwise_and.expect
```
1
```

## Test: bitwise_or

### bitwise_or.fg
```javascript
var x = 5
var y = x | 3
print(y, "\n")
```

### bitwise_or.expect
```
7
```

## Test: bitwise_xor

### bitwise_xor.fg
```javascript
var x = 5
var y = x ^ 3
print(y, "\n")
```

### bitwise_xor.expect
```
6
```

## Test: comparison_eq

### comparison_eq.fg
```javascript
var x = 5
var y = x == 5
print(y, "\n")
```

### comparison_eq.expect
```
true
```

## Test: comparison_gt

### comparison_gt.fg
```javascript
var x = 5
var y = x > 3
print(y, "\n")
var z = x > 10
print(z, "\n")
```

### comparison_gt.expect
```
true
false
```

## Test: comparison_gte

### comparison_gte.fg
```javascript
var x = 5
var y = x >= 5
print(y, "\n")
var z = x >= 10
print(z, "\n")
```

### comparison_gte.expect
```
true
false
```

## Test: comparison_lt

### comparison_lt.fg
```javascript
var x = 5
var y = x < 10
print(y, "\n")
```

### comparison_lt.expect
```
true
```

## Test: comparison_lte

### comparison_lte.fg
```javascript
var x = 5
var y = x <= 5
print(y, "\n")
var z = x <= 3
print(z, "\n")
```

### comparison_lte.expect
```
true
false
```

## Test: comparison_neq

### comparison_neq.fg
```javascript
var x = 5
var y = x != 3
print(y, "\n")
var z = x != 5
print(z, "\n")
```

### comparison_neq.expect
```
true
false
```

## Test: complex_expression

### complex_expression.fg
```javascript
var x = 5
var y = 10
var z = x + y * 2
print(z, "\n")
```

### complex_expression.expect
```
25
```

## Test: division

### division.fg
```javascript
var x = 15
var y = x / 3
print(y, "\n")
```

### division.expect
```
5
```

## Test: dynamic_plus_dynamic

### dynamic_plus_dynamic.fg
```javascript
var x = 5
var y = 10
var z = x + y
print(z, "\n")
```

### dynamic_plus_dynamic.expect
```
15
```

## Test: dynamic_plus_primitive

### dynamic_plus_primitive.fg
```javascript
var x = 5
var y = x + 10
print(y, "\n")
```

### dynamic_plus_primitive.expect
```
15
```

## Test: integer_division

### integer_division.fg
```javascript
var x = 15
var y = x // 4
print(y, "\n")
```

### integer_division.expect
```
3
```

## Test: logical_and

### logical_and.fg
```javascript
var x = 5
var y = x && 3
print(y, "\n")
var z = x && 0
print(z, "\n")
```

### logical_and.expect
```
true
false
```

## Test: logical_or

### logical_or.fg
```javascript
var x = 5
var y = x || 0
println(y)
```

### logical_or.expect
```
true
```

## Test: mixed_types_int_deci

### mixed_types_int_deci.fg
```javascript
var x = 5
var y = x + 3.5
print(y, "\n")
```

### mixed_types_int_deci.expect
```
8.5
```

## Test: modulo

### modulo.fg
```javascript
var x = 15
var y = x % 4
print(y, "\n")
```

### modulo.expect
```
3
```

## Test: multiplication

### multiplication.fg
```javascript
var x = 5
var y = x * 3
print(y, "\n")
```

### multiplication.expect
```
15
```

## Test: primitive_plus_dynamic

### primitive_plus_dynamic.fg
```javascript
var x = 5
var y = 10 + x
print(y, "\n")
```

### primitive_plus_dynamic.expect
```
15
```

## Test: string_concat

### string_concat.fg
```javascript
var x = "Hello"
var y = x + " World"
print(y, "\n")
```

### string_concat.expect
```
"Hello World"
```

## Test: subtraction

### subtraction.fg
```javascript
var x = 10
var y = x - 3
print(y, "\n")
```

### subtraction.expect
```
7
```

---

# Directory: DynamicVariableTests/runtime_errors

## Test: bitwise_not_on_float

### bitwise_not_on_float.fg
```javascript
/; EXPECT_ERROR: Bitwise NOT cannot be applied to decimals
var x = 5.5
var y = ~x
print(y, "\n")
```

## Test: bitwise_on_float

### bitwise_on_float.fg
```javascript
/; EXPECT_ERROR: Invalid operator for floating point numbers
var x = 5.5
var y = x & 3
print(y, "\n")
```

## Test: bitwise_or_on_float

### bitwise_or_on_float.fg
```javascript
/; EXPECT_ERROR: Invalid operator for floating point numbers
var x = 5.5
var y = x | 3
print(y, "\n")
```

## Test: bitwise_xor_on_float

### bitwise_xor_on_float.fg
```javascript
/; EXPECT_ERROR: Invalid operator for floating point numbers
var x = 5.5
var y = x ^ 3
print(y, "\n")
```

## Test: cannot_cast_dynamic_to_char

### cannot_cast_dynamic_to_char.fg
```javascript
/; EXPECT_ERROR: Cannot cast Dynamic value to Char
var z: char = 'a'
print(z, "\n")

var x = 'b'
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

## Test: cannot_cast_dynamic_to_float32

### cannot_cast_dynamic_to_float32.fg
```javascript
/; EXPECT_ERROR: Cannot cast Dynamic value to Float
var z: deci32 = 3.14f
print(z, "\n")

var x = 5.5
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

## Test: cannot_cast_dynamic_to_float64

### cannot_cast_dynamic_to_float64.fg
```javascript
/; EXPECT_ERROR: Cannot cast Dynamic value to Decimal
var z: deci = 3.14
print(z, "\n")

var x = 5.5
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

## Test: cannot_cast_dynamic_to_int32

### cannot_cast_dynamic_to_int32.fg
```javascript
/; EXPECT_ERROR: Cannot cast Dynamic value to Int32
var z: int = 22
print(z, "\n")

var x =  55
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

## Test: cannot_cast_dynamic_to_int64

### cannot_cast_dynamic_to_int64.fg
```javascript
/; EXPECT_ERROR: Cannot cast Dynamic value to Int64
var z: int64 = 22
print(z, "\n")

var x = 55
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

## Test: cannot_cast_dynamic_to_int8

### cannot_cast_dynamic_to_int8.fg
```javascript
/; EXPECT_ERROR: Cannot cast Dynamic value to Int8
var z: int8 = 22
print(z, "\n")

var x = 55
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

## Test: char_unary_plus

### char_unary_plus.fg
```javascript
/; EXPECT_ERROR: Invalid type for unary plus
var x = 'a'
var y = +x
print(y, "\n")
```

## Test: division_by_zero

### division_by_zero.fg
```javascript
/; EXPECT_ERROR: Division by zero
var x = 10
var y = x / 0
print(y, "\n")
```

## Test: float_division_by_zero

### float_division_by_zero.fg
```javascript
/; EXPECT_ERROR: Division by zero
var x = 10.5
var y = x / 0.0
print(y, "\n")
```

## Test: integer_division_by_zero

### integer_division_by_zero.fg
```javascript
/; EXPECT_ERROR: Integer Division by zero
var x = 10
var y = x // 0
print(y, "\n")
```

## Test: modulo_by_zero

### modulo_by_zero.fg
```javascript
/; EXPECT_ERROR: Modulo by zero
var x = 10
var y = x % 0
print(y, "\n")
```

## Test: unary_plus_on_bool

### unary_plus_on_bool.fg
```javascript
/; EXPECT_ERROR: Invalid type for unary plus
var x = true
var y = +x
print(y, "\n")
```

## Test: unary_plus_on_string

### unary_plus_on_string.fg
```javascript
/; EXPECT_ERROR: Invalid type for unary plus
var x = "hello"
var y = +x
print(y, "\n")
```

---

# Directory: DynamicVariableTests/conversion

## Test: dynamic_bool

### dynamic_bool.fg
```javascript
var _int = 100000222222
println(Bool(_int))
var _deci = 10.5344345333333
println(Bool(_deci))
var _deci32 = 10.5344345333333f
println(Bool(_deci32))
var _null = null
println(Bool(_null))
var _str = "Hello"
println(Bool(_str))
var _char = 'x'
println(Bool(_char))
var _int64 = 1000000000000
println(Bool(_int64))
var _int8 = 127
println(Bool(_int8))
```

### dynamic_bool.expect
```
true
true
true
false
true
true
true
true
```

## Test: dynamic_decimal

### dynamic_decimal.fg
```javascript
var _int = 100000222222
println(Decimal(_int))
var _deci = 10.5344345333333
println(Decimal(_deci))
var _deci32 = 10.5344345333333f
println(Decimal(_deci32))
var _char = 'x'
println(Decimal(_char))
var _int64 = 1000000000000
println(Decimal(_int64))
var _int8 = 127
println(Decimal(_int8))
```

### dynamic_decimal.expect
```
100000222222
10.5344345333333
10.53443431854248
120
1000000000000
127
```

## Test: dynamic_decimal32

### dynamic_decimal32.fg
```javascript
var _int = 100000222222
println(Decimal32(_int))
var _deci = 10.5
println(Decimal32(_deci))
var _char = 'x'
println(Decimal32(_char))
var _int64 = 1000000000000
println(Decimal32(_int64))
var _int8 = 127
println(Decimal32(_int8))
```

### dynamic_decimal32.expect
```
1.000002e+11
10.5
120
1e+12
127
```

## Test: dynamic_int32

### dynamic_int32.fg
```javascript
var _int = 1000002
println(Int32(_int))
var _deci = 10.5344345333333
println(Int32(_deci))
var _deci32 = 10.53443f
println(Int32(_deci32))
var _null = null
println(Int32(_null))
var _char = 'x'
println(Int32(_char))
var _int64 = 1000000000000
println(Int32(_int64))
var _int8 = 127
println(Int32(_int8))
```

### dynamic_int32.expect
```
1000002
10
10
0
120
-727379968
127
```

## Test: dynamic_int64

### dynamic_int64.fg
```javascript
var _int = 100000222222
println(Int64(_int))
var _deci = 10.5344345333333
println(Int64(_deci))
var _deci32 = 10.5344345333333f
println(Int64(_deci32))

var _char = 'x'
println(Int64(_char))
var _int64 = 1000000000000
println(Int64(_int64))
var _int8 = 127
println(Int64(_int8))
```

### dynamic_int64.expect
```
100000222222
10
10
120
1000000000000
127
```

## Test: dynamic_int8

### dynamic_int8.fg
```javascript
var _int = 100000222222
println(Int8(_int))
var _deci = 10.5344345333333
println(Int8(_deci))
var _deci32 = 10.5344345333333f
println(Int8(_deci32))
var _null = null
println(Int8(_null))
var _char = 'x'
println(Int8(_char))
var _int64 = 10000
println(Int8(_int64))
var _int8 = 127
println(Int8(_int8))
```

### dynamic_int8.expect
```
14
10
10
0
120
16
127
```

## Test: dynamic_string

### dynamic_string.fg
```javascript
var _int = 100000222222
println(String(_int))
var _deci = 10.0
println(String(_deci))
var _bool = true
println(String(_bool))
var _null = null
println(String(_null))
var _str = "Hello"
println(String(_str))
var _char = 'x'
println(String(_char))
var _int64 = 1000000000000
println(String(_int64))
var _int8 = 127
println(String(_int8))
```

### dynamic_string.expect
```
100000222222
10
true
0
Hello
x
1000000000000
127
```

---

# Directory: DynamicVariableTests/errors

## Test: assign_const

### assign_const.fg
```javascript
/; EXPECT_ERROR: UnexpectedToken
const var x = 5
x = 10
print(x, "\n")
```

## Test: assign_to_non_lvalue

### assign_to_non_lvalue.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
5 = 10
print(5, "\n")
```

## Test: assign_to_non_variable

### assign_to_non_variable.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonVariable
var x = 5
print = 10
```

## Test: dyn_bool_to_decimal

### dyn_bool_to_decimal.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Decimal.
var _bool = true
println(Decimal(_bool))
```

## Test: dyn_str_to_decimal

### dyn_str_to_decimal.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Decimal.
var _str = "Hello"
println(Decimal(_str))
```

## Test: dyn_str_to_int32

### dyn_str_to_int32.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var _str = "Hello"
println(Int32(_str))
```

## Test: dyn_str_to_int64

### dyn_str_to_int64.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int64.
var _str = "Hello"
println(Int64(_str))
```

## Test: dyn_str_to_int8

### dyn_str_to_int8.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int8.
vvar _str = "Hello"
println(Int8(_str))
```

## Test: invalid_int

### invalid_int.fg
```javascript
/; EXPECT_ERROR:  Cannot cast Dynamic value to Int32.
var z: int = 22
print(z, "\n")

var x =  55
print(x, "\n")
z = x
print(z, "\n")
var k = "Hello"
z = k
print(z, "\n")
```

---

# Directory: DynamicVariableTests/declaration

## Test: bool

### bool.fg
```javascript
var x = true
print(x, "\n")
var y = false
print(y, "\n")
```

### bool.expect
```
true
false
```

## Test: char

### char.fg
```javascript
var x = 'a'
print(x, "\n")
```

### char.expect
```
'a'
```

## Test: deci

### deci.fg
```javascript
var x = 3.14
print(x, "\n")
```

### deci.expect
```
3.14
```

## Test: deci32

### deci32.fg
```javascript
var x = 2.5f
print(x, "\n")
```

### deci32.expect
```
2.5
```

## Test: int32

### int32.fg
```javascript
var x = 2
print(x, "\n")
```

### int32.expect
```
2
```

## Test: int64

### int64.fg
```javascript
var x = 2l
print(x, "\n")
```

### int64.expect
```
2
```

## Test: int8

### int8.fg
```javascript
var x = 5
print(x, "\n")
```

### int8.expect
```
5
```

## Test: multiple

### multiple.fg
```javascript
var x = 2
var y = 3.14
var z = "test"
var w = true
var v = 'x'
print(x, " ", y, " ", z, " ", w, " ", v, "\n")
```

### multiple.expect
```
2 3.14 "test" true 'x'
```

## Test: str

### str.fg
```javascript
var x = "Hello"
print(x, "\n")
```

### str.expect
```
"Hello"
```

---

# Directory: 01_unary

## Test: bang

### bang.fg
```javascript
print("Bang Prefix Operator for Int\n")
print(!1 , "\n")
print(!3 , "\n")
print(!0, "\n")

print("Bang Prefix Operator for Double\n")
print(!1.0 , "\n")
print(!3.0 , "\n")
print(!2.5 , "\n")
print(!0.0 , "\n")

print("Bang Prefix Operator for Float\n")
print(!1.0f , "\n")
print(!3.0f , "\n")
print(!2.5f , "\n")
print(!0.0f , "\n")

print("Bang Prefix Operator for String\n")
print(!"Hello" , "\n")
print(!"World" , "\n")
print(!("Hello" + "World") , "\n")
print(!("Hello" != "World") , "\n")
print(!"" , "\n")

print("Bang Prefix Operator for Boolean\n")
print(!true , "\n")
print(!false , "\n")
print(!(true && false) , "\n")
print(!(true || false) , "\n")
print(!(true && true) , "\n")
print(!(true || true) , "\n")
print(!(false && false) , "\n")
print(!(false || false) , "\n")
print(!(false && true) , "\n")
print(!(false || true) , "\n")

print("Bang Prefix Operator for Char\n")
print(!'a' , '\n')
print(!'b' , '\n')
print(!('a' + 'b') , '\n')
print(!('a' != 'b') , '\n')
print(!('a' == 'b') , '\n')
print(!('a' != 'a') , '\n')
print(!('a' == 'a') , '\n')
print(!('a' != 'b') , '\n')

print("Bang Prefix Operator for Nir\n")
print(!null , '\n')


print("Bang Bang Prefix Operator for Int\n")
print(!(!1) , '\n')
print(!(!3) , '\n')
print(!(!0) , '\n')

print("Bang Bang Prefix Operator for Double\n")
print(!(!1.0) , '\n')
print(!(!3.0) , '\n')
print(!(!2.5) , '\n')
print(!(!0.0) , '\n')
```

### bang.expect
```
Bang Prefix Operator for Int
false
false
true
Bang Prefix Operator for Double
false
false
false
true
Bang Prefix Operator for Float
false
false
false
true
Bang Prefix Operator for String
false
false
false
false
true
Bang Prefix Operator for Boolean
false
true
true
false
false
false
true
true
true
false
Bang Prefix Operator for Char
false
false
false
false
true
true
false
false
Bang Prefix Operator for Nir
true
Bang Bang Prefix Operator for Int
true
true
false
Bang Bang Prefix Operator for Double
true
true
true
false
```

## Test: kInvalidUnaryOperator_1

### kInvalidUnaryOperator_1.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+('a' + 'b') , '\n')
```

## Test: kInvalidUnaryOperator_2

### kInvalidUnaryOperator_2.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+('a' != 'b') , '\n')
```

## Test: kInvalidUnaryOperator_3

### kInvalidUnaryOperator_3.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+'a' , '\n')
```

## Test: minus

### minus.fg
```javascript
print("Minus Prefix Operator for Int\n")
print(-1 , "\n")
print(-3 , "\n")

print("Minus Prefix Operator for Double\n")
print(-1.0 , "\n")
print(-3.0 , "\n")
print(-2.5 , "\n")

print("Minus Prefix Operator for Float\n")
print(-1.0f , "\n")
print(-3.0f , "\n")
print(-2.5f , "\n")
```

### minus.expect
```
Minus Prefix Operator for Int
-1
-3
Minus Prefix Operator for Double
-1
-3
-2.5
Minus Prefix Operator for Float
-1
-3
-2.5
```

## Test: plus

### plus.fg
```javascript
print("Plus Prefix Operator for Int\n")
print(+1 , "\n")
print(+3 , "\n")

print("Plus Prefix Operator for Double\n")
print(+1.0 , "\n")
print(+3.0 , "\n")
print(+2.5 , "\n")

print("Plus Prefix Operator for Float\n")
print(+1.0f , "\n")
print(+3.0f , "\n")
print(+2.5f , "\n")
```

### plus.expect
```
Plus Prefix Operator for Int
1
3
Plus Prefix Operator for Double
1
3
2.5
Plus Prefix Operator for Float
1
3
2.5
```

## Test: tilde

### tilde.fg
```javascript
print("Tilting Prefix Operator for Int\n")
print(~1 , "\n")
print(~3 , "\n")
print(~0 , "\n")
```

### tilde.expect
```
Tilting Prefix Operator for Int
-2
-4
-1
```

---

# Directory: FileModuleTests

## Test: file_features

### file_features.fg
```javascript
bring Err
bring file
bring text 

println("=========================================================")
println("          FLOWWING FILE SYSTEM COMPREHENSIVE TESTS       ")
println("=========================================================\n")

var testPath = "flowwing_test_output.txt"
var emptyTestPath = "flowwing_empty_test.txt"

println("--- Test 1: Writing and Reading Static Texts ---")
var writeOk: bool, writeErr: Err::Result = file::writeText(testPath, "Hello, FlowWing File System!\n")
if writeErr.isErr() { println("ERROR: " + writeErr.getMessage()) } else { println("Successfully wrote to file.") }

var appOk: bool, appErr: Err::Result = file::appendText(testPath, "This is an appended line.\n")
if appErr.isErr() { println("ERROR: " + appErr.getMessage()) } else { println("Successfully appended to file.") }

var content: str, readErr: Err::Result = file::readText(testPath)
if readErr.isOk() {
  println("File Contents:\n" + content)
}

println("--- Test 2: Checking Existence & Error Handling ---")
println("Does test file exist? " + String(file::exists(testPath)))
println("Does fake file exist? " + String(file::exists("missing_file_404.txt")))

var badData: str, badErr: Err::Result = file::readText("missing_file_404.txt")
if badErr.isErr() {
  println("Expected Error Caught (Read missing): " + badErr.getMessage())
}

var delFakeOk: bool, delFakeErr: Err::Result = file::delete("missing_file_404.txt")
if delFakeErr.isErr() {
  println("Expected Error Caught (Delete missing): " + delFakeErr.getMessage())
}


println("\n--- Test 3: Stateful Line-by-Line Reading ---")
var lineFile: file::File = new file::File(testPath)
var openErr: Err::Result = lineFile.open("r")

if openErr.isOk() {
  println("Reading line by line:")
  var lineCount = 1
  
  while true {
    var line: str, eofErr: Err::Result = lineFile.readLine()
    if eofErr.isErr() {
      println("Reached EOF.")
      break
    }
    println("Line " + String(lineCount) + ": " + line)
    lineCount = lineCount + 1
  }
  lineFile.close()
  println("File closed successfully.")
}

println("\n--- Test 4: Edge Cases - Empty Files & Strings ---")
/; Write empty string
var emptyWOk: bool, emptyWErr: Err::Result = file::writeText(emptyTestPath, "")
if emptyWErr.isOk() { println("Successfully created empty file.") }

/; Read empty file statically
var emptyData: str, emptyRErr: Err::Result = file::readText(emptyTestPath)
if emptyRErr.isOk() {
  println("Read empty file statically. Content length: " + String(text::getLength(emptyData))) /; Assuming String has length
}

/; Read empty file statefully
var emptyFile: file::File = new file::File(emptyTestPath)
emptyFile.open("r")
var emptyLine: str, emptyLineErr: Err::Result = emptyFile.readLine()
if emptyLineErr.isErr() {
  println("Expected Error Caught (Read line on empty file): " + emptyLineErr.getMessage())
}
emptyFile.close()

println("\n--- Test 5: Edge Cases - Invalid Paths ---")
var badPathOk: bool, badPathErr: Err::Result = file::writeText("", "Should fail")
if badPathErr.isErr() {
  println("Expected Error Caught (Write to empty path): " + badPathErr.getMessage())
}

println("\n--- Test 6: Edge Cases - Stateful Class Misuse ---")
var misuseFile: file::File = new file::File(testPath)

/; 6a. Read before open
var readBeforeOpen: str, errReadBefore: Err::Result = misuseFile.readLine()
if errReadBefore.isErr() {
  println("Expected Error Caught (Read before open): " + errReadBefore.getMessage())
}

/; 6b. Invalid mode
var errBadMode: Err::Result = misuseFile.open("z")
if errBadMode.isErr() {
  println("Expected Error Caught (Invalid open mode): " + errBadMode.getMessage())
}

/; 6c. Double open
var errOpen1: Err::Result = misuseFile.open("r")
var errOpen2: Err::Result = misuseFile.open("r")
if errOpen2.isErr() {
  println("Expected Error Caught (Double open): " + errOpen2.getMessage())
}

/; 6d. Read after close
misuseFile.close()
var errReadAfter: Err::Result = misuseFile.close() /; Double close should be safe per your code
println("Double close is safe: " + String(errReadAfter.isOk()))

var readAfterClose: str, errReadAfterClose: Err::Result = misuseFile.readLine()
if errReadAfterClose.isErr() {
  println("Expected Error Caught (Read after close): " + errReadAfterClose.getMessage())
}


println("\n--- Test 7: Edge Cases - Append to Non-existent File ---")
var newAppPath = "flowwing_new_append.txt"
var newAppOk: bool, newAppErr: Err::Result = file::appendText(newAppPath, "Created via append.")
if newAppErr.isOk() {
  println("Successfully created new file via append.")
}
var readNewApp: str, readNewAppErr: Err::Result = file::readText(newAppPath)
if readNewAppErr.isOk() {
  println("Content of appended file: " + readNewApp)
}

println("\n--- Test 8: Cleanup ---")
var del1: bool, e1: Err::Result = file::delete(testPath)
var del2: bool, e2: Err::Result = file::delete(emptyTestPath)
var del3: bool, e3: Err::Result = file::delete(newAppPath)

if e1.isOk() && e2.isOk() && e3.isOk() {
  println("All test files cleaned up successfully.")
}

println("\n=========================================================")
println("                     TESTS COMPLETE                      ")
println("=========================================================")
```

### file_features.expect
```
=========================================================
          FLOWWING FILE SYSTEM COMPREHENSIVE TESTS       
=========================================================

--- Test 1: Writing and Reading Static Texts ---
Successfully wrote to file.
Successfully appended to file.
File Contents:
Hello, FlowWing File System!
This is an appended line.

--- Test 2: Checking Existence & Error Handling ---
Does test file exist? true
Does fake file exist? false
Expected Error Caught (Read missing): Error: 
File not found: missing_file_404.txt
Expected Error Caught (Delete missing): Error: 
Cannot delete. File does not exist: missing_file_404.txt

--- Test 3: Stateful Line-by-Line Reading ---
Reading line by line:
Line 1: Hello, FlowWing File System!
Line 2: This is an appended line.
Reached EOF.
File closed successfully.

--- Test 4: Edge Cases - Empty Files & Strings ---
Successfully created empty file.
Read empty file statically. Content length: 0
Expected Error Caught (Read line on empty file): Error: 
EOF

--- Test 5: Edge Cases - Invalid Paths ---
Expected Error Caught (Write to empty path): Error: 
Failed to write to file: 

--- Test 6: Edge Cases - Stateful Class Misuse ---
Expected Error Caught (Read before open): Error: 
Cannot read. File is not open.
Expected Error Caught (Invalid open mode): Error: 
Invalid mode. Use 'r', 'w', or 'a'.
Expected Error Caught (Double open): Error: 
File is already open.
Double close is safe: true
Expected Error Caught (Read after close): Error: 
Cannot read. File is not open.

--- Test 7: Edge Cases - Append to Non-existent File ---
Successfully created new file via append.
Content of appended file: Created via append.

--- Test 8: Cleanup ---
All test files cleaned up successfully.

=========================================================
                     TESTS COMPLETE                      
=========================================================
```

---

# Directory: ModuleTests/11_errors

## Test: module_function_not_found

### module_function_not_found.fg
```javascript
/; EXPECT_ERROR: FunctionNotFound
module [m]

var x: int = 1

println(m::noSuchFun())
```

## Test: module_not_found

### module_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
module [m]

var x: int = 1

println(no_such_module::x)
```

## Test: module_not_found_2

### module_not_found_2.fg
```javascript
/; EXPECT_ERROR: ModuleNotFound
/; External C Declarations linking to the high-performance C Engine

module [fg]

fun strCopy(dest: as str, src: as str) -> as nthg decl/;in use
fun strCompare(str1: as str, str2: as str) -> as int decl/;in use
fun strLength(str1: as str) -> as int decl/;in use
fun strToUpper(str1: as str) -> as str decl/;in use
fun strToLower(str1: as str) -> as str decl/;in use
fun strReverse(str1: as str) -> as str decl/;in use
fun strTrim(str1: as str) -> as str decl/;in use
fun strFind(haystack: as str, needle: as str) -> as str decl/;in use
fun strReplace(str1: as str, oldSub: as str, newSub: as str) -> as str decl/;in use
fun strFindChar(str1: as str, ch: as int) -> as str decl/;in use


/; The Flow Class wraps the string, mutating its state 
/; and always returning 'self' to allow chainable manipulation.
class Str {
  var _buffer: str
  var _len: int

  init(source: str) -> nthg {
    self._buffer = source
    self._len = strLength(source)
  }

  /; Chain: Converts to uppercase via fast C backend
  fun upper() -> FlowingStr::Flow {
    self._buffer = strToUpper(self._buffer)
    return self
  }

  /; Chain: Converts to lowercase via fast C backend
  fun lower() -> FlowingStr::Flow {
    self._buffer = strToLower(self._buffer)
    return self
  }

  /; Chain: Strip whitespaces safely
  fun trim() -> FlowingStr::Flow {
    var res: str = strTrim(self._buffer)
    if (res == "") {
      self._buffer = res
    }
    return self
  }

  /; Chain: Reverse the buffer memory pointers
  fun reverse() -> FlowingStr::Flow {
    self._buffer = strReverse(self._buffer)
    return self
  }

  /; Chain: Replaces substrings in bulk via the 2-pass C function
  fun replace(inout oldSub: str, inout newSub: str) -> FlowingStr::Flow {
    var res: str = strReplace(self._buffer, oldSub, newSub)
    if (res == "") {
      self._buffer = res
    }
    return self
  }

  /; Chain: Concatenates another string onto the buffer
  fun concat(inout addon: str) -> FlowingStr::Flow {
    self._buffer = self._buffer + addon
    return self
  }

  /; Terminal: Finalizes the chain and returns the native string
  fun get() -> str {
    return self._buffer
  }

  /; Terminal: Reads the length of the string
  fun length() -> int {
    return strLength(self._buffer)
  }
}

/; Global initialization factory
fun string(inout source: str) -> FlowingStr::Flow {
  return new FlowingStr::Flow(source)
}/;in use
```

## Test: module_qualified_member_not_found

### module_qualified_member_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
module [m]

var x: int = 1

println(m::y)
```

## Test: module_var_type_mismatch_assign

### module_var_type_mismatch_assign.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
module [m]

var x: int = 0

fun fg_main() -> nthg {
  m::x = "bad"
}
```

---

# Directory: ModuleTests/ModuleImportTestCustomTypes

## Test: local-module

### local-module.fg
```javascript
module [local]


type T = {
    a:int
  }

  var x:local::T

fun fg_main() -> nthg {
  print(local::x)
  }
```

### local-module.expect
```

```

## Test: temp2

### temp2.fg
```javascript
bring local

local::fg_main()
print(local::x)
```

### temp2.expect
```
{ a: 0 }{ a: 0 }
```

---

# Directory: ModuleTests/02_functions

## Test: module_fun_call

### module_fun_call.fg
```javascript
module [lib]

fun getN() -> int {
  return 7
}

println(lib::getN())
```

### module_fun_call.expect
```
7
```

---

# Directory: ModuleTests/04_cross_bring_class

## Test: class_counter_module

### class_counter_module.fg
```javascript
module [cnt]

class Counter {
  var n: int
  fun init(start: int) -> nthg {
    self.n = start
  }
  fun bump() -> int {
    self.n = self.n + 1
    return self.n
  }
}
```

### class_counter_module.expect
```

```

## Test: use_class_from_module

### use_class_from_module.fg
```javascript
bring "class_counter_module.fg"

var c: cnt::Counter = new cnt::Counter(0)
println(c.bump())
println(c.bump())
```

### use_class_from_module.expect
```
1
2
```

---

# Directory: ModuleTests/ModuleImportTestFunctionTest

## Test: local-module

### local-module.fg
```javascript
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T


fun callMe(y:local::T) -> local::T {
  var p:local::T = y

  p.e = true

  return p

  
}

fun fg_main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
```

### local-module.expect
```

```

## Test: temp7

### temp7.fg
```javascript
bring local


print(local::callMe({a:10}))
```

### temp7.expect
```
{ a: 10, b: "", c: 0, d: 0, e: true, f: { a: 0 } }
```

---

# Directory: ModuleTests/ModuleImportTestCustomTypes2

## Test: local-module

### local-module.fg
```javascript
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T

fun fg_main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
```

### local-module.expect
```

```

## Test: temp3

### temp3.fg
```javascript
bring local


var j:local::T = {a:5}


print(j)
```

### temp3.expect
```
{ a: 5, b: "", c: 0, d: 0, e: false, f: null }
```

---

# Directory: ModuleTests/ModuleImportTestFunctionTest2

## Test: local-module

### local-module.fg
```javascript
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T

fun fg_main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
fun callMe(y:local::T) -> local::T {
  var p:local::T = y

  p.e = true
local::fg_main()
  return p

  
}
```

### local-module.expect
```

```

## Test: temp8

### temp8.fg
```javascript
bring local


print(local::callMe({a:10}))
```

### temp8.expect
```
{ a: 0, b: "", c: 0, d: 0, e: false, f: null }{ a: 2, b: "", c: 0, d: 0, e: false, f: null }{ a: 10, b: "", c: 0, d: 0, e: true, f: { a: 0 } }
```

---

# Directory: ModuleTests/ModuleImportTestCustomTypesAssignment2

## Test: local-module

### local-module.fg
```javascript
module [local]


type T = {
    a:int
  }

  var x:local::T

fun fg_main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
```

### local-module.expect
```

```

## Test: temp5

### temp5.fg
```javascript
bring local


local::fg_main()
```

### temp5.expect
```
{ a: 0 }{ a: 2 }
```

---

# Directory: ModuleTests/01_basic

## Test: module_var_access

### module_var_access.fg
```javascript
module [m]

var x: int = 42

println(m::x)
```

### module_var_access.expect
```
42
```

---

# Directory: ModuleTests/ModuleImportTestFunction

## Test: temp2

### temp2.fg
```javascript
bring test2

test2::main2(2,"s")
```

### temp2.expect
```
Printing from Module Test 2s
```

## Test: test2-module

### test2-module.fg
```javascript
module [test2]
  
    var x:int = 2
 
 fun main2(x:int,s:str) -> nthg {
    print("Printing from Module Test "+x+s)
}
```

### test2-module.expect
```

```

---

# Directory: ModuleTests/ModuleImportTestCustomTypesAssignment3

## Test: local-module

### local-module.fg
```javascript
module [local]


type T = {
    a:int
  }

  var x:local::T

fun fg_main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
```

### local-module.expect
```

```

## Test: temp6

### temp6.fg
```javascript
bring local



local::x = {a:3}
print(local::x)
local::fg_main()

local::x = {a:3}
print(local::x)
```

### temp6.expect
```
{ a: 3 }{ a: 0 }{ a: 2 }{ a: 3 }
```

---

# Directory: ModuleTests/ModuleImportTestUsingClassAccess

## Test: local-module

### local-module.fg
```javascript
module [local]


type T ={
    a:int 
  }
var x:int


class A {

  var x:local::T 
  var u:int


  init() -> nthg {

  }
}
```

### local-module.expect
```

```

## Test: temp10

### temp10.fg
```javascript
bring local

var g:local::T = {}
var a:local::A =  new local::A()

print(a.x)
print(a.u)
a.x = {a:21}
print(a.x)
```

### temp10.expect
```
{ a: 0 }0{ a: 21 }
```

---

# Directory: ModuleTests/ModuleImportTestUsingClassAccess3

## Test: local-module

### local-module.fg
```javascript
module [local]


var x:int


class A {

type T ={
    a:int 
  }
  var x:T 
  var u:int


  init() -> nthg {

  }
}
```

### local-module.expect
```

```

## Test: temp12

### temp12.fg
```javascript
bring local
var a:local::A =  new local::A()
print(a.x)
print(a.u)
a.x = {a:21}
print(a.x)
```

### temp12.expect
```
{ a: 0 }0{ a: 21 }
```

---

# Directory: ModuleTests/ModuleImportTestUsingClassAccess4

## Test: local-module

### local-module.fg
```javascript
module [local]


var x:int


class A {

type T ={
    a:int 
  }
  var x:T 
  var u:int


  init() -> nthg {

  }

  printX() -> nthg {
      print(self.x)
    }
}
```

### local-module.expect
```

```

## Test: temp13

### temp13.fg
```javascript
bring local
var a:local::A =  new local::A()
print(a.x)
print(a.u)
a.x = {a:21}
a.printX()
```

### temp13.expect
```
{ a: 0 }0{ a: 21 }
```

---

# Directory: ModuleTests/ModuleImportTestUsingClassAccess2

## Test: local-module

### local-module.fg
```javascript
module [local]


var x:int


class A {

type T ={
    a:int 
  }
  var x:T 
  var u:int


  init() -> nthg {

  }
}
```

### local-module.expect
```

```

## Test: temp11

### temp11.fg
```javascript
bring local

var a:local::A =  new local::A()

print(a.x)
print(a.u)
a.x = {a:21}
print(a.x)
```

### temp11.expect
```
{ a: 0 }0{ a: 21 }
```

---

# Directory: ModuleTests/ModuleImportTestCustomTypesAssignment

## Test: local-module

### local-module.fg
```javascript
module [local]


type T = {
    a:int
  }

  var x:local::T

fun fg_main() -> nthg {
  local::x = {a:2}
print(local::x)
}
```

### local-module.expect
```

```

## Test: temp4

### temp4.fg
```javascript
bring local


local::fg_main()
```

### temp4.expect
```
{ a: 2 }
```

---

# Directory: ModuleTests/03_edge_cases

## Test: module_for_counter

### module_for_counter.fg
```javascript
module [acc]

var total: int = 0

fun add(n: int) -> nthg {
  acc::total = acc::total + n
}
```

### module_for_counter.expect
```

```

## Test: module_two_functions

### module_two_functions.fg
```javascript
module [maths]

fun triple(x: int) -> int {
  return x * 3
}

fun addThenTriple(a: int, b: int) -> int {
  return triple(a + b)
}
```

### module_two_functions.expect
```

```

## Test: module_var_twice_and_arithmetic

### module_var_twice_and_arithmetic.fg
```javascript
module [m]

var n: int = 5

println(m::n + 1)
println(m::n)
```

### module_var_twice_and_arithmetic.expect
```
6
5
```

## Test: use_module_chained_math

### use_module_chained_math.fg
```javascript
bring "module_two_functions.fg"

println(maths::addThenTriple(1, 2))
```

### use_module_chained_math.expect
```
9
```

## Test: use_module_for_accumulator

### use_module_for_accumulator.fg
```javascript
bring "module_for_counter.fg"

for (var i: int = 1 to 4) {
  acc::add(i)
}
println(acc::total)
```

### use_module_for_accumulator.expect
```
10
```

---

# Directory: ModuleTests/ModuleImportTest

## Test: temp1

### temp1.fg
```javascript
bring test
    print(test::x)
```

### temp1.expect
```
2
```

## Test: test-module

### test-module.fg
```javascript
module [test]
  
    var x:int = 2
```

### test-module.expect
```

```

---

# Directory: ModuleTests/ModuleImportTestUsingClass

## Test: local-module

### local-module.fg
```javascript
module [local]


type T ={
    a:int 
  }
var x:int


class A {

  var x:local::T 
  var u:int


  init() -> nthg {

  }
}


var g:local::T = {}

fun fg_main()-> nthg {
var a:local::A =  new local::A()
print(a.u)
a.x = {a:100}

print(a.x)

}
```

### local-module.expect
```

```

## Test: temp9

### temp9.fg
```javascript
bring local


local::fg_main()
```

### temp9.expect
```
0{ a: 100 }
```

---

# Directory: VariableDeclarationTests/char

## Test: basic

### basic.fg
```javascript
var x:char = 'a'
print(x, "\n")
```

### basic.expect
```
a
```

## Test: digit

### digit.fg
```javascript
var x:char = '9'
print(x, "\n")
```

### digit.expect
```
9
```

## Test: special

### special.fg
```javascript
var x:char = '@'
print(x, "\n")
```

### special.expect
```
@
```

## Test: uppercase

### uppercase.fg
```javascript
var x:char = 'Z'
print(x, "\n")
```

### uppercase.expect
```
Z
```

---

# Directory: VariableDeclarationTests/uninitialized

## Test: assignment_after

### assignment_after.fg
```javascript
var x:int
print(x, "\n")
x = 42
print(x, "\n")
```

### assignment_after.expect
```
0
42
```

## Test: bool

### bool.fg
```javascript
var x:bool
print(x, "\n")
```

### bool.expect
```
false
```

## Test: char

### char.fg
```javascript
var x:char
print(x, "\n")
```

### char.expect
```

```

## Test: deci

### deci.fg
```javascript
var x:deci
print(x, "\n")
```

### deci.expect
```
0
```

## Test: deci32

### deci32.fg
```javascript
var x:deci32
print(x, "\n")
```

### deci32.expect
```
0
```

## Test: in_expression

### in_expression.fg
```javascript
var x:int
var y:int
print(x + y, "\n")
x = 10
y = 20
print(x + y, "\n")
```

### in_expression.expect
```
0
30
```

## Test: int32

### int32.fg
```javascript
var x:int
print(x, "\n")
```

### int32.expect
```
0
```

## Test: int64

### int64.fg
```javascript
var x:int64
print(x, "\n")
```

### int64.expect
```
0
```

## Test: int8

### int8.fg
```javascript
var x:int8
print(x, "\n")
```

### int8.expect
```
0
```

## Test: multiple

### multiple.fg
```javascript
var x:int8
var y:int
var z:deci
var w:bool
print(x, " ", y, " ", z, " ", w, "\n")
```

### multiple.expect
```
0 0 0 false
```

## Test: str

### str.fg
```javascript
var x:str
print(x, "\n")
```

### str.expect
```

```

---

# Directory: VariableDeclarationTests/reassignment

## Test: bool

### bool.fg
```javascript
var x:bool = true
print(x, "\n")
x = false
print(x, "\n")
x = true
print(x, "\n")
```

### bool.expect
```
true
false
true
```

## Test: char

### char.fg
```javascript
var x:char = 'a'
print(x, "\n")
x = 'b'
print(x, "\n")
x = 'c'
print(x, "\n")
```

### char.expect
```
a
b
c
```

## Test: deci

### deci.fg
```javascript
var x:deci = 1.1
print(x, "\n")
x = 2.2
print(x, "\n")
x = 3.3
print(x, "\n")
```

### deci.expect
```
1.1
2.2
3.3
```

## Test: deci32

### deci32.fg
```javascript
var x:deci32 = 1.5f
print(x, "\n")
x = 2.5f
print(x, "\n")
x = 3.5f
print(x, "\n")
```

### deci32.expect
```
1.5
2.5
3.5
```

## Test: int32

### int32.fg
```javascript
var x:int = 100
print(x, "\n")
x = 200
print(x, "\n")
x = 300
print(x, "\n")
```

### int32.expect
```
100
200
300
```

## Test: int64

### int64.fg
```javascript
var x:int64 = 1000l
print(x, "\n")
x = 2000l
print(x, "\n")
x = 3000l
print(x, "\n")
```

### int64.expect
```
1000
2000
3000
```

## Test: int8

### int8.fg
```javascript
var x:int8 = 10
print(x, "\n")
x = 20
print(x, "\n")
x = 30
print(x, "\n")
```

### int8.expect
```
10
20
30
```

## Test: str

### str.fg
```javascript
var x:str = "First"
print(x, "\n")
x = "Second"
print(x, "\n")
x = "Third"
print(x, "\n")
```

### str.expect
```
First
Second
Third
```

---

# Directory: VariableDeclarationTests/int32

## Test: basic

### basic.fg
```javascript
var x:int = 1000
print(x, "\n")
```

### basic.expect
```
1000
```

## Test: boundary_max

### boundary_max.fg
```javascript
var x:int = 2147483647
print(x, "\n")
```

### boundary_max.expect
```
2147483647
```

## Test: from_int8_literal

### from_int8_literal.fg
```javascript
var x:int = 5
print(x, "\n")
```

### from_int8_literal.expect
```
5
```

## Test: negative

### negative.fg
```javascript
var x:int = -50000
print(x, "\n")
```

### negative.expect
```
-50000
```

---

# Directory: VariableDeclarationTests/edge_cases

## Test: assignment_chained

### assignment_chained.fg
```javascript
var x:int = 10
var y:int = 20
var z:int = 30
z = y
y = x
x = 100
print(x, " ", y, " ", z, "\n")
```

### assignment_chained.expect
```
100 10 20
```

## Test: assignment_char_to_str

### assignment_char_to_str.fg
```javascript
var x:str = "Hello"
x = 'a'
print(x, "\n")
```

### assignment_char_to_str.expect
```
a
```

## Test: assignment_char_to_str_multiple

### assignment_char_to_str_multiple.fg
```javascript
var x:str = "Hello"
var y:str = "World"
x = 'a'
y = 'b'
print(x, " ", y, "\n")
```

### assignment_char_to_str_multiple.expect
```
a b
```

## Test: assignment_in_scope

### assignment_in_scope.fg
```javascript
var x:int = 10
{
  x = 20
  print(x, "\n")
}
print(x, "\n")
```

### assignment_in_scope.expect
```
20
20
```

## Test: assignment_multiple_types

### assignment_multiple_types.fg
```javascript
var a:int8 = 10
var b:int = 100
var c:int64 = 1000l
var d:deci = 1.1
var e:bool = true
var f:str = "Hello"
var g:char = 'a'
a = 20
b = 200
c = 2000l
d = 2.2
e = false
f = "World"
g = 'b'
print(a, " ", b, " ", c, " ", d, " ", e, " ", f, " ", g, "\n")
```

### assignment_multiple_types.expect
```
20 200 2000 2.2 false World b
```

## Test: assignment_self

### assignment_self.fg
```javascript
var x:int = 10
x = x
print(x, "\n")
x = x + 1
print(x, "\n")
```

### assignment_self.expect
```
10
11
```

## Test: assignment_type_promotion_char_to_str

### assignment_type_promotion_char_to_str.fg
```javascript
var x:str = "Hello"
var y:char = 'a'
x = y
print(x, "\n")
```

### assignment_type_promotion_char_to_str.expect
```
a
```

## Test: assignment_type_promotion_deci32_to_deci

### assignment_type_promotion_deci32_to_deci.fg
```javascript
var x:deci = 3.14
var y:deci32 = 2.5f
x = y
print(x, "\n")
```

### assignment_type_promotion_deci32_to_deci.expect
```
2.5
```

## Test: assignment_type_promotion_int32_to_int64

### assignment_type_promotion_int32_to_int64.fg
```javascript
var x:int64 = 1000l
var y:int = 500
x = y
print(x, "\n")
```

### assignment_type_promotion_int32_to_int64.expect
```
500
```

## Test: assignment_type_promotion_int8_to_int32

### assignment_type_promotion_int8_to_int32.fg
```javascript
var x:int = 100
var y:int8 = 50
x = y
print(x, "\n")
```

### assignment_type_promotion_int8_to_int32.expect
```
50
```

## Test: assignment_type_promotion_int8_to_int64

### assignment_type_promotion_int8_to_int64.fg
```javascript
var x:int64 = 1000l
var y:int8 = 50
x = y
print(x, "\n")
```

### assignment_type_promotion_int8_to_int64.expect
```
50
```

## Test: assignment_with_expression

### assignment_with_expression.fg
```javascript
var x:int = 10
var y:int = 20
x = y + 5
print(x, "\n")
```

### assignment_with_expression.expect
```
25
```

## Test: assignment_with_function_call

### assignment_with_function_call.fg
```javascript
var x:str = "Test"
x = String(42)
print(x, "\n")
```

### assignment_with_function_call.expect
```
42
```

## Test: assignment_with_unary

### assignment_with_unary.fg
```javascript
var x:int = 10
x = -x
print(x, "\n")
x = -x
print(x, "\n")
```

### assignment_with_unary.expect
```
-10
10
```

## Test: multiple_uninitialized

### multiple_uninitialized.fg
```javascript
var a:int
var b:int
var c:int
print(a, " ", b, " ", c, "\n")
a = 1
b = 2
c = 3
print(a, " ", b, " ", c, "\n")
```

### multiple_uninitialized.expect
```
0 0 0
1 2 3
```

## Test: scope_access

### scope_access.fg
```javascript
{
  var x:int = 10
  print(x, "\n")
}
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
```

## Test: shadowing

### shadowing.fg
```javascript
var x:int = 10
print(x, "\n")
{
  var x:int = 20
  print(x, "\n")
}
print(x, "\n")
```

### shadowing.expect
```
10
20
10
```

## Test: uninitialized_bool_logic

### uninitialized_bool_logic.fg
```javascript
var x:bool
var y:bool = true
print(x && y, "\n")
print(x || y, "\n")
print(!x, "\n")
```

### uninitialized_bool_logic.expect
```
false
true
true
```

## Test: uninitialized_decimal_operations

### uninitialized_decimal_operations.fg
```javascript
var x:deci
var y:deci32
print(x, " ", y, "\n")
x = 3.14
y = 2.5f
print(x, " ", y, "\n")
```

### uninitialized_decimal_operations.expect
```
0 0
3.14 2.5
```

## Test: uninitialized_in_arithmetic

### uninitialized_in_arithmetic.fg
```javascript
var x:int
var y:int
var z:int = x + y
print(z, "\n")
x = 10
y = 20
z = x + y
print(z, "\n")
```

### uninitialized_in_arithmetic.expect
```
0
30
```

## Test: uninitialized_in_comparison

### uninitialized_in_comparison.fg
```javascript
var x:int
var y:int = 5
print(x < y, "\n")
print(x == 0, "\n")
```

### uninitialized_in_comparison.expect
```
true
true
```

## Test: uninitialized_in_scope

### uninitialized_in_scope.fg
```javascript
{
  var x:int
  print(x, "\n")
  x = 42
  print(x, "\n")
}
```

### uninitialized_in_scope.expect
```
0
42
```

## Test: uninitialized_in_string_concat

### uninitialized_in_string_concat.fg
```javascript
var x:int
var y:str
print("x=", x, " y=", y, "\n")
```

### uninitialized_in_string_concat.expect
```
x=0 y=
```

## Test: uninitialized_shadowing

### uninitialized_shadowing.fg
```javascript
var x:int = 10
print(x, "\n")
{
  var x:int
  print(x, "\n")
  x = 20
  print(x, "\n")
}
print(x, "\n")
```

### uninitialized_shadowing.expect
```
10
0
20
10
```

## Test: uninitialized_with_initialized

### uninitialized_with_initialized.fg
```javascript
var x:int
var y:int = 100
var z:int
print(x, " ", y, " ", z, "\n")
```

### uninitialized_with_initialized.expect
```
0 100 0
```

## Test: uninitialized_with_type_conversion

### uninitialized_with_type_conversion.fg
```javascript
var x:int
var y:str = String(x)
print(y, "\n")
```

### uninitialized_with_type_conversion.expect
```
0
```

---

# Directory: VariableDeclarationTests/assignment

## Test: bool

### bool.fg
```javascript
var x:bool
x = true
print(x, "\n")
x = false
print(x, "\n")
```

### bool.expect
```
true
false
```

## Test: char

### char.fg
```javascript
var x:char
x = 'a'
print(x, "\n")
```

### char.expect
```
a
```

## Test: deci

### deci.fg
```javascript
var x:deci
x = 3.14
print(x, "\n")
```

### deci.expect
```
3.14
```

## Test: deci32

### deci32.fg
```javascript
var x:deci32
x = 2.5f
print(x, "\n")
```

### deci32.expect
```
2.5
```

## Test: int32

### int32.fg
```javascript
var x:int
x = 100
print(x, "\n")
```

### int32.expect
```
100
```

## Test: int64

### int64.fg
```javascript
var x:int64
x = 1000l
print(x, "\n")
```

### int64.expect
```
1000
```

## Test: int8

### int8.fg
```javascript
var x:int8
x = 42
print(x, "\n")
```

### int8.expect
```
42
```

## Test: str

### str.fg
```javascript
var x:str
x = "Hello"
print(x, "\n")
```

### str.expect
```
Hello
```

---

# Directory: VariableDeclarationTests/deci

## Test: basic

### basic.fg
```javascript
var x:deci = 5.2
print(x, "\n")
```

### basic.expect
```
5.2
```

## Test: from_deci32

### from_deci32.fg
```javascript
var x:deci = 5.2f
print(x, "\n")
```

### from_deci32.expect
```
5.199999809265137
```

## Test: negative

### negative.fg
```javascript
var x:deci = -123.456
print(x, "\n")
```

### negative.expect
```
-123.456000000000003
```

## Test: scientific

### scientific.fg
```javascript
var x:deci = 1e10
print(x, "\n")
```

### scientific.expect
```
10000000000
```

---

# Directory: VariableDeclarationTests/scope

## Test: all_types_global

### all_types_global.fg
```javascript
var a:int8 = 10
var b:int = 100
var c:int64 = 1000l
var d:deci = 1.1
var e:bool = true
var f:str = "Hello"
var g:char = 'a'
print(a, " ", b, " ", c, " ", d, " ", e, " ", f, " ", g, "\n")
{
  print(a, " ", b, " ", c, " ", d, " ", e, " ", f, " ", g, "\n")
}
```

### all_types_global.expect
```
10 100 1000 1.1 true Hello a
10 100 1000 1.1 true Hello a
```

## Test: all_types_local

### all_types_local.fg
```javascript
{
  var a:int8 = 10
  var b:int = 100
  var c:int64 = 1000l
  var d:deci = 1.1
  var e:bool = true
  var f:str = "Hello"
  var g:char = 'a'
  print(a, " ", b, " ", c, " ", d, " ", e, " ", f, " ", g, "\n")
}
```

### all_types_local.expect
```
10 100 1000 1.1 true Hello a
```

## Test: expression_with_global

### expression_with_global.fg
```javascript
var x:int = 10
var y:int = 20
{
  var z:int = x + y
  print(z, "\n")
  x = 100
  z = x + y
  print(z, "\n")
}
```

### expression_with_global.expect
```
30
120
```

## Test: global_access_from_local

### global_access_from_local.fg
```javascript
var x:int = 100
{
  print(x, "\n")
}
```

### global_access_from_local.expect
```
100
```

## Test: global_assignment_from_local

### global_assignment_from_local.fg
```javascript
var x:int = 100
print(x, "\n")
{
  x = 200
  print(x, "\n")
}
print(x, "\n")
```

### global_assignment_from_local.expect
```
100
200
200
```

## Test: global_shadowing

### global_shadowing.fg
```javascript
var x:int = 100
print(x, "\n")
{
  var x:int = 200
  print(x, "\n")
}
print(x, "\n")
```

### global_shadowing.expect
```
100
200
100
```

## Test: global_with_local_mixed

### global_with_local_mixed.fg
```javascript
var x:int = 100
var y:int = 200
print(x, " ", y, "\n")
{
  var y:int = 300
  var z:int = 400
  print(x, " ", y, " ", z, "\n")
  x = 150
  print(x, " ", y, " ", z, "\n")
}
print(x, " ", y, "\n")
```

### global_with_local_mixed.expect
```
100 200
100 300 400
150 300 400
150 200
```

## Test: local_only

### local_only.fg
```javascript
{
  var x:int = 100
  print(x, "\n")
  x = 200
  print(x, "\n")
}
```

### local_only.expect
```
100
200
```

## Test: local_shadowing_assignment

### local_shadowing_assignment.fg
```javascript
var x:int = 100
print(x, "\n")
{
  var x:int = 200
  print(x, "\n")
  x = 300
  print(x, "\n")
}
print(x, "\n")
```

### local_shadowing_assignment.expect
```
100
200
300
100
```

## Test: multiple_globals

### multiple_globals.fg
```javascript
var a:int = 10
var b:int = 20
var c:int = 30
print(a, " ", b, " ", c, "\n")
{
  print(a, " ", b, " ", c, "\n")
  a = 100
  b = 200
  c = 300
  print(a, " ", b, " ", c, "\n")
}
print(a, " ", b, " ", c, "\n")
```

### multiple_globals.expect
```
10 20 30
10 20 30
100 200 300
100 200 300
```

## Test: multiple_nested

### multiple_nested.fg
```javascript
var a:int = 1
{
  var b:int = 2
  print(a, " ", b, "\n")
  {
    var c:int = 3
    print(a, " ", b, " ", c, "\n")
    a = 10
    b = 20
    c = 30
    print(a, " ", b, " ", c, "\n")
  }
  print(a, " ", b, "\n")
}
print(a, "\n")
```

### multiple_nested.expect
```
1 2
1 2 3
10 20 30
10 20
10
```

## Test: nested_scopes

### nested_scopes.fg
```javascript
var x:int = 100
print(x, "\n")
{
  var y:int = 200
  print(x, " ", y, "\n")
  {
    var z:int = 300
    print(x, " ", y, " ", z, "\n")
    x = 150
    y = 250
    z = 350
    print(x, " ", y, " ", z, "\n")
  }
  print(x, " ", y, "\n")
}
print(x, "\n")
```

### nested_scopes.expect
```
100
100 200
100 200 300
150 250 350
150 250
150
```

## Test: nested_shadowing

### nested_shadowing.fg
```javascript
var x:int = 100
print(x, "\n")
{
  var x:int = 200
  print(x, "\n")
  {
    var x:int = 300
    print(x, "\n")
  }
  print(x, "\n")
}
print(x, "\n")
```

### nested_shadowing.expect
```
100
200
300
200
100
```

## Test: reassignment_operator_global

### reassignment_operator_global.fg
```javascript
var x:int = 100
print(x, "\n")
{
  x <- 200
  print(x, "\n")
}
print(x, "\n")
```

### reassignment_operator_global.expect
```
100
200
200
```

## Test: reassignment_operator_local

### reassignment_operator_local.fg
```javascript
{
  var x:int = 100
  print(x, "\n")
  x <- 200
  print(x, "\n")
}
```

### reassignment_operator_local.expect
```
100
200
```

## Test: reassignment_operator_shadowing

### reassignment_operator_shadowing.fg
```javascript
var x:int = 100
print(x, "\n")
{
  var x:int = 200
  print(x, "\n")
  x <- 300
  print(x, "\n")
}
print(x, "\n")
```

### reassignment_operator_shadowing.expect
```
100
200
300
100
```

## Test: uninitialized_global

### uninitialized_global.fg
```javascript
var x:int
print(x, "\n")
{
  x = 100
  print(x, "\n")
}
print(x, "\n")
```

### uninitialized_global.expect
```
0
100
100
```

## Test: uninitialized_local

### uninitialized_local.fg
```javascript
{
  var x:int
  print(x, "\n")
  x = 100
  print(x, "\n")
}
```

### uninitialized_local.expect
```
0
100
```

---

# Directory: VariableDeclarationTests/reassignment_operator

## Test: bool

### bool.fg
```javascript
var x:bool = true
print(x, "\n")
x <- false
print(x, "\n")
x <- true
print(x, "\n")
```

### bool.expect
```
true
false
true
```

## Test: char

### char.fg
```javascript
var x:char = 'a'
print(x, "\n")
x <- 'b'
print(x, "\n")
```

### char.expect
```
a
b
```

## Test: deci

### deci.fg
```javascript
var x:deci = 1.1
print(x, "\n")
x <- 2.2
print(x, "\n")
```

### deci.expect
```
1.1
2.2
```

## Test: deci32

### deci32.fg
```javascript
var x:deci32 = 1.5f
print(x, "\n")
x <- 2.5f
print(x, "\n")
```

### deci32.expect
```
1.5
2.5
```

## Test: int32

### int32.fg
```javascript
var x:int = 100
print(x, "\n")
x <- 200
print(x, "\n")
```

### int32.expect
```
100
200
```

## Test: int64

### int64.fg
```javascript
var x:int64 = 1000l
print(x, "\n")
x <- 2000l
print(x, "\n")
```

### int64.expect
```
1000
2000
```

## Test: int8

### int8.fg
```javascript
var x:int8 = 10
print(x, "\n")
x <- 20
print(x, "\n")
```

### int8.expect
```
10
20
```

## Test: str

### str.fg
```javascript
var x:str = "First"
print(x, "\n")
x <- "Second"
print(x, "\n")
```

### str.expect
```
First
Second
```

## Test: type_promotion_char_to_str

### type_promotion_char_to_str.fg
```javascript
var x:str = "Hello"
x <- 'a'
print(x, "\n")
```

### type_promotion_char_to_str.expect
```
a
```

## Test: type_promotion_int8_to_int32

### type_promotion_int8_to_int32.fg
```javascript
var x:int = 100
var y:int8 = 50
x <- y
print(x, "\n")
```

### type_promotion_int8_to_int32.expect
```
50
```

## Test: uninitialized

### uninitialized.fg
```javascript
var x:int = 10
print(x, "\n")
var y:int
y <- 20
print(y, "\n")
```

### uninitialized.expect
```
10
20
```

## Test: with_expression

### with_expression.fg
```javascript
var x:int = 10
var y:int = 20
x <- y + 5
print(x, "\n")
```

### with_expression.expect
```
25
```

---

# Directory: VariableDeclarationTests/deci32

## Test: basic

### basic.fg
```javascript
var x:deci32 = 5.2f
print(x, "\n")
```

### basic.expect
```
5.1999998
```

## Test: negative

### negative.fg
```javascript
var x:deci32 = -3.14f
print(x, "\n")
```

### negative.expect
```
-3.1400001
```

## Test: scientific

### scientific.fg
```javascript
var x:deci32 = 1.5e3f
print(x, "\n")
```

### scientific.expect
```
1500
```

---

# Directory: VariableDeclarationTests/bool

## Test: false

### false.fg
```javascript
var x:bool = false
print(x, "\n")
```

### false.expect
```
false
```

## Test: from_expression

### from_expression.fg
```javascript
var x:bool = 5 > 3
print(x, "\n")
```

### from_expression.expect
```
true
```

## Test: logical_and

### logical_and.fg
```javascript
var x:bool = true && true
print(x, "\n")
```

### logical_and.expect
```
true
```

## Test: logical_or

### logical_or.fg
```javascript
var x:bool = true || false
print(x, "\n")
```

### logical_or.expect
```
true
```

## Test: true

### true.fg
```javascript
var x:bool = true
print(x, "\n")
```

### true.expect
```
true
```

---

# Directory: VariableDeclarationTests/type_promotion

## Test: char_to_str

### char_to_str.fg
```javascript
var x:str = 'a'
print(x, "\n")
```

### char_to_str.expect
```
a
```

## Test: deci32_to_deci

### deci32_to_deci.fg
```javascript
var x:deci = 3.14f
print(x, "\n")
```

### deci32_to_deci.expect
```
3.140000104904175
```

## Test: int32_to_int64

### int32_to_int64.fg
```javascript
var x:int64 = 100000
print(x, "\n")
```

### int32_to_int64.expect
```
100000
```

## Test: int8_to_int32

### int8_to_int32.fg
```javascript
var x:int = 5
print(x, "\n")
```

### int8_to_int32.expect
```
5
```

## Test: int8_to_int64

### int8_to_int64.fg
```javascript
var x:int64 = 5
print(x, "\n")
```

### int8_to_int64.expect
```
5
```

## Test: negative_int8_to_int32

### negative_int8_to_int32.fg
```javascript
var x:int = -50
print(x, "\n")
```

### negative_int8_to_int32.expect
```
-50
```

## Test: negative_int8_to_int64

### negative_int8_to_int64.fg
```javascript
var x:int64 = -100
print(x, "\n")
```

### negative_int8_to_int64.expect
```
-100
```

---

# Directory: VariableDeclarationTests/int8

## Test: basic

### basic.fg
```javascript
var x:int8 = 5
print(x, "\n")
```

### basic.expect
```
5
```

## Test: boundary_max

### boundary_max.fg
```javascript
var x:int8 = 127
print(x, "\n")
```

### boundary_max.expect
```
127
```

## Test: boundary_min

### boundary_min.fg
```javascript
var x:int8 = -128
print(x, "\n")
```

### boundary_min.expect
```
-128
```

## Test: negative

### negative.fg
```javascript
var x:int8 = -100
print(x, "\n")
```

### negative.expect
```
-100
```

---

# Directory: VariableDeclarationTests/string

## Test: basic

### basic.fg
```javascript
var x:str = "Hello"
print(x, "\n")
```

### basic.expect
```
Hello
```

## Test: concat_with_int

### concat_with_int.fg
```javascript
var x:str = "Value: " + 42
print(x, "\n")
```

### concat_with_int.expect
```
Value: 42
```

## Test: concatenation

### concatenation.fg
```javascript
var x:str = "Hello" + "World"
print(x, "\n")
```

### concatenation.expect
```
HelloWorld
```

## Test: empty

### empty.fg
```javascript
var x:str = ""
print(x, "end\n")
```

### empty.expect
```
end
```

## Test: from_String_int

### from_String_int.fg
```javascript
var x:str = String(10)
print(x, "\n")
```

### from_String_int.expect
```
10
```

## Test: from_char

### from_char.fg
```javascript
var x:str = 'a'
print(x, "\n")
```

### from_char.expect
```
a
```

---

# Directory: VariableDeclarationTests/errors

## Test: assignment_count_mismatch_one_to_two

### assignment_count_mismatch_one_to_two.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
var x:int = 10
var y:int = 20
x = 30, 40
```

## Test: assignment_count_mismatch_three_to_two

### assignment_count_mismatch_three_to_two.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
var x:int = 10
var y:int = 20
var z:int = 30
x, y, z = 40, 50
```

## Test: assignment_count_mismatch_two_to_one

### assignment_count_mismatch_two_to_one.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
var x:int = 10
var y:int = 20
x, y = 30
```

## Test: assignment_count_mismatch_two_to_three

### assignment_count_mismatch_two_to_three.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
var x:int = 10
var y:int = 20
x, y = 30, 40, 50
```

## Test: assignment_to_const_bool

### assignment_to_const_bool.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:bool = true
x = false
```

## Test: assignment_to_const_char

### assignment_to_const_char.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:char = 'a'
x = 'b'
```

## Test: assignment_to_const_deci

### assignment_to_const_deci.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:deci = 1.1
x = 2.2
```

## Test: assignment_to_const_deci32

### assignment_to_const_deci32.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:deci32 = 1.5f
x = 2.5f
```

## Test: assignment_to_const_in_scope

### assignment_to_const_in_scope.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int = 10
{
  x = 20
}
```

## Test: assignment_to_const_int32

### assignment_to_const_int32.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int = 10
x = 20
```

## Test: assignment_to_const_int64

### assignment_to_const_int64.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int64 = 10l
x = 20l
```

## Test: assignment_to_const_int8

### assignment_to_const_int8.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int8 = 10
x = 20
```

## Test: assignment_to_const_str

### assignment_to_const_str.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:str = "Hello"
x = "World"
```

## Test: assignment_to_non_lvalue_bool

### assignment_to_non_lvalue_bool.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
true = false
```

## Test: assignment_to_non_lvalue_char

### assignment_to_non_lvalue_char.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
var x:char = 'a'
'b' = x
```

## Test: assignment_to_non_lvalue_expression

### assignment_to_non_lvalue_expression.fg
```javascript
/; EXPECT_ERROR: UnexpectedExpression
var x:int = 10
var y:int = 20
(x + y) = 30
```

## Test: assignment_to_non_lvalue_literal

### assignment_to_non_lvalue_literal.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
var x:int = 10
print(x, "\n")
5 = x
```

## Test: assignment_to_non_lvalue_number

### assignment_to_non_lvalue_number.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
var x:int = 10
42 = x
```

## Test: assignment_to_non_lvalue_string

### assignment_to_non_lvalue_string.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
"Hello" = "World"
```

## Test: assignment_type_mismatch_bool_to_int

### assignment_type_mismatch_bool_to_int.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int = 10
x = true
```

## Test: assignment_type_mismatch_deci_to_deci32

### assignment_type_mismatch_deci_to_deci32.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:deci32 = 1.5f
x = 2.5
```

## Test: assignment_type_mismatch_deci_to_int

### assignment_type_mismatch_deci_to_int.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int = 10
x = 2.5
```

## Test: assignment_type_mismatch_int32_to_int8

### assignment_type_mismatch_int32_to_int8.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int8 = 5
x = 200
```

## Test: assignment_type_mismatch_int64_to_int32

### assignment_type_mismatch_int64_to_int32.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int = 10
x = 10000000000l
```

## Test: assignment_type_mismatch_int64_to_int8

### assignment_type_mismatch_int64_to_int8.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int8 = 5
x = 10000000000l
```

## Test: assignment_type_mismatch_int_to_bool

### assignment_type_mismatch_int_to_bool.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:bool = true
x = 42
```

## Test: assignment_type_mismatch_int_to_str

### assignment_type_mismatch_int_to_str.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:str = "Hello"
x = 42
```

## Test: assignment_type_mismatch_str_to_char

### assignment_type_mismatch_str_to_char.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:char = 'a'
x = "hello"
```

## Test: assignment_type_mismatch_str_to_int

### assignment_type_mismatch_str_to_int.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int = 10
x = "Hello"
```

## Test: bool_addition

### bool_addition.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
var x:bool = true + false
```

## Test: bool_to_int

### bool_to_int.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:int = true
```

## Test: deci_to_deci32

### deci_to_deci32.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:deci32 = 5.2
```

## Test: deci_to_int

### deci_to_int.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:int = 5.5
```

## Test: int32_to_int8

### int32_to_int8.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:int8 = 1000
```

## Test: int64_to_int32

### int64_to_int32.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:int = 5l
```

## Test: int64_to_int8

### int64_to_int8.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:int8 = 5l
```

## Test: int_to_bool

### int_to_bool.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:bool = 5
```

## Test: int_to_str

### int_to_str.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:str = 5
```

## Test: reassignment_count_mismatch

### reassignment_count_mismatch.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
var x:int = 10
var y:int = 20
x, y <- 30
```

## Test: reassignment_to_const_bool

### reassignment_to_const_bool.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:bool = true
x <- false
```

## Test: reassignment_to_const_char

### reassignment_to_const_char.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:char = 'a'
x <- 'b'
```

## Test: reassignment_to_const_deci

### reassignment_to_const_deci.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:deci = 1.1
x <- 2.2
```

## Test: reassignment_to_const_deci32

### reassignment_to_const_deci32.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:deci32 = 1.5f
x <- 2.5f
```

## Test: reassignment_to_const_int32

### reassignment_to_const_int32.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int = 10
x <- 20
```

## Test: reassignment_to_const_int64

### reassignment_to_const_int64.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int64 = 10l
x <- 20l
```

## Test: reassignment_to_const_int8

### reassignment_to_const_int8.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int8 = 10
x <- 20
```

## Test: reassignment_to_const_str

### reassignment_to_const_str.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:str = "Hello"
x <- "World"
```

## Test: reassignment_to_non_lvalue

### reassignment_to_non_lvalue.fg
```javascript
/; EXPECT_ERROR: AssignmentToNonLValue
var x:int = 10
5 <- x
```

## Test: reassignment_type_mismatch_int32_to_int8

### reassignment_type_mismatch_int32_to_int8.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int8 = 5
x <- 200
```

## Test: reassignment_type_mismatch_int64_to_int32

### reassignment_type_mismatch_int64_to_int32.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int = 10
x <- 10000000000l
```

## Test: reassignment_type_mismatch_int_to_str

### reassignment_type_mismatch_int_to_str.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:str = "Hello"
x <- 42
```

## Test: reassignment_type_mismatch_str_to_int

### reassignment_type_mismatch_str_to_int.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
var x:int = 10
x <- "Hello"
```

## Test: scope_assignment_to_local_outside

### scope_assignment_to_local_outside.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
{
  var x:int = 100
}
x = 200
```

## Test: scope_local_access_outside

### scope_local_access_outside.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
{
  var x:int = 100
}
print(x, "\n")
```

## Test: scope_reassignment_to_local_outside

### scope_reassignment_to_local_outside.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
{
  var x:int = 100
}
x <- 200
```

## Test: str_to_char

### str_to_char.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:char = "hello"
```

## Test: str_to_int

### str_to_int.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var x:int = "hello"
```

## Test: uninitialized_use_before_declare_bool

### uninitialized_use_before_declare_bool.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:bool = true
```

## Test: uninitialized_use_before_declare_char

### uninitialized_use_before_declare_char.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:char = 'a'
```

## Test: uninitialized_use_before_declare_deci

### uninitialized_use_before_declare_deci.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:deci = 5.5
```

## Test: uninitialized_use_before_declare_int32

### uninitialized_use_before_declare_int32.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:int = 5
```

## Test: uninitialized_use_before_declare_int64

### uninitialized_use_before_declare_int64.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:int64 = 5l
```

## Test: uninitialized_use_before_declare_int8

### uninitialized_use_before_declare_int8.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:int8 = 5
```

## Test: uninitialized_use_before_declare_str

### uninitialized_use_before_declare_str.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:str = "Hello"
```

## Test: uninitialized_use_in_assignment

### uninitialized_use_in_assignment.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
y = x
var x:int = 10
var y:int = 20
```

## Test: uninitialized_use_in_binary_op

### uninitialized_use_in_binary_op.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var y:int = x * 2
var x:int = 10
```

## Test: uninitialized_use_in_expression

### uninitialized_use_in_expression.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var y:int = x + 5
var x:int = 10
```

## Test: uninitialized_use_in_function_call

### uninitialized_use_in_function_call.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
var x:int = 42
```

## Test: uninitialized_use_in_scope

### uninitialized_use_in_scope.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
{
  print(x, "\n")
}
var x:int = 10
```

## Test: uninitialized_use_in_unary

### uninitialized_use_in_unary.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var y:int = -x
var x:int = 10
```

## Test: uninitialized_use_nested_scope

### uninitialized_use_nested_scope.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
{
  {
    print(x, "\n")
  }
}
var x:int = 10
```

---

# Directory: VariableDeclarationTests/int64

## Test: basic

### basic.fg
```javascript
var x:int64 = 10000000000l
print(x, "\n")
```

### basic.expect
```
10000000000
```

## Test: from_int32_literal

### from_int32_literal.fg
```javascript
var x:int64 = 1000000
print(x, "\n")
```

### from_int32_literal.expect
```
1000000
```

## Test: from_int8_literal

### from_int8_literal.fg
```javascript
var x:int64 = 5
print(x, "\n")
```

### from_int8_literal.expect
```
5
```

## Test: negative

### negative.fg
```javascript
var x:int64 = -9000000000l
print(x, "\n")
```

### negative.expect
```
-9000000000
```

## Test: with_suffix

### with_suffix.fg
```javascript
var x:int64 = 5l
print(x, "\n")
```

### with_suffix.expect
```
5
```

---

# Directory: ConstVariableDeclarationTests/dynamic

## Test: complex_nested

### complex_nested.fg
```javascript
var x = 10
var y = (x + 5) * 2
print(y, "\n")
var z = (x > 5) && (y < 50)
print(z, "\n")
var w = !(x == 10)
print(w, "\n")
```

### complex_nested.expect
```
30
true
false
```

---

# Directory: ConstVariableDeclarationTests/char

## Test: basic

### basic.fg
```javascript
const x:char = 'a'
print(x, "\n")
```

### basic.expect
```
a
```

---

# Directory: ConstVariableDeclarationTests/uninitialized

## Test: bool

### bool.fg
```javascript
const x:bool = false
print(x, "\n")
```

### bool.expect
```
false
```

## Test: char

### char.fg
```javascript
const x:char = '\0'
print(x, "\n")
```

### char.expect
```

```

## Test: deci

### deci.fg
```javascript
const x:deci = 0
print(x, "\n")
```

### deci.expect
```
0
```

## Test: deci32

### deci32.fg
```javascript
const x:deci32 = 0
print(x, "\n")
```

### deci32.expect
```
0
```

## Test: int32

### int32.fg
```javascript
const x:int = 0
print(x, "\n")
```

### int32.expect
```
0
```

## Test: int64

### int64.fg
```javascript
const x:int64 = 0
print(x, "\n")
```

### int64.expect
```
0
```

## Test: int8

### int8.fg
```javascript
const x:int8 = 0
print(x, "\n")
```

### int8.expect
```
0
```

## Test: multiple

### multiple.fg
```javascript
const x:int8 = 0
const y:int = 0
const z:deci = 0
const z2:deci32 = 0
const w:bool = false
const c:char = '\0'
print(x, " ", y, " ", z, " ", z2, " ", w, " ", c, "\n")
```

### multiple.expect
```
0 0 0 0 false
```

## Test: str

### str.fg
```javascript
const x:str = ""
print(x, "\n")
```

### str.expect
```

```

---

# Directory: ConstVariableDeclarationTests/int32

## Test: basic

### basic.fg
```javascript
const x:int = 1000
print(x, "\n")
```

### basic.expect
```
1000
```

## Test: from_int8_literal

### from_int8_literal.fg
```javascript
const x:int = 5
print(x, "\n")
```

### from_int8_literal.expect
```
5
```

## Test: negative

### negative.fg
```javascript
const x:int = -50000
print(x, "\n")
```

### negative.expect
```
-50000
```

---

# Directory: ConstVariableDeclarationTests/edge_cases

## Test: const_in_expression

### const_in_expression.fg
```javascript
const x:int = 10
const y:int = 20
const sum:int = x + y
print(sum, "\n")
```

### const_in_expression.expect
```
30
```

## Test: const_with_function_call

### const_with_function_call.fg
```javascript
const x:str = String(42)
print(x, "\n")
```

### const_with_function_call.expect
```
42
```

## Test: multiple_const

### multiple_const.fg
```javascript
const a:int = 1
const b:int = 2
const c:int = 3
print(a, " ", b, " ", c, "\n")
```

### multiple_const.expect
```
1 2 3
```

## Test: negative_boundary

### negative_boundary.fg
```javascript
const x:int8 = -128
print(x, "\n")
```

### negative_boundary.expect
```
-128
```

## Test: pi_constant

### pi_constant.fg
```javascript
const pi:deci = 3.141592653589793
print(pi, "\n")
```

### pi_constant.expect
```
3.141592653589793
```

## Test: uninitialized_in_scope

### uninitialized_in_scope.fg
```javascript
{
  const x:int = 0
  print(x, "\n")
}
```

### uninitialized_in_scope.expect
```
0
```

## Test: uninitialized_shadowing

### uninitialized_shadowing.fg
```javascript
const x:int = 10
print(x, "\n")
{
  var x:int 
  print(x, "\n")
}
print(x, "\n")
```

### uninitialized_shadowing.expect
```
10
0
10
```

---

# Directory: ConstVariableDeclarationTests/deci

## Test: basic

### basic.fg
```javascript
const x:deci = 5.2
print(x, "\n")
```

### basic.expect
```
5.2
```

## Test: from_deci32

### from_deci32.fg
```javascript
const x:deci = 3.14f
print(x, "\n")
```

### from_deci32.expect
```
3.140000104904175
```

---

# Directory: ConstVariableDeclarationTests/deci32

## Test: basic

### basic.fg
```javascript
const x:deci32 = 5.2f
print(x, "\n")
```

### basic.expect
```
5.1999998
```

## Test: negative

### negative.fg
```javascript
const x:deci32 = -3.14f
print(x, "\n")
```

### negative.expect
```
-3.1400001
```

---

# Directory: ConstVariableDeclarationTests/bool

## Test: false

### false.fg
```javascript
const x:bool = false
print(x, "\n")
```

### false.expect
```
false
```

## Test: from_expression

### from_expression.fg
```javascript
const x:bool = 5 > 3
print(x, "\n")
```

### from_expression.expect
```
true
```

## Test: true

### true.fg
```javascript
const x:bool = true
print(x, "\n")
```

### true.expect
```
true
```

---

# Directory: ConstVariableDeclarationTests/type_promotion

## Test: char_to_str

### char_to_str.fg
```javascript
const x:str = 'a'
print(x, "\n")
```

### char_to_str.expect
```
a
```

## Test: deci32_to_deci

### deci32_to_deci.fg
```javascript
const x:deci = 3.14f
print(x, "\n")
```

### deci32_to_deci.expect
```
3.140000104904175
```

## Test: int8_to_int32

### int8_to_int32.fg
```javascript
const x:int = 5
print(x, "\n")
```

### int8_to_int32.expect
```
5
```

## Test: int8_to_int64

### int8_to_int64.fg
```javascript
const x:int64 = 5
print(x, "\n")
```

### int8_to_int64.expect
```
5
```

---

# Directory: ConstVariableDeclarationTests/int8

## Test: basic

### basic.fg
```javascript
const x:int8 = 5
print(x, "\n")
```

### basic.expect
```
5
```

## Test: boundary_max

### boundary_max.fg
```javascript
const x:int8 = 127
print(x, "\n")
```

### boundary_max.expect
```
127
```

## Test: boundary_min

### boundary_min.fg
```javascript
const x:int8 = -128
print(x, "\n")
```

### boundary_min.expect
```
-128
```

## Test: negative

### negative.fg
```javascript
const x:int8 = -100
print(x, "\n")
```

### negative.expect
```
-100
```

---

# Directory: ConstVariableDeclarationTests/string

## Test: basic

### basic.fg
```javascript
const x:str = "Hello"
print(x, "\n")
```

### basic.expect
```
Hello
```

## Test: concatenation

### concatenation.fg
```javascript
const x:str = "Hello" + "World"
print(x, "\n")
```

### concatenation.expect
```
HelloWorld
```

## Test: from_char

### from_char.fg
```javascript
const x:str = 'a'
print(x, "\n")
```

### from_char.expect
```
a
```

---

# Directory: ConstVariableDeclarationTests/errors

## Test: bool_addition

### bool_addition.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
const x:bool = true + false
```

## Test: bool_to_int

### bool_to_int.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int = true
```

## Test: const_and_var_same_name

### const_and_var_same_name.fg
```javascript
/; EXPECT_ERROR: VariableAlreadyDeclared
const x:int = 5
var x:int = 10
```

## Test: const_redeclaration

### const_redeclaration.fg
```javascript
/; EXPECT_ERROR: VariableAlreadyDeclared
const x:int = 5
const x:int = 10
```

## Test: deci_to_deci32

### deci_to_deci32.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:deci32 = 5.2
```

## Test: deci_to_int

### deci_to_int.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int = 5.5
```

## Test: int32_to_int8

### int32_to_int8.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int8 = 1000
```

## Test: int64_to_int32

### int64_to_int32.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int = 5l
```

## Test: int64_to_int8

### int64_to_int8.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int8 = 5l
```

## Test: int_to_bool

### int_to_bool.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:bool = 5
```

## Test: int_to_str

### int_to_str.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:str = 5
```

## Test: str_to_char

### str_to_char.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:char = "hello"
```

## Test: str_to_int

### str_to_int.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int = "hello"
```

## Test: uninitialized_use_before_declare

### uninitialized_use_before_declare.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
const x:int = 5
```

## Test: uninitialized_use_before_declare_char

### uninitialized_use_before_declare_char.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
const x:char = 'a'
```

## Test: uninitialized_use_before_declare_deci32

### uninitialized_use_before_declare_deci32.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
const x:deci32 = 5.2f
```

## Test: uninitialized_use_before_declare_int8

### uninitialized_use_before_declare_int8.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
const x:int8 = 5
```

## Test: uninitialized_use_before_declare_str

### uninitialized_use_before_declare_str.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
print(x, "\n")
const x:str = "Hello"
```

## Test: uninitialized_use_in_expression

### uninitialized_use_in_expression.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
const y:int = x + 5
const x:int = 10
```

---

# Directory: ConstVariableDeclarationTests/int64

## Test: basic

### basic.fg
```javascript
const x:int64 = 10000000000l
print(x, "\n")
```

### basic.expect
```
10000000000
```

## Test: from_int8_literal

### from_int8_literal.fg
```javascript
const x:int64 = 5
print(x, "\n")
```

### from_int8_literal.expect
```
5
```

## Test: with_suffix

### with_suffix.fg
```javascript
const x:int64 = 5l
print(x, "\n")
```

### with_suffix.expect
```
5
```

---

# Directory: ClassTests/18_mingled_module_bring

## Test: bring_module_class_field_while

### bring_module_class_field_while.fg
```javascript
bring "support_cnt_module.fg"

class Holder {
  var c: cnt::Counter
  fun init() -> nthg {
    self.c = new cnt::Counter(0)
  }
}

var h: Holder = new Holder()
var i: int = 0
while (i < 3) {
  println(h.c.bump())
  i = i + 1
}
```

### bring_module_class_field_while.expect
```
1
2
3
```

## Test: bring_module_while_print_counter

### bring_module_while_print_counter.fg
```javascript
bring "support_cnt_module.fg"

var c: cnt::Counter = new cnt::Counter(0)
var i: int = 0
while (i < 3) {
  println(c.bump())
  i = i + 1
}
```

### bring_module_while_print_counter.expect
```
1
2
3
```

## Test: global_fun_accepts_module_class

### global_fun_accepts_module_class.fg
```javascript
bring "support_cnt_module.fg"

fun use(c: cnt::Counter) -> nthg {
  println(c.bump())
}

var x: cnt::Counter = new cnt::Counter(5)
use(x)
```

### global_fun_accepts_module_class.expect
```
6
```

## Test: holder_uses_brought_class

### holder_uses_brought_class.fg
```javascript
bring "support_cnt_module.fg"

class Holder {
  var c: cnt::Counter
  fun init() -> nthg {
    self.c = new cnt::Counter(10)
  }
  fun read() -> int {
    return self.c.bump()
  }
}

var h: Holder = new Holder()
println(h.read())
```

### holder_uses_brought_class.expect
```
11
```

## Test: support_cnt_module

### support_cnt_module.fg
```javascript
module [cnt]

class Counter {
  var n: int
  fun init(start: int) -> nthg {
    self.n = start
  }
  fun bump() -> int {
    self.n = self.n + 1
    return self.n
  }
}
```

### support_cnt_module.expect
```

```

---

# Directory: ClassTests/02_variables

## Test: class_var_and_member

### class_var_and_member.fg
```javascript
class A {
  var x: int
}

var a: A = new A()
println(a.x)
```

### class_var_and_member.expect
```
0
```

## Test: class_var_equality

### class_var_equality.fg
```javascript
class A {
  var x: int
}

var a: A = new A()
var b: A = new A()
println(a == a)
println(a == b)
println(a != b)
```

### class_var_equality.expect
```
true
false
true
```

---

# Directory: ClassTests/13_stress

## Test: large_type_graph

### large_type_graph.fg
```javascript
type L0 = { x: int }
type L1 = { n: L0 }
type L2 = { n: L1 }
type L3 = { n: L2 }
type L4 = { n: L3 }

class Holder {
  var root: L4
  fun init(root: L4) -> nthg {
    self.root = root
  }
  fun leaf() -> int {
    return self.root.n.n.n.n.x
  }
}

var h: Holder = new Holder({n: {n: {n: {n: {x: 42}}}}})
println(h.leaf())
```

### large_type_graph.expect
```
42
```

---

# Directory: ClassTests/16_cross_feature

## Test: class_inout_vs_by_value_mutation

### class_inout_vs_by_value_mutation.fg
```javascript
class A {

  var x:int


  incrementX() -> nthg {
    x = x + 1
  }



}


fun mutable(inout a:A) -> nthg {
  a.x = a.x + 1
}

fun immutableDefault(a:A = new A()) -> nthg {
  a.x = a.x + 1

  println("Immutable Default a.x: ", a.x)
}

fun immutable(a:A) -> nthg {
  a.x = a.x + 1
}

fun immutableWithNew(a:A) -> nthg {
  a = new A()
}

fun mutableWithNew(inout a:A) -> nthg {
  a = new A()
}

var a: A = new A()
a.incrementX()
println("a.x: ", a.x)

mutable(a)
println("a.x: ", a.x)

immutableDefault()
println("a.x: ", a.x)

immutable(a)
println("a.x: ", a.x)

immutableWithNew(a)
println("a.x: ", a.x)

mutableWithNew(a)
println("a.x: ", a.x)
```

### class_inout_vs_by_value_mutation.expect
```
a.x: 1
a.x: 2
Immutable Default a.x: 1
a.x: 2
a.x: 3
a.x: 3
a.x: 0
```

## Test: with_default_param_function_taking_class

### with_default_param_function_taking_class.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
fun show(a: A, prefix: str = ">") -> nthg {
  println(prefix, a.x)
}
var a: A = new A(4)
show(a)
show(a, ">>")
```

### with_default_param_function_taking_class.expect
```
>4
>>4
```

## Test: with_for_loop_member

### with_for_loop_member.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
var a: A = new A(10)
for (var i: int = 0 to 2) {
  println(a.x + i)
}
```

### with_for_loop_member.expect
```
10
11
12
```

## Test: with_if_else_mutate_field_twice

### with_if_else_mutate_field_twice.fg
```javascript
class Box {
  var n: int
  fun init(v: int) -> nthg {
    self.n = v
  }
  fun add(d: int) -> nthg {
    self.n = self.n + d
  }
}

var b: Box = new Box(0)
if (b.n < 1) {
  b.add(5)
} else {
  b.add(100)
}
b.add(2)
println(b.n)
```

### with_if_else_mutate_field_twice.expect
```
7
```

## Test: with_multi_return_int_and_class

### with_multi_return_int_and_class.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
fun makePair() -> int, A {
  return 3, new A(9)
}
var n: int, a: A = makePair()
println(n)
println(a.x)
```

### with_multi_return_int_and_class.expect
```
3
9
```

## Test: with_nested_object_type_field

### with_nested_object_type_field.fg
```javascript
type Box = {
  inner: int
}

class A {
  var b: Box
  fun init(v: int) -> nthg {
    self.b = {inner: v}
  }
}
var a: A = new A(7)
println(a.b.inner)
```

### with_nested_object_type_field.expect
```
7
```

## Test: with_or_if_else_on_member

### with_or_if_else_on_member.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
var a: A = new A(0)
if (a.x > 0) {
  println(1)
} or if (a.x == 0) {
  println(2)
} else {
  println(3)
}
```

### with_or_if_else_on_member.expect
```
2
```

## Test: with_switch_case_member

### with_switch_case_member.fg
```javascript
class A {
  var tag: int
  fun init(tag: int) -> nthg {
    self.tag = tag
  }
}
var a: A = new A(2)
var k: int = 2
switch (k) {
  case 1: {
    println(1)
  }
  case 2: {
    println(a.tag)
  }
  default: {
    println(0)
  }
}
```

### with_switch_case_member.expect
```
2
```

## Test: with_switch_on_member_field

### with_switch_on_member_field.fg
```javascript
class Mode {
  var k: int
  fun init(v: int) -> nthg {
    self.k = v
  }
}

var m: Mode = new Mode(2)
switch (m.k) {
  case 1: {
    println(10)
  }
  case 2: {
    println(20)
  }
  default: {
    println(99)
  }
}
```

### with_switch_on_member_field.expect
```
20
```

## Test: with_while_if_break

### with_while_if_break.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
var a: A = new A(1)
var i: int = 0
while (i < 10) {
  if (a.x + i > 3) {
    break
  }
  i = i + 1
}
println(i)
```

### with_while_if_break.expect
```
3
```

---

# Directory: ClassTests/03_init

## Test: init_with_args

### init_with_args.fg
```javascript
class A {
  var x: int
  var b: str
  fun init(x: int, b: str) -> nthg {
    self.x = x
    self.b = b
  }
}

var a: A = new A(10, "Nice")
println(a.x)
println(a.b)
```

### init_with_args.expect
```
10
Nice
```

## Test: init_with_print

### init_with_print.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
    print("init called ")
    println(x)
  }
}

var a: A = new A(42)
println(a.x)
```

### init_with_print.expect
```
init called 42
42
```

---

# Directory: ClassTests/legacy_Class_fixtures/ClassPrintTest

## Test: CreatingObjectFromFunctionAssignmentLocalVaradicPrint

### CreatingObjectFromFunctionAssignmentLocalVaradicPrint.fg
```javascript
print(1,2,3,"ssdweqdfwe")

type T = {
  a:int 
}

type K = {
  j:T[2]
}

class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}
fun getAA(a:A) -> A {
  return getA(a)
}
fun createA() -> A {
  return new A({a:22})
}

    var a:A = new A({a:1})
print(a.obj)
a = createA()
print(a.obj)
a = new A({a:322})
print(a.obj)
a.printB(new B({j:[]}))
a.obj = {a:32}
print("After Pass")
a.printB(new B({j:[{a:2}]}))
```

### CreatingObjectFromFunctionAssignmentLocalVaradicPrint.expect
```
123ssdweqdfwe{ a: 1 }{ a: 22 }{ a: 322 }{ j: [ { a: 0 }, { a: 0 } ] }After Pass{ j: [ { a: 2 }, { a: 0 } ] }
```

## Test: InsideClassPrintAssignWithOutSelfFunctionCall

### InsideClassPrintAssignWithOutSelfFunctionCall.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    printComplex()
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
```

### InsideClassPrintAssignWithOutSelfFunctionCall.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0[ { a: [ 5, 5, 0 ], j: [ { x1: "yo", x2: 2 }, { x1: "WAY", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
```

---

# Directory: ClassTests/legacy_Class_fixtures/InheritanceTest/InheritanceTest

## Test: Basic

### Basic.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}

var a:A = new A({a:2})
a.printX()
```

### Basic.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicLocal

### BasicLocal.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}

{
  var a:A = new A({a:2})
a.printX()
}
```

### BasicLocal.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithOutSuper

### BasicWithObjectOfBWithOutSuper.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
  }
}

var b:B = new B({a:2})
b.printX()
```

### BasicWithObjectOfBWithOutSuper.expect
```
{ a: 0, b: "", c: null, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithOutSuperLocal

### BasicWithObjectOfBWithOutSuperLocal.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
  }
}

var b:B = new B({a:2})
{
  b.printX()
}
```

### BasicWithObjectOfBWithOutSuperLocal.expect
```
{ a: 0, b: "", c: null, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuper

### BasicWithObjectOfBWithSuper.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}

var b:B = new B({a:2})
b.printX()
```

### BasicWithObjectOfBWithSuper.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }

  printX()-> nthg {
      print("Not printing it ")
    }
}

var b:A = new B({a:2})
b.printX()
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj.expect
```
Not printing it
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:A = new B({a:2})
b.printX()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2.expect
```
02.2
2
hi
0Not printing it { a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2Local

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2Local.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

{
  var b:A = new B({a:2})
b.printX()
print(b.x)
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2Local.expect
```
02.2
2
hi
0Not printing it { a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:B = new B({a:2})
b.printX()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3.expect
```
02.2
2
hi
0Not printing it { a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3Local

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3Local.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

{
  var b:B = new B({a:2})
b.printX()
print(b.x)
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3Local.expect
```
02.2
2
hi
0Not printing it { a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:A = new A({a:2})
b.printX()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4Local

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4Local.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

{
  var b:A = new A({a:2})
b.printX()
print(b.x)
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4Local.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print(a)
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }{ u: "Nice" }{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5Local

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5Local.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print(a)
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

{
  var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5Local.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }{ u: "Nice" }{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:B = new B({a:2})
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6Local

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6Local.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

{
  var b:B = new B({a:2})
b.printX()
b.printNice()
print(b.x)
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6Local.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:A = new B({a:2})
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatch

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatch.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
b = new B({a:3})

b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatch.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }02.2
2
hi
0Not printing it Hi Printint Nice{ a: 3, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassFromFunction

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassFromFunction.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }


}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})
    return b 
}
var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
b = getB() 

b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassFromFunction.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }02.2
2
hi
0Not printing it Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOfB

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOfB.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}
var b:A = new B({a:2})

b.printX()
b.printNice()
print(b.x)
b = new A({a:5})
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOfB.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOpposite

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOpposite.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}
var b:A = new A({a:2})

b.printX()
b.printNice()
print(b.x)
b = new B({a:5})
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOpposite.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }02.2
2
hi
0Not printing it Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetAReturning

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetAReturning.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:A = getA() 
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetAReturning.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetB

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetB.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}
var b:A = new A({a:2})

b.printX()
b.printNice()
print(b.x)
b = getB()
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetB.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }02.2
2
hi
0Not printing it Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturning

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturning.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:B = getB() 
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturning.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginA

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginA.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:A = getB() 
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginA.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginAOpposite

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginAOpposite.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
  j = 2
  a = 2.2
  s = "hi"
}

printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:A = getB() 
b.printX()
b.printNice()
print(b.x)
b = getA()
b.printX()
b.printNice()
print(b.x)
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginAOpposite.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 5, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7Local

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7Local.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  printNice()-> nthg {
    print("Hi Printint Nice")
  } 

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

{
  var b:A = new B({a:2})
b.printX()
b.printNice()
print(b.x)
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7Local.expect
```
02.2
2
hi
0Not printing it Hi Printint Nice{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObjLocal

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObjLocal.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }

  printX()-> nthg {
      print("Not printing it ")
    }
}
{

var b:A = new B({a:2})
b.printX()
}
```

### BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObjLocal.expect
```
Not printing it
```

## Test: BasicWithObjectOfBWithSuperLocal

### BasicWithObjectOfBWithSuperLocal.fg
```javascript
type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}

{
  var b:B = new B({a:2})
b.printX()
}
```

### BasicWithObjectOfBWithSuperLocal.expect
```
{ a: 2, b: "", c: { d: 0 }, d: [ { d: 0 }, { d: 0 } ] }
```

## Test: DogAndAnimalExample

### DogAndAnimalExample.fg
```javascript
class Animal {
  var age:int 
  var species:str 
  init(age:int) -> nthg {
    self.age = age
  }
  getAge() -> int {
    return self.age
  }
  printSpecies() -> nthg { 
    print("Species: ",species)
  }
}
class Dog extends Animal {
   var breed:str 
  
  init(age:int) -> nthg {
    super(age)
  }

  getAge() ->int {
    return 7*self.age  
  }
  printBreed() -> nthg { 
    print("breed "+breed)
  }
}
fun printAge(a: Animal) ->nthg{
  print("I'm "+a.getAge()+" years old!\n")
}
fun main2() -> nthg {
  var animal:Animal = new Animal(2)
  var  dog:Dog = new Dog(2)

  printAge(animal) 
  printAge(dog) 
}

main2()
```

### DogAndAnimalExample.expect
```
I'm 2 years old!
I'm 14 years old!
```

---

# Directory: ClassTests/legacy_Class_fixtures/ClassesTests

## Test: ClassEqualityOperator

### ClassEqualityOperator.fg
```javascript
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)
var b:A = new A(2)
var aRef:A = a
if(a) {
  print("Class A","\n")
}

if(a && true) {
  print("Class A and true","\n")
}

if(a && false) {
  print("Class A and false","\n")
}

if(a || true) {
  print("Class A or true","\n")
}

if(a == a){
  print("Class A == A","\n")
}

if(a != a){
  print("Class A != A","\n")
}


if(a == b){
  print("Class A == B","\n")
}

if(a != b){
  print("Class A != B","\n")
}

if(a == aRef){
  print("Class A == ARef","\n")
}

if(a != aRef){
  print("Class A != ARef","\n")
}
```

### ClassEqualityOperator.expect
```
Class A
Class A and true
Class A or true
Class A == A
Class A != B
Class A == ARef
```

## Test: ClassInitTest

### ClassInitTest.fg
```javascript
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
  }
  test(a:int,k:deci = 3.3 ) -> nthg {
    print("a: "+a)
    print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)
  }
  
}

var a:A = new A(10,"Nice")


a.test(2,5.3)
```

### ClassInitTest.expect
```
init B 10Nicea: 2
b: Nice
x: 10
k: 5.3
```

## Test: ClassInitTest2

### ClassInitTest2.fg
```javascript
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,k:deci = 3.3 ) -> nthg {
    print("a: "+a)
    print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)
  }
  
}

var a:A = new A(10)


a.test(2,5.3)
```

### ClassInitTest2.expect
```
init B 10Helloa: 2
b: Hello
x: 10
k: 5.3
```

## Test: ClassInitTest3

### ClassInitTest3.fg
```javascript
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,k:deci = 3.3 ) -> nthg {
    print("a: "+a)
    print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)
  }
  
}

var a:A = new A(10)


a.test(2)
```

### ClassInitTest3.expect
```
init B 10Helloa: 2
b: Hello
x: 10
k: 3.3
```

## Test: ClassInitTest4WithMultiRetrun

### ClassInitTest4WithMultiRetrun.fg
```javascript
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,b:int = 4,k:str ="Hello" ) -> int,deci  {
    print("a: "+a)
   print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)

    return 23,35.5
  } 
}

var a:A = new A(10)
var b:int,c:deci = a.test(2)
print(b,c)
```

### ClassInitTest4WithMultiRetrun.expect
```
init B 10Helloa: 2
b: 4
x: 10
k: Hello2335.5
```

## Test: ClassInitTest4WithMultiRetrunAssignment

### ClassInitTest4WithMultiRetrunAssignment.fg
```javascript
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,b:int = 4,k:str ="Hello" ) -> int,deci  {
    print("a: "+a)
   print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)

    return 23,35.5
  } 
}

var a:A = new A(10)
var b:int,c:deci 


b,c =a.test(2)
print(b,c)
```

### ClassInitTest4WithMultiRetrunAssignment.expect
```
init B 10Helloa: 2
b: 4
x: 10
k: Hello2335.5
```

## Test: ClassInitTest4WithMultiRetrunAssignment2

### ClassInitTest4WithMultiRetrunAssignment2.fg
```javascript
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,b:int = 4,k:str ="Hello" ) -> int,deci  {
    print("a: "+a)
   print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)

    return 23,35.5
  } 
}

var a:A = new A(10)
var b:int,c:deci 


b,c =a.test(2,53)
print(b,c)
```

### ClassInitTest4WithMultiRetrunAssignment2.expect
```
init B 10Helloa: 2
b: 53
x: 10
k: Hello2335.5
```

## Test: ClassInitTest4WithMultiRetrunAssignmentClassItSelf

### ClassInitTest4WithMultiRetrunAssignmentClassItSelf.fg
```javascript
class B {
    init()->nthg {

      }
  }
class A {

  var x:int 
  init(x:int )-> nthg {
    self.x = x
  }
  
  getA() -> A {
    return new A(12)    
  }

  getB() -> B {
      return new B()
    }

}

var a:A = new A(11)
var b:A = a.getA()

var ba:B = a.getB()
print(a.x)
print(b.x)
```

### ClassInitTest4WithMultiRetrunAssignmentClassItSelf.expect
```
1112
```

## Test: ClassInitTest4WithMultiRetrunAssignmentClassItSelf2

### ClassInitTest4WithMultiRetrunAssignmentClassItSelf2.fg
```javascript
class B {
    init()->nthg {

      }
  }
class A {

  var x:int
  var y:deci 
  init(x:int )-> nthg {
    self.x = x
  }
  
  getAS() -> A {

    self.x = 12
    return self 
  }
  getA() -> A {
    x =32

    return self 
  }
  printX() -> nthg {
    print("Y: ",y)
  }

  getB() -> B {
      return new B()
    }

}

var a:A = new A(11)
print(a.x)

var b:A = a.getA()

print(b.x)
a.getAS()
print(a.x)
print(b.x)
```

### ClassInitTest4WithMultiRetrunAssignmentClassItSelf2.expect
```
11321212
```

## Test: ClassTestBasicInheritanceWithConstructor

### ClassTestBasicInheritanceWithConstructor.fg
```javascript
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
  
    print(j,"\nB Constructor is Called",self.z)
  }

  getZ() -> int {
    
    return z
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init() -> nthg {

    print("\nA Constructor is Called",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return 45.2
  }

}

var a:A = new A()
print(a.z)
```

### ClassTestBasicInheritanceWithConstructor.expect
```
A Constructor is Called00
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheck

### ClassTestBasicInheritanceWithConstructorFunctionCheck.fg
```javascript
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
  
    print(j,"\nB Constructor is Called",self.z)
  }

  printFromB()-> nthg {
    print("Print from B\n")
  }

  getZ() -> int {
    
    return z+2
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init(y:deci ) -> nthg {
    self.y = y
    print("\nA Constructor is Called",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return y
  }

}

var a:A = new A(4.4)
print("\n",a.getZ(),"\n",a.getS(),"\n",a.getX(),"\n")
a.printFromB()
print("\n")
a.printW()
```

### ClassTestBasicInheritanceWithConstructorFunctionCheck.expect
```
A Constructor is Called0
0
4.4
0
Print from B

world
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScope

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScope.fg
```javascript
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
  
    print(j,"\nB Constructor is Called",self.z)
  }

  printFromB()-> nthg {
    print("Print from B\n")
  }

  getZ() -> int {
    
    return z+2
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init(y:deci ) -> nthg {
    self.y = y
    print("\nA Constructor is Called",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return y
  }

}
{

var a:A = new A(4.4)
print("\n",a.getZ(),"\n",a.getS(),"\n",a.getX(),"\n")
a.printFromB()
print("\n")
a.printW()
}
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScope.expect
```
A Constructor is Called0
0
4.4
0
Print from B

world
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInit

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInit.fg
```javascript
type T = {
    a:int,
    b:deci
  }

class A {
  var x:int = 10
  var a:deci = 22.2
  const u:T = {a:43,b:54.2}
  init(x:int) -> nthg {
    self.x = x
  }

  getTT() -> T {
    var j:T = {a:2}
    return j
  }

  getT(s:str ) -> T {
    print(s)

    return getTT()
  }
}

var a:A = new A(2)

print(a.a)
print(a.x)
print(a.u)
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInit.expect
```
22.1999999999999992{ a: 43, b: 54.200000000000003 }
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun.fg
```javascript
type T = {
    a:int 
}
class A {
var i:deci32
var x:int 
var s:str 
var t:T
var g:T[2]
init(s: str) -> nthg{
  self.s = s 
}

getT() -> T {
    return t  
  }

getTA() -> T[2] {
    return g
  }
}

fun printT(t: T) -> nthg {
  print(t)
}
fun printTAr(ta:T[2]) -> nthg {
    print(ta)
  }

var a:A = new A("Hello")

printT(a.getT())
printTAr(a.getTA())
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun.expect
```
{ a: 0 }[ { a: 0 }, { a: 0 } ]
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun2

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun2.fg
```javascript
type T = {
    a:int,
    b:str
}
class A {
var i:deci32
var x:int 
var s:str 
var t:T
var g:T[2]
init(s: str) -> nthg{
  self.s = s 
}

getT(b:str) -> T {
   t.b = b
   return t  
  }

getTA(b:str ) -> T[2] {
  g[0].b =b 
    return g
  }
}

fun printT(t: T) -> nthg {
  print(t)
}
fun printTAr(ta:T[2]) -> nthg {
    print(ta)
  }

var a:A = new A("Hello")

printT(a.getT("IH"))
printTAr(a.getTA("Hi"))
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun2.expect
```
{ a: 0, b: "IH" }[ { a: 0, b: "Hi" }, { a: 0, b: "" } ]
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun3

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun3.fg
```javascript
type T  = {
      x:int,
      d:str 
    }
class Animal {
  var age:int 
  var species:str


  var t:T 
  init(age:int) -> nthg {
    self.age = age
    self.t = {d:"Hi",x:12}
  }
  getAge() -> int {
    return self.age
  }
  printSpecies() -> nthg { 
    print("Species: ",species)
  }
}
class Dog extends Animal {
   var breed:str 
  
  init(age:int) -> nthg {
    super(age)
  }

  getAge() ->int {
    return 7*self.age  
  }
  printBreed() -> nthg { 
    print("breed "+breed)
  }


  getT() -> T {
      return self.t
    }
}
fun printAge(a: Animal) ->nthg{
 print("I'm "+a.getAge()+" years old!\n")
}
fun main2() -> nthg {
  var animal:Animal = new Animal(2)
  var  dog:Dog = new Dog(2)
var x:int = dog.getAge()
print("x ",x)
print(dog.getT())
print(dog.getAge())
print(animal.getAge())
printAge(animal) 
 printAge(dog) 
}
main2()
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun3.expect
```
x 14{ d: "Hi", x: 12 }142I'm 2 years old!
I'm 14 years old!
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4.fg
```javascript
type T = {
    a:int,
    b:str
}
class A {
var s:str 
var k:T
var x:int
init(s: str) -> nthg{
  self.s = s 
}
  getHell() -> str {
      return "Hell"
    }
  setHell(s:str) -> nthg {
    
      print(s)
    }


      getC() -> int {
      return  3
    }
  setC(i:int) -> nthg{
    
      print(i)
    }
      getT() -> T {
        var x:T = {b:"hel"}
      return x 
    }
  setT(i:T) -> nthg{
    
      print(i)
    }

   getX(x:int ) -> int  {
      return x 
    } 

   getXX() -> int  {
      return 3 
    }

    setX(x:int ) -> nthg {
        self.x = x
      print("x: ",x)
      }

      getXXX(x:int) -> int {
          return x
        }
}



var a:A = new A("Hello")

a.setC(a.getC())
print(a.getC())
a.setHell(a.getHell())
print(a.getHell())
a.setT(a.getT())
print(a.getT())
print(a.getX(a.getXX()))
a.setX(a.getX(a.getXX()))
a.setX(a.getX(a.getXXX(5)))
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4.expect
```
33HellHell{ a: 0, b: "hel" }{ a: 0, b: "hel" }3x: 3x: 5
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal.fg
```javascript
type T = {
    a:int,
    b:str
}
class A {
var s:str 
var k:T
var x:int
init(s: str) -> nthg{
  self.s = s 
}
  getHell() -> str {
      return "Hell"
    }
  setHell(s:str) -> nthg {
    
  print(s)
    }


      getC() -> int {
      return  3
    }
  setC(i:int) -> nthg{
    
   print(i)
    }
      getT() -> T {
        var x:T = {b:"hel"}
      return x 
    }
  setT(i:T) -> nthg{
    
     print(i)
    }

   getX(x:int ) -> int  {
      return x 
    } 

   getXX() -> int  {
      return 3 
    }

    setX(x:int ) -> nthg {
        self.x = x
      print("x: ",x)
      }

      getXXX(x:int) -> int {
          return x
        }
}



var a:A = new A("Hello")

fun main2() -> int {

   print(a.s) 
    return 0 
  }

  main2()
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal.expect
```
Hello
```

## Test: ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal2

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal2.fg
```javascript
class A{
    var x:int 

    init() -> nthg {
         x = 3 
    }

    getX()->int {
        return x
      }

  }

var a:A = new A() 

fun getX() -> int {
    return a.x 
  }


{
if(true){
    var x:int 
}
var x:int 
print(getX())
}
```

### ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal2.expect
```
3
```

## Test: ClassTestBasicInheritanceWithSuper

### ClassTestBasicInheritanceWithSuper.fg
```javascript
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called\n",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1 
    print(j,"B Constructor is Called\n",self.z)
  }

  init(j:str) -> nthg {
      print(j)
    }

  getZ() -> int {
    
    return z
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init() -> nthg {
    super("CalledB")
    print("A Constructor is Called\n",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return 45.2
  }

}

var a:A = new A()
print(a.z)
```

### ClassTestBasicInheritanceWithSuper.expect
```
CalledBA Constructor is Called
00
```

## Test: ClassTestBasicInheritanceWithSuper2

### ClassTestBasicInheritanceWithSuper2.fg
```javascript
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called\n",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
    super(3)
    print(j,"B Constructor is Called\n",self.z)
  }

  getZ() -> int {
    
    return z
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init() -> nthg {

    print("A Constructor is Called\n",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return 45.2
  }

}

var a:A = new A()
print(a.z)
```

### ClassTestBasicInheritanceWithSuper2.expect
```
A Constructor is Called
00
```

## Test: CreatingObjectFromFunction

### CreatingObjectFromFunction.fg
```javascript
type T = {
  a:int 
}

type K = {
  j:T[2]
}

class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}

fun getAA(a:A) -> A {
  return getA(a)
}
fun createA() -> A {
  return new A({a:22})
}
var a:A =  createA() 
print(a.obj)
a.obj = {a:32}
print("After Pass")
a.printB( new B({j:[{a:2}]}))
```

### CreatingObjectFromFunction.expect
```
{ a: 22 }After Pass{ j: [ { a: 2 }, { a: 0 } ] }
```

## Test: CreatingObjectFromFunctionAssignment

### CreatingObjectFromFunctionAssignment.fg
```javascript
type T = {
  a:int 
}
type K = {
  j:T[2]
}

class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}
fun getAA(a:A) -> A {
  return getA(a)
}
fun createA() -> A {
  return new A({a:22})
}
var a:A = new A({a:1})
print(a.obj)
a = createA()
print(a.obj)
a = new A({a:322})
print(a.obj)
a.obj = {a:32}
print("After Pass")
a.printB(new B({j:[{a:2}]}))
```

### CreatingObjectFromFunctionAssignment.expect
```
{ a: 1 }{ a: 22 }{ a: 322 }After Pass{ j: [ { a: 2 }, { a: 0 } ] }
```

## Test: CreatingObjectFromFunctionAssignmentLocal

### CreatingObjectFromFunctionAssignmentLocal.fg
```javascript
type T = {
  a:int 
}

type K = {
  j:T[2]
}

class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}
fun getAA(a:A) -> A {
  return getA(a)
}
fun createA() -> A {
  return new A({a:22})
}

{
    var a:A = new A({a:1})
print(a.obj)
a = createA()
print(a.obj)
a = new A({a:322})
print(a.obj)
a.obj = {a:32}
print("After Pass")
a.printB(new B({j:[{a:2}]}))

  }
```

### CreatingObjectFromFunctionAssignmentLocal.expect
```
{ a: 1 }{ a: 22 }{ a: 322 }After Pass{ j: [ { a: 2 }, { a: 0 } ] }
```

## Test: DefaultInitilizer

### DefaultInitilizer.fg
```javascript
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X 
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2] 
  init() -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
  }
  printDefaults()-> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
    print(arr)
  }
}
var a: A  = new A() 
a.printDefaults()
```

### DefaultInitilizer.expect
```
Pinting u: { x1: "", x2: 0 }00false{ x1: "", x2: 0 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ][ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlock

### DefaultInitilizerScopeSelfAndFunctionBlock.fg
```javascript
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X 
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2] 
  init(a:int,b:str,yesD:deci) -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
    print(a)
    a = a 
    b = b 
    d = yesD
  }
  printDefaults()-> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
    print(arr)
  }
}
var a: A  = new A(2,"Hello",3.3) 
a.printDefaults()
```

### DefaultInitilizerScopeSelfAndFunctionBlock.expect
```
Pinting u: { x1: "", x2: 0 }203.3false{ x1: "", x2: 0 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ][ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignment

### DefaultInitilizerScopeSelfAndFunctionBlockAssignment.fg
```javascript
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X 
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2] 
  init(a:int,b:str,yesD:deci) -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
    print(a)
    self.a = a 
    self.b = b 
    d = yesD
  }
  printDefaults()-> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
    print(arr)
  }
}
var a: A  = new A(2,"Hello",3.3) 
a.printDefaults()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignment.expect
```
Pinting u: { x1: "", x2: 0 }22Hello3.3false{ x1: "", x2: 0 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ][ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgs

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgs.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print(a)
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgs.expect
```
22Hello3.3false{ x1: "HI", x2: 45 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
print("BeforeUpdate\n")
a.printDefaults()  
print("AfterUpdate\n")
a.updateA()
a.printDefaults()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction.expect
```
initCalledBeforeUpdate
2Hello3.3false{ x1: "HI", x2: 45 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]AfterUpdate
100Hello3.3false{ x1: "HI", x2: 45 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
      self.d = 2.2
      b = "Nice"
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
print("BeforeUpdate\n")
a.printDefaults()  
print("AfterUpdate\n")
a.updateA()
a.printDefaults()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2.expect
```
initCalledBeforeUpdate
2Hello3.3false{ x1: "HI", x2: 45 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]AfterUpdate
100Nice2.2false{ x1: "HI", x2: 45 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2Complex

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2Complex.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
     type Complex = {
    a: int[3],
    j: X[2]
  }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 

  var arr: Complex[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
      self.d = 2.2
      b = "Nice"
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }
  updateComplex(arr:Complex[2]) -> nthg {
    self.arr = arr 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2Complex.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
[ { a: [ 5, 5, 0 ], j: [ { x1: "yo", x2: 40 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBody

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBody.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
     type Complex = {
    a: int[3],
    j: X[2]
  }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 

  var arr: Complex[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
      self.d = 2.2
      b = "Nice"
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }
  updateComplex(arr:Complex[2]) -> nthg {
    arr = arr 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBody.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelf

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelf.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
     type Complex = {
    a: int[3],
    j: X[2]
  }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 

  var arr: Complex[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
      self.d = 2.2
      b = "Nice"
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }
  updateComplex(ar:Complex[2]) -> nthg {
    arr = ar
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelf.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
[ { a: [ 5, 5, 0 ], j: [ { x1: "yo", x2: 40 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdate

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdate.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
     type Complex = {
    a: int[3],
    j: X[2]
  }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 

  var arr: Complex[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
      self.d = 2.2
      b = "Nice"
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }
  updateComplex(ar:Complex[2]) -> nthg {
    arr = ar
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdate.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
[ { a: [ 5, 5, 0 ], j: [ { x1: "yo", x2: 40 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClass

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClass.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr )
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 
print("\nAfter Update\n")
print(a.arr )
print("\nprint nested\n")
print(a.arr[0].a[1] )
print("\n")
print(a.arr[0].j[0].x2 )
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 )
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClass.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
After Update
[ { a: [ 5, 5, 0 ], j: [ { x1: "yo", x2: 40 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
print nested
5
40
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClassAssignment

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClassAssignment.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr )
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 
print("\n")
print(a.arr[0].j[0].x2 )
a.arr[0].j[0].x2 = 2
print("\n")
print(a.arr[0].j[0].x2)
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
a.obj2 = {j:[{x2:2,x1:"Ge"}], a:[2 fill 1]}
print(a.obj2)
print("\n")
a.obj2 <- {}
print(a.obj2)
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 )
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClassAssignment.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdateAccessingOutSideClassAssignment

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdateAccessingOutSideClassAssignment.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr )
  }

}
{
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 

    print("\n")
print(a.arr[0].j[0].x2 )
a.arr[0].j[0].x2 = 2
print("\n")
print(a.arr[0].j[0].x2)
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
a.obj2 = {j:[{x2:2,x1:"Ge"}], a:[2 fill 1]}
print(a.obj2)
print("\n")
a.obj2 <- {}
print(a.obj2)
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 ) 
}
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdateAccessingOutSideClassAssignment.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdatePartialScopeAccessingOutSideClassAssignment

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdatePartialScopeAccessingOutSideClassAssignment.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr )
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 
{
    print("\n")
print(a.arr[0].j[0].x2 )
a.arr[0].j[0].x2 = 2
print("\n")
print(a.arr[0].j[0].x2)
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
a.obj2 = {j:[{x2:2,x1:"Ge"}], a:[2 fill 1]}
print(a.obj2)
print("\n")
a.obj2 <- {}
print(a.obj2)
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 ) 
}
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdatePartialScopeAccessingOutSideClassAssignment.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexOwnMember

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexOwnMember.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
     type Complex = {
    a: int[3],
    j: X[2]
  }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 

  var arr: Complex[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
      self.d = 2.2
      b = "Nice"
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }
  updateComplex(ar:Complex[2]) -> nthg {
    self.arr = arr 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexOwnMember.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
```

## Test: DefaultInitilizerScopeSelfAndFunctionBlockAssignmentOveride

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentOveride.fg
```javascript
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


type X = { 
    x1: str, 
    x2: int  
}      

  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {
    var obj: X 
    print("Pinting u: ")
    print(obj)
    print(a)
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
```

### DefaultInitilizerScopeSelfAndFunctionBlockAssignmentOveride.expect
```
Pinting u: { x1: "", x2: 0 }22Hello3.3false{ x1: "", x2: 0 }[ { x1: "", x2: 0 }, { x1: "", x2: 0 } ]
```

## Test: InsideClassPrint

### InsideClassPrint.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(self.arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(self.arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(self.arr[0].j[1].x1)
    print("\n")
    print(self.obj)
    print("\n")
    print(self.obj.x2)
    print("\n")
    print(self.obj.x1)
    print("\n")
    print(self.obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(self.obj2)
    print("\n")
    obj2 <- {

    } 
    print(self.obj2)
    print("\n")
    print(self.obj2.a)
    print("\n")
    print(self.obj2.j[0].x2)
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
```

### InsideClassPrint.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: InsideClassPrintAssignWithOutSelf

### InsideClassPrintAssignWithOutSelf.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
```

### InsideClassPrintAssignWithOutSelf.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: InsideClassPrintAssignWithSelf

### InsideClassPrintAssignWithSelf.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(self.arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(self.arr[0].j[0].x2)
    print("\n")
    self.arr[0].j[1].x1= "WAY"
    print(self.arr[0].j[1].x1)
    print("\n")
    print(self.obj)
    print("\n")
    print(self.obj.x2)
    print("\n")
    print(self.obj.x1)
    print("\n")
    print(self.obj2)
    print("\n")
    self.obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(self.obj2)
    print("\n")
    obj2 <- {

    } 
    print(self.obj2)
    print("\n")
    print(self.obj2.a)
    print("\n")
    print(self.obj2.j[0].x2)
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
```

### InsideClassPrintAssignWithSelf.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0
```

## Test: LogicalNotForClass

### LogicalNotForClass.fg
```javascript
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)

if(!a){
  print("A")
}or if(a){
    print("or A")
  }
```

### LogicalNotForClass.expect
```
or A
```

## Test: PrintNiceInsideClassFunctionOutsideClass

### PrintNiceInsideClassFunctionOutsideClass.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
fun printNice() -> nthg {
    print("Not Nice")
  }

  fun outsidefun()-> nthg {
      print("Outsidefunction")
    }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    printNice()
    self.printNice()
    outsidefun()
  }

  printNice() -> nthg {
      print("Nice")
    }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
a.printNice()
printNice()
outsidefun()
```

### PrintNiceInsideClassFunctionOutsideClass.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Not NiceNiceOutsidefunctionNiceNot NiceOutsidefunction
```

## Test: PrintNiceInsideClassFunctionOutsideClassInScope

### PrintNiceInsideClassFunctionOutsideClassInScope.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
fun printNice() -> nthg {
    print("Not Nice")
  }

  fun outsidefun()-> nthg {
      print("Outsidefunction")
    }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    printNice()
    self.printNice()
    outsidefun()
  }

  printNice() -> nthg {
      print("Nice")
    }

}
{
  var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
a.printNice()
printNice()
outsidefun()
}
```

### PrintNiceInsideClassFunctionOutsideClassInScope.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Not NiceNiceOutsidefunctionNiceNot NiceOutsidefunction
```

## Test: PrintNiceInsideClassFunctionOutsideClassPassingAnotherObjectOfSameType

### PrintNiceInsideClassFunctionOutsideClassPassingAnotherObjectOfSameType.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
fun printNice() -> nthg {
    print("Not Nice")
  }

  fun outsidefun()-> nthg {
      print("Outsidefunction")
    }
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    printNice()
    self.printNice()
    outsidefun()
  }

  printNice() -> nthg {
      print("Nice")
  }

  printBsa(b: A) -> nthg {
   print("\n\n\n")
   b.printAll()
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
a.printNice()
printNice()
outsidefun()
var b:A = new A(5,"e",5.5,{
    x1:"s",
    x2:22
})
a.printBsa(b)
```

### PrintNiceInsideClassFunctionOutsideClassPassingAnotherObjectOfSameType.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Not NiceNiceOutsidefunctionNiceNot NiceOutsidefunctioninitCalled


0
2
WAY
{ x1: "s", x2: 22 }
22
s
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Not NiceNiceOutsidefunction
```

## Test: PrintNiceInsideClassWithSelf

### PrintNiceInsideClassWithSelf.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}

class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    self.printNice()
  }

  printNice() -> nthg {
      print("Nice")
    }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
```

### PrintNiceInsideClassWithSelf.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Nice
```

## Test: PrintNiceInsideClassWithoutSelf

### PrintNiceInsideClassWithoutSelf.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}

class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    printNice()
  }

  printNice() -> nthg {
      print("Nice")
    }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
```

### PrintNiceInsideClassWithoutSelf.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Nice
```

## Test: PrintNiceOutsideClass

### PrintNiceOutsideClass.fg
```javascript
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}

class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
  }

  printNice() -> nthg {
      print("Nice")
    }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll()
a.printNice()
```

### PrintNiceOutsideClass.expect
```
initCalled2Hello3.3false{ x1: "HI", x2: 45 }[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
Before Update
[ { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }, { a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] } ]
40
2
WAY
{ x1: "HI", x2: 45 }
45
HI
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
{ a: [ 1, 1, 0 ], j: [ { x1: "Ge", x2: 2 }, { x1: "", x2: 0 } ] }
{ a: [ 0, 0, 0 ], j: [ { x1: "", x2: 0 }, { x1: "", x2: 0 } ] }
[ 0, 0, 0 ]
0Nice
```

## Test: ReturnClassObjectFromFunction

### ReturnClassObjectFromFunction.fg
```javascript
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA() -> A {
var d:A= new A({a:100})

 d.obj.a = 21
  return d
}
var a:A =  getA()  
a.obj = {a:32}
print(a.obj)
a = getA()
print("After Pass")
print(a.obj)
```

### ReturnClassObjectFromFunction.expect
```
{ a: 32 }After Pass{ a: 21 }
```

## Test: ReturnClassObjectFromFunction2

### ReturnClassObjectFromFunction2.fg
```javascript
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA() -> A {
var d:A= new A({a:100})

 d.obj.a = 21
  return d
}
var a:A =  getA()  
a.obj = {a:32}
print(a.obj)
a = getA()
print("After Pass")
print(a.obj)
```

### ReturnClassObjectFromFunction2.expect
```
{ a: 32 }After Pass{ a: 21 }
```

## Test: ReturnClassObjectFromFunctionReturining

### ReturnClassObjectFromFunctionReturining.fg
```javascript
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA() -> A {
var d:A= new A({a:100})

 d.obj.a = 21
  return d
}

fun getAA() -> A {
  return getA()
}

var a:A =  getAA()  
a.obj = {a:32}
print(a.obj)
a = getA()
print("After Pass")
print(a.obj)
```

### ReturnClassObjectFromFunctionReturining.expect
```
{ a: 32 }After Pass{ a: 21 }
```

## Test: ReturnClassObjectFromFunctionReturiningComplexTwo

### ReturnClassObjectFromFunctionReturiningComplexTwo.fg
```javascript
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA(d:A) -> A {

 d.obj.a = 21
  return d
}

fun getAA(a:A) -> A {
  return getA(a)
}

var a:A =  getAA(new A({a:22}))  
print(a.obj)
a.obj = {a:32}
print("After Pass")
print(a.obj)
```

### ReturnClassObjectFromFunctionReturiningComplexTwo.expect
```
{ a: 21 }After Pass{ a: 32 }
```

## Test: ReturnClassObjectFromFunctionReturiningComplexTwo3

### ReturnClassObjectFromFunctionReturiningComplexTwo3.fg
```javascript
type T = {
  a:int 
}
type K = {
  j:T[2]
}
class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}

fun getAA(a:A) -> A {
  return getA(a)
}

var a:A =  getAA(new A({a:22}))  
print(a.obj)
a.obj = {a:32}
print("After Pass")
var d:B = new B({j:[{a:2}]})
print(d.getU())
```

### ReturnClassObjectFromFunctionReturiningComplexTwo3.expect
```
{ a: 21 }After Pass{ j: [ { a: 2 }, { a: 0 } ] }
```

## Test: ReturnClassObjectFromFunctionReturiningComplexTwo3Direct

### ReturnClassObjectFromFunctionReturiningComplexTwo3Direct.fg
```javascript
type T = {
  a:int 
}

type K = {
  j:T[2]
}

class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}

fun getAA(a:A) -> A {
  return getA(a)
}

var a:A =  getAA(new A({a:22}))  
print(a.obj)
a.obj = {a:32}
print("After Pass")
a.printB( new B({j:[{a:2}]}))
```

### ReturnClassObjectFromFunctionReturiningComplexTwo3Direct.expect
```
{ a: 21 }After Pass{ j: [ { a: 2 }, { a: 0 } ] }
```

---

# Directory: ClassTests/04_member_methods

## Test: member_method_implicit_return_like_global_fun

### member_method_implicit_return_like_global_fun.fg
```javascript
class A {
  fun addOne(x: int) {
    return x + 1
  }
}

fun addOneGlobal(x: int) {
  return x + 1
}

var a: A = new A()
var fromMember = a.addOne(10)
var fromGlobal = addOneGlobal(10)
println(fromMember)
println(fromGlobal)
```

### member_method_implicit_return_like_global_fun.expect
```
11
11
```

## Test: method_getter_setter

### method_getter_setter.fg
```javascript
class A {
  var x: int
  fun setX(val: int) -> nthg {
    self.x = val
  }
  fun getX() -> int {
    return self.x
  }
}

var a: A = new A()
a.setX(42)
println(a.getX())
println(a.x)
```

### method_getter_setter.expect
```
42
42
```

## Test: method_mutate_field

### method_mutate_field.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun doubleX() -> nthg {
    self.x = self.x * 2
  }
}

var a: A = new A(5)
println(a.x)
a.doubleX()
println(a.x)
```

### method_mutate_field.expect
```
5
10
```

## Test: method_void_return

### method_void_return.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun printX() -> nthg {
    println(self.x)
  }
}

var a: A = new A(99)
a.printX()
```

### method_void_return.expect
```
99
```

## Test: method_with_args

### method_with_args.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun add(y: int) -> int {
    return self.x + y
  }
}

var a: A = new A(10)
println(a.add(5))
```

### method_with_args.expect
```
15
```

## Test: method_without_fun_keyword

### method_without_fun_keyword.fg
```javascript
class A {
  var x: int
  fun init(v: int) -> nthg {
    self.x = v
  }
  doubleX() -> int {
    return x * 2
  }
}

var a: A = new A(20)
print(a.doubleX())
println("")
```

### method_without_fun_keyword.expect
```
40
```

---

# Directory: ClassTests/13_cross_suite

## Test: dynamic_class_null_branch

### dynamic_class_null_branch.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

var a: A = new A(2)
if (a == null) {
  println("null")
} else {
  println(a.x)
}
```

### dynamic_class_null_branch.expect
```
2
```

---

# Directory: ClassTests/12_integration

## Test: class_with_custom_type_field

### class_with_custom_type_field.fg
```javascript
type T = {
  a: int
}

class A {
  var obj: T
  fun init(obj: T) -> nthg {
    self.obj = obj
  }
}

fun getA() -> A {
  return new A({a: 22})
}

var a: A = getA()
println(a.obj)
```

### class_with_custom_type_field.expect
```
{ a: 22 }
```

## Test: index_member_array

### index_member_array.fg
```javascript
class A {
  var x: int[2]
  fun init(x: int[2]) -> nthg {
    self.x[1] = x[1]
  }
}

var a: A = new A([2, 3])
println(a.x)
```

### index_member_array.expect
```
[ 0, 3 ]
```

---

# Directory: ClassTests/01_basic

## Test: class_equality

### class_equality.fg
```javascript
class A {
  var x: int
}

println((new A()) != (new A()))
println((new A()) == (new A()))
```

### class_equality.expect
```
true
false
```

## Test: class_new_and_field_read

### class_new_and_field_read.fg
```javascript
class A {
  var x: int
}

println((new A()).x)
```

### class_new_and_field_read.expect
```
0
```

## Test: logical_not_class

### logical_not_class.fg
```javascript
class A {
  var x: int
}

if (new A()) {
  println("ok")
}
```

### logical_not_class.expect
```
ok
```

## Test: new_direct_member_access

### new_direct_member_access.fg
```javascript
class A {
  var x: int
}

println((new A()).x)
```

### new_direct_member_access.expect
```
0
```

---

# Directory: ClassTests/15_errors

## Test: call_undefined_member_method

### call_undefined_member_method.fg
```javascript
/; EXPECT_ERROR: FunctionNotFound
class A {
  fun init() -> nthg {}
}

var a: A = new A()
println(a.missing())
```

## Test: compile_bare_init_at_file_scope

### compile_bare_init_at_file_scope.fg
```javascript
/; EXPECT_ERROR: InvalidInitFunctionCall
init()
```

## Test: compile_bare_init_call_in_member

### compile_bare_init_call_in_member.fg
```javascript
/; EXPECT_ERROR: InvalidInitFunctionCall
class A {
  fun init() -> nthg {
  }
  fun f() -> nthg {
    init()
  }
}
```

## Test: compile_class_name_declared_twice

### compile_class_name_declared_twice.fg
```javascript
/; EXPECT_ERROR: ClassAlreadyDeclared
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
class A {
  var y: int
}
```

## Test: compile_duplicate_init_same_signature_in_one_class

### compile_duplicate_init_same_signature_in_one_class.fg
```javascript
/; EXPECT_ERROR: FunctionAlreadyDeclared
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun init(x: int) -> nthg {
    self.x = x + 1
  }
}
```

## Test: compile_duplicate_member_method

### compile_duplicate_member_method.fg
```javascript
/; EXPECT_ERROR: FunctionAlreadyDeclared
class A {
  fun init() -> nthg {}
  fun f() -> int {
    return 1
  }
  fun f() -> int {
    return 2
  }
}
```

## Test: compile_dynamic_member_access_on_class_return

### compile_dynamic_member_access_on_class_return.fg
```javascript
/; EXPECT_ERROR: MemberAccessOnNonObjectVariable
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
fun getA() -> A {
  return new A(8)
}
var d = getA()
println(d.x)
```

## Test: compile_explicit_init_on_instance

### compile_explicit_init_on_instance.fg
```javascript
/; EXPECT_ERROR: InvalidInitFunctionCall
class A {
  fun init() -> nthg {
  }
  fun reset() -> nthg {
    self.init()
  }
}
```

## Test: compile_explicit_init_via_local

### compile_explicit_init_via_local.fg
```javascript
/; EXPECT_ERROR: InvalidInitFunctionCall
class A {
  fun init() -> nthg {
  }
}
var a: A = new A()
a.init()
```

## Test: compile_extends_custom_type_not_class

### compile_extends_custom_type_not_class.fg
```javascript
/; EXPECT_ERROR: ParentClassIsNotAClass
type Box = {
  x: int
}
class A extends Box {
  fun init() -> nthg {
  }
}
```

## Test: compile_extends_unknown_parent

### compile_extends_unknown_parent.fg
```javascript
/; EXPECT_ERROR: ParentClassNotFound
class A extends UnknownBase {
  fun init() -> nthg {
  }
}
```

## Test: compile_index_primitive_field_like_array

### compile_index_primitive_field_like_array.fg
```javascript
/; EXPECT_ERROR: IndexingNonArrayTypeVariable
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
var a: A = new A(1)
println(a.x[0])
```

## Test: compile_new_with_args_when_no_init

### compile_new_with_args_when_no_init.fg
```javascript
/; EXPECT_ERROR: NewExpressionConstructorArgumentCountMismatch
class A {
  var x: int

  incrementX() -> nthg {
    x = x + 1
  }
}

var a: A = new A(2)
```

## Test: compile_new_without_args_when_init_requires_one

### compile_new_without_args_when_init_requires_one.fg
```javascript
/; EXPECT_ERROR: NewExpressionConstructorArgumentCountMismatch
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
println(new A())
```

## Test: compile_new_wrong_type_for_init

### compile_new_wrong_type_for_init.fg
```javascript
/; EXPECT_ERROR: NewExpressionConstructorArgumentTypeMismatch
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
var a: A = new A("bad")
```

## Test: compile_pass_int_where_class_param_expected

### compile_pass_int_where_class_param_expected.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
fun take(a: A) -> nthg {
  println(a.x)
}
take(42)
```

## Test: compile_super_outside_constructor

### compile_super_outside_constructor.fg
```javascript
/; EXPECT_ERROR: SuperCallOutsideConstructor
class Base {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}
class D extends Base {
  fun bump() -> nthg {
    super(1)
  }
}
```

## Test: member_access_on_primitive_int

### member_access_on_primitive_int.fg
```javascript
/; EXPECT_ERROR: MemberAccessOnNonObjectVariable
var x: int = 1
println(x.nope)
```

## Test: member_nthg_in_dynamic_var

### member_nthg_in_dynamic_var.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
class A {
  fun init() -> nthg {}
  fun sideEffect() -> nthg {
    print("ok")
  }
}

var a: A = new A()
var x = a.sideEffect()
```

## Test: runtime_member_array_index_out_of_bounds

### runtime_member_array_index_out_of_bounds.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
class A {
  var arr: int[2]
  fun init() -> nthg {
    self.arr[0] = 1
    self.arr[1] = 2
  }
}
var a: A = new A()
println(a.arr[5])
```

---

# Directory: ClassTests/05_member_access

## Test: implicit_self

### implicit_self.fg
```javascript
class A {
  var x: int
  fun init(val: int) -> nthg {
    self.x = val
  }
  fun getX() -> int {
    return x
  }
}

var a: A = new A(77)
println(a.getX())
```

### implicit_self.expect
```
77
```

## Test: self_dot_member

### self_dot_member.fg
```javascript
class A {
  var x: int
  var y: int
  fun init(x: int, y: int) -> nthg {
    self.x = x
    self.y = y
  }
  fun sum() -> int {
    return self.x + self.y
  }
}

var a: A = new A(3, 7)
println(a.sum())
```

### self_dot_member.expect
```
10
```

---

# Directory: ClassTests/07_init_variants

## Test: default_fields_no_init

### default_fields_no_init.fg
```javascript
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
}

var obj: A = new A()
println(obj.a)
println(obj.b)
println(obj.d)
println(obj.e)
```

### default_fields_no_init.expect
```
0

0
false
```

## Test: init_default_second_param

### init_default_second_param.fg
```javascript
class A {
  var a: int
  var b: int
  init(x: int, y: int = 100) -> nthg {
    self.a = x
    self.b = y
  }
}

var z: A = new A(5)
println(z.a)
println(z.b)
```

### init_default_second_param.expect
```
5
100
```

## Test: init_multiple_types

### init_multiple_types.fg
```javascript
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  fun init(a: int, b: str, d: deci, e: bool) -> nthg {
    self.a = a
    self.b = b
    self.d = d
    self.e = e
  }
}

var obj: A = new A(42, "world", 3.14, true)
println(obj.a)
println(obj.b)
println(obj.d)
println(obj.e)
```

### init_multiple_types.expect
```
42
world
3.14
true
```

## Test: init_no_args

### init_no_args.fg
```javascript
class A {
  var x: int
  var y: str
  fun init() -> nthg {
    self.x = 99
    self.y = "initialized"
  }
}

var a: A = new A()
println(a.x)
println(a.y)
```

### init_no_args.expect
```
99
initialized
```

## Test: init_overloads_zero_or_one_arg

### init_overloads_zero_or_one_arg.fg
```javascript
class A {
  var x: int
  var y: int
  fun init() -> nthg {
    self.x = 0
    self.y = 0
  }
  fun init(a: int) -> nthg {
    self.x = a
    self.y = a
  }
}

var z: A = new A(99)
println(z.x)
var w: A = new A()
println(w.x)
```

### init_overloads_zero_or_one_arg.expect
```
99
0
```

## Test: init_two_fields

### init_two_fields.fg
```javascript
class A {
  var x: int
  var b: str
  fun init(x: int, b: str) -> nthg {
    self.x = x
    self.b = b
  }
}

var a: A = new A(10, "Hello")
println(a.x)
println(a.b)
```

### init_two_fields.expect
```
10
Hello
```

---

# Directory: ClassTests/09_class_with_functions

## Test: class_as_method_param

### class_as_method_param.fg
```javascript
class B {
  var val: int
  fun init(val: int) -> nthg {
    self.val = val
  }
  fun getVal() -> int {
    return self.val
  }
}

class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun addB(b: B) -> int {
    return self.x + b.getVal()
  }
}

var a: A = new A(10)
var b: B = new B(32)
println(a.addB(b))
```

### class_as_method_param.expect
```
42
```

## Test: function_chain_class

### function_chain_class.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun createA(val: int) -> A {
  return new A(val)
}

fun doubleA(a: A) -> A {
  return new A(a.x * 2)
}

var a: A = createA(10)
var b: A = doubleA(a)
println(a.x)
println(b.x)
```

### function_chain_class.expect
```
10
20
```

## Test: multiple_classes

### multiple_classes.fg
```javascript
class Point {
  var x: int
  var y: int
  fun init(x: int, y: int) -> nthg {
    self.x = x
    self.y = y
  }
}

class Line {
  var x1: int
  var y1: int
  var x2: int
  var y2: int
  fun init(x1: int, y1: int, x2: int, y2: int) -> nthg {
    self.x1 = x1
    self.y1 = y1
    self.x2 = x2
    self.y2 = y2
  }
  fun dx() -> int {
    return self.x2 - self.x1
  }
  fun dy() -> int {
    return self.y2 - self.y1
  }
}

var p: Point = new Point(3, 4)
println(p.x)
println(p.y)

var l: Line = new Line(1, 2, 5, 8)
println(l.dx())
println(l.dy())
```

### multiple_classes.expect
```
3
4
4
6
```

## Test: reassign_from_function

### reassign_from_function.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun getA() -> A {
  return new A(21)
}

var a: A = getA()
println(a.x)
a = getA()
println(a.x)
```

### reassign_from_function.expect
```
21
21
```

## Test: return_class_modify

### return_class_modify.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun getA() -> A {
  var d: A = new A(100)
  d.x = 21
  return d
}

var a: A = getA()
println(a.x)
```

### return_class_modify.expect
```
21
```

---

# Directory: ClassTests/11_inheritance_basic

## Test: inherit_field_access

### inherit_field_access.fg
```javascript
class Animal {
  var name: str
  var age: int
  fun init(name: str, age: int) -> nthg {
    self.name = name
    self.age = age
  }
}

class Dog extends Animal {
  var breed: str
  fun init(name: str, age: int, breed: str) -> nthg {
    self.name = name
    self.age = age
    self.breed = breed
  }
}

var d: Dog = new Dog("Rex", 5, "Labrador")
println(d.name)
println(d.age)
println(d.breed)
```

### inherit_field_access.expect
```
Rex
5
Labrador
```

## Test: simple_extends

### simple_extends.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun getX() -> int {
    return self.x
  }
}

class B extends A {
  var y: int
  fun init(x: int, y: int) -> nthg {
    self.x = x
    self.y = y
  }
  fun getY() -> int {
    return self.y
  }
}

var b: B = new B(10, 20)
println(b.getX())
println(b.getY())
```

### simple_extends.expect
```
10
20
```

## Test: super_in_derived_init

### super_in_derived_init.fg
```javascript
class Base {
  var tag: int
  fun init(x: int) -> nthg {
    self.tag = x
  }
}

class Child extends Base {
  var extra: int
  fun init(y: int) -> nthg {
    super(y)
    self.extra = y + 10
  }
}

var c: Child = new Child(7)
println(c.tag)
println(c.extra)
```

### super_in_derived_init.expect
```
7
17
```

## Test: virtual_dispatch_base_ref

### virtual_dispatch_base_ref.fg
```javascript
class Base {
  fun tag() -> nthg {
    println("Base")
  }
}

class Derived extends Base {
  fun tag() -> nthg {
    println("Derived")
  }
}

var b: Base = new Derived()
b.tag()
```

### virtual_dispatch_base_ref.expect
```
Derived
```

## Test: virtual_dispatch_function_param

### virtual_dispatch_function_param.fg
```javascript
class Base {
  fun tag() -> nthg {
    println("Base")
  }
}

class Derived extends Base {
  fun tag() -> nthg {
    println("Derived")
  }
}

fun callTag(b: Base) -> nthg {
  b.tag()
}

callTag(new Derived())
```

### virtual_dispatch_function_param.expect
```
Derived
```

---

# Directory: ClassTests/08_methods_advanced

## Test: method_calls_method

### method_calls_method.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun getDouble() -> int {
    return self.x * 2
  }
  fun printDouble() -> nthg {
    var d: int = self.getDouble()
    println(d)
  }
}

var a: A = new A(21)
a.printDouble()
```

### method_calls_method.expect
```
42
```

## Test: method_update_fields

### method_update_fields.fg
```javascript
class A {
  var a: int
  var b: str
  var d: deci
  fun init(a: int, b: str, d: deci) -> nthg {
    self.a = a
    self.b = b
    self.d = d
  }
  fun updateA() -> nthg {
    self.a = 100
    self.d = 2.2
    self.b = "Nice"
  }
}

var obj: A = new A(2, "Hello", 3.3)
println(obj.a)
println(obj.b)
println(obj.d)
obj.updateA()
println(obj.a)
println(obj.b)
println(obj.d)
```

### method_update_fields.expect
```
2
Hello
3.3
100
Nice
2.2
```

## Test: method_with_multiple_args

### method_with_multiple_args.fg
```javascript
class Calculator {
  var result: int
  fun init() -> nthg {
    self.result = 0
  }
  fun add(a: int, b: int) -> int {
    self.result = a + b
    return self.result
  }
  fun getResult() -> int {
    return self.result
  }
}

var calc: Calculator = new Calculator()
var sum: int = calc.add(10, 32)
println(sum)
println(calc.getResult())
```

### method_with_multiple_args.expect
```
42
42
```

## Test: method_with_return

### method_with_return.fg
```javascript
class A {
  var x: int
  var b: str
  fun init(x: int, b: str) -> nthg {
    self.x = x
    self.b = b
  }
  fun getX() -> int {
    return self.x
  }
  fun getB() -> str {
    return self.b
  }
}

var a: A = new A(10, "Hello")
println(a.getX())
println(a.getB())
```

### method_with_return.expect
```
10
Hello
```

---

# Directory: ClassTests/10_class_operators

## Test: class_equality_ref

### class_equality_ref.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

var a: A = new A(2)
var b: A = new A(2)
var aRef: A = a

if (a == a) {
  println("a == a")
}
if (a != b) {
  println("a != b")
}
if (a == aRef) {
  println("a == aRef")
}
```

### class_equality_ref.expect
```
a == a
a != b
a == aRef
```

## Test: class_logical_not

### class_logical_not.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

var a: A = new A(2)

if (!a) {
  println("null")
} or if (a) {
  println("not null")
}
```

### class_logical_not.expect
```
not null
```

## Test: class_null

### class_null.fg
```javascript
class C {
    var b:A 
    init() -> nthg {
        println("c init called")
        self.b = null
    }
}
class A {

    var b:A 
    var c:C
    var d:C
  init() -> nthg {
    println("a init called")
    self.b = null
    self.d = new C()    
  }
}

var a: A = new A()
var c: C = new C()

if(c.b != null) {
    println("b is not null")
} else {
    println("b is null")
}

if(a.b != null) {
    println("b is not null")
} else {
    println("b is null")
}

if(a.c != null) {
    println("c is not null")
} else {
    println("c is null")
}

if(a.d != null) {
    println("d is not null")
} else {
    println("d is null")
}
```

### class_null.expect
```
a init called
c init called
c init called
b is null
b is null
c is null
d is not null
```

## Test: class_null_indirect_declaration

### class_null_indirect_declaration.fg
```javascript
class A {
    var a:A 
    
}
var o_a:A = new A()

if(o_a.a != null) {
    println("o_a is not null")
} else {
    println("o_a is null")
}

var o_b:A = o_a.a

if(o_b != null) {
    println("o_b is not null")
} else {
    println("o_b is null")
}
```

### class_null_indirect_declaration.expect
```
o_a is null
o_b is null
```

## Test: class_truthiness

### class_truthiness.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

var a: A = new A(2)

if (a) {
  println("truthy")
}
```

### class_truthiness.expect
```
truthy
```

---

# Directory: ClassTests/14_inference_and_external_mutate

## Test: inferred_field_int_then_string_assign

### inferred_field_int_then_string_assign.fg
```javascript
class A {
  var x
  init(s) {
    self.x = s
  }
}

fun printA(a: A) {
      println(a.x)
      a.x = "Hello2"
  println(a.x)
}

printA(new A(10))
```

### inferred_field_int_then_string_assign.expect
```
10
"Hello2"
```

## Test: inferred_field_str_typed_init

### inferred_field_str_typed_init.fg
```javascript
class A {
  var x
  init(s: str) {
    self.x = s
  }
}

fun printA(a: A) {
      println(a.x)
      a.x = "Hello2"
  println(a.x)
}

printA(new A("Hello"))
```

### inferred_field_str_typed_init.expect
```
"Hello"
"Hello2"
```

---

# Directory: ClassTests/17_edge_cases

## Test: implicit_return_chained_calls

### implicit_return_chained_calls.fg
```javascript
class A {
  fun init() -> nthg {}
  fun inc(x: int) {
    return x + 1
  }
  fun addTwo(x: int) {
    return x + 2
  }
}

var a: A = new A()
println(a.inc(a.addTwo(0)))
```

### implicit_return_chained_calls.expect
```
3
```

## Test: member_and_global_implicit_return_same_expr

### member_and_global_implicit_return_same_expr.fg
```javascript
class A {
  fun init() -> nthg {}
  fun dbl(x: int) {
    return x * 2
  }
}

fun dblG(x: int) {
  return x * 2
}

var a: A = new A()
println(a.dbl(3) + dblG(4))
```

### member_and_global_implicit_return_same_expr.expect
```
14
```

## Test: two_classes_cross_reference_methods

### two_classes_cross_reference_methods.fg
```javascript
class A {
  fun init() -> nthg {}
  fun tag() -> int {
    return 1
  }
}

class B {
  fun init() -> nthg {}
  fun fromA(a: A) -> int {
    return a.tag() + 10
  }
}

var a: A = new A()
var b: B = new B()
println(b.fromA(a))
```

### two_classes_cross_reference_methods.expect
```
11
```

---

# Directory: ClassTests/06_object_from_function

## Test: pass_class_to_function

### pass_class_to_function.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun printA(a: A) -> nthg {
  println(a.x)
}

var a: A = new A(55)
printA(a)
```

### pass_class_to_function.expect
```
55
```

## Test: return_class_from_function

### return_class_from_function.fg
```javascript
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun createA() -> A {
  return new A(42)
}

var a: A = createA()
println(a.x)
```

### return_class_from_function.expect
```
42
```

---

# Directory: ObjectTests/array_of_objects

## Test: array_of_objects_deci

### array_of_objects_deci.fg
```javascript
type T = {
  a:int 
  b:deci 
}

var t:T[2] = [{a:1, b:2.3}, {a:2, b:3.4}]
println(t)
```

### array_of_objects_deci.expect
```
[ { a: 1, b: 2.3 }, { a: 2, b: 3.4 } ]
```

## Test: array_of_objects_element_modify

### array_of_objects_element_modify.fg
```javascript
type T = {
  a:int 
  b:deci32 
}

var t:T[2] = [{a:1, b:2.3f}, {a:2, b:3.4f}]
println(t)
t[1] = {a: 200,b:5.5f}
println(t)
```

### array_of_objects_element_modify.expect
```
[ { a: 1, b: 2.3 }, { a: 2, b: 3.4000001 } ]
[ { a: 1, b: 2.3 }, { a: 200, b: 5.5 } ]
```

## Test: array_of_objects_full_assign

### array_of_objects_full_assign.fg
```javascript
type T = {
  a:int 
  b:deci32 
}

var t:T[2] = [{a:1, b:2.3f}, {a:2, b:3.4f}]
println(t)
t[1] = {b:5.5f}
println(t)
```

### array_of_objects_full_assign.expect
```
[ { a: 1, b: 2.3 }, { a: 2, b: 3.4000001 } ]
[ { a: 1, b: 2.3 }, { a: 0, b: 5.5 } ]
```

## Test: array_of_objects_partial_assign

### array_of_objects_partial_assign.fg
```javascript
type T = {
  a:int 
  b:deci32 
}

var st:T = {
  a: 5,
  b: 12.5f
}

var t:T[2] = [st]
println(t)
t[1] = {b:5.5f}
println(t)
```

### array_of_objects_partial_assign.expect
```
[ { a: 5, b: 12.5 }, { a: 0, b: 0 } ]
[ { a: 5, b: 12.5 }, { a: 0, b: 5.5 } ]
```

## Test: complex_array_init

### complex_array_init.fg
```javascript
type NestedType = {
  value:int
}

type ParentType = {
  name:str,
  nestedArray:NestedType[5]
}

type ComplexType = {
  id:int,
  message:str,
  amount:deci,
  flag:bool,
  parentArray:ParentType[1]
}

{
  var complexArray:ComplexType[2] = [
    {
      id:1,
      message:"hello",
      amount:3.3,
      flag:true,
      parentArray:[
        {
          name:"Parent1",
          nestedArray:[
            {value:1}, {value:2}, {value:3}, {value:4}, {value:5}
          ]
        }
      ]
    },
    {
      id:2,
      message:"world",
      amount:4.4,
      flag:false,
      parentArray:[
        {
          name:"Parent2",
          nestedArray:[
            {value:6}, {value:7}, {value:8}, {value:9}, {value:10}
          ]
        }
      ]
    }
  ]
  print(complexArray)
}
```

### complex_array_init.expect
```
[ { amount: 3.3, flag: true, id: 1, message: "hello", parentArray: [ { name: "Parent1", nestedArray: [ { value: 1 }, { value: 2 }, { value: 3 }, { value: 4 }, { value: 5 } ] } ] }, { amount: 4.4, flag: false, id: 2, message: "world", parentArray: [ { name: "Parent2", nestedArray: [ { value: 6 }, { value: 7 }, { value: 8 }, { value: 9 }, { value: 10 } ] } ] } ]
```

## Test: global_object_array_shadowed_in_block

### global_object_array_shadowed_in_block.fg
```javascript
type T = { val:int }
var a:T[2] = [{val:1}, {val:2}]

println("Global before: ", a)

{
    var a:T[2] = [{val:10}, {val:20}]
    println("Local: ", a)
    a[0].val = 99
    println("Local modified: ", a)
}

println("Global after: ", a)
```

### global_object_array_shadowed_in_block.expect
```
Global before: [ { val: 1 }, { val: 2 } ]
Local: [ { val: 10 }, { val: 20 } ]
Local modified: [ { val: 99 }, { val: 20 } ]
Global after: [ { val: 1 }, { val: 2 } ]
```

## Test: nested_member_array_padding_read

### nested_member_array_padding_read.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:[3] 
}

var st:T = {
  a: 5,
  b: 12.5f,
  c:[1,2]
}

println(st)
```

### nested_member_array_padding_read.expect
```
{ a: 5, b: 12.5, c: [ 1, 2, 0 ] }
```

## Test: nested_member_array_padding_replace

### nested_member_array_padding_replace.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:[3] 
}

var st:T = {
  a: 5,
  b: 12.5f,
  c:[1,2]
}

println(st)
st.c = [1,2,3]
println(st)
```

### nested_member_array_padding_replace.expect
```
{ a: 5, b: 12.5, c: [ 1, 2, 0 ] }
{ a: 5, b: 12.5, c: [ 1, 2, 3 ] }
```

## Test: nested_member_array_read

### nested_member_array_read.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:[3] 
}
var j:[3] = ["Hello", 2, 3]

var st:T = {
  a: 5,
  b: 12.5f,
  c:j
}
println(st.c[0])
```

### nested_member_array_read.expect
```
"Hello"
```

## Test: nested_member_array_reassign

### nested_member_array_reassign.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:[3] 
}
var j:[3] = ["Hello", 2, 3]

var st:T = {
  a: 5,
  b: 12.5f,
  c:j
}
println(st)
println(j)
st.c[0] = "Hi"
println(st)
println(j)
```

### nested_member_array_reassign.expect
```
{ a: 5, b: 12.5, c: [ "Hello", 2, 3 ] }
[ "Hello", 2, 3 ]
{ a: 5, b: 12.5, c: [ "Hi", 2, 3 ] }
[ "Hello", 2, 3 ]
```

## Test: nested_member_array_replace

### nested_member_array_replace.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:[3] 
}
var j:[3] = ["Hello", 2, 3]

var st:T = {
  a: 5,
  b: 12.5f,
  c:j
}

println(st)
st.c = [1,2,3]
println(st)
```

### nested_member_array_replace.expect
```
{ a: 5, b: 12.5, c: [ "Hello", 2, 3 ] }
{ a: 5, b: 12.5, c: [ 1, 2, 3 ] }
```

## Test: nested_member_static_array_no_padding

### nested_member_static_array_no_padding.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:int[2] 
}

var st:T = {
  a: 5,
  b: 12.5f,
  c:[1,2]
}

println(st)
```

### nested_member_static_array_no_padding.expect
```
{ a: 5, b: 12.5, c: [ 1, 2 ] }
```

## Test: nested_member_static_array_padding_read

### nested_member_static_array_padding_read.fg
```javascript
type T = {
  a:int 
  b:deci32,
  c:int[3] 
}

var st:T = {
  a: 5,
  b: 12.5f,
  c:[1,2]
}

println(st)
```

### nested_member_static_array_padding_read.expect
```
{ a: 5, b: 12.5, c: [ 1, 2, 0 ] }
```

---

# Directory: ObjectTests/edge_cases

## Test: all_primitive_types

### all_primitive_types.fg
```javascript
type AllPrimitives = {
    i32: int
    i64: int64
    i8: int8
    _deci: deci
    _deci32: deci32
    _str: str
    ch: char
    b: bool
}

var all: AllPrimitives = {
    i32: 32,
    i64: 64,
    i8: 8,
    _deci: 3.14,
    _deci32: 2.5f,
    _str: "string",
    ch: 'A',
    b: true
}

print(all, "\n")
```

### all_primitive_types.expect
```
{ _deci: 3.14, _deci32: 2.5, _str: "string", b: true, ch: 'A', i32: 32, i64: 64, i8: 8 }
```

## Test: assignment_operators

### assignment_operators.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Initial age: ", p.age, "\n")

p.age = p.age + 5
print("After + 5: ", p.age, "\n")

p.age = p.age - 3
print("After - 3: ", p.age, "\n")

p.age = p.age * 2
print("After * 2: ", p.age, "\n")

p.age = p.age // 4
print("After // 4: ", p.age, "\n")
```

### assignment_operators.expect
```
Initial age: 30
After + 5: 35
After - 3: 32
After * 2: 64
After // 4: 16
```

## Test: bang_operator_nested

### bang_operator_nested.fg
```javascript
type T = {
    x: int
}

type T2 = {
    x: T
}

var t1: T = { x: 10 }
var t2: T = { x: 20 }

var t3: T2 = { x: t1 }
var t4: T2 = { x: t2 }

print("t3 == t4: ", t3 == t4, "\n")
print("t3 != t4: ", t3 != t4, "\n")
print("t3.x == t4.x: ", t3.x == t4.x, "\n")
print("t3.x != t4.x: ", t3.x != t4.x, "\n")

print("!t1: ", !t1, "\n")
print("!t1.x: ", !t1.x, "\n")
print("!t2: ", !t2, "\n")
print("!t2.x: ", !t2.x, "\n")

print("t3.x: ", t3.x, "\n")
print("!t3.x: ", !t3.x, "\n")
t3.x = null
print("t3.x: ", t3.x, "\n")
print("!t3.x: ", !t3.x, "\n")

print("t3: ", t3, "\n")
print("!t3: ", !t3, "\n")

print("t3 == null: ", t3 == null, "\n")
print("t3.x == null: ", t3.x == null, "\n")
```

### bang_operator_nested.expect
```
t3 == t4: false
t3 != t4: true
t3.x == t4.x: false
t3.x != t4.x: true
!t1: false
!t1.x: false
!t2: false
!t2.x: false
t3.x: { x: 10 }
!t3.x: false
t3.x: null
!t3.x: true
t3: { x: null }
!t3: false
t3 == null: false
t3.x == null: true
```

## Test: bang_operator_object

### bang_operator_object.fg
```javascript
type T = {
    x: int
}

var t1: T = { x: 10 }
var t2: T = { x: 20 }

print("t1 == t2: ", t1 == t2, "\n")
print("t1 != t2: ", t1 != t2, "\n")
print("t1.x == t2.x: ", t1.x == t2.x, "\n")
print("t1.x != t2.x: ", t1.x != t2.x, "\n")
print("!t1: ", !t1, "\n")
print("!t1.x: ", !t1.x, "\n")
print("!t2: ", !t2, "\n")
print("!t2.x: ", !t2.x, "\n")
print("!t1 == !t2: ", !t1 == !t2, "\n")
print("!t1 != !t2: ", !t1 != !t2, "\n")
print("!t1.x == !t2.x: ", !t1.x == !t2.x, "\n")
print("!t1.x != !t2.x: ", !t1.x != !t2.x, "\n")
```

### bang_operator_object.expect
```
t1 == t2: false
t1 != t2: true
t1.x == t2.x: false
t1.x != t2.x: true
!t1: false
!t1.x: false
!t2: false
!t2.x: false
!t1 == !t2: true
!t1 != !t2: false
!t1.x == !t2.x: true
!t1.x != !t2.x: false
```

## Test: bang_operator_self_ref

### bang_operator_self_ref.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: null
}

var node2: Node = {
    value: 2,
    next: node1
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

print("!node1: ", !node1, "\n")
print("!node2: ", !node2, "\n")

print("!node1.next: ", !node1.next, "\n")
print("!node2.next: ", !node2.next, "\n")
```

### bang_operator_self_ref.expect
```
node1: { next: null, value: 1 }
node2: { next: { next: null, value: 1 }, value: 2 }
!node1: false
!node2: false
!node1.next: true
!node2.next: false
```

## Test: binary_operations

### binary_operations.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

print("p1.age: ", p1.age, "\n")
print("p2.age: ", p2.age, "\n")
print("p1.age + p2.age: ", p1.age + p2.age, "\n")
print("p1.age * 2: ", p1.age * 2, "\n")
print("p2.age - p1.age: ", p2.age - p1.age, "\n")
```

### binary_operations.expect
```
p1.age: 20
p2.age: 25
p1.age + p2.age: 45
p1.age * 2: 40
p2.age - p1.age: 5
```

## Test: chained_assignment

### chained_assignment.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

var p3: Person = {
    name: "Charlie",
    age: 30
}

print("Initial:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")

p1 = p3
p2 = p3

print("After chained assignment:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")
```

### chained_assignment.expect
```
Initial:
p1: { age: 20, name: "Alice" }
p2: { age: 25, name: "Bob" }
p3: { age: 30, name: "Charlie" }
After chained assignment:
p1: { age: 30, name: "Charlie" }
p2: { age: 30, name: "Charlie" }
p3: { age: 30, name: "Charlie" }
```

## Test: circular_reference

### circular_reference.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1
}

var node2: Node = {
    value: 2
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

node1.next = node2

print("node1.next: ", node1.next, "\n")

node2.next = node1

print("node2.next: ", node2.next, "\n")

print("After circular assignment:\n")
print("node1: ", node1, "\n")
print("node2: ", node2, "\n")
print("node1.next: ", node1.next, "\n")
print("node2.next: ", node2.next, "\n")
```

### circular_reference.expect
```
node1: { next: null, value: 1 }
node2: { next: null, value: 2 }
node1.next: { next: null, value: 2 }
node2.next: { next: { next: <Cycle>, value: 2 }, value: 1 }
After circular assignment:
node1: { next: { next: <Cycle>, value: 2 }, value: 1 }
node2: { next: { next: <Cycle>, value: 1 }, value: 2 }
node1.next: { next: { next: <Cycle>, value: 1 }, value: 2 }
node2.next: { next: { next: <Cycle>, value: 2 }, value: 1 }
```

## Test: circular_type_definition

### circular_type_definition.fg
```javascript
type A = {
    b: B
}

type B = {
    a: A
}
var a1: A = {b:{}}
var x: B = {a: a1}
println(x)
x.a.b = x 
println(x)
```

### circular_type_definition.expect
```
{ a: { b: { a: null } } }
{ a: { b: <Cycle> } }
```

## Test: comparison_operations

### comparison_operations.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

print("p1.age == 20: ", p1.age == 20, "\n")
print("p1.age != p2.age: ", p1.age != p2.age, "\n")
print("p1.age < p2.age: ", p1.age < p2.age, "\n")
print("p1.age > p2.age: ", p1.age > p2.age, "\n")
print("p1.age <= p2.age: ", p1.age <= p2.age, "\n")
print("p1.age >= p2.age: ", p1.age >= p2.age, "\n")
```

### comparison_operations.expect
```
p1.age == 20: true
p1.age != p2.age: true
p1.age < p2.age: true
p1.age > p2.age: false
p1.age <= p2.age: true
p1.age >= p2.age: false
```

## Test: complex_expression

### complex_expression.fg
```javascript
type Person = {
    name: str
    age: int
    height: deci
}

var p1: Person = {
    name: "Alice",
    age: 20,
    height: 5.5
}

var p2: Person = {
    name: "Bob",
    age: 25,
    height: 6.0
}

var avgAge: deci = (p1.age + p2.age) / 2.0
var avgHeight: deci = (p1.height + p2.height) / 2.0
var totalAge: int = p1.age + p2.age

print("Average age: ", avgAge, "\n")
print("Average height: ", avgHeight, "\n")
print("Total age: ", totalAge, "\n")
print("Age difference: ", p2.age - p1.age, "\n")
```

### complex_expression.expect
```
Average age: 22.5
Average height: 5.75
Total age: 45
Age difference: 5
```

## Test: complex_nested

### complex_nested.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

type Shape = {
    name: str
    rect: Rectangle
}

var shape: Shape = {
    name: "MyShape",
    rect: {
        topLeft: {
            x: 0,
            y: 0
        },
        bottomRight: {
            x: 100,
            y: 100
        }
    }
}

print(shape, "\n")
```

### complex_nested.expect
```
{ name: "MyShape", rect: { bottomRight: { x: 100, y: 100 }, topLeft: { x: 0, y: 0 } } }
```

## Test: conditional_assignment

### conditional_assignment.expect
```
Result: { age: 20, name: "Alice" }
Result after condition change: { age: 25, name: "Bob" }
```

## Test: const_comparison

### const_comparison.fg
```javascript
type Person = {
    name: str
    age: int
}

const p1: Person = {
    name: "Alice",
    age: 30
}

const p2: Person = {
    name: "Bob",
    age: 25
}

print("p1.age > p2.age: ", p1.age > p2.age, "\n")
print("p1.name == p2.name: ", p1.name == p2.name, "\n")
print("p1 == p2: ", p1 == p2, "\n")
```

### const_comparison.expect
```
p1.age > p2.age: true
p1.name == p2.name: false
p1 == p2: false
```

## Test: const_in_expression

### const_in_expression.fg
```javascript
type Point = {
    x: int
    y: int
}

const p1: Point = {
    x: 10,
    y: 20
}

const p2: Point = {
    x: 5,
    y: 15
}

var result: int = p1.x + p2.y

print("p1.x: ", p1.x, "\n")
print("p2.y: ", p2.y, "\n")
print("result (p1.x + p2.y): ", result, "\n")
```

### const_in_expression.expect
```
p1.x: 10
p2.y: 15
result (p1.x + p2.y): 25
```

## Test: const_logical_ops

### const_logical_ops.fg
```javascript
type Person = {
    name: str
    age: int
    active: bool
}

const p1: Person = {
    name: "Alice",
    age: 30,
    active: true
}

const p2: Person = {
    name: "Bob",
    age: 25,
    active: false
}

print("p1.active && p2.active: ", p1.active && p2.active, "\n")
print("p1.active || p2.active: ", p1.active || p2.active, "\n")
print("!p1.active: ", !p1.active, "\n")
print("!p2.active: ", !p2.active, "\n")
print("p1.age > 20 && p2.age > 20: ", p1.age > 20 && p2.age > 20, "\n")
print("p1.age > 30 || p2.age > 30: ", p1.age > 30 || p2.age > 30, "\n")
```

### const_logical_ops.expect
```
p1.active && p2.active: false
p1.active || p2.active: true
!p1.active: false
!p2.active: true
p1.age > 20 && p2.age > 20: true
p1.age > 30 || p2.age > 30: false
```

## Test: const_member_binary_ops

### const_member_binary_ops.fg
```javascript
type Point = {
    x: int
    y: int
}

const p1: Point = {
    x: 10,
    y: 20
}

const p2: Point = {
    x: 5,
    y: 15
}

print("p1.x + p2.x: ", p1.x + p2.x, "\n")
print("p1.y - p2.y: ", p1.y - p2.y, "\n")
print("p1.x * 2: ", p1.x * 2, "\n")
print("p1.y / 2: ", p1.y / 2, "\n")
print("p1.x % 3: ", p1.x % 3, "\n")
print("p1.x + p2.y: ", p1.x + p2.y, "\n")
```

### const_member_binary_ops.expect
```
p1.x + p2.x: 15
p1.y - p2.y: 5
p1.x * 2: 20
p1.y / 2: 10
p1.x % 3: 1
p1.x + p2.y: 25
```

## Test: const_member_comparison

### const_member_comparison.fg
```javascript
type Person = {
    name: str
    age: int
}

const p1: Person = {
    name: "Alice",
    age: 30
}

const p2: Person = {
    name: "Bob",
    age: 25
}

print("p1.age == 30: ", p1.age == 30, "\n")
print("p1.age != p2.age: ", p1.age != p2.age, "\n")
print("p1.age < p2.age: ", p1.age < p2.age, "\n")
print("p1.age > p2.age: ", p1.age > p2.age, "\n")
print("p1.age <= p2.age: ", p1.age <= p2.age, "\n")
print("p1.age >= p2.age: ", p1.age >= p2.age, "\n")
print("p1.name == p2.name: ", p1.name == p2.name, "\n")
print("p1.name != p2.name: ", p1.name != p2.name, "\n")
```

### const_member_comparison.expect
```
p1.age == 30: true
p1.age != p2.age: true
p1.age < p2.age: false
p1.age > p2.age: true
p1.age <= p2.age: false
p1.age >= p2.age: true
p1.name == p2.name: false
p1.name != p2.name: true
```

## Test: const_member_unary_ops

### const_member_unary_ops.fg
```javascript
type Point = {
    x: int
    y: int
}

const p: Point = {
    x: 10,
    y: -20
}

print("p.x: ", p.x, "\n")
print("-p.x: ", -p.x, "\n")
print("+p.x: ", +p.x, "\n")
print("~p.x: ", ~p.x, "\n")
print("!p.x: ", !p.x, "\n")
print("p.y: ", p.y, "\n")
print("-p.y: ", -p.y, "\n")
```

### const_member_unary_ops.expect
```
p.x: 10
-p.x: -10
+p.x: 10
~p.x: -11
!p.x: false
p.y: -20
-p.y: 20
```

## Test: const_nested_member_ops

### const_nested_member_ops.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

const rect1: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

const rect2: Rectangle = {
    topLeft: {
        x: 5,
        y: 5
    },
    bottomRight: {
        x: 15,
        y: 15
    }
}

print("rect1.topLeft.x + rect2.topLeft.x: ", rect1.topLeft.x + rect2.topLeft.x, "\n")
print("rect1.bottomRight.y - rect2.bottomRight.y: ", rect1.bottomRight.y - rect2.bottomRight.y, "\n")
print("-rect1.topLeft.x: ", -rect1.topLeft.x, "\n")
print("rect1.topLeft.x == rect2.topLeft.x: ", rect1.topLeft.x == rect2.topLeft.x, "\n")
print("rect1.topLeft.x < rect2.topLeft.x: ", rect1.topLeft.x < rect2.topLeft.x, "\n")
```

### const_nested_member_ops.expect
```
rect1.topLeft.x + rect2.topLeft.x: 5
rect1.bottomRight.y - rect2.bottomRight.y: -5
-rect1.topLeft.x: 0
rect1.topLeft.x == rect2.topLeft.x: false
rect1.topLeft.x < rect2.topLeft.x: true
```

## Test: const_object

### const_object.fg
```javascript
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

print("Const person: ", p, "\n")
print("Name: ", p.name, "\n")
print("Age: ", p.age, "\n")
```

### const_object.expect
```
Const person: { age: 30, name: "John" }
Name: John
Age: 30
```

## Test: const_object_equality

### const_object_equality.fg
```javascript
type Person = {
    name: str
    age: int
}

const p1: Person = {
    name: "Alice",
    age: 30
}

const p2: Person = {
    name: "Alice",
    age: 30
}

const p3: Person = {
    name: "Bob",
    age: 25
}

print("p1 == p2: ", p1 == p2, "\n")
print("p1 != p2: ", p1 != p2, "\n")
print("p1 == p3: ", p1 == p3, "\n")
print("p1 != p3: ", p1 != p3, "\n")
```

### const_object_equality.expect
```
p1 == p2: true
p1 != p2: false
p1 == p3: false
p1 != p3: true
```

## Test: const_object_member_read

### const_object_member_read.fg
```javascript
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

print("Name: ", p.name, "\n")
print("Age: ", p.age, "\n")
print("Full object: ", p, "\n")
```

### const_object_member_read.expect
```
Name: John
Age: 30
Full object: { age: 30, name: "John" }
```

## Test: const_person_equality

### const_person_equality.fg
```javascript
type Person = {
    name: str
    age: int
}

const p1: Person = {
    name: "Alice",
    age: 30
}

const p2: Person = {
    name: "Alice",
    age: 30
}

const p3: Person = {
    name: "Bob",
    age: 25
}

print("p1 == p2: ", p1 == p2, "\n")
print("p1 != p2: ", p1 != p2, "\n")
print("p1 == p3: ", p1 == p3, "\n")
print("p1 != p3: ", p1 != p3, "\n")

var p4: Person = p3

print("p4 == p3: ", p4 == p3, "\n")
print("p4 != p3: ", p4 != p3, "\n")

p4 = p1

print("p4 == p1: ", p4 == p1, "\n")
print("p4 != p1: ", p4 != p1, "\n")
print("p4 == p2: ", p4 == p2, "\n")
print("p4 != p2: ", p4 != p2, "\n")
```

### const_person_equality.expect
```
p1 == p2: true
p1 != p2: false
p1 == p3: false
p1 != p3: true
p4 == p3: true
p4 != p3: false
p4 == p1: true
p4 != p1: false
p4 == p2: true
p4 != p2: false
```

## Test: const_with_nested_mutable

### const_with_nested_mutable.fg
```javascript
type Inner = {
    value: int
}

type Outer = {
    inner: Inner
}

const outer: Outer = {
    inner: {
        value: 10
    }
}

var inner: Inner = {
    value: 20
}

print("Const outer.inner.value (read-only): ", outer.inner.value, "\n")
print("Mutable inner.value (before): ", inner.value, "\n")

inner.value = 30

print("Mutable inner.value (after): ", inner.value, "\n")
print("Const outer.inner.value (still unchanged): ", outer.inner.value, "\n")
```

### const_with_nested_mutable.expect
```
Const outer.inner.value (read-only): 10
Mutable inner.value (before): 20
Mutable inner.value (after): 30
Const outer.inner.value (still unchanged): 10
```

## Test: deep_nested_access

### deep_nested_access.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

type Shape = {
    name: str
    rect: Rectangle
}

var shape: Shape = {
    name: "MyShape",
    rect: {
        topLeft: {
            x: 0,
            y: 0
        },
        bottomRight: {
            x: 100,
            y: 100
        }
    }
}

print("Full shape: ", shape, "\n")
print("Top-left x: ", shape.rect.topLeft.x, "\n")
print("Top-left y: ", shape.rect.topLeft.y, "\n")
print("Bottom-right x: ", shape.rect.bottomRight.x, "\n")
print("Bottom-right y: ", shape.rect.bottomRight.y, "\n")

shape.rect.topLeft.x = 10
shape.rect.topLeft.y = 20
shape.rect.bottomRight.x = 200
shape.rect.bottomRight.y = 300

print("After field updates:\n")
print("Top-left x: ", shape.rect.topLeft.x, "\n")
print("Top-left y: ", shape.rect.topLeft.y, "\n")
print("Bottom-right x: ", shape.rect.bottomRight.x, "\n")
print("Bottom-right y: ", shape.rect.bottomRight.y, "\n")
print("Full shape: ", shape, "\n")
```

### deep_nested_access.expect
```
Full shape: { name: "MyShape", rect: { bottomRight: { x: 100, y: 100 }, topLeft: { x: 0, y: 0 } } }
Top-left x: 0
Top-left y: 0
Bottom-right x: 100
Bottom-right y: 100
After field updates:
Top-left x: 10
Top-left y: 20
Bottom-right x: 200
Bottom-right y: 300
Full shape: { name: "MyShape", rect: { bottomRight: { x: 200, y: 300 }, topLeft: { x: 10, y: 20 } } }
```

## Test: deep_nested_const_read

### deep_nested_const_read.fg
```javascript
type Level3 = {
    value: str
}

type Level2 = {
    level3: Level3
}

type Level1 = {
    level2: Level2
}

const obj: Level1 = {
    level2: {
        level3: {
            value: "deep"
        }
    }
}

print("Level 1 -> Level 2 -> Level 3 value: ", obj.level2.level3.value, "\n")
print("Level 2 -> Level 3: ", obj.level2.level3, "\n")
print("Level 1 -> Level 2: ", obj.level2, "\n")
```

### deep_nested_const_read.expect
```
Level 1 -> Level 2 -> Level 3 value: deep
Level 2 -> Level 3: { value: "deep" }
Level 1 -> Level 2: { level3: { value: "deep" } }
```

## Test: empty_type

### empty_type.fg
```javascript
type Empty = {
}

var e: Empty = {}

print(e, "\n")
```

### empty_type.expect
```
{  }
```

## Test: expression_in_initializer

### expression_in_initializer.fg
```javascript
type Person = {
    name: str
    age: int
}

var x: int = 20
var y: int = 10

var p: Person = {
    name: "John",
    age: x + y
}

print("Person with expression: ", p, "\n")

p.age = p.age * 2

print("After doubling age: ", p, "\n")
```

### expression_in_initializer.expect
```
Person with expression: { age: 30, name: "John" }
After doubling age: { age: 60, name: "John" }
```

## Test: field-assignment-01

### field-assignment-01.fg
```javascript
type P = {
    x:int
}
type T = {
    y:int
    z: P 
}

var t: T = {
    y: 10,
    z: {
        x: 20
    }
}


var j:T 


j.z = t.z

print(j, "\n")
print(t, "\n")
```

### field-assignment-01.expect
```
{ y: 0, z: { x: 20 } }
{ y: 10, z: { x: 20 } }
```

## Test: field_access

### field_access.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Name: ", p.name, "\n")
print("Age: ", p.age, "\n")

p.name = "Jane"
p.age = 25

print("After field updates:\n")
print("Name: ", p.name, "\n")
print("Age: ", p.age, "\n")
print("Full object: ", p, "\n")
```

### field_access.expect
```
Name: John
Age: 30
After field updates:
Name: Jane
Age: 25
Full object: { age: 25, name: "Jane" }
```

## Test: field_order

### field_order.fg
```javascript
type Person = {
    name: str
    age: int
    height: deci
}

var p: Person = {
    height: 5.10,
    name: "John",
    age: 30
}

print(p, "\n")
```

### field_order.expect
```
{ age: 30, height: 5.1, name: "John" }
```

## Test: global_local_scope

### global_local_scope.fg
```javascript
type Person = {
    name: str
    age: int
}

var global: Person = {
    name: "Global",
    age: 100
}

print("Global scope - global: ", global, "\n")

{
    var local: Person = {
        name: "Local",
        age: 50
    }
    
    print("Local scope - local: ", local, "\n")
    print("Local scope - global: ", global, "\n")
    
    local = global
    
    print("After assignment in local scope:\n")
    print("local: ", local, "\n")
    print("global: ", global, "\n")
    
    {
        var nested: Person = {
            name: "Nested",
            age: 25
        }
        
        print("Nested scope - nested: ", nested, "\n")
        print("Nested scope - local: ", local, "\n")
        print("Nested scope - global: ", global, "\n")
        
        nested = local
        
        print("After assignment in nested scope:\n")
        print("nested: ", nested, "\n")
        print("local: ", local, "\n")
        print("global: ", global, "\n")
    }
}

print("Back to global scope - global: ", global, "\n")
```

### global_local_scope.expect
```
Global scope - global: { age: 100, name: "Global" }
Local scope - local: { age: 50, name: "Local" }
Local scope - global: { age: 100, name: "Global" }
After assignment in local scope:
local: { age: 100, name: "Global" }
global: { age: 100, name: "Global" }
Nested scope - nested: { age: 25, name: "Nested" }
Nested scope - local: { age: 100, name: "Global" }
Nested scope - global: { age: 100, name: "Global" }
After assignment in nested scope:
nested: { age: 100, name: "Global" }
local: { age: 100, name: "Global" }
global: { age: 100, name: "Global" }
Back to global scope - global: { age: 100, name: "Global" }
```

## Test: inline_object_print

### inline_object_print.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: null
}

print("node1: ", node1, "\n")

print(
    {
        value: 2
    }
)
print("\n")
```

### inline_object_print.expect
```
node1: { next: null, value: 1 }
{ value: 2 }
```

## Test: large_object

### large_object.fg
```javascript
type LargeObject = {
    field1: int
    field2: int
    field3: int
    field4: int
    field5: int
    field6: str
    field7: str
    field8: str
    field9: deci
    field10: deci
}

var large: LargeObject = {
    field1: 1,
    field2: 2,
    field3: 3,
    field4: 4,
    field5: 5,
    field6: "six",
    field7: "seven",
    field8: "eight",
    field9: 9.9,
    field10: 10.10
}

print(large, "\n")
```

### large_object.expect
```
{ field1: 1, field10: 10.1, field2: 2, field3: 3, field4: 4, field5: 5, field6: "six", field7: "seven", field8: "eight", field9: 9.9 }
```

## Test: linked_list_advanced

### linked_list_advanced.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1
}

node1.next = {
    value: 2,
    next: {
        value: 3,
        next: null
    }
}

print("node1: ", node1, "\n")

var node3: Node = {
    value: 5,
    next: null
}

node1.next = node3

print("node1: ", node1, "\n")

var node4: Node = {
    value: 6,
    next: {
        value: 7,
        next: null
    }
}

node1.next.next = node4

print("node1: ", node1, "\n")

var node5: Node = node1

print("node5: ", node5, "\n")

node5.next = null

print("node1: ", node1, "\n")
print("node5: ", node5, "\n")

print("node1 == node5: ", node1 == node5, "\n")

var node6: Node = {
    value: 1,
    next: null
}

print("node5 == node6: ", node5 == node6, "\n")

var node7: Node = {
    value: 2,
    next: null
}

print("node7 == node6: ", node7 == node6, "\n")
```

### linked_list_advanced.expect
```
node1: { next: { next: { next: null, value: 3 }, value: 2 }, value: 1 }
node1: { next: { next: null, value: 5 }, value: 1 }
node1: { next: { next: { next: { next: null, value: 7 }, value: 6 }, value: 5 }, value: 1 }
node5: { next: { next: { next: { next: null, value: 7 }, value: 6 }, value: 5 }, value: 1 }
node1: { next: null, value: 1 }
node5: { next: null, value: 1 }
node1 == node5: true
node5 == node6: true
node7 == node6: false
```

## Test: linked_list_deep_equality

### linked_list_deep_equality.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node9: Node = {
    value: 2,
    next: {
        value: 3,
        next: null
    }
}

var node10: Node = {
    value: 2,
    next: {
        value: 3,
        next: null
    }
}

print("node9 == node10: ", node9 == node10, "\n")

print("node9.next == node10.next: ", node9.next == node10.next, "\n")

var node11: Node = {
    value: 2,
    next: node9
}

var node12: Node = {
    value: 2,
    next: node10
}

print("node11 == node12: ", node11 == node12, "\n")

node11.next.next = {
    value: 100
}

print("node11: ", node11, "\n")
print("node9: ", node9, "\n")

node11.next.next = null

print("node11: ", node11, "\n")
print("node9: ", node9, "\n")
```

### linked_list_deep_equality.expect
```
node9 == node10: true
node9.next == node10.next: true
node11 == node12: true
node11: { next: { next: { next: null, value: 100 }, value: 2 }, value: 2 }
node9: { next: { next: null, value: 100 }, value: 2 }
node11: { next: { next: null, value: 2 }, value: 2 }
node9: { next: null, value: 2 }
```

## Test: linked_list_equality

### linked_list_equality.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: null
}

var node2: Node = {
    value: 2,
    next: node1
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

print("node1 == node2: ", node1 == node2, "\n")
print("node1 != node2: ", node1 != node2, "\n")

print("node1.next == node2.next: ", node1.next == node2.next, "\n")
print("node1.next != node2.next: ", node1.next != node2.next, "\n")

print("node2.next == node1: ", node2.next == node1, "\n")
print("node2.next != node1: ", node2.next != node1, "\n")

print("node1.next == node2: ", node1.next == node2, "\n")
print("node1.next != node2: ", node1.next != node2, "\n")
```

### linked_list_equality.expect
```
node1: { next: null, value: 1 }
node2: { next: { next: null, value: 1 }, value: 2 }
node1 == node2: false
node1 != node2: true
node1.next == node2.next: false
node1.next != node2.next: true
node2.next == node1: true
node2.next != node1: false
node1.next == node2: false
node1.next != node2: true
```

## Test: linked_list_in_scope

### linked_list_in_scope.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node9: Node = {
    value: 2,
    next: {
        value: 3,
        next: null
    }
}

var node10: Node = {
    value: 2,
    next: {
        value: 3,
        next: null
    }
}

{
    var node11: Node = {
        value: 2,
        next: node9
    }

    var node12: Node = {
        value: 2,
        next: node10
    }

    print("node11 == node12: ", node11 == node12, "\n")
}

var node11: Node = {
    value: 2,
    next: node9
}

var node12: Node = {
    value: 2,
    next: node10
}

print("node11 == node12: ", node11 == node12, "\n")
```

### linked_list_in_scope.expect
```
node11 == node12: true
node11 == node12: true
```

## Test: linked_list_null_ops

### linked_list_null_ops.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: null
}

var node2: Node = {
    value: 2,
    next: node1
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

node1.next = node2

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

node1 = null

print("node1: ", node1, "\n")

node1 = {
    value: 1
}

print("node1: ", node1, "\n")

node1 = {
    next: {
        value: 2
    }
}

print("node1: ", node1, "\n")

node1.next = {
    value: 3,
    next: null
}

print("node1: ", node1, "\n")

node1 = {
    value: 1
}

print("node1: ", node1, "\n")

node1.next = {
    value: 2,
    next: {
        value: 3,
        next: null
    }
}

print("node1: ", node1, "\n")

node1.next.next = {
    value: 4,
    next: null
}

print("node1: ", node1, "\n")
```

### linked_list_null_ops.expect
```
node1: { next: null, value: 1 }
node2: { next: { next: null, value: 1 }, value: 2 }
node1: { next: { next: <Cycle>, value: 2 }, value: 1 }
node2: { next: { next: <Cycle>, value: 1 }, value: 2 }
node1: null
node1: { next: null, value: 1 }
node1: { next: { next: null, value: 2 }, value: 0 }
node1: { next: { next: null, value: 3 }, value: 0 }
node1: { next: null, value: 1 }
node1: { next: { next: { next: null, value: 3 }, value: 2 }, value: 1 }
node1: { next: { next: { next: null, value: 4 }, value: 2 }, value: 1 }
```

## Test: linked_list_operations

### linked_list_operations.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: null
}

var node2: Node = {
    value: 2,
    next: node1
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

node1.next = node2

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

node1 = {
    value: 1,
    next: {
        value: 2,
        next: {
            value: 3
        }
    }
}

print("node1: ", node1, "\n")

node1 = {
    value: 1,
    next: {
        value: 2,
        next: {
            value: 3,
            next: {
                value: 4
            }
        }
    }
}

print("node1: ", node1, "\n")
```

### linked_list_operations.expect
```
node1: { next: null, value: 1 }
node2: { next: { next: null, value: 1 }, value: 2 }
node1: { next: { next: <Cycle>, value: 2 }, value: 1 }
node2: { next: { next: <Cycle>, value: 1 }, value: 2 }
node1: { next: { next: { next: null, value: 3 }, value: 2 }, value: 1 }
node1: { next: { next: { next: { next: null, value: 4 }, value: 3 }, value: 2 }, value: 1 }
```

## Test: member_chain_assignment

### member_chain_assignment.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect1: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

var rect2: Rectangle = {
    topLeft: {
        x: 20,
        y: 20
    },
    bottomRight: {
        x: 30,
        y: 30
    }
}

print("Before:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")

rect1.topLeft = rect2.topLeft

print("After assignment:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")

rect1.topLeft.x = 100
rect1.topLeft.y = 200

print("After modifying rect1.topLeft:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")
```

### member_chain_assignment.expect
```
Before:
rect1.topLeft: { x: 0, y: 0 }
rect2.topLeft: { x: 20, y: 20 }
After assignment:
rect1.topLeft: { x: 20, y: 20 }
rect2.topLeft: { x: 20, y: 20 }
After modifying rect1.topLeft:
rect1.topLeft: { x: 100, y: 200 }
rect2.topLeft: { x: 100, y: 200 }
```

## Test: member_deep_chain_access

### member_deep_chain_access.fg
```javascript
type Node = {
    value: int
    next: Node
}

var nodeDefault: Node
print("nodeDefault: ", nodeDefault, "\n")
var node1: Node = {
    value: 1
}
var node2: Node = {
    value: 2
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

var node3: Node = {
    value: 3,
    next: node1
}

print("node3: ", node3, "\n")

node1.next = node3
node2.next = node1

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")
print("node3: ", node3, "\n")

print("node1: ", node1, "\n")
print("node1.next.next: ", node1.next.next, "\n")
```

### member_deep_chain_access.expect
```
nodeDefault: { next: null, value: 0 }
node1: { next: null, value: 1 }
node2: { next: null, value: 2 }
node3: { next: { next: null, value: 1 }, value: 3 }
node1: { next: { next: <Cycle>, value: 3 }, value: 1 }
node2: { next: { next: { next: <Cycle>, value: 3 }, value: 1 }, value: 2 }
node3: { next: { next: <Cycle>, value: 1 }, value: 3 }
node1: { next: { next: <Cycle>, value: 3 }, value: 1 }
node1.next.next: { next: { next: <Cycle>, value: 3 }, value: 1 }
```

## Test: member_in_expression

### member_in_expression.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

var sum: int = p1.age + p2.age
var product: int = p1.age * p2.age

print("Sum: ", sum, "\n")
print("Product: ", product, "\n")
print("Average: ", sum / 2, "\n")
```

### member_in_expression.expect
```
Sum: 45
Product: 500
Average: 22.5
```

## Test: mixed_const_equality

### mixed_const_equality.fg
```javascript
type Person = {
    name: str
    age: int
}

const constPerson: Person = {
    name: "Alice",
    age: 30
}

var mutablePerson: Person = {
    name: "Alice",
    age: 30
}

var differentPerson: Person = {
    name: "Bob",
    age: 25
}

print("constPerson == mutablePerson: ", constPerson == mutablePerson, "\n")
print("constPerson != mutablePerson: ", constPerson != mutablePerson, "\n")
print("constPerson == differentPerson: ", constPerson == differentPerson, "\n")
print("mutablePerson == differentPerson: ", mutablePerson == differentPerson, "\n")
```

### mixed_const_equality.expect
```
constPerson == mutablePerson: true
constPerson != mutablePerson: false
constPerson == differentPerson: false
mutablePerson == differentPerson: false
```

## Test: mixed_const_nonconst

### mixed_const_nonconst.fg
```javascript
type Person = {
    name: str
    age: int
}

const constPerson: Person = {
    name: "Alice",
    age: 25
}

var mutablePerson: Person = {
    name: "Bob",
    age: 30
}

print("Const person (read-only): ", constPerson, "\n")
print("Mutable person (before): ", mutablePerson, "\n")

mutablePerson.name = "Charlie"
mutablePerson.age = 35

print("Mutable person (after): ", mutablePerson, "\n")
print("Const person (still unchanged): ", constPerson, "\n")
```

### mixed_const_nonconst.expect
```
Const person (read-only): { age: 25, name: "Alice" }
Mutable person (before): { age: 30, name: "Bob" }
Mutable person (after): { age: 35, name: "Charlie" }
Const person (still unchanged): { age: 25, name: "Alice" }
```

## Test: mixed_primitive_object

### mixed_primitive_object.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x: int = 10
var y: str = "test"

print("Person: ", p, "\n")
print("x: ", x, "\n")
print("y: ", y, "\n")

x = p.age
y = p.name

print("After assignments:\n")
print("x: ", x, "\n")
print("y: ", y, "\n")
print("p: ", p, "\n")
```

### mixed_primitive_object.expect
```
Person: { age: 30, name: "John" }
x: 10
y: test
After assignments:
x: 30
y: John
p: { age: 30, name: "John" }
```

## Test: multiple_declarations

### multiple_declarations.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

var p3: Person = {
    name: "Charlie",
    age: 30
}

print("Initial:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")

p1 = p2
p2 = p3

print("After assignments:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")
```

### multiple_declarations.expect
```
Initial:
p1: { age: 20, name: "Alice" }
p2: { age: 25, name: "Bob" }
p3: { age: 30, name: "Charlie" }
After assignments:
p1: { age: 25, name: "Bob" }
p2: { age: 30, name: "Charlie" }
p3: { age: 30, name: "Charlie" }
```

## Test: multiple_types

### multiple_types.fg
```javascript
type Type1 = {
    a: int
    b: str
}

type Type2 = {
    a: int
    b: str
    c: deci
}

type Type3 = {
    a: int
    b: str
    c: deci
}

var t1: Type1 = {
    a: 10,
    b: "hello"
}

var t2: Type2
var t3: Type3

print("Initial:\n")
print("t1: ", t1, "\n")
print("t2: ", t2, "\n")
print("t3: ", t3, "\n")

t2 = t1
t3 = t1

print("After assignments:\n")
print("t1: ", t1, "\n")
print("t2: ", t2, "\n")
print("t3: ", t3, "\n")
```

### multiple_types.expect
```
Initial:
t1: { a: 10, b: "hello" }
t2: { a: 0, b: "", c: 0 }
t3: { a: 0, b: "", c: 0 }
After assignments:
t1: { a: 10, b: "hello" }
t2: { a: 10, b: "hello", c: 0 }
t3: { a: 10, b: "hello", c: 0 }
```

## Test: nested_assignment

### nested_assignment.fg
```javascript
type Address = {
    street: str
    city: str
}

type Person = {
    name: str
    age: int
    address: Address
}

var p1: Person = {
    name: "John",
    age: 30,
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

var p2: Person

print("Before assignment:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")

p2 = p1

print("After assignment:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
```

### nested_assignment.expect
```
Before assignment:
p1: { address: { city: "New York", street: "123 Main St" }, age: 30, name: "John" }
p2: { address: null, age: 0, name: "" }
After assignment:
p1: { address: { city: "New York", street: "123 Main St" }, age: 30, name: "John" }
p2: { address: { city: "New York", street: "123 Main St" }, age: 30, name: "John" }
```

## Test: nested_const_read

### nested_const_read.fg
```javascript
type Address = {
    street: str
    city: str
}

type Person = {
    name: str
    address: Address
}

const person: Person = {
    name: "John",
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

print("Person name: ", person.name, "\n")
print("Street: ", person.address.street, "\n")
print("City: ", person.address.city, "\n")
print("Full address: ", person.address, "\n")
```

### nested_const_read.expect
```
Person name: John
Street: 123 Main St
City: New York
Full address: { city: "New York", street: "123 Main St" }
```

## Test: nested_member_field_assign

### nested_member_field_assign.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect1: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

var rect2: Rectangle = {
    topLeft: {
        x: 20,
        y: 20
    },
    bottomRight: {
        x: 30,
        y: 30
    }
}

print("Before:\n")
print("rect1: ", rect1, "\n")
print("rect2: ", rect2, "\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")

rect1.topLeft.x = rect2.topLeft.x
rect1.topLeft.y = rect2.topLeft.y

print("After nested member assignment:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")
```

### nested_member_field_assign.expect
```
Before:
rect1: { bottomRight: { x: 10, y: 10 }, topLeft: { x: 0, y: 0 } }
rect2: { bottomRight: { x: 30, y: 30 }, topLeft: { x: 20, y: 20 } }
rect1.topLeft: { x: 0, y: 0 }
rect2.topLeft: { x: 20, y: 20 }
After nested member assignment:
rect1.topLeft: { x: 20, y: 20 }
rect2.topLeft: { x: 20, y: 20 }
```

## Test: nested_member_to_member

### nested_member_to_member.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect1: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

var rect2: Rectangle = {
    topLeft: {
        x: 20,
        y: 20
    },
    bottomRight: {
        x: 30,
        y: 30
    }
}

print("Before:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")

rect1.topLeft = rect2.topLeft

print("After assignment:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")

rect1.topLeft.x = 100
rect1.topLeft.y = 200

print("After modifying rect1.topLeft:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")
```

### nested_member_to_member.expect
```
Before:
rect1.topLeft: { x: 0, y: 0 }
rect2.topLeft: { x: 20, y: 20 }
After assignment:
rect1.topLeft: { x: 20, y: 20 }
rect2.topLeft: { x: 20, y: 20 }
After modifying rect1.topLeft:
rect1.topLeft: { x: 100, y: 200 }
rect2.topLeft: { x: 100, y: 200 }
```

## Test: nested_object_binary_ops

### nested_object_binary_ops.expect
```
rect1: { bottomRight: { x: 10, y: 10 }, topLeft: { x: 0, y: 0 } }
rect2: { bottomRight: { x: 15, y: 15 }, topLeft: { x: 5, y: 5 } }
result (rect1 + rect2): { bottomRight: { x: 25, y: 25 }, topLeft: { x: 5, y: 5 } }
```

## Test: nested_object_equality

### nested_object_equality.fg
```javascript
type Address = {
    street: str
    city: str
}

type Person = {
    name: str
    address: Address
}

const p1: Person = {
    name: "John",
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

const p2: Person = {
    name: "John",
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

const p3: Person = {
    name: "John",
    address: {
        street: "456 Oak Ave",
        city: "Boston"
    }
}

print("p1 == p2: ", p1 == p2, "\n")
print("p1 != p2: ", p1 != p2, "\n")
print("p1 == p3: ", p1 == p3, "\n")
print("p1 != p3: ", p1 != p3, "\n")
```

### nested_object_equality.expect
```
p1 == p2: true
p1 != p2: false
p1 == p3: false
p1 != p3: true
```

## Test: nested_object_full_init

### nested_object_full_init.fg
```javascript
type P = {
    x: int
}

type T = {
    z: P
    l: deci
    y: int
}

var j: T

j.z = {
    x: 20
}

j.l = 3.14
j.y = 100

print("j: ", j, "\n")
```

### nested_object_full_init.expect
```
j: { l: 3.14, y: 100, z: { x: 20 } }
```

## Test: nested_object_member_assign

### nested_object_member_assign.fg
```javascript
type P = {
    x: int
}

type T = {
    z: P
    l: deci
    y: int
}

var j: T

j.z = {
    x: 20
}

print("j: ", j, "\n")
```

### nested_object_member_assign.expect
```
j: { l: 0, y: 0, z: { x: 20 } }
```

## Test: nested_object_var_assign

### nested_object_var_assign.fg
```javascript
type P = {
    x: int
}

type T = {
    z: P
    l: deci
    y: int
}

var p1: P = {
    x: 54
}

var j: T = {
    z: p1,
    l: 3.14,
    y: 100
}

j.z = p1

print("p1: ", p1, "\n")
print("j: ", j, "\n")

p1.x = 100
print("After p1.x = 100:\n")
print("p1: ", p1, "\n")
print("j: ", j, "\n")

j.z.x = 200
print("After j.z.x = 200:\n")
print("p1: ", p1, "\n")
print("j: ", j, "\n")
```

### nested_object_var_assign.expect
```
p1: { x: 54 }
j: { l: 3.14, y: 100, z: { x: 54 } }
After p1.x = 100:
p1: { x: 100 }
j: { l: 3.14, y: 100, z: { x: 100 } }
After j.z.x = 200:
p1: { x: 200 }
j: { l: 3.14, y: 100, z: { x: 200 } }
```

## Test: nested_objects

### nested_objects.fg
```javascript
type Address = {
    street: str
    city: str
}

type Person = {
    name: str
    age: int
    address: Address
}

var p: Person = {
    name: "John",
    age: 30,
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

print(p, "\n")
```

### nested_objects.expect
```
{ address: { city: "New York", street: "123 Main St" }, age: 30, name: "John" }
```

## Test: nested_uninitialized

### nested_uninitialized.fg
```javascript
type T = {
    x: int
    y: deci
}

type Nested = {
    z: int
    t1: T
    n2: Nested
}

var n1: Nested

print("n1: ", n1, "\n")
```

### nested_uninitialized.expect
```
n1: { n2: null, t1: null, z: 0 }
```

## Test: null_assignment

### null_assignment.fg
```javascript
type T = {
    x: int
}

var t1: T

print("t1 == null: ", t1 == null, "\n")
print("t1 != null: ", t1 != null, "\n")

t1 = { x: 10 }

print("t1 == null: ", t1 == null, "\n")
print("t1 != null: ", t1 != null, "\n")

t1 = null 

print("t1 == null: ", t1 == null, "\n")
print("t1 != null: ", t1 != null, "\n")
```

### null_assignment.expect
```
t1 == null: false
t1 != null: true
t1 == null: false
t1 != null: true
t1 == null: true
t1 != null: false
```

## Test: null_comparison

### null_comparison.fg
```javascript
type T = {
    x: int
}

var t1: T

print("t1 == null: ", t1 == null, "\n")
print("t1 != null: ", t1 != null, "\n")

t1 = { x: 10 }

print("t1 == null: ", t1 == null, "\n")
print("t1 != null: ", t1 != null, "\n")
```

### null_comparison.expect
```
t1 == null: false
t1 != null: true
t1 == null: false
t1 != null: true
```

## Test: null_initialization

### null_initialization.fg
```javascript
type T = {
    x: int
}

var t1: T = null

print("t1: ", t1, "\n")
```

### null_initialization.expect
```
t1: null
```

## Test: object_assignment_after_decl

### object_assignment_after_decl.fg
```javascript
type P = {
    x: int
}

type T = {
    z: P
    l: deci
    y: int
}

var p1: P = {
    x: 54
}

var j1: T = {
    z: p1,
    l: 3.14,
    y: 100
}

var j2: T

j2 = j1

print("Before modification:\n")
print("j1: ", j1, "\n")
print("j2: ", j2, "\n")

j2.l = 100.00

print("After modification:\n")
print("j1: ", j1, "\n")
print("j2: ", j2, "\n")

print("After modification of j2.z ref:\n")
j2.z.x = 200

print("j1: ", j1, "\n")
print("j2: ", j2, "\n")
```

### object_assignment_after_decl.expect
```
Before modification:
j1: { l: 3.14, y: 100, z: { x: 54 } }
j2: { l: 3.14, y: 100, z: { x: 54 } }
After modification:
j1: { l: 100, y: 100, z: { x: 54 } }
j2: { l: 100, y: 100, z: { x: 54 } }
After modification of j2.z ref:
j1: { l: 100, y: 100, z: { x: 200 } }
j2: { l: 100, y: 100, z: { x: 200 } }
```

## Test: object_equality_simple

### object_equality_simple.fg
```javascript
type T = {
    x: int
}

var t1: T = { x: 10 }
var t2: T = { x: 20 }

print("t1 == t2: ", t1 == t2, "\n")
print("t1 != t2: ", t1 != t2, "\n")
t1 = t2
print("t1 == t2: ", t1 == t2, "\n")
print("t1 != t2: ", t1 != t2, "\n")
```

### object_equality_simple.expect
```
t1 == t2: false
t1 != t2: true
t1 == t2: true
t1 != t2: false
```

## Test: object_equality_with_members

### object_equality_with_members.fg
```javascript
type T = {
    x: int
}

type Nested = {
    x: T
}

var t1: T = { x: 10 }
var t2: T = { x: 20 }

var n1: Nested = { x: t1 }
var n2: Nested = { x: t2 }

print("n1 == n2: ", n1 == n2, "\n")
print("n1 != n2: ", n1 != n2, "\n")
n1 = n2
print("n1 == n2: ", n1 == n2, "\n")

var n3: Nested = { x: t1 }
var n4: Nested = { x: t2 }

print("n3 == n4: ", n3 == n4, "\n")
print("n3 != n4: ", n3 != n4, "\n")
n3 = n4
print("n3 == n4: ", n3 == n4, "\n")
print("n3 != n4: ", n3 != n4, "\n")

type ObjectMembers = {
    x: T
    y: T
}

var o1: ObjectMembers = { x: t1, y: t2 }
var o2: ObjectMembers = { x: t1, y: t2 }

print("o1 == o2: ", o1 == o2, "\n")
print("o1 != o2: ", o1 != o2, "\n")
o1 = o2
print("o1 == o2: ", o1 == o2, "\n")
print("o1 != o2: ", o1 != o2, "\n")

print("o1.x == o2.x: ", o1.x == o2.x, "\n")
print("o1.x != o2.x: ", o1.x != o2.x, "\n")
print("o1.y == o2.y: ", o1.y == o2.y, "\n")
print("o1.y != o2.y: ", o1.y != o2.y, "\n")
```

### object_equality_with_members.expect
```
n1 == n2: false
n1 != n2: true
n1 == n2: true
n3 == n4: false
n3 != n4: true
n3 == n4: true
n3 != n4: false
o1 == o2: true
o1 != o2: false
o1 == o2: true
o1 != o2: false
o1.x == o2.x: true
o1.x != o2.x: false
o1.y == o2.y: true
o1.y != o2.y: false
```

## Test: object_init_with_var

### object_init_with_var.fg
```javascript
type T = {
    x: int
}

var t1: T = { x: 10 }

print("t1: ", t1, "\n")

var t2: T
print("t2: ", t2, "\n")
t2 = { x: 10 }
print("t2: ", t2, "\n")
```

### object_init_with_var.expect
```
t1: { x: 10 }
t2: { x: 0 }
t2: { x: 10 }
```

## Test: object_literal_in_init

### object_literal_in_init.fg
```javascript
type P = {
    x: int
}

type T = {
    z: P
    l: deci
    y: int
}

var j: T = {
    z: {
        x: 20
    },
    l: 3.14,
    y: 100
}

j.z = {
    x: 20
}

print("j: ", j, "\n")
```

### object_literal_in_init.expect
```
j: { l: 3.14, y: 100, z: { x: 20 } }
```

## Test: object_reference_nested

### object_reference_nested.fg
```javascript
type P = {
    x: int
}

type T = {
    z: P
    l: deci
    y: int
}

var p1: P = {
    x: 54
}

var j1: T = {
    z: p1,
    l: 3.14,
    y: 100
}

var j2: T = j1

print("Before modification:\n")
print("j1: ", j1, "\n")
print("j2: ", j2, "\n")

j2.l = 100.00

print("After modification:\n")
print("j1: ", j1, "\n")
print("j2: ", j2, "\n")

print("After modification of j2.z ref:\n")
j2.z.x = 200

print("j1: ", j1, "\n")
print("j2: ", j2, "\n")
```

### object_reference_nested.expect
```
Before modification:
j1: { l: 3.14, y: 100, z: { x: 54 } }
j2: { l: 3.14, y: 100, z: { x: 54 } }
After modification:
j1: { l: 100, y: 100, z: { x: 54 } }
j2: { l: 100, y: 100, z: { x: 54 } }
After modification of j2.z ref:
j1: { l: 100, y: 100, z: { x: 200 } }
j2: { l: 100, y: 100, z: { x: 200 } }
```

## Test: object_reference_semantics

### object_reference_semantics.fg
```javascript
type T = {
    x: int
    y: deci
}

var t1: T = { x: 10, y: 10.10 }
print("t1: ", t1, "\n")

var t2: T = t1
print("t2: ", t2, "\n")

print("t1 == t2: ", t1 == t2, "\n")

t2.x = 100
t2.y = 100.100

print("After modifying t2:\n")
print("t1: ", t1, "\n")
print("t2: ", t2, "\n")
```

### object_reference_semantics.expect
```
t1: { x: 10, y: 10.1 }
t2: { x: 10, y: 10.1 }
t1 == t2: true
After modifying t2:
t1: { x: 100, y: 100.099999999999994 }
t2: { x: 100, y: 100.099999999999994 }
```

## Test: partial_nested

### partial_nested.fg
```javascript
type Address = {
    street: str
    city: str
    zip: int
}

type Person = {
    name: str
    age: int
    address: Address
}

type PartialAddress = {
    street: str
    city: str
}

type PartialPerson = {
    name: str
    address: PartialAddress
}

var partial: PartialPerson = {
    name: "Alice",
    address: {
        street: "456 Oak Ave",
        city: "Boston"
    }
}

var full: Person

print("Before assignment:\n")
print("partial: ", partial, "\n")
print("full: ", full, "\n")

full = partial

print("After assignment:\n")
print("partial: ", partial, "\n")
print("full: ", full, "\n")
```

### partial_nested.expect
```
Before assignment:
partial: { address: { city: "Boston", street: "456 Oak Ave" }, name: "Alice" }
full: { address: null, age: 0, name: "" }
After assignment:
partial: { address: { city: "Boston", street: "456 Oak Ave" }, name: "Alice" }
full: { address: { city: "Boston", street: "456 Oak Ave", zip: 0 }, age: 0, name: "Alice" }
```

## Test: partial_update

### partial_update.fg
```javascript
type Person = {
    name: str
    age: int
    height: deci
    weight: deci
}

var p: Person = {
    name: "John",
    age: 30,
    height: 5.10,
    weight: 70.5
}

print("Initial: ", p, "\n")

p.age = 31
p.height = 6.0

print("After partial update: ", p, "\n")

p.name = "Jane"
p.weight = 65.0

print("After more updates: ", p, "\n")
```

### partial_update.expect
```
Initial: { age: 30, height: 5.1, name: "John", weight: 70.5 }
After partial update: { age: 31, height: 6, name: "John", weight: 70.5 }
After more updates: { age: 31, height: 6, name: "Jane", weight: 65 }
```

## Test: scope

### scope.fg
```javascript
type Person = {
    name: str
    age: int
}

var global: Person = {
    name: "Global",
    age: 100
}

{
    var local: Person = {
        name: "Local",
        age: 50
    }
    
    print("Inside scope:\n")
    print("local: ", local, "\n")
    print("global: ", global, "\n")
    
    local = global
    
    print("After assignment:\n")
    print("local: ", local, "\n")
    print("global: ", global, "\n")
}

print("Outside scope:\n")
print("global: ", global, "\n")
```

### scope.expect
```
Inside scope:
local: { age: 50, name: "Local" }
global: { age: 100, name: "Global" }
After assignment:
local: { age: 100, name: "Global" }
global: { age: 100, name: "Global" }
Outside scope:
global: { age: 100, name: "Global" }
```

## Test: scope_assign_inner_to_outer

### scope_assign_inner_to_outer.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

print("before scope p1: ", p1, "\n")

{
    var p2: Point = { x: 100, y: 200 }
    print("inner p2: ", p2, "\n")
    
    p1 = p2
    print("inner p1 after assign: ", p1, "\n")
    
    p2.x = 999
    print("inner p2 after modify: ", p2, "\n")
    print("inner p1 after p2 modify: ", p1, "\n")
}

print("outer p1 after scope: ", p1, "\n")
```

### scope_assign_inner_to_outer.expect
```
before scope p1: { x: 10, y: 20 }
inner p2: { x: 100, y: 200 }
inner p1 after assign: { x: 100, y: 200 }
inner p2 after modify: { x: 999, y: 200 }
inner p1 after p2 modify: { x: 999, y: 200 }
outer p1 after scope: { x: 999, y: 200 }
```

## Test: scope_bang_operator

### scope_bang_operator.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

print("outer !p1: ", !p1, "\n")

{
    var p1: Point
    print("inner !p1 (uninitialized): ", !p1, "\n")
    
    p1 = { x: 100, y: 200 }
    print("inner !p1 (initialized): ", !p1, "\n")
    
    p1 = null
    print("inner !p1 (null): ", !p1, "\n")
}

print("outer !p1 after scope: ", !p1, "\n")
```

### scope_bang_operator.expect
```
outer !p1: false
inner !p1 (uninitialized): false
inner !p1 (initialized): false
inner !p1 (null): true
outer !p1 after scope: false
```

## Test: scope_basic

### scope_basic.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

print("outer p1: ", p1, "\n")

{
    var p1: Point = { x: 100, y: 200 }
    print("inner p1: ", p1, "\n")
}

print("outer p1 after scope: ", p1, "\n")
```

### scope_basic.expect
```
outer p1: { x: 10, y: 20 }
inner p1: { x: 100, y: 200 }
outer p1 after scope: { x: 10, y: 20 }
```

## Test: scope_const_object

### scope_const_object.fg
```javascript
type Point = {
    x: int
    y: int
}

const p1: Point = { x: 10, y: 20 }

print("outer p1: ", p1, "\n")

{
    const p1: Point = { x: 100, y: 200 }
    print("inner p1: ", p1, "\n")
    
    var p2: Point = p1
    print("inner p2 (from const): ", p2, "\n")
    
    p2.x = 999
    print("inner p2 after modify: ", p2, "\n")
    print("inner p1 after p2 modify: ", p1, "\n")
}

print("outer p1 after scope: ", p1, "\n")
```

### scope_const_object.expect
```
outer p1: { x: 10, y: 20 }
inner p1: { x: 100, y: 200 }
inner p2 (from const): { x: 100, y: 200 }
inner p2 after modify: { x: 999, y: 200 }
inner p1 after p2 modify: { x: 999, y: 200 }
outer p1 after scope: { x: 10, y: 20 }
```

## Test: scope_equality

### scope_equality.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }
var p2: Point = { x: 10, y: 20 }

print("outer p1 == p2: ", p1 == p2, "\n")

{
    var p1: Point = { x: 10, y: 20 }
    var p2: Point = { x: 10, y: 20 }
    
    print("inner p1 == p2: ", p1 == p2, "\n")
    
    p2 = p1
    
    print("inner p1 == p2 after assignment: ", p1 == p2, "\n")
}

print("outer p1 == p2 after scope: ", p1 == p2, "\n")
```

### scope_equality.expect
```
outer p1 == p2: true
inner p1 == p2: true
inner p1 == p2 after assignment: true
outer p1 == p2 after scope: true
```

## Test: scope_linked_list_ref

### scope_linked_list_ref.fg
```javascript
type Node = {
    value: int
    next: Node
}

var outerNode: Node = { value: 1 }

print("outer node: ", outerNode, "\n")

{
    var innerNode: Node = { value: 2, next: outerNode }
    print("inner node: ", innerNode, "\n")
    
    innerNode.next.value = 100
    print("inner node after modify outer via next: ", innerNode, "\n")
}

print("outer node after scope: ", outerNode, "\n")
```

### scope_linked_list_ref.expect
```
outer node: { next: null, value: 1 }
inner node: { next: { next: null, value: 1 }, value: 2 }
inner node after modify outer via next: { next: { next: null, value: 100 }, value: 2 }
outer node after scope: { next: null, value: 100 }
```

## Test: scope_modify_outer

### scope_modify_outer.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

print("before scope p1: ", p1, "\n")

{
    p1.x = 100
    p1.y = 200
    print("inside scope p1: ", p1, "\n")
}

print("after scope p1: ", p1, "\n")
```

### scope_modify_outer.expect
```
before scope p1: { x: 10, y: 20 }
inside scope p1: { x: 100, y: 200 }
after scope p1: { x: 100, y: 200 }
```

## Test: scope_multiple_objects

### scope_multiple_objects.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 1, y: 1 }
var p2: Point = { x: 2, y: 2 }
var p3: Point = { x: 3, y: 3 }

print("outer p1: ", p1, "\n")
print("outer p2: ", p2, "\n")
print("outer p3: ", p3, "\n")

{
    var p1: Point = { x: 10, y: 10 }
    var p2: Point = { x: 20, y: 20 }
    
    print("inner p1: ", p1, "\n")
    print("inner p2: ", p2, "\n")
    print("inner p3 (outer): ", p3, "\n")
    
    p3.x = 300
    p3.y = 300
    
    print("inner p3 after modify: ", p3, "\n")
}

print("outer p1 after: ", p1, "\n")
print("outer p2 after: ", p2, "\n")
print("outer p3 after: ", p3, "\n")
```

### scope_multiple_objects.expect
```
outer p1: { x: 1, y: 1 }
outer p2: { x: 2, y: 2 }
outer p3: { x: 3, y: 3 }
inner p1: { x: 10, y: 10 }
inner p2: { x: 20, y: 20 }
inner p3 (outer): { x: 3, y: 3 }
inner p3 after modify: { x: 300, y: 300 }
outer p1 after: { x: 1, y: 1 }
outer p2 after: { x: 2, y: 2 }
outer p3 after: { x: 300, y: 300 }
```

## Test: scope_nested

### scope_nested.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 1, y: 1 }

print("level 0 p1: ", p1, "\n")

{
    var p1: Point = { x: 2, y: 2 }
    print("level 1 p1: ", p1, "\n")
    
    {
        var p1: Point = { x: 3, y: 3 }
        print("level 2 p1: ", p1, "\n")
        
        {
            var p1: Point = { x: 4, y: 4 }
            print("level 3 p1: ", p1, "\n")
        }
        
        print("level 2 p1 after: ", p1, "\n")
    }
    
    print("level 1 p1 after: ", p1, "\n")
}

print("level 0 p1 after: ", p1, "\n")
```

### scope_nested.expect
```
level 0 p1: { x: 1, y: 1 }
level 1 p1: { x: 2, y: 2 }
level 2 p1: { x: 3, y: 3 }
level 3 p1: { x: 4, y: 4 }
level 2 p1 after: { x: 3, y: 3 }
level 1 p1 after: { x: 2, y: 2 }
level 0 p1 after: { x: 1, y: 1 }
```

## Test: scope_nested_object

### scope_nested_object.fg
```javascript
type Inner = {
    value: int
}

type Outer = {
    name: str
    inner: Inner
}

var obj1: Outer = {
    name: "outer",
    inner: { value: 10 }
}

print("obj1: ", obj1, "\n")

{
    var obj1: Outer = {
        name: "inner scope",
        inner: { value: 100 }
    }
    print("scoped obj1: ", obj1, "\n")
    
    obj1.inner.value = 999
    print("scoped obj1 after modify: ", obj1, "\n")
}

print("obj1 after scope: ", obj1, "\n")
```

### scope_nested_object.expect
```
obj1: { inner: { value: 10 }, name: "outer" }
scoped obj1: { inner: { value: 100 }, name: "inner scope" }
scoped obj1 after modify: { inner: { value: 999 }, name: "inner scope" }
obj1 after scope: { inner: { value: 10 }, name: "outer" }
```

## Test: scope_null_handling

### scope_null_handling.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

print("before scope p1: ", p1, "\n")
print("p1 == null: ", p1 == null, "\n")

{
    p1 = null
    print("inside scope p1: ", p1, "\n")
    print("p1 == null: ", p1 == null, "\n")
    
    p1 = { x: 100, y: 200 }
    print("inside scope p1 after reassign: ", p1, "\n")
}

print("after scope p1: ", p1, "\n")
print("p1 == null: ", p1 == null, "\n")
```

### scope_null_handling.expect
```
before scope p1: { x: 10, y: 20 }
p1 == null: false
inside scope p1: null
p1 == null: true
inside scope p1 after reassign: { x: 100, y: 200 }
after scope p1: { x: 100, y: 200 }
p1 == null: false
```

## Test: scope_reference_outer

### scope_reference_outer.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

print("outer p1: ", p1, "\n")

{
    var p2: Point = p1
    print("inner p2 (ref to outer p1): ", p2, "\n")
    
    p2.x = 999
    p2.y = 888
    
    print("inner p2 after modify: ", p2, "\n")
}

print("outer p1 after scope: ", p1, "\n")
```

### scope_reference_outer.expect
```
outer p1: { x: 10, y: 20 }
inner p2 (ref to outer p1): { x: 10, y: 20 }
inner p2 after modify: { x: 999, y: 888 }
outer p1 after scope: { x: 999, y: 888 }
```

## Test: scope_self_ref

### scope_self_ref.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = { value: 1 }

print("outer node1: ", node1, "\n")

{
    var node1: Node = { value: 100 }
    print("inner node1: ", node1, "\n")
    
    var node2: Node = { value: 200, next: node1 }
    print("inner node2: ", node2, "\n")
}

print("outer node1 after scope: ", node1, "\n")
```

### scope_self_ref.expect
```
outer node1: { next: null, value: 1 }
inner node1: { next: null, value: 100 }
inner node2: { next: { next: null, value: 100 }, value: 200 }
outer node1 after scope: { next: null, value: 1 }
```

## Test: scope_sequential

### scope_sequential.fg
```javascript
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 1, y: 1 }

print("initial p1: ", p1, "\n")

{
    var p1: Point = { x: 10, y: 10 }
    print("scope 1 p1: ", p1, "\n")
}

print("after scope 1 p1: ", p1, "\n")

{
    var p1: Point = { x: 100, y: 100 }
    print("scope 2 p1: ", p1, "\n")
}

print("after scope 2 p1: ", p1, "\n")

{
    var p1: Point = { x: 1000, y: 1000 }
    print("scope 3 p1: ", p1, "\n")
}

print("after scope 3 p1: ", p1, "\n")
```

### scope_sequential.expect
```
initial p1: { x: 1, y: 1 }
scope 1 p1: { x: 10, y: 10 }
after scope 1 p1: { x: 1, y: 1 }
scope 2 p1: { x: 100, y: 100 }
after scope 2 p1: { x: 1, y: 1 }
scope 3 p1: { x: 1000, y: 1000 }
after scope 3 p1: { x: 1, y: 1 }
```

## Test: self_assignment

### self_assignment.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Before: ", p, "\n")

p = p

print("After self-assignment: ", p, "\n")
```

### self_assignment.expect
```
Before: { age: 30, name: "John" }
After self-assignment: { age: 30, name: "John" }
```

## Test: self_ref_default

### self_ref_default.fg
```javascript
type Node = {
    value: int
    next: Node
}

var nodeDefault: Node

print("nodeDefault: ", nodeDefault, "\n")
```

### self_ref_default.expect
```
nodeDefault: { next: null, value: 0 }
```

## Test: self_ref_nested_init

### self_ref_nested_init.fg
```javascript
type T = {
    x: int
    t2: T
}

var t1: T = {
    x: 2,
    t2: {
        x: 10
    }
}

print("t1.x: ", t1.x, "\n")
print("t1.t2.x: ", t1.t2.x, "\n")
```

### self_ref_nested_init.expect
```
t1.x: 2
t1.t2.x: 10
```

## Test: self_ref_partial_init

### self_ref_partial_init.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1
}

var node2: Node = {
    value: 2
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")

var node3: Node = {
    value: 3,
    next: node1
}

print("node3: ", node3, "\n")
```

### self_ref_partial_init.expect
```
node1: { next: null, value: 1 }
node2: { next: null, value: 2 }
node3: { next: { next: null, value: 1 }, value: 3 }
```

## Test: self_ref_with_null

### self_ref_with_null.fg
```javascript
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: null
}

var node2: Node = {
    value: 2,
    next: node1
}

print("node1: ", node1, "\n")
print("node2: ", node2, "\n")
```

### self_ref_with_null.expect
```
node1: { next: null, value: 1 }
node2: { next: { next: null, value: 1 }, value: 2 }
```

## Test: shadowing

### shadowing.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "Global",
    age: 100
}

print("Global p: ", p, "\n")

{
    var p: Person = {
        name: "Local",
        age: 50
    }
    
    print("Local p (shadowed): ", p, "\n")
    
    p.age = 25
    
    print("After modifying local p: ", p, "\n")
}

print("Global p after local scope: ", p, "\n")
```

### shadowing.expect
```
Global p: { age: 100, name: "Global" }
Local p (shadowed): { age: 50, name: "Local" }
After modifying local p: { age: 25, name: "Local" }
Global p after local scope: { age: 100, name: "Global" }
```

## Test: string_concatenation

### string_concatenation.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Name: " + p.name + "\n")
print("Age: " + p.age + "\n")
print("Full: " + p.name + " is " + p.age + " years old\n")
```

### string_concatenation.expect
```
Name: John
Age: 30
Full: John is 30 years old
```

## Test: triple_nested_object

### triple_nested_object.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

type Shape = {
    name: str
    rect: Rectangle
}

var shape: Shape = {
    name: "MyShape",
    rect: {
        topLeft: {
            x: 0,
            y: 0
        },
        bottomRight: {
            x: 100,
            y: 100
        }
    }
}

print("shape: ", shape, "\n")

print("shape.rect: ", shape.rect, "\n")
print("shape.rect.bottomRight: ", shape.rect.bottomRight, "\n")
```

### triple_nested_object.expect
```
shape: { name: "MyShape", rect: { bottomRight: { x: 100, y: 100 }, topLeft: { x: 0, y: 0 } } }
shape.rect: { bottomRight: { x: 100, y: 100 }, topLeft: { x: 0, y: 0 } }
shape.rect.bottomRight: { x: 100, y: 100 }
```

## Test: type_promotion

### type_promotion.fg
```javascript
type Small = {
    a: int
}

type Medium = {
    a: int
    b: str
}

type Large = {
    a: int
    b: str
    c: deci
}

var small: Small = {
    a: 10
}

var medium: Medium
var large: Large

print("Initial:\n")
print("small: ", small, "\n")
print("medium: ", medium, "\n")
print("large: ", large, "\n")

medium = small
large = small
large = medium

print("After assignments:\n")
print("small: ", small, "\n")
print("medium: ", medium, "\n")
print("large: ", large, "\n")
```

### type_promotion.expect
```
Initial:
small: { a: 10 }
medium: { a: 0, b: "" }
large: { a: 0, b: "", c: 0 }
After assignments:
small: { a: 10 }
medium: { a: 10, b: "" }
large: { a: 10, b: "", c: 0 }
```

## Test: unary_on_member

### unary_on_member.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Age: ", p.age, "\n")
print("Negated age: ", -(p.age), "\n")
print("Bitwise not age: ", ~(p.age), "\n")
print("Logical not (age == 0): ", !(p.age == 0), "\n")
```

### unary_on_member.expect
```
Age: 30
Negated age: -30
Bitwise not age: -31
Logical not (age == 0): true
```

## Test: zero_values

### zero_values.fg
```javascript
type Person = {
    name: str
    age: int
    height: deci
    isActive: bool
}

var p: Person = {
    name: "",
    age: 0,
    height: 0.0,
    isActive: false
}

print("Zero values: ", p, "\n")

p.name = "John"
p.age = 30

print("After updates: ", p, "\n")
```

### zero_values.expect
```
Zero values: { age: 0, height: 0, isActive: false, name: "" }
After updates: { age: 30, height: 0, isActive: false, name: "John" }
```

---

# Directory: ObjectTests/assignment

## Test: different_type_compatible

### different_type_compatible.fg
```javascript
type type_test = {
    _string_name: str
    _int_age: int
    _int64: int64
    _int8: int8
    _char: char
    _bool: bool
    _deci_age: deci
    _deci32_age: deci32
}

type sub_type_test = {
    _int_age: int
    _int64: int64
    _string_name: str
}

var y: sub_type_test = {
    _string_name: "John",
    _int_age: 20
}

var x: type_test

print("Before assignment:\n")
print("x: ", x, "\n")
print("y: ", y, "\n")

x = y

print("After assignment:\n")
print("x: ", x, "\n")
print("y: ", y, "\n")
```

### different_type_compatible.expect
```
Before assignment:
x: { _bool: false, _char: '', _deci32_age: 0, _deci_age: 0, _int64: 0, _int8: 0, _int_age: 0, _string_name: "" }
y: { _int64: 0, _int_age: 20, _string_name: "John" }
After assignment:
x: { _bool: false, _char: '', _deci32_age: 0, _deci_age: 0, _int64: 0, _int8: 0, _int_age: 20, _string_name: "John" }
y: { _int64: 0, _int_age: 20, _string_name: "John" }
```

## Test: member_to_member

### member_to_member.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

print("Before:\n")
print("p1.name: ", p1.name, ", p1.age: ", p1.age, "\n")
print("p2.name: ", p2.name, ", p2.age: ", p2.age, "\n")

p1.name = p2.name
p1.age = p2.age

print("After member-to-member assignment:\n")
print("p1.name: ", p1.name, ", p1.age: ", p1.age, "\n")
print("p2.name: ", p2.name, ", p2.age: ", p2.age, "\n")
```

### member_to_member.expect
```
Before:
p1.name: Alice, p1.age: 20
p2.name: Bob, p2.age: 25
After member-to-member assignment:
p1.name: Bob, p1.age: 25
p2.name: Bob, p2.age: 25
```

## Test: member_to_member_const

### member_to_member_const.fg
```javascript
type Person = {
    name: str
    age: int
}

const source: Person = {
    name: "Alice",
    age: 30
}

var dest: Person = {
    name: "Bob",
    age: 25
}

print("Before assignment:\n")
print("source: ", source, "\n")
print("dest: ", dest, "\n")

dest.name = source.name
dest.age = source.age

print("After assignment:\n")
print("source: ", source, "\n")
print("dest: ", dest, "\n")
```

### member_to_member_const.expect
```
Before assignment:
source: { age: 30, name: "Alice" }
dest: { age: 25, name: "Bob" }
After assignment:
source: { age: 30, name: "Alice" }
dest: { age: 30, name: "Alice" }
```

## Test: multiple_assignments

### multiple_assignments.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

var p3: Person = {
    name: "Charlie",
    age: 30
}

print("Initial:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")

p1 = p2
p2 = p3

print("After assignments:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")
```

### multiple_assignments.expect
```
Initial:
p1: { age: 20, name: "Alice" }
p2: { age: 25, name: "Bob" }
p3: { age: 30, name: "Charlie" }
After assignments:
p1: { age: 25, name: "Bob" }
p2: { age: 30, name: "Charlie" }
p3: { age: 30, name: "Charlie" }
```

## Test: nested_member_assignment

### nested_member_assignment.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect1: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

var rect2: Rectangle = {
    topLeft: {
        x: 20,
        y: 20
    },
    bottomRight: {
        x: 30,
        y: 30
    }
}

print("Before:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")

rect1.topLeft.x = rect2.topLeft.x
rect1.topLeft.y = rect2.topLeft.y

print("After nested member assignment:\n")
print("rect1.topLeft: ", rect1.topLeft, "\n")
print("rect2.topLeft: ", rect2.topLeft, "\n")
```

### nested_member_assignment.expect
```
Before:
rect1.topLeft: { x: 0, y: 0 }
rect2.topLeft: { x: 20, y: 20 }
After nested member assignment:
rect1.topLeft: { x: 20, y: 20 }
rect2.topLeft: { x: 20, y: 20 }
```

## Test: nested_member_const_read

### nested_member_const_read.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

const rect: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

print("Top-left x: ", rect.topLeft.x, "\n")
print("Top-left y: ", rect.topLeft.y, "\n")
print("Bottom-right x: ", rect.bottomRight.x, "\n")
print("Bottom-right y: ", rect.bottomRight.y, "\n")
print("Full rectangle: ", rect, "\n")
```

### nested_member_const_read.expect
```
Top-left x: 0
Top-left y: 0
Bottom-right x: 10
Bottom-right y: 10
Full rectangle: { bottomRight: { x: 10, y: 10 }, topLeft: { x: 0, y: 0 } }
```

## Test: object_literal_assignment

### object_literal_assignment.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Initial: ", p, "\n")

p = {
    name: "Jane",
    age: 25
}

print("After literal assignment: ", p, "\n")

p = {
    name: "Bob",
    age: 40
}

print("After second literal assignment: ", p, "\n")
```

### object_literal_assignment.expect
```
Initial: { age: 30, name: "John" }
After literal assignment: { age: 25, name: "Jane" }
After second literal assignment: { age: 40, name: "Bob" }
```

## Test: partial_fields

### partial_fields.fg
```javascript
type FullPerson = {
    name: str
    age: int
    height: deci
    weight: deci
    isEmployed: bool
}

type PartialPerson = {
    name: str
    age: int
}

var partial: PartialPerson = {
    name: "Alice",
    age: 28
}

var full: FullPerson

print("Before assignment:\n")
print("partial: ", partial, "\n")
print("full: ", full, "\n")

full = partial

print("After assignment:\n")
print("partial: ", partial, "\n")
print("full: ", full, "\n")
```

### partial_fields.expect
```
Before assignment:
partial: { age: 28, name: "Alice" }
full: { age: 0, height: 0, isEmployed: false, name: "", weight: 0 }
After assignment:
partial: { age: 28, name: "Alice" }
full: { age: 28, height: 0, isEmployed: false, name: "Alice", weight: 0 }
```

## Test: reassignment

### reassignment.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print("Initial: ", p, "\n")

p = {
    name: "Jane",
    age: 25
}

print("After reassignment: ", p, "\n")
```

### reassignment.expect
```
Initial: { age: 30, name: "John" }
After reassignment: { age: 25, name: "Jane" }
```

## Test: same_type

### same_type.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "John",
    age: 30
}

var p2: Person = {
    name: "Jane",
    age: 25
}

print("Before assignment:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")

p1 = p2

print("After assignment:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
```

### same_type.expect
```
Before assignment:
p1: { age: 30, name: "John" }
p2: { age: 25, name: "Jane" }
After assignment:
p1: { age: 25, name: "Jane" }
p2: { age: 25, name: "Jane" }
```

## Test: swap_objects

### swap_objects.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 20
}

var p2: Person = {
    name: "Bob",
    age: 25
}

var temp: Person

print("Before swap:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")

temp = p1
p1 = p2
p2 = temp

print("After swap:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("temp: ", temp, "\n")
```

### swap_objects.expect
```
Before swap:
p1: { age: 20, name: "Alice" }
p2: { age: 25, name: "Bob" }
After swap:
p1: { age: 25, name: "Bob" }
p2: { age: 20, name: "Alice" }
temp: { age: 20, name: "Alice" }
```

## Test: valid_nested_member_assignment

### valid_nested_member_assignment.fg
```javascript
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 10,
        y: 10
    }
}

print("Before assignment:\n")
print("rect.topLeft: ", rect.topLeft, "\n")

rect.topLeft.x = 5
rect.topLeft.y = 5

print("After assignment:\n")
print("rect.topLeft: ", rect.topLeft, "\n")
```

### valid_nested_member_assignment.expect
```
Before assignment:
rect.topLeft: { x: 0, y: 0 }
After assignment:
rect.topLeft: { x: 5, y: 5 }
```

---

# Directory: ObjectTests/errors

## Test: assign_count_mismatch

### assign_count_mismatch.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "John",
    age: 30
}

var p2: Person = {
    name: "Jane",
    age: 25
}

var p3: Person

p1, p2 = p3
```

## Test: assign_count_mismatch2

### assign_count_mismatch2.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "John",
    age: 30
}

var p2: Person = {
    name: "Jane",
    age: 25
}

var p3: Person

p1 = p2, p3
```

## Test: assign_incompatible_nested

### assign_incompatible_nested.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Point = {
    x: int
    y: int
    j:int
}

type Point3D = {
    x: int
    y: int
    z: int
}

type Shape = {
    point: Point
}

type Shape3D = {
    point: Point3D
}

var shape: Shape = {
    point: {
        x: 0,
        y: 0
    }
}

var shape3d: Shape3D

shape3d.point = shape.point
```

## Test: assign_member_access_to_wrong_type

### assign_member_access_to_wrong_type.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x: int = 10

p.name = x
```

## Test: assign_member_to_wrong_type

### assign_member_to_wrong_type.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x: str = "test"

p.name = 123
```

## Test: assign_member_to_wrong_type2

### assign_member_to_wrong_type2.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

p.age = "not a number"
```

## Test: assign_object_to_primitive

### assign_object_to_primitive.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x: int

x = p
```

## Test: assign_primitive_to_object

### assign_primitive_to_object.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person
var x: int = 10

p = x
```

## Test: assign_to_const

### assign_to_const.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

p = {
    name: "Jane",
    age: 25
}
```

## Test: assign_to_const_in_scope

### assign_to_const_in_scope.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Person = {
    name: str
    age: int
}

{
    const p: Person = {
        name: "John",
        age: 30
    }
    
    p.name = "Jane"
}
```

## Test: assign_to_const_member_chain

### assign_to_const_member_chain.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Address = {
    street: str
    city: str
}

type Person = {
    name: str
    address: Address
}

const person: Person = {
    name: "John",
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

person.address.street = "456 Oak Ave"
```

## Test: assign_to_const_multiple_fields

### assign_to_const_multiple_fields.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Person = {
    name: str
    age: int
    email: str
}

const p: Person = {
    name: "John",
    age: 30,
    email: "john@example.com"
}

p.name = "Jane"
p.age = 25
```

## Test: assign_to_const_nested_object

### assign_to_const_nested_object.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Inner = {
    data: str
}

type Outer = {
    inner: Inner
}

const outer: Outer = {
    inner: {
        data: "test"
    }
}

outer.inner.data = "modified"
```

## Test: assign_to_deep_nested_const

### assign_to_deep_nested_const.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Level3 = {
    value: int
}

type Level2 = {
    level3: Level3
}

type Level1 = {
    level2: Level2
}

const obj: Level1 = {
    level2: {
        level3: {
            value: 42
        }
    }
}

obj.level2.level3.value = 100
```

## Test: assign_to_member_of_const

### assign_to_member_of_const.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

p.name = "Jane"
```

## Test: assign_to_non_lvalue

### assign_to_non_lvalue.fg
```javascript
/; EXPECT_ERROR: UnexpectedToken
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

{
    name: "Jane",
    age: 25
} = p
```

## Test: assign_to_nonexistent_member

### assign_to_nonexistent_member.fg
```javascript
/; EXPECT_ERROR: MemberNotFoundInObject
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

p.nonexistent = "value"
```

## Test: const_object_unary_bitwise_not

### const_object_unary_bitwise_not.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

var result = ~p
```

## Test: const_object_unary_negate

### const_object_unary_negate.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

var result = -p
```

## Test: const_object_unary_plus

### const_object_unary_plus.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
type Person = {
    name: str
    age: int
}

const p: Person = {
    name: "John",
    age: 30
}

var result = +p
```

## Test: custom_type_does_not_exists

### custom_type_does_not_exists.fg
```javascript
/; EXPECT_ERROR: CustomTypeNotFound
type Node = {
    value: int
    next: Node3
}
```

## Test: duplicate_type_declaration

### duplicate_type_declaration.fg
```javascript
/; EXPECT_ERROR: CustomTypeAlreadyDeclared
type Person = {
    name: str
    age: int
}

type Person = {
    name: str
    age: int
}
```

## Test: extra_fields

### extra_fields.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30,
    extra: "field"
}
```

## Test: incompatible_object_types

### incompatible_object_types.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Type1 = {
    a: int
    b: str
}

type Type2 = {
    x: deci
    y: bool
}

var t1: Type1 = {
    a: 10,
    b: "hello"
}

var t2: Type2

t2 = t1
```

## Test: initializer_type_mismatch

### initializer_type_mismatch.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: 123,
    age: "thirty"
}
```

## Test: invalid_binary_operation

### invalid_binary_operation.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var result = p + p
```

## Test: invalid_field_type

### invalid_field_type.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: "thirty"
}
```

## Test: invalid_unary_operation

### invalid_unary_operation.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var result = -p
```

## Test: member_access_non_object

### member_access_non_object.fg
```javascript
/; EXPECT_ERROR: MemberAccessOnNonObjectVariable
var x: int = 10
var y = x.field
```

## Test: member_access_on_wrong_type

### member_access_on_wrong_type.fg
```javascript
/; EXPECT_ERROR: MemberAccessOnNonObjectVariable
var x: int = 10
var y = x.field
```

## Test: missing_field

### missing_field.fg
```javascript
/; EXPECT_ERROR: MemberNotFoundInObject
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x = p.nonexistent
```

## Test: nested_member_access_error

### nested_member_access_error.fg
```javascript
/; EXPECT_ERROR: MemberNotFoundInObject
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect: Rectangle = {
    topLeft: {
        x: 0,
        y: 0
    },
    bottomRight: {
        x: 100,
        y: 100
    }
}

var z = rect.topLeft.z
```

## Test: too_few_initializers

### too_few_initializers.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
type Person = {
    name: str
    age: int
}

var p1: Person
var p2: Person

p1, p2: Person = {
    name: "John",
    age: 30
}, {
    name: "Jane",
    age: 25
}, {
    name: "Extra",
    age: 20
}
```

## Test: too_many_initializers

### too_many_initializers.fg
```javascript
/; EXPECT_ERROR: TooManyInitializerExpressions
type Person = {
    name: str
    age: int
}

var p1, p2: Person = {
    name: "John",
    age: 30
}, {
    name: "Jane",
    age: 25
}, {
    name: "Extra",
    age: 20
}
```

## Test: type_mismatch

### type_mismatch.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
type AllTypes = {
    _string_name: str
    _int_age: int
    _int64: int64
    _int8: int8
    _char: char
    _bool: bool
    _deci_age: deci
    _deci32_age: deci32
}

var x: AllTypes = {
    _string_name: "Test",
    _int_age: 20,
    _int64: 1000000000000,
    _int8: 127,
    _char: 'A',
    _bool: true,
    _deci_age: 3.14,
    _deci32_age: 2.5
}

print(x, "\n")
```

## Test: type_mismatch_in_nested

### type_mismatch_in_nested.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect: Rectangle = {
    topLeft: {
        x: "not a number",
        y: 0
    },
    bottomRight: {
        x: 100,
        y: 100
    }
}
```

## Test: type_not_found

### type_not_found.fg
```javascript
/; EXPECT_ERROR: CustomTypeNotFound
var p: UnknownType = {
    name: "John",
    age: 30
}
```

## Test: variable_already_declared

### variable_already_declared.fg
```javascript
/; EXPECT_ERROR: VariableAlreadyDeclared
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var p: Person = {
    name: "Jane",
    age: 25
}
```

---

# Directory: ObjectTests/scopes

## Test: dyn_object_interaction

### dyn_object_interaction.fg
```javascript
type T = { val:int }
var obj:T = { val: 42 }
var dyn2 = obj.val
println(dyn2)
dyn2 = "changed"
println(dyn2)
println(obj.val)
```

### dyn_object_interaction.expect
```
42
"changed"
42
```

## Test: object_global_scope

### object_global_scope.fg
```javascript
type T = { x:int, y:int }
var obj:T = { x:10, y:20 }
println(obj)
{
    obj.x = 100
    println(obj)
}
println(obj)
```

### object_global_scope.expect
```
{ x: 10, y: 20 }
{ x: 100, y: 20 }
{ x: 100, y: 20 }
```

## Test: object_local_scope

### object_local_scope.fg
```javascript
type T = { val:str }
{
    var obj:T = { val: "hello" }
    println(obj)
}
```

### object_local_scope.expect
```
{ val: "hello" }
```

## Test: object_shadowed_in_scope

### object_shadowed_in_scope.fg
```javascript
type T = { n:int }
var obj:T = { n: 1 }
println(obj)
{
    var obj:T = { n: 999 }
    println(obj)
}
println(obj)
```

### object_shadowed_in_scope.expect
```
{ n: 1 }
{ n: 999 }
{ n: 1 }
```

---

# Directory: ObjectTests/declaration

## Test: all_types

### all_types.fg
```javascript
type AllTypes = {
    _string_name: str
    _int_age: int
    _int64: int64
    _int8: int8
    _char: char
    _bool: bool
    _deci_age: deci
    _deci32_age: deci32
}

var x: AllTypes = {
    _string_name: "Test",
    _int_age: 20,
    _int64: 1000000000000,
    _int8: 127,
    _char: 'A',
    _bool: true,
    _deci_age: 3.14,
    _deci32_age: 2.5f
}

print(x, "\n")
```

### all_types.expect
```
{ _bool: true, _char: 'A', _deci32_age: 2.5, _deci_age: 3.14, _int64: 1000000000000, _int8: 127, _int_age: 20, _string_name: "Test" }
```

## Test: basic

### basic.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

print(p, "\n")
```

### basic.expect
```
{ age: 30, name: "John" }
```

## Test: empty

### empty.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person = {}

print(p, "\n")
```

### empty.expect
```
{ age: 0, name: "" }
```

## Test: mixed_types

### mixed_types.fg
```javascript
type Person = {
    name: str
    age: int
}

type Point = {
    x: int
    y: int
}

var p: Person = {
    name: "John",
    age: 30
}

var pt: Point = {
    x: 10,
    y: 20
}

print("Person: ", p, "\n")
print("Point: ", pt, "\n")
```

### mixed_types.expect
```
Person: { age: 30, name: "John" }
Point: { x: 10, y: 20 }
```

## Test: multiple

### multiple.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person = {
    name: "Alice",
    age: 25
}

var p2: Person = {
    name: "Bob",
    age: 30
}

var p3: Person = {
    name: "Charlie",
    age: 35
}

print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")
```

### multiple.expect
```
p1: { age: 25, name: "Alice" }
p2: { age: 30, name: "Bob" }
p3: { age: 35, name: "Charlie" }
```

## Test: multiple_same_line

### multiple_same_line.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person, p2: Person, p3: Person

print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")

p1 = {
    name: "Alice",
    age: 20
}

p2 = {
    name: "Bob",
    age: 25
}

p3 = {
    name: "Charlie",
    age: 30
}

print("After assignments:\n")
print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
print("p3: ", p3, "\n")
```

### multiple_same_line.expect
```
p1: { age: 0, name: "" }
p2: { age: 0, name: "" }
p3: { age: 0, name: "" }
After assignments:
p1: { age: 20, name: "Alice" }
p2: { age: 25, name: "Bob" }
p3: { age: 30, name: "Charlie" }
```

## Test: multiple_with_initializers

### multiple_with_initializers.fg
```javascript
type Person = {
    name: str
    age: int
}

var p1: Person, p2: Person = {
    name: "Alice",
    age: 20
}, {
    name: "Bob",
    age: 25
}

print("p1: ", p1, "\n")
print("p2: ", p2, "\n")
```

### multiple_with_initializers.expect
```
p1: { age: 20, name: "Alice" }
p2: { age: 25, name: "Bob" }
```

## Test: partial

### partial.fg
```javascript
type Person = {
    name: str
    age: int
    height: deci
}

var p: Person = {
    name: "John",
    age: 25
}

print(p, "\n")
```

### partial.expect
```
{ age: 25, height: 0, name: "John" }
```

## Test: uninitialized

### uninitialized.fg
```javascript
type Person = {
    name: str
    age: int
}

var p: Person

print(p, "\n")
```

### uninitialized.expect
```
{ age: 0, name: "" }
```

---

# Directory: BringTests/11_errors

## Test: bring_choosy_file_has_errors

### bring_choosy_file_has_errors.fg
```javascript
/; EXPECT_ERROR: FileContainsErrors
bring {x} from "broken_lib.fg"

println(0)
```

## Test: bring_choosy_not_reexported_from_nested

### bring_choosy_not_reexported_from_nested.fg
```javascript
/; EXPECT_ERROR: IdentifierNotFoundInFileOrModule
bring {nested_leaf_val} from "../include_for_nested_chain/nested_mid.fg"

println(0)
```

## Test: bring_choosy_unknown_identifier

### bring_choosy_unknown_identifier.fg
```javascript
/; EXPECT_ERROR: IdentifierNotFoundInFileOrModule
bring {does_not_exist} from "../01_ok/bring_ok_lib.fg"

println(0)
```

## Test: bring_circular_two_file_cycle

### bring_circular_two_file_cycle.fg
```javascript
/; EXPECT_ERROR: CircularReference
bring "../support_circular_bring/bring_circular_pair_b.fg"

println(0)
```

## Test: bring_duplicate_same_file

### bring_duplicate_same_file.fg
```javascript
/; EXPECT_ERROR: VariableAlreadyDeclared
bring "../support_dup_lib/dup_one_var_lib.fg"
bring "../support_dup_lib/dup_one_var_lib.fg"

println(0)
```

## Test: bring_file_has_errors

### bring_file_has_errors.fg
```javascript
/; EXPECT_ERROR: FileContainsErrors
bring "broken_lib.fg"

println(0)
```

## Test: bring_missing_file

### bring_missing_file.fg
```javascript
/; EXPECT_ERROR: FileNotFound
bring "file_not_exist_9f3a2c1d.fg"

println(0)
```

## Test: bring_self_cycle

### bring_self_cycle.fg
```javascript
/; EXPECT_ERROR: CircularReference
bring "bring_self_cycle.fg"

println(0)
```

## Test: broken_lib

### broken_lib.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
this is not valid flowwing
```

## Test: nested_import_transitive_hidden

### nested_import_transitive_hidden.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
bring "../include_for_nested_chain/nested_mid.fg"

println(nested_leaf_val)
```

---

# Directory: BringTests/BringTestBasicTestAllChoosy

## Test: expose_only

### expose_only.fg
```javascript
expose var x:int = 2
```

### expose_only.expect
```

```

## Test: expose_var_only

### expose_var_only.fg
```javascript
expose var x:int = 2
```

### expose_var_only.expect
```

```

## Test: file1

### file1.fg
```javascript
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2] 

expose class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}




expose fun callS(x:int ) -> nthg {
  var aF:A = new A({b:[{s:"Hello"}]})
  print("Printing af ",aF.y)

  print("Printing k ",k)

  print("Print local x",x)
}
```

### file1.expect
```

```

## Test: file1_class_only

### file1_class_only.fg
```javascript
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2] 

expose class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}
```

### file1_class_only.expect
```

```

## Test: file1_empty_class

### file1_empty_class.fg
```javascript
expose class A {
}
```

### file1_empty_class.expect
```

```

## Test: file1_no_callS

### file1_no_callS.fg
```javascript
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2] 

expose class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}
```

### file1_no_callS.expect
```

```

## Test: file1_to_class

### file1_to_class.fg
```javascript
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2] 

expose class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}
```

### file1_to_class.expect
```

```

## Test: file1_types_only

### file1_types_only.fg
```javascript
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2]
```

### file1_types_only.expect
```

```

## Test: file1_types_vars

### file1_types_vars.fg
```javascript
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2]
```

### file1_types_vars.expect
```

```

## Test: task

### task.fg
```javascript
bring {x,k,j,callS,A,T,TB} from "file1.fg"


print(x)

print(k)

print(j)



callS(88)

var p:T  

p = {a:2 }
print("print p ",p )

var g:A = new A({})

g.printY()
```

### task.expect
```
2{ a: 0, b: [ { s: "" }, { s: "" } ] }[ { a: 0, b: [ { s: "" }, { s: "" } ] }, { a: 0, b: [ { s: "" }, { s: "" } ] } ]Printing af { a: 0, b: [ { s: "Hello" }, { s: "" } ] }Printing k { a: 0, b: [ { s: "" }, { s: "" } ] }Print local x88print p { a: 2, b: [ { s: "" }, { s: "" } ] }{ a: 0, b: [ { s: "" }, { s: "" } ] }
```

---

# Directory: BringTests/BringTestBasicTestAll

## Test: class_empty

### class_empty.fg
```javascript
class A {
}
```

### class_empty.expect
```

```

## Test: file1

### file1.fg
```javascript
var x:int = 2

type TB = {
    s:str 
  }

type T  ={
    a:int,
    b:TB[2]
}

var k:T = {}

var j:T[2] 

class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}




fun callS(x:int ) -> nthg {
  var aF:A = new A({b:[{s:"Hello"}]})
  print("Printing af ",aF.y)

  print("Printing k ",k)

  print("Print local x",x)
}
```

### file1.expect
```

```

## Test: task2

### task2.fg
```javascript
bring "file1.fg"


print(x)

print(k)

print(j)



callS(88)

var p:T  

p = {a:2 }
print("print p ",p )

var g:A = new A({a:100})

g.printY()
```

### task2.expect
```
2{ a: 0, b: [ { s: "" }, { s: "" } ] }[ { a: 0, b: [ { s: "" }, { s: "" } ] }, { a: 0, b: [ { s: "" }, { s: "" } ] } ]Printing af { a: 0, b: [ { s: "Hello" }, { s: "" } ] }Printing k { a: 0, b: [ { s: "" }, { s: "" } ] }Print local x88print p { a: 2, b: [ { s: "" }, { s: "" } ] }{ a: 100, b: [ { s: "" }, { s: "" } ] }
```

---

# Directory: BringTests/support_dup_lib

## Test: dup_one_var_lib

### dup_one_var_lib.fg
```javascript
var dup_exported: int = 1
```

### dup_one_var_lib.expect
```

```

---

# Directory: BringTests/support_choosy_lib

## Test: single_int_var

### single_int_var.fg
```javascript
var exported_only: int = 99
```

### single_int_var.expect
```

```

---

# Directory: BringTests/support_circular_bring

## Test: bring_circular_pair_a

### bring_circular_pair_a.fg
```javascript
/; EXPECT_ERROR: CircularReference
/; Circular-bring support: side A of an intentional A<->B cycle (see pair B).
/; Includes types, globals, and a function so the graph looks like real split modules.
bring "bring_circular_pair_b.fg"

type SideARecord = { owner_id: int, revision: int }

var a_partition_rows: int = 10

fun a_row_hint() -> int {
  return a_partition_rows
}
```

## Test: bring_circular_pair_b

### bring_circular_pair_b.fg
```javascript
/; EXPECT_ERROR: CircularReference
bring "c.fg"
```

## Test: c

### c.fg
```javascript
/; EXPECT_ERROR: CircularReference
/; Circular-bring support: side B imports A again, closing the A<->B cycle.
/; The compiler must report CircularReference; this pair is not valid to merge.
/; EXPECT_ERROR: CircularReference
bring "bring_circular_pair_a.fg"

type SideBRecord = { tag_id: int, checksum: int }

var b_partition_rows: int = 20

fun b_row_hint() -> int {
  return b_partition_rows
}
```

---

# Directory: BringTests/include_for_nested_chain

## Test: nested_leaf

### nested_leaf.fg
```javascript
var nested_leaf_val: int = 7
println(nested_leaf_val)
```

### nested_leaf.expect
```
7
```

## Test: nested_mid

### nested_mid.fg
```javascript
bring "nested_leaf.fg"
println(0)
```

### nested_mid.expect
```
7
0
```

---

# Directory: BringTests/01_ok

## Test: bring_choosy_one_symbol

### bring_choosy_one_symbol.fg
```javascript
bring {exported_only} from "../support_choosy_lib/single_int_var.fg"

println(exported_only)
```

### bring_choosy_one_symbol.expect
```
99
```

## Test: bring_ok_lib

### bring_ok_lib.fg
```javascript
var only_in_this_file: int = 42
println(only_in_this_file)
```

### bring_ok_lib.expect
```
42
```

## Test: bring_validates_only

### bring_validates_only.fg
```javascript
bring "bring_ok_lib.fg"

println(only_in_this_file)
```

### bring_validates_only.expect
```
42
42
```

## Test: nested_import_explicit_leaf

### nested_import_explicit_leaf.fg
```javascript
bring "../include_for_nested_chain/nested_mid.fg"
bring "../include_for_nested_chain/nested_leaf.fg"

println(nested_leaf_val)
```

### nested_import_explicit_leaf.expect
```
7
0
7
```

---

# Directory: ContainerTests

## Test: array_bool_uninit

### array_bool_uninit.fg
```javascript
var x:bool[2]
println(x)
```

### array_bool_uninit.expect
```
[ false, false ]
```

## Test: array_cast_error_runtime_32

### array_cast_error_runtime_32.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int =  5
var y = "Hello"

var a:int[5] = [x, y]
print(a)
```

## Test: array_cast_error_runtime_32_2

### array_cast_error_runtime_32_2.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int =  5
var y:str = "Hello"

var a:int[5] = [x, y]
print(a)
```

## Test: array_char_uninit

### array_char_uninit.fg
```javascript
var x:char[2]
println(x)
```

### array_char_uninit.expect
```
[ '', '' ]
```

## Test: array_double_nested_padding

### array_double_nested_padding.fg
```javascript
var a:int[5][2] = [[1, 2], [3, 4]]
print(a)
```

### array_double_nested_padding.expect
```
[ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ]
```

## Test: array_dyn_cast_success

### array_dyn_cast_success.fg
```javascript
var x:int =  5
var y = 7

var a:int[5] = [x, y]
print(a)
```

### array_dyn_cast_success.expect
```
[ 5, 7, 0, 0, 0 ]
```

## Test: array_dyn_cast_success_2

### array_dyn_cast_success_2.fg
```javascript
var x:int =  5

var a:int[5] = [x, 7]
print(a)
```

### array_dyn_cast_success_2.expect
```
[ 5, 7, 0, 0, 0 ]
```

## Test: array_dynamic_assign_diff_types

### array_dynamic_assign_diff_types.fg
```javascript
var x:[2] = [2, "Hello"]
println("x = ", x)
println("x[0] = ", x[0])
println("x[1] = ", x[1])
x[1] = 2.4
println("x = ", x)
x = [true, 2]
println("x = ", x)
```

### array_dynamic_assign_diff_types.expect
```
x = [ 2, "Hello" ]
x[0] = 2
x[1] = "Hello"
x = [ 2, 2.4 ]
x = [ true, 2 ]
```

## Test: array_dynamic_cast_modify

### array_dynamic_cast_modify.fg
```javascript
var x:[2] = ['a','b']
println(x)
var j:int[2] = [1, 2]
println(j)
x = j
println(x)
println(j)
x[1] = "Hello World"
j[1] = 11
println(x)
println(j)
```

### array_dynamic_cast_modify.expect
```
[ 'a', 'b' ]
[ 1, 2 ]
[ 1, 2 ]
[ 1, 2 ]
[ 1, "Hello World" ]
[ 1, 11 ]
```

## Test: array_int_reassign

### array_int_reassign.fg
```javascript
var x:int[2] = [1, 2]
var j = 5
x[1] = j
println("x = ", x)
println("j = ", j)
j = 10
println("x = ", x)
println("j = ", j)
```

### array_int_reassign.expect
```
x = [ 1, 5 ]
j = 5
x = [ 1, 5 ]
j = 10
```

## Test: array_int_reassign_explicit

### array_int_reassign_explicit.fg
```javascript
var x:int[2] = [1, 2]
var j:int = 5
x[1] = j
println("x = ", x)
println("j = ", j)
j = 10
println("x = ", x)
println("j = ", j)
```

### array_int_reassign_explicit.expect
```
x = [ 1, 5 ]
j = 5
x = [ 1, 5 ]
j = 10
```

## Test: array_mixed_type_cast_deci

### array_mixed_type_cast_deci.fg
```javascript
var x =  5
var y = 2.2f
var z = 3.2f

var a:deci32[5] = [x, y, z]
print(a)
```

### array_mixed_type_cast_deci.expect
```
[ 5, 2.2, 3.2, 0, 0 ]
```

## Test: array_mixed_type_cast_str

### array_mixed_type_cast_str.fg
```javascript
var x =  5
var y = "Hello"
var z = 3.2f
var w:bool = true

var a:str[5] = [x, y, z, w]
print(a)
```

### array_mixed_type_cast_str.expect
```
[ "5", "Hello", "3.2", "true", "" ]
```

## Test: array_mixed_type_cast_str2

### array_mixed_type_cast_str2.fg
```javascript
var x =  5
var y = "Hello"

var a:str[5] = [x, y]
print(a)
```

### array_mixed_type_cast_str2.expect
```
[ "5", "Hello", "", "", "" ]
```

## Test: array_mixed_type_nested

### array_mixed_type_nested.fg
```javascript
var x:int = 10
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]

print(a)
```

### array_mixed_type_nested.expect
```
[ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 10, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

## Test: array_single_padding

### array_single_padding.fg
```javascript
var a:int[5] = [1, 2]
print(a)
```

### array_single_padding.expect
```
[ 1, 2, 0, 0, 0 ]
```

## Test: array_str_uninit

### array_str_uninit.fg
```javascript
var x:str[2] 
println(x)
```

### array_str_uninit.expect
```
[ "", "" ]
```

## Test: array_triple_nested_padding

### array_triple_nested_padding.fg
```javascript
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[5], [7, 8]], [[9, 10], [11, 12]]]
print(a)
```

### array_triple_nested_padding.expect
```
[ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 5, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

## Test: double_dim_multi_oob

### double_dim_multi_oob.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
var a:int[2][2] = [[1, 2], [3, 4]]
println(a[0][3])
```

## Test: double_dim_multi_read_assign

### double_dim_multi_read_assign.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
p = [10, 11]
println(a)
println(p)
```

### double_dim_multi_read_assign.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
[ [ 1, 2 ], [ 3, 4 ] ]
[ 10, 11 ]
```

## Test: double_dim_multi_read_assign2

### double_dim_multi_read_assign2.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = [9, 10]
println(a)
println(p)
p = a[1]
println(a)
println(p)
```

### double_dim_multi_read_assign2.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 9, 10 ]
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
```

## Test: double_dim_multi_read_assign3

### double_dim_multi_read_assign3.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
p = [10, 11]
println(a)
println(p)
```

### double_dim_multi_read_assign3.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
[ [ 1, 2 ], [ 3, 4 ] ]
[ 10, 11 ]
```

## Test: double_dim_multi_read_elements

### double_dim_multi_read_elements.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
println(a[0][0])
println(a[0][1])
println(a[1][0])
println(a[1][1])
```

### double_dim_multi_read_elements.expect
```
1
2
3
4
```

## Test: double_dim_multi_read_modify

### double_dim_multi_read_modify.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
p[0] = 11
println(a)
println(p)
```

### double_dim_multi_read_modify.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
[ [ 1, 2 ], [ 11, 4 ] ]
[ 11, 4 ]
```

## Test: double_dim_multi_read_nested

### double_dim_multi_read_nested.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = [1, a[1][1]]
println(a)
println(p)
```

### double_dim_multi_read_nested.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 1, 4 ]
```

## Test: double_dim_multi_read_prim

### double_dim_multi_read_prim.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var k:int = a[1][1]
println(k)
```

### double_dim_multi_read_prim.expect
```
4
```

## Test: double_dim_multi_read_print

### double_dim_multi_read_print.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
```

### double_dim_multi_read_print.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
```

## Test: dynamic_array_scope_shadowing

### dynamic_array_scope_shadowing.fg
```javascript
var d:[2] = [true, "Hello"]
{
    var d:[2] = [100, 2.5]
    println("Inner: ", d)
}
println("Outer: ", d)
```

### dynamic_array_scope_shadowing.expect
```
Inner: [ 100, 2.5 ]
Outer: [ true, "Hello" ]
```

## Test: global_array_modified_in_block

### global_array_modified_in_block.fg
```javascript
var a:int[3] = [1, 2, 3]

{
    a[1] = 100
    println(a)
}

println(a)
```

### global_array_modified_in_block.expect
```
[ 1, 100, 3 ]
[ 1, 100, 3 ]
```

## Test: multi_dim_array_cast_error

### multi_dim_array_cast_error.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int8.
var x:[2][3] = [[1, 2, 3], ["Hello", "World", "Test"]]
println(x)
var j:int[2][3] = [[1, 2, 3], x[1]]
println(j)
x = j
println(x)
println(j)
x[1] = ["Test", "World", "Test"]
j[1] = [1, 2, 3]
println(x)
println(j)
x[1][1] = 3.5
j[1][1] = 3
println(x)
println(j)
```

## Test: multi_dim_array_int

### multi_dim_array_int.fg
```javascript
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
println("x = ", x)
var j:int[3] = [9, 8, 7]
println("j = ", j)
x[1] = j
println("x = ", x)
println("j = ", j)
j[1] = 100
println("x = ", x)
println("j = ", j)
```

### multi_dim_array_int.expect
```
x = [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
j = [ 9, 8, 7 ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
j = [ 9, 8, 7 ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
j = [ 9, 100, 7 ]
```

## Test: multi_dim_array_reassign

### multi_dim_array_reassign.fg
```javascript
var x:[2][3] = [[1, 2, 3], ["Hello", "World", 1.2]]
println(x)
var j:int[2][3] = [[1, 2, 3], x[0]]
println(j)
x = j
println(x)
println(j)
x[1] = ["Test", "World", "Test"]
j[1] = [1, 2, 3]
println(x)
println(j)
x[1][1] = 3.5
j[1][1] = 3
println(x)
println(j)
```

### multi_dim_array_reassign.expect
```
[ [ 1, 2, 3 ], [ "Hello", "World", 1.2 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ "Test", "World", "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ "Test", 3.5, "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
```

## Test: multi_dim_dynamic_array

### multi_dim_dynamic_array.fg
```javascript
var k:[3] = [2,"Some", "Test"]
var x:[2][3] = [[1,2,3]]

println(k)
println(x)

x = [k, ["H"]]
println(x)
println(k)

x[1] = k
println(x)
println(k)
```

### multi_dim_dynamic_array.expect
```
[ 2, "Some", "Test" ]
[ [ 1, 2, 3 ], [ 0, 0, 0 ] ]
[ [ 2, "Some", "Test" ], [ "H", 0, 0 ] ]
[ 2, "Some", "Test" ]
[ [ 2, "Some", "Test" ], [ 2, "Some", "Test" ] ]
[ 2, "Some", "Test" ]
```

## Test: multi_dim_dynamic_array_complex

### multi_dim_dynamic_array_complex.fg
```javascript
var x:[2][3] = [[1, 2, 3], ["Hello", "World", "Test"]]
println("x = ", x)
var j:int[2][3] = [[1, 2, 3], x[0]]
println("j = ", j)
x = j
println("x = ", x)
println("j = ", j)
x[1] = ["Test", "World", "Test"]
j[1] = [1, 2, 3]
println("x = ", x)
println("j = ", j)
x[1][1] = 3.5
j[1][1] = 3
println("x = ", x)
println("j = ", j)
x[1] = j[1]
println("x = ", x)
println("j = ", j)
x[1][1] = 22
println("x = ", x)
println("j = ", j)
```

### multi_dim_dynamic_array_complex.expect
```
x = [ [ 1, 2, 3 ], [ "Hello", "World", "Test" ] ]
j = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
x = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
j = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
x = [ [ 1, 2, 3 ], [ "Test", "World", "Test" ] ]
j = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
x = [ [ 1, 2, 3 ], [ "Test", 3.5, "Test" ] ]
j = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
x = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
j = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
x = [ [ 1, 2, 3 ], [ 1, 22, 3 ] ]
j = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
```

## Test: multi_dim_dynamic_array_complex_print

### multi_dim_dynamic_array_complex_print.fg
```javascript
var x:[2][3] = [[1, 2, 3], ["Hello", "World", "Test"]]
println(x)
var j:int[2][3] = [[1, 2, 3], x[0]]
println(j)
x = j
println(x)
println(j)
x[1] = ["Test", "World", "Test"]
j[1] = [1, 2, 3]
println(x)
println(j)
x[1][1] = 3.5
j[1][1] = 3
println(x)
println(j)
```

### multi_dim_dynamic_array_complex_print.expect
```
[ [ 1, 2, 3 ], [ "Hello", "World", "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ "Test", "World", "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ "Test", 3.5, "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
```

## Test: multi_dim_dynamic_array_init

### multi_dim_dynamic_array_init.fg
```javascript
var k:[3] = [2,"Some", "Test"]
var x:[2][3] = [k, k]
println(x)
```

### multi_dim_dynamic_array_init.expect
```
[ [ 2, "Some", "Test" ], [ 2, "Some", "Test" ] ]
```

## Test: multi_dim_dynamic_array_padding

### multi_dim_dynamic_array_padding.fg
```javascript
var k:[3] = [2,"Some", "Test"]
var x:[2][3] = [k, ["test2", 5]]
println(x)
```

### multi_dim_dynamic_array_padding.expect
```
[ [ 2, "Some", "Test" ], [ "test2", 5, 0 ] ]
```

## Test: multi_dim_dynamic_array_strs

### multi_dim_dynamic_array_strs.fg
```javascript
var k:[3] = ["Some", "Test", "Hello"]
var x:[2][3] = [k, k]
println(x)
```

### multi_dim_dynamic_array_strs.expect
```
[ [ "Some", "Test", "Hello" ], [ "Some", "Test", "Hello" ] ]
```

## Test: multi_dim_int_array_modify

### multi_dim_int_array_modify.fg
```javascript
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
println("x = ", x)
x[1] = [9, 8, 7]
println("x = ", x)
x[1][1] = 100
println("x = ", x)
```

### multi_dim_int_array_modify.expect
```
x = [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
x = [ [ 1, 2, 3 ], [ 9, 100, 7 ] ]
```

## Test: multi_dim_int_array_row_replace

### multi_dim_int_array_row_replace.fg
```javascript
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
println("x = ", x)
x[1] = [9, 8, 7]
println("x = ", x)
```

### multi_dim_int_array_row_replace.expect
```
x = [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
```

## Test: multi_dim_mixed_vars

### multi_dim_mixed_vars.fg
```javascript
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1,j]

var q:int[3][2] = [l, p,[7,j]]

print(q)
```

### multi_dim_mixed_vars.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 7, 2 ] ]
```

## Test: multi_dim_mixed_vars_3

### multi_dim_mixed_vars_3.fg
```javascript
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1,j]

var q:int[3][2] = [l, p,p]

print(q)
```

### multi_dim_mixed_vars_3.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: multi_dim_mixed_vars_4

### multi_dim_mixed_vars_4.fg
```javascript
var p:int[2] = [3, 5]
var l:int[2] = [1,2]

var q:int[3][2] = [l, p,p]

print(q)
```

### multi_dim_mixed_vars_4.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: multi_dim_mixed_vars_5

### multi_dim_mixed_vars_5.fg
```javascript
var p:int[2] = [3, 5]

var q:int[3][2] = [[1, 2], p,p]

print(q)
```

### multi_dim_mixed_vars_5.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: multi_dim_mixed_vars_6

### multi_dim_mixed_vars_6.fg
```javascript
var p:int[2] = [3, 5]

var q:int[3][2] = [[1, 2], p, [5, 6]]

print(q)
```

### multi_dim_mixed_vars_6.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 5, 6 ] ]
```

## Test: multi_dim_padding_with_vars

### multi_dim_padding_with_vars.fg
```javascript
var p:int[2][4] = [[1,2,3,4], [5,6,7,8]]

var q:int[3][2][4] = [[[1],[2]], p, [[5], [6]]]

print(q)
```

### multi_dim_padding_with_vars.expect
```
[ [ [ 1, 0, 0, 0 ], [ 2, 0, 0, 0 ] ], [ [ 1, 2, 3, 4 ], [ 5, 6, 7, 8 ] ], [ [ 5, 0, 0, 0 ], [ 6, 0, 0, 0 ] ] ]
```

## Test: nested_blocks_array_access

### nested_blocks_array_access.fg
```javascript
{
    var x:int[2][2] = [[1, 2], [3, 4]]
    {
        x[0][1] = 200
        {
            x[1][0] = 300
            println(x)
        }
    }
    println(x)
}
```

### nested_blocks_array_access.expect
```
[ [ 1, 200 ], [ 300, 4 ] ]
[ [ 1, 200 ], [ 300, 4 ] ]
```

## Test: single_dim_multi_ref

### single_dim_multi_ref.fg
```javascript
var a:int[2] = [1, 2]
println(a)
var b:int[2] = a 
println(b)
```

### single_dim_multi_ref.expect
```
[ 1, 2 ]
[ 1, 2 ]
```

## Test: triple_dim_multi_ref

### triple_dim_multi_ref.fg
```javascript
var a:int[5] = [1, 2, 3, 4, 5]
var b:int[2][5] = [a, [6, 7, 8, 9, 10]]
var c:int[3][2][5] = [b, [[11, 12], [13, 14]], b]
var d:int[3][2][5] = c
println(a)
println(b)
println(c)
println(d)
```

### triple_dim_multi_ref.expect
```
[ 1, 2, 3, 4, 5 ]
[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
```

## Test: triple_dim_multi_ref_2

### triple_dim_multi_ref_2.fg
```javascript
var a:int[5] = [1, 2, 3, 4, 5]
var b:int[2][5] = [a, [6, 7, 8, 9, 10]]
var c:int[3][2][5] = [b, [[11, 12], [13, 14]], b]
println(a)
println(b)
println(c)
```

### triple_dim_multi_ref_2.expect
```
[ 1, 2, 3, 4, 5 ]
[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
```

## Test: triple_nested_multi_dim

### triple_nested_multi_dim.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p = [[1,2,3], a[0][1]]
println(a)
println(p)
p[1][1] = 100
println(a)
println(p)
var j:int[3] = [9,8,6]
p = [[1,2,3], j]
println(a)
println(j)
println(p)
p[1][1] = 100
println(a)
println(j)
println(p)
```

### triple_nested_multi_dim.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 1, 2, 3 ], [ 4, 100, 6 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ 9, 8, 6 ]
[ [ 1, 2, 3 ], [ 9, 8, 6 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ 9, 8, 6 ]
[ [ 1, 2, 3 ], [ 9, 100, 6 ] ]
```

## Test: triple_nested_multi_dim_assign

### triple_nested_multi_dim_assign.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p = [[1,2,3], [4,5,6]]
println(a)
println(p)
```

### triple_nested_multi_dim_assign.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
```

## Test: triple_nested_multi_dim_modify_0

### triple_nested_multi_dim_modify_0.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p[0][0] = 11
println(a)
println(p)
```

### triple_nested_multi_dim_modify_0.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 11, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 11, 8, 9 ], [ 10, 11, 12 ] ]
```

## Test: triple_nested_multi_dim_modify_2

### triple_nested_multi_dim_modify_2.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p[0][2] = 11
println(a)
println(p)
```

### triple_nested_multi_dim_modify_2.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 11 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 11 ], [ 10, 11, 12 ] ]
```

## Test: triple_nested_multi_dim_oob

### triple_nested_multi_dim_oob.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
println(a[1][1][3])
```

## Test: triple_nested_multi_dim_read

### triple_nested_multi_dim_read.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
println(a)
println(a[1])
println(a[1][1])
println(a[1][1][1])
```

### triple_nested_multi_dim_read.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ 10, 11, 12 ]
11
```

---

# Directory: ContainerTests/errors

## Test: array_empty_init_error

### array_empty_init_error.fg
```javascript
/; EXPECT_ERROR: EmptyContainerExpression
var x:int[2] = []
println(x)
```

## Test: array_index_more_dims_error

### array_index_more_dims_error.fg
```javascript
/; EXPECT_ERROR: IndexingMoreDimensionsThanArrayTypeHas
var a:int[2] = [1, 2]
println(a[0][2])
```

## Test: array_index_non_array_error

### array_index_non_array_error.fg
```javascript
/; EXPECT_ERROR: IndexingNonArrayTypeVariable
var a:int = 2
println(a[0])
```

## Test: array_index_non_int_error

### array_index_non_int_error.fg
```javascript
/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var a:int[2] = [1, 2]
var x:int[3] =  [1, 3]
print(a[x])
```

## Test: array_init_type_mismatch_error

### array_init_type_mismatch_error.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var a:int[5] = [[2,3], [2,3]]
```

## Test: array_rank_mismatch_error

### array_rank_mismatch_error.fg
```javascript
/; EXPECT_ERROR: ContainerExpressionRankMismatch
var a:int[5] = [1, [2,3]]
```

## Test: array_var_not_found_error

### array_var_not_found_error.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]

print(a)
```

## Test: multi_dim_mixed_vars_error

### multi_dim_mixed_vars_error.fg
```javascript
/; EXPECT_ERROR: ContainerExpressionRankMismatch
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1,j]

var q:int[3][2] = [l, p,[7,p]]

print(q)
```

---

# Directory: 01_string

## Test: add

### add.fg
```javascript
print("String Concatenation\n")
print("Hello" + "World", "\n")
print("Hello" + "World" + "Hello", "\n")

print("String Concatenation with Numbers\n")
print("Hello" + 2, "\n")
print("Hello" + 2.0, "\n")
print("Hello" + 2.0f, "\n")
print("Hello" + 2.2f, "\n")
print("Hello" + 2.5, "\n")
print("Hello" + true, "\n")

print("String Concatenation with Booleans\n")
print("Hello" + true, "\n")
print("Hello" + false, "\n")

print("String Concatenation with Characters\n")
print("Hello" + 'a', "\n")
print("Hello" + 'b', "\n")

print("String Concatenation with escaped characters\n")
print("Hello" + "\n", "\n")
print("Hello" + "\t" + "World", "\n")
print("Hello" + "\r" + "World", "\n")
print("Hello" + "\0" + "World", "\n")
print("old text" +"\r" + "new text", "\n")

print("String Concatenation with Char\n")
print("Hello" + 'a', "\n")
print("Hello" + 'b', "\n")
print("Hello" + ('a' + 'b'), "\n")
print("Hello" + ('a' != 'b'), "\n")
print("Hello" + ('a' == 'b'), "\n")
print("Hello" + ('a' != 'a'), "\n")
print("Hello" + ('a' == 'a'), "\n")
print("Hello" + ('a' != 'b'), "\n")

print("String Concatenation Char with Char\n")
print('a' + 'b', "\n")
```

### add.expect
```
String Concatenation
HelloWorld
HelloWorldHello
String Concatenation with Numbers
Hello2
Hello2
Hello2
Hello2.2
Hello2.5
Hellotrue
String Concatenation with Booleans
Hellotrue
Hellofalse
String Concatenation with Characters
Helloa
Hellob
String Concatenation with escaped characters
Hello

Hello	World
Hello
World
HelloWorld
old text
new text
String Concatenation with Char
Helloa
Hellob
Helloab
Hellotrue
Hellofalse
Hellofalse
Hellotrue
Hellotrue
String Concatenation Char with Char
ab
```

## Test: complex

### complex.fg
```javascript
print("Complex Concatenation Operation\n")
print("Hello" + "World" + "Hello", "\n")
print("Hello" + "World" + "Hello" + "World", "\n")


print("Contact different types in single operation\n")
print("Hello" + 2 + "World" + true + "Hello", "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false + 'a', "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false + 'a' + 'b', "\n")


print(0*(1+2.2)+1.1*2.3f+"S"+1*2+2*0.01+"1111"+"hello"=="1.10000000000000S20.000000000000001111hello")
print("\n")
print(0*(1+1)+1.1*1+"S"+1*2+1*0.01+"1111"+"hello")
print("Ex:1\n")
print(0*(1+2.2)+1.1*2.3f+"S"+1*2+2*0.01+"1111"+"hello" == "2.52999994754791S20.021111hello")
```

### complex.expect
```
Complex Concatenation Operation
HelloWorldHello
HelloWorldHelloWorld
Contact different types in single operation
Hello2WorldtrueHello
Hello2WorldtrueHello2
Hello2WorldtrueHello22.2
Hello2WorldtrueHello22.22.5
Hello2WorldtrueHello22.22.5false
Hello2WorldtrueHello22.22.5falsea
Hello2WorldtrueHello22.22.5falseab
false
1.1S20.011111helloEx:1
false
```

## Test: complex.escape.add

### complex.escape.add.fg
```javascript
print("Complex Concatenation Operation\n")
print("Hello" + "World" + "Hello", "\n")
print("Hello" + "World" + "Hello" + "World", "\n")


print("Contact different types in single operation\n")
print("Hello" + 2 + "World" + true + "Hello", "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false, "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false + 'a', "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false + 'a' + 'b', "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false + 'a' + 'b' + "\n", "\n")
print("Hello" + 2 + "World" + true + "Hello" + 2.0 + 2.2f + 2.5 + false + 'a' + 'b' + "\n" + "\t", "\n")
```

### complex.escape.add.expect
```
Complex Concatenation Operation
HelloWorldHello
HelloWorldHelloWorld
Contact different types in single operation
Hello2WorldtrueHello
Hello2WorldtrueHello2
Hello2WorldtrueHello22.2
Hello2WorldtrueHello22.22.5
Hello2WorldtrueHello22.22.5false
Hello2WorldtrueHello22.22.5falsea
Hello2WorldtrueHello22.22.5falseab
Hello2WorldtrueHello22.22.5falseab

Hello2WorldtrueHello22.22.5falseab
```

---

# Directory: ErrModuleTests/02_features/01_ok

## Test: bring_err_null_guard

### bring_err_null_guard.fg
```javascript
bring "Err-module.fg"

fun attempt(flag: bool) -> int, Err::Result {
  if flag {
    return 7, null
  }
  return 0, Err::error("count missing", Err::CODE.NOT_FOUND)
}

var count: int, err: Err::Result = attempt(true)
println(count)
if err != null {
  println(err.toString())
} else {
  println("no error")
}

var count2: int, err2: Err::Result = attempt(false)
println(count2)
if err2 != null {
  println(err2.toString())
}
```

### bring_err_null_guard.expect
```
7
no error
0
Error: count missing
```

---

# Directory: ErrModuleTests/01_ok

## Test: bring_err_name_dynamic_multi

### bring_err_name_dynamic_multi.fg
```javascript
bring Err

fun parseStatus(flag: bool) -> str, Err::Result {
  if flag {
    return "ready", Err::ok("everything is fine")
  }
  return "", Err::error("failed", Err::CODE.INVALID_ARGUMENT, "flag was false")
}

var status: str, err: Err::Result = parseStatus(true)
println(status)
println(err.isOk())
println(err.toString())

var inferred = "plain dynamic primitive"
println(inferred)

var err2: Err::Result = Err::error("boom")
println(err2.isErr())
println(err2.hasDetails())
println(err2.withDetails("more").toString())
```

### bring_err_name_dynamic_multi.expect
```
ready
true
Error: everything is fine
"plain dynamic primitive"
true
false
Error: boom (Details: more)
```

## Test: bring_err_path_helpers

### bring_err_path_helpers.fg
```javascript
bring "Err-module.fg"

fun attempt(flag: bool) -> int, Err::Result {
  if flag {
    return 7, Err::ok("count ready")
  }
  return 0, Err::error("count missing", Err::CODE.NOT_FOUND)
}

var count: int, err: Err::Result = attempt(true)
println(count)
println(err.toString())
println(err.withMessage("checked").toString())
println(err.withCode(Err::CODE.FAILED).isErr())
println(err.clearDetails().hasDetails())
println(Err::isOk(err))
```

### bring_err_path_helpers.expect
```
7
Error: count ready
Error: count ready -> checked
true
false
true
```

---

# Directory: EdgeCaseTests

## Test: bool_zero_init

### bool_zero_init.fg
```javascript
var b:bool
println(b)
```

### bool_zero_init.expect
```
false
```

## Test: chained_index_and_member

### chained_index_and_member.fg
```javascript
type T = { vals:int[3] }
var obj:T = { vals:[10,20,30] }
println(obj.vals[0])
println(obj.vals[1])
println(obj.vals[2])
obj.vals[2] = 99
println(obj.vals)
```

### chained_index_and_member.expect
```
10
20
30
[ 10, 20, 99 ]
```

## Test: char_zero_init

### char_zero_init.fg
```javascript
var c:char
println(c)
```

### char_zero_init.expect
```

```

## Test: deci_zero_init

### deci_zero_init.fg
```javascript
var x:deci
println(x)
```

### deci_zero_init.expect
```
0
```

## Test: dyn_null_array_element

### dyn_null_array_element.fg
```javascript
var a:[3] = [0, 0, 0]
println(a)
```

### dyn_null_array_element.expect
```
[ 0, 0, 0 ]
```

## Test: empty_block_scope

### empty_block_scope.fg
```javascript
var x:int = 5
{}
println(x)
```

### empty_block_scope.expect
```
5
```

## Test: int_zero_init

### int_zero_init.fg
```javascript
var x:int
println(x)
```

### int_zero_init.expect
```
0
```

## Test: large_array_padding

### large_array_padding.fg
```javascript
var a:int[10] = [1, 2]
println(a)
```

### large_array_padding.expect
```
[ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0 ]
```

## Test: mixed_type_index_assign

### mixed_type_index_assign.fg
```javascript
var a:[4] = [1, 2, 3, 4]
a[0] = "hello"
a[1] = 3.14
a[2] = true
a[3] = 'z'
println(a)
```

### mixed_type_index_assign.expect
```
[ "hello", 3.14, true, 'z' ]
```

## Test: multiple_nested_blocks

### multiple_nested_blocks.fg
```javascript
var a:int = 1
{
    var b:int = 2
    {
        var c:int = 3
        {
            var d:int = 4
            println(a, b, c, d)
        }
        println(a, b, c)
    }
    println(a, b)
}
println(a)
```

### multiple_nested_blocks.expect
```
1234
123
12
1
```

## Test: object_array_uninitialized_field

### object_array_uninitialized_field.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
type T = { a:int, b:str }
var arr:T[2] = [{a:5}, {b:"hi"}]
println(arr)
```

## Test: reuse_var_name_after_scope

### reuse_var_name_after_scope.fg
```javascript
{
    var x:int = 1
    println(x)
}
{
    var x:str = "re-declared"
    println(x)
}
```

### reuse_var_name_after_scope.expect
```
1
re-declared
```

## Test: str_zero_init

### str_zero_init.fg
```javascript
var s:str
println(s)
```

### str_zero_init.expect
```

```

---

# Directory: 01_int

## Test: add

### add.fg
```javascript
print("Int Addition\n")
print(1 + 1, "\n")
print(1 + 2, "\n")
print(2 + 1, "\n")
print(2 + 2, "\n")
```

### add.expect
```
Int Addition
2
3
3
4
```

## Test: bitwise

### bitwise.fg
```javascript
print("Int Bitwise AND\n")
print(1 & 1, "\n")
print(1 & 2, "\n")
print(2 & 1, "\n")
print(2 & 2, "\n")

print("Int Bitwise OR\n")
print(1 | 1, "\n")
print(1 | 2, "\n")
print(2 | 1, "\n")
print(2 | 2, "\n")

print("Int Bitwise XOR\n")
print(1 ^ 1, "\n")
print(1 ^ 2, "\n")
print(2 ^ 1, "\n")
print(2 ^ 2, "\n")
```

### bitwise.expect
```
Int Bitwise AND
1
0
0
2
Int Bitwise OR
1
3
3
2
Int Bitwise XOR
0
3
3
0
```

## Test: kInvalidBinaryOperationWithTypes

### kInvalidBinaryOperationWithTypes.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(2.0 % 5)
```

## Test: other

### other.fg
```javascript
print("Int Multiplication\n")
print(1 * 1, "\n")
print(1 * 2, "\n")
print(2 * 1, "\n")
print(2 * 2, "\n")

print("Int Division\n")
print(1 // 1, "\n")
print(1 // 2, "\n")
print(2 // 1, "\n")
print(2 // 2, "\n")

print("Int Modulus\n")
print(1 % 1, "\n")
print(1 % 2, "\n")
print(2 % 1, "\n")
print(2 % 2, "\n")
```

### other.expect
```
Int Multiplication
1
2
2
4
Int Division
1
0
2
1
Int Modulus
0
1
0
0
```

## Test: sub

### sub.fg
```javascript
print("Int Subtraction\n")
print(1 - 1, "\n")
print(1 - 2, "\n")
print(2 - 1, "\n")
print(2 - 2, "\n")
```

### sub.expect
```
Int Subtraction
0
-1
1
0
```

---

# Directory: IfStatementTests/04_scope

## Test: scope_assign_both_branches_func

### scope_assign_both_branches_func.fg
```javascript
fun getA() -> int {
  return 1
}

fun getB() -> int {
  return 2
}

var x: int = 0

if (true) {
  x = getA()
} else {
  x = getB()
}
println(x)
```

### scope_assign_both_branches_func.expect
```
1
```

## Test: scope_assign_from_func_in_branch

### scope_assign_from_func_in_branch.fg
```javascript
fun getVal() -> int {
  return 100
}

var x: int = 0

if (true) {
  x = getVal()
  println(x)
} else {
  x = 200
}
println(x)
```

### scope_assign_from_func_in_branch.expect
```
100
100
```

## Test: scope_assignment_else_branch

### scope_assignment_else_branch.fg
```javascript
var x: int = 1

if (false) {
  x = 10
} else {
  x = 20
  println(x)
}
println(x)
```

### scope_assignment_else_branch.expect
```
20
20
```

## Test: scope_assignment_in_branch

### scope_assignment_in_branch.fg
```javascript
var x: int = 1

if (true) {
  x = 10
  println(x)
} else {
  x = 20
}
println(x)
```

### scope_assignment_in_branch.expect
```
10
10
```

## Test: scope_decl_from_func_in_branch

### scope_decl_from_func_in_branch.fg
```javascript
fun getVal() -> int {
  return 42
}

if (true) {
  var y: int = getVal()
  println(y)
} else {
  var y: int = 0
  println(y)
}
println("done")
```

### scope_decl_from_func_in_branch.expect
```
42
done
```

## Test: scope_decl_in_if_and_else

### scope_decl_in_if_and_else.fg
```javascript
if (true) {
  var a: int = 1
  println(a)
} else {
  var a: int = 2
  println(a)
}
println("done")
```

### scope_decl_in_if_and_else.expect
```
1
done
```

## Test: scope_declaration_in_branch

### scope_declaration_in_branch.fg
```javascript
if (true) {
  var y: int = 42
  println(y)
}
println("done")
```

### scope_declaration_in_branch.expect
```
42
done
```

## Test: scope_nested_block

### scope_nested_block.fg
```javascript
var x: int = 0

if (true) {
  var y: int = 1
  if (true) {
    var z: int = 2
    println(x, y, z)
  }
}
println("done")
```

### scope_nested_block.expect
```
012
done
```

## Test: scope_outer_var_in_inner

### scope_outer_var_in_inner.fg
```javascript
var outer: int = 42

if (true) {
  var inner: int = 10
  println(outer + inner)
}
println(outer)
```

### scope_outer_var_in_inner.expect
```
52
42
```

## Test: scope_shadow_in_branch

### scope_shadow_in_branch.fg
```javascript
var x: int = 1

if (true) {
  var x: int = 2
  println(x)
} else {
  println(x)
}
println(x)
```

### scope_shadow_in_branch.expect
```
2
1
```

---

# Directory: IfStatementTests/11_errors

## Test: body_variable_not_found

### body_variable_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
if (true) {
  println(never_declared)
}
```

## Test: condition_func_return_void

### condition_func_return_void.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
fun doSideEffect() -> nthg {
  println("x")
}

if (doSideEffect() == 1) {
  println("bad")
}
```

## Test: condition_func_return_void_implicit

### condition_func_return_void_implicit.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
fun doSideEffect() {
  println("x")
}

if (doSideEffect() == 1) {
  println("bad")
}
```

## Test: condition_function_arg_mismatch

### condition_function_arg_mismatch.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
fun check(x: int) -> bool {
  return x > 0
}
if (check(1, 2)) {
  println("x")
}
```

## Test: condition_function_not_found

### condition_function_not_found.fg
```javascript
/; EXPECT_ERROR: FunctionNotFound
if (nonexistentFunc()) {
  println("x")
}
```

## Test: condition_function_type_mismatch

### condition_function_type_mismatch.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
fun check(x: int) -> bool {
  return x > 0
}
if (check("not an int")) {
  println("x")
}
```

## Test: condition_invalid_binary_op

### condition_invalid_binary_op.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
var a: bool = true
var b: int = 1
if (a + b) {
  println("x")
}
```

## Test: condition_invalid_unary_op

### condition_invalid_unary_op.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
var arr: [int] = [1, 2, 3]
if (-arr) {
  println("x")
}
```

## Test: condition_undeclared_in_else_if

### condition_undeclared_in_else_if.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
if (false) {
  println("x")
} else if (missing_var) {
  println("y")
}
```

## Test: condition_undeclared_in_or_if

### condition_undeclared_in_or_if.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
if (true) {
  println("ok")
} or if (bad_var) {
  println("x")
}
```

## Test: condition_variable_not_found

### condition_variable_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
if (undefined_var) {
  println("x")
}
```

---

# Directory: IfStatementTests/03_conditions

## Test: condition_arithmetic_result

### condition_arithmetic_result.fg
```javascript
var a: int = 3
var b: int = 2

if (a - b) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_arithmetic_result.expect
```
nonzero
```

## Test: condition_binary_bitwise_and

### condition_binary_bitwise_and.fg
```javascript
var a: int = 5
var b: int = 3

if (a & b) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_binary_bitwise_and.expect
```
nonzero
```

## Test: condition_binary_divide

### condition_binary_divide.fg
```javascript
var a: int = 10
var b: int = 2

if (a // b > 4) {
  println("gt4")
} else {
  println("le4")
}
```

### condition_binary_divide.expect
```
gt4
```

## Test: condition_binary_eq

### condition_binary_eq.fg
```javascript
var a: int = 2
var b: int = 2

if (a == b) {
  println("equal")
} else {
  println("not equal")
}
```

### condition_binary_eq.expect
```
equal
```

## Test: condition_binary_ge

### condition_binary_ge.fg
```javascript
var a: int = 10
var b: int = 5

if (a >= b) {
  println("ge")
} else {
  println("lt")
}
```

### condition_binary_ge.expect
```
ge
```

## Test: condition_binary_gt

### condition_binary_gt.fg
```javascript
var a: int = 10
var b: int = 3

if (a > b) {
  println("greater")
} else {
  println("not greater")
}
```

### condition_binary_gt.expect
```
greater
```

## Test: condition_binary_le

### condition_binary_le.fg
```javascript
var a: int = 5
var b: int = 5

if (a <= b) {
  println("le")
} else {
  println("gt")
}
```

### condition_binary_le.expect
```
le
```

## Test: condition_binary_lt

### condition_binary_lt.fg
```javascript
var a: int = 1
var b: int = 5

if (a < b) {
  println("less")
} else {
  println("not less")
}
```

### condition_binary_lt.expect
```
less
```

## Test: condition_binary_modulo

### condition_binary_modulo.fg
```javascript
var a: int = 7
var b: int = 3

if (a % b == 1) {
  println("mod1")
} else {
  println("not mod1")
}
```

### condition_binary_modulo.expect
```
mod1
```

## Test: condition_binary_multiply

### condition_binary_multiply.fg
```javascript
var a: int = 2
var b: int = 3

if (a * b > 5) {
  println("gt5")
} else {
  println("le5")
}
```

### condition_binary_multiply.expect
```
gt5
```

## Test: condition_binary_neq

### condition_binary_neq.fg
```javascript
var a: int = 2
var b: int = 3

if (a != b) {
  println("not equal")
} else {
  println("equal")
}
```

### condition_binary_neq.expect
```
not equal
```

## Test: condition_bool

### condition_bool.fg
```javascript
var b: bool = true

if (b) {
  println("true")
} else {
  println("false")
}
```

### condition_bool.expect
```
true
```

## Test: condition_char_nonzero

### condition_char_nonzero.fg
```javascript
var c: char = 'a'

if (c) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_char_nonzero.expect
```
nonzero
```

## Test: condition_char_zero

### condition_char_zero.fg
```javascript
var c: char = '\0'

if (c) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_char_zero.expect
```
zero
```

## Test: condition_deci32_nonzero

### condition_deci32_nonzero.fg
```javascript
var d: deci32 = 3.14f

if (d) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_deci32_nonzero.expect
```
nonzero
```

## Test: condition_deci32_zero

### condition_deci32_zero.fg
```javascript
var d: deci32 = 0.0f

if (d) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_deci32_zero.expect
```
zero
```

## Test: condition_func_arithmetic_result

### condition_func_arithmetic_result.fg
```javascript
fun getA() -> int {
  return 10
}

fun getB() -> int {
  return 4
}

if (getA() - getB()) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_func_arithmetic_result.expect
```
nonzero
```

## Test: condition_func_return_bool_not

### condition_func_return_bool_not.fg
```javascript
fun isZero(x: int) -> bool {
  return x == 0
}

if (!isZero(5)) {
  println("not zero")
} else {
  println("zero")
}
```

### condition_func_return_bool_not.expect
```
not zero
```

## Test: condition_func_return_char

### condition_func_return_char.fg
```javascript
fun getChar() -> char {
  return 'x'
}

if (getChar()) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_func_return_char.expect
```
nonzero
```

## Test: condition_func_return_deci

### condition_func_return_deci.fg
```javascript
fun getDeci() -> deci {
  return 3.14
}

if (getDeci()) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_func_return_deci.expect
```
nonzero
```

## Test: condition_func_return_eq

### condition_func_return_eq.fg
```javascript
fun getVal() -> int {
  return 42
}

if (getVal() == 42) {
  println("match")
} else {
  println("no match")
}
```

### condition_func_return_eq.expect
```
match
```

## Test: condition_func_return_int_binary

### condition_func_return_int_binary.fg
```javascript
fun getA() -> int {
  return 5
}

fun getB() -> int {
  return 3
}

if (getA() > getB()) {
  println("a gt b")
} else {
  println("a le b")
}
```

### condition_func_return_int_binary.expect
```
a gt b
```

## Test: condition_func_return_str

### condition_func_return_str.fg
```javascript
fun getStr() -> str {
  return "hello"
}

if (getStr()) {
  println("nonempty")
} else {
  println("empty")
}
```

### condition_func_return_str.expect
```
nonempty
```

## Test: condition_func_return_value_implicit

### condition_func_return_value_implicit.fg
```javascript
fun doSideEffect() {
  println("x")
  return 1
}

if (doSideEffect() == 1) {
  println("match")
} else {
  println("no match")
}
```

### condition_func_return_value_implicit.expect
```
x
match
```

## Test: condition_function_call

### condition_function_call.fg
```javascript
fun isEven(n: int) -> bool {
  return n == 2
}

if (isEven(2)) {
  println("even")
} else {
  println("odd")
}
```

### condition_function_call.expect
```
even
```

## Test: condition_function_returns_bool

### condition_function_returns_bool.fg
```javascript
fun check(x: int) -> bool {
  return x > 0
}

if (check(5)) {
  println("positive")
} else {
  println("non-positive")
}
```

### condition_function_returns_bool.expect
```
positive
```

## Test: condition_int32_nonzero

### condition_int32_nonzero.fg
```javascript
var x: int = 42

if (x) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_int32_nonzero.expect
```
nonzero
```

## Test: condition_int64_nonzero

### condition_int64_nonzero.fg
```javascript
var x: int64 = 100

if (x) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_int64_nonzero.expect
```
nonzero
```

## Test: condition_int8_nonzero

### condition_int8_nonzero.fg
```javascript
var x: int8 = 5

if (x) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_int8_nonzero.expect
```
nonzero
```

## Test: condition_int8_zero

### condition_int8_zero.fg
```javascript
var x: int8 = 0

if (x) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_int8_zero.expect
```
zero
```

## Test: condition_int_nonzero

### condition_int_nonzero.fg
```javascript
var n: int = 5

if (n) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_int_nonzero.expect
```
nonzero
```

## Test: condition_int_zero

### condition_int_zero.fg
```javascript
var n: int = 0

if (n) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_int_zero.expect
```
zero
```

## Test: condition_logical_and

### condition_logical_and.fg
```javascript
var a: bool = true
var b: bool = true

if (a && b) {
  println("both true")
} else {
  println("not both")
}
```

### condition_logical_and.expect
```
both true
```

## Test: condition_logical_or

### condition_logical_or.fg
```javascript
var a: bool = false
var b: bool = true

if (a || b) {
  println("or true")
} else {
  println("or false")
}
```

### condition_logical_or.expect
```
or true
```

## Test: condition_nested_logical

### condition_nested_logical.fg
```javascript
var a: bool = true
var b: bool = false
var c: bool = true

if (a && (b || c)) {
  println("true")
} else {
  println("false")
}
```

### condition_nested_logical.expect
```
true
```

## Test: condition_string_empty

### condition_string_empty.fg
```javascript
var s: str = ""

if (s) {
  println("nonempty")
} else {
  println("empty")
}
```

### condition_string_empty.expect
```
empty
```

## Test: condition_string_nonempty

### condition_string_nonempty.fg
```javascript
var s: str = "hello"

if (s) {
  println("nonempty")
} else {
  println("empty")
}
```

### condition_string_nonempty.expect
```
nonempty
```

## Test: condition_unary_negate

### condition_unary_negate.fg
```javascript
var x: int = 5

if (-x < 0) {
  println("negative")
} else {
  println("non-negative")
}
```

### condition_unary_negate.expect
```
negative
```

## Test: condition_unary_not

### condition_unary_not.fg
```javascript
var a: bool = false

if (!a) {
  println("not false")
} else {
  println("not true")
}
```

### condition_unary_not.expect
```
not false
```

## Test: condition_unary_plus

### condition_unary_plus.fg
```javascript
var x: int = 1

if (+x > 0) {
  println("positive")
} else {
  println("non-positive")
}
```

### condition_unary_plus.expect
```
positive
```

## Test: condition_unary_tilde

### condition_unary_tilde.fg
```javascript
var x: int = 0

if (~x) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_unary_tilde.expect
```
nonzero
```

---

# Directory: IfStatementTests/07_edge_cases

## Test: condition_all_false_or_if

### condition_all_false_or_if.fg
```javascript
if (false) {
  println(1)
} or if (false) {
  println(2)
} or if (false) {
  println(3)
} else {
  println("else")
}
```

### condition_all_false_or_if.expect
```
else
```

## Test: condition_chained_and_or

### condition_chained_and_or.fg
```javascript
var a: bool = true
var b: bool = false
var c: bool = true
var d: bool = false

if (a && b || c && !d) {
  println("true")
} else {
  println("false")
}
```

### condition_chained_and_or.expect
```
true
```

## Test: condition_deci

### condition_deci.fg
```javascript
var d: deci = 3.14

if (d) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_deci.expect
```
nonzero
```

## Test: condition_deci_eq_zero

### condition_deci_eq_zero.fg
```javascript
var d: deci = 0.0

if (d == 0.0) {
  println("zero")
} else {
  println("nonzero")
}
```

### condition_deci_eq_zero.expect
```
zero
```

## Test: condition_deci_small

### condition_deci_small.fg
```javascript
var d: deci = 0.000001

if (d) {
  println("nonzero")
} else {
  println("zero")
}
```

### condition_deci_small.expect
```
nonzero
```

## Test: condition_int_negative

### condition_int_negative.fg
```javascript
var x: int = -1

if (x) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_int_negative.expect
```
truthy
```

## Test: condition_nir

### condition_nir.fg
```javascript
var n = null

if (n) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_nir.expect
```
falsy
```

## Test: condition_str_neq_empty

### condition_str_neq_empty.fg
```javascript
fun getStr() -> str {
  return "x"
}

if (getStr() != "") {
  println("nonempty")
} else {
  println("empty")
}
```

### condition_str_neq_empty.expect
```
nonempty
```

## Test: empty_else_block

### empty_else_block.fg
```javascript
if (false) {
  println("if")
} else {
}
println("after")
```

### empty_else_block.expect
```
after
```

## Test: empty_if_block

### empty_if_block.fg
```javascript
if (true) {
}
println("after")
```

### empty_if_block.expect
```
after
```

## Test: if_without_else

### if_without_else.fg
```javascript
var a: int = 2

if (a == 2) {
  println("match")
}
println("after")
```

### if_without_else.expect
```
match
after
```

## Test: only_else

### only_else.fg
```javascript
if (false) {
  println("if")
} else {
  println("else")
}
```

### only_else.expect
```
else
```

---

# Directory: IfStatementTests/01_basic

## Test: else_if

### else_if.fg
```javascript
var a: int = 3

if (a == 2) {
  println("a is 2")
} else if (a == 3) {
  println("a is 3")
} else {
  println("a is other")
}
```

### else_if.expect
```
a is 3
```

## Test: else_if_else_branch

### else_if_else_branch.fg
```javascript
var a: int = 5

if (a == 2) {
  println("a is 2")
} else if (a == 3) {
  println("a is 3")
} else {
  println("a is other")
}
```

### else_if_else_branch.expect
```
a is other
```

## Test: if_else

### if_else.fg
```javascript
var a: int = 2

if (a == 2) {
  println("a is 2")
} else {
  println("a is not 2")
}
```

### if_else.expect
```
a is 2
```

## Test: if_else_false_branch

### if_else_false_branch.fg
```javascript
var a: int = 3

if (a == 2) {
  println("a is 2")
} else {
  println("a is not 2")
}
```

### if_else_false_branch.expect
```
a is not 2
```

## Test: simple_if_false

### simple_if_false.fg
```javascript
if (false) {
  println("yes")
}
println("after")
```

### simple_if_false.expect
```
after
```

## Test: simple_if_true

### simple_if_true.fg
```javascript
if (true) {
  println("yes")
}
```

### simple_if_true.expect
```
yes
```

---

# Directory: IfStatementTests/08_object

## Test: condition_func_return_complex_object

### condition_func_return_complex_object.fg
```javascript
type Point = {
  x: int
  y: int
}

type Rectangle = {
  topLeft: Point
  bottomRight: Point
}

fun getShape() -> Rectangle {
  return {
    topLeft: { x: 0, y: 0 },
    bottomRight: { x: 100, y: 100 }
  }
}

if (getShape()) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_func_return_complex_object.expect
```
nonnull
```

## Test: condition_func_return_complex_object_nested_access

### condition_func_return_complex_object_nested_access.fg
```javascript
type Point = {
  x: int
  y: int
}

type Rectangle = {
  topLeft: Point
  bottomRight: Point
}

fun getShape() -> Rectangle {
  return {
    topLeft: { x: 0, y: 0 },
    bottomRight: { x: 100, y: 100 }
  }
}

if (getShape().topLeft.x == 0) {
  println("topleft_x_0")
} else {
  println("topleft_x_ne_0")
}

if (getShape().bottomRight.y > 50) {
  println("bottomright_y_gt_50")
} else {
  println("bottomright_y_le_50")
}
```

### condition_func_return_complex_object_nested_access.expect
```
topleft_x_0
bottomright_y_gt_50
```

## Test: condition_func_return_object

### condition_func_return_object.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoint() -> Point {
  return { x: 1, y: 2 }
}

if (getPoint()) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_func_return_object.expect
```
nonnull
```

## Test: condition_func_return_object_member_access

### condition_func_return_object_member_access.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoint() -> Point {
  return { x: 5, y: 10 }
}

if (getPoint().x > 3) {
  println("x_gt_3")
} else {
  println("x_le_3")
}

if (getPoint().y == 10) {
  println("y_eq_10")
} else {
  println("y_ne_10")
}
```

### condition_func_return_object_member_access.expect
```
x_gt_3
y_eq_10
```

## Test: condition_func_return_triple_nested_member_access

### condition_func_return_triple_nested_member_access.fg
```javascript
type Point = {
  x: int
  y: int
}

type Rectangle = {
  topLeft: Point
  bottomRight: Point
}

type Shape = {
  name: str
  rect: Rectangle
}

fun getShape() -> Shape {
  return {
    name: "box",
    rect: {
      topLeft: { x: 0, y: 0 },
      bottomRight: { x: 10, y: 20 }
    }
  }
}

if (getShape().rect.topLeft.x == 0) {
  println("nested_x_0")
} else {
  println("nested_x_ne_0")
}

if (getShape().rect.bottomRight.y == 20) {
  println("nested_y_20")
} else {
  println("nested_y_ne_20")
}
```

### condition_func_return_triple_nested_member_access.expect
```
nested_x_0
nested_y_20
```

## Test: condition_object_nonnull

### condition_object_nonnull.fg
```javascript
type Point = {
  x: int
  y: int
}

var p: Point = { x: 1, y: 2 }

if (p) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_object_nonnull.expect
```
nonnull
```

## Test: condition_object_null

### condition_object_null.fg
```javascript
type Point = {
  x: int
  y: int
}

var p: Point = null

if (p) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_object_null.expect
```
null
```

## Test: condition_object_uninitialized

### condition_object_uninitialized.fg
```javascript
type Point = {
  x: int
  y: int
}

var p: Point

if (p) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_object_uninitialized.expect
```
nonnull
```

## Test: object_nested_in_if

### object_nested_in_if.fg
```javascript
type Inner = { v: int }
type Outer = { inner: Inner }

var o: Outer = { inner: { v: 42 } }

if (o) {
  if (o.inner) {
    println("both")
  } else {
    println("outer only")
  }
} else {
  println("neither")
}
```

### object_nested_in_if.expect
```
both
```

## Test: object_or_if

### object_or_if.fg
```javascript
type T = { x: int }

var a: T = null
var b: T = { x: 1 }

if (a) {
  println("a")
} or if (b) {
  println("b")
} else {
  println("both null")
}
```

### object_or_if.expect
```
b
```

---

# Directory: IfStatementTests/10_dynamic_edge

## Test: condition_dynamic_bool_false

### condition_dynamic_bool_false.fg
```javascript
var d = false

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_bool_false.expect
```
falsy
```

## Test: condition_dynamic_deci_nonzero

### condition_dynamic_deci_nonzero.fg
```javascript
var d = 3.14

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_deci_nonzero.expect
```
truthy
```

## Test: condition_dynamic_deci_zero

### condition_dynamic_deci_zero.fg
```javascript
var d = 0.0

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_deci_zero.expect
```
falsy
```

## Test: condition_dynamic_from_function

### condition_dynamic_from_function.fg
```javascript
fun getVal() {
  return 10
}

if (getVal()) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_from_function.expect
```
truthy
```

## Test: condition_dynamic_string_empty

### condition_dynamic_string_empty.fg
```javascript
var d = ""

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_string_empty.expect
```
falsy
```

## Test: condition_dynamic_string_nonempty

### condition_dynamic_string_nonempty.fg
```javascript
var d = "hello"

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_string_nonempty.expect
```
truthy
```

## Test: dynamic_or_if

### dynamic_or_if.fg
```javascript
var a = 0
var b = 0.0
var c = 42

if (a) {
  println("a")
} or if (b) {
  println("b")
} or if (c) {
  println("c")
} else {
  println("all falsy")
}
```

### dynamic_or_if.expect
```
c
```

---

# Directory: IfStatementTests/05_complex

## Test: assignment_in_branch

### assignment_in_branch.fg
```javascript
var x: int = 1

if (true) {
  x = 10
  println(x)
} else {
  x = 20
}
println(x)
```

### assignment_in_branch.expect
```
10
10
```

## Test: assignment_in_else_if

### assignment_in_else_if.fg
```javascript
var x: int = 1

if (x == 2) {
  x = 10
  println(x)
} else if (x == 1) {
  x = 20
  println(x)
} else {
  x = 30
}
println(x)
```

### assignment_in_else_if.expect
```
20
20
```

## Test: deeply_nested_if

### deeply_nested_if.fg
```javascript
var a: int = 1
var b: int = 2
var c: int = 3

if (a == 1) {
  if (b == 2) {
    if (c == 3) {
      println("all match")
    } else {
      println("c no match")
    }
  } else {
    println("b no match")
  }
} else {
  println("a no match")
}
```

### deeply_nested_if.expect
```
all match
```

## Test: func_call_in_nested_condition

### func_call_in_nested_condition.fg
```javascript
fun isPos(x: int) -> bool {
  return x > 0
}

fun getVal() -> int {
  return 7
}

if (isPos(getVal())) {
  if (getVal() > 5) {
    println("pos and gt5")
  } else {
    println("pos and le5")
  }
} else {
  println("non-pos")
}
```

### func_call_in_nested_condition.expect
```
pos and gt5
```

## Test: func_multi_return_in_condition

### func_multi_return_in_condition.fg
```javascript
fun getPair() -> int, int {
  return 5, 10
}

var a: int, b: int = getPair()

if (a < b) {
  println("a lt b")
} else {
  println("a ge b")
}
```

### func_multi_return_in_condition.expect
```
a lt b
```

## Test: func_return_in_else_if

### func_return_in_else_if.fg
```javascript
fun getVal() -> int {
  return 3
}

if (getVal() == 1) {
  println("one")
} else if (getVal() == 2) {
  println("two")
} else if (getVal() == 3) {
  println("three")
} else {
  println("other")
}
```

### func_return_in_else_if.expect
```
three
```

## Test: func_return_in_or_if

### func_return_in_or_if.fg
```javascript
fun getVal() -> int {
  return 2
}

if (getVal() == 1) {
  println("one")
} or if (getVal() == 2) {
  println("two")
} or if (getVal() == 3) {
  println("three")
} else {
  println("other")
}
```

### func_return_in_or_if.expect
```
two
```

## Test: if_else_if_or_if_else

### if_else_if_or_if_else.fg
```javascript
var x: int = 3

if (x == 1) {
  println("one")
} or if (x == 2) {
  println("two")
} or if (x == 3) {
  println("three")
} else {
  println("other")
}
```

### if_else_if_or_if_else.expect
```
three
```

## Test: nested_else_if

### nested_else_if.fg
```javascript
var x: int = 3

if (x == 1) {
  println("one")
} else if (x == 2) {
  println("two")
} else if (x == 3) {
  println("three")
} else {
  println("other")
}
```

### nested_else_if.expect
```
three
```

## Test: nested_if

### nested_if.fg
```javascript
var a: int = 2
var b: int = 3

if (a == 2) {
  if (b == 3) {
    println("both")
  } else {
    println("a only")
  }
} else {
  println("neither")
}
```

### nested_if.expect
```
both
```

## Test: nested_or_if

### nested_or_if.fg
```javascript
if (false) {
  println(1)
} or if (true) {
  if (2 > 3) {
    println(2)
  } else {
    println(3)
  }
} else {
  println(4)
}
```

### nested_or_if.expect
```
3
```

## Test: scope_nested_assign_func

### scope_nested_assign_func.fg
```javascript
fun getOuter() -> int {
  return 10
}

fun getInner() -> int {
  return 5
}

var x: int = 0

if (true) {
  x = getOuter()
  if (x > 5) {
    var y: int = getInner()
    println(x, y)
  }
}
println(x)
```

### scope_nested_assign_func.expect
```
105
10
```

---

# Directory: IfStatementTests/06_dynamic

## Test: condition_dynamic_binary_op

### condition_dynamic_binary_op.fg
```javascript
fun getA() {
  return 5
}

fun getB() {
  return 3
}

if (getA() > getB()) {
  println("a gt b")
} else {
  println("a le b")
}
```

### condition_dynamic_binary_op.expect
```
a gt b
```

## Test: condition_dynamic_from_func_then_assign

### condition_dynamic_from_func_then_assign.fg
```javascript
fun getDynamic() {
  return 99
}

var x = getDynamic()

if (x) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_from_func_then_assign.expect
```
truthy
```

## Test: condition_dynamic_true

### condition_dynamic_true.fg
```javascript
var d = 42

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_true.expect
```
truthy
```

## Test: condition_dynamic_zero

### condition_dynamic_zero.fg
```javascript
var d = 0

if (d) {
  println("truthy")
} else {
  println("falsy")
}
```

### condition_dynamic_zero.expect
```
falsy
```

---

# Directory: IfStatementTests/09_array

## Test: array_in_or_if

### array_in_or_if.fg
```javascript
var a: int[1] = [1]
var b: int[1] = [2]

if (a) {
  println("a")
} or if (b) {
  println("b")
} else {
  println("both null")
}
```

### array_in_or_if.expect
```
a
```

## Test: condition_array_nonempty

### condition_array_nonempty.fg
```javascript
var a: int[3] = [1, 2, 3]

if (a) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_array_nonempty.expect
```
nonnull
```

## Test: condition_array_uninitialized

### condition_array_uninitialized.fg
```javascript
var a: int[2]

if (a) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_array_uninitialized.expect
```
nonnull
```

## Test: condition_func_return_array

### condition_func_return_array.fg
```javascript
fun getArray() -> int[3] {
  return [1, 2, 3]
}

if (getArray()) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_func_return_array.expect
```
nonnull
```

## Test: condition_func_return_array_index

### condition_func_return_array_index.fg
```javascript
fun getArray() -> int[3] {
  return [1, 2, 3]
}

if (getArray()[0] == 1) {
  println("idx0_eq_1")
} else {
  println("idx0_ne_1")
}

if (getArray()[2] > 2) {
  println("idx2_gt_2")
} else {
  println("idx2_le_2")
}
```

### condition_func_return_array_index.expect
```
idx0_eq_1
idx2_gt_2
```

## Test: condition_func_return_array_of_objects

### condition_func_return_array_of_objects.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoints() -> Point[2] {
  return [{ x: 1, y: 2 }, { x: 3, y: 4 }]
}

if (getPoints()) {
  println("nonnull")
} else {
  println("null")
}
```

### condition_func_return_array_of_objects.expect
```
nonnull
```

## Test: condition_func_return_array_of_objects_member_access

### condition_func_return_array_of_objects_member_access.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoints() -> Point[2] {
  return [{ x: 1, y: 2 }, { x: 3, y: 4 }]
}

if (getPoints()[0].x == 1) {
  println("p0_x_eq_1")
} else {
  println("p0_x_ne_1")
}

if (getPoints()[1].y > 3) {
  println("p1_y_gt_3")
} else {
  println("p1_y_le_3")
}
```

### condition_func_return_array_of_objects_member_access.expect
```
p0_x_eq_1
p1_y_gt_3
```

---

# Directory: IfStatementTests/02_or_if

## Test: or_if_else_branch

### or_if_else_branch.fg
```javascript
if (false) {
  println(4)
} or if (false) {
  println(5)
} else {
  println(6)
}
```

### or_if_else_branch.expect
```
6
```

## Test: or_if_first_true

### or_if_first_true.fg
```javascript
if (false) {
  println(4)
} or if (true) {
  println(5)
} else {
  println(6)
}
```

### or_if_first_true.expect
```
5
```

## Test: or_if_multiple

### or_if_multiple.fg
```javascript
if (false) {
  println(4)
} or if (false) {
  println(5)
} or if (true) {
  println(6)
} else {
  println(7)
}
```

### or_if_multiple.expect
```
6
```

## Test: or_if_second_true

### or_if_second_true.fg
```javascript
var a: int = 3

if (a == 2) {
  println("a is 2")
} or if (a == 3) {
  println("a is 3")
} else {
  println("a is other")
}
```

### or_if_second_true.expect
```
a is 3
```

---

# Directory: TernaryTests/05_errors

## Test: incompatible_types

### incompatible_types.fg
```javascript
/; EXPECT_ERROR: IncompatibleTypesForTernaryExpression
var x: int = true ? 1 : "bad"

println(x)
```

## Test: void_ternary_as_function_arg

### void_ternary_as_function_arg.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
fun printA() {
  println("A")
}
fun printB() {
  println("B")
}
fun takeInt(x: int) {
  println(x)
}

var a = 'A'
takeInt((a == 'B') ? printA() : printB())
```

## Test: void_ternary_assigned_to_var

### void_ternary_assigned_to_var.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
fun printA() {
  println("A")
}
fun printB() {
  println("B")
}

var a = 'A'
var x = (a == 'B') ? printA() : printB()
println(x)
```

## Test: void_ternary_in_assignment

### void_ternary_in_assignment.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
fun printA() {
  println("A")
}
fun printB() {
  println("B")
}

var a = 'A'
var x: int = 0
x = (a == 'B') ? printA() : printB()
println(x)
```

---

# Directory: TernaryTests/07_edge_cases

## Test: condition_chained_and_or

### condition_chained_and_or.fg
```javascript
var a: bool = true
var b: bool = false
var c: bool = true
var d: bool = false

println((a && b || c && !d) ? "true" : "false")
```

### condition_chained_and_or.expect
```
true
```

## Test: condition_deci_small

### condition_deci_small.fg
```javascript
var d: deci = 0.000001

println(d ? "nonzero" : "zero")
```

### condition_deci_small.expect
```
nonzero
```

## Test: condition_int_negative

### condition_int_negative.fg
```javascript
var x: int = -1

println(x ? "truthy" : "falsy")
```

### condition_int_negative.expect
```
truthy
```

## Test: condition_nir

### condition_nir.fg
```javascript
var n = null

println(n ? "truthy" : "falsy")
```

### condition_nir.expect
```
falsy
```

## Test: condition_str_neq_empty

### condition_str_neq_empty.fg
```javascript
fun getStr() -> str {
  return "x"
}

println((getStr() != "") ? "nonempty" : "empty")
```

### condition_str_neq_empty.expect
```
nonempty
```

## Test: nested_ternary

### nested_ternary.fg
```javascript
var a: bool = true
var b: bool = false

println(a ? (b ? "a-t-b-t" : "a-t-b-f") : (b ? "a-f-b-t" : "a-f-b-f"))
```

### nested_ternary.expect
```
a-t-b-f
```

## Test: ternary_as_function_arg

### ternary_as_function_arg.fg
```javascript
fun show(s: str) {
  println(s)
}

show(true ? "a" : "b")
show(false ? "a" : "b")
```

### ternary_as_function_arg.expect
```
a
b
```

---

# Directory: TernaryTests/03_var_decl_assignment

## Test: var_assignment

### var_assignment.fg
```javascript
var x: str = true ? "Hello" : "Bye"
var y: str = false ? "Hello" : "Bye"

x = "Hello"
y = (1 == 1) ? "Hello" : "Bye"

println(x)
println(y)
```

### var_assignment.expect
```
Hello
Hello
```

## Test: var_dec

### var_dec.fg
```javascript
var x: str = true ? "Hello" : "Bye"
var y: str = false ? "Hello" : "Bye"

println(x)
println(y)
```

### var_dec.expect
```
Hello
Bye
```

---

# Directory: TernaryTests/04_func_return

## Test: calling_function_returning_array

### calling_function_returning_array.fg
```javascript
fun getArr() -> int[2] {
  return [10, 20]
}

fun getZero() -> int[2] {
  var z: int[2] = [0, 0]
  return z
}

var a: int[2] = true ? getArr() : getZero()

println(a[0])
println(a[1])
```

### calling_function_returning_array.expect
```
10
20
```

## Test: calling_function_returning_int

### calling_function_returning_int.fg
```javascript
fun printA() -> int {
  return 2
}

fun printB() -> int {
  return 3
}

var g: int = 3
var x: int = (g == 2) ? printA() : printB()

println(x)
```

### calling_function_returning_int.expect
```
3
```

## Test: calling_function_returning_int_no_assign

### calling_function_returning_int_no_assign.fg
```javascript
fun printA() -> int {
  println("A")
  return 2
}

fun printB() -> int {
  println("B")
  return 3
}

var g: int = 3
(g == 2) ? printA() : printB()
```

### calling_function_returning_int_no_assign.expect
```
B
```

## Test: calling_function_returning_object

### calling_function_returning_object.fg
```javascript
type B = {
  s: int
}

fun printA() -> B {
  println("A")
  return {s: 0}
}

fun printB() -> B {
  println("B")
  return {s: 2}
}

var g: int = 2
var x: B = (g == 2) ? printA() : printB()

println(x)
```

### calling_function_returning_object.expect
```
A
{ s: 0 }
```

---

# Directory: TernaryTests/01_basic

## Test: basic_print_truthy

### basic_print_truthy.fg
```javascript
println(true ? "Hello" : "Bye")
println(false ? "Hello" : "Bye")
println("Hello" ? "Hello" : "Bye")
println("Bye" ? "Hello" : "Bye")
println(1 ? "Hello" : "Bye")
println(0 ? "Hello" : "Bye")
println(1.5 ? "Hello" : "Bye")
println(0.5 ? "Hello" : "Bye")
println(0.0 ? "Hello" : "Bye")
println(1.0 ? "Hello" : "Bye")
```

### basic_print_truthy.expect
```
Hello
Bye
Hello
Hello
Hello
Bye
Hello
Hello
Bye
Hello
```

## Test: ternary_basic

### ternary_basic.fg
```javascript
var a: int = 2

println(a == 2 ? "yes" : "no")
```

### ternary_basic.expect
```
yes
```

## Test: ternary_else_branch

### ternary_else_branch.fg
```javascript
println(false ? "a" : "b")
```

### ternary_else_branch.expect
```
b
```

## Test: ternary_int_result

### ternary_int_result.fg
```javascript
var x: int = true ? 1 : 0

println(x)
```

### ternary_int_result.expect
```
1
```

## Test: ternary_void_branches

### ternary_void_branches.fg
```javascript
fun printA() {
  println("A")
}
fun printB() {
  println("B")
}

var a = 'A'
a == 'B' ? printA() : printB()
```

### ternary_void_branches.expect
```
B
```

---

# Directory: TernaryTests/08_object

## Test: condition_func_return_object_member_access

### condition_func_return_object_member_access.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoint() -> Point {
  return { x: 5, y: 10 }
}

println((getPoint().x > 3) ? "x_gt_3" : "x_le_3")
println((getPoint().y == 10) ? "y_eq_10" : "y_ne_10")
```

### condition_func_return_object_member_access.expect
```
x_gt_3
y_eq_10
```

## Test: ternary_result_object_member_access

### ternary_result_object_member_access.fg
```javascript
type T = {
  v: int
}

fun makeT(x: int) -> T {
  return { v: x }
}

var a: T = (true ? makeT(1) : makeT(2))

println(a.v)
```

### ternary_result_object_member_access.expect
```
1
```

---

# Directory: TernaryTests/02_conditions

## Test: binary_operators_int

### binary_operators_int.fg
```javascript
println((1 > 2) ? "Hello" : "Bye")
println((1 < 2) ? "Hello" : "Bye")
println((1 == 2) ? "Hello" : "Bye")
println((1 != 2) ? "Hello" : "Bye")
println((1 >= 2) ? "Hello" : "Bye")
println((1 <= 2) ? "Hello" : "Bye")
```

### binary_operators_int.expect
```
Bye
Hello
Bye
Hello
Bye
Hello
```

## Test: binary_operators_other_types

### binary_operators_other_types.fg
```javascript
println((1 > 2) ? "Hello" : "Bye")
println(("Hl" == "hl") ? "Hello" : "Bye")
println(("Hl" == "Hl") ? "Hello" : "Bye")
println((2.2 == 2.2) ? "Hello" : "Bye")
println((2.2 != 2.2) ? "Hello" : "Bye")
println((false == false) ? "Hello" : "Bye")
println((false == true) ? "Hello" : "Bye")
```

### binary_operators_other_types.expect
```
Bye
Bye
Hello
Hello
Bye
Hello
Bye
```

## Test: condition_arithmetic_result

### condition_arithmetic_result.fg
```javascript
var a: int = 3
var b: int = 2

println((a - b) ? "nonzero" : "zero")
```

### condition_arithmetic_result.expect
```
nonzero
```

## Test: condition_bool

### condition_bool.fg
```javascript
var b: bool = true

println(b ? "t" : "f")
```

### condition_bool.expect
```
t
```

## Test: condition_char_nonzero

### condition_char_nonzero.fg
```javascript
var c: char = 'a'

println(c ? "nonzero" : "zero")
```

### condition_char_nonzero.expect
```
nonzero
```

## Test: condition_char_zero

### condition_char_zero.fg
```javascript
var c: char = '\0'

println(c ? "nonzero" : "zero")
```

### condition_char_zero.expect
```
zero
```

## Test: condition_func_return_str

### condition_func_return_str.fg
```javascript
fun getStr() -> str {
  return "hello"
}

println(getStr() ? "nonempty" : "empty")
```

### condition_func_return_str.expect
```
nonempty
```

## Test: condition_int8_nonzero

### condition_int8_nonzero.fg
```javascript
var x: int8 = 5

println(x ? "nonzero" : "zero")
```

### condition_int8_nonzero.expect
```
nonzero
```

## Test: condition_int_nonzero

### condition_int_nonzero.fg
```javascript
var n: int = 5

println(n != 0 ? "nonzero" : "zero")
```

### condition_int_nonzero.expect
```
nonzero
```

## Test: condition_int_zero

### condition_int_zero.fg
```javascript
var n: int = 0

println(n ? "nonzero" : "zero")
```

### condition_int_zero.expect
```
zero
```

## Test: condition_logical_and

### condition_logical_and.fg
```javascript
var a: bool = true
var b: bool = true

println((a && b) ? "both true" : "not both")
```

### condition_logical_and.expect
```
both true
```

## Test: condition_logical_or

### condition_logical_or.fg
```javascript
var a: bool = false
var b: bool = true

println((a || b) ? "or true" : "or false")
```

### condition_logical_or.expect
```
or true
```

## Test: condition_nested_logical

### condition_nested_logical.fg
```javascript
var a: bool = true
var b: bool = false
var c: bool = true

println((a && (b || c)) ? "true" : "false")
```

### condition_nested_logical.expect
```
true
```

## Test: condition_string_empty

### condition_string_empty.fg
```javascript
var s: str = ""

println(s ? "nonempty" : "empty")
```

### condition_string_empty.expect
```
empty
```

## Test: condition_string_nonempty

### condition_string_nonempty.fg
```javascript
var s: str = "hello"

println(s ? "nonempty" : "empty")
```

### condition_string_nonempty.expect
```
nonempty
```

## Test: condition_unary_not

### condition_unary_not.fg
```javascript
var a: bool = false

println((!a) ? "not false" : "not true")
```

### condition_unary_not.expect
```
not false
```

---

# Directory: TernaryTests/10_scope

## Test: global_var_in_ternary

### global_var_in_ternary.fg
```javascript
var global: int = 5

println(global > 0 ? "positive" : "non-positive")

var g2: bool = true

println(g2 ? "yes" : "no")
```

### global_var_in_ternary.expect
```
positive
yes
```

## Test: local_var_in_ternary

### local_var_in_ternary.fg
```javascript
fun f() {
  var local: int = 3
  println(local == 3 ? "eq" : "ne")
}

f()
```

### local_var_in_ternary.expect
```
eq
```

## Test: mixed_global_and_local_ternary

### mixed_global_and_local_ternary.fg
```javascript
var g: int = 10

fun useBoth() {
  var local: int = 2
  println(g > local ? "g_gt" : "g_le")
  println((g == 10 && local == 2) ? "match" : "nomatch")
}

useBoth()
```

### mixed_global_and_local_ternary.expect
```
g_gt
match
```

---

# Directory: TernaryTests/06_dynamic

## Test: condition_dynamic_true

### condition_dynamic_true.fg
```javascript
var d = 42

println(d ? "truthy" : "falsy")
```

### condition_dynamic_true.expect
```
truthy
```

## Test: condition_dynamic_zero

### condition_dynamic_zero.fg
```javascript
var d = 0

println(d ? "truthy" : "falsy")
```

### condition_dynamic_zero.expect
```
falsy
```

## Test: dynamic_return_from_func_condition

### dynamic_return_from_func_condition.fg
```javascript
fun getDynamic() {
  return 99
}

var x = getDynamic() ? "truthy" : "falsy"

println(x)
```

### dynamic_return_from_func_condition.expect
```
"truthy"
```

## Test: dynamic_return_from_func_result

### dynamic_return_from_func_result.fg
```javascript
fun getDynamic() {
  return 42
}

var x = true ? getDynamic() : 0

println(x)
```

### dynamic_return_from_func_result.expect
```
42
```

## Test: dynamic_ternary_mixed_types_else

### dynamic_ternary_mixed_types_else.fg
```javascript
var x = false ? 1 : "bad"

println(x)
```

### dynamic_ternary_mixed_types_else.expect
```
"bad"
```

## Test: dynamic_ternary_mixed_types_then

### dynamic_ternary_mixed_types_then.fg
```javascript
var x = true ? 1 : "bad"

println(x)
```

### dynamic_ternary_mixed_types_then.expect
```
1
```

---

# Directory: TernaryTests/09_array

## Test: condition_array_nonempty

### condition_array_nonempty.fg
```javascript
var a: int[3] = [1, 2, 3]

println(a ? "nonnull" : "null")
```

### condition_array_nonempty.expect
```
nonnull
```

## Test: condition_array_uninitialized

### condition_array_uninitialized.fg
```javascript
var a: int[2]

println(a ? "nonnull" : "null")
```

### condition_array_uninitialized.expect
```
nonnull
```

## Test: ternary_result_array

### ternary_result_array.fg
```javascript
var a: int[2] = true ? [1, 2] : [3, 4]

println(a[0])
println(a[1])

var b: int[2] = false ? [1, 2] : [3, 4]

println(b[0])
println(b[1])
```

### ternary_result_array.expect
```
1
2
3
4
```

---

# Directory: 01_bool

## Test: equality

### equality.fg
```javascript
print("Boolean Equality\n")
print(true == true, "\n")
print(true == false, "\n")
print(false == true, "\n")
print(false == false, "\n")

print("Decimal Equality\n")
print(1.0 == 1.0, "\n")
print(1.0 == 2.0, "\n")
print(2.0 == 1.0, "\n")
print(2.0 == 2.0, "\n")

print("Nir Equality\n")
print(null == null, "\n")

print("Int32 Equality\n")
print(2 == 2, "\n")

print("String Equality\n")
print("Hello" == "Hello", "\n")
print("Hello" == "World", "\n")
print("World" == "Hello", "\n")
print("World" == "World", "\n")

print("Character Equality\n")
print('a' == 'a', "\n")
print('a' == 'b', "\n")
print('b' == 'a', "\n")
print('b' == 'b', "\n")
```

### equality.expect
```
Boolean Equality
true
false
false
true
Decimal Equality
true
false
false
true
Nir Equality
true
Int32 Equality
true
String Equality
true
false
false
true
Character Equality
true
false
false
true
```

## Test: greaterThan

### greaterThan.fg
```javascript
print("Boolean Greater Than\n")
print(true > true, "\n")
print(true > false, "\n")
print(false > true, "\n")
print(false > false, "\n")

print("Decimal Greater Than\n")
print(1.0 > 1.0, "\n")
print(1.0 > 2.0, "\n")
print(2.0 > 1.0, "\n")
print(2.0 > 2.0, "\n")

print("Int32 Greater Than\n")
print(2 > 2, "\n")
print(2 > 1, "\n")
print(1 > 2, "\n")
print(1 > 1, "\n")

print("String Greater Than\n")
print("Hello" > "Hello", "\n")
print("abc" > "abd", "\n")
print("a" >"b", "\n")
print("a" > "a", "\n")
print("da" > "ab", "\n")
print("a" > "da", "\n")
print("da" > "da", "\n")
print("abc" > "ab", "\n")

print("Character Greater Than\n")
print('a' > 'a', "\n")
print('a' > 'b', "\n")
print('b' > 'a', "\n")
print('b' > 'b', "\n")
```

### greaterThan.expect
```
Boolean Greater Than
false
true
false
false
Decimal Greater Than
false
false
true
false
Int32 Greater Than
false
true
false
false
String Greater Than
false
false
false
false
true
false
false
true
Character Greater Than
false
false
true
false
```

## Test: greaterThanEqual

### greaterThanEqual.fg
```javascript
print("Boolean Greater Than Equal\n")
print(true >= true, "\n")
print(true >= false, "\n")
print(false >= true, "\n")
print(false >= false, "\n")

print("Decimal Greater Than Equal\n")
print(1.0 >= 1.0, "\n")
print(1.0 >= 2.0, "\n")
print(2.0 >= 1.0, "\n")
print(2.0 >= 2.0, "\n")

print("Int32 Greater Than Equal\n")
print(2 >= 2, "\n")
print(2 >= 1, "\n")
print(1 >= 2, "\n")
print(1 >= 1, "\n")

print("String Greater Than\n")
print("Hello" >= "Hello", "\n")
print("abc" >= "abd", "\n")
print("a" >= "b", "\n")
print("a" >= "a", "\n")
print("da" >= "ab", "\n")
print("a" >= "da", "\n")
print("da" >= "da", "\n")
print("abc" >= "ab", "\n")

print("Character Greater Than Equal\n")
print('a' >= 'a', "\n")
print('a' >= 'b', "\n")
print('b' >= 'a', "\n")
print('b' >= 'b', "\n")
```

### greaterThanEqual.expect
```
Boolean Greater Than Equal
true
true
false
true
Decimal Greater Than Equal
true
false
true
true
Int32 Greater Than Equal
true
true
false
true
String Greater Than
true
false
false
true
true
false
true
true
Character Greater Than Equal
true
false
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Boolean Inequality\n")
print(true != true, "\n")
print(true != false, "\n")
print(false != true, "\n")
print(false != false, "\n")

print("Decimal Inequality\n")
print(1.0 != 1.0, "\n")
print(1.0 != 2.0, "\n")
print(2.0 != 1.0, "\n")
print(2.0 != 2.0, "\n")

print("Nir Inequality\n")
print(null != null, "\n")

print("Int32 Inequality\n")
print(2 != 2, "\n")
print(2 != 1, "\n")
print(1 != 2, "\n")
print(1 != 1, "\n")

print("String Inequality\n")
print("Hello" != "Hello", "\n")
print("Hello" != "World", "\n")
print("World" != "Hello", "\n")
print("World" != "World", "\n")

print("Character Inequality\n")
print('a' != 'a', "\n")
print('a' != 'b', "\n")
print('b' != 'a', "\n")
print('b' != 'b', "\n")
```

### inequality.expect
```
Boolean Inequality
false
true
true
false
Decimal Inequality
false
true
true
false
Nir Inequality
false
Int32 Inequality
false
true
true
false
String Inequality
false
true
true
false
Character Inequality
false
true
true
false
```

## Test: kInvalidBinaryOperationWithTypes_div

### kInvalidBinaryOperationWithTypes_div.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true/1.0)
```

## Test: kInvalidBinaryOperationWithTypes_eq_str

### kInvalidBinaryOperationWithTypes_eq_str.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(2 == "2")
```

## Test: kInvalidBinaryOperationWithTypes_equal

### kInvalidBinaryOperationWithTypes_equal.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true==1.0)
```

## Test: kInvalidBinaryOperationWithTypes_int

### kInvalidBinaryOperationWithTypes_int.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(1 && 2)
```

## Test: kInvalidBinaryOperationWithTypes_lessThan

### kInvalidBinaryOperationWithTypes_lessThan.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true < 1)
```

## Test: kInvalidBinaryOperationWithTypes_mul

### kInvalidBinaryOperationWithTypes_mul.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true * false)
```

## Test: kInvalidBinaryOperationWithTypes_nir

### kInvalidBinaryOperationWithTypes_nir.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(Nir > Nir)
```

## Test: kInvalidBinaryOperationWithTypes_sub

### kInvalidBinaryOperationWithTypes_sub.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true - false)
```

## Test: lessThan

### lessThan.fg
```javascript
print("Boolean Less Than\n")
print(true < true, "\n")
print(true < false, "\n")
print(false < true, "\n")
print(false < false, "\n")

print("Decimal Less Than\n")
print(1.0 < 1.0, "\n")
print(1.0 < 2.0, "\n")
print(2.0 < 1.0, "\n")
print(2.0 < 2.0, "\n")

print("Int32 Less Than\n")
print(2 < 2, "\n")
print(2 < 1, "\n")
print(1 < 2, "\n")
print(1 < 1, "\n")

print("String Less Than\n")
print("Hello" < "Hello", "\n")
print("abc" < "abd", "\n")
print("a" <"b", "\n")
print("a" < "a", "\n")
print("da" < "ab", "\n")
print("a" < "da", "\n")
print("da" < "a", "\n")

print("Character Less Than\n")
print('a' < 'a', "\n")
print('a' < 'b', "\n")
print('b' < 'a', "\n")
print('b' < 'b', "\n")
```

### lessThan.expect
```
Boolean Less Than
false
false
true
false
Decimal Less Than
false
true
false
false
Int32 Less Than
false
false
true
false
String Less Than
false
true
true
false
false
true
false
Character Less Than
false
true
false
false
```

## Test: lessThanEqual

### lessThanEqual.fg
```javascript
print("Boolean Less Than Equal\n")
print(true <= true, "\n")
print(true <= false, "\n")
print(false <= true, "\n")
print(false <= false, "\n")

print("Decimal Less Than Equal\n")
print(1.0 <= 1.0, "\n")
print(1.0 <= 2.0, "\n")
print(2.0 <= 1.0, "\n")
print(2.0 <= 2.0, "\n")

print("Int32 Less Than Equal\n")
print(2 <= 2, "\n")
print(2 <= 1, "\n")
print(1 <= 2, "\n")
print(1 <= 1, "\n")

print("String Less Than Equal\n")
print("Hello" <= "Hello", "\n")
print("abc" <= "abd", "\n")
print("a" <= "b", "\n")
print("a" <= "a", "\n")
print("da" <= "ab", "\n")
print("a" <= "da", "\n")
print("da" <= "da", "\n")
print("abc" <= "ab", "\n")

print("Character Less Than Equal\n")
print('a' <= 'a', "\n")
print('a' <= 'b', "\n")
print('b' <= 'a', "\n")
print('b' <= 'b', "\n")
```

### lessThanEqual.expect
```
Boolean Less Than Equal
true
false
true
true
Decimal Less Than Equal
true
true
false
true
Int32 Less Than Equal
true
false
true
true
String Less Than Equal
true
true
true
true
false
true
true
false
Character Less Than Equal
true
true
false
true
```

## Test: logicalAnd

### logicalAnd.fg
```javascript
print(true && true, "\n")
print(true && false, "\n")
print(false && true, "\n")
print(false && false)
```

### logicalAnd.expect
```
true
false
false
false
```

## Test: logicalOr

### logicalOr.fg
```javascript
print(true || true, "\n")
print(true || false, "\n")
print(false || true, "\n")
print(false || false)
```

### logicalOr.expect
```
true
true
true
false
```

---

# Directory: MixtureTests

## Test: array_of_dynamic_arrays

### array_of_dynamic_arrays.fg
```javascript
var a:[2] = [1, 2]
var b:[2] = ["x", "y"]
var c:[2][2] = [a, b]
println(c)
```

### array_of_dynamic_arrays.expect
```
[ [ 1, 2 ], [ "x", "y" ] ]
```

## Test: index_in_expression

### index_in_expression.fg
```javascript
var a:int[3] = [5, 10, 15]
var b:int = a[0] + a[1] + a[2]
println(b)
```

### index_in_expression.expect
```
30
```

## Test: mixed_dyn_and_typed_arrays

### mixed_dyn_and_typed_arrays.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var dyn2:[3] = [1, "two", true]
var typed:int[3] = [10, 20, 30]
println(dyn2)
println(typed)
typed[0] = dyn2[1]
println(typed[0])
```

## Test: multi_dim_with_var_index

### multi_dim_with_var_index.fg
```javascript
var a:int[3][3] = [[1,2,3],[4,5,6],[7,8,9]]
var row:int = 1
var col:int = 2
println(a[row][col])
a[row][col] = 100
println(a)
```

### multi_dim_with_var_index.expect
```
6
[ [ 1, 2, 3 ], [ 4, 5, 100 ], [ 7, 8, 9 ] ]
```

## Test: nested_object_array_index

### nested_object_array_index.fg
```javascript
type Inner = { v:int }
type Outer = { arr:Inner[2] }
var obj:Outer = { arr: [{v:10}, {v:20}] }
println(obj.arr[0].v)
println(obj.arr[1].v)
obj.arr[0].v = 99
println(obj.arr)
```

### nested_object_array_index.expect
```
10
20
[ { v: 99 }, { v: 20 } ]
```

## Test: object_array_index_read

### object_array_index_read.fg
```javascript
type Point = { x:int, y:int }
var pts:Point[3] = [{x:1,y:2}, {x:3,y:4}, {x:5,y:6}]
println(pts[0].x)
println(pts[1].y)
println(pts[2])
```

### object_array_index_read.expect
```
1
4
{ x: 5, y: 6 }
```

## Test: object_array_index_write

### object_array_index_write.fg
```javascript
type Point = { x:int, y:int }
var pts:Point[2] = [{x:0,y:0}, {x:0,y:0}]
pts[0].x = 10
pts[0].y = 20
pts[1].x = 30
pts[1].y = 40
println(pts)
```

### object_array_index_write.expect
```
[ { x: 10, y: 20 }, { x: 30, y: 40 } ]
```

## Test: object_array_same_type_copy

### object_array_same_type_copy.fg
```javascript
type T = { n:int }
var a:T[2] = [{n:1},{n:2}]
var b:T[2] = a
println(a)
println(b)
b[0].n = 99
println(a)
println(b)
```

### object_array_same_type_copy.expect
```
[ { n: 1 }, { n: 2 } ]
[ { n: 1 }, { n: 2 } ]
[ { n: 99 }, { n: 2 } ]
[ { n: 99 }, { n: 2 } ]
```

## Test: object_with_dyn_field

### object_with_dyn_field.fg
```javascript
type T = { data:[3] }
var x:[3] = [1, "two", 3.0]
var obj:T = { data: x }
println(obj.data[1])
obj.data[0] = 99
println(obj.data)
```

### object_with_dyn_field.expect
```
"two"
[ 99, "two", 3 ]
```

---

# Directory: WhileTests/05_edge_cases

## Test: condition_deci_small

### condition_deci_small.fg
```javascript
var d: deci = 0.5
var n = 0
while (d > 0.0) {
  println(n)
  n = n + 1
  d = d - 0.25
  if (n >= 2) {
    d = -1.0
  }
}
println("end")
```

### condition_deci_small.expect
```
0
1
end
```

## Test: condition_int_negative

### condition_int_negative.fg
```javascript
var i = -2
while (i < 0) {
  println(i)
  i = i + 1
}
println("done")
```

### condition_int_negative.expect
```
-2
-1
done
```

## Test: condition_int_zero_stops

### condition_int_zero_stops.fg
```javascript
var i = 3
while (i) {
  println(i)
  i = i - 1
}
println("zero")
```

### condition_int_zero_stops.expect
```
3
2
1
zero
```

## Test: condition_string_empty_immediate

### condition_string_empty_immediate.fg
```javascript
var s: str = ""
var n = 0
while (s) {
  n = n + 1
}
println(n)
```

### condition_string_empty_immediate.expect
```
0
```

## Test: empty_body

### empty_body.fg
```javascript
var x = 0
while (x < 0) {
}
println(x)
```

### empty_body.expect
```
0
```

## Test: many_iterations

### many_iterations.fg
```javascript
var i = 0
while (i < 10) {
  println(i)
  i = i + 1
}
println("done")
```

### many_iterations.expect
```
0
1
2
3
4
5
6
7
8
9
done
```

## Test: single_iteration

### single_iteration.fg
```javascript
var x = 0
while (x < 1) {
  println(x)
  x = x + 1
}
println("done")
```

### single_iteration.expect
```
0
done
```

---

# Directory: WhileTests/07_object

## Test: condition_object_nonnull

### condition_object_nonnull.fg
```javascript
type Point = {
  x: int
  y: int
}

var p: Point = { x: 1, y: 2 }
var i = 0
while (p) {
  println(i)
  i = i + 1
  if (i >= 2) {
    p = null
  }
}
println("done")
```

### condition_object_nonnull.expect
```
0
1
done
```

## Test: condition_object_null_never_enters

### condition_object_null_never_enters.fg
```javascript
type T = {
  v: int
}

var o: T = null
var n = 0
while (o) {
  n = n + 1
}
println(n)
```

### condition_object_null_never_enters.expect
```
0
```

## Test: while_with_member_access

### while_with_member_access.fg
```javascript
type Box = {
  count: int
}

var b: Box = { count: 0 }
while (b.count < 3) {
  println(b.count)
  b.count = b.count + 1
}
println("done")
```

### while_with_member_access.expect
```
0
1
2
done
```

---

# Directory: WhileTests/10_break_continue/06_scope

## Test: block_scope_after_break

### block_scope_after_break.fg
```javascript
var x = 0
while (x < 3) {
  var inner = 0
  x = x + 1
  inner = x
  if (x == 2) {
    break
  }
  println(inner)
}
println(x)
```

### block_scope_after_break.expect
```
1
2
```

## Test: loop_inside_function_break

### loop_inside_function_break.fg
```javascript
fun run() {
  var x = 0
  while (x < 5) {
    x = x + 1
    println(x)
    if (x == 3) {
      break
    }
  }
  println("out")
}

run()
println("done")
```

### loop_inside_function_break.expect
```
1
2
3
out
done
```

## Test: loop_inside_function_continue

### loop_inside_function_continue.fg
```javascript
fun run() {
  var x = 0
  while (x < 5) {
    x = x + 1
    if (x == 2) {
      continue
    }
    println(x)
  }
  println("out")
}

run()
println("done")
```

### loop_inside_function_continue.expect
```
1
3
4
5
out
done
```

## Test: nested_loop_local_var_break

### nested_loop_local_var_break.fg
```javascript
var global = 0

fun outer() {
  var i = 0
  while (i < 2) {
    var j = 0
    while (j < 2) {
      println(global)
      println(j)
      j = j + 1
      global = global + 1
      if (global >= 2) {
        break
      }
    }
    i = i + 1
  }
  println("end")
}

outer()
println(global)
```

### nested_loop_local_var_break.expect
```
0
0
1
1
2
0
end
3
```

---

# Directory: WhileTests/10_break_continue/01_errors

## Test: break_in_function_outside_loop

### break_in_function_outside_loop.fg
```javascript
/; EXPECT_ERROR: BreakStatementNotAllowedOutsideOfLoop
fun foo() {
  var x = 1
  if (x > 0) {
    break
  }
  println(x)
}
foo()
```

## Test: break_inside_if_not_loop

### break_inside_if_not_loop.fg
```javascript
/; EXPECT_ERROR: BreakStatementNotAllowedOutsideOfLoop
var n = 0
if (n < 5) {
  println(n)
  break
}
println("end")
```

## Test: break_outside_loop_block

### break_outside_loop_block.fg
```javascript
/; EXPECT_ERROR: BreakStatementNotAllowedOutsideOfLoop
var x = 0
if (true) {
  break
}
println(x)
```

## Test: continue_in_function_outside_loop

### continue_in_function_outside_loop.fg
```javascript
/; EXPECT_ERROR: ContinueStatementNotAllowedOutsideOfLoop
fun foo() {
  var x = 1
  if (x > 0) {
    continue
  }
  println(x)
}
foo()
```

## Test: continue_inside_else_not_loop

### continue_inside_else_not_loop.fg
```javascript
/; EXPECT_ERROR: ContinueStatementNotAllowedOutsideOfLoop
var n = 0
if (n > 0) {
  println("pos")
} else {
  continue
}
println("end")
```

## Test: continue_outside_loop_block

### continue_outside_loop_block.fg
```javascript
/; EXPECT_ERROR: ContinueStatementNotAllowedOutsideOfLoop
var x = 0
if (true) {
  continue
}
println(x)
```

---

# Directory: WhileTests/10_break_continue/02_basic

## Test: break_after_one_iteration

### break_after_one_iteration.fg
```javascript
var x = 0
while (x < 5) {
  x = x + 1
  println(x)
  break
}
println("done")
```

### break_after_one_iteration.expect
```
1
done
```

## Test: break_immediate

### break_immediate.fg
```javascript
var x = 0
while (x < 5) {
  break
  println(x)
  x = x + 1
}
println("done")
```

### break_immediate.expect
```
done
```

## Test: break_on_condition

### break_on_condition.fg
```javascript
var x = 0
while (x < 10) {
  x = x + 1
  if (x == 5) {
    break
  }
  println(x)
}
println("done")
```

### break_on_condition.expect
```
1
2
3
4
done
```

## Test: continue_immediate

### continue_immediate.fg
```javascript
var x = 0
while (x < 3) {
  x = x + 1
  continue
}
println(x)
println("done")
```

### continue_immediate.expect
```
3
done
```

## Test: continue_skip_one

### continue_skip_one.fg
```javascript
var x = 0
while (x < 5) {
  x = x + 1
  if (x == 3) {
    continue
  }
  println(x)
}
println("done")
```

### continue_skip_one.expect
```
1
2
4
5
done
```

## Test: continue_then_break

### continue_then_break.fg
```javascript
var x = 0
while (x < 5) {
  x = x + 1
  if (x == 3) {
    continue
  }
  println(x)
  if (x == 4) {
    break
  }
}
println("done")
```

### continue_then_break.expect
```
1
2
4
done
```

---

# Directory: WhileTests/10_break_continue/03_edge

## Test: break_after_last_iteration

### break_after_last_iteration.fg
```javascript
var x = 0
while (x < 3) {
  println(x)
  x = x + 1
  if (x >= 3) {
    break
  }
}
println("done")
```

### break_after_last_iteration.expect
```
0
1
2
done
```

## Test: break_never_entered

### break_never_entered.fg
```javascript
var x = 0
while (x < 0) {
  println(x)
  break
}
println("done")
```

### break_never_entered.expect
```
done
```

## Test: continue_all_but_last

### continue_all_but_last.fg
```javascript
var x = 0
while (x < 4) {
  x = x + 1
  if (x < 4) {
    continue
  }
  println(x)
}
println("done")
```

### continue_all_but_last.expect
```
4
done
```

---

# Directory: WhileTests/10_break_continue/04_nested

## Test: break_inner_only

### break_inner_only.fg
```javascript
var i = 0
while (i < 3) {
  var j = 0
  while (j < 3) {
    println(j)
    j = j + 1
    if (j >= 2) {
      break
    }
  }
  println(i)
  i = i + 1
}
println("done")
```

### break_inner_only.expect
```
0
1
0
0
1
1
0
1
2
done
```

## Test: break_outer_from_inner

### break_outer_from_inner.fg
```javascript
var i = 0
var j = 0
while (i < 3) {
  j = 0
  while (j < 3) {
    println(i)
    println(j)
    j = j + 1
    if (i == 1 && j == 2) {
      break
    }
  }
  if (i == 1) {
    break
  }
  i = i + 1
}
println("done")
```

### break_outer_from_inner.expect
```
0
0
0
1
0
2
1
0
1
1
done
```

## Test: continue_inner_only

### continue_inner_only.fg
```javascript
var i = 0
while (i < 3) {
  var j = 0
  while (j < 4) {
    j = j + 1
    if (j == 2) {
      continue
    }
    println(j)
  }
  println(i)
  i = i + 1
}
println("done")
```

### continue_inner_only.expect
```
1
3
4
0
1
3
4
1
1
3
4
2
done
```

## Test: deeply_nested_break_inner

### deeply_nested_break_inner.fg
```javascript
var a = 0
while (a < 2) {
  var b = 0
  while (b < 2) {
    var c = 0
    while (c < 3) {
      println(c)
      c = c + 1
      if (c >= 2) {
        break
      }
    }
    b = b + 1
  }
  a = a + 1
}
println("done")
```

### deeply_nested_break_inner.expect
```
0
1
0
1
0
1
0
1
done
```

---

# Directory: WhileTests/10_break_continue/05_complex

## Test: break_after_assign

### break_after_assign.fg
```javascript
var x = 0
var sum = 0
while (x < 5) {
  x = x + 1
  sum = sum + x
  if (sum >= 6) {
    break
  }
  println(sum)
}
println("done")
```

### break_after_assign.expect
```
1
3
done
```

## Test: break_with_if_else

### break_with_if_else.fg
```javascript
var x = 0
while (x < 6) {
  x = x + 1
  if (x == 2) {
    println(2)
  } else if (x == 4) {
    println(4)
    break
  } else if (x == 5) {
    println(5)
  }
}
println("done")
```

### break_with_if_else.expect
```
2
4
done
```

## Test: continue_with_nested_if

### continue_with_nested_if.fg
```javascript
var x = 0
while (x < 5) {
  x = x + 1
  if (x > 1) {
    if (x == 3) {
      continue
    }
    println(x)
  }
}
println("done")
```

### continue_with_nested_if.expect
```
2
4
5
done
```

---

# Directory: WhileTests/01_basic

## Test: basic_while_count

### basic_while_count.fg
```javascript
var x = 0
while (x < 5) {
  x = x + 1
}
println(x)
```

### basic_while_count.expect
```
5
```

## Test: while_only_break

### while_only_break.fg
```javascript
var x = 0
while (x < 5) {
  break
}
println("done")
```

### while_only_break.expect
```
done
```

## Test: while_print_each

### while_print_each.fg
```javascript
var x = 0
while (x < 5) {
  println(x)
  x = x + 1
}
```

### while_print_each.expect
```
0
1
2
3
4
```

## Test: while_zero_iterations

### while_zero_iterations.fg
```javascript
var x = 10
while (x < 5) {
  x = x + 1
}
println(x)
```

### while_zero_iterations.expect
```
10
```

---

# Directory: WhileTests/09_short_circuit

## Test: and_bool_vars

### and_bool_vars.fg
```javascript
var a: bool = true
var b: bool = true
while (a && b) {
  println("ok")
  a = false
}
println("done")
```

### and_bool_vars.expect
```
ok
done
```

## Test: and_dynamic_literal_left

### and_dynamic_literal_left.fg
```javascript
var x = true
while (true && x) {
  println("once")
  x = false
}
println("done")
```

### and_dynamic_literal_left.expect
```
once
done
```

## Test: and_dynamic_vars

### and_dynamic_vars.fg
```javascript
var i = 0
var flag = true
while (i < 2 && flag) {
  println(i)
  i = i + 1
  if (i >= 2) {
    flag = false
  }
}
println("done")
```

### and_dynamic_vars.expect
```
0
1
done
```

## Test: and_false_literal_never_enters

### and_false_literal_never_enters.fg
```javascript
while (false && true) {
  println("body")
}
println("done")
```

### and_false_literal_never_enters.expect
```
done
```

## Test: and_literal_left_var_right

### and_literal_left_var_right.fg
```javascript
var flag: bool = true
while (true && flag) {
  println("once")
  flag = false
}
println("done")
```

### and_literal_left_var_right.expect
```
once
done
```

## Test: and_typed_int

### and_typed_int.fg
```javascript
var i: int = 0
var j: int = 1
while (i < 2 && j > 0) {
  println(i)
  i = i + 1
}
println("done")
```

### and_typed_int.expect
```
0
1
done
```

## Test: chained_and_three

### chained_and_three.fg
```javascript
var a: bool = true
var b: bool = true
var c: bool = true
while (a && b && c) {
  println("ok")
  a = false
}
println("done")
```

### chained_and_three.expect
```
ok
done
```

## Test: chained_four_and

### chained_four_and.fg
```javascript
var a: bool = true
var b: bool = true
var c: bool = true
var d: bool = true
while (a && b && c && d) {
  println("ok")
  a = false
}
println("done")
```

### chained_four_and.expect
```
ok
done
```

## Test: chained_func_and_var_and_func

### chained_func_and_var_and_func.fg
```javascript
fun limit() -> int {
  return 2
}

fun ok() -> bool {
  return true
}

var i = 0
var flag = true
while (i < limit() && flag && ok()) {
  println(i)
  i = i + 1
  if (i >= 2) {
    flag = false
  }
}
println("done")
```

### chained_func_and_var_and_func.expect
```
0
1
done
```

## Test: chained_or_or_and

### chained_or_or_and.fg
```javascript
var a: bool = false
var b: bool = false
var c: bool = true
var d: bool = true
while (a || b || c && d) {
  println("x")
  c = false
}
println("done")
```

### chained_or_or_and.expect
```
x
done
```

## Test: chained_or_three

### chained_or_three.fg
```javascript
var a: bool = false
var b: bool = false
var c: bool = true
while (a || b || c) {
  println("ok")
  c = false
}
println("done")
```

### chained_or_three.expect
```
ok
done
```

## Test: chained_three_and_or

### chained_three_and_or.fg
```javascript
var a: bool = true
var b: bool = true
var c: bool = true
var d: bool = true
while (a && b && c || d) {
  println("x")
  d = false
  if (a && b && c) {
    a = false
  }
}
println("done")
```

### chained_three_and_or.expect
```
x
done
```

## Test: chained_var_and_func

### chained_var_and_func.fg
```javascript
fun check(n: int) -> bool {
  return n < 2
}

var a: bool = true
var i: int = 0
while (a && check(i)) {
  println(i)
  i = i + 1
  if (i >= 2) {
    a = false
  }
}
println("done")
```

### chained_var_and_func.expect
```
0
1
done
```

## Test: complex_dynamic_and_or

### complex_dynamic_and_or.fg
```javascript
var i = 0
var stop = false
var extra = true
while (i < 2 && (!stop || extra)) {
  println(i)
  i = i + 1
  if (i >= 2) {
    stop = true
    extra = false
  }
}
println("done")
```

### complex_dynamic_and_or.expect
```
0
1
done
```

## Test: complex_four_and_one_or

### complex_four_and_one_or.fg
```javascript
var a: bool = true
var b: bool = true
var c: bool = true
var d: bool = true
while (a && b && (c || d)) {
  println("x")
  if (d) {
    d = false
  } else {
    c = false
  }
}
println("done")
```

### complex_four_and_one_or.expect
```
x
x
done
```

## Test: complex_func_nested

### complex_func_nested.fg
```javascript
fun outer(n: int) -> bool {
  return n < 2
}

fun left() -> bool {
  return false
}

fun right() -> bool {
  return true
}

var i = 0
while (outer(i) && (left() || right())) {
  println(i)
  i = i + 1
}
println("done")
```

### complex_func_nested.expect
```
0
1
done
```

## Test: complex_mixed_parens

### complex_mixed_parens.fg
```javascript
var a: bool = false
var b: bool = true
var c: bool = true
var d: bool = true
while ((a && b) || (c && d)) {
  println("x")
  c = false
}
println("done")
```

### complex_mixed_parens.expect
```
x
done
```

## Test: func_and_func

### func_and_func.fg
```javascript
var run: bool = true

fun first() -> bool {
  return run
}

fun second() -> bool {
  return true
}

while (first() && second()) {
  println("once")
  run = false
}
println("done")
```

### func_and_func.expect
```
once
done
```

## Test: func_and_var

### func_and_var.fg
```javascript
fun ok() -> bool {
  return true
}

var flag: bool = true
while (ok() && flag) {
  println("once")
  flag = false
}
println("done")
```

### func_and_var.expect
```
once
done
```

## Test: func_compare_and_var

### func_compare_and_var.fg
```javascript
fun getLimit() -> int {
  return 2
}

var i = 0
var flag = true
while (i < getLimit() && flag) {
  println(i)
  i = i + 1
  if (i >= 2) {
    flag = false
  }
}
println("done")
```

### func_compare_and_var.expect
```
0
1
done
```

## Test: func_or_func

### func_or_func.fg
```javascript
fun yes() -> bool {
  return true
}

fun no() -> bool {
  return false
}

var n = 0
while (no() || yes() && n < 1) {
  println("once")
  n = 1
}
println("done")
```

### func_or_func.expect
```
once
done
```

## Test: func_or_var

### func_or_var.fg
```javascript
fun no() -> bool {
  return false
}

var flag: bool = true
while (no() || flag) {
  println("once")
  flag = false
}
println("done")
```

### func_or_var.expect
```
once
done
```

## Test: nested_and_or

### nested_and_or.fg
```javascript
var a: bool = false
var b: bool = true
var c: bool = true
while ((a || b) && c) {
  println("n")
  b = false
}
println("done")
```

### nested_and_or.expect
```
n
done
```

## Test: nested_or_and

### nested_or_and.fg
```javascript
var a: bool = true
var b: bool = false
var c: bool = true
while (a && (b || c)) {
  println("n")
  a = false
}
println("done")
```

### nested_or_and.expect
```
n
done
```

## Test: or_bool_vars

### or_bool_vars.fg
```javascript
var a: bool = false
var b: bool = true
while (a || b) {
  println("ok")
  b = false
}
println("done")
```

### or_bool_vars.expect
```
ok
done
```

## Test: or_dynamic_literal_right

### or_dynamic_literal_right.fg
```javascript
var flag = true
while (flag || false) {
  println("once")
  flag = false
}
println("done")
```

### or_dynamic_literal_right.expect
```
once
done
```

## Test: or_dynamic_vars

### or_dynamic_vars.fg
```javascript
var a = 0
var b = 5
while (a < 1 || b > 3) {
  println(a)
  a = a + 1
  b = b - 1
}
println("end")
```

### or_dynamic_vars.expect
```
0
1
end
```

## Test: or_true_literal_enters_once

### or_true_literal_enters_once.fg
```javascript
var n = 0
while (n == 0 || false) {
  println("once")
  n = 1
}
println("done")
```

### or_true_literal_enters_once.expect
```
once
done
```

## Test: or_typed_int

### or_typed_int.fg
```javascript
var i: int = 0
var j: int = 1
while (i < 1 || j > 0) {
  println(i)
  i = i + 1
  j = j - 1
}
println("done")
```

### or_typed_int.expect
```
0
done
```

## Test: or_var_left_literal_right

### or_var_left_literal_right.fg
```javascript
var flag: bool = true
while (flag || false) {
  println("once")
  flag = false
}
println("done")
```

### or_var_left_literal_right.expect
```
once
done
```

---

# Directory: WhileTests/03_scope

## Test: scope_assign_from_func_in_body

### scope_assign_from_func_in_body.fg
```javascript
fun nextVal() -> int {
  return 1
}

var sum = 0
var i = 0
while (i < 3) {
  sum = sum + nextVal()
  i = i + 1
}
println(sum)
```

### scope_assign_from_func_in_body.expect
```
3
```

## Test: scope_decl_from_func_in_body

### scope_decl_from_func_in_body.fg
```javascript
fun getVal() -> int {
  return 7
}

var i = 0
while (i < 2) {
  var x: int = getVal()
  println(x)
  i = i + 1
}
println("done")
```

### scope_decl_from_func_in_body.expect
```
7
7
done
```

## Test: scope_nested_block_in_body

### scope_nested_block_in_body.fg
```javascript
var i = 0
while (i < 2) {
  {
    var inner = i * 10
    println(inner)
  }
  i = i + 1
}
println("end")
```

### scope_nested_block_in_body.expect
```
0
10
end
```

## Test: scope_outer_var_in_inner_while

### scope_outer_var_in_inner_while.fg
```javascript
var outer = 0
while (outer < 2) {
  var inner = 0
  while (inner < 2) {
    println(outer)
    println(inner)
    inner = inner + 1
  }
  outer = outer + 1
}
println("done")
```

### scope_outer_var_in_inner_while.expect
```
0
0
0
1
1
0
1
1
done
```

## Test: scope_reassign_outer_in_body

### scope_reassign_outer_in_body.fg
```javascript
var total = 0
var i = 0
while (i < 3) {
  total = total + i
  i = i + 1
}
println(total)
```

### scope_reassign_outer_in_body.expect
```
3
```

## Test: scope_shadow_in_body

### scope_shadow_in_body.fg
```javascript
var x: int = 1
var i = 0
while (i < 2) {
  var x: int = 10
  println(x)
  i = i + 1
}
println(x)
```

### scope_shadow_in_body.expect
```
10
10
1
```

## Test: scope_var_in_body

### scope_var_in_body.fg
```javascript
var x = 0
while (x < 2) {
  var inner = x * 10
  println(inner)
  x = x + 1
}
println(x)
```

### scope_var_in_body.expect
```
0
10
2
```

---

# Directory: WhileTests/02_conditions

## Test: condition_arithmetic_in_condition

### condition_arithmetic_in_condition.fg
```javascript
var i = 0
while (i + 1 < 4) {
  println(i)
  i = i + 1
}
println("end")
```

### condition_arithmetic_in_condition.expect
```
0
1
2
end
```

## Test: condition_binary_eq

### condition_binary_eq.fg
```javascript
var i = 0
while (i != 3) {
  println(i)
  i = i + 1
}
println("done")
```

### condition_binary_eq.expect
```
0
1
2
done
```

## Test: condition_binary_lt

### condition_binary_lt.fg
```javascript
var i = 0
while (i < 4) {
  println(i)
  i = i + 1
}
println("end")
```

### condition_binary_lt.expect
```
0
1
2
3
end
```

## Test: condition_bool_true

### condition_bool_true.fg
```javascript
var n = 0
var flag = true
while (flag) {
  n = n + 1
  if (n >= 3) {
    flag = false
  }
}
println(n)
```

### condition_bool_true.expect
```
3
```

## Test: condition_char_nonzero

### condition_char_nonzero.fg
```javascript
var c: char = 'a'
var n = 0
while (c) {
  println(n)
  n = n + 1
  if (n >= 1) {
    c = '\0'
  }
}
println("done")
```

### condition_char_nonzero.expect
```
0
done
```

## Test: condition_deci_nonzero

### condition_deci_nonzero.fg
```javascript
var d: deci = 2.0
var n = 0
while (d) {
  println(n)
  n = n + 1
  d = d - 1.0
  if (n >= 2) {
    d = 0.0
  }
}
println("end")
```

### condition_deci_nonzero.expect
```
0
1
end
```

## Test: condition_func_return_bool

### condition_func_return_bool.fg
```javascript
fun check(n: int) -> bool {
  return n < 3
}

var i = 0
while (check(i)) {
  println(i)
  i = i + 1
}
println("done")
```

### condition_func_return_bool.expect
```
0
1
2
done
```

## Test: condition_func_return_int_compare

### condition_func_return_int_compare.fg
```javascript
fun getLimit() -> int {
  return 3
}

var i = 0
while (i < getLimit()) {
  println(i)
  i = i + 1
}
println("end")
```

### condition_func_return_int_compare.expect
```
0
1
2
end
```

## Test: condition_int_nonzero

### condition_int_nonzero.fg
```javascript
var x = 3
while (x) {
  println(x)
  x = x - 1
}
println("done")
```

### condition_int_nonzero.expect
```
3
2
1
done
```

## Test: condition_logical_and

### condition_logical_and.fg
```javascript
var i = 0
var flag = true
while (i < 2 && flag) {
  println(i)
  i = i + 1
  if (i >= 2) {
    flag = false
  }
}
println("done")
```

### condition_logical_and.expect
```
0
1
done
```

## Test: condition_logical_or

### condition_logical_or.fg
```javascript
var a = 0
var b = 5
while (a < 2 || b > 3) {
  println(a)
  println(b)
  a = a + 1
  b = b - 1
}
println("end")
```

### condition_logical_or.expect
```
0
5
1
4
end
```

## Test: condition_string_nonempty

### condition_string_nonempty.fg
```javascript
var s: str = "ab"
var i = 0
while (s) {
  println(i)
  i = i + 1
  if (i >= 2) {
    s = ""
  }
}
println("done")
```

### condition_string_nonempty.expect
```
0
1
done
```

## Test: condition_unary_not

### condition_unary_not.fg
```javascript
var flag = true
var n = 0
while (!(n >= 2)) {
  println(n)
  n = n + 1
}
println("done")
```

### condition_unary_not.expect
```
0
1
done
```

---

# Directory: WhileTests/08_array

## Test: condition_func_return_array

### condition_func_return_array.fg
```javascript
fun getArr() -> int[3] {
  return [1, 2, 3]
}

var i = 0
var arr: int[3] = getArr()
while (arr[0]) {
  println(i)
  i = i + 1
  if (i >= 2) {
    arr = [0]
  }
}
println("done")
```

### condition_func_return_array.expect
```
0
1
done
```

## Test: while_accumulate_array

### while_accumulate_array.fg
```javascript
var arr: int[3] = [10, 20, 30]
var i = 0
var sum = 0
while (i < 3) {
  sum = sum + arr[i]
  i = i + 1
}
println(sum)
```

### while_accumulate_array.expect
```
60
```

## Test: while_array_index_condition

### while_array_index_condition.fg
```javascript
var arr: int[3] = [5, 3, 1]
var i = 0
while (i < 3 && arr[i] > 0) {
  println(arr[i])
  i = i + 1
}
println("end")
```

### while_array_index_condition.expect
```
5
3
1
end
```

## Test: while_array_index_shortcircuit

### while_array_index_shortcircuit.fg
```javascript
var arr: int[3] = [5, 3, 1]
var i: int = 0
while (i < 3 && arr[i] > 0) {
  println(arr[i])
  i = i + 1
}
println("end")
```

### while_array_index_shortcircuit.expect
```
5
3
1
end
```

---

# Directory: WhileTests/06_dynamic

## Test: condition_dynamic_from_func

### condition_dynamic_from_func.fg
```javascript
fun getVal() {
  return 2
}

var i = 0
var limit = getVal()
while (i < limit) {
  println(i)
  i = i + 1
}
println("done")
```

### condition_dynamic_from_func.expect
```
0
1
done
```

## Test: condition_dynamic_truthy

### condition_dynamic_truthy.fg
```javascript
fun getCount() {
  return 1
}

var i = 0
var step = getCount()
while (i < 3) {
  i = i + step
  println(i)
}
println("end")
```

### condition_dynamic_truthy.expect
```
1
2
3
end
```

## Test: condition_dynamic_zero

### condition_dynamic_zero.fg
```javascript
var d = 0
var n = 0
while (d) {
  n = n + 1
}
println(n)
```

### condition_dynamic_zero.expect
```
0
```

---

# Directory: WhileTests/04_complex

## Test: deeply_nested_while_if

### deeply_nested_while_if.fg
```javascript
var a = 0
while (a < 2) {
  var b = 0
  while (b < 2) {
    if (a == b) {
      println(1)
    } else {
      println(0)
    }
    b = b + 1
  }
  a = a + 1
}
println("end")
```

### deeply_nested_while_if.expect
```
1
0
0
1
end
```

## Test: factorial

### factorial.fg
```javascript
var x = 5
var factorial = 1
while (x > 0) {
  factorial = factorial * x
  x = x - 1
}
println(factorial)
```

### factorial.expect
```
120
```

## Test: nested_while

### nested_while.fg
```javascript
var i = 0
while (i < 2) {
  var j = 0
  while (j < 2) {
    println(i)
    println(j)
    j = j + 1
  }
  i = i + 1
}
println("done")
```

### nested_while.expect
```
0
0
0
1
1
0
1
1
done
```

## Test: while_assign_from_func_in_body

### while_assign_from_func_in_body.fg
```javascript
fun step() -> int {
  return 1
}

var acc = 0
var i = 0
while (i < 3) {
  acc = acc + step()
  println(acc)
  i = i + 1
}
println("done")
```

### while_assign_from_func_in_body.expect
```
1
2
3
done
```

## Test: while_condition_from_func_call

### while_condition_from_func_call.fg
```javascript
fun limit() -> int {
  return 2
}

var i = 0
while (i < limit()) {
  println(i)
  i = i + 1
}
println("end")
```

### while_condition_from_func_call.expect
```
0
1
end
```

## Test: while_multi_var_assign

### while_multi_var_assign.fg
```javascript
fun getPair() -> int, int {
  return 1, 2
}

var i = 0
var a = 0
var b = 0
while (i < 2) {
  a, b = getPair()
  println(a)
  println(b)
  i = i + 1
}
println("end")
```

### while_multi_var_assign.expect
```
1
2
1
2
end
```

## Test: while_with_if_else

### while_with_if_else.fg
```javascript
var x = 0
while (x < 5) {
  if (x == 3) {
    x = x + 1
  } else {
    x = x + 2
  }
}
println(x)
```

### while_with_if_else.expect
```
6
```

## Test: while_with_ternary_in_body

### while_with_ternary_in_body.fg
```javascript
var i = 0
while (i < 3) {
  var v = i > 1 ? 10 : 0
  println(v)
  i = i + 1
}
println("done")
```

### while_with_ternary_in_body.expect
```
0
0
10
done
```

---

# Directory: WhileTests/06_errors

## Test: body_variable_not_found

### body_variable_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var x = 0
while (x < 5) {
  y = y + 1
}
println(x)
```

## Test: condition_func_return_void

### condition_func_return_void.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
fun doVoid() -> nthg {
  println("x")
}

var i = 0
while (doVoid() == true) {
  i = i + 1
}
println(i)
```

## Test: condition_function_not_found

### condition_function_not_found.fg
```javascript
/; EXPECT_ERROR: FunctionNotFound
var i = 0
while (unknownFunc(i)) {
  i = i + 1
}
println(i)
```

## Test: condition_invalid_binary_op

### condition_invalid_binary_op.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
var s: str = "hello"
var i = 0
while (s < 5) {
  i = i + 1
}
println(i)
```

## Test: condition_variable_not_found

### condition_variable_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var x = 0
while (unknown < 5) {
  x = x + 1
}
println(x)
```

---

# Directory: BinaryOperationLiteralTests/char

## Test: bool_and_char_add

### bool_and_char_add.fg
```javascript
print('A' + true, "\n")
print('A' + false, "\n")
/; EXPECT: B
/; EXPECT: A
```

### bool_and_char_add.expect
```
B
A
```

## Test: concatenation

### concatenation.fg
```javascript
print("Char Concatenation Tests (returns string)\n")
print('a' + 'b', "\n")
print('A' + 'B', "\n")
print('1' + '2', "\n")
print(' ' + ' ', "\n")
print('H' + 'i', "\n")
print('0' + '0', "\n")
print('a' + ' ', "\n")
print(' ' + 'b', "\n")
```

### concatenation.expect
```
Char Concatenation Tests (returns string)
ab
AB
12
  
Hi
00
a 
 b
```

## Test: deci64_and_char_add

### deci64_and_char_add.fg
```javascript
print('A' + 1.5, "\n")
/; EXPECT: B
```

### deci64_and_char_add.expect
```
B
```

## Test: decimal_and_char_add

### decimal_and_char_add.fg
```javascript
print(1.0 + 'a')
```

### decimal_and_char_add.expect
```
b
```

## Test: division

### division.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('9' / '1', "\n")
```

## Test: equality

### equality.fg
```javascript
print("Char Equality Tests\n")
print('a' == 'a', "\n")
print('a' == 'b', "\n")
print('A' == 'A', "\n")
print('A' == 'a', "\n")
print('1' == '1', "\n")
print('1' == '2', "\n")
print(' ' == ' ', "\n")
print('0' == '0', "\n")
```

### equality.expect
```
Char Equality Tests
true
false
true
false
true
false
true
true
```

## Test: greater_than

### greater_than.fg
```javascript
print("Char Greater Than Tests\n")
print('a' > 'a', "\n")
print('a' > 'b', "\n")
print('b' > 'a', "\n")
print('A' > 'Z', "\n")
print('Z' > 'A', "\n")
print('A' > 'a', "\n")
print('a' > 'A', "\n")
print('0' > '9', "\n")
print('9' > '0', "\n")
```

### greater_than.expect
```
Char Greater Than Tests
false
false
true
false
true
false
true
false
true
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Char Greater Than or Equal Tests\n")
print('a' >= 'a', "\n")
print('a' >= 'b', "\n")
print('b' >= 'a', "\n")
print('A' >= 'Z', "\n")
print('Z' >= 'A', "\n")
print('A' >= 'a', "\n")
print('a' >= 'A', "\n")
print('9' >= '0', "\n")
print('9' >= '9', "\n")
```

### greater_than_equal.expect
```
Char Greater Than or Equal Tests
true
false
true
false
true
false
true
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Char Inequality Tests\n")
print('a' != 'a', "\n")
print('a' != 'b', "\n")
print('A' != 'A', "\n")
print('A' != 'a', "\n")
print('1' != '1', "\n")
print('1' != '2', "\n")
print(' ' != ' ', "\n")
print('0' != '1', "\n")
```

### inequality.expect
```
Char Inequality Tests
false
true
false
true
false
true
false
true
```

## Test: int8_and_char_add

### int8_and_char_add.fg
```javascript
print('A' + 1, "\n")
print('A' + 32, "\n")
/; EXPECT: B
/; EXPECT: a
```

### int8_and_char_add.expect
```
B
a
```

## Test: int_and_char_add

### int_and_char_add.fg
```javascript
print(1 + 'a')
```

### int_and_char_add.expect
```
b
```

## Test: less_than

### less_than.fg
```javascript
print("Char Less Than Tests\n")
print('a' < 'a', "\n")
print('a' < 'b', "\n")
print('b' < 'a', "\n")
print('A' < 'Z', "\n")
print('Z' < 'A', "\n")
print('A' < 'a', "\n")
print('a' < 'A', "\n")
print('0' < '9', "\n")
print('9' < '0', "\n")
```

### less_than.expect
```
Char Less Than Tests
false
true
false
true
false
true
false
true
false
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Char Less Than or Equal Tests\n")
print('a' <= 'a', "\n")
print('a' <= 'b', "\n")
print('b' <= 'a', "\n")
print('A' <= 'Z', "\n")
print('Z' <= 'A', "\n")
print('A' <= 'a', "\n")
print('a' <= 'A', "\n")
print('0' <= '9', "\n")
print('9' <= '9', "\n")
```

### less_than_equal.expect
```
Char Less Than or Equal Tests
true
true
false
true
false
true
false
true
true
```

---

# Directory: BinaryOperationLiteralTests/deci64

## Test: addition

### addition.fg
```javascript
print("Deci (Double) Addition Tests\n")
print(0.0 + 0.0, "\n")
print(1.0 + 0.0, "\n")
print(0.0 + 1.0, "\n")
print(1.5 + 1.5, "\n")
print(3.14159265359 + 2.71828182846, "\n")
print(-1.5 + 1.5, "\n")
print(-3.14 + -2.86, "\n")
print(100.25 + 200.75, "\n")
print(0.000001 + 0.000001, "\n")
print(1234567890.123456 + 0.0, "\n")
```

### addition.expect
```
Deci (Double) Addition Tests
0
1
1
3
5.85987448205
0
-6
301
2e-06
1234567890.123456001281738
```

## Test: division

### division.fg
```javascript
print("Deci (Double) Division Tests\n")
print(0.0 / 1.0, "\n")
print(1.0 / 1.0, "\n")
print(6.0 / 2.0, "\n")
print(5.0 / 2.0, "\n")
print(10.0 / 3.0, "\n")
print(-6.0 / 2.0, "\n")
print(6.0 / -2.0, "\n")
print(-6.0 / -2.0, "\n")
print(3.14159265359 / 2.0, "\n")
print(1.0 / 4.0, "\n")
print(22.0 / 7.0, "\n")
```

### division.expect
```
Deci (Double) Division Tests
0
1
3
2.5
3.333333333333333
-3
-3
3
1.570796326795
0.25
3.142857142857143
```

## Test: equality

### equality.fg
```javascript
print("Deci (Double) Equality Tests\n")
print(0.0 == 0.0, "\n")
print(1.0 == 1.0, "\n")
print(1.0 == 0.0, "\n")
print(0.0 == 1.0, "\n")
print(3.14159265359 == 3.14159265359, "\n")
print(3.14159265359 == 3.14159265358, "\n")
print(-1.5 == -1.5, "\n")
print(-1.5 == 1.5, "\n")
```

### equality.expect
```
Deci (Double) Equality Tests
true
true
false
false
true
false
true
false
```

## Test: greater_than

### greater_than.fg
```javascript
print("Deci (Double) Greater Than Tests\n")
print(0.0 > 0.0, "\n")
print(0.0 > 1.0, "\n")
print(1.0 > 0.0, "\n")
print(1.0 > 1.0, "\n")
print(3.14 > 3.15, "\n")
print(3.15 > 3.14, "\n")
print(-1.5 > 1.5, "\n")
print(1.5 > -1.5, "\n")
print(-1.0 > -2.0, "\n")
print(-2.0 > -1.0, "\n")
print(0.000002 > 0.000001, "\n")
```

### greater_than.expect
```
Deci (Double) Greater Than Tests
false
false
true
false
false
true
false
true
true
false
true
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Deci (Double) Greater Than or Equal Tests\n")
print(0.0 >= 0.0, "\n")
print(0.0 >= 1.0, "\n")
print(1.0 >= 0.0, "\n")
print(1.0 >= 1.0, "\n")
print(3.14 >= 3.15, "\n")
print(3.15 >= 3.14, "\n")
print(-1.5 >= 1.5, "\n")
print(1.5 >= -1.5, "\n")
print(3.14159265359 >= 3.14159265359, "\n")
```

### greater_than_equal.expect
```
Deci (Double) Greater Than or Equal Tests
true
false
true
true
false
true
false
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Deci (Double) Inequality Tests\n")
print(0.0 != 0.0, "\n")
print(1.0 != 1.0, "\n")
print(1.0 != 0.0, "\n")
print(0.0 != 1.0, "\n")
print(3.14159265359 != 3.14159265359, "\n")
print(3.14159265359 != 3.14159265358, "\n")
print(-1.5 != -1.5, "\n")
print(-1.5 != 1.5, "\n")
```

### inequality.expect
```
Deci (Double) Inequality Tests
false
false
true
true
false
true
false
true
```

## Test: int_deci

### int_deci.fg
```javascript
var x: deci = 2 + 5
print(x, "\n")
```

### int_deci.expect
```
7
```

## Test: less_than

### less_than.fg
```javascript
print("Deci (Double) Less Than Tests\n")
print(0.0 < 0.0, "\n")
print(0.0 < 1.0, "\n")
print(1.0 < 0.0, "\n")
print(1.0 < 1.0, "\n")
print(3.14 < 3.15, "\n")
print(3.15 < 3.14, "\n")
print(-1.5 < 1.5, "\n")
print(1.5 < -1.5, "\n")
print(-2.0 < -1.0, "\n")
print(-1.0 < -2.0, "\n")
print(0.000001 < 0.000002, "\n")
```

### less_than.expect
```
Deci (Double) Less Than Tests
false
true
false
false
true
false
true
false
true
false
true
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Deci (Double) Less Than or Equal Tests\n")
print(0.0 <= 0.0, "\n")
print(0.0 <= 1.0, "\n")
print(1.0 <= 0.0, "\n")
print(1.0 <= 1.0, "\n")
print(3.14 <= 3.15, "\n")
print(3.15 <= 3.14, "\n")
print(-1.5 <= 1.5, "\n")
print(1.5 <= -1.5, "\n")
print(3.14159265359 <= 3.14159265359, "\n")
```

### less_than_equal.expect
```
Deci (Double) Less Than or Equal Tests
true
true
false
true
true
false
true
false
true
```

## Test: multiplication

### multiplication.fg
```javascript
print("Deci (Double) Multiplication Tests\n")
print(0.0 * 0.0, "\n")
print(1.0 * 0.0, "\n")
print(0.0 * 1.0, "\n")
print(1.0 * 1.0, "\n")
print(2.0 * 3.0, "\n")
print(1.5 * 2.0, "\n")
print(-1.5 * 2.0, "\n")
print(-2.0 * -3.0, "\n")
print(3.14159265359 * 2.0, "\n")
print(0.5 * 0.5, "\n")
print(1000000.0 * 1000000.0, "\n")
```

### multiplication.expect
```
Deci (Double) Multiplication Tests
0
0
0
1
6
3
-3
6
6.28318530718
0.25
1000000000000
```

## Test: subtraction

### subtraction.fg
```javascript
print("Deci (Double) Subtraction Tests\n")
print(0.0 - 0.0, "\n")
print(1.0 - 0.0, "\n")
print(0.0 - 1.0, "\n")
print(3.0 - 1.5, "\n")
print(3.14159265359 - 2.71828182846, "\n")
print(-1.5 - 1.5, "\n")
print(-3.14 - -2.86, "\n")
print(100.25 - 200.75, "\n")
print(0.000002 - 0.000001, "\n")
print(1234567890.123456 - 1234567890.123456, "\n")
```

### subtraction.expect
```
Deci (Double) Subtraction Tests
0
1
-1
1.5
0.42331082513
-3
-0.28
-100.5
1e-06
0
```

---

# Directory: BinaryOperationLiteralTests/int32

## Test: addition

### addition.fg
```javascript
print("Int32 Addition Tests (values outside int8 range)\n")
print(128 + 0, "\n")
print(128 + 128, "\n")
print(1000 + 2000, "\n")
print(50000 + 50000, "\n")
print(1000000 + 1000000, "\n")
print(-129 + 1, "\n")
print(-500 + 300, "\n")
print(-1000 + -2000, "\n")
print(2147483647 + 0, "\n")
print(-2147483648 + 0, "\n")
print(1000000000 + 1000000000, "\n")
```

### addition.expect
```
Int32 Addition Tests (values outside int8 range)
128
256
3000
100000
2000000
-128
-200
-3000
2147483647
-2147483648
2000000000
```

## Test: bitwise_and

### bitwise_and.fg
```javascript
print("Int32 Bitwise AND Tests (values outside int8 range)\n")
print(128 & 0, "\n")
print(128 & 128, "\n")
print(256 & 255, "\n")
print(1000 & 500, "\n")
print(65535 & 255, "\n")
print(0xFFFF & 0x00FF, "\n")
print(1000000 & 999999, "\n")
print(2147483647 & 1073741823, "\n")
```

### bitwise_and.expect
```
Int32 Bitwise AND Tests (values outside int8 range)
0
128
0
480
255
255
999936
1073741823
```

## Test: bitwise_or

### bitwise_or.fg
```javascript
print("Int32 Bitwise OR Tests (values outside int8 range)\n")
print(128 | 0, "\n")
print(128 | 128, "\n")
print(256 | 255, "\n")
print(1000 | 500, "\n")
print(65280 | 255, "\n")
print(0xFF00 | 0x00FF, "\n")
print(1000000 | 1, "\n")
print(1073741824 | 536870912, "\n")
```

### bitwise_or.expect
```
Int32 Bitwise OR Tests (values outside int8 range)
128
128
511
1020
65535
65535
1000001
1610612736
```

## Test: bitwise_xor

### bitwise_xor.fg
```javascript
print("Int32 Bitwise XOR Tests (values outside int8 range)\n")
print(128 ^ 0, "\n")
print(128 ^ 128, "\n")
print(256 ^ 255, "\n")
print(1000 ^ 500, "\n")
print(65535 ^ 255, "\n")
print(0xFFFF ^ 0x00FF, "\n")
print(1000000 ^ 1000000, "\n")
print(2147483647 ^ 0, "\n")
```

### bitwise_xor.expect
```
Int32 Bitwise XOR Tests (values outside int8 range)
128
0
511
540
65280
65280
0
2147483647
```

## Test: division

### division.fg
```javascript
print("Int32 Division Tests (returns decimal, values outside int8 range)\n")
print(128 / 1, "\n")
print(256 / 2, "\n")
print(1000 / 3, "\n")
print(10000 / 7, "\n")
print(1000000 / 1000, "\n")
print(-129 / 2, "\n")
print(-1000 / 3, "\n")
print(-1000 / -3, "\n")
print(2147483647 / 2, "\n")
print(1000 / 400, "\n")
```

### division.expect
```
Int32 Division Tests (returns decimal, values outside int8 range)
128
128
333.3333435
1428.5714111
1000
-64.5
-333.3333435
333.3333435
1.073742e+09
2.5
```

## Test: equality

### equality.fg
```javascript
print("Int32 Equality Tests (values outside int8 range)\n")
print(128 == 128, "\n")
print(128 == 129, "\n")
print(1000 == 1000, "\n")
print(1000 == 1001, "\n")
print(-129 == -129, "\n")
print(-129 == 129, "\n")
print(1000000 == 1000000, "\n")
print(2147483647 == 2147483647, "\n")
print(-2147483648 == -2147483648, "\n")
```

### equality.expect
```
Int32 Equality Tests (values outside int8 range)
true
false
true
false
true
false
true
true
true
```

## Test: greater_than

### greater_than.fg
```javascript
print("Int32 Greater Than Tests (values outside int8 range)\n")
print(128 > 128, "\n")
print(128 > 129, "\n")
print(129 > 128, "\n")
print(1000 > 2000, "\n")
print(2000 > 1000, "\n")
print(-129 > 128, "\n")
print(128 > -129, "\n")
print(-500 > -1000, "\n")
print(-1000 > -500, "\n")
print(2000000 > 1000000, "\n")
```

### greater_than.expect
```
Int32 Greater Than Tests (values outside int8 range)
false
false
true
false
true
false
true
true
false
true
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Int32 Greater Than or Equal Tests (values outside int8 range)\n")
print(128 >= 128, "\n")
print(128 >= 129, "\n")
print(129 >= 128, "\n")
print(1000 >= 2000, "\n")
print(2000 >= 1000, "\n")
print(-129 >= 128, "\n")
print(128 >= -129, "\n")
print(-1000 >= -1000, "\n")
print(1000000 >= 1000000, "\n")
```

### greater_than_equal.expect
```
Int32 Greater Than or Equal Tests (values outside int8 range)
true
false
true
false
true
false
true
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Int32 Inequality Tests (values outside int8 range)\n")
print(128 != 128, "\n")
print(128 != 129, "\n")
print(1000 != 1000, "\n")
print(1000 != 1001, "\n")
print(-129 != -129, "\n")
print(-129 != 129, "\n")
print(1000000 != 1000000, "\n")
print(1000000 != 2000000, "\n")
```

### inequality.expect
```
Int32 Inequality Tests (values outside int8 range)
false
true
false
true
false
true
false
true
```

## Test: integer_division

### integer_division.fg
```javascript
print("Int32 Integer Division Tests (values outside int8 range)\n")
print(128 // 1, "\n")
print(256 // 2, "\n")
print(1000 // 3, "\n")
print(10000 // 7, "\n")
print(1000000 // 1000, "\n")
print(-129 // 2, "\n")
print(-1000 // 3, "\n")
print(-1000 // -3, "\n")
print(2147483647 // 2, "\n")
print(1000000000 // 7, "\n")
```

### integer_division.expect
```
Int32 Integer Division Tests (values outside int8 range)
128
128
333
1428
1000
-64
-333
333
1073741823
142857142
```

## Test: less_than

### less_than.fg
```javascript
print("Int32 Less Than Tests (values outside int8 range)\n")
print(128 < 128, "\n")
print(128 < 129, "\n")
print(129 < 128, "\n")
print(1000 < 2000, "\n")
print(2000 < 1000, "\n")
print(-129 < 128, "\n")
print(128 < -129, "\n")
print(-1000 < -500, "\n")
print(-500 < -1000, "\n")
print(1000000 < 2000000, "\n")
```

### less_than.expect
```
Int32 Less Than Tests (values outside int8 range)
false
true
false
true
false
true
false
true
false
true
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Int32 Less Than or Equal Tests (values outside int8 range)\n")
print(128 <= 128, "\n")
print(128 <= 129, "\n")
print(129 <= 128, "\n")
print(1000 <= 2000, "\n")
print(2000 <= 1000, "\n")
print(-129 <= 128, "\n")
print(128 <= -129, "\n")
print(-1000 <= -1000, "\n")
print(1000000 <= 1000000, "\n")
```

### less_than_equal.expect
```
Int32 Less Than or Equal Tests (values outside int8 range)
true
true
false
true
false
true
false
true
true
```

## Test: modulo

### modulo.fg
```javascript
print("Int32 Modulo Tests (values outside int8 range)\n")
print(128 % 1, "\n")
print(128 % 10, "\n")
print(1000 % 7, "\n")
print(10000 % 17, "\n")
print(1000000 % 1001, "\n")
print(-129 % 10, "\n")
print(-1000 % 7, "\n")
print(-1000 % -7, "\n")
print(2147483647 % 10, "\n")
print(1000000000 % 7, "\n")
```

### modulo.expect
```
Int32 Modulo Tests (values outside int8 range)
0
8
6
4
1
-9
-6
-6
7
6
```

## Test: multiplication

### multiplication.fg
```javascript
print("Int32 Multiplication Tests (values outside int8 range)\n")
print(128 * 0, "\n")
print(128 * 1, "\n")
print(128 * 2, "\n")
print(1000 * 1000, "\n")
print(500 * 500, "\n")
print(-129 * 1, "\n")
print(-500 * 3, "\n")
print(-200 * -200, "\n")
print(10000 * 10000, "\n")
print(46340 * 46340, "\n")
```

### multiplication.expect
```
Int32 Multiplication Tests (values outside int8 range)
0
128
256
1000000
250000
-129
-1500
40000
100000000
2147395600
```

## Test: subtraction

### subtraction.fg
```javascript
print("Int32 Subtraction Tests (values outside int8 range)\n")
print(128 - 0, "\n")
print(256 - 128, "\n")
print(3000 - 1000, "\n")
print(100000 - 50000, "\n")
print(1000000 - 500000, "\n")
print(-129 - 1, "\n")
print(-500 - 300, "\n")
print(-1000 - -2000, "\n")
print(2147483647 - 0, "\n")
print(-2147483648 - 0, "\n")
print(2000000000 - 1000000000, "\n")
```

### subtraction.expect
```
Int32 Subtraction Tests (values outside int8 range)
128
128
2000
50000
500000
-130
-800
1000
2147483647
-2147483648
1000000000
```

---

# Directory: BinaryOperationLiteralTests/int64_suffix

## Test: addition

### addition.fg
```javascript
print(10000l + 10000l, "\n")
/; EXPECT: 20000
```

### addition.expect
```
20000
```

## Test: bitwise_and

### bitwise_and.fg
```javascript
print(255l & 15l, "\n")
/; EXPECT: 15
```

### bitwise_and.expect
```
15
```

## Test: bitwise_or

### bitwise_or.fg
```javascript
print(240l | 15l, "\n")
/; EXPECT: 255
```

### bitwise_or.expect
```
255
```

## Test: bitwise_xor

### bitwise_xor.fg
```javascript
print(255l ^ 15l, "\n")
/; EXPECT: 240
```

### bitwise_xor.expect
```
240
```

## Test: comparison

### comparison.fg
```javascript
print(10000000000l > 5000000000l, "\n")
print(10000000000l < 5000000000l, "\n")
print(10000000000l == 10000000000l, "\n")
print(10000000000l != 5000000000l, "\n")
print(10000000000l >= 10000000000l, "\n")
print(10000000000l <= 10000000000l, "\n")
/; EXPECT: true
/; EXPECT: false
/; EXPECT: true
/; EXPECT: true
/; EXPECT: true
/; EXPECT: true
```

### comparison.expect
```
true
false
true
true
true
true
```

## Test: division

### division.fg
```javascript
print(10000000000l / 2l, "\n")
/; EXPECT: 5e+09
```

### division.expect
```
5000000000
```

## Test: hex_addition

### hex_addition.fg
```javascript
print(0xFFl + 0x10l, "\n")
/; EXPECT: 271
```

### hex_addition.expect
```
271
```

## Test: hex_multiplication

### hex_multiplication.fg
```javascript
print(0x10000l * 0x10000l, "\n")
/; EXPECT: 4294967296
```

### hex_multiplication.expect
```
4294967296
```

## Test: integer_division

### integer_division.fg
```javascript
print(10000000000l // 3l, "\n")
/; EXPECT: 3333333333
```

### integer_division.expect
```
3333333333
```

## Test: mixed_with_int32

### mixed_with_int32.fg
```javascript
print(10000l * 10000, "\n")
/; EXPECT: 100000000
```

### mixed_with_int32.expect
```
100000000
```

## Test: mixed_with_int8

### mixed_with_int8.fg
```javascript
print(10000000000l + 5, "\n")
/; EXPECT: 10000000005
```

### mixed_with_int8.expect
```
10000000005
```

## Test: modulo

### modulo.fg
```javascript
print(10000000001l % 10l, "\n")
/; EXPECT: 1
```

### modulo.expect
```
1
```

## Test: multiplication_large

### multiplication_large.fg
```javascript
print(100000l * 100000l, "\n")
/; EXPECT: 10000000000
```

### multiplication_large.expect
```
10000000000
```

## Test: multiplication_overflow_fix

### multiplication_overflow_fix.fg
```javascript
print(10000l * 10000l, "\n")
/; EXPECT: 100000000
```

### multiplication_overflow_fix.expect
```
100000000
```

## Test: negative_addition

### negative_addition.fg
```javascript
print(-10000000000l + 5000000000l, "\n")
/; EXPECT: -5000000000
```

### negative_addition.expect
```
-5000000000
```

## Test: negative_multiplication

### negative_multiplication.fg
```javascript
print(-10000l * 10000l, "\n")
/; EXPECT: -100000000
```

### negative_multiplication.expect
```
-100000000
```

## Test: small_value_as_int64

### small_value_as_int64.fg
```javascript
print(5l + 10l, "\n")
/; EXPECT: 15
```

### small_value_as_int64.expect
```
15
```

## Test: subtraction

### subtraction.fg
```javascript
print(10000000000l - 5000000000l, "\n")
/; EXPECT: 5000000000
```

### subtraction.expect
```
5000000000
```

## Test: zero_literal

### zero_literal.fg
```javascript
print(0l + 0l, "\n")
print(0l * 10000000000l, "\n")
/; EXPECT: 0
/; EXPECT: 0
```

### zero_literal.expect
```
0
0
```

---

# Directory: BinaryOperationLiteralTests/deci32

## Test: addition

### addition.fg
```javascript
print("Deci32 (Float) Addition Tests\n")
print(0.0f + 0.0f, "\n")
print(1.0f + 0.0f, "\n")
print(0.0f + 1.0f, "\n")
print(1.5f + 1.5f, "\n")
print(3.14f + 2.86f, "\n")
print(-1.5f + 1.5f, "\n")
print(-3.14f + -2.86f, "\n")
print(100.25f + 200.75f, "\n")
print(0.001f + 0.001f, "\n")
print(1234.5678f + 0.0f, "\n")
```

### addition.expect
```
Deci32 (Float) Addition Tests
0
1
1
3
6
0
-6
301
0.002
1234.567749
```

## Test: division

### division.fg
```javascript
print("Deci32 (Float) Division Tests\n")
print(0.0f / 1.0f, "\n")
print(1.0f / 1.0f, "\n")
print(6.0f / 2.0f, "\n")
print(5.0f / 2.0f, "\n")
print(10.0f / 3.0f, "\n")
print(-6.0f / 2.0f, "\n")
print(6.0f / -2.0f, "\n")
print(-6.0f / -2.0f, "\n")
print(3.14f / 2.0f, "\n")
print(1.0f / 4.0f, "\n")
```

### division.expect
```
Deci32 (Float) Division Tests
0
1
3
2.5
3.3333333
-3
-3
3
1.5700001
0.25
```

## Test: equality

### equality.fg
```javascript
print("Deci32 (Float) Equality Tests\n")
print(0.0f == 0.0f, "\n")
print(1.0f == 1.0f, "\n")
print(1.0f == 0.0f, "\n")
print(0.0f == 1.0f, "\n")
print(3.14f == 3.14f, "\n")
print(3.14f == 3.15f, "\n")
print(-1.5f == -1.5f, "\n")
print(-1.5f == 1.5f, "\n")
```

### equality.expect
```
Deci32 (Float) Equality Tests
true
true
false
false
true
false
true
false
```

## Test: greater_than

### greater_than.fg
```javascript
print("Deci32 (Float) Greater Than Tests\n")
print(0.0f > 0.0f, "\n")
print(0.0f > 1.0f, "\n")
print(1.0f > 0.0f, "\n")
print(1.0f > 1.0f, "\n")
print(3.14f > 3.15f, "\n")
print(3.15f > 3.14f, "\n")
print(-1.5f > 1.5f, "\n")
print(1.5f > -1.5f, "\n")
print(-1.0f > -2.0f, "\n")
print(-2.0f > -1.0f, "\n")
```

### greater_than.expect
```
Deci32 (Float) Greater Than Tests
false
false
true
false
false
true
false
true
true
false
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Deci32 (Float) Greater Than or Equal Tests\n")
print(0.0f >= 0.0f, "\n")
print(0.0f >= 1.0f, "\n")
print(1.0f >= 0.0f, "\n")
print(1.0f >= 1.0f, "\n")
print(3.14f >= 3.15f, "\n")
print(3.15f >= 3.14f, "\n")
print(-1.5f >= 1.5f, "\n")
print(1.5f >= -1.5f, "\n")
print(3.14f >= 3.14f, "\n")
```

### greater_than_equal.expect
```
Deci32 (Float) Greater Than or Equal Tests
true
false
true
true
false
true
false
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Deci32 (Float) Inequality Tests\n")
print(0.0f != 0.0f, "\n")
print(1.0f != 1.0f, "\n")
print(1.0f != 0.0f, "\n")
print(0.0f != 1.0f, "\n")
print(3.14f != 3.14f, "\n")
print(3.14f != 3.15f, "\n")
print(-1.5f != -1.5f, "\n")
print(-1.5f != 1.5f, "\n")
```

### inequality.expect
```
Deci32 (Float) Inequality Tests
false
false
true
true
false
true
false
true
```

## Test: less_than

### less_than.fg
```javascript
print("Deci32 (Float) Less Than Tests\n")
print(0.0f < 0.0f, "\n")
print(0.0f < 1.0f, "\n")
print(1.0f < 0.0f, "\n")
print(1.0f < 1.0f, "\n")
print(3.14f < 3.15f, "\n")
print(3.15f < 3.14f, "\n")
print(-1.5f < 1.5f, "\n")
print(1.5f < -1.5f, "\n")
print(-2.0f < -1.0f, "\n")
print(-1.0f < -2.0f, "\n")
```

### less_than.expect
```
Deci32 (Float) Less Than Tests
false
true
false
false
true
false
true
false
true
false
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Deci32 (Float) Less Than or Equal Tests\n")
print(0.0f <= 0.0f, "\n")
print(0.0f <= 1.0f, "\n")
print(1.0f <= 0.0f, "\n")
print(1.0f <= 1.0f, "\n")
print(3.14f <= 3.15f, "\n")
print(3.15f <= 3.14f, "\n")
print(-1.5f <= 1.5f, "\n")
print(1.5f <= -1.5f, "\n")
print(3.14f <= 3.14f, "\n")
```

### less_than_equal.expect
```
Deci32 (Float) Less Than or Equal Tests
true
true
false
true
true
false
true
false
true
```

## Test: multiplication

### multiplication.fg
```javascript
print("Deci32 (Float) Multiplication Tests\n")
print(0.0f * 0.0f, "\n")
print(1.0f * 0.0f, "\n")
print(0.0f * 1.0f, "\n")
print(1.0f * 1.0f, "\n")
print(2.0f * 3.0f, "\n")
print(1.5f * 2.0f, "\n")
print(-1.5f * 2.0f, "\n")
print(-2.0f * -3.0f, "\n")
print(3.14f * 2.0f, "\n")
print(0.5f * 0.5f, "\n")
```

### multiplication.expect
```
Deci32 (Float) Multiplication Tests
0
0
0
1
6
3
-3
6
6.2800002
0.25
```

## Test: subtraction

### subtraction.fg
```javascript
print("Deci32 (Float) Subtraction Tests\n")
print(0.0f - 0.0f, "\n")
print(1.0f - 0.0f, "\n")
print(0.0f - 1.0f, "\n")
print(3.0f - 1.5f, "\n")
print(3.14f - 2.86f, "\n")
print(-1.5f - 1.5f, "\n")
print(-3.14f - -2.86f, "\n")
print(100.25f - 200.75f, "\n")
print(0.002f - 0.001f, "\n")
print(1234.5678f - 1234.5678f, "\n")
```

### subtraction.expect
```
Deci32 (Float) Subtraction Tests
0
1
-1
1.5
0.2800002
-3
-0.2800002
-100.5
0.001
0
```

---

# Directory: BinaryOperationLiteralTests/nir

## Test: equality

### equality.fg
```javascript
print("Nir (Null) Equality Tests\n")
print(null == null, "\n")
```

### equality.expect
```
Nir (Null) Equality Tests
true
```

## Test: inequality

### inequality.fg
```javascript
print("Nir (Null) Inequality Tests\n")
print(null != null, "\n")
```

### inequality.expect
```
Nir (Null) Inequality Tests
false
```

---

# Directory: BinaryOperationLiteralTests/bool

## Test: complex

### complex.fg
```javascript
print("Bool Complex Expressions Tests\n")
print((true && true) || false, "\n")
print((true || false) && true, "\n")
print((false || false) && true, "\n")
print((true && false) || (false && true), "\n")
print((true || true) && (false || true), "\n")
print(true && (false || true), "\n")
print(false || (true && true), "\n")
print((true == true) && (false == false), "\n")
print((true != false) || (false != true), "\n")
```

### complex.expect
```
Bool Complex Expressions Tests
true
true
false
false
true
true
true
true
true
```

## Test: equality

### equality.fg
```javascript
print("Bool Equality Tests\n")
print(true == true, "\n")
print(true == false, "\n")
print(false == true, "\n")
print(false == false, "\n")
```

### equality.expect
```
Bool Equality Tests
true
false
false
true
```

## Test: greater_than

### greater_than.fg
```javascript
print("Bool Greater Than Tests\n")
print(true > true, "\n")
print(true > false, "\n")
print(false > true, "\n")
print(false > false, "\n")
```

### greater_than.expect
```
Bool Greater Than Tests
false
true
false
false
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Bool Greater Than or Equal Tests\n")
print(true >= true, "\n")
print(true >= false, "\n")
print(false >= true, "\n")
print(false >= false, "\n")
```

### greater_than_equal.expect
```
Bool Greater Than or Equal Tests
true
true
false
true
```

## Test: inequality

### inequality.fg
```javascript
print("Bool Inequality Tests\n")
print(true != true, "\n")
print(true != false, "\n")
print(false != true, "\n")
print(false != false, "\n")
```

### inequality.expect
```
Bool Inequality Tests
false
true
true
false
```

## Test: less_than

### less_than.fg
```javascript
print("Bool Less Than Tests\n")
print(true < true, "\n")
print(true < false, "\n")
print(false < true, "\n")
print(false < false, "\n")
```

### less_than.expect
```
Bool Less Than Tests
false
false
true
false
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Bool Less Than or Equal Tests\n")
print(true <= true, "\n")
print(true <= false, "\n")
print(false <= true, "\n")
print(false <= false, "\n")
```

### less_than_equal.expect
```
Bool Less Than or Equal Tests
true
false
true
true
```

## Test: logical_and

### logical_and.fg
```javascript
print("Bool Logical AND Tests\n")
print(true && true, "\n")
print(true && false, "\n")
print(false && true, "\n")
print(false && false, "\n")
```

### logical_and.expect
```
Bool Logical AND Tests
true
false
false
false
```

## Test: logical_or

### logical_or.fg
```javascript
print("Bool Logical OR Tests\n")
print(true || true, "\n")
print(true || false, "\n")
print(false || true, "\n")
print(false || false, "\n")
```

### logical_or.expect
```
Bool Logical OR Tests
true
true
true
false
```

---

# Directory: BinaryOperationLiteralTests/int8

## Test: addition

### addition.fg
```javascript
print("Int8 Addition Tests\n")
print(0 + 0, "\n")
print(1 + 0, "\n")
print(0 + 1, "\n")
print(1 + 1, "\n")
print(5 + 3, "\n")
print(10 + 20, "\n")
print(50 + 50, "\n")
print(-1 + 1, "\n")
print(-5 + 3, "\n")
print(-10 + -20, "\n")
print(127 + 0, "\n")
print(-128 + 0, "\n")
```

### addition.expect
```
Int8 Addition Tests
0
1
1
2
8
30
100
0
-2
-30
127
-128
```

## Test: bitwise

### bitwise.fg
```javascript
print("Int8 Bitwise AND Tests\n")
print(0 & 0, "\n")
print(1 & 0, "\n")
print(0 & 1, "\n")
print(1 & 1, "\n")
print(5 & 3, "\n")
print(15 & 7, "\n")
print(127 & 64, "\n")
print("Int8 Bitwise OR Tests\n")
print(0 | 0, "\n")
print(1 | 0, "\n")
print(0 | 1, "\n")
print(1 | 1, "\n")
print(5 | 3, "\n")
print(15 | 7, "\n")
print(64 | 32, "\n")
print("Int8 Bitwise XOR Tests\n")
print(0 ^ 0, "\n")
print(1 ^ 0, "\n")
print(0 ^ 1, "\n")
print(1 ^ 1, "\n")
print(5 ^ 3, "\n")
print(15 ^ 7, "\n")
print(127 ^ 64, "\n")
```

### bitwise.expect
```
Int8 Bitwise AND Tests
0
0
0
1
1
7
64
Int8 Bitwise OR Tests
0
1
1
1
7
15
96
Int8 Bitwise XOR Tests
0
1
1
0
6
8
63
```

## Test: bitwise_and

### bitwise_and.fg
```javascript
print("Int8 Bitwise AND Tests\n")
print(0 & 0, "\n")
print(1 & 0, "\n")
print(0 & 1, "\n")
print(1 & 1, "\n")
print(5 & 3, "\n")
print(15 & 7, "\n")
print(127 & 64, "\n")
print(127 & 0, "\n")
print(-1 & 127, "\n")
```

### bitwise_and.expect
```
Int8 Bitwise AND Tests
0
0
0
1
1
7
64
0
127
```

## Test: bitwise_or

### bitwise_or.fg
```javascript
print("Int8 Bitwise OR Tests\n")
print(0 | 0, "\n")
print(1 | 0, "\n")
print(0 | 1, "\n")
print(1 | 1, "\n")
print(5 | 3, "\n")
print(15 | 7, "\n")
print(64 | 32, "\n")
print(0 | 127, "\n")
print(64 | 63, "\n")
```

### bitwise_or.expect
```
Int8 Bitwise OR Tests
0
1
1
1
7
15
96
127
127
```

## Test: bitwise_xor

### bitwise_xor.fg
```javascript
print("Int8 Bitwise XOR Tests\n")
print(0 ^ 0, "\n")
print(1 ^ 0, "\n")
print(0 ^ 1, "\n")
print(1 ^ 1, "\n")
print(5 ^ 3, "\n")
print(15 ^ 7, "\n")
print(127 ^ 64, "\n")
print(127 ^ 127, "\n")
print(85 ^ 42, "\n")
```

### bitwise_xor.expect
```
Int8 Bitwise XOR Tests
0
1
1
0
6
8
63
0
127
```

## Test: comparison

### comparison.fg
```javascript
print("Int8 Comparison Tests\n")
print("Equality:\n")
print(0 == 0, "\n")
print(1 == 1, "\n")
print(1 == 0, "\n")
print(127 == 127, "\n")
print(-128 == -128, "\n")
print("Inequality:\n")
print(0 != 0, "\n")
print(1 != 0, "\n")
print(127 != -128, "\n")
print("Less Than:\n")
print(0 < 1, "\n")
print(1 < 0, "\n")
print(-128 < 127, "\n")
print("Less Than or Equal:\n")
print(0 <= 0, "\n")
print(0 <= 1, "\n")
print(1 <= 0, "\n")
print("Greater Than:\n")
print(1 > 0, "\n")
print(0 > 1, "\n")
print(127 > -128, "\n")
print("Greater Than or Equal:\n")
print(0 >= 0, "\n")
print(1 >= 0, "\n")
print(0 >= 1, "\n")
```

### comparison.expect
```
Int8 Comparison Tests
Equality:
true
true
false
true
true
Inequality:
false
true
true
Less Than:
true
false
true
Less Than or Equal:
true
true
false
Greater Than:
true
false
true
Greater Than or Equal:
true
true
false
```

## Test: division

### division.fg
```javascript
print("Int8 Division Tests (returns decimal)\n")
print(0 / 1, "\n")
print(1 / 1, "\n")
print(5 / 2, "\n")
print(10 / 3, "\n")
print(20 / 4, "\n")
print(100 / 7, "\n")
print(-10 / 3, "\n")
print(10 / -3, "\n")
print(-10 / -3, "\n")
print(7 / 2, "\n")
print(1 / 4, "\n")
```

### division.expect
```
Int8 Division Tests (returns decimal)
0
1
2.5
3.3333333
5
14.2857141
-3.3333333
-3.3333333
3.3333333
3.5
0.25
```

## Test: equality

### equality.fg
```javascript
print("Int8 Equality Tests\n")
print(0 == 0, "\n")
print(1 == 1, "\n")
print(1 == 0, "\n")
print(0 == 1, "\n")
print(127 == 127, "\n")
print(-128 == -128, "\n")
print(127 == -128, "\n")
print(-1 == -1, "\n")
print(50 == 50, "\n")
```

### equality.expect
```
Int8 Equality Tests
true
true
false
false
true
true
false
true
true
```

## Test: greater_than

### greater_than.fg
```javascript
print("Int8 Greater Than Tests\n")
print(0 > 0, "\n")
print(0 > 1, "\n")
print(1 > 0, "\n")
print(-128 > 127, "\n")
print(127 > -128, "\n")
print(-50 > 50, "\n")
print(50 > -50, "\n")
print(-5 > -10, "\n")
print(-10 > -5, "\n")
```

### greater_than.expect
```
Int8 Greater Than Tests
false
false
true
false
true
false
true
true
false
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Int8 Greater Than or Equal Tests\n")
print(0 >= 0, "\n")
print(0 >= 1, "\n")
print(1 >= 0, "\n")
print(-128 >= 127, "\n")
print(127 >= -128, "\n")
print(-50 >= 50, "\n")
print(50 >= 50, "\n")
print(-10 >= -10, "\n")
```

### greater_than_equal.expect
```
Int8 Greater Than or Equal Tests
true
false
true
false
true
false
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Int8 Inequality Tests\n")
print(0 != 0, "\n")
print(1 != 1, "\n")
print(1 != 0, "\n")
print(0 != 1, "\n")
print(127 != -128, "\n")
print(-128 != 127, "\n")
print(-1 != 1, "\n")
print(50 != 50, "\n")
```

### inequality.expect
```
Int8 Inequality Tests
false
false
true
true
true
true
true
false
```

## Test: integer_division

### integer_division.fg
```javascript
print("Int8 Integer Division Tests\n")
print(0 // 1, "\n")
print(1 // 1, "\n")
print(5 // 3, "\n")
print(10 // 3, "\n")
print(20 // 4, "\n")
print(100 // 7, "\n")
print(-10 // 3, "\n")
print(10 // -3, "\n")
print(-10 // -3, "\n")
print(99 // 10, "\n")
print(127 // 10, "\n")
```

### integer_division.expect
```
Int8 Integer Division Tests
0
1
1
3
5
14
-3
-3
3
9
12
```

## Test: less_than

### less_than.fg
```javascript
print("Int8 Less Than Tests\n")
print(0 < 0, "\n")
print(0 < 1, "\n")
print(1 < 0, "\n")
print(-128 < 127, "\n")
print(127 < -128, "\n")
print(-50 < 50, "\n")
print(50 < -50, "\n")
print(-10 < -5, "\n")
print(-5 < -10, "\n")
```

### less_than.expect
```
Int8 Less Than Tests
false
true
false
true
false
true
false
true
false
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Int8 Less Than or Equal Tests\n")
print(0 <= 0, "\n")
print(0 <= 1, "\n")
print(1 <= 0, "\n")
print(-128 <= 127, "\n")
print(127 <= -128, "\n")
print(-50 <= 50, "\n")
print(50 <= 50, "\n")
print(-10 <= -10, "\n")
```

### less_than_equal.expect
```
Int8 Less Than or Equal Tests
true
true
false
true
false
true
true
true
```

## Test: modulo

### modulo.fg
```javascript
print("Int8 Modulo Tests\n")
print(0 % 1, "\n")
print(1 % 1, "\n")
print(5 % 3, "\n")
print(10 % 3, "\n")
print(20 % 4, "\n")
print(100 % 7, "\n")
print(-10 % 3, "\n")
print(10 % -3, "\n")
print(-10 % -3, "\n")
print(99 % 10, "\n")
print(127 % 10, "\n")
print(17 % 5, "\n")
```

### modulo.expect
```
Int8 Modulo Tests
0
0
2
1
0
2
-1
1
-1
9
7
2
```

## Test: multiplication

### multiplication.fg
```javascript
print("Int8 Multiplication Tests\n")
print(0 * 0, "\n")
print(1 * 0, "\n")
print(0 * 1, "\n")
print(1 * 1, "\n")
print(5 * 3, "\n")
print(10 * 10, "\n")
print(-1 * 1, "\n")
print(-5 * 3, "\n")
print(-10 * -10, "\n")
print(2 * 3 * 4, "\n")
print(-2 * -3 * -4, "\n")
```

### multiplication.expect
```
Int8 Multiplication Tests
0
0
0
1
15
100
-1
-15
100
24
-24
```

## Test: subtraction

### subtraction.fg
```javascript
print("Int8 Subtraction Tests\n")
print(0 - 0, "\n")
print(1 - 0, "\n")
print(0 - 1, "\n")
print(1 - 1, "\n")
print(5 - 3, "\n")
print(10 - 20, "\n")
print(100 - 50, "\n")
print(-1 - 1, "\n")
print(-5 - 3, "\n")
print(-10 - -20, "\n")
print(127 - 0, "\n")
print(-128 - 0, "\n")
```

### subtraction.expect
```
Int8 Subtraction Tests
0
1
-1
0
2
-10
50
-2
-8
10
127
-128
```

---

# Directory: BinaryOperationLiteralTests/mixed_types

## Test: bitwise_mixed

### bitwise_mixed.fg
```javascript
print("Mixed Integer Bitwise Tests\n")
print("Int8 & Int32:\n")
print(15 & 255, "\n")
print(255 & 15, "\n")
print(127 & 128, "\n")
print("Int8 | Int32:\n")
print(15 | 256, "\n")
print(256 | 15, "\n")
print(127 | 128, "\n")
print("Int8 ^ Int32:\n")
print(15 ^ 255, "\n")
print(255 ^ 15, "\n")
print(127 ^ 128, "\n")
print("Int32 & Int64:\n")
print(255 & 3000000000, "\n")
print(3000000000 & 255, "\n")
print("Int32 | Int64:\n")
print(255 | 3000000000, "\n")
print(3000000000 | 255, "\n")
```

### bitwise_mixed.expect
```
Mixed Integer Bitwise Tests
Int8 & Int32:
15
15
0
Int8 | Int32:
271
271
255
Int8 ^ Int32:
240
240
255
Int32 & Int64:
0
0
Int32 | Int64:
3000000255
3000000255
```

## Test: char_and_string

### char_and_string.fg
```javascript
print("Char and String Mixed Operations\n")
print('H' + "ello", "\n")
print("Hell" + 'o', "\n")
print('a' + "bc", "\n")
print("ab" + 'c', "\n")
print(' ' + "space before", "\n")
print("space after" + ' ', "\n")
print('1' + "23", "\n")
print("12" + '3', "\n")
```

### char_and_string.expect
```
Char and String Mixed Operations
Hello
Hello
abc
abc
 space before
space after 
123
123
```

## Test: complex_expressions

### complex_expressions.fg
```javascript
print("Complex Mixed Type Expressions\n")
print((1 + 2) * (3.0 + 4.0), "\n")
print((10 / 3) * 2.0f, "\n")
print("Result: " + (1 + 2 + 3), "\n")
print("Pi * 2 = " + (3.14 * 2), "\n")
print("1 + 2 = " + (1 + 2), "\n")
print((true && false) + " is the result", "\n")
print("Sum: " + (1 + 2 + 3 + 4 + 5), "\n")
```

### complex_expressions.expect
```
Complex Mixed Type Expressions
21
6.6666665
Result: 6
Pi * 2 = 6.28
1 + 2 = 3
false is the result
Sum: 15
```

## Test: float_and_double

### float_and_double.fg
```javascript
print("Float and Double Mixed Operations\n")
print("Addition:\n")
print(1.5f + 1.5, "\n")
print(1.5 + 1.5f, "\n")
print("Subtraction:\n")
print(5.5f - 1.5, "\n")
print(5.5 - 1.5f, "\n")
print("Multiplication:\n")
print(2.0f * 1.5, "\n")
print(2.0 * 1.5f, "\n")
print("Division:\n")
print(5.0f / 2.0, "\n")
print(5.0 / 2.0f, "\n")
```

### float_and_double.expect
```
Float and Double Mixed Operations
Addition:
3
3
Subtraction:
4
4
Multiplication:
3
3
Division:
2.5
2.5
```

## Test: int32_and_decimal

### int32_and_decimal.fg
```javascript
print("Int32 and Decimal Mixed Operations\n")
print("Int32 + Double:\n")
print(1000 + 1.5, "\n")
print(1.5 + 1000, "\n")
print(-1000 + 1.5, "\n")
print("Int32 + Float:\n")
print(1000 + 1.5f, "\n")
print(1.5f + 1000, "\n")
print(-1000 + 1.5f, "\n")
print("Int32 - Double:\n")
print(1000 - 1.5, "\n")
print(1.5 - 1000, "\n")
print("Int32 * Double:\n")
print(1000 * 1.5, "\n")
print(1.5 * 1000, "\n")
print("Int32 / Double:\n")
print(1000 / 1.5, "\n")
print(1.5 / 1000, "\n")
```

### int32_and_decimal.expect
```
Int32 and Decimal Mixed Operations
Int32 + Double:
1001.5
1001.5
-998.5
Int32 + Float:
1001.5
1001.5
-998.5
Int32 - Double:
998.5
-998.5
Int32 * Double:
1500
1500
Int32 / Double:
666.666666666666629
0.0015
```

## Test: int32_and_int64

### int32_and_int64.fg
```javascript
print("Int32 and Int64 Mixed Operations\n")
print("Addition:\n")
print(1000000 + 3000000000, "\n")
print(3000000000 + 1000000, "\n")
print(2147483647 + 3000000000, "\n")
print("Subtraction:\n")
print(1000000 - 3000000000, "\n")
print(3000000000 - 1000000, "\n")
print("Multiplication:\n")
print(1000 * 3000000000, "\n")
print(-1000 * 3000000000, "\n")
print("Division:\n")
print(1000000 / 3000000000, "\n")
print(3000000000 / 1000000, "\n")
print("Integer Division:\n")
print(1000000 // 3000000000, "\n")
print(3000000000 // 1000000, "\n")
print("Modulo:\n")
print(1000000 % 3000000000, "\n")
print(3000000000 % 1000000, "\n")
```

### int32_and_int64.expect
```
Int32 and Int64 Mixed Operations
Addition:
3001000000
3001000000
5147483647
Subtraction:
-2999000000
2999000000
Multiplication:
3000000000000
-3000000000000
Division:
0.000333333333333
3000
Integer Division:
0
3000
Modulo:
1000000
0
```

## Test: int64_and_decimal

### int64_and_decimal.fg
```javascript
print("Int64 and Decimal Mixed Operations\n")
print("Addition:\n")
print(3000000000 + 1.5, "\n")
print(1.5 + 3000000000, "\n")
print(3000000000 + 1.5f, "\n")
print(1.5f + 3000000000, "\n")
print("Subtraction:\n")
print(3000000000 - 1.5, "\n")
print(3000000001.5 - 3000000000, "\n")
print("Multiplication:\n")
print(3000000000 * 1.5, "\n")
print(1.5 * 3000000000, "\n")
print("Division:\n")
print(3000000000 / 2.0, "\n")
print(6000000000.0 / 3000000000, "\n")
```

### int64_and_decimal.expect
```
Int64 and Decimal Mixed Operations
Addition:
3000000001.5
3000000001.5
3000000001.5
3000000001.5
Subtraction:
2999999998.5
1.5
Multiplication:
4500000000
4500000000
Division:
1500000000
2
```

## Test: int8_and_decimal

### int8_and_decimal.fg
```javascript
print("Int8 and Decimal Mixed Operations\n")
print("Int8 + Double:\n")
print(10 + 1.5, "\n")
print(1.5 + 10, "\n")
print(-10 + 1.5, "\n")
print(1.5 + -10, "\n")
print("Int8 + Float:\n")
print(10 + 1.5f, "\n")
print(1.5f + 10, "\n")
print(-10 + 1.5f, "\n")
print(1.5f + -10, "\n")
print("Int8 - Double:\n")
print(10 - 1.5, "\n")
print(1.5 - 10, "\n")
print("Int8 * Double:\n")
print(10 * 1.5, "\n")
print(1.5 * 10, "\n")
print("Int8 / Double:\n")
print(10 / 1.5, "\n")
print(1.5 / 10, "\n")
```

### int8_and_decimal.expect
```
Int8 and Decimal Mixed Operations
Int8 + Double:
11.5
11.5
-8.5
-8.5
Int8 + Float:
11.5
11.5
-8.5
-8.5
Int8 - Double:
8.5
-8.5
Int8 * Double:
15
15
Int8 / Double:
6.666666666666667
0.15
```

## Test: int8_and_int32

### int8_and_int32.fg
```javascript
print("Int8 and Int32 Mixed Operations\n")
print("Addition:\n")
print(10 + 1000, "\n")
print(1000 + 10, "\n")
print(127 + 128, "\n")
print(-128 + 1000, "\n")
print("Subtraction:\n")
print(10 - 1000, "\n")
print(1000 - 10, "\n")
print(127 - 128, "\n")
print("Multiplication:\n")
print(10 * 1000, "\n")
print(100 * 100, "\n")
print(-10 * 1000, "\n")
print("Division:\n")
print(10 / 1000, "\n")
print(1000 / 10, "\n")
print("Integer Division:\n")
print(10 // 1000, "\n")
print(1000 // 10, "\n")
print("Modulo:\n")
print(10 % 1000, "\n")
print(1000 % 10, "\n")
```

### int8_and_int32.expect
```
Int8 and Int32 Mixed Operations
Addition:
1010
1010
255
872
Subtraction:
-990
990
-1
Multiplication:
10000
10000
-10000
Division:
0.01
100
Integer Division:
0
100
Modulo:
10
0
```

## Test: int8_and_int64

### int8_and_int64.fg
```javascript
print("Int8 and Int64 Mixed Operations\n")
print("Addition:\n")
print(10 + 3000000000, "\n")
print(3000000000 + 10, "\n")
print(127 + 3000000000, "\n")
print(-128 + 3000000000, "\n")
print("Subtraction:\n")
print(10 - 3000000000, "\n")
print(3000000000 - 10, "\n")
print("Multiplication:\n")
print(10 * 3000000000, "\n")
print(-10 * 3000000000, "\n")
print("Division:\n")
print(10 / 3000000000, "\n")
print(3000000000 / 10, "\n")
print("Integer Division:\n")
print(10 // 3000000000, "\n")
print(3000000000 // 10, "\n")
print("Modulo:\n")
print(10 % 3000000000, "\n")
print(3000000000 % 10, "\n")
```

### int8_and_int64.expect
```
Int8 and Int64 Mixed Operations
Addition:
3000000010
3000000010
3000000127
2999999872
Subtraction:
-2999999990
2999999990
Multiplication:
30000000000
-30000000000
Division:
3.33333333333333e-09
300000000
Integer Division:
0
300000000
Modulo:
10
0
```

## Test: int_and_double

### int_and_double.fg
```javascript
print("Int and Double Mixed Operations\n")
print("Addition:\n")
print(1 + 1.5, "\n")
print(1.5 + 1, "\n")
print(10 + 0.5, "\n")
print(0.5 + 10, "\n")
print("Subtraction:\n")
print(5 - 1.5, "\n")
print(5.5 - 2, "\n")
print("Multiplication:\n")
print(2 * 1.5, "\n")
print(1.5 * 2, "\n")
print("Division:\n")
print(5 / 2.0, "\n")
print(5.0 / 2, "\n")
```

### int_and_double.expect
```
Int and Double Mixed Operations
Addition:
2.5
2.5
10.5
10.5
Subtraction:
3.5
3.5
Multiplication:
3
3
Division:
2.5
2.5
```

## Test: int_and_float

### int_and_float.fg
```javascript
print("Int and Float Mixed Operations\n")
print("Addition:\n")
print(1 + 1.5f, "\n")
print(1.5f + 1, "\n")
print(10 + 0.5f, "\n")
print(0.5f + 10, "\n")
print("Subtraction:\n")
print(5 - 1.5f, "\n")
print(5.5f - 2, "\n")
print("Multiplication:\n")
print(2 * 1.5f, "\n")
print(1.5f * 2, "\n")
print("Division:\n")
print(5 / 2.0f, "\n")
print(5.0f / 2, "\n")
```

### int_and_float.expect
```
Int and Float Mixed Operations
Addition:
2.5
2.5
10.5
10.5
Subtraction:
3.5
3.5
Multiplication:
3
3
Division:
2.5
2.5
```

## Test: int_comparison

### int_comparison.fg
```javascript
print("Mixed Integer Comparison Tests\n")
print("Int8 vs Int32:\n")
print(10 == 1000, "\n")
print(10 != 1000, "\n")
print(10 < 1000, "\n")
print(1000 < 10, "\n")
print(10 <= 1000, "\n")
print(10 > 1000, "\n")
print(1000 > 10, "\n")
print(10 >= 1000, "\n")
print("Int8 vs Int64:\n")
print(10 == 3000000000, "\n")
print(10 < 3000000000, "\n")
print(3000000000 > 10, "\n")
print("Int32 vs Int64:\n")
print(1000000 == 3000000000, "\n")
print(1000000 < 3000000000, "\n")
print(3000000000 > 1000000, "\n")
```

### int_comparison.expect
```
Mixed Integer Comparison Tests
Int8 vs Int32:
false
true
true
false
true
false
true
false
Int8 vs Int64:
false
true
true
Int32 vs Int64:
false
true
true
```

## Test: string_and_bool

### string_and_bool.fg
```javascript
print("String and Bool Mixed Operations\n")
print("Value: " + true, "\n")
print(true + " is true", "\n")
print("Value: " + false, "\n")
print(false + " is false", "\n")
print("Result: " + (1 == 1), "\n")
print((1 != 1) + " is false", "\n")
```

### string_and_bool.expect
```
String and Bool Mixed Operations
Value: true
true is true
Value: false
false is false
Result: true
false is false
```

## Test: string_and_decimal

### string_and_decimal.fg
```javascript
print("String and Decimal Mixed Operations\n")
print("Pi: " + 3.14, "\n")
print(3.14 + " is pi", "\n")
print("Float: " + 3.14f, "\n")
print(3.14f + " is float", "\n")
print("Zero: " + 0.0, "\n")
print(0.0 + " is zero", "\n")
```

### string_and_decimal.expect
```
String and Decimal Mixed Operations
Pi: 3.14
3.14 is pi
Float: 3.1400001
3.1400001 is float
Zero: 0
0 is zero
```

## Test: string_and_int

### string_and_int.fg
```javascript
print("String and Int Mixed Operations\n")
print("Hello" + 42, "\n")
print(42 + "World", "\n")
print("Number: " + 0, "\n")
print(0 + " is zero", "\n")
print("Negative: " + -1, "\n")
print(-1 + " is negative", "\n")
print("Large: " + 2147483647, "\n")
```

### string_and_int.expect
```
String and Int Mixed Operations
Hello42
42World
Number: 0
0 is zero
Negative: -1
-1 is negative
Large: 2147483647
```

---

# Directory: BinaryOperationLiteralTests/string

## Test: char_concatenation

### char_concatenation.fg
```javascript
print("String with Char Concatenation Tests\n")
print("Hello" + 'W' + "orld", "\n")
print('H' + "ello" + ' ' + "World", "\n")
print("A" + 'B' + "C" + 'D', "\n")
print('a' + 'b' + "cd", "\n")
print("ab" + 'c' + 'd', "\n")
```

### char_concatenation.expect
```
String with Char Concatenation Tests
HelloWorld
Hello World
ABCD
abcd
abcd
```

## Test: concatenation

### concatenation.fg
```javascript
print("String Concatenation Tests\n")
print("" + "", "\n")
print("Hello" + "", "\n")
print("" + "World", "\n")
print("Hello" + "World", "\n")
print("Hello" + " " + "World", "\n")
print("a" + "b" + "c" + "d", "\n")
print("The answer is: " + "42", "\n")
print("Line1\n" + "Line2", "\n")
```

### concatenation.expect
```
String Concatenation Tests

Hello
World
HelloWorld
Hello World
abcd
The answer is: 42
Line1
Line2
```

## Test: concatenation_with_types

### concatenation_with_types.fg
```javascript
print("String Concatenation with Other Types Tests\n")
print("Value: " + 42, "\n")
print("Value: " + -42, "\n")
print("Value: " + 3.14, "\n")
print("Value: " + 3.14f, "\n")
print("Value: " + true, "\n")
print("Value: " + false, "\n")
print(42 + " is the answer", "\n")
print(-42 + " is negative", "\n")
print(3.14 + " is pi", "\n")
print(3.14f + " is float pi", "\n")
print(true + " is true", "\n")
print(false + " is false", "\n")
```

### concatenation_with_types.expect
```
String Concatenation with Other Types Tests
Value: 42
Value: -42
Value: 3.14
Value: 3.1400001
Value: true
Value: false
42 is the answer
-42 is negative
3.14 is pi
3.1400001 is float pi
true is true
false is false
```

## Test: equality

### equality.fg
```javascript
print("String Equality Tests\n")
print("" == "", "\n")
print("Hello" == "Hello", "\n")
print("Hello" == "World", "\n")
print("World" == "Hello", "\n")
print("hello" == "Hello", "\n")
print("abc" == "abc", "\n")
print("abc" == "ABC", "\n")
print(" " == " ", "\n")
print("  " == " ", "\n")
```

### equality.expect
```
String Equality Tests
true
true
false
false
false
true
false
true
false
```

## Test: greater_than

### greater_than.fg
```javascript
print("String Greater Than Tests\n")
print("" > "", "\n")
print("" > "a", "\n")
print("a" > "", "\n")
print("a" > "a", "\n")
print("a" > "b", "\n")
print("b" > "a", "\n")
print("abc" > "abd", "\n")
print("abcd" > "abc", "\n")
print("a" > "A", "\n")
print("Z" > "a", "\n")
```

### greater_than.expect
```
String Greater Than Tests
false
false
true
false
false
true
false
true
true
false
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("String Greater Than or Equal Tests\n")
print("" >= "", "\n")
print("" >= "a", "\n")
print("a" >= "", "\n")
print("a" >= "a", "\n")
print("a" >= "b", "\n")
print("b" >= "a", "\n")
print("abc" >= "abc", "\n")
print("abd" >= "abc", "\n")
print("abcd" >= "abc", "\n")
```

### greater_than_equal.expect
```
String Greater Than or Equal Tests
true
false
true
true
false
true
true
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("String Inequality Tests\n")
print("" != "", "\n")
print("Hello" != "Hello", "\n")
print("Hello" != "World", "\n")
print("World" != "Hello", "\n")
print("hello" != "Hello", "\n")
print("abc" != "abc", "\n")
print("abc" != "ABC", "\n")
print(" " != " ", "\n")
print("  " != " ", "\n")
```

### inequality.expect
```
String Inequality Tests
false
false
true
true
true
false
true
false
true
```

## Test: less_than

### less_than.fg
```javascript
print("String Less Than Tests\n")
print("" < "", "\n")
print("" < "a", "\n")
print("a" < "", "\n")
print("a" < "a", "\n")
print("a" < "b", "\n")
print("b" < "a", "\n")
print("abc" < "abd", "\n")
print("abc" < "abcd", "\n")
print("A" < "a", "\n")
print("z" < "A", "\n")
```

### less_than.expect
```
String Less Than Tests
false
true
false
false
true
false
true
true
true
false
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("String Less Than or Equal Tests\n")
print("" <= "", "\n")
print("" <= "a", "\n")
print("a" <= "", "\n")
print("a" <= "a", "\n")
print("a" <= "b", "\n")
print("b" <= "a", "\n")
print("abc" <= "abc", "\n")
print("abc" <= "abd", "\n")
print("abc" <= "abcd", "\n")
```

### less_than_equal.expect
```
String Less Than or Equal Tests
true
true
false
true
true
false
true
true
true
```

---

# Directory: BinaryOperationLiteralTests/errors

## Test: bool_addition

### bool_addition.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true + true)
```

## Test: bool_and_char_eq

### bool_and_char_eq.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true == 'a')
```

## Test: bool_and_decimal_add

### bool_and_decimal_add.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true + 1.0)
```

## Test: bool_and_int_add

### bool_and_int_add.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true + 1)
```

## Test: bool_and_nir

### bool_and_nir.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true + null)
```

## Test: bool_bitwise_and

### bool_bitwise_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true & false)
```

## Test: bool_bitwise_or

### bool_bitwise_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true | false)
```

## Test: bool_bitwise_xor

### bool_bitwise_xor.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true ^ false)
```

## Test: bool_division

### bool_division.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true / false)
```

## Test: bool_modulo

### bool_modulo.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true % false)
```

## Test: bool_multiplication

### bool_multiplication.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true * false)
```

## Test: bool_subtraction

### bool_subtraction.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true - false)
```

## Test: char_bitwise_and

### char_bitwise_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' & 'b')
```

## Test: char_bitwise_or

### char_bitwise_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' | 'b')
```

## Test: char_bitwise_xor

### char_bitwise_xor.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' ^ 'b')
```

## Test: char_logical_and

### char_logical_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' && 'b')
```

## Test: char_logical_or

### char_logical_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' || 'b')
```

## Test: char_modulo

### char_modulo.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' % 'b')
```

## Test: char_multiplication

### char_multiplication.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' * 'b')
```

## Test: char_subtraction

### char_subtraction.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print('a' - 'b')
```

## Test: decimal_bitwise_and

### decimal_bitwise_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(3.14 & 2.0)
```

## Test: decimal_bitwise_or

### decimal_bitwise_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(3.14 | 2.0)
```

## Test: decimal_bitwise_xor

### decimal_bitwise_xor.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(3.14 ^ 2.0)
```

## Test: decimal_integer_division

### decimal_integer_division.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(3.14 // 2.0)
```

## Test: decimal_logical_and

### decimal_logical_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(1.0 && 2.0)
```

## Test: decimal_logical_or

### decimal_logical_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(1.0 || 2.0)
```

## Test: decimal_modulo

### decimal_modulo.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(3.14 % 2.0)
```

## Test: float_modulo

### float_modulo.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(3.14f % 2.0f)
```

## Test: int_and_nir

### int_and_nir.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(1 + null)
```

## Test: int_logical_and

### int_logical_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(1 && 2)
```

## Test: int_logical_or

### int_logical_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(1 || 2)
```

## Test: integer_overflow_literal

### integer_overflow_literal.fg
```javascript
/; EXPECT_ERROR: NumberTooLargeForInt
print(99999999999999999999999999999999999999999)
```

## Test: integer_overflow_negative

### integer_overflow_negative.fg
```javascript
/; EXPECT_ERROR: NumberTooLargeForInt
print(-9223372036854775809)
```

## Test: integer_overflow_positive

### integer_overflow_positive.fg
```javascript
/; EXPECT_ERROR: NumberTooLargeForInt
print(922337203685477580822)
```

## Test: nir_addition

### nir_addition.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(null + null)
```

## Test: nir_and_char

### nir_and_char.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(null + 'a')
```

## Test: nir_greater_than

### nir_greater_than.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(null > null)
```

## Test: nir_less_than

### nir_less_than.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(null < null)
```

## Test: nir_multiplication

### nir_multiplication.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(null * null)
```

## Test: nir_subtraction

### nir_subtraction.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(null - null)
```

## Test: string_and_char_mul

### string_and_char_mul.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" * 'a')
```

## Test: string_and_nir

### string_and_nir.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" + null)
```

## Test: string_bitwise_and

### string_bitwise_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" & "World")
```

## Test: string_bitwise_or

### string_bitwise_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" | "World")
```

## Test: string_bitwise_xor

### string_bitwise_xor.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" ^ "World")
```

## Test: string_division

### string_division.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" / "World")
```

## Test: string_logical_and

### string_logical_and.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" && "World")
```

## Test: string_logical_or

### string_logical_or.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" || "World")
```

## Test: string_modulo

### string_modulo.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" % "World")
```

## Test: string_multiplication

### string_multiplication.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" * "World")
```

## Test: string_subtraction

### string_subtraction.fg
```javascript
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print("Hello" - "World")
```

---

# Directory: BinaryOperationLiteralTests/int64

## Test: addition

### addition.fg
```javascript
print("Int64 Addition Tests (using large numbers)\n")
print(3000000000 + 0, "\n")
print(3000000000 + 1, "\n")
print(3000000000 + 3000000000, "\n")
print(9223372036854775807 + 0, "\n")
print(-9223372036854775808 + 0, "\n")
print(-3000000000 + 3000000000, "\n")
print(5000000000 + 5000000000, "\n")
```

### addition.expect
```
Int64 Addition Tests (using large numbers)
3000000000
3000000001
6000000000
9223372036854775807
-9223372036854775808
0
10000000000
```

## Test: bitwise_and

### bitwise_and.fg
```javascript
print("Int64 Bitwise AND Tests\n")
print(3000000000 & 0, "\n")
print(3000000000 & 3000000000, "\n")
print(3000000000 & 1500000000, "\n")
print(0xFFFFFFFFFF & 0x0F0F0F0F0F, "\n")
print(4294967295 & 4294967295, "\n")
```

### bitwise_and.expect
```
Int64 Bitwise AND Tests
0
3000000000
272633344
64677154575
4294967295
```

## Test: bitwise_or

### bitwise_or.fg
```javascript
print("Int64 Bitwise OR Tests\n")
print(3000000000 | 0, "\n")
print(3000000000 | 3000000000, "\n")
print(3000000000 | 1500000000, "\n")
print(0xF0F0F0F0F0 | 0x0F0F0F0F0F, "\n")
print(4294967295 | 1, "\n")
```

### bitwise_or.expect
```
Int64 Bitwise OR Tests
3000000000
3000000000
4227366656
1099511627775
4294967295
```

## Test: bitwise_xor

### bitwise_xor.fg
```javascript
print("Int64 Bitwise XOR Tests\n")
print(3000000000 ^ 0, "\n")
print(3000000000 ^ 3000000000, "\n")
print(3000000000 ^ 1500000000, "\n")
print(0xF0F0F0F0F0 ^ 0x0F0F0F0F0F, "\n")
print(4294967295 ^ 4294967295, "\n")
```

### bitwise_xor.expect
```
Int64 Bitwise XOR Tests
3000000000
0
3954733312
1099511627775
0
```

## Test: comparison

### comparison.fg
```javascript
print("Int64 Comparison Tests\n")
print("Equality:\n")
print(3000000000 == 3000000000, "\n")
print(3000000000 == 3000000001, "\n")
print("Inequality:\n")
print(3000000000 != 3000000000, "\n")
print(3000000000 != 3000000001, "\n")
print("Less Than:\n")
print(3000000000 < 3000000001, "\n")
print(3000000001 < 3000000000, "\n")
print("Less Than or Equal:\n")
print(3000000000 <= 3000000000, "\n")
print(3000000000 <= 3000000001, "\n")
print("Greater Than:\n")
print(3000000001 > 3000000000, "\n")
print(3000000000 > 3000000001, "\n")
print("Greater Than or Equal:\n")
print(3000000000 >= 3000000000, "\n")
print(3000000001 >= 3000000000, "\n")
```

### comparison.expect
```
Int64 Comparison Tests
Equality:
true
false
Inequality:
false
true
Less Than:
true
false
Less Than or Equal:
true
true
Greater Than:
true
false
Greater Than or Equal:
true
true
```

## Test: division

### division.fg
```javascript
print("Int64 Division Tests (returns decimal)\n")
print(3000000000 / 1, "\n")
print(3000000000 / 2, "\n")
print(3000000000 / 3, "\n")
print(9000000000 / 4, "\n")
print(-3000000000 / 2, "\n")
print(7 / 3000000000, "\n")
```

### division.expect
```
Int64 Division Tests (returns decimal)
3000000000
1500000000
1000000000
2250000000
-1500000000
2.33333333333333e-09
```

## Test: equality

### equality.fg
```javascript
print("Int64 Equality Tests\n")
print(3000000000 == 3000000000, "\n")
print(3000000000 == 3000000001, "\n")
print(9223372036854775807 == 9223372036854775807, "\n")
print(-9223372036854775808 == -9223372036854775808, "\n")
print(3000000000 == -3000000000, "\n")
```

### equality.expect
```
Int64 Equality Tests
true
false
true
true
false
```

## Test: greater_than

### greater_than.fg
```javascript
print("Int64 Greater Than Tests\n")
print(3000000000 > 3000000000, "\n")
print(3000000000 > 3000000001, "\n")
print(3000000001 > 3000000000, "\n")
print(-3000000000 > 3000000000, "\n")
print(3000000000 > -3000000000, "\n")
print(9223372036854775807 > -9223372036854775808, "\n")
```

### greater_than.expect
```
Int64 Greater Than Tests
false
false
true
false
true
true
```

## Test: greater_than_equal

### greater_than_equal.fg
```javascript
print("Int64 Greater Than or Equal Tests\n")
print(3000000000 >= 3000000000, "\n")
print(3000000000 >= 3000000001, "\n")
print(3000000001 >= 3000000000, "\n")
print(-3000000000 >= 3000000000, "\n")
print(3000000000 >= -3000000000, "\n")
print(9223372036854775807 >= -9223372036854775808, "\n")
```

### greater_than_equal.expect
```
Int64 Greater Than or Equal Tests
true
false
true
false
true
true
```

## Test: inequality

### inequality.fg
```javascript
print("Int64 Inequality Tests\n")
print(3000000000 != 3000000000, "\n")
print(3000000000 != 3000000001, "\n")
print(9223372036854775807 != -9223372036854775808, "\n")
print(3000000000 != -3000000000, "\n")
```

### inequality.expect
```
Int64 Inequality Tests
false
true
true
true
```

## Test: integer_division

### integer_division.fg
```javascript
print("Int64 Integer Division Tests\n")
print(3000000000 // 1, "\n")
print(3000000000 // 2, "\n")
print(3000000000 // 3, "\n")
print(9000000000 // 3, "\n")
print(-3000000000 // 2, "\n")
print(3000000000 // -2, "\n")
print(10000000000 // 7, "\n")
```

### integer_division.expect
```
Int64 Integer Division Tests
3000000000
1500000000
1000000000
3000000000
-1500000000
-1500000000
1428571428
```

## Test: less_than

### less_than.fg
```javascript
print("Int64 Less Than Tests\n")
print(3000000000 < 3000000000, "\n")
print(3000000000 < 3000000001, "\n")
print(3000000001 < 3000000000, "\n")
print(-3000000000 < 3000000000, "\n")
print(3000000000 < -3000000000, "\n")
print(-9223372036854775808 < 9223372036854775807, "\n")
```

### less_than.expect
```
Int64 Less Than Tests
false
true
false
true
false
true
```

## Test: less_than_equal

### less_than_equal.fg
```javascript
print("Int64 Less Than or Equal Tests\n")
print(3000000000 <= 3000000000, "\n")
print(3000000000 <= 3000000001, "\n")
print(3000000001 <= 3000000000, "\n")
print(-3000000000 <= 3000000000, "\n")
print(3000000000 <= -3000000000, "\n")
print(-9223372036854775808 <= 9223372036854775807, "\n")
```

### less_than_equal.expect
```
Int64 Less Than or Equal Tests
true
true
false
true
false
true
```

## Test: modulo

### modulo.fg
```javascript
print("Int64 Modulo Tests\n")
print(3000000000 % 1, "\n")
print(3000000000 % 7, "\n")
print(3000000000 % 100, "\n")
print(9000000001 % 3, "\n")
print(-3000000000 % 7, "\n")
print(3000000000 % -7, "\n")
```

### modulo.expect
```
Int64 Modulo Tests
0
4
0
1
-4
4
```

## Test: multiplication

### multiplication.fg
```javascript
print("Int64 Multiplication Tests (using large numbers)\n")
print(3000000000 * 0, "\n")
print(3000000000 * 1, "\n")
print(3000000000 * 2, "\n")
print(100000 * 100000, "\n")
print(-3000000000 * 2, "\n")
print(-3000000000 * -2, "\n")
```

### multiplication.expect
```
Int64 Multiplication Tests (using large numbers)
0
3000000000
6000000000
1410065408
-6000000000
6000000000
```

## Test: subtraction

### subtraction.fg
```javascript
print("Int64 Subtraction Tests (using large numbers)\n")
print(3000000000 - 0, "\n")
print(3000000000 - 1, "\n")
print(6000000000 - 3000000000, "\n")
print(9223372036854775807 - 0, "\n")
print(-9223372036854775808 - 0, "\n")
print(0 - 3000000000, "\n")
print(5000000000 - 10000000000, "\n")
```

### subtraction.expect
```
Int64 Subtraction Tests (using large numbers)
3000000000
2999999999
3000000000
9223372036854775807
-9223372036854775808
-3000000000
-5000000000
```

---

# Directory: IndexTests

## Test: index_2d

### index_2d.fg
```javascript
var a:int[2][3] = [[1,2,3],[4,5,6]]
println(a[0][1])
println(a[1][2])
a[0][1] = 99
println(a)
```

### index_2d.expect
```
2
6
[ [ 1, 99, 3 ], [ 4, 5, 6 ] ]
```

## Test: index_3d

### index_3d.fg
```javascript
var a:int[2][2][2] = [[[1,2],[3,4]],[[5,6],[7,8]]]
println(a[1][0][1])
a[1][0][1] = 99
println(a[1][0][1])
```

### index_3d.expect
```
6
99
```

## Test: index_assign_then_read

### index_assign_then_read.fg
```javascript
var a:int[3] = [1, 2, 3]
a[1] = 100
println(a[1])
println(a)
```

### index_assign_then_read.expect
```
100
[ 1, 100, 3 ]
```

## Test: index_basic_read

### index_basic_read.fg
```javascript
var a:int[5] = [10, 20, 30, 40, 50]
println(a[0])
println(a[2])
println(a[4])
```

### index_basic_read.expect
```
10
30
50
```

## Test: index_bool_array

### index_bool_array.fg
```javascript
var a:bool[4] = [true, false, true, false]
println(a[0])
println(a[3])
a[3] = true
println(a[3])
```

### index_bool_array.expect
```
true
false
true
```

## Test: index_dyn_array

### index_dyn_array.fg
```javascript
var a:[3] = ["hello", 42, true]
println(a[0])
println(a[1])
println(a[2])
a[0] = 3.14
println(a[0])
```

### index_dyn_array.expect
```
"hello"
42
true
3.14
```

## Test: index_dyn_multi_dim_error

### index_dyn_multi_dim_error.fg
```javascript
/; EXPECT_ERROR: IndexingMoreDimensionsThanArrayTypeHas
var d = "flow"
println(d[0][1])
```

## Test: index_dyn_nonint_index_error

### index_dyn_nonint_index_error.fg
```javascript
/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var d = "flow"
println(d[3.14])
```

## Test: index_dyn_not_str_error

### index_dyn_not_str_error.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot index a non-string dynamic value.
var d = 42
println(d[0])
```

## Test: index_dyn_not_str_write_error

### index_dyn_not_str_write_error.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot index a non-string dynamic value.
var x = 42
x[0] = 'z'
```

## Test: index_dyn_str

### index_dyn_str.fg
```javascript
var d = "flow"
println(d[0])
println(d[2])
```

### index_dyn_str.expect
```
f
o
```

## Test: index_dyn_str_mix_array

### index_dyn_str_mix_array.fg
```javascript
fun token() -> str {
  return "flow"
}

var d = token()
var a:int[3] = [10, 20, 30]
var i:int = 2

println(d[i])
d[i] = 'x'
println(d)

println(a[i])
a[i] = 99
println(a)
```

### index_dyn_str_mix_array.expect
```
o
"flxw"
30
[ 10, 20, 99 ]
```

## Test: index_dyn_str_write

### index_dyn_str_write.fg
```javascript
var x = "hello"
x[1] = 'a'
println(x)
```

### index_dyn_str_write.expect
```
"hallo"
```

## Test: index_dyn_str_write_oob

### index_dyn_str_write_oob.fg
```javascript
/; EXPECT_ERROR: Runtime Error: String Index Out of Bounds.
var x = "hello"
x[10] = 'z'
```

## Test: index_non_array_error

### index_non_array_error.fg
```javascript
/; EXPECT_ERROR: IndexingNonArrayTypeVariable
var x:int = 5
println(x[0])
```

## Test: index_nonint_error

### index_nonint_error.fg
```javascript
/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var a:int[2] = [1, 2]
var s:str = "idx"
println(a[s])
```

## Test: index_oob_1d

### index_oob_1d.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
var a:int[3] = [1,2,3]
println(a[5])
```

## Test: index_str_array

### index_str_array.fg
```javascript
var a:str[3] = ["a", "b", "c"]
println(a[1])
a[1] = "Z"
println(a[1])
```

### index_str_array.expect
```
b
Z
```

## Test: index_str_basic

### index_str_basic.fg
```javascript
var s: str = "hello"
println(s[0])
println(s[1])
println(s[4])
```

### index_str_basic.expect
```
h
e
o
```

## Test: index_str_from_func

### index_str_from_func.fg
```javascript
fun greeting() -> str {
  return "FlowWing"
}

var s: str = greeting()
println(s[0])
println(s[4])
println(s[7])
```

### index_str_from_func.expect
```
F
W
g
```

## Test: index_str_loop

### index_str_loop.fg
```javascript
var s: str = "world"
for (var i: int = 0 to 4) {
  println(s[i])
}
```

### index_str_loop.expect
```
w
o
r
l
d
```

## Test: index_str_mix_func_array

### index_str_mix_func_array.fg
```javascript
fun greeting() -> str {
  return "hello"
}

var s: str = greeting()
var a:int[3] = [1, 2, 3]
var i:int = 1

println(s[i])
s[i] = 'a'
println(s)

println(a[i])
a[i] = 9
println(a)
```

### index_str_mix_func_array.expect
```
e
hallo
2
[ 1, 9, 3 ]
```

## Test: index_str_mix_loop_write

### index_str_mix_loop_write.fg
```javascript
var s: str = "hello"

for (var i: int = 0 to 4) {
  println(s[i])
}

s[1] = 'a'
s[3] = 'p'
println(s)
```

### index_str_mix_loop_write.expect
```
h
e
l
l
o
halpo
```

## Test: index_str_multi_dim_error

### index_str_multi_dim_error.fg
```javascript
/; EXPECT_ERROR: IndexingMoreDimensionsThanArrayTypeHas
var s: str = "hello"
println(s[0][1])
```

## Test: index_str_nonint_index_error

### index_str_nonint_index_error.fg
```javascript
/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var s: str = "hello"
println(s[3.14])
```

## Test: index_str_oob

### index_str_oob.fg
```javascript
/; EXPECT_ERROR: Runtime Error: String Index Out of Bounds.
var s: str = "hi"
println(s[5])
```

## Test: index_str_write

### index_str_write.fg
```javascript
var x: str = "hello"
x[2] = 's'
println(x)
```

### index_str_write.expect
```
heslo
```

## Test: index_str_write_negative

### index_str_write_negative.fg
```javascript
/; EXPECT_ERROR: Runtime Error: String Index Out of Bounds.
var x: str = "hello"
x[-1] = 'z'
```

## Test: index_str_write_oob

### index_str_write_oob.fg
```javascript
/; EXPECT_ERROR: Runtime Error: String Index Out of Bounds.
var x: str = "hello"
x[10] = 'z'
```

## Test: index_with_var

### index_with_var.fg
```javascript
var a:int[4] = [5, 10, 15, 20]
var i:int = 2
println(a[i])
a[i] = 99
println(a[i])
println(a)
```

### index_with_var.expect
```
15
99
[ 5, 10, 99, 20 ]
```

---

# Directory: 01_conversion

## Test: basic

### basic.fg
```javascript
print("Int to String Conversion\n")
print(String(1), "\n")
print(String(3), "\n")
print(String(0), "\n")

print("Double to String Conversion\n")
print(String(1.0), "\n")
print(String(3.0), "\n")
print(String(2.5), "\n")
print(String(0.0), "\n")

print("Float to String Conversion\n")
print(String(1.0f), "\n")
print(String(3.0f), "\n")
print(String(2.5f), "\n")
print(String(0.0f), "\n")

print("Char to String Conversion\n")
print(String('a'), "\n" )
print(String('b'), "\n")
print(String('0'), "\n")

print("Bool to String Conversion\n")
print(String(true), "\n")
print(String(false), "\n")
```

### basic.expect
```
Int to String Conversion
1
3
0
Double to String Conversion
1
3
2.5
0
Float to String Conversion
1
3
2.5
0
Char to String Conversion
a
b
0
Bool to String Conversion
true
false
```

## Test: basic2

### basic2.fg
```javascript
print("Int to String Conversion\n")
print(String(1 + 1), "\n")
print(String(3 + 1), "\n")
print(String(0 + 1), "\n")

print("Double to String Conversion\n")
print(String(1.0 + 1.0), "\n")
print(String(3.0 + 1.0), "\n")
print(String(2.5 + 1.0), "\n")
print(String(0.0 + 1.0), "\n")

print("Float to String Conversion\n")
print(String(1.0f + 1.0f), "\n")
print(String(3.0f + 1.0f), "\n")
print(String(2.5f + 1.0f), "\n")
print(String(0.0f + 1.0f), "\n")

print("Char to String Conversion\n")
print(String('a'), "\n" )
print(String('b' + 'a'), "\n")
print(String('0' + '1'), "\n")
```

### basic2.expect
```
Int to String Conversion
2
4
1
Double to String Conversion
2
4
3.5
1
Float to String Conversion
2
4
3.5
1
Char to String Conversion
a
ba
01
```

## Test: basic_add

### basic_add.fg
```javascript
print("Int to String Conversion\n")
print(String(1 + 1), "\n")
print(String(3 + 1), "\n")
print(String(0 + 1), "\n")

print("Double to String Conversion\n")
print(String(1.0 + 1.0), "\n")
print(String(3.0 + 1.0), "\n")
print(String(2.5 + 1.0), "\n")
print(String(0.0 + 1.0), "\n")

print("Float to String Conversion\n")
print(String(1.0f + 1.0f), "\n")
print(String(3.0f + 1.0f), "\n")
print(String(2.5f + 1.0f), "\n")
print(String(0.0f + 1.0f), "\n")

print("Char to String Conversion\n")
print(String('a'), "\n" )
print(String('b' + 'a'), "\n")
print(String('0' + '1'), "\n")
```

### basic_add.expect
```
Int to String Conversion
2
4
1
Double to String Conversion
2
4
3.5
1
Float to String Conversion
2
4
3.5
1
Char to String Conversion
a
ba
01
```

## Test: indirect

### indirect.fg
```javascript
print("String to String Conversion\n")
print(String("Hello World"), "\n")
print(String(2/2), "\n")
print(String("25"), "\n")
```

### indirect.expect
```
String to String Conversion
Hello World
1
25
```

## Test: string_string

### string_string.fg
```javascript
print(String(String("Hello World")))
```

### string_string.expect
```
Hello World
```

---

# Directory: CodingProblems

## Test: 01_fizzbuzz

### 01_fizzbuzz.fg
```javascript
for (var i: int = 1 to 15 : 1) {
  if (i % 3 == 0 && i % 5 == 0) {
    println("FizzBuzz")
  } else if (i % 3 == 0) {
    println("Fizz")
  } else if (i % 5 == 0) {
    println("Buzz")
  } else {
    println(i)
  }
}
println("done")
```

### 01_fizzbuzz.expect
```
1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
done
```

## Test: 02_factorial_recursion

### 02_factorial_recursion.fg
```javascript
fun factorial(n: int) -> int {
  if (n == 0) {
    return 1
  }
  return n * factorial(n - 1)
}

println(factorial(5))
println(factorial(0))
println("done")
```

### 02_factorial_recursion.expect
```
120
1
done
```

## Test: 03_factorial_loop

### 03_factorial_loop.fg
```javascript
fun factorial(n: int) -> int {
  var fact: int = 1
  for (var i: int = 1 to n : 1) {
    fact = fact * i
  }
  return fact
}

println(factorial(5))
println(factorial(0))
println("done")
```

### 03_factorial_loop.expect
```
120
1
done
```

## Test: 04_fibonacci_recursion

### 04_fibonacci_recursion.fg
```javascript
fun fibonacci(n: int) -> int {
  if (n == 0) {
    return 0
  }
  if (n == 1) {
    return 1
  }
  return fibonacci(n - 1) + fibonacci(n - 2)
}

println(fibonacci(10))
println(fibonacci(0))
println(fibonacci(1))
println("done")
```

### 04_fibonacci_recursion.expect
```
55
0
1
done
```

## Test: 05_fibonacci_loop

### 05_fibonacci_loop.fg
```javascript
fun fibonacci(n: int) -> int {
  if (n <= 1) {
    return n
  }
  var a: int = 0
  var b: int = 1
  var c: int = 0
  for (var i: int = 2 to n : 1) {
    c = a + b
    a = b
    b = c
  }
  return b
}

println(fibonacci(10))
println(fibonacci(0))
println(fibonacci(1))
println("done")
```

### 05_fibonacci_loop.expect
```
55
0
1
done
```

## Test: 06_sum_n_recursion

### 06_sum_n_recursion.fg
```javascript
fun sumN(n: int) -> int {
  if (n == 0) {
    return 0
  }
  return n + sumN(n - 1)
}

println(sumN(10))
println(sumN(0))
println("done")
```

### 06_sum_n_recursion.expect
```
55
0
done
```

## Test: 07_sum_n_loop

### 07_sum_n_loop.fg
```javascript
fun sumN(n: int) -> int {
  var s: int = 0
  for (var i: int = 1 to n : 1) {
    s = s + i
  }
  return s
}

println(sumN(10))
println(sumN(0))
println("done")
```

### 07_sum_n_loop.expect
```
55
0
done
```

## Test: 08_gcd

### 08_gcd.fg
```javascript
fun gcd(a: int, b: int) -> int {
  if (b == 0) {
    return a
  }
  return gcd(b, a % b)
}

println(gcd(10, 15))
println(gcd(48, 18))
println(gcd(17, 19))
println("done")
```

### 08_gcd.expect
```
5
6
1
done
```

## Test: 09_power_recursion

### 09_power_recursion.fg
```javascript
fun power(base: int, exp: int) -> int {
  if (exp == 0) {
    return 1
  }
  return base * power(base, exp - 1)
}

println(power(2, 3))
println(power(5, 0))
println(power(10, 2))
println("done")
```

### 09_power_recursion.expect
```
8
1
100
done
```

## Test: 10_is_prime

### 10_is_prime.fg
```javascript
fun isPrime(n: int) -> bool {
  if (n <= 1) {
    return false
  }
  var i: int = 2
  while (i < n) {
    if (n % i == 0) {
      return false
    }
    i = i + 1
  }
  return true
}

println(isPrime(7))
println(isPrime(10))
println(isPrime(2))
println(isPrime(1))
println("done")
```

### 10_is_prime.expect
```
true
false
true
false
done
```

## Test: 11_sum_of_digits

### 11_sum_of_digits.fg
```javascript
fun sumOfDigits(n: int) -> int {
  if (n == 0) {
    return 0
  }
  return (n % 10) + sumOfDigits(n // 10)
}

println(sumOfDigits(123))
println(sumOfDigits(0))
println(sumOfDigits(999))
println("done")
```

### 11_sum_of_digits.expect
```
6
0
27
done
```

## Test: 12_reverse_number

### 12_reverse_number.fg
```javascript
fun reverseNum(n: int) -> int {
  var rev: int = 0
  var x: int = n
  while (x > 0) {
    rev = rev * 10 + (x % 10)
    x = x // 10
  }
  return rev
}

println(reverseNum(123))
println(reverseNum(121))
println(reverseNum(1))
println("done")
```

### 12_reverse_number.expect
```
321
121
1
done
```

## Test: 13_palindrome_number

### 13_palindrome_number.fg
```javascript
fun reverseNum(n: int) -> int {
  var rev: int = 0
  var x: int = n
  while (x > 0) {
    rev = rev * 10 + (x % 10)
    x = x // 10
  }
  return rev
}

fun isPalindrome(n: int) -> bool {
  return n == reverseNum(n)
}

println(isPalindrome(121))
println(isPalindrome(123))
println(isPalindrome(1))
println("done")
```

### 13_palindrome_number.expect
```
true
false
true
done
```

## Test: 14_count_digits

### 14_count_digits.fg
```javascript
fun countDigits(n: int) -> int {
  if (n == 0) {
    return 1
  }
  var c: int = 0
  var x: int = n
  if (x < 0) {
    x = -x
  }
  while (x > 0) {
    c = c + 1
    x = x // 10
  }
  return c
}

println(countDigits(12345))
println(countDigits(0))
println(countDigits(9))
println("done")
```

### 14_count_digits.expect
```
5
1
1
done
```

## Test: 15_is_even

### 15_is_even.fg
```javascript
fun isEven(n: int) -> bool {
  return n % 2 == 0
}

println(isEven(4))
println(isEven(7))
println(isEven(0))
println("done")
```

### 15_is_even.expect
```
true
false
true
done
```

---

# Directory: VecModuleTests

## Test: vec_e2e_test

### vec_e2e_test.fg
```javascript
bring vec

var list: vec::Vec = new vec::Vec()

println("--- Test 1: Push Mixed Types & Size ---")
list.push(10)
list.push("FlowWing")
list.push(3.14159)
list.push(true)
list.push('Z')

println(list.size())
println(list.get(0))
println(list.get(1))
println(list.get(2))
println(list.get(3))
println(list.get(4))

println("--- Test 2: Set & Out of Bounds Get ---")
list.set(1, "Replaced!") /; String replaces String
list.set(2, false)       /; Boolean replaces Float
println(list.get(1))
println(list.get(2))
println(list.get(999))   /; Out of bounds! Should return (null)

println("--- Test 3: Insert & RemoveAt ---")
list.insert(0, "First")  /; Shift everything right
println(list.get(0))
println(list.get(1))     /; 10 moved to index 1

var removed = list.removeAt(0)
println(removed)         /; Should be "First"
println(list.get(0))     /; 10 is back at index 0

println("--- Test 4: Pop, Clear, & isEmpty ---")
println(list.isEmpty())
println(list.pop())      /; Pops 'Z'
list.clear()
println(list.isEmpty())
println(list.size())
println(list.pop())      /; Popping empty list should safely return (null)

println("--- Test 5: Sorting Numbers (Ascending & Descending) ---")
list.clear().push(42).push(-5).push(100).push(0).push(3.14)
list.sort(true)
println(list.get(0)) /; -5
println(list.get(2)) /; 3.14
println(list.get(4)) /; 100

list.sort(false)
println(list.get(0)) /; 100
println(list.get(4)) /; -5

println("--- Test 6: Sorting Strings ---")
list.clear().push("Zebra").push("Apple").push("Mango")
list.sort(true)
println(list.get(0))
println(list.get(2))

println("--- Test 7: Array Reversal ---")
list.clear().push(1).push(2).push(3).push(4)
list.reverse()
println(list.get(0))
println(list.get(3))

println("--- Test 8: IndexOf (Searching Mixed Types) ---")
list.clear().push("Target").push(100).push(true).push('X')
println(list.indexOf(100))
println(list.indexOf(true))
println(list.indexOf('X'))
println(list.indexOf("Missing")) /; Not found, returns -1

println("--- Test 9: Mega Method Chaining ---")
list.clear().push(1).push(2).push(3).reverse().push(4).sort(false)
/; State flow:
/; 1. [1, 2, 3]
/; 2. reversed -> [3, 2, 1]
/; 3. push 4 -> [3, 2, 1, 4]
/; 4. sort desc -> [4, 3, 2, 1]
println(list.size())
println(list.get(0))
println(list.get(3))
```

### vec_e2e_test.expect
```
--- Test 1: Push Mixed Types & Size ---
5
10
"FlowWing"
3.14159
true
'Z'
--- Test 2: Set & Out of Bounds Get ---
"Replaced!"
false
null
--- Test 3: Insert & RemoveAt ---
"First"
10
"First"
10
--- Test 4: Pop, Clear, & isEmpty ---
false
'Z'
true
0
null
--- Test 5: Sorting Numbers (Ascending & Descending) ---
-5
3.14
100
100
-5
--- Test 6: Sorting Strings ---
"Apple"
"Zebra"
--- Test 7: Array Reversal ---
4
1
--- Test 8: IndexOf (Searching Mixed Types) ---
1
2
3
-1
--- Test 9: Mega Method Chaining ---
4
4
1
```

## Test: vec_mix_test

### vec_mix_test.fg
```javascript
bring Err
bring vec 

var list: vec::Vec = new vec::Vec()
list.push(1)
list.push(2)
list.push(3)

for var i: int = 0 to list.size() - 1 {
  println(list.get(i))
}

var err: Err::Result = Err::error("boom")
println(err.toString())
```

### vec_mix_test.expect
```
1
2
3
Error: boom
```

## Test: vec_mix_test_reverse

### vec_mix_test_reverse.fg
```javascript
bring vec 
bring Err

var list: vec::Vec = new vec::Vec()
list.push(1)
list.push(2)
list.push(3)

for var i: int = 0 to list.size() - 1 {
  println(list.get(i))
}

var err: Err::Result = Err::error("boom")
println(err.toString())
```

### vec_mix_test_reverse.expect
```
1
2
3
Error: boom
```

---

# Directory: TypeConversionFunctionTests/Decimal

## Test: from_bool

### from_bool.fg
```javascript
print(Decimal(true), "\n")
print(Decimal(false), "\n")
```

### from_bool.expect
```
1
0
```

## Test: from_char

### from_char.fg
```javascript
print(Decimal('A'), "\n")
print(Decimal('0'), "\n")
```

### from_char.expect
```
65
48
```

## Test: from_deci

### from_deci.fg
```javascript
print(Decimal(3.14159265359), "\n")
print(Decimal(-3.14159265359), "\n")
print(Decimal(0.0), "\n")
```

### from_deci.expect
```
3.14159265359
-3.14159265359
0
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(Decimal(3.14f), "\n")
print(Decimal(-3.14f), "\n")
print(Decimal(0.0f), "\n")
```

### from_deci32.expect
```
3.140000104904175
-3.140000104904175
0
```

## Test: from_int32

### from_int32.fg
```javascript
print(Decimal(1000), "\n")
print(Decimal(-1000), "\n")
print(Decimal(2147483647), "\n")
```

### from_int32.expect
```
1000
-1000
2147483647
```

## Test: from_int64

### from_int64.fg
```javascript
print(Decimal(10000000000l), "\n")
print(Decimal(-10000000000l), "\n")
```

### from_int64.expect
```
10000000000
-10000000000
```

## Test: from_int8

### from_int8.fg
```javascript
print(Decimal(1), "\n")
print(Decimal(127), "\n")
print(Decimal(-128), "\n")
```

### from_int8.expect
```
1
127
-128
```

## Test: from_string

### from_string.fg
```javascript
print(Decimal("3.14159"), "\n")
print(Decimal("-100.5"), "\n")
print(Decimal("0"), "\n")
```

### from_string.expect
```
3.14159
-100.5
0
```

---

# Directory: TypeConversionFunctionTests/Char

## Test: from_char

### from_char.fg
```javascript
print(Char('A'), "\n")
print(Char('z'), "\n")
print(Char(' '), "\n")
```

### from_char.expect
```
A
z
```

## Test: from_int32

### from_int32.fg
```javascript
print(Char(1000), "\n")
print(Char(255), "\n")
print(Char(32), "\n")
```

### from_int32.expect
```
Ϩ
ÿ
```

## Test: from_int64

### from_int64.fg
```javascript
print(Char(65l), "\n")
print(Char(90l), "\n")
```

### from_int64.expect
```
A
Z
```

## Test: from_int8

### from_int8.fg
```javascript
print(Char(65), "\n")
print(Char(97), "\n")
print(Char(48), "\n")
```

### from_int8.expect
```
A
a
0
```

## Test: from_string

### from_string.fg
```javascript
print(Char("😍"), "\n")
print(Char("A"), "\n")
print(Char("😄"), "\n")
```

### from_string.expect
```
😍
A
😄
```

---

# Directory: TypeConversionFunctionTests/Int32

## Test: from_bool

### from_bool.fg
```javascript
print(Int32(true), "\n")
print(Int32(false), "\n")
```

### from_bool.expect
```
1
0
```

## Test: from_char

### from_char.fg
```javascript
print(Int32('A'), "\n")
print(Int32('0'), "\n")
print(Int32('z'), "\n")
```

### from_char.expect
```
65
48
122
```

## Test: from_deci

### from_deci.fg
```javascript
print(Int32(3.14), "\n")
print(Int32(-3.99), "\n")
print(Int32(2147483647.9), "\n")
```

### from_deci.expect
```
3
-3
2147483647
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(Int32(3.14f), "\n")
print(Int32(-3.99f), "\n")
print(Int32(1000.5f), "\n")
```

### from_deci32.expect
```
3
-3
1000
```

## Test: from_int32

### from_int32.fg
```javascript
print(Int32(1000), "\n")
print(Int32(-1000), "\n")
print(Int32(2147483647), "\n")
print(Int32(-2147483648), "\n")
```

### from_int32.expect
```
1000
-1000
2147483647
-2147483648
```

## Test: from_int64

### from_int64.fg
```javascript
print(Int32(10000000000l), "\n")
print(Int32(100l), "\n")
print(Int32(-100l), "\n")
```

### from_int64.expect
```
1410065408
100
-100
```

## Test: from_int8

### from_int8.fg
```javascript
print(Int32(1), "\n")
print(Int32(127), "\n")
print(Int32(-128), "\n")
```

### from_int8.expect
```
1
127
-128
```

## Test: from_string

### from_string.fg
```javascript
print(Int32("42"), "\n")
print(Int32("-1000"), "\n")
print(Int32("0"), "\n")
```

### from_string.expect
```
42
-1000
0
```

---

# Directory: TypeConversionFunctionTests/scientific_notation

## Test: arithmetic

### arithmetic.fg
```javascript
print(1e3 + 1e2, "\n")
print(1e5 - 5e4, "\n")
print(2e2 * 3e1, "\n")
print(1e6 / 1e3, "\n")
```

### arithmetic.expect
```
1100
50000
6000
1000
```

## Test: basic

### basic.fg
```javascript
print(1e10, "\n")
print(1e5, "\n")
print(1e0, "\n")
print(5e2, "\n")
```

### basic.expect
```
10000000000
100000
1
500
```

## Test: comparison

### comparison.fg
```javascript
print(1e5 > 1e4, "\n")
print(1e-3 < 1e-2, "\n")
print(1e10 == 10000000000.0, "\n")
print(1e3 != 1e4, "\n")
```

### comparison.expect
```
true
true
true
true
```

## Test: conversion

### conversion.fg
```javascript
print(Int32(1e3), "\n")
print(Int64(1e10), "\n")
print(Decimal(1e5), "\n")
print(Decimal32(1e3f), "\n")
print(String(1e6), "\n")
```

### conversion.expect
```
1000
10000000000
100000
1000
1000000
```

## Test: float_suffix

### float_suffix.fg
```javascript
print(1e5f, "\n")
print(1.5e3f, "\n")
print(2.5e-2f, "\n")
```

### float_suffix.expect
```
100000
1500
0.025
```

## Test: large_exponent

### large_exponent.fg
```javascript
print(1e15, "\n")
print(1e20, "\n")
print(1e-15, "\n")
```

### large_exponent.expect
```
1e+15
1e+20
1e-15
```

## Test: negative_base

### negative_base.fg
```javascript
print(-1e5, "\n")
print(-2.5e3, "\n")
print(-1e-2, "\n")
```

### negative_base.expect
```
-100000
-2500
-0.01
```

## Test: negative_exponent

### negative_exponent.fg
```javascript
print(1e-1, "\n")
print(1e-3, "\n")
print(1e-5, "\n")
print(5e-2, "\n")
```

### negative_exponent.expect
```
0.1
0.001
0.00001
0.05
```

## Test: positive_exponent

### positive_exponent.fg
```javascript
print(1e+10, "\n")
print(1e+5, "\n")
print(2e+3, "\n")
```

### positive_exponent.expect
```
10000000000
100000
2000
```

## Test: uppercase_e

### uppercase_e.fg
```javascript
print(1E10, "\n")
print(1E5, "\n")
print(5E-2, "\n")
print(2E+3, "\n")
```

### uppercase_e.expect
```
10000000000
100000
0.05
2000
```

## Test: with_decimal

### with_decimal.fg
```javascript
print(1.5e10, "\n")
print(3.14e5, "\n")
print(2.5e-3, "\n")
print(9.99e0, "\n")
```

### with_decimal.expect
```
15000000000
314000
0.0025
9.99
```

## Test: zero_base

### zero_base.fg
```javascript
print(0e10, "\n")
print(0e-10, "\n")
print(0.0e5, "\n")
```

### zero_base.expect
```
0
0
0
```

---

# Directory: TypeConversionFunctionTests/edge_cases

## Test: bool_falsy

### bool_falsy.fg
```javascript
print(Bool(0), "\n")
print(Bool(0.0), "\n")
print(Bool(""), "\n")
```

### bool_falsy.expect
```
false
false
false
```

## Test: bool_truthy

### bool_truthy.fg
```javascript
print(Bool(1), "\n")
print(Bool(-1), "\n")
print(Bool(100), "\n")
print(Bool(0.001), "\n")
print(Bool(-0.001), "\n")
print(Bool('A'), "\n")
print(Bool("hello"), "\n")
```

### bool_truthy.expect
```
true
true
true
true
true
true
true
```

## Test: char_ascii

### char_ascii.fg
```javascript
print(Int32('A'), "\n")
print(Int32('Z'), "\n")
print(Int32('a'), "\n")
print(Int32('z'), "\n")
print(Int32('0'), "\n")
print(Int32('9'), "\n")
print(Int32(' '), "\n")
print(Int32('\n'), "\n")
```

### char_ascii.expect
```
65
90
97
122
48
57
32
10
```

## Test: char_unicode

### char_unicode.fg
```javascript
print(Char("A"), "\n")
print(Char("é"), "\n")
print(Char("中"), "\n")
print(Char("🚀"), "\n")
```

### char_unicode.expect
```
A
é
中
🚀
```

## Test: decimal_precision

### decimal_precision.fg
```javascript
print(Decimal(0.1), "\n")
print(Decimal(0.00001), "\n")
print(Decimal(1e10), "\n")
print(Decimal(1e-10), "\n")
```

### decimal_precision.expect
```
0.1
0.00001
10000000000
1e-10
```

## Test: decimal_truncation

### decimal_truncation.fg
```javascript
print(Int32(9.99), "\n")
print(Int32(-9.99), "\n")
print(Int32(0.1), "\n")
print(Int32(-0.1), "\n")
```

### decimal_truncation.expect
```
9
-9
0
0
```

## Test: int32_boundary

### int32_boundary.fg
```javascript
print(Int32(2147483647), "\n")
print(Int32(-2147483648), "\n")
print(Int32(0), "\n")
```

### int32_boundary.expect
```
2147483647
-2147483648
0
```

## Test: int64_boundary

### int64_boundary.fg
```javascript
print(Int64(9223372036854775807l), "\n")
print(Int64(0l), "\n")
```

### int64_boundary.expect
```
9223372036854775807
0
```

## Test: int8_boundary

### int8_boundary.fg
```javascript
print(Int8(127), "\n")
print(Int8(-128), "\n")
print(Int8(0), "\n")
```

### int8_boundary.expect
```
127
-128
0
```

## Test: int_overflow_wrap

### int_overflow_wrap.fg
```javascript
print(Int8(128), "\n")
print(Int8(256), "\n")
print(Int8(-129), "\n")
```

### int_overflow_wrap.expect
```
-128
0
127
```

## Test: string_empty

### string_empty.fg
```javascript
print(String(""), "\n")
print(Bool(""), "\n")
```

### string_empty.expect
```
false
```

## Test: string_numeric

### string_numeric.fg
```javascript
print(Int32("42"), "\n")
print(Int32("-999"), "\n")
print(Int64("9223372036854775807"), "\n")
print(Decimal("3.14159265358979"), "\n")
print(Decimal32("3.14"), "\n")
```

### string_numeric.expect
```
42
-999
9223372036854775807
3.14159265358979
3.1400001
```

---

# Directory: TypeConversionFunctionTests/Decimal32

## Test: from_bool

### from_bool.fg
```javascript
print(Decimal32(true), "\n")
print(Decimal32(false), "\n")
```

### from_bool.expect
```
1
0
```

## Test: from_char

### from_char.fg
```javascript
print(Decimal32('A'), "\n")
print(Decimal32('0'), "\n")
```

### from_char.expect
```
65
48
```

## Test: from_deci

### from_deci.fg
```javascript
print(Decimal32(3.14159), "\n")
print(Decimal32(-3.14159), "\n")
print(Decimal32(0.0), "\n")
```

### from_deci.expect
```
3.1415901
-3.1415901
0
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(Decimal32(3.14f), "\n")
print(Decimal32(-3.14f), "\n")
print(Decimal32(0.0f), "\n")
```

### from_deci32.expect
```
3.1400001
-3.1400001
0
```

## Test: from_int32

### from_int32.fg
```javascript
print(Decimal32(1000), "\n")
print(Decimal32(-1000), "\n")
print(Decimal32(0), "\n")
```

### from_int32.expect
```
1000
-1000
0
```

## Test: from_int64

### from_int64.fg
```javascript
print(Decimal32(1000000l), "\n")
print(Decimal32(-1000000l), "\n")
```

### from_int64.expect
```
1000000
-1000000
```

## Test: from_int8

### from_int8.fg
```javascript
print(Decimal32(1), "\n")
print(Decimal32(127), "\n")
print(Decimal32(-128), "\n")
```

### from_int8.expect
```
1
127
-128
```

## Test: from_string

### from_string.fg
```javascript
print(Decimal32("3.14"), "\n")
print(Decimal32("-100.5"), "\n")
print(Decimal32("0"), "\n")
```

### from_string.expect
```
3.1400001
-100.5
0
```

---

# Directory: TypeConversionFunctionTests/chained

## Test: bool_to_string_to_bool

### bool_to_string_to_bool.fg
```javascript
print(Bool(String(true)), "\n")
print(Bool(String(false)), "\n")
```

### bool_to_string_to_bool.expect
```
true
true
```

## Test: char_to_int_to_char

### char_to_int_to_char.fg
```javascript
print(Char(Int32('A')), "\n")
print(Char(Int32('z')), "\n")
print(Char(Int32('0')), "\n")
```

### char_to_int_to_char.expect
```
A
z
0
```

## Test: decimal32_decimal_chain

### decimal32_decimal_chain.fg
```javascript
print(Decimal(Decimal32(3.14f)), "\n")
print(Decimal32(Decimal(2.71828)), "\n")
```

### decimal32_decimal_chain.expect
```
3.140000104904175
2.7182801
```

## Test: decimal_to_int_to_decimal

### decimal_to_int_to_decimal.fg
```javascript
print(Decimal(Int32(3.99)), "\n")
print(Decimal(Int32(-3.99)), "\n")
```

### decimal_to_int_to_decimal.expect
```
3
-3
```

## Test: decimal_to_string_to_decimal

### decimal_to_string_to_decimal.fg
```javascript
print(Decimal(String(3.14159)), "\n")
print(Decimal(String(-2.5)), "\n")
```

### decimal_to_string_to_decimal.expect
```
3.14159
-2.5
```

## Test: int64_to_string_to_int64

### int64_to_string_to_int64.fg
```javascript
print(Int64(String(10000000000l)), "\n")
print(Int64(String(-10000000000l)), "\n")
```

### int64_to_string_to_int64.expect
```
10000000000
-10000000000
```

## Test: int8_int32_int64_chain

### int8_int32_int64_chain.fg
```javascript
print(Int64(Int32(Int8(100))), "\n")
print(Int8(Int32(Int64(50l))), "\n")
```

### int8_int32_int64_chain.expect
```
100
50
```

## Test: int_to_bool_to_int

### int_to_bool_to_int.fg
```javascript
print(Int32(Bool(42)), "\n")
print(Int32(Bool(0)), "\n")
print(Int32(Bool(-1)), "\n")
```

### int_to_bool_to_int.expect
```
1
0
1
```

## Test: int_to_decimal_to_int

### int_to_decimal_to_int.fg
```javascript
print(Int32(Decimal(42)), "\n")
print(Int32(Decimal(-100)), "\n")
```

### int_to_decimal_to_int.expect
```
42
-100
```

## Test: int_to_string_to_int

### int_to_string_to_int.fg
```javascript
print(Int32(String(42)), "\n")
print(Int32(String(-100)), "\n")
print(Int32(String(0)), "\n")
```

### int_to_string_to_int.expect
```
42
-100
0
```

## Test: invalid_input_for_int

### invalid_input_for_int.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Int conversion.
print(Int32(String(Bool(42))), "\n")
```

## Test: triple_chain

### triple_chain.fg
```javascript
print(Bool(Int32(String("1"))), "\n")
print(String(Int64(Decimal(12345.67))), "\n")
```

### triple_chain.expect
```
true
12345
```

---

# Directory: TypeConversionFunctionTests/runtime_errors

## Test: char_from_empty_string

### char_from_empty_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot convert empty string to Char.
print(Char(""))
```

## Test: char_from_multichar_string

### char_from_multichar_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: String contains more than one character.
print(Char("AB"))
```

## Test: decimal32_from_invalid_string

### decimal32_from_invalid_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Decimal32(Float) conversion.
print(Decimal32("abc"))
```

## Test: decimal_from_invalid_string

### decimal_from_invalid_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Decimal(Double) conversion.
print(Decimal("abc"))
```

## Test: decimal_from_special_chars

### decimal_from_special_chars.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Decimal(Double) conversion.
print(Decimal("!@#$"))
```

## Test: int32_from_float_string

### int32_from_float_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Int conversion.
print(Int32("3.14"))
```

## Test: int32_from_invalid_string

### int32_from_invalid_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Int conversion.
print(Int32("abc"))
```

## Test: int32_from_mixed_string

### int32_from_mixed_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Int conversion.
print(Int32("123abc"))
```

## Test: int64_from_float_string

### int64_from_float_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Long conversion.
print(Int64("3.14"))
```

## Test: int64_from_invalid_string

### int64_from_invalid_string.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Invalid input for Long conversion.
print(Int64("abc"))
```

---

# Directory: TypeConversionFunctionTests/Bool

## Test: from_bool

### from_bool.fg
```javascript
print(Bool(true), "\n")
print(Bool(false), "\n")
```

### from_bool.expect
```
true
false
```

## Test: from_char

### from_char.fg
```javascript
print(Bool('A'), "\n")
print(Bool('0'), "\n")
```

### from_char.expect
```
true
true
```

## Test: from_deci

### from_deci.fg
```javascript
print(Bool(3.14), "\n")
print(Bool(0.0), "\n")
print(Bool(-1.5), "\n")
```

### from_deci.expect
```
true
false
true
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(Bool(3.14f), "\n")
print(Bool(0.0f), "\n")
print(Bool(-1.5f), "\n")
```

### from_deci32.expect
```
true
false
true
```

## Test: from_int32

### from_int32.fg
```javascript
print(Bool(1000), "\n")
print(Bool(0), "\n")
print(Bool(-1000), "\n")
```

### from_int32.expect
```
true
false
true
```

## Test: from_int64

### from_int64.fg
```javascript
print(Bool(10000000000l), "\n")
print(Bool(0l), "\n")
print(Bool(-10000000000l), "\n")
```

### from_int64.expect
```
true
false
true
```

## Test: from_int8

### from_int8.fg
```javascript
print(Bool(1), "\n")
print(Bool(0), "\n")
print(Bool(-1), "\n")
print(Bool(127), "\n")
```

### from_int8.expect
```
true
false
true
true
```

## Test: from_string

### from_string.fg
```javascript
print(Bool("true"), "\n")
print(Bool("false"), "\n")
print(Bool("hello"), "\n")
print(Bool(""), "\n")
```

### from_string.expect
```
true
true
true
false
```

---

# Directory: TypeConversionFunctionTests/Int8

## Test: from_bool

### from_bool.fg
```javascript
print(Int8(true), "\n")
print(Int8(false), "\n")
```

### from_bool.expect
```
1
0
```

## Test: from_char

### from_char.fg
```javascript
print(Int8('A'), "\n")
print(Int8('0'), "\n")
print(Int8('z'), "\n")
```

### from_char.expect
```
65
48
122
```

## Test: from_deci

### from_deci.fg
```javascript
print(Int8(3.14), "\n")
print(Int8(-3.99), "\n")
print(Int8(127.9), "\n")
```

### from_deci.expect
```
3
-3
127
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(Int8(3.14f), "\n")
print(Int8(-3.99f), "\n")
print(Int8(100.5f), "\n")
```

### from_deci32.expect
```
3
-3
100
```

## Test: from_int32

### from_int32.fg
```javascript
print(Int8(1000), "\n")
print(Int8(-1000), "\n")
print(Int8(200), "\n")
```

### from_int32.expect
```
-24
24
-56
```

## Test: from_int64

### from_int64.fg
```javascript
print(Int8(10000000000l), "\n")
print(Int8(100l), "\n")
```

### from_int64.expect
```
0
100
```

## Test: from_int8

### from_int8.fg
```javascript
print(Int8(1), "\n")
print(Int8(127), "\n")
print(Int8(-128), "\n")
print(Int8(0), "\n")
```

### from_int8.expect
```
1
127
-128
0
```

## Test: from_string

### from_string.fg
```javascript
print(Int8("42"), "\n")
print(Int8("-100"), "\n")
print(Int8("0"), "\n")
```

### from_string.expect
```
42
-100
0
```

---

# Directory: TypeConversionFunctionTests/String

## Test: from_bool

### from_bool.fg
```javascript
print(String(true), "\n")
print(String(false), "\n")
```

### from_bool.expect
```
true
false
```

## Test: from_char

### from_char.fg
```javascript
print(String('A'), "\n")
print(String('z'), "\n")
print(String('0'), "\n")
print(String(' '), "\n")
```

### from_char.expect
```
A
z
0
```

## Test: from_deci

### from_deci.fg
```javascript
print(String(3.14159265359), "\n")
print(String(-3.14159265359), "\n")
print(String(0.0), "\n")
```

### from_deci.expect
```
3.14159265359
-3.14159265359
0
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(String(3.14f), "\n")
print(String(-3.14f), "\n")
print(String(0.0f), "\n")
```

### from_deci32.expect
```
3.1400001
-3.1400001
0
```

## Test: from_int32

### from_int32.fg
```javascript
print(String(1000), "\n")
print(String(-1000), "\n")
print(String(2147483647), "\n")
print(String(-2147483648), "\n")
```

### from_int32.expect
```
1000
-1000
2147483647
-2147483648
```

## Test: from_int64

### from_int64.fg
```javascript
print(String(10000000000l), "\n")
print(String(-10000000000l), "\n")
print(String(9223372036854775807l), "\n")
```

### from_int64.expect
```
10000000000
-10000000000
9223372036854775807
```

## Test: from_int8

### from_int8.fg
```javascript
print(String(1), "\n")
print(String(127), "\n")
print(String(-128), "\n")
print(String(0), "\n")
```

### from_int8.expect
```
1
127
-128
0
```

## Test: from_string

### from_string.fg
```javascript
print(String("Hello World"), "\n")
print(String(""), "\n")
print(String("123"), "\n")
```

### from_string.expect
```
Hello World

123
```

---

# Directory: TypeConversionFunctionTests/errors

## Test: bool_no_argument

### bool_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Bool())
```

## Test: char_from_bool

### char_from_bool.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
print(Char(true))
```

## Test: char_from_deci

### char_from_deci.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
print(Char(3.14))
```

## Test: char_from_deci32

### char_from_deci32.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
print(Char(3.14f))
```

## Test: char_no_argument

### char_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Char())
```

## Test: decimal32_no_argument

### decimal32_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Decimal32())
```

## Test: decimal_no_argument

### decimal_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Decimal())
```

## Test: int64_no_argument

### int64_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Int64())
```

## Test: int8_no_argument

### int8_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Int8())
```

## Test: no_argument

### no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Int32())
```

## Test: string_no_argument

### string_no_argument.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(String())
```

## Test: too_many_arguments

### too_many_arguments.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Int32(1, 2))
```

---

# Directory: TypeConversionFunctionTests/Int64

## Test: from_bool

### from_bool.fg
```javascript
print(Int64(true), "\n")
print(Int64(false), "\n")
```

### from_bool.expect
```
1
0
```

## Test: from_char

### from_char.fg
```javascript
print(Int64('A'), "\n")
print(Int64('0'), "\n")
print(Int64('z'), "\n")
```

### from_char.expect
```
65
48
122
```

## Test: from_deci

### from_deci.fg
```javascript
print(Int64(3.14), "\n")
print(Int64(-3.99), "\n")
print(Int64(9007199254740992.0), "\n")
```

### from_deci.expect
```
3
-3
9007199254740992
```

## Test: from_deci32

### from_deci32.fg
```javascript
print(Int64(3.14f), "\n")
print(Int64(-3.99f), "\n")
print(Int64(1000000.5f), "\n")
```

### from_deci32.expect
```
3
-3
1000000
```

## Test: from_int32

### from_int32.fg
```javascript
print(Int64(1000), "\n")
print(Int64(-1000), "\n")
print(Int64(2147483647), "\n")
```

### from_int32.expect
```
1000
-1000
2147483647
```

## Test: from_int64

### from_int64.fg
```javascript
print(Int64(10000000000l), "\n")
print(Int64(-10000000000l), "\n")
print(Int64(9223372036854775807l), "\n")
```

### from_int64.expect
```
10000000000
-10000000000
9223372036854775807
```

## Test: from_int8

### from_int8.fg
```javascript
print(Int64(1), "\n")
print(Int64(127), "\n")
print(Int64(-128), "\n")
```

### from_int8.expect
```
1
127
-128
```

## Test: from_string

### from_string.fg
```javascript
print(Int64("42"), "\n")
print(Int64("-1000000000000"), "\n")
print(Int64("0"), "\n")
```

### from_string.expect
```
42
-1000000000000
0
```

---

# Directory: 01_deci

## Test: add

### add.fg
```javascript
print("Double Addition\n")
print(1.3 + 1.2, "\n")
print(1.3 + 2.2, "\n")


print("Double / Int Addition\n")
print(1.3 + 1, "\n")
print(2 + 1.3, "\n")

print("Float Addition\n")
print(1.3f + 1.2f, "\n")
print(1.3f + 2.2f, "\n")


print("Float / Int Addition\n")
print(1.3f + 1, "\n")
print(2 + 1.3f, "\n")

print("Double / Float Addition\n")
print(1.3 + 1.2f, "\n")
print(2.2 + 1.3f, "\n")
```

### add.expect
```
Double Addition
2.5
3.5
Double / Int Addition
2.3
3.3
Float Addition
2.5
3.5
Float / Int Addition
2.3
3.3
Double / Float Addition
2.5
3.5
```

## Test: div

### div.fg
```javascript
print("Double Division\n")
print(1.3 / 1.2, "\n")
print(1.3 / 2.2, "\n")


print("Double / Int Multiplication\n")
print(1.3 / 1, "\n")
print(2 / 1.3, "\n")

print("Int Division\n")
print(1 / 2, "\n")
print(1 / 3, "\n")
print(2 / 4, "\n")
print(2 / 3, "\n")

print("Float Division\n")
print(1.3f / 1.2f, "\n")
print(1.3f / 2.2f, "\n")

print("Float / Int Division\n")
print(1.3f / 1, "\n")
print(2 / 1.3f, "\n")

print("Double / Float Division\n")
print(1.3 / 1.2f, "\n")
print(2.2 / 1.3f, "\n")
```

### div.expect
```
Double Division
1.083333333333333
0.590909090909091
Double / Int Multiplication
1.3
1.538461538461538
Int Division
0.5
0.3333333
0.5
0.6666667
Float Division
1.0833333
0.5909091
Float / Int Division
1.3
1.5384616
Double / Float Division
1.0833333
1.6923078
```

## Test: mul

### mul.fg
```javascript
print("Double Multiplication\n")
print(1.3 * 1.2, "\n")
print(1.3 * 2.2, "\n")


print("Double / Int Multiplication\n")
print(1.3 * 1, "\n")
print(2 * 1.3, "\n")

print("Float Multiplication\n")
print(1.3f * 1.2f, "\n")
print(1.3f * 2.2f, "\n")

print("Float / Int Multiplication\n")
print(1.3f * 1, "\n")
print(2 * 1.3f, "\n")

print("Double / Float Multiplication\n")
print(1.3 * 1.2f, "\n")
print(2.2 * 1.3f, "\n")
print(3.3f * 4.4, "\n")
```

### mul.expect
```
Double Multiplication
1.56
2.86
Double / Int Multiplication
1.3
2.6
Float Multiplication
1.5600001
2.8599999
Float / Int Multiplication
1.3
2.5999999
Double / Float Multiplication
1.5600001
2.8599999
14.5200005
```

## Test: sub

### sub.fg
```javascript
print("Double Subtraction\n")
print(1.3 - 1.2, "\n")
print(1.3 - 2.2, "\n")


print("Double / Int Subtraction\n")
print(1.3 - 1, "\n")
print(2 - 1.3, "\n")

print("Float Subtraction\n")
print(1.3f - 1.2f, "\n")
print(1.3f - 2.2f, "\n")

print("Float / Int Subtraction\n")
print(1.3f - 1, "\n")
print(2 - 1.3f, "\n")

print("Double / Float Subtraction\n")
print(1.3 - 1.2f, "\n")
print(2.2 - 1.3f, "\n")
```

### sub.expect
```
Double Subtraction
0.1
-0.9
Double / Int Subtraction
0.3
0.7
Float Subtraction
0.0999999
-0.9000001
Float / Int Subtraction
0.3
0.7
Double / Float Subtraction
0.0999999
0.9000001
```

---

# Directory: SwitchTests/06_scope

## Test: scope_assign_from_func_in_case

### scope_assign_from_func_in_case.fg
```javascript
fun getVal() -> int {
  return 7
}

var a: int = 1
var x: int = 0

switch a {
  case 1:{
    x = getVal()
    println(x)
  }
  default:{
    println(0)
  }
}
println(x)
```

### scope_assign_from_func_in_case.expect
```
7
7
```

## Test: scope_assign_in_case

### scope_assign_in_case.fg
```javascript
var x: int = 0
var a: int = 1

switch a {
  case 1:{
    x = 10
    println(x)
  }
  case 2:{
    x = 20
    println(x)
  }
  default:{
    x = 99
  }
}
println(x)
```

### scope_assign_in_case.expect
```
10
10
```

## Test: scope_decl_both_cases

### scope_decl_both_cases.fg
```javascript
var a: int = 1

switch a {
  case 1:{
    var u: int = 11
    println(u)
  }
  case 2:{
    var v: int = 22
    println(v)
  }
  default:{
    println("default")
  }
}
```

### scope_decl_both_cases.expect
```
11
```

## Test: scope_decl_in_case

### scope_decl_in_case.fg
```javascript
var a: int = 1

switch a {
  case 1:{
    var y: int = 42
    println(y)
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
println("done")
```

### scope_decl_in_case.expect
```
42
done
```

## Test: scope_nested_block_in_case

### scope_nested_block_in_case.fg
```javascript
var a: int = 2

switch a {
  case 1:{
    println("one")
  }
  case 2:{
    {
      var inner: int = 100
      println(inner)
    }
    println("two")
  }
  default:{
    println("default")
  }
}
```

### scope_nested_block_in_case.expect
```
100
two
```

## Test: scope_shadow_in_case

### scope_shadow_in_case.fg
```javascript
var x: int = 1
var a: int = 1

switch a {
  case 1:{
    var x: int = 2
    println(x)
  }
  case 2:{
    println(x)
  }
  default:{
    println(x)
  }
}
println(x)
```

### scope_shadow_in_case.expect
```
2
1
```

## Test: scope_var_decl_from_func_in_case

### scope_var_decl_from_func_in_case.fg
```javascript
fun getVal() -> int {
  return 42
}

var a: int = 1

switch a {
  case 1:{
    var y: int = getVal()
    println(y)
  }
  default:{
    println(0)
  }
}
```

### scope_var_decl_from_func_in_case.expect
```
42
```

---

# Directory: SwitchTests/03_nested

## Test: nested_switch

### nested_switch.fg
```javascript
var a: int = 1

switch a {
  case 1:{
    println("outer one")
    var b: int = 2
    switch b {
      case 1:{
        println("inner one")
      }
      case 2:{
        println("inner two")
      }
      default:{
        println("inner default")
      }
    }
  }
  case 2:{
    println("outer two")
  }
  default:{
    println("outer default")
  }
}
```

### nested_switch.expect
```
outer one
inner two
```

---

# Directory: SwitchTests/03_conditions

## Test: case_binary_expr

### case_binary_expr.fg
```javascript
var a: int = 4

switch a {
  case 1 + 0:{
    println("one")
  }
  case 2 * 2:{
    println("four")
  }
  default:{
    println("default")
  }
}
```

### case_binary_expr.expect
```
four
```

## Test: case_expression

### case_expression.fg
```javascript
var a: int = 4

switch a {
  case 1 + 2:{
    println("three")
  }
  case 2 + 2:{
    println("four")
  }
  default:{
    println("default")
  }
}
```

### case_expression.expect
```
four
```

## Test: case_function_call

### case_function_call.fg
```javascript
fun getVal() -> int {
  return 3
}

var a: int = 3

switch a {
  case getVal():{
    println("match")
  }
  default:{
    println("default")
  }
}
```

### case_function_call.expect
```
match
```

## Test: case_variable

### case_variable.fg
```javascript
var a: int = 2
var b: int = 2

switch a {
  case b:{
    println("match")
  }
  default:{
    println("default")
  }
}
```

### case_variable.expect
```
match
```

---

# Directory: SwitchTests/05_errors

## Test: case_type_mismatch

### case_type_mismatch.fg
```javascript
/; EXPECT_ERROR: CaseExpressionTypeMismatch
var a: int = 1

switch a {
  case "hello":{
    println("str case")
  }
  default:{
    println("default")
  }
}
```

## Test: duplicate_default

### duplicate_default.fg
```javascript
/; EXPECT_ERROR: MultipleDefaultCaseStatements
var a: int = 1

switch a {
  case 1:{
    println("one")
  }
  default:{
    println("default")
  }
  default:{
    println("second default")
  }
}
```

---

# Directory: SwitchTests/02_default_order

## Test: default_first_match

### default_first_match.fg
```javascript
var a: int = 1

switch a {
  default:{
    println("default")
  }
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
}
```

### default_first_match.expect
```
one
```

## Test: default_first_no_match

### default_first_no_match.fg
```javascript
var a: int = 99

switch a {
  default:{
    println("default")
  }
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
}
```

### default_first_no_match.expect
```
default
```

---

# Directory: SwitchTests/08_dynamic

## Test: multi_return

### multi_return.fg
```javascript
fun getString() -> str, bool {
    return "Hello, FlowWing File System!", true
}

var s: str, ok: bool = getString()
println("s: ", s, " ok: ", ok)
var sdyn, okl = getString()
println("sdyn: ", sdyn, " okl: ", okl)
var sdyn2, ok2: bool = getString()
println("sdyn2: ", sdyn2, " ok2: ", ok2)
```

### multi_return.expect
```
s: Hello, FlowWing File System! ok: true
sdyn: "Hello, FlowWing File System!" okl: true
sdyn2: "Hello, FlowWing File System!" ok2: true
```

## Test: switch_on_dynamic_from_func

### switch_on_dynamic_from_func.fg
```javascript
fun getVal() {
  return 2
}

var x = getVal()

switch x {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
```

### switch_on_dynamic_from_func.expect
```
two
```

## Test: switch_on_dynamic_str

### switch_on_dynamic_str.fg
```javascript
fun getStr() {
  return "hi"
}

var s = getStr()

switch s {
  case "hi":{
    println("hi")
  }
  case "bye":{
    println("bye")
  }
  default:{
    println("default")
  }
}
```

### switch_on_dynamic_str.expect
```
hi
```

---

# Directory: SwitchTests/01_basic

## Test: switch_bool_false

### switch_bool_false.fg
```javascript
var a: bool = false

switch a {
  case true:{
    println("true")
  }
  case false:{
    println("false")
  }
  default:{
    println("default")
  }
}
```

### switch_bool_false.expect
```
false
```

## Test: switch_bool_true

### switch_bool_true.fg
```javascript
var a: bool = true

switch a {
  case true:{
    println("true")
  }
  case false:{
    println("false")
  }
  default:{
    println("default")
  }
}
```

### switch_bool_true.expect
```
true
```

## Test: switch_deci32

### switch_deci32.fg
```javascript
var a: deci32 = 2.5f

switch a {
  case 2.5f:{
    println("two five")
  }
  case 3.14f:{
    println("pi")
  }
  default:{
    println("default")
  }
}
```

### switch_deci32.expect
```
two five
```

## Test: switch_int64

### switch_int64.fg
```javascript
var a: int64 = 100

switch a {
  case 99:{
    println("ninety nine")
  }
  case 100:{
    println("hundred")
  }
  default:{
    println("default")
  }
}
```

### switch_int64.expect
```
hundred
```

## Test: switch_int8

### switch_int8.fg
```javascript
var a: int8 = 2

switch a {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
```

### switch_int8.expect
```
two
```

## Test: switch_int_default

### switch_int_default.fg
```javascript
var a: int = 42

switch a {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
```

### switch_int_default.expect
```
default
```

## Test: switch_int_match

### switch_int_match.fg
```javascript
var a: int = 2

switch a {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
```

### switch_int_match.expect
```
two
```

## Test: switch_str_match

### switch_str_match.fg
```javascript
var a: str = "hello"

switch a {
  case "hello":{
    println("hello")
  }
  case "world":{
    println("world")
  }
  default:{
    println("default")
  }
}
```

### switch_str_match.expect
```
hello
```

---

# Directory: SwitchTests/07_complex

## Test: assignment_then_print_in_case

### assignment_then_print_in_case.fg
```javascript
var x: int = 0
var a: int = 2

switch a {
  case 1:{
    x = 1
    println(x)
  }
  case 2:{
    x = 2
    println(x)
  }
  default:{
    x = -1
    println(x)
  }
}
println(x)
```

### assignment_then_print_in_case.expect
```
2
2
```

## Test: deeply_nested_switch

### deeply_nested_switch.fg
```javascript
var a: int = 1
var b: int = 2

switch a {
  case 1:{
    switch b {
      case 1:{
        println("1-1")
      }
      case 2:{
        println("1-2")
      }
      default:{
        println("1-d")
      }
    }
  }
  case 2:{
    println("2")
  }
  default:{
    println("d")
  }
}
```

### deeply_nested_switch.expect
```
1-2
```

## Test: empty_case_block

### empty_case_block.fg
```javascript
var a: int = 1

switch a {
  case 1:{
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
println("after")
```

### empty_case_block.expect
```
after
```

## Test: func_return_in_case_body

### func_return_in_case_body.fg
```javascript
fun getVal() -> int {
  return 3
}

var a: int = 2

switch a {
  case 1:{
    println(getVal())
  }
  case 2:{
    println(getVal())
  }
  case 3:{
    println(getVal())
  }
  default:{
    println(0)
  }
}
```

### func_return_in_case_body.expect
```
3
```

## Test: switch_on_func_call

### switch_on_func_call.fg
```javascript
fun getVal() -> int {
  return 3
}

switch getVal() {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  case 3:{
    println("three")
  }
  default:{
    println("other")
  }
}
```

### switch_on_func_call.expect
```
three
```

---

# Directory: SwitchTests/04_edge_cases

## Test: first_match_wins

### first_match_wins.fg
```javascript
var a: int = 1

switch a {
  case 1:{
    println("first")
  }
  case 1:{
    println("second")
  }
  default:{
    println("default")
  }
}
```

### first_match_wins.expect
```
first
```

## Test: no_match_uses_default

### no_match_uses_default.fg
```javascript
var a: int = 100

switch a {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  default:{
    println("No match")
  }
}
```

### no_match_uses_default.expect
```
No match
```

## Test: only_default

### only_default.fg
```javascript
var a: int = 7

switch a {
  default:{
    println("only default")
  }
}
```

### only_default.expect
```
only default
```

## Test: return_in_switch

### return_in_switch.fg
```javascript
fun testSwitch() -> str {
  var a: int = 1
  switch a {
    case 1:{
      return "one"
    }
    case 2:{
      return "two"
    }
    default:{
      return "default"
    }
  }
}

println(testSwitch())
```

### return_in_switch.expect
```
one
```

## Test: switch_char

### switch_char.fg
```javascript
var a: char = 'x'

switch a {
  case 'x':{
    println("x")
  }
  case 'y':{
    println("y")
  }
  default:{
    println("default")
  }
}
```

### switch_char.expect
```
x
```

## Test: switch_deci

### switch_deci.fg
```javascript
var a: deci = 2.5

switch a {
  case 2.5:{
    println("two point five")
  }
  case 3.14:{
    println("pi")
  }
  default:{
    println("default")
  }
}
```

### switch_deci.expect
```
two point five
```

## Test: switch_int_negative

### switch_int_negative.fg
```javascript
var a: int = -1

switch a {
  case -1:{
    println("minus one")
  }
  case 0:{
    println("zero")
  }
  default:{
    println("default")
  }
}
```

### switch_int_negative.expect
```
minus one
```

## Test: switch_int_zero

### switch_int_zero.fg
```javascript
var a: int = 0

switch a {
  case 0:{
    println("zero")
  }
  case 1:{
    println("one")
  }
  default:{
    println("default")
  }
}
```

### switch_int_zero.expect
```
zero
```

## Test: switch_str_empty

### switch_str_empty.fg
```javascript
var a: str = ""

switch a {
  case "":{
    println("empty")
  }
  case "x":{
    println("x")
  }
  default:{
    println("default")
  }
}
```

### switch_str_empty.expect
```
empty
```

---

# Directory: SwitchTests/10_object

## Test: func_return_object_in_case

### func_return_object_in_case.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoint() -> Point {
  return { x: 5, y: 10 }
}

var a: int = 1

switch a {
  case 1:{
    var p: Point = getPoint()
    println(p.x)
  }
  default:{
    println(0)
  }
}
```

### func_return_object_in_case.expect
```
5
```

## Test: object_decl_in_case

### object_decl_in_case.fg
```javascript
type Point = {
  x: int
  y: int
}

var a: int = 1

switch a {
  case 1:{
    var p: Point = { x: 1, y: 2 }
    println(p.x)
  }
  case 2:{
    println(0)
  }
  default:{
    println(0)
  }
}
```

### object_decl_in_case.expect
```
1
```

## Test: object_member_in_case

### object_member_in_case.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getPoint() -> Point {
  return { x: 3, y: 4 }
}

var a: int = 1

switch a {
  case 1:{
    var p: Point = getPoint()
    println(p.y)
  }
  default:{
    println(0)
  }
}
```

### object_member_in_case.expect
```
4
```

---

# Directory: SwitchTests/09_array

## Test: case_array_index

### case_array_index.fg
```javascript
var arr: int[3] = [1, 2, 3]
var i: int = 0

switch arr[i] {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  case 3:{
    println("three")
  }
  default:{
    println("default")
  }
}
```

### case_array_index.expect
```
one
```

## Test: switch_on_array_element

### switch_on_array_element.fg
```javascript
fun getArray() -> int[3] {
  return [10, 20, 30]
}

var arr: int[3] = getArray()

switch arr[0] {
  case 10:{
    println("ten")
  }
  case 20:{
    println("twenty")
  }
  default:{
    println("default")
  }
}

switch arr[1] {
  case 10:{
    println("ten")
  }
  case 20:{
    println("twenty")
  }
  default:{
    println("default")
  }
}
```

### switch_on_array_element.expect
```
ten
twenty
```

---

# Directory: ForTests/03_errors

## Test: for_break_outside_loop_if

### for_break_outside_loop_if.fg
```javascript
/; EXPECT_ERROR: BreakStatementNotAllowedOutsideOfLoop
fun foo() {
  if (true) {
    break
  }
}
foo()
```

## Test: for_continue_outside_loop_if

### for_continue_outside_loop_if.fg
```javascript
/; EXPECT_ERROR: ContinueStatementNotAllowedOutsideOfLoop
fun foo() {
  if (true) {
    continue
  }
}
foo()
```

## Test: for_invalid_step_str

### for_invalid_step_str.fg
```javascript
/; EXPECT_ERROR: InvalidStepTypeForForLoop
for (var i: int = 0 to 3 : "step") {
  println(i)
}
```

## Test: for_invalid_upper_bound_float

### for_invalid_upper_bound_float.fg
```javascript
/; EXPECT_ERROR: InvalidUpperBoundTypeForForLoop
for (var i: int = 0 to 3.5 : 1) {
  println(i)
}
```

## Test: for_invalid_upper_bound_str

### for_invalid_upper_bound_str.fg
```javascript
/; EXPECT_ERROR: InvalidUpperBoundTypeForForLoop
for (var i: int = 0 to "bad" : 1) {
  println(i)
}
```

## Test: for_invalid_var_type_bool

### for_invalid_var_type_bool.fg
```javascript
/; EXPECT_ERROR: InvalidVariableDeclarationTypeForForLoopVariableDeclaration
for (var flag: bool = true to false : true) {
  println(flag)
}
```

## Test: for_invalid_var_type_str

### for_invalid_var_type_str.fg
```javascript
/; EXPECT_ERROR: InvalidVariableDeclarationTypeForForLoopVariableDeclaration
for (var x: str = "a" to "c" : "b") {
  println(x)
}
```

## Test: for_too_many_declarators

### for_too_many_declarators.fg
```javascript
/; EXPECT_ERROR: TooManyDeclaratorsInVariableDeclaration
for (var a: int = 0, b: int = 0 to 3 : 1) {
  println(a)
}
```

---

# Directory: ForTests/04_functions

## Test: for_bound_and_step_from_functions

### for_bound_and_step_from_functions.fg
```javascript
fun getBound() -> int {
  return 5
}

fun getStep() -> int {
  return 2
}

for (var i: int = 0 to getBound() : getStep()) {
  println(i)
}
println("done")
```

### for_bound_and_step_from_functions.expect
```
0
2
4
done
```

## Test: for_bound_from_function

### for_bound_from_function.fg
```javascript
fun getBound() -> int {
  return 3
}

for (var i: int = 0 to getBound() : 1) {
  println(i)
}
println("done")
```

### for_bound_from_function.expect
```
0
1
2
3
done
```

## Test: for_loop_returns_from_function

### for_loop_returns_from_function.fg
```javascript
fun countTo(n: int) -> int {
  var c: int = 0
  for (var i: int = 0 to n : 1) {
    c = c + 1
  }
  return c
}

var r: int = countTo(4)
println(r)
println("done")
```

### for_loop_returns_from_function.expect
```
5
done
```

## Test: for_step_from_function

### for_step_from_function.fg
```javascript
fun getStep()-> int {
  return 2
}

for (var i: int = 0 to 6 : getStep()) {
  println(i)
}
println("done")
```

### for_step_from_function.expect
```
0
2
4
6
done
```

---

# Directory: ForTests/01_basic

## Test: for_basic

### for_basic.fg
```javascript
for (var i = 0 to 3 : 1) {
  println(i)
}
println("done")
```

### for_basic.expect
```
0
1
2
3
done
```

## Test: for_dynamic_var

### for_dynamic_var.fg
```javascript
for (var i = 0 to 3 : 1) {
  println(i)
}
println("done")
```

### for_dynamic_var.expect
```
0
1
2
3
done
```

## Test: for_dynamic_var_modify

### for_dynamic_var_modify.fg
```javascript
for (var i = 0 to 3 : 1) {
  println(i)
  i = i + 1
}
println("done")
```

### for_dynamic_var_modify.expect
```
0
2
done
```

## Test: for_int

### for_int.fg
```javascript
for (var i: int = 0 to 3 : 1) {
  println(i)
}
println("done")
```

### for_int.expect
```
0
1
2
3
done
```

## Test: for_int32

### for_int32.fg
```javascript
for (var i: int = 0 to 3 : 1) {
  println(i)
}
println("done")
```

### for_int32.expect
```
0
1
2
3
done
```

## Test: for_int64

### for_int64.fg
```javascript
for (var i: int64 = 0 to 3 : 1) {
  println(i)
}
println("done")
```

### for_int64.expect
```
0
1
2
3
done
```

## Test: for_int8

### for_int8.fg
```javascript
for (var i: int8 = 0 to 3 : 1) {
  println(i)
}
println("done")
```

### for_int8.expect
```
0
1
2
3
done
```

## Test: for_negative_step

### for_negative_step.fg
```javascript
for (var i: int = 3 to 0 : -1) {
  println(i)
}
println("done")
```

### for_negative_step.expect
```
3
2
1
0
done
```

## Test: for_no_step

### for_no_step.fg
```javascript
for (var i: int = 0 to 2) {
  println(i)
}
println("done")
```

### for_no_step.expect
```
0
1
2
done
```

## Test: for_step_two

### for_step_two.fg
```javascript
for (var i: int = 0 to 6 : 2) {
  println(i)
}
println("done")
```

### for_step_two.expect
```
0
2
4
6
done
```

---

# Directory: ForTests/02_break_continue

## Test: for_break_after_one_iteration

### for_break_after_one_iteration.fg
```javascript
for (var i: int = 0 to 5 : 1) {
  println(i)
  break
}
println("done")
```

### for_break_after_one_iteration.expect
```
0
done
```

## Test: for_break_immediate

### for_break_immediate.fg
```javascript
for (var i: int = 0 to 5 : 1) {
  break
  println(i)
}
println("done")
```

### for_break_immediate.expect
```
done
```

## Test: for_break_on_condition

### for_break_on_condition.fg
```javascript
for (var i: int = 0 to 10 : 1) {
  if (i == 5) {
    break
  }
  println(i)
}
println("done")
```

### for_break_on_condition.expect
```
0
1
2
3
4
done
```

## Test: for_continue_immediate

### for_continue_immediate.fg
```javascript
for (var i: int = 0 to 4 : 1) {
  continue
  println(i)
}
println("done")
```

### for_continue_immediate.expect
```
done
```

## Test: for_continue_skip_one

### for_continue_skip_one.fg
```javascript
for (var i: int = 0 to 4 : 1) {
  if (i == 2) {
    continue
  }
  println(i)
}
println("done")
```

### for_continue_skip_one.expect
```
0
1
3
4
done
```

## Test: for_continue_then_break

### for_continue_then_break.fg
```javascript
for (var i: int = 0 to 5 : 1) {
  if (i == 2) {
    continue
  }
  println(i)
  if (i == 4) {
    break
  }
}
println("done")
```

### for_continue_then_break.expect
```
0
1
3
4
done
```

## Test: for_dynamic_break

### for_dynamic_break.fg
```javascript
for (var i = 0 to 5 : 1) {
  println(i)
  if (i == 3) {
    break
  }
}
println("out")
println("done")
```

### for_dynamic_break.expect
```
0
1
2
3
out
done
```

## Test: for_dynamic_continue

### for_dynamic_continue.fg
```javascript
for (var i = 0 to 4 : 1) {
  if (i == 2) {
    continue
  }
  println(i)
}
println("done")
```

### for_dynamic_continue.expect
```
0
1
3
4
done
```

## Test: for_loop_inside_function_break

### for_loop_inside_function_break.fg
```javascript
fun run() {
  for (var i: int = 0 to 5 : 1) {
    println(i)
    if (i == 3) {
      break
    }
  }
  println("out")
}

run()
println("done")
```

### for_loop_inside_function_break.expect
```
0
1
2
3
out
done
```

## Test: for_loop_inside_function_continue

### for_loop_inside_function_continue.fg
```javascript
fun run() {
  for (var i: int = 0 to 5 : 1) {
    if (i == 2) {
      continue
    }
    println(i)
  }
  println("out")
}

run()
println("done")
```

### for_loop_inside_function_continue.expect
```
0
1
3
4
5
out
done
```

## Test: for_nested_break_inner

### for_nested_break_inner.fg
```javascript
for (var i: int = 0 to 2 : 1) {
  for (var j: int = 0 to 2 : 1) {
    println(i)
    println(j)
    if (i == 1 && j == 1) {
      break
    }
  }
}
println("done")
```

### for_nested_break_inner.expect
```
0
0
0
1
0
2
1
0
1
1
2
0
2
1
2
2
done
```

## Test: for_nested_continue_inner

### for_nested_continue_inner.fg
```javascript
for (var i: int = 0 to 2 : 1) {
  for (var j: int = 0 to 2 : 1) {
    if (j == 1) {
      continue
    }
    println(i)
    println(j)
  }
}
println("done")
```

### for_nested_continue_inner.expect
```
0
0
0
2
1
0
1
2
2
0
2
2
done
```

## Test: for_nested_loops_with_switch_break

### for_nested_loops_with_switch_break.fg
```javascript
for (var i: int = 0 to 2 : 1) {
  for (var j: int = 0 to 2 : 1) {
    switch j {
      case 0: {
        println(0)
      }
      case 1: {
        println(1)
        break
      }
      default: {
        println(2)
      }
    }
  }
  println(i)
}
println("done")
```

### for_nested_loops_with_switch_break.expect
```
0
1
0
0
1
1
0
1
2
done
```

---

# Directory: ForTests/03_control_flow

## Test: for_array_index

### for_array_index.fg
```javascript
var arr: int[3] = [10, 20, 30]
for (var i: int = 0 to 2 : 1) {
  println(arr[i])
}
println("done")
```

### for_array_index.expect
```
10
20
30
done
```

## Test: for_binary_ops_body

### for_binary_ops_body.fg
```javascript
for (var i: int = 1 to 4 : 1) {
  var double: int = i * 2
  var sum: int = i + 10
  println(double)
  println(sum)
}
println("done")
```

### for_binary_ops_body.expect
```
2
11
4
12
6
13
8
14
done
```

## Test: for_combined_if_ternary

### for_combined_if_ternary.fg
```javascript
for (var i: int = 0 to 3 : 1) {
  if (i % 2 == 0) {
    var s: str = i > 1 ? "even_big" : "even_small"
    println(s)
  } else {
    println("odd")
  }
}
println("done")
```

### for_combined_if_ternary.expect
```
even_small
odd
even_big
odd
done
```

## Test: for_nested_double

### for_nested_double.fg
```javascript
for (var i: int = 0 to 1 : 1) {
  for (var j: int = 0 to 1 : 1) {
    println(i)
    println(j)
  }
}
println("done")
```

### for_nested_double.expect
```
0
0
0
1
1
0
1
1
done
```

## Test: for_nested_with_while

### for_nested_with_while.fg
```javascript
var w: int = 0
for (var i: int = 0 to 2 : 1) {
  while (w < 2) {
    println(w)
    w = w + 1
  }
  println(i)
}
println("done")
```

### for_nested_with_while.expect
```
0
1
0
1
2
done
```

## Test: for_unary_ops_body

### for_unary_ops_body.fg
```javascript
for (var i: int = 0 to 2 : 1) {
  var neg: int = -i
  println(neg)
  var pos: int = +i
  println(pos)
}
println("done")
```

### for_unary_ops_body.expect
```
0
0
-1
1
-2
2
done
```

## Test: for_with_if_else

### for_with_if_else.fg
```javascript
for (var i: int = 0 to 4 : 1) {
  if (i % 2 == 0) {
    println("even")
  } else {
    println("odd")
  }
}
println("done")
```

### for_with_if_else.expect
```
even
odd
even
odd
even
done
```

## Test: for_with_object_in_body

### for_with_object_in_body.fg
```javascript
type Point = {
  x: int
  y: int
}

for (var i: int = 0 to 2 : 1) {
  var p: Point = { x: i, y: i * 2 }
  println(p.x)
  println(p.y)
}
println("done")
```

### for_with_object_in_body.expect
```
0
0
1
2
2
4
done
```

## Test: for_with_switch

### for_with_switch.fg
```javascript
for (var i: int = 0 to 3 : 1) {
  switch i {
    case 0:{
      println("zero")
    }
    case 1:{
      println("one")
    }
    case 2:{
      println("two")
    }
    default:{
      println("other")
    }
  }
}
println("done")
```

### for_with_switch.expect
```
zero
one
two
other
done
```

## Test: for_with_ternary

### for_with_ternary.fg
```javascript
for (var i: int = 0 to 3 : 1) {
  var s: str = i > 1 ? "big" : "small"
  println(s)
}
println("done")
```

### for_with_ternary.expect
```
small
small
big
big
done
```

---

# Directory: ConstTests

## Test: const_all_types

### const_all_types.fg
```javascript
const i:int = 42
const d:deci = 3.14
const s:str = "hello"
const b:bool = true
const c:char = 'A'
println(i, d, s, b, c)
```

### const_all_types.expect
```
423.14hellotrueA
```

## Test: const_in_expression

### const_in_expression.fg
```javascript
const x:int = 10
const y:int = 20
var z:int = x + y
println(z)
```

### const_in_expression.expect
```
30
```

## Test: const_int

### const_int.fg
```javascript
const x:int = 100
println(x)
```

### const_int.expect
```
100
```

## Test: const_reassign_error

### const_reassign_error.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int = 5
x = 10
```

## Test: const_scope_global_access

### const_scope_global_access.fg
```javascript
const MAX:int = 100
{
    var x:int = MAX + 1
    println(x)
}
println(MAX)
```

### const_scope_global_access.expect
```
101
100
```

---

# Directory: FunctionTests/16_dynamic_return

## Test: dynamic_return_bool

### dynamic_return_bool.fg
```javascript
fun getFlag() {
  return true
}

var b: bool = getFlag()
println(b)
```

### dynamic_return_bool.expect
```
true
```

## Test: dynamic_return_int

### dynamic_return_int.fg
```javascript
fun getNumber() {
  return 42
}

var x: int = getNumber()
println(x)
```

### dynamic_return_int.expect
```
42
```

## Test: dynamic_return_str

### dynamic_return_str.fg
```javascript
fun getMessage() {
  return "hello"
}

var s: str = getMessage()
println(s)
```

### dynamic_return_str.expect
```
hello
```

---

# Directory: FunctionTests/05_inout

## Test: inout_bool_toggle

### inout_bool_toggle.fg
```javascript
fun setFlag(inout flag: bool) -> bool {
  flag = !flag
  return flag
}

var b: bool = true
println(b)
setFlag(b)
println(b)
setFlag(b)
println(b)
```

### inout_bool_toggle.expect
```
true
false
true
```

## Test: inout_bool_twice

### inout_bool_twice.fg
```javascript
fun flip(inout b: bool) {
  b = !b
}

var f: bool = false
println(f)
flip(f)
println(f)
flip(f)
println(f)
```

### inout_bool_twice.expect
```
false
true
false
```

## Test: inout_chain_three

### inout_chain_three.fg
```javascript
fun inc(inout n: int) {
  n = n + 1
}

var a: int = 0
inc(a)
inc(a)
inc(a)
println(a)
```

### inout_chain_three.expect
```
3
```

## Test: inout_char

### inout_char.fg
```javascript
fun nextChar(inout c: char) -> char {
  c = 'b'
  return c
}

var ch: char = 'a'
println(ch)
nextChar(ch)
println(ch)
```

### inout_char.expect
```
a
b
```

## Test: inout_deci

### inout_deci.fg
```javascript
fun addHalf(inout x: deci) -> deci {
  x = x + 0.5
  return x
}

var v: deci = 1.5
println(v)
addHalf(v)
println(v)
addHalf(v)
println(v)
```

### inout_deci.expect
```
1.5
2
2.5
```

## Test: inout_deci32

### inout_deci32.fg
```javascript
fun addHalf(inout x: deci32) -> deci32 {
  x = x + 0.5f
  return x
}

var v: deci32 = 1.5f
println(v)
addHalf(v)
println(v)
addHalf(v)
println(v)
```

### inout_deci32.expect
```
1.5
2
2.5
```

## Test: inout_deci_add

### inout_deci_add.fg
```javascript
fun addHalf(inout d: deci) {
  d = d + 0.5
}

var d: deci = 1.5
println(d)
addHalf(d)
addHalf(d)
println(d)
```

### inout_deci_add.expect
```
1.5
2.5
```

## Test: inout_double_increment

### inout_double_increment.fg
```javascript
fun inc2(inout n: int) {
  n = n + 1
  n = n + 1
}

var v: int = 0
println(v)
inc2(v)
println(v)
inc2(v)
println(v)
```

### inout_double_increment.expect
```
0
2
4
```

## Test: inout_int_increment

### inout_int_increment.fg
```javascript
fun increment(inout n: int) -> int {
  n = n + 1
  return n
}

var a: int = 10
println(a)
increment(a)
println(a)
increment(a)
println(a)
```

### inout_int_increment.expect
```
10
11
12
```

## Test: inout_return_modified_value

### inout_return_modified_value.fg
```javascript
fun incAndReturn(inout n: int) -> int {
  n = n + 10
  return n
}

var x: int = 5
var y: int = incAndReturn(x)
println(x)
println(y)
```

### inout_return_modified_value.expect
```
15
15
```

## Test: inout_str_append_chain

### inout_str_append_chain.fg
```javascript
fun append(inout s: str, t: str) {
  s = s + t
}

var x: str = "a"
append(x, "b")
println(x)
append(x, "c")
println(x)
```

### inout_str_append_chain.expect
```
ab
abc
```

## Test: inout_str_print_return

### inout_str_print_return.fg
```javascript
fun test1(inout a) {
  print("Hello", a)
  a = "something"
  return "Hello World2"
}

var a = 10
println(a)
var x = test1(a)
println(a)
```

### inout_str_print_return.expect
```
10
Hello10"something"
```

## Test: inout_str_typed

### inout_str_typed.fg
```javascript
fun setGreeting(inout msg: str) -> str {
  msg = "Hello"
  return msg
}

var s: str = "Hi"
println(s)
setGreeting(s)
println(s)
```

### inout_str_typed.expect
```
Hi
Hello
```

## Test: inout_two_params

### inout_two_params.fg
```javascript
fun swapAndDouble(inout a: int, inout b: int) -> int {
  var temp: int = a
  a = b * 2
  b = temp * 2
  return a
}

var x: int = 5
var y: int = 10
println(x)
println(y)
swapAndDouble(x, y)
println(x)
println(y)
```

### inout_two_params.expect
```
5
10
20
10
```

---

# Directory: FunctionTests/03_parameters

## Test: param_all_types

### param_all_types.fg
```javascript
fun describe(a: int, b: deci, c: str, d: bool) -> str {
  return c
}

println(describe(1, 2.5, "test", true))
```

### param_all_types.expect
```
test
```

## Test: param_bool

### param_bool.fg
```javascript
fun negate(flag: bool) -> bool {
  return !flag
}

println(negate(true))
println(negate(false))
```

### param_bool.expect
```
false
true
```

## Test: param_char

### param_char.fg
```javascript
fun echo(c: char) -> char {
  return c
}

println(echo('Z'))
```

### param_char.expect
```
Z
```

## Test: param_deci

### param_deci.fg
```javascript
fun addDeci(a: deci, b: deci) -> deci {
  return a + b
}

println(addDeci(1.5, 2.5))
```

### param_deci.expect
```
4
```

## Test: param_default

### param_default.fg
```javascript
fun greet(name: str = "World") -> str {
  return "Hello " + name
}

println(greet())
println(greet("Flow-Wing"))
```

### param_default.expect
```
Hello World
Hello Flow-Wing
```

## Test: param_five_args

### param_five_args.fg
```javascript
fun add5(a: int, b: int, c: int, d: int, e: int) -> int {
  return a + b + c + d + e
}

println(add5(1, 2, 3, 4, 5))
println(add5(0, 0, 0, 0, 0))
```

### param_five_args.expect
```
15
0
```

## Test: param_int

### param_int.fg
```javascript
fun add(a: int, b: int) -> int {
  return a + b
}

println(add(3, 7))
```

### param_int.expect
```
10
```

## Test: param_int8

### param_int8.fg
```javascript
fun add(a: int8, b: int8) -> int {
  return a + b
}

println(add(10, 20))
```

### param_int8.expect
```
30
```

## Test: param_mixed_typed_and_default

### param_mixed_typed_and_default.fg
```javascript
fun mix(x: int, y: deci = 2.5) -> deci {
  return x * y
}

println(mix(2))
println(mix(4, 1.0))
```

### param_mixed_typed_and_default.expect
```
5
4
```

## Test: param_second_default_first_given

### param_second_default_first_given.fg
```javascript
fun greet(name: str = "World", suffix: str = "!") -> str {
  return "Hi " + name + suffix
}

println(greet("A"))
println(greet("B", "?"))
println(greet())
```

### param_second_default_first_given.expect
```
Hi A!
Hi B?
Hi World!
```

## Test: param_str

### param_str.fg
```javascript
fun greetPerson(name: str) -> str {
  return "Hello " + name
}

println(greetPerson("Alice"))
```

### param_str.expect
```
Hello Alice
```

## Test: param_two_defaults

### param_two_defaults.fg
```javascript
fun f(a: int = 1, b: int = 2) -> int {
  return a + b
}

println(f())
println(f(10))
println(f(10, 20))
```

### param_two_defaults.expect
```
3
12
30
```

---

# Directory: FunctionTests/14_object_with_func

## Test: complex_nested_struct_array_inout

### complex_nested_struct_array_inout.fg
```javascript
type Vec2 = {x: deci, y: deci}
type Polygon = { vertices: Vec2[3], color: str }

fun shiftPolygon(inout poly: Polygon, dx: deci, dy: deci) {
  poly.vertices[0].x = poly.vertices[0].x + dx
  poly.vertices[0].y = poly.vertices[0].y + dy
  poly.vertices[1].x = poly.vertices[1].x + dx
  poly.vertices[1].y = poly.vertices[1].y + dy
  poly.color = "shifted"
}

var p: Polygon = {
  vertices: [{x: 0.0, y: 0.0}, {x: 1.0, y: 0.0}, {x: 0.5, y: 1.0}],
  color: "original"
}

shiftPolygon(p, 2.5, 3.5)

println(p.color)
println(p.vertices[0].x)
println(p.vertices[0].y)
println(p.vertices[1].x)
println(p.vertices[1].y)
println(p.vertices[2].x)
```

### complex_nested_struct_array_inout.expect
```
shifted
2.5
3.5
3.5
3.5
0.5
```

## Test: complex_object_array_args

### complex_object_array_args.fg
```javascript
type Point = {x: int, y: int}
type Shape = {points: Point[2], name: str}

fun printShape(s: Shape) {
    println("Shape: ", s.name)
    println("First point: ", s.points[0].x, ", ", s.points[0].y)
    s.name = "ModifiedCopy"
    s.points[0].x = 99
}

fun modifyShape(inout s: Shape) {
    s.name = "ModifiedRef"
    s.points[1].y = 100
}

var p1: Point = {x: 1, y: 2}
var p2: Point = {x: 3, y: 4}
var arr: Point[2] = [p1, p2]
var myShape: Shape = {points: arr, name: "Original"}

printShape(myShape)
println("After printShape: ", myShape.name, " ", myShape.points[0].x)

modifyShape(myShape)
println("After modifyShape: ", myShape.name, " ", myShape.points[1].y)
```

### complex_object_array_args.expect
```
Shape: Original
First point: 1, 2
After printShape: ModifiedCopy 99
After modifyShape: ModifiedRef 100
```

## Test: complex_return_types

### complex_return_types.fg
```javascript
type Point = {x: int, y: int}
type Path = {points: Point[2]}

fun createPath(p1: Point, p2: Point) -> Path {
    var arr: Point[2] = [p1, p2]
    var path: Path = {points: arr}
    return path
}

fun getFirstPointX(path: Path) -> int {
    return path.points[0].x
}

var start: Point = {x: 10, y: 20}
var end: Point = {x: 30, y: 40}

var myPath: Path = createPath(start, end)
println("Path second y: ", myPath.points[1].y)

var xVal = getFirstPointX(createPath(start, end))
println("Direct access x: ", xVal)
```

### complex_return_types.expect
```
Path second y: 40
Direct access x: 10
```

## Test: gen_100_deep_nest_1

### gen_100_deep_nest_1.fg
```javascript
type L3_1 = { c: int }
type L2_1 = { b: L3_1[2] }
type L1_1 = { a: L2_1 }
fun build_dn_1() -> L1_1[2] {
  var l2_0: L2_1 = { b: [{c: 1}, {c: 2}] }
  var l2_1: L2_1 = { b: [{c: 3}, {c: 4}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_1()[0].a.b[1].c)
println(build_dn_1()[1].a.b[0].c)
```

### gen_100_deep_nest_1.expect
```
2
3
```

## Test: gen_100_deep_nest_10

### gen_100_deep_nest_10.fg
```javascript
type L3_10 = { c: int }
type L2_10 = { b: L3_10[2] }
type L1_10 = { a: L2_10 }
fun build_dn_10() -> L1_10[2] {
  var l2_0: L2_10 = { b: [{c: 10}, {c: 20}] }
  var l2_1: L2_10 = { b: [{c: 30}, {c: 40}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_10()[0].a.b[1].c)
println(build_dn_10()[1].a.b[0].c)
```

### gen_100_deep_nest_10.expect
```
20
30
```

## Test: gen_100_deep_nest_11

### gen_100_deep_nest_11.fg
```javascript
type L3_11 = { c: int }
type L2_11 = { b: L3_11[2] }
type L1_11 = { a: L2_11 }
fun build_dn_11() -> L1_11[2] {
  var l2_0: L2_11 = { b: [{c: 11}, {c: 22}] }
  var l2_1: L2_11 = { b: [{c: 33}, {c: 44}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_11()[0].a.b[1].c)
println(build_dn_11()[1].a.b[0].c)
```

### gen_100_deep_nest_11.expect
```
22
33
```

## Test: gen_100_deep_nest_12

### gen_100_deep_nest_12.fg
```javascript
type L3_12 = { c: int }
type L2_12 = { b: L3_12[2] }
type L1_12 = { a: L2_12 }
fun build_dn_12() -> L1_12[2] {
  var l2_0: L2_12 = { b: [{c: 12}, {c: 24}] }
  var l2_1: L2_12 = { b: [{c: 36}, {c: 48}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_12()[0].a.b[1].c)
println(build_dn_12()[1].a.b[0].c)
```

### gen_100_deep_nest_12.expect
```
24
36
```

## Test: gen_100_deep_nest_13

### gen_100_deep_nest_13.fg
```javascript
type L3_13 = { c: int }
type L2_13 = { b: L3_13[2] }
type L1_13 = { a: L2_13 }
fun build_dn_13() -> L1_13[2] {
  var l2_0: L2_13 = { b: [{c: 13}, {c: 26}] }
  var l2_1: L2_13 = { b: [{c: 39}, {c: 52}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_13()[0].a.b[1].c)
println(build_dn_13()[1].a.b[0].c)
```

### gen_100_deep_nest_13.expect
```
26
39
```

## Test: gen_100_deep_nest_14

### gen_100_deep_nest_14.fg
```javascript
type L3_14 = { c: int }
type L2_14 = { b: L3_14[2] }
type L1_14 = { a: L2_14 }
fun build_dn_14() -> L1_14[2] {
  var l2_0: L2_14 = { b: [{c: 14}, {c: 28}] }
  var l2_1: L2_14 = { b: [{c: 42}, {c: 56}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_14()[0].a.b[1].c)
println(build_dn_14()[1].a.b[0].c)
```

### gen_100_deep_nest_14.expect
```
28
42
```

## Test: gen_100_deep_nest_15

### gen_100_deep_nest_15.fg
```javascript
type L3_15 = { c: int }
type L2_15 = { b: L3_15[2] }
type L1_15 = { a: L2_15 }
fun build_dn_15() -> L1_15[2] {
  var l2_0: L2_15 = { b: [{c: 15}, {c: 30}] }
  var l2_1: L2_15 = { b: [{c: 45}, {c: 60}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_15()[0].a.b[1].c)
println(build_dn_15()[1].a.b[0].c)
```

### gen_100_deep_nest_15.expect
```
30
45
```

## Test: gen_100_deep_nest_16

### gen_100_deep_nest_16.fg
```javascript
type L3_16 = { c: int }
type L2_16 = { b: L3_16[2] }
type L1_16 = { a: L2_16 }
fun build_dn_16() -> L1_16[2] {
  var l2_0: L2_16 = { b: [{c: 16}, {c: 32}] }
  var l2_1: L2_16 = { b: [{c: 48}, {c: 64}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_16()[0].a.b[1].c)
println(build_dn_16()[1].a.b[0].c)
```

### gen_100_deep_nest_16.expect
```
32
48
```

## Test: gen_100_deep_nest_17

### gen_100_deep_nest_17.fg
```javascript
type L3_17 = { c: int }
type L2_17 = { b: L3_17[2] }
type L1_17 = { a: L2_17 }
fun build_dn_17() -> L1_17[2] {
  var l2_0: L2_17 = { b: [{c: 17}, {c: 34}] }
  var l2_1: L2_17 = { b: [{c: 51}, {c: 68}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_17()[0].a.b[1].c)
println(build_dn_17()[1].a.b[0].c)
```

### gen_100_deep_nest_17.expect
```
34
51
```

## Test: gen_100_deep_nest_18

### gen_100_deep_nest_18.fg
```javascript
type L3_18 = { c: int }
type L2_18 = { b: L3_18[2] }
type L1_18 = { a: L2_18 }
fun build_dn_18() -> L1_18[2] {
  var l2_0: L2_18 = { b: [{c: 18}, {c: 36}] }
  var l2_1: L2_18 = { b: [{c: 54}, {c: 72}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_18()[0].a.b[1].c)
println(build_dn_18()[1].a.b[0].c)
```

### gen_100_deep_nest_18.expect
```
36
54
```

## Test: gen_100_deep_nest_19

### gen_100_deep_nest_19.fg
```javascript
type L3_19 = { c: int }
type L2_19 = { b: L3_19[2] }
type L1_19 = { a: L2_19 }
fun build_dn_19() -> L1_19[2] {
  var l2_0: L2_19 = { b: [{c: 19}, {c: 38}] }
  var l2_1: L2_19 = { b: [{c: 57}, {c: 76}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_19()[0].a.b[1].c)
println(build_dn_19()[1].a.b[0].c)
```

### gen_100_deep_nest_19.expect
```
38
57
```

## Test: gen_100_deep_nest_2

### gen_100_deep_nest_2.fg
```javascript
type L3_2 = { c: int }
type L2_2 = { b: L3_2[2] }
type L1_2 = { a: L2_2 }
fun build_dn_2() -> L1_2[2] {
  var l2_0: L2_2 = { b: [{c: 2}, {c: 4}] }
  var l2_1: L2_2 = { b: [{c: 6}, {c: 8}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_2()[0].a.b[1].c)
println(build_dn_2()[1].a.b[0].c)
```

### gen_100_deep_nest_2.expect
```
4
6
```

## Test: gen_100_deep_nest_20

### gen_100_deep_nest_20.fg
```javascript
type L3_20 = { c: int }
type L2_20 = { b: L3_20[2] }
type L1_20 = { a: L2_20 }
fun build_dn_20() -> L1_20[2] {
  var l2_0: L2_20 = { b: [{c: 20}, {c: 40}] }
  var l2_1: L2_20 = { b: [{c: 60}, {c: 80}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_20()[0].a.b[1].c)
println(build_dn_20()[1].a.b[0].c)
```

### gen_100_deep_nest_20.expect
```
40
60
```

## Test: gen_100_deep_nest_3

### gen_100_deep_nest_3.fg
```javascript
type L3_3 = { c: int }
type L2_3 = { b: L3_3[2] }
type L1_3 = { a: L2_3 }
fun build_dn_3() -> L1_3[2] {
  var l2_0: L2_3 = { b: [{c: 3}, {c: 6}] }
  var l2_1: L2_3 = { b: [{c: 9}, {c: 12}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_3()[0].a.b[1].c)
println(build_dn_3()[1].a.b[0].c)
```

### gen_100_deep_nest_3.expect
```
6
9
```

## Test: gen_100_deep_nest_4

### gen_100_deep_nest_4.fg
```javascript
type L3_4 = { c: int }
type L2_4 = { b: L3_4[2] }
type L1_4 = { a: L2_4 }
fun build_dn_4() -> L1_4[2] {
  var l2_0: L2_4 = { b: [{c: 4}, {c: 8}] }
  var l2_1: L2_4 = { b: [{c: 12}, {c: 16}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_4()[0].a.b[1].c)
println(build_dn_4()[1].a.b[0].c)
```

### gen_100_deep_nest_4.expect
```
8
12
```

## Test: gen_100_deep_nest_5

### gen_100_deep_nest_5.fg
```javascript
type L3_5 = { c: int }
type L2_5 = { b: L3_5[2] }
type L1_5 = { a: L2_5 }
fun build_dn_5() -> L1_5[2] {
  var l2_0: L2_5 = { b: [{c: 5}, {c: 10}] }
  var l2_1: L2_5 = { b: [{c: 15}, {c: 20}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_5()[0].a.b[1].c)
println(build_dn_5()[1].a.b[0].c)
```

### gen_100_deep_nest_5.expect
```
10
15
```

## Test: gen_100_deep_nest_6

### gen_100_deep_nest_6.fg
```javascript
type L3_6 = { c: int }
type L2_6 = { b: L3_6[2] }
type L1_6 = { a: L2_6 }
fun build_dn_6() -> L1_6[2] {
  var l2_0: L2_6 = { b: [{c: 6}, {c: 12}] }
  var l2_1: L2_6 = { b: [{c: 18}, {c: 24}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_6()[0].a.b[1].c)
println(build_dn_6()[1].a.b[0].c)
```

### gen_100_deep_nest_6.expect
```
12
18
```

## Test: gen_100_deep_nest_7

### gen_100_deep_nest_7.fg
```javascript
type L3_7 = { c: int }
type L2_7 = { b: L3_7[2] }
type L1_7 = { a: L2_7 }
fun build_dn_7() -> L1_7[2] {
  var l2_0: L2_7 = { b: [{c: 7}, {c: 14}] }
  var l2_1: L2_7 = { b: [{c: 21}, {c: 28}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_7()[0].a.b[1].c)
println(build_dn_7()[1].a.b[0].c)
```

### gen_100_deep_nest_7.expect
```
14
21
```

## Test: gen_100_deep_nest_8

### gen_100_deep_nest_8.fg
```javascript
type L3_8 = { c: int }
type L2_8 = { b: L3_8[2] }
type L1_8 = { a: L2_8 }
fun build_dn_8() -> L1_8[2] {
  var l2_0: L2_8 = { b: [{c: 8}, {c: 16}] }
  var l2_1: L2_8 = { b: [{c: 24}, {c: 32}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_8()[0].a.b[1].c)
println(build_dn_8()[1].a.b[0].c)
```

### gen_100_deep_nest_8.expect
```
16
24
```

## Test: gen_100_deep_nest_9

### gen_100_deep_nest_9.fg
```javascript
type L3_9 = { c: int }
type L2_9 = { b: L3_9[2] }
type L1_9 = { a: L2_9 }
fun build_dn_9() -> L1_9[2] {
  var l2_0: L2_9 = { b: [{c: 9}, {c: 18}] }
  var l2_1: L2_9 = { b: [{c: 27}, {c: 36}] }
  return [{a: l2_0}, {a: l2_1}]
}
println(build_dn_9()[0].a.b[1].c)
println(build_dn_9()[1].a.b[0].c)
```

### gen_100_deep_nest_9.expect
```
18
27
```

## Test: gen_100_global_array_return_1

### gen_100_global_array_return_1.fg
```javascript
type GlobObj_1 = { x: int, y: int }
var g_arr_1: GlobObj_1[3] = [{x: 1, y: 2}, {x: 3, y: 4}, {x: 5, y: 6}]
fun fetchGlobal_1() -> GlobObj_1[3] {
  return g_arr_1
}
fun fetchGlobalElem_1() -> GlobObj_1 {
  return g_arr_1[0]
}
var fetched_1: GlobObj_1[3] = fetchGlobal_1()
println(fetched_1[2].x)
println(fetched_1[1].y)
var elem_1: GlobObj_1 = fetchGlobalElem_1()
println(elem_1.x)
```

### gen_100_global_array_return_1.expect
```
5
4
1
```

## Test: gen_100_global_array_return_10

### gen_100_global_array_return_10.fg
```javascript
type GlobObj_10 = { x: int, y: int }
var g_arr_10: GlobObj_10[3] = [{x: 10, y: 11}, {x: 12, y: 13}, {x: 14, y: 15}]
fun fetchGlobal_10() -> GlobObj_10[3] {
  return g_arr_10
}
fun fetchGlobalElem_10() -> GlobObj_10 {
  return g_arr_10[0]
}
var fetched_10: GlobObj_10[3] = fetchGlobal_10()
println(fetched_10[2].x)
println(fetched_10[1].y)
var elem_10: GlobObj_10 = fetchGlobalElem_10()
println(elem_10.x)
```

### gen_100_global_array_return_10.expect
```
14
13
10
```

## Test: gen_100_global_array_return_11

### gen_100_global_array_return_11.fg
```javascript
type GlobObj_11 = { x: int, y: int }
var g_arr_11: GlobObj_11[3] = [{x: 11, y: 12}, {x: 13, y: 14}, {x: 15, y: 16}]
fun fetchGlobal_11() -> GlobObj_11[3] {
  return g_arr_11
}
fun fetchGlobalElem_11() -> GlobObj_11 {
  return g_arr_11[0]
}
var fetched_11: GlobObj_11[3] = fetchGlobal_11()
println(fetched_11[2].x)
println(fetched_11[1].y)
var elem_11: GlobObj_11 = fetchGlobalElem_11()
println(elem_11.x)
```

### gen_100_global_array_return_11.expect
```
15
14
11
```

## Test: gen_100_global_array_return_12

### gen_100_global_array_return_12.fg
```javascript
type GlobObj_12 = { x: int, y: int }
var g_arr_12: GlobObj_12[3] = [{x: 12, y: 13}, {x: 14, y: 15}, {x: 16, y: 17}]
fun fetchGlobal_12() -> GlobObj_12[3] {
  return g_arr_12
}
fun fetchGlobalElem_12() -> GlobObj_12 {
  return g_arr_12[0]
}
var fetched_12: GlobObj_12[3] = fetchGlobal_12()
println(fetched_12[2].x)
println(fetched_12[1].y)
var elem_12: GlobObj_12 = fetchGlobalElem_12()
println(elem_12.x)
```

### gen_100_global_array_return_12.expect
```
16
15
12
```

## Test: gen_100_global_array_return_13

### gen_100_global_array_return_13.fg
```javascript
type GlobObj_13 = { x: int, y: int }
var g_arr_13: GlobObj_13[3] = [{x: 13, y: 14}, {x: 15, y: 16}, {x: 17, y: 18}]
fun fetchGlobal_13() -> GlobObj_13[3] {
  return g_arr_13
}
fun fetchGlobalElem_13() -> GlobObj_13 {
  return g_arr_13[0]
}
var fetched_13: GlobObj_13[3] = fetchGlobal_13()
println(fetched_13[2].x)
println(fetched_13[1].y)
var elem_13: GlobObj_13 = fetchGlobalElem_13()
println(elem_13.x)
```

### gen_100_global_array_return_13.expect
```
17
16
13
```

## Test: gen_100_global_array_return_14

### gen_100_global_array_return_14.fg
```javascript
type GlobObj_14 = { x: int, y: int }
var g_arr_14: GlobObj_14[3] = [{x: 14, y: 15}, {x: 16, y: 17}, {x: 18, y: 19}]
fun fetchGlobal_14() -> GlobObj_14[3] {
  return g_arr_14
}
fun fetchGlobalElem_14() -> GlobObj_14 {
  return g_arr_14[0]
}
var fetched_14: GlobObj_14[3] = fetchGlobal_14()
println(fetched_14[2].x)
println(fetched_14[1].y)
var elem_14: GlobObj_14 = fetchGlobalElem_14()
println(elem_14.x)
```

### gen_100_global_array_return_14.expect
```
18
17
14
```

## Test: gen_100_global_array_return_15

### gen_100_global_array_return_15.fg
```javascript
type GlobObj_15 = { x: int, y: int }
var g_arr_15: GlobObj_15[3] = [{x: 15, y: 16}, {x: 17, y: 18}, {x: 19, y: 20}]
fun fetchGlobal_15() -> GlobObj_15[3] {
  return g_arr_15
}
fun fetchGlobalElem_15() -> GlobObj_15 {
  return g_arr_15[0]
}
var fetched_15: GlobObj_15[3] = fetchGlobal_15()
println(fetched_15[2].x)
println(fetched_15[1].y)
var elem_15: GlobObj_15 = fetchGlobalElem_15()
println(elem_15.x)
```

### gen_100_global_array_return_15.expect
```
19
18
15
```

## Test: gen_100_global_array_return_16

### gen_100_global_array_return_16.fg
```javascript
type GlobObj_16 = { x: int, y: int }
var g_arr_16: GlobObj_16[3] = [{x: 16, y: 17}, {x: 18, y: 19}, {x: 20, y: 21}]
fun fetchGlobal_16() -> GlobObj_16[3] {
  return g_arr_16
}
fun fetchGlobalElem_16() -> GlobObj_16 {
  return g_arr_16[0]
}
var fetched_16: GlobObj_16[3] = fetchGlobal_16()
println(fetched_16[2].x)
println(fetched_16[1].y)
var elem_16: GlobObj_16 = fetchGlobalElem_16()
println(elem_16.x)
```

### gen_100_global_array_return_16.expect
```
20
19
16
```

## Test: gen_100_global_array_return_17

### gen_100_global_array_return_17.fg
```javascript
type GlobObj_17 = { x: int, y: int }
var g_arr_17: GlobObj_17[3] = [{x: 17, y: 18}, {x: 19, y: 20}, {x: 21, y: 22}]
fun fetchGlobal_17() -> GlobObj_17[3] {
  return g_arr_17
}
fun fetchGlobalElem_17() -> GlobObj_17 {
  return g_arr_17[0]
}
var fetched_17: GlobObj_17[3] = fetchGlobal_17()
println(fetched_17[2].x)
println(fetched_17[1].y)
var elem_17: GlobObj_17 = fetchGlobalElem_17()
println(elem_17.x)
```

### gen_100_global_array_return_17.expect
```
21
20
17
```

## Test: gen_100_global_array_return_18

### gen_100_global_array_return_18.fg
```javascript
type GlobObj_18 = { x: int, y: int }
var g_arr_18: GlobObj_18[3] = [{x: 18, y: 19}, {x: 20, y: 21}, {x: 22, y: 23}]
fun fetchGlobal_18() -> GlobObj_18[3] {
  return g_arr_18
}
fun fetchGlobalElem_18() -> GlobObj_18 {
  return g_arr_18[0]
}
var fetched_18: GlobObj_18[3] = fetchGlobal_18()
println(fetched_18[2].x)
println(fetched_18[1].y)
var elem_18: GlobObj_18 = fetchGlobalElem_18()
println(elem_18.x)
```

### gen_100_global_array_return_18.expect
```
22
21
18
```

## Test: gen_100_global_array_return_19

### gen_100_global_array_return_19.fg
```javascript
type GlobObj_19 = { x: int, y: int }
var g_arr_19: GlobObj_19[3] = [{x: 19, y: 20}, {x: 21, y: 22}, {x: 23, y: 24}]
fun fetchGlobal_19() -> GlobObj_19[3] {
  return g_arr_19
}
fun fetchGlobalElem_19() -> GlobObj_19 {
  return g_arr_19[0]
}
var fetched_19: GlobObj_19[3] = fetchGlobal_19()
println(fetched_19[2].x)
println(fetched_19[1].y)
var elem_19: GlobObj_19 = fetchGlobalElem_19()
println(elem_19.x)
```

### gen_100_global_array_return_19.expect
```
23
22
19
```

## Test: gen_100_global_array_return_2

### gen_100_global_array_return_2.fg
```javascript
type GlobObj_2 = { x: int, y: int }
var g_arr_2: GlobObj_2[3] = [{x: 2, y: 3}, {x: 4, y: 5}, {x: 6, y: 7}]
fun fetchGlobal_2() -> GlobObj_2[3] {
  return g_arr_2
}
fun fetchGlobalElem_2() -> GlobObj_2 {
  return g_arr_2[0]
}
var fetched_2: GlobObj_2[3] = fetchGlobal_2()
println(fetched_2[2].x)
println(fetched_2[1].y)
var elem_2: GlobObj_2 = fetchGlobalElem_2()
println(elem_2.x)
```

### gen_100_global_array_return_2.expect
```
6
5
2
```

## Test: gen_100_global_array_return_20

### gen_100_global_array_return_20.fg
```javascript
type GlobObj_20 = { x: int, y: int }
var g_arr_20: GlobObj_20[3] = [{x: 20, y: 21}, {x: 22, y: 23}, {x: 24, y: 25}]
fun fetchGlobal_20() -> GlobObj_20[3] {
  return g_arr_20
}
fun fetchGlobalElem_20() -> GlobObj_20 {
  return g_arr_20[0]
}
var fetched_20: GlobObj_20[3] = fetchGlobal_20()
println(fetched_20[2].x)
println(fetched_20[1].y)
var elem_20: GlobObj_20 = fetchGlobalElem_20()
println(elem_20.x)
```

### gen_100_global_array_return_20.expect
```
24
23
20
```

## Test: gen_100_global_array_return_3

### gen_100_global_array_return_3.fg
```javascript
type GlobObj_3 = { x: int, y: int }
var g_arr_3: GlobObj_3[3] = [{x: 3, y: 4}, {x: 5, y: 6}, {x: 7, y: 8}]
fun fetchGlobal_3() -> GlobObj_3[3] {
  return g_arr_3
}
fun fetchGlobalElem_3() -> GlobObj_3 {
  return g_arr_3[0]
}
var fetched_3: GlobObj_3[3] = fetchGlobal_3()
println(fetched_3[2].x)
println(fetched_3[1].y)
var elem_3: GlobObj_3 = fetchGlobalElem_3()
println(elem_3.x)
```

### gen_100_global_array_return_3.expect
```
7
6
3
```

## Test: gen_100_global_array_return_4

### gen_100_global_array_return_4.fg
```javascript
type GlobObj_4 = { x: int, y: int }
var g_arr_4: GlobObj_4[3] = [{x: 4, y: 5}, {x: 6, y: 7}, {x: 8, y: 9}]
fun fetchGlobal_4() -> GlobObj_4[3] {
  return g_arr_4
}
fun fetchGlobalElem_4() -> GlobObj_4 {
  return g_arr_4[0]
}
var fetched_4: GlobObj_4[3] = fetchGlobal_4()
println(fetched_4[2].x)
println(fetched_4[1].y)
var elem_4: GlobObj_4 = fetchGlobalElem_4()
println(elem_4.x)
```

### gen_100_global_array_return_4.expect
```
8
7
4
```

## Test: gen_100_global_array_return_5

### gen_100_global_array_return_5.fg
```javascript
type GlobObj_5 = { x: int, y: int }
var g_arr_5: GlobObj_5[3] = [{x: 5, y: 6}, {x: 7, y: 8}, {x: 9, y: 10}]
fun fetchGlobal_5() -> GlobObj_5[3] {
  return g_arr_5
}
fun fetchGlobalElem_5() -> GlobObj_5 {
  return g_arr_5[0]
}
var fetched_5: GlobObj_5[3] = fetchGlobal_5()
println(fetched_5[2].x)
println(fetched_5[1].y)
var elem_5: GlobObj_5 = fetchGlobalElem_5()
println(elem_5.x)
```

### gen_100_global_array_return_5.expect
```
9
8
5
```

## Test: gen_100_global_array_return_6

### gen_100_global_array_return_6.fg
```javascript
type GlobObj_6 = { x: int, y: int }
var g_arr_6: GlobObj_6[3] = [{x: 6, y: 7}, {x: 8, y: 9}, {x: 10, y: 11}]
fun fetchGlobal_6() -> GlobObj_6[3] {
  return g_arr_6
}
fun fetchGlobalElem_6() -> GlobObj_6 {
  return g_arr_6[0]
}
var fetched_6: GlobObj_6[3] = fetchGlobal_6()
println(fetched_6[2].x)
println(fetched_6[1].y)
var elem_6: GlobObj_6 = fetchGlobalElem_6()
println(elem_6.x)
```

### gen_100_global_array_return_6.expect
```
10
9
6
```

## Test: gen_100_global_array_return_7

### gen_100_global_array_return_7.fg
```javascript
type GlobObj_7 = { x: int, y: int }
var g_arr_7: GlobObj_7[3] = [{x: 7, y: 8}, {x: 9, y: 10}, {x: 11, y: 12}]
fun fetchGlobal_7() -> GlobObj_7[3] {
  return g_arr_7
}
fun fetchGlobalElem_7() -> GlobObj_7 {
  return g_arr_7[0]
}
var fetched_7: GlobObj_7[3] = fetchGlobal_7()
println(fetched_7[2].x)
println(fetched_7[1].y)
var elem_7: GlobObj_7 = fetchGlobalElem_7()
println(elem_7.x)
```

### gen_100_global_array_return_7.expect
```
11
10
7
```

## Test: gen_100_global_array_return_8

### gen_100_global_array_return_8.fg
```javascript
type GlobObj_8 = { x: int, y: int }
var g_arr_8: GlobObj_8[3] = [{x: 8, y: 9}, {x: 10, y: 11}, {x: 12, y: 13}]
fun fetchGlobal_8() -> GlobObj_8[3] {
  return g_arr_8
}
fun fetchGlobalElem_8() -> GlobObj_8 {
  return g_arr_8[0]
}
var fetched_8: GlobObj_8[3] = fetchGlobal_8()
println(fetched_8[2].x)
println(fetched_8[1].y)
var elem_8: GlobObj_8 = fetchGlobalElem_8()
println(elem_8.x)
```

### gen_100_global_array_return_8.expect
```
12
11
8
```

## Test: gen_100_global_array_return_9

### gen_100_global_array_return_9.fg
```javascript
type GlobObj_9 = { x: int, y: int }
var g_arr_9: GlobObj_9[3] = [{x: 9, y: 10}, {x: 11, y: 12}, {x: 13, y: 14}]
fun fetchGlobal_9() -> GlobObj_9[3] {
  return g_arr_9
}
fun fetchGlobalElem_9() -> GlobObj_9 {
  return g_arr_9[0]
}
var fetched_9: GlobObj_9[3] = fetchGlobal_9()
println(fetched_9[2].x)
println(fetched_9[1].y)
var elem_9: GlobObj_9 = fetchGlobalElem_9()
println(elem_9.x)
```

### gen_100_global_array_return_9.expect
```
13
12
9
```

## Test: gen_100_inout_struct_mod_1

### gen_100_inout_struct_mod_1.fg
```javascript
type P_1 = { x: int, y: int }
type Shape_1 = { pts: P_1[2], id: int }
fun mod_1(inout s: Shape_1[2]) {
  s[0].pts[0].x = 10
  s[1].id = 100
}
var shapes_1: Shape_1[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_1(shapes_1)
println(shapes_1[0].pts[0].x)
println(shapes_1[1].id)
```

### gen_100_inout_struct_mod_1.expect
```
10
100
```

## Test: gen_100_inout_struct_mod_10

### gen_100_inout_struct_mod_10.fg
```javascript
type P_10 = { x: int, y: int }
type Shape_10 = { pts: P_10[2], id: int }
fun mod_10(inout s: Shape_10[2]) {
  s[0].pts[0].x = 100
  s[1].id = 1000
}
var shapes_10: Shape_10[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_10(shapes_10)
println(shapes_10[0].pts[0].x)
println(shapes_10[1].id)
```

### gen_100_inout_struct_mod_10.expect
```
100
1000
```

## Test: gen_100_inout_struct_mod_11

### gen_100_inout_struct_mod_11.fg
```javascript
type P_11 = { x: int, y: int }
type Shape_11 = { pts: P_11[2], id: int }
fun mod_11(inout s: Shape_11[2]) {
  s[0].pts[0].x = 110
  s[1].id = 1100
}
var shapes_11: Shape_11[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_11(shapes_11)
println(shapes_11[0].pts[0].x)
println(shapes_11[1].id)
```

### gen_100_inout_struct_mod_11.expect
```
110
1100
```

## Test: gen_100_inout_struct_mod_12

### gen_100_inout_struct_mod_12.fg
```javascript
type P_12 = { x: int, y: int }
type Shape_12 = { pts: P_12[2], id: int }
fun mod_12(inout s: Shape_12[2]) {
  s[0].pts[0].x = 120
  s[1].id = 1200
}
var shapes_12: Shape_12[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_12(shapes_12)
println(shapes_12[0].pts[0].x)
println(shapes_12[1].id)
```

### gen_100_inout_struct_mod_12.expect
```
120
1200
```

## Test: gen_100_inout_struct_mod_13

### gen_100_inout_struct_mod_13.fg
```javascript
type P_13 = { x: int, y: int }
type Shape_13 = { pts: P_13[2], id: int }
fun mod_13(inout s: Shape_13[2]) {
  s[0].pts[0].x = 130
  s[1].id = 1300
}
var shapes_13: Shape_13[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_13(shapes_13)
println(shapes_13[0].pts[0].x)
println(shapes_13[1].id)
```

### gen_100_inout_struct_mod_13.expect
```
130
1300
```

## Test: gen_100_inout_struct_mod_14

### gen_100_inout_struct_mod_14.fg
```javascript
type P_14 = { x: int, y: int }
type Shape_14 = { pts: P_14[2], id: int }
fun mod_14(inout s: Shape_14[2]) {
  s[0].pts[0].x = 140
  s[1].id = 1400
}
var shapes_14: Shape_14[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_14(shapes_14)
println(shapes_14[0].pts[0].x)
println(shapes_14[1].id)
```

### gen_100_inout_struct_mod_14.expect
```
140
1400
```

## Test: gen_100_inout_struct_mod_15

### gen_100_inout_struct_mod_15.fg
```javascript
type P_15 = { x: int, y: int }
type Shape_15 = { pts: P_15[2], id: int }
fun mod_15(inout s: Shape_15[2]) {
  s[0].pts[0].x = 150
  s[1].id = 1500
}
var shapes_15: Shape_15[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_15(shapes_15)
println(shapes_15[0].pts[0].x)
println(shapes_15[1].id)
```

### gen_100_inout_struct_mod_15.expect
```
150
1500
```

## Test: gen_100_inout_struct_mod_16

### gen_100_inout_struct_mod_16.fg
```javascript
type P_16 = { x: int, y: int }
type Shape_16 = { pts: P_16[2], id: int }
fun mod_16(inout s: Shape_16[2]) {
  s[0].pts[0].x = 160
  s[1].id = 1600
}
var shapes_16: Shape_16[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_16(shapes_16)
println(shapes_16[0].pts[0].x)
println(shapes_16[1].id)
```

### gen_100_inout_struct_mod_16.expect
```
160
1600
```

## Test: gen_100_inout_struct_mod_2

### gen_100_inout_struct_mod_2.fg
```javascript
type P_2 = { x: int, y: int }
type Shape_2 = { pts: P_2[2], id: int }
fun mod_2(inout s: Shape_2[2]) {
  s[0].pts[0].x = 20
  s[1].id = 200
}
var shapes_2: Shape_2[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_2(shapes_2)
println(shapes_2[0].pts[0].x)
println(shapes_2[1].id)
```

### gen_100_inout_struct_mod_2.expect
```
20
200
```

## Test: gen_100_inout_struct_mod_3

### gen_100_inout_struct_mod_3.fg
```javascript
type P_3 = { x: int, y: int }
type Shape_3 = { pts: P_3[2], id: int }
fun mod_3(inout s: Shape_3[2]) {
  s[0].pts[0].x = 30
  s[1].id = 300
}
var shapes_3: Shape_3[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_3(shapes_3)
println(shapes_3[0].pts[0].x)
println(shapes_3[1].id)
```

### gen_100_inout_struct_mod_3.expect
```
30
300
```

## Test: gen_100_inout_struct_mod_4

### gen_100_inout_struct_mod_4.fg
```javascript
type P_4 = { x: int, y: int }
type Shape_4 = { pts: P_4[2], id: int }
fun mod_4(inout s: Shape_4[2]) {
  s[0].pts[0].x = 40
  s[1].id = 400
}
var shapes_4: Shape_4[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_4(shapes_4)
println(shapes_4[0].pts[0].x)
println(shapes_4[1].id)
```

### gen_100_inout_struct_mod_4.expect
```
40
400
```

## Test: gen_100_inout_struct_mod_5

### gen_100_inout_struct_mod_5.fg
```javascript
type P_5 = { x: int, y: int }
type Shape_5 = { pts: P_5[2], id: int }
fun mod_5(inout s: Shape_5[2]) {
  s[0].pts[0].x = 50
  s[1].id = 500
}
var shapes_5: Shape_5[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_5(shapes_5)
println(shapes_5[0].pts[0].x)
println(shapes_5[1].id)
```

### gen_100_inout_struct_mod_5.expect
```
50
500
```

## Test: gen_100_inout_struct_mod_6

### gen_100_inout_struct_mod_6.fg
```javascript
type P_6 = { x: int, y: int }
type Shape_6 = { pts: P_6[2], id: int }
fun mod_6(inout s: Shape_6[2]) {
  s[0].pts[0].x = 60
  s[1].id = 600
}
var shapes_6: Shape_6[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_6(shapes_6)
println(shapes_6[0].pts[0].x)
println(shapes_6[1].id)
```

### gen_100_inout_struct_mod_6.expect
```
60
600
```

## Test: gen_100_inout_struct_mod_7

### gen_100_inout_struct_mod_7.fg
```javascript
type P_7 = { x: int, y: int }
type Shape_7 = { pts: P_7[2], id: int }
fun mod_7(inout s: Shape_7[2]) {
  s[0].pts[0].x = 70
  s[1].id = 700
}
var shapes_7: Shape_7[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_7(shapes_7)
println(shapes_7[0].pts[0].x)
println(shapes_7[1].id)
```

### gen_100_inout_struct_mod_7.expect
```
70
700
```

## Test: gen_100_inout_struct_mod_8

### gen_100_inout_struct_mod_8.fg
```javascript
type P_8 = { x: int, y: int }
type Shape_8 = { pts: P_8[2], id: int }
fun mod_8(inout s: Shape_8[2]) {
  s[0].pts[0].x = 80
  s[1].id = 800
}
var shapes_8: Shape_8[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_8(shapes_8)
println(shapes_8[0].pts[0].x)
println(shapes_8[1].id)
```

### gen_100_inout_struct_mod_8.expect
```
80
800
```

## Test: gen_100_inout_struct_mod_9

### gen_100_inout_struct_mod_9.fg
```javascript
type P_9 = { x: int, y: int }
type Shape_9 = { pts: P_9[2], id: int }
fun mod_9(inout s: Shape_9[2]) {
  s[0].pts[0].x = 90
  s[1].id = 900
}
var shapes_9: Shape_9[2] = [
  {pts: [{x: 0, y: 1}, {x: 2, y: 3}], id: 1},
  {pts: [{x: 4, y: 5}, {x: 6, y: 7}], id: 2}
]
mod_9(shapes_9)
println(shapes_9[0].pts[0].x)
println(shapes_9[1].id)
```

### gen_100_inout_struct_mod_9.expect
```
90
900
```

## Test: gen_100_multi_bool_bool

### gen_100_multi_bool_bool.fg
```javascript
type O1_bool_m = { v: bool }
type O2_bool_m = { v: bool }
fun get_m_bool_bool() -> O1_bool_m[2], O2_bool_m[2] {
  return [{v: true}, {v: true}], [{v: false}, {v: false}]
}
var r1_bool_bool: O1_bool_m[2], r2_bool_bool: O2_bool_m[2] = get_m_bool_bool()
println(r1_bool_bool[1].v)
println(r2_bool_bool[0].v)
```

### gen_100_multi_bool_bool.expect
```
true
false
```

## Test: gen_100_multi_bool_char

### gen_100_multi_bool_char.fg
```javascript
type O1_bool_m = { v: bool }
type O2_char_m = { v: char }
fun get_m_bool_char() -> O1_bool_m[2], O2_char_m[2] {
  return [{v: true}, {v: true}], [{v: 'B'}, {v: 'B'}]
}
var r1_bool_char: O1_bool_m[2], r2_bool_char: O2_char_m[2] = get_m_bool_char()
println(r1_bool_char[1].v)
println(r2_bool_char[0].v)
```

### gen_100_multi_bool_char.expect
```
true
B
```

## Test: gen_100_multi_bool_deci

### gen_100_multi_bool_deci.fg
```javascript
type O1_bool_m = { v: bool }
type O2_deci_m = { v: deci }
fun get_m_bool_deci() -> O1_bool_m[2], O2_deci_m[2] {
  return [{v: true}, {v: true}], [{v: 20.5}, {v: 20.5}]
}
var r1_bool_deci: O1_bool_m[2], r2_bool_deci: O2_deci_m[2] = get_m_bool_deci()
println(r1_bool_deci[1].v)
println(r2_bool_deci[0].v)
```

### gen_100_multi_bool_deci.expect
```
true
20.5
```

## Test: gen_100_multi_bool_int

### gen_100_multi_bool_int.fg
```javascript
type O1_bool_m = { v: bool }
type O2_int_m = { v: int }
fun get_m_bool_int() -> O1_bool_m[2], O2_int_m[2] {
  return [{v: true}, {v: true}], [{v: 20}, {v: 20}]
}
var r1_bool_int: O1_bool_m[2], r2_bool_int: O2_int_m[2] = get_m_bool_int()
println(r1_bool_int[1].v)
println(r2_bool_int[0].v)
```

### gen_100_multi_bool_int.expect
```
true
20
```

## Test: gen_100_multi_bool_int8

### gen_100_multi_bool_int8.fg
```javascript
type O1_bool_m = { v: bool }
type O2_int8_m = { v: int8 }
fun get_m_bool_int8() -> O1_bool_m[2], O2_int8_m[2] {
  return [{v: true}, {v: true}], [{v: 2}, {v: 2}]
}
var r1_bool_int8: O1_bool_m[2], r2_bool_int8: O2_int8_m[2] = get_m_bool_int8()
println(r1_bool_int8[1].v)
println(r2_bool_int8[0].v)
```

### gen_100_multi_bool_int8.expect
```
true
2
```

## Test: gen_100_multi_bool_str

### gen_100_multi_bool_str.fg
```javascript
type O1_bool_m = { v: bool }
type O2_str_m = { v: str }
fun get_m_bool_str() -> O1_bool_m[2], O2_str_m[2] {
  return [{v: true}, {v: true}], [{v: "World"}, {v: "World"}]
}
var r1_bool_str: O1_bool_m[2], r2_bool_str: O2_str_m[2] = get_m_bool_str()
println(r1_bool_str[1].v)
println(r2_bool_str[0].v)
```

### gen_100_multi_bool_str.expect
```
true
World
```

## Test: gen_100_multi_char_bool

### gen_100_multi_char_bool.fg
```javascript
type O1_char_m = { v: char }
type O2_bool_m = { v: bool }
fun get_m_char_bool() -> O1_char_m[2], O2_bool_m[2] {
  return [{v: 'A'}, {v: 'A'}], [{v: false}, {v: false}]
}
var r1_char_bool: O1_char_m[2], r2_char_bool: O2_bool_m[2] = get_m_char_bool()
println(r1_char_bool[1].v)
println(r2_char_bool[0].v)
```

### gen_100_multi_char_bool.expect
```
A
false
```

## Test: gen_100_multi_char_char

### gen_100_multi_char_char.fg
```javascript
type O1_char_m = { v: char }
type O2_char_m = { v: char }
fun get_m_char_char() -> O1_char_m[2], O2_char_m[2] {
  return [{v: 'A'}, {v: 'A'}], [{v: 'B'}, {v: 'B'}]
}
var r1_char_char: O1_char_m[2], r2_char_char: O2_char_m[2] = get_m_char_char()
println(r1_char_char[1].v)
println(r2_char_char[0].v)
```

### gen_100_multi_char_char.expect
```
A
B
```

## Test: gen_100_multi_char_deci

### gen_100_multi_char_deci.fg
```javascript
type O1_char_m = { v: char }
type O2_deci_m = { v: deci }
fun get_m_char_deci() -> O1_char_m[2], O2_deci_m[2] {
  return [{v: 'A'}, {v: 'A'}], [{v: 20.5}, {v: 20.5}]
}
var r1_char_deci: O1_char_m[2], r2_char_deci: O2_deci_m[2] = get_m_char_deci()
println(r1_char_deci[1].v)
println(r2_char_deci[0].v)
```

### gen_100_multi_char_deci.expect
```
A
20.5
```

## Test: gen_100_multi_char_int

### gen_100_multi_char_int.fg
```javascript
type O1_char_m = { v: char }
type O2_int_m = { v: int }
fun get_m_char_int() -> O1_char_m[2], O2_int_m[2] {
  return [{v: 'A'}, {v: 'A'}], [{v: 20}, {v: 20}]
}
var r1_char_int: O1_char_m[2], r2_char_int: O2_int_m[2] = get_m_char_int()
println(r1_char_int[1].v)
println(r2_char_int[0].v)
```

### gen_100_multi_char_int.expect
```
A
20
```

## Test: gen_100_multi_char_int8

### gen_100_multi_char_int8.fg
```javascript
type O1_char_m = { v: char }
type O2_int8_m = { v: int8 }
fun get_m_char_int8() -> O1_char_m[2], O2_int8_m[2] {
  return [{v: 'A'}, {v: 'A'}], [{v: 2}, {v: 2}]
}
var r1_char_int8: O1_char_m[2], r2_char_int8: O2_int8_m[2] = get_m_char_int8()
println(r1_char_int8[1].v)
println(r2_char_int8[0].v)
```

### gen_100_multi_char_int8.expect
```
A
2
```

## Test: gen_100_multi_char_str

### gen_100_multi_char_str.fg
```javascript
type O1_char_m = { v: char }
type O2_str_m = { v: str }
fun get_m_char_str() -> O1_char_m[2], O2_str_m[2] {
  return [{v: 'A'}, {v: 'A'}], [{v: "World"}, {v: "World"}]
}
var r1_char_str: O1_char_m[2], r2_char_str: O2_str_m[2] = get_m_char_str()
println(r1_char_str[1].v)
println(r2_char_str[0].v)
```

### gen_100_multi_char_str.expect
```
A
World
```

## Test: gen_100_multi_deci_bool

### gen_100_multi_deci_bool.fg
```javascript
type O1_deci_m = { v: deci }
type O2_bool_m = { v: bool }
fun get_m_deci_bool() -> O1_deci_m[2], O2_bool_m[2] {
  return [{v: 10.5}, {v: 10.5}], [{v: false}, {v: false}]
}
var r1_deci_bool: O1_deci_m[2], r2_deci_bool: O2_bool_m[2] = get_m_deci_bool()
println(r1_deci_bool[1].v)
println(r2_deci_bool[0].v)
```

### gen_100_multi_deci_bool.expect
```
10.5
false
```

## Test: gen_100_multi_deci_char

### gen_100_multi_deci_char.fg
```javascript
type O1_deci_m = { v: deci }
type O2_char_m = { v: char }
fun get_m_deci_char() -> O1_deci_m[2], O2_char_m[2] {
  return [{v: 10.5}, {v: 10.5}], [{v: 'B'}, {v: 'B'}]
}
var r1_deci_char: O1_deci_m[2], r2_deci_char: O2_char_m[2] = get_m_deci_char()
println(r1_deci_char[1].v)
println(r2_deci_char[0].v)
```

### gen_100_multi_deci_char.expect
```
10.5
B
```

## Test: gen_100_multi_deci_deci

### gen_100_multi_deci_deci.fg
```javascript
type O1_deci_m = { v: deci }
type O2_deci_m = { v: deci }
fun get_m_deci_deci() -> O1_deci_m[2], O2_deci_m[2] {
  return [{v: 10.5}, {v: 10.5}], [{v: 20.5}, {v: 20.5}]
}
var r1_deci_deci: O1_deci_m[2], r2_deci_deci: O2_deci_m[2] = get_m_deci_deci()
println(r1_deci_deci[1].v)
println(r2_deci_deci[0].v)
```

### gen_100_multi_deci_deci.expect
```
10.5
20.5
```

## Test: gen_100_multi_deci_int

### gen_100_multi_deci_int.fg
```javascript
type O1_deci_m = { v: deci }
type O2_int_m = { v: int }
fun get_m_deci_int() -> O1_deci_m[2], O2_int_m[2] {
  return [{v: 10.5}, {v: 10.5}], [{v: 20}, {v: 20}]
}
var r1_deci_int: O1_deci_m[2], r2_deci_int: O2_int_m[2] = get_m_deci_int()
println(r1_deci_int[1].v)
println(r2_deci_int[0].v)
```

### gen_100_multi_deci_int.expect
```
10.5
20
```

## Test: gen_100_multi_deci_int8

### gen_100_multi_deci_int8.fg
```javascript
type O1_deci_m = { v: deci }
type O2_int8_m = { v: int8 }
fun get_m_deci_int8() -> O1_deci_m[2], O2_int8_m[2] {
  return [{v: 10.5}, {v: 10.5}], [{v: 2}, {v: 2}]
}
var r1_deci_int8: O1_deci_m[2], r2_deci_int8: O2_int8_m[2] = get_m_deci_int8()
println(r1_deci_int8[1].v)
println(r2_deci_int8[0].v)
```

### gen_100_multi_deci_int8.expect
```
10.5
2
```

## Test: gen_100_multi_deci_str

### gen_100_multi_deci_str.fg
```javascript
type O1_deci_m = { v: deci }
type O2_str_m = { v: str }
fun get_m_deci_str() -> O1_deci_m[2], O2_str_m[2] {
  return [{v: 10.5}, {v: 10.5}], [{v: "World"}, {v: "World"}]
}
var r1_deci_str: O1_deci_m[2], r2_deci_str: O2_str_m[2] = get_m_deci_str()
println(r1_deci_str[1].v)
println(r2_deci_str[0].v)
```

### gen_100_multi_deci_str.expect
```
10.5
World
```

## Test: gen_100_multi_int8_bool

### gen_100_multi_int8_bool.fg
```javascript
type O1_int8_m = { v: int8 }
type O2_bool_m = { v: bool }
fun get_m_int8_bool() -> O1_int8_m[2], O2_bool_m[2] {
  return [{v: 1}, {v: 1}], [{v: false}, {v: false}]
}
var r1_int8_bool: O1_int8_m[2], r2_int8_bool: O2_bool_m[2] = get_m_int8_bool()
println(r1_int8_bool[1].v)
println(r2_int8_bool[0].v)
```

### gen_100_multi_int8_bool.expect
```
1
false
```

## Test: gen_100_multi_int8_char

### gen_100_multi_int8_char.fg
```javascript
type O1_int8_m = { v: int8 }
type O2_char_m = { v: char }
fun get_m_int8_char() -> O1_int8_m[2], O2_char_m[2] {
  return [{v: 1}, {v: 1}], [{v: 'B'}, {v: 'B'}]
}
var r1_int8_char: O1_int8_m[2], r2_int8_char: O2_char_m[2] = get_m_int8_char()
println(r1_int8_char[1].v)
println(r2_int8_char[0].v)
```

### gen_100_multi_int8_char.expect
```
1
B
```

## Test: gen_100_multi_int8_deci

### gen_100_multi_int8_deci.fg
```javascript
type O1_int8_m = { v: int8 }
type O2_deci_m = { v: deci }
fun get_m_int8_deci() -> O1_int8_m[2], O2_deci_m[2] {
  return [{v: 1}, {v: 1}], [{v: 20.5}, {v: 20.5}]
}
var r1_int8_deci: O1_int8_m[2], r2_int8_deci: O2_deci_m[2] = get_m_int8_deci()
println(r1_int8_deci[1].v)
println(r2_int8_deci[0].v)
```

### gen_100_multi_int8_deci.expect
```
1
20.5
```

## Test: gen_100_multi_int8_int

### gen_100_multi_int8_int.fg
```javascript
type O1_int8_m = { v: int8 }
type O2_int_m = { v: int }
fun get_m_int8_int() -> O1_int8_m[2], O2_int_m[2] {
  return [{v: 1}, {v: 1}], [{v: 20}, {v: 20}]
}
var r1_int8_int: O1_int8_m[2], r2_int8_int: O2_int_m[2] = get_m_int8_int()
println(r1_int8_int[1].v)
println(r2_int8_int[0].v)
```

### gen_100_multi_int8_int.expect
```
1
20
```

## Test: gen_100_multi_int8_int8

### gen_100_multi_int8_int8.fg
```javascript
type O1_int8_m = { v: int8 }
type O2_int8_m = { v: int8 }
fun get_m_int8_int8() -> O1_int8_m[2], O2_int8_m[2] {
  return [{v: 1}, {v: 1}], [{v: 2}, {v: 2}]
}
var r1_int8_int8: O1_int8_m[2], r2_int8_int8: O2_int8_m[2] = get_m_int8_int8()
println(r1_int8_int8[1].v)
println(r2_int8_int8[0].v)
```

### gen_100_multi_int8_int8.expect
```
1
2
```

## Test: gen_100_multi_int8_str

### gen_100_multi_int8_str.fg
```javascript
type O1_int8_m = { v: int8 }
type O2_str_m = { v: str }
fun get_m_int8_str() -> O1_int8_m[2], O2_str_m[2] {
  return [{v: 1}, {v: 1}], [{v: "World"}, {v: "World"}]
}
var r1_int8_str: O1_int8_m[2], r2_int8_str: O2_str_m[2] = get_m_int8_str()
println(r1_int8_str[1].v)
println(r2_int8_str[0].v)
```

### gen_100_multi_int8_str.expect
```
1
World
```

## Test: gen_100_multi_int_bool

### gen_100_multi_int_bool.fg
```javascript
type O1_int_m = { v: int }
type O2_bool_m = { v: bool }
fun get_m_int_bool() -> O1_int_m[2], O2_bool_m[2] {
  return [{v: 10}, {v: 10}], [{v: false}, {v: false}]
}
var r1_int_bool: O1_int_m[2], r2_int_bool: O2_bool_m[2] = get_m_int_bool()
println(r1_int_bool[1].v)
println(r2_int_bool[0].v)
```

### gen_100_multi_int_bool.expect
```
10
false
```

## Test: gen_100_multi_int_char

### gen_100_multi_int_char.fg
```javascript
type O1_int_m = { v: int }
type O2_char_m = { v: char }
fun get_m_int_char() -> O1_int_m[2], O2_char_m[2] {
  return [{v: 10}, {v: 10}], [{v: 'B'}, {v: 'B'}]
}
var r1_int_char: O1_int_m[2], r2_int_char: O2_char_m[2] = get_m_int_char()
println(r1_int_char[1].v)
println(r2_int_char[0].v)
```

### gen_100_multi_int_char.expect
```
10
B
```

## Test: gen_100_multi_int_deci

### gen_100_multi_int_deci.fg
```javascript
type O1_int_m = { v: int }
type O2_deci_m = { v: deci }
fun get_m_int_deci() -> O1_int_m[2], O2_deci_m[2] {
  return [{v: 10}, {v: 10}], [{v: 20.5}, {v: 20.5}]
}
var r1_int_deci: O1_int_m[2], r2_int_deci: O2_deci_m[2] = get_m_int_deci()
println(r1_int_deci[1].v)
println(r2_int_deci[0].v)
```

### gen_100_multi_int_deci.expect
```
10
20.5
```

## Test: gen_100_multi_int_int

### gen_100_multi_int_int.fg
```javascript
type O1_int_m = { v: int }
type O2_int_m = { v: int }
fun get_m_int_int() -> O1_int_m[2], O2_int_m[2] {
  return [{v: 10}, {v: 10}], [{v: 20}, {v: 20}]
}
var r1_int_int: O1_int_m[2], r2_int_int: O2_int_m[2] = get_m_int_int()
println(r1_int_int[1].v)
println(r2_int_int[0].v)
```

### gen_100_multi_int_int.expect
```
10
20
```

## Test: gen_100_multi_int_int8

### gen_100_multi_int_int8.fg
```javascript
type O1_int_m = { v: int }
type O2_int8_m = { v: int8 }
fun get_m_int_int8() -> O1_int_m[2], O2_int8_m[2] {
  return [{v: 10}, {v: 10}], [{v: 2}, {v: 2}]
}
var r1_int_int8: O1_int_m[2], r2_int_int8: O2_int8_m[2] = get_m_int_int8()
println(r1_int_int8[1].v)
println(r2_int_int8[0].v)
```

### gen_100_multi_int_int8.expect
```
10
2
```

## Test: gen_100_multi_int_str

### gen_100_multi_int_str.fg
```javascript
type O1_int_m = { v: int }
type O2_str_m = { v: str }
fun get_m_int_str() -> O1_int_m[2], O2_str_m[2] {
  return [{v: 10}, {v: 10}], [{v: "World"}, {v: "World"}]
}
var r1_int_str: O1_int_m[2], r2_int_str: O2_str_m[2] = get_m_int_str()
println(r1_int_str[1].v)
println(r2_int_str[0].v)
```

### gen_100_multi_int_str.expect
```
10
World
```

## Test: gen_100_multi_str_bool

### gen_100_multi_str_bool.fg
```javascript
type O1_str_m = { v: str }
type O2_bool_m = { v: bool }
fun get_m_str_bool() -> O1_str_m[2], O2_bool_m[2] {
  return [{v: "Hello"}, {v: "Hello"}], [{v: false}, {v: false}]
}
var r1_str_bool: O1_str_m[2], r2_str_bool: O2_bool_m[2] = get_m_str_bool()
println(r1_str_bool[1].v)
println(r2_str_bool[0].v)
```

### gen_100_multi_str_bool.expect
```
Hello
false
```

## Test: gen_100_multi_str_char

### gen_100_multi_str_char.fg
```javascript
type O1_str_m = { v: str }
type O2_char_m = { v: char }
fun get_m_str_char() -> O1_str_m[2], O2_char_m[2] {
  return [{v: "Hello"}, {v: "Hello"}], [{v: 'B'}, {v: 'B'}]
}
var r1_str_char: O1_str_m[2], r2_str_char: O2_char_m[2] = get_m_str_char()
println(r1_str_char[1].v)
println(r2_str_char[0].v)
```

### gen_100_multi_str_char.expect
```
Hello
B
```

## Test: gen_100_multi_str_deci

### gen_100_multi_str_deci.fg
```javascript
type O1_str_m = { v: str }
type O2_deci_m = { v: deci }
fun get_m_str_deci() -> O1_str_m[2], O2_deci_m[2] {
  return [{v: "Hello"}, {v: "Hello"}], [{v: 20.5}, {v: 20.5}]
}
var r1_str_deci: O1_str_m[2], r2_str_deci: O2_deci_m[2] = get_m_str_deci()
println(r1_str_deci[1].v)
println(r2_str_deci[0].v)
```

### gen_100_multi_str_deci.expect
```
Hello
20.5
```

## Test: gen_100_multi_str_int

### gen_100_multi_str_int.fg
```javascript
type O1_str_m = { v: str }
type O2_int_m = { v: int }
fun get_m_str_int() -> O1_str_m[2], O2_int_m[2] {
  return [{v: "Hello"}, {v: "Hello"}], [{v: 20}, {v: 20}]
}
var r1_str_int: O1_str_m[2], r2_str_int: O2_int_m[2] = get_m_str_int()
println(r1_str_int[1].v)
println(r2_str_int[0].v)
```

### gen_100_multi_str_int.expect
```
Hello
20
```

## Test: gen_100_multi_str_int8

### gen_100_multi_str_int8.fg
```javascript
type O1_str_m = { v: str }
type O2_int8_m = { v: int8 }
fun get_m_str_int8() -> O1_str_m[2], O2_int8_m[2] {
  return [{v: "Hello"}, {v: "Hello"}], [{v: 2}, {v: 2}]
}
var r1_str_int8: O1_str_m[2], r2_str_int8: O2_int8_m[2] = get_m_str_int8()
println(r1_str_int8[1].v)
println(r2_str_int8[0].v)
```

### gen_100_multi_str_int8.expect
```
Hello
2
```

## Test: gen_100_multi_str_str

### gen_100_multi_str_str.fg
```javascript
type O1_str_m = { v: str }
type O2_str_m = { v: str }
fun get_m_str_str() -> O1_str_m[2], O2_str_m[2] {
  return [{v: "Hello"}, {v: "Hello"}], [{v: "World"}, {v: "World"}]
}
var r1_str_str: O1_str_m[2], r2_str_str: O2_str_m[2] = get_m_str_str()
println(r1_str_str[1].v)
println(r2_str_str[0].v)
```

### gen_100_multi_str_str.expect
```
Hello
World
```

## Test: gen_100_ret_bool

### gen_100_ret_bool.fg
```javascript
type Obj_bool_r = { v: bool }
fun get_r_bool() -> Obj_bool_r[3] { return [{v: true}, {v: false}, {v: true}] }
var a: Obj_bool_r[3] = get_r_bool()
println(a[0].v)
println(a[1].v)
println(a[2].v)
```

### gen_100_ret_bool.expect
```
true
false
true
```

## Test: gen_100_ret_char

### gen_100_ret_char.fg
```javascript
type Obj_char_r = { v: char }
fun get_r_char() -> Obj_char_r[3] { return [{v: 'A'}, {v: 'B'}, {v: 'C'}] }
var a: Obj_char_r[3] = get_r_char()
println(a[0].v)
println(a[1].v)
println(a[2].v)
```

### gen_100_ret_char.expect
```
A
B
C
```

## Test: gen_100_ret_deci

### gen_100_ret_deci.fg
```javascript
type Obj_deci_r = { v: deci }
fun get_r_deci() -> Obj_deci_r[3] { return [{v: 10.5}, {v: 20.5}, {v: 30.5}] }
var a: Obj_deci_r[3] = get_r_deci()
println(a[0].v)
println(a[1].v)
println(a[2].v)
```

### gen_100_ret_deci.expect
```
10.5
20.5
30.5
```

## Test: gen_100_ret_inline_bool

### gen_100_ret_inline_bool.fg
```javascript
type Obj_bool_i = { v: bool }
fun get_i_bool() -> Obj_bool_i[3] { return [{v: true}, {v: false}, {v: true}] }
println(get_i_bool()[0].v)
println(get_i_bool()[1].v)
println(get_i_bool()[2].v)
```

### gen_100_ret_inline_bool.expect
```
true
false
true
```

## Test: gen_100_ret_inline_char

### gen_100_ret_inline_char.fg
```javascript
type Obj_char_i = { v: char }
fun get_i_char() -> Obj_char_i[3] { return [{v: 'A'}, {v: 'B'}, {v: 'C'}] }
println(get_i_char()[0].v)
println(get_i_char()[1].v)
println(get_i_char()[2].v)
```

### gen_100_ret_inline_char.expect
```
A
B
C
```

## Test: gen_100_ret_inline_deci

### gen_100_ret_inline_deci.fg
```javascript
type Obj_deci_i = { v: deci }
fun get_i_deci() -> Obj_deci_i[3] { return [{v: 10.5}, {v: 20.5}, {v: 30.5}] }
println(get_i_deci()[0].v)
println(get_i_deci()[1].v)
println(get_i_deci()[2].v)
```

### gen_100_ret_inline_deci.expect
```
10.5
20.5
30.5
```

## Test: gen_100_ret_inline_int

### gen_100_ret_inline_int.fg
```javascript
type Obj_int_i = { v: int }
fun get_i_int() -> Obj_int_i[3] { return [{v: 10}, {v: 20}, {v: 30}] }
println(get_i_int()[0].v)
println(get_i_int()[1].v)
println(get_i_int()[2].v)
```

### gen_100_ret_inline_int.expect
```
10
20
30
```

## Test: gen_100_ret_inline_int8

### gen_100_ret_inline_int8.fg
```javascript
type Obj_int8_i = { v: int8 }
fun get_i_int8() -> Obj_int8_i[3] { return [{v: 1}, {v: 2}, {v: 3}] }
println(get_i_int8()[0].v)
println(get_i_int8()[1].v)
println(get_i_int8()[2].v)
```

### gen_100_ret_inline_int8.expect
```
1
2
3
```

## Test: gen_100_ret_inline_str

### gen_100_ret_inline_str.fg
```javascript
type Obj_str_i = { v: str }
fun get_i_str() -> Obj_str_i[3] { return [{v: "Hello"}, {v: "World"}, {v: "Flow"}] }
println(get_i_str()[0].v)
println(get_i_str()[1].v)
println(get_i_str()[2].v)
```

### gen_100_ret_inline_str.expect
```
Hello
World
Flow
```

## Test: gen_100_ret_int

### gen_100_ret_int.fg
```javascript
type Obj_int_r = { v: int }
fun get_r_int() -> Obj_int_r[3] { return [{v: 10}, {v: 20}, {v: 30}] }
var a: Obj_int_r[3] = get_r_int()
println(a[0].v)
println(a[1].v)
println(a[2].v)
```

### gen_100_ret_int.expect
```
10
20
30
```

## Test: gen_100_ret_int8

### gen_100_ret_int8.fg
```javascript
type Obj_int8_r = { v: int8 }
fun get_r_int8() -> Obj_int8_r[3] { return [{v: 1}, {v: 2}, {v: 3}] }
var a: Obj_int8_r[3] = get_r_int8()
println(a[0].v)
println(a[1].v)
println(a[2].v)
```

### gen_100_ret_int8.expect
```
1
2
3
```

## Test: gen_100_ret_str

### gen_100_ret_str.fg
```javascript
type Obj_str_r = { v: str }
fun get_r_str() -> Obj_str_r[3] { return [{v: "Hello"}, {v: "World"}, {v: "Flow"}] }
var a: Obj_str_r[3] = get_r_str()
println(a[0].v)
println(a[1].v)
println(a[2].v)
```

### gen_100_ret_str.expect
```
Hello
World
Flow
```

## Test: inout_object_array

### inout_object_array.fg
```javascript
type Item = { id: int, active: bool }

fun toggleItems(inout items: Item[2]) {
  items[0].active = true
  items[0].id = 99
  
  var temp: Item = items[1]
  temp.id = 100
  items[1] = temp
}

var myItems: Item[2] = [{id: 1, active: false}, {id: 2, active: true}]
toggleItems(myItems)
println(myItems[0].id)
println(myItems[0].active)
println(myItems[1].id)
```

### inout_object_array.expect
```
99
true
100
```

## Test: multi_return_object_arrays

### multi_return_object_arrays.fg
```javascript
type A = { a: int }
type B = { b: str }

fun getBoth() -> A[2], B[2] {
  var a_arr: A[2] = [{a: 1}, {a: 2}]
  var b_arr: B[2] = [{b: "one"}, {b: "two"}]
  return a_arr, b_arr
}

var arrA: A[2], arrB: B[2] = getBoth()

println(arrA[1].a)
println(arrB[0].b)
```

### multi_return_object_arrays.expect
```
2
one
```

## Test: object_field_init_from_func

### object_field_init_from_func.fg
```javascript
type Point = {
  x: int
  y: int
}

fun getX() -> int {
  return 5
}

fun getY() -> int {
  return 10
}

var p: Point = {x: getX(), y: getY()}
print(p, "\n")
```

### object_field_init_from_func.expect
```
{ x: 5, y: 10 }
```

## Test: object_inout

### object_inout.fg
```javascript
type Counter = {
  value: int
}

fun increment(inout c: Counter) -> int {
  c.value = c.value + 1
  return c.value
}

var cnt: Counter = {value: 0}
print(cnt, "\n")
increment(cnt)
print(cnt, "\n")
increment(cnt)
print(cnt, "\n")
```

### object_inout.expect
```
{ value: 0 }
{ value: 1 }
{ value: 2 }
```

## Test: object_member_in_call

### object_member_in_call.fg
```javascript
type Point = {
  x: int
  y: int
}

fun doubleN(n: int) -> int {
  return n * 2
}

var pt: Point = {x: 5, y: 10}
println(doubleN(pt.x))
println(doubleN(pt.y))
```

### object_member_in_call.expect
```
10
20
```

## Test: object_param

### object_param.fg
```javascript
type Point = {
  x: int
  y: int
}

fun printPoint(p: Point) -> int {
  print(p, "\n")
  return p.x
}

var pt: Point = {x: 3, y: 4}
printPoint(pt)
```

### object_param.expect
```
{ x: 3, y: 4 }
```

## Test: object_pass_by_value

### object_pass_by_value.fg
```javascript
type Box = {
  value: int
}

fun addOne(b: Box) -> int {
  var v: int = b.value
  return v + 1
}

var b: Box = {value: 10}
println(b.value)
println(addOne(b))
println(b.value)
```

### object_pass_by_value.expect
```
10
11
10
```

## Test: object_pass_by_value_modify_copy

### object_pass_by_value_modify_copy.fg
```javascript
type T = {
  a: int
}

fun modifyCopy(d: T) -> T {
  d.a = 21
  return d
}

var b: T = {a: 10}
var d: T = modifyCopy(b)
println(b.a)
println(d.a)
```

### object_pass_by_value_modify_copy.expect
```
21
21
```

## Test: object_return

### object_return.fg
```javascript
type Person = {
  name: str
  age: int
}

fun makePerson(n: str, a: int) -> Person {
  var p: Person = {name: n, age: a}
  return p
}

var p: Person = makePerson("Alice", 30)
print(p, "\n")
```

### object_return.expect
```
{ age: 30, name: "Alice" }
```

## Test: object_return_access_member_direct

### object_return_access_member_direct.fg
```javascript
type Person = {
  name: str
  age: int
}

fun makePerson(n: str, a: int) -> Person {
  var p: Person = {name: n, age: a}
  return p
}

var p1: Person = makePerson("Alice", 30)
var p2: Person = makePerson("Bob", 25)
println(p1.name)
println(p1.age)
println(p2.name)
println(p2.age)
```

### object_return_access_member_direct.expect
```
Alice
30
Bob
25
```

## Test: object_return_assign_then_access

### object_return_assign_then_access.fg
```javascript
type Person = {
  name: str
  age: int
}

fun makePerson(n: str, a: int) -> Person {
  var p: Person = {name: n, age: a}
  return p
}

var p: Person = makePerson("Bob", 25)
println(p.name)
println(p.age)
```

### object_return_assign_then_access.expect
```
Bob
25
```

## Test: object_return_inline_member_access

### object_return_inline_member_access.fg
```javascript
type Person = {
  name: str
  age: int
}

fun getPerson() -> Person {
    var p: Person = {
        name: "John",
        age: 30
    }
    return p
}

println(getPerson().name)
println(getPerson().age)

var pAge = getPerson().age
println(pAge)

var p2: Person = getPerson()
println(p2.name)

p2.name = "Jane"
println(p2.name)

var p3: Person = getPerson()
p3.age = getPerson().age + 10
println(p3.age)
```

### object_return_inline_member_access.expect
```
John
30
30
John
Jane
40
```

## Test: object_return_reassign_then_access

### object_return_reassign_then_access.fg
```javascript
type Person = {
  name: str
  age: int
}

fun makePerson(n: str, a: int) -> Person {
  var p: Person = {name: n, age: a}
  return p
}

var p: Person = makePerson("Alice", 30)
println(p.name)
p = makePerson("Bob", 40)
println(p.name)
println(p.age)
```

### object_return_reassign_then_access.expect
```
Alice
Bob
40
```

## Test: object_with_array_field_param

### object_with_array_field_param.fg
```javascript
type Wrapper = {
  a: int
  nums: int[3]
}

fun sumNums(w: Wrapper) -> int {
  return w.nums[0] + w.nums[1] + w.nums[2]
}

var w: Wrapper = {a: 0, nums: [1, 2, 3]}
println(sumNums(w))
```

### object_with_array_field_param.expect
```
6
```

## Test: return_complex_struct

### return_complex_struct.fg
```javascript
type Box = {
  matrix: int[2][2],
  name: str
}

fun createBox(n: str, val: int) -> Box {
  var b: Box = {
    matrix: [[val, val + 1], [val + 2, val + 3]],
    name: n
  }
  return b
}

var box1: Box = createBox("boxA", 10)
println(box1.name)
println(box1.matrix[0][1])
println(box1.matrix[1][0])

var box2:Box = createBox("boxB", 100)
println(box2.name)
println(box2.matrix[1][1])
```

### return_complex_struct.expect
```
boxA
11
12
boxB
103
```

## Test: return_mixed_data_types

### return_mixed_data_types.fg
```javascript
type Record = {
  active: bool,
  letter: char,
  score: deci,
  name: str
}

fun getRecords() -> Record[2] {
  var r1: Record = { active: true, letter: 'A', score: 99.5, name: "Alice" }
  var r2: Record = { active: false, letter: 'Z', score: 10.1, name: "Zack" }
  return [r1, r2]
}

var recs: Record[2] = getRecords()
println(recs[0].active)
println(recs[0].letter)
println(recs[0].score)
println(recs[0].name)

println(recs[1].active)
println(recs[1].letter)
println(recs[1].score)
println(recs[1].name)
```

### return_mixed_data_types.expect
```
true
A
99.5
Alice
false
Z
10.1
Zack
```

## Test: return_nested_object_array

### return_nested_object_array.fg
```javascript
type Point = { x: int, y: int }
type Path = { points: Point[2], id: str }

var myPath: Path = {
  points: [{x: 10, y: 20}, {x: 30, y: 40}],
  id: "path1"
}

fun getPath() -> Path {
  return myPath
}

fun getPaths() -> Path[2] {
  var p2: Path = {
    points: [{x: 5, y: 15}, {x: 25, y: 35}],
    id: "path2"
  }
  var paths: Path[2] = [myPath, p2]
  return paths
}

var p: Path = getPath()
println(p.id)
println(p.points[0].x)
println(p.points[1].y)

var ps: Path[2] = getPaths()
println(ps[0].id)
println(ps[1].points[0].x)
```

### return_nested_object_array.expect
```
path1
10
40
path1
5
```

## Test: return_object_array

### return_object_array.fg
```javascript
type T = {
  val: int
}

var arr: T[2] = [{val: 1}, {val: 2}]
fun makePair() -> T[2] {
  return arr
}

var a: T[2] = makePair()
println(a[0].val)
println(a[1].val)
```

### return_object_array.expect
```
1
2
```

## Test: return_object_array_inline_access

### return_object_array_inline_access.fg
```javascript
type Point = {x: int, y: int}

fun getPoints() -> Point[2] {
  var pts: Point[2] = [{x: 10, y: 20}, {x: 30, y: 40}]
  return pts
}

println(getPoints()[1].y)
println(getPoints()[0].x)
```

### return_object_array_inline_access.expect
```
40
10
```

## Test: sub_object_field_from_func

### sub_object_field_from_func.fg
```javascript
type Inner = {
  value: int
}

type Outer = {
  inner: Inner
  label: str
}

fun makeInner(v: int) -> Inner {
  var i: Inner = {value: v}
  return i
}

var o: Outer = {inner: makeInner(99), label: "test"}
print(o, "\n")
```

### sub_object_field_from_func.expect
```
{ inner: { value: 99 }, label: "test" }
```

---

# Directory: FunctionTests/02_return_types

## Test: basic_nthg_return

### basic_nthg_return.fg
```javascript
fun test2(x) -> nthg{
 return: /; colon is required for nthg return type
}
```

### basic_nthg_return.expect
```

```

## Test: return_bool

### return_bool.fg
```javascript
fun getBool() -> bool {
  return true
}

var b: bool = getBool()
println(b)
```

### return_bool.expect
```
true
```

## Test: return_bool_both

### return_bool_both.fg
```javascript
fun yes() -> bool {
  return true
}

fun no() -> bool {
  return false
}

println(yes())
println(no())
```

### return_bool_both.expect
```
true
false
```

## Test: return_char

### return_char.fg
```javascript
fun getChar() -> char {
  return 'X'
}

var c: char = getChar()
println(c)
```

### return_char.expect
```
X
```

## Test: return_char_digit

### return_char_digit.fg
```javascript
fun digit() -> char {
  return '9'
}

println(digit())
println(digit())
```

### return_char_digit.expect
```
9
9
```

## Test: return_deci

### return_deci.fg
```javascript
fun getDeci() -> deci {
  return 3.14
}

var x: deci = getDeci()
println(x)
```

### return_deci.expect
```
3.14
```

## Test: return_deci32

### return_deci32.fg
```javascript
fun getDeci32() -> deci32 {
  return 2.5f
}

var x: deci32 = getDeci32()
println(x)
```

### return_deci32.expect
```
2.5
```

## Test: return_deci32_value

### return_deci32_value.fg
```javascript
fun half() -> deci32 {
  return 0.5f
}

println(half())
println(half())
```

### return_deci32_value.expect
```
0.5
0.5
```

## Test: return_deci_large

### return_deci_large.fg
```javascript
fun big() -> deci {
  return 1.5e10
}

println(big())
```

### return_deci_large.expect
```
15000000000
```

## Test: return_int

### return_int.fg
```javascript
fun getInt() -> int {
  return 42
}

var x: int = getInt()
println(x)
```

### return_int.expect
```
42
```

## Test: return_int8

### return_int8.fg
```javascript
fun getInt8() -> int8 {
  return 100
}

var n: int8 = getInt8()
println(n)
```

### return_int8.expect
```
100
```

## Test: return_int8_small

### return_int8_small.fg
```javascript
fun small() -> int8 {
  return 127
}

var x: int8 = small()
println(x)
```

### return_int8_small.expect
```
127
```

## Test: return_int_negative

### return_int_negative.fg
```javascript
fun neg() -> int {
  return -99
}

var n: int = neg()
println(n)
println(neg())
```

### return_int_negative.expect
```
-99
-99
```

## Test: return_int_zero

### return_int_zero.fg
```javascript
fun zero() -> int {
  return 0
}

println(zero())
println(zero())
```

### return_int_zero.expect
```
0
0
```

## Test: return_str

### return_str.fg
```javascript
fun getStr() -> str {
  return "Hello Flow-Wing"
}

var s: str = getStr()
println(s)
```

### return_str.expect
```
Hello Flow-Wing
```

## Test: return_str_empty

### return_str_empty.fg
```javascript
fun emptyStr() -> str {
  return ""
}

var s: str = emptyStr()
println("len")
println(s)
```

### return_str_empty.expect
```
len
```

---

# Directory: FunctionTests/22_only_function_declaration

## Test: function_declaration

### function_declaration.fg
```javascript
fun strReplace(str1: as str, oldSub: as str, newSub: as int) -> as deci decl
```

### function_declaration.expect
```

```

---

# Directory: FunctionTests/15_dynamic_param

## Test: dynamic_all_types

### dynamic_all_types.fg
```javascript
fun test_all_types(inout i, inout d, inout s, inout b, inout c) {
    println(i)
    println(d)
    println(s)
    println(b)
    println(c)
    i = 42
    d = 3.14
    s = "changed"
    b = false
    c = 'z'
}

var v_i = 10
var v_d = 1.23
var v_s = "original"
var v_b = true
var v_c = 'a'

test_all_types(v_i, v_d, v_s, v_b, v_c)
println(v_i)
println(v_d)
println(v_s)
println(v_b)
println(v_c)
```

### dynamic_all_types.expect
```
10
1.23
"original"
true
'a'
42
3.14
"changed"
false
'z'
```

## Test: dynamic_in_dynamic_out

### dynamic_in_dynamic_out.fg
```javascript
fun getDouble(n: int) -> int {
  return n * 2
}

var x = 5
var y = getDouble(x)
println(y)
```

### dynamic_in_dynamic_out.expect
```
10
```

## Test: dynamic_inout_reassignment

### dynamic_inout_reassignment.fg
```javascript
fun test1(inout a) {
  print("Hello",a)
  a = "something"
  return "Hello World2"
}

var a = 10
println(a)
var x = test1(a)
println(a)
```

### dynamic_inout_reassignment.expect
```
10
Hello10"something"
```

## Test: dynamic_var_to_typed_param

### dynamic_var_to_typed_param.fg
```javascript
fun printAny(val: int) -> int {
  println(val)
  return val
}

var x = 42
printAny(x)
```

### dynamic_var_to_typed_param.expect
```
42
```

---

# Directory: FunctionTests/20_generated_complex

## Test: 2d_array_init_access_2_2_0

### 2d_array_init_access_2_2_0.fg
```javascript
fun get2D() -> int[2][2] {
    var flat: int[2][2]
    return flat
}
var temp: int[2][2] = get2D()
temp[0][0] = 4
println(temp[0][0])
```

### 2d_array_init_access_2_2_0.expect
```
4
```

## Test: 2d_array_init_access_2_2_1

### 2d_array_init_access_2_2_1.fg
```javascript
fun get2D() -> int[2][2] {
    var flat: int[2][2]
    return flat
}
var temp: int[2][2] = get2D()
temp[0][0] = 5
println(temp[0][0])
```

### 2d_array_init_access_2_2_1.expect
```
5
```

## Test: 2d_array_init_access_2_2_2

### 2d_array_init_access_2_2_2.fg
```javascript
fun get2D() -> int[2][2] {
    var flat: int[2][2]
    return flat
}
var temp: int[2][2] = get2D()
temp[0][0] = 6
println(temp[0][0])
```

### 2d_array_init_access_2_2_2.expect
```
6
```

## Test: 2d_array_init_access_2_3_0

### 2d_array_init_access_2_3_0.fg
```javascript
fun get2D() -> int[2][3] {
    var flat: int[2][3]
    return flat
}
var temp: int[2][3] = get2D()
temp[0][0] = 6
println(temp[0][0])
```

### 2d_array_init_access_2_3_0.expect
```
6
```

## Test: 2d_array_init_access_2_3_1

### 2d_array_init_access_2_3_1.fg
```javascript
fun get2D() -> int[2][3] {
    var flat: int[2][3]
    return flat
}
var temp: int[2][3] = get2D()
temp[0][0] = 7
println(temp[0][0])
```

### 2d_array_init_access_2_3_1.expect
```
7
```

## Test: 2d_array_init_access_2_3_2

### 2d_array_init_access_2_3_2.fg
```javascript
fun get2D() -> int[2][3] {
    var flat: int[2][3]
    return flat
}
var temp: int[2][3] = get2D()
temp[0][0] = 8
println(temp[0][0])
```

### 2d_array_init_access_2_3_2.expect
```
8
```

## Test: 2d_array_init_access_3_2_0

### 2d_array_init_access_3_2_0.fg
```javascript
fun get2D() -> int[3][2] {
    var flat: int[3][2]
    return flat
}
var temp: int[3][2] = get2D()
temp[0][0] = 6
println(temp[0][0])
```

### 2d_array_init_access_3_2_0.expect
```
6
```

## Test: 2d_array_init_access_3_2_1

### 2d_array_init_access_3_2_1.fg
```javascript
fun get2D() -> int[3][2] {
    var flat: int[3][2]
    return flat
}
var temp: int[3][2] = get2D()
temp[0][0] = 7
println(temp[0][0])
```

### 2d_array_init_access_3_2_1.expect
```
7
```

## Test: 2d_array_init_access_3_2_2

### 2d_array_init_access_3_2_2.fg
```javascript
fun get2D() -> int[3][2] {
    var flat: int[3][2]
    return flat
}
var temp: int[3][2] = get2D()
temp[0][0] = 8
println(temp[0][0])
```

### 2d_array_init_access_3_2_2.expect
```
8
```

## Test: 2d_array_init_access_3_3_0

### 2d_array_init_access_3_3_0.fg
```javascript
fun get2D() -> int[3][3] {
    var flat: int[3][3]
    return flat
}
var temp: int[3][3] = get2D()
temp[0][0] = 9
println(temp[0][0])
```

### 2d_array_init_access_3_3_0.expect
```
9
```

## Test: 2d_array_init_access_3_3_1

### 2d_array_init_access_3_3_1.fg
```javascript
fun get2D() -> int[3][3] {
    var flat: int[3][3]
    return flat
}
var temp: int[3][3] = get2D()
temp[0][0] = 10
println(temp[0][0])
```

### 2d_array_init_access_3_3_1.expect
```
10
```

## Test: 2d_array_init_access_3_3_2

### 2d_array_init_access_3_3_2.fg
```javascript
fun get2D() -> int[3][3] {
    var flat: int[3][3]
    return flat
}
var temp: int[3][3] = get2D()
temp[0][0] = 11
println(temp[0][0])
```

### 2d_array_init_access_3_3_2.expect
```
11
```

## Test: block_shadow_bool_3

### block_shadow_bool_3.fg
```javascript
fun printVal(val: bool) {
    println(val)
}

var a: bool = true
{
    var a: bool = false
    printVal(a)
}
printVal(a)
```

### block_shadow_bool_3.expect
```
false
true
```

## Test: block_shadow_bool_8

### block_shadow_bool_8.fg
```javascript
fun printVal(val: bool) {
    println(val)
}

var a: bool = false
{
    var a: bool = true
    printVal(a)
}
printVal(a)
```

### block_shadow_bool_8.expect
```
true
false
```

## Test: block_shadow_char_4

### block_shadow_char_4.fg
```javascript
fun printVal(val: char) {
    println(val)
}

var a: char = 'X'
{
    var a: char = 'Y'
    printVal(a)
}
printVal(a)
```

### block_shadow_char_4.expect
```
Y
X
```

## Test: block_shadow_char_9

### block_shadow_char_9.fg
```javascript
fun printVal(val: char) {
    println(val)
}

var a: char = 'A'
{
    var a: char = 'B'
    printVal(a)
}
printVal(a)
```

### block_shadow_char_9.expect
```
B
A
```

## Test: block_shadow_deci_1

### block_shadow_deci_1.fg
```javascript
fun printVal(val: deci) {
    println(val)
}

var a: deci = 1.5
{
    var a: deci = 2.5
    printVal(a)
}
printVal(a)
```

### block_shadow_deci_1.expect
```
2.5
1.5
```

## Test: block_shadow_deci_6

### block_shadow_deci_6.fg
```javascript
fun printVal(val: deci) {
    println(val)
}

var a: deci = 10.5
{
    var a: deci = 20.5
    printVal(a)
}
printVal(a)
```

### block_shadow_deci_6.expect
```
20.5
10.5
```

## Test: block_shadow_int_0

### block_shadow_int_0.fg
```javascript
fun printVal(val: int) {
    println(val)
}

var a: int = 10
{
    var a: int = 20
    printVal(a)
}
printVal(a)
```

### block_shadow_int_0.expect
```
20
10
```

## Test: block_shadow_int_5

### block_shadow_int_5.fg
```javascript
fun printVal(val: int) {
    println(val)
}

var a: int = 100
{
    var a: int = 200
    printVal(a)
}
printVal(a)
```

### block_shadow_int_5.expect
```
200
100
```

## Test: block_shadow_str_2

### block_shadow_str_2.fg
```javascript
fun printVal(val: str) {
    println(val)
}

var a: str = "A"
{
    var a: str = "B"
    printVal(a)
}
printVal(a)
```

### block_shadow_str_2.expect
```
B
A
```

## Test: block_shadow_str_7

### block_shadow_str_7.fg
```javascript
fun printVal(val: str) {
    println(val)
}

var a: str = "AA"
{
    var a: str = "BB"
    printVal(a)
}
printVal(a)
```

### block_shadow_str_7.expect
```
BB
AA
```

## Test: inline_arr_obj_access_bool_0

### inline_arr_obj_access_bool_0.fg
```javascript
type Obj_0_2 = { val: bool }
fun getObjs() -> Obj_0_2[5] {
    var res: Obj_0_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_0.expect
```
false
```

## Test: inline_arr_obj_access_bool_1

### inline_arr_obj_access_bool_1.fg
```javascript
type Obj_1_2 = { val: bool }
fun getObjs() -> Obj_1_2[5] {
    var res: Obj_1_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_1.expect
```
false
```

## Test: inline_arr_obj_access_bool_2

### inline_arr_obj_access_bool_2.fg
```javascript
type Obj_2_2 = { val: bool }
fun getObjs() -> Obj_2_2[5] {
    var res: Obj_2_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_2.expect
```
false
```

## Test: inline_arr_obj_access_bool_3

### inline_arr_obj_access_bool_3.fg
```javascript
type Obj_3_2 = { val: bool }
fun getObjs() -> Obj_3_2[5] {
    var res: Obj_3_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_3.expect
```
false
```

## Test: inline_arr_obj_access_bool_4

### inline_arr_obj_access_bool_4.fg
```javascript
type Obj_4_2 = { val: bool }
fun getObjs() -> Obj_4_2[5] {
    var res: Obj_4_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_4.expect
```
false
```

## Test: inline_arr_obj_access_bool_5

### inline_arr_obj_access_bool_5.fg
```javascript
type Obj_5_2 = { val: bool }
fun getObjs() -> Obj_5_2[5] {
    var res: Obj_5_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_5.expect
```
false
```

## Test: inline_arr_obj_access_bool_6

### inline_arr_obj_access_bool_6.fg
```javascript
type Obj_6_2 = { val: bool }
fun getObjs() -> Obj_6_2[5] {
    var res: Obj_6_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_6.expect
```
false
```

## Test: inline_arr_obj_access_bool_7

### inline_arr_obj_access_bool_7.fg
```javascript
type Obj_7_2 = { val: bool }
fun getObjs() -> Obj_7_2[5] {
    var res: Obj_7_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_7.expect
```
false
```

## Test: inline_arr_obj_access_bool_8

### inline_arr_obj_access_bool_8.fg
```javascript
type Obj_8_2 = { val: bool }
fun getObjs() -> Obj_8_2[5] {
    var res: Obj_8_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_8.expect
```
false
```

## Test: inline_arr_obj_access_bool_9

### inline_arr_obj_access_bool_9.fg
```javascript
type Obj_9_2 = { val: bool }
fun getObjs() -> Obj_9_2[5] {
    var res: Obj_9_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_bool_9.expect
```
false
```

## Test: inline_arr_obj_access_char_0

### inline_arr_obj_access_char_0.fg
```javascript
type Obj_0_4 = { val: char }
fun getObjs() -> Obj_0_4[5] {
    var res: Obj_0_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_0.expect
```
a
```

## Test: inline_arr_obj_access_char_1

### inline_arr_obj_access_char_1.fg
```javascript
type Obj_1_4 = { val: char }
fun getObjs() -> Obj_1_4[5] {
    var res: Obj_1_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_1.expect
```
a
```

## Test: inline_arr_obj_access_char_2

### inline_arr_obj_access_char_2.fg
```javascript
type Obj_2_4 = { val: char }
fun getObjs() -> Obj_2_4[5] {
    var res: Obj_2_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_2.expect
```
a
```

## Test: inline_arr_obj_access_char_3

### inline_arr_obj_access_char_3.fg
```javascript
type Obj_3_4 = { val: char }
fun getObjs() -> Obj_3_4[5] {
    var res: Obj_3_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_3.expect
```
a
```

## Test: inline_arr_obj_access_char_4

### inline_arr_obj_access_char_4.fg
```javascript
type Obj_4_4 = { val: char }
fun getObjs() -> Obj_4_4[5] {
    var res: Obj_4_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_4.expect
```
a
```

## Test: inline_arr_obj_access_char_5

### inline_arr_obj_access_char_5.fg
```javascript
type Obj_5_4 = { val: char }
fun getObjs() -> Obj_5_4[5] {
    var res: Obj_5_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_5.expect
```
a
```

## Test: inline_arr_obj_access_char_6

### inline_arr_obj_access_char_6.fg
```javascript
type Obj_6_4 = { val: char }
fun getObjs() -> Obj_6_4[5] {
    var res: Obj_6_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_6.expect
```
a
```

## Test: inline_arr_obj_access_char_7

### inline_arr_obj_access_char_7.fg
```javascript
type Obj_7_4 = { val: char }
fun getObjs() -> Obj_7_4[5] {
    var res: Obj_7_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_7.expect
```
a
```

## Test: inline_arr_obj_access_char_8

### inline_arr_obj_access_char_8.fg
```javascript
type Obj_8_4 = { val: char }
fun getObjs() -> Obj_8_4[5] {
    var res: Obj_8_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_8.expect
```
a
```

## Test: inline_arr_obj_access_char_9

### inline_arr_obj_access_char_9.fg
```javascript
type Obj_9_4 = { val: char }
fun getObjs() -> Obj_9_4[5] {
    var res: Obj_9_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_char_9.expect
```
a
```

## Test: inline_arr_obj_access_deci_0

### inline_arr_obj_access_deci_0.fg
```javascript
type Obj_0_1 = { val: deci }
fun getObjs() -> Obj_0_1[5] {
    var res: Obj_0_1[5] = [{val: 0.0}, {val: 1.5}, {val: 3.0}, {val: 4.5}, {val: 6.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_0.expect
```
6
```

## Test: inline_arr_obj_access_deci_1

### inline_arr_obj_access_deci_1.fg
```javascript
type Obj_1_1 = { val: deci }
fun getObjs() -> Obj_1_1[5] {
    var res: Obj_1_1[5] = [{val: 1.0}, {val: 2.5}, {val: 4.0}, {val: 5.5}, {val: 7.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_1.expect
```
7
```

## Test: inline_arr_obj_access_deci_2

### inline_arr_obj_access_deci_2.fg
```javascript
type Obj_2_1 = { val: deci }
fun getObjs() -> Obj_2_1[5] {
    var res: Obj_2_1[5] = [{val: 2.0}, {val: 3.5}, {val: 5.0}, {val: 6.5}, {val: 8.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_2.expect
```
8
```

## Test: inline_arr_obj_access_deci_3

### inline_arr_obj_access_deci_3.fg
```javascript
type Obj_3_1 = { val: deci }
fun getObjs() -> Obj_3_1[5] {
    var res: Obj_3_1[5] = [{val: 3.0}, {val: 4.5}, {val: 6.0}, {val: 7.5}, {val: 9.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_3.expect
```
9
```

## Test: inline_arr_obj_access_deci_4

### inline_arr_obj_access_deci_4.fg
```javascript
type Obj_4_1 = { val: deci }
fun getObjs() -> Obj_4_1[5] {
    var res: Obj_4_1[5] = [{val: 4.0}, {val: 5.5}, {val: 7.0}, {val: 8.5}, {val: 10.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_4.expect
```
10
```

## Test: inline_arr_obj_access_deci_5

### inline_arr_obj_access_deci_5.fg
```javascript
type Obj_5_1 = { val: deci }
fun getObjs() -> Obj_5_1[5] {
    var res: Obj_5_1[5] = [{val: 5.0}, {val: 6.5}, {val: 8.0}, {val: 9.5}, {val: 11.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_5.expect
```
11
```

## Test: inline_arr_obj_access_deci_6

### inline_arr_obj_access_deci_6.fg
```javascript
type Obj_6_1 = { val: deci }
fun getObjs() -> Obj_6_1[5] {
    var res: Obj_6_1[5] = [{val: 6.0}, {val: 7.5}, {val: 9.0}, {val: 10.5}, {val: 12.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_6.expect
```
12
```

## Test: inline_arr_obj_access_deci_7

### inline_arr_obj_access_deci_7.fg
```javascript
type Obj_7_1 = { val: deci }
fun getObjs() -> Obj_7_1[5] {
    var res: Obj_7_1[5] = [{val: 7.0}, {val: 8.5}, {val: 10.0}, {val: 11.5}, {val: 13.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_7.expect
```
13
```

## Test: inline_arr_obj_access_deci_8

### inline_arr_obj_access_deci_8.fg
```javascript
type Obj_8_1 = { val: deci }
fun getObjs() -> Obj_8_1[5] {
    var res: Obj_8_1[5] = [{val: 8.0}, {val: 9.5}, {val: 11.0}, {val: 12.5}, {val: 14.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_8.expect
```
14
```

## Test: inline_arr_obj_access_deci_9

### inline_arr_obj_access_deci_9.fg
```javascript
type Obj_9_1 = { val: deci }
fun getObjs() -> Obj_9_1[5] {
    var res: Obj_9_1[5] = [{val: 9.0}, {val: 10.5}, {val: 12.0}, {val: 13.5}, {val: 15.0}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_deci_9.expect
```
15
```

## Test: inline_arr_obj_access_int_0

### inline_arr_obj_access_int_0.fg
```javascript
type Obj_0_0 = { val: int }
fun getObjs() -> Obj_0_0[5] {
    var res: Obj_0_0[5] = [{val: 0}, {val: 10}, {val: 20}, {val: 30}, {val: 40}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_0.expect
```
40
```

## Test: inline_arr_obj_access_int_1

### inline_arr_obj_access_int_1.fg
```javascript
type Obj_1_0 = { val: int }
fun getObjs() -> Obj_1_0[5] {
    var res: Obj_1_0[5] = [{val: 1}, {val: 11}, {val: 21}, {val: 31}, {val: 41}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_1.expect
```
41
```

## Test: inline_arr_obj_access_int_2

### inline_arr_obj_access_int_2.fg
```javascript
type Obj_2_0 = { val: int }
fun getObjs() -> Obj_2_0[5] {
    var res: Obj_2_0[5] = [{val: 2}, {val: 12}, {val: 22}, {val: 32}, {val: 42}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_2.expect
```
42
```

## Test: inline_arr_obj_access_int_3

### inline_arr_obj_access_int_3.fg
```javascript
type Obj_3_0 = { val: int }
fun getObjs() -> Obj_3_0[5] {
    var res: Obj_3_0[5] = [{val: 3}, {val: 13}, {val: 23}, {val: 33}, {val: 43}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_3.expect
```
43
```

## Test: inline_arr_obj_access_int_4

### inline_arr_obj_access_int_4.fg
```javascript
type Obj_4_0 = { val: int }
fun getObjs() -> Obj_4_0[5] {
    var res: Obj_4_0[5] = [{val: 4}, {val: 14}, {val: 24}, {val: 34}, {val: 44}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_4.expect
```
44
```

## Test: inline_arr_obj_access_int_5

### inline_arr_obj_access_int_5.fg
```javascript
type Obj_5_0 = { val: int }
fun getObjs() -> Obj_5_0[5] {
    var res: Obj_5_0[5] = [{val: 5}, {val: 15}, {val: 25}, {val: 35}, {val: 45}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_5.expect
```
45
```

## Test: inline_arr_obj_access_int_6

### inline_arr_obj_access_int_6.fg
```javascript
type Obj_6_0 = { val: int }
fun getObjs() -> Obj_6_0[5] {
    var res: Obj_6_0[5] = [{val: 6}, {val: 16}, {val: 26}, {val: 36}, {val: 46}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_6.expect
```
46
```

## Test: inline_arr_obj_access_int_7

### inline_arr_obj_access_int_7.fg
```javascript
type Obj_7_0 = { val: int }
fun getObjs() -> Obj_7_0[5] {
    var res: Obj_7_0[5] = [{val: 7}, {val: 17}, {val: 27}, {val: 37}, {val: 47}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_7.expect
```
47
```

## Test: inline_arr_obj_access_int_8

### inline_arr_obj_access_int_8.fg
```javascript
type Obj_8_0 = { val: int }
fun getObjs() -> Obj_8_0[5] {
    var res: Obj_8_0[5] = [{val: 8}, {val: 18}, {val: 28}, {val: 38}, {val: 48}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_8.expect
```
48
```

## Test: inline_arr_obj_access_int_9

### inline_arr_obj_access_int_9.fg
```javascript
type Obj_9_0 = { val: int }
fun getObjs() -> Obj_9_0[5] {
    var res: Obj_9_0[5] = [{val: 9}, {val: 19}, {val: 29}, {val: 39}, {val: 49}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_int_9.expect
```
49
```

## Test: inline_arr_obj_access_str_0

### inline_arr_obj_access_str_0.fg
```javascript
type Obj_0_3 = { val: str }
fun getObjs() -> Obj_0_3[5] {
    var res: Obj_0_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_0.expect
```
str_4
```

## Test: inline_arr_obj_access_str_1

### inline_arr_obj_access_str_1.fg
```javascript
type Obj_1_3 = { val: str }
fun getObjs() -> Obj_1_3[5] {
    var res: Obj_1_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_1.expect
```
str_4
```

## Test: inline_arr_obj_access_str_2

### inline_arr_obj_access_str_2.fg
```javascript
type Obj_2_3 = { val: str }
fun getObjs() -> Obj_2_3[5] {
    var res: Obj_2_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_2.expect
```
str_4
```

## Test: inline_arr_obj_access_str_3

### inline_arr_obj_access_str_3.fg
```javascript
type Obj_3_3 = { val: str }
fun getObjs() -> Obj_3_3[5] {
    var res: Obj_3_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_3.expect
```
str_4
```

## Test: inline_arr_obj_access_str_4

### inline_arr_obj_access_str_4.fg
```javascript
type Obj_4_3 = { val: str }
fun getObjs() -> Obj_4_3[5] {
    var res: Obj_4_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_4.expect
```
str_4
```

## Test: inline_arr_obj_access_str_5

### inline_arr_obj_access_str_5.fg
```javascript
type Obj_5_3 = { val: str }
fun getObjs() -> Obj_5_3[5] {
    var res: Obj_5_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_5.expect
```
str_4
```

## Test: inline_arr_obj_access_str_6

### inline_arr_obj_access_str_6.fg
```javascript
type Obj_6_3 = { val: str }
fun getObjs() -> Obj_6_3[5] {
    var res: Obj_6_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_6.expect
```
str_4
```

## Test: inline_arr_obj_access_str_7

### inline_arr_obj_access_str_7.fg
```javascript
type Obj_7_3 = { val: str }
fun getObjs() -> Obj_7_3[5] {
    var res: Obj_7_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_7.expect
```
str_4
```

## Test: inline_arr_obj_access_str_8

### inline_arr_obj_access_str_8.fg
```javascript
type Obj_8_3 = { val: str }
fun getObjs() -> Obj_8_3[5] {
    var res: Obj_8_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_8.expect
```
str_4
```

## Test: inline_arr_obj_access_str_9

### inline_arr_obj_access_str_9.fg
```javascript
type Obj_9_3 = { val: str }
fun getObjs() -> Obj_9_3[5] {
    var res: Obj_9_3[5] = [{val: "str_0"}, {val: "str_1"}, {val: "str_2"}, {val: "str_3"}, {val: "str_4"}]
    return res
}

println(getObjs()[4].val)
```

### inline_arr_obj_access_str_9.expect
```
str_4
```

## Test: inout_array_modification_deci_size2

### inout_array_modification_deci_size2.fg
```javascript
fun mutateArray(inout arr: deci[2], idx: int, v: deci) {
    arr[idx] = v
}

var data: deci[2] = [0.5, 1.5]
mutateArray(data, 1, 10.5)
println(data[1])
```

### inout_array_modification_deci_size2.expect
```
10.5
```

## Test: inout_array_modification_deci_size3

### inout_array_modification_deci_size3.fg
```javascript
fun mutateArray(inout arr: deci[3], idx: int, v: deci) {
    arr[idx] = v
}

var data: deci[3] = [0.5, 1.5, 2.5]
mutateArray(data, 2, 20.5)
println(data[2])
```

### inout_array_modification_deci_size3.expect
```
20.5
```

## Test: inout_array_modification_deci_size4

### inout_array_modification_deci_size4.fg
```javascript
fun mutateArray(inout arr: deci[4], idx: int, v: deci) {
    arr[idx] = v
}

var data: deci[4] = [0.5, 1.5, 2.5, 3.5]
mutateArray(data, 3, 30.5)
println(data[3])
```

### inout_array_modification_deci_size4.expect
```
30.5
```

## Test: inout_array_modification_deci_size5

### inout_array_modification_deci_size5.fg
```javascript
fun mutateArray(inout arr: deci[5], idx: int, v: deci) {
    arr[idx] = v
}

var data: deci[5] = [0.5, 1.5, 2.5, 3.5, 4.5]
mutateArray(data, 4, 40.5)
println(data[4])
```

### inout_array_modification_deci_size5.expect
```
40.5
```

## Test: inout_array_modification_int_size2

### inout_array_modification_int_size2.fg
```javascript
fun mutateArray(inout arr: int[2], idx: int, v: int) {
    arr[idx] = v
}

var data: int[2] = [0, 1]
mutateArray(data, 1, 10)
println(data[1])
```

### inout_array_modification_int_size2.expect
```
10
```

## Test: inout_array_modification_int_size3

### inout_array_modification_int_size3.fg
```javascript
fun mutateArray(inout arr: int[3], idx: int, v: int) {
    arr[idx] = v
}

var data: int[3] = [0, 1, 2]
mutateArray(data, 2, 20)
println(data[2])
```

### inout_array_modification_int_size3.expect
```
20
```

## Test: inout_array_modification_int_size4

### inout_array_modification_int_size4.fg
```javascript
fun mutateArray(inout arr: int[4], idx: int, v: int) {
    arr[idx] = v
}

var data: int[4] = [0, 1, 2, 3]
mutateArray(data, 3, 30)
println(data[3])
```

### inout_array_modification_int_size4.expect
```
30
```

## Test: inout_array_modification_int_size5

### inout_array_modification_int_size5.fg
```javascript
fun mutateArray(inout arr: int[5], idx: int, v: int) {
    arr[idx] = v
}

var data: int[5] = [0, 1, 2, 3, 4]
mutateArray(data, 4, 40)
println(data[4])
```

### inout_array_modification_int_size5.expect
```
40
```

## Test: multi_return_block_shadowing_0

### multi_return_block_shadowing_0.fg
```javascript
fun getMulti_0() -> int, str {
    return 0, "test0"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_0()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_0.expect
```
0
test0
999
outer
```

## Test: multi_return_block_shadowing_1

### multi_return_block_shadowing_1.fg
```javascript
fun getMulti_1() -> int, str {
    return 1, "test1"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_1()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_1.expect
```
1
test1
999
outer
```

## Test: multi_return_block_shadowing_2

### multi_return_block_shadowing_2.fg
```javascript
fun getMulti_2() -> int, str {
    return 2, "test2"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_2()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_2.expect
```
2
test2
999
outer
```

## Test: multi_return_block_shadowing_3

### multi_return_block_shadowing_3.fg
```javascript
fun getMulti_3() -> int, str {
    return 3, "test3"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_3()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_3.expect
```
3
test3
999
outer
```

## Test: multi_return_block_shadowing_4

### multi_return_block_shadowing_4.fg
```javascript
fun getMulti_4() -> int, str {
    return 4, "test4"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_4()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_4.expect
```
4
test4
999
outer
```

## Test: multi_return_block_shadowing_5

### multi_return_block_shadowing_5.fg
```javascript
fun getMulti_5() -> int, str {
    return 5, "test5"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_5()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_5.expect
```
5
test5
999
outer
```

## Test: multi_return_block_shadowing_6

### multi_return_block_shadowing_6.fg
```javascript
fun getMulti_6() -> int, str {
    return 6, "test6"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_6()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_6.expect
```
6
test6
999
outer
```

## Test: multi_return_block_shadowing_7

### multi_return_block_shadowing_7.fg
```javascript
fun getMulti_7() -> int, str {
    return 7, "test7"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_7()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_7.expect
```
7
test7
999
outer
```

## Test: multi_return_block_shadowing_8

### multi_return_block_shadowing_8.fg
```javascript
fun getMulti_8() -> int, str {
    return 8, "test8"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_8()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_8.expect
```
8
test8
999
outer
```

## Test: multi_return_block_shadowing_9

### multi_return_block_shadowing_9.fg
```javascript
fun getMulti_9() -> int, str {
    return 9, "test9"
}

var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_9()
    println(x)
    println(y)
}
println(x)
println(y)
```

### multi_return_block_shadowing_9.expect
```
9
test9
999
outer
```

## Test: struct_with_2d_array_0

### struct_with_2d_array_0.fg
```javascript
type Matrix_0 = { rows: int[1][2], valid: bool }
fun getMatrix(v: int) -> Matrix_0 {
    var m: Matrix_0
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_0 = getMatrix(0)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_0.expect
```
true
0
```

## Test: struct_with_2d_array_1

### struct_with_2d_array_1.fg
```javascript
type Matrix_1 = { rows: int[2][2], valid: bool }
fun getMatrix(v: int) -> Matrix_1 {
    var m: Matrix_1
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_1 = getMatrix(100)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_1.expect
```
true
100
```

## Test: struct_with_2d_array_10

### struct_with_2d_array_10.fg
```javascript
type Matrix_10 = { rows: int[11][2], valid: bool }
fun getMatrix(v: int) -> Matrix_10 {
    var m: Matrix_10
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_10 = getMatrix(1000)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_10.expect
```
true
1000
```

## Test: struct_with_2d_array_11

### struct_with_2d_array_11.fg
```javascript
type Matrix_11 = { rows: int[12][2], valid: bool }
fun getMatrix(v: int) -> Matrix_11 {
    var m: Matrix_11
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_11 = getMatrix(1100)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_11.expect
```
true
1100
```

## Test: struct_with_2d_array_12

### struct_with_2d_array_12.fg
```javascript
type Matrix_12 = { rows: int[13][2], valid: bool }
fun getMatrix(v: int) -> Matrix_12 {
    var m: Matrix_12
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_12 = getMatrix(1200)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_12.expect
```
true
1200
```

## Test: struct_with_2d_array_13

### struct_with_2d_array_13.fg
```javascript
type Matrix_13 = { rows: int[14][2], valid: bool }
fun getMatrix(v: int) -> Matrix_13 {
    var m: Matrix_13
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_13 = getMatrix(1300)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_13.expect
```
true
1300
```

## Test: struct_with_2d_array_14

### struct_with_2d_array_14.fg
```javascript
type Matrix_14 = { rows: int[15][2], valid: bool }
fun getMatrix(v: int) -> Matrix_14 {
    var m: Matrix_14
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_14 = getMatrix(1400)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_14.expect
```
true
1400
```

## Test: struct_with_2d_array_2

### struct_with_2d_array_2.fg
```javascript
type Matrix_2 = { rows: int[3][2], valid: bool }
fun getMatrix(v: int) -> Matrix_2 {
    var m: Matrix_2
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_2 = getMatrix(200)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_2.expect
```
true
200
```

## Test: struct_with_2d_array_3

### struct_with_2d_array_3.fg
```javascript
type Matrix_3 = { rows: int[4][2], valid: bool }
fun getMatrix(v: int) -> Matrix_3 {
    var m: Matrix_3
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_3 = getMatrix(300)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_3.expect
```
true
300
```

## Test: struct_with_2d_array_4

### struct_with_2d_array_4.fg
```javascript
type Matrix_4 = { rows: int[5][2], valid: bool }
fun getMatrix(v: int) -> Matrix_4 {
    var m: Matrix_4
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_4 = getMatrix(400)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_4.expect
```
true
400
```

## Test: struct_with_2d_array_5

### struct_with_2d_array_5.fg
```javascript
type Matrix_5 = { rows: int[6][2], valid: bool }
fun getMatrix(v: int) -> Matrix_5 {
    var m: Matrix_5
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_5 = getMatrix(500)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_5.expect
```
true
500
```

## Test: struct_with_2d_array_6

### struct_with_2d_array_6.fg
```javascript
type Matrix_6 = { rows: int[7][2], valid: bool }
fun getMatrix(v: int) -> Matrix_6 {
    var m: Matrix_6
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_6 = getMatrix(600)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_6.expect
```
true
600
```

## Test: struct_with_2d_array_7

### struct_with_2d_array_7.fg
```javascript
type Matrix_7 = { rows: int[8][2], valid: bool }
fun getMatrix(v: int) -> Matrix_7 {
    var m: Matrix_7
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_7 = getMatrix(700)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_7.expect
```
true
700
```

## Test: struct_with_2d_array_8

### struct_with_2d_array_8.fg
```javascript
type Matrix_8 = { rows: int[9][2], valid: bool }
fun getMatrix(v: int) -> Matrix_8 {
    var m: Matrix_8
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_8 = getMatrix(800)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_8.expect
```
true
800
```

## Test: struct_with_2d_array_9

### struct_with_2d_array_9.fg
```javascript
type Matrix_9 = { rows: int[10][2], valid: bool }
fun getMatrix(v: int) -> Matrix_9 {
    var m: Matrix_9
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_9 = getMatrix(900)
println(mat.valid)
println(mat.rows[0][0])
```

### struct_with_2d_array_9.expect
```
true
900
```

---

# Directory: FunctionTests/17_return_errors

## Test: return_count_mismatch

### return_count_mismatch.fg
```javascript
/; EXPECT_ERROR: InvalidNumberOfReturnExpressions
fun getTwo() -> int {
  return 1, 2
}

var x: int = getTwo()
```

## Test: return_outside_function

### return_outside_function.fg
```javascript
/; EXPECT_ERROR: ReturnStatementNotInFunction
return 42
```

## Test: return_type_mismatch

### return_type_mismatch.fg
```javascript
/; EXPECT_ERROR: ReturnExpressionTypeMismatch
fun getInt() -> int {
  return "hello"
}

var x: int = getInt()
```

---

# Directory: FunctionTests/01_basic_void

## Test: no_args_void

### no_args_void.fg
```javascript
fun greet() -> int {
  print("Hello World")
  print("\n")
  return 0
}

greet()
```

### no_args_void.expect
```
Hello World
```

## Test: no_args_void_nthg_return

### no_args_void_nthg_return.fg
```javascript
fun greet() -> int {
  print("Hello World")
  print("\n")
  return 0
}

greet()
```

### no_args_void_nthg_return.expect
```
Hello World
```

## Test: void_chain_two_calls

### void_chain_two_calls.fg
```javascript
fun step1() -> nthg {
  println(1)
}

fun step2() -> nthg {
  println(2)
}

step1()
step2()
step1()
```

### void_chain_two_calls.expect
```
1
2
1
```

## Test: void_no_return_type

### void_no_return_type.fg
```javascript
fun noRet() {
  println(42)
}

noRet()
noRet()
```

### void_no_return_type.expect
```
42
42
```

## Test: void_side_effect_print

### void_side_effect_print.fg
```javascript
fun say(msg: str) -> nthg {
  println(msg)
}

say("A")
say("B")
println("C")
```

### void_side_effect_print.expect
```
A
B
C
```

---

# Directory: FunctionTests/06_var_decl_from_func

## Test: var_decl_from_func_in_block

### var_decl_from_func_in_block.fg
```javascript
fun getX() -> int {
  return 100
}

var g: int = 0
{
  var local: int = getX()
  println(local)
  println(g)
}
println(g)
```

### var_decl_from_func_in_block.expect
```
100
0
0
```

## Test: var_decl_multi_return

### var_decl_multi_return.fg
```javascript
fun getPoint() -> int, deci {
  return 10, 3.14
}

var x: int, y: deci = getPoint()
println(x)
println(y)
```

### var_decl_multi_return.expect
```
10
3.14
```

## Test: var_decl_single_return

### var_decl_single_return.fg
```javascript
fun getValue() -> int {
  return 99
}

var x: int = getValue()
println(x)
```

### var_decl_single_return.expect
```
99
```

## Test: var_decl_single_typed_int

### var_decl_single_typed_int.fg
```javascript
fun seven() -> int {
  return 7
}

var x: int = seven()
var y: int = seven()
println(x)
println(y)
println(x + y)
```

### var_decl_single_typed_int.expect
```
7
7
14
```

## Test: var_decl_three_from_multi

### var_decl_three_from_multi.fg
```javascript
fun triple() -> int, deci, str {
  return 1, 2.5, "three"
}

var a: int, b: deci, c: str = triple()
println(a)
println(b)
println(c)
```

### var_decl_three_from_multi.expect
```
1
2.5
three
```

## Test: var_decl_two_single_return_funcs

### var_decl_two_single_return_funcs.fg
```javascript
fun getSum(a: int, b: int) -> int {
  return a + b
}

fun getProduct(a: int, b: int) -> int {
  return a * b
}

var s: int, p: int = getSum(3, 4), getProduct(3, 4)
println(s)
println(p)
```

### var_decl_two_single_return_funcs.expect
```
7
12
```

---

# Directory: FunctionTests/04_multi_return

## Test: multi_return_discard

### multi_return_discard.fg
```javascript
fun test2(a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  return 1, 3.4
}

var a: int = 10

test2(a, "hello2")
println(a)
```

### multi_return_discard.expect
```
Hello World10hello2
10
```

## Test: multi_return_discard_second

### multi_return_discard_second.fg
```javascript
fun two() -> int, str {
  return 100, "ignored"
}

var a: int, b: str = two()
println(a)
b = "used"
println(b)
```

### multi_return_discard_second.expect
```
100
used
```

## Test: multi_return_exact_match

### multi_return_exact_match.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  a = 20
  println("Hello World", a, b)
  return 1, 3.5
}

var a: int = 10
println(a)
var x: int, y: deci = test2(a, "hello2")
println(a)
println(x)
println(y)
```

### multi_return_exact_match.expect
```
10
Hello World10hello2
Hello World20hello2
20
1
3.5
```

## Test: multi_return_extra_vars_zero_default

### multi_return_extra_vars_zero_default.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  a = 20
  println("Hello World", a, b)
  return 1, 3.5
}

var a: int = 10
println(a)
var x: int, y: deci, c: deci32 = test2(a, "hello2")
println(a)
println(x)
println(y)
println(c)
```

### multi_return_extra_vars_zero_default.expect
```
10
Hello World10hello2
Hello World20hello2
20
1
3.5
0
```

## Test: multi_return_four_values

### multi_return_four_values.fg
```javascript
fun quad() -> int, int, int, int {
  return 1, 2, 3, 4
}

var a: int, b: int, c: int, d: int = quad()
println(a)
println(b)
println(c)
println(d)
```

### multi_return_four_values.expect
```
1
2
3
4
```

## Test: multi_return_from_params

### multi_return_from_params.fg
```javascript
fun swap(a: int, b: int) -> int, int {
  return b, a
}

var x: int = 1
var y: int = 2
var u: int, v: int = swap(x, y)
println(u)
println(v)
println(x)
println(y)
```

### multi_return_from_params.expect
```
2
1
1
2
```

## Test: multi_return_inout_mutation

### multi_return_inout_mutation.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  a = 20
  println("Hello World", a, b)
  return 1, 3.5
}

var a: int = 10
var b: int = 33
println(a)
println(b)
var x: int, y: deci, c: deci32, x1: int, y1: deci, c1: deci32 = test2(a, "hello2"), 2.2f, test2(b, "hello3")
println(a)
println(x)
println(y)
println(c)
println(x1)
println(y1)
println(c1)
```

### multi_return_inout_mutation.expect
```
10
33
Hello World10hello2
Hello World20hello2
Hello World33hello3
Hello World20hello3
20
1
3.5
2.2
1
3.5
0
```

## Test: multi_return_mixed_bool_int_str

### multi_return_mixed_bool_int_str.fg
```javascript
fun mixed() -> bool, int, str {
  return true, 7, "ok"
}

var b: bool, i: int, s: str = mixed()
println(b)
println(i)
println(s)
```

### multi_return_mixed_bool_int_str.expect
```
true
7
ok
```

## Test: multi_return_same_type_three

### multi_return_same_type_three.fg
```javascript
fun threeInts() -> int, int, int {
  return 10, 20, 30
}

var x: int, y: int, z: int = threeInts()
println(x + y + z)
println(z)
```

### multi_return_same_type_three.expect
```
60
30
```

## Test: multi_return_two_func_calls

### multi_return_two_func_calls.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  return a, 3.5 * a
}

var a: int = 10
var b: int = 30
println(a)
println(b)
var x: int, y: deci, c: deci32, x1: int, y1: deci, c1: deci32 = test2(a, "hello2"), 2.2f, test2(b, "hello3")
println(a)
println(b)
println(x)
println(y)
println(c)
println(x1)
println(y1)
println(c1)
```

### multi_return_two_func_calls.expect
```
10
30
Hello World10hello2
Hello World30hello3
10
30
10
35
2.2
30
105
0
```

## Test: multi_return_two_vars

### multi_return_two_vars.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  return a, 3.5 * a
}

var a: int = 10
var b: int = 30
println(a)
println(b)
var x: int, y: deci = test2(a, "hello2")
println(a)
println(b)
println(x)
println(y)
```

### multi_return_two_vars.expect
```
10
30
Hello World10hello2
10
30
10
35
```

## Test: multi_return_with_literal_prefix

### multi_return_with_literal_prefix.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  println("Hello World", a, b)
  return a, 3.5 * a
}

var a: int = 10
var b: int = 30
println(a)
println(b)
var j: str, x: int, y: deci = "something", test2(a, "hello2")
println(a)
println(j)
println(b)
println(x)
println(y)
```

### multi_return_with_literal_prefix.expect
```
10
30
Hello World10hello2
10
something
30
10
35
```

---

# Directory: FunctionTests/10_errors

## Test: argument_type_mismatch

### argument_type_mismatch.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
fun greet(name: str) -> str {
  return "Hello " + name
}

greet(42)
```

## Test: assign_count_mismatch_one_var_multi_return

### assign_count_mismatch_one_var_multi_return.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
fun pair() -> int, int {
  return 10, 20
}

var a: int = 0
a = pair()
```

## Test: assign_count_mismatch_two_vars_one_func

### assign_count_mismatch_two_vars_one_func.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionCountMismatch
fun one() -> int {
  return 1
}

var a: int = 0
var b: int = 0
a, b = one()
```

## Test: assign_to_const_in_multi

### assign_to_const_in_multi.fg
```javascript
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
fun one() -> int { return 1 }
fun two() -> int { return 2 }

const a: int = 0
var b: int = 0
a, b = one(), two()
```

## Test: assign_type_mismatch_multi

### assign_type_mismatch_multi.fg
```javascript
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
fun pair() -> int, str {
  return 10, "twenty"
}

var a: int = 0
var b: int = 0
a, b = pair()
```

## Test: function_already_declared

### function_already_declared.fg
```javascript
/; EXPECT_ERROR: FunctionAlreadyDeclared
fun greet() {
  println("Hello")
}

fun greet() {
  println("Hi")
}

greet()
```

## Test: function_not_found

### function_not_found.fg
```javascript
/; EXPECT_ERROR: FunctionNotFound
foo()
```

## Test: init_type_mismatch

### init_type_mismatch.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
fun getText() -> str {
  return "hello"
}

var x: int = getText()
```

## Test: inout_array_literal

### inout_array_literal.fg
```javascript
/; EXPECT_ERROR: LiteralCannotBePassedToInoutParameter
fun mutate(inout arr: int[2]) {
  arr[0] = 99
}

mutate([1, 2])
```

## Test: inout_object_literal

### inout_object_literal.fg
```javascript
/; EXPECT_ERROR: LiteralCannotBePassedToInoutParameter
type B = {
  b: int
}
type A = {
  a: int
  b: B
}

fun test(inout d: A[2]) {
  d[0].b.b = 5
}

test([{b: {b: 2}, a: 2}])
```

## Test: inout_primitive_literal

### inout_primitive_literal.fg
```javascript
/; EXPECT_ERROR: LiteralCannotBePassedToInoutParameter
fun test2(inout d: int) {
  println(d)
}

test2(1)
```

## Test: inout_string_literal

### inout_string_literal.fg
```javascript
/; EXPECT_ERROR: LiteralCannotBePassedToInoutParameter
fun append(inout s: str, t: str) {
  s = s + t
}

append("hello", " world")
```

## Test: too_few_arguments

### too_few_arguments.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
fun add(a: int, b: int) -> int {
  return a + b
}

add(1)
```

## Test: too_many_arguments

### too_many_arguments.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
fun add(a: int, b: int) -> int {
  return a + b
}

add(1, 2, 3)
```

## Test: too_many_initializers

### too_many_initializers.fg
```javascript
/; EXPECT_ERROR: TooManyInitializerExpressions
fun getNum() -> int {
  return 1
}

var x: int = getNum(), getNum(), getNum()
```

---

# Directory: FunctionTests/11_return_stmt

## Test: return_call_expression

### return_call_expression.fg
```javascript
fun inner() -> int {
  return 13
}

fun outer() -> int {
  return inner() + 1
}

println(outer())
println(inner())
```

### return_call_expression.expect
```
14
13
```

## Test: return_expression_arithmetic

### return_expression_arithmetic.fg
```javascript
fun compute(a: int, b: int) -> int {
  return a * b + a + b
}

println(compute(2, 3))
println(compute(0, 10))
```

### return_expression_arithmetic.expect
```
11
10
```

## Test: return_expression_string_concat

### return_expression_string_concat.fg
```javascript
fun join(a: str, b: str) -> str {
  return a + "-" + b
}

println(join("x", "y"))
println(join("Hello", "World"))
```

### return_expression_string_concat.expect
```
x-y
Hello-World
```

## Test: return_four_values

### return_four_values.fg
```javascript
fun four() -> int, int, int, int {
  return 1, 2, 3, 4
}

var a: int, b: int, c: int, d: int = four()
println(a)
println(b)
println(c)
println(d)
```

### return_four_values.expect
```
1
2
3
4
```

## Test: return_single

### return_single.fg
```javascript
fun earlyReturn(a: int) -> str {
  return "positive"
}

println(earlyReturn(5))
println(earlyReturn(-1))
```

### return_single.expect
```
positive
positive
```

## Test: return_three_values

### return_three_values.fg
```javascript
fun getStats(n: int) -> int, deci, str {
  return n, n * 1.5, "done"
}

var a: int, b: deci, c: str = getStats(4)
println(a)
println(b)
println(c)
```

### return_three_values.expect
```
4
6
done
```

---

# Directory: FunctionTests/13_array_with_func

## Test: array_arg_count_mismatch_error

### array_arg_count_mismatch_error.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
fun sumArray(arr: int[3], n: int) -> int {
  return arr[0]
}

var a: int[3] = [1, 2, 3]
sumArray(a)
```

## Test: array_element_init_from_func

### array_element_init_from_func.fg
```javascript
fun getVal() -> int {
  return 42
}

var a: int[3] = [getVal(), 2, 3]
println(a)
```

### array_element_init_from_func.expect
```
[ 42, 2, 3 ]
```

## Test: array_index_in_object_in_call

### array_index_in_object_in_call.fg
```javascript
type Wrapper = {
  nums: int[3]
}

fun doubleN(n: int) -> int {
  return n * 2
}

var w: Wrapper = {nums: [5, 10, 15]}
println(doubleN(w.nums[0]))
println(doubleN(w.nums[1]))
```

### array_index_in_object_in_call.expect
```
10
20
```

## Test: array_inout

### array_inout.fg
```javascript
fun fillFirst(inout arr: int[3], val: int) -> int {
  arr[0] = val
  return val
}

var a: int[3] = [0, 0, 0]
println(a)
fillFirst(a, 99)
println(a)
```

### array_inout.expect
```
[ 0, 0, 0 ]
[ 99, 0, 0 ]
```

## Test: array_member_in_call

### array_member_in_call.fg
```javascript
type T = {
  val: int
}

fun doubleN(n: int) -> int {
  return n * 2
}

var a: T[2] = [{val: 3}, {val: 7}]
println(doubleN(a[0].val))
println(doubleN(a[1].val))
```

### array_member_in_call.expect
```
6
14
```

## Test: array_of_objects_param

### array_of_objects_param.fg
```javascript
type T = {
  val: int
}

fun sumVals(arr: T[2]) -> int {
  return arr[0].val + arr[1].val
}

var a: T[2] = [{val: 10}, {val: 20}]
println(sumVals(a))
```

### array_of_objects_param.expect
```
30
```

## Test: array_of_objects_return

### array_of_objects_return.fg
```javascript
type T = {
  val: int
}

fun makePair() -> T[2] {
  var arr: T[2] = [{val: 1}, {val: 2}]
  return arr
}

var a: T[2] = makePair()
println(a[0].val)
println(a[1].val)
```

### array_of_objects_return.expect
```
1
2
```

## Test: array_param

### array_param.fg
```javascript
fun sumArray(arr: int[3]) -> int {
  return arr[0] + arr[1] + arr[2]
}

var a: int[3] = [10, 20, 30]
var s: int = sumArray(a)
println(s)
```

### array_param.expect
```
60
```

## Test: array_param_deci

### array_param_deci.fg
```javascript
fun sumArray(arr: deci[3]) -> deci {
  return arr[0] + arr[1] + arr[2]
}

var a: deci[3] = [1.5, 2.5, 3.0]
println(sumArray(a))
```

### array_param_deci.expect
```
7
```

## Test: array_param_str

### array_param_str.fg
```javascript
fun firstTwo(arr: str[2]) -> str {
  return arr[0] + arr[1]
}

var a: str[2] = ["Hello", "World"]
println(firstTwo(a))
```

### array_param_str.expect
```
HelloWorld
```

## Test: array_return

### array_return.fg
```javascript
fun makeArray() -> int[3] {
  var arr: int[3] = [7, 8, 9]
  return arr
}

var result: int[3] = makeArray()
println(result)
```

### array_return.expect
```
[ 7, 8, 9 ]
```

## Test: array_type_mismatch_error

### array_type_mismatch_error.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentTypeMismatch
fun sumArray(arr: int[3]) -> int {
  return arr[0] + arr[1] + arr[2]
}

var a: deci[3] = [1.1, 2.2, 3.3]
sumArray(a)
```

## Test: sub_array_init_from_func

### sub_array_init_from_func.fg
```javascript
fun getSubArray() -> int[2] {
  var sub: int[2] = [10, 20]
  return sub
}

var a: int[2][2] = [getSubArray(), [3, 4]]
println(a)
```

### sub_array_init_from_func.expect
```
[ [ 10, 20 ], [ 3, 4 ] ]
```

---

# Directory: FunctionTests/09_scope

## Test: scope_block_call_func_that_uses_global

### scope_block_call_func_that_uses_global.fg
```javascript
var globalNum: int = 100

fun useGlobal() -> int {
  return globalNum
}

{
  println(useGlobal())
  var localNum: int = 50
  println(localNum)
  println(useGlobal())
}
println(globalNum)
```

### scope_block_call_func_that_uses_global.expect
```
100
50
100
100
```

## Test: scope_block_multi_decl_shadow

### scope_block_multi_decl_shadow.fg
```javascript
fun pair() -> int, str {
  return 88, "block"
}

var a: int = 1
var b: str = "global"
println(a)
println(b)
{
  var a: int, b: str = pair()
  println(a)
  println(b)
}
println(a)
println(b)
```

### scope_block_multi_decl_shadow.expect
```
1
global
88
block
1
global
```

## Test: scope_block_reassign_global_twice

### scope_block_reassign_global_twice.fg
```javascript
fun getFirst() -> int { return 111 }
fun getSecond() -> int { return 222 }

var w: int = 0
println(w)
{
  w = getFirst()
  println(w)
  w = getSecond()
  println(w)
}
println(w)
```

### scope_block_reassign_global_twice.expect
```
0
111
222
222
```

## Test: scope_block_shadow_bool

### scope_block_shadow_bool.fg
```javascript
fun flip() -> bool {
  return true
}

var b: bool = false
println(b)
{
  var b: bool = flip()
  println(b)
}
println(b)
```

### scope_block_shadow_bool.expect
```
false
true
false
```

## Test: scope_block_shadow_char

### scope_block_shadow_char.fg
```javascript
fun getChar() -> char {
  return 'X'
}

var c: char = 'A'
println(c)
{
  var c: char = getChar()
  println(c)
}
println(c)
```

### scope_block_shadow_char.expect
```
A
X
A
```

## Test: scope_block_shadow_int_then_global

### scope_block_shadow_int_then_global.fg
```javascript
fun getVal() -> int {
  return 100
}

var x: int = 5
println(x)
{
  var x: int = getVal()
  println(x)
}
println(x)
```

### scope_block_shadow_int_then_global.expect
```
5
100
5
```

## Test: scope_block_shadow_str_double_block

### scope_block_shadow_str_double_block.fg
```javascript
fun tag(s: str) -> str {
  return "[" + s + "]"
}

var s: str = "global"
println(s)
{
  var s: str = tag("inner")
  println(s)
}
{
  var s: str = tag("second")
  println(s)
}
println(s)
```

### scope_block_shadow_str_double_block.expect
```
global
[inner]
[second]
global
```

## Test: scope_empty_block_global_unchanged

### scope_empty_block_global_unchanged.fg
```javascript
fun id(n: int) -> int {
  return n
}

var t: int = 33
println(t)
{
}
println(t)
println(id(t))
```

### scope_empty_block_global_unchanged.expect
```
33
33
33
```

## Test: scope_function_modifies_global_via_inout

### scope_function_modifies_global_via_inout.fg
```javascript
fun addOne(inout n: int) {
  n = n + 1
}

var g: int = 10
println(g)
addOne(g)
println(g)
addOne(g)
println(g)
```

### scope_function_modifies_global_via_inout.expect
```
10
11
12
```

## Test: scope_function_reads_global

### scope_function_reads_global.fg
```javascript
var g: int = 42

fun show() -> int {
  return g
}

println(show())
g = 99
println(show())
```

### scope_function_reads_global.expect
```
42
99
```

## Test: scope_global_inout_in_block

### scope_global_inout_in_block.fg
```javascript
fun inc(inout i: int) -> int {
  i = i + 1
  return i
}

var i: int = 0
{
  println(inc(i))
  println(inc(i))
}
println(i)
```

### scope_global_inout_in_block.expect
```
1
2
2
```

## Test: scope_global_used_in_func_param_expr

### scope_global_used_in_func_param_expr.fg
```javascript
fun sum(a: int, b: int) -> int {
  return a + b
}

var base: int = 10
{
  var x: int = sum(base, 5)
  println(x)
}
println(base)
```

### scope_global_used_in_func_param_expr.expect
```
15
10
```

## Test: scope_global_visible_inside_block

### scope_global_visible_inside_block.fg
```javascript
fun double(n: int) -> int {
  return n * 2
}

var g: int = 7
{
  println(g)
  println(double(g))
}
println(g)
```

### scope_global_visible_inside_block.expect
```
7
14
7
```

## Test: scope_local_global

### scope_local_global.fg
```javascript
fun getLiteral() -> int {
  return 100
}

var a: int = 10
println(a)
{
  var a: int = getLiteral()
  println(a)
}
println(a)
```

### scope_local_global.expect
```
10
100
10
```

## Test: scope_nested_blocks_inner_shadows

### scope_nested_blocks_inner_shadows.fg
```javascript
fun one() -> int { return 1 }
fun two() -> int { return 2 }
fun three() -> int { return 3 }

var v: int = 0
println(v)
{
  var v: int = one()
  println(v)
  {
    var v: int = two()
    println(v)
  }
  println(v)
  {
    var v: int = three()
    println(v)
  }
}
println(v)
```

### scope_nested_blocks_inner_shadows.expect
```
0
1
2
1
3
0
```

## Test: scope_nested_three_blocks

### scope_nested_three_blocks.fg
```javascript
fun f1() -> int { return 1 }
fun f2() -> int { return 2 }
fun f3() -> int { return 3 }

var z: int = 0
{
  var z: int = f1()
  {
    var z: int = f2()
    {
      var z: int = f3()
      println(z)
    }
    println(z)
  }
  println(z)
}
println(z)
```

### scope_nested_three_blocks.expect
```
3
2
1
0
```

## Test: scope_reassign_global

### scope_reassign_global.fg
```javascript
fun getValue() -> int {
  return 50
}

var a: int = 10
{
  a = getValue()
  println(a)
}
println(a)
```

### scope_reassign_global.expect
```
50
50
```

## Test: scope_two_blocks_same_name

### scope_two_blocks_same_name.fg
```javascript
fun valA() -> int { return 11 }
fun valB() -> int { return 22 }

var k: int = 0
{
  var k: int = valA()
  println(k)
}
{
  var k: int = valB()
  println(k)
}
println(k)
```

### scope_two_blocks_same_name.expect
```
11
22
0
```

---

# Directory: FunctionTests/21_complex_edge

## Test: assign_multi_from_func_twice

### assign_multi_from_func_twice.fg
```javascript
fun next() -> int, int {
  return 1, 2
}

var a: int = 0
var b: int = 0
a, b = next()
println(a)
println(b)
a, b = next()
println(a)
println(b)
```

### assign_multi_from_func_twice.expect
```
1
2
1
2
```

## Test: block_assign_global_from_func

### block_assign_global_from_func.fg
```javascript
fun supply() -> int { return 42 }

var g: int = 0
println(g)
{
  g = supply()
  println(g)
}
println(g)
```

### block_assign_global_from_func.expect
```
0
42
42
```

## Test: block_read_global_modify_inout

### block_read_global_modify_inout.fg
```javascript
fun add(inout n: int, m: int) {
  n = n + m
}

var g: int = 10
{
  println(g)
  add(g, 5)
  println(g)
}
println(g)
```

### block_read_global_modify_inout.expect
```
10
15
15
```

## Test: block_shadow_then_assign_global

### block_shadow_then_assign_global.fg
```javascript
fun val1() -> int { return 11 }
fun val2() -> int { return 22 }

var m: int = 0
{
  var m: int = val1()
  println(m)
}
m = val2()
println(m)
```

### block_shadow_then_assign_global.expect
```
11
22
```

## Test: block_two_vars_one_shadow

### block_two_vars_one_shadow.fg
```javascript
fun getA() -> int { return 10 }
fun getB() -> int { return 20 }

var a: int = 1
var b: int = 2
{
  var a: int = getA()
  println(a)
  println(b)
}
println(a)
println(b)
```

### block_two_vars_one_shadow.expect
```
10
2
1
2
```

## Test: call_in_expression

### call_in_expression.fg
```javascript
fun double(x: int) -> int {
  return x * 2
}

var a: int = double(3) + double(4)
println(a)
println(double(1) + 1)
```

### call_in_expression.expect
```
14
3
```

## Test: chained_calls_three_levels

### chained_calls_three_levels.fg
```javascript
fun a() -> int { return 1 }
fun b(x: int) -> int { return x + 10 }
fun c(x: int) -> int { return x * 2 }

println(c(b(a())))
println(b(a()))
```

### chained_calls_three_levels.expect
```
22
11
```

## Test: default_param_with_inout

### default_param_with_inout.fg
```javascript
fun f(inout a: int, b: int = 5) -> int {
  a = a + b
  return a
}

var x: int = 0
println(f(x))
println(x)
println(f(x, 10))
println(x)
```

### default_param_with_inout.expect
```
5
5
15
15
```

## Test: dynamic_reassign_int_then_str

### dynamic_reassign_int_then_str.fg
```javascript
fun i() -> int { return 1 }
fun s() -> str { return "s" }

var v = i()
println(v)
v = s()
println(v)
v = i()
println(v)
```

### dynamic_reassign_int_then_str.expect
```
1
"s"
1
```

## Test: four_params_no_default

### four_params_no_default.fg
```javascript
fun sum4(a: int, b: int, c: int, d: int) -> int {
  return a + b + c + d
}

println(sum4(1, 1, 1, 1))
println(sum4(10, 0, 0, 0))
```

### four_params_no_default.expect
```
4
10
```

## Test: global_and_param_same_name_func

### global_and_param_same_name_func.fg
```javascript
var x: int = 100

fun useGlobal() -> int {
  return x
}

fun useParam(x: int) -> int {
  return x + 1
}

println(useGlobal())
println(useParam(5))
println(x)
```

### global_and_param_same_name_func.expect
```
100
6
100
```

## Test: inout_plus_multi_return

### inout_plus_multi_return.fg
```javascript
fun op(inout a: int, b: int) -> int, int {
  a = a + b
  return a, b
}

var x: int = 1
var u: int, v: int = op(x, 2)
println(x)
println(u)
println(v)
```

### inout_plus_multi_return.expect
```
3
3
2
```

## Test: inout_str_append

### inout_str_append.fg
```javascript
fun append(inout s: str, t: str) {
  s = s + t
}

var x: str = "a"
append(x, "b")
println(x)
append(x, "c")
println(x)
```

### inout_str_append.expect
```
ab
abc
```

## Test: inout_two_separate_calls

### inout_two_separate_calls.fg
```javascript
fun inc(inout n: int) {
  n = n + 1
}

var p: int = 0
var q: int = 10
inc(p)
inc(q)
println(p)
println(q)
inc(p)
println(p)
```

### inout_two_separate_calls.expect
```
1
11
2
```

## Test: multi_decl_literal_func_literal

### multi_decl_literal_func_literal.fg
```javascript
fun mid() -> int { return 5 }

var a: int, b: int, c: int = 1, mid(), 9
println(a)
println(b)
println(c)
```

### multi_decl_literal_func_literal.expect
```
1
5
9
```

## Test: multi_return_assign_partial

### multi_return_assign_partial.fg
```javascript
fun two() -> int, str {
  return 7, "seven"
}

var a: int = 0
var b: str = ""
a, b = two()
println(a)
println(b)
```

### multi_return_assign_partial.expect
```
7
seven
```

## Test: multi_return_five

### multi_return_five.fg
```javascript
fun five() -> int, int, int, int, int {
  return 1, 2, 3, 4, 5
}

var a: int, b: int, c: int, d: int, e: int = five()
println(a + b + c + d + e)
println(e)
```

### multi_return_five.expect
```
15
5
```

## Test: multi_return_int_str_bool

### multi_return_int_str_bool.fg
```javascript
fun triple() -> int, str, bool {
  return 1, "a", true
}

var i: int, s: str, b: bool = triple()
println(i)
println(s)
println(b)
```

### multi_return_int_str_bool.expect
```
1
a
true
```

## Test: param_default_bool

### param_default_bool.fg
```javascript
fun flag(on: bool = true) -> bool {
  return on
}

println(flag())
println(flag(false))
```

### param_default_bool.expect
```
true
false
```

## Test: param_default_str_empty

### param_default_str_empty.fg
```javascript
fun wrap(s: str = "") -> str {
  return "[" + s + "]"
}

println(wrap())
println(wrap("x"))
```

### param_default_str_empty.expect
```
[]
[x]
```

## Test: param_int8_boundary

### param_int8_boundary.fg
```javascript
fun maxInt8() -> int8 {
  return 127
}

fun minInt8() -> int8 {
  return -128
}

println(maxInt8())
println(minInt8())
```

### param_int8_boundary.expect
```
127
-128
```

## Test: param_three_defaults

### param_three_defaults.fg
```javascript
fun f(a: int = 1, b: int = 2, c: int = 3) -> int {
  return a + b + c
}

println(f())
println(f(10))
println(f(10, 20))
println(f(10, 20, 30))
```

### param_three_defaults.expect
```
6
15
33
60
```

## Test: print_func_result_directly

### print_func_result_directly.fg
```javascript
fun seven() -> int { return 7 }
fun word() -> str { return "word" }

println(seven())
println(word())
println(seven(), word())
```

### print_func_result_directly.expect
```
7
word
7word
```

## Test: print_multiple_args

### print_multiple_args.fg
```javascript
fun numVal() -> int { return 42 }
fun strVal() -> str { return "x" }

println("a", numVal(), "b", strVal(), "c")
println(numVal(), numVal())
```

### print_multiple_args.expect
```
a42bxc
4242
```

## Test: recursive_style_two_funcs

### recursive_style_two_funcs.fg
```javascript
fun b() -> int { return 2 }
fun a() -> int { return 1 + b() }

println(a())
println(b())
```

### recursive_style_two_funcs.expect
```
3
2
```

## Test: return_bool_expr

### return_bool_expr.fg
```javascript
fun eq(a: int, b: int) -> bool {
  return a == b
}

fun lt(a: int, b: int) -> bool {
  return a < b
}

println(eq(1, 1))
println(eq(1, 2))
println(lt(1, 2))
println(lt(2, 1))
```

### return_bool_expr.expect
```
true
false
true
false
```

## Test: return_char_from_param

### return_char_from_param.fg
```javascript
fun echo(c: char) -> char {
  return c
}

println(echo('Z'))
println(echo('!'))
```

### return_char_from_param.expect
```
Z
!
```

## Test: return_complex_expr

### return_complex_expr.fg
```javascript
fun f(a: int, b: int, c: int) -> int {
  return a * 100 + b * 10 + c
}

println(f(1, 2, 3))
println(f(0, 0, 7))
```

### return_complex_expr.expect
```
123
7
```

## Test: return_deci32_from_literal

### return_deci32_from_literal.fg
```javascript
fun half() -> deci32 {
  return 0.5f
}

println(half())
```

### return_deci32_from_literal.expect
```
0.5
```

## Test: return_deci_from_int_params

### return_deci_from_int_params.fg
```javascript
fun ratio(a: int, b: int) -> deci {
  return a * 1.0 / b
}

println(ratio(1, 2))
println(ratio(3, 2))
```

### return_deci_from_int_params.expect
```
0.5
1.5
```

## Test: return_int8_negative

### return_int8_negative.fg
```javascript
fun neg8() -> int8 {
  return -1
}

println(neg8())
var x: int8 = neg8()
println(x)
```

### return_int8_negative.expect
```
-1
-1
```

## Test: return_int_from_deci_param

### return_int_from_deci_param.fg
```javascript
fun trunc(d: deci) -> int {
  return 0
}

fun round(d: deci) -> int {
  return 1
}

println(trunc(3.7))
println(round(3.2))
```

### return_int_from_deci_param.expect
```
0
1
```

## Test: return_multi_then_use_in_expr

### return_multi_then_use_in_expr.fg
```javascript
fun pair() -> int, int {
  return 3, 7
}

var a: int, b: int = pair()
println(a * b)
println(a + b)
```

### return_multi_then_use_in_expr.expect
```
21
10
```

## Test: return_negated_bool

### return_negated_bool.fg
```javascript
fun notVal(b: bool) -> bool {
  return !b
}

println(notVal(true))
println(notVal(false))
```

### return_negated_bool.expect
```
false
true
```

## Test: return_str_from_concat

### return_str_from_concat.fg
```javascript
fun greet(a: str, b: str) -> str {
  return a + " " + b
}

println(greet("Hello", "World"))
println(greet("A", "B"))
```

### return_str_from_concat.expect
```
Hello World
A B
```

## Test: return_zero_int_deci

### return_zero_int_deci.fg
```javascript
fun zeroInt() -> int {
  return 0
}

fun zeroDeci() -> deci {
  return 0.0
}

println(zeroInt())
println(zeroDeci())
```

### return_zero_int_deci.expect
```
0
0
```

## Test: scope_block_func_returns_global

### scope_block_func_returns_global.fg
```javascript
var g: int = 7

fun readG() -> int {
  return g
}

{
  println(readG())
  var g: int = 99
  println(g)
  println(readG())
}
println(g)
```

### scope_block_func_returns_global.expect
```
7
99
7
7
```

## Test: scope_block_inout_then_read

### scope_block_inout_then_read.fg
```javascript
fun inc(inout n: int) {
  n = n + 1
}

var g: int = 0
{
  inc(g)
  println(g)
  inc(g)
  println(g)
}
println(g)
```

### scope_block_inout_then_read.expect
```
1
2
2
```

## Test: scope_global_after_two_blocks

### scope_global_after_two_blocks.fg
```javascript
fun one() -> int { return 1 }
fun two() -> int { return 2 }

var g: int = 0
{
  var g: int = one()
  println(g)
}
{
  var g: int = two()
  println(g)
}
println(g)
```

### scope_global_after_two_blocks.expect
```
1
2
0
```

## Test: scope_nested_block_reassign_outer

### scope_nested_block_reassign_outer.fg
```javascript
fun getInner() -> int { return 100 }
fun getOuter() -> int { return 200 }

var o: int = 0
{
  var i: int = getInner()
  println(i)
  o = getOuter()
  println(o)
}
println(o)
```

### scope_nested_block_reassign_outer.expect
```
100
200
200
```

## Test: three_blocks_sequential

### three_blocks_sequential.fg
```javascript
fun v1() -> int { return 1 }
fun v2() -> int { return 2 }
fun v3() -> int { return 3 }

var x: int = 0
{
  var x: int = v1()
  println(x)
}
{
  var x: int = v2()
  println(x)
}
{
  var x: int = v3()
  println(x)
}
println(x)
```

### three_blocks_sequential.expect
```
1
2
3
0
```

## Test: var_decl_from_multi_in_block

### var_decl_from_multi_in_block.fg
```javascript
fun pair() -> int, str {
  return 77, "seven"
}

var a: int = 0
var b: str = ""
{
  var c: int, d: str = pair()
  println(c)
  println(d)
}
println(a)
println(b)
```

### var_decl_from_multi_in_block.expect
```
77
seven
0
```

## Test: void_calls_void

### void_calls_void.fg
```javascript
fun inner() -> nthg {
  println(1)
}

fun outer() -> nthg {
  println(0)
  inner()
  println(2)
}

outer()
```

### void_calls_void.expect
```
0
1
2
```

## Test: void_then_returning_call

### void_then_returning_call.fg
```javascript
fun noop() -> nthg {
  println(0)
}

fun get() -> int {
  return 9
}

noop()
println(get())
noop()
```

### void_then_returning_call.expect
```
0
9
0
```

---

# Directory: FunctionTests/12_multi_decl_mixed

## Test: multi_decl_func_literal_func

### multi_decl_func_literal_func.fg
```javascript
fun first() -> int { return 10 }
fun last() -> int { return 30 }

var a: int, b: int, c: int = first(), 20, last()
println(a)
println(b)
println(c)
```

### multi_decl_func_literal_func.expect
```
10
20
30
```

## Test: multi_decl_literal_and_func

### multi_decl_literal_and_func.fg
```javascript
fun getValue() -> int {
  return 7
}

var s: str, n: int = "prefix", getValue()
println(s)
println(n)
```

### multi_decl_literal_and_func.expect
```
prefix
7
```

## Test: multi_decl_multi_return_and_single

### multi_decl_multi_return_and_single.fg
```javascript
fun getPoint() -> int, deci {
  return 3, 1.5
}

fun getTag() -> str {
  return "ok"
}

var a: int, b: deci, c: str = getPoint(), getTag()
println(a)
println(b)
println(c)
```

### multi_decl_multi_return_and_single.expect
```
3
1.5
ok
```

## Test: multi_decl_three_literal_two_func

### multi_decl_three_literal_two_func.fg
```javascript
fun a() -> int { return 1 }
fun b() -> int { return 2 }

var x: int, y: int, z: int = 0, a(), b()
println(x)
println(y)
println(z)
```

### multi_decl_three_literal_two_func.expect
```
0
1
2
```

## Test: multi_decl_two_multi_return

### multi_decl_two_multi_return.fg
```javascript
fun p1() -> int, int { return 1, 2 }
fun p2() -> int, int { return 3, 4 }

var a: int, b: int, c: int, d: int = p1(), p2()
println(a)
println(b)
println(c)
println(d)
```

### multi_decl_two_multi_return.expect
```
1
2
3
4
```

---

# Directory: FunctionTests/08_assignment_from_func

## Test: assign_bool_char_from_func

### assign_bool_char_from_func.fg
```javascript
fun flags() -> bool, char {
  return true, 'X'
}

var ok: bool = false
var ch: char = ' '
println(ok)
println(ch)
ok, ch = flags()
println(ok)
println(ch)
```

### assign_bool_char_from_func.expect
```
false
 
true
X
```

## Test: assign_discard_second

### assign_discard_second.fg
```javascript
fun two() -> int, str {
  return 100, "ignored"
}

var a: int = 0
var b: str = ""
println(a)
println(b)
a, b = two()
println(a)
b = "used"
println(b)
```

### assign_discard_second.expect
```
0

100
used
```

## Test: assign_four_from_two_multi

### assign_four_from_two_multi.fg
```javascript
fun p1() -> int, int { return 1, 2 }
fun p2() -> int, int { return 3, 4 }

var a: int = 0
var b: int = 0
var c: int = 0
var d: int = 0
println(a)
println(b)
println(c)
println(d)
a, b, c, d = p1(), p2()
println(a)
println(b)
println(c)
println(d)
```

### assign_four_from_two_multi.expect
```
0
0
0
0
1
2
3
4
```

## Test: assign_from_func

### assign_from_func.fg
```javascript
fun compute(x: int) -> int {
  return x * x
}

var a: int = 5
println(a)
a = compute(a)
println(a)
a = compute(3)
println(a)
```

### assign_from_func.expect
```
5
25
9
```

## Test: assign_in_block_global_var

### assign_in_block_global_var.fg
```javascript
fun getVal() -> int {
  return 999
}

var g: int = 0
println(g)
{
  g = getVal()
  println(g)
}
println(g)
```

### assign_in_block_global_var.expect
```
0
999
999
```

## Test: assign_mixed_func_literal

### assign_mixed_func_literal.fg
```javascript
fun getValue() -> int {
  return 42
}

var n: int = 0
var s: str = ""
println(n)
println(s)
n, s = getValue(), "suffix"
println(n)
println(s)
```

### assign_mixed_func_literal.expect
```
0

42
suffix
```

## Test: assign_mixed_literal_func

### assign_mixed_literal_func.fg
```javascript
fun getValue() -> int {
  return 7
}

var s: str = ""
var n: int = 0
println(s)
println(n)
s, n = "prefix", getValue()
println(s)
println(n)
```

### assign_mixed_literal_func.expect
```
0
prefix
7
```

## Test: assign_mixed_literal_func_literal

### assign_mixed_literal_func_literal.fg
```javascript
fun mid() -> int { return 5 }

var a: int = 0
var b: int = 0
var c: int = 0
println(a)
println(b)
println(c)
a, b, c = 1, mid(), 9
println(a)
println(b)
println(c)
```

### assign_mixed_literal_func_literal.expect
```
0
0
0
1
5
9
```

## Test: assign_mixed_multi_and_single

### assign_mixed_multi_and_single.fg
```javascript
fun getPoint() -> int, deci {
  return 3, 1.5
}

fun getTag() -> str {
  return "ok"
}

var a: int = 0
var b: deci = 0.0
var c: str = ""
println(a)
println(b)
println(c)
a, b, c = getPoint(), getTag()
println(a)
println(b)
println(c)
```

### assign_mixed_multi_and_single.expect
```
0
0

3
1.5
ok
```

## Test: assign_multi_from_func

### assign_multi_from_func.fg
```javascript
fun getMulti() -> int, deci {
  return 5, 2.5
}

var a: int = 0
var b: deci = 0.0
a, b = getMulti()
println(a)
println(b)
```

### assign_multi_from_func.expect
```
5
2.5
```

## Test: assign_multi_in_block

### assign_multi_in_block.fg
```javascript
fun pair() -> int, str {
  return 77, "seven"
}

var a: int = 0
var b: str = ""
println(a)
println(b)
{
  a, b = pair()
  println(a)
  println(b)
}
println(a)
println(b)
```

### assign_multi_in_block.expect
```
0

77
seven
77
seven
```

## Test: assign_multi_then_single

### assign_multi_then_single.fg
```javascript
fun pair() -> int, int {
  return 10, 20
}

fun one() -> int {
  return 999
}

var a: int = 0
var b: int = 0
println(a)
println(b)
a, b = pair()
println(a)
println(b)
a = one()
println(a)
println(b)
```

### assign_multi_then_single.expect
```
0
0
10
20
999
20
```

## Test: assign_sequential_different_funcs

### assign_sequential_different_funcs.fg
```javascript
fun p1() -> int, int { return 1, 2 }
fun p2() -> int, int { return 3, 4 }

var a: int = 0
var b: int = 0
var c: int = 0
var d: int = 0
a, b = p1()
println(a)
println(b)
c, d = p2()
println(c)
println(d)
```

### assign_sequential_different_funcs.expect
```
1
2
3
4
```

## Test: assign_single_then_multi

### assign_single_then_multi.fg
```javascript
fun one() -> int {
  return 1
}

fun pair() -> int, int {
  return 10, 20
}

var a: int = 0
var b: int = 0
println(a)
println(b)
a = one()
println(a)
a, b = pair()
println(a)
println(b)
```

### assign_single_then_multi.expect
```
0
0
1
10
20
```

## Test: assign_three_from_multi

### assign_three_from_multi.fg
```javascript
fun triple() -> int, deci, str {
  return 1, 2.5, "three"
}

var a: int = 0
var b: deci = 0.0
var c: str = ""
println(a)
println(b)
println(c)
a, b, c = triple()
println(a)
println(b)
println(c)
```

### assign_three_from_multi.expect
```
0
0

1
2.5
three
```

## Test: assign_twice_from_same_func

### assign_twice_from_same_func.fg
```javascript
fun next() -> int {
  return 5
}

var x: int = 0
x = next()
println(x)
x = next()
println(x)
```

### assign_twice_from_same_func.expect
```
5
5
```

## Test: assign_two_from_two_funcs

### assign_two_from_two_funcs.fg
```javascript
fun getSum(a: int, b: int) -> int {
  return a + b
}

fun getProduct(a: int, b: int) -> int {
  return a * b
}

var s: int = 0
var p: int = 0
println(s)
println(p)
s, p = getSum(3, 4), getProduct(3, 4)
println(s)
println(p)
```

### assign_two_from_two_funcs.expect
```
0
0
7
12
```

---

# Directory: FunctionTests/07_dynamic

## Test: dynamic_assign_then_reassign

### dynamic_assign_then_reassign.fg
```javascript
fun first() -> int {
  return 1
}

fun second() -> int {
  return 2
}

var v = first()
println(v)
v = second()
println(v)
```

### dynamic_assign_then_reassign.expect
```
1
2
```

## Test: dynamic_from_bool_func

### dynamic_from_bool_func.fg
```javascript
fun flag() -> bool {
  return true
}

var f = flag()
println(f)
println(!f)
```

### dynamic_from_bool_func.expect
```
true
false
```

## Test: dynamic_printed

### dynamic_printed.fg
```javascript
fun num() -> int {
  return 42
}

var x = num()
println(x)
println(x)
```

### dynamic_printed.expect
```
42
42
```

## Test: dynamic_two_vars_two_funcs

### dynamic_two_vars_two_funcs.fg
```javascript
fun getNum() -> int {
  return 7
}

fun getLabel() -> str {
  return "count"
}

var n = getNum()
var s = getLabel()
println(n)
println(s)
```

### dynamic_two_vars_two_funcs.expect
```
7
"count"
```

## Test: dynamic_var_from_func

### dynamic_var_from_func.fg
```javascript
fun getValue() -> int {
  return 42
}

var x = getValue()
println(x)
```

### dynamic_var_from_func.expect
```
42
```

## Test: dynamic_var_from_inout_func

### dynamic_var_from_inout_func.fg
```javascript
fun test2(inout a: int, b: str = "Hello") -> int {
  println("Hello World", a, b)
  a = 20
  return 1
}

var a: int = 10

var x = test2(a, "hello2")
println(a)
println(x)
```

### dynamic_var_from_inout_func.expect
```
Hello World10hello2
20
1
```

## Test: dynamic_var_inferred_str

### dynamic_var_inferred_str.fg
```javascript
fun getStr() -> str {
  return "dynamic"
}

var s = getStr()
println(s)
```

### dynamic_var_inferred_str.expect
```
"dynamic"
```

---

# Directory: FunctionTests/FunctionTypeTest

## Test: BasicTest

### BasicTest.fg
```javascript
fun printX(x: int) -> nthg {
    print("Printing X",x)
  }


fun main2(f:[(int)-> nthg]) -> nthg {
f(2)
}


  main2(printX)
```

### BasicTest.expect
```
Printing X2
```

## Test: BasicWithPrimitiveType

### BasicWithPrimitiveType.fg
```javascript
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg]) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun main2(f:[(int,deci,str,bool,[(str)->nthg])-> nthg]) -> nthg {
f(2,2.2,"Sss",false,printS)
}


  main2(printX)
```

### BasicWithPrimitiveType.expect
```
Printing X22.2Sssfalse
 from printSHehe
```

## Test: BasicWithPrimitiveType2

### BasicWithPrimitiveType2.fg
```javascript
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg]) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun getDeci(y:int,j:str) -> deci  {
    print("\ny",y,"\nj",j)

    return 3.5
  }

fun main2(f:[(int,deci,str,bool,[(str)->nthg])-> nthg] , c: [(int,str)->deci]) -> int {
f(2,2.2,"Sss",false,printS)c(23,"getDeci")
return 2
}


  main2(printX,getDeci)
```

### BasicWithPrimitiveType2.expect
```
Printing X22.2Sssfalse
 from printSHehe
y23
jgetDeci
```

## Test: BasicWithPrimitiveType3

### BasicWithPrimitiveType3.fg
```javascript
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg],d:deci ) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
    print("D",d)
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun getDeci(y:int,j:str) -> deci  {
    print("\ny",y,"\nj",j)

    return 3.5
  }

fun main2(f:[(int,deci,str,bool,[(str)->nthg],deci)-> nthg] , c: [(int,str)->deci]) -> int {
f(2,2.2,"Sss",false,printS,c(23,"getDeci"))return 2
}


  main2(printX,getDeci)
```

### BasicWithPrimitiveType3.expect
```
y23
jgetDeciPrinting X22.2Sssfalse
 from printSHeheD3.5
```

---

# Directory: FunctionTests/FunctionTypeTest/errors

## Test: function_arg_mismatch

### function_arg_mismatch.fg
```javascript
/; EXPECT_ERROR: FunctionArgumentCountMismatch
fun printX(x: int) -> nthg {
    print("Printing X",x)
  }


fun main2(f:[(int)-> nthg]) -> nthg {
f()
}


  main2(printX)
```

## Test: function_not_found

### function_not_found.fg
```javascript
/; EXPECT_ERROR: FunctionNotFound
fun callback() {
  println("callback")
}


fun handler(x:str,callback: [() -> nthg]) {
  s() 
  println("handler")
}

handler("s",callback)
```

---

# Directory: UnaryOperationLiteralTests/not

## Test: bool

### bool.fg
```javascript
print("Unary Not Bool Tests\n")
print(!true, "\n")
print(!false, "\n")
print(!!true, "\n")
print(!!false, "\n")
print(!!!true, "\n")
print(!!!false, "\n")
```

### bool.expect
```
Unary Not Bool Tests
false
true
true
false
false
true
```

## Test: char

### char.fg
```javascript
print("Unary Not Char Tests (checks if zero char)\n")
print(!'a', "\n")
print(!'A', "\n")
print(!'0', "\n")
print(!'1', "\n")
print(!' ', "\n")
print(!'z', "\n")
```

### char.expect
```
Unary Not Char Tests (checks if zero char)
false
false
false
false
false
false
```

## Test: deci32

### deci32.fg
```javascript
print("Unary Not Deci32 (Float) Tests (checks if zero)\n")
print(!0.0f, "\n")
print(!1.0f, "\n")
print(!-1.0f, "\n")
print(!3.14f, "\n")
print(!-3.14f, "\n")
print(!0.001f, "\n")
```

### deci32.expect
```
Unary Not Deci32 (Float) Tests (checks if zero)
true
false
false
false
false
false
```

## Test: deci64

### deci64.fg
```javascript
print("Unary Not Deci (Double) Tests (checks if zero)\n")
print(!0.0, "\n")
print(!1.0, "\n")
print(!-1.0, "\n")
print(!3.14159265359, "\n")
print(!-3.14159265359, "\n")
print(!0.000001, "\n")
```

### deci64.expect
```
Unary Not Deci (Double) Tests (checks if zero)
true
false
false
false
false
false
```

## Test: int32

### int32.fg
```javascript
print("Unary Not Int32 Tests (checks if zero)\n")
print(!128, "\n")
print(!-129, "\n")
print(!1000, "\n")
print(!-1000, "\n")
print(!1000000, "\n")
print(!2147483647, "\n")
print(!-2147483648, "\n")
```

### int32.expect
```
Unary Not Int32 Tests (checks if zero)
false
false
false
false
false
false
false
```

## Test: int64

### int64.fg
```javascript
print("Unary Not Int64 Tests (checks if zero)\n")
print(!3000000000, "\n")
print(!-3000000000, "\n")
print(!9223372036854775807, "\n")
print(!-9223372036854775808, "\n")
print(!5000000000, "\n")
```

### int64.expect
```
Unary Not Int64 Tests (checks if zero)
false
false
false
false
false
```

## Test: int64_suffix

### int64_suffix.fg
```javascript
print(!0l, "\n")
print(!1l, "\n")
print(!10000000000l, "\n")
/; EXPECT: true
/; EXPECT: false
/; EXPECT: false
```

### int64_suffix.expect
```
true
false
false
```

## Test: int8

### int8.fg
```javascript
print("Unary Not Int8 Tests (checks if zero)\n")
print(!0, "\n")
print(!1, "\n")
print(!-1, "\n")
print(!127, "\n")
print(!-128, "\n")
print(!10, "\n")
print(!50, "\n")
```

### int8.expect
```
Unary Not Int8 Tests (checks if zero)
true
false
false
false
false
false
false
```

## Test: nir

### nir.fg
```javascript
print("Unary Not Nir Tests (always true)\n")
print(!null, "\n")
print(!!null, "\n")
```

### nir.expect
```
Unary Not Nir Tests (always true)
true
false
```

## Test: string

### string.fg
```javascript
print("Unary Not String Tests (checks if empty)\n")
print(!"", "\n")
print(!"Hello", "\n")
print(!" ", "\n")
print(!"a", "\n")
print(!"Hello World", "\n")
print(!"\n", "\n")
```

### string.expect
```
Unary Not String Tests (checks if empty)
true
false
false
false
false
false
```

---

# Directory: UnaryOperationLiteralTests/minus

## Test: deci32

### deci32.fg
```javascript
print("Unary Minus Deci32 (Float) Tests\n")
print(-0.0f, "\n")
print(-1.0f, "\n")
print(-3.14f, "\n")
print(--1.0f, "\n")
print(--3.14f, "\n")
print(-100.5f, "\n")
print(--100.5f, "\n")
```

### deci32.expect
```
Unary Minus Deci32 (Float) Tests
-0
-1
-3.1400001
1
3.1400001
-100.5
100.5
```

## Test: deci64

### deci64.fg
```javascript
print("Unary Minus Deci (Double) Tests\n")
print(-0.0, "\n")
print(-1.0, "\n")
print(-3.14159265359, "\n")
print(--1.0, "\n")
print(--3.14159265359, "\n")
print(-1000000.123456, "\n")
print(--1000000.123456, "\n")
```

### deci64.expect
```
Unary Minus Deci (Double) Tests
-0
-1
-3.14159265359
1
3.14159265359
-1000000.12345600000117
1000000.12345600000117
```

## Test: int32

### int32.fg
```javascript
print("Unary Minus Int32 Tests\n")
print(-128, "\n")
print(-1000, "\n")
print(-1000000, "\n")
print(-2147483647, "\n")
print(--129, "\n")
print(--1000, "\n")
print(--1000000, "\n")
```

### int32.expect
```
Unary Minus Int32 Tests
-128
-1000
-1000000
-2147483647
129
1000
1000000
```

## Test: int64

### int64.fg
```javascript
print("Unary Minus Int64 Tests\n")
print(-3000000000, "\n")
print(-9223372036854775807, "\n")
print(--3000000000, "\n")
print(-5000000000, "\n")
print(--5000000000, "\n")
```

### int64.expect
```
Unary Minus Int64 Tests
-3000000000
-9223372036854775807
3000000000
-5000000000
5000000000
```

## Test: int64_suffix

### int64_suffix.fg
```javascript
print(-10000000000l, "\n")
/; EXPECT: -10000000000
```

### int64_suffix.expect
```
-10000000000
```

## Test: int64_suffix_negative

### int64_suffix_negative.fg
```javascript
print(-(-10000000000l), "\n")
/; EXPECT: 10000000000
```

### int64_suffix_negative.expect
```
10000000000
```

## Test: int8

### int8.fg
```javascript
print("Unary Minus Int8 Tests\n")
print(-0, "\n")
print(-1, "\n")
print(-10, "\n")
print(-127, "\n")
print(--1, "\n")
print(--127, "\n")
print(-50, "\n")
print(--50, "\n")
```

### int8.expect
```
Unary Minus Int8 Tests
0
-1
-10
-127
1
127
-50
50
```

---

# Directory: UnaryOperationLiteralTests/errors

## Test: minus_bool

### minus_bool.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(-true)
```

## Test: minus_char

### minus_char.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(-'a')
```

## Test: minus_nir

### minus_nir.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(-null)
```

## Test: minus_string

### minus_string.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(-"Hello")
```

## Test: plus_bool

### plus_bool.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+true)
```

## Test: plus_char

### plus_char.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+'a')
```

## Test: plus_nir

### plus_nir.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+null)
```

## Test: plus_string

### plus_string.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(+"Hello")
```

## Test: tilde_bool

### tilde_bool.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(~true)
```

## Test: tilde_char

### tilde_char.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(~'a')
```

## Test: tilde_deci32

### tilde_deci32.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(~3.14f)
```

## Test: tilde_deci64

### tilde_deci64.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(~3.14)
```

## Test: tilde_nir

### tilde_nir.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(~null)
```

## Test: tilde_string

### tilde_string.fg
```javascript
/; EXPECT_ERROR: InvalidUnaryOperator
print(~"Hello")
```

---

# Directory: UnaryOperationLiteralTests/plus

## Test: deci32

### deci32.fg
```javascript
print("Unary Plus Deci32 (Float) Tests\n")
print(+0.0f, "\n")
print(+1.0f, "\n")
print(+3.14f, "\n")
print(+-1.0f, "\n")
print(+-3.14f, "\n")
print(+100.5f, "\n")
print(+-100.5f, "\n")
```

### deci32.expect
```
Unary Plus Deci32 (Float) Tests
0
1
3.1400001
-1
-3.1400001
100.5
-100.5
```

## Test: deci64

### deci64.fg
```javascript
print("Unary Plus Deci (Double) Tests\n")
print(+0.0, "\n")
print(+1.0, "\n")
print(+3.14159265359, "\n")
print(+-1.0, "\n")
print(+-3.14159265359, "\n")
print(+1000000.123456, "\n")
print(+-1000000.123456, "\n")
```

### deci64.expect
```
Unary Plus Deci (Double) Tests
0
1
3.14159265359
-1
-3.14159265359
1000000.12345600000117
-1000000.12345600000117
```

## Test: int32

### int32.fg
```javascript
print("Unary Plus Int32 Tests\n")
print(+128, "\n")
print(+1000, "\n")
print(+1000000, "\n")
print(+2147483647, "\n")
print(+-129, "\n")
print(+-1000, "\n")
print(+-2147483648, "\n")
```

### int32.expect
```
Unary Plus Int32 Tests
128
1000
1000000
2147483647
-129
-1000
-2147483648
```

## Test: int64

### int64.fg
```javascript
print("Unary Plus Int64 Tests\n")
print(+3000000000, "\n")
print(+9223372036854775807, "\n")
print(+-3000000000, "\n")
print(+-9223372036854775808, "\n")
print(+5000000000, "\n")
```

### int64.expect
```
Unary Plus Int64 Tests
3000000000
9223372036854775807
-3000000000
-9223372036854775808
5000000000
```

## Test: int64_suffix

### int64_suffix.fg
```javascript
print(+10000000000l, "\n")
/; EXPECT: 10000000000
```

### int64_suffix.expect
```
10000000000
```

## Test: int64_suffix_hex

### int64_suffix_hex.fg
```javascript
print(+0xFFFFFFFFl, "\n")
/; EXPECT: 4294967295
```

### int64_suffix_hex.expect
```
4294967295
```

## Test: int8

### int8.fg
```javascript
print("Unary Plus Int8 Tests\n")
print(+0, "\n")
print(+1, "\n")
print(+10, "\n")
print(+127, "\n")
print(+-1, "\n")
print(+-128, "\n")
print(+50, "\n")
print(+-50, "\n")
```

### int8.expect
```
Unary Plus Int8 Tests
0
1
10
127
-1
-128
50
-50
```

---

# Directory: UnaryOperationLiteralTests/tilde

## Test: int32

### int32.fg
```javascript
print("Unary Bitwise Not Int32 Tests\n")
print(~128, "\n")
print(~255, "\n")
print(~1000, "\n")
print(~0, "\n")
print(~-1, "\n")
print(~65535, "\n")
print(~2147483647, "\n")
print(~~128, "\n")
print(~~1000, "\n")
```

### int32.expect
```
Unary Bitwise Not Int32 Tests
-129
-256
-1001
-1
0
-65536
-2147483648
128
1000
```

## Test: int64

### int64.fg
```javascript
print("Unary Bitwise Not Int64 Tests\n")
print(~3000000000, "\n")
print(~4294967295, "\n")
print(~9223372036854775807, "\n")
print(~0, "\n")
print(~-1, "\n")
print(~~3000000000, "\n")
print(~~9223372036854775807, "\n")
```

### int64.expect
```
Unary Bitwise Not Int64 Tests
-3000000001
-4294967296
-9223372036854775808
-1
0
3000000000
9223372036854775807
```

## Test: int64_suffix

### int64_suffix.fg
```javascript
print(~0l, "\n")
print(~1l, "\n")
/; EXPECT: -1
/; EXPECT: -2
```

### int64_suffix.expect
```
-1
-2
```

## Test: int64_suffix_large

### int64_suffix_large.fg
```javascript
print(~4294967295l, "\n")
/; EXPECT: -4294967296
```

### int64_suffix_large.expect
```
-4294967296
```

## Test: int8

### int8.fg
```javascript
print(~0, "\n")
print(~1, "\n")
print(~127, "\n")
/; EXPECT: -1
/; EXPECT: -2
/; EXPECT: -128
```

### int8.expect
```
-1
-2
-128
```

---

# Directory: MapModuleTests/02_features

## Test: bring_map_path_chainable

### bring_map_path_chainable.fg
```javascript
bring map

var customMap: map::Map = new map::Map()

println("--- Test 1: Basic Sequential Chaining ---")
/; Chaining set and insert together
customMap.set("first", 1).set("second", 2).insert("third", 3)

println(customMap.size())
println(customMap.get("second"))
println(customMap.get("third"))

println("--- Test 2: Chaining with Clear ---")
/; Because clear() returns self, we can wipe the customMap and immediately rebuild it in one line
customMap.clear().set("reborn", true).insert("phoenix", "fire")

println(customMap.size())
println(customMap.get("reborn"))
println(customMap.get("phoenix"))

println("--- Test 3: Multi-line Chaining ---")
/; Testing how the parser handles chained calls formatted across multiple lines
customMap.clear()
   .set("a", "Alpha")
   .set("b", "Beta")
   .set("c", "Gamma")
   .set("d", "Delta")
   .set("e", "Epsilon")

println(customMap.size())
println(customMap.get("c"))
println(customMap.get("e"))
```

### bring_map_path_chainable.expect
```
--- Test 1: Basic Sequential Chaining ---
3
2
3
--- Test 2: Chaining with Clear ---
2
true
"fire"
--- Test 3: Multi-line Chaining ---
5
"Gamma"
"Epsilon"
```

---

# Directory: MapModuleTests/01_ok

## Test: bring_map_name_typed_basic

### bring_map_name_typed_basic.fg
```javascript
bring map

var customMap: map::Map = new map::Map()

println("--- Test 1: Basic Insert & Mixed Types ---")
customMap.set("title", "FlowWing")
customMap.set("version", 1.0)
customMap.set("isFast", true)
customMap.set("magicNumber", 42)
customMap.set("charVal", 'X')

println(customMap.get("title"))
println(customMap.get("version"))
println(customMap.get("isFast"))
println(customMap.get("magicNumber"))
println(customMap.get("charVal"))

println("--- Test 2: Reassignment (Overwriting keys) ---")
customMap.set("version", 2.5) 
customMap.set("magicNumber", "Forty Two") 
println(customMap.get("version"))
println(customMap.get("magicNumber"))

println("--- Test 3: Fallbacks (getOr) ---")
println(customMap.getOr("missingString", "default"))
println(customMap.getOr("missingBool", false))
println(customMap.getOr("missingInt", -99))

println("--- Test 4: Size & Existence (has/contains) ---")
println(customMap.size())
println(customMap.has("title"))
println(customMap.contains("fakeKey"))

println("--- Test 5: Removal ---")
var wasRemoved = customMap.remove("isFast")
var wasFakeRemoved = customMap.remove("fakeKey")

println(wasRemoved)
println(wasFakeRemoved)
println(customMap.has("isFast"))
println(customMap.size())

println("--- Test 6: Clear & isEmpty ---")
println(customMap.isEmpty())
customMap.clear()
println(customMap.isEmpty())
println(customMap.size())

println("--- Test 7: Method Chaining ---")
customMap.set("a", 1).set("b", 2).set("c", 3)
println(customMap.size())
```

### bring_map_name_typed_basic.expect
```
--- Test 1: Basic Insert & Mixed Types ---
"FlowWing"
1
true
42
'X'
--- Test 2: Reassignment (Overwriting keys) ---
2.5
"Forty Two"
--- Test 3: Fallbacks (getOr) ---
"default"
false
-99
--- Test 4: Size & Existence (has/contains) ---
5
true
false
--- Test 5: Removal ---
true
false
false
4
--- Test 6: Clear & isEmpty ---
false
true
0
--- Test 7: Method Chaining ---
3
```

---

# Directory: PrimitiveTests

## Test: bool_array

### bool_array.fg
```javascript
var a:bool[4] = [true, false, true, false]
println(a)
a[0] = false
println(a)
```

### bool_array.expect
```
[ true, false, true, false ]
[ false, false, true, false ]
```

## Test: bool_basic

### bool_basic.fg
```javascript
var t:bool = true
var f:bool = false
println(t)
println(f)
println(t && f)
println(t || f)
println(!t)
```

### bool_basic.expect
```
true
false
false
true
false
```

## Test: bool_scope

### bool_scope.fg
```javascript
var b:bool = true
{
    var b:bool = false
    println(b)
}
println(b)
```

### bool_scope.expect
```
false
true
```

## Test: char_array

### char_array.fg
```javascript
var a:char[3] = ['x', 'y', 'z']
println(a)
a[0] = 'a'
println(a)
```

### char_array.expect
```
[ 'x', 'y', 'z' ]
[ 'a', 'y', 'z' ]
```

## Test: char_basic

### char_basic.fg
```javascript
var c:char = 'A'
println(c)
var newline:char = '\n'
println(newline)
```

### char_basic.expect
```
A
```

## Test: deci32_array

### deci32_array.fg
```javascript
var a:deci32[3] = [1.1f, 2.2f, 3.3f]
println(a)
```

### deci32_array.expect
```
[ 1.1, 2.2, 3.3 ]
```

## Test: deci32_basic

### deci32_basic.fg
```javascript
var x:deci32 = 3.14f
var y:deci32 = 2.71f
println(x)
println(y)
println(x + y)
```

### deci32_basic.expect
```
3.1400001
2.71
5.8500004
```

## Test: deci_array

### deci_array.fg
```javascript
var a:deci[3] = [1.1, 2.2, 3.3]
println(a)
```

### deci_array.expect
```
[ 1.1, 2.2, 3.3 ]
```

## Test: deci_basic

### deci_basic.fg
```javascript
var x:deci = 3.14159265358979
println(x)
var y:deci = -2.71828
println(y)
println(x + y)
```

### deci_basic.expect
```
3.14159265358979
-2.71828
0.42331265358979
```

## Test: int32_array

### int32_array.fg
```javascript
var a:int[3] = [100, 200, 300]
println(a)
a[1] = -999
println(a)
```

### int32_array.expect
```
[ 100, 200, 300 ]
[ 100, -999, 300 ]
```

## Test: int32_basic

### int32_basic.fg
```javascript
var x:int = 2147483647
println(x)
var y:int = -100
println(x + y)
```

### int32_basic.expect
```
2147483647
2147483547
```

## Test: int64_array

### int64_array.fg
```javascript
var a:int64[2] = [1000000000000, 2000000000000]
println(a)
```

### int64_array.expect
```
[ 1000000000000, 2000000000000 ]
```

## Test: int64_basic

### int64_basic.fg
```javascript
var x:int64 = 9223372036854775807
println(x)
```

### int64_basic.expect
```
9223372036854775807
```

## Test: int8_array

### int8_array.fg
```javascript
var a:int8[4] = [1, 2, -1, 127]
println(a)
```

### int8_array.expect
```
[ 1, 2, -1, 127 ]
```

## Test: int8_basic

### int8_basic.fg
```javascript
var x:int8 = 127
var y:int8 = -5
println(x)
println(y)
println(x + y)
```

### int8_basic.expect
```
127
-5
122
```

## Test: int8_scope

### int8_scope.fg
```javascript
var x:int8 = 10
{
    var x:int8 = 20
    println(x)
}
println(x)
```

### int8_scope.expect
```
20
10
```

## Test: str_array

### str_array.fg
```javascript
var a:str[3] = ["apple", "banana", "cherry"]
println(a)
a[1] = "mango"
println(a)
```

### str_array.expect
```
[ "apple", "banana", "cherry" ]
[ "apple", "mango", "cherry" ]
```

## Test: str_basic

### str_basic.fg
```javascript
var s:str = "Hello, FlowWing!"
println(s)
var empty:str = ""
println(empty)
```

### str_basic.expect
```
Hello, FlowWing!
```

## Test: str_scope

### str_scope.fg
```javascript
var s:str = "global"
{
    var s:str = "local"
    println(s)
}
println(s)
```

### str_scope.expect
```
local
global
```

---

# Directory: DynamicTests

## Test: dyn_array_mixed

### dyn_array_mixed.fg
```javascript
var a:[4] = [1, "two", 3.0, true]
println(a)
a[0] = "changed"
println(a)
```

### dyn_array_mixed.expect
```
[ 1, "two", 3, true ]
[ "changed", "two", 3, true ]
```

## Test: dyn_basic_types

### dyn_basic_types.fg
```javascript
var a = 42
var b = 3.14
var c = "hello"
var d = true
var e = 'x'
println(a)
println(b)
println(c)
println(d)
println(e)
```

### dyn_basic_types.expect
```
42
3.14
"hello"
true
'x'
```

## Test: dyn_in_scope

### dyn_in_scope.fg
```javascript
var x = "outer"
println(x)
{
    var x = 100
    println(x)
    x = 200
    println(x)
}
println(x)
```

### dyn_in_scope.expect
```
"outer"
100
200
"outer"
```

## Test: dyn_null

### dyn_null.fg
```javascript
var x:[3] = [1, 2, 3]
println(x[0])
println(x[1])
println(x[2])
```

### dyn_null.expect
```
1
2
3
```

## Test: dyn_reassign

### dyn_reassign.fg
```javascript
var x = 10
println(x)
x = "now a string"
println(x)
x = false
println(x)
```

### dyn_reassign.expect
```
10
"now a string"
false
```

## Test: dyn_scope_modify_outer

### dyn_scope_modify_outer.fg
```javascript
var x = 10
{
    x = 99
    println(x)
}
println(x)
```

### dyn_scope_modify_outer.expect
```
99
99
```

---

# Directory: StrModuleTests/02_features/01_ok

## Test: str_module_mutation_and_helpers

### str_module_mutation_and_helpers.fg
```javascript
bring text

var s: text::Text = new text::Text("  Flow Wing  ")
println(s.getLength())
println(s.trim().get())
println(s.getLength())
println(s.toUpper().get())
println(s.toLower().get())
println(s.reverse().get())

var t: text::Text = new text::Text("ab")
println(t.concat("cd").get())
println(t.length())
println(t.charAt(2))

var u: text::Text = new text::Text("MiXeD")
println(u.equalsIgnoreCase("mixed"))
println(u.clear().getLength())
println(u.isEmpty())
```

### str_module_mutation_and_helpers.expect
```
13
Flow Wing
9
FLOW WING
flow wing
gniw wolf
abcd
4
c
true
0
true
```

## Test: str_module_path_helpers

### str_module_path_helpers.fg
```javascript
bring "text-module.fg"

var padded: text::Text = new text::Text("  hi  ")
println(padded.trim().get())
println(padded.getLength())
println(padded.concat("!").get())
println(padded.length())
println(padded.charAt(2))

var empty: text::Text = new text::Text("")
println(empty.isEmpty())
println(empty.getLength())

println(text::concat(text::trim("  a  "), "b"))
println(text::length("abc"))
println(text::equalsIgnoreCase("FlowWing", "flowwing"))
```

### str_module_path_helpers.expect
```
hi
2
hi!
3
!
true
0
ab
3
true
```

---

# Directory: StrModuleTests/01_ok

## Test: bring_str_module_name_at

### bring_str_module_name_at.fg
```javascript
bring text

var s: text::Text = new text::Text("abc")
println(s.getLength())
println(s.at(1))
println(s.toUpper().get())
println(s.reverse().get())
```

### bring_str_module_name_at.expect
```
3
b
ABC
CBA
```

## Test: bring_str_module_path_chain

### bring_str_module_path_chain.fg
```javascript
bring "text-module.fg"

var s: text::Text = new text::Text("  hill ")
println(text::trim("  hill "))
println(s.trim().get())
println(s.at(3))
```

### bring_str_module_path_chain.expect
```
hill
hill
l
```

---

# Directory: ScopeTests

## Test: array_shadowed_by_local

### array_shadowed_by_local.fg
```javascript
var a:int[2] = [1, 2]
{
    var a:int[2] = [100, 200]
    println(a)
}
println(a)
```

### array_shadowed_by_local.expect
```
[ 100, 200 ]
[ 1, 2 ]
```

## Test: const_and_var_scope

### const_and_var_scope.fg
```javascript
const x:int = 42
var y:int = 10
println(x, y)
{
    var y:int = 99
    println(x, y)
}
println(x, y)
```

### const_and_var_scope.expect
```
4210
4299
4210
```

## Test: global_dyn_array_modified_in_nested_scope

### global_dyn_array_modified_in_nested_scope.fg
```javascript
var d:[3] = [1, "hello", true]
println(d)
{
    d[2] = false
    {
        d[0] = 99
    }
}
println(d)
```

### global_dyn_array_modified_in_nested_scope.expect
```
[ 1, "hello", true ]
[ 99, "hello", false ]
```

## Test: int_array_global_scope

### int_array_global_scope.fg
```javascript
var a:int[3] = [10, 20, 30]
println(a)
{
    println(a)
    a[1] = 99
}
println(a)
```

### int_array_global_scope.expect
```
[ 10, 20, 30 ]
[ 10, 20, 30 ]
[ 10, 99, 30 ]
```

## Test: int_array_local_scope

### int_array_local_scope.fg
```javascript
var x:int = 1
{
    var a:int[2] = [x, 2]
    println(a)
}
```

### int_array_local_scope.expect
```
[ 1, 2 ]
```

## Test: nested_scope_array_reads

### nested_scope_array_reads.fg
```javascript
var x:int = 5
var a:int[3] = [1, x, 3]
{
    var b:int[2] = [a[0], a[1]]
    println(b)
    {
        var c:int[1] = [b[1]]
        println(c)
    }
    println(b)
}
println(a)
```

### nested_scope_array_reads.expect
```
[ 1, 5 ]
[ 5 ]
[ 1, 5 ]
[ 1, 5, 3 ]
```

---

# Directory: ScopeTests/object_scope

## Test: object_from_global_array_modified_in_scope

### object_from_global_array_modified_in_scope.fg
```javascript
type T = { val:int }
var arr:T[2] = [{val:1}, {val:2}]
println(arr)
{
    arr[0].val = 100
    println(arr)
}
println(arr)
```

### object_from_global_array_modified_in_scope.expect
```
[ { val: 1 }, { val: 2 } ]
[ { val: 100 }, { val: 2 } ]
[ { val: 100 }, { val: 2 } ]
```

---

# Directory: JsonModuleTests

## Test: json_features

### json_features.fg
```javascript
bring json

println("--- Test 1: Building a JSON Object Programmatically ---")
var myJson: json::JsonNode = json::newObject()
myJson.put("name", json::newString("FlowWing"))
      .put("version", json::newNumber(1.5))
      .put("isCompiled", json::newBool(true))
      .put("nullValue", json::newNull())

var featuresArr: json::JsonNode = json::newArray()
featuresArr.push(json::newString("Fast"))
           .push(json::newString("Dynamic"))
           .push(json::newString("Safe"))

myJson.put("features", featuresArr)

var serializedStr = json::stringify(myJson)
println("Programmatic JSON -> String:")
println(serializedStr)


println("\n--- Test 2: Parsing JSON Strings ---")
var rawJson: str = "{ \"user\": \"Kushagra\", \"id\": 42, \"active\": true, \"scores\": [95.5, 82.0, 100.0] }"

var parsedAst: json::JsonNode = json::parse(rawJson)

var userNode: json::JsonNode = parsedAst.get("user")
var idNode: json::JsonNode = parsedAst.get("id")

println("Parsed User: " + userNode.strVal)
println("Parsed ID: " + String(idNode.numVal))

var scoresArr: json::JsonNode = parsedAst.get("scores")
var firstScore: json::JsonNode = scoresArr.getAt(0)
println("Parsed First Score: " + String(firstScore.numVal))


println("\n--- Test 3: Formatting and Re-Stringifying ---")
var reStr = json::stringify(parsedAst)
println("Re-Stringified output:")
println(reStr)

println("\n--- Test 4: Handling Malformed JSON ---")
var badJson = "{ \"missing_quote: true }"
var badAst: json::JsonNode = json::parse(badJson)
println("Parsed Bad JSON: " + json::stringify(badAst))

println("Multiline string: Test" )
var templateString = `
 {
    "name": "John",
    "age": 30,
    "city": "New York"
 }
`


println(templateString)

var parsedJson: json::JsonNode = json::parse(templateString)


println(json::stringify(parsedJson))


println("\n--- Test 5: Deeply Nested Structures ---")
var deepJsonStr = "{ \"level1\": { \"level2\": { \"level3\": [ 1, [2, 3], {\"deepKey\": \"deepValue\"} ] } } }"
var deepAst: json::JsonNode = json::parse(deepJsonStr)
println("Parsed Deep JSON: " + json::stringify(deepAst))

var l1: json::JsonNode = deepAst.get("level1")
var l2: json::JsonNode = l1.get("level2")
var l3: json::JsonNode = l2.get("level3")
var innerObj: json::JsonNode = l3.getAt(2)
println("Extracted deep value: " + innerObj.get("deepKey").strVal)

println("\n--- Test 6: Array Manipulations and Bounds ---")
var testArr: json::JsonNode = json::newArray()
testArr.push(json::newNumber(10.0))
       .push(json::newNumber(20.0))
       .push(json::newNumber(30.0))

println("Array contents: " + json::stringify(testArr))
println("Index 1: " + String(testArr.getAt(1).numVal))
println("Index 5 (OutOfBounds): " + json::stringify(testArr.getAt(5)))

println("\n--- Test 7: Object Key Updates (Overwriting) ---")
var updateObj: json::JsonNode = json::newObject()
updateObj.put("keyA", json::newString("initial"))
         .put("keyB", json::newNumber(100.0))
println("Before Update: " + json::stringify(updateObj))

/; Update existing key to test the while-loop replacement logic
updateObj.put("keyA", json::newString("updated_value!"))
println("After Update: " + json::stringify(updateObj))

println("\n--- Test 8: Escaped Characters in Strings ---")
/; The string has escaped newlines, tabs, and quotes.
var escStr = "{ \"text\": \"Line1\\nLine2\\tTabbed \\\"Quotes\\\"\" }"
var escAst: json::JsonNode = json::parse(escStr)
println("Parsed Escaped String: " + json::stringify(escAst))

println("\n--- Test 9: Empty Structures ---")
var emptyAst: json::JsonNode = json::parse(" { \"emptyObj\": {  }, \"emptyArr\": [  ] } ")
println("Parsed Empty Structures: " + json::stringify(emptyAst))
```

### json_features.expect
```
--- Test 1: Building a JSON Object Programmatically ---
Programmatic JSON -> String:
"{"name": "FlowWing", "version": 1.5, "isCompiled": true, "nullValue": null, "features": ["Fast", "Dynamic", "Safe"]}"

--- Test 2: Parsing JSON Strings ---
Parsed User: Kushagra
Parsed ID: 42
Parsed First Score: 95.5

--- Test 3: Formatting and Re-Stringifying ---
Re-Stringified output:
"{"user": "Kushagra", "id": 42, "active": true, "scores": [95.5, 82, 100]}"

--- Test 4: Handling Malformed JSON ---
Parsed Bad JSON: {}
Multiline string: Test
"
 {
    "name": "John",
    "age": 30,
    "city": "New York"
 }
"
{"name": "John", "age": 30, "city": "New York"}

--- Test 5: Deeply Nested Structures ---
Parsed Deep JSON: {"level1": {"level2": {"level3": [1, [2, 3], {"deepKey": "deepValue"}]}}}
Extracted deep value: deepValue

--- Test 6: Array Manipulations and Bounds ---
Array contents: [10, 20, 30]
Index 1: 20
Index 5 (OutOfBounds): null

--- Test 7: Object Key Updates (Overwriting) ---
Before Update: {"keyA": "initial", "keyB": 100}
After Update: {"keyA": "updated_value!", "keyB": 100}

--- Test 8: Escaped Characters in Strings ---
Parsed Escaped String: {"text": "Line1
Line2	Tabbed "Quotes""}

--- Test 9: Empty Structures ---
Parsed Empty Structures: {"emptyObj": {}, "emptyArr": []}
```

---

# Directory: 01_char

## Test: print

### print.fg
```javascript
print("--- 1. Basic ASCII Characters ---\n")
print('a', "\n")
print('z', "\n")
print('A', "\n")
print('0', "\n")
print('9', "\n")
print('!', "\n")
print('~', "\n")

print("\n--- 2. Escape Sequences ---\n")
print("Newline:", '\n')
print("Tab:", '\t', "End\n")
print("Single Quote:", '\'', "\n")
print("Backslash:", '\\', "\n")

print("\n--- 3. UTF-8 Extended Characters (2-byte) ---\n")
print('ñ', "\n")
print('µ', "\n")
print('ß', "\n")

print("\n--- 4. UTF-8 Emojis & Symbols (3/4-byte) ---\n")
/; If your source file reading supports UTF-8, these should work
print('🚀', "\n") 
print('€', "\n")
print('👍', "\n")

print("\n--- 5. Char Logic & Identity ---\n")
/; Verify that 'a' is distinct from string "a" visually, 
/; but here we just check if it prints cleanly without quotes.
print('x', " = ", 'x', "\n")

print("\n--- 6. Char Logic & Identity ---\n")
var c: char = 'a'
print(c, "\n")

{
    print("\n--- 7. Char Logic & Identity ---\n")
var c: char = 'b'
print(c, "\n")
}
```

### print.expect
```
--- 1. Basic ASCII Characters ---
a
z
A
0
9
!
~

--- 2. Escape Sequences ---
Newline:
Tab:	End
Single Quote:'
Backslash:\

--- 3. UTF-8 Extended Characters (2-byte) ---
ñ
µ
ß

--- 4. UTF-8 Emojis & Symbols (3/4-byte) ---
🚀
€
👍

--- 5. Char Logic & Identity ---
x = x

--- 6. Char Logic & Identity ---
a

--- 7. Char Logic & Identity ---
b
```

---

# Directory: ArrayTests/mixed

## Test: literal_and_var

### literal_and_var.fg
```javascript
var p:int[2] = [3, 5]

var q:int[3][2] = [[1, 2], p, p]

print(q)
```

### literal_and_var.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: literal_and_vars

### literal_and_vars.fg
```javascript
var p:int[2] = [3, 5]
var q:int[3][2] = [[1, 2], p, [5, 6]]
print(q)
```

### literal_and_vars.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 5, 6 ] ]
```

## Test: mixed_1d_assign

### mixed_1d_assign.fg
```javascript
var x:[2] = ['a','b']
println(x)
var j:int[2] = [1, 2]
println(j)
x = j
println(x)
println(j)
x[1] = "Hello World"
j[1] = 11
println(x)
println(j)
```

### mixed_1d_assign.expect
```
[ 'a', 'b' ]
[ 1, 2 ]
[ 1, 2 ]
[ 1, 2 ]
[ 1, "Hello World" ]
[ 1, 11 ]
```

## Test: mixed_1d_elements

### mixed_1d_elements.fg
```javascript
var x:[2] = [2, "Hello"]
println("x = ", x)
println("x[0] = ", x[0])
println("x[1] = ", x[1])
x[1] = 2.4
println("x = ", x)
x = [true, 2]
println("x = ", x)
```

### mixed_1d_elements.expect
```
x = [ 2, "Hello" ]
x[0] = 2
x[1] = "Hello"
x = [ 2, 2.4 ]
x = [ true, 2 ]
```

## Test: mixed_2d_println_no_labels

### mixed_2d_println_no_labels.fg
```javascript
var x:[2][3] = [[1, 2, 3], ["Hello", "World", "Test"]]
println(x)
var j:int[2][3] = [[1, 2, 3], x[0]]
println(j)
x = j
println(x)
println(j)
x[1] = ["Test", "World", "Test"]
j[1] = [1, 2, 3]
println(x)
println(j)
x[1][1] = 3.5
j[1][1] = 3
println(x)
println(j)
```

### mixed_2d_println_no_labels.expect
```
[ [ 1, 2, 3 ], [ "Hello", "World", "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ "Test", "World", "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
[ [ 1, 2, 3 ], [ "Test", 3.5, "Test" ] ]
[ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
```

## Test: mixed_2d_slice_and_element

### mixed_2d_slice_and_element.fg
```javascript
var x:[2][3] = [[1, 2, 3], ["Hello", "World", "Test"]]
println("x = ", x)
var j:int[2][3] = [[1, 2, 3], x[0]]
println("j = ", j)
x = j
println("x = ", x)
println("j = ", j)
x[1] = ["Test", "World", "Test"]
j[1] = [1, 2, 3]
println("x = ", x)
println("j = ", j)
x[1][1] = 3.5
j[1][1] = 3
println("x = ", x)
println("j = ", j)
x[1] = j[1]
println("x = ", x)
println("j = ", j)
x[1][1] = 22
println("x = ", x)
println("j = ", j)
```

### mixed_2d_slice_and_element.expect
```
x = [ [ 1, 2, 3 ], [ "Hello", "World", "Test" ] ]
j = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
x = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
j = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
x = [ [ 1, 2, 3 ], [ "Test", "World", "Test" ] ]
j = [ [ 1, 2, 3 ], [ 1, 2, 3 ] ]
x = [ [ 1, 2, 3 ], [ "Test", 3.5, "Test" ] ]
j = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
x = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
j = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
x = [ [ 1, 2, 3 ], [ 1, 22, 3 ] ]
j = [ [ 1, 2, 3 ], [ 1, 3, 3 ] ]
```

## Test: mixed_2d_with_var

### mixed_2d_with_var.fg
```javascript
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1,j]
var q:int[3][2] = [l, p,[7,j]]
print(q)
```

### mixed_2d_with_var.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 7, 2 ] ]
```

## Test: partial_2d_4cols

### partial_2d_4cols.fg
```javascript
var p:int[2][4] = [[1,2,3,4], [5,6,7,8]]
var q:int[3][2][4] = [[[1],[2]], p, [[5], [6]]]
print(q)
```

### partial_2d_4cols.expect
```
[ [ [ 1, 0, 0, 0 ], [ 2, 0, 0, 0 ] ], [ [ 1, 2, 3, 4 ], [ 5, 6, 7, 8 ] ], [ [ 5, 0, 0, 0 ], [ 6, 0, 0, 0 ] ] ]
```

## Test: partial_3d

### partial_3d.fg
```javascript
var p:int[2][4] = [[1, 2, 3, 4], [5, 6, 7, 8]]

var q:int[3][2][4] = [[[1], [2]], p, [[5], [6]]]

print(q)
```

### partial_3d.expect
```
[ [ [ 1, 0, 0, 0 ], [ 2, 0, 0, 0 ] ], [ [ 1, 2, 3, 4 ], [ 5, 6, 7, 8 ] ], [ [ 5, 0, 0, 0 ], [ 6, 0, 0, 0 ] ] ]
```

## Test: refs_and_literal

### refs_and_literal.fg
```javascript
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1, j]

var q:int[3][2] = [l, p, [7, j]]

print(q)
```

### refs_and_literal.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 7, 2 ] ]
```

## Test: same_row_twice

### same_row_twice.fg
```javascript
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1,j]
var q:int[3][2] = [l, p,p]
print(q)
```

### same_row_twice.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: same_row_twice_literal

### same_row_twice_literal.fg
```javascript
var p:int[2] = [3, 5]
var l:int[2] = [1,2]
var q:int[3][2] = [l, p,p]
print(q)
```

### same_row_twice_literal.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: same_var_repeated

### same_var_repeated.fg
```javascript
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1, j]

var q:int[3][2] = [l, p, p]

print(q)
```

### same_var_repeated.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 3, 5 ] ]
```

## Test: three_rows

### three_rows.fg
```javascript
var p:int[2] = [3, 5]

var q:int[3][2] = [[1, 2], p, [5, 6]]

print(q)
```

### three_rows.expect
```
[ [ 1, 2 ], [ 3, 5 ], [ 5, 6 ] ]
```

---

# Directory: ArrayTests/basic

## Test: copy_1d

### copy_1d.fg
```javascript
var a:int[2] = [1, 2]
println(a)
var b:int[2] = a
println(b)
```

### copy_1d.expect
```
[ 1, 2 ]
[ 1, 2 ]
```

## Test: int_1d_partial

### int_1d_partial.fg
```javascript
var a:int[5] = [1, 2]
print(a)
```

### int_1d_partial.expect
```
[ 1, 2, 0, 0, 0 ]
```

## Test: int_2d_partial

### int_2d_partial.fg
```javascript
var a:int[5][2] = [[1, 2], [3, 4]]
print(a)
```

### int_2d_partial.expect
```
[ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ]
```

## Test: int_partial_from_vars

### int_partial_from_vars.fg
```javascript
var x:int = 5
var y = 7
var a:int[5] = [x, y]
print(a)
```

### int_partial_from_vars.expect
```
[ 5, 7, 0, 0, 0 ]
```

## Test: int_partial_literal

### int_partial_literal.fg
```javascript
var x:int = 5
var a:int[5] = [x, 7]
print(a)
```

### int_partial_literal.expect
```
[ 5, 7, 0, 0, 0 ]
```

## Test: one_dim_from_var_and_literal

### one_dim_from_var_and_literal.fg
```javascript
var x:int = 5

var a:int[5] = [x, 7]
println(a)
```

### one_dim_from_var_and_literal.expect
```
[ 5, 7, 0, 0, 0 ]
```

## Test: one_dim_from_vars

### one_dim_from_vars.fg
```javascript
var x:int = 5
var y = 7

var a:int[5] = [x, y]
println(a)
```

### one_dim_from_vars.expect
```
[ 5, 7, 0, 0, 0 ]
```

## Test: one_dim_partial

### one_dim_partial.fg
```javascript
var a:int[5] = [1, 2]

println(a)
```

### one_dim_partial.expect
```
[ 1, 2, 0, 0, 0 ]
```

## Test: scalar_assignment_to_index

### scalar_assignment_to_index.fg
```javascript
var x:int[2] = [1, 2]
var j = 5
x[1] = j
println("x = ", x)
println("j = ", j)
j = 10
println("x = ", x)
println("j = ", j)
```

### scalar_assignment_to_index.expect
```
x = [ 1, 5 ]
j = 5
x = [ 1, 5 ]
j = 10
```

## Test: scalar_typed_assignment_to_index

### scalar_typed_assignment_to_index.fg
```javascript
var x:int[2] = [1, 2]
var j:int = 5
x[1] = j
println("x = ", x)
println("j = ", j)
j = 10
println("x = ", x)
println("j = ", j)
```

### scalar_typed_assignment_to_index.expect
```
x = [ 1, 5 ]
j = 5
x = [ 1, 5 ]
j = 10
```

## Test: two_dim_partial

### two_dim_partial.fg
```javascript
var a:int[5][2] = [[1, 2], [3, 4]]

println(a)
```

### two_dim_partial.expect
```
[ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ]
```

## Test: uninit_bool

### uninit_bool.fg
```javascript
var x:bool[2]
println(x)
```

### uninit_bool.expect
```
[ false, false ]
```

## Test: uninit_char

### uninit_char.fg
```javascript
var x:char[2]
println(x)
```

### uninit_char.expect
```
[ '', '' ]
```

## Test: uninit_str

### uninit_str.fg
```javascript
var x:str[2]
println(x)
```

### uninit_str.expect
```
[ "", "" ]
```

---

# Directory: ArrayTests/type_conversion

## Test: deci32_from_mixed

### deci32_from_mixed.fg
```javascript
var x = 5
var y = 2.2f
var z = 3.2f

var a:deci32[5] = [x, y, z]
print(a)
```

### deci32_from_mixed.expect
```
[ 5, 2.2, 3.2, 0, 0 ]
```

## Test: deci32_from_mixed_vars

### deci32_from_mixed_vars.fg
```javascript
var x = 5
var y = 2.2f
var z = 3.2f
var a:deci32[5] = [x, y, z]
print(a)
```

### deci32_from_mixed_vars.expect
```
[ 5, 2.2, 3.2, 0, 0 ]
```

## Test: str_from_mixed

### str_from_mixed.fg
```javascript
var x = 5
var y = "Hello"
var z = 3.2f
var w:bool = true

var a:str[5] = [x, y, z, w]
print(a)
```

### str_from_mixed.expect
```
[ "5", "Hello", "3.2", "true", "" ]
```

## Test: str_from_mixed_types

### str_from_mixed_types.fg
```javascript
var x = 5
var y = "Hello"
var z = 3.2f
var w:bool = true
var a:str[5] = [x, y, z, w]
print(a)
```

### str_from_mixed_types.expect
```
[ "5", "Hello", "3.2", "true", "" ]
```

## Test: str_partial

### str_partial.fg
```javascript
var x = 5
var y = "Hello"

var a:str[5] = [x, y]
print(a)
```

### str_partial.expect
```
[ "5", "Hello", "", "", "" ]
```

## Test: str_partial_from_vars

### str_partial_from_vars.fg
```javascript
var x = 5
var y = "Hello"
var a:str[5] = [x, y]
print(a)
```

### str_partial_from_vars.expect
```
[ "5", "Hello", "", "", "" ]
```

---

# Directory: ArrayTests/runtime_errors

## Test: 2d_index_out_of_bounds

### 2d_index_out_of_bounds.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
var a:int[2][2] = [[1, 2], [3, 4]]
println(a[0][3])
```

## Test: 3d_index_out_of_bounds

### 3d_index_out_of_bounds.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
println(a[1][1][3])
```

## Test: int_from_dynamic_str

### int_from_dynamic_str.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int = 5
var y = "Hello"

var a:int[5] = [x, y]
print(a)
```

## Test: int_from_dynamic_str_runtime

### int_from_dynamic_str_runtime.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int = 5
var y = "Hello"
var a:int[5] = [x, y]
print(a)
```

## Test: int_from_typed_str

### int_from_typed_str.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int = 5
var y:str = "Hello"

var a:int[5] = [x, y]
print(a)
```

## Test: int_from_typed_str_runtime

### int_from_typed_str_runtime.fg
```javascript
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int = 5
var y:str = "Hello"
var a:int[5] = [x, y]
print(a)
```

---

# Directory: ArrayTests/multidimensional

## Test: 2d_all_indices

### 2d_all_indices.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
println(a[0][0])
println(a[0][1])
println(a[1][0])
println(a[1][1])
```

### 2d_all_indices.expect
```
1
2
3
4
```

## Test: 2d_element_access

### 2d_element_access.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var k:int = a[1][1]
println(k)
```

### 2d_element_access.expect
```
4
```

## Test: 2d_slice_basic

### 2d_slice_basic.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
```

### 2d_slice_basic.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
```

## Test: 2d_slice_element_modify

### 2d_slice_element_modify.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
p[0] = 11
println(a)
println(p)
```

### 2d_slice_element_modify.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
[ [ 1, 2 ], [ 11, 4 ] ]
[ 11, 4 ]
```

## Test: 2d_slice_from_literal_assign

### 2d_slice_from_literal_assign.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = [9, 10]
println(a)
println(p)
p = a[1]
println(a)
println(p)
```

### 2d_slice_from_literal_assign.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 9, 10 ]
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
```

## Test: 2d_slice_reassign

### 2d_slice_reassign.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
p = [10, 11]
println(a)
println(p)
```

### 2d_slice_reassign.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
[ [ 1, 2 ], [ 3, 4 ] ]
[ 10, 11 ]
```

## Test: 2d_slice_reassign_literal

### 2d_slice_reassign_literal.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
println(a)
println(p)
p = [10, 11]
println(a)
println(p)
```

### 2d_slice_reassign_literal.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 3, 4 ]
[ [ 1, 2 ], [ 3, 4 ] ]
[ 10, 11 ]
```

## Test: 2d_slice_with_expr

### 2d_slice_with_expr.fg
```javascript
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = [1, a[1][1]]
println(a)
println(p)
```

### 2d_slice_with_expr.expect
```
[ [ 1, 2 ], [ 3, 4 ] ]
[ 1, 4 ]
```

## Test: 3d_print_slices

### 3d_print_slices.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
println(a)
println(a[1])
println(a[1][1])
println(a[1][1][1])
```

### 3d_print_slices.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ 10, 11, 12 ]
11
```

## Test: 3d_slice_element_modify

### 3d_slice_element_modify.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p[0][2] = 11
println(a)
println(p)
```

### 3d_slice_element_modify.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 11 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 11 ], [ 10, 11, 12 ] ]
```

## Test: 3d_slice_element_modify_first

### 3d_slice_element_modify_first.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p[0][0] = 11
println(a)
println(p)
```

### 3d_slice_element_modify_first.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 11, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 11, 8, 9 ], [ 10, 11, 12 ] ]
```

## Test: 3d_slice_literal_reassign

### 3d_slice_literal_reassign.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p = [[1,2,3], [4,5,6]]
println(a)
println(p)
```

### 3d_slice_literal_reassign.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
```

## Test: 3d_slice_reassign_and_element

### 3d_slice_reassign_and_element.fg
```javascript
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
var p:int[2][3] = a[1]
println(a)
println(p)
p = [[1,2,3], a[0][1]]
println(a)
println(p)
p[1][1] = 100
println(a)
println(p)
var j:int[3] = [9,8,6]
p = [[1,2,3], j]
println(a)
println(j)
println(p)
p[1][1] = 100
println(a)
println(j)
println(p)
```

### 3d_slice_reassign_and_element.expect
```
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 7, 8, 9 ], [ 10, 11, 12 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ [ 1, 2, 3 ], [ 4, 100, 6 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ 9, 8, 6 ]
[ [ 1, 2, 3 ], [ 9, 8, 6 ] ]
[ [ [ 1, 2, 3 ], [ 4, 5, 6 ] ], [ [ 7, 8, 9 ], [ 10, 11, 12 ] ] ]
[ 9, 8, 6 ]
[ [ 1, 2, 3 ], [ 9, 100, 6 ] ]
```

## Test: copy_assignment

### copy_assignment.fg
```javascript
var a:int[2] = [1, 2]
println(a)
var b:int[2] = a
println(b)
```

### copy_assignment.expect
```
[ 1, 2 ]
[ 1, 2 ]
```

## Test: int_3d_partial

### int_3d_partial.fg
```javascript
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[5], [7, 8]], [[9, 10], [11, 12]]]

print(a)
```

### int_3d_partial.expect
```
[ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 5, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

## Test: int_3d_partial_only

### int_3d_partial_only.fg
```javascript
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[5], [7, 8]], [[9, 10], [11, 12]]]
print(a)
```

### int_3d_partial_only.expect
```
[ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 5, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

## Test: nested_3d_from_1d_2d

### nested_3d_from_1d_2d.fg
```javascript
var a:int[5] = [1, 2, 3, 4, 5]
var b:int[2][5] = [a, [6, 7, 8, 9, 10]]
var c:int[3][2][5] = [b, [[11, 12], [13, 14]], b]
var d:int[3][2][5] = c
println(a)
println(b)
println(c)
println(d)
```

### nested_3d_from_1d_2d.expect
```
[ 1, 2, 3, 4, 5 ]
[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
```

## Test: nested_from_vars

### nested_from_vars.fg
```javascript
var a:int[5] = [1, 2, 3, 4, 5]
var b:int[2][5] = [a, [6, 7, 8, 9, 10]]
var c:int[3][2][5] = [b, [[11, 12], [13, 14]], b]
println(a)
println(b)
println(c)
```

### nested_from_vars.expect
```
[ 1, 2, 3, 4, 5 ]
[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
```

## Test: println_1d_2d_3d

### println_1d_2d_3d.fg
```javascript
var a:int[5] = [1, 2, 3, 4, 5]
var b:int[2][5] = [a, [6, 7, 8, 9, 10]]
var c:int[3][2][5] = [b, [[11, 12], [13, 14]], b]
var d:int[3][2][5] = c
println(a)
println(b)
println(c)
println(d)
```

### println_1d_2d_3d.expect
```
[ 1, 2, 3, 4, 5 ]
[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
[ [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ], [ [ 11, 12, 0, 0, 0 ], [ 13, 14, 0, 0, 0 ] ], [ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ] ]
```

---

# Directory: ArrayTests/errors

## Test: array_index_not_int

### array_index_not_int.fg
```javascript
/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var a:int[2] = [1, 2]
var x:int[3] = [1, 3]
print(a[x])
```

## Test: empty_container

### empty_container.fg
```javascript
/; EXPECT_ERROR: EmptyContainerExpression
var x:int[2] = []
println(x)
```

## Test: index_more_dims

### index_more_dims.fg
```javascript
/; EXPECT_ERROR: IndexingMoreDimensionsThanArrayTypeHas
var a:int[2] = [1, 2]
println(a[0][2])
```

## Test: index_non_array

### index_non_array.fg
```javascript
/; EXPECT_ERROR: IndexingNonArrayTypeVariable
var a:int = 2
println(a[0])
```

## Test: init_type_mismatch

### init_type_mismatch.fg
```javascript
/; EXPECT_ERROR: InitializerExpressionTypeMismatch
var a:int[5] = [[2, 3], [2, 3]]
```

## Test: rank_mismatch_1d

### rank_mismatch_1d.fg
```javascript
/; EXPECT_ERROR: ContainerExpressionRankMismatch
var a:int[5] = [1, [2, 3]]
```

## Test: rank_mismatch_element

### rank_mismatch_element.fg
```javascript
/; EXPECT_ERROR: ContainerExpressionRankMismatch
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1, j]

var q:int[3][2] = [l, p, [7, p]]

print(q)
```

## Test: rank_mismatch_inner

### rank_mismatch_inner.fg
```javascript
/; EXPECT_ERROR: ContainerExpressionRankMismatch
var j = 2
var p:int[2] = [3, 5]
var l:int[2] = [1,j]
var q:int[3][2] = [l, p,[7,p]]
print(q)
```

## Test: variable_not_found

### variable_not_found.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]

print(a)
```

## Test: variable_not_found_3d

### variable_not_found_3d.fg
```javascript
/; EXPECT_ERROR: VariableNotFound
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]
print(a)
```

---

# Directory: ArrayTests/with_var_in_init

## Test: int_3d_partial_with_var

### int_3d_partial_with_var.fg
```javascript
var x:int = 10
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]
print(a)
```

### int_3d_partial_with_var.expect
```
[ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 10, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

## Test: int_3d_with_var

### int_3d_with_var.fg
```javascript
var x:int = 10
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]

print(a)
```

### int_3d_with_var.expect
```
[ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 10, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

---

# Directory: ArrayTests/slice_assignment

## Test: inline_row_and_element

### inline_row_and_element.fg
```javascript
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
println("x = ", x)
x[1] = [9, 8, 7]
println("x = ", x)
x[1][1] = 100
println("x = ", x)
```

### inline_row_and_element.expect
```
x = [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
x = [ [ 1, 2, 3 ], [ 9, 100, 7 ] ]
```

## Test: inline_row_only

### inline_row_only.fg
```javascript
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
println("x = ", x)
x[1] = [9, 8, 7]
println("x = ", x)
```

### inline_row_only.expect
```
x = [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
```

## Test: row_from_var

### row_from_var.fg
```javascript
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
println("x = ", x)
var j:int[3] = [9, 8, 7]
println("j = ", j)
x[1] = j
println("x = ", x)
println("j = ", j)
j[1] = 100
println("x = ", x)
println("j = ", j)
```

### row_from_var.expect
```
x = [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]
j = [ 9, 8, 7 ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
j = [ 9, 8, 7 ]
x = [ [ 1, 2, 3 ], [ 9, 8, 7 ] ]
j = [ 9, 100, 7 ]
```

---

# Directory: 01_basics

## Test: hello-world

### hello-world.fg
```javascript
print("Hello, World!")
```

### hello-world.expect
```
Hello, World!
```

## Test: print

### print.fg
```javascript
print(1, "\n")
print(1.0, "\n")
print(1.0f, "\n")
print(2.2, "\n")
print(2.2f, "\n")
print(true, "\n")
print(false, "\n")
print('a', "\n")
print('b', "\n")
```

### print.expect
```
1
1
1
2.2
2.2
true
false
a
b
```

## Test: println

### println.fg
```javascript
println(1)
println(1.0)
println(1.0f)
println(2.2)
println(2.2f)
println(true)
println(false)
println('a')
println('b')
println("hello", " ", "world")
```

### println.expect
```
1
1
1
2.2
2.2
true
false
a
b
hello world
```

---

