; ModuleID = 'flowmain'
source_filename = "flowmain"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Err::Result::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"GameUnit::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"WideMountain::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"HeightedMountain::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"GreenMountain::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"BlackMountain::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"Bird::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Cloud::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"Ground::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr }
%"GameContext::VTableType" = type { ptr, ptr, ptr }
%"Screen::VTableType" = type { ptr, ptr }
%"MenuScreen::VTableType" = type { ptr, ptr, ptr, ptr }
%"GameScreen::VTableType" = type { ptr, ptr, ptr }
%"PauseScreen::VTableType" = type { ptr, ptr, ptr }
%"TextureManager::VTableType" = type { ptr, ptr }
%"BirdGame::VTableType" = type { ptr, ptr, ptr, ptr }
%"Err::ErrorCode.8" = type { i32, i32, i32 }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
%GameScreenType.10 = type { i32, i32, i32, i32 }
%Texture.9 = type { i32, i32, i32, i32, i32 }
%Position.7 = type { float, float }
%AttributeType.11 = type { [4 x float], [4 x float], [2 x float], float }
%OPTIONS_TYPE.12 = type { i32, i32 }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.4, %KEYS_TYPE.3, %LOG_TYPE.5 }
%COLORS_TYPE.4 = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%KEYS_TYPE.3 = type { i32, i32, i32, i32, i32, i32, i32 }
%LOG_TYPE.5 = type { i32, i32, i32, i32, i32, i32, i32, i32 }
%GameUnit = type { ptr, %Texture.9, %Position.7 }
%WideMountain = type { ptr, %Texture.9, %Position.7, %Position.7, %Position.7 }
%HeightedMountain = type { ptr, %Texture.9, %Position.7 }
%GreenMountain = type { ptr, %Texture.9, %Position.7 }
%BlackMountain = type { ptr, %Texture.9, %Position.7 }
%Bird = type { ptr, %Texture.9, %Position.7, float, float, double, double, i32, i32, i1, [9 x %Position.7] }
%Cloud = type { ptr, %Texture.9, %Position.7, [5 x %AttributeType.11] }
%Ground = type { ptr, %Texture.9, %Position.7, %Texture.9 }
%GameContext = type { ptr, %Bird, %Cloud, %Ground, %WideMountain, %HeightedMountain, %GreenMountain, %BlackMountain, i32, i32 }
%Screen = type { ptr, %GameContext }
%MenuScreen = type { ptr, %GameContext, ptr, ptr, %OPTIONS_TYPE.12, i32, double, float, i32, i32, i32, float, float, i32, i32 }
%GameScreen = type { ptr, %GameContext, ptr }
%BoxWithText.6 = type { ptr, i32, i32, i32, i32, i32, i32, i32, i32 }
%PauseScreen = type { ptr, %GameContext }
%TextureManager = type { ptr, %Texture.9, %Texture.9, %Texture.9, %Texture.9, %Texture.9, %Texture.9, %Texture.9, %Texture.9, %Texture.9 }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%"Err::Result" = type { ptr, ptr, i32, ptr }
%BirdGame = type { ptr, %TextureManager, %GameContext, %MenuScreen, %GameScreen, %PauseScreen }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.FlowWingAnim.fg = common global %"FlowWingAnim::VTableType" zeroinitializer
@"vtable.Err::Result.fg" = common global %"Err::Result::VTableType" zeroinitializer
@vtable.GameUnit.fg = common global %"GameUnit::VTableType" zeroinitializer
@vtable.WideMountain.fg = common global %"WideMountain::VTableType" zeroinitializer
@vtable.HeightedMountain.fg = common global %"HeightedMountain::VTableType" zeroinitializer
@vtable.GreenMountain.fg = common global %"GreenMountain::VTableType" zeroinitializer
@vtable.BlackMountain.fg = common global %"BlackMountain::VTableType" zeroinitializer
@vtable.Bird.fg = common global %"Bird::VTableType" zeroinitializer
@vtable.Cloud.fg = common global %"Cloud::VTableType" zeroinitializer
@vtable.Ground.fg = common global %"Ground::VTableType" zeroinitializer
@vtable.GameContext.fg = common global %"GameContext::VTableType" zeroinitializer
@vtable.Screen.fg = common global %"Screen::VTableType" zeroinitializer
@vtable.MenuScreen.fg = common global %"MenuScreen::VTableType" zeroinitializer
@vtable.GameScreen.fg = common global %"GameScreen::VTableType" zeroinitializer
@vtable.PauseScreen.fg = common global %"PauseScreen::VTableType" zeroinitializer
@vtable.TextureManager.fg = common global %"TextureManager::VTableType" zeroinitializer
@vtable.BirdGame.fg = common global %"BirdGame::VTableType" zeroinitializer
@"Err::CODE" = common local_unnamed_addr global %"Err::ErrorCode.8" zeroinitializer
@"Err::x" = common local_unnamed_addr global [2 x %"Err::ErrorCode.8"] zeroinitializer
@screenWidth = common local_unnamed_addr global i32 0
@screenHeight = common local_unnamed_addr global i32 0
@FPS = common local_unnamed_addr global i32 0
@side = common local_unnamed_addr global i32 0
@fgAnim = common local_unnamed_addr global ptr null
@GAME_SPEED = common local_unnamed_addr global %DynamicType zeroinitializer
@GAME_SCREEN = common local_unnamed_addr global %GameScreenType.10 zeroinitializer
@NORMAL_COLOR = common local_unnamed_addr global i32 0
@HOVER_COLOR = common local_unnamed_addr global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private local_unnamed_addr global [23 x i8] c"snake-game-in-flowwing\00"
@7 = private unnamed_addr constant [729 x i8] c"\0A\1B[33m248| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m249| \1B[0m\1B[0m\0A\1B[0m\1B[33m250| \1B[0m\1B[0m\0A\1B[0m\1B[33m251| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m252| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m253| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m254| \1B[0m\1B[0m\0A\1B[0m\1B[33m255| \1B[0m\1B[0m\0A\1B[0m\1B[33m256| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 252:32\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@8 = private unnamed_addr constant [807 x i8] c"\0A\1B[33m248| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m249| \1B[0m\1B[0m\0A\1B[0m\1B[33m250| \1B[0m\1B[0m\0A\1B[0m\1B[33m251| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m252| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m253| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m254| \1B[0m\1B[0m\0A\1B[0m\1B[33m255| \1B[0m\1B[0m\0A\1B[0m\1B[33m256| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 252:71\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [840 x i8] c"\0A\1B[33m319| \1B[0m\1B[0m\0A\1B[0m\1B[33m320| \1B[0m\1B[0m\0A\1B[0m\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 323:14\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [854 x i8] c"\0A\1B[33m319| \1B[0m\1B[0m\0A\1B[0m\1B[33m320| \1B[0m\1B[0m\0A\1B[0m\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[32m\1B[1m                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 323:24\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [884 x i8] c"\0A\1B[33m319| \1B[0m\1B[0m\0A\1B[0m\1B[33m320| \1B[0m\1B[0m\0A\1B[0m\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[32m\1B[1m                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 323:36\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [898 x i8] c"\0A\1B[33m319| \1B[0m\1B[0m\0A\1B[0m\1B[33m320| \1B[0m\1B[0m\0A\1B[0m\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 323:46\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [851 x i8] c"\0A\1B[33m320| \1B[0m\1B[0m\0A\1B[0m\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[33m324| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                 \0A   ~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m328| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 324:17\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [865 x i8] c"\0A\1B[33m320| \1B[0m\1B[0m\0A\1B[0m\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[33m324| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                           \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m328| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 324:27\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [852 x i8] c"\0A\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m328| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m329| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 325:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@16 = private unnamed_addr constant [866 x i8] c"\0A\1B[33m321| \1B[0m\1B[0m  update() -> nthg {\0A\1B[0m\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m326| \1B[0m\1B[0m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m328| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m329| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 325:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@17 = private unnamed_addr constant [832 x i8] c"\0A\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m328| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m329| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m330| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 326:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@18 = private unnamed_addr constant [846 x i8] c"\0A\1B[33m322| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m323| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + fgAnim.getFrameTime() * ((10))\0A\1B[0m\1B[33m324| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m325| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m326| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1] = -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m327| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m328| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m329| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m330| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 326:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@19 = private unnamed_addr constant [737 x i8] c"\0A\1B[33m330| \1B[0m\1B[0m\0A\1B[0m\1B[33m331| \1B[0m\1B[0m\0A\1B[0m\1B[33m332| \1B[0m\1B[0m  draw() -> nthg {\0A\1B[0m\1B[33m333| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m334| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(texture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m335| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m336| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m337| \1B[0m\1B[0m\0A\1B[0m\1B[33m338| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 334:45\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@20 = private unnamed_addr constant [773 x i8] c"\0A\1B[33m330| \1B[0m\1B[0m\0A\1B[0m\1B[33m331| \1B[0m\1B[0m\0A\1B[0m\1B[33m332| \1B[0m\1B[0m  draw() -> nthg {\0A\1B[0m\1B[33m333| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m334| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(texture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                               \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m335| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m336| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m337| \1B[0m\1B[0m\0A\1B[0m\1B[33m338| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 334:63\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@21 = private unnamed_addr constant [819 x i8] c"\0A\1B[33m330| \1B[0m\1B[0m\0A\1B[0m\1B[33m331| \1B[0m\1B[0m\0A\1B[0m\1B[33m332| \1B[0m\1B[0m  draw() -> nthg {\0A\1B[0m\1B[33m333| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m334| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(texture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                      \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m335| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m336| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m337| \1B[0m\1B[0m\0A\1B[0m\1B[33m338| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 334:86\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@22 = private unnamed_addr constant [856 x i8] c"\0A\1B[33m330| \1B[0m\1B[0m\0A\1B[0m\1B[33m331| \1B[0m\1B[0m\0A\1B[0m\1B[33m332| \1B[0m\1B[0m  draw() -> nthg {\0A\1B[0m\1B[33m333| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m334| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(texture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m335| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m336| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m337| \1B[0m\1B[0m\0A\1B[0m\1B[33m338| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 334:104\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@23 = private local_unnamed_addr global [21 x i8] c"Press ENTER to Start\00"
@24 = private local_unnamed_addr global [18 x i8] c"Press ESC to Exit\00"
@25 = private local_unnamed_addr global [10 x i8] c"MAIN MENU\00"
@26 = private local_unnamed_addr global [10 x i8] c"MAIN MENU\00"
@27 = private local_unnamed_addr global [27 x i8] c"Use arrow keys to navigate\00"
@28 = private local_unnamed_addr global [27 x i8] c"Use arrow keys to navigate\00"
@29 = private local_unnamed_addr global [27 x i8] c"Press ESC to exit the game\00"
@30 = private local_unnamed_addr global [27 x i8] c"Press ESC to exit the game\00"
@31 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@32 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@33 = private local_unnamed_addr global [7 x i8] c"Score \00"
@34 = private local_unnamed_addr global [12 x i8] c"Game Paused\00"
@35 = private local_unnamed_addr global [12 x i8] c"Game Paused\00"
@36 = private local_unnamed_addr global [22 x i8] c"Press SPACE to resume\00"
@37 = private local_unnamed_addr global [22 x i8] c"Press SPACE to resume\00"
@38 = private local_unnamed_addr global [27 x i8] c"Press ESC to exit the game\00"
@39 = private local_unnamed_addr global [27 x i8] c"Press ESC to exit the game\00"
@40 = private local_unnamed_addr global [27 x i8] c"./assets/skyBackground.png\00"
@41 = private local_unnamed_addr global [20 x i8] c"./assets/ground.png\00"
@42 = private local_unnamed_addr global [31 x i8] c"./assets/mountain/1mountL1.png\00"
@43 = private local_unnamed_addr global [31 x i8] c"./assets/mountain/1mountL2.png\00"
@44 = private local_unnamed_addr global [31 x i8] c"./assets/mountain/2mountL2.png\00"
@45 = private local_unnamed_addr global [31 x i8] c"./assets/mountain/1mountL3.png\00"
@46 = private local_unnamed_addr global [19 x i8] c"./assets/wood1.png\00"
@47 = private local_unnamed_addr global [18 x i8] c"./assets/bird.png\00"
@48 = private local_unnamed_addr global [21 x i8] c"./assets/3clouds.png\00"
@49 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@50 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@51 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@52 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@53 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@54 = private local_unnamed_addr global [28 x i8] c"Failed to load all textures\00"
@55 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@56 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@57 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@58 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@59 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@60 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@61 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@62 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@63 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@64 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@65 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@66 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@67 = private local_unnamed_addr global [21 x i8] c"Press ENTER to Start\00"
@68 = private local_unnamed_addr global [18 x i8] c"Press ESC to Exit\00"
@69 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@70 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@71 = private local_unnamed_addr global [21 x i8] c"Press SPACE to pause\00"
@72 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@73 = private local_unnamed_addr global [25 x i8] c"Error loading textures: \00"
@74 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @74
@75 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@76 = private local_unnamed_addr global [26 x i8] c"Error initializing game: \00"
@77 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @77

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

define i32 @flowmain(i32 %0, ptr %1) {
entry:
  call void @"assign_<Object<Err::ErrorCode.8>"(ptr @"Err::CODE")
  call void @"assign_<Array[2]<Object<Err::ErrorCode.8>>:2,"(ptr @"Err::x")
  store i32 0, ptr @screenWidth, align 4
  store i32 0, ptr @screenHeight, align 4
  store i32 0, ptr @FPS, align 4
  store i32 0, ptr @side, align 4
  call void @"assign_<Object<Err::ErrorCode.8>"(ptr @"Err::CODE")
  call void @"assign_<Array[2]<Object<Err::ErrorCode.8>>:2,"(ptr @"Err::x")
  %2 = alloca ptr, align 8
  call void @"assign_<Object<GameScreenType.10>"(ptr @GAME_SCREEN)
  %texture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %texture)
  %origin = alloca %Position.7, align 8
  call void @"assign_<Object<Position.7>"(ptr %origin)
  %firstMountPos = alloca %Position.7, align 8
  call void @"assign_<Object<Position.7>"(ptr %firstMountPos)
  %secondMountPos = alloca %Position.7, align 8
  call void @"assign_<Object<Position.7>"(ptr %secondMountPos)
  %ACTUAL_BIRD_SIZE = alloca float, align 4
  store float 0.000000e+00, ptr %ACTUAL_BIRD_SIZE, align 4
  %birdSize = alloca float, align 4
  store float 0.000000e+00, ptr %birdSize, align 4
  %BIRD_TIMMER = alloca double, align 8
  store double 0.000000e+00, ptr %BIRD_TIMMER, align 8
  %birdTimmer = alloca double, align 8
  store double 0.000000e+00, ptr %birdTimmer, align 8
  %BIRD_SPRITE_SIZE = alloca i32, align 4
  store i32 0, ptr %BIRD_SPRITE_SIZE, align 4
  %birdSpriteIndex = alloca i32, align 4
  store i32 0, ptr %birdSpriteIndex, align 4
  %isBirdAlive = alloca i1, align 1
  store i1 false, ptr %isBirdAlive, align 1
  %birdSpritePosition = alloca [9 x %Position.7], align 8
  call void @"assign_<Array[9]<Object<Position.7>>:9,"(ptr %birdSpritePosition)
  %clouds = alloca [5 x %AttributeType.11], align 8
  call void @"assign_<Array[5]<Object<AttributeType.11>>:5,"(ptr %clouds)
  %woodTexture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %woodTexture)
  %bird = alloca ptr, align 8
  %cloud = alloca ptr, align 8
  %ground = alloca ptr, align 8
  %wideMountain = alloca ptr, align 8
  %heightedMountain = alloca ptr, align 8
  %greenMountain = alloca ptr, align 8
  %blackMountain = alloca ptr, align 8
  %currentGameScreen = alloca i32, align 4
  store i32 0, ptr %currentGameScreen, align 4
  %gameScore = alloca i32, align 4
  store i32 0, ptr %gameScore, align 4
  store i32 0, ptr @NORMAL_COLOR, align 4
  store i32 0, ptr @HOVER_COLOR, align 4
  %gameCtx = alloca ptr, align 8
  %START_TEXT = alloca ptr, align 8
  store ptr @0, ptr %START_TEXT, align 8
  %EXIT_TEXT = alloca ptr, align 8
  store ptr @1, ptr %EXIT_TEXT, align 8
  %OPTIONS = alloca %OPTIONS_TYPE.12, align 8
  call void @"assign_<Object<OPTIONS_TYPE.12>"(ptr %OPTIONS)
  %OPTION_HEIGHT = alloca i32, align 4
  store i32 0, ptr %OPTION_HEIGHT, align 4
  %timeValue = alloca double, align 8
  store double 0.000000e+00, ptr %timeValue, align 8
  %glowOffset = alloca float, align 4
  store float 0.000000e+00, ptr %glowOffset, align 4
  %startY = alloca i32, align 4
  store i32 0, ptr %startY, align 4
  %startColor = alloca i32, align 4
  store i32 0, ptr %startColor, align 4
  %exitColor = alloca i32, align 4
  store i32 0, ptr %exitColor, align 4
  %glowOffsetForStartText = alloca float, align 4
  store float 0.000000e+00, ptr %glowOffsetForStartText, align 4
  %glowOffsetForExitText = alloca float, align 4
  store float 0.000000e+00, ptr %glowOffsetForExitText, align 4
  %padding = alloca i32, align 4
  store i32 0, ptr %padding, align 4
  %selectedOption = alloca i32, align 4
  store i32 0, ptr %selectedOption, align 4
  %PAUSE_TEXT = alloca ptr, align 8
  store ptr @2, ptr %PAUSE_TEXT, align 8
  %backgroundTexture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %backgroundTexture)
  %groundTexture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %groundTexture)
  %mountL1Texture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %mountL1Texture)
  %mountL2Texture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %mountL2Texture)
  %mount2L2Texture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %mount2L2Texture)
  %mount1L3Texture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %mount1L3Texture)
  %wood1Texture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %wood1Texture)
  %birdTexture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %birdTexture)
  %cloudTexture = alloca %Texture.9, align 8
  call void @"assign_<Object<Texture.9>"(ptr %cloudTexture)
  %textureManager = alloca ptr, align 8
  %gameCtx1 = alloca ptr, align 8
  %menuScreen = alloca ptr, align 8
  %gameScreen = alloca ptr, align 8
  %pauseScreen = alloca ptr, align 8
  %rtPtr = alloca i32, align 4
  %3 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim()
  %4 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random()
  store i32 1024, ptr @screenWidth, align 4
  store i32 500, ptr @screenHeight, align 4
  store i32 120, ptr @FPS, align 4
  store i32 10, ptr @side, align 4
  %5 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-..-..-..-lib-mac-silicon-lib-modules-Err-module()
  %6 = call ptr @malloc(i64 136)
  call void @"assign_<Class<FlowWingAnim>>"(ptr %6)
  %7 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %7, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 28
  store ptr @FlowWingAnim.closeWindow, ptr %9, align 8
  %10 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 26
  store ptr @FlowWingAnim.setTargetFPS, ptr %10, align 8
  %11 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 25
  store ptr @FlowWingAnim.createWindow, ptr %11, align 8
  %12 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 23
  store ptr @FlowWingAnim.beforeInit, ptr %12, align 8
  %13 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 19
  store ptr @FlowWingAnim.getMousePosition, ptr %13, align 8
  %14 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 22
  store ptr @FlowWingAnim.windowShouldClose, ptr %14, align 8
  %15 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 18
  store ptr @FlowWingAnim.drawRectangleLines, ptr %15, align 8
  %16 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 15
  store ptr @FlowWingAnim.drawRectangleLinesEx, ptr %16, align 8
  %17 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 14
  store ptr @FlowWingAnim.endDrawing, ptr %17, align 8
  %18 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 7
  store ptr @FlowWingAnim.getScreenWidth, ptr %18, align 8
  %19 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 9
  store ptr @FlowWingAnim.getScreenHeight, ptr %19, align 8
  %20 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 13
  store ptr @FlowWingAnim.getTime, ptr %20, align 8
  %21 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 12
  store ptr @FlowWingAnim.clearBackground, ptr %21, align 8
  %22 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 11
  store ptr @FlowWingAnim.getFrameTime, ptr %22, align 8
  %23 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 10
  store ptr @FlowWingAnim.drawTexture, ptr %23, align 8
  %24 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 6
  store ptr @FlowWingAnim.isKeyDown, ptr %24, align 8
  %25 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 27
  store ptr @FlowWingAnim.textFormat, ptr %25, align 8
  %26 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 20
  store ptr @FlowWingAnim.getColor, ptr %26, align 8
  %27 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %27, align 8
  %28 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 2
  store ptr @FlowWingAnim.loadTexture, ptr %28, align 8
  %29 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 1
  store ptr @FlowWingAnim.unloadTexture, ptr %29, align 8
  %30 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 3
  store ptr @FlowWingAnim.traceLog, ptr %30, align 8
  %31 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 4
  store ptr @FlowWingAnim.drawText, ptr %31, align 8
  %32 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 8
  store ptr @FlowWingAnim.measureText, ptr %32, align 8
  %33 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 21
  store ptr @FlowWingAnim.drawBoxWithText, ptr %33, align 8
  %34 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 24
  store ptr @FlowWingAnim.drawTexturePro, ptr %34, align 8
  %35 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 5
  store ptr @FlowWingAnim.drawCircle, ptr %35, align 8
  %36 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 17
  store ptr @FlowWingAnim.drawRectangle, ptr %36, align 8
  %37 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %8, i32 0, i32 16
  store ptr @FlowWingAnim.beginDrawing, ptr %37, align 8
  %38 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 1
  store i32 0, ptr %38, align 4
  %39 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 2
  store i32 0, ptr %39, align 4
  %40 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 3
  store ptr @5, ptr %40, align 8
  %41 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 4
  store i32 0, ptr %41, align 4
  %42 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 5
  call void @"assign_<Object<COLORS_TYPE.4>"(ptr %42)
  %43 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 6
  call void @"assign_<Object<KEYS_TYPE.3>"(ptr %43)
  %44 = getelementptr inbounds %FlowWingAnim, ptr %6, i32 0, i32 7
  call void @"assign_<Object<LOG_TYPE.5>"(ptr %44)
  store ptr %6, ptr @fgAnim, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  store ptr @6, ptr %2, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %2, ptr @FPS, ptr @fgAnim)
  store i32 100, ptr @GAME_SPEED, align 4
  store i32 0, ptr @GAME_SCREEN, align 4
  store i32 1, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  store i32 2, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), align 4
  store i32 3, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), align 4
  %45 = load ptr, ptr @fgAnim, align 8
  %46 = getelementptr inbounds %FlowWingAnim, ptr %45, i32 0, i32 5
  %47 = getelementptr inbounds %COLORS_TYPE.4, ptr %46, i32 0, i32 6
  %DARKGRAY = load i32, ptr %47, align 4
  %48 = load i32, ptr %47, align 4
  store i32 %48, ptr @NORMAL_COLOR, align 4
  %49 = load ptr, ptr @fgAnim, align 8
  %50 = getelementptr inbounds %FlowWingAnim, ptr %49, i32 0, i32 5
  %51 = getelementptr inbounds %COLORS_TYPE.4, ptr %50, i32 0, i32 4
  %DARKBLUE = load i32, ptr %51, align 4
  %52 = load i32, ptr %51, align 4
  store i32 %52, ptr @HOVER_COLOR, align 4
  call void @main(ptr %rtPtr)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 void @FlowWingAnim.init4(ptr, ptr, ptr, ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit(ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS(ptr)

declare !rt !3 void @FlowWingAnim.getColor(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow(ptr)

declare !rt !5 void @FlowWingAnim.clearBackground(ptr, ptr)

declare !rt !6 void @FlowWingAnim.windowShouldClose(ptr, ptr)

declare !rt !7 void @FlowWingAnim.beginDrawing(ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !9 void @FlowWingAnim.drawRectangleLines(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !10 void @FlowWingAnim.drawRectangleLinesEx(ptr, ptr, ptr, ptr)

declare !rt !11 void @FlowWingAnim.endDrawing(ptr)

declare !rt !12 void @FlowWingAnim.closeWindow(ptr)

declare !rt !13 void @FlowWingAnim.getTime(ptr, ptr)

declare !rt !14 void @FlowWingAnim.getFrameTime(ptr, ptr)

declare !rt !15 void @FlowWingAnim.getScreenHeight(ptr, ptr)

declare !rt !16 void @FlowWingAnim.getScreenWidth(ptr, ptr)

declare !rt !17 void @FlowWingAnim.drawCircle(ptr, ptr, ptr, ptr, ptr)

declare !rt !18 void @FlowWingAnim.drawText(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !19 void @FlowWingAnim.drawTexture(ptr, ptr, ptr, ptr, ptr)

declare !rt !20 void @FlowWingAnim.getMousePosition(ptr, ptr)

declare !rt !21 void @FlowWingAnim.drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !22 void @FlowWingAnim.traceLog(ptr, ptr, ptr)

declare !rt !23 void @FlowWingAnim.loadTexture(ptr, ptr, ptr)

declare !rt !24 void @FlowWingAnim.unloadTexture(ptr, ptr)

declare !rt !25 void @FlowWingAnim.isKeyPressed(ptr, ptr, ptr)

declare !rt !26 void @FlowWingAnim.isKeyDown(ptr, ptr, ptr)

declare !rt !27 void @FlowWingAnim.textFormat(ptr, ptr, ptr)

declare !rt !28 i32 @FlowWingAnim.measureText(ptr, i32, ptr)

declare !rt !29 void @FlowWingAnim.drawBoxWithText(ptr, ptr)

declare !rt !30 void @"Err::Result.init1"(ptr, ptr)

declare !rt !31 void @"Err::Result.init2"(ptr, ptr, ptr)

declare !rt !32 void @"Err::Result.init3"(ptr, ptr, ptr, ptr)

declare !rt !33 void @"Err::Result.getMessage"(ptr, ptr)

declare !rt !34 void @"Err::Result.getCode"(ptr, ptr)

declare !rt !35 void @"Err::Result.getDetails"(ptr, ptr)

declare !rt !36 void @"Err::Result.withMessage"(ptr, ptr, ptr)

declare !rt !37 void @"Err::Result.withDetails"(ptr, ptr, ptr)

declare !rt !38 void @"Err::Result.toString"(ptr, ptr)

define void @GameUnit.init2(ptr %0, ptr %1, ptr %2) !rt !39 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %GameUnit, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %GameUnit, ptr %3, i32 0, i32 2
  %text = alloca %Texture.9, align 8
  %6 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %6, ptr %text, align 4
  %ori = alloca %Position.7, align 8
  %7 = load %Position.7, ptr %1, align 4
  store %Position.7 %7, ptr %ori, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = load %Texture.9, ptr %text, align 4
  store %Texture.9 %8, ptr %4, align 4
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %11 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %13 = load %Position.7, ptr %ori, align 4
  store %Position.7 %13, ptr %5, align 4
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @GameUnit.init1(ptr %0, ptr %1) !rt !40 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 2
  %text = alloca %Texture.9, align 8
  %5 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %5, ptr %text, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = load %Texture.9, ptr %text, align 4
  store %Texture.9 %6, ptr %3, align 4
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @GameUnit.getTexture(ptr %0, ptr %1) !rt !41 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = load %Texture.9, ptr %3, align 4
  store %Texture.9 %5, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock
}

define void @GameUnit.getOrigin(ptr %0, ptr %1) !rt !42 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = load %Position.7, ptr %4, align 4
  store %Position.7 %5, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock
}

define void @GameUnit.getOriginAsArray(ptr %0, ptr %1) !rt !43 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameUnit, ptr %2, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = getelementptr [2 x float], ptr %0, i32 0, i32 0
  %6 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x = load float, ptr %6, align 4
  %7 = load float, ptr %6, align 4
  store float %7, ptr %5, align 4
  %8 = getelementptr [2 x float], ptr %0, i32 0, i32 1
  %9 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  %y = load float, ptr %9, align 4
  %10 = load float, ptr %9, align 4
  store float %10, ptr %8, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock
}

define void @GameUnit.draw(ptr %0) !rt !44 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GameUnit, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GameUnit, ptr %1, i32 0, i32 2
  br label %afterNestedBlock

afterNestedBlock:                                 ; preds = %entry
  ret void
}

define void @GameUnit.update(ptr %0) !rt !45 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GameUnit, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GameUnit, ptr %1, i32 0, i32 2
  br label %afterNestedBlock

afterNestedBlock:                                 ; preds = %entry
  ret void
}

define void @WideMountain.init1(ptr %0, ptr %1) !rt !46 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 4
  %texture = alloca %Texture.9, align 8
  %7 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %7, ptr %texture, align 4
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %texture, ptr %1)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %12 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 0
  store float 0.000000e+00, ptr %12, align 4
  %13 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 1
  store float 0.000000e+00, ptr %13, align 4
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %18 = getelementptr inbounds %Position.7, ptr %6, i32 0, i32 0
  store float -1.542000e+03, ptr %18, align 4
  %19 = getelementptr inbounds %Position.7, ptr %6, i32 0, i32 1
  store float 0.000000e+00, ptr %19, align 4
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @WideMountain.update(ptr %0) !rt !47 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 4
  %rtPtr = alloca float, align 4
  %rtPtr1 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock7, %afterIfElse19, %checkContinueBlock5, %afterIfElse, %checkContinueBlock3, %nestedBlock2, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x = load float, ptr %6, align 4
  %7 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x8 = load float, ptr %7, align 4
  %8 = load float, ptr %7, align 4
  %9 = load ptr, ptr @fgAnim, align 8
  %10 = getelementptr inbounds %FlowWingAnim, ptr %9, i32 0, i32 0
  %11 = load ptr, ptr %10, align 8
  %12 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %11, i32 0, i32 11
  %13 = load ptr, ptr %12, align 8
  call void %13(ptr %rtPtr, ptr @fgAnim)
  %14 = load float, ptr %rtPtr, align 4
  %15 = load i32, ptr @GAME_SPEED, align 4
  %16 = sitofp i32 %15 to float
  %17 = fmul float %14, %16
  %18 = fadd float %8, %17
  store float %18, ptr %6, align 4
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %21 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  %23 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 0
  %x9 = load float, ptr %23, align 4
  %24 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 0
  %x10 = load float, ptr %24, align 4
  %25 = load float, ptr %24, align 4
  %26 = load ptr, ptr @fgAnim, align 8
  %27 = getelementptr inbounds %FlowWingAnim, ptr %26, i32 0, i32 0
  %28 = load ptr, ptr %27, align 8
  %29 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 11
  %30 = load ptr, ptr %29, align 8
  call void %30(ptr %rtPtr1, ptr @fgAnim)
  %31 = load float, ptr %rtPtr1, align 4
  %32 = load i32, ptr @GAME_SPEED, align 4
  %33 = sitofp i32 %32 to float
  %34 = fmul float %31, %33
  %35 = fadd float %25, %34
  store float %35, ptr %23, align 4
  %36 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock3, label %afterNestedBlock

checkContinueBlock3:                              ; preds = %nestedBlock2
  %38 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock3
  %40 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x11 = load float, ptr %40, align 4
  %41 = load float, ptr %40, align 4
  %42 = fcmp ogt float %41, 1.542000e+03
  br i1 %42, label %then, label %else

checkContinueBlock5:                              ; preds = %afterIfElse
  %43 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  %45 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 0
  %x16 = load float, ptr %45, align 4
  %46 = load float, ptr %45, align 4
  %47 = fcmp ogt float %46, 1.542000e+03
  br i1 %47, label %then17, label %else18

checkContinueBlock7:                              ; preds = %afterIfElse19
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock4
  br label %nestedBlock13

else:                                             ; preds = %nestedBlock4
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock12
  %48 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock5, label %afterNestedBlock

afterNestedBlock12:                               ; preds = %checkContinueBlock14, %nestedBlock13
  %50 = load float, ptr %51, align 4
  br label %afterIfElse

nestedBlock13:                                    ; preds = %then
  %51 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x15 = load float, ptr %51, align 4
  store float -1.542000e+03, ptr %51, align 4
  %52 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock14, label %afterNestedBlock12

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock12

then17:                                           ; preds = %nestedBlock6
  br label %nestedBlock21

else18:                                           ; preds = %nestedBlock6
  br label %afterIfElse19

afterIfElse19:                                    ; preds = %else18, %afterNestedBlock20
  %54 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %checkContinueBlock7, label %afterNestedBlock

afterNestedBlock20:                               ; preds = %checkContinueBlock22, %nestedBlock21
  %56 = load float, ptr %57, align 4
  br label %afterIfElse19

nestedBlock21:                                    ; preds = %then17
  %57 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 0
  %x23 = load float, ptr %57, align 4
  store float -1.542000e+03, ptr %57, align 4
  %58 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %59 = icmp eq i32 %58, 0
  br i1 %59, label %checkContinueBlock22, label %afterNestedBlock20

checkContinueBlock22:                             ; preds = %nestedBlock21
  br label %afterNestedBlock20
}

define void @WideMountain.draw(ptr %0) !rt !48 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %WideMountain, ptr %1, i32 0, i32 4
  %6 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %6)
  %7 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %7)
  %8 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %8)
  %9 = alloca float, align 4
  %10 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %10)
  %11 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %11)
  %12 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %12)
  %13 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %14 = load ptr, ptr @fgAnim, align 8
  %15 = getelementptr inbounds %FlowWingAnim, ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %16, i32 0, i32 24
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr [4 x float], ptr %6, i32 0, i32 0
  store float 0.000000e+00, ptr %19, align 4
  %20 = getelementptr [4 x float], ptr %6, i32 0, i32 1
  store float 0.000000e+00, ptr %20, align 4
  %21 = getelementptr [4 x float], ptr %6, i32 0, i32 2
  store float 8.982000e+03, ptr %21, align 4
  %22 = getelementptr [4 x float], ptr %6, i32 0, i32 3
  store float 1.542000e+03, ptr %22, align 4
  %23 = getelementptr [4 x float], ptr %7, i32 0, i32 0
  store float 0.000000e+00, ptr %23, align 4
  %24 = getelementptr [4 x float], ptr %7, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %25 = load i32, ptr @screenHeight, align 4
  %26 = sitofp i32 %25 to double
  %27 = fdiv double %26, 3.000000e+00
  %28 = fptrunc double %27 to float
  store float %28, ptr %24, align 4
  %29 = getelementptr [4 x float], ptr %7, i32 0, i32 2
  %screenWidth = load i32, ptr @screenWidth, align 4
  %30 = load i32, ptr @screenWidth, align 4
  %screenWidth3 = load i32, ptr @screenWidth, align 4
  %31 = load i32, ptr @screenWidth, align 4
  %32 = sitofp i32 %31 to double
  %33 = fdiv double %32, 2.000000e+00
  %34 = sitofp i32 %30 to double
  %35 = fadd double %34, %33
  %36 = fptrunc double %35 to float
  store float %36, ptr %29, align 4
  %37 = getelementptr [4 x float], ptr %7, i32 0, i32 3
  %screenHeight4 = load i32, ptr @screenHeight, align 4
  %38 = load i32, ptr @screenHeight, align 4
  %39 = sitofp i32 %38 to double
  %40 = fdiv double %39, 3.000000e+00
  %41 = fptrunc double %40 to float
  store float %41, ptr %37, align 4
  %42 = getelementptr [2 x float], ptr %8, i32 0, i32 0
  %43 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x = load float, ptr %43, align 4
  %44 = load float, ptr %43, align 4
  store float %44, ptr %42, align 4
  %45 = getelementptr [2 x float], ptr %8, i32 0, i32 1
  %46 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  %y = load float, ptr %46, align 4
  %47 = load float, ptr %46, align 4
  store float %47, ptr %45, align 4
  store float 0.000000e+00, ptr %9, align 4
  %48 = load ptr, ptr @fgAnim, align 8
  %49 = getelementptr inbounds %FlowWingAnim, ptr %48, i32 0, i32 5
  %50 = getelementptr inbounds %COLORS_TYPE.4, ptr %49, i32 0, i32 0
  %WHITE = load i32, ptr %50, align 4
  call void %18(ptr %2, ptr %6, ptr %7, ptr %8, ptr %9, ptr %50, ptr @fgAnim)
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %53 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %55 = load ptr, ptr @fgAnim, align 8
  %56 = getelementptr inbounds %FlowWingAnim, ptr %55, i32 0, i32 0
  %57 = load ptr, ptr %56, align 8
  %58 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %57, i32 0, i32 24
  %59 = load ptr, ptr %58, align 8
  %60 = getelementptr [4 x float], ptr %10, i32 0, i32 0
  store float 0.000000e+00, ptr %60, align 4
  %61 = getelementptr [4 x float], ptr %10, i32 0, i32 1
  store float 0.000000e+00, ptr %61, align 4
  %62 = getelementptr [4 x float], ptr %10, i32 0, i32 2
  store float 8.982000e+03, ptr %62, align 4
  %63 = getelementptr [4 x float], ptr %10, i32 0, i32 3
  store float 1.542000e+03, ptr %63, align 4
  %64 = getelementptr [4 x float], ptr %11, i32 0, i32 0
  store float 0.000000e+00, ptr %64, align 4
  %65 = getelementptr [4 x float], ptr %11, i32 0, i32 1
  %screenHeight5 = load i32, ptr @screenHeight, align 4
  %66 = load i32, ptr @screenHeight, align 4
  %67 = sitofp i32 %66 to double
  %68 = fdiv double %67, 3.000000e+00
  %69 = fptrunc double %68 to float
  store float %69, ptr %65, align 4
  %70 = getelementptr [4 x float], ptr %11, i32 0, i32 2
  %screenWidth6 = load i32, ptr @screenWidth, align 4
  %71 = load i32, ptr @screenWidth, align 4
  %screenWidth7 = load i32, ptr @screenWidth, align 4
  %72 = load i32, ptr @screenWidth, align 4
  %73 = sitofp i32 %72 to double
  %74 = fdiv double %73, 2.000000e+00
  %75 = sitofp i32 %71 to double
  %76 = fadd double %75, %74
  %77 = fptrunc double %76 to float
  store float %77, ptr %70, align 4
  %78 = getelementptr [4 x float], ptr %11, i32 0, i32 3
  %screenHeight8 = load i32, ptr @screenHeight, align 4
  %79 = load i32, ptr @screenHeight, align 4
  %80 = sitofp i32 %79 to double
  %81 = fdiv double %80, 3.000000e+00
  %82 = fptrunc double %81 to float
  store float %82, ptr %78, align 4
  %83 = getelementptr [2 x float], ptr %12, i32 0, i32 0
  %84 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 0
  %x9 = load float, ptr %84, align 4
  %85 = load float, ptr %84, align 4
  store float %85, ptr %83, align 4
  %86 = getelementptr [2 x float], ptr %12, i32 0, i32 1
  %87 = getelementptr inbounds %Position.7, ptr %5, i32 0, i32 1
  %y10 = load float, ptr %87, align 4
  %88 = load float, ptr %87, align 4
  store float %88, ptr %86, align 4
  store float 0.000000e+00, ptr %13, align 4
  %89 = load ptr, ptr @fgAnim, align 8
  %90 = getelementptr inbounds %FlowWingAnim, ptr %89, i32 0, i32 5
  %91 = getelementptr inbounds %COLORS_TYPE.4, ptr %90, i32 0, i32 0
  %WHITE11 = load i32, ptr %91, align 4
  call void %59(ptr %2, ptr %10, ptr %11, ptr %12, ptr %13, ptr %91, ptr @fgAnim)
  %92 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @WideMountain.getOriginFirstMount(ptr %0, ptr %1) !rt !49 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %7 = load %Position.7, ptr %5, align 4
  store %Position.7 %7, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @WideMountain.getOriginSecondMount(ptr %0, ptr %1) !rt !50 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %WideMountain, ptr %2, i32 0, i32 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %7 = load %Position.7, ptr %6, align 4
  store %Position.7 %7, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define void @HeightedMountain.init1(ptr %0, ptr %1) !rt !51 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %HeightedMountain, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %HeightedMountain, ptr %2, i32 0, i32 2
  %texture = alloca %Texture.9, align 8
  %5 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %5, ptr %texture, align 4
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %texture, ptr %1)
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %8 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %10 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %11 = load i32, ptr @screenWidth, align 4
  %12 = mul i32 -1, %11
  %13 = sitofp i32 %12 to float
  store float %13, ptr %10, align 4
  %14 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  store float 0.000000e+00, ptr %14, align 4
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @HeightedMountain.update(ptr %0) !rt !52 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %HeightedMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %HeightedMountain, ptr %1, i32 0, i32 2
  %rtPtr = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %4, align 4
  %5 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x3 = load float, ptr %5, align 4
  %6 = load float, ptr %5, align 4
  %7 = load ptr, ptr @fgAnim, align 8
  %8 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %9, i32 0, i32 11
  %11 = load ptr, ptr %10, align 8
  call void %11(ptr %rtPtr, ptr @fgAnim)
  %12 = load float, ptr %rtPtr, align 4
  %13 = load i32, ptr @GAME_SPEED, align 4
  %14 = sitofp i32 %13 to double
  %15 = fdiv double %14, 1.000000e+01
  %16 = fptrunc double %15 to float
  %17 = fmul float %12, %16
  %18 = fadd float %6, %17
  store float %18, ptr %4, align 4
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %21 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %23 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x4 = load float, ptr %23, align 4
  %24 = load float, ptr %23, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %25 = load i32, ptr @screenWidth, align 4
  %screenWidth5 = load i32, ptr @screenWidth, align 4
  %26 = load i32, ptr @screenWidth, align 4
  %27 = sitofp i32 %26 to double
  %28 = fdiv double %27, 2.000000e+00
  %29 = sitofp i32 %25 to double
  %30 = fadd double %29, %28
  %31 = fptrunc double %30 to float
  %32 = fcmp ogt float %24, %31
  br i1 %32, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock8, %nestedBlock7
  %35 = load float, ptr %36, align 4
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %36 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x9 = load float, ptr %36, align 4
  %screenWidth10 = load i32, ptr @screenWidth, align 4
  %37 = load i32, ptr @screenWidth, align 4
  %38 = mul i32 -1, %37
  %39 = sitofp i32 %38 to float
  store float %39, ptr %36, align 4
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock6
}

define void @HeightedMountain.draw(ptr %0) !rt !53 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %HeightedMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %HeightedMountain, ptr %1, i32 0, i32 2
  %4 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %4)
  %5 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %5)
  %6 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %6)
  %7 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = load ptr, ptr @fgAnim, align 8
  %9 = getelementptr inbounds %FlowWingAnim, ptr %8, i32 0, i32 0
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %10, i32 0, i32 24
  %12 = load ptr, ptr %11, align 8
  %13 = getelementptr [4 x float], ptr %4, i32 0, i32 0
  store float 0.000000e+00, ptr %13, align 4
  %14 = getelementptr [4 x float], ptr %4, i32 0, i32 1
  store float 0.000000e+00, ptr %14, align 4
  %15 = getelementptr [4 x float], ptr %4, i32 0, i32 2
  store float 5.975000e+03, ptr %15, align 4
  %16 = getelementptr [4 x float], ptr %4, i32 0, i32 3
  store float 1.607000e+03, ptr %16, align 4
  %17 = getelementptr [4 x float], ptr %5, i32 0, i32 0
  store float 0.000000e+00, ptr %17, align 4
  %18 = getelementptr [4 x float], ptr %5, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %19 = load i32, ptr @screenHeight, align 4
  %20 = sitofp i32 %19 to double
  %21 = fdiv double %20, 3.000000e+00
  %22 = fptrunc double %21 to float
  store float %22, ptr %18, align 4
  %23 = getelementptr [4 x float], ptr %5, i32 0, i32 2
  %screenWidth = load i32, ptr @screenWidth, align 4
  %24 = load i32, ptr @screenWidth, align 4
  %25 = sitofp i32 %24 to double
  %26 = fdiv double %25, 2.000000e+00
  %27 = fptrunc double %26 to float
  store float %27, ptr %23, align 4
  %28 = getelementptr [4 x float], ptr %5, i32 0, i32 3
  %screenHeight1 = load i32, ptr @screenHeight, align 4
  %29 = load i32, ptr @screenHeight, align 4
  %30 = sitofp i32 %29 to double
  %31 = fdiv double %30, 3.000000e+00
  %32 = fptrunc double %31 to float
  store float %32, ptr %28, align 4
  %33 = getelementptr [2 x float], ptr %6, i32 0, i32 0
  %34 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %34, align 4
  %35 = load float, ptr %34, align 4
  store float %35, ptr %33, align 4
  %36 = getelementptr [2 x float], ptr %6, i32 0, i32 1
  %37 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y = load float, ptr %37, align 4
  %38 = load float, ptr %37, align 4
  store float %38, ptr %36, align 4
  store float 0.000000e+00, ptr %7, align 4
  %39 = load ptr, ptr @fgAnim, align 8
  %40 = getelementptr inbounds %FlowWingAnim, ptr %39, i32 0, i32 5
  %41 = getelementptr inbounds %COLORS_TYPE.4, ptr %40, i32 0, i32 0
  %WHITE = load i32, ptr %41, align 4
  call void %12(ptr %2, ptr %4, ptr %5, ptr %6, ptr %7, ptr %41, ptr @fgAnim)
  %42 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @GreenMountain.init1(ptr %0, ptr %1) !rt !54 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GreenMountain, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GreenMountain, ptr %2, i32 0, i32 2
  %texture = alloca %Texture.9, align 8
  %5 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %5, ptr %texture, align 4
  %clPtr = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %texture, ptr %1)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %12 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %13 = load i32, ptr @screenWidth, align 4
  %14 = mul i32 -1, %13
  %screenWidth3 = load i32, ptr @screenWidth, align 4
  %15 = load i32, ptr @screenWidth, align 4
  %16 = sitofp i32 %15 to double
  %17 = fdiv double %16, 4.000000e+00
  %18 = fptosi double %17 to i32
  store i32 %18, ptr %6, align 4
  %screenWidth4 = load i32, ptr @screenWidth, align 4
  %19 = load i32, ptr @screenWidth, align 4
  %20 = sitofp i32 %19 to double
  %21 = fdiv double %20, 2.000000e+00
  %22 = fptosi double %21 to i32
  store i32 %22, ptr %7, align 4
  %23 = call i32 @getRandomNumber(ptr %6, ptr %7)
  %24 = sub i32 %14, %23
  %25 = sitofp i32 %24 to float
  store float %25, ptr %12, align 4
  %26 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  store float 0.000000e+00, ptr %26, align 4
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @GreenMountain.update(ptr %0) !rt !55 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GreenMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GreenMountain, ptr %1, i32 0, i32 2
  %rtPtr = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %4, align 4
  %5 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x3 = load float, ptr %5, align 4
  %6 = load float, ptr %5, align 4
  %7 = load ptr, ptr @fgAnim, align 8
  %8 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %9, i32 0, i32 11
  %11 = load ptr, ptr %10, align 8
  call void %11(ptr %rtPtr, ptr @fgAnim)
  %12 = load float, ptr %rtPtr, align 4
  %13 = load i32, ptr @GAME_SPEED, align 4
  %14 = sitofp i32 %13 to double
  %15 = fdiv double %14, 1.000000e+01
  %16 = fptrunc double %15 to float
  %17 = fmul float %12, %16
  %18 = fadd float %6, %17
  store float %18, ptr %4, align 4
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %21 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %23 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x4 = load float, ptr %23, align 4
  %24 = load float, ptr %23, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %25 = load i32, ptr @screenWidth, align 4
  %screenWidth5 = load i32, ptr @screenWidth, align 4
  %26 = load i32, ptr @screenWidth, align 4
  %27 = sitofp i32 %26 to double
  %28 = fdiv double %27, 2.000000e+00
  %29 = sitofp i32 %25 to double
  %30 = fadd double %29, %28
  %31 = fptrunc double %30 to float
  %32 = fcmp ogt float %24, %31
  br i1 %32, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock8, %nestedBlock7
  %35 = load float, ptr %36, align 4
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %36 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x9 = load float, ptr %36, align 4
  %screenWidth10 = load i32, ptr @screenWidth, align 4
  %37 = load i32, ptr @screenWidth, align 4
  %38 = mul i32 -1, %37
  %39 = sitofp i32 %38 to float
  store float %39, ptr %36, align 4
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock6
}

define void @GreenMountain.draw(ptr %0) !rt !56 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GreenMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GreenMountain, ptr %1, i32 0, i32 2
  %4 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %4)
  %5 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %5)
  %6 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %6)
  %7 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = load ptr, ptr @fgAnim, align 8
  %9 = getelementptr inbounds %FlowWingAnim, ptr %8, i32 0, i32 0
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %10, i32 0, i32 24
  %12 = load ptr, ptr %11, align 8
  %13 = getelementptr [4 x float], ptr %4, i32 0, i32 0
  store float 0.000000e+00, ptr %13, align 4
  %14 = getelementptr [4 x float], ptr %4, i32 0, i32 1
  store float 0.000000e+00, ptr %14, align 4
  %15 = getelementptr [4 x float], ptr %4, i32 0, i32 2
  store float 4.461000e+03, ptr %15, align 4
  %16 = getelementptr [4 x float], ptr %4, i32 0, i32 3
  store float 1.989000e+03, ptr %16, align 4
  %17 = getelementptr [4 x float], ptr %5, i32 0, i32 0
  store float 0.000000e+00, ptr %17, align 4
  %18 = getelementptr [4 x float], ptr %5, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %19 = load i32, ptr @screenHeight, align 4
  %20 = sitofp i32 %19 to double
  %21 = fdiv double %20, 3.000000e+00
  %22 = fptrunc double %21 to float
  store float %22, ptr %18, align 4
  %23 = getelementptr [4 x float], ptr %5, i32 0, i32 2
  %screenWidth = load i32, ptr @screenWidth, align 4
  %24 = load i32, ptr @screenWidth, align 4
  %25 = sitofp i32 %24 to double
  %26 = fdiv double %25, 2.000000e+00
  %27 = fptrunc double %26 to float
  store float %27, ptr %23, align 4
  %28 = getelementptr [4 x float], ptr %5, i32 0, i32 3
  %screenHeight1 = load i32, ptr @screenHeight, align 4
  %29 = load i32, ptr @screenHeight, align 4
  %30 = sitofp i32 %29 to double
  %31 = fdiv double %30, 3.000000e+00
  %32 = fptrunc double %31 to float
  store float %32, ptr %28, align 4
  %33 = getelementptr [2 x float], ptr %6, i32 0, i32 0
  %34 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %34, align 4
  %35 = load float, ptr %34, align 4
  store float %35, ptr %33, align 4
  %36 = getelementptr [2 x float], ptr %6, i32 0, i32 1
  %37 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y = load float, ptr %37, align 4
  %38 = load float, ptr %37, align 4
  store float %38, ptr %36, align 4
  store float 0.000000e+00, ptr %7, align 4
  %39 = load ptr, ptr @fgAnim, align 8
  %40 = getelementptr inbounds %FlowWingAnim, ptr %39, i32 0, i32 5
  %41 = getelementptr inbounds %COLORS_TYPE.4, ptr %40, i32 0, i32 0
  %WHITE = load i32, ptr %41, align 4
  call void %12(ptr %2, ptr %4, ptr %5, ptr %6, ptr %7, ptr %41, ptr @fgAnim)
  %42 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @BlackMountain.init1(ptr %0, ptr %1) !rt !57 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %BlackMountain, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %BlackMountain, ptr %2, i32 0, i32 2
  %texture = alloca %Texture.9, align 8
  %5 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %5, ptr %texture, align 4
  %clPtr = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %texture, ptr %1)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %12 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %13 = load i32, ptr @screenWidth, align 4
  %14 = mul i32 -1, %13
  %screenWidth3 = load i32, ptr @screenWidth, align 4
  %15 = load i32, ptr @screenWidth, align 4
  %16 = sitofp i32 %15 to double
  %17 = fdiv double %16, 4.000000e+00
  %18 = fptosi double %17 to i32
  store i32 %18, ptr %6, align 4
  %screenWidth4 = load i32, ptr @screenWidth, align 4
  %19 = load i32, ptr @screenWidth, align 4
  store i32 %19, ptr %7, align 4
  %20 = call i32 @getRandomNumber(ptr %6, ptr %7)
  %21 = sub i32 %14, %20
  %22 = sitofp i32 %21 to float
  store float %22, ptr %12, align 4
  %23 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  store float 0.000000e+00, ptr %23, align 4
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @BlackMountain.update(ptr %0) !rt !58 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %BlackMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %BlackMountain, ptr %1, i32 0, i32 2
  %rtPtr = alloca float, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %10 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %10, align 4
  %11 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x3 = load float, ptr %11, align 4
  %12 = load float, ptr %11, align 4
  %13 = load ptr, ptr @fgAnim, align 8
  %14 = getelementptr inbounds %FlowWingAnim, ptr %13, i32 0, i32 0
  %15 = load ptr, ptr %14, align 8
  %16 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %15, i32 0, i32 11
  %17 = load ptr, ptr %16, align 8
  call void %17(ptr %rtPtr, ptr @fgAnim)
  %18 = load float, ptr %rtPtr, align 4
  %19 = load i32, ptr @GAME_SPEED, align 4
  %20 = sitofp i32 %19 to double
  %21 = fdiv double %20, 1.000000e+01
  %22 = fptrunc double %21 to float
  %23 = fmul float %18, %22
  %24 = fadd float %12, %23
  store float %24, ptr %10, align 4
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %27 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %29 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x4 = load float, ptr %29, align 4
  %30 = load float, ptr %29, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %31 = load i32, ptr @screenWidth, align 4
  %screenWidth5 = load i32, ptr @screenWidth, align 4
  %32 = load i32, ptr @screenWidth, align 4
  %33 = sitofp i32 %32 to double
  %34 = fdiv double %33, 2.000000e+00
  %35 = sitofp i32 %31 to double
  %36 = fadd double %35, %34
  %37 = fptrunc double %36 to float
  %38 = fcmp ogt float %30, %37
  br i1 %38, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock8, %nestedBlock7
  %41 = load float, ptr %42, align 4
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %42 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x9 = load float, ptr %42, align 4
  %screenWidth10 = load i32, ptr @screenWidth, align 4
  %43 = load i32, ptr @screenWidth, align 4
  %44 = mul i32 -1, %43
  %screenWidth11 = load i32, ptr @screenWidth, align 4
  %45 = load i32, ptr @screenWidth, align 4
  %46 = sitofp i32 %45 to double
  %47 = fdiv double %46, 4.000000e+00
  %48 = fptosi double %47 to i32
  store i32 %48, ptr %8, align 4
  %screenWidth12 = load i32, ptr @screenWidth, align 4
  %49 = load i32, ptr @screenWidth, align 4
  %50 = sitofp i32 %49 to double
  %51 = fdiv double %50, 2.000000e+00
  %52 = fptosi double %51 to i32
  store i32 %52, ptr %9, align 4
  %53 = call i32 @getRandomNumber(ptr %8, ptr %9)
  %54 = sub i32 %44, %53
  %55 = sitofp i32 %54 to float
  store float %55, ptr %42, align 4
  %56 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock6
}

define void @BlackMountain.draw(ptr %0) !rt !59 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %BlackMountain, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %BlackMountain, ptr %1, i32 0, i32 2
  %4 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %4)
  %5 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %5)
  %6 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %6)
  %7 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = load ptr, ptr @fgAnim, align 8
  %9 = getelementptr inbounds %FlowWingAnim, ptr %8, i32 0, i32 0
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %10, i32 0, i32 24
  %12 = load ptr, ptr %11, align 8
  %13 = getelementptr [4 x float], ptr %4, i32 0, i32 0
  store float 0.000000e+00, ptr %13, align 4
  %14 = getelementptr [4 x float], ptr %4, i32 0, i32 1
  store float 0.000000e+00, ptr %14, align 4
  %15 = getelementptr [4 x float], ptr %4, i32 0, i32 2
  store float 6.005000e+03, ptr %15, align 4
  %16 = getelementptr [4 x float], ptr %4, i32 0, i32 3
  store float 2.376000e+03, ptr %16, align 4
  %17 = getelementptr [4 x float], ptr %5, i32 0, i32 0
  store float 0.000000e+00, ptr %17, align 4
  %18 = getelementptr [4 x float], ptr %5, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %19 = load i32, ptr @screenHeight, align 4
  %20 = sitofp i32 %19 to double
  %21 = fdiv double %20, 3.000000e+00
  %22 = fptrunc double %21 to float
  store float %22, ptr %18, align 4
  %23 = getelementptr [4 x float], ptr %5, i32 0, i32 2
  %screenWidth = load i32, ptr @screenWidth, align 4
  %24 = load i32, ptr @screenWidth, align 4
  %25 = sitofp i32 %24 to double
  %26 = fdiv double %25, 2.000000e+00
  %27 = fptrunc double %26 to float
  store float %27, ptr %23, align 4
  %28 = getelementptr [4 x float], ptr %5, i32 0, i32 3
  %screenHeight1 = load i32, ptr @screenHeight, align 4
  %29 = load i32, ptr @screenHeight, align 4
  %30 = sitofp i32 %29 to double
  %31 = fdiv double %30, 3.000000e+00
  %32 = fptrunc double %31 to float
  store float %32, ptr %28, align 4
  %33 = getelementptr [2 x float], ptr %6, i32 0, i32 0
  %34 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %34, align 4
  %35 = load float, ptr %34, align 4
  store float %35, ptr %33, align 4
  %36 = getelementptr [2 x float], ptr %6, i32 0, i32 1
  %37 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y = load float, ptr %37, align 4
  %38 = load float, ptr %37, align 4
  store float %38, ptr %36, align 4
  store float 0.000000e+00, ptr %7, align 4
  %39 = load ptr, ptr @fgAnim, align 8
  %40 = getelementptr inbounds %FlowWingAnim, ptr %39, i32 0, i32 5
  %41 = getelementptr inbounds %COLORS_TYPE.4, ptr %40, i32 0, i32 0
  %WHITE = load i32, ptr %41, align 4
  call void %12(ptr %2, ptr %4, ptr %5, ptr %6, ptr %7, ptr %41, ptr @fgAnim)
  %42 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Bird.init1(ptr %0, ptr %1) !rt !60 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 10
  %birdTexture = alloca %Texture.9, align 8
  %13 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %13, ptr %birdTexture, align 4
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %birdTexture, ptr %1)
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %18 = load ptr, ptr %1, align 8
  %19 = getelementptr inbounds %Bird, ptr %18, i32 0, i32 6
  %birdTimmer = load double, ptr %19, align 8
  %BIRD_TIMMER = load double, ptr %7, align 8
  %20 = load double, ptr %7, align 8
  store double %20, ptr %19, align 8
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = load ptr, ptr %1, align 8
  %26 = getelementptr inbounds %Bird, ptr %25, i32 0, i32 9
  %isBirdAlive = load i1, ptr %26, align 1
  store i1 true, ptr %26, align 1
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %29 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %31 = load ptr, ptr %1, align 8
  %32 = getelementptr inbounds %Bird, ptr %31, i32 0, i32 10
  %33 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 0
  %34 = getelementptr inbounds %Position.7, ptr %33, i32 0, i32 0
  store float 0.000000e+00, ptr %34, align 4
  %35 = getelementptr inbounds %Position.7, ptr %33, i32 0, i32 1
  store float 0.000000e+00, ptr %35, align 4
  %36 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 1
  %37 = getelementptr inbounds %Position.7, ptr %36, i32 0, i32 0
  %ACTUAL_BIRD_SIZE = load float, ptr %5, align 4
  %38 = load float, ptr %5, align 4
  %39 = fmul float %38, 1.000000e+00
  store float %39, ptr %37, align 4
  %40 = getelementptr inbounds %Position.7, ptr %36, i32 0, i32 1
  store float 0.000000e+00, ptr %40, align 4
  %41 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 2
  %42 = getelementptr inbounds %Position.7, ptr %41, i32 0, i32 0
  %ACTUAL_BIRD_SIZE7 = load float, ptr %5, align 4
  %43 = load float, ptr %5, align 4
  %44 = fmul float %43, 2.000000e+00
  store float %44, ptr %42, align 4
  %45 = getelementptr inbounds %Position.7, ptr %41, i32 0, i32 1
  store float 0.000000e+00, ptr %45, align 4
  %46 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 3
  %47 = getelementptr inbounds %Position.7, ptr %46, i32 0, i32 0
  store float 0.000000e+00, ptr %47, align 4
  %48 = getelementptr inbounds %Position.7, ptr %46, i32 0, i32 1
  %ACTUAL_BIRD_SIZE8 = load float, ptr %5, align 4
  %49 = load float, ptr %5, align 4
  %50 = fmul float %49, 1.000000e+00
  store float %50, ptr %48, align 4
  %51 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 4
  %52 = getelementptr inbounds %Position.7, ptr %51, i32 0, i32 0
  %ACTUAL_BIRD_SIZE9 = load float, ptr %5, align 4
  %53 = load float, ptr %5, align 4
  %54 = fmul float %53, 1.000000e+00
  store float %54, ptr %52, align 4
  %55 = getelementptr inbounds %Position.7, ptr %51, i32 0, i32 1
  %ACTUAL_BIRD_SIZE10 = load float, ptr %5, align 4
  %56 = load float, ptr %5, align 4
  %57 = fmul float %56, 1.000000e+00
  store float %57, ptr %55, align 4
  %58 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 5
  %59 = getelementptr inbounds %Position.7, ptr %58, i32 0, i32 0
  %ACTUAL_BIRD_SIZE11 = load float, ptr %5, align 4
  %60 = load float, ptr %5, align 4
  %61 = fmul float %60, 2.000000e+00
  store float %61, ptr %59, align 4
  %62 = getelementptr inbounds %Position.7, ptr %58, i32 0, i32 1
  %ACTUAL_BIRD_SIZE12 = load float, ptr %5, align 4
  %63 = load float, ptr %5, align 4
  %64 = fmul float %63, 1.000000e+00
  store float %64, ptr %62, align 4
  %65 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 6
  %66 = getelementptr inbounds %Position.7, ptr %65, i32 0, i32 0
  store float 0.000000e+00, ptr %66, align 4
  %67 = getelementptr inbounds %Position.7, ptr %65, i32 0, i32 1
  %ACTUAL_BIRD_SIZE13 = load float, ptr %5, align 4
  %68 = load float, ptr %5, align 4
  %69 = fmul float %68, 2.000000e+00
  store float %69, ptr %67, align 4
  %70 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 7
  %71 = getelementptr inbounds %Position.7, ptr %70, i32 0, i32 0
  %ACTUAL_BIRD_SIZE14 = load float, ptr %5, align 4
  %72 = load float, ptr %5, align 4
  %73 = fmul float %72, 1.000000e+00
  store float %73, ptr %71, align 4
  %74 = getelementptr inbounds %Position.7, ptr %70, i32 0, i32 1
  %ACTUAL_BIRD_SIZE15 = load float, ptr %5, align 4
  %75 = load float, ptr %5, align 4
  %76 = fmul float %75, 2.000000e+00
  store float %76, ptr %74, align 4
  %77 = getelementptr [9 x %Position.7], ptr %32, i32 0, i32 8
  %78 = getelementptr inbounds %Position.7, ptr %77, i32 0, i32 0
  %ACTUAL_BIRD_SIZE16 = load float, ptr %5, align 4
  %79 = load float, ptr %5, align 4
  %80 = fmul float %79, 2.000000e+00
  store float %80, ptr %78, align 4
  %81 = getelementptr inbounds %Position.7, ptr %77, i32 0, i32 1
  %ACTUAL_BIRD_SIZE17 = load float, ptr %5, align 4
  %82 = load float, ptr %5, align 4
  %83 = fmul float %82, 2.000000e+00
  store float %83, ptr %81, align 4
  %84 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %85 = icmp eq i32 %84, 0
  br i1 %85, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @Bird.update(ptr %0) !rt !61 {
entry:
  %1 = load ptr, ptr %0, align 8
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
  store float 0.000000e+00, ptr %frameTime, align 4
  %rtPtr = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %afterIfElse, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %12 = load ptr, ptr @fgAnim, align 8
  %13 = getelementptr inbounds %FlowWingAnim, ptr %12, i32 0, i32 0
  %14 = load ptr, ptr %13, align 8
  %15 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %14, i32 0, i32 11
  %16 = load ptr, ptr %15, align 8
  call void %16(ptr %rtPtr, ptr @fgAnim)
  %17 = load float, ptr %rtPtr, align 4
  store float %17, ptr %frameTime, align 4
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %20 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %birdTimmer = load double, ptr %7, align 8
  %birdTimmer7 = load double, ptr %7, align 8
  %22 = load double, ptr %7, align 8
  %frameTime8 = load float, ptr %frameTime, align 4
  %23 = load float, ptr %frameTime, align 4
  %24 = fpext float %23 to double
  %25 = fsub double %22, %24
  store double %25, ptr %7, align 8
  %26 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %birdTimmer9 = load double, ptr %7, align 8
  %30 = load double, ptr %7, align 8
  %31 = fcmp olt double %30, 0.000000e+00
  br i1 %31, label %then, label %else

checkContinueBlock4:                              ; preds = %afterIfElse
  %32 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  call void @Bird.handleInput(ptr %0)
  %34 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock3
  br label %nestedBlock11

else:                                             ; preds = %nestedBlock3
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock10
  %36 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock4, label %afterNestedBlock

afterNestedBlock10:                               ; preds = %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %afterIfElse24, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11
  br label %afterIfElse

nestedBlock11:                                    ; preds = %then
  %birdTimmer19 = load double, ptr %7, align 8
  %BIRD_TIMMER = load double, ptr %6, align 8
  %38 = load double, ptr %6, align 8
  store double %38, ptr %7, align 8
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock12, label %afterNestedBlock10

checkContinueBlock12:                             ; preds = %nestedBlock11
  %41 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock13, label %afterNestedBlock10

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %birdSpriteIndex = load i32, ptr %9, align 4
  %birdSpriteIndex20 = load i32, ptr %9, align 4
  %43 = load i32, ptr %9, align 4
  %44 = add i32 %43, 1
  store i32 %44, ptr %9, align 4
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock14, label %afterNestedBlock10

checkContinueBlock14:                             ; preds = %nestedBlock13
  %47 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %nestedBlock15, label %afterNestedBlock10

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %birdSpriteIndex21 = load i32, ptr %9, align 4
  %49 = load i32, ptr %9, align 4
  %BIRD_SPRITE_SIZE = load i32, ptr %8, align 4
  %50 = load i32, ptr %8, align 4
  %51 = icmp sge i32 %49, %50
  br i1 %51, label %then22, label %else23

checkContinueBlock16:                             ; preds = %afterIfElse24
  %52 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %nestedBlock17, label %afterNestedBlock10

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %54 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y = load float, ptr %54, align 4
  %55 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y29 = load float, ptr %55, align 4
  %56 = load float, ptr %55, align 4
  %frameTime30 = load float, ptr %frameTime, align 4
  %57 = load float, ptr %frameTime, align 4
  %58 = fmul float %57, -1.490000e+02
  %59 = fadd float %56, %58
  store float %59, ptr %54, align 4
  %60 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %checkContinueBlock18, label %afterNestedBlock10

checkContinueBlock18:                             ; preds = %nestedBlock17
  br label %afterNestedBlock10

then22:                                           ; preds = %nestedBlock15
  br label %nestedBlock26

else23:                                           ; preds = %nestedBlock15
  br label %afterIfElse24

afterIfElse24:                                    ; preds = %else23, %afterNestedBlock25
  %62 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %63 = icmp eq i32 %62, 0
  br i1 %63, label %checkContinueBlock16, label %afterNestedBlock10

afterNestedBlock25:                               ; preds = %checkContinueBlock27, %nestedBlock26
  br label %afterIfElse24

nestedBlock26:                                    ; preds = %then22
  %birdSpriteIndex28 = load i32, ptr %9, align 4
  store i32 0, ptr %9, align 4
  %64 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %checkContinueBlock27, label %afterNestedBlock25

checkContinueBlock27:                             ; preds = %nestedBlock26
  br label %afterNestedBlock25
}

define void @Bird.handleInput(ptr %0) !rt !62 {
entry:
  %1 = load ptr, ptr %0, align 8
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
  %rtPtr = alloca i1, align 1
  %rtPtr1 = alloca i1, align 1
  %12 = alloca float, align 4
  %13 = alloca float, align 4
  %14 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = load ptr, ptr @fgAnim, align 8
  %16 = getelementptr inbounds %FlowWingAnim, ptr %15, i32 0, i32 0
  %17 = load ptr, ptr %16, align 8
  %18 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  %20 = load ptr, ptr @fgAnim, align 8
  %21 = getelementptr inbounds %FlowWingAnim, ptr %20, i32 0, i32 6
  %22 = getelementptr inbounds %KEYS_TYPE.3, ptr %21, i32 0, i32 3
  %KEY_UP = load i32, ptr %22, align 4
  call void %19(ptr %rtPtr, ptr %22, ptr @fgAnim)
  %23 = load i1, ptr %rtPtr, align 1
  %24 = load ptr, ptr @fgAnim, align 8
  %25 = getelementptr inbounds %FlowWingAnim, ptr %24, i32 0, i32 0
  %26 = load ptr, ptr %25, align 8
  %27 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %26, i32 0, i32 6
  %28 = load ptr, ptr %27, align 8
  %29 = load ptr, ptr @fgAnim, align 8
  %30 = getelementptr inbounds %FlowWingAnim, ptr %29, i32 0, i32 6
  %31 = getelementptr inbounds %KEYS_TYPE.3, ptr %30, i32 0, i32 3
  %KEY_UP2 = load i32, ptr %31, align 4
  call void %28(ptr %rtPtr1, ptr %31, ptr @fgAnim)
  %32 = load i1, ptr %rtPtr1, align 1
  %33 = select i1 %23, i1 true, i1 %32
  br i1 %33, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock4

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock3
  %34 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock3:                                ; preds = %checkContinueBlock5, %nestedBlock4
  br label %afterIfElse

nestedBlock4:                                     ; preds = %then
  %36 = load ptr, ptr @fgAnim, align 8
  %37 = getelementptr inbounds %FlowWingAnim, ptr %36, i32 0, i32 0
  %38 = load ptr, ptr %37, align 8
  %39 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %38, i32 0, i32 11
  %40 = load ptr, ptr %39, align 8
  call void %40(ptr %14, ptr @fgAnim)
  call void @Bird.updateY(ptr %14, ptr %0)
  %41 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %checkContinueBlock5, label %afterNestedBlock3

checkContinueBlock5:                              ; preds = %nestedBlock4
  br label %afterNestedBlock3
}

define void @Bird.getSource(ptr %0, ptr %1) !rt !63 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %birdSpriteIndex = load i32, ptr %10, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %birdSpriteIndex, 9
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %birdSpriteIndex, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

mergeBlock:                                       ; No predecessors!
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %returnBlock
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %returnBlock
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %16 = getelementptr [9 x %Position.7], ptr %12, i32 0, i32 %birdSpriteIndex
  %17 = getelementptr inbounds %Position.7, ptr %16, i32 0, i32 0
  %x = load float, ptr %17, align 4
  %18 = load float, ptr %17, align 4
  store float %18, ptr %13, align 4
  %19 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %birdSpriteIndex1 = load i32, ptr %10, align 4
  %"GlobalIndexExpr::isLessThan5" = icmp slt i32 %birdSpriteIndex1, 9
  %"GlobalIndexExpr::isGreaterThan6" = icmp sge i32 %birdSpriteIndex1, 0
  %"GlobalIndexExpr::isWithinBounds7" = and i1 %"GlobalIndexExpr::isLessThan5", %"GlobalIndexExpr::isGreaterThan6"
  br i1 %"GlobalIndexExpr::isWithinBounds7", label %"GlobalIndexExpr::then2", label %"GlobalIndexExpr::else3"

"GlobalIndexExpr::then2":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge4"

"GlobalIndexExpr::else3":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge4"

"GlobalIndexExpr::merge4":                        ; preds = %"GlobalIndexExpr::else3", %"GlobalIndexExpr::then2"
  %20 = getelementptr [9 x %Position.7], ptr %12, i32 0, i32 %birdSpriteIndex1
  %21 = getelementptr inbounds %Position.7, ptr %20, i32 0, i32 1
  %y = load float, ptr %21, align 4
  %22 = load float, ptr %21, align 4
  store float %22, ptr %19, align 4
  %23 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %ACTUAL_BIRD_SIZE = load float, ptr %5, align 4
  %24 = load float, ptr %5, align 4
  store float %24, ptr %23, align 4
  %25 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %ACTUAL_BIRD_SIZE8 = load float, ptr %5, align 4
  %26 = load float, ptr %5, align 4
  store float %26, ptr %25, align 4
  ret void
}

define void @Bird.getDistination(ptr %0, ptr %1) !rt !64 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %14 = load i32, ptr @screenWidth, align 4
  %15 = sitofp i32 %14 to double
  %16 = fdiv double %15, 3.000000e+00
  %birdSize = load float, ptr %6, align 4
  %17 = load float, ptr %6, align 4
  %18 = fdiv float %17, 2.000000e+00
  %19 = fptrunc double %16 to float
  %20 = fsub float %19, %18
  store float %20, ptr %13, align 4
  %21 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %22 = load i32, ptr @screenHeight, align 4
  %23 = sitofp i32 %22 to double
  %24 = fdiv double %23, 2.000000e+00
  %birdSize1 = load float, ptr %6, align 4
  %25 = load float, ptr %6, align 4
  %26 = fdiv float %25, 2.000000e+00
  %27 = fptrunc double %24 to float
  %28 = fsub float %27, %26
  store float %28, ptr %21, align 4
  %29 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %birdSize2 = load float, ptr %6, align 4
  %30 = load float, ptr %6, align 4
  store float %30, ptr %29, align 4
  %31 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %birdSize3 = load float, ptr %6, align 4
  %32 = load float, ptr %6, align 4
  store float %32, ptr %31, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getOriginAsArray(ptr %0, ptr %1) !rt !65 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr [2 x float], ptr %0, i32 0, i32 0
  %14 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 0
  %x = load float, ptr %14, align 4
  %15 = load float, ptr %14, align 4
  store float %15, ptr %13, align 4
  %16 = getelementptr [2 x float], ptr %0, i32 0, i32 1
  %17 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  %y = load float, ptr %17, align 4
  %18 = load float, ptr %17, align 4
  store float %18, ptr %16, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getRotation(ptr %0, ptr %1) !rt !66 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 10
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  store float 0.000000e+00, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.updateY(ptr %0, ptr %1) !rt !67 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 10
  %frameTime = alloca float, align 4
  %13 = load float, ptr %0, align 4
  store float %13, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %14 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  %y = load float, ptr %14, align 4
  %15 = getelementptr inbounds %Position.7, ptr %4, i32 0, i32 1
  %y1 = load float, ptr %15, align 4
  %16 = load float, ptr %15, align 4
  %frameTime2 = load float, ptr %frameTime, align 4
  %17 = load float, ptr %frameTime, align 4
  %18 = fmul float %17, 3.010000e+02
  %19 = fadd float %16, %18
  store float %19, ptr %14, align 4
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Bird.draw(ptr %0) !rt !68 {
entry:
  %1 = load ptr, ptr %0, align 8
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
  %12 = alloca [4 x float], align 4
  %13 = alloca [4 x float], align 4
  %14 = alloca [2 x float], align 4
  %15 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %16 = load ptr, ptr @fgAnim, align 8
  %17 = getelementptr inbounds %FlowWingAnim, ptr %16, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %18, i32 0, i32 24
  %20 = load ptr, ptr %19, align 8
  call void @Bird.getSource(ptr %12, ptr %0)
  call void @Bird.getDistination(ptr %13, ptr %0)
  call void @Bird.getOriginAsArray(ptr %14, ptr %0)
  call void @Bird.getRotation(ptr %15, ptr %0)
  %21 = load ptr, ptr @fgAnim, align 8
  %22 = getelementptr inbounds %FlowWingAnim, ptr %21, i32 0, i32 5
  %23 = getelementptr inbounds %COLORS_TYPE.4, ptr %22, i32 0, i32 0
  %WHITE = load i32, ptr %23, align 4
  call void %20(ptr %2, ptr %12, ptr %13, ptr %14, ptr %15, ptr %23, ptr @fgAnim)
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Cloud.init1(ptr %0, ptr %1) !rt !69 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  %texture = alloca %Texture.9, align 8
  %6 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %6, ptr %texture, align 4
  %clPtr = alloca ptr, align 8
  %rtPtr = alloca float, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %rtPtr1 = alloca float, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %rtPtr2 = alloca float, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %rtPtr3 = alloca float, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %rtPtr4 = alloca float, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %rtPtr5 = alloca float, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %rtPtr6 = alloca float, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %rtPtr7 = alloca float, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %rtPtr8 = alloca float, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %rtPtr9 = alloca float, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock11, %nestedBlock10, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %texture, ptr %1)
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %29 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock
  %31 = getelementptr [5 x %AttributeType.11], ptr %5, i32 0, i32 0
  %32 = getelementptr inbounds %AttributeType.11, ptr %31, i32 0, i32 0
  %33 = getelementptr [4 x float], ptr %32, i32 0, i32 0
  store float 0.000000e+00, ptr %33, align 4
  %34 = getelementptr [4 x float], ptr %32, i32 0, i32 1
  store float 0.000000e+00, ptr %34, align 4
  %35 = getelementptr [4 x float], ptr %32, i32 0, i32 2
  store float 2.500000e+02, ptr %35, align 4
  %36 = getelementptr [4 x float], ptr %32, i32 0, i32 3
  store float 1.660000e+02, ptr %36, align 4
  %37 = getelementptr inbounds %AttributeType.11, ptr %31, i32 0, i32 1
  %38 = getelementptr [4 x float], ptr %37, i32 0, i32 0
  store float 0.000000e+00, ptr %38, align 4
  %39 = getelementptr [4 x float], ptr %37, i32 0, i32 1
  store float 0.000000e+00, ptr %39, align 4
  %40 = getelementptr [4 x float], ptr %37, i32 0, i32 2
  store float 0x4062D34700000000, ptr %40, align 4
  %41 = getelementptr [4 x float], ptr %37, i32 0, i32 3
  store float 1.000000e+02, ptr %41, align 4
  %42 = getelementptr inbounds %AttributeType.11, ptr %31, i32 0, i32 2
  %43 = getelementptr [2 x float], ptr %42, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %44 = load i32, ptr @screenWidth, align 4
  %45 = mul i32 -1, %44
  store i32 %45, ptr %7, align 4
  store i32 0, ptr %8, align 4
  %46 = call i32 @getRandomNumber(ptr %7, ptr %8)
  %47 = sitofp i32 %46 to float
  store float %47, ptr %43, align 4
  %48 = getelementptr [2 x float], ptr %42, i32 0, i32 1
  store i32 0, ptr %9, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %49 = load i32, ptr @screenHeight, align 4
  %50 = sitofp i32 %49 to double
  %51 = fdiv double %50, 3.000000e+00
  %52 = fptosi double %51 to i32
  store i32 %52, ptr %10, align 4
  %53 = call i32 @getRandomNumber(ptr %9, ptr %10)
  %54 = sitofp i32 %53 to float
  %55 = fmul float -1.000000e+00, %54
  store float %55, ptr %48, align 4
  %56 = getelementptr inbounds %AttributeType.11, ptr %31, i32 0, i32 3
  store float 0.000000e+00, ptr %56, align 4
  %57 = getelementptr [5 x %AttributeType.11], ptr %5, i32 0, i32 1
  %58 = getelementptr inbounds %AttributeType.11, ptr %57, i32 0, i32 0
  %59 = getelementptr [4 x float], ptr %58, i32 0, i32 0
  store float 2.500000e+02, ptr %59, align 4
  %60 = getelementptr [4 x float], ptr %58, i32 0, i32 1
  store float 0.000000e+00, ptr %60, align 4
  %61 = getelementptr [4 x float], ptr %58, i32 0, i32 2
  store float 2.500000e+02, ptr %61, align 4
  %62 = getelementptr [4 x float], ptr %58, i32 0, i32 3
  store float 1.660000e+02, ptr %62, align 4
  %63 = getelementptr inbounds %AttributeType.11, ptr %57, i32 0, i32 1
  %64 = getelementptr [4 x float], ptr %63, i32 0, i32 0
  store float 0.000000e+00, ptr %64, align 4
  %65 = getelementptr [4 x float], ptr %63, i32 0, i32 1
  store float 0.000000e+00, ptr %65, align 4
  %66 = getelementptr [4 x float], ptr %63, i32 0, i32 2
  store float 0x4062D34700000000, ptr %66, align 4
  %67 = getelementptr [4 x float], ptr %63, i32 0, i32 3
  store float 1.000000e+02, ptr %67, align 4
  %68 = getelementptr inbounds %AttributeType.11, ptr %57, i32 0, i32 2
  %69 = getelementptr [2 x float], ptr %68, i32 0, i32 0
  %screenWidth12 = load i32, ptr @screenWidth, align 4
  %70 = load i32, ptr @screenWidth, align 4
  %71 = mul i32 -1, %70
  store i32 %71, ptr %11, align 4
  store i32 0, ptr %12, align 4
  %72 = call i32 @getRandomNumber(ptr %11, ptr %12)
  %73 = sitofp i32 %72 to float
  store float %73, ptr %69, align 4
  %74 = getelementptr [2 x float], ptr %68, i32 0, i32 1
  store i32 0, ptr %13, align 4
  %screenHeight13 = load i32, ptr @screenHeight, align 4
  %75 = load i32, ptr @screenHeight, align 4
  %76 = sitofp i32 %75 to double
  %77 = fdiv double %76, 3.000000e+00
  %78 = fptosi double %77 to i32
  store i32 %78, ptr %14, align 4
  %79 = call i32 @getRandomNumber(ptr %13, ptr %14)
  %80 = sitofp i32 %79 to float
  %81 = fmul float -1.000000e+00, %80
  store float %81, ptr %74, align 4
  %82 = getelementptr inbounds %AttributeType.11, ptr %57, i32 0, i32 3
  store float 0.000000e+00, ptr %82, align 4
  %83 = getelementptr [5 x %AttributeType.11], ptr %5, i32 0, i32 2
  %84 = getelementptr inbounds %AttributeType.11, ptr %83, i32 0, i32 0
  %85 = getelementptr [4 x float], ptr %84, i32 0, i32 0
  store float 0.000000e+00, ptr %85, align 4
  %86 = getelementptr [4 x float], ptr %84, i32 0, i32 1
  store float 1.660000e+02, ptr %86, align 4
  %87 = getelementptr [4 x float], ptr %84, i32 0, i32 2
  store float 5.000000e+02, ptr %87, align 4
  %88 = getelementptr [4 x float], ptr %84, i32 0, i32 3
  store float 1.660000e+02, ptr %88, align 4
  %89 = getelementptr inbounds %AttributeType.11, ptr %83, i32 0, i32 1
  %90 = getelementptr [4 x float], ptr %89, i32 0, i32 0
  store float 0.000000e+00, ptr %90, align 4
  %91 = getelementptr [4 x float], ptr %89, i32 0, i32 1
  store float 0.000000e+00, ptr %91, align 4
  %92 = getelementptr [4 x float], ptr %89, i32 0, i32 2
  store float 0x4062D34700000000, ptr %92, align 4
  %93 = getelementptr [4 x float], ptr %89, i32 0, i32 3
  store float 1.000000e+02, ptr %93, align 4
  %94 = getelementptr inbounds %AttributeType.11, ptr %83, i32 0, i32 2
  %95 = getelementptr [2 x float], ptr %94, i32 0, i32 0
  %screenWidth14 = load i32, ptr @screenWidth, align 4
  %96 = load i32, ptr @screenWidth, align 4
  %97 = mul i32 -1, %96
  store i32 %97, ptr %15, align 4
  store i32 0, ptr %16, align 4
  %98 = call i32 @getRandomNumber(ptr %15, ptr %16)
  %99 = sitofp i32 %98 to float
  store float %99, ptr %95, align 4
  %100 = getelementptr [2 x float], ptr %94, i32 0, i32 1
  store i32 0, ptr %17, align 4
  %screenHeight15 = load i32, ptr @screenHeight, align 4
  %101 = load i32, ptr @screenHeight, align 4
  %102 = sitofp i32 %101 to double
  %103 = fdiv double %102, 3.000000e+00
  %104 = fptosi double %103 to i32
  store i32 %104, ptr %18, align 4
  %105 = call i32 @getRandomNumber(ptr %17, ptr %18)
  %106 = sitofp i32 %105 to float
  %107 = fmul float -1.000000e+00, %106
  store float %107, ptr %100, align 4
  %108 = getelementptr inbounds %AttributeType.11, ptr %83, i32 0, i32 3
  store float 0.000000e+00, ptr %108, align 4
  %109 = getelementptr [5 x %AttributeType.11], ptr %5, i32 0, i32 3
  %110 = getelementptr inbounds %AttributeType.11, ptr %109, i32 0, i32 0
  %111 = getelementptr [4 x float], ptr %110, i32 0, i32 0
  store float 0.000000e+00, ptr %111, align 4
  %112 = getelementptr [4 x float], ptr %110, i32 0, i32 1
  store float 3.320000e+02, ptr %112, align 4
  %113 = getelementptr [4 x float], ptr %110, i32 0, i32 2
  store float 2.500000e+02, ptr %113, align 4
  %114 = getelementptr [4 x float], ptr %110, i32 0, i32 3
  store float 1.660000e+02, ptr %114, align 4
  %115 = getelementptr inbounds %AttributeType.11, ptr %109, i32 0, i32 1
  %116 = getelementptr [4 x float], ptr %115, i32 0, i32 0
  store float 0.000000e+00, ptr %116, align 4
  %117 = getelementptr [4 x float], ptr %115, i32 0, i32 1
  store float 0.000000e+00, ptr %117, align 4
  %118 = getelementptr [4 x float], ptr %115, i32 0, i32 2
  store float 0x4062D34700000000, ptr %118, align 4
  %119 = getelementptr [4 x float], ptr %115, i32 0, i32 3
  store float 1.000000e+02, ptr %119, align 4
  %120 = getelementptr inbounds %AttributeType.11, ptr %109, i32 0, i32 2
  %121 = getelementptr [2 x float], ptr %120, i32 0, i32 0
  %screenWidth16 = load i32, ptr @screenWidth, align 4
  %122 = load i32, ptr @screenWidth, align 4
  %123 = mul i32 -1, %122
  store i32 %123, ptr %19, align 4
  store i32 0, ptr %20, align 4
  %124 = call i32 @getRandomNumber(ptr %19, ptr %20)
  %125 = sitofp i32 %124 to float
  store float %125, ptr %121, align 4
  %126 = getelementptr [2 x float], ptr %120, i32 0, i32 1
  store i32 0, ptr %21, align 4
  %screenHeight17 = load i32, ptr @screenHeight, align 4
  %127 = load i32, ptr @screenHeight, align 4
  %128 = sitofp i32 %127 to double
  %129 = fdiv double %128, 3.000000e+00
  %130 = fptosi double %129 to i32
  store i32 %130, ptr %22, align 4
  %131 = call i32 @getRandomNumber(ptr %21, ptr %22)
  %132 = sitofp i32 %131 to float
  %133 = fmul float -1.000000e+00, %132
  store float %133, ptr %126, align 4
  %134 = getelementptr inbounds %AttributeType.11, ptr %109, i32 0, i32 3
  store float 0.000000e+00, ptr %134, align 4
  %135 = getelementptr [5 x %AttributeType.11], ptr %5, i32 0, i32 4
  %136 = getelementptr inbounds %AttributeType.11, ptr %135, i32 0, i32 0
  %137 = getelementptr [4 x float], ptr %136, i32 0, i32 0
  store float 2.500000e+02, ptr %137, align 4
  %138 = getelementptr [4 x float], ptr %136, i32 0, i32 1
  store float 3.320000e+02, ptr %138, align 4
  %139 = getelementptr [4 x float], ptr %136, i32 0, i32 2
  store float 2.500000e+02, ptr %139, align 4
  %140 = getelementptr [4 x float], ptr %136, i32 0, i32 3
  store float 1.660000e+02, ptr %140, align 4
  %141 = getelementptr inbounds %AttributeType.11, ptr %135, i32 0, i32 1
  %142 = getelementptr [4 x float], ptr %141, i32 0, i32 0
  store float 0.000000e+00, ptr %142, align 4
  %143 = getelementptr [4 x float], ptr %141, i32 0, i32 1
  store float 0.000000e+00, ptr %143, align 4
  %144 = getelementptr [4 x float], ptr %141, i32 0, i32 2
  store float 0x4062D34700000000, ptr %144, align 4
  %145 = getelementptr [4 x float], ptr %141, i32 0, i32 3
  store float 1.000000e+02, ptr %145, align 4
  %146 = getelementptr inbounds %AttributeType.11, ptr %135, i32 0, i32 2
  %147 = getelementptr [2 x float], ptr %146, i32 0, i32 0
  %screenWidth18 = load i32, ptr @screenWidth, align 4
  %148 = load i32, ptr @screenWidth, align 4
  %149 = mul i32 -1, %148
  store i32 %149, ptr %23, align 4
  store i32 0, ptr %24, align 4
  %150 = call i32 @getRandomNumber(ptr %23, ptr %24)
  %151 = sitofp i32 %150 to float
  store float %151, ptr %147, align 4
  %152 = getelementptr [2 x float], ptr %146, i32 0, i32 1
  store i32 0, ptr %25, align 4
  %screenHeight19 = load i32, ptr @screenHeight, align 4
  %153 = load i32, ptr @screenHeight, align 4
  %154 = sitofp i32 %153 to double
  %155 = fdiv double %154, 3.000000e+00
  %156 = fptosi double %155 to i32
  store i32 %156, ptr %26, align 4
  %157 = call i32 @getRandomNumber(ptr %25, ptr %26)
  %158 = sitofp i32 %157 to float
  %159 = fmul float -1.000000e+00, %158
  store float %159, ptr %152, align 4
  %160 = getelementptr inbounds %AttributeType.11, ptr %135, i32 0, i32 3
  store float 0.000000e+00, ptr %160, align 4
  %161 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  br label %afterNestedBlock
}

define void @Cloud.update(ptr %0) !rt !70 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %i = alloca %DynamicType, align 8
  %rtPtr = alloca float, align 4
  %rtPtr1 = alloca float, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %rtPtr2 = alloca float, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block54
  ret void

nestedBlock:                                      ; preds = %entry
  %17 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %17, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock:                               ; preds = %end_block54
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock3, %nestedBlock
  %18 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock4

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %end_block54, label %decrement_block53

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %22 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %24 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %25 = sub i32 %24, 1
  store i32 %25, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %26 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %28 = icmp sge i32 %27, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %29 = icmp sle i32 %27, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %30 = phi i1 [ %28, %"ForLoop::Conditon::trueBlock" ], [ %29, %"ForLoop::Conditon::falseBlock" ]
  br i1 %30, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock3:                                ; preds = %checkContinueBlock7, %afterIfElse, %checkContinueBlock5, %"GlobalIndexExpr::merge19"
  %31 = add i32 %27, 1
  store i32 %31, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock4:                                     ; preds = %"ForLoop::loopBody"
  %32 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %33 = load i32, ptr %32, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %33, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %33, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock5:                              ; preds = %"GlobalIndexExpr::merge19"
  %34 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %nestedBlock6, label %afterNestedBlock3

nestedBlock6:                                     ; preds = %checkContinueBlock5
  %36 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %37 = load i32, ptr %36, align 4
  %"GlobalIndexExpr::isLessThan23" = icmp slt i32 %37, 5
  %"GlobalIndexExpr::isGreaterThan24" = icmp sge i32 %37, 0
  %"GlobalIndexExpr::isWithinBounds25" = and i1 %"GlobalIndexExpr::isLessThan23", %"GlobalIndexExpr::isGreaterThan24"
  br i1 %"GlobalIndexExpr::isWithinBounds25", label %"GlobalIndexExpr::then20", label %"GlobalIndexExpr::else21"

checkContinueBlock7:                              ; preds = %afterIfElse
  br label %afterNestedBlock3

"GlobalIndexExpr::then":                          ; preds = %nestedBlock4
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock4
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %38 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %33
  %39 = getelementptr inbounds %AttributeType.11, ptr %38, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then8", label %"GlobalIndexExpr::else9"

"GlobalIndexExpr::then8":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge10"

"GlobalIndexExpr::else9":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge10"

"GlobalIndexExpr::merge10":                       ; preds = %"GlobalIndexExpr::else9", %"GlobalIndexExpr::then8"
  %40 = getelementptr [2 x float], ptr %39, i32 0, i32 0
  %41 = load float, ptr %40, align 4
  %42 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %43 = load i32, ptr %42, align 4
  %"GlobalIndexExpr::isLessThan14" = icmp slt i32 %43, 5
  %"GlobalIndexExpr::isGreaterThan15" = icmp sge i32 %43, 0
  %"GlobalIndexExpr::isWithinBounds16" = and i1 %"GlobalIndexExpr::isLessThan14", %"GlobalIndexExpr::isGreaterThan15"
  br i1 %"GlobalIndexExpr::isWithinBounds16", label %"GlobalIndexExpr::then11", label %"GlobalIndexExpr::else12"

"GlobalIndexExpr::then11":                        ; preds = %"GlobalIndexExpr::merge10"
  br label %"GlobalIndexExpr::merge13"

"GlobalIndexExpr::else12":                        ; preds = %"GlobalIndexExpr::merge10"
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge13"

"GlobalIndexExpr::merge13":                       ; preds = %"GlobalIndexExpr::else12", %"GlobalIndexExpr::then11"
  %44 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %43
  %45 = getelementptr inbounds %AttributeType.11, ptr %44, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then17", label %"GlobalIndexExpr::else18"

"GlobalIndexExpr::then17":                        ; preds = %"GlobalIndexExpr::merge13"
  br label %"GlobalIndexExpr::merge19"

"GlobalIndexExpr::else18":                        ; preds = %"GlobalIndexExpr::merge13"
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge19"

"GlobalIndexExpr::merge19":                       ; preds = %"GlobalIndexExpr::else18", %"GlobalIndexExpr::then17"
  %46 = getelementptr [2 x float], ptr %45, i32 0, i32 0
  %47 = load float, ptr %46, align 4
  %48 = load ptr, ptr @fgAnim, align 8
  %49 = getelementptr inbounds %FlowWingAnim, ptr %48, i32 0, i32 0
  %50 = load ptr, ptr %49, align 8
  %51 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 11
  %52 = load ptr, ptr %51, align 8
  call void %52(ptr %rtPtr, ptr @fgAnim)
  %53 = load float, ptr %rtPtr, align 4
  %54 = fmul float %53, 1.000000e+01
  %55 = fadd float %47, %54
  store float %55, ptr %40, align 4
  %56 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %checkContinueBlock5, label %afterNestedBlock3

"GlobalIndexExpr::then20":                        ; preds = %nestedBlock6
  br label %"GlobalIndexExpr::merge22"

"GlobalIndexExpr::else21":                        ; preds = %nestedBlock6
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge22"

"GlobalIndexExpr::merge22":                       ; preds = %"GlobalIndexExpr::else21", %"GlobalIndexExpr::then20"
  %58 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %37
  %59 = getelementptr inbounds %AttributeType.11, ptr %58, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then26", label %"GlobalIndexExpr::else27"

"GlobalIndexExpr::then26":                        ; preds = %"GlobalIndexExpr::merge22"
  br label %"GlobalIndexExpr::merge28"

"GlobalIndexExpr::else27":                        ; preds = %"GlobalIndexExpr::merge22"
  call void @raise_exception(ptr @14)
  br label %"GlobalIndexExpr::merge28"

"GlobalIndexExpr::merge28":                       ; preds = %"GlobalIndexExpr::else27", %"GlobalIndexExpr::then26"
  %60 = getelementptr [2 x float], ptr %59, i32 0, i32 0
  %61 = load float, ptr %60, align 4
  %62 = fcmp ogt float %61, 2.500000e+02
  br i1 %62, label %then, label %else

then:                                             ; preds = %"GlobalIndexExpr::merge28"
  br label %nestedBlock30

else:                                             ; preds = %"GlobalIndexExpr::merge28"
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock29
  %63 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %64 = icmp eq i32 %63, 0
  br i1 %64, label %checkContinueBlock7, label %afterNestedBlock3

afterNestedBlock29:                               ; preds = %checkContinueBlock33, %"GlobalIndexExpr::merge52", %checkContinueBlock31, %"GlobalIndexExpr::merge42"
  br label %afterIfElse

nestedBlock30:                                    ; preds = %then
  %65 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %66 = load i32, ptr %65, align 4
  %"GlobalIndexExpr::isLessThan37" = icmp slt i32 %66, 5
  %"GlobalIndexExpr::isGreaterThan38" = icmp sge i32 %66, 0
  %"GlobalIndexExpr::isWithinBounds39" = and i1 %"GlobalIndexExpr::isLessThan37", %"GlobalIndexExpr::isGreaterThan38"
  br i1 %"GlobalIndexExpr::isWithinBounds39", label %"GlobalIndexExpr::then34", label %"GlobalIndexExpr::else35"

checkContinueBlock31:                             ; preds = %"GlobalIndexExpr::merge42"
  %67 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %nestedBlock32, label %afterNestedBlock29

nestedBlock32:                                    ; preds = %checkContinueBlock31
  %69 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %70 = load i32, ptr %69, align 4
  %"GlobalIndexExpr::isLessThan47" = icmp slt i32 %70, 5
  %"GlobalIndexExpr::isGreaterThan48" = icmp sge i32 %70, 0
  %"GlobalIndexExpr::isWithinBounds49" = and i1 %"GlobalIndexExpr::isLessThan47", %"GlobalIndexExpr::isGreaterThan48"
  br i1 %"GlobalIndexExpr::isWithinBounds49", label %"GlobalIndexExpr::then44", label %"GlobalIndexExpr::else45"

checkContinueBlock33:                             ; preds = %"GlobalIndexExpr::merge52"
  br label %afterNestedBlock29

"GlobalIndexExpr::then34":                        ; preds = %nestedBlock30
  br label %"GlobalIndexExpr::merge36"

"GlobalIndexExpr::else35":                        ; preds = %nestedBlock30
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge36"

"GlobalIndexExpr::merge36":                       ; preds = %"GlobalIndexExpr::else35", %"GlobalIndexExpr::then34"
  %71 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %66
  %72 = getelementptr inbounds %AttributeType.11, ptr %71, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then40", label %"GlobalIndexExpr::else41"

"GlobalIndexExpr::then40":                        ; preds = %"GlobalIndexExpr::merge36"
  br label %"GlobalIndexExpr::merge42"

"GlobalIndexExpr::else41":                        ; preds = %"GlobalIndexExpr::merge36"
  call void @raise_exception(ptr @16)
  br label %"GlobalIndexExpr::merge42"

"GlobalIndexExpr::merge42":                       ; preds = %"GlobalIndexExpr::else41", %"GlobalIndexExpr::then40"
  %73 = getelementptr [2 x float], ptr %72, i32 0, i32 0
  %74 = load float, ptr %73, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %75 = load i32, ptr @screenWidth, align 4
  %76 = mul i32 -2, %75
  store i32 %76, ptr %13, align 4
  %screenWidth43 = load i32, ptr @screenWidth, align 4
  %77 = load i32, ptr @screenWidth, align 4
  %78 = mul i32 -1, %77
  store i32 %78, ptr %14, align 4
  %79 = call i32 @getRandomNumber(ptr %13, ptr %14)
  %80 = sitofp i32 %79 to float
  store float %80, ptr %73, align 4
  %81 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock31, label %afterNestedBlock29

"GlobalIndexExpr::then44":                        ; preds = %nestedBlock32
  br label %"GlobalIndexExpr::merge46"

"GlobalIndexExpr::else45":                        ; preds = %nestedBlock32
  call void @raise_exception(ptr @17)
  br label %"GlobalIndexExpr::merge46"

"GlobalIndexExpr::merge46":                       ; preds = %"GlobalIndexExpr::else45", %"GlobalIndexExpr::then44"
  %83 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %70
  %84 = getelementptr inbounds %AttributeType.11, ptr %83, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then50", label %"GlobalIndexExpr::else51"

"GlobalIndexExpr::then50":                        ; preds = %"GlobalIndexExpr::merge46"
  br label %"GlobalIndexExpr::merge52"

"GlobalIndexExpr::else51":                        ; preds = %"GlobalIndexExpr::merge46"
  call void @raise_exception(ptr @18)
  br label %"GlobalIndexExpr::merge52"

"GlobalIndexExpr::merge52":                       ; preds = %"GlobalIndexExpr::else51", %"GlobalIndexExpr::then50"
  %85 = getelementptr [2 x float], ptr %84, i32 0, i32 1
  %86 = load float, ptr %85, align 4
  store i32 0, ptr %15, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %87 = load i32, ptr @screenHeight, align 4
  %88 = sitofp i32 %87 to double
  %89 = fdiv double %88, 3.000000e+00
  %90 = fptosi double %89 to i32
  store i32 %90, ptr %16, align 4
  %91 = call i32 @getRandomNumber(ptr %15, ptr %16)
  %92 = sitofp i32 %91 to float
  %93 = fmul float -1.000000e+00, %92
  store float %93, ptr %85, align 4
  %94 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %checkContinueBlock33, label %afterNestedBlock29

decrement_block53:                                ; preds = %"ForLoop::afterLoop"
  %96 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %97 = sub i32 %96, 1
  store i32 %97, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block54

end_block54:                                      ; preds = %decrement_block53, %"ForLoop::afterLoop"
  %98 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.draw(ptr %0) !rt !71 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %i = alloca %DynamicType, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block23
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %5, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock:                               ; preds = %end_block23
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock1, %nestedBlock
  %6 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock2

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %end_block23, label %decrement_block22

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %10 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %12 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %13 = sub i32 %12, 1
  store i32 %13, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %14 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %15 = load i32, ptr %14, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %16 = icmp sge i32 %15, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %17 = icmp sle i32 %15, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %18 = phi i1 [ %16, %"ForLoop::Conditon::trueBlock" ], [ %17, %"ForLoop::Conditon::falseBlock" ]
  br i1 %18, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock1:                                ; preds = %checkContinueBlock3, %"GlobalIndexExpr::merge18"
  %19 = add i32 %15, 1
  store i32 %19, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock2:                                     ; preds = %"ForLoop::loopBody"
  %20 = load ptr, ptr @fgAnim, align 8
  %21 = getelementptr inbounds %FlowWingAnim, ptr %20, i32 0, i32 0
  %22 = load ptr, ptr %21, align 8
  %23 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %22, i32 0, i32 24
  %24 = load ptr, ptr %23, align 8
  %25 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %26 = load i32, ptr %25, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %26, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %26, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock3:                              ; preds = %"GlobalIndexExpr::merge18"
  br label %afterNestedBlock1

"GlobalIndexExpr::then":                          ; preds = %nestedBlock2
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock2
  call void @raise_exception(ptr @19)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %27 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %26
  %28 = getelementptr inbounds %AttributeType.11, ptr %27, i32 0, i32 0
  %29 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %30 = load i32, ptr %29, align 4
  %"GlobalIndexExpr::isLessThan7" = icmp slt i32 %30, 5
  %"GlobalIndexExpr::isGreaterThan8" = icmp sge i32 %30, 0
  %"GlobalIndexExpr::isWithinBounds9" = and i1 %"GlobalIndexExpr::isLessThan7", %"GlobalIndexExpr::isGreaterThan8"
  br i1 %"GlobalIndexExpr::isWithinBounds9", label %"GlobalIndexExpr::then4", label %"GlobalIndexExpr::else5"

"GlobalIndexExpr::then4":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge6"

"GlobalIndexExpr::else5":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @20)
  br label %"GlobalIndexExpr::merge6"

"GlobalIndexExpr::merge6":                        ; preds = %"GlobalIndexExpr::else5", %"GlobalIndexExpr::then4"
  %31 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %30
  %32 = getelementptr inbounds %AttributeType.11, ptr %31, i32 0, i32 1
  %33 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %34 = load i32, ptr %33, align 4
  %"GlobalIndexExpr::isLessThan13" = icmp slt i32 %34, 5
  %"GlobalIndexExpr::isGreaterThan14" = icmp sge i32 %34, 0
  %"GlobalIndexExpr::isWithinBounds15" = and i1 %"GlobalIndexExpr::isLessThan13", %"GlobalIndexExpr::isGreaterThan14"
  br i1 %"GlobalIndexExpr::isWithinBounds15", label %"GlobalIndexExpr::then10", label %"GlobalIndexExpr::else11"

"GlobalIndexExpr::then10":                        ; preds = %"GlobalIndexExpr::merge6"
  br label %"GlobalIndexExpr::merge12"

"GlobalIndexExpr::else11":                        ; preds = %"GlobalIndexExpr::merge6"
  call void @raise_exception(ptr @21)
  br label %"GlobalIndexExpr::merge12"

"GlobalIndexExpr::merge12":                       ; preds = %"GlobalIndexExpr::else11", %"GlobalIndexExpr::then10"
  %35 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %34
  %36 = getelementptr inbounds %AttributeType.11, ptr %35, i32 0, i32 2
  %37 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %38 = load i32, ptr %37, align 4
  %"GlobalIndexExpr::isLessThan19" = icmp slt i32 %38, 5
  %"GlobalIndexExpr::isGreaterThan20" = icmp sge i32 %38, 0
  %"GlobalIndexExpr::isWithinBounds21" = and i1 %"GlobalIndexExpr::isLessThan19", %"GlobalIndexExpr::isGreaterThan20"
  br i1 %"GlobalIndexExpr::isWithinBounds21", label %"GlobalIndexExpr::then16", label %"GlobalIndexExpr::else17"

"GlobalIndexExpr::then16":                        ; preds = %"GlobalIndexExpr::merge12"
  br label %"GlobalIndexExpr::merge18"

"GlobalIndexExpr::else17":                        ; preds = %"GlobalIndexExpr::merge12"
  call void @raise_exception(ptr @22)
  br label %"GlobalIndexExpr::merge18"

"GlobalIndexExpr::merge18":                       ; preds = %"GlobalIndexExpr::else17", %"GlobalIndexExpr::then16"
  %39 = getelementptr [5 x %AttributeType.11], ptr %4, i32 0, i32 %38
  %40 = getelementptr inbounds %AttributeType.11, ptr %39, i32 0, i32 3
  %rotation = load float, ptr %40, align 4
  %41 = load ptr, ptr @fgAnim, align 8
  %42 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 5
  %43 = getelementptr inbounds %COLORS_TYPE.4, ptr %42, i32 0, i32 0
  %WHITE = load i32, ptr %43, align 4
  call void %24(ptr %2, ptr %28, ptr %32, ptr %36, ptr %40, ptr %43, ptr @fgAnim)
  %44 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock3, label %afterNestedBlock1

decrement_block22:                                ; preds = %"ForLoop::afterLoop"
  %46 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %47 = sub i32 %46, 1
  store i32 %47, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block23

end_block23:                                      ; preds = %decrement_block22, %"ForLoop::afterLoop"
  %48 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock, label %afterNestedBlock
}

define void @Ground.init1(ptr %0, ptr %1) !rt !72 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Ground, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Ground, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Ground, ptr %2, i32 0, i32 3
  %texture = alloca %Texture.9, align 8
  %6 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %6, ptr %texture, align 4
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameUnit.init1(ptr %texture, ptr %1)
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Ground.update(ptr %0) !rt !73 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Ground, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Ground, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Ground, ptr %1, i32 0, i32 3
  %rtPtr = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %5, align 4
  %6 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x1 = load float, ptr %6, align 4
  %7 = load float, ptr %6, align 4
  %8 = load ptr, ptr @fgAnim, align 8
  %9 = getelementptr inbounds %FlowWingAnim, ptr %8, i32 0, i32 0
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %10, i32 0, i32 11
  %12 = load ptr, ptr %11, align 8
  call void %12(ptr %rtPtr, ptr @fgAnim)
  %13 = load float, ptr %rtPtr, align 4
  %14 = load i32, ptr @GAME_SPEED, align 4
  %15 = sitofp i32 %14 to float
  %16 = fmul float %13, %15
  %17 = fadd float %7, %16
  store float %17, ptr %5, align 4
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Ground.setWoodTexture(ptr %0, ptr %1) !rt !74 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Ground, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Ground, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Ground, ptr %2, i32 0, i32 3
  %texture = alloca %Texture.9, align 8
  %6 = load %Texture.9, ptr %0, align 4
  store %Texture.9 %6, ptr %texture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = load %Texture.9, ptr %texture, align 4
  store %Texture.9 %7, ptr %5, align 4
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Ground.draw(ptr %0) !rt !75 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Ground, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Ground, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Ground, ptr %1, i32 0, i32 3
  %5 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %5)
  %6 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %6)
  %7 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %7)
  %8 = alloca float, align 4
  %9 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %9)
  %10 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %10)
  %11 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %11)
  %12 = alloca float, align 4
  %13 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %13)
  %14 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %14)
  %15 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %15)
  %16 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %17 = load ptr, ptr @fgAnim, align 8
  %18 = getelementptr inbounds %FlowWingAnim, ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  %20 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %19, i32 0, i32 24
  %21 = load ptr, ptr %20, align 8
  %22 = getelementptr [4 x float], ptr %5, i32 0, i32 0
  store float 3.100000e+02, ptr %22, align 4
  %23 = getelementptr [4 x float], ptr %5, i32 0, i32 1
  store float 1.250000e+03, ptr %23, align 4
  %24 = getelementptr [4 x float], ptr %5, i32 0, i32 2
  store float 4.360000e+03, ptr %24, align 4
  %25 = getelementptr [4 x float], ptr %5, i32 0, i32 3
  store float 1.250000e+03, ptr %25, align 4
  %26 = getelementptr [4 x float], ptr %6, i32 0, i32 0
  store float 0.000000e+00, ptr %26, align 4
  %27 = getelementptr [4 x float], ptr %6, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %28 = load i32, ptr @screenHeight, align 4
  %29 = sitofp i32 %28 to double
  %30 = fdiv double %29, 2.000000e+00
  %screenHeight5 = load i32, ptr @screenHeight, align 4
  %31 = load i32, ptr @screenHeight, align 4
  %32 = sitofp i32 %31 to double
  %33 = fdiv double %32, 1.000000e+01
  %34 = fadd double %30, %33
  %35 = fptrunc double %34 to float
  store float %35, ptr %27, align 4
  %36 = getelementptr [4 x float], ptr %6, i32 0, i32 2
  %screenWidth = load i32, ptr @screenWidth, align 4
  %37 = load i32, ptr @screenWidth, align 4
  %38 = sitofp i32 %37 to float
  store float %38, ptr %36, align 4
  %39 = getelementptr [4 x float], ptr %6, i32 0, i32 3
  %screenHeight6 = load i32, ptr @screenHeight, align 4
  %40 = load i32, ptr @screenHeight, align 4
  %41 = sitofp i32 %40 to double
  %42 = fdiv double %41, 2.000000e+00
  %43 = fptrunc double %42 to float
  store float %43, ptr %39, align 4
  %44 = getelementptr [2 x float], ptr %7, i32 0, i32 0
  %45 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x = load float, ptr %45, align 4
  %46 = load float, ptr %45, align 4
  %47 = fptosi float %46 to i32
  %screenWidth7 = load i32, ptr @screenWidth, align 4
  %48 = load i32, ptr @screenWidth, align 4
  %49 = srem i32 %47, %48
  %50 = sitofp i32 %49 to float
  store float %50, ptr %44, align 4
  %51 = getelementptr [2 x float], ptr %7, i32 0, i32 1
  %52 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y = load float, ptr %52, align 4
  %53 = load float, ptr %52, align 4
  store float %53, ptr %51, align 4
  store float 0.000000e+00, ptr %8, align 4
  %54 = load ptr, ptr @fgAnim, align 8
  %55 = getelementptr inbounds %FlowWingAnim, ptr %54, i32 0, i32 5
  %56 = getelementptr inbounds %COLORS_TYPE.4, ptr %55, i32 0, i32 0
  %WHITE = load i32, ptr %56, align 4
  call void %21(ptr %2, ptr %5, ptr %6, ptr %7, ptr %8, ptr %56, ptr @fgAnim)
  %57 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %59 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %61 = load ptr, ptr @fgAnim, align 8
  %62 = getelementptr inbounds %FlowWingAnim, ptr %61, i32 0, i32 0
  %63 = load ptr, ptr %62, align 8
  %64 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %63, i32 0, i32 24
  %65 = load ptr, ptr %64, align 8
  %66 = getelementptr [4 x float], ptr %9, i32 0, i32 0
  store float 3.100000e+02, ptr %66, align 4
  %67 = getelementptr [4 x float], ptr %9, i32 0, i32 1
  store float 1.250000e+03, ptr %67, align 4
  %68 = getelementptr [4 x float], ptr %9, i32 0, i32 2
  store float 4.360000e+03, ptr %68, align 4
  %69 = getelementptr [4 x float], ptr %9, i32 0, i32 3
  store float 1.250000e+03, ptr %69, align 4
  %70 = getelementptr [4 x float], ptr %10, i32 0, i32 0
  %screenWidth8 = load i32, ptr @screenWidth, align 4
  %71 = load i32, ptr @screenWidth, align 4
  %72 = sitofp i32 %71 to float
  store float %72, ptr %70, align 4
  %73 = getelementptr [4 x float], ptr %10, i32 0, i32 1
  %screenHeight9 = load i32, ptr @screenHeight, align 4
  %74 = load i32, ptr @screenHeight, align 4
  %75 = sitofp i32 %74 to double
  %76 = fdiv double %75, 2.000000e+00
  %screenHeight10 = load i32, ptr @screenHeight, align 4
  %77 = load i32, ptr @screenHeight, align 4
  %78 = sitofp i32 %77 to double
  %79 = fdiv double %78, 1.000000e+01
  %80 = fadd double %76, %79
  %81 = fptrunc double %80 to float
  store float %81, ptr %73, align 4
  %82 = getelementptr [4 x float], ptr %10, i32 0, i32 2
  %screenWidth11 = load i32, ptr @screenWidth, align 4
  %83 = load i32, ptr @screenWidth, align 4
  %84 = sitofp i32 %83 to float
  store float %84, ptr %82, align 4
  %85 = getelementptr [4 x float], ptr %10, i32 0, i32 3
  %screenHeight12 = load i32, ptr @screenHeight, align 4
  %86 = load i32, ptr @screenHeight, align 4
  %87 = sitofp i32 %86 to double
  %88 = fdiv double %87, 2.000000e+00
  %89 = fptrunc double %88 to float
  store float %89, ptr %85, align 4
  %90 = getelementptr [2 x float], ptr %11, i32 0, i32 0
  %91 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x13 = load float, ptr %91, align 4
  %92 = load float, ptr %91, align 4
  %93 = fptosi float %92 to i32
  %screenWidth14 = load i32, ptr @screenWidth, align 4
  %94 = load i32, ptr @screenWidth, align 4
  %95 = srem i32 %93, %94
  %96 = sitofp i32 %95 to float
  store float %96, ptr %90, align 4
  %97 = getelementptr [2 x float], ptr %11, i32 0, i32 1
  %98 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 1
  %y15 = load float, ptr %98, align 4
  %99 = load float, ptr %98, align 4
  store float %99, ptr %97, align 4
  store float 0.000000e+00, ptr %12, align 4
  %100 = load ptr, ptr @fgAnim, align 8
  %101 = getelementptr inbounds %FlowWingAnim, ptr %100, i32 0, i32 5
  %102 = getelementptr inbounds %COLORS_TYPE.4, ptr %101, i32 0, i32 0
  %WHITE16 = load i32, ptr %102, align 4
  call void %65(ptr %2, ptr %9, ptr %10, ptr %11, ptr %12, ptr %102, ptr @fgAnim)
  %103 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %105 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %106 = icmp eq i32 %105, 0
  br i1 %106, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %107 = load ptr, ptr @fgAnim, align 8
  %108 = getelementptr inbounds %FlowWingAnim, ptr %107, i32 0, i32 0
  %109 = load ptr, ptr %108, align 8
  %110 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %109, i32 0, i32 24
  %111 = load ptr, ptr %110, align 8
  %112 = getelementptr [4 x float], ptr %13, i32 0, i32 0
  store float 5.070000e+02, ptr %112, align 4
  %113 = getelementptr [4 x float], ptr %13, i32 0, i32 1
  store float 1.700000e+02, ptr %113, align 4
  %114 = getelementptr [4 x float], ptr %13, i32 0, i32 2
  store float 5.070000e+02, ptr %114, align 4
  %115 = getelementptr [4 x float], ptr %13, i32 0, i32 3
  store float 1.700000e+02, ptr %115, align 4
  %116 = getelementptr [4 x float], ptr %14, i32 0, i32 0
  %screenWidth17 = load i32, ptr @screenWidth, align 4
  %117 = load i32, ptr @screenWidth, align 4
  %118 = add i32 %117, 10
  %119 = sitofp i32 %118 to float
  store float %119, ptr %116, align 4
  %120 = getelementptr [4 x float], ptr %14, i32 0, i32 1
  %screenHeight18 = load i32, ptr @screenHeight, align 4
  %121 = load i32, ptr @screenHeight, align 4
  %122 = sitofp i32 %121 to double
  %123 = fdiv double %122, 2.000000e+00
  %124 = fptrunc double %123 to float
  store float %124, ptr %120, align 4
  %125 = getelementptr [4 x float], ptr %14, i32 0, i32 2
  %screenHeight19 = load i32, ptr @screenHeight, align 4
  %126 = load i32, ptr @screenHeight, align 4
  %127 = sitofp i32 %126 to double
  %128 = fdiv double %127, 2.000000e+00
  %129 = fptrunc double %128 to float
  store float %129, ptr %125, align 4
  %130 = getelementptr [4 x float], ptr %14, i32 0, i32 3
  store float 5.000000e+01, ptr %130, align 4
  %131 = getelementptr [2 x float], ptr %15, i32 0, i32 0
  store float 0.000000e+00, ptr %131, align 4
  %132 = getelementptr [2 x float], ptr %15, i32 0, i32 1
  %133 = getelementptr inbounds %Position.7, ptr %3, i32 0, i32 0
  %x20 = load float, ptr %133, align 4
  %134 = load float, ptr %133, align 4
  %135 = fptosi float %134 to i32
  %screenWidth21 = load i32, ptr @screenWidth, align 4
  %136 = load i32, ptr @screenWidth, align 4
  %137 = srem i32 %135, %136
  %138 = sitofp i32 %137 to float
  %139 = fmul float -1.000000e+00, %138
  store float %139, ptr %132, align 4
  store float 9.000000e+01, ptr %16, align 4
  %140 = load ptr, ptr @fgAnim, align 8
  %141 = getelementptr inbounds %FlowWingAnim, ptr %140, i32 0, i32 5
  %142 = getelementptr inbounds %COLORS_TYPE.4, ptr %141, i32 0, i32 0
  %WHITE22 = load i32, ptr %142, align 4
  call void %111(ptr %4, ptr %13, ptr %14, ptr %15, ptr %16, ptr %142, ptr @fgAnim)
  %143 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %144 = icmp eq i32 %143, 0
  br i1 %144, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @GameContext.init1(ptr %0, ptr %1) !rt !76 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 9
  %gameScreen = alloca i32, align 4
  %12 = load i32, ptr %0, align 4
  store i32 %12, ptr %gameScreen, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %currentGameScreen = load i32, ptr %10, align 4
  %gameScreen3 = load i32, ptr %gameScreen, align 4
  %13 = load i32, ptr %gameScreen, align 4
  store i32 %13, ptr %10, align 4
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %gameScore = load i32, ptr %11, align 4
  store i32 0, ptr %11, align 4
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @GameContext.setCurrentGameScreen(ptr %0, ptr %1) !rt !77 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 9
  %gameScreen = alloca i32, align 4
  %12 = load i32, ptr %0, align 4
  store i32 %12, ptr %gameScreen, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %currentGameScreen = load i32, ptr %10, align 4
  %gameScreen1 = load i32, ptr %gameScreen, align 4
  %13 = load i32, ptr %gameScreen, align 4
  store i32 %13, ptr %10, align 4
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @GameContext.getCurrentGameScreen(ptr %0, ptr %1) !rt !78 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 9
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %currentGameScreen = load i32, ptr %10, align 4
  %12 = load i32, ptr %10, align 4
  store i32 %12, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @GameContext.getGameScore(ptr %0, ptr %1) !rt !79 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %GameContext, ptr %2, i32 0, i32 9
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %gameScore = load i32, ptr %11, align 4
  %12 = load i32, ptr %11, align 4
  store i32 %12, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

define void @Screen.init1(ptr %0, ptr %1) !rt !80 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Screen, ptr %2, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %3, align 8
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Screen.drawScreen(ptr %0) !rt !81 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Screen, ptr %1, i32 0, i32 1
  br label %afterNestedBlock

afterNestedBlock:                                 ; preds = %entry
  ret void
}

define void @Screen.updateScreen(ptr %0) !rt !82 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Screen, ptr %1, i32 0, i32 1
  br label %afterNestedBlock

afterNestedBlock:                                 ; preds = %entry
  ret void
}

define void @MenuScreen.init1(ptr %0, ptr %1) !rt !83 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 9
  %12 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 10
  %13 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 11
  %14 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 12
  %15 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 13
  %16 = getelementptr inbounds %MenuScreen, ptr %2, i32 0, i32 14
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @Screen.init1(ptr %0, ptr %1)
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @MenuScreen.handleInput(ptr %0) !rt !84 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 10
  %12 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 11
  %13 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 12
  %14 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 13
  %15 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 14
  %rtPtr = alloca i1, align 1
  %rtPtr1 = alloca i1, align 1
  %rtPtr2 = alloca i1, align 1
  %rtPtr3 = alloca i1, align 1
  %mousePosition = alloca %Position.7, align 8
  call void @"assign_<Object<Position.7>"(ptr %mousePosition)
  %rtPtr4 = alloca %Position.7, align 8
  %startY = alloca i32, align 4
  store i32 0, ptr %startY, align 4
  %rtPtr5 = alloca i1, align 1
  %16 = alloca ptr, align 8
  %rtPtr6 = alloca i1, align 1
  %17 = alloca ptr, align 8
  %18 = alloca ptr, align 8
  %19 = alloca ptr, align 8
  %20 = alloca ptr, align 8
  %21 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock18, %afterIfElse57, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse49, %checkContinueBlock10, %afterIfElse41, %checkContinueBlock8, %afterIfElse33, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %22 = load ptr, ptr @fgAnim, align 8
  %23 = getelementptr inbounds %FlowWingAnim, ptr %22, i32 0, i32 0
  %24 = load ptr, ptr %23, align 8
  %25 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %24, i32 0, i32 0
  %26 = load ptr, ptr %25, align 8
  %27 = load ptr, ptr @fgAnim, align 8
  %28 = getelementptr inbounds %FlowWingAnim, ptr %27, i32 0, i32 6
  %29 = getelementptr inbounds %KEYS_TYPE.3, ptr %28, i32 0, i32 4
  %KEY_ENTER = load i32, ptr %29, align 4
  call void %26(ptr %rtPtr, ptr %29, ptr @fgAnim)
  %30 = load i1, ptr %rtPtr, align 1
  br i1 %30, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %31 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock
  %33 = load ptr, ptr @fgAnim, align 8
  %34 = getelementptr inbounds %FlowWingAnim, ptr %33, i32 0, i32 0
  %35 = load ptr, ptr %34, align 8
  %36 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %35, i32 0, i32 0
  %37 = load ptr, ptr %36, align 8
  %38 = load ptr, ptr @fgAnim, align 8
  %39 = getelementptr inbounds %FlowWingAnim, ptr %38, i32 0, i32 6
  %40 = getelementptr inbounds %KEYS_TYPE.3, ptr %39, i32 0, i32 2
  %KEY_DOWN = load i32, ptr %40, align 4
  call void %37(ptr %rtPtr1, ptr %40, ptr @fgAnim)
  %41 = load i1, ptr %rtPtr1, align 1
  br i1 %41, label %then31, label %else32

checkContinueBlock8:                              ; preds = %afterIfElse33
  %42 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %44 = load ptr, ptr @fgAnim, align 8
  %45 = getelementptr inbounds %FlowWingAnim, ptr %44, i32 0, i32 0
  %46 = load ptr, ptr %45, align 8
  %47 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %46, i32 0, i32 0
  %48 = load ptr, ptr %47, align 8
  %49 = load ptr, ptr @fgAnim, align 8
  %50 = getelementptr inbounds %FlowWingAnim, ptr %49, i32 0, i32 6
  %51 = getelementptr inbounds %KEYS_TYPE.3, ptr %50, i32 0, i32 3
  %KEY_UP = load i32, ptr %51, align 4
  call void %48(ptr %rtPtr2, ptr %51, ptr @fgAnim)
  %52 = load i1, ptr %rtPtr2, align 1
  br i1 %52, label %then39, label %else40

checkContinueBlock10:                             ; preds = %afterIfElse41
  %53 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %55 = load ptr, ptr @fgAnim, align 8
  %56 = getelementptr inbounds %FlowWingAnim, ptr %55, i32 0, i32 0
  %57 = load ptr, ptr %56, align 8
  %58 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %57, i32 0, i32 0
  %59 = load ptr, ptr %58, align 8
  %60 = load ptr, ptr @fgAnim, align 8
  %61 = getelementptr inbounds %FlowWingAnim, ptr %60, i32 0, i32 6
  %62 = getelementptr inbounds %KEYS_TYPE.3, ptr %61, i32 0, i32 5
  %KEY_ESCAPE = load i32, ptr %62, align 4
  call void %59(ptr %rtPtr3, ptr %62, ptr @fgAnim)
  %63 = load i1, ptr %rtPtr3, align 1
  br i1 %63, label %then47, label %else48

checkContinueBlock12:                             ; preds = %afterIfElse49
  %64 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %66 = load ptr, ptr @fgAnim, align 8
  %67 = getelementptr inbounds %FlowWingAnim, ptr %66, i32 0, i32 0
  %68 = load ptr, ptr %67, align 8
  %69 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 19
  %70 = load ptr, ptr %69, align 8
  call void %70(ptr %rtPtr4, ptr @fgAnim)
  %71 = load %Position.7, ptr %rtPtr4, align 4
  store %Position.7 %71, ptr %mousePosition, align 4
  %72 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %74 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %screenHeight = load i32, ptr @screenHeight, align 4
  %76 = load i32, ptr @screenHeight, align 4
  %77 = sitofp i32 %76 to double
  %78 = fdiv double %77, 2.000000e+00
  %79 = fptosi double %78 to i32
  %80 = sub i32 %79, 50
  store i32 %80, ptr %startY, align 4
  %81 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %83 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  store ptr @23, ptr %20, align 8
  %startY54 = load i32, ptr %startY, align 4
  call void @MenuScreen.isMouseOverText(ptr %rtPtr5, ptr %mousePosition, ptr %20, ptr %startY, ptr %0)
  %85 = load i1, ptr %rtPtr5, align 1
  br i1 %85, label %then55, label %orIf0

checkContinueBlock18:                             ; preds = %afterIfElse57
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock20

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock19
  %86 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock19:                               ; preds = %checkContinueBlock21, %afterIfElse24
  br label %afterIfElse

nestedBlock20:                                    ; preds = %then
  %selectedOption = load i32, ptr %15, align 4
  %88 = load i32, ptr %15, align 4
  %89 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %5, i32 0, i32 0
  %START = load i32, ptr %89, align 4
  %90 = load i32, ptr %89, align 4
  %91 = icmp eq i32 %88, %90
  br i1 %91, label %then22, label %else23

checkContinueBlock21:                             ; preds = %afterIfElse24
  br label %afterNestedBlock19

then22:                                           ; preds = %nestedBlock20
  br label %nestedBlock26

else23:                                           ; preds = %nestedBlock20
  br label %nestedBlock29

afterIfElse24:                                    ; preds = %afterNestedBlock28, %afterNestedBlock25
  %92 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %checkContinueBlock21, label %afterNestedBlock19

afterNestedBlock25:                               ; preds = %checkContinueBlock27, %nestedBlock26
  br label %afterIfElse24

nestedBlock26:                                    ; preds = %then22
  %94 = load ptr, ptr %2, align 8
  %95 = getelementptr inbounds %GameContext, ptr %94, i32 0, i32 0
  %96 = load ptr, ptr %95, align 8
  %97 = getelementptr inbounds %"GameContext::VTableType", ptr %96, i32 0, i32 1
  %98 = load ptr, ptr %97, align 8
  %GAME = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  call void %98(ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), ptr %2)
  %99 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %100 = icmp eq i32 %99, 0
  br i1 %100, label %checkContinueBlock27, label %afterNestedBlock25

checkContinueBlock27:                             ; preds = %nestedBlock26
  br label %afterNestedBlock25

afterNestedBlock28:                               ; preds = %checkContinueBlock30, %nestedBlock29
  br label %afterIfElse24

nestedBlock29:                                    ; preds = %else23
  %101 = load ptr, ptr %2, align 8
  %102 = getelementptr inbounds %GameContext, ptr %101, i32 0, i32 0
  %103 = load ptr, ptr %102, align 8
  %104 = getelementptr inbounds %"GameContext::VTableType", ptr %103, i32 0, i32 1
  %105 = load ptr, ptr %104, align 8
  %EXIT = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), align 4
  call void %105(ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), ptr %2)
  %106 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %checkContinueBlock30, label %afterNestedBlock28

checkContinueBlock30:                             ; preds = %nestedBlock29
  br label %afterNestedBlock28

then31:                                           ; preds = %nestedBlock7
  br label %nestedBlock35

else32:                                           ; preds = %nestedBlock7
  br label %afterIfElse33

afterIfElse33:                                    ; preds = %else32, %afterNestedBlock34
  %108 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %checkContinueBlock8, label %afterNestedBlock

afterNestedBlock34:                               ; preds = %checkContinueBlock36, %nestedBlock35
  br label %afterIfElse33

nestedBlock35:                                    ; preds = %then31
  %selectedOption37 = load i32, ptr %15, align 4
  %selectedOption38 = load i32, ptr %15, align 4
  %110 = load i32, ptr %15, align 4
  %111 = add i32 %110, 1
  %112 = srem i32 %111, 2
  store i32 %112, ptr %15, align 4
  %113 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %114 = icmp eq i32 %113, 0
  br i1 %114, label %checkContinueBlock36, label %afterNestedBlock34

checkContinueBlock36:                             ; preds = %nestedBlock35
  br label %afterNestedBlock34

then39:                                           ; preds = %nestedBlock9
  br label %nestedBlock43

else40:                                           ; preds = %nestedBlock9
  br label %afterIfElse41

afterIfElse41:                                    ; preds = %else40, %afterNestedBlock42
  %115 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %116 = icmp eq i32 %115, 0
  br i1 %116, label %checkContinueBlock10, label %afterNestedBlock

afterNestedBlock42:                               ; preds = %checkContinueBlock44, %nestedBlock43
  br label %afterIfElse41

nestedBlock43:                                    ; preds = %then39
  %selectedOption45 = load i32, ptr %15, align 4
  %selectedOption46 = load i32, ptr %15, align 4
  %117 = load i32, ptr %15, align 4
  %118 = sub i32 %117, 1
  %119 = add i32 %118, 2
  %120 = srem i32 %119, 2
  store i32 %120, ptr %15, align 4
  %121 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %122 = icmp eq i32 %121, 0
  br i1 %122, label %checkContinueBlock44, label %afterNestedBlock42

checkContinueBlock44:                             ; preds = %nestedBlock43
  br label %afterNestedBlock42

then47:                                           ; preds = %nestedBlock11
  br label %nestedBlock51

else48:                                           ; preds = %nestedBlock11
  br label %afterIfElse49

afterIfElse49:                                    ; preds = %else48, %afterNestedBlock50
  %123 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %124 = icmp eq i32 %123, 0
  br i1 %124, label %checkContinueBlock12, label %afterNestedBlock

afterNestedBlock50:                               ; preds = %checkContinueBlock52, %nestedBlock51
  br label %afterIfElse49

nestedBlock51:                                    ; preds = %then47
  %125 = load ptr, ptr %2, align 8
  %126 = getelementptr inbounds %GameContext, ptr %125, i32 0, i32 0
  %127 = load ptr, ptr %126, align 8
  %128 = getelementptr inbounds %"GameContext::VTableType", ptr %127, i32 0, i32 1
  %129 = load ptr, ptr %128, align 8
  %EXIT53 = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), align 4
  call void %129(ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), ptr %2)
  %130 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %131 = icmp eq i32 %130, 0
  br i1 %131, label %checkContinueBlock52, label %afterNestedBlock50

checkContinueBlock52:                             ; preds = %nestedBlock51
  br label %afterNestedBlock50

then55:                                           ; preds = %nestedBlock17
  br label %nestedBlock60

orIf0:                                            ; preds = %nestedBlock17
  store ptr @24, ptr %21, align 8
  %startY58 = load i32, ptr %startY, align 4
  call void @MenuScreen.isMouseOverText(ptr %rtPtr6, ptr %mousePosition, ptr %21, ptr %startY, ptr %0)
  %132 = icmp eq ptr %rtPtr6, null
  br i1 %132, label %"BoolTC::NullBlock", label %"BoolTC::NotNullBlock"

orIfThen0:                                        ; preds = %"BoolTC::MergeBlock"
  br label %nestedBlock65

else56:                                           ; preds = %"BoolTC::MergeBlock"
  br label %afterIfElse57

afterIfElse57:                                    ; preds = %else56, %afterNestedBlock64, %afterNestedBlock59
  %133 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %134 = icmp eq i32 %133, 0
  br i1 %134, label %checkContinueBlock18, label %afterNestedBlock

"BoolTC::NullBlock":                              ; preds = %orIf0
  br label %"BoolTC::MergeBlock"

"BoolTC::NotNullBlock":                           ; preds = %orIf0
  %135 = call i32 @string_length(ptr %rtPtr6)
  %136 = icmp eq i32 %135, 0
  %137 = select i1 %136, i1 false, i1 true
  br label %"BoolTC::MergeBlock"

"BoolTC::MergeBlock":                             ; preds = %"BoolTC::NotNullBlock", %"BoolTC::NullBlock"
  %138 = phi i1 [ false, %"BoolTC::NullBlock" ], [ %137, %"BoolTC::NotNullBlock" ]
  br i1 %138, label %orIfThen0, label %else56

afterNestedBlock59:                               ; preds = %checkContinueBlock61, %nestedBlock60
  br label %afterIfElse57

nestedBlock60:                                    ; preds = %then55
  %selectedOption62 = load i32, ptr %15, align 4
  %139 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %5, i32 0, i32 0
  %START63 = load i32, ptr %139, align 4
  %140 = load i32, ptr %139, align 4
  store i32 %140, ptr %15, align 4
  %141 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %142 = icmp eq i32 %141, 0
  br i1 %142, label %checkContinueBlock61, label %afterNestedBlock59

checkContinueBlock61:                             ; preds = %nestedBlock60
  br label %afterNestedBlock59

afterNestedBlock64:                               ; preds = %checkContinueBlock66, %nestedBlock65
  br label %afterIfElse57

nestedBlock65:                                    ; preds = %orIfThen0
  %selectedOption67 = load i32, ptr %15, align 4
  %143 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %5, i32 0, i32 1
  %EXIT68 = load i32, ptr %143, align 4
  %144 = load i32, ptr %143, align 4
  store i32 %144, ptr %15, align 4
  %145 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %146 = icmp eq i32 %145, 0
  br i1 %146, label %checkContinueBlock66, label %afterNestedBlock64

checkContinueBlock66:                             ; preds = %nestedBlock65
  br label %afterNestedBlock64
}

define void @MenuScreen.updateScreen(ptr %0) !rt !85 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 10
  %12 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 11
  %13 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 12
  %14 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 13
  %15 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 14
  %rtPtr = alloca double, align 8
  %rtPtr1 = alloca float, align 4
  %rtPtr2 = alloca float, align 4
  %16 = alloca double, align 8
  %rtPtr3 = alloca double, align 8
  %rtPtr4 = alloca float, align 4
  %17 = alloca double, align 8
  %rtPtr5 = alloca double, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock23, %afterIfElse, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %nestedBlock10, %checkContinueBlock9, %nestedBlock8, %checkContinueBlock7, %nestedBlock6, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @MenuScreen.handleInput(ptr %0)
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %20 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock
  %timeValue = load double, ptr %7, align 8
  %22 = load ptr, ptr @fgAnim, align 8
  %23 = getelementptr inbounds %FlowWingAnim, ptr %22, i32 0, i32 0
  %24 = load ptr, ptr %23, align 8
  %25 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %24, i32 0, i32 13
  %26 = load ptr, ptr %25, align 8
  call void %26(ptr %rtPtr, ptr @fgAnim)
  %27 = load double, ptr %rtPtr, align 8
  %28 = fmul double %27, 1.000000e+01
  store double %28, ptr %7, align 8
  %29 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %31 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  %glowOffset = load float, ptr %8, align 4
  %timeValue24 = load double, ptr %7, align 8
  %33 = call double @getSin(ptr %7)
  %34 = fptrunc double %33 to float
  %35 = fmul float %34, 1.000000e+00
  store float %35, ptr %8, align 4
  %36 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock9, label %afterNestedBlock

checkContinueBlock9:                              ; preds = %nestedBlock8
  %38 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %startY = load i32, ptr %9, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %40 = load i32, ptr @screenHeight, align 4
  %41 = sitofp i32 %40 to double
  %42 = fdiv double %41, 2.000000e+00
  %43 = fptosi double %42 to i32
  %44 = sub i32 %43, 50
  store i32 %44, ptr %9, align 4
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %47 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %startColor = load i32, ptr %10, align 4
  %NORMAL_COLOR = load i32, ptr @NORMAL_COLOR, align 4
  %49 = load i32, ptr @NORMAL_COLOR, align 4
  store i32 %49, ptr %10, align 4
  %50 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %52 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %exitColor = load i32, ptr %11, align 4
  %NORMAL_COLOR25 = load i32, ptr @NORMAL_COLOR, align 4
  %54 = load i32, ptr @NORMAL_COLOR, align 4
  store i32 %54, ptr %11, align 4
  %55 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %57 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %glowOffsetForStartText = load float, ptr %12, align 4
  %59 = load ptr, ptr @fgAnim, align 8
  %60 = getelementptr inbounds %FlowWingAnim, ptr %59, i32 0, i32 0
  %61 = load ptr, ptr %60, align 8
  %62 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %61, i32 0, i32 13
  %63 = load ptr, ptr %62, align 8
  call void %63(ptr %rtPtr3, ptr @fgAnim)
  %64 = load double, ptr %rtPtr3, align 8
  %65 = fmul double %64, 2.000000e+01
  store double %65, ptr %16, align 8
  %66 = call double @getSin(ptr %16)
  %67 = fptrunc double %66 to float
  %68 = fmul float %67, 1.000000e+00
  store float %68, ptr %12, align 4
  %69 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %71 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %glowOffsetForExitText = load float, ptr %13, align 4
  %73 = load ptr, ptr @fgAnim, align 8
  %74 = getelementptr inbounds %FlowWingAnim, ptr %73, i32 0, i32 0
  %75 = load ptr, ptr %74, align 8
  %76 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %75, i32 0, i32 13
  %77 = load ptr, ptr %76, align 8
  call void %77(ptr %rtPtr5, ptr @fgAnim)
  %78 = load double, ptr %rtPtr5, align 8
  %79 = fmul double %78, 2.000000e+01
  store double %79, ptr %17, align 8
  %80 = call double @getSin(ptr %17)
  %81 = fptrunc double %80 to float
  %82 = fmul float %81, 1.000000e+00
  store float %82, ptr %13, align 4
  %83 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  %85 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %padding = load i32, ptr %14, align 4
  store i32 0, ptr %14, align 4
  %87 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %88 = icmp eq i32 %87, 0
  br i1 %88, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %89 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %90 = icmp eq i32 %89, 0
  br i1 %90, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %selectedOption = load i32, ptr %15, align 4
  %91 = load i32, ptr %15, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %then, label %else

checkContinueBlock23:                             ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock22
  br label %nestedBlock27

else:                                             ; preds = %nestedBlock22
  br label %nestedBlock37

afterIfElse:                                      ; preds = %afterNestedBlock36, %afterNestedBlock26
  %93 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %94 = icmp eq i32 %93, 0
  br i1 %94, label %checkContinueBlock23, label %afterNestedBlock

afterNestedBlock26:                               ; preds = %checkContinueBlock32, %nestedBlock31, %checkContinueBlock30, %nestedBlock29, %checkContinueBlock28, %nestedBlock27
  br label %afterIfElse

nestedBlock27:                                    ; preds = %then
  %padding33 = load i32, ptr %14, align 4
  store i32 -5, ptr %14, align 4
  %95 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %96 = icmp eq i32 %95, 0
  br i1 %96, label %checkContinueBlock28, label %afterNestedBlock26

checkContinueBlock28:                             ; preds = %nestedBlock27
  %97 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %98 = icmp eq i32 %97, 0
  br i1 %98, label %nestedBlock29, label %afterNestedBlock26

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %startColor34 = load i32, ptr %10, align 4
  %HOVER_COLOR = load i32, ptr @HOVER_COLOR, align 4
  %99 = load i32, ptr @HOVER_COLOR, align 4
  store i32 %99, ptr %10, align 4
  %100 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %checkContinueBlock30, label %afterNestedBlock26

checkContinueBlock30:                             ; preds = %nestedBlock29
  %102 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %103 = icmp eq i32 %102, 0
  br i1 %103, label %nestedBlock31, label %afterNestedBlock26

nestedBlock31:                                    ; preds = %checkContinueBlock30
  %glowOffsetForExitText35 = load float, ptr %13, align 4
  store float 0.000000e+00, ptr %13, align 4
  %104 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %105 = icmp eq i32 %104, 0
  br i1 %105, label %checkContinueBlock32, label %afterNestedBlock26

checkContinueBlock32:                             ; preds = %nestedBlock31
  br label %afterNestedBlock26

afterNestedBlock36:                               ; preds = %checkContinueBlock40, %nestedBlock39, %checkContinueBlock38, %nestedBlock37
  br label %afterIfElse

nestedBlock37:                                    ; preds = %else
  %exitColor41 = load i32, ptr %11, align 4
  %HOVER_COLOR42 = load i32, ptr @HOVER_COLOR, align 4
  %106 = load i32, ptr @HOVER_COLOR, align 4
  store i32 %106, ptr %11, align 4
  %107 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %checkContinueBlock38, label %afterNestedBlock36

checkContinueBlock38:                             ; preds = %nestedBlock37
  %109 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %110 = icmp eq i32 %109, 0
  br i1 %110, label %nestedBlock39, label %afterNestedBlock36

nestedBlock39:                                    ; preds = %checkContinueBlock38
  %glowOffsetForStartText43 = load float, ptr %12, align 4
  store float 0.000000e+00, ptr %12, align 4
  %111 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %112 = icmp eq i32 %111, 0
  br i1 %112, label %checkContinueBlock40, label %afterNestedBlock36

checkContinueBlock40:                             ; preds = %nestedBlock39
  br label %afterNestedBlock36
}

define void @MenuScreen.drawScreen(ptr %0) !rt !86 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 9
  %11 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 10
  %12 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 11
  %13 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 12
  %14 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 13
  %15 = getelementptr inbounds %MenuScreen, ptr %1, i32 0, i32 14
  %bird = alloca ptr, align 8
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca ptr, align 8
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i32, align 4
  %28 = alloca i32, align 4
  %29 = alloca i32, align 4
  %30 = alloca ptr, align 8
  %31 = alloca i32, align 4
  %32 = alloca i32, align 4
  %33 = alloca i32, align 4
  %34 = alloca ptr, align 8
  %35 = alloca i32, align 4
  %36 = alloca i32, align 4
  %37 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %38 = load ptr, ptr %2, align 8
  %39 = getelementptr inbounds %GameContext, ptr %38, i32 0, i32 1
  %40 = load ptr, ptr %39, align 8
  store ptr %40, ptr %bird, align 8
  %41 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %43 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %45 = load ptr, ptr %bird, align 8
  %46 = getelementptr inbounds %Bird, ptr %45, i32 0, i32 0
  %47 = load ptr, ptr %46, align 8
  %48 = getelementptr inbounds %"Bird::VTableType", ptr %47, i32 0, i32 2
  %49 = load ptr, ptr %48, align 8
  call void %49(ptr %bird)
  %50 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %52 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %54 = load ptr, ptr @fgAnim, align 8
  %55 = getelementptr inbounds %FlowWingAnim, ptr %54, i32 0, i32 0
  %56 = load ptr, ptr %55, align 8
  %57 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %56, i32 0, i32 17
  %58 = load ptr, ptr %57, align 8
  store i32 20, ptr %16, align 4
  store i32 20, ptr %17, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %59 = load i32, ptr @screenWidth, align 4
  %60 = sub i32 %59, 40
  store i32 %60, ptr %18, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %61 = load i32, ptr @screenHeight, align 4
  %62 = sub i32 %61, 40
  store i32 %62, ptr %19, align 4
  %63 = load ptr, ptr @fgAnim, align 8
  %64 = getelementptr inbounds %FlowWingAnim, ptr %63, i32 0, i32 5
  %65 = getelementptr inbounds %COLORS_TYPE.4, ptr %64, i32 0, i32 5
  %TRANSPARENT = load i32, ptr %65, align 4
  call void %58(ptr %16, ptr %17, ptr %18, ptr %19, ptr %65, ptr @fgAnim)
  %66 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %68 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %70 = load ptr, ptr @fgAnim, align 8
  %71 = getelementptr inbounds %FlowWingAnim, ptr %70, i32 0, i32 0
  %72 = load ptr, ptr %71, align 8
  %73 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %72, i32 0, i32 4
  %74 = load ptr, ptr %73, align 8
  store ptr @25, ptr %20, align 8
  %screenWidth15 = load i32, ptr @screenWidth, align 4
  %75 = load i32, ptr @screenWidth, align 4
  %76 = sitofp i32 %75 to double
  %77 = fdiv double %76, 2.000000e+00
  %78 = load ptr, ptr @fgAnim, align 8
  %79 = getelementptr inbounds %FlowWingAnim, ptr %78, i32 0, i32 0
  %80 = load ptr, ptr %79, align 8
  %81 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %80, i32 0, i32 8
  %82 = load ptr, ptr %81, align 8
  %83 = call i32 %82(ptr @26, i32 60, ptr @fgAnim)
  %84 = sitofp i32 %83 to double
  %85 = fdiv double %84, 2.000000e+00
  %86 = fsub double %77, %85
  %87 = fptosi double %86 to i32
  store i32 %87, ptr %21, align 4
  %screenHeight16 = load i32, ptr @screenHeight, align 4
  %88 = load i32, ptr @screenHeight, align 4
  %89 = sitofp i32 %88 to double
  %90 = fdiv double %89, 2.000000e+00
  %91 = fsub double %90, 1.500000e+02
  %92 = fptosi double %91 to i32
  store i32 %92, ptr %22, align 4
  store i32 60, ptr %23, align 4
  %93 = load ptr, ptr @fgAnim, align 8
  %94 = getelementptr inbounds %FlowWingAnim, ptr %93, i32 0, i32 5
  %95 = getelementptr inbounds %COLORS_TYPE.4, ptr %94, i32 0, i32 4
  %DARKBLUE = load i32, ptr %95, align 4
  call void %74(ptr %20, ptr %21, ptr %22, ptr %23, ptr %95, ptr @fgAnim)
  %96 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %97 = icmp eq i32 %96, 0
  br i1 %97, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %98 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %100 = load ptr, ptr @fgAnim, align 8
  %101 = getelementptr inbounds %FlowWingAnim, ptr %100, i32 0, i32 0
  %102 = load ptr, ptr %101, align 8
  %103 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %102, i32 0, i32 4
  %104 = load ptr, ptr %103, align 8
  %START_TEXT = load ptr, ptr %3, align 8
  %screenWidth17 = load i32, ptr @screenWidth, align 4
  %105 = load i32, ptr @screenWidth, align 4
  %106 = sitofp i32 %105 to double
  %107 = fdiv double %106, 2.000000e+00
  %108 = load ptr, ptr @fgAnim, align 8
  %109 = getelementptr inbounds %FlowWingAnim, ptr %108, i32 0, i32 0
  %110 = load ptr, ptr %109, align 8
  %111 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %110, i32 0, i32 8
  %112 = load ptr, ptr %111, align 8
  %START_TEXT18 = load ptr, ptr %3, align 8
  %113 = load ptr, ptr %3, align 8
  %114 = call i32 %112(ptr %113, i32 20, ptr @fgAnim)
  %115 = sitofp i32 %114 to double
  %116 = fdiv double %115, 2.000000e+00
  %117 = fsub double %107, %116
  %glowOffsetForStartText = load float, ptr %12, align 4
  %118 = load float, ptr %12, align 4
  %119 = fptrunc double %117 to float
  %120 = fadd float %119, %118
  %121 = fptosi float %120 to i32
  store i32 %121, ptr %24, align 4
  %startY = load i32, ptr %9, align 4
  %122 = load i32, ptr %9, align 4
  %padding = load i32, ptr %14, align 4
  %123 = load i32, ptr %14, align 4
  %124 = add i32 %122, %123
  %glowOffsetForStartText19 = load float, ptr %12, align 4
  %125 = load float, ptr %12, align 4
  %126 = sitofp i32 %124 to float
  %127 = fadd float %126, %125
  %128 = fptosi float %127 to i32
  store i32 %128, ptr %25, align 4
  store i32 20, ptr %26, align 4
  %startColor = load i32, ptr %10, align 4
  call void %104(ptr %3, ptr %24, ptr %25, ptr %26, ptr %10, ptr @fgAnim)
  %129 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %131 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %132 = icmp eq i32 %131, 0
  br i1 %132, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %133 = load ptr, ptr @fgAnim, align 8
  %134 = getelementptr inbounds %FlowWingAnim, ptr %133, i32 0, i32 0
  %135 = load ptr, ptr %134, align 8
  %136 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %135, i32 0, i32 4
  %137 = load ptr, ptr %136, align 8
  %EXIT_TEXT = load ptr, ptr %4, align 8
  %screenWidth20 = load i32, ptr @screenWidth, align 4
  %138 = load i32, ptr @screenWidth, align 4
  %139 = sitofp i32 %138 to double
  %140 = fdiv double %139, 2.000000e+00
  %141 = load ptr, ptr @fgAnim, align 8
  %142 = getelementptr inbounds %FlowWingAnim, ptr %141, i32 0, i32 0
  %143 = load ptr, ptr %142, align 8
  %144 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %143, i32 0, i32 8
  %145 = load ptr, ptr %144, align 8
  %EXIT_TEXT21 = load ptr, ptr %4, align 8
  %146 = load ptr, ptr %4, align 8
  %147 = call i32 %145(ptr %146, i32 20, ptr @fgAnim)
  %148 = sitofp i32 %147 to double
  %149 = fdiv double %148, 2.000000e+00
  %150 = fsub double %140, %149
  %glowOffsetForExitText = load float, ptr %13, align 4
  %151 = load float, ptr %13, align 4
  %152 = fptrunc double %150 to float
  %153 = fadd float %152, %151
  %154 = fptosi float %153 to i32
  store i32 %154, ptr %27, align 4
  %startY22 = load i32, ptr %9, align 4
  %155 = load i32, ptr %9, align 4
  %OPTION_HEIGHT = load i32, ptr %6, align 4
  %156 = load i32, ptr %6, align 4
  %157 = add i32 %155, %156
  %158 = add i32 %157, 10
  %padding23 = load i32, ptr %14, align 4
  %159 = load i32, ptr %14, align 4
  %160 = add i32 %158, %159
  %glowOffsetForExitText24 = load float, ptr %13, align 4
  %161 = load float, ptr %13, align 4
  %162 = sitofp i32 %160 to float
  %163 = fadd float %162, %161
  %164 = fptosi float %163 to i32
  store i32 %164, ptr %28, align 4
  store i32 20, ptr %29, align 4
  %exitColor = load i32, ptr %11, align 4
  call void %137(ptr %4, ptr %27, ptr %28, ptr %29, ptr %11, ptr @fgAnim)
  %165 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %166 = icmp eq i32 %165, 0
  br i1 %166, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %167 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %168 = icmp eq i32 %167, 0
  br i1 %168, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %169 = load ptr, ptr @fgAnim, align 8
  %170 = getelementptr inbounds %FlowWingAnim, ptr %169, i32 0, i32 0
  %171 = load ptr, ptr %170, align 8
  %172 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %171, i32 0, i32 4
  %173 = load ptr, ptr %172, align 8
  store ptr @27, ptr %30, align 8
  %screenWidth25 = load i32, ptr @screenWidth, align 4
  %174 = load i32, ptr @screenWidth, align 4
  %175 = sitofp i32 %174 to double
  %176 = fdiv double %175, 2.000000e+00
  %177 = load ptr, ptr @fgAnim, align 8
  %178 = getelementptr inbounds %FlowWingAnim, ptr %177, i32 0, i32 0
  %179 = load ptr, ptr %178, align 8
  %180 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %179, i32 0, i32 8
  %181 = load ptr, ptr %180, align 8
  %182 = call i32 %181(ptr @28, i32 20, ptr @fgAnim)
  %183 = sitofp i32 %182 to double
  %184 = fdiv double %183, 2.000000e+00
  %185 = fsub double %176, %184
  %186 = fptosi double %185 to i32
  store i32 %186, ptr %31, align 4
  %screenHeight26 = load i32, ptr @screenHeight, align 4
  %187 = load i32, ptr @screenHeight, align 4
  %188 = sitofp i32 %187 to double
  %189 = fdiv double %188, 2.000000e+00
  %190 = fadd double %189, 5.000000e+01
  %191 = fptosi double %190 to i32
  store i32 %191, ptr %32, align 4
  store i32 20, ptr %33, align 4
  %192 = load ptr, ptr @fgAnim, align 8
  %193 = getelementptr inbounds %FlowWingAnim, ptr %192, i32 0, i32 5
  %194 = getelementptr inbounds %COLORS_TYPE.4, ptr %193, i32 0, i32 7
  %GRAY = load i32, ptr %194, align 4
  call void %173(ptr %30, ptr %31, ptr %32, ptr %33, ptr %194, ptr @fgAnim)
  %195 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %196 = icmp eq i32 %195, 0
  br i1 %196, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %197 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %198 = icmp eq i32 %197, 0
  br i1 %198, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %199 = load ptr, ptr @fgAnim, align 8
  %200 = getelementptr inbounds %FlowWingAnim, ptr %199, i32 0, i32 0
  %201 = load ptr, ptr %200, align 8
  %202 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %201, i32 0, i32 4
  %203 = load ptr, ptr %202, align 8
  store ptr @29, ptr %34, align 8
  %screenWidth27 = load i32, ptr @screenWidth, align 4
  %204 = load i32, ptr @screenWidth, align 4
  %205 = sitofp i32 %204 to double
  %206 = fdiv double %205, 2.000000e+00
  %207 = load ptr, ptr @fgAnim, align 8
  %208 = getelementptr inbounds %FlowWingAnim, ptr %207, i32 0, i32 0
  %209 = load ptr, ptr %208, align 8
  %210 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %209, i32 0, i32 8
  %211 = load ptr, ptr %210, align 8
  %212 = call i32 %211(ptr @30, i32 20, ptr @fgAnim)
  %213 = sitofp i32 %212 to double
  %214 = fdiv double %213, 2.000000e+00
  %215 = fsub double %206, %214
  %216 = fptosi double %215 to i32
  store i32 %216, ptr %35, align 4
  %screenHeight28 = load i32, ptr @screenHeight, align 4
  %217 = load i32, ptr @screenHeight, align 4
  %218 = sitofp i32 %217 to double
  %219 = fdiv double %218, 2.000000e+00
  %220 = fadd double %219, 8.000000e+01
  %221 = fptosi double %220 to i32
  store i32 %221, ptr %36, align 4
  store i32 20, ptr %37, align 4
  %222 = load ptr, ptr @fgAnim, align 8
  %223 = getelementptr inbounds %FlowWingAnim, ptr %222, i32 0, i32 5
  %224 = getelementptr inbounds %COLORS_TYPE.4, ptr %223, i32 0, i32 7
  %GRAY29 = load i32, ptr %224, align 4
  call void %203(ptr %34, ptr %35, ptr %36, ptr %37, ptr %224, ptr @fgAnim)
  %225 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %226 = icmp eq i32 %225, 0
  br i1 %226, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock
}

define void @MenuScreen.isMouseOverText(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !87 {
entry:
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 4
  %10 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 5
  %11 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 6
  %12 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 7
  %13 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 8
  %14 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 9
  %15 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 10
  %16 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 11
  %17 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 12
  %18 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 13
  %19 = getelementptr inbounds %MenuScreen, ptr %5, i32 0, i32 14
  %mousePosition = alloca %Position.7, align 8
  %20 = load %Position.7, ptr %1, align 4
  store %Position.7 %20, ptr %mousePosition, align 4
  %text = alloca ptr, align 8
  %21 = load ptr, ptr %2, align 8
  store ptr %21, ptr %text, align 8
  %y = alloca i32, align 4
  %22 = load i32, ptr %3, align 4
  store i32 %22, ptr %y, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %23 = getelementptr inbounds %Position.7, ptr %mousePosition, i32 0, i32 0
  %x = load float, ptr %23, align 4
  %24 = load float, ptr %23, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %25 = load i32, ptr @screenWidth, align 4
  %26 = sitofp i32 %25 to double
  %27 = fdiv double %26, 2.000000e+00
  %28 = load ptr, ptr @fgAnim, align 8
  %29 = getelementptr inbounds %FlowWingAnim, ptr %28, i32 0, i32 0
  %30 = load ptr, ptr %29, align 8
  %31 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %30, i32 0, i32 8
  %32 = load ptr, ptr %31, align 8
  %text1 = load ptr, ptr %text, align 8
  %33 = load ptr, ptr %text, align 8
  %34 = call i32 %32(ptr %33, i32 20, ptr @fgAnim)
  %35 = sitofp i32 %34 to double
  %36 = fdiv double %35, 2.000000e+00
  %37 = fsub double %27, %36
  %38 = fptrunc double %37 to float
  %39 = fcmp oge float %24, %38
  %40 = getelementptr inbounds %Position.7, ptr %mousePosition, i32 0, i32 0
  %x2 = load float, ptr %40, align 4
  %41 = load float, ptr %40, align 4
  %screenWidth3 = load i32, ptr @screenWidth, align 4
  %42 = load i32, ptr @screenWidth, align 4
  %43 = sitofp i32 %42 to double
  %44 = fdiv double %43, 2.000000e+00
  %45 = load ptr, ptr @fgAnim, align 8
  %46 = getelementptr inbounds %FlowWingAnim, ptr %45, i32 0, i32 0
  %47 = load ptr, ptr %46, align 8
  %48 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %47, i32 0, i32 8
  %49 = load ptr, ptr %48, align 8
  %text4 = load ptr, ptr %text, align 8
  %50 = load ptr, ptr %text, align 8
  %51 = call i32 %49(ptr %50, i32 20, ptr @fgAnim)
  %52 = sitofp i32 %51 to double
  %53 = fdiv double %52, 2.000000e+00
  %54 = fadd double %44, %53
  %55 = fptrunc double %54 to float
  %56 = fcmp ole float %41, %55
  %57 = select i1 %39, i1 %56, i1 false
  %58 = getelementptr inbounds %Position.7, ptr %mousePosition, i32 0, i32 1
  %y5 = load float, ptr %58, align 4
  %59 = load float, ptr %58, align 4
  %y6 = load i32, ptr %y, align 4
  %60 = load i32, ptr %y, align 4
  %61 = sitofp i32 %60 to float
  %62 = fcmp oge float %59, %61
  %63 = select i1 %57, i1 %62, i1 false
  %64 = getelementptr inbounds %Position.7, ptr %mousePosition, i32 0, i32 1
  %y7 = load float, ptr %64, align 4
  %65 = load float, ptr %64, align 4
  %y8 = load i32, ptr %y, align 4
  %66 = load i32, ptr %y, align 4
  %OPTION_HEIGHT = load i32, ptr %10, align 4
  %67 = load i32, ptr %10, align 4
  %68 = add i32 %66, %67
  %69 = sitofp i32 %68 to float
  %70 = fcmp ole float %65, %69
  %71 = select i1 %63, i1 %70, i1 false
  store i1 %71, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %72 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %checkContinueBlock, label %afterNestedBlock
}

define void @GameScreen.init1(ptr %0, ptr %1) !rt !88 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %GameScreen, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %GameScreen, ptr %2, i32 0, i32 2
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @Screen.init1(ptr %0, ptr %1)
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @GameScreen.drawScreen(ptr %0) !rt !89 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GameScreen, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GameScreen, ptr %1, i32 0, i32 2
  %cloud = alloca ptr, align 8
  %heightedMountain = alloca ptr, align 8
  %greenMountain = alloca ptr, align 8
  %blackMountain = alloca ptr, align 8
  %wideMountain = alloca ptr, align 8
  %ground = alloca ptr, align 8
  %bird = alloca ptr, align 8
  %rtPtr = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock30, %afterIfElse, %checkContinueBlock28, %nestedBlock27, %checkContinueBlock26, %nestedBlock25, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %nestedBlock19, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %13 = load ptr, ptr @fgAnim, align 8
  %14 = getelementptr inbounds %FlowWingAnim, ptr %13, i32 0, i32 0
  %15 = load ptr, ptr %14, align 8
  %16 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %15, i32 0, i32 12
  %17 = load ptr, ptr %16, align 8
  %18 = load ptr, ptr @fgAnim, align 8
  %19 = getelementptr inbounds %FlowWingAnim, ptr %18, i32 0, i32 5
  %20 = getelementptr inbounds %COLORS_TYPE.4, ptr %19, i32 0, i32 8
  %RAYWHITE = load i32, ptr %20, align 4
  call void %17(ptr %20, ptr @fgAnim)
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %25 = load ptr, ptr %2, align 8
  %26 = getelementptr inbounds %GameContext, ptr %25, i32 0, i32 2
  %27 = load ptr, ptr %26, align 8
  store ptr %27, ptr %cloud, align 8
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %32 = load ptr, ptr %cloud, align 8
  %33 = getelementptr inbounds %Cloud, ptr %32, i32 0, i32 0
  %34 = load ptr, ptr %33, align 8
  %35 = getelementptr inbounds %"Cloud::VTableType", ptr %34, i32 0, i32 2
  %36 = load ptr, ptr %35, align 8
  call void %36(ptr %cloud)
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %39 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %41 = load ptr, ptr %2, align 8
  %42 = getelementptr inbounds %GameContext, ptr %41, i32 0, i32 5
  %43 = load ptr, ptr %42, align 8
  store ptr %43, ptr %heightedMountain, align 8
  %44 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %46 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %48 = load ptr, ptr %heightedMountain, align 8
  %49 = getelementptr inbounds %HeightedMountain, ptr %48, i32 0, i32 0
  %50 = load ptr, ptr %49, align 8
  %51 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %50, i32 0, i32 2
  %52 = load ptr, ptr %51, align 8
  call void %52(ptr %heightedMountain)
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %55 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %57 = load ptr, ptr %2, align 8
  %58 = getelementptr inbounds %GameContext, ptr %57, i32 0, i32 6
  %59 = load ptr, ptr %58, align 8
  store ptr %59, ptr %greenMountain, align 8
  %60 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %62 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %63 = icmp eq i32 %62, 0
  br i1 %63, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %64 = load ptr, ptr %greenMountain, align 8
  %65 = getelementptr inbounds %GreenMountain, ptr %64, i32 0, i32 0
  %66 = load ptr, ptr %65, align 8
  %67 = getelementptr inbounds %"GreenMountain::VTableType", ptr %66, i32 0, i32 2
  %68 = load ptr, ptr %67, align 8
  call void %68(ptr %greenMountain)
  %69 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %71 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %73 = load ptr, ptr %2, align 8
  %74 = getelementptr inbounds %GameContext, ptr %73, i32 0, i32 7
  %75 = load ptr, ptr %74, align 8
  store ptr %75, ptr %blackMountain, align 8
  %76 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %77 = icmp eq i32 %76, 0
  br i1 %77, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %78 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %80 = load ptr, ptr %blackMountain, align 8
  %81 = getelementptr inbounds %BlackMountain, ptr %80, i32 0, i32 0
  %82 = load ptr, ptr %81, align 8
  %83 = getelementptr inbounds %"BlackMountain::VTableType", ptr %82, i32 0, i32 2
  %84 = load ptr, ptr %83, align 8
  call void %84(ptr %blackMountain)
  %85 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %87 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %88 = icmp eq i32 %87, 0
  br i1 %88, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %89 = load ptr, ptr %2, align 8
  %90 = getelementptr inbounds %GameContext, ptr %89, i32 0, i32 4
  %91 = load ptr, ptr %90, align 8
  store ptr %91, ptr %wideMountain, align 8
  %92 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %94 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %96 = load ptr, ptr %wideMountain, align 8
  %97 = getelementptr inbounds %WideMountain, ptr %96, i32 0, i32 0
  %98 = load ptr, ptr %97, align 8
  %99 = getelementptr inbounds %"WideMountain::VTableType", ptr %98, i32 0, i32 2
  %100 = load ptr, ptr %99, align 8
  call void %100(ptr %wideMountain)
  %101 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %102 = icmp eq i32 %101, 0
  br i1 %102, label %checkContinueBlock20, label %afterNestedBlock

checkContinueBlock20:                             ; preds = %nestedBlock19
  %103 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %105 = load ptr, ptr %2, align 8
  %106 = getelementptr inbounds %GameContext, ptr %105, i32 0, i32 3
  %107 = load ptr, ptr %106, align 8
  store ptr %107, ptr %ground, align 8
  %108 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %110 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %111 = icmp eq i32 %110, 0
  br i1 %111, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %112 = load ptr, ptr %ground, align 8
  %113 = getelementptr inbounds %Ground, ptr %112, i32 0, i32 0
  %114 = load ptr, ptr %113, align 8
  %115 = getelementptr inbounds %"Ground::VTableType", ptr %114, i32 0, i32 2
  %116 = load ptr, ptr %115, align 8
  call void %116(ptr %ground)
  %117 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %118 = icmp eq i32 %117, 0
  br i1 %118, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %119 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %120 = icmp eq i32 %119, 0
  br i1 %120, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  %121 = load ptr, ptr %2, align 8
  %122 = getelementptr inbounds %GameContext, ptr %121, i32 0, i32 1
  %123 = load ptr, ptr %122, align 8
  store ptr %123, ptr %bird, align 8
  %124 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %125 = icmp eq i32 %124, 0
  br i1 %125, label %checkContinueBlock26, label %afterNestedBlock

checkContinueBlock26:                             ; preds = %nestedBlock25
  %126 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %127 = icmp eq i32 %126, 0
  br i1 %127, label %nestedBlock27, label %afterNestedBlock

nestedBlock27:                                    ; preds = %checkContinueBlock26
  %128 = load ptr, ptr %bird, align 8
  %129 = getelementptr inbounds %Bird, ptr %128, i32 0, i32 0
  %130 = load ptr, ptr %129, align 8
  %131 = getelementptr inbounds %"Bird::VTableType", ptr %130, i32 0, i32 2
  %132 = load ptr, ptr %131, align 8
  call void %132(ptr %bird)
  %133 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %134 = icmp eq i32 %133, 0
  br i1 %134, label %checkContinueBlock28, label %afterNestedBlock

checkContinueBlock28:                             ; preds = %nestedBlock27
  %135 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %136 = icmp eq i32 %135, 0
  br i1 %136, label %nestedBlock29, label %afterNestedBlock

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %137 = load ptr, ptr %2, align 8
  %138 = getelementptr inbounds %GameContext, ptr %137, i32 0, i32 0
  %139 = load ptr, ptr %138, align 8
  %140 = getelementptr inbounds %"GameContext::VTableType", ptr %139, i32 0, i32 0
  %141 = load ptr, ptr %140, align 8
  call void %141(ptr %rtPtr, ptr %2)
  %142 = load i32, ptr %rtPtr, align 4
  %GAME = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  %143 = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  %144 = icmp eq i32 %142, %143
  br i1 %144, label %then, label %else

checkContinueBlock30:                             ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock29
  br label %nestedBlock32

else:                                             ; preds = %nestedBlock29
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock31
  %145 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %146 = icmp eq i32 %145, 0
  br i1 %146, label %checkContinueBlock30, label %afterNestedBlock

afterNestedBlock31:                               ; preds = %checkContinueBlock33, %nestedBlock32
  br label %afterIfElse

nestedBlock32:                                    ; preds = %then
  %147 = load ptr, ptr @fgAnim, align 8
  %148 = getelementptr inbounds %FlowWingAnim, ptr %147, i32 0, i32 0
  %149 = load ptr, ptr %148, align 8
  %150 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %149, i32 0, i32 4
  %151 = load ptr, ptr %150, align 8
  %PAUSE_TEXT = load ptr, ptr %3, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %152 = load i32, ptr @screenWidth, align 4
  %153 = load ptr, ptr @fgAnim, align 8
  %154 = getelementptr inbounds %FlowWingAnim, ptr %153, i32 0, i32 0
  %155 = load ptr, ptr %154, align 8
  %156 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %155, i32 0, i32 8
  %157 = load ptr, ptr %156, align 8
  %PAUSE_TEXT34 = load ptr, ptr %3, align 8
  %158 = load ptr, ptr %3, align 8
  %159 = call i32 %157(ptr %158, i32 15, ptr @fgAnim)
  %160 = sub i32 %152, %159
  %161 = sub i32 %160, 15
  store i32 %161, ptr %10, align 4
  store i32 10, ptr %11, align 4
  store i32 15, ptr %12, align 4
  %162 = load ptr, ptr @fgAnim, align 8
  %163 = getelementptr inbounds %FlowWingAnim, ptr %162, i32 0, i32 5
  %164 = getelementptr inbounds %COLORS_TYPE.4, ptr %163, i32 0, i32 7
  %GRAY = load i32, ptr %164, align 4
  call void %151(ptr %3, ptr %10, ptr %11, ptr %12, ptr %164, ptr @fgAnim)
  %165 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %166 = icmp eq i32 %165, 0
  br i1 %166, label %checkContinueBlock33, label %afterNestedBlock31

checkContinueBlock33:                             ; preds = %nestedBlock32
  br label %afterNestedBlock31
}

define void @GameScreen.handleInput(ptr %0) !rt !90 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GameScreen, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GameScreen, ptr %1, i32 0, i32 2
  %rtPtr = alloca i1, align 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr @fgAnim, align 8
  %5 = getelementptr inbounds %FlowWingAnim, ptr %4, i32 0, i32 0
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %6, i32 0, i32 0
  %8 = load ptr, ptr %7, align 8
  %9 = load ptr, ptr @fgAnim, align 8
  %10 = getelementptr inbounds %FlowWingAnim, ptr %9, i32 0, i32 6
  %11 = getelementptr inbounds %KEYS_TYPE.3, ptr %10, i32 0, i32 6
  %KEY_SPACE = load i32, ptr %11, align 4
  call void %8(ptr %rtPtr, ptr %11, ptr @fgAnim)
  %12 = load i1, ptr %rtPtr, align 1
  br i1 %12, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock2

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock1
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock1:                                ; preds = %checkContinueBlock3, %nestedBlock2
  br label %afterIfElse

nestedBlock2:                                     ; preds = %then
  %15 = load ptr, ptr %2, align 8
  %16 = getelementptr inbounds %GameContext, ptr %15, i32 0, i32 0
  %17 = load ptr, ptr %16, align 8
  %18 = getelementptr inbounds %"GameContext::VTableType", ptr %17, i32 0, i32 1
  %19 = load ptr, ptr %18, align 8
  %PAUSE = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), align 4
  call void %19(ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), ptr %2)
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock3, label %afterNestedBlock1

checkContinueBlock3:                              ; preds = %nestedBlock2
  br label %afterNestedBlock1
}

define void @GameScreen.updateScreen(ptr %0) !rt !91 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %GameScreen, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %GameScreen, ptr %1, i32 0, i32 2
  %ground = alloca ptr, align 8
  %heightedMountain = alloca ptr, align 8
  %greenMountain = alloca ptr, align 8
  %blackMountain = alloca ptr, align 8
  %wideMountain = alloca ptr, align 8
  %bird = alloca ptr, align 8
  %cloud = alloca ptr, align 8
  %4 = alloca %BoxWithText.6, align 8
  call void @"assign_<Object<BoxWithText.6>"(ptr %4)
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock30, %nestedBlock29, %checkContinueBlock28, %nestedBlock27, %checkContinueBlock26, %nestedBlock25, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %nestedBlock19, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @GameScreen.handleInput(ptr %0)
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %9 = load ptr, ptr %2, align 8
  %10 = getelementptr inbounds %GameContext, ptr %9, i32 0, i32 3
  %11 = load ptr, ptr %10, align 8
  store ptr %11, ptr %ground, align 8
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %14 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %16 = load ptr, ptr %ground, align 8
  %17 = getelementptr inbounds %Ground, ptr %16, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr inbounds %"Ground::VTableType", ptr %18, i32 0, i32 0
  %20 = load ptr, ptr %19, align 8
  call void %20(ptr %ground)
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %25 = load ptr, ptr %2, align 8
  %26 = getelementptr inbounds %GameContext, ptr %25, i32 0, i32 5
  %27 = load ptr, ptr %26, align 8
  store ptr %27, ptr %heightedMountain, align 8
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %32 = load ptr, ptr %heightedMountain, align 8
  %33 = getelementptr inbounds %HeightedMountain, ptr %32, i32 0, i32 0
  %34 = load ptr, ptr %33, align 8
  %35 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %34, i32 0, i32 0
  %36 = load ptr, ptr %35, align 8
  call void %36(ptr %heightedMountain)
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %39 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %41 = load ptr, ptr %2, align 8
  %42 = getelementptr inbounds %GameContext, ptr %41, i32 0, i32 6
  %43 = load ptr, ptr %42, align 8
  store ptr %43, ptr %greenMountain, align 8
  %44 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %46 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %48 = load ptr, ptr %greenMountain, align 8
  %49 = getelementptr inbounds %GreenMountain, ptr %48, i32 0, i32 0
  %50 = load ptr, ptr %49, align 8
  %51 = getelementptr inbounds %"GreenMountain::VTableType", ptr %50, i32 0, i32 0
  %52 = load ptr, ptr %51, align 8
  call void %52(ptr %greenMountain)
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %55 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %57 = load ptr, ptr %2, align 8
  %58 = getelementptr inbounds %GameContext, ptr %57, i32 0, i32 7
  %59 = load ptr, ptr %58, align 8
  store ptr %59, ptr %blackMountain, align 8
  %60 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %62 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %63 = icmp eq i32 %62, 0
  br i1 %63, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %64 = load ptr, ptr %blackMountain, align 8
  %65 = getelementptr inbounds %BlackMountain, ptr %64, i32 0, i32 0
  %66 = load ptr, ptr %65, align 8
  %67 = getelementptr inbounds %"BlackMountain::VTableType", ptr %66, i32 0, i32 0
  %68 = load ptr, ptr %67, align 8
  call void %68(ptr %blackMountain)
  %69 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %71 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %73 = load ptr, ptr %2, align 8
  %74 = getelementptr inbounds %GameContext, ptr %73, i32 0, i32 4
  %75 = load ptr, ptr %74, align 8
  store ptr %75, ptr %wideMountain, align 8
  %76 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %77 = icmp eq i32 %76, 0
  br i1 %77, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %78 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %80 = load ptr, ptr %wideMountain, align 8
  %81 = getelementptr inbounds %WideMountain, ptr %80, i32 0, i32 0
  %82 = load ptr, ptr %81, align 8
  %83 = getelementptr inbounds %"WideMountain::VTableType", ptr %82, i32 0, i32 0
  %84 = load ptr, ptr %83, align 8
  call void %84(ptr %wideMountain)
  %85 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %checkContinueBlock20, label %afterNestedBlock

checkContinueBlock20:                             ; preds = %nestedBlock19
  %87 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %88 = icmp eq i32 %87, 0
  br i1 %88, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %89 = load ptr, ptr %2, align 8
  %90 = getelementptr inbounds %GameContext, ptr %89, i32 0, i32 1
  %91 = load ptr, ptr %90, align 8
  store ptr %91, ptr %bird, align 8
  %92 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %94 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %96 = load ptr, ptr %bird, align 8
  %97 = getelementptr inbounds %Bird, ptr %96, i32 0, i32 0
  %98 = load ptr, ptr %97, align 8
  %99 = getelementptr inbounds %"Bird::VTableType", ptr %98, i32 0, i32 0
  %100 = load ptr, ptr %99, align 8
  call void %100(ptr %bird)
  %101 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %102 = icmp eq i32 %101, 0
  br i1 %102, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %103 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  %105 = load ptr, ptr %2, align 8
  %106 = getelementptr inbounds %GameContext, ptr %105, i32 0, i32 2
  %107 = load ptr, ptr %106, align 8
  store ptr %107, ptr %cloud, align 8
  %108 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %checkContinueBlock26, label %afterNestedBlock

checkContinueBlock26:                             ; preds = %nestedBlock25
  %110 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %111 = icmp eq i32 %110, 0
  br i1 %111, label %nestedBlock27, label %afterNestedBlock

nestedBlock27:                                    ; preds = %checkContinueBlock26
  %112 = load ptr, ptr %cloud, align 8
  %113 = getelementptr inbounds %Cloud, ptr %112, i32 0, i32 0
  %114 = load ptr, ptr %113, align 8
  %115 = getelementptr inbounds %"Cloud::VTableType", ptr %114, i32 0, i32 0
  %116 = load ptr, ptr %115, align 8
  call void %116(ptr %cloud)
  %117 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %118 = icmp eq i32 %117, 0
  br i1 %118, label %checkContinueBlock28, label %afterNestedBlock

checkContinueBlock28:                             ; preds = %nestedBlock27
  %119 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %120 = icmp eq i32 %119, 0
  br i1 %120, label %nestedBlock29, label %afterNestedBlock

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %121 = load ptr, ptr @fgAnim, align 8
  %122 = getelementptr inbounds %FlowWingAnim, ptr %121, i32 0, i32 0
  %123 = load ptr, ptr %122, align 8
  %124 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %123, i32 0, i32 21
  %125 = load ptr, ptr %124, align 8
  %126 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 0
  store ptr @32, ptr %126, align 8
  %127 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 1
  store i32 0, ptr %127, align 4
  %128 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 2
  store i32 0, ptr %128, align 4
  %129 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 3
  store i32 0, ptr %129, align 4
  %130 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 4
  store i32 0, ptr %130, align 4
  %131 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 5
  store i32 0, ptr %131, align 4
  %132 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 6
  store i32 0, ptr %132, align 4
  %133 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 7
  store i32 0, ptr %133, align 4
  %134 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 8
  store i32 0, ptr %134, align 4
  %135 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 0
  %136 = load ptr, ptr %2, align 8
  %137 = getelementptr inbounds %GameContext, ptr %136, i32 0, i32 9
  %gameScore = load i32, ptr %137, align 4
  %138 = load i32, ptr %137, align 4
  %139 = call ptr @itos(i32 %138)
  %140 = call ptr @concat_strings(ptr @33, ptr %139)
  store ptr %140, ptr %135, align 8
  %141 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 1
  store i32 10, ptr %141, align 4
  %142 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 2
  store i32 10, ptr %142, align 4
  %143 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 3
  store i32 300, ptr %143, align 4
  %144 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 4
  store i32 50, ptr %144, align 4
  %145 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 5
  %146 = load ptr, ptr @fgAnim, align 8
  %147 = getelementptr inbounds %FlowWingAnim, ptr %146, i32 0, i32 5
  %148 = getelementptr inbounds %COLORS_TYPE.4, ptr %147, i32 0, i32 3
  %BLUE = load i32, ptr %148, align 4
  %149 = load i32, ptr %148, align 4
  store i32 %149, ptr %145, align 4
  %150 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 6
  store i32 20, ptr %150, align 4
  %151 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 7
  store i32 40, ptr %151, align 4
  %152 = getelementptr inbounds %BoxWithText.6, ptr %4, i32 0, i32 8
  %153 = load ptr, ptr @fgAnim, align 8
  %154 = getelementptr inbounds %FlowWingAnim, ptr %153, i32 0, i32 5
  %155 = getelementptr inbounds %COLORS_TYPE.4, ptr %154, i32 0, i32 5
  %TRANSPARENT = load i32, ptr %155, align 4
  %156 = load i32, ptr %155, align 4
  store i32 %156, ptr %152, align 4
  call void %125(ptr %4, ptr @fgAnim)
  %157 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %158 = icmp eq i32 %157, 0
  br i1 %158, label %checkContinueBlock30, label %afterNestedBlock

checkContinueBlock30:                             ; preds = %nestedBlock29
  br label %afterNestedBlock
}

define void @PauseScreen.init1(ptr %0, ptr %1) !rt !92 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %PauseScreen, ptr %2, i32 0, i32 1
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @Screen.init1(ptr %0, ptr %1)
  %4 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @PauseScreen.drawScreen(ptr %0) !rt !93 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %PauseScreen, ptr %1, i32 0, i32 1
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca ptr, align 8
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca ptr, align 8
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %19 = load ptr, ptr @fgAnim, align 8
  %20 = getelementptr inbounds %FlowWingAnim, ptr %19, i32 0, i32 0
  %21 = load ptr, ptr %20, align 8
  %22 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %21, i32 0, i32 12
  %23 = load ptr, ptr %22, align 8
  %24 = load ptr, ptr @fgAnim, align 8
  %25 = getelementptr inbounds %FlowWingAnim, ptr %24, i32 0, i32 5
  %26 = getelementptr inbounds %COLORS_TYPE.4, ptr %25, i32 0, i32 8
  %RAYWHITE = load i32, ptr %26, align 4
  call void %23(ptr %26, ptr @fgAnim)
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %29 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %31 = load ptr, ptr @fgAnim, align 8
  %32 = getelementptr inbounds %FlowWingAnim, ptr %31, i32 0, i32 0
  %33 = load ptr, ptr %32, align 8
  %34 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %33, i32 0, i32 17
  %35 = load ptr, ptr %34, align 8
  store i32 20, ptr %3, align 4
  store i32 20, ptr %4, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %36 = load i32, ptr @screenWidth, align 4
  %37 = sub i32 %36, 40
  store i32 %37, ptr %5, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %38 = load i32, ptr @screenHeight, align 4
  %39 = sub i32 %38, 40
  store i32 %39, ptr %6, align 4
  %40 = load ptr, ptr @fgAnim, align 8
  %41 = getelementptr inbounds %FlowWingAnim, ptr %40, i32 0, i32 5
  %42 = getelementptr inbounds %COLORS_TYPE.4, ptr %41, i32 0, i32 10
  %BLUR = load i32, ptr %42, align 4
  call void %35(ptr %3, ptr %4, ptr %5, ptr %6, ptr %42, ptr @fgAnim)
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %45 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %47 = load ptr, ptr @fgAnim, align 8
  %48 = getelementptr inbounds %FlowWingAnim, ptr %47, i32 0, i32 0
  %49 = load ptr, ptr %48, align 8
  %50 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %49, i32 0, i32 4
  %51 = load ptr, ptr %50, align 8
  store ptr @34, ptr %7, align 8
  %screenWidth9 = load i32, ptr @screenWidth, align 4
  %52 = load i32, ptr @screenWidth, align 4
  %53 = sitofp i32 %52 to double
  %54 = fdiv double %53, 2.000000e+00
  %55 = load ptr, ptr @fgAnim, align 8
  %56 = getelementptr inbounds %FlowWingAnim, ptr %55, i32 0, i32 0
  %57 = load ptr, ptr %56, align 8
  %58 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %57, i32 0, i32 8
  %59 = load ptr, ptr %58, align 8
  %60 = call i32 %59(ptr @35, i32 40, ptr @fgAnim)
  %61 = sitofp i32 %60 to double
  %62 = fdiv double %61, 2.000000e+00
  %63 = fsub double %54, %62
  %64 = fptosi double %63 to i32
  store i32 %64, ptr %8, align 4
  %screenHeight10 = load i32, ptr @screenHeight, align 4
  %65 = load i32, ptr @screenHeight, align 4
  %66 = sitofp i32 %65 to double
  %67 = fdiv double %66, 2.000000e+00
  %68 = fsub double %67, 5.000000e+01
  %69 = fptosi double %68 to i32
  store i32 %69, ptr %9, align 4
  store i32 40, ptr %10, align 4
  %70 = load ptr, ptr @fgAnim, align 8
  %71 = getelementptr inbounds %FlowWingAnim, ptr %70, i32 0, i32 5
  %72 = getelementptr inbounds %COLORS_TYPE.4, ptr %71, i32 0, i32 0
  %WHITE = load i32, ptr %72, align 4
  call void %51(ptr %7, ptr %8, ptr %9, ptr %10, ptr %72, ptr @fgAnim)
  %73 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %74 = icmp eq i32 %73, 0
  br i1 %74, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %75 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %77 = load ptr, ptr @fgAnim, align 8
  %78 = getelementptr inbounds %FlowWingAnim, ptr %77, i32 0, i32 0
  %79 = load ptr, ptr %78, align 8
  %80 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %79, i32 0, i32 4
  %81 = load ptr, ptr %80, align 8
  store ptr @36, ptr %11, align 8
  %screenWidth11 = load i32, ptr @screenWidth, align 4
  %82 = load i32, ptr @screenWidth, align 4
  %83 = sitofp i32 %82 to double
  %84 = fdiv double %83, 2.000000e+00
  %85 = load ptr, ptr @fgAnim, align 8
  %86 = getelementptr inbounds %FlowWingAnim, ptr %85, i32 0, i32 0
  %87 = load ptr, ptr %86, align 8
  %88 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %87, i32 0, i32 8
  %89 = load ptr, ptr %88, align 8
  %90 = call i32 %89(ptr @37, i32 20, ptr @fgAnim)
  %91 = sitofp i32 %90 to double
  %92 = fdiv double %91, 2.000000e+00
  %93 = fsub double %84, %92
  %94 = fptosi double %93 to i32
  store i32 %94, ptr %12, align 4
  %screenHeight12 = load i32, ptr @screenHeight, align 4
  %95 = load i32, ptr @screenHeight, align 4
  %96 = sitofp i32 %95 to double
  %97 = fdiv double %96, 2.000000e+00
  %98 = fadd double %97, 5.000000e+01
  %99 = fptosi double %98 to i32
  store i32 %99, ptr %13, align 4
  store i32 20, ptr %14, align 4
  %100 = load ptr, ptr @fgAnim, align 8
  %101 = getelementptr inbounds %FlowWingAnim, ptr %100, i32 0, i32 5
  %102 = getelementptr inbounds %COLORS_TYPE.4, ptr %101, i32 0, i32 0
  %WHITE13 = load i32, ptr %102, align 4
  call void %81(ptr %11, ptr %12, ptr %13, ptr %14, ptr %102, ptr @fgAnim)
  %103 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %105 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %106 = icmp eq i32 %105, 0
  br i1 %106, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %107 = load ptr, ptr @fgAnim, align 8
  %108 = getelementptr inbounds %FlowWingAnim, ptr %107, i32 0, i32 0
  %109 = load ptr, ptr %108, align 8
  %110 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %109, i32 0, i32 4
  %111 = load ptr, ptr %110, align 8
  store ptr @38, ptr %15, align 8
  %screenWidth14 = load i32, ptr @screenWidth, align 4
  %112 = load i32, ptr @screenWidth, align 4
  %113 = sitofp i32 %112 to double
  %114 = fdiv double %113, 2.000000e+00
  %115 = load ptr, ptr @fgAnim, align 8
  %116 = getelementptr inbounds %FlowWingAnim, ptr %115, i32 0, i32 0
  %117 = load ptr, ptr %116, align 8
  %118 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %117, i32 0, i32 8
  %119 = load ptr, ptr %118, align 8
  %120 = call i32 %119(ptr @39, i32 20, ptr @fgAnim)
  %121 = sitofp i32 %120 to double
  %122 = fdiv double %121, 2.000000e+00
  %123 = fsub double %114, %122
  %124 = fptosi double %123 to i32
  store i32 %124, ptr %16, align 4
  %screenHeight15 = load i32, ptr @screenHeight, align 4
  %125 = load i32, ptr @screenHeight, align 4
  %126 = sitofp i32 %125 to double
  %127 = fdiv double %126, 2.000000e+00
  %128 = fadd double %127, 8.000000e+01
  %129 = fptosi double %128 to i32
  store i32 %129, ptr %17, align 4
  store i32 20, ptr %18, align 4
  %130 = load ptr, ptr @fgAnim, align 8
  %131 = getelementptr inbounds %FlowWingAnim, ptr %130, i32 0, i32 5
  %132 = getelementptr inbounds %COLORS_TYPE.4, ptr %131, i32 0, i32 1
  %RED = load i32, ptr %132, align 4
  call void %111(ptr %15, ptr %16, ptr %17, ptr %18, ptr %132, ptr @fgAnim)
  %133 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %134 = icmp eq i32 %133, 0
  br i1 %134, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock
}

define void @PauseScreen.handleInput(ptr %0) !rt !94 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %PauseScreen, ptr %1, i32 0, i32 1
  %rtPtr = alloca i1, align 1
  %rtPtr1 = alloca i1, align 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock3, %afterIfElse9, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr @fgAnim, align 8
  %4 = getelementptr inbounds %FlowWingAnim, ptr %3, i32 0, i32 0
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %5, i32 0, i32 0
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr @fgAnim, align 8
  %9 = getelementptr inbounds %FlowWingAnim, ptr %8, i32 0, i32 6
  %10 = getelementptr inbounds %KEYS_TYPE.3, ptr %9, i32 0, i32 6
  %KEY_SPACE = load i32, ptr %10, align 4
  call void %7(ptr %rtPtr, ptr %10, ptr @fgAnim)
  %11 = load i1, ptr %rtPtr, align 1
  br i1 %11, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %12 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  %14 = load ptr, ptr @fgAnim, align 8
  %15 = getelementptr inbounds %FlowWingAnim, ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %16, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = load ptr, ptr @fgAnim, align 8
  %20 = getelementptr inbounds %FlowWingAnim, ptr %19, i32 0, i32 6
  %21 = getelementptr inbounds %KEYS_TYPE.3, ptr %20, i32 0, i32 5
  %KEY_ESCAPE = load i32, ptr %21, align 4
  call void %18(ptr %rtPtr1, ptr %21, ptr @fgAnim)
  %22 = load i1, ptr %rtPtr1, align 1
  br i1 %22, label %then7, label %else8

checkContinueBlock3:                              ; preds = %afterIfElse9
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock5

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock4
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock4:                                ; preds = %checkContinueBlock6, %nestedBlock5
  br label %afterIfElse

nestedBlock5:                                     ; preds = %then
  %25 = load ptr, ptr %2, align 8
  %26 = getelementptr inbounds %GameContext, ptr %25, i32 0, i32 0
  %27 = load ptr, ptr %26, align 8
  %28 = getelementptr inbounds %"GameContext::VTableType", ptr %27, i32 0, i32 1
  %29 = load ptr, ptr %28, align 8
  %GAME = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  call void %29(ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), ptr %2)
  %30 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock6, label %afterNestedBlock4

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock4

then7:                                            ; preds = %nestedBlock2
  br label %nestedBlock11

else8:                                            ; preds = %nestedBlock2
  br label %afterIfElse9

afterIfElse9:                                     ; preds = %else8, %afterNestedBlock10
  %32 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %checkContinueBlock3, label %afterNestedBlock

afterNestedBlock10:                               ; preds = %checkContinueBlock12, %nestedBlock11
  br label %afterIfElse9

nestedBlock11:                                    ; preds = %then7
  %34 = load ptr, ptr %2, align 8
  %35 = getelementptr inbounds %GameContext, ptr %34, i32 0, i32 0
  %36 = load ptr, ptr %35, align 8
  %37 = getelementptr inbounds %"GameContext::VTableType", ptr %36, i32 0, i32 1
  %38 = load ptr, ptr %37, align 8
  %EXIT = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), align 4
  call void %38(ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 3), ptr %2)
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock12, label %afterNestedBlock10

checkContinueBlock12:                             ; preds = %nestedBlock11
  br label %afterNestedBlock10
}

define void @PauseScreen.updateScreen(ptr %0) !rt !95 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %PauseScreen, ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @PauseScreen.handleInput(ptr %0)
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @TextureManager.init0(ptr %0) !rt !96 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 5
  %7 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 6
  %8 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 7
  %9 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 8
  %10 = getelementptr inbounds %TextureManager, ptr %1, i32 0, i32 9
  br label %afterNestedBlock

afterNestedBlock:                                 ; preds = %entry
  ret void
}

define void @TextureManager.loadAllTextures(ptr %0, ptr %1) !rt !97 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 9
  %rtPtr = alloca %Texture.0, align 8
  %12 = alloca ptr, align 8
  %rtPtr1 = alloca %Texture.0, align 8
  %13 = alloca ptr, align 8
  %rtPtr2 = alloca %Texture.0, align 8
  %14 = alloca ptr, align 8
  %rtPtr3 = alloca %Texture.0, align 8
  %15 = alloca ptr, align 8
  %rtPtr4 = alloca %Texture.0, align 8
  %16 = alloca ptr, align 8
  %rtPtr5 = alloca %Texture.0, align 8
  %17 = alloca ptr, align 8
  %rtPtr6 = alloca %Texture.0, align 8
  %18 = alloca ptr, align 8
  %rtPtr7 = alloca %Texture.0, align 8
  %19 = alloca ptr, align 8
  %rtPtr8 = alloca %Texture.0, align 8
  %20 = alloca ptr, align 8
  %rtPtr9 = alloca %"Err::Result", align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock27, %mergeBlock, %checkContinueBlock25, %nestedBlock24, %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %nestedBlock10, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %21 = load ptr, ptr %1, align 8
  %22 = getelementptr inbounds %TextureManager, ptr %21, i32 0, i32 1
  %23 = load ptr, ptr @fgAnim, align 8
  %24 = getelementptr inbounds %FlowWingAnim, ptr %23, i32 0, i32 0
  %25 = load ptr, ptr %24, align 8
  %26 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %25, i32 0, i32 2
  %27 = load ptr, ptr %26, align 8
  store ptr @40, ptr %12, align 8
  call void %27(ptr %rtPtr, ptr %12, ptr @fgAnim)
  %28 = load %Texture.0, ptr %rtPtr, align 4
  store %Texture.0 %28, ptr %22, align 4
  %29 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %31 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock
  %33 = load ptr, ptr %1, align 8
  %34 = getelementptr inbounds %TextureManager, ptr %33, i32 0, i32 2
  %35 = load ptr, ptr @fgAnim, align 8
  %36 = getelementptr inbounds %FlowWingAnim, ptr %35, i32 0, i32 0
  %37 = load ptr, ptr %36, align 8
  %38 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %37, i32 0, i32 2
  %39 = load ptr, ptr %38, align 8
  store ptr @41, ptr %13, align 8
  call void %39(ptr %rtPtr1, ptr %13, ptr @fgAnim)
  %40 = load %Texture.0, ptr %rtPtr1, align 4
  store %Texture.0 %40, ptr %34, align 4
  %41 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %43 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %45 = load ptr, ptr %1, align 8
  %46 = getelementptr inbounds %TextureManager, ptr %45, i32 0, i32 3
  %47 = load ptr, ptr @fgAnim, align 8
  %48 = getelementptr inbounds %FlowWingAnim, ptr %47, i32 0, i32 0
  %49 = load ptr, ptr %48, align 8
  %50 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %49, i32 0, i32 2
  %51 = load ptr, ptr %50, align 8
  store ptr @42, ptr %14, align 8
  call void %51(ptr %rtPtr2, ptr %14, ptr @fgAnim)
  %52 = load %Texture.0, ptr %rtPtr2, align 4
  store %Texture.0 %52, ptr %46, align 4
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %55 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %57 = load ptr, ptr %1, align 8
  %58 = getelementptr inbounds %TextureManager, ptr %57, i32 0, i32 4
  %59 = load ptr, ptr @fgAnim, align 8
  %60 = getelementptr inbounds %FlowWingAnim, ptr %59, i32 0, i32 0
  %61 = load ptr, ptr %60, align 8
  %62 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %61, i32 0, i32 2
  %63 = load ptr, ptr %62, align 8
  store ptr @43, ptr %15, align 8
  call void %63(ptr %rtPtr3, ptr %15, ptr @fgAnim)
  %64 = load %Texture.0, ptr %rtPtr3, align 4
  store %Texture.0 %64, ptr %58, align 4
  %65 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %66 = icmp eq i32 %65, 0
  br i1 %66, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %67 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %69 = load ptr, ptr %1, align 8
  %70 = getelementptr inbounds %TextureManager, ptr %69, i32 0, i32 5
  %71 = load ptr, ptr @fgAnim, align 8
  %72 = getelementptr inbounds %FlowWingAnim, ptr %71, i32 0, i32 0
  %73 = load ptr, ptr %72, align 8
  %74 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %73, i32 0, i32 2
  %75 = load ptr, ptr %74, align 8
  store ptr @44, ptr %16, align 8
  call void %75(ptr %rtPtr4, ptr %16, ptr @fgAnim)
  %76 = load %Texture.0, ptr %rtPtr4, align 4
  store %Texture.0 %76, ptr %70, align 4
  %77 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %79 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %80 = icmp eq i32 %79, 0
  br i1 %80, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %81 = load ptr, ptr %1, align 8
  %82 = getelementptr inbounds %TextureManager, ptr %81, i32 0, i32 6
  %83 = load ptr, ptr @fgAnim, align 8
  %84 = getelementptr inbounds %FlowWingAnim, ptr %83, i32 0, i32 0
  %85 = load ptr, ptr %84, align 8
  %86 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %85, i32 0, i32 2
  %87 = load ptr, ptr %86, align 8
  store ptr @45, ptr %17, align 8
  call void %87(ptr %rtPtr5, ptr %17, ptr @fgAnim)
  %88 = load %Texture.0, ptr %rtPtr5, align 4
  store %Texture.0 %88, ptr %82, align 4
  %89 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %90 = icmp eq i32 %89, 0
  br i1 %90, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  %91 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %93 = load ptr, ptr %1, align 8
  %94 = getelementptr inbounds %TextureManager, ptr %93, i32 0, i32 7
  %95 = load ptr, ptr @fgAnim, align 8
  %96 = getelementptr inbounds %FlowWingAnim, ptr %95, i32 0, i32 0
  %97 = load ptr, ptr %96, align 8
  %98 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %97, i32 0, i32 2
  %99 = load ptr, ptr %98, align 8
  store ptr @46, ptr %18, align 8
  call void %99(ptr %rtPtr6, ptr %18, ptr @fgAnim)
  %100 = load %Texture.0, ptr %rtPtr6, align 4
  store %Texture.0 %100, ptr %94, align 4
  %101 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %102 = icmp eq i32 %101, 0
  br i1 %102, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %103 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %105 = load ptr, ptr %1, align 8
  %106 = getelementptr inbounds %TextureManager, ptr %105, i32 0, i32 8
  %107 = load ptr, ptr @fgAnim, align 8
  %108 = getelementptr inbounds %FlowWingAnim, ptr %107, i32 0, i32 0
  %109 = load ptr, ptr %108, align 8
  %110 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %109, i32 0, i32 2
  %111 = load ptr, ptr %110, align 8
  store ptr @47, ptr %19, align 8
  call void %111(ptr %rtPtr7, ptr %19, ptr @fgAnim)
  %112 = load %Texture.0, ptr %rtPtr7, align 4
  store %Texture.0 %112, ptr %106, align 4
  %113 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %114 = icmp eq i32 %113, 0
  br i1 %114, label %checkContinueBlock23, label %afterNestedBlock

checkContinueBlock23:                             ; preds = %nestedBlock22
  %115 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %116 = icmp eq i32 %115, 0
  br i1 %116, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  %117 = load ptr, ptr %1, align 8
  %118 = getelementptr inbounds %TextureManager, ptr %117, i32 0, i32 9
  %119 = load ptr, ptr @fgAnim, align 8
  %120 = getelementptr inbounds %FlowWingAnim, ptr %119, i32 0, i32 0
  %121 = load ptr, ptr %120, align 8
  %122 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %121, i32 0, i32 2
  %123 = load ptr, ptr %122, align 8
  store ptr @48, ptr %20, align 8
  call void %123(ptr %rtPtr8, ptr %20, ptr @fgAnim)
  %124 = load %Texture.0, ptr %rtPtr8, align 4
  store %Texture.0 %124, ptr %118, align 4
  %125 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %126 = icmp eq i32 %125, 0
  br i1 %126, label %checkContinueBlock25, label %afterNestedBlock

checkContinueBlock25:                             ; preds = %nestedBlock24
  %127 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %nestedBlock26, label %afterNestedBlock

nestedBlock26:                                    ; preds = %checkContinueBlock25
  br label %returnBlock

checkContinueBlock27:                             ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock26
  call void @TextureManager.hasAllTexturesLoaded(ptr %0, ptr %1)
  ret void

mergeBlock:                                       ; No predecessors!
  %129 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %checkContinueBlock27, label %afterNestedBlock
}

define void @TextureManager.hasAllTexturesLoaded(ptr %0, ptr %1) !rt !98 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 5
  %8 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 6
  %9 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 7
  %10 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 8
  %11 = getelementptr inbounds %TextureManager, ptr %2, i32 0, i32 9
  %12 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %13 = alloca ptr, align 8
  %14 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %mergeBlock15, %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = getelementptr inbounds %Texture.9, ptr %3, i32 0, i32 0
  %id = load i32, ptr %15, align 4
  %16 = load i32, ptr %15, align 4
  %17 = icmp eq i32 %16, 0
  %18 = getelementptr inbounds %Texture.9, ptr %4, i32 0, i32 0
  %id3 = load i32, ptr %18, align 4
  %19 = load i32, ptr %18, align 4
  %20 = icmp eq i32 %19, 0
  %21 = select i1 %17, i1 true, i1 %20
  %22 = getelementptr inbounds %Texture.9, ptr %5, i32 0, i32 0
  %id4 = load i32, ptr %22, align 4
  %23 = load i32, ptr %22, align 4
  %24 = icmp eq i32 %23, 0
  %25 = select i1 %21, i1 true, i1 %24
  %26 = getelementptr inbounds %Texture.9, ptr %6, i32 0, i32 0
  %id5 = load i32, ptr %26, align 4
  %27 = load i32, ptr %26, align 4
  %28 = icmp eq i32 %27, 0
  %29 = select i1 %25, i1 true, i1 %28
  %30 = getelementptr inbounds %Texture.9, ptr %7, i32 0, i32 0
  %id6 = load i32, ptr %30, align 4
  %31 = load i32, ptr %30, align 4
  %32 = icmp eq i32 %31, 0
  %33 = select i1 %29, i1 true, i1 %32
  %34 = getelementptr inbounds %Texture.9, ptr %8, i32 0, i32 0
  %id7 = load i32, ptr %34, align 4
  %35 = load i32, ptr %34, align 4
  %36 = icmp eq i32 %35, 0
  %37 = select i1 %33, i1 true, i1 %36
  %38 = getelementptr inbounds %Texture.9, ptr %9, i32 0, i32 0
  %id8 = load i32, ptr %38, align 4
  %39 = load i32, ptr %38, align 4
  %40 = icmp eq i32 %39, 0
  %41 = select i1 %37, i1 true, i1 %40
  %42 = getelementptr inbounds %Texture.9, ptr %10, i32 0, i32 0
  %id9 = load i32, ptr %42, align 4
  %43 = load i32, ptr %42, align 4
  %44 = icmp eq i32 %43, 0
  %45 = select i1 %41, i1 true, i1 %44
  %46 = getelementptr inbounds %Texture.9, ptr %11, i32 0, i32 0
  %id10 = load i32, ptr %46, align 4
  %47 = load i32, ptr %46, align 4
  %48 = icmp eq i32 %47, 0
  %49 = select i1 %45, i1 true, i1 %48
  br i1 %49, label %then, label %else

checkContinueBlock:                               ; preds = %afterIfElse
  %50 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  br label %returnBlock14

checkContinueBlock2:                              ; preds = %mergeBlock15
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock12

else:                                             ; preds = %nestedBlock
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock11
  %52 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock11:                               ; preds = %checkContinueBlock13, %mergeBlock
  br label %afterIfElse

nestedBlock12:                                    ; preds = %then
  br label %returnBlock

checkContinueBlock13:                             ; preds = %mergeBlock
  br label %afterNestedBlock11

returnBlock:                                      ; preds = %nestedBlock12
  %54 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Err::Result>>"(ptr %54)
  %55 = getelementptr inbounds %"Err::Result", ptr %54, i32 0, i32 0
  store ptr @"vtable.Err::Result.fg", ptr %55, align 8
  %56 = load ptr, ptr %55, align 8
  %57 = getelementptr inbounds %"Err::Result::VTableType", ptr %56, i32 0, i32 5
  store ptr @"Err::Result.getMessage", ptr %57, align 8
  %58 = getelementptr inbounds %"Err::Result::VTableType", ptr %56, i32 0, i32 3
  store ptr @"Err::Result.withDetails", ptr %58, align 8
  %59 = getelementptr inbounds %"Err::Result::VTableType", ptr %56, i32 0, i32 2
  store ptr @"Err::Result.getDetails", ptr %59, align 8
  %60 = getelementptr inbounds %"Err::Result::VTableType", ptr %56, i32 0, i32 4
  store ptr @"Err::Result.getCode", ptr %60, align 8
  %61 = getelementptr inbounds %"Err::Result::VTableType", ptr %56, i32 0, i32 1
  store ptr @"Err::Result.withMessage", ptr %61, align 8
  %62 = getelementptr inbounds %"Err::Result::VTableType", ptr %56, i32 0, i32 0
  store ptr @"Err::Result.toString", ptr %62, align 8
  %63 = getelementptr inbounds %"Err::Result", ptr %54, i32 0, i32 1
  store ptr @52, ptr %63, align 8
  %64 = getelementptr inbounds %"Err::Result", ptr %54, i32 0, i32 2
  store i32 0, ptr %64, align 4
  %65 = getelementptr inbounds %"Err::Result", ptr %54, i32 0, i32 3
  store ptr @53, ptr %65, align 8
  store ptr %54, ptr %0, align 8
  store ptr @54, ptr %14, align 8
  call void @"Err::Result.init1"(ptr %14, ptr %0)
  ret void

mergeBlock:                                       ; No predecessors!
  %66 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %checkContinueBlock13, label %afterNestedBlock11

returnBlock14:                                    ; preds = %nestedBlock1
  store ptr null, ptr %0, align 8
  ret void

mergeBlock15:                                     ; No predecessors!
  %68 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %checkContinueBlock2, label %afterNestedBlock
}

define void @BirdGame.init0(ptr %0) !rt !99 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 5
  %clPtr = alloca ptr, align 8
  %clPtr1 = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %clPtr3 = alloca ptr, align 8
  %clPtr4 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = load ptr, ptr @fgAnim, align 8
  %8 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %9, i32 0, i32 25
  %11 = load ptr, ptr %10, align 8
  call void %11(ptr @fgAnim)
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %14 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock
  %16 = call ptr @malloc(i64 656)
  call void @"assign_<Class<GameContext>>"(ptr %16)
  %17 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 0
  store ptr @vtable.GameContext.fg, ptr %17, align 8
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr inbounds %"GameContext::VTableType", ptr %18, i32 0, i32 2
  store ptr @GameContext.getGameScore, ptr %19, align 8
  %20 = getelementptr inbounds %"GameContext::VTableType", ptr %18, i32 0, i32 1
  store ptr @GameContext.setCurrentGameScreen, ptr %20, align 8
  %21 = getelementptr inbounds %"GameContext::VTableType", ptr %18, i32 0, i32 0
  store ptr @GameContext.getCurrentGameScreen, ptr %21, align 8
  %22 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 1
  call void @"assign_<Class<Bird>>"(ptr %22)
  %23 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 2
  call void @"assign_<Class<Cloud>>"(ptr %23)
  %24 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 3
  call void @"assign_<Class<Ground>>"(ptr %24)
  %25 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 4
  call void @"assign_<Class<WideMountain>>"(ptr %25)
  %26 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 5
  call void @"assign_<Class<HeightedMountain>>"(ptr %26)
  %27 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 6
  call void @"assign_<Class<GreenMountain>>"(ptr %27)
  %28 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 7
  call void @"assign_<Class<BlackMountain>>"(ptr %28)
  %29 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 8
  store i32 0, ptr %29, align 4
  %30 = getelementptr inbounds %GameContext, ptr %16, i32 0, i32 9
  store i32 0, ptr %30, align 4
  store ptr %16, ptr %3, align 8
  %MENU = load i32, ptr @GAME_SCREEN, align 4
  call void @GameContext.init1(ptr @GAME_SCREEN, ptr %3)
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %33 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %35 = call ptr @malloc(i64 192)
  call void @"assign_<Class<TextureManager>>"(ptr %35)
  %36 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 0
  store ptr @vtable.TextureManager.fg, ptr %36, align 8
  %37 = load ptr, ptr %36, align 8
  %38 = getelementptr inbounds %"TextureManager::VTableType", ptr %37, i32 0, i32 1
  store ptr @TextureManager.hasAllTexturesLoaded, ptr %38, align 8
  %39 = getelementptr inbounds %"TextureManager::VTableType", ptr %37, i32 0, i32 0
  store ptr @TextureManager.loadAllTextures, ptr %39, align 8
  %40 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %40)
  %41 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 2
  call void @"assign_<Object<Texture.9>"(ptr %41)
  %42 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 3
  call void @"assign_<Object<Texture.9>"(ptr %42)
  %43 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 4
  call void @"assign_<Object<Texture.9>"(ptr %43)
  %44 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 5
  call void @"assign_<Object<Texture.9>"(ptr %44)
  %45 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 6
  call void @"assign_<Object<Texture.9>"(ptr %45)
  %46 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 7
  call void @"assign_<Object<Texture.9>"(ptr %46)
  %47 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 8
  call void @"assign_<Object<Texture.9>"(ptr %47)
  %48 = getelementptr inbounds %TextureManager, ptr %35, i32 0, i32 9
  call void @"assign_<Object<Texture.9>"(ptr %48)
  store ptr %35, ptr %2, align 8
  call void @TextureManager.init0(ptr %2)
  %49 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %51 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %53 = call ptr @malloc(i64 736)
  call void @"assign_<Class<MenuScreen>>"(ptr %53)
  %54 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 0
  store ptr @vtable.MenuScreen.fg, ptr %54, align 8
  %55 = load ptr, ptr %54, align 8
  %56 = getelementptr inbounds %"MenuScreen::VTableType", ptr %55, i32 0, i32 3
  store ptr @MenuScreen.isMouseOverText, ptr %56, align 8
  %57 = getelementptr inbounds %"MenuScreen::VTableType", ptr %55, i32 0, i32 2
  store ptr @MenuScreen.handleInput, ptr %57, align 8
  %58 = getelementptr inbounds %"MenuScreen::VTableType", ptr %55, i32 0, i32 1
  store ptr @MenuScreen.drawScreen, ptr %58, align 8
  %59 = getelementptr inbounds %"MenuScreen::VTableType", ptr %55, i32 0, i32 0
  store ptr @MenuScreen.updateScreen, ptr %59, align 8
  %60 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 2
  store ptr @67, ptr %60, align 8
  %61 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 3
  store ptr @68, ptr %61, align 8
  %62 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 4
  %63 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %62, i32 0, i32 0
  store i32 0, ptr %63, align 4
  %64 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %62, i32 0, i32 1
  store i32 1, ptr %64, align 4
  %65 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 5
  store i32 40, ptr %65, align 4
  %66 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 6
  store double 0.000000e+00, ptr %66, align 8
  %67 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 7
  store float 0.000000e+00, ptr %67, align 4
  %68 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 8
  store i32 0, ptr %68, align 4
  %69 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 9
  store i32 0, ptr %69, align 4
  %70 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 10
  store i32 0, ptr %70, align 4
  %71 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 11
  store float 0.000000e+00, ptr %71, align 4
  %72 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 12
  store float 0.000000e+00, ptr %72, align 4
  %73 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 13
  store i32 0, ptr %73, align 4
  %74 = getelementptr inbounds %MenuScreen, ptr %53, i32 0, i32 14
  store i32 0, ptr %74, align 4
  store ptr %53, ptr %4, align 8
  call void @MenuScreen.init1(ptr %3, ptr %4)
  %75 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %77 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %79 = call ptr @malloc(i64 672)
  call void @"assign_<Class<GameScreen>>"(ptr %79)
  %80 = getelementptr inbounds %GameScreen, ptr %79, i32 0, i32 0
  store ptr @vtable.GameScreen.fg, ptr %80, align 8
  %81 = load ptr, ptr %80, align 8
  %82 = getelementptr inbounds %"GameScreen::VTableType", ptr %81, i32 0, i32 2
  store ptr @GameScreen.handleInput, ptr %82, align 8
  %83 = getelementptr inbounds %"GameScreen::VTableType", ptr %81, i32 0, i32 1
  store ptr @GameScreen.drawScreen, ptr %83, align 8
  %84 = getelementptr inbounds %"GameScreen::VTableType", ptr %81, i32 0, i32 0
  store ptr @GameScreen.updateScreen, ptr %84, align 8
  %85 = getelementptr inbounds %GameScreen, ptr %79, i32 0, i32 2
  store ptr @71, ptr %85, align 8
  store ptr %79, ptr %5, align 8
  call void @GameScreen.init1(ptr %3, ptr %5)
  %86 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %88 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %89 = icmp eq i32 %88, 0
  br i1 %89, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %90 = call ptr @malloc(i64 664)
  call void @"assign_<Class<PauseScreen>>"(ptr %90)
  %91 = getelementptr inbounds %PauseScreen, ptr %90, i32 0, i32 0
  store ptr @vtable.PauseScreen.fg, ptr %91, align 8
  %92 = load ptr, ptr %91, align 8
  %93 = getelementptr inbounds %"PauseScreen::VTableType", ptr %92, i32 0, i32 2
  store ptr @PauseScreen.handleInput, ptr %93, align 8
  %94 = getelementptr inbounds %"PauseScreen::VTableType", ptr %92, i32 0, i32 1
  store ptr @PauseScreen.drawScreen, ptr %94, align 8
  %95 = getelementptr inbounds %"PauseScreen::VTableType", ptr %92, i32 0, i32 0
  store ptr @PauseScreen.updateScreen, ptr %95, align 8
  store ptr %90, ptr %6, align 8
  call void @PauseScreen.init1(ptr %3, ptr %6)
  %96 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %97 = icmp eq i32 %96, 0
  br i1 %97, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock
}

define void @BirdGame.Initialize(ptr %0, ptr %1) !rt !100 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %BirdGame, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %BirdGame, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %BirdGame, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %BirdGame, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %BirdGame, ptr %2, i32 0, i32 5
  %err = alloca ptr, align 8
  %rtPtr = alloca %"Err::Result", align 8
  %rtPtr1 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  %clPtr2 = alloca ptr, align 8
  %clPtr3 = alloca ptr, align 8
  %clPtr4 = alloca ptr, align 8
  %clPtr5 = alloca ptr, align 8
  %clPtr6 = alloca ptr, align 8
  %clPtr7 = alloca ptr, align 8
  %g = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock31, %mergeBlock40, %checkContinueBlock29, %nestedBlock28, %checkContinueBlock27, %nestedBlock26, %checkContinueBlock25, %nestedBlock24, %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %afterIfElse, %checkContinueBlock9, %nestedBlock8, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = load ptr, ptr @fgAnim, align 8
  %9 = getelementptr inbounds %FlowWingAnim, ptr %8, i32 0, i32 0
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %10, i32 0, i32 25
  %12 = load ptr, ptr %11, align 8
  call void %12(ptr @fgAnim)
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock
  %17 = load ptr, ptr %3, align 8
  %18 = getelementptr inbounds %TextureManager, ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  %20 = getelementptr inbounds %"TextureManager::VTableType", ptr %19, i32 0, i32 0
  %21 = load ptr, ptr %20, align 8
  call void %21(ptr %rtPtr, ptr %3)
  %22 = load ptr, ptr %rtPtr, align 8
  store ptr %22, ptr %err, align 8
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock9, label %afterNestedBlock

checkContinueBlock9:                              ; preds = %nestedBlock8
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %27 = load ptr, ptr %err, align 8
  %28 = icmp ne ptr %27, null
  %29 = icmp ne i1 %28, false
  br i1 %29, label %then, label %else

checkContinueBlock11:                             ; preds = %afterIfElse
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %32 = load ptr, ptr %4, align 8
  %33 = getelementptr inbounds %GameContext, ptr %32, i32 0, i32 1
  %34 = call ptr @malloc(i64 152)
  call void @"assign_<Class<Bird>>"(ptr %34)
  %35 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %35, align 8
  %36 = load ptr, ptr %35, align 8
  %37 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 9
  store ptr @Bird.getSource, ptr %37, align 8
  %38 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 6
  store ptr @Bird.getRotation, ptr %38, align 8
  %39 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 5
  store ptr @Bird.updateY, ptr %39, align 8
  %40 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 4
  store ptr @Bird.getOriginAsArray, ptr %40, align 8
  %41 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 7
  store ptr @Bird.handleInput, ptr %41, align 8
  %42 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 2
  store ptr @Bird.draw, ptr %42, align 8
  %43 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 8
  store ptr @Bird.getDistination, ptr %43, align 8
  %44 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 0
  store ptr @Bird.update, ptr %44, align 8
  %45 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %45, align 8
  %46 = getelementptr inbounds %"Bird::VTableType", ptr %36, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %46, align 8
  %47 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 3
  store float 3.600000e+02, ptr %47, align 4
  %48 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 4
  store float 9.000000e+01, ptr %48, align 4
  %49 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 5
  %FPS = load i32, ptr @FPS, align 4
  %50 = load i32, ptr @FPS, align 4
  %51 = sitofp i32 %50 to double
  %52 = fdiv double 1.000000e+01, %51
  store double %52, ptr %49, align 8
  %53 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 6
  store double 0.000000e+00, ptr %53, align 8
  %54 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 7
  store i32 9, ptr %54, align 4
  %55 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 8
  store i32 0, ptr %55, align 4
  %56 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 9
  store i1 false, ptr %56, align 1
  %57 = getelementptr inbounds %Bird, ptr %34, i32 0, i32 10
  call void @"assign_<Array[9]<Object<Position.7>>:9,"(ptr %57)
  store ptr %34, ptr %33, align 8
  %58 = load ptr, ptr %3, align 8
  %59 = getelementptr inbounds %TextureManager, ptr %58, i32 0, i32 8
  call void @Bird.init1(ptr %59, ptr %33)
  %60 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %62 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %63 = icmp eq i32 %62, 0
  br i1 %63, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %64 = load ptr, ptr %4, align 8
  %65 = getelementptr inbounds %GameContext, ptr %64, i32 0, i32 2
  %66 = call ptr @malloc(i64 256)
  call void @"assign_<Class<Cloud>>"(ptr %66)
  %67 = getelementptr inbounds %Cloud, ptr %66, i32 0, i32 0
  store ptr @vtable.Cloud.fg, ptr %67, align 8
  %68 = load ptr, ptr %67, align 8
  %69 = getelementptr inbounds %"Cloud::VTableType", ptr %68, i32 0, i32 4
  store ptr @GameUnit.getOriginAsArray, ptr %69, align 8
  %70 = getelementptr inbounds %"Cloud::VTableType", ptr %68, i32 0, i32 2
  store ptr @Cloud.draw, ptr %70, align 8
  %71 = getelementptr inbounds %"Cloud::VTableType", ptr %68, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %71, align 8
  %72 = getelementptr inbounds %"Cloud::VTableType", ptr %68, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %72, align 8
  %73 = getelementptr inbounds %"Cloud::VTableType", ptr %68, i32 0, i32 0
  store ptr @Cloud.update, ptr %73, align 8
  %74 = getelementptr inbounds %Cloud, ptr %66, i32 0, i32 3
  call void @"assign_<Array[5]<Object<AttributeType.11>>:5,"(ptr %74)
  store ptr %66, ptr %65, align 8
  %75 = load ptr, ptr %3, align 8
  %76 = getelementptr inbounds %TextureManager, ptr %75, i32 0, i32 9
  call void @Cloud.init1(ptr %76, ptr %65)
  %77 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %79 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %80 = icmp eq i32 %79, 0
  br i1 %80, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %81 = load ptr, ptr %4, align 8
  %82 = getelementptr inbounds %GameContext, ptr %81, i32 0, i32 3
  %83 = call ptr @malloc(i64 56)
  call void @"assign_<Class<Ground>>"(ptr %83)
  %84 = getelementptr inbounds %Ground, ptr %83, i32 0, i32 0
  store ptr @vtable.Ground.fg, ptr %84, align 8
  %85 = load ptr, ptr %84, align 8
  %86 = getelementptr inbounds %"Ground::VTableType", ptr %85, i32 0, i32 5
  store ptr @Ground.setWoodTexture, ptr %86, align 8
  %87 = getelementptr inbounds %"Ground::VTableType", ptr %85, i32 0, i32 4
  store ptr @GameUnit.getOriginAsArray, ptr %87, align 8
  %88 = getelementptr inbounds %"Ground::VTableType", ptr %85, i32 0, i32 2
  store ptr @Ground.draw, ptr %88, align 8
  %89 = getelementptr inbounds %"Ground::VTableType", ptr %85, i32 0, i32 0
  store ptr @Ground.update, ptr %89, align 8
  %90 = getelementptr inbounds %"Ground::VTableType", ptr %85, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %90, align 8
  %91 = getelementptr inbounds %"Ground::VTableType", ptr %85, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %91, align 8
  %92 = getelementptr inbounds %Ground, ptr %83, i32 0, i32 3
  call void @"assign_<Object<Texture.9>"(ptr %92)
  store ptr %83, ptr %82, align 8
  %93 = load ptr, ptr %3, align 8
  %94 = getelementptr inbounds %TextureManager, ptr %93, i32 0, i32 2
  call void @Ground.init1(ptr %94, ptr %82)
  %95 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %96 = icmp eq i32 %95, 0
  br i1 %96, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %97 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %98 = icmp eq i32 %97, 0
  br i1 %98, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %99 = load ptr, ptr %4, align 8
  %100 = getelementptr inbounds %GameContext, ptr %99, i32 0, i32 4
  %101 = call ptr @malloc(i64 56)
  call void @"assign_<Class<WideMountain>>"(ptr %101)
  %102 = getelementptr inbounds %WideMountain, ptr %101, i32 0, i32 0
  store ptr @vtable.WideMountain.fg, ptr %102, align 8
  %103 = load ptr, ptr %102, align 8
  %104 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 6
  store ptr @WideMountain.getOriginSecondMount, ptr %104, align 8
  %105 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 5
  store ptr @WideMountain.getOriginFirstMount, ptr %105, align 8
  %106 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 4
  store ptr @GameUnit.getOriginAsArray, ptr %106, align 8
  %107 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 2
  store ptr @WideMountain.draw, ptr %107, align 8
  %108 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 0
  store ptr @WideMountain.update, ptr %108, align 8
  %109 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %109, align 8
  %110 = getelementptr inbounds %"WideMountain::VTableType", ptr %103, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %110, align 8
  %111 = getelementptr inbounds %WideMountain, ptr %101, i32 0, i32 3
  call void @"assign_<Object<Position.7>"(ptr %111)
  %112 = getelementptr inbounds %WideMountain, ptr %101, i32 0, i32 4
  call void @"assign_<Object<Position.7>"(ptr %112)
  store ptr %101, ptr %100, align 8
  %113 = load ptr, ptr %3, align 8
  %114 = getelementptr inbounds %TextureManager, ptr %113, i32 0, i32 3
  call void @WideMountain.init1(ptr %114, ptr %100)
  %115 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %116 = icmp eq i32 %115, 0
  br i1 %116, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  %117 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %118 = icmp eq i32 %117, 0
  br i1 %118, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %119 = load ptr, ptr %4, align 8
  %120 = getelementptr inbounds %GameContext, ptr %119, i32 0, i32 5
  %121 = call ptr @malloc(i64 40)
  call void @"assign_<Class<HeightedMountain>>"(ptr %121)
  %122 = getelementptr inbounds %HeightedMountain, ptr %121, i32 0, i32 0
  store ptr @vtable.HeightedMountain.fg, ptr %122, align 8
  %123 = load ptr, ptr %122, align 8
  %124 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %123, i32 0, i32 4
  store ptr @GameUnit.getOriginAsArray, ptr %124, align 8
  %125 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %123, i32 0, i32 2
  store ptr @HeightedMountain.draw, ptr %125, align 8
  %126 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %123, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %126, align 8
  %127 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %123, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %127, align 8
  %128 = getelementptr inbounds %"HeightedMountain::VTableType", ptr %123, i32 0, i32 0
  store ptr @HeightedMountain.update, ptr %128, align 8
  store ptr %121, ptr %120, align 8
  %129 = load ptr, ptr %3, align 8
  %130 = getelementptr inbounds %TextureManager, ptr %129, i32 0, i32 4
  call void @HeightedMountain.init1(ptr %130, ptr %120)
  %131 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %132 = icmp eq i32 %131, 0
  br i1 %132, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %133 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %134 = icmp eq i32 %133, 0
  br i1 %134, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %135 = load ptr, ptr %4, align 8
  %136 = getelementptr inbounds %GameContext, ptr %135, i32 0, i32 6
  %137 = call ptr @malloc(i64 40)
  call void @"assign_<Class<GreenMountain>>"(ptr %137)
  %138 = getelementptr inbounds %GreenMountain, ptr %137, i32 0, i32 0
  store ptr @vtable.GreenMountain.fg, ptr %138, align 8
  %139 = load ptr, ptr %138, align 8
  %140 = getelementptr inbounds %"GreenMountain::VTableType", ptr %139, i32 0, i32 4
  store ptr @GameUnit.getOriginAsArray, ptr %140, align 8
  %141 = getelementptr inbounds %"GreenMountain::VTableType", ptr %139, i32 0, i32 2
  store ptr @GreenMountain.draw, ptr %141, align 8
  %142 = getelementptr inbounds %"GreenMountain::VTableType", ptr %139, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %142, align 8
  %143 = getelementptr inbounds %"GreenMountain::VTableType", ptr %139, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %143, align 8
  %144 = getelementptr inbounds %"GreenMountain::VTableType", ptr %139, i32 0, i32 0
  store ptr @GreenMountain.update, ptr %144, align 8
  store ptr %137, ptr %136, align 8
  %145 = load ptr, ptr %3, align 8
  %146 = getelementptr inbounds %TextureManager, ptr %145, i32 0, i32 5
  call void @GreenMountain.init1(ptr %146, ptr %136)
  %147 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %148 = icmp eq i32 %147, 0
  br i1 %148, label %checkContinueBlock23, label %afterNestedBlock

checkContinueBlock23:                             ; preds = %nestedBlock22
  %149 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %150 = icmp eq i32 %149, 0
  br i1 %150, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  %151 = load ptr, ptr %4, align 8
  %152 = getelementptr inbounds %GameContext, ptr %151, i32 0, i32 7
  %153 = call ptr @malloc(i64 40)
  call void @"assign_<Class<BlackMountain>>"(ptr %153)
  %154 = getelementptr inbounds %BlackMountain, ptr %153, i32 0, i32 0
  store ptr @vtable.BlackMountain.fg, ptr %154, align 8
  %155 = load ptr, ptr %154, align 8
  %156 = getelementptr inbounds %"BlackMountain::VTableType", ptr %155, i32 0, i32 4
  store ptr @GameUnit.getOriginAsArray, ptr %156, align 8
  %157 = getelementptr inbounds %"BlackMountain::VTableType", ptr %155, i32 0, i32 2
  store ptr @BlackMountain.draw, ptr %157, align 8
  %158 = getelementptr inbounds %"BlackMountain::VTableType", ptr %155, i32 0, i32 1
  store ptr @GameUnit.getTexture, ptr %158, align 8
  %159 = getelementptr inbounds %"BlackMountain::VTableType", ptr %155, i32 0, i32 3
  store ptr @GameUnit.getOrigin, ptr %159, align 8
  %160 = getelementptr inbounds %"BlackMountain::VTableType", ptr %155, i32 0, i32 0
  store ptr @BlackMountain.update, ptr %160, align 8
  store ptr %153, ptr %152, align 8
  %161 = load ptr, ptr %3, align 8
  %162 = getelementptr inbounds %TextureManager, ptr %161, i32 0, i32 6
  call void @BlackMountain.init1(ptr %162, ptr %152)
  %163 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %164 = icmp eq i32 %163, 0
  br i1 %164, label %checkContinueBlock25, label %afterNestedBlock

checkContinueBlock25:                             ; preds = %nestedBlock24
  %165 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %166 = icmp eq i32 %165, 0
  br i1 %166, label %nestedBlock26, label %afterNestedBlock

nestedBlock26:                                    ; preds = %checkContinueBlock25
  %167 = load ptr, ptr %4, align 8
  %168 = getelementptr inbounds %GameContext, ptr %167, i32 0, i32 3
  %169 = load ptr, ptr %168, align 8
  store ptr %169, ptr %g, align 8
  %170 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %checkContinueBlock27, label %afterNestedBlock

checkContinueBlock27:                             ; preds = %nestedBlock26
  %172 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %173 = icmp eq i32 %172, 0
  br i1 %173, label %nestedBlock28, label %afterNestedBlock

nestedBlock28:                                    ; preds = %checkContinueBlock27
  %174 = load ptr, ptr %g, align 8
  %175 = getelementptr inbounds %Ground, ptr %174, i32 0, i32 0
  %176 = load ptr, ptr %175, align 8
  %177 = getelementptr inbounds %"Ground::VTableType", ptr %176, i32 0, i32 5
  %178 = load ptr, ptr %177, align 8
  %179 = load ptr, ptr %3, align 8
  %180 = getelementptr inbounds %TextureManager, ptr %179, i32 0, i32 7
  call void %178(ptr %180, ptr %g)
  %181 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %182 = icmp eq i32 %181, 0
  br i1 %182, label %checkContinueBlock29, label %afterNestedBlock

checkContinueBlock29:                             ; preds = %nestedBlock28
  %183 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %184 = icmp eq i32 %183, 0
  br i1 %184, label %nestedBlock30, label %afterNestedBlock

nestedBlock30:                                    ; preds = %checkContinueBlock29
  br label %returnBlock39

checkContinueBlock31:                             ; preds = %mergeBlock40
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock10
  br label %nestedBlock33

else:                                             ; preds = %nestedBlock10
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock32
  %185 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %checkContinueBlock11, label %afterNestedBlock

afterNestedBlock32:                               ; preds = %checkContinueBlock38, %mergeBlock, %checkContinueBlock36, %nestedBlock35, %checkContinueBlock34, %nestedBlock33
  br label %afterIfElse

nestedBlock33:                                    ; preds = %then
  %187 = load ptr, ptr @fgAnim, align 8
  %188 = getelementptr inbounds %FlowWingAnim, ptr %187, i32 0, i32 0
  %189 = load ptr, ptr %188, align 8
  %190 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %189, i32 0, i32 28
  %191 = load ptr, ptr %190, align 8
  call void %191(ptr @fgAnim)
  %192 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %193 = icmp eq i32 %192, 0
  br i1 %193, label %checkContinueBlock34, label %afterNestedBlock32

checkContinueBlock34:                             ; preds = %nestedBlock33
  %194 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %195 = icmp eq i32 %194, 0
  br i1 %195, label %nestedBlock35, label %afterNestedBlock32

nestedBlock35:                                    ; preds = %checkContinueBlock34
  %196 = load ptr, ptr %err, align 8
  %197 = getelementptr inbounds %"Err::Result", ptr %196, i32 0, i32 0
  %198 = load ptr, ptr %197, align 8
  %199 = getelementptr inbounds %"Err::Result::VTableType", ptr %198, i32 0, i32 2
  %200 = load ptr, ptr %199, align 8
  call void %200(ptr %rtPtr1, ptr %err)
  %201 = load ptr, ptr %rtPtr1, align 8
  %202 = call ptr @concat_strings(ptr @73, ptr %201)
  %203 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %203, ptr %202)
  %204 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %205 = icmp eq i32 %204, 0
  br i1 %205, label %checkContinueBlock36, label %afterNestedBlock32

checkContinueBlock36:                             ; preds = %nestedBlock35
  %206 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %207 = icmp eq i32 %206, 0
  br i1 %207, label %nestedBlock37, label %afterNestedBlock32

nestedBlock37:                                    ; preds = %checkContinueBlock36
  br label %returnBlock

checkContinueBlock38:                             ; preds = %mergeBlock
  br label %afterNestedBlock32

returnBlock:                                      ; preds = %nestedBlock37
  %208 = load ptr, ptr %err, align 8
  store ptr %208, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %209 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %210 = icmp eq i32 %209, 0
  br i1 %210, label %checkContinueBlock38, label %afterNestedBlock32

returnBlock39:                                    ; preds = %nestedBlock30
  store ptr null, ptr %0, align 8
  ret void

mergeBlock40:                                     ; No predecessors!
  %211 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %212 = icmp eq i32 %211, 0
  br i1 %212, label %checkContinueBlock31, label %afterNestedBlock
}

define void @BirdGame.update(ptr %0) !rt !101 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 5
  %rtPtr = alloca i32, align 4
  %rtPtr1 = alloca i32, align 4
  %rtPtr2 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = load ptr, ptr %3, align 8
  %8 = getelementptr inbounds %GameContext, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %"GameContext::VTableType", ptr %9, i32 0, i32 0
  %11 = load ptr, ptr %10, align 8
  call void %11(ptr %rtPtr, ptr %3)
  %12 = load i32, ptr %rtPtr, align 4
  %MENU = load i32, ptr @GAME_SCREEN, align 4
  %13 = load i32, ptr @GAME_SCREEN, align 4
  %14 = icmp eq i32 %12, %13
  br i1 %14, label %then, label %orIf0

checkContinueBlock:                               ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock4

orIf0:                                            ; preds = %nestedBlock
  %15 = load ptr, ptr %3, align 8
  %16 = getelementptr inbounds %GameContext, ptr %15, i32 0, i32 0
  %17 = load ptr, ptr %16, align 8
  %18 = getelementptr inbounds %"GameContext::VTableType", ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  call void %19(ptr %rtPtr1, ptr %3)
  %20 = load i32, ptr %rtPtr1, align 4
  %GAME = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  %21 = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  %22 = icmp eq i32 %20, %21
  br i1 %22, label %orIfThen0, label %orIf1

orIf1:                                            ; preds = %orIf0
  %23 = load ptr, ptr %3, align 8
  %24 = getelementptr inbounds %GameContext, ptr %23, i32 0, i32 0
  %25 = load ptr, ptr %24, align 8
  %26 = getelementptr inbounds %"GameContext::VTableType", ptr %25, i32 0, i32 0
  %27 = load ptr, ptr %26, align 8
  call void %27(ptr %rtPtr2, ptr %3)
  %28 = load i32, ptr %rtPtr2, align 4
  %PAUSE = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), align 4
  %29 = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), align 4
  %30 = icmp eq i32 %28, %29
  br i1 %30, label %orIfThen1, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock7

orIfThen1:                                        ; preds = %orIf1
  br label %nestedBlock10

else:                                             ; preds = %orIf1
  br label %nestedBlock13

afterIfElse:                                      ; preds = %afterNestedBlock12, %afterNestedBlock9, %afterNestedBlock6, %afterNestedBlock3
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock3:                                ; preds = %checkContinueBlock5, %nestedBlock4
  br label %afterIfElse

nestedBlock4:                                     ; preds = %then
  %33 = load ptr, ptr %4, align 8
  %34 = getelementptr inbounds %MenuScreen, ptr %33, i32 0, i32 0
  %35 = load ptr, ptr %34, align 8
  %36 = getelementptr inbounds %"MenuScreen::VTableType", ptr %35, i32 0, i32 0
  %37 = load ptr, ptr %36, align 8
  call void %37(ptr %4)
  %38 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %checkContinueBlock5, label %afterNestedBlock3

checkContinueBlock5:                              ; preds = %nestedBlock4
  br label %afterNestedBlock3

afterNestedBlock6:                                ; preds = %checkContinueBlock8, %nestedBlock7
  br label %afterIfElse

nestedBlock7:                                     ; preds = %orIfThen0
  %40 = load ptr, ptr %5, align 8
  %41 = getelementptr inbounds %GameScreen, ptr %40, i32 0, i32 0
  %42 = load ptr, ptr %41, align 8
  %43 = getelementptr inbounds %"GameScreen::VTableType", ptr %42, i32 0, i32 0
  %44 = load ptr, ptr %43, align 8
  call void %44(ptr %5)
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock6

afterNestedBlock9:                                ; preds = %checkContinueBlock11, %nestedBlock10
  br label %afterIfElse

nestedBlock10:                                    ; preds = %orIfThen1
  %47 = load ptr, ptr %6, align 8
  %48 = getelementptr inbounds %PauseScreen, ptr %47, i32 0, i32 0
  %49 = load ptr, ptr %48, align 8
  %50 = getelementptr inbounds %"PauseScreen::VTableType", ptr %49, i32 0, i32 0
  %51 = load ptr, ptr %50, align 8
  call void %51(ptr %6)
  %52 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock11, label %afterNestedBlock9

checkContinueBlock11:                             ; preds = %nestedBlock10
  br label %afterNestedBlock9

afterNestedBlock12:                               ; preds = %checkContinueBlock16, %mergeBlock, %checkContinueBlock14, %nestedBlock13
  br label %afterIfElse

nestedBlock13:                                    ; preds = %else
  %54 = load ptr, ptr @fgAnim, align 8
  %55 = getelementptr inbounds %FlowWingAnim, ptr %54, i32 0, i32 0
  %56 = load ptr, ptr %55, align 8
  %57 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %56, i32 0, i32 28
  %58 = load ptr, ptr %57, align 8
  call void %58(ptr @fgAnim)
  %59 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %checkContinueBlock14, label %afterNestedBlock12

checkContinueBlock14:                             ; preds = %nestedBlock13
  %61 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %nestedBlock15, label %afterNestedBlock12

nestedBlock15:                                    ; preds = %checkContinueBlock14
  br label %returnBlock

checkContinueBlock16:                             ; preds = %mergeBlock
  br label %afterNestedBlock12

returnBlock:                                      ; preds = %nestedBlock15
  ret void

mergeBlock:                                       ; No predecessors!
  %63 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %64 = icmp eq i32 %63, 0
  br i1 %64, label %checkContinueBlock16, label %afterNestedBlock12
}

define void @BirdGame.draw(ptr %0) !rt !102 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 5
  %rtPtr = alloca i32, align 4
  %rtPtr1 = alloca i32, align 4
  %rtPtr2 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %afterIfElse, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = load ptr, ptr @fgAnim, align 8
  %8 = getelementptr inbounds %FlowWingAnim, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %9, i32 0, i32 16
  %11 = load ptr, ptr %10, align 8
  call void %11(ptr @fgAnim)
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %14 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock
  %16 = load ptr, ptr @fgAnim, align 8
  %17 = getelementptr inbounds %FlowWingAnim, ptr %16, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %18, i32 0, i32 12
  %20 = load ptr, ptr %19, align 8
  %21 = load ptr, ptr @fgAnim, align 8
  %22 = getelementptr inbounds %FlowWingAnim, ptr %21, i32 0, i32 5
  %23 = getelementptr inbounds %COLORS_TYPE.4, ptr %22, i32 0, i32 8
  %RAYWHITE = load i32, ptr %23, align 4
  call void %20(ptr %23, ptr @fgAnim)
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %26 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %28 = load ptr, ptr %3, align 8
  %29 = getelementptr inbounds %GameContext, ptr %28, i32 0, i32 0
  %30 = load ptr, ptr %29, align 8
  %31 = getelementptr inbounds %"GameContext::VTableType", ptr %30, i32 0, i32 0
  %32 = load ptr, ptr %31, align 8
  call void %32(ptr %rtPtr, ptr %3)
  %33 = load i32, ptr %rtPtr, align 4
  %MENU = load i32, ptr @GAME_SCREEN, align 4
  %34 = load i32, ptr @GAME_SCREEN, align 4
  %35 = icmp eq i32 %33, %34
  br i1 %35, label %then, label %orIf0

checkContinueBlock6:                              ; preds = %afterIfElse
  %36 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %38 = load ptr, ptr @fgAnim, align 8
  %39 = getelementptr inbounds %FlowWingAnim, ptr %38, i32 0, i32 0
  %40 = load ptr, ptr %39, align 8
  %41 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %40, i32 0, i32 14
  %42 = load ptr, ptr %41, align 8
  call void %42(ptr @fgAnim)
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock5
  br label %nestedBlock10

orIf0:                                            ; preds = %nestedBlock5
  %45 = load ptr, ptr %3, align 8
  %46 = getelementptr inbounds %GameContext, ptr %45, i32 0, i32 0
  %47 = load ptr, ptr %46, align 8
  %48 = getelementptr inbounds %"GameContext::VTableType", ptr %47, i32 0, i32 0
  %49 = load ptr, ptr %48, align 8
  call void %49(ptr %rtPtr1, ptr %3)
  %50 = load i32, ptr %rtPtr1, align 4
  %GAME = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  %51 = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 1), align 4
  %52 = icmp eq i32 %50, %51
  br i1 %52, label %orIfThen0, label %orIf1

orIf1:                                            ; preds = %orIf0
  %53 = load ptr, ptr %3, align 8
  %54 = getelementptr inbounds %GameContext, ptr %53, i32 0, i32 0
  %55 = load ptr, ptr %54, align 8
  %56 = getelementptr inbounds %"GameContext::VTableType", ptr %55, i32 0, i32 0
  %57 = load ptr, ptr %56, align 8
  call void %57(ptr %rtPtr2, ptr %3)
  %58 = load i32, ptr %rtPtr2, align 4
  %PAUSE = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), align 4
  %59 = load i32, ptr getelementptr inbounds (%GameScreenType.10, ptr @GAME_SCREEN, i32 0, i32 2), align 4
  %60 = icmp eq i32 %58, %59
  br i1 %60, label %orIfThen1, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock13

orIfThen1:                                        ; preds = %orIf1
  br label %nestedBlock16

else:                                             ; preds = %orIf1
  br label %nestedBlock21

afterIfElse:                                      ; preds = %afterNestedBlock20, %afterNestedBlock15, %afterNestedBlock12, %afterNestedBlock9
  %61 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %checkContinueBlock6, label %afterNestedBlock

afterNestedBlock9:                                ; preds = %checkContinueBlock11, %nestedBlock10
  br label %afterIfElse

nestedBlock10:                                    ; preds = %then
  %63 = load ptr, ptr %4, align 8
  %64 = getelementptr inbounds %MenuScreen, ptr %63, i32 0, i32 0
  %65 = load ptr, ptr %64, align 8
  %66 = getelementptr inbounds %"MenuScreen::VTableType", ptr %65, i32 0, i32 1
  %67 = load ptr, ptr %66, align 8
  call void %67(ptr %4)
  %68 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %checkContinueBlock11, label %afterNestedBlock9

checkContinueBlock11:                             ; preds = %nestedBlock10
  br label %afterNestedBlock9

afterNestedBlock12:                               ; preds = %checkContinueBlock14, %nestedBlock13
  br label %afterIfElse

nestedBlock13:                                    ; preds = %orIfThen0
  %70 = load ptr, ptr %5, align 8
  %71 = getelementptr inbounds %GameScreen, ptr %70, i32 0, i32 0
  %72 = load ptr, ptr %71, align 8
  %73 = getelementptr inbounds %"GameScreen::VTableType", ptr %72, i32 0, i32 1
  %74 = load ptr, ptr %73, align 8
  call void %74(ptr %5)
  %75 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %checkContinueBlock14, label %afterNestedBlock12

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock12

afterNestedBlock15:                               ; preds = %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16
  br label %afterIfElse

nestedBlock16:                                    ; preds = %orIfThen1
  %77 = load ptr, ptr %5, align 8
  %78 = getelementptr inbounds %GameScreen, ptr %77, i32 0, i32 0
  %79 = load ptr, ptr %78, align 8
  %80 = getelementptr inbounds %"GameScreen::VTableType", ptr %79, i32 0, i32 1
  %81 = load ptr, ptr %80, align 8
  call void %81(ptr %5)
  %82 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %83 = icmp eq i32 %82, 0
  br i1 %83, label %checkContinueBlock17, label %afterNestedBlock15

checkContinueBlock17:                             ; preds = %nestedBlock16
  %84 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %85 = icmp eq i32 %84, 0
  br i1 %85, label %nestedBlock18, label %afterNestedBlock15

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %86 = load ptr, ptr %6, align 8
  %87 = getelementptr inbounds %PauseScreen, ptr %86, i32 0, i32 0
  %88 = load ptr, ptr %87, align 8
  %89 = getelementptr inbounds %"PauseScreen::VTableType", ptr %88, i32 0, i32 1
  %90 = load ptr, ptr %89, align 8
  call void %90(ptr %6)
  %91 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %checkContinueBlock19, label %afterNestedBlock15

checkContinueBlock19:                             ; preds = %nestedBlock18
  br label %afterNestedBlock15

afterNestedBlock20:                               ; preds = %checkContinueBlock26, %mergeBlock, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %nestedBlock21
  br label %afterIfElse

nestedBlock21:                                    ; preds = %else
  %93 = load ptr, ptr @fgAnim, align 8
  %94 = getelementptr inbounds %FlowWingAnim, ptr %93, i32 0, i32 0
  %95 = load ptr, ptr %94, align 8
  %96 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %95, i32 0, i32 14
  %97 = load ptr, ptr %96, align 8
  call void %97(ptr @fgAnim)
  %98 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %checkContinueBlock22, label %afterNestedBlock20

checkContinueBlock22:                             ; preds = %nestedBlock21
  %100 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %nestedBlock23, label %afterNestedBlock20

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %102 = load ptr, ptr @fgAnim, align 8
  %103 = getelementptr inbounds %FlowWingAnim, ptr %102, i32 0, i32 0
  %104 = load ptr, ptr %103, align 8
  %105 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %104, i32 0, i32 28
  %106 = load ptr, ptr %105, align 8
  call void %106(ptr @fgAnim)
  %107 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %checkContinueBlock24, label %afterNestedBlock20

checkContinueBlock24:                             ; preds = %nestedBlock23
  %109 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %110 = icmp eq i32 %109, 0
  br i1 %110, label %nestedBlock25, label %afterNestedBlock20

nestedBlock25:                                    ; preds = %checkContinueBlock24
  br label %returnBlock

checkContinueBlock26:                             ; preds = %mergeBlock
  br label %afterNestedBlock20

returnBlock:                                      ; preds = %nestedBlock25
  ret void

mergeBlock:                                       ; No predecessors!
  %111 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %112 = icmp eq i32 %111, 0
  br i1 %112, label %checkContinueBlock26, label %afterNestedBlock20
}

define void @BirdGame.runGameLoop(ptr %0) !rt !103 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 5
  %rtPtr = alloca i1, align 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %mergeBlock, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %end_block11
  ret void

nestedBlock:                                      ; preds = %entry
  br label %"while:conditon"

checkContinueBlock:                               ; preds = %end_block11
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %9 = load ptr, ptr @fgAnim, align 8
  %10 = getelementptr inbounds %FlowWingAnim, ptr %9, i32 0, i32 0
  %11 = load ptr, ptr %10, align 8
  %12 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %11, i32 0, i32 28
  %13 = load ptr, ptr %12, align 8
  call void %13(ptr @fgAnim)
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  br label %returnBlock

checkContinueBlock4:                              ; preds = %mergeBlock
  br label %afterNestedBlock

"while:conditon":                                 ; preds = %afterNestedBlock5, %nestedBlock
  %18 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock6

while.end:                                        ; preds = %afterNestedBlock5, %end_block
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %end_block11, label %decrement_block10

decrement_block:                                  ; preds = %"while:conditon"
  %22 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %23 = sub i32 %22, 1
  store i32 %23, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %24 = load ptr, ptr @fgAnim, align 8
  %25 = getelementptr inbounds %FlowWingAnim, ptr %24, i32 0, i32 0
  %26 = load ptr, ptr %25, align 8
  %27 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %26, i32 0, i32 22
  %28 = load ptr, ptr %27, align 8
  call void %28(ptr %rtPtr, ptr @fgAnim)
  %29 = load i1, ptr %rtPtr, align 1
  %30 = xor i1 %29, true
  br i1 %30, label %"while:body", label %while.end

afterNestedBlock5:                                ; preds = %checkContinueBlock9, %nestedBlock8, %checkContinueBlock7, %nestedBlock6
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %"while:conditon", label %while.end

nestedBlock6:                                     ; preds = %"while:body"
  call void @BirdGame.update(ptr %0)
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock7, label %afterNestedBlock5

checkContinueBlock7:                              ; preds = %nestedBlock6
  %35 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock8, label %afterNestedBlock5

nestedBlock8:                                     ; preds = %checkContinueBlock7
  call void @BirdGame.draw(ptr %0)
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock9, label %afterNestedBlock5

checkContinueBlock9:                              ; preds = %nestedBlock8
  br label %afterNestedBlock5

decrement_block10:                                ; preds = %while.end
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = sub i32 %39, 1
  store i32 %40, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block11

end_block11:                                      ; preds = %decrement_block10, %while.end
  %41 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %checkContinueBlock, label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock3
  ret void

mergeBlock:                                       ; No predecessors!
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock4, label %afterNestedBlock
}

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim()

declare !rt !104 double @getSin(ptr)

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random()

declare !rt !105 i32 @getRandomNumber(ptr, ptr)

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-..-..-..-lib-mac-silicon-lib-modules-Err-module()

define internal void @"assign_<Object<Err::ErrorCode.8>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::ErrorCode.8", ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %"Err::ErrorCode.8", ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %"Err::ErrorCode.8", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  ret void
}

define internal void @"assign_<Array[2]<Object<Err::ErrorCode.8>>:2,"(ptr %0) {
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
  %7 = getelementptr [2 x %"Err::ErrorCode.8"], ptr %0, i32 0, i32 %6
  call void @"assign_<Object<Err::ErrorCode.8>"(ptr %7)
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

define void @main(ptr %0) !rt !106 {
entry:
  %birdGame = alloca ptr, align 8
  %err = alloca ptr, align 8
  %rtPtr = alloca %"Err::Result", align 8
  %rtPtr1 = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock9, %mergeBlock16, %checkContinueBlock7, %nestedBlock6, %checkContinueBlock5, %afterIfElse, %checkContinueBlock3, %nestedBlock2, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %1 = call ptr @malloc(i64 2928)
  call void @"assign_<Class<BirdGame>>"(ptr %1)
  %2 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 0
  store ptr @vtable.BirdGame.fg, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %"BirdGame::VTableType", ptr %3, i32 0, i32 3
  store ptr @BirdGame.runGameLoop, ptr %4, align 8
  %5 = getelementptr inbounds %"BirdGame::VTableType", ptr %3, i32 0, i32 2
  store ptr @BirdGame.Initialize, ptr %5, align 8
  %6 = getelementptr inbounds %"BirdGame::VTableType", ptr %3, i32 0, i32 1
  store ptr @BirdGame.update, ptr %6, align 8
  %7 = getelementptr inbounds %"BirdGame::VTableType", ptr %3, i32 0, i32 0
  store ptr @BirdGame.draw, ptr %7, align 8
  %8 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 1
  call void @"assign_<Class<TextureManager>>"(ptr %8)
  %9 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 2
  call void @"assign_<Class<GameContext>>"(ptr %9)
  %10 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 3
  call void @"assign_<Class<MenuScreen>>"(ptr %10)
  %11 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 4
  call void @"assign_<Class<GameScreen>>"(ptr %11)
  %12 = getelementptr inbounds %BirdGame, ptr %1, i32 0, i32 5
  call void @"assign_<Class<PauseScreen>>"(ptr %12)
  store ptr %1, ptr %birdGame, align 8
  call void @BirdGame.init0(ptr %birdGame)
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  %17 = load ptr, ptr %birdGame, align 8
  %18 = getelementptr inbounds %BirdGame, ptr %17, i32 0, i32 0
  %19 = load ptr, ptr %18, align 8
  %20 = getelementptr inbounds %"BirdGame::VTableType", ptr %19, i32 0, i32 2
  %21 = load ptr, ptr %20, align 8
  call void %21(ptr %rtPtr, ptr %birdGame)
  %22 = load ptr, ptr %rtPtr, align 8
  store ptr %22, ptr %err, align 8
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock3, label %afterNestedBlock

checkContinueBlock3:                              ; preds = %nestedBlock2
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock3
  %27 = load ptr, ptr %err, align 8
  %28 = icmp ne ptr %27, null
  %29 = icmp ne i1 %28, false
  br i1 %29, label %then, label %else

checkContinueBlock5:                              ; preds = %afterIfElse
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  %32 = load ptr, ptr %birdGame, align 8
  %33 = getelementptr inbounds %BirdGame, ptr %32, i32 0, i32 0
  %34 = load ptr, ptr %33, align 8
  %35 = getelementptr inbounds %"BirdGame::VTableType", ptr %34, i32 0, i32 3
  %36 = load ptr, ptr %35, align 8
  call void %36(ptr %birdGame)
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %39 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  br label %returnBlock15

checkContinueBlock9:                              ; preds = %mergeBlock16
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock4
  br label %nestedBlock11

else:                                             ; preds = %nestedBlock4
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock10
  %41 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %checkContinueBlock5, label %afterNestedBlock

afterNestedBlock10:                               ; preds = %checkContinueBlock14, %mergeBlock, %checkContinueBlock12, %nestedBlock11
  br label %afterIfElse

nestedBlock11:                                    ; preds = %then
  %43 = load ptr, ptr %err, align 8
  %44 = getelementptr inbounds %"Err::Result", ptr %43, i32 0, i32 0
  %45 = load ptr, ptr %44, align 8
  %46 = getelementptr inbounds %"Err::Result::VTableType", ptr %45, i32 0, i32 5
  %47 = load ptr, ptr %46, align 8
  call void %47(ptr %rtPtr1, ptr %err)
  %48 = load ptr, ptr %rtPtr1, align 8
  %49 = call ptr @concat_strings(ptr @76, ptr %48)
  %50 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %50, ptr %49)
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock12, label %afterNestedBlock10

checkContinueBlock12:                             ; preds = %nestedBlock11
  %53 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %nestedBlock13, label %afterNestedBlock10

nestedBlock13:                                    ; preds = %checkContinueBlock12
  br label %returnBlock

checkContinueBlock14:                             ; preds = %mergeBlock
  br label %afterNestedBlock10

returnBlock:                                      ; preds = %nestedBlock13
  store i32 1, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %55 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %checkContinueBlock14, label %afterNestedBlock10

returnBlock15:                                    ; preds = %nestedBlock8
  store i32 0, ptr %0, align 4
  ret void

mergeBlock16:                                     ; No predecessors!
  %57 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %checkContinueBlock9, label %afterNestedBlock
}

define internal void @"assign_<Object<GameScreenType.10>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %GameScreenType.10, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %GameScreenType.10, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %GameScreenType.10, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %GameScreenType.10, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  ret void
}

define internal void @"assign_<Object<Texture.9>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Texture.9, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Texture.9, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %Texture.9, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %Texture.9, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %Texture.9, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  ret void
}

define internal void @"assign_<Object<Position.7>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Position.7, ptr %0, i32 0, i32 0
  store float 0.000000e+00, ptr %1, align 4
  %2 = getelementptr inbounds %Position.7, ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %2, align 4
  ret void
}

define internal void @"assign_<Array[9]<Object<Position.7>>:9,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 9
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 9
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [9 x %Position.7], ptr %0, i32 0, i32 %6
  call void @"assign_<Object<Position.7>"(ptr %7)
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

define internal void @"assign_<Array[5]<Object<AttributeType.11>>:5,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 5
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 5
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [5 x %AttributeType.11], ptr %0, i32 0, i32 %6
  call void @"assign_<Object<AttributeType.11>"(ptr %7)
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

define internal void @"assign_<Object<AttributeType.11>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %AttributeType.11, ptr %0, i32 0, i32 0
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %1)
  %2 = getelementptr inbounds %AttributeType.11, ptr %0, i32 0, i32 1
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %2)
  %3 = getelementptr inbounds %AttributeType.11, ptr %0, i32 0, i32 2
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %3)
  %4 = getelementptr inbounds %AttributeType.11, ptr %0, i32 0, i32 3
  store float 0.000000e+00, ptr %4, align 4
  ret void
}

