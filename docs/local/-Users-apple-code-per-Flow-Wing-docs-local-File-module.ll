; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-local-File-module'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-local-File-module"

@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
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

define i32 @-Users-apple-code-per-Flow-Wing-docs-local-File-module() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 ptr @fopen(ptr, ptr)

define ptr @"File::openFile"(ptr %0, ptr %1) !rt !1 {
entry:
  %fileName = alloca ptr, align 8
  %2 = load ptr, ptr %0, align 8
  store ptr %2, ptr %fileName, align 8
  %mode = alloca ptr, align 8
  store ptr %1, ptr %mode, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %fileName1 = load ptr, ptr %fileName, align 8
  %mode2 = load ptr, ptr %mode, align 8
  %3 = load ptr, ptr %mode, align 8
  %4 = call ptr @fopen(ptr %fileName, ptr %3)
  ret ptr %4

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

declare !rt !1 ptr @"File::openFile.1"(ptr, ptr)

declare !rt !2 i32 @fread(ptr, i32, i32, ptr)

define void @"File::readFile"(ptr %0, ptr %1, ptr %2) !rt !3 {
entry:
  %buffer = alloca [256 x ptr], align 8, !ET !4, !I !5
  %3 = load [256 x ptr], ptr %1, align 8
  store [256 x ptr] %3, ptr %buffer, align 8
  %file = alloca ptr, align 8
  %4 = load ptr, ptr %2, align 8
  store ptr %4, ptr %file, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %file1 = load ptr, ptr %file, align 8
  %5 = call i32 @fread(ptr %buffer, i32 0, i32 10, ptr %file)
  store i32 %5, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %6 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock
}

declare !rt !3 void @"File::readFile.2"(ptr, ptr, ptr)

!0 = !{!"fopen:rt:pr:33"}
!1 = !{!"File::openFile:rt:pr:33"}
!2 = !{!"fread:rt:pr:28"}
!3 = !{!"File::readFile:rt:pr:28"}
!4 = !{!"33"}
!5 = !{!"256:"}
