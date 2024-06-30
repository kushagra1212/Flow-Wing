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
@21 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@22 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@25 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@26 = private unnamed_addr constant [18 x i8] c"./assets/bird.png\00", align 1
@27 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@28 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@29 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@30 = private unnamed_addr constant [21 x i8] c"./assets/3clouds.png\00", align 1
@31 = private unnamed_addr constant [27 x i8] c"./assets/skyBackground.png\00", align 1
@32 = private unnamed_addr constant [20 x i8] c"./assets/ground.png\00", align 1
@33 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL1.png\00", align 1
@34 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL2.png\00", align 1
@35 = private unnamed_addr constant [31 x i8] c"./assets/mountain/2mountL2.png\00", align 1
@36 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL3.png\00", align 1
@37 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1

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
  call void @"assign_<Object<COLORS_TYPE.3>>"(ptr %colors)
  %KEYS = alloca %KEYS_TYPE.2, align 8
  call void @"assign_<Object<KEYS_TYPE.2>>"(ptr %KEYS)
  %LOG = alloca %LOG_TYPE.1, align 8
  call void @"assign_<Object<LOG_TYPE.1>>"(ptr %LOG)
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
  call void @"assign_<Object<Texture.0>>"(ptr %birdTexture)
  %birdSpritePosition = alloca [9 x %Position.4], align 8
  call void @"assign_<Array<Object<Position.4>>>:9,"(ptr %birdSpritePosition)
  %pos = alloca %Position.4, align 8
  call void @"assign_<Object<Position.4>>"(ptr %pos)
  %clouds = alloca [5 x %AttributeType.5], align 8
  call void @"assign_<Array<Object<AttributeType.5>>>:5,"(ptr %clouds)
  %cloudTexture = alloca %Texture.0, align 8
  call void @"assign_<Object<Texture.0>>"(ptr %cloudTexture)
  %texturePath = alloca ptr, align 8
  store ptr @2, ptr %texturePath, align 8
  %rtPtr = alloca i32, align 4
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()
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
  call void @raise_exception(ptr @3)
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
  call void @raise_exception(ptr @4)
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
  call void @raise_exception(ptr @5)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %40 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %35
  %41 = getelementptr inbounds %AttributeType.5, ptr %40, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then7", label %"GlobalIndexExpr::else8"

"GlobalIndexExpr::then7":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge9"

"GlobalIndexExpr::else8":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @6)
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
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge13"

"GlobalIndexExpr::merge13":                       ; preds = %"GlobalIndexExpr::else12", %"GlobalIndexExpr::then11"
  %46 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %45
  %47 = getelementptr inbounds %AttributeType.5, ptr %46, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then17", label %"GlobalIndexExpr::else18"

"GlobalIndexExpr::then17":                        ; preds = %"GlobalIndexExpr::merge13"
  br label %"GlobalIndexExpr::merge19"

"GlobalIndexExpr::else18":                        ; preds = %"GlobalIndexExpr::merge13"
  call void @raise_exception(ptr @8)
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
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge24"

"GlobalIndexExpr::merge24":                       ; preds = %"GlobalIndexExpr::else23", %"GlobalIndexExpr::then22"
  %55 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %39
  %56 = getelementptr inbounds %AttributeType.5, ptr %55, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then28", label %"GlobalIndexExpr::else29"

"GlobalIndexExpr::then28":                        ; preds = %"GlobalIndexExpr::merge24"
  br label %"GlobalIndexExpr::merge30"

"GlobalIndexExpr::else29":                        ; preds = %"GlobalIndexExpr::merge24"
  call void @raise_exception(ptr @10)
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
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge39"

"GlobalIndexExpr::merge39":                       ; preds = %"GlobalIndexExpr::else38", %"GlobalIndexExpr::then37"
  %68 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %63
  %69 = getelementptr inbounds %AttributeType.5, ptr %68, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then43", label %"GlobalIndexExpr::else44"

"GlobalIndexExpr::then43":                        ; preds = %"GlobalIndexExpr::merge39"
  br label %"GlobalIndexExpr::merge45"

"GlobalIndexExpr::else44":                        ; preds = %"GlobalIndexExpr::merge39"
  call void @raise_exception(ptr @12)
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
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::merge50":                       ; preds = %"GlobalIndexExpr::else49", %"GlobalIndexExpr::then48"
  %80 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %67
  %81 = getelementptr inbounds %AttributeType.5, ptr %80, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then54", label %"GlobalIndexExpr::else55"

"GlobalIndexExpr::then54":                        ; preds = %"GlobalIndexExpr::merge50"
  br label %"GlobalIndexExpr::merge56"

"GlobalIndexExpr::else55":                        ; preds = %"GlobalIndexExpr::merge50"
  call void @raise_exception(ptr @14)
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
  %21 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %22 = load i32, ptr %21, align 4
  %clouds = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %22, 5
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %22, 0
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
  %23 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %22
  %24 = getelementptr inbounds %AttributeType.5, ptr %23, i32 0, i32 0
  %25 = load [4 x float], ptr %24, align 4
  %26 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  %clouds4 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan8" = icmp slt i32 %27, 5
  %"GlobalIndexExpr::isGreaterThan9" = icmp sge i32 %27, 0
  %"GlobalIndexExpr::isWithinBounds10" = and i1 %"GlobalIndexExpr::isLessThan8", %"GlobalIndexExpr::isGreaterThan9"
  br i1 %"GlobalIndexExpr::isWithinBounds10", label %"GlobalIndexExpr::then5", label %"GlobalIndexExpr::else6"

"GlobalIndexExpr::then5":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge7"

"GlobalIndexExpr::else6":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @16)
  br label %"GlobalIndexExpr::merge7"

"GlobalIndexExpr::merge7":                        ; preds = %"GlobalIndexExpr::else6", %"GlobalIndexExpr::then5"
  %28 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %27
  %29 = getelementptr inbounds %AttributeType.5, ptr %28, i32 0, i32 1
  %30 = load [4 x float], ptr %29, align 4
  %31 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %32 = load i32, ptr %31, align 4
  %clouds11 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan15" = icmp slt i32 %32, 5
  %"GlobalIndexExpr::isGreaterThan16" = icmp sge i32 %32, 0
  %"GlobalIndexExpr::isWithinBounds17" = and i1 %"GlobalIndexExpr::isLessThan15", %"GlobalIndexExpr::isGreaterThan16"
  br i1 %"GlobalIndexExpr::isWithinBounds17", label %"GlobalIndexExpr::then12", label %"GlobalIndexExpr::else13"

"GlobalIndexExpr::then12":                        ; preds = %"GlobalIndexExpr::merge7"
  br label %"GlobalIndexExpr::merge14"

"GlobalIndexExpr::else13":                        ; preds = %"GlobalIndexExpr::merge7"
  call void @raise_exception(ptr @17)
  br label %"GlobalIndexExpr::merge14"

"GlobalIndexExpr::merge14":                       ; preds = %"GlobalIndexExpr::else13", %"GlobalIndexExpr::then12"
  %33 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %32
  %34 = getelementptr inbounds %AttributeType.5, ptr %33, i32 0, i32 2
  %35 = load [2 x float], ptr %34, align 4
  %36 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %37 = load i32, ptr %36, align 4
  %clouds18 = load [5 x %AttributeType.5], ptr %3, align 4
  %"GlobalIndexExpr::isLessThan22" = icmp slt i32 %37, 5
  %"GlobalIndexExpr::isGreaterThan23" = icmp sge i32 %37, 0
  %"GlobalIndexExpr::isWithinBounds24" = and i1 %"GlobalIndexExpr::isLessThan22", %"GlobalIndexExpr::isGreaterThan23"
  br i1 %"GlobalIndexExpr::isWithinBounds24", label %"GlobalIndexExpr::then19", label %"GlobalIndexExpr::else20"

"GlobalIndexExpr::then19":                        ; preds = %"GlobalIndexExpr::merge14"
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::else20":                        ; preds = %"GlobalIndexExpr::merge14"
  call void @raise_exception(ptr @18)
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::merge21":                       ; preds = %"GlobalIndexExpr::else20", %"GlobalIndexExpr::then19"
  %38 = getelementptr [5 x %AttributeType.5], ptr %3, i32 0, i32 %37
  %39 = getelementptr inbounds %AttributeType.5, ptr %38, i32 0, i32 3
  %rotation = load float, ptr %39, align 4
  %40 = load float, ptr %39, align 4
  %41 = load ptr, ptr %0, align 8
  %42 = getelementptr inbounds %FlowWingAnim, ptr %41, i32 0, i32 5
  %43 = getelementptr inbounds %COLORS_TYPE.3, ptr %42, i32 0, i32 0
  %WHITE = load i32, ptr %43, align 4
  %44 = load i32, ptr %43, align 4
  call void @DrawTexturePro(ptr %4, [4 x float] %25, [4 x float] %30, [2 x float] %35, float %40, i32 %44)
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

