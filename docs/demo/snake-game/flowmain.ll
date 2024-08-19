; ModuleID = 'flowmain'
source_filename = "flowmain"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%Position.4 = type { i32, i32 }
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
@side = common global i32 0
@BIRD_SIZE = common global float 0.000000e+00
@"_fg_i:0" = common global i32 0
@"_fg_numberOfElementsFilled:" = common global i32 0
@0 = private unnamed_addr constant [696 x i8] c"\0A\1B[33m25| \1B[0m\1B[0m  const speed = 10\0A\1B[0m\1B[33m26| \1B[0m\1B[0m  var tail: int = 1\0A\1B[0m\1B[33m27| \1B[0m\1B[0m  var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m29| \1B[0m\1B[31m\1B[1m  posX[0]= 0\0A\1B[0m\1B[32m\1B[1m        \0A   ~~~~~~~^\1B[0m\0A\1B[33m30| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m31| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m32| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m33| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 29:8\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@1 = private unnamed_addr constant [692 x i8] c"\0A\1B[33m26| \1B[0m\1B[0m  var tail: int = 1\0A\1B[0m\1B[33m27| \1B[0m\1B[0m  var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  posX[0]= 0\0A\1B[0m\1B[33m30| \1B[0m\1B[31m\1B[1m  posY[0]= 0\0A\1B[0m\1B[32m\1B[1m        \0A   ~~~~~~~^\1B[0m\0A\1B[33m31| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m32| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m33| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[33m34| \1B[0m\1B[0m    y: posY[0]\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 30:8\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [734 x i8] c"\0A\1B[33m29| \1B[0m\1B[0m  posX[0]= 0\0A\1B[0m\1B[33m30| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m31| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m32| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m33| \1B[0m\1B[31m\1B[1m    x: posX[0],\0A\1B[0m\1B[32m\1B[1m             \0A   ~~~~~~~~~~~~^\1B[0m\0A\1B[33m34| \1B[0m\1B[0m    y: posY[0]\0A\1B[0m\1B[33m35| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m36| \1B[0m\1B[0m  const fgAnim: FlowWingAnim = new FlowWingAnim(screenWidth, screenHeight, \22snake-game-in-flowwing\22, 60)\0A\1B[0m\1B[33m37| \1B[0m\1B[0m  fgAnim.createWindow()\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 33:13\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [761 x i8] c"\0A\1B[33m30| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m31| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m32| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m33| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[33m34| \1B[0m\1B[31m\1B[1m    y: posY[0]\0A\1B[0m\1B[32m\1B[1m             \0A   ~~~~~~~~~~~~^\1B[0m\0A\1B[33m35| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m36| \1B[0m\1B[0m  const fgAnim: FlowWingAnim = new FlowWingAnim(screenWidth, screenHeight, \22snake-game-in-flowwing\22, 60)\0A\1B[0m\1B[33m37| \1B[0m\1B[0m  fgAnim.createWindow()\0A\1B[0m\1B[33m38| \1B[0m\1B[0m  while (!fgAnim.windowShouldClose()) {\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 34:13\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@8 = private unnamed_addr constant [643 x i8] c"\0A\1B[33m76| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m77| \1B[0m\1B[0m\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m80| \1B[0m\1B[31m\1B[1m        posX[index]= posX[index - 1]\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m81| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m82| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m83| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 80:14\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [685 x i8] c"\0A\1B[33m76| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m77| \1B[0m\1B[0m\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m80| \1B[0m\1B[31m\1B[1m        posX[index]= posX[index - 1]\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m81| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m82| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m83| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 80:35\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [659 x i8] c"\0A\1B[33m77| \1B[0m\1B[0m\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m80| \1B[0m\1B[0m        posX[index]= posX[index - 1]\0A\1B[0m\1B[33m81| \1B[0m\1B[31m\1B[1m        posY[index]= posY[index - 1]\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m82| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m83| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 81:14\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [701 x i8] c"\0A\1B[33m77| \1B[0m\1B[0m\0A\1B[0m\1B[33m78| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m80| \1B[0m\1B[0m        posX[index]= posX[index - 1]\0A\1B[0m\1B[33m81| \1B[0m\1B[31m\1B[1m        posY[index]= posY[index - 1]\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m82| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m83| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 81:35\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [678 x i8] c"\0A\1B[33m81| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m82| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m83| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[31m\1B[1m    posX[0]= newPos.x\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m86| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m87| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 85:10\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [726 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m83| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    posY[0]= newPos.y\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m90| \1B[0m\1B[0m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 86:10\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [921 x i8] c"\0A\1B[33m86| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m87| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m90| \1B[0m\1B[31m\1B[1m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[32m\1B[1m                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m91| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[33m93| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m94| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 90:33\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [947 x i8] c"\0A\1B[33m86| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m87| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m90| \1B[0m\1B[31m\1B[1m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m91| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[33m93| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m94| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[31mFile: snake.fg [Error] : \1B[1;31mLine 90:46\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/snake.fg\0A\1B[0m\00", align 1

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
  store i32 0, ptr @side, align 4
  store float 0.000000e+00, ptr @BIRD_SIZE, align 4
  %rtPtr = alloca i32, align 4
  %0 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-snake-game-FlowWingAnim()
  %1 = call i32 @-Users-apple-code-per-Flow-Wing-docs-demo-snake-game-random()
  store i32 1000, ptr @screenWidth, align 4
  store i32 500, ptr @screenHeight, align 4
  store i32 10, ptr @side, align 4
  store float 3.600000e+02, ptr @BIRD_SIZE, align 4
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

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-snake-game-FlowWingAnim()

declare i32 @-Users-apple-code-per-Flow-Wing-docs-demo-snake-game-random()

declare !rt !25 void @getRandomNumber(ptr, ptr, ptr)

define void @getFoodPosition(ptr sret(%Position.4) %0) !rt !26 {
entry:
  %pos = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %pos)
  %rtPtr = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %rtPtr1 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock7, %mergeBlock, %checkContinueBlock5, %nestedBlock4, %checkContinueBlock3, %nestedBlock2, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %6 = load i32, ptr @screenWidth, align 4
  %7 = sub i32 %6, 1
  store i32 %7, ptr %2, align 4
  call void @getRandomNumber(ptr %5, ptr %1, ptr %2)
  %8 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 1
  store i32 0, ptr %3, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %9 = load i32, ptr @screenHeight, align 4
  %10 = sub i32 %9, 1
  store i32 %10, ptr %4, align 4
  call void @getRandomNumber(ptr %8, ptr %3, ptr %4)
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %13 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  %15 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 0
  %x = load i32, ptr %15, align 4
  %16 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 0
  %x8 = load i32, ptr %16, align 4
  %17 = load i32, ptr %16, align 4
  %18 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 0
  %x9 = load i32, ptr %18, align 4
  %19 = load i32, ptr %18, align 4
  %side = load i32, ptr @side, align 4
  %20 = load i32, ptr @side, align 4
  %21 = srem i32 %19, %20
  %22 = sub i32 %17, %21
  store i32 %22, ptr %15, align 4
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock3, label %afterNestedBlock

checkContinueBlock3:                              ; preds = %nestedBlock2
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock3
  %27 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 1
  %y = load i32, ptr %27, align 4
  %28 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 1
  %y10 = load i32, ptr %28, align 4
  %29 = load i32, ptr %28, align 4
  %30 = getelementptr inbounds %Position.4, ptr %pos, i32 0, i32 1
  %y11 = load i32, ptr %30, align 4
  %31 = load i32, ptr %30, align 4
  %side12 = load i32, ptr @side, align 4
  %32 = load i32, ptr @side, align 4
  %33 = srem i32 %31, %32
  %34 = sub i32 %29, %33
  store i32 %34, ptr %27, align 4
  %35 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %checkContinueBlock5, label %afterNestedBlock

checkContinueBlock5:                              ; preds = %nestedBlock4
  %37 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  br label %returnBlock

checkContinueBlock7:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock6
  %39 = load %Position.4, ptr %pos, align 4
  store %Position.4 %39, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock7, label %afterNestedBlock
}

define void @main(ptr %0) !rt !27 {
entry:
  %speed = alloca %DynamicType, align 8
  %tail = alloca i32, align 4
  store i32 0, ptr %tail, align 4
  %posX = alloca [10000 x i32], align 4
  call void @"assign_<Array[10000]<'Integer32'>>:10000,"(ptr %posX)
  %posY = alloca [10000 x i32], align 4
  call void @"assign_<Array[10000]<'Integer32'>>:10000,"(ptr %posY)
  %foodPos = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %foodPos)
  %newPos = alloca %Position.4, align 8
  call void @"assign_<ObjectPosition.4>"(ptr %newPos)
  %fgAnim = alloca ptr, align 8
  %1 = alloca ptr, align 8
  %2 = alloca i32, align 4
  %rtPtr = alloca i1, align 1
  %isKeyPressed = alloca %DynamicType, align 8
  %rtPtr1 = alloca i1, align 1
  %rtPtr2 = alloca i1, align 1
  %rtPtr3 = alloca i1, align 1
  %rtPtr4 = alloca i1, align 1
  %rtPtr5 = alloca i1, align 1
  %rtPtr6 = alloca i1, align 1
  %rtPtr7 = alloca i1, align 1
  %rtPtr8 = alloca i1, align 1
  %rtPtr9 = alloca %Position.4, align 8
  %index = alloca i32, align 4
  store i32 0, ptr %index, align 4
  %index10 = alloca i32, align 4
  store i32 0, ptr %index10, align 4
  %index11 = alloca i32, align 4
  store i32 0, ptr %index11, align 4
  %index12 = alloca i32, align 4
  store i32 0, ptr %index12, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca float, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock36, %mergeBlock, %checkContinueBlock34, %nestedBlock33, %checkContinueBlock32, %end_block263, %checkContinueBlock30, %nestedBlock29, %checkContinueBlock28, %nestedBlock27, %checkContinueBlock26, %"GlobalIndexExpr::merge54", %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %"GlobalIndexExpr::merge46", %checkContinueBlock20, %"GlobalIndexExpr::merge", %checkContinueBlock18, %FillExpr.exit41, %checkContinueBlock16, %FillExpr.exit, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  store i32 10, ptr %6, align 4
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %9 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock
  store i32 1, ptr %tail, align 4
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %13 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  store i32 0, ptr @"_fg_i:0", align 4
  store i32 0, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopStart-0

checkContinueBlock16:                             ; preds = %FillExpr.exit
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  store i32 0, ptr @"_fg_i:0", align 4
  store i32 0, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopStart-037

checkContinueBlock18:                             ; preds = %FillExpr.exit41
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %posX42 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock20:                             ; preds = %"GlobalIndexExpr::merge"
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %posY43 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then44", label %"GlobalIndexExpr::else45"

checkContinueBlock22:                             ; preds = %"GlobalIndexExpr::merge46"
  %21 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  call void @getFoodPosition(ptr %foodPos)
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  %27 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %posX47 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then48", label %"GlobalIndexExpr::else49"

checkContinueBlock26:                             ; preds = %"GlobalIndexExpr::merge54"
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock27, label %afterNestedBlock

nestedBlock27:                                    ; preds = %checkContinueBlock26
  %30 = call ptr @malloc(i64 96)
  call void @"assign_<Class<FlowWingAnim>>"(ptr %30)
  %31 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %31, align 8
  %32 = load ptr, ptr %31, align 8
  %33 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 23
  store ptr @FlowWingAnim.setTargetFPS, ptr %33, align 8
  %34 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 22
  store ptr @FlowWingAnim.endDrawing, ptr %34, align 8
  %35 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 21
  store ptr @FlowWingAnim.createWindow, ptr %35, align 8
  %36 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %36, align 8
  %37 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 20
  store ptr @FlowWingAnim.drawTexturePro, ptr %37, align 8
  %38 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 16
  store ptr @FlowWingAnim.drawRectangle, ptr %38, align 8
  %39 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 15
  store ptr @FlowWingAnim.beginDrawing, ptr %39, align 8
  %40 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 1
  store ptr @FlowWingAnim.traceLog, ptr %40, align 8
  %41 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 14
  store ptr @FlowWingAnim.unloadTexture, ptr %41, align 8
  %42 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 13
  store ptr @FlowWingAnim.closeWindow, ptr %42, align 8
  %43 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 17
  store ptr @FlowWingAnim.getColor, ptr %43, align 8
  %44 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 12
  store ptr @FlowWingAnim.textFormat, ptr %44, align 8
  %45 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 18
  store ptr @FlowWingAnim.windowShouldClose, ptr %45, align 8
  %46 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenWidth, ptr %46, align 8
  %47 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenHeight, ptr %47, align 8
  %48 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 11
  store ptr @FlowWingAnim.getTime, ptr %48, align 8
  %49 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 19
  store ptr @FlowWingAnim.beforeInit, ptr %49, align 8
  %50 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 10
  store ptr @FlowWingAnim.clearBackground, ptr %50, align 8
  %51 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 7
  store ptr @FlowWingAnim.drawTexture, ptr %51, align 8
  %52 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 8
  store ptr @FlowWingAnim.getFrameTime, ptr %52, align 8
  %53 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 2
  store ptr @FlowWingAnim.drawText, ptr %53, align 8
  %54 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %54, align 8
  %55 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 9
  store ptr @FlowWingAnim.loadTexture, ptr %55, align 8
  %56 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %32, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %56, align 8
  %57 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 1
  store i32 0, ptr %57, align 4
  %58 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 2
  store i32 0, ptr %58, align 4
  %59 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 3
  store ptr @6, ptr %59, align 8
  %60 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 4
  store i32 0, ptr %60, align 4
  %61 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 5
  call void @"assign_<ObjectCOLORS_TYPE.3>"(ptr %61)
  %62 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 6
  call void @"assign_<ObjectKEYS_TYPE.2>"(ptr %62)
  %63 = getelementptr inbounds %FlowWingAnim, ptr %30, i32 0, i32 7
  call void @"assign_<ObjectLOG_TYPE.1>"(ptr %63)
  store ptr %30, ptr %fgAnim, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  store ptr @7, ptr %1, align 8
  store i32 60, ptr %2, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %1, ptr %2, ptr %fgAnim)
  %64 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %65 = icmp eq i32 %64, 0
  br i1 %65, label %checkContinueBlock28, label %afterNestedBlock

checkContinueBlock28:                             ; preds = %nestedBlock27
  %66 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %nestedBlock29, label %afterNestedBlock

nestedBlock29:                                    ; preds = %checkContinueBlock28
  %68 = load ptr, ptr %fgAnim, align 8
  %69 = getelementptr inbounds %FlowWingAnim, ptr %68, i32 0, i32 0
  %70 = load ptr, ptr %69, align 8
  %71 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %70, i32 0, i32 21
  %72 = load ptr, ptr %71, align 8
  call void %72(ptr %fgAnim)
  %73 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %74 = icmp eq i32 %73, 0
  br i1 %74, label %checkContinueBlock30, label %afterNestedBlock

checkContinueBlock30:                             ; preds = %nestedBlock29
  %75 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %nestedBlock31, label %afterNestedBlock

nestedBlock31:                                    ; preds = %checkContinueBlock30
  br label %"while:conditon"

checkContinueBlock32:                             ; preds = %end_block263
  %77 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %nestedBlock33, label %afterNestedBlock

nestedBlock33:                                    ; preds = %checkContinueBlock32
  %79 = load ptr, ptr %fgAnim, align 8
  %80 = getelementptr inbounds %FlowWingAnim, ptr %79, i32 0, i32 0
  %81 = load ptr, ptr %80, align 8
  %82 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %81, i32 0, i32 13
  %83 = load ptr, ptr %82, align 8
  call void %83(ptr %fgAnim)
  %84 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %85 = icmp eq i32 %84, 0
  br i1 %85, label %checkContinueBlock34, label %afterNestedBlock

checkContinueBlock34:                             ; preds = %nestedBlock33
  %86 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %87 = icmp eq i32 %86, 0
  br i1 %87, label %nestedBlock35, label %afterNestedBlock

nestedBlock35:                                    ; preds = %checkContinueBlock34
  br label %returnBlock

checkContinueBlock36:                             ; preds = %mergeBlock
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock15
  store i32 0, ptr @"_fg_i:0", align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %88 = load i32, ptr @"_fg_i:0", align 4
  %89 = icmp slt i32 %88, 10000
  %90 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %91 = icmp slt i32 %90, 10000
  %92 = and i1 %89, %91
  br i1 %92, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %93 = load i32, ptr @"_fg_i:0", align 4
  %94 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %93
  store i32 -1, ptr %94, align 4
  %95 = load i32, ptr @"_fg_i:0", align 4
  %96 = add i32 %95, 1
  store i32 %96, ptr @"_fg_i:0", align 4
  %97 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %98 = add i32 %97, 1
  store i32 %98, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %99 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %100 = icmp eq i32 %99, 0
  br i1 %100, label %checkContinueBlock16, label %afterNestedBlock

FillExpr.loopStart-037:                           ; preds = %nestedBlock17
  store i32 0, ptr @"_fg_i:0", align 4
  br label %FillExpr.loopCmp-038

FillExpr.loopCmp-038:                             ; preds = %FillExpr.loopBody-039, %FillExpr.loopStart-037
  %101 = load i32, ptr @"_fg_i:0", align 4
  %102 = icmp slt i32 %101, 10000
  %103 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %104 = icmp slt i32 %103, 10000
  %105 = and i1 %102, %104
  br i1 %105, label %FillExpr.loopBody-039, label %FillExpr.loopEnd-040

FillExpr.loopBody-039:                            ; preds = %FillExpr.loopCmp-038
  %106 = load i32, ptr @"_fg_i:0", align 4
  %107 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %106
  store i32 -1, ptr %107, align 4
  %108 = load i32, ptr @"_fg_i:0", align 4
  %109 = add i32 %108, 1
  store i32 %109, ptr @"_fg_i:0", align 4
  %110 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %111 = add i32 %110, 1
  store i32 %111, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopCmp-038

FillExpr.loopEnd-040:                             ; preds = %FillExpr.loopCmp-038
  br label %FillExpr.exit41

FillExpr.exit41:                                  ; preds = %FillExpr.loopEnd-040
  %112 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %113 = icmp eq i32 %112, 0
  br i1 %113, label %checkContinueBlock18, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %nestedBlock19
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock19
  call void @raise_exception(ptr @0)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %114 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %115 = load i32, ptr %114, align 4
  store i32 0, ptr %114, align 4
  %116 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %117 = icmp eq i32 %116, 0
  br i1 %117, label %checkContinueBlock20, label %afterNestedBlock

"GlobalIndexExpr::then44":                        ; preds = %nestedBlock21
  br label %"GlobalIndexExpr::merge46"

"GlobalIndexExpr::else45":                        ; preds = %nestedBlock21
  call void @raise_exception(ptr @1)
  br label %"GlobalIndexExpr::merge46"

"GlobalIndexExpr::merge46":                       ; preds = %"GlobalIndexExpr::else45", %"GlobalIndexExpr::then44"
  %118 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %119 = load i32, ptr %118, align 4
  store i32 0, ptr %118, align 4
  %120 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %121 = icmp eq i32 %120, 0
  br i1 %121, label %checkContinueBlock22, label %afterNestedBlock

"GlobalIndexExpr::then48":                        ; preds = %nestedBlock25
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::else49":                        ; preds = %nestedBlock25
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::merge50":                       ; preds = %"GlobalIndexExpr::else49", %"GlobalIndexExpr::then48"
  %122 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %123 = load i32, ptr %122, align 4
  %124 = load i32, ptr %122, align 4
  store i32 %124, ptr %27, align 4
  %125 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %posY51 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then52", label %"GlobalIndexExpr::else53"

"GlobalIndexExpr::then52":                        ; preds = %"GlobalIndexExpr::merge50"
  br label %"GlobalIndexExpr::merge54"

"GlobalIndexExpr::else53":                        ; preds = %"GlobalIndexExpr::merge50"
  call void @raise_exception(ptr @3)
  br label %"GlobalIndexExpr::merge54"

"GlobalIndexExpr::merge54":                       ; preds = %"GlobalIndexExpr::else53", %"GlobalIndexExpr::then52"
  %126 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %127 = load i32, ptr %126, align 4
  %128 = load i32, ptr %126, align 4
  store i32 %128, ptr %125, align 4
  %129 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %checkContinueBlock26, label %afterNestedBlock

"while:conditon":                                 ; preds = %afterNestedBlock55, %nestedBlock31
  %131 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %132 = icmp eq i32 %131, 0
  br i1 %132, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock56

while.end:                                        ; preds = %afterNestedBlock55, %end_block
  %133 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %134 = icmp eq i32 %133, 0
  br i1 %134, label %end_block263, label %decrement_block262

decrement_block:                                  ; preds = %"while:conditon"
  %135 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %136 = sub i32 %135, 1
  store i32 %136, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %137 = load ptr, ptr %fgAnim, align 8
  %138 = getelementptr inbounds %FlowWingAnim, ptr %137, i32 0, i32 0
  %139 = load ptr, ptr %138, align 8
  %140 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %139, i32 0, i32 18
  %141 = load ptr, ptr %140, align 8
  call void %141(ptr %rtPtr, ptr %fgAnim)
  %142 = load i1, ptr %rtPtr, align 1
  %143 = xor i1 %142, true
  br i1 %143, label %"while:body", label %while.end

afterNestedBlock55:                               ; preds = %checkContinueBlock87, %nestedBlock86, %checkContinueBlock85, %nestedBlock84, %checkContinueBlock83, %nestedBlock82, %checkContinueBlock81, %end_block256, %checkContinueBlock79, %nestedBlock78, %checkContinueBlock77, %nestedBlock76, %checkContinueBlock75, %"GlobalIndexExpr::merge222", %checkContinueBlock73, %"GlobalIndexExpr::merge217", %checkContinueBlock71, %afterIfElse170, %checkContinueBlock69, %afterIfElse160, %checkContinueBlock67, %afterIfElse148, %checkContinueBlock65, %afterIfElse139, %checkContinueBlock63, %afterIfElse130, %checkContinueBlock61, %afterIfElse121, %checkContinueBlock59, %afterIfElse, %checkContinueBlock57, %nestedBlock56
  %144 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %145 = icmp eq i32 %144, 0
  br i1 %145, label %"while:conditon", label %while.end

nestedBlock56:                                    ; preds = %"while:body"
  %146 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 false, ptr %146, align 1
  %147 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %148 = icmp eq i32 %147, 0
  br i1 %148, label %checkContinueBlock57, label %afterNestedBlock55

checkContinueBlock57:                             ; preds = %nestedBlock56
  %149 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %150 = icmp eq i32 %149, 0
  br i1 %150, label %nestedBlock58, label %afterNestedBlock55

nestedBlock58:                                    ; preds = %checkContinueBlock57
  %151 = load ptr, ptr %fgAnim, align 8
  %152 = getelementptr inbounds %FlowWingAnim, ptr %151, i32 0, i32 0
  %153 = load ptr, ptr %152, align 8
  %154 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %153, i32 0, i32 0
  %155 = load ptr, ptr %154, align 8
  %156 = load ptr, ptr %fgAnim, align 8
  %157 = getelementptr inbounds %FlowWingAnim, ptr %156, i32 0, i32 6
  %158 = getelementptr inbounds %KEYS_TYPE.2, ptr %157, i32 0, i32 3
  %KEY_UP = load i32, ptr %158, align 4
  call void %155(ptr %rtPtr1, ptr %158, ptr %fgAnim)
  %159 = load i1, ptr %rtPtr1, align 1
  %160 = load ptr, ptr %fgAnim, align 8
  %161 = getelementptr inbounds %FlowWingAnim, ptr %160, i32 0, i32 0
  %162 = load ptr, ptr %161, align 8
  %163 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %162, i32 0, i32 4
  %164 = load ptr, ptr %163, align 8
  %165 = load ptr, ptr %fgAnim, align 8
  %166 = getelementptr inbounds %FlowWingAnim, ptr %165, i32 0, i32 6
  %167 = getelementptr inbounds %KEYS_TYPE.2, ptr %166, i32 0, i32 3
  %KEY_UP88 = load i32, ptr %167, align 4
  call void %164(ptr %rtPtr2, ptr %167, ptr %fgAnim)
  %168 = load i1, ptr %rtPtr2, align 1
  %169 = select i1 %159, i1 true, i1 %168
  br i1 %169, label %then, label %orIf0

checkContinueBlock59:                             ; preds = %afterIfElse
  %170 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %nestedBlock60, label %afterNestedBlock55

nestedBlock60:                                    ; preds = %checkContinueBlock59
  %172 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x118 = load i32, ptr %172, align 4
  %173 = load i32, ptr %172, align 4
  %174 = icmp slt i32 %173, 0
  br i1 %174, label %then119, label %else120

checkContinueBlock61:                             ; preds = %afterIfElse121
  %175 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %176 = icmp eq i32 %175, 0
  br i1 %176, label %nestedBlock62, label %afterNestedBlock55

nestedBlock62:                                    ; preds = %checkContinueBlock61
  %177 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x126 = load i32, ptr %177, align 4
  %178 = load i32, ptr %177, align 4
  %screenWidth127 = load i32, ptr @screenWidth, align 4
  %179 = load i32, ptr @screenWidth, align 4
  %180 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %181 = load i32, ptr %180, align 4
  %182 = sub i32 %179, %181
  %183 = icmp sge i32 %178, %182
  br i1 %183, label %then128, label %else129

checkContinueBlock63:                             ; preds = %afterIfElse130
  %184 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %185 = icmp eq i32 %184, 0
  br i1 %185, label %nestedBlock64, label %afterNestedBlock55

nestedBlock64:                                    ; preds = %checkContinueBlock63
  %186 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y136 = load i32, ptr %186, align 4
  %187 = load i32, ptr %186, align 4
  %188 = icmp slt i32 %187, 0
  br i1 %188, label %then137, label %else138

checkContinueBlock65:                             ; preds = %afterIfElse139
  %189 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %190 = icmp eq i32 %189, 0
  br i1 %190, label %nestedBlock66, label %afterNestedBlock55

nestedBlock66:                                    ; preds = %checkContinueBlock65
  %191 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y144 = load i32, ptr %191, align 4
  %192 = load i32, ptr %191, align 4
  %screenHeight145 = load i32, ptr @screenHeight, align 4
  %193 = load i32, ptr @screenHeight, align 4
  %194 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %195 = load i32, ptr %194, align 4
  %196 = sub i32 %193, %195
  %197 = icmp sge i32 %192, %196
  br i1 %197, label %then146, label %else147

checkContinueBlock67:                             ; preds = %afterIfElse148
  %198 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %199 = icmp eq i32 %198, 0
  br i1 %199, label %nestedBlock68, label %afterNestedBlock55

nestedBlock68:                                    ; preds = %checkContinueBlock67
  %200 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x154 = load i32, ptr %200, align 4
  %201 = load i32, ptr %200, align 4
  %202 = getelementptr inbounds %Position.4, ptr %foodPos, i32 0, i32 0
  %x155 = load i32, ptr %202, align 4
  %203 = load i32, ptr %202, align 4
  %204 = icmp eq i32 %201, %203
  %205 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y156 = load i32, ptr %205, align 4
  %206 = load i32, ptr %205, align 4
  %207 = getelementptr inbounds %Position.4, ptr %foodPos, i32 0, i32 1
  %y157 = load i32, ptr %207, align 4
  %208 = load i32, ptr %207, align 4
  %209 = icmp eq i32 %206, %208
  %210 = select i1 %204, i1 %209, i1 false
  br i1 %210, label %then158, label %else159

checkContinueBlock69:                             ; preds = %afterIfElse160
  %211 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %212 = icmp eq i32 %211, 0
  br i1 %212, label %nestedBlock70, label %afterNestedBlock55

nestedBlock70:                                    ; preds = %checkContinueBlock69
  %213 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %214 = load i1, ptr %213, align 1
  br i1 %214, label %then168, label %else169

checkContinueBlock71:                             ; preds = %afterIfElse170
  %215 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %216 = icmp eq i32 %215, 0
  br i1 %216, label %nestedBlock72, label %afterNestedBlock55

nestedBlock72:                                    ; preds = %checkContinueBlock71
  %posX214 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then215", label %"GlobalIndexExpr::else216"

checkContinueBlock73:                             ; preds = %"GlobalIndexExpr::merge217"
  %217 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %218 = icmp eq i32 %217, 0
  br i1 %218, label %nestedBlock74, label %afterNestedBlock55

nestedBlock74:                                    ; preds = %checkContinueBlock73
  %posY219 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then220", label %"GlobalIndexExpr::else221"

checkContinueBlock75:                             ; preds = %"GlobalIndexExpr::merge222"
  %219 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %220 = icmp eq i32 %219, 0
  br i1 %220, label %nestedBlock76, label %afterNestedBlock55

nestedBlock76:                                    ; preds = %checkContinueBlock75
  %221 = load ptr, ptr %fgAnim, align 8
  %222 = getelementptr inbounds %FlowWingAnim, ptr %221, i32 0, i32 0
  %223 = load ptr, ptr %222, align 8
  %224 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %223, i32 0, i32 15
  %225 = load ptr, ptr %224, align 8
  call void %225(ptr %fgAnim)
  %226 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %227 = icmp eq i32 %226, 0
  br i1 %227, label %checkContinueBlock77, label %afterNestedBlock55

checkContinueBlock77:                             ; preds = %nestedBlock76
  %228 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %229 = icmp eq i32 %228, 0
  br i1 %229, label %nestedBlock78, label %afterNestedBlock55

nestedBlock78:                                    ; preds = %checkContinueBlock77
  %230 = load ptr, ptr %fgAnim, align 8
  %231 = getelementptr inbounds %FlowWingAnim, ptr %230, i32 0, i32 0
  %232 = load ptr, ptr %231, align 8
  %233 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %232, i32 0, i32 10
  %234 = load ptr, ptr %233, align 8
  %235 = load ptr, ptr %fgAnim, align 8
  %236 = getelementptr inbounds %FlowWingAnim, ptr %235, i32 0, i32 5
  %237 = getelementptr inbounds %COLORS_TYPE.3, ptr %236, i32 0, i32 0
  %WHITE = load i32, ptr %237, align 4
  call void %234(ptr %237, ptr %fgAnim)
  %238 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %239 = icmp eq i32 %238, 0
  br i1 %239, label %checkContinueBlock79, label %afterNestedBlock55

checkContinueBlock79:                             ; preds = %nestedBlock78
  %240 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %241 = icmp eq i32 %240, 0
  br i1 %241, label %nestedBlock80, label %afterNestedBlock55

nestedBlock80:                                    ; preds = %checkContinueBlock79
  %tail224 = load i32, ptr %tail, align 4
  %242 = load i32, ptr %tail, align 4
  %243 = sub i32 %242, 1
  store i32 0, ptr %index12, align 4
  br label %"ForLoop::loopCondition225"

checkContinueBlock81:                             ; preds = %end_block256
  %244 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %245 = icmp eq i32 %244, 0
  br i1 %245, label %nestedBlock82, label %afterNestedBlock55

nestedBlock82:                                    ; preds = %checkContinueBlock81
  %246 = load ptr, ptr %fgAnim, align 8
  %247 = getelementptr inbounds %FlowWingAnim, ptr %246, i32 0, i32 0
  %248 = load ptr, ptr %247, align 8
  %249 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %248, i32 0, i32 3
  %250 = load ptr, ptr %249, align 8
  %screenWidth257 = load i32, ptr @screenWidth, align 4
  %251 = load i32, ptr @screenWidth, align 4
  %252 = sdiv i32 %251, 5
  store i32 %252, ptr %3, align 4
  store i32 120, ptr %4, align 4
  store float 3.500000e+01, ptr %5, align 4
  %253 = load ptr, ptr %fgAnim, align 8
  %254 = getelementptr inbounds %FlowWingAnim, ptr %253, i32 0, i32 5
  %255 = getelementptr inbounds %COLORS_TYPE.3, ptr %254, i32 0, i32 4
  %DARKBLUE = load i32, ptr %255, align 4
  call void %250(ptr %3, ptr %4, ptr %5, ptr %255, ptr %fgAnim)
  %256 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %257 = icmp eq i32 %256, 0
  br i1 %257, label %checkContinueBlock83, label %afterNestedBlock55

checkContinueBlock83:                             ; preds = %nestedBlock82
  %258 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %259 = icmp eq i32 %258, 0
  br i1 %259, label %nestedBlock84, label %afterNestedBlock55

nestedBlock84:                                    ; preds = %checkContinueBlock83
  %260 = load ptr, ptr %fgAnim, align 8
  %261 = getelementptr inbounds %FlowWingAnim, ptr %260, i32 0, i32 0
  %262 = load ptr, ptr %261, align 8
  %263 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %262, i32 0, i32 16
  %264 = load ptr, ptr %263, align 8
  %265 = getelementptr inbounds %Position.4, ptr %foodPos, i32 0, i32 0
  %x258 = load i32, ptr %265, align 4
  %266 = getelementptr inbounds %Position.4, ptr %foodPos, i32 0, i32 1
  %y259 = load i32, ptr %266, align 4
  %side260 = load i32, ptr @side, align 4
  %side261 = load i32, ptr @side, align 4
  %267 = load ptr, ptr %fgAnim, align 8
  %268 = getelementptr inbounds %FlowWingAnim, ptr %267, i32 0, i32 5
  %269 = getelementptr inbounds %COLORS_TYPE.3, ptr %268, i32 0, i32 2
  %GREEN = load i32, ptr %269, align 4
  call void %264(ptr %265, ptr %266, ptr @side, ptr @side, ptr %269, ptr %fgAnim)
  %270 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %271 = icmp eq i32 %270, 0
  br i1 %271, label %checkContinueBlock85, label %afterNestedBlock55

checkContinueBlock85:                             ; preds = %nestedBlock84
  %272 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %273 = icmp eq i32 %272, 0
  br i1 %273, label %nestedBlock86, label %afterNestedBlock55

nestedBlock86:                                    ; preds = %checkContinueBlock85
  %274 = load ptr, ptr %fgAnim, align 8
  %275 = getelementptr inbounds %FlowWingAnim, ptr %274, i32 0, i32 0
  %276 = load ptr, ptr %275, align 8
  %277 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %276, i32 0, i32 22
  %278 = load ptr, ptr %277, align 8
  call void %278(ptr %fgAnim)
  %279 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %280 = icmp eq i32 %279, 0
  br i1 %280, label %checkContinueBlock87, label %afterNestedBlock55

checkContinueBlock87:                             ; preds = %nestedBlock86
  br label %afterNestedBlock55

then:                                             ; preds = %nestedBlock58
  br label %nestedBlock93

orIf0:                                            ; preds = %nestedBlock58
  %281 = load ptr, ptr %fgAnim, align 8
  %282 = getelementptr inbounds %FlowWingAnim, ptr %281, i32 0, i32 0
  %283 = load ptr, ptr %282, align 8
  %284 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %283, i32 0, i32 0
  %285 = load ptr, ptr %284, align 8
  %286 = load ptr, ptr %fgAnim, align 8
  %287 = getelementptr inbounds %FlowWingAnim, ptr %286, i32 0, i32 6
  %288 = getelementptr inbounds %KEYS_TYPE.2, ptr %287, i32 0, i32 2
  %KEY_DOWN = load i32, ptr %288, align 4
  call void %285(ptr %rtPtr3, ptr %288, ptr %fgAnim)
  %289 = load i1, ptr %rtPtr3, align 1
  %290 = load ptr, ptr %fgAnim, align 8
  %291 = getelementptr inbounds %FlowWingAnim, ptr %290, i32 0, i32 0
  %292 = load ptr, ptr %291, align 8
  %293 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %292, i32 0, i32 4
  %294 = load ptr, ptr %293, align 8
  %295 = load ptr, ptr %fgAnim, align 8
  %296 = getelementptr inbounds %FlowWingAnim, ptr %295, i32 0, i32 6
  %297 = getelementptr inbounds %KEYS_TYPE.2, ptr %296, i32 0, i32 2
  %KEY_DOWN89 = load i32, ptr %297, align 4
  call void %294(ptr %rtPtr4, ptr %297, ptr %fgAnim)
  %298 = load i1, ptr %rtPtr4, align 1
  %299 = select i1 %289, i1 true, i1 %298
  br i1 %299, label %orIfThen0, label %orIf1

orIf1:                                            ; preds = %orIf0
  %300 = load ptr, ptr %fgAnim, align 8
  %301 = getelementptr inbounds %FlowWingAnim, ptr %300, i32 0, i32 0
  %302 = load ptr, ptr %301, align 8
  %303 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %302, i32 0, i32 0
  %304 = load ptr, ptr %303, align 8
  %305 = load ptr, ptr %fgAnim, align 8
  %306 = getelementptr inbounds %FlowWingAnim, ptr %305, i32 0, i32 6
  %307 = getelementptr inbounds %KEYS_TYPE.2, ptr %306, i32 0, i32 0
  %KEY_RIGHT = load i32, ptr %307, align 4
  call void %304(ptr %rtPtr5, ptr %307, ptr %fgAnim)
  %308 = load i1, ptr %rtPtr5, align 1
  %309 = load ptr, ptr %fgAnim, align 8
  %310 = getelementptr inbounds %FlowWingAnim, ptr %309, i32 0, i32 0
  %311 = load ptr, ptr %310, align 8
  %312 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %311, i32 0, i32 4
  %313 = load ptr, ptr %312, align 8
  %314 = load ptr, ptr %fgAnim, align 8
  %315 = getelementptr inbounds %FlowWingAnim, ptr %314, i32 0, i32 6
  %316 = getelementptr inbounds %KEYS_TYPE.2, ptr %315, i32 0, i32 0
  %KEY_RIGHT90 = load i32, ptr %316, align 4
  call void %313(ptr %rtPtr6, ptr %316, ptr %fgAnim)
  %317 = load i1, ptr %rtPtr6, align 1
  %318 = select i1 %308, i1 true, i1 %317
  br i1 %318, label %orIfThen1, label %orIf2

orIf2:                                            ; preds = %orIf1
  %319 = load ptr, ptr %fgAnim, align 8
  %320 = getelementptr inbounds %FlowWingAnim, ptr %319, i32 0, i32 0
  %321 = load ptr, ptr %320, align 8
  %322 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %321, i32 0, i32 0
  %323 = load ptr, ptr %322, align 8
  %324 = load ptr, ptr %fgAnim, align 8
  %325 = getelementptr inbounds %FlowWingAnim, ptr %324, i32 0, i32 6
  %326 = getelementptr inbounds %KEYS_TYPE.2, ptr %325, i32 0, i32 1
  %KEY_LEFT = load i32, ptr %326, align 4
  call void %323(ptr %rtPtr7, ptr %326, ptr %fgAnim)
  %327 = load i1, ptr %rtPtr7, align 1
  %328 = load ptr, ptr %fgAnim, align 8
  %329 = getelementptr inbounds %FlowWingAnim, ptr %328, i32 0, i32 0
  %330 = load ptr, ptr %329, align 8
  %331 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %330, i32 0, i32 4
  %332 = load ptr, ptr %331, align 8
  %333 = load ptr, ptr %fgAnim, align 8
  %334 = getelementptr inbounds %FlowWingAnim, ptr %333, i32 0, i32 6
  %335 = getelementptr inbounds %KEYS_TYPE.2, ptr %334, i32 0, i32 1
  %KEY_LEFT91 = load i32, ptr %335, align 4
  call void %332(ptr %rtPtr8, ptr %335, ptr %fgAnim)
  %336 = load i1, ptr %rtPtr8, align 1
  %337 = select i1 %327, i1 true, i1 %336
  br i1 %337, label %orIfThen2, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock99

orIfThen1:                                        ; preds = %orIf1
  br label %nestedBlock106

orIfThen2:                                        ; preds = %orIf2
  br label %nestedBlock112

else:                                             ; preds = %orIf2
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock111, %afterNestedBlock105, %afterNestedBlock98, %afterNestedBlock92
  %338 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %339 = icmp eq i32 %338, 0
  br i1 %339, label %checkContinueBlock59, label %afterNestedBlock55

afterNestedBlock92:                               ; preds = %checkContinueBlock96, %nestedBlock95, %checkContinueBlock94, %nestedBlock93
  br label %afterIfElse

nestedBlock93:                                    ; preds = %then
  %340 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %341 = load i1, ptr %340, align 1
  %342 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %342, align 1
  %343 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %344 = icmp eq i32 %343, 0
  br i1 %344, label %checkContinueBlock94, label %afterNestedBlock92

checkContinueBlock94:                             ; preds = %nestedBlock93
  %345 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %346 = icmp eq i32 %345, 0
  br i1 %346, label %nestedBlock95, label %afterNestedBlock92

nestedBlock95:                                    ; preds = %checkContinueBlock94
  %347 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y = load i32, ptr %347, align 4
  %348 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y97 = load i32, ptr %348, align 4
  %349 = load i32, ptr %348, align 4
  %350 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %351 = load i32, ptr %350, align 4
  %352 = sub i32 %349, %351
  store i32 %352, ptr %347, align 4
  %353 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %354 = icmp eq i32 %353, 0
  br i1 %354, label %checkContinueBlock96, label %afterNestedBlock92

checkContinueBlock96:                             ; preds = %nestedBlock95
  br label %afterNestedBlock92

afterNestedBlock98:                               ; preds = %checkContinueBlock102, %nestedBlock101, %checkContinueBlock100, %nestedBlock99
  br label %afterIfElse

nestedBlock99:                                    ; preds = %orIfThen0
  %355 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %356 = load i1, ptr %355, align 1
  %357 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %357, align 1
  %358 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %359 = icmp eq i32 %358, 0
  br i1 %359, label %checkContinueBlock100, label %afterNestedBlock98

checkContinueBlock100:                            ; preds = %nestedBlock99
  %360 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %361 = icmp eq i32 %360, 0
  br i1 %361, label %nestedBlock101, label %afterNestedBlock98

nestedBlock101:                                   ; preds = %checkContinueBlock100
  %362 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y103 = load i32, ptr %362, align 4
  %363 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y104 = load i32, ptr %363, align 4
  %364 = load i32, ptr %363, align 4
  %365 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %366 = load i32, ptr %365, align 4
  %367 = add i32 %364, %366
  store i32 %367, ptr %362, align 4
  %368 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %369 = icmp eq i32 %368, 0
  br i1 %369, label %checkContinueBlock102, label %afterNestedBlock98

checkContinueBlock102:                            ; preds = %nestedBlock101
  br label %afterNestedBlock98

afterNestedBlock105:                              ; preds = %checkContinueBlock109, %nestedBlock108, %checkContinueBlock107, %nestedBlock106
  br label %afterIfElse

nestedBlock106:                                   ; preds = %orIfThen1
  %370 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %371 = load i1, ptr %370, align 1
  %372 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %372, align 1
  %373 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %374 = icmp eq i32 %373, 0
  br i1 %374, label %checkContinueBlock107, label %afterNestedBlock105

checkContinueBlock107:                            ; preds = %nestedBlock106
  %375 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %376 = icmp eq i32 %375, 0
  br i1 %376, label %nestedBlock108, label %afterNestedBlock105

nestedBlock108:                                   ; preds = %checkContinueBlock107
  %377 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x = load i32, ptr %377, align 4
  %378 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x110 = load i32, ptr %378, align 4
  %379 = load i32, ptr %378, align 4
  %380 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %381 = load i32, ptr %380, align 4
  %382 = add i32 %379, %381
  store i32 %382, ptr %377, align 4
  %383 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %384 = icmp eq i32 %383, 0
  br i1 %384, label %checkContinueBlock109, label %afterNestedBlock105

checkContinueBlock109:                            ; preds = %nestedBlock108
  br label %afterNestedBlock105

afterNestedBlock111:                              ; preds = %checkContinueBlock115, %nestedBlock114, %checkContinueBlock113, %nestedBlock112
  br label %afterIfElse

nestedBlock112:                                   ; preds = %orIfThen2
  %385 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %386 = load i1, ptr %385, align 1
  %387 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %387, align 1
  %388 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %389 = icmp eq i32 %388, 0
  br i1 %389, label %checkContinueBlock113, label %afterNestedBlock111

checkContinueBlock113:                            ; preds = %nestedBlock112
  %390 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %391 = icmp eq i32 %390, 0
  br i1 %391, label %nestedBlock114, label %afterNestedBlock111

nestedBlock114:                                   ; preds = %checkContinueBlock113
  %392 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x116 = load i32, ptr %392, align 4
  %393 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x117 = load i32, ptr %393, align 4
  %394 = load i32, ptr %393, align 4
  %395 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %396 = load i32, ptr %395, align 4
  %397 = sub i32 %394, %396
  store i32 %397, ptr %392, align 4
  %398 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %399 = icmp eq i32 %398, 0
  br i1 %399, label %checkContinueBlock115, label %afterNestedBlock111

checkContinueBlock115:                            ; preds = %nestedBlock114
  br label %afterNestedBlock111

then119:                                          ; preds = %nestedBlock60
  br label %nestedBlock123

else120:                                          ; preds = %nestedBlock60
  br label %afterIfElse121

afterIfElse121:                                   ; preds = %else120, %afterNestedBlock122
  %400 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %401 = icmp eq i32 %400, 0
  br i1 %401, label %checkContinueBlock61, label %afterNestedBlock55

afterNestedBlock122:                              ; preds = %checkContinueBlock124, %nestedBlock123
  br label %afterIfElse121

nestedBlock123:                                   ; preds = %then119
  %402 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x125 = load i32, ptr %402, align 4
  store i32 0, ptr %402, align 4
  %403 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %404 = icmp eq i32 %403, 0
  br i1 %404, label %checkContinueBlock124, label %afterNestedBlock122

checkContinueBlock124:                            ; preds = %nestedBlock123
  br label %afterNestedBlock122

then128:                                          ; preds = %nestedBlock62
  br label %nestedBlock132

else129:                                          ; preds = %nestedBlock62
  br label %afterIfElse130

afterIfElse130:                                   ; preds = %else129, %afterNestedBlock131
  %405 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %406 = icmp eq i32 %405, 0
  br i1 %406, label %checkContinueBlock63, label %afterNestedBlock55

afterNestedBlock131:                              ; preds = %checkContinueBlock133, %nestedBlock132
  br label %afterIfElse130

nestedBlock132:                                   ; preds = %then128
  %407 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x134 = load i32, ptr %407, align 4
  %screenWidth135 = load i32, ptr @screenWidth, align 4
  %408 = load i32, ptr @screenWidth, align 4
  %409 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %410 = load i32, ptr %409, align 4
  %411 = sub i32 %408, %410
  store i32 %411, ptr %407, align 4
  %412 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %413 = icmp eq i32 %412, 0
  br i1 %413, label %checkContinueBlock133, label %afterNestedBlock131

checkContinueBlock133:                            ; preds = %nestedBlock132
  br label %afterNestedBlock131

then137:                                          ; preds = %nestedBlock64
  br label %nestedBlock141

else138:                                          ; preds = %nestedBlock64
  br label %afterIfElse139

afterIfElse139:                                   ; preds = %else138, %afterNestedBlock140
  %414 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %415 = icmp eq i32 %414, 0
  br i1 %415, label %checkContinueBlock65, label %afterNestedBlock55

afterNestedBlock140:                              ; preds = %checkContinueBlock142, %nestedBlock141
  br label %afterIfElse139

nestedBlock141:                                   ; preds = %then137
  %416 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y143 = load i32, ptr %416, align 4
  store i32 0, ptr %416, align 4
  %417 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %418 = icmp eq i32 %417, 0
  br i1 %418, label %checkContinueBlock142, label %afterNestedBlock140

checkContinueBlock142:                            ; preds = %nestedBlock141
  br label %afterNestedBlock140

then146:                                          ; preds = %nestedBlock66
  br label %nestedBlock150

else147:                                          ; preds = %nestedBlock66
  br label %afterIfElse148

afterIfElse148:                                   ; preds = %else147, %afterNestedBlock149
  %419 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %420 = icmp eq i32 %419, 0
  br i1 %420, label %checkContinueBlock67, label %afterNestedBlock55

afterNestedBlock149:                              ; preds = %checkContinueBlock151, %nestedBlock150
  br label %afterIfElse148

nestedBlock150:                                   ; preds = %then146
  %421 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y152 = load i32, ptr %421, align 4
  %screenHeight153 = load i32, ptr @screenHeight, align 4
  %422 = load i32, ptr @screenHeight, align 4
  %423 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %424 = load i32, ptr %423, align 4
  %425 = sub i32 %422, %424
  store i32 %425, ptr %421, align 4
  %426 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %427 = icmp eq i32 %426, 0
  br i1 %427, label %checkContinueBlock151, label %afterNestedBlock149

checkContinueBlock151:                            ; preds = %nestedBlock150
  br label %afterNestedBlock149

then158:                                          ; preds = %nestedBlock68
  br label %nestedBlock162

else159:                                          ; preds = %nestedBlock68
  br label %afterIfElse160

afterIfElse160:                                   ; preds = %else159, %afterNestedBlock161
  %428 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %429 = icmp eq i32 %428, 0
  br i1 %429, label %checkContinueBlock69, label %afterNestedBlock55

afterNestedBlock161:                              ; preds = %checkContinueBlock165, %nestedBlock164, %checkContinueBlock163, %nestedBlock162
  br label %afterIfElse160

nestedBlock162:                                   ; preds = %then158
  call void @getFoodPosition(ptr %foodPos)
  %430 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %431 = icmp eq i32 %430, 0
  br i1 %431, label %checkContinueBlock163, label %afterNestedBlock161

checkContinueBlock163:                            ; preds = %nestedBlock162
  %432 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %433 = icmp eq i32 %432, 0
  br i1 %433, label %nestedBlock164, label %afterNestedBlock161

nestedBlock164:                                   ; preds = %checkContinueBlock163
  %tail166 = load i32, ptr %tail, align 4
  %tail167 = load i32, ptr %tail, align 4
  %434 = load i32, ptr %tail, align 4
  %435 = add i32 %434, 1
  store i32 %435, ptr %tail, align 4
  %436 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %437 = icmp eq i32 %436, 0
  br i1 %437, label %checkContinueBlock165, label %afterNestedBlock161

checkContinueBlock165:                            ; preds = %nestedBlock164
  br label %afterNestedBlock161

then168:                                          ; preds = %nestedBlock70
  br label %nestedBlock172

else169:                                          ; preds = %nestedBlock70
  br label %afterIfElse170

afterIfElse170:                                   ; preds = %else169, %afterNestedBlock171
  %438 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %439 = icmp eq i32 %438, 0
  br i1 %439, label %checkContinueBlock71, label %afterNestedBlock55

afterNestedBlock171:                              ; preds = %checkContinueBlock173, %end_block213
  br label %afterIfElse170

nestedBlock172:                                   ; preds = %then168
  %tail174 = load i32, ptr %tail, align 4
  %440 = load i32, ptr %tail, align 4
  %441 = sub i32 %440, 1
  store i32 %441, ptr %index11, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock173:                            ; preds = %end_block213
  br label %afterNestedBlock171

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock178, %nestedBlock172
  %442 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %443 = icmp eq i32 %442, 0
  br i1 %443, label %end_block176, label %decrement_block175

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock179

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %444 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %445 = icmp eq i32 %444, 0
  br i1 %445, label %end_block213, label %decrement_block212

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %446 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %447 = icmp eq i32 %446, 0
  br i1 %447, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block175:                               ; preds = %"ForLoop::loopCondition"
  %448 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %449 = sub i32 %448, 1
  store i32 %449, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block176

end_block176:                                     ; preds = %decrement_block175, %"ForLoop::loopCondition"
  %index177 = load i32, ptr %index11, align 4
  br i1 true, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block176
  %450 = icmp sge i32 %index177, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block176
  %451 = icmp sle i32 %index177, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %452 = phi i1 [ %450, %"ForLoop::Conditon::trueBlock" ], [ %451, %"ForLoop::Conditon::falseBlock" ]
  br i1 %452, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock178:                              ; preds = %checkContinueBlock182, %"GlobalIndexExpr::merge208", %checkContinueBlock180, %"GlobalIndexExpr::merge192"
  %453 = add i32 %index177, -1
  store i32 %453, ptr %index11, align 4
  br label %"ForLoop::loopCondition"

nestedBlock179:                                   ; preds = %"ForLoop::loopBody"
  %index183 = load i32, ptr %index11, align 4
  %posX184 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %index183, 10000
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %index183, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then185", label %"GlobalIndexExpr::else186"

checkContinueBlock180:                            ; preds = %"GlobalIndexExpr::merge192"
  %454 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %455 = icmp eq i32 %454, 0
  br i1 %455, label %nestedBlock181, label %afterNestedBlock178

nestedBlock181:                                   ; preds = %checkContinueBlock180
  %index196 = load i32, ptr %index11, align 4
  %posY197 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan201" = icmp slt i32 %index196, 10000
  %"GlobalIndexExpr::isGreaterThan202" = icmp sge i32 %index196, 0
  %"GlobalIndexExpr::isWithinBounds203" = and i1 %"GlobalIndexExpr::isLessThan201", %"GlobalIndexExpr::isGreaterThan202"
  br i1 %"GlobalIndexExpr::isWithinBounds203", label %"GlobalIndexExpr::then198", label %"GlobalIndexExpr::else199"

checkContinueBlock182:                            ; preds = %"GlobalIndexExpr::merge208"
  br label %afterNestedBlock178

"GlobalIndexExpr::then185":                       ; preds = %nestedBlock179
  br label %"GlobalIndexExpr::merge187"

"GlobalIndexExpr::else186":                       ; preds = %nestedBlock179
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge187"

"GlobalIndexExpr::merge187":                      ; preds = %"GlobalIndexExpr::else186", %"GlobalIndexExpr::then185"
  %456 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index183
  %457 = load i32, ptr %456, align 4
  %index188 = load i32, ptr %index11, align 4
  %458 = load i32, ptr %index11, align 4
  %459 = sub i32 %458, 1
  %posX189 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan193" = icmp slt i32 %459, 10000
  %"GlobalIndexExpr::isGreaterThan194" = icmp sge i32 %459, 0
  %"GlobalIndexExpr::isWithinBounds195" = and i1 %"GlobalIndexExpr::isLessThan193", %"GlobalIndexExpr::isGreaterThan194"
  br i1 %"GlobalIndexExpr::isWithinBounds195", label %"GlobalIndexExpr::then190", label %"GlobalIndexExpr::else191"

"GlobalIndexExpr::then190":                       ; preds = %"GlobalIndexExpr::merge187"
  br label %"GlobalIndexExpr::merge192"

"GlobalIndexExpr::else191":                       ; preds = %"GlobalIndexExpr::merge187"
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge192"

"GlobalIndexExpr::merge192":                      ; preds = %"GlobalIndexExpr::else191", %"GlobalIndexExpr::then190"
  %460 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %459
  %461 = load i32, ptr %460, align 4
  %462 = load i32, ptr %460, align 4
  store i32 %462, ptr %456, align 4
  %463 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %464 = icmp eq i32 %463, 0
  br i1 %464, label %checkContinueBlock180, label %afterNestedBlock178

"GlobalIndexExpr::then198":                       ; preds = %nestedBlock181
  br label %"GlobalIndexExpr::merge200"

"GlobalIndexExpr::else199":                       ; preds = %nestedBlock181
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge200"

"GlobalIndexExpr::merge200":                      ; preds = %"GlobalIndexExpr::else199", %"GlobalIndexExpr::then198"
  %465 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index196
  %466 = load i32, ptr %465, align 4
  %index204 = load i32, ptr %index11, align 4
  %467 = load i32, ptr %index11, align 4
  %468 = sub i32 %467, 1
  %posY205 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan209" = icmp slt i32 %468, 10000
  %"GlobalIndexExpr::isGreaterThan210" = icmp sge i32 %468, 0
  %"GlobalIndexExpr::isWithinBounds211" = and i1 %"GlobalIndexExpr::isLessThan209", %"GlobalIndexExpr::isGreaterThan210"
  br i1 %"GlobalIndexExpr::isWithinBounds211", label %"GlobalIndexExpr::then206", label %"GlobalIndexExpr::else207"

"GlobalIndexExpr::then206":                       ; preds = %"GlobalIndexExpr::merge200"
  br label %"GlobalIndexExpr::merge208"

"GlobalIndexExpr::else207":                       ; preds = %"GlobalIndexExpr::merge200"
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge208"

"GlobalIndexExpr::merge208":                      ; preds = %"GlobalIndexExpr::else207", %"GlobalIndexExpr::then206"
  %469 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %468
  %470 = load i32, ptr %469, align 4
  %471 = load i32, ptr %469, align 4
  store i32 %471, ptr %465, align 4
  %472 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %473 = icmp eq i32 %472, 0
  br i1 %473, label %checkContinueBlock182, label %afterNestedBlock178

decrement_block212:                               ; preds = %"ForLoop::afterLoop"
  %474 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %475 = sub i32 %474, 1
  store i32 %475, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block213

end_block213:                                     ; preds = %decrement_block212, %"ForLoop::afterLoop"
  %476 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %477 = icmp eq i32 %476, 0
  br i1 %477, label %checkContinueBlock173, label %afterNestedBlock171

"GlobalIndexExpr::then215":                       ; preds = %nestedBlock72
  br label %"GlobalIndexExpr::merge217"

"GlobalIndexExpr::else216":                       ; preds = %nestedBlock72
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge217"

"GlobalIndexExpr::merge217":                      ; preds = %"GlobalIndexExpr::else216", %"GlobalIndexExpr::then215"
  %478 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %479 = load i32, ptr %478, align 4
  %480 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 0
  %x218 = load i32, ptr %480, align 4
  %481 = load i32, ptr %480, align 4
  store i32 %481, ptr %478, align 4
  %482 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %483 = icmp eq i32 %482, 0
  br i1 %483, label %checkContinueBlock73, label %afterNestedBlock55

"GlobalIndexExpr::then220":                       ; preds = %nestedBlock74
  br label %"GlobalIndexExpr::merge222"

"GlobalIndexExpr::else221":                       ; preds = %nestedBlock74
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge222"

"GlobalIndexExpr::merge222":                      ; preds = %"GlobalIndexExpr::else221", %"GlobalIndexExpr::then220"
  %484 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %485 = load i32, ptr %484, align 4
  %486 = getelementptr inbounds %Position.4, ptr %newPos, i32 0, i32 1
  %y223 = load i32, ptr %486, align 4
  %487 = load i32, ptr %486, align 4
  store i32 %487, ptr %484, align 4
  %488 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %489 = icmp eq i32 %488, 0
  br i1 %489, label %checkContinueBlock75, label %afterNestedBlock55

"ForLoop::loopCondition225":                      ; preds = %afterNestedBlock235, %nestedBlock80
  %490 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %491 = icmp eq i32 %490, 0
  br i1 %491, label %end_block230, label %decrement_block229

"ForLoop::loopBody226":                           ; preds = %"ForLoop::breakLoop228"
  br label %nestedBlock236

"ForLoop::afterLoop227":                          ; preds = %"ForLoop::breakLoop228", %"ForLoop::Conditon::mergeBlock234"
  %492 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %493 = icmp eq i32 %492, 0
  br i1 %493, label %end_block256, label %decrement_block255

"ForLoop::breakLoop228":                          ; preds = %"ForLoop::Conditon::mergeBlock234"
  %494 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %495 = icmp eq i32 %494, 0
  br i1 %495, label %"ForLoop::loopBody226", label %"ForLoop::afterLoop227"

decrement_block229:                               ; preds = %"ForLoop::loopCondition225"
  %496 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %497 = sub i32 %496, 1
  store i32 %497, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block230

end_block230:                                     ; preds = %decrement_block229, %"ForLoop::loopCondition225"
  %index231 = load i32, ptr %index12, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock232", label %"ForLoop::Conditon::falseBlock233"

"ForLoop::Conditon::trueBlock232":                ; preds = %end_block230
  %498 = icmp sge i32 %index231, %243
  br label %"ForLoop::Conditon::mergeBlock234"

"ForLoop::Conditon::falseBlock233":               ; preds = %end_block230
  %499 = icmp sle i32 %index231, %243
  br label %"ForLoop::Conditon::mergeBlock234"

"ForLoop::Conditon::mergeBlock234":               ; preds = %"ForLoop::Conditon::falseBlock233", %"ForLoop::Conditon::trueBlock232"
  %500 = phi i1 [ %498, %"ForLoop::Conditon::trueBlock232" ], [ %499, %"ForLoop::Conditon::falseBlock233" ]
  br i1 %500, label %"ForLoop::breakLoop228", label %"ForLoop::afterLoop227"

afterNestedBlock235:                              ; preds = %checkContinueBlock237, %"GlobalIndexExpr::merge250"
  %501 = add i32 %index231, 1
  store i32 %501, ptr %index12, align 4
  br label %"ForLoop::loopCondition225"

nestedBlock236:                                   ; preds = %"ForLoop::loopBody226"
  %502 = load ptr, ptr %fgAnim, align 8
  %503 = getelementptr inbounds %FlowWingAnim, ptr %502, i32 0, i32 0
  %504 = load ptr, ptr %503, align 8
  %505 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %504, i32 0, i32 16
  %506 = load ptr, ptr %505, align 8
  %index238 = load i32, ptr %index12, align 4
  %posX239 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan243" = icmp slt i32 %index238, 10000
  %"GlobalIndexExpr::isGreaterThan244" = icmp sge i32 %index238, 0
  %"GlobalIndexExpr::isWithinBounds245" = and i1 %"GlobalIndexExpr::isLessThan243", %"GlobalIndexExpr::isGreaterThan244"
  br i1 %"GlobalIndexExpr::isWithinBounds245", label %"GlobalIndexExpr::then240", label %"GlobalIndexExpr::else241"

checkContinueBlock237:                            ; preds = %"GlobalIndexExpr::merge250"
  br label %afterNestedBlock235

"GlobalIndexExpr::then240":                       ; preds = %nestedBlock236
  br label %"GlobalIndexExpr::merge242"

"GlobalIndexExpr::else241":                       ; preds = %nestedBlock236
  call void @raise_exception(ptr @14)
  br label %"GlobalIndexExpr::merge242"

"GlobalIndexExpr::merge242":                      ; preds = %"GlobalIndexExpr::else241", %"GlobalIndexExpr::then240"
  %507 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index238
  %508 = load i32, ptr %507, align 4
  %index246 = load i32, ptr %index12, align 4
  %posY247 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan251" = icmp slt i32 %index246, 10000
  %"GlobalIndexExpr::isGreaterThan252" = icmp sge i32 %index246, 0
  %"GlobalIndexExpr::isWithinBounds253" = and i1 %"GlobalIndexExpr::isLessThan251", %"GlobalIndexExpr::isGreaterThan252"
  br i1 %"GlobalIndexExpr::isWithinBounds253", label %"GlobalIndexExpr::then248", label %"GlobalIndexExpr::else249"

"GlobalIndexExpr::then248":                       ; preds = %"GlobalIndexExpr::merge242"
  br label %"GlobalIndexExpr::merge250"

"GlobalIndexExpr::else249":                       ; preds = %"GlobalIndexExpr::merge242"
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge250"

"GlobalIndexExpr::merge250":                      ; preds = %"GlobalIndexExpr::else249", %"GlobalIndexExpr::then248"
  %509 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index246
  %510 = load i32, ptr %509, align 4
  %side = load i32, ptr @side, align 4
  %side254 = load i32, ptr @side, align 4
  %511 = load ptr, ptr %fgAnim, align 8
  %512 = getelementptr inbounds %FlowWingAnim, ptr %511, i32 0, i32 5
  %513 = getelementptr inbounds %COLORS_TYPE.3, ptr %512, i32 0, i32 3
  %BLUE = load i32, ptr %513, align 4
  call void %506(ptr %507, ptr %509, ptr @side, ptr @side, ptr %513, ptr %fgAnim)
  %514 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %515 = icmp eq i32 %514, 0
  br i1 %515, label %checkContinueBlock237, label %afterNestedBlock235

decrement_block255:                               ; preds = %"ForLoop::afterLoop227"
  %516 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %517 = sub i32 %516, 1
  store i32 %517, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block256

end_block256:                                     ; preds = %decrement_block255, %"ForLoop::afterLoop227"
  %518 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %519 = icmp eq i32 %518, 0
  br i1 %519, label %checkContinueBlock81, label %afterNestedBlock55

decrement_block262:                               ; preds = %while.end
  %520 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %521 = sub i32 %520, 1
  store i32 %521, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block263

end_block263:                                     ; preds = %decrement_block262, %while.end
  %522 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %523 = icmp eq i32 %522, 0
  br i1 %523, label %checkContinueBlock32, label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock35
  store i32 0, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %524 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %525 = icmp eq i32 %524, 0
  br i1 %525, label %checkContinueBlock36, label %afterNestedBlock
}

define internal void @"assign_<ObjectPosition.4>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Position.4, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Position.4, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  ret void
}

define internal void @"assign_<Array[10000]<'Integer32'>>:10000,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 10000
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 10000
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [10000 x i32], ptr %0, i32 0, i32 %6
  store i32 0, ptr %7, align 4
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
  store ptr @4, ptr %1, align 8
  %2 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  %4 = getelementptr inbounds %FlowWingAnim, ptr %0, i32 0, i32 3
  store ptr @5, ptr %4, align 8
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
!25 = !{!"getRandomNumber:rt:pr:28"}
!26 = !{!"getFoodPosition:rt:ob:Position.4"}
!27 = !{!"main:rt:pr:28"}
