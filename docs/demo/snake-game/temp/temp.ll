; ModuleID = 'temp.cpp'
source_filename = "temp.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

%struct.Vector2 = type { float, float }
%struct.Color = type { i8, i8, i8, i8 }

@.str = private unnamed_addr constant [23 x i8] c"Mouse Position Example\00", align 1
@.str.1 = private unnamed_addr constant [35 x i8] c"Move the mouse to see its position\00", align 1

; Function Attrs: mustprogress noinline norecurse optnone ssp uwtable(sync)
define noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.Vector2, align 4
  %3 = alloca %struct.Color, align 1
  %4 = alloca i64, align 8
  %5 = alloca %struct.Color, align 1
  %6 = alloca i64, align 8
  store i32 0, ptr %1, align 4
  call void @InitWindow(i32 noundef 800, i32 noundef 600, ptr noundef @.str)
  br label %7

7:                                                ; preds = %32, %0
  %8 = call zeroext i1 @WindowShouldClose()
  %9 = xor i1 %8, true
  br i1 %9, label %10, label %43

10:                                               ; preds = %7
  %11 = call %struct.Vector2 @GetMousePosition()
  %12 = getelementptr inbounds %struct.Vector2, ptr %2, i32 0, i32 0
  %13 = extractvalue %struct.Vector2 %11, 0
  store float %13, ptr %12, align 4
  %14 = getelementptr inbounds %struct.Vector2, ptr %2, i32 0, i32 1
  %15 = extractvalue %struct.Vector2 %11, 1
  store float %15, ptr %14, align 4
  %16 = getelementptr inbounds %struct.Vector2, ptr %2, i32 0, i32 0
  %17 = load float, ptr %16, align 4
  %18 = fcmp ogt float %17, 1.000000e+02
  br i1 %18, label %19, label %32

19:                                               ; preds = %10
  %20 = getelementptr inbounds %struct.Vector2, ptr %2, i32 0, i32 0
  %21 = load float, ptr %20, align 4
  %22 = fcmp olt float %21, 2.000000e+02
  br i1 %22, label %23, label %32

23:                                               ; preds = %19
  %24 = getelementptr inbounds %struct.Vector2, ptr %2, i32 0, i32 1
  %25 = load float, ptr %24, align 4
  %26 = fcmp ogt float %25, 1.000000e+02
  br i1 %26, label %27, label %32

27:                                               ; preds = %23
  %28 = getelementptr inbounds %struct.Vector2, ptr %2, i32 0, i32 1
  %29 = load float, ptr %28, align 4
  %30 = fcmp olt float %29, 2.000000e+02
  br i1 %30, label %31, label %32

31:                                               ; preds = %27
  br label %32

32:                                               ; preds = %31, %27, %23, %19, %10
  call void @BeginDrawing()
  %33 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 0
  store i8 -11, ptr %33, align 1
  %34 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 1
  store i8 -11, ptr %34, align 1
  %35 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 2
  store i8 -11, ptr %35, align 1
  %36 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 3
  store i8 -1, ptr %36, align 1
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %4, ptr align 1 %3, i64 4, i1 false)
  %37 = load i64, ptr %4, align 8
  call void @ClearBackground(i64 %37)
  %38 = getelementptr inbounds %struct.Color, ptr %5, i32 0, i32 0
  store i8 80, ptr %38, align 1
  %39 = getelementptr inbounds %struct.Color, ptr %5, i32 0, i32 1
  store i8 80, ptr %39, align 1
  %40 = getelementptr inbounds %struct.Color, ptr %5, i32 0, i32 2
  store i8 80, ptr %40, align 1
  %41 = getelementptr inbounds %struct.Color, ptr %5, i32 0, i32 3
  store i8 -1, ptr %41, align 1
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %6, ptr align 1 %5, i64 4, i1 false)
  %42 = load i64, ptr %6, align 8
  call void @DrawText(ptr noundef @.str.1, i32 noundef 10, i32 noundef 10, i32 noundef 20, i64 %42)
  call void @EndDrawing()
  br label %7, !llvm.loop !5

43:                                               ; preds = %7
  call void @CloseWindow()
  ret i32 0
}

declare void @InitWindow(i32 noundef, i32 noundef, ptr noundef) #1

declare zeroext i1 @WindowShouldClose() #1

declare %struct.Vector2 @GetMousePosition() #1

declare void @BeginDrawing() #1

declare void @ClearBackground(i64) #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #2

declare void @DrawText(ptr noundef, i32 noundef, i32 noundef, i32 noundef, i64) #1

declare void @EndDrawing() #1

declare void @CloseWindow() #1

attributes #0 = { mustprogress noinline norecurse optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 1}
!3 = !{i32 7, !"frame-pointer", i32 1}
!4 = !{!"Homebrew clang version 17.0.6"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