define void @main(ptr %0) !rt !42 {
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
  call void @"assign_<Class<Texture.0>>"(ptr %backgroundTexture)
  %rtPtr = alloca %Texture.0, align 8
  %8 = alloca ptr, align 8
  %groundTexture = alloca %Texture.0, align 8
  call void @"assign_<Class<Texture.0>>"(ptr %groundTexture)
  %rtPtr1 = alloca %Texture.0, align 8
  %9 = alloca ptr, align 8
  %mountL1Texture = alloca %Texture.0, align 8
  call void @"assign_<Class<Texture.0>>"(ptr %mountL1Texture)
  %rtPtr2 = alloca %Texture.0, align 8
  %10 = alloca ptr, align 8
  %mountL2Texture = alloca %Texture.0, align 8
  call void @"assign_<Class<Texture.0>>"(ptr %mountL2Texture)
  %rtPtr3 = alloca %Texture.0, align 8
  %11 = alloca ptr, align 8
  %mount2L2Texture = alloca %Texture.0, align 8
  call void @"assign_<Class<Texture.0>>"(ptr %mount2L2Texture)
  %rtPtr4 = alloca %Texture.0, align 8
  %12 = alloca ptr, align 8
  %mount1L3Texture = alloca %Texture.0, align 8
  call void @"assign_<Class<Texture.0>>"(ptr %mount1L3Texture)
  %rtPtr5 = alloca %Texture.0, align 8
  %13 = alloca ptr, align 8
  %mountL1Pos1 = alloca %Position.4, align 8
  call void @"assign_<Object<Position.4>>"(ptr %mountL1Pos1)
  %mountL1Pos2 = alloca %Position.4, align 8
  call void @"assign_<Object<Position.4>>"(ptr %mountL1Pos2)
  %mountL2Pos1 = alloca %Position.4, align 8
  call void @"assign_<Object<Position.4>>"(ptr %mountL2Pos1)
  %mount2L2Pos1 = alloca %Position.4, align 8
  call void @"assign_<Object<Position.4>>"(ptr %mount2L2Pos1)
  %rtPtr6 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %mount1L3Pos1 = alloca %Position.4, align 8
  call void @"assign_<Object<Position.4>>"(ptr %mount1L3Pos1)
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
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %35)
  %36 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %36)
  %37 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %37)
  %38 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %38)
  %39 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %39)
  %40 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %40)
  %41 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %41)
  %42 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %42)
  %43 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %43)
  %44 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %44)
  %45 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %45)
  %46 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %46)
  %47 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %47)
  %48 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %48)
  %49 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %49)
  %50 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %50)
  %51 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %51)
  %52 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %52)
  %53 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %53)
  %54 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %54)
  %55 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %55)
  %56 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %56)
  %57 = alloca [4 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %57)
  %58 = alloca [2 x float], align 4
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %58)
  %59 = alloca %Texture.0, align 8
  %60 = alloca [4 x float], align 4
  %61 = alloca [4 x float], align 4
  %62 = alloca [2 x float], align 4
  %63 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock57, %mergeBlock258, %checkContinueBlock55, %nestedBlock54, %checkContinueBlock53, %end_block256, %checkContinueBlock51, %afterIfElse, %checkContinueBlock49, %nestedBlock48, %checkContinueBlock47, %nestedBlock46, %checkContinueBlock45, %nestedBlock44, %checkContinueBlock43, %nestedBlock42, %checkContinueBlock41, %nestedBlock40, %checkContinueBlock39, %nestedBlock38, %checkContinueBlock37, %nestedBlock36, %checkContinueBlock35, %nestedBlock34, %checkContinueBlock33, %nestedBlock32, %checkContinueBlock31, %nestedBlock30, %checkContinueBlock29, %nestedBlock28, %checkContinueBlock27, %nestedBlock26, %checkContinueBlock25, %nestedBlock24, %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %64 = call ptr @malloc(i64 96)
  call void @"assign_<Class<FlowWingAnim>>"(ptr %64)
  %65 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %65, align 8
  %66 = load ptr, ptr %65, align 8
  %67 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 23
  store ptr @FlowWingAnim.setTargetFPS, ptr %67, align 8
  %68 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 22
  store ptr @FlowWingAnim.endDrawing, ptr %68, align 8
  %69 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 21
  store ptr @FlowWingAnim.createWindow, ptr %69, align 8
  %70 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %70, align 8
  %71 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 20
  store ptr @FlowWingAnim.drawTexturePro, ptr %71, align 8
  %72 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 16
  store ptr @FlowWingAnim.drawRectangle, ptr %72, align 8
  %73 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 15
  store ptr @FlowWingAnim.beginDrawing, ptr %73, align 8
  %74 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 1
  store ptr @FlowWingAnim.traceLog, ptr %74, align 8
  %75 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 14
  store ptr @FlowWingAnim.unloadTexture, ptr %75, align 8
  %76 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 13
  store ptr @FlowWingAnim.closeWindow, ptr %76, align 8
  %77 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 17
  store ptr @FlowWingAnim.getColor, ptr %77, align 8
  %78 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 12
  store ptr @FlowWingAnim.textFormat, ptr %78, align 8
  %79 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 18
  store ptr @FlowWingAnim.windowShouldClose, ptr %79, align 8
  %80 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenWidth, ptr %80, align 8
  %81 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenHeight, ptr %81, align 8
  %82 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 11
  store ptr @FlowWingAnim.getTime, ptr %82, align 8
  %83 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 19
  store ptr @FlowWingAnim.beforeInit, ptr %83, align 8
  %84 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 10
  store ptr @FlowWingAnim.clearBackground, ptr %84, align 8
  %85 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 7
  store ptr @FlowWingAnim.drawTexture, ptr %85, align 8
  %86 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 8
  store ptr @FlowWingAnim.getFrameTime, ptr %86, align 8
  %87 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 2
  store ptr @FlowWingAnim.drawText, ptr %87, align 8
  %88 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %88, align 8
  %89 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 9
  store ptr @FlowWingAnim.loadTexture, ptr %89, align 8
  %90 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %66, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %90, align 8
  %91 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 1
  store i32 0, ptr %91, align 4
  %92 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 2
  store i32 0, ptr %92, align 4
  %93 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 3
  store ptr @21, ptr %93, align 8
  %94 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 4
  store i32 0, ptr %94, align 4
  %95 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 5
  call void @"assign_<Object<COLORS_TYPE.3>>"(ptr %95)
  %96 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 6
  call void @"assign_<Object<KEYS_TYPE.2>>"(ptr %96)
  %97 = getelementptr inbounds %FlowWingAnim, ptr %64, i32 0, i32 7
  call void @"assign_<Object<LOG_TYPE.1>>"(ptr %97)
  store ptr %64, ptr %fgAnim, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  store ptr @22, ptr %1, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %1, ptr @FPS, ptr %fgAnim)
  %98 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %100 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock
  %102 = load ptr, ptr %fgAnim, align 8
  %103 = getelementptr inbounds %FlowWingAnim, ptr %102, i32 0, i32 0
  %104 = load ptr, ptr %103, align 8
  %105 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %104, i32 0, i32 21
  %106 = load ptr, ptr %105, align 8
  call void %106(ptr %fgAnim)
  %107 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  %109 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %110 = icmp eq i32 %109, 0
  br i1 %110, label %nestedBlock20, label %afterNestedBlock

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %111 = call ptr @malloc(i64 152)
  call void @"assign_<Class<Bird>>"(ptr %111)
  %112 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %112, align 8
  %113 = load ptr, ptr %112, align 8
  %114 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 8
  store ptr @Bird.updateY, ptr %114, align 8
  %115 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 7
  store ptr @Bird.getTexturePath, ptr %115, align 8
  %116 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 5
  store ptr @Bird.isTextureLoaded, ptr %116, align 8
  %117 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 9
  store ptr @Bird.setTexture, ptr %117, align 8
  %118 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 2
  store ptr @Bird.getOrigin, ptr %118, align 8
  %119 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 4
  store ptr @Bird.getSource, ptr %119, align 8
  %120 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 6
  store ptr @Bird.update, ptr %120, align 8
  %121 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 0
  store ptr @Bird.getTexture, ptr %121, align 8
  %122 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 3
  store ptr @Bird.getDistination, ptr %122, align 8
  %123 = getelementptr inbounds %"Bird::VTableType", ptr %113, i32 0, i32 1
  store ptr @Bird.getRotation, ptr %123, align 8
  %124 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 1
  store float 3.600000e+02, ptr %124, align 4
  %125 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 2
  store float 9.000000e+01, ptr %125, align 4
  %126 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 3
  %FPS58 = load i32, ptr @FPS, align 4
  %127 = load i32, ptr @FPS, align 4
  %128 = sitofp i32 %127 to double
  %129 = fdiv double 1.000000e+01, %128
  store double %129, ptr %126, align 8
  %130 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 4
  store double 0.000000e+00, ptr %130, align 8
  %131 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 5
  store i32 9, ptr %131, align 4
  %132 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 6
  store i32 0, ptr %132, align 4
  %133 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 7
  store ptr @25, ptr %133, align 8
  %134 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 8
  store i1 false, ptr %134, align 1
  %135 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 9
  call void @"assign_<Class<Texture.0>>"(ptr %135)
  %136 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 10
  call void @"assign_<Array<Object<Position.4>>>:9,"(ptr %136)
  %137 = getelementptr inbounds %Bird, ptr %111, i32 0, i32 11
  call void @"assign_<Object<Position.4>>"(ptr %137)
  store ptr %111, ptr %bird, align 8
  store ptr @26, ptr %2, align 8
  call void @Bird.init1(ptr %2, ptr %bird)
  %138 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %139 = icmp eq i32 %138, 0
  br i1 %139, label %checkContinueBlock21, label %afterNestedBlock

checkContinueBlock21:                             ; preds = %nestedBlock20
  %140 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %141 = icmp eq i32 %140, 0
  br i1 %141, label %nestedBlock22, label %afterNestedBlock

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %142 = call ptr @malloc(i64 256)
  call void @"assign_<Class<Cloud>>"(ptr %142)
  %143 = getelementptr inbounds %Cloud, ptr %142, i32 0, i32 0
  store ptr @vtable.Cloud.fg, ptr %143, align 8
  %144 = load ptr, ptr %143, align 8
  %145 = getelementptr inbounds %"Cloud::VTableType", ptr %144, i32 0, i32 4
  store ptr @Cloud.update, ptr %145, align 8
  %146 = getelementptr inbounds %"Cloud::VTableType", ptr %144, i32 0, i32 3
  store ptr @Cloud.setTexture, ptr %146, align 8
  %147 = getelementptr inbounds %"Cloud::VTableType", ptr %144, i32 0, i32 2
  store ptr @Cloud.getTexturePath, ptr %147, align 8
  %148 = getelementptr inbounds %"Cloud::VTableType", ptr %144, i32 0, i32 1
  store ptr @Cloud.getTexture, ptr %148, align 8
  %149 = getelementptr inbounds %"Cloud::VTableType", ptr %144, i32 0, i32 0
  store ptr @Cloud.draw, ptr %149, align 8
  %150 = getelementptr inbounds %Cloud, ptr %142, i32 0, i32 1
  call void @"assign_<Array<Object<AttributeType.5>>>:5,"(ptr %150)
  %151 = getelementptr inbounds %Cloud, ptr %142, i32 0, i32 2
  call void @"assign_<Class<Texture.0>>"(ptr %151)
  %152 = getelementptr inbounds %Cloud, ptr %142, i32 0, i32 3
  store ptr @29, ptr %152, align 8
  store ptr %142, ptr %cloud, align 8
  store ptr @30, ptr %3, align 8
  call void @Cloud.init1(ptr %3, ptr %cloud)
  %153 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %checkContinueBlock23, label %afterNestedBlock

checkContinueBlock23:                             ; preds = %nestedBlock22
  %155 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %156 = icmp eq i32 %155, 0
  br i1 %156, label %nestedBlock24, label %afterNestedBlock

nestedBlock24:                                    ; preds = %checkContinueBlock23
  %157 = load ptr, ptr %bird, align 8
  %158 = getelementptr inbounds %Bird, ptr %157, i32 0, i32 0
  %159 = load ptr, ptr %158, align 8
  %160 = getelementptr inbounds %"Bird::VTableType", ptr %159, i32 0, i32 9
  %161 = load ptr, ptr %160, align 8
  %162 = load ptr, ptr %fgAnim, align 8
  %163 = getelementptr inbounds %FlowWingAnim, ptr %162, i32 0, i32 0
  %164 = load ptr, ptr %163, align 8
  %165 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %164, i32 0, i32 9
  %166 = load ptr, ptr %165, align 8
  %167 = load ptr, ptr %bird, align 8
  %168 = getelementptr inbounds %Bird, ptr %167, i32 0, i32 0
  %169 = load ptr, ptr %168, align 8
  %170 = getelementptr inbounds %"Bird::VTableType", ptr %169, i32 0, i32 7
  %171 = load ptr, ptr %170, align 8
  call void %171(ptr %5, ptr %bird)
  call void %166(ptr %4, ptr %5, ptr %fgAnim)
  call void %161(ptr %4, ptr %bird)
  %172 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %173 = icmp eq i32 %172, 0
  br i1 %173, label %checkContinueBlock25, label %afterNestedBlock

checkContinueBlock25:                             ; preds = %nestedBlock24
  %174 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %175 = icmp eq i32 %174, 0
  br i1 %175, label %nestedBlock26, label %afterNestedBlock

nestedBlock26:                                    ; preds = %checkContinueBlock25
  %176 = load ptr, ptr %cloud, align 8
  %177 = getelementptr inbounds %Cloud, ptr %176, i32 0, i32 0
  %178 = load ptr, ptr %177, align 8
  %179 = getelementptr inbounds %"Cloud::VTableType", ptr %178, i32 0, i32 3
  %180 = load ptr, ptr %179, align 8
  %181 = load ptr, ptr %fgAnim, align 8
  %182 = getelementptr inbounds %FlowWingAnim, ptr %181, i32 0, i32 0
  %183 = load ptr, ptr %182, align 8
  %184 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %183, i32 0, i32 9
  %185 = load ptr, ptr %184, align 8
  %186 = load ptr, ptr %cloud, align 8
  %187 = getelementptr inbounds %Cloud, ptr %186, i32 0, i32 0
  %188 = load ptr, ptr %187, align 8
  %189 = getelementptr inbounds %"Cloud::VTableType", ptr %188, i32 0, i32 2
  %190 = load ptr, ptr %189, align 8
  call void %190(ptr %7, ptr %cloud)
  call void %185(ptr %6, ptr %7, ptr %fgAnim)
  call void %180(ptr %6, ptr %cloud)
  %191 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %192 = icmp eq i32 %191, 0
  br i1 %192, label %checkContinueBlock27, label %afterNestedBlock

checkContinueBlock27:                             ; preds = %nestedBlock26
  %193 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %194 = icmp eq i32 %193, 0
  br i1 %194, label %nestedBlock28, label %afterNestedBlock

nestedBlock28:                                    ; preds = %checkContinueBlock27
  %195 = load ptr, ptr %fgAnim, align 8
  %196 = getelementptr inbounds %FlowWingAnim, ptr %195, i32 0, i32 0
  %197 = load ptr, ptr %196, align 8
  %198 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %197, i32 0, i32 9
  %199 = load ptr, ptr %198, align 8
  store ptr @31, ptr %8, align 8
  call void %199(ptr %rtPtr, ptr %8, ptr %fgAnim)
  %200 = load %Texture.0, ptr %rtPtr, align 4
  store %Texture.0 %200, ptr %backgroundTexture, align 4
  %201 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %202 = icmp eq i32 %201, 0
  br i1 %202, label %checkContinueBlock29, label %afterNestedBlock

checkContinueBlock29:                             ; preds = %nestedBlock28
  %203 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %204 = icmp eq i32 %203, 0
  br i1 %204, label %nestedBlock30, label %afterNestedBlock

nestedBlock30:                                    ; preds = %checkContinueBlock29
  %205 = load ptr, ptr %fgAnim, align 8
  %206 = getelementptr inbounds %FlowWingAnim, ptr %205, i32 0, i32 0
  %207 = load ptr, ptr %206, align 8
  %208 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %207, i32 0, i32 9
  %209 = load ptr, ptr %208, align 8
  store ptr @32, ptr %9, align 8
  call void %209(ptr %rtPtr1, ptr %9, ptr %fgAnim)
  %210 = load %Texture.0, ptr %rtPtr1, align 4
  store %Texture.0 %210, ptr %groundTexture, align 4
  %211 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %212 = icmp eq i32 %211, 0
  br i1 %212, label %checkContinueBlock31, label %afterNestedBlock

checkContinueBlock31:                             ; preds = %nestedBlock30
  %213 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %214 = icmp eq i32 %213, 0
  br i1 %214, label %nestedBlock32, label %afterNestedBlock

nestedBlock32:                                    ; preds = %checkContinueBlock31
  %215 = load ptr, ptr %fgAnim, align 8
  %216 = getelementptr inbounds %FlowWingAnim, ptr %215, i32 0, i32 0
  %217 = load ptr, ptr %216, align 8
  %218 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %217, i32 0, i32 9
  %219 = load ptr, ptr %218, align 8
  store ptr @33, ptr %10, align 8
  call void %219(ptr %rtPtr2, ptr %10, ptr %fgAnim)
  %220 = load %Texture.0, ptr %rtPtr2, align 4
  store %Texture.0 %220, ptr %mountL1Texture, align 4
  %221 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %222 = icmp eq i32 %221, 0
  br i1 %222, label %checkContinueBlock33, label %afterNestedBlock

