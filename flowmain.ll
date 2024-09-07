; ModuleID = 'flowmain'
source_filename = "flowmain"

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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

define i32 @flowmain() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 ptr @strCopy(ptr, ptr)

declare !rt !1 ptr @strConcat(ptr, ptr)

declare !rt !2 i32 @strCompare(ptr, ptr)

declare !rt !3 i32 @strLength(ptr)

declare !rt !4 ptr @strToUpper(ptr)

declare !rt !5 ptr @strToLower(ptr)

declare !rt !6 ptr @strReverse(ptr)

declare !rt !7 ptr @strTrim(ptr)

declare !rt !8 ptr @strFind(ptr, ptr)

declare !rt !9 ptr @strReplace(ptr, ptr, ptr)

declare !rt !10 ptr @strSplit(ptr, ptr)

define ptr @"Str::strCopy"(ptr %0, ptr %1) !rt !11 {
entry:
  %dest = alloca ptr, align 8
  store ptr %0, ptr %dest, align 8
  %src = alloca ptr, align 8
  store ptr %1, ptr %src, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %dest1 = load ptr, ptr %dest, align 8
  %2 = load ptr, ptr %dest, align 8
  %src2 = load ptr, ptr %src, align 8
  %3 = load ptr, ptr %src, align 8
  %4 = call ptr @strCopy(ptr %2, ptr %3)
  ret ptr %4

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strConcat"(ptr %0, ptr %1) !rt !12 {
entry:
  %dest = alloca ptr, align 8
  store ptr %0, ptr %dest, align 8
  %src = alloca ptr, align 8
  store ptr %1, ptr %src, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @1

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %dest1 = load ptr, ptr %dest, align 8
  %2 = load ptr, ptr %dest, align 8
  %src2 = load ptr, ptr %src, align 8
  %3 = load ptr, ptr %src, align 8
  %4 = call ptr @strConcat(ptr %2, ptr %3)
  ret ptr %4

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

define i32 @"Str::strCompare"(ptr %0, ptr %1) !rt !13 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  %str2 = alloca ptr, align 8
  store ptr %1, ptr %str2, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %2 = load ptr, ptr %str1, align 8
  %str22 = load ptr, ptr %str2, align 8
  %3 = load ptr, ptr %str2, align 8
  %4 = call i32 @strCompare(ptr %2, ptr %3)
  ret i32 %4

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

define i32 @"Str::strLength"(ptr %0) !rt !14 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %1 = load ptr, ptr %str1, align 8
  %2 = call i32 @strLength(ptr %1)
  ret i32 %2

mergeBlock:                                       ; No predecessors!
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strToUpper"(ptr %0) !rt !15 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @2

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %1 = load ptr, ptr %str1, align 8
  %2 = call ptr @strToUpper(ptr %1)
  ret ptr %2

mergeBlock:                                       ; No predecessors!
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strToLower"(ptr %0) !rt !16 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @3

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %1 = load ptr, ptr %str1, align 8
  %2 = call ptr @strToLower(ptr %1)
  ret ptr %2

mergeBlock:                                       ; No predecessors!
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strReverse"(ptr %0) !rt !17 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @4

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %1 = load ptr, ptr %str1, align 8
  %2 = call ptr @strReverse(ptr %1)
  ret ptr %2

mergeBlock:                                       ; No predecessors!
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strTrim"(ptr %0) !rt !18 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @5

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %1 = load ptr, ptr %str1, align 8
  %2 = call ptr @strTrim(ptr %1)
  ret ptr %2

mergeBlock:                                       ; No predecessors!
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strFind"(ptr %0, ptr %1) !rt !19 {
entry:
  %haystack = alloca ptr, align 8
  store ptr %0, ptr %haystack, align 8
  %needle = alloca ptr, align 8
  store ptr %1, ptr %needle, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @6

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %haystack1 = load ptr, ptr %haystack, align 8
  %2 = load ptr, ptr %haystack, align 8
  %needle2 = load ptr, ptr %needle, align 8
  %3 = load ptr, ptr %needle, align 8
  %4 = call ptr @strFind(ptr %2, ptr %3)
  ret ptr %4

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strReplace"(ptr %0, ptr %1, ptr %2) !rt !20 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  %oldSub = alloca ptr, align 8
  store ptr %1, ptr %oldSub, align 8
  %newSub = alloca ptr, align 8
  store ptr %2, ptr %newSub, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @7

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %3 = load ptr, ptr %str1, align 8
  %oldSub2 = load ptr, ptr %oldSub, align 8
  %4 = load ptr, ptr %oldSub, align 8
  %newSub3 = load ptr, ptr %newSub, align 8
  %5 = load ptr, ptr %newSub, align 8
  %6 = call ptr @strReplace(ptr %3, ptr %4, ptr %5)
  ret ptr %6

mergeBlock:                                       ; No predecessors!
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @"Str::strSplit"(ptr %0, ptr %1) !rt !21 {
entry:
  %str1 = alloca ptr, align 8
  store ptr %0, ptr %str1, align 8
  %delim = alloca ptr, align 8
  store ptr %1, ptr %delim, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @8

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %str11 = load ptr, ptr %str1, align 8
  %2 = load ptr, ptr %str1, align 8
  %delim2 = load ptr, ptr %delim, align 8
  %3 = load ptr, ptr %delim, align 8
  %4 = call ptr @strSplit(ptr %2, ptr %3)
  ret ptr %4

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"strCopy:rt:pr:33"}
!1 = !{!"strConcat:rt:pr:33"}
!2 = !{!"strCompare:rt:pr:28"}
!3 = !{!"strLength:rt:pr:28"}
!4 = !{!"strToUpper:rt:pr:33"}
!5 = !{!"strToLower:rt:pr:33"}
!6 = !{!"strReverse:rt:pr:33"}
!7 = !{!"strTrim:rt:pr:33"}
!8 = !{!"strFind:rt:pr:33"}
!9 = !{!"strReplace:rt:pr:33"}
!10 = !{!"strSplit:rt:pr:33"}
!11 = !{!"Str::strCopy:rt:pr:33"}
!12 = !{!"Str::strConcat:rt:pr:33"}
!13 = !{!"Str::strCompare:rt:pr:28"}
!14 = !{!"Str::strLength:rt:pr:28"}
!15 = !{!"Str::strToUpper:rt:pr:33"}
!16 = !{!"Str::strToLower:rt:pr:33"}
!17 = !{!"Str::strReverse:rt:pr:33"}
!18 = !{!"Str::strTrim:rt:pr:33"}
!19 = !{!"Str::strFind:rt:pr:33"}
!20 = !{!"Str::strReplace:rt:pr:33"}
!21 = !{!"Str::strSplit:rt:pr:33"}
