; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-local-ERR-module'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-local-ERR-module"

%"ERR::Error::VTableType" = type {}
%"ERR::Error" = type { ptr, ptr }

@-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.ERR::Error.fg" = common global %"ERR::Error::VTableType" zeroinitializer
@0 = private unnamed_addr constant [8 x i8] c"Error: \00", align 1

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

define i32 @-Users-apple-code-per-Flow-Wing-docs-local-ERR-module() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @"ERR::Error.init1"(ptr %0, ptr %1) !rt !0 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"ERR::Error", ptr %2, i32 0, i32 1
  %message = alloca ptr, align 8
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %message, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %1, align 8
  %6 = getelementptr inbounds %"ERR::Error", ptr %5, i32 0, i32 1
  %message1 = load ptr, ptr %6, align 8
  %message2 = load ptr, ptr %message, align 8
  %7 = load ptr, ptr %message, align 8
  %8 = call ptr @concat_strings(ptr @0, ptr %7)
  store ptr %8, ptr %6, align 8
  %9 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-ERR-module_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

!0 = !{!"ERR::Error.init1:rt:pr:27"}