checkContinueBlock33:                             ; preds = %nestedBlock32
  %223 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %224 = icmp eq i32 %223, 0
  br i1 %224, label %nestedBlock34, label %afterNestedBlock

nestedBlock34:                                    ; preds = %checkContinueBlock33
  %225 = load ptr, ptr %fgAnim, align 8
  %226 = getelementptr inbounds %FlowWingAnim, ptr %225, i32 0, i32 0
  %227 = load ptr, ptr %226, align 8
  %228 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %227, i32 0, i32 9
  %229 = load ptr, ptr %228, align 8
  store ptr @34, ptr %11, align 8
  call void %229(ptr %rtPtr3, ptr %11, ptr %fgAnim)
  %230 = load %Texture.0, ptr %rtPtr3, align 4
  store %Texture.0 %230, ptr %mountL2Texture, align 4
  %231 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %232 = icmp eq i32 %231, 0
  br i1 %232, label %checkContinueBlock35, label %afterNestedBlock

checkContinueBlock35:                             ; preds = %nestedBlock34
  %233 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %234 = icmp eq i32 %233, 0
  br i1 %234, label %nestedBlock36, label %afterNestedBlock

nestedBlock36:                                    ; preds = %checkContinueBlock35
  %235 = load ptr, ptr %fgAnim, align 8
  %236 = getelementptr inbounds %FlowWingAnim, ptr %235, i32 0, i32 0
  %237 = load ptr, ptr %236, align 8
  %238 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %237, i32 0, i32 9
  %239 = load ptr, ptr %238, align 8
  store ptr @35, ptr %12, align 8
  call void %239(ptr %rtPtr4, ptr %12, ptr %fgAnim)
  %240 = load %Texture.0, ptr %rtPtr4, align 4
  store %Texture.0 %240, ptr %mount2L2Texture, align 4
  %241 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %242 = icmp eq i32 %241, 0
  br i1 %242, label %checkContinueBlock37, label %afterNestedBlock

checkContinueBlock37:                             ; preds = %nestedBlock36
  %243 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %244 = icmp eq i32 %243, 0
  br i1 %244, label %nestedBlock38, label %afterNestedBlock

nestedBlock38:                                    ; preds = %checkContinueBlock37
  %245 = load ptr, ptr %fgAnim, align 8
  %246 = getelementptr inbounds %FlowWingAnim, ptr %245, i32 0, i32 0
  %247 = load ptr, ptr %246, align 8
  %248 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %247, i32 0, i32 9
  %249 = load ptr, ptr %248, align 8
  store ptr @36, ptr %13, align 8
  call void %249(ptr %rtPtr5, ptr %13, ptr %fgAnim)
  %250 = load %Texture.0, ptr %rtPtr5, align 4
  store %Texture.0 %250, ptr %mount1L3Texture, align 4
  %251 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %252 = icmp eq i32 %251, 0
  br i1 %252, label %checkContinueBlock39, label %afterNestedBlock

checkContinueBlock39:                             ; preds = %nestedBlock38
  %253 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %254 = icmp eq i32 %253, 0
  br i1 %254, label %nestedBlock40, label %afterNestedBlock

nestedBlock40:                                    ; preds = %checkContinueBlock39
  %255 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %255, align 4
  %256 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %256, align 4
  %257 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %258 = icmp eq i32 %257, 0
  br i1 %258, label %checkContinueBlock41, label %afterNestedBlock

checkContinueBlock41:                             ; preds = %nestedBlock40
  %259 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %260 = icmp eq i32 %259, 0
  br i1 %260, label %nestedBlock42, label %afterNestedBlock

nestedBlock42:                                    ; preds = %checkContinueBlock41
  %261 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  store float -1.542000e+03, ptr %261, align 4
  %262 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %262, align 4
  %263 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %264 = icmp eq i32 %263, 0
  br i1 %264, label %checkContinueBlock43, label %afterNestedBlock

checkContinueBlock43:                             ; preds = %nestedBlock42
  %265 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %266 = icmp eq i32 %265, 0
  br i1 %266, label %nestedBlock44, label %afterNestedBlock

nestedBlock44:                                    ; preds = %checkContinueBlock43
  %267 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %screenWidth59 = load i32, ptr @screenWidth, align 4
  %268 = load i32, ptr @screenWidth, align 4
  %269 = mul i32 -1, %268
  %270 = sitofp i32 %269 to float
  store float %270, ptr %267, align 4
  %271 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %271, align 4
  %272 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %273 = icmp eq i32 %272, 0
  br i1 %273, label %checkContinueBlock45, label %afterNestedBlock

checkContinueBlock45:                             ; preds = %nestedBlock44
  %274 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %275 = icmp eq i32 %274, 0
  br i1 %275, label %nestedBlock46, label %afterNestedBlock

nestedBlock46:                                    ; preds = %checkContinueBlock45
  %276 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %screenWidth60 = load i32, ptr @screenWidth, align 4
  %277 = load i32, ptr @screenWidth, align 4
  %278 = mul i32 -1, %277
  %screenWidth61 = load i32, ptr @screenWidth, align 4
  %279 = load i32, ptr @screenWidth, align 4
  %280 = sitofp i32 %279 to double
  %281 = fdiv double %280, 4.000000e+00
  %282 = fptosi double %281 to i32
  store i32 %282, ptr %14, align 4
  %screenWidth62 = load i32, ptr @screenWidth, align 4
  %283 = load i32, ptr @screenWidth, align 4
  %284 = sitofp i32 %283 to double
  %285 = fdiv double %284, 2.000000e+00
  %286 = fptosi double %285 to i32
  store i32 %286, ptr %15, align 4
  call void @getRandomNumber(ptr %rtPtr6, ptr %14, ptr %15)
  %287 = load i32, ptr %rtPtr6, align 4
  %288 = sub i32 %278, %287
  %289 = sitofp i32 %288 to float
  store float %289, ptr %276, align 4
  %290 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %290, align 4
  %291 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %292 = icmp eq i32 %291, 0
  br i1 %292, label %checkContinueBlock47, label %afterNestedBlock

checkContinueBlock47:                             ; preds = %nestedBlock46
  %293 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %294 = icmp eq i32 %293, 0
  br i1 %294, label %nestedBlock48, label %afterNestedBlock

nestedBlock48:                                    ; preds = %checkContinueBlock47
  %295 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %screenWidth63 = load i32, ptr @screenWidth, align 4
  %296 = load i32, ptr @screenWidth, align 4
  %297 = mul i32 -1, %296
  %screenWidth64 = load i32, ptr @screenWidth, align 4
  %298 = load i32, ptr @screenWidth, align 4
  %299 = sitofp i32 %298 to double
  %300 = fdiv double %299, 4.000000e+00
  %301 = fptosi double %300 to i32
  store i32 %301, ptr %16, align 4
  %screenWidth65 = load i32, ptr @screenWidth, align 4
  %302 = load i32, ptr @screenWidth, align 4
  store i32 %302, ptr %17, align 4
  call void @getRandomNumber(ptr %rtPtr7, ptr %16, ptr %17)
  %303 = load i32, ptr %rtPtr7, align 4
  %304 = sub i32 %297, %303
  %305 = sitofp i32 %304 to float
  store float %305, ptr %295, align 4
  %306 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %306, align 4
  %307 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %308 = icmp eq i32 %307, 0
  br i1 %308, label %checkContinueBlock49, label %afterNestedBlock

checkContinueBlock49:                             ; preds = %nestedBlock48
  %309 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %310 = icmp eq i32 %309, 0
  br i1 %310, label %nestedBlock50, label %afterNestedBlock

nestedBlock50:                                    ; preds = %checkContinueBlock49
  %311 = load ptr, ptr %bird, align 8
  %312 = getelementptr inbounds %Bird, ptr %311, i32 0, i32 0
  %313 = load ptr, ptr %312, align 8
  %314 = getelementptr inbounds %"Bird::VTableType", ptr %313, i32 0, i32 5
  %315 = load ptr, ptr %314, align 8
  call void %315(ptr %rtPtr8, ptr %bird)
  %316 = load i1, ptr %rtPtr8, align 1
  %317 = xor i1 %316, true
  %318 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  %id = load i32, ptr %318, align 4
  %319 = load i32, ptr %318, align 4
  %320 = icmp eq i32 %319, 0
  %321 = select i1 %317, i1 true, i1 %320
  br i1 %321, label %then, label %else

checkContinueBlock51:                             ; preds = %afterIfElse
  %322 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %323 = icmp eq i32 %322, 0
  br i1 %323, label %nestedBlock52, label %afterNestedBlock

nestedBlock52:                                    ; preds = %checkContinueBlock51
  br label %"while:conditon"

checkContinueBlock53:                             ; preds = %end_block256
  %324 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %325 = icmp eq i32 %324, 0
  br i1 %325, label %nestedBlock54, label %afterNestedBlock

nestedBlock54:                                    ; preds = %checkContinueBlock53
  %326 = load ptr, ptr %fgAnim, align 8
  %327 = getelementptr inbounds %FlowWingAnim, ptr %326, i32 0, i32 0
  %328 = load ptr, ptr %327, align 8
  %329 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %328, i32 0, i32 13
  %330 = load ptr, ptr %329, align 8
  call void %330(ptr %fgAnim)
  %331 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %332 = icmp eq i32 %331, 0
  br i1 %332, label %checkContinueBlock55, label %afterNestedBlock

checkContinueBlock55:                             ; preds = %nestedBlock54
  %333 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %334 = icmp eq i32 %333, 0
  br i1 %334, label %nestedBlock56, label %afterNestedBlock

nestedBlock56:                                    ; preds = %checkContinueBlock55
  br label %returnBlock257

checkContinueBlock57:                             ; preds = %mergeBlock258
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock50
  br label %nestedBlock67

else:                                             ; preds = %nestedBlock50
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock66
  %335 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %336 = icmp eq i32 %335, 0
  br i1 %336, label %checkContinueBlock51, label %afterNestedBlock

afterNestedBlock66:                               ; preds = %checkContinueBlock74, %mergeBlock, %checkContinueBlock72, %nestedBlock71, %checkContinueBlock70, %nestedBlock69, %checkContinueBlock68, %nestedBlock67
  br label %afterIfElse

nestedBlock67:                                    ; preds = %then
  %337 = load ptr, ptr %fgAnim, align 8
  %338 = getelementptr inbounds %FlowWingAnim, ptr %337, i32 0, i32 0
  %339 = load ptr, ptr %338, align 8
  %340 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %339, i32 0, i32 1
  %341 = load ptr, ptr %340, align 8
  %342 = load ptr, ptr %fgAnim, align 8
  %343 = getelementptr inbounds %FlowWingAnim, ptr %342, i32 0, i32 7
  %344 = getelementptr inbounds %LOG_TYPE.1, ptr %343, i32 0, i32 5
  %ERROR = load i32, ptr %344, align 4
  store ptr @37, ptr %22, align 8
  call void %341(ptr %344, ptr %22, ptr %fgAnim)
  %345 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %346 = icmp eq i32 %345, 0
  br i1 %346, label %checkContinueBlock68, label %afterNestedBlock66

checkContinueBlock68:                             ; preds = %nestedBlock67
  %347 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %348 = icmp eq i32 %347, 0
  br i1 %348, label %nestedBlock69, label %afterNestedBlock66

nestedBlock69:                                    ; preds = %checkContinueBlock68
  %349 = load ptr, ptr %fgAnim, align 8
  %350 = getelementptr inbounds %FlowWingAnim, ptr %349, i32 0, i32 0
  %351 = load ptr, ptr %350, align 8
  %352 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %351, i32 0, i32 14
  %353 = load ptr, ptr %352, align 8
  %354 = load ptr, ptr %bird, align 8
  %355 = getelementptr inbounds %Bird, ptr %354, i32 0, i32 0
  %356 = load ptr, ptr %355, align 8
  %357 = getelementptr inbounds %"Bird::VTableType", ptr %356, i32 0, i32 0
  %358 = load ptr, ptr %357, align 8
  call void %358(ptr %23, ptr %bird)
  call void %353(ptr %23, ptr %fgAnim)
  %359 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %360 = icmp eq i32 %359, 0
  br i1 %360, label %checkContinueBlock70, label %afterNestedBlock66

checkContinueBlock70:                             ; preds = %nestedBlock69
  %361 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %362 = icmp eq i32 %361, 0
  br i1 %362, label %nestedBlock71, label %afterNestedBlock66

nestedBlock71:                                    ; preds = %checkContinueBlock70
  %363 = load ptr, ptr %fgAnim, align 8
  %364 = getelementptr inbounds %FlowWingAnim, ptr %363, i32 0, i32 0
  %365 = load ptr, ptr %364, align 8
  %366 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %365, i32 0, i32 13
  %367 = load ptr, ptr %366, align 8
  call void %367(ptr %fgAnim)
  %368 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %369 = icmp eq i32 %368, 0
  br i1 %369, label %checkContinueBlock72, label %afterNestedBlock66

checkContinueBlock72:                             ; preds = %nestedBlock71
  %370 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %371 = icmp eq i32 %370, 0
  br i1 %371, label %nestedBlock73, label %afterNestedBlock66

nestedBlock73:                                    ; preds = %checkContinueBlock72
  br label %returnBlock

checkContinueBlock74:                             ; preds = %mergeBlock
  br label %afterNestedBlock66