define internal void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 4
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 4
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [4 x float], ptr %0, i32 0, i32 %6
  store float 0.000000e+00, ptr %7, align 4
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

define internal void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %0) {
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
  %7 = getelementptr [2 x float], ptr %0, i32 0, i32 %6
  store float 0.000000e+00, ptr %7, align 4
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

define internal void @"assign_<Object<OPTIONS_TYPE.12>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %OPTIONS_TYPE.12, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  ret void
}

define internal void @"assign_<Class<FlowWingAnim>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  store ptr @3, ptr %1, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  store ptr @4, ptr %4, align 8
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  call void @"assign_<Object<COLORS_TYPE.4>"(ptr %6)
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  call void @"assign_<Object<KEYS_TYPE.3>"(ptr %7)
  %8 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  call void @"assign_<Object<LOG_TYPE.5>"(ptr %8)
  ret void
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

define internal void @"assign_<Object<BoxWithText.6>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 0
  store ptr @31, ptr %1, align 8
  %2 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 6
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 7
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %BoxWithText.6, ptr %0, i32 0, i32 8
  store i32 0, ptr %9, align 4
  ret void
}

define internal void @"assign_<Class<Err::Result>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 0
  store ptr @49, ptr %1, align 8
  %2 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 1
  store ptr @50, ptr %2, align 8
  %3 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %"Err::Result", ptr %0, i32 0, i32 3
  store ptr @51, ptr %4, align 8
  ret void
}

