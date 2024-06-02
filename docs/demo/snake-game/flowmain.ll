; ModuleID = 'flowmain'
source_filename = "flowmain"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
%Position.4 = type { float, float }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.3, %KEYS_TYPE.2, %LOG_TYPE.1 }
%COLORS_TYPE.3 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.2 = type { i32, i32, i32, i32 }
%LOG_TYPE.1 = type { i32, i32, i32, i32, i32, i32, i32, i32 }
%Texture.0 = type { i32, i32, i32, i32, i32 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.FlowWingAnim.fg = common global %"FlowWingAnim::VTableType" zeroinitializer
@screenWidth = common global i32 0
@screenHeight = common global i32 0
@side = common global i32 0
@ACTUAL_BIRD_SIZE = common global float 0.000000e+00
@birdSize = common global float 0.000000e+00
@FPS = common global i32 0
@0 = private unnamed_addr constant [701 x i8] c"\0A\1B[33m5| \1B[0m\1B[0mconst side: int = 10\0A\1B[0m\1B[33m6| \1B[0m\1B[0mconst ACTUAL_BIRD_SIZE: deci32 = 360.0d\0A\1B[0m\1B[33m7| \1B[0m\1B[0mvar birdSize: deci32 = 90.0d\0A\1B[0m\1B[33m8| \1B[0m\1B[0mconst FPS:int = 12\0A\1B[0m\1B[33m9| \1B[0m\1B[31m\1B[1mconst BIRD_TIMMER: deci = 1.0/FPS\0A\1B[0m\1B[32m\1B[1m                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m10| \1B[0m\1B[0mvar birdTimmer:deci = BIRD_TIMMER\0A\1B[0m\1B[33m11| \1B[0m\1B[0mconst BIRD_SPRITE_SIZE = 9\0A\1B[0m\1B[33m12| \1B[0m\1B[0mvar birdSpriteIndex = 0\0A\1B[0m\1B[33m13| \1B[0m\1B[0mtype Position = {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 9:30\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@BIRD_TIMMER = common global double 0.000000e+00
@birdTimmer = common global double 0.000000e+00
@BIRD_SPRITE_SIZE = common global %DynamicType zeroinitializer
@birdSpriteIndex = common global %DynamicType zeroinitializer
@birdSpritePosition = common global [9 x %Position.4] zeroinitializer
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@4 = private unnamed_addr constant [11 x i8] c"./bird.png\00", align 1
@5 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1
@6 = private unnamed_addr constant [1020 x i8] c"\0A\1B[33m75| \1B[0m\1B[0m\0A\1B[0m\1B[33m76| \1B[0m\1B[0m\0A\1B[0m\1B[33m77| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m79| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(birdTexture, [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE], [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize], [0.0d, 0.0d], 0.0d, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m80| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  return 0\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 79:60\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@7 = private unnamed_addr constant [1098 x i8] c"\0A\1B[33m75| \1B[0m\1B[0m\0A\1B[0m\1B[33m76| \1B[0m\1B[0m\0A\1B[0m\1B[33m77| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m79| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(birdTexture, [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE], [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize], [0.0d, 0.0d], 0.0d, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m80| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  return 0\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 79:99\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@8 = private unnamed_addr constant [1192 x i8] c"\0A\1B[33m75| \1B[0m\1B[0m\0A\1B[0m\1B[33m76| \1B[0m\1B[0m\0A\1B[0m\1B[33m77| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m79| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(birdTexture, [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE], [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize], [0.0d, 0.0d], 0.0d, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                                                     \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m80| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  return 0\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 79:181\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [1233 x i8] c"\0A\1B[33m75| \1B[0m\1B[0m\0A\1B[0m\1B[33m76| \1B[0m\1B[0m\0A\1B[0m\1B[33m77| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m79| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(birdTexture, [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE], [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize], [0.0d, 0.0d], 0.0d, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m80| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  return 0\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 79:194\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [1280 x i8] c"\0A\1B[33m75| \1B[0m\1B[0m\0A\1B[0m\1B[33m76| \1B[0m\1B[0m\0A\1B[0m\1B[33m77| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m79| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(birdTexture, [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE], [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize], [0.0d, 0.0d], 0.0d, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                                                                                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m80| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  return 0\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 79:225\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [1321 x i8] c"\0A\1B[33m75| \1B[0m\1B[0m\0A\1B[0m\1B[33m76| \1B[0m\1B[0m\0A\1B[0m\1B[33m77| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m79| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(birdTexture, [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE], [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize], [0.0d, 0.0d], 0.0d, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                                                                                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m80| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  return 0\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 79:238\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1

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
  store i32 0, ptr @side, align 4
  store i32 10, ptr @side, align 4
  store float 0.000000e+00, ptr @ACTUAL_BIRD_SIZE, align 4
  store float 3.600000e+02, ptr @ACTUAL_BIRD_SIZE, align 4
  store float 0.000000e+00, ptr @birdSize, align 4
  store float 9.000000e+01, ptr @birdSize, align 4
  store i32 0, ptr @FPS, align 4
  store i32 12, ptr @FPS, align 4
  %FPS = load i32, ptr @FPS, align 4
  %1 = sitofp i32 %FPS to double
  %2 = fcmp oeq double %1, 0.000000e+00
  br i1 %2, label %if, label %else

returnBlock:                                      ; preds = %FillExpr.exit
  ret i32 0

if:                                               ; preds = %entry
  call void @raise_exception(ptr @0)
  br label %else

else:                                             ; preds = %if, %entry
  %3 = fdiv double 1.000000e+00, %1
  store double 0.000000e+00, ptr @BIRD_TIMMER, align 8
  store double %3, ptr @BIRD_TIMMER, align 8
  %BIRD_TIMMER = load double, ptr @BIRD_TIMMER, align 8
  store double 0.000000e+00, ptr @birdTimmer, align 8
  store double %BIRD_TIMMER, ptr @birdTimmer, align 8
  store i32 9, ptr @BIRD_SPRITE_SIZE, align 4
  store i32 0, ptr @birdSpriteIndex, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, ptr %5, align 4
  br label %FillExpr.loopStart-0

FillExpr.loopStart-0:                             ; preds = %else
  store i32 0, ptr %4, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %6 = load i32, ptr %4, align 4
  %7 = icmp slt i32 %6, 9
  %8 = load i32, ptr %5, align 4
  %9 = icmp slt i32 %8, 9
  %10 = and i1 %7, %9
  br i1 %10, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %11 = load i32, ptr %4, align 4
  %12 = getelementptr [9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 %11
  %13 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 0
  store float 0.000000e+00, ptr %13, align 4
  %14 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  store float 0.000000e+00, ptr %14, align 4
  %15 = load i32, ptr %4, align 4
  %16 = add i32 %15, 1
  store i32 %16, ptr %4, align 4
  %17 = load i32, ptr %5, align 4
  %18 = add i32 %17, 1
  store i32 %18, ptr %5, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  store float 0.000000e+00, ptr @birdSpritePosition, align 4
  store float 0.000000e+00, ptr getelementptr inbounds (%Position.4, ptr @birdSpritePosition, i32 0, i32 1), align 4
  %ACTUAL_BIRD_SIZE = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %19 = fmul float %ACTUAL_BIRD_SIZE, 1.000000e+00
  store float %19, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 1), align 4
  store float 0.000000e+00, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 1, i32 1), align 4
  %ACTUAL_BIRD_SIZE1 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %20 = fmul float %ACTUAL_BIRD_SIZE1, 2.000000e+00
  store float %20, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 2), align 4
  store float 0.000000e+00, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 2, i32 1), align 4
  store float 0.000000e+00, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 3), align 4
  %ACTUAL_BIRD_SIZE2 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %21 = fmul float %ACTUAL_BIRD_SIZE2, 1.000000e+00
  store float %21, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 3, i32 1), align 4
  %ACTUAL_BIRD_SIZE3 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %22 = fmul float %ACTUAL_BIRD_SIZE3, 1.000000e+00
  store float %22, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 4), align 4
  %ACTUAL_BIRD_SIZE4 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %23 = fmul float %ACTUAL_BIRD_SIZE4, 1.000000e+00
  store float %23, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 4, i32 1), align 4
  %ACTUAL_BIRD_SIZE5 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %24 = fmul float %ACTUAL_BIRD_SIZE5, 2.000000e+00
  store float %24, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 5), align 4
  %ACTUAL_BIRD_SIZE6 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %25 = fmul float %ACTUAL_BIRD_SIZE6, 1.000000e+00
  store float %25, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 5, i32 1), align 4
  store float 0.000000e+00, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 6), align 4
  %ACTUAL_BIRD_SIZE7 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %26 = fmul float %ACTUAL_BIRD_SIZE7, 2.000000e+00
  store float %26, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 6, i32 1), align 4
  %ACTUAL_BIRD_SIZE8 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %27 = fmul float %ACTUAL_BIRD_SIZE8, 1.000000e+00
  store float %27, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 7), align 4
  %ACTUAL_BIRD_SIZE9 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %28 = fmul float %ACTUAL_BIRD_SIZE9, 2.000000e+00
  store float %28, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 7, i32 1), align 4
  %ACTUAL_BIRD_SIZE10 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %29 = fmul float %ACTUAL_BIRD_SIZE10, 2.000000e+00
  store float %29, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 8), align 4
  %ACTUAL_BIRD_SIZE11 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %30 = fmul float %ACTUAL_BIRD_SIZE11, 2.000000e+00
  store float %30, ptr getelementptr inbounds ([9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 8, i32 1), align 4
  %31 = call i32 @main()
  br label %returnBlock
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

declare !rt !11 i32 @FlowWingAnim.getScreenHeight(ptr)

declare !rt !12 i32 @FlowWingAnim.getScreenWidth(ptr)

declare !rt !13 void @FlowWingAnim.drawCircle(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.drawText(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !15 void @FlowWingAnim.drawTexture(ptr, ptr, ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !17 void @FlowWingAnim.traceLog(ptr, ptr, ptr)

declare !rt !18 void @FlowWingAnim.loadTexture(ptr, ptr, ptr)

declare !rt !19 i1 @FlowWingAnim.isKeyPressed(ptr, ptr)

declare !rt !20 i1 @FlowWingAnim.isKeyDown(ptr, ptr)

declare !rt !21 ptr @FlowWingAnim.textFormat(ptr, ptr)

declare !rt !21 ptr @FlowWingAnim.textFormat.1(ptr, ptr)

declare !rt !19 i1 @FlowWingAnim.isKeyPressed.2(ptr, ptr)

declare !rt !18 void @FlowWingAnim.loadTexture.3(ptr, ptr, ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle.4(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow.5(ptr)

declare !rt !17 void @FlowWingAnim.traceLog.6(ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.drawText.7(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !22 void @SetTargetFPS(i32)

declare !rt !7 void @FlowWingAnim.beginDrawing.8(ptr)

declare !rt !13 void @FlowWingAnim.drawCircle.9(ptr, ptr, ptr, ptr, ptr)

declare !rt !23 void @LoadTexture(ptr sret, ptr)

declare !rt !20 i1 @FlowWingAnim.isKeyDown.10(ptr, ptr)

declare !rt !12 i32 @FlowWingAnim.getScreenWidth.11(ptr)

declare !rt !24 i32 @getRandomNumber(ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit.12(ptr)

declare !rt !11 i32 @FlowWingAnim.getScreenHeight.13(ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.14(ptr)

declare !rt !9 void @FlowWingAnim.endDrawing.15(ptr)

declare !rt !3 i32 @FlowWingAnim.getColor.16(ptr, ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.17(ptr)

declare !rt !0 void @FlowWingAnim.init4.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !25 void @ClearBackground(i32)

declare !rt !26 void @TraceLog(i32, ptr)

declare !rt !27 i32 @GetScreenWidth()

declare !rt !28 void @DrawCircle(i32, i32, float, i32)

declare !rt !29 i32 @time()

declare !rt !30 void @BeginDrawing()

declare !rt !31 i1 @IsKeyPressed(i32)

declare !rt !32 i1 @WindowShouldClose()

declare !rt !33 void @InitWindow(i32, i32, ptr)

declare !rt !34 void @EndDrawing()

declare !rt !35 void @CloseWindow()

declare !rt !15 void @FlowWingAnim.drawTexture.19(ptr, ptr, ptr, ptr, ptr)

declare !rt !36 i32 @GetScreenHeight()

declare !rt !16 void @FlowWingAnim.drawTexturePro.20(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !37 float @GetFrameTime()

declare !rt !38 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !39 double @GetTime()

declare !rt !40 void @UnloadTexture(ptr)

declare !rt !41 ptr @TextFormat(ptr)

declare !rt !42 i1 @IsKeyDown(i32)

declare !rt !6 i1 @FlowWingAnim.windowShouldClose.21(ptr)

declare !rt !43 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !44 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !45 void @srand(i32)

declare !rt !5 void @FlowWingAnim.clearBackground.22(ptr, ptr)

declare !rt !46 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !47 i32 @rand()

define i32 @main() !rt !48 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock12, %mergeBlock96, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %end_block94, %checkContinueBlock6, %afterIfElse, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  %0 = call ptr @malloc(i64 96)
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  store ptr @1, ptr %1, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  store ptr @2, ptr %4, align 8
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
  %28 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 19
  store ptr @FlowWingAnim.endDrawing, ptr %28, align 8
  %29 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 20
  store ptr @FlowWingAnim.setTargetFPS, ptr %29, align 8
  %30 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 18
  store ptr @FlowWingAnim.createWindow, ptr %30, align 8
  %31 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 17
  store ptr @FlowWingAnim.drawTexturePro, ptr %31, align 8
  %32 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 16
  store ptr @FlowWingAnim.clearBackground, ptr %32, align 8
  %33 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 15
  store ptr @FlowWingAnim.beforeInit, ptr %33, align 8
  %34 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 14
  store ptr @FlowWingAnim.textFormat, ptr %34, align 8
  %35 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 13
  store ptr @FlowWingAnim.windowShouldClose, ptr %35, align 8
  %36 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 11
  store ptr @FlowWingAnim.drawRectangle, ptr %36, align 8
  %37 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 10
  store ptr @FlowWingAnim.beginDrawing, ptr %37, align 8
  %38 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 9
  store ptr @FlowWingAnim.closeWindow, ptr %38, align 8
  %39 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 8
  store ptr @FlowWingAnim.getScreenHeight, ptr %39, align 8
  %40 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 7
  store ptr @FlowWingAnim.getScreenWidth, ptr %40, align 8
  %41 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 5
  store ptr @FlowWingAnim.isKeyDown, ptr %41, align 8
  %42 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 6
  store ptr @FlowWingAnim.drawCircle, ptr %42, align 8
  %43 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 4
  store ptr @FlowWingAnim.drawText, ptr %43, align 8
  %44 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 12
  store ptr @FlowWingAnim.getColor, ptr %44, align 8
  %45 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 1
  store ptr @FlowWingAnim.loadTexture, ptr %45, align 8
  %46 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 2
  store ptr @FlowWingAnim.traceLog, ptr %46, align 8
  %47 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 3
  store ptr @FlowWingAnim.drawTexture, ptr %47, align 8
  %48 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %27, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %48, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %49 = alloca ptr, align 8
  store ptr @3, ptr %49, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %49, ptr @FPS, ptr %0)
  %50 = load %FlowWingAnim, ptr %0, align 8
  store %FlowWingAnim %50, ptr %0, align 8
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %53 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %55 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %56 = load ptr, ptr %55, align 8
  %57 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %56, i32 0, i32 18
  %58 = load ptr, ptr %57, align 8
  call void %58(ptr %0)
  %59 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %61 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %birdTexture = alloca %Texture.0, align 8
  %63 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 0
  store i32 0, ptr %63, align 4
  %64 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 1
  store i32 0, ptr %64, align 4
  %65 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 2
  store i32 0, ptr %65, align 4
  %66 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 3
  store i32 0, ptr %66, align 4
  %67 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 4
  store i32 0, ptr %67, align 4
  %68 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %69 = load ptr, ptr %68, align 8
  %70 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %69, i32 0, i32 1
  %71 = load ptr, ptr %70, align 8
  %rtPtr = alloca %Texture.0, align 8
  %72 = alloca ptr, align 8
  store ptr @4, ptr %72, align 8
  call void %71(ptr %rtPtr, ptr %72, ptr %0)
  %73 = load %Texture.0, ptr %rtPtr, align 4
  store %Texture.0 %73, ptr %birdTexture, align 4
  %74 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %76 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %77 = icmp eq i32 %76, 0
  br i1 %77, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %78 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 0
  %id = load i32, ptr %78, align 4
  %79 = icmp eq i32 %id, 0
  br i1 %79, label %then, label %else

checkContinueBlock6:                              ; preds = %afterIfElse
  %80 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %81 = icmp eq i32 %80, 0
  br i1 %81, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  br label %"while:conditon"

checkContinueBlock8:                              ; preds = %end_block94
  %82 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %83 = icmp eq i32 %82, 0
  br i1 %83, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %84 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %85 = load ptr, ptr %84, align 8
  %86 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %85, i32 0, i32 9
  %87 = load ptr, ptr %86, align 8
  call void %87(ptr %0)
  %88 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %89 = icmp eq i32 %88, 0
  br i1 %89, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %90 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %91 = icmp eq i32 %90, 0
  br i1 %91, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  br label %returnBlock95

checkContinueBlock12:                             ; preds = %mergeBlock96
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock5
  br label %nestedBlock14

else:                                             ; preds = %nestedBlock5
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock13
  %92 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %checkContinueBlock6, label %afterNestedBlock

afterNestedBlock13:                               ; preds = %checkContinueBlock21, %mergeBlock, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %afterIfElse25
  br label %afterIfElse

nestedBlock14:                                    ; preds = %then
  %94 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 0
  %id22 = load i32, ptr %94, align 4
  %95 = icmp eq i32 %id22, 0
  br i1 %95, label %then23, label %else24

checkContinueBlock15:                             ; preds = %afterIfElse25
  %96 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %97 = icmp eq i32 %96, 0
  br i1 %97, label %nestedBlock16, label %afterNestedBlock13

nestedBlock16:                                    ; preds = %checkContinueBlock15
  call void @UnloadTexture(ptr %birdTexture)
  %98 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %checkContinueBlock17, label %afterNestedBlock13

checkContinueBlock17:                             ; preds = %nestedBlock16
  %100 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %nestedBlock18, label %afterNestedBlock13

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %102 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %103 = load ptr, ptr %102, align 8
  %104 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %103, i32 0, i32 9
  %105 = load ptr, ptr %104, align 8
  call void %105(ptr %0)
  %106 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %checkContinueBlock19, label %afterNestedBlock13

checkContinueBlock19:                             ; preds = %nestedBlock18
  %108 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %nestedBlock20, label %afterNestedBlock13

nestedBlock20:                                    ; preds = %checkContinueBlock19
  br label %returnBlock

checkContinueBlock21:                             ; preds = %mergeBlock
  br label %afterNestedBlock13

then23:                                           ; preds = %nestedBlock14
  br label %nestedBlock27

else24:                                           ; preds = %nestedBlock14
  br label %afterIfElse25

afterIfElse25:                                    ; preds = %else24, %afterNestedBlock26
  %110 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %111 = icmp eq i32 %110, 0
  br i1 %111, label %checkContinueBlock15, label %afterNestedBlock13

afterNestedBlock26:                               ; preds = %checkContinueBlock28, %nestedBlock27
  br label %afterIfElse25

nestedBlock27:                                    ; preds = %then23
  %112 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %113 = load ptr, ptr %112, align 8
  %114 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %113, i32 0, i32 2
  %115 = load ptr, ptr %114, align 8
  %116 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  %117 = getelementptr inbounds %LOG_TYPE.1, ptr %116, i32 0, i32 5
  %ERROR = load i32, ptr %117, align 4
  %118 = alloca ptr, align 8
  store ptr @5, ptr %118, align 8
  call void %115(ptr %117, ptr %118, ptr %0)
  %119 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %120 = icmp eq i32 %119, 0
  br i1 %120, label %checkContinueBlock28, label %afterNestedBlock26

checkContinueBlock28:                             ; preds = %nestedBlock27
  br label %afterNestedBlock26

returnBlock:                                      ; preds = %nestedBlock20
  ret i32 1

mergeBlock:                                       ; No predecessors!
  %121 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %122 = icmp eq i32 %121, 0
  br i1 %122, label %checkContinueBlock21, label %afterNestedBlock13

"while:conditon":                                 ; preds = %afterNestedBlock29, %nestedBlock7
  %123 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %124 = icmp eq i32 %123, 0
  br i1 %124, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock30

while.end:                                        ; preds = %afterNestedBlock29, %end_block
  %125 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %126 = icmp eq i32 %125, 0
  br i1 %126, label %end_block94, label %decrement_block93

decrement_block:                                  ; preds = %"while:conditon"
  %127 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %128 = sub i32 %127, 1
  store i32 %128, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %129 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %130 = load ptr, ptr %129, align 8
  %131 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %130, i32 0, i32 13
  %132 = load ptr, ptr %131, align 8
  %133 = call i1 %132(ptr %0)
  %134 = xor i1 %133, true
  br i1 %134, label %"while:body", label %while.end

afterNestedBlock29:                               ; preds = %checkContinueBlock41, %nestedBlock40, %checkContinueBlock39, %FillExpr.exit91, %checkContinueBlock37, %nestedBlock36, %checkContinueBlock35, %nestedBlock34, %checkContinueBlock33, %afterIfElse46, %checkContinueBlock31, %nestedBlock30
  %135 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %136 = icmp eq i32 %135, 0
  br i1 %136, label %"while:conditon", label %while.end

nestedBlock30:                                    ; preds = %"while:body"
  %birdTimmer = load double, ptr @birdTimmer, align 8
  %birdTimmer42 = load double, ptr @birdTimmer, align 8
  %137 = call float @GetFrameTime()
  %138 = fpext float %137 to double
  %139 = fsub double %birdTimmer42, %138
  store double %139, ptr @birdTimmer, align 8
  %140 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %141 = icmp eq i32 %140, 0
  br i1 %141, label %checkContinueBlock31, label %afterNestedBlock29

checkContinueBlock31:                             ; preds = %nestedBlock30
  %142 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %143 = icmp eq i32 %142, 0
  br i1 %143, label %nestedBlock32, label %afterNestedBlock29

nestedBlock32:                                    ; preds = %checkContinueBlock31
  %birdTimmer43 = load double, ptr @birdTimmer, align 8
  %144 = fcmp olt double %birdTimmer43, 0.000000e+00
  br i1 %144, label %then44, label %else45

checkContinueBlock33:                             ; preds = %afterIfElse46
  %145 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %146 = icmp eq i32 %145, 0
  br i1 %146, label %nestedBlock34, label %afterNestedBlock29

nestedBlock34:                                    ; preds = %checkContinueBlock33
  %147 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %148 = load ptr, ptr %147, align 8
  %149 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %148, i32 0, i32 10
  %150 = load ptr, ptr %149, align 8
  call void %150(ptr %0)
  %151 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %152 = icmp eq i32 %151, 0
  br i1 %152, label %checkContinueBlock35, label %afterNestedBlock29

checkContinueBlock35:                             ; preds = %nestedBlock34
  %153 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %nestedBlock36, label %afterNestedBlock29

nestedBlock36:                                    ; preds = %checkContinueBlock35
  %155 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %156 = load ptr, ptr %155, align 8
  %157 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %156, i32 0, i32 16
  %158 = load ptr, ptr %157, align 8
  %159 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %160 = getelementptr inbounds %COLORS_TYPE.3, ptr %159, i32 0, i32 0
  %WHITE = load i32, ptr %160, align 4
  call void %158(ptr %160, ptr %0)
  %161 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %checkContinueBlock37, label %afterNestedBlock29

checkContinueBlock37:                             ; preds = %nestedBlock36
  %163 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %164 = icmp eq i32 %163, 0
  br i1 %164, label %nestedBlock38, label %afterNestedBlock29

nestedBlock38:                                    ; preds = %checkContinueBlock37
  %165 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %166 = load ptr, ptr %165, align 8
  %167 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %166, i32 0, i32 17
  %168 = load ptr, ptr %167, align 8
  %169 = alloca [4 x float], align 4
  %170 = alloca i32, align 4
  %171 = alloca i32, align 4
  store i32 0, ptr %171, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock39:                             ; preds = %FillExpr.exit91
  %172 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %173 = icmp eq i32 %172, 0
  br i1 %173, label %nestedBlock40, label %afterNestedBlock29

nestedBlock40:                                    ; preds = %checkContinueBlock39
  %174 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  %175 = load ptr, ptr %174, align 8
  %176 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %175, i32 0, i32 19
  %177 = load ptr, ptr %176, align 8
  call void %177(ptr %0)
  %178 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %179 = icmp eq i32 %178, 0
  br i1 %179, label %checkContinueBlock41, label %afterNestedBlock29

checkContinueBlock41:                             ; preds = %nestedBlock40
  br label %afterNestedBlock29

then44:                                           ; preds = %nestedBlock32
  br label %nestedBlock48

else45:                                           ; preds = %nestedBlock32
  br label %afterIfElse46

afterIfElse46:                                    ; preds = %else45, %afterNestedBlock47
  %180 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %181 = icmp eq i32 %180, 0
  br i1 %181, label %checkContinueBlock33, label %afterNestedBlock29

afterNestedBlock47:                               ; preds = %checkContinueBlock53, %afterIfElse57, %checkContinueBlock51, %nestedBlock50, %checkContinueBlock49, %nestedBlock48
  br label %afterIfElse46

nestedBlock48:                                    ; preds = %then44
  %birdTimmer54 = load double, ptr @birdTimmer, align 8
  %BIRD_TIMMER = load double, ptr @BIRD_TIMMER, align 8
  %182 = load double, ptr @BIRD_TIMMER, align 8
  store double %182, ptr @birdTimmer, align 8
  %183 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %184 = icmp eq i32 %183, 0
  br i1 %184, label %checkContinueBlock49, label %afterNestedBlock47

checkContinueBlock49:                             ; preds = %nestedBlock48
  %185 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %nestedBlock50, label %afterNestedBlock47

nestedBlock50:                                    ; preds = %checkContinueBlock49
  %187 = load i32, ptr @birdSpriteIndex, align 4
  %188 = load i32, ptr @birdSpriteIndex, align 4
  %189 = add i32 %188, 1
  store i32 %189, ptr @birdSpriteIndex, align 4
  %190 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %191 = icmp eq i32 %190, 0
  br i1 %191, label %checkContinueBlock51, label %afterNestedBlock47

checkContinueBlock51:                             ; preds = %nestedBlock50
  %192 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %193 = icmp eq i32 %192, 0
  br i1 %193, label %nestedBlock52, label %afterNestedBlock47

nestedBlock52:                                    ; preds = %checkContinueBlock51
  %194 = load i32, ptr @birdSpriteIndex, align 4
  %195 = load i32, ptr @BIRD_SPRITE_SIZE, align 4
  %196 = icmp sge i32 %194, %195
  br i1 %196, label %then55, label %else56

checkContinueBlock53:                             ; preds = %afterIfElse57
  br label %afterNestedBlock47

then55:                                           ; preds = %nestedBlock52
  br label %nestedBlock59

else56:                                           ; preds = %nestedBlock52
  br label %afterIfElse57

afterIfElse57:                                    ; preds = %else56, %afterNestedBlock58
  %197 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %198 = icmp eq i32 %197, 0
  br i1 %198, label %checkContinueBlock53, label %afterNestedBlock47

afterNestedBlock58:                               ; preds = %checkContinueBlock60, %nestedBlock59
  br label %afterIfElse57

nestedBlock59:                                    ; preds = %then55
  %199 = load i32, ptr @birdSpriteIndex, align 4
  store i32 0, ptr @birdSpriteIndex, align 4
  %200 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %201 = icmp eq i32 %200, 0
  br i1 %201, label %checkContinueBlock60, label %afterNestedBlock58

checkContinueBlock60:                             ; preds = %nestedBlock59
  br label %afterNestedBlock58

FillExpr.loopStart-0:                             ; preds = %nestedBlock38
  store i32 0, ptr %170, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %202 = load i32, ptr %170, align 4
  %203 = icmp slt i32 %202, 4
  %204 = load i32, ptr %171, align 4
  %205 = icmp slt i32 %204, 4
  %206 = and i1 %203, %205
  br i1 %206, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %207 = load i32, ptr %170, align 4
  %208 = getelementptr [4 x float], ptr %169, i32 0, i32 %207
  store float 0.000000e+00, ptr %208, align 4
  %209 = load i32, ptr %170, align 4
  %210 = add i32 %209, 1
  store i32 %210, ptr %170, align 4
  %211 = load i32, ptr %171, align 4
  %212 = add i32 %211, 1
  store i32 %212, ptr %171, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %213 = getelementptr [4 x float], ptr %169, i32 0, i32 0
  %214 = load i32, ptr @birdSpriteIndex, align 4
  %birdSpritePosition = load [9 x %Position.4], ptr @birdSpritePosition, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %214, 9
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %214, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

"GlobalIndexExpr::then":                          ; preds = %FillExpr.exit
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %FillExpr.exit
  call void @raise_exception(ptr @6)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %215 = getelementptr [9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 %214
  %216 = getelementptr inbounds %Position.4, ptr %215, i32 0, i32 0
  %x = load float, ptr %216, align 4
  %217 = load float, ptr %216, align 4
  store float %217, ptr %213, align 4
  %218 = getelementptr [4 x float], ptr %169, i32 0, i32 1
  %219 = load i32, ptr @birdSpriteIndex, align 4
  %birdSpritePosition61 = load [9 x %Position.4], ptr @birdSpritePosition, align 4
  %"GlobalIndexExpr::isLessThan65" = icmp slt i32 %219, 9
  %"GlobalIndexExpr::isGreaterThan66" = icmp sge i32 %219, 0
  %"GlobalIndexExpr::isWithinBounds67" = and i1 %"GlobalIndexExpr::isLessThan65", %"GlobalIndexExpr::isGreaterThan66"
  br i1 %"GlobalIndexExpr::isWithinBounds67", label %"GlobalIndexExpr::then62", label %"GlobalIndexExpr::else63"

"GlobalIndexExpr::then62":                        ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge64"

"GlobalIndexExpr::else63":                        ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge64"

"GlobalIndexExpr::merge64":                       ; preds = %"GlobalIndexExpr::else63", %"GlobalIndexExpr::then62"
  %220 = getelementptr [9 x %Position.4], ptr @birdSpritePosition, i32 0, i32 %219
  %221 = getelementptr inbounds %Position.4, ptr %220, i32 0, i32 1
  %y = load float, ptr %221, align 4
  %222 = load float, ptr %221, align 4
  store float %222, ptr %218, align 4
  %223 = getelementptr [4 x float], ptr %169, i32 0, i32 2
  %ACTUAL_BIRD_SIZE = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %224 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  store float %224, ptr %223, align 4
  %225 = getelementptr [4 x float], ptr %169, i32 0, i32 3
  %ACTUAL_BIRD_SIZE68 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  %226 = load float, ptr @ACTUAL_BIRD_SIZE, align 4
  store float %226, ptr %225, align 4
  %227 = alloca [4 x float], align 4
  %228 = alloca i32, align 4
  %229 = alloca i32, align 4
  store i32 0, ptr %229, align 4
  br label %FillExpr.loopStart-069

FillExpr.loopStart-069:                           ; preds = %"GlobalIndexExpr::merge64"
  store i32 0, ptr %228, align 4
  br label %FillExpr.loopCmp-070

FillExpr.loopCmp-070:                             ; preds = %FillExpr.loopBody-071, %FillExpr.loopStart-069
  %230 = load i32, ptr %228, align 4
  %231 = icmp slt i32 %230, 4
  %232 = load i32, ptr %229, align 4
  %233 = icmp slt i32 %232, 4
  %234 = and i1 %231, %233
  br i1 %234, label %FillExpr.loopBody-071, label %FillExpr.loopEnd-072

FillExpr.loopBody-071:                            ; preds = %FillExpr.loopCmp-070
  %235 = load i32, ptr %228, align 4
  %236 = getelementptr [4 x float], ptr %227, i32 0, i32 %235
  store float 0.000000e+00, ptr %236, align 4
  %237 = load i32, ptr %228, align 4
  %238 = add i32 %237, 1
  store i32 %238, ptr %228, align 4
  %239 = load i32, ptr %229, align 4
  %240 = add i32 %239, 1
  store i32 %240, ptr %229, align 4
  br label %FillExpr.loopCmp-070

FillExpr.loopEnd-072:                             ; preds = %FillExpr.loopCmp-070
  br label %FillExpr.exit73

FillExpr.exit73:                                  ; preds = %FillExpr.loopEnd-072
  %241 = getelementptr [4 x float], ptr %227, i32 0, i32 0
  %screenWidth74 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if, label %else75

if:                                               ; preds = %FillExpr.exit73
  call void @raise_exception(ptr @8)
  br label %merge

else75:                                           ; preds = %FillExpr.exit73
  %242 = sitofp i32 %screenWidth74 to double
  %243 = fdiv double %242, 3.000000e+00
  br label %merge

merge:                                            ; preds = %else75, %if
  %birdSize = load float, ptr @birdSize, align 4
  br i1 false, label %if76, label %else77

if76:                                             ; preds = %merge
  call void @raise_exception(ptr @9)
  br label %else77

else77:                                           ; preds = %if76, %merge
  %244 = fdiv float %birdSize, 2.000000e+00
  %245 = fptrunc double %243 to float
  %246 = fsub float %245, %244
  store float %246, ptr %241, align 4
  %247 = getelementptr [4 x float], ptr %227, i32 0, i32 1
  %screenHeight78 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if79, label %else80

if79:                                             ; preds = %else77
  call void @raise_exception(ptr @10)
  br label %merge81

else80:                                           ; preds = %else77
  %248 = sitofp i32 %screenHeight78 to double
  %249 = fdiv double %248, 2.000000e+00
  br label %merge81

merge81:                                          ; preds = %else80, %if79
  %birdSize82 = load float, ptr @birdSize, align 4
  br i1 false, label %if83, label %else84

if83:                                             ; preds = %merge81
  call void @raise_exception(ptr @11)
  br label %else84

else84:                                           ; preds = %if83, %merge81
  %250 = fdiv float %birdSize82, 2.000000e+00
  %251 = fptrunc double %249 to float
  %252 = fsub float %251, %250
  store float %252, ptr %247, align 4
  %253 = getelementptr [4 x float], ptr %227, i32 0, i32 2
  %birdSize85 = load float, ptr @birdSize, align 4
  %254 = load float, ptr @birdSize, align 4
  store float %254, ptr %253, align 4
  %255 = getelementptr [4 x float], ptr %227, i32 0, i32 3
  %birdSize86 = load float, ptr @birdSize, align 4
  %256 = load float, ptr @birdSize, align 4
  store float %256, ptr %255, align 4
  %257 = alloca [2 x float], align 4
  %258 = alloca i32, align 4
  %259 = alloca i32, align 4
  store i32 0, ptr %259, align 4
  br label %FillExpr.loopStart-087

FillExpr.loopStart-087:                           ; preds = %else84
  store i32 0, ptr %258, align 4
  br label %FillExpr.loopCmp-088

FillExpr.loopCmp-088:                             ; preds = %FillExpr.loopBody-089, %FillExpr.loopStart-087
  %260 = load i32, ptr %258, align 4
  %261 = icmp slt i32 %260, 2
  %262 = load i32, ptr %259, align 4
  %263 = icmp slt i32 %262, 2
  %264 = and i1 %261, %263
  br i1 %264, label %FillExpr.loopBody-089, label %FillExpr.loopEnd-090

FillExpr.loopBody-089:                            ; preds = %FillExpr.loopCmp-088
  %265 = load i32, ptr %258, align 4
  %266 = getelementptr [2 x float], ptr %257, i32 0, i32 %265
  store float 0.000000e+00, ptr %266, align 4
  %267 = load i32, ptr %258, align 4
  %268 = add i32 %267, 1
  store i32 %268, ptr %258, align 4
  %269 = load i32, ptr %259, align 4
  %270 = add i32 %269, 1
  store i32 %270, ptr %259, align 4
  br label %FillExpr.loopCmp-088

FillExpr.loopEnd-090:                             ; preds = %FillExpr.loopCmp-088
  br label %FillExpr.exit91

FillExpr.exit91:                                  ; preds = %FillExpr.loopEnd-090
  %271 = getelementptr [2 x float], ptr %257, i32 0, i32 0
  store float 0.000000e+00, ptr %271, align 4
  %272 = getelementptr [2 x float], ptr %257, i32 0, i32 1
  store float 0.000000e+00, ptr %272, align 4
  %273 = alloca float, align 4
  store float 0.000000e+00, ptr %273, align 4
  %274 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %275 = getelementptr inbounds %COLORS_TYPE.3, ptr %274, i32 0, i32 0
  %WHITE92 = load i32, ptr %275, align 4
  call void %168(ptr %birdTexture, ptr %169, ptr %227, ptr %257, ptr %273, ptr %275, ptr %0)
  %276 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %277 = icmp eq i32 %276, 0
  br i1 %277, label %checkContinueBlock39, label %afterNestedBlock29

decrement_block93:                                ; preds = %while.end
  %278 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %279 = sub i32 %278, 1
  store i32 %279, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block94

end_block94:                                      ; preds = %decrement_block93, %while.end
  %280 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %281 = icmp eq i32 %280, 0
  br i1 %281, label %checkContinueBlock8, label %afterNestedBlock

returnBlock95:                                    ; preds = %nestedBlock11
  ret i32 0

mergeBlock96:                                     ; No predecessors!
  %282 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %283 = icmp eq i32 %282, 0
  br i1 %283, label %checkContinueBlock12, label %afterNestedBlock
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
!11 = !{!"FlowWingAnim.getScreenHeight:rt:pr:28"}
!12 = !{!"FlowWingAnim.getScreenWidth:rt:pr:28"}
!13 = !{!"FlowWingAnim.drawCircle:rt:pr:27"}
!14 = !{!"FlowWingAnim.drawText:rt:pr:27"}
!15 = !{!"FlowWingAnim.drawTexture:rt:pr:27"}
!16 = !{!"FlowWingAnim.drawTexturePro:rt:pr:27"}
!17 = !{!"FlowWingAnim.traceLog:rt:pr:27"}
!18 = !{!"FlowWingAnim.loadTexture:rt:ob:Texture"}
!19 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!20 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!21 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!22 = !{!"SetTargetFPS:rt:pr:27"}
!23 = !{!"LoadTexture:rt:ob:Texture"}
!24 = !{!"getRandomNumber:rt:pr:28"}
!25 = !{!"ClearBackground:rt:pr:27"}
!26 = !{!"TraceLog:rt:pr:27"}
!27 = !{!"GetScreenWidth:rt:pr:28"}
!28 = !{!"DrawCircle:rt:pr:27"}
!29 = !{!"time:rt:pr:28"}
!30 = !{!"BeginDrawing:rt:pr:27"}
!31 = !{!"IsKeyPressed:rt:pr:34"}
!32 = !{!"WindowShouldClose:rt:pr:34"}
!33 = !{!"InitWindow:rt:pr:27"}
!34 = !{!"EndDrawing:rt:pr:27"}
!35 = !{!"CloseWindow:rt:pr:27"}
!36 = !{!"GetScreenHeight:rt:pr:28"}
!37 = !{!"GetFrameTime:rt:pr:32"}
!38 = !{!"DrawText:rt:pr:27"}
!39 = !{!"GetTime:rt:pr:31"}
!40 = !{!"UnloadTexture:rt:pr:27"}
!41 = !{!"TextFormat:rt:pr:33"}
!42 = !{!"IsKeyDown:rt:pr:34"}
!43 = !{!"DrawRectangle:rt:pr:27"}
!44 = !{!"DrawTexture:rt:pr:27"}
!45 = !{!"srand:rt:pr:27"}
!46 = !{!"DrawTexturePro:rt:pr:27"}
!47 = !{!"rand:rt:pr:28"}
!48 = !{!"main:rt:pr:28"}
