; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"
target triple = "x86_64-pc-linux-gnu"

%type1 = type { ptr, i32, double, i1, ptr }

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
@a = global %type1 zeroinitializer
@0 = private unnamed_addr constant [9 x i8] c"Kushagra\00", align 1
@a.type1 = global %type1 zeroinitializer
@1 = private unnamed_addr constant [8 x i8] c"Rathore\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = constant ptr @2
@3 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@4 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = constant ptr @4
@5 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'" = constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c", \00", align 1
@" , " = constant ptr @6
@7 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@8 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@9 = private unnamed_addr constant [3 x i8] c"is\00", align 1
@10 = private unnamed_addr constant [6 x i8] c"type1\00", align 1
@11 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@12 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@13 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@14 = private unnamed_addr constant [3 x i8] c"is\00", align 1
@15 = private unnamed_addr constant [6 x i8] c"type1\00", align 1
@16 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = constant ptr @16
@17 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@x = global %type1 zeroinitializer
@x.type1 = global %type1 zeroinitializer
@18 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@19 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@20 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@21 = private unnamed_addr constant [3 x i8] c"is\00", align 1
@22 = private unnamed_addr constant [6 x i8] c"type1\00", align 1
@23 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@24 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@25 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@26 = private unnamed_addr constant [3 x i8] c"is\00", align 1
@27 = private unnamed_addr constant [6 x i8] c"type1\00", align 1
@28 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@29 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@30 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@31 = private unnamed_addr constant [3 x i8] c"is\00", align 1
@32 = private unnamed_addr constant [6 x i8] c"type1\00", align 1
@33 = private unnamed_addr constant [5 x i8] c"name\00", align 1
@34 = private unnamed_addr constant [4 x i8] c"age\00", align 1
@35 = private unnamed_addr constant [7 x i8] c"height\00", align 1
@36 = private unnamed_addr constant [3 x i8] c"is\00", align 1
@37 = private unnamed_addr constant [6 x i8] c"type1\00", align 1
@38 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

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
  store ptr null, ptr @a, align 8
  store i32 0, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 1), align 4
  store double 0.000000e+00, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 2), align 8
  store i1 false, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 3), align 1
  store ptr @0, ptr @a, align 8
  store i32 30, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 1), align 4
  store double 5.100000e+00, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 2), align 8
  store i1 false, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 3), align 1
  store ptr null, ptr @a.type1, align 8
  store i32 0, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 1), align 4
  store double 0.000000e+00, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 2), align 8
  store i1 false, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 3), align 1
  store ptr @1, ptr @a.type1, align 8
  store ptr @a.type1, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 4), align 8
  %0 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %0, i1 false)
  call void @print(ptr @3, i1 false)
  %1 = load ptr, ptr @" : ", align 8
  call void @print(ptr %1, i1 false)
  %2 = load ptr, ptr @a, align 8
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
  call void @print(ptr @7, i1 false)
  %7 = load ptr, ptr @" : ", align 8
  call void @print(ptr %7, i1 false)
  %8 = load i32, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 1), align 4
  %9 = call ptr @itos(i32 %8)
  call void @print(ptr %9, i1 false)
  %10 = load ptr, ptr @" , ", align 8
  call void @print(ptr %10, i1 false)
  call void @print(ptr @8, i1 false)
  %11 = load ptr, ptr @" : ", align 8
  call void @print(ptr %11, i1 false)
  %12 = load double, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 2), align 8
  %13 = call ptr @dtos(double %12)
  call void @print(ptr %13, i1 false)
  %14 = load ptr, ptr @" , ", align 8
  call void @print(ptr %14, i1 false)
  call void @print(ptr @9, i1 false)
  %15 = load ptr, ptr @" : ", align 8
  call void @print(ptr %15, i1 false)
  %16 = load i1, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 3), align 1
  %17 = select i1 %16, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %17, i1 false)
  %18 = load ptr, ptr @" , ", align 8
  call void @print(ptr %18, i1 false)
  call void @print(ptr @10, i1 false)
  %19 = load ptr, ptr @" : ", align 8
  call void @print(ptr %19, i1 false)
  %20 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %20, i1 false)
  call void @print(ptr @11, i1 false)
  %21 = load ptr, ptr @" : ", align 8
  call void @print(ptr %21, i1 false)
  %22 = load ptr, ptr @a.type1, align 8
  %23 = load ptr, ptr @"'", align 8
  call void @print(ptr %23, i1 false)
  %24 = icmp ne ptr %22, null
  br i1 %24, label %End2, label %IsNull1

