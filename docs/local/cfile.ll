; ModuleID = 'cfile.c'
source_filename = "cfile.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

@.str = private unnamed_addr constant [9 x i8] c"temp.txt\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Hello, LLVM!\0A\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.3 = private unnamed_addr constant [31 x i8] c"Error opening file for writing\00", align 1
@.str.4 = private unnamed_addr constant [22 x i8] c"Error writing to file\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.6 = private unnamed_addr constant [31 x i8] c"Error opening file for reading\00", align 1
@.str.7 = private unnamed_addr constant [24 x i8] c"Data read from file: %s\00", align 1
@.str.8 = private unnamed_addr constant [24 x i8] c"Error reading from file\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca [100 x i8], align 1
  store i32 0, ptr %1, align 4
  store ptr @.str, ptr %3, align 8
  store ptr @.str.1, ptr %4, align 8
  %6 = load ptr, ptr %3, align 8
  %7 = call ptr @"\01_fopen"(ptr noundef %6, ptr noundef @.str.2)
  store ptr %7, ptr %2, align 8
  %8 = load ptr, ptr %2, align 8
  %9 = icmp eq ptr %8, null
  br i1 %9, label %10, label %11

10:                                               ; preds = %0
  call void @perror(ptr noundef @.str.3) #3
  store i32 1, ptr %1, align 4
  br label %40

11:                                               ; preds = %0
  %12 = load ptr, ptr %4, align 8
  %13 = load ptr, ptr %2, align 8
  %14 = call i64 @"\01_fwrite"(ptr noundef %12, i64 noundef 1, i64 noundef 8, ptr noundef %13)
  %15 = icmp ne i64 %14, 8
  br i1 %15, label %16, label %19

16:                                               ; preds = %11
  call void @perror(ptr noundef @.str.4) #3
  %17 = load ptr, ptr %2, align 8
  %18 = call i32 @fclose(ptr noundef %17)
  store i32 1, ptr %1, align 4
  br label %40

19:                                               ; preds = %11
  %20 = load ptr, ptr %2, align 8
  %21 = call i32 @fclose(ptr noundef %20)
  %22 = load ptr, ptr %3, align 8
  %23 = call ptr @"\01_fopen"(ptr noundef %22, ptr noundef @.str.5)
  store ptr %23, ptr %2, align 8
  %24 = load ptr, ptr %2, align 8
  %25 = icmp eq ptr %24, null
  br i1 %25, label %26, label %27

26:                                               ; preds = %19
  call void @perror(ptr noundef @.str.6) #3
  store i32 1, ptr %1, align 4
  br label %40

27:                                               ; preds = %19
  %28 = getelementptr inbounds [100 x i8], ptr %5, i64 0, i64 0
  %29 = load ptr, ptr %2, align 8
  %30 = call i64 @fread(ptr noundef %28, i64 noundef 1, i64 noundef 99, ptr noundef %29)
  %31 = icmp ugt i64 %30, 0
  br i1 %31, label %32, label %36

32:                                               ; preds = %27
  %33 = getelementptr inbounds [100 x i8], ptr %5, i64 0, i64 99
  store i8 0, ptr %33, align 1
  %34 = getelementptr inbounds [100 x i8], ptr %5, i64 0, i64 0
  %35 = call i32 (ptr, ...) @printf(ptr noundef @.str.7, ptr noundef %34)
  br label %37

36:                                               ; preds = %27
  call void @perror(ptr noundef @.str.8) #3
  br label %37

37:                                               ; preds = %36, %32
  %38 = load ptr, ptr %2, align 8
  %39 = call i32 @fclose(ptr noundef %38)
  store i32 0, ptr %1, align 4
  br label %40

40:                                               ; preds = %37, %26, %16, %10
  %41 = load i32, ptr %1, align 4
  ret i32 %41
}

declare ptr @"\01_fopen"(ptr noundef, ptr noundef) #1

; Function Attrs: cold
declare void @perror(ptr noundef) #2

declare i64 @"\01_fwrite"(ptr noundef, i64 noundef, i64 noundef, ptr noundef) #1

declare i32 @fclose(ptr noundef) #1

declare i64 @fread(ptr noundef, i64 noundef, i64 noundef, ptr noundef) #1

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #2 = { cold "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #3 = { cold }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 1}
!3 = !{i32 7, !"frame-pointer", i32 1}
!4 = !{!"Homebrew clang version 17.0.6"}
