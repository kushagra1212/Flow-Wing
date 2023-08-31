; ModuleID = 'ElangModule'
source_filename = "ElangModule"

declare i8* @malloc(i64)
declare i64 @strlen(i8*)
declare void @memcpy(i8*, i8*, i64, i1)
declare i32 @strcmp(i8*, i8*)

declare i32 @snprintf(i8*, i64, i8*, i32)
@intFormat = constant [3 x i8] c"%d\00"
@doubleFormat = constant [5 x i8] c"%.6f\00"
define i8* @concat_strings(i8* %str1, i8* %str2) {
    ; Get the lengths of the input strings
    %len1 = call i64 @strlen(i8* %str1)
    %len2 = call i64 @strlen(i8* %str2)
    
    ; Allocate memory for the concatenated string
    %totalLen = add i64 %len1, %len2
    %concatStr = call i8* @malloc(i64 %totalLen)
    
    ; Copy characters from the first string to the concatenated string
    %ptr1 = bitcast i8* %concatStr to i8*
    call void @memcpy(i8* %ptr1, i8* %str1, i64 %len1, i1 false)
    
    ; Copy characters from the second string to the concatenated string
    %ptr2 = getelementptr i8, i8* %ptr1, i64 %len1
    call void @memcpy(i8* %ptr2, i8* %str2, i64 %len2, i1 false)

    ; Null-terminate the concatenated string
    %nullPtr = getelementptr i8, i8* %concatStr, i64 %totalLen
    store i8 0, i8* %nullPtr
    ret i8* %concatStr
}

define i32 @stringLength(i8* %str) {
entry:
  %0 = alloca i32, align 4
  store i32 0, i32* %0, align 4
  %1 = load i32, i32* %0, align 4
  ret i32 %1
}


define i8* @itos(i32 %num) {
    ; Allocate memory for the string buffer
    %buffer = call i8* @malloc(i64 12)
    
    ; Convert the integer to a string
    %formatStr = getelementptr [3 x i8], [3 x i8]* @intFormat, i32 0, i32 0
    call i32 @snprintf(i8* %buffer, i64 12, i8* %formatStr, i32 %num)

    ; Return the result as a pointer to the string
    ret i8* %buffer
}


define i8* @dtos(i32 %f) {
  ; Allocate memory for the string buffer
  %buffer = call i8* @malloc(i64 16)

  ; Convert the double to a string
  %formatStr = getelementptr [5 x i8], [5 x i8]* @doubleFormat, i32 0, i32 0
  call i32 @snprintf(i8* %buffer, i64 16, i8* %formatStr, i32 %f)
  ; Return the result as a pointer to the string
  ret i8* %buffer
}


define i32 @compare_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    ret i32 %result
}

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

