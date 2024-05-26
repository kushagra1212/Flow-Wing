; ModuleID = 'iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib'
source_filename = "iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib"

@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_GLOBAL_NULL = external global i8
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_BREAK_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_CONTINUE_COUNT = global i32 0
@iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0

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

define i32 @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib() {
entry:
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define i32 @COLOR(ptr %0, ptr %1, ptr %2, ptr %3) !rt !0 {
entry:
  %r = alloca i32, align 4
  %4 = load i32, ptr %0, align 4
  store i32 %4, ptr %r, align 4
  %g = alloca i32, align 4
  %5 = load i32, ptr %1, align 4
  store i32 %5, ptr %g, align 4
  %b = alloca i32, align 4
  %6 = load i32, ptr %2, align 4
  store i32 %6, ptr %b, align 4
  %a = alloca i32, align 4
  %7 = load i32, ptr %3, align 4
  store i32 %7, ptr %a, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %a1 = load i32, ptr %a, align 4
  %8 = mul i32 %a1, 256
  %9 = mul i32 %8, 256
  %10 = mul i32 %9, 256
  %b2 = load i32, ptr %b, align 4
  %11 = mul i32 %b2, 256
  %12 = mul i32 %11, 256
  %13 = add i32 %10, %12
  %g3 = load i32, ptr %g, align 4
  %14 = mul i32 %g3, 256
  %15 = add i32 %13, %14
  %r4 = load i32, ptr %r, align 4
  %16 = add i32 %15, %r4
  ret i32 %16

mergeBlock:                                       ; No predecessors!
  %17 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock
}

declare !rt !1 void @InitWindow(i32, i32, ptr)

declare !rt !2 void @SetTargetFPS(i32)

declare !rt !3 void @ClearBackground(i32)

declare !rt !4 i1 @WindowShouldClose()

declare !rt !5 void @BeginDrawing()

declare !rt !6 void @DrawRectangle(i32, i32, i32, i32, i32)

declare !rt !7 void @EndDrawing()

declare !rt !8 void @CloseWindow()

declare !rt !9 i32 @GetScreenHeight()

declare !rt !10 i32 @GetScreenWidth()

declare !rt !11 void @DrawCircle(i32, i32, float, i32)

declare !rt !12 void @DrawText(ptr, i32, i32, i32, i32)

declare !rt !13 i1 @IsKeyPressed(i32)

declare !rt !14 i1 @IsKeyDown(i32)

declare !rt !15 ptr @TextFormat(ptr)

declare !rt !16 i32 @rand()

declare !rt !17 i32 @time()

declare !rt !18 void @srand(i32)

define i32 @getRandomNumber(ptr %0, ptr %1) !rt !19 {
entry:
  %start = alloca i32, align 4
  %2 = load i32, ptr %0, align 4
  store i32 %2, ptr %start, align 4
  %end = alloca i32, align 4
  %3 = load i32, ptr %1, align 4
  store i32 %3, ptr %end, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %4 = call i32 @rand()
  %end1 = load i32, ptr %end, align 4
  %start2 = load i32, ptr %start, align 4
  %5 = sub i32 %end1, %start2
  %6 = add i32 %5, 1
  %7 = srem i32 %4, %6
  %start3 = load i32, ptr %start, align 4
  %8 = add i32 %7, %start3
  ret i32 %8

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @iUsersiappleicodeiperiFlow-Wingidocsidemoisnake-gameifg-raylib_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

!0 = !{!"COLOR:rt:pr:28"}
!1 = !{!"InitWindow:rt:pr:27"}
!2 = !{!"SetTargetFPS:rt:pr:27"}
!3 = !{!"ClearBackground:rt:pr:27"}
!4 = !{!"WindowShouldClose:rt:pr:34"}
!5 = !{!"BeginDrawing:rt:pr:27"}
!6 = !{!"DrawRectangle:rt:pr:27"}
!7 = !{!"EndDrawing:rt:pr:27"}
!8 = !{!"CloseWindow:rt:pr:27"}
!9 = !{!"GetScreenHeight:rt:pr:28"}
!10 = !{!"GetScreenWidth:rt:pr:28"}
!11 = !{!"DrawCircle:rt:pr:27"}
!12 = !{!"DrawText:rt:pr:27"}
!13 = !{!"IsKeyPressed:rt:pr:34"}
!14 = !{!"IsKeyDown:rt:pr:34"}
!15 = !{!"TextFormat:rt:pr:33"}
!16 = !{!"rand:rt:pr:28"}
!17 = !{!"time:rt:pr:28"}
!18 = !{!"srand:rt:pr:27"}
!19 = !{!"getRandomNumber:rt:pr:28"}
