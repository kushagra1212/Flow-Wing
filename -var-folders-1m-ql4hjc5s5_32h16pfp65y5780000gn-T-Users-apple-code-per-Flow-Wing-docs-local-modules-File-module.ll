; ModuleID = '-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module'
source_filename = "-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module"

%0 = type { ptr, ptr }
%"Err::Result::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Err::ErrorCode.0" = type { i32, i32, i32 }
%"Err::Result" = type { ptr, ptr, i32, ptr }

@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_NULL = external global i8
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Err::Result.fg" = common global %"Err::Result::VTableType" zeroinitializer
@"Err::CODE" = common global %"Err::ErrorCode.0" zeroinitializer
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

define i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module() {
entry:
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  store i32 1, ptr @"Err::CODE", align 4
  store i32 2, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  store i32 3, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 2), align 4
  %0 = call i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
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

declare i32 @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-Err-module()

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
  %26 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock
  %filePath32 = load ptr, ptr %filePath, align 8
  %28 = load ptr, ptr %filePath, align 8
  %mode33 = load ptr, ptr %mode, align 8
  %29 = load ptr, ptr %mode, align 8
  %30 = call ptr @fopen(ptr %28, ptr %29)
  store ptr %30, ptr %file, align 8
  %31 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock5, label %afterNestedBlock

checkContinueBlock5:                              ; preds = %nestedBlock4
  %33 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  store i32 2, ptr %SEEK_END, align 4
  %35 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %37 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  %file34 = load ptr, ptr %file, align 8
  %39 = load ptr, ptr %file, align 8
  %40 = icmp eq ptr %39, null
  br i1 %40, label %then35, label %else36

checkContinueBlock9:                              ; preds = %afterIfElse37
  %41 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %file44 = load ptr, ptr %file, align 8
  %43 = load ptr, ptr %file, align 8
  %SEEK_END45 = load i32, ptr %SEEK_END, align 4
  %44 = load i32, ptr %SEEK_END, align 4
  %45 = call i32 @fseek(ptr %43, i32 0, i32 %44)
  %46 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %48 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %file46 = load ptr, ptr %file, align 8
  %50 = load ptr, ptr %file, align 8
  %51 = call i32 @ftell(ptr %50)
  store i32 %51, ptr %fileSize, align 4
  %52 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %54 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %file47 = load ptr, ptr %file, align 8
  %56 = load ptr, ptr %file, align 8
  call void @rewind(ptr %56)
  %57 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %59 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %fileSize48 = load i32, ptr %fileSize, align 4
  %61 = load i32, ptr %fileSize, align 4
  %62 = add i32 %61, 1
  %63 = call ptr @calloc(i32 %62, i32 4)
  store ptr %63, ptr %buffer, align 8
  %64 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %66 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %buffer49 = load ptr, ptr %buffer, align 8
  %68 = load ptr, ptr %buffer, align 8
  %69 = icmp eq ptr %68, null
  br i1 %69, label %then50, label %else51

checkContinueBlock19:                             ; preds = %afterIfElse52
  %70 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
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
  %76 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %77 = icmp eq i32 %76, 0
  br i1 %77, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %78 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
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
  %83 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_CONTINUE_COUNT, align 4
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
  %85 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
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
  %105 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %106 = icmp eq i32 %105, 0
  br i1 %106, label %checkContinueBlock30, label %afterNestedBlock28

then35:                                           ; preds = %nestedBlock8
  br label %nestedBlock39

else36:                                           ; preds = %nestedBlock8
  br label %afterIfElse37

afterIfElse37:                                    ; preds = %else36, %afterNestedBlock38
  %107 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
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
  %127 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %checkContinueBlock40, label %afterNestedBlock38

then50:                                           ; preds = %nestedBlock18
  br label %nestedBlock54

else51:                                           ; preds = %nestedBlock18
  br label %afterIfElse52

afterIfElse52:                                    ; preds = %else51, %afterNestedBlock53
  %129 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
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
  %147 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %148 = icmp eq i32 %147, 0
  br i1 %148, label %checkContinueBlock55, label %afterNestedBlock53

then63:                                           ; preds = %nestedBlock22
  br label %nestedBlock67

else64:                                           ; preds = %nestedBlock22
  br label %afterIfElse65

afterIfElse65:                                    ; preds = %else64, %afterNestedBlock66
  %149 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
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
  %170 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
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
  %177 = load i32, ptr @-var-folders-1m-ql4hjc5s5_32h16pfp65y5780000gn-T-Users-apple-code-per-Flow-Wing-docs-local-modules-File-module_FLOWWING_BREAK_COUNT, align 4
  %178 = icmp eq i32 %177, 0
  br i1 %178, label %checkContinueBlock25, label %afterNestedBlock
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
