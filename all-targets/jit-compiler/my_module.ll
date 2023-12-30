; ModuleID = '../../../src/IR/BuiltinIRs/built_in_module.ll'
source_filename = "built_in_module"

%DynamicType = type { i32, double, i1, ptr }

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
@y = global %DynamicType zeroinitializer
@0 = private unnamed_addr constant [638 x i8] c"\0A\1B[33m1| \1B[0m\1B[0mvar y = 8\0A\1B[0m\1B[33m2| \1B[0m\1B[0m{\0A\1B[0m\1B[33m3| \1B[0m\1B[0m    var x:int[10] = [1,2,3,4,5,5]\0A\1B[0m\1B[33m4| \1B[0m\1B[0m    for(var i = 0 to 10:y){\0A\1B[0m\1B[33m5| \1B[0m\1B[31m\1B[1m        print(x[i])\0A\1B[0m\1B[32m\1B[1m                 \0A   ~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m6| \1B[0m\1B[0m        print(\22\\n\22)\0A\1B[0m\1B[33m7| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m8| \1B[0m\1B[0m    x = [10 fill 10]\0A\1B[0m\1B[33m9| \1B[0m\1B[0m    print(x)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 5:17\1B[31m \22Index out of bounds of 'x' in index expression, index value should be between 0 and 10\22\1B[0m\0A\1B[33mLocation: /jit-compiler-dev/all-targets/jit-compiler/jit-compiler-build/../../dir/index.fg\0A\1B[0m\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [672 x i8] c"\0A\1B[33m4| \1B[0m\1B[0m    for(var i = 0 to 10:y){\0A\1B[0m\1B[33m5| \1B[0m\1B[0m        print(x[i])\0A\1B[0m\1B[33m6| \1B[0m\1B[0m        print(\22\\n\22)\0A\1B[0m\1B[33m7| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m8| \1B[0m\1B[31m\1B[1m    x = [10 fill 10]\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m9| \1B[0m\1B[0m    print(x)\0A\1B[0m\1B[33m10| \1B[0m\1B[0m    y = y + 8\0A\1B[0m\1B[33m11| \1B[0m\1B[0m    x = [y,y]\0A\1B[0m\1B[33m12| \1B[0m\1B[0m    print(x)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 8:10\1B[31m \22Element to fill is out of bound.  Size to fill must be less than to the actual size of the container and greater than or equal to zero:x\22\1B[0m\0A\1B[33mLocation: /jit-compiler-dev/all-targets/jit-compiler/jit-compiler-build/../../dir/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket = constant ptr @3
@4 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma = constant ptr @4
@5 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket = constant ptr @5
@6 = private unnamed_addr constant [653 x i8] c"\0A\1B[33m10| \1B[0m\1B[0m    y = y + 8\0A\1B[0m\1B[33m11| \1B[0m\1B[0m    x = [y,y]\0A\1B[0m\1B[33m12| \1B[0m\1B[0m    print(x)\0A\1B[0m\1B[33m13| \1B[0m\1B[0m    y = y - 6\0A\1B[0m\1B[33m14| \1B[0m\1B[31m\1B[1m    x = [10 fill y]\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m15| \1B[0m\1B[0m    print(x)\0A\1B[0m\1B[33m16| \1B[0m\1B[0m}\0A\1B[0m\1B[33m17| \1B[0m\1B[0m\0A\1B[0m\1B[33m18| \1B[0m\1B[0m/#var x:int[5][5] = [3 fill 10]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 14:10\1B[31m \22Element to fill is out of bound.  Size to fill must be less than to the actual size of the container and greater than or equal to zero:x\22\1B[0m\0A\1B[33mLocation: /jit-compiler-dev/all-targets/jit-compiler/jit-compiler-build/../../dir/index.fg\0A\1B[0m\00", align 1

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
  store i32 8, ptr @y, align 4
  br label %nestedBlock

returnBlock:                                      ; preds = %afterNestedBlock
  ret i32 0

afterNestedBlock:                                 ; preds = %"FillExpr::CHECK::merge27", %"FillExpr::CHECK::merge", %end_block25, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %checkContinueBlock2, %checkContinueBlock, %nestedBlock
  br label %returnBlock

nestedBlock:                                      ; preds = %entry
  %x = alloca [10 x i32], align 4, !I !0, !ET !1
  %0 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  store i32 0, ptr %0, align 4
  %1 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  store i32 0, ptr %1, align 4
  %2 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  store i32 0, ptr %2, align 4
  %3 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  store i32 0, ptr %3, align 4
  %4 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  store i32 0, ptr %4, align 4
  %5 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  store i32 0, ptr %5, align 4
  %6 = getelementptr [10 x i32], ptr %x, i32 0, i32 6
  store i32 0, ptr %6, align 4
  %7 = getelementptr [10 x i32], ptr %x, i32 0, i32 7
  store i32 0, ptr %7, align 4
  %8 = getelementptr [10 x i32], ptr %x, i32 0, i32 8
  store i32 0, ptr %8, align 4
  %9 = getelementptr [10 x i32], ptr %x, i32 0, i32 9
  store i32 0, ptr %9, align 4
  %10 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  store i32 1, ptr %10, align 4
  %11 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  store i32 2, ptr %11, align 4
  %12 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  store i32 3, ptr %12, align 4
  %13 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  store i32 4, ptr %13, align 4
  %14 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  store i32 5, ptr %14, align 4
  %15 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  store i32 5, ptr %15, align 4
  %16 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %18 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %20 = load i32, ptr @y, align 4
  %i = alloca %DynamicType, align 8
  %21 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %21, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock2:                              ; preds = %end_block25
  %22 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  br i1 false, label %"FillExpr::CHECK::outOfBound", label %"FillExpr::CHECK::merge"

checkContinueBlock4:                              ; preds = %"FillExpr::CHECK::merge"
  %24 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %26 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %26, i1 false)
  %27 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  %28 = load i32, ptr %27, align 4
  %29 = call ptr @itos(i32 %28)
  call void @print(ptr %29, i1 false)
  %30 = load ptr, ptr @comma, align 8
  call void @print(ptr %30, i1 false)
  %31 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  %32 = load i32, ptr %31, align 4
  %33 = call ptr @itos(i32 %32)
  call void @print(ptr %33, i1 false)
  %34 = load ptr, ptr @comma, align 8
  call void @print(ptr %34, i1 false)
  %35 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  %36 = load i32, ptr %35, align 4
  %37 = call ptr @itos(i32 %36)
  call void @print(ptr %37, i1 false)
  %38 = load ptr, ptr @comma, align 8
  call void @print(ptr %38, i1 false)
  %39 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  %40 = load i32, ptr %39, align 4
  %41 = call ptr @itos(i32 %40)
  call void @print(ptr %41, i1 false)
  %42 = load ptr, ptr @comma, align 8
  call void @print(ptr %42, i1 false)
  %43 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  %44 = load i32, ptr %43, align 4
  %45 = call ptr @itos(i32 %44)
  call void @print(ptr %45, i1 false)
  %46 = load ptr, ptr @comma, align 8
  call void @print(ptr %46, i1 false)
  %47 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  %48 = load i32, ptr %47, align 4
  %49 = call ptr @itos(i32 %48)
  call void @print(ptr %49, i1 false)
  %50 = load ptr, ptr @comma, align 8
  call void @print(ptr %50, i1 false)
  %51 = getelementptr [10 x i32], ptr %x, i32 0, i32 6
  %52 = load i32, ptr %51, align 4
  %53 = call ptr @itos(i32 %52)
  call void @print(ptr %53, i1 false)
  %54 = load ptr, ptr @comma, align 8
  call void @print(ptr %54, i1 false)
  %55 = getelementptr [10 x i32], ptr %x, i32 0, i32 7
  %56 = load i32, ptr %55, align 4
  %57 = call ptr @itos(i32 %56)
  call void @print(ptr %57, i1 false)
  %58 = load ptr, ptr @comma, align 8
  call void @print(ptr %58, i1 false)
  %59 = getelementptr [10 x i32], ptr %x, i32 0, i32 8
  %60 = load i32, ptr %59, align 4
  %61 = call ptr @itos(i32 %60)
  call void @print(ptr %61, i1 false)
  %62 = load ptr, ptr @comma, align 8
  call void @print(ptr %62, i1 false)
  %63 = getelementptr [10 x i32], ptr %x, i32 0, i32 9
  %64 = load i32, ptr %63, align 4
  %65 = call ptr @itos(i32 %64)
  call void @print(ptr %65, i1 false)
  %66 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %66, i1 false)
  %67 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %69 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %71 = load i32, ptr @y, align 4
  %72 = add i32 %71, 8
  store i32 %72, ptr @y, align 4
  %73 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %74 = icmp eq i32 %73, 0
  br i1 %74, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %75 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %77 = load i32, ptr @y, align 4
  %78 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  store i32 %77, ptr %78, align 4
  %79 = load i32, ptr @y, align 4
  %80 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  store i32 %79, ptr %80, align 4
  %81 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %83 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %85 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %85, i1 false)
  %86 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  %87 = load i32, ptr %86, align 4
  %88 = call ptr @itos(i32 %87)
  call void @print(ptr %88, i1 false)
  %89 = load ptr, ptr @comma, align 8
  call void @print(ptr %89, i1 false)
  %90 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  %91 = load i32, ptr %90, align 4
  %92 = call ptr @itos(i32 %91)
  call void @print(ptr %92, i1 false)
  %93 = load ptr, ptr @comma, align 8
  call void @print(ptr %93, i1 false)
  %94 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  %95 = load i32, ptr %94, align 4
  %96 = call ptr @itos(i32 %95)
  call void @print(ptr %96, i1 false)
  %97 = load ptr, ptr @comma, align 8
  call void @print(ptr %97, i1 false)
  %98 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  %99 = load i32, ptr %98, align 4
  %100 = call ptr @itos(i32 %99)
  call void @print(ptr %100, i1 false)
  %101 = load ptr, ptr @comma, align 8
  call void @print(ptr %101, i1 false)
  %102 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  %103 = load i32, ptr %102, align 4
  %104 = call ptr @itos(i32 %103)
  call void @print(ptr %104, i1 false)
  %105 = load ptr, ptr @comma, align 8
  call void @print(ptr %105, i1 false)
  %106 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  %107 = load i32, ptr %106, align 4
  %108 = call ptr @itos(i32 %107)
  call void @print(ptr %108, i1 false)
  %109 = load ptr, ptr @comma, align 8
  call void @print(ptr %109, i1 false)
  %110 = getelementptr [10 x i32], ptr %x, i32 0, i32 6
  %111 = load i32, ptr %110, align 4
  %112 = call ptr @itos(i32 %111)
  call void @print(ptr %112, i1 false)
  %113 = load ptr, ptr @comma, align 8
  call void @print(ptr %113, i1 false)
  %114 = getelementptr [10 x i32], ptr %x, i32 0, i32 7
  %115 = load i32, ptr %114, align 4
  %116 = call ptr @itos(i32 %115)
  call void @print(ptr %116, i1 false)
  %117 = load ptr, ptr @comma, align 8
  call void @print(ptr %117, i1 false)
  %118 = getelementptr [10 x i32], ptr %x, i32 0, i32 8
  %119 = load i32, ptr %118, align 4
  %120 = call ptr @itos(i32 %119)
  call void @print(ptr %120, i1 false)
  %121 = load ptr, ptr @comma, align 8
  call void @print(ptr %121, i1 false)
  %122 = getelementptr [10 x i32], ptr %x, i32 0, i32 9
  %123 = load i32, ptr %122, align 4
  %124 = call ptr @itos(i32 %123)
  call void @print(ptr %124, i1 false)
  %125 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %125, i1 false)
  %126 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %127 = icmp eq i32 %126, 0
  br i1 %127, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %128 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %129 = icmp eq i32 %128, 0
  br i1 %129, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %130 = load i32, ptr @y, align 4
  %131 = sub i32 %130, 6
  store i32 %131, ptr @y, align 4
  %132 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %133 = icmp eq i32 %132, 0
  br i1 %133, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %134 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %135 = icmp eq i32 %134, 0
  br i1 %135, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  br i1 false, label %"FillExpr::CHECK::outOfBound26", label %"FillExpr::CHECK::merge27"

checkContinueBlock16:                             ; preds = %"FillExpr::CHECK::merge27"
  %136 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %137 = icmp eq i32 %136, 0
  br i1 %137, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %138 = load ptr, ptr @openBracket, align 8
  call void @print(ptr %138, i1 false)
  %139 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  %140 = load i32, ptr %139, align 4
  %141 = call ptr @itos(i32 %140)
  call void @print(ptr %141, i1 false)
  %142 = load ptr, ptr @comma, align 8
  call void @print(ptr %142, i1 false)
  %143 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  %144 = load i32, ptr %143, align 4
  %145 = call ptr @itos(i32 %144)
  call void @print(ptr %145, i1 false)
  %146 = load ptr, ptr @comma, align 8
  call void @print(ptr %146, i1 false)
  %147 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  %148 = load i32, ptr %147, align 4
  %149 = call ptr @itos(i32 %148)
  call void @print(ptr %149, i1 false)
  %150 = load ptr, ptr @comma, align 8
  call void @print(ptr %150, i1 false)
  %151 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  %152 = load i32, ptr %151, align 4
  %153 = call ptr @itos(i32 %152)
  call void @print(ptr %153, i1 false)
  %154 = load ptr, ptr @comma, align 8
  call void @print(ptr %154, i1 false)
  %155 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  %156 = load i32, ptr %155, align 4
  %157 = call ptr @itos(i32 %156)
  call void @print(ptr %157, i1 false)
  %158 = load ptr, ptr @comma, align 8
  call void @print(ptr %158, i1 false)
  %159 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  %160 = load i32, ptr %159, align 4
  %161 = call ptr @itos(i32 %160)
  call void @print(ptr %161, i1 false)
  %162 = load ptr, ptr @comma, align 8
  call void @print(ptr %162, i1 false)
  %163 = getelementptr [10 x i32], ptr %x, i32 0, i32 6
  %164 = load i32, ptr %163, align 4
  %165 = call ptr @itos(i32 %164)
  call void @print(ptr %165, i1 false)
  %166 = load ptr, ptr @comma, align 8
  call void @print(ptr %166, i1 false)
  %167 = getelementptr [10 x i32], ptr %x, i32 0, i32 7
  %168 = load i32, ptr %167, align 4
  %169 = call ptr @itos(i32 %168)
  call void @print(ptr %169, i1 false)
  %170 = load ptr, ptr @comma, align 8
  call void @print(ptr %170, i1 false)
  %171 = getelementptr [10 x i32], ptr %x, i32 0, i32 8
  %172 = load i32, ptr %171, align 4
  %173 = call ptr @itos(i32 %172)
  call void @print(ptr %173, i1 false)
  %174 = load ptr, ptr @comma, align 8
  call void @print(ptr %174, i1 false)
  %175 = getelementptr [10 x i32], ptr %x, i32 0, i32 9
  %176 = load i32, ptr %175, align 4
  %177 = call ptr @itos(i32 %176)
  call void @print(ptr %177, i1 false)
  %178 = load ptr, ptr @closeBracket, align 8
  call void @print(ptr %178, i1 false)
  %179 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %180 = icmp eq i32 %179, 0
  br i1 %180, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock19, %nestedBlock1
  %181 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %182 = icmp eq i32 %181, 0
  br i1 %182, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock20

"ForLoop::afterLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock", %"ForLoop::breakLoop"
  %183 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %184 = icmp eq i32 %183, 0
  br i1 %184, label %end_block25, label %decrement_block24

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %185 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %187 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %188 = sub i32 %187, 1
  store i32 %188, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %189 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %190 = load i32, ptr %189, align 4
  %191 = icmp slt i32 %20, 0
  br i1 %191, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %192 = icmp sge i32 %190, 10
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %193 = icmp sle i32 %190, 10
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %194 = phi i1 [ %192, %"ForLoop::Conditon::trueBlock" ], [ %193, %"ForLoop::Conditon::falseBlock" ]
  br i1 %194, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock19:                               ; preds = %"GlobalIndexExpr::merge", %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21
  %195 = add i32 %190, %20
  store i32 %195, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock20:                                    ; preds = %"ForLoop::loopBody"
  %196 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %197 = load i32, ptr %196, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %197, 10
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %197, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock21:                             ; preds = %"GlobalIndexExpr::merge"
  %198 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_CONTINUE_COUNT", align 4
  %199 = icmp eq i32 %198, 0
  br i1 %199, label %nestedBlock22, label %afterNestedBlock19

nestedBlock22:                                    ; preds = %checkContinueBlock21
  call void @print(ptr @1, i1 false)
  %200 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %201 = icmp eq i32 %200, 0
  br i1 %201, label %checkContinueBlock23, label %afterNestedBlock19

checkContinueBlock23:                             ; preds = %nestedBlock22
  br label %afterNestedBlock19

"GlobalIndexExpr::then":                          ; preds = %nestedBlock20
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock20
  call void @raise_exception(ptr @0)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %202 = getelementptr [10 x i32], ptr %x, i32 0, i32 %197
  %203 = load i32, ptr %202, align 4
  %204 = call ptr @itos(i32 %203)
  call void @print(ptr %204, i1 false)
  %205 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %206 = icmp eq i32 %205, 0
  br i1 %206, label %checkContinueBlock21, label %afterNestedBlock19

decrement_block24:                                ; preds = %"ForLoop::afterLoop"
  %207 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %208 = sub i32 %207, 1
  store i32 %208, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  br label %end_block25

end_block25:                                      ; preds = %decrement_block24, %"ForLoop::afterLoop"
  %209 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %210 = icmp eq i32 %209, 0
  br i1 %210, label %checkContinueBlock2, label %afterNestedBlock

"FillExpr::CHECK::outOfBound":                    ; preds = %nestedBlock3
  call void @raise_exception(ptr @2)
  br label %"FillExpr::CHECK::merge"

"FillExpr::CHECK::merge":                         ; preds = %"FillExpr::CHECK::outOfBound", %nestedBlock3
  %211 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  store i32 10, ptr %211, align 4
  %212 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  store i32 10, ptr %212, align 4
  %213 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  store i32 10, ptr %213, align 4
  %214 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  store i32 10, ptr %214, align 4
  %215 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  store i32 10, ptr %215, align 4
  %216 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  store i32 10, ptr %216, align 4
  %217 = getelementptr [10 x i32], ptr %x, i32 0, i32 6
  store i32 10, ptr %217, align 4
  %218 = getelementptr [10 x i32], ptr %x, i32 0, i32 7
  store i32 10, ptr %218, align 4
  %219 = getelementptr [10 x i32], ptr %x, i32 0, i32 8
  store i32 10, ptr %219, align 4
  %220 = getelementptr [10 x i32], ptr %x, i32 0, i32 9
  store i32 10, ptr %220, align 4
  %221 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %222 = icmp eq i32 %221, 0
  br i1 %222, label %checkContinueBlock4, label %afterNestedBlock

"FillExpr::CHECK::outOfBound26":                  ; preds = %nestedBlock15
  call void @raise_exception(ptr @6)
  br label %"FillExpr::CHECK::merge27"

"FillExpr::CHECK::merge27":                       ; preds = %"FillExpr::CHECK::outOfBound26", %nestedBlock15
  %223 = load i32, ptr @y, align 4
  %224 = getelementptr [10 x i32], ptr %x, i32 0, i32 0
  store i32 %223, ptr %224, align 4
  %225 = getelementptr [10 x i32], ptr %x, i32 0, i32 1
  store i32 %223, ptr %225, align 4
  %226 = getelementptr [10 x i32], ptr %x, i32 0, i32 2
  store i32 %223, ptr %226, align 4
  %227 = getelementptr [10 x i32], ptr %x, i32 0, i32 3
  store i32 %223, ptr %227, align 4
  %228 = getelementptr [10 x i32], ptr %x, i32 0, i32 4
  store i32 %223, ptr %228, align 4
  %229 = getelementptr [10 x i32], ptr %x, i32 0, i32 5
  store i32 %223, ptr %229, align 4
  %230 = getelementptr [10 x i32], ptr %x, i32 0, i32 6
  store i32 %223, ptr %230, align 4
  %231 = getelementptr [10 x i32], ptr %x, i32 0, i32 7
  store i32 %223, ptr %231, align 4
  %232 = getelementptr [10 x i32], ptr %x, i32 0, i32 8
  store i32 %223, ptr %232, align 4
  %233 = getelementptr [10 x i32], ptr %x, i32 0, i32 9
  store i32 %223, ptr %233, align 4
  %234 = load i32, ptr @"____##FLOWWING_GLOBAL_ENTRY_POINT____##_FLOWWING_BREAK_COUNT", align 4
  %235 = icmp eq i32 %234, 0
  br i1 %235, label %checkContinueBlock16, label %afterNestedBlock
}

!0 = !{!"10:"}
!1 = !{!"2"}
