; ModuleID = '-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module'
source_filename = "-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%"testm::A::VTableType" = type { ptr, ptr }
%"testm::A" = type { ptr, i32, %"testm::D.0" }
%"testm::D.0" = type { i32 }

@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_GLOBAL_NULL = external global i8
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_BREAK_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.testm::A.fg" = common global %"testm::A::VTableType" zeroinitializer
@"testm::x" = common local_unnamed_addr global i32 0
@0 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @0
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @1
@2 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @2
@3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.2" = private constant ptr @3
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.3" = private constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = private constant ptr @5
@6 = private unnamed_addr constant [2 x i8] c"j\00", align 1
@7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.4" = private constant ptr @7
@8 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = private constant ptr @8
@9 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.5" = private constant ptr @9
@10 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.6" = private constant ptr @10
@11 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.7" = private constant ptr @11
@12 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = private constant ptr @12

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

define i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module(i32 %0, ptr %1) {
entry:
  store i32 0, ptr @"testm::x", align 4
  store i32 100, ptr @"testm::x", align 4
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @"testm::A.init1"(ptr %0, ptr %1) !rt !0 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"testm::A", ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %"testm::A", ptr %2, i32 0, i32 2
  %u = alloca i32, align 4
  %5 = load i32, ptr %0, align 4
  store i32 %5, ptr %u, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %"testm::A", ptr %6, i32 0, i32 1
  %u1 = load i32, ptr %7, align 4
  %u2 = load i32, ptr %u, align 4
  %8 = load i32, ptr %u, align 4
  store i32 %8, ptr %7, align 4
  %9 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"testm::A.printX"(ptr %0) !rt !1 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"testm::A", ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %"testm::A", ptr %1, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %u = load i32, ptr %2, align 4
  %4 = load i32, ptr %2, align 4
  %5 = load ptr, ptr @"%s.1", align 8
  %6 = load ptr, ptr @"%d.2", align 8
  call void (ptr, ...) @printf(ptr %6, i32 %4)
  %7 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"testm::A.printD"(ptr %0) !rt !2 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"testm::A", ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %"testm::A", ptr %1, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @"print_testm::D.0"(ptr %3)
  %4 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"testm::fromTest"() !rt !3 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %"testm::x" = load i32, ptr @"testm::x", align 4
  %0 = load i32, ptr @"testm::x", align 4
  %1 = load ptr, ptr @"%s", align 8
  %2 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %2, i32 %0)
  %3 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-targets-aot-compiler-aot-compiler-build-testm-module_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define internal void @"print_testm::D.0"(ptr %0) {
entry:
  %1 = load ptr, ptr @"%s.3", align 8
  %2 = load ptr, ptr @"{ ", align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  call void @print(ptr @6, i1 false)
  %3 = load ptr, ptr @"%s.4", align 8
  %4 = load ptr, ptr @" : ", align 8
  call void (ptr, ...) @printf(ptr %3, ptr %4)
  %5 = getelementptr inbounds %"testm::D.0", ptr %0, i32 0, i32 0
  %6 = load i32, ptr %5, align 4
  %7 = load ptr, ptr @"%s.5", align 8
  %8 = load ptr, ptr @"%d.6", align 8
  call void (ptr, ...) @printf(ptr %8, i32 %6)
  %9 = load ptr, ptr @"%s.7", align 8
  %10 = load ptr, ptr @"}", align 8
  call void (ptr, ...) @printf(ptr %9, ptr %10)
  ret void
}

!0 = !{!"testm::A.init1:rt:pr:27"}
!1 = !{!"testm::A.printX:rt:pr:27"}
!2 = !{!"testm::A.printD:rt:pr:27"}
!3 = !{!"testm::fromTest:rt:pr:27"}
