; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

%t1 = type { ptr, i32, i1, double, %parent }
%parent = type { i32, ptr, i1, double }

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
@x = global %t1 zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"fso\00", align 1
@z = global %t1 zeroinitializer
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [7 x i8] c"string\00", align 1
@7 = private unnamed_addr constant [5 x i8] c"fdso\00", align 1
@8 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = constant ptr @8
@9 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@10 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = constant ptr @10
@11 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'" = constant ptr @11
@12 = private unnamed_addr constant [3 x i8] c", \00", align 1
@" , " = constant ptr @12
@13 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@14 = private unnamed_addr constant [2 x i8] c"c\00", align 1
@15 = private unnamed_addr constant [2 x i8] c"d\00", align 1
@16 = private unnamed_addr constant [4 x i8] c"par\00", align 1
@17 = private unnamed_addr constant [3 x i8] c"pa\00", align 1
@18 = private unnamed_addr constant [3 x i8] c"pb\00", align 1
@19 = private unnamed_addr constant [3 x i8] c"pc\00", align 1
@20 = private unnamed_addr constant [3 x i8] c"pd\00", align 1
@21 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = constant ptr @21
@22 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@23 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@24 = private unnamed_addr constant [2 x i8] c"c\00", align 1
@25 = private unnamed_addr constant [2 x i8] c"d\00", align 1
@26 = private unnamed_addr constant [4 x i8] c"par\00", align 1
@27 = private unnamed_addr constant [3 x i8] c"pa\00", align 1
@28 = private unnamed_addr constant [3 x i8] c"pb\00", align 1
@29 = private unnamed_addr constant [3 x i8] c"pc\00", align 1
@30 = private unnamed_addr constant [3 x i8] c"pd\00", align 1
@31 = private unnamed_addr constant [4 x i8] c"llo\00", align 1
@32 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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
  store ptr @0, ptr @x, align 8
  store i32 0, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 1), align 4
  store i1 false, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 2), align 1
  store double 0.000000e+00, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 3), align 8
  store i32 0, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4), align 4
  store ptr @1, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4, i32 1), align 8
  store i1 false, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4, i32 2), align 1
  store double 0.000000e+00, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4, i32 3), align 8
  store ptr @2, ptr @x, align 8
  store i32 100, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 1), align 4
  store i1 true, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 2), align 1
  store double 2.000000e+00, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 3), align 8
  store i32 200, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4), align 4
  store ptr @3, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4, i32 1), align 8
  store i1 true, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4, i32 2), align 1
  store double 3.000000e+00, ptr getelementptr inbounds (%t1, ptr @x, i32 0, i32 4, i32 3), align 8
  store ptr @4, ptr @z, align 8
  store i32 0, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 1), align 4
  store i1 false, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 2), align 1
  store double 0.000000e+00, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 3), align 8
  store i32 0, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4), align 4
  store ptr @5, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 1), align 8
  store i1 false, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 2), align 1
  store double 0.000000e+00, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 3), align 8
  store ptr @6, ptr @z, align 8
  store i32 500, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 1), align 4
  store i1 true, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 2), align 1
  store double 5.000000e+00, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 3), align 8
  store i32 700, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4), align 4
  store ptr @7, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 1), align 8
  store i1 true, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 2), align 1
  store double 4.000000e+00, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 3), align 8
  %0 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %0, i1 false)
  call void @print(ptr @9, i1 false)
  %1 = load ptr, ptr @" : ", align 8
  call void @print(ptr %1, i1 false)
  %2 = load ptr, ptr @z, align 8
  %3 = load ptr, ptr @"'", align 8
  call void @print(ptr %3, i1 false)
  %4 = icmp ne ptr %2, null
  br i1 %4, label %End, label %IsNull

returnBlock:                                      ; preds = %Merge9
  ret i32 0

IsNull:                                           ; preds = %entry
  br label %Merge

End:                                              ; preds = %entry
  call void @print(ptr %2, i1 false)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %5 = load ptr, ptr @"'", align 8
  call void @print(ptr %5, i1 false)
  %6 = load ptr, ptr @" , ", align 8
  call void @print(ptr %6, i1 false)
  call void @print(ptr @13, i1 false)
  %7 = load ptr, ptr @" : ", align 8
  call void @print(ptr %7, i1 false)
  %8 = load i32, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 1), align 4
  %9 = call ptr @itos(i32 %8)
  call void @print(ptr %9, i1 false)
  %10 = load ptr, ptr @" , ", align 8
  call void @print(ptr %10, i1 false)
  call void @print(ptr @14, i1 false)
  %11 = load ptr, ptr @" : ", align 8
  call void @print(ptr %11, i1 false)
  %12 = load i1, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 2), align 1
  %13 = select i1 %12, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %13, i1 false)
  %14 = load ptr, ptr @" , ", align 8
  call void @print(ptr %14, i1 false)
  call void @print(ptr @15, i1 false)
  %15 = load ptr, ptr @" : ", align 8
  call void @print(ptr %15, i1 false)
  %16 = load double, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 3), align 8
  %17 = call ptr @dtos(double %16)
  call void @print(ptr %17, i1 false)
  %18 = load ptr, ptr @" , ", align 8
  call void @print(ptr %18, i1 false)
  call void @print(ptr @16, i1 false)
  %19 = load ptr, ptr @" : ", align 8
  call void @print(ptr %19, i1 false)
  %20 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %20, i1 false)
  call void @print(ptr @17, i1 false)
  %21 = load ptr, ptr @" : ", align 8
  call void @print(ptr %21, i1 false)
  %22 = load i32, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4), align 4
  %23 = call ptr @itos(i32 %22)
  call void @print(ptr %23, i1 false)
  %24 = load ptr, ptr @" , ", align 8
  call void @print(ptr %24, i1 false)
  call void @print(ptr @18, i1 false)
  %25 = load ptr, ptr @" : ", align 8
  call void @print(ptr %25, i1 false)
  %26 = load ptr, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 1), align 8
  %27 = load ptr, ptr @"'", align 8
  call void @print(ptr %27, i1 false)
  %28 = icmp ne ptr %26, null
  br i1 %28, label %End2, label %IsNull1

