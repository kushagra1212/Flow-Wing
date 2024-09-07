; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module"

%0 = type { ptr, ptr }
%1 = type { ptr, ptr }
%2 = type { ptr, ptr }
%"Err::Result::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Err::ErrorCode.0" = type { i32, i32, i32 }
%"Err::Result" = type { ptr, ptr, i32, ptr }

@-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Err::Result.fg" = common global %"Err::Result::VTableType" zeroinitializer
@"Err::x" = common global [2 x %"Err::ErrorCode.0"] zeroinitializer
@"Err::CODE" = common global %"Err::ErrorCode.0" zeroinitializer
@"_fg_i:0" = common global i32 0
@"_fg_numberOfElementsFilled:" = common global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@3 = private unnamed_addr constant [3 x i8] c"rb\00", align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [20 x i8] c"Invalid file mode: \00", align 1
@11 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@12 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@13 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@14 = private unnamed_addr constant [13 x i8] c" not found !\00", align 1
@15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@16 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@17 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@18 = private unnamed_addr constant [28 x i8] c"Failed to allocate memory !\00", align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@22 = private unnamed_addr constant [33 x i8] c"Failed to read the entire file '\00", align 1
@23 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@25 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@26 = private unnamed_addr constant [3 x i8] c"wb\00", align 1
@27 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@28 = private unnamed_addr constant [3 x i8] c"ab\00", align 1
@29 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@30 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@31 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@32 = private unnamed_addr constant [20 x i8] c"Invalid file mode: \00", align 1
@33 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@34 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@35 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@36 = private unnamed_addr constant [22 x i8] c"Failed to open file: \00", align 1
@37 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@38 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@39 = private unnamed_addr constant [42 x i8] c"Failed to write the entire data to file: \00", align 1
@40 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@41 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@42 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@43 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@44 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@45 = private unnamed_addr constant [24 x i8] c"Failed to create file: \00", align 1
@46 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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

