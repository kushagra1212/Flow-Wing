; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

@formatStrprintfnewline = global [4 x i8] c"%s\0A\00"
@formatStrprintf = global [3 x i8] c"%s\00"
@formatStrscanf = global [10 x i8] c"%1000000s\00", align 1
@intFormat = global [3 x i8] c"%d\00"
@doubleFormat = global [6 x i8] c"%.14f\00"
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE" = constant [5 x i8] c"true\00"
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE" = constant [6 x i8] c"false\00"
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT" = global i32 0
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT" = global i32 0
@"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_ERROR_COUNT" = global i32 0
@0 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket = constant ptr @0
@1 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma = constant ptr @1
@2 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket = constant ptr @2
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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

define i32 @"____##FLOWWING_GLOBAL_ENTRY_POINT____##"() {
entry:
  %0 = call ptr @main()
  %1 = load [2 x [5 x i32]], ptr %0, align 4
  %2 = alloca [2 x [5 x i32]], align 4
  store [2 x [5 x i32]] %1, ptr %2, align 4
  %3 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %3, i1 false)
  %4 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %4, i1 false)
  %5 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 0, i32 0
  %6 = load i32, ptr %5, align 4
  %7 = call ptr @itos(i32 %6)
  call void @print(ptr %7, i1 false)
  %8 = load ptr, ptr @comma, align 8
  call void @print(ptr %8, i1 false)
  %9 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 0, i32 1
  %10 = load i32, ptr %9, align 4
  %11 = call ptr @itos(i32 %10)
  call void @print(ptr %11, i1 false)
  %12 = load ptr, ptr @comma, align 8
  call void @print(ptr %12, i1 false)
  %13 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 0, i32 2
  %14 = load i32, ptr %13, align 4
  %15 = call ptr @itos(i32 %14)
  call void @print(ptr %15, i1 false)
  %16 = load ptr, ptr @comma, align 8
  call void @print(ptr %16, i1 false)
  %17 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 0, i32 3
  %18 = load i32, ptr %17, align 4
  %19 = call ptr @itos(i32 %18)
  call void @print(ptr %19, i1 false)
  %20 = load ptr, ptr @comma, align 8
  call void @print(ptr %20, i1 false)
  %21 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 0, i32 4
  %22 = load i32, ptr %21, align 4
  %23 = call ptr @itos(i32 %22)
  call void @print(ptr %23, i1 false)
  %24 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %24, i1 false)
  %25 = load ptr, ptr @comma, align 8
  call void @print(ptr %25, i1 false)
  %26 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %26, i1 false)
  %27 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 1, i32 0
  %28 = load i32, ptr %27, align 4
  %29 = call ptr @itos(i32 %28)
  call void @print(ptr %29, i1 false)
  %30 = load ptr, ptr @comma, align 8
  call void @print(ptr %30, i1 false)
  %31 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 1, i32 1
  %32 = load i32, ptr %31, align 4
  %33 = call ptr @itos(i32 %32)
  call void @print(ptr %33, i1 false)
  %34 = load ptr, ptr @comma, align 8
  call void @print(ptr %34, i1 false)
  %35 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 1, i32 2
  %36 = load i32, ptr %35, align 4
  %37 = call ptr @itos(i32 %36)
  call void @print(ptr %37, i1 false)
  %38 = load ptr, ptr @comma, align 8
  call void @print(ptr %38, i1 false)
  %39 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 1, i32 3
  %40 = load i32, ptr %39, align 4
  %41 = call ptr @itos(i32 %40)
  call void @print(ptr %41, i1 false)
  %42 = load ptr, ptr @comma, align 8
  call void @print(ptr %42, i1 false)
  %43 = getelementptr [2 x [5 x i32]], ptr %2, i32 0, i32 1, i32 4
  %44 = load i32, ptr %43, align 4
  %45 = call ptr @itos(i32 %44)
  call void @print(ptr %45, i1 false)
  %46 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %46, i1 false)
  %47 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %47, i1 false)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define ptr @main() !rt !0 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %mergeBlock, %checkContinueBlock2, %checkContinueBlock, %nestedBlock
  ret ptr @3

nestedBlock:                                      ; preds = %entry
  %x = alloca [2 x [5 x i32]], align 4, !I !1, !ET !2
  %0 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 0
  store i32 0, ptr %0, align 4
  %1 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 1
  store i32 0, ptr %1, align 4
  %2 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 2
  store i32 0, ptr %2, align 4
  %3 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 3
  store i32 0, ptr %3, align 4
  %4 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 4
  store i32 0, ptr %4, align 4
  %5 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 1, i32 0
  store i32 0, ptr %5, align 4
  %6 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 1, i32 1
  store i32 0, ptr %6, align 4
  %7 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 1, i32 2
  store i32 0, ptr %7, align 4
  %8 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 1, i32 3
  store i32 0, ptr %8, align 4
  %9 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 1, i32 4
  store i32 0, ptr %9, align 4
  %10 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 0
  store i32 10, ptr %10, align 4
  %11 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 1
  store i32 10, ptr %11, align 4
  %12 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 2
  store i32 10, ptr %12, align 4
  %13 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 3
  store i32 10, ptr %13, align 4
  %14 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 0, i32 4
  store i32 10, ptr %14, align 4
  %15 = getelementptr [2 x [5 x i32]], ptr %x, i32 0, i32 1, i32 0
  store i32 10, ptr %15, align 4
  %16 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %18 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  br label %returnBlock

checkContinueBlock2:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock1
  ret ptr %x

mergeBlock:                                       ; No predecessors!
  %20 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock2, label %afterNestedBlock
}

!0 = !{!"main:rt:ay:2:sz:2:5:"}
!1 = !{!"2:5:"}
!2 = !{!"2"}