define internal void @"assign_<Class<GameContext>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 0
  store ptr @55, ptr %1, align 8
  %2 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 1
  call void @"assign_<Class<Bird>>"(ptr %2)
  %3 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 2
  call void @"assign_<Class<Cloud>>"(ptr %3)
  %4 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 3
  call void @"assign_<Class<Ground>>"(ptr %4)
  %5 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 4
  call void @"assign_<Class<WideMountain>>"(ptr %5)
  %6 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 5
  call void @"assign_<Class<HeightedMountain>>"(ptr %6)
  %7 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 6
  call void @"assign_<Class<GreenMountain>>"(ptr %7)
  %8 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 7
  call void @"assign_<Class<BlackMountain>>"(ptr %8)
  %9 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 8
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %GameContext, ptr %0, i32 0, i32 9
  store i32 0, ptr %10, align 4
  ret void
}

define internal void @"assign_<Class<Bird>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 0
  store ptr @56, ptr %1, align 8
  %2 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  %4 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 3
  store float 0.000000e+00, ptr %4, align 4
  %5 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 4
  store float 0.000000e+00, ptr %5, align 4
  %6 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 5
  store double 0.000000e+00, ptr %6, align 8
  %7 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 6
  store double 0.000000e+00, ptr %7, align 8
  %8 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 7
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 8
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  store i1 false, ptr %10, align 1
  %11 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 10
  call void @"assign_<Array[9]<Object<Position.7>>:9,"(ptr %11)
  ret void
}

