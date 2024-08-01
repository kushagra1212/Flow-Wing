; ModuleID = 'iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom'
source_filename = "iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom"

@iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_GLOBAL_NULL = external global i8
@iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_BREAK_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_CONTINUE_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0

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

define i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 i32 @rand()

declare !rt !1 i32 @time()

declare !rt !2 void @srand(i32)

define void @getRandomNumber(ptr %0, ptr %1, ptr %2) !rt !3 {
entry:
  %start = alloca i32, align 4
  %3 = load i32, ptr %1, align 4
  store i32 %3, ptr %start, align 4
  %end = alloca i32, align 4
  %4 = load i32, ptr %2, align 4
  store i32 %4, ptr %end, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = call i32 @rand()
  %end1 = load i32, ptr %end, align 4
  %6 = load i32, ptr %end, align 4
  %start2 = load i32, ptr %start, align 4
  %7 = load i32, ptr %start, align 4
  %8 = sub i32 %6, %7
  %9 = add i32 %8, 1
  %10 = srem i32 %5, %9
  %start3 = load i32, ptr %start, align 4
  %11 = load i32, ptr %start, align 4
  %12 = add i32 %10, %11
  store i32 %12, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoibird-gameirandom_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"rand:rt:pr:28"}
!1 = !{!"time:rt:pr:28"}
!2 = !{!"srand:rt:pr:27"}
!3 = !{!"getRandomNumber:rt:pr:28"}
