; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"

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
@arr = global [2 x [2 x i32]] zeroinitializer, !I !0, !ET !1
@arr2 = global [2 x [4 x i32]] zeroinitializer, !I !2, !ET !1
@0 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket = constant ptr @0
@1 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma = constant ptr @1
@2 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket = constant ptr @2

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
  store i32 2, ptr @arr, align 4
  store i32 2, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 0, i32 1), align 4
  store i32 3, ptr @arr2, align 4
  store i32 3, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 0, i32 1), align 4
  %0 = load i32, ptr @arr, align 4
  store i32 %0, ptr @arr2, align 4
  %1 = load i32, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 0, i32 1), align 4
  store i32 %1, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 0, i32 1), align 4
  %2 = load i32, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 1, i32 0), align 4
  store i32 %2, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 1, i32 0), align 4
  %3 = load i32, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 1, i32 1), align 4
  store i32 %3, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 1, i32 1), align 4
  %4 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %4, i1 false)
  %5 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %5, i1 false)
  %6 = load i32, ptr @arr2, align 4
  %7 = call ptr @itos(i32 %6)
  call void @print(ptr %7, i1 false)
  %8 = load ptr, ptr @comma, align 8
  call void @print(ptr %8, i1 false)
  %9 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 0, i32 1), align 4
  %10 = call ptr @itos(i32 %9)
  call void @print(ptr %10, i1 false)
  %11 = load ptr, ptr @comma, align 8
  call void @print(ptr %11, i1 false)
  %12 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 0, i32 2), align 4
  %13 = call ptr @itos(i32 %12)
  call void @print(ptr %13, i1 false)
  %14 = load ptr, ptr @comma, align 8
  call void @print(ptr %14, i1 false)
  %15 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 0, i32 3), align 4
  %16 = call ptr @itos(i32 %15)
  call void @print(ptr %16, i1 false)
  %17 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %17, i1 false)
  %18 = load ptr, ptr @comma, align 8
  call void @print(ptr %18, i1 false)
  %19 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %19, i1 false)
  %20 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 1, i32 0), align 4
  %21 = call ptr @itos(i32 %20)
  call void @print(ptr %21, i1 false)
  %22 = load ptr, ptr @comma, align 8
  call void @print(ptr %22, i1 false)
  %23 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 1, i32 1), align 4
  %24 = call ptr @itos(i32 %23)
  call void @print(ptr %24, i1 false)
  %25 = load ptr, ptr @comma, align 8
  call void @print(ptr %25, i1 false)
  %26 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 1, i32 2), align 4
  %27 = call ptr @itos(i32 %26)
  call void @print(ptr %27, i1 false)
  %28 = load ptr, ptr @comma, align 8
  call void @print(ptr %28, i1 false)
  %29 = load i32, ptr getelementptr inbounds ([2 x [4 x i32]], ptr @arr2, i32 0, i32 1, i32 3), align 4
  %30 = call ptr @itos(i32 %29)
  call void @print(ptr %30, i1 false)
  %31 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %31, i1 false)
  %32 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %32, i1 false)
  %33 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %33, i1 false)
  %34 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %34, i1 false)
  %35 = load i32, ptr @arr, align 4
  %36 = call ptr @itos(i32 %35)
  call void @print(ptr %36, i1 false)
  %37 = load ptr, ptr @comma, align 8
  call void @print(ptr %37, i1 false)
  %38 = load i32, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 0, i32 1), align 4
  %39 = call ptr @itos(i32 %38)
  call void @print(ptr %39, i1 false)
  %40 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %40, i1 false)
  %41 = load ptr, ptr @comma, align 8
  call void @print(ptr %41, i1 false)
  %42 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %42, i1 false)
  %43 = load i32, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 1, i32 0), align 4
  %44 = call ptr @itos(i32 %43)
  call void @print(ptr %44, i1 false)
  %45 = load ptr, ptr @comma, align 8
  call void @print(ptr %45, i1 false)
  %46 = load i32, ptr getelementptr inbounds ([2 x [2 x i32]], ptr @arr, i32 0, i32 1, i32 1), align 4
  %47 = call ptr @itos(i32 %46)
  call void @print(ptr %47, i1 false)
  %48 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %48, i1 false)
  %49 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %49, i1 false)
  call void @main(ptr @arr, ptr @arr2)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @main(ptr %arr, ptr %arr2) !argInfo0 !3 !argInfo1 !4 {
entry:
  %arr1 = alloca [2 x [2 x i32]], align 4, !I !0, !ET !1
  %0 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 0, i32 0
  %1 = getelementptr [2 x [2 x i32]], ptr %arr, i32 0, i32 0, i32 0
  %2 = load i32, ptr %1, align 4
  store i32 %2, ptr %0, align 4
  %3 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 0, i32 1
  %4 = getelementptr [2 x [2 x i32]], ptr %arr, i32 0, i32 0, i32 1
  %5 = load i32, ptr %4, align 4
  store i32 %5, ptr %3, align 4
  %6 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 1, i32 0
  %7 = getelementptr [2 x [2 x i32]], ptr %arr, i32 0, i32 1, i32 0
  %8 = load i32, ptr %7, align 4
  store i32 %8, ptr %6, align 4
  %9 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 1, i32 1
  %10 = getelementptr [2 x [2 x i32]], ptr %arr, i32 0, i32 1, i32 1
  %11 = load i32, ptr %10, align 4
  store i32 %11, ptr %9, align 4
  %arr22 = alloca [2 x [4 x i32]], align 4, !I !2, !ET !1
  %12 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 0
  %13 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 0, i32 0
  %14 = load i32, ptr %13, align 4
  store i32 %14, ptr %12, align 4
  %15 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 1
  %16 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 0, i32 1
  %17 = load i32, ptr %16, align 4
  store i32 %17, ptr %15, align 4
  %18 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 2
  %19 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 0, i32 2
  %20 = load i32, ptr %19, align 4
  store i32 %20, ptr %18, align 4
  %21 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 3
  %22 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 0, i32 3
  %23 = load i32, ptr %22, align 4
  store i32 %23, ptr %21, align 4
  %24 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 0
  %25 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 1, i32 0
  %26 = load i32, ptr %25, align 4
  store i32 %26, ptr %24, align 4
  %27 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 1
  %28 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 1, i32 1
  %29 = load i32, ptr %28, align 4
  store i32 %29, ptr %27, align 4
  %30 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 2
  %31 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 1, i32 2
  %32 = load i32, ptr %31, align 4
  store i32 %32, ptr %30, align 4
  %33 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 3
  %34 = getelementptr [2 x [4 x i32]], ptr %arr2, i32 0, i32 1, i32 3
  %35 = load i32, ptr %34, align 4
  store i32 %35, ptr %33, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %36 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 0, i32 0
  store i32 10, ptr %36, align 4
  %37 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 0, i32 1
  store i32 10, ptr %37, align 4
  %38 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %40 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock
  %42 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %42, i1 false)
  %43 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %43, i1 false)
  %44 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  %46 = call ptr @itos(i32 %45)
  call void @print(ptr %46, i1 false)
  %47 = load ptr, ptr @comma, align 8
  call void @print(ptr %47, i1 false)
  %48 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 0, i32 1
  %49 = load i32, ptr %48, align 4
  %50 = call ptr @itos(i32 %49)
  call void @print(ptr %50, i1 false)
  %51 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %51, i1 false)
  %52 = load ptr, ptr @comma, align 8
  call void @print(ptr %52, i1 false)
  %53 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %53, i1 false)
  %54 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 1, i32 0
  %55 = load i32, ptr %54, align 4
  %56 = call ptr @itos(i32 %55)
  call void @print(ptr %56, i1 false)
  %57 = load ptr, ptr @comma, align 8
  call void @print(ptr %57, i1 false)
  %58 = getelementptr [2 x [2 x i32]], ptr %arr1, i32 0, i32 1, i32 1
  %59 = load i32, ptr %58, align 4
  %60 = call ptr @itos(i32 %59)
  call void @print(ptr %60, i1 false)
  %61 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %61, i1 false)
  %62 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %62, i1 false)
  %63 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %64 = icmp eq i32 %63, 0
  br i1 %64, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %65 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %66 = icmp eq i32 %65, 0
  br i1 %66, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %67 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %67, i1 false)
  %68 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %68, i1 false)
  %69 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 0
  %70 = load i32, ptr %69, align 4
  %71 = call ptr @itos(i32 %70)
  call void @print(ptr %71, i1 false)
  %72 = load ptr, ptr @comma, align 8
  call void @print(ptr %72, i1 false)
  %73 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 1
  %74 = load i32, ptr %73, align 4
  %75 = call ptr @itos(i32 %74)
  call void @print(ptr %75, i1 false)
  %76 = load ptr, ptr @comma, align 8
  call void @print(ptr %76, i1 false)
  %77 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 2
  %78 = load i32, ptr %77, align 4
  %79 = call ptr @itos(i32 %78)
  call void @print(ptr %79, i1 false)
  %80 = load ptr, ptr @comma, align 8
  call void @print(ptr %80, i1 false)
  %81 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 0, i32 3
  %82 = load i32, ptr %81, align 4
  %83 = call ptr @itos(i32 %82)
  call void @print(ptr %83, i1 false)
  %84 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %84, i1 false)
  %85 = load ptr, ptr @comma, align 8
  call void @print(ptr %85, i1 false)
  %86 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %86, i1 false)
  %87 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 0
  %88 = load i32, ptr %87, align 4
  %89 = call ptr @itos(i32 %88)
  call void @print(ptr %89, i1 false)
  %90 = load ptr, ptr @comma, align 8
  call void @print(ptr %90, i1 false)
  %91 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 1
  %92 = load i32, ptr %91, align 4
  %93 = call ptr @itos(i32 %92)
  call void @print(ptr %93, i1 false)
  %94 = load ptr, ptr @comma, align 8
  call void @print(ptr %94, i1 false)
  %95 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 2
  %96 = load i32, ptr %95, align 4
  %97 = call ptr @itos(i32 %96)
  call void @print(ptr %97, i1 false)
  %98 = load ptr, ptr @comma, align 8
  call void @print(ptr %98, i1 false)
  %99 = getelementptr [2 x [4 x i32]], ptr %arr22, i32 0, i32 1, i32 3
  %100 = load i32, ptr %99, align 4
  %101 = call ptr @itos(i32 %100)
  call void @print(ptr %101, i1 false)
  %102 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %102, i1 false)
  %103 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %103, i1 false)
  %104 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %105 = icmp eq i32 %104, 0
  br i1 %105, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

!0 = !{!"2:2:"}
!1 = !{!"2"}
!2 = !{!"2:4:"}
!3 = !{!"arr:0:Array:Integer:size:2:2:"}
!4 = !{!"arr2:1:Array:Integer:size:2:4:"}
