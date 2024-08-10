; ModuleID = 'flowmain'
source_filename = "flowmain"

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@fileName = common global ptr null
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@file = common global ptr null
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [11 x i8] c"2temp3.txt\00", align 1
@3 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @4
@5 = private unnamed_addr constant [5 x i8] c"NULL\00", align 1
@6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @6

declare i32 @compare_strings(ptr, ptr)

declare ptr @concat_strings(ptr, ptr)

declare ptr @dtos(double)

declare i1 @equal_strings(ptr, ptr)

declare ptr @get_input()

declare ptr @get_malloc_ptr_of_int_constant(i32)

declare ptr @get_malloc_ptr_of_string_constant(ptr)

declare i1 @greater_than_or_equal_strings(ptr, ptr)

declare i1 @greater_than_strings(ptr, ptr)

declare ptr @itos(i32)

declare i1 @less_than_or_equal_strings(ptr, ptr)

declare i1 @less_than_strings(ptr, ptr)

declare void @print(ptr, i1)

declare void @printf(ptr, ...)

declare i32 @string_length(ptr)

declare double @string_to_double(ptr)

declare i32 @string_to_int(ptr)

declare i64 @string_to_long(ptr)

declare void @raise_exception(ptr)

declare ptr @malloc(i64)

define i32 @flowmain() {
entry:
  store ptr @0, ptr @fileName, align 8
  store ptr @1, ptr @file, align 8
  store ptr @2, ptr @fileName, align 8
  %fileName = load ptr, ptr @fileName, align 8
  %0 = load ptr, ptr @fileName, align 8
  %1 = call ptr @fopen(ptr %0, ptr @3)
  store ptr %1, ptr @file, align 8
  %2 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %2, ptr null)
  %file = load ptr, ptr @file, align 8
  %3 = load ptr, ptr @file, align 8
  %4 = icmp eq ptr %3, null
  br i1 %4, label %then, label %else

returnBlock:                                      ; preds = %afterIfElse
  ret i32 0

then:                                             ; preds = %entry
  br label %nestedBlock

else:                                             ; preds = %entry
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock
  br label %returnBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  br label %afterIfElse

nestedBlock:                                      ; preds = %then
  %5 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %5, ptr @5)
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

declare !rt !0 ptr @fopen(ptr, ptr)

declare !rt !1 i32 @fread(ptr, i32, i32, ptr)

!0 = !{!"fopen:rt:pr:33"}
!1 = !{!"fread:rt:pr:28"}