define i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module() {
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
  %11 = call i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module()
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

declare i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module()

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
  %6 = alloca ptr, align 8
  %file = alloca ptr, align 8
  store ptr @0, ptr %file, align 8
  %SEEK_END = alloca i32, align 4
  store i32 0, ptr %SEEK_END, align 4
  %7 = alloca ptr, align 8
  %clPtr1 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  %fileSize = alloca i32, align 4
  store i32 0, ptr %fileSize, align 4
  %buffer = alloca ptr, align 8
  store ptr @1, ptr %buffer, align 8
  %11 = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %12 = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca ptr, align 8
  %bytesRead = alloca i32, align 4
  store i32 0, ptr %bytesRead, align 4
  %15 = alloca ptr, align 8
  %clPtr3 = alloca ptr, align 8
  %16 = alloca ptr, align 8
  %17 = alloca ptr, align 8
  %18 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock25, %mergeBlock74, %checkContinueBlock23, %afterIfElse65, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %afterIfElse52, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %nestedBlock10, %checkContinueBlock9, %afterIfElse37, %checkContinueBlock7, %nestedBlock6, %checkContinueBlock5, %nestedBlock4, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %mode26 = load ptr, ptr %mode, align 8
  %19 = load ptr, ptr %mode, align 8
  %20 = call i1 @equal_strings(ptr %19, ptr @2)
  %21 = select i1 %20, i1 false, i1 true
  %mode27 = load ptr, ptr %mode, align 8
  %22 = load ptr, ptr %mode, align 8
  %23 = call i1 @equal_strings(ptr %22, ptr @3)
  %24 = select i1 %23, i1 false, i1 true
  %25 = select i1 %21, i1 %24, i1 false
  br i1 %25, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %26 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock
  %filePath32 = load ptr, ptr %filePath, align 8
  %28 = load ptr, ptr %filePath, align 8
  %mode33 = load ptr, ptr %mode, align 8
  %29 = load ptr, ptr %mode, align 8
  %30 = call ptr @fopen(ptr %28, ptr %29)
  store ptr %30, ptr %file, align 8
  %31 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock5, label %afterNestedBlock

checkContinueBlock5:                              ; preds = %nestedBlock4
  %33 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  store i32 2, ptr %SEEK_END, align 4
  %35 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %37 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  %file34 = load ptr, ptr %file, align 8
  %39 = load ptr, ptr %file, align 8
  %40 = icmp eq ptr %39, null
  br i1 %40, label %then35, label %else36

checkContinueBlock9:                              ; preds = %afterIfElse37
  %41 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %file44 = load ptr, ptr %file, align 8
  %43 = load ptr, ptr %file, align 8
  %SEEK_END45 = load i32, ptr %SEEK_END, align 4
  %44 = load i32, ptr %SEEK_END, align 4
  %45 = call i32 @fseek(ptr %43, i32 0, i32 %44)
  %46 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %48 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %file46 = load ptr, ptr %file, align 8
  %50 = load ptr, ptr %file, align 8
  %51 = call i32 @ftell(ptr %50)
  store i32 %51, ptr %fileSize, align 4
  %52 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %54 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %file47 = load ptr, ptr %file, align 8
  %56 = load ptr, ptr %file, align 8
  call void @rewind(ptr %56)
  %57 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %59 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %fileSize48 = load i32, ptr %fileSize, align 4
  %61 = load i32, ptr %fileSize, align 4
  %62 = add i32 %61, 1
  %63 = call ptr @calloc(i32 %62, i32 4)
  store ptr %63, ptr %buffer, align 8
  %64 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %66 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %buffer49 = load ptr, ptr %buffer, align 8
  %68 = load ptr, ptr %buffer, align 8
  %69 = icmp eq ptr %68, null
  br i1 %69, label %then50, label %else51

checkContinueBlock19:                             ; preds = %afterIfElse52
  %70 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %buffer58 = load ptr, ptr %buffer, align 8
  %72 = load ptr, ptr %buffer, align 8
  %fileSize59 = load i32, ptr %fileSize, align 4
  %73 = load i32, ptr %fileSize, align 4
  %file60 = load ptr, ptr %file, align 8
  %74 = load ptr, ptr %file, align 8
  %75 = call i32 @fread(ptr %72, i32 1, i32 %73, ptr %74)
  store i32 %75, ptr %bytesRead, align 4
  %76 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %77 = icmp eq i32 %76, 0
  br i1 %77, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %78 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %bytesRead61 = load i32, ptr %bytesRead, align 4
  %80 = load i32, ptr %bytesRead, align 4
  %fileSize62 = load i32, ptr %fileSize, align 4
  %81 = load i32, ptr %fileSize, align 4
  %82 = icmp ne i32 %80, %81
  br i1 %82, label %then63, label %else64

checkContinueBlock23:                             ; preds = %afterIfElse65
  %83 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  br label %returnBlock73

checkContinueBlock25:                             ; preds = %mergeBlock74
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock29

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock28
  %85 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock28:                               ; preds = %checkContinueBlock30, %mergeBlock
  br label %afterIfElse

nestedBlock29:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock30:                             ; preds = %mergeBlock
  br label %afterNestedBlock28

returnBlock:                                      ; preds = %nestedBlock29
  %87 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %88 = load ptr, ptr %87, align 8
  store ptr @4, ptr %88, align 8
  %89 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %90 = load ptr, ptr %89, align 8
  %91 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %91)
  %92 = getelementptr inbounds %"Err::Result", ptr %91, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %92, align 8
  %93 = load ptr, ptr %92, align 8
  %94 = getelementptr inbounds %"Err::Result::VTableType", ptr %93, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %94, align 8
  %95 = getelementptr inbounds %"Err::Result::VTableType", ptr %93, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %95, align 8
  %96 = getelementptr inbounds %"Err::Result::VTableType", ptr %93, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %96, align 8
  %97 = getelementptr inbounds %"Err::Result::VTableType", ptr %93, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %97, align 8
  %98 = getelementptr inbounds %"Err::Result::VTableType", ptr %93, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %98, align 8
  %99 = getelementptr inbounds %"Err::Result::VTableType", ptr %93, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %99, align 8
  %100 = getelementptr inbounds %"Err::Result", ptr %91, i32 0, i32 1
  store ptr @8, ptr %100, align 8
  %101 = getelementptr inbounds %"Err::Result", ptr %91, i32 0, i32 2
  store i32 0, ptr %101, align 4
  %102 = getelementptr inbounds %"Err::Result", ptr %91, i32 0, i32 3
  store ptr @9, ptr %102, align 8
  store ptr %91, ptr %90, align 8
  %mode31 = load ptr, ptr %mode, align 8
  %103 = load ptr, ptr %mode, align 8
  %104 = call ptr @concat_strings(ptr @10, ptr %103)
  store ptr %104, ptr %6, align 8
  %INVALID_ARGUMENT = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  call void @"Err::Result.init2"(ptr %6, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), ptr %90)
  ret void