returnBlock:                                      ; preds = %nestedBlock73
  store i32 1, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %372 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %373 = icmp eq i32 %372, 0
  br i1 %373, label %checkContinueBlock74, label %afterNestedBlock66

"while:conditon":                                 ; preds = %afterNestedBlock75, %nestedBlock52
  %374 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %375 = icmp eq i32 %374, 0
  br i1 %375, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock76

while.end:                                        ; preds = %afterNestedBlock75, %end_block
  %376 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %377 = icmp eq i32 %376, 0
  br i1 %377, label %end_block256, label %decrement_block255

decrement_block:                                  ; preds = %"while:conditon"
  %378 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %379 = sub i32 %378, 1
  store i32 %379, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %380 = load ptr, ptr %fgAnim, align 8
  %381 = getelementptr inbounds %FlowWingAnim, ptr %380, i32 0, i32 0
  %382 = load ptr, ptr %381, align 8
  %383 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %382, i32 0, i32 18
  %384 = load ptr, ptr %383, align 8
  call void %384(ptr %rtPtr9, ptr %fgAnim)
  %385 = load i1, ptr %rtPtr9, align 1
  %386 = xor i1 %385, true
  br i1 %386, label %"while:body", label %while.end

afterNestedBlock75:                               ; preds = %checkContinueBlock115, %nestedBlock114, %checkContinueBlock113, %nestedBlock112, %checkContinueBlock111, %nestedBlock110, %checkContinueBlock109, %nestedBlock108, %checkContinueBlock107, %nestedBlock106, %checkContinueBlock105, %nestedBlock104, %checkContinueBlock103, %nestedBlock102, %checkContinueBlock101, %nestedBlock100, %checkContinueBlock99, %nestedBlock98, %checkContinueBlock97, %nestedBlock96, %checkContinueBlock95, %nestedBlock94, %checkContinueBlock93, %nestedBlock92, %checkContinueBlock91, %nestedBlock90, %checkContinueBlock89, %nestedBlock88, %checkContinueBlock87, %afterIfElse203, %checkContinueBlock85, %afterNestedBlock180, %checkContinueBlock83, %afterNestedBlock162, %checkContinueBlock81, %afterNestedBlock144, %checkContinueBlock79, %afterNestedBlock116, %checkContinueBlock77, %nestedBlock76
  %387 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %388 = icmp eq i32 %387, 0
  br i1 %388, label %"while:conditon", label %while.end

nestedBlock76:                                    ; preds = %"while:body"
  %389 = load ptr, ptr %bird, align 8
  %390 = getelementptr inbounds %Bird, ptr %389, i32 0, i32 0
  %391 = load ptr, ptr %390, align 8
  %392 = getelementptr inbounds %"Bird::VTableType", ptr %391, i32 0, i32 6
  %393 = load ptr, ptr %392, align 8
  %394 = load ptr, ptr %fgAnim, align 8
  %395 = getelementptr inbounds %FlowWingAnim, ptr %394, i32 0, i32 0
  %396 = load ptr, ptr %395, align 8
  %397 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %396, i32 0, i32 8
  %398 = load ptr, ptr %397, align 8
  call void %398(ptr %24, ptr %fgAnim)
  call void %393(ptr %24, ptr %bird)
  %399 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %400 = icmp eq i32 %399, 0
  br i1 %400, label %checkContinueBlock77, label %afterNestedBlock75

checkContinueBlock77:                             ; preds = %nestedBlock76
  %401 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %402 = icmp eq i32 %401, 0
  br i1 %402, label %nestedBlock78, label %afterNestedBlock75

nestedBlock78:                                    ; preds = %checkContinueBlock77
  br label %nestedBlock117

checkContinueBlock79:                             ; preds = %afterNestedBlock116
  %403 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %404 = icmp eq i32 %403, 0
  br i1 %404, label %nestedBlock80, label %afterNestedBlock75

nestedBlock80:                                    ; preds = %checkContinueBlock79
  br label %nestedBlock145

checkContinueBlock81:                             ; preds = %afterNestedBlock144
  %405 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %406 = icmp eq i32 %405, 0
  br i1 %406, label %nestedBlock82, label %afterNestedBlock75

nestedBlock82:                                    ; preds = %checkContinueBlock81
  br label %nestedBlock163

checkContinueBlock83:                             ; preds = %afterNestedBlock162
  %407 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %408 = icmp eq i32 %407, 0
  br i1 %408, label %nestedBlock84, label %afterNestedBlock75

nestedBlock84:                                    ; preds = %checkContinueBlock83
  br label %nestedBlock181

checkContinueBlock85:                             ; preds = %afterNestedBlock180
  %409 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %410 = icmp eq i32 %409, 0
  br i1 %410, label %nestedBlock86, label %afterNestedBlock75

nestedBlock86:                                    ; preds = %checkContinueBlock85
  %411 = load ptr, ptr %fgAnim, align 8
  %412 = getelementptr inbounds %FlowWingAnim, ptr %411, i32 0, i32 0
  %413 = load ptr, ptr %412, align 8
  %414 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %413, i32 0, i32 0
  %415 = load ptr, ptr %414, align 8
  %416 = load ptr, ptr %fgAnim, align 8
  %417 = getelementptr inbounds %FlowWingAnim, ptr %416, i32 0, i32 6
  %418 = getelementptr inbounds %KEYS_TYPE.2, ptr %417, i32 0, i32 3
  %KEY_UP = load i32, ptr %418, align 4
  call void %415(ptr %rtPtr16, ptr %418, ptr %fgAnim)
  %419 = load i1, ptr %rtPtr16, align 1
  %420 = load ptr, ptr %fgAnim, align 8
  %421 = getelementptr inbounds %FlowWingAnim, ptr %420, i32 0, i32 0
  %422 = load ptr, ptr %421, align 8
  %423 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %422, i32 0, i32 4
  %424 = load ptr, ptr %423, align 8
  %425 = load ptr, ptr %fgAnim, align 8
  %426 = getelementptr inbounds %FlowWingAnim, ptr %425, i32 0, i32 6
  %427 = getelementptr inbounds %KEYS_TYPE.2, ptr %426, i32 0, i32 3
  %KEY_UP200 = load i32, ptr %427, align 4
  call void %424(ptr %rtPtr17, ptr %427, ptr %fgAnim)
  %428 = load i1, ptr %rtPtr17, align 1
  %429 = select i1 %419, i1 true, i1 %428
  br i1 %429, label %then201, label %else202

checkContinueBlock87:                             ; preds = %afterIfElse203
  %430 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %431 = icmp eq i32 %430, 0
  br i1 %431, label %nestedBlock88, label %afterNestedBlock75

nestedBlock88:                                    ; preds = %checkContinueBlock87
  %432 = load ptr, ptr %cloud, align 8
  %433 = getelementptr inbounds %Cloud, ptr %432, i32 0, i32 0
  %434 = load ptr, ptr %433, align 8
  %435 = getelementptr inbounds %"Cloud::VTableType", ptr %434, i32 0, i32 4
  %436 = load ptr, ptr %435, align 8
  %437 = load ptr, ptr %fgAnim, align 8
  %438 = getelementptr inbounds %FlowWingAnim, ptr %437, i32 0, i32 0
  %439 = load ptr, ptr %438, align 8
  %440 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %439, i32 0, i32 8
  %441 = load ptr, ptr %440, align 8
  call void %441(ptr %34, ptr %fgAnim)
  call void %436(ptr %34, ptr %cloud)
  %442 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %443 = icmp eq i32 %442, 0
  br i1 %443, label %checkContinueBlock89, label %afterNestedBlock75

checkContinueBlock89:                             ; preds = %nestedBlock88
  %444 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %445 = icmp eq i32 %444, 0
  br i1 %445, label %nestedBlock90, label %afterNestedBlock75

nestedBlock90:                                    ; preds = %checkContinueBlock89
  %446 = load ptr, ptr %fgAnim, align 8
  %447 = getelementptr inbounds %FlowWingAnim, ptr %446, i32 0, i32 0
  %448 = load ptr, ptr %447, align 8
  %449 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %448, i32 0, i32 15
  %450 = load ptr, ptr %449, align 8
  call void %450(ptr %fgAnim)
  %451 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %452 = icmp eq i32 %451, 0
  br i1 %452, label %checkContinueBlock91, label %afterNestedBlock75

checkContinueBlock91:                             ; preds = %nestedBlock90
  %453 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %454 = icmp eq i32 %453, 0
  br i1 %454, label %nestedBlock92, label %afterNestedBlock75

nestedBlock92:                                    ; preds = %checkContinueBlock91
  %455 = load ptr, ptr %fgAnim, align 8
  %456 = getelementptr inbounds %FlowWingAnim, ptr %455, i32 0, i32 0
  %457 = load ptr, ptr %456, align 8
  %458 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %457, i32 0, i32 10
  %459 = load ptr, ptr %458, align 8
  %460 = load ptr, ptr %fgAnim, align 8
  %461 = getelementptr inbounds %FlowWingAnim, ptr %460, i32 0, i32 5
  %462 = getelementptr inbounds %COLORS_TYPE.3, ptr %461, i32 0, i32 1
  %RED = load i32, ptr %462, align 4
  call void %459(ptr %462, ptr %fgAnim)
  %463 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %464 = icmp eq i32 %463, 0
  br i1 %464, label %checkContinueBlock93, label %afterNestedBlock75

checkContinueBlock93:                             ; preds = %nestedBlock92
  %465 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %466 = icmp eq i32 %465, 0
  br i1 %466, label %nestedBlock94, label %afterNestedBlock75

nestedBlock94:                                    ; preds = %checkContinueBlock93
  %467 = getelementptr [4 x float], ptr %35, i32 0, i32 0
  store float 0.000000e+00, ptr %467, align 4
  %468 = getelementptr [4 x float], ptr %35, i32 0, i32 1
  store float 0.000000e+00, ptr %468, align 4
  %469 = getelementptr [4 x float], ptr %35, i32 0, i32 2
  store float 3.840000e+03, ptr %469, align 4
  %470 = getelementptr [4 x float], ptr %35, i32 0, i32 3
  store float 2.160000e+03, ptr %470, align 4
  %471 = load [4 x float], ptr %35, align 4
  %472 = getelementptr [4 x float], ptr %36, i32 0, i32 0
  store float 0.000000e+00, ptr %472, align 4
  %473 = getelementptr [4 x float], ptr %36, i32 0, i32 1
  store float 0.000000e+00, ptr %473, align 4
  %474 = getelementptr [4 x float], ptr %36, i32 0, i32 2
  %screenWidth207 = load i32, ptr @screenWidth, align 4
  %475 = load i32, ptr @screenWidth, align 4
  %476 = sitofp i32 %475 to float
  store float %476, ptr %474, align 4
  %477 = getelementptr [4 x float], ptr %36, i32 0, i32 3
  %screenHeight208 = load i32, ptr @screenHeight, align 4
  %478 = load i32, ptr @screenHeight, align 4
  %479 = sitofp i32 %478 to float
  store float %479, ptr %477, align 4
  %480 = load [4 x float], ptr %36, align 4
  %481 = getelementptr [2 x float], ptr %37, i32 0, i32 0
  store float 0.000000e+00, ptr %481, align 4
  %482 = getelementptr [2 x float], ptr %37, i32 0, i32 1
  store float 0.000000e+00, ptr %482, align 4
  %483 = load [2 x float], ptr %37, align 4
  %484 = load ptr, ptr %fgAnim, align 8
  %485 = getelementptr inbounds %FlowWingAnim, ptr %484, i32 0, i32 5
  %486 = getelementptr inbounds %COLORS_TYPE.3, ptr %485, i32 0, i32 0
  %WHITE = load i32, ptr %486, align 4
  %487 = load i32, ptr %486, align 4
  call void @DrawTexturePro(ptr %backgroundTexture, [4 x float] %471, [4 x float] %480, [2 x float] %483, float 0.000000e+00, i32 %487)
  %488 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %489 = icmp eq i32 %488, 0
  br i1 %489, label %checkContinueBlock95, label %afterNestedBlock75

checkContinueBlock95:                             ; preds = %nestedBlock94
  %490 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %491 = icmp eq i32 %490, 0
  br i1 %491, label %nestedBlock96, label %afterNestedBlock75

nestedBlock96:                                    ; preds = %checkContinueBlock95
  %492 = load ptr, ptr %cloud, align 8
  %493 = getelementptr inbounds %Cloud, ptr %492, i32 0, i32 0
  %494 = load ptr, ptr %493, align 8
  %495 = getelementptr inbounds %"Cloud::VTableType", ptr %494, i32 0, i32 0
  %496 = load ptr, ptr %495, align 8
  call void %496(ptr %fgAnim, ptr %cloud)
  %497 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %498 = icmp eq i32 %497, 0
  br i1 %498, label %checkContinueBlock97, label %afterNestedBlock75

checkContinueBlock97:                             ; preds = %nestedBlock96
  %499 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %500 = icmp eq i32 %499, 0
  br i1 %500, label %nestedBlock98, label %afterNestedBlock75

