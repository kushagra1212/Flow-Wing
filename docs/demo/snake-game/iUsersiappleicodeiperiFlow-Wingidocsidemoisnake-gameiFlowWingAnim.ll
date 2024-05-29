; ModuleID = 'iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim'
source_filename = "iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.1, %KEYS_TYPE.0 }
%COLORS_TYPE.1 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.0 = type { i32, i32, i32, i32 }

@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_NULL = external global i8
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
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

declare i32 @string_length(ptr)

declare double @string_to_double(ptr)

declare i32 @string_to_int(ptr)

declare i64 @string_to_long(ptr)

declare void @raise_exception(ptr)

declare ptr @malloc()

define i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim() {
entry:
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib()

declare !rt !0 void @srand(i32)

declare !rt !1 i32 @rand()

declare !rt !2 i32 @getRandomNumber(ptr, ptr)

declare !rt !3 i1 @IsKeyDown(i32)

declare !rt !4 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !5 i32 @GetScreenHeight()

declare !rt !6 void @CloseWindow()

declare !rt !7 void @EndDrawing()

declare !rt !8 i1 @IsKeyPressed(i32)

declare !rt !9 void @BeginDrawing()

declare !rt !10 i32 @time()

declare !rt !11 ptr @TextFormat(ptr)

declare !rt !12 i1 @WindowShouldClose()

declare !rt !13 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !14 void @DrawCircle(i32, i32, float, i32)

declare !rt !15 i32 @GetScreenWidth()

declare !rt !16 void @ClearBackground(i32)

declare !rt !17 void @InitWindow(i32, i32, ptr)

declare !rt !18 void @SetTargetFPS(i32)

define void @FlowWingAnim.init4(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !19 {
entry:
  %5 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 6
  %screenHeight = alloca i32, align 4
  %11 = load i32, ptr %0, align 4
  store i32 %11, ptr %screenHeight, align 4
  %screenWidth = alloca i32, align 4
  %12 = load i32, ptr %1, align 4
  store i32 %12, ptr %screenWidth, align 4
  %screenName = alloca ptr, align 8
  %13 = load ptr, ptr %2, align 8
  store ptr %13, ptr %screenName, align 8
  %fps = alloca i32, align 4
  %14 = load i32, ptr %3, align 4
  store i32 %14, ptr %fps, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 4
  %fps9 = load i32, ptr %15, align 4
  %fps10 = load i32, ptr %fps, align 4
  %16 = load i32, ptr %fps, align 4
  store i32 %16, ptr %15, align 4
  %17 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %19 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  call void @FlowWingAnim.beforeInit(ptr %4)
  %21 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 2
  %screenHeight11 = load i32, ptr %25, align 4
  %screenHeight12 = load i32, ptr %screenHeight, align 4
  %26 = load i32, ptr %screenHeight, align 4
  store i32 %26, ptr %25, align 4
  %27 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %29 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %31 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 1
  %screenWidth13 = load i32, ptr %31, align 4
  %screenWidth14 = load i32, ptr %screenWidth, align 4
  %32 = load i32, ptr %screenWidth, align 4
  store i32 %32, ptr %31, align 4
  %33 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %35 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %37 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 3
  %screenName15 = load ptr, ptr %37, align 8
  %screenName16 = load ptr, ptr %screenName, align 8
  %38 = load ptr, ptr %screenName, align 8
  store ptr %38, ptr %37, align 8
  %39 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock
}

define void @FlowWingAnim.beforeInit(ptr %0) !rt !20 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = getelementptr inbounds %COLORS_TYPE.1, ptr %5, i32 0, i32 0
  %8 = alloca i32, align 4
  store i32 255, ptr %8, align 4
  %9 = alloca i32, align 4
  store i32 255, ptr %9, align 4
  %10 = alloca i32, align 4
  store i32 255, ptr %10, align 4
  %11 = alloca i32, align 4
  store i32 255, ptr %11, align 4
  %12 = call i32 @FlowWingAnim.getColor(ptr %8, ptr %9, ptr %10, ptr %11, ptr %0)
  store i32 %12, ptr %7, align 4
  %13 = getelementptr inbounds %COLORS_TYPE.1, ptr %5, i32 0, i32 1
  %14 = alloca i32, align 4
  store i32 255, ptr %14, align 4
  %15 = alloca i32, align 4
  store i32 0, ptr %15, align 4
  %16 = alloca i32, align 4
  store i32 0, ptr %16, align 4
  %17 = alloca i32, align 4
  store i32 255, ptr %17, align 4
  %18 = call i32 @FlowWingAnim.getColor(ptr %14, ptr %15, ptr %16, ptr %17, ptr %0)
  store i32 %18, ptr %13, align 4
  %19 = getelementptr inbounds %COLORS_TYPE.1, ptr %5, i32 0, i32 2
  %20 = alloca i32, align 4
  store i32 0, ptr %20, align 4
  %21 = alloca i32, align 4
  store i32 255, ptr %21, align 4
  %22 = alloca i32, align 4
  store i32 0, ptr %22, align 4
  %23 = alloca i32, align 4
  store i32 255, ptr %23, align 4
  %24 = call i32 @FlowWingAnim.getColor(ptr %20, ptr %21, ptr %22, ptr %23, ptr %0)
  store i32 %24, ptr %19, align 4
  %25 = getelementptr inbounds %COLORS_TYPE.1, ptr %5, i32 0, i32 3
  %26 = alloca i32, align 4
  store i32 0, ptr %26, align 4
  %27 = alloca i32, align 4
  store i32 0, ptr %27, align 4
  %28 = alloca i32, align 4
  store i32 255, ptr %28, align 4
  %29 = alloca i32, align 4
  store i32 255, ptr %29, align 4
  %30 = call i32 @FlowWingAnim.getColor(ptr %26, ptr %27, ptr %28, ptr %29, ptr %0)
  store i32 %30, ptr %25, align 4
  %31 = getelementptr inbounds %COLORS_TYPE.1, ptr %5, i32 0, i32 4
  %32 = alloca i32, align 4
  store i32 0, ptr %32, align 4
  %33 = alloca i32, align 4
  store i32 82, ptr %33, align 4
  %34 = alloca i32, align 4
  store i32 172, ptr %34, align 4
  %35 = alloca i32, align 4
  store i32 255, ptr %35, align 4
  %36 = call i32 @FlowWingAnim.getColor(ptr %32, ptr %33, ptr %34, ptr %35, ptr %0)
  store i32 %36, ptr %31, align 4
  %37 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %39 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %41 = getelementptr inbounds %KEYS_TYPE.0, ptr %6, i32 0, i32 0
  store i32 262, ptr %41, align 4
  %42 = getelementptr inbounds %KEYS_TYPE.0, ptr %6, i32 0, i32 1
  store i32 263, ptr %42, align 4
  %43 = getelementptr inbounds %KEYS_TYPE.0, ptr %6, i32 0, i32 2
  store i32 264, ptr %43, align 4
  %44 = getelementptr inbounds %KEYS_TYPE.0, ptr %6, i32 0, i32 3
  store i32 265, ptr %44, align 4
  %45 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %47 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_CONTINUE_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  call void @FlowWingAnim.setTargetFPS(ptr %0)
  %49 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @FlowWingAnim.setTargetFPS(ptr %0) !rt !21 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %fps = load i32, ptr %4, align 4
  %7 = load i32, ptr %4, align 4
  call void @SetTargetFPS(i32 %7)
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define i32 @FlowWingAnim.getColor(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !22 {
entry:
  %5 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 6
  %r = alloca i32, align 4
  %11 = load i32, ptr %0, align 4
  store i32 %11, ptr %r, align 4
  %g = alloca i32, align 4
  %12 = load i32, ptr %1, align 4
  store i32 %12, ptr %g, align 4
  %b = alloca i32, align 4
  %13 = load i32, ptr %2, align 4
  store i32 %13, ptr %b, align 4
  %a = alloca i32, align 4
  %14 = load i32, ptr %3, align 4
  store i32 %14, ptr %a, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %a1 = load i32, ptr %a, align 4
  %15 = mul i32 %a1, 256
  %16 = mul i32 %15, 256
  %17 = mul i32 %16, 256
  %b2 = load i32, ptr %b, align 4
  %18 = mul i32 %b2, 256
  %19 = mul i32 %18, 256
  %20 = add i32 %17, %19
  %g3 = load i32, ptr %g, align 4
  %21 = mul i32 %g3, 256
  %22 = add i32 %20, %21
  %r4 = load i32, ptr %r, align 4
  %23 = add i32 %22, %r4
  ret i32 %23

mergeBlock:                                       ; No predecessors!
  %24 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.createWindow(ptr %0) !rt !23 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  %screenHeight = load i32, ptr %7, align 4
  %8 = load i32, ptr %7, align 4
  %9 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  %screenWidth = load i32, ptr %9, align 4
  %10 = load i32, ptr %9, align 4
  %11 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  %screenName = load ptr, ptr %11, align 8
  %12 = load ptr, ptr %11, align 8
  call void @InitWindow(i32 %8, i32 %10, ptr %12)
  %13 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.clearBackground(ptr %0, ptr %1) !rt !24 {
entry:
  %2 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 6
  %color = alloca i32, align 4
  %8 = load i32, ptr %0, align 4
  store i32 %8, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %color1 = load i32, ptr %color, align 4
  %9 = load i32, ptr %color, align 4
  call void @ClearBackground(i32 %9)
  %10 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define i1 @FlowWingAnim.windowShouldClose(ptr %0) !rt !25 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i1 false

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %7 = call i1 @WindowShouldClose()
  ret i1 %7

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.beginDrawing(ptr %0) !rt !26 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @BeginDrawing()
  %7 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawRectangle(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !27 {
entry:
  %6 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 6
  %posX = alloca i32, align 4
  %12 = load i32, ptr %0, align 4
  store i32 %12, ptr %posX, align 4
  %posY = alloca i32, align 4
  %13 = load i32, ptr %1, align 4
  store i32 %13, ptr %posY, align 4
  %width = alloca i32, align 4
  %14 = load i32, ptr %2, align 4
  store i32 %14, ptr %width, align 4
  %height = alloca i32, align 4
  %15 = load i32, ptr %3, align 4
  store i32 %15, ptr %height, align 4
  %color = alloca i32, align 4
  %16 = load i32, ptr %4, align 4
  store i32 %16, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %posX1 = load i32, ptr %posX, align 4
  %17 = load i32, ptr %posX, align 4
  %posY2 = load i32, ptr %posY, align 4
  %18 = load i32, ptr %posY, align 4
  %width3 = load i32, ptr %width, align 4
  %19 = load i32, ptr %width, align 4
  %height4 = load i32, ptr %height, align 4
  %20 = load i32, ptr %height, align 4
  %color5 = load i32, ptr %color, align 4
  %21 = load i32, ptr %color, align 4
  call void @DrawRectangle(i32 %17, i32 %18, i32 %19, i32 %20, i32 %21)
  %22 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.endDrawing(ptr %0) !rt !28 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @EndDrawing()
  %7 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.closeWindow(ptr %0) !rt !29 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @CloseWindow()
  %7 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define i32 @FlowWingAnim.getScreenHeight(ptr %0) !rt !30 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %7 = call i32 @GetScreenHeight()
  ret i32 %7

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define i32 @FlowWingAnim.getScreenWidth(ptr %0) !rt !31 {
entry:
  %1 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 1
  %2 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 2
  %3 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 3
  %4 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 4
  %5 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 5
  %6 = getelementptr %FlowWingAnim, ptr %0, i32 0, i32 6
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %7 = call i32 @GetScreenWidth()
  ret i32 %7

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @FlowWingAnim.drawCircle(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !32 {
entry:
  %5 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 1
  %6 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 2
  %7 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 3
  %8 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 4
  %9 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 5
  %10 = getelementptr %FlowWingAnim, ptr %4, i32 0, i32 6
  %centerX = alloca i32, align 4
  %11 = load i32, ptr %0, align 4
  store i32 %11, ptr %centerX, align 4
  %centerY = alloca i32, align 4
  %12 = load i32, ptr %1, align 4
  store i32 %12, ptr %centerY, align 4
  %radius = alloca float, align 4
  %13 = load float, ptr %2, align 4
  store float %13, ptr %radius, align 4
  %color = alloca i32, align 4
  %14 = load i32, ptr %3, align 4
  store i32 %14, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %centerX1 = load i32, ptr %centerX, align 4
  %15 = load i32, ptr %centerX, align 4
  %centerY2 = load i32, ptr %centerY, align 4
  %16 = load i32, ptr %centerY, align 4
  %radius3 = load float, ptr %radius, align 4
  %17 = load float, ptr %radius, align 4
  %color4 = load i32, ptr %color, align 4
  %18 = load i32, ptr %color, align 4
  call void @DrawCircle(i32 %15, i32 %16, float %17, i32 %18)
  %19 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @FlowWingAnim.drawText(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4, ptr %5) !rt !33 {
entry:
  %6 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 1
  %7 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 2
  %8 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 3
  %9 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 4
  %10 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 5
  %11 = getelementptr %FlowWingAnim, ptr %5, i32 0, i32 6
  %text = alloca ptr, align 8
  %12 = load ptr, ptr %0, align 8
  store ptr %12, ptr %text, align 8
  %posX = alloca i32, align 4
  %13 = load i32, ptr %1, align 4
  store i32 %13, ptr %posX, align 4
  %posY = alloca i32, align 4
  %14 = load i32, ptr %2, align 4
  store i32 %14, ptr %posY, align 4
  %fontSize = alloca i32, align 4
  %15 = load i32, ptr %3, align 4
  store i32 %15, ptr %fontSize, align 4
  %color = alloca i32, align 4
  %16 = load i32, ptr %4, align 4
  store i32 %16, ptr %color, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %text1 = load ptr, ptr %text, align 8
  %17 = load ptr, ptr %text, align 8
  %posX2 = load i32, ptr %posX, align 4
  %18 = load i32, ptr %posX, align 4
  %posY3 = load i32, ptr %posY, align 4
  %19 = load i32, ptr %posY, align 4
  %fontSize4 = load i32, ptr %fontSize, align 4
  %20 = load i32, ptr %fontSize, align 4
  %color5 = load i32, ptr %color, align 4
  %21 = load i32, ptr %color, align 4
  call void @DrawText(ptr %17, i32 %18, i32 %19, i32 %20, i32 %21)
  %22 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define i1 @FlowWingAnim.isKeyPressed(ptr %0, ptr %1) !rt !34 {
entry:
  %2 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 6
  %key = alloca i32, align 4
  %8 = load i32, ptr %0, align 4
  store i32 %8, ptr %key, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i1 false

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %key1 = load i32, ptr %key, align 4
  %9 = load i32, ptr %key, align 4
  %10 = call i1 @IsKeyPressed(i32 %9)
  ret i1 %10

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define i1 @FlowWingAnim.isKeyDown(ptr %0, ptr %1) !rt !35 {
entry:
  %2 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 6
  %key = alloca i32, align 4
  %8 = load i32, ptr %0, align 4
  store i32 %8, ptr %key, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i1 false

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %key1 = load i32, ptr %key, align 4
  %9 = load i32, ptr %key, align 4
  %10 = call i1 @IsKeyDown(i32 %9)
  ret i1 %10

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @FlowWingAnim.textFormat(ptr %0, ptr %1) !rt !36 {
entry:
  %2 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 1
  %3 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 2
  %4 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 3
  %5 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 4
  %6 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 5
  %7 = getelementptr %FlowWingAnim, ptr %1, i32 0, i32 6
  %text = alloca ptr, align 8
  %8 = load ptr, ptr %0, align 8
  store ptr %8, ptr %text, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %text1 = load ptr, ptr %text, align 8
  %9 = load ptr, ptr %text, align 8
  %10 = call ptr @TextFormat(ptr %9)
  ret ptr %10

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"srand:rt:pr:27"}
!1 = !{!"rand:rt:pr:28"}
!2 = !{!"getRandomNumber:rt:pr:28"}
!3 = !{!"IsKeyDown:rt:pr:34"}
!4 = !{!"DrawText:rt:pr:27"}
!5 = !{!"GetScreenHeight:rt:pr:28"}
!6 = !{!"CloseWindow:rt:pr:27"}
!7 = !{!"EndDrawing:rt:pr:27"}
!8 = !{!"IsKeyPressed:rt:pr:34"}
!9 = !{!"BeginDrawing:rt:pr:27"}
!10 = !{!"time:rt:pr:28"}
!11 = !{!"TextFormat:rt:pr:33"}
!12 = !{!"WindowShouldClose:rt:pr:34"}
!13 = !{!"DrawRectangle:rt:pr:27"}
!14 = !{!"DrawCircle:rt:pr:27"}
!15 = !{!"GetScreenWidth:rt:pr:28"}
!16 = !{!"ClearBackground:rt:pr:27"}
!17 = !{!"InitWindow:rt:pr:27"}
!18 = !{!"SetTargetFPS:rt:pr:27"}
!19 = !{!"FlowWingAnim.init4:rt:pr:27"}
!20 = !{!"FlowWingAnim.beforeInit:rt:pr:27"}
!21 = !{!"FlowWingAnim.setTargetFPS:rt:pr:27"}
!22 = !{!"FlowWingAnim.getColor:rt:pr:28"}
!23 = !{!"FlowWingAnim.createWindow:rt:pr:27"}
!24 = !{!"FlowWingAnim.clearBackground:rt:pr:27"}
!25 = !{!"FlowWingAnim.windowShouldClose:rt:pr:34"}
!26 = !{!"FlowWingAnim.beginDrawing:rt:pr:27"}
!27 = !{!"FlowWingAnim.drawRectangle:rt:pr:27"}
!28 = !{!"FlowWingAnim.endDrawing:rt:pr:27"}
!29 = !{!"FlowWingAnim.closeWindow:rt:pr:27"}
!30 = !{!"FlowWingAnim.getScreenHeight:rt:pr:28"}
!31 = !{!"FlowWingAnim.getScreenWidth:rt:pr:28"}
!32 = !{!"FlowWingAnim.drawCircle:rt:pr:27"}
!33 = !{!"FlowWingAnim.drawText:rt:pr:27"}
!34 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!35 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!36 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