mergeBlock:                                       ; No predecessors!
  %105 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %106 = icmp eq i32 %105, 0
  br i1 %106, label %checkContinueBlock30, label %afterNestedBlock28

then35:                                           ; preds = %nestedBlock8
  br label %nestedBlock39

else36:                                           ; preds = %nestedBlock8
  br label %afterIfElse37

afterIfElse37:                                    ; preds = %else36, %afterNestedBlock38
  %107 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %checkContinueBlock9, label %afterNestedBlock

afterNestedBlock38:                               ; preds = %checkContinueBlock40, %mergeBlock42
  br label %afterIfElse37

nestedBlock39:                                    ; preds = %then35
  br label %returnBlock41

checkContinueBlock40:                             ; preds = %mergeBlock42
  br label %afterNestedBlock38

returnBlock41:                                    ; preds = %nestedBlock39
  %109 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %110 = load ptr, ptr %109, align 8
  store ptr @11, ptr %110, align 8
  %111 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %112 = load ptr, ptr %111, align 8
  %113 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %113)
  %114 = getelementptr inbounds %"Err::Result", ptr %113, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %114, align 8
  %115 = load ptr, ptr %114, align 8
  %116 = getelementptr inbounds %"Err::Result::VTableType", ptr %115, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %116, align 8
  %117 = getelementptr inbounds %"Err::Result::VTableType", ptr %115, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %117, align 8
  %118 = getelementptr inbounds %"Err::Result::VTableType", ptr %115, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %118, align 8
  %119 = getelementptr inbounds %"Err::Result::VTableType", ptr %115, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %119, align 8
  %120 = getelementptr inbounds %"Err::Result::VTableType", ptr %115, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %120, align 8
  %121 = getelementptr inbounds %"Err::Result::VTableType", ptr %115, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %121, align 8
  %122 = getelementptr inbounds %"Err::Result", ptr %113, i32 0, i32 1
  store ptr @12, ptr %122, align 8
  %123 = getelementptr inbounds %"Err::Result", ptr %113, i32 0, i32 2
  store i32 0, ptr %123, align 4
  %124 = getelementptr inbounds %"Err::Result", ptr %113, i32 0, i32 3
  store ptr @13, ptr %124, align 8
  store ptr %113, ptr %112, align 8
  %filePath43 = load ptr, ptr %filePath, align 8
  %125 = load ptr, ptr %filePath, align 8
  %126 = call ptr @concat_strings(ptr %125, ptr @14)
  store ptr %126, ptr %10, align 8
  %NOT_FOUND = load i32, ptr @"Err::CODE", align 4
  call void @"Err::Result.init2"(ptr %10, ptr @"Err::CODE", ptr %112)
  ret void

mergeBlock42:                                     ; No predecessors!
  %127 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %checkContinueBlock40, label %afterNestedBlock38

then50:                                           ; preds = %nestedBlock18
  br label %nestedBlock54

else51:                                           ; preds = %nestedBlock18
  br label %afterIfElse52