nestedBlock98:                                    ; preds = %checkContinueBlock97
  %501 = getelementptr [4 x float], ptr %38, i32 0, i32 0
  store float 0.000000e+00, ptr %501, align 4
  %502 = getelementptr [4 x float], ptr %38, i32 0, i32 1
  store float 0.000000e+00, ptr %502, align 4
  %503 = getelementptr [4 x float], ptr %38, i32 0, i32 2
  store float 5.975000e+03, ptr %503, align 4
  %504 = getelementptr [4 x float], ptr %38, i32 0, i32 3
  store float 1.607000e+03, ptr %504, align 4
  %505 = load [4 x float], ptr %38, align 4
  %506 = getelementptr [4 x float], ptr %39, i32 0, i32 0
  store float 0.000000e+00, ptr %506, align 4
  %507 = getelementptr [4 x float], ptr %39, i32 0, i32 1
  %screenHeight209 = load i32, ptr @screenHeight, align 4
  %508 = load i32, ptr @screenHeight, align 4
  %509 = sitofp i32 %508 to double
  %510 = fdiv double %509, 3.000000e+00
  %511 = fptrunc double %510 to float
  store float %511, ptr %507, align 4
  %512 = getelementptr [4 x float], ptr %39, i32 0, i32 2
  %screenWidth210 = load i32, ptr @screenWidth, align 4
  %513 = load i32, ptr @screenWidth, align 4
  %514 = sitofp i32 %513 to double
  %515 = fdiv double %514, 2.000000e+00
  %516 = fptrunc double %515 to float
  store float %516, ptr %512, align 4
  %517 = getelementptr [4 x float], ptr %39, i32 0, i32 3
  %screenHeight211 = load i32, ptr @screenHeight, align 4
  %518 = load i32, ptr @screenHeight, align 4
  %519 = sitofp i32 %518 to double
  %520 = fdiv double %519, 3.000000e+00
  %521 = fptrunc double %520 to float
  store float %521, ptr %517, align 4
  %522 = load [4 x float], ptr %39, align 4
  %523 = getelementptr [2 x float], ptr %40, i32 0, i32 0
  %524 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x212 = load float, ptr %524, align 4
  %525 = load float, ptr %524, align 4
  store float %525, ptr %523, align 4
  %526 = getelementptr [2 x float], ptr %40, i32 0, i32 1
  %527 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  %y = load float, ptr %527, align 4
  %528 = load float, ptr %527, align 4
  store float %528, ptr %526, align 4
  %529 = load [2 x float], ptr %40, align 4
  %530 = load ptr, ptr %fgAnim, align 8
  %531 = getelementptr inbounds %FlowWingAnim, ptr %530, i32 0, i32 5
  %532 = getelementptr inbounds %COLORS_TYPE.3, ptr %531, i32 0, i32 0
  %WHITE213 = load i32, ptr %532, align 4
  %533 = load i32, ptr %532, align 4
  call void @DrawTexturePro(ptr %mountL2Texture, [4 x float] %505, [4 x float] %522, [2 x float] %529, float 0.000000e+00, i32 %533)
  %534 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %535 = icmp eq i32 %534, 0
  br i1 %535, label %checkContinueBlock99, label %afterNestedBlock75

checkContinueBlock99:                             ; preds = %nestedBlock98
  %536 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %537 = icmp eq i32 %536, 0
  br i1 %537, label %nestedBlock100, label %afterNestedBlock75

nestedBlock100:                                   ; preds = %checkContinueBlock99
  %538 = getelementptr [4 x float], ptr %41, i32 0, i32 0
  store float 0.000000e+00, ptr %538, align 4
  %539 = getelementptr [4 x float], ptr %41, i32 0, i32 1
  store float 0.000000e+00, ptr %539, align 4
  %540 = getelementptr [4 x float], ptr %41, i32 0, i32 2
  store float 4.461000e+03, ptr %540, align 4
  %541 = getelementptr [4 x float], ptr %41, i32 0, i32 3
  store float 1.989000e+03, ptr %541, align 4
  %542 = load [4 x float], ptr %41, align 4
  %543 = getelementptr [4 x float], ptr %42, i32 0, i32 0
  store float 0.000000e+00, ptr %543, align 4
  %544 = getelementptr [4 x float], ptr %42, i32 0, i32 1
  %screenHeight214 = load i32, ptr @screenHeight, align 4
  %545 = load i32, ptr @screenHeight, align 4
  %546 = sitofp i32 %545 to double
  %547 = fdiv double %546, 3.000000e+00
  %548 = fptrunc double %547 to float
  store float %548, ptr %544, align 4
  %549 = getelementptr [4 x float], ptr %42, i32 0, i32 2
  %screenWidth215 = load i32, ptr @screenWidth, align 4
  %550 = load i32, ptr @screenWidth, align 4
  %551 = sitofp i32 %550 to double
  %552 = fdiv double %551, 2.000000e+00
  %553 = fptrunc double %552 to float
  store float %553, ptr %549, align 4
  %554 = getelementptr [4 x float], ptr %42, i32 0, i32 3
  %screenHeight216 = load i32, ptr @screenHeight, align 4
  %555 = load i32, ptr @screenHeight, align 4
  %556 = sitofp i32 %555 to double
  %557 = fdiv double %556, 3.000000e+00
  %558 = fptrunc double %557 to float
  store float %558, ptr %554, align 4
  %559 = load [4 x float], ptr %42, align 4
  %560 = getelementptr [2 x float], ptr %43, i32 0, i32 0
  %561 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x217 = load float, ptr %561, align 4
  %562 = load float, ptr %561, align 4
  store float %562, ptr %560, align 4
  %563 = getelementptr [2 x float], ptr %43, i32 0, i32 1
  %564 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  %y218 = load float, ptr %564, align 4
  %565 = load float, ptr %564, align 4
  store float %565, ptr %563, align 4
  %566 = load [2 x float], ptr %43, align 4
  %567 = load ptr, ptr %fgAnim, align 8
  %568 = getelementptr inbounds %FlowWingAnim, ptr %567, i32 0, i32 5
  %569 = getelementptr inbounds %COLORS_TYPE.3, ptr %568, i32 0, i32 0
  %WHITE219 = load i32, ptr %569, align 4
  %570 = load i32, ptr %569, align 4
  call void @DrawTexturePro(ptr %mount2L2Texture, [4 x float] %542, [4 x float] %559, [2 x float] %566, float 0.000000e+00, i32 %570)
  %571 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %572 = icmp eq i32 %571, 0
  br i1 %572, label %checkContinueBlock101, label %afterNestedBlock75

checkContinueBlock101:                            ; preds = %nestedBlock100
  %573 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %574 = icmp eq i32 %573, 0
  br i1 %574, label %nestedBlock102, label %afterNestedBlock75

nestedBlock102:                                   ; preds = %checkContinueBlock101
  %575 = getelementptr [4 x float], ptr %44, i32 0, i32 0
  store float 0.000000e+00, ptr %575, align 4
  %576 = getelementptr [4 x float], ptr %44, i32 0, i32 1
  store float 0.000000e+00, ptr %576, align 4
  %577 = getelementptr [4 x float], ptr %44, i32 0, i32 2
  store float 6.005000e+03, ptr %577, align 4
  %578 = getelementptr [4 x float], ptr %44, i32 0, i32 3
  store float 2.376000e+03, ptr %578, align 4
  %579 = load [4 x float], ptr %44, align 4
  %580 = getelementptr [4 x float], ptr %45, i32 0, i32 0
  store float 0.000000e+00, ptr %580, align 4
  %581 = getelementptr [4 x float], ptr %45, i32 0, i32 1
  %screenHeight220 = load i32, ptr @screenHeight, align 4
  %582 = load i32, ptr @screenHeight, align 4
  %583 = sitofp i32 %582 to double
  %584 = fdiv double %583, 3.000000e+00
  %585 = fptrunc double %584 to float
  store float %585, ptr %581, align 4
  %586 = getelementptr [4 x float], ptr %45, i32 0, i32 2
  %screenWidth221 = load i32, ptr @screenWidth, align 4
  %587 = load i32, ptr @screenWidth, align 4
  %588 = sitofp i32 %587 to double
  %589 = fdiv double %588, 2.000000e+00
  %590 = fptrunc double %589 to float
  store float %590, ptr %586, align 4
  %591 = getelementptr [4 x float], ptr %45, i32 0, i32 3
  %screenHeight222 = load i32, ptr @screenHeight, align 4
  %592 = load i32, ptr @screenHeight, align 4
  %593 = sitofp i32 %592 to double
  %594 = fdiv double %593, 3.000000e+00
  %595 = fptrunc double %594 to float
  store float %595, ptr %591, align 4
  %596 = load [4 x float], ptr %45, align 4
  %597 = getelementptr [2 x float], ptr %46, i32 0, i32 0
  %598 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x223 = load float, ptr %598, align 4
  %599 = load float, ptr %598, align 4
  store float %599, ptr %597, align 4
  %600 = getelementptr [2 x float], ptr %46, i32 0, i32 1
  %601 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  %y224 = load float, ptr %601, align 4
  %602 = load float, ptr %601, align 4
  store float %602, ptr %600, align 4
  %603 = load [2 x float], ptr %46, align 4
  %604 = load ptr, ptr %fgAnim, align 8
  %605 = getelementptr inbounds %FlowWingAnim, ptr %604, i32 0, i32 5
  %606 = getelementptr inbounds %COLORS_TYPE.3, ptr %605, i32 0, i32 0
  %WHITE225 = load i32, ptr %606, align 4
  %607 = load i32, ptr %606, align 4
  call void @DrawTexturePro(ptr %mount1L3Texture, [4 x float] %579, [4 x float] %596, [2 x float] %603, float 0.000000e+00, i32 %607)
  %608 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %609 = icmp eq i32 %608, 0
  br i1 %609, label %checkContinueBlock103, label %afterNestedBlock75

checkContinueBlock103:                            ; preds = %nestedBlock102
  %610 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %611 = icmp eq i32 %610, 0
  br i1 %611, label %nestedBlock104, label %afterNestedBlock75

nestedBlock104:                                   ; preds = %checkContinueBlock103
  %612 = getelementptr [4 x float], ptr %47, i32 0, i32 0
  store float 0.000000e+00, ptr %612, align 4
  %613 = getelementptr [4 x float], ptr %47, i32 0, i32 1
  store float 0.000000e+00, ptr %613, align 4
  %614 = getelementptr [4 x float], ptr %47, i32 0, i32 2
  store float 8.982000e+03, ptr %614, align 4
  %615 = getelementptr [4 x float], ptr %47, i32 0, i32 3
  store float 1.542000e+03, ptr %615, align 4
  %616 = load [4 x float], ptr %47, align 4
  %617 = getelementptr [4 x float], ptr %48, i32 0, i32 0
  store float 0.000000e+00, ptr %617, align 4
  %618 = getelementptr [4 x float], ptr %48, i32 0, i32 1
  %screenHeight226 = load i32, ptr @screenHeight, align 4
  %619 = load i32, ptr @screenHeight, align 4
  %620 = sitofp i32 %619 to double
  %621 = fdiv double %620, 3.000000e+00
  %622 = fptrunc double %621 to float
  store float %622, ptr %618, align 4
  %623 = getelementptr [4 x float], ptr %48, i32 0, i32 2
  %screenWidth227 = load i32, ptr @screenWidth, align 4
  %624 = load i32, ptr @screenWidth, align 4
  %screenWidth228 = load i32, ptr @screenWidth, align 4
  %625 = load i32, ptr @screenWidth, align 4
  %626 = sitofp i32 %625 to double
  %627 = fdiv double %626, 2.000000e+00
  %628 = sitofp i32 %624 to double
  %629 = fadd double %628, %627
  %630 = fptrunc double %629 to float
  store float %630, ptr %623, align 4
  %631 = getelementptr [4 x float], ptr %48, i32 0, i32 3
  %screenHeight229 = load i32, ptr @screenHeight, align 4
  %632 = load i32, ptr @screenHeight, align 4
  %633 = sitofp i32 %632 to double
  %634 = fdiv double %633, 3.000000e+00
  %635 = fptrunc double %634 to float
  store float %635, ptr %631, align 4
  %636 = load [4 x float], ptr %48, align 4
  %637 = getelementptr [2 x float], ptr %49, i32 0, i32 0
  %638 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x230 = load float, ptr %638, align 4
  %639 = load float, ptr %638, align 4
  store float %639, ptr %637, align 4
  %640 = getelementptr [2 x float], ptr %49, i32 0, i32 1
  %641 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y231 = load float, ptr %641, align 4
  %642 = load float, ptr %641, align 4
  store float %642, ptr %640, align 4
  %643 = load [2 x float], ptr %49, align 4
  %644 = load ptr, ptr %fgAnim, align 8
  %645 = getelementptr inbounds %FlowWingAnim, ptr %644, i32 0, i32 5
  %646 = getelementptr inbounds %COLORS_TYPE.3, ptr %645, i32 0, i32 0
  %WHITE232 = load i32, ptr %646, align 4
  %647 = load i32, ptr %646, align 4
  call void @DrawTexturePro(ptr %mountL1Texture, [4 x float] %616, [4 x float] %636, [2 x float] %643, float 0.000000e+00, i32 %647)
  %648 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %649 = icmp eq i32 %648, 0
  br i1 %649, label %checkContinueBlock105, label %afterNestedBlock75

checkContinueBlock105:                            ; preds = %nestedBlock104
  %650 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %651 = icmp eq i32 %650, 0
  br i1 %651, label %nestedBlock106, label %afterNestedBlock75

