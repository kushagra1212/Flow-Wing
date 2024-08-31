; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-local-File-module'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-local-File-module"

%0 = type { ptr, ptr }
%"Err::Result::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"Err::ErrorCode.0" = type { i32, i32 }
%"Err::Result" = type { ptr, ptr, i32, ptr }

@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Err::Result.fg" = common global %"Err::Result::VTableType" zeroinitializer
@"Err::CODE" = common global %"Err::ErrorCode.0" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [13 x i8] c" not found !\00", align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@11 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@12 = private unnamed_addr constant [28 x i8] c"Failed to allocate memory !\00", align 1
@13 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@14 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@16 = private unnamed_addr constant [33 x i8] c"Failed to read the entire file '\00", align 1
@17 = private unnamed_addr constant [2 x i8] c"'\00", align 1

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
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  call void @"assign_<ObjectErr::ErrorCode.0>"(ptr @"Err::CODE")
  store i32 1, ptr @"Err::CODE", align 4
  store i32 2, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  %0 = call i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-Error-Err-module()
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

declare i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-Error-Err-module()

define internal void @"assign_<ObjectErr::ErrorCode.0>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::ErrorCode.0", ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %"Err::ErrorCode.0", ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
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
  %file = alloca ptr, align 8
  store ptr @0, ptr %file, align 8
  %SEEK_END = alloca i32, align 4
  store i32 0, ptr %SEEK_END, align 4
  %3 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %fileSize = alloca i32, align 4
  store i32 0, ptr %fileSize, align 4
  %buffer = alloca ptr, align 8
  store ptr @1, ptr %buffer, align 8
  %7 = alloca ptr, align 8
  %clPtr1 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  %10 = alloca ptr, align 8
  %bytesRead = alloca i32, align 4
  store i32 0, ptr %bytesRead, align 4
  %11 = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %12 = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock22, %mergeBlock60, %checkContinueBlock20, %afterIfElse51, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %afterIfElse38, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %afterIfElse, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %filePath23 = load ptr, ptr %filePath, align 8
  %15 = load ptr, ptr %filePath, align 8
  %mode24 = load ptr, ptr %mode, align 8
  %16 = load ptr, ptr %mode, align 8
  %17 = call ptr @fopen(ptr %15, ptr %16)
  store ptr %17, ptr %file, align 8
  %18 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %20 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock
  store i32 2, ptr %SEEK_END, align 4
  %22 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %24 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %file25 = load ptr, ptr %file, align 8
  %26 = load ptr, ptr %file, align 8
  %27 = icmp eq ptr %26, null
  br i1 %27, label %then, label %else

checkContinueBlock6:                              ; preds = %afterIfElse
  %28 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %file30 = load ptr, ptr %file, align 8
  %30 = load ptr, ptr %file, align 8
  %SEEK_END31 = load i32, ptr %SEEK_END, align 4
  %31 = load i32, ptr %SEEK_END, align 4
  %32 = call i32 @fseek(ptr %30, i32 0, i32 %31)
  %33 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %35 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %file32 = load ptr, ptr %file, align 8
  %37 = load ptr, ptr %file, align 8
  %38 = call i32 @ftell(ptr %37)
  store i32 %38, ptr %fileSize, align 4
  %39 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %41 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %file33 = load ptr, ptr %file, align 8
  %43 = load ptr, ptr %file, align 8
  call void @rewind(ptr %43)
  %44 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %46 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %fileSize34 = load i32, ptr %fileSize, align 4
  %48 = load i32, ptr %fileSize, align 4
  %49 = add i32 %48, 1
  %50 = call ptr @calloc(i32 %49, i32 4)
  store ptr %50, ptr %buffer, align 8
  %51 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %53 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %buffer35 = load ptr, ptr %buffer, align 8
  %55 = load ptr, ptr %buffer, align 8
  %56 = icmp eq ptr %55, null
  br i1 %56, label %then36, label %else37

checkContinueBlock16:                             ; preds = %afterIfElse38
  %57 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %buffer44 = load ptr, ptr %buffer, align 8
  %59 = load ptr, ptr %buffer, align 8
  %fileSize45 = load i32, ptr %fileSize, align 4
  %60 = load i32, ptr %fileSize, align 4
  %file46 = load ptr, ptr %file, align 8
  %61 = load ptr, ptr %file, align 8
  %62 = call i32 @fread(ptr %59, i32 1, i32 %60, ptr %61)
  store i32 %62, ptr %bytesRead, align 4
  %63 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %64 = icmp eq i32 %63, 0
  br i1 %64, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %65 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %66 = icmp eq i32 %65, 0
  br i1 %66, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %bytesRead47 = load i32, ptr %bytesRead, align 4
  %67 = load i32, ptr %bytesRead, align 4
  %fileSize48 = load i32, ptr %fileSize, align 4
  %68 = load i32, ptr %fileSize, align 4
  %69 = icmp ne i32 %67, %68
  br i1 %69, label %then49, label %else50

