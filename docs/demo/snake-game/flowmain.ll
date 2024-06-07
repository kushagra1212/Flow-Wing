; ModuleID = 'flowmain'
source_filename = "flowmain"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Bird::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%Bird = type { ptr, float, float, double, double, i32, i32, ptr, i1, %Texture.0, [9 x %Position.4] }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%Position.4 = type { float, float }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.3, %KEYS_TYPE.2, %LOG_TYPE.1 }
%COLORS_TYPE.3 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.2 = type { i32, i32, i32, i32 }
%LOG_TYPE.1 = type { i32, i32, i32, i32, i32, i32, i32, i32 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.FlowWingAnim.fg = common global %"FlowWingAnim::VTableType" zeroinitializer
@screenWidth = common global i32 0
@screenHeight = common global i32 0
@FPS = common global i32 0
@side = common global i32 0
@vtable.Bird.fg = common global %"Bird::VTableType" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [875 x i8] c"\0A\1B[33m78| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m79| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m82| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 82:32\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [953 x i8] c"\0A\1B[33m78| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m79| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m82| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 82:71\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [802 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                     \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m88| \1B[0m\1B[0m\0A\1B[0m\1B[33m89| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    return [0.0d, 0.0d]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 86:37\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [843 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m88| \1B[0m\1B[0m\0A\1B[0m\1B[33m89| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    return [0.0d, 0.0d]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 86:50\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [890 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                                                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m88| \1B[0m\1B[0m\0A\1B[0m\1B[33m89| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    return [0.0d, 0.0d]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 86:81\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@6 = private unnamed_addr constant [931 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                                                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m88| \1B[0m\1B[0m\0A\1B[0m\1B[33m89| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    return [0.0d, 0.0d]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 86:94\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@9 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@11 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@12 = private unnamed_addr constant [708 x i8] c"\0A\1B[33m10| \1B[0m\1B[0m}\0A\1B[0m\1B[33m11| \1B[0m\1B[0mclass Bird {\0A\1B[0m\1B[33m12| \1B[0m\1B[0m  const ACTUAL_BIRD_SIZE: deci32 = 360.0d\0A\1B[0m\1B[33m13| \1B[0m\1B[0m  var birdSize: deci32 = 90.0d\0A\1B[0m\1B[33m14| \1B[0m\1B[31m\1B[1m  const BIRD_TIMMER: deci = 1.0 / FPS\0A\1B[0m\1B[32m\1B[1m                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m15| \1B[0m\1B[0m  var birdTimmer: deci   \0A\1B[0m\1B[33m16| \1B[0m\1B[0m  const BIRD_SPRITE_SIZE:int = 9\0A\1B[0m\1B[33m17| \1B[0m\1B[0m  var birdSpriteIndex:int = 0\0A\1B[0m\1B[33m18| \1B[0m\1B[0m  var birdTexturePath:str\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 14:33\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [11 x i8] c"./bird.png\00", align 1
@14 = private unnamed_addr constant [11 x i8] c"./bird.png\00", align 1
@15 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1

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

declare ptr @malloc()

define i32 @flowmain() {
entry:
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()
  store i32 0, ptr @screenWidth, align 4
  store i32 1024, ptr @screenWidth, align 4
  store i32 0, ptr @screenHeight, align 4
  store i32 768, ptr @screenHeight, align 4
  store i32 0, ptr @FPS, align 4
  store i32 12, ptr @FPS, align 4
  store i32 0, ptr @side, align 4
  store i32 10, ptr @side, align 4
  %1 = call i32 @main()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()

declare !rt !0 void @FlowWingAnim.init4(ptr, ptr, ptr, ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit(ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS(ptr)

declare !rt !3 i32 @FlowWingAnim.getColor(ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow(ptr)

declare !rt !5 void @FlowWingAnim.clearBackground(ptr, ptr)

declare !rt !6 i1 @FlowWingAnim.windowShouldClose(ptr)

declare !rt !7 void @FlowWingAnim.beginDrawing(ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !9 void @FlowWingAnim.endDrawing(ptr)

declare !rt !10 void @FlowWingAnim.closeWindow(ptr)

declare !rt !11 double @FlowWingAnim.getTime(ptr)

declare !rt !12 float @FlowWingAnim.getFrameTime(ptr)

declare !rt !13 i32 @FlowWingAnim.getScreenHeight(ptr)

declare !rt !14 i32 @FlowWingAnim.getScreenWidth(ptr)

declare !rt !15 void @FlowWingAnim.drawCircle(ptr, ptr, ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !17 void @FlowWingAnim.drawTexture(ptr, ptr, ptr, ptr, ptr)

declare !rt !18 void @FlowWingAnim.drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !19 void @FlowWingAnim.traceLog(ptr, ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture(ptr, ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture(ptr, ptr)

declare !rt !22 i1 @FlowWingAnim.isKeyPressed(ptr, ptr)

declare !rt !23 i1 @FlowWingAnim.isKeyDown(ptr, ptr)

declare !rt !24 ptr @FlowWingAnim.textFormat(ptr, ptr)

declare !rt !24 ptr @FlowWingAnim.textFormat.1(ptr, ptr)

declare !rt !22 i1 @FlowWingAnim.isKeyPressed.2(ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture.3(ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture.4(ptr, ptr, ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle.5(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow.6(ptr)

declare !rt !19 void @FlowWingAnim.traceLog.7(ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText.8(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !25 void @SetTargetFPS(i32)

declare !rt !7 void @FlowWingAnim.beginDrawing.9(ptr)

declare !rt !15 void @FlowWingAnim.drawCircle.10(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 i32 @FlowWingAnim.getScreenWidth.11(ptr)

declare !rt !26 i32 @getRandomNumber(ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit.12(ptr)

declare !rt !13 i32 @FlowWingAnim.getScreenHeight.13(ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.14(ptr)

declare !rt !9 void @FlowWingAnim.endDrawing.15(ptr)

declare !rt !3 i32 @FlowWingAnim.getColor.16(ptr, ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.17(ptr)

declare !rt !0 void @FlowWingAnim.init4.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !27 void @ClearBackground(i32)

declare !rt !28 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !12 float @FlowWingAnim.getFrameTime.19(ptr)

declare !rt !29 void @TraceLog(i32, ptr)

declare !rt !30 i32 @GetScreenWidth()

declare !rt !31 void @DrawCircle(i32, i32, float, i32)

declare !rt !32 i32 @time()

declare !rt !33 void @BeginDrawing()

declare !rt !34 i1 @IsKeyPressed(i32)

declare !rt !35 i1 @WindowShouldClose()

declare !rt !36 void @InitWindow(i32, i32, ptr)

declare !rt !37 void @EndDrawing()

declare !rt !38 void @CloseWindow()

declare !rt !17 void @FlowWingAnim.drawTexture.20(ptr, ptr, ptr, ptr, ptr)

declare !rt !39 i32 @GetScreenHeight()

declare !rt !18 void @FlowWingAnim.drawTexturePro.21(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !40 float @GetFrameTime()

declare !rt !41 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !42 double @GetTime()

declare !rt !43 void @UnloadTexture(ptr)

declare !rt !44 ptr @TextFormat(ptr)

declare !rt !23 i1 @FlowWingAnim.isKeyDown.22(ptr, ptr)

declare !rt !45 void @LoadTexture(ptr sret, ptr)

declare !rt !46 i1 @IsKeyDown(i32)

declare !rt !6 i1 @FlowWingAnim.windowShouldClose.23(ptr)

declare !rt !47 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !48 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !49 void @srand(i32)

declare !rt !11 double @FlowWingAnim.getTime.24(ptr)

declare !rt !5 void @FlowWingAnim.clearBackground.25(ptr, ptr)

declare !rt !50 i32 @rand()

define void @Bird.init1(ptr %0, ptr %1) !rt !51 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  %birdTexturePath = alloca ptr, align 8
  %12 = load ptr, ptr %0, align 8
  store ptr %12, ptr %birdTexturePath, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %13 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %birdTexturePath7 = load ptr, ptr %13, align 8
  %birdTexturePath8 = load ptr, ptr %birdTexturePath, align 8
  %14 = load ptr, ptr %birdTexturePath, align 8
  store ptr %14, ptr %13, align 8
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %19 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %birdTimmer = load double, ptr %19, align 8
  %BIRD_TIMMER = load double, ptr %4, align 8
  %20 = load double, ptr %4, align 8
  store double %20, ptr %19, align 8
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %isBirdAlive = load i1, ptr %25, align 1
  store i1 true, ptr %25, align 1
  %26 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %30 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  %31 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 0
  %32 = getelementptr inbounds %Position.4, ptr %31, i32 0, i32 0
  store float 0.000000e+00, ptr %32, align 4
  %33 = getelementptr inbounds %Position.4, ptr %31, i32 0, i32 1
  store float 0.000000e+00, ptr %33, align 4
  %34 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 1
  %35 = getelementptr inbounds %Position.4, ptr %34, i32 0, i32 0
  %ACTUAL_BIRD_SIZE = load float, ptr %2, align 4
  %36 = fmul float %ACTUAL_BIRD_SIZE, 1.000000e+00
  store float %36, ptr %35, align 4
  %37 = getelementptr inbounds %Position.4, ptr %34, i32 0, i32 1
  store float 0.000000e+00, ptr %37, align 4
  %38 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 2
  %39 = getelementptr inbounds %Position.4, ptr %38, i32 0, i32 0
  %ACTUAL_BIRD_SIZE9 = load float, ptr %2, align 4
  %40 = fmul float %ACTUAL_BIRD_SIZE9, 2.000000e+00
  store float %40, ptr %39, align 4
  %41 = getelementptr inbounds %Position.4, ptr %38, i32 0, i32 1
  store float 0.000000e+00, ptr %41, align 4
  %42 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 3
  %43 = getelementptr inbounds %Position.4, ptr %42, i32 0, i32 0
  store float 0.000000e+00, ptr %43, align 4
  %44 = getelementptr inbounds %Position.4, ptr %42, i32 0, i32 1
  %ACTUAL_BIRD_SIZE10 = load float, ptr %2, align 4
  %45 = fmul float %ACTUAL_BIRD_SIZE10, 1.000000e+00
  store float %45, ptr %44, align 4
  %46 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 4
  %47 = getelementptr inbounds %Position.4, ptr %46, i32 0, i32 0
  %ACTUAL_BIRD_SIZE11 = load float, ptr %2, align 4
  %48 = fmul float %ACTUAL_BIRD_SIZE11, 1.000000e+00
  store float %48, ptr %47, align 4
  %49 = getelementptr inbounds %Position.4, ptr %46, i32 0, i32 1
  %ACTUAL_BIRD_SIZE12 = load float, ptr %2, align 4
  %50 = fmul float %ACTUAL_BIRD_SIZE12, 1.000000e+00
  store float %50, ptr %49, align 4
  %51 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 5
  %52 = getelementptr inbounds %Position.4, ptr %51, i32 0, i32 0
  %ACTUAL_BIRD_SIZE13 = load float, ptr %2, align 4
  %53 = fmul float %ACTUAL_BIRD_SIZE13, 2.000000e+00
  store float %53, ptr %52, align 4
  %54 = getelementptr inbounds %Position.4, ptr %51, i32 0, i32 1
  %ACTUAL_BIRD_SIZE14 = load float, ptr %2, align 4
  %55 = fmul float %ACTUAL_BIRD_SIZE14, 1.000000e+00
  store float %55, ptr %54, align 4
  %56 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 6
  %57 = getelementptr inbounds %Position.4, ptr %56, i32 0, i32 0
  store float 0.000000e+00, ptr %57, align 4
  %58 = getelementptr inbounds %Position.4, ptr %56, i32 0, i32 1
  %ACTUAL_BIRD_SIZE15 = load float, ptr %2, align 4
  %59 = fmul float %ACTUAL_BIRD_SIZE15, 2.000000e+00
  store float %59, ptr %58, align 4
  %60 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 7
  %61 = getelementptr inbounds %Position.4, ptr %60, i32 0, i32 0
  %ACTUAL_BIRD_SIZE16 = load float, ptr %2, align 4
  %62 = fmul float %ACTUAL_BIRD_SIZE16, 1.000000e+00
  store float %62, ptr %61, align 4
  %63 = getelementptr inbounds %Position.4, ptr %60, i32 0, i32 1
  %ACTUAL_BIRD_SIZE17 = load float, ptr %2, align 4
  %64 = fmul float %ACTUAL_BIRD_SIZE17, 2.000000e+00
  store float %64, ptr %63, align 4
  %65 = getelementptr [9 x %Position.4], ptr %30, i32 0, i32 8
  %66 = getelementptr inbounds %Position.4, ptr %65, i32 0, i32 0
  %ACTUAL_BIRD_SIZE18 = load float, ptr %2, align 4
  %67 = fmul float %ACTUAL_BIRD_SIZE18, 2.000000e+00
  store float %67, ptr %66, align 4
  %68 = getelementptr inbounds %Position.4, ptr %65, i32 0, i32 1
  %ACTUAL_BIRD_SIZE19 = load float, ptr %2, align 4
  %69 = fmul float %ACTUAL_BIRD_SIZE19, 2.000000e+00
  store float %69, ptr %68, align 4
  %70 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @Bird.setTexture(ptr %0, ptr %1) !rt !52 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  %birdTexture = alloca %Texture.0, align 8
  %12 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %12, ptr %birdTexture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %13 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %14 = load %Texture.0, ptr %birdTexture, align 4
  store %Texture.0 %14, ptr %13, align 4
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define ptr @Bird.getTexturePath(ptr %0) !rt !53 {
entry:
  %1 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 7
  %8 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 8
  %9 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  %10 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %11 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 7
  %birdTexturePath = load ptr, ptr %11, align 8
  ret ptr %birdTexturePath

mergeBlock:                                       ; No predecessors!
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.update(ptr %0, ptr %1) !rt !54 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  %frameTime = alloca float, align 4
  %12 = load float, ptr %0, align 4
  store float %12, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %birdTimmer = load double, ptr %5, align 8
  %birdTimmer3 = load double, ptr %5, align 8
  %frameTime4 = load float, ptr %frameTime, align 4
  %13 = fpext float %frameTime4 to double
  %14 = fsub double %birdTimmer3, %13
  store double %14, ptr %5, align 8
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %birdTimmer5 = load double, ptr %5, align 8
  %19 = fcmp olt double %birdTimmer5, 0.000000e+00
  br i1 %19, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock12, %afterIfElse18, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %birdTimmer13 = load double, ptr %5, align 8
  %BIRD_TIMMER = load double, ptr %4, align 8
  %22 = load double, ptr %4, align 8
  store double %22, ptr %5, align 8
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock9, label %afterNestedBlock6

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %birdSpriteIndex = load i32, ptr %7, align 4
  %birdSpriteIndex14 = load i32, ptr %7, align 4
  %27 = add i32 %birdSpriteIndex14, 1
  store i32 %27, ptr %7, align 4
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock10, label %afterNestedBlock6

checkContinueBlock10:                             ; preds = %nestedBlock9
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock11, label %afterNestedBlock6

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %birdSpriteIndex15 = load i32, ptr %7, align 4
  %BIRD_SPRITE_SIZE = load i32, ptr %6, align 4
  %32 = icmp sge i32 %birdSpriteIndex15, %BIRD_SPRITE_SIZE
  br i1 %32, label %then16, label %else17

checkContinueBlock12:                             ; preds = %afterIfElse18
  br label %afterNestedBlock6

then16:                                           ; preds = %nestedBlock11
  br label %nestedBlock20

else17:                                           ; preds = %nestedBlock11
  br label %afterIfElse18

afterIfElse18:                                    ; preds = %else17, %afterNestedBlock19
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock12, label %afterNestedBlock6

afterNestedBlock19:                               ; preds = %checkContinueBlock21, %nestedBlock20
  br label %afterIfElse18

nestedBlock20:                                    ; preds = %then16
  %birdSpriteIndex22 = load i32, ptr %7, align 4
  store i32 0, ptr %7, align 4
  %35 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %checkContinueBlock21, label %afterNestedBlock19

checkContinueBlock21:                             ; preds = %nestedBlock20
  br label %afterNestedBlock19
}

define i1 @Bird.isTextureLoaded(ptr %0) !rt !55 {
entry:
  %1 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 7
  %8 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 8
  %9 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  %10 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i1 false

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %11 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  %12 = getelementptr inbounds %Texture.0, ptr %11, i32 0, i32 0
  %id = load i32, ptr %12, align 4
  %13 = icmp ne i32 %id, 0
  ret i1 %13

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getSource(ptr %0, ptr %1) !rt !56 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %12 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %birdSpriteIndex = load i32, ptr %7, align 4
  %birdSpritePosition = load [9 x %Position.4], ptr %11, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %birdSpriteIndex, 9
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %birdSpriteIndex, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %returnBlock
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %returnBlock
  call void @raise_exception(ptr @1)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %15 = getelementptr [9 x %Position.4], ptr %11, i32 0, i32 %birdSpriteIndex
  %16 = getelementptr inbounds %Position.4, ptr %15, i32 0, i32 0
  %x = load float, ptr %16, align 4
  %17 = load float, ptr %16, align 4
  store float %17, ptr %12, align 4
  %18 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %birdSpriteIndex1 = load i32, ptr %7, align 4
  %birdSpritePosition2 = load [9 x %Position.4], ptr %11, align 4
  %"GlobalIndexExpr::isLessThan6" = icmp slt i32 %birdSpriteIndex1, 9
  %"GlobalIndexExpr::isGreaterThan7" = icmp sge i32 %birdSpriteIndex1, 0
  %"GlobalIndexExpr::isWithinBounds8" = and i1 %"GlobalIndexExpr::isLessThan6", %"GlobalIndexExpr::isGreaterThan7"
  br i1 %"GlobalIndexExpr::isWithinBounds8", label %"GlobalIndexExpr::then3", label %"GlobalIndexExpr::else4"

"GlobalIndexExpr::then3":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge5"

"GlobalIndexExpr::else4":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge5"

"GlobalIndexExpr::merge5":                        ; preds = %"GlobalIndexExpr::else4", %"GlobalIndexExpr::then3"
  %19 = getelementptr [9 x %Position.4], ptr %11, i32 0, i32 %birdSpriteIndex1
  %20 = getelementptr inbounds %Position.4, ptr %19, i32 0, i32 1
  %y = load float, ptr %20, align 4
  %21 = load float, ptr %20, align 4
  store float %21, ptr %18, align 4
  %22 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %ACTUAL_BIRD_SIZE = load float, ptr %2, align 4
  %23 = load float, ptr %2, align 4
  store float %23, ptr %22, align 4
  %24 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %ACTUAL_BIRD_SIZE9 = load float, ptr %2, align 4
  %25 = load float, ptr %2, align 4
  store float %25, ptr %24, align 4
  ret void
}

define void @Bird.getDistination(ptr %0, ptr %1) !rt !57 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %12 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  br i1 false, label %if, label %else

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

if:                                               ; preds = %returnBlock
  call void @raise_exception(ptr @3)
  br label %merge

else:                                             ; preds = %returnBlock
  %15 = sitofp i32 %screenWidth to double
  %16 = fdiv double %15, 3.000000e+00
  br label %merge

merge:                                            ; preds = %else, %if
  %birdSize = load float, ptr %3, align 4
  br i1 false, label %if1, label %else2

if1:                                              ; preds = %merge
  call void @raise_exception(ptr @4)
  br label %else2

else2:                                            ; preds = %if1, %merge
  %17 = fdiv float %birdSize, 2.000000e+00
  %18 = fptrunc double %16 to float
  %19 = fsub float %18, %17
  store float %19, ptr %12, align 4
  %20 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  br i1 false, label %if3, label %else4

if3:                                              ; preds = %else2
  call void @raise_exception(ptr @5)
  br label %merge5

else4:                                            ; preds = %else2
  %21 = sitofp i32 %screenHeight to double
  %22 = fdiv double %21, 2.000000e+00
  br label %merge5

merge5:                                           ; preds = %else4, %if3
  %birdSize6 = load float, ptr %3, align 4
  br i1 false, label %if7, label %else8

if7:                                              ; preds = %merge5
  call void @raise_exception(ptr @6)
  br label %else8

else8:                                            ; preds = %if7, %merge5
  %23 = fdiv float %birdSize6, 2.000000e+00
  %24 = fptrunc double %22 to float
  %25 = fsub float %24, %23
  store float %25, ptr %20, align 4
  %26 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %birdSize9 = load float, ptr %3, align 4
  %27 = load float, ptr %3, align 4
  store float %27, ptr %26, align 4
  %28 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %birdSize10 = load float, ptr %3, align 4
  %29 = load float, ptr %3, align 4
  store float %29, ptr %28, align 4
  ret void
}

define void @Bird.getOrigin(ptr %0, ptr %1) !rt !58 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %12 = getelementptr [2 x float], ptr %0, i32 0, i32 0
  store float 0.000000e+00, ptr %12, align 4
  %13 = getelementptr [2 x float], ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %13, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define float @Bird.getRotation(ptr %0) !rt !59 {
entry:
  %1 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 1
  %2 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 2
  %3 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 3
  %4 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 4
  %5 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 5
  %6 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 6
  %7 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 7
  %8 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 8
  %9 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  %10 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret float 0.000000e+00

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  ret float 0.000000e+00

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getTexture(ptr %0, ptr %1) !rt !60 {
entry:
  %2 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %13 = load %Texture.0, ptr %12, align 4
  store %Texture.0 %13, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define i32 @main() !rt !61 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock14, %mergeBlock46, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %end_block44, %checkContinueBlock8, %afterIfElse, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %else, %checkContinueBlock, %nestedBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  %0 = call ptr @malloc(i64 96)
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  store ptr @7, ptr %1, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  store ptr @8, ptr %4, align 8
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %7 = getelementptr inbounds %COLORS_TYPE.3, ptr %6, i32 0, i32 0
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %COLORS_TYPE.3, ptr %6, i32 0, i32 1
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %COLORS_TYPE.3, ptr %6, i32 0, i32 2
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %COLORS_TYPE.3, ptr %6, i32 0, i32 3
  store i32 0, ptr %10, align 4
  %11 = getelementptr inbounds %COLORS_TYPE.3, ptr %6, i32 0, i32 4
  store i32 0, ptr %11, align 4
  %12 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  %13 = getelementptr inbounds %KEYS_TYPE.2, ptr %12, i32 0, i32 0
  store i32 0, ptr %13, align 4
  %14 = getelementptr inbounds %KEYS_TYPE.2, ptr %12, i32 0, i32 1
  store i32 0, ptr %14, align 4
  %15 = getelementptr inbounds %KEYS_TYPE.2, ptr %12, i32 0, i32 2
  store i32 0, ptr %15, align 4
  %16 = getelementptr inbounds %KEYS_TYPE.2, ptr %12, i32 0, i32 3
  store i32 0, ptr %16, align 4
  %17 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  %18 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 0
  store i32 0, ptr %18, align 4
  %19 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 1
  store i32 0, ptr %19, align 4
  %20 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 2
  store i32 0, ptr %20, align 4
  %21 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 3
  store i32 0, ptr %21, align 4
  %22 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 4
  store i32 0, ptr %22, align 4
  %23 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 5
  store i32 0, ptr %23, align 4
  %24 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 6
  store i32 0, ptr %24, align 4
  %25 = getelementptr inbounds %LOG_TYPE.1, ptr %17, i32 0, i32 7
  store i32 0, ptr %25, align 4
  %26 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %26, align 8
  %27 = load ptr, ptr %26, align 8
  %28 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 23
  store ptr @FlowWingAnim.setTargetFPS, ptr %28, align 8
  %29 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 22
  store ptr @FlowWingAnim.endDrawing, ptr %29, align 8
  %30 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 21
  store ptr @FlowWingAnim.createWindow, ptr %30, align 8
  %31 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %31, align 8
  %32 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 20
  store ptr @FlowWingAnim.drawTexturePro, ptr %32, align 8
  %33 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 16
  store ptr @FlowWingAnim.drawRectangle, ptr %33, align 8
  %34 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 15
  store ptr @FlowWingAnim.beginDrawing, ptr %34, align 8
  %35 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 1
  store ptr @FlowWingAnim.traceLog, ptr %35, align 8
  %36 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 14
  store ptr @FlowWingAnim.unloadTexture, ptr %36, align 8
  %37 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 13
  store ptr @FlowWingAnim.closeWindow, ptr %37, align 8
  %38 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 17
  store ptr @FlowWingAnim.getColor, ptr %38, align 8
  %39 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 12
  store ptr @FlowWingAnim.textFormat, ptr %39, align 8
  %40 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 18
  store ptr @FlowWingAnim.windowShouldClose, ptr %40, align 8
  %41 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenWidth, ptr %41, align 8
  %42 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenHeight, ptr %42, align 8
  %43 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 11
  store ptr @FlowWingAnim.getTime, ptr %43, align 8
  %44 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 19
  store ptr @FlowWingAnim.beforeInit, ptr %44, align 8
  %45 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 10
  store ptr @FlowWingAnim.clearBackground, ptr %45, align 8
  %46 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 7
  store ptr @FlowWingAnim.drawTexture, ptr %46, align 8
  %47 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 8
  store ptr @FlowWingAnim.getFrameTime, ptr %47, align 8
  %48 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 2
  store ptr @FlowWingAnim.drawText, ptr %48, align 8
  %49 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %49, align 8
  %50 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 9
  store ptr @FlowWingAnim.loadTexture, ptr %50, align 8
  %51 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %51, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %52 = alloca ptr, align 8
  store ptr @9, ptr %52, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %52, ptr @FPS, ptr %0)
  %53 = load %FlowWingAnim, ptr %0, align 8
  store %FlowWingAnim %53, ptr %0, align 8
  %54 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %56 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %58 = call ptr @malloc(i64 144)
  %59 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  store ptr @10, ptr %59, align 8
  %60 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 1
  store float 0.000000e+00, ptr %60, align 4
  %61 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 2
  store float 0.000000e+00, ptr %61, align 4
  %62 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 3
  store double 0.000000e+00, ptr %62, align 8
  %63 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 4
  store double 0.000000e+00, ptr %63, align 8
  %64 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 5
  store i32 0, ptr %64, align 4
  %65 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 6
  store i32 0, ptr %65, align 4
  %66 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 7
  store ptr @11, ptr %66, align 8
  %67 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 8
  store i1 false, ptr %67, align 1
  %68 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 9
  %69 = getelementptr inbounds %Texture.0, ptr %68, i32 0, i32 0
  store i32 0, ptr %69, align 4
  %70 = getelementptr inbounds %Texture.0, ptr %68, i32 0, i32 1
  store i32 0, ptr %70, align 4
  %71 = getelementptr inbounds %Texture.0, ptr %68, i32 0, i32 2
  store i32 0, ptr %71, align 4
  %72 = getelementptr inbounds %Texture.0, ptr %68, i32 0, i32 3
  store i32 0, ptr %72, align 4
  %73 = getelementptr inbounds %Texture.0, ptr %68, i32 0, i32 4
  store i32 0, ptr %73, align 4
  %74 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 10
  %75 = alloca i32, align 4
  %76 = alloca i32, align 4
  store i32 0, ptr %76, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock2:                              ; preds = %else
  %77 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %79 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %80 = load ptr, ptr %79, align 8
  %81 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %80, i32 0, i32 21
  %82 = load ptr, ptr %81, align 8
  call void %82(ptr %0)
  %83 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %85 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %87 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %88 = load ptr, ptr %87, align 8
  %89 = getelementptr inbounds %"Bird::VTableType", ptr %88, i32 0, i32 8
  %90 = load ptr, ptr %89, align 8
  %91 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %92 = load ptr, ptr %91, align 8
  %93 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %92, i32 0, i32 9
  %94 = load ptr, ptr %93, align 8
  %rtPtr = alloca %Texture.0, align 8
  %95 = alloca ptr, align 8
  store ptr @14, ptr %95, align 8
  call void %94(ptr %rtPtr, ptr %95, ptr %0)
  call void %90(ptr %rtPtr, ptr %58)
  %96 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %97 = icmp eq i32 %96, 0
  br i1 %97, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %98 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %100 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %101 = load ptr, ptr %100, align 8
  %102 = getelementptr inbounds %"Bird::VTableType", ptr %101, i32 0, i32 5
  %103 = load ptr, ptr %102, align 8
  %104 = call i1 %103(ptr %58)
  %105 = xor i1 %104, true
  br i1 %105, label %then, label %else16

checkContinueBlock8:                              ; preds = %afterIfElse
  %106 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  br label %"while:conditon"

checkContinueBlock10:                             ; preds = %end_block44
  %108 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %110 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %111 = load ptr, ptr %110, align 8
  %112 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %111, i32 0, i32 13
  %113 = load ptr, ptr %112, align 8
  call void %113(ptr %0)
  %114 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %115 = icmp eq i32 %114, 0
  br i1 %115, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %116 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %117 = icmp eq i32 %116, 0
  br i1 %117, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  br label %returnBlock45

checkContinueBlock14:                             ; preds = %mergeBlock46
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock1
  store i32 0, ptr %75, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %118 = load i32, ptr %75, align 4
  %119 = icmp slt i32 %118, 9
  %120 = load i32, ptr %76, align 4
  %121 = icmp slt i32 %120, 9
  %122 = and i1 %119, %121
  br i1 %122, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %123 = load i32, ptr %75, align 4
  %124 = getelementptr [9 x %Position.4], ptr %74, i32 0, i32 %123
  %125 = getelementptr inbounds %Position.4, ptr %124, i32 0, i32 0
  store float 0.000000e+00, ptr %125, align 4
  %126 = getelementptr inbounds %Position.4, ptr %124, i32 0, i32 1
  store float 0.000000e+00, ptr %126, align 4
  %127 = load i32, ptr %75, align 4
  %128 = add i32 %127, 1
  store i32 %128, ptr %75, align 4
  %129 = load i32, ptr %76, align 4
  %130 = add i32 %129, 1
  store i32 %130, ptr %76, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %131 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %131, align 8
  %132 = load ptr, ptr %131, align 8
  %133 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 7
  store ptr @Bird.getTexturePath, ptr %133, align 8
  %134 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 5
  store ptr @Bird.isTextureLoaded, ptr %134, align 8
  %135 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 8
  store ptr @Bird.setTexture, ptr %135, align 8
  %136 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 2
  store ptr @Bird.getOrigin, ptr %136, align 8
  %137 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 4
  store ptr @Bird.getSource, ptr %137, align 8
  %138 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 6
  store ptr @Bird.update, ptr %138, align 8
  %139 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 0
  store ptr @Bird.getTexture, ptr %139, align 8
  %140 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 3
  store ptr @Bird.getDistination, ptr %140, align 8
  %141 = getelementptr inbounds %"Bird::VTableType", ptr %132, i32 0, i32 1
  store ptr @Bird.getRotation, ptr %141, align 8
  %142 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 1
  store float 3.600000e+02, ptr %142, align 4
  %143 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 2
  store float 9.000000e+01, ptr %143, align 4
  %144 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 3
  %FPS15 = load i32, ptr @FPS, align 4
  %145 = sitofp i32 %FPS15 to double
  %146 = fcmp oeq double %145, 0.000000e+00
  br i1 %146, label %if, label %else

if:                                               ; preds = %FillExpr.exit
  call void @raise_exception(ptr @12)
  br label %else

else:                                             ; preds = %if, %FillExpr.exit
  %147 = fdiv double 1.000000e+00, %145
  store double %147, ptr %144, align 8
  %148 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 5
  store i32 9, ptr %148, align 4
  %149 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 6
  store i32 0, ptr %149, align 4
  %150 = alloca ptr, align 8
  store ptr @13, ptr %150, align 8
  call void @Bird.init1(ptr %150, ptr %58)
  %151 = load %Bird, ptr %58, align 8
  store %Bird %151, ptr %58, align 8
  %152 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %153 = icmp eq i32 %152, 0
  br i1 %153, label %checkContinueBlock2, label %afterNestedBlock

then:                                             ; preds = %nestedBlock7
  br label %nestedBlock18

else16:                                           ; preds = %nestedBlock7
  br label %afterIfElse

afterIfElse:                                      ; preds = %else16, %afterNestedBlock17
  %154 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %155 = icmp eq i32 %154, 0
  br i1 %155, label %checkContinueBlock8, label %afterNestedBlock

afterNestedBlock17:                               ; preds = %checkContinueBlock25, %mergeBlock, %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18
  br label %afterIfElse

nestedBlock18:                                    ; preds = %then
  %156 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %157 = load ptr, ptr %156, align 8
  %158 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %157, i32 0, i32 1
  %159 = load ptr, ptr %158, align 8
  %160 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  %161 = getelementptr inbounds %LOG_TYPE.1, ptr %160, i32 0, i32 5
  %ERROR = load i32, ptr %161, align 4
  %162 = alloca ptr, align 8
  store ptr @15, ptr %162, align 8
  call void %159(ptr %161, ptr %162, ptr %0)
  %163 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %164 = icmp eq i32 %163, 0
  br i1 %164, label %checkContinueBlock19, label %afterNestedBlock17

checkContinueBlock19:                             ; preds = %nestedBlock18
  %165 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %166 = icmp eq i32 %165, 0
  br i1 %166, label %nestedBlock20, label %afterNestedBlock17

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %167 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %168 = load ptr, ptr %167, align 8
  %169 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %168, i32 0, i32 14
  %170 = load ptr, ptr %169, align 8
  %171 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %172 = load ptr, ptr %171, align 8
  %173 = getelementptr inbounds %"Bird::VTableType", ptr %172, i32 0, i32 0
  %174 = load ptr, ptr %173, align 8
  %rtPtr26 = alloca %Texture.0, align 8
  call void %174(ptr %rtPtr26, ptr %58)
  call void %170(ptr %rtPtr26, ptr %0)
  %175 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %176 = icmp eq i32 %175, 0
  br i1 %176, label %checkContinueBlock21, label %afterNestedBlock17

checkContinueBlock21:                             ; preds = %nestedBlock20
  %177 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %178 = icmp eq i32 %177, 0
  br i1 %178, label %nestedBlock22, label %afterNestedBlock17

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %179 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %180 = load ptr, ptr %179, align 8
  %181 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %180, i32 0, i32 13
  %182 = load ptr, ptr %181, align 8
  call void %182(ptr %0)
  %183 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %184 = icmp eq i32 %183, 0
  br i1 %184, label %checkContinueBlock23, label %afterNestedBlock17

checkContinueBlock23:                             ; preds = %nestedBlock22
  %185 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %nestedBlock24, label %afterNestedBlock17

nestedBlock24:                                    ; preds = %checkContinueBlock23
  br label %returnBlock

checkContinueBlock25:                             ; preds = %mergeBlock
  br label %afterNestedBlock17

returnBlock:                                      ; preds = %nestedBlock24
  ret i32 1

mergeBlock:                                       ; No predecessors!
  %187 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %188 = icmp eq i32 %187, 0
  br i1 %188, label %checkContinueBlock25, label %afterNestedBlock17

"while:conditon":                                 ; preds = %afterNestedBlock27, %nestedBlock9
  %189 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %190 = icmp eq i32 %189, 0
  br i1 %190, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock28

while.end:                                        ; preds = %afterNestedBlock27, %end_block
  %191 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %192 = icmp eq i32 %191, 0
  br i1 %192, label %end_block44, label %decrement_block43

decrement_block:                                  ; preds = %"while:conditon"
  %193 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %194 = sub i32 %193, 1
  store i32 %194, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %195 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %196 = load ptr, ptr %195, align 8
  %197 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %196, i32 0, i32 18
  %198 = load ptr, ptr %197, align 8
  %199 = call i1 %198(ptr %0)
  %200 = xor i1 %199, true
  br i1 %200, label %"while:body", label %while.end

afterNestedBlock27:                               ; preds = %checkContinueBlock37, %nestedBlock36, %checkContinueBlock35, %nestedBlock34, %checkContinueBlock33, %nestedBlock32, %checkContinueBlock31, %nestedBlock30, %checkContinueBlock29, %nestedBlock28
  %201 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %202 = icmp eq i32 %201, 0
  br i1 %202, label %"while:conditon", label %while.end

nestedBlock28:                                    ; preds = %"while:body"
  %203 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %204 = load ptr, ptr %203, align 8
  %205 = getelementptr inbounds %"Bird::VTableType", ptr %204, i32 0, i32 6
  %206 = load ptr, ptr %205, align 8
  %207 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %208 = load ptr, ptr %207, align 8
  %209 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %208, i32 0, i32 8
  %210 = load ptr, ptr %209, align 8
  %211 = call float %210(ptr %0)
  call void %206(float %211, ptr %58)
  %212 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %213 = icmp eq i32 %212, 0
  br i1 %213, label %checkContinueBlock29, label %afterNestedBlock27

checkContinueBlock29:                             ; preds = %nestedBlock28
  %214 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %215 = icmp eq i32 %214, 0
  br i1 %215, label %nestedBlock30, label %afterNestedBlock27

nestedBlock30:                                    ; preds = %checkContinueBlock29
  %216 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %217 = load ptr, ptr %216, align 8
  %218 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %217, i32 0, i32 15
  %219 = load ptr, ptr %218, align 8
  call void %219(ptr %0)
  %220 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %221 = icmp eq i32 %220, 0
  br i1 %221, label %checkContinueBlock31, label %afterNestedBlock27

checkContinueBlock31:                             ; preds = %nestedBlock30
  %222 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %223 = icmp eq i32 %222, 0
  br i1 %223, label %nestedBlock32, label %afterNestedBlock27

nestedBlock32:                                    ; preds = %checkContinueBlock31
  %224 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %225 = load ptr, ptr %224, align 8
  %226 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %225, i32 0, i32 10
  %227 = load ptr, ptr %226, align 8
  %228 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %229 = getelementptr inbounds %COLORS_TYPE.3, ptr %228, i32 0, i32 0
  %WHITE = load i32, ptr %229, align 4
  call void %227(ptr %229, ptr %0)
  %230 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %231 = icmp eq i32 %230, 0
  br i1 %231, label %checkContinueBlock33, label %afterNestedBlock27

checkContinueBlock33:                             ; preds = %nestedBlock32
  %232 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %233 = icmp eq i32 %232, 0
  br i1 %233, label %nestedBlock34, label %afterNestedBlock27

nestedBlock34:                                    ; preds = %checkContinueBlock33
  %234 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %235 = load ptr, ptr %234, align 8
  %236 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %235, i32 0, i32 20
  %237 = load ptr, ptr %236, align 8
  %238 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %239 = load ptr, ptr %238, align 8
  %240 = getelementptr inbounds %"Bird::VTableType", ptr %239, i32 0, i32 0
  %241 = load ptr, ptr %240, align 8
  %rtPtr38 = alloca %Texture.0, align 8
  call void %241(ptr %rtPtr38, ptr %58)
  %242 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %243 = load ptr, ptr %242, align 8
  %244 = getelementptr inbounds %"Bird::VTableType", ptr %243, i32 0, i32 4
  %245 = load ptr, ptr %244, align 8
  %rtPtr39 = alloca [4 x float], align 4
  call void %245(ptr %rtPtr39, ptr %58)
  %246 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %247 = load ptr, ptr %246, align 8
  %248 = getelementptr inbounds %"Bird::VTableType", ptr %247, i32 0, i32 3
  %249 = load ptr, ptr %248, align 8
  %rtPtr40 = alloca [4 x float], align 4
  call void %249(ptr %rtPtr40, ptr %58)
  %250 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %251 = load ptr, ptr %250, align 8
  %252 = getelementptr inbounds %"Bird::VTableType", ptr %251, i32 0, i32 2
  %253 = load ptr, ptr %252, align 8
  %rtPtr41 = alloca [2 x float], align 4
  call void %253(ptr %rtPtr41, ptr %58)
  %254 = getelementptr inbounds %Bird, ptr %58, i32 0, i32 0
  %255 = load ptr, ptr %254, align 8
  %256 = getelementptr inbounds %"Bird::VTableType", ptr %255, i32 0, i32 1
  %257 = load ptr, ptr %256, align 8
  %258 = call float %257(ptr %58)
  %259 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %260 = getelementptr inbounds %COLORS_TYPE.3, ptr %259, i32 0, i32 0
  %WHITE42 = load i32, ptr %260, align 4
  call void %237(ptr %rtPtr38, ptr %rtPtr39, ptr %rtPtr40, ptr %rtPtr41, float %258, ptr %260, ptr %0)
  %261 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %262 = icmp eq i32 %261, 0
  br i1 %262, label %checkContinueBlock35, label %afterNestedBlock27

checkContinueBlock35:                             ; preds = %nestedBlock34
  %263 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %264 = icmp eq i32 %263, 0
  br i1 %264, label %nestedBlock36, label %afterNestedBlock27

nestedBlock36:                                    ; preds = %checkContinueBlock35
  %265 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %266 = load ptr, ptr %265, align 8
  %267 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %266, i32 0, i32 22
  %268 = load ptr, ptr %267, align 8
  call void %268(ptr %0)
  %269 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %270 = icmp eq i32 %269, 0
  br i1 %270, label %checkContinueBlock37, label %afterNestedBlock27

checkContinueBlock37:                             ; preds = %nestedBlock36
  br label %afterNestedBlock27

decrement_block43:                                ; preds = %while.end
  %271 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %272 = sub i32 %271, 1
  store i32 %272, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block44

end_block44:                                      ; preds = %decrement_block43, %while.end
  %273 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %274 = icmp eq i32 %273, 0
  br i1 %274, label %checkContinueBlock10, label %afterNestedBlock

returnBlock45:                                    ; preds = %nestedBlock13
  ret i32 0

mergeBlock46:                                     ; No predecessors!
  %275 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %276 = icmp eq i32 %275, 0
  br i1 %276, label %checkContinueBlock14, label %afterNestedBlock
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
!9 = !{!"FlowWingAnim.endDrawing:rt:pr:27"}
!10 = !{!"FlowWingAnim.closeWindow:rt:pr:27"}
!11 = !{!"FlowWingAnim.getTime:rt:pr:31"}
!12 = !{!"FlowWingAnim.getFrameTime:rt:pr:32"}
!13 = !{!"FlowWingAnim.getScreenHeight:rt:pr:28"}
!14 = !{!"FlowWingAnim.getScreenWidth:rt:pr:28"}
!15 = !{!"FlowWingAnim.drawCircle:rt:pr:27"}
!16 = !{!"FlowWingAnim.drawText:rt:pr:27"}
!17 = !{!"FlowWingAnim.drawTexture:rt:pr:27"}
!18 = !{!"FlowWingAnim.drawTexturePro:rt:pr:27"}
!19 = !{!"FlowWingAnim.traceLog:rt:pr:27"}
!20 = !{!"FlowWingAnim.loadTexture:rt:ob:Texture"}
!21 = !{!"FlowWingAnim.unloadTexture:rt:pr:27"}
!22 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!23 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!24 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!25 = !{!"SetTargetFPS:rt:pr:27"}
!26 = !{!"getRandomNumber:rt:pr:28"}
!27 = !{!"ClearBackground:rt:pr:27"}
!28 = !{!"DrawTexturePro:rt:pr:27"}
!29 = !{!"TraceLog:rt:pr:27"}
!30 = !{!"GetScreenWidth:rt:pr:28"}
!31 = !{!"DrawCircle:rt:pr:27"}
!32 = !{!"time:rt:pr:28"}
!33 = !{!"BeginDrawing:rt:pr:27"}
!34 = !{!"IsKeyPressed:rt:pr:34"}
!35 = !{!"WindowShouldClose:rt:pr:34"}
!36 = !{!"InitWindow:rt:pr:27"}
!37 = !{!"EndDrawing:rt:pr:27"}
!38 = !{!"CloseWindow:rt:pr:27"}
!39 = !{!"GetScreenHeight:rt:pr:28"}
!40 = !{!"GetFrameTime:rt:pr:32"}
!41 = !{!"DrawText:rt:pr:27"}
!42 = !{!"GetTime:rt:pr:31"}
!43 = !{!"UnloadTexture:rt:pr:27"}
!44 = !{!"TextFormat:rt:pr:33"}
!45 = !{!"LoadTexture:rt:ob:Texture"}
!46 = !{!"IsKeyDown:rt:pr:34"}
!47 = !{!"DrawRectangle:rt:pr:27"}
!48 = !{!"DrawTexture:rt:pr:27"}
!49 = !{!"srand:rt:pr:27"}
!50 = !{!"rand:rt:pr:28"}
!51 = !{!"Bird.init1:rt:pr:27"}
!52 = !{!"Bird.setTexture:rt:pr:27"}
!53 = !{!"Bird.getTexturePath:rt:pr:33"}
!54 = !{!"Bird.update:rt:pr:27"}
!55 = !{!"Bird.isTextureLoaded:rt:pr:34"}
!56 = !{!"Bird.getSource:rt:ay:32:sz:4:"}
!57 = !{!"Bird.getDistination:rt:ay:32:sz:4:"}
!58 = !{!"Bird.getOrigin:rt:ay:32:sz:2:"}
!59 = !{!"Bird.getRotation:rt:pr:32"}
!60 = !{!"Bird.getTexture:rt:ob:Texture"}
!61 = !{!"main:rt:pr:28"}