afterIfElse52:                                    ; preds = %else51, %afterNestedBlock53
  %129 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %checkContinueBlock19, label %afterNestedBlock

afterNestedBlock53:                               ; preds = %checkContinueBlock55, %mergeBlock57
  br label %afterIfElse52

nestedBlock54:                                    ; preds = %then50
  br label %returnBlock56

checkContinueBlock55:                             ; preds = %mergeBlock57
  br label %afterNestedBlock53

returnBlock56:                                    ; preds = %nestedBlock54
  %131 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %132 = load ptr, ptr %131, align 8
  store ptr @15, ptr %132, align 8
  %133 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %134 = load ptr, ptr %133, align 8
  %135 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %135)
  %136 = getelementptr inbounds %"Err::Result", ptr %135, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %136, align 8
  %137 = load ptr, ptr %136, align 8
  %138 = getelementptr inbounds %"Err::Result::VTableType", ptr %137, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %138, align 8
  %139 = getelementptr inbounds %"Err::Result::VTableType", ptr %137, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %139, align 8
  %140 = getelementptr inbounds %"Err::Result::VTableType", ptr %137, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %140, align 8
  %141 = getelementptr inbounds %"Err::Result::VTableType", ptr %137, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %141, align 8
  %142 = getelementptr inbounds %"Err::Result::VTableType", ptr %137, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %142, align 8
  %143 = getelementptr inbounds %"Err::Result::VTableType", ptr %137, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %143, align 8
  %144 = getelementptr inbounds %"Err::Result", ptr %135, i32 0, i32 1
  store ptr @16, ptr %144, align 8
  %145 = getelementptr inbounds %"Err::Result", ptr %135, i32 0, i32 2
  store i32 0, ptr %145, align 4
  %146 = getelementptr inbounds %"Err::Result", ptr %135, i32 0, i32 3
  store ptr @17, ptr %146, align 8
  store ptr %135, ptr %134, align 8
  store ptr @18, ptr %14, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %14, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %134)
  ret void

mergeBlock57:                                     ; No predecessors!
  %147 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %148 = icmp eq i32 %147, 0
  br i1 %148, label %checkContinueBlock55, label %afterNestedBlock53

then63:                                           ; preds = %nestedBlock22
  br label %nestedBlock67

else64:                                           ; preds = %nestedBlock22
  br label %afterIfElse65

afterIfElse65:                                    ; preds = %else64, %afterNestedBlock66
  %149 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %150 = icmp eq i32 %149, 0
  br i1 %150, label %checkContinueBlock23, label %afterNestedBlock

afterNestedBlock66:                               ; preds = %checkContinueBlock68, %mergeBlock70
  br label %afterIfElse65

nestedBlock67:                                    ; preds = %then63
  br label %returnBlock69

checkContinueBlock68:                             ; preds = %mergeBlock70
  br label %afterNestedBlock66

returnBlock69:                                    ; preds = %nestedBlock67
  %151 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %152 = load ptr, ptr %151, align 8
  store ptr @19, ptr %152, align 8
  %153 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %154 = load ptr, ptr %153, align 8
  %155 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %155)
  %156 = getelementptr inbounds %"Err::Result", ptr %155, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %156, align 8
  %157 = load ptr, ptr %156, align 8
  %158 = getelementptr inbounds %"Err::Result::VTableType", ptr %157, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %158, align 8
  %159 = getelementptr inbounds %"Err::Result::VTableType", ptr %157, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %159, align 8
  %160 = getelementptr inbounds %"Err::Result::VTableType", ptr %157, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %160, align 8
  %161 = getelementptr inbounds %"Err::Result::VTableType", ptr %157, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %161, align 8
  %162 = getelementptr inbounds %"Err::Result::VTableType", ptr %157, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %162, align 8
  %163 = getelementptr inbounds %"Err::Result::VTableType", ptr %157, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %163, align 8
  %164 = getelementptr inbounds %"Err::Result", ptr %155, i32 0, i32 1
  store ptr @20, ptr %164, align 8
  %165 = getelementptr inbounds %"Err::Result", ptr %155, i32 0, i32 2
  store i32 0, ptr %165, align 4
  %166 = getelementptr inbounds %"Err::Result", ptr %155, i32 0, i32 3
  store ptr @21, ptr %166, align 8
  store ptr %155, ptr %154, align 8
  %filePath71 = load ptr, ptr %filePath, align 8
  %167 = load ptr, ptr %filePath, align 8
  %168 = call ptr @concat_strings(ptr @22, ptr %167)
  %169 = call ptr @concat_strings(ptr %168, ptr @23)
  store ptr %169, ptr %18, align 8
  %FAILED72 = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %18, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %154)
  ret void

