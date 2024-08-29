; ModuleID = 'flowmain'
source_filename = "flowmain"

%0 = type { ptr, ptr }
%1 = type { ptr, ptr }
%"Err::Result::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Err::ErrorCode.0" = type { i32, i32, i32 }
%"Err::Result" = type { ptr, ptr, i32, ptr }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Err::Result.fg" = common global %"Err::Result::VTableType" zeroinitializer
@"Err::CODE" = common global %"Err::ErrorCode.0" zeroinitializer
@a = common global i32 0
@b = common global i32 0
@ans = common global double 0.000000e+00
@err = common global ptr null
@rtStructPtr = common global %0 zeroinitializer
@0 = private unnamed_addr constant [20 x i8] c"Enter Value for a: \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @1
@2 = private unnamed_addr constant [20 x i8] c"Enter value for b: \00", align 1
@3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.12" = private constant ptr @3
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.13" = private constant ptr @4
@5 = private unnamed_addr constant [7 x i8] c"%0.14f\00", align 1
@"%0.14f" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.14" = private constant ptr @6
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@11 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@12 = private unnamed_addr constant [16 x i8] c"Can not divide \00", align 1
@13 = private unnamed_addr constant [8 x i8] c" with 0\00", align 1

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
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  store i32 0, ptr @a, align 4
  store i32 0, ptr @b, align 4
  store i32 0, ptr @a, align 4
  store i32 0, ptr @b, align 4
  store double 0.000000e+00, ptr @ans, align 8
  store double 0.000000e+00, ptr @ans, align 8
  store ptr @ans, ptr @rtStructPtr, align 8
  store ptr @err, ptr getelementptr inbounds (%0, ptr @rtStructPtr, i32 0, i32 1), align 8
  %rtPtr = alloca ptr, align 8
  store i32 1, ptr @"Err::CODE", align 4
  store i32 2, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  store i32 3, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  %0 = call i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module()
  %a = load i32, ptr @a, align 4
  %1 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %1, ptr @0)
  %2 = call ptr @get_input()
  %3 = call i32 @string_to_int(ptr %2)
  store i32 %3, ptr @a, align 4
  %b = load i32, ptr @b, align 4
  %4 = load ptr, ptr @"%s.12", align 8
  call void (ptr, ...) @printf(ptr %4, ptr @2)
  %5 = call ptr @get_input()
  %6 = call i32 @string_to_int(ptr %5)
  store i32 %6, ptr @b, align 4
  %a1 = load i32, ptr @a, align 4
  %b2 = load i32, ptr @b, align 4
  call void @div(ptr @rtStructPtr, ptr @a, ptr @b)
  %7 = load ptr, ptr @err, align 8
  %8 = icmp ne ptr %7, null
  %9 = icmp eq i1 %8, false
  br i1 %9, label %then, label %else

returnBlock:                                      ; preds = %afterIfElse
  ret i32 0

then:                                             ; preds = %entry
  br label %nestedBlock

else:                                             ; preds = %entry
  br label %nestedBlock4

afterIfElse:                                      ; preds = %afterNestedBlock3, %afterNestedBlock
  br label %returnBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  br label %afterIfElse

nestedBlock:                                      ; preds = %then
  %ans = load double, ptr @ans, align 8
  %10 = load double, ptr @ans, align 8
  %11 = load ptr, ptr @"%s.13", align 8
  %12 = load ptr, ptr @"%0.14f", align 8
  call void (ptr, ...) @printf(ptr %12, double %10)
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock

afterNestedBlock3:                                ; preds = %checkContinueBlock5, %nestedBlock4
  br label %afterIfElse

nestedBlock4:                                     ; preds = %else
  %15 = load ptr, ptr @err, align 8
  %16 = getelementptr inbounds %"Err::Result", ptr %15, i32 0, i32 0
  %17 = load ptr, ptr %16, align 8
  %18 = getelementptr inbounds %"Err::Result::VTableType", ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  call void %19(ptr %rtPtr, ptr @err)
  %20 = load ptr, ptr %rtPtr, align 8
  %21 = load ptr, ptr @"%s.14", align 8
  call void (ptr, ...) @printf(ptr %21, ptr %20)
  %22 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock5, label %afterNestedBlock3

checkContinueBlock5:                              ; preds = %nestedBlock4
  br label %afterNestedBlock3
}

declare !rt !0 void @"Err::Result.init1"(ptr, ptr)

declare !rt !1 void @"Err::Result.init2"(ptr, ptr, ptr)

declare !rt !2 void @"Err::Result.init3"(ptr, ptr, ptr, ptr)

declare !rt !3 void @"Err::Result.getMessage"(ptr, ptr)

declare !rt !4 void @"Err::Result.getCode"(ptr, ptr)

declare !rt !5 void @"Err::Result.getDetails"(ptr, ptr)

declare !rt !6 void @"Err::Result.withMessage"(ptr, ptr, ptr)

declare !rt !7 void @"Err::Result.withDetails"(ptr, ptr, ptr)

declare !rt !8 void @"Err::Result.toString"(ptr, ptr)

declare i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module()

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

declare void @"File::read"(ptr, ptr, ptr)

declare !rt !9 void @"File::read.1"(ptr, ptr, ptr)

declare !rt !10 i32 @ftell(ptr)

declare !rt !11 void @rewind(ptr)

