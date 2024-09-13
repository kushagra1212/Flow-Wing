; ModuleID = 'flowmain'
source_filename = "flowmain"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%0 = type { ptr, ptr }
%1 = type { ptr, ptr }
%2 = type { ptr, ptr }
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
@"Err::x" = common local_unnamed_addr global [2 x %"Err::ErrorCode.0"] zeroinitializer
@"Err::CODE" = common local_unnamed_addr global %"Err::ErrorCode.0" zeroinitializer
@"_fg_i:0" = common local_unnamed_addr global i32 0
@"_fg_numberOfElementsFilled:" = common local_unnamed_addr global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private local_unnamed_addr global [2 x i8] c"r\00"
@3 = private local_unnamed_addr global [3 x i8] c"rb\00"
@4 = private local_unnamed_addr global [1 x i8] zeroinitializer
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private local_unnamed_addr global [20 x i8] c"Invalid file mode: \00"
@11 = private local_unnamed_addr global [1 x i8] zeroinitializer
@12 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@13 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@14 = private local_unnamed_addr global [13 x i8] c" not found !\00"
@15 = private local_unnamed_addr global [1 x i8] zeroinitializer
@16 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@17 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@18 = private local_unnamed_addr global [28 x i8] c"Failed to allocate memory !\00"
@19 = private local_unnamed_addr global [1 x i8] zeroinitializer
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@22 = private local_unnamed_addr global [33 x i8] c"Failed to read the entire file '\00"
@23 = private local_unnamed_addr global [2 x i8] c"'\00"
@24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@25 = private local_unnamed_addr global [2 x i8] c"w\00"
@26 = private local_unnamed_addr global [3 x i8] c"wb\00"
@27 = private local_unnamed_addr global [2 x i8] c"a\00"
@28 = private local_unnamed_addr global [3 x i8] c"ab\00"
@29 = private local_unnamed_addr global [1 x i8] zeroinitializer
@30 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@31 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@32 = private local_unnamed_addr global [20 x i8] c"Invalid file mode: \00"
@33 = private local_unnamed_addr global [1 x i8] zeroinitializer
@34 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@35 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@36 = private local_unnamed_addr global [22 x i8] c"Failed to open file: \00"
@37 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@38 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@39 = private local_unnamed_addr global [42 x i8] c"Failed to write the entire data to file: \00"
@40 = private local_unnamed_addr global [1 x i8] zeroinitializer
@41 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@42 = private local_unnamed_addr global [2 x i8] c"w\00"
@43 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@44 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@45 = private local_unnamed_addr global [24 x i8] c"Failed to create file: \00"
@46 = private local_unnamed_addr global [1 x i8] zeroinitializer

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

