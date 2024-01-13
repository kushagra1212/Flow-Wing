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
  %0 = call i32 @sum(i32 10)
  %1 = call ptr @itos(i32 %0)
  call void @print(ptr %1, i1 false)
  %2 = call i32 @sum(i32 10)
  %3 = call ptr @itos(i32 %2)
  call void @print(ptr %3, i1 false)
  %4 = call i32 @sum(i32 10)
  %5 = call ptr @itos(i32 %4)
  call void @print(ptr %5, i1 false)
  %6 = call i32 @sum(i32 10)
  %7 = call ptr @itos(i32 %6)
  call void @print(ptr %7, i1 false)
  %8 = call i32 @sum(i32 10)
  %9 = call ptr @itos(i32 %8)
  call void @print(ptr %9, i1 false)
  %10 = call i32 @sum(i32 10)
  %11 = call ptr @itos(i32 %10)
  call void @print(ptr %11, i1 false)
  %12 = call i32 @sum(i32 10)
  %13 = call ptr @itos(i32 %12)
  call void @print(ptr %13, i1 false)
  %14 = call i32 @sum2(i32 10)
  %15 = call ptr @itos(i32 %14)
  call void @print(ptr %15, i1 false)
  %16 = call i32 @sum2(i32 10)
  %17 = call ptr @itos(i32 %16)
  call void @print(ptr %17, i1 false)
  %18 = call i32 @sum2(i32 10)
  %19 = call ptr @itos(i32 %18)
  call void @print(ptr %19, i1 false)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define i32 @sum(i32 %n) !rt !0 !argInfo0 !1 {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %mergeBlock9, %afterIfElse, %checkContinueBlock3, %checkContinueBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  %n4 = load i32, ptr %n1, align 4
  %0 = icmp eq i32 %n4, 0
  br i1 %0, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %1 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  br label %returnBlock8

checkContinueBlock3:                              ; preds = %mergeBlock9
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock6

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %afterNestedBlock5, %else
  %3 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock5:                                ; preds = %mergeBlock, %checkContinueBlock7
  br label %afterIfElse

nestedBlock6:                                     ; preds = %then
  br label %returnBlock

checkContinueBlock7:                              ; preds = %mergeBlock
  br label %afterNestedBlock5

returnBlock:                                      ; preds = %nestedBlock6
  ret i32 0

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock7, label %afterNestedBlock5

returnBlock8:                                     ; preds = %nestedBlock2
  %n10 = load i32, ptr %n1, align 4
  %n11 = load i32, ptr %n1, align 4
  %7 = sub i32 %n11, 1
  %8 = call i32 @sum(i32 %7)
  %9 = add i32 %n10, %8
  %n12 = load i32, ptr %n1, align 4
  %n13 = load i32, ptr %n1, align 4
  %10 = sub i32 %n13, 1
  %11 = call i32 @sum(i32 %10)
  %12 = add i32 %n12, %11
  ret i32 %12

mergeBlock9:                                      ; No predecessors!
  %13 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock3, label %afterNestedBlock
}

define i32 @sum2(i32 %n) !rt !2 !argInfo0 !1 {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %mergeBlock9, %afterIfElse, %checkContinueBlock3, %checkContinueBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  %n4 = load i32, ptr %n1, align 4
  %0 = icmp eq i32 %n4, 0
  br i1 %0, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %1 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  br label %returnBlock8

checkContinueBlock3:                              ; preds = %mergeBlock9
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock6

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %afterNestedBlock5, %else
  %3 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock5:                                ; preds = %mergeBlock, %checkContinueBlock7
  br label %afterIfElse

nestedBlock6:                                     ; preds = %then
  br label %returnBlock

checkContinueBlock7:                              ; preds = %mergeBlock
  br label %afterNestedBlock5

returnBlock:                                      ; preds = %nestedBlock6
  ret i32 0

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock7, label %afterNestedBlock5

returnBlock8:                                     ; preds = %nestedBlock2
  %n10 = load i32, ptr %n1, align 4
  %n11 = load i32, ptr %n1, align 4
  %7 = sub i32 %n11, 1
  %8 = call i32 @sum(i32 %7)
  %9 = add i32 %n10, %8
  %n12 = load i32, ptr %n1, align 4
  %n13 = load i32, ptr %n1, align 4
  %10 = sub i32 %n13, 1
  %11 = call i32 @sum(i32 %10)
  %12 = add i32 %n12, %11
  ret i32 %12

mergeBlock9:                                      ; No predecessors!
  %13 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock3, label %afterNestedBlock
}

!0 = !{!"sum:rt:pr:28"}
!1 = !{!"function0:Integer32"}
!2 = !{!"sum2:rt:pr:28"}