nestedBlock106:                                   ; preds = %checkContinueBlock105
  %652 = getelementptr [4 x float], ptr %50, i32 0, i32 0
  store float 0.000000e+00, ptr %652, align 4
  %653 = getelementptr [4 x float], ptr %50, i32 0, i32 1
  store float 0.000000e+00, ptr %653, align 4
  %654 = getelementptr [4 x float], ptr %50, i32 0, i32 2
  store float 8.982000e+03, ptr %654, align 4
  %655 = getelementptr [4 x float], ptr %50, i32 0, i32 3
  store float 1.542000e+03, ptr %655, align 4
  %656 = load [4 x float], ptr %50, align 4
  %657 = getelementptr [4 x float], ptr %51, i32 0, i32 0
  store float 0.000000e+00, ptr %657, align 4
  %658 = getelementptr [4 x float], ptr %51, i32 0, i32 1
  %screenHeight233 = load i32, ptr @screenHeight, align 4
  %659 = load i32, ptr @screenHeight, align 4
  %660 = sitofp i32 %659 to double
  %661 = fdiv double %660, 3.000000e+00
  %662 = fptrunc double %661 to float
  store float %662, ptr %658, align 4
  %663 = getelementptr [4 x float], ptr %51, i32 0, i32 2
  %screenWidth234 = load i32, ptr @screenWidth, align 4
  %664 = load i32, ptr @screenWidth, align 4
  %screenWidth235 = load i32, ptr @screenWidth, align 4
  %665 = load i32, ptr @screenWidth, align 4
  %666 = sitofp i32 %665 to double
  %667 = fdiv double %666, 2.000000e+00
  %668 = sitofp i32 %664 to double
  %669 = fadd double %668, %667
  %670 = fptrunc double %669 to float
  store float %670, ptr %663, align 4
  %671 = getelementptr [4 x float], ptr %51, i32 0, i32 3
  %screenHeight236 = load i32, ptr @screenHeight, align 4
  %672 = load i32, ptr @screenHeight, align 4
  %673 = sitofp i32 %672 to double
  %674 = fdiv double %673, 3.000000e+00
  %675 = fptrunc double %674 to float
  store float %675, ptr %671, align 4
  %676 = load [4 x float], ptr %51, align 4
  %677 = getelementptr [2 x float], ptr %52, i32 0, i32 0
  %678 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x237 = load float, ptr %678, align 4
  %679 = load float, ptr %678, align 4
  store float %679, ptr %677, align 4
  %680 = getelementptr [2 x float], ptr %52, i32 0, i32 1
  %681 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y238 = load float, ptr %681, align 4
  %682 = load float, ptr %681, align 4
  store float %682, ptr %680, align 4
  %683 = load [2 x float], ptr %52, align 4
  %684 = load ptr, ptr %fgAnim, align 8
  %685 = getelementptr inbounds %FlowWingAnim, ptr %684, i32 0, i32 5
  %686 = getelementptr inbounds %COLORS_TYPE.3, ptr %685, i32 0, i32 0
  %WHITE239 = load i32, ptr %686, align 4
  %687 = load i32, ptr %686, align 4
  call void @DrawTexturePro(ptr %mountL1Texture, [4 x float] %656, [4 x float] %676, [2 x float] %683, float 0.000000e+00, i32 %687)
  %688 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %689 = icmp eq i32 %688, 0
  br i1 %689, label %checkContinueBlock107, label %afterNestedBlock75

checkContinueBlock107:                            ; preds = %nestedBlock106
  %690 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %691 = icmp eq i32 %690, 0
  br i1 %691, label %nestedBlock108, label %afterNestedBlock75

nestedBlock108:                                   ; preds = %checkContinueBlock107
  %692 = getelementptr [4 x float], ptr %53, i32 0, i32 0
  store float 3.100000e+02, ptr %692, align 4
  %693 = getelementptr [4 x float], ptr %53, i32 0, i32 1
  store float 1.250000e+03, ptr %693, align 4
  %694 = getelementptr [4 x float], ptr %53, i32 0, i32 2
  store float 4.360000e+03, ptr %694, align 4
  %695 = getelementptr [4 x float], ptr %53, i32 0, i32 3
  store float 1.250000e+03, ptr %695, align 4
  %696 = load [4 x float], ptr %53, align 4
  %697 = getelementptr [4 x float], ptr %54, i32 0, i32 0
  store float 0.000000e+00, ptr %697, align 4
  %698 = getelementptr [4 x float], ptr %54, i32 0, i32 1
  %screenHeight240 = load i32, ptr @screenHeight, align 4
  %699 = load i32, ptr @screenHeight, align 4
  %700 = sitofp i32 %699 to double
  %701 = fdiv double %700, 2.000000e+00
  %screenHeight241 = load i32, ptr @screenHeight, align 4
  %702 = load i32, ptr @screenHeight, align 4
  %703 = sitofp i32 %702 to double
  %704 = fdiv double %703, 1.000000e+01
  %705 = fadd double %701, %704
  %706 = fptrunc double %705 to float
  store float %706, ptr %698, align 4
  %707 = getelementptr [4 x float], ptr %54, i32 0, i32 2
  %screenWidth242 = load i32, ptr @screenWidth, align 4
  %708 = load i32, ptr @screenWidth, align 4
  %709 = sitofp i32 %708 to float
  store float %709, ptr %707, align 4
  %710 = getelementptr [4 x float], ptr %54, i32 0, i32 3
  %screenHeight243 = load i32, ptr @screenHeight, align 4
  %711 = load i32, ptr @screenHeight, align 4
  %712 = sitofp i32 %711 to double
  %713 = fdiv double %712, 2.000000e+00
  %714 = fptrunc double %713 to float
  store float %714, ptr %710, align 4
  %715 = load [4 x float], ptr %54, align 4
  %716 = getelementptr [2 x float], ptr %55, i32 0, i32 0
  %717 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x244 = load float, ptr %717, align 4
  %718 = load float, ptr %717, align 4
  store float %718, ptr %716, align 4
  %719 = getelementptr [2 x float], ptr %55, i32 0, i32 1
  %720 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y245 = load float, ptr %720, align 4
  %721 = load float, ptr %720, align 4
  store float %721, ptr %719, align 4
  %722 = load [2 x float], ptr %55, align 4
  %723 = load ptr, ptr %fgAnim, align 8
  %724 = getelementptr inbounds %FlowWingAnim, ptr %723, i32 0, i32 5
  %725 = getelementptr inbounds %COLORS_TYPE.3, ptr %724, i32 0, i32 0
  %WHITE246 = load i32, ptr %725, align 4
  %726 = load i32, ptr %725, align 4
  call void @DrawTexturePro(ptr %groundTexture, [4 x float] %696, [4 x float] %715, [2 x float] %722, float 0.000000e+00, i32 %726)
  %727 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %728 = icmp eq i32 %727, 0
  br i1 %728, label %checkContinueBlock109, label %afterNestedBlock75

checkContinueBlock109:                            ; preds = %nestedBlock108
  %729 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %730 = icmp eq i32 %729, 0
  br i1 %730, label %nestedBlock110, label %afterNestedBlock75

nestedBlock110:                                   ; preds = %checkContinueBlock109
  %731 = getelementptr [4 x float], ptr %56, i32 0, i32 0
  store float 3.100000e+02, ptr %731, align 4
  %732 = getelementptr [4 x float], ptr %56, i32 0, i32 1
  store float 1.250000e+03, ptr %732, align 4
  %733 = getelementptr [4 x float], ptr %56, i32 0, i32 2
  store float 4.360000e+03, ptr %733, align 4
  %734 = getelementptr [4 x float], ptr %56, i32 0, i32 3
  store float 1.250000e+03, ptr %734, align 4
  %735 = load [4 x float], ptr %56, align 4
  %736 = getelementptr [4 x float], ptr %57, i32 0, i32 0
  store float 0.000000e+00, ptr %736, align 4
  %737 = getelementptr [4 x float], ptr %57, i32 0, i32 1
  %screenHeight247 = load i32, ptr @screenHeight, align 4
  %738 = load i32, ptr @screenHeight, align 4
  %739 = sitofp i32 %738 to double
  %740 = fdiv double %739, 2.000000e+00
  %screenHeight248 = load i32, ptr @screenHeight, align 4
  %741 = load i32, ptr @screenHeight, align 4
  %742 = sitofp i32 %741 to double
  %743 = fdiv double %742, 1.000000e+01
  %744 = fadd double %740, %743
  %745 = fptrunc double %744 to float
  store float %745, ptr %737, align 4
  %746 = getelementptr [4 x float], ptr %57, i32 0, i32 2
  %screenWidth249 = load i32, ptr @screenWidth, align 4
  %747 = load i32, ptr @screenWidth, align 4
  %748 = sitofp i32 %747 to float
  store float %748, ptr %746, align 4
  %749 = getelementptr [4 x float], ptr %57, i32 0, i32 3
  %screenHeight250 = load i32, ptr @screenHeight, align 4
  %750 = load i32, ptr @screenHeight, align 4
  %751 = sitofp i32 %750 to double
  %752 = fdiv double %751, 2.000000e+00
  %753 = fptrunc double %752 to float
  store float %753, ptr %749, align 4
  %754 = load [4 x float], ptr %57, align 4
  %755 = getelementptr [2 x float], ptr %58, i32 0, i32 0
  %756 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x251 = load float, ptr %756, align 4
  %757 = load float, ptr %756, align 4
  store float %757, ptr %755, align 4
  %758 = getelementptr [2 x float], ptr %58, i32 0, i32 1
  %759 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y252 = load float, ptr %759, align 4
  %760 = load float, ptr %759, align 4
  store float %760, ptr %758, align 4
  %761 = load [2 x float], ptr %58, align 4
  %762 = load ptr, ptr %fgAnim, align 8
  %763 = getelementptr inbounds %FlowWingAnim, ptr %762, i32 0, i32 5
  %764 = getelementptr inbounds %COLORS_TYPE.3, ptr %763, i32 0, i32 0
  %WHITE253 = load i32, ptr %764, align 4
  %765 = load i32, ptr %764, align 4
  call void @DrawTexturePro(ptr %groundTexture, [4 x float] %735, [4 x float] %754, [2 x float] %761, float 0.000000e+00, i32 %765)
  %766 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %767 = icmp eq i32 %766, 0
  br i1 %767, label %checkContinueBlock111, label %afterNestedBlock75

checkContinueBlock111:                            ; preds = %nestedBlock110
  %768 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %769 = icmp eq i32 %768, 0
  br i1 %769, label %nestedBlock112, label %afterNestedBlock75

nestedBlock112:                                   ; preds = %checkContinueBlock111
  %770 = load ptr, ptr %bird, align 8
  %771 = getelementptr inbounds %Bird, ptr %770, i32 0, i32 0
  %772 = load ptr, ptr %771, align 8
  %773 = getelementptr inbounds %"Bird::VTableType", ptr %772, i32 0, i32 0
  %774 = load ptr, ptr %773, align 8
  call void %774(ptr %59, ptr %bird)
  %775 = load ptr, ptr %bird, align 8
  %776 = getelementptr inbounds %Bird, ptr %775, i32 0, i32 0
  %777 = load ptr, ptr %776, align 8
  %778 = getelementptr inbounds %"Bird::VTableType", ptr %777, i32 0, i32 4
  %779 = load ptr, ptr %778, align 8
  call void %779(ptr %60, ptr %bird)
  %780 = load [4 x float], ptr %60, align 4
  %781 = load ptr, ptr %bird, align 8
  %782 = getelementptr inbounds %Bird, ptr %781, i32 0, i32 0
  %783 = load ptr, ptr %782, align 8
  %784 = getelementptr inbounds %"Bird::VTableType", ptr %783, i32 0, i32 3
  %785 = load ptr, ptr %784, align 8
  call void %785(ptr %61, ptr %bird)
  %786 = load [4 x float], ptr %61, align 4
  %787 = load ptr, ptr %bird, align 8
  %788 = getelementptr inbounds %Bird, ptr %787, i32 0, i32 0
  %789 = load ptr, ptr %788, align 8
  %790 = getelementptr inbounds %"Bird::VTableType", ptr %789, i32 0, i32 2
  %791 = load ptr, ptr %790, align 8
  call void %791(ptr %62, ptr %bird)
  %792 = load [2 x float], ptr %62, align 4
  %793 = load ptr, ptr %bird, align 8
  %794 = getelementptr inbounds %Bird, ptr %793, i32 0, i32 0
  %795 = load ptr, ptr %794, align 8
  %796 = getelementptr inbounds %"Bird::VTableType", ptr %795, i32 0, i32 1
  %797 = load ptr, ptr %796, align 8
  call void %797(ptr %63, ptr %bird)
  %798 = load float, ptr %63, align 4
  %799 = load ptr, ptr %fgAnim, align 8
  %800 = getelementptr inbounds %FlowWingAnim, ptr %799, i32 0, i32 5
  %801 = getelementptr inbounds %COLORS_TYPE.3, ptr %800, i32 0, i32 0
  %WHITE254 = load i32, ptr %801, align 4
  %802 = load i32, ptr %801, align 4
  call void @DrawTexturePro(ptr %59, [4 x float] %780, [4 x float] %786, [2 x float] %792, float %798, i32 %802)
  %803 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %804 = icmp eq i32 %803, 0
  br i1 %804, label %checkContinueBlock113, label %afterNestedBlock75

