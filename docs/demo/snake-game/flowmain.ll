; ModuleID = 'flowmain'
source_filename = "flowmain"
target triple = "x86_64-apple-macosx14.0.0"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Bird::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Cloud::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%Bird = type { ptr, float, float, double, double, i32, i32, ptr, i1, %Texture.0, [9 x %Position.4], %Position.4 }
%Position.4 = type { float, float }
%Cloud = type { ptr, [5 x %AttributeType.5], %Texture.0, ptr }
%AttributeType.5 = type { [4 x float], [4 x float], [2 x float], float }
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
@screenWidth = common global i32 0
@screenHeight = common global i32 0
@FPS = common global i32 0
@side = common global i32 0
@vtable.Bird.fg = common global %"Bird::VTableType" zeroinitializer
@vtable.Cloud.fg = common global %"Cloud::VTableType" zeroinitializer
@0 = private unnamed_addr constant [875 x i8] c"\0A\1B[33m80| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m84| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 84:32\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@1 = private unnamed_addr constant [953 x i8] c"\0A\1B[33m80| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m84| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 84:71\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [840 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:14\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [854 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:24\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [884 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:36\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [898 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:46\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@6 = private unnamed_addr constant [851 x i8] c"\0A\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                 \0A   ~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 178:17\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@7 = private unnamed_addr constant [865 x i8] c"\0A\1B[33m174| \1B[0m\1B[0m  update(frameTime: deci32) -> nthg {\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[31m\1B[1m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[32m\1B[1m                           \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 178:27\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@8 = private unnamed_addr constant [815 x i8] c"\0A\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 179:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [829 x i8] c"\0A\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[31m\1B[1m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m180| \1B[0m\1B[0m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 179:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [815 x i8] c"\0A\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 180:16\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [829 x i8] c"\0A\1B[33m176| \1B[0m\1B[0m    for var i = 0 to 4 {  \0A\1B[0m\1B[33m177| \1B[0m\1B[0m      clouds[i].origin[0] = clouds[i].origin[0] + frameTime * ((10))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      if clouds[i].origin[0] > 250.0d {\0A\1B[0m\1B[33m179| \1B[0m\1B[0m        clouds[i].origin[0] = Decimal32(getRandomNumber(-2*screenWidth,-1*screenWidth))\0A\1B[0m\1B[33m180| \1B[0m\1B[31m\1B[1m        clouds[i].origin[1] = -1*Decimal32(getRandomNumber(0,Int32(screenHeight/3)))\0A\1B[0m\1B[32m\1B[1m                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m181| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m182| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m183| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 180:26\1B[31m \22Index out of bounds of '' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [744 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:40\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [778 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                         \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:57\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [822 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                               \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:79\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [856 x i8] c"\0A\1B[33m184| \1B[0m\1B[0m\0A\1B[0m\1B[33m185| \1B[0m\1B[0m  draw(inout fgAnim: FlowWingAnim) -> nthg {\0A\1B[0m\1B[33m186| \1B[0m\1B[0m\0A\1B[0m\1B[33m187| \1B[0m\1B[0m  for var i = 0 to 4 {\0A\1B[0m\1B[33m188| \1B[0m\1B[31m\1B[1m    DrawTexturePro(cloudTexture,clouds[i].source,clouds[i].distination,clouds[i].origin,clouds[i].rotation,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m189| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m190| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m191| \1B[0m\1B[0m}\0A\1B[0m\1B[33m192| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 188:96\1B[31m \22Index out of bounds of 'clouds' in index expression, index value should be between 0 and 5\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@16 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@17 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@18 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [18 x i8] c"./assets/bird.png\00", align 1
@22 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [21 x i8] c"./assets/3clouds.png\00", align 1
@25 = private unnamed_addr constant [27 x i8] c"./assets/skyBackground.png\00", align 1
@26 = private unnamed_addr constant [20 x i8] c"./assets/ground.png\00", align 1
@27 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL1.png\00", align 1
@28 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL2.png\00", align 1
@29 = private unnamed_addr constant [31 x i8] c"./assets/mountain/2mountL2.png\00", align 1
@30 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL3.png\00", align 1
@31 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1

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
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()
  store i32 0, ptr @screenWidth, align 4
  store i32 1024, ptr @screenWidth, align 4
  store i32 0, ptr @screenHeight, align 4
  store i32 500, ptr @screenHeight, align 4
  store i32 0, ptr @FPS, align 4
  store i32 120, ptr @FPS, align 4
  store i32 0, ptr @side, align 4
  store i32 10, ptr @side, align 4
  %rtPtr = alloca i32, align 4
  call void @main(ptr %rtPtr)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()

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

declare !rt !25 void @drawTexturePro(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !24 void @FlowWingAnim.textFormat.1(ptr, ptr, ptr)

declare !rt !22 void @FlowWingAnim.isKeyPressed.2(ptr, ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture.3(ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture.4(ptr, ptr, ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle.5(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow.6(ptr)

declare !rt !19 void @FlowWingAnim.traceLog.7(ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText.8(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !26 void @SetTargetFPS(i32)

declare !rt !7 void @FlowWingAnim.beginDrawing.9(ptr)

declare !rt !15 void @FlowWingAnim.drawCircle.10(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.getScreenWidth.11(ptr, ptr)

declare !rt !27 void @getRandomNumber(ptr, ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit.12(ptr)

declare !rt !13 void @FlowWingAnim.getScreenHeight.13(ptr, ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.14(ptr)

declare !rt !9 void @FlowWingAnim.endDrawing.15(ptr)

declare !rt !3 void @FlowWingAnim.getColor.16(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.17(ptr)

declare !rt !0 void @FlowWingAnim.init4.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !28 void @ClearBackground(i32)

declare !rt !29 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !12 void @FlowWingAnim.getFrameTime.19(ptr, ptr)

declare !rt !30 void @TraceLog(i32, ptr)

declare !rt !31 i32 @GetScreenWidth()

declare !rt !32 void @DrawCircle(i32, i32, float, i32)

declare !rt !33 i32 @time()

declare !rt !34 void @BeginDrawing()

declare !rt !35 i1 @IsKeyPressed(i32)

declare !rt !36 i1 @WindowShouldClose()

declare !rt !37 void @InitWindow(i32, i32, ptr)

declare !rt !38 void @EndDrawing()

declare !rt !39 void @CloseWindow()

declare !rt !17 void @FlowWingAnim.drawTexture.20(ptr, ptr, ptr, ptr, ptr)

declare !rt !40 i32 @GetScreenHeight()

declare !rt !18 void @FlowWingAnim.drawTexturePro.21(ptr, ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !41 float @GetFrameTime()

declare !rt !42 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !43 double @GetTime()

declare !rt !44 void @UnloadTexture(ptr)

declare !rt !45 ptr @TextFormat(ptr)

declare !rt !23 void @FlowWingAnim.isKeyDown.22(ptr, ptr, ptr)

declare !rt !46 void @LoadTexture(ptr sret(%Texture.0) align 4, ptr)

declare !rt !47 i1 @IsKeyDown(i32)

declare !rt !6 void @FlowWingAnim.windowShouldClose.23(ptr, ptr)

declare !rt !48 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !49 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !50 void @srand(i32)

declare !rt !11 void @FlowWingAnim.getTime.24(ptr, ptr)

declare !rt !5 void @FlowWingAnim.clearBackground.25(ptr, ptr)

declare !rt !51 i32 @rand()

define void @Bird.init1(ptr %0, ptr %1) !rt !52 {
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
  %39 = alloca float, align 4
  store float %38, ptr %39, align 4
  %40 = load float, ptr %39, align 4
  store float %40, ptr %36, align 4
  %41 = getelementptr inbounds %Position.4, ptr %35, i32 0, i32 1
  store float 0.000000e+00, ptr %41, align 4
  %42 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 2
  %43 = getelementptr inbounds %Position.4, ptr %42, i32 0, i32 0
  %ACTUAL_BIRD_SIZE9 = load float, ptr %2, align 4
  %44 = load float, ptr %2, align 4
  %45 = fmul float %44, 2.000000e+00
  %46 = alloca float, align 4
  store float %45, ptr %46, align 4
  %47 = load float, ptr %46, align 4
  store float %47, ptr %43, align 4
  %48 = getelementptr inbounds %Position.4, ptr %42, i32 0, i32 1
  store float 0.000000e+00, ptr %48, align 4
  %49 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 3
  %50 = getelementptr inbounds %Position.4, ptr %49, i32 0, i32 0
  store float 0.000000e+00, ptr %50, align 4
  %51 = getelementptr inbounds %Position.4, ptr %49, i32 0, i32 1
  %ACTUAL_BIRD_SIZE10 = load float, ptr %2, align 4
  %52 = load float, ptr %2, align 4
  %53 = fmul float %52, 1.000000e+00
  %54 = alloca float, align 4
  store float %53, ptr %54, align 4
  %55 = load float, ptr %54, align 4
  store float %55, ptr %51, align 4
  %56 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 4
  %57 = getelementptr inbounds %Position.4, ptr %56, i32 0, i32 0
  %ACTUAL_BIRD_SIZE11 = load float, ptr %2, align 4
  %58 = load float, ptr %2, align 4
  %59 = fmul float %58, 1.000000e+00
  %60 = alloca float, align 4
  store float %59, ptr %60, align 4
  %61 = load float, ptr %60, align 4
  store float %61, ptr %57, align 4
  %62 = getelementptr inbounds %Position.4, ptr %56, i32 0, i32 1
  %ACTUAL_BIRD_SIZE12 = load float, ptr %2, align 4
  %63 = load float, ptr %2, align 4
  %64 = fmul float %63, 1.000000e+00
  %65 = alloca float, align 4
  store float %64, ptr %65, align 4
  %66 = load float, ptr %65, align 4
  store float %66, ptr %62, align 4
  %67 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 5
  %68 = getelementptr inbounds %Position.4, ptr %67, i32 0, i32 0
  %ACTUAL_BIRD_SIZE13 = load float, ptr %2, align 4
  %69 = load float, ptr %2, align 4
  %70 = fmul float %69, 2.000000e+00
  %71 = alloca float, align 4
  store float %70, ptr %71, align 4
  %72 = load float, ptr %71, align 4
  store float %72, ptr %68, align 4
  %73 = getelementptr inbounds %Position.4, ptr %67, i32 0, i32 1
  %ACTUAL_BIRD_SIZE14 = load float, ptr %2, align 4
  %74 = load float, ptr %2, align 4
  %75 = fmul float %74, 1.000000e+00
  %76 = alloca float, align 4
  store float %75, ptr %76, align 4
  %77 = load float, ptr %76, align 4
  store float %77, ptr %73, align 4
  %78 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 6
  %79 = getelementptr inbounds %Position.4, ptr %78, i32 0, i32 0
  store float 0.000000e+00, ptr %79, align 4
  %80 = getelementptr inbounds %Position.4, ptr %78, i32 0, i32 1
  %ACTUAL_BIRD_SIZE15 = load float, ptr %2, align 4
  %81 = load float, ptr %2, align 4
  %82 = fmul float %81, 2.000000e+00
  %83 = alloca float, align 4
  store float %82, ptr %83, align 4
  %84 = load float, ptr %83, align 4
  store float %84, ptr %80, align 4
  %85 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 7
  %86 = getelementptr inbounds %Position.4, ptr %85, i32 0, i32 0
  %ACTUAL_BIRD_SIZE16 = load float, ptr %2, align 4
  %87 = load float, ptr %2, align 4
  %88 = fmul float %87, 1.000000e+00
  %89 = alloca float, align 4
  store float %88, ptr %89, align 4
  %90 = load float, ptr %89, align 4
  store float %90, ptr %86, align 4
  %91 = getelementptr inbounds %Position.4, ptr %85, i32 0, i32 1
  %ACTUAL_BIRD_SIZE17 = load float, ptr %2, align 4
  %92 = load float, ptr %2, align 4
  %93 = fmul float %92, 2.000000e+00
  %94 = alloca float, align 4
  store float %93, ptr %94, align 4
  %95 = load float, ptr %94, align 4
  store float %95, ptr %91, align 4
  %96 = getelementptr [9 x %Position.4], ptr %31, i32 0, i32 8
  %97 = getelementptr inbounds %Position.4, ptr %96, i32 0, i32 0
  %ACTUAL_BIRD_SIZE18 = load float, ptr %2, align 4
  %98 = load float, ptr %2, align 4
  %99 = fmul float %98, 2.000000e+00
  %100 = alloca float, align 4
  store float %99, ptr %100, align 4
  %101 = load float, ptr %100, align 4
  store float %101, ptr %97, align 4
  %102 = getelementptr inbounds %Position.4, ptr %96, i32 0, i32 1
  %ACTUAL_BIRD_SIZE19 = load float, ptr %2, align 4
  %103 = load float, ptr %2, align 4
  %104 = fmul float %103, 2.000000e+00
  %105 = alloca float, align 4
  store float %104, ptr %105, align 4
  %106 = load float, ptr %105, align 4
  store float %106, ptr %102, align 4
  %107 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @Bird.setTexture(ptr %0, ptr %1) !rt !53 {
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

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %13 = getelementptr inbounds %Bird, ptr %1, i32 0, i32 9
  %14 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %14, ptr %13, align 4
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Bird.getTexturePath(ptr %0, ptr %1) !rt !54 {
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

define void @Bird.update(ptr %0, ptr %1) !rt !55 {
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
  %18 = alloca double, align 8
  store double %17, ptr %18, align 8
  %19 = load double, ptr %18, align 8
  store double %19, ptr %5, align 8
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %22 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %birdTimmer5 = load double, ptr %5, align 8
  %24 = load double, ptr %5, align 8
  %25 = fcmp olt double %24, 0.000000e+00
  %26 = alloca i1, align 1
  store i1 %25, ptr %26, align 1
  %27 = load i1, ptr %26, align 1
  br i1 %27, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse20, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %birdTimmer15 = load double, ptr %5, align 8
  %BIRD_TIMMER = load double, ptr %4, align 8
  %30 = load double, ptr %4, align 8
  store double %30, ptr %5, align 8
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  %33 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock9, label %afterNestedBlock6

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %birdSpriteIndex = load i32, ptr %7, align 4
  %birdSpriteIndex16 = load i32, ptr %7, align 4
  %35 = load i32, ptr %7, align 4
  %36 = add i32 %35, 1
  %37 = alloca i32, align 4
  store i32 %36, ptr %37, align 4
  %38 = load i32, ptr %37, align 4
  store i32 %38, ptr %7, align 4
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock10, label %afterNestedBlock6

checkContinueBlock10:                             ; preds = %nestedBlock9
  %41 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock11, label %afterNestedBlock6

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %birdSpriteIndex17 = load i32, ptr %7, align 4
  %43 = load i32, ptr %7, align 4
  %BIRD_SPRITE_SIZE = load i32, ptr %6, align 4
  %44 = load i32, ptr %6, align 4
  %45 = icmp sge i32 %43, %44
  %46 = alloca i1, align 1
  store i1 %45, ptr %46, align 1
  %47 = load i1, ptr %46, align 1
  br i1 %47, label %then18, label %else19

checkContinueBlock12:                             ; preds = %afterIfElse20
  %48 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %nestedBlock13, label %afterNestedBlock6

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %50 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y = load float, ptr %50, align 4
  %51 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y25 = load float, ptr %51, align 4
  %52 = load float, ptr %51, align 4
  %frameTime26 = load float, ptr %frameTime, align 4
  %53 = load float, ptr %frameTime, align 4
  %54 = alloca i32, align 4
  store i32 -150, ptr %54, align 4
  %55 = load i32, ptr %54, align 4
  %56 = add i32 1, %55
  %57 = alloca i32, align 4
  store i32 %56, ptr %57, align 4
  %58 = load i32, ptr %57, align 4
  %59 = sitofp i32 %58 to float
  %60 = fmul float %53, %59
  %61 = alloca float, align 4
  store float %60, ptr %61, align 4
  %62 = load float, ptr %61, align 4
  %63 = fadd float %52, %62
  %64 = alloca float, align 4
  store float %63, ptr %64, align 4
  %65 = load float, ptr %64, align 4
  store float %65, ptr %50, align 4
  %66 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %checkContinueBlock14, label %afterNestedBlock6

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock6

then18:                                           ; preds = %nestedBlock11
  br label %nestedBlock22

else19:                                           ; preds = %nestedBlock11
  br label %afterIfElse20

afterIfElse20:                                    ; preds = %else19, %afterNestedBlock21
  %68 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %checkContinueBlock12, label %afterNestedBlock6

afterNestedBlock21:                               ; preds = %checkContinueBlock23, %nestedBlock22
  br label %afterIfElse20

nestedBlock22:                                    ; preds = %then18
  %birdSpriteIndex24 = load i32, ptr %7, align 4
  store i32 0, ptr %7, align 4
  %70 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %checkContinueBlock23, label %afterNestedBlock21

checkContinueBlock23:                             ; preds = %nestedBlock22
  br label %afterNestedBlock21
}

define void @Bird.isTextureLoaded(ptr %0, ptr %1) !rt !56 {
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
  %17 = alloca i1, align 1
  store i1 %16, ptr %17, align 1
  %18 = load i1, ptr %17, align 1
  store i1 %18, ptr %0, align 1
  ret void

mergeBlock:                                       ; No predecessors!
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getSource(ptr %0, ptr %1) !rt !57 {
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
  call void @raise_exception(ptr @0)
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
  call void @raise_exception(ptr @1)
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

define void @Bird.getDistination(ptr %0, ptr %1) !rt !58 {
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
  %17 = alloca double, align 8
  store double %16, ptr %17, align 8
  %18 = load double, ptr %17, align 8
  %birdSize = load float, ptr %3, align 4
  %19 = load float, ptr %3, align 4
  %20 = fdiv float %19, 2.000000e+00
  %21 = alloca float, align 4
  store float %20, ptr %21, align 4
  %22 = load float, ptr %21, align 4
  %23 = fptrunc double %18 to float
  %24 = fsub float %23, %22
  %25 = alloca float, align 4
  store float %24, ptr %25, align 4
  %26 = load float, ptr %25, align 4
  store float %26, ptr %13, align 4
  %27 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %28 = load i32, ptr @screenHeight, align 4
  %29 = sitofp i32 %28 to double
  %30 = fdiv double %29, 2.000000e+00
  %31 = alloca double, align 8
  store double %30, ptr %31, align 8
  %32 = load double, ptr %31, align 8
  %birdSize1 = load float, ptr %3, align 4
  %33 = load float, ptr %3, align 4
  %34 = fdiv float %33, 2.000000e+00
  %35 = alloca float, align 4
  store float %34, ptr %35, align 4
  %36 = load float, ptr %35, align 4
  %37 = fptrunc double %32 to float
  %38 = fsub float %37, %36
  %39 = alloca float, align 4
  store float %38, ptr %39, align 4
  %40 = load float, ptr %39, align 4
  store float %40, ptr %27, align 4
  %41 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %birdSize2 = load float, ptr %3, align 4
  %42 = load float, ptr %3, align 4
  store float %42, ptr %41, align 4
  %43 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %birdSize3 = load float, ptr %3, align 4
  %44 = load float, ptr %3, align 4
  store float %44, ptr %43, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock, label %afterNestedBlock
}

define void @Bird.getOrigin(ptr %0, ptr %1) !rt !59 {
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

define void @Bird.getRotation(ptr %0, ptr %1) !rt !60 {
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

define void @Bird.getTexture(ptr %0, ptr %1) !rt !61 {
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

define void @Bird.updateY(ptr %0, ptr %1) !rt !62 {
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
  %18 = alloca i32, align 4
  store i32 300, ptr %18, align 4
  %19 = load i32, ptr %18, align 4
  %20 = add i32 1, %19
  %21 = alloca i32, align 4
  store i32 %20, ptr %21, align 4
  %22 = load i32, ptr %21, align 4
  %23 = sitofp i32 %22 to float
  %24 = fmul float %17, %23
  %25 = alloca float, align 4
  store float %24, ptr %25, align 4
  %26 = load float, ptr %25, align 4
  %27 = fadd float %16, %26
  %28 = alloca float, align 4
  store float %27, ptr %28, align 4
  %29 = load float, ptr %28, align 4
  store float %29, ptr %14, align 4
  %30 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Cloud.init1(ptr %0, ptr %1) !rt !63 {
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
  %22 = alloca double, align 8
  store double 0x3FF818ACB90F6BF4, ptr %22, align 8
  %23 = load double, ptr %22, align 8
  %24 = fmul double %23, 1.000000e+02
  %25 = alloca double, align 8
  store double %24, ptr %25, align 8
  %26 = load double, ptr %25, align 8
  %27 = fptrunc double %26 to float
  store float %27, ptr %21, align 4
  %28 = getelementptr [4 x float], ptr %18, i32 0, i32 3
  store float 1.000000e+02, ptr %28, align 4
  %29 = getelementptr inbounds %AttributeType.5, ptr %12, i32 0, i32 2
  %30 = getelementptr [2 x float], ptr %29, i32 0, i32 0
  %rtPtr = alloca i32, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %31 = load i32, ptr @screenWidth, align 4
  %32 = mul i32 -1, %31
  %33 = alloca i32, align 4
  store i32 %32, ptr %33, align 4
  %34 = load i32, ptr %33, align 4
  %35 = alloca i32, align 4
  store i32 %34, ptr %35, align 4
  %36 = alloca i32, align 4
  store i32 0, ptr %36, align 4
  call void @getRandomNumber(ptr %rtPtr, ptr %35, ptr %36)
  %37 = load i32, ptr %rtPtr, align 4
  %38 = sitofp i32 %37 to float
  store float %38, ptr %30, align 4
  %39 = getelementptr [2 x float], ptr %29, i32 0, i32 1
  %rtPtr5 = alloca i32, align 4
  %40 = alloca i32, align 4
  store i32 0, ptr %40, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %41 = load i32, ptr @screenHeight, align 4
  %42 = sitofp i32 %41 to double
  %43 = fdiv double %42, 3.000000e+00
  %44 = alloca double, align 8
  store double %43, ptr %44, align 8
  %45 = load double, ptr %44, align 8
  %46 = fptosi double %45 to i32
  %47 = alloca i32, align 4
  store i32 %46, ptr %47, align 4
  call void @getRandomNumber(ptr %rtPtr5, ptr %40, ptr %47)
  %48 = load i32, ptr %rtPtr5, align 4
  %49 = sitofp i32 %48 to float
  %50 = fmul float -1.000000e+00, %49
  %51 = alloca float, align 4
  store float %50, ptr %51, align 4
  %52 = load float, ptr %51, align 4
  store float %52, ptr %39, align 4
  %53 = getelementptr inbounds %AttributeType.5, ptr %12, i32 0, i32 3
  store float 0.000000e+00, ptr %53, align 4
  %54 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 1
  %55 = getelementptr inbounds %AttributeType.5, ptr %54, i32 0, i32 0
  %56 = getelementptr [4 x float], ptr %55, i32 0, i32 0
  store float 2.500000e+02, ptr %56, align 4
  %57 = getelementptr [4 x float], ptr %55, i32 0, i32 1
  store float 0.000000e+00, ptr %57, align 4
  %58 = getelementptr [4 x float], ptr %55, i32 0, i32 2
  store float 2.500000e+02, ptr %58, align 4
  %59 = getelementptr [4 x float], ptr %55, i32 0, i32 3
  store float 1.660000e+02, ptr %59, align 4
  %60 = getelementptr inbounds %AttributeType.5, ptr %54, i32 0, i32 1
  %61 = getelementptr [4 x float], ptr %60, i32 0, i32 0
  store float 0.000000e+00, ptr %61, align 4
  %62 = getelementptr [4 x float], ptr %60, i32 0, i32 1
  store float 0.000000e+00, ptr %62, align 4
  %63 = getelementptr [4 x float], ptr %60, i32 0, i32 2
  %64 = alloca double, align 8
  store double 0x3FF818ACB90F6BF4, ptr %64, align 8
  %65 = load double, ptr %64, align 8
  %66 = fmul double %65, 1.000000e+02
  %67 = alloca double, align 8
  store double %66, ptr %67, align 8
  %68 = load double, ptr %67, align 8
  %69 = fptrunc double %68 to float
  store float %69, ptr %63, align 4
  %70 = getelementptr [4 x float], ptr %60, i32 0, i32 3
  store float 1.000000e+02, ptr %70, align 4
  %71 = getelementptr inbounds %AttributeType.5, ptr %54, i32 0, i32 2
  %72 = getelementptr [2 x float], ptr %71, i32 0, i32 0
  %rtPtr6 = alloca i32, align 4
  %screenWidth7 = load i32, ptr @screenWidth, align 4
  %73 = load i32, ptr @screenWidth, align 4
  %74 = mul i32 -1, %73
  %75 = alloca i32, align 4
  store i32 %74, ptr %75, align 4
  %76 = load i32, ptr %75, align 4
  %77 = alloca i32, align 4
  store i32 %76, ptr %77, align 4
  %78 = alloca i32, align 4
  store i32 0, ptr %78, align 4
  call void @getRandomNumber(ptr %rtPtr6, ptr %77, ptr %78)
  %79 = load i32, ptr %rtPtr6, align 4
  %80 = sitofp i32 %79 to float
  store float %80, ptr %72, align 4
  %81 = getelementptr [2 x float], ptr %71, i32 0, i32 1
  %rtPtr8 = alloca i32, align 4
  %82 = alloca i32, align 4
  store i32 0, ptr %82, align 4
  %screenHeight9 = load i32, ptr @screenHeight, align 4
  %83 = load i32, ptr @screenHeight, align 4
  %84 = sitofp i32 %83 to double
  %85 = fdiv double %84, 3.000000e+00
  %86 = alloca double, align 8
  store double %85, ptr %86, align 8
  %87 = load double, ptr %86, align 8
  %88 = fptosi double %87 to i32
  %89 = alloca i32, align 4
  store i32 %88, ptr %89, align 4
  call void @getRandomNumber(ptr %rtPtr8, ptr %82, ptr %89)
  %90 = load i32, ptr %rtPtr8, align 4
  %91 = sitofp i32 %90 to float
  %92 = fmul float -1.000000e+00, %91
  %93 = alloca float, align 4
  store float %92, ptr %93, align 4
  %94 = load float, ptr %93, align 4
  store float %94, ptr %81, align 4
  %95 = getelementptr inbounds %AttributeType.5, ptr %54, i32 0, i32 3
  store float 0.000000e+00, ptr %95, align 4
  %96 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 2
  %97 = getelementptr inbounds %AttributeType.5, ptr %96, i32 0, i32 0
  %98 = getelementptr [4 x float], ptr %97, i32 0, i32 0
  store float 0.000000e+00, ptr %98, align 4
  %99 = getelementptr [4 x float], ptr %97, i32 0, i32 1
  store float 1.660000e+02, ptr %99, align 4
  %100 = getelementptr [4 x float], ptr %97, i32 0, i32 2
  store float 5.000000e+02, ptr %100, align 4
  %101 = getelementptr [4 x float], ptr %97, i32 0, i32 3
  store float 1.660000e+02, ptr %101, align 4
  %102 = getelementptr inbounds %AttributeType.5, ptr %96, i32 0, i32 1
  %103 = getelementptr [4 x float], ptr %102, i32 0, i32 0
  store float 0.000000e+00, ptr %103, align 4
  %104 = getelementptr [4 x float], ptr %102, i32 0, i32 1
  store float 0.000000e+00, ptr %104, align 4
  %105 = getelementptr [4 x float], ptr %102, i32 0, i32 2
  %106 = alloca double, align 8
  store double 0x3FF818ACB90F6BF4, ptr %106, align 8
  %107 = load double, ptr %106, align 8
  %108 = fmul double %107, 1.000000e+02
  %109 = alloca double, align 8
  store double %108, ptr %109, align 8
  %110 = load double, ptr %109, align 8
  %111 = fptrunc double %110 to float
  store float %111, ptr %105, align 4
  %112 = getelementptr [4 x float], ptr %102, i32 0, i32 3
  store float 1.000000e+02, ptr %112, align 4
  %113 = getelementptr inbounds %AttributeType.5, ptr %96, i32 0, i32 2
  %114 = getelementptr [2 x float], ptr %113, i32 0, i32 0
  %rtPtr10 = alloca i32, align 4
  %screenWidth11 = load i32, ptr @screenWidth, align 4
  %115 = load i32, ptr @screenWidth, align 4
  %116 = mul i32 -1, %115
  %117 = alloca i32, align 4
  store i32 %116, ptr %117, align 4
  %118 = load i32, ptr %117, align 4
  %119 = alloca i32, align 4
  store i32 %118, ptr %119, align 4
  %120 = alloca i32, align 4
  store i32 0, ptr %120, align 4
  call void @getRandomNumber(ptr %rtPtr10, ptr %119, ptr %120)
  %121 = load i32, ptr %rtPtr10, align 4
  %122 = sitofp i32 %121 to float
  store float %122, ptr %114, align 4
  %123 = getelementptr [2 x float], ptr %113, i32 0, i32 1
  %rtPtr12 = alloca i32, align 4
  %124 = alloca i32, align 4
  store i32 0, ptr %124, align 4
  %screenHeight13 = load i32, ptr @screenHeight, align 4
  %125 = load i32, ptr @screenHeight, align 4
  %126 = sitofp i32 %125 to double
  %127 = fdiv double %126, 3.000000e+00
  %128 = alloca double, align 8
  store double %127, ptr %128, align 8
  %129 = load double, ptr %128, align 8
  %130 = fptosi double %129 to i32
  %131 = alloca i32, align 4
  store i32 %130, ptr %131, align 4
  call void @getRandomNumber(ptr %rtPtr12, ptr %124, ptr %131)
  %132 = load i32, ptr %rtPtr12, align 4
  %133 = sitofp i32 %132 to float
  %134 = fmul float -1.000000e+00, %133
  %135 = alloca float, align 4
  store float %134, ptr %135, align 4
  %136 = load float, ptr %135, align 4
  store float %136, ptr %123, align 4
  %137 = getelementptr inbounds %AttributeType.5, ptr %96, i32 0, i32 3
  store float 0.000000e+00, ptr %137, align 4
  %138 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 3
  %139 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 0
  %140 = getelementptr [4 x float], ptr %139, i32 0, i32 0
  store float 0.000000e+00, ptr %140, align 4
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
  %148 = alloca double, align 8
  store double 0x3FF818ACB90F6BF4, ptr %148, align 8
  %149 = load double, ptr %148, align 8
  %150 = fmul double %149, 1.000000e+02
  %151 = alloca double, align 8
  store double %150, ptr %151, align 8
  %152 = load double, ptr %151, align 8
  %153 = fptrunc double %152 to float
  store float %153, ptr %147, align 4
  %154 = getelementptr [4 x float], ptr %144, i32 0, i32 3
  store float 1.000000e+02, ptr %154, align 4
  %155 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 2
  %156 = getelementptr [2 x float], ptr %155, i32 0, i32 0
  %rtPtr14 = alloca i32, align 4
  %screenWidth15 = load i32, ptr @screenWidth, align 4
  %157 = load i32, ptr @screenWidth, align 4
  %158 = mul i32 -1, %157
  %159 = alloca i32, align 4
  store i32 %158, ptr %159, align 4
  %160 = load i32, ptr %159, align 4
  %161 = alloca i32, align 4
  store i32 %160, ptr %161, align 4
  %162 = alloca i32, align 4
  store i32 0, ptr %162, align 4
  call void @getRandomNumber(ptr %rtPtr14, ptr %161, ptr %162)
  %163 = load i32, ptr %rtPtr14, align 4
  %164 = sitofp i32 %163 to float
  store float %164, ptr %156, align 4
  %165 = getelementptr [2 x float], ptr %155, i32 0, i32 1
  %rtPtr16 = alloca i32, align 4
  %166 = alloca i32, align 4
  store i32 0, ptr %166, align 4
  %screenHeight17 = load i32, ptr @screenHeight, align 4
  %167 = load i32, ptr @screenHeight, align 4
  %168 = sitofp i32 %167 to double
  %169 = fdiv double %168, 3.000000e+00
  %170 = alloca double, align 8
  store double %169, ptr %170, align 8
  %171 = load double, ptr %170, align 8
  %172 = fptosi double %171 to i32
  %173 = alloca i32, align 4
  store i32 %172, ptr %173, align 4
  call void @getRandomNumber(ptr %rtPtr16, ptr %166, ptr %173)
  %174 = load i32, ptr %rtPtr16, align 4
  %175 = sitofp i32 %174 to float
  %176 = fmul float -1.000000e+00, %175
  %177 = alloca float, align 4
  store float %176, ptr %177, align 4
  %178 = load float, ptr %177, align 4
  store float %178, ptr %165, align 4
  %179 = getelementptr inbounds %AttributeType.5, ptr %138, i32 0, i32 3
  store float 0.000000e+00, ptr %179, align 4
  %180 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 4
  %181 = getelementptr inbounds %AttributeType.5, ptr %180, i32 0, i32 0
  %182 = getelementptr [4 x float], ptr %181, i32 0, i32 0
  store float 2.500000e+02, ptr %182, align 4
  %183 = getelementptr [4 x float], ptr %181, i32 0, i32 1
  store float 3.320000e+02, ptr %183, align 4
  %184 = getelementptr [4 x float], ptr %181, i32 0, i32 2
  store float 2.500000e+02, ptr %184, align 4
  %185 = getelementptr [4 x float], ptr %181, i32 0, i32 3
  store float 1.660000e+02, ptr %185, align 4
  %186 = getelementptr inbounds %AttributeType.5, ptr %180, i32 0, i32 1
  %187 = getelementptr [4 x float], ptr %186, i32 0, i32 0
  store float 0.000000e+00, ptr %187, align 4
  %188 = getelementptr [4 x float], ptr %186, i32 0, i32 1
  store float 0.000000e+00, ptr %188, align 4
  %189 = getelementptr [4 x float], ptr %186, i32 0, i32 2
  %190 = alloca double, align 8
  store double 0x3FF818ACB90F6BF4, ptr %190, align 8
  %191 = load double, ptr %190, align 8
  %192 = fmul double %191, 1.000000e+02
  %193 = alloca double, align 8
  store double %192, ptr %193, align 8
  %194 = load double, ptr %193, align 8
  %195 = fptrunc double %194 to float
  store float %195, ptr %189, align 4
  %196 = getelementptr [4 x float], ptr %186, i32 0, i32 3
  store float 1.000000e+02, ptr %196, align 4
  %197 = getelementptr inbounds %AttributeType.5, ptr %180, i32 0, i32 2
  %198 = getelementptr [2 x float], ptr %197, i32 0, i32 0
  %rtPtr18 = alloca i32, align 4
  %screenWidth19 = load i32, ptr @screenWidth, align 4
  %199 = load i32, ptr @screenWidth, align 4
  %200 = mul i32 -1, %199
  %201 = alloca i32, align 4
  store i32 %200, ptr %201, align 4
  %202 = load i32, ptr %201, align 4
  %203 = alloca i32, align 4
  store i32 %202, ptr %203, align 4
  %204 = alloca i32, align 4
  store i32 0, ptr %204, align 4
  call void @getRandomNumber(ptr %rtPtr18, ptr %203, ptr %204)
  %205 = load i32, ptr %rtPtr18, align 4
  %206 = sitofp i32 %205 to float
  store float %206, ptr %198, align 4
  %207 = getelementptr [2 x float], ptr %197, i32 0, i32 1
  %rtPtr20 = alloca i32, align 4
  %208 = alloca i32, align 4
  store i32 0, ptr %208, align 4
  %screenHeight21 = load i32, ptr @screenHeight, align 4
  %209 = load i32, ptr @screenHeight, align 4
  %210 = sitofp i32 %209 to double
  %211 = fdiv double %210, 3.000000e+00
  %212 = alloca double, align 8
  store double %211, ptr %212, align 8
  %213 = load double, ptr %212, align 8
  %214 = fptosi double %213 to i32
  %215 = alloca i32, align 4
  store i32 %214, ptr %215, align 4
  call void @getRandomNumber(ptr %rtPtr20, ptr %208, ptr %215)
  %216 = load i32, ptr %rtPtr20, align 4
  %217 = sitofp i32 %216 to float
  %218 = fmul float -1.000000e+00, %217
  %219 = alloca float, align 4
  store float %218, ptr %219, align 4
  %220 = load float, ptr %219, align 4
  store float %220, ptr %207, align 4
  %221 = getelementptr inbounds %AttributeType.5, ptr %180, i32 0, i32 3
  store float 0.000000e+00, ptr %221, align 4
  %222 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %223 = icmp eq i32 %222, 0
  br i1 %223, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @Cloud.setTexture(ptr %0, ptr %1) !rt !64 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %5 = call ptr @malloc(i64 20)
  %6 = load %Texture.0, ptr %0, align 4
  store %Texture.0 %6, ptr %5, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %8 = load %Texture.0, ptr %5, align 4
  store %Texture.0 %8, ptr %7, align 4
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Cloud.getTexture(ptr %0, ptr %1) !rt !65 {
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

define void @Cloud.getTexturePath(ptr %0, ptr %1) !rt !66 {
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

define void @Cloud.update(ptr %0, ptr %1) !rt !67 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  %frameTime = alloca float, align 4
  %5 = load float, ptr %0, align 4
  store float %5, ptr %frameTime, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block58
  ret void

nestedBlock:                                      ; preds = %entry
  %i = alloca %DynamicType, align 8
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
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %27 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %22
  %28 = getelementptr inbounds %AttributeType.5, ptr %27, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then6", label %"GlobalIndexExpr::else7"

"GlobalIndexExpr::then6":                         ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge8"

"GlobalIndexExpr::else7":                         ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @3)
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
  call void @raise_exception(ptr @4)
  br label %"GlobalIndexExpr::merge12"

"GlobalIndexExpr::merge12":                       ; preds = %"GlobalIndexExpr::else11", %"GlobalIndexExpr::then10"
  %33 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %32
  %34 = getelementptr inbounds %AttributeType.5, ptr %33, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then16", label %"GlobalIndexExpr::else17"

"GlobalIndexExpr::then16":                        ; preds = %"GlobalIndexExpr::merge12"
  br label %"GlobalIndexExpr::merge18"

"GlobalIndexExpr::else17":                        ; preds = %"GlobalIndexExpr::merge12"
  call void @raise_exception(ptr @5)
  br label %"GlobalIndexExpr::merge18"

"GlobalIndexExpr::merge18":                       ; preds = %"GlobalIndexExpr::else17", %"GlobalIndexExpr::then16"
  %35 = getelementptr [2 x float], ptr %34, i32 0, i32 0
  %36 = load float, ptr %35, align 4
  %frameTime19 = load float, ptr %frameTime, align 4
  %37 = load float, ptr %frameTime, align 4
  %38 = fmul float %37, 1.000000e+01
  %39 = alloca float, align 4
  store float %38, ptr %39, align 4
  %40 = load float, ptr %39, align 4
  %41 = fadd float %36, %40
  %42 = alloca float, align 4
  store float %41, ptr %42, align 4
  %43 = load float, ptr %42, align 4
  store float %43, ptr %29, align 4
  %44 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock3, label %afterNestedBlock1

"GlobalIndexExpr::then21":                        ; preds = %nestedBlock4
  br label %"GlobalIndexExpr::merge23"

"GlobalIndexExpr::else22":                        ; preds = %nestedBlock4
  call void @raise_exception(ptr @6)
  br label %"GlobalIndexExpr::merge23"

"GlobalIndexExpr::merge23":                       ; preds = %"GlobalIndexExpr::else22", %"GlobalIndexExpr::then21"
  %46 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %26
  %47 = getelementptr inbounds %AttributeType.5, ptr %46, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then27", label %"GlobalIndexExpr::else28"

"GlobalIndexExpr::then27":                        ; preds = %"GlobalIndexExpr::merge23"
  br label %"GlobalIndexExpr::merge29"

"GlobalIndexExpr::else28":                        ; preds = %"GlobalIndexExpr::merge23"
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge29"

"GlobalIndexExpr::merge29":                       ; preds = %"GlobalIndexExpr::else28", %"GlobalIndexExpr::then27"
  %48 = getelementptr [2 x float], ptr %47, i32 0, i32 0
  %49 = load float, ptr %48, align 4
  %50 = fcmp ogt float %49, 2.500000e+02
  %51 = alloca i1, align 1
  store i1 %50, ptr %51, align 1
  %52 = load i1, ptr %51, align 1
  br i1 %52, label %then, label %else

then:                                             ; preds = %"GlobalIndexExpr::merge29"
  br label %nestedBlock31

else:                                             ; preds = %"GlobalIndexExpr::merge29"
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock30
  %53 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %checkContinueBlock5, label %afterNestedBlock1

afterNestedBlock30:                               ; preds = %checkContinueBlock34, %"GlobalIndexExpr::merge55", %checkContinueBlock32, %"GlobalIndexExpr::merge44"
  br label %afterIfElse

nestedBlock31:                                    ; preds = %then
  %55 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %56 = load i32, ptr %55, align 4
  %clouds35 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan39" = icmp slt i32 %56, 5
  %"GlobalIndexExpr::isGreaterThan40" = icmp sge i32 %56, 0
  %"GlobalIndexExpr::isWithinBounds41" = and i1 %"GlobalIndexExpr::isLessThan39", %"GlobalIndexExpr::isGreaterThan40"
  br i1 %"GlobalIndexExpr::isWithinBounds41", label %"GlobalIndexExpr::then36", label %"GlobalIndexExpr::else37"

checkContinueBlock32:                             ; preds = %"GlobalIndexExpr::merge44"
  %57 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %nestedBlock33, label %afterNestedBlock30

nestedBlock33:                                    ; preds = %checkContinueBlock32
  %59 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %60 = load i32, ptr %59, align 4
  %clouds46 = load [5 x %AttributeType.5], ptr %2, align 4
  %"GlobalIndexExpr::isLessThan50" = icmp slt i32 %60, 5
  %"GlobalIndexExpr::isGreaterThan51" = icmp sge i32 %60, 0
  %"GlobalIndexExpr::isWithinBounds52" = and i1 %"GlobalIndexExpr::isLessThan50", %"GlobalIndexExpr::isGreaterThan51"
  br i1 %"GlobalIndexExpr::isWithinBounds52", label %"GlobalIndexExpr::then47", label %"GlobalIndexExpr::else48"

checkContinueBlock34:                             ; preds = %"GlobalIndexExpr::merge55"
  br label %afterNestedBlock30

"GlobalIndexExpr::then36":                        ; preds = %nestedBlock31
  br label %"GlobalIndexExpr::merge38"

"GlobalIndexExpr::else37":                        ; preds = %nestedBlock31
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge38"

"GlobalIndexExpr::merge38":                       ; preds = %"GlobalIndexExpr::else37", %"GlobalIndexExpr::then36"
  %61 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %56
  %62 = getelementptr inbounds %AttributeType.5, ptr %61, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then42", label %"GlobalIndexExpr::else43"

"GlobalIndexExpr::then42":                        ; preds = %"GlobalIndexExpr::merge38"
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::else43":                        ; preds = %"GlobalIndexExpr::merge38"
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::merge44":                       ; preds = %"GlobalIndexExpr::else43", %"GlobalIndexExpr::then42"
  %63 = getelementptr [2 x float], ptr %62, i32 0, i32 0
  %64 = load float, ptr %63, align 4
  %rtPtr = alloca i32, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %65 = load i32, ptr @screenWidth, align 4
  %66 = mul i32 -2, %65
  %67 = alloca i32, align 4
  store i32 %66, ptr %67, align 4
  %68 = load i32, ptr %67, align 4
  %69 = alloca i32, align 4
  store i32 %68, ptr %69, align 4
  %screenWidth45 = load i32, ptr @screenWidth, align 4
  %70 = load i32, ptr @screenWidth, align 4
  %71 = mul i32 -1, %70
  %72 = alloca i32, align 4
  store i32 %71, ptr %72, align 4
  %73 = load i32, ptr %72, align 4
  %74 = alloca i32, align 4
  store i32 %73, ptr %74, align 4
  call void @getRandomNumber(ptr %rtPtr, ptr %69, ptr %74)
  %75 = load i32, ptr %rtPtr, align 4
  %76 = sitofp i32 %75 to float
  store float %76, ptr %63, align 4
  %77 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %checkContinueBlock32, label %afterNestedBlock30

"GlobalIndexExpr::then47":                        ; preds = %nestedBlock33
  br label %"GlobalIndexExpr::merge49"

"GlobalIndexExpr::else48":                        ; preds = %nestedBlock33
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge49"

"GlobalIndexExpr::merge49":                       ; preds = %"GlobalIndexExpr::else48", %"GlobalIndexExpr::then47"
  %79 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %60
  %80 = getelementptr inbounds %AttributeType.5, ptr %79, i32 0, i32 2
  br i1 true, label %"GlobalIndexExpr::then53", label %"GlobalIndexExpr::else54"

"GlobalIndexExpr::then53":                        ; preds = %"GlobalIndexExpr::merge49"
  br label %"GlobalIndexExpr::merge55"

"GlobalIndexExpr::else54":                        ; preds = %"GlobalIndexExpr::merge49"
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge55"

"GlobalIndexExpr::merge55":                       ; preds = %"GlobalIndexExpr::else54", %"GlobalIndexExpr::then53"
  %81 = getelementptr [2 x float], ptr %80, i32 0, i32 1
  %82 = load float, ptr %81, align 4
  %rtPtr56 = alloca i32, align 4
  %83 = alloca i32, align 4
  store i32 0, ptr %83, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %84 = load i32, ptr @screenHeight, align 4
  %85 = sitofp i32 %84 to double
  %86 = fdiv double %85, 3.000000e+00
  %87 = alloca double, align 8
  store double %86, ptr %87, align 8
  %88 = load double, ptr %87, align 8
  %89 = fptosi double %88 to i32
  %90 = alloca i32, align 4
  store i32 %89, ptr %90, align 4
  call void @getRandomNumber(ptr %rtPtr56, ptr %83, ptr %90)
  %91 = load i32, ptr %rtPtr56, align 4
  %92 = sitofp i32 %91 to float
  %93 = fmul float -1.000000e+00, %92
  %94 = alloca float, align 4
  store float %93, ptr %94, align 4
  %95 = load float, ptr %94, align 4
  store float %95, ptr %81, align 4
  %96 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %97 = icmp eq i32 %96, 0
  br i1 %97, label %checkContinueBlock34, label %afterNestedBlock30

decrement_block57:                                ; preds = %"ForLoop::afterLoop"
  %98 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %99 = sub i32 %98, 1
  store i32 %99, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block58

end_block58:                                      ; preds = %decrement_block57, %"ForLoop::afterLoop"
  %100 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %checkContinueBlock, label %afterNestedBlock
}

define void @Cloud.draw(ptr %0, ptr %1) !rt !68 {
entry:
  %2 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Cloud, ptr %1, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %end_block26
  ret void

nestedBlock:                                      ; preds = %entry
  %i = alloca %DynamicType, align 8
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
  call void @raise_exception(ptr @12)
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
  call void @raise_exception(ptr @13)
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
  call void @raise_exception(ptr @14)
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
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge21"

"GlobalIndexExpr::merge21":                       ; preds = %"GlobalIndexExpr::else20", %"GlobalIndexExpr::then19"
  %37 = getelementptr [5 x %AttributeType.5], ptr %2, i32 0, i32 %36
  %38 = getelementptr inbounds %AttributeType.5, ptr %37, i32 0, i32 3
  %rotation = load float, ptr %38, align 4
  %39 = load float, ptr %38, align 4
  %40 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 5
  %41 = getelementptr inbounds %COLORS_TYPE.3, ptr %40, i32 0, i32 0
  %WHITE = load i32, ptr %41, align 4
  %42 = load i32, ptr %41, align 4
  call void @DrawTexturePro(ptr %3, [4 x float] %24, [4 x float] %29, [2 x float] %34, float %39, i32 %42)
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock3, label %afterNestedBlock1

decrement_block25:                                ; preds = %"ForLoop::afterLoop"
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = sub i32 %45, 1
  store i32 %46, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block26

end_block26:                                      ; preds = %decrement_block25, %"ForLoop::afterLoop"
  %47 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %checkContinueBlock, label %afterNestedBlock
}

define void @main(ptr %0) !rt !69 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock40, %mergeBlock291, %checkContinueBlock38, %nestedBlock37, %checkContinueBlock36, %end_block289, %checkContinueBlock34, %afterIfElse, %checkContinueBlock32, %nestedBlock31, %checkContinueBlock30, %nestedBlock29, %checkContinueBlock28, %nestedBlock27, %checkContinueBlock26, %nestedBlock25, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %nestedBlock19, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %FillExpr.exit46, %checkContinueBlock4, %FillExpr.exit, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %1 = call ptr @malloc(i64 96)
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  store ptr @16, ptr %2, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  store ptr @17, ptr %5, align 8
  %6 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 4
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %8 = getelementptr inbounds %COLORS_TYPE.3, ptr %7, i32 0, i32 0
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %COLORS_TYPE.3, ptr %7, i32 0, i32 1
  store i32 0, ptr %9, align 4
  %10 = getelementptr inbounds %COLORS_TYPE.3, ptr %7, i32 0, i32 2
  store i32 0, ptr %10, align 4
  %11 = getelementptr inbounds %COLORS_TYPE.3, ptr %7, i32 0, i32 3
  store i32 0, ptr %11, align 4
  %12 = getelementptr inbounds %COLORS_TYPE.3, ptr %7, i32 0, i32 4
  store i32 0, ptr %12, align 4
  %13 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %14 = getelementptr inbounds %KEYS_TYPE.2, ptr %13, i32 0, i32 0
  store i32 0, ptr %14, align 4
  %15 = getelementptr inbounds %KEYS_TYPE.2, ptr %13, i32 0, i32 1
  store i32 0, ptr %15, align 4
  %16 = getelementptr inbounds %KEYS_TYPE.2, ptr %13, i32 0, i32 2
  store i32 0, ptr %16, align 4
  %17 = getelementptr inbounds %KEYS_TYPE.2, ptr %13, i32 0, i32 3
  store i32 0, ptr %17, align 4
  %18 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  %19 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 0
  store i32 0, ptr %19, align 4
  %20 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 1
  store i32 0, ptr %20, align 4
  %21 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 2
  store i32 0, ptr %21, align 4
  %22 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 3
  store i32 0, ptr %22, align 4
  %23 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 4
  store i32 0, ptr %23, align 4
  %24 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 5
  store i32 0, ptr %24, align 4
  %25 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 6
  store i32 0, ptr %25, align 4
  %26 = getelementptr inbounds %LOG_TYPE.1, ptr %18, i32 0, i32 7
  store i32 0, ptr %26, align 4
  %27 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %27, align 8
  %28 = load ptr, ptr %27, align 8
  %29 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 23
  store ptr @FlowWingAnim.setTargetFPS, ptr %29, align 8
  %30 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 22
  store ptr @FlowWingAnim.endDrawing, ptr %30, align 8
  %31 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 21
  store ptr @FlowWingAnim.createWindow, ptr %31, align 8
  %32 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %32, align 8
  %33 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 20
  store ptr @FlowWingAnim.drawTexturePro, ptr %33, align 8
  %34 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 16
  store ptr @FlowWingAnim.drawRectangle, ptr %34, align 8
  %35 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 15
  store ptr @FlowWingAnim.beginDrawing, ptr %35, align 8
  %36 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 1
  store ptr @FlowWingAnim.traceLog, ptr %36, align 8
  %37 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 14
  store ptr @FlowWingAnim.unloadTexture, ptr %37, align 8
  %38 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 13
  store ptr @FlowWingAnim.closeWindow, ptr %38, align 8
  %39 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 17
  store ptr @FlowWingAnim.getColor, ptr %39, align 8
  %40 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 12
  store ptr @FlowWingAnim.textFormat, ptr %40, align 8
  %41 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 18
  store ptr @FlowWingAnim.windowShouldClose, ptr %41, align 8
  %42 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenWidth, ptr %42, align 8
  %43 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenHeight, ptr %43, align 8
  %44 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 11
  store ptr @FlowWingAnim.getTime, ptr %44, align 8
  %45 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 19
  store ptr @FlowWingAnim.beforeInit, ptr %45, align 8
  %46 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 10
  store ptr @FlowWingAnim.clearBackground, ptr %46, align 8
  %47 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 7
  store ptr @FlowWingAnim.drawTexture, ptr %47, align 8
  %48 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 8
  store ptr @FlowWingAnim.getFrameTime, ptr %48, align 8
  %49 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 2
  store ptr @FlowWingAnim.drawText, ptr %49, align 8
  %50 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %50, align 8
  %51 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 9
  store ptr @FlowWingAnim.loadTexture, ptr %51, align 8
  %52 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %28, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %52, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %53 = alloca ptr, align 8
  store ptr @18, ptr %53, align 8
  %FPS = load i32, ptr @FPS, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %53, ptr @FPS, ptr %1)
  %54 = load %FlowWingAnim, ptr %1, align 8
  store %FlowWingAnim %54, ptr %1, align 8
  %55 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %57 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %59 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %60 = load ptr, ptr %59, align 8
  %61 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %60, i32 0, i32 21
  %62 = load ptr, ptr %61, align 8
  call void %62(ptr %1)
  %63 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %64 = icmp eq i32 %63, 0
  br i1 %64, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %65 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %66 = icmp eq i32 %65, 0
  br i1 %66, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %67 = call ptr @malloc(i64 152)
  %68 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  store ptr @19, ptr %68, align 8
  %69 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 1
  store float 0.000000e+00, ptr %69, align 4
  %70 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 2
  store float 0.000000e+00, ptr %70, align 4
  %71 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 3
  store double 0.000000e+00, ptr %71, align 8
  %72 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 4
  store double 0.000000e+00, ptr %72, align 8
  %73 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 5
  store i32 0, ptr %73, align 4
  %74 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 6
  store i32 0, ptr %74, align 4
  %75 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 7
  store ptr @20, ptr %75, align 8
  %76 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 8
  store i1 false, ptr %76, align 1
  %77 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 9
  %78 = getelementptr inbounds %Texture.0, ptr %77, i32 0, i32 0
  store i32 0, ptr %78, align 4
  %79 = getelementptr inbounds %Texture.0, ptr %77, i32 0, i32 1
  store i32 0, ptr %79, align 4
  %80 = getelementptr inbounds %Texture.0, ptr %77, i32 0, i32 2
  store i32 0, ptr %80, align 4
  %81 = getelementptr inbounds %Texture.0, ptr %77, i32 0, i32 3
  store i32 0, ptr %81, align 4
  %82 = getelementptr inbounds %Texture.0, ptr %77, i32 0, i32 4
  store i32 0, ptr %82, align 4
  %83 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 10
  %84 = alloca i32, align 4
  %85 = alloca i32, align 4
  store i32 0, ptr %85, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock4:                              ; preds = %FillExpr.exit
  %86 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %88 = call ptr @malloc(i64 256)
  %89 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 0
  store ptr @22, ptr %89, align 8
  %90 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 1
  %91 = alloca i32, align 4
  %92 = alloca i32, align 4
  store i32 0, ptr %92, align 4
  br label %FillExpr.loopStart-042

checkContinueBlock6:                              ; preds = %FillExpr.exit46
  %93 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %94 = icmp eq i32 %93, 0
  br i1 %94, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %95 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %96 = load ptr, ptr %95, align 8
  %97 = getelementptr inbounds %"Bird::VTableType", ptr %96, i32 0, i32 9
  %98 = load ptr, ptr %97, align 8
  %99 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %100 = load ptr, ptr %99, align 8
  %101 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %100, i32 0, i32 9
  %102 = load ptr, ptr %101, align 8
  %rtPtr = alloca %Texture.0, align 8
  %103 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %104 = load ptr, ptr %103, align 8
  %105 = getelementptr inbounds %"Bird::VTableType", ptr %104, i32 0, i32 7
  %106 = load ptr, ptr %105, align 8
  %rtPtr62 = alloca ptr, align 8
  call void %106(ptr %rtPtr62, ptr %67)
  call void %102(ptr %rtPtr, ptr %rtPtr62, ptr %1)
  call void %98(ptr %rtPtr, ptr %67)
  %107 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %109 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %110 = icmp eq i32 %109, 0
  br i1 %110, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %111 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 0
  %112 = load ptr, ptr %111, align 8
  %113 = getelementptr inbounds %"Cloud::VTableType", ptr %112, i32 0, i32 3
  %114 = load ptr, ptr %113, align 8
  %115 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %116 = load ptr, ptr %115, align 8
  %117 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %116, i32 0, i32 9
  %118 = load ptr, ptr %117, align 8
  %rtPtr63 = alloca %Texture.0, align 8
  %119 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 0
  %120 = load ptr, ptr %119, align 8
  %121 = getelementptr inbounds %"Cloud::VTableType", ptr %120, i32 0, i32 2
  %122 = load ptr, ptr %121, align 8
  %rtPtr64 = alloca ptr, align 8
  call void %122(ptr %rtPtr64, ptr %88)
  call void %118(ptr %rtPtr63, ptr %rtPtr64, ptr %1)
  call void %114(ptr %rtPtr63, ptr %88)
  %123 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %124 = icmp eq i32 %123, 0
  br i1 %124, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %125 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %126 = icmp eq i32 %125, 0
  br i1 %126, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %backgroundTexture = alloca %Texture.0, align 8
  %127 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  store i32 0, ptr %127, align 4
  %128 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 1
  store i32 0, ptr %128, align 4
  %129 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 2
  store i32 0, ptr %129, align 4
  %130 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 3
  store i32 0, ptr %130, align 4
  %131 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 4
  store i32 0, ptr %131, align 4
  %132 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %133 = load ptr, ptr %132, align 8
  %134 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %133, i32 0, i32 9
  %135 = load ptr, ptr %134, align 8
  %rtPtr65 = alloca %Texture.0, align 8
  %136 = alloca ptr, align 8
  store ptr @25, ptr %136, align 8
  call void %135(ptr %rtPtr65, ptr %136, ptr %1)
  %137 = load %Texture.0, ptr %rtPtr65, align 4
  store %Texture.0 %137, ptr %backgroundTexture, align 4
  %138 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %139 = icmp eq i32 %138, 0
  br i1 %139, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %140 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %141 = icmp eq i32 %140, 0
  br i1 %141, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %groundTexture = alloca %Texture.0, align 8
  %142 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 0
  store i32 0, ptr %142, align 4
  %143 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 1
  store i32 0, ptr %143, align 4
  %144 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 2
  store i32 0, ptr %144, align 4
  %145 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 3
  store i32 0, ptr %145, align 4
  %146 = getelementptr inbounds %Texture.0, ptr %groundTexture, i32 0, i32 4
  store i32 0, ptr %146, align 4
  %147 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %148 = load ptr, ptr %147, align 8
  %149 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %148, i32 0, i32 9
  %150 = load ptr, ptr %149, align 8
  %rtPtr66 = alloca %Texture.0, align 8
  %151 = alloca ptr, align 8
  store ptr @26, ptr %151, align 8
  call void %150(ptr %rtPtr66, ptr %151, ptr %1)
  %152 = load %Texture.0, ptr %rtPtr66, align 4
  store %Texture.0 %152, ptr %groundTexture, align 4
  %153 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %155 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %156 = icmp eq i32 %155, 0
  br i1 %156, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %mountL1Texture = alloca %Texture.0, align 8
  %157 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 0
  store i32 0, ptr %157, align 4
  %158 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 1
  store i32 0, ptr %158, align 4
  %159 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 2
  store i32 0, ptr %159, align 4
  %160 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 3
  store i32 0, ptr %160, align 4
  %161 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 4
  store i32 0, ptr %161, align 4
  %162 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %163 = load ptr, ptr %162, align 8
  %164 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %163, i32 0, i32 9
  %165 = load ptr, ptr %164, align 8
  %rtPtr67 = alloca %Texture.0, align 8
  %166 = alloca ptr, align 8
  store ptr @27, ptr %166, align 8
  call void %165(ptr %rtPtr67, ptr %166, ptr %1)
  %167 = load %Texture.0, ptr %rtPtr67, align 4
  store %Texture.0 %167, ptr %mountL1Texture, align 4
  %168 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %169 = icmp eq i32 %168, 0
  br i1 %169, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %170 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %mountL2Texture = alloca %Texture.0, align 8
  %172 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 0
  store i32 0, ptr %172, align 4
  %173 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 1
  store i32 0, ptr %173, align 4
  %174 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 2
  store i32 0, ptr %174, align 4
  %175 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 3
  store i32 0, ptr %175, align 4
  %176 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 4
  store i32 0, ptr %176, align 4
  %177 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %178 = load ptr, ptr %177, align 8
  %179 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %178, i32 0, i32 9
  %180 = load ptr, ptr %179, align 8
  %rtPtr68 = alloca %Texture.0, align 8
  %181 = alloca ptr, align 8
  store ptr @28, ptr %181, align 8
  call void %180(ptr %rtPtr68, ptr %181, ptr %1)
  %182 = load %Texture.0, ptr %rtPtr68, align 4
  store %Texture.0 %182, ptr %mountL2Texture, align 4
  %183 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %184 = icmp eq i32 %183, 0
  br i1 %184, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %185 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %mount2L2Texture = alloca %Texture.0, align 8
  %187 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 0
  store i32 0, ptr %187, align 4
  %188 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 1
  store i32 0, ptr %188, align 4
  %189 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 2
  store i32 0, ptr %189, align 4
  %190 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 3
  store i32 0, ptr %190, align 4
  %191 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 4
  store i32 0, ptr %191, align 4
  %192 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %193 = load ptr, ptr %192, align 8
  %194 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %193, i32 0, i32 9
  %195 = load ptr, ptr %194, align 8
  %rtPtr69 = alloca %Texture.0, align 8
  %196 = alloca ptr, align 8
  store ptr @29, ptr %196, align 8
  call void %195(ptr %rtPtr69, ptr %196, ptr %1)
  %197 = load %Texture.0, ptr %rtPtr69, align 4
  store %Texture.0 %197, ptr %mount2L2Texture, align 4
  %198 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %199 = icmp eq i32 %198, 0
  br i1 %199, label %checkContinueBlock20, label %afterNestedBlock

checkContinueBlock20:                             ; preds = %nestedBlock19
  %200 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %201 = icmp eq i32 %200, 0
  br i1 %201, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %mount1L3Texture = alloca %Texture.0, align 8
  %202 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 0
  store i32 0, ptr %202, align 4
  %203 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 1
  store i32 0, ptr %203, align 4
  %204 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 2
  store i32 0, ptr %204, align 4
  %205 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 3
  store i32 0, ptr %205, align 4
  %206 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 4
  store i32 0, ptr %206, align 4
  %207 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %208 = load ptr, ptr %207, align 8
  %209 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %208, i32 0, i32 9
  %210 = load ptr, ptr %209, align 8
  %rtPtr70 = alloca %Texture.0, align 8
  %211 = alloca ptr, align 8
  store ptr @30, ptr %211, align 8
  call void %210(ptr %rtPtr70, ptr %211, ptr %1)
  %212 = load %Texture.0, ptr %rtPtr70, align 4
  store %Texture.0 %212, ptr %mount1L3Texture, align 4
  %213 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %214 = icmp eq i32 %213, 0
  br i1 %214, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %215 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %216 = icmp eq i32 %215, 0
  br i1 %216, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %mountL1Pos1 = alloca %Position.4, align 8
  %217 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %217, align 4
  %218 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %218, align 4
  %219 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %219, align 4
  %220 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %220, align 4
  %221 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %222 = icmp eq i32 %221, 0
  br i1 %222, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %223 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %224 = icmp eq i32 %223, 0
  br i1 %224, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  %mountL1Pos2 = alloca %Position.4, align 8
  %225 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  store float 0.000000e+00, ptr %225, align 4
  %226 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %226, align 4
  %227 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %228 = alloca i32, align 4
  store i32 -1542, ptr %228, align 4
  %229 = load i32, ptr %228, align 4
  %230 = sitofp i32 %229 to float
  store float %230, ptr %227, align 4
  %231 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %231, align 4
  %232 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %233 = icmp eq i32 %232, 0
  br i1 %233, label %checkContinueBlock26, label %afterNestedBlock

checkContinueBlock26:                             ; preds = %nestedBlock25
  %234 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %235 = icmp eq i32 %234, 0
  br i1 %235, label %nestedBlock27, label %afterNestedBlock

nestedBlock27:                                    ; preds = %checkContinueBlock26
  %mountL2Pos1 = alloca %Position.4, align 8
  %236 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %236, align 4
  %237 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %237, align 4
  %238 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %screenWidth71 = load i32, ptr @screenWidth, align 4
  %239 = load i32, ptr @screenWidth, align 4
  %240 = mul i32 -1, %239
  %241 = alloca i32, align 4
  store i32 %240, ptr %241, align 4
  %242 = load i32, ptr %241, align 4
  %243 = sitofp i32 %242 to float
  store float %243, ptr %238, align 4
  %244 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %244, align 4
  %245 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %246 = icmp eq i32 %245, 0
  br i1 %246, label %checkContinueBlock28, label %afterNestedBlock

checkContinueBlock28:                             ; preds = %nestedBlock27
  %247 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %248 = icmp eq i32 %247, 0
  br i1 %248, label %nestedBlock29, label %afterNestedBlock

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %mount2L2Pos1 = alloca %Position.4, align 8
  %249 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %249, align 4
  %250 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %250, align 4
  %251 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %screenWidth72 = load i32, ptr @screenWidth, align 4
  %252 = load i32, ptr @screenWidth, align 4
  %253 = mul i32 -1, %252
  %254 = alloca i32, align 4
  store i32 %253, ptr %254, align 4
  %255 = load i32, ptr %254, align 4
  %rtPtr73 = alloca i32, align 4
  %screenWidth74 = load i32, ptr @screenWidth, align 4
  %256 = load i32, ptr @screenWidth, align 4
  %257 = sitofp i32 %256 to double
  %258 = fdiv double %257, 4.000000e+00
  %259 = alloca double, align 8
  store double %258, ptr %259, align 8
  %260 = load double, ptr %259, align 8
  %261 = fptosi double %260 to i32
  %262 = alloca i32, align 4
  store i32 %261, ptr %262, align 4
  %screenWidth75 = load i32, ptr @screenWidth, align 4
  %263 = load i32, ptr @screenWidth, align 4
  %264 = sitofp i32 %263 to double
  %265 = fdiv double %264, 2.000000e+00
  %266 = alloca double, align 8
  store double %265, ptr %266, align 8
  %267 = load double, ptr %266, align 8
  %268 = fptosi double %267 to i32
  %269 = alloca i32, align 4
  store i32 %268, ptr %269, align 4
  call void @getRandomNumber(ptr %rtPtr73, ptr %262, ptr %269)
  %270 = load i32, ptr %rtPtr73, align 4
  %271 = sub i32 %255, %270
  %272 = alloca i32, align 4
  store i32 %271, ptr %272, align 4
  %273 = load i32, ptr %272, align 4
  %274 = sitofp i32 %273 to float
  store float %274, ptr %251, align 4
  %275 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %275, align 4
  %276 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %277 = icmp eq i32 %276, 0
  br i1 %277, label %checkContinueBlock30, label %afterNestedBlock

checkContinueBlock30:                             ; preds = %nestedBlock29
  %278 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %279 = icmp eq i32 %278, 0
  br i1 %279, label %nestedBlock31, label %afterNestedBlock

nestedBlock31:                                    ; preds = %checkContinueBlock30
  %mount1L3Pos1 = alloca %Position.4, align 8
  %280 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %280, align 4
  %281 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %281, align 4
  %282 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %screenWidth76 = load i32, ptr @screenWidth, align 4
  %283 = load i32, ptr @screenWidth, align 4
  %284 = mul i32 -1, %283
  %285 = alloca i32, align 4
  store i32 %284, ptr %285, align 4
  %286 = load i32, ptr %285, align 4
  %rtPtr77 = alloca i32, align 4
  %screenWidth78 = load i32, ptr @screenWidth, align 4
  %287 = load i32, ptr @screenWidth, align 4
  %288 = sitofp i32 %287 to double
  %289 = fdiv double %288, 4.000000e+00
  %290 = alloca double, align 8
  store double %289, ptr %290, align 8
  %291 = load double, ptr %290, align 8
  %292 = fptosi double %291 to i32
  %293 = alloca i32, align 4
  store i32 %292, ptr %293, align 4
  %screenWidth79 = load i32, ptr @screenWidth, align 4
  %294 = load i32, ptr @screenWidth, align 4
  %295 = alloca i32, align 4
  store i32 %294, ptr %295, align 4
  call void @getRandomNumber(ptr %rtPtr77, ptr %293, ptr %295)
  %296 = load i32, ptr %rtPtr77, align 4
  %297 = sub i32 %286, %296
  %298 = alloca i32, align 4
  store i32 %297, ptr %298, align 4
  %299 = load i32, ptr %298, align 4
  %300 = sitofp i32 %299 to float
  store float %300, ptr %282, align 4
  %301 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %301, align 4
  %302 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %303 = icmp eq i32 %302, 0
  br i1 %303, label %checkContinueBlock32, label %afterNestedBlock

checkContinueBlock32:                             ; preds = %nestedBlock31
  %304 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %305 = icmp eq i32 %304, 0
  br i1 %305, label %nestedBlock33, label %afterNestedBlock

nestedBlock33:                                    ; preds = %checkContinueBlock32
  %306 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %307 = load ptr, ptr %306, align 8
  %308 = getelementptr inbounds %"Bird::VTableType", ptr %307, i32 0, i32 5
  %309 = load ptr, ptr %308, align 8
  %rtPtr80 = alloca i1, align 1
  call void %309(ptr %rtPtr80, ptr %67)
  %310 = load i1, ptr %rtPtr80, align 1
  %311 = xor i1 %310, true
  %312 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  %id = load i32, ptr %312, align 4
  %313 = load i32, ptr %312, align 4
  %314 = icmp eq i32 %313, 0
  %315 = alloca i1, align 1
  store i1 %314, ptr %315, align 1
  %316 = load i1, ptr %315, align 1
  %317 = select i1 %311, i1 true, i1 %316
  %318 = alloca i1, align 1
  store i1 %317, ptr %318, align 1
  %319 = load i1, ptr %318, align 1
  br i1 %319, label %then, label %else

checkContinueBlock34:                             ; preds = %afterIfElse
  %320 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %321 = icmp eq i32 %320, 0
  br i1 %321, label %nestedBlock35, label %afterNestedBlock

nestedBlock35:                                    ; preds = %checkContinueBlock34
  br label %"while:conditon"

checkContinueBlock36:                             ; preds = %end_block289
  %322 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %323 = icmp eq i32 %322, 0
  br i1 %323, label %nestedBlock37, label %afterNestedBlock

nestedBlock37:                                    ; preds = %checkContinueBlock36
  %324 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %325 = load ptr, ptr %324, align 8
  %326 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %325, i32 0, i32 13
  %327 = load ptr, ptr %326, align 8
  call void %327(ptr %1)
  %328 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %329 = icmp eq i32 %328, 0
  br i1 %329, label %checkContinueBlock38, label %afterNestedBlock

checkContinueBlock38:                             ; preds = %nestedBlock37
  %330 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %331 = icmp eq i32 %330, 0
  br i1 %331, label %nestedBlock39, label %afterNestedBlock

nestedBlock39:                                    ; preds = %checkContinueBlock38
  br label %returnBlock290

checkContinueBlock40:                             ; preds = %mergeBlock291
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock3
  store i32 0, ptr %84, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %332 = load i32, ptr %84, align 4
  %333 = icmp slt i32 %332, 9
  %334 = load i32, ptr %85, align 4
  %335 = icmp slt i32 %334, 9
  %336 = and i1 %333, %335
  br i1 %336, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %337 = load i32, ptr %84, align 4
  %338 = getelementptr [9 x %Position.4], ptr %83, i32 0, i32 %337
  %339 = getelementptr inbounds %Position.4, ptr %338, i32 0, i32 0
  store float 0.000000e+00, ptr %339, align 4
  %340 = getelementptr inbounds %Position.4, ptr %338, i32 0, i32 1
  store float 0.000000e+00, ptr %340, align 4
  %341 = load i32, ptr %84, align 4
  %342 = add i32 %341, 1
  store i32 %342, ptr %84, align 4
  %343 = load i32, ptr %85, align 4
  %344 = add i32 %343, 1
  store i32 %344, ptr %85, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %345 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 11
  %346 = getelementptr inbounds %Position.4, ptr %345, i32 0, i32 0
  store float 0.000000e+00, ptr %346, align 4
  %347 = getelementptr inbounds %Position.4, ptr %345, i32 0, i32 1
  store float 0.000000e+00, ptr %347, align 4
  %348 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %348, align 8
  %349 = load ptr, ptr %348, align 8
  %350 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 8
  store ptr @Bird.updateY, ptr %350, align 8
  %351 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 7
  store ptr @Bird.getTexturePath, ptr %351, align 8
  %352 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 5
  store ptr @Bird.isTextureLoaded, ptr %352, align 8
  %353 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 9
  store ptr @Bird.setTexture, ptr %353, align 8
  %354 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 2
  store ptr @Bird.getOrigin, ptr %354, align 8
  %355 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 4
  store ptr @Bird.getSource, ptr %355, align 8
  %356 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 6
  store ptr @Bird.update, ptr %356, align 8
  %357 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 0
  store ptr @Bird.getTexture, ptr %357, align 8
  %358 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 3
  store ptr @Bird.getDistination, ptr %358, align 8
  %359 = getelementptr inbounds %"Bird::VTableType", ptr %349, i32 0, i32 1
  store ptr @Bird.getRotation, ptr %359, align 8
  %360 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 1
  store float 3.600000e+02, ptr %360, align 4
  %361 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 2
  store float 9.000000e+01, ptr %361, align 4
  %362 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 3
  %FPS41 = load i32, ptr @FPS, align 4
  %363 = load i32, ptr @FPS, align 4
  %364 = sitofp i32 %363 to double
  %365 = fdiv double 1.000000e+01, %364
  %366 = alloca double, align 8
  store double %365, ptr %366, align 8
  %367 = load double, ptr %366, align 8
  store double %367, ptr %362, align 8
  %368 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 5
  store i32 9, ptr %368, align 4
  %369 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 6
  store i32 0, ptr %369, align 4
  %370 = alloca ptr, align 8
  store ptr @21, ptr %370, align 8
  call void @Bird.init1(ptr %370, ptr %67)
  %371 = load %Bird, ptr %67, align 8
  store %Bird %371, ptr %67, align 8
  %372 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %373 = icmp eq i32 %372, 0
  br i1 %373, label %checkContinueBlock4, label %afterNestedBlock

FillExpr.loopStart-042:                           ; preds = %nestedBlock5
  store i32 0, ptr %91, align 4
  br label %FillExpr.loopCmp-043

FillExpr.loopCmp-043:                             ; preds = %FillExpr.exit61, %FillExpr.loopStart-042
  %374 = load i32, ptr %91, align 4
  %375 = icmp slt i32 %374, 5
  %376 = load i32, ptr %92, align 4
  %377 = icmp slt i32 %376, 5
  %378 = and i1 %375, %377
  br i1 %378, label %FillExpr.loopBody-044, label %FillExpr.loopEnd-045

FillExpr.loopBody-044:                            ; preds = %FillExpr.loopCmp-043
  %379 = load i32, ptr %91, align 4
  %380 = getelementptr [5 x %AttributeType.5], ptr %90, i32 0, i32 %379
  %381 = getelementptr inbounds %AttributeType.5, ptr %380, i32 0, i32 0
  %382 = alloca i32, align 4
  %383 = alloca i32, align 4
  store i32 0, ptr %383, align 4
  br label %FillExpr.loopStart-047

FillExpr.loopEnd-045:                             ; preds = %FillExpr.loopCmp-043
  br label %FillExpr.exit46

FillExpr.exit46:                                  ; preds = %FillExpr.loopEnd-045
  %384 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 2
  %385 = getelementptr inbounds %Texture.0, ptr %384, i32 0, i32 0
  store i32 0, ptr %385, align 4
  %386 = getelementptr inbounds %Texture.0, ptr %384, i32 0, i32 1
  store i32 0, ptr %386, align 4
  %387 = getelementptr inbounds %Texture.0, ptr %384, i32 0, i32 2
  store i32 0, ptr %387, align 4
  %388 = getelementptr inbounds %Texture.0, ptr %384, i32 0, i32 3
  store i32 0, ptr %388, align 4
  %389 = getelementptr inbounds %Texture.0, ptr %384, i32 0, i32 4
  store i32 0, ptr %389, align 4
  %390 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 3
  store ptr @23, ptr %390, align 8
  %391 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 0
  store ptr @vtable.Cloud.fg, ptr %391, align 8
  %392 = load ptr, ptr %391, align 8
  %393 = getelementptr inbounds %"Cloud::VTableType", ptr %392, i32 0, i32 4
  store ptr @Cloud.update, ptr %393, align 8
  %394 = getelementptr inbounds %"Cloud::VTableType", ptr %392, i32 0, i32 3
  store ptr @Cloud.setTexture, ptr %394, align 8
  %395 = getelementptr inbounds %"Cloud::VTableType", ptr %392, i32 0, i32 2
  store ptr @Cloud.getTexturePath, ptr %395, align 8
  %396 = getelementptr inbounds %"Cloud::VTableType", ptr %392, i32 0, i32 1
  store ptr @Cloud.getTexture, ptr %396, align 8
  %397 = getelementptr inbounds %"Cloud::VTableType", ptr %392, i32 0, i32 0
  store ptr @Cloud.draw, ptr %397, align 8
  %398 = alloca ptr, align 8
  store ptr @24, ptr %398, align 8
  call void @Cloud.init1(ptr %398, ptr %88)
  %399 = load %Cloud, ptr %88, align 8
  store %Cloud %399, ptr %88, align 8
  %400 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %401 = icmp eq i32 %400, 0
  br i1 %401, label %checkContinueBlock6, label %afterNestedBlock

FillExpr.loopStart-047:                           ; preds = %FillExpr.loopBody-044
  store i32 0, ptr %382, align 4
  br label %FillExpr.loopCmp-048

FillExpr.loopCmp-048:                             ; preds = %FillExpr.loopBody-049, %FillExpr.loopStart-047
  %402 = load i32, ptr %382, align 4
  %403 = icmp slt i32 %402, 4
  %404 = load i32, ptr %383, align 4
  %405 = icmp slt i32 %404, 4
  %406 = and i1 %403, %405
  br i1 %406, label %FillExpr.loopBody-049, label %FillExpr.loopEnd-050

FillExpr.loopBody-049:                            ; preds = %FillExpr.loopCmp-048
  %407 = load i32, ptr %382, align 4
  %408 = getelementptr [4 x float], ptr %381, i32 0, i32 %407
  store float 0.000000e+00, ptr %408, align 4
  %409 = load i32, ptr %382, align 4
  %410 = add i32 %409, 1
  store i32 %410, ptr %382, align 4
  %411 = load i32, ptr %383, align 4
  %412 = add i32 %411, 1
  store i32 %412, ptr %383, align 4
  br label %FillExpr.loopCmp-048

FillExpr.loopEnd-050:                             ; preds = %FillExpr.loopCmp-048
  br label %FillExpr.exit51

FillExpr.exit51:                                  ; preds = %FillExpr.loopEnd-050
  %413 = getelementptr inbounds %AttributeType.5, ptr %380, i32 0, i32 1
  %414 = alloca i32, align 4
  %415 = alloca i32, align 4
  store i32 0, ptr %415, align 4
  br label %FillExpr.loopStart-052

FillExpr.loopStart-052:                           ; preds = %FillExpr.exit51
  store i32 0, ptr %414, align 4
  br label %FillExpr.loopCmp-053

FillExpr.loopCmp-053:                             ; preds = %FillExpr.loopBody-054, %FillExpr.loopStart-052
  %416 = load i32, ptr %414, align 4
  %417 = icmp slt i32 %416, 4
  %418 = load i32, ptr %415, align 4
  %419 = icmp slt i32 %418, 4
  %420 = and i1 %417, %419
  br i1 %420, label %FillExpr.loopBody-054, label %FillExpr.loopEnd-055

FillExpr.loopBody-054:                            ; preds = %FillExpr.loopCmp-053
  %421 = load i32, ptr %414, align 4
  %422 = getelementptr [4 x float], ptr %413, i32 0, i32 %421
  store float 0.000000e+00, ptr %422, align 4
  %423 = load i32, ptr %414, align 4
  %424 = add i32 %423, 1
  store i32 %424, ptr %414, align 4
  %425 = load i32, ptr %415, align 4
  %426 = add i32 %425, 1
  store i32 %426, ptr %415, align 4
  br label %FillExpr.loopCmp-053

FillExpr.loopEnd-055:                             ; preds = %FillExpr.loopCmp-053
  br label %FillExpr.exit56

FillExpr.exit56:                                  ; preds = %FillExpr.loopEnd-055
  %427 = getelementptr inbounds %AttributeType.5, ptr %380, i32 0, i32 2
  %428 = alloca i32, align 4
  %429 = alloca i32, align 4
  store i32 0, ptr %429, align 4
  br label %FillExpr.loopStart-057

FillExpr.loopStart-057:                           ; preds = %FillExpr.exit56
  store i32 0, ptr %428, align 4
  br label %FillExpr.loopCmp-058

FillExpr.loopCmp-058:                             ; preds = %FillExpr.loopBody-059, %FillExpr.loopStart-057
  %430 = load i32, ptr %428, align 4
  %431 = icmp slt i32 %430, 2
  %432 = load i32, ptr %429, align 4
  %433 = icmp slt i32 %432, 2
  %434 = and i1 %431, %433
  br i1 %434, label %FillExpr.loopBody-059, label %FillExpr.loopEnd-060

FillExpr.loopBody-059:                            ; preds = %FillExpr.loopCmp-058
  %435 = load i32, ptr %428, align 4
  %436 = getelementptr [2 x float], ptr %427, i32 0, i32 %435
  store float 0.000000e+00, ptr %436, align 4
  %437 = load i32, ptr %428, align 4
  %438 = add i32 %437, 1
  store i32 %438, ptr %428, align 4
  %439 = load i32, ptr %429, align 4
  %440 = add i32 %439, 1
  store i32 %440, ptr %429, align 4
  br label %FillExpr.loopCmp-058

FillExpr.loopEnd-060:                             ; preds = %FillExpr.loopCmp-058
  br label %FillExpr.exit61

FillExpr.exit61:                                  ; preds = %FillExpr.loopEnd-060
  %441 = getelementptr inbounds %AttributeType.5, ptr %380, i32 0, i32 3
  store float 0.000000e+00, ptr %441, align 4
  %442 = load i32, ptr %91, align 4
  %443 = add i32 %442, 1
  store i32 %443, ptr %91, align 4
  %444 = load i32, ptr %92, align 4
  %445 = add i32 %444, 1
  store i32 %445, ptr %92, align 4
  br label %FillExpr.loopCmp-043

then:                                             ; preds = %nestedBlock33
  br label %nestedBlock82

else:                                             ; preds = %nestedBlock33
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock81
  %446 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %447 = icmp eq i32 %446, 0
  br i1 %447, label %checkContinueBlock34, label %afterNestedBlock

afterNestedBlock81:                               ; preds = %checkContinueBlock89, %mergeBlock, %checkContinueBlock87, %nestedBlock86, %checkContinueBlock85, %nestedBlock84, %checkContinueBlock83, %nestedBlock82
  br label %afterIfElse

nestedBlock82:                                    ; preds = %then
  %448 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %449 = load ptr, ptr %448, align 8
  %450 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %449, i32 0, i32 1
  %451 = load ptr, ptr %450, align 8
  %452 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  %453 = getelementptr inbounds %LOG_TYPE.1, ptr %452, i32 0, i32 5
  %ERROR = load i32, ptr %453, align 4
  %454 = alloca ptr, align 8
  store ptr @31, ptr %454, align 8
  call void %451(ptr %453, ptr %454, ptr %1)
  %455 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %456 = icmp eq i32 %455, 0
  br i1 %456, label %checkContinueBlock83, label %afterNestedBlock81

checkContinueBlock83:                             ; preds = %nestedBlock82
  %457 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %458 = icmp eq i32 %457, 0
  br i1 %458, label %nestedBlock84, label %afterNestedBlock81

nestedBlock84:                                    ; preds = %checkContinueBlock83
  %459 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %460 = load ptr, ptr %459, align 8
  %461 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %460, i32 0, i32 14
  %462 = load ptr, ptr %461, align 8
  %463 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %464 = load ptr, ptr %463, align 8
  %465 = getelementptr inbounds %"Bird::VTableType", ptr %464, i32 0, i32 0
  %466 = load ptr, ptr %465, align 8
  %rtPtr90 = alloca %Texture.0, align 8
  call void %466(ptr %rtPtr90, ptr %67)
  call void %462(ptr %rtPtr90, ptr %1)
  %467 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %468 = icmp eq i32 %467, 0
  br i1 %468, label %checkContinueBlock85, label %afterNestedBlock81

checkContinueBlock85:                             ; preds = %nestedBlock84
  %469 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %470 = icmp eq i32 %469, 0
  br i1 %470, label %nestedBlock86, label %afterNestedBlock81

nestedBlock86:                                    ; preds = %checkContinueBlock85
  %471 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %472 = load ptr, ptr %471, align 8
  %473 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %472, i32 0, i32 13
  %474 = load ptr, ptr %473, align 8
  call void %474(ptr %1)
  %475 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %476 = icmp eq i32 %475, 0
  br i1 %476, label %checkContinueBlock87, label %afterNestedBlock81

checkContinueBlock87:                             ; preds = %nestedBlock86
  %477 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %478 = icmp eq i32 %477, 0
  br i1 %478, label %nestedBlock88, label %afterNestedBlock81

nestedBlock88:                                    ; preds = %checkContinueBlock87
  br label %returnBlock

checkContinueBlock89:                             ; preds = %mergeBlock
  br label %afterNestedBlock81

returnBlock:                                      ; preds = %nestedBlock88
  store i32 1, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %479 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %480 = icmp eq i32 %479, 0
  br i1 %480, label %checkContinueBlock89, label %afterNestedBlock81

"while:conditon":                                 ; preds = %afterNestedBlock92, %nestedBlock35
  %481 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %482 = icmp eq i32 %481, 0
  br i1 %482, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock93

while.end:                                        ; preds = %afterNestedBlock92, %end_block
  %483 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %484 = icmp eq i32 %483, 0
  br i1 %484, label %end_block289, label %decrement_block288

decrement_block:                                  ; preds = %"while:conditon"
  %485 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %486 = sub i32 %485, 1
  store i32 %486, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %487 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %488 = load ptr, ptr %487, align 8
  %489 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %488, i32 0, i32 18
  %490 = load ptr, ptr %489, align 8
  %rtPtr91 = alloca i1, align 1
  call void %490(ptr %rtPtr91, ptr %1)
  %491 = load i1, ptr %rtPtr91, align 1
  %492 = xor i1 %491, true
  br i1 %492, label %"while:body", label %while.end

afterNestedBlock92:                               ; preds = %checkContinueBlock132, %nestedBlock131, %checkContinueBlock130, %nestedBlock129, %checkContinueBlock128, %nestedBlock127, %checkContinueBlock126, %nestedBlock125, %checkContinueBlock124, %nestedBlock123, %checkContinueBlock122, %nestedBlock121, %checkContinueBlock120, %nestedBlock119, %checkContinueBlock118, %nestedBlock117, %checkContinueBlock116, %nestedBlock115, %checkContinueBlock114, %nestedBlock113, %checkContinueBlock112, %nestedBlock111, %checkContinueBlock110, %nestedBlock109, %checkContinueBlock108, %nestedBlock107, %checkContinueBlock106, %nestedBlock105, %checkContinueBlock104, %afterIfElse229, %checkContinueBlock102, %afterNestedBlock202, %checkContinueBlock100, %afterNestedBlock183, %checkContinueBlock98, %afterNestedBlock164, %checkContinueBlock96, %afterNestedBlock134, %checkContinueBlock94, %nestedBlock93
  %493 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %494 = icmp eq i32 %493, 0
  br i1 %494, label %"while:conditon", label %while.end

nestedBlock93:                                    ; preds = %"while:body"
  %495 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %496 = load ptr, ptr %495, align 8
  %497 = getelementptr inbounds %"Bird::VTableType", ptr %496, i32 0, i32 6
  %498 = load ptr, ptr %497, align 8
  %499 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %500 = load ptr, ptr %499, align 8
  %501 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %500, i32 0, i32 8
  %502 = load ptr, ptr %501, align 8
  %rtPtr133 = alloca float, align 4
  call void %502(ptr %rtPtr133, ptr %1)
  call void %498(ptr %rtPtr133, ptr %67)
  %503 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %504 = icmp eq i32 %503, 0
  br i1 %504, label %checkContinueBlock94, label %afterNestedBlock92

checkContinueBlock94:                             ; preds = %nestedBlock93
  %505 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %506 = icmp eq i32 %505, 0
  br i1 %506, label %nestedBlock95, label %afterNestedBlock92

nestedBlock95:                                    ; preds = %checkContinueBlock94
  br label %nestedBlock135

checkContinueBlock96:                             ; preds = %afterNestedBlock134
  %507 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %508 = icmp eq i32 %507, 0
  br i1 %508, label %nestedBlock97, label %afterNestedBlock92

nestedBlock97:                                    ; preds = %checkContinueBlock96
  br label %nestedBlock165

checkContinueBlock98:                             ; preds = %afterNestedBlock164
  %509 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %510 = icmp eq i32 %509, 0
  br i1 %510, label %nestedBlock99, label %afterNestedBlock92

nestedBlock99:                                    ; preds = %checkContinueBlock98
  br label %nestedBlock184

checkContinueBlock100:                            ; preds = %afterNestedBlock183
  %511 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %512 = icmp eq i32 %511, 0
  br i1 %512, label %nestedBlock101, label %afterNestedBlock92

nestedBlock101:                                   ; preds = %checkContinueBlock100
  br label %nestedBlock203

checkContinueBlock102:                            ; preds = %afterNestedBlock202
  %513 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %514 = icmp eq i32 %513, 0
  br i1 %514, label %nestedBlock103, label %afterNestedBlock92

nestedBlock103:                                   ; preds = %checkContinueBlock102
  %515 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %516 = load ptr, ptr %515, align 8
  %517 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %516, i32 0, i32 0
  %518 = load ptr, ptr %517, align 8
  %rtPtr224 = alloca i1, align 1
  %519 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %520 = getelementptr inbounds %KEYS_TYPE.2, ptr %519, i32 0, i32 3
  %KEY_UP = load i32, ptr %520, align 4
  call void %518(ptr %rtPtr224, ptr %520, ptr %1)
  %521 = load i1, ptr %rtPtr224, align 1
  %522 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %523 = load ptr, ptr %522, align 8
  %524 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %523, i32 0, i32 4
  %525 = load ptr, ptr %524, align 8
  %rtPtr225 = alloca i1, align 1
  %526 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %527 = getelementptr inbounds %KEYS_TYPE.2, ptr %526, i32 0, i32 3
  %KEY_UP226 = load i32, ptr %527, align 4
  call void %525(ptr %rtPtr225, ptr %527, ptr %1)
  %528 = load i1, ptr %rtPtr225, align 1
  %529 = select i1 %521, i1 true, i1 %528
  %530 = alloca i1, align 1
  store i1 %529, ptr %530, align 1
  %531 = load i1, ptr %530, align 1
  br i1 %531, label %then227, label %else228

checkContinueBlock104:                            ; preds = %afterIfElse229
  %532 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %533 = icmp eq i32 %532, 0
  br i1 %533, label %nestedBlock105, label %afterNestedBlock92

nestedBlock105:                                   ; preds = %checkContinueBlock104
  %534 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 0
  %535 = load ptr, ptr %534, align 8
  %536 = getelementptr inbounds %"Cloud::VTableType", ptr %535, i32 0, i32 4
  %537 = load ptr, ptr %536, align 8
  %538 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %539 = load ptr, ptr %538, align 8
  %540 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %539, i32 0, i32 8
  %541 = load ptr, ptr %540, align 8
  %rtPtr234 = alloca float, align 4
  call void %541(ptr %rtPtr234, ptr %1)
  call void %537(ptr %rtPtr234, ptr %88)
  %542 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %543 = icmp eq i32 %542, 0
  br i1 %543, label %checkContinueBlock106, label %afterNestedBlock92

checkContinueBlock106:                            ; preds = %nestedBlock105
  %544 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %545 = icmp eq i32 %544, 0
  br i1 %545, label %nestedBlock107, label %afterNestedBlock92

nestedBlock107:                                   ; preds = %checkContinueBlock106
  %546 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %547 = load ptr, ptr %546, align 8
  %548 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %547, i32 0, i32 15
  %549 = load ptr, ptr %548, align 8
  call void %549(ptr %1)
  %550 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %551 = icmp eq i32 %550, 0
  br i1 %551, label %checkContinueBlock108, label %afterNestedBlock92

checkContinueBlock108:                            ; preds = %nestedBlock107
  %552 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %553 = icmp eq i32 %552, 0
  br i1 %553, label %nestedBlock109, label %afterNestedBlock92

nestedBlock109:                                   ; preds = %checkContinueBlock108
  %554 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %555 = load ptr, ptr %554, align 8
  %556 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %555, i32 0, i32 10
  %557 = load ptr, ptr %556, align 8
  %558 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %559 = getelementptr inbounds %COLORS_TYPE.3, ptr %558, i32 0, i32 1
  %RED = load i32, ptr %559, align 4
  call void %557(ptr %559, ptr %1)
  %560 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %561 = icmp eq i32 %560, 0
  br i1 %561, label %checkContinueBlock110, label %afterNestedBlock92

checkContinueBlock110:                            ; preds = %nestedBlock109
  %562 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %563 = icmp eq i32 %562, 0
  br i1 %563, label %nestedBlock111, label %afterNestedBlock92

nestedBlock111:                                   ; preds = %checkContinueBlock110
  %564 = alloca [4 x float], align 4, !I !70, !ET !71
  %565 = getelementptr [4 x float], ptr %564, i32 0, i32 0
  store float 0.000000e+00, ptr %565, align 4
  %566 = getelementptr [4 x float], ptr %564, i32 0, i32 1
  store float 0.000000e+00, ptr %566, align 4
  %567 = getelementptr [4 x float], ptr %564, i32 0, i32 2
  store float 0.000000e+00, ptr %567, align 4
  %568 = getelementptr [4 x float], ptr %564, i32 0, i32 3
  store float 0.000000e+00, ptr %568, align 4
  %569 = getelementptr [4 x float], ptr %564, i32 0, i32 0
  store float 0.000000e+00, ptr %569, align 4
  %570 = getelementptr [4 x float], ptr %564, i32 0, i32 1
  store float 0.000000e+00, ptr %570, align 4
  %571 = getelementptr [4 x float], ptr %564, i32 0, i32 2
  store float 3.840000e+03, ptr %571, align 4
  %572 = getelementptr [4 x float], ptr %564, i32 0, i32 3
  store float 2.160000e+03, ptr %572, align 4
  %573 = load [4 x float], ptr %564, align 4
  %574 = alloca [4 x float], align 4, !I !70, !ET !71
  %575 = getelementptr [4 x float], ptr %574, i32 0, i32 0
  store float 0.000000e+00, ptr %575, align 4
  %576 = getelementptr [4 x float], ptr %574, i32 0, i32 1
  store float 0.000000e+00, ptr %576, align 4
  %577 = getelementptr [4 x float], ptr %574, i32 0, i32 2
  store float 0.000000e+00, ptr %577, align 4
  %578 = getelementptr [4 x float], ptr %574, i32 0, i32 3
  store float 0.000000e+00, ptr %578, align 4
  %579 = getelementptr [4 x float], ptr %574, i32 0, i32 0
  store float 0.000000e+00, ptr %579, align 4
  %580 = getelementptr [4 x float], ptr %574, i32 0, i32 1
  store float 0.000000e+00, ptr %580, align 4
  %581 = getelementptr [4 x float], ptr %574, i32 0, i32 2
  %screenWidth235 = load i32, ptr @screenWidth, align 4
  %582 = load i32, ptr @screenWidth, align 4
  %583 = sitofp i32 %582 to float
  store float %583, ptr %581, align 4
  %584 = getelementptr [4 x float], ptr %574, i32 0, i32 3
  %screenHeight236 = load i32, ptr @screenHeight, align 4
  %585 = load i32, ptr @screenHeight, align 4
  %586 = sitofp i32 %585 to float
  store float %586, ptr %584, align 4
  %587 = load [4 x float], ptr %574, align 4
  %588 = alloca [2 x float], align 4, !I !72, !ET !71
  %589 = getelementptr [2 x float], ptr %588, i32 0, i32 0
  store float 0.000000e+00, ptr %589, align 4
  %590 = getelementptr [2 x float], ptr %588, i32 0, i32 1
  store float 0.000000e+00, ptr %590, align 4
  %591 = getelementptr [2 x float], ptr %588, i32 0, i32 0
  store float 0.000000e+00, ptr %591, align 4
  %592 = getelementptr [2 x float], ptr %588, i32 0, i32 1
  store float 0.000000e+00, ptr %592, align 4
  %593 = load [2 x float], ptr %588, align 4
  %594 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %595 = getelementptr inbounds %COLORS_TYPE.3, ptr %594, i32 0, i32 0
  %WHITE = load i32, ptr %595, align 4
  %596 = load i32, ptr %595, align 4
  call void @DrawTexturePro(ptr %backgroundTexture, [4 x float] %573, [4 x float] %587, [2 x float] %593, float 0.000000e+00, i32 %596)
  %597 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %598 = icmp eq i32 %597, 0
  br i1 %598, label %checkContinueBlock112, label %afterNestedBlock92

checkContinueBlock112:                            ; preds = %nestedBlock111
  %599 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %600 = icmp eq i32 %599, 0
  br i1 %600, label %nestedBlock113, label %afterNestedBlock92

nestedBlock113:                                   ; preds = %checkContinueBlock112
  %601 = getelementptr inbounds %Cloud, ptr %88, i32 0, i32 0
  %602 = load ptr, ptr %601, align 8
  %603 = getelementptr inbounds %"Cloud::VTableType", ptr %602, i32 0, i32 0
  %604 = load ptr, ptr %603, align 8
  call void %604(ptr %1, ptr %88)
  %605 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %606 = icmp eq i32 %605, 0
  br i1 %606, label %checkContinueBlock114, label %afterNestedBlock92

checkContinueBlock114:                            ; preds = %nestedBlock113
  %607 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %608 = icmp eq i32 %607, 0
  br i1 %608, label %nestedBlock115, label %afterNestedBlock92

nestedBlock115:                                   ; preds = %checkContinueBlock114
  %609 = alloca [4 x float], align 4, !I !70, !ET !71
  %610 = getelementptr [4 x float], ptr %609, i32 0, i32 0
  store float 0.000000e+00, ptr %610, align 4
  %611 = getelementptr [4 x float], ptr %609, i32 0, i32 1
  store float 0.000000e+00, ptr %611, align 4
  %612 = getelementptr [4 x float], ptr %609, i32 0, i32 2
  store float 0.000000e+00, ptr %612, align 4
  %613 = getelementptr [4 x float], ptr %609, i32 0, i32 3
  store float 0.000000e+00, ptr %613, align 4
  %614 = getelementptr [4 x float], ptr %609, i32 0, i32 0
  store float 0.000000e+00, ptr %614, align 4
  %615 = getelementptr [4 x float], ptr %609, i32 0, i32 1
  store float 0.000000e+00, ptr %615, align 4
  %616 = getelementptr [4 x float], ptr %609, i32 0, i32 2
  store float 5.975000e+03, ptr %616, align 4
  %617 = getelementptr [4 x float], ptr %609, i32 0, i32 3
  store float 1.607000e+03, ptr %617, align 4
  %618 = load [4 x float], ptr %609, align 4
  %619 = alloca [4 x float], align 4, !I !70, !ET !71
  %620 = getelementptr [4 x float], ptr %619, i32 0, i32 0
  store float 0.000000e+00, ptr %620, align 4
  %621 = getelementptr [4 x float], ptr %619, i32 0, i32 1
  store float 0.000000e+00, ptr %621, align 4
  %622 = getelementptr [4 x float], ptr %619, i32 0, i32 2
  store float 0.000000e+00, ptr %622, align 4
  %623 = getelementptr [4 x float], ptr %619, i32 0, i32 3
  store float 0.000000e+00, ptr %623, align 4
  %624 = getelementptr [4 x float], ptr %619, i32 0, i32 0
  store float 0.000000e+00, ptr %624, align 4
  %625 = getelementptr [4 x float], ptr %619, i32 0, i32 1
  %screenHeight237 = load i32, ptr @screenHeight, align 4
  %626 = load i32, ptr @screenHeight, align 4
  %627 = sitofp i32 %626 to double
  %628 = fdiv double %627, 3.000000e+00
  %629 = alloca double, align 8
  store double %628, ptr %629, align 8
  %630 = load double, ptr %629, align 8
  %631 = fptrunc double %630 to float
  store float %631, ptr %625, align 4
  %632 = getelementptr [4 x float], ptr %619, i32 0, i32 2
  %screenWidth238 = load i32, ptr @screenWidth, align 4
  %633 = load i32, ptr @screenWidth, align 4
  %634 = sitofp i32 %633 to double
  %635 = fdiv double %634, 2.000000e+00
  %636 = alloca double, align 8
  store double %635, ptr %636, align 8
  %637 = load double, ptr %636, align 8
  %638 = fptrunc double %637 to float
  store float %638, ptr %632, align 4
  %639 = getelementptr [4 x float], ptr %619, i32 0, i32 3
  %screenHeight239 = load i32, ptr @screenHeight, align 4
  %640 = load i32, ptr @screenHeight, align 4
  %641 = sitofp i32 %640 to double
  %642 = fdiv double %641, 3.000000e+00
  %643 = alloca double, align 8
  store double %642, ptr %643, align 8
  %644 = load double, ptr %643, align 8
  %645 = fptrunc double %644 to float
  store float %645, ptr %639, align 4
  %646 = load [4 x float], ptr %619, align 4
  %647 = alloca [2 x float], align 4, !I !72, !ET !71
  %648 = getelementptr [2 x float], ptr %647, i32 0, i32 0
  store float 0.000000e+00, ptr %648, align 4
  %649 = getelementptr [2 x float], ptr %647, i32 0, i32 1
  store float 0.000000e+00, ptr %649, align 4
  %650 = getelementptr [2 x float], ptr %647, i32 0, i32 0
  %651 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x240 = load float, ptr %651, align 4
  %652 = load float, ptr %651, align 4
  store float %652, ptr %650, align 4
  %653 = getelementptr [2 x float], ptr %647, i32 0, i32 1
  %654 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  %y = load float, ptr %654, align 4
  %655 = load float, ptr %654, align 4
  store float %655, ptr %653, align 4
  %656 = load [2 x float], ptr %647, align 4
  %657 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %658 = getelementptr inbounds %COLORS_TYPE.3, ptr %657, i32 0, i32 0
  %WHITE241 = load i32, ptr %658, align 4
  %659 = load i32, ptr %658, align 4
  call void @DrawTexturePro(ptr %mountL2Texture, [4 x float] %618, [4 x float] %646, [2 x float] %656, float 0.000000e+00, i32 %659)
  %660 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %661 = icmp eq i32 %660, 0
  br i1 %661, label %checkContinueBlock116, label %afterNestedBlock92

checkContinueBlock116:                            ; preds = %nestedBlock115
  %662 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %663 = icmp eq i32 %662, 0
  br i1 %663, label %nestedBlock117, label %afterNestedBlock92

nestedBlock117:                                   ; preds = %checkContinueBlock116
  %664 = alloca [4 x float], align 4, !I !70, !ET !71
  %665 = getelementptr [4 x float], ptr %664, i32 0, i32 0
  store float 0.000000e+00, ptr %665, align 4
  %666 = getelementptr [4 x float], ptr %664, i32 0, i32 1
  store float 0.000000e+00, ptr %666, align 4
  %667 = getelementptr [4 x float], ptr %664, i32 0, i32 2
  store float 0.000000e+00, ptr %667, align 4
  %668 = getelementptr [4 x float], ptr %664, i32 0, i32 3
  store float 0.000000e+00, ptr %668, align 4
  %669 = getelementptr [4 x float], ptr %664, i32 0, i32 0
  store float 0.000000e+00, ptr %669, align 4
  %670 = getelementptr [4 x float], ptr %664, i32 0, i32 1
  store float 0.000000e+00, ptr %670, align 4
  %671 = getelementptr [4 x float], ptr %664, i32 0, i32 2
  store float 4.461000e+03, ptr %671, align 4
  %672 = getelementptr [4 x float], ptr %664, i32 0, i32 3
  store float 1.989000e+03, ptr %672, align 4
  %673 = load [4 x float], ptr %664, align 4
  %674 = alloca [4 x float], align 4, !I !70, !ET !71
  %675 = getelementptr [4 x float], ptr %674, i32 0, i32 0
  store float 0.000000e+00, ptr %675, align 4
  %676 = getelementptr [4 x float], ptr %674, i32 0, i32 1
  store float 0.000000e+00, ptr %676, align 4
  %677 = getelementptr [4 x float], ptr %674, i32 0, i32 2
  store float 0.000000e+00, ptr %677, align 4
  %678 = getelementptr [4 x float], ptr %674, i32 0, i32 3
  store float 0.000000e+00, ptr %678, align 4
  %679 = getelementptr [4 x float], ptr %674, i32 0, i32 0
  store float 0.000000e+00, ptr %679, align 4
  %680 = getelementptr [4 x float], ptr %674, i32 0, i32 1
  %screenHeight242 = load i32, ptr @screenHeight, align 4
  %681 = load i32, ptr @screenHeight, align 4
  %682 = sitofp i32 %681 to double
  %683 = fdiv double %682, 3.000000e+00
  %684 = alloca double, align 8
  store double %683, ptr %684, align 8
  %685 = load double, ptr %684, align 8
  %686 = fptrunc double %685 to float
  store float %686, ptr %680, align 4
  %687 = getelementptr [4 x float], ptr %674, i32 0, i32 2
  %screenWidth243 = load i32, ptr @screenWidth, align 4
  %688 = load i32, ptr @screenWidth, align 4
  %689 = sitofp i32 %688 to double
  %690 = fdiv double %689, 2.000000e+00
  %691 = alloca double, align 8
  store double %690, ptr %691, align 8
  %692 = load double, ptr %691, align 8
  %693 = fptrunc double %692 to float
  store float %693, ptr %687, align 4
  %694 = getelementptr [4 x float], ptr %674, i32 0, i32 3
  %screenHeight244 = load i32, ptr @screenHeight, align 4
  %695 = load i32, ptr @screenHeight, align 4
  %696 = sitofp i32 %695 to double
  %697 = fdiv double %696, 3.000000e+00
  %698 = alloca double, align 8
  store double %697, ptr %698, align 8
  %699 = load double, ptr %698, align 8
  %700 = fptrunc double %699 to float
  store float %700, ptr %694, align 4
  %701 = load [4 x float], ptr %674, align 4
  %702 = alloca [2 x float], align 4, !I !72, !ET !71
  %703 = getelementptr [2 x float], ptr %702, i32 0, i32 0
  store float 0.000000e+00, ptr %703, align 4
  %704 = getelementptr [2 x float], ptr %702, i32 0, i32 1
  store float 0.000000e+00, ptr %704, align 4
  %705 = getelementptr [2 x float], ptr %702, i32 0, i32 0
  %706 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x245 = load float, ptr %706, align 4
  %707 = load float, ptr %706, align 4
  store float %707, ptr %705, align 4
  %708 = getelementptr [2 x float], ptr %702, i32 0, i32 1
  %709 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  %y246 = load float, ptr %709, align 4
  %710 = load float, ptr %709, align 4
  store float %710, ptr %708, align 4
  %711 = load [2 x float], ptr %702, align 4
  %712 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %713 = getelementptr inbounds %COLORS_TYPE.3, ptr %712, i32 0, i32 0
  %WHITE247 = load i32, ptr %713, align 4
  %714 = load i32, ptr %713, align 4
  call void @DrawTexturePro(ptr %mount2L2Texture, [4 x float] %673, [4 x float] %701, [2 x float] %711, float 0.000000e+00, i32 %714)
  %715 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %716 = icmp eq i32 %715, 0
  br i1 %716, label %checkContinueBlock118, label %afterNestedBlock92

checkContinueBlock118:                            ; preds = %nestedBlock117
  %717 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %718 = icmp eq i32 %717, 0
  br i1 %718, label %nestedBlock119, label %afterNestedBlock92

nestedBlock119:                                   ; preds = %checkContinueBlock118
  %719 = alloca [4 x float], align 4, !I !70, !ET !71
  %720 = getelementptr [4 x float], ptr %719, i32 0, i32 0
  store float 0.000000e+00, ptr %720, align 4
  %721 = getelementptr [4 x float], ptr %719, i32 0, i32 1
  store float 0.000000e+00, ptr %721, align 4
  %722 = getelementptr [4 x float], ptr %719, i32 0, i32 2
  store float 0.000000e+00, ptr %722, align 4
  %723 = getelementptr [4 x float], ptr %719, i32 0, i32 3
  store float 0.000000e+00, ptr %723, align 4
  %724 = getelementptr [4 x float], ptr %719, i32 0, i32 0
  store float 0.000000e+00, ptr %724, align 4
  %725 = getelementptr [4 x float], ptr %719, i32 0, i32 1
  store float 0.000000e+00, ptr %725, align 4
  %726 = getelementptr [4 x float], ptr %719, i32 0, i32 2
  store float 6.005000e+03, ptr %726, align 4
  %727 = getelementptr [4 x float], ptr %719, i32 0, i32 3
  store float 2.376000e+03, ptr %727, align 4
  %728 = load [4 x float], ptr %719, align 4
  %729 = alloca [4 x float], align 4, !I !70, !ET !71
  %730 = getelementptr [4 x float], ptr %729, i32 0, i32 0
  store float 0.000000e+00, ptr %730, align 4
  %731 = getelementptr [4 x float], ptr %729, i32 0, i32 1
  store float 0.000000e+00, ptr %731, align 4
  %732 = getelementptr [4 x float], ptr %729, i32 0, i32 2
  store float 0.000000e+00, ptr %732, align 4
  %733 = getelementptr [4 x float], ptr %729, i32 0, i32 3
  store float 0.000000e+00, ptr %733, align 4
  %734 = getelementptr [4 x float], ptr %729, i32 0, i32 0
  store float 0.000000e+00, ptr %734, align 4
  %735 = getelementptr [4 x float], ptr %729, i32 0, i32 1
  %screenHeight248 = load i32, ptr @screenHeight, align 4
  %736 = load i32, ptr @screenHeight, align 4
  %737 = sitofp i32 %736 to double
  %738 = fdiv double %737, 3.000000e+00
  %739 = alloca double, align 8
  store double %738, ptr %739, align 8
  %740 = load double, ptr %739, align 8
  %741 = fptrunc double %740 to float
  store float %741, ptr %735, align 4
  %742 = getelementptr [4 x float], ptr %729, i32 0, i32 2
  %screenWidth249 = load i32, ptr @screenWidth, align 4
  %743 = load i32, ptr @screenWidth, align 4
  %744 = sitofp i32 %743 to double
  %745 = fdiv double %744, 2.000000e+00
  %746 = alloca double, align 8
  store double %745, ptr %746, align 8
  %747 = load double, ptr %746, align 8
  %748 = fptrunc double %747 to float
  store float %748, ptr %742, align 4
  %749 = getelementptr [4 x float], ptr %729, i32 0, i32 3
  %screenHeight250 = load i32, ptr @screenHeight, align 4
  %750 = load i32, ptr @screenHeight, align 4
  %751 = sitofp i32 %750 to double
  %752 = fdiv double %751, 3.000000e+00
  %753 = alloca double, align 8
  store double %752, ptr %753, align 8
  %754 = load double, ptr %753, align 8
  %755 = fptrunc double %754 to float
  store float %755, ptr %749, align 4
  %756 = load [4 x float], ptr %729, align 4
  %757 = alloca [2 x float], align 4, !I !72, !ET !71
  %758 = getelementptr [2 x float], ptr %757, i32 0, i32 0
  store float 0.000000e+00, ptr %758, align 4
  %759 = getelementptr [2 x float], ptr %757, i32 0, i32 1
  store float 0.000000e+00, ptr %759, align 4
  %760 = getelementptr [2 x float], ptr %757, i32 0, i32 0
  %761 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x251 = load float, ptr %761, align 4
  %762 = load float, ptr %761, align 4
  store float %762, ptr %760, align 4
  %763 = getelementptr [2 x float], ptr %757, i32 0, i32 1
  %764 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  %y252 = load float, ptr %764, align 4
  %765 = load float, ptr %764, align 4
  store float %765, ptr %763, align 4
  %766 = load [2 x float], ptr %757, align 4
  %767 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %768 = getelementptr inbounds %COLORS_TYPE.3, ptr %767, i32 0, i32 0
  %WHITE253 = load i32, ptr %768, align 4
  %769 = load i32, ptr %768, align 4
  call void @DrawTexturePro(ptr %mount1L3Texture, [4 x float] %728, [4 x float] %756, [2 x float] %766, float 0.000000e+00, i32 %769)
  %770 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %771 = icmp eq i32 %770, 0
  br i1 %771, label %checkContinueBlock120, label %afterNestedBlock92

checkContinueBlock120:                            ; preds = %nestedBlock119
  %772 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %773 = icmp eq i32 %772, 0
  br i1 %773, label %nestedBlock121, label %afterNestedBlock92

nestedBlock121:                                   ; preds = %checkContinueBlock120
  %774 = alloca [4 x float], align 4, !I !70, !ET !71
  %775 = getelementptr [4 x float], ptr %774, i32 0, i32 0
  store float 0.000000e+00, ptr %775, align 4
  %776 = getelementptr [4 x float], ptr %774, i32 0, i32 1
  store float 0.000000e+00, ptr %776, align 4
  %777 = getelementptr [4 x float], ptr %774, i32 0, i32 2
  store float 0.000000e+00, ptr %777, align 4
  %778 = getelementptr [4 x float], ptr %774, i32 0, i32 3
  store float 0.000000e+00, ptr %778, align 4
  %779 = getelementptr [4 x float], ptr %774, i32 0, i32 0
  store float 0.000000e+00, ptr %779, align 4
  %780 = getelementptr [4 x float], ptr %774, i32 0, i32 1
  store float 0.000000e+00, ptr %780, align 4
  %781 = getelementptr [4 x float], ptr %774, i32 0, i32 2
  store float 8.982000e+03, ptr %781, align 4
  %782 = getelementptr [4 x float], ptr %774, i32 0, i32 3
  store float 1.542000e+03, ptr %782, align 4
  %783 = load [4 x float], ptr %774, align 4
  %784 = alloca [4 x float], align 4, !I !70, !ET !71
  %785 = getelementptr [4 x float], ptr %784, i32 0, i32 0
  store float 0.000000e+00, ptr %785, align 4
  %786 = getelementptr [4 x float], ptr %784, i32 0, i32 1
  store float 0.000000e+00, ptr %786, align 4
  %787 = getelementptr [4 x float], ptr %784, i32 0, i32 2
  store float 0.000000e+00, ptr %787, align 4
  %788 = getelementptr [4 x float], ptr %784, i32 0, i32 3
  store float 0.000000e+00, ptr %788, align 4
  %789 = getelementptr [4 x float], ptr %784, i32 0, i32 0
  store float 0.000000e+00, ptr %789, align 4
  %790 = getelementptr [4 x float], ptr %784, i32 0, i32 1
  %screenHeight254 = load i32, ptr @screenHeight, align 4
  %791 = load i32, ptr @screenHeight, align 4
  %792 = sitofp i32 %791 to double
  %793 = fdiv double %792, 3.000000e+00
  %794 = alloca double, align 8
  store double %793, ptr %794, align 8
  %795 = load double, ptr %794, align 8
  %796 = fptrunc double %795 to float
  store float %796, ptr %790, align 4
  %797 = getelementptr [4 x float], ptr %784, i32 0, i32 2
  %screenWidth255 = load i32, ptr @screenWidth, align 4
  %798 = load i32, ptr @screenWidth, align 4
  %screenWidth256 = load i32, ptr @screenWidth, align 4
  %799 = load i32, ptr @screenWidth, align 4
  %800 = sitofp i32 %799 to double
  %801 = fdiv double %800, 2.000000e+00
  %802 = alloca double, align 8
  store double %801, ptr %802, align 8
  %803 = load double, ptr %802, align 8
  %804 = sitofp i32 %798 to double
  %805 = fadd double %804, %803
  %806 = alloca double, align 8
  store double %805, ptr %806, align 8
  %807 = load double, ptr %806, align 8
  %808 = fptrunc double %807 to float
  store float %808, ptr %797, align 4
  %809 = getelementptr [4 x float], ptr %784, i32 0, i32 3
  %screenHeight257 = load i32, ptr @screenHeight, align 4
  %810 = load i32, ptr @screenHeight, align 4
  %811 = sitofp i32 %810 to double
  %812 = fdiv double %811, 3.000000e+00
  %813 = alloca double, align 8
  store double %812, ptr %813, align 8
  %814 = load double, ptr %813, align 8
  %815 = fptrunc double %814 to float
  store float %815, ptr %809, align 4
  %816 = load [4 x float], ptr %784, align 4
  %817 = alloca [2 x float], align 4, !I !72, !ET !71
  %818 = getelementptr [2 x float], ptr %817, i32 0, i32 0
  store float 0.000000e+00, ptr %818, align 4
  %819 = getelementptr [2 x float], ptr %817, i32 0, i32 1
  store float 0.000000e+00, ptr %819, align 4
  %820 = getelementptr [2 x float], ptr %817, i32 0, i32 0
  %821 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x258 = load float, ptr %821, align 4
  %822 = load float, ptr %821, align 4
  store float %822, ptr %820, align 4
  %823 = getelementptr [2 x float], ptr %817, i32 0, i32 1
  %824 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y259 = load float, ptr %824, align 4
  %825 = load float, ptr %824, align 4
  store float %825, ptr %823, align 4
  %826 = load [2 x float], ptr %817, align 4
  %827 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %828 = getelementptr inbounds %COLORS_TYPE.3, ptr %827, i32 0, i32 0
  %WHITE260 = load i32, ptr %828, align 4
  %829 = load i32, ptr %828, align 4
  call void @DrawTexturePro(ptr %mountL1Texture, [4 x float] %783, [4 x float] %816, [2 x float] %826, float 0.000000e+00, i32 %829)
  %830 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %831 = icmp eq i32 %830, 0
  br i1 %831, label %checkContinueBlock122, label %afterNestedBlock92

checkContinueBlock122:                            ; preds = %nestedBlock121
  %832 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %833 = icmp eq i32 %832, 0
  br i1 %833, label %nestedBlock123, label %afterNestedBlock92

nestedBlock123:                                   ; preds = %checkContinueBlock122
  %834 = alloca [4 x float], align 4, !I !70, !ET !71
  %835 = getelementptr [4 x float], ptr %834, i32 0, i32 0
  store float 0.000000e+00, ptr %835, align 4
  %836 = getelementptr [4 x float], ptr %834, i32 0, i32 1
  store float 0.000000e+00, ptr %836, align 4
  %837 = getelementptr [4 x float], ptr %834, i32 0, i32 2
  store float 0.000000e+00, ptr %837, align 4
  %838 = getelementptr [4 x float], ptr %834, i32 0, i32 3
  store float 0.000000e+00, ptr %838, align 4
  %839 = getelementptr [4 x float], ptr %834, i32 0, i32 0
  store float 0.000000e+00, ptr %839, align 4
  %840 = getelementptr [4 x float], ptr %834, i32 0, i32 1
  store float 0.000000e+00, ptr %840, align 4
  %841 = getelementptr [4 x float], ptr %834, i32 0, i32 2
  store float 8.982000e+03, ptr %841, align 4
  %842 = getelementptr [4 x float], ptr %834, i32 0, i32 3
  store float 1.542000e+03, ptr %842, align 4
  %843 = load [4 x float], ptr %834, align 4
  %844 = alloca [4 x float], align 4, !I !70, !ET !71
  %845 = getelementptr [4 x float], ptr %844, i32 0, i32 0
  store float 0.000000e+00, ptr %845, align 4
  %846 = getelementptr [4 x float], ptr %844, i32 0, i32 1
  store float 0.000000e+00, ptr %846, align 4
  %847 = getelementptr [4 x float], ptr %844, i32 0, i32 2
  store float 0.000000e+00, ptr %847, align 4
  %848 = getelementptr [4 x float], ptr %844, i32 0, i32 3
  store float 0.000000e+00, ptr %848, align 4
  %849 = getelementptr [4 x float], ptr %844, i32 0, i32 0
  store float 0.000000e+00, ptr %849, align 4
  %850 = getelementptr [4 x float], ptr %844, i32 0, i32 1
  %screenHeight261 = load i32, ptr @screenHeight, align 4
  %851 = load i32, ptr @screenHeight, align 4
  %852 = sitofp i32 %851 to double
  %853 = fdiv double %852, 3.000000e+00
  %854 = alloca double, align 8
  store double %853, ptr %854, align 8
  %855 = load double, ptr %854, align 8
  %856 = fptrunc double %855 to float
  store float %856, ptr %850, align 4
  %857 = getelementptr [4 x float], ptr %844, i32 0, i32 2
  %screenWidth262 = load i32, ptr @screenWidth, align 4
  %858 = load i32, ptr @screenWidth, align 4
  %screenWidth263 = load i32, ptr @screenWidth, align 4
  %859 = load i32, ptr @screenWidth, align 4
  %860 = sitofp i32 %859 to double
  %861 = fdiv double %860, 2.000000e+00
  %862 = alloca double, align 8
  store double %861, ptr %862, align 8
  %863 = load double, ptr %862, align 8
  %864 = sitofp i32 %858 to double
  %865 = fadd double %864, %863
  %866 = alloca double, align 8
  store double %865, ptr %866, align 8
  %867 = load double, ptr %866, align 8
  %868 = fptrunc double %867 to float
  store float %868, ptr %857, align 4
  %869 = getelementptr [4 x float], ptr %844, i32 0, i32 3
  %screenHeight264 = load i32, ptr @screenHeight, align 4
  %870 = load i32, ptr @screenHeight, align 4
  %871 = sitofp i32 %870 to double
  %872 = fdiv double %871, 3.000000e+00
  %873 = alloca double, align 8
  store double %872, ptr %873, align 8
  %874 = load double, ptr %873, align 8
  %875 = fptrunc double %874 to float
  store float %875, ptr %869, align 4
  %876 = load [4 x float], ptr %844, align 4
  %877 = alloca [2 x float], align 4, !I !72, !ET !71
  %878 = getelementptr [2 x float], ptr %877, i32 0, i32 0
  store float 0.000000e+00, ptr %878, align 4
  %879 = getelementptr [2 x float], ptr %877, i32 0, i32 1
  store float 0.000000e+00, ptr %879, align 4
  %880 = getelementptr [2 x float], ptr %877, i32 0, i32 0
  %881 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x265 = load float, ptr %881, align 4
  %882 = load float, ptr %881, align 4
  store float %882, ptr %880, align 4
  %883 = getelementptr [2 x float], ptr %877, i32 0, i32 1
  %884 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y266 = load float, ptr %884, align 4
  %885 = load float, ptr %884, align 4
  store float %885, ptr %883, align 4
  %886 = load [2 x float], ptr %877, align 4
  %887 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %888 = getelementptr inbounds %COLORS_TYPE.3, ptr %887, i32 0, i32 0
  %WHITE267 = load i32, ptr %888, align 4
  %889 = load i32, ptr %888, align 4
  call void @DrawTexturePro(ptr %mountL1Texture, [4 x float] %843, [4 x float] %876, [2 x float] %886, float 0.000000e+00, i32 %889)
  %890 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %891 = icmp eq i32 %890, 0
  br i1 %891, label %checkContinueBlock124, label %afterNestedBlock92

checkContinueBlock124:                            ; preds = %nestedBlock123
  %892 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %893 = icmp eq i32 %892, 0
  br i1 %893, label %nestedBlock125, label %afterNestedBlock92

nestedBlock125:                                   ; preds = %checkContinueBlock124
  %894 = alloca [4 x float], align 4, !I !70, !ET !71
  %895 = getelementptr [4 x float], ptr %894, i32 0, i32 0
  store float 0.000000e+00, ptr %895, align 4
  %896 = getelementptr [4 x float], ptr %894, i32 0, i32 1
  store float 0.000000e+00, ptr %896, align 4
  %897 = getelementptr [4 x float], ptr %894, i32 0, i32 2
  store float 0.000000e+00, ptr %897, align 4
  %898 = getelementptr [4 x float], ptr %894, i32 0, i32 3
  store float 0.000000e+00, ptr %898, align 4
  %899 = getelementptr [4 x float], ptr %894, i32 0, i32 0
  store float 3.100000e+02, ptr %899, align 4
  %900 = getelementptr [4 x float], ptr %894, i32 0, i32 1
  store float 1.250000e+03, ptr %900, align 4
  %901 = getelementptr [4 x float], ptr %894, i32 0, i32 2
  %902 = alloca float, align 4
  store float 4.360000e+03, ptr %902, align 4
  %903 = load float, ptr %902, align 4
  store float %903, ptr %901, align 4
  %904 = getelementptr [4 x float], ptr %894, i32 0, i32 3
  store float 1.250000e+03, ptr %904, align 4
  %905 = load [4 x float], ptr %894, align 4
  %906 = alloca [4 x float], align 4, !I !70, !ET !71
  %907 = getelementptr [4 x float], ptr %906, i32 0, i32 0
  store float 0.000000e+00, ptr %907, align 4
  %908 = getelementptr [4 x float], ptr %906, i32 0, i32 1
  store float 0.000000e+00, ptr %908, align 4
  %909 = getelementptr [4 x float], ptr %906, i32 0, i32 2
  store float 0.000000e+00, ptr %909, align 4
  %910 = getelementptr [4 x float], ptr %906, i32 0, i32 3
  store float 0.000000e+00, ptr %910, align 4
  %911 = getelementptr [4 x float], ptr %906, i32 0, i32 0
  store float 0.000000e+00, ptr %911, align 4
  %912 = getelementptr [4 x float], ptr %906, i32 0, i32 1
  %screenHeight268 = load i32, ptr @screenHeight, align 4
  %913 = load i32, ptr @screenHeight, align 4
  %914 = sitofp i32 %913 to double
  %915 = fdiv double %914, 2.000000e+00
  %916 = alloca double, align 8
  store double %915, ptr %916, align 8
  %917 = load double, ptr %916, align 8
  %screenHeight269 = load i32, ptr @screenHeight, align 4
  %918 = load i32, ptr @screenHeight, align 4
  %919 = sitofp i32 %918 to double
  %920 = fdiv double %919, 1.000000e+01
  %921 = alloca double, align 8
  store double %920, ptr %921, align 8
  %922 = load double, ptr %921, align 8
  %923 = fadd double %917, %922
  %924 = alloca double, align 8
  store double %923, ptr %924, align 8
  %925 = load double, ptr %924, align 8
  %926 = fptrunc double %925 to float
  store float %926, ptr %912, align 4
  %927 = getelementptr [4 x float], ptr %906, i32 0, i32 2
  %screenWidth270 = load i32, ptr @screenWidth, align 4
  %928 = load i32, ptr @screenWidth, align 4
  %929 = sitofp i32 %928 to float
  store float %929, ptr %927, align 4
  %930 = getelementptr [4 x float], ptr %906, i32 0, i32 3
  %screenHeight271 = load i32, ptr @screenHeight, align 4
  %931 = load i32, ptr @screenHeight, align 4
  %932 = sitofp i32 %931 to double
  %933 = fdiv double %932, 2.000000e+00
  %934 = alloca double, align 8
  store double %933, ptr %934, align 8
  %935 = load double, ptr %934, align 8
  %936 = fptrunc double %935 to float
  store float %936, ptr %930, align 4
  %937 = load [4 x float], ptr %906, align 4
  %938 = alloca [2 x float], align 4, !I !72, !ET !71
  %939 = getelementptr [2 x float], ptr %938, i32 0, i32 0
  store float 0.000000e+00, ptr %939, align 4
  %940 = getelementptr [2 x float], ptr %938, i32 0, i32 1
  store float 0.000000e+00, ptr %940, align 4
  %941 = getelementptr [2 x float], ptr %938, i32 0, i32 0
  %942 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x272 = load float, ptr %942, align 4
  %943 = load float, ptr %942, align 4
  store float %943, ptr %941, align 4
  %944 = getelementptr [2 x float], ptr %938, i32 0, i32 1
  %945 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y273 = load float, ptr %945, align 4
  %946 = load float, ptr %945, align 4
  store float %946, ptr %944, align 4
  %947 = load [2 x float], ptr %938, align 4
  %948 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %949 = getelementptr inbounds %COLORS_TYPE.3, ptr %948, i32 0, i32 0
  %WHITE274 = load i32, ptr %949, align 4
  %950 = load i32, ptr %949, align 4
  call void @DrawTexturePro(ptr %groundTexture, [4 x float] %905, [4 x float] %937, [2 x float] %947, float 0.000000e+00, i32 %950)
  %951 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %952 = icmp eq i32 %951, 0
  br i1 %952, label %checkContinueBlock126, label %afterNestedBlock92

checkContinueBlock126:                            ; preds = %nestedBlock125
  %953 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %954 = icmp eq i32 %953, 0
  br i1 %954, label %nestedBlock127, label %afterNestedBlock92

nestedBlock127:                                   ; preds = %checkContinueBlock126
  %955 = alloca [4 x float], align 4, !I !70, !ET !71
  %956 = getelementptr [4 x float], ptr %955, i32 0, i32 0
  store float 0.000000e+00, ptr %956, align 4
  %957 = getelementptr [4 x float], ptr %955, i32 0, i32 1
  store float 0.000000e+00, ptr %957, align 4
  %958 = getelementptr [4 x float], ptr %955, i32 0, i32 2
  store float 0.000000e+00, ptr %958, align 4
  %959 = getelementptr [4 x float], ptr %955, i32 0, i32 3
  store float 0.000000e+00, ptr %959, align 4
  %960 = getelementptr [4 x float], ptr %955, i32 0, i32 0
  store float 3.100000e+02, ptr %960, align 4
  %961 = getelementptr [4 x float], ptr %955, i32 0, i32 1
  store float 1.250000e+03, ptr %961, align 4
  %962 = getelementptr [4 x float], ptr %955, i32 0, i32 2
  %963 = alloca float, align 4
  store float 4.360000e+03, ptr %963, align 4
  %964 = load float, ptr %963, align 4
  store float %964, ptr %962, align 4
  %965 = getelementptr [4 x float], ptr %955, i32 0, i32 3
  store float 1.250000e+03, ptr %965, align 4
  %966 = load [4 x float], ptr %955, align 4
  %967 = alloca [4 x float], align 4, !I !70, !ET !71
  %968 = getelementptr [4 x float], ptr %967, i32 0, i32 0
  store float 0.000000e+00, ptr %968, align 4
  %969 = getelementptr [4 x float], ptr %967, i32 0, i32 1
  store float 0.000000e+00, ptr %969, align 4
  %970 = getelementptr [4 x float], ptr %967, i32 0, i32 2
  store float 0.000000e+00, ptr %970, align 4
  %971 = getelementptr [4 x float], ptr %967, i32 0, i32 3
  store float 0.000000e+00, ptr %971, align 4
  %972 = getelementptr [4 x float], ptr %967, i32 0, i32 0
  store float 0.000000e+00, ptr %972, align 4
  %973 = getelementptr [4 x float], ptr %967, i32 0, i32 1
  %screenHeight275 = load i32, ptr @screenHeight, align 4
  %974 = load i32, ptr @screenHeight, align 4
  %975 = sitofp i32 %974 to double
  %976 = fdiv double %975, 2.000000e+00
  %977 = alloca double, align 8
  store double %976, ptr %977, align 8
  %978 = load double, ptr %977, align 8
  %screenHeight276 = load i32, ptr @screenHeight, align 4
  %979 = load i32, ptr @screenHeight, align 4
  %980 = sitofp i32 %979 to double
  %981 = fdiv double %980, 1.000000e+01
  %982 = alloca double, align 8
  store double %981, ptr %982, align 8
  %983 = load double, ptr %982, align 8
  %984 = fadd double %978, %983
  %985 = alloca double, align 8
  store double %984, ptr %985, align 8
  %986 = load double, ptr %985, align 8
  %987 = fptrunc double %986 to float
  store float %987, ptr %973, align 4
  %988 = getelementptr [4 x float], ptr %967, i32 0, i32 2
  %screenWidth277 = load i32, ptr @screenWidth, align 4
  %989 = load i32, ptr @screenWidth, align 4
  %990 = sitofp i32 %989 to float
  store float %990, ptr %988, align 4
  %991 = getelementptr [4 x float], ptr %967, i32 0, i32 3
  %screenHeight278 = load i32, ptr @screenHeight, align 4
  %992 = load i32, ptr @screenHeight, align 4
  %993 = sitofp i32 %992 to double
  %994 = fdiv double %993, 2.000000e+00
  %995 = alloca double, align 8
  store double %994, ptr %995, align 8
  %996 = load double, ptr %995, align 8
  %997 = fptrunc double %996 to float
  store float %997, ptr %991, align 4
  %998 = load [4 x float], ptr %967, align 4
  %999 = alloca [2 x float], align 4, !I !72, !ET !71
  %1000 = getelementptr [2 x float], ptr %999, i32 0, i32 0
  store float 0.000000e+00, ptr %1000, align 4
  %1001 = getelementptr [2 x float], ptr %999, i32 0, i32 1
  store float 0.000000e+00, ptr %1001, align 4
  %1002 = getelementptr [2 x float], ptr %999, i32 0, i32 0
  %1003 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x279 = load float, ptr %1003, align 4
  %1004 = load float, ptr %1003, align 4
  store float %1004, ptr %1002, align 4
  %1005 = getelementptr [2 x float], ptr %999, i32 0, i32 1
  %1006 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y280 = load float, ptr %1006, align 4
  %1007 = load float, ptr %1006, align 4
  store float %1007, ptr %1005, align 4
  %1008 = load [2 x float], ptr %999, align 4
  %1009 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %1010 = getelementptr inbounds %COLORS_TYPE.3, ptr %1009, i32 0, i32 0
  %WHITE281 = load i32, ptr %1010, align 4
  %1011 = load i32, ptr %1010, align 4
  call void @DrawTexturePro(ptr %groundTexture, [4 x float] %966, [4 x float] %998, [2 x float] %1008, float 0.000000e+00, i32 %1011)
  %1012 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1013 = icmp eq i32 %1012, 0
  br i1 %1013, label %checkContinueBlock128, label %afterNestedBlock92

checkContinueBlock128:                            ; preds = %nestedBlock127
  %1014 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1015 = icmp eq i32 %1014, 0
  br i1 %1015, label %nestedBlock129, label %afterNestedBlock92

nestedBlock129:                                   ; preds = %checkContinueBlock128
  %1016 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %1017 = load ptr, ptr %1016, align 8
  %1018 = getelementptr inbounds %"Bird::VTableType", ptr %1017, i32 0, i32 0
  %1019 = load ptr, ptr %1018, align 8
  %rtPtr282 = alloca %Texture.0, align 8
  call void %1019(ptr %rtPtr282, ptr %67)
  %1020 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %1021 = load ptr, ptr %1020, align 8
  %1022 = getelementptr inbounds %"Bird::VTableType", ptr %1021, i32 0, i32 4
  %1023 = load ptr, ptr %1022, align 8
  %rtPtr283 = alloca [4 x float], align 4
  call void %1023(ptr %rtPtr283, ptr %67)
  %1024 = load [4 x float], ptr %rtPtr283, align 4
  %1025 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %1026 = load ptr, ptr %1025, align 8
  %1027 = getelementptr inbounds %"Bird::VTableType", ptr %1026, i32 0, i32 3
  %1028 = load ptr, ptr %1027, align 8
  %rtPtr284 = alloca [4 x float], align 4
  call void %1028(ptr %rtPtr284, ptr %67)
  %1029 = load [4 x float], ptr %rtPtr284, align 4
  %1030 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %1031 = load ptr, ptr %1030, align 8
  %1032 = getelementptr inbounds %"Bird::VTableType", ptr %1031, i32 0, i32 2
  %1033 = load ptr, ptr %1032, align 8
  %rtPtr285 = alloca [2 x float], align 4
  call void %1033(ptr %rtPtr285, ptr %67)
  %1034 = load [2 x float], ptr %rtPtr285, align 4
  %1035 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %1036 = load ptr, ptr %1035, align 8
  %1037 = getelementptr inbounds %"Bird::VTableType", ptr %1036, i32 0, i32 1
  %1038 = load ptr, ptr %1037, align 8
  %rtPtr286 = alloca float, align 4
  call void %1038(ptr %rtPtr286, ptr %67)
  %1039 = load float, ptr %rtPtr286, align 4
  %1040 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %1041 = getelementptr inbounds %COLORS_TYPE.3, ptr %1040, i32 0, i32 0
  %WHITE287 = load i32, ptr %1041, align 4
  %1042 = load i32, ptr %1041, align 4
  call void @DrawTexturePro(ptr %rtPtr282, [4 x float] %1024, [4 x float] %1029, [2 x float] %1034, float %1039, i32 %1042)
  %1043 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1044 = icmp eq i32 %1043, 0
  br i1 %1044, label %checkContinueBlock130, label %afterNestedBlock92

checkContinueBlock130:                            ; preds = %nestedBlock129
  %1045 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1046 = icmp eq i32 %1045, 0
  br i1 %1046, label %nestedBlock131, label %afterNestedBlock92

nestedBlock131:                                   ; preds = %checkContinueBlock130
  %1047 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1048 = load ptr, ptr %1047, align 8
  %1049 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1048, i32 0, i32 22
  %1050 = load ptr, ptr %1049, align 8
  call void %1050(ptr %1)
  %1051 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1052 = icmp eq i32 %1051, 0
  br i1 %1052, label %checkContinueBlock132, label %afterNestedBlock92

checkContinueBlock132:                            ; preds = %nestedBlock131
  br label %afterNestedBlock92

afterNestedBlock134:                              ; preds = %checkContinueBlock142, %afterIfElse159, %checkContinueBlock140, %afterIfElse151, %checkContinueBlock138, %nestedBlock137, %checkContinueBlock136, %nestedBlock135
  %1053 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1054 = icmp eq i32 %1053, 0
  br i1 %1054, label %checkContinueBlock96, label %afterNestedBlock92

nestedBlock135:                                   ; preds = %nestedBlock95
  %1055 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x = load float, ptr %1055, align 4
  %1056 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x143 = load float, ptr %1056, align 4
  %1057 = load float, ptr %1056, align 4
  %1058 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1059 = load ptr, ptr %1058, align 8
  %1060 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1059, i32 0, i32 8
  %1061 = load ptr, ptr %1060, align 8
  %rtPtr144 = alloca float, align 4
  call void %1061(ptr %rtPtr144, ptr %1)
  %1062 = load float, ptr %rtPtr144, align 4
  %1063 = fmul float %1062, 1.000000e+02
  %1064 = alloca float, align 4
  store float %1063, ptr %1064, align 4
  %1065 = load float, ptr %1064, align 4
  %1066 = fadd float %1057, %1065
  %1067 = alloca float, align 4
  store float %1066, ptr %1067, align 4
  %1068 = load float, ptr %1067, align 4
  store float %1068, ptr %1055, align 4
  %1069 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1070 = icmp eq i32 %1069, 0
  br i1 %1070, label %checkContinueBlock136, label %afterNestedBlock134

checkContinueBlock136:                            ; preds = %nestedBlock135
  %1071 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1072 = icmp eq i32 %1071, 0
  br i1 %1072, label %nestedBlock137, label %afterNestedBlock134

nestedBlock137:                                   ; preds = %checkContinueBlock136
  %1073 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x145 = load float, ptr %1073, align 4
  %1074 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x146 = load float, ptr %1074, align 4
  %1075 = load float, ptr %1074, align 4
  %1076 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1077 = load ptr, ptr %1076, align 8
  %1078 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1077, i32 0, i32 8
  %1079 = load ptr, ptr %1078, align 8
  %rtPtr147 = alloca float, align 4
  call void %1079(ptr %rtPtr147, ptr %1)
  %1080 = load float, ptr %rtPtr147, align 4
  %1081 = fmul float %1080, 1.000000e+02
  %1082 = alloca float, align 4
  store float %1081, ptr %1082, align 4
  %1083 = load float, ptr %1082, align 4
  %1084 = fadd float %1075, %1083
  %1085 = alloca float, align 4
  store float %1084, ptr %1085, align 4
  %1086 = load float, ptr %1085, align 4
  store float %1086, ptr %1073, align 4
  %1087 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1088 = icmp eq i32 %1087, 0
  br i1 %1088, label %checkContinueBlock138, label %afterNestedBlock134

checkContinueBlock138:                            ; preds = %nestedBlock137
  %1089 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1090 = icmp eq i32 %1089, 0
  br i1 %1090, label %nestedBlock139, label %afterNestedBlock134

nestedBlock139:                                   ; preds = %checkContinueBlock138
  %1091 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x148 = load float, ptr %1091, align 4
  %1092 = load float, ptr %1091, align 4
  %1093 = fcmp ogt float %1092, 1.542000e+03
  %1094 = alloca i1, align 1
  store i1 %1093, ptr %1094, align 1
  %1095 = load i1, ptr %1094, align 1
  br i1 %1095, label %then149, label %else150

checkContinueBlock140:                            ; preds = %afterIfElse151
  %1096 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1097 = icmp eq i32 %1096, 0
  br i1 %1097, label %nestedBlock141, label %afterNestedBlock134

nestedBlock141:                                   ; preds = %checkContinueBlock140
  %1098 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x156 = load float, ptr %1098, align 4
  %1099 = load float, ptr %1098, align 4
  %1100 = fcmp ogt float %1099, 1.542000e+03
  %1101 = alloca i1, align 1
  store i1 %1100, ptr %1101, align 1
  %1102 = load i1, ptr %1101, align 1
  br i1 %1102, label %then157, label %else158

checkContinueBlock142:                            ; preds = %afterIfElse159
  br label %afterNestedBlock134

then149:                                          ; preds = %nestedBlock139
  br label %nestedBlock153

else150:                                          ; preds = %nestedBlock139
  br label %afterIfElse151

afterIfElse151:                                   ; preds = %else150, %afterNestedBlock152
  %1103 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1104 = icmp eq i32 %1103, 0
  br i1 %1104, label %checkContinueBlock140, label %afterNestedBlock134

afterNestedBlock152:                              ; preds = %checkContinueBlock154, %nestedBlock153
  %1105 = load float, ptr %1106, align 4
  br label %afterIfElse151

nestedBlock153:                                   ; preds = %then149
  %1106 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x155 = load float, ptr %1106, align 4
  %1107 = alloca i32, align 4
  store i32 -1542, ptr %1107, align 4
  %1108 = load i32, ptr %1107, align 4
  %1109 = sitofp i32 %1108 to float
  store float %1109, ptr %1106, align 4
  %1110 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1111 = icmp eq i32 %1110, 0
  br i1 %1111, label %checkContinueBlock154, label %afterNestedBlock152

checkContinueBlock154:                            ; preds = %nestedBlock153
  br label %afterNestedBlock152

then157:                                          ; preds = %nestedBlock141
  br label %nestedBlock161

else158:                                          ; preds = %nestedBlock141
  br label %afterIfElse159

afterIfElse159:                                   ; preds = %else158, %afterNestedBlock160
  %1112 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1113 = icmp eq i32 %1112, 0
  br i1 %1113, label %checkContinueBlock142, label %afterNestedBlock134

afterNestedBlock160:                              ; preds = %checkContinueBlock162, %nestedBlock161
  %1114 = load float, ptr %1115, align 4
  br label %afterIfElse159

nestedBlock161:                                   ; preds = %then157
  %1115 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x163 = load float, ptr %1115, align 4
  %1116 = alloca i32, align 4
  store i32 -1542, ptr %1116, align 4
  %1117 = load i32, ptr %1116, align 4
  %1118 = sitofp i32 %1117 to float
  store float %1118, ptr %1115, align 4
  %1119 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1120 = icmp eq i32 %1119, 0
  br i1 %1120, label %checkContinueBlock162, label %afterNestedBlock160

checkContinueBlock162:                            ; preds = %nestedBlock161
  br label %afterNestedBlock160

afterNestedBlock164:                              ; preds = %checkContinueBlock168, %afterIfElse177, %checkContinueBlock166, %nestedBlock165
  %1121 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1122 = icmp eq i32 %1121, 0
  br i1 %1122, label %checkContinueBlock98, label %afterNestedBlock92

nestedBlock165:                                   ; preds = %nestedBlock97
  %1123 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x169 = load float, ptr %1123, align 4
  %1124 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x170 = load float, ptr %1124, align 4
  %1125 = load float, ptr %1124, align 4
  %1126 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1127 = load ptr, ptr %1126, align 8
  %1128 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1127, i32 0, i32 8
  %1129 = load ptr, ptr %1128, align 8
  %rtPtr171 = alloca float, align 4
  call void %1129(ptr %rtPtr171, ptr %1)
  %1130 = load float, ptr %rtPtr171, align 4
  %1131 = fmul float %1130, 1.000000e+01
  %1132 = alloca float, align 4
  store float %1131, ptr %1132, align 4
  %1133 = load float, ptr %1132, align 4
  %1134 = fadd float %1125, %1133
  %1135 = alloca float, align 4
  store float %1134, ptr %1135, align 4
  %1136 = load float, ptr %1135, align 4
  store float %1136, ptr %1123, align 4
  %1137 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1138 = icmp eq i32 %1137, 0
  br i1 %1138, label %checkContinueBlock166, label %afterNestedBlock164

checkContinueBlock166:                            ; preds = %nestedBlock165
  %1139 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1140 = icmp eq i32 %1139, 0
  br i1 %1140, label %nestedBlock167, label %afterNestedBlock164

nestedBlock167:                                   ; preds = %checkContinueBlock166
  %1141 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x172 = load float, ptr %1141, align 4
  %1142 = load float, ptr %1141, align 4
  %screenWidth173 = load i32, ptr @screenWidth, align 4
  %1143 = load i32, ptr @screenWidth, align 4
  %screenWidth174 = load i32, ptr @screenWidth, align 4
  %1144 = load i32, ptr @screenWidth, align 4
  %1145 = sitofp i32 %1144 to double
  %1146 = fdiv double %1145, 2.000000e+00
  %1147 = alloca double, align 8
  store double %1146, ptr %1147, align 8
  %1148 = load double, ptr %1147, align 8
  %1149 = sitofp i32 %1143 to double
  %1150 = fadd double %1149, %1148
  %1151 = alloca double, align 8
  store double %1150, ptr %1151, align 8
  %1152 = load double, ptr %1151, align 8
  %1153 = fptrunc double %1152 to float
  %1154 = fcmp ogt float %1142, %1153
  %1155 = alloca i1, align 1
  store i1 %1154, ptr %1155, align 1
  %1156 = load i1, ptr %1155, align 1
  br i1 %1156, label %then175, label %else176

checkContinueBlock168:                            ; preds = %afterIfElse177
  br label %afterNestedBlock164

then175:                                          ; preds = %nestedBlock167
  br label %nestedBlock179

else176:                                          ; preds = %nestedBlock167
  br label %afterIfElse177

afterIfElse177:                                   ; preds = %else176, %afterNestedBlock178
  %1157 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1158 = icmp eq i32 %1157, 0
  br i1 %1158, label %checkContinueBlock168, label %afterNestedBlock164

afterNestedBlock178:                              ; preds = %checkContinueBlock180, %nestedBlock179
  %1159 = load float, ptr %1160, align 4
  br label %afterIfElse177

nestedBlock179:                                   ; preds = %then175
  %1160 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x181 = load float, ptr %1160, align 4
  %screenWidth182 = load i32, ptr @screenWidth, align 4
  %1161 = load i32, ptr @screenWidth, align 4
  %1162 = mul i32 -1, %1161
  %1163 = alloca i32, align 4
  store i32 %1162, ptr %1163, align 4
  %1164 = load i32, ptr %1163, align 4
  %1165 = sitofp i32 %1164 to float
  store float %1165, ptr %1160, align 4
  %1166 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1167 = icmp eq i32 %1166, 0
  br i1 %1167, label %checkContinueBlock180, label %afterNestedBlock178

checkContinueBlock180:                            ; preds = %nestedBlock179
  br label %afterNestedBlock178

afterNestedBlock183:                              ; preds = %checkContinueBlock187, %afterIfElse196, %checkContinueBlock185, %nestedBlock184
  %1168 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1169 = icmp eq i32 %1168, 0
  br i1 %1169, label %checkContinueBlock100, label %afterNestedBlock92

nestedBlock184:                                   ; preds = %nestedBlock99
  %1170 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x188 = load float, ptr %1170, align 4
  %1171 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x189 = load float, ptr %1171, align 4
  %1172 = load float, ptr %1171, align 4
  %1173 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1174 = load ptr, ptr %1173, align 8
  %1175 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1174, i32 0, i32 8
  %1176 = load ptr, ptr %1175, align 8
  %rtPtr190 = alloca float, align 4
  call void %1176(ptr %rtPtr190, ptr %1)
  %1177 = load float, ptr %rtPtr190, align 4
  %1178 = fmul float %1177, 1.000000e+01
  %1179 = alloca float, align 4
  store float %1178, ptr %1179, align 4
  %1180 = load float, ptr %1179, align 4
  %1181 = fadd float %1172, %1180
  %1182 = alloca float, align 4
  store float %1181, ptr %1182, align 4
  %1183 = load float, ptr %1182, align 4
  store float %1183, ptr %1170, align 4
  %1184 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1185 = icmp eq i32 %1184, 0
  br i1 %1185, label %checkContinueBlock185, label %afterNestedBlock183

checkContinueBlock185:                            ; preds = %nestedBlock184
  %1186 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1187 = icmp eq i32 %1186, 0
  br i1 %1187, label %nestedBlock186, label %afterNestedBlock183

nestedBlock186:                                   ; preds = %checkContinueBlock185
  %1188 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x191 = load float, ptr %1188, align 4
  %1189 = load float, ptr %1188, align 4
  %screenWidth192 = load i32, ptr @screenWidth, align 4
  %1190 = load i32, ptr @screenWidth, align 4
  %screenWidth193 = load i32, ptr @screenWidth, align 4
  %1191 = load i32, ptr @screenWidth, align 4
  %1192 = sitofp i32 %1191 to double
  %1193 = fdiv double %1192, 2.000000e+00
  %1194 = alloca double, align 8
  store double %1193, ptr %1194, align 8
  %1195 = load double, ptr %1194, align 8
  %1196 = sitofp i32 %1190 to double
  %1197 = fadd double %1196, %1195
  %1198 = alloca double, align 8
  store double %1197, ptr %1198, align 8
  %1199 = load double, ptr %1198, align 8
  %1200 = fptrunc double %1199 to float
  %1201 = fcmp ogt float %1189, %1200
  %1202 = alloca i1, align 1
  store i1 %1201, ptr %1202, align 1
  %1203 = load i1, ptr %1202, align 1
  br i1 %1203, label %then194, label %else195

checkContinueBlock187:                            ; preds = %afterIfElse196
  br label %afterNestedBlock183

then194:                                          ; preds = %nestedBlock186
  br label %nestedBlock198

else195:                                          ; preds = %nestedBlock186
  br label %afterIfElse196

afterIfElse196:                                   ; preds = %else195, %afterNestedBlock197
  %1204 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1205 = icmp eq i32 %1204, 0
  br i1 %1205, label %checkContinueBlock187, label %afterNestedBlock183

afterNestedBlock197:                              ; preds = %checkContinueBlock199, %nestedBlock198
  %1206 = load float, ptr %1207, align 4
  br label %afterIfElse196

nestedBlock198:                                   ; preds = %then194
  %1207 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x200 = load float, ptr %1207, align 4
  %screenWidth201 = load i32, ptr @screenWidth, align 4
  %1208 = load i32, ptr @screenWidth, align 4
  %1209 = mul i32 -1, %1208
  %1210 = alloca i32, align 4
  store i32 %1209, ptr %1210, align 4
  %1211 = load i32, ptr %1210, align 4
  %1212 = sitofp i32 %1211 to float
  store float %1212, ptr %1207, align 4
  %1213 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1214 = icmp eq i32 %1213, 0
  br i1 %1214, label %checkContinueBlock199, label %afterNestedBlock197

checkContinueBlock199:                            ; preds = %nestedBlock198
  br label %afterNestedBlock197

afterNestedBlock202:                              ; preds = %checkContinueBlock206, %afterIfElse215, %checkContinueBlock204, %nestedBlock203
  %1215 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1216 = icmp eq i32 %1215, 0
  br i1 %1216, label %checkContinueBlock102, label %afterNestedBlock92

nestedBlock203:                                   ; preds = %nestedBlock101
  %1217 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x207 = load float, ptr %1217, align 4
  %1218 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x208 = load float, ptr %1218, align 4
  %1219 = load float, ptr %1218, align 4
  %1220 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1221 = load ptr, ptr %1220, align 8
  %1222 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1221, i32 0, i32 8
  %1223 = load ptr, ptr %1222, align 8
  %rtPtr209 = alloca float, align 4
  call void %1223(ptr %rtPtr209, ptr %1)
  %1224 = load float, ptr %rtPtr209, align 4
  %1225 = fmul float %1224, 1.000000e+01
  %1226 = alloca float, align 4
  store float %1225, ptr %1226, align 4
  %1227 = load float, ptr %1226, align 4
  %1228 = fadd float %1219, %1227
  %1229 = alloca float, align 4
  store float %1228, ptr %1229, align 4
  %1230 = load float, ptr %1229, align 4
  store float %1230, ptr %1217, align 4
  %1231 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1232 = icmp eq i32 %1231, 0
  br i1 %1232, label %checkContinueBlock204, label %afterNestedBlock202

checkContinueBlock204:                            ; preds = %nestedBlock203
  %1233 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %1234 = icmp eq i32 %1233, 0
  br i1 %1234, label %nestedBlock205, label %afterNestedBlock202

nestedBlock205:                                   ; preds = %checkContinueBlock204
  %1235 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x210 = load float, ptr %1235, align 4
  %1236 = load float, ptr %1235, align 4
  %screenWidth211 = load i32, ptr @screenWidth, align 4
  %1237 = load i32, ptr @screenWidth, align 4
  %screenWidth212 = load i32, ptr @screenWidth, align 4
  %1238 = load i32, ptr @screenWidth, align 4
  %1239 = sitofp i32 %1238 to double
  %1240 = fdiv double %1239, 2.000000e+00
  %1241 = alloca double, align 8
  store double %1240, ptr %1241, align 8
  %1242 = load double, ptr %1241, align 8
  %1243 = sitofp i32 %1237 to double
  %1244 = fadd double %1243, %1242
  %1245 = alloca double, align 8
  store double %1244, ptr %1245, align 8
  %1246 = load double, ptr %1245, align 8
  %1247 = fptrunc double %1246 to float
  %1248 = fcmp ogt float %1236, %1247
  %1249 = alloca i1, align 1
  store i1 %1248, ptr %1249, align 1
  %1250 = load i1, ptr %1249, align 1
  br i1 %1250, label %then213, label %else214

checkContinueBlock206:                            ; preds = %afterIfElse215
  br label %afterNestedBlock202

then213:                                          ; preds = %nestedBlock205
  br label %nestedBlock217

else214:                                          ; preds = %nestedBlock205
  br label %afterIfElse215

afterIfElse215:                                   ; preds = %else214, %afterNestedBlock216
  %1251 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1252 = icmp eq i32 %1251, 0
  br i1 %1252, label %checkContinueBlock206, label %afterNestedBlock202

afterNestedBlock216:                              ; preds = %checkContinueBlock218, %nestedBlock217
  %1253 = load float, ptr %1254, align 4
  br label %afterIfElse215

nestedBlock217:                                   ; preds = %then213
  %1254 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x219 = load float, ptr %1254, align 4
  %screenWidth220 = load i32, ptr @screenWidth, align 4
  %1255 = load i32, ptr @screenWidth, align 4
  %1256 = mul i32 -1, %1255
  %1257 = alloca i32, align 4
  store i32 %1256, ptr %1257, align 4
  %1258 = load i32, ptr %1257, align 4
  %rtPtr221 = alloca i32, align 4
  %screenWidth222 = load i32, ptr @screenWidth, align 4
  %1259 = load i32, ptr @screenWidth, align 4
  %1260 = sitofp i32 %1259 to double
  %1261 = fdiv double %1260, 4.000000e+00
  %1262 = alloca double, align 8
  store double %1261, ptr %1262, align 8
  %1263 = load double, ptr %1262, align 8
  %1264 = fptosi double %1263 to i32
  %1265 = alloca i32, align 4
  store i32 %1264, ptr %1265, align 4
  %screenWidth223 = load i32, ptr @screenWidth, align 4
  %1266 = load i32, ptr @screenWidth, align 4
  %1267 = sitofp i32 %1266 to double
  %1268 = fdiv double %1267, 2.000000e+00
  %1269 = alloca double, align 8
  store double %1268, ptr %1269, align 8
  %1270 = load double, ptr %1269, align 8
  %1271 = fptosi double %1270 to i32
  %1272 = alloca i32, align 4
  store i32 %1271, ptr %1272, align 4
  call void @getRandomNumber(ptr %rtPtr221, ptr %1265, ptr %1272)
  %1273 = load i32, ptr %rtPtr221, align 4
  %1274 = sub i32 %1258, %1273
  %1275 = alloca i32, align 4
  store i32 %1274, ptr %1275, align 4
  %1276 = load i32, ptr %1275, align 4
  %1277 = sitofp i32 %1276 to float
  store float %1277, ptr %1254, align 4
  %1278 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1279 = icmp eq i32 %1278, 0
  br i1 %1279, label %checkContinueBlock218, label %afterNestedBlock216

checkContinueBlock218:                            ; preds = %nestedBlock217
  br label %afterNestedBlock216

then227:                                          ; preds = %nestedBlock103
  br label %nestedBlock231

else228:                                          ; preds = %nestedBlock103
  br label %afterIfElse229

afterIfElse229:                                   ; preds = %else228, %afterNestedBlock230
  %1280 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1281 = icmp eq i32 %1280, 0
  br i1 %1281, label %checkContinueBlock104, label %afterNestedBlock92

afterNestedBlock230:                              ; preds = %checkContinueBlock232, %nestedBlock231
  br label %afterIfElse229

nestedBlock231:                                   ; preds = %then227
  %1282 = getelementptr inbounds %Bird, ptr %67, i32 0, i32 0
  %1283 = load ptr, ptr %1282, align 8
  %1284 = getelementptr inbounds %"Bird::VTableType", ptr %1283, i32 0, i32 8
  %1285 = load ptr, ptr %1284, align 8
  %1286 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %1287 = load ptr, ptr %1286, align 8
  %1288 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %1287, i32 0, i32 8
  %1289 = load ptr, ptr %1288, align 8
  %rtPtr233 = alloca float, align 4
  call void %1289(ptr %rtPtr233, ptr %1)
  call void %1285(ptr %rtPtr233, ptr %67)
  %1290 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1291 = icmp eq i32 %1290, 0
  br i1 %1291, label %checkContinueBlock232, label %afterNestedBlock230

checkContinueBlock232:                            ; preds = %nestedBlock231
  br label %afterNestedBlock230

decrement_block288:                               ; preds = %while.end
  %1292 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1293 = sub i32 %1292, 1
  store i32 %1293, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block289

end_block289:                                     ; preds = %decrement_block288, %while.end
  %1294 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1295 = icmp eq i32 %1294, 0
  br i1 %1295, label %checkContinueBlock36, label %afterNestedBlock

returnBlock290:                                   ; preds = %nestedBlock39
  store i32 0, ptr %0, align 4
  ret void

mergeBlock291:                                    ; No predecessors!
  %1296 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1297 = icmp eq i32 %1296, 0
  br i1 %1297, label %checkContinueBlock40, label %afterNestedBlock
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
!25 = !{!"drawTexturePro:rt:pr:27"}
!26 = !{!"SetTargetFPS:rt:pr:27"}
!27 = !{!"getRandomNumber:rt:pr:28"}
!28 = !{!"ClearBackground:rt:pr:27"}
!29 = !{!"DrawTexturePro:rt:pr:27"}
!30 = !{!"TraceLog:rt:pr:27"}
!31 = !{!"GetScreenWidth:rt:pr:28"}
!32 = !{!"DrawCircle:rt:pr:27"}
!33 = !{!"time:rt:pr:28"}
!34 = !{!"BeginDrawing:rt:pr:27"}
!35 = !{!"IsKeyPressed:rt:pr:34"}
!36 = !{!"WindowShouldClose:rt:pr:34"}
!37 = !{!"InitWindow:rt:pr:27"}
!38 = !{!"EndDrawing:rt:pr:27"}
!39 = !{!"CloseWindow:rt:pr:27"}
!40 = !{!"GetScreenHeight:rt:pr:28"}
!41 = !{!"GetFrameTime:rt:pr:32"}
!42 = !{!"DrawText:rt:pr:27"}
!43 = !{!"GetTime:rt:pr:31"}
!44 = !{!"UnloadTexture:rt:pr:27"}
!45 = !{!"TextFormat:rt:pr:33"}
!46 = !{!"LoadTexture:rt:ob:Texture"}
!47 = !{!"IsKeyDown:rt:pr:34"}
!48 = !{!"DrawRectangle:rt:pr:27"}
!49 = !{!"DrawTexture:rt:pr:27"}
!50 = !{!"srand:rt:pr:27"}
!51 = !{!"rand:rt:pr:28"}
!52 = !{!"Bird.init1:rt:pr:27"}
!53 = !{!"Bird.setTexture:rt:pr:27"}
!54 = !{!"Bird.getTexturePath:rt:pr:33"}
!55 = !{!"Bird.update:rt:pr:27"}
!56 = !{!"Bird.isTextureLoaded:rt:pr:34"}
!57 = !{!"Bird.getSource:rt:ay:32:sz:4:"}
!58 = !{!"Bird.getDistination:rt:ay:32:sz:4:"}
!59 = !{!"Bird.getOrigin:rt:ay:32:sz:2:"}
!60 = !{!"Bird.getRotation:rt:pr:32"}
!61 = !{!"Bird.getTexture:rt:ob:Texture"}
!62 = !{!"Bird.updateY:rt:pr:27"}
!63 = !{!"Cloud.init1:rt:pr:27"}
!64 = !{!"Cloud.setTexture:rt:pr:27"}
!65 = !{!"Cloud.getTexture:rt:ob:Texture"}
!66 = !{!"Cloud.getTexturePath:rt:pr:33"}
!67 = !{!"Cloud.update:rt:pr:27"}
!68 = !{!"Cloud.draw:rt:pr:27"}
!69 = !{!"main:rt:pr:28"}
!70 = !{!"4:"}
!71 = !{!"32"}
!72 = !{!"2:"}
