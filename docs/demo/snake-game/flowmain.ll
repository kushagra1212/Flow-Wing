; ModuleID = 'flowmain'
source_filename = "flowmain"
target triple = "x86_64-apple-macosx14.0.0"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Bird::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Cloud::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%COLORS_TYPE.3 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.2 = type { i32, i32, i32, i32 }
%LOG_TYPE.1 = type { i32, i32, i32, i32, i32, i32, i32, i32 }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%Position.4 = type { float, float }
%AttributeType.5 = type { [4 x float], [4 x float], [2 x float], float }
%Bird = type { ptr, float, float, double, double, i32, i32, ptr, i1, %Texture.0, [9 x %Position.4], %Position.4 }
%Cloud = type { ptr, [5 x %AttributeType.5], %Texture.0, ptr }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.3, %KEYS_TYPE.2, %LOG_TYPE.1 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.FlowWingAnim.fg = common global %"FlowWingAnim::VTableType" zeroinitializer
@vtable.Bird.fg = common global %"Bird::VTableType" zeroinitializer
@vtable.Cloud.fg = common global %"Cloud::VTableType" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@screenWidth = common global i32 0
@screenHeight = common global i32 0
@FPS = common global i32 0
@side = common global i32 0
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [875 x i8] c"\0A\1B[33m80| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m84| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 84:32\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [953 x i8] c"\0A\1B[33m80| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m84| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 84:71\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [840 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:14\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@6 = private unnamed_addr constant [854 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:24\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@7 = private unnamed_addr constant [884 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:36\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@8 = private unnamed_addr constant [898 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:46\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [851 x i8] c"\0A\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                 \0A   ~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 178:17\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [865 x i8] c"\0A\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                           \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 178:27\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [815 x i8] c"\0A\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 179:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [829 x i8] c"\0A\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 179:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [815 x i8] c"\0A\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 180:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [829 x i8] c"\0A\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 180:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [744 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:40\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@16 = private unnamed_addr constant [778 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                         \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:57\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@17 = private unnamed_addr constant [822 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                               \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:79\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@18 = private unnamed_addr constant [856 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:96\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@22 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [18 x i8] c"./assets/bird.png\00", align 1
@25 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@26 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@27 = private unnamed_addr constant [21 x i8] c"./assets/3clouds.png\00", align 1
@28 = private unnamed_addr constant [27 x i8] c"./assets/skyBackground.png\00", align 1
@29 = private unnamed_addr constant [20 x i8] c"./assets/ground.png\00", align 1
@30 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL1.png\00", align 1
@31 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL2.png\00", align 1
@32 = private unnamed_addr constant [31 x i8] c"./assets/mountain/2mountL2.png\00", align 1
@33 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL3.png\00", align 1
@34 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1

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
  %screenWidth = alloca i32, align 4
  store i32 0, ptr %screenWidth, align 4
  %screenHeight = alloca i32, align 4
  store i32 0, ptr %screenHeight, align 4
  %screenName = alloca ptr, align 8
  store ptr @0, ptr %screenName, align 8
  %fps = alloca i32, align 4
  store i32 0, ptr %fps, align 4
  %colors = alloca %COLORS_TYPE.3, align 8
  %0 = getelementptr inbounds %COLORS_TYPE.3, ptr %colors, i32 0, i32 0
  store i32 0, ptr %0, align 4
  %1 = getelementptr inbounds %COLORS_TYPE.3, ptr %colors, i32 0, i32 1
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %COLORS_TYPE.3, ptr %colors, i32 0, i32 2
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %COLORS_TYPE.3, ptr %colors, i32 0, i32 3
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %COLORS_TYPE.3, ptr %colors, i32 0, i32 4
  store i32 0, ptr %4, align 4
  %KEYS = alloca %KEYS_TYPE.2, align 8
  %5 = getelementptr inbounds %KEYS_TYPE.2, ptr %KEYS, i32 0, i32 0
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %KEYS_TYPE.2, ptr %KEYS, i32 0, i32 1
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %KEYS_TYPE.2, ptr %KEYS, i32 0, i32 2
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %KEYS_TYPE.2, ptr %KEYS, i32 0, i32 3
  store i32 0, ptr %8, align 4
  %LOG = alloca %LOG_TYPE.1, align 8
  %9 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 0
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 1
  store i32 0, ptr %10, align 4
  %11 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 2
  store i32 0, ptr %11, align 4
  %12 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 3
  store i32 0, ptr %12, align 4
  %13 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 4
  store i32 0, ptr %13, align 4
  %14 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 5
  store i32 0, ptr %14, align 4
  %15 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 6
  store i32 0, ptr %15, align 4
  %16 = getelementptr inbounds %LOG_TYPE.1, ptr %LOG, i32 0, i32 7
  store i32 0, ptr %16, align 4
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
  store ptr @1, ptr %birdTexturePath, align 8
  %isBirdAlive = alloca i1, align 1
  store i1 false, ptr %isBirdAlive, align 1
  %birdTexture = alloca %Texture.0, align 8
  %17 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 0
  store i32 0, ptr %17, align 4
  %18 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 1
  store i32 0, ptr %18, align 4
  %19 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 2
  store i32 0, ptr %19, align 4
  %20 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 3
  store i32 0, ptr %20, align 4
  %21 = getelementptr inbounds %Texture.0, ptr %birdTexture, i32 0, i32 4
  store i32 0, ptr %21, align 4
  %birdSpritePosition = alloca [9 x %Position.4], align 8
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  store i32 0, ptr %23, align 4
  br label %FillExpr.loopStart-0

returnBlock:                                      ; preds = %FillExpr.exit5
  ret i32 0

FillExpr.loopStart-0:                             ; preds = %entry
  store i32 0, ptr %22, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %24 = load i32, ptr %22, align 4
  %25 = icmp slt i32 %24, 9
  %26 = load i32, ptr %23, align 4
  %27 = icmp slt i32 %26, 9
  %28 = and i1 %25, %27
  br i1 %28, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %29 = load i32, ptr %22, align 4
  %30 = getelementptr [9 x %Position.4], ptr %birdSpritePosition, i32 0, i32 %29
  %31 = getelementptr inbounds %Position.4, ptr %30, i32 0, i32 0
  store float 0.000000e+00, ptr %31, align 4
  %32 = getelementptr inbounds %Position.4, ptr %30, i32 0, i32 1
  store float 0.000000e+00, ptr %32, align 4
  %33 = load i32, ptr %22, align 4
  %34 = add i32 %33, 1
  store i32 %34, ptr %22, align 4
  %35 = load i32, ptr %23, align 4
  %36 = add i32 %35, 1
  store i32 %36, ptr %23, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %pos = alloca %Position.4, align 8
  %37 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 0
  store float 0.000000e+00, ptr %37, align 4
  %38 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 1
  store float 0.000000e+00, ptr %38, align 4
  %clouds = alloca [5 x %AttributeType.5], align 8
  %39 = alloca i32, align 4
  %40 = alloca i32, align 4
  store i32 0, ptr %40, align 4
  br label %FillExpr.loopStart-01

FillExpr.loopStart-01:                            ; preds = %FillExpr.exit
  store i32 0, ptr %39, align 4
  br label %FillExpr.loopCmp-02

FillExpr.loopCmp-02:                              ; preds = %FillExpr.exit20, %FillExpr.loopStart-01
  %41 = load i32, ptr %39, align 4
  %42 = icmp slt i32 %41, 5
  %43 = load i32, ptr %40, align 4
  %44 = icmp slt i32 %43, 5
  %45 = and i1 %42, %44
  br i1 %45, label %FillExpr.loopBody-03, label %FillExpr.loopEnd-04

FillExpr.loopBody-03:                             ; preds = %FillExpr.loopCmp-02
  %46 = load i32, ptr %39, align 4
  %47 = getelementptr [5 x %AttributeType.5], ptr %clouds, i32 0, i32 %46
  %48 = getelementptr inbounds %AttributeType.5, ptr %47, i32 0, i32 0
  %49 = alloca i32, align 4
  %50 = alloca i32, align 4
  store i32 0, ptr %50, align 4
  br label %FillExpr.loopStart-06

FillExpr.loopEnd-04:                              ; preds = %FillExpr.loopCmp-02
  br label %FillExpr.exit5

FillExpr.exit5:                                   ; preds = %FillExpr.loopEnd-04
  %cloudTexture = alloca %Texture.0, align 8
  %51 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 0
  store i32 0, ptr %51, align 4
  %52 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 1
  store i32 0, ptr %52, align 4
  %53 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 2
  store i32 0, ptr %53, align 4
  %54 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 3
  store i32 0, ptr %54, align 4
  %55 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 4
  store i32 0, ptr %55, align 4
  %texturePath = alloca ptr, align 8
  store ptr @2, ptr %texturePath, align 8
  %56 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()
  store i32 1024, ptr @screenWidth, align 4
  store i32 500, ptr @screenHeight, align 4
  store i32 120, ptr @FPS, align 4
  store i32 10, ptr @side, align 4
  %rtPtr = alloca i32, align 4
  call void @main(ptr %rtPtr)
  br label %returnBlock

FillExpr.loopStart-06:                            ; preds = %FillExpr.loopBody-03
  store i32 0, ptr %49, align 4
  br label %FillExpr.loopCmp-07

FillExpr.loopCmp-07:                              ; preds = %FillExpr.loopBody-08, %FillExpr.loopStart-06
  %57 = load i32, ptr %49, align 4
  %58 = icmp slt i32 %57, 4
  %59 = load i32, ptr %50, align 4
  %60 = icmp slt i32 %59, 4
  %61 = and i1 %58, %60
  br i1 %61, label %FillExpr.loopBody-08, label %FillExpr.loopEnd-09

FillExpr.loopBody-08:                             ; preds = %FillExpr.loopCmp-07
  %62 = load i32, ptr %49, align 4
  %63 = getelementptr [4 x float], ptr %48, i32 0, i32 %62
  store float 0.000000e+00, ptr %63, align 4
  %64 = load i32, ptr %49, align 4
  %65 = add i32 %64, 1
  store i32 %65, ptr %49, align 4
  %66 = load i32, ptr %50, align 4
  %67 = add i32 %66, 1
  store i32 %67, ptr %50, align 4
  br label %FillExpr.loopCmp-07

FillExpr.loopEnd-09:                              ; preds = %FillExpr.loopCmp-07
  br label %FillExpr.exit10

FillExpr.exit10:                                  ; preds = %FillExpr.loopEnd-09
  %68 = getelementptr inbounds %AttributeType.5, ptr %47, i32 0, i32 1
  %69 = alloca i32, align 4
  %70 = alloca i32, align 4
  store i32 0, ptr %70, align 4
  br label %FillExpr.loopStart-011

FillExpr.loopStart-011:                           ; preds = %FillExpr.exit10
  store i32 0, ptr %69, align 4
  br label %FillExpr.loopCmp-012

FillExpr.loopCmp-012:                             ; preds = %FillExpr.loopBody-013, %FillExpr.loopStart-011
  %71 = load i32, ptr %69, align 4
  %72 = icmp slt i32 %71, 4
  %73 = load i32, ptr %70, align 4
  %74 = icmp slt i32 %73, 4
  %75 = and i1 %72, %74
  br i1 %75, label %FillExpr.loopBody-013, label %FillExpr.loopEnd-014

FillExpr.loopBody-013:                            ; preds = %FillExpr.loopCmp-012
  %76 = load i32, ptr %69, align 4
  %77 = getelementptr [4 x float], ptr %68, i32 0, i32 %76
  store float 0.000000e+00, ptr %77, align 4
  %78 = load i32, ptr %69, align 4
  %79 = add i32 %78, 1
  store i32 %79, ptr %69, align 4
  %80 = load i32, ptr %70, align 4
  %81 = add i32 %80, 1
  store i32 %81, ptr %70, align 4
  br label %FillExpr.loopCmp-012

FillExpr.loopEnd-014:                             ; preds = %FillExpr.loopCmp-012
  br label %FillExpr.exit15

FillExpr.exit15:                                  ; preds = %FillExpr.loopEnd-014
  %82 = getelementptr inbounds %AttributeType.5, ptr %47, i32 0, i32 2
  %83 = alloca i32, align 4
  %84 = alloca i32, align 4
  store i32 0, ptr %84, align 4
  br label %FillExpr.loopStart-016

FillExpr.loopStart-016:                           ; preds = %FillExpr.exit15
  store i32 0, ptr %83, align 4
  br label %FillExpr.loopCmp-017

FillExpr.loopCmp-017:                             ; preds = %FillExpr.loopBody-018, %FillExpr.loopStart-016
  %85 = load i32, ptr %83, align 4
  %86 = icmp slt i32 %85, 2
  %87 = load i32, ptr %84, align 4
  %88 = icmp slt i32 %87, 2
  %89 = and i1 %86, %88
  br i1 %89, label %FillExpr.loopBody-018, label %FillExpr.loopEnd-019

FillExpr.loopBody-018:                            ; preds = %FillExpr.loopCmp-017
  %90 = load i32, ptr %83, align 4
  %91 = getelementptr [2 x float], ptr %82, i32 0, i32 %90
  store float 0.000000e+00, ptr %91, align 4
  %92 = load i32, ptr %83, align 4
  %93 = add i32 %92, 1
  store i32 %93, ptr %83, align 4
  %94 = load i32, ptr %84, align 4
  %95 = add i32 %94, 1
  store i32 %95, ptr %84, align 4
  br label %FillExpr.loopCmp-017

FillExpr.loopEnd-019:                             ; preds = %FillExpr.loopCmp-017
  br label %FillExpr.exit20

FillExpr.exit20:                                  ; preds = %FillExpr.loopEnd-019
  %96 = getelementptr inbounds %AttributeType.5, ptr %47, i32 0, i32 3
  store float 0.000000e+00, ptr %96, align 4
  %97 = load i32, ptr %39, align 4
  %98 = add i32 %97, 1
  store i32 %98, ptr %39, align 4
  %99 = load i32, ptr %40, align 4
  %100 = add i32 %99, 1
  store i32 %100, ptr %40, align 4
  br label %FillExpr.loopCmp-02
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  %birdTexturePath = alloca ptr, align 8
  %13 = load ptr, ptr %0, align 8
  store ptr %13, ptr %birdTexturePath, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %14 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %birdTexturePath7 = load ptr, ptr %14, align 8
  %birdTexturePath8 = load ptr, ptr %birdTexturePath, align 8
  %15 = load ptr, ptr %birdTexturePath, align 8
  store ptr %15, ptr %14, align 8
  %16 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %18 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %20 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 4
  %birdTimmer = load double, ptr %20, align 8
  %BIRD_TIMMER = load double, ptr %4, align 8
  %21 = load double, ptr %4, align 8
  store double %21, ptr %20, align 8
  %22 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %24 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %26 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 8
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
  %31 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 10
  %32 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 0
  %33 = getelementptr inbounds %Position.4, ptr %32, i32 0, i32 0
  store float 0.000000e+00, ptr %33, align 4
  %34 = getelementptr inbounds %Position.4, ptr %32, i32 0, i32 1
  store float 0.000000e+00, ptr %34, align 4
  %35 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 1
  %36 = getelementptr inbounds %Position.4, ptr %35, i32 0, i32 0
  %ACTUAL_BIRD_SIZE = load float, ptr %2, align 4
  %37 = load float, ptr %2, align 4
  %38 = fmul float %37, 1.000000e+00
  store float %38, ptr %36, align 4
  %39 = getelementptr inbounds %Position.4, ptr %35, i32 0, i32 1
  store float 0.000000e+00, ptr %39, align 4
  %40 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 2
  %41 = getelementptr inbounds %Position.4, ptr %40, i32 0, i32 0
  %ACTUAL_BIRD_SIZE9 = load float, ptr %2, align 4
  %42 = load float, ptr %2, align 4
  %43 = fmul float %42, 2.000000e+00
  store float %43, ptr %41, align 4
  %44 = getelementptr inbounds %Position.4, ptr %40, i32 0, i32 1
  store float 0.000000e+00, ptr %44, align 4
  %45 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 3
  %46 = getelementptr inbounds %Position.4, ptr %45, i32 0, i32 0
  store float 0.000000e+00, ptr %46, align 4
  %47 = getelementptr inbounds %Position.4, ptr %45, i32 0, i32 1
  %ACTUAL_BIRD_SIZE10 = load float, ptr %2, align 4
  %48 = load float, ptr %2, align 4
  %49 = fmul float %48, 1.000000e+00
  store float %49, ptr %47, align 4
  %50 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 4
  %51 = getelementptr inbounds %Position.4, ptr %50, i32 0, i32 0
  %ACTUAL_BIRD_SIZE11 = load float, ptr %2, align 4
  %52 = load float, ptr %2, align 4
  %53 = fmul float %52, 1.000000e+00
  store float %53, ptr %51, align 4
  %54 = getelementptr inbounds %Position.4, ptr %50, i32 0, i32 1
  %ACTUAL_BIRD_SIZE12 = load float, ptr %2, align 4
  %55 = load float, ptr %2, align 4
  %56 = fmul float %55, 1.000000e+00
  store float %56, ptr %54, align 4
  %57 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 5
  %58 = getelementptr inbounds %Position.4, ptr %57, i32 0, i32 0
  %ACTUAL_BIRD_SIZE13 = load float, ptr %2, align 4
  %59 = load float, ptr %2, align 4
  %60 = fmul float %59, 2.000000e+00
  store float %60, ptr %58, align 4
  %61 = getelementptr inbounds %Position.4, ptr %57, i32 0, i32 1
  %ACTUAL_BIRD_SIZE14 = load float, ptr %2, align 4
  %62 = load float, ptr %2, align 4
  %63 = fmul float %62, 1.000000e+00
  store float %63, ptr %61, align 4
  %64 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 6
  %65 = getelementptr inbounds %Position.4, ptr %64, i32 0, i32 0
  store float 0.000000e+00, ptr %65, align 4
  %66 = getelementptr inbounds %Position.4, ptr %64, i32 0, i32 1
  %ACTUAL_BIRD_SIZE15 = load float, ptr %2, align 4
  %67 = load float, ptr %2, align 4
  %68 = fmul float %67, 2.000000e+00
  store float %68, ptr %66, align 4
  %69 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 7
  %70 = getelementptr inbounds %Position.4, ptr %69, i32 0, i32 0
  %ACTUAL_BIRD_SIZE16 = load float, ptr %2, align 4
  %71 = load float, ptr %2, align 4
  %72 = fmul float %71, 1.000000e+00
  store float %72, ptr %70, align 4
  %73 = getelementptr inbounds %Position.4, ptr %69, i32 0, i32 1
  %ACTUAL_BIRD_SIZE17 = load float, ptr %2, align 4
  %74 = load float, ptr %2, align 4
  %75 = fmul float %74, 2.000000e+00
  store float %75, ptr %73, align 4
  %76 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 8
  %77 = getelementptr inbounds %Position.4, ptr %76, i32 0, i32 0
  %ACTUAL_BIRD_SIZE18 = load float, ptr %2, align 4
  %78 = load float, ptr %2, align 4
  %79 = fmul float %78, 2.000000e+00
  store float %79, ptr %77, align 4
  %80 = getelementptr inbounds %Position.4, ptr %76, i32 0, i32 1
  %ACTUAL_BIRD_SIZE19 = load float, ptr %2, align 4
  %81 = load float, ptr %2, align 4
  %82 = fmul float %81, 2.000000e+00
  store float %82, ptr %80, align 4
  %83 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @Bird.setTexture(ptr %0, ptr %1) !rt !26 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  %birdTexture = alloca %Texture.0, align 8
  %13 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %13, ptr %birdTexture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %14 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %15 = load %Texture.0, ptr %birdTexture, align 4
  store %Texture.0 %15, ptr %14, align 4
  %16 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Bird.getTexturePath(ptr %0, ptr %1) !rt !27 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 7
  %birdTexturePath = load ptr, ptr %13, align 8
  %14 = load ptr, ptr %13, align 8
  store ptr %14, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.update(ptr %0, ptr %1) !rt !28 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  %frameTime = alloca float, align 4
  %13 = load float, ptr %0, align 4
  store float %13, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %afterIfElse, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %birdTimmer = load double, ptr %5, align 8
  %birdTimmer3 = load double, ptr %5, align 8
  %14 = load double, ptr %5, align 8
  %frameTime4 = load float, ptr %frameTime, align 4
  %15 = load float, ptr %frameTime, align 4
  %16 = fpext float %15 to double
  %17 = fsub double %14, %16
  store double %17, ptr %5, align 8
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %20 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %birdTimmer5 = load double, ptr %5, align 8
  %22 = load double, ptr %5, align 8
  %23 = fcmp olt double %22, 0.000000e+00
  br i1 %23, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse20, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %birdTimmer15 = load double, ptr %5, align 8
  %BIRD_TIMMER = load double, ptr %4, align 8
  %26 = load double, ptr %4, align 8
  store double %26, ptr %5, align 8
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  %29 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock9, label %afterNestedBlock6

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %birdSpriteIndex = load i32, ptr %7, align 4
  %birdSpriteIndex16 = load i32, ptr %7, align 4
  %31 = load i32, ptr %7, align 4
  %32 = add i32 %31, 1
  store i32 %32, ptr %7, align 4
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock10, label %afterNestedBlock6

checkContinueBlock10:                             ; preds = %nestedBlock9
  %35 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock11, label %afterNestedBlock6

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %birdSpriteIndex17 = load i32, ptr %7, align 4
  %37 = load i32, ptr %7, align 4
  %BIRD_SPRITE_SIZE = load i32, ptr %6, align 4
  %38 = load i32, ptr %6, align 4
  %39 = icmp sge i32 %37, %38
  br i1 %39, label %then18, label %else19

checkContinueBlock12:                             ; preds = %afterIfElse20
  %40 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %nestedBlock13, label %afterNestedBlock6

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %42 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y = load float, ptr %42, align 4
  %43 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y25 = load float, ptr %43, align 4
  %44 = load float, ptr %43, align 4
  %frameTime26 = load float, ptr %frameTime, align 4
  %45 = load float, ptr %frameTime, align 4
  %46 = fmul float %45, -1.490000e+02
  %47 = fadd float %44, %46
  store float %47, ptr %42, align 4
  %48 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock14, label %afterNestedBlock6

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock6

then18:                                           ; preds = %nestedBlock11
  br label %nestedBlock22

else19:                                           ; preds = %nestedBlock11
  br label %afterIfElse20

afterIfElse20:                                    ; preds = %else19, %afterNestedBlock21
  %50 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %checkContinueBlock12, label %afterNestedBlock6

afterNestedBlock21:                               ; preds = %checkContinueBlock23, %nestedBlock22
  br label %afterIfElse20

nestedBlock22:                                    ; preds = %then18
  %birdSpriteIndex24 = load i32, ptr %7, align 4
  store i32 0, ptr %7, align 4
  %52 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock23, label %afterNestedBlock21

checkContinueBlock23:                             ; preds = %nestedBlock22
  br label %afterNestedBlock21
}

define void @Bird.isTextureLoaded(ptr %0, ptr %1) !rt !29 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %14 = getelementptr inbounds %Texture.0, ptr %13, i32 0, i32 0
  %id = load i32, ptr %14, align 4
  %15 = load i32, ptr %14, align 4
  %16 = icmp ne i32 %15, 0
  store i1 %16, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getSource(ptr %0, ptr %1) !rt !30 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr [4 x float], ptr %0, i32 0, i32 0
  %birdSpriteIndex = load i32, ptr %7, align 4
  %birdSpritePosition = load [9 x %Position.4], ptr %11, align 4
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
  call void @raise_exception(ptr @3)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %16 = getelementptr [9 x %Position.4], ptr %11, i32 0, i32 %birdSpriteIndex
  %17 = getelementptr inbounds %Position.4, ptr %16, i32 0, i32 0
  %x = load float, ptr %17, align 4
  %18 = load float, ptr %17, align 4
  store float %18, ptr %13, align 4
  %19 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %birdSpriteIndex1 = load i32, ptr %7, align 4
  %birdSpritePosition2 = load [9 x %Position.4], ptr %11, align 4
  %"GlobalIndexExpr::isLessThan6" = icmp slt i32 %birdSpriteIndex1, 9
  %"GlobalIndexExpr::isGreaterThan7" = icmp sge i32 %birdSpriteIndex1, 0
  %"GlobalIndexExpr::isWithinBounds8" = and i1 %"GlobalIndexExpr::isLessThan6", %"GlobalIndexExpr::isGreaterThan7"
  br i1 %"GlobalIndexExpr::isWithinBounds8", label %"GlobalIndexExpr::then3", label %"GlobalIndexExpr::else4"

"GlobalIndexExpr::then3":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge5"

"GlobalIndexExpr::else4":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @4)
  br label %"GlobalIndexExpr::merge5"

"GlobalIndexExpr::merge5":                        ; preds = %"GlobalIndexExpr::else4", %"GlobalIndexExpr::then3"
  %20 = getelementptr [9 x %Position.4], ptr %11, i32 0, i32 %birdSpriteIndex1
  %21 = getelementptr inbounds %Position.4, ptr %20, i32 0, i32 1
  %y = load float, ptr %21, align 4
  %22 = load float, ptr %21, align 4
  store float %22, ptr %19, align 4
  %23 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %ACTUAL_BIRD_SIZE = load float, ptr %2, align 4
  %24 = load float, ptr %2, align 4
  store float %24, ptr %23, align 4
  %25 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %ACTUAL_BIRD_SIZE9 = load float, ptr %2, align 4
  %26 = load float, ptr %2, align 4
  store float %26, ptr %25, align 4
  ret void
}

define void @Bird.getDistination(ptr %0, ptr %1) !rt !31 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
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
  %birdSize = load float, ptr %3, align 4
  %17 = load float, ptr %3, align 4
  %18 = fdiv float %17, 2.000000e+00
  %19 = fptrunc double %16 to float
  %20 = fsub float %19, %18
  store float %20, ptr %13, align 4
  %21 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %22 = load i32, ptr @screenHeight, align 4
  %23 = sitofp i32 %22 to double
  %24 = fdiv double %23, 2.000000e+00
  %birdSize1 = load float, ptr %3, align 4
  %25 = load float, ptr %3, align 4
  %26 = fdiv float %25, 2.000000e+00
  %27 = fptrunc double %24 to float
  %28 = fsub float %27, %26
  store float %28, ptr %21, align 4
  %29 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %birdSize2 = load float, ptr %3, align 4
  %30 = load float, ptr %3, align 4
  store float %30, ptr %29, align 4
  %31 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %birdSize3 = load float, ptr %3, align 4
  %32 = load float, ptr %3, align 4
  store float %32, ptr %31, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getOrigin(ptr %0, ptr %1) !rt !32 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr [2 x float], ptr %0, i32 0, i32 0
  %14 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  %15 = getelementptr inbounds %Position.4, ptr %14, i32 0, i32 0
  %x = load float, ptr %15, align 4
  %16 = load float, ptr %15, align 4
  store float %16, ptr %13, align 4
  %17 = getelementptr [2 x float], ptr %0, i32 0, i32 1
  %18 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  %19 = getelementptr inbounds %Position.4, ptr %18, i32 0, i32 1
  %y = load float, ptr %19, align 4
  %20 = load float, ptr %19, align 4
  store float %20, ptr %17, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getRotation(ptr %0, ptr %1) !rt !33 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
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

define void @Bird.getTexture(ptr %0, ptr %1) !rt !34 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %13 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %14 = load %Texture.0, ptr %13, align 4
  store %Texture.0 %14, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.updateY(ptr %0, ptr %1) !rt !35 {
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
  %12 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 11
  %frameTime = alloca float, align 4
  %13 = load float, ptr %0, align 4
  store float %13, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %14 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y = load float, ptr %14, align 4
  %15 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
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

define void @Cloud.init1(ptr %0, ptr %1) !rt !36 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %texturePath = alloca ptr, align 8
  %5 = load ptr, ptr %0, align 8
  store ptr %5, ptr %texturePath, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %texturePath3 = load ptr, ptr %6, align 8
  %texturePath4 = load ptr, ptr %texturePath, align 8
  %7 = load ptr, ptr %texturePath, align 8
  store ptr %7, ptr %6, align 8
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %12 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 0
  %13 = getelementptr inbounds %AttributeType.5, ptr %12, i32 0, i32 0
  %14 = getelementptr [4 x float], ptr %13, i32 0, i32 0
  store float 0.000000e+00, ptr %14, align 4
  %15 = getelementptr [4 x float], ptr %13, i32 0, i32 1
  store float 0.000000e+00, ptr %15, align 4
  %16 = getelementptr [4 x float], ptr %13, i32 0, i32 2
  store float 2.500000e+02, ptr %16, align 4
  %17 = getelementptr [4 x float], ptr %13, i32 0, i32 3
  store float 1.660000e+02, ptr %17, align 4
  %18 = getelementptr inbounds %AttributeType.5, ptr %12, i32 0, i32 1
  %19 = getelementptr [4 x float], ptr %18, i32 0, i32 0
  store float 0.000000e+00, ptr %19, align 4
  %20 = getelementptr [4 x float], ptr %18, i32 0, i32 1
  store float 0.000000e+00, ptr %20, align 4
  %21 = getelementptr [4 x float], ptr %18, i32 0, i32 2
  store float 0x4062D34700000000, ptr %21, align 4
  %22 = getelementptr [4 x float], ptr %18, i32 0, i32 3
  store float 1.000000e+02, ptr %22, align 4
  %23 = getelementptr inbounds %AttributeType.5, ptr %12, i32 0, i32 2
  %24 = getelementptr [2 x float], ptr %23, i32 0, i32 0
  %rtPtr = alloca i32, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %25 = load i32, ptr @screenWidth, align 4
  %26 = mul i32 -1, %25
  %27 = alloca i32, align 4
  store i32 %26, ptr %27, align 4
  %28 = alloca i32, align 4
  store i32 0, ptr %28, align 4
  call void @getRandomNumber(ptr %rtPtr, ptr %27, ptr %28)
  %29 = load i32, ptr %rtPtr, align 4
  %30 = sitofp i32 %29 to float
  store float %30, ptr %24, align 4
  %31 = getelementptr [2 x float], ptr %23, i32 0, i32 1
  %rtPtr5 = alloca i32, align 4
  %32 = alloca i32, align 4
  store i32 0, ptr %32, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %33 = load i32, ptr @screenHeight, align 4
  %34 = sitofp i32 %33 to double
  %35 = fdiv double %34, 3.000000e+00
  %36 = fptosi double %35 to i32
  %37 = alloca i32, align 4
  store i32 %36, ptr %37, align 4
  call void @getRandomNumber(ptr %rtPtr5, ptr %32, ptr %37)
  %38 = load i32, ptr %rtPtr5, align 4
  %39 = sitofp i32 %38 to float
  %40 = fmul float -1.000000e+00, %39
  store float %40, ptr %31, align 4
  %41 = getelementptr inbounds %AttributeType.5, ptr %12, i32 0, i32 3
  store float 0.000000e+00, ptr %41, align 4
  %42 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 1
  %43 = getelementptr inbounds %AttributeType.5, ptr %42, i32 0, i32 0
  %44 = getelementptr [4 x float], ptr %43, i32 0, i32 0
  store float 2.500000e+02, ptr %44, align 4
  %45 = getelementptr [4 x float], ptr %43, i32 0, i32 1
  store float 0.000000e+00, ptr %45, align 4
  %46 = getelementptr [4 x float], ptr %43, i32 0, i32 2
  store float 2.500000e+02, ptr %46, align 4
  %47 = getelementptr [4 x float], ptr %43, i32 0, i32 3
  store float 1.660000e+02, ptr %47, align 4
  %48 = getelementptr inbounds %AttributeType.5, ptr %42, i32 0, i32 1
  %49 = getelementptr [4 x float], ptr %48, i32 0, i32 0
  store float 0.000000e+00, ptr %49, align 4
  %50 = getelementptr [4 x float], ptr %48, i32 0, i32 1
  store float 0.000000e+00, ptr %50, align 4
  %51 = getelementptr [4 x float], ptr %48, i32 0, i32 2
  store float 0x4062D34700000000, ptr %51, align 4
  %52 = getelementptr [4 x float], ptr %48, i32 0, i32 3
  store float 1.000000e+02, ptr %52, align 4
  %53 = getelementptr inbounds %AttributeType.5, ptr %42, i32 0, i32 2
  %54 = getelementptr [2 x float], ptr %53, i32 0, i32 0
  %rtPtr6 = alloca i32, align 4
  %screenWidth7 = load i32, ptr @screenWidth, align 4
  %55 = load i32, ptr @screenWidth, align 4
  %56 = mul i32 -1, %55
  %57 = alloca i32, align 4
  store i32 %56, ptr %57, align 4
  %58 = alloca i32, align 4
  store i32 0, ptr %58, align 4
  call void @getRandomNumber(ptr %rtPtr6, ptr %57, ptr %58)
  %59 = load i32, ptr %rtPtr6, align 4
  %60 = sitofp i32 %59 to float
  store float %60, ptr %54, align 4
  %61 = getelementptr [2 x float], ptr %53, i32 0, i32 1
  %rtPtr8 = alloca i32, align 4
  %62 = alloca i32, align 4
  store i32 0, ptr %62, align 4
  %screenHeight9 = load i32, ptr @screenHeight, align 4
  %63 = load i32, ptr @screenHeight, align 4
  %64 = sitofp i32 %63 to double
  %65 = fdiv double %64, 3.000000e+00
  %66 = fptosi double %65 to i32
  %67 = alloca i32, align 4
  store i32 %66, ptr %67, align 4
  call void @getRandomNumber(ptr %rtPtr8, ptr %62, ptr %67)
  %68 = load i32, ptr %rtPtr8, align 4
  %69 = sitofp i32 %68 to float
  %70 = fmul float -1.000000e+00, %69
  store float %70, ptr %61, align 4
  %71 = getelementptr inbounds %AttributeType.5, ptr %42, i32 0, i32 3
  store float 0.000000e+00, ptr %71, align 4
  %72 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 2
  %73 = getelementptr inbounds %AttributeType.5, ptr %72, i32 0, i32 0
  %74 = getelementptr [4 x float], ptr %73, i32 0, i32 0
  store float 0.000000e+00, ptr %74, align 4
  %75 = getelementptr [4 x float], ptr %73, i32 0, i32 1
  store float 1.660000e+02, ptr %75, align 4
  %76 = getelementptr [4 x float], ptr %73, i32 0, i32 2
  store float 5.000000e+02, ptr %76, align 4
  %77 = getelementptr [4 x float], ptr %73, i32 0, i32 3
  store float 1.660000e+02, ptr %77, align 4
  %78 = getelementptr inbounds %AttributeType.5, ptr %72, i32 0, i32 1
  %79 = getelementptr [4 x float], ptr %78, i32 0, i32 0
  store float 0.000000e+00, ptr %79, align 4
  %80 = getelementptr [4 x float], ptr %78, i32 0, i32 1
  store float 0.000000e+00, ptr %80, align 4
  %81 = getelementptr [4 x float], ptr %78, i32 0, i32 2
  store float 0x4062D34700000000, ptr %81, align 4
  %82 = getelementptr [4 x float], ptr %78, i32 0, i32 3
  store float 1.000000e+02, ptr %82, align 4
  %83 = getelementptr inbounds %AttributeType.5, ptr %72, i32 0, i32 2
  %84 = getelementptr [2 x float], ptr %83, i32 0, i32 0
  %rtPtr10 = alloca i32, align 4
  %screenWidth11 = load i32, ptr @screenWidth, align 4
  %85 = load i32, ptr @screenWidth, align 4
  %86 = mul i32 -1, %85
  %87 = alloca i32, align 4
  store i32 %86, ptr %87, align 4
  %88 = alloca i32, align 4
  store i32 0, ptr %88, align 4
  call void @getRandomNumber(ptr %rtPtr10, ptr %87, ptr %88)
  %89 = load i32, ptr %rtPtr10, align 4
  %90 = sitofp i32 %89 to float
  store float %90, ptr %84, align 4
  %91 = getelementptr [2 x float], ptr %83, i32 0, i32 1
  %rtPtr12 = alloca i32, align 4
  %92 = alloca i32, align 4
  store i32 0, ptr %92, align 4
  %screenHeight13 = load i32, ptr @screenHeight, align 4
  %93 = load i32, ptr @screenHeight, align 4
  %94 = sitofp i32 %93 to double
  %95 = fdiv double %94, 3.000000e+00
  %96 = fptosi double %95 to i32
  %97 = alloca i32, align 4
  store i32 %96, ptr %97, align 4
  call void @getRandomNumber(ptr %rtPtr12, ptr %92, ptr %97)
  %98 = load i32, ptr %rtPtr12, align 4
  %99 = sitofp i32 %98 to float
  %100 = fmul float -1.000000e+00, %99
  store float %100, ptr %91, align 4
  %101 = getelementptr inbounds %AttributeType.5, ptr %72, i32 0, i32 3
  store float 0.000000e+00, ptr %101, align 4
  %102 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 3
  %103 = getelementptr inbounds %AttributeType.5, ptr %102, i32 0, i32 0
  %104 = getelementptr [4 x float], ptr %103, i32 0, i32 0
  store float 0.000000e+00, ptr %104, align 4
  %105 = getelementptr [4 x float], ptr %103, i32 0, i32 1
  store float 3.320000e+02, ptr %105, align 4
  %106 = getelementptr [4 x float], ptr %103, i32 0, i32 2
  store float 2.500000e+02, ptr %106, align 4
  %107 = getelementptr [4 x float], ptr %103, i32 0, i32 3
  store float 1.660000e+02, ptr %107, align 4
  %108 = getelementptr inbounds %AttributeType.5, ptr %102, i32 0, i32 1
  %109 = getelementptr [4 x float], ptr %108, i32 0, i32 0
  store float 0.000000e+00, ptr %109, align 4
  %110 = getelementptr [4 x float], ptr %108, i32 0, i32 1
  store float 0.000000e+00, ptr %110, align 4
  %111 = getelementptr [4 x float], ptr %108, i32 0, i32 2
  store float 0x4062D34700000000, ptr %111, align 4
  %112 = getelementptr [4 x float], ptr %108, i32 0, i32 3
  store float 1.000000e+02, ptr %112, align 4
  %113 = getelementptr inbounds %AttributeType.5, ptr %102, i32 0, i32 2
  %114 = getelementptr [2 x float], ptr %113, i32 0, i32 0
  %rtPtr14 = alloca i32, align 4
  %screenWidth15 = load i32, ptr @screenWidth, align 4
  %115 = load i32, ptr @screenWidth, align 4
  %116 = mul i32 -1, %115
  %117 = alloca i32, align 4
  store i32 %116, ptr %117, align 4
  %118 = alloca i32, align 4
  store i32 0, ptr %118, align 4
  call void @getRandomNumber(ptr %rtPtr14, ptr %117, ptr %118)
  %119 = load i32, ptr %rtPtr14, align 4
  %120 = sitofp i32 %119 to float
  store float %120, ptr %114, align 4
  %121 = getelementptr [2 x float], ptr %113, i32 0, i32 1
  %rtPtr16 = alloca i32, align 4
  %122 = alloca i32, align 4
  store i32 0, ptr %122, align 4
  %screenHeight17 = load i32, ptr @screenHeight, align 4
  %123 = load i32, ptr @screenHeight, align 4
  %124 = sitofp i32 %123 to double
  %125 = fdiv double %124, 3.000000e+00
  %126 = fptosi double %125 to i32
  %127 = alloca i32, align 4
  store i32 %126, ptr %127, align 4
  call void @getRandomNumber(ptr %rtPtr16, ptr %122, ptr %127)
  %128 = load i32, ptr %rtPtr16, align 4
  %129 = sitofp i32 %128 to float
  %130 = fmul float -1.000000e+00, %129
  store float %130, ptr %121, align 4
  %131 = getelementptr inbounds %AttributeType.5, ptr %102, i32 0, i32 3
  store float 0.000000e+00, ptr %131, align 4
  %132 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 4
  %133 = getelementptr inbounds %AttributeType.5, ptr %132, i32 0, i32 0
  %134 = getelementptr [4 x float], ptr %133, i32 0, i32 0
  store float 2.500000e+02, ptr %134, align 4
  %135 = getelementptr [4 x float], ptr %133, i32 0, i32 1
  store float 3.320000e+02, ptr %135, align 4
  %136 = getelementptr [4 x float], ptr %133, i32 0, i32 2
  store float 2.500000e+02, ptr %136, align 4
  %137 = getelementptr [4 x float], ptr %133, i32 0, i32 3
  store float 1.660000e+02, ptr %137, align 4
  %138 = getelementptr inbounds %AttributeType.5, ptr %132, i32 0, i32 1
  %139 = getelementptr [4 x float], ptr %138, i32 0, i32 0
  store float 0.000000e+00, ptr %139, align 4
  %140 = getelementptr [4 x float], ptr %138, i32 0, i32 1
  store float 0.000000e+00, ptr %140, align 4
  %141 = getelementptr [4 x float], ptr %138, i32 0, i32 2
  store float 0x4062D34700000000, ptr %141, align 4
  %142 = getelementptr [4 x float], ptr %138, i32 0, i32 3
  store float 1.000000e+02, ptr %142, align 4
  %143 = getelementptr inbounds %AttributeType.5, ptr %132, i32 0, i32 2
  %144 = getelementptr [2 x float], ptr %143, i32 0, i32 0
  %rtPtr18 = alloca i32, align 4
  %screenWidth19 = load i32, ptr @screenWidth, align 4
  %145 = load i32, ptr @screenWidth, align 4
  %146 = mul i32 -1, %145
  %147 = alloca i32, align 4
  store i32 %146, ptr %147, align 4
  %148 = alloca i32, align 4
  store i32 0, ptr %148, align 4
  call void @getRandomNumber(ptr %rtPtr18, ptr %147, ptr %148)
  %149 = load i32, ptr %rtPtr18, align 4
  %150 = sitofp i32 %149 to float
  store float %150, ptr %144, align 4
  %151 = getelementptr [2 x float], ptr %143, i32 0, i32 1
  %rtPtr20 = alloca i32, align 4
  %152 = alloca i32, align 4
  store i32 0, ptr %152, align 4
  %screenHeight21 = load i32, ptr @screenHeight, align 4
  %153 = load i32, ptr @screenHeight, align 4
  %154 = sitofp i32 %153 to double
  %155 = fdiv double %154, 3.000000e+00
  %156 = fptosi double %155 to i32
  %157 = alloca i32, align 4
  store i32 %156, ptr %157, align 4
  call void @getRandomNumber(ptr %rtPtr20, ptr %152, ptr %157)
  %158 = load i32, ptr %rtPtr20, align 4
  %159 = sitofp i32 %158 to float
  %160 = fmul float -1.000000e+00, %159
  store float %160, ptr %151, align 4
  %161 = getelementptr inbounds %AttributeType.5, ptr %132, i32 0, i32 3
  store float 0.000000e+00, ptr %161, align 4
  %162 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %163 = icmp eq i32 %162, 0
  br i1 %163, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @Cloud.setTexture(ptr %0, ptr %1) !rt !37 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %cloudTexture = alloca %Texture.0, align 8
  %5 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %5, ptr %cloudTexture, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %7 = load %Texture.0, ptr %cloudTexture, align 4
  store %Texture.0 %7, ptr %6, align 4
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Cloud.getTexture(ptr %0, ptr %1) !rt !38 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %6 = load %Texture.0, ptr %5, align 4
  store %Texture.0 %6, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.getTexturePath(ptr %0, ptr %1) !rt !39 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %texturePath = load ptr, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  store ptr %6, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.update(ptr %0, ptr %1) !rt !40 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %frameTime = alloca float, align 4
  %5 = load float, ptr %0, align 4
  store float %5, ptr %frameTime, align 4
  %i = alloca %DynamicType, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block58
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %6, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock:                               ; preds = %end_block58
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
  br i1 %10, label %end_block58, label %decrement_block57

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

afterNestedBlock1:                                ; preds = %checkContinueBlock5, %afterIfElse, %checkContinueBlock3, %"GlobalIndexExpr::merge18"
  %20 = add i32 %16, 1
  store i32 %20, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock2:                                     ; preds = %"ForLoop::loopBody"
  %21 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %22 = load i32, ptr %21, align 4
  %clouds = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %22, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %22, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock3:                              ; preds = %"GlobalIndexExpr::merge18"
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock4, label %afterNestedBlock1

nestedBlock4:                                     ; preds = %checkContinueBlock3
  %25 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %26 = load i32, ptr %25, align 4
  %clouds20 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan24" = icmp slt i32 %26, 5
  %"GlobalIndexExpr::isGreaterThan25" = icmp sge i32 %26, 0
  %"GlobalIndexExpr::isWithinBounds26" = and i1 %"GlobalIndexExpr::isLessThan24", %"GlobalIndexExpr::isGreaterThan25"
  br i1 %"GlobalIndexExpr::isWithinBounds26", label %"GlobalIndexExpr::then21", label %"GlobalIndexExpr::else22"

checkContinueBlock5:                              ; preds = %afterIfElse
  br label %afterNestedBlock1

"GlobalIndexExpr::then":                          ; preds = %nestedBlock2
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock2
  call void @raise_exception(ptr @5)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %27 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %22
  %28 = getelementptr inbounds %AttributeType.5, ptr %27, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then6", label %"GlobalIndexExpr::else7"

"GlobalIndexExpr::then6":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge8"

"GlobalIndexExpr::else7":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @6)
  br label %"GlobalIndexExpr::merge8"

"GlobalIndexExpr::merge8":                        ; preds = %"GlobalIndexExpr::else7", %"GlobalIndexExpr::then6"
  %29 = getelementptr [2 x float], ptr %28, i32 0, i32 0
  %30 = load float, ptr %29, align 4
  %31 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %32 = load i32, ptr %31, align 4
  %clouds9 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan13" = icmp slt i32 %32, 5
  %"GlobalIndexExpr::isGreaterThan14" = icmp sge i32 %32, 0
  %"GlobalIndexExpr::isWithinBounds15" = and i1 %"GlobalIndexExpr::isLessThan13", %"GlobalIndexExpr::isGreaterThan14"
  br i1 %"GlobalIndexExpr::isWithinBounds15", label %"GlobalIndexExpr::then10", label %"GlobalIndexExpr::else11"

"GlobalIndexExpr::then10":                        ; preds = %"GlobalIndexExpr::merge8"
  br label %"GlobalIndexExpr::merge12"

"GlobalIndexExpr::else11":                        ; preds = %"GlobalIndexExpr::merge8"
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge12"

"GlobalIndexExpr::merge12":                       ; preds = %"GlobalIndexExpr::else11", %"GlobalIndexExpr::then10"
  %33 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %32
  %34 = getelementptr inbounds %AttributeType.5, ptr %33, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then16", label %"GlobalIndexExpr::else17"

"GlobalIndexExpr::then16":                        ; preds = %"GlobalIndexExpr::merge12"
  br label %"GlobalIndexExpr::merge18"

"GlobalIndexExpr::else17":                        ; preds = %"GlobalIndexExpr::merge12"
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge18"

"GlobalIndexExpr::merge18":                       ; preds = %"GlobalIndexExpr::else17", %"GlobalIndexExpr::then16"
  %35 = getelementptr [2 x float], ptr %34, i32 0, i32 0
  %36 = load float, ptr %35, align 4
  %frameTime19 = load float, ptr %frameTime, align 4
  %37 = load float, ptr %frameTime, align 4
  %38 = fmul float %37, 1.000000e+01
  %39 = fadd float %36, %38
  store float %39, ptr %29, align 4
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock3, label %afterNestedBlock1

"GlobalIndexExpr::then21":                        ; preds = %nestedBlock4
  br label %"GlobalIndexExpr::merge23"

"GlobalIndexExpr::else22":                        ; preds = %nestedBlock4
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge23"

"GlobalIndexExpr::merge23":                       ; preds = %"GlobalIndexExpr::else22", %"GlobalIndexExpr::then21"
  %42 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %26
  %43 = getelementptr inbounds %AttributeType.5, ptr %42, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then27", label %"GlobalIndexExpr::else28"

"GlobalIndexExpr::then27":                        ; preds = %"GlobalIndexExpr::merge23"
  br label %"GlobalIndexExpr::merge29"

"GlobalIndexExpr::else28":                        ; preds = %"GlobalIndexExpr::merge23"
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge29"

"GlobalIndexExpr::merge29":                       ; preds = %"GlobalIndexExpr::else28", %"GlobalIndexExpr::then27"
  %44 = getelementptr [2 x float], ptr %43, i32 0, i32 0
  %45 = load float, ptr %44, align 4
  %46 = fcmp ogt float %45, 2.500000e+02
  br i1 %46, label %then, label %else

then:                                             ; preds = %"GlobalIndexExpr::merge29"
  br label %nestedBlock31

else:                                             ; preds = %"GlobalIndexExpr::merge29"
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock30
  %47 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %checkContinueBlock5, label %afterNestedBlock1

afterNestedBlock30:                               ; preds = %checkContinueBlock34, %"GlobalIndexExpr::merge55", %checkContinueBlock32, %"GlobalIndexExpr::merge44"
  br label %afterIfElse

nestedBlock31:                                    ; preds = %then
  %49 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %50 = load i32, ptr %49, align 4
  %clouds35 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan39" = icmp slt i32 %50, 5
  %"GlobalIndexExpr::isGreaterThan40" = icmp sge i32 %50, 0
  %"GlobalIndexExpr::isWithinBounds41" = and i1 %"GlobalIndexExpr::isLessThan39", %"GlobalIndexExpr::isGreaterThan40"
  br i1 %"GlobalIndexExpr::isWithinBounds41", label %"GlobalIndexExpr::then36", label %"GlobalIndexExpr::else37"

checkContinueBlock32:                             ; preds = %"GlobalIndexExpr::merge44"
  %51 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %nestedBlock33, label %afterNestedBlock30

nestedBlock33:                                    ; preds = %checkContinueBlock32
  %53 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %54 = load i32, ptr %53, align 4
  %clouds46 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan50" = icmp slt i32 %54, 5
  %"GlobalIndexExpr::isGreaterThan51" = icmp sge i32 %54, 0
  %"GlobalIndexExpr::isWithinBounds52" = and i1 %"GlobalIndexExpr::isLessThan50", %"GlobalIndexExpr::isGreaterThan51"
  br i1 %"GlobalIndexExpr::isWithinBounds52", label %"GlobalIndexExpr::then47", label %"GlobalIndexExpr::else48"

checkContinueBlock34:                             ; preds = %"GlobalIndexExpr::merge55"
  br label %afterNestedBlock30

"GlobalIndexExpr::then36":                        ; preds = %nestedBlock31
  br label %"GlobalIndexExpr::merge38"

"GlobalIndexExpr::else37":                        ; preds = %nestedBlock31
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge38"

"GlobalIndexExpr::merge38":                       ; preds = %"GlobalIndexExpr::else37", %"GlobalIndexExpr::then36"
  %55 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %50
  %56 = getelementptr inbounds %AttributeType.5, ptr %55, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then42", label %"GlobalIndexExpr::else43"

"GlobalIndexExpr::then42":                        ; preds = %"GlobalIndexExpr::merge38"
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::else43":                        ; preds = %"GlobalIndexExpr::merge38"
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::merge44":                       ; preds = %"GlobalIndexExpr::else43", %"GlobalIndexExpr::then42"
  %57 = getelementptr [2 x float], ptr %56, i32 0, i32 0
  %58 = load float, ptr %57, align 4
  %rtPtr = alloca i32, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %59 = load i32, ptr @screenWidth, align 4
  %60 = mul i32 -2, %59
  %61 = alloca i32, align 4
  store i32 %60, ptr %61, align 4
  %screenWidth45 = load i32, ptr @screenWidth, align 4
  %62 = load i32, ptr @screenWidth, align 4
  %63 = mul i32 -1, %62
  %64 = alloca i32, align 4
  store i32 %63, ptr %64, align 4
  call void @getRandomNumber(ptr %rtPtr, ptr %61, ptr %64)
  %65 = load i32, ptr %rtPtr, align 4
  %66 = sitofp i32 %65 to float
  store float %66, ptr %57, align 4
  %67 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %checkContinueBlock32, label %afterNestedBlock30

"GlobalIndexExpr::then47":                        ; preds = %nestedBlock33
  br label %"GlobalIndexExpr::merge49"

"GlobalIndexExpr::else48":                        ; preds = %nestedBlock33
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge49"

"GlobalIndexExpr::merge49":                       ; preds = %"GlobalIndexExpr::else48", %"GlobalIndexExpr::then47"
  %69 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %54
  %70 = getelementptr inbounds %AttributeType.5, ptr %69, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then53", label %"GlobalIndexExpr::else54"

"GlobalIndexExpr::then53":                        ; preds = %"GlobalIndexExpr::merge49"
  br label %"GlobalIndexExpr::merge55"

"GlobalIndexExpr::else54":                        ; preds = %"GlobalIndexExpr::merge49"
  call void @raise_exception(ptr @14)
  br label %"GlobalIndexExpr::merge55"

"GlobalIndexExpr::merge55":                       ; preds = %"GlobalIndexExpr::else54", %"GlobalIndexExpr::then53"
  %71 = getelementptr [2 x float], ptr %70, i32 0, i32 1
  %72 = load float, ptr %71, align 4
  %rtPtr56 = alloca i32, align 4
  %73 = alloca i32, align 4
  store i32 0, ptr %73, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %74 = load i32, ptr @screenHeight, align 4
  %75 = sitofp i32 %74 to double
  %76 = fdiv double %75, 3.000000e+00
  %77 = fptosi double %76 to i32
  %78 = alloca i32, align 4
  store i32 %77, ptr %78, align 4
  call void @getRandomNumber(ptr %rtPtr56, ptr %73, ptr %78)
  %79 = load i32, ptr %rtPtr56, align 4
  %80 = sitofp i32 %79 to float
  %81 = fmul float -1.000000e+00, %80
  store float %81, ptr %71, align 4
  %82 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %83 = icmp eq i32 %82, 0
  br i1 %83, label %checkContinueBlock34, label %afterNestedBlock30

decrement_block57:                                ; preds = %"ForLoop::afterLoop"
  %84 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %85 = sub i32 %84, 1
  store i32 %85, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block58

end_block58:                                      ; preds = %decrement_block57, %"ForLoop::afterLoop"
  %86 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.draw(ptr %0, ptr %1) !rt !41 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %fgAnim = alloca ptr, align 8
  store ptr %0, ptr %fgAnim, align 8
  %i = alloca %DynamicType, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block26
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %5, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock:                               ; preds = %end_block26
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
  br i1 %9, label %end_block26, label %decrement_block25

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

afterNestedBlock1:                                ; preds = %checkContinueBlock3, %"GlobalIndexExpr::merge21"
  %19 = add i32 %15, 1
  store i32 %19, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock2:                                     ; preds = %"ForLoop::loopBody"
  %20 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %21 = load i32, ptr %20, align 4
  %clouds = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %21, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %21, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock3:                              ; preds = %"GlobalIndexExpr::merge21"
  br label %afterNestedBlock1

"GlobalIndexExpr::then":                          ; preds = %nestedBlock2
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock2
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %22 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %21
  %23 = getelementptr inbounds %AttributeType.5, ptr %22, i32 0, i32 0
  %24 = load [4 x float], ptr %23, align 4
  %25 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %26 = load i32, ptr %25, align 4
  %clouds4 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan8" = icmp slt i32 %26, 5
  %"GlobalIndexExpr::isGreaterThan9" = icmp sge i32 %26, 0
  %"GlobalIndexExpr::isWithinBounds10" = and i1 %"GlobalIndexExpr::isLessThan8", %"GlobalIndexExpr::isGreaterThan9"
  br i1 %"GlobalIndexExpr::isWithinBounds10", label %"GlobalIndexExpr::then5", label %"GlobalIndexExpr::else6"

"GlobalIndexExpr::then5":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge7"

"GlobalIndexExpr::else6":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @16)
  br label %"GlobalIndexExpr::merge7"

"GlobalIndexExpr::merge7":                        ; preds = %"GlobalIndexExpr::else6", %"GlobalIndexExpr::then5"
  %27 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %26
  %28 = getelementptr inbounds %AttributeType.5, ptr %27, i32 0, i32 1
  %29 = load [4 x float], ptr %28, align 4
  %30 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %31 = load i32, ptr %30, align 4
  %clouds11 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan15" = icmp slt i32 %31, 5
  %"GlobalIndexExpr::isGreaterThan16" = icmp sge i32 %31, 0
  %"GlobalIndexExpr::isWithinBounds17" = and i1 %"GlobalIndexExpr::isLessThan15", %"GlobalIndexExpr::isGreaterThan16"
  br i1 %"GlobalIndexExpr::isWithinBounds17", label %"GlobalIndexExpr::then12", label %"GlobalIndexExpr::else13"

"GlobalIndexExpr::then12":                        ; preds = %"GlobalIndexExpr::merge7"
  br label %"GlobalIndexExpr::merge14"

"GlobalIndexExpr::else13":                        ; preds = %"GlobalIndexExpr::merge7"
  call void @raise_exception(ptr @17)
  br label %"GlobalIndexExpr::merge14"

"GlobalIndexExpr::merge14":                       ; preds = %"GlobalIndexExpr::else13", %"GlobalIndexExpr::then12"
  %32 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %31
  %33 = getelementptr inbounds %AttributeType.5, ptr %32, i32 0, i32 2
  %34 = load [2 x float], ptr %33, align 4
  %35 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %36 = load i32, ptr %35, align 4
  %clouds18 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan22" = icmp slt i32 %36, 5
  %"GlobalIndexExpr::isGreaterThan23" = icmp sge i32 %36, 0
  %"GlobalIndexExpr::isWithinBounds24" = and i1 %"GlobalIndexExpr::isLessThan22", %"GlobalIndexExpr::isGreaterThan23"
  br i1 %"GlobalIndexExpr::isWithinBounds24", label %"GlobalIndexExpr::then19", label %"GlobalIndexExpr::else20"

"GlobalIndexExpr::then19":                        ; preds = %"GlobalIndexExpr::merge14"
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::else20":                        ; preds = %"GlobalIndexExpr::merge14"
  call void @raise_exception(ptr @18)
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::merge21":                       ; preds = %"GlobalIndexExpr::else20", %"GlobalIndexExpr::then19"
  %37 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %36
  %38 = getelementptr inbounds %AttributeType.5, ptr %37, i32 0, i32 3
  %rotation = load float, ptr %38, align 4
  %39 = load float, ptr %38, align 4
  %40 = load ptr, ptr %fgAnim, align 8
  %41 = getelementptr inbounds %FlowWingAnim, ptr %40, i32 0, i32 5
  %42 = getelementptr inbounds %COLORS_TYPE.3, ptr %41, i32 0, i32 0
  %WHITE = load i32, ptr %42, align 4
  %43 = load i32, ptr %42, align 4
  call void @DrawTexturePro(ptr %3, [4 x float] %24, [4 x float] %29, [2 x float] %34, float %39, i32 %43)
  %44 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock3, label %afterNestedBlock1

decrement_block25:                                ; preds = %"ForLoop::afterLoop"
  %46 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %47 = sub i32 %46, 1
  store i32 %47, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block26

end_block26:                                      ; preds = %decrement_block25, %"ForLoop::afterLoop"
  %48 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock, label %afterNestedBlock
}

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()

declare !rt !42 void @drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !24 void @FlowWingAnim.textFormat.1(ptr, ptr, ptr)

declare !rt !22 void @FlowWingAnim.isKeyPressed.2(ptr, ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture.3(ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture.4(ptr, ptr, ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle.5(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow.6(ptr)

declare !rt !19 void @FlowWingAnim.traceLog.7(ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText.8(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !43 void @SetTargetFPS(i32)

declare !rt !7 void @FlowWingAnim.beginDrawing.9(ptr)

declare !rt !15 void @FlowWingAnim.drawCircle.10(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.getScreenWidth.11(ptr, ptr)

declare !rt !44 void @getRandomNumber(ptr, ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit.12(ptr)

declare !rt !13 void @FlowWingAnim.getScreenHeight.13(ptr, ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.14(ptr)

declare !rt !9 void @FlowWingAnim.endDrawing.15(ptr)

declare !rt !3 void @FlowWingAnim.getColor.16(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.17(ptr)

declare !rt !0 void @FlowWingAnim.init4.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !45 void @ClearBackground(i32)

declare !rt !46 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !12 void @FlowWingAnim.getFrameTime.19(ptr, ptr)

declare !rt !47 void @TraceLog(i32, ptr)

declare !rt !48 i32 @GetScreenWidth()

declare !rt !49 void @DrawCircle(i32, i32, float, i32)

declare !rt !50 i32 @time()

declare !rt !51 void @BeginDrawing()

declare !rt !52 i1 @IsKeyPressed(i32)

declare !rt !53 i1 @WindowShouldClose()

declare !rt !54 void @InitWindow(i32, i32, ptr)

declare !rt !55 void @EndDrawing()

declare !rt !56 void @CloseWindow()

declare !rt !17 void @FlowWingAnim.drawTexture.20(ptr, ptr, ptr, ptr, ptr)

declare !rt !57 i32 @GetScreenHeight()

declare !rt !18 void @FlowWingAnim.drawTexturePro.21(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !58 float @GetFrameTime()

declare !rt !59 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !60 double @GetTime()

declare !rt !61 void @UnloadTexture(ptr)

declare !rt !62 ptr @TextFormat(ptr)

declare !rt !23 void @FlowWingAnim.isKeyDown.22(ptr, ptr, ptr)

declare !rt !63 void @LoadTexture(ptr sret(%Texture.0) align 4, ptr)

declare !rt !64 i1 @IsKeyDown(i32)

declare !rt !6 void @FlowWingAnim.windowShouldClose.23(ptr, ptr)

declare !rt !65 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !66 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !67 void @srand(i32)

declare !rt !11 void @FlowWingAnim.getTime.24(ptr, ptr)

declare !rt !5 void @FlowWingAnim.clearBackground.25(ptr, ptr)

declare !rt !68 i32 @rand()

define void @main(ptr %0) !rt !69 {
entry:
  %fgAnim = alloca ptr, align 8
  %bird = alloca ptr, align 8
  %cloud = alloca ptr, align 8
  %backgroundTexture = alloca %Texture.0, align 8
  %1 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %groundTexture = alloca %Texture.0, align 8
  %6 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 0
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 1
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 2
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 3
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 4
  store i32 0, ptr %10, align 4
  %mountL1Texture = alloca %Texture.0, align 8
  %11 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 0
  store i32 0, ptr %11, align 4
  %12 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 1
  store i32 0, ptr %12, align 4
  %13 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 2
  store i32 0, ptr %13, align 4
  %14 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 3
  store i32 0, ptr %14, align 4
  %15 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 4
  store i32 0, ptr %15, align 4
  %mountL2Texture = alloca %Texture.0, align 8
  %16 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 0
  store i32 0, ptr %16, align 4
  %17 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 1
  store i32 0, ptr %17, align 4
  %18 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 2
  store i32 0, ptr %18, align 4
  %19 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 3
  store i32 0, ptr %19, align 4
  %20 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 4
  store i32 0, ptr %20, align 4
  %mount2L2Texture = alloca %Texture.0, align 8
  %21 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 0
  store i32 0, ptr %21, align 4
  %22 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 1
  store i32 0, ptr %22, align 4
  %23 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 2
  store i32 0, ptr %23, align 4
  %24 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 3
  store i32 0, ptr %24, align 4
  %25 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 4
  store i32 0, ptr %25, align 4
  %mount1L3Texture = alloca %Texture.0, align 8
  %26 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 0
  store i32 0, ptr %26, align 4
  %27 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 1
  store i32 0, ptr %27, align 4
  %28 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 2
  store i32 0, ptr %28, align 4
  %29 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 3
  store i32 0, ptr %29, align 4
  %30 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 4
  store i32 0, ptr %30, align 4
  %mountL1Pos1 = alloca %Position.4, align 8
  %31 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %31, align 4
  %32 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %32, align 4
  %mountL1Pos2 = alloca %Position.4, align 8
  %33 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  store float 0.000000e+00, ptr %33, align 4
  %34 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %34, align 4
  %mountL2Pos1 = alloca %Position.4, align 8
  %35 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %35, align 4
  %36 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %36, align 4
  %mount2L2Pos1 = alloca %Position.4, align 8
  %37 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %37, align 4
  %38 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %38, align 4
  %mount1L3Pos1 = alloca %Position.4, align 8
  %39 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %39, align 4
  %40 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %40, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock40, %mergeBlock411, %checkContinueBlock38, %nestedBlock37, %checkContinueBlock36, %end_block409, %checkContinueBlock34, %afterIfElse, %checkContinueBlock32, %nestedBlock31, %checkContinueBlock30, %nestedBlock29, %checkContinueBlock28, %nestedBlock27, %checkContinueBlock26, %nestedBlock25, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %nestedBlock19, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %FillExpr.exit46, %checkContinueBlock4, %FillExpr.exit, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %41 = call ptr @malloc(i64 96)
  %42 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 0
  store ptr @19, ptr %42, align 8
  %43 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 1
  store i32 0, ptr %43, align 4
  %44 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 2
  store i32 0, ptr %44, align 4
  %45 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 3
  store ptr @20, ptr %45, align 8
  %46 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 4
  store i32 0, ptr %46, align 4
  %47 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 5
  %48 = getelementptr inbounds %COLORS_TYPE.3, ptr %47, i32 0, i32 0
  store i32 0, ptr %48, align 4
  %49 = getelementptr inbounds %COLORS_TYPE.3, ptr %47, i32 0, i32 1
  store i32 0, ptr %49, align 4
  %50 = getelementptr inbounds %COLORS_TYPE.3, ptr %47, i32 0, i32 2
  store i32 0, ptr %50, align 4
  %51 = getelementptr inbounds %COLORS_TYPE.3, ptr %47, i32 0, i32 3
  store i32 0, ptr %51, align 4
  %52 = getelementptr inbounds %COLORS_TYPE.3, ptr %47, i32 0, i32 4
  store i32 0, ptr %52, align 4
  %53 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 6
  %54 = getelementptr inbounds %KEYS_TYPE.2, ptr %53, i32 0, i32 0
  store i32 0, ptr %54, align 4
  %55 = getelementptr inbounds %KEYS_TYPE.2, ptr %53, i32 0, i32 1
  store i32 0, ptr %55, align 4
  %56 = getelementptr inbounds %KEYS_TYPE.2, ptr %53, i32 0, i32 2
  store i32 0, ptr %56, align 4
  %57 = getelementptr inbounds %KEYS_TYPE.2, ptr %53, i32 0, i32 3
  store i32 0, ptr %57, align 4
  %58 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 7
  %59 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 0
  store i32 0, ptr %59, align 4
  %60 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 1
  store i32 0, ptr %60, align 4
  %61 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 2
  store i32 0, ptr %61, align 4
  %62 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 3
  store i32 0, ptr %62, align 4
  %63 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 4
  store i32 0, ptr %63, align 4
  %64 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 5
  store i32 0, ptr %64, align 4
  %65 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 6
  store i32 0, ptr %65, align 4
  %66 = getelementptr inbounds %LOG_TYPE.1, ptr %58, i32 0, i32 7
  store i32 0, ptr %66, align 4
  %67 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %67, align 8
  %68 = load ptr, ptr %67, align 8
  %69 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 23
  store ptr @FlowWingAnim.setTargetFPS, ptr %69, align 8
  %70 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 22
  store ptr @FlowWingAnim.endDrawing, ptr %70, align 8
  %71 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 21
  store ptr @FlowWingAnim.createWindow, ptr %71, align 8
  %72 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %72, align 8
  %73 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 20
  store ptr @FlowWingAnim.drawTexturePro, ptr %73, align 8
  %74 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 16
  store ptr @FlowWingAnim.drawRectangle, ptr %74, align 8
  %75 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 15
  store ptr @FlowWingAnim.beginDrawing, ptr %75, align 8
  %76 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 1
  store ptr @FlowWingAnim.traceLog, ptr %76, align 8
  %77 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 14
  store ptr @FlowWingAnim.unloadTexture, ptr %77, align 8
  %78 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 13
  store ptr @FlowWingAnim.closeWindow, ptr %78, align 8
  %79 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 17
  store ptr @FlowWingAnim.getColor, ptr %79, align 8
  %80 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 12
  store ptr @FlowWingAnim.textFormat, ptr %80, align 8
  %81 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 18
  store ptr @FlowWingAnim.windowShouldClose, ptr %81, align 8
  %82 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenWidth, ptr %82, align 8
  %83 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenHeight, ptr %83, align 8
  %84 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 11
  store ptr @FlowWingAnim.getTime, ptr %84, align 8
  %85 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 19
  store ptr @FlowWingAnim.beforeInit, ptr %85, align 8
  %86 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 10
  store ptr @FlowWingAnim.clearBackground, ptr %86, align 8
  %87 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 7
  store ptr @FlowWingAnim.drawTexture, ptr %87, align 8
  %88 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 8
  store ptr @FlowWingAnim.getFrameTime, ptr %88, align 8
  %89 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 2
  store ptr @FlowWingAnim.drawText, ptr %89, align 8
  %90 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %90, align 8
  %91 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 9
  store ptr @FlowWingAnim.loadTexture, ptr %91, align 8
  %92 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %68, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %92, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %93 = alloca ptr, align 8
  store ptr @21, ptr %93, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %93, ptr @FPS, ptr %41)
  %94 = load %FlowWingAnim, ptr %41, align 8
  store %FlowWingAnim %94, ptr %41, align 8
  store ptr %41, ptr %fgAnim, align 8
  %95 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %96 = icmp eq i32 %95, 0
  br i1 %96, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %97 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %98 = icmp eq i32 %97, 0
  br i1 %98, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %99 = load ptr, ptr %fgAnim, align 8
  %100 = getelementptr inbounds %FlowWingAnim, ptr %99, i32 0, i32 0
  %101 = load ptr, ptr %100, align 8
  %102 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %101, i32 0, i32 21
  %103 = load ptr, ptr %102, align 8
  call void %103(ptr %99)
  %104 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %105 = icmp eq i32 %104, 0
  br i1 %105, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %106 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %107 = icmp eq i32 %106, 0
  br i1 %107, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %108 = call ptr @malloc(i64 152)
  %109 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 0
  store ptr @22, ptr %109, align 8
  %110 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 1
  store float 0.000000e+00, ptr %110, align 4
  %111 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 2
  store float 0.000000e+00, ptr %111, align 4
  %112 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 3
  store double 0.000000e+00, ptr %112, align 8
  %113 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 4
  store double 0.000000e+00, ptr %113, align 8
  %114 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 5
  store i32 0, ptr %114, align 4
  %115 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 6
  store i32 0, ptr %115, align 4
  %116 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 7
  store ptr @23, ptr %116, align 8
  %117 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 8
  store i1 false, ptr %117, align 1
  %118 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 9
  %119 = getelementptr inbounds %Texture.0, ptr %118, i32 0, i32 0
  store i32 0, ptr %119, align 4
  %120 = getelementptr inbounds %Texture.0, ptr %118, i32 0, i32 1
  store i32 0, ptr %120, align 4
  %121 = getelementptr inbounds %Texture.0, ptr %118, i32 0, i32 2
  store i32 0, ptr %121, align 4
  %122 = getelementptr inbounds %Texture.0, ptr %118, i32 0, i32 3
  store i32 0, ptr %122, align 4
  %123 = getelementptr inbounds %Texture.0, ptr %118, i32 0, i32 4
  store i32 0, ptr %123, align 4
  %124 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 10
  %125 = alloca i32, align 4
  %126 = alloca i32, align 4
  store i32 0, ptr %126, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock4:                              ; preds = %FillExpr.exit
  %127 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %129 = call ptr @malloc(i64 256)
  %130 = getelementptr inbounds %Cloud, ptr %129, i32 0, i32 0
  store ptr @25, ptr %130, align 8
  %131 = getelementptr inbounds %Cloud, ptr %129, i32 0, i32 1
  %132 = alloca i32, align 4
  %133 = alloca i32, align 4
  store i32 0, ptr %133, align 4
  br label %FillExpr.loopStart-042

checkContinueBlock6:                              ; preds = %FillExpr.exit46
  %134 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %135 = icmp eq i32 %134, 0
  br i1 %135, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %136 = load ptr, ptr %bird, align 8
  %137 = getelementptr inbounds %Bird, ptr %136, i32 0, i32 0
  %138 = load ptr, ptr %137, align 8
  %139 = getelementptr inbounds %"Bird::VTableType", ptr %138, i32 0, i32 9
  %140 = load ptr, ptr %139, align 8
  %141 = load ptr, ptr %fgAnim, align 8
  %142 = getelementptr inbounds %FlowWingAnim, ptr %141, i32 0, i32 0
  %143 = load ptr, ptr %142, align 8
  %144 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %143, i32 0, i32 9
  %145 = load ptr, ptr %144, align 8
  %rtPtr = alloca %Texture.0, align 8
  %146 = load ptr, ptr %bird, align 8
  %147 = getelementptr inbounds %Bird, ptr %146, i32 0, i32 0
  %148 = load ptr, ptr %147, align 8
  %149 = getelementptr inbounds %"Bird::VTableType", ptr %148, i32 0, i32 7
  %150 = load ptr, ptr %149, align 8
  %rtPtr62 = alloca ptr, align 8
  call void %150(ptr %rtPtr62, ptr %146)
  call void %145(ptr %rtPtr, ptr %rtPtr62, ptr %141)
  call void %140(ptr %rtPtr, ptr %136)
  %151 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %152 = icmp eq i32 %151, 0
  br i1 %152, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %153 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %155 = load ptr, ptr %cloud, align 8
  %156 = getelementptr inbounds %Cloud, ptr %155, i32 0, i32 0
  %157 = load ptr, ptr %156, align 8
  %158 = getelementptr inbounds %"Cloud::VTableType", ptr %157, i32 0, i32 3
  %159 = load ptr, ptr %158, align 8
  %160 = load ptr, ptr %fgAnim, align 8
  %161 = getelementptr inbounds %FlowWingAnim, ptr %160, i32 0, i32 0
  %162 = load ptr, ptr %161, align 8
  %163 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %162, i32 0, i32 9
  %164 = load ptr, ptr %163, align 8
  %rtPtr63 = alloca %Texture.0, align 8
  %165 = load ptr, ptr %cloud, align 8
  %166 = getelementptr inbounds %Cloud, ptr %165, i32 0, i32 0
  %167 = load ptr, ptr %166, align 8
  %168 = getelementptr inbounds %"Cloud::VTableType", ptr %167, i32 0, i32 2
  %169 = load ptr, ptr %168, align 8
  %rtPtr64 = alloca ptr, align 8
  call void %169(ptr %rtPtr64, ptr %165)
  call void %164(ptr %rtPtr63, ptr %rtPtr64, ptr %160)
  call void %159(ptr %rtPtr63, ptr %155)
  %170 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %172 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %173 = icmp eq i32 %172, 0
  br i1 %173, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %174 = load ptr, ptr %fgAnim, align 8
  %175 = getelementptr inbounds %FlowWingAnim, ptr %174, i32 0, i32 0
  %176 = load ptr, ptr %175, align 8
  %177 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %176, i32 0, i32 9
  %178 = load ptr, ptr %177, align 8
  %rtPtr65 = alloca %Texture.0, align 8
  %179 = alloca ptr, align 8
  store ptr @28, ptr %179, align 8
  call void %178(ptr %rtPtr65, ptr %179, ptr %174)
  %180 = load %Texture.0, ptr %rtPtr65, align 4
  store %Texture.0 %180, ptr %backgroundTexture, align 4
  %181 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %182 = icmp eq i32 %181, 0
  br i1 %182, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %183 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %184 = icmp eq i32 %183, 0
  br i1 %184, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %185 = load ptr, ptr %fgAnim, align 8
  %186 = getelementptr inbounds %FlowWingAnim, ptr %185, i32 0, i32 0
  %187 = load ptr, ptr %186, align 8
  %188 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %187, i32 0, i32 9
  %189 = load ptr, ptr %188, align 8
  %rtPtr66 = alloca %Texture.0, align 8
  %190 = alloca ptr, align 8
  store ptr @29, ptr %190, align 8
  call void %189(ptr %rtPtr66, ptr %190, ptr %185)
  %191 = load %Texture.0, ptr %rtPtr66, align 4
  store %Texture.0 %191, ptr %groundTexture, align 4
  %192 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %193 = icmp eq i32 %192, 0
  br i1 %193, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %194 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %195 = icmp eq i32 %194, 0
  br i1 %195, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %196 = load ptr, ptr %fgAnim, align 8
  %197 = getelementptr inbounds %FlowWingAnim, ptr %196, i32 0, i32 0
  %198 = load ptr, ptr %197, align 8
  %199 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %198, i32 0, i32 9
  %200 = load ptr, ptr %199, align 8
  %rtPtr67 = alloca %Texture.0, align 8
  %201 = alloca ptr, align 8
  store ptr @30, ptr %201, align 8
  call void %200(ptr %rtPtr67, ptr %201, ptr %196)
  %202 = load %Texture.0, ptr %rtPtr67, align 4
  store %Texture.0 %202, ptr %mountL1Texture, align 4
  %203 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %204 = icmp eq i32 %203, 0
  br i1 %204, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %205 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %206 = icmp eq i32 %205, 0
  br i1 %206, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %207 = load ptr, ptr %fgAnim, align 8
  %208 = getelementptr inbounds %FlowWingAnim, ptr %207, i32 0, i32 0
  %209 = load ptr, ptr %208, align 8
  %210 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %209, i32 0, i32 9
  %211 = load ptr, ptr %210, align 8
  %rtPtr68 = alloca %Texture.0, align 8
  %212 = alloca ptr, align 8
  store ptr @31, ptr %212, align 8
  call void %211(ptr %rtPtr68, ptr %212, ptr %207)
  %213 = load %Texture.0, ptr %rtPtr68, align 4
  store %Texture.0 %213, ptr %mountL2Texture, align 4
  %214 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %215 = icmp eq i32 %214, 0
  br i1 %215, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %216 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %217 = icmp eq i32 %216, 0
  br i1 %217, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %218 = load ptr, ptr %fgAnim, align 8
  %219 = getelementptr inbounds %FlowWingAnim, ptr %218, i32 0, i32 0
  %220 = load ptr, ptr %219, align 8
  %221 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %220, i32 0, i32 9
  %222 = load ptr, ptr %221, align 8
  %rtPtr69 = alloca %Texture.0, align 8
  %223 = alloca ptr, align 8
  store ptr @32, ptr %223, align 8
  call void %222(ptr %rtPtr69, ptr %223, ptr %218)
  %224 = load %Texture.0, ptr %rtPtr69, align 4
  store %Texture.0 %224, ptr %mount2L2Texture, align 4
  %225 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %226 = icmp eq i32 %225, 0
  br i1 %226, label %checkContinueBlock20, label %afterNestedBlock

checkContinueBlock20:                             ; preds = %nestedBlock19
  %227 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %228 = icmp eq i32 %227, 0
  br i1 %228, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %229 = load ptr, ptr %fgAnim, align 8
  %230 = getelementptr inbounds %FlowWingAnim, ptr %229, i32 0, i32 0
  %231 = load ptr, ptr %230, align 8
  %232 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %231, i32 0, i32 9
  %233 = load ptr, ptr %232, align 8
  %rtPtr70 = alloca %Texture.0, align 8
  %234 = alloca ptr, align 8
  store ptr @33, ptr %234, align 8
  call void %233(ptr %rtPtr70, ptr %234, ptr %229)
  %235 = load %Texture.0, ptr %rtPtr70, align 4
  store %Texture.0 %235, ptr %mount1L3Texture, align 4
  %236 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %237 = icmp eq i32 %236, 0
  br i1 %237, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %238 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %239 = icmp eq i32 %238, 0
  br i1 %239, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %240 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %240, align 4
  %241 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %241, align 4
  %242 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %243 = icmp eq i32 %242, 0
  br i1 %243, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %244 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %245 = icmp eq i32 %244, 0
  br i1 %245, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  %246 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  store float -1.542000e+03, ptr %246, align 4
  %247 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %247, align 4
  %248 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %249 = icmp eq i32 %248, 0
  br i1 %249, label %checkContinueBlock26, label %afterNestedBlock

checkContinueBlock26:                             ; preds = %nestedBlock25
  %250 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %251 = icmp eq i32 %250, 0
  br i1 %251, label %nestedBlock27, label %afterNestedBlock

nestedBlock27:                                    ; preds = %checkContinueBlock26
  %252 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %screenWidth71 = load i32, ptr @screenWidth, align 4
  %253 = load i32, ptr @screenWidth, align 4
  %254 = mul i32 -1, %253
  %255 = sitofp i32 %254 to float
  store float %255, ptr %252, align 4
  %256 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %256, align 4
  %257 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %258 = icmp eq i32 %257, 0
  br i1 %258, label %checkContinueBlock28, label %afterNestedBlock

checkContinueBlock28:                             ; preds = %nestedBlock27
  %259 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %260 = icmp eq i32 %259, 0
  br i1 %260, label %nestedBlock29, label %afterNestedBlock

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %261 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %screenWidth72 = load i32, ptr @screenWidth, align 4
  %262 = load i32, ptr @screenWidth, align 4
  %263 = mul i32 -1, %262
  %rtPtr73 = alloca i32, align 4
  %screenWidth74 = load i32, ptr @screenWidth, align 4
  %264 = load i32, ptr @screenWidth, align 4
  %265 = sitofp i32 %264 to double
  %266 = fdiv double %265, 4.000000e+00
  %267 = fptosi double %266 to i32
  %268 = alloca i32, align 4
  store i32 %267, ptr %268, align 4
  %screenWidth75 = load i32, ptr @screenWidth, align 4
  %269 = load i32, ptr @screenWidth, align 4
  %270 = sitofp i32 %269 to double
  %271 = fdiv double %270, 2.000000e+00
  %272 = fptosi double %271 to i32
  %273 = alloca i32, align 4
  store i32 %272, ptr %273, align 4
  call void @getRandomNumber(ptr %rtPtr73, ptr %268, ptr %273)
  %274 = load i32, ptr %rtPtr73, align 4
  %275 = sub i32 %263, %274
  %276 = sitofp i32 %275 to float
  store float %276, ptr %261, align 4
  %277 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %277, align 4
  %278 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %279 = icmp eq i32 %278, 0
  br i1 %279, label %checkContinueBlock30, label %afterNestedBlock

checkContinueBlock30:                             ; preds = %nestedBlock29
  %280 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %281 = icmp eq i32 %280, 0
  br i1 %281, label %nestedBlock31, label %afterNestedBlock

nestedBlock31:                                    ; preds = %checkContinueBlock30
  %282 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %screenWidth76 = load i32, ptr @screenWidth, align 4
  %283 = load i32, ptr @screenWidth, align 4
  %284 = mul i32 -1, %283
  %rtPtr77 = alloca i32, align 4
  %screenWidth78 = load i32, ptr @screenWidth, align 4
  %285 = load i32, ptr @screenWidth, align 4
  %286 = sitofp i32 %285 to double
  %287 = fdiv double %286, 4.000000e+00
  %288 = fptosi double %287 to i32
  %289 = alloca i32, align 4
  store i32 %288, ptr %289, align 4
  %screenWidth79 = load i32, ptr @screenWidth, align 4
  %290 = load i32, ptr @screenWidth, align 4
  %291 = alloca i32, align 4
  store i32 %290, ptr %291, align 4
  call void @getRandomNumber(ptr %rtPtr77, ptr %289, ptr %291)
  %292 = load i32, ptr %rtPtr77, align 4
  %293 = sub i32 %284, %292
  %294 = sitofp i32 %293 to float
  store float %294, ptr %282, align 4
  %295 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %295, align 4
  %296 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %297 = icmp eq i32 %296, 0
  br i1 %297, label %checkContinueBlock32, label %afterNestedBlock

checkContinueBlock32:                             ; preds = %nestedBlock31
  %298 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %299 = icmp eq i32 %298, 0
  br i1 %299, label %nestedBlock33, label %afterNestedBlock

nestedBlock33:                                    ; preds = %checkContinueBlock32
  %300 = load ptr, ptr %bird, align 8
  %301 = getelementptr inbounds %Bird, ptr %300, i32 0, i32 0
  %302 = load ptr, ptr %301, align 8
  %303 = getelementptr inbounds %"Bird::VTableType", ptr %302, i32 0, i32 5
  %304 = load ptr, ptr %303, align 8
  %rtPtr80 = alloca i1, align 1
  call void %304(ptr %rtPtr80, ptr %300)
  %305 = load i1, ptr %rtPtr80, align 1
  %306 = xor i1 %305, true
  %307 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  %id = load i32, ptr %307, align 4
  %308 = load i32, ptr %307, align 4
  %309 = icmp eq i32 %308, 0
  %310 = select i1 %306, i1 true, i1 %309
  br i1 %310, label %then, label %else

checkContinueBlock34:                             ; preds = %afterIfElse
  %311 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %312 = icmp eq i32 %311, 0
  br i1 %312, label %nestedBlock35, label %afterNestedBlock

nestedBlock35:                                    ; preds = %checkContinueBlock34
  br label %"while:conditon"

checkContinueBlock36:                             ; preds = %end_block409
  %313 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %314 = icmp eq i32 %313, 0
  br i1 %314, label %nestedBlock37, label %afterNestedBlock

nestedBlock37:                                    ; preds = %checkContinueBlock36
  %315 = load ptr, ptr %fgAnim, align 8
  %316 = getelementptr inbounds %FlowWingAnim, ptr %315, i32 0, i32 0
  %317 = load ptr, ptr %316, align 8
  %318 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %317, i32 0, i32 13
  %319 = load ptr, ptr %318, align 8
  call void %319(ptr %315)
  %320 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %321 = icmp eq i32 %320, 0
  br i1 %321, label %checkContinueBlock38, label %afterNestedBlock

checkContinueBlock38:                             ; preds = %nestedBlock37
  %322 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %323 = icmp eq i32 %322, 0
  br i1 %323, label %nestedBlock39, label %afterNestedBlock

nestedBlock39:                                    ; preds = %checkContinueBlock38
  br label %returnBlock410

checkContinueBlock40:                             ; preds = %mergeBlock411
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock3
  store i32 0, ptr %125, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %324 = load i32, ptr %125, align 4
  %325 = icmp slt i32 %324, 9
  %326 = load i32, ptr %126, align 4
  %327 = icmp slt i32 %326, 9
  %328 = and i1 %325, %327
  br i1 %328, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %329 = load i32, ptr %125, align 4
  %330 = getelementptr [9 x %Position.4], ptr %124, i32 0, i32 %329
  %331 = getelementptr inbounds %Position.4, ptr %330, i32 0, i32 0
  store float 0.000000e+00, ptr %331, align 4
  %332 = getelementptr inbounds %Position.4, ptr %330, i32 0, i32 1
  store float 0.000000e+00, ptr %332, align 4
  %333 = load i32, ptr %125, align 4
  %334 = add i32 %333, 1
  store i32 %334, ptr %125, align 4
  %335 = load i32, ptr %126, align 4
  %336 = add i32 %335, 1
  store i32 %336, ptr %126, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %337 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 11
  %338 = getelementptr inbounds %Position.4, ptr %337, i32 0, i32 0
  store float 0.000000e+00, ptr %338, align 4
  %339 = getelementptr inbounds %Position.4, ptr %337, i32 0, i32 1
  store float 0.000000e+00, ptr %339, align 4
  %340 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %340, align 8
  %341 = load ptr, ptr %340, align 8
  %342 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 8
  store ptr @Bird.updateY, ptr %342, align 8
  %343 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 7
  store ptr @Bird.getTexturePath, ptr %343, align 8
  %344 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 5
  store ptr @Bird.isTextureLoaded, ptr %344, align 8
  %345 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 9
  store ptr @Bird.setTexture, ptr %345, align 8
  %346 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 2
  store ptr @Bird.getOrigin, ptr %346, align 8
  %347 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 4
  store ptr @Bird.getSource, ptr %347, align 8
  %348 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 6
  store ptr @Bird.update, ptr %348, align 8
  %349 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 0
  store ptr @Bird.getTexture, ptr %349, align 8
  %350 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 3
  store ptr @Bird.getDistination, ptr %350, align 8
  %351 = getelementptr inbounds %"Bird::VTableType", ptr %341, i32 0, i32 1
  store ptr @Bird.getRotation, ptr %351, align 8
  %352 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 1
  store float 3.600000e+02, ptr %352, align 4
  %353 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 2
  store float 9.000000e+01, ptr %353, align 4
  %354 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 3
  %FPS41 = load i32, ptr @FPS, align 4
  %355 = load i32, ptr @FPS, align 4
  %356 = sitofp i32 %355 to double
  %357 = fdiv double 1.000000e+01, %356
  store double %357, ptr %354, align 8
  %358 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 5
  store i32 9, ptr %358, align 4
  %359 = getelementptr inbounds %Bird, ptr %108, i32 0, i32 6
  store i32 0, ptr %359, align 4
  %360 = alloca ptr, align 8
  store ptr @24, ptr %360, align 8
  call void @Bird.init1(ptr %360, ptr %108)
  %361 = load %Bird, ptr %108, align 8
  store %Bird %361, ptr %108, align 8
  store ptr %108, ptr %bird, align 8
  %362 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %363 = icmp eq i32 %362, 0
  br i1 %363, label %checkContinueBlock4, label %afterNestedBlock

FillExpr.loopStart-042:                           ; preds = %nestedBlock5
  store i32 0, ptr %132, align 4
  br label %FillExpr.loopCmp-043

FillExpr.loopCmp-043:                             ; preds = %FillExpr.exit61, %FillExpr.loopStart-042
  %364 = load i32, ptr %132, align 4
  %365 = icmp slt i32 %364, 5
  %366 = load i32, ptr %133, align 4
  %367 = icmp slt i32 %366, 5
  %368 = and i1 %365, %367
  br i1 %368, label %FillExpr.loopBody-044, label %FillExpr.loopEnd-045

FillExpr.loopBody-044:                            ; preds = %FillExpr.loopCmp-043
  %369 = load i32, ptr %132, align 4
  %370 = getelementptr [5 x %AttributeType.5], ptr %131, i32 0, i32 %369
  %371 = getelementptr inbounds %AttributeType.5, ptr %370, i32 0, i32 0
  %372 = alloca i32, align 4
  %373 = alloca i32, align 4
  store i32 0, ptr %373, align 4
  br label %FillExpr.loopStart-047

FillExpr.loopEnd-045:                             ; preds = %FillExpr.loopCmp-043
  br label %FillExpr.exit46

FillExpr.exit46:                                  ; preds = %FillExpr.loopEnd-045
  %374 = getelementptr inbounds %Cloud, ptr %129, i32 0, i32 2
  %375 = getelementptr inbounds %Texture.0, ptr %374, i32 0, i32 0
  store i32 0, ptr %375, align 4
  %376 = getelementptr inbounds %Texture.0, ptr %374, i32 0, i32 1
  store i32 0, ptr %376, align 4
  %377 = getelementptr inbounds %Texture.0, ptr %374, i32 0, i32 2
  store i32 0, ptr %377, align 4
  %378 = getelementptr inbounds %Texture.0, ptr %374, i32 0, i32 3
  store i32 0, ptr %378, align 4
  %379 = getelementptr inbounds %Texture.0, ptr %374, i32 0, i32 4
  store i32 0, ptr %379, align 4
  %380 = getelementptr inbounds %Cloud, ptr %129, i32 0, i32 3
  store ptr @26, ptr %380, align 8
  %381 = getelementptr inbounds %Cloud, ptr %129, i32 0, i32 0
  store ptr @vtable.Cloud.fg, ptr %381, align 8
  %382 = load ptr, ptr %381, align 8
  %383 = getelementptr inbounds %"Cloud::VTableType", ptr %382, i32 0, i32 4
  store ptr @Cloud.update, ptr %383, align 8
  %384 = getelementptr inbounds %"Cloud::VTableType", ptr %382, i32 0, i32 3
  store ptr @Cloud.setTexture, ptr %384, align 8
  %385 = getelementptr inbounds %"Cloud::VTableType", ptr %382, i32 0, i32 2
  store ptr @Cloud.getTexturePath, ptr %385, align 8
  %386 = getelementptr inbounds %"Cloud::VTableType", ptr %382, i32 0, i32 1
  store ptr @Cloud.getTexture, ptr %386, align 8
  %387 = getelementptr inbounds %"Cloud::VTableType", ptr %382, i32 0, i32 0
  store ptr @Cloud.draw, ptr %387, align 8
  %388 = alloca ptr, align 8
  store ptr @27, ptr %388, align 8
  call void @Cloud.init1(ptr %388, ptr %129)
  %389 = load %Cloud, ptr %129, align 8
  store %Cloud %389, ptr %129, align 8
  store ptr %129, ptr %cloud, align 8
  %390 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %391 = icmp eq i32 %390, 0
  br i1 %391, label %checkContinueBlock6, label %afterNestedBlock

FillExpr.loopStart-047:                           ; preds = %FillExpr.loopBody-044
  store i32 0, ptr %372, align 4
  br label %FillExpr.loopCmp-048

FillExpr.loopCmp-048:                             ; preds = %FillExpr.loopBody-049, %FillExpr.loopStart-047
  %392 = load i32, ptr %372, align 4
  %393 = icmp slt i32 %392, 4
  %394 = load i32, ptr %373, align 4
  %395 = icmp slt i32 %394, 4
  %396 = and i1 %393, %395
  br i1 %396, label %FillExpr.loopBody-049, label %FillExpr.loopEnd-050

FillExpr.loopBody-049:                            ; preds = %FillExpr.loopCmp-048
  %397 = load i32, ptr %372, align 4
  %398 = getelementptr [4 x float], ptr %371, i32 0, i32 %397
  store float 0.000000e+00, ptr %398, align 4
  %399 = load i32, ptr %372, align 4
  %400 = add i32 %399, 1
  store i32 %400, ptr %372, align 4
  %401 = load i32, ptr %373, align 4
  %402 = add i32 %401, 1
  store i32 %402, ptr %373, align 4
  br label %FillExpr.loopCmp-048

FillExpr.loopEnd-050:                             ; preds = %FillExpr.loopCmp-048
  br label %FillExpr.exit51

FillExpr.exit51:                                  ; preds = %FillExpr.loopEnd-050
  %403 = getelementptr inbounds %AttributeType.5, ptr %370, i32 0, i32 1
  %404 = alloca i32, align 4
  %405 = alloca i32, align 4
  store i32 0, ptr %405, align 4
  br label %FillExpr.loopStart-052

FillExpr.loopStart-052:                           ; preds = %FillExpr.exit51
  store i32 0, ptr %404, align 4
  br label %FillExpr.loopCmp-053

FillExpr.loopCmp-053:                             ; preds = %FillExpr.loopBody-054, %FillExpr.loopStart-052
  %406 = load i32, ptr %404, align 4
  %407 = icmp slt i32 %406, 4
  %408 = load i32, ptr %405, align 4
  %409 = icmp slt i32 %408, 4
  %410 = and i1 %407, %409
  br i1 %410, label %FillExpr.loopBody-054, label %FillExpr.loopEnd-055

FillExpr.loopBody-054:                            ; preds = %FillExpr.loopCmp-053
  %411 = load i32, ptr %404, align 4
  %412 = getelementptr [4 x float], ptr %403, i32 0, i32 %411
  store float 0.000000e+00, ptr %412, align 4
  %413 = load i32, ptr %404, align 4
  %414 = add i32 %413, 1
  store i32 %414, ptr %404, align 4
  %415 = load i32, ptr %405, align 4
  %416 = add i32 %415, 1
  store i32 %416, ptr %405, align 4
  br label %FillExpr.loopCmp-053

FillExpr.loopEnd-055:                             ; preds = %FillExpr.loopCmp-053
  br label %FillExpr.exit56

FillExpr.exit56:                                  ; preds = %FillExpr.loopEnd-055
  %417 = getelementptr inbounds %AttributeType.5, ptr %370, i32 0, i32 2
  %418 = alloca i32, align 4
  %419 = alloca i32, align 4
  store i32 0, ptr %419, align 4
  br label %FillExpr.loopStart-057

FillExpr.loopStart-057:                           ; preds = %FillExpr.exit56
  store i32 0, ptr %418, align 4
  br label %FillExpr.loopCmp-058

FillExpr.loopCmp-058:                             ; preds = %FillExpr.loopBody-059, %FillExpr.loopStart-057
  %420 = load i32, ptr %418, align 4
  %421 = icmp slt i32 %420, 2
  %422 = load i32, ptr %419, align 4
  %423 = icmp slt i32 %422, 2
  %424 = and i1 %421, %423
  br i1 %424, label %FillExpr.loopBody-059, label %FillExpr.loopEnd-060

FillExpr.loopBody-059:                            ; preds = %FillExpr.loopCmp-058
  %425 = load i32, ptr %418, align 4
  %426 = getelementptr [2 x float], ptr %417, i32 0, i32 %425
  store float 0.000000e+00, ptr %426, align 4
  %427 = load i32, ptr %418, align 4
  %428 = add i32 %427, 1
  store i32 %428, ptr %418, align 4
  %429 = load i32, ptr %419, align 4
  %430 = add i32 %429, 1
  store i32 %430, ptr %419, align 4
  br label %FillExpr.loopCmp-058

FillExpr.loopEnd-060:                             ; preds = %FillExpr.loopCmp-058
  br label %FillExpr.exit61

FillExpr.exit61:                                  ; preds = %FillExpr.loopEnd-060
  %431 = getelementptr inbounds %AttributeType.5, ptr %370, i32 0, i32 3
  store float 0.000000e+00, ptr %431, align 4
  %432 = load i32, ptr %132, align 4
  %433 = add i32 %432, 1
  store i32 %433, ptr %132, align 4
  %434 = load i32, ptr %133, align 4
  %435 = add i32 %434, 1
  store i32 %435, ptr %133, align 4
  br label %FillExpr.loopCmp-043

then:                                             ; preds = %nestedBlock33
  br label %nestedBlock82

else:                                             ; preds = %nestedBlock33
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock81
  %436 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %437 = icmp eq i32 %436, 0
  br i1 %437, label %checkContinueBlock34, label %afterNestedBlock

afterNestedBlock81:                               ; preds = %checkContinueBlock89, %mergeBlock, %checkContinueBlock87, %nestedBlock86, %checkContinueBlock85, %nestedBlock84, %checkContinueBlock83, %nestedBlock82
  br label %afterIfElse

nestedBlock82:                                    ; preds = %then
  %438 = load ptr, ptr %fgAnim, align 8
  %439 = getelementptr inbounds %FlowWingAnim, ptr %438, i32 0, i32 0
  %440 = load ptr, ptr %439, align 8
  %441 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %440, i32 0, i32 1
  %442 = load ptr, ptr %441, align 8
  %443 = load ptr, ptr %fgAnim, align 8
  %444 = getelementptr inbounds %FlowWingAnim, ptr %443, i32 0, i32 7
  %445 = getelementptr inbounds %LOG_TYPE.1, ptr %444, i32 0, i32 5
  %ERROR = load i32, ptr %445, align 4
  %446 = alloca ptr, align 8
  store ptr @34, ptr %446, align 8
  call void %442(ptr %445, ptr %446, ptr %438)
  %447 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %448 = icmp eq i32 %447, 0
  br i1 %448, label %checkContinueBlock83, label %afterNestedBlock81

checkContinueBlock83:                             ; preds = %nestedBlock82
  %449 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %450 = icmp eq i32 %449, 0
  br i1 %450, label %nestedBlock84, label %afterNestedBlock81

nestedBlock84:                                    ; preds = %checkContinueBlock83
  %451 = load ptr, ptr %fgAnim, align 8
  %452 = getelementptr inbounds %FlowWingAnim, ptr %451, i32 0, i32 0
  %453 = load ptr, ptr %452, align 8
  %454 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %453, i32 0, i32 14
  %455 = load ptr, ptr %454, align 8
  %456 = load ptr, ptr %bird, align 8
  %457 = getelementptr inbounds %Bird, ptr %456, i32 0, i32 0
  %458 = load ptr, ptr %457, align 8
  %459 = getelementptr inbounds %"Bird::VTableType", ptr %458, i32 0, i32 0
  %460 = load ptr, ptr %459, align 8
  %rtPtr90 = alloca %Texture.0, align 8
  call void %460(ptr %rtPtr90, ptr %456)
  call void %455(ptr %rtPtr90, ptr %451)
  %461 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %462 = icmp eq i32 %461, 0
  br i1 %462, label %checkContinueBlock85, label %afterNestedBlock81

checkContinueBlock85:                             ; preds = %nestedBlock84
  %463 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %464 = icmp eq i32 %463, 0
  br i1 %464, label %nestedBlock86, label %afterNestedBlock81

nestedBlock86:                                    ; preds = %checkContinueBlock85
  %465 = load ptr, ptr %fgAnim, align 8
  %466 = getelementptr inbounds %FlowWingAnim, ptr %465, i32 0, i32 0
  %467 = load ptr, ptr %466, align 8
  %468 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %467, i32 0, i32 13
  %469 = load ptr, ptr %468, align 8
  call void %469(ptr %465)
  %470 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %471 = icmp eq i32 %470, 0
  br i1 %471, label %checkContinueBlock87, label %afterNestedBlock81

checkContinueBlock87:                             ; preds = %nestedBlock86
  %472 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %473 = icmp eq i32 %472, 0
  br i1 %473, label %nestedBlock88, label %afterNestedBlock81

nestedBlock88:                                    ; preds = %checkContinueBlock87
  br label %returnBlock

checkContinueBlock89:                             ; preds = %mergeBlock
  br label %afterNestedBlock81

returnBlock:                                      ; preds = %nestedBlock88
  store i32 1, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %474 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %475 = icmp eq i32 %474, 0
  br i1 %475, label %checkContinueBlock89, label %afterNestedBlock81

"while:conditon":                                 ; preds = %afterNestedBlock92, %nestedBlock35
  %476 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %477 = icmp eq i32 %476, 0
  br i1 %477, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock93

while.end:                                        ; preds = %afterNestedBlock92, %end_block
  %478 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %479 = icmp eq i32 %478, 0
  br i1 %479, label %end_block409, label %decrement_block408

decrement_block:                                  ; preds = %"while:conditon"
  %480 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %481 = sub i32 %480, 1
  store i32 %481, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %482 = load ptr, ptr %fgAnim, align 8
  %483 = getelementptr inbounds %FlowWingAnim, ptr %482, i32 0, i32 0
  %484 = load ptr, ptr %483, align 8
  %485 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %484, i32 0, i32 18
  %486 = load ptr, ptr %485, align 8
  %rtPtr91 = alloca i1, align 1
  call void %486(ptr %rtPtr91, ptr %482)
  %487 = load i1, ptr %rtPtr91, align 1
  %488 = xor i1 %487, true
  br i1 %488, label %"while:body", label %while.end

afterNestedBlock92:                               ; preds = %checkContinueBlock132, %nestedBlock131, %checkContinueBlock130, %nestedBlock129, %checkContinueBlock128, %FillExpr.exit398, %checkContinueBlock126, %FillExpr.exit376, %checkContinueBlock124, %FillExpr.exit354, %checkContinueBlock122, %FillExpr.exit332, %checkContinueBlock120, %FillExpr.exit310, %checkContinueBlock118, %FillExpr.exit289, %checkContinueBlock116, %FillExpr.exit269, %checkContinueBlock114, %nestedBlock113, %checkContinueBlock112, %FillExpr.exit251, %checkContinueBlock110, %nestedBlock109, %checkContinueBlock108, %nestedBlock107, %checkContinueBlock106, %nestedBlock105, %checkContinueBlock104, %afterIfElse229, %checkContinueBlock102, %afterNestedBlock202, %checkContinueBlock100, %afterNestedBlock183, %checkContinueBlock98, %afterNestedBlock164, %checkContinueBlock96, %afterNestedBlock134, %checkContinueBlock94, %nestedBlock93
  %489 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %490 = icmp eq i32 %489, 0
  br i1 %490, label %"while:conditon", label %while.end

nestedBlock93:                                    ; preds = %"while:body"
  %491 = load ptr, ptr %bird, align 8
  %492 = getelementptr inbounds %Bird, ptr %491, i32 0, i32 0
  %493 = load ptr, ptr %492, align 8
  %494 = getelementptr inbounds %"Bird::VTableType", ptr %493, i32 0, i32 6
  %495 = load ptr, ptr %494, align 8
  %496 = load ptr, ptr %fgAnim, align 8
  %497 = getelementptr inbounds %FlowWingAnim, ptr %496, i32 0, i32 0
  %498 = load ptr, ptr %497, align 8
  %499 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %498, i32 0, i32 8
  %500 = load ptr, ptr %499, align 8
  %rtPtr133 = alloca float, align 4
  call void %500(ptr %rtPtr133, ptr %496)
  call void %495(ptr %rtPtr133, ptr %491)
  %501 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %502 = icmp eq i32 %501, 0
  br i1 %502, label %checkContinueBlock94, label %afterNestedBlock92

checkContinueBlock94:                             ; preds = %nestedBlock93
  %503 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %504 = icmp eq i32 %503, 0
  br i1 %504, label %nestedBlock95, label %afterNestedBlock92

nestedBlock95:                                    ; preds = %checkContinueBlock94
  br label %nestedBlock135

checkContinueBlock96:                             ; preds = %afterNestedBlock134
  %505 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %506 = icmp eq i32 %505, 0
  br i1 %506, label %nestedBlock97, label %afterNestedBlock92

nestedBlock97:                                    ; preds = %checkContinueBlock96
  br label %nestedBlock165

checkContinueBlock98:                             ; preds = %afterNestedBlock164
  %507 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %508 = icmp eq i32 %507, 0
  br i1 %508, label %nestedBlock99, label %afterNestedBlock92

nestedBlock99:                                    ; preds = %checkContinueBlock98
  br label %nestedBlock184

checkContinueBlock100:                            ; preds = %afterNestedBlock183
  %509 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %510 = icmp eq i32 %509, 0
  br i1 %510, label %nestedBlock101, label %afterNestedBlock92

nestedBlock101:                                   ; preds = %checkContinueBlock100
  br label %nestedBlock203

checkContinueBlock102:                            ; preds = %afterNestedBlock202
  %511 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %512 = icmp eq i32 %511, 0
  br i1 %512, label %nestedBlock103, label %afterNestedBlock92

nestedBlock103:                                   ; preds = %checkContinueBlock102
  %513 = load ptr, ptr %fgAnim, align 8
  %514 = getelementptr inbounds %FlowWingAnim, ptr %513, i32 0, i32 0
  %515 = load ptr, ptr %514, align 8
  %516 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %515, i32 0, i32 0
  %517 = load ptr, ptr %516, align 8
  %rtPtr224 = alloca i1, align 1
  %518 = load ptr, ptr %fgAnim, align 8
  %519 = getelementptr inbounds %FlowWingAnim, ptr %518, i32 0, i32 6
  %520 = getelementptr inbounds %KEYS_TYPE.2, ptr %519, i32 0, i32 3
  %KEY_UP = load i32, ptr %520, align 4
  call void %517(ptr %rtPtr224, ptr %520, ptr %513)
  %521 = load i1, ptr %rtPtr224, align 1
  %522 = load ptr, ptr %fgAnim, align 8
  %523 = getelementptr inbounds %FlowWingAnim, ptr %522, i32 0, i32 0
  %524 = load ptr, ptr %523, align 8
  %525 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %524, i32 0, i32 4
  %526 = load ptr, ptr %525, align 8
  %rtPtr225 = alloca i1, align 1
  %527 = load ptr, ptr %fgAnim, align 8
  %528 = getelementptr inbounds %FlowWingAnim, ptr %527, i32 0, i32 6
  %529 = getelementptr inbounds %KEYS_TYPE.2, ptr %528, i32 0, i32 3
  %KEY_UP226 = load i32, ptr %529, align 4
  call void %526(ptr %rtPtr225, ptr %529, ptr %522)
  %530 = load i1, ptr %rtPtr225, align 1
  %531 = select i1 %521, i1 true, i1 %530
  br i1 %531, label %then227, label %else228

checkContinueBlock104:                            ; preds = %afterIfElse229
  %532 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %533 = icmp eq i32 %532, 0
  br i1 %533, label %nestedBlock105, label %afterNestedBlock92

nestedBlock105:                                   ; preds = %checkContinueBlock104
  %534 = load ptr, ptr %cloud, align 8
  %535 = getelementptr inbounds %Cloud, ptr %534, i32 0, i32 0
  %536 = load ptr, ptr %535, align 8
  %537 = getelementptr inbounds %"Cloud::VTableType", ptr %536, i32 0, i32 4
  %538 = load ptr, ptr %537, align 8
  %539 = load ptr, ptr %fgAnim, align 8
  %540 = getelementptr inbounds %FlowWingAnim, ptr %539, i32 0, i32 0
  %541 = load ptr, ptr %540, align 8
  %542 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %541, i32 0, i32 8
  %543 = load ptr, ptr %542, align 8
  %rtPtr234 = alloca float, align 4
  call void %543(ptr %rtPtr234, ptr %539)
  call void %538(ptr %rtPtr234, ptr %534)
  %544 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %545 = icmp eq i32 %544, 0
  br i1 %545, label %checkContinueBlock106, label %afterNestedBlock92

checkContinueBlock106:                            ; preds = %nestedBlock105
  %546 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %547 = icmp eq i32 %546, 0
  br i1 %547, label %nestedBlock107, label %afterNestedBlock92

nestedBlock107:                                   ; preds = %checkContinueBlock106
  %548 = load ptr, ptr %fgAnim, align 8
  %549 = getelementptr inbounds %FlowWingAnim, ptr %548, i32 0, i32 0
  %550 = load ptr, ptr %549, align 8
  %551 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %550, i32 0, i32 15
  %552 = load ptr, ptr %551, align 8
  call void %552(ptr %548)
  %553 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %554 = icmp eq i32 %553, 0
  br i1 %554, label %checkContinueBlock108, label %afterNestedBlock92

checkContinueBlock108:                            ; preds = %nestedBlock107
  %555 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %556 = icmp eq i32 %555, 0
  br i1 %556, label %nestedBlock109, label %afterNestedBlock92

nestedBlock109:                                   ; preds = %checkContinueBlock108
  %557 = load ptr, ptr %fgAnim, align 8
  %558 = getelementptr inbounds %FlowWingAnim, ptr %557, i32 0, i32 0
  %559 = load ptr, ptr %558, align 8
  %560 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %559, i32 0, i32 10
  %561 = load ptr, ptr %560, align 8
  %562 = load ptr, ptr %fgAnim, align 8
  %563 = getelementptr inbounds %FlowWingAnim, ptr %562, i32 0, i32 5
  %564 = getelementptr inbounds %COLORS_TYPE.3, ptr %563, i32 0, i32 1
  %RED = load i32, ptr %564, align 4
  call void %561(ptr %564, ptr %557)
  %565 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %566 = icmp eq i32 %565, 0
  br i1 %566, label %checkContinueBlock110, label %afterNestedBlock92

checkContinueBlock110:                            ; preds = %nestedBlock109
  %567 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %568 = icmp eq i32 %567, 0
  br i1 %568, label %nestedBlock111, label %afterNestedBlock92

nestedBlock111:                                   ; preds = %checkContinueBlock110
  %569 = alloca [4 x float], align 4
  %570 = alloca i32, align 4
  %571 = alloca i32, align 4
  store i32 0, ptr %571, align 4
  br label %FillExpr.loopStart-0235

checkContinueBlock112:                            ; preds = %FillExpr.exit251
  %572 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %573 = icmp eq i32 %572, 0
  br i1 %573, label %nestedBlock113, label %afterNestedBlock92

nestedBlock113:                                   ; preds = %checkContinueBlock112
  %574 = load ptr, ptr %cloud, align 8
  %575 = getelementptr inbounds %Cloud, ptr %574, i32 0, i32 0
  %576 = load ptr, ptr %575, align 8
  %577 = getelementptr inbounds %"Cloud::VTableType", ptr %576, i32 0, i32 0
  %578 = load ptr, ptr %577, align 8
  %579 = load ptr, ptr %fgAnim, align 8
  call void %578(ptr %579, ptr %574)
  %580 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %581 = icmp eq i32 %580, 0
  br i1 %581, label %checkContinueBlock114, label %afterNestedBlock92

checkContinueBlock114:                            ; preds = %nestedBlock113
  %582 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %583 = icmp eq i32 %582, 0
  br i1 %583, label %nestedBlock115, label %afterNestedBlock92

nestedBlock115:                                   ; preds = %checkContinueBlock114
  %584 = alloca [4 x float], align 4
  %585 = alloca i32, align 4
  %586 = alloca i32, align 4
  store i32 0, ptr %586, align 4
  br label %FillExpr.loopStart-0252

checkContinueBlock116:                            ; preds = %FillExpr.exit269
  %587 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %588 = icmp eq i32 %587, 0
  br i1 %588, label %nestedBlock117, label %afterNestedBlock92

nestedBlock117:                                   ; preds = %checkContinueBlock116
  %589 = alloca [4 x float], align 4
  %590 = alloca i32, align 4
  %591 = alloca i32, align 4
  store i32 0, ptr %591, align 4
  br label %FillExpr.loopStart-0272

checkContinueBlock118:                            ; preds = %FillExpr.exit289
  %592 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %593 = icmp eq i32 %592, 0
  br i1 %593, label %nestedBlock119, label %afterNestedBlock92

nestedBlock119:                                   ; preds = %checkContinueBlock118
  %594 = alloca [4 x float], align 4
  %595 = alloca i32, align 4
  %596 = alloca i32, align 4
  store i32 0, ptr %596, align 4
  br label %FillExpr.loopStart-0293

checkContinueBlock120:                            ; preds = %FillExpr.exit310
  %597 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %598 = icmp eq i32 %597, 0
  br i1 %598, label %nestedBlock121, label %afterNestedBlock92

nestedBlock121:                                   ; preds = %checkContinueBlock120
  %599 = alloca [4 x float], align 4
  %600 = alloca i32, align 4
  %601 = alloca i32, align 4
  store i32 0, ptr %601, align 4
  br label %FillExpr.loopStart-0314

checkContinueBlock122:                            ; preds = %FillExpr.exit332
  %602 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %603 = icmp eq i32 %602, 0
  br i1 %603, label %nestedBlock123, label %afterNestedBlock92

nestedBlock123:                                   ; preds = %checkContinueBlock122
  %604 = alloca [4 x float], align 4
  %605 = alloca i32, align 4
  %606 = alloca i32, align 4
  store i32 0, ptr %606, align 4
  br label %FillExpr.loopStart-0336

checkContinueBlock124:                            ; preds = %FillExpr.exit354
  %607 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %608 = icmp eq i32 %607, 0
  br i1 %608, label %nestedBlock125, label %afterNestedBlock92

nestedBlock125:                                   ; preds = %checkContinueBlock124
  %609 = alloca [4 x float], align 4
  %610 = alloca i32, align 4
  %611 = alloca i32, align 4
  store i32 0, ptr %611, align 4
  br label %FillExpr.loopStart-0358

checkContinueBlock126:                            ; preds = %FillExpr.exit376
  %612 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %613 = icmp eq i32 %612, 0
  br i1 %613, label %nestedBlock127, label %afterNestedBlock92

nestedBlock127:                                   ; preds = %checkContinueBlock126
  %614 = alloca [4 x float], align 4
  %615 = alloca i32, align 4
  %616 = alloca i32, align 4
  store i32 0, ptr %616, align 4
  br label %FillExpr.loopStart-0380

checkContinueBlock128:                            ; preds = %FillExpr.exit398
  %617 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %618 = icmp eq i32 %617, 0
  br i1 %618, label %nestedBlock129, label %afterNestedBlock92

nestedBlock129:                                   ; preds = %checkContinueBlock128
  %619 = load ptr, ptr %bird, align 8
  %620 = getelementptr inbounds %Bird, ptr %619, i32 0, i32 0
  %621 = load ptr, ptr %620, align 8
  %622 = getelementptr inbounds %"Bird::VTableType", ptr %621, i32 0, i32 0
  %623 = load ptr, ptr %622, align 8
  %rtPtr402 = alloca %Texture.0, align 8
  call void %623(ptr %rtPtr402, ptr %619)
  %624 = load ptr, ptr %bird, align 8
  %625 = getelementptr inbounds %Bird, ptr %624, i32 0, i32 0
  %626 = load ptr, ptr %625, align 8
  %627 = getelementptr inbounds %"Bird::VTableType", ptr %626, i32 0, i32 4
  %628 = load ptr, ptr %627, align 8
  %rtPtr403 = alloca [4 x float], align 4
  call void %628(ptr %rtPtr403, ptr %624)
  %629 = load [4 x float], ptr %rtPtr403, align 4
  %630 = load ptr, ptr %bird, align 8
  %631 = getelementptr inbounds %Bird, ptr %630, i32 0, i32 0
  %632 = load ptr, ptr %631, align 8
  %633 = getelementptr inbounds %"Bird::VTableType", ptr %632, i32 0, i32 3
  %634 = load ptr, ptr %633, align 8
  %rtPtr404 = alloca [4 x float], align 4
  call void %634(ptr %rtPtr404, ptr %630)
  %635 = load [4 x float], ptr %rtPtr404, align 4
  %636 = load ptr, ptr %bird, align 8
  %637 = getelementptr inbounds %Bird, ptr %636, i32 0, i32 0
  %638 = load ptr, ptr %637, align 8
  %639 = getelementptr inbounds %"Bird::VTableType", ptr %638, i32 0, i32 2
  %640 = load ptr, ptr %639, align 8
  %rtPtr405 = alloca [2 x float], align 4
  call void %640(ptr %rtPtr405, ptr %636)
  %641 = load [2 x float], ptr %rtPtr405, align 4
  %642 = load ptr, ptr %bird, align 8
  %643 = getelementptr inbounds %Bird, ptr %642, i32 0, i32 0
  %644 = load ptr, ptr %643, align 8
  %645 = getelementptr inbounds %"Bird::VTableType", ptr %644, i32 0, i32 1
  %646 = load ptr, ptr %645, align 8
  %rtPtr406 = alloca float, align 4
  call void %646(ptr %rtPtr406, ptr %642)
  %647 = load float, ptr %rtPtr406, align 4
  %648 = load ptr, ptr %fgAnim, align 8
  %649 = getelementptr inbounds %FlowWingAnim, ptr %648, i32 0, i32 5
  %650 = getelementptr inbounds %COLORS_TYPE.3, ptr %649, i32 0, i32 0
  %WHITE407 = load i32, ptr %650, align 4
  %651 = load i32, ptr %650, align 4
  call void @DrawTexturePro(ptr %rtPtr402, [4 x float] %629, [4 x float] %635, [2 x float] %641, float %647, i32 %651)
  %652 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %653 = icmp eq i32 %652, 0
  br i1 %653, label %checkContinueBlock130, label %afterNestedBlock92

checkContinueBlock130:                            ; preds = %nestedBlock129
  %654 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %655 = icmp eq i32 %654, 0
  br i1 %655, label %nestedBlock131, label %afterNestedBlock92

nestedBlock131:                                   ; preds = %checkContinueBlock130
  %656 = load ptr, ptr %fgAnim, align 8
  %657 = getelementptr inbounds %FlowWingAnim, ptr %656, i32 0, i32 0
  %658 = load ptr, ptr %657, align 8
  %659 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %658, i32 0, i32 22
  %660 = load ptr, ptr %659, align 8
  call void %660(ptr %656)
  %661 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %662 = icmp eq i32 %661, 0
  br i1 %662, label %checkContinueBlock132, label %afterNestedBlock92

checkContinueBlock132:                            ; preds = %nestedBlock131
  br label %afterNestedBlock92

afterNestedBlock134:                              ; preds = %checkContinueBlock142, %afterIfElse159, %checkContinueBlock140, %afterIfElse151, %checkContinueBlock138, %nestedBlock137, %checkContinueBlock136, %nestedBlock135
  %663 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %664 = icmp eq i32 %663, 0
  br i1 %664, label %checkContinueBlock96, label %afterNestedBlock92

nestedBlock135:                                   ; preds = %nestedBlock95
  %665 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x = load float, ptr %665, align 4
  %666 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x143 = load float, ptr %666, align 4
  %667 = load float, ptr %666, align 4
  %668 = load ptr, ptr %fgAnim, align 8
  %669 = getelementptr inbounds %FlowWingAnim, ptr %668, i32 0, i32 0
  %670 = load ptr, ptr %669, align 8
  %671 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %670, i32 0, i32 8
  %672 = load ptr, ptr %671, align 8
  %rtPtr144 = alloca float, align 4
  call void %672(ptr %rtPtr144, ptr %668)
  %673 = load float, ptr %rtPtr144, align 4
  %674 = fmul float %673, 1.000000e+02
  %675 = fadd float %667, %674
  store float %675, ptr %665, align 4
  %676 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %677 = icmp eq i32 %676, 0
  br i1 %677, label %checkContinueBlock136, label %afterNestedBlock134

checkContinueBlock136:                            ; preds = %nestedBlock135
  %678 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %679 = icmp eq i32 %678, 0
  br i1 %679, label %nestedBlock137, label %afterNestedBlock134

nestedBlock137:                                   ; preds = %checkContinueBlock136
  %680 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x145 = load float, ptr %680, align 4
  %681 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x146 = load float, ptr %681, align 4
  %682 = load float, ptr %681, align 4
  %683 = load ptr, ptr %fgAnim, align 8
  %684 = getelementptr inbounds %FlowWingAnim, ptr %683, i32 0, i32 0
  %685 = load ptr, ptr %684, align 8
  %686 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %685, i32 0, i32 8
  %687 = load ptr, ptr %686, align 8
  %rtPtr147 = alloca float, align 4
  call void %687(ptr %rtPtr147, ptr %683)
  %688 = load float, ptr %rtPtr147, align 4
  %689 = fmul float %688, 1.000000e+02
  %690 = fadd float %682, %689
  store float %690, ptr %680, align 4
  %691 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %692 = icmp eq i32 %691, 0
  br i1 %692, label %checkContinueBlock138, label %afterNestedBlock134

checkContinueBlock138:                            ; preds = %nestedBlock137
  %693 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %694 = icmp eq i32 %693, 0
  br i1 %694, label %nestedBlock139, label %afterNestedBlock134

nestedBlock139:                                   ; preds = %checkContinueBlock138
  %695 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x148 = load float, ptr %695, align 4
  %696 = load float, ptr %695, align 4
  %697 = fcmp ogt float %696, 1.542000e+03
  br i1 %697, label %then149, label %else150

checkContinueBlock140:                            ; preds = %afterIfElse151
  %698 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %699 = icmp eq i32 %698, 0
  br i1 %699, label %nestedBlock141, label %afterNestedBlock134

nestedBlock141:                                   ; preds = %checkContinueBlock140
  %700 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x156 = load float, ptr %700, align 4
  %701 = load float, ptr %700, align 4
  %702 = fcmp ogt float %701, 1.542000e+03
  br i1 %702, label %then157, label %else158

checkContinueBlock142:                            ; preds = %afterIfElse159
  br label %afterNestedBlock134

then149:                                          ; preds = %nestedBlock139
  br label %nestedBlock153

else150:                                          ; preds = %nestedBlock139
  br label %afterIfElse151

afterIfElse151:                                   ; preds = %else150, %afterNestedBlock152
  %703 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %704 = icmp eq i32 %703, 0
  br i1 %704, label %checkContinueBlock140, label %afterNestedBlock134

afterNestedBlock152:                              ; preds = %checkContinueBlock154, %nestedBlock153
  %705 = load float, ptr %706, align 4
  br label %afterIfElse151

nestedBlock153:                                   ; preds = %then149
  %706 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x155 = load float, ptr %706, align 4
  store float -1.542000e+03, ptr %706, align 4
  %707 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %708 = icmp eq i32 %707, 0
  br i1 %708, label %checkContinueBlock154, label %afterNestedBlock152

checkContinueBlock154:                            ; preds = %nestedBlock153
  br label %afterNestedBlock152

then157:                                          ; preds = %nestedBlock141
  br label %nestedBlock161

else158:                                          ; preds = %nestedBlock141
  br label %afterIfElse159

afterIfElse159:                                   ; preds = %else158, %afterNestedBlock160
  %709 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %710 = icmp eq i32 %709, 0
  br i1 %710, label %checkContinueBlock142, label %afterNestedBlock134

afterNestedBlock160:                              ; preds = %checkContinueBlock162, %nestedBlock161
  %711 = load float, ptr %712, align 4
  br label %afterIfElse159

nestedBlock161:                                   ; preds = %then157
  %712 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x163 = load float, ptr %712, align 4
  store float -1.542000e+03, ptr %712, align 4
  %713 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %714 = icmp eq i32 %713, 0
  br i1 %714, label %checkContinueBlock162, label %afterNestedBlock160

checkContinueBlock162:                            ; preds = %nestedBlock161
  br label %afterNestedBlock160

afterNestedBlock164:                              ; preds = %checkContinueBlock168, %afterIfElse177, %checkContinueBlock166, %nestedBlock165
  %715 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %716 = icmp eq i32 %715, 0
  br i1 %716, label %checkContinueBlock98, label %afterNestedBlock92

nestedBlock165:                                   ; preds = %nestedBlock97
  %717 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x169 = load float, ptr %717, align 4
  %718 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x170 = load float, ptr %718, align 4
  %719 = load float, ptr %718, align 4
  %720 = load ptr, ptr %fgAnim, align 8
  %721 = getelementptr inbounds %FlowWingAnim, ptr %720, i32 0, i32 0
  %722 = load ptr, ptr %721, align 8
  %723 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %722, i32 0, i32 8
  %724 = load ptr, ptr %723, align 8
  %rtPtr171 = alloca float, align 4
  call void %724(ptr %rtPtr171, ptr %720)
  %725 = load float, ptr %rtPtr171, align 4
  %726 = fmul float %725, 1.000000e+01
  %727 = fadd float %719, %726
  store float %727, ptr %717, align 4
  %728 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %729 = icmp eq i32 %728, 0
  br i1 %729, label %checkContinueBlock166, label %afterNestedBlock164

checkContinueBlock166:                            ; preds = %nestedBlock165
  %730 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %731 = icmp eq i32 %730, 0
  br i1 %731, label %nestedBlock167, label %afterNestedBlock164

nestedBlock167:                                   ; preds = %checkContinueBlock166
  %732 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x172 = load float, ptr %732, align 4
  %733 = load float, ptr %732, align 4
  %screenWidth173 = load i32, ptr @screenWidth, align 4
  %734 = load i32, ptr @screenWidth, align 4
  %screenWidth174 = load i32, ptr @screenWidth, align 4
  %735 = load i32, ptr @screenWidth, align 4
  %736 = sitofp i32 %735 to double
  %737 = fdiv double %736, 2.000000e+00
  %738 = sitofp i32 %734 to double
  %739 = fadd double %738, %737
  %740 = fptrunc double %739 to float
  %741 = fcmp ogt float %733, %740
  br i1 %741, label %then175, label %else176

checkContinueBlock168:                            ; preds = %afterIfElse177
  br label %afterNestedBlock164

then175:                                          ; preds = %nestedBlock167
  br label %nestedBlock179

else176:                                          ; preds = %nestedBlock167
  br label %afterIfElse177

afterIfElse177:                                   ; preds = %else176, %afterNestedBlock178
  %742 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %743 = icmp eq i32 %742, 0
  br i1 %743, label %checkContinueBlock168, label %afterNestedBlock164

afterNestedBlock178:                              ; preds = %checkContinueBlock180, %nestedBlock179
  %744 = load float, ptr %745, align 4
  br label %afterIfElse177

nestedBlock179:                                   ; preds = %then175
  %745 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x181 = load float, ptr %745, align 4
  %screenWidth182 = load i32, ptr @screenWidth, align 4
  %746 = load i32, ptr @screenWidth, align 4
  %747 = mul i32 -1, %746
  %748 = sitofp i32 %747 to float
  store float %748, ptr %745, align 4
  %749 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %750 = icmp eq i32 %749, 0
  br i1 %750, label %checkContinueBlock180, label %afterNestedBlock178

checkContinueBlock180:                            ; preds = %nestedBlock179
  br label %afterNestedBlock178

afterNestedBlock183:                              ; preds = %checkContinueBlock187, %afterIfElse196, %checkContinueBlock185, %nestedBlock184
  %751 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %752 = icmp eq i32 %751, 0
  br i1 %752, label %checkContinueBlock100, label %afterNestedBlock92

nestedBlock184:                                   ; preds = %nestedBlock99
  %753 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x188 = load float, ptr %753, align 4
  %754 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x189 = load float, ptr %754, align 4
  %755 = load float, ptr %754, align 4
  %756 = load ptr, ptr %fgAnim, align 8
  %757 = getelementptr inbounds %FlowWingAnim, ptr %756, i32 0, i32 0
  %758 = load ptr, ptr %757, align 8
  %759 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %758, i32 0, i32 8
  %760 = load ptr, ptr %759, align 8
  %rtPtr190 = alloca float, align 4
  call void %760(ptr %rtPtr190, ptr %756)
  %761 = load float, ptr %rtPtr190, align 4
  %762 = fmul float %761, 1.000000e+01
  %763 = fadd float %755, %762
  store float %763, ptr %753, align 4
  %764 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %765 = icmp eq i32 %764, 0
  br i1 %765, label %checkContinueBlock185, label %afterNestedBlock183

checkContinueBlock185:                            ; preds = %nestedBlock184
  %766 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %767 = icmp eq i32 %766, 0
  br i1 %767, label %nestedBlock186, label %afterNestedBlock183

nestedBlock186:                                   ; preds = %checkContinueBlock185
  %768 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x191 = load float, ptr %768, align 4
  %769 = load float, ptr %768, align 4
  %screenWidth192 = load i32, ptr @screenWidth, align 4
  %770 = load i32, ptr @screenWidth, align 4
  %screenWidth193 = load i32, ptr @screenWidth, align 4
  %771 = load i32, ptr @screenWidth, align 4
  %772 = sitofp i32 %771 to double
  %773 = fdiv double %772, 2.000000e+00
  %774 = sitofp i32 %770 to double
  %775 = fadd double %774, %773
  %776 = fptrunc double %775 to float
  %777 = fcmp ogt float %769, %776
  br i1 %777, label %then194, label %else195

checkContinueBlock187:                            ; preds = %afterIfElse196
  br label %afterNestedBlock183

then194:                                          ; preds = %nestedBlock186
  br label %nestedBlock198

else195:                                          ; preds = %nestedBlock186
  br label %afterIfElse196

afterIfElse196:                                   ; preds = %else195, %afterNestedBlock197
  %778 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %779 = icmp eq i32 %778, 0
  br i1 %779, label %checkContinueBlock187, label %afterNestedBlock183

afterNestedBlock197:                              ; preds = %checkContinueBlock199, %nestedBlock198
  %780 = load float, ptr %781, align 4
  br label %afterIfElse196

nestedBlock198:                                   ; preds = %then194
  %781 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x200 = load float, ptr %781, align 4
  %screenWidth201 = load i32, ptr @screenWidth, align 4
  %782 = load i32, ptr @screenWidth, align 4
  %783 = mul i32 -1, %782
  %784 = sitofp i32 %783 to float
  store float %784, ptr %781, align 4
  %785 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %786 = icmp eq i32 %785, 0
  br i1 %786, label %checkContinueBlock199, label %afterNestedBlock197

checkContinueBlock199:                            ; preds = %nestedBlock198
  br label %afterNestedBlock197

afterNestedBlock202:                              ; preds = %checkContinueBlock206, %afterIfElse215, %checkContinueBlock204, %nestedBlock203
  %787 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %788 = icmp eq i32 %787, 0
  br i1 %788, label %checkContinueBlock102, label %afterNestedBlock92

nestedBlock203:                                   ; preds = %nestedBlock101
  %789 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x207 = load float, ptr %789, align 4
  %790 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x208 = load float, ptr %790, align 4
  %791 = load float, ptr %790, align 4
  %792 = load ptr, ptr %fgAnim, align 8
  %793 = getelementptr inbounds %FlowWingAnim, ptr %792, i32 0, i32 0
  %794 = load ptr, ptr %793, align 8
  %795 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %794, i32 0, i32 8
  %796 = load ptr, ptr %795, align 8
  %rtPtr209 = alloca float, align 4
  call void %796(ptr %rtPtr209, ptr %792)
  %797 = load float, ptr %rtPtr209, align 4
  %798 = fmul float %797, 1.000000e+01
  %799 = fadd float %791, %798
  store float %799, ptr %789, align 4
  %800 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %801 = icmp eq i32 %800, 0
  br i1 %801, label %checkContinueBlock204, label %afterNestedBlock202

checkContinueBlock204:                            ; preds = %nestedBlock203
  %802 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %803 = icmp eq i32 %802, 0
  br i1 %803, label %nestedBlock205, label %afterNestedBlock202

nestedBlock205:                                   ; preds = %checkContinueBlock204
  %804 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x210 = load float, ptr %804, align 4
  %805 = load float, ptr %804, align 4
  %screenWidth211 = load i32, ptr @screenWidth, align 4
  %806 = load i32, ptr @screenWidth, align 4
  %screenWidth212 = load i32, ptr @screenWidth, align 4
  %807 = load i32, ptr @screenWidth, align 4
  %808 = sitofp i32 %807 to double
  %809 = fdiv double %808, 2.000000e+00
  %810 = sitofp i32 %806 to double
  %811 = fadd double %810, %809
  %812 = fptrunc double %811 to float
  %813 = fcmp ogt float %805, %812
  br i1 %813, label %then213, label %else214

checkContinueBlock206:                            ; preds = %afterIfElse215
  br label %afterNestedBlock202

then213:                                          ; preds = %nestedBlock205
  br label %nestedBlock217

else214:                                          ; preds = %nestedBlock205
  br label %afterIfElse215

afterIfElse215:                                   ; preds = %else214, %afterNestedBlock216
  %814 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %815 = icmp eq i32 %814, 0
  br i1 %815, label %checkContinueBlock206, label %afterNestedBlock202

afterNestedBlock216:                              ; preds = %checkContinueBlock218, %nestedBlock217
  %816 = load float, ptr %817, align 4
  br label %afterIfElse215

nestedBlock217:                                   ; preds = %then213
  %817 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x219 = load float, ptr %817, align 4
  %screenWidth220 = load i32, ptr @screenWidth, align 4
  %818 = load i32, ptr @screenWidth, align 4
  %819 = mul i32 -1, %818
  %rtPtr221 = alloca i32, align 4
  %screenWidth222 = load i32, ptr @screenWidth, align 4
  %820 = load i32, ptr @screenWidth, align 4
  %821 = sitofp i32 %820 to double
  %822 = fdiv double %821, 4.000000e+00
  %823 = fptosi double %822 to i32
  %824 = alloca i32, align 4
  store i32 %823, ptr %824, align 4
  %screenWidth223 = load i32, ptr @screenWidth, align 4
  %825 = load i32, ptr @screenWidth, align 4
  %826 = sitofp i32 %825 to double
  %827 = fdiv double %826, 2.000000e+00
  %828 = fptosi double %827 to i32
  %829 = alloca i32, align 4
  store i32 %828, ptr %829, align 4
  call void @getRandomNumber(ptr %rtPtr221, ptr %824, ptr %829)
  %830 = load i32, ptr %rtPtr221, align 4
  %831 = sub i32 %819, %830
  %832 = sitofp i32 %831 to float
  store float %832, ptr %817, align 4
  %833 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %834 = icmp eq i32 %833, 0
  br i1 %834, label %checkContinueBlock218, label %afterNestedBlock216

checkContinueBlock218:                            ; preds = %nestedBlock217
  br label %afterNestedBlock216

then227:                                          ; preds = %nestedBlock103
  br label %nestedBlock231

else228:                                          ; preds = %nestedBlock103
  br label %afterIfElse229

afterIfElse229:                                   ; preds = %else228, %afterNestedBlock230
  %835 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %836 = icmp eq i32 %835, 0
  br i1 %836, label %checkContinueBlock104, label %afterNestedBlock92

afterNestedBlock230:                              ; preds = %checkContinueBlock232, %nestedBlock231
  br label %afterIfElse229

nestedBlock231:                                   ; preds = %then227
  %837 = load ptr, ptr %bird, align 8
  %838 = getelementptr inbounds %Bird, ptr %837, i32 0, i32 0
  %839 = load ptr, ptr %838, align 8
  %840 = getelementptr inbounds %"Bird::VTableType", ptr %839, i32 0, i32 8
  %841 = load ptr, ptr %840, align 8
  %842 = load ptr, ptr %fgAnim, align 8
  %843 = getelementptr inbounds %FlowWingAnim, ptr %842, i32 0, i32 0
  %844 = load ptr, ptr %843, align 8
  %845 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %844, i32 0, i32 8
  %846 = load ptr, ptr %845, align 8
  %rtPtr233 = alloca float, align 4
  call void %846(ptr %rtPtr233, ptr %842)
  call void %841(ptr %rtPtr233, ptr %837)
  %847 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %848 = icmp eq i32 %847, 0
  br i1 %848, label %checkContinueBlock232, label %afterNestedBlock230

checkContinueBlock232:                            ; preds = %nestedBlock231
  br label %afterNestedBlock230

FillExpr.loopStart-0235:                          ; preds = %nestedBlock111
  store i32 0, ptr %570, align 4
  br label %FillExpr.loopCmp-0236

FillExpr.loopCmp-0236:                            ; preds = %FillExpr.loopBody-0237, %FillExpr.loopStart-0235
  %849 = load i32, ptr %570, align 4
  %850 = icmp slt i32 %849, 4
  %851 = load i32, ptr %571, align 4
  %852 = icmp slt i32 %851, 4
  %853 = and i1 %850, %852
  br i1 %853, label %FillExpr.loopBody-0237, label %FillExpr.loopEnd-0238

FillExpr.loopBody-0237:                           ; preds = %FillExpr.loopCmp-0236
  %854 = load i32, ptr %570, align 4
  %855 = getelementptr [4 x float], ptr %569, i32 0, i32 %854
  store float 0.000000e+00, ptr %855, align 4
  %856 = load i32, ptr %570, align 4
  %857 = add i32 %856, 1
  store i32 %857, ptr %570, align 4
  %858 = load i32, ptr %571, align 4
  %859 = add i32 %858, 1
  store i32 %859, ptr %571, align 4
  br label %FillExpr.loopCmp-0236

FillExpr.loopEnd-0238:                            ; preds = %FillExpr.loopCmp-0236
  br label %FillExpr.exit239

FillExpr.exit239:                                 ; preds = %FillExpr.loopEnd-0238
  %860 = getelementptr [4 x float], ptr %569, i32 0, i32 0
  store float 0.000000e+00, ptr %860, align 4
  %861 = getelementptr [4 x float], ptr %569, i32 0, i32 1
  store float 0.000000e+00, ptr %861, align 4
  %862 = getelementptr [4 x float], ptr %569, i32 0, i32 2
  store float 3.840000e+03, ptr %862, align 4
  %863 = getelementptr [4 x float], ptr %569, i32 0, i32 3
  store float 2.160000e+03, ptr %863, align 4
  %864 = load [4 x float], ptr %569, align 4
  %865 = alloca [4 x float], align 4
  %866 = alloca i32, align 4
  %867 = alloca i32, align 4
  store i32 0, ptr %867, align 4
  br label %FillExpr.loopStart-0240

FillExpr.loopStart-0240:                          ; preds = %FillExpr.exit239
  store i32 0, ptr %866, align 4
  br label %FillExpr.loopCmp-0241

FillExpr.loopCmp-0241:                            ; preds = %FillExpr.loopBody-0242, %FillExpr.loopStart-0240
  %868 = load i32, ptr %866, align 4
  %869 = icmp slt i32 %868, 4
  %870 = load i32, ptr %867, align 4
  %871 = icmp slt i32 %870, 4
  %872 = and i1 %869, %871
  br i1 %872, label %FillExpr.loopBody-0242, label %FillExpr.loopEnd-0243

FillExpr.loopBody-0242:                           ; preds = %FillExpr.loopCmp-0241
  %873 = load i32, ptr %866, align 4
  %874 = getelementptr [4 x float], ptr %865, i32 0, i32 %873
  store float 0.000000e+00, ptr %874, align 4
  %875 = load i32, ptr %866, align 4
  %876 = add i32 %875, 1
  store i32 %876, ptr %866, align 4
  %877 = load i32, ptr %867, align 4
  %878 = add i32 %877, 1
  store i32 %878, ptr %867, align 4
  br label %FillExpr.loopCmp-0241

FillExpr.loopEnd-0243:                            ; preds = %FillExpr.loopCmp-0241
  br label %FillExpr.exit244

FillExpr.exit244:                                 ; preds = %FillExpr.loopEnd-0243
  %879 = getelementptr [4 x float], ptr %865, i32 0, i32 0
  store float 0.000000e+00, ptr %879, align 4
  %880 = getelementptr [4 x float], ptr %865, i32 0, i32 1
  store float 0.000000e+00, ptr %880, align 4
  %881 = getelementptr [4 x float], ptr %865, i32 0, i32 2
  %screenWidth245 = load i32, ptr @screenWidth, align 4
  %882 = load i32, ptr @screenWidth, align 4
  %883 = sitofp i32 %882 to float
  store float %883, ptr %881, align 4
  %884 = getelementptr [4 x float], ptr %865, i32 0, i32 3
  %screenHeight246 = load i32, ptr @screenHeight, align 4
  %885 = load i32, ptr @screenHeight, align 4
  %886 = sitofp i32 %885 to float
  store float %886, ptr %884, align 4
  %887 = load [4 x float], ptr %865, align 4
  %888 = alloca [2 x float], align 4
  %889 = alloca i32, align 4
  %890 = alloca i32, align 4
  store i32 0, ptr %890, align 4
  br label %FillExpr.loopStart-0247

FillExpr.loopStart-0247:                          ; preds = %FillExpr.exit244
  store i32 0, ptr %889, align 4
  br label %FillExpr.loopCmp-0248

FillExpr.loopCmp-0248:                            ; preds = %FillExpr.loopBody-0249, %FillExpr.loopStart-0247
  %891 = load i32, ptr %889, align 4
  %892 = icmp slt i32 %891, 2
  %893 = load i32, ptr %890, align 4
  %894 = icmp slt i32 %893, 2
  %895 = and i1 %892, %894
  br i1 %895, label %FillExpr.loopBody-0249, label %FillExpr.loopEnd-0250

FillExpr.loopBody-0249:                           ; preds = %FillExpr.loopCmp-0248
  %896 = load i32, ptr %889, align 4
  %897 = getelementptr [2 x float], ptr %888, i32 0, i32 %896
  store float 0.000000e+00, ptr %897, align 4
  %898 = load i32, ptr %889, align 4
  %899 = add i32 %898, 1
  store i32 %899, ptr %889, align 4
  %900 = load i32, ptr %890, align 4
  %901 = add i32 %900, 1
  store i32 %901, ptr %890, align 4
  br label %FillExpr.loopCmp-0248

FillExpr.loopEnd-0250:                            ; preds = %FillExpr.loopCmp-0248
  br label %FillExpr.exit251

FillExpr.exit251:                                 ; preds = %FillExpr.loopEnd-0250
  %902 = getelementptr [2 x float], ptr %888, i32 0, i32 0
  store float 0.000000e+00, ptr %902, align 4
  %903 = getelementptr [2 x float], ptr %888, i32 0, i32 1
  store float 0.000000e+00, ptr %903, align 4
  %904 = load [2 x float], ptr %888, align 4
  %905 = load ptr, ptr %fgAnim, align 8
  %906 = getelementptr inbounds %FlowWingAnim, ptr %905, i32 0, i32 5
  %907 = getelementptr inbounds %COLORS_TYPE.3, ptr %906, i32 0, i32 0
  %WHITE = load i32, ptr %907, align 4
  %908 = load i32, ptr %907, align 4
  call void @DrawTexturePro(ptr %backgroundTexture, [4 x float] %864, [4 x float] %887, [2 x float] %904, float 0.000000e+00, i32 %908)
  %909 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %910 = icmp eq i32 %909, 0
  br i1 %910, label %checkContinueBlock112, label %afterNestedBlock92

FillExpr.loopStart-0252:                          ; preds = %nestedBlock115
  store i32 0, ptr %585, align 4
  br label %FillExpr.loopCmp-0253

FillExpr.loopCmp-0253:                            ; preds = %FillExpr.loopBody-0254, %FillExpr.loopStart-0252
  %911 = load i32, ptr %585, align 4
  %912 = icmp slt i32 %911, 4
  %913 = load i32, ptr %586, align 4
  %914 = icmp slt i32 %913, 4
  %915 = and i1 %912, %914
  br i1 %915, label %FillExpr.loopBody-0254, label %FillExpr.loopEnd-0255

FillExpr.loopBody-0254:                           ; preds = %FillExpr.loopCmp-0253
  %916 = load i32, ptr %585, align 4
  %917 = getelementptr [4 x float], ptr %584, i32 0, i32 %916
  store float 0.000000e+00, ptr %917, align 4
  %918 = load i32, ptr %585, align 4
  %919 = add i32 %918, 1
  store i32 %919, ptr %585, align 4
  %920 = load i32, ptr %586, align 4
  %921 = add i32 %920, 1
  store i32 %921, ptr %586, align 4
  br label %FillExpr.loopCmp-0253

FillExpr.loopEnd-0255:                            ; preds = %FillExpr.loopCmp-0253
  br label %FillExpr.exit256

FillExpr.exit256:                                 ; preds = %FillExpr.loopEnd-0255
  %922 = getelementptr [4 x float], ptr %584, i32 0, i32 0
  store float 0.000000e+00, ptr %922, align 4
  %923 = getelementptr [4 x float], ptr %584, i32 0, i32 1
  store float 0.000000e+00, ptr %923, align 4
  %924 = getelementptr [4 x float], ptr %584, i32 0, i32 2
  store float 5.975000e+03, ptr %924, align 4
  %925 = getelementptr [4 x float], ptr %584, i32 0, i32 3
  store float 1.607000e+03, ptr %925, align 4
  %926 = load [4 x float], ptr %584, align 4
  %927 = alloca [4 x float], align 4
  %928 = alloca i32, align 4
  %929 = alloca i32, align 4
  store i32 0, ptr %929, align 4
  br label %FillExpr.loopStart-0257

FillExpr.loopStart-0257:                          ; preds = %FillExpr.exit256
  store i32 0, ptr %928, align 4
  br label %FillExpr.loopCmp-0258

FillExpr.loopCmp-0258:                            ; preds = %FillExpr.loopBody-0259, %FillExpr.loopStart-0257
  %930 = load i32, ptr %928, align 4
  %931 = icmp slt i32 %930, 4
  %932 = load i32, ptr %929, align 4
  %933 = icmp slt i32 %932, 4
  %934 = and i1 %931, %933
  br i1 %934, label %FillExpr.loopBody-0259, label %FillExpr.loopEnd-0260

FillExpr.loopBody-0259:                           ; preds = %FillExpr.loopCmp-0258
  %935 = load i32, ptr %928, align 4
  %936 = getelementptr [4 x float], ptr %927, i32 0, i32 %935
  store float 0.000000e+00, ptr %936, align 4
  %937 = load i32, ptr %928, align 4
  %938 = add i32 %937, 1
  store i32 %938, ptr %928, align 4
  %939 = load i32, ptr %929, align 4
  %940 = add i32 %939, 1
  store i32 %940, ptr %929, align 4
  br label %FillExpr.loopCmp-0258

FillExpr.loopEnd-0260:                            ; preds = %FillExpr.loopCmp-0258
  br label %FillExpr.exit261

FillExpr.exit261:                                 ; preds = %FillExpr.loopEnd-0260
  %941 = getelementptr [4 x float], ptr %927, i32 0, i32 0
  store float 0.000000e+00, ptr %941, align 4
  %942 = getelementptr [4 x float], ptr %927, i32 0, i32 1
  %screenHeight262 = load i32, ptr @screenHeight, align 4
  %943 = load i32, ptr @screenHeight, align 4
  %944 = sitofp i32 %943 to double
  %945 = fdiv double %944, 3.000000e+00
  %946 = fptrunc double %945 to float
  store float %946, ptr %942, align 4
  %947 = getelementptr [4 x float], ptr %927, i32 0, i32 2
  %screenWidth263 = load i32, ptr @screenWidth, align 4
  %948 = load i32, ptr @screenWidth, align 4
  %949 = sitofp i32 %948 to double
  %950 = fdiv double %949, 2.000000e+00
  %951 = fptrunc double %950 to float
  store float %951, ptr %947, align 4
  %952 = getelementptr [4 x float], ptr %927, i32 0, i32 3
  %screenHeight264 = load i32, ptr @screenHeight, align 4
  %953 = load i32, ptr @screenHeight, align 4
  %954 = sitofp i32 %953 to double
  %955 = fdiv double %954, 3.000000e+00
  %956 = fptrunc double %955 to float
  store float %956, ptr %952, align 4
  %957 = load [4 x float], ptr %927, align 4
  %958 = alloca [2 x float], align 4
  %959 = alloca i32, align 4
  %960 = alloca i32, align 4
  store i32 0, ptr %960, align 4
  br label %FillExpr.loopStart-0265

FillExpr.loopStart-0265:                          ; preds = %FillExpr.exit261
  store i32 0, ptr %959, align 4
  br label %FillExpr.loopCmp-0266

FillExpr.loopCmp-0266:                            ; preds = %FillExpr.loopBody-0267, %FillExpr.loopStart-0265
  %961 = load i32, ptr %959, align 4
  %962 = icmp slt i32 %961, 2
  %963 = load i32, ptr %960, align 4
  %964 = icmp slt i32 %963, 2
  %965 = and i1 %962, %964
  br i1 %965, label %FillExpr.loopBody-0267, label %FillExpr.loopEnd-0268

FillExpr.loopBody-0267:                           ; preds = %FillExpr.loopCmp-0266
  %966 = load i32, ptr %959, align 4
  %967 = getelementptr [2 x float], ptr %958, i32 0, i32 %966
  store float 0.000000e+00, ptr %967, align 4
  %968 = load i32, ptr %959, align 4
  %969 = add i32 %968, 1
  store i32 %969, ptr %959, align 4
  %970 = load i32, ptr %960, align 4
  %971 = add i32 %970, 1
  store i32 %971, ptr %960, align 4
  br label %FillExpr.loopCmp-0266

FillExpr.loopEnd-0268:                            ; preds = %FillExpr.loopCmp-0266
  br label %FillExpr.exit269

FillExpr.exit269:                                 ; preds = %FillExpr.loopEnd-0268
  %972 = getelementptr [2 x float], ptr %958, i32 0, i32 0
  %973 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x270 = load float, ptr %973, align 4
  %974 = load float, ptr %973, align 4
  store float %974, ptr %972, align 4
  %975 = getelementptr [2 x float], ptr %958, i32 0, i32 1
  %976 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  %y = load float, ptr %976, align 4
  %977 = load float, ptr %976, align 4
  store float %977, ptr %975, align 4
  %978 = load [2 x float], ptr %958, align 4
  %979 = load ptr, ptr %fgAnim, align 8
  %980 = getelementptr inbounds %FlowWingAnim, ptr %979, i32 0, i32 5
  %981 = getelementptr inbounds %COLORS_TYPE.3, ptr %980, i32 0, i32 0
  %WHITE271 = load i32, ptr %981, align 4
  %982 = load i32, ptr %981, align 4
  call void @DrawTexturePro(ptr %mountL2Texture, [4 x float] %926, [4 x float] %957, [2 x float] %978, float 0.000000e+00, i32 %982)
  %983 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %984 = icmp eq i32 %983, 0
  br i1 %984, label %checkContinueBlock116, label %afterNestedBlock92

FillExpr.loopStart-0272:                          ; preds = %nestedBlock117
  store i32 0, ptr %590, align 4
  br label %FillExpr.loopCmp-0273

FillExpr.loopCmp-0273:                            ; preds = %FillExpr.loopBody-0274, %FillExpr.loopStart-0272
  %985 = load i32, ptr %590, align 4
  %986 = icmp slt i32 %985, 4
  %987 = load i32, ptr %591, align 4
  %988 = icmp slt i32 %987, 4
  %989 = and i1 %986, %988
  br i1 %989, label %FillExpr.loopBody-0274, label %FillExpr.loopEnd-0275

FillExpr.loopBody-0274:                           ; preds = %FillExpr.loopCmp-0273
  %990 = load i32, ptr %590, align 4
  %991 = getelementptr [4 x float], ptr %589, i32 0, i32 %990
  store float 0.000000e+00, ptr %991, align 4
  %992 = load i32, ptr %590, align 4
  %993 = add i32 %992, 1
  store i32 %993, ptr %590, align 4
  %994 = load i32, ptr %591, align 4
  %995 = add i32 %994, 1
  store i32 %995, ptr %591, align 4
  br label %FillExpr.loopCmp-0273

FillExpr.loopEnd-0275:                            ; preds = %FillExpr.loopCmp-0273
  br label %FillExpr.exit276

FillExpr.exit276:                                 ; preds = %FillExpr.loopEnd-0275
  %996 = getelementptr [4 x float], ptr %589, i32 0, i32 0
  store float 0.000000e+00, ptr %996, align 4
  %997 = getelementptr [4 x float], ptr %589, i32 0, i32 1
  store float 0.000000e+00, ptr %997, align 4
  %998 = getelementptr [4 x float], ptr %589, i32 0, i32 2
  store float 4.461000e+03, ptr %998, align 4
  %999 = getelementptr [4 x float], ptr %589, i32 0, i32 3
  store float 1.989000e+03, ptr %999, align 4
  %1000 = load [4 x float], ptr %589, align 4
  %1001 = alloca [4 x float], align 4
  %1002 = alloca i32, align 4
  %1003 = alloca i32, align 4
  store i32 0, ptr %1003, align 4
  br label %FillExpr.loopStart-0277

FillExpr.loopStart-0277:                          ; preds = %FillExpr.exit276
  store i32 0, ptr %1002, align 4
  br label %FillExpr.loopCmp-0278

FillExpr.loopCmp-0278:                            ; preds = %FillExpr.loopBody-0279, %FillExpr.loopStart-0277
  %1004 = load i32, ptr %1002, align 4
  %1005 = icmp slt i32 %1004, 4
  %1006 = load i32, ptr %1003, align 4
  %1007 = icmp slt i32 %1006, 4
  %1008 = and i1 %1005, %1007
  br i1 %1008, label %FillExpr.loopBody-0279, label %FillExpr.loopEnd-0280

FillExpr.loopBody-0279:                           ; preds = %FillExpr.loopCmp-0278
  %1009 = load i32, ptr %1002, align 4
  %1010 = getelementptr [4 x float], ptr %1001, i32 0, i32 %1009
  store float 0.000000e+00, ptr %1010, align 4
  %1011 = load i32, ptr %1002, align 4
  %1012 = add i32 %1011, 1
  store i32 %1012, ptr %1002, align 4
  %1013 = load i32, ptr %1003, align 4
  %1014 = add i32 %1013, 1
  store i32 %1014, ptr %1003, align 4
  br label %FillExpr.loopCmp-0278

FillExpr.loopEnd-0280:                            ; preds = %FillExpr.loopCmp-0278
  br label %FillExpr.exit281

FillExpr.exit281:                                 ; preds = %FillExpr.loopEnd-0280
  %1015 = getelementptr [4 x float], ptr %1001, i32 0, i32 0
  store float 0.000000e+00, ptr %1015, align 4
  %1016 = getelementptr [4 x float], ptr %1001, i32 0, i32 1
  %screenHeight282 = load i32, ptr @screenHeight, align 4
  %1017 = load i32, ptr @screenHeight, align 4
  %1018 = sitofp i32 %1017 to double
  %1019 = fdiv double %1018, 3.000000e+00
  %1020 = fptrunc double %1019 to float
  store float %1020, ptr %1016, align 4
  %1021 = getelementptr [4 x float], ptr %1001, i32 0, i32 2
  %screenWidth283 = load i32, ptr @screenWidth, align 4
  %1022 = load i32, ptr @screenWidth, align 4
  %1023 = sitofp i32 %1022 to double
  %1024 = fdiv double %1023, 2.000000e+00
  %1025 = fptrunc double %1024 to float
  store float %1025, ptr %1021, align 4
  %1026 = getelementptr [4 x float], ptr %1001, i32 0, i32 3
  %screenHeight284 = load i32, ptr @screenHeight, align 4
  %1027 = load i32, ptr @screenHeight, align 4
  %1028 = sitofp i32 %1027 to double
  %1029 = fdiv double %1028, 3.000000e+00
  %1030 = fptrunc double %1029 to float
  store float %1030, ptr %1026, align 4
  %1031 = load [4 x float], ptr %1001, align 4
  %1032 = alloca [2 x float], align 4
  %1033 = alloca i32, align 4
  %1034 = alloca i32, align 4
  store i32 0, ptr %1034, align 4
  br label %FillExpr.loopStart-0285

FillExpr.loopStart-0285:                          ; preds = %FillExpr.exit281
  store i32 0, ptr %1033, align 4
  br label %FillExpr.loopCmp-0286

FillExpr.loopCmp-0286:                            ; preds = %FillExpr.loopBody-0287, %FillExpr.loopStart-0285
  %1035 = load i32, ptr %1033, align 4
  %1036 = icmp slt i32 %1035, 2
  %1037 = load i32, ptr %1034, align 4
  %1038 = icmp slt i32 %1037, 2
  %1039 = and i1 %1036, %1038
  br i1 %1039, label %FillExpr.loopBody-0287, label %FillExpr.loopEnd-0288

FillExpr.loopBody-0287:                           ; preds = %FillExpr.loopCmp-0286
  %1040 = load i32, ptr %1033, align 4
  %1041 = getelementptr [2 x float], ptr %1032, i32 0, i32 %1040
  store float 0.000000e+00, ptr %1041, align 4
  %1042 = load i32, ptr %1033, align 4
  %1043 = add i32 %1042, 1
  store i32 %1043, ptr %1033, align 4
  %1044 = load i32, ptr %1034, align 4
  %1045 = add i32 %1044, 1
  store i32 %1045, ptr %1034, align 4
  br label %FillExpr.loopCmp-0286

FillExpr.loopEnd-0288:                            ; preds = %FillExpr.loopCmp-0286
  br label %FillExpr.exit289

FillExpr.exit289:                                 ; preds = %FillExpr.loopEnd-0288
  %1046 = getelementptr [2 x float], ptr %1032, i32 0, i32 0
  %1047 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x290 = load float, ptr %1047, align 4
  %1048 = load float, ptr %1047, align 4
  store float %1048, ptr %1046, align 4
  %1049 = getelementptr [2 x float], ptr %1032, i32 0, i32 1
  %1050 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  %y291 = load float, ptr %1050, align 4
  %1051 = load float, ptr %1050, align 4
  store float %1051, ptr %1049, align 4
  %1052 = load [2 x float], ptr %1032, align 4
  %1053 = load ptr, ptr %fgAnim, align 8
  %1054 = getelementptr inbounds %FlowWingAnim, ptr %1053, i32 0, i32 5
  %1055 = getelementptr inbounds %COLORS_TYPE.3, ptr %1054, i32 0, i32 0
  %WHITE292 = load i32, ptr %1055, align 4
  %1056 = load i32, ptr %1055, align 4
  call void @DrawTexturePro(ptr %mount2L2Texture, [4 x float] %1000, [4 x float] %1031, [2 x float] %1052, float 0.000000e+00, i32 %1056)
  %1057 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1058 = icmp eq i32 %1057, 0
  br i1 %1058, label %checkContinueBlock118, label %afterNestedBlock92

FillExpr.loopStart-0293:                          ; preds = %nestedBlock119
  store i32 0, ptr %595, align 4
  br label %FillExpr.loopCmp-0294

FillExpr.loopCmp-0294:                            ; preds = %FillExpr.loopBody-0295, %FillExpr.loopStart-0293
  %1059 = load i32, ptr %595, align 4
  %1060 = icmp slt i32 %1059, 4
  %1061 = load i32, ptr %596, align 4
  %1062 = icmp slt i32 %1061, 4
  %1063 = and i1 %1060, %1062
  br i1 %1063, label %FillExpr.loopBody-0295, label %FillExpr.loopEnd-0296

FillExpr.loopBody-0295:                           ; preds = %FillExpr.loopCmp-0294
  %1064 = load i32, ptr %595, align 4
  %1065 = getelementptr [4 x float], ptr %594, i32 0, i32 %1064
  store float 0.000000e+00, ptr %1065, align 4
  %1066 = load i32, ptr %595, align 4
  %1067 = add i32 %1066, 1
  store i32 %1067, ptr %595, align 4
  %1068 = load i32, ptr %596, align 4
  %1069 = add i32 %1068, 1
  store i32 %1069, ptr %596, align 4
  br label %FillExpr.loopCmp-0294

FillExpr.loopEnd-0296:                            ; preds = %FillExpr.loopCmp-0294
  br label %FillExpr.exit297

FillExpr.exit297:                                 ; preds = %FillExpr.loopEnd-0296
  %1070 = getelementptr [4 x float], ptr %594, i32 0, i32 0
  store float 0.000000e+00, ptr %1070, align 4
  %1071 = getelementptr [4 x float], ptr %594, i32 0, i32 1
  store float 0.000000e+00, ptr %1071, align 4
  %1072 = getelementptr [4 x float], ptr %594, i32 0, i32 2
  store float 6.005000e+03, ptr %1072, align 4
  %1073 = getelementptr [4 x float], ptr %594, i32 0, i32 3
  store float 2.376000e+03, ptr %1073, align 4
  %1074 = load [4 x float], ptr %594, align 4
  %1075 = alloca [4 x float], align 4
  %1076 = alloca i32, align 4
  %1077 = alloca i32, align 4
  store i32 0, ptr %1077, align 4
  br label %FillExpr.loopStart-0298

FillExpr.loopStart-0298:                          ; preds = %FillExpr.exit297
  store i32 0, ptr %1076, align 4
  br label %FillExpr.loopCmp-0299

FillExpr.loopCmp-0299:                            ; preds = %FillExpr.loopBody-0300, %FillExpr.loopStart-0298
  %1078 = load i32, ptr %1076, align 4
  %1079 = icmp slt i32 %1078, 4
  %1080 = load i32, ptr %1077, align 4
  %1081 = icmp slt i32 %1080, 4
  %1082 = and i1 %1079, %1081
  br i1 %1082, label %FillExpr.loopBody-0300, label %FillExpr.loopEnd-0301

FillExpr.loopBody-0300:                           ; preds = %FillExpr.loopCmp-0299
  %1083 = load i32, ptr %1076, align 4
  %1084 = getelementptr [4 x float], ptr %1075, i32 0, i32 %1083
  store float 0.000000e+00, ptr %1084, align 4
  %1085 = load i32, ptr %1076, align 4
  %1086 = add i32 %1085, 1
  store i32 %1086, ptr %1076, align 4
  %1087 = load i32, ptr %1077, align 4
  %1088 = add i32 %1087, 1
  store i32 %1088, ptr %1077, align 4
  br label %FillExpr.loopCmp-0299

FillExpr.loopEnd-0301:                            ; preds = %FillExpr.loopCmp-0299
  br label %FillExpr.exit302

FillExpr.exit302:                                 ; preds = %FillExpr.loopEnd-0301
  %1089 = getelementptr [4 x float], ptr %1075, i32 0, i32 0
  store float 0.000000e+00, ptr %1089, align 4
  %1090 = getelementptr [4 x float], ptr %1075, i32 0, i32 1
  %screenHeight303 = load i32, ptr @screenHeight, align 4
  %1091 = load i32, ptr @screenHeight, align 4
  %1092 = sitofp i32 %1091 to double
  %1093 = fdiv double %1092, 3.000000e+00
  %1094 = fptrunc double %1093 to float
  store float %1094, ptr %1090, align 4
  %1095 = getelementptr [4 x float], ptr %1075, i32 0, i32 2
  %screenWidth304 = load i32, ptr @screenWidth, align 4
  %1096 = load i32, ptr @screenWidth, align 4
  %1097 = sitofp i32 %1096 to double
  %1098 = fdiv double %1097, 2.000000e+00
  %1099 = fptrunc double %1098 to float
  store float %1099, ptr %1095, align 4
  %1100 = getelementptr [4 x float], ptr %1075, i32 0, i32 3
  %screenHeight305 = load i32, ptr @screenHeight, align 4
  %1101 = load i32, ptr @screenHeight, align 4
  %1102 = sitofp i32 %1101 to double
  %1103 = fdiv double %1102, 3.000000e+00
  %1104 = fptrunc double %1103 to float
  store float %1104, ptr %1100, align 4
  %1105 = load [4 x float], ptr %1075, align 4
  %1106 = alloca [2 x float], align 4
  %1107 = alloca i32, align 4
  %1108 = alloca i32, align 4
  store i32 0, ptr %1108, align 4
  br label %FillExpr.loopStart-0306

FillExpr.loopStart-0306:                          ; preds = %FillExpr.exit302
  store i32 0, ptr %1107, align 4
  br label %FillExpr.loopCmp-0307

FillExpr.loopCmp-0307:                            ; preds = %FillExpr.loopBody-0308, %FillExpr.loopStart-0306
  %1109 = load i32, ptr %1107, align 4
  %1110 = icmp slt i32 %1109, 2
  %1111 = load i32, ptr %1108, align 4
  %1112 = icmp slt i32 %1111, 2
  %1113 = and i1 %1110, %1112
  br i1 %1113, label %FillExpr.loopBody-0308, label %FillExpr.loopEnd-0309

FillExpr.loopBody-0308:                           ; preds = %FillExpr.loopCmp-0307
  %1114 = load i32, ptr %1107, align 4
  %1115 = getelementptr [2 x float], ptr %1106, i32 0, i32 %1114
  store float 0.000000e+00, ptr %1115, align 4
  %1116 = load i32, ptr %1107, align 4
  %1117 = add i32 %1116, 1
  store i32 %1117, ptr %1107, align 4
  %1118 = load i32, ptr %1108, align 4
  %1119 = add i32 %1118, 1
  store i32 %1119, ptr %1108, align 4
  br label %FillExpr.loopCmp-0307

FillExpr.loopEnd-0309:                            ; preds = %FillExpr.loopCmp-0307
  br label %FillExpr.exit310

FillExpr.exit310:                                 ; preds = %FillExpr.loopEnd-0309
  %1120 = getelementptr [2 x float], ptr %1106, i32 0, i32 0
  %1121 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x311 = load float, ptr %1121, align 4
  %1122 = load float, ptr %1121, align 4
  store float %1122, ptr %1120, align 4
  %1123 = getelementptr [2 x float], ptr %1106, i32 0, i32 1
  %1124 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  %y312 = load float, ptr %1124, align 4
  %1125 = load float, ptr %1124, align 4
  store float %1125, ptr %1123, align 4
  %1126 = load [2 x float], ptr %1106, align 4
  %1127 = load ptr, ptr %fgAnim, align 8
  %1128 = getelementptr inbounds %FlowWingAnim, ptr %1127, i32 0, i32 5
  %1129 = getelementptr inbounds %COLORS_TYPE.3, ptr %1128, i32 0, i32 0
  %WHITE313 = load i32, ptr %1129, align 4
  %1130 = load i32, ptr %1129, align 4
  call void @DrawTexturePro(ptr %mount1L3Texture, [4 x float] %1074, [4 x float] %1105, [2 x float] %1126, float 0.000000e+00, i32 %1130)
  %1131 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1132 = icmp eq i32 %1131, 0
  br i1 %1132, label %checkContinueBlock120, label %afterNestedBlock92

FillExpr.loopStart-0314:                          ; preds = %nestedBlock121
  store i32 0, ptr %600, align 4
  br label %FillExpr.loopCmp-0315

FillExpr.loopCmp-0315:                            ; preds = %FillExpr.loopBody-0316, %FillExpr.loopStart-0314
  %1133 = load i32, ptr %600, align 4
  %1134 = icmp slt i32 %1133, 4
  %1135 = load i32, ptr %601, align 4
  %1136 = icmp slt i32 %1135, 4
  %1137 = and i1 %1134, %1136
  br i1 %1137, label %FillExpr.loopBody-0316, label %FillExpr.loopEnd-0317

FillExpr.loopBody-0316:                           ; preds = %FillExpr.loopCmp-0315
  %1138 = load i32, ptr %600, align 4
  %1139 = getelementptr [4 x float], ptr %599, i32 0, i32 %1138
  store float 0.000000e+00, ptr %1139, align 4
  %1140 = load i32, ptr %600, align 4
  %1141 = add i32 %1140, 1
  store i32 %1141, ptr %600, align 4
  %1142 = load i32, ptr %601, align 4
  %1143 = add i32 %1142, 1
  store i32 %1143, ptr %601, align 4
  br label %FillExpr.loopCmp-0315

FillExpr.loopEnd-0317:                            ; preds = %FillExpr.loopCmp-0315
  br label %FillExpr.exit318

FillExpr.exit318:                                 ; preds = %FillExpr.loopEnd-0317
  %1144 = getelementptr [4 x float], ptr %599, i32 0, i32 0
  store float 0.000000e+00, ptr %1144, align 4
  %1145 = getelementptr [4 x float], ptr %599, i32 0, i32 1
  store float 0.000000e+00, ptr %1145, align 4
  %1146 = getelementptr [4 x float], ptr %599, i32 0, i32 2
  store float 8.982000e+03, ptr %1146, align 4
  %1147 = getelementptr [4 x float], ptr %599, i32 0, i32 3
  store float 1.542000e+03, ptr %1147, align 4
  %1148 = load [4 x float], ptr %599, align 4
  %1149 = alloca [4 x float], align 4
  %1150 = alloca i32, align 4
  %1151 = alloca i32, align 4
  store i32 0, ptr %1151, align 4
  br label %FillExpr.loopStart-0319

FillExpr.loopStart-0319:                          ; preds = %FillExpr.exit318
  store i32 0, ptr %1150, align 4
  br label %FillExpr.loopCmp-0320

FillExpr.loopCmp-0320:                            ; preds = %FillExpr.loopBody-0321, %FillExpr.loopStart-0319
  %1152 = load i32, ptr %1150, align 4
  %1153 = icmp slt i32 %1152, 4
  %1154 = load i32, ptr %1151, align 4
  %1155 = icmp slt i32 %1154, 4
  %1156 = and i1 %1153, %1155
  br i1 %1156, label %FillExpr.loopBody-0321, label %FillExpr.loopEnd-0322

FillExpr.loopBody-0321:                           ; preds = %FillExpr.loopCmp-0320
  %1157 = load i32, ptr %1150, align 4
  %1158 = getelementptr [4 x float], ptr %1149, i32 0, i32 %1157
  store float 0.000000e+00, ptr %1158, align 4
  %1159 = load i32, ptr %1150, align 4
  %1160 = add i32 %1159, 1
  store i32 %1160, ptr %1150, align 4
  %1161 = load i32, ptr %1151, align 4
  %1162 = add i32 %1161, 1
  store i32 %1162, ptr %1151, align 4
  br label %FillExpr.loopCmp-0320

FillExpr.loopEnd-0322:                            ; preds = %FillExpr.loopCmp-0320
  br label %FillExpr.exit323

FillExpr.exit323:                                 ; preds = %FillExpr.loopEnd-0322
  %1163 = getelementptr [4 x float], ptr %1149, i32 0, i32 0
  store float 0.000000e+00, ptr %1163, align 4
  %1164 = getelementptr [4 x float], ptr %1149, i32 0, i32 1
  %screenHeight324 = load i32, ptr @screenHeight, align 4
  %1165 = load i32, ptr @screenHeight, align 4
  %1166 = sitofp i32 %1165 to double
  %1167 = fdiv double %1166, 3.000000e+00
  %1168 = fptrunc double %1167 to float
  store float %1168, ptr %1164, align 4
  %1169 = getelementptr [4 x float], ptr %1149, i32 0, i32 2
  %screenWidth325 = load i32, ptr @screenWidth, align 4
  %1170 = load i32, ptr @screenWidth, align 4
  %screenWidth326 = load i32, ptr @screenWidth, align 4
  %1171 = load i32, ptr @screenWidth, align 4
  %1172 = sitofp i32 %1171 to double
  %1173 = fdiv double %1172, 2.000000e+00
  %1174 = sitofp i32 %1170 to double
  %1175 = fadd double %1174, %1173
  %1176 = fptrunc double %1175 to float
  store float %1176, ptr %1169, align 4
  %1177 = getelementptr [4 x float], ptr %1149, i32 0, i32 3
  %screenHeight327 = load i32, ptr @screenHeight, align 4
  %1178 = load i32, ptr @screenHeight, align 4
  %1179 = sitofp i32 %1178 to double
  %1180 = fdiv double %1179, 3.000000e+00
  %1181 = fptrunc double %1180 to float
  store float %1181, ptr %1177, align 4
  %1182 = load [4 x float], ptr %1149, align 4
  %1183 = alloca [2 x float], align 4
  %1184 = alloca i32, align 4
  %1185 = alloca i32, align 4
  store i32 0, ptr %1185, align 4
  br label %FillExpr.loopStart-0328

FillExpr.loopStart-0328:                          ; preds = %FillExpr.exit323
  store i32 0, ptr %1184, align 4
  br label %FillExpr.loopCmp-0329

FillExpr.loopCmp-0329:                            ; preds = %FillExpr.loopBody-0330, %FillExpr.loopStart-0328
  %1186 = load i32, ptr %1184, align 4
  %1187 = icmp slt i32 %1186, 2
  %1188 = load i32, ptr %1185, align 4
  %1189 = icmp slt i32 %1188, 2
  %1190 = and i1 %1187, %1189
  br i1 %1190, label %FillExpr.loopBody-0330, label %FillExpr.loopEnd-0331

FillExpr.loopBody-0330:                           ; preds = %FillExpr.loopCmp-0329
  %1191 = load i32, ptr %1184, align 4
  %1192 = getelementptr [2 x float], ptr %1183, i32 0, i32 %1191
  store float 0.000000e+00, ptr %1192, align 4
  %1193 = load i32, ptr %1184, align 4
  %1194 = add i32 %1193, 1
  store i32 %1194, ptr %1184, align 4
  %1195 = load i32, ptr %1185, align 4
  %1196 = add i32 %1195, 1
  store i32 %1196, ptr %1185, align 4
  br label %FillExpr.loopCmp-0329

FillExpr.loopEnd-0331:                            ; preds = %FillExpr.loopCmp-0329
  br label %FillExpr.exit332

FillExpr.exit332:                                 ; preds = %FillExpr.loopEnd-0331
  %1197 = getelementptr [2 x float], ptr %1183, i32 0, i32 0
  %1198 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x333 = load float, ptr %1198, align 4
  %1199 = load float, ptr %1198, align 4
  store float %1199, ptr %1197, align 4
  %1200 = getelementptr [2 x float], ptr %1183, i32 0, i32 1
  %1201 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y334 = load float, ptr %1201, align 4
  %1202 = load float, ptr %1201, align 4
  store float %1202, ptr %1200, align 4
  %1203 = load [2 x float], ptr %1183, align 4
  %1204 = load ptr, ptr %fgAnim, align 8
  %1205 = getelementptr inbounds %FlowWingAnim, ptr %1204, i32 0, i32 5
  %1206 = getelementptr inbounds %COLORS_TYPE.3, ptr %1205, i32 0, i32 0
  %WHITE335 = load i32, ptr %1206, align 4
  %1207 = load i32, ptr %1206, align 4
  call void @DrawTexturePro(ptr %mountL1Texture, [4 x float] %1148, [4 x float] %1182, [2 x float] %1203, float 0.000000e+00, i32 %1207)
  %1208 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1209 = icmp eq i32 %1208, 0
  br i1 %1209, label %checkContinueBlock122, label %afterNestedBlock92

FillExpr.loopStart-0336:                          ; preds = %nestedBlock123
  store i32 0, ptr %605, align 4
  br label %FillExpr.loopCmp-0337

FillExpr.loopCmp-0337:                            ; preds = %FillExpr.loopBody-0338, %FillExpr.loopStart-0336
  %1210 = load i32, ptr %605, align 4
  %1211 = icmp slt i32 %1210, 4
  %1212 = load i32, ptr %606, align 4
  %1213 = icmp slt i32 %1212, 4
  %1214 = and i1 %1211, %1213
  br i1 %1214, label %FillExpr.loopBody-0338, label %FillExpr.loopEnd-0339

FillExpr.loopBody-0338:                           ; preds = %FillExpr.loopCmp-0337
  %1215 = load i32, ptr %605, align 4
  %1216 = getelementptr [4 x float], ptr %604, i32 0, i32 %1215
  store float 0.000000e+00, ptr %1216, align 4
  %1217 = load i32, ptr %605, align 4
  %1218 = add i32 %1217, 1
  store i32 %1218, ptr %605, align 4
  %1219 = load i32, ptr %606, align 4
  %1220 = add i32 %1219, 1
  store i32 %1220, ptr %606, align 4
  br label %FillExpr.loopCmp-0337

FillExpr.loopEnd-0339:                            ; preds = %FillExpr.loopCmp-0337
  br label %FillExpr.exit340

FillExpr.exit340:                                 ; preds = %FillExpr.loopEnd-0339
  %1221 = getelementptr [4 x float], ptr %604, i32 0, i32 0
  store float 0.000000e+00, ptr %1221, align 4
  %1222 = getelementptr [4 x float], ptr %604, i32 0, i32 1
  store float 0.000000e+00, ptr %1222, align 4
  %1223 = getelementptr [4 x float], ptr %604, i32 0, i32 2
  store float 8.982000e+03, ptr %1223, align 4
  %1224 = getelementptr [4 x float], ptr %604, i32 0, i32 3
  store float 1.542000e+03, ptr %1224, align 4
  %1225 = load [4 x float], ptr %604, align 4
  %1226 = alloca [4 x float], align 4
  %1227 = alloca i32, align 4
  %1228 = alloca i32, align 4
  store i32 0, ptr %1228, align 4
  br label %FillExpr.loopStart-0341

FillExpr.loopStart-0341:                          ; preds = %FillExpr.exit340
  store i32 0, ptr %1227, align 4
  br label %FillExpr.loopCmp-0342

FillExpr.loopCmp-0342:                            ; preds = %FillExpr.loopBody-0343, %FillExpr.loopStart-0341
  %1229 = load i32, ptr %1227, align 4
  %1230 = icmp slt i32 %1229, 4
  %1231 = load i32, ptr %1228, align 4
  %1232 = icmp slt i32 %1231, 4
  %1233 = and i1 %1230, %1232
  br i1 %1233, label %FillExpr.loopBody-0343, label %FillExpr.loopEnd-0344

FillExpr.loopBody-0343:                           ; preds = %FillExpr.loopCmp-0342
  %1234 = load i32, ptr %1227, align 4
  %1235 = getelementptr [4 x float], ptr %1226, i32 0, i32 %1234
  store float 0.000000e+00, ptr %1235, align 4
  %1236 = load i32, ptr %1227, align 4
  %1237 = add i32 %1236, 1
  store i32 %1237, ptr %1227, align 4
  %1238 = load i32, ptr %1228, align 4
  %1239 = add i32 %1238, 1
  store i32 %1239, ptr %1228, align 4
  br label %FillExpr.loopCmp-0342

FillExpr.loopEnd-0344:                            ; preds = %FillExpr.loopCmp-0342
  br label %FillExpr.exit345

FillExpr.exit345:                                 ; preds = %FillExpr.loopEnd-0344
  %1240 = getelementptr [4 x float], ptr %1226, i32 0, i32 0
  store float 0.000000e+00, ptr %1240, align 4
  %1241 = getelementptr [4 x float], ptr %1226, i32 0, i32 1
  %screenHeight346 = load i32, ptr @screenHeight, align 4
  %1242 = load i32, ptr @screenHeight, align 4
  %1243 = sitofp i32 %1242 to double
  %1244 = fdiv double %1243, 3.000000e+00
  %1245 = fptrunc double %1244 to float
  store float %1245, ptr %1241, align 4
  %1246 = getelementptr [4 x float], ptr %1226, i32 0, i32 2
  %screenWidth347 = load i32, ptr @screenWidth, align 4
  %1247 = load i32, ptr @screenWidth, align 4
  %screenWidth348 = load i32, ptr @screenWidth, align 4
  %1248 = load i32, ptr @screenWidth, align 4
  %1249 = sitofp i32 %1248 to double
  %1250 = fdiv double %1249, 2.000000e+00
  %1251 = sitofp i32 %1247 to double
  %1252 = fadd double %1251, %1250
  %1253 = fptrunc double %1252 to float
  store float %1253, ptr %1246, align 4
  %1254 = getelementptr [4 x float], ptr %1226, i32 0, i32 3
  %screenHeight349 = load i32, ptr @screenHeight, align 4
  %1255 = load i32, ptr @screenHeight, align 4
  %1256 = sitofp i32 %1255 to double
  %1257 = fdiv double %1256, 3.000000e+00
  %1258 = fptrunc double %1257 to float
  store float %1258, ptr %1254, align 4
  %1259 = load [4 x float], ptr %1226, align 4
  %1260 = alloca [2 x float], align 4
  %1261 = alloca i32, align 4
  %1262 = alloca i32, align 4
  store i32 0, ptr %1262, align 4
  br label %FillExpr.loopStart-0350

FillExpr.loopStart-0350:                          ; preds = %FillExpr.exit345
  store i32 0, ptr %1261, align 4
  br label %FillExpr.loopCmp-0351

FillExpr.loopCmp-0351:                            ; preds = %FillExpr.loopBody-0352, %FillExpr.loopStart-0350
  %1263 = load i32, ptr %1261, align 4
  %1264 = icmp slt i32 %1263, 2
  %1265 = load i32, ptr %1262, align 4
  %1266 = icmp slt i32 %1265, 2
  %1267 = and i1 %1264, %1266
  br i1 %1267, label %FillExpr.loopBody-0352, label %FillExpr.loopEnd-0353

FillExpr.loopBody-0352:                           ; preds = %FillExpr.loopCmp-0351
  %1268 = load i32, ptr %1261, align 4
  %1269 = getelementptr [2 x float], ptr %1260, i32 0, i32 %1268
  store float 0.000000e+00, ptr %1269, align 4
  %1270 = load i32, ptr %1261, align 4
  %1271 = add i32 %1270, 1
  store i32 %1271, ptr %1261, align 4
  %1272 = load i32, ptr %1262, align 4
  %1273 = add i32 %1272, 1
  store i32 %1273, ptr %1262, align 4
  br label %FillExpr.loopCmp-0351

FillExpr.loopEnd-0353:                            ; preds = %FillExpr.loopCmp-0351
  br label %FillExpr.exit354

FillExpr.exit354:                                 ; preds = %FillExpr.loopEnd-0353
  %1274 = getelementptr [2 x float], ptr %1260, i32 0, i32 0
  %1275 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x355 = load float, ptr %1275, align 4
  %1276 = load float, ptr %1275, align 4
  store float %1276, ptr %1274, align 4
  %1277 = getelementptr [2 x float], ptr %1260, i32 0, i32 1
  %1278 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y356 = load float, ptr %1278, align 4
  %1279 = load float, ptr %1278, align 4
  store float %1279, ptr %1277, align 4
  %1280 = load [2 x float], ptr %1260, align 4
  %1281 = load ptr, ptr %fgAnim, align 8
  %1282 = getelementptr inbounds %FlowWingAnim, ptr %1281, i32 0, i32 5
  %1283 = getelementptr inbounds %COLORS_TYPE.3, ptr %1282, i32 0, i32 0
  %WHITE357 = load i32, ptr %1283, align 4
  %1284 = load i32, ptr %1283, align 4
  call void @DrawTexturePro(ptr %mountL1Texture, [4 x float] %1225, [4 x float] %1259, [2 x float] %1280, float 0.000000e+00, i32 %1284)
  %1285 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1286 = icmp eq i32 %1285, 0
  br i1 %1286, label %checkContinueBlock124, label %afterNestedBlock92

FillExpr.loopStart-0358:                          ; preds = %nestedBlock125
  store i32 0, ptr %610, align 4
  br label %FillExpr.loopCmp-0359

FillExpr.loopCmp-0359:                            ; preds = %FillExpr.loopBody-0360, %FillExpr.loopStart-0358
  %1287 = load i32, ptr %610, align 4
  %1288 = icmp slt i32 %1287, 4
  %1289 = load i32, ptr %611, align 4
  %1290 = icmp slt i32 %1289, 4
  %1291 = and i1 %1288, %1290
  br i1 %1291, label %FillExpr.loopBody-0360, label %FillExpr.loopEnd-0361

FillExpr.loopBody-0360:                           ; preds = %FillExpr.loopCmp-0359
  %1292 = load i32, ptr %610, align 4
  %1293 = getelementptr [4 x float], ptr %609, i32 0, i32 %1292
  store float 0.000000e+00, ptr %1293, align 4
  %1294 = load i32, ptr %610, align 4
  %1295 = add i32 %1294, 1
  store i32 %1295, ptr %610, align 4
  %1296 = load i32, ptr %611, align 4
  %1297 = add i32 %1296, 1
  store i32 %1297, ptr %611, align 4
  br label %FillExpr.loopCmp-0359

FillExpr.loopEnd-0361:                            ; preds = %FillExpr.loopCmp-0359
  br label %FillExpr.exit362

FillExpr.exit362:                                 ; preds = %FillExpr.loopEnd-0361
  %1298 = getelementptr [4 x float], ptr %609, i32 0, i32 0
  store float 3.100000e+02, ptr %1298, align 4
  %1299 = getelementptr [4 x float], ptr %609, i32 0, i32 1
  store float 1.250000e+03, ptr %1299, align 4
  %1300 = getelementptr [4 x float], ptr %609, i32 0, i32 2
  store float 4.360000e+03, ptr %1300, align 4
  %1301 = getelementptr [4 x float], ptr %609, i32 0, i32 3
  store float 1.250000e+03, ptr %1301, align 4
  %1302 = load [4 x float], ptr %609, align 4
  %1303 = alloca [4 x float], align 4
  %1304 = alloca i32, align 4
  %1305 = alloca i32, align 4
  store i32 0, ptr %1305, align 4
  br label %FillExpr.loopStart-0363

FillExpr.loopStart-0363:                          ; preds = %FillExpr.exit362
  store i32 0, ptr %1304, align 4
  br label %FillExpr.loopCmp-0364

FillExpr.loopCmp-0364:                            ; preds = %FillExpr.loopBody-0365, %FillExpr.loopStart-0363
  %1306 = load i32, ptr %1304, align 4
  %1307 = icmp slt i32 %1306, 4
  %1308 = load i32, ptr %1305, align 4
  %1309 = icmp slt i32 %1308, 4
  %1310 = and i1 %1307, %1309
  br i1 %1310, label %FillExpr.loopBody-0365, label %FillExpr.loopEnd-0366

FillExpr.loopBody-0365:                           ; preds = %FillExpr.loopCmp-0364
  %1311 = load i32, ptr %1304, align 4
  %1312 = getelementptr [4 x float], ptr %1303, i32 0, i32 %1311
  store float 0.000000e+00, ptr %1312, align 4
  %1313 = load i32, ptr %1304, align 4
  %1314 = add i32 %1313, 1
  store i32 %1314, ptr %1304, align 4
  %1315 = load i32, ptr %1305, align 4
  %1316 = add i32 %1315, 1
  store i32 %1316, ptr %1305, align 4
  br label %FillExpr.loopCmp-0364

FillExpr.loopEnd-0366:                            ; preds = %FillExpr.loopCmp-0364
  br label %FillExpr.exit367

FillExpr.exit367:                                 ; preds = %FillExpr.loopEnd-0366
  %1317 = getelementptr [4 x float], ptr %1303, i32 0, i32 0
  store float 0.000000e+00, ptr %1317, align 4
  %1318 = getelementptr [4 x float], ptr %1303, i32 0, i32 1
  %screenHeight368 = load i32, ptr @screenHeight, align 4
  %1319 = load i32, ptr @screenHeight, align 4
  %1320 = sitofp i32 %1319 to double
  %1321 = fdiv double %1320, 2.000000e+00
  %screenHeight369 = load i32, ptr @screenHeight, align 4
  %1322 = load i32, ptr @screenHeight, align 4
  %1323 = sitofp i32 %1322 to double
  %1324 = fdiv double %1323, 1.000000e+01
  %1325 = fadd double %1321, %1324
  %1326 = fptrunc double %1325 to float
  store float %1326, ptr %1318, align 4
  %1327 = getelementptr [4 x float], ptr %1303, i32 0, i32 2
  %screenWidth370 = load i32, ptr @screenWidth, align 4
  %1328 = load i32, ptr @screenWidth, align 4
  %1329 = sitofp i32 %1328 to float
  store float %1329, ptr %1327, align 4
  %1330 = getelementptr [4 x float], ptr %1303, i32 0, i32 3
  %screenHeight371 = load i32, ptr @screenHeight, align 4
  %1331 = load i32, ptr @screenHeight, align 4
  %1332 = sitofp i32 %1331 to double
  %1333 = fdiv double %1332, 2.000000e+00
  %1334 = fptrunc double %1333 to float
  store float %1334, ptr %1330, align 4
  %1335 = load [4 x float], ptr %1303, align 4
  %1336 = alloca [2 x float], align 4
  %1337 = alloca i32, align 4
  %1338 = alloca i32, align 4
  store i32 0, ptr %1338, align 4
  br label %FillExpr.loopStart-0372

FillExpr.loopStart-0372:                          ; preds = %FillExpr.exit367
  store i32 0, ptr %1337, align 4
  br label %FillExpr.loopCmp-0373

FillExpr.loopCmp-0373:                            ; preds = %FillExpr.loopBody-0374, %FillExpr.loopStart-0372
  %1339 = load i32, ptr %1337, align 4
  %1340 = icmp slt i32 %1339, 2
  %1341 = load i32, ptr %1338, align 4
  %1342 = icmp slt i32 %1341, 2
  %1343 = and i1 %1340, %1342
  br i1 %1343, label %FillExpr.loopBody-0374, label %FillExpr.loopEnd-0375

FillExpr.loopBody-0374:                           ; preds = %FillExpr.loopCmp-0373
  %1344 = load i32, ptr %1337, align 4
  %1345 = getelementptr [2 x float], ptr %1336, i32 0, i32 %1344
  store float 0.000000e+00, ptr %1345, align 4
  %1346 = load i32, ptr %1337, align 4
  %1347 = add i32 %1346, 1
  store i32 %1347, ptr %1337, align 4
  %1348 = load i32, ptr %1338, align 4
  %1349 = add i32 %1348, 1
  store i32 %1349, ptr %1338, align 4
  br label %FillExpr.loopCmp-0373

FillExpr.loopEnd-0375:                            ; preds = %FillExpr.loopCmp-0373
  br label %FillExpr.exit376

FillExpr.exit376:                                 ; preds = %FillExpr.loopEnd-0375
  %1350 = getelementptr [2 x float], ptr %1336, i32 0, i32 0
  %1351 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x377 = load float, ptr %1351, align 4
  %1352 = load float, ptr %1351, align 4
  store float %1352, ptr %1350, align 4
  %1353 = getelementptr [2 x float], ptr %1336, i32 0, i32 1
  %1354 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y378 = load float, ptr %1354, align 4
  %1355 = load float, ptr %1354, align 4
  store float %1355, ptr %1353, align 4
  %1356 = load [2 x float], ptr %1336, align 4
  %1357 = load ptr, ptr %fgAnim, align 8
  %1358 = getelementptr inbounds %FlowWingAnim, ptr %1357, i32 0, i32 5
  %1359 = getelementptr inbounds %COLORS_TYPE.3, ptr %1358, i32 0, i32 0
  %WHITE379 = load i32, ptr %1359, align 4
  %1360 = load i32, ptr %1359, align 4
  call void @DrawTexturePro(ptr %groundTexture, [4 x float] %1302, [4 x float] %1335, [2 x float] %1356, float 0.000000e+00, i32 %1360)
  %1361 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1362 = icmp eq i32 %1361, 0
  br i1 %1362, label %checkContinueBlock126, label %afterNestedBlock92

FillExpr.loopStart-0380:                          ; preds = %nestedBlock127
  store i32 0, ptr %615, align 4
  br label %FillExpr.loopCmp-0381

FillExpr.loopCmp-0381:                            ; preds = %FillExpr.loopBody-0382, %FillExpr.loopStart-0380
  %1363 = load i32, ptr %615, align 4
  %1364 = icmp slt i32 %1363, 4
  %1365 = load i32, ptr %616, align 4
  %1366 = icmp slt i32 %1365, 4
  %1367 = and i1 %1364, %1366
  br i1 %1367, label %FillExpr.loopBody-0382, label %FillExpr.loopEnd-0383

FillExpr.loopBody-0382:                           ; preds = %FillExpr.loopCmp-0381
  %1368 = load i32, ptr %615, align 4
  %1369 = getelementptr [4 x float], ptr %614, i32 0, i32 %1368
  store float 0.000000e+00, ptr %1369, align 4
  %1370 = load i32, ptr %615, align 4
  %1371 = add i32 %1370, 1
  store i32 %1371, ptr %615, align 4
  %1372 = load i32, ptr %616, align 4
  %1373 = add i32 %1372, 1
  store i32 %1373, ptr %616, align 4
  br label %FillExpr.loopCmp-0381

FillExpr.loopEnd-0383:                            ; preds = %FillExpr.loopCmp-0381
  br label %FillExpr.exit384

FillExpr.exit384:                                 ; preds = %FillExpr.loopEnd-0383
  %1374 = getelementptr [4 x float], ptr %614, i32 0, i32 0
  store float 3.100000e+02, ptr %1374, align 4
  %1375 = getelementptr [4 x float], ptr %614, i32 0, i32 1
  store float 1.250000e+03, ptr %1375, align 4
  %1376 = getelementptr [4 x float], ptr %614, i32 0, i32 2
  store float 4.360000e+03, ptr %1376, align 4
  %1377 = getelementptr [4 x float], ptr %614, i32 0, i32 3
  store float 1.250000e+03, ptr %1377, align 4
  %1378 = load [4 x float], ptr %614, align 4
  %1379 = alloca [4 x float], align 4
  %1380 = alloca i32, align 4
  %1381 = alloca i32, align 4
  store i32 0, ptr %1381, align 4
  br label %FillExpr.loopStart-0385

FillExpr.loopStart-0385:                          ; preds = %FillExpr.exit384
  store i32 0, ptr %1380, align 4
  br label %FillExpr.loopCmp-0386

FillExpr.loopCmp-0386:                            ; preds = %FillExpr.loopBody-0387, %FillExpr.loopStart-0385
  %1382 = load i32, ptr %1380, align 4
  %1383 = icmp slt i32 %1382, 4
  %1384 = load i32, ptr %1381, align 4
  %1385 = icmp slt i32 %1384, 4
  %1386 = and i1 %1383, %1385
  br i1 %1386, label %FillExpr.loopBody-0387, label %FillExpr.loopEnd-0388

FillExpr.loopBody-0387:                           ; preds = %FillExpr.loopCmp-0386
  %1387 = load i32, ptr %1380, align 4
  %1388 = getelementptr [4 x float], ptr %1379, i32 0, i32 %1387
  store float 0.000000e+00, ptr %1388, align 4
  %1389 = load i32, ptr %1380, align 4
  %1390 = add i32 %1389, 1
  store i32 %1390, ptr %1380, align 4
  %1391 = load i32, ptr %1381, align 4
  %1392 = add i32 %1391, 1
  store i32 %1392, ptr %1381, align 4
  br label %FillExpr.loopCmp-0386

FillExpr.loopEnd-0388:                            ; preds = %FillExpr.loopCmp-0386
  br label %FillExpr.exit389

FillExpr.exit389:                                 ; preds = %FillExpr.loopEnd-0388
  %1393 = getelementptr [4 x float], ptr %1379, i32 0, i32 0
  store float 0.000000e+00, ptr %1393, align 4
  %1394 = getelementptr [4 x float], ptr %1379, i32 0, i32 1
  %screenHeight390 = load i32, ptr @screenHeight, align 4
  %1395 = load i32, ptr @screenHeight, align 4
  %1396 = sitofp i32 %1395 to double
  %1397 = fdiv double %1396, 2.000000e+00
  %screenHeight391 = load i32, ptr @screenHeight, align 4
  %1398 = load i32, ptr @screenHeight, align 4
  %1399 = sitofp i32 %1398 to double
  %1400 = fdiv double %1399, 1.000000e+01
  %1401 = fadd double %1397, %1400
  %1402 = fptrunc double %1401 to float
  store float %1402, ptr %1394, align 4
  %1403 = getelementptr [4 x float], ptr %1379, i32 0, i32 2
  %screenWidth392 = load i32, ptr @screenWidth, align 4
  %1404 = load i32, ptr @screenWidth, align 4
  %1405 = sitofp i32 %1404 to float
  store float %1405, ptr %1403, align 4
  %1406 = getelementptr [4 x float], ptr %1379, i32 0, i32 3
  %screenHeight393 = load i32, ptr @screenHeight, align 4
  %1407 = load i32, ptr @screenHeight, align 4
  %1408 = sitofp i32 %1407 to double
  %1409 = fdiv double %1408, 2.000000e+00
  %1410 = fptrunc double %1409 to float
  store float %1410, ptr %1406, align 4
  %1411 = load [4 x float], ptr %1379, align 4
  %1412 = alloca [2 x float], align 4
  %1413 = alloca i32, align 4
  %1414 = alloca i32, align 4
  store i32 0, ptr %1414, align 4
  br label %FillExpr.loopStart-0394

FillExpr.loopStart-0394:                          ; preds = %FillExpr.exit389
  store i32 0, ptr %1413, align 4
  br label %FillExpr.loopCmp-0395

FillExpr.loopCmp-0395:                            ; preds = %FillExpr.loopBody-0396, %FillExpr.loopStart-0394
  %1415 = load i32, ptr %1413, align 4
  %1416 = icmp slt i32 %1415, 2
  %1417 = load i32, ptr %1414, align 4
  %1418 = icmp slt i32 %1417, 2
  %1419 = and i1 %1416, %1418
  br i1 %1419, label %FillExpr.loopBody-0396, label %FillExpr.loopEnd-0397

FillExpr.loopBody-0396:                           ; preds = %FillExpr.loopCmp-0395
  %1420 = load i32, ptr %1413, align 4
  %1421 = getelementptr [2 x float], ptr %1412, i32 0, i32 %1420
  store float 0.000000e+00, ptr %1421, align 4
  %1422 = load i32, ptr %1413, align 4
  %1423 = add i32 %1422, 1
  store i32 %1423, ptr %1413, align 4
  %1424 = load i32, ptr %1414, align 4
  %1425 = add i32 %1424, 1
  store i32 %1425, ptr %1414, align 4
  br label %FillExpr.loopCmp-0395

FillExpr.loopEnd-0397:                            ; preds = %FillExpr.loopCmp-0395
  br label %FillExpr.exit398

FillExpr.exit398:                                 ; preds = %FillExpr.loopEnd-0397
  %1426 = getelementptr [2 x float], ptr %1412, i32 0, i32 0
  %1427 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x399 = load float, ptr %1427, align 4
  %1428 = load float, ptr %1427, align 4
  store float %1428, ptr %1426, align 4
  %1429 = getelementptr [2 x float], ptr %1412, i32 0, i32 1
  %1430 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y400 = load float, ptr %1430, align 4
  %1431 = load float, ptr %1430, align 4
  store float %1431, ptr %1429, align 4
  %1432 = load [2 x float], ptr %1412, align 4
  %1433 = load ptr, ptr %fgAnim, align 8
  %1434 = getelementptr inbounds %FlowWingAnim, ptr %1433, i32 0, i32 5
  %1435 = getelementptr inbounds %COLORS_TYPE.3, ptr %1434, i32 0, i32 0
  %WHITE401 = load i32, ptr %1435, align 4
  %1436 = load i32, ptr %1435, align 4
  call void @DrawTexturePro(ptr %groundTexture, [4 x float] %1378, [4 x float] %1411, [2 x float] %1432, float 0.000000e+00, i32 %1436)
  %1437 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1438 = icmp eq i32 %1437, 0
  br i1 %1438, label %checkContinueBlock128, label %afterNestedBlock92

decrement_block408:                               ; preds = %while.end
  %1439 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1440 = sub i32 %1439, 1
  store i32 %1440, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block409

end_block409:                                     ; preds = %decrement_block408, %while.end
  %1441 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1442 = icmp eq i32 %1441, 0
  br i1 %1442, label %checkContinueBlock36, label %afterNestedBlock

returnBlock410:                                   ; preds = %nestedBlock39
  store i32 0, ptr %0, align 4
  ret void

mergeBlock411:                                    ; No predecessors!
  %1443 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1444 = icmp eq i32 %1443, 0
  br i1 %1444, label %checkContinueBlock40, label %afterNestedBlock
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
!42 = !{!"drawTexturePro:rt:pr:27"}
!43 = !{!"SetTargetFPS:rt:pr:27"}
!44 = !{!"getRandomNumber:rt:pr:28"}
!45 = !{!"ClearBackground:rt:pr:27"}
!46 = !{!"DrawTexturePro:rt:pr:27"}
!47 = !{!"TraceLog:rt:pr:27"}
!48 = !{!"GetScreenWidth:rt:pr:28"}
!49 = !{!"DrawCircle:rt:pr:27"}
!50 = !{!"time:rt:pr:28"}
!51 = !{!"BeginDrawing:rt:pr:27"}
!52 = !{!"IsKeyPressed:rt:pr:34"}
!53 = !{!"WindowShouldClose:rt:pr:34"}
!54 = !{!"InitWindow:rt:pr:27"}
!55 = !{!"EndDrawing:rt:pr:27"}
!56 = !{!"CloseWindow:rt:pr:27"}
!57 = !{!"GetScreenHeight:rt:pr:28"}
!58 = !{!"GetFrameTime:rt:pr:32"}
!59 = !{!"DrawText:rt:pr:27"}
!60 = !{!"GetTime:rt:pr:31"}
!61 = !{!"UnloadTexture:rt:pr:27"}
!62 = !{!"TextFormat:rt:pr:33"}
!63 = !{!"LoadTexture:rt:ob:Texture.0"}
!64 = !{!"IsKeyDown:rt:pr:34"}
!65 = !{!"DrawRectangle:rt:pr:27"}
!66 = !{!"DrawTexture:rt:pr:27"}
!67 = !{!"srand:rt:pr:27"}
!68 = !{!"rand:rt:pr:28"}
!69 = !{!"main:rt:pr:28"}
