; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

%DynamicType = type { i32, double, i1, ptr }
%t2 = type { i32, %t1 }
%t1 = type { i32, ptr }

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
@0 = private unnamed_addr constant [7 x i8] c"string\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = constant ptr @1
@2 = private unnamed_addr constant [2 x i8] c"c\00", align 1
@3 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = constant ptr @3
@4 = private unnamed_addr constant [3 x i8] c", \00", align 1
@" , " = constant ptr @4
@5 = private unnamed_addr constant [2 x i8] c"d\00", align 1
@6 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@7 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@8 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'" = constant ptr @8
@9 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = constant ptr @9
@main_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@main_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@main_FLOWWING_BREAK_COUNT = global i32 0
@main_FLOWWING_CONTINUE_COUNT = global i32 0
@main_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@staticVar = global i32 0
@10 = private unnamed_addr constant [14 x i8] c"Hello, world!\00", align 1
@dynamicVar = global %DynamicType zeroinitializer
@11 = private unnamed_addr constant [24 x i8] c"Static variable value: \00", align 1
@12 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@13 = private unnamed_addr constant [25 x i8] c"Dynamic variable value: \00", align 1

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

afterNestedBlock:                                 ; preds = %Merge, %checkContinueBlock6, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  br label %returnBlock

nestedBlock:                                      ; preds = %entry
  %x = alloca %t2, align 8
  %0 = getelementptr inbounds %t2, ptr %x, i32 0, i32 0
  store i32 2, ptr %0, align 4
  %1 = getelementptr inbounds %t2, ptr %x, i32 0, i32 1
  %2 = getelementptr inbounds %t1, ptr %1, i32 0, i32 0
  store i32 3, ptr %2, align 4
  %3 = getelementptr inbounds %t1, ptr %1, i32 0, i32 1
  store ptr @0, ptr %3, align 8
  %4 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %6 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %y = alloca %t2, align 8
  %8 = getelementptr inbounds %t2, ptr %y, i32 0, i32 0
  %9 = getelementptr inbounds %t2, ptr %x, i32 0, i32 0
  %10 = load i32, ptr %9, align 4
  store i32 %10, ptr %8, align 4
  %11 = getelementptr inbounds %t2, ptr %y, i32 0, i32 1
  %12 = getelementptr inbounds %t2, ptr %x, i32 0, i32 1
  %13 = getelementptr inbounds %t1, ptr %11, i32 0, i32 0
  %14 = getelementptr inbounds %t1, ptr %12, i32 0, i32 0
  %15 = load i32, ptr %14, align 4
  store i32 %15, ptr %13, align 4
  %16 = getelementptr inbounds %t1, ptr %11, i32 0, i32 1
  %17 = getelementptr inbounds %t1, ptr %12, i32 0, i32 1
  %18 = load ptr, ptr %17, align 8
  store ptr %18, ptr %16, align 8
  %19 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %21 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %23 = getelementptr inbounds %t2, ptr %y, i32 0, i32 0
  store i32 5, ptr %23, align 4
  %24 = getelementptr inbounds %t2, ptr %y, i32 0, i32 1
  %25 = getelementptr inbounds %t2, ptr %x, i32 0, i32 1
  %26 = getelementptr inbounds %t1, ptr %24, i32 0, i32 0
  %27 = getelementptr inbounds %t1, ptr %25, i32 0, i32 0
  %28 = load i32, ptr %27, align 4
  store i32 %28, ptr %26, align 4
  %29 = getelementptr inbounds %t1, ptr %24, i32 0, i32 1
  %30 = getelementptr inbounds %t1, ptr %25, i32 0, i32 1
  %31 = load ptr, ptr %30, align 8
  store ptr %31, ptr %29, align 8
  %32 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %34 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %36 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %36, i1 false)
  call void @print(ptr @2, i1 false)
  %37 = load ptr, ptr @" : ", align 8
  call void @print(ptr %37, i1 false)
  %38 = getelementptr inbounds %t2, ptr %y, i32 0, i32 0
  %39 = load i32, ptr %38, align 4
  %40 = call ptr @itos(i32 %39)
  call void @print(ptr %40, i1 false)
  %41 = load ptr, ptr @" , ", align 8
  call void @print(ptr %41, i1 false)
  call void @print(ptr @5, i1 false)
  %42 = load ptr, ptr @" : ", align 8
  call void @print(ptr %42, i1 false)
  %43 = getelementptr inbounds %t2, ptr %y, i32 0, i32 1
  %44 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %44, i1 false)
  call void @print(ptr @6, i1 false)
  %45 = load ptr, ptr @" : ", align 8
  call void @print(ptr %45, i1 false)
  %46 = getelementptr inbounds %t1, ptr %43, i32 0, i32 0
  %47 = load i32, ptr %46, align 4
  %48 = call ptr @itos(i32 %47)
  call void @print(ptr %48, i1 false)
  %49 = load ptr, ptr @" , ", align 8
  call void @print(ptr %49, i1 false)
  call void @print(ptr @7, i1 false)
  %50 = load ptr, ptr @" : ", align 8
  call void @print(ptr %50, i1 false)
  %51 = getelementptr inbounds %t1, ptr %43, i32 0, i32 1
  %52 = load ptr, ptr %51, align 8
  %53 = load ptr, ptr @"'", align 8
  call void @print(ptr %53, i1 false)
  %54 = icmp ne ptr %52, null
  br i1 %54, label %End, label %IsNull

checkContinueBlock6:                              ; preds = %Merge
  br label %afterNestedBlock

IsNull:                                           ; preds = %nestedBlock5
  br label %Merge

End:                                              ; preds = %nestedBlock5
  call void @print(ptr %52, i1 false)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %55 = load ptr, ptr @"'", align 8
  call void @print(ptr %55, i1 false)
  %56 = load ptr, ptr @"}", align 8
  call void @print(ptr %56, i1 false)
  %57 = load ptr, ptr @"}", align 8
  call void @print(ptr %57, i1 false)
  %58 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %59 = icmp eq i32 %58, 0
  br i1 %59, label %checkContinueBlock6, label %afterNestedBlock
}

define i32 @main() {
entry:
  store i32 10, ptr @staticVar, align 4
  store ptr @10, ptr getelementptr inbounds (%DynamicType, ptr @dynamicVar, i32 0, i32 3), align 8
  %staticVar = load i32, ptr @staticVar, align 4
  %0 = call ptr @itos(i32 %staticVar)
  %1 = call ptr @concat_strings(ptr @11, ptr %0)
  call void @print(ptr %1, i1 false)
  call void @print(ptr @12, i1 false)
  %2 = load ptr, ptr getelementptr inbounds (%DynamicType, ptr @dynamicVar, i32 0, i32 3), align 8
  %3 = call ptr @concat_strings(ptr @13, ptr %2)
  call void @print(ptr %3, i1 false)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}
