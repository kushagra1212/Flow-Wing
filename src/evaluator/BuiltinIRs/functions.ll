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
  %len = call i64 @strlen(i8* %str)

  ; convert to i32

  %len32 = trunc i64 %len to i32

  ret i32 %len32
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

define i8* @getMallocPtrOfStringConstant(i8* %str) {
    ; Get the length of the string
    %len = call i64 @strlen(i8* %str)

    %lenIncreasedByOne = add i64 %len, 1
    
    ; Allocate memory for the string
    %strPtr = call i8* @malloc(i64 %lenIncreasedByOne)
    
    ; Copy the string to the allocated memory
    call void @memcpy(i8* %strPtr, i8* %str, i64 %lenIncreasedByOne, i1 false)
    
    ; Return the pointer to the string
    ret i8* %strPtr
}

define i8* @getMallocPtrofIntConstant(i32 %num) {
    ; Allocate memory for the string buffer
    %buffer = call i8* @malloc(i64 12)
    
    ; Convert the integer to a string
    %formatStr = getelementptr [3 x i8], [3 x i8]* @intFormat, i32 0, i32 0
    call i32 @snprintf(i8* %buffer, i64 12, i8* %formatStr, i32 %num)

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

declare i32 @scanf(i8*, ...)
@formatStrscanf = private constant [10 x i8] c"%1000000s\00", align 1


define i8* @getInput() {
entry:
  ; Allocate space for the string 
  %inputValue = call i8* (i64) @malloc(i64 1000001)

  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @formatStrscanf, i32 0, i32 0), i8* %inputValue, i32 0, i32 0)


  ret i8* %inputValue
}

declare i32 @atoi(i8*)

define i32 @stringToInt(i8* %str) {
entry:
  ; Call the atoi function to convert the string to an integer
  %intValue = call i32 @atoi(i8* %str)

  ; Return the integer value
  ret i32 %intValue
}
declare i64 @atol(i8*)
; Example usage of the atol function
define i64 @stringToLong(i8* %str) {
entry:
  %longValue = call i64 @atol(i8* %str)
  ret i64 %longValue
}

declare double @atof(i8*)
; Example usage of the atof function
define double @stringToDouble(i8* %str) {
entry:
  %doubleValue = call double @atof(i8* %str)
  ret double %doubleValue
}