checkContinueBlock20:                             ; preds = %afterIfElse51
  %70 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_CONTINUE_COUNT, align 4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  br label %returnBlock59

checkContinueBlock22:                             ; preds = %mergeBlock60
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock5
  br label %nestedBlock27

else:                                             ; preds = %nestedBlock5
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock26
  %72 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %checkContinueBlock6, label %afterNestedBlock

afterNestedBlock26:                               ; preds = %checkContinueBlock28, %mergeBlock
  br label %afterIfElse

nestedBlock27:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock28:                             ; preds = %mergeBlock
  br label %afterNestedBlock26

returnBlock:                                      ; preds = %nestedBlock27
  %74 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %75 = load ptr, ptr %74, align 8
  store ptr @2, ptr %75, align 8
  %76 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %77 = load ptr, ptr %76, align 8
  %78 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %78)
  %79 = getelementptr inbounds %"Err::Result", ptr %78, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %79, align 8
  %80 = load ptr, ptr %79, align 8
  %81 = getelementptr inbounds %"Err::Result::VTableType", ptr %80, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %81, align 8
  %82 = getelementptr inbounds %"Err::Result::VTableType", ptr %80, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %82, align 8
  %83 = getelementptr inbounds %"Err::Result::VTableType", ptr %80, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %83, align 8
  %84 = getelementptr inbounds %"Err::Result::VTableType", ptr %80, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %84, align 8
  %85 = getelementptr inbounds %"Err::Result::VTableType", ptr %80, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %85, align 8
  %86 = getelementptr inbounds %"Err::Result::VTableType", ptr %80, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %86, align 8
  %87 = getelementptr inbounds %"Err::Result", ptr %78, i32 0, i32 1
  store ptr @6, ptr %87, align 8
  %88 = getelementptr inbounds %"Err::Result", ptr %78, i32 0, i32 2
  store i32 0, ptr %88, align 4
  %89 = getelementptr inbounds %"Err::Result", ptr %78, i32 0, i32 3
  store ptr @7, ptr %89, align 8
  store ptr %78, ptr %77, align 8
  %filePath29 = load ptr, ptr %filePath, align 8
  %90 = load ptr, ptr %filePath, align 8
  %91 = call ptr @concat_strings(ptr %90, ptr @8)
  store ptr %91, ptr %6, align 8
  %NOT_FOUND = load i32, ptr @"Err::CODE", align 4
  call void @"Err::Result.init2"(ptr %6, ptr @"Err::CODE", ptr %77)
  ret void

mergeBlock:                                       ; No predecessors!
  %92 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %checkContinueBlock28, label %afterNestedBlock26

then36:                                           ; preds = %nestedBlock15
  br label %nestedBlock40

else37:                                           ; preds = %nestedBlock15
  br label %afterIfElse38

afterIfElse38:                                    ; preds = %else37, %afterNestedBlock39
  %94 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %checkContinueBlock16, label %afterNestedBlock

afterNestedBlock39:                               ; preds = %checkContinueBlock41, %mergeBlock43
  br label %afterIfElse38

nestedBlock40:                                    ; preds = %then36
  br label %returnBlock42

checkContinueBlock41:                             ; preds = %mergeBlock43
  br label %afterNestedBlock39

returnBlock42:                                    ; preds = %nestedBlock40
  %96 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %97 = load ptr, ptr %96, align 8
  store ptr @9, ptr %97, align 8
  %98 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %99 = load ptr, ptr %98, align 8
  %100 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %100)
  %101 = getelementptr inbounds %"Err::Result", ptr %100, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %101, align 8
  %102 = load ptr, ptr %101, align 8
  %103 = getelementptr inbounds %"Err::Result::VTableType", ptr %102, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %103, align 8
  %104 = getelementptr inbounds %"Err::Result::VTableType", ptr %102, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %104, align 8
  %105 = getelementptr inbounds %"Err::Result::VTableType", ptr %102, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %105, align 8
  %106 = getelementptr inbounds %"Err::Result::VTableType", ptr %102, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %106, align 8
  %107 = getelementptr inbounds %"Err::Result::VTableType", ptr %102, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %107, align 8
  %108 = getelementptr inbounds %"Err::Result::VTableType", ptr %102, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %108, align 8
  %109 = getelementptr inbounds %"Err::Result", ptr %100, i32 0, i32 1
  store ptr @10, ptr %109, align 8
  %110 = getelementptr inbounds %"Err::Result", ptr %100, i32 0, i32 2
  store i32 0, ptr %110, align 4
  %111 = getelementptr inbounds %"Err::Result", ptr %100, i32 0, i32 3
  store ptr @11, ptr %111, align 8
  store ptr %100, ptr %99, align 8
  store ptr @12, ptr %10, align 8
  %FAILED = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %10, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %99)
  ret void