IsNull1:                                          ; preds = %Merge
  br label %Merge3

End2:                                             ; preds = %Merge
  call void @print(ptr %22, i1 false)
  br label %Merge3

Merge3:                                           ; preds = %End2, %IsNull1
  %25 = load ptr, ptr @"'", align 8
  call void @print(ptr %25, i1 false)
  %26 = load ptr, ptr @" , ", align 8
  call void @print(ptr %26, i1 false)
  call void @print(ptr @12, i1 false)
  %27 = load ptr, ptr @" : ", align 8
  call void @print(ptr %27, i1 false)
  %28 = load i32, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 1), align 4
  %29 = call ptr @itos(i32 %28)
  call void @print(ptr %29, i1 false)
  %30 = load ptr, ptr @" , ", align 8
  call void @print(ptr %30, i1 false)
  call void @print(ptr @13, i1 false)
  %31 = load ptr, ptr @" : ", align 8
  call void @print(ptr %31, i1 false)
  %32 = load double, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 2), align 8
  %33 = call ptr @dtos(double %32)
  call void @print(ptr %33, i1 false)
  %34 = load ptr, ptr @" , ", align 8
  call void @print(ptr %34, i1 false)
  call void @print(ptr @14, i1 false)
  %35 = load ptr, ptr @" : ", align 8
  call void @print(ptr %35, i1 false)
  %36 = load i1, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 3), align 1
  %37 = select i1 %36, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %37, i1 false)
  %38 = load ptr, ptr @" , ", align 8
  call void @print(ptr %38, i1 false)
  call void @print(ptr @15, i1 false)
  %39 = load ptr, ptr @" : ", align 8
  call void @print(ptr %39, i1 false)
  %40 = load ptr, ptr @"}", align 8
  call void @print(ptr %40, i1 false)
  %41 = load ptr, ptr @"}", align 8
  call void @print(ptr %41, i1 false)
  call void @print(ptr @17, i1 false)
  store ptr null, ptr @x, align 8
  store i32 0, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 1), align 4
  store double 0.000000e+00, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 2), align 8
  store i1 false, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 3), align 1
  call void @pass(ptr @a)
  %42 = load ptr, ptr @a, align 8
  store ptr %42, ptr @x, align 8
  %43 = load i32, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 1), align 4
  store i32 %43, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 1), align 4
  %44 = load double, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 2), align 8
  store double %44, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 2), align 8
  %45 = load i1, ptr getelementptr inbounds (%type1, ptr @a, i32 0, i32 3), align 1
  store i1 %45, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 3), align 1
  %46 = load ptr, ptr @a.type1, align 8
  store ptr %46, ptr @x.type1, align 8
  %47 = load i32, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 1), align 4
  store i32 %47, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 1), align 4
  %48 = load double, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 2), align 8
  store double %48, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 2), align 8
  %49 = load i1, ptr getelementptr inbounds (%type1, ptr @a.type1, i32 0, i32 3), align 1
  store i1 %49, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 3), align 1
  %50 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %50, i1 false)
  call void @print(ptr @18, i1 false)
  %51 = load ptr, ptr @" : ", align 8
  call void @print(ptr %51, i1 false)
  %52 = load ptr, ptr @x, align 8
  %53 = load ptr, ptr @"'", align 8
  call void @print(ptr %53, i1 false)
  %54 = icmp ne ptr %52, null
  br i1 %54, label %End5, label %IsNull4

IsNull4:                                          ; preds = %Merge3
  br label %Merge6

End5:                                             ; preds = %Merge3
  call void @print(ptr %52, i1 false)
  br label %Merge6