mergeBlock70:                                     ; No predecessors!
  %170 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %checkContinueBlock68, label %afterNestedBlock66

returnBlock73:                                    ; preds = %nestedBlock24
  %172 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %173 = load ptr, ptr %172, align 8
  %buffer75 = load ptr, ptr %buffer, align 8
  %174 = load ptr, ptr %buffer, align 8
  store ptr %174, ptr %173, align 8
  %175 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %176 = load ptr, ptr %175, align 8
  ret void

mergeBlock74:                                     ; No predecessors!
  %177 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %178 = icmp eq i32 %177, 0
  br i1 %178, label %checkContinueBlock25, label %afterNestedBlock
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
  %7 = alloca ptr, align 8
  %file = alloca ptr, align 8
  store ptr @24, ptr %file, align 8
  %8 = alloca ptr, align 8
  %clPtr1 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  %11 = alloca ptr, align 8
  %len = alloca i32, align 4
  store i32 0, ptr %len, align 4
  %bytesWritten = alloca i32, align 4
  store i32 0, ptr %bytesWritten, align 4
  %12 = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca ptr, align 8
  %15 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock16, %mergeBlock54, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse45, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %afterIfElse30, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %mode17 = load ptr, ptr %mode, align 8
  %16 = load ptr, ptr %mode, align 8
  %17 = call i1 @equal_strings(ptr %16, ptr @25)
  %18 = select i1 %17, i1 false, i1 true
  %mode18 = load ptr, ptr %mode, align 8
  %19 = load ptr, ptr %mode, align 8
  %20 = call i1 @equal_strings(ptr %19, ptr @26)
  %21 = select i1 %20, i1 false, i1 true
  %22 = select i1 %18, i1 %21, i1 false
  %mode19 = load ptr, ptr %mode, align 8
  %23 = load ptr, ptr %mode, align 8
  %24 = call i1 @equal_strings(ptr %23, ptr @27)
  %25 = select i1 %24, i1 false, i1 true
  %26 = select i1 %22, i1 %25, i1 false
  %mode20 = load ptr, ptr %mode, align 8
  %27 = load ptr, ptr %mode, align 8
  %28 = call i1 @equal_strings(ptr %27, ptr @28)
  %29 = select i1 %28, i1 false, i1 true
  %30 = select i1 %26, i1 %29, i1 false
  br i1 %30, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %31 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock
  %filePath25 = load ptr, ptr %filePath, align 8
  %33 = load ptr, ptr %filePath, align 8
  %mode26 = load ptr, ptr %mode, align 8
  %34 = load ptr, ptr %mode, align 8
  %35 = call ptr @fopen(ptr %33, ptr %34)
  store ptr %35, ptr %file, align 8
  %36 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %38 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %file27 = load ptr, ptr %file, align 8
  %40 = load ptr, ptr %file, align 8
  %41 = icmp eq ptr %40, null
  br i1 %41, label %then28, label %else29

