; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module"

%0 = type { ptr, ptr }
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

declare !rt !10 i32 @fread(ptr, i32, i32, ptr)

declare !rt !11 i32 @fseek(ptr, i32, i32)

declare !rt !12 i32 @ftell(ptr)

declare !rt !13 ptr @calloc(i32, i32)

declare !rt !14 void @rewind(ptr)

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

afterNestedBlock:                                 ; preds = %checkContinueBlock27, %mergeBlock77, %checkContinueBlock25, %afterIfElse68, %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %afterIfElse55, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %afterIfElse40, %checkContinueBlock9, %nestedBlock8, %checkContinueBlock7, %nestedBlock6, %checkContinueBlock5, %nestedBlock4, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %mode28 = load ptr, ptr %mode, align 8
  %19 = load ptr, ptr %mode, align 8
  %20 = call i1 @equal_strings(ptr %19, ptr @2)
  %21 = select i1 %20, i1 false, i1 true
  %mode29 = load ptr, ptr %mode, align 8
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
  %INVALID_ARGUMENT34 = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  %28 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock5, label %afterNestedBlock

checkContinueBlock5:                              ; preds = %nestedBlock4
  %30 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  %filePath35 = load ptr, ptr %filePath, align 8
  %32 = load ptr, ptr %filePath, align 8
  %mode36 = load ptr, ptr %mode, align 8
  %33 = load ptr, ptr %mode, align 8
  %34 = call ptr @fopen(ptr %32, ptr %33)
  store ptr %34, ptr %file, align 8
  %35 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %37 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  store i32 2, ptr %SEEK_END, align 4
  %39 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock9, label %afterNestedBlock

checkContinueBlock9:                              ; preds = %nestedBlock8
  %41 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %file37 = load ptr, ptr %file, align 8
  %43 = load ptr, ptr %file, align 8
  %44 = icmp eq ptr %43, null
  br i1 %44, label %then38, label %else39

checkContinueBlock11:                             ; preds = %afterIfElse40
  %45 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %file47 = load ptr, ptr %file, align 8
  %47 = load ptr, ptr %file, align 8
  %SEEK_END48 = load i32, ptr %SEEK_END, align 4
  %48 = load i32, ptr %SEEK_END, align 4
  %49 = call i32 @fseek(ptr %47, i32 0, i32 %48)
  %50 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %52 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %file49 = load ptr, ptr %file, align 8
  %54 = load ptr, ptr %file, align 8
  %55 = call i32 @ftell(ptr %54)
  store i32 %55, ptr %fileSize, align 4
  %56 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %58 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %59 = icmp eq i32 %58, 0
  br i1 %59, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %file50 = load ptr, ptr %file, align 8
  %60 = load ptr, ptr %file, align 8
  call void @rewind(ptr %60)
  %61 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %63 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %64 = icmp eq i32 %63, 0
  br i1 %64, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %fileSize51 = load i32, ptr %fileSize, align 4
  %65 = load i32, ptr %fileSize, align 4
  %66 = add i32 %65, 1
  %67 = call ptr @calloc(i32 %66, i32 4)
  store ptr %67, ptr %buffer, align 8
  %68 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  %70 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %buffer52 = load ptr, ptr %buffer, align 8
  %72 = load ptr, ptr %buffer, align 8
  %73 = icmp eq ptr %72, null
  br i1 %73, label %then53, label %else54

checkContinueBlock21:                             ; preds = %afterIfElse55
  %74 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %buffer61 = load ptr, ptr %buffer, align 8
  %76 = load ptr, ptr %buffer, align 8
  %fileSize62 = load i32, ptr %fileSize, align 4
  %77 = load i32, ptr %fileSize, align 4
  %file63 = load ptr, ptr %file, align 8
  %78 = load ptr, ptr %file, align 8
  %79 = call i32 @fread(ptr %76, i32 1, i32 %77, ptr %78)
  store i32 %79, ptr %bytesRead, align 4
  %80 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %81 = icmp eq i32 %80, 0
  br i1 %81, label %checkContinueBlock23, label %afterNestedBlock

