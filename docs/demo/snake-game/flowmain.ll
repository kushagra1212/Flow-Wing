; ModuleID = 'flowmain'
source_filename = "flowmain"
target triple = "x86_64-apple-macosx14.0.0"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%"Bird::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%Bird = type { ptr, float, float, double, double, i32, i32, ptr, i1, %Texture.0, [9 x %Position.4], %Position.4 }
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
@0 = private unnamed_addr constant [875 x i8] c"\0A\1B[33m80| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m84| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 84:32\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@1 = private unnamed_addr constant [953 x i8] c"\0A\1B[33m80| \1B[0m\1B[0m    return self.birdTexture.id != 0\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m82| \1B[0m\1B[0m\0A\1B[0m\1B[33m83| \1B[0m\1B[0m  getSource() -> deci32[4] {\0A\1B[0m\1B[33m84| \1B[0m\1B[31m\1B[1m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[32m\1B[1m                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 84:71\1B[31m \22Index out of bounds of 'birdSpritePosition' in index expression, index value should be between 0 and 9\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [814 x i8] c"\0A\1B[33m84| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                     \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m89| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m90| \1B[0m\1B[0m\0A\1B[0m\1B[33m91| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    return [self.pos.x, self.pos.y]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 88:37\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [855 x i8] c"\0A\1B[33m84| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m89| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m90| \1B[0m\1B[0m\0A\1B[0m\1B[33m91| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    return [self.pos.x, self.pos.y]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 88:50\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [902 x i8] c"\0A\1B[33m84| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                                                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m89| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m90| \1B[0m\1B[0m\0A\1B[0m\1B[33m91| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    return [self.pos.x, self.pos.y]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 88:81\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [943 x i8] c"\0A\1B[33m84| \1B[0m\1B[0m    return [birdSpritePosition[birdSpriteIndex].x, birdSpritePosition[birdSpriteIndex].y, ACTUAL_BIRD_SIZE, ACTUAL_BIRD_SIZE]\0A\1B[0m\1B[33m85| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[33m87| \1B[0m\1B[0m  getDistination() -> deci32[4] {\0A\1B[0m\1B[33m88| \1B[0m\1B[31m\1B[1m    return [Decimal32(screenWidth / 3 - birdSize / 2), Decimal32(screenHeight / 2 - birdSize / 2), birdSize, birdSize]\0A\1B[0m\1B[32m\1B[1m                                                                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m89| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m90| \1B[0m\1B[0m\0A\1B[0m\1B[33m91| \1B[0m\1B[0m  getOrigin() -> deci32[2] {\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    return [self.pos.x, self.pos.y]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 88:94\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@11 = private unnamed_addr constant [685 x i8] c"\0A\1B[33m10| \1B[0m\1B[0m}\0A\1B[0m\1B[33m11| \1B[0m\1B[0mclass Bird {\0A\1B[0m\1B[33m12| \1B[0m\1B[0m  const ACTUAL_BIRD_SIZE: deci32 = 360.0d\0A\1B[0m\1B[33m13| \1B[0m\1B[0m  var birdSize: deci32 = 90.0d\0A\1B[0m\1B[33m14| \1B[0m\1B[31m\1B[1m  var BIRD_TIMMER: deci = 5 / FPS\0A\1B[0m\1B[32m\1B[1m                               \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m15| \1B[0m\1B[0m  var birdTimmer: deci   \0A\1B[0m\1B[33m16| \1B[0m\1B[0m  const BIRD_SPRITE_SIZE:int = 9\0A\1B[0m\1B[33m17| \1B[0m\1B[0m  var birdSpriteIndex:int = 0\0A\1B[0m\1B[33m18| \1B[0m\1B[0m  var birdTexturePath:str\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 14:31\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [18 x i8] c"./assets/bird.png\00", align 1
@13 = private unnamed_addr constant [18 x i8] c"./assets/bird.png\00", align 1
@14 = private unnamed_addr constant [27 x i8] c"./assets/skyBackground.png\00", align 1
@15 = private unnamed_addr constant [21 x i8] c"./assets/3clouds.png\00", align 1
@16 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL1.png\00", align 1
@17 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL2.png\00", align 1
@18 = private unnamed_addr constant [31 x i8] c"./assets/mountain/2mountL2.png\00", align 1
@19 = private unnamed_addr constant [31 x i8] c"./assets/mountain/1mountL3.png\00", align 1
@20 = private unnamed_addr constant [1085 x i8] c"\0A\1B[33m117| \1B[0m\1B[0m  var mountL2Texture:Texture = fgAnim.loadTexture(\22./assets/mountain/1mountL2.png\22)\0A\1B[0m\1B[33m118| \1B[0m\1B[0m  var mount2L2Texture:Texture = fgAnim.loadTexture(\22./assets/mountain/2mountL2.png\22)\0A\1B[0m\1B[33m119| \1B[0m\1B[0m  var mount1L3Texture:Texture = fgAnim.loadTexture(\22./assets/mountain/1mountL3.png\22)\0A\1B[0m\1B[33m120| \1B[0m\1B[0m\0A\1B[0m\1B[33m121| \1B[0m\1B[31m\1B[1m  var mountL1Pos1:Position = {x:Decimal32(screenWidth/4),y:0.0d}\0A\1B[0m\1B[32m\1B[1m                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m122| \1B[0m\1B[0m  var mountL1Pos2:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m123| \1B[0m\1B[0m\0A\1B[0m\1B[33m124| \1B[0m\1B[0m  var mountL2Pos1:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m125| \1B[0m\1B[0m  var mount2L2Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2))),y:0.0d}\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 121:55\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@21 = private unnamed_addr constant [1146 x i8] c"\0A\1B[33m121| \1B[0m\1B[0m  var mountL1Pos1:Position = {x:Decimal32(screenWidth/4),y:0.0d}\0A\1B[0m\1B[33m122| \1B[0m\1B[0m  var mountL1Pos2:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m123| \1B[0m\1B[0m\0A\1B[0m\1B[33m124| \1B[0m\1B[0m  var mountL2Pos1:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m125| \1B[0m\1B[31m\1B[1m  var mount2L2Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2))),y:0.0d}\0A\1B[0m\1B[32m\1B[1m                                                                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m126| \1B[0m\1B[0m  var mount1L3Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth))),y:0.0d}\0A\1B[0m\1B[33m127| \1B[0m\1B[0m\0A\1B[0m\1B[33m128| \1B[0m\1B[0m  if !bird.isTextureLoaded() || backgroundTexture.id == 0 {/; If any texture failed to load, print error and exit\0A\1B[0m\1B[33m129| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 125:93\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@22 = private unnamed_addr constant [1189 x i8] c"\0A\1B[33m121| \1B[0m\1B[0m  var mountL1Pos1:Position = {x:Decimal32(screenWidth/4),y:0.0d}\0A\1B[0m\1B[33m122| \1B[0m\1B[0m  var mountL1Pos2:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m123| \1B[0m\1B[0m\0A\1B[0m\1B[33m124| \1B[0m\1B[0m  var mountL2Pos1:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m125| \1B[0m\1B[31m\1B[1m  var mount2L2Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2))),y:0.0d}\0A\1B[0m\1B[32m\1B[1m                                                                                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m126| \1B[0m\1B[0m  var mount1L3Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth))),y:0.0d}\0A\1B[0m\1B[33m127| \1B[0m\1B[0m\0A\1B[0m\1B[33m128| \1B[0m\1B[0m  if !bird.isTextureLoaded() || backgroundTexture.id == 0 {/; If any texture failed to load, print error and exit\0A\1B[0m\1B[33m129| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 125:114\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@23 = private unnamed_addr constant [1170 x i8] c"\0A\1B[33m122| \1B[0m\1B[0m  var mountL1Pos2:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m123| \1B[0m\1B[0m\0A\1B[0m\1B[33m124| \1B[0m\1B[0m  var mountL2Pos1:Position = {x:Decimal32(-1*screenWidth),y:0.0d}\0A\1B[0m\1B[33m125| \1B[0m\1B[0m  var mount2L2Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2))),y:0.0d}\0A\1B[0m\1B[33m126| \1B[0m\1B[31m\1B[1m  var mount1L3Pos1:Position = {x:Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth))),y:0.0d}\0A\1B[0m\1B[32m\1B[1m                                                                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m127| \1B[0m\1B[0m\0A\1B[0m\1B[33m128| \1B[0m\1B[0m  if !bird.isTextureLoaded() || backgroundTexture.id == 0 {/; If any texture failed to load, print error and exit\0A\1B[0m\1B[33m129| \1B[0m\1B[0m\0A\1B[0m\1B[33m130| \1B[0m\1B[0m    fgAnim.traceLog(fgAnim.LOG.ERROR, \22Failed to load bird texture\22)/; Clean up and exit\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 126:93\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@24 = private unnamed_addr constant [28 x i8] c"Failed to load bird texture\00", align 1
@25 = private unnamed_addr constant [797 x i8] c"\0A\1B[33m140| \1B[0m\1B[0m    {\0A\1B[0m\1B[33m141| \1B[0m\1B[0m      mountL1Pos1.x = mountL1Pos1.x + fgAnim.getFrameTime()*60\0A\1B[0m\1B[33m142| \1B[0m\1B[0m      mountL1Pos2.x = mountL1Pos2.x + fgAnim.getFrameTime()*60\0A\1B[0m\1B[33m143| \1B[0m\1B[0m\0A\1B[0m\1B[33m144| \1B[0m\1B[31m\1B[1m      if mountL1Pos1.x > screenWidth+screenWidth/2 {\0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m145| \1B[0m\1B[0m        mountL1Pos1.x = Decimal32(-1*screenWidth)\0A\1B[0m\1B[33m146| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m147| \1B[0m\1B[0m\0A\1B[0m\1B[33m148| \1B[0m\1B[0m    if mountL1Pos2.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 144:50\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@26 = private unnamed_addr constant [722 x i8] c"\0A\1B[33m144| \1B[0m\1B[0m      if mountL1Pos1.x > screenWidth+screenWidth/2 {\0A\1B[0m\1B[33m145| \1B[0m\1B[0m        mountL1Pos1.x = Decimal32(-1*screenWidth)\0A\1B[0m\1B[33m146| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m147| \1B[0m\1B[0m\0A\1B[0m\1B[33m148| \1B[0m\1B[31m\1B[1m    if mountL1Pos2.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[32m\1B[1m                                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m149| \1B[0m\1B[0m      mountL2Pos1.x =Decimal32(-1*screenWidth)\0A\1B[0m\1B[33m150| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m151| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m152| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 148:49\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@27 = private unnamed_addr constant [688 x i8] c"\0A\1B[33m153| \1B[0m\1B[0m    {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m\0A\1B[0m\1B[33m155| \1B[0m\1B[0m      mountL2Pos1.x = mountL2Pos1.x + fgAnim.getFrameTime()*20\0A\1B[0m\1B[33m156| \1B[0m\1B[0m\0A\1B[0m\1B[33m157| \1B[0m\1B[31m\1B[1m     if mountL2Pos1.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m158| \1B[0m\1B[0m        mountL2Pos1.x =Decimal32(-1*screenWidth)\0A\1B[0m\1B[33m159| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m160| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m161| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 157:50\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@28 = private unnamed_addr constant [752 x i8] c"\0A\1B[33m162| \1B[0m\1B[0m    {\0A\1B[0m\1B[33m163| \1B[0m\1B[0m\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      mount2L2Pos1.x = mount2L2Pos1.x + fgAnim.getFrameTime()*10\0A\1B[0m\1B[33m165| \1B[0m\1B[0m\0A\1B[0m\1B[33m166| \1B[0m\1B[31m\1B[1m     if mount2L2Pos1.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[32m\1B[1m                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m167| \1B[0m\1B[0m        mount2L2Pos1.x = Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth)))\0A\1B[0m\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m170| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 166:51\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@29 = private unnamed_addr constant [815 x i8] c"\0A\1B[33m163| \1B[0m\1B[0m\0A\1B[0m\1B[33m164| \1B[0m\1B[0m      mount2L2Pos1.x = mount2L2Pos1.x + fgAnim.getFrameTime()*10\0A\1B[0m\1B[33m165| \1B[0m\1B[0m\0A\1B[0m\1B[33m166| \1B[0m\1B[0m     if mount2L2Pos1.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[33m167| \1B[0m\1B[31m\1B[1m        mount2L2Pos1.x = Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth)))\0A\1B[0m\1B[32m\1B[1m                                                                                     \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m168| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m169| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m170| \1B[0m\1B[0m\0A\1B[0m\1B[33m171| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 167:85\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@30 = private unnamed_addr constant [757 x i8] c"\0A\1B[33m172| \1B[0m\1B[0m        {\0A\1B[0m\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m      mount1L3Pos1.x = mount1L3Pos1.x + fgAnim.getFrameTime()*5\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[31m\1B[1m     if mount1L3Pos1.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[32m\1B[1m                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m177| \1B[0m\1B[0m        mount1L3Pos1.x = Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2)))\0A\1B[0m\1B[33m178| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m179| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m180| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 176:51\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@31 = private unnamed_addr constant [906 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m      mount1L3Pos1.x = mount1L3Pos1.x + fgAnim.getFrameTime()*5\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m     if mount1L3Pos1.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m        mount1L3Pos1.x = Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2)))\0A\1B[0m\1B[32m\1B[1m                                                                                     \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m179| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m180| \1B[0m\1B[0m\0A\1B[0m\1B[33m181| \1B[0m\1B[0m    if (fgAnim.isKeyPressed(fgAnim.KEYS.KEY_UP) || fgAnim.isKeyDown(fgAnim.KEYS.KEY_UP)) {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:85\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@32 = private unnamed_addr constant [949 x i8] c"\0A\1B[33m173| \1B[0m\1B[0m\0A\1B[0m\1B[33m174| \1B[0m\1B[0m      mount1L3Pos1.x = mount1L3Pos1.x + fgAnim.getFrameTime()*5\0A\1B[0m\1B[33m175| \1B[0m\1B[0m\0A\1B[0m\1B[33m176| \1B[0m\1B[0m     if mount1L3Pos1.x >  screenWidth+screenWidth/2     {\0A\1B[0m\1B[33m177| \1B[0m\1B[31m\1B[1m        mount1L3Pos1.x = Decimal32(-1*screenWidth-getRandomNumber(Int32(screenWidth/4),Int32(screenWidth/2)))\0A\1B[0m\1B[32m\1B[1m                                                                                                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m178| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m179| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m180| \1B[0m\1B[0m\0A\1B[0m\1B[33m181| \1B[0m\1B[0m    if (fgAnim.isKeyPressed(fgAnim.KEYS.KEY_UP) || fgAnim.isKeyDown(fgAnim.KEYS.KEY_UP)) {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 177:106\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@33 = private unnamed_addr constant [1228 x i8] c"\0A\1B[33m186| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m187| \1B[0m\1B[0m    fgAnim.drawTexturePro(backgroundTexture,[0.0d,0.0d,3840.0d,2160.0d],[0.0d,0.0d,Decimal32(screenWidth),Decimal32(screenHeight)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m188| \1B[0m\1B[0m\0A\1B[0m\1B[33m189| \1B[0m\1B[0m    /; Cloud\0A\1B[0m\1B[33m190| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(cloudTexture,[0.0d,0.0d,1280.0d,720.0d],[0.0d,0.0d,Decimal32((1280)/(720)*screenHeight/2),Decimal32(screenHeight/2)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m191| \1B[0m\1B[0m\0A\1B[0m\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 190:96\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@34 = private unnamed_addr constant [1278 x i8] c"\0A\1B[33m186| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m187| \1B[0m\1B[0m    fgAnim.drawTexturePro(backgroundTexture,[0.0d,0.0d,3840.0d,2160.0d],[0.0d,0.0d,Decimal32(screenWidth),Decimal32(screenHeight)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m188| \1B[0m\1B[0m\0A\1B[0m\1B[33m189| \1B[0m\1B[0m    /; Cloud\0A\1B[0m\1B[33m190| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(cloudTexture,[0.0d,0.0d,1280.0d,720.0d],[0.0d,0.0d,Decimal32((1280)/(720)*screenHeight/2),Decimal32(screenHeight/2)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m191| \1B[0m\1B[0m\0A\1B[0m\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 190:113\1B[31m \22Floating point division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@35 = private unnamed_addr constant [1317 x i8] c"\0A\1B[33m186| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m187| \1B[0m\1B[0m    fgAnim.drawTexturePro(backgroundTexture,[0.0d,0.0d,3840.0d,2160.0d],[0.0d,0.0d,Decimal32(screenWidth),Decimal32(screenHeight)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m188| \1B[0m\1B[0m\0A\1B[0m\1B[33m189| \1B[0m\1B[0m    /; Cloud\0A\1B[0m\1B[33m190| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(cloudTexture,[0.0d,0.0d,1280.0d,720.0d],[0.0d,0.0d,Decimal32((1280)/(720)*screenHeight/2),Decimal32(screenHeight/2)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m191| \1B[0m\1B[0m\0A\1B[0m\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 190:140\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@36 = private unnamed_addr constant [1247 x i8] c"\0A\1B[33m189| \1B[0m\1B[0m    /; Cloud\0A\1B[0m\1B[33m190| \1B[0m\1B[0m    fgAnim.drawTexturePro(cloudTexture,[0.0d,0.0d,1280.0d,720.0d],[0.0d,0.0d,Decimal32((1280)/(720)*screenHeight/2),Decimal32(screenHeight/2)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m191| \1B[0m\1B[0m\0A\1B[0m\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 193:99\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@37 = private unnamed_addr constant [1298 x i8] c"\0A\1B[33m189| \1B[0m\1B[0m    /; Cloud\0A\1B[0m\1B[33m190| \1B[0m\1B[0m    fgAnim.drawTexturePro(cloudTexture,[0.0d,0.0d,1280.0d,720.0d],[0.0d,0.0d,Decimal32((1280)/(720)*screenHeight/2),Decimal32(screenHeight/2)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m191| \1B[0m\1B[0m\0A\1B[0m\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 193:124\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@38 = private unnamed_addr constant [1350 x i8] c"\0A\1B[33m189| \1B[0m\1B[0m    /; Cloud\0A\1B[0m\1B[33m190| \1B[0m\1B[0m    fgAnim.drawTexturePro(cloudTexture,[0.0d,0.0d,1280.0d,720.0d],[0.0d,0.0d,Decimal32((1280)/(720)*screenHeight/2),Decimal32(screenHeight/2)],[0.0d,0.0d],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m191| \1B[0m\1B[0m\0A\1B[0m\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                      \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 193:150\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@39 = private unnamed_addr constant [1285 x i8] c"\0A\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 196:100\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@40 = private unnamed_addr constant [1335 x i8] c"\0A\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 196:125\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@41 = private unnamed_addr constant [1387 x i8] c"\0A\1B[33m192| \1B[0m\1B[0m    /; mount1L2 \0A\1B[0m\1B[33m193| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL2Texture,[0.0d,0.0d,5975.0d,1607.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mountL2Pos1.x,mountL2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m194| \1B[0m\1B[0m\0A\1B[0m\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 196:151\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@42 = private unnamed_addr constant [1516 x i8] c"\0A\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m203| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 199:100\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@43 = private unnamed_addr constant [1566 x i8] c"\0A\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m203| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 199:125\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@44 = private unnamed_addr constant [1618 x i8] c"\0A\1B[33m195| \1B[0m\1B[0m    /; 2mount1L2 \0A\1B[0m\1B[33m196| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,4461.0d,1989.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount2L2Pos1.x,mount2L2Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m197| \1B[0m\1B[0m\0A\1B[0m\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m203| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 199:151\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@45 = private unnamed_addr constant [1429 x i8] c"\0A\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m203| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m204| \1B[0m\1B[0m\0A\1B[0m\1B[33m205| \1B[0m\1B[0m\0A\1B[0m\1B[33m206| \1B[0m\1B[0m    fgAnim.drawTexturePro(bird.getTexture(), bird.getSource(), bird.getDistination(), bird.getOrigin(), bird.getRotation(), fgAnim.colors.WHITE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 202:99\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@46 = private unnamed_addr constant [1504 x i8] c"\0A\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m203| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m204| \1B[0m\1B[0m\0A\1B[0m\1B[33m205| \1B[0m\1B[0m\0A\1B[0m\1B[33m206| \1B[0m\1B[0m    fgAnim.drawTexturePro(bird.getTexture(), bird.getSource(), bird.getDistination(), bird.getOrigin(), bird.getRotation(), fgAnim.colors.WHITE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 202:136\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@47 = private unnamed_addr constant [1556 x i8] c"\0A\1B[33m198| \1B[0m\1B[0m    /; 1mount1L3\0A\1B[0m\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m203| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m204| \1B[0m\1B[0m\0A\1B[0m\1B[33m205| \1B[0m\1B[0m\0A\1B[0m\1B[33m206| \1B[0m\1B[0m    fgAnim.drawTexturePro(bird.getTexture(), bird.getSource(), bird.getDistination(), bird.getOrigin(), bird.getRotation(), fgAnim.colors.WHITE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 202:162\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@48 = private unnamed_addr constant [1417 x i8] c"\0A\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m203| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m204| \1B[0m\1B[0m\0A\1B[0m\1B[33m205| \1B[0m\1B[0m\0A\1B[0m\1B[33m206| \1B[0m\1B[0m    fgAnim.drawTexturePro(bird.getTexture(), bird.getSource(), bird.getDistination(), bird.getOrigin(), bird.getRotation(), fgAnim.colors.WHITE)\0A\1B[0m\1B[33m207| \1B[0m\1B[0m    \0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 203:99\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@49 = private unnamed_addr constant [1492 x i8] c"\0A\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m203| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m204| \1B[0m\1B[0m\0A\1B[0m\1B[33m205| \1B[0m\1B[0m\0A\1B[0m\1B[33m206| \1B[0m\1B[0m    fgAnim.drawTexturePro(bird.getTexture(), bird.getSource(), bird.getDistination(), bird.getOrigin(), bird.getRotation(), fgAnim.colors.WHITE)\0A\1B[0m\1B[33m207| \1B[0m\1B[0m    \0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 203:136\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@50 = private unnamed_addr constant [1544 x i8] c"\0A\1B[33m199| \1B[0m\1B[0m    fgAnim.drawTexturePro(mount2L2Texture,[0.0d,0.0d,6005.0d,2376.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth/2),Decimal32(screenHeight/5)],[mount1L3Pos1.x,mount1L3Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m200| \1B[0m\1B[0m\0A\1B[0m\1B[33m201| \1B[0m\1B[0m    /; muont1L1\0A\1B[0m\1B[33m202| \1B[0m\1B[0m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos1.x,mountL1Pos1.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[33m203| \1B[0m\1B[31m\1B[1m    fgAnim.drawTexturePro(mountL1Texture,[0.0d,0.0d,8982.0d,1542.0d],[0.0d,Decimal32(screenHeight/2),Decimal32(screenWidth+screenWidth/2),Decimal32(screenHeight/5)],[mountL1Pos2.x,mountL1Pos2.y],0.0d,fgAnim.colors.WHITE)\0A\1B[0m\1B[32m\1B[1m                                                                                                                                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m204| \1B[0m\1B[0m\0A\1B[0m\1B[33m205| \1B[0m\1B[0m\0A\1B[0m\1B[33m206| \1B[0m\1B[0m    fgAnim.drawTexturePro(bird.getTexture(), bird.getSource(), bird.getDistination(), bird.getOrigin(), bird.getRotation(), fgAnim.colors.WHITE)\0A\1B[0m\1B[33m207| \1B[0m\1B[0m    \0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 203:162\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1

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
  store i32 60, ptr @FPS, align 4
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

declare !rt !24 void @FlowWingAnim.textFormat.1(ptr, ptr, ptr)

declare !rt !22 void @FlowWingAnim.isKeyPressed.2(ptr, ptr, ptr)

declare !rt !21 void @FlowWingAnim.unloadTexture.3(ptr, ptr)

declare !rt !20 void @FlowWingAnim.loadTexture.4(ptr, ptr, ptr)

declare !rt !8 void @FlowWingAnim.drawRectangle.5(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !4 void @FlowWingAnim.createWindow.6(ptr)

declare !rt !19 void @FlowWingAnim.traceLog.7(ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.drawText.8(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !25 void @SetTargetFPS(i32)

declare !rt !7 void @FlowWingAnim.beginDrawing.9(ptr)

declare !rt !15 void @FlowWingAnim.drawCircle.10(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.getScreenWidth.11(ptr, ptr)

declare !rt !26 void @getRandomNumber(ptr, ptr, ptr)

declare !rt !1 void @FlowWingAnim.beforeInit.12(ptr)

declare !rt !13 void @FlowWingAnim.getScreenHeight.13(ptr, ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.14(ptr)

declare !rt !9 void @FlowWingAnim.endDrawing.15(ptr)

declare !rt !3 void @FlowWingAnim.getColor.16(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.17(ptr)

declare !rt !0 void @FlowWingAnim.init4.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !27 void @ClearBackground(i32)

declare !rt !28 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !12 void @FlowWingAnim.getFrameTime.19(ptr, ptr)

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

declare !rt !23 void @FlowWingAnim.isKeyDown.22(ptr, ptr, ptr)

declare !rt !45 void @LoadTexture(ptr sret, ptr)

declare !rt !46 i1 @IsKeyDown(i32)

declare !rt !6 void @FlowWingAnim.windowShouldClose.23(ptr, ptr)

declare !rt !47 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !48 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !49 void @srand(i32)

declare !rt !11 void @FlowWingAnim.getTime.24(ptr, ptr)

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

define void @Bird.getTexturePath(ptr %0, ptr %1) !rt !53 {
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
  %15 = fpext float %frameTime4 to double
  %16 = fsub double %14, %15
  store double %16, ptr %5, align 8
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %birdTimmer5 = load double, ptr %5, align 8
  %21 = load double, ptr %5, align 8
  %22 = fcmp olt double %21, 0.000000e+00
  br i1 %22, label %then, label %else

checkContinueBlock2:                              ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock1
  br label %nestedBlock7

else:                                             ; preds = %nestedBlock1
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock6
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock2, label %afterNestedBlock

afterNestedBlock6:                                ; preds = %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %afterIfElse20, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7
  br label %afterIfElse

nestedBlock7:                                     ; preds = %then
  %birdTimmer15 = load double, ptr %5, align 8
  %BIRD_TIMMER = load double, ptr %4, align 8
  %25 = load double, ptr %4, align 8
  store double %25, ptr %5, align 8
  %26 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock8, label %afterNestedBlock6

checkContinueBlock8:                              ; preds = %nestedBlock7
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock9, label %afterNestedBlock6

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %birdSpriteIndex = load i32, ptr %7, align 4
  %birdSpriteIndex16 = load i32, ptr %7, align 4
  %30 = load i32, ptr %7, align 4
  %31 = add i32 %30, 1
  store i32 %31, ptr %7, align 4
  %32 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %checkContinueBlock10, label %afterNestedBlock6

checkContinueBlock10:                             ; preds = %nestedBlock9
  %34 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %nestedBlock11, label %afterNestedBlock6

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %birdSpriteIndex17 = load i32, ptr %7, align 4
  %36 = load i32, ptr %7, align 4
  %BIRD_SPRITE_SIZE = load i32, ptr %6, align 4
  %37 = load i32, ptr %6, align 4
  %38 = icmp sge i32 %36, %37
  br i1 %38, label %then18, label %else19

checkContinueBlock12:                             ; preds = %afterIfElse20
  %39 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock13, label %afterNestedBlock6

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %41 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y = load float, ptr %41, align 4
  %42 = getelementptr inbounds %Position.4, ptr %12, i32 0, i32 1
  %y25 = load float, ptr %42, align 4
  %43 = load float, ptr %42, align 4
  %frameTime26 = load float, ptr %frameTime, align 4
  %44 = load float, ptr %frameTime, align 4
  %45 = fmul float %44, -1.490000e+02
  %46 = fadd float %43, %45
  store float %46, ptr %41, align 4
  %47 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %checkContinueBlock14, label %afterNestedBlock6

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock6

then18:                                           ; preds = %nestedBlock11
  br label %nestedBlock22

else19:                                           ; preds = %nestedBlock11
  br label %afterIfElse20

afterIfElse20:                                    ; preds = %else19, %afterNestedBlock21
  %49 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %checkContinueBlock12, label %afterNestedBlock6

afterNestedBlock21:                               ; preds = %checkContinueBlock23, %nestedBlock22
  br label %afterIfElse20

nestedBlock22:                                    ; preds = %then18
  %birdSpriteIndex24 = load i32, ptr %7, align 4
  store i32 0, ptr %7, align 4
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock23, label %afterNestedBlock21

checkContinueBlock23:                             ; preds = %nestedBlock22
  br label %afterNestedBlock21
}

define void @Bird.isTextureLoaded(ptr %0, ptr %1) !rt !55 {
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
  br i1 false, label %if, label %else

mergeBlock:                                       ; No predecessors!
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

if:                                               ; preds = %returnBlock
  call void @raise_exception(ptr @2)
  br label %merge

else:                                             ; preds = %returnBlock
  %17 = sitofp i32 %14 to double
  %18 = fdiv double %17, 3.000000e+00
  br label %merge

merge:                                            ; preds = %else, %if
  %birdSize = load float, ptr %3, align 4
  %19 = load float, ptr %3, align 4
  br i1 false, label %if1, label %else2

if1:                                              ; preds = %merge
  call void @raise_exception(ptr @3)
  br label %else2

else2:                                            ; preds = %if1, %merge
  %20 = fdiv float %19, 2.000000e+00
  %21 = fptrunc double %18 to float
  %22 = fsub float %21, %20
  store float %22, ptr %13, align 4
  %23 = getelementptr [4 x float], ptr %0, i32 0, i32 1
  %screenHeight = load i32, ptr @screenHeight, align 4
  %24 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if3, label %else4

if3:                                              ; preds = %else2
  call void @raise_exception(ptr @4)
  br label %merge5

else4:                                            ; preds = %else2
  %25 = sitofp i32 %24 to double
  %26 = fdiv double %25, 2.000000e+00
  br label %merge5

merge5:                                           ; preds = %else4, %if3
  %birdSize6 = load float, ptr %3, align 4
  %27 = load float, ptr %3, align 4
  br i1 false, label %if7, label %else8

if7:                                              ; preds = %merge5
  call void @raise_exception(ptr @5)
  br label %else8

else8:                                            ; preds = %if7, %merge5
  %28 = fdiv float %27, 2.000000e+00
  %29 = fptrunc double %26 to float
  %30 = fsub float %29, %28
  store float %30, ptr %23, align 4
  %31 = getelementptr [4 x float], ptr %0, i32 0, i32 2
  %birdSize9 = load float, ptr %3, align 4
  %32 = load float, ptr %3, align 4
  store float %32, ptr %31, align 4
  %33 = getelementptr [4 x float], ptr %0, i32 0, i32 3
  %birdSize10 = load float, ptr %3, align 4
  %34 = load float, ptr %3, align 4
  store float %34, ptr %33, align 4
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

define void @Bird.getRotation(ptr %0, ptr %1) !rt !59 {
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

define void @Bird.updateY(ptr %0, ptr %1) !rt !61 {
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

define void @main(ptr %0) !rt !62 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock36, %mergeBlock453, %checkContinueBlock34, %nestedBlock33, %checkContinueBlock32, %end_block451, %checkContinueBlock30, %afterIfElse, %checkContinueBlock28, %merge65, %checkContinueBlock26, %merge59, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %merge47, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %merge, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %1 = call ptr @malloc(i64 96)
  %2 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  store ptr @6, ptr %2, align 8
  %3 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 1
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 2
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 3
  store ptr @7, ptr %5, align 8
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
  store ptr @8, ptr %53, align 8
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
  %59 = call ptr @malloc(i64 152)
  %60 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  store ptr @9, ptr %60, align 8
  %61 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 1
  store float 0.000000e+00, ptr %61, align 4
  %62 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 2
  store float 0.000000e+00, ptr %62, align 4
  %63 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 3
  store double 0.000000e+00, ptr %63, align 8
  %64 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 4
  store double 0.000000e+00, ptr %64, align 8
  %65 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 5
  store i32 0, ptr %65, align 4
  %66 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 6
  store i32 0, ptr %66, align 4
  %67 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 7
  store ptr @10, ptr %67, align 8
  %68 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 8
  store i1 false, ptr %68, align 1
  %69 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 9
  %70 = getelementptr inbounds %Texture.0, ptr %69, i32 0, i32 0
  store i32 0, ptr %70, align 4
  %71 = getelementptr inbounds %Texture.0, ptr %69, i32 0, i32 1
  store i32 0, ptr %71, align 4
  %72 = getelementptr inbounds %Texture.0, ptr %69, i32 0, i32 2
  store i32 0, ptr %72, align 4
  %73 = getelementptr inbounds %Texture.0, ptr %69, i32 0, i32 3
  store i32 0, ptr %73, align 4
  %74 = getelementptr inbounds %Texture.0, ptr %69, i32 0, i32 4
  store i32 0, ptr %74, align 4
  %75 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 10
  %76 = alloca i32, align 4
  %77 = alloca i32, align 4
  store i32 0, ptr %77, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock2:                              ; preds = %merge
  %78 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %80 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %81 = load ptr, ptr %80, align 8
  %82 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %81, i32 0, i32 21
  %83 = load ptr, ptr %82, align 8
  call void %83(ptr %1)
  %84 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %85 = icmp eq i32 %84, 0
  br i1 %85, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %86 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %88 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %89 = load ptr, ptr %88, align 8
  %90 = getelementptr inbounds %"Bird::VTableType", ptr %89, i32 0, i32 9
  %91 = load ptr, ptr %90, align 8
  %92 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %93 = load ptr, ptr %92, align 8
  %94 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %93, i32 0, i32 9
  %95 = load ptr, ptr %94, align 8
  %rtPtr = alloca %Texture.0, align 8
  %96 = alloca ptr, align 8
  store ptr @13, ptr %96, align 8
  call void %95(ptr %rtPtr, ptr %96, ptr %1)
  call void %91(ptr %rtPtr, ptr %59)
  %97 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %98 = icmp eq i32 %97, 0
  br i1 %98, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %99 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %100 = icmp eq i32 %99, 0
  br i1 %100, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %backgroundTexture = alloca %Texture.0, align 8
  %101 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  store i32 0, ptr %101, align 4
  %102 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 1
  store i32 0, ptr %102, align 4
  %103 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 2
  store i32 0, ptr %103, align 4
  %104 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 3
  store i32 0, ptr %104, align 4
  %105 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 4
  store i32 0, ptr %105, align 4
  %106 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %107 = load ptr, ptr %106, align 8
  %108 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %107, i32 0, i32 9
  %109 = load ptr, ptr %108, align 8
  %rtPtr38 = alloca %Texture.0, align 8
  %110 = alloca ptr, align 8
  store ptr @14, ptr %110, align 8
  call void %109(ptr %rtPtr38, ptr %110, ptr %1)
  %111 = load %Texture.0, ptr %rtPtr38, align 4
  store %Texture.0 %111, ptr %backgroundTexture, align 4
  %112 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %113 = icmp eq i32 %112, 0
  br i1 %113, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %114 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %115 = icmp eq i32 %114, 0
  br i1 %115, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %cloudTexture = alloca %Texture.0, align 8
  %116 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 0
  store i32 0, ptr %116, align 4
  %117 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 1
  store i32 0, ptr %117, align 4
  %118 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 2
  store i32 0, ptr %118, align 4
  %119 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 3
  store i32 0, ptr %119, align 4
  %120 = getelementptr inbounds %Texture.0, ptr %cloudTexture, i32 0, i32 4
  store i32 0, ptr %120, align 4
  %121 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %122 = load ptr, ptr %121, align 8
  %123 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %122, i32 0, i32 9
  %124 = load ptr, ptr %123, align 8
  %rtPtr39 = alloca %Texture.0, align 8
  %125 = alloca ptr, align 8
  store ptr @15, ptr %125, align 8
  call void %124(ptr %rtPtr39, ptr %125, ptr %1)
  %126 = load %Texture.0, ptr %rtPtr39, align 4
  store %Texture.0 %126, ptr %cloudTexture, align 4
  %127 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %129 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %mountL1Texture = alloca %Texture.0, align 8
  %131 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 0
  store i32 0, ptr %131, align 4
  %132 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 1
  store i32 0, ptr %132, align 4
  %133 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 2
  store i32 0, ptr %133, align 4
  %134 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 3
  store i32 0, ptr %134, align 4
  %135 = getelementptr inbounds %Texture.0, ptr %mountL1Texture, i32 0, i32 4
  store i32 0, ptr %135, align 4
  %136 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %137 = load ptr, ptr %136, align 8
  %138 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %137, i32 0, i32 9
  %139 = load ptr, ptr %138, align 8
  %rtPtr40 = alloca %Texture.0, align 8
  %140 = alloca ptr, align 8
  store ptr @16, ptr %140, align 8
  call void %139(ptr %rtPtr40, ptr %140, ptr %1)
  %141 = load %Texture.0, ptr %rtPtr40, align 4
  store %Texture.0 %141, ptr %mountL1Texture, align 4
  %142 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %143 = icmp eq i32 %142, 0
  br i1 %143, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %144 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %145 = icmp eq i32 %144, 0
  br i1 %145, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %mountL2Texture = alloca %Texture.0, align 8
  %146 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 0
  store i32 0, ptr %146, align 4
  %147 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 1
  store i32 0, ptr %147, align 4
  %148 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 2
  store i32 0, ptr %148, align 4
  %149 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 3
  store i32 0, ptr %149, align 4
  %150 = getelementptr inbounds %Texture.0, ptr %mountL2Texture, i32 0, i32 4
  store i32 0, ptr %150, align 4
  %151 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %152 = load ptr, ptr %151, align 8
  %153 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %152, i32 0, i32 9
  %154 = load ptr, ptr %153, align 8
  %rtPtr41 = alloca %Texture.0, align 8
  %155 = alloca ptr, align 8
  store ptr @17, ptr %155, align 8
  call void %154(ptr %rtPtr41, ptr %155, ptr %1)
  %156 = load %Texture.0, ptr %rtPtr41, align 4
  store %Texture.0 %156, ptr %mountL2Texture, align 4
  %157 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %158 = icmp eq i32 %157, 0
  br i1 %158, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %159 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %160 = icmp eq i32 %159, 0
  br i1 %160, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %mount2L2Texture = alloca %Texture.0, align 8
  %161 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 0
  store i32 0, ptr %161, align 4
  %162 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 1
  store i32 0, ptr %162, align 4
  %163 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 2
  store i32 0, ptr %163, align 4
  %164 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 3
  store i32 0, ptr %164, align 4
  %165 = getelementptr inbounds %Texture.0, ptr %mount2L2Texture, i32 0, i32 4
  store i32 0, ptr %165, align 4
  %166 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %167 = load ptr, ptr %166, align 8
  %168 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %167, i32 0, i32 9
  %169 = load ptr, ptr %168, align 8
  %rtPtr42 = alloca %Texture.0, align 8
  %170 = alloca ptr, align 8
  store ptr @18, ptr %170, align 8
  call void %169(ptr %rtPtr42, ptr %170, ptr %1)
  %171 = load %Texture.0, ptr %rtPtr42, align 4
  store %Texture.0 %171, ptr %mount2L2Texture, align 4
  %172 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %173 = icmp eq i32 %172, 0
  br i1 %173, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %174 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %175 = icmp eq i32 %174, 0
  br i1 %175, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %mount1L3Texture = alloca %Texture.0, align 8
  %176 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 0
  store i32 0, ptr %176, align 4
  %177 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 1
  store i32 0, ptr %177, align 4
  %178 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 2
  store i32 0, ptr %178, align 4
  %179 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 3
  store i32 0, ptr %179, align 4
  %180 = getelementptr inbounds %Texture.0, ptr %mount1L3Texture, i32 0, i32 4
  store i32 0, ptr %180, align 4
  %181 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %182 = load ptr, ptr %181, align 8
  %183 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %182, i32 0, i32 9
  %184 = load ptr, ptr %183, align 8
  %rtPtr43 = alloca %Texture.0, align 8
  %185 = alloca ptr, align 8
  store ptr @19, ptr %185, align 8
  call void %184(ptr %rtPtr43, ptr %185, ptr %1)
  %186 = load %Texture.0, ptr %rtPtr43, align 4
  store %Texture.0 %186, ptr %mount1L3Texture, align 4
  %187 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %188 = icmp eq i32 %187, 0
  br i1 %188, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %189 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %190 = icmp eq i32 %189, 0
  br i1 %190, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %mountL1Pos1 = alloca %Position.4, align 8
  %191 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %191, align 4
  %192 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %192, align 4
  %193 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %screenWidth44 = load i32, ptr @screenWidth, align 4
  %194 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if45, label %else46

checkContinueBlock20:                             ; preds = %merge47
  %195 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %196 = icmp eq i32 %195, 0
  br i1 %196, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %mountL1Pos2 = alloca %Position.4, align 8
  %197 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  store float 0.000000e+00, ptr %197, align 4
  %198 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %198, align 4
  %199 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %screenWidth48 = load i32, ptr @screenWidth, align 4
  %200 = load i32, ptr @screenWidth, align 4
  %201 = mul i32 -1, %200
  %202 = sitofp i32 %201 to float
  store float %202, ptr %199, align 4
  %203 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  store float 0.000000e+00, ptr %203, align 4
  %204 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %205 = icmp eq i32 %204, 0
  br i1 %205, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %206 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %207 = icmp eq i32 %206, 0
  br i1 %207, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %mountL2Pos1 = alloca %Position.4, align 8
  %208 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %208, align 4
  %209 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %209, align 4
  %210 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %screenWidth49 = load i32, ptr @screenWidth, align 4
  %211 = load i32, ptr @screenWidth, align 4
  %212 = mul i32 -1, %211
  %213 = sitofp i32 %212 to float
  store float %213, ptr %210, align 4
  %214 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %214, align 4
  %215 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %216 = icmp eq i32 %215, 0
  br i1 %216, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %217 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %218 = icmp eq i32 %217, 0
  br i1 %218, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  %mount2L2Pos1 = alloca %Position.4, align 8
  %219 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %219, align 4
  %220 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %220, align 4
  %221 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %screenWidth50 = load i32, ptr @screenWidth, align 4
  %222 = load i32, ptr @screenWidth, align 4
  %223 = mul i32 -1, %222
  %rtPtr51 = alloca i32, align 4
  %screenWidth52 = load i32, ptr @screenWidth, align 4
  %224 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if53, label %else54

checkContinueBlock26:                             ; preds = %merge59
  %225 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %226 = icmp eq i32 %225, 0
  br i1 %226, label %nestedBlock27, label %afterNestedBlock

nestedBlock27:                                    ; preds = %checkContinueBlock26
  %mount1L3Pos1 = alloca %Position.4, align 8
  %227 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  store float 0.000000e+00, ptr %227, align 4
  %228 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %228, align 4
  %229 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %screenWidth60 = load i32, ptr @screenWidth, align 4
  %230 = load i32, ptr @screenWidth, align 4
  %231 = mul i32 -1, %230
  %rtPtr61 = alloca i32, align 4
  %screenWidth62 = load i32, ptr @screenWidth, align 4
  %232 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if63, label %else64

checkContinueBlock28:                             ; preds = %merge65
  %233 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %234 = icmp eq i32 %233, 0
  br i1 %234, label %nestedBlock29, label %afterNestedBlock

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %235 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %236 = load ptr, ptr %235, align 8
  %237 = getelementptr inbounds %"Bird::VTableType", ptr %236, i32 0, i32 5
  %238 = load ptr, ptr %237, align 8
  %rtPtr67 = alloca i1, align 1
  call void %238(ptr %rtPtr67, ptr %59)
  %239 = load i1, ptr %rtPtr67, align 1
  %240 = xor i1 %239, true
  %241 = getelementptr inbounds %Texture.0, ptr %backgroundTexture, i32 0, i32 0
  %id = load i32, ptr %241, align 4
  %242 = load i32, ptr %241, align 4
  %243 = icmp eq i32 %242, 0
  %244 = select i1 %240, i1 true, i1 %243
  br i1 %244, label %then, label %else68

checkContinueBlock30:                             ; preds = %afterIfElse
  %245 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %246 = icmp eq i32 %245, 0
  br i1 %246, label %nestedBlock31, label %afterNestedBlock

nestedBlock31:                                    ; preds = %checkContinueBlock30
  br label %"while:conditon"

checkContinueBlock32:                             ; preds = %end_block451
  %247 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %248 = icmp eq i32 %247, 0
  br i1 %248, label %nestedBlock33, label %afterNestedBlock

nestedBlock33:                                    ; preds = %checkContinueBlock32
  %249 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %250 = load ptr, ptr %249, align 8
  %251 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %250, i32 0, i32 13
  %252 = load ptr, ptr %251, align 8
  call void %252(ptr %1)
  %253 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %254 = icmp eq i32 %253, 0
  br i1 %254, label %checkContinueBlock34, label %afterNestedBlock

checkContinueBlock34:                             ; preds = %nestedBlock33
  %255 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %256 = icmp eq i32 %255, 0
  br i1 %256, label %nestedBlock35, label %afterNestedBlock

nestedBlock35:                                    ; preds = %checkContinueBlock34
  br label %returnBlock452

checkContinueBlock36:                             ; preds = %mergeBlock453
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock1
  store i32 0, ptr %76, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %257 = load i32, ptr %76, align 4
  %258 = icmp slt i32 %257, 9
  %259 = load i32, ptr %77, align 4
  %260 = icmp slt i32 %259, 9
  %261 = and i1 %258, %260
  br i1 %261, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %262 = load i32, ptr %76, align 4
  %263 = getelementptr [9 x %Position.4], ptr %75, i32 0, i32 %262
  %264 = getelementptr inbounds %Position.4, ptr %263, i32 0, i32 0
  store float 0.000000e+00, ptr %264, align 4
  %265 = getelementptr inbounds %Position.4, ptr %263, i32 0, i32 1
  store float 0.000000e+00, ptr %265, align 4
  %266 = load i32, ptr %76, align 4
  %267 = add i32 %266, 1
  store i32 %267, ptr %76, align 4
  %268 = load i32, ptr %77, align 4
  %269 = add i32 %268, 1
  store i32 %269, ptr %77, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %270 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 11
  %271 = getelementptr inbounds %Position.4, ptr %270, i32 0, i32 0
  store float 0.000000e+00, ptr %271, align 4
  %272 = getelementptr inbounds %Position.4, ptr %270, i32 0, i32 1
  store float 0.000000e+00, ptr %272, align 4
  %273 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  store ptr @vtable.Bird.fg, ptr %273, align 8
  %274 = load ptr, ptr %273, align 8
  %275 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 8
  store ptr @Bird.updateY, ptr %275, align 8
  %276 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 7
  store ptr @Bird.getTexturePath, ptr %276, align 8
  %277 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 5
  store ptr @Bird.isTextureLoaded, ptr %277, align 8
  %278 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 9
  store ptr @Bird.setTexture, ptr %278, align 8
  %279 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 2
  store ptr @Bird.getOrigin, ptr %279, align 8
  %280 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 4
  store ptr @Bird.getSource, ptr %280, align 8
  %281 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 6
  store ptr @Bird.update, ptr %281, align 8
  %282 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 0
  store ptr @Bird.getTexture, ptr %282, align 8
  %283 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 3
  store ptr @Bird.getDistination, ptr %283, align 8
  %284 = getelementptr inbounds %"Bird::VTableType", ptr %274, i32 0, i32 1
  store ptr @Bird.getRotation, ptr %284, align 8
  %285 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 1
  store float 3.600000e+02, ptr %285, align 4
  %286 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 2
  store float 9.000000e+01, ptr %286, align 4
  %287 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 3
  %FPS37 = load i32, ptr @FPS, align 4
  %288 = load i32, ptr @FPS, align 4
  %289 = icmp eq i32 %288, 0
  br i1 %289, label %if, label %else

if:                                               ; preds = %FillExpr.exit
  call void @raise_exception(ptr @11)
  br label %merge

else:                                             ; preds = %FillExpr.exit
  %290 = sitofp i32 %288 to double
  %291 = fdiv double 5.000000e+00, %290
  br label %merge

merge:                                            ; preds = %else, %if
  store double %291, ptr %287, align 8
  %292 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 5
  store i32 9, ptr %292, align 4
  %293 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 6
  store i32 0, ptr %293, align 4
  %294 = alloca ptr, align 8
  store ptr @12, ptr %294, align 8
  call void @Bird.init1(ptr %294, ptr %59)
  %295 = load %Bird, ptr %59, align 8
  store %Bird %295, ptr %59, align 8
  %296 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %297 = icmp eq i32 %296, 0
  br i1 %297, label %checkContinueBlock2, label %afterNestedBlock

if45:                                             ; preds = %nestedBlock19
  call void @raise_exception(ptr @20)
  br label %merge47

else46:                                           ; preds = %nestedBlock19
  %298 = sitofp i32 %194 to double
  %299 = fdiv double %298, 4.000000e+00
  br label %merge47

merge47:                                          ; preds = %else46, %if45
  %300 = fptrunc double %299 to float
  store float %300, ptr %193, align 4
  %301 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %301, align 4
  %302 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %303 = icmp eq i32 %302, 0
  br i1 %303, label %checkContinueBlock20, label %afterNestedBlock

if53:                                             ; preds = %nestedBlock25
  call void @raise_exception(ptr @21)
  br label %merge55

else54:                                           ; preds = %nestedBlock25
  %304 = sitofp i32 %224 to double
  %305 = fdiv double %304, 4.000000e+00
  br label %merge55

merge55:                                          ; preds = %else54, %if53
  %306 = fptosi double %305 to i32
  %307 = alloca i32, align 4
  store i32 %306, ptr %307, align 4
  %screenWidth56 = load i32, ptr @screenWidth, align 4
  %308 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if57, label %else58

if57:                                             ; preds = %merge55
  call void @raise_exception(ptr @22)
  br label %merge59

else58:                                           ; preds = %merge55
  %309 = sitofp i32 %308 to double
  %310 = fdiv double %309, 2.000000e+00
  br label %merge59

merge59:                                          ; preds = %else58, %if57
  %311 = fptosi double %310 to i32
  %312 = alloca i32, align 4
  store i32 %311, ptr %312, align 4
  call void @getRandomNumber(ptr %rtPtr51, ptr %307, ptr %312)
  %313 = load i32, ptr %rtPtr51, align 4
  %314 = sub i32 %223, %313
  %315 = sitofp i32 %314 to float
  store float %315, ptr %221, align 4
  %316 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %316, align 4
  %317 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %318 = icmp eq i32 %317, 0
  br i1 %318, label %checkContinueBlock26, label %afterNestedBlock

if63:                                             ; preds = %nestedBlock27
  call void @raise_exception(ptr @23)
  br label %merge65

else64:                                           ; preds = %nestedBlock27
  %319 = sitofp i32 %232 to double
  %320 = fdiv double %319, 4.000000e+00
  br label %merge65

merge65:                                          ; preds = %else64, %if63
  %321 = fptosi double %320 to i32
  %322 = alloca i32, align 4
  store i32 %321, ptr %322, align 4
  %screenWidth66 = load i32, ptr @screenWidth, align 4
  %323 = alloca i32, align 4
  store i32 %screenWidth66, ptr %323, align 4
  call void @getRandomNumber(ptr %rtPtr61, ptr %322, ptr %323)
  %324 = load i32, ptr %rtPtr61, align 4
  %325 = sub i32 %231, %324
  %326 = sitofp i32 %325 to float
  store float %326, ptr %229, align 4
  %327 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  store float 0.000000e+00, ptr %327, align 4
  %328 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %329 = icmp eq i32 %328, 0
  br i1 %329, label %checkContinueBlock28, label %afterNestedBlock

then:                                             ; preds = %nestedBlock29
  br label %nestedBlock70

else68:                                           ; preds = %nestedBlock29
  br label %afterIfElse

afterIfElse:                                      ; preds = %else68, %afterNestedBlock69
  %330 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %331 = icmp eq i32 %330, 0
  br i1 %331, label %checkContinueBlock30, label %afterNestedBlock

afterNestedBlock69:                               ; preds = %checkContinueBlock77, %mergeBlock, %checkContinueBlock75, %nestedBlock74, %checkContinueBlock73, %nestedBlock72, %checkContinueBlock71, %nestedBlock70
  br label %afterIfElse

nestedBlock70:                                    ; preds = %then
  %332 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %333 = load ptr, ptr %332, align 8
  %334 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %333, i32 0, i32 1
  %335 = load ptr, ptr %334, align 8
  %336 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 7
  %337 = getelementptr inbounds %LOG_TYPE.1, ptr %336, i32 0, i32 5
  %ERROR = load i32, ptr %337, align 4
  %338 = alloca ptr, align 8
  store ptr @24, ptr %338, align 8
  call void %335(ptr %337, ptr %338, ptr %1)
  %339 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %340 = icmp eq i32 %339, 0
  br i1 %340, label %checkContinueBlock71, label %afterNestedBlock69

checkContinueBlock71:                             ; preds = %nestedBlock70
  %341 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %342 = icmp eq i32 %341, 0
  br i1 %342, label %nestedBlock72, label %afterNestedBlock69

nestedBlock72:                                    ; preds = %checkContinueBlock71
  %343 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %344 = load ptr, ptr %343, align 8
  %345 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %344, i32 0, i32 14
  %346 = load ptr, ptr %345, align 8
  %347 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %348 = load ptr, ptr %347, align 8
  %349 = getelementptr inbounds %"Bird::VTableType", ptr %348, i32 0, i32 0
  %350 = load ptr, ptr %349, align 8
  %rtPtr78 = alloca %Texture.0, align 8
  call void %350(ptr %rtPtr78, ptr %59)
  call void %346(ptr %rtPtr78, ptr %1)
  %351 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %352 = icmp eq i32 %351, 0
  br i1 %352, label %checkContinueBlock73, label %afterNestedBlock69

checkContinueBlock73:                             ; preds = %nestedBlock72
  %353 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %354 = icmp eq i32 %353, 0
  br i1 %354, label %nestedBlock74, label %afterNestedBlock69

nestedBlock74:                                    ; preds = %checkContinueBlock73
  %355 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %356 = load ptr, ptr %355, align 8
  %357 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %356, i32 0, i32 13
  %358 = load ptr, ptr %357, align 8
  call void %358(ptr %1)
  %359 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %360 = icmp eq i32 %359, 0
  br i1 %360, label %checkContinueBlock75, label %afterNestedBlock69

checkContinueBlock75:                             ; preds = %nestedBlock74
  %361 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %362 = icmp eq i32 %361, 0
  br i1 %362, label %nestedBlock76, label %afterNestedBlock69

nestedBlock76:                                    ; preds = %checkContinueBlock75
  br label %returnBlock

checkContinueBlock77:                             ; preds = %mergeBlock
  br label %afterNestedBlock69

returnBlock:                                      ; preds = %nestedBlock76
  store i32 1, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %363 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %364 = icmp eq i32 %363, 0
  br i1 %364, label %checkContinueBlock77, label %afterNestedBlock69

"while:conditon":                                 ; preds = %afterNestedBlock80, %nestedBlock31
  %365 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %366 = icmp eq i32 %365, 0
  br i1 %366, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock81

while.end:                                        ; preds = %afterNestedBlock80, %end_block
  %367 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %368 = icmp eq i32 %367, 0
  br i1 %368, label %end_block451, label %decrement_block450

decrement_block:                                  ; preds = %"while:conditon"
  %369 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %370 = sub i32 %369, 1
  store i32 %370, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %371 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %372 = load ptr, ptr %371, align 8
  %373 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %372, i32 0, i32 18
  %374 = load ptr, ptr %373, align 8
  %rtPtr79 = alloca i1, align 1
  call void %374(ptr %rtPtr79, ptr %1)
  %375 = load i1, ptr %rtPtr79, align 1
  %376 = xor i1 %375, true
  br i1 %376, label %"while:body", label %while.end

afterNestedBlock80:                               ; preds = %checkContinueBlock114, %nestedBlock113, %checkContinueBlock112, %nestedBlock111, %checkContinueBlock110, %FillExpr.exit440, %checkContinueBlock108, %FillExpr.exit409, %checkContinueBlock106, %FillExpr.exit378, %checkContinueBlock104, %FillExpr.exit348, %checkContinueBlock102, %FillExpr.exit319, %checkContinueBlock100, %FillExpr.exit291, %checkContinueBlock98, %FillExpr.exit265, %checkContinueBlock96, %nestedBlock95, %checkContinueBlock94, %nestedBlock93, %checkContinueBlock92, %afterIfElse244, %checkContinueBlock90, %afterNestedBlock208, %checkContinueBlock88, %afterNestedBlock180, %checkContinueBlock86, %afterNestedBlock158, %checkContinueBlock84, %afterNestedBlock116, %checkContinueBlock82, %nestedBlock81
  %377 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %378 = icmp eq i32 %377, 0
  br i1 %378, label %"while:conditon", label %while.end

nestedBlock81:                                    ; preds = %"while:body"
  %379 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %380 = load ptr, ptr %379, align 8
  %381 = getelementptr inbounds %"Bird::VTableType", ptr %380, i32 0, i32 6
  %382 = load ptr, ptr %381, align 8
  %383 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %384 = load ptr, ptr %383, align 8
  %385 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %384, i32 0, i32 8
  %386 = load ptr, ptr %385, align 8
  %rtPtr115 = alloca float, align 4
  call void %386(ptr %rtPtr115, ptr %1)
  call void %382(ptr %rtPtr115, ptr %59)
  %387 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %388 = icmp eq i32 %387, 0
  br i1 %388, label %checkContinueBlock82, label %afterNestedBlock80

checkContinueBlock82:                             ; preds = %nestedBlock81
  %389 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %390 = icmp eq i32 %389, 0
  br i1 %390, label %nestedBlock83, label %afterNestedBlock80

nestedBlock83:                                    ; preds = %checkContinueBlock82
  br label %nestedBlock117

checkContinueBlock84:                             ; preds = %afterNestedBlock116
  %391 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %392 = icmp eq i32 %391, 0
  br i1 %392, label %nestedBlock85, label %afterNestedBlock80

nestedBlock85:                                    ; preds = %checkContinueBlock84
  br label %nestedBlock159

checkContinueBlock86:                             ; preds = %afterNestedBlock158
  %393 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %394 = icmp eq i32 %393, 0
  br i1 %394, label %nestedBlock87, label %afterNestedBlock80

nestedBlock87:                                    ; preds = %checkContinueBlock86
  br label %nestedBlock181

checkContinueBlock88:                             ; preds = %afterNestedBlock180
  %395 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %396 = icmp eq i32 %395, 0
  br i1 %396, label %nestedBlock89, label %afterNestedBlock80

nestedBlock89:                                    ; preds = %checkContinueBlock88
  br label %nestedBlock209

checkContinueBlock90:                             ; preds = %afterNestedBlock208
  %397 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %398 = icmp eq i32 %397, 0
  br i1 %398, label %nestedBlock91, label %afterNestedBlock80

nestedBlock91:                                    ; preds = %checkContinueBlock90
  %399 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %400 = load ptr, ptr %399, align 8
  %401 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %400, i32 0, i32 0
  %402 = load ptr, ptr %401, align 8
  %rtPtr239 = alloca i1, align 1
  %403 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %404 = getelementptr inbounds %KEYS_TYPE.2, ptr %403, i32 0, i32 3
  %KEY_UP = load i32, ptr %404, align 4
  call void %402(ptr %rtPtr239, ptr %404, ptr %1)
  %405 = load i1, ptr %rtPtr239, align 1
  %406 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %407 = load ptr, ptr %406, align 8
  %408 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %407, i32 0, i32 4
  %409 = load ptr, ptr %408, align 8
  %rtPtr240 = alloca i1, align 1
  %410 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 6
  %411 = getelementptr inbounds %KEYS_TYPE.2, ptr %410, i32 0, i32 3
  %KEY_UP241 = load i32, ptr %411, align 4
  call void %409(ptr %rtPtr240, ptr %411, ptr %1)
  %412 = load i1, ptr %rtPtr240, align 1
  %413 = select i1 %405, i1 true, i1 %412
  br i1 %413, label %then242, label %else243

checkContinueBlock92:                             ; preds = %afterIfElse244
  %414 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %415 = icmp eq i32 %414, 0
  br i1 %415, label %nestedBlock93, label %afterNestedBlock80

nestedBlock93:                                    ; preds = %checkContinueBlock92
  %416 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %417 = load ptr, ptr %416, align 8
  %418 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %417, i32 0, i32 15
  %419 = load ptr, ptr %418, align 8
  call void %419(ptr %1)
  %420 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %421 = icmp eq i32 %420, 0
  br i1 %421, label %checkContinueBlock94, label %afterNestedBlock80

checkContinueBlock94:                             ; preds = %nestedBlock93
  %422 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %423 = icmp eq i32 %422, 0
  br i1 %423, label %nestedBlock95, label %afterNestedBlock80

nestedBlock95:                                    ; preds = %checkContinueBlock94
  %424 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %425 = load ptr, ptr %424, align 8
  %426 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %425, i32 0, i32 10
  %427 = load ptr, ptr %426, align 8
  %428 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %429 = getelementptr inbounds %COLORS_TYPE.3, ptr %428, i32 0, i32 0
  %WHITE = load i32, ptr %429, align 4
  call void %427(ptr %429, ptr %1)
  %430 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %431 = icmp eq i32 %430, 0
  br i1 %431, label %checkContinueBlock96, label %afterNestedBlock80

checkContinueBlock96:                             ; preds = %nestedBlock95
  %432 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %433 = icmp eq i32 %432, 0
  br i1 %433, label %nestedBlock97, label %afterNestedBlock80

nestedBlock97:                                    ; preds = %checkContinueBlock96
  %434 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %435 = load ptr, ptr %434, align 8
  %436 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %435, i32 0, i32 20
  %437 = load ptr, ptr %436, align 8
  %438 = alloca [4 x float], align 4
  %439 = alloca i32, align 4
  %440 = alloca i32, align 4
  store i32 0, ptr %440, align 4
  br label %FillExpr.loopStart-0249

checkContinueBlock98:                             ; preds = %FillExpr.exit265
  %441 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %442 = icmp eq i32 %441, 0
  br i1 %442, label %nestedBlock99, label %afterNestedBlock80

nestedBlock99:                                    ; preds = %checkContinueBlock98
  %443 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %444 = load ptr, ptr %443, align 8
  %445 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %444, i32 0, i32 20
  %446 = load ptr, ptr %445, align 8
  %447 = alloca [4 x float], align 4
  %448 = alloca i32, align 4
  %449 = alloca i32, align 4
  store i32 0, ptr %449, align 4
  br label %FillExpr.loopStart-0267

checkContinueBlock100:                            ; preds = %FillExpr.exit291
  %450 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %451 = icmp eq i32 %450, 0
  br i1 %451, label %nestedBlock101, label %afterNestedBlock80

nestedBlock101:                                   ; preds = %checkContinueBlock100
  %452 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %453 = load ptr, ptr %452, align 8
  %454 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %453, i32 0, i32 20
  %455 = load ptr, ptr %454, align 8
  %456 = alloca [4 x float], align 4
  %457 = alloca i32, align 4
  %458 = alloca i32, align 4
  store i32 0, ptr %458, align 4
  br label %FillExpr.loopStart-0293

checkContinueBlock102:                            ; preds = %FillExpr.exit319
  %459 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %460 = icmp eq i32 %459, 0
  br i1 %460, label %nestedBlock103, label %afterNestedBlock80

nestedBlock103:                                   ; preds = %checkContinueBlock102
  %461 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %462 = load ptr, ptr %461, align 8
  %463 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %462, i32 0, i32 20
  %464 = load ptr, ptr %463, align 8
  %465 = alloca [4 x float], align 4
  %466 = alloca i32, align 4
  %467 = alloca i32, align 4
  store i32 0, ptr %467, align 4
  br label %FillExpr.loopStart-0322

checkContinueBlock104:                            ; preds = %FillExpr.exit348
  %468 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %469 = icmp eq i32 %468, 0
  br i1 %469, label %nestedBlock105, label %afterNestedBlock80

nestedBlock105:                                   ; preds = %checkContinueBlock104
  %470 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %471 = load ptr, ptr %470, align 8
  %472 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %471, i32 0, i32 20
  %473 = load ptr, ptr %472, align 8
  %474 = alloca [4 x float], align 4
  %475 = alloca i32, align 4
  %476 = alloca i32, align 4
  store i32 0, ptr %476, align 4
  br label %FillExpr.loopStart-0352

checkContinueBlock106:                            ; preds = %FillExpr.exit378
  %477 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %478 = icmp eq i32 %477, 0
  br i1 %478, label %nestedBlock107, label %afterNestedBlock80

nestedBlock107:                                   ; preds = %checkContinueBlock106
  %479 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %480 = load ptr, ptr %479, align 8
  %481 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %480, i32 0, i32 20
  %482 = load ptr, ptr %481, align 8
  %483 = alloca [4 x float], align 4
  %484 = alloca i32, align 4
  %485 = alloca i32, align 4
  store i32 0, ptr %485, align 4
  br label %FillExpr.loopStart-0382

checkContinueBlock108:                            ; preds = %FillExpr.exit409
  %486 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %487 = icmp eq i32 %486, 0
  br i1 %487, label %nestedBlock109, label %afterNestedBlock80

nestedBlock109:                                   ; preds = %checkContinueBlock108
  %488 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %489 = load ptr, ptr %488, align 8
  %490 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %489, i32 0, i32 20
  %491 = load ptr, ptr %490, align 8
  %492 = alloca [4 x float], align 4
  %493 = alloca i32, align 4
  %494 = alloca i32, align 4
  store i32 0, ptr %494, align 4
  br label %FillExpr.loopStart-0413

checkContinueBlock110:                            ; preds = %FillExpr.exit440
  %495 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %496 = icmp eq i32 %495, 0
  br i1 %496, label %nestedBlock111, label %afterNestedBlock80

nestedBlock111:                                   ; preds = %checkContinueBlock110
  %497 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %498 = load ptr, ptr %497, align 8
  %499 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %498, i32 0, i32 20
  %500 = load ptr, ptr %499, align 8
  %501 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %502 = load ptr, ptr %501, align 8
  %503 = getelementptr inbounds %"Bird::VTableType", ptr %502, i32 0, i32 0
  %504 = load ptr, ptr %503, align 8
  %rtPtr444 = alloca %Texture.0, align 8
  call void %504(ptr %rtPtr444, ptr %59)
  %505 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %506 = load ptr, ptr %505, align 8
  %507 = getelementptr inbounds %"Bird::VTableType", ptr %506, i32 0, i32 4
  %508 = load ptr, ptr %507, align 8
  %rtPtr445 = alloca [4 x float], align 4
  call void %508(ptr %rtPtr445, ptr %59)
  %509 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %510 = load ptr, ptr %509, align 8
  %511 = getelementptr inbounds %"Bird::VTableType", ptr %510, i32 0, i32 3
  %512 = load ptr, ptr %511, align 8
  %rtPtr446 = alloca [4 x float], align 4
  call void %512(ptr %rtPtr446, ptr %59)
  %513 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %514 = load ptr, ptr %513, align 8
  %515 = getelementptr inbounds %"Bird::VTableType", ptr %514, i32 0, i32 2
  %516 = load ptr, ptr %515, align 8
  %rtPtr447 = alloca [2 x float], align 4
  call void %516(ptr %rtPtr447, ptr %59)
  %517 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %518 = load ptr, ptr %517, align 8
  %519 = getelementptr inbounds %"Bird::VTableType", ptr %518, i32 0, i32 1
  %520 = load ptr, ptr %519, align 8
  %rtPtr448 = alloca float, align 4
  call void %520(ptr %rtPtr448, ptr %59)
  %521 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %522 = getelementptr inbounds %COLORS_TYPE.3, ptr %521, i32 0, i32 0
  %WHITE449 = load i32, ptr %522, align 4
  call void %500(ptr %rtPtr444, ptr %rtPtr445, ptr %rtPtr446, ptr %rtPtr447, ptr %rtPtr448, ptr %522, ptr %1)
  %523 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %524 = icmp eq i32 %523, 0
  br i1 %524, label %checkContinueBlock112, label %afterNestedBlock80

checkContinueBlock112:                            ; preds = %nestedBlock111
  %525 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %526 = icmp eq i32 %525, 0
  br i1 %526, label %nestedBlock113, label %afterNestedBlock80

nestedBlock113:                                   ; preds = %checkContinueBlock112
  %527 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %528 = load ptr, ptr %527, align 8
  %529 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %528, i32 0, i32 22
  %530 = load ptr, ptr %529, align 8
  call void %530(ptr %1)
  %531 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %532 = icmp eq i32 %531, 0
  br i1 %532, label %checkContinueBlock114, label %afterNestedBlock80

checkContinueBlock114:                            ; preds = %nestedBlock113
  br label %afterNestedBlock80

afterNestedBlock116:                              ; preds = %checkContinueBlock124, %afterIfElse152, %checkContinueBlock122, %afterIfElse138, %checkContinueBlock120, %nestedBlock119, %checkContinueBlock118, %nestedBlock117
  %533 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %534 = icmp eq i32 %533, 0
  br i1 %534, label %checkContinueBlock84, label %afterNestedBlock80

nestedBlock117:                                   ; preds = %nestedBlock83
  %535 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x = load float, ptr %535, align 4
  %536 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x125 = load float, ptr %536, align 4
  %537 = load float, ptr %536, align 4
  %538 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %539 = load ptr, ptr %538, align 8
  %540 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %539, i32 0, i32 8
  %541 = load ptr, ptr %540, align 8
  %rtPtr126 = alloca float, align 4
  call void %541(ptr %rtPtr126, ptr %1)
  %542 = load float, ptr %rtPtr126, align 4
  %543 = fmul float %542, 6.000000e+01
  %544 = fadd float %537, %543
  store float %544, ptr %535, align 4
  %545 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %546 = icmp eq i32 %545, 0
  br i1 %546, label %checkContinueBlock118, label %afterNestedBlock116

checkContinueBlock118:                            ; preds = %nestedBlock117
  %547 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %548 = icmp eq i32 %547, 0
  br i1 %548, label %nestedBlock119, label %afterNestedBlock116

nestedBlock119:                                   ; preds = %checkContinueBlock118
  %549 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x127 = load float, ptr %549, align 4
  %550 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x128 = load float, ptr %550, align 4
  %551 = load float, ptr %550, align 4
  %552 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %553 = load ptr, ptr %552, align 8
  %554 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %553, i32 0, i32 8
  %555 = load ptr, ptr %554, align 8
  %rtPtr129 = alloca float, align 4
  call void %555(ptr %rtPtr129, ptr %1)
  %556 = load float, ptr %rtPtr129, align 4
  %557 = fmul float %556, 6.000000e+01
  %558 = fadd float %551, %557
  store float %558, ptr %549, align 4
  %559 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %560 = icmp eq i32 %559, 0
  br i1 %560, label %checkContinueBlock120, label %afterNestedBlock116

checkContinueBlock120:                            ; preds = %nestedBlock119
  %561 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %562 = icmp eq i32 %561, 0
  br i1 %562, label %nestedBlock121, label %afterNestedBlock116

nestedBlock121:                                   ; preds = %checkContinueBlock120
  %563 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x130 = load float, ptr %563, align 4
  %564 = load float, ptr %563, align 4
  %screenWidth131 = load i32, ptr @screenWidth, align 4
  %565 = load i32, ptr @screenWidth, align 4
  %screenWidth132 = load i32, ptr @screenWidth, align 4
  %566 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if133, label %else134

checkContinueBlock122:                            ; preds = %afterIfElse138
  %567 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %568 = icmp eq i32 %567, 0
  br i1 %568, label %nestedBlock123, label %afterNestedBlock116

nestedBlock123:                                   ; preds = %checkContinueBlock122
  %569 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x144 = load float, ptr %569, align 4
  %570 = load float, ptr %569, align 4
  %screenWidth145 = load i32, ptr @screenWidth, align 4
  %571 = load i32, ptr @screenWidth, align 4
  %screenWidth146 = load i32, ptr @screenWidth, align 4
  %572 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if147, label %else148

checkContinueBlock124:                            ; preds = %afterIfElse152
  br label %afterNestedBlock116

if133:                                            ; preds = %nestedBlock121
  call void @raise_exception(ptr @25)
  br label %merge135

else134:                                          ; preds = %nestedBlock121
  %573 = sitofp i32 %566 to double
  %574 = fdiv double %573, 2.000000e+00
  br label %merge135

merge135:                                         ; preds = %else134, %if133
  %575 = sitofp i32 %565 to double
  %576 = fadd double %575, %574
  %577 = fptrunc double %576 to float
  %578 = fcmp ogt float %564, %577
  br i1 %578, label %then136, label %else137

then136:                                          ; preds = %merge135
  br label %nestedBlock140

else137:                                          ; preds = %merge135
  br label %afterIfElse138

afterIfElse138:                                   ; preds = %else137, %afterNestedBlock139
  %579 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %580 = icmp eq i32 %579, 0
  br i1 %580, label %checkContinueBlock122, label %afterNestedBlock116

afterNestedBlock139:                              ; preds = %checkContinueBlock141, %nestedBlock140
  %581 = load float, ptr %582, align 4
  br label %afterIfElse138

nestedBlock140:                                   ; preds = %then136
  %582 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x142 = load float, ptr %582, align 4
  %screenWidth143 = load i32, ptr @screenWidth, align 4
  %583 = load i32, ptr @screenWidth, align 4
  %584 = mul i32 -1, %583
  %585 = sitofp i32 %584 to float
  store float %585, ptr %582, align 4
  %586 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %587 = icmp eq i32 %586, 0
  br i1 %587, label %checkContinueBlock141, label %afterNestedBlock139

checkContinueBlock141:                            ; preds = %nestedBlock140
  br label %afterNestedBlock139

if147:                                            ; preds = %nestedBlock123
  call void @raise_exception(ptr @26)
  br label %merge149

else148:                                          ; preds = %nestedBlock123
  %588 = sitofp i32 %572 to double
  %589 = fdiv double %588, 2.000000e+00
  br label %merge149

merge149:                                         ; preds = %else148, %if147
  %590 = sitofp i32 %571 to double
  %591 = fadd double %590, %589
  %592 = fptrunc double %591 to float
  %593 = fcmp ogt float %570, %592
  br i1 %593, label %then150, label %else151

then150:                                          ; preds = %merge149
  br label %nestedBlock154

else151:                                          ; preds = %merge149
  br label %afterIfElse152

afterIfElse152:                                   ; preds = %else151, %afterNestedBlock153
  %594 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %595 = icmp eq i32 %594, 0
  br i1 %595, label %checkContinueBlock124, label %afterNestedBlock116

afterNestedBlock153:                              ; preds = %checkContinueBlock155, %nestedBlock154
  %596 = load float, ptr %597, align 4
  br label %afterIfElse152

nestedBlock154:                                   ; preds = %then150
  %597 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x156 = load float, ptr %597, align 4
  %screenWidth157 = load i32, ptr @screenWidth, align 4
  %598 = load i32, ptr @screenWidth, align 4
  %599 = mul i32 -1, %598
  %600 = sitofp i32 %599 to float
  store float %600, ptr %597, align 4
  %601 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %602 = icmp eq i32 %601, 0
  br i1 %602, label %checkContinueBlock155, label %afterNestedBlock153

checkContinueBlock155:                            ; preds = %nestedBlock154
  br label %afterNestedBlock153

afterNestedBlock158:                              ; preds = %checkContinueBlock162, %afterIfElse174, %checkContinueBlock160, %nestedBlock159
  %603 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %604 = icmp eq i32 %603, 0
  br i1 %604, label %checkContinueBlock86, label %afterNestedBlock80

nestedBlock159:                                   ; preds = %nestedBlock85
  %605 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x163 = load float, ptr %605, align 4
  %606 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x164 = load float, ptr %606, align 4
  %607 = load float, ptr %606, align 4
  %608 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %609 = load ptr, ptr %608, align 8
  %610 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %609, i32 0, i32 8
  %611 = load ptr, ptr %610, align 8
  %rtPtr165 = alloca float, align 4
  call void %611(ptr %rtPtr165, ptr %1)
  %612 = load float, ptr %rtPtr165, align 4
  %613 = fmul float %612, 2.000000e+01
  %614 = fadd float %607, %613
  store float %614, ptr %605, align 4
  %615 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %616 = icmp eq i32 %615, 0
  br i1 %616, label %checkContinueBlock160, label %afterNestedBlock158

checkContinueBlock160:                            ; preds = %nestedBlock159
  %617 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %618 = icmp eq i32 %617, 0
  br i1 %618, label %nestedBlock161, label %afterNestedBlock158

nestedBlock161:                                   ; preds = %checkContinueBlock160
  %619 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x166 = load float, ptr %619, align 4
  %620 = load float, ptr %619, align 4
  %screenWidth167 = load i32, ptr @screenWidth, align 4
  %621 = load i32, ptr @screenWidth, align 4
  %screenWidth168 = load i32, ptr @screenWidth, align 4
  %622 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if169, label %else170

checkContinueBlock162:                            ; preds = %afterIfElse174
  br label %afterNestedBlock158

if169:                                            ; preds = %nestedBlock161
  call void @raise_exception(ptr @27)
  br label %merge171

else170:                                          ; preds = %nestedBlock161
  %623 = sitofp i32 %622 to double
  %624 = fdiv double %623, 2.000000e+00
  br label %merge171

merge171:                                         ; preds = %else170, %if169
  %625 = sitofp i32 %621 to double
  %626 = fadd double %625, %624
  %627 = fptrunc double %626 to float
  %628 = fcmp ogt float %620, %627
  br i1 %628, label %then172, label %else173

then172:                                          ; preds = %merge171
  br label %nestedBlock176

else173:                                          ; preds = %merge171
  br label %afterIfElse174

afterIfElse174:                                   ; preds = %else173, %afterNestedBlock175
  %629 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %630 = icmp eq i32 %629, 0
  br i1 %630, label %checkContinueBlock162, label %afterNestedBlock158

afterNestedBlock175:                              ; preds = %checkContinueBlock177, %nestedBlock176
  %631 = load float, ptr %632, align 4
  br label %afterIfElse174

nestedBlock176:                                   ; preds = %then172
  %632 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x178 = load float, ptr %632, align 4
  %screenWidth179 = load i32, ptr @screenWidth, align 4
  %633 = load i32, ptr @screenWidth, align 4
  %634 = mul i32 -1, %633
  %635 = sitofp i32 %634 to float
  store float %635, ptr %632, align 4
  %636 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %637 = icmp eq i32 %636, 0
  br i1 %637, label %checkContinueBlock177, label %afterNestedBlock175

checkContinueBlock177:                            ; preds = %nestedBlock176
  br label %afterNestedBlock175

afterNestedBlock180:                              ; preds = %checkContinueBlock184, %afterIfElse196, %checkContinueBlock182, %nestedBlock181
  %638 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %639 = icmp eq i32 %638, 0
  br i1 %639, label %checkContinueBlock88, label %afterNestedBlock80

nestedBlock181:                                   ; preds = %nestedBlock87
  %640 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x185 = load float, ptr %640, align 4
  %641 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x186 = load float, ptr %641, align 4
  %642 = load float, ptr %641, align 4
  %643 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %644 = load ptr, ptr %643, align 8
  %645 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %644, i32 0, i32 8
  %646 = load ptr, ptr %645, align 8
  %rtPtr187 = alloca float, align 4
  call void %646(ptr %rtPtr187, ptr %1)
  %647 = load float, ptr %rtPtr187, align 4
  %648 = fmul float %647, 1.000000e+01
  %649 = fadd float %642, %648
  store float %649, ptr %640, align 4
  %650 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %651 = icmp eq i32 %650, 0
  br i1 %651, label %checkContinueBlock182, label %afterNestedBlock180

checkContinueBlock182:                            ; preds = %nestedBlock181
  %652 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %653 = icmp eq i32 %652, 0
  br i1 %653, label %nestedBlock183, label %afterNestedBlock180

nestedBlock183:                                   ; preds = %checkContinueBlock182
  %654 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x188 = load float, ptr %654, align 4
  %655 = load float, ptr %654, align 4
  %screenWidth189 = load i32, ptr @screenWidth, align 4
  %656 = load i32, ptr @screenWidth, align 4
  %screenWidth190 = load i32, ptr @screenWidth, align 4
  %657 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if191, label %else192

checkContinueBlock184:                            ; preds = %afterIfElse196
  br label %afterNestedBlock180

if191:                                            ; preds = %nestedBlock183
  call void @raise_exception(ptr @28)
  br label %merge193

else192:                                          ; preds = %nestedBlock183
  %658 = sitofp i32 %657 to double
  %659 = fdiv double %658, 2.000000e+00
  br label %merge193

merge193:                                         ; preds = %else192, %if191
  %660 = sitofp i32 %656 to double
  %661 = fadd double %660, %659
  %662 = fptrunc double %661 to float
  %663 = fcmp ogt float %655, %662
  br i1 %663, label %then194, label %else195

then194:                                          ; preds = %merge193
  br label %nestedBlock198

else195:                                          ; preds = %merge193
  br label %afterIfElse196

afterIfElse196:                                   ; preds = %else195, %afterNestedBlock197
  %664 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %665 = icmp eq i32 %664, 0
  br i1 %665, label %checkContinueBlock184, label %afterNestedBlock180

afterNestedBlock197:                              ; preds = %checkContinueBlock199, %merge206
  %666 = load float, ptr %667, align 4
  br label %afterIfElse196

nestedBlock198:                                   ; preds = %then194
  %667 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x200 = load float, ptr %667, align 4
  %screenWidth201 = load i32, ptr @screenWidth, align 4
  %668 = load i32, ptr @screenWidth, align 4
  %669 = mul i32 -1, %668
  %rtPtr202 = alloca i32, align 4
  %screenWidth203 = load i32, ptr @screenWidth, align 4
  %670 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if204, label %else205

checkContinueBlock199:                            ; preds = %merge206
  br label %afterNestedBlock197

if204:                                            ; preds = %nestedBlock198
  call void @raise_exception(ptr @29)
  br label %merge206

else205:                                          ; preds = %nestedBlock198
  %671 = sitofp i32 %670 to double
  %672 = fdiv double %671, 4.000000e+00
  br label %merge206

merge206:                                         ; preds = %else205, %if204
  %673 = fptosi double %672 to i32
  %674 = alloca i32, align 4
  store i32 %673, ptr %674, align 4
  %screenWidth207 = load i32, ptr @screenWidth, align 4
  %675 = alloca i32, align 4
  store i32 %screenWidth207, ptr %675, align 4
  call void @getRandomNumber(ptr %rtPtr202, ptr %674, ptr %675)
  %676 = load i32, ptr %rtPtr202, align 4
  %677 = sub i32 %669, %676
  %678 = sitofp i32 %677 to float
  store float %678, ptr %667, align 4
  %679 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %680 = icmp eq i32 %679, 0
  br i1 %680, label %checkContinueBlock199, label %afterNestedBlock197

afterNestedBlock208:                              ; preds = %checkContinueBlock212, %afterIfElse224, %checkContinueBlock210, %nestedBlock209
  %681 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %682 = icmp eq i32 %681, 0
  br i1 %682, label %checkContinueBlock90, label %afterNestedBlock80

nestedBlock209:                                   ; preds = %nestedBlock89
  %683 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x213 = load float, ptr %683, align 4
  %684 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x214 = load float, ptr %684, align 4
  %685 = load float, ptr %684, align 4
  %686 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %687 = load ptr, ptr %686, align 8
  %688 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %687, i32 0, i32 8
  %689 = load ptr, ptr %688, align 8
  %rtPtr215 = alloca float, align 4
  call void %689(ptr %rtPtr215, ptr %1)
  %690 = load float, ptr %rtPtr215, align 4
  %691 = fmul float %690, 5.000000e+00
  %692 = fadd float %685, %691
  store float %692, ptr %683, align 4
  %693 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %694 = icmp eq i32 %693, 0
  br i1 %694, label %checkContinueBlock210, label %afterNestedBlock208

checkContinueBlock210:                            ; preds = %nestedBlock209
  %695 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %696 = icmp eq i32 %695, 0
  br i1 %696, label %nestedBlock211, label %afterNestedBlock208

nestedBlock211:                                   ; preds = %checkContinueBlock210
  %697 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x216 = load float, ptr %697, align 4
  %698 = load float, ptr %697, align 4
  %screenWidth217 = load i32, ptr @screenWidth, align 4
  %699 = load i32, ptr @screenWidth, align 4
  %screenWidth218 = load i32, ptr @screenWidth, align 4
  %700 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if219, label %else220

checkContinueBlock212:                            ; preds = %afterIfElse224
  br label %afterNestedBlock208

if219:                                            ; preds = %nestedBlock211
  call void @raise_exception(ptr @30)
  br label %merge221

else220:                                          ; preds = %nestedBlock211
  %701 = sitofp i32 %700 to double
  %702 = fdiv double %701, 2.000000e+00
  br label %merge221

merge221:                                         ; preds = %else220, %if219
  %703 = sitofp i32 %699 to double
  %704 = fadd double %703, %702
  %705 = fptrunc double %704 to float
  %706 = fcmp ogt float %698, %705
  br i1 %706, label %then222, label %else223

then222:                                          ; preds = %merge221
  br label %nestedBlock226

else223:                                          ; preds = %merge221
  br label %afterIfElse224

afterIfElse224:                                   ; preds = %else223, %afterNestedBlock225
  %707 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %708 = icmp eq i32 %707, 0
  br i1 %708, label %checkContinueBlock212, label %afterNestedBlock208

afterNestedBlock225:                              ; preds = %checkContinueBlock227, %merge238
  %709 = load float, ptr %710, align 4
  br label %afterIfElse224

nestedBlock226:                                   ; preds = %then222
  %710 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x228 = load float, ptr %710, align 4
  %screenWidth229 = load i32, ptr @screenWidth, align 4
  %711 = load i32, ptr @screenWidth, align 4
  %712 = mul i32 -1, %711
  %rtPtr230 = alloca i32, align 4
  %screenWidth231 = load i32, ptr @screenWidth, align 4
  %713 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if232, label %else233

checkContinueBlock227:                            ; preds = %merge238
  br label %afterNestedBlock225

if232:                                            ; preds = %nestedBlock226
  call void @raise_exception(ptr @31)
  br label %merge234

else233:                                          ; preds = %nestedBlock226
  %714 = sitofp i32 %713 to double
  %715 = fdiv double %714, 4.000000e+00
  br label %merge234

merge234:                                         ; preds = %else233, %if232
  %716 = fptosi double %715 to i32
  %717 = alloca i32, align 4
  store i32 %716, ptr %717, align 4
  %screenWidth235 = load i32, ptr @screenWidth, align 4
  %718 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if236, label %else237

if236:                                            ; preds = %merge234
  call void @raise_exception(ptr @32)
  br label %merge238

else237:                                          ; preds = %merge234
  %719 = sitofp i32 %718 to double
  %720 = fdiv double %719, 2.000000e+00
  br label %merge238

merge238:                                         ; preds = %else237, %if236
  %721 = fptosi double %720 to i32
  %722 = alloca i32, align 4
  store i32 %721, ptr %722, align 4
  call void @getRandomNumber(ptr %rtPtr230, ptr %717, ptr %722)
  %723 = load i32, ptr %rtPtr230, align 4
  %724 = sub i32 %712, %723
  %725 = sitofp i32 %724 to float
  store float %725, ptr %710, align 4
  %726 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %727 = icmp eq i32 %726, 0
  br i1 %727, label %checkContinueBlock227, label %afterNestedBlock225

then242:                                          ; preds = %nestedBlock91
  br label %nestedBlock246

else243:                                          ; preds = %nestedBlock91
  br label %afterIfElse244

afterIfElse244:                                   ; preds = %else243, %afterNestedBlock245
  %728 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %729 = icmp eq i32 %728, 0
  br i1 %729, label %checkContinueBlock92, label %afterNestedBlock80

afterNestedBlock245:                              ; preds = %checkContinueBlock247, %nestedBlock246
  br label %afterIfElse244

nestedBlock246:                                   ; preds = %then242
  %730 = getelementptr inbounds %Bird, ptr %59, i32 0, i32 0
  %731 = load ptr, ptr %730, align 8
  %732 = getelementptr inbounds %"Bird::VTableType", ptr %731, i32 0, i32 8
  %733 = load ptr, ptr %732, align 8
  %734 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 0
  %735 = load ptr, ptr %734, align 8
  %736 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %735, i32 0, i32 8
  %737 = load ptr, ptr %736, align 8
  %rtPtr248 = alloca float, align 4
  call void %737(ptr %rtPtr248, ptr %1)
  call void %733(ptr %rtPtr248, ptr %59)
  %738 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %739 = icmp eq i32 %738, 0
  br i1 %739, label %checkContinueBlock247, label %afterNestedBlock245

checkContinueBlock247:                            ; preds = %nestedBlock246
  br label %afterNestedBlock245

FillExpr.loopStart-0249:                          ; preds = %nestedBlock97
  store i32 0, ptr %439, align 4
  br label %FillExpr.loopCmp-0250

FillExpr.loopCmp-0250:                            ; preds = %FillExpr.loopBody-0251, %FillExpr.loopStart-0249
  %740 = load i32, ptr %439, align 4
  %741 = icmp slt i32 %740, 4
  %742 = load i32, ptr %440, align 4
  %743 = icmp slt i32 %742, 4
  %744 = and i1 %741, %743
  br i1 %744, label %FillExpr.loopBody-0251, label %FillExpr.loopEnd-0252

FillExpr.loopBody-0251:                           ; preds = %FillExpr.loopCmp-0250
  %745 = load i32, ptr %439, align 4
  %746 = getelementptr [4 x float], ptr %438, i32 0, i32 %745
  store float 0.000000e+00, ptr %746, align 4
  %747 = load i32, ptr %439, align 4
  %748 = add i32 %747, 1
  store i32 %748, ptr %439, align 4
  %749 = load i32, ptr %440, align 4
  %750 = add i32 %749, 1
  store i32 %750, ptr %440, align 4
  br label %FillExpr.loopCmp-0250

FillExpr.loopEnd-0252:                            ; preds = %FillExpr.loopCmp-0250
  br label %FillExpr.exit253

FillExpr.exit253:                                 ; preds = %FillExpr.loopEnd-0252
  %751 = getelementptr [4 x float], ptr %438, i32 0, i32 0
  store float 0.000000e+00, ptr %751, align 4
  %752 = getelementptr [4 x float], ptr %438, i32 0, i32 1
  store float 0.000000e+00, ptr %752, align 4
  %753 = getelementptr [4 x float], ptr %438, i32 0, i32 2
  store float 3.840000e+03, ptr %753, align 4
  %754 = getelementptr [4 x float], ptr %438, i32 0, i32 3
  store float 2.160000e+03, ptr %754, align 4
  %755 = alloca [4 x float], align 4
  %756 = alloca i32, align 4
  %757 = alloca i32, align 4
  store i32 0, ptr %757, align 4
  br label %FillExpr.loopStart-0254

FillExpr.loopStart-0254:                          ; preds = %FillExpr.exit253
  store i32 0, ptr %756, align 4
  br label %FillExpr.loopCmp-0255

FillExpr.loopCmp-0255:                            ; preds = %FillExpr.loopBody-0256, %FillExpr.loopStart-0254
  %758 = load i32, ptr %756, align 4
  %759 = icmp slt i32 %758, 4
  %760 = load i32, ptr %757, align 4
  %761 = icmp slt i32 %760, 4
  %762 = and i1 %759, %761
  br i1 %762, label %FillExpr.loopBody-0256, label %FillExpr.loopEnd-0257

FillExpr.loopBody-0256:                           ; preds = %FillExpr.loopCmp-0255
  %763 = load i32, ptr %756, align 4
  %764 = getelementptr [4 x float], ptr %755, i32 0, i32 %763
  store float 0.000000e+00, ptr %764, align 4
  %765 = load i32, ptr %756, align 4
  %766 = add i32 %765, 1
  store i32 %766, ptr %756, align 4
  %767 = load i32, ptr %757, align 4
  %768 = add i32 %767, 1
  store i32 %768, ptr %757, align 4
  br label %FillExpr.loopCmp-0255

FillExpr.loopEnd-0257:                            ; preds = %FillExpr.loopCmp-0255
  br label %FillExpr.exit258

FillExpr.exit258:                                 ; preds = %FillExpr.loopEnd-0257
  %769 = getelementptr [4 x float], ptr %755, i32 0, i32 0
  store float 0.000000e+00, ptr %769, align 4
  %770 = getelementptr [4 x float], ptr %755, i32 0, i32 1
  store float 0.000000e+00, ptr %770, align 4
  %771 = getelementptr [4 x float], ptr %755, i32 0, i32 2
  %screenWidth259 = load i32, ptr @screenWidth, align 4
  %772 = sitofp i32 %screenWidth259 to float
  store float %772, ptr %771, align 4
  %773 = getelementptr [4 x float], ptr %755, i32 0, i32 3
  %screenHeight260 = load i32, ptr @screenHeight, align 4
  %774 = sitofp i32 %screenHeight260 to float
  store float %774, ptr %773, align 4
  %775 = alloca [2 x float], align 4
  %776 = alloca i32, align 4
  %777 = alloca i32, align 4
  store i32 0, ptr %777, align 4
  br label %FillExpr.loopStart-0261

FillExpr.loopStart-0261:                          ; preds = %FillExpr.exit258
  store i32 0, ptr %776, align 4
  br label %FillExpr.loopCmp-0262

FillExpr.loopCmp-0262:                            ; preds = %FillExpr.loopBody-0263, %FillExpr.loopStart-0261
  %778 = load i32, ptr %776, align 4
  %779 = icmp slt i32 %778, 2
  %780 = load i32, ptr %777, align 4
  %781 = icmp slt i32 %780, 2
  %782 = and i1 %779, %781
  br i1 %782, label %FillExpr.loopBody-0263, label %FillExpr.loopEnd-0264

FillExpr.loopBody-0263:                           ; preds = %FillExpr.loopCmp-0262
  %783 = load i32, ptr %776, align 4
  %784 = getelementptr [2 x float], ptr %775, i32 0, i32 %783
  store float 0.000000e+00, ptr %784, align 4
  %785 = load i32, ptr %776, align 4
  %786 = add i32 %785, 1
  store i32 %786, ptr %776, align 4
  %787 = load i32, ptr %777, align 4
  %788 = add i32 %787, 1
  store i32 %788, ptr %777, align 4
  br label %FillExpr.loopCmp-0262

FillExpr.loopEnd-0264:                            ; preds = %FillExpr.loopCmp-0262
  br label %FillExpr.exit265

FillExpr.exit265:                                 ; preds = %FillExpr.loopEnd-0264
  %789 = getelementptr [2 x float], ptr %775, i32 0, i32 0
  store float 0.000000e+00, ptr %789, align 4
  %790 = getelementptr [2 x float], ptr %775, i32 0, i32 1
  store float 0.000000e+00, ptr %790, align 4
  %791 = alloca float, align 4
  store float 0.000000e+00, ptr %791, align 4
  %792 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %793 = getelementptr inbounds %COLORS_TYPE.3, ptr %792, i32 0, i32 0
  %WHITE266 = load i32, ptr %793, align 4
  call void %437(ptr %backgroundTexture, ptr %438, ptr %755, ptr %775, ptr %791, ptr %793, ptr %1)
  %794 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %795 = icmp eq i32 %794, 0
  br i1 %795, label %checkContinueBlock98, label %afterNestedBlock80

FillExpr.loopStart-0267:                          ; preds = %nestedBlock99
  store i32 0, ptr %448, align 4
  br label %FillExpr.loopCmp-0268

FillExpr.loopCmp-0268:                            ; preds = %FillExpr.loopBody-0269, %FillExpr.loopStart-0267
  %796 = load i32, ptr %448, align 4
  %797 = icmp slt i32 %796, 4
  %798 = load i32, ptr %449, align 4
  %799 = icmp slt i32 %798, 4
  %800 = and i1 %797, %799
  br i1 %800, label %FillExpr.loopBody-0269, label %FillExpr.loopEnd-0270

FillExpr.loopBody-0269:                           ; preds = %FillExpr.loopCmp-0268
  %801 = load i32, ptr %448, align 4
  %802 = getelementptr [4 x float], ptr %447, i32 0, i32 %801
  store float 0.000000e+00, ptr %802, align 4
  %803 = load i32, ptr %448, align 4
  %804 = add i32 %803, 1
  store i32 %804, ptr %448, align 4
  %805 = load i32, ptr %449, align 4
  %806 = add i32 %805, 1
  store i32 %806, ptr %449, align 4
  br label %FillExpr.loopCmp-0268

FillExpr.loopEnd-0270:                            ; preds = %FillExpr.loopCmp-0268
  br label %FillExpr.exit271

FillExpr.exit271:                                 ; preds = %FillExpr.loopEnd-0270
  %807 = getelementptr [4 x float], ptr %447, i32 0, i32 0
  store float 0.000000e+00, ptr %807, align 4
  %808 = getelementptr [4 x float], ptr %447, i32 0, i32 1
  store float 0.000000e+00, ptr %808, align 4
  %809 = getelementptr [4 x float], ptr %447, i32 0, i32 2
  store float 1.280000e+03, ptr %809, align 4
  %810 = getelementptr [4 x float], ptr %447, i32 0, i32 3
  store float 7.200000e+02, ptr %810, align 4
  %811 = alloca [4 x float], align 4
  %812 = alloca i32, align 4
  %813 = alloca i32, align 4
  store i32 0, ptr %813, align 4
  br label %FillExpr.loopStart-0272

FillExpr.loopStart-0272:                          ; preds = %FillExpr.exit271
  store i32 0, ptr %812, align 4
  br label %FillExpr.loopCmp-0273

FillExpr.loopCmp-0273:                            ; preds = %FillExpr.loopBody-0274, %FillExpr.loopStart-0272
  %814 = load i32, ptr %812, align 4
  %815 = icmp slt i32 %814, 4
  %816 = load i32, ptr %813, align 4
  %817 = icmp slt i32 %816, 4
  %818 = and i1 %815, %817
  br i1 %818, label %FillExpr.loopBody-0274, label %FillExpr.loopEnd-0275

FillExpr.loopBody-0274:                           ; preds = %FillExpr.loopCmp-0273
  %819 = load i32, ptr %812, align 4
  %820 = getelementptr [4 x float], ptr %811, i32 0, i32 %819
  store float 0.000000e+00, ptr %820, align 4
  %821 = load i32, ptr %812, align 4
  %822 = add i32 %821, 1
  store i32 %822, ptr %812, align 4
  %823 = load i32, ptr %813, align 4
  %824 = add i32 %823, 1
  store i32 %824, ptr %813, align 4
  br label %FillExpr.loopCmp-0273

FillExpr.loopEnd-0275:                            ; preds = %FillExpr.loopCmp-0273
  br label %FillExpr.exit276

FillExpr.exit276:                                 ; preds = %FillExpr.loopEnd-0275
  %825 = getelementptr [4 x float], ptr %811, i32 0, i32 0
  store float 0.000000e+00, ptr %825, align 4
  %826 = getelementptr [4 x float], ptr %811, i32 0, i32 1
  store float 0.000000e+00, ptr %826, align 4
  %827 = getelementptr [4 x float], ptr %811, i32 0, i32 2
  br i1 false, label %if277, label %else278

if277:                                            ; preds = %FillExpr.exit276
  call void @raise_exception(ptr @33)
  br label %merge279

else278:                                          ; preds = %FillExpr.exit276
  br label %merge279

merge279:                                         ; preds = %else278, %if277
  %screenHeight280 = load i32, ptr @screenHeight, align 4
  %828 = load i32, ptr @screenHeight, align 4
  %829 = sitofp i32 %828 to double
  %830 = fmul double 0x3FFC71C71C71C71C, %829
  br i1 false, label %if281, label %else282

if281:                                            ; preds = %merge279
  call void @raise_exception(ptr @34)
  br label %else282

else282:                                          ; preds = %if281, %merge279
  %831 = fdiv double %830, 2.000000e+00
  %832 = fptrunc double %831 to float
  store float %832, ptr %827, align 4
  %833 = getelementptr [4 x float], ptr %811, i32 0, i32 3
  %screenHeight283 = load i32, ptr @screenHeight, align 4
  %834 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if284, label %else285

if284:                                            ; preds = %else282
  call void @raise_exception(ptr @35)
  br label %merge286

else285:                                          ; preds = %else282
  %835 = sitofp i32 %834 to double
  %836 = fdiv double %835, 2.000000e+00
  br label %merge286

merge286:                                         ; preds = %else285, %if284
  %837 = fptrunc double %836 to float
  store float %837, ptr %833, align 4
  %838 = alloca [2 x float], align 4
  %839 = alloca i32, align 4
  %840 = alloca i32, align 4
  store i32 0, ptr %840, align 4
  br label %FillExpr.loopStart-0287

FillExpr.loopStart-0287:                          ; preds = %merge286
  store i32 0, ptr %839, align 4
  br label %FillExpr.loopCmp-0288

FillExpr.loopCmp-0288:                            ; preds = %FillExpr.loopBody-0289, %FillExpr.loopStart-0287
  %841 = load i32, ptr %839, align 4
  %842 = icmp slt i32 %841, 2
  %843 = load i32, ptr %840, align 4
  %844 = icmp slt i32 %843, 2
  %845 = and i1 %842, %844
  br i1 %845, label %FillExpr.loopBody-0289, label %FillExpr.loopEnd-0290

FillExpr.loopBody-0289:                           ; preds = %FillExpr.loopCmp-0288
  %846 = load i32, ptr %839, align 4
  %847 = getelementptr [2 x float], ptr %838, i32 0, i32 %846
  store float 0.000000e+00, ptr %847, align 4
  %848 = load i32, ptr %839, align 4
  %849 = add i32 %848, 1
  store i32 %849, ptr %839, align 4
  %850 = load i32, ptr %840, align 4
  %851 = add i32 %850, 1
  store i32 %851, ptr %840, align 4
  br label %FillExpr.loopCmp-0288

FillExpr.loopEnd-0290:                            ; preds = %FillExpr.loopCmp-0288
  br label %FillExpr.exit291

FillExpr.exit291:                                 ; preds = %FillExpr.loopEnd-0290
  %852 = getelementptr [2 x float], ptr %838, i32 0, i32 0
  store float 0.000000e+00, ptr %852, align 4
  %853 = getelementptr [2 x float], ptr %838, i32 0, i32 1
  store float 0.000000e+00, ptr %853, align 4
  %854 = alloca float, align 4
  store float 0.000000e+00, ptr %854, align 4
  %855 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %856 = getelementptr inbounds %COLORS_TYPE.3, ptr %855, i32 0, i32 0
  %WHITE292 = load i32, ptr %856, align 4
  call void %446(ptr %cloudTexture, ptr %447, ptr %811, ptr %838, ptr %854, ptr %856, ptr %1)
  %857 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %858 = icmp eq i32 %857, 0
  br i1 %858, label %checkContinueBlock100, label %afterNestedBlock80

FillExpr.loopStart-0293:                          ; preds = %nestedBlock101
  store i32 0, ptr %457, align 4
  br label %FillExpr.loopCmp-0294

FillExpr.loopCmp-0294:                            ; preds = %FillExpr.loopBody-0295, %FillExpr.loopStart-0293
  %859 = load i32, ptr %457, align 4
  %860 = icmp slt i32 %859, 4
  %861 = load i32, ptr %458, align 4
  %862 = icmp slt i32 %861, 4
  %863 = and i1 %860, %862
  br i1 %863, label %FillExpr.loopBody-0295, label %FillExpr.loopEnd-0296

FillExpr.loopBody-0295:                           ; preds = %FillExpr.loopCmp-0294
  %864 = load i32, ptr %457, align 4
  %865 = getelementptr [4 x float], ptr %456, i32 0, i32 %864
  store float 0.000000e+00, ptr %865, align 4
  %866 = load i32, ptr %457, align 4
  %867 = add i32 %866, 1
  store i32 %867, ptr %457, align 4
  %868 = load i32, ptr %458, align 4
  %869 = add i32 %868, 1
  store i32 %869, ptr %458, align 4
  br label %FillExpr.loopCmp-0294

FillExpr.loopEnd-0296:                            ; preds = %FillExpr.loopCmp-0294
  br label %FillExpr.exit297

FillExpr.exit297:                                 ; preds = %FillExpr.loopEnd-0296
  %870 = getelementptr [4 x float], ptr %456, i32 0, i32 0
  store float 0.000000e+00, ptr %870, align 4
  %871 = getelementptr [4 x float], ptr %456, i32 0, i32 1
  store float 0.000000e+00, ptr %871, align 4
  %872 = getelementptr [4 x float], ptr %456, i32 0, i32 2
  store float 5.975000e+03, ptr %872, align 4
  %873 = getelementptr [4 x float], ptr %456, i32 0, i32 3
  store float 1.607000e+03, ptr %873, align 4
  %874 = alloca [4 x float], align 4
  %875 = alloca i32, align 4
  %876 = alloca i32, align 4
  store i32 0, ptr %876, align 4
  br label %FillExpr.loopStart-0298

FillExpr.loopStart-0298:                          ; preds = %FillExpr.exit297
  store i32 0, ptr %875, align 4
  br label %FillExpr.loopCmp-0299

FillExpr.loopCmp-0299:                            ; preds = %FillExpr.loopBody-0300, %FillExpr.loopStart-0298
  %877 = load i32, ptr %875, align 4
  %878 = icmp slt i32 %877, 4
  %879 = load i32, ptr %876, align 4
  %880 = icmp slt i32 %879, 4
  %881 = and i1 %878, %880
  br i1 %881, label %FillExpr.loopBody-0300, label %FillExpr.loopEnd-0301

FillExpr.loopBody-0300:                           ; preds = %FillExpr.loopCmp-0299
  %882 = load i32, ptr %875, align 4
  %883 = getelementptr [4 x float], ptr %874, i32 0, i32 %882
  store float 0.000000e+00, ptr %883, align 4
  %884 = load i32, ptr %875, align 4
  %885 = add i32 %884, 1
  store i32 %885, ptr %875, align 4
  %886 = load i32, ptr %876, align 4
  %887 = add i32 %886, 1
  store i32 %887, ptr %876, align 4
  br label %FillExpr.loopCmp-0299

FillExpr.loopEnd-0301:                            ; preds = %FillExpr.loopCmp-0299
  br label %FillExpr.exit302

FillExpr.exit302:                                 ; preds = %FillExpr.loopEnd-0301
  %888 = getelementptr [4 x float], ptr %874, i32 0, i32 0
  store float 0.000000e+00, ptr %888, align 4
  %889 = getelementptr [4 x float], ptr %874, i32 0, i32 1
  %screenHeight303 = load i32, ptr @screenHeight, align 4
  %890 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if304, label %else305

if304:                                            ; preds = %FillExpr.exit302
  call void @raise_exception(ptr @36)
  br label %merge306

else305:                                          ; preds = %FillExpr.exit302
  %891 = sitofp i32 %890 to double
  %892 = fdiv double %891, 2.000000e+00
  br label %merge306

merge306:                                         ; preds = %else305, %if304
  %893 = fptrunc double %892 to float
  store float %893, ptr %889, align 4
  %894 = getelementptr [4 x float], ptr %874, i32 0, i32 2
  %screenWidth307 = load i32, ptr @screenWidth, align 4
  %895 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if308, label %else309

if308:                                            ; preds = %merge306
  call void @raise_exception(ptr @37)
  br label %merge310

else309:                                          ; preds = %merge306
  %896 = sitofp i32 %895 to double
  %897 = fdiv double %896, 2.000000e+00
  br label %merge310

merge310:                                         ; preds = %else309, %if308
  %898 = fptrunc double %897 to float
  store float %898, ptr %894, align 4
  %899 = getelementptr [4 x float], ptr %874, i32 0, i32 3
  %screenHeight311 = load i32, ptr @screenHeight, align 4
  %900 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if312, label %else313

if312:                                            ; preds = %merge310
  call void @raise_exception(ptr @38)
  br label %merge314

else313:                                          ; preds = %merge310
  %901 = sitofp i32 %900 to double
  %902 = fdiv double %901, 5.000000e+00
  br label %merge314

merge314:                                         ; preds = %else313, %if312
  %903 = fptrunc double %902 to float
  store float %903, ptr %899, align 4
  %904 = alloca [2 x float], align 4
  %905 = alloca i32, align 4
  %906 = alloca i32, align 4
  store i32 0, ptr %906, align 4
  br label %FillExpr.loopStart-0315

FillExpr.loopStart-0315:                          ; preds = %merge314
  store i32 0, ptr %905, align 4
  br label %FillExpr.loopCmp-0316

FillExpr.loopCmp-0316:                            ; preds = %FillExpr.loopBody-0317, %FillExpr.loopStart-0315
  %907 = load i32, ptr %905, align 4
  %908 = icmp slt i32 %907, 2
  %909 = load i32, ptr %906, align 4
  %910 = icmp slt i32 %909, 2
  %911 = and i1 %908, %910
  br i1 %911, label %FillExpr.loopBody-0317, label %FillExpr.loopEnd-0318

FillExpr.loopBody-0317:                           ; preds = %FillExpr.loopCmp-0316
  %912 = load i32, ptr %905, align 4
  %913 = getelementptr [2 x float], ptr %904, i32 0, i32 %912
  store float 0.000000e+00, ptr %913, align 4
  %914 = load i32, ptr %905, align 4
  %915 = add i32 %914, 1
  store i32 %915, ptr %905, align 4
  %916 = load i32, ptr %906, align 4
  %917 = add i32 %916, 1
  store i32 %917, ptr %906, align 4
  br label %FillExpr.loopCmp-0316

FillExpr.loopEnd-0318:                            ; preds = %FillExpr.loopCmp-0316
  br label %FillExpr.exit319

FillExpr.exit319:                                 ; preds = %FillExpr.loopEnd-0318
  %918 = getelementptr [2 x float], ptr %904, i32 0, i32 0
  %919 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 0
  %x320 = load float, ptr %919, align 4
  %920 = load float, ptr %919, align 4
  store float %920, ptr %918, align 4
  %921 = getelementptr [2 x float], ptr %904, i32 0, i32 1
  %922 = getelementptr inbounds %Position.4, ptr %mountL2Pos1, i32 0, i32 1
  %y = load float, ptr %922, align 4
  %923 = load float, ptr %922, align 4
  store float %923, ptr %921, align 4
  %924 = alloca float, align 4
  store float 0.000000e+00, ptr %924, align 4
  %925 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %926 = getelementptr inbounds %COLORS_TYPE.3, ptr %925, i32 0, i32 0
  %WHITE321 = load i32, ptr %926, align 4
  call void %455(ptr %mountL2Texture, ptr %456, ptr %874, ptr %904, ptr %924, ptr %926, ptr %1)
  %927 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %928 = icmp eq i32 %927, 0
  br i1 %928, label %checkContinueBlock102, label %afterNestedBlock80

FillExpr.loopStart-0322:                          ; preds = %nestedBlock103
  store i32 0, ptr %466, align 4
  br label %FillExpr.loopCmp-0323

FillExpr.loopCmp-0323:                            ; preds = %FillExpr.loopBody-0324, %FillExpr.loopStart-0322
  %929 = load i32, ptr %466, align 4
  %930 = icmp slt i32 %929, 4
  %931 = load i32, ptr %467, align 4
  %932 = icmp slt i32 %931, 4
  %933 = and i1 %930, %932
  br i1 %933, label %FillExpr.loopBody-0324, label %FillExpr.loopEnd-0325

FillExpr.loopBody-0324:                           ; preds = %FillExpr.loopCmp-0323
  %934 = load i32, ptr %466, align 4
  %935 = getelementptr [4 x float], ptr %465, i32 0, i32 %934
  store float 0.000000e+00, ptr %935, align 4
  %936 = load i32, ptr %466, align 4
  %937 = add i32 %936, 1
  store i32 %937, ptr %466, align 4
  %938 = load i32, ptr %467, align 4
  %939 = add i32 %938, 1
  store i32 %939, ptr %467, align 4
  br label %FillExpr.loopCmp-0323

FillExpr.loopEnd-0325:                            ; preds = %FillExpr.loopCmp-0323
  br label %FillExpr.exit326

FillExpr.exit326:                                 ; preds = %FillExpr.loopEnd-0325
  %940 = getelementptr [4 x float], ptr %465, i32 0, i32 0
  store float 0.000000e+00, ptr %940, align 4
  %941 = getelementptr [4 x float], ptr %465, i32 0, i32 1
  store float 0.000000e+00, ptr %941, align 4
  %942 = getelementptr [4 x float], ptr %465, i32 0, i32 2
  store float 4.461000e+03, ptr %942, align 4
  %943 = getelementptr [4 x float], ptr %465, i32 0, i32 3
  store float 1.989000e+03, ptr %943, align 4
  %944 = alloca [4 x float], align 4
  %945 = alloca i32, align 4
  %946 = alloca i32, align 4
  store i32 0, ptr %946, align 4
  br label %FillExpr.loopStart-0327

FillExpr.loopStart-0327:                          ; preds = %FillExpr.exit326
  store i32 0, ptr %945, align 4
  br label %FillExpr.loopCmp-0328

FillExpr.loopCmp-0328:                            ; preds = %FillExpr.loopBody-0329, %FillExpr.loopStart-0327
  %947 = load i32, ptr %945, align 4
  %948 = icmp slt i32 %947, 4
  %949 = load i32, ptr %946, align 4
  %950 = icmp slt i32 %949, 4
  %951 = and i1 %948, %950
  br i1 %951, label %FillExpr.loopBody-0329, label %FillExpr.loopEnd-0330

FillExpr.loopBody-0329:                           ; preds = %FillExpr.loopCmp-0328
  %952 = load i32, ptr %945, align 4
  %953 = getelementptr [4 x float], ptr %944, i32 0, i32 %952
  store float 0.000000e+00, ptr %953, align 4
  %954 = load i32, ptr %945, align 4
  %955 = add i32 %954, 1
  store i32 %955, ptr %945, align 4
  %956 = load i32, ptr %946, align 4
  %957 = add i32 %956, 1
  store i32 %957, ptr %946, align 4
  br label %FillExpr.loopCmp-0328

FillExpr.loopEnd-0330:                            ; preds = %FillExpr.loopCmp-0328
  br label %FillExpr.exit331

FillExpr.exit331:                                 ; preds = %FillExpr.loopEnd-0330
  %958 = getelementptr [4 x float], ptr %944, i32 0, i32 0
  store float 0.000000e+00, ptr %958, align 4
  %959 = getelementptr [4 x float], ptr %944, i32 0, i32 1
  %screenHeight332 = load i32, ptr @screenHeight, align 4
  %960 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if333, label %else334

if333:                                            ; preds = %FillExpr.exit331
  call void @raise_exception(ptr @39)
  br label %merge335

else334:                                          ; preds = %FillExpr.exit331
  %961 = sitofp i32 %960 to double
  %962 = fdiv double %961, 2.000000e+00
  br label %merge335

merge335:                                         ; preds = %else334, %if333
  %963 = fptrunc double %962 to float
  store float %963, ptr %959, align 4
  %964 = getelementptr [4 x float], ptr %944, i32 0, i32 2
  %screenWidth336 = load i32, ptr @screenWidth, align 4
  %965 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if337, label %else338

if337:                                            ; preds = %merge335
  call void @raise_exception(ptr @40)
  br label %merge339

else338:                                          ; preds = %merge335
  %966 = sitofp i32 %965 to double
  %967 = fdiv double %966, 2.000000e+00
  br label %merge339

merge339:                                         ; preds = %else338, %if337
  %968 = fptrunc double %967 to float
  store float %968, ptr %964, align 4
  %969 = getelementptr [4 x float], ptr %944, i32 0, i32 3
  %screenHeight340 = load i32, ptr @screenHeight, align 4
  %970 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if341, label %else342

if341:                                            ; preds = %merge339
  call void @raise_exception(ptr @41)
  br label %merge343

else342:                                          ; preds = %merge339
  %971 = sitofp i32 %970 to double
  %972 = fdiv double %971, 5.000000e+00
  br label %merge343

merge343:                                         ; preds = %else342, %if341
  %973 = fptrunc double %972 to float
  store float %973, ptr %969, align 4
  %974 = alloca [2 x float], align 4
  %975 = alloca i32, align 4
  %976 = alloca i32, align 4
  store i32 0, ptr %976, align 4
  br label %FillExpr.loopStart-0344

FillExpr.loopStart-0344:                          ; preds = %merge343
  store i32 0, ptr %975, align 4
  br label %FillExpr.loopCmp-0345

FillExpr.loopCmp-0345:                            ; preds = %FillExpr.loopBody-0346, %FillExpr.loopStart-0344
  %977 = load i32, ptr %975, align 4
  %978 = icmp slt i32 %977, 2
  %979 = load i32, ptr %976, align 4
  %980 = icmp slt i32 %979, 2
  %981 = and i1 %978, %980
  br i1 %981, label %FillExpr.loopBody-0346, label %FillExpr.loopEnd-0347

FillExpr.loopBody-0346:                           ; preds = %FillExpr.loopCmp-0345
  %982 = load i32, ptr %975, align 4
  %983 = getelementptr [2 x float], ptr %974, i32 0, i32 %982
  store float 0.000000e+00, ptr %983, align 4
  %984 = load i32, ptr %975, align 4
  %985 = add i32 %984, 1
  store i32 %985, ptr %975, align 4
  %986 = load i32, ptr %976, align 4
  %987 = add i32 %986, 1
  store i32 %987, ptr %976, align 4
  br label %FillExpr.loopCmp-0345

FillExpr.loopEnd-0347:                            ; preds = %FillExpr.loopCmp-0345
  br label %FillExpr.exit348

FillExpr.exit348:                                 ; preds = %FillExpr.loopEnd-0347
  %988 = getelementptr [2 x float], ptr %974, i32 0, i32 0
  %989 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 0
  %x349 = load float, ptr %989, align 4
  %990 = load float, ptr %989, align 4
  store float %990, ptr %988, align 4
  %991 = getelementptr [2 x float], ptr %974, i32 0, i32 1
  %992 = getelementptr inbounds %Position.4, ptr %mount2L2Pos1, i32 0, i32 1
  %y350 = load float, ptr %992, align 4
  %993 = load float, ptr %992, align 4
  store float %993, ptr %991, align 4
  %994 = alloca float, align 4
  store float 0.000000e+00, ptr %994, align 4
  %995 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %996 = getelementptr inbounds %COLORS_TYPE.3, ptr %995, i32 0, i32 0
  %WHITE351 = load i32, ptr %996, align 4
  call void %464(ptr %mount2L2Texture, ptr %465, ptr %944, ptr %974, ptr %994, ptr %996, ptr %1)
  %997 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %998 = icmp eq i32 %997, 0
  br i1 %998, label %checkContinueBlock104, label %afterNestedBlock80

FillExpr.loopStart-0352:                          ; preds = %nestedBlock105
  store i32 0, ptr %475, align 4
  br label %FillExpr.loopCmp-0353

FillExpr.loopCmp-0353:                            ; preds = %FillExpr.loopBody-0354, %FillExpr.loopStart-0352
  %999 = load i32, ptr %475, align 4
  %1000 = icmp slt i32 %999, 4
  %1001 = load i32, ptr %476, align 4
  %1002 = icmp slt i32 %1001, 4
  %1003 = and i1 %1000, %1002
  br i1 %1003, label %FillExpr.loopBody-0354, label %FillExpr.loopEnd-0355

FillExpr.loopBody-0354:                           ; preds = %FillExpr.loopCmp-0353
  %1004 = load i32, ptr %475, align 4
  %1005 = getelementptr [4 x float], ptr %474, i32 0, i32 %1004
  store float 0.000000e+00, ptr %1005, align 4
  %1006 = load i32, ptr %475, align 4
  %1007 = add i32 %1006, 1
  store i32 %1007, ptr %475, align 4
  %1008 = load i32, ptr %476, align 4
  %1009 = add i32 %1008, 1
  store i32 %1009, ptr %476, align 4
  br label %FillExpr.loopCmp-0353

FillExpr.loopEnd-0355:                            ; preds = %FillExpr.loopCmp-0353
  br label %FillExpr.exit356

FillExpr.exit356:                                 ; preds = %FillExpr.loopEnd-0355
  %1010 = getelementptr [4 x float], ptr %474, i32 0, i32 0
  store float 0.000000e+00, ptr %1010, align 4
  %1011 = getelementptr [4 x float], ptr %474, i32 0, i32 1
  store float 0.000000e+00, ptr %1011, align 4
  %1012 = getelementptr [4 x float], ptr %474, i32 0, i32 2
  store float 6.005000e+03, ptr %1012, align 4
  %1013 = getelementptr [4 x float], ptr %474, i32 0, i32 3
  store float 2.376000e+03, ptr %1013, align 4
  %1014 = alloca [4 x float], align 4
  %1015 = alloca i32, align 4
  %1016 = alloca i32, align 4
  store i32 0, ptr %1016, align 4
  br label %FillExpr.loopStart-0357

FillExpr.loopStart-0357:                          ; preds = %FillExpr.exit356
  store i32 0, ptr %1015, align 4
  br label %FillExpr.loopCmp-0358

FillExpr.loopCmp-0358:                            ; preds = %FillExpr.loopBody-0359, %FillExpr.loopStart-0357
  %1017 = load i32, ptr %1015, align 4
  %1018 = icmp slt i32 %1017, 4
  %1019 = load i32, ptr %1016, align 4
  %1020 = icmp slt i32 %1019, 4
  %1021 = and i1 %1018, %1020
  br i1 %1021, label %FillExpr.loopBody-0359, label %FillExpr.loopEnd-0360

FillExpr.loopBody-0359:                           ; preds = %FillExpr.loopCmp-0358
  %1022 = load i32, ptr %1015, align 4
  %1023 = getelementptr [4 x float], ptr %1014, i32 0, i32 %1022
  store float 0.000000e+00, ptr %1023, align 4
  %1024 = load i32, ptr %1015, align 4
  %1025 = add i32 %1024, 1
  store i32 %1025, ptr %1015, align 4
  %1026 = load i32, ptr %1016, align 4
  %1027 = add i32 %1026, 1
  store i32 %1027, ptr %1016, align 4
  br label %FillExpr.loopCmp-0358

FillExpr.loopEnd-0360:                            ; preds = %FillExpr.loopCmp-0358
  br label %FillExpr.exit361

FillExpr.exit361:                                 ; preds = %FillExpr.loopEnd-0360
  %1028 = getelementptr [4 x float], ptr %1014, i32 0, i32 0
  store float 0.000000e+00, ptr %1028, align 4
  %1029 = getelementptr [4 x float], ptr %1014, i32 0, i32 1
  %screenHeight362 = load i32, ptr @screenHeight, align 4
  %1030 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if363, label %else364

if363:                                            ; preds = %FillExpr.exit361
  call void @raise_exception(ptr @42)
  br label %merge365

else364:                                          ; preds = %FillExpr.exit361
  %1031 = sitofp i32 %1030 to double
  %1032 = fdiv double %1031, 2.000000e+00
  br label %merge365

merge365:                                         ; preds = %else364, %if363
  %1033 = fptrunc double %1032 to float
  store float %1033, ptr %1029, align 4
  %1034 = getelementptr [4 x float], ptr %1014, i32 0, i32 2
  %screenWidth366 = load i32, ptr @screenWidth, align 4
  %1035 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if367, label %else368

if367:                                            ; preds = %merge365
  call void @raise_exception(ptr @43)
  br label %merge369

else368:                                          ; preds = %merge365
  %1036 = sitofp i32 %1035 to double
  %1037 = fdiv double %1036, 2.000000e+00
  br label %merge369

merge369:                                         ; preds = %else368, %if367
  %1038 = fptrunc double %1037 to float
  store float %1038, ptr %1034, align 4
  %1039 = getelementptr [4 x float], ptr %1014, i32 0, i32 3
  %screenHeight370 = load i32, ptr @screenHeight, align 4
  %1040 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if371, label %else372

if371:                                            ; preds = %merge369
  call void @raise_exception(ptr @44)
  br label %merge373

else372:                                          ; preds = %merge369
  %1041 = sitofp i32 %1040 to double
  %1042 = fdiv double %1041, 5.000000e+00
  br label %merge373

merge373:                                         ; preds = %else372, %if371
  %1043 = fptrunc double %1042 to float
  store float %1043, ptr %1039, align 4
  %1044 = alloca [2 x float], align 4
  %1045 = alloca i32, align 4
  %1046 = alloca i32, align 4
  store i32 0, ptr %1046, align 4
  br label %FillExpr.loopStart-0374

FillExpr.loopStart-0374:                          ; preds = %merge373
  store i32 0, ptr %1045, align 4
  br label %FillExpr.loopCmp-0375

FillExpr.loopCmp-0375:                            ; preds = %FillExpr.loopBody-0376, %FillExpr.loopStart-0374
  %1047 = load i32, ptr %1045, align 4
  %1048 = icmp slt i32 %1047, 2
  %1049 = load i32, ptr %1046, align 4
  %1050 = icmp slt i32 %1049, 2
  %1051 = and i1 %1048, %1050
  br i1 %1051, label %FillExpr.loopBody-0376, label %FillExpr.loopEnd-0377

FillExpr.loopBody-0376:                           ; preds = %FillExpr.loopCmp-0375
  %1052 = load i32, ptr %1045, align 4
  %1053 = getelementptr [2 x float], ptr %1044, i32 0, i32 %1052
  store float 0.000000e+00, ptr %1053, align 4
  %1054 = load i32, ptr %1045, align 4
  %1055 = add i32 %1054, 1
  store i32 %1055, ptr %1045, align 4
  %1056 = load i32, ptr %1046, align 4
  %1057 = add i32 %1056, 1
  store i32 %1057, ptr %1046, align 4
  br label %FillExpr.loopCmp-0375

FillExpr.loopEnd-0377:                            ; preds = %FillExpr.loopCmp-0375
  br label %FillExpr.exit378

FillExpr.exit378:                                 ; preds = %FillExpr.loopEnd-0377
  %1058 = getelementptr [2 x float], ptr %1044, i32 0, i32 0
  %1059 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 0
  %x379 = load float, ptr %1059, align 4
  %1060 = load float, ptr %1059, align 4
  store float %1060, ptr %1058, align 4
  %1061 = getelementptr [2 x float], ptr %1044, i32 0, i32 1
  %1062 = getelementptr inbounds %Position.4, ptr %mount1L3Pos1, i32 0, i32 1
  %y380 = load float, ptr %1062, align 4
  %1063 = load float, ptr %1062, align 4
  store float %1063, ptr %1061, align 4
  %1064 = alloca float, align 4
  store float 0.000000e+00, ptr %1064, align 4
  %1065 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %1066 = getelementptr inbounds %COLORS_TYPE.3, ptr %1065, i32 0, i32 0
  %WHITE381 = load i32, ptr %1066, align 4
  call void %473(ptr %mount2L2Texture, ptr %474, ptr %1014, ptr %1044, ptr %1064, ptr %1066, ptr %1)
  %1067 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1068 = icmp eq i32 %1067, 0
  br i1 %1068, label %checkContinueBlock106, label %afterNestedBlock80

FillExpr.loopStart-0382:                          ; preds = %nestedBlock107
  store i32 0, ptr %484, align 4
  br label %FillExpr.loopCmp-0383

FillExpr.loopCmp-0383:                            ; preds = %FillExpr.loopBody-0384, %FillExpr.loopStart-0382
  %1069 = load i32, ptr %484, align 4
  %1070 = icmp slt i32 %1069, 4
  %1071 = load i32, ptr %485, align 4
  %1072 = icmp slt i32 %1071, 4
  %1073 = and i1 %1070, %1072
  br i1 %1073, label %FillExpr.loopBody-0384, label %FillExpr.loopEnd-0385

FillExpr.loopBody-0384:                           ; preds = %FillExpr.loopCmp-0383
  %1074 = load i32, ptr %484, align 4
  %1075 = getelementptr [4 x float], ptr %483, i32 0, i32 %1074
  store float 0.000000e+00, ptr %1075, align 4
  %1076 = load i32, ptr %484, align 4
  %1077 = add i32 %1076, 1
  store i32 %1077, ptr %484, align 4
  %1078 = load i32, ptr %485, align 4
  %1079 = add i32 %1078, 1
  store i32 %1079, ptr %485, align 4
  br label %FillExpr.loopCmp-0383

FillExpr.loopEnd-0385:                            ; preds = %FillExpr.loopCmp-0383
  br label %FillExpr.exit386

FillExpr.exit386:                                 ; preds = %FillExpr.loopEnd-0385
  %1080 = getelementptr [4 x float], ptr %483, i32 0, i32 0
  store float 0.000000e+00, ptr %1080, align 4
  %1081 = getelementptr [4 x float], ptr %483, i32 0, i32 1
  store float 0.000000e+00, ptr %1081, align 4
  %1082 = getelementptr [4 x float], ptr %483, i32 0, i32 2
  store float 8.982000e+03, ptr %1082, align 4
  %1083 = getelementptr [4 x float], ptr %483, i32 0, i32 3
  store float 1.542000e+03, ptr %1083, align 4
  %1084 = alloca [4 x float], align 4
  %1085 = alloca i32, align 4
  %1086 = alloca i32, align 4
  store i32 0, ptr %1086, align 4
  br label %FillExpr.loopStart-0387

FillExpr.loopStart-0387:                          ; preds = %FillExpr.exit386
  store i32 0, ptr %1085, align 4
  br label %FillExpr.loopCmp-0388

FillExpr.loopCmp-0388:                            ; preds = %FillExpr.loopBody-0389, %FillExpr.loopStart-0387
  %1087 = load i32, ptr %1085, align 4
  %1088 = icmp slt i32 %1087, 4
  %1089 = load i32, ptr %1086, align 4
  %1090 = icmp slt i32 %1089, 4
  %1091 = and i1 %1088, %1090
  br i1 %1091, label %FillExpr.loopBody-0389, label %FillExpr.loopEnd-0390

FillExpr.loopBody-0389:                           ; preds = %FillExpr.loopCmp-0388
  %1092 = load i32, ptr %1085, align 4
  %1093 = getelementptr [4 x float], ptr %1084, i32 0, i32 %1092
  store float 0.000000e+00, ptr %1093, align 4
  %1094 = load i32, ptr %1085, align 4
  %1095 = add i32 %1094, 1
  store i32 %1095, ptr %1085, align 4
  %1096 = load i32, ptr %1086, align 4
  %1097 = add i32 %1096, 1
  store i32 %1097, ptr %1086, align 4
  br label %FillExpr.loopCmp-0388

FillExpr.loopEnd-0390:                            ; preds = %FillExpr.loopCmp-0388
  br label %FillExpr.exit391

FillExpr.exit391:                                 ; preds = %FillExpr.loopEnd-0390
  %1098 = getelementptr [4 x float], ptr %1084, i32 0, i32 0
  store float 0.000000e+00, ptr %1098, align 4
  %1099 = getelementptr [4 x float], ptr %1084, i32 0, i32 1
  %screenHeight392 = load i32, ptr @screenHeight, align 4
  %1100 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if393, label %else394

if393:                                            ; preds = %FillExpr.exit391
  call void @raise_exception(ptr @45)
  br label %merge395

else394:                                          ; preds = %FillExpr.exit391
  %1101 = sitofp i32 %1100 to double
  %1102 = fdiv double %1101, 2.000000e+00
  br label %merge395

merge395:                                         ; preds = %else394, %if393
  %1103 = fptrunc double %1102 to float
  store float %1103, ptr %1099, align 4
  %1104 = getelementptr [4 x float], ptr %1084, i32 0, i32 2
  %screenWidth396 = load i32, ptr @screenWidth, align 4
  %1105 = load i32, ptr @screenWidth, align 4
  %screenWidth397 = load i32, ptr @screenWidth, align 4
  %1106 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if398, label %else399

if398:                                            ; preds = %merge395
  call void @raise_exception(ptr @46)
  br label %merge400

else399:                                          ; preds = %merge395
  %1107 = sitofp i32 %1106 to double
  %1108 = fdiv double %1107, 2.000000e+00
  br label %merge400

merge400:                                         ; preds = %else399, %if398
  %1109 = sitofp i32 %1105 to double
  %1110 = fadd double %1109, %1108
  %1111 = fptrunc double %1110 to float
  store float %1111, ptr %1104, align 4
  %1112 = getelementptr [4 x float], ptr %1084, i32 0, i32 3
  %screenHeight401 = load i32, ptr @screenHeight, align 4
  %1113 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if402, label %else403

if402:                                            ; preds = %merge400
  call void @raise_exception(ptr @47)
  br label %merge404

else403:                                          ; preds = %merge400
  %1114 = sitofp i32 %1113 to double
  %1115 = fdiv double %1114, 5.000000e+00
  br label %merge404

merge404:                                         ; preds = %else403, %if402
  %1116 = fptrunc double %1115 to float
  store float %1116, ptr %1112, align 4
  %1117 = alloca [2 x float], align 4
  %1118 = alloca i32, align 4
  %1119 = alloca i32, align 4
  store i32 0, ptr %1119, align 4
  br label %FillExpr.loopStart-0405

FillExpr.loopStart-0405:                          ; preds = %merge404
  store i32 0, ptr %1118, align 4
  br label %FillExpr.loopCmp-0406

FillExpr.loopCmp-0406:                            ; preds = %FillExpr.loopBody-0407, %FillExpr.loopStart-0405
  %1120 = load i32, ptr %1118, align 4
  %1121 = icmp slt i32 %1120, 2
  %1122 = load i32, ptr %1119, align 4
  %1123 = icmp slt i32 %1122, 2
  %1124 = and i1 %1121, %1123
  br i1 %1124, label %FillExpr.loopBody-0407, label %FillExpr.loopEnd-0408

FillExpr.loopBody-0407:                           ; preds = %FillExpr.loopCmp-0406
  %1125 = load i32, ptr %1118, align 4
  %1126 = getelementptr [2 x float], ptr %1117, i32 0, i32 %1125
  store float 0.000000e+00, ptr %1126, align 4
  %1127 = load i32, ptr %1118, align 4
  %1128 = add i32 %1127, 1
  store i32 %1128, ptr %1118, align 4
  %1129 = load i32, ptr %1119, align 4
  %1130 = add i32 %1129, 1
  store i32 %1130, ptr %1119, align 4
  br label %FillExpr.loopCmp-0406

FillExpr.loopEnd-0408:                            ; preds = %FillExpr.loopCmp-0406
  br label %FillExpr.exit409

FillExpr.exit409:                                 ; preds = %FillExpr.loopEnd-0408
  %1131 = getelementptr [2 x float], ptr %1117, i32 0, i32 0
  %1132 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 0
  %x410 = load float, ptr %1132, align 4
  %1133 = load float, ptr %1132, align 4
  store float %1133, ptr %1131, align 4
  %1134 = getelementptr [2 x float], ptr %1117, i32 0, i32 1
  %1135 = getelementptr inbounds %Position.4, ptr %mountL1Pos1, i32 0, i32 1
  %y411 = load float, ptr %1135, align 4
  %1136 = load float, ptr %1135, align 4
  store float %1136, ptr %1134, align 4
  %1137 = alloca float, align 4
  store float 0.000000e+00, ptr %1137, align 4
  %1138 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %1139 = getelementptr inbounds %COLORS_TYPE.3, ptr %1138, i32 0, i32 0
  %WHITE412 = load i32, ptr %1139, align 4
  call void %482(ptr %mountL1Texture, ptr %483, ptr %1084, ptr %1117, ptr %1137, ptr %1139, ptr %1)
  %1140 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1141 = icmp eq i32 %1140, 0
  br i1 %1141, label %checkContinueBlock108, label %afterNestedBlock80

FillExpr.loopStart-0413:                          ; preds = %nestedBlock109
  store i32 0, ptr %493, align 4
  br label %FillExpr.loopCmp-0414

FillExpr.loopCmp-0414:                            ; preds = %FillExpr.loopBody-0415, %FillExpr.loopStart-0413
  %1142 = load i32, ptr %493, align 4
  %1143 = icmp slt i32 %1142, 4
  %1144 = load i32, ptr %494, align 4
  %1145 = icmp slt i32 %1144, 4
  %1146 = and i1 %1143, %1145
  br i1 %1146, label %FillExpr.loopBody-0415, label %FillExpr.loopEnd-0416

FillExpr.loopBody-0415:                           ; preds = %FillExpr.loopCmp-0414
  %1147 = load i32, ptr %493, align 4
  %1148 = getelementptr [4 x float], ptr %492, i32 0, i32 %1147
  store float 0.000000e+00, ptr %1148, align 4
  %1149 = load i32, ptr %493, align 4
  %1150 = add i32 %1149, 1
  store i32 %1150, ptr %493, align 4
  %1151 = load i32, ptr %494, align 4
  %1152 = add i32 %1151, 1
  store i32 %1152, ptr %494, align 4
  br label %FillExpr.loopCmp-0414

FillExpr.loopEnd-0416:                            ; preds = %FillExpr.loopCmp-0414
  br label %FillExpr.exit417

FillExpr.exit417:                                 ; preds = %FillExpr.loopEnd-0416
  %1153 = getelementptr [4 x float], ptr %492, i32 0, i32 0
  store float 0.000000e+00, ptr %1153, align 4
  %1154 = getelementptr [4 x float], ptr %492, i32 0, i32 1
  store float 0.000000e+00, ptr %1154, align 4
  %1155 = getelementptr [4 x float], ptr %492, i32 0, i32 2
  store float 8.982000e+03, ptr %1155, align 4
  %1156 = getelementptr [4 x float], ptr %492, i32 0, i32 3
  store float 1.542000e+03, ptr %1156, align 4
  %1157 = alloca [4 x float], align 4
  %1158 = alloca i32, align 4
  %1159 = alloca i32, align 4
  store i32 0, ptr %1159, align 4
  br label %FillExpr.loopStart-0418

FillExpr.loopStart-0418:                          ; preds = %FillExpr.exit417
  store i32 0, ptr %1158, align 4
  br label %FillExpr.loopCmp-0419

FillExpr.loopCmp-0419:                            ; preds = %FillExpr.loopBody-0420, %FillExpr.loopStart-0418
  %1160 = load i32, ptr %1158, align 4
  %1161 = icmp slt i32 %1160, 4
  %1162 = load i32, ptr %1159, align 4
  %1163 = icmp slt i32 %1162, 4
  %1164 = and i1 %1161, %1163
  br i1 %1164, label %FillExpr.loopBody-0420, label %FillExpr.loopEnd-0421

FillExpr.loopBody-0420:                           ; preds = %FillExpr.loopCmp-0419
  %1165 = load i32, ptr %1158, align 4
  %1166 = getelementptr [4 x float], ptr %1157, i32 0, i32 %1165
  store float 0.000000e+00, ptr %1166, align 4
  %1167 = load i32, ptr %1158, align 4
  %1168 = add i32 %1167, 1
  store i32 %1168, ptr %1158, align 4
  %1169 = load i32, ptr %1159, align 4
  %1170 = add i32 %1169, 1
  store i32 %1170, ptr %1159, align 4
  br label %FillExpr.loopCmp-0419

FillExpr.loopEnd-0421:                            ; preds = %FillExpr.loopCmp-0419
  br label %FillExpr.exit422

FillExpr.exit422:                                 ; preds = %FillExpr.loopEnd-0421
  %1171 = getelementptr [4 x float], ptr %1157, i32 0, i32 0
  store float 0.000000e+00, ptr %1171, align 4
  %1172 = getelementptr [4 x float], ptr %1157, i32 0, i32 1
  %screenHeight423 = load i32, ptr @screenHeight, align 4
  %1173 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if424, label %else425

if424:                                            ; preds = %FillExpr.exit422
  call void @raise_exception(ptr @48)
  br label %merge426

else425:                                          ; preds = %FillExpr.exit422
  %1174 = sitofp i32 %1173 to double
  %1175 = fdiv double %1174, 2.000000e+00
  br label %merge426

merge426:                                         ; preds = %else425, %if424
  %1176 = fptrunc double %1175 to float
  store float %1176, ptr %1172, align 4
  %1177 = getelementptr [4 x float], ptr %1157, i32 0, i32 2
  %screenWidth427 = load i32, ptr @screenWidth, align 4
  %1178 = load i32, ptr @screenWidth, align 4
  %screenWidth428 = load i32, ptr @screenWidth, align 4
  %1179 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if429, label %else430

if429:                                            ; preds = %merge426
  call void @raise_exception(ptr @49)
  br label %merge431

else430:                                          ; preds = %merge426
  %1180 = sitofp i32 %1179 to double
  %1181 = fdiv double %1180, 2.000000e+00
  br label %merge431

merge431:                                         ; preds = %else430, %if429
  %1182 = sitofp i32 %1178 to double
  %1183 = fadd double %1182, %1181
  %1184 = fptrunc double %1183 to float
  store float %1184, ptr %1177, align 4
  %1185 = getelementptr [4 x float], ptr %1157, i32 0, i32 3
  %screenHeight432 = load i32, ptr @screenHeight, align 4
  %1186 = load i32, ptr @screenHeight, align 4
  br i1 false, label %if433, label %else434

if433:                                            ; preds = %merge431
  call void @raise_exception(ptr @50)
  br label %merge435

else434:                                          ; preds = %merge431
  %1187 = sitofp i32 %1186 to double
  %1188 = fdiv double %1187, 5.000000e+00
  br label %merge435

merge435:                                         ; preds = %else434, %if433
  %1189 = fptrunc double %1188 to float
  store float %1189, ptr %1185, align 4
  %1190 = alloca [2 x float], align 4
  %1191 = alloca i32, align 4
  %1192 = alloca i32, align 4
  store i32 0, ptr %1192, align 4
  br label %FillExpr.loopStart-0436

FillExpr.loopStart-0436:                          ; preds = %merge435
  store i32 0, ptr %1191, align 4
  br label %FillExpr.loopCmp-0437

FillExpr.loopCmp-0437:                            ; preds = %FillExpr.loopBody-0438, %FillExpr.loopStart-0436
  %1193 = load i32, ptr %1191, align 4
  %1194 = icmp slt i32 %1193, 2
  %1195 = load i32, ptr %1192, align 4
  %1196 = icmp slt i32 %1195, 2
  %1197 = and i1 %1194, %1196
  br i1 %1197, label %FillExpr.loopBody-0438, label %FillExpr.loopEnd-0439

FillExpr.loopBody-0438:                           ; preds = %FillExpr.loopCmp-0437
  %1198 = load i32, ptr %1191, align 4
  %1199 = getelementptr [2 x float], ptr %1190, i32 0, i32 %1198
  store float 0.000000e+00, ptr %1199, align 4
  %1200 = load i32, ptr %1191, align 4
  %1201 = add i32 %1200, 1
  store i32 %1201, ptr %1191, align 4
  %1202 = load i32, ptr %1192, align 4
  %1203 = add i32 %1202, 1
  store i32 %1203, ptr %1192, align 4
  br label %FillExpr.loopCmp-0437

FillExpr.loopEnd-0439:                            ; preds = %FillExpr.loopCmp-0437
  br label %FillExpr.exit440

FillExpr.exit440:                                 ; preds = %FillExpr.loopEnd-0439
  %1204 = getelementptr [2 x float], ptr %1190, i32 0, i32 0
  %1205 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 0
  %x441 = load float, ptr %1205, align 4
  %1206 = load float, ptr %1205, align 4
  store float %1206, ptr %1204, align 4
  %1207 = getelementptr [2 x float], ptr %1190, i32 0, i32 1
  %1208 = getelementptr inbounds %Position.4, ptr %mountL1Pos2, i32 0, i32 1
  %y442 = load float, ptr %1208, align 4
  %1209 = load float, ptr %1208, align 4
  store float %1209, ptr %1207, align 4
  %1210 = alloca float, align 4
  store float 0.000000e+00, ptr %1210, align 4
  %1211 = getelementptr inbounds %FlowWingAnim, ptr %1, i32 0, i32 5
  %1212 = getelementptr inbounds %COLORS_TYPE.3, ptr %1211, i32 0, i32 0
  %WHITE443 = load i32, ptr %1212, align 4
  call void %491(ptr %mountL1Texture, ptr %492, ptr %1157, ptr %1190, ptr %1210, ptr %1212, ptr %1)
  %1213 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1214 = icmp eq i32 %1213, 0
  br i1 %1214, label %checkContinueBlock110, label %afterNestedBlock80

decrement_block450:                               ; preds = %while.end
  %1215 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1216 = sub i32 %1215, 1
  store i32 %1216, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block451

end_block451:                                     ; preds = %decrement_block450, %while.end
  %1217 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1218 = icmp eq i32 %1217, 0
  br i1 %1218, label %checkContinueBlock32, label %afterNestedBlock

returnBlock452:                                   ; preds = %nestedBlock35
  store i32 0, ptr %0, align 4
  ret void

mergeBlock453:                                    ; No predecessors!
  %1219 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1220 = icmp eq i32 %1219, 0
  br i1 %1220, label %checkContinueBlock36, label %afterNestedBlock
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
!61 = !{!"Bird.updateY:rt:pr:27"}
!62 = !{!"main:rt:pr:28"}
