; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

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
@x = global %t2 zeroinitializer
@0 = private unnamed_addr constant [2 x i8] c"x\00", align 1
@y = global %t2 zeroinitializer
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
@10 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@11 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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
  store i32 2, ptr @x, align 4
  store i32 50, ptr getelementptr inbounds (%t2, ptr @x, i32 0, i32 1), align 4
  store ptr @0, ptr getelementptr inbounds (%t2, ptr @x, i32 0, i32 1, i32 1), align 8
  %0 = load i32, ptr @x, align 4
  store i32 %0, ptr @y, align 4
  %1 = load i32, ptr getelementptr inbounds (%t2, ptr @x, i32 0, i32 1), align 4
  store i32 %1, ptr getelementptr inbounds (%t2, ptr @y, i32 0, i32 1), align 4
  %2 = load ptr, ptr getelementptr inbounds (%t2, ptr @x, i32 0, i32 1, i32 1), align 8
  store ptr %2, ptr getelementptr inbounds (%t2, ptr @y, i32 0, i32 1, i32 1), align 8
  %3 = call ptr @main(ptr @x)
  %4 = load %t2, ptr %3, align 8
  store %t2 %4, ptr @y, align 8
  %5 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %5, i1 false)
  call void @print(ptr @2, i1 false)
  %6 = load ptr, ptr @" : ", align 8
  call void @print(ptr %6, i1 false)
  %7 = load i32, ptr @y, align 4
  %8 = call ptr @itos(i32 %7)
  call void @print(ptr %8, i1 false)
  %9 = load ptr, ptr @" , ", align 8
  call void @print(ptr %9, i1 false)
  call void @print(ptr @5, i1 false)
  %10 = load ptr, ptr @" : ", align 8
  call void @print(ptr %10, i1 false)
  %11 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %11, i1 false)
  call void @print(ptr @6, i1 false)
  %12 = load ptr, ptr @" : ", align 8
  call void @print(ptr %12, i1 false)
  %13 = load i32, ptr getelementptr inbounds (%t2, ptr @y, i32 0, i32 1), align 4
  %14 = call ptr @itos(i32 %13)
  call void @print(ptr %14, i1 false)
  %15 = load ptr, ptr @" , ", align 8
  call void @print(ptr %15, i1 false)
  call void @print(ptr @7, i1 false)
  %16 = load ptr, ptr @" : ", align 8
  call void @print(ptr %16, i1 false)
  %17 = load ptr, ptr getelementptr inbounds (%t2, ptr @y, i32 0, i32 1, i32 1), align 8
  %18 = load ptr, ptr @"'", align 8
  call void @print(ptr %18, i1 false)
  %19 = icmp ne ptr %17, null
  br i1 %19, label %End, label %IsNull

returnBlock:                                      ; preds = %Merge
  ret i32 0

IsNull:                                           ; preds = %entry
  br label %Merge

End:                                              ; preds = %entry
  call void @print(ptr %17, i1 false)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %20 = load ptr, ptr @"'", align 8
  call void @print(ptr %20, i1 false)
  %21 = load ptr, ptr @"}", align 8
  call void @print(ptr %21, i1 false)
  %22 = load ptr, ptr @"}", align 8
  call void @print(ptr %22, i1 false)
  br label %returnBlock
}

define ptr @main(ptr %0) !rt !0 {
entry:
  %v = alloca %t2, align 8
  %1 = getelementptr inbounds %t2, ptr %v, i32 0, i32 0
  %2 = getelementptr inbounds %t2, ptr %0, i32 0, i32 0
  %3 = load i32, ptr %2, align 4
  store i32 %3, ptr %1, align 4
  %4 = getelementptr inbounds %t2, ptr %v, i32 0, i32 1
  %5 = getelementptr inbounds %t2, ptr %0, i32 0, i32 1
  %6 = getelementptr inbounds %t1, ptr %4, i32 0, i32 0
  %7 = getelementptr inbounds %t1, ptr %5, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  store i32 %8, ptr %6, align 4
  %9 = getelementptr inbounds %t1, ptr %4, i32 0, i32 1
  %10 = getelementptr inbounds %t1, ptr %5, i32 0, i32 1
  %11 = load ptr, ptr %10, align 8
  store ptr %11, ptr %9, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %mergeBlock, %checkContinueBlock8, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret ptr @11

nestedBlock:                                      ; preds = %entry
  %12 = getelementptr inbounds %t2, ptr %v, i32 0, i32 0
  %13 = load i32, ptr %12, align 4
  store i32 11, ptr %12, align 4
  %14 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %16 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %18 = getelementptr inbounds %t2, ptr %v, i32 0, i32 1
  %19 = getelementptr inbounds %t1, ptr %18, i32 0, i32 0
  store i32 100, ptr %19, align 4
  %20 = getelementptr inbounds %t1, ptr %18, i32 0, i32 1
  store ptr @10, ptr %20, align 8
  %21 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %e = alloca %t2, align 8
  %25 = getelementptr inbounds %t2, ptr %e, i32 0, i32 0
  %26 = getelementptr inbounds %t2, ptr %v, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  store i32 %27, ptr %25, align 4
  %28 = getelementptr inbounds %t2, ptr %e, i32 0, i32 1
  %29 = getelementptr inbounds %t2, ptr %v, i32 0, i32 1
  %30 = getelementptr inbounds %t1, ptr %28, i32 0, i32 0
  %31 = getelementptr inbounds %t1, ptr %29, i32 0, i32 0
  %32 = load i32, ptr %31, align 4
  store i32 %32, ptr %30, align 4
  %33 = getelementptr inbounds %t1, ptr %28, i32 0, i32 1
  %34 = getelementptr inbounds %t1, ptr %29, i32 0, i32 1
  %35 = load ptr, ptr %34, align 8
  store ptr %35, ptr %33, align 8
  %36 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %38 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %f = alloca %t1, align 8
  %40 = getelementptr inbounds %t2, ptr %e, i32 0, i32 1
  %41 = getelementptr inbounds %t1, ptr %f, i32 0, i32 0
  %42 = getelementptr inbounds %t1, ptr %40, i32 0, i32 0
  %43 = load i32, ptr %42, align 4
  store i32 %43, ptr %41, align 4
  %44 = getelementptr inbounds %t1, ptr %f, i32 0, i32 1
  %45 = getelementptr inbounds %t1, ptr %40, i32 0, i32 1
  %46 = load ptr, ptr %45, align 8
  store ptr %46, ptr %44, align 8
  %47 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %49 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  br label %returnBlock

checkContinueBlock8:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock7
  ret ptr %f

mergeBlock:                                       ; No predecessors!
  %51 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock8, label %afterNestedBlock
}

!0 = !{!"main:rt:ob:t2"}