define i32 @flowmain() {
entry:
  call void @"assign_<Array[2]<ObjectErr::ErrorCode.0>>:2,"(ptr @"Err::x")
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  call void @"assign_<Array[2]<ObjectErr::ErrorCode.0>>:2,"(ptr @"Err::x")
  store i32 0, ptr @"_fg_i:0", align 4
  store i32 0, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopStart-0

returnBlock:                                      ; preds = %FillExpr.exit
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
  store i32 1, ptr @"Err::CODE", align 4
  store i32 2, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  store i32 3, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  %11 = call i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-lib-mac-silicon-lib-modules-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-Users-apple-code-per-Flow-Wing-lib-mac-silicon-lib-modules-Err-module()
  br label %returnBlock
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

declare i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-lib-mac-silicon-lib-modules-..-..-..-..-..-..-..-..-..-..-..-..-..-..-..-Users-apple-code-per-Flow-Wing-lib-mac-silicon-lib-modules-Err-module()

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

declare !rt !8 void @"Err::Result.toString.1"(ptr, ptr)

declare !rt !6 void @"Err::Result.withMessage.2"(ptr, ptr, ptr)

declare !rt !5 void @"Err::Result.getDetails.3"(ptr, ptr)

declare !rt !7 void @"Err::Result.withDetails.4"(ptr, ptr, ptr)

declare !rt !4 void @"Err::Result.getCode.5"(ptr, ptr)

declare !rt !1 void @"Err::Result.init2.6"(ptr, ptr, ptr)

declare !rt !3 void @"Err::Result.getMessage.7"(ptr, ptr)

declare !rt !2 void @"Err::Result.init3.8"(ptr, ptr, ptr, ptr)

declare !rt !0 void @"Err::Result.init1.9"(ptr, ptr)

declare !rt !9 ptr @fopen(ptr, ptr)

declare !rt !10 i32 @fclose(ptr)

declare !rt !11 i32 @fread(ptr, i32, i32, ptr)

declare !rt !12 i32 @fwrite(ptr, i32, i32, ptr)

declare !rt !13 i32 @strlen(ptr)

declare !rt !14 i32 @fseek(ptr, i32, i32)

declare !rt !15 i32 @ftell(ptr)

declare !rt !16 ptr @calloc(i32, i32)

declare !rt !17 void @rewind(ptr)

define void @"File::read"(ptr %0, ptr %1, ptr %2) {
entry:
  %filePath = alloca ptr, align 8
  store ptr %1, ptr %filePath, align 8
  %mode = alloca ptr, align 8
  store ptr %2, ptr %mode, align 8
  %3 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %file = alloca ptr, align 8
  store ptr @0, ptr %file, align 8
  %SEEK_END = alloca i32, align 4
  store i32 0, ptr %SEEK_END, align 4
  %6 = alloca ptr, align 8
  %clPtr1 = alloca ptr, align 8
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %fileSize = alloca i32, align 4
  store i32 0, ptr %fileSize, align 4
  %buffer = alloca ptr, align 8
  store ptr @1, ptr %buffer, align 8
  %9 = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  %11 = alloca ptr, align 8
  %bytesRead = alloca i32, align 4
  store i32 0, ptr %bytesRead, align 4
  %12 = alloca ptr, align 8
  %clPtr3 = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock25, %mergeBlock74, %checkContinueBlock23, %afterIfElse65, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %afterIfElse52, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %nestedBlock10, %checkContinueBlock9, %afterIfElse37, %checkContinueBlock7, %nestedBlock6, %checkContinueBlock5, %nestedBlock4, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %mode26 = load ptr, ptr %mode, align 8
  %15 = load ptr, ptr %mode, align 8
  %16 = call i1 @equal_strings(ptr %15, ptr @2)
  %17 = select i1 %16, i1 false, i1 true
  %mode27 = load ptr, ptr %mode, align 8
  %18 = load ptr, ptr %mode, align 8
  %19 = call i1 @equal_strings(ptr %18, ptr @3)
  %20 = select i1 %19, i1 false, i1 true
  %21 = select i1 %17, i1 %20, i1 false
  br i1 %21, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %22 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock
  %filePath32 = load ptr, ptr %filePath, align 8
  %24 = load ptr, ptr %filePath, align 8
  %mode33 = load ptr, ptr %mode, align 8
  %25 = load ptr, ptr %mode, align 8
  %26 = call ptr @fopen(ptr %24, ptr %25)
  store ptr %26, ptr %file, align 8
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock5, label %afterNestedBlock

checkContinueBlock5:                              ; preds = %nestedBlock4
  %29 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  store i32 2, ptr %SEEK_END, align 4
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %33 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  %file34 = load ptr, ptr %file, align 8
  %35 = load ptr, ptr %file, align 8
  %36 = icmp eq ptr %35, null
  br i1 %36, label %then35, label %else36

checkContinueBlock9:                              ; preds = %afterIfElse37
  %37 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %file44 = load ptr, ptr %file, align 8
  %39 = load ptr, ptr %file, align 8
  %SEEK_END45 = load i32, ptr %SEEK_END, align 4
  %40 = load i32, ptr %SEEK_END, align 4
  %41 = call i32 @fseek(ptr %39, i32 0, i32 %40)
  %42 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %44 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %file46 = load ptr, ptr %file, align 8
  %46 = load ptr, ptr %file, align 8
  %47 = call i32 @ftell(ptr %46)
  store i32 %47, ptr %fileSize, align 4
  %48 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %50 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %file47 = load ptr, ptr %file, align 8
  %52 = load ptr, ptr %file, align 8
  call void @rewind(ptr %52)
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %55 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %fileSize48 = load i32, ptr %fileSize, align 4
  %57 = load i32, ptr %fileSize, align 4
  %58 = add i32 %57, 1
  %59 = call ptr @calloc(i32 %58, i32 4)
  store ptr %59, ptr %buffer, align 8
  %60 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %62 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %63 = icmp eq i32 %62, 0
  br i1 %63, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %buffer49 = load ptr, ptr %buffer, align 8
  %64 = load ptr, ptr %buffer, align 8
  %65 = icmp eq ptr %64, null
  br i1 %65, label %then50, label %else51

checkContinueBlock19:                             ; preds = %afterIfElse52
  %66 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %buffer58 = load ptr, ptr %buffer, align 8
  %68 = load ptr, ptr %buffer, align 8
  %fileSize59 = load i32, ptr %fileSize, align 4
  %69 = load i32, ptr %fileSize, align 4
  %file60 = load ptr, ptr %file, align 8
  %70 = load ptr, ptr %file, align 8
  %71 = call i32 @fread(ptr %68, i32 1, i32 %69, ptr %70)
  store i32 %71, ptr %bytesRead, align 4
  %72 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %74 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %bytesRead61 = load i32, ptr %bytesRead, align 4
  %76 = load i32, ptr %bytesRead, align 4
  %fileSize62 = load i32, ptr %fileSize, align 4
  %77 = load i32, ptr %fileSize, align 4
  %78 = icmp ne i32 %76, %77
  br i1 %78, label %then63, label %else64

checkContinueBlock23:                             ; preds = %afterIfElse65
  %79 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %80 = icmp eq i32 %79, 0
  br i1 %80, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  br label %returnBlock73

checkContinueBlock25:                             ; preds = %mergeBlock74
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock29

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock28
  %81 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock28:                               ; preds = %checkContinueBlock30, %mergeBlock
  br label %afterIfElse

nestedBlock29:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock30:                             ; preds = %mergeBlock
  br label %afterNestedBlock28

returnBlock:                                      ; preds = %nestedBlock29
  %83 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %84 = load ptr, ptr %83, align 8
  store ptr @4, ptr %84, align 8
  %85 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %86 = load ptr, ptr %85, align 8
  %87 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %87)
  %88 = getelementptr inbounds %"Err::Result", ptr %87, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %88, align 8
  %89 = load ptr, ptr %88, align 8
  %90 = getelementptr inbounds %"Err::Result::VTableType", ptr %89, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %90, align 8
  %91 = getelementptr inbounds %"Err::Result::VTableType", ptr %89, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %91, align 8
  %92 = getelementptr inbounds %"Err::Result::VTableType", ptr %89, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %92, align 8
  %93 = getelementptr inbounds %"Err::Result::VTableType", ptr %89, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %93, align 8
  %94 = getelementptr inbounds %"Err::Result::VTableType", ptr %89, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %94, align 8
  %95 = getelementptr inbounds %"Err::Result::VTableType", ptr %89, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %95, align 8
  %96 = getelementptr inbounds %"Err::Result", ptr %87, i32 0, i32 1
  store ptr @8, ptr %96, align 8
  %97 = getelementptr inbounds %"Err::Result", ptr %87, i32 0, i32 2
  store i32 0, ptr %97, align 4
  %98 = getelementptr inbounds %"Err::Result", ptr %87, i32 0, i32 3
  store ptr @9, ptr %98, align 8
  store ptr %87, ptr %86, align 8
  %mode31 = load ptr, ptr %mode, align 8
  %99 = load ptr, ptr %mode, align 8
  %100 = call ptr @concat_strings(ptr @10, ptr %99)
  store ptr %100, ptr %5, align 8
  %INVALID_ARGUMENT = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  call void @"Err::Result.init2"(ptr %5, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), ptr %86)
  ret void