checkContinueBlock113:                            ; preds = %nestedBlock112
  %805 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %806 = icmp eq i32 %805, 0
  br i1 %806, label %nestedBlock114, label %afterNestedBlock75

nestedBlock114:                                   ; preds = %checkContinueBlock113
  %807 = load ptr, ptr %fgAnim, align 8
  %808 = getelementptr inbounds %FlowWingAnim, ptr %807, i32 0, i32 0
  %809 = load ptr, ptr %808, align 8
  %810 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %809, i32 0, i32 22
  %811 = load ptr, ptr %810, align 8
  call void %811(ptr %fgAnim)
  %812 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %813 = icmp eq i32 %812, 0
  br i1 %813, label %checkContinueBlock115, label %afterNestedBlock75

checkContinueBlock115:                            ; preds = %nestedBlock114
  br label %afterNestedBlock75

afterNestedBlock116:                              ; preds = %checkContinueBlock124, %afterIfElse139, %checkContinueBlock122, %afterIfElse131, %checkContinueBlock120, %nestedBlock119, %checkContinueBlock118, %nestedBlock117
  %814 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %815 = icmp eq i32 %814, 0
  br i1 %815, label %checkContinueBlock79, label %afterNestedBlock75

nestedBlock117:                                   ; preds = %nestedBlock78
  %816 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x = load float, ptr %816, align 4
  %817 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x125 = load float, ptr %817, align 4
  %818 = load float, ptr %817, align 4
  %819 = load ptr, ptr %fgAnim, align 8
  %820 = getelementptr inbounds %FlowWingAnim, ptr %819, i32 0, i32 0
  %821 = load ptr, ptr %820, align 8
  %822 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %821, i32 0, i32 8
  %823 = load ptr, ptr %822, align 8
  call void %823(ptr %rtPtr10, ptr %fgAnim)
  %824 = load float, ptr %rtPtr10, align 4
  %825 = fmul float %824, 1.000000e+02
  %826 = fadd float %818, %825
  store float %826, ptr %816, align 4
  %827 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %828 = icmp eq i32 %827, 0
  br i1 %828, label %checkContinueBlock118, label %afterNestedBlock116

checkContinueBlock118:                            ; preds = %nestedBlock117
  %829 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %830 = icmp eq i32 %829, 0
  br i1 %830, label %nestedBlock119, label %afterNestedBlock116

nestedBlock119:                                   ; preds = %checkContinueBlock118
  %831 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x126 = load float, ptr %831, align 4
  %832 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x127 = load float, ptr %832, align 4
  %833 = load float, ptr %832, align 4
  %834 = load ptr, ptr %fgAnim, align 8
  %835 = getelementptr inbounds %FlowWingAnim, ptr %834, i32 0, i32 0
  %836 = load ptr, ptr %835, align 8
  %837 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %836, i32 0, i32 8
  %838 = load ptr, ptr %837, align 8
  call void %838(ptr %rtPtr11, ptr %fgAnim)
  %839 = load float, ptr %rtPtr11, align 4
  %840 = fmul float %839, 1.000000e+02
  %841 = fadd float %833, %840
  store float %841, ptr %831, align 4
  %842 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %843 = icmp eq i32 %842, 0
  br i1 %843, label %checkContinueBlock120, label %afterNestedBlock116

checkContinueBlock120:                            ; preds = %nestedBlock119
  %844 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %845 = icmp eq i32 %844, 0
  br i1 %845, label %nestedBlock121, label %afterNestedBlock116

nestedBlock121:                                   ; preds = %checkContinueBlock120
  %846 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x128 = load float, ptr %846, align 4
  %847 = load float, ptr %846, align 4
  %848 = fcmp ogt float %847, 1.542000e+03
  br i1 %848, label %then129, label %else130

checkContinueBlock122:                            ; preds = %afterIfElse131
  %849 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %850 = icmp eq i32 %849, 0
  br i1 %850, label %nestedBlock123, label %afterNestedBlock116

nestedBlock123:                                   ; preds = %checkContinueBlock122
  %851 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x136 = load float, ptr %851, align 4
  %852 = load float, ptr %851, align 4
  %853 = fcmp ogt float %852, 1.542000e+03
  br i1 %853, label %then137, label %else138

checkContinueBlock124:                            ; preds = %afterIfElse139
  br label %afterNestedBlock116

then129:                                          ; preds = %nestedBlock121
  br label %nestedBlock133

else130:                                          ; preds = %nestedBlock121
  br label %afterIfElse131

afterIfElse131:                                   ; preds = %else130, %afterNestedBlock132
  %854 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %855 = icmp eq i32 %854, 0
  br i1 %855, label %checkContinueBlock122, label %afterNestedBlock116

afterNestedBlock132:                              ; preds = %checkContinueBlock134, %nestedBlock133
  %856 = load float, ptr %857, align 4
  br label %afterIfElse131

nestedBlock133:                                   ; preds = %then129
  %857 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x135 = load float, ptr %857, align 4
  store float -1.542000e+03, ptr %857, align 4
  %858 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %859 = icmp eq i32 %858, 0
  br i1 %859, label %checkContinueBlock134, label %afterNestedBlock132

checkContinueBlock134:                            ; preds = %nestedBlock133
  br label %afterNestedBlock132

then137:                                          ; preds = %nestedBlock123
  br label %nestedBlock141

else138:                                          ; preds = %nestedBlock123
  br label %afterIfElse139

afterIfElse139:                                   ; preds = %else138, %afterNestedBlock140
  %860 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %861 = icmp eq i32 %860, 0
  br i1 %861, label %checkContinueBlock124, label %afterNestedBlock116

afterNestedBlock140:                              ; preds = %checkContinueBlock142, %nestedBlock141
  %862 = load float, ptr %863, align 4
  br label %afterIfElse139

nestedBlock141:                                   ; preds = %then137
  %863 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x143 = load float, ptr %863, align 4
  store float -1.542000e+03, ptr %863, align 4
  %864 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %865 = icmp eq i32 %864, 0
  br i1 %865, label %checkContinueBlock142, label %afterNestedBlock140

checkContinueBlock142:                            ; preds = %nestedBlock141
  br label %afterNestedBlock140

afterNestedBlock144:                              ; preds = %checkContinueBlock148, %afterIfElse156, %checkContinueBlock146, %nestedBlock145
  %866 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %867 = icmp eq i32 %866, 0
  br i1 %867, label %checkContinueBlock81, label %afterNestedBlock75

nestedBlock145:                                   ; preds = %nestedBlock80
  %868 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x149 = load float, ptr %868, align 4
  %869 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x150 = load float, ptr %869, align 4
  %870 = load float, ptr %869, align 4
  %871 = load ptr, ptr %fgAnim, align 8
  %872 = getelementptr inbounds %FlowWingAnim, ptr %871, i32 0, i32 0
  %873 = load ptr, ptr %872, align 8
  %874 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %873, i32 0, i32 8
  %875 = load ptr, ptr %874, align 8
  call void %875(ptr %rtPtr12, ptr %fgAnim)
  %876 = load float, ptr %rtPtr12, align 4
  %877 = fmul float %876, 1.000000e+01
  %878 = fadd float %870, %877
  store float %878, ptr %868, align 4
  %879 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %880 = icmp eq i32 %879, 0
  br i1 %880, label %checkContinueBlock146, label %afterNestedBlock144

checkContinueBlock146:                            ; preds = %nestedBlock145
  %881 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %882 = icmp eq i32 %881, 0
  br i1 %882, label %nestedBlock147, label %afterNestedBlock144

nestedBlock147:                                   ; preds = %checkContinueBlock146
  %883 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x151 = load float, ptr %883, align 4
  %884 = load float, ptr %883, align 4
  %screenWidth152 = load i32, ptr @screenWidth, align 4
  %885 = load i32, ptr @screenWidth, align 4
  %screenWidth153 = load i32, ptr @screenWidth, align 4
  %886 = load i32, ptr @screenWidth, align 4
  %887 = sitofp i32 %886 to double
  %888 = fdiv double %887, 2.000000e+00
  %889 = sitofp i32 %885 to double
  %890 = fadd double %889, %888
  %891 = fptrunc double %890 to float
  %892 = fcmp ogt float %884, %891
  br i1 %892, label %then154, label %else155

checkContinueBlock148:                            ; preds = %afterIfElse156
  br label %afterNestedBlock144

then154:                                          ; preds = %nestedBlock147
  br label %nestedBlock158

else155:                                          ; preds = %nestedBlock147
  br label %afterIfElse156

afterIfElse156:                                   ; preds = %else155, %afterNestedBlock157
  %893 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %894 = icmp eq i32 %893, 0
  br i1 %894, label %checkContinueBlock148, label %afterNestedBlock144

afterNestedBlock157:                              ; preds = %checkContinueBlock159, %nestedBlock158
  %895 = load float, ptr %896, align 4
  br label %afterIfElse156

nestedBlock158:                                   ; preds = %then154
  %896 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x160 = load float, ptr %896, align 4
  %screenWidth161 = load i32, ptr @screenWidth, align 4
  %897 = load i32, ptr @screenWidth, align 4
  %898 = mul i32 -1, %897
  %899 = sitofp i32 %898 to float
  store float %899, ptr %896, align 4
  %900 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %901 = icmp eq i32 %900, 0
  br i1 %901, label %checkContinueBlock159, label %afterNestedBlock157

checkContinueBlock159:                            ; preds = %nestedBlock158
  br label %afterNestedBlock157

afterNestedBlock162:                              ; preds = %checkContinueBlock166, %afterIfElse174, %checkContinueBlock164, %nestedBlock163
  %902 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %903 = icmp eq i32 %902, 0
  br i1 %903, label %checkContinueBlock83, label %afterNestedBlock75

nestedBlock163:                                   ; preds = %nestedBlock82
  %904 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x167 = load float, ptr %904, align 4
  %905 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x168 = load float, ptr %905, align 4
  %906 = load float, ptr %905, align 4
  %907 = load ptr, ptr %fgAnim, align 8
  %908 = getelementptr inbounds %FlowWingAnim, ptr %907, i32 0, i32 0
  %909 = load ptr, ptr %908, align 8
  %910 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %909, i32 0, i32 8
  %911 = load ptr, ptr %910, align 8
  call void %911(ptr %rtPtr13, ptr %fgAnim)
  %912 = load float, ptr %rtPtr13, align 4
  %913 = fmul float %912, 1.000000e+01
  %914 = fadd float %906, %913
  store float %914, ptr %904, align 4
  %915 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %916 = icmp eq i32 %915, 0
  br i1 %916, label %checkContinueBlock164, label %afterNestedBlock162

checkContinueBlock164:                            ; preds = %nestedBlock163
  %917 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %918 = icmp eq i32 %917, 0
  br i1 %918, label %nestedBlock165, label %afterNestedBlock162

nestedBlock165:                                   ; preds = %checkContinueBlock164
  %919 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x169 = load float, ptr %919, align 4
  %920 = load float, ptr %919, align 4
  %screenWidth170 = load i32, ptr @screenWidth, align 4
  %921 = load i32, ptr @screenWidth, align 4
  %screenWidth171 = load i32, ptr @screenWidth, align 4
  %922 = load i32, ptr @screenWidth, align 4
  %923 = sitofp i32 %922 to double
  %924 = fdiv double %923, 2.000000e+00
  %925 = sitofp i32 %921 to double
  %926 = fadd double %925, %924
  %927 = fptrunc double %926 to float
  %928 = fcmp ogt float %920, %927
  br i1 %928, label %then172, label %else173

checkContinueBlock166:                            ; preds = %afterIfElse174
  br label %afterNestedBlock162

then172:                                          ; preds = %nestedBlock165
  br label %nestedBlock176

else173:                                          ; preds = %nestedBlock165
  br label %afterIfElse174

afterIfElse174:                                   ; preds = %else173, %afterNestedBlock175
  %929 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %930 = icmp eq i32 %929, 0
  br i1 %930, label %checkContinueBlock166, label %afterNestedBlock162

afterNestedBlock175:                              ; preds = %checkContinueBlock177, %nestedBlock176
  %931 = load float, ptr %932, align 4
  br label %afterIfElse174

nestedBlock176:                                   ; preds = %then172
  %932 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x178 = load float, ptr %932, align 4
  %screenWidth179 = load i32, ptr @screenWidth, align 4
  %933 = load i32, ptr @screenWidth, align 4
  %934 = mul i32 -1, %933
  %935 = sitofp i32 %934 to float
  store float %935, ptr %932, align 4
  %936 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %937 = icmp eq i32 %936, 0
  br i1 %937, label %checkContinueBlock177, label %afterNestedBlock175

checkContinueBlock177:                            ; preds = %nestedBlock176
  br label %afterNestedBlock175

afterNestedBlock180:                              ; preds = %checkContinueBlock184, %afterIfElse192, %checkContinueBlock182, %nestedBlock181
  %938 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %939 = icmp eq i32 %938, 0
  br i1 %939, label %checkContinueBlock85, label %afterNestedBlock75

