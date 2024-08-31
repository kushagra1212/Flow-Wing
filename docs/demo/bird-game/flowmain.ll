; ModuleID = 'flowmain'
source_filename = "flowmain"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Bird::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Cloud::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%Position.4 = type { float, float }
%AttributeType.5 = type { [4 x float], [4 x float], [2 x float], float }
%Bird = type { ptr, float, float, double, double, i32, i32, ptr, i1, %Texture.0, [9 x %Position.4], %Position.4 }
%Cloud = type { ptr, [5 x %AttributeType.5], %Texture.0, ptr }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
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
@vtable.Bird.fg = common global %"Bird::VTableType" zeroinitializer
@vtable.Cloud.fg = common global %"Cloud::VTableType" zeroinitializer
@screenWidth = common global i32 0
@screenHeight = common global i32 0
@FPS = common global i32 0
@side = common global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [872 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m88| \1B[0m\1B[0m\0A\1B[0m\1B[33m89| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 86:32\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [950 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m88| \1B[0m\1B[0m\0A\1B[0m\1B[33m89| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 86:71\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [845 x i8] c"\0A\1B[33m160| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 164:14\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [859 x i8] c"\0A\1B[33m160| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 164:24\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@6 = private unnamed_addr constant [887 x i8] c"\0A\1B[33m160| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 164:35\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@7 = private unnamed_addr constant [901 x i8] c"\0A\1B[33m160| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 164:45\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@8 = private unnamed_addr constant [848 x i8] c"\0A\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m165| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                 \0A   ~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 165:17\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [862 x i8] c"\0A\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m165| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                           \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 165:27\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [851 x i8] c"\0A\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m\0A\1B[0m\1B[33m170| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 166:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [865 x i8] c"\0A\1B[33m162| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m167| \1B[0m\1B[0m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m\0A\1B[0m\1B[33m170| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 166:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [817 x i8] c"\0A\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m\0A\1B[0m\1B[33m170| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m171| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 167:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [831 x i8] c"\0A\1B[33m163| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      clouds[i].origin[0]= clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m165| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        clouds[i].origin[0]= Decimal32(getRandomNumber(-2 * screenWidth, -1 * screenWidth))\0A\1B[0m\1B[33m167| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1]= -1 * Decimal32(getRandomNumber(0, Int32(screenHeight / 3)))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m\0A\1B[0m\1B[33m170| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m171| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 167:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [782 x i8] c"\0A\1B[33m171| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m172| \1B[0m\1B[0m\0A\1B[0m\1B[33m173| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m174| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m175| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(cloudTexture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m176| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m177| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m178| \1B[0m\1B[0m\0A\1B[0m\1B[33m179| \1B[0m\1B[0m}\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 175:50\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [818 x i8] c"\0A\1B[33m171| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m172| \1B[0m\1B[0m\0A\1B[0m\1B[33m173| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m174| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m175| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(cloudTexture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m176| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m177| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m178| \1B[0m\1B[0m\0A\1B[0m\1B[33m179| \1B[0m\1B[0m}\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 175:68\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@16 = private unnamed_addr constant [864 x i8] c"\0A\1B[33m171| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m172| \1B[0m\1B[0m\0A\1B[0m\1B[33m173| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m174| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m175| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(cloudTexture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                           \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m176| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m177| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m178| \1B[0m\1B[0m\0A\1B[0m\1B[33m179| \1B[0m\1B[0m}\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 175:91\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@17 = private unnamed_addr constant [901 x i8] c"\0A\1B[33m171| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m172| \1B[0m\1B[0m\0A\1B[0m\1B[33m173| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m174| \1B[0m\1B[0m    for var i = 0 to 4 {\0A\1B[0m\1B[33m175| \1B[0m\1B[31m\1B[1m      fgAnim.drawTexturePro(cloudTexture, clouds[i].source, clouds[i].distination, clouds[i].origin, clouds[i].rotation, fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m176| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m177| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m178| \1B[0m\1B[0m\0A\1B[0m\1B[33m179| \1B[0m\1B[0m}\0A\1B[0m\1B[31mFile: bird.fg [Error] : \1B[1;31mLine 175:109\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/bird-game/bird.fg\0A\1B[0m\00", align 1
@18 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@22 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@25 = private unnamed_addr constant [18 x i8] c"./assets/bird.png\00", align 1
@26 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@27 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@28 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@29 = private unnamed_addr constant [21 x i8] c"./assets/3clouds.png\00", align 1
@30 = private unnamed_addr constant [27 x i8] c"./assets/skyBackground.png\00", align 1
@31 = private unnamed_addr constant [20 x i8] c"./assets/ground.png\00", align 1
@32 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL1.png\00", align 1
@33 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL2.png\00", align 1
@34 = private unnamed_addr constant [31 x i8] c"./assets/mountain/2mountL2.png\00", align 1
@35 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL3.png\00", align 1
@36 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1

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

define i32 @flowmain() {
entry:
  store i32 0, ptr @screenWidth, align 4
  store i32 0, ptr @screenHeight, align 4
  store i32 0, ptr @FPS, align 4
  store i32 0, ptr @side, align 4
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
  %birdTexturePath = alloca ptr, align 8
  store ptr @0, ptr %birdTexturePath, align 8
  %isBirdAlive = alloca i1, align 1
  store i1 false, ptr %isBirdAlive, align 1
  %birdTexture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %birdTexture)
  %birdSpritePosition = alloca [9 x %Position.4], align 8
  call void @"assign_<Array[9]<ObjectPosition.4>>:9,"(ptr %birdSpritePosition)
  %pos = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %pos)
  %clouds = alloca [5 x %AttributeType.5], align 8
  call void @"assign_<Array[5]<ObjectAttributeType.5>>:5,"(ptr %clouds)
  %cloudTexture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %cloudTexture)
  %texturePath = alloca ptr, align 8
  store ptr @1, ptr %texturePath, align 8
  %rtPtr = alloca i32, align 4
  %0 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim()
  %1 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random()
  store i32 1024, ptr @screenWidth, align 4
  store i32 500, ptr @screenHeight, align 4
  store i32 120, ptr @FPS, align 4
  store i32 10, ptr @side, align 4
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

declare !rt !9 void @FlowWingAnim.endDrawing(ptr)

declare !rt !10 void @FlowWingAnim.closeWindow(ptr)

declare !rt !11 void @FlowWingAnim.getTime(ptr, ptr)

declare !rt !12 void @FlowWingAnim.getFrameTime(ptr, ptr)

declare !rt !13 void @FlowWingAnim.getScreenHeight(ptr, ptr)

declare !rt !14 void @FlowWingAnim.getScreenWidth(ptr, ptr)

declare !rt !15 void @FlowWingAnim.drawCircle(ptr, ptr, ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !17 void @FlowWingAnim.drawTexture(ptr, ptr, ptr, ptr, ptr)

declare !rt !18 void @FlowWingAnim.drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !19 void @FlowWingAnim.traceLog(ptr, ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture(ptr, ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture(ptr, ptr)

declare !rt !22 void @FlowWingAnim.isKeyPressed(ptr, ptr, ptr)

declare !rt !23 void @FlowWingAnim.isKeyDown(ptr, ptr, ptr)

declare !rt !24 void @FlowWingAnim.textFormat(ptr, ptr, ptr)

define void @Bird.init1(ptr %0, ptr %1) !rt !25 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  %birdTexturePath = alloca ptr, align 8
  %14 = load ptr, ptr %0, align 8
  store ptr %14, ptr %birdTexturePath, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = load ptr, ptr %1, align 8
  %16 = getelementptr inbounds %Bird, ptr %15, i32 0, i32 7
  %birdTexturePath7 = load ptr, ptr %16, align 8
  %birdTexturePath8 = load ptr, ptr %birdTexturePath, align 8
  %17 = load ptr, ptr %birdTexturePath, align 8
  store ptr %17, ptr %16, align 8
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %20 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %22 = load ptr, ptr %1, align 8
  %23 = getelementptr inbounds %Bird, ptr %22, i32 0, i32 4
  %birdTimmer = load double, ptr %23, align 8
  %BIRD_TIMMER = load double, ptr %5, align 8
  %24 = load double, ptr %5, align 8
  store double %24, ptr %23, align 8
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %27 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %29 = load ptr, ptr %1, align 8
  %30 = getelementptr inbounds %Bird, ptr %29, i32 0, i32 8
  %isBirdAlive = load i1, ptr %30, align 1
  store i1 true, ptr %30, align 1
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %33 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %35 = load ptr, ptr %1, align 8
  %36 = getelementptr inbounds %Bird, ptr %35, i32 0, i32 10
  %37 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 0
  %38 = getelementptr inbounds %Position.4, ptr %37, i32 0, i32 0
  store float 0.000000e+00, ptr %38, align 4
  %39 = getelementptr inbounds %Position.4, ptr %37, i32 0, i32 1
  store float 0.000000e+00, ptr %39, align 4
  %40 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 1
  %41 = getelementptr inbounds %Position.4, ptr %40, i32 0, i32 0
  %ACTUAL_BIRD_SIZE = load float, ptr %3, align 4
  %42 = load float, ptr %3, align 4
  %43 = fmul float %42, 1.000000e+00
  store float %43, ptr %41, align 4
  %44 = getelementptr inbounds %Position.4, ptr %40, i32 0, i32 1
  store float 0.000000e+00, ptr %44, align 4
  %45 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 2
  %46 = getelementptr inbounds %Position.4, ptr %45, i32 0, i32 0
  %ACTUAL_BIRD_SIZE9 = load float, ptr %3, align 4
  %47 = load float, ptr %3, align 4
  %48 = fmul float %47, 2.000000e+00
  store float %48, ptr %46, align 4
  %49 = getelementptr inbounds %Position.4, ptr %45, i32 0, i32 1
  store float 0.000000e+00, ptr %49, align 4
  %50 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 3
  %51 = getelementptr inbounds %Position.4, ptr %50, i32 0, i32 0
  store float 0.000000e+00, ptr %51, align 4
  %52 = getelementptr inbounds %Position.4, ptr %50, i32 0, i32 1
  %ACTUAL_BIRD_SIZE10 = load float, ptr %3, align 4
  %53 = load float, ptr %3, align 4
  %54 = fmul float %53, 1.000000e+00
  store float %54, ptr %52, align 4
  %55 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 4
  %56 = getelementptr inbounds %Position.4, ptr %55, i32 0, i32 0
  %ACTUAL_BIRD_SIZE11 = load float, ptr %3, align 4
  %57 = load float, ptr %3, align 4
  %58 = fmul float %57, 1.000000e+00
  store float %58, ptr %56, align 4
  %59 = getelementptr inbounds %Position.4, ptr %55, i32 0, i32 1
  %ACTUAL_BIRD_SIZE12 = load float, ptr %3, align 4
  %60 = load float, ptr %3, align 4
  %61 = fmul float %60, 1.000000e+00
  store float %61, ptr %59, align 4
  %62 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 5
  %63 = getelementptr inbounds %Position.4, ptr %62, i32 0, i32 0
  %ACTUAL_BIRD_SIZE13 = load float, ptr %3, align 4
  %64 = load float, ptr %3, align 4
  %65 = fmul float %64, 2.000000e+00
  store float %65, ptr %63, align 4
  %66 = getelementptr inbounds %Position.4, ptr %62, i32 0, i32 1
  %ACTUAL_BIRD_SIZE14 = load float, ptr %3, align 4
  %67 = load float, ptr %3, align 4
  %68 = fmul float %67, 1.000000e+00
  store float %68, ptr %66, align 4
  %69 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 6
  %70 = getelementptr inbounds %Position.4, ptr %69, i32 0, i32 0
  store float 0.000000e+00, ptr %70, align 4
  %71 = getelementptr inbounds %Position.4, ptr %69, i32 0, i32 1
  %ACTUAL_BIRD_SIZE15 = load float, ptr %3, align 4
  %72 = load float, ptr %3, align 4
  %73 = fmul float %72, 2.000000e+00
  store float %73, ptr %71, align 4
  %74 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 7
  %75 = getelementptr inbounds %Position.4, ptr %74, i32 0, i32 0
  %ACTUAL_BIRD_SIZE16 = load float, ptr %3, align 4
  %76 = load float, ptr %3, align 4
  %77 = fmul float %76, 1.000000e+00
  store float %77, ptr %75, align 4
  %78 = getelementptr inbounds %Position.4, ptr %74, i32 0, i32 1
  %ACTUAL_BIRD_SIZE17 = load float, ptr %3, align 4
  %79 = load float, ptr %3, align 4
  %80 = fmul float %79, 2.000000e+00
  store float %80, ptr %78, align 4
  %81 = getelementptr [9 x %Position.4], ptr %36, i32 0, i32 8
  %82 = getelementptr inbounds %Position.4, ptr %81, i32 0, i32 0
  %ACTUAL_BIRD_SIZE18 = load float, ptr %3, align 4
  %83 = load float, ptr %3, align 4
  %84 = fmul float %83, 2.000000e+00
  store float %84, ptr %82, align 4
  %85 = getelementptr inbounds %Position.4, ptr %81, i32 0, i32 1
  %ACTUAL_BIRD_SIZE19 = load float, ptr %3, align 4
  %86 = load float, ptr %3, align 4
  %87 = fmul float %86, 2.000000e+00
  store float %87, ptr %85, align 4
  %88 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %89 = icmp eq i32 %88, 0
  br i1 %89, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @Bird.setTexture(ptr %0, ptr %1) !rt !26 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  %birdTexture = alloca %Texture.0, align 8
  %14 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %14, ptr %birdTexture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = load ptr, ptr %1, align 8
  %16 = getelementptr inbounds %Bird, ptr %15, i32 0, i32 9
  %17 = load %Texture.0, ptr %birdTexture, align 4
  store %Texture.0 %17, ptr %16, align 4
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Bird.getTexturePath(ptr %0, ptr %1) !rt !27 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %14 = load ptr, ptr %1, align 8
  %15 = getelementptr inbounds %Bird, ptr %14, i32 0, i32 7
  %birdTexturePath = load ptr, ptr %15, align 8
  %16 = load ptr, ptr %15, align 8
  store ptr %16, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.update(ptr %0, ptr %1) !rt !28 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  %frameTime = alloca float, align 4
  %14 = load float, ptr %0, align 4
  store float %14, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %birdTimmer = load double, ptr %6, align 8
  %birdTimmer3 = load double, ptr %6, align 8
  %15 = load double, ptr %6, align 8
  %frameTime4 = load float, ptr %frameTime, align 4
  %16 = load float, ptr %frameTime, align 4
  %17 = fpext float %16 to double
  %18 = fsub double %15, %17
  store double %18, ptr %6, align 8
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %21 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %birdTimmer5 = load double, ptr %6, align 8
  %23 = load double, ptr %6, align 8
  %24 = fcmp olt double %23, 0.000000e+00
  br i1 %24, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse20, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %birdTimmer15 = load double, ptr %6, align 8
  %BIRD_TIMMER = load double, ptr %5, align 8
  %27 = load double, ptr %5, align 8
  store double %27, ptr %6, align 8
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock9, label %afterNestedBlock6

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %birdSpriteIndex = load i32, ptr %8, align 4
  %birdSpriteIndex16 = load i32, ptr %8, align 4
  %32 = load i32, ptr %8, align 4
  %33 = add i32 %32, 1
  store i32 %33, ptr %8, align 4
  %34 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %checkContinueBlock10, label %afterNestedBlock6

checkContinueBlock10:                             ; preds = %nestedBlock9
  %36 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %nestedBlock11, label %afterNestedBlock6

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %birdSpriteIndex17 = load i32, ptr %8, align 4
  %38 = load i32, ptr %8, align 4
  %BIRD_SPRITE_SIZE = load i32, ptr %7, align 4
  %39 = load i32, ptr %7, align 4
  %40 = icmp sge i32 %38, %39
  br i1 %40, label %then18, label %else19

checkContinueBlock12:                             ; preds = %afterIfElse20
  %41 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock13, label %afterNestedBlock6

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %43 = getelementptr inbounds %Position.4, ptr %13, i32 0, i32 1
  %y = load float, ptr %43, align 4
  %44 = getelementptr inbounds %Position.4, ptr %13, i32 0, i32 1
  %y25 = load float, ptr %44, align 4
  %45 = load float, ptr %44, align 4
  %frameTime26 = load float, ptr %frameTime, align 4
  %46 = load float, ptr %frameTime, align 4
  %47 = fmul float %46, -1.490000e+02
  %48 = fadd float %45, %47
  store float %48, ptr %43, align 4
  %49 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %checkContinueBlock14, label %afterNestedBlock6

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock6

then18:                                           ; preds = %nestedBlock11
  br label %nestedBlock22

else19:                                           ; preds = %nestedBlock11
  br label %afterIfElse20

afterIfElse20:                                    ; preds = %else19, %afterNestedBlock21
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock12, label %afterNestedBlock6

afterNestedBlock21:                               ; preds = %checkContinueBlock23, %nestedBlock22
  br label %afterIfElse20

nestedBlock22:                                    ; preds = %then18
  %birdSpriteIndex24 = load i32, ptr %8, align 4
  store i32 0, ptr %8, align 4
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock23, label %afterNestedBlock21

checkContinueBlock23:                             ; preds = %nestedBlock22
  br label %afterNestedBlock21
}

define void @Bird.isTextureLoaded(ptr %0, ptr %1) !rt !29 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %14 = load ptr, ptr %1, align 8
  %15 = getelementptr inbounds %Bird, ptr %14, i32 0, i32 9
  %16 = getelementptr inbounds %Texture.0, ptr %15, i32 0, i32 0
  %id = load i32, ptr %16, align 4
  %17 = load i32, ptr %16, align 4
  %18 = icmp ne i32 %17, 0
  store i1 %18, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getSource(ptr %0, ptr %1) !rt !30 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %14 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %birdSpriteIndex = load i32, ptr %8, align 4
  %birdSpritePosition = load [9 x %Position.4], ptr %12, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %birdSpriteIndex, 9
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %birdSpriteIndex, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

mergeBlock:                                       ; No predecessors!
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %returnBlock
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %returnBlock
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %17 = getelementptr [9 x %Position.4], ptr %12, i32 0, i32 %birdSpriteIndex
  %18 = getelementptr inbounds %Position.4, ptr %17, i32 0, i32 0
  %x = load float, ptr %18, align 4
  %19 = load float, ptr %18, align 4
  store float %19, ptr %14, align 4
  %20 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %birdSpriteIndex1 = load i32, ptr %8, align 4
  %birdSpritePosition2 = load [9 x %Position.4], ptr %12, align 4
  %"GlobalIndexExpr::isLessThan6" = icmp slt i32 %birdSpriteIndex1, 9
  %"GlobalIndexExpr::isGreaterThan7" = icmp sge i32 %birdSpriteIndex1, 0
  %"GlobalIndexExpr::isWithinBounds8" = and i1 %"GlobalIndexExpr::isLessThan6", %"GlobalIndexExpr::isGreaterThan7"
  br i1 %"GlobalIndexExpr::isWithinBounds8", label %"GlobalIndexExpr::then3", label %"GlobalIndexExpr::else4"

"GlobalIndexExpr::then3":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge5"

"GlobalIndexExpr::else4":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @3)
  br label %"GlobalIndexExpr::merge5"

"GlobalIndexExpr::merge5":                        ; preds = %"GlobalIndexExpr::else4", %"GlobalIndexExpr::then3"
  %21 = getelementptr [9 x %Position.4], ptr %12, i32 0, i32 %birdSpriteIndex1
  %22 = getelementptr inbounds %Position.4, ptr %21, i32 0, i32 1
  %y = load float, ptr %22, align 4
  %23 = load float, ptr %22, align 4
  store float %23, ptr %20, align 4
  %24 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %ACTUAL_BIRD_SIZE = load float, ptr %3, align 4
  %25 = load float, ptr %3, align 4
  store float %25, ptr %24, align 4
  %26 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %ACTUAL_BIRD_SIZE9 = load float, ptr %3, align 4
  %27 = load float, ptr %3, align 4
  store float %27, ptr %26, align 4
  ret void
}

define void @Bird.getDistination(ptr %0, ptr %1) !rt !31 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %14 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %15 = load i32, ptr @screenWidth, align 4
  %16 = sitofp i32 %15 to double
  %17 = fdiv double %16, 3.000000e+00
  %birdSize = load float, ptr %4, align 4
  %18 = load float, ptr %4, align 4
  %19 = fdiv float %18, 2.000000e+00
  %20 = fptrunc double %17 to float
  %21 = fsub float %20, %19
  store float %21, ptr %14, align 4
  %22 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %23 = load i32, ptr @screenHeight, align 4
  %24 = sitofp i32 %23 to double
  %25 = fdiv double %24, 2.000000e+00
  %birdSize1 = load float, ptr %4, align 4
  %26 = load float, ptr %4, align 4
  %27 = fdiv float %26, 2.000000e+00
  %28 = fptrunc double %25 to float
  %29 = fsub float %28, %27
  store float %29, ptr %22, align 4
  %30 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %birdSize2 = load float, ptr %4, align 4
  %31 = load float, ptr %4, align 4
  store float %31, ptr %30, align 4
  %32 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %birdSize3 = load float, ptr %4, align 4
  %33 = load float, ptr %4, align 4
  store float %33, ptr %32, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %34 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getOrigin(ptr %0, ptr %1) !rt !32 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %14 = getelementptr [2 x float], ptr %0, i32 0, i32 0
  %15 = load ptr, ptr %1, align 8
  %16 = getelementptr inbounds %Bird, ptr %15, i32 0, i32 11
  %17 = getelementptr inbounds %Position.4, ptr %16, i32 0, i32 0
  %x = load float, ptr %17, align 4
  %18 = load float, ptr %17, align 4
  store float %18, ptr %14, align 4
  %19 = getelementptr [2 x float], ptr %0, i32 0, i32 1
  %20 = load ptr, ptr %1, align 8
  %21 = getelementptr inbounds %Bird, ptr %20, i32 0, i32 11
  %22 = getelementptr inbounds %Position.4, ptr %21, i32 0, i32 1
  %y = load float, ptr %22, align 4
  %23 = load float, ptr %22, align 4
  store float %23, ptr %19, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getRotation(ptr %0, ptr %1) !rt !33 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
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
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getTexture(ptr %0, ptr %1) !rt !34 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %14 = load ptr, ptr %1, align 8
  %15 = getelementptr inbounds %Bird, ptr %14, i32 0, i32 9
  %16 = load %Texture.0, ptr %15, align 4
  store %Texture.0 %16, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.updateY(ptr %0, ptr %1) !rt !35 {
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
  %13 = getelementptr inbounds %Bird, ptr %2, i32 0, i32 11
  %frameTime = alloca float, align 4
  %14 = load float, ptr %0, align 4
  store float %14, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %15 = getelementptr inbounds %Position.4, ptr %13, i32 0, i32 1
  %y = load float, ptr %15, align 4
  %16 = getelementptr inbounds %Position.4, ptr %13, i32 0, i32 1
  %y1 = load float, ptr %16, align 4
  %17 = load float, ptr %16, align 4
  %frameTime2 = load float, ptr %frameTime, align 4
  %18 = load float, ptr %frameTime, align 4
  %19 = fmul float %18, 3.010000e+02
  %20 = fadd float %17, %19
  store float %20, ptr %15, align 4
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Cloud.init1(ptr %0, ptr %1) !rt !36 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  %texturePath = alloca ptr, align 8
  %6 = load ptr, ptr %0, align 8
  store ptr %6, ptr %texturePath, align 8
  %rtPtr = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %rtPtr1 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %rtPtr2 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %rtPtr3 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %rtPtr4 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %rtPtr5 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %rtPtr6 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %rtPtr7 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %rtPtr8 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %rtPtr9 = alloca i32, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock11, %nestedBlock10, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %27 = load ptr, ptr %1, align 8
  %28 = getelementptr inbounds %Cloud, ptr %27, i32 0, i32 3
  %texturePath12 = load ptr, ptr %28, align 8
  %texturePath13 = load ptr, ptr %texturePath, align 8
  %29 = load ptr, ptr %texturePath, align 8
  store ptr %29, ptr %28, align 8
  %30 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %32 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock
  %34 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 0
  %35 = getelementptr inbounds %AttributeType.5, ptr %34, i32 0, i32 0
  %36 = getelementptr [4 x float], ptr %35, i32 0, i32 0
  store float 0.000000e+00, ptr %36, align 4
  %37 = getelementptr [4 x float], ptr %35, i32 0, i32 1
  store float 0.000000e+00, ptr %37, align 4
  %38 = getelementptr [4 x float], ptr %35, i32 0, i32 2
  store float 2.500000e+02, ptr %38, align 4
  %39 = getelementptr [4 x float], ptr %35, i32 0, i32 3
  store float 1.660000e+02, ptr %39, align 4
  %40 = getelementptr inbounds %AttributeType.5, ptr %34, i32 0, i32 1
  %41 = getelementptr [4 x float], ptr %40, i32 0, i32 0
  store float 0.000000e+00, ptr %41, align 4
  %42 = getelementptr [4 x float], ptr %40, i32 0, i32 1
  store float 0.000000e+00, ptr %42, align 4
  %43 = getelementptr [4 x float], ptr %40, i32 0, i32 2
  store float 0x4062D34700000000, ptr %43, align 4
  %44 = getelementptr [4 x float], ptr %40, i32 0, i32 3
  store float 1.000000e+02, ptr %44, align 4
  %45 = getelementptr inbounds %AttributeType.5, ptr %34, i32 0, i32 2
  %46 = getelementptr [2 x float], ptr %45, i32 0, i32 0
  %screenWidth = load i32, ptr @screenWidth, align 4
  %47 = load i32, ptr @screenWidth, align 4
  %48 = mul i32 -1, %47
  store i32 %48, ptr %7, align 4
  store i32 0, ptr %8, align 4
  call void @getRandomNumber(ptr %rtPtr, ptr %7, ptr %8)
  %49 = load i32, ptr %rtPtr, align 4
  %50 = sitofp i32 %49 to float
  store float %50, ptr %46, align 4
  %51 = getelementptr [2 x float], ptr %45, i32 0, i32 1
  store i32 0, ptr %9, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %52 = load i32, ptr @screenHeight, align 4
  %53 = sitofp i32 %52 to double
  %54 = fdiv double %53, 3.000000e+00
  %55 = fptosi double %54 to i32
  store i32 %55, ptr %10, align 4
  call void @getRandomNumber(ptr %rtPtr1, ptr %9, ptr %10)
  %56 = load i32, ptr %rtPtr1, align 4
  %57 = sitofp i32 %56 to float
  %58 = fmul float -1.000000e+00, %57
  store float %58, ptr %51, align 4
  %59 = getelementptr inbounds %AttributeType.5, ptr %34, i32 0, i32 3
  store float 0.000000e+00, ptr %59, align 4
  %60 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 1
  %61 = getelementptr inbounds %AttributeType.5, ptr %60, i32 0, i32 0
  %62 = getelementptr [4 x float], ptr %61, i32 0, i32 0
  store float 2.500000e+02, ptr %62, align 4
  %63 = getelementptr [4 x float], ptr %61, i32 0, i32 1
  store float 0.000000e+00, ptr %63, align 4
  %64 = getelementptr [4 x float], ptr %61, i32 0, i32 2
  store float 2.500000e+02, ptr %64, align 4
  %65 = getelementptr [4 x float], ptr %61, i32 0, i32 3
  store float 1.660000e+02, ptr %65, align 4
  %66 = getelementptr inbounds %AttributeType.5, ptr %60, i32 0, i32 1
  %67 = getelementptr [4 x float], ptr %66, i32 0, i32 0
  store float 0.000000e+00, ptr %67, align 4
  %68 = getelementptr [4 x float], ptr %66, i32 0, i32 1
  store float 0.000000e+00, ptr %68, align 4
  %69 = getelementptr [4 x float], ptr %66, i32 0, i32 2
  store float 0x4062D34700000000, ptr %69, align 4
  %70 = getelementptr [4 x float], ptr %66, i32 0, i32 3
  store float 1.000000e+02, ptr %70, align 4
  %71 = getelementptr inbounds %AttributeType.5, ptr %60, i32 0, i32 2
  %72 = getelementptr [2 x float], ptr %71, i32 0, i32 0
  %screenWidth14 = load i32, ptr @screenWidth, align 4
  %73 = load i32, ptr @screenWidth, align 4
  %74 = mul i32 -1, %73
  store i32 %74, ptr %11, align 4
  store i32 0, ptr %12, align 4
  call void @getRandomNumber(ptr %rtPtr2, ptr %11, ptr %12)
  %75 = load i32, ptr %rtPtr2, align 4
  %76 = sitofp i32 %75 to float
  store float %76, ptr %72, align 4
  %77 = getelementptr [2 x float], ptr %71, i32 0, i32 1
  store i32 0, ptr %13, align 4
  %screenHeight15 = load i32, ptr @screenHeight, align 4
  %78 = load i32, ptr @screenHeight, align 4
  %79 = sitofp i32 %78 to double
  %80 = fdiv double %79, 3.000000e+00
  %81 = fptosi double %80 to i32
  store i32 %81, ptr %14, align 4
  call void @getRandomNumber(ptr %rtPtr3, ptr %13, ptr %14)
  %82 = load i32, ptr %rtPtr3, align 4
  %83 = sitofp i32 %82 to float
  %84 = fmul float -1.000000e+00, %83
  store float %84, ptr %77, align 4
  %85 = getelementptr inbounds %AttributeType.5, ptr %60, i32 0, i32 3
  store float 0.000000e+00, ptr %85, align 4
  %86 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 2
  %87 = getelementptr inbounds %AttributeType.5, ptr %86, i32 0, i32 0
  %88 = getelementptr [4 x float], ptr %87, i32 0, i32 0
  store float 0.000000e+00, ptr %88, align 4
  %89 = getelementptr [4 x float], ptr %87, i32 0, i32 1
  store float 1.660000e+02, ptr %89, align 4
  %90 = getelementptr [4 x float], ptr %87, i32 0, i32 2
  store float 5.000000e+02, ptr %90, align 4
  %91 = getelementptr [4 x float], ptr %87, i32 0, i32 3
  store float 1.660000e+02, ptr %91, align 4
  %92 = getelementptr inbounds %AttributeType.5, ptr %86, i32 0, i32 1
  %93 = getelementptr [4 x float], ptr %92, i32 0, i32 0
  store float 0.000000e+00, ptr %93, align 4
  %94 = getelementptr [4 x float], ptr %92, i32 0, i32 1
  store float 0.000000e+00, ptr %94, align 4
  %95 = getelementptr [4 x float], ptr %92, i32 0, i32 2
  store float 0x4062D34700000000, ptr %95, align 4
  %96 = getelementptr [4 x float], ptr %92, i32 0, i32 3
  store float 1.000000e+02, ptr %96, align 4
  %97 = getelementptr inbounds %AttributeType.5, ptr %86, i32 0, i32 2
  %98 = getelementptr [2 x float], ptr %97, i32 0, i32 0
  %screenWidth16 = load i32, ptr @screenWidth, align 4
  %99 = load i32, ptr @screenWidth, align 4
  %100 = mul i32 -1, %99
  store i32 %100, ptr %15, align 4
  store i32 0, ptr %16, align 4
  call void @getRandomNumber(ptr %rtPtr4, ptr %15, ptr %16)
  %101 = load i32, ptr %rtPtr4, align 4
  %102 = sitofp i32 %101 to float
  store float %102, ptr %98, align 4
  %103 = getelementptr [2 x float], ptr %97, i32 0, i32 1
  store i32 0, ptr %17, align 4
  %screenHeight17 = load i32, ptr @screenHeight, align 4
  %104 = load i32, ptr @screenHeight, align 4
  %105 = sitofp i32 %104 to double
  %106 = fdiv double %105, 3.000000e+00
  %107 = fptosi double %106 to i32
  store i32 %107, ptr %18, align 4
  call void @getRandomNumber(ptr %rtPtr5, ptr %17, ptr %18)
  %108 = load i32, ptr %rtPtr5, align 4
  %109 = sitofp i32 %108 to float
  %110 = fmul float -1.000000e+00, %109
  store float %110, ptr %103, align 4
  %111 = getelementptr inbounds %AttributeType.5, ptr %86, i32 0, i32 3
  store float 0.000000e+00, ptr %111, align 4
  %112 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 3
  %113 = getelementptr inbounds %AttributeType.5, ptr %112, i32 0, i32 0
  %114 = getelementptr [4 x float], ptr %113, i32 0, i32 0
  store float 0.000000e+00, ptr %114, align 4
  %115 = getelementptr [4 x float], ptr %113, i32 0, i32 1
  store float 3.320000e+02, ptr %115, align 4
  %116 = getelementptr [4 x float], ptr %113, i32 0, i32 2
  store float 2.500000e+02, ptr %116, align 4
  %117 = getelementptr [4 x float], ptr %113, i32 0, i32 3
  store float 1.660000e+02, ptr %117, align 4
  %118 = getelementptr inbounds %AttributeType.5, ptr %112, i32 0, i32 1
  %119 = getelementptr [4 x float], ptr %118, i32 0, i32 0
  store float 0.000000e+00, ptr %119, align 4
  %120 = getelementptr [4 x float], ptr %118, i32 0, i32 1
  store float 0.000000e+00, ptr %120, align 4
  %121 = getelementptr [4 x float], ptr %118, i32 0, i32 2
  store float 0x4062D34700000000, ptr %121, align 4
  %122 = getelementptr [4 x float], ptr %118, i32 0, i32 3
  store float 1.000000e+02, ptr %122, align 4
  %123 = getelementptr inbounds %AttributeType.5, ptr %112, i32 0, i32 2
  %124 = getelementptr [2 x float], ptr %123, i32 0, i32 0
  %screenWidth18 = load i32, ptr @screenWidth, align 4
  %125 = load i32, ptr @screenWidth, align 4
  %126 = mul i32 -1, %125
  store i32 %126, ptr %19, align 4
  store i32 0, ptr %20, align 4
  call void @getRandomNumber(ptr %rtPtr6, ptr %19, ptr %20)
  %127 = load i32, ptr %rtPtr6, align 4
  %128 = sitofp i32 %127 to float
  store float %128, ptr %124, align 4
  %129 = getelementptr [2 x float], ptr %123, i32 0, i32 1
  store i32 0, ptr %21, align 4
  %screenHeight19 = load i32, ptr @screenHeight, align 4
  %130 = load i32, ptr @screenHeight, align 4
  %131 = sitofp i32 %130 to double
  %132 = fdiv double %131, 3.000000e+00
  %133 = fptosi double %132 to i32
  store i32 %133, ptr %22, align 4
  call void @getRandomNumber(ptr %rtPtr7, ptr %21, ptr %22)
  %134 = load i32, ptr %rtPtr7, align 4
  %135 = sitofp i32 %134 to float
  %136 = fmul float -1.000000e+00, %135
  store float %136, ptr %129, align 4
  %137 = getelementptr inbounds %AttributeType.5, ptr %112, i32 0, i32 3
  store float 0.000000e+00, ptr %137, align 4
  %138 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 4
  %139 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 0
  %140 = getelementptr [4 x float], ptr %139, i32 0, i32 0
  store float 2.500000e+02, ptr %140, align 4
  %141 = getelementptr [4 x float], ptr %139, i32 0, i32 1
  store float 3.320000e+02, ptr %141, align 4
  %142 = getelementptr [4 x float], ptr %139, i32 0, i32 2
  store float 2.500000e+02, ptr %142, align 4
  %143 = getelementptr [4 x float], ptr %139, i32 0, i32 3
  store float 1.660000e+02, ptr %143, align 4
  %144 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 1
  %145 = getelementptr [4 x float], ptr %144, i32 0, i32 0
  store float 0.000000e+00, ptr %145, align 4
  %146 = getelementptr [4 x float], ptr %144, i32 0, i32 1
  store float 0.000000e+00, ptr %146, align 4
  %147 = getelementptr [4 x float], ptr %144, i32 0, i32 2
  store float 0x4062D34700000000, ptr %147, align 4
  %148 = getelementptr [4 x float], ptr %144, i32 0, i32 3
  store float 1.000000e+02, ptr %148, align 4
  %149 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 2
  %150 = getelementptr [2 x float], ptr %149, i32 0, i32 0
  %screenWidth20 = load i32, ptr @screenWidth, align 4
  %151 = load i32, ptr @screenWidth, align 4
  %152 = mul i32 -1, %151
  store i32 %152, ptr %23, align 4
  store i32 0, ptr %24, align 4
  call void @getRandomNumber(ptr %rtPtr8, ptr %23, ptr %24)
  %153 = load i32, ptr %rtPtr8, align 4
  %154 = sitofp i32 %153 to float
  store float %154, ptr %150, align 4
  %155 = getelementptr [2 x float], ptr %149, i32 0, i32 1
  store i32 0, ptr %25, align 4
  %screenHeight21 = load i32, ptr @screenHeight, align 4
  %156 = load i32, ptr @screenHeight, align 4
  %157 = sitofp i32 %156 to double
  %158 = fdiv double %157, 3.000000e+00
  %159 = fptosi double %158 to i32
  store i32 %159, ptr %26, align 4
  call void @getRandomNumber(ptr %rtPtr9, ptr %25, ptr %26)
  %160 = load i32, ptr %rtPtr9, align 4
  %161 = sitofp i32 %160 to float
  %162 = fmul float -1.000000e+00, %161
  store float %162, ptr %155, align 4
  %163 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 3
  store float 0.000000e+00, ptr %163, align 4
  %164 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %165 = icmp eq i32 %164, 0
  br i1 %165, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  br label %afterNestedBlock
}

define void @Cloud.setTexture(ptr %0, ptr %1) !rt !37 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  %cloudTexture = alloca %Texture.0, align 8
  %6 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %6, ptr %cloudTexture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = load ptr, ptr %1, align 8
  %8 = getelementptr inbounds %Cloud, ptr %7, i32 0, i32 2
  %9 = load %Texture.0, ptr %cloudTexture, align 4
  store %Texture.0 %9, ptr %8, align 4
  %10 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Cloud.getTexture(ptr %0, ptr %1) !rt !38 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %Cloud, ptr %6, i32 0, i32 2
  %8 = load %Texture.0, ptr %7, align 4
  store %Texture.0 %8, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.getTexturePath(ptr %0, ptr %1) !rt !39 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %Cloud, ptr %6, i32 0, i32 3
  %texturePath = load ptr, ptr %7, align 8
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.update(ptr %0, ptr %1) !rt !40 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  %frameTime = alloca float, align 4
  %6 = load float, ptr %0, align 4
  store float %6, ptr %frameTime, align 4
  %i = alloca %DynamicType, align 8
  %rtPtr = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %rtPtr1 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block58
  ret void

nestedBlock:                                      ; preds = %entry
  %19 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %19, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock:                               ; preds = %end_block58
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock2, %nestedBlock
  %20 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock3

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %22 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %end_block58, label %decrement_block57

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %26 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %27 = sub i32 %26, 1
  store i32 %27, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %28 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %29 = load i32, ptr %28, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %30 = icmp sge i32 %29, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %31 = icmp sle i32 %29, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %32 = phi i1 [ %30, %"ForLoop::Conditon::trueBlock" ], [ %31, %"ForLoop::Conditon::falseBlock" ]
  br i1 %32, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock2:                                ; preds = %checkContinueBlock6, %afterIfElse, %checkContinueBlock4, %"GlobalIndexExpr::merge19"
  %33 = add i32 %29, 1
  store i32 %33, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock3:                                     ; preds = %"ForLoop::loopBody"
  %34 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %35 = load i32, ptr %34, align 4
  %clouds = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %35, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %35, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock4:                              ; preds = %"GlobalIndexExpr::merge19"
  %36 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %nestedBlock5, label %afterNestedBlock2

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %38 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %39 = load i32, ptr %38, align 4
  %clouds21 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan25" = icmp slt i32 %39, 5
  %"GlobalIndexExpr::isGreaterThan26" = icmp sge i32 %39, 0
  %"GlobalIndexExpr::isWithinBounds27" = and i1 %"GlobalIndexExpr::isLessThan25", %"GlobalIndexExpr::isGreaterThan26"
  br i1 %"GlobalIndexExpr::isWithinBounds27", label %"GlobalIndexExpr::then22", label %"GlobalIndexExpr::else23"

checkContinueBlock6:                              ; preds = %afterIfElse
  br label %afterNestedBlock2

"GlobalIndexExpr::then":                          ; preds = %nestedBlock3
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock3
  call void @raise_exception(ptr @4)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %40 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %35
  %41 = getelementptr inbounds %AttributeType.5, ptr %40, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then7", label %"GlobalIndexExpr::else8"

"GlobalIndexExpr::then7":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge9"

"GlobalIndexExpr::else8":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @5)
  br label %"GlobalIndexExpr::merge9"

"GlobalIndexExpr::merge9":                        ; preds = %"GlobalIndexExpr::else8", %"GlobalIndexExpr::then7"
  %42 = getelementptr [2 x float], ptr %41, i32 0, i32 0
  %43 = load float, ptr %42, align 4
  %44 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  %clouds10 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan14" = icmp slt i32 %45, 5
  %"GlobalIndexExpr::isGreaterThan15" = icmp sge i32 %45, 0
  %"GlobalIndexExpr::isWithinBounds16" = and i1 %"GlobalIndexExpr::isLessThan14", %"GlobalIndexExpr::isGreaterThan15"
  br i1 %"GlobalIndexExpr::isWithinBounds16", label %"GlobalIndexExpr::then11", label %"GlobalIndexExpr::else12"

"GlobalIndexExpr::then11":                        ; preds = %"GlobalIndexExpr::merge9"
  br label %"GlobalIndexExpr::merge13"

"GlobalIndexExpr::else12":                        ; preds = %"GlobalIndexExpr::merge9"
  call void @raise_exception(ptr @6)
  br label %"GlobalIndexExpr::merge13"

"GlobalIndexExpr::merge13":                       ; preds = %"GlobalIndexExpr::else12", %"GlobalIndexExpr::then11"
  %46 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %45
  %47 = getelementptr inbounds %AttributeType.5, ptr %46, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then17", label %"GlobalIndexExpr::else18"

"GlobalIndexExpr::then17":                        ; preds = %"GlobalIndexExpr::merge13"
  br label %"GlobalIndexExpr::merge19"

"GlobalIndexExpr::else18":                        ; preds = %"GlobalIndexExpr::merge13"
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge19"

"GlobalIndexExpr::merge19":                       ; preds = %"GlobalIndexExpr::else18", %"GlobalIndexExpr::then17"
  %48 = getelementptr [2 x float], ptr %47, i32 0, i32 0
  %49 = load float, ptr %48, align 4
  %frameTime20 = load float, ptr %frameTime, align 4
  %50 = load float, ptr %frameTime, align 4
  %51 = fmul float %50, 1.000000e+01
  %52 = fadd float %49, %51
  store float %52, ptr %42, align 4
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock4, label %afterNestedBlock2

"GlobalIndexExpr::then22":                        ; preds = %nestedBlock5
  br label %"GlobalIndexExpr::merge24"

"GlobalIndexExpr::else23":                        ; preds = %nestedBlock5
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge24"

"GlobalIndexExpr::merge24":                       ; preds = %"GlobalIndexExpr::else23", %"GlobalIndexExpr::then22"
  %55 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %39
  %56 = getelementptr inbounds %AttributeType.5, ptr %55, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then28", label %"GlobalIndexExpr::else29"

"GlobalIndexExpr::then28":                        ; preds = %"GlobalIndexExpr::merge24"
  br label %"GlobalIndexExpr::merge30"

"GlobalIndexExpr::else29":                        ; preds = %"GlobalIndexExpr::merge24"
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge30"

"GlobalIndexExpr::merge30":                       ; preds = %"GlobalIndexExpr::else29", %"GlobalIndexExpr::then28"
  %57 = getelementptr [2 x float], ptr %56, i32 0, i32 0
  %58 = load float, ptr %57, align 4
  %59 = fcmp ogt float %58, 2.500000e+02
  br i1 %59, label %then, label %else

then:                                             ; preds = %"GlobalIndexExpr::merge30"
  br label %nestedBlock32

else:                                             ; preds = %"GlobalIndexExpr::merge30"
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock31
  %60 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %checkContinueBlock6, label %afterNestedBlock2

afterNestedBlock31:                               ; preds = %checkContinueBlock35, %"GlobalIndexExpr::merge56", %checkContinueBlock33, %"GlobalIndexExpr::merge45"
  br label %afterIfElse

nestedBlock32:                                    ; preds = %then
  %62 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %63 = load i32, ptr %62, align 4
  %clouds36 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan40" = icmp slt i32 %63, 5
  %"GlobalIndexExpr::isGreaterThan41" = icmp sge i32 %63, 0
  %"GlobalIndexExpr::isWithinBounds42" = and i1 %"GlobalIndexExpr::isLessThan40", %"GlobalIndexExpr::isGreaterThan41"
  br i1 %"GlobalIndexExpr::isWithinBounds42", label %"GlobalIndexExpr::then37", label %"GlobalIndexExpr::else38"

checkContinueBlock33:                             ; preds = %"GlobalIndexExpr::merge45"
  %64 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %nestedBlock34, label %afterNestedBlock31

nestedBlock34:                                    ; preds = %checkContinueBlock33
  %66 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %67 = load i32, ptr %66, align 4
  %clouds47 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan51" = icmp slt i32 %67, 5
  %"GlobalIndexExpr::isGreaterThan52" = icmp sge i32 %67, 0
  %"GlobalIndexExpr::isWithinBounds53" = and i1 %"GlobalIndexExpr::isLessThan51", %"GlobalIndexExpr::isGreaterThan52"
  br i1 %"GlobalIndexExpr::isWithinBounds53", label %"GlobalIndexExpr::then48", label %"GlobalIndexExpr::else49"

checkContinueBlock35:                             ; preds = %"GlobalIndexExpr::merge56"
  br label %afterNestedBlock31

"GlobalIndexExpr::then37":                        ; preds = %nestedBlock32
  br label %"GlobalIndexExpr::merge39"

"GlobalIndexExpr::else38":                        ; preds = %nestedBlock32
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge39"

"GlobalIndexExpr::merge39":                       ; preds = %"GlobalIndexExpr::else38", %"GlobalIndexExpr::then37"
  %68 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %63
  %69 = getelementptr inbounds %AttributeType.5, ptr %68, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then43", label %"GlobalIndexExpr::else44"

"GlobalIndexExpr::then43":                        ; preds = %"GlobalIndexExpr::merge39"
  br label %"GlobalIndexExpr::merge45"

"GlobalIndexExpr::else44":                        ; preds = %"GlobalIndexExpr::merge39"
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge45"

"GlobalIndexExpr::merge45":                       ; preds = %"GlobalIndexExpr::else44", %"GlobalIndexExpr::then43"
  %70 = getelementptr [2 x float], ptr %69, i32 0, i32 0
  %71 = load float, ptr %70, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %72 = load i32, ptr @screenWidth, align 4
  %73 = mul i32 -2, %72
  store i32 %73, ptr %15, align 4
  %screenWidth46 = load i32, ptr @screenWidth, align 4
  %74 = load i32, ptr @screenWidth, align 4
  %75 = mul i32 -1, %74
  store i32 %75, ptr %16, align 4
  call void @getRandomNumber(ptr %rtPtr, ptr %15, ptr %16)
  %76 = load i32, ptr %rtPtr, align 4
  %77 = sitofp i32 %76 to float
  store float %77, ptr %70, align 4
  %78 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %checkContinueBlock33, label %afterNestedBlock31

"GlobalIndexExpr::then48":                        ; preds = %nestedBlock34
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::else49":                        ; preds = %nestedBlock34
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::merge50":                       ; preds = %"GlobalIndexExpr::else49", %"GlobalIndexExpr::then48"
  %80 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %67
  %81 = getelementptr inbounds %AttributeType.5, ptr %80, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then54", label %"GlobalIndexExpr::else55"

"GlobalIndexExpr::then54":                        ; preds = %"GlobalIndexExpr::merge50"
  br label %"GlobalIndexExpr::merge56"

"GlobalIndexExpr::else55":                        ; preds = %"GlobalIndexExpr::merge50"
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge56"

"GlobalIndexExpr::merge56":                       ; preds = %"GlobalIndexExpr::else55", %"GlobalIndexExpr::then54"
  %82 = getelementptr [2 x float], ptr %81, i32 0, i32 1
  %83 = load float, ptr %82, align 4
  store i32 0, ptr %17, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %84 = load i32, ptr @screenHeight, align 4
  %85 = sitofp i32 %84 to double
  %86 = fdiv double %85, 3.000000e+00
  %87 = fptosi double %86 to i32
  store i32 %87, ptr %18, align 4
  call void @getRandomNumber(ptr %rtPtr1, ptr %17, ptr %18)
  %88 = load i32, ptr %rtPtr1, align 4
  %89 = sitofp i32 %88 to float
  %90 = fmul float -1.000000e+00, %89
  store float %90, ptr %82, align 4
  %91 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %checkContinueBlock35, label %afterNestedBlock31

decrement_block57:                                ; preds = %"ForLoop::afterLoop"
  %93 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %94 = sub i32 %93, 1
  store i32 %94, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block58

end_block58:                                      ; preds = %decrement_block57, %"ForLoop::afterLoop"
  %95 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %96 = icmp eq i32 %95, 0
  br i1 %96, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.draw(ptr %0, ptr %1) !rt !41 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Cloud, ptr %2, i32 0, i32 3
  %i = alloca %DynamicType, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block26
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %6, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock:                               ; preds = %end_block26
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock1, %nestedBlock
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock2

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %end_block26, label %decrement_block25

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %13 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %14 = sub i32 %13, 1
  store i32 %14, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %15 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %17 = icmp sge i32 %16, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %18 = icmp sle i32 %16, 4
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %19 = phi i1 [ %17, %"ForLoop::Conditon::trueBlock" ], [ %18, %"ForLoop::Conditon::falseBlock" ]
  br i1 %19, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock1:                                ; preds = %checkContinueBlock3, %"GlobalIndexExpr::merge21"
  %20 = add i32 %16, 1
  store i32 %20, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock2:                                     ; preds = %"ForLoop::loopBody"
  %21 = load ptr, ptr %0, align 8
  %22 = getelementptr inbounds %FlowWingAnim, ptr %21, i32 0, i32 0
  %23 = load ptr, ptr %22, align 8
  %24 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %23, i32 0, i32 20
  %25 = load ptr, ptr %24, align 8
  %26 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  %clouds = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %27, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %27, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock3:                              ; preds = %"GlobalIndexExpr::merge21"
  br label %afterNestedBlock1

"GlobalIndexExpr::then":                          ; preds = %nestedBlock2
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock2
  call void @raise_exception(ptr @14)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %28 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %27
  %29 = getelementptr inbounds %AttributeType.5, ptr %28, i32 0, i32 0
  %30 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %31 = load i32, ptr %30, align 4
  %clouds4 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan8" = icmp slt i32 %31, 5
  %"GlobalIndexExpr::isGreaterThan9" = icmp sge i32 %31, 0
  %"GlobalIndexExpr::isWithinBounds10" = and i1 %"GlobalIndexExpr::isLessThan8", %"GlobalIndexExpr::isGreaterThan9"
  br i1 %"GlobalIndexExpr::isWithinBounds10", label %"GlobalIndexExpr::then5", label %"GlobalIndexExpr::else6"

"GlobalIndexExpr::then5":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge7"

"GlobalIndexExpr::else6":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge7"

"GlobalIndexExpr::merge7":                        ; preds = %"GlobalIndexExpr::else6", %"GlobalIndexExpr::then5"
  %32 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %31
  %33 = getelementptr inbounds %AttributeType.5, ptr %32, i32 0, i32 1
  %34 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %35 = load i32, ptr %34, align 4
  %clouds11 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan15" = icmp slt i32 %35, 5
  %"GlobalIndexExpr::isGreaterThan16" = icmp sge i32 %35, 0
  %"GlobalIndexExpr::isWithinBounds17" = and i1 %"GlobalIndexExpr::isLessThan15", %"GlobalIndexExpr::isGreaterThan16"
  br i1 %"GlobalIndexExpr::isWithinBounds17", label %"GlobalIndexExpr::then12", label %"GlobalIndexExpr::else13"

"GlobalIndexExpr::then12":                        ; preds = %"GlobalIndexExpr::merge7"
  br label %"GlobalIndexExpr::merge14"

"GlobalIndexExpr::else13":                        ; preds = %"GlobalIndexExpr::merge7"
  call void @raise_exception(ptr @16)
  br label %"GlobalIndexExpr::merge14"

"GlobalIndexExpr::merge14":                       ; preds = %"GlobalIndexExpr::else13", %"GlobalIndexExpr::then12"
  %36 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %35
  %37 = getelementptr inbounds %AttributeType.5, ptr %36, i32 0, i32 2
  %38 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %39 = load i32, ptr %38, align 4
  %clouds18 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan22" = icmp slt i32 %39, 5
  %"GlobalIndexExpr::isGreaterThan23" = icmp sge i32 %39, 0
  %"GlobalIndexExpr::isWithinBounds24" = and i1 %"GlobalIndexExpr::isLessThan22", %"GlobalIndexExpr::isGreaterThan23"
  br i1 %"GlobalIndexExpr::isWithinBounds24", label %"GlobalIndexExpr::then19", label %"GlobalIndexExpr::else20"

"GlobalIndexExpr::then19":                        ; preds = %"GlobalIndexExpr::merge14"
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::else20":                        ; preds = %"GlobalIndexExpr::merge14"
  call void @raise_exception(ptr @17)
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::merge21":                       ; preds = %"GlobalIndexExpr::else20", %"GlobalIndexExpr::then19"
  %40 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %39
  %41 = getelementptr inbounds %AttributeType.5, ptr %40, i32 0, i32 3
  %rotation = load float, ptr %41, align 4
  %42 = load ptr, ptr %0, align 8
  %43 = getelementptr inbounds %FlowWingAnim, ptr %42, i32 0, i32 5
  %44 = getelementptr inbounds %COLORS_TYPE.3, ptr %43, i32 0, i32 0
  %WHITE = load i32, ptr %44, align 4
  call void %25(ptr %4, ptr %29, ptr %33, ptr %37, ptr %41, ptr %44, ptr %0)
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock3, label %afterNestedBlock1

decrement_block25:                                ; preds = %"ForLoop::afterLoop"
  %47 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %48 = sub i32 %47, 1
  store i32 %48, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block26

end_block26:                                      ; preds = %decrement_block25, %"ForLoop::afterLoop"
  %49 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %checkContinueBlock, label %afterNestedBlock
}

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-FlowWingAnim()

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-random()

declare !rt !42 void @getRandomNumber(ptr, ptr, ptr)

define void @main(ptr %0) !rt !43 {
entry:
  %fgAnim = alloca ptr, align 8
  %1 = alloca ptr, align 8
  %bird = alloca ptr, align 8
  %2 = alloca ptr, align 8
  %cloud = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca %Texture.0, align 8
  %5 = alloca ptr, align 8
  %6 = alloca %Texture.0, align 8
  %7 = alloca ptr, align 8
  %backgroundTexture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %backgroundTexture)
  %rtPtr = alloca %Texture.0, align 8
  %8 = alloca ptr, align 8
  %groundTexture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %groundTexture)
  %rtPtr1 = alloca %Texture.0, align 8
  %9 = alloca ptr, align 8
  %mountL1Texture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %mountL1Texture)
  %rtPtr2 = alloca %Texture.0, align 8
  %10 = alloca ptr, align 8
  %mountL2Texture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %mountL2Texture)
  %rtPtr3 = alloca %Texture.0, align 8
  %11 = alloca ptr, align 8
  %mount2L2Texture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %mount2L2Texture)
  %rtPtr4 = alloca %Texture.0, align 8
  %12 = alloca ptr, align 8
  %mount1L3Texture = alloca %Texture.0, align 8
  call void @"assign_<ObjectTexture.0>"(ptr %mount1L3Texture)
  %rtPtr5 = alloca %Texture.0, align 8
  %13 = alloca ptr, align 8
  %mountL1Pos1 = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %mountL1Pos1)
  %mountL1Pos2 = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %mountL1Pos2)
  %mountL2Pos1 = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %mountL2Pos1)
  %mount2L2Pos1 = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %mount2L2Pos1)
  %rtPtr6 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %mount1L3Pos1 = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %mount1L3Pos1)
  %rtPtr7 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %rtPtr8 = alloca i1, align 1
  %18 = alloca ptr, align 8
  %19 = alloca %Texture.0, align 8
  %20 = alloca ptr, align 8
  %21 = alloca %Texture.0, align 8
  %22 = alloca ptr, align 8
  %23 = alloca %Texture.0, align 8
  %rtPtr9 = alloca i1, align 1
  %24 = alloca float, align 4
  %rtPtr10 = alloca float, align 4
  %rtPtr11 = alloca float, align 4
  %rtPtr12 = alloca float, align 4
  %rtPtr13 = alloca float, align 4
  %rtPtr14 = alloca float, align 4
  %rtPtr15 = alloca i32, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i32, align 4
  %28 = alloca i32, align 4
  %29 = alloca i32, align 4
  %30 = alloca i32, align 4
  %rtPtr16 = alloca i1, align 1
  %rtPtr17 = alloca i1, align 1
  %31 = alloca float, align 4
  %32 = alloca float, align 4
  %33 = alloca float, align 4
  %34 = alloca float, align 4
  %35 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %35)
  %36 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %36)
  %37 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %37)
  %38 = alloca float, align 4
  %39 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %39)
  %40 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %40)
  %41 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %41)
  %42 = alloca float, align 4
  %43 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %43)
  %44 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %44)
  %45 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %45)
  %46 = alloca float, align 4
  %47 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %47)
  %48 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %48)
  %49 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %49)
  %50 = alloca float, align 4
  %51 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %51)
  %52 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %52)
  %53 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %53)
  %54 = alloca float, align 4
  %55 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %55)
  %56 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %56)
  %57 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %57)
  %58 = alloca float, align 4
  %59 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %59)
  %60 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %60)
  %61 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %61)
  %62 = alloca float, align 4
  %63 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %63)
  %64 = alloca [4 x float], align 4
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %64)
  %65 = alloca [2 x float], align 4
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %65)
  %66 = alloca float, align 4
  %67 = alloca %Texture.0, align 8
  %68 = alloca [4 x float], align 4
  %69 = alloca [4 x float], align 4
  %70 = alloca [2 x float], align 4
  %71 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock57, %mergeBlock258, %checkContinueBlock55, %nestedBlock54, %checkContinueBlock53, %end_block256, %checkContinueBlock51, %afterIfElse, %checkContinueBlock49, %nestedBlock48, %checkContinueBlock47, %nestedBlock46, %checkContinueBlock45, %nestedBlock44, %checkContinueBlock43, %nestedBlock42, %checkContinueBlock41, %nestedBlock40, %checkContinueBlock39, %nestedBlock38, %checkContinueBlock37, %nestedBlock36, %checkContinueBlock35, %nestedBlock34, %checkContinueBlock33, %nestedBlock32, %checkContinueBlock31, %nestedBlock30, %checkContinueBlock29, %nestedBlock28, %checkContinueBlock27, %nestedBlock26, %checkContinueBlock25, %nestedBlock24, %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %72 = call ptr @malloc(i64 96)
  call void @"assign_<Class<FlowWingAnim>>"(ptr %72)
  %73 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %73, align 8
  %74 = load ptr, ptr %73, align 8
  %75 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 23
  store ptr @FlowWingAnim.setTargetFPS, ptr %75, align 8
  %76 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 22
  store ptr @FlowWingAnim.endDrawing, ptr %76, align 8
  %77 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 21
  store ptr @FlowWingAnim.createWindow, ptr %77, align 8
  %78 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %78, align 8
  %79 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 20
  store ptr @FlowWingAnim.drawTexturePro, ptr %79, align 8
  %80 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 16
  store ptr @FlowWingAnim.drawRectangle, ptr %80, align 8
  %81 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 15
  store ptr @FlowWingAnim.beginDrawing, ptr %81, align 8
  %82 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 1
  store ptr @FlowWingAnim.traceLog, ptr %82, align 8
  %83 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 14
  store ptr @FlowWingAnim.unloadTexture, ptr %83, align 8
  %84 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 13
  store ptr @FlowWingAnim.closeWindow, ptr %84, align 8
  %85 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 17
  store ptr @FlowWingAnim.getColor, ptr %85, align 8
  %86 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 12
  store ptr @FlowWingAnim.textFormat, ptr %86, align 8
  %87 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 18
  store ptr @FlowWingAnim.windowShouldClose, ptr %87, align 8
  %88 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenWidth, ptr %88, align 8
  %89 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenHeight, ptr %89, align 8
  %90 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 11
  store ptr @FlowWingAnim.getTime, ptr %90, align 8
  %91 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 19
  store ptr @FlowWingAnim.beforeInit, ptr %91, align 8
  %92 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 10
  store ptr @FlowWingAnim.clearBackground, ptr %92, align 8
  %93 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 7
  store ptr @FlowWingAnim.drawTexture, ptr %93, align 8
  %94 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 8
  store ptr @FlowWingAnim.getFrameTime, ptr %94, align 8
  %95 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 2
  store ptr @FlowWingAnim.drawText, ptr %95, align 8
  %96 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %96, align 8
  %97 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 9
  store ptr @FlowWingAnim.loadTexture, ptr %97, align 8
  %98 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %74, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %98, align 8
  %99 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 1
  store i32 0, ptr %99, align 4
  %100 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 2
  store i32 0, ptr %100, align 4
  %101 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 3
  store ptr @20, ptr %101, align 8
  %102 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 4
  store i32 0, ptr %102, align 4
  %103 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 5
  call void @"assign_<ObjectCOLORS_TYPE.3>"(ptr %103)
  %104 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 6
  call void @"assign_<ObjectKEYS_TYPE.2>"(ptr %104)
  %105 = getelementptr inbounds %FlowWingAnim, ptr %72, i32 0, i32 7
  call void @"assign_<ObjectLOG_TYPE.1>"(ptr %105)
  store ptr %72, ptr %fgAnim, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  store ptr @21, ptr %1, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %1, ptr @FPS, ptr %fgAnim)
  %106 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %108 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock
  %110 = load ptr, ptr %fgAnim, align 8
  %111 = getelementptr inbounds %FlowWingAnim, ptr %110, i32 0, i32 0
  %112 = load ptr, ptr %111, align 8
  %113 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %112, i32 0, i32 21
  %114 = load ptr, ptr %113, align 8
  call void %114(ptr %fgAnim)
  %115 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %116 = icmp eq i32 %115, 0
  br i1 %116, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  %117 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %118 = icmp eq i32 %117, 0
  br i1 %118, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %119 = call ptr @malloc(i64 152)
  call void @"assign_<Class<Bird>>"(ptr %119)
  %120 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %120, align 8
  %121 = load ptr, ptr %120, align 8
  %122 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 8
  store ptr @Bird.updateY, ptr %122, align 8
  %123 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 7
  store ptr @Bird.getTexturePath, ptr %123, align 8
  %124 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 5
  store ptr @Bird.isTextureLoaded, ptr %124, align 8
  %125 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 9
  store ptr @Bird.setTexture, ptr %125, align 8
  %126 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 2
  store ptr @Bird.getOrigin, ptr %126, align 8
  %127 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 4
  store ptr @Bird.getSource, ptr %127, align 8
  %128 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 6
  store ptr @Bird.update, ptr %128, align 8
  %129 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 0
  store ptr @Bird.getTexture, ptr %129, align 8
  %130 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 3
  store ptr @Bird.getDistination, ptr %130, align 8
  %131 = getelementptr inbounds %"Bird::VTableType", ptr %121, i32 0, i32 1
  store ptr @Bird.getRotation, ptr %131, align 8
  %132 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 1
  store float 3.600000e+02, ptr %132, align 4
  %133 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 2
  store float 9.000000e+01, ptr %133, align 4
  %134 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 3
  %FPS58 = load i32, ptr @FPS, align 4
  %135 = load i32, ptr @FPS, align 4
  %136 = sitofp i32 %135 to double
  %137 = fdiv double 1.000000e+01, %136
  store double %137, ptr %134, align 8
  %138 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 4
  store double 0.000000e+00, ptr %138, align 8
  %139 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 5
  store i32 9, ptr %139, align 4
  %140 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 6
  store i32 0, ptr %140, align 4
  %141 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 7
  store ptr @24, ptr %141, align 8
  %142 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 8
  store i1 false, ptr %142, align 1
  %143 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 9
  call void @"assign_<ObjectTexture.0>"(ptr %143)
  %144 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 10
  call void @"assign_<Array[9]<ObjectPosition.4>>:9,"(ptr %144)
  %145 = getelementptr inbounds %Bird, ptr %119, i32 0, i32 11
  call void @"assign_<ObjectPosition.4>"(ptr %145)
  store ptr %119, ptr %bird, align 8
  store ptr @25, ptr %2, align 8
  call void @Bird.init1(ptr %2, ptr %bird)
  %146 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %147 = icmp eq i32 %146, 0
  br i1 %147, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %148 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %149 = icmp eq i32 %148, 0
  br i1 %149, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %150 = call ptr @malloc(i64 256)
  call void @"assign_<Class<Cloud>>"(ptr %150)
  %151 = getelementptr inbounds %Cloud, ptr %150, i32 0, i32 0
  store ptr @vtable.Cloud.fg, ptr %151, align 8
  %152 = load ptr, ptr %151, align 8
  %153 = getelementptr inbounds %"Cloud::VTableType", ptr %152, i32 0, i32 4
  store ptr @Cloud.update, ptr %153, align 8
  %154 = getelementptr inbounds %"Cloud::VTableType", ptr %152, i32 0, i32 3
  store ptr @Cloud.setTexture, ptr %154, align 8
  %155 = getelementptr inbounds %"Cloud::VTableType", ptr %152, i32 0, i32 2
  store ptr @Cloud.getTexturePath, ptr %155, align 8
  %156 = getelementptr inbounds %"Cloud::VTableType", ptr %152, i32 0, i32 1
  store ptr @Cloud.getTexture, ptr %156, align 8
  %157 = getelementptr inbounds %"Cloud::VTableType", ptr %152, i32 0, i32 0
  store ptr @Cloud.draw, ptr %157, align 8
  %158 = getelementptr inbounds %Cloud, ptr %150, i32 0, i32 1
  call void @"assign_<Array[5]<ObjectAttributeType.5>>:5,"(ptr %158)
  %159 = getelementptr inbounds %Cloud, ptr %150, i32 0, i32 2
  call void @"assign_<ObjectTexture.0>"(ptr %159)
  %160 = getelementptr inbounds %Cloud, ptr %150, i32 0, i32 3
  store ptr @28, ptr %160, align 8
  store ptr %150, ptr %cloud, align 8
  store ptr @29, ptr %3, align 8
  call void @Cloud.init1(ptr %3, ptr %cloud)
  %161 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %checkContinueBlock23, label %afterNestedBlock

checkContinueBlock23:                             ; preds = %nestedBlock22
  %163 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %164 = icmp eq i32 %163, 0
  br i1 %164, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  %165 = load ptr, ptr %bird, align 8
  %166 = getelementptr inbounds %Bird, ptr %165, i32 0, i32 0
  %167 = load ptr, ptr %166, align 8
  %168 = getelementptr inbounds %"Bird::VTableType", ptr %167, i32 0, i32 9
  %169 = load ptr, ptr %168, align 8
  %170 = load ptr, ptr %fgAnim, align 8
  %171 = getelementptr inbounds %FlowWingAnim, ptr %170, i32 0, i32 0
  %172 = load ptr, ptr %171, align 8
  %173 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %172, i32 0, i32 9
  %174 = load ptr, ptr %173, align 8
  %175 = load ptr, ptr %bird, align 8
  %176 = getelementptr inbounds %Bird, ptr %175, i32 0, i32 0
  %177 = load ptr, ptr %176, align 8
  %178 = getelementptr inbounds %"Bird::VTableType", ptr %177, i32 0, i32 7
  %179 = load ptr, ptr %178, align 8
  call void %179(ptr %5, ptr %bird)
  call void %174(ptr %4, ptr %5, ptr %fgAnim)
  call void %169(ptr %4, ptr %bird)
  %180 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %181 = icmp eq i32 %180, 0
  br i1 %181, label %checkContinueBlock25, label %afterNestedBlock

checkContinueBlock25:                             ; preds = %nestedBlock24
  %182 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %183 = icmp eq i32 %182, 0
  br i1 %183, label %nestedBlock26, label %afterNestedBlock

nestedBlock26:                                    ; preds = %checkContinueBlock25
  %184 = load ptr, ptr %cloud, align 8
  %185 = getelementptr inbounds %Cloud, ptr %184, i32 0, i32 0
  %186 = load ptr, ptr %185, align 8
  %187 = getelementptr inbounds %"Cloud::VTableType", ptr %186, i32 0, i32 3
  %188 = load ptr, ptr %187, align 8
  %189 = load ptr, ptr %fgAnim, align 8
  %190 = getelementptr inbounds %FlowWingAnim, ptr %189, i32 0, i32 0
  %191 = load ptr, ptr %190, align 8
  %192 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %191, i32 0, i32 9
  %193 = load ptr, ptr %192, align 8
  %194 = load ptr, ptr %cloud, align 8
  %195 = getelementptr inbounds %Cloud, ptr %194, i32 0, i32 0
  %196 = load ptr, ptr %195, align 8
  %197 = getelementptr inbounds %"Cloud::VTableType", ptr %196, i32 0, i32 2
  %198 = load ptr, ptr %197, align 8
  call void %198(ptr %7, ptr %cloud)
  call void %193(ptr %6, ptr %7, ptr %fgAnim)
  call void %188(ptr %6, ptr %cloud)
  %199 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %200 = icmp eq i32 %199, 0
  br i1 %200, label %checkContinueBlock27, label %afterNestedBlock

checkContinueBlock27:                             ; preds = %nestedBlock26
  %201 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %202 = icmp eq i32 %201, 0
  br i1 %202, label %nestedBlock28, label %afterNestedBlock

nestedBlock28:                                    ; preds = %checkContinueBlock27
  %203 = load ptr, ptr %fgAnim, align 8
  %204 = getelementptr inbounds %FlowWingAnim, ptr %203, i32 0, i32 0
  %205 = load ptr, ptr %204, align 8
  %206 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %205, i32 0, i32 9
  %207 = load ptr, ptr %206, align 8
  store ptr @30, ptr %8, align 8
  call void %207(ptr %rtPtr, ptr %8, ptr %fgAnim)
  %208 = load %Texture.0, ptr %rtPtr, align 4
  store %Texture.0 %208, ptr %backgroundTexture, align 4
  %209 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %210 = icmp eq i32 %209, 0
  br i1 %210, label %checkContinueBlock29, label %afterNestedBlock

checkContinueBlock29:                             ; preds = %nestedBlock28
  %211 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %212 = icmp eq i32 %211, 0
  br i1 %212, label %nestedBlock30, label %afterNestedBlock

nestedBlock30:                                    ; preds = %checkContinueBlock29
  %213 = load ptr, ptr %fgAnim, align 8
  %214 = getelementptr inbounds %FlowWingAnim, ptr %213, i32 0, i32 0
  %215 = load ptr, ptr %214, align 8
  %216 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %215, i32 0, i32 9
  %217 = load ptr, ptr %216, align 8
  store ptr @31, ptr %9, align 8
  call void %217(ptr %rtPtr1, ptr %9, ptr %fgAnim)
  %218 = load %Texture.0, ptr %rtPtr1, align 4
  store %Texture.0 %218, ptr %groundTexture, align 4
  %219 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %220 = icmp eq i32 %219, 0
  br i1 %220, label %checkContinueBlock31, label %afterNestedBlock

checkContinueBlock31:                             ; preds = %nestedBlock30
  %221 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %222 = icmp eq i32 %221, 0
  br i1 %222, label %nestedBlock32, label %afterNestedBlock

nestedBlock32:                                    ; preds = %checkContinueBlock31
  %223 = load ptr, ptr %fgAnim, align 8
  %224 = getelementptr inbounds %FlowWingAnim, ptr %223, i32 0, i32 0
  %225 = load ptr, ptr %224, align 8
  %226 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %225, i32 0, i32 9
  %227 = load ptr, ptr %226, align 8
  store ptr @32, ptr %10, align 8
  call void %227(ptr %rtPtr2, ptr %10, ptr %fgAnim)
  %228 = load %Texture.0, ptr %rtPtr2, align 4
  store %Texture.0 %228, ptr %mountL1Texture, align 4
  %229 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %230 = icmp eq i32 %229, 0
  br i1 %230, label %checkContinueBlock33, label %afterNestedBlock

checkContinueBlock33:                             ; preds = %nestedBlock32
  %231 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %232 = icmp eq i32 %231, 0
  br i1 %232, label %nestedBlock34, label %afterNestedBlock

nestedBlock34:                                    ; preds = %checkContinueBlock33
  %233 = load ptr, ptr %fgAnim, align 8
  %234 = getelementptr inbounds %FlowWingAnim, ptr %233, i32 0, i32 0
  %235 = load ptr, ptr %234, align 8
  %236 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %235, i32 0, i32 9
  %237 = load ptr, ptr %236, align 8
  store ptr @33, ptr %11, align 8
  call void %237(ptr %rtPtr3, ptr %11, ptr %fgAnim)
  %238 = load %Texture.0, ptr %rtPtr3, align 4
  store %Texture.0 %238, ptr %mountL2Texture, align 4
  %239 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %240 = icmp eq i32 %239, 0
  br i1 %240, label %checkContinueBlock35, label %afterNestedBlock

checkContinueBlock35:                             ; preds = %nestedBlock34
  %241 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %242 = icmp eq i32 %241, 0
  br i1 %242, label %nestedBlock36, label %afterNestedBlock

nestedBlock36:                                    ; preds = %checkContinueBlock35
  %243 = load ptr, ptr %fgAnim, align 8
  %244 = getelementptr inbounds %FlowWingAnim, ptr %243, i32 0, i32 0
  %245 = load ptr, ptr %244, align 8
  %246 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %245, i32 0, i32 9
  %247 = load ptr, ptr %246, align 8
  store ptr @34, ptr %12, align 8
  call void %247(ptr %rtPtr4, ptr %12, ptr %fgAnim)
  %248 = load %Texture.0, ptr %rtPtr4, align 4
  store %Texture.0 %248, ptr %mount2L2Texture, align 4
  %249 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %250 = icmp eq i32 %249, 0
  br i1 %250, label %checkContinueBlock37, label %afterNestedBlock

checkContinueBlock37:                             ; preds = %nestedBlock36
  %251 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %252 = icmp eq i32 %251, 0
  br i1 %252, label %nestedBlock38, label %afterNestedBlock

nestedBlock38:                                    ; preds = %checkContinueBlock37
  %253 = load ptr, ptr %fgAnim, align 8
  %254 = getelementptr inbounds %FlowWingAnim, ptr %253, i32 0, i32 0
  %255 = load ptr, ptr %254, align 8
  %256 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %255, i32 0, i32 9
  %257 = load ptr, ptr %256, align 8
  store ptr @35, ptr %13, align 8
  call void %257(ptr %rtPtr5, ptr %13, ptr %fgAnim)
  %258 = load %Texture.0, ptr %rtPtr5, align 4
  store %Texture.0 %258, ptr %mount1L3Texture, align 4
  %259 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %260 = icmp eq i32 %259, 0
  br i1 %260, label %checkContinueBlock39, label %afterNestedBlock

checkContinueBlock39:                             ; preds = %nestedBlock38
  %261 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %262 = icmp eq i32 %261, 0
  br i1 %262, label %nestedBlock40, label %afterNestedBlock

nestedBlock40:                                    ; preds = %checkContinueBlock39
  %263 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %263, align 4
  %264 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %264, align 4
  %265 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %266 = icmp eq i32 %265, 0
  br i1 %266, label %checkContinueBlock41, label %afterNestedBlock

checkContinueBlock41:                             ; preds = %nestedBlock40
  %267 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %268 = icmp eq i32 %267, 0
  br i1 %268, label %nestedBlock42, label %afterNestedBlock

nestedBlock42:                                    ; preds = %checkContinueBlock41
  %269 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  store float -1.542000e+03, ptr %269, align 4
  %270 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %270, align 4
  %271 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %272 = icmp eq i32 %271, 0
  br i1 %272, label %checkContinueBlock43, label %afterNestedBlock

checkContinueBlock43:                             ; preds = %nestedBlock42
  %273 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %274 = icmp eq i32 %273, 0
  br i1 %274, label %nestedBlock44, label %afterNestedBlock

nestedBlock44:                                    ; preds = %checkContinueBlock43
  %275 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %screenWidth59 = load i32, ptr @screenWidth, align 4
  %276 = load i32, ptr @screenWidth, align 4
  %277 = mul i32 -1, %276
  %278 = sitofp i32 %277 to float
  store float %278, ptr %275, align 4
  %279 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %279, align 4
  %280 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %281 = icmp eq i32 %280, 0
  br i1 %281, label %checkContinueBlock45, label %afterNestedBlock

checkContinueBlock45:                             ; preds = %nestedBlock44
  %282 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %283 = icmp eq i32 %282, 0
  br i1 %283, label %nestedBlock46, label %afterNestedBlock

nestedBlock46:                                    ; preds = %checkContinueBlock45
  %284 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %screenWidth60 = load i32, ptr @screenWidth, align 4
  %285 = load i32, ptr @screenWidth, align 4
  %286 = mul i32 -1, %285
  %screenWidth61 = load i32, ptr @screenWidth, align 4
  %287 = load i32, ptr @screenWidth, align 4
  %288 = sitofp i32 %287 to double
  %289 = fdiv double %288, 4.000000e+00
  %290 = fptosi double %289 to i32
  store i32 %290, ptr %14, align 4
  %screenWidth62 = load i32, ptr @screenWidth, align 4
  %291 = load i32, ptr @screenWidth, align 4
  %292 = sitofp i32 %291 to double
  %293 = fdiv double %292, 2.000000e+00
  %294 = fptosi double %293 to i32
  store i32 %294, ptr %15, align 4
  call void @getRandomNumber(ptr %rtPtr6, ptr %14, ptr %15)
  %295 = load i32, ptr %rtPtr6, align 4
  %296 = sub i32 %286, %295
  %297 = sitofp i32 %296 to float
  store float %297, ptr %284, align 4
  %298 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %298, align 4
  %299 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %300 = icmp eq i32 %299, 0
  br i1 %300, label %checkContinueBlock47, label %afterNestedBlock

checkContinueBlock47:                             ; preds = %nestedBlock46
  %301 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %302 = icmp eq i32 %301, 0
  br i1 %302, label %nestedBlock48, label %afterNestedBlock

nestedBlock48:                                    ; preds = %checkContinueBlock47
  %303 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %screenWidth63 = load i32, ptr @screenWidth, align 4
  %304 = load i32, ptr @screenWidth, align 4
  %305 = mul i32 -1, %304
  %screenWidth64 = load i32, ptr @screenWidth, align 4
  %306 = load i32, ptr @screenWidth, align 4
  %307 = sitofp i32 %306 to double
  %308 = fdiv double %307, 4.000000e+00
  %309 = fptosi double %308 to i32
  store i32 %309, ptr %16, align 4
  %screenWidth65 = load i32, ptr @screenWidth, align 4
  %310 = load i32, ptr @screenWidth, align 4
  store i32 %310, ptr %17, align 4
  call void @getRandomNumber(ptr %rtPtr7, ptr %16, ptr %17)
  %311 = load i32, ptr %rtPtr7, align 4
  %312 = sub i32 %305, %311
  %313 = sitofp i32 %312 to float
  store float %313, ptr %303, align 4
  %314 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %314, align 4
  %315 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %316 = icmp eq i32 %315, 0
  br i1 %316, label %checkContinueBlock49, label %afterNestedBlock

checkContinueBlock49:                             ; preds = %nestedBlock48
  %317 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %318 = icmp eq i32 %317, 0
  br i1 %318, label %nestedBlock50, label %afterNestedBlock

nestedBlock50:                                    ; preds = %checkContinueBlock49
  %319 = load ptr, ptr %bird, align 8
  %320 = getelementptr inbounds %Bird, ptr %319, i32 0, i32 0
  %321 = load ptr, ptr %320, align 8
  %322 = getelementptr inbounds %"Bird::VTableType", ptr %321, i32 0, i32 5
  %323 = load ptr, ptr %322, align 8
  call void %323(ptr %rtPtr8, ptr %bird)
  %324 = load i1, ptr %rtPtr8, align 1
  %325 = xor i1 %324, true
  %326 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  %id = load i32, ptr %326, align 4
  %327 = load i32, ptr %326, align 4
  %328 = icmp eq i32 %327, 0
  %329 = select i1 %325, i1 true, i1 %328
  br i1 %329, label %then, label %else

checkContinueBlock51:                             ; preds = %afterIfElse
  %330 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %331 = icmp eq i32 %330, 0
  br i1 %331, label %nestedBlock52, label %afterNestedBlock

nestedBlock52:                                    ; preds = %checkContinueBlock51
  br label %"while:conditon"

checkContinueBlock53:                             ; preds = %end_block256
  %332 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %333 = icmp eq i32 %332, 0
  br i1 %333, label %nestedBlock54, label %afterNestedBlock

nestedBlock54:                                    ; preds = %checkContinueBlock53
  %334 = load ptr, ptr %fgAnim, align 8
  %335 = getelementptr inbounds %FlowWingAnim, ptr %334, i32 0, i32 0
  %336 = load ptr, ptr %335, align 8
  %337 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %336, i32 0, i32 13
  %338 = load ptr, ptr %337, align 8
  call void %338(ptr %fgAnim)
  %339 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %340 = icmp eq i32 %339, 0
  br i1 %340, label %checkContinueBlock55, label %afterNestedBlock

checkContinueBlock55:                             ; preds = %nestedBlock54
  %341 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %342 = icmp eq i32 %341, 0
  br i1 %342, label %nestedBlock56, label %afterNestedBlock

nestedBlock56:                                    ; preds = %checkContinueBlock55
  br label %returnBlock257

checkContinueBlock57:                             ; preds = %mergeBlock258
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock50
  br label %nestedBlock67

else:                                             ; preds = %nestedBlock50
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock66
  %343 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %344 = icmp eq i32 %343, 0
  br i1 %344, label %checkContinueBlock51, label %afterNestedBlock

afterNestedBlock66:                               ; preds = %checkContinueBlock74, %mergeBlock, %checkContinueBlock72, %nestedBlock71, %checkContinueBlock70, %nestedBlock69, %checkContinueBlock68, %nestedBlock67
  br label %afterIfElse

nestedBlock67:                                    ; preds = %then
  %345 = load ptr, ptr %fgAnim, align 8
  %346 = getelementptr inbounds %FlowWingAnim, ptr %345, i32 0, i32 0
  %347 = load ptr, ptr %346, align 8
  %348 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %347, i32 0, i32 1
  %349 = load ptr, ptr %348, align 8
  %350 = load ptr, ptr %fgAnim, align 8
  %351 = getelementptr inbounds %FlowWingAnim, ptr %350, i32 0, i32 7
  %352 = getelementptr inbounds %LOG_TYPE.1, ptr %351, i32 0, i32 5
  %ERROR = load i32, ptr %352, align 4
  store ptr @36, ptr %22, align 8
  call void %349(ptr %352, ptr %22, ptr %fgAnim)
  %353 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %354 = icmp eq i32 %353, 0
  br i1 %354, label %checkContinueBlock68, label %afterNestedBlock66

checkContinueBlock68:                             ; preds = %nestedBlock67
  %355 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %356 = icmp eq i32 %355, 0
  br i1 %356, label %nestedBlock69, label %afterNestedBlock66

nestedBlock69:                                    ; preds = %checkContinueBlock68
  %357 = load ptr, ptr %fgAnim, align 8
  %358 = getelementptr inbounds %FlowWingAnim, ptr %357, i32 0, i32 0
  %359 = load ptr, ptr %358, align 8
  %360 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %359, i32 0, i32 14
  %361 = load ptr, ptr %360, align 8
  %362 = load ptr, ptr %bird, align 8
  %363 = getelementptr inbounds %Bird, ptr %362, i32 0, i32 0
  %364 = load ptr, ptr %363, align 8
  %365 = getelementptr inbounds %"Bird::VTableType", ptr %364, i32 0, i32 0
  %366 = load ptr, ptr %365, align 8
  call void %366(ptr %23, ptr %bird)
  call void %361(ptr %23, ptr %fgAnim)
  %367 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %368 = icmp eq i32 %367, 0
  br i1 %368, label %checkContinueBlock70, label %afterNestedBlock66

checkContinueBlock70:                             ; preds = %nestedBlock69
  %369 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %370 = icmp eq i32 %369, 0
  br i1 %370, label %nestedBlock71, label %afterNestedBlock66

nestedBlock71:                                    ; preds = %checkContinueBlock70
  %371 = load ptr, ptr %fgAnim, align 8
  %372 = getelementptr inbounds %FlowWingAnim, ptr %371, i32 0, i32 0
  %373 = load ptr, ptr %372, align 8
  %374 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %373, i32 0, i32 13
  %375 = load ptr, ptr %374, align 8
  call void %375(ptr %fgAnim)
  %376 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %377 = icmp eq i32 %376, 0
  br i1 %377, label %checkContinueBlock72, label %afterNestedBlock66

checkContinueBlock72:                             ; preds = %nestedBlock71
  %378 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %379 = icmp eq i32 %378, 0
  br i1 %379, label %nestedBlock73, label %afterNestedBlock66

nestedBlock73:                                    ; preds = %checkContinueBlock72
  br label %returnBlock

checkContinueBlock74:                             ; preds = %mergeBlock
  br label %afterNestedBlock66

returnBlock:                                      ; preds = %nestedBlock73
  store i32 1, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %380 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %381 = icmp eq i32 %380, 0
  br i1 %381, label %checkContinueBlock74, label %afterNestedBlock66

"while:conditon":                                 ; preds = %afterNestedBlock75, %nestedBlock52
  %382 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %383 = icmp eq i32 %382, 0
  br i1 %383, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock76

while.end:                                        ; preds = %afterNestedBlock75, %end_block
  %384 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %385 = icmp eq i32 %384, 0
  br i1 %385, label %end_block256, label %decrement_block255

decrement_block:                                  ; preds = %"while:conditon"
  %386 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %387 = sub i32 %386, 1
  store i32 %387, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %388 = load ptr, ptr %fgAnim, align 8
  %389 = getelementptr inbounds %FlowWingAnim, ptr %388, i32 0, i32 0
  %390 = load ptr, ptr %389, align 8
  %391 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %390, i32 0, i32 18
  %392 = load ptr, ptr %391, align 8
  call void %392(ptr %rtPtr9, ptr %fgAnim)
  %393 = load i1, ptr %rtPtr9, align 1
  %394 = xor i1 %393, true
  br i1 %394, label %"while:body", label %while.end

afterNestedBlock75:                               ; preds = %checkContinueBlock115, %nestedBlock114, %checkContinueBlock113, %nestedBlock112, %checkContinueBlock111, %nestedBlock110, %checkContinueBlock109, %nestedBlock108, %checkContinueBlock107, %nestedBlock106, %checkContinueBlock105, %nestedBlock104, %checkContinueBlock103, %nestedBlock102, %checkContinueBlock101, %nestedBlock100, %checkContinueBlock99, %nestedBlock98, %checkContinueBlock97, %nestedBlock96, %checkContinueBlock95, %nestedBlock94, %checkContinueBlock93, %nestedBlock92, %checkContinueBlock91, %nestedBlock90, %checkContinueBlock89, %nestedBlock88, %checkContinueBlock87, %afterIfElse203, %checkContinueBlock85, %afterNestedBlock180, %checkContinueBlock83, %afterNestedBlock162, %checkContinueBlock81, %afterNestedBlock144, %checkContinueBlock79, %afterNestedBlock116, %checkContinueBlock77, %nestedBlock76
  %395 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %396 = icmp eq i32 %395, 0
  br i1 %396, label %"while:conditon", label %while.end

nestedBlock76:                                    ; preds = %"while:body"
  %397 = load ptr, ptr %bird, align 8
  %398 = getelementptr inbounds %Bird, ptr %397, i32 0, i32 0
  %399 = load ptr, ptr %398, align 8
  %400 = getelementptr inbounds %"Bird::VTableType", ptr %399, i32 0, i32 6
  %401 = load ptr, ptr %400, align 8
  %402 = load ptr, ptr %fgAnim, align 8
  %403 = getelementptr inbounds %FlowWingAnim, ptr %402, i32 0, i32 0
  %404 = load ptr, ptr %403, align 8
  %405 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %404, i32 0, i32 8
  %406 = load ptr, ptr %405, align 8
  call void %406(ptr %24, ptr %fgAnim)
  call void %401(ptr %24, ptr %bird)
  %407 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %408 = icmp eq i32 %407, 0
  br i1 %408, label %checkContinueBlock77, label %afterNestedBlock75

checkContinueBlock77:                             ; preds = %nestedBlock76
  %409 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %410 = icmp eq i32 %409, 0
  br i1 %410, label %nestedBlock78, label %afterNestedBlock75

nestedBlock78:                                    ; preds = %checkContinueBlock77
  br label %nestedBlock117

checkContinueBlock79:                             ; preds = %afterNestedBlock116
  %411 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %412 = icmp eq i32 %411, 0
  br i1 %412, label %nestedBlock80, label %afterNestedBlock75

nestedBlock80:                                    ; preds = %checkContinueBlock79
  br label %nestedBlock145

checkContinueBlock81:                             ; preds = %afterNestedBlock144
  %413 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %414 = icmp eq i32 %413, 0
  br i1 %414, label %nestedBlock82, label %afterNestedBlock75

nestedBlock82:                                    ; preds = %checkContinueBlock81
  br label %nestedBlock163

checkContinueBlock83:                             ; preds = %afterNestedBlock162
  %415 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %416 = icmp eq i32 %415, 0
  br i1 %416, label %nestedBlock84, label %afterNestedBlock75

nestedBlock84:                                    ; preds = %checkContinueBlock83
  br label %nestedBlock181

checkContinueBlock85:                             ; preds = %afterNestedBlock180
  %417 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %418 = icmp eq i32 %417, 0
  br i1 %418, label %nestedBlock86, label %afterNestedBlock75

nestedBlock86:                                    ; preds = %checkContinueBlock85
  %419 = load ptr, ptr %fgAnim, align 8
  %420 = getelementptr inbounds %FlowWingAnim, ptr %419, i32 0, i32 0
  %421 = load ptr, ptr %420, align 8
  %422 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %421, i32 0, i32 0
  %423 = load ptr, ptr %422, align 8
  %424 = load ptr, ptr %fgAnim, align 8
  %425 = getelementptr inbounds %FlowWingAnim, ptr %424, i32 0, i32 6
  %426 = getelementptr inbounds %KEYS_TYPE.2, ptr %425, i32 0, i32 3
  %KEY_UP = load i32, ptr %426, align 4
  call void %423(ptr %rtPtr16, ptr %426, ptr %fgAnim)
  %427 = load i1, ptr %rtPtr16, align 1
  %428 = load ptr, ptr %fgAnim, align 8
  %429 = getelementptr inbounds %FlowWingAnim, ptr %428, i32 0, i32 0
  %430 = load ptr, ptr %429, align 8
  %431 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %430, i32 0, i32 4
  %432 = load ptr, ptr %431, align 8
  %433 = load ptr, ptr %fgAnim, align 8
  %434 = getelementptr inbounds %FlowWingAnim, ptr %433, i32 0, i32 6
  %435 = getelementptr inbounds %KEYS_TYPE.2, ptr %434, i32 0, i32 3
  %KEY_UP200 = load i32, ptr %435, align 4
  call void %432(ptr %rtPtr17, ptr %435, ptr %fgAnim)
  %436 = load i1, ptr %rtPtr17, align 1
  %437 = select i1 %427, i1 true, i1 %436
  br i1 %437, label %then201, label %else202

checkContinueBlock87:                             ; preds = %afterIfElse203
  %438 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %439 = icmp eq i32 %438, 0
  br i1 %439, label %nestedBlock88, label %afterNestedBlock75

nestedBlock88:                                    ; preds = %checkContinueBlock87
  %440 = load ptr, ptr %cloud, align 8
  %441 = getelementptr inbounds %Cloud, ptr %440, i32 0, i32 0
  %442 = load ptr, ptr %441, align 8
  %443 = getelementptr inbounds %"Cloud::VTableType", ptr %442, i32 0, i32 4
  %444 = load ptr, ptr %443, align 8
  %445 = load ptr, ptr %fgAnim, align 8
  %446 = getelementptr inbounds %FlowWingAnim, ptr %445, i32 0, i32 0
  %447 = load ptr, ptr %446, align 8
  %448 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %447, i32 0, i32 8
  %449 = load ptr, ptr %448, align 8
  call void %449(ptr %34, ptr %fgAnim)
  call void %444(ptr %34, ptr %cloud)
  %450 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %451 = icmp eq i32 %450, 0
  br i1 %451, label %checkContinueBlock89, label %afterNestedBlock75

checkContinueBlock89:                             ; preds = %nestedBlock88
  %452 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %453 = icmp eq i32 %452, 0
  br i1 %453, label %nestedBlock90, label %afterNestedBlock75

nestedBlock90:                                    ; preds = %checkContinueBlock89
  %454 = load ptr, ptr %fgAnim, align 8
  %455 = getelementptr inbounds %FlowWingAnim, ptr %454, i32 0, i32 0
  %456 = load ptr, ptr %455, align 8
  %457 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %456, i32 0, i32 15
  %458 = load ptr, ptr %457, align 8
  call void %458(ptr %fgAnim)
  %459 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %460 = icmp eq i32 %459, 0
  br i1 %460, label %checkContinueBlock91, label %afterNestedBlock75

checkContinueBlock91:                             ; preds = %nestedBlock90
  %461 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %462 = icmp eq i32 %461, 0
  br i1 %462, label %nestedBlock92, label %afterNestedBlock75

nestedBlock92:                                    ; preds = %checkContinueBlock91
  %463 = load ptr, ptr %fgAnim, align 8
  %464 = getelementptr inbounds %FlowWingAnim, ptr %463, i32 0, i32 0
  %465 = load ptr, ptr %464, align 8
  %466 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %465, i32 0, i32 10
  %467 = load ptr, ptr %466, align 8
  %468 = load ptr, ptr %fgAnim, align 8
  %469 = getelementptr inbounds %FlowWingAnim, ptr %468, i32 0, i32 5
  %470 = getelementptr inbounds %COLORS_TYPE.3, ptr %469, i32 0, i32 1
  %RED = load i32, ptr %470, align 4
  call void %467(ptr %470, ptr %fgAnim)
  %471 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %472 = icmp eq i32 %471, 0
  br i1 %472, label %checkContinueBlock93, label %afterNestedBlock75

checkContinueBlock93:                             ; preds = %nestedBlock92
  %473 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %474 = icmp eq i32 %473, 0
  br i1 %474, label %nestedBlock94, label %afterNestedBlock75

nestedBlock94:                                    ; preds = %checkContinueBlock93
  %475 = load ptr, ptr %fgAnim, align 8
  %476 = getelementptr inbounds %FlowWingAnim, ptr %475, i32 0, i32 0
  %477 = load ptr, ptr %476, align 8
  %478 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %477, i32 0, i32 20
  %479 = load ptr, ptr %478, align 8
  %480 = getelementptr [4 x float], ptr %35, i32 0, i32 0
  store float 0.000000e+00, ptr %480, align 4
  %481 = getelementptr [4 x float], ptr %35, i32 0, i32 1
  store float 0.000000e+00, ptr %481, align 4
  %482 = getelementptr [4 x float], ptr %35, i32 0, i32 2
  store float 3.840000e+03, ptr %482, align 4
  %483 = getelementptr [4 x float], ptr %35, i32 0, i32 3
  store float 2.160000e+03, ptr %483, align 4
  %484 = getelementptr [4 x float], ptr %36, i32 0, i32 0
  store float 0.000000e+00, ptr %484, align 4
  %485 = getelementptr [4 x float], ptr %36, i32 0, i32 1
  store float 0.000000e+00, ptr %485, align 4
  %486 = getelementptr [4 x float], ptr %36, i32 0, i32 2
  %screenWidth207 = load i32, ptr @screenWidth, align 4
  %487 = load i32, ptr @screenWidth, align 4
  %488 = sitofp i32 %487 to float
  store float %488, ptr %486, align 4
  %489 = getelementptr [4 x float], ptr %36, i32 0, i32 3
  %screenHeight208 = load i32, ptr @screenHeight, align 4
  %490 = load i32, ptr @screenHeight, align 4
  %491 = sitofp i32 %490 to float
  store float %491, ptr %489, align 4
  %492 = getelementptr [2 x float], ptr %37, i32 0, i32 0
  store float 0.000000e+00, ptr %492, align 4
  %493 = getelementptr [2 x float], ptr %37, i32 0, i32 1
  store float 0.000000e+00, ptr %493, align 4
  store float 0.000000e+00, ptr %38, align 4
  %494 = load ptr, ptr %fgAnim, align 8
  %495 = getelementptr inbounds %FlowWingAnim, ptr %494, i32 0, i32 5
  %496 = getelementptr inbounds %COLORS_TYPE.3, ptr %495, i32 0, i32 0
  %WHITE = load i32, ptr %496, align 4
  call void %479(ptr %backgroundTexture, ptr %35, ptr %36, ptr %37, ptr %38, ptr %496, ptr %fgAnim)
  %497 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %498 = icmp eq i32 %497, 0
  br i1 %498, label %checkContinueBlock95, label %afterNestedBlock75

checkContinueBlock95:                             ; preds = %nestedBlock94
  %499 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %500 = icmp eq i32 %499, 0
  br i1 %500, label %nestedBlock96, label %afterNestedBlock75

nestedBlock96:                                    ; preds = %checkContinueBlock95
  %501 = load ptr, ptr %cloud, align 8
  %502 = getelementptr inbounds %Cloud, ptr %501, i32 0, i32 0
  %503 = load ptr, ptr %502, align 8
  %504 = getelementptr inbounds %"Cloud::VTableType", ptr %503, i32 0, i32 0
  %505 = load ptr, ptr %504, align 8
  call void %505(ptr %fgAnim, ptr %cloud)
  %506 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %507 = icmp eq i32 %506, 0
  br i1 %507, label %checkContinueBlock97, label %afterNestedBlock75

checkContinueBlock97:                             ; preds = %nestedBlock96
  %508 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %509 = icmp eq i32 %508, 0
  br i1 %509, label %nestedBlock98, label %afterNestedBlock75

nestedBlock98:                                    ; preds = %checkContinueBlock97
  %510 = load ptr, ptr %fgAnim, align 8
  %511 = getelementptr inbounds %FlowWingAnim, ptr %510, i32 0, i32 0
  %512 = load ptr, ptr %511, align 8
  %513 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %512, i32 0, i32 20
  %514 = load ptr, ptr %513, align 8
  %515 = getelementptr [4 x float], ptr %39, i32 0, i32 0
  store float 0.000000e+00, ptr %515, align 4
  %516 = getelementptr [4 x float], ptr %39, i32 0, i32 1
  store float 0.000000e+00, ptr %516, align 4
  %517 = getelementptr [4 x float], ptr %39, i32 0, i32 2
  store float 5.975000e+03, ptr %517, align 4
  %518 = getelementptr [4 x float], ptr %39, i32 0, i32 3
  store float 1.607000e+03, ptr %518, align 4
  %519 = getelementptr [4 x float], ptr %40, i32 0, i32 0
  store float 0.000000e+00, ptr %519, align 4
  %520 = getelementptr [4 x float], ptr %40, i32 0, i32 1
  %screenHeight209 = load i32, ptr @screenHeight, align 4
  %521 = load i32, ptr @screenHeight, align 4
  %522 = sitofp i32 %521 to double
  %523 = fdiv double %522, 3.000000e+00
  %524 = fptrunc double %523 to float
  store float %524, ptr %520, align 4
  %525 = getelementptr [4 x float], ptr %40, i32 0, i32 2
  %screenWidth210 = load i32, ptr @screenWidth, align 4
  %526 = load i32, ptr @screenWidth, align 4
  %527 = sitofp i32 %526 to double
  %528 = fdiv double %527, 2.000000e+00
  %529 = fptrunc double %528 to float
  store float %529, ptr %525, align 4
  %530 = getelementptr [4 x float], ptr %40, i32 0, i32 3
  %screenHeight211 = load i32, ptr @screenHeight, align 4
  %531 = load i32, ptr @screenHeight, align 4
  %532 = sitofp i32 %531 to double
  %533 = fdiv double %532, 3.000000e+00
  %534 = fptrunc double %533 to float
  store float %534, ptr %530, align 4
  %535 = getelementptr [2 x float], ptr %41, i32 0, i32 0
  %536 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x212 = load float, ptr %536, align 4
  %537 = load float, ptr %536, align 4
  store float %537, ptr %535, align 4
  %538 = getelementptr [2 x float], ptr %41, i32 0, i32 1
  %539 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  %y = load float, ptr %539, align 4
  %540 = load float, ptr %539, align 4
  store float %540, ptr %538, align 4
  store float 0.000000e+00, ptr %42, align 4
  %541 = load ptr, ptr %fgAnim, align 8
  %542 = getelementptr inbounds %FlowWingAnim, ptr %541, i32 0, i32 5
  %543 = getelementptr inbounds %COLORS_TYPE.3, ptr %542, i32 0, i32 0
  %WHITE213 = load i32, ptr %543, align 4
  call void %514(ptr %mountL2Texture, ptr %39, ptr %40, ptr %41, ptr %42, ptr %543, ptr %fgAnim)
  %544 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %545 = icmp eq i32 %544, 0
  br i1 %545, label %checkContinueBlock99, label %afterNestedBlock75

checkContinueBlock99:                             ; preds = %nestedBlock98
  %546 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %547 = icmp eq i32 %546, 0
  br i1 %547, label %nestedBlock100, label %afterNestedBlock75

nestedBlock100:                                   ; preds = %checkContinueBlock99
  %548 = load ptr, ptr %fgAnim, align 8
  %549 = getelementptr inbounds %FlowWingAnim, ptr %548, i32 0, i32 0
  %550 = load ptr, ptr %549, align 8
  %551 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %550, i32 0, i32 20
  %552 = load ptr, ptr %551, align 8
  %553 = getelementptr [4 x float], ptr %43, i32 0, i32 0
  store float 0.000000e+00, ptr %553, align 4
  %554 = getelementptr [4 x float], ptr %43, i32 0, i32 1
  store float 0.000000e+00, ptr %554, align 4
  %555 = getelementptr [4 x float], ptr %43, i32 0, i32 2
  store float 4.461000e+03, ptr %555, align 4
  %556 = getelementptr [4 x float], ptr %43, i32 0, i32 3
  store float 1.989000e+03, ptr %556, align 4
  %557 = getelementptr [4 x float], ptr %44, i32 0, i32 0
  store float 0.000000e+00, ptr %557, align 4
  %558 = getelementptr [4 x float], ptr %44, i32 0, i32 1
  %screenHeight214 = load i32, ptr @screenHeight, align 4
  %559 = load i32, ptr @screenHeight, align 4
  %560 = sitofp i32 %559 to double
  %561 = fdiv double %560, 3.000000e+00
  %562 = fptrunc double %561 to float
  store float %562, ptr %558, align 4
  %563 = getelementptr [4 x float], ptr %44, i32 0, i32 2
  %screenWidth215 = load i32, ptr @screenWidth, align 4
  %564 = load i32, ptr @screenWidth, align 4
  %565 = sitofp i32 %564 to double
  %566 = fdiv double %565, 2.000000e+00
  %567 = fptrunc double %566 to float
  store float %567, ptr %563, align 4
  %568 = getelementptr [4 x float], ptr %44, i32 0, i32 3
  %screenHeight216 = load i32, ptr @screenHeight, align 4
  %569 = load i32, ptr @screenHeight, align 4
  %570 = sitofp i32 %569 to double
  %571 = fdiv double %570, 3.000000e+00
  %572 = fptrunc double %571 to float
  store float %572, ptr %568, align 4
  %573 = getelementptr [2 x float], ptr %45, i32 0, i32 0
  %574 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x217 = load float, ptr %574, align 4
  %575 = load float, ptr %574, align 4
  store float %575, ptr %573, align 4
  %576 = getelementptr [2 x float], ptr %45, i32 0, i32 1
  %577 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  %y218 = load float, ptr %577, align 4
  %578 = load float, ptr %577, align 4
  store float %578, ptr %576, align 4
  store float 0.000000e+00, ptr %46, align 4
  %579 = load ptr, ptr %fgAnim, align 8
  %580 = getelementptr inbounds %FlowWingAnim, ptr %579, i32 0, i32 5
  %581 = getelementptr inbounds %COLORS_TYPE.3, ptr %580, i32 0, i32 0
  %WHITE219 = load i32, ptr %581, align 4
  call void %552(ptr %mount2L2Texture, ptr %43, ptr %44, ptr %45, ptr %46, ptr %581, ptr %fgAnim)
  %582 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %583 = icmp eq i32 %582, 0
  br i1 %583, label %checkContinueBlock101, label %afterNestedBlock75

checkContinueBlock101:                            ; preds = %nestedBlock100
  %584 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %585 = icmp eq i32 %584, 0
  br i1 %585, label %nestedBlock102, label %afterNestedBlock75

nestedBlock102:                                   ; preds = %checkContinueBlock101
  %586 = load ptr, ptr %fgAnim, align 8
  %587 = getelementptr inbounds %FlowWingAnim, ptr %586, i32 0, i32 0
  %588 = load ptr, ptr %587, align 8
  %589 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %588, i32 0, i32 20
  %590 = load ptr, ptr %589, align 8
  %591 = getelementptr [4 x float], ptr %47, i32 0, i32 0
  store float 0.000000e+00, ptr %591, align 4
  %592 = getelementptr [4 x float], ptr %47, i32 0, i32 1
  store float 0.000000e+00, ptr %592, align 4
  %593 = getelementptr [4 x float], ptr %47, i32 0, i32 2
  store float 6.005000e+03, ptr %593, align 4
  %594 = getelementptr [4 x float], ptr %47, i32 0, i32 3
  store float 2.376000e+03, ptr %594, align 4
  %595 = getelementptr [4 x float], ptr %48, i32 0, i32 0
  store float 0.000000e+00, ptr %595, align 4
  %596 = getelementptr [4 x float], ptr %48, i32 0, i32 1
  %screenHeight220 = load i32, ptr @screenHeight, align 4
  %597 = load i32, ptr @screenHeight, align 4
  %598 = sitofp i32 %597 to double
  %599 = fdiv double %598, 3.000000e+00
  %600 = fptrunc double %599 to float
  store float %600, ptr %596, align 4
  %601 = getelementptr [4 x float], ptr %48, i32 0, i32 2
  %screenWidth221 = load i32, ptr @screenWidth, align 4
  %602 = load i32, ptr @screenWidth, align 4
  %603 = sitofp i32 %602 to double
  %604 = fdiv double %603, 2.000000e+00
  %605 = fptrunc double %604 to float
  store float %605, ptr %601, align 4
  %606 = getelementptr [4 x float], ptr %48, i32 0, i32 3
  %screenHeight222 = load i32, ptr @screenHeight, align 4
  %607 = load i32, ptr @screenHeight, align 4
  %608 = sitofp i32 %607 to double
  %609 = fdiv double %608, 3.000000e+00
  %610 = fptrunc double %609 to float
  store float %610, ptr %606, align 4
  %611 = getelementptr [2 x float], ptr %49, i32 0, i32 0
  %612 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x223 = load float, ptr %612, align 4
  %613 = load float, ptr %612, align 4
  store float %613, ptr %611, align 4
  %614 = getelementptr [2 x float], ptr %49, i32 0, i32 1
  %615 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  %y224 = load float, ptr %615, align 4
  %616 = load float, ptr %615, align 4
  store float %616, ptr %614, align 4
  store float 0.000000e+00, ptr %50, align 4
  %617 = load ptr, ptr %fgAnim, align 8
  %618 = getelementptr inbounds %FlowWingAnim, ptr %617, i32 0, i32 5
  %619 = getelementptr inbounds %COLORS_TYPE.3, ptr %618, i32 0, i32 0
  %WHITE225 = load i32, ptr %619, align 4
  call void %590(ptr %mount1L3Texture, ptr %47, ptr %48, ptr %49, ptr %50, ptr %619, ptr %fgAnim)
  %620 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %621 = icmp eq i32 %620, 0
  br i1 %621, label %checkContinueBlock103, label %afterNestedBlock75

checkContinueBlock103:                            ; preds = %nestedBlock102
  %622 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %623 = icmp eq i32 %622, 0
  br i1 %623, label %nestedBlock104, label %afterNestedBlock75

nestedBlock104:                                   ; preds = %checkContinueBlock103
  %624 = load ptr, ptr %fgAnim, align 8
  %625 = getelementptr inbounds %FlowWingAnim, ptr %624, i32 0, i32 0
  %626 = load ptr, ptr %625, align 8
  %627 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %626, i32 0, i32 20
  %628 = load ptr, ptr %627, align 8
  %629 = getelementptr [4 x float], ptr %51, i32 0, i32 0
  store float 0.000000e+00, ptr %629, align 4
  %630 = getelementptr [4 x float], ptr %51, i32 0, i32 1
  store float 0.000000e+00, ptr %630, align 4
  %631 = getelementptr [4 x float], ptr %51, i32 0, i32 2
  store float 8.982000e+03, ptr %631, align 4
  %632 = getelementptr [4 x float], ptr %51, i32 0, i32 3
  store float 1.542000e+03, ptr %632, align 4
  %633 = getelementptr [4 x float], ptr %52, i32 0, i32 0
  store float 0.000000e+00, ptr %633, align 4
  %634 = getelementptr [4 x float], ptr %52, i32 0, i32 1
  %screenHeight226 = load i32, ptr @screenHeight, align 4
  %635 = load i32, ptr @screenHeight, align 4
  %636 = sitofp i32 %635 to double
  %637 = fdiv double %636, 3.000000e+00
  %638 = fptrunc double %637 to float
  store float %638, ptr %634, align 4
  %639 = getelementptr [4 x float], ptr %52, i32 0, i32 2
  %screenWidth227 = load i32, ptr @screenWidth, align 4
  %640 = load i32, ptr @screenWidth, align 4
  %screenWidth228 = load i32, ptr @screenWidth, align 4
  %641 = load i32, ptr @screenWidth, align 4
  %642 = sitofp i32 %641 to double
  %643 = fdiv double %642, 2.000000e+00
  %644 = sitofp i32 %640 to double
  %645 = fadd double %644, %643
  %646 = fptrunc double %645 to float
  store float %646, ptr %639, align 4
  %647 = getelementptr [4 x float], ptr %52, i32 0, i32 3
  %screenHeight229 = load i32, ptr @screenHeight, align 4
  %648 = load i32, ptr @screenHeight, align 4
  %649 = sitofp i32 %648 to double
  %650 = fdiv double %649, 3.000000e+00
  %651 = fptrunc double %650 to float
  store float %651, ptr %647, align 4
  %652 = getelementptr [2 x float], ptr %53, i32 0, i32 0
  %653 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x230 = load float, ptr %653, align 4
  %654 = load float, ptr %653, align 4
  store float %654, ptr %652, align 4
  %655 = getelementptr [2 x float], ptr %53, i32 0, i32 1
  %656 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y231 = load float, ptr %656, align 4
  %657 = load float, ptr %656, align 4
  store float %657, ptr %655, align 4
  store float 0.000000e+00, ptr %54, align 4
  %658 = load ptr, ptr %fgAnim, align 8
  %659 = getelementptr inbounds %FlowWingAnim, ptr %658, i32 0, i32 5
  %660 = getelementptr inbounds %COLORS_TYPE.3, ptr %659, i32 0, i32 0
  %WHITE232 = load i32, ptr %660, align 4
  call void %628(ptr %mountL1Texture, ptr %51, ptr %52, ptr %53, ptr %54, ptr %660, ptr %fgAnim)
  %661 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %662 = icmp eq i32 %661, 0
  br i1 %662, label %checkContinueBlock105, label %afterNestedBlock75

checkContinueBlock105:                            ; preds = %nestedBlock104
  %663 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %664 = icmp eq i32 %663, 0
  br i1 %664, label %nestedBlock106, label %afterNestedBlock75

nestedBlock106:                                   ; preds = %checkContinueBlock105
  %665 = load ptr, ptr %fgAnim, align 8
  %666 = getelementptr inbounds %FlowWingAnim, ptr %665, i32 0, i32 0
  %667 = load ptr, ptr %666, align 8
  %668 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %667, i32 0, i32 20
  %669 = load ptr, ptr %668, align 8
  %670 = getelementptr [4 x float], ptr %55, i32 0, i32 0
  store float 0.000000e+00, ptr %670, align 4
  %671 = getelementptr [4 x float], ptr %55, i32 0, i32 1
  store float 0.000000e+00, ptr %671, align 4
  %672 = getelementptr [4 x float], ptr %55, i32 0, i32 2
  store float 8.982000e+03, ptr %672, align 4
  %673 = getelementptr [4 x float], ptr %55, i32 0, i32 3
  store float 1.542000e+03, ptr %673, align 4
  %674 = getelementptr [4 x float], ptr %56, i32 0, i32 0
  store float 0.000000e+00, ptr %674, align 4
  %675 = getelementptr [4 x float], ptr %56, i32 0, i32 1
  %screenHeight233 = load i32, ptr @screenHeight, align 4
  %676 = load i32, ptr @screenHeight, align 4
  %677 = sitofp i32 %676 to double
  %678 = fdiv double %677, 3.000000e+00
  %679 = fptrunc double %678 to float
  store float %679, ptr %675, align 4
  %680 = getelementptr [4 x float], ptr %56, i32 0, i32 2
  %screenWidth234 = load i32, ptr @screenWidth, align 4
  %681 = load i32, ptr @screenWidth, align 4
  %screenWidth235 = load i32, ptr @screenWidth, align 4
  %682 = load i32, ptr @screenWidth, align 4
  %683 = sitofp i32 %682 to double
  %684 = fdiv double %683, 2.000000e+00
  %685 = sitofp i32 %681 to double
  %686 = fadd double %685, %684
  %687 = fptrunc double %686 to float
  store float %687, ptr %680, align 4
  %688 = getelementptr [4 x float], ptr %56, i32 0, i32 3
  %screenHeight236 = load i32, ptr @screenHeight, align 4
  %689 = load i32, ptr @screenHeight, align 4
  %690 = sitofp i32 %689 to double
  %691 = fdiv double %690, 3.000000e+00
  %692 = fptrunc double %691 to float
  store float %692, ptr %688, align 4
  %693 = getelementptr [2 x float], ptr %57, i32 0, i32 0
  %694 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x237 = load float, ptr %694, align 4
  %695 = load float, ptr %694, align 4
  store float %695, ptr %693, align 4
  %696 = getelementptr [2 x float], ptr %57, i32 0, i32 1
  %697 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y238 = load float, ptr %697, align 4
  %698 = load float, ptr %697, align 4
  store float %698, ptr %696, align 4
  store float 0.000000e+00, ptr %58, align 4
  %699 = load ptr, ptr %fgAnim, align 8
  %700 = getelementptr inbounds %FlowWingAnim, ptr %699, i32 0, i32 5
  %701 = getelementptr inbounds %COLORS_TYPE.3, ptr %700, i32 0, i32 0
  %WHITE239 = load i32, ptr %701, align 4
  call void %669(ptr %mountL1Texture, ptr %55, ptr %56, ptr %57, ptr %58, ptr %701, ptr %fgAnim)
  %702 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %703 = icmp eq i32 %702, 0
  br i1 %703, label %checkContinueBlock107, label %afterNestedBlock75

checkContinueBlock107:                            ; preds = %nestedBlock106
  %704 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %705 = icmp eq i32 %704, 0
  br i1 %705, label %nestedBlock108, label %afterNestedBlock75

nestedBlock108:                                   ; preds = %checkContinueBlock107
  %706 = load ptr, ptr %fgAnim, align 8
  %707 = getelementptr inbounds %FlowWingAnim, ptr %706, i32 0, i32 0
  %708 = load ptr, ptr %707, align 8
  %709 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %708, i32 0, i32 20
  %710 = load ptr, ptr %709, align 8
  %711 = getelementptr [4 x float], ptr %59, i32 0, i32 0
  store float 3.100000e+02, ptr %711, align 4
  %712 = getelementptr [4 x float], ptr %59, i32 0, i32 1
  store float 1.250000e+03, ptr %712, align 4
  %713 = getelementptr [4 x float], ptr %59, i32 0, i32 2
  store float 4.360000e+03, ptr %713, align 4
  %714 = getelementptr [4 x float], ptr %59, i32 0, i32 3
  store float 1.250000e+03, ptr %714, align 4
  %715 = getelementptr [4 x float], ptr %60, i32 0, i32 0
  store float 0.000000e+00, ptr %715, align 4
  %716 = getelementptr [4 x float], ptr %60, i32 0, i32 1
  %screenHeight240 = load i32, ptr @screenHeight, align 4
  %717 = load i32, ptr @screenHeight, align 4
  %718 = sitofp i32 %717 to double
  %719 = fdiv double %718, 2.000000e+00
  %screenHeight241 = load i32, ptr @screenHeight, align 4
  %720 = load i32, ptr @screenHeight, align 4
  %721 = sitofp i32 %720 to double
  %722 = fdiv double %721, 1.000000e+01
  %723 = fadd double %719, %722
  %724 = fptrunc double %723 to float
  store float %724, ptr %716, align 4
  %725 = getelementptr [4 x float], ptr %60, i32 0, i32 2
  %screenWidth242 = load i32, ptr @screenWidth, align 4
  %726 = load i32, ptr @screenWidth, align 4
  %727 = sitofp i32 %726 to float
  store float %727, ptr %725, align 4
  %728 = getelementptr [4 x float], ptr %60, i32 0, i32 3
  %screenHeight243 = load i32, ptr @screenHeight, align 4
  %729 = load i32, ptr @screenHeight, align 4
  %730 = sitofp i32 %729 to double
  %731 = fdiv double %730, 2.000000e+00
  %732 = fptrunc double %731 to float
  store float %732, ptr %728, align 4
  %733 = getelementptr [2 x float], ptr %61, i32 0, i32 0
  %734 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x244 = load float, ptr %734, align 4
  %735 = load float, ptr %734, align 4
  store float %735, ptr %733, align 4
  %736 = getelementptr [2 x float], ptr %61, i32 0, i32 1
  %737 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y245 = load float, ptr %737, align 4
  %738 = load float, ptr %737, align 4
  store float %738, ptr %736, align 4
  store float 0.000000e+00, ptr %62, align 4
  %739 = load ptr, ptr %fgAnim, align 8
  %740 = getelementptr inbounds %FlowWingAnim, ptr %739, i32 0, i32 5
  %741 = getelementptr inbounds %COLORS_TYPE.3, ptr %740, i32 0, i32 0
  %WHITE246 = load i32, ptr %741, align 4
  call void %710(ptr %groundTexture, ptr %59, ptr %60, ptr %61, ptr %62, ptr %741, ptr %fgAnim)
  %742 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %743 = icmp eq i32 %742, 0
  br i1 %743, label %checkContinueBlock109, label %afterNestedBlock75

checkContinueBlock109:                            ; preds = %nestedBlock108
  %744 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %745 = icmp eq i32 %744, 0
  br i1 %745, label %nestedBlock110, label %afterNestedBlock75

nestedBlock110:                                   ; preds = %checkContinueBlock109
  %746 = load ptr, ptr %fgAnim, align 8
  %747 = getelementptr inbounds %FlowWingAnim, ptr %746, i32 0, i32 0
  %748 = load ptr, ptr %747, align 8
  %749 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %748, i32 0, i32 20
  %750 = load ptr, ptr %749, align 8
  %751 = getelementptr [4 x float], ptr %63, i32 0, i32 0
  store float 3.100000e+02, ptr %751, align 4
  %752 = getelementptr [4 x float], ptr %63, i32 0, i32 1
  store float 1.250000e+03, ptr %752, align 4
  %753 = getelementptr [4 x float], ptr %63, i32 0, i32 2
  store float 4.360000e+03, ptr %753, align 4
  %754 = getelementptr [4 x float], ptr %63, i32 0, i32 3
  store float 1.250000e+03, ptr %754, align 4
  %755 = getelementptr [4 x float], ptr %64, i32 0, i32 0
  store float 0.000000e+00, ptr %755, align 4
  %756 = getelementptr [4 x float], ptr %64, i32 0, i32 1
  %screenHeight247 = load i32, ptr @screenHeight, align 4
  %757 = load i32, ptr @screenHeight, align 4
  %758 = sitofp i32 %757 to double
  %759 = fdiv double %758, 2.000000e+00
  %screenHeight248 = load i32, ptr @screenHeight, align 4
  %760 = load i32, ptr @screenHeight, align 4
  %761 = sitofp i32 %760 to double
  %762 = fdiv double %761, 1.000000e+01
  %763 = fadd double %759, %762
  %764 = fptrunc double %763 to float
  store float %764, ptr %756, align 4
  %765 = getelementptr [4 x float], ptr %64, i32 0, i32 2
  %screenWidth249 = load i32, ptr @screenWidth, align 4
  %766 = load i32, ptr @screenWidth, align 4
  %767 = sitofp i32 %766 to float
  store float %767, ptr %765, align 4
  %768 = getelementptr [4 x float], ptr %64, i32 0, i32 3
  %screenHeight250 = load i32, ptr @screenHeight, align 4
  %769 = load i32, ptr @screenHeight, align 4
  %770 = sitofp i32 %769 to double
  %771 = fdiv double %770, 2.000000e+00
  %772 = fptrunc double %771 to float
  store float %772, ptr %768, align 4
  %773 = getelementptr [2 x float], ptr %65, i32 0, i32 0
  %774 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x251 = load float, ptr %774, align 4
  %775 = load float, ptr %774, align 4
  store float %775, ptr %773, align 4
  %776 = getelementptr [2 x float], ptr %65, i32 0, i32 1
  %777 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y252 = load float, ptr %777, align 4
  %778 = load float, ptr %777, align 4
  store float %778, ptr %776, align 4
  store float 0.000000e+00, ptr %66, align 4
  %779 = load ptr, ptr %fgAnim, align 8
  %780 = getelementptr inbounds %FlowWingAnim, ptr %779, i32 0, i32 5
  %781 = getelementptr inbounds %COLORS_TYPE.3, ptr %780, i32 0, i32 0
  %WHITE253 = load i32, ptr %781, align 4
  call void %750(ptr %groundTexture, ptr %63, ptr %64, ptr %65, ptr %66, ptr %781, ptr %fgAnim)
  %782 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %783 = icmp eq i32 %782, 0
  br i1 %783, label %checkContinueBlock111, label %afterNestedBlock75

checkContinueBlock111:                            ; preds = %nestedBlock110
  %784 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %785 = icmp eq i32 %784, 0
  br i1 %785, label %nestedBlock112, label %afterNestedBlock75

nestedBlock112:                                   ; preds = %checkContinueBlock111
  %786 = load ptr, ptr %fgAnim, align 8
  %787 = getelementptr inbounds %FlowWingAnim, ptr %786, i32 0, i32 0
  %788 = load ptr, ptr %787, align 8
  %789 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %788, i32 0, i32 20
  %790 = load ptr, ptr %789, align 8
  %791 = load ptr, ptr %bird, align 8
  %792 = getelementptr inbounds %Bird, ptr %791, i32 0, i32 0
  %793 = load ptr, ptr %792, align 8
  %794 = getelementptr inbounds %"Bird::VTableType", ptr %793, i32 0, i32 0
  %795 = load ptr, ptr %794, align 8
  call void %795(ptr %67, ptr %bird)
  %796 = load ptr, ptr %bird, align 8
  %797 = getelementptr inbounds %Bird, ptr %796, i32 0, i32 0
  %798 = load ptr, ptr %797, align 8
  %799 = getelementptr inbounds %"Bird::VTableType", ptr %798, i32 0, i32 4
  %800 = load ptr, ptr %799, align 8
  call void %800(ptr %68, ptr %bird)
  %801 = load ptr, ptr %bird, align 8
  %802 = getelementptr inbounds %Bird, ptr %801, i32 0, i32 0
  %803 = load ptr, ptr %802, align 8
  %804 = getelementptr inbounds %"Bird::VTableType", ptr %803, i32 0, i32 3
  %805 = load ptr, ptr %804, align 8
  call void %805(ptr %69, ptr %bird)
  %806 = load ptr, ptr %bird, align 8
  %807 = getelementptr inbounds %Bird, ptr %806, i32 0, i32 0
  %808 = load ptr, ptr %807, align 8
  %809 = getelementptr inbounds %"Bird::VTableType", ptr %808, i32 0, i32 2
  %810 = load ptr, ptr %809, align 8
  call void %810(ptr %70, ptr %bird)
  %811 = load ptr, ptr %bird, align 8
  %812 = getelementptr inbounds %Bird, ptr %811, i32 0, i32 0
  %813 = load ptr, ptr %812, align 8
  %814 = getelementptr inbounds %"Bird::VTableType", ptr %813, i32 0, i32 1
  %815 = load ptr, ptr %814, align 8
  call void %815(ptr %71, ptr %bird)
  %816 = load ptr, ptr %fgAnim, align 8
  %817 = getelementptr inbounds %FlowWingAnim, ptr %816, i32 0, i32 5
  %818 = getelementptr inbounds %COLORS_TYPE.3, ptr %817, i32 0, i32 0
  %WHITE254 = load i32, ptr %818, align 4
  call void %790(ptr %67, ptr %68, ptr %69, ptr %70, ptr %71, ptr %818, ptr %fgAnim)
  %819 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %820 = icmp eq i32 %819, 0
  br i1 %820, label %checkContinueBlock113, label %afterNestedBlock75

checkContinueBlock113:                            ; preds = %nestedBlock112
  %821 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %822 = icmp eq i32 %821, 0
  br i1 %822, label %nestedBlock114, label %afterNestedBlock75

nestedBlock114:                                   ; preds = %checkContinueBlock113
  %823 = load ptr, ptr %fgAnim, align 8
  %824 = getelementptr inbounds %FlowWingAnim, ptr %823, i32 0, i32 0
  %825 = load ptr, ptr %824, align 8
  %826 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %825, i32 0, i32 22
  %827 = load ptr, ptr %826, align 8
  call void %827(ptr %fgAnim)
  %828 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %829 = icmp eq i32 %828, 0
  br i1 %829, label %checkContinueBlock115, label %afterNestedBlock75

checkContinueBlock115:                            ; preds = %nestedBlock114
  br label %afterNestedBlock75

afterNestedBlock116:                              ; preds = %checkContinueBlock124, %afterIfElse139, %checkContinueBlock122, %afterIfElse131, %checkContinueBlock120, %nestedBlock119, %checkContinueBlock118, %nestedBlock117
  %830 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %831 = icmp eq i32 %830, 0
  br i1 %831, label %checkContinueBlock79, label %afterNestedBlock75

nestedBlock117:                                   ; preds = %nestedBlock78
  %832 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x = load float, ptr %832, align 4
  %833 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x125 = load float, ptr %833, align 4
  %834 = load float, ptr %833, align 4
  %835 = load ptr, ptr %fgAnim, align 8
  %836 = getelementptr inbounds %FlowWingAnim, ptr %835, i32 0, i32 0
  %837 = load ptr, ptr %836, align 8
  %838 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %837, i32 0, i32 8
  %839 = load ptr, ptr %838, align 8
  call void %839(ptr %rtPtr10, ptr %fgAnim)
  %840 = load float, ptr %rtPtr10, align 4
  %841 = fmul float %840, 1.000000e+02
  %842 = fadd float %834, %841
  store float %842, ptr %832, align 4
  %843 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %844 = icmp eq i32 %843, 0
  br i1 %844, label %checkContinueBlock118, label %afterNestedBlock116

checkContinueBlock118:                            ; preds = %nestedBlock117
  %845 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %846 = icmp eq i32 %845, 0
  br i1 %846, label %nestedBlock119, label %afterNestedBlock116

nestedBlock119:                                   ; preds = %checkContinueBlock118
  %847 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x126 = load float, ptr %847, align 4
  %848 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x127 = load float, ptr %848, align 4
  %849 = load float, ptr %848, align 4
  %850 = load ptr, ptr %fgAnim, align 8
  %851 = getelementptr inbounds %FlowWingAnim, ptr %850, i32 0, i32 0
  %852 = load ptr, ptr %851, align 8
  %853 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %852, i32 0, i32 8
  %854 = load ptr, ptr %853, align 8
  call void %854(ptr %rtPtr11, ptr %fgAnim)
  %855 = load float, ptr %rtPtr11, align 4
  %856 = fmul float %855, 1.000000e+02
  %857 = fadd float %849, %856
  store float %857, ptr %847, align 4
  %858 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %859 = icmp eq i32 %858, 0
  br i1 %859, label %checkContinueBlock120, label %afterNestedBlock116

checkContinueBlock120:                            ; preds = %nestedBlock119
  %860 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %861 = icmp eq i32 %860, 0
  br i1 %861, label %nestedBlock121, label %afterNestedBlock116

nestedBlock121:                                   ; preds = %checkContinueBlock120
  %862 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x128 = load float, ptr %862, align 4
  %863 = load float, ptr %862, align 4
  %864 = fcmp ogt float %863, 1.542000e+03
  br i1 %864, label %then129, label %else130

checkContinueBlock122:                            ; preds = %afterIfElse131
  %865 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %866 = icmp eq i32 %865, 0
  br i1 %866, label %nestedBlock123, label %afterNestedBlock116

nestedBlock123:                                   ; preds = %checkContinueBlock122
  %867 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x136 = load float, ptr %867, align 4
  %868 = load float, ptr %867, align 4
  %869 = fcmp ogt float %868, 1.542000e+03
  br i1 %869, label %then137, label %else138

checkContinueBlock124:                            ; preds = %afterIfElse139
  br label %afterNestedBlock116

then129:                                          ; preds = %nestedBlock121
  br label %nestedBlock133

else130:                                          ; preds = %nestedBlock121
  br label %afterIfElse131

afterIfElse131:                                   ; preds = %else130, %afterNestedBlock132
  %870 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %871 = icmp eq i32 %870, 0
  br i1 %871, label %checkContinueBlock122, label %afterNestedBlock116

afterNestedBlock132:                              ; preds = %checkContinueBlock134, %nestedBlock133
  %872 = load float, ptr %873, align 4
  br label %afterIfElse131

nestedBlock133:                                   ; preds = %then129
  %873 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x135 = load float, ptr %873, align 4
  store float -1.542000e+03, ptr %873, align 4
  %874 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %875 = icmp eq i32 %874, 0
  br i1 %875, label %checkContinueBlock134, label %afterNestedBlock132

checkContinueBlock134:                            ; preds = %nestedBlock133
  br label %afterNestedBlock132

then137:                                          ; preds = %nestedBlock123
  br label %nestedBlock141

else138:                                          ; preds = %nestedBlock123
  br label %afterIfElse139

afterIfElse139:                                   ; preds = %else138, %afterNestedBlock140
  %876 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %877 = icmp eq i32 %876, 0
  br i1 %877, label %checkContinueBlock124, label %afterNestedBlock116

afterNestedBlock140:                              ; preds = %checkContinueBlock142, %nestedBlock141
  %878 = load float, ptr %879, align 4
  br label %afterIfElse139

nestedBlock141:                                   ; preds = %then137
  %879 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x143 = load float, ptr %879, align 4
  store float -1.542000e+03, ptr %879, align 4
  %880 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %881 = icmp eq i32 %880, 0
  br i1 %881, label %checkContinueBlock142, label %afterNestedBlock140

checkContinueBlock142:                            ; preds = %nestedBlock141
  br label %afterNestedBlock140

afterNestedBlock144:                              ; preds = %checkContinueBlock148, %afterIfElse156, %checkContinueBlock146, %nestedBlock145
  %882 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %883 = icmp eq i32 %882, 0
  br i1 %883, label %checkContinueBlock81, label %afterNestedBlock75

nestedBlock145:                                   ; preds = %nestedBlock80
  %884 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x149 = load float, ptr %884, align 4
  %885 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x150 = load float, ptr %885, align 4
  %886 = load float, ptr %885, align 4
  %887 = load ptr, ptr %fgAnim, align 8
  %888 = getelementptr inbounds %FlowWingAnim, ptr %887, i32 0, i32 0
  %889 = load ptr, ptr %888, align 8
  %890 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %889, i32 0, i32 8
  %891 = load ptr, ptr %890, align 8
  call void %891(ptr %rtPtr12, ptr %fgAnim)
  %892 = load float, ptr %rtPtr12, align 4
  %893 = fmul float %892, 1.000000e+01
  %894 = fadd float %886, %893
  store float %894, ptr %884, align 4
  %895 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %896 = icmp eq i32 %895, 0
  br i1 %896, label %checkContinueBlock146, label %afterNestedBlock144

checkContinueBlock146:                            ; preds = %nestedBlock145
  %897 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %898 = icmp eq i32 %897, 0
  br i1 %898, label %nestedBlock147, label %afterNestedBlock144

nestedBlock147:                                   ; preds = %checkContinueBlock146
  %899 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x151 = load float, ptr %899, align 4
  %900 = load float, ptr %899, align 4
  %screenWidth152 = load i32, ptr @screenWidth, align 4
  %901 = load i32, ptr @screenWidth, align 4
  %screenWidth153 = load i32, ptr @screenWidth, align 4
  %902 = load i32, ptr @screenWidth, align 4
  %903 = sitofp i32 %902 to double
  %904 = fdiv double %903, 2.000000e+00
  %905 = sitofp i32 %901 to double
  %906 = fadd double %905, %904
  %907 = fptrunc double %906 to float
  %908 = fcmp ogt float %900, %907
  br i1 %908, label %then154, label %else155

checkContinueBlock148:                            ; preds = %afterIfElse156
  br label %afterNestedBlock144

then154:                                          ; preds = %nestedBlock147
  br label %nestedBlock158

else155:                                          ; preds = %nestedBlock147
  br label %afterIfElse156

afterIfElse156:                                   ; preds = %else155, %afterNestedBlock157
  %909 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %910 = icmp eq i32 %909, 0
  br i1 %910, label %checkContinueBlock148, label %afterNestedBlock144

afterNestedBlock157:                              ; preds = %checkContinueBlock159, %nestedBlock158
  %911 = load float, ptr %912, align 4
  br label %afterIfElse156

nestedBlock158:                                   ; preds = %then154
  %912 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x160 = load float, ptr %912, align 4
  %screenWidth161 = load i32, ptr @screenWidth, align 4
  %913 = load i32, ptr @screenWidth, align 4
  %914 = mul i32 -1, %913
  %915 = sitofp i32 %914 to float
  store float %915, ptr %912, align 4
  %916 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %917 = icmp eq i32 %916, 0
  br i1 %917, label %checkContinueBlock159, label %afterNestedBlock157

checkContinueBlock159:                            ; preds = %nestedBlock158
  br label %afterNestedBlock157

afterNestedBlock162:                              ; preds = %checkContinueBlock166, %afterIfElse174, %checkContinueBlock164, %nestedBlock163
  %918 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %919 = icmp eq i32 %918, 0
  br i1 %919, label %checkContinueBlock83, label %afterNestedBlock75

nestedBlock163:                                   ; preds = %nestedBlock82
  %920 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x167 = load float, ptr %920, align 4
  %921 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x168 = load float, ptr %921, align 4
  %922 = load float, ptr %921, align 4
  %923 = load ptr, ptr %fgAnim, align 8
  %924 = getelementptr inbounds %FlowWingAnim, ptr %923, i32 0, i32 0
  %925 = load ptr, ptr %924, align 8
  %926 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %925, i32 0, i32 8
  %927 = load ptr, ptr %926, align 8
  call void %927(ptr %rtPtr13, ptr %fgAnim)
  %928 = load float, ptr %rtPtr13, align 4
  %929 = fmul float %928, 1.000000e+01
  %930 = fadd float %922, %929
  store float %930, ptr %920, align 4
  %931 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %932 = icmp eq i32 %931, 0
  br i1 %932, label %checkContinueBlock164, label %afterNestedBlock162

checkContinueBlock164:                            ; preds = %nestedBlock163
  %933 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %934 = icmp eq i32 %933, 0
  br i1 %934, label %nestedBlock165, label %afterNestedBlock162

nestedBlock165:                                   ; preds = %checkContinueBlock164
  %935 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x169 = load float, ptr %935, align 4
  %936 = load float, ptr %935, align 4
  %screenWidth170 = load i32, ptr @screenWidth, align 4
  %937 = load i32, ptr @screenWidth, align 4
  %screenWidth171 = load i32, ptr @screenWidth, align 4
  %938 = load i32, ptr @screenWidth, align 4
  %939 = sitofp i32 %938 to double
  %940 = fdiv double %939, 2.000000e+00
  %941 = sitofp i32 %937 to double
  %942 = fadd double %941, %940
  %943 = fptrunc double %942 to float
  %944 = fcmp ogt float %936, %943
  br i1 %944, label %then172, label %else173

checkContinueBlock166:                            ; preds = %afterIfElse174
  br label %afterNestedBlock162

then172:                                          ; preds = %nestedBlock165
  br label %nestedBlock176

else173:                                          ; preds = %nestedBlock165
  br label %afterIfElse174

afterIfElse174:                                   ; preds = %else173, %afterNestedBlock175
  %945 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %946 = icmp eq i32 %945, 0
  br i1 %946, label %checkContinueBlock166, label %afterNestedBlock162

afterNestedBlock175:                              ; preds = %checkContinueBlock177, %nestedBlock176
  %947 = load float, ptr %948, align 4
  br label %afterIfElse174

nestedBlock176:                                   ; preds = %then172
  %948 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x178 = load float, ptr %948, align 4
  %screenWidth179 = load i32, ptr @screenWidth, align 4
  %949 = load i32, ptr @screenWidth, align 4
  %950 = mul i32 -1, %949
  %951 = sitofp i32 %950 to float
  store float %951, ptr %948, align 4
  %952 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %953 = icmp eq i32 %952, 0
  br i1 %953, label %checkContinueBlock177, label %afterNestedBlock175

checkContinueBlock177:                            ; preds = %nestedBlock176
  br label %afterNestedBlock175

afterNestedBlock180:                              ; preds = %checkContinueBlock184, %afterIfElse192, %checkContinueBlock182, %nestedBlock181
  %954 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %955 = icmp eq i32 %954, 0
  br i1 %955, label %checkContinueBlock85, label %afterNestedBlock75

nestedBlock181:                                   ; preds = %nestedBlock84
  %956 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x185 = load float, ptr %956, align 4
  %957 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x186 = load float, ptr %957, align 4
  %958 = load float, ptr %957, align 4
  %959 = load ptr, ptr %fgAnim, align 8
  %960 = getelementptr inbounds %FlowWingAnim, ptr %959, i32 0, i32 0
  %961 = load ptr, ptr %960, align 8
  %962 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %961, i32 0, i32 8
  %963 = load ptr, ptr %962, align 8
  call void %963(ptr %rtPtr14, ptr %fgAnim)
  %964 = load float, ptr %rtPtr14, align 4
  %965 = fmul float %964, 1.000000e+01
  %966 = fadd float %958, %965
  store float %966, ptr %956, align 4
  %967 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %968 = icmp eq i32 %967, 0
  br i1 %968, label %checkContinueBlock182, label %afterNestedBlock180

checkContinueBlock182:                            ; preds = %nestedBlock181
  %969 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %970 = icmp eq i32 %969, 0
  br i1 %970, label %nestedBlock183, label %afterNestedBlock180

nestedBlock183:                                   ; preds = %checkContinueBlock182
  %971 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x187 = load float, ptr %971, align 4
  %972 = load float, ptr %971, align 4
  %screenWidth188 = load i32, ptr @screenWidth, align 4
  %973 = load i32, ptr @screenWidth, align 4
  %screenWidth189 = load i32, ptr @screenWidth, align 4
  %974 = load i32, ptr @screenWidth, align 4
  %975 = sitofp i32 %974 to double
  %976 = fdiv double %975, 2.000000e+00
  %977 = sitofp i32 %973 to double
  %978 = fadd double %977, %976
  %979 = fptrunc double %978 to float
  %980 = fcmp ogt float %972, %979
  br i1 %980, label %then190, label %else191

checkContinueBlock184:                            ; preds = %afterIfElse192
  br label %afterNestedBlock180

then190:                                          ; preds = %nestedBlock183
  br label %nestedBlock194

else191:                                          ; preds = %nestedBlock183
  br label %afterIfElse192

afterIfElse192:                                   ; preds = %else191, %afterNestedBlock193
  %981 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %982 = icmp eq i32 %981, 0
  br i1 %982, label %checkContinueBlock184, label %afterNestedBlock180

afterNestedBlock193:                              ; preds = %checkContinueBlock195, %nestedBlock194
  %983 = load float, ptr %984, align 4
  br label %afterIfElse192

nestedBlock194:                                   ; preds = %then190
  %984 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x196 = load float, ptr %984, align 4
  %screenWidth197 = load i32, ptr @screenWidth, align 4
  %985 = load i32, ptr @screenWidth, align 4
  %986 = mul i32 -1, %985
  %screenWidth198 = load i32, ptr @screenWidth, align 4
  %987 = load i32, ptr @screenWidth, align 4
  %988 = sitofp i32 %987 to double
  %989 = fdiv double %988, 4.000000e+00
  %990 = fptosi double %989 to i32
  store i32 %990, ptr %29, align 4
  %screenWidth199 = load i32, ptr @screenWidth, align 4
  %991 = load i32, ptr @screenWidth, align 4
  %992 = sitofp i32 %991 to double
  %993 = fdiv double %992, 2.000000e+00
  %994 = fptosi double %993 to i32
  store i32 %994, ptr %30, align 4
  call void @getRandomNumber(ptr %rtPtr15, ptr %29, ptr %30)
  %995 = load i32, ptr %rtPtr15, align 4
  %996 = sub i32 %986, %995
  %997 = sitofp i32 %996 to float
  store float %997, ptr %984, align 4
  %998 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %999 = icmp eq i32 %998, 0
  br i1 %999, label %checkContinueBlock195, label %afterNestedBlock193

checkContinueBlock195:                            ; preds = %nestedBlock194
  br label %afterNestedBlock193

then201:                                          ; preds = %nestedBlock86
  br label %nestedBlock205

else202:                                          ; preds = %nestedBlock86
  br label %afterIfElse203

afterIfElse203:                                   ; preds = %else202, %afterNestedBlock204
  %1000 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1001 = icmp eq i32 %1000, 0
  br i1 %1001, label %checkContinueBlock87, label %afterNestedBlock75

afterNestedBlock204:                              ; preds = %checkContinueBlock206, %nestedBlock205
  br label %afterIfElse203

nestedBlock205:                                   ; preds = %then201
  %1002 = load ptr, ptr %bird, align 8
  %1003 = getelementptr inbounds %Bird, ptr %1002, i32 0, i32 0
  %1004 = load ptr, ptr %1003, align 8
  %1005 = getelementptr inbounds %"Bird::VTableType", ptr %1004, i32 0, i32 8
  %1006 = load ptr, ptr %1005, align 8
  %1007 = load ptr, ptr %fgAnim, align 8
  %1008 = getelementptr inbounds %FlowWingAnim, ptr %1007, i32 0, i32 0
  %1009 = load ptr, ptr %1008, align 8
  %1010 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1009, i32 0, i32 8
  %1011 = load ptr, ptr %1010, align 8
  call void %1011(ptr %33, ptr %fgAnim)
  call void %1006(ptr %33, ptr %bird)
  %1012 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1013 = icmp eq i32 %1012, 0
  br i1 %1013, label %checkContinueBlock206, label %afterNestedBlock204

checkContinueBlock206:                            ; preds = %nestedBlock205
  br label %afterNestedBlock204

decrement_block255:                               ; preds = %while.end
  %1014 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1015 = sub i32 %1014, 1
  store i32 %1015, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block256

end_block256:                                     ; preds = %decrement_block255, %while.end
  %1016 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1017 = icmp eq i32 %1016, 0
  br i1 %1017, label %checkContinueBlock53, label %afterNestedBlock

returnBlock257:                                   ; preds = %nestedBlock56
  store i32 0, ptr %0, align 4
  ret void

mergeBlock258:                                    ; No predecessors!
  %1018 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1019 = icmp eq i32 %1018, 0
  br i1 %1019, label %checkContinueBlock57, label %afterNestedBlock
}

define internal void @"assign_<ObjectTexture.0>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Texture.0, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Texture.0, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %Texture.0, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %Texture.0, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %Texture.0, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  ret void
}

define internal void @"assign_<Array[9]<ObjectPosition.4>>:9,"(ptr %0) {
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
  %7 = getelementptr [9 x %Position.4], ptr %0, i32 0, i32 %6
  call void @"assign_<ObjectPosition.4>"(ptr %7)
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

define internal void @"assign_<ObjectPosition.4>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Position.4, ptr %0, i32 0, i32 0
  store float 0.000000e+00, ptr %1, align 4
  %2 = getelementptr inbounds %Position.4, ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %2, align 4
  ret void
}

define internal void @"assign_<Array[5]<ObjectAttributeType.5>>:5,"(ptr %0) {
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
  %7 = getelementptr [5 x %AttributeType.5], ptr %0, i32 0, i32 %6
  call void @"assign_<ObjectAttributeType.5>"(ptr %7)
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

define internal void @"assign_<ObjectAttributeType.5>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 0
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %1)
  %2 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 1
  call void @"assign_<Array[4]<'Decimal32'>>:4,"(ptr %2)
  %3 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 2
  call void @"assign_<Array[2]<'Decimal32'>>:2,"(ptr %3)
  %4 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 3
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

define internal void @"assign_<Class<FlowWingAnim>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  store ptr @18, ptr %1, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  store ptr @19, ptr %4, align 8
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  call void @"assign_<ObjectCOLORS_TYPE.3>"(ptr %6)
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  call void @"assign_<ObjectKEYS_TYPE.2>"(ptr %7)
  %8 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  call void @"assign_<ObjectLOG_TYPE.1>"(ptr %8)
  ret void
}

define internal void @"assign_<ObjectCOLORS_TYPE.3>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %COLORS_TYPE.3, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %COLORS_TYPE.3, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %COLORS_TYPE.3, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %COLORS_TYPE.3, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %COLORS_TYPE.3, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  ret void
}

define internal void @"assign_<ObjectKEYS_TYPE.2>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %KEYS_TYPE.2, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %KEYS_TYPE.2, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %KEYS_TYPE.2, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %KEYS_TYPE.2, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  ret void
}

define internal void @"assign_<ObjectLOG_TYPE.1>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 6
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %LOG_TYPE.1, ptr %0, i32 0, i32 7
  store i32 0, ptr %8, align 4
  ret void
}

define internal void @"assign_<Class<Bird>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 0
  store ptr @22, ptr %1, align 8
  %2 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %2, align 4
  %3 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 2
  store float 0.000000e+00, ptr %3, align 4
  %4 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 3
  store double 0.000000e+00, ptr %4, align 8
  %5 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 4
  store double 0.000000e+00, ptr %5, align 8
  %6 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 6
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 7
  store ptr @23, ptr %8, align 8
  %9 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 8
  store i1 false, ptr %9, align 1
  %10 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  call void @"assign_<ObjectTexture.0>"(ptr %10)
  %11 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 10
  call void @"assign_<Array[9]<ObjectPosition.4>>:9,"(ptr %11)
  %12 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 11
  call void @"assign_<ObjectPosition.4>"(ptr %12)
  ret void
}

define internal void @"assign_<Class<Cloud>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 0
  store ptr @26, ptr %1, align 8
  %2 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 1
  call void @"assign_<Array[5]<ObjectAttributeType.5>>:5,"(ptr %2)
  %3 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 2
  call void @"assign_<ObjectTexture.0>"(ptr %3)
  %4 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 3
  store ptr @27, ptr %4, align 8
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
!20 = !{!"FlowWingAnim.loadTexture:rt:ob:Texture.0"}
!21 = !{!"FlowWingAnim.unloadTexture:rt:pr:27"}
!22 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!23 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!24 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!25 = !{!"Bird.init1:rt:pr:27"}
!26 = !{!"Bird.setTexture:rt:pr:27"}
!27 = !{!"Bird.getTexturePath:rt:pr:33"}
!28 = !{!"Bird.update:rt:pr:27"}
!29 = !{!"Bird.isTextureLoaded:rt:pr:34"}
!30 = !{!"Bird.getSource:rt:ay:32:sz:4:"}
!31 = !{!"Bird.getDistination:rt:ay:32:sz:4:"}
!32 = !{!"Bird.getOrigin:rt:ay:32:sz:2:"}
!33 = !{!"Bird.getRotation:rt:pr:32"}
!34 = !{!"Bird.getTexture:rt:ob:Texture.0"}
!35 = !{!"Bird.updateY:rt:pr:27"}
!36 = !{!"Cloud.init1:rt:pr:27"}
!37 = !{!"Cloud.setTexture:rt:pr:27"}
!38 = !{!"Cloud.getTexture:rt:ob:Texture.0"}
!39 = !{!"Cloud.getTexturePath:rt:pr:33"}
!40 = !{!"Cloud.update:rt:pr:27"}
!41 = !{!"Cloud.draw:rt:pr:27"}
!42 = !{!"getRandomNumber:rt:pr:28"}
!43 = !{!"main:rt:pr:28"}