define internal void @"assign_<Class<Cloud>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 0
  store ptr @57, ptr %1, align 8
  %2 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  %4 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 3
  call void @"assign_<Array[5]<Object<AttributeType.11>>:5,"(ptr %4)
  ret void
}

define internal void @"assign_<Class<Ground>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Ground, ptr %0, i32 0, i32 0
  store ptr @58, ptr %1, align 8
  %2 = getelementptr inbounds %Ground, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %Ground, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  %4 = getelementptr inbounds %Ground, ptr %0, i32 0, i32 3
  call void @"assign_<Object<Texture.9>"(ptr %4)
  ret void
}

define internal void @"assign_<Class<WideMountain>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %WideMountain, ptr %0, i32 0, i32 0
  store ptr @59, ptr %1, align 8
  %2 = getelementptr inbounds %WideMountain, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %WideMountain, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  %4 = getelementptr inbounds %WideMountain, ptr %0, i32 0, i32 3
  call void @"assign_<Object<Position.7>"(ptr %4)
  %5 = getelementptr inbounds %WideMountain, ptr %0, i32 0, i32 4
  call void @"assign_<Object<Position.7>"(ptr %5)
  ret void
}

define internal void @"assign_<Class<HeightedMountain>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %HeightedMountain, ptr %0, i32 0, i32 0
  store ptr @60, ptr %1, align 8
  %2 = getelementptr inbounds %HeightedMountain, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %HeightedMountain, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  ret void
}