Merge6:                                           ; preds = %End5, %IsNull4
  %55 = load ptr, ptr @"'", align 8
  call void @print(ptr %55, i1 false)
  %56 = load ptr, ptr @" , ", align 8
  call void @print(ptr %56, i1 false)
  call void @print(ptr @19, i1 false)
  %57 = load ptr, ptr @" : ", align 8
  call void @print(ptr %57, i1 false)
  %58 = load i32, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 1), align 4
  %59 = call ptr @itos(i32 %58)
  call void @print(ptr %59, i1 false)
  %60 = load ptr, ptr @" , ", align 8
  call void @print(ptr %60, i1 false)
  call void @print(ptr @20, i1 false)
  %61 = load ptr, ptr @" : ", align 8
  call void @print(ptr %61, i1 false)
  %62 = load double, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 2), align 8
  %63 = call ptr @dtos(double %62)
  call void @print(ptr %63, i1 false)
  %64 = load ptr, ptr @" , ", align 8
  call void @print(ptr %64, i1 false)
  call void @print(ptr @21, i1 false)
  %65 = load ptr, ptr @" : ", align 8
  call void @print(ptr %65, i1 false)
  %66 = load i1, ptr getelementptr inbounds (%type1, ptr @x, i32 0, i32 3), align 1
  %67 = select i1 %66, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %67, i1 false)
  %68 = load ptr, ptr @" , ", align 8
  call void @print(ptr %68, i1 false)
  call void @print(ptr @22, i1 false)
  %69 = load ptr, ptr @" : ", align 8
  call void @print(ptr %69, i1 false)
  %70 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %70, i1 false)
  call void @print(ptr @23, i1 false)
  %71 = load ptr, ptr @" : ", align 8
  call void @print(ptr %71, i1 false)
  %72 = load ptr, ptr @x.type1, align 8
  %73 = load ptr, ptr @"'", align 8
  call void @print(ptr %73, i1 false)
  %74 = icmp ne ptr %72, null
  br i1 %74, label %End8, label %IsNull7

IsNull7:                                          ; preds = %Merge6
  br label %Merge9

End8:                                             ; preds = %Merge6
  call void @print(ptr %72, i1 false)
  br label %Merge9

Merge9:                                           ; preds = %End8, %IsNull7
  %75 = load ptr, ptr @"'", align 8
  call void @print(ptr %75, i1 false)
  %76 = load ptr, ptr @" , ", align 8
  call void @print(ptr %76, i1 false)
  call void @print(ptr @24, i1 false)
  %77 = load ptr, ptr @" : ", align 8
  call void @print(ptr %77, i1 false)
  %78 = load i32, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 1), align 4
  %79 = call ptr @itos(i32 %78)
  call void @print(ptr %79, i1 false)
  %80 = load ptr, ptr @" , ", align 8
  call void @print(ptr %80, i1 false)
  call void @print(ptr @25, i1 false)
  %81 = load ptr, ptr @" : ", align 8
  call void @print(ptr %81, i1 false)
  %82 = load double, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 2), align 8
  %83 = call ptr @dtos(double %82)
  call void @print(ptr %83, i1 false)
  %84 = load ptr, ptr @" , ", align 8
  call void @print(ptr %84, i1 false)
  call void @print(ptr @26, i1 false)
  %85 = load ptr, ptr @" : ", align 8
  call void @print(ptr %85, i1 false)
  %86 = load i1, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 3), align 1
  %87 = select i1 %86, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %87, i1 false)
  %88 = load ptr, ptr @" , ", align 8
  call void @print(ptr %88, i1 false)
  call void @print(ptr @27, i1 false)
  %89 = load ptr, ptr @" : ", align 8
  call void @print(ptr %89, i1 false)
  %90 = load ptr, ptr @"}", align 8
  call void @print(ptr %90, i1 false)
  %91 = load ptr, ptr @"}", align 8
  call void @print(ptr %91, i1 false)
  br label %returnBlock
}

define void @pass(ptr %0) !rt !0 {
entry:
  %x = alloca %type1, align 8
  %1 = getelementptr %type1, ptr %x, i32 0, i32 0
  %2 = getelementptr %type1, ptr %0, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %1, align 8
  %4 = getelementptr %type1, ptr %x, i32 0, i32 1
  %5 = getelementptr %type1, ptr %0, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  store i32 %6, ptr %4, align 4
  %7 = getelementptr %type1, ptr %x, i32 0, i32 2
  %8 = getelementptr %type1, ptr %0, i32 0, i32 2
  %9 = load double, ptr %8, align 8
  store double %9, ptr %7, align 8
  %10 = getelementptr %type1, ptr %x, i32 0, i32 3
  %11 = getelementptr %type1, ptr %0, i32 0, i32 3
  %12 = load i1, ptr %11, align 1
  store i1 %12, ptr %10, align 1
  %13 = getelementptr %type1, ptr %x, i32 0, i32 4
  %14 = getelementptr %type1, ptr %0, i32 0, i32 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %Merge5, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %15, i1 false)
  call void @print(ptr @28, i1 false)
  %16 = load ptr, ptr @" : ", align 8
  call void @print(ptr %16, i1 false)
  %17 = getelementptr inbounds %type1, ptr %x, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = load ptr, ptr @"'", align 8
  call void @print(ptr %19, i1 false)
  %20 = icmp ne ptr %18, null
  br i1 %20, label %End, label %IsNull

checkContinueBlock:                               ; preds = %Merge5
  %21 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  call void @print(ptr @38, i1 false)
  %23 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock

