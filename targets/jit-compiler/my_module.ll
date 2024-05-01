; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

%t1 = type { ptr }
%DynamicType = type { i32, double, i1, ptr }

@formatStrprintfnewline = global [4 x i8] c"%s\0A\00"
@formatStrprintf = global [3 x i8] c"%s\00"
@formatStrscanf = global [10 x i8] c"%1000000s\00", align 1
@intFormat = global [3 x i8] c"%d\00"
@doubleFormat = global [6 x i8] c"%.14f\00"
@-jit-compiler-dev-all-targets-jit-compiler-jit-compiler-build-..-..-dir-math_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-jit-compiler-dev-all-targets-jit-compiler-jit-compiler-build-..-..-dir-math_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-jit-compiler-dev-all-targets-jit-compiler-jit-compiler-build-..-..-dir-math_FLOWWING_BREAK_COUNT = global i32 0
@-jit-compiler-dev-all-targets-jit-compiler-jit-compiler-build-..-..-dir-math_FLOWWING_CONTINUE_COUNT = global i32 0
@-jit-compiler-dev-all-targets-jit-compiler-jit-compiler-build-..-..-dir-math_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE" = constant [5 x i8] c"true\00"
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE" = constant [6 x i8] c"false\00"
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT" = global i32 0
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT" = global i32 0
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_ERROR_COUNT" = global i32 0
@obj = global %t1 zeroinitializer
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@a = global [10 x i32] zeroinitializer, !I !0, !ET !1
@PI = global double 0.000000e+00
@x = global i32 0
@4 = private unnamed_addr constant [6 x i8] c"hellO\00", align 1
@5 = private unnamed_addr constant [13 x i8] c"Enter number\00", align 1
@6 = private unnamed_addr constant [2 x i8] c"s\00", align 1
@zx = global %DynamicType zeroinitializer

declare ptr @malloc(i32)

declare i32 @strlen(ptr)

declare i32 @memcpy(ptr, ptr, i32)

declare i32 @strcmp(ptr, ptr)

declare i32 @printf(ptr, ...)

declare i32 @snprintf(ptr, i32, ptr, ...)

declare i32 @atoi(ptr)

declare double @atof(ptr)

declare i32 @scanf(ptr, ...)

declare i64 @atoll(ptr)

declare i32 @puts(ptr)

declare void @exit(i32)

define void @print(ptr %0, i1 %1) {
entry:
  br i1 %1, label %newline, label %withoutnewline

exit:                                             ; preds = %newline, %withoutnewline
  ret void

withoutnewline:                                   ; preds = %entry
  %2 = call i32 (ptr, ...) @printf(ptr @formatStrprintf, ptr %0)
  br label %exit

newline:                                          ; preds = %entry
  %3 = call i32 (ptr, ...) @printf(ptr @formatStrprintfnewline, ptr %0)
  br label %exit
}

define ptr @concat_strings(ptr %str1, ptr %str2) {
  %len1 = call i32 @strlen(ptr %str1)
  %len2 = call i32 @strlen(ptr %str2)
  %totalLen = add i32 %len1, %len2
  %totalLenPlusOne = add i32 %totalLen, 1
  %concatStr = call ptr @malloc(i32 %totalLenPlusOne)
  %ptr1 = bitcast ptr %concatStr to ptr
  %1 = call i32 @memcpy(ptr %ptr1, ptr %str1, i32 %len1)
  %ptr2 = getelementptr i8, ptr %ptr1, i32 %len1
  %2 = call i32 @memcpy(ptr %ptr2, ptr %str2, i32 %len2)
  %nullPtr = getelementptr i8, ptr %concatStr, i32 %totalLen
  store i8 0, ptr %nullPtr, align 1
  ret ptr %concatStr
}

define i32 @string_length(ptr %str) {
entry:
  %len = call i32 @strlen(ptr %str)
  ret i32 %len
}

define ptr @itos(i32 %num) {
  %buffer = call ptr @malloc(i32 12)
  %formatStr = getelementptr [3 x i8], ptr @intFormat, i32 0, i32 0
  %1 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr %buffer, i32 12, ptr %formatStr, i32 %num)
  ret ptr %buffer
}

define ptr @dtos(double %f) {
  %buffer = call ptr @malloc(i32 32)
  %formatStr = getelementptr [6 x i8], ptr @doubleFormat, i32 0, i32 0
  %1 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr %buffer, i32 32, ptr %formatStr, double %f)
  ret ptr %buffer
}

define ptr @get_malloc_ptr_of_string_constant(ptr %str) {
  %len = call i32 @strlen(ptr %str)
  %lenIncreasedByOne = add i32 %len, 1
  %strPtr = call ptr @malloc(i32 %lenIncreasedByOne)
  %1 = call i32 @memcpy(ptr %strPtr, ptr %str, i32 %lenIncreasedByOne)
  ret ptr %strPtr
}

define ptr @get_malloc_ptr_of_int_constant(i32 %num) {
  %buffer = call ptr @malloc(i32 12)
  %formatStr = getelementptr [3 x i8], ptr @intFormat, i32 0, i32 0
  %1 = call i32 (ptr, i32, ptr, ...) @snprintf(ptr %buffer, i32 12, ptr %formatStr, i32 %num)
  ret ptr %buffer
}

