; ModuleID = '-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module'
source_filename = "-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module"

@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module_FLOWWING_GLOBAL_NULL = external global i8
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module_FLOWWING_BREAK_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"f1::x" = common global i32 0

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

define i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-temp-f1-module() {
entry:
  store i32 0, ptr @"f1::x", align 4
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}