IsNull:                                           ; preds = %nestedBlock
  br label %Merge

End:                                              ; preds = %nestedBlock
  call void @print(ptr %18, i1 false)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %25 = load ptr, ptr @"'", align 8
  call void @print(ptr %25, i1 false)
  %26 = load ptr, ptr @" , ", align 8
  call void @print(ptr %26, i1 false)
  call void @print(ptr @29, i1 false)
  %27 = load ptr, ptr @" : ", align 8
  call void @print(ptr %27, i1 false)
  %28 = getelementptr inbounds %type1, ptr %x, i32 0, i32 1
  %29 = load i32, ptr %28, align 4
  %30 = call ptr @itos(i32 %29)
  call void @print(ptr %30, i1 false)
  %31 = load ptr, ptr @" , ", align 8
  call void @print(ptr %31, i1 false)
  call void @print(ptr @30, i1 false)
  %32 = load ptr, ptr @" : ", align 8
  call void @print(ptr %32, i1 false)
  %33 = getelementptr inbounds %type1, ptr %x, i32 0, i32 2
  %34 = load double, ptr %33, align 8
  %35 = call ptr @dtos(double %34)
  call void @print(ptr %35, i1 false)
  %36 = load ptr, ptr @" , ", align 8
  call void @print(ptr %36, i1 false)
  call void @print(ptr @31, i1 false)
  %37 = load ptr, ptr @" : ", align 8
  call void @print(ptr %37, i1 false)
  %38 = getelementptr inbounds %type1, ptr %x, i32 0, i32 3
  %39 = load i1, ptr %38, align 1
  %40 = select i1 %39, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %40, i1 false)
  %41 = load ptr, ptr @" , ", align 8
  call void @print(ptr %41, i1 false)
  call void @print(ptr @32, i1 false)
  %42 = load ptr, ptr @" : ", align 8
  call void @print(ptr %42, i1 false)
  %43 = getelementptr inbounds %type1, ptr %x, i32 0, i32 4
  %44 = load ptr, ptr @"{ ", align 8
  call void @print(ptr %44, i1 false)
  call void @print(ptr @33, i1 false)
  %45 = load ptr, ptr @" : ", align 8
  call void @print(ptr %45, i1 false)
  %46 = load ptr, ptr @x.type1, align 8
  %47 = load ptr, ptr @"'", align 8
  call void @print(ptr %47, i1 false)
  %48 = icmp ne ptr %46, null
  br i1 %48, label %End4, label %IsNull3

IsNull3:                                          ; preds = %Merge
  br label %Merge5

End4:                                             ; preds = %Merge
  call void @print(ptr %46, i1 false)
  br label %Merge5

Merge5:                                           ; preds = %End4, %IsNull3
  %49 = load ptr, ptr @"'", align 8
  call void @print(ptr %49, i1 false)
  %50 = load ptr, ptr @" , ", align 8
  call void @print(ptr %50, i1 false)
  call void @print(ptr @34, i1 false)
  %51 = load ptr, ptr @" : ", align 8
  call void @print(ptr %51, i1 false)
  %52 = load i32, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 1), align 4
  %53 = call ptr @itos(i32 %52)
  call void @print(ptr %53, i1 false)
  %54 = load ptr, ptr @" , ", align 8
  call void @print(ptr %54, i1 false)
  call void @print(ptr @35, i1 false)
  %55 = load ptr, ptr @" : ", align 8
  call void @print(ptr %55, i1 false)
  %56 = load double, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 2), align 8
  %57 = call ptr @dtos(double %56)
  call void @print(ptr %57, i1 false)
  %58 = load ptr, ptr @" , ", align 8
  call void @print(ptr %58, i1 false)
  call void @print(ptr @36, i1 false)
  %59 = load ptr, ptr @" : ", align 8
  call void @print(ptr %59, i1 false)
  %60 = load i1, ptr getelementptr inbounds (%type1, ptr @x.type1, i32 0, i32 3), align 1
  %61 = select i1 %60, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_TRUE", ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_GLOBAL_FALSE"
  call void @print(ptr %61, i1 false)
  %62 = load ptr, ptr @" , ", align 8
  call void @print(ptr %62, i1 false)
  call void @print(ptr @37, i1 false)
  %63 = load ptr, ptr @" : ", align 8
  call void @print(ptr %63, i1 false)
  %64 = load ptr, ptr @"}", align 8
  call void @print(ptr %64, i1 false)
  %65 = load ptr, ptr @"}", align 8
  call void @print(ptr %65, i1 false)
  %66 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"pass:rt:pr:27"}