declare !rt !12 i32 @fseek(ptr, i32, i32)

declare !rt !13 i32 @fread(ptr, i32, i32, ptr)

declare !rt !0 void @"Err::Result.init1.2"(ptr, ptr)

declare !rt !2 void @"Err::Result.init3.3"(ptr, ptr, ptr, ptr)

declare !rt !7 void @"Err::Result.withDetails.4"(ptr, ptr, ptr)

declare !rt !6 void @"Err::Result.withMessage.5"(ptr, ptr, ptr)

declare !rt !14 ptr @fopen(ptr, ptr)

declare !rt !3 void @"Err::Result.getMessage.6"(ptr, ptr)

declare !rt !15 ptr @calloc(i32, i32)

declare !rt !1 void @"Err::Result.init2.7"(ptr, ptr, ptr)

declare !rt !5 void @"Err::Result.getDetails.8"(ptr, ptr)

declare !rt !4 void @"Err::Result.getCode.9"(ptr, ptr)

declare !rt !8 void @"Err::Result.toString.10"(ptr, ptr)

define void @div(ptr %0, ptr %1, ptr %2) {
entry:
  %a = alloca i32, align 4
  %3 = load i32, ptr %1, align 4
  store i32 %3, ptr %a, align 4
  %b = alloca i32, align 4
  %4 = load i32, ptr %2, align 4
  store i32 %4, ptr %b, align 4
  %5 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %mergeBlock9, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %b3 = load i32, ptr %b, align 4
  %8 = load i32, ptr %b, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  br label %returnBlock8

checkContinueBlock2:                              ; preds = %mergeBlock9
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock5

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock4
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock4:                                ; preds = %checkContinueBlock6, %mergeBlock
  br label %afterIfElse

nestedBlock5:                                     ; preds = %then
  br label %returnBlock

checkContinueBlock6:                              ; preds = %mergeBlock
  br label %afterNestedBlock4

returnBlock:                                      ; preds = %nestedBlock5
  %14 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %15 = load ptr, ptr %14, align 8
  store double 0.000000e+00, ptr %15, align 8
  %16 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %17 = load ptr, ptr %16, align 8
  %18 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %18)
  %19 = getelementptr inbounds %"Err::Result", ptr %18, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %19, align 8
  %20 = load ptr, ptr %19, align 8
  %21 = getelementptr inbounds %"Err::Result::VTableType", ptr %20, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %21, align 8
  %22 = getelementptr inbounds %"Err::Result::VTableType", ptr %20, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %22, align 8
  %23 = getelementptr inbounds %"Err::Result::VTableType", ptr %20, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %23, align 8
  %24 = getelementptr inbounds %"Err::Result::VTableType", ptr %20, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %24, align 8
  %25 = getelementptr inbounds %"Err::Result::VTableType", ptr %20, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %25, align 8
  %26 = getelementptr inbounds %"Err::Result::VTableType", ptr %20, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %26, align 8
  %27 = getelementptr inbounds %"Err::Result", ptr %18, i32 0, i32 1
  store ptr @10, ptr %27, align 8
  %28 = getelementptr inbounds %"Err::Result", ptr %18, i32 0, i32 2
  store i32 0, ptr %28, align 4
  %29 = getelementptr inbounds %"Err::Result", ptr %18, i32 0, i32 3
  store ptr @11, ptr %29, align 8
  store ptr %18, ptr %17, align 8
  %a7 = load i32, ptr %a, align 4
  %30 = load i32, ptr %a, align 4
  %31 = call ptr @itos(i32 %30)
  %32 = call ptr @concat_strings(ptr @12, ptr %31)
  %33 = call ptr @concat_strings(ptr %32, ptr @13)
  store ptr %33, ptr %7, align 8
  call void @"Err::Result.init1"(ptr %7, ptr %17)
  ret void

mergeBlock:                                       ; No predecessors!
  %34 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %checkContinueBlock6, label %afterNestedBlock4

returnBlock8:                                     ; preds = %nestedBlock1
  %36 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %37 = load ptr, ptr %36, align 8
  %a10 = load i32, ptr %a, align 4
  %38 = load i32, ptr %a, align 4
  %b11 = load i32, ptr %b, align 4
  %39 = load i32, ptr %b, align 4
  %40 = sitofp i32 %38 to double
  %41 = sitofp i32 %39 to double
  %42 = fdiv double %40, %41
  store double %42, ptr %37, align 8
  %43 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %44 = load ptr, ptr %43, align 8
  ret void

mergeBlock9:                                      ; No predecessors!
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock2, label %afterNestedBlock
}

declare !rt !16 void @div.11(ptr, ptr, ptr)

define internal void @"assign_<Class<Err::Result>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 0
  store ptr @7, ptr %1, align 8
  %2 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 1
  store ptr @8, ptr %2, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 3
  store ptr @9, ptr %4, align 8
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
!9 = !{!"File::read:rt:ob:Err::Result"}
!10 = !{!"ftell:rt:pr:28"}
!11 = !{!"rewind:rt:pr:27"}
!12 = !{!"fseek:rt:pr:28"}
!13 = !{!"fread:rt:pr:28"}
!14 = !{!"fopen:rt:pr:33"}
!15 = !{!"calloc:rt:pr:33"}
!16 = !{!"div:rt:ob:Err::Result"}