checkContinueBlock23:                             ; preds = %nestedBlock22
  %82 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %83 = icmp eq i32 %82, 0
  br i1 %83, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  %bytesRead64 = load i32, ptr %bytesRead, align 4
  %84 = load i32, ptr %bytesRead, align 4
  %fileSize65 = load i32, ptr %fileSize, align 4
  %85 = load i32, ptr %fileSize, align 4
  %86 = icmp ne i32 %84, %85
  br i1 %86, label %then66, label %else67

checkContinueBlock25:                             ; preds = %afterIfElse68
  %87 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %88 = icmp eq i32 %87, 0
  br i1 %88, label %nestedBlock26, label %afterNestedBlock

nestedBlock26:                                    ; preds = %checkContinueBlock25
  br label %returnBlock76

checkContinueBlock27:                             ; preds = %mergeBlock77
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock31

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock30
  %89 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %90 = icmp eq i32 %89, 0
  br i1 %90, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock30:                               ; preds = %checkContinueBlock32, %mergeBlock
  br label %afterIfElse

nestedBlock31:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock32:                             ; preds = %mergeBlock
  br label %afterNestedBlock30

returnBlock:                                      ; preds = %nestedBlock31
  %91 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %92 = load ptr, ptr %91, align 8
  store ptr @4, ptr %92, align 8
  %93 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %94 = load ptr, ptr %93, align 8
  %95 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %95)
  %96 = getelementptr inbounds %"Err::Result", ptr %95, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %96, align 8
  %97 = load ptr, ptr %96, align 8
  %98 = getelementptr inbounds %"Err::Result::VTableType", ptr %97, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %98, align 8
  %99 = getelementptr inbounds %"Err::Result::VTableType", ptr %97, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %99, align 8
  %100 = getelementptr inbounds %"Err::Result::VTableType", ptr %97, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %100, align 8
  %101 = getelementptr inbounds %"Err::Result::VTableType", ptr %97, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %101, align 8
  %102 = getelementptr inbounds %"Err::Result::VTableType", ptr %97, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %102, align 8
  %103 = getelementptr inbounds %"Err::Result::VTableType", ptr %97, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %103, align 8
  %104 = getelementptr inbounds %"Err::Result", ptr %95, i32 0, i32 1
  store ptr @8, ptr %104, align 8
  %105 = getelementptr inbounds %"Err::Result", ptr %95, i32 0, i32 2
  store i32 0, ptr %105, align 4
  %106 = getelementptr inbounds %"Err::Result", ptr %95, i32 0, i32 3
  store ptr @9, ptr %106, align 8
  store ptr %95, ptr %94, align 8
  %mode33 = load ptr, ptr %mode, align 8
  %107 = load ptr, ptr %mode, align 8
  %108 = call ptr @concat_strings(ptr @10, ptr %107)
  store ptr %108, ptr %6, align 8
  %INVALID_ARGUMENT = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  call void @"Err::Result.init2"(ptr %6, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), ptr %94)
  ret void

mergeBlock:                                       ; No predecessors!
  %109 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %110 = icmp eq i32 %109, 0
  br i1 %110, label %checkContinueBlock32, label %afterNestedBlock30

then38:                                           ; preds = %nestedBlock10
  br label %nestedBlock42

else39:                                           ; preds = %nestedBlock10
  br label %afterIfElse40

afterIfElse40:                                    ; preds = %else39, %afterNestedBlock41
  %111 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %112 = icmp eq i32 %111, 0
  br i1 %112, label %checkContinueBlock11, label %afterNestedBlock

afterNestedBlock41:                               ; preds = %checkContinueBlock43, %mergeBlock45
  br label %afterIfElse40

nestedBlock42:                                    ; preds = %then38
  br label %returnBlock44

checkContinueBlock43:                             ; preds = %mergeBlock45
  br label %afterNestedBlock41

