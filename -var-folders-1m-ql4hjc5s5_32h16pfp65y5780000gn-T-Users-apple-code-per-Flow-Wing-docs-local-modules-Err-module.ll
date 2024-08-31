; ModuleID = '-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module'
source_filename = "-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module"

%"Err::Result::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Err::ErrorCode.0" = type { i32, i32, i32 }
%"Err::Result" = type { ptr, ptr, i32, ptr }

@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_GLOBAL_NULL = external global i8
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Err::Result.fg" = common global %"Err::Result::VTableType" zeroinitializer
@"Err::CODE" = common global %"Err::ErrorCode.0" zeroinitializer
@0 = private unnamed_addr constant [9 x i8] c"Error: \0A\00", align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [5 x i8] c" -> \00", align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [8 x i8] c"Error: \00", align 1
@11 = private unnamed_addr constant [12 x i8] c" (Details: \00", align 1
@12 = private unnamed_addr constant [2 x i8] c")\00", align 1

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

define i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module() {
entry:
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @"Err::Result.init1"(ptr %0, ptr %1) !rt !0 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 3
  %message = alloca ptr, align 8
  %6 = load ptr, ptr %0, align 8
  store ptr %6, ptr %message, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = load ptr, ptr %1, align 8
  %8 = getelementptr inbounds %"Err::Result", ptr %7, i32 0, i32 1
  %message1 = load ptr, ptr %8, align 8
  %message2 = load ptr, ptr %message, align 8
  %9 = load ptr, ptr %message, align 8
  store ptr %9, ptr %8, align 8
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Err::Result.init2"(ptr %0, ptr %1, ptr %2) !rt !1 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 3
  %message = alloca ptr, align 8
  %7 = load ptr, ptr %0, align 8
  store ptr %7, ptr %message, align 8
  %code = alloca i32, align 4
  %8 = load i32, ptr %1, align 4
  store i32 %8, ptr %code, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %9 = load ptr, ptr %2, align 8
  %10 = getelementptr inbounds %"Err::Result", ptr %9, i32 0, i32 1
  %message3 = load ptr, ptr %10, align 8
  %message4 = load ptr, ptr %message, align 8
  %11 = load ptr, ptr %message, align 8
  store ptr %11, ptr %10, align 8
  %12 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %14 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %16 = load ptr, ptr %2, align 8
  %17 = getelementptr inbounds %"Err::Result", ptr %16, i32 0, i32 2
  %code5 = load i32, ptr %17, align 4
  %code6 = load i32, ptr %code, align 4
  %18 = load i32, ptr %code, align 4
  store i32 %18, ptr %17, align 4
  %19 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @"Err::Result.init3"(ptr %0, ptr %1, ptr %2, ptr %3) !rt !2 {
entry:
  %4 = load ptr, ptr %3, align 8
  %5 = getelementptr inbounds %"Err::Result", ptr %4, i32 0, i32 1
  %6 = getelementptr inbounds %"Err::Result", ptr %4, i32 0, i32 2
  %7 = getelementptr inbounds %"Err::Result", ptr %4, i32 0, i32 3
  %message = alloca ptr, align 8
  %8 = load ptr, ptr %0, align 8
  store ptr %8, ptr %message, align 8
  %code = alloca i32, align 4
  %9 = load i32, ptr %1, align 4
  store i32 %9, ptr %code, align 4
  %details = alloca ptr, align 8
  %10 = load ptr, ptr %2, align 8
  store ptr %10, ptr %details, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %11 = load ptr, ptr %3, align 8
  %12 = getelementptr inbounds %"Err::Result", ptr %11, i32 0, i32 1
  %message5 = load ptr, ptr %12, align 8
  %message6 = load ptr, ptr %message, align 8
  %13 = load ptr, ptr %message, align 8
  store ptr %13, ptr %12, align 8
  %14 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %16 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %18 = load ptr, ptr %3, align 8
  %19 = getelementptr inbounds %"Err::Result", ptr %18, i32 0, i32 2
  %code7 = load i32, ptr %19, align 4
  %code8 = load i32, ptr %code, align 4
  %20 = load i32, ptr %code, align 4
  store i32 %20, ptr %19, align 4
  %21 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = load ptr, ptr %3, align 8
  %26 = getelementptr inbounds %"Err::Result", ptr %25, i32 0, i32 3
  %details9 = load ptr, ptr %26, align 8
  %details10 = load ptr, ptr %details, align 8
  %27 = load ptr, ptr %details, align 8
  store ptr %27, ptr %26, align 8
  %28 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @"Err::Result.getMessage"(ptr %0, ptr %1) !rt !3 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %"Err::Result", ptr %6, i32 0, i32 1
  %message = load ptr, ptr %7, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = call ptr @concat_strings(ptr @0, ptr %8)
  store ptr %9, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Err::Result.getCode"(ptr %0, ptr %1) !rt !4 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %"Err::Result", ptr %6, i32 0, i32 2
  %code = load i32, ptr %7, align 4
  %8 = load i32, ptr %7, align 4
  store i32 %8, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Err::Result.getDetails"(ptr %0, ptr %1) !rt !5 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %"Err::Result", ptr %6, i32 0, i32 3
  %details = load ptr, ptr %7, align 8
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Err::Result.withMessage"(ptr %0, ptr %1, ptr %2) !rt !6 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 3
  %extraMessage = alloca ptr, align 8
  %7 = load ptr, ptr %1, align 8
  store ptr %7, ptr %extraMessage, align 8
  %8 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %9 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %9)
  %10 = getelementptr inbounds %"Err::Result", ptr %9, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %10, align 8
  %11 = load ptr, ptr %10, align 8
  %12 = getelementptr inbounds %"Err::Result::VTableType", ptr %11, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %12, align 8
  %13 = getelementptr inbounds %"Err::Result::VTableType", ptr %11, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %13, align 8
  %14 = getelementptr inbounds %"Err::Result::VTableType", ptr %11, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %14, align 8
  %15 = getelementptr inbounds %"Err::Result::VTableType", ptr %11, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %15, align 8
  %16 = getelementptr inbounds %"Err::Result::VTableType", ptr %11, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %16, align 8
  %17 = getelementptr inbounds %"Err::Result::VTableType", ptr %11, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %17, align 8
  %18 = getelementptr inbounds %"Err::Result", ptr %9, i32 0, i32 1
  store ptr @4, ptr %18, align 8
  %19 = getelementptr inbounds %"Err::Result", ptr %9, i32 0, i32 2
  store i32 0, ptr %19, align 4
  %20 = getelementptr inbounds %"Err::Result", ptr %9, i32 0, i32 3
  store ptr @5, ptr %20, align 8
  store ptr %9, ptr %0, align 8
  %21 = load ptr, ptr %2, align 8
  %22 = getelementptr inbounds %"Err::Result", ptr %21, i32 0, i32 1
  %message = load ptr, ptr %22, align 8
  %23 = load ptr, ptr %22, align 8
  %24 = call ptr @concat_strings(ptr %23, ptr @6)
  %extraMessage1 = load ptr, ptr %extraMessage, align 8
  %25 = load ptr, ptr %extraMessage, align 8
  %26 = call ptr @concat_strings(ptr %24, ptr %25)
  store ptr %26, ptr %8, align 8
  %27 = load ptr, ptr %2, align 8
  %28 = getelementptr inbounds %"Err::Result", ptr %27, i32 0, i32 2
  %code = load i32, ptr %28, align 4
  %29 = load ptr, ptr %2, align 8
  %30 = getelementptr inbounds %"Err::Result", ptr %29, i32 0, i32 3
  %details = load ptr, ptr %30, align 8
  call void @"Err::Result.init3"(ptr %8, ptr %28, ptr %30, ptr %0)
  ret void

mergeBlock:                                       ; No predecessors!
  %31 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Err::Result.withDetails"(ptr %0, ptr %1, ptr %2) !rt !7 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %"Err::Result", ptr %3, i32 0, i32 3
  %details = alloca ptr, align 8
  %7 = load ptr, ptr %1, align 8
  store ptr %7, ptr %details, align 8
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %8 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %8)
  %9 = getelementptr inbounds %"Err::Result", ptr %8, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %9, align 8
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"Err::Result::VTableType", ptr %10, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %11, align 8
  %12 = getelementptr inbounds %"Err::Result::VTableType", ptr %10, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %12, align 8
  %13 = getelementptr inbounds %"Err::Result::VTableType", ptr %10, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %13, align 8
  %14 = getelementptr inbounds %"Err::Result::VTableType", ptr %10, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %14, align 8
  %15 = getelementptr inbounds %"Err::Result::VTableType", ptr %10, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %15, align 8
  %16 = getelementptr inbounds %"Err::Result::VTableType", ptr %10, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %16, align 8
  %17 = getelementptr inbounds %"Err::Result", ptr %8, i32 0, i32 1
  store ptr @7, ptr %17, align 8
  %18 = getelementptr inbounds %"Err::Result", ptr %8, i32 0, i32 2
  store i32 0, ptr %18, align 4
  %19 = getelementptr inbounds %"Err::Result", ptr %8, i32 0, i32 3
  store ptr @8, ptr %19, align 8
  store ptr %8, ptr %0, align 8
  %20 = load ptr, ptr %2, align 8
  %21 = getelementptr inbounds %"Err::Result", ptr %20, i32 0, i32 1
  %message = load ptr, ptr %21, align 8
  %22 = load ptr, ptr %2, align 8
  %23 = getelementptr inbounds %"Err::Result", ptr %22, i32 0, i32 2
  %code = load i32, ptr %23, align 4
  %details1 = load ptr, ptr %details, align 8
  call void @"Err::Result.init3"(ptr %21, ptr %23, ptr %details, ptr %0)
  ret void