IsNull1:                                          ; preds = %Merge
  br label %Merge3

End2:                                             ; preds = %Merge
  call void @print(ptr %26, i1 false)
  br label %Merge3

Merge3:                                           ; preds = %End2, %IsNull1
  %29 = load ptr, ptr @"'", align 8
  call void @print(ptr %29, i1 false)
  %30 = load ptr, ptr @" , ", align 8
  call void @print(ptr %30, i1 false)
  call void @print(ptr @19, i1 false)
  %31 = load ptr, ptr @" : ", align 8
  call void @print(ptr %31, i1 false)
  %32 = load i1, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 2), align 1
  %33 = select i1 %32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %33, i1 false)
  %34 = load ptr, ptr @" , ", align 8
  call void @print(ptr %34, i1 false)
  call void @print(ptr @20, i1 false)
  %35 = load ptr, ptr @" : ", align 8
  call void @print(ptr %35, i1 false)
  %36 = load double, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 3), align 8
  %37 = call ptr @dtos(double %36)
  call void @print(ptr %37, i1 false)
  %38 = load ptr, ptr @"}", align 8
  call void @print(ptr %38, i1 false)
  %39 = load ptr, ptr @"}", align 8
  call void @print(ptr %39, i1 false)
  %40 = call ptr @get(ptr @x)
  %41 = load %t1, ptr %40, align 8
  store %t1 %41, ptr @z, align 8
  %42 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %42, i1 false)
  call void @print(ptr @22, i1 false)
  %43 = load ptr, ptr @" : ", align 8
  call void @print(ptr %43, i1 false)
  %44 = load ptr, ptr @z, align 8
  %45 = load ptr, ptr @"'", align 8
  call void @print(ptr %45, i1 false)
  %46 = icmp ne ptr %44, null
  br i1 %46, label %End5, label %IsNull4

IsNull4:                                          ; preds = %Merge3
  br label %Merge6

End5:                                             ; preds = %Merge3
  call void @print(ptr %44, i1 false)
  br label %Merge6

Merge6:                                           ; preds = %End5, %IsNull4
  %47 = load ptr, ptr @"'", align 8
  call void @print(ptr %47, i1 false)
  %48 = load ptr, ptr @" , ", align 8
  call void @print(ptr %48, i1 false)
  call void @print(ptr @23, i1 false)
  %49 = load ptr, ptr @" : ", align 8
  call void @print(ptr %49, i1 false)
  %50 = load i32, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 1), align 4
  %51 = call ptr @itos(i32 %50)
  call void @print(ptr %51, i1 false)
  %52 = load ptr, ptr @" , ", align 8
  call void @print(ptr %52, i1 false)
  call void @print(ptr @24, i1 false)
  %53 = load ptr, ptr @" : ", align 8
  call void @print(ptr %53, i1 false)
  %54 = load i1, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 2), align 1
  %55 = select i1 %54, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %55, i1 false)
  %56 = load ptr, ptr @" , ", align 8
  call void @print(ptr %56, i1 false)
  call void @print(ptr @25, i1 false)
  %57 = load ptr, ptr @" : ", align 8
  call void @print(ptr %57, i1 false)
  %58 = load double, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 3), align 8
  %59 = call ptr @dtos(double %58)
  call void @print(ptr %59, i1 false)
  %60 = load ptr, ptr @" , ", align 8
  call void @print(ptr %60, i1 false)
  call void @print(ptr @26, i1 false)
  %61 = load ptr, ptr @" : ", align 8
  call void @print(ptr %61, i1 false)
  %62 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %62, i1 false)
  call void @print(ptr @27, i1 false)
  %63 = load ptr, ptr @" : ", align 8
  call void @print(ptr %63, i1 false)
  %64 = load i32, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4), align 4
  %65 = call ptr @itos(i32 %64)
  call void @print(ptr %65, i1 false)
  %66 = load ptr, ptr @" , ", align 8
  call void @print(ptr %66, i1 false)
  call void @print(ptr @28, i1 false)
  %67 = load ptr, ptr @" : ", align 8
  call void @print(ptr %67, i1 false)
  %68 = load ptr, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 1), align 8
  %69 = load ptr, ptr @"'", align 8
  call void @print(ptr %69, i1 false)
  %70 = icmp ne ptr %68, null
  br i1 %70, label %End8, label %IsNull7

