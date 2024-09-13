; ModuleID = '-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module'
source_filename = "-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%"Vec::Int::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Vec::Bool::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Vec::String::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Vec::Deci::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Vec::Int" = type { ptr, ptr }
%"Vec::Bool" = type { ptr, ptr }
%"Vec::String" = type { ptr, ptr }
%"Vec::Deci" = type { ptr, ptr }

@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_GLOBAL_NULL = external global i8
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Vec::Int.fg" = common global %"Vec::Int::VTableType" zeroinitializer
@"vtable.Vec::Bool.fg" = common global %"Vec::Bool::VTableType" zeroinitializer
@"vtable.Vec::String.fg" = common global %"Vec::String::VTableType" zeroinitializer
@"vtable.Vec::Deci.fg" = common global %"Vec::Deci::VTableType" zeroinitializer

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

define i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @"Vec::Int.init0"(ptr %0) !rt !0 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::Int", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::Int", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = call ptr @int_vector_new()
  store ptr %5, ptr %4, align 8
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Int.add"(ptr %0, ptr %1) !rt !1 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Int", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Int", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %element = load i32, ptr %0, align 4
  %7 = load i32, ptr %0, align 4
  call void @int_vector_add(ptr %6, i32 %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Int.get"(ptr %0, ptr %1, ptr %2) !rt !2 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::Int", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::Int", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %1, align 4
  %8 = load i32, ptr %1, align 4
  %9 = call i32 @int_vector_get(ptr %7, i32 %8)
  store i32 %9, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::Int.set"(ptr %0, ptr %1, ptr %2) !rt !3 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::Int", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::Int", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %0, align 4
  %8 = load i32, ptr %0, align 4
  %element = load i32, ptr %1, align 4
  %9 = load i32, ptr %1, align 4
  call void @int_vector_set(ptr %7, i32 %8, i32 %9)
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Int.remove"(ptr %0, ptr %1) !rt !4 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Int", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Int", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %index = load i32, ptr %0, align 4
  %7 = load i32, ptr %0, align 4
  call void @int_vector_remove(ptr %6, i32 %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Int.size"(ptr %0, ptr %1) !rt !5 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Int", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Int", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = call i32 @int_vector_size(ptr %6)
  store i32 %7, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::Int.free"(ptr %0) !rt !6 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::Int", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::Int", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = load ptr, ptr %4, align 8
  call void @int_vector_free(ptr %5)
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Bool.init0"(ptr %0) !rt !7 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::Bool", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::Bool", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = call ptr @bool_vector_new()
  store ptr %5, ptr %4, align 8
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Bool.add"(ptr %0, ptr %1) !rt !8 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Bool", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Bool", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %element = load i1, ptr %0, align 1
  %7 = load i1, ptr %0, align 1
  call void @bool_vector_add(ptr %6, i1 %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Bool.get"(ptr %0, ptr %1, ptr %2) !rt !9 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::Bool", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::Bool", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %1, align 4
  %8 = load i32, ptr %1, align 4
  %9 = call i1 @bool_vector_get(ptr %7, i32 %8)
  store i1 %9, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::Bool.set"(ptr %0, ptr %1, ptr %2) !rt !10 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::Bool", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::Bool", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %0, align 4
  %8 = load i32, ptr %0, align 4
  %element = load i1, ptr %1, align 1
  %9 = load i1, ptr %1, align 1
  call void @bool_vector_set(ptr %7, i32 %8, i1 %9)
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Bool.remove"(ptr %0, ptr %1) !rt !11 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Bool", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Bool", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %index = load i32, ptr %0, align 4
  %7 = load i32, ptr %0, align 4
  call void @bool_vector_remove(ptr %6, i32 %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Bool.size"(ptr %0, ptr %1) !rt !12 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Bool", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Bool", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = call i32 @bool_vector_size(ptr %6)
  store i32 %7, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::Bool.free"(ptr %0) !rt !13 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::Bool", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::Bool", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = load ptr, ptr %4, align 8
  call void @bool_vector_free(ptr %5)
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::String.init0"(ptr %0) !rt !14 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::String", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::String", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = call ptr @string_vector_new()
  store ptr %5, ptr %4, align 8
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::String.add"(ptr %0, ptr %1) !rt !15 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::String", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::String", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %element = load ptr, ptr %0, align 8
  %7 = load ptr, ptr %0, align 8
  call void @string_vector_add(ptr %6, ptr %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::String.get"(ptr %0, ptr %1, ptr %2) !rt !16 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::String", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::String", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %1, align 4
  %8 = load i32, ptr %1, align 4
  %9 = call ptr @string_vector_get(ptr %7, i32 %8)
  store ptr %9, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::String.set"(ptr %0, ptr %1, ptr %2) !rt !17 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::String", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::String", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %0, align 4
  %8 = load i32, ptr %0, align 4
  %element = load ptr, ptr %1, align 8
  %9 = load ptr, ptr %1, align 8
  call void @string_vector_set(ptr %7, i32 %8, ptr %9)
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::String.remove"(ptr %0, ptr %1) !rt !18 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::String", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::String", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %index = load i32, ptr %0, align 4
  %7 = load i32, ptr %0, align 4
  call void @string_vector_remove(ptr %6, i32 %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::String.size"(ptr %0, ptr %1) !rt !19 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::String", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::String", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = call i32 @string_vector_size(ptr %6)
  store i32 %7, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::String.free"(ptr %0) !rt !20 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::String", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::String", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = load ptr, ptr %4, align 8
  call void @string_vector_free(ptr %5)
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Deci.init0"(ptr %0) !rt !21 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::Deci", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::Deci", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = call ptr @double_vector_new()
  store ptr %5, ptr %4, align 8
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Deci.add"(ptr %0, ptr %1) !rt !22 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Deci", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Deci", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %element = load double, ptr %0, align 8
  %7 = load double, ptr %0, align 8
  call void @double_vector_add(ptr %6, double %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Deci.get"(ptr %0, ptr %1, ptr %2) !rt !23 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::Deci", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::Deci", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %1, align 4
  %8 = load i32, ptr %1, align 4
  %9 = call double @double_vector_get(ptr %7, i32 %8)
  store double %9, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::Deci.set"(ptr %0, ptr %1, ptr %2) !rt !24 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"Vec::Deci", ptr %3, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %2, align 8
  %6 = getelementptr inbounds %"Vec::Deci", ptr %5, i32 0, i32 1
  %vectorHandler = load ptr, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %index = load i32, ptr %0, align 4
  %8 = load i32, ptr %0, align 4
  %element = load double, ptr %1, align 8
  %9 = load double, ptr %1, align 8
  call void @double_vector_set(ptr %7, i32 %8, double %9)
  %10 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Deci.remove"(ptr %0, ptr %1) !rt !25 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Deci", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Deci", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %index = load i32, ptr %0, align 4
  %7 = load i32, ptr %0, align 4
  call void @double_vector_remove(ptr %6, i32 %7)
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @"Vec::Deci.size"(ptr %0, ptr %1) !rt !26 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"Vec::Deci", ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %4 = load ptr, ptr %1, align 8
  %5 = getelementptr inbounds %"Vec::Deci", ptr %4, i32 0, i32 1
  %vectorHandler = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = call i32 @double_vector_size(ptr %6)
  store i32 %7, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @"Vec::Deci.free"(ptr %0) !rt !27 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %"Vec::Deci", ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr %0, align 8
  %4 = getelementptr inbounds %"Vec::Deci", ptr %3, i32 0, i32 1
  %vectorHandler = load ptr, ptr %4, align 8
  %5 = load ptr, ptr %4, align 8
  call void @double_vector_free(ptr %5)
  %6 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-core-VectorModule-Vec-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

declare !rt !28 ptr @int_vector_new()

declare !rt !29 void @int_vector_add(ptr, i32)

declare !rt !30 i32 @int_vector_get(ptr, i32)

declare !rt !31 void @int_vector_set(ptr, i32, i32)

declare !rt !32 void @int_vector_remove(ptr, i32)

declare !rt !33 i32 @int_vector_size(ptr)

declare !rt !34 void @int_vector_free(ptr)

declare !rt !35 ptr @bool_vector_new()

declare !rt !36 void @bool_vector_add(ptr, i1)

declare !rt !37 void @bool_vector_set(ptr, i32, i1)

declare !rt !38 i1 @bool_vector_get(ptr, i32)

declare !rt !39 void @bool_vector_remove(ptr, i32)

declare !rt !40 i32 @bool_vector_size(ptr)

declare !rt !41 void @bool_vector_free(ptr)

declare !rt !42 ptr @string_vector_new()

declare !rt !43 void @string_vector_add(ptr, ptr)

declare !rt !44 void @string_vector_set(ptr, i32, ptr)

declare !rt !45 ptr @string_vector_get(ptr, i32)

declare !rt !46 void @string_vector_remove(ptr, i32)

declare !rt !47 i32 @string_vector_size(ptr)

declare !rt !48 void @string_vector_free(ptr)

declare !rt !49 ptr @double_vector_new()

declare !rt !50 void @double_vector_add(ptr, double)

declare !rt !51 void @double_vector_set(ptr, i32, double)

declare !rt !52 double @double_vector_get(ptr, i32)

declare !rt !53 void @double_vector_remove(ptr, i32)

declare !rt !54 i32 @double_vector_size(ptr)

declare !rt !55 void @double_vector_free(ptr)

!0 = !{!"Vec::Int.init0:rt:pr:27"}
!1 = !{!"Vec::Int.add:rt:pr:27"}
!2 = !{!"Vec::Int.get:rt:pr:28"}
!3 = !{!"Vec::Int.set:rt:pr:27"}
!4 = !{!"Vec::Int.remove:rt:pr:27"}
!5 = !{!"Vec::Int.size:rt:pr:28"}
!6 = !{!"Vec::Int.free:rt:pr:27"}
!7 = !{!"Vec::Bool.init0:rt:pr:27"}
!8 = !{!"Vec::Bool.add:rt:pr:27"}
!9 = !{!"Vec::Bool.get:rt:pr:34"}
!10 = !{!"Vec::Bool.set:rt:pr:27"}
!11 = !{!"Vec::Bool.remove:rt:pr:27"}
!12 = !{!"Vec::Bool.size:rt:pr:28"}
!13 = !{!"Vec::Bool.free:rt:pr:27"}
!14 = !{!"Vec::String.init0:rt:pr:27"}
!15 = !{!"Vec::String.add:rt:pr:27"}
!16 = !{!"Vec::String.get:rt:pr:33"}
!17 = !{!"Vec::String.set:rt:pr:27"}
!18 = !{!"Vec::String.remove:rt:pr:27"}
!19 = !{!"Vec::String.size:rt:pr:28"}
!20 = !{!"Vec::String.free:rt:pr:27"}
!21 = !{!"Vec::Deci.init0:rt:pr:27"}
!22 = !{!"Vec::Deci.add:rt:pr:27"}
!23 = !{!"Vec::Deci.get:rt:pr:31"}
!24 = !{!"Vec::Deci.set:rt:pr:27"}
!25 = !{!"Vec::Deci.remove:rt:pr:27"}
!26 = !{!"Vec::Deci.size:rt:pr:28"}
!27 = !{!"Vec::Deci.free:rt:pr:27"}
!28 = !{!"int_vector_new:rt:pr:33"}
!29 = !{!"int_vector_add:rt:pr:27"}
!30 = !{!"int_vector_get:rt:pr:28"}
!31 = !{!"int_vector_set:rt:pr:27"}
!32 = !{!"int_vector_remove:rt:pr:27"}
!33 = !{!"int_vector_size:rt:pr:28"}
!34 = !{!"int_vector_free:rt:pr:27"}
!35 = !{!"bool_vector_new:rt:pr:33"}
!36 = !{!"bool_vector_add:rt:pr:27"}
!37 = !{!"bool_vector_set:rt:pr:27"}
!38 = !{!"bool_vector_get:rt:pr:34"}
!39 = !{!"bool_vector_remove:rt:pr:27"}
!40 = !{!"bool_vector_size:rt:pr:28"}
!41 = !{!"bool_vector_free:rt:pr:27"}
!42 = !{!"string_vector_new:rt:pr:33"}
!43 = !{!"string_vector_add:rt:pr:27"}
!44 = !{!"string_vector_set:rt:pr:27"}
!45 = !{!"string_vector_get:rt:pr:33"}
!46 = !{!"string_vector_remove:rt:pr:27"}
!47 = !{!"string_vector_size:rt:pr:28"}
!48 = !{!"string_vector_free:rt:pr:27"}
!49 = !{!"double_vector_new:rt:pr:33"}
!50 = !{!"double_vector_add:rt:pr:27"}
!51 = !{!"double_vector_set:rt:pr:27"}
!52 = !{!"double_vector_get:rt:pr:31"}
!53 = !{!"double_vector_remove:rt:pr:27"}
!54 = !{!"double_vector_size:rt:pr:28"}
!55 = !{!"double_vector_free:rt:pr:27"}