mergeBlock:                                       ; No predecessors!
  %101 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %102 = icmp eq i32 %101, 0
  br i1 %102, label %checkContinueBlock30, label %afterNestedBlock28

then35:                                           ; preds = %nestedBlock8
  br label %nestedBlock39

else36:                                           ; preds = %nestedBlock8
  br label %afterIfElse37

afterIfElse37:                                    ; preds = %else36, %afterNestedBlock38
  %103 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %checkContinueBlock9, label %afterNestedBlock

afterNestedBlock38:                               ; preds = %checkContinueBlock40, %mergeBlock42
  br label %afterIfElse37

nestedBlock39:                                    ; preds = %then35
  br label %returnBlock41

checkContinueBlock40:                             ; preds = %mergeBlock42
  br label %afterNestedBlock38

returnBlock41:                                    ; preds = %nestedBlock39
  %105 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %106 = load ptr, ptr %105, align 8
  store ptr @11, ptr %106, align 8
  %107 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %108 = load ptr, ptr %107, align 8
  %109 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %109)
  %110 = getelementptr inbounds %"Err::Result", ptr %109, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %110, align 8
  %111 = load ptr, ptr %110, align 8
  %112 = getelementptr inbounds %"Err::Result::VTableType", ptr %111, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %112, align 8
  %113 = getelementptr inbounds %"Err::Result::VTableType", ptr %111, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %113, align 8
  %114 = getelementptr inbounds %"Err::Result::VTableType", ptr %111, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %114, align 8
  %115 = getelementptr inbounds %"Err::Result::VTableType", ptr %111, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %115, align 8
  %116 = getelementptr inbounds %"Err::Result::VTableType", ptr %111, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %116, align 8
  %117 = getelementptr inbounds %"Err::Result::VTableType", ptr %111, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %117, align 8
  %118 = getelementptr inbounds %"Err::Result", ptr %109, i32 0, i32 1
  store ptr @12, ptr %118, align 8
  %119 = getelementptr inbounds %"Err::Result", ptr %109, i32 0, i32 2
  store i32 0, ptr %119, align 4
  %120 = getelementptr inbounds %"Err::Result", ptr %109, i32 0, i32 3
  store ptr @13, ptr %120, align 8
  store ptr %109, ptr %108, align 8
  %filePath43 = load ptr, ptr %filePath, align 8
  %121 = load ptr, ptr %filePath, align 8
  %122 = call ptr @concat_strings(ptr %121, ptr @14)
  store ptr %122, ptr %8, align 8
  %NOT_FOUND = load i32, ptr @"Err::CODE", align 4
  call void @"Err::Result.init2"(ptr %8, ptr @"Err::CODE", ptr %108)
  ret void