IsNull7:                                          ; preds = %Merge6
  br label %Merge9

End8:                                             ; preds = %Merge6
  call void @print(ptr %68, i1 false)
  br label %Merge9

Merge9:                                           ; preds = %End8, %IsNull7
  %71 = load ptr, ptr @"'", align 8
  call void @print(ptr %71, i1 false)
  %72 = load ptr, ptr @" , ", align 8
  call void @print(ptr %72, i1 false)
  call void @print(ptr @29, i1 false)
  %73 = load ptr, ptr @" : ", align 8
  call void @print(ptr %73, i1 false)
  %74 = load i1, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 2), align 1
  %75 = select i1 %74, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %75, i1 false)
  %76 = load ptr, ptr @" , ", align 8
  call void @print(ptr %76, i1 false)
  call void @print(ptr @30, i1 false)
  %77 = load ptr, ptr @" : ", align 8
  call void @print(ptr %77, i1 false)
  %78 = load double, ptr getelementptr inbounds (%t1, ptr @z, i32 0, i32 4, i32 3), align 8
  %79 = call ptr @dtos(double %78)
  call void @print(ptr %79, i1 false)
  %80 = load ptr, ptr @"}", align 8
  call void @print(ptr %80, i1 false)
  %81 = load ptr, ptr @"}", align 8
  call void @print(ptr %81, i1 false)
  br label %returnBlock
}

define ptr @get(ptr %0) !rt !0 {
entry:
  %y = alloca %t1, align 8
  %1 = getelementptr inbounds %t1, ptr %y, i32 0, i32 0
  %2 = getelementptr inbounds %t1, ptr %0, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %1, align 8
  %4 = getelementptr inbounds %t1, ptr %y, i32 0, i32 1
  %5 = getelementptr inbounds %t1, ptr %0, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  store i32 %6, ptr %4, align 4
  %7 = getelementptr inbounds %t1, ptr %y, i32 0, i32 2
  %8 = getelementptr inbounds %t1, ptr %0, i32 0, i32 2
  %9 = load i1, ptr %8, align 1
  store i1 %9, ptr %7, align 1
  %10 = getelementptr inbounds %t1, ptr %y, i32 0, i32 3
  %11 = getelementptr inbounds %t1, ptr %0, i32 0, i32 3
  %12 = load double, ptr %11, align 8
  store double %12, ptr %10, align 8
  %13 = getelementptr inbounds %t1, ptr %y, i32 0, i32 4
  %14 = getelementptr inbounds %t1, ptr %0, i32 0, i32 4
  %15 = getelementptr inbounds %parent, ptr %13, i32 0, i32 0
  %16 = getelementptr inbounds %parent, ptr %14, i32 0, i32 0
  %17 = load i32, ptr %16, align 4
  store i32 %17, ptr %15, align 4
  %18 = getelementptr inbounds %parent, ptr %13, i32 0, i32 1
  %19 = getelementptr inbounds %parent, ptr %14, i32 0, i32 1
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %18, align 8
  %21 = getelementptr inbounds %parent, ptr %13, i32 0, i32 2
  %22 = getelementptr inbounds %parent, ptr %14, i32 0, i32 2
  %23 = load i1, ptr %22, align 1
  store i1 %23, ptr %21, align 1
  %24 = getelementptr inbounds %parent, ptr %13, i32 0, i32 3
  %25 = getelementptr inbounds %parent, ptr %14, i32 0, i32 3
  %26 = load double, ptr %25, align 8
  store double %26, ptr %24, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %mergeBlock, %checkContinueBlock6, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret ptr @32

nestedBlock:                                      ; preds = %entry
  %27 = getelementptr inbounds %t1, ptr %y, i32 0, i32 4
  %28 = getelementptr inbounds %parent, ptr %27, i32 0, i32 0
  %29 = load i32, ptr %28, align 4
  store i32 545, ptr %28, align 4
  %30 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %32 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %34 = getelementptr inbounds %t1, ptr %y, i32 0, i32 4
  %35 = getelementptr inbounds %parent, ptr %34, i32 0, i32 1
  %36 = load ptr, ptr %35, align 8
  store ptr @31, ptr %35, align 8
  %37 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %39 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %41 = getelementptr inbounds %t1, ptr %y, i32 0, i32 4
  %42 = getelementptr inbounds %parent, ptr %41, i32 0, i32 2
  %43 = load i1, ptr %42, align 1
  store i1 true, ptr %42, align 1
  %44 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %46 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  br label %returnBlock

checkContinueBlock6:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock5
  ret ptr %y

mergeBlock:                                       ; No predecessors!
  %48 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock6, label %afterNestedBlock
}

!0 = !{!"get:rt:ob:t1"}