define internal void @"assign_<Class<GreenMountain>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %GreenMountain, ptr %0, i32 0, i32 0
  store ptr @61, ptr %1, align 8
  %2 = getelementptr inbounds %GreenMountain, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %GreenMountain, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  ret void
}

define internal void @"assign_<Class<BlackMountain>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %BlackMountain, ptr %0, i32 0, i32 0
  store ptr @62, ptr %1, align 8
  %2 = getelementptr inbounds %BlackMountain, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %BlackMountain, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Position.7>"(ptr %3)
  ret void
}

define internal void @"assign_<Class<TextureManager>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 0
  store ptr @63, ptr %1, align 8
  %2 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 1
  call void @"assign_<Object<Texture.9>"(ptr %2)
  %3 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 2
  call void @"assign_<Object<Texture.9>"(ptr %3)
  %4 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 3
  call void @"assign_<Object<Texture.9>"(ptr %4)
  %5 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 4
  call void @"assign_<Object<Texture.9>"(ptr %5)
  %6 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 5
  call void @"assign_<Object<Texture.9>"(ptr %6)
  %7 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 6
  call void @"assign_<Object<Texture.9>"(ptr %7)
  %8 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 7
  call void @"assign_<Object<Texture.9>"(ptr %8)
  %9 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 8
  call void @"assign_<Object<Texture.9>"(ptr %9)
  %10 = getelementptr inbounds %TextureManager, ptr %0, i32 0, i32 9
  call void @"assign_<Object<Texture.9>"(ptr %10)
  ret void
}