mergeBlock42:                                     ; No predecessors!
  %123 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %124 = icmp eq i32 %123, 0
  br i1 %124, label %checkContinueBlock40, label %afterNestedBlock38

then50:                                           ; preds = %nestedBlock18
  br label %nestedBlock54

else51:                                           ; preds = %nestedBlock18
  br label %afterIfElse52

afterIfElse52:                                    ; preds = %else51, %afterNestedBlock53
  %125 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %126 = icmp eq i32 %125, 0
  br i1 %126, label %checkContinueBlock19, label %afterNestedBlock

afterNestedBlock53:                               ; preds = %checkContinueBlock55, %mergeBlock57
  br label %afterIfElse52

nestedBlock54:                                    ; preds = %then50
  br label %returnBlock56

checkContinueBlock55:                             ; preds = %mergeBlock57
  br label %afterNestedBlock53

returnBlock56:                                    ; preds = %nestedBlock54
  %127 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %128 = load ptr, ptr %127, align 8
  store ptr @15, ptr %128, align 8
  %129 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %130 = load ptr, ptr %129, align 8
  %131 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %131)
  %132 = getelementptr inbounds %"Err::Result", ptr %131, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %132, align 8
  %133 = load ptr, ptr %132, align 8
  %134 = getelementptr inbounds %"Err::Result::VTableType", ptr %133, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %134, align 8
  %135 = getelementptr inbounds %"Err::Result::VTableType", ptr %133, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %135, align 8
  %136 = getelementptr inbounds %"Err::Result::VTableType", ptr %133, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %136, align 8
  %137 = getelementptr inbounds %"Err::Result::VTableType", ptr %133, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %137, align 8
  %138 = getelementptr inbounds %"Err::Result::VTableType", ptr %133, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %138, align 8
  %139 = getelementptr inbounds %"Err::Result::VTableType", ptr %133, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %139, align 8
  %140 = getelementptr inbounds %"Err::Result", ptr %131, i32 0, i32 1
  store ptr @16, ptr %140, align 8
  %141 = getelementptr inbounds %"Err::Result", ptr %131, i32 0, i32 2
  store i32 0, ptr %141, align 4
  %142 = getelementptr inbounds %"Err::Result", ptr %131, i32 0, i32 3
  store ptr @17, ptr %142, align 8
  store ptr %131, ptr %130, align 8
  store ptr @18, ptr %11, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %11, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %130)
  ret void

mergeBlock57:                                     ; No predecessors!
  %143 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %144 = icmp eq i32 %143, 0
  br i1 %144, label %checkContinueBlock55, label %afterNestedBlock53

then63:                                           ; preds = %nestedBlock22
  br label %nestedBlock67

else64:                                           ; preds = %nestedBlock22
  br label %afterIfElse65

afterIfElse65:                                    ; preds = %else64, %afterNestedBlock66
  %145 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %146 = icmp eq i32 %145, 0
  br i1 %146, label %checkContinueBlock23, label %afterNestedBlock

afterNestedBlock66:                               ; preds = %checkContinueBlock68, %mergeBlock70
  br label %afterIfElse65

nestedBlock67:                                    ; preds = %then63
  br label %returnBlock69

checkContinueBlock68:                             ; preds = %mergeBlock70
  br label %afterNestedBlock66

