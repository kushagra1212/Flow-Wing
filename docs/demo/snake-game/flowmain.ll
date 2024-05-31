; ModuleID = 'flowmain'
source_filename = "flowmain"

%"FlowWingAnim::VTableType" = type { ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr, ptr }
%Texture.0 = type { i32, i32, i32, i32, i32 }
%Position.3 = type { i32, i32 }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
%FlowWingAnim = type { ptr, i32, i32, ptr, i32, %COLORS_TYPE.2, %KEYS_TYPE.1 }
%COLORS_TYPE.2 = type { i32, i32, i32, i32, i32 }
%KEYS_TYPE.1 = type { i32, i32, i32, i32 }

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
@0 = private unnamed_addr constant [696 x i8] c"\0A\1B[33m22| \1B[0m\1B[0m  const speed = 10\0A\1B[0m\1B[33m23| \1B[0m\1B[0m  var tail: int = 1\0A\1B[0m\1B[33m24| \1B[0m\1B[0m  var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m25| \1B[0m\1B[0m  var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m26| \1B[0m\1B[31m\1B[1m  posX[0]= 0\0A\1B[0m\1B[32m\1B[1m        \0A   ~~~~~~~^\1B[0m\0A\1B[33m27| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 26:8\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@1 = private unnamed_addr constant [692 x i8] c"\0A\1B[33m23| \1B[0m\1B[0m  var tail: int = 1\0A\1B[0m\1B[33m24| \1B[0m\1B[0m  var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m25| \1B[0m\1B[0m  var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m26| \1B[0m\1B[0m  posX[0]= 0\0A\1B[0m\1B[33m27| \1B[0m\1B[31m\1B[1m  posY[0]= 0\0A\1B[0m\1B[32m\1B[1m        \0A   ~~~~~~~^\1B[0m\0A\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[33m31| \1B[0m\1B[0m    y: posY[0]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 27:8\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [780 x i8] c"\0A\1B[33m26| \1B[0m\1B[0m  posX[0]= 0\0A\1B[0m\1B[33m27| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[31m\1B[1m    x: posX[0],\0A\1B[0m\1B[32m\1B[1m             \0A   ~~~~~~~~~~~~^\1B[0m\0A\1B[33m31| \1B[0m\1B[0m    y: posY[0]\0A\1B[0m\1B[33m32| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m33| \1B[0m\1B[0m  const fgAnim: FlowWingAnim = new FlowWingAnim(screenWidth, screenHeight, \22snake-game-in-flowwing\22, 60)\0A\1B[0m\1B[33m34| \1B[0m\1B[0m  var bird:Texture = LoadTexture(\22/Users/apple/Downloads/images.png\22)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 30:13\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [768 x i8] c"\0A\1B[33m27| \1B[0m\1B[0m  posY[0]= 0\0A\1B[0m\1B[33m28| \1B[0m\1B[0m  var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m29| \1B[0m\1B[0m  var newPos: Position = {\0A\1B[0m\1B[33m30| \1B[0m\1B[0m    x: posX[0],\0A\1B[0m\1B[33m31| \1B[0m\1B[31m\1B[1m    y: posY[0]\0A\1B[0m\1B[32m\1B[1m             \0A   ~~~~~~~~~~~~^\1B[0m\0A\1B[33m32| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m33| \1B[0m\1B[0m  const fgAnim: FlowWingAnim = new FlowWingAnim(screenWidth, screenHeight, \22snake-game-in-flowwing\22, 60)\0A\1B[0m\1B[33m34| \1B[0m\1B[0m  var bird:Texture = LoadTexture(\22/Users/apple/Downloads/images.png\22)\0A\1B[0m\1B[33m35| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 31:13\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@6 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@7 = private unnamed_addr constant [34 x i8] c"/Users/apple/Downloads/images.png\00", align 1
@8 = private unnamed_addr constant [643 x i8] c"\0A\1B[33m77| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m78| \1B[0m\1B[0m\0A\1B[0m\1B[33m79| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m80| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m81| \1B[0m\1B[31m\1B[1m        posX[index]= posX[index - 1]\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m82| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m85| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 81:14\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [685 x i8] c"\0A\1B[33m77| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m78| \1B[0m\1B[0m\0A\1B[0m\1B[33m79| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m80| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m81| \1B[0m\1B[31m\1B[1m        posX[index]= posX[index - 1]\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m82| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m85| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 81:35\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [659 x i8] c"\0A\1B[33m78| \1B[0m\1B[0m\0A\1B[0m\1B[33m79| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m80| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m81| \1B[0m\1B[0m        posX[index]= posX[index - 1]\0A\1B[0m\1B[33m82| \1B[0m\1B[31m\1B[1m        posY[index]= posY[index - 1]\0A\1B[0m\1B[32m\1B[1m              \0A   ~~~~~~~~~~~~~^\1B[0m\0A\1B[33m83| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m85| \1B[0m\1B[0m\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 82:14\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [701 x i8] c"\0A\1B[33m78| \1B[0m\1B[0m\0A\1B[0m\1B[33m79| \1B[0m\1B[0m    if (isKeyPressed) {\0A\1B[0m\1B[33m80| \1B[0m\1B[0m      for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m81| \1B[0m\1B[0m        posX[index]= posX[index - 1]\0A\1B[0m\1B[33m82| \1B[0m\1B[31m\1B[1m        posY[index]= posY[index - 1]\0A\1B[0m\1B[32m\1B[1m                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m83| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m85| \1B[0m\1B[0m\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 82:35\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [678 x i8] c"\0A\1B[33m82| \1B[0m\1B[0m        posY[index]= posY[index - 1]\0A\1B[0m\1B[33m83| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m85| \1B[0m\1B[0m\0A\1B[0m\1B[33m86| \1B[0m\1B[31m\1B[1m    posX[0]= newPos.x\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m87| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 86:10\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [726 x i8] c"\0A\1B[33m83| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m85| \1B[0m\1B[0m\0A\1B[0m\1B[33m86| \1B[0m\1B[0m    posX[0]= newPos.x\0A\1B[0m\1B[33m87| \1B[0m\1B[31m\1B[1m    posY[0]= newPos.y\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m88| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m91| \1B[0m\1B[0m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 87:10\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [921 x i8] c"\0A\1B[33m87| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m91| \1B[0m\1B[31m\1B[1m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[32m\1B[1m                                 \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m92| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m93| \1B[0m\1B[0m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[33m94| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m95| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 91:33\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@15 = private unnamed_addr constant [947 x i8] c"\0A\1B[33m87| \1B[0m\1B[0m    posY[0]= newPos.y\0A\1B[0m\1B[33m88| \1B[0m\1B[0m    fgAnim.beginDrawing()\0A\1B[0m\1B[33m89| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m91| \1B[0m\1B[31m\1B[1m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m92| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m93| \1B[0m\1B[0m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[33m94| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m95| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 91:46\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@16 = private unnamed_addr constant [849 x i8] c"\0A\1B[33m89| \1B[0m\1B[0m    fgAnim.clearBackground(fgAnim.colors.WHITE)\0A\1B[0m\1B[33m90| \1B[0m\1B[0m    for var index: int = 0 to tail - 1 {\0A\1B[0m\1B[33m91| \1B[0m\1B[0m      fgAnim.drawRectangle(posX[index], posY[index], side, side, fgAnim.colors.BLUE)\0A\1B[0m\1B[33m92| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m93| \1B[0m\1B[31m\1B[1m    fgAnim.drawCircle(screenWidth // 5, 120, 35.0d, fgAnim.colors.DARKBLUE)\0A\1B[0m\1B[32m\1B[1m                                      \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m94| \1B[0m\1B[0m    fgAnim.drawRectangle(foodPos.x, foodPos.y, side, side, fgAnim.colors.GREEN)\0A\1B[0m\1B[33m95| \1B[0m\1B[0m    fgAnim.endDrawing()\0A\1B[0m\1B[33m96| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m97| \1B[0m\1B[0m  fgAnim.closeWindow()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 93:38\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1

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

declare !rt !15 void @FlowWingAnim.drawTexture(ptr, ptr, ptr, ptr, ptr)

declare !rt !16 void @FlowWingAnim.loadTexture(ptr, ptr, ptr)

declare !rt !17 i1 @FlowWingAnim.isKeyPressed(ptr, ptr)

declare !rt !18 i1 @FlowWingAnim.isKeyDown(ptr, ptr)

declare !rt !19 ptr @FlowWingAnim.textFormat(ptr, ptr)

declare !rt !17 i1 @FlowWingAnim.isKeyPressed.1(ptr)

declare !rt !16 void @FlowWingAnim.loadTexture.2(ptr, ptr)

declare !rt !14 void @FlowWingAnim.drawText.3(ptr, ptr, ptr, ptr, ptr)

declare !rt !13 void @FlowWingAnim.drawCircle.4(ptr, ptr, ptr, ptr)

declare !rt !18 i1 @FlowWingAnim.isKeyDown.5(ptr)

declare !rt !12 i32 @FlowWingAnim.getScreenWidth.6()

declare !rt !11 i32 @FlowWingAnim.getScreenHeight.7()

declare !rt !19 ptr @FlowWingAnim.textFormat.8(ptr)

declare !rt !10 void @FlowWingAnim.closeWindow.9()

declare !rt !9 void @FlowWingAnim.endDrawing.10()

declare !rt !7 void @FlowWingAnim.beginDrawing.11()

declare !rt !5 void @FlowWingAnim.clearBackground.12(ptr)

declare !rt !4 void @FlowWingAnim.createWindow.13()

declare !rt !3 i32 @FlowWingAnim.getColor.14(ptr, ptr, ptr, ptr)

declare !rt !2 void @FlowWingAnim.setTargetFPS.15()

declare !rt !20 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !21 void @SetTargetFPS(i32)

declare !rt !22 void @EndDrawing()

declare !rt !23 void @InitWindow(i32, i32, ptr)

declare !rt !24 void @ClearBackground(i32)

declare !rt !25 i32 @GetScreenWidth()

declare !rt !26 void @DrawCircle(i32, i32, float, i32)

declare !rt !6 i1 @FlowWingAnim.windowShouldClose.16()

declare !rt !27 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !28 i1 @WindowShouldClose()

declare !rt !29 void @LoadTexture(ptr, ptr)

declare !rt !30 ptr @TextFormat(ptr)

declare !rt !31 i32 @time()

declare !rt !32 void @BeginDrawing()

declare !rt !33 i1 @IsKeyPressed(i32)

declare !rt !1 void @FlowWingAnim.beforeInit.17()

declare !rt !34 void @CloseWindow()

declare !rt !8 void @FlowWingAnim.drawRectangle.18(ptr, ptr, ptr, ptr, ptr)

declare !rt !35 i32 @getRandomNumber(ptr, ptr)

declare !rt !36 i1 @IsKeyDown(i32)

declare !rt !0 void @FlowWingAnim.init4.19(ptr, ptr, ptr, ptr)

declare !rt !15 void @FlowWingAnim.drawTexture.20(ptr, ptr, ptr, ptr)

declare !rt !37 i32 @GetScreenHeight()

declare !rt !38 void @DrawTexture(%Texture.0, i32, i32, i32)

declare !rt !39 i32 @rand()

declare !rt !40 void @srand(i32)

define void @getFoodPosition(ptr %0) !rt !41 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %mergeBlock, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %pos = alloca %Position.3, align 8
  %1 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 0
  %4 = alloca i32, align 4
  store i32 0, ptr %4, align 4
  %screenWidth = load i32, ptr @screenWidth, align 4
  %5 = sub i32 %screenWidth, 1
  %6 = alloca i32, align 4
  store i32 %5, ptr %6, align 4
  %7 = call i32 @getRandomNumber(ptr %4, ptr %6)
  store i32 %7, ptr %3, align 4
  %8 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 1
  %9 = alloca i32, align 4
  store i32 0, ptr %9, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %10 = sub i32 %screenHeight, 1
  %11 = alloca i32, align 4
  store i32 %10, ptr %11, align 4
  %12 = call i32 @getRandomNumber(ptr %9, ptr %11)
  store i32 %12, ptr %8, align 4
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %17 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 0
  %x = load i32, ptr %17, align 4
  %18 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 0
  %x7 = load i32, ptr %18, align 4
  %19 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 0
  %x8 = load i32, ptr %19, align 4
  %side = load i32, ptr @side, align 4
  %20 = srem i32 %x8, %side
  %21 = sub i32 %x7, %20
  store i32 %21, ptr %17, align 4
  %22 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %24 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %26 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 1
  %y = load i32, ptr %26, align 4
  %27 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 1
  %y9 = load i32, ptr %27, align 4
  %28 = getelementptr inbounds %Position.3, ptr %pos, i32 0, i32 1
  %y10 = load i32, ptr %28, align 4
  %side11 = load i32, ptr @side, align 4
  %29 = srem i32 %y10, %side11
  %30 = sub i32 %y9, %29
  store i32 %30, ptr %26, align 4
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %33 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  br label %returnBlock

checkContinueBlock6:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock5
  %35 = load %Position.3, ptr %pos, align 4
  store %Position.3 %35, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %36 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %checkContinueBlock6, label %afterNestedBlock
}

define i32 @main() !rt !42 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock26, %mergeBlock, %checkContinueBlock24, %nestedBlock23, %checkContinueBlock22, %end_block265, %checkContinueBlock20, %nestedBlock19, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %"GlobalIndexExpr::merge54", %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %"GlobalIndexExpr::merge46", %checkContinueBlock8, %"GlobalIndexExpr::merge", %checkContinueBlock6, %FillExpr.exit41, %checkContinueBlock4, %FillExpr.exit31, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
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

checkContinueBlock4:                              ; preds = %FillExpr.exit31
  %11 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %posY = alloca [10000 x i32], align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store i32 0, ptr %14, align 4
  br label %FillExpr.loopStart-032

checkContinueBlock6:                              ; preds = %FillExpr.exit41
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %posX42 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock8:                              ; preds = %"GlobalIndexExpr::merge"
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %posY43 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then44", label %"GlobalIndexExpr::else45"

checkContinueBlock10:                             ; preds = %"GlobalIndexExpr::merge46"
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %foodPos = alloca %Position.3, align 8
  %21 = getelementptr inbounds %Position.3, ptr %foodPos, i32 0, i32 0
  store i32 0, ptr %21, align 4
  %22 = getelementptr inbounds %Position.3, ptr %foodPos, i32 0, i32 1
  store i32 0, ptr %22, align 4
  call void @getFoodPosition(ptr %foodPos)
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %newPos = alloca %Position.3, align 8
  %27 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  store i32 0, ptr %27, align 4
  %28 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  store i32 0, ptr %28, align 4
  %29 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %posX47 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then48", label %"GlobalIndexExpr::else49"

checkContinueBlock14:                             ; preds = %"GlobalIndexExpr::merge54"
  %30 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %32 = call ptr @malloc(i64 64)
  %33 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  store ptr @4, ptr %33, align 8
  %34 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 1
  store i32 0, ptr %34, align 4
  %35 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 2
  store i32 0, ptr %35, align 4
  %36 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 3
  store ptr @5, ptr %36, align 8
  %37 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 4
  store i32 0, ptr %37, align 4
  %38 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 5
  %39 = getelementptr inbounds %COLORS_TYPE.2, ptr %38, i32 0, i32 0
  store i32 0, ptr %39, align 4
  %40 = getelementptr inbounds %COLORS_TYPE.2, ptr %38, i32 0, i32 1
  store i32 0, ptr %40, align 4
  %41 = getelementptr inbounds %COLORS_TYPE.2, ptr %38, i32 0, i32 2
  store i32 0, ptr %41, align 4
  %42 = getelementptr inbounds %COLORS_TYPE.2, ptr %38, i32 0, i32 3
  store i32 0, ptr %42, align 4
  %43 = getelementptr inbounds %COLORS_TYPE.2, ptr %38, i32 0, i32 4
  store i32 0, ptr %43, align 4
  %44 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %45 = getelementptr inbounds %KEYS_TYPE.1, ptr %44, i32 0, i32 0
  store i32 0, ptr %45, align 4
  %46 = getelementptr inbounds %KEYS_TYPE.1, ptr %44, i32 0, i32 1
  store i32 0, ptr %46, align 4
  %47 = getelementptr inbounds %KEYS_TYPE.1, ptr %44, i32 0, i32 2
  store i32 0, ptr %47, align 4
  %48 = getelementptr inbounds %KEYS_TYPE.1, ptr %44, i32 0, i32 3
  store i32 0, ptr %48, align 4
  %49 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  store ptr @vtable.FlowWingAnim.fg, ptr %49, align 8
  %50 = load ptr, ptr %49, align 8
  %51 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 17
  store ptr @FlowWingAnim.endDrawing, ptr %51, align 8
  %52 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 18
  store ptr @FlowWingAnim.setTargetFPS, ptr %52, align 8
  %53 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 16
  store ptr @FlowWingAnim.createWindow, ptr %53, align 8
  %54 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 15
  store ptr @FlowWingAnim.clearBackground, ptr %54, align 8
  %55 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 14
  store ptr @FlowWingAnim.beforeInit, ptr %55, align 8
  %56 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 13
  store ptr @FlowWingAnim.textFormat, ptr %56, align 8
  %57 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 12
  store ptr @FlowWingAnim.windowShouldClose, ptr %57, align 8
  %58 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 10
  store ptr @FlowWingAnim.drawRectangle, ptr %58, align 8
  %59 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 9
  store ptr @FlowWingAnim.beginDrawing, ptr %59, align 8
  %60 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 8
  store ptr @FlowWingAnim.closeWindow, ptr %60, align 8
  %61 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 7
  store ptr @FlowWingAnim.getScreenHeight, ptr %61, align 8
  %62 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 6
  store ptr @FlowWingAnim.getScreenWidth, ptr %62, align 8
  %63 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 4
  store ptr @FlowWingAnim.isKeyDown, ptr %63, align 8
  %64 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 5
  store ptr @FlowWingAnim.drawCircle, ptr %64, align 8
  %65 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 3
  store ptr @FlowWingAnim.drawText, ptr %65, align 8
  %66 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 2
  store ptr @FlowWingAnim.drawTexture, ptr %66, align 8
  %67 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 11
  store ptr @FlowWingAnim.getColor, ptr %67, align 8
  %68 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 1
  store ptr @FlowWingAnim.loadTexture, ptr %68, align 8
  %69 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %50, i32 0, i32 0
  store ptr @FlowWingAnim.isKeyPressed, ptr %69, align 8
  %screenWidth = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %70 = alloca ptr, align 8
  store ptr @6, ptr %70, align 8
  %71 = alloca i32, align 4
  store i32 60, ptr %71, align 4
  call void @FlowWingAnim.init4(ptr @screenWidth, ptr @screenHeight, ptr %70, ptr %71, ptr %32)
  %72 = load %FlowWingAnim, ptr %32, align 8
  store %FlowWingAnim %72, ptr %32, align 8
  %73 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %74 = icmp eq i32 %73, 0
  br i1 %74, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %75 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %bird = alloca %Texture.0, align 8
  %77 = getelementptr inbounds %Texture.0, ptr %bird, i32 0, i32 0
  store i32 0, ptr %77, align 4
  %78 = getelementptr inbounds %Texture.0, ptr %bird, i32 0, i32 1
  store i32 0, ptr %78, align 4
  %79 = getelementptr inbounds %Texture.0, ptr %bird, i32 0, i32 2
  store i32 0, ptr %79, align 4
  %80 = getelementptr inbounds %Texture.0, ptr %bird, i32 0, i32 3
  store i32 0, ptr %80, align 4
  %81 = getelementptr inbounds %Texture.0, ptr %bird, i32 0, i32 4
  store i32 0, ptr %81, align 4
  call void @LoadTexture(ptr %bird, ptr @7)
  %82 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %83 = icmp eq i32 %82, 0
  br i1 %83, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %84 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %85 = icmp eq i32 %84, 0
  br i1 %85, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %86 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %87 = load ptr, ptr %86, align 8
  %88 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %87, i32 0, i32 16
  %89 = load ptr, ptr %88, align 8
  call void %89(ptr %32)
  %90 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %91 = icmp eq i32 %90, 0
  br i1 %91, label %checkContinueBlock20, label %afterNestedBlock

checkContinueBlock20:                             ; preds = %nestedBlock19
  %92 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %93 = icmp eq i32 %92, 0
  br i1 %93, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  br label %"while:conditon"

checkContinueBlock22:                             ; preds = %end_block265
  %94 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  %96 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %97 = load ptr, ptr %96, align 8
  %98 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %97, i32 0, i32 8
  %99 = load ptr, ptr %98, align 8
  call void %99(ptr %32)
  %100 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %checkContinueBlock24, label %afterNestedBlock

checkContinueBlock24:                             ; preds = %nestedBlock23
  %102 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %103 = icmp eq i32 %102, 0
  br i1 %103, label %nestedBlock25, label %afterNestedBlock

nestedBlock25:                                    ; preds = %checkContinueBlock24
  br label %returnBlock

checkContinueBlock26:                             ; preds = %mergeBlock
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock3
  store i32 0, ptr %9, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %104 = load i32, ptr %9, align 4
  %105 = icmp slt i32 %104, 10000
  %106 = load i32, ptr %10, align 4
  %107 = icmp slt i32 %106, 10000
  %108 = and i1 %105, %107
  br i1 %108, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %109 = load i32, ptr %9, align 4
  %110 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %109
  store i32 0, ptr %110, align 4
  %111 = load i32, ptr %9, align 4
  %112 = add i32 %111, 1
  store i32 %112, ptr %9, align 4
  %113 = load i32, ptr %10, align 4
  %114 = add i32 %113, 1
  store i32 %114, ptr %10, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %115 = alloca i32, align 4
  %116 = alloca i32, align 4
  store i32 0, ptr %116, align 4
  br label %FillExpr.loopStart-027

FillExpr.loopStart-027:                           ; preds = %FillExpr.exit
  store i32 0, ptr %115, align 4
  br label %FillExpr.loopCmp-028

FillExpr.loopCmp-028:                             ; preds = %FillExpr.loopBody-029, %FillExpr.loopStart-027
  %117 = load i32, ptr %115, align 4
  %118 = icmp slt i32 %117, 10000
  %119 = load i32, ptr %116, align 4
  %120 = icmp slt i32 %119, 10000
  %121 = and i1 %118, %120
  br i1 %121, label %FillExpr.loopBody-029, label %FillExpr.loopEnd-030

FillExpr.loopBody-029:                            ; preds = %FillExpr.loopCmp-028
  %122 = load i32, ptr %115, align 4
  %123 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %122
  store i32 -1, ptr %123, align 4
  %124 = load i32, ptr %115, align 4
  %125 = add i32 %124, 1
  store i32 %125, ptr %115, align 4
  %126 = load i32, ptr %116, align 4
  %127 = add i32 %126, 1
  store i32 %127, ptr %116, align 4
  br label %FillExpr.loopCmp-028

FillExpr.loopEnd-030:                             ; preds = %FillExpr.loopCmp-028
  br label %FillExpr.exit31

FillExpr.exit31:                                  ; preds = %FillExpr.loopEnd-030
  %128 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %129 = icmp eq i32 %128, 0
  br i1 %129, label %checkContinueBlock4, label %afterNestedBlock

FillExpr.loopStart-032:                           ; preds = %nestedBlock5
  store i32 0, ptr %13, align 4
  br label %FillExpr.loopCmp-033

FillExpr.loopCmp-033:                             ; preds = %FillExpr.loopBody-034, %FillExpr.loopStart-032
  %130 = load i32, ptr %13, align 4
  %131 = icmp slt i32 %130, 10000
  %132 = load i32, ptr %14, align 4
  %133 = icmp slt i32 %132, 10000
  %134 = and i1 %131, %133
  br i1 %134, label %FillExpr.loopBody-034, label %FillExpr.loopEnd-035

FillExpr.loopBody-034:                            ; preds = %FillExpr.loopCmp-033
  %135 = load i32, ptr %13, align 4
  %136 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %135
  store i32 0, ptr %136, align 4
  %137 = load i32, ptr %13, align 4
  %138 = add i32 %137, 1
  store i32 %138, ptr %13, align 4
  %139 = load i32, ptr %14, align 4
  %140 = add i32 %139, 1
  store i32 %140, ptr %14, align 4
  br label %FillExpr.loopCmp-033

FillExpr.loopEnd-035:                             ; preds = %FillExpr.loopCmp-033
  br label %FillExpr.exit36

FillExpr.exit36:                                  ; preds = %FillExpr.loopEnd-035
  %141 = alloca i32, align 4
  %142 = alloca i32, align 4
  store i32 0, ptr %142, align 4
  br label %FillExpr.loopStart-037

FillExpr.loopStart-037:                           ; preds = %FillExpr.exit36
  store i32 0, ptr %141, align 4
  br label %FillExpr.loopCmp-038

FillExpr.loopCmp-038:                             ; preds = %FillExpr.loopBody-039, %FillExpr.loopStart-037
  %143 = load i32, ptr %141, align 4
  %144 = icmp slt i32 %143, 10000
  %145 = load i32, ptr %142, align 4
  %146 = icmp slt i32 %145, 10000
  %147 = and i1 %144, %146
  br i1 %147, label %FillExpr.loopBody-039, label %FillExpr.loopEnd-040

FillExpr.loopBody-039:                            ; preds = %FillExpr.loopCmp-038
  %148 = load i32, ptr %141, align 4
  %149 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %148
  store i32 -1, ptr %149, align 4
  %150 = load i32, ptr %141, align 4
  %151 = add i32 %150, 1
  store i32 %151, ptr %141, align 4
  %152 = load i32, ptr %142, align 4
  %153 = add i32 %152, 1
  store i32 %153, ptr %142, align 4
  br label %FillExpr.loopCmp-038

FillExpr.loopEnd-040:                             ; preds = %FillExpr.loopCmp-038
  br label %FillExpr.exit41

FillExpr.exit41:                                  ; preds = %FillExpr.loopEnd-040
  %154 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %155 = icmp eq i32 %154, 0
  br i1 %155, label %checkContinueBlock6, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %nestedBlock7
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock7
  call void @raise_exception(ptr @0)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %156 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %157 = load i32, ptr %156, align 4
  store i32 0, ptr %156, align 4
  %158 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %159 = icmp eq i32 %158, 0
  br i1 %159, label %checkContinueBlock8, label %afterNestedBlock

"GlobalIndexExpr::then44":                        ; preds = %nestedBlock9
  br label %"GlobalIndexExpr::merge46"

"GlobalIndexExpr::else45":                        ; preds = %nestedBlock9
  call void @raise_exception(ptr @1)
  br label %"GlobalIndexExpr::merge46"

"GlobalIndexExpr::merge46":                       ; preds = %"GlobalIndexExpr::else45", %"GlobalIndexExpr::then44"
  %160 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %161 = load i32, ptr %160, align 4
  store i32 0, ptr %160, align 4
  %162 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %163 = icmp eq i32 %162, 0
  br i1 %163, label %checkContinueBlock10, label %afterNestedBlock

"GlobalIndexExpr::then48":                        ; preds = %nestedBlock13
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::else49":                        ; preds = %nestedBlock13
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge50"

"GlobalIndexExpr::merge50":                       ; preds = %"GlobalIndexExpr::else49", %"GlobalIndexExpr::then48"
  %164 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %165 = load i32, ptr %164, align 4
  %166 = load i32, ptr %164, align 4
  store i32 %166, ptr %29, align 4
  %167 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %posY51 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then52", label %"GlobalIndexExpr::else53"

"GlobalIndexExpr::then52":                        ; preds = %"GlobalIndexExpr::merge50"
  br label %"GlobalIndexExpr::merge54"

"GlobalIndexExpr::else53":                        ; preds = %"GlobalIndexExpr::merge50"
  call void @raise_exception(ptr @3)
  br label %"GlobalIndexExpr::merge54"

"GlobalIndexExpr::merge54":                       ; preds = %"GlobalIndexExpr::else53", %"GlobalIndexExpr::then52"
  %168 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %169 = load i32, ptr %168, align 4
  %170 = load i32, ptr %168, align 4
  store i32 %170, ptr %167, align 4
  %171 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %172 = icmp eq i32 %171, 0
  br i1 %172, label %checkContinueBlock14, label %afterNestedBlock

"while:conditon":                                 ; preds = %afterNestedBlock55, %nestedBlock21
  %173 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %174 = icmp eq i32 %173, 0
  br i1 %174, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock56

while.end:                                        ; preds = %afterNestedBlock55, %end_block
  %175 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %176 = icmp eq i32 %175, 0
  br i1 %176, label %end_block265, label %decrement_block264

decrement_block:                                  ; preds = %"while:conditon"
  %177 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %178 = sub i32 %177, 1
  store i32 %178, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %179 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %180 = load ptr, ptr %179, align 8
  %181 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %180, i32 0, i32 12
  %182 = load ptr, ptr %181, align 8
  %183 = call i1 %182(ptr %32)
  %184 = xor i1 %183, true
  br i1 %184, label %"while:body", label %while.end

afterNestedBlock55:                               ; preds = %checkContinueBlock87, %nestedBlock86, %checkContinueBlock85, %nestedBlock84, %checkContinueBlock83, %merge, %checkContinueBlock81, %end_block257, %checkContinueBlock79, %nestedBlock78, %checkContinueBlock77, %nestedBlock76, %checkContinueBlock75, %"GlobalIndexExpr::merge222", %checkContinueBlock73, %"GlobalIndexExpr::merge217", %checkContinueBlock71, %afterIfElse170, %checkContinueBlock69, %afterIfElse160, %checkContinueBlock67, %afterIfElse148, %checkContinueBlock65, %afterIfElse139, %checkContinueBlock63, %afterIfElse130, %checkContinueBlock61, %afterIfElse121, %checkContinueBlock59, %afterIfElse, %checkContinueBlock57, %nestedBlock56
  %185 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %"while:conditon", label %while.end

nestedBlock56:                                    ; preds = %"while:body"
  %isKeyPressed = alloca %DynamicType, align 8
  %187 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 false, ptr %187, align 1
  %188 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %189 = icmp eq i32 %188, 0
  br i1 %189, label %checkContinueBlock57, label %afterNestedBlock55

checkContinueBlock57:                             ; preds = %nestedBlock56
  %190 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %191 = icmp eq i32 %190, 0
  br i1 %191, label %nestedBlock58, label %afterNestedBlock55

nestedBlock58:                                    ; preds = %checkContinueBlock57
  %192 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %193 = load ptr, ptr %192, align 8
  %194 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %193, i32 0, i32 0
  %195 = load ptr, ptr %194, align 8
  %196 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %197 = getelementptr inbounds %KEYS_TYPE.1, ptr %196, i32 0, i32 3
  %KEY_UP = load i32, ptr %197, align 4
  %198 = call i1 %195(ptr %197, ptr %32)
  %199 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %200 = load ptr, ptr %199, align 8
  %201 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %200, i32 0, i32 4
  %202 = load ptr, ptr %201, align 8
  %203 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %204 = getelementptr inbounds %KEYS_TYPE.1, ptr %203, i32 0, i32 3
  %KEY_UP88 = load i32, ptr %204, align 4
  %205 = call i1 %202(ptr %204, ptr %32)
  %206 = select i1 %198, i1 true, i1 %205
  br i1 %206, label %then, label %orIf0

checkContinueBlock59:                             ; preds = %afterIfElse
  %207 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %208 = icmp eq i32 %207, 0
  br i1 %208, label %nestedBlock60, label %afterNestedBlock55

nestedBlock60:                                    ; preds = %checkContinueBlock59
  %209 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x118 = load i32, ptr %209, align 4
  %210 = icmp slt i32 %x118, 0
  br i1 %210, label %then119, label %else120

checkContinueBlock61:                             ; preds = %afterIfElse121
  %211 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %212 = icmp eq i32 %211, 0
  br i1 %212, label %nestedBlock62, label %afterNestedBlock55

nestedBlock62:                                    ; preds = %checkContinueBlock61
  %213 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x126 = load i32, ptr %213, align 4
  %screenWidth127 = load i32, ptr @screenWidth, align 4
  %214 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %215 = load i32, ptr %214, align 4
  %216 = sub i32 %screenWidth127, %215
  %217 = icmp sge i32 %x126, %216
  br i1 %217, label %then128, label %else129

checkContinueBlock63:                             ; preds = %afterIfElse130
  %218 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %219 = icmp eq i32 %218, 0
  br i1 %219, label %nestedBlock64, label %afterNestedBlock55

nestedBlock64:                                    ; preds = %checkContinueBlock63
  %220 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y136 = load i32, ptr %220, align 4
  %221 = icmp slt i32 %y136, 0
  br i1 %221, label %then137, label %else138

checkContinueBlock65:                             ; preds = %afterIfElse139
  %222 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %223 = icmp eq i32 %222, 0
  br i1 %223, label %nestedBlock66, label %afterNestedBlock55

nestedBlock66:                                    ; preds = %checkContinueBlock65
  %224 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y144 = load i32, ptr %224, align 4
  %screenHeight145 = load i32, ptr @screenHeight, align 4
  %225 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %226 = load i32, ptr %225, align 4
  %227 = sub i32 %screenHeight145, %226
  %228 = icmp sge i32 %y144, %227
  br i1 %228, label %then146, label %else147

checkContinueBlock67:                             ; preds = %afterIfElse148
  %229 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %230 = icmp eq i32 %229, 0
  br i1 %230, label %nestedBlock68, label %afterNestedBlock55

nestedBlock68:                                    ; preds = %checkContinueBlock67
  %231 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x154 = load i32, ptr %231, align 4
  %232 = getelementptr inbounds %Position.3, ptr %foodPos, i32 0, i32 0
  %x155 = load i32, ptr %232, align 4
  %233 = icmp eq i32 %x154, %x155
  %234 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y156 = load i32, ptr %234, align 4
  %235 = getelementptr inbounds %Position.3, ptr %foodPos, i32 0, i32 1
  %y157 = load i32, ptr %235, align 4
  %236 = icmp eq i32 %y156, %y157
  %237 = select i1 %233, i1 %236, i1 false
  br i1 %237, label %then158, label %else159

checkContinueBlock69:                             ; preds = %afterIfElse160
  %238 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %239 = icmp eq i32 %238, 0
  br i1 %239, label %nestedBlock70, label %afterNestedBlock55

nestedBlock70:                                    ; preds = %checkContinueBlock69
  %240 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %241 = load i1, ptr %240, align 1
  br i1 %241, label %then168, label %else169

checkContinueBlock71:                             ; preds = %afterIfElse170
  %242 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %243 = icmp eq i32 %242, 0
  br i1 %243, label %nestedBlock72, label %afterNestedBlock55

nestedBlock72:                                    ; preds = %checkContinueBlock71
  %posX214 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then215", label %"GlobalIndexExpr::else216"

checkContinueBlock73:                             ; preds = %"GlobalIndexExpr::merge217"
  %244 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %245 = icmp eq i32 %244, 0
  br i1 %245, label %nestedBlock74, label %afterNestedBlock55

nestedBlock74:                                    ; preds = %checkContinueBlock73
  %posY219 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then220", label %"GlobalIndexExpr::else221"

checkContinueBlock75:                             ; preds = %"GlobalIndexExpr::merge222"
  %246 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %247 = icmp eq i32 %246, 0
  br i1 %247, label %nestedBlock76, label %afterNestedBlock55

nestedBlock76:                                    ; preds = %checkContinueBlock75
  %248 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %249 = load ptr, ptr %248, align 8
  %250 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %249, i32 0, i32 9
  %251 = load ptr, ptr %250, align 8
  call void %251(ptr %32)
  %252 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %253 = icmp eq i32 %252, 0
  br i1 %253, label %checkContinueBlock77, label %afterNestedBlock55

checkContinueBlock77:                             ; preds = %nestedBlock76
  %254 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %255 = icmp eq i32 %254, 0
  br i1 %255, label %nestedBlock78, label %afterNestedBlock55

nestedBlock78:                                    ; preds = %checkContinueBlock77
  %256 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %257 = load ptr, ptr %256, align 8
  %258 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %257, i32 0, i32 15
  %259 = load ptr, ptr %258, align 8
  %260 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 5
  %261 = getelementptr inbounds %COLORS_TYPE.2, ptr %260, i32 0, i32 0
  %WHITE = load i32, ptr %261, align 4
  call void %259(ptr %261, ptr %32)
  %262 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %263 = icmp eq i32 %262, 0
  br i1 %263, label %checkContinueBlock79, label %afterNestedBlock55

checkContinueBlock79:                             ; preds = %nestedBlock78
  %264 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %265 = icmp eq i32 %264, 0
  br i1 %265, label %nestedBlock80, label %afterNestedBlock55

nestedBlock80:                                    ; preds = %checkContinueBlock79
  %tail224 = load i32, ptr %tail, align 4
  %266 = sub i32 %tail224, 1
  %index225 = alloca i32, align 4
  store i32 0, ptr %index225, align 4
  store i32 0, ptr %index225, align 4
  br label %"ForLoop::loopCondition226"

checkContinueBlock81:                             ; preds = %end_block257
  %267 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %268 = icmp eq i32 %267, 0
  br i1 %268, label %nestedBlock82, label %afterNestedBlock55

nestedBlock82:                                    ; preds = %checkContinueBlock81
  %269 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %270 = load ptr, ptr %269, align 8
  %271 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %270, i32 0, i32 5
  %272 = load ptr, ptr %271, align 8
  %screenWidth258 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if, label %else259

checkContinueBlock83:                             ; preds = %merge
  %273 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %274 = icmp eq i32 %273, 0
  br i1 %274, label %nestedBlock84, label %afterNestedBlock55

nestedBlock84:                                    ; preds = %checkContinueBlock83
  %275 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %276 = load ptr, ptr %275, align 8
  %277 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %276, i32 0, i32 10
  %278 = load ptr, ptr %277, align 8
  %279 = getelementptr inbounds %Position.3, ptr %foodPos, i32 0, i32 0
  %x260 = load i32, ptr %279, align 4
  %280 = getelementptr inbounds %Position.3, ptr %foodPos, i32 0, i32 1
  %y261 = load i32, ptr %280, align 4
  %side262 = load i32, ptr @side, align 4
  %side263 = load i32, ptr @side, align 4
  %281 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 5
  %282 = getelementptr inbounds %COLORS_TYPE.2, ptr %281, i32 0, i32 2
  %GREEN = load i32, ptr %282, align 4
  call void %278(ptr %279, ptr %280, ptr @side, ptr @side, ptr %282, ptr %32)
  %283 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %284 = icmp eq i32 %283, 0
  br i1 %284, label %checkContinueBlock85, label %afterNestedBlock55

checkContinueBlock85:                             ; preds = %nestedBlock84
  %285 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %286 = icmp eq i32 %285, 0
  br i1 %286, label %nestedBlock86, label %afterNestedBlock55

nestedBlock86:                                    ; preds = %checkContinueBlock85
  %287 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %288 = load ptr, ptr %287, align 8
  %289 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %288, i32 0, i32 17
  %290 = load ptr, ptr %289, align 8
  call void %290(ptr %32)
  %291 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %292 = icmp eq i32 %291, 0
  br i1 %292, label %checkContinueBlock87, label %afterNestedBlock55

checkContinueBlock87:                             ; preds = %nestedBlock86
  br label %afterNestedBlock55

then:                                             ; preds = %nestedBlock58
  br label %nestedBlock93

orIf0:                                            ; preds = %nestedBlock58
  %293 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %294 = load ptr, ptr %293, align 8
  %295 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %294, i32 0, i32 0
  %296 = load ptr, ptr %295, align 8
  %297 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %298 = getelementptr inbounds %KEYS_TYPE.1, ptr %297, i32 0, i32 2
  %KEY_DOWN = load i32, ptr %298, align 4
  %299 = call i1 %296(ptr %298, ptr %32)
  %300 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %301 = load ptr, ptr %300, align 8
  %302 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %301, i32 0, i32 4
  %303 = load ptr, ptr %302, align 8
  %304 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %305 = getelementptr inbounds %KEYS_TYPE.1, ptr %304, i32 0, i32 2
  %KEY_DOWN89 = load i32, ptr %305, align 4
  %306 = call i1 %303(ptr %305, ptr %32)
  %307 = select i1 %299, i1 true, i1 %306
  br i1 %307, label %orIfThen0, label %orIf1

orIf1:                                            ; preds = %orIf0
  %308 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %309 = load ptr, ptr %308, align 8
  %310 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %309, i32 0, i32 0
  %311 = load ptr, ptr %310, align 8
  %312 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %313 = getelementptr inbounds %KEYS_TYPE.1, ptr %312, i32 0, i32 0
  %KEY_RIGHT = load i32, ptr %313, align 4
  %314 = call i1 %311(ptr %313, ptr %32)
  %315 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %316 = load ptr, ptr %315, align 8
  %317 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %316, i32 0, i32 4
  %318 = load ptr, ptr %317, align 8
  %319 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %320 = getelementptr inbounds %KEYS_TYPE.1, ptr %319, i32 0, i32 0
  %KEY_RIGHT90 = load i32, ptr %320, align 4
  %321 = call i1 %318(ptr %320, ptr %32)
  %322 = select i1 %314, i1 true, i1 %321
  br i1 %322, label %orIfThen1, label %orIf2

orIf2:                                            ; preds = %orIf1
  %323 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %324 = load ptr, ptr %323, align 8
  %325 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %324, i32 0, i32 0
  %326 = load ptr, ptr %325, align 8
  %327 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %328 = getelementptr inbounds %KEYS_TYPE.1, ptr %327, i32 0, i32 1
  %KEY_LEFT = load i32, ptr %328, align 4
  %329 = call i1 %326(ptr %328, ptr %32)
  %330 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %331 = load ptr, ptr %330, align 8
  %332 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %331, i32 0, i32 4
  %333 = load ptr, ptr %332, align 8
  %334 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 6
  %335 = getelementptr inbounds %KEYS_TYPE.1, ptr %334, i32 0, i32 1
  %KEY_LEFT91 = load i32, ptr %335, align 4
  %336 = call i1 %333(ptr %335, ptr %32)
  %337 = select i1 %329, i1 true, i1 %336
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
  %347 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y = load i32, ptr %347, align 4
  %348 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y97 = load i32, ptr %348, align 4
  %349 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %350 = load i32, ptr %349, align 4
  %351 = sub i32 %y97, %350
  store i32 %351, ptr %347, align 4
  %352 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %353 = icmp eq i32 %352, 0
  br i1 %353, label %checkContinueBlock96, label %afterNestedBlock92

checkContinueBlock96:                             ; preds = %nestedBlock95
  br label %afterNestedBlock92

afterNestedBlock98:                               ; preds = %checkContinueBlock102, %nestedBlock101, %checkContinueBlock100, %nestedBlock99
  br label %afterIfElse

nestedBlock99:                                    ; preds = %orIfThen0
  %354 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %355 = load i1, ptr %354, align 1
  %356 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %356, align 1
  %357 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %358 = icmp eq i32 %357, 0
  br i1 %358, label %checkContinueBlock100, label %afterNestedBlock98

checkContinueBlock100:                            ; preds = %nestedBlock99
  %359 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %360 = icmp eq i32 %359, 0
  br i1 %360, label %nestedBlock101, label %afterNestedBlock98

nestedBlock101:                                   ; preds = %checkContinueBlock100
  %361 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y103 = load i32, ptr %361, align 4
  %362 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y104 = load i32, ptr %362, align 4
  %363 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %364 = load i32, ptr %363, align 4
  %365 = add i32 %y104, %364
  store i32 %365, ptr %361, align 4
  %366 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %367 = icmp eq i32 %366, 0
  br i1 %367, label %checkContinueBlock102, label %afterNestedBlock98

checkContinueBlock102:                            ; preds = %nestedBlock101
  br label %afterNestedBlock98

afterNestedBlock105:                              ; preds = %checkContinueBlock109, %nestedBlock108, %checkContinueBlock107, %nestedBlock106
  br label %afterIfElse

nestedBlock106:                                   ; preds = %orIfThen1
  %368 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %369 = load i1, ptr %368, align 1
  %370 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %370, align 1
  %371 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %372 = icmp eq i32 %371, 0
  br i1 %372, label %checkContinueBlock107, label %afterNestedBlock105

checkContinueBlock107:                            ; preds = %nestedBlock106
  %373 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %374 = icmp eq i32 %373, 0
  br i1 %374, label %nestedBlock108, label %afterNestedBlock105

nestedBlock108:                                   ; preds = %checkContinueBlock107
  %375 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x = load i32, ptr %375, align 4
  %376 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x110 = load i32, ptr %376, align 4
  %377 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %378 = load i32, ptr %377, align 4
  %379 = add i32 %x110, %378
  store i32 %379, ptr %375, align 4
  %380 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %381 = icmp eq i32 %380, 0
  br i1 %381, label %checkContinueBlock109, label %afterNestedBlock105

checkContinueBlock109:                            ; preds = %nestedBlock108
  br label %afterNestedBlock105

afterNestedBlock111:                              ; preds = %checkContinueBlock115, %nestedBlock114, %checkContinueBlock113, %nestedBlock112
  br label %afterIfElse

nestedBlock112:                                   ; preds = %orIfThen2
  %382 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %383 = load i1, ptr %382, align 1
  %384 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %384, align 1
  %385 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %386 = icmp eq i32 %385, 0
  br i1 %386, label %checkContinueBlock113, label %afterNestedBlock111

checkContinueBlock113:                            ; preds = %nestedBlock112
  %387 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %388 = icmp eq i32 %387, 0
  br i1 %388, label %nestedBlock114, label %afterNestedBlock111

nestedBlock114:                                   ; preds = %checkContinueBlock113
  %389 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x116 = load i32, ptr %389, align 4
  %390 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x117 = load i32, ptr %390, align 4
  %391 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %392 = load i32, ptr %391, align 4
  %393 = sub i32 %x117, %392
  store i32 %393, ptr %389, align 4
  %394 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %395 = icmp eq i32 %394, 0
  br i1 %395, label %checkContinueBlock115, label %afterNestedBlock111

checkContinueBlock115:                            ; preds = %nestedBlock114
  br label %afterNestedBlock111

then119:                                          ; preds = %nestedBlock60
  br label %nestedBlock123

else120:                                          ; preds = %nestedBlock60
  br label %afterIfElse121

afterIfElse121:                                   ; preds = %else120, %afterNestedBlock122
  %396 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %397 = icmp eq i32 %396, 0
  br i1 %397, label %checkContinueBlock61, label %afterNestedBlock55

afterNestedBlock122:                              ; preds = %checkContinueBlock124, %nestedBlock123
  br label %afterIfElse121

nestedBlock123:                                   ; preds = %then119
  %398 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x125 = load i32, ptr %398, align 4
  store i32 0, ptr %398, align 4
  %399 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %400 = icmp eq i32 %399, 0
  br i1 %400, label %checkContinueBlock124, label %afterNestedBlock122

checkContinueBlock124:                            ; preds = %nestedBlock123
  br label %afterNestedBlock122

then128:                                          ; preds = %nestedBlock62
  br label %nestedBlock132

else129:                                          ; preds = %nestedBlock62
  br label %afterIfElse130

afterIfElse130:                                   ; preds = %else129, %afterNestedBlock131
  %401 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %402 = icmp eq i32 %401, 0
  br i1 %402, label %checkContinueBlock63, label %afterNestedBlock55

afterNestedBlock131:                              ; preds = %checkContinueBlock133, %nestedBlock132
  br label %afterIfElse130

nestedBlock132:                                   ; preds = %then128
  %403 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x134 = load i32, ptr %403, align 4
  %screenWidth135 = load i32, ptr @screenWidth, align 4
  %404 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %405 = load i32, ptr %404, align 4
  %406 = sub i32 %screenWidth135, %405
  store i32 %406, ptr %403, align 4
  %407 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %408 = icmp eq i32 %407, 0
  br i1 %408, label %checkContinueBlock133, label %afterNestedBlock131

checkContinueBlock133:                            ; preds = %nestedBlock132
  br label %afterNestedBlock131

then137:                                          ; preds = %nestedBlock64
  br label %nestedBlock141

else138:                                          ; preds = %nestedBlock64
  br label %afterIfElse139

afterIfElse139:                                   ; preds = %else138, %afterNestedBlock140
  %409 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %410 = icmp eq i32 %409, 0
  br i1 %410, label %checkContinueBlock65, label %afterNestedBlock55

afterNestedBlock140:                              ; preds = %checkContinueBlock142, %nestedBlock141
  br label %afterIfElse139

nestedBlock141:                                   ; preds = %then137
  %411 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y143 = load i32, ptr %411, align 4
  store i32 0, ptr %411, align 4
  %412 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %413 = icmp eq i32 %412, 0
  br i1 %413, label %checkContinueBlock142, label %afterNestedBlock140

checkContinueBlock142:                            ; preds = %nestedBlock141
  br label %afterNestedBlock140

then146:                                          ; preds = %nestedBlock66
  br label %nestedBlock150

else147:                                          ; preds = %nestedBlock66
  br label %afterIfElse148

afterIfElse148:                                   ; preds = %else147, %afterNestedBlock149
  %414 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %415 = icmp eq i32 %414, 0
  br i1 %415, label %checkContinueBlock67, label %afterNestedBlock55

afterNestedBlock149:                              ; preds = %checkContinueBlock151, %nestedBlock150
  br label %afterIfElse148

nestedBlock150:                                   ; preds = %then146
  %416 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y152 = load i32, ptr %416, align 4
  %screenHeight153 = load i32, ptr @screenHeight, align 4
  %417 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %418 = load i32, ptr %417, align 4
  %419 = sub i32 %screenHeight153, %418
  store i32 %419, ptr %416, align 4
  %420 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %421 = icmp eq i32 %420, 0
  br i1 %421, label %checkContinueBlock151, label %afterNestedBlock149

checkContinueBlock151:                            ; preds = %nestedBlock150
  br label %afterNestedBlock149

then158:                                          ; preds = %nestedBlock68
  br label %nestedBlock162

else159:                                          ; preds = %nestedBlock68
  br label %afterIfElse160

afterIfElse160:                                   ; preds = %else159, %afterNestedBlock161
  %422 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %423 = icmp eq i32 %422, 0
  br i1 %423, label %checkContinueBlock69, label %afterNestedBlock55

afterNestedBlock161:                              ; preds = %checkContinueBlock165, %nestedBlock164, %checkContinueBlock163, %nestedBlock162
  br label %afterIfElse160

nestedBlock162:                                   ; preds = %then158
  call void @getFoodPosition(ptr %foodPos)
  %424 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %425 = icmp eq i32 %424, 0
  br i1 %425, label %checkContinueBlock163, label %afterNestedBlock161

checkContinueBlock163:                            ; preds = %nestedBlock162
  %426 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %427 = icmp eq i32 %426, 0
  br i1 %427, label %nestedBlock164, label %afterNestedBlock161

nestedBlock164:                                   ; preds = %checkContinueBlock163
  %tail166 = load i32, ptr %tail, align 4
  %tail167 = load i32, ptr %tail, align 4
  %428 = add i32 %tail167, 1
  store i32 %428, ptr %tail, align 4
  %429 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %430 = icmp eq i32 %429, 0
  br i1 %430, label %checkContinueBlock165, label %afterNestedBlock161

checkContinueBlock165:                            ; preds = %nestedBlock164
  br label %afterNestedBlock161

then168:                                          ; preds = %nestedBlock70
  br label %nestedBlock172

else169:                                          ; preds = %nestedBlock70
  br label %afterIfElse170

afterIfElse170:                                   ; preds = %else169, %afterNestedBlock171
  %431 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %432 = icmp eq i32 %431, 0
  br i1 %432, label %checkContinueBlock71, label %afterNestedBlock55

afterNestedBlock171:                              ; preds = %checkContinueBlock173, %end_block213
  br label %afterIfElse170

nestedBlock172:                                   ; preds = %then168
  %tail174 = load i32, ptr %tail, align 4
  %433 = sub i32 %tail174, 1
  %index = alloca i32, align 4
  store i32 0, ptr %index, align 4
  store i32 %433, ptr %index, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock173:                            ; preds = %end_block213
  br label %afterNestedBlock171

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock178, %nestedBlock172
  %434 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %435 = icmp eq i32 %434, 0
  br i1 %435, label %end_block176, label %decrement_block175

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock179

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %436 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %437 = icmp eq i32 %436, 0
  br i1 %437, label %end_block213, label %decrement_block212

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %438 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %439 = icmp eq i32 %438, 0
  br i1 %439, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block175:                               ; preds = %"ForLoop::loopCondition"
  %440 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %441 = sub i32 %440, 1
  store i32 %441, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block176

end_block176:                                     ; preds = %decrement_block175, %"ForLoop::loopCondition"
  %index177 = load i32, ptr %index, align 4
  br i1 true, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block176
  %442 = icmp sge i32 %index177, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block176
  %443 = icmp sle i32 %index177, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %444 = phi i1 [ %442, %"ForLoop::Conditon::trueBlock" ], [ %443, %"ForLoop::Conditon::falseBlock" ]
  br i1 %444, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock178:                              ; preds = %checkContinueBlock182, %"GlobalIndexExpr::merge208", %checkContinueBlock180, %"GlobalIndexExpr::merge192"
  %445 = add i32 %index177, -1
  store i32 %445, ptr %index, align 4
  br label %"ForLoop::loopCondition"

nestedBlock179:                                   ; preds = %"ForLoop::loopBody"
  %index183 = load i32, ptr %index, align 4
  %posX184 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %index183, 10000
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %index183, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then185", label %"GlobalIndexExpr::else186"

checkContinueBlock180:                            ; preds = %"GlobalIndexExpr::merge192"
  %446 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %447 = icmp eq i32 %446, 0
  br i1 %447, label %nestedBlock181, label %afterNestedBlock178

nestedBlock181:                                   ; preds = %checkContinueBlock180
  %index196 = load i32, ptr %index, align 4
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
  %448 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index183
  %449 = load i32, ptr %448, align 4
  %index188 = load i32, ptr %index, align 4
  %450 = sub i32 %index188, 1
  %posX189 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan193" = icmp slt i32 %450, 10000
  %"GlobalIndexExpr::isGreaterThan194" = icmp sge i32 %450, 0
  %"GlobalIndexExpr::isWithinBounds195" = and i1 %"GlobalIndexExpr::isLessThan193", %"GlobalIndexExpr::isGreaterThan194"
  br i1 %"GlobalIndexExpr::isWithinBounds195", label %"GlobalIndexExpr::then190", label %"GlobalIndexExpr::else191"

"GlobalIndexExpr::then190":                       ; preds = %"GlobalIndexExpr::merge187"
  br label %"GlobalIndexExpr::merge192"

"GlobalIndexExpr::else191":                       ; preds = %"GlobalIndexExpr::merge187"
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge192"

"GlobalIndexExpr::merge192":                      ; preds = %"GlobalIndexExpr::else191", %"GlobalIndexExpr::then190"
  %451 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %450
  %452 = load i32, ptr %451, align 4
  %453 = load i32, ptr %451, align 4
  store i32 %453, ptr %448, align 4
  %454 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %455 = icmp eq i32 %454, 0
  br i1 %455, label %checkContinueBlock180, label %afterNestedBlock178

"GlobalIndexExpr::then198":                       ; preds = %nestedBlock181
  br label %"GlobalIndexExpr::merge200"

"GlobalIndexExpr::else199":                       ; preds = %nestedBlock181
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge200"

"GlobalIndexExpr::merge200":                      ; preds = %"GlobalIndexExpr::else199", %"GlobalIndexExpr::then198"
  %456 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index196
  %457 = load i32, ptr %456, align 4
  %index204 = load i32, ptr %index, align 4
  %458 = sub i32 %index204, 1
  %posY205 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan209" = icmp slt i32 %458, 10000
  %"GlobalIndexExpr::isGreaterThan210" = icmp sge i32 %458, 0
  %"GlobalIndexExpr::isWithinBounds211" = and i1 %"GlobalIndexExpr::isLessThan209", %"GlobalIndexExpr::isGreaterThan210"
  br i1 %"GlobalIndexExpr::isWithinBounds211", label %"GlobalIndexExpr::then206", label %"GlobalIndexExpr::else207"

"GlobalIndexExpr::then206":                       ; preds = %"GlobalIndexExpr::merge200"
  br label %"GlobalIndexExpr::merge208"

"GlobalIndexExpr::else207":                       ; preds = %"GlobalIndexExpr::merge200"
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge208"

"GlobalIndexExpr::merge208":                      ; preds = %"GlobalIndexExpr::else207", %"GlobalIndexExpr::then206"
  %459 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %458
  %460 = load i32, ptr %459, align 4
  %461 = load i32, ptr %459, align 4
  store i32 %461, ptr %456, align 4
  %462 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %463 = icmp eq i32 %462, 0
  br i1 %463, label %checkContinueBlock182, label %afterNestedBlock178

decrement_block212:                               ; preds = %"ForLoop::afterLoop"
  %464 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %465 = sub i32 %464, 1
  store i32 %465, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block213

end_block213:                                     ; preds = %decrement_block212, %"ForLoop::afterLoop"
  %466 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %467 = icmp eq i32 %466, 0
  br i1 %467, label %checkContinueBlock173, label %afterNestedBlock171

"GlobalIndexExpr::then215":                       ; preds = %nestedBlock72
  br label %"GlobalIndexExpr::merge217"

"GlobalIndexExpr::else216":                       ; preds = %nestedBlock72
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge217"

"GlobalIndexExpr::merge217":                      ; preds = %"GlobalIndexExpr::else216", %"GlobalIndexExpr::then215"
  %468 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %469 = load i32, ptr %468, align 4
  %470 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 0
  %x218 = load i32, ptr %470, align 4
  %471 = load i32, ptr %470, align 4
  store i32 %471, ptr %468, align 4
  %472 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %473 = icmp eq i32 %472, 0
  br i1 %473, label %checkContinueBlock73, label %afterNestedBlock55

"GlobalIndexExpr::then220":                       ; preds = %nestedBlock74
  br label %"GlobalIndexExpr::merge222"

"GlobalIndexExpr::else221":                       ; preds = %nestedBlock74
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge222"

"GlobalIndexExpr::merge222":                      ; preds = %"GlobalIndexExpr::else221", %"GlobalIndexExpr::then220"
  %474 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %475 = load i32, ptr %474, align 4
  %476 = getelementptr inbounds %Position.3, ptr %newPos, i32 0, i32 1
  %y223 = load i32, ptr %476, align 4
  %477 = load i32, ptr %476, align 4
  store i32 %477, ptr %474, align 4
  %478 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %479 = icmp eq i32 %478, 0
  br i1 %479, label %checkContinueBlock75, label %afterNestedBlock55

"ForLoop::loopCondition226":                      ; preds = %afterNestedBlock236, %nestedBlock80
  %480 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %481 = icmp eq i32 %480, 0
  br i1 %481, label %end_block231, label %decrement_block230

"ForLoop::loopBody227":                           ; preds = %"ForLoop::breakLoop229"
  br label %nestedBlock237

"ForLoop::afterLoop228":                          ; preds = %"ForLoop::breakLoop229", %"ForLoop::Conditon::mergeBlock235"
  %482 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %483 = icmp eq i32 %482, 0
  br i1 %483, label %end_block257, label %decrement_block256

"ForLoop::breakLoop229":                          ; preds = %"ForLoop::Conditon::mergeBlock235"
  %484 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %485 = icmp eq i32 %484, 0
  br i1 %485, label %"ForLoop::loopBody227", label %"ForLoop::afterLoop228"

decrement_block230:                               ; preds = %"ForLoop::loopCondition226"
  %486 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %487 = sub i32 %486, 1
  store i32 %487, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block231

end_block231:                                     ; preds = %decrement_block230, %"ForLoop::loopCondition226"
  %index232 = load i32, ptr %index225, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock233", label %"ForLoop::Conditon::falseBlock234"

"ForLoop::Conditon::trueBlock233":                ; preds = %end_block231
  %488 = icmp sge i32 %index232, %266
  br label %"ForLoop::Conditon::mergeBlock235"

"ForLoop::Conditon::falseBlock234":               ; preds = %end_block231
  %489 = icmp sle i32 %index232, %266
  br label %"ForLoop::Conditon::mergeBlock235"

"ForLoop::Conditon::mergeBlock235":               ; preds = %"ForLoop::Conditon::falseBlock234", %"ForLoop::Conditon::trueBlock233"
  %490 = phi i1 [ %488, %"ForLoop::Conditon::trueBlock233" ], [ %489, %"ForLoop::Conditon::falseBlock234" ]
  br i1 %490, label %"ForLoop::breakLoop229", label %"ForLoop::afterLoop228"

afterNestedBlock236:                              ; preds = %checkContinueBlock238, %"GlobalIndexExpr::merge251"
  %491 = add i32 %index232, 1
  store i32 %491, ptr %index225, align 4
  br label %"ForLoop::loopCondition226"

nestedBlock237:                                   ; preds = %"ForLoop::loopBody227"
  %492 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 0
  %493 = load ptr, ptr %492, align 8
  %494 = getelementptr inbounds %"FlowWingAnim::VTableType", ptr %493, i32 0, i32 10
  %495 = load ptr, ptr %494, align 8
  %index239 = load i32, ptr %index225, align 4
  %posX240 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan244" = icmp slt i32 %index239, 10000
  %"GlobalIndexExpr::isGreaterThan245" = icmp sge i32 %index239, 0
  %"GlobalIndexExpr::isWithinBounds246" = and i1 %"GlobalIndexExpr::isLessThan244", %"GlobalIndexExpr::isGreaterThan245"
  br i1 %"GlobalIndexExpr::isWithinBounds246", label %"GlobalIndexExpr::then241", label %"GlobalIndexExpr::else242"

checkContinueBlock238:                            ; preds = %"GlobalIndexExpr::merge251"
  br label %afterNestedBlock236

"GlobalIndexExpr::then241":                       ; preds = %nestedBlock237
  br label %"GlobalIndexExpr::merge243"

"GlobalIndexExpr::else242":                       ; preds = %nestedBlock237
  call void @raise_exception(ptr @14)
  br label %"GlobalIndexExpr::merge243"

"GlobalIndexExpr::merge243":                      ; preds = %"GlobalIndexExpr::else242", %"GlobalIndexExpr::then241"
  %496 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index239
  %497 = load i32, ptr %496, align 4
  %index247 = load i32, ptr %index225, align 4
  %posY248 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan252" = icmp slt i32 %index247, 10000
  %"GlobalIndexExpr::isGreaterThan253" = icmp sge i32 %index247, 0
  %"GlobalIndexExpr::isWithinBounds254" = and i1 %"GlobalIndexExpr::isLessThan252", %"GlobalIndexExpr::isGreaterThan253"
  br i1 %"GlobalIndexExpr::isWithinBounds254", label %"GlobalIndexExpr::then249", label %"GlobalIndexExpr::else250"

"GlobalIndexExpr::then249":                       ; preds = %"GlobalIndexExpr::merge243"
  br label %"GlobalIndexExpr::merge251"

"GlobalIndexExpr::else250":                       ; preds = %"GlobalIndexExpr::merge243"
  call void @raise_exception(ptr @15)
  br label %"GlobalIndexExpr::merge251"

"GlobalIndexExpr::merge251":                      ; preds = %"GlobalIndexExpr::else250", %"GlobalIndexExpr::then249"
  %498 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index247
  %499 = load i32, ptr %498, align 4
  %side = load i32, ptr @side, align 4
  %side255 = load i32, ptr @side, align 4
  %500 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 5
  %501 = getelementptr inbounds %COLORS_TYPE.2, ptr %500, i32 0, i32 3
  %BLUE = load i32, ptr %501, align 4
  call void %495(ptr %496, ptr %498, ptr @side, ptr @side, ptr %501, ptr %32)
  %502 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %503 = icmp eq i32 %502, 0
  br i1 %503, label %checkContinueBlock238, label %afterNestedBlock236

decrement_block256:                               ; preds = %"ForLoop::afterLoop228"
  %504 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %505 = sub i32 %504, 1
  store i32 %505, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block257

end_block257:                                     ; preds = %decrement_block256, %"ForLoop::afterLoop228"
  %506 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %507 = icmp eq i32 %506, 0
  br i1 %507, label %checkContinueBlock81, label %afterNestedBlock55

if:                                               ; preds = %nestedBlock82
  call void @raise_exception(ptr @16)
  br label %merge

else259:                                          ; preds = %nestedBlock82
  %508 = sdiv i32 %screenWidth258, 5
  br label %merge

merge:                                            ; preds = %else259, %if
  %509 = alloca i32, align 4
  store i32 %508, ptr %509, align 4
  %510 = alloca i32, align 4
  store i32 120, ptr %510, align 4
  %511 = alloca float, align 4
  store float 3.500000e+01, ptr %511, align 4
  %512 = getelementptr inbounds %FlowWingAnim, ptr %32, i32 0, i32 5
  %513 = getelementptr inbounds %COLORS_TYPE.2, ptr %512, i32 0, i32 4
  %DARKBLUE = load i32, ptr %513, align 4
  call void %272(ptr %509, ptr %510, ptr %511, ptr %513, ptr %32)
  %514 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %515 = icmp eq i32 %514, 0
  br i1 %515, label %checkContinueBlock83, label %afterNestedBlock55

decrement_block264:                               ; preds = %while.end
  %516 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %517 = sub i32 %516, 1
  store i32 %517, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block265

end_block265:                                     ; preds = %decrement_block264, %while.end
  %518 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %519 = icmp eq i32 %518, 0
  br i1 %519, label %checkContinueBlock22, label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock25
  ret i32 0

mergeBlock:                                       ; No predecessors!
  %520 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %521 = icmp eq i32 %520, 0
  br i1 %521, label %checkContinueBlock26, label %afterNestedBlock
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
!16 = !{!"FlowWingAnim.loadTexture:rt:ob:Texture"}
!17 = !{!"FlowWingAnim.isKeyPressed:rt:pr:34"}
!18 = !{!"FlowWingAnim.isKeyDown:rt:pr:34"}
!19 = !{!"FlowWingAnim.textFormat:rt:pr:33"}
!20 = !{!"DrawText:rt:pr:27"}
!21 = !{!"SetTargetFPS:rt:pr:27"}
!22 = !{!"EndDrawing:rt:pr:27"}
!23 = !{!"InitWindow:rt:pr:27"}
!24 = !{!"ClearBackground:rt:pr:27"}
!25 = !{!"GetScreenWidth:rt:pr:28"}
!26 = !{!"DrawCircle:rt:pr:27"}
!27 = !{!"DrawRectangle:rt:pr:27"}
!28 = !{!"WindowShouldClose:rt:pr:34"}
!29 = !{!"LoadTexture:rt:ob:Texture"}
!30 = !{!"TextFormat:rt:pr:33"}
!31 = !{!"time:rt:pr:28"}
!32 = !{!"BeginDrawing:rt:pr:27"}
!33 = !{!"IsKeyPressed:rt:pr:34"}
!34 = !{!"CloseWindow:rt:pr:27"}
!35 = !{!"getRandomNumber:rt:pr:28"}
!36 = !{!"IsKeyDown:rt:pr:34"}
!37 = !{!"GetScreenHeight:rt:pr:28"}
!38 = !{!"DrawTexture:rt:pr:27"}
!39 = !{!"rand:rt:pr:28"}
!40 = !{!"srand:rt:pr:27"}
!41 = !{!"getFoodPosition:rt:ob:Position"}
!42 = !{!"main:rt:pr:28"}
