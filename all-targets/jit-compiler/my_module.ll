; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

%parentType = type { ptr, ptr, ptr }
%my = type { i32 }

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
@0 = private unnamed_addr constant [3 x i8] c"ss\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"s\00", align 1

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
  br label %nestedBlock

returnBlock:                                      ; preds = %afterNestedBlock
  ret i32 0

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  br label %returnBlock

nestedBlock:                                      ; preds = %entry
  %0 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %1 = icmp eq i32 %0, 0
  br i1 %1, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %2 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %4 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %6 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %x = alloca %parentType, align 8
  %8 = getelementptr %parentType, ptr %x, i32 0, i32 0
  store ptr @0, ptr %8, align 8
  %9 = getelementptr %parentType, ptr %x, i32 0, i32 2
  %10 = getelementptr %my, ptr %9, i32 0, i32 0
  store i32 22, ptr %10, align 4
  %11 = getelementptr %parentType, ptr %x, i32 0, i32 1
  %12 = getelementptr %parentType, ptr %11, i32 0, i32 0
  store ptr @1, ptr %12, align 8
  %13 = getelementptr %parentType, ptr %11, i32 0, i32 2
  %14 = getelementptr %my, ptr %13, i32 0, i32 0
  store i32 1, ptr %14, align 4
  %15 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %17 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %19 = getelementptr inbounds %parentType, ptr %x, i32 0, i32 2
  %20 = getelementptr inbounds %my, ptr %19, i32 0, i32 0
  %21 = load i32, ptr %20, align 4
  %22 = call ptr @itos(i32 %21)
  call void @print(ptr %22, i1 false)
  %23 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}