returnBlock69:                                    ; preds = %nestedBlock67
  %147 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %148 = load ptr, ptr %147, align 8
  store ptr @19, ptr %148, align 8
  %149 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %150 = load ptr, ptr %149, align 8
  %151 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %151)
  %152 = getelementptr inbounds %"Err::Result", ptr %151, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %152, align 8
  %153 = load ptr, ptr %152, align 8
  %154 = getelementptr inbounds %"Err::Result::VTableType", ptr %153, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %154, align 8
  %155 = getelementptr inbounds %"Err::Result::VTableType", ptr %153, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %155, align 8
  %156 = getelementptr inbounds %"Err::Result::VTableType", ptr %153, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %156, align 8
  %157 = getelementptr inbounds %"Err::Result::VTableType", ptr %153, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %157, align 8
  %158 = getelementptr inbounds %"Err::Result::VTableType", ptr %153, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %158, align 8
  %159 = getelementptr inbounds %"Err::Result::VTableType", ptr %153, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %159, align 8
  %160 = getelementptr inbounds %"Err::Result", ptr %151, i32 0, i32 1
  store ptr @20, ptr %160, align 8
  %161 = getelementptr inbounds %"Err::Result", ptr %151, i32 0, i32 2
  store i32 0, ptr %161, align 4
  %162 = getelementptr inbounds %"Err::Result", ptr %151, i32 0, i32 3
  store ptr @21, ptr %162, align 8
  store ptr %151, ptr %150, align 8
  %filePath71 = load ptr, ptr %filePath, align 8
  %163 = load ptr, ptr %filePath, align 8
  %164 = call ptr @concat_strings(ptr @22, ptr %163)
  %165 = call ptr @concat_strings(ptr %164, ptr @23)
  store ptr %165, ptr %14, align 8
  %FAILED72 = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %14, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %150)
  ret void

mergeBlock70:                                     ; No predecessors!
  %166 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %167 = icmp eq i32 %166, 0
  br i1 %167, label %checkContinueBlock68, label %afterNestedBlock66

returnBlock73:                                    ; preds = %nestedBlock24
  %168 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %169 = load ptr, ptr %168, align 8
  %buffer75 = load ptr, ptr %buffer, align 8
  %170 = load ptr, ptr %buffer, align 8
  store ptr %170, ptr %169, align 8
  %171 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %172 = load ptr, ptr %171, align 8
  ret void

mergeBlock74:                                     ; No predecessors!
  %173 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %174 = icmp eq i32 %173, 0
  br i1 %174, label %checkContinueBlock25, label %afterNestedBlock
}

declare !rt !18 void @"File::read.10"(ptr, ptr, ptr)