checkContinueBlock6:                              ; preds = %afterIfElse30
  %42 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %data37 = load ptr, ptr %data, align 8
  %44 = load ptr, ptr %data, align 8
  %45 = call i32 @strlen(ptr %44)
  store i32 %45, ptr %len, align 4
  %46 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %48 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %data38 = load ptr, ptr %data, align 8
  %50 = load ptr, ptr %data, align 8
  %len39 = load i32, ptr %len, align 4
  %51 = load i32, ptr %len, align 4
  %file40 = load ptr, ptr %file, align 8
  %52 = load ptr, ptr %file, align 8
  %53 = call i32 @fwrite(ptr %50, i32 1, i32 %51, ptr %52)
  store i32 %53, ptr %bytesWritten, align 4
  %54 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %56 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %bytesWritten41 = load i32, ptr %bytesWritten, align 4
  %58 = load i32, ptr %bytesWritten, align 4
  %len42 = load i32, ptr %len, align 4
  %59 = load i32, ptr %len, align 4
  %60 = icmp ne i32 %58, %59
  br i1 %60, label %then43, label %else44

checkContinueBlock12:                             ; preds = %afterIfElse45
  %61 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %file52 = load ptr, ptr %file, align 8
  %63 = load ptr, ptr %file, align 8
  %64 = call i32 @fclose(ptr %63)
  %65 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %66 = icmp eq i32 %65, 0
  br i1 %66, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %67 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  br label %returnBlock53

checkContinueBlock16:                             ; preds = %mergeBlock54
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock22

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock21
  %69 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock21:                               ; preds = %checkContinueBlock23, %mergeBlock
  br label %afterIfElse

nestedBlock22:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock23:                             ; preds = %mergeBlock
  br label %afterNestedBlock21

returnBlock:                                      ; preds = %nestedBlock22
  %71 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %72 = load ptr, ptr %71, align 8
  store ptr @29, ptr %72, align 8
  %73 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %74 = load ptr, ptr %73, align 8
  %75 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %75)
  %76 = getelementptr inbounds %"Err::Result", ptr %75, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %76, align 8
  %77 = load ptr, ptr %76, align 8
  %78 = getelementptr inbounds %"Err::Result::VTableType", ptr %77, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %78, align 8
  %79 = getelementptr inbounds %"Err::Result::VTableType", ptr %77, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %79, align 8
  %80 = getelementptr inbounds %"Err::Result::VTableType", ptr %77, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %80, align 8
  %81 = getelementptr inbounds %"Err::Result::VTableType", ptr %77, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %81, align 8
  %82 = getelementptr inbounds %"Err::Result::VTableType", ptr %77, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %82, align 8
  %83 = getelementptr inbounds %"Err::Result::VTableType", ptr %77, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %83, align 8
  %84 = getelementptr inbounds %"Err::Result", ptr %75, i32 0, i32 1
  store ptr @30, ptr %84, align 8
  %85 = getelementptr inbounds %"Err::Result", ptr %75, i32 0, i32 2
  store i32 0, ptr %85, align 4
  %86 = getelementptr inbounds %"Err::Result", ptr %75, i32 0, i32 3
  store ptr @31, ptr %86, align 8
  store ptr %75, ptr %74, align 8
  %mode24 = load ptr, ptr %mode, align 8
  %87 = load ptr, ptr %mode, align 8
  %88 = call ptr @concat_strings(ptr @32, ptr %87)
  store ptr %88, ptr %7, align 8
  %INVALID_ARGUMENT = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  call void @"Err::Result.init2"(ptr %7, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), ptr %74)
  ret void

mergeBlock:                                       ; No predecessors!
  %89 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %90 = icmp eq i32 %89, 0
  br i1 %90, label %checkContinueBlock23, label %afterNestedBlock21

then28:                                           ; preds = %nestedBlock5
  br label %nestedBlock32

else29:                                           ; preds = %nestedBlock5
  br label %afterIfElse30

afterIfElse30:                                    ; preds = %else29, %afterNestedBlock31
  %91 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %checkContinueBlock6, label %afterNestedBlock

afterNestedBlock31:                               ; preds = %checkContinueBlock33, %mergeBlock35
  br label %afterIfElse30

nestedBlock32:                                    ; preds = %then28
  br label %returnBlock34

checkContinueBlock33:                             ; preds = %mergeBlock35
  br label %afterNestedBlock31

