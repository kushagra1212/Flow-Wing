; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

%my2 = type { ptr, i32, ptr }
%obj = type { double, double, i1 }

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
@0 = private unnamed_addr constant [9 x i8] c"Kushagra\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = constant ptr @1
@2 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@3 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = constant ptr @3
@4 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'" = constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c", \00", align 1
@" , " = constant ptr @5
@6 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"obj\00", align 1
@8 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@9 = private unnamed_addr constant [7 x i8] c"weight\00", align 1
@10 = private unnamed_addr constant [11 x i8] c"isEmployed\00", align 1
@11 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = constant ptr @11
@12 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@13 = private unnamed_addr constant [7 x i8] c"weight\00", align 1
@14 = private unnamed_addr constant [11 x i8] c"isEmployed\00", align 1

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

afterNestedBlock:                                 ; preds = %Merge, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
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
  %a = alloca %my2, align 8, !a !0
  %8 = getelementptr %my2, ptr %a, i32 0, i32 0
  store ptr null, ptr %8, align 8
  %9 = getelementptr %my2, ptr %a, i32 0, i32 1
  store i32 0, ptr %9, align 4
  %10 = getelementptr %my2, ptr %a, i32 0, i32 0
  store ptr @0, ptr %10, align 8
  %11 = getelementptr %my2, ptr %a, i32 0, i32 1
  store i32 30, ptr %11, align 4
  %12 = getelementptr %my2, ptr %a, i32 0, i32 2
  %a.obj = alloca %obj, align 8, !a.obj !1
  %13 = getelementptr %obj, ptr %a.obj, i32 0, i32 0
  store double 0.000000e+00, ptr %13, align 8
  %14 = getelementptr %obj, ptr %a.obj, i32 0, i32 1
  store double 0.000000e+00, ptr %14, align 8
  %15 = getelementptr %obj, ptr %a.obj, i32 0, i32 2
  store i1 false, ptr %15, align 1
  %16 = getelementptr %obj, ptr %a.obj, i32 0, i32 0
  store double 5.100000e+00, ptr %16, align 8
  %17 = getelementptr %obj, ptr %a.obj, i32 0, i32 1
  store double 5.050000e+01, ptr %17, align 8
  %18 = getelementptr %obj, ptr %a.obj, i32 0, i32 2
  store i1 true, ptr %18, align 1
  store ptr %a.obj, ptr %12, align 8
  %19 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %21 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %23 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %23, i1 false)
  call void @print(ptr @2, i1 false)
  %24 = load ptr, ptr @" : ", align 8
  call void @print(ptr %24, i1 false)
  %25 = getelementptr inbounds %my2, ptr %a, i32 0, i32 0
  %26 = load ptr, ptr %25, align 8
  %27 = load ptr, ptr @"'", align 8
  call void @print(ptr %27, i1 false)
  %28 = icmp ne ptr %26, null
  br i1 %28, label %End, label %IsNull

checkContinueBlock6:                              ; preds = %Merge
  %29 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %31 = getelementptr inbounds %my2, ptr %a, i32 0, i32 2
  %32 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %32, i1 false)
  call void @print(ptr @12, i1 false)
  %33 = load ptr, ptr @" : ", align 8
  call void @print(ptr %33, i1 false)
  %34 = getelementptr inbounds %obj, ptr %a.obj, i32 0, i32 0
  %35 = load double, ptr %34, align 8
  %36 = call ptr @dtos(double %35)
  call void @print(ptr %36, i1 false)
  %37 = load ptr, ptr @" , ", align 8
  call void @print(ptr %37, i1 false)
  call void @print(ptr @13, i1 false)
  %38 = load ptr, ptr @" : ", align 8
  call void @print(ptr %38, i1 false)
  %39 = getelementptr inbounds %obj, ptr %a.obj, i32 0, i32 1
  %40 = load double, ptr %39, align 8
  %41 = call ptr @dtos(double %40)
  call void @print(ptr %41, i1 false)
  %42 = load ptr, ptr @" , ", align 8
  call void @print(ptr %42, i1 false)
  call void @print(ptr @14, i1 false)
  %43 = load ptr, ptr @" : ", align 8
  call void @print(ptr %43, i1 false)
  %44 = getelementptr inbounds %obj, ptr %a.obj, i32 0, i32 2
  %45 = load i1, ptr %44, align 1
  %46 = select i1 %45, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %46, i1 false)
  %47 = load ptr, ptr @"}", align 8
  call void @print(ptr %47, i1 false)
  %48 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock

IsNull:                                           ; preds = %nestedBlock5
  br label %Merge

End:                                              ; preds = %nestedBlock5
  call void @print(ptr %26, i1 false)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %50 = load ptr, ptr @"'", align 8
  call void @print(ptr %50, i1 false)
  %51 = load ptr, ptr @" , ", align 8
  call void @print(ptr %51, i1 false)
  call void @print(ptr @6, i1 false)
  %52 = load ptr, ptr @" : ", align 8
  call void @print(ptr %52, i1 false)
  %53 = getelementptr inbounds %my2, ptr %a, i32 0, i32 1
  %54 = load i32, ptr %53, align 4
  %55 = call ptr @itos(i32 %54)
  call void @print(ptr %55, i1 false)
  %56 = load ptr, ptr @" , ", align 8
  call void @print(ptr %56, i1 false)
  call void @print(ptr @7, i1 false)
  %57 = load ptr, ptr @" : ", align 8
  call void @print(ptr %57, i1 false)
  %58 = getelementptr inbounds %my2, ptr %a, i32 0, i32 2
  %59 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %59, i1 false)
  call void @print(ptr @8, i1 false)
  %60 = load ptr, ptr @" : ", align 8
  call void @print(ptr %60, i1 false)
  %61 = getelementptr inbounds %obj, ptr %a.obj, i32 0, i32 0
  %62 = load double, ptr %61, align 8
  %63 = call ptr @dtos(double %62)
  call void @print(ptr %63, i1 false)
  %64 = load ptr, ptr @" , ", align 8
  call void @print(ptr %64, i1 false)
  call void @print(ptr @9, i1 false)
  %65 = load ptr, ptr @" : ", align 8
  call void @print(ptr %65, i1 false)
  %66 = getelementptr inbounds %obj, ptr %a.obj, i32 0, i32 1
  %67 = load double, ptr %66, align 8
  %68 = call ptr @dtos(double %67)
  call void @print(ptr %68, i1 false)
  %69 = load ptr, ptr @" , ", align 8
  call void @print(ptr %69, i1 false)
  call void @print(ptr @10, i1 false)
  %70 = load ptr, ptr @" : ", align 8
  call void @print(ptr %70, i1 false)
  %71 = getelementptr inbounds %obj, ptr %a.obj, i32 0, i32 2
  %72 = load i1, ptr %71, align 1
  %73 = select i1 %72, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %73, i1 false)
  %74 = load ptr, ptr @"}", align 8
  call void @print(ptr %74, i1 false)
  %75 = load ptr, ptr @"}", align 8
  call void @print(ptr %75, i1 false)
  %76 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %77 = icmp eq i32 %76, 0
  br i1 %77, label %checkContinueBlock6, label %afterNestedBlock
}

!0 = !{!"my2"}
!1 = !{!"obj"}
