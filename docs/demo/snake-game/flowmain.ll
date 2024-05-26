; ModuleID = 'flowmain'
source_filename = "flowmain"

%Position.0 = type { i32, i32 }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@WHITE = extern_weak global i32 0
@RED = extern_weak global i32 0
@GREEN = extern_weak global i32 0
@BLUE = extern_weak global i32 0
@DARKBLUE = extern_weak global i32 0
@screenWidth = extern_weak global i32 0
@screenHeight = extern_weak global i32 0
@side = extern_weak global i32 0
@KEY_RIGHT = extern_weak global i32 0
@KEY_LEFT = extern_weak global i32 0
@KEY_DOWN = extern_weak global i32 0
@KEY_UP = extern_weak global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [688 x i8] c"\0A\1B[33m43| \1B[0m\1B[0m    var posX: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m44| \1B[0m\1B[0m    var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m45| \1B[0m\1B[0m\0A\1B[0m\1B[33m46| \1B[0m\1B[0m  \0A\1B[0m\1B[33m47| \1B[0m\1B[31m\1B[1m    posX[0] = 0\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m48| \1B[0m\1B[0m    posY[0] = 0\0A\1B[0m\1B[33m49| \1B[0m\1B[0m    var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m50| \1B[0m\1B[0m      var newPos: Position = {\0A\1B[0m\1B[33m51| \1B[0m\1B[0m          x: posX[0],\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 47:10\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@2 = private unnamed_addr constant [666 x i8] c"\0A\1B[33m44| \1B[0m\1B[0m    var posY: int[10000] = [10000 fill -1]\0A\1B[0m\1B[33m45| \1B[0m\1B[0m\0A\1B[0m\1B[33m46| \1B[0m\1B[0m  \0A\1B[0m\1B[33m47| \1B[0m\1B[0m    posX[0] = 0\0A\1B[0m\1B[33m48| \1B[0m\1B[31m\1B[1m    posY[0] = 0\0A\1B[0m\1B[32m\1B[1m          \0A   ~~~~~~~~~^\1B[0m\0A\1B[33m49| \1B[0m\1B[0m    var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m50| \1B[0m\1B[0m      var newPos: Position = {\0A\1B[0m\1B[33m51| \1B[0m\1B[0m          x: posX[0],\0A\1B[0m\1B[33m52| \1B[0m\1B[0m          y: posY[0]\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 48:10\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@3 = private unnamed_addr constant [712 x i8] c"\0A\1B[33m47| \1B[0m\1B[0m    posX[0] = 0\0A\1B[0m\1B[33m48| \1B[0m\1B[0m    posY[0] = 0\0A\1B[0m\1B[33m49| \1B[0m\1B[0m    var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m50| \1B[0m\1B[0m      var newPos: Position = {\0A\1B[0m\1B[33m51| \1B[0m\1B[31m\1B[1m          x: posX[0],\0A\1B[0m\1B[32m\1B[1m                   \0A   ~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m52| \1B[0m\1B[0m          y: posY[0]\0A\1B[0m\1B[33m53| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m54| \1B[0m\1B[0m\0A\1B[0m\1B[33m55| \1B[0m\1B[0m    InitWindow(screenWidth,screenHeight,\22snake-game-in-flowwing\22)\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 51:19\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@4 = private unnamed_addr constant [730 x i8] c"\0A\1B[33m48| \1B[0m\1B[0m    posY[0] = 0\0A\1B[0m\1B[33m49| \1B[0m\1B[0m    var foodPos: Position = getFoodPosition()\0A\1B[0m\1B[33m50| \1B[0m\1B[0m      var newPos: Position = {\0A\1B[0m\1B[33m51| \1B[0m\1B[0m          x: posX[0],\0A\1B[0m\1B[33m52| \1B[0m\1B[31m\1B[1m          y: posY[0]\0A\1B[0m\1B[32m\1B[1m                   \0A   ~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m53| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m54| \1B[0m\1B[0m\0A\1B[0m\1B[33m55| \1B[0m\1B[0m    InitWindow(screenWidth,screenHeight,\22snake-game-in-flowwing\22)\0A\1B[0m\1B[33m56| \1B[0m\1B[0m    while(!WindowShouldClose()) {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 52:19\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@5 = private unnamed_addr constant [23 x i8] c"snake-game-in-flowwing\00", align 1
@6 = private unnamed_addr constant [692 x i8] c"\0A\1B[33m95| \1B[0m\1B[0m\0A\1B[0m\1B[33m96| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m97| \1B[0m\1B[0m      if(isKeyPressed) {\0A\1B[0m\1B[33m98| \1B[0m\1B[0m        for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m99| \1B[0m\1B[31m\1B[1m          posX[index] =  posX[index - 1]\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m100| \1B[0m\1B[0m          posY[index] = posY[index - 1]\0A\1B[0m\1B[33m101| \1B[0m\1B[0m        }\0A\1B[0m\1B[33m102| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m103| \1B[0m\1B[0m      posX[0] = newPos.x \0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 99:16\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@7 = private unnamed_addr constant [738 x i8] c"\0A\1B[33m95| \1B[0m\1B[0m\0A\1B[0m\1B[33m96| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m97| \1B[0m\1B[0m      if(isKeyPressed) {\0A\1B[0m\1B[33m98| \1B[0m\1B[0m        for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m99| \1B[0m\1B[31m\1B[1m          posX[index] =  posX[index - 1]\0A\1B[0m\1B[32m\1B[1m                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m100| \1B[0m\1B[0m          posY[index] = posY[index - 1]\0A\1B[0m\1B[33m101| \1B[0m\1B[0m        }\0A\1B[0m\1B[33m102| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m103| \1B[0m\1B[0m      posX[0] = newPos.x \0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 99:39\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@8 = private unnamed_addr constant [718 x i8] c"\0A\1B[33m96| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m97| \1B[0m\1B[0m      if(isKeyPressed) {\0A\1B[0m\1B[33m98| \1B[0m\1B[0m        for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m99| \1B[0m\1B[0m          posX[index] =  posX[index - 1]\0A\1B[0m\1B[33m100| \1B[0m\1B[31m\1B[1m          posY[index] = posY[index - 1]\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m101| \1B[0m\1B[0m        }\0A\1B[0m\1B[33m102| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m103| \1B[0m\1B[0m      posX[0] = newPos.x \0A\1B[0m\1B[33m104| \1B[0m\1B[0m      posY[0] = newPos.y\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 100:16\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@9 = private unnamed_addr constant [762 x i8] c"\0A\1B[33m96| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m97| \1B[0m\1B[0m      if(isKeyPressed) {\0A\1B[0m\1B[33m98| \1B[0m\1B[0m        for var index: int = tail - 1 to 1 : -1 {\0A\1B[0m\1B[33m99| \1B[0m\1B[0m          posX[index] =  posX[index - 1]\0A\1B[0m\1B[33m100| \1B[0m\1B[31m\1B[1m          posY[index] = posY[index - 1]\0A\1B[0m\1B[32m\1B[1m                                      \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m101| \1B[0m\1B[0m        }\0A\1B[0m\1B[33m102| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m103| \1B[0m\1B[0m      posX[0] = newPos.x \0A\1B[0m\1B[33m104| \1B[0m\1B[0m      posY[0] = newPos.y\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 100:38\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@10 = private unnamed_addr constant [722 x i8] c"\0A\1B[33m99| \1B[0m\1B[0m          posX[index] =  posX[index - 1]\0A\1B[0m\1B[33m100| \1B[0m\1B[0m          posY[index] = posY[index - 1]\0A\1B[0m\1B[33m101| \1B[0m\1B[0m        }\0A\1B[0m\1B[33m102| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m103| \1B[0m\1B[31m\1B[1m      posX[0] = newPos.x \0A\1B[0m\1B[32m\1B[1m            \0A   ~~~~~~~~~~~^\1B[0m\0A\1B[33m104| \1B[0m\1B[0m      posY[0] = newPos.y\0A\1B[0m\1B[33m105| \1B[0m\1B[0m      BeginDrawing()\0A\1B[0m\1B[33m106| \1B[0m\1B[0m      ClearBackground(WHITE)\0A\1B[0m\1B[33m107| \1B[0m\1B[0m      for var index: int = 0 to tail -1 {\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 103:12\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@11 = private unnamed_addr constant [750 x i8] c"\0A\1B[33m100| \1B[0m\1B[0m          posY[index] = posY[index - 1]\0A\1B[0m\1B[33m101| \1B[0m\1B[0m        }\0A\1B[0m\1B[33m102| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m103| \1B[0m\1B[0m      posX[0] = newPos.x \0A\1B[0m\1B[33m104| \1B[0m\1B[31m\1B[1m      posY[0] = newPos.y\0A\1B[0m\1B[32m\1B[1m            \0A   ~~~~~~~~~~~^\1B[0m\0A\1B[33m105| \1B[0m\1B[0m      BeginDrawing()\0A\1B[0m\1B[33m106| \1B[0m\1B[0m      ClearBackground(WHITE)\0A\1B[0m\1B[33m107| \1B[0m\1B[0m      for var index: int = 0 to tail -1 {\0A\1B[0m\1B[33m108| \1B[0m\1B[0m        DrawRectangle(posX[index] , posY[index], side, side, BLUE) \0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 104:12\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@12 = private unnamed_addr constant [851 x i8] c"\0A\1B[33m104| \1B[0m\1B[0m      posY[0] = newPos.y\0A\1B[0m\1B[33m105| \1B[0m\1B[0m      BeginDrawing()\0A\1B[0m\1B[33m106| \1B[0m\1B[0m      ClearBackground(WHITE)\0A\1B[0m\1B[33m107| \1B[0m\1B[0m      for var index: int = 0 to tail -1 {\0A\1B[0m\1B[33m108| \1B[0m\1B[31m\1B[1m        DrawRectangle(posX[index] , posY[index], side, side, BLUE) \0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m109| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m110| \1B[0m\1B[0m      DrawCircle(screenWidth //5, 120, 35.0d, DARKBLUE)\0A\1B[0m\1B[33m111| \1B[0m\1B[0m      DrawRectangle(foodPos.x, foodPos.y, side, side, GREEN)         \0A\1B[0m\1B[33m112| \1B[0m\1B[0m      EndDrawing()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 108:28\1B[31m \22Index out of bounds of 'posX' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@13 = private unnamed_addr constant [879 x i8] c"\0A\1B[33m104| \1B[0m\1B[0m      posY[0] = newPos.y\0A\1B[0m\1B[33m105| \1B[0m\1B[0m      BeginDrawing()\0A\1B[0m\1B[33m106| \1B[0m\1B[0m      ClearBackground(WHITE)\0A\1B[0m\1B[33m107| \1B[0m\1B[0m      for var index: int = 0 to tail -1 {\0A\1B[0m\1B[33m108| \1B[0m\1B[31m\1B[1m        DrawRectangle(posX[index] , posY[index], side, side, BLUE) \0A\1B[0m\1B[32m\1B[1m                                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m109| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m110| \1B[0m\1B[0m      DrawCircle(screenWidth //5, 120, 35.0d, DARKBLUE)\0A\1B[0m\1B[33m111| \1B[0m\1B[0m      DrawRectangle(foodPos.x, foodPos.y, side, side, GREEN)         \0A\1B[0m\1B[33m112| \1B[0m\1B[0m      EndDrawing()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 108:42\1B[31m \22Index out of bounds of 'posY' in index expression, index value should be between 0 and 10000\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1
@14 = private unnamed_addr constant [772 x i8] c"\0A\1B[33m106| \1B[0m\1B[0m      ClearBackground(WHITE)\0A\1B[0m\1B[33m107| \1B[0m\1B[0m      for var index: int = 0 to tail -1 {\0A\1B[0m\1B[33m108| \1B[0m\1B[0m        DrawRectangle(posX[index] , posY[index], side, side, BLUE) \0A\1B[0m\1B[33m109| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m110| \1B[0m\1B[31m\1B[1m      DrawCircle(screenWidth //5, 120, 35.0d, DARKBLUE)\0A\1B[0m\1B[32m\1B[1m                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m111| \1B[0m\1B[0m      DrawRectangle(foodPos.x, foodPos.y, side, side, GREEN)         \0A\1B[0m\1B[33m112| \1B[0m\1B[0m      EndDrawing()\0A\1B[0m\1B[33m113| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m114| \1B[0m\1B[0m  CloseWindow()\0A\1B[0m\1B[31mFile: index.fg [Error] : \1B[1;31mLine 110:32\1B[31m \22Division by zero is not allowed\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/demo/snake-game/index.fg\0A\1B[0m\00", align 1

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
  %0 = call i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib()
  %1 = alloca i32, align 4
  store i32 255, ptr %1, align 4
  %2 = alloca i32, align 4
  store i32 255, ptr %2, align 4
  %3 = alloca i32, align 4
  store i32 255, ptr %3, align 4
  %4 = alloca i32, align 4
  store i32 255, ptr %4, align 4
  %5 = call i32 @COLOR(ptr %1, ptr %2, ptr %3, ptr %4)
  store i32 0, ptr @WHITE, align 4
  store i32 %5, ptr @WHITE, align 4
  %6 = alloca i32, align 4
  store i32 255, ptr %6, align 4
  %7 = alloca i32, align 4
  store i32 0, ptr %7, align 4
  %8 = alloca i32, align 4
  store i32 0, ptr %8, align 4
  %9 = alloca i32, align 4
  store i32 255, ptr %9, align 4
  %10 = call i32 @COLOR(ptr %6, ptr %7, ptr %8, ptr %9)
  store i32 0, ptr @RED, align 4
  store i32 %10, ptr @RED, align 4
  %11 = alloca i32, align 4
  store i32 0, ptr %11, align 4
  %12 = alloca i32, align 4
  store i32 255, ptr %12, align 4
  %13 = alloca i32, align 4
  store i32 0, ptr %13, align 4
  %14 = alloca i32, align 4
  store i32 255, ptr %14, align 4
  %15 = call i32 @COLOR(ptr %11, ptr %12, ptr %13, ptr %14)
  store i32 0, ptr @GREEN, align 4
  store i32 %15, ptr @GREEN, align 4
  %16 = alloca i32, align 4
  store i32 0, ptr %16, align 4
  %17 = alloca i32, align 4
  store i32 0, ptr %17, align 4
  %18 = alloca i32, align 4
  store i32 255, ptr %18, align 4
  %19 = alloca i32, align 4
  store i32 255, ptr %19, align 4
  %20 = call i32 @COLOR(ptr %16, ptr %17, ptr %18, ptr %19)
  store i32 0, ptr @BLUE, align 4
  store i32 %20, ptr @BLUE, align 4
  %21 = alloca i32, align 4
  store i32 0, ptr %21, align 4
  %22 = alloca i32, align 4
  store i32 82, ptr %22, align 4
  %23 = alloca i32, align 4
  store i32 172, ptr %23, align 4
  %24 = alloca i32, align 4
  store i32 255, ptr %24, align 4
  %25 = call i32 @COLOR(ptr %21, ptr %22, ptr %23, ptr %24)
  store i32 0, ptr @DARKBLUE, align 4
  store i32 %25, ptr @DARKBLUE, align 4
  store i32 0, ptr @screenWidth, align 4
  store i32 1000, ptr @screenWidth, align 4
  store i32 0, ptr @screenHeight, align 4
  store i32 500, ptr @screenHeight, align 4
  store i32 0, ptr @side, align 4
  store i32 10, ptr @side, align 4
  store i32 0, ptr @KEY_RIGHT, align 4
  store i32 262, ptr @KEY_RIGHT, align 4
  store i32 0, ptr @KEY_LEFT, align 4
  store i32 263, ptr @KEY_LEFT, align 4
  store i32 0, ptr @KEY_DOWN, align 4
  store i32 264, ptr @KEY_DOWN, align 4
  store i32 0, ptr @KEY_UP, align 4
  store i32 265, ptr @KEY_UP, align 4
  %26 = call i32 @main()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib()

declare !rt !0 void @srand(i32)

declare !rt !1 i32 @rand()

declare !rt !2 i32 @getRandomNumber(ptr, ptr)

declare !rt !3 i1 @IsKeyDown(i32)

declare !rt !4 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !5 i32 @GetScreenHeight()

declare !rt !6 void @CloseWindow()

declare !rt !7 void @EndDrawing()

declare !rt !8 i1 @IsKeyPressed(i32)

declare !rt !9 i32 @COLOR(ptr, ptr, ptr, ptr)

declare !rt !10 void @BeginDrawing()

declare !rt !11 i32 @time()

declare !rt !12 ptr @TextFormat(ptr)

declare !rt !13 void @DrawCircle(i32, i32, float, i32)

declare !rt !14 i1 @WindowShouldClose()

declare !rt !15 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !16 void @SetTargetFPS(i32)

declare !rt !17 void @InitWindow(i32, i32, ptr)

declare !rt !18 i32 @GetScreenWidth()

declare !rt !19 void @ClearBackground(i32)

define i32 @getN() !rt !20 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  ret i32 2

mergeBlock:                                       ; No predecessors!
  %0 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1 = icmp eq i32 %0, 0
  br i1 %1, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @getFoodPosition() !rt !21 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %mergeBlock, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret ptr @0

nestedBlock:                                      ; preds = %entry
  %pos = alloca %Position.0, align 8
  %0 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 0
  store i32 0, ptr %0, align 4
  %1 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 1
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 0
  %3 = call i32 @getN()
  %4 = load i32, i32 %3, align 4
  store i32 %4, ptr %2, align 4
  %5 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 1
  %6 = call i32 @getN()
  %7 = load i32, i32 %6, align 4
  store i32 %7, ptr %5, align 4
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %12 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 0
  %x = load i32, ptr %12, align 4
  %13 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 0
  %x7 = load i32, ptr %13, align 4
  %14 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 0
  %x8 = load i32, ptr %14, align 4
  %side = load i32, ptr @side, align 4
  %15 = srem i32 %x8, %side
  %16 = sub i32 %x7, %15
  store i32 %16, ptr %12, align 4
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %21 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 1
  %y = load i32, ptr %21, align 4
  %22 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 1
  %y9 = load i32, ptr %22, align 4
  %23 = getelementptr inbounds %Position.0, ptr %pos, i32 0, i32 1
  %y10 = load i32, ptr %23, align 4
  %side11 = load i32, ptr @side, align 4
  %24 = srem i32 %y10, %side11
  %25 = sub i32 %y9, %24
  store i32 %25, ptr %21, align 4
  %26 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  br label %returnBlock

checkContinueBlock6:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock5
  ret ptr %pos

mergeBlock:                                       ; No predecessors!
  %30 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock6, label %afterNestedBlock
}

define i32 @main() !rt !22 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock24, %mergeBlock, %checkContinueBlock22, %nestedBlock21, %checkContinueBlock20, %end_block263, %checkContinueBlock18, %nestedBlock17, %checkContinueBlock16, %"GlobalIndexExpr::merge52", %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %"GlobalIndexExpr::merge44", %checkContinueBlock10, %"GlobalIndexExpr::merge", %checkContinueBlock8, %FillExpr.exit39, %checkContinueBlock6, %FillExpr.exit29, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  call void @SetTargetFPS(i32 60)
  %0 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1 = icmp eq i32 %0, 0
  br i1 %1, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %2 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %speed = alloca %DynamicType, align 8
  %4 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  store i32 10, ptr %4, align 4
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %tail = alloca i32, align 4
  store i32 0, ptr %tail, align 4
  store i32 1, ptr %tail, align 4
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %11 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %posX = alloca [10000 x i32], align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store i32 0, ptr %14, align 4
  br label %FillExpr.loopStart-0

checkContinueBlock6:                              ; preds = %FillExpr.exit29
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  %posY = alloca [10000 x i32], align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  store i32 0, ptr %18, align 4
  br label %FillExpr.loopStart-030

checkContinueBlock8:                              ; preds = %FillExpr.exit39
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  %posX40 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock10:                             ; preds = %"GlobalIndexExpr::merge"
  %21 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %posY41 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then42", label %"GlobalIndexExpr::else43"

checkContinueBlock12:                             ; preds = %"GlobalIndexExpr::merge44"
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %foodPos = alloca %Position.0, align 8
  %25 = getelementptr inbounds %Position.0, ptr %foodPos, i32 0, i32 0
  store i32 0, ptr %25, align 4
  %26 = getelementptr inbounds %Position.0, ptr %foodPos, i32 0, i32 1
  store i32 0, ptr %26, align 4
  %27 = call ptr @getFoodPosition()
  %28 = load %Position.0, ptr %27, align 4
  store %Position.0 %28, ptr %foodPos, align 4
  %29 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %31 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %newPos = alloca %Position.0, align 8
  %33 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  store i32 0, ptr %33, align 4
  %34 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  store i32 0, ptr %34, align 4
  %35 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %posX45 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then46", label %"GlobalIndexExpr::else47"

checkContinueBlock16:                             ; preds = %"GlobalIndexExpr::merge52"
  %36 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %screenWidth = load i32, ptr @screenWidth, align 4
  %38 = load i32, ptr @screenWidth, align 4
  %screenHeight = load i32, ptr @screenHeight, align 4
  %39 = load i32, ptr @screenHeight, align 4
  call void @InitWindow(i32 %38, i32 %39, ptr @5)
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock18, label %afterNestedBlock

checkContinueBlock18:                             ; preds = %nestedBlock17
  %42 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  br label %"while:conditon"

checkContinueBlock20:                             ; preds = %end_block263
  %44 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %nestedBlock21, label %afterNestedBlock

nestedBlock21:                                    ; preds = %checkContinueBlock20
  call void @CloseWindow()
  %46 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %checkContinueBlock22, label %afterNestedBlock

checkContinueBlock22:                             ; preds = %nestedBlock21
  %48 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %nestedBlock23, label %afterNestedBlock

nestedBlock23:                                    ; preds = %checkContinueBlock22
  br label %returnBlock

checkContinueBlock24:                             ; preds = %mergeBlock
  br label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %nestedBlock5
  store i32 0, ptr %13, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %50 = load i32, ptr %13, align 4
  %51 = icmp slt i32 %50, 10000
  %52 = load i32, ptr %14, align 4
  %53 = icmp slt i32 %52, 10000
  %54 = and i1 %51, %53
  br i1 %54, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %55 = load i32, ptr %13, align 4
  %56 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %55
  store i32 0, ptr %56, align 4
  %57 = load i32, ptr %13, align 4
  %58 = add i32 %57, 1
  store i32 %58, ptr %13, align 4
  %59 = load i32, ptr %14, align 4
  %60 = add i32 %59, 1
  store i32 %60, ptr %14, align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %61 = alloca i32, align 4
  %62 = alloca i32, align 4
  store i32 0, ptr %62, align 4
  br label %FillExpr.loopStart-025

FillExpr.loopStart-025:                           ; preds = %FillExpr.exit
  store i32 0, ptr %61, align 4
  br label %FillExpr.loopCmp-026

FillExpr.loopCmp-026:                             ; preds = %FillExpr.loopBody-027, %FillExpr.loopStart-025
  %63 = load i32, ptr %61, align 4
  %64 = icmp slt i32 %63, 10000
  %65 = load i32, ptr %62, align 4
  %66 = icmp slt i32 %65, 10000
  %67 = and i1 %64, %66
  br i1 %67, label %FillExpr.loopBody-027, label %FillExpr.loopEnd-028

FillExpr.loopBody-027:                            ; preds = %FillExpr.loopCmp-026
  %68 = load i32, ptr %61, align 4
  %69 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %68
  store i32 -1, ptr %69, align 4
  %70 = load i32, ptr %61, align 4
  %71 = add i32 %70, 1
  store i32 %71, ptr %61, align 4
  %72 = load i32, ptr %62, align 4
  %73 = add i32 %72, 1
  store i32 %73, ptr %62, align 4
  br label %FillExpr.loopCmp-026

FillExpr.loopEnd-028:                             ; preds = %FillExpr.loopCmp-026
  br label %FillExpr.exit29

FillExpr.exit29:                                  ; preds = %FillExpr.loopEnd-028
  %74 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %checkContinueBlock6, label %afterNestedBlock

FillExpr.loopStart-030:                           ; preds = %nestedBlock7
  store i32 0, ptr %17, align 4
  br label %FillExpr.loopCmp-031

FillExpr.loopCmp-031:                             ; preds = %FillExpr.loopBody-032, %FillExpr.loopStart-030
  %76 = load i32, ptr %17, align 4
  %77 = icmp slt i32 %76, 10000
  %78 = load i32, ptr %18, align 4
  %79 = icmp slt i32 %78, 10000
  %80 = and i1 %77, %79
  br i1 %80, label %FillExpr.loopBody-032, label %FillExpr.loopEnd-033

FillExpr.loopBody-032:                            ; preds = %FillExpr.loopCmp-031
  %81 = load i32, ptr %17, align 4
  %82 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %81
  store i32 0, ptr %82, align 4
  %83 = load i32, ptr %17, align 4
  %84 = add i32 %83, 1
  store i32 %84, ptr %17, align 4
  %85 = load i32, ptr %18, align 4
  %86 = add i32 %85, 1
  store i32 %86, ptr %18, align 4
  br label %FillExpr.loopCmp-031

FillExpr.loopEnd-033:                             ; preds = %FillExpr.loopCmp-031
  br label %FillExpr.exit34

FillExpr.exit34:                                  ; preds = %FillExpr.loopEnd-033
  %87 = alloca i32, align 4
  %88 = alloca i32, align 4
  store i32 0, ptr %88, align 4
  br label %FillExpr.loopStart-035

FillExpr.loopStart-035:                           ; preds = %FillExpr.exit34
  store i32 0, ptr %87, align 4
  br label %FillExpr.loopCmp-036

FillExpr.loopCmp-036:                             ; preds = %FillExpr.loopBody-037, %FillExpr.loopStart-035
  %89 = load i32, ptr %87, align 4
  %90 = icmp slt i32 %89, 10000
  %91 = load i32, ptr %88, align 4
  %92 = icmp slt i32 %91, 10000
  %93 = and i1 %90, %92
  br i1 %93, label %FillExpr.loopBody-037, label %FillExpr.loopEnd-038

FillExpr.loopBody-037:                            ; preds = %FillExpr.loopCmp-036
  %94 = load i32, ptr %87, align 4
  %95 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %94
  store i32 -1, ptr %95, align 4
  %96 = load i32, ptr %87, align 4
  %97 = add i32 %96, 1
  store i32 %97, ptr %87, align 4
  %98 = load i32, ptr %88, align 4
  %99 = add i32 %98, 1
  store i32 %99, ptr %88, align 4
  br label %FillExpr.loopCmp-036

FillExpr.loopEnd-038:                             ; preds = %FillExpr.loopCmp-036
  br label %FillExpr.exit39

FillExpr.exit39:                                  ; preds = %FillExpr.loopEnd-038
  %100 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %checkContinueBlock8, label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %nestedBlock9
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock9
  call void @raise_exception(ptr @1)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %102 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %103 = load i32, ptr %102, align 4
  store i32 0, ptr %102, align 4
  %104 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %105 = icmp eq i32 %104, 0
  br i1 %105, label %checkContinueBlock10, label %afterNestedBlock

"GlobalIndexExpr::then42":                        ; preds = %nestedBlock11
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::else43":                        ; preds = %nestedBlock11
  call void @raise_exception(ptr @2)
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::merge44":                       ; preds = %"GlobalIndexExpr::else43", %"GlobalIndexExpr::then42"
  %106 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %107 = load i32, ptr %106, align 4
  store i32 0, ptr %106, align 4
  %108 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %checkContinueBlock12, label %afterNestedBlock

"GlobalIndexExpr::then46":                        ; preds = %nestedBlock15
  br label %"GlobalIndexExpr::merge48"

"GlobalIndexExpr::else47":                        ; preds = %nestedBlock15
  call void @raise_exception(ptr @3)
  br label %"GlobalIndexExpr::merge48"

"GlobalIndexExpr::merge48":                       ; preds = %"GlobalIndexExpr::else47", %"GlobalIndexExpr::then46"
  %110 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %111 = load i32, ptr %110, align 4
  %112 = load i32, ptr %110, align 4
  store i32 %112, ptr %35, align 4
  %113 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %posY49 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then50", label %"GlobalIndexExpr::else51"

"GlobalIndexExpr::then50":                        ; preds = %"GlobalIndexExpr::merge48"
  br label %"GlobalIndexExpr::merge52"

"GlobalIndexExpr::else51":                        ; preds = %"GlobalIndexExpr::merge48"
  call void @raise_exception(ptr @4)
  br label %"GlobalIndexExpr::merge52"

"GlobalIndexExpr::merge52":                       ; preds = %"GlobalIndexExpr::else51", %"GlobalIndexExpr::then50"
  %114 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %115 = load i32, ptr %114, align 4
  %116 = load i32, ptr %114, align 4
  store i32 %116, ptr %113, align 4
  %117 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %118 = icmp eq i32 %117, 0
  br i1 %118, label %checkContinueBlock16, label %afterNestedBlock

"while:conditon":                                 ; preds = %afterNestedBlock53, %nestedBlock19
  %119 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %120 = icmp eq i32 %119, 0
  br i1 %120, label %end_block, label %decrement_block

"while:body":                                     ; preds = %end_block
  br label %nestedBlock54

while.end:                                        ; preds = %afterNestedBlock53, %end_block
  %121 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %122 = icmp eq i32 %121, 0
  br i1 %122, label %end_block263, label %decrement_block262

decrement_block:                                  ; preds = %"while:conditon"
  %123 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %124 = sub i32 %123, 1
  store i32 %124, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"while:conditon"
  %125 = call i1 @WindowShouldClose()
  %126 = xor i1 %125, true
  br i1 %126, label %"while:body", label %while.end

afterNestedBlock53:                               ; preds = %checkContinueBlock85, %nestedBlock84, %checkContinueBlock83, %nestedBlock82, %checkContinueBlock81, %merge, %checkContinueBlock79, %end_block255, %checkContinueBlock77, %nestedBlock76, %checkContinueBlock75, %nestedBlock74, %checkContinueBlock73, %"GlobalIndexExpr::merge220", %checkContinueBlock71, %"GlobalIndexExpr::merge215", %checkContinueBlock69, %afterIfElse168, %checkContinueBlock67, %afterIfElse158, %checkContinueBlock65, %afterIfElse146, %checkContinueBlock63, %afterIfElse137, %checkContinueBlock61, %afterIfElse128, %checkContinueBlock59, %afterIfElse119, %checkContinueBlock57, %afterIfElse, %checkContinueBlock55, %nestedBlock54
  %127 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %128 = icmp eq i32 %127, 0
  br i1 %128, label %"while:conditon", label %while.end

nestedBlock54:                                    ; preds = %"while:body"
  %isKeyPressed = alloca %DynamicType, align 8
  %129 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 false, ptr %129, align 1
  %130 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %131 = icmp eq i32 %130, 0
  br i1 %131, label %checkContinueBlock55, label %afterNestedBlock53

checkContinueBlock55:                             ; preds = %nestedBlock54
  %132 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %133 = icmp eq i32 %132, 0
  br i1 %133, label %nestedBlock56, label %afterNestedBlock53

nestedBlock56:                                    ; preds = %checkContinueBlock55
  %KEY_UP = load i32, ptr @KEY_UP, align 4
  %134 = load i32, ptr @KEY_UP, align 4
  %135 = call i1 @IsKeyPressed(i32 %134)
  %KEY_UP86 = load i32, ptr @KEY_UP, align 4
  %136 = load i32, ptr @KEY_UP, align 4
  %137 = call i1 @IsKeyDown(i32 %136)
  %138 = select i1 %135, i1 true, i1 %137
  br i1 %138, label %then, label %orIf0

checkContinueBlock57:                             ; preds = %afterIfElse
  %139 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %140 = icmp eq i32 %139, 0
  br i1 %140, label %nestedBlock58, label %afterNestedBlock53

nestedBlock58:                                    ; preds = %checkContinueBlock57
  %141 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x116 = load i32, ptr %141, align 4
  %142 = icmp slt i32 %x116, 0
  br i1 %142, label %then117, label %else118

checkContinueBlock59:                             ; preds = %afterIfElse119
  %143 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %144 = icmp eq i32 %143, 0
  br i1 %144, label %nestedBlock60, label %afterNestedBlock53

nestedBlock60:                                    ; preds = %checkContinueBlock59
  %145 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x124 = load i32, ptr %145, align 4
  %screenWidth125 = load i32, ptr @screenWidth, align 4
  %146 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %147 = load i32, ptr %146, align 4
  %148 = sub i32 %screenWidth125, %147
  %149 = icmp sge i32 %x124, %148
  br i1 %149, label %then126, label %else127

checkContinueBlock61:                             ; preds = %afterIfElse128
  %150 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %151 = icmp eq i32 %150, 0
  br i1 %151, label %nestedBlock62, label %afterNestedBlock53

nestedBlock62:                                    ; preds = %checkContinueBlock61
  %152 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y134 = load i32, ptr %152, align 4
  %153 = icmp slt i32 %y134, 0
  br i1 %153, label %then135, label %else136

checkContinueBlock63:                             ; preds = %afterIfElse137
  %154 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %155 = icmp eq i32 %154, 0
  br i1 %155, label %nestedBlock64, label %afterNestedBlock53

nestedBlock64:                                    ; preds = %checkContinueBlock63
  %156 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y142 = load i32, ptr %156, align 4
  %screenHeight143 = load i32, ptr @screenHeight, align 4
  %157 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %158 = load i32, ptr %157, align 4
  %159 = sub i32 %screenHeight143, %158
  %160 = icmp sge i32 %y142, %159
  br i1 %160, label %then144, label %else145

checkContinueBlock65:                             ; preds = %afterIfElse146
  %161 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %nestedBlock66, label %afterNestedBlock53

nestedBlock66:                                    ; preds = %checkContinueBlock65
  %163 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x152 = load i32, ptr %163, align 4
  %164 = getelementptr inbounds %Position.0, ptr %foodPos, i32 0, i32 0
  %x153 = load i32, ptr %164, align 4
  %165 = icmp eq i32 %x152, %x153
  %166 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y154 = load i32, ptr %166, align 4
  %167 = getelementptr inbounds %Position.0, ptr %foodPos, i32 0, i32 1
  %y155 = load i32, ptr %167, align 4
  %168 = icmp eq i32 %y154, %y155
  %169 = select i1 %165, i1 %168, i1 false
  br i1 %169, label %then156, label %else157

checkContinueBlock67:                             ; preds = %afterIfElse158
  %170 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %nestedBlock68, label %afterNestedBlock53

nestedBlock68:                                    ; preds = %checkContinueBlock67
  %172 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %173 = load i1, ptr %172, align 1
  br i1 %173, label %then166, label %else167

checkContinueBlock69:                             ; preds = %afterIfElse168
  %174 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %175 = icmp eq i32 %174, 0
  br i1 %175, label %nestedBlock70, label %afterNestedBlock53

nestedBlock70:                                    ; preds = %checkContinueBlock69
  %posX212 = load [10000 x i32], ptr %posX, align 4
  br i1 true, label %"GlobalIndexExpr::then213", label %"GlobalIndexExpr::else214"

checkContinueBlock71:                             ; preds = %"GlobalIndexExpr::merge215"
  %176 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %177 = icmp eq i32 %176, 0
  br i1 %177, label %nestedBlock72, label %afterNestedBlock53

nestedBlock72:                                    ; preds = %checkContinueBlock71
  %posY217 = load [10000 x i32], ptr %posY, align 4
  br i1 true, label %"GlobalIndexExpr::then218", label %"GlobalIndexExpr::else219"

checkContinueBlock73:                             ; preds = %"GlobalIndexExpr::merge220"
  %178 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %179 = icmp eq i32 %178, 0
  br i1 %179, label %nestedBlock74, label %afterNestedBlock53

nestedBlock74:                                    ; preds = %checkContinueBlock73
  call void @BeginDrawing()
  %180 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %181 = icmp eq i32 %180, 0
  br i1 %181, label %checkContinueBlock75, label %afterNestedBlock53

checkContinueBlock75:                             ; preds = %nestedBlock74
  %182 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %183 = icmp eq i32 %182, 0
  br i1 %183, label %nestedBlock76, label %afterNestedBlock53

nestedBlock76:                                    ; preds = %checkContinueBlock75
  %WHITE = load i32, ptr @WHITE, align 4
  %184 = load i32, ptr @WHITE, align 4
  call void @ClearBackground(i32 %184)
  %185 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %186 = icmp eq i32 %185, 0
  br i1 %186, label %checkContinueBlock77, label %afterNestedBlock53

checkContinueBlock77:                             ; preds = %nestedBlock76
  %187 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %188 = icmp eq i32 %187, 0
  br i1 %188, label %nestedBlock78, label %afterNestedBlock53

nestedBlock78:                                    ; preds = %checkContinueBlock77
  %tail222 = load i32, ptr %tail, align 4
  %189 = sub i32 %tail222, 1
  %index223 = alloca i32, align 4
  store i32 0, ptr %index223, align 4
  store i32 0, ptr %index223, align 4
  br label %"ForLoop::loopCondition224"

checkContinueBlock79:                             ; preds = %end_block255
  %190 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %191 = icmp eq i32 %190, 0
  br i1 %191, label %nestedBlock80, label %afterNestedBlock53

nestedBlock80:                                    ; preds = %checkContinueBlock79
  %screenWidth256 = load i32, ptr @screenWidth, align 4
  br i1 false, label %if, label %else257

checkContinueBlock81:                             ; preds = %merge
  %192 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %193 = icmp eq i32 %192, 0
  br i1 %193, label %nestedBlock82, label %afterNestedBlock53

nestedBlock82:                                    ; preds = %checkContinueBlock81
  %194 = getelementptr inbounds %Position.0, ptr %foodPos, i32 0, i32 0
  %x258 = load i32, ptr %194, align 4
  %195 = load i32, ptr %194, align 4
  %196 = getelementptr inbounds %Position.0, ptr %foodPos, i32 0, i32 1
  %y259 = load i32, ptr %196, align 4
  %197 = load i32, ptr %196, align 4
  %side260 = load i32, ptr @side, align 4
  %198 = load i32, ptr @side, align 4
  %side261 = load i32, ptr @side, align 4
  %199 = load i32, ptr @side, align 4
  %GREEN = load i32, ptr @GREEN, align 4
  %200 = load i32, ptr @GREEN, align 4
  call void @DrawRectangle(i32 %195, i32 %197, i32 %198, i32 %199, i32 %200)
  %201 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %202 = icmp eq i32 %201, 0
  br i1 %202, label %checkContinueBlock83, label %afterNestedBlock53

checkContinueBlock83:                             ; preds = %nestedBlock82
  %203 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %204 = icmp eq i32 %203, 0
  br i1 %204, label %nestedBlock84, label %afterNestedBlock53

nestedBlock84:                                    ; preds = %checkContinueBlock83
  call void @EndDrawing()
  %205 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %206 = icmp eq i32 %205, 0
  br i1 %206, label %checkContinueBlock85, label %afterNestedBlock53

checkContinueBlock85:                             ; preds = %nestedBlock84
  br label %afterNestedBlock53

then:                                             ; preds = %nestedBlock56
  br label %nestedBlock91

orIf0:                                            ; preds = %nestedBlock56
  %KEY_DOWN = load i32, ptr @KEY_DOWN, align 4
  %207 = load i32, ptr @KEY_DOWN, align 4
  %208 = call i1 @IsKeyPressed(i32 %207)
  %KEY_DOWN87 = load i32, ptr @KEY_DOWN, align 4
  %209 = load i32, ptr @KEY_DOWN, align 4
  %210 = call i1 @IsKeyDown(i32 %209)
  %211 = select i1 %208, i1 true, i1 %210
  br i1 %211, label %orIfThen0, label %orIf1

orIf1:                                            ; preds = %orIf0
  %KEY_RIGHT = load i32, ptr @KEY_RIGHT, align 4
  %212 = load i32, ptr @KEY_RIGHT, align 4
  %213 = call i1 @IsKeyPressed(i32 %212)
  %KEY_RIGHT88 = load i32, ptr @KEY_RIGHT, align 4
  %214 = load i32, ptr @KEY_RIGHT, align 4
  %215 = call i1 @IsKeyDown(i32 %214)
  %216 = select i1 %213, i1 true, i1 %215
  br i1 %216, label %orIfThen1, label %orIf2

orIf2:                                            ; preds = %orIf1
  %KEY_LEFT = load i32, ptr @KEY_LEFT, align 4
  %217 = load i32, ptr @KEY_LEFT, align 4
  %218 = call i1 @IsKeyPressed(i32 %217)
  %KEY_LEFT89 = load i32, ptr @KEY_LEFT, align 4
  %219 = load i32, ptr @KEY_LEFT, align 4
  %220 = call i1 @IsKeyDown(i32 %219)
  %221 = select i1 %218, i1 true, i1 %220
  br i1 %221, label %orIfThen2, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock97

orIfThen1:                                        ; preds = %orIf1
  br label %nestedBlock104

orIfThen2:                                        ; preds = %orIf2
  br label %nestedBlock110

else:                                             ; preds = %orIf2
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock109, %afterNestedBlock103, %afterNestedBlock96, %afterNestedBlock90
  %222 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %223 = icmp eq i32 %222, 0
  br i1 %223, label %checkContinueBlock57, label %afterNestedBlock53

afterNestedBlock90:                               ; preds = %checkContinueBlock94, %nestedBlock93, %checkContinueBlock92, %nestedBlock91
  br label %afterIfElse

nestedBlock91:                                    ; preds = %then
  %224 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %225 = load i1, ptr %224, align 1
  %226 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %226, align 1
  %227 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %228 = icmp eq i32 %227, 0
  br i1 %228, label %checkContinueBlock92, label %afterNestedBlock90

checkContinueBlock92:                             ; preds = %nestedBlock91
  %229 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %230 = icmp eq i32 %229, 0
  br i1 %230, label %nestedBlock93, label %afterNestedBlock90

nestedBlock93:                                    ; preds = %checkContinueBlock92
  %231 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y = load i32, ptr %231, align 4
  %232 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y95 = load i32, ptr %232, align 4
  %233 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %234 = load i32, ptr %233, align 4
  %235 = sub i32 %y95, %234
  store i32 %235, ptr %231, align 4
  %236 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %237 = icmp eq i32 %236, 0
  br i1 %237, label %checkContinueBlock94, label %afterNestedBlock90

checkContinueBlock94:                             ; preds = %nestedBlock93
  br label %afterNestedBlock90

afterNestedBlock96:                               ; preds = %checkContinueBlock100, %nestedBlock99, %checkContinueBlock98, %nestedBlock97
  br label %afterIfElse

nestedBlock97:                                    ; preds = %orIfThen0
  %238 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %239 = load i1, ptr %238, align 1
  %240 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %240, align 1
  %241 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %242 = icmp eq i32 %241, 0
  br i1 %242, label %checkContinueBlock98, label %afterNestedBlock96

checkContinueBlock98:                             ; preds = %nestedBlock97
  %243 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %244 = icmp eq i32 %243, 0
  br i1 %244, label %nestedBlock99, label %afterNestedBlock96

nestedBlock99:                                    ; preds = %checkContinueBlock98
  %245 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y101 = load i32, ptr %245, align 4
  %246 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y102 = load i32, ptr %246, align 4
  %247 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %248 = load i32, ptr %247, align 4
  %249 = add i32 %y102, %248
  store i32 %249, ptr %245, align 4
  %250 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %251 = icmp eq i32 %250, 0
  br i1 %251, label %checkContinueBlock100, label %afterNestedBlock96

checkContinueBlock100:                            ; preds = %nestedBlock99
  br label %afterNestedBlock96

afterNestedBlock103:                              ; preds = %checkContinueBlock107, %nestedBlock106, %checkContinueBlock105, %nestedBlock104
  br label %afterIfElse

nestedBlock104:                                   ; preds = %orIfThen1
  %252 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %253 = load i1, ptr %252, align 1
  %254 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %254, align 1
  %255 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %256 = icmp eq i32 %255, 0
  br i1 %256, label %checkContinueBlock105, label %afterNestedBlock103

checkContinueBlock105:                            ; preds = %nestedBlock104
  %257 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %258 = icmp eq i32 %257, 0
  br i1 %258, label %nestedBlock106, label %afterNestedBlock103

nestedBlock106:                                   ; preds = %checkContinueBlock105
  %259 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x = load i32, ptr %259, align 4
  %260 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x108 = load i32, ptr %260, align 4
  %261 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %262 = load i32, ptr %261, align 4
  %263 = add i32 %x108, %262
  store i32 %263, ptr %259, align 4
  %264 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %265 = icmp eq i32 %264, 0
  br i1 %265, label %checkContinueBlock107, label %afterNestedBlock103

checkContinueBlock107:                            ; preds = %nestedBlock106
  br label %afterNestedBlock103

afterNestedBlock109:                              ; preds = %checkContinueBlock113, %nestedBlock112, %checkContinueBlock111, %nestedBlock110
  br label %afterIfElse

nestedBlock110:                                   ; preds = %orIfThen2
  %266 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  %267 = load i1, ptr %266, align 1
  %268 = getelementptr inbounds %DynamicType, ptr %isKeyPressed, i32 0, i32 2
  store i1 true, ptr %268, align 1
  %269 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %270 = icmp eq i32 %269, 0
  br i1 %270, label %checkContinueBlock111, label %afterNestedBlock109

checkContinueBlock111:                            ; preds = %nestedBlock110
  %271 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %272 = icmp eq i32 %271, 0
  br i1 %272, label %nestedBlock112, label %afterNestedBlock109

nestedBlock112:                                   ; preds = %checkContinueBlock111
  %273 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x114 = load i32, ptr %273, align 4
  %274 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x115 = load i32, ptr %274, align 4
  %275 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %276 = load i32, ptr %275, align 4
  %277 = sub i32 %x115, %276
  store i32 %277, ptr %273, align 4
  %278 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %279 = icmp eq i32 %278, 0
  br i1 %279, label %checkContinueBlock113, label %afterNestedBlock109

checkContinueBlock113:                            ; preds = %nestedBlock112
  br label %afterNestedBlock109

then117:                                          ; preds = %nestedBlock58
  br label %nestedBlock121

else118:                                          ; preds = %nestedBlock58
  br label %afterIfElse119

afterIfElse119:                                   ; preds = %else118, %afterNestedBlock120
  %280 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %281 = icmp eq i32 %280, 0
  br i1 %281, label %checkContinueBlock59, label %afterNestedBlock53

afterNestedBlock120:                              ; preds = %checkContinueBlock122, %nestedBlock121
  br label %afterIfElse119

nestedBlock121:                                   ; preds = %then117
  %282 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x123 = load i32, ptr %282, align 4
  store i32 0, ptr %282, align 4
  %283 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %284 = icmp eq i32 %283, 0
  br i1 %284, label %checkContinueBlock122, label %afterNestedBlock120

checkContinueBlock122:                            ; preds = %nestedBlock121
  br label %afterNestedBlock120

then126:                                          ; preds = %nestedBlock60
  br label %nestedBlock130

else127:                                          ; preds = %nestedBlock60
  br label %afterIfElse128

afterIfElse128:                                   ; preds = %else127, %afterNestedBlock129
  %285 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %286 = icmp eq i32 %285, 0
  br i1 %286, label %checkContinueBlock61, label %afterNestedBlock53

afterNestedBlock129:                              ; preds = %checkContinueBlock131, %nestedBlock130
  br label %afterIfElse128

nestedBlock130:                                   ; preds = %then126
  %287 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x132 = load i32, ptr %287, align 4
  %screenWidth133 = load i32, ptr @screenWidth, align 4
  %288 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %289 = load i32, ptr %288, align 4
  %290 = sub i32 %screenWidth133, %289
  store i32 %290, ptr %287, align 4
  %291 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %292 = icmp eq i32 %291, 0
  br i1 %292, label %checkContinueBlock131, label %afterNestedBlock129

checkContinueBlock131:                            ; preds = %nestedBlock130
  br label %afterNestedBlock129

then135:                                          ; preds = %nestedBlock62
  br label %nestedBlock139

else136:                                          ; preds = %nestedBlock62
  br label %afterIfElse137

afterIfElse137:                                   ; preds = %else136, %afterNestedBlock138
  %293 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %294 = icmp eq i32 %293, 0
  br i1 %294, label %checkContinueBlock63, label %afterNestedBlock53

afterNestedBlock138:                              ; preds = %checkContinueBlock140, %nestedBlock139
  br label %afterIfElse137

nestedBlock139:                                   ; preds = %then135
  %295 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y141 = load i32, ptr %295, align 4
  store i32 0, ptr %295, align 4
  %296 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %297 = icmp eq i32 %296, 0
  br i1 %297, label %checkContinueBlock140, label %afterNestedBlock138

checkContinueBlock140:                            ; preds = %nestedBlock139
  br label %afterNestedBlock138

then144:                                          ; preds = %nestedBlock64
  br label %nestedBlock148

else145:                                          ; preds = %nestedBlock64
  br label %afterIfElse146

afterIfElse146:                                   ; preds = %else145, %afterNestedBlock147
  %298 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %299 = icmp eq i32 %298, 0
  br i1 %299, label %checkContinueBlock65, label %afterNestedBlock53

afterNestedBlock147:                              ; preds = %checkContinueBlock149, %nestedBlock148
  br label %afterIfElse146

nestedBlock148:                                   ; preds = %then144
  %300 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y150 = load i32, ptr %300, align 4
  %screenHeight151 = load i32, ptr @screenHeight, align 4
  %301 = getelementptr inbounds %DynamicType, ptr %speed, i32 0, i32 0
  %302 = load i32, ptr %301, align 4
  %303 = sub i32 %screenHeight151, %302
  store i32 %303, ptr %300, align 4
  %304 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %305 = icmp eq i32 %304, 0
  br i1 %305, label %checkContinueBlock149, label %afterNestedBlock147

checkContinueBlock149:                            ; preds = %nestedBlock148
  br label %afterNestedBlock147

then156:                                          ; preds = %nestedBlock66
  br label %nestedBlock160

else157:                                          ; preds = %nestedBlock66
  br label %afterIfElse158

afterIfElse158:                                   ; preds = %else157, %afterNestedBlock159
  %306 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %307 = icmp eq i32 %306, 0
  br i1 %307, label %checkContinueBlock67, label %afterNestedBlock53

afterNestedBlock159:                              ; preds = %checkContinueBlock163, %nestedBlock162, %checkContinueBlock161, %nestedBlock160
  br label %afterIfElse158

nestedBlock160:                                   ; preds = %then156
  %308 = call ptr @getFoodPosition()
  %309 = load %Position.0, ptr %308, align 4
  store %Position.0 %309, ptr %foodPos, align 4
  %310 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %311 = icmp eq i32 %310, 0
  br i1 %311, label %checkContinueBlock161, label %afterNestedBlock159

checkContinueBlock161:                            ; preds = %nestedBlock160
  %312 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %313 = icmp eq i32 %312, 0
  br i1 %313, label %nestedBlock162, label %afterNestedBlock159

nestedBlock162:                                   ; preds = %checkContinueBlock161
  %tail164 = load i32, ptr %tail, align 4
  %tail165 = load i32, ptr %tail, align 4
  %314 = add i32 %tail165, 1
  store i32 %314, ptr %tail, align 4
  %315 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %316 = icmp eq i32 %315, 0
  br i1 %316, label %checkContinueBlock163, label %afterNestedBlock159

checkContinueBlock163:                            ; preds = %nestedBlock162
  br label %afterNestedBlock159

then166:                                          ; preds = %nestedBlock68
  br label %nestedBlock170

else167:                                          ; preds = %nestedBlock68
  br label %afterIfElse168

afterIfElse168:                                   ; preds = %else167, %afterNestedBlock169
  %317 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %318 = icmp eq i32 %317, 0
  br i1 %318, label %checkContinueBlock69, label %afterNestedBlock53

afterNestedBlock169:                              ; preds = %checkContinueBlock171, %end_block211
  br label %afterIfElse168

nestedBlock170:                                   ; preds = %then166
  %tail172 = load i32, ptr %tail, align 4
  %319 = sub i32 %tail172, 1
  %index = alloca i32, align 4
  store i32 0, ptr %index, align 4
  store i32 %319, ptr %index, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock171:                            ; preds = %end_block211
  br label %afterNestedBlock169

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock176, %nestedBlock170
  %320 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %321 = icmp eq i32 %320, 0
  br i1 %321, label %end_block174, label %decrement_block173

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock177

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %322 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %323 = icmp eq i32 %322, 0
  br i1 %323, label %end_block211, label %decrement_block210

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %324 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %325 = icmp eq i32 %324, 0
  br i1 %325, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block173:                               ; preds = %"ForLoop::loopCondition"
  %326 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %327 = sub i32 %326, 1
  store i32 %327, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block174

end_block174:                                     ; preds = %decrement_block173, %"ForLoop::loopCondition"
  %index175 = load i32, ptr %index, align 4
  br i1 true, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block174
  %328 = icmp sge i32 %index175, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block174
  %329 = icmp sle i32 %index175, 1
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %330 = phi i1 [ %328, %"ForLoop::Conditon::trueBlock" ], [ %329, %"ForLoop::Conditon::falseBlock" ]
  br i1 %330, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock176:                              ; preds = %checkContinueBlock180, %"GlobalIndexExpr::merge206", %checkContinueBlock178, %"GlobalIndexExpr::merge190"
  %331 = add i32 %index175, -1
  store i32 %331, ptr %index, align 4
  br label %"ForLoop::loopCondition"

nestedBlock177:                                   ; preds = %"ForLoop::loopBody"
  %index181 = load i32, ptr %index, align 4
  %posX182 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %index181, 10000
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %index181, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then183", label %"GlobalIndexExpr::else184"

checkContinueBlock178:                            ; preds = %"GlobalIndexExpr::merge190"
  %332 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %333 = icmp eq i32 %332, 0
  br i1 %333, label %nestedBlock179, label %afterNestedBlock176

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
  call void @raise_exception(ptr @6)
  br label %"GlobalIndexExpr::merge185"

"GlobalIndexExpr::merge185":                      ; preds = %"GlobalIndexExpr::else184", %"GlobalIndexExpr::then183"
  %334 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index181
  %335 = load i32, ptr %334, align 4
  %index186 = load i32, ptr %index, align 4
  %336 = sub i32 %index186, 1
  %posX187 = load [10000 x i32], ptr %posX, align 4
  %"GlobalIndexExpr::isLessThan191" = icmp slt i32 %336, 10000
  %"GlobalIndexExpr::isGreaterThan192" = icmp sge i32 %336, 0
  %"GlobalIndexExpr::isWithinBounds193" = and i1 %"GlobalIndexExpr::isLessThan191", %"GlobalIndexExpr::isGreaterThan192"
  br i1 %"GlobalIndexExpr::isWithinBounds193", label %"GlobalIndexExpr::then188", label %"GlobalIndexExpr::else189"

"GlobalIndexExpr::then188":                       ; preds = %"GlobalIndexExpr::merge185"
  br label %"GlobalIndexExpr::merge190"

"GlobalIndexExpr::else189":                       ; preds = %"GlobalIndexExpr::merge185"
  call void @raise_exception(ptr @7)
  br label %"GlobalIndexExpr::merge190"

"GlobalIndexExpr::merge190":                      ; preds = %"GlobalIndexExpr::else189", %"GlobalIndexExpr::then188"
  %337 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %336
  %338 = load i32, ptr %337, align 4
  %339 = load i32, ptr %337, align 4
  store i32 %339, ptr %334, align 4
  %340 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %341 = icmp eq i32 %340, 0
  br i1 %341, label %checkContinueBlock178, label %afterNestedBlock176

"GlobalIndexExpr::then196":                       ; preds = %nestedBlock179
  br label %"GlobalIndexExpr::merge198"

"GlobalIndexExpr::else197":                       ; preds = %nestedBlock179
  call void @raise_exception(ptr @8)
  br label %"GlobalIndexExpr::merge198"

"GlobalIndexExpr::merge198":                      ; preds = %"GlobalIndexExpr::else197", %"GlobalIndexExpr::then196"
  %342 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index194
  %343 = load i32, ptr %342, align 4
  %index202 = load i32, ptr %index, align 4
  %344 = sub i32 %index202, 1
  %posY203 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan207" = icmp slt i32 %344, 10000
  %"GlobalIndexExpr::isGreaterThan208" = icmp sge i32 %344, 0
  %"GlobalIndexExpr::isWithinBounds209" = and i1 %"GlobalIndexExpr::isLessThan207", %"GlobalIndexExpr::isGreaterThan208"
  br i1 %"GlobalIndexExpr::isWithinBounds209", label %"GlobalIndexExpr::then204", label %"GlobalIndexExpr::else205"

"GlobalIndexExpr::then204":                       ; preds = %"GlobalIndexExpr::merge198"
  br label %"GlobalIndexExpr::merge206"

"GlobalIndexExpr::else205":                       ; preds = %"GlobalIndexExpr::merge198"
  call void @raise_exception(ptr @9)
  br label %"GlobalIndexExpr::merge206"

"GlobalIndexExpr::merge206":                      ; preds = %"GlobalIndexExpr::else205", %"GlobalIndexExpr::then204"
  %345 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %344
  %346 = load i32, ptr %345, align 4
  %347 = load i32, ptr %345, align 4
  store i32 %347, ptr %342, align 4
  %348 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %349 = icmp eq i32 %348, 0
  br i1 %349, label %checkContinueBlock180, label %afterNestedBlock176

decrement_block210:                               ; preds = %"ForLoop::afterLoop"
  %350 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %351 = sub i32 %350, 1
  store i32 %351, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block211

end_block211:                                     ; preds = %decrement_block210, %"ForLoop::afterLoop"
  %352 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %353 = icmp eq i32 %352, 0
  br i1 %353, label %checkContinueBlock171, label %afterNestedBlock169

"GlobalIndexExpr::then213":                       ; preds = %nestedBlock70
  br label %"GlobalIndexExpr::merge215"

"GlobalIndexExpr::else214":                       ; preds = %nestedBlock70
  call void @raise_exception(ptr @10)
  br label %"GlobalIndexExpr::merge215"

"GlobalIndexExpr::merge215":                      ; preds = %"GlobalIndexExpr::else214", %"GlobalIndexExpr::then213"
  %354 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 0
  %355 = load i32, ptr %354, align 4
  %356 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 0
  %x216 = load i32, ptr %356, align 4
  %357 = load i32, ptr %356, align 4
  store i32 %357, ptr %354, align 4
  %358 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %359 = icmp eq i32 %358, 0
  br i1 %359, label %checkContinueBlock71, label %afterNestedBlock53

"GlobalIndexExpr::then218":                       ; preds = %nestedBlock72
  br label %"GlobalIndexExpr::merge220"

"GlobalIndexExpr::else219":                       ; preds = %nestedBlock72
  call void @raise_exception(ptr @11)
  br label %"GlobalIndexExpr::merge220"

"GlobalIndexExpr::merge220":                      ; preds = %"GlobalIndexExpr::else219", %"GlobalIndexExpr::then218"
  %360 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 0
  %361 = load i32, ptr %360, align 4
  %362 = getelementptr inbounds %Position.0, ptr %newPos, i32 0, i32 1
  %y221 = load i32, ptr %362, align 4
  %363 = load i32, ptr %362, align 4
  store i32 %363, ptr %360, align 4
  %364 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %365 = icmp eq i32 %364, 0
  br i1 %365, label %checkContinueBlock73, label %afterNestedBlock53

"ForLoop::loopCondition224":                      ; preds = %afterNestedBlock234, %nestedBlock78
  %366 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %367 = icmp eq i32 %366, 0
  br i1 %367, label %end_block229, label %decrement_block228

"ForLoop::loopBody225":                           ; preds = %"ForLoop::breakLoop227"
  br label %nestedBlock235

"ForLoop::afterLoop226":                          ; preds = %"ForLoop::breakLoop227", %"ForLoop::Conditon::mergeBlock233"
  %368 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %369 = icmp eq i32 %368, 0
  br i1 %369, label %end_block255, label %decrement_block254

"ForLoop::breakLoop227":                          ; preds = %"ForLoop::Conditon::mergeBlock233"
  %370 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %371 = icmp eq i32 %370, 0
  br i1 %371, label %"ForLoop::loopBody225", label %"ForLoop::afterLoop226"

decrement_block228:                               ; preds = %"ForLoop::loopCondition224"
  %372 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %373 = sub i32 %372, 1
  store i32 %373, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block229

end_block229:                                     ; preds = %decrement_block228, %"ForLoop::loopCondition224"
  %index230 = load i32, ptr %index223, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock231", label %"ForLoop::Conditon::falseBlock232"

"ForLoop::Conditon::trueBlock231":                ; preds = %end_block229
  %374 = icmp sge i32 %index230, %189
  br label %"ForLoop::Conditon::mergeBlock233"

"ForLoop::Conditon::falseBlock232":               ; preds = %end_block229
  %375 = icmp sle i32 %index230, %189
  br label %"ForLoop::Conditon::mergeBlock233"

"ForLoop::Conditon::mergeBlock233":               ; preds = %"ForLoop::Conditon::falseBlock232", %"ForLoop::Conditon::trueBlock231"
  %376 = phi i1 [ %374, %"ForLoop::Conditon::trueBlock231" ], [ %375, %"ForLoop::Conditon::falseBlock232" ]
  br i1 %376, label %"ForLoop::breakLoop227", label %"ForLoop::afterLoop226"

afterNestedBlock234:                              ; preds = %checkContinueBlock236, %"GlobalIndexExpr::merge249"
  %377 = add i32 %index230, 1
  store i32 %377, ptr %index223, align 4
  br label %"ForLoop::loopCondition224"

nestedBlock235:                                   ; preds = %"ForLoop::loopBody225"
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
  call void @raise_exception(ptr @12)
  br label %"GlobalIndexExpr::merge241"

"GlobalIndexExpr::merge241":                      ; preds = %"GlobalIndexExpr::else240", %"GlobalIndexExpr::then239"
  %378 = getelementptr [10000 x i32], ptr %posX, i32 0, i32 %index237
  %379 = load i32, ptr %378, align 4
  %index245 = load i32, ptr %index223, align 4
  %posY246 = load [10000 x i32], ptr %posY, align 4
  %"GlobalIndexExpr::isLessThan250" = icmp slt i32 %index245, 10000
  %"GlobalIndexExpr::isGreaterThan251" = icmp sge i32 %index245, 0
  %"GlobalIndexExpr::isWithinBounds252" = and i1 %"GlobalIndexExpr::isLessThan250", %"GlobalIndexExpr::isGreaterThan251"
  br i1 %"GlobalIndexExpr::isWithinBounds252", label %"GlobalIndexExpr::then247", label %"GlobalIndexExpr::else248"

"GlobalIndexExpr::then247":                       ; preds = %"GlobalIndexExpr::merge241"
  br label %"GlobalIndexExpr::merge249"

"GlobalIndexExpr::else248":                       ; preds = %"GlobalIndexExpr::merge241"
  call void @raise_exception(ptr @13)
  br label %"GlobalIndexExpr::merge249"

"GlobalIndexExpr::merge249":                      ; preds = %"GlobalIndexExpr::else248", %"GlobalIndexExpr::then247"
  %380 = getelementptr [10000 x i32], ptr %posY, i32 0, i32 %index245
  %381 = load i32, ptr %380, align 4
  %side = load i32, ptr @side, align 4
  %382 = load i32, ptr @side, align 4
  %side253 = load i32, ptr @side, align 4
  %383 = load i32, ptr @side, align 4
  %BLUE = load i32, ptr @BLUE, align 4
  %384 = load i32, ptr @BLUE, align 4
  call void @DrawRectangle(ptr %378, ptr %380, i32 %382, i32 %383, i32 %384)
  %385 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %386 = icmp eq i32 %385, 0
  br i1 %386, label %checkContinueBlock236, label %afterNestedBlock234

decrement_block254:                               ; preds = %"ForLoop::afterLoop226"
  %387 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %388 = sub i32 %387, 1
  store i32 %388, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block255

end_block255:                                     ; preds = %decrement_block254, %"ForLoop::afterLoop226"
  %389 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %390 = icmp eq i32 %389, 0
  br i1 %390, label %checkContinueBlock79, label %afterNestedBlock53

if:                                               ; preds = %nestedBlock80
  call void @raise_exception(ptr @14)
  br label %merge

else257:                                          ; preds = %nestedBlock80
  %391 = sdiv i32 %screenWidth256, 5
  br label %merge

merge:                                            ; preds = %else257, %if
  %DARKBLUE = load i32, ptr @DARKBLUE, align 4
  %392 = load i32, ptr @DARKBLUE, align 4
  call void @DrawCircle(i32 %391, i32 120, float 3.500000e+01, i32 %392)
  %393 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %394 = icmp eq i32 %393, 0
  br i1 %394, label %checkContinueBlock81, label %afterNestedBlock53

decrement_block262:                               ; preds = %while.end
  %395 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %396 = sub i32 %395, 1
  store i32 %396, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block263

end_block263:                                     ; preds = %decrement_block262, %while.end
  %397 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %398 = icmp eq i32 %397, 0
  br i1 %398, label %checkContinueBlock20, label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock23
  ret i32 0

mergeBlock:                                       ; No predecessors!
  %399 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %400 = icmp eq i32 %399, 0
  br i1 %400, label %checkContinueBlock24, label %afterNestedBlock
}

!0 = !{!"srand:rt:pr:27"}
!1 = !{!"rand:rt:pr:28"}
!2 = !{!"getRandomNumber:rt:pr:28"}
!3 = !{!"IsKeyDown:rt:pr:34"}
!4 = !{!"DrawText:rt:pr:27"}
!5 = !{!"GetScreenHeight:rt:pr:28"}
!6 = !{!"CloseWindow:rt:pr:27"}
!7 = !{!"EndDrawing:rt:pr:27"}
!8 = !{!"IsKeyPressed:rt:pr:34"}
!9 = !{!"COLOR:rt:pr:28"}
!10 = !{!"BeginDrawing:rt:pr:27"}
!11 = !{!"time:rt:pr:28"}
!12 = !{!"TextFormat:rt:pr:33"}
!13 = !{!"DrawCircle:rt:pr:27"}
!14 = !{!"WindowShouldClose:rt:pr:34"}
!15 = !{!"DrawRectangle:rt:pr:27"}
!16 = !{!"SetTargetFPS:rt:pr:27"}
!17 = !{!"InitWindow:rt:pr:27"}
!18 = !{!"GetScreenWidth:rt:pr:28"}
!19 = !{!"ClearBackground:rt:pr:27"}
!20 = !{!"getN:rt:pr:28"}
!21 = !{!"getFoodPosition:rt:ob:Position"}
!22 = !{!"main:rt:pr:28"}