mergeBlock:                                       ; No predecessors!
  %24 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Err::Result.toString"(ptr %0, ptr %1) !rt !8 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %"Err::Result", ptr %2, i32 0, i32 3
  %result = alloca ptr, align 8
  store ptr @9, ptr %result, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %mergeBlock, %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %"Err::Result", ptr %6, i32 0, i32 1
  %message = load ptr, ptr %7, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = call ptr @concat_strings(ptr @10, ptr %8)
  store ptr %9, ptr %result, align 8
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %12 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_CONTINUE_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %14 = load ptr, ptr %1, align 8
  %15 = getelementptr inbounds %"Err::Result", ptr %14, i32 0, i32 3
  %details = load ptr, ptr %15, align 8
  %16 = load ptr, ptr %15, align 8
  %17 = icmp eq ptr %16, null
  br i1 %17, label %"BoolTC::NullBlock", label %"BoolTC::NotNullBlock"

checkContinueBlock2:                              ; preds = %afterIfElse
  %18 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  br label %returnBlock

checkContinueBlock4:                              ; preds = %mergeBlock
  br label %afterNestedBlock

then:                                             ; preds = %"BoolTC::MergeBlock"
  br label %nestedBlock6

else:                                             ; preds = %"BoolTC::MergeBlock"
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock5
  %20 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock2, label %afterNestedBlock

