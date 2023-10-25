; ModuleID = 'Elang'
source_filename = "Elang"

@formatStrprintfnewline = global [4 x i8] c"%s\0A\00"
@formatStrprintf = global [3 x i8] c"%s\00"
@intFormat = global [3 x i8] c"%d\00"
@doubleFormat = global [5 x i8] c"%.6f\00"
@formatStrscanf = global [10 x i8] c"%1000000s\00", align 1
@ELANG_GLOBAL_TRUE = global [5 x i8] c"true\00"
@ELANG_GLOBAL_FALSE = global [6 x i8] c"false\00"
@ELANG_GLOBAL_NULL = global i8* null
@ELANG_BREAK_COUNT = global i32 0
@ELANG_CONTINUE_COUNT = global i32 0
@ELANG_GLOBAL_ZERO = global i32 0
@ELANG_GLOBAL_ERROR_COUNT = global i32 0
@HELLO_WORLD = global [14 x i8] c"Hello, World!\00"


define void @print(i8* %0, i1 %1) {
entry:
  br i1 %1, label %newline, label %withoutnewline

exit:                                             ; preds = %newline, %withoutnewline
  ret void

withoutnewline:                                   ; preds = %entry
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @formatStrprintf, i32 0, i32 0), i8* %0)
  br label %exit

newline:                                          ; preds = %entry
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @formatStrprintfnewline, i32 0, i32 0), i8* %0)
  br label %exit
}

declare i32 @printf(i8*, ...)

define i8* @concat_strings(i8* %str1, i8* %str2) {
  %len1 = call i64 @strlen(i8* %str1)
  %len2 = call i64 @strlen(i8* %str2)
  %totalLen = add i64 %len1, %len2
  %concatStr = call i8* @malloc(i64 %totalLen)
  %ptr1 = bitcast i8* %concatStr to i8*
  call void @memcpy(i8* %ptr1, i8* %str1, i64 %len1, i1 false)
  %ptr2 = getelementptr i8, i8* %ptr1, i64 %len1
  call void @memcpy(i8* %ptr2, i8* %str2, i64 %len2, i1 false)
  %nullPtr = getelementptr i8, i8* %concatStr, i64 %totalLen
  store i8 0, i8* %nullPtr, align 1
  ret i8* %concatStr
}

declare i64 @strlen(i8*)

declare i8* @malloc(i64)

declare void @memcpy(i8*, i8*, i64, i1)

define i32 @stringLength(i8* %str) {
entry:
  %len = call i64 @strlen(i8* %str)
  %len32 = trunc i64 %len to i32
  ret i32 %len32
}

define i8* @itos(i32 %num) {
  %buffer = call i8* @malloc(i64 12)
  %formatStr = getelementptr [3 x i8], [3 x i8]* @intFormat, i32 0, i32 0
  %1 = call i32 @snprintf(i8* %buffer, i64 12, i8* %formatStr, i32 %num)
  ret i8* %buffer
}

declare i32 @snprintf(i8*, i64, i8*, i32)

define i8* @dtos(i32 %f) {
  %buffer = call i8* @malloc(i64 16)
  %formatStr = getelementptr [5 x i8], [5 x i8]* @doubleFormat, i32 0, i32 0
  %1 = call i32 @snprintf(i8* %buffer, i64 16, i8* %formatStr, i32 %f)
  ret i8* %buffer
}

define i8* @getMallocPtrOfStringConstant(i8* %str) {
  %len = call i64 @strlen(i8* %str)
  %lenIncreasedByOne = add i64 %len, 1
  %strPtr = call i8* @malloc(i64 %lenIncreasedByOne)
  call void @memcpy(i8* %strPtr, i8* %str, i64 %lenIncreasedByOne, i1 false)
  ret i8* %strPtr
}

define i8* @getMallocPtrofIntConstant(i32 %num) {
  %buffer = call i8* @malloc(i64 12)
  %formatStr = getelementptr [3 x i8], [3 x i8]* @intFormat, i32 0, i32 0
  %1 = call i32 @snprintf(i8* %buffer, i64 12, i8* %formatStr, i32 %num)
  ret i8* %buffer
}

define i32 @compare_strings(i8* %str1, i8* %str2) {
  %result = call i32 @strcmp(i8* %str1, i8* %str2)
  ret i32 %result
}

declare i32 @strcmp(i8*, i8*)

define i1 @less_than_strings(i8* %str1, i8* %str2) {
  %result = call i32 @strcmp(i8* %str1, i8* %str2)
  %less_than = icmp slt i32 %result, 0
  ret i1 %less_than
}

define i1 @less_than_or_equal_strings(i8* %str1, i8* %str2) {
  %result = call i32 @strcmp(i8* %str1, i8* %str2)
  %less_than_or_equal = icmp sle i32 %result, 0
  ret i1 %less_than_or_equal
}

define i1 @greater_than_strings(i8* %str1, i8* %str2) {
  %result = call i32 @strcmp(i8* %str1, i8* %str2)
  %greater_than = icmp sgt i32 %result, 0
  ret i1 %greater_than
}

define i1 @greater_than_or_equal_strings(i8* %str1, i8* %str2) {
  %result = call i32 @strcmp(i8* %str1, i8* %str2)
  %greater_than_or_equal = icmp sge i32 %result, 0
  ret i1 %greater_than_or_equal
}

define i1 @equal_strings(i8* %str1, i8* %str2) {
  %result = call i32 @strcmp(i8* %str1, i8* %str2)
  %equal = icmp eq i32 %result, 0
  ret i1 %equal
}

define i8* @getInput() {
entry:
  %inputValue = call i8* @malloc(i64 1000001)
  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @formatStrscanf, i32 0, i32 0), i8* %inputValue, i32 0, i32 0)
  ret i8* %inputValue
}

declare i32 @scanf(i8*, ...)

define i32 @stringToInt(i8* %str) {
entry:
  %intValue = call i32 @atoi(i8* %str)
  ret i32 %intValue
}

declare i32 @atoi(i8*)

define i64 @stringToLong(i8* %str) {
entry:
  %longValue = call i64 @atol(i8* %str)
  ret i64 %longValue
}

declare i64 @atol(i8*)

define double @stringToDouble(i8* %str) {
entry:
  %doubleValue = call double @atof(i8* %str)
  ret double %doubleValue
}

declare double @atof(i8*)

define i32 @main() {
entry:
  %result = add i32 2, 3
  call void @print(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @HELLO_WORLD, i32 0, i32 0), i1 false)
  ret i32 %result
}

define i32 @evaluateBlockStatement() {
entry:
  %x = alloca i32, align 4
  store i32 2, i32* %x, align 4
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  %0 = load i32, i32* @ELANG_GLOBAL_ERROR_COUNT, align 4
  ret i32 %0
}
