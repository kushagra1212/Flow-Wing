; ModuleID = 'temp.cpp'
source_filename = "temp.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

%struct.Texture = type { i32, i32, i32, i32, i32 }
%struct.Color = type { i8, i8, i8, i8 }
%struct.Rectangle = type { float, float, float, float }
%struct.Vector2 = type { float, float }

@.str = private unnamed_addr constant [15 x i8] c"Hello, World!\0A\00", align 1
@.str.1 = private unnamed_addr constant [11 x i8] c"Snake Game\00", align 1
@.str.2 = private unnamed_addr constant [12 x i8] c"../bird.png\00", align 1
@.str.3 = private unnamed_addr constant [13 x i8] c"Texure Id%d\0A\00", align 1

; Function Attrs: mustprogress noinline norecurse optnone ssp uwtable(sync)
define noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.Texture, align 4
  %3 = alloca %struct.Color, align 1
  %4 = alloca i64, align 8
  %5 = alloca %struct.Texture, align 4
  %6 = alloca %struct.Rectangle, align 4
  %7 = alloca %struct.Rectangle, align 4
  %8 = alloca %struct.Vector2, align 4
  %9 = alloca %struct.Color, align 1
  %10 = alloca i64, align 8
  store i32 0, ptr %1, align 4
  %11 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  call void @InitWindow(i32 noundef 800, i32 noundef 600, ptr noundef @.str.1)
  call void @SetTargetFPS(i32 noundef 60)
  call void @LoadTexture(ptr sret(%struct.Texture) align 4 %2, ptr noundef @.str.2)
  br label %12

12:                                               ; preds = %15, %0
  %13 = call zeroext i1 @WindowShouldClose()
  %14 = xor i1 %13, true
  br i1 %14, label %15, label %39

15:                                               ; preds = %12
  call void @BeginDrawing()
  %16 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 0
  store i8 -11, ptr %16, align 1
  %17 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 1
  store i8 -11, ptr %17, align 1
  %18 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 2
  store i8 -11, ptr %18, align 1
  %19 = getelementptr inbounds %struct.Color, ptr %3, i32 0, i32 3
  store i8 -1, ptr %19, align 1
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %4, ptr align 1 %3, i64 4, i1 false)
  %20 = load i64, ptr %4, align 8
  call void @ClearBackground(i64 %20)
  call void @llvm.memcpy.p0.p0.i64(ptr align 4 %5, ptr align 4 %2, i64 20, i1 false)
  %21 = getelementptr inbounds %struct.Rectangle, ptr %6, i32 0, i32 0
  store float 0.000000e+00, ptr %21, align 4
  %22 = getelementptr inbounds %struct.Rectangle, ptr %6, i32 0, i32 1
  store float 0.000000e+00, ptr %22, align 4
  %23 = getelementptr inbounds %struct.Rectangle, ptr %6, i32 0, i32 2
  store float 1.080000e+03, ptr %23, align 4
  %24 = getelementptr inbounds %struct.Rectangle, ptr %6, i32 0, i32 3
  store float 1.080000e+03, ptr %24, align 4
  %25 = getelementptr inbounds %struct.Rectangle, ptr %7, i32 0, i32 0
  store float 0.000000e+00, ptr %25, align 4
  %26 = getelementptr inbounds %struct.Rectangle, ptr %7, i32 0, i32 1
  store float 0.000000e+00, ptr %26, align 4
  %27 = getelementptr inbounds %struct.Rectangle, ptr %7, i32 0, i32 2
  store float 1.080000e+03, ptr %27, align 4
  %28 = getelementptr inbounds %struct.Rectangle, ptr %7, i32 0, i32 3
  store float 1.080000e+03, ptr %28, align 4
  %29 = getelementptr inbounds %struct.Vector2, ptr %8, i32 0, i32 0
  store float 0.000000e+00, ptr %29, align 4
  %30 = getelementptr inbounds %struct.Vector2, ptr %8, i32 0, i32 1
  store float 0.000000e+00, ptr %30, align 4
  %31 = getelementptr inbounds %struct.Color, ptr %9, i32 0, i32 0
  store i8 -1, ptr %31, align 1
  %32 = getelementptr inbounds %struct.Color, ptr %9, i32 0, i32 1
  store i8 -1, ptr %32, align 1
  %33 = getelementptr inbounds %struct.Color, ptr %9, i32 0, i32 2
  store i8 -1, ptr %33, align 1
  %34 = getelementptr inbounds %struct.Color, ptr %9, i32 0, i32 3
  store i8 -1, ptr %34, align 1
  %35 = load [4 x float], ptr %6, align 4
  %36 = load [4 x float], ptr %7, align 4
  %37 = load [2 x float], ptr %8, align 4
  call void @llvm.memcpy.p0.p0.i64(ptr align 8 %10, ptr align 1 %9, i64 4, i1 false)
  %38 = load i64, ptr %10, align 8
  call void @DrawTexturePro(ptr noundef %5, [4 x float] %35, [4 x float] %36, [2 x float] %37, float noundef 0.000000e+00, i64 %38)
  call void @EndDrawing()
  br label %12, !llvm.loop !5

39:                                               ; preds = %12
  %40 = getelementptr inbounds %struct.Texture, ptr %2, i32 0, i32 0
  %41 = load i32, ptr %40, align 4
  %42 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %41)
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #1

declare void @InitWindow(i32 noundef, i32 noundef, ptr noundef) #1

declare void @SetTargetFPS(i32 noundef) #1

declare void @LoadTexture(ptr sret(%struct.Texture) align 4, ptr noundef) #1

declare zeroext i1 @WindowShouldClose() #1

declare void @BeginDrawing() #1

declare void @ClearBackground(i64) #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #2

declare void @DrawTexturePro(ptr noundef, [4 x float], [4 x float], [2 x float], float noundef, i64) #1

declare void @EndDrawing() #1

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
