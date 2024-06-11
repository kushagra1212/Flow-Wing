; ModuleID = 'iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim'
source_filename = "iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim"
target triple = "x86_64-apple-macosx14.0.0"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.3, %KEYS_TYPE.2, %LOG_TYPE.1 }
%COLORS_TYPE.3 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.2 = type { i32, i32, i32, i32 }
%LOG_TYPE.1 = type { i32, i32, i32, i32, i32, i32, i32, i32 }

@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_NULL = external global i8
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.FlowWingAnim.fg = common global %"FlowWingAnim::VTableType" zeroinitializer

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

define i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim() {
entry:
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib()

declare !rt !0 void @getRandomNumber(ptr, ptr, ptr)

declare !rt !1 void @srand(i32)

declare !rt !2 i32 @rand()

declare !rt !3 float @GetFrameTime()

declare !rt !4 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !5 void @UnloadTexture(ptr)

declare !rt !6 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !7 double @GetTime()

declare !rt !8 ptr @TextFormat(ptr)

declare !rt !9 void @LoadTexture(ptr sret(%Texture.0) align 4, ptr)

declare !rt !10 i1 @IsKeyDown(i32)

declare !rt !11 void @SetTargetFPS(i32)

declare !rt !12 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !13 i32 @GetScreenHeight()

declare !rt !14 void @CloseWindow()

declare !rt !15 void @InitWindow(i32, i32, ptr)

declare !rt !16 void @EndDrawing()

declare !rt !17 i1 @IsKeyPressed(i32)

declare !rt !18 i32 @time()

declare !rt !19 void @BeginDrawing()

declare !rt !20 void @TraceLog(i32, ptr)

declare !rt !21 i1 @WindowShouldClose()

declare !rt !22 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !23 void @DrawCircle(i32, i32, float, i32)

declare !rt !24 i32 @GetScreenWidth()

declare !rt !25 void @ClearBackground(i32)

define void @FlowWingAnim.init4(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !26 {
entry:
  %5 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 6
  %11 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 7
  %screenHeight = alloca i32, align 4
  %12 = load i32, ptr %0, align 4
  store i32 %12, ptr %screenHeight, align 4
  %screenWidth = alloca i32, align 4
  %13 = load i32, ptr %1, align 4
  store i32 %13, ptr %screenWidth, align 4
  %screenName = alloca ptr, align 8
  %14 = load ptr, ptr %2, align 8
  store ptr %14, ptr %screenName, align 8
  %fps = alloca i32, align 4
  %15 = load i32, ptr %3, align 4
  store i32 %15, ptr %fps, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %16 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %fps11 = load i32, ptr %16, align 4
  store i32 60, ptr %16, align 4
  %17 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %19 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %21 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %fps12 = load i32, ptr %21, align 4
  %fps13 = load i32, ptr %fps, align 4
  %22 = load i32, ptr %fps, align 4
  store i32 %22, ptr %21, align 4
  %23 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %25 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  call void @FlowWingAnim.beforeInit(ptr %4)
  %27 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %29 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %31 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 2
  %screenHeight14 = load i32, ptr %31, align 4
  %screenHeight15 = load i32, ptr %screenHeight, align 4
  %32 = load i32, ptr %screenHeight, align 4
  store i32 %32, ptr %31, align 4
  %33 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %35 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %37 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 1
  %screenWidth16 = load i32, ptr %37, align 4
  %screenWidth17 = load i32, ptr %screenWidth, align 4
  %38 = load i32, ptr %screenWidth, align 4
  store i32 %38, ptr %37, align 4
  %39 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %41 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %43 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 3
  %screenName18 = load ptr, ptr %43, align 8
  %screenName19 = load ptr, ptr %screenName, align 8
  %44 = load ptr, ptr %screenName, align 8
  store ptr %44, ptr %43, align 8
  %45 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  br label %afterNestedBlock
}

define void @FlowWingAnim.beforeInit(ptr %0) !rt !27 {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = getelementptr inbounds %COLORS_TYPE.3, ptr %5, i32 0, i32 0
  %9 = alloca i32, align 4
  store i32 255, ptr %9, align 4
  %10 = alloca i32, align 4
  store i32 255, ptr %10, align 4
  %11 = alloca i32, align 4
  store i32 255, ptr %11, align 4
  %12 = alloca i32, align 4
  store i32 255, ptr %12, align 4
  call void @FlowWingAnim.getColor(ptr %8, ptr %9, ptr %10, ptr %11, ptr %12, ptr %0)
  %13 = getelementptr inbounds %COLORS_TYPE.3, ptr %5, i32 0, i32 1
  %14 = alloca i32, align 4
  store i32 255, ptr %14, align 4
  %15 = alloca i32, align 4
  store i32 0, ptr %15, align 4
  %16 = alloca i32, align 4
  store i32 0, ptr %16, align 4
  %17 = alloca i32, align 4
  store i32 255, ptr %17, align 4
  call void @FlowWingAnim.getColor(ptr %13, ptr %14, ptr %15, ptr %16, ptr %17, ptr %0)
  %18 = getelementptr inbounds %COLORS_TYPE.3, ptr %5, i32 0, i32 2
  %19 = alloca i32, align 4
  store i32 0, ptr %19, align 4
  %20 = alloca i32, align 4
  store i32 255, ptr %20, align 4
  %21 = alloca i32, align 4
  store i32 0, ptr %21, align 4
  %22 = alloca i32, align 4
  store i32 255, ptr %22, align 4
  call void @FlowWingAnim.getColor(ptr %18, ptr %19, ptr %20, ptr %21, ptr %22, ptr %0)
  %23 = getelementptr inbounds %COLORS_TYPE.3, ptr %5, i32 0, i32 3
  %24 = alloca i32, align 4
  store i32 0, ptr %24, align 4
  %25 = alloca i32, align 4
  store i32 0, ptr %25, align 4
  %26 = alloca i32, align 4
  store i32 255, ptr %26, align 4
  %27 = alloca i32, align 4
  store i32 255, ptr %27, align 4
  call void @FlowWingAnim.getColor(ptr %23, ptr %24, ptr %25, ptr %26, ptr %27, ptr %0)
  %28 = getelementptr inbounds %COLORS_TYPE.3, ptr %5, i32 0, i32 4
  %29 = alloca i32, align 4
  store i32 0, ptr %29, align 4
  %30 = alloca i32, align 4
  store i32 82, ptr %30, align 4
  %31 = alloca i32, align 4
  store i32 172, ptr %31, align 4
  %32 = alloca i32, align 4
  store i32 255, ptr %32, align 4
  call void @FlowWingAnim.getColor(ptr %28, ptr %29, ptr %30, ptr %31, ptr %32, ptr %0)
  %33 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %35 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %37 = getelementptr inbounds %KEYS_TYPE.2, ptr %6, i32 0, i32 0
  store i32 262, ptr %37, align 4
  %38 = getelementptr inbounds %KEYS_TYPE.2, ptr %6, i32 0, i32 1
  store i32 263, ptr %38, align 4
  %39 = getelementptr inbounds %KEYS_TYPE.2, ptr %6, i32 0, i32 2
  store i32 264, ptr %39, align 4
  %40 = getelementptr inbounds %KEYS_TYPE.2, ptr %6, i32 0, i32 3
  store i32 265, ptr %40, align 4
  %41 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %43 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %45 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 0
  store i32 0, ptr %45, align 4
  %46 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 1
  store i32 1, ptr %46, align 4
  %47 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 2
  store i32 2, ptr %47, align 4
  %48 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 3
  store i32 3, ptr %48, align 4
  %49 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 4
  store i32 4, ptr %49, align 4
  %50 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 5
  store i32 5, ptr %50, align 4
  %51 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 6
  store i32 6, ptr %51, align 4
  %52 = getelementptr inbounds %LOG_TYPE.1, ptr %7, i32 0, i32 7
  store i32 7, ptr %52, align 4
  %53 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %55 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  call void @FlowWingAnim.setTargetFPS(ptr %0)
  %57 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @FlowWingAnim.setTargetFPS(ptr %0) !rt !28 {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %fps = load i32, ptr %4, align 4
  %8 = load i32, ptr %4, align 4
  call void @SetTargetFPS(i32 %8)
  %9 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.getColor(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !29 {
entry:
  %6 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 7
  %r = alloca i32, align 4
  %13 = load i32, ptr %1, align 4
  store i32 %13, ptr %r, align 4
  %g = alloca i32, align 4
  %14 = load i32, ptr %2, align 4
  store i32 %14, ptr %g, align 4
  %b = alloca i32, align 4
  %15 = load i32, ptr %3, align 4
  store i32 %15, ptr %b, align 4
  %a = alloca i32, align 4
  %16 = load i32, ptr %4, align 4
  store i32 %16, ptr %a, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %a1 = load i32, ptr %a, align 4
  %17 = load i32, ptr %a, align 4
  %18 = mul i32 %17, 256
  %19 = alloca i32, align 4
  store i32 %18, ptr %19, align 4
  %20 = load i32, ptr %19, align 4
  %21 = mul i32 %20, 256
  %22 = alloca i32, align 4
  store i32 %21, ptr %22, align 4
  %23 = load i32, ptr %22, align 4
  %24 = mul i32 %23, 256
  %25 = alloca i32, align 4
  store i32 %24, ptr %25, align 4
  %26 = load i32, ptr %25, align 4
  %b2 = load i32, ptr %b, align 4
  %27 = load i32, ptr %b, align 4
  %28 = mul i32 %27, 256
  %29 = alloca i32, align 4
  store i32 %28, ptr %29, align 4
  %30 = load i32, ptr %29, align 4
  %31 = mul i32 %30, 256
  %32 = alloca i32, align 4
  store i32 %31, ptr %32, align 4
  %33 = load i32, ptr %32, align 4
  %34 = add i32 %26, %33
  %35 = alloca i32, align 4
  store i32 %34, ptr %35, align 4
  %36 = load i32, ptr %35, align 4
  %g3 = load i32, ptr %g, align 4
  %37 = load i32, ptr %g, align 4
  %38 = mul i32 %37, 256
  %39 = alloca i32, align 4
  store i32 %38, ptr %39, align 4
  %40 = load i32, ptr %39, align 4
  %41 = add i32 %36, %40
  %42 = alloca i32, align 4
  store i32 %41, ptr %42, align 4
  %43 = load i32, ptr %42, align 4
  %r4 = load i32, ptr %r, align 4
  %44 = load i32, ptr %r, align 4
  %45 = add i32 %43, %44
  %46 = alloca i32, align 4
  store i32 %45, ptr %46, align 4
  %47 = load i32, ptr %46, align 4
  store i32 %47, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %48 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.createWindow(ptr %0) !rt !30 {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %screenHeight = load i32, ptr %8, align 4
  %9 = load i32, ptr %8, align 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %screenWidth = load i32, ptr %10, align 4
  %11 = load i32, ptr %10, align 4
  %12 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %screenName = load ptr, ptr %12, align 8
  %13 = load ptr, ptr %12, align 8
  call void @InitWindow(i32 %9, i32 %11, ptr %13)
  %14 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.clearBackground(ptr %0, ptr %1) !rt !31 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  %color = alloca i32, align 4
  %9 = load i32, ptr %0, align 4
  store i32 %9, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %color1 = load i32, ptr %color, align 4
  %10 = load i32, ptr %color, align 4
  call void @ClearBackground(i32 %10)
  %11 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.windowShouldClose(ptr %0, ptr %1) !rt !32 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %9 = call i1 @WindowShouldClose()
  store i1 %9, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.beginDrawing(ptr %0) !rt !33 {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @BeginDrawing()
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawRectangle(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !34 {
entry:
  %6 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 7
  %posX = alloca i32, align 4
  %13 = load i32, ptr %0, align 4
  store i32 %13, ptr %posX, align 4
  %posY = alloca i32, align 4
  %14 = load i32, ptr %1, align 4
  store i32 %14, ptr %posY, align 4
  %width = alloca i32, align 4
  %15 = load i32, ptr %2, align 4
  store i32 %15, ptr %width, align 4
  %height = alloca i32, align 4
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %height, align 4
  %color = alloca i32, align 4
  %17 = load i32, ptr %4, align 4
  store i32 %17, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %posX1 = load i32, ptr %posX, align 4
  %18 = load i32, ptr %posX, align 4
  %posY2 = load i32, ptr %posY, align 4
  %19 = load i32, ptr %posY, align 4
  %width3 = load i32, ptr %width, align 4
  %20 = load i32, ptr %width, align 4
  %height4 = load i32, ptr %height, align 4
  %21 = load i32, ptr %height, align 4
  %color5 = load i32, ptr %color, align 4
  %22 = load i32, ptr %color, align 4
  call void @DrawRectangle(i32 %18, i32 %19, i32 %20, i32 %21, i32 %22)
  %23 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.endDrawing(ptr %0) !rt !35 {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @EndDrawing()
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.closeWindow(ptr %0) !rt !36 {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @CloseWindow()
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.getTime(ptr %0, ptr %1) !rt !37 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %9 = call double @GetTime()
  store double %9, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.getFrameTime(ptr %0, ptr %1) !rt !38 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %9 = call float @GetFrameTime()
  store float %9, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.getScreenHeight(ptr %0, ptr %1) !rt !39 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %9 = call i32 @GetScreenHeight()
  store i32 %9, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.getScreenWidth(ptr %0, ptr %1) !rt !40 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %9 = call i32 @GetScreenWidth()
  store i32 %9, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %10 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.drawCircle(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !41 {
entry:
  %5 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 6
  %11 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 7
  %centerX = alloca i32, align 4
  %12 = load i32, ptr %0, align 4
  store i32 %12, ptr %centerX, align 4
  %centerY = alloca i32, align 4
  %13 = load i32, ptr %1, align 4
  store i32 %13, ptr %centerY, align 4
  %radius = alloca float, align 4
  %14 = load float, ptr %2, align 4
  store float %14, ptr %radius, align 4
  %color = alloca i32, align 4
  %15 = load i32, ptr %3, align 4
  store i32 %15, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %centerX1 = load i32, ptr %centerX, align 4
  %16 = load i32, ptr %centerX, align 4
  %centerY2 = load i32, ptr %centerY, align 4
  %17 = load i32, ptr %centerY, align 4
  %radius3 = load float, ptr %radius, align 4
  %18 = load float, ptr %radius, align 4
  %color4 = load i32, ptr %color, align 4
  %19 = load i32, ptr %color, align 4
  call void @DrawCircle(i32 %16, i32 %17, float %18, i32 %19)
  %20 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawText(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !42 {
entry:
  %6 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %FlowWingAnim, ptr %5, i32 0, i32 7
  %text = alloca ptr, align 8
  %13 = load ptr, ptr %0, align 8
  store ptr %13, ptr %text, align 8
  %posX = alloca i32, align 4
  %14 = load i32, ptr %1, align 4
  store i32 %14, ptr %posX, align 4
  %posY = alloca i32, align 4
  %15 = load i32, ptr %2, align 4
  store i32 %15, ptr %posY, align 4
  %fontSize = alloca i32, align 4
  %16 = load i32, ptr %3, align 4
  store i32 %16, ptr %fontSize, align 4
  %color = alloca i32, align 4
  %17 = load i32, ptr %4, align 4
  store i32 %17, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %text1 = load ptr, ptr %text, align 8
  %18 = load ptr, ptr %text, align 8
  %posX2 = load i32, ptr %posX, align 4
  %19 = load i32, ptr %posX, align 4
  %posY3 = load i32, ptr %posY, align 4
  %20 = load i32, ptr %posY, align 4
  %fontSize4 = load i32, ptr %fontSize, align 4
  %21 = load i32, ptr %fontSize, align 4
  %color5 = load i32, ptr %color, align 4
  %22 = load i32, ptr %color, align 4
  call void @DrawText(ptr %18, i32 %19, i32 %20, i32 %21, i32 %22)
  %23 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawTexture(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !43 {
entry:
  %5 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 6
  %11 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 7
  %posX = alloca i32, align 4
  %12 = load i32, ptr %1, align 4
  store i32 %12, ptr %posX, align 4
  %posY = alloca i32, align 4
  %13 = load i32, ptr %2, align 4
  store i32 %13, ptr %posY, align 4
  %color = alloca i32, align 4
  %14 = load i32, ptr %3, align 4
  store i32 %14, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %posX1 = load i32, ptr %posX, align 4
  %15 = load i32, ptr %posX, align 4
  %posY2 = load i32, ptr %posY, align 4
  %16 = load i32, ptr %posY, align 4
  %color3 = load i32, ptr %color, align 4
  %17 = load i32, ptr %color, align 4
  call void @DrawTexture(ptr %0, i32 %15, i32 %16, i32 %17)
  %18 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawTexturePro(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5, ptr %6) !rt !44 {
entry:
  %7 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 1
  %8 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 2
  %9 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 3
  %10 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 4
  %11 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 5
  %12 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 6
  %13 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 7
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %14 = load [4 x float], ptr %1, align 4
  %15 = load [4 x float], ptr %2, align 4
  %16 = load [2 x float], ptr %3, align 4
  %rotation = load float, ptr %4, align 4
  %17 = load float, ptr %4, align 4
  %color = load i32, ptr %5, align 4
  %18 = load i32, ptr %5, align 4
  call void @DrawTexturePro(ptr %0, [4 x float] %14, [4 x float] %15, [2 x float] %16, float %17, i32 %18)
  %19 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.traceLog(ptr %0, ptr %1, ptr %2) !rt !45 {
entry:
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %logLevel = alloca i32, align 4
  %10 = load i32, ptr %0, align 4
  store i32 %10, ptr %logLevel, align 4
  %text = alloca ptr, align 8
  %11 = load ptr, ptr %1, align 8
  store ptr %11, ptr %text, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %logLevel1 = load i32, ptr %logLevel, align 4
  %12 = load i32, ptr %logLevel, align 4
  %text2 = load ptr, ptr %text, align 8
  %13 = load ptr, ptr %text, align 8
  call void @TraceLog(i32 %12, ptr %13)
  %14 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.loadTexture(ptr %0, ptr %1, ptr %2) !rt !46 {
entry:
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %fileName = alloca ptr, align 8
  %10 = load ptr, ptr %1, align 8
  store ptr %10, ptr %fileName, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %fileName1 = load ptr, ptr %fileName, align 8
  %11 = load ptr, ptr %fileName, align 8
  call void @LoadTexture(ptr %0, ptr %11)
  ret void

mergeBlock:                                       ; No predecessors!
  %12 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.unloadTexture(ptr %0, ptr %1) !rt !47 {
entry:
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  %9 = call ptr @malloc(i64 20)
  %10 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %10, ptr %9, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @UnloadTexture(ptr %9)
  %11 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.isKeyPressed(ptr %0, ptr %1, ptr %2) !rt !48 {
entry:
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %key = alloca i32, align 4
  %10 = load i32, ptr %1, align 4
  store i32 %10, ptr %key, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %key1 = load i32, ptr %key, align 4
  %11 = load i32, ptr %key, align 4
  %12 = call i1 @IsKeyPressed(i32 %11)
  store i1 %12, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.isKeyDown(ptr %0, ptr %1, ptr %2) !rt !49 {
entry:
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %key = alloca i32, align 4
  %10 = load i32, ptr %1, align 4
  store i32 %10, ptr %key, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %key1 = load i32, ptr %key, align 4
  %11 = load i32, ptr %key, align 4
  %12 = call i1 @IsKeyDown(i32 %11)
  store i1 %12, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.textFormat(ptr %0, ptr %1, ptr %2) !rt !50 {
entry:
  %3 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %FlowWingAnim, ptr %2, i32 0, i32 7
  %text = alloca ptr, align 8
  %10 = load ptr, ptr %1, align 8
  store ptr %10, ptr %text, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %text1 = load ptr, ptr %text, align 8
  %11 = load ptr, ptr %text, align 8
  %12 = call ptr @TextFormat(ptr %11)
  store ptr %12, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @drawTexturePro(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !51 {
entry:
  %6 = call ptr @malloc(i64 20)
  %7 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %7, ptr %6, align 4
  %source = alloca [4 x float], align 4, !ET !52, !I !53
  %8 = load [4 x float], ptr %1, align 4
  store [4 x float] %8, ptr %source, align 4
  %dest = alloca [4 x float], align 4, !ET !52, !I !53
  %9 = load [4 x float], ptr %2, align 4
  store [4 x float] %9, ptr %dest, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %10 = load [4 x float], ptr %source, align 4
  %11 = load [4 x float], ptr %dest, align 4
  %12 = load [2 x float], ptr %3, align 4
  %rotation = load float, ptr %4, align 4
  %13 = load float, ptr %4, align 4
  %color = load i32, ptr %5, align 4
  %14 = load i32, ptr %5, align 4
  call void @DrawTexturePro(ptr %6, [4 x float] %10, [4 x float] %11, [2 x float] %12, float %13, i32 %14)
  %15 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

!0 = !{!"getRandomNumber:rt:pr:28"}
!1 = !{!"srand:rt:pr:27"}
!2 = !{!"rand:rt:pr:28"}
!3 = !{!"GetFrameTime:rt:pr:32"}
!4 = !{!"DrawTexturePro:rt:pr:27"}
!5 = !{!"UnloadTexture:rt:pr:27"}
!6 = !{!"DrawTexture:rt:pr:27"}
!7 = !{!"GetTime:rt:pr:31"}
!8 = !{!"TextFormat:rt:pr:33"}
!9 = !{!"LoadTexture:rt:ob:Texture"}
!10 = !{!"IsKeyDown:rt:pr:34"}
!11 = !{!"SetTargetFPS:rt:pr:27"}
!12 = !{!"DrawText:rt:pr:27"}
!13 = !{!"GetScreenHeight:rt:pr:28"}
!14 = !{!"CloseWindow:rt:pr:27"}
!15 = !{!"InitWindow:rt:pr:27"}
!16 = !{!"EndDrawing:rt:pr:27"}
!17 = !{!"IsKeyPressed:rt:pr:34"}
!18 = !{!"time:rt:pr:28"}
!19 = !{!"BeginDrawing:rt:pr:27"}
!20 = !{!"TraceLog:rt:pr:27"}
!21 = !{!"WindowShouldClose:rt:pr:34"}
!22 = !{!"DrawRectangle:rt:pr:27"}
!23 = !{!"DrawCircle:rt:pr:27"}
!24 = !{!"GetScreenWidth:rt:pr:28"}
!25 = !{!"ClearBackground:rt:pr:27"}
!26 = !{!"FlowWingAnim.init4:rt:pr:27"}
!27 = !{!"FlowWingAnim.beforeInit:rt:pr:27"}
!28 = !{!"FlowWingAnim.setTargetFPS:rt:pr:27"}
!29 = !{!"FlowWingAnim.getColor:rt:pr:28"}
!30 = !{!"FlowWingAnim.createWindow:rt:pr:27"}
!31 = !{!"FlowWingAnim.clearBackground:rt:pr:27"}
!32 = !{!"FlowWingAnim.windowShouldClose:rt:pr:34"}
!33 = !{!"FlowWingAnim.beginDrawing:rt:pr:27"}
!34 = !{!"FlowWingAnim.drawRectangle:rt:pr:27"}
!35 = !{!"FlowWingAnim.endDrawing:rt:pr:27"}
!36 = !{!"FlowWingAnim.closeWindow:rt:pr:27"}
!37 = !{!"FlowWingAnim.getTime:rt:pr:31"}
!38 = !{!"FlowWingAnim.getFrameTime:rt:pr:32"}
!39 = !{!"FlowWingAnim.getScreenHeight:rt:pr:28"}
!40 = !{!"FlowWingAnim.getScreenWidth:rt:pr:28"}
!41 = !{!"FlowWingAnim.drawCircle:rt:pr:27"}
!42 = !{!"FlowWingAnim.drawText:rt:pr:27"}
!43 = !{!"FlowWingAnim.drawTexture:rt:pr:27"}
!44 = !{!"FlowWingAnim.drawTexturePro:rt:pr:27"}
!45 = !{!"FlowWingAnim.traceLog:rt:pr:27"}
!46 = !{!"FlowWingAnim.loadTexture:rt:ob:Texture"}
!47 = !{!"FlowWingAnim.unloadTexture:rt:pr:27"}
!48 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!49 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!50 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!51 = !{!"drawTexturePro:rt:pr:27"}
!52 = !{!"32"}
!53 = !{!"4:"}