define i32 @compare_strings(ptr %str1, ptr %str2) {
  %result = call i32 @strcmp(ptr %str1, ptr %str2)
  ret i32 %result
}

define i1 @less_than_strings(ptr %str1, ptr %str2) {
  %result = call i32 @strcmp(ptr %str1, ptr %str2)
  %less_than = icmp slt i32 %result, 0
  ret i1 %less_than
}

define i1 @less_than_or_equal_strings(ptr %str1, ptr %str2) {
  %result = call i32 @strcmp(ptr %str1, ptr %str2)
  %less_than_or_equal = icmp sle i32 %result, 0
  ret i1 %less_than_or_equal
}

define i1 @greater_than_strings(ptr %str1, ptr %str2) {
  %result = call i32 @strcmp(ptr %str1, ptr %str2)
  %greater_than = icmp sgt i32 %result, 0
  ret i1 %greater_than
}

define i1 @greater_than_or_equal_strings(ptr %str1, ptr %str2) {
  %result = call i32 @strcmp(ptr %str1, ptr %str2)
  %greater_than_or_equal = icmp sge i32 %result, 0
  ret i1 %greater_than_or_equal
}

define i1 @equal_strings(ptr %str1, ptr %str2) {
  %result = call i32 @strcmp(ptr %str1, ptr %str2)
  %equal = icmp eq i32 %result, 0
  ret i1 %equal
}

define ptr @get_input() {
entry:
  %inputValue = call ptr @malloc(i32 1000001)
  %0 = call i32 (ptr, ...) @scanf(ptr @formatStrscanf, ptr %inputValue, i32 0, i32 0)
  ret ptr %inputValue
}

define i32 @string_to_int(ptr %str) {
entry:
  %intValue = call i32 @atoi(ptr %str)
  ret i32 %intValue
}

define i64 @string_to_long(ptr %str) {
entry:
  %longValue = call i64 @atoll(ptr %str)
  ret i64 %longValue
}

define double @string_to_double(ptr %str) {
entry:
  %doubleValue = call double @atof(ptr %str)
  ret double %doubleValue
}

define void @raise_exception(ptr %errorMsg) {
  %res = call i32 @puts(ptr %errorMsg)
  call void @exit(i32 1)
  unreachable
}

define i32 @"1710009489772_math"() {
entry:
  store double 3.140000e+00, ptr @PI, align 8
  store i32 1, ptr @a, align 4
  store i32 2, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 1), align 4
  store i32 3, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 2), align 4
  store i32 4, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 3), align 4
  store i32 5, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 4), align 4
  store i32 6, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 5), align 4
  store i32 7, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 6), align 4
  store i32 8, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 7), align 4
  store i32 9, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 8), align 4
  store i32 10, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 9), align 4
  store ptr @0, ptr @obj, align 8
  store ptr @1, ptr @obj, align 8
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define double @area(i32 %0) !rt !2 {
entry:
  %r = alloca i32, align 4
  store i32 %0, ptr %r, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %mergeBlock, %checkContinueBlock
  ret double 0.000000e+00

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %PI = load double, ptr @PI, align 8
  %r1 = load i32, ptr %r, align 4
  %1 = sitofp i32 %r1 to double
  %2 = fmul double %PI, %1
  %r2 = load i32, ptr %r, align 4
  %3 = sitofp i32 %r2 to double
  %4 = fmul double %2, %3
  %PI3 = load double, ptr @PI, align 8
  %r4 = load i32, ptr %r, align 4
  %5 = sitofp i32 %r4 to double
  %6 = fmul double %PI3, %5
  %r5 = load i32, ptr %r, align 4
  %7 = sitofp i32 %r5 to double
  %8 = fmul double %6, %7
  ret double %8

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @-jit-compiler-dev-all-targets-jit-compiler-jit-compiler-build-..-..-dir-math_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define i32 @"____##FLOWWING_GLOBAL_ENTRY_POINT____##"() {
entry:
  store ptr @2, ptr @obj, align 8
  store ptr @3, ptr @obj, align 8
  store i32 1, ptr @a, align 4
  store i32 2, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 1), align 4
  store i32 3, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 2), align 4
  store i32 4, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 3), align 4
  store i32 5, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 4), align 4
  store i32 6, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 5), align 4
  store i32 7, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 6), align 4
  store i32 8, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 7), align 4
  store i32 9, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 8), align 4
  store i32 10, ptr getelementptr inbounds ([10 x i32], ptr @a, i32 0, i32 9), align 4
  store double 3.140000e+00, ptr @PI, align 8
  %0 = call i32 @"1710009489772_math"()
  store i32 0, ptr @x, align 4
  call void @print(ptr @4, i1 false)
  call void @print(ptr @5, i1 false)
  %1 = call ptr @get_input()
  %2 = call i32 @string_to_int(ptr %1)
  store i32 %2, ptr @x, align 4
  %3 = call double @area(i32 2)
  %4 = call ptr @dtos(double %3)
  call void @print(ptr %4, i1 false)
  store ptr @6, ptr getelementptr inbounds (%DynamicType, ptr @zx, i32 0, i32 3), align 8
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

!0 = !{!"10:"}
!1 = !{!"28"}
!2 = !{!"area:rt:pr:29"}