returnBlock34:                                    ; preds = %nestedBlock32
  %93 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %94 = load ptr, ptr %93, align 8
  store ptr @33, ptr %94, align 8
  %95 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %96 = load ptr, ptr %95, align 8
  %97 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %97)
  %98 = getelementptr inbounds %"Err::Result", ptr %97, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %98, align 8
  %99 = load ptr, ptr %98, align 8
  %100 = getelementptr inbounds %"Err::Result::VTableType", ptr %99, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %100, align 8
  %101 = getelementptr inbounds %"Err::Result::VTableType", ptr %99, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %101, align 8
  %102 = getelementptr inbounds %"Err::Result::VTableType", ptr %99, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %102, align 8
  %103 = getelementptr inbounds %"Err::Result::VTableType", ptr %99, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %103, align 8
  %104 = getelementptr inbounds %"Err::Result::VTableType", ptr %99, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %104, align 8
  %105 = getelementptr inbounds %"Err::Result::VTableType", ptr %99, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %105, align 8
  %106 = getelementptr inbounds %"Err::Result", ptr %97, i32 0, i32 1
  store ptr @34, ptr %106, align 8
  %107 = getelementptr inbounds %"Err::Result", ptr %97, i32 0, i32 2
  store i32 0, ptr %107, align 4
  %108 = getelementptr inbounds %"Err::Result", ptr %97, i32 0, i32 3
  store ptr @35, ptr %108, align 8
  store ptr %97, ptr %96, align 8
  %filePath36 = load ptr, ptr %filePath, align 8
  %109 = load ptr, ptr %filePath, align 8
  %110 = call ptr @concat_strings(ptr @36, ptr %109)
  store ptr %110, ptr %11, align 8
  %NOT_FOUND = load i32, ptr @"Err::CODE", align 4
  call void @"Err::Result.init2"(ptr %11, ptr @"Err::CODE", ptr %96)
  ret void

mergeBlock35:                                     ; No predecessors!
  %111 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %112 = icmp eq i32 %111, 0
  br i1 %112, label %checkContinueBlock33, label %afterNestedBlock31

then43:                                           ; preds = %nestedBlock11
  br label %nestedBlock47

else44:                                           ; preds = %nestedBlock11
  br label %afterIfElse45

afterIfElse45:                                    ; preds = %else44, %afterNestedBlock46
  %113 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %114 = icmp eq i32 %113, 0
  br i1 %114, label %checkContinueBlock12, label %afterNestedBlock

afterNestedBlock46:                               ; preds = %checkContinueBlock48, %mergeBlock50
  br label %afterIfElse45

nestedBlock47:                                    ; preds = %then43
  br label %returnBlock49

checkContinueBlock48:                             ; preds = %mergeBlock50
  br label %afterNestedBlock46

returnBlock49:                                    ; preds = %nestedBlock47
  %115 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %115)
  %116 = getelementptr inbounds %"Err::Result", ptr %115, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %116, align 8
  %117 = load ptr, ptr %116, align 8
  %118 = getelementptr inbounds %"Err::Result::VTableType", ptr %117, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %118, align 8
  %119 = getelementptr inbounds %"Err::Result::VTableType", ptr %117, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %119, align 8
  %120 = getelementptr inbounds %"Err::Result::VTableType", ptr %117, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %120, align 8
  %121 = getelementptr inbounds %"Err::Result::VTableType", ptr %117, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %121, align 8
  %122 = getelementptr inbounds %"Err::Result::VTableType", ptr %117, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %122, align 8
  %123 = getelementptr inbounds %"Err::Result::VTableType", ptr %117, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %123, align 8
  %124 = getelementptr inbounds %"Err::Result", ptr %115, i32 0, i32 1
  store ptr @37, ptr %124, align 8
  %125 = getelementptr inbounds %"Err::Result", ptr %115, i32 0, i32 2
  store i32 0, ptr %125, align 4
  %126 = getelementptr inbounds %"Err::Result", ptr %115, i32 0, i32 3
  store ptr @38, ptr %126, align 8
  store ptr %115, ptr %0, align 8
  %filePath51 = load ptr, ptr %filePath, align 8
  %127 = load ptr, ptr %filePath, align 8
  %128 = call ptr @concat_strings(ptr @39, ptr %127)
  store ptr %128, ptr %15, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %15, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %0)
  ret void

