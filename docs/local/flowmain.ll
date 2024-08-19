; ModuleID = 'flowmain'
source_filename = "flowmain"

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@x = common global ptr null
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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
  store ptr @0, ptr @x, align 8
  %x = load ptr, ptr @x, align 8
  %0 = load ptr, ptr @x, align 8
  %1 = call i32 @string_length(ptr %0)
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %then, label %else

returnBlock:                                      ; preds = %afterIfElse
  ret i32 0

then:                                             ; preds = %entry
  br label %afterNestedBlock

else:                                             ; preds = %entry
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock
  br label %returnBlock

afterNestedBlock:                                 ; preds = %then
  br label %afterIfElse
}
