; ModuleID = 'iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib'
source_filename = "iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib"
target triple = "x86_64-apple-macosx14.0.0"

%Texture.0 = type { i32, i32, i32, i32, i32 }

@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_GLOBAL_NULL = external global i8
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_BREAK_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_CONTINUE_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0

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

define i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib() {
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

declare !rt !6 void @EndDrawing()

declare !rt !7 void @CloseWindow()

declare !rt !8 i32 @GetScreenHeight()

declare !rt !9 i32 @GetScreenWidth()

declare !rt !10 void @DrawCircle(i32, i32, float, i32)

declare !rt !11 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !12 i1 @IsKeyPressed(i32)

declare !rt !13 i1 @IsKeyDown(i32)

declare !rt !14 ptr @TextFormat(ptr)

declare !rt !15 void @LoadTexture(ptr sret(%Texture.0), ptr)

declare !rt !16 void @DrawTexture(ptr, i32, i32, i32)

declare !rt !17 void @UnloadTexture(ptr)

declare !rt !18 void @DrawTexturePro(ptr, [4 x float], [4 x float], [2 x float], float, i32)

declare !rt !19 void @TraceLog(i32, ptr)

declare !rt !20 double @GetTime()

declare !rt !21 float @GetFrameTime()

declare !rt !22 i32 @rand()

declare !rt !23 i32 @time()

declare !rt !24 void @srand(i32)

define void @getRandomNumber(ptr %0, ptr %1, ptr %2) !rt !25 {
entry:
  %start = alloca i32, align 4
  %3 = load i32, ptr %1, align 4
  store i32 %3, ptr %start, align 4
  %end = alloca i32, align 4
  %4 = load i32, ptr %2, align 4
  store i32 %4, ptr %end, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %5 = call i32 @rand()
  %end1 = load i32, ptr %end, align 4
  %6 = load i32, ptr %end, align 4
  %start2 = load i32, ptr %start, align 4
  %7 = load i32, ptr %start, align 4
  %8 = sub i32 %6, %7
  %9 = add i32 %8, 1
  %10 = srem i32 %5, %9
  %start3 = load i32, ptr %start, align 4
  %11 = load i32, ptr %start, align 4
  %12 = add i32 %10, %11
  store i32 %12, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %13 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameiflow-wing-raylib_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"InitWindow:rt:pr:27"}
!1 = !{!"SetTargetFPS:rt:pr:27"}
!2 = !{!"ClearBackground:rt:pr:27"}
!3 = !{!"WindowShouldClose:rt:pr:34"}
!4 = !{!"BeginDrawing:rt:pr:27"}
!5 = !{!"DrawRectangle:rt:pr:27"}
!6 = !{!"EndDrawing:rt:pr:27"}
!7 = !{!"CloseWindow:rt:pr:27"}
!8 = !{!"GetScreenHeight:rt:pr:28"}
!9 = !{!"GetScreenWidth:rt:pr:28"}
!10 = !{!"DrawCircle:rt:pr:27"}
!11 = !{!"DrawText:rt:pr:27"}
!12 = !{!"IsKeyPressed:rt:pr:34"}
!13 = !{!"IsKeyDown:rt:pr:34"}
!14 = !{!"TextFormat:rt:pr:33"}
!15 = !{!"LoadTexture:rt:ob:Texture.0"}
!16 = !{!"DrawTexture:rt:pr:27"}
!17 = !{!"UnloadTexture:rt:pr:27"}
!18 = !{!"DrawTexturePro:rt:pr:27"}
!19 = !{!"TraceLog:rt:pr:27"}
!20 = !{!"GetTime:rt:pr:31"}
!21 = !{!"GetFrameTime:rt:pr:32"}
!22 = !{!"rand:rt:pr:28"}
!23 = !{!"time:rt:pr:28"}
!24 = !{!"srand:rt:pr:27"}
!25 = !{!"getRandomNumber:rt:pr:28"}