define void @"File::write"(ptr %0, ptr %1, ptr %2, ptr %3) {
entry:
  %filePath = alloca ptr, align 8
  store ptr %1, ptr %filePath, align 8
  %data = alloca ptr, align 8
  store ptr %2, ptr %data, align 8
  %mode = alloca ptr, align 8
  store ptr %3, ptr %mode, align 8
  %4 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %file = alloca ptr, align 8
  store ptr @24, ptr %file, align 8
  %7 = alloca ptr, align 8
  %clPtr1 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  %len = alloca i32, align 4
  store i32 0, ptr %len, align 4
  %bytesWritten = alloca i32, align 4
  store i32 0, ptr %bytesWritten, align 4
  %10 = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %11 = alloca ptr, align 8
  %12 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock16, %mergeBlock54, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse45, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %afterIfElse30, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %mode17 = load ptr, ptr %mode, align 8
  %13 = load ptr, ptr %mode, align 8
  %14 = call i1 @equal_strings(ptr %13, ptr @25)
  %15 = select i1 %14, i1 false, i1 true
  %mode18 = load ptr, ptr %mode, align 8
  %16 = load ptr, ptr %mode, align 8
  %17 = call i1 @equal_strings(ptr %16, ptr @26)
  %18 = select i1 %17, i1 false, i1 true
  %19 = select i1 %15, i1 %18, i1 false
  %mode19 = load ptr, ptr %mode, align 8
  %20 = load ptr, ptr %mode, align 8
  %21 = call i1 @equal_strings(ptr %20, ptr @27)
  %22 = select i1 %21, i1 false, i1 true
  %23 = select i1 %19, i1 %22, i1 false
  %mode20 = load ptr, ptr %mode, align 8
  %24 = load ptr, ptr %mode, align 8
  %25 = call i1 @equal_strings(ptr %24, ptr @28)
  %26 = select i1 %25, i1 false, i1 true
  %27 = select i1 %23, i1 %26, i1 false
  br i1 %27, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock
  %filePath25 = load ptr, ptr %filePath, align 8
  %30 = load ptr, ptr %filePath, align 8
  %mode26 = load ptr, ptr %mode, align 8
  %31 = load ptr, ptr %mode, align 8
  %32 = call ptr @fopen(ptr %30, ptr %31)
  store ptr %32, ptr %file, align 8
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %35 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %file27 = load ptr, ptr %file, align 8
  %37 = load ptr, ptr %file, align 8
  %38 = icmp eq ptr %37, null
  br i1 %38, label %then28, label %else29

checkContinueBlock6:                              ; preds = %afterIfElse30
  %39 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %data37 = load ptr, ptr %data, align 8
  %41 = load ptr, ptr %data, align 8
  %42 = call i32 @strlen(ptr %41)
  store i32 %42, ptr %len, align 4
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %45 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %data38 = load ptr, ptr %data, align 8
  %47 = load ptr, ptr %data, align 8
  %len39 = load i32, ptr %len, align 4
  %48 = load i32, ptr %len, align 4
  %file40 = load ptr, ptr %file, align 8
  %49 = load ptr, ptr %file, align 8
  %50 = call i32 @fwrite(ptr %47, i32 1, i32 %48, ptr %49)
  store i32 %50, ptr %bytesWritten, align 4
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %53 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %bytesWritten41 = load i32, ptr %bytesWritten, align 4
  %55 = load i32, ptr %bytesWritten, align 4
  %len42 = load i32, ptr %len, align 4
  %56 = load i32, ptr %len, align 4
  %57 = icmp ne i32 %55, %56
  br i1 %57, label %then43, label %else44

checkContinueBlock12:                             ; preds = %afterIfElse45
  %58 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %59 = icmp eq i32 %58, 0
  br i1 %59, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %file52 = load ptr, ptr %file, align 8
  %60 = load ptr, ptr %file, align 8
  %61 = call i32 @fclose(ptr %60)
  %62 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %63 = icmp eq i32 %62, 0
  br i1 %63, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %64 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  br label %returnBlock53

checkContinueBlock16:                             ; preds = %mergeBlock54
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock22

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock21
  %66 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock21:                               ; preds = %checkContinueBlock23, %mergeBlock
  br label %afterIfElse

nestedBlock22:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock23:                             ; preds = %mergeBlock
  br label %afterNestedBlock21

returnBlock:                                      ; preds = %nestedBlock22
  %68 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %69 = load ptr, ptr %68, align 8
  store ptr @29, ptr %69, align 8
  %70 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %71 = load ptr, ptr %70, align 8
  %72 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %72)
  %73 = getelementptr inbounds %"Err::Result", ptr %72, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %73, align 8
  %74 = load ptr, ptr %73, align 8
  %75 = getelementptr inbounds %"Err::Result::VTableType", ptr %74, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %75, align 8
  %76 = getelementptr inbounds %"Err::Result::VTableType", ptr %74, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %76, align 8
  %77 = getelementptr inbounds %"Err::Result::VTableType", ptr %74, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %77, align 8
  %78 = getelementptr inbounds %"Err::Result::VTableType", ptr %74, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %78, align 8
  %79 = getelementptr inbounds %"Err::Result::VTableType", ptr %74, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %79, align 8
  %80 = getelementptr inbounds %"Err::Result::VTableType", ptr %74, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %80, align 8
  %81 = getelementptr inbounds %"Err::Result", ptr %72, i32 0, i32 1
  store ptr @30, ptr %81, align 8
  %82 = getelementptr inbounds %"Err::Result", ptr %72, i32 0, i32 2
  store i32 0, ptr %82, align 4
  %83 = getelementptr inbounds %"Err::Result", ptr %72, i32 0, i32 3
  store ptr @31, ptr %83, align 8
  store ptr %72, ptr %71, align 8
  %mode24 = load ptr, ptr %mode, align 8
  %84 = load ptr, ptr %mode, align 8
  %85 = call ptr @concat_strings(ptr @32, ptr %84)
  store ptr %85, ptr %6, align 8
  %INVALID_ARGUMENT = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  call void @"Err::Result.init2"(ptr %6, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), ptr %71)
  ret void

mergeBlock:                                       ; No predecessors!
  %86 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %checkContinueBlock23, label %afterNestedBlock21

then28:                                           ; preds = %nestedBlock5
  br label %nestedBlock32

else29:                                           ; preds = %nestedBlock5
  br label %afterIfElse30

afterIfElse30:                                    ; preds = %else29, %afterNestedBlock31
  %88 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %89 = icmp eq i32 %88, 0
  br i1 %89, label %checkContinueBlock6, label %afterNestedBlock

afterNestedBlock31:                               ; preds = %checkContinueBlock33, %mergeBlock35
  br label %afterIfElse30

nestedBlock32:                                    ; preds = %then28
  br label %returnBlock34

checkContinueBlock33:                             ; preds = %mergeBlock35
  br label %afterNestedBlock31