mergeBlock43:                                     ; No predecessors!
  %112 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %113 = icmp eq i32 %112, 0
  br i1 %113, label %checkContinueBlock41, label %afterNestedBlock39

then49:                                           ; preds = %nestedBlock19
  br label %nestedBlock53

else50:                                           ; preds = %nestedBlock19
  br label %afterIfElse51

afterIfElse51:                                    ; preds = %else50, %afterNestedBlock52
  %114 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %115 = icmp eq i32 %114, 0
  br i1 %115, label %checkContinueBlock20, label %afterNestedBlock

afterNestedBlock52:                               ; preds = %checkContinueBlock54, %mergeBlock56
  br label %afterIfElse51

nestedBlock53:                                    ; preds = %then49
  br label %returnBlock55

checkContinueBlock54:                             ; preds = %mergeBlock56
  br label %afterNestedBlock52

returnBlock55:                                    ; preds = %nestedBlock53
  %116 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %117 = load ptr, ptr %116, align 8
  store ptr @13, ptr %117, align 8
  %118 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %119 = load ptr, ptr %118, align 8
  %120 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %120)
  %121 = getelementptr inbounds %"Err::Result", ptr %120, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %121, align 8
  %122 = load ptr, ptr %121, align 8
  %123 = getelementptr inbounds %"Err::Result::VTableType", ptr %122, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %123, align 8
  %124 = getelementptr inbounds %"Err::Result::VTableType", ptr %122, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %124, align 8
  %125 = getelementptr inbounds %"Err::Result::VTableType", ptr %122, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %125, align 8
  %126 = getelementptr inbounds %"Err::Result::VTableType", ptr %122, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %126, align 8
  %127 = getelementptr inbounds %"Err::Result::VTableType", ptr %122, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %127, align 8
  %128 = getelementptr inbounds %"Err::Result::VTableType", ptr %122, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %128, align 8
  %129 = getelementptr inbounds %"Err::Result", ptr %120, i32 0, i32 1
  store ptr @14, ptr %129, align 8
  %130 = getelementptr inbounds %"Err::Result", ptr %120, i32 0, i32 2
  store i32 0, ptr %130, align 4
  %131 = getelementptr inbounds %"Err::Result", ptr %120, i32 0, i32 3
  store ptr @15, ptr %131, align 8
  store ptr %120, ptr %119, align 8
  %filePath57 = load ptr, ptr %filePath, align 8
  %132 = load ptr, ptr %filePath, align 8
  %133 = call ptr @concat_strings(ptr @16, ptr %132)
  %134 = call ptr @concat_strings(ptr %133, ptr @17)
  store ptr %134, ptr %14, align 8
  %FAILED58 = load i32, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), align 4
  call void @"Err::Result.init2"(ptr %14, ptr getelementptr inbounds (%"Err::ErrorCode.0", ptr @"Err::CODE", i32 0, i32 1), ptr %119)
  ret void

mergeBlock56:                                     ; No predecessors!
  %135 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %136 = icmp eq i32 %135, 0
  br i1 %136, label %checkContinueBlock54, label %afterNestedBlock52

returnBlock59:                                    ; preds = %nestedBlock21
  %137 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %138 = load ptr, ptr %137, align 8
  %buffer61 = load ptr, ptr %buffer, align 8
  %139 = load ptr, ptr %buffer, align 8
  store ptr %139, ptr %138, align 8
  %140 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %141 = load ptr, ptr %140, align 8
  ret void

mergeBlock60:                                     ; No predecessors!
  %142 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-local-File-module_FLOWWING_BREAK_COUNT, align 4
  %143 = icmp eq i32 %142, 0
  br i1 %143, label %checkContinueBlock22, label %afterNestedBlock
}

declare !rt !15 void @"File::read.10"(ptr, ptr, ptr)

define internal void @"assign_<Class<Err::Result>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 0
  store ptr @3, ptr %1, align 8
  %2 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 1
  store ptr @4, ptr %2, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 3
  store ptr @5, ptr %4, align 8
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
