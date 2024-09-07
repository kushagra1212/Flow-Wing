; ModuleID = '-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module'
source_filename = "-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module"

%"local::A::VTableType" = type { ptr }
%"local::A" = type { ptr, %T.0, i32 }
%T.0 = type { i32 }

@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_GLOBAL_NULL = external global i8
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_BREAK_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.local::A.fg" = common global %"local::A::VTableType" zeroinitializer
@"local::x" = common global i32 0
@0 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @0
@1 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = private constant ptr @1
@2 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @3
@4 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = private constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.2" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @6
@7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.3" = private constant ptr @7
@8 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = private constant ptr @8

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

define i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module() {
entry:
  store i32 0, ptr @"local::x", align 4
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @"local::A.init0"(ptr %0) !rt !0 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"local::A", ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %"local::A", ptr %1, i32 0, i32 2
  br label %afterNestedBlock

afterNestedBlock:                                 ; preds = %entry
  ret void
}

define void @"local::A.printX"(ptr %0) !rt !1 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"local::A", ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %"local::A", ptr %1, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %0, align 8
  %5 = getelementptr inbounds %"local::A", ptr %4, i32 0, i32 1
  call void @print_T.0(ptr %5)
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-local-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define internal void @print_T.0(ptr %0) {
entry:
  %1 = load ptr, ptr @"%s", align 8
  %2 = load ptr, ptr @"{ ", align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  call void @print(ptr @2, i1 false)
  %3 = load ptr, ptr @"%s.1", align 8
  %4 = load ptr, ptr @" : ", align 8
  call void (ptr, ...) @printf(ptr %3, ptr %4)
  %5 = getelementptr inbounds %T.0, ptr %0, i32 0, i32 0
  %6 = load i32, ptr %5, align 4
  %7 = load ptr, ptr @"%s.2", align 8
  %8 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %8, i32 %6)
  %9 = load ptr, ptr @"%s.3", align 8
  %10 = load ptr, ptr @"}", align 8
  call void (ptr, ...) @printf(ptr %9, ptr %10)
  ret void
}

!0 = !{!"local::A.init0:rt:pr:27"}
!1 = !{!"local::A.printX:rt:pr:27"}
