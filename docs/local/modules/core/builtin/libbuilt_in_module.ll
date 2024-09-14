; ModuleID = 'built_in_module'

source_filename = "built_in_module"

@formatStrprintfnewline =   global [4 x i8] c"%s\0A\00"
@formatStrprintf =   global [3 x i8] c"%s\00"
@formatStrscanf =   global [10 x i8] c"%1000000s\00", align 1
@intFormat =   global [3 x i8] c"%d\00"
@doubleFormat =   global [6 x i8] c"%.14f\00"

declare i8* @malloc(i32)
declare i32 @strlen(i8*)
declare i32 @memcpy(i8*, i8*, i32)
declare i32 @strcmp(i8*, i8*)
declare i32 @printf(i8*, ...)
declare i32 @snprintf(i8*, i32, i8*, ...)
declare i32 @atoi(i8*)
declare double @atof(i8*)
declare i32 @scanf(i8*, ...)
declare i64 @atoll(i8*)
declare i32 @puts(i8*)
declare void @exit(i32)

define  void @print(i8* %0, i1 %1) {
 entry:
   br i1 %1, label %newline, label %withoutnewline

 exit:                                             ; preds = %withoutnewline, %newline
   ret void

 withoutnewline:                                   ; preds = %entry
   %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @formatStrprintf, i32 0, i32 0), i8* %0)
   br label %exit

 newline:                                          ; preds = %entry
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @formatStrprintfnewline, i32 0, i32 0), i8* %0)
  br label %exit
}

define   i8* @concat_strings(i8* %str1, i8* %str2) {
    ; Get the lengths of the input strings
    %len1 = call i32 @strlen(i8* %str1)
    %len2 = call i32 @strlen(i8* %str2)
    
    ; Allocate memory for the concatenated string (including space for null terminator)
    %totalLen = add i32 %len1, %len2
    %totalLenPlusOne = add i32 %totalLen, 1
    %concatStr = call i8* @malloc(i32 %totalLenPlusOne)
    
    ; Copy characters from the first string to the concatenated string
    %ptr1 = bitcast i8* %concatStr to i8*
    call i32 @memcpy(i8* %ptr1, i8* %str1, i32 %len1)
    
    ; Copy characters from the second string to the concatenated string
    %ptr2 = getelementptr i8, i8* %ptr1, i32 %len1
    call i32 @memcpy(i8* %ptr2, i8* %str2, i32 %len2)

    ; Null-terminate the concatenated string
    %nullPtr = getelementptr i8, i8* %concatStr, i32 %totalLen
    store i8 0, i8* %nullPtr
    ret i8* %concatStr
}

define  i32 @string_length(i8* %str) {
entry:
  %len = call i32 @strlen(i8* %str)

  ret i32 %len
}


define  i8* @itos(i32 %num) {
    ; Allocate memory for the string buffer
    %buffer = call i8* @malloc(i32 12)
    
    ; Convert the integer to a string
    %formatStr = getelementptr [3 x i8], [3 x i8]* @intFormat, i32 0, i32 0
    call i32 (i8*, i32, i8*, ...)@snprintf(i8* %buffer, i32 12, i8* %formatStr, i32 %num)

    ; Return the result as a pointer to the string
    ret i8* %buffer
}


define  i8* @dtos(double %f) {
  ; Allocate memory for the string buffer
  %buffer = call i8* @malloc(i32 32)

  ; Convert the double to a string
  %formatStr = getelementptr [6 x i8], [6 x i8]* @doubleFormat, i32 0, i32 0
  call i32 (i8*, i32, i8*, ...)@snprintf(i8* %buffer, i32 32, i8* %formatStr, double %f)
  ; Return the result as a pointer to the string
  ret i8* %buffer
}

define  i8* @get_malloc_ptr_of_string_constant(i8* %str) {
    ; Get the length of the string
    %len = call i32 @strlen(i8* %str)

    %lenIncreasedByOne = add i32 %len, 1
    
    ; Allocate memory for the string
    %strPtr = call i8* @malloc(i32 %lenIncreasedByOne)
    
    ; Copy the string to the allocated memory
    call i32 @memcpy(i8* %strPtr, i8* %str, i32 %lenIncreasedByOne)
    
    ; Return the pointer to the string
    ret i8* %strPtr
}

define  i8* @get_malloc_ptr_of_int_constant(i32 %num) {
    ; Allocate memory for the string buffer
    %buffer = call i8* @malloc(i32 12)
    
    ; Convert the integer to a string
    %formatStr = getelementptr [3 x i8], [3 x i8]* @intFormat, i32 0, i32 0
    call i32 (i8*, i32, i8*, ...)@snprintf(i8* %buffer, i32 12, i8* %formatStr, i32 %num)

    ; Return the result as a pointer to the string
    ret i8* %buffer
}


define  i32 @compare_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    ret i32 %result
}

define  i1 @less_than_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    %less_than = icmp slt i32 %result, 0
    ret i1 %less_than
}

define  i1 @less_than_or_equal_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    %less_than_or_equal = icmp sle i32 %result, 0
    ret i1 %less_than_or_equal
}

define  i1 @greater_than_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    %greater_than = icmp sgt i32 %result, 0
    ret i1 %greater_than
}

define  i1 @greater_than_or_equal_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    %greater_than_or_equal = icmp sge i32 %result, 0
    ret i1 %greater_than_or_equal
}

define  i1 @equal_strings(i8* %str1, i8* %str2) {
    %result = call i32 @strcmp(i8* %str1, i8* %str2)
    %equal = icmp eq i32 %result, 0
    ret i1 %equal
}



define  i8* @get_input() {
entry:
  ; Allocate space for the string 
  %inputValue = call i8* @malloc(i32 1000001)

  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @formatStrscanf, i32 0, i32 0), i8* %inputValue, i32 0, i32 0)


  ret i8* %inputValue
}

define  i32 @string_to_int(i8* %str) {
entry:
  ; Call the atoi function to convert the string to an integer
  %intValue = call i32 @atoi(i8* %str)

  ; Return the integer value
  ret i32 %intValue
}

; Example usage of the atoll function
define  i64 @string_to_long(i8* %str) {
entry:
  %longValue = call i64 @atoll(i8* %str)
  ret i64 %longValue
}

; Example usage of the atof function
define  double @string_to_double(i8* %str) {
entry:
  %doubleValue = call double @atof(i8* %str)
  ret double %doubleValue
}


; Exception handling functions

; This function is called when a division by zero occurs
define void @raise_exception(i8* %errorMsg) {
    ; Print the error message
    %res = call i32 @puts(i8* %errorMsg)

    ; Exit the program with an error code
    call void @exit(i32 1)
    unreachable ; Terminate the program (unreachable code)
}
