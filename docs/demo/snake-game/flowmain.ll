; ModuleID = 'flowmain'
source_filename = "flowmain"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%Position.2 = type { i32, i32 }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.1, %KEYS_TYPE.0 }
%COLORS_TYPE.1 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.0 = type { i32, i32, i32, i32 }

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
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [696 x i8] c"\0A\1B[33m22| \1B[0m\1B[0m  const speed = 10\0A\1B[0m\1B[33m23| \1B[0m\1B[0m  var tail: int = 1\0A\1B[0m\1B[33m24| \1B[0m\1B[0m  var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m25| \1B[0m\1B[0m  var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m26| \1B[0m\1B[31m\1B[1m  posX[0]= 0\0A\1B[0m\1B[32m\1B[1m        \0A   ~~~~~~~^\1B[0m\0A\1B[33m27| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 26:8\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [692 x i8] c"\0A\1B[33m23| \1B[0m\1B[0m  var tail: int = 1\0A\1B[0m\1B[33m24| \1B[0m\1B[0m  var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m25| \1B[0m\1B[0m  var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m26| \1B[0m\1B[0m  posX[0]= 0\0A\1B[0m\1B[33m27| \1B[0m\1B[31m\1B[1m  posY[0]= 0\0A\1B[0m\1B[32m\1B[1m        \0A   ~~~~~~~^\1B[0m\0A\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[33m31| \1B[0m\1B[0m    y: posY[0]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 27:8\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [734 x i8] c"\0A\1B[33m26| \1B[0m\1B[0m  posX[0]= 0\0A\1B[0m\1B[33m27| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[31m\1B[1m    x: posX[0],\0A\1B[0m\1B[32m\1B[1m             \0A   ~~~~~~~~~~~~^\1B[0m\0A\1B[33m31| \1B[0m\1B[0m    y: posY[0]\0A\1B[0m\1B[33m32| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m33| \1B[0m\1B[0m  const fgAnim: FlowWingAnim = new FlowWingAnim(screenWidth, screenHeight, \22snake-game-in-flowwing\22, 60)\0A\1B[0m\1B[33m34| \1B[0m\1B[0m  fgAnim.createWindow()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 30:13\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [761 x i8] c"\0A\1B[33m27| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[33m31| \1B[0m\1B[31m\1B[1m    y: posY[0]\0A\1B[0m\1B[32m\1B[1m             \0A   ~~~~~~~~~~~~^\1B[0m\0A\1B[33m32| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m33| \1B[0m\1B[0m  const fgAnim: FlowWingAnim = new FlowWingAnim(screenWidth, screenHeight, \22snake-game-in-flowwing\22, 60)\0A\1B[0m\1B[33m34| \1B[0m\1B[0m  fgAnim.createWindow()\0A\1B[0m\1B[33m35| \1B[0m\1B[0m  while (!fgAnim.windowShouldClose()) {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 31:13\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@8 = private unnamed_addr constant [643 x i8] c"\0A\1B[33m73| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m74| \1B[0m\1B[0m\0A\1B[0m\1B[33m75| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m76| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m77| \1B[0m\1B[31m\1B[1m        posX[index]= posX[index - 1]\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m78| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 77:14\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [685 x i8] c"\0A\1B[33m73| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m74| \1B[0m\1B[0m\0A\1B[0m\1B[33m75| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m76| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m77| \1B[0m\1B[31m\1B[1m        posX[index]= posX[index - 1]\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m78| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 77:35\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [659 x i8] c"\0A\1B[33m74| \1B[0m\1B[0m\0A\1B[0m\1B[33m75| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m76| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m77| \1B[0m\1B[0m        posX[index]= posX[index - 1]\0A\1B[0m\1B[33m78| \1B[0m\1B[31m\1B[1m        posY[index]= posY[index - 1]\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m79| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m\0A\1B[0m\1B[33m82| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 78:14\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [701 x i8] c"\0A\1B[33m74| \1B[0m\1B[0m\0A\1B[0m\1B[33m75| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m76| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m77| \1B[0m\1B[0m        posX[index]= posX[index - 1]\0A\1B[0m\1B[33m78| \1B[0m\1B[31m\1B[1m        posY[index]= posY[index - 1]\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m79| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m\0A\1B[0m\1B[33m82| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 78:35\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [678 x i8] c"\0A\1B[33m78| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m79| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m\0A\1B[0m\1B[33m82| \1B[0m\1B[31m\1B[1m    posX[0]= newPos.x\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m83| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 82:10\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [726 x i8] c"\0A\1B[33m79| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m\0A\1B[0m\1B[33m82| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[33m83| \1B[0m\1B[31m\1B[1m    posY[0]= newPos.y\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m84| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m87| \1B[0m\1B[0m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 83:10\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [921 x i8] c"\0A\1B[33m83| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m87| \1B[0m\1B[31m\1B[1m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[32m\1B[1m                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m88| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m91| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 87:33\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [947 x i8] c"\0A\1B[33m83| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m85| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m87| \1B[0m\1B[31m\1B[1m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m88| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m91| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 87:46\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@16 = private unnamed_addr constant [849 x i8] c"\0A\1B[33m85| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m87| \1B[0m\1B[0m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m89| \1B[0m\1B[31m\1B[1m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[32m\1B[1m                                      \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m90| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m91| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m92| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m93| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 89:38\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1

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

define i32 @flowmain() {
entry:
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiFlowWingAnim()
  store i32 0, ptr @screenWidth, align 4
  store i32 1000, ptr @screenWidth, align 4
  store i32 0, ptr @screenHeight, align 4
  store i32 500, ptr @screenHeight, align 4
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

declare !rt !11 i32 @FlowWingAnim.getScreenHeight(ptr)

declare !rt !12 i32 @FlowWingAnim.getScreenWidth(ptr)

declare !rt !13 void @FlowWingAnim.drawCircle(ptr, ptr, ptr, ptr, ptr)

declare !rt !14 void @FlowWingAnim.drawText(ptr, ptr, ptr, ptr, ptr, ptr)

declare !rt !15 i1 @FlowWingAnim.isKeyPressed(ptr, ptr)

declare !rt !16 i1 @FlowWingAnim.isKeyDown(ptr, ptr)

declare !rt !17 ptr @FlowWingAnim.textFormat(ptr, ptr)

declare !rt !15 i1 @FlowWingAnim.isKeyPressed.1(ptr)

declare !rt !14 void @FlowWingAnim.drawText.2(ptr, ptr, ptr, ptr, ptr)

declare !rt !13 void @FlowWingAnim.drawCircle.3(ptr, ptr, ptr, ptr)

declare !rt !16 i1 @FlowWingAnim.isKeyDown.4(ptr)

declare !rt !12 i32 @FlowWingAnim.getScreenWidth.5()

declare !rt !11 i32 @FlowWingAnim.getScreenHeight.6()

declare !rt !17 ptr @FlowWingAnim.textFormat.7(ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.8()

declare !rt !9 void @FlowWingAnim.endDrawing.9()

declare !rt !7 void @FlowWingAnim.beginDrawing.10()

declare !rt !5 void @FlowWingAnim.clearBackground.11(ptr)

declare !rt !4 void @FlowWingAnim.createWindow.12()

declare !rt !3 i32 @FlowWingAnim.getColor.13(ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.14()

declare !rt !18 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !19 void @SetTargetFPS(i32)

declare !rt !20 void @EndDrawing()

declare !rt !21 void @InitWindow(i32, i32, ptr)

declare !rt !22 void @ClearBackground(i32)

declare !rt !23 i32 @GetScreenWidth()

declare !rt !24 void @DrawCircle(i32, i32, float, i32)

declare !rt !6 i1 @FlowWingAnim.windowShouldClose.15()

declare !rt !25 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !26 i1 @WindowShouldClose()

declare !rt !27 ptr @TextFormat(ptr)

declare !rt !28 void @BeginDrawing()

declare !rt !29 i32 @time()

declare !rt !30 i1 @IsKeyPressed(i32)

declare !rt !1 void @FlowWingAnim.beforeInit.16()

declare !rt !31 void @CloseWindow()

declare !rt !0 void @FlowWingAnim.init4.17(ptr, ptr, ptr, ptr)

declare !rt !32 i32 @GetScreenHeight()

declare !rt !8 void @FlowWingAnim.drawRectangle.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !33 i32 @getRandomNumber(ptr, ptr)

declare !rt !34 i1 @IsKeyDown(i32)

declare !rt !35 i32 @rand()

declare !rt !36 void @srand(i32)

define ptr @getFoodPosition() !rt !37 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %mergeBlock, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret ptr @0

nestedBlock:                                      ; preds = %entry
  %pos = alloca %Position.2, align 8
  %0 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 0
  store i32 0, ptr %0, align 4
  %1 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 1
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 0
  %3 = alloca i32, align 4
  store i32 0, ptr %3, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %4 = sub i32 %screenWidth, 1
  %5 = alloca i32, align 4
  store i32 %4, ptr %5, align 4
  %6 = call i32 @getRandomNumber(ptr %3, ptr %5)
  store i32 %6, ptr %2, align 4
  %7 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 1
  %8 = alloca i32, align 4
  store i32 0, ptr %8, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %9 = sub i32 %screenHeight, 1
  %10 = alloca i32, align 4
  store i32 %9, ptr %10, align 4
  %11 = call i32 @getRandomNumber(ptr %8, ptr %10)
  store i32 %11, ptr %7, align 4
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %14 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %16 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 0
  %x = load i32, ptr %16, align 4
  %17 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 0
  %x7 = load i32, ptr %17, align 4
  %18 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 0
  %x8 = load i32, ptr %18, align 4
  %side = load i32, ptr @side, align 4
  %19 = srem i32 %x8, %side
  %20 = sub i32 %x7, %19
  store i32 %20, ptr %16, align 4
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 1
  %y = load i32, ptr %25, align 4
  %26 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 1
  %y9 = load i32, ptr %26, align 4
  %27 = getelementptr inbounds %Position.2, ptr %pos, i32 0, i32 1
  %y10 = load i32, ptr %27, align 4
  %side11 = load i32, ptr @side, align 4
  %28 = srem i32 %y10, %side11
  %29 = sub i32 %y9, %28
  store i32 %29, ptr %25, align 4
  %30 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %32 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  br label %returnBlock

checkContinueBlock6:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock5
  ret ptr %pos

mergeBlock:                                       ; No predecessors!
  %34 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %checkContinueBlock6, label %afterNestedBlock
}

define i32 @main() !rt !38 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock24, %mergeBlock, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %end_block263, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %"GlobalIndexExpr::merge52", %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %"GlobalIndexExpr::merge44", %checkContinueBlock8, %"GlobalIndexExpr::merge", %checkContinueBlock6, %FillExpr.exit39, %checkContinueBlock4, %FillExpr.exit29, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  %speed = alloca %DynamicType, align 8
  %0 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  store i32 10, ptr %0, align 4
  %1 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %3 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %tail = alloca i32, align 4
  store i32 0, ptr %tail, align 4
  store i32 1, ptr %tail, align 4
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %posX = alloca [10000 x i32], align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 0, ptr %10, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock4:                              ; preds = %FillExpr.exit29
  %11 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %posY = alloca [10000 x i32], align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store i32 0, ptr %14, align 4
  br label %FillExpr.loopStart-030

checkContinueBlock6:                              ; preds = %FillExpr.exit39
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %posX40 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock8:                              ; preds = %"GlobalIndexExpr::merge"
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %posY41 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then42", label %"GlobalIndexExpr::else43"

checkContinueBlock10:                             ; preds = %"GlobalIndexExpr::merge44"
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %foodPos = alloca %Position.2, align 8
  %21 = getelementptr inbounds %Position.2, ptr %foodPos, i32 0, i32 0
  store i32 0, ptr %21, align 4
  %22 = getelementptr inbounds %Position.2, ptr %foodPos, i32 0, i32 1
  store i32 0, ptr %22, align 4
  %23 = call ptr @getFoodPosition()
  %24 = load %Position.2, ptr %23, align 4
  store %Position.2 %24, ptr %foodPos, align 4
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %27 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %newPos = alloca %Position.2, align 8
  %29 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  store i32 0, ptr %29, align 4
  %30 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  store i32 0, ptr %30, align 4
  %31 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %posX45 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then46", label %"GlobalIndexExpr::else47"

checkContinueBlock14:                             ; preds = %"GlobalIndexExpr::merge52"
  %32 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %34 = call ptr @malloc(i64 64)
  %35 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  store ptr @5, ptr %35, align 8
  %36 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 1
  store i32 0, ptr %36, align 4
  %37 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 2
  store i32 0, ptr %37, align 4
  %38 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 3
  store ptr @6, ptr %38, align 8
  %39 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 4
  store i32 0, ptr %39, align 4
  %40 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 5
  %41 = getelementptr inbounds %COLORS_TYPE.1, ptr %40, i32 0, i32 0
  store i32 0, ptr %41, align 4
  %42 = getelementptr inbounds %COLORS_TYPE.1, ptr %40, i32 0, i32 1
  store i32 0, ptr %42, align 4
  %43 = getelementptr inbounds %COLORS_TYPE.1, ptr %40, i32 0, i32 2
  store i32 0, ptr %43, align 4
  %44 = getelementptr inbounds %COLORS_TYPE.1, ptr %40, i32 0, i32 3
  store i32 0, ptr %44, align 4
  %45 = getelementptr inbounds %COLORS_TYPE.1, ptr %40, i32 0, i32 4
  store i32 0, ptr %45, align 4
  %46 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %47 = getelementptr inbounds %KEYS_TYPE.0, ptr %46, i32 0, i32 0
  store i32 0, ptr %47, align 4
  %48 = getelementptr inbounds %KEYS_TYPE.0, ptr %46, i32 0, i32 1
  store i32 0, ptr %48, align 4
  %49 = getelementptr inbounds %KEYS_TYPE.0, ptr %46, i32 0, i32 2
  store i32 0, ptr %49, align 4
  %50 = getelementptr inbounds %KEYS_TYPE.0, ptr %46, i32 0, i32 3
  store i32 0, ptr %50, align 4
  %51 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %51, align 8
  %52 = load ptr, ptr %51, align 8
  %53 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 15
  store ptr @FlowWingAnim.endDrawing, ptr %53, align 8
  %54 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 16
  store ptr @FlowWingAnim.setTargetFPS, ptr %54, align 8
  %55 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 14
  store ptr @FlowWingAnim.createWindow, ptr %55, align 8
  %56 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 13
  store ptr @FlowWingAnim.clearBackground, ptr %56, align 8
  %57 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 12
  store ptr @FlowWingAnim.beforeInit, ptr %57, align 8
  %58 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 11
  store ptr @FlowWingAnim.textFormat, ptr %58, align 8
  %59 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 9
  store ptr @FlowWingAnim.getColor, ptr %59, align 8
  %60 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 8
  store ptr @FlowWingAnim.drawRectangle, ptr %60, align 8
  %61 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 7
  store ptr @FlowWingAnim.beginDrawing, ptr %61, align 8
  %62 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 6
  store ptr @FlowWingAnim.closeWindow, ptr %62, align 8
  %63 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 5
  store ptr @FlowWingAnim.getScreenHeight, ptr %63, align 8
  %64 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 4
  store ptr @FlowWingAnim.getScreenWidth, ptr %64, align 8
  %65 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 2
  store ptr @FlowWingAnim.isKeyDown, ptr %65, align 8
  %66 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 10
  store ptr @FlowWingAnim.windowShouldClose, ptr %66, align 8
  %67 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 3
  store ptr @FlowWingAnim.drawCircle, ptr %67, align 8
  %68 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 1
  store ptr @FlowWingAnim.drawText, ptr %68, align 8
  %69 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %52, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %69, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %70 = alloca ptr, align 8
  store ptr @7, ptr %70, align 8
  %71 = alloca i32, align 4
  store i32 60, ptr %71, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %70, ptr %71, ptr %34)
  %72 = load %FlowWingAnim, ptr %34, align 8
  store %FlowWingAnim %72, ptr %34, align 8
  %73 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %74 = icmp eq i32 %73, 0
  br i1 %74, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %75 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %77 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %78 = load ptr, ptr %77, align 8
  %79 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %78, i32 0, i32 14
  %80 = load ptr, ptr %79, align 8
  call void %80(ptr %34)
  %81 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %83 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  br label %"while:conditon"

checkContinueBlock20:                             ; preds = %end_block263
  %85 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  %87 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %88 = load ptr, ptr %87, align 8
  %89 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %88, i32 0, i32 6
  %90 = load ptr, ptr %89, align 8
  call void %90(ptr %34)
  %91 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %93 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %94 = icmp eq i32 %93, 0
  br i1 %94, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  br label %returnBlock

checkContinueBlock24:                             ; preds = %mergeBlock
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock3
  store i32 0, ptr %9, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %95 = load i32, ptr %9, align 4
  %96 = icmp slt i32 %95, 10000
  %97 = load i32, ptr %10, align 4
  %98 = icmp slt i32 %97, 10000
  %99 = and i1 %96, %98
  br i1 %99, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %100 = load i32, ptr %9, align 4
  %101 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %100
  store i32 0, ptr %101, align 4
  %102 = load i32, ptr %9, align 4
  %103 = add i32 %102, 1
  store i32 %103, ptr %9, align 4
  %104 = load i32, ptr %10, align 4
  %105 = add i32 %104, 1
  store i32 %105, ptr %10, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %106 = alloca i32, align 4
  %107 = alloca i32, align 4
  store i32 0, ptr %107, align 4
  br label %FillExpr.loopStart-025

FillExpr.loopStart-025:                           ; preds = %FillExpr.exit
  store i32 0, ptr %106, align 4
  br label %FillExpr.loopCmp-026

FillExpr.loopCmp-026:                             ; preds = %FillExpr.loopBody-027, %FillExpr.loopStart-025
  %108 = load i32, ptr %106, align 4
  %109 = icmp slt i32 %108, 10000
  %110 = load i32, ptr %107, align 4
  %111 = icmp slt i32 %110, 10000
  %112 = and i1 %109, %111
  br i1 %112, label %FillExpr.loopBody-027, label %FillExpr.loopEnd-028

FillExpr.loopBody-027:                            ; preds = %FillExpr.loopCmp-026
  %113 = load i32, ptr %106, align 4
  %114 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %113
  store i32 -1, ptr %114, align 4
  %115 = load i32, ptr %106, align 4
  %116 = add i32 %115, 1
  store i32 %116, ptr %106, align 4
  %117 = load i32, ptr %107, align 4
  %118 = add i32 %117, 1
  store i32 %118, ptr %107, align 4
  br label %FillExpr.loopCmp-026

FillExpr.loopEnd-028:                             ; preds = %FillExpr.loopCmp-026
  br label %FillExpr.exit29

FillExpr.exit29:                                  ; preds = %FillExpr.loopEnd-028
  %119 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %120 = icmp eq i32 %119, 0
  br i1 %120, label %checkContinueBlock4, label %afterNestedBlock

FillExpr.loopStart-030:                           ; preds = %nestedBlock5
  store i32 0, ptr %13, align 4
  br label %FillExpr.loopCmp-031

FillExpr.loopCmp-031:                             ; preds = %FillExpr.loopBody-032, %FillExpr.loopStart-030
  %121 = load i32, ptr %13, align 4
  %122 = icmp slt i32 %121, 10000
  %123 = load i32, ptr %14, align 4
  %124 = icmp slt i32 %123, 10000
  %125 = and i1 %122, %124
  br i1 %125, label %FillExpr.loopBody-032, label %FillExpr.loopEnd-033

FillExpr.loopBody-032:                            ; preds = %FillExpr.loopCmp-031
  %126 = load i32, ptr %13, align 4
  %127 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %126
  store i32 0, ptr %127, align 4
  %128 = load i32, ptr %13, align 4
  %129 = add i32 %128, 1
  store i32 %129, ptr %13, align 4
  %130 = load i32, ptr %14, align 4
  %131 = add i32 %130, 1
  store i32 %131, ptr %14, align 4
  br label %FillExpr.loopCmp-031

FillExpr.loopEnd-033:                             ; preds = %FillExpr.loopCmp-031
  br label %FillExpr.exit34

FillExpr.exit34:                                  ; preds = %FillExpr.loopEnd-033
  %132 = alloca i32, align 4
  %133 = alloca i32, align 4
  store i32 0, ptr %133, align 4
  br label %FillExpr.loopStart-035

FillExpr.loopStart-035:                           ; preds = %FillExpr.exit34
  store i32 0, ptr %132, align 4
  br label %FillExpr.loopCmp-036

FillExpr.loopCmp-036:                             ; preds = %FillExpr.loopBody-037, %FillExpr.loopStart-035
  %134 = load i32, ptr %132, align 4
  %135 = icmp slt i32 %134, 10000
  %136 = load i32, ptr %133, align 4
  %137 = icmp slt i32 %136, 10000
  %138 = and i1 %135, %137
  br i1 %138, label %FillExpr.loopBody-037, label %FillExpr.loopEnd-038

FillExpr.loopBody-037:                            ; preds = %FillExpr.loopCmp-036
  %139 = load i32, ptr %132, align 4
  %140 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %139
  store i32 -1, ptr %140, align 4
  %141 = load i32, ptr %132, align 4
  %142 = add i32 %141, 1
  store i32 %142, ptr %132, align 4
  %143 = load i32, ptr %133, align 4
  %144 = add i32 %143, 1
  store i32 %144, ptr %133, align 4
  br label %FillExpr.loopCmp-036

FillExpr.loopEnd-038:                             ; preds = %FillExpr.loopCmp-036
  br label %FillExpr.exit39

FillExpr.exit39:                                  ; preds = %FillExpr.loopEnd-038
  %145 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %146 = icmp eq i32 %145, 0
  br i1 %146, label %checkContinueBlock6, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %nestedBlock7
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock7
  call void @raise_exception(ptr @1)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %147 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %148 = load i32, ptr %147, align 4
  store i32 0, ptr %147, align 4
  %149 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %150 = icmp eq i32 %149, 0
  br i1 %150, label %checkContinueBlock8, label %afterNestedBlock

"GlobalIndexExpr::then42":                        ; preds = %nestedBlock9
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::else43":                        ; preds = %nestedBlock9
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::merge44":                       ; preds = %"GlobalIndexExpr::else43", %"GlobalIndexExpr::then42"
  %151 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %152 = load i32, ptr %151, align 4
  store i32 0, ptr %151, align 4
  %153 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %checkContinueBlock10, label %afterNestedBlock

"GlobalIndexExpr::then46":                        ; preds = %nestedBlock13
  br label %"GlobalIndexExpr::merge48"

"GlobalIndexExpr::else47":                        ; preds = %nestedBlock13
  call void @raise_exception(ptr @3)
  br label %"GlobalIndexExpr::merge48"

"GlobalIndexExpr::merge48":                       ; preds = %"GlobalIndexExpr::else47", %"GlobalIndexExpr::then46"
  %155 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %156 = load i32, ptr %155, align 4
  %157 = load i32, ptr %155, align 4
  store i32 %157, ptr %31, align 4
  %158 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %posY49 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then50", label %"GlobalIndexExpr::else51"

"GlobalIndexExpr::then50":                        ; preds = %"GlobalIndexExpr::merge48"
  br label %"GlobalIndexExpr::merge52"

"GlobalIndexExpr::else51":                        ; preds = %"GlobalIndexExpr::merge48"
  call void @raise_exception(ptr @4)
  br label %"GlobalIndexExpr::merge52"

"GlobalIndexExpr::merge52":                       ; preds = %"GlobalIndexExpr::else51", %"GlobalIndexExpr::then50"
  %159 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %160 = load i32, ptr %159, align 4
  %161 = load i32, ptr %159, align 4
  store i32 %161, ptr %158, align 4
  %162 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %163 = icmp eq i32 %162, 0
  br i1 %163, label %checkContinueBlock14, label %afterNestedBlock

"while:conditon":                                 ; preds = %afterNestedBlock53, %nestedBlock19
  %164 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %165 = icmp eq i32 %164, 0
  br i1 %165, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock54

while.end:                                        ; preds = %afterNestedBlock53, %end_block
  %166 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %167 = icmp eq i32 %166, 0
  br i1 %167, label %end_block263, label %decrement_block262

decrement_block:                                  ; preds = %"while:conditon"
  %168 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %169 = sub i32 %168, 1
  store i32 %169, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %170 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %171 = load ptr, ptr %170, align 8
  %172 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %171, i32 0, i32 10
  %173 = load ptr, ptr %172, align 8
  %174 = call i1 %173(ptr %34)
  %175 = xor i1 %174, true
  br i1 %175, label %"while:body", label %while.end

afterNestedBlock53:                               ; preds = %checkContinueBlock85, %nestedBlock84, %checkContinueBlock83, %nestedBlock82, %checkContinueBlock81, %merge, %checkContinueBlock79, %end_block255, %checkContinueBlock77, %nestedBlock76, %checkContinueBlock75, %nestedBlock74, %checkContinueBlock73, %"GlobalIndexExpr::merge220", %checkContinueBlock71, %"GlobalIndexExpr::merge215", %checkContinueBlock69, %afterIfElse168, %checkContinueBlock67, %afterIfElse158, %checkContinueBlock65, %afterIfElse146, %checkContinueBlock63, %afterIfElse137, %checkContinueBlock61, %afterIfElse128, %checkContinueBlock59, %afterIfElse119, %checkContinueBlock57, %afterIfElse, %checkContinueBlock55, %nestedBlock54
  %176 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %177 = icmp eq i32 %176, 0
  br i1 %177, label %"while:conditon", label %while.end

nestedBlock54:                                    ; preds = %"while:body"
  %isKeyPressed = alloca %DynamicType, align 8
  %178 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 false, ptr %178, align 1
  %179 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %180 = icmp eq i32 %179, 0
  br i1 %180, label %checkContinueBlock55, label %afterNestedBlock53

checkContinueBlock55:                             ; preds = %nestedBlock54
  %181 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %182 = icmp eq i32 %181, 0
  br i1 %182, label %nestedBlock56, label %afterNestedBlock53

nestedBlock56:                                    ; preds = %checkContinueBlock55
  %183 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %184 = load ptr, ptr %183, align 8
  %185 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %184, i32 0, i32 0
  %186 = load ptr, ptr %185, align 8
  %187 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %188 = getelementptr inbounds %KEYS_TYPE.0, ptr %187, i32 0, i32 3
  %KEY_UP = load i32, ptr %188, align 4
  %189 = call i1 %186(ptr %188, ptr %34)
  %190 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %191 = load ptr, ptr %190, align 8
  %192 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %191, i32 0, i32 2
  %193 = load ptr, ptr %192, align 8
  %194 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %195 = getelementptr inbounds %KEYS_TYPE.0, ptr %194, i32 0, i32 3
  %KEY_UP86 = load i32, ptr %195, align 4
  %196 = call i1 %193(ptr %195, ptr %34)
  %197 = select i1 %189, i1 true, i1 %196
  br i1 %197, label %then, label %orIf0

checkContinueBlock57:                             ; preds = %afterIfElse
  %198 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %199 = icmp eq i32 %198, 0
  br i1 %199, label %nestedBlock58, label %afterNestedBlock53

nestedBlock58:                                    ; preds = %checkContinueBlock57
  %200 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x116 = load i32, ptr %200, align 4
  %201 = icmp slt i32 %x116, 0
  br i1 %201, label %then117, label %else118

checkContinueBlock59:                             ; preds = %afterIfElse119
  %202 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %203 = icmp eq i32 %202, 0
  br i1 %203, label %nestedBlock60, label %afterNestedBlock53

nestedBlock60:                                    ; preds = %checkContinueBlock59
  %204 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x124 = load i32, ptr %204, align 4
  %screenWidth125 = load i32, ptr @screenWidth, align 4
  %205 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %206 = load i32, ptr %205, align 4
  %207 = sub i32 %screenWidth125, %206
  %208 = icmp sge i32 %x124, %207
  br i1 %208, label %then126, label %else127

checkContinueBlock61:                             ; preds = %afterIfElse128
  %209 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %210 = icmp eq i32 %209, 0
  br i1 %210, label %nestedBlock62, label %afterNestedBlock53

nestedBlock62:                                    ; preds = %checkContinueBlock61
  %211 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y134 = load i32, ptr %211, align 4
  %212 = icmp slt i32 %y134, 0
  br i1 %212, label %then135, label %else136

checkContinueBlock63:                             ; preds = %afterIfElse137
  %213 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %214 = icmp eq i32 %213, 0
  br i1 %214, label %nestedBlock64, label %afterNestedBlock53

nestedBlock64:                                    ; preds = %checkContinueBlock63
  %215 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y142 = load i32, ptr %215, align 4
  %screenHeight143 = load i32, ptr @screenHeight, align 4
  %216 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %217 = load i32, ptr %216, align 4
  %218 = sub i32 %screenHeight143, %217
  %219 = icmp sge i32 %y142, %218
  br i1 %219, label %then144, label %else145

checkContinueBlock65:                             ; preds = %afterIfElse146
  %220 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %221 = icmp eq i32 %220, 0
  br i1 %221, label %nestedBlock66, label %afterNestedBlock53

nestedBlock66:                                    ; preds = %checkContinueBlock65
  %222 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x152 = load i32, ptr %222, align 4
  %223 = getelementptr inbounds %Position.2, ptr %foodPos, i32 0, i32 0
  %x153 = load i32, ptr %223, align 4
  %224 = icmp eq i32 %x152, %x153
  %225 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y154 = load i32, ptr %225, align 4
  %226 = getelementptr inbounds %Position.2, ptr %foodPos, i32 0, i32 1
  %y155 = load i32, ptr %226, align 4
  %227 = icmp eq i32 %y154, %y155
  %228 = select i1 %224, i1 %227, i1 false
  br i1 %228, label %then156, label %else157

checkContinueBlock67:                             ; preds = %afterIfElse158
  %229 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %230 = icmp eq i32 %229, 0
  br i1 %230, label %nestedBlock68, label %afterNestedBlock53

nestedBlock68:                                    ; preds = %checkContinueBlock67
  %231 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %232 = load i1, ptr %231, align 1
  br i1 %232, label %then166, label %else167

checkContinueBlock69:                             ; preds = %afterIfElse168
  %233 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %234 = icmp eq i32 %233, 0
  br i1 %234, label %nestedBlock70, label %afterNestedBlock53

nestedBlock70:                                    ; preds = %checkContinueBlock69
  %posX212 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then213", label %"GlobalIndexExpr::else214"

checkContinueBlock71:                             ; preds = %"GlobalIndexExpr::merge215"
  %235 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %236 = icmp eq i32 %235, 0
  br i1 %236, label %nestedBlock72, label %afterNestedBlock53

nestedBlock72:                                    ; preds = %checkContinueBlock71
  %posY217 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then218", label %"GlobalIndexExpr::else219"

checkContinueBlock73:                             ; preds = %"GlobalIndexExpr::merge220"
  %237 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %238 = icmp eq i32 %237, 0
  br i1 %238, label %nestedBlock74, label %afterNestedBlock53

nestedBlock74:                                    ; preds = %checkContinueBlock73
  %239 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %240 = load ptr, ptr %239, align 8
  %241 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %240, i32 0, i32 7
  %242 = load ptr, ptr %241, align 8
  call void %242(ptr %34)
  %243 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %244 = icmp eq i32 %243, 0
  br i1 %244, label %checkContinueBlock75, label %afterNestedBlock53

checkContinueBlock75:                             ; preds = %nestedBlock74
  %245 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %246 = icmp eq i32 %245, 0
  br i1 %246, label %nestedBlock76, label %afterNestedBlock53

nestedBlock76:                                    ; preds = %checkContinueBlock75
  %247 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %248 = load ptr, ptr %247, align 8
  %249 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %248, i32 0, i32 13
  %250 = load ptr, ptr %249, align 8
  %251 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 5
  %252 = getelementptr inbounds %COLORS_TYPE.1, ptr %251, i32 0, i32 0
  %WHITE = load i32, ptr %252, align 4
  call void %250(ptr %252, ptr %34)
  %253 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %254 = icmp eq i32 %253, 0
  br i1 %254, label %checkContinueBlock77, label %afterNestedBlock53

checkContinueBlock77:                             ; preds = %nestedBlock76
  %255 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %256 = icmp eq i32 %255, 0
  br i1 %256, label %nestedBlock78, label %afterNestedBlock53

nestedBlock78:                                    ; preds = %checkContinueBlock77
  %tail222 = load i32, ptr %tail, align 4
  %257 = sub i32 %tail222, 1
  %index223 = alloca i32, align 4
  store i32 0, ptr %index223, align 4
  store i32 0, ptr %index223, align 4
  br label %"ForLoop::loopCondition224"

checkContinueBlock79:                             ; preds = %end_block255
  %258 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %259 = icmp eq i32 %258, 0
  br i1 %259, label %nestedBlock80, label %afterNestedBlock53

nestedBlock80:                                    ; preds = %checkContinueBlock79
  %260 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %261 = load ptr, ptr %260, align 8
  %262 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %261, i32 0, i32 3
  %263 = load ptr, ptr %262, align 8
  %screenWidth256 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if, label %else257

checkContinueBlock81:                             ; preds = %merge
  %264 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %265 = icmp eq i32 %264, 0
  br i1 %265, label %nestedBlock82, label %afterNestedBlock53

nestedBlock82:                                    ; preds = %checkContinueBlock81
  %266 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %267 = load ptr, ptr %266, align 8
  %268 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %267, i32 0, i32 8
  %269 = load ptr, ptr %268, align 8
  %270 = getelementptr inbounds %Position.2, ptr %foodPos, i32 0, i32 0
  %x258 = load i32, ptr %270, align 4
  %271 = getelementptr inbounds %Position.2, ptr %foodPos, i32 0, i32 1
  %y259 = load i32, ptr %271, align 4
  %side260 = load i32, ptr @side, align 4
  %side261 = load i32, ptr @side, align 4
  %272 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 5
  %273 = getelementptr inbounds %COLORS_TYPE.1, ptr %272, i32 0, i32 2
  %GREEN = load i32, ptr %273, align 4
  call void %269(ptr %270, ptr %271, ptr @side, ptr @side, ptr %273, ptr %34)
  %274 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %275 = icmp eq i32 %274, 0
  br i1 %275, label %checkContinueBlock83, label %afterNestedBlock53

checkContinueBlock83:                             ; preds = %nestedBlock82
  %276 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %277 = icmp eq i32 %276, 0
  br i1 %277, label %nestedBlock84, label %afterNestedBlock53

nestedBlock84:                                    ; preds = %checkContinueBlock83
  %278 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %279 = load ptr, ptr %278, align 8
  %280 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %279, i32 0, i32 15
  %281 = load ptr, ptr %280, align 8
  call void %281(ptr %34)
  %282 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %283 = icmp eq i32 %282, 0
  br i1 %283, label %checkContinueBlock85, label %afterNestedBlock53

checkContinueBlock85:                             ; preds = %nestedBlock84
  br label %afterNestedBlock53

then:                                             ; preds = %nestedBlock56
  br label %nestedBlock91

orIf0:                                            ; preds = %nestedBlock56
  %284 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %285 = load ptr, ptr %284, align 8
  %286 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %285, i32 0, i32 0
  %287 = load ptr, ptr %286, align 8
  %288 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %289 = getelementptr inbounds %KEYS_TYPE.0, ptr %288, i32 0, i32 2
  %KEY_DOWN = load i32, ptr %289, align 4
  %290 = call i1 %287(ptr %289, ptr %34)
  %291 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %292 = load ptr, ptr %291, align 8
  %293 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %292, i32 0, i32 2
  %294 = load ptr, ptr %293, align 8
  %295 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %296 = getelementptr inbounds %KEYS_TYPE.0, ptr %295, i32 0, i32 2
  %KEY_DOWN87 = load i32, ptr %296, align 4
  %297 = call i1 %294(ptr %296, ptr %34)
  %298 = select i1 %290, i1 true, i1 %297
  br i1 %298, label %orIfThen0, label %orIf1

orIf1:                                            ; preds = %orIf0
  %299 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %300 = load ptr, ptr %299, align 8
  %301 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %300, i32 0, i32 0
  %302 = load ptr, ptr %301, align 8
  %303 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %304 = getelementptr inbounds %KEYS_TYPE.0, ptr %303, i32 0, i32 0
  %KEY_RIGHT = load i32, ptr %304, align 4
  %305 = call i1 %302(ptr %304, ptr %34)
  %306 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %307 = load ptr, ptr %306, align 8
  %308 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %307, i32 0, i32 2
  %309 = load ptr, ptr %308, align 8
  %310 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %311 = getelementptr inbounds %KEYS_TYPE.0, ptr %310, i32 0, i32 0
  %KEY_RIGHT88 = load i32, ptr %311, align 4
  %312 = call i1 %309(ptr %311, ptr %34)
  %313 = select i1 %305, i1 true, i1 %312
  br i1 %313, label %orIfThen1, label %orIf2

orIf2:                                            ; preds = %orIf1
  %314 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %315 = load ptr, ptr %314, align 8
  %316 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %315, i32 0, i32 0
  %317 = load ptr, ptr %316, align 8
  %318 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %319 = getelementptr inbounds %KEYS_TYPE.0, ptr %318, i32 0, i32 1
  %KEY_LEFT = load i32, ptr %319, align 4
  %320 = call i1 %317(ptr %319, ptr %34)
  %321 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %322 = load ptr, ptr %321, align 8
  %323 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %322, i32 0, i32 2
  %324 = load ptr, ptr %323, align 8
  %325 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 6
  %326 = getelementptr inbounds %KEYS_TYPE.0, ptr %325, i32 0, i32 1
  %KEY_LEFT89 = load i32, ptr %326, align 4
  %327 = call i1 %324(ptr %326, ptr %34)
  %328 = select i1 %320, i1 true, i1 %327
  br i1 %328, label %orIfThen2, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock97

orIfThen1:                                        ; preds = %orIf1
  br label %nestedBlock104

orIfThen2:                                        ; preds = %orIf2
  br label %nestedBlock110

else:                                             ; preds = %orIf2
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock109, %afterNestedBlock103, %afterNestedBlock96, %afterNestedBlock90
  %329 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %330 = icmp eq i32 %329, 0
  br i1 %330, label %checkContinueBlock57, label %afterNestedBlock53

afterNestedBlock90:                               ; preds = %checkContinueBlock94, %nestedBlock93, %checkContinueBlock92, %nestedBlock91
  br label %afterIfElse

nestedBlock91:                                    ; preds = %then
  %331 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %332 = load i1, ptr %331, align 1
  %333 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %333, align 1
  %334 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %335 = icmp eq i32 %334, 0
  br i1 %335, label %checkContinueBlock92, label %afterNestedBlock90

checkContinueBlock92:                             ; preds = %nestedBlock91
  %336 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %337 = icmp eq i32 %336, 0
  br i1 %337, label %nestedBlock93, label %afterNestedBlock90

nestedBlock93:                                    ; preds = %checkContinueBlock92
  %338 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y = load i32, ptr %338, align 4
  %339 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y95 = load i32, ptr %339, align 4
  %340 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %341 = load i32, ptr %340, align 4
  %342 = sub i32 %y95, %341
  store i32 %342, ptr %338, align 4
  %343 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %344 = icmp eq i32 %343, 0
  br i1 %344, label %checkContinueBlock94, label %afterNestedBlock90

checkContinueBlock94:                             ; preds = %nestedBlock93
  br label %afterNestedBlock90

afterNestedBlock96:                               ; preds = %checkContinueBlock100, %nestedBlock99, %checkContinueBlock98, %nestedBlock97
  br label %afterIfElse

nestedBlock97:                                    ; preds = %orIfThen0
  %345 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %346 = load i1, ptr %345, align 1
  %347 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %347, align 1
  %348 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %349 = icmp eq i32 %348, 0
  br i1 %349, label %checkContinueBlock98, label %afterNestedBlock96

checkContinueBlock98:                             ; preds = %nestedBlock97
  %350 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %351 = icmp eq i32 %350, 0
  br i1 %351, label %nestedBlock99, label %afterNestedBlock96

nestedBlock99:                                    ; preds = %checkContinueBlock98
  %352 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y101 = load i32, ptr %352, align 4
  %353 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y102 = load i32, ptr %353, align 4
  %354 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %355 = load i32, ptr %354, align 4
  %356 = add i32 %y102, %355
  store i32 %356, ptr %352, align 4
  %357 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %358 = icmp eq i32 %357, 0
  br i1 %358, label %checkContinueBlock100, label %afterNestedBlock96

checkContinueBlock100:                            ; preds = %nestedBlock99
  br label %afterNestedBlock96

afterNestedBlock103:                              ; preds = %checkContinueBlock107, %nestedBlock106, %checkContinueBlock105, %nestedBlock104
  br label %afterIfElse

nestedBlock104:                                   ; preds = %orIfThen1
  %359 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %360 = load i1, ptr %359, align 1
  %361 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %361, align 1
  %362 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %363 = icmp eq i32 %362, 0
  br i1 %363, label %checkContinueBlock105, label %afterNestedBlock103

checkContinueBlock105:                            ; preds = %nestedBlock104
  %364 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %365 = icmp eq i32 %364, 0
  br i1 %365, label %nestedBlock106, label %afterNestedBlock103

nestedBlock106:                                   ; preds = %checkContinueBlock105
  %366 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x = load i32, ptr %366, align 4
  %367 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x108 = load i32, ptr %367, align 4
  %368 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %369 = load i32, ptr %368, align 4
  %370 = add i32 %x108, %369
  store i32 %370, ptr %366, align 4
  %371 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %372 = icmp eq i32 %371, 0
  br i1 %372, label %checkContinueBlock107, label %afterNestedBlock103

checkContinueBlock107:                            ; preds = %nestedBlock106
  br label %afterNestedBlock103

afterNestedBlock109:                              ; preds = %checkContinueBlock113, %nestedBlock112, %checkContinueBlock111, %nestedBlock110
  br label %afterIfElse

nestedBlock110:                                   ; preds = %orIfThen2
  %373 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %374 = load i1, ptr %373, align 1
  %375 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %375, align 1
  %376 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %377 = icmp eq i32 %376, 0
  br i1 %377, label %checkContinueBlock111, label %afterNestedBlock109

checkContinueBlock111:                            ; preds = %nestedBlock110
  %378 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %379 = icmp eq i32 %378, 0
  br i1 %379, label %nestedBlock112, label %afterNestedBlock109

nestedBlock112:                                   ; preds = %checkContinueBlock111
  %380 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x114 = load i32, ptr %380, align 4
  %381 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x115 = load i32, ptr %381, align 4
  %382 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %383 = load i32, ptr %382, align 4
  %384 = sub i32 %x115, %383
  store i32 %384, ptr %380, align 4
  %385 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %386 = icmp eq i32 %385, 0
  br i1 %386, label %checkContinueBlock113, label %afterNestedBlock109

checkContinueBlock113:                            ; preds = %nestedBlock112
  br label %afterNestedBlock109

then117:                                          ; preds = %nestedBlock58
  br label %nestedBlock121

else118:                                          ; preds = %nestedBlock58
  br label %afterIfElse119

afterIfElse119:                                   ; preds = %else118, %afterNestedBlock120
  %387 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %388 = icmp eq i32 %387, 0
  br i1 %388, label %checkContinueBlock59, label %afterNestedBlock53

afterNestedBlock120:                              ; preds = %checkContinueBlock122, %nestedBlock121
  br label %afterIfElse119

nestedBlock121:                                   ; preds = %then117
  %389 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x123 = load i32, ptr %389, align 4
  store i32 0, ptr %389, align 4
  %390 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %391 = icmp eq i32 %390, 0
  br i1 %391, label %checkContinueBlock122, label %afterNestedBlock120

checkContinueBlock122:                            ; preds = %nestedBlock121
  br label %afterNestedBlock120

then126:                                          ; preds = %nestedBlock60
  br label %nestedBlock130

else127:                                          ; preds = %nestedBlock60
  br label %afterIfElse128

afterIfElse128:                                   ; preds = %else127, %afterNestedBlock129
  %392 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %393 = icmp eq i32 %392, 0
  br i1 %393, label %checkContinueBlock61, label %afterNestedBlock53

afterNestedBlock129:                              ; preds = %checkContinueBlock131, %nestedBlock130
  br label %afterIfElse128

nestedBlock130:                                   ; preds = %then126
  %394 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x132 = load i32, ptr %394, align 4
  %screenWidth133 = load i32, ptr @screenWidth, align 4
  %395 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %396 = load i32, ptr %395, align 4
  %397 = sub i32 %screenWidth133, %396
  store i32 %397, ptr %394, align 4
  %398 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %399 = icmp eq i32 %398, 0
  br i1 %399, label %checkContinueBlock131, label %afterNestedBlock129

checkContinueBlock131:                            ; preds = %nestedBlock130
  br label %afterNestedBlock129

then135:                                          ; preds = %nestedBlock62
  br label %nestedBlock139

else136:                                          ; preds = %nestedBlock62
  br label %afterIfElse137

afterIfElse137:                                   ; preds = %else136, %afterNestedBlock138
  %400 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %401 = icmp eq i32 %400, 0
  br i1 %401, label %checkContinueBlock63, label %afterNestedBlock53

afterNestedBlock138:                              ; preds = %checkContinueBlock140, %nestedBlock139
  br label %afterIfElse137

nestedBlock139:                                   ; preds = %then135
  %402 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y141 = load i32, ptr %402, align 4
  store i32 0, ptr %402, align 4
  %403 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %404 = icmp eq i32 %403, 0
  br i1 %404, label %checkContinueBlock140, label %afterNestedBlock138

checkContinueBlock140:                            ; preds = %nestedBlock139
  br label %afterNestedBlock138

then144:                                          ; preds = %nestedBlock64
  br label %nestedBlock148

else145:                                          ; preds = %nestedBlock64
  br label %afterIfElse146

afterIfElse146:                                   ; preds = %else145, %afterNestedBlock147
  %405 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %406 = icmp eq i32 %405, 0
  br i1 %406, label %checkContinueBlock65, label %afterNestedBlock53

afterNestedBlock147:                              ; preds = %checkContinueBlock149, %nestedBlock148
  br label %afterIfElse146

nestedBlock148:                                   ; preds = %then144
  %407 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y150 = load i32, ptr %407, align 4
  %screenHeight151 = load i32, ptr @screenHeight, align 4
  %408 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %409 = load i32, ptr %408, align 4
  %410 = sub i32 %screenHeight151, %409
  store i32 %410, ptr %407, align 4
  %411 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %412 = icmp eq i32 %411, 0
  br i1 %412, label %checkContinueBlock149, label %afterNestedBlock147

checkContinueBlock149:                            ; preds = %nestedBlock148
  br label %afterNestedBlock147

then156:                                          ; preds = %nestedBlock66
  br label %nestedBlock160

else157:                                          ; preds = %nestedBlock66
  br label %afterIfElse158

afterIfElse158:                                   ; preds = %else157, %afterNestedBlock159
  %413 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %414 = icmp eq i32 %413, 0
  br i1 %414, label %checkContinueBlock67, label %afterNestedBlock53

afterNestedBlock159:                              ; preds = %checkContinueBlock163, %nestedBlock162, %checkContinueBlock161, %nestedBlock160
  br label %afterIfElse158

nestedBlock160:                                   ; preds = %then156
  %415 = call ptr @getFoodPosition()
  %416 = load %Position.2, ptr %415, align 4
  store %Position.2 %416, ptr %foodPos, align 4
  %417 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %418 = icmp eq i32 %417, 0
  br i1 %418, label %checkContinueBlock161, label %afterNestedBlock159

checkContinueBlock161:                            ; preds = %nestedBlock160
  %419 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %420 = icmp eq i32 %419, 0
  br i1 %420, label %nestedBlock162, label %afterNestedBlock159

nestedBlock162:                                   ; preds = %checkContinueBlock161
  %tail164 = load i32, ptr %tail, align 4
  %tail165 = load i32, ptr %tail, align 4
  %421 = add i32 %tail165, 1
  store i32 %421, ptr %tail, align 4
  %422 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %423 = icmp eq i32 %422, 0
  br i1 %423, label %checkContinueBlock163, label %afterNestedBlock159

checkContinueBlock163:                            ; preds = %nestedBlock162
  br label %afterNestedBlock159

then166:                                          ; preds = %nestedBlock68
  br label %nestedBlock170

else167:                                          ; preds = %nestedBlock68
  br label %afterIfElse168

afterIfElse168:                                   ; preds = %else167, %afterNestedBlock169
  %424 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %425 = icmp eq i32 %424, 0
  br i1 %425, label %checkContinueBlock69, label %afterNestedBlock53

afterNestedBlock169:                              ; preds = %checkContinueBlock171, %end_block211
  br label %afterIfElse168

nestedBlock170:                                   ; preds = %then166
  %tail172 = load i32, ptr %tail, align 4
  %426 = sub i32 %tail172, 1
  %index = alloca i32, align 4
  store i32 0, ptr %index, align 4
  store i32 %426, ptr %index, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock171:                            ; preds = %end_block211
  br label %afterNestedBlock169

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock176, %nestedBlock170
  %427 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %428 = icmp eq i32 %427, 0
  br i1 %428, label %end_block174, label %decrement_block173

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock177

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %429 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %430 = icmp eq i32 %429, 0
  br i1 %430, label %end_block211, label %decrement_block210

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %431 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %432 = icmp eq i32 %431, 0
  br i1 %432, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block173:                               ; preds = %"ForLoop::loopCondition"
  %433 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %434 = sub i32 %433, 1
  store i32 %434, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block174

end_block174:                                     ; preds = %decrement_block173, %"ForLoop::loopCondition"
  %index175 = load i32, ptr %index, align 4
  br i1 true, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block174
  %435 = icmp sge i32 %index175, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block174
  %436 = icmp sle i32 %index175, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %437 = phi i1 [ %435, %"ForLoop::Conditon::trueBlock" ], [ %436, %"ForLoop::Conditon::falseBlock" ]
  br i1 %437, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock176:                              ; preds = %checkContinueBlock180, %"GlobalIndexExpr::merge206", %checkContinueBlock178, %"GlobalIndexExpr::merge190"
  %438 = add i32 %index175, -1
  store i32 %438, ptr %index, align 4
  br label %"ForLoop::loopCondition"

nestedBlock177:                                   ; preds = %"ForLoop::loopBody"
  %index181 = load i32, ptr %index, align 4
  %posX182 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %index181, 10000
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %index181, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then183", label %"GlobalIndexExpr::else184"

checkContinueBlock178:                            ; preds = %"GlobalIndexExpr::merge190"
  %439 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %440 = icmp eq i32 %439, 0
  br i1 %440, label %nestedBlock179, label %afterNestedBlock176

nestedBlock179:                                   ; preds = %checkContinueBlock178
  %index194 = load i32, ptr %index, align 4
  %posY195 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan199" = icmp slt i32 %index194, 10000
  %"GlobalIndexExpr::isGreaterThan200" = icmp sge i32 %index194, 0
  %"GlobalIndexExpr::isWithinBounds201" = and i1 %"GlobalIndexExpr::isLessThan199", %"GlobalIndexExpr::isGreaterThan200"
  br i1 %"GlobalIndexExpr::isWithinBounds201", label %"GlobalIndexExpr::then196", label %"GlobalIndexExpr::else197"

checkContinueBlock180:                            ; preds = %"GlobalIndexExpr::merge206"
  br label %afterNestedBlock176

"GlobalIndexExpr::then183":                       ; preds = %nestedBlock177
  br label %"GlobalIndexExpr::merge185"

"GlobalIndexExpr::else184":                       ; preds = %nestedBlock177
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge185"

"GlobalIndexExpr::merge185":                      ; preds = %"GlobalIndexExpr::else184", %"GlobalIndexExpr::then183"
  %441 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index181
  %442 = load i32, ptr %441, align 4
  %index186 = load i32, ptr %index, align 4
  %443 = sub i32 %index186, 1
  %posX187 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan191" = icmp slt i32 %443, 10000
  %"GlobalIndexExpr::isGreaterThan192" = icmp sge i32 %443, 0
  %"GlobalIndexExpr::isWithinBounds193" = and i1 %"GlobalIndexExpr::isLessThan191", %"GlobalIndexExpr::isGreaterThan192"
  br i1 %"GlobalIndexExpr::isWithinBounds193", label %"GlobalIndexExpr::then188", label %"GlobalIndexExpr::else189"

"GlobalIndexExpr::then188":                       ; preds = %"GlobalIndexExpr::merge185"
  br label %"GlobalIndexExpr::merge190"

"GlobalIndexExpr::else189":                       ; preds = %"GlobalIndexExpr::merge185"
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge190"

"GlobalIndexExpr::merge190":                      ; preds = %"GlobalIndexExpr::else189", %"GlobalIndexExpr::then188"
  %444 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %443
  %445 = load i32, ptr %444, align 4
  %446 = load i32, ptr %444, align 4
  store i32 %446, ptr %441, align 4
  %447 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %448 = icmp eq i32 %447, 0
  br i1 %448, label %checkContinueBlock178, label %afterNestedBlock176

"GlobalIndexExpr::then196":                       ; preds = %nestedBlock179
  br label %"GlobalIndexExpr::merge198"

"GlobalIndexExpr::else197":                       ; preds = %nestedBlock179
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge198"

"GlobalIndexExpr::merge198":                      ; preds = %"GlobalIndexExpr::else197", %"GlobalIndexExpr::then196"
  %449 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index194
  %450 = load i32, ptr %449, align 4
  %index202 = load i32, ptr %index, align 4
  %451 = sub i32 %index202, 1
  %posY203 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan207" = icmp slt i32 %451, 10000
  %"GlobalIndexExpr::isGreaterThan208" = icmp sge i32 %451, 0
  %"GlobalIndexExpr::isWithinBounds209" = and i1 %"GlobalIndexExpr::isLessThan207", %"GlobalIndexExpr::isGreaterThan208"
  br i1 %"GlobalIndexExpr::isWithinBounds209", label %"GlobalIndexExpr::then204", label %"GlobalIndexExpr::else205"

"GlobalIndexExpr::then204":                       ; preds = %"GlobalIndexExpr::merge198"
  br label %"GlobalIndexExpr::merge206"

"GlobalIndexExpr::else205":                       ; preds = %"GlobalIndexExpr::merge198"
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge206"

"GlobalIndexExpr::merge206":                      ; preds = %"GlobalIndexExpr::else205", %"GlobalIndexExpr::then204"
  %452 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %451
  %453 = load i32, ptr %452, align 4
  %454 = load i32, ptr %452, align 4
  store i32 %454, ptr %449, align 4
  %455 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %456 = icmp eq i32 %455, 0
  br i1 %456, label %checkContinueBlock180, label %afterNestedBlock176

decrement_block210:                               ; preds = %"ForLoop::afterLoop"
  %457 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %458 = sub i32 %457, 1
  store i32 %458, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block211

end_block211:                                     ; preds = %decrement_block210, %"ForLoop::afterLoop"
  %459 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %460 = icmp eq i32 %459, 0
  br i1 %460, label %checkContinueBlock171, label %afterNestedBlock169

"GlobalIndexExpr::then213":                       ; preds = %nestedBlock70
  br label %"GlobalIndexExpr::merge215"

"GlobalIndexExpr::else214":                       ; preds = %nestedBlock70
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge215"

"GlobalIndexExpr::merge215":                      ; preds = %"GlobalIndexExpr::else214", %"GlobalIndexExpr::then213"
  %461 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %462 = load i32, ptr %461, align 4
  %463 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 0
  %x216 = load i32, ptr %463, align 4
  %464 = load i32, ptr %463, align 4
  store i32 %464, ptr %461, align 4
  %465 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %466 = icmp eq i32 %465, 0
  br i1 %466, label %checkContinueBlock71, label %afterNestedBlock53

"GlobalIndexExpr::then218":                       ; preds = %nestedBlock72
  br label %"GlobalIndexExpr::merge220"

"GlobalIndexExpr::else219":                       ; preds = %nestedBlock72
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge220"

"GlobalIndexExpr::merge220":                      ; preds = %"GlobalIndexExpr::else219", %"GlobalIndexExpr::then218"
  %467 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %468 = load i32, ptr %467, align 4
  %469 = getelementptr inbounds %Position.2, ptr %newPos, i32 0, i32 1
  %y221 = load i32, ptr %469, align 4
  %470 = load i32, ptr %469, align 4
  store i32 %470, ptr %467, align 4
  %471 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %472 = icmp eq i32 %471, 0
  br i1 %472, label %checkContinueBlock73, label %afterNestedBlock53

"ForLoop::loopCondition224":                      ; preds = %afterNestedBlock234, %nestedBlock78
  %473 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %474 = icmp eq i32 %473, 0
  br i1 %474, label %end_block229, label %decrement_block228

"ForLoop::loopBody225":                           ; preds = %"ForLoop::breakLoop227"
  br label %nestedBlock235

"ForLoop::afterLoop226":                          ; preds = %"ForLoop::breakLoop227", %"ForLoop::Conditon::mergeBlock233"
  %475 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %476 = icmp eq i32 %475, 0
  br i1 %476, label %end_block255, label %decrement_block254

"ForLoop::breakLoop227":                          ; preds = %"ForLoop::Conditon::mergeBlock233"
  %477 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %478 = icmp eq i32 %477, 0
  br i1 %478, label %"ForLoop::loopBody225", label %"ForLoop::afterLoop226"

decrement_block228:                               ; preds = %"ForLoop::loopCondition224"
  %479 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %480 = sub i32 %479, 1
  store i32 %480, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block229

end_block229:                                     ; preds = %decrement_block228, %"ForLoop::loopCondition224"
  %index230 = load i32, ptr %index223, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock231", label %"ForLoop::Conditon::falseBlock232"

"ForLoop::Conditon::trueBlock231":                ; preds = %end_block229
  %481 = icmp sge i32 %index230, %257
  br label %"ForLoop::Conditon::mergeBlock233"

"ForLoop::Conditon::falseBlock232":               ; preds = %end_block229
  %482 = icmp sle i32 %index230, %257
  br label %"ForLoop::Conditon::mergeBlock233"

"ForLoop::Conditon::mergeBlock233":               ; preds = %"ForLoop::Conditon::falseBlock232", %"ForLoop::Conditon::trueBlock231"
  %483 = phi i1 [ %481, %"ForLoop::Conditon::trueBlock231" ], [ %482, %"ForLoop::Conditon::falseBlock232" ]
  br i1 %483, label %"ForLoop::breakLoop227", label %"ForLoop::afterLoop226"

afterNestedBlock234:                              ; preds = %checkContinueBlock236, %"GlobalIndexExpr::merge249"
  %484 = add i32 %index230, 1
  store i32 %484, ptr %index223, align 4
  br label %"ForLoop::loopCondition224"

nestedBlock235:                                   ; preds = %"ForLoop::loopBody225"
  %485 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 0
  %486 = load ptr, ptr %485, align 8
  %487 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %486, i32 0, i32 8
  %488 = load ptr, ptr %487, align 8
  %index237 = load i32, ptr %index223, align 4
  %posX238 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan242" = icmp slt i32 %index237, 10000
  %"GlobalIndexExpr::isGreaterThan243" = icmp sge i32 %index237, 0
  %"GlobalIndexExpr::isWithinBounds244" = and i1 %"GlobalIndexExpr::isLessThan242", %"GlobalIndexExpr::isGreaterThan243"
  br i1 %"GlobalIndexExpr::isWithinBounds244", label %"GlobalIndexExpr::then239", label %"GlobalIndexExpr::else240"

checkContinueBlock236:                            ; preds = %"GlobalIndexExpr::merge249"
  br label %afterNestedBlock234

"GlobalIndexExpr::then239":                       ; preds = %nestedBlock235
  br label %"GlobalIndexExpr::merge241"

"GlobalIndexExpr::else240":                       ; preds = %nestedBlock235
  call void @raise_exception(ptr @14)
  br label %"GlobalIndexExpr::merge241"

"GlobalIndexExpr::merge241":                      ; preds = %"GlobalIndexExpr::else240", %"GlobalIndexExpr::then239"
  %489 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index237
  %490 = load i32, ptr %489, align 4
  %index245 = load i32, ptr %index223, align 4
  %posY246 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan250" = icmp slt i32 %index245, 10000
  %"GlobalIndexExpr::isGreaterThan251" = icmp sge i32 %index245, 0
  %"GlobalIndexExpr::isWithinBounds252" = and i1 %"GlobalIndexExpr::isLessThan250", %"GlobalIndexExpr::isGreaterThan251"
  br i1 %"GlobalIndexExpr::isWithinBounds252", label %"GlobalIndexExpr::then247", label %"GlobalIndexExpr::else248"

"GlobalIndexExpr::then247":                       ; preds = %"GlobalIndexExpr::merge241"
  br label %"GlobalIndexExpr::merge249"

"GlobalIndexExpr::else248":                       ; preds = %"GlobalIndexExpr::merge241"
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge249"

"GlobalIndexExpr::merge249":                      ; preds = %"GlobalIndexExpr::else248", %"GlobalIndexExpr::then247"
  %491 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index245
  %492 = load i32, ptr %491, align 4
  %side = load i32, ptr @side, align 4
  %side253 = load i32, ptr @side, align 4
  %493 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 5
  %494 = getelementptr inbounds %COLORS_TYPE.1, ptr %493, i32 0, i32 3
  %BLUE = load i32, ptr %494, align 4
  call void %488(ptr %489, ptr %491, ptr @side, ptr @side, ptr %494, ptr %34)
  %495 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %496 = icmp eq i32 %495, 0
  br i1 %496, label %checkContinueBlock236, label %afterNestedBlock234

decrement_block254:                               ; preds = %"ForLoop::afterLoop226"
  %497 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %498 = sub i32 %497, 1
  store i32 %498, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block255

end_block255:                                     ; preds = %decrement_block254, %"ForLoop::afterLoop226"
  %499 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %500 = icmp eq i32 %499, 0
  br i1 %500, label %checkContinueBlock79, label %afterNestedBlock53

if:                                               ; preds = %nestedBlock80
  call void @raise_exception(ptr @16)
  br label %merge

else257:                                          ; preds = %nestedBlock80
  %501 = sdiv i32 %screenWidth256, 5
  br label %merge

merge:                                            ; preds = %else257, %if
  %502 = alloca i32, align 4
  store i32 %501, ptr %502, align 4
  %503 = alloca i32, align 4
  store i32 120, ptr %503, align 4
  %504 = alloca float, align 4
  store float 3.500000e+01, ptr %504, align 4
  %505 = getelementptr inbounds %FlowWingAnim, ptr %34, i32 0, i32 5
  %506 = getelementptr inbounds %COLORS_TYPE.1, ptr %505, i32 0, i32 4
  %DARKBLUE = load i32, ptr %506, align 4
  call void %263(ptr %502, ptr %503, ptr %504, ptr %506, ptr %34)
  %507 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %508 = icmp eq i32 %507, 0
  br i1 %508, label %checkContinueBlock81, label %afterNestedBlock53

decrement_block262:                               ; preds = %while.end
  %509 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %510 = sub i32 %509, 1
  store i32 %510, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block263

end_block263:                                     ; preds = %decrement_block262, %while.end
  %511 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %512 = icmp eq i32 %511, 0
  br i1 %512, label %checkContinueBlock20, label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock23
  ret i32 0

mergeBlock:                                       ; No predecessors!
  %513 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %514 = icmp eq i32 %513, 0
  br i1 %514, label %checkContinueBlock24, label %afterNestedBlock
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
!15 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!16 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!17 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!18 = !{!"DrawText:rt:pr:27"}
!19 = !{!"SetTargetFPS:rt:pr:27"}
!20 = !{!"EndDrawing:rt:pr:27"}
!21 = !{!"InitWindow:rt:pr:27"}
!22 = !{!"ClearBackground:rt:pr:27"}
!23 = !{!"GetScreenWidth:rt:pr:28"}
!24 = !{!"DrawCircle:rt:pr:27"}
!25 = !{!"DrawRectangle:rt:pr:27"}
!26 = !{!"WindowShouldClose:rt:pr:34"}
!27 = !{!"TextFormat:rt:pr:33"}
!28 = !{!"BeginDrawing:rt:pr:27"}
!29 = !{!"time:rt:pr:28"}
!30 = !{!"IsKeyPressed:rt:pr:34"}
!31 = !{!"CloseWindow:rt:pr:27"}
!32 = !{!"GetScreenHeight:rt:pr:28"}
!33 = !{!"getRandomNumber:rt:pr:28"}
!34 = !{!"IsKeyDown:rt:pr:34"}
!35 = !{!"rand:rt:pr:28"}
!36 = !{!"srand:rt:pr:27"}
!37 = !{!"getFoodPosition:rt:ob:Position"}
!38 = !{!"main:rt:pr:28"}
