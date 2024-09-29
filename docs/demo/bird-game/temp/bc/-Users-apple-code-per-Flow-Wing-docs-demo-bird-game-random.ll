; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0

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

declare i32 @putchar(i32)

define i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random(i32 %0, ptr %1) {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 i32 @rand()

declare !rt !1 i32 @time()

declare !rt !2 void @srand(i32)

define i32 @getRandomNumber(ptr %0, ptr %1) !rt !3 {
entry:
  %start = alloca i32, align 4
  %2 = load i32, ptr %0, align 4
  store i32 %2, ptr %start, align 4
  %end = alloca i32, align 4
  %3 = load i32, ptr %1, align 4
  store i32 %3, ptr %end, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %4 = call i32 @rand()
  %end1 = load i32, ptr %end, align 4
  %5 = load i32, ptr %end, align 4
  %start2 = load i32, ptr %start, align 4
  %6 = load i32, ptr %start, align 4
  %7 = sub i32 %5, %6
  %8 = add i32 %7, 1
  %9 = srem i32 %4, %8
  %start3 = load i32, ptr %start, align 4
  %10 = load i32, ptr %start, align 4
  %11 = add i32 %9, %10
  ret i32 %11

mergeBlock:                                       ; No predecessors!
  %12 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"rand:rt:pr:28"}
!1 = !{!"time:rt:pr:28"}
!2 = !{!"srand:rt:pr:27"}
!3 = !{!"getRandomNumber:rt:pr:28"}