mergeBlock50:                                     ; No predecessors!
  %129 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %checkContinueBlock48, label %afterNestedBlock46

returnBlock53:                                    ; preds = %nestedBlock15
  %131 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %132 = load ptr, ptr %131, align 8
  store ptr @40, ptr %132, align 8
  %133 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %134 = load ptr, ptr %133, align 8
  ret void

mergeBlock54:                                     ; No predecessors!
  %135 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %136 = icmp eq i32 %135, 0
  br i1 %136, label %checkContinueBlock16, label %afterNestedBlock
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
  %5 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %mergeBlock15, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %filePath7 = load ptr, ptr %filePath, align 8
  %6 = load ptr, ptr %filePath, align 8
  %7 = call ptr @fopen(ptr %6, ptr @42)
  store ptr %7, ptr %file, align 8
  %8 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %10 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %file8 = load ptr, ptr %file, align 8
  %12 = load ptr, ptr %file, align 8
  %13 = icmp eq ptr %12, null
  br i1 %13, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  %14 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %file13 = load ptr, ptr %file, align 8
  %16 = load ptr, ptr %file, align 8
  %17 = call i32 @fclose(ptr %16)
  %18 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %20 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  br label %returnBlock14

checkContinueBlock6:                              ; preds = %mergeBlock15
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock10

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock9
  %22 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock9:                                ; preds = %checkContinueBlock11, %mergeBlock
  br label %afterIfElse

nestedBlock10:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock11:                             ; preds = %mergeBlock
  br label %afterNestedBlock9

returnBlock:                                      ; preds = %nestedBlock10
  %24 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %24)
  %25 = getelementptr inbounds %"Err::Result", ptr %24, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %25, align 8
  %26 = load ptr, ptr %25, align 8
  %27 = getelementptr inbounds %"Err::Result::VTableType", ptr %26, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %27, align 8
  %28 = getelementptr inbounds %"Err::Result::VTableType", ptr %26, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %28, align 8
  %29 = getelementptr inbounds %"Err::Result::VTableType", ptr %26, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %29, align 8
  %30 = getelementptr inbounds %"Err::Result::VTableType", ptr %26, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %30, align 8
  %31 = getelementptr inbounds %"Err::Result::VTableType", ptr %26, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %31, align 8
  %32 = getelementptr inbounds %"Err::Result::VTableType", ptr %26, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %32, align 8
  %33 = getelementptr inbounds %"Err::Result", ptr %24, i32 0, i32 1
  store ptr @43, ptr %33, align 8
  %34 = getelementptr inbounds %"Err::Result", ptr %24, i32 0, i32 2
  store i32 0, ptr %34, align 4
  %35 = getelementptr inbounds %"Err::Result", ptr %24, i32 0, i32 3
  store ptr @44, ptr %35, align 8
  store ptr %24, ptr %0, align 8
  %filePath12 = load ptr, ptr %filePath, align 8
  %36 = load ptr, ptr %filePath, align 8
  %37 = call ptr @concat_strings(ptr @45, ptr %36)
  store ptr %37, ptr %5, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %5, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %0)
  ret void

mergeBlock:                                       ; No predecessors!
  %38 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %checkContinueBlock11, label %afterNestedBlock9

returnBlock14:                                    ; preds = %nestedBlock5
  %40 = getelementptr inbounds %2, ptr %0, i32 0, i32 0
  %41 = load ptr, ptr %40, align 8
  store ptr @46, ptr %41, align 8
  %42 = getelementptr inbounds %2, ptr %0, i32 0, i32 1
  %43 = load ptr, ptr %42, align 8
  ret void

mergeBlock15:                                     ; No predecessors!
  %44 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock6, label %afterNestedBlock
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