returnBlock44:                                    ; preds = %nestedBlock42
  %113 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %114 = load ptr, ptr %113, align 8
  store ptr @11, ptr %114, align 8
  %115 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %116 = load ptr, ptr %115, align 8
  %117 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %117)
  %118 = getelementptr inbounds %"Err::Result", ptr %117, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %118, align 8
  %119 = load ptr, ptr %118, align 8
  %120 = getelementptr inbounds %"Err::Result::VTableType", ptr %119, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %120, align 8
  %121 = getelementptr inbounds %"Err::Result::VTableType", ptr %119, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %121, align 8
  %122 = getelementptr inbounds %"Err::Result::VTableType", ptr %119, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %122, align 8
  %123 = getelementptr inbounds %"Err::Result::VTableType", ptr %119, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %123, align 8
  %124 = getelementptr inbounds %"Err::Result::VTableType", ptr %119, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %124, align 8
  %125 = getelementptr inbounds %"Err::Result::VTableType", ptr %119, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %125, align 8
  %126 = getelementptr inbounds %"Err::Result", ptr %117, i32 0, i32 1
  store ptr @12, ptr %126, align 8
  %127 = getelementptr inbounds %"Err::Result", ptr %117, i32 0, i32 2
  store i32 0, ptr %127, align 4
  %128 = getelementptr inbounds %"Err::Result", ptr %117, i32 0, i32 3
  store ptr @13, ptr %128, align 8
  store ptr %117, ptr %116, align 8
  %filePath46 = load ptr, ptr %filePath, align 8
  %129 = load ptr, ptr %filePath, align 8
  %130 = call ptr @concat_strings(ptr %129, ptr @14)
  store ptr %130, ptr %10, align 8
  %NOT_FOUND = load i32, ptr @"Err::CODE", align 4
  call void @"Err::Result.init2"(ptr %10, ptr @"Err::CODE", ptr %116)
  ret void

mergeBlock45:                                     ; No predecessors!
  %131 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %132 = icmp eq i32 %131, 0
  br i1 %132, label %checkContinueBlock43, label %afterNestedBlock41

then53:                                           ; preds = %nestedBlock20
  br label %nestedBlock57

else54:                                           ; preds = %nestedBlock20
  br label %afterIfElse55

afterIfElse55:                                    ; preds = %else54, %afterNestedBlock56
  %133 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %134 = icmp eq i32 %133, 0
  br i1 %134, label %checkContinueBlock21, label %afterNestedBlock

afterNestedBlock56:                               ; preds = %checkContinueBlock58, %mergeBlock60
  br label %afterIfElse55

nestedBlock57:                                    ; preds = %then53
  br label %returnBlock59

checkContinueBlock58:                             ; preds = %mergeBlock60
  br label %afterNestedBlock56

returnBlock59:                                    ; preds = %nestedBlock57
  %135 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %136 = load ptr, ptr %135, align 8
  store ptr @15, ptr %136, align 8
  %137 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %138 = load ptr, ptr %137, align 8
  %139 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %139)
  %140 = getelementptr inbounds %"Err::Result", ptr %139, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %140, align 8
  %141 = load ptr, ptr %140, align 8
  %142 = getelementptr inbounds %"Err::Result::VTableType", ptr %141, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %142, align 8
  %143 = getelementptr inbounds %"Err::Result::VTableType", ptr %141, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %143, align 8
  %144 = getelementptr inbounds %"Err::Result::VTableType", ptr %141, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %144, align 8
  %145 = getelementptr inbounds %"Err::Result::VTableType", ptr %141, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %145, align 8
  %146 = getelementptr inbounds %"Err::Result::VTableType", ptr %141, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %146, align 8
  %147 = getelementptr inbounds %"Err::Result::VTableType", ptr %141, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %147, align 8
  %148 = getelementptr inbounds %"Err::Result", ptr %139, i32 0, i32 1
  store ptr @16, ptr %148, align 8
  %149 = getelementptr inbounds %"Err::Result", ptr %139, i32 0, i32 2
  store i32 0, ptr %149, align 4
  %150 = getelementptr inbounds %"Err::Result", ptr %139, i32 0, i32 3
  store ptr @17, ptr %150, align 8
  store ptr %139, ptr %138, align 8
  store ptr @18, ptr %14, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %14, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %138)
  ret void