nestedBlock181:                                   ; preds = %nestedBlock84
  %940 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x185 = load float, ptr %940, align 4
  %941 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x186 = load float, ptr %941, align 4
  %942 = load float, ptr %941, align 4
  %943 = load ptr, ptr %fgAnim, align 8
  %944 = getelementptr inbounds %FlowWingAnim, ptr %943, i32 0, i32 0
  %945 = load ptr, ptr %944, align 8
  %946 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %945, i32 0, i32 8
  %947 = load ptr, ptr %946, align 8
  call void %947(ptr %rtPtr14, ptr %fgAnim)
  %948 = load float, ptr %rtPtr14, align 4
  %949 = fmul float %948, 1.000000e+01
  %950 = fadd float %942, %949
  store float %950, ptr %940, align 4
  %951 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %952 = icmp eq i32 %951, 0
  br i1 %952, label %checkContinueBlock182, label %afterNestedBlock180

checkContinueBlock182:                            ; preds = %nestedBlock181
  %953 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %954 = icmp eq i32 %953, 0
  br i1 %954, label %nestedBlock183, label %afterNestedBlock180

nestedBlock183:                                   ; preds = %checkContinueBlock182
  %955 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x187 = load float, ptr %955, align 4
  %956 = load float, ptr %955, align 4
  %screenWidth188 = load i32, ptr @screenWidth, align 4
  %957 = load i32, ptr @screenWidth, align 4
  %screenWidth189 = load i32, ptr @screenWidth, align 4
  %958 = load i32, ptr @screenWidth, align 4
  %959 = sitofp i32 %958 to double
  %960 = fdiv double %959, 2.000000e+00
  %961 = sitofp i32 %957 to double
  %962 = fadd double %961, %960
  %963 = fptrunc double %962 to float
  %964 = fcmp ogt float %956, %963
  br i1 %964, label %then190, label %else191

checkContinueBlock184:                            ; preds = %afterIfElse192
  br label %afterNestedBlock180

then190:                                          ; preds = %nestedBlock183
  br label %nestedBlock194

else191:                                          ; preds = %nestedBlock183
  br label %afterIfElse192

afterIfElse192:                                   ; preds = %else191, %afterNestedBlock193
  %965 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %966 = icmp eq i32 %965, 0
  br i1 %966, label %checkContinueBlock184, label %afterNestedBlock180

afterNestedBlock193:                              ; preds = %checkContinueBlock195, %nestedBlock194
  %967 = load float, ptr %968, align 4
  br label %afterIfElse192

nestedBlock194:                                   ; preds = %then190
  %968 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x196 = load float, ptr %968, align 4
  %screenWidth197 = load i32, ptr @screenWidth, align 4
  %969 = load i32, ptr @screenWidth, align 4
  %970 = mul i32 -1, %969
  %screenWidth198 = load i32, ptr @screenWidth, align 4
  %971 = load i32, ptr @screenWidth, align 4
  %972 = sitofp i32 %971 to double
  %973 = fdiv double %972, 4.000000e+00
  %974 = fptosi double %973 to i32
  store i32 %974, ptr %29, align 4
  %screenWidth199 = load i32, ptr @screenWidth, align 4
  %975 = load i32, ptr @screenWidth, align 4
  %976 = sitofp i32 %975 to double
  %977 = fdiv double %976, 2.000000e+00
  %978 = fptosi double %977 to i32
  store i32 %978, ptr %30, align 4
  call void @getRandomNumber(ptr %rtPtr15, ptr %29, ptr %30)
  %979 = load i32, ptr %rtPtr15, align 4
  %980 = sub i32 %970, %979
  %981 = sitofp i32 %980 to float
  store float %981, ptr %968, align 4
  %982 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %983 = icmp eq i32 %982, 0
  br i1 %983, label %checkContinueBlock195, label %afterNestedBlock193

checkContinueBlock195:                            ; preds = %nestedBlock194
  br label %afterNestedBlock193

then201:                                          ; preds = %nestedBlock86
  br label %nestedBlock205

else202:                                          ; preds = %nestedBlock86
  br label %afterIfElse203

afterIfElse203:                                   ; preds = %else202, %afterNestedBlock204
  %984 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %985 = icmp eq i32 %984, 0
  br i1 %985, label %checkContinueBlock87, label %afterNestedBlock75

afterNestedBlock204:                              ; preds = %checkContinueBlock206, %nestedBlock205
  br label %afterIfElse203

nestedBlock205:                                   ; preds = %then201
  %986 = load ptr, ptr %bird, align 8
  %987 = getelementptr inbounds %Bird, ptr %986, i32 0, i32 0
  %988 = load ptr, ptr %987, align 8
  %989 = getelementptr inbounds %"Bird::VTableType", ptr %988, i32 0, i32 8
  %990 = load ptr, ptr %989, align 8
  %991 = load ptr, ptr %fgAnim, align 8
  %992 = getelementptr inbounds %FlowWingAnim, ptr %991, i32 0, i32 0
  %993 = load ptr, ptr %992, align 8
  %994 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %993, i32 0, i32 8
  %995 = load ptr, ptr %994, align 8
  call void %995(ptr %33, ptr %fgAnim)
  call void %990(ptr %33, ptr %bird)
  %996 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %997 = icmp eq i32 %996, 0
  br i1 %997, label %checkContinueBlock206, label %afterNestedBlock204

checkContinueBlock206:                            ; preds = %nestedBlock205
  br label %afterNestedBlock204

decrement_block255:                               ; preds = %while.end
  %998 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %999 = sub i32 %998, 1
  store i32 %999, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block256

end_block256:                                     ; preds = %decrement_block255, %while.end
  %1000 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1001 = icmp eq i32 %1000, 0
  br i1 %1001, label %checkContinueBlock53, label %afterNestedBlock

returnBlock257:                                   ; preds = %nestedBlock56
  store i32 0, ptr %0, align 4
  ret void

mergeBlock258:                                    ; No predecessors!
  %1002 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1003 = icmp eq i32 %1002, 0
  br i1 %1003, label %checkContinueBlock57, label %afterNestedBlock
}

define internal void @"assign_<Object<COLORS_TYPE.3>>"(ptr %0) {
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

define internal void @"assign_<Object<KEYS_TYPE.2>>"(ptr %0) {
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

define internal void @"assign_<Object<LOG_TYPE.1>>"(ptr %0) {
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

define internal void @"assign_<Object<Texture.0>>"(ptr %0) {
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

define internal void @"assign_<Array<Object<Position.4>>>:9,"(ptr %0) {
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
  call void @"assign_<Object<Position.4>>"(ptr %7)
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

define internal void @"assign_<Object<Position.4>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Position.4, ptr %0, i32 0, i32 0
  store float 0.000000e+00, ptr %1, align 4
  %2 = getelementptr inbounds %Position.4, ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %2, align 4
  ret void
}

define internal void @"assign_<Array<Object<AttributeType.5>>>:5,"(ptr %0) {
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
  call void @"assign_<Object<AttributeType.5>>"(ptr %7)
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

define internal void @"assign_<Object<AttributeType.5>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 0
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %1)
  %2 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 1
  call void @"assign_<Array<'Decimal32'>>:4,"(ptr %2)
  %3 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 2
  call void @"assign_<Array<'Decimal32'>>:2,"(ptr %3)
  %4 = getelementptr inbounds %AttributeType.5, ptr %0, i32 0, i32 3
  store float 0.000000e+00, ptr %4, align 4
  ret void
}

define internal void @"assign_<Array<'Decimal32'>>:4,"(ptr %0) {
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

define internal void @"assign_<Array<'Decimal32'>>:2,"(ptr %0) {
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

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()

declare !rt !43 void @drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !24 void @FlowWingAnim.textFormat.1(ptr, ptr, ptr)

declare !rt !22 void @FlowWingAnim.isKeyPressed.2(ptr, ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture.3(ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture.4(ptr, ptr, ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle.5(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow.6(ptr)

declare !rt !19 void @FlowWingAnim.traceLog.7(ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText.8(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !44 void @SetTargetFPS(i32)

declare !rt !7 void @FlowWingAnim.beginDrawing.9(ptr)

declare !rt !15 void @FlowWingAnim.drawCircle.10(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.getScreenWidth.11(ptr, ptr)

declare !rt !45 void @getRandomNumber(ptr, ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit.12(ptr)

declare !rt !13 void @FlowWingAnim.getScreenHeight.13(ptr, ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.14(ptr)

declare !rt !9 void @FlowWingAnim.endDrawing.15(ptr)

declare !rt !3 void @FlowWingAnim.getColor.16(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.17(ptr)

declare !rt !0 void @FlowWingAnim.init4.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !46 void @ClearBackground(i32)

declare !rt !47 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !12 void @FlowWingAnim.getFrameTime.19(ptr, ptr)

declare !rt !48 void @TraceLog(i32, ptr)

declare !rt !49 i32 @GetScreenWidth()

declare !rt !50 void @DrawCircle(i32, i32, float, i32)

declare !rt !51 i32 @time()

declare !rt !52 void @BeginDrawing()

declare !rt !53 i1 @IsKeyPressed(i32)

declare !rt !54 i1 @WindowShouldClose()

declare !rt !55 void @InitWindow(i32, i32, ptr)

declare !rt !56 void @EndDrawing()

declare !rt !57 void @CloseWindow()

declare !rt !17 void @FlowWingAnim.drawTexture.20(ptr, ptr, ptr, ptr, ptr)

declare !rt !58 i32 @GetScreenHeight()

declare !rt !18 void @FlowWingAnim.drawTexturePro.21(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !59 float @GetFrameTime()

declare !rt !60 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !61 double @GetTime()

declare !rt !62 void @UnloadTexture(ptr)

declare !rt !63 ptr @TextFormat(ptr)

declare !rt !23 void @FlowWingAnim.isKeyDown.22(ptr, ptr, ptr)

declare !rt !64 void @LoadTexture(ptr sret(%Texture.0), ptr)

declare !rt !65 i1 @IsKeyDown(i32)

declare !rt !6 void @FlowWingAnim.windowShouldClose.23(ptr, ptr)

declare !rt !66 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !67 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !68 void @srand(i32)

declare !rt !11 void @FlowWingAnim.getTime.24(ptr, ptr)

declare !rt !5 void @FlowWingAnim.clearBackground.25(ptr, ptr)

declare !rt !69 i32 @rand()

define internal void @"assign_<Class<Texture.0>>"(ptr %0) {
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

define internal void @"assign_<Class<FlowWingAnim>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 0
  store ptr @19, ptr %1, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  store ptr @20, ptr %4, align 8
  %5 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  call void @"assign_<Object<COLORS_TYPE.3>>"(ptr %6)
  %7 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 6
  call void @"assign_<Object<KEYS_TYPE.2>>"(ptr %7)
  %8 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 7
  call void @"assign_<Object<LOG_TYPE.1>>"(ptr %8)
  ret void
}

define internal void @"assign_<Class<Bird>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 0
  store ptr @23, ptr %1, align 8
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
  store ptr @24, ptr %8, align 8
  %9 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 8
  store i1 false, ptr %9, align 1
  %10 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 9
  call void @"assign_<Class<Texture.0>>"(ptr %10)
  %11 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 10
  call void @"assign_<Array<Object<Position.4>>>:9,"(ptr %11)
  %12 = getelementptr inbounds %Bird, ptr %0, i32 0, i32 11
  call void @"assign_<Object<Position.4>>"(ptr %12)
  ret void
}

define internal void @"assign_<Class<Cloud>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 0
  store ptr @27, ptr %1, align 8
  %2 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 1
  call void @"assign_<Array<Object<AttributeType.5>>>:5,"(ptr %2)
  %3 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 2
  call void @"assign_<Class<Texture.0>>"(ptr %3)
  %4 = getelementptr inbounds %Cloud, ptr %0, i32 0, i32 3
  store ptr @28, ptr %4, align 8
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
!42 = !{!"main:rt:pr:28"}
!43 = !{!"drawTexturePro:rt:pr:27"}
!44 = !{!"SetTargetFPS:rt:pr:27"}
!45 = !{!"getRandomNumber:rt:pr:28"}
!46 = !{!"ClearBackground:rt:pr:27"}
!47 = !{!"DrawTexturePro:rt:pr:27"}
!48 = !{!"TraceLog:rt:pr:27"}
!49 = !{!"GetScreenWidth:rt:pr:28"}
!50 = !{!"DrawCircle:rt:pr:27"}
!51 = !{!"time:rt:pr:28"}
!52 = !{!"BeginDrawing:rt:pr:27"}
!53 = !{!"IsKeyPressed:rt:pr:34"}
!54 = !{!"WindowShouldClose:rt:pr:34"}
!55 = !{!"InitWindow:rt:pr:27"}
!56 = !{!"EndDrawing:rt:pr:27"}
!57 = !{!"CloseWindow:rt:pr:27"}
!58 = !{!"GetScreenHeight:rt:pr:28"}
!59 = !{!"GetFrameTime:rt:pr:32"}
!60 = !{!"DrawText:rt:pr:27"}
!61 = !{!"GetTime:rt:pr:31"}
!62 = !{!"UnloadTexture:rt:pr:27"}
!63 = !{!"TextFormat:rt:pr:33"}
!64 = !{!"LoadTexture:rt:ob:Texture.0"}
!65 = !{!"IsKeyDown:rt:pr:34"}
!66 = !{!"DrawRectangle:rt:pr:27"}
!67 = !{!"DrawTexture:rt:pr:27"}
!68 = !{!"srand:rt:pr:27"}
!69 = !{!"rand:rt:pr:28"}