define internal void @"assign_<Class<MenuScreen>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 0
  store ptr @64, ptr %1, align 8
  %2 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 1
  call void @"assign_<Class<GameContext>>"(ptr %2)
  %3 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 2
  store ptr @65, ptr %3, align 8
  %4 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 3
  store ptr @66, ptr %4, align 8
  %5 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 4
  call void @"assign_<Object<OPTIONS_TYPE.12>"(ptr %5)
  %6 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 6
  store double 0.000000e+00, ptr %7, align 8
  %8 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 7
  store float 0.000000e+00, ptr %8, align 4
  %9 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 8
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 9
  store i32 0, ptr %10, align 4
  %11 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 10
  store i32 0, ptr %11, align 4
  %12 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 11
  store float 0.000000e+00, ptr %12, align 4
  %13 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 12
  store float 0.000000e+00, ptr %13, align 4
  %14 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 13
  store i32 0, ptr %14, align 4
  %15 = getelementptr inbounds %MenuScreen, ptr %0, i32 0, i32 14
  store i32 0, ptr %15, align 4
  ret void
}

define internal void @"assign_<Class<GameScreen>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %GameScreen, ptr %0, i32 0, i32 0
  store ptr @69, ptr %1, align 8
  %2 = getelementptr inbounds %GameScreen, ptr %0, i32 0, i32 1
  call void @"assign_<Class<GameContext>>"(ptr %2)
  %3 = getelementptr inbounds %GameScreen, ptr %0, i32 0, i32 2
  store ptr @70, ptr %3, align 8
  ret void
}