mergeBlock60:                                     ; No predecessors!
  %151 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %152 = icmp eq i32 %151, 0
  br i1 %152, label %checkContinueBlock58, label %afterNestedBlock56

then66:                                           ; preds = %nestedBlock24
  br label %nestedBlock70

else67:                                           ; preds = %nestedBlock24
  br label %afterIfElse68

afterIfElse68:                                    ; preds = %else67, %afterNestedBlock69
  %153 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %checkContinueBlock25, label %afterNestedBlock

afterNestedBlock69:                               ; preds = %checkContinueBlock71, %mergeBlock73
  br label %afterIfElse68

nestedBlock70:                                    ; preds = %then66
  br label %returnBlock72

checkContinueBlock71:                             ; preds = %mergeBlock73
  br label %afterNestedBlock69

returnBlock72:                                    ; preds = %nestedBlock70
  %155 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %156 = load ptr, ptr %155, align 8
  store ptr @19, ptr %156, align 8
  %157 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %158 = load ptr, ptr %157, align 8
  %159 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %159)
  %160 = getelementptr inbounds %"Err::Result", ptr %159, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %160, align 8
  %161 = load ptr, ptr %160, align 8
  %162 = getelementptr inbounds %"Err::Result::VTableType", ptr %161, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %162, align 8
  %163 = getelementptr inbounds %"Err::Result::VTableType", ptr %161, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %163, align 8
  %164 = getelementptr inbounds %"Err::Result::VTableType", ptr %161, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %164, align 8
  %165 = getelementptr inbounds %"Err::Result::VTableType", ptr %161, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %165, align 8
  %166 = getelementptr inbounds %"Err::Result::VTableType", ptr %161, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %166, align 8
  %167 = getelementptr inbounds %"Err::Result::VTableType", ptr %161, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %167, align 8
  %168 = getelementptr inbounds %"Err::Result", ptr %159, i32 0, i32 1
  store ptr @20, ptr %168, align 8
  %169 = getelementptr inbounds %"Err::Result", ptr %159, i32 0, i32 2
  store i32 0, ptr %169, align 4
  %170 = getelementptr inbounds %"Err::Result", ptr %159, i32 0, i32 3
  store ptr @21, ptr %170, align 8
  store ptr %159, ptr %158, align 8
  %filePath74 = load ptr, ptr %filePath, align 8
  %171 = load ptr, ptr %filePath, align 8
  %172 = call ptr @concat_strings(ptr @22, ptr %171)
  %173 = call ptr @concat_strings(ptr %172, ptr @23)
  store ptr %173, ptr %18, align 8
  %FAILED75 = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %18, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %158)
  ret void

mergeBlock73:                                     ; No predecessors!
  %174 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %175 = icmp eq i32 %174, 0
  br i1 %175, label %checkContinueBlock71, label %afterNestedBlock69

returnBlock76:                                    ; preds = %nestedBlock26
  %176 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %177 = load ptr, ptr %176, align 8
  %buffer78 = load ptr, ptr %buffer, align 8
  %178 = load ptr, ptr %buffer, align 8
  store ptr %178, ptr %177, align 8
  %179 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %180 = load ptr, ptr %179, align 8
  ret void

mergeBlock77:                                     ; No predecessors!
  %181 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %182 = icmp eq i32 %181, 0
  br i1 %182, label %checkContinueBlock27, label %afterNestedBlock
}

declare !rt !15 void @"File::read.10"(ptr, ptr, ptr)

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
!10 = !{!"fread:rt:pr:28"}
!11 = !{!"fseek:rt:pr:28"}
!12 = !{!"ftell:rt:pr:28"}
!13 = !{!"calloc:rt:pr:33"}
!14 = !{!"rewind:rt:pr:27"}
!15 = !{!"File::read:rt:ob:Err::Result"}