returnBlock34:                                    ; preds = %nestedBlock32
  %90 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %91 = load ptr, ptr %90, align 8
  store ptr @33, ptr %91, align 8
  %92 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %93 = load ptr, ptr %92, align 8
  %94 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %94)
  %95 = getelementptr inbounds %"Err::Result", ptr %94, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %95, align 8
  %96 = load ptr, ptr %95, align 8
  %97 = getelementptr inbounds %"Err::Result::VTableType", ptr %96, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %97, align 8
  %98 = getelementptr inbounds %"Err::Result::VTableType", ptr %96, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %98, align 8
  %99 = getelementptr inbounds %"Err::Result::VTableType", ptr %96, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %99, align 8
  %100 = getelementptr inbounds %"Err::Result::VTableType", ptr %96, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %100, align 8
  %101 = getelementptr inbounds %"Err::Result::VTableType", ptr %96, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %101, align 8
  %102 = getelementptr inbounds %"Err::Result::VTableType", ptr %96, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %102, align 8
  %103 = getelementptr inbounds %"Err::Result", ptr %94, i32 0, i32 1
  store ptr @34, ptr %103, align 8
  %104 = getelementptr inbounds %"Err::Result", ptr %94, i32 0, i32 2
  store i32 0, ptr %104, align 4
  %105 = getelementptr inbounds %"Err::Result", ptr %94, i32 0, i32 3
  store ptr @35, ptr %105, align 8
  store ptr %94, ptr %93, align 8
  %filePath36 = load ptr, ptr %filePath, align 8
  %106 = load ptr, ptr %filePath, align 8
  %107 = call ptr @concat_strings(ptr @36, ptr %106)
  store ptr %107, ptr %9, align 8
  %NOT_FOUND = load i32, ptr @"Err::CODE", align 4
  call void @"Err::Result.init2"(ptr %9, ptr @"Err::CODE", ptr %93)
  ret void

mergeBlock35:                                     ; No predecessors!
  %108 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %checkContinueBlock33, label %afterNestedBlock31

then43:                                           ; preds = %nestedBlock11
  br label %nestedBlock47

else44:                                           ; preds = %nestedBlock11
  br label %afterIfElse45

afterIfElse45:                                    ; preds = %else44, %afterNestedBlock46
  %110 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %111 = icmp eq i32 %110, 0
  br i1 %111, label %checkContinueBlock12, label %afterNestedBlock

afterNestedBlock46:                               ; preds = %checkContinueBlock48, %mergeBlock50
  br label %afterIfElse45

nestedBlock47:                                    ; preds = %then43
  br label %returnBlock49

checkContinueBlock48:                             ; preds = %mergeBlock50
  br label %afterNestedBlock46

returnBlock49:                                    ; preds = %nestedBlock47
  %112 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %112)
  %113 = getelementptr inbounds %"Err::Result", ptr %112, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %113, align 8
  %114 = load ptr, ptr %113, align 8
  %115 = getelementptr inbounds %"Err::Result::VTableType", ptr %114, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %115, align 8
  %116 = getelementptr inbounds %"Err::Result::VTableType", ptr %114, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %116, align 8
  %117 = getelementptr inbounds %"Err::Result::VTableType", ptr %114, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %117, align 8
  %118 = getelementptr inbounds %"Err::Result::VTableType", ptr %114, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %118, align 8
  %119 = getelementptr inbounds %"Err::Result::VTableType", ptr %114, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %119, align 8
  %120 = getelementptr inbounds %"Err::Result::VTableType", ptr %114, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %120, align 8
  %121 = getelementptr inbounds %"Err::Result", ptr %112, i32 0, i32 1
  store ptr @37, ptr %121, align 8
  %122 = getelementptr inbounds %"Err::Result", ptr %112, i32 0, i32 2
  store i32 0, ptr %122, align 4
  %123 = getelementptr inbounds %"Err::Result", ptr %112, i32 0, i32 3
  store ptr @38, ptr %123, align 8
  store ptr %112, ptr %0, align 8
  %filePath51 = load ptr, ptr %filePath, align 8
  %124 = load ptr, ptr %filePath, align 8
  %125 = call ptr @concat_strings(ptr @39, ptr %124)
  store ptr %125, ptr %12, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %12, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %0)
  ret void

mergeBlock50:                                     ; No predecessors!
  %126 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %127 = icmp eq i32 %126, 0
  br i1 %127, label %checkContinueBlock48, label %afterNestedBlock46

returnBlock53:                                    ; preds = %nestedBlock15
  %128 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %129 = load ptr, ptr %128, align 8
  store ptr @40, ptr %129, align 8
  %130 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %131 = load ptr, ptr %130, align 8
  ret void

