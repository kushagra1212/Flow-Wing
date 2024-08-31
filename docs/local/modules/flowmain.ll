; ModuleID = 'flowmain'
source_filename = "flowmain"

%0 = type { ptr, ptr }
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
@"Err::x" = common global [2 x %"Err::ErrorCode.0"] zeroinitializer
@res = common global ptr null
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@err = common global ptr null
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@rtStructPtr = common global %0 zeroinitializer
@"_fg_i:0" = common global i32 0
@"_fg_numberOfElementsFilled:" = common global i32 0
@2 = private unnamed_addr constant [8 x i8] c"test.fg\00", align 1
@3 = private unnamed_addr constant [3 x i8] c"rb\00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.11" = private constant ptr @5

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
  call void @"assign_<Array[2]<ObjectErr::ErrorCode.0>>:2,"(ptr @"Err::x")
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  call void @"assign_<Array[2]<ObjectErr::ErrorCode.0>>:2,"(ptr @"Err::x")
  store ptr @0, ptr @res, align 8
  store ptr @1, ptr @res, align 8
  store ptr @res, ptr @rtStructPtr, align 8
  store ptr @err, ptr getelementptr inbounds (%0, ptr @rtStructPtr, i32 0, i32 1), align 8
  %rtPtr = alloca ptr, align 8
  store i32 1, ptr @"Err::CODE", align 4
  store i32 2, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  store i32 3, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  store i32 0, ptr @"_fg_i:0", align 4
  store i32 0, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopStart-0

returnBlock:                                      ; preds = %afterIfElse
  ret i32 0

FillExpr.loopStart-0:                             ; preds = %entry
  store i32 0, ptr @"_fg_i:0", align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %0 = load i32, ptr @"_fg_i:0", align 4
  %1 = icmp slt i32 %0, 2
  %2 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %3 = icmp slt i32 %2, 2
  %4 = and i1 %1, %3
  br i1 %4, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %5 = load i32, ptr @"_fg_i:0", align 4
  %6 = getelementptr [2 x %"Err::ErrorCode.0"], ptr @"Err::x", i32 0, i32 %5
  store %"Err::ErrorCode.0" zeroinitializer, ptr %6, align 4
  %7 = load i32, ptr @"_fg_i:0", align 4
  %8 = add i32 %7, 1
  store i32 %8, ptr @"_fg_i:0", align 4
  %9 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %10 = add i32 %9, 1
  store i32 %10, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %11 = call i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module()
  call void @"File::read"(ptr @rtStructPtr, ptr @2, ptr @3)
  %12 = load ptr, ptr @err, align 8
  %13 = icmp ne ptr %12, null
  br i1 %13, label %then, label %else

then:                                             ; preds = %FillExpr.exit
  br label %nestedBlock

else:                                             ; preds = %FillExpr.exit
  br label %nestedBlock2

afterIfElse:                                      ; preds = %afterNestedBlock1, %afterNestedBlock
  br label %returnBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  br label %afterIfElse

nestedBlock:                                      ; preds = %then
  %14 = load ptr, ptr @err, align 8
  %15 = getelementptr inbounds %"Err::Result", ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = getelementptr inbounds %"Err::Result::VTableType", ptr %16, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  call void %18(ptr %rtPtr, ptr @err)
  %19 = load ptr, ptr %rtPtr, align 8
  %20 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %20, ptr %19)
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock

afterNestedBlock1:                                ; preds = %checkContinueBlock3, %nestedBlock2
  br label %afterIfElse

nestedBlock2:                                     ; preds = %else
  %res = load ptr, ptr @res, align 8
  %23 = load ptr, ptr @res, align 8
  %24 = load ptr, ptr @"%s.11", align 8
  call void (ptr, ...) @printf(ptr %24, ptr %23)
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock3, label %afterNestedBlock1

checkContinueBlock3:                              ; preds = %nestedBlock2
  br label %afterNestedBlock1
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

declare i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module()

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

define internal void @"assign_<Array[2]<ObjectErr::ErrorCode.0>>:2,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %AssignExpr.loopStart-0

AssignExpr.loopStart-0:                           ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  br label %AssignExpr.loopCmp-0

AssignExpr.loopCmp-0:                             ; preds = %AssignExpr.loopBody-0, %AssignExpr.loopStart-0
  %1 = load i32, ptr %"0_i", align 4
  %2 = icmp slt i32 %1, 2
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 2
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [2 x %"Err::ErrorCode.0"], ptr %0, i32 0, i32 %6
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr %7)
  %8 = load i32, ptr %"0_i", align 4
  %9 = add i32 %8, 1
  store i32 %9, ptr %"0_i", align 4
  %10 = load i32, ptr %numberOfElementsFilled, align 4
  %11 = add i32 %10, 1
  store i32 %11, ptr %numberOfElementsFilled, align 4
  br label %AssignExpr.loopCmp-0

AssignExpr.loopEnd-0:                             ; preds = %AssignExpr.loopCmp-0
  br label %AssignExpr.exit

AssignExpr.exit:                                  ; preds = %AssignExpr.loopEnd-0
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
