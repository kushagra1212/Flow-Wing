; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%COLORS_TYPE.4 = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%KEYS_TYPE.3 = type { i32, i32, i32, i32, i32, i32, i32 }
%LOG_TYPE.5 = type { i32, i32, i32, i32, i32, i32, i32, i32 }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.4, %KEYS_TYPE.3, %LOG_TYPE.5 }
%Rectangle.2 = type { float, float, float, float }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%Position.7 = type { float, float }
%BoxWithText.6 = type { ptr, i32, i32, i32, i32, i32, i32, i32, i32 }

@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.FlowWingAnim.fg = common global %"FlowWingAnim::VTableType" zeroinitializer
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

declare i32 @putchar(i32)

define i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim(i32 %0, ptr %1) {
entry:
  %screenWidth = alloca i32, align 4
  store i32 0, ptr %screenWidth, align 4
  %screenHeight = alloca i32, align 4
  store i32 0, ptr %screenHeight, align 4
  %screenName = alloca ptr, align 8
  store ptr @0, ptr %screenName, align 8
  %fps = alloca i32, align 4
  store i32 0, ptr %fps, align 4
  %colors = alloca %COLORS_TYPE.4, align 8
  call void @"assign_<Object<COLORS_TYPE.4>"(ptr %colors)
  %KEYS = alloca %KEYS_TYPE.3, align 8
  call void @"assign_<Object<KEYS_TYPE.3>"(ptr %KEYS)
  %LOG = alloca %LOG_TYPE.5, align 8
  call void @"assign_<Object<LOG_TYPE.5>"(ptr %LOG)
  %2 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @FlowWingAnim.init4(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !0 {
entry:
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 7
  %screenHeight = alloca i32, align 4
  %13 = load i32, ptr %0, align 4
  store i32 %13, ptr %screenHeight, align 4
  %screenWidth = alloca i32, align 4
  %14 = load i32, ptr %1, align 4
  store i32 %14, ptr %screenWidth, align 4
  %screenName = alloca ptr, align 8
  %15 = load ptr, ptr %2, align 8
  store ptr %15, ptr %screenName, align 8
  %fps = alloca i32, align 4
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %fps, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %17 = load ptr, ptr %4, align 8
  %18 = getelementptr inbounds %FlowWingAnim, ptr %17, i32 0, i32 4
  %fps11 = load i32, ptr %18, align 4
  store i32 60, ptr %18, align 4
  %19 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %21 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %23 = load ptr, ptr %4, align 8
  %24 = getelementptr inbounds %FlowWingAnim, ptr %23, i32 0, i32 4
  %fps12 = load i32, ptr %24, align 4
  %fps13 = load i32, ptr %fps, align 4
  %25 = load i32, ptr %fps, align 4
  store i32 %25, ptr %24, align 4
  %26 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %28 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  call void @FlowWingAnim.beforeInit(ptr %4)
  %30 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %32 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %34 = load ptr, ptr %4, align 8
  %35 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 2
  %screenHeight14 = load i32, ptr %35, align 4
  %screenHeight15 = load i32, ptr %screenHeight, align 4
  %36 = load i32, ptr %screenHeight, align 4
  store i32 %36, ptr %35, align 4
  %37 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %39 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %41 = load ptr, ptr %4, align 8
  %42 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 1
  %screenWidth16 = load i32, ptr %42, align 4
  %screenWidth17 = load i32, ptr %screenWidth, align 4
  %43 = load i32, ptr %screenWidth, align 4
  store i32 %43, ptr %42, align 4
  %44 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %46 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %48 = load ptr, ptr %4, align 8
  %49 = getelementptr inbounds %FlowWingAnim, ptr %48, i32 0, i32 3
  %screenName18 = load ptr, ptr %49, align 8
  %screenName19 = load ptr, ptr %screenName, align 8
  %50 = load ptr, ptr %screenName, align 8
  store ptr %50, ptr %49, align 8
  %51 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  br label %afterNestedBlock
}

define void @FlowWingAnim.beforeInit(ptr %0) !rt !1 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  %rtPtr = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %rtPtr1 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %rtPtr2 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %rtPtr3 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %rtPtr4 = alloca i32, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i32, align 4
  %28 = alloca i32, align 4
  %rtPtr5 = alloca i32, align 4
  %29 = alloca i32, align 4
  %30 = alloca i32, align 4
  %31 = alloca i32, align 4
  %32 = alloca i32, align 4
  %rtPtr6 = alloca i32, align 4
  %33 = alloca i32, align 4
  %34 = alloca i32, align 4
  %35 = alloca i32, align 4
  %36 = alloca i32, align 4
  %rtPtr7 = alloca i32, align 4
  %37 = alloca i32, align 4
  %38 = alloca i32, align 4
  %39 = alloca i32, align 4
  %40 = alloca i32, align 4
  %rtPtr8 = alloca i32, align 4
  %41 = alloca i32, align 4
  %42 = alloca i32, align 4
  %43 = alloca i32, align 4
  %44 = alloca i32, align 4
  %rtPtr9 = alloca i32, align 4
  %45 = alloca i32, align 4
  %46 = alloca i32, align 4
  %47 = alloca i32, align 4
  %48 = alloca i32, align 4
  %rtPtr10 = alloca i32, align 4
  %49 = alloca i32, align 4
  %50 = alloca i32, align 4
  %51 = alloca i32, align 4
  %52 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %53 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 0
  store i32 255, ptr %9, align 4
  store i32 255, ptr %10, align 4
  store i32 255, ptr %11, align 4
  store i32 255, ptr %53, align 4
  call void @FlowWingAnim.getColor(ptr %53, ptr %9, ptr %10, ptr %11, ptr %53, ptr %0)
  %54 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 1
  store i32 255, ptr %13, align 4
  store i32 0, ptr %14, align 4
  store i32 0, ptr %15, align 4
  store i32 255, ptr %54, align 4
  call void @FlowWingAnim.getColor(ptr %54, ptr %13, ptr %14, ptr %15, ptr %54, ptr %0)
  %55 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 2
  store i32 0, ptr %17, align 4
  store i32 255, ptr %18, align 4
  store i32 0, ptr %19, align 4
  store i32 255, ptr %55, align 4
  call void @FlowWingAnim.getColor(ptr %55, ptr %17, ptr %18, ptr %19, ptr %55, ptr %0)
  %56 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 3
  store i32 0, ptr %21, align 4
  store i32 0, ptr %22, align 4
  store i32 255, ptr %23, align 4
  store i32 255, ptr %56, align 4
  call void @FlowWingAnim.getColor(ptr %56, ptr %21, ptr %22, ptr %23, ptr %56, ptr %0)
  %57 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 4
  store i32 0, ptr %25, align 4
  store i32 82, ptr %26, align 4
  store i32 172, ptr %27, align 4
  store i32 255, ptr %57, align 4
  call void @FlowWingAnim.getColor(ptr %57, ptr %25, ptr %26, ptr %27, ptr %57, ptr %0)
  %58 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 5
  store i32 0, ptr %29, align 4
  store i32 0, ptr %30, align 4
  store i32 0, ptr %31, align 4
  store i32 0, ptr %58, align 4
  call void @FlowWingAnim.getColor(ptr %58, ptr %29, ptr %30, ptr %31, ptr %58, ptr %0)
  %59 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 6
  store i32 40, ptr %33, align 4
  store i32 40, ptr %34, align 4
  store i32 40, ptr %35, align 4
  store i32 255, ptr %59, align 4
  call void @FlowWingAnim.getColor(ptr %59, ptr %33, ptr %34, ptr %35, ptr %59, ptr %0)
  %60 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 7
  store i32 100, ptr %37, align 4
  store i32 100, ptr %38, align 4
  store i32 100, ptr %39, align 4
  store i32 255, ptr %60, align 4
  call void @FlowWingAnim.getColor(ptr %60, ptr %37, ptr %38, ptr %39, ptr %60, ptr %0)
  %61 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 8
  store i32 245, ptr %41, align 4
  store i32 245, ptr %42, align 4
  store i32 245, ptr %43, align 4
  store i32 255, ptr %61, align 4
  call void @FlowWingAnim.getColor(ptr %61, ptr %41, ptr %42, ptr %43, ptr %61, ptr %0)
  %62 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 9
  store i32 200, ptr %45, align 4
  store i32 200, ptr %46, align 4
  store i32 200, ptr %47, align 4
  store i32 255, ptr %62, align 4
  call void @FlowWingAnim.getColor(ptr %62, ptr %45, ptr %46, ptr %47, ptr %62, ptr %0)
  %63 = getelementptr inbounds %COLORS_TYPE.4, ptr %6, i32 0, i32 10
  store i32 0, ptr %49, align 4
  store i32 0, ptr %50, align 4
  store i32 0, ptr %51, align 4
  store i32 200, ptr %63, align 4
  call void @FlowWingAnim.getColor(ptr %63, ptr %49, ptr %50, ptr %51, ptr %63, ptr %0)
  %64 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %66 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock
  %68 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 0
  store i32 262, ptr %68, align 4
  %69 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 1
  store i32 263, ptr %69, align 4
  %70 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 2
  store i32 264, ptr %70, align 4
  %71 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 3
  store i32 265, ptr %71, align 4
  %72 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 4
  store i32 257, ptr %72, align 4
  %73 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 5
  store i32 256, ptr %73, align 4
  %74 = getelementptr inbounds %KEYS_TYPE.3, ptr %7, i32 0, i32 6
  store i32 32, ptr %74, align 4
  %75 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %77 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %79 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 0
  store i32 0, ptr %79, align 4
  %80 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 1
  store i32 1, ptr %80, align 4
  %81 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 2
  store i32 2, ptr %81, align 4
  %82 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 3
  store i32 3, ptr %82, align 4
  %83 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 4
  store i32 4, ptr %83, align 4
  %84 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 5
  store i32 5, ptr %84, align 4
  %85 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 6
  store i32 6, ptr %85, align 4
  %86 = getelementptr inbounds %LOG_TYPE.5, ptr %8, i32 0, i32 7
  store i32 7, ptr %86, align 4
  %87 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %88 = icmp eq i32 %87, 0
  br i1 %88, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %89 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %90 = icmp eq i32 %89, 0
  br i1 %90, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  call void @FlowWingAnim.setTargetFPS(ptr %0)
  %91 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  br label %afterNestedBlock
}

define void @FlowWingAnim.setTargetFPS(ptr %0) !rt !2 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %fps = load i32, ptr %5, align 4
  %9 = load i32, ptr %5, align 4
  call void @SetTargetFPS(i32 %9)
  %10 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.getColor(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !3 {
entry:
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 1
  %8 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 2
  %9 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 3
  %10 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 4
  %11 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 5
  %12 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 6
  %13 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 7
  %r = alloca i32, align 4
  %14 = load i32, ptr %1, align 4
  store i32 %14, ptr %r, align 4
  %g = alloca i32, align 4
  %15 = load i32, ptr %2, align 4
  store i32 %15, ptr %g, align 4
  %b = alloca i32, align 4
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %b, align 4
  %a = alloca i32, align 4
  %17 = load i32, ptr %4, align 4
  store i32 %17, ptr %a, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %a1 = load i32, ptr %a, align 4
  %18 = load i32, ptr %a, align 4
  %19 = mul i32 %18, 256
  %20 = mul i32 %19, 256
  %21 = mul i32 %20, 256
  %b2 = load i32, ptr %b, align 4
  %22 = load i32, ptr %b, align 4
  %23 = mul i32 %22, 256
  %24 = mul i32 %23, 256
  %25 = add i32 %21, %24
  %g3 = load i32, ptr %g, align 4
  %26 = load i32, ptr %g, align 4
  %27 = mul i32 %26, 256
  %28 = add i32 %25, %27
  %r4 = load i32, ptr %r, align 4
  %29 = load i32, ptr %r, align 4
  %30 = add i32 %28, %29
  store i32 %30, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %31 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.createWindow(ptr %0) !rt !4 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %9 = load ptr, ptr %0, align 8
  %10 = getelementptr inbounds %FlowWingAnim, ptr %9, i32 0, i32 2
  %screenHeight = load i32, ptr %10, align 4
  %11 = load i32, ptr %10, align 4
  %12 = load ptr, ptr %0, align 8
  %13 = getelementptr inbounds %FlowWingAnim, ptr %12, i32 0, i32 1
  %screenWidth = load i32, ptr %13, align 4
  %14 = load i32, ptr %13, align 4
  %15 = load ptr, ptr %0, align 8
  %16 = getelementptr inbounds %FlowWingAnim, ptr %15, i32 0, i32 3
  %screenName = load ptr, ptr %16, align 8
  %17 = load ptr, ptr %16, align 8
  call void @InitWindow(i32 %11, i32 %14, ptr %17)
  %18 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.clearBackground(ptr %0, ptr %1) !rt !5 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %color = alloca i32, align 4
  %10 = load i32, ptr %0, align 4
  store i32 %10, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %color1 = load i32, ptr %color, align 4
  %11 = load i32, ptr %color, align 4
  call void @ClearBackground(i32 %11)
  %12 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.windowShouldClose(ptr %0, ptr %1) !rt !6 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %10 = call i1 @WindowShouldClose()
  store i1 %10, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.beginDrawing(ptr %0) !rt !7 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @BeginDrawing()
  %9 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawRectangle(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !8 {
entry:
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 1
  %8 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 2
  %9 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 3
  %10 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 4
  %11 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 5
  %12 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 6
  %13 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 7
  %posX = alloca i32, align 4
  %14 = load i32, ptr %0, align 4
  store i32 %14, ptr %posX, align 4
  %posY = alloca i32, align 4
  %15 = load i32, ptr %1, align 4
  store i32 %15, ptr %posY, align 4
  %width = alloca i32, align 4
  %16 = load i32, ptr %2, align 4
  store i32 %16, ptr %width, align 4
  %height = alloca i32, align 4
  %17 = load i32, ptr %3, align 4
  store i32 %17, ptr %height, align 4
  %color = alloca i32, align 4
  %18 = load i32, ptr %4, align 4
  store i32 %18, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %posX1 = load i32, ptr %posX, align 4
  %19 = load i32, ptr %posX, align 4
  %posY2 = load i32, ptr %posY, align 4
  %20 = load i32, ptr %posY, align 4
  %width3 = load i32, ptr %width, align 4
  %21 = load i32, ptr %width, align 4
  %height4 = load i32, ptr %height, align 4
  %22 = load i32, ptr %height, align 4
  %color5 = load i32, ptr %color, align 4
  %23 = load i32, ptr %color, align 4
  call void @DrawRectangle(i32 %19, i32 %20, i32 %21, i32 %22, i32 %23)
  %24 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawRectangleLines(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !9 {
entry:
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 1
  %8 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 2
  %9 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 3
  %10 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 4
  %11 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 5
  %12 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 6
  %13 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 7
  %posX = alloca i32, align 4
  %14 = load i32, ptr %0, align 4
  store i32 %14, ptr %posX, align 4
  %posY = alloca i32, align 4
  %15 = load i32, ptr %1, align 4
  store i32 %15, ptr %posY, align 4
  %width = alloca i32, align 4
  %16 = load i32, ptr %2, align 4
  store i32 %16, ptr %width, align 4
  %height = alloca i32, align 4
  %17 = load i32, ptr %3, align 4
  store i32 %17, ptr %height, align 4
  %color = alloca i32, align 4
  %18 = load i32, ptr %4, align 4
  store i32 %18, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %posX1 = load i32, ptr %posX, align 4
  %19 = load i32, ptr %posX, align 4
  %posY2 = load i32, ptr %posY, align 4
  %20 = load i32, ptr %posY, align 4
  %width3 = load i32, ptr %width, align 4
  %21 = load i32, ptr %width, align 4
  %height4 = load i32, ptr %height, align 4
  %22 = load i32, ptr %height, align 4
  %color5 = load i32, ptr %color, align 4
  %23 = load i32, ptr %color, align 4
  call void @DrawRectangleLines(i32 %19, i32 %20, i32 %21, i32 %22, i32 %23)
  %24 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawRectangleLinesEx(ptr %0, ptr %1, ptr %2, ptr %3) !rt !10 {
entry:
  %4 = load ptr, ptr %3, align 8
  %5 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 6
  %11 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 7
  %rec = alloca %Rectangle.2, align 8
  %12 = load %Rectangle.2, ptr %0, align 4
  store %Rectangle.2 %12, ptr %rec, align 4
  %lineThick = alloca float, align 4
  %13 = load float, ptr %1, align 4
  store float %13, ptr %lineThick, align 4
  %color = alloca i32, align 4
  %14 = load i32, ptr %2, align 4
  store i32 %14, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %lineThick1 = load float, ptr %lineThick, align 4
  %15 = load float, ptr %lineThick, align 4
  %color2 = load i32, ptr %color, align 4
  %16 = load i32, ptr %color, align 4
  call void @DrawRectangleLinesEx(ptr %rec, float %15, i32 %16)
  %17 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.endDrawing(ptr %0) !rt !11 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @EndDrawing()
  %9 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.closeWindow(ptr %0) !rt !12 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @CloseWindow()
  %9 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.getTime(ptr %0, ptr %1) !rt !13 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %10 = call double @GetTime()
  store double %10, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.getFrameTime(ptr %0, ptr %1) !rt !14 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %10 = call float @GetFrameTime()
  store float %10, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.getScreenHeight(ptr %0, ptr %1) !rt !15 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %10 = call i32 @GetScreenHeight()
  store i32 %10, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.getScreenWidth(ptr %0, ptr %1) !rt !16 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %10 = call i32 @GetScreenWidth()
  store i32 %10, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.drawCircle(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !17 {
entry:
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 7
  %centerX = alloca i32, align 4
  %13 = load i32, ptr %0, align 4
  store i32 %13, ptr %centerX, align 4
  %centerY = alloca i32, align 4
  %14 = load i32, ptr %1, align 4
  store i32 %14, ptr %centerY, align 4
  %radius = alloca float, align 4
  %15 = load float, ptr %2, align 4
  store float %15, ptr %radius, align 4
  %color = alloca i32, align 4
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %centerX1 = load i32, ptr %centerX, align 4
  %17 = load i32, ptr %centerX, align 4
  %centerY2 = load i32, ptr %centerY, align 4
  %18 = load i32, ptr %centerY, align 4
  %radius3 = load float, ptr %radius, align 4
  %19 = load float, ptr %radius, align 4
  %color4 = load i32, ptr %color, align 4
  %20 = load i32, ptr %color, align 4
  call void @DrawCircle(i32 %17, i32 %18, float %19, i32 %20)
  %21 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawText(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !18 {
entry:
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 1
  %8 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 2
  %9 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 3
  %10 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 4
  %11 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 5
  %12 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 6
  %13 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 7
  %text = alloca ptr, align 8
  %14 = load ptr, ptr %0, align 8
  store ptr %14, ptr %text, align 8
  %posX = alloca i32, align 4
  %15 = load i32, ptr %1, align 4
  store i32 %15, ptr %posX, align 4
  %posY = alloca i32, align 4
  %16 = load i32, ptr %2, align 4
  store i32 %16, ptr %posY, align 4
  %fontSize = alloca i32, align 4
  %17 = load i32, ptr %3, align 4
  store i32 %17, ptr %fontSize, align 4
  %color = alloca i32, align 4
  %18 = load i32, ptr %4, align 4
  store i32 %18, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %text1 = load ptr, ptr %text, align 8
  %19 = load ptr, ptr %text, align 8
  %posX2 = load i32, ptr %posX, align 4
  %20 = load i32, ptr %posX, align 4
  %posY3 = load i32, ptr %posY, align 4
  %21 = load i32, ptr %posY, align 4
  %fontSize4 = load i32, ptr %fontSize, align 4
  %22 = load i32, ptr %fontSize, align 4
  %color5 = load i32, ptr %color, align 4
  %23 = load i32, ptr %color, align 4
  call void @DrawText(ptr %19, i32 %20, i32 %21, i32 %22, i32 %23)
  %24 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawTexture(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !19 {
entry:
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 7
  %texture = alloca %Texture.0, align 8
  %13 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %13, ptr %texture, align 4
  %posX = alloca i32, align 4
  %14 = load i32, ptr %1, align 4
  store i32 %14, ptr %posX, align 4
  %posY = alloca i32, align 4
  %15 = load i32, ptr %2, align 4
  store i32 %15, ptr %posY, align 4
  %color = alloca i32, align 4
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %posX1 = load i32, ptr %posX, align 4
  %17 = load i32, ptr %posX, align 4
  %posY2 = load i32, ptr %posY, align 4
  %18 = load i32, ptr %posY, align 4
  %color3 = load i32, ptr %color, align 4
  %19 = load i32, ptr %color, align 4
  call void @DrawTexture(ptr %texture, i32 %17, i32 %18, i32 %19)
  %20 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.getMousePosition(ptr %0, ptr %1) !rt !20 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  %y = alloca i32, align 4
  store i32 0, ptr %y, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %mergeBlock, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %10 = call i32 @GetMouseX()
  store i32 %10, ptr %x, align 4
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %13 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %15 = call i32 @GetMouseY()
  store i32 %15, ptr %y, align 4
  %16 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %18 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  br label %returnBlock

checkContinueBlock4:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock3
  %20 = getelementptr inbounds %Position.7, ptr %0, i32 0, i32 0
  %x5 = load i32, ptr %x, align 4
  %21 = load i32, ptr %x, align 4
  %22 = sitofp i32 %21 to float
  store float %22, ptr %20, align 4
  %23 = getelementptr inbounds %Position.7, ptr %0, i32 0, i32 1
  %y6 = load i32, ptr %y, align 4
  %24 = load i32, ptr %y, align 4
  %25 = sitofp i32 %24 to float
  store float %25, ptr %23, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %26 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock4, label %afterNestedBlock
}

define void @FlowWingAnim.drawTexturePro(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5, ptr %6) !rt !21 {
entry:
  %7 = load ptr, ptr %6, align 8
  %8 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 1
  %9 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 2
  %10 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 3
  %11 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 4
  %12 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 5
  %13 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 6
  %14 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = load [4 x float], ptr %1, align 4
  %16 = load [4 x float], ptr %2, align 4
  %17 = load [2 x float], ptr %3, align 4
  %rotation = load float, ptr %4, align 4
  %18 = load float, ptr %4, align 4
  %color = load i32, ptr %5, align 4
  %19 = load i32, ptr %5, align 4
  call void @DrawTexturePro(ptr %0, [4 x float] %15, [4 x float] %16, [2 x float] %17, float %18, i32 %19)
  %20 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.traceLog(ptr %0, ptr %1, ptr %2) !rt !22 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 3
  %7 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 4
  %8 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 5
  %9 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 6
  %10 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 7
  %logLevel = alloca i32, align 4
  %11 = load i32, ptr %0, align 4
  store i32 %11, ptr %logLevel, align 4
  %text = alloca ptr, align 8
  %12 = load ptr, ptr %1, align 8
  store ptr %12, ptr %text, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %logLevel1 = load i32, ptr %logLevel, align 4
  %13 = load i32, ptr %logLevel, align 4
  %text2 = load ptr, ptr %text, align 8
  %14 = load ptr, ptr %text, align 8
  call void @TraceLog(i32 %13, ptr %14)
  %15 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.loadTexture(ptr %0, ptr %1, ptr %2) !rt !23 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 3
  %7 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 4
  %8 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 5
  %9 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 6
  %10 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 7
  %fileName = alloca ptr, align 8
  %11 = load ptr, ptr %1, align 8
  store ptr %11, ptr %fileName, align 8
  %rtPtr = alloca %Texture.0, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %fileName1 = load ptr, ptr %fileName, align 8
  %12 = load ptr, ptr %fileName, align 8
  call void @LoadTexture(ptr %0, ptr %12)
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.unloadTexture(ptr %0, ptr %1) !rt !24 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %texture = alloca %Texture.0, align 8
  %10 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %10, ptr %texture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @UnloadTexture(ptr %texture)
  %11 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.isKeyPressed(ptr %0, ptr %1, ptr %2) !rt !25 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 3
  %7 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 4
  %8 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 5
  %9 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 6
  %10 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 7
  %key = alloca i32, align 4
  %11 = load i32, ptr %1, align 4
  store i32 %11, ptr %key, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %key1 = load i32, ptr %key, align 4
  %12 = load i32, ptr %key, align 4
  %13 = call i1 @IsKeyPressed(i32 %12)
  store i1 %13, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.isKeyDown(ptr %0, ptr %1, ptr %2) !rt !26 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 3
  %7 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 4
  %8 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 5
  %9 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 6
  %10 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 7
  %key = alloca i32, align 4
  %11 = load i32, ptr %1, align 4
  store i32 %11, ptr %key, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %key1 = load i32, ptr %key, align 4
  %12 = load i32, ptr %key, align 4
  %13 = call i1 @IsKeyDown(i32 %12)
  store i1 %13, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.textFormat(ptr %0, ptr %1, ptr %2) !rt !27 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 3
  %7 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 4
  %8 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 5
  %9 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 6
  %10 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 7
  %text = alloca ptr, align 8
  %11 = load ptr, ptr %1, align 8
  store ptr %11, ptr %text, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %text1 = load ptr, ptr %text, align 8
  %12 = load ptr, ptr %text, align 8
  %13 = call ptr @TextFormat(ptr %12)
  store ptr %13, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define i32 @FlowWingAnim.measureText(ptr %0, i32 %1, ptr %2) !rt !28 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 2
  %6 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 3
  %7 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 4
  %8 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 5
  %9 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 6
  %10 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 7
  %text = alloca ptr, align 8
  store ptr %0, ptr %text, align 8
  %fontSize = alloca i32, align 4
  store i32 %1, ptr %fontSize, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %text1 = load ptr, ptr %text, align 8
  %11 = load ptr, ptr %text, align 8
  %fontSize2 = load i32, ptr %fontSize, align 4
  %12 = load i32, ptr %fontSize, align 4
  %13 = call i32 @MeasureText(ptr %11, i32 %12)
  ret i32 %13

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.drawBoxWithText(ptr %0, ptr %1) !rt !29 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %boxWithtext = alloca %BoxWithText.6, align 8
  %10 = load %BoxWithText.6, ptr %0, align 8
  store %BoxWithText.6 %10, ptr %boxWithtext, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %11 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 1
  %posX = load i32, ptr %11, align 4
  %12 = load i32, ptr %11, align 4
  %13 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 2
  %posY = load i32, ptr %13, align 4
  %14 = load i32, ptr %13, align 4
  %15 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 3
  %width = load i32, ptr %15, align 4
  %16 = load i32, ptr %15, align 4
  %17 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 4
  %height = load i32, ptr %17, align 4
  %18 = load i32, ptr %17, align 4
  %19 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 8
  %backgroundColor = load i32, ptr %19, align 4
  %20 = load i32, ptr %19, align 4
  call void @DrawRectangle(i32 %12, i32 %14, i32 %16, i32 %18, i32 %20)
  %21 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %23 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %25 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 0
  %text = load ptr, ptr %25, align 8
  %26 = load ptr, ptr %25, align 8
  %27 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 1
  %posX3 = load i32, ptr %27, align 4
  %28 = load i32, ptr %27, align 4
  %29 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 2
  %posY4 = load i32, ptr %29, align 4
  %30 = load i32, ptr %29, align 4
  %31 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 7
  %fontSize = load i32, ptr %31, align 4
  %32 = load i32, ptr %31, align 4
  %33 = getelementptr inbounds %BoxWithText.6, ptr %boxWithtext, i32 0, i32 5
  %textColor = load i32, ptr %33, align 4
  %34 = load i32, ptr %33, align 4
  call void @DrawText(ptr %26, i32 %28, i32 %30, i32 %32, i32 %34)
  %35 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib()

declare !rt !30 void @InitWindow(i32, i32, ptr)

declare !rt !31 void @SetTargetFPS(i32)

declare !rt !32 void @ClearBackground(i32)

declare !rt !33 i1 @WindowShouldClose()

declare !rt !34 void @BeginDrawing()

declare !rt !35 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !36 void @DrawRectangleLines(i32, i32, i32, i32, i32)

declare !rt !37 void @EndDrawing()

declare !rt !38 void @CloseWindow()

declare !rt !39 i32 @GetScreenHeight()

declare !rt !40 i32 @GetScreenWidth()

declare !rt !41 i32 @GetMouseX()

declare !rt !42 i32 @GetMouseY()

declare !rt !43 void @DrawCircle(i32, i32, float, i32)

declare !rt !44 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !45 i32 @MeasureText(ptr, i32)

declare !rt !46 i1 @IsKeyPressed(i32)

declare !rt !47 i1 @IsKeyDown(i32)

declare !rt !48 ptr @TextFormat(ptr)

declare !rt !49 void @LoadTexture(ptr sret(%Texture.0), ptr)

declare !rt !50 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !51 void @UnloadTexture(ptr)

declare !rt !52 void @DrawRectangleLinesEx(ptr, float, i32)

declare !rt !53 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !54 void @TraceLog(i32, ptr)

declare !rt !55 double @GetTime()

declare !rt !56 float @GetFrameTime()

define void @drawTexturePro(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !57 {
entry:
  %texture = alloca %Texture.0, align 8
  %6 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %6, ptr %texture, align 4
  %source = alloca [4 x float], align 4, !ET !58, !I !59
  %7 = load [4 x float], ptr %1, align 4
  store [4 x float] %7, ptr %source, align 4
  %dest = alloca [4 x float], align 4, !ET !58, !I !59
  %8 = load [4 x float], ptr %2, align 4
  store [4 x float] %8, ptr %dest, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %9 = load [4 x float], ptr %source, align 4
  %10 = load [4 x float], ptr %dest, align 4
  %11 = load [2 x float], ptr %3, align 4
  %rotation = load float, ptr %4, align 4
  %12 = load float, ptr %4, align 4
  %color = load i32, ptr %5, align 4
  %13 = load i32, ptr %5, align 4
  call void @DrawTexturePro(ptr %texture, [4 x float] %9, [4 x float] %10, [2 x float] %11, float %12, i32 %13)
  %14 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

declare !rt !60 double @sin(double)

define double @getSin(ptr %0) !rt !61 {
entry:
  %val = alloca double, align 8
  %1 = load double, ptr %0, align 8
  store double %1, ptr %val, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret double 0.000000e+00

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %val1 = load double, ptr %val, align 8
  %2 = load double, ptr %val, align 8
  %3 = call double @sin(double %2)
  ret double %3

mergeBlock:                                       ; No predecessors!
  %4 = load i32, ptr @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock, label %afterNestedBlock
}

define internal void @"assign_<Object<COLORS_TYPE.4>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 6
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 7
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 8
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 9
  store i32 0, ptr %10, align 4
  %11 = getelementptr inbounds %COLORS_TYPE.4, ptr %0, i32 0, i32 10
  store i32 0, ptr %11, align 4
  ret void
}

define internal void @"assign_<Object<KEYS_TYPE.3>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %KEYS_TYPE.3, ptr %0, i32 0, i32 6
  store i32 0, ptr %7, align 4
  ret void
}

define internal void @"assign_<Object<LOG_TYPE.5>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 6
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %LOG_TYPE.5, ptr %0, i32 0, i32 7
  store i32 0, ptr %8, align 4
  ret void
}

!0 = !{!"FlowWingAnim.init4:rt:pr:27"}
!1 = !{!"FlowWingAnim.beforeInit:rt:pr:27"}
!2 = !{!"FlowWingAnim.setTargetFPS:rt:pr:27"}
!3 = !{!"FlowWingAnim.getColor:rt:pr:28"}
!4 = !{!"FlowWingAnim.createWindow:rt:pr:27"}
!5 = !{!"FlowWingAnim.clearBackground:rt:pr:27"}
!6 = !{!"FlowWingAnim.windowShouldClose:rt:pr:34"}
!7 = !{!"FlowWingAnim.beginDrawing:rt:pr:27"}
!8 = !{!"FlowWingAnim.drawRectangle:rt:pr:27"}
!9 = !{!"FlowWingAnim.drawRectangleLines:rt:pr:27"}
!10 = !{!"FlowWingAnim.drawRectangleLinesEx:rt:pr:27"}
!11 = !{!"FlowWingAnim.endDrawing:rt:pr:27"}
!12 = !{!"FlowWingAnim.closeWindow:rt:pr:27"}
!13 = !{!"FlowWingAnim.getTime:rt:pr:31"}
!14 = !{!"FlowWingAnim.getFrameTime:rt:pr:32"}
!15 = !{!"FlowWingAnim.getScreenHeight:rt:pr:28"}
!16 = !{!"FlowWingAnim.getScreenWidth:rt:pr:28"}
!17 = !{!"FlowWingAnim.drawCircle:rt:pr:27"}
!18 = !{!"FlowWingAnim.drawText:rt:pr:27"}
!19 = !{!"FlowWingAnim.drawTexture:rt:pr:27"}
!20 = !{!"FlowWingAnim.getMousePosition:rt:ob:Position.7"}
!21 = !{!"FlowWingAnim.drawTexturePro:rt:pr:27"}
!22 = !{!"FlowWingAnim.traceLog:rt:pr:27"}
!23 = !{!"FlowWingAnim.loadTexture:rt:ob:Texture.0"}
!24 = !{!"FlowWingAnim.unloadTexture:rt:pr:27"}
!25 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!26 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!27 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!28 = !{!"FlowWingAnim.measureText:rt:pr:28"}
!29 = !{!"FlowWingAnim.drawBoxWithText:rt:pr:27"}
!30 = !{!"InitWindow:rt:pr:27"}
!31 = !{!"SetTargetFPS:rt:pr:27"}
!32 = !{!"ClearBackground:rt:pr:27"}
!33 = !{!"WindowShouldClose:rt:pr:34"}
!34 = !{!"BeginDrawing:rt:pr:27"}
!35 = !{!"DrawRectangle:rt:pr:27"}
!36 = !{!"DrawRectangleLines:rt:pr:27"}
!37 = !{!"EndDrawing:rt:pr:27"}
!38 = !{!"CloseWindow:rt:pr:27"}
!39 = !{!"GetScreenHeight:rt:pr:28"}
!40 = !{!"GetScreenWidth:rt:pr:28"}
!41 = !{!"GetMouseX:rt:pr:28"}
!42 = !{!"GetMouseY:rt:pr:28"}
!43 = !{!"DrawCircle:rt:pr:27"}
!44 = !{!"DrawText:rt:pr:27"}
!45 = !{!"MeasureText:rt:pr:28"}
!46 = !{!"IsKeyPressed:rt:pr:34"}
!47 = !{!"IsKeyDown:rt:pr:34"}
!48 = !{!"TextFormat:rt:pr:33"}
!49 = !{!"LoadTexture:rt:ob:Texture.0"}
!50 = !{!"DrawTexture:rt:pr:27"}
!51 = !{!"UnloadTexture:rt:pr:27"}
!52 = !{!"DrawRectangleLinesEx:rt:pr:27"}
!53 = !{!"DrawTexturePro:rt:pr:27"}
!54 = !{!"TraceLog:rt:pr:27"}
!55 = !{!"GetTime:rt:pr:31"}
!56 = !{!"GetFrameTime:rt:pr:32"}
!57 = !{!"drawTexturePro:rt:pr:27"}
!58 = !{!"32"}
!59 = !{!"4:"}
!60 = !{!"sin:rt:pr:31"}
!61 = !{!"getSin:rt:pr:31"}