define internal void @"assign_<Class<PauseScreen>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %PauseScreen, ptr %0, i32 0, i32 0
  store ptr @72, ptr %1, align 8
  %2 = getelementptr inbounds %PauseScreen, ptr %0, i32 0, i32 1
  call void @"assign_<Class<GameContext>>"(ptr %2)
  ret void
}

define internal void @"assign_<Class<BirdGame>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %BirdGame, ptr %0, i32 0, i32 0
  store ptr @75, ptr %1, align 8
  %2 = getelementptr inbounds %BirdGame, ptr %0, i32 0, i32 1
  call void @"assign_<Class<TextureManager>>"(ptr %2)
  %3 = getelementptr inbounds %BirdGame, ptr %0, i32 0, i32 2
  call void @"assign_<Class<GameContext>>"(ptr %3)
  %4 = getelementptr inbounds %BirdGame, ptr %0, i32 0, i32 3
  call void @"assign_<Class<MenuScreen>>"(ptr %4)
  %5 = getelementptr inbounds %BirdGame, ptr %0, i32 0, i32 4
  call void @"assign_<Class<GameScreen>>"(ptr %5)
  %6 = getelementptr inbounds %BirdGame, ptr %0, i32 0, i32 5
  call void @"assign_<Class<PauseScreen>>"(ptr %6)
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
!30 = !{!"Err::Result.init1:rt:pr:27"}
!31 = !{!"Err::Result.init2:rt:pr:27"}
!32 = !{!"Err::Result.init3:rt:pr:27"}
!33 = !{!"Err::Result.getMessage:rt:pr:33"}
!34 = !{!"Err::Result.getCode:rt:pr:28"}
!35 = !{!"Err::Result.getDetails:rt:pr:33"}
!36 = !{!"Err::Result.withMessage:rt:ob:Err::Result"}
!37 = !{!"Err::Result.withDetails:rt:ob:Err::Result"}
!38 = !{!"Err::Result.toString:rt:pr:33"}
!39 = !{!"GameUnit.init2:rt:pr:27"}
!40 = !{!"GameUnit.init1:rt:pr:27"}
!41 = !{!"GameUnit.getTexture:rt:ob:Texture.9"}
!42 = !{!"GameUnit.getOrigin:rt:ob:Position.7"}
!43 = !{!"GameUnit.getOriginAsArray:rt:ay:32:sz:2:"}
!44 = !{!"GameUnit.draw:rt:pr:27"}
!45 = !{!"GameUnit.update:rt:pr:27"}
!46 = !{!"WideMountain.init1:rt:pr:27"}
!47 = !{!"WideMountain.update:rt:pr:27"}
!48 = !{!"WideMountain.draw:rt:pr:27"}
!49 = !{!"WideMountain.getOriginFirstMount:rt:ob:Position.7"}
!50 = !{!"WideMountain.getOriginSecondMount:rt:ob:Position.7"}
!51 = !{!"HeightedMountain.init1:rt:pr:27"}
!52 = !{!"HeightedMountain.update:rt:pr:27"}
!53 = !{!"HeightedMountain.draw:rt:pr:27"}
!54 = !{!"GreenMountain.init1:rt:pr:27"}
!55 = !{!"GreenMountain.update:rt:pr:27"}
!56 = !{!"GreenMountain.draw:rt:pr:27"}
!57 = !{!"BlackMountain.init1:rt:pr:27"}
!58 = !{!"BlackMountain.update:rt:pr:27"}
!59 = !{!"BlackMountain.draw:rt:pr:27"}
!60 = !{!"Bird.init1:rt:pr:27"}
!61 = !{!"Bird.update:rt:pr:27"}
!62 = !{!"Bird.handleInput:rt:pr:27"}
!63 = !{!"Bird.getSource:rt:ay:32:sz:4:"}
!64 = !{!"Bird.getDistination:rt:ay:32:sz:4:"}
!65 = !{!"Bird.getOriginAsArray:rt:ay:32:sz:2:"}
!66 = !{!"Bird.getRotation:rt:pr:32"}
!67 = !{!"Bird.updateY:rt:pr:27"}
!68 = !{!"Bird.draw:rt:pr:27"}
!69 = !{!"Cloud.init1:rt:pr:27"}
!70 = !{!"Cloud.update:rt:pr:27"}
!71 = !{!"Cloud.draw:rt:pr:27"}
!72 = !{!"Ground.init1:rt:pr:27"}
!73 = !{!"Ground.update:rt:pr:27"}
!74 = !{!"Ground.setWoodTexture:rt:pr:27"}
!75 = !{!"Ground.draw:rt:pr:27"}
!76 = !{!"GameContext.init1:rt:pr:27"}
!77 = !{!"GameContext.setCurrentGameScreen:rt:pr:27"}
!78 = !{!"GameContext.getCurrentGameScreen:rt:pr:28"}
!79 = !{!"GameContext.getGameScore:rt:pr:28"}
!80 = !{!"Screen.init1:rt:pr:27"}
!81 = !{!"Screen.drawScreen:rt:pr:27"}
!82 = !{!"Screen.updateScreen:rt:pr:27"}
!83 = !{!"MenuScreen.init1:rt:pr:27"}
!84 = !{!"MenuScreen.handleInput:rt:pr:27"}
!85 = !{!"MenuScreen.updateScreen:rt:pr:27"}
!86 = !{!"MenuScreen.drawScreen:rt:pr:27"}
!87 = !{!"MenuScreen.isMouseOverText:rt:pr:34"}
!88 = !{!"GameScreen.init1:rt:pr:27"}
!89 = !{!"GameScreen.drawScreen:rt:pr:27"}
!90 = !{!"GameScreen.handleInput:rt:pr:27"}
!91 = !{!"GameScreen.updateScreen:rt:pr:27"}
!92 = !{!"PauseScreen.init1:rt:pr:27"}
!93 = !{!"PauseScreen.drawScreen:rt:pr:27"}
!94 = !{!"PauseScreen.handleInput:rt:pr:27"}
!95 = !{!"PauseScreen.updateScreen:rt:pr:27"}
!96 = !{!"TextureManager.init0:rt:pr:27"}
!97 = !{!"TextureManager.loadAllTextures:rt:ob:Err::Result"}
!98 = !{!"TextureManager.hasAllTexturesLoaded:rt:ob:Err::Result"}
!99 = !{!"BirdGame.init0:rt:pr:27"}
!100 = !{!"BirdGame.Initialize:rt:ob:Err::Result"}
!101 = !{!"BirdGame.update:rt:pr:27"}
!102 = !{!"BirdGame.draw:rt:pr:27"}
!103 = !{!"BirdGame.runGameLoop:rt:pr:27"}
!104 = !{!"getSin:rt:pr:31"}
!105 = !{!"getRandomNumber:rt:pr:28"}
!106 = !{!"main:rt:pr:28"}
