; ModuleID = '-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib'
source_filename = "-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%Texture.0 = type { i32, i32, i32, i32, i32 }

@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib_FLOWWING_GLOBAL_NULL = external global i8
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib_FLOWWING_BREAK_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib_FLOWWING_CONTINUE_COUNT = global i32 0
@-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0

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

define i32 @-Users-apple-code-per-Flow-Wing-docs-demo-bird-game-flow-wing-raylib(i32 %0, ptr %1) {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 void @InitWindow(i32, i32, ptr)

declare !rt !1 void @SetTargetFPS(i32)

declare !rt !2 void @ClearBackground(i32)

declare !rt !3 i1 @WindowShouldClose()

declare !rt !4 void @BeginDrawing()

declare !rt !5 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !6 void @DrawRectangleLines(i32, i32, i32, i32, i32)

declare !rt !7 void @EndDrawing()

declare !rt !8 void @CloseWindow()

declare !rt !9 i32 @GetScreenHeight()

declare !rt !10 i32 @GetScreenWidth()

declare !rt !11 i32 @GetMouseX()

declare !rt !12 i32 @GetMouseY()

declare !rt !13 void @DrawCircle(i32, i32, float, i32)

declare !rt !14 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !15 i32 @MeasureText(ptr, i32)

declare !rt !16 i1 @IsKeyPressed(i32)

declare !rt !17 i1 @IsKeyDown(i32)

declare !rt !18 ptr @TextFormat(ptr)

declare !rt !19 void @LoadTexture(ptr sret(%Texture.0), ptr)

declare !rt !20 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !21 void @UnloadTexture(ptr)

declare !rt !22 void @DrawRectangleLinesEx(ptr, float, i32)

declare !rt !23 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !24 void @TraceLog(i32, ptr)

declare !rt !25 double @GetTime()

declare !rt !26 float @GetFrameTime()

!0 = !{!"InitWindow:rt:pr:27"}
!1 = !{!"SetTargetFPS:rt:pr:27"}
!2 = !{!"ClearBackground:rt:pr:27"}
!3 = !{!"WindowShouldClose:rt:pr:34"}
!4 = !{!"BeginDrawing:rt:pr:27"}
!5 = !{!"DrawRectangle:rt:pr:27"}
!6 = !{!"DrawRectangleLines:rt:pr:27"}
!7 = !{!"EndDrawing:rt:pr:27"}
!8 = !{!"CloseWindow:rt:pr:27"}
!9 = !{!"GetScreenHeight:rt:pr:28"}
!10 = !{!"GetScreenWidth:rt:pr:28"}
!11 = !{!"GetMouseX:rt:pr:28"}
!12 = !{!"GetMouseY:rt:pr:28"}
!13 = !{!"DrawCircle:rt:pr:27"}
!14 = !{!"DrawText:rt:pr:27"}
!15 = !{!"MeasureText:rt:pr:28"}
!16 = !{!"IsKeyPressed:rt:pr:34"}
!17 = !{!"IsKeyDown:rt:pr:34"}
!18 = !{!"TextFormat:rt:pr:33"}
!19 = !{!"LoadTexture:rt:ob:Texture.0"}
!20 = !{!"DrawTexture:rt:pr:27"}
!21 = !{!"UnloadTexture:rt:pr:27"}
!22 = !{!"DrawRectangleLinesEx:rt:pr:27"}
!23 = !{!"DrawTexturePro:rt:pr:27"}
!24 = !{!"TraceLog:rt:pr:27"}
!25 = !{!"GetTime:rt:pr:31"}
!26 = !{!"GetFrameTime:rt:pr:32"}