"BoolTC::NullBlock":                              ; preds = %nestedBlock1
  br label %"BoolTC::MergeBlock"

"BoolTC::NotNullBlock":                           ; preds = %nestedBlock1
  %22 = call i32 @string_length(ptr %16)
  %23 = icmp eq i32 %22, 0
  %24 = select i1 %23, i1 false, i1 true
  br label %"BoolTC::MergeBlock"

"BoolTC::MergeBlock":                             ; preds = %"BoolTC::NotNullBlock", %"BoolTC::NullBlock"
  %25 = phi i1 [ false, %"BoolTC::NullBlock" ], [ %24, %"BoolTC::NotNullBlock" ]
  br i1 %25, label %then, label %else

afterNestedBlock5:                                ; preds = %checkContinueBlock7, %nestedBlock6
  br label %afterIfElse

nestedBlock6:                                     ; preds = %then
  %result8 = load ptr, ptr %result, align 8
  %result9 = load ptr, ptr %result, align 8
  %26 = load ptr, ptr %result, align 8
  %27 = call ptr @concat_strings(ptr %26, ptr @11)
  %28 = load ptr, ptr %1, align 8
  %29 = getelementptr inbounds %"Err::Result", ptr %28, i32 0, i32 3
  %details10 = load ptr, ptr %29, align 8
  %30 = load ptr, ptr %29, align 8
  %31 = call ptr @concat_strings(ptr %27, ptr %30)
  %32 = call ptr @concat_strings(ptr %31, ptr @12)
  store ptr %32, ptr %result, align 8
  %33 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock7, label %afterNestedBlock5

checkContinueBlock7:                              ; preds = %nestedBlock6
  br label %afterNestedBlock5

returnBlock:                                      ; preds = %nestedBlock3
  %result11 = load ptr, ptr %result, align 8
  %35 = load ptr, ptr %result, align 8
  store ptr %35, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %36 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock4, label %afterNestedBlock
}

define internal void @"assign_<ObjectErr::ErrorCode.0>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::ErrorCode.0", ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %"Err::ErrorCode.0", ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %"Err::ErrorCode.0", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  ret void
}

define internal void @"assign_<Class<Err::Result>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 0
  store ptr @1, ptr %1, align 8
  %2 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 1
  store ptr @2, ptr %2, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 3
  store ptr @3, ptr %4, align 8
  ret void
}

!0 = !{!"Err::Result.init1:rt:pr:27"}
!1 = !{!"Err::Result.init2:rt:pr:27"}
!2 = !{!"Err::Result.init3:rt:pr:27"}
!3 = !{!"Err::Result.getMessage:rt:pr:33"}
!4 = !{!"Err::Result.getCode:rt:pr:28"}
!5 = !{!"Err::Result.getDetails:rt:pr:33"}
!6 = !{!"Err::Result.withMessage:rt:ob:Err::Result"}
!7 = !{!"Err::Result.withDetails:rt:ob:Err::Result"}
!8 = !{!"Err::Result.toString:rt:pr:33"}