mergeBlock54:                                     ; No predecessors!
  %132 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %133 = icmp eq i32 %132, 0
  br i1 %133, label %checkContinueBlock16, label %afterNestedBlock
}

declare !rt !19 void @"File::write.11"(ptr, ptr, ptr, ptr)

define void @"File::createFile"(ptr %0, ptr %1) {
entry:
  %filePath = alloca ptr, align 8
  store ptr %1, ptr %filePath, align 8
  %file = alloca ptr, align 8
  store ptr @41, ptr %file, align 8
  %2 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %mergeBlock15, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %filePath7 = load ptr, ptr %filePath, align 8
  %5 = load ptr, ptr %filePath, align 8
  %6 = call ptr @fopen(ptr %5, ptr @42)
  store ptr %6, ptr %file, align 8
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %9 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %file8 = load ptr, ptr %file, align 8
  %11 = load ptr, ptr %file, align 8
  %12 = icmp eq ptr %11, null
  br i1 %12, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  %13 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %file13 = load ptr, ptr %file, align 8
  %15 = load ptr, ptr %file, align 8
  %16 = call i32 @fclose(ptr %15)
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  br label %returnBlock14

checkContinueBlock6:                              ; preds = %mergeBlock15
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock10

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock9
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock9:                                ; preds = %checkContinueBlock11, %mergeBlock
  br label %afterIfElse

nestedBlock10:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock11:                             ; preds = %mergeBlock
  br label %afterNestedBlock9

returnBlock:                                      ; preds = %nestedBlock10
  %23 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %23)
  %24 = getelementptr inbounds %"Err::Result", ptr %23, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %24, align 8
  %25 = load ptr, ptr %24, align 8
  %26 = getelementptr inbounds %"Err::Result::VTableType", ptr %25, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %26, align 8
  %27 = getelementptr inbounds %"Err::Result::VTableType", ptr %25, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %27, align 8
  %28 = getelementptr inbounds %"Err::Result::VTableType", ptr %25, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %28, align 8
  %29 = getelementptr inbounds %"Err::Result::VTableType", ptr %25, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %29, align 8
  %30 = getelementptr inbounds %"Err::Result::VTableType", ptr %25, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %30, align 8
  %31 = getelementptr inbounds %"Err::Result::VTableType", ptr %25, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %31, align 8
  %32 = getelementptr inbounds %"Err::Result", ptr %23, i32 0, i32 1
  store ptr @43, ptr %32, align 8
  %33 = getelementptr inbounds %"Err::Result", ptr %23, i32 0, i32 2
  store i32 0, ptr %33, align 4
  %34 = getelementptr inbounds %"Err::Result", ptr %23, i32 0, i32 3
  store ptr @44, ptr %34, align 8
  store ptr %23, ptr %0, align 8
  %filePath12 = load ptr, ptr %filePath, align 8
  %35 = load ptr, ptr %filePath, align 8
  %36 = call ptr @concat_strings(ptr @45, ptr %35)
  store ptr %36, ptr %4, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %4, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %0)
  ret void

mergeBlock:                                       ; No predecessors!
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock11, label %afterNestedBlock9

returnBlock14:                                    ; preds = %nestedBlock5
  %39 = getelementptr inbounds %2, ptr %0, i32 0, i32 0
  %40 = load ptr, ptr %39, align 8
  store ptr @46, ptr %40, align 8
  %41 = getelementptr inbounds %2, ptr %0, i32 0, i32 1
  %42 = load ptr, ptr %41, align 8
  ret void

mergeBlock15:                                     ; No predecessors!
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock6, label %afterNestedBlock
}

declare !rt !20 void @"File::createFile.12"(ptr, ptr)

define internal void @"assign_<Class<Err::Result>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 0
  store ptr @5, ptr %1, align 8
  %2 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 1
  store ptr @6, ptr %2, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 3
  store ptr @7, ptr %4, align 8
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
!9 = !{!"fopen:rt:pr:33"}
!10 = !{!"fclose:rt:pr:28"}
!11 = !{!"fread:rt:pr:28"}
!12 = !{!"fwrite:rt:pr:28"}
!13 = !{!"strlen:rt:pr:28"}
!14 = !{!"fseek:rt:pr:28"}
!15 = !{!"ftell:rt:pr:28"}
!16 = !{!"calloc:rt:pr:33"}
!17 = !{!"rewind:rt:pr:27"}
!18 = !{!"File::read:rt:ob:Err::Result"}
!19 = !{!"File::write:rt:ob:Err::Result"}
!20 = !{!"File::createFile:rt:ob:Err::Result"}
