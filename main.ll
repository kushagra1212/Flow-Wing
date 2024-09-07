; ModuleID = 'main'
source_filename = "main"

@main_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@main_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@main_FLOWWING_GLOBAL_NULL = external global i8
@main_FLOWWING_BREAK_COUNT = global i32 0
@main_FLOWWING_CONTINUE_COUNT = global i32 0
@main_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0

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

define i32 @main() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define i32 @flowmain(i32 %0, ptr %1) !rt !0 {
entry:
  %argc = alloca i32, align 4
  store i32 %0, ptr %argc, align 4
  %argv = alloca ptr, align 8
  store ptr %1, ptr %argv, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  ret i32 0

mergeBlock:                                       ; No predecessors!
  %2 = load i32, ptr @main_FLOWWING_BREAK_COUNT, align 4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"flowmain:rt:pr:28"}
