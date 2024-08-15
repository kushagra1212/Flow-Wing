; ModuleID = 'flowmain'
source_filename = "flowmain"

%0 = type { ptr, ptr }
%1 = type { ptr, ptr }
%"A::VTableType" = type { ptr }
%A = type { ptr, i32, ptr }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.A.fg = common global %"A::VTableType" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@a = common global ptr null
@b = common global i32 0
@c = common global double 0.000000e+00
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@5 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @6
@7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.2" = private constant ptr @7
@8 = private unnamed_addr constant [7 x i8] c"%0.14f\00", align 1
@"%0.14f" = private constant ptr @8
@9 = private unnamed_addr constant [8 x i8] c"init B \00", align 1
@10 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.3" = private constant ptr @10
@11 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.4" = private constant ptr @11
@12 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.5" = private constant ptr @12
@13 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.6" = private constant ptr @13
@14 = private unnamed_addr constant [3 x i8] c"He\00", align 1
@15 = private unnamed_addr constant [4 x i8] c"a: \00", align 1
@16 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.7" = private constant ptr @16
@17 = private unnamed_addr constant [5 x i8] c"\0Ab: \00", align 1
@18 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.8" = private constant ptr @18
@19 = private unnamed_addr constant [5 x i8] c"\0Ax: \00", align 1
@20 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.9" = private constant ptr @20
@21 = private unnamed_addr constant [5 x i8] c"\0Ak: \00", align 1
@22 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.10" = private constant ptr @22

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
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  %b = alloca ptr, align 8
  store ptr @0, ptr %b, align 8
  %0 = alloca i32, align 4
  store i32 0, ptr @b, align 4
  store double 0.000000e+00, ptr @c, align 8
  store i32 0, ptr @b, align 4
  store double 0.000000e+00, ptr @c, align 8
  %rtPtr = alloca double, align 8
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  %rtStructPtrForAssignment = alloca %0, align 8
  %4 = call ptr @malloc(i64 24)
  call void @"assign_<Class<A>>"(ptr %4)
  %5 = getelementptr inbounds %A, ptr %4, i32 0, i32 0
  store ptr @vtable.A.fg, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %"A::VTableType", ptr %6, i32 0, i32 0
  store ptr @A.test, ptr %7, align 8
  %8 = getelementptr inbounds %A, ptr %4, i32 0, i32 1
  store i32 0, ptr %8, align 4
  %9 = getelementptr inbounds %A, ptr %4, i32 0, i32 2
  store ptr @3, ptr %9, align 8
  store ptr %4, ptr @a, align 8
  store i32 10, ptr %0, align 4
  call void @A.init1(ptr %0, ptr @a)
  %10 = getelementptr inbounds %0, ptr %rtStructPtrForAssignment, i32 0, i32 0
  store ptr @b, ptr %10, align 8
  %11 = getelementptr inbounds %0, ptr %rtStructPtrForAssignment, i32 0, i32 1
  store ptr @c, ptr %11, align 8
  %12 = load ptr, ptr @a, align 8
  %13 = getelementptr inbounds %A, ptr %12, i32 0, i32 0
  %14 = load ptr, ptr %13, align 8
  %15 = getelementptr inbounds %"A::VTableType", ptr %14, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  store i32 2, ptr %1, align 4
  store i32 53, ptr %2, align 4
  store ptr @4, ptr %3, align 8
  call void %16(ptr %rtStructPtrForAssignment, ptr %1, ptr %2, ptr %3, ptr @a)
  %17 = load %0, ptr %rtStructPtrForAssignment, align 8
  store %0 %17, ptr %rtStructPtrForAssignment, align 8
  %b1 = load i32, ptr @b, align 4
  %18 = load i32, ptr @b, align 4
  %19 = load ptr, ptr @"%s", align 8
  %20 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %20, i32 %18)
  %c = load double, ptr @c, align 8
  %21 = load double, ptr @c, align 8
  %22 = load ptr, ptr @"%s.2", align 8
  %23 = load ptr, ptr @"%0.14f", align 8
  call void (ptr, ...) @printf(ptr %23, double %21)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @A.init2(ptr %0, ptr %1, ptr %2) !rt !0 {
entry:
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %A, ptr %3, i32 0, i32 1
  %5 = getelementptr inbounds %A, ptr %3, i32 0, i32 2
  %x = alloca i32, align 4
  %6 = load i32, ptr %0, align 4
  store i32 %6, ptr %x, align 4
  %b = alloca ptr, align 8
  %7 = load ptr, ptr %1, align 8
  store ptr %7, ptr %b, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = load ptr, ptr %2, align 8
  %9 = getelementptr inbounds %A, ptr %8, i32 0, i32 1
  %x5 = load i32, ptr %9, align 4
  %x6 = load i32, ptr %x, align 4
  %10 = load i32, ptr %x, align 4
  store i32 %10, ptr %9, align 4
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %13 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %15 = load ptr, ptr @"%s.3", align 8
  call void (ptr, ...) @printf(ptr %15, ptr @9)
  %x7 = load i32, ptr %x, align 4
  %16 = load i32, ptr %x, align 4
  %17 = load ptr, ptr @"%s.4", align 8
  %18 = load ptr, ptr @"%d.5", align 8
  call void (ptr, ...) @printf(ptr %18, i32 %16)
  %b8 = load ptr, ptr %b, align 8
  %19 = load ptr, ptr %b, align 8
  %20 = load ptr, ptr @"%s.6", align 8
  call void (ptr, ...) @printf(ptr %20, ptr %19)
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = load ptr, ptr %2, align 8
  %26 = getelementptr inbounds %A, ptr %25, i32 0, i32 2
  %b9 = load ptr, ptr %26, align 8
  %b10 = load ptr, ptr %b, align 8
  %27 = load ptr, ptr %b, align 8
  store ptr %27, ptr %26, align 8
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @A.init1(ptr %0, ptr %1) !rt !1 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %A, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %A, ptr %2, i32 0, i32 2
  %x = alloca i32, align 4
  %5 = load i32, ptr %0, align 4
  store i32 %5, ptr %x, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %A, ptr %6, i32 0, i32 1
  %x3 = load i32, ptr %7, align 4
  %x4 = load i32, ptr %x, align 4
  %8 = load i32, ptr %x, align 4
  store i32 %8, ptr %7, align 4
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %11 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %13 = load ptr, ptr %1, align 8
  %14 = getelementptr inbounds %A, ptr %13, i32 0, i32 2
  %b = load ptr, ptr %14, align 8
  store ptr @14, ptr %14, align 8
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @A.test(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) {
entry:
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %A, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %A, ptr %5, i32 0, i32 2
  %a = alloca i32, align 4
  %8 = load i32, ptr %1, align 4
  store i32 %8, ptr %a, align 4
  %b = alloca i32, align 4
  %9 = load i32, ptr %2, align 4
  store i32 %9, ptr %b, align 4
  %k = alloca ptr, align 8
  %10 = load ptr, ptr %3, align 8
  store ptr %10, ptr %k, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock8, %mergeBlock, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %a9 = load i32, ptr %a, align 4
  %11 = load i32, ptr %a, align 4
  %12 = call ptr @itos(i32 %11)
  %13 = call ptr @concat_strings(ptr @15, ptr %12)
  %14 = load ptr, ptr @"%s.7", align 8
  call void (ptr, ...) @printf(ptr %14, ptr %13)
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %b10 = load i32, ptr %b, align 4
  %19 = load i32, ptr %b, align 4
  %20 = call ptr @itos(i32 %19)
  %21 = call ptr @concat_strings(ptr @17, ptr %20)
  %22 = load ptr, ptr @"%s.8", align 8
  call void (ptr, ...) @printf(ptr %22, ptr %21)
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %27 = load ptr, ptr %4, align 8
  %28 = getelementptr inbounds %A, ptr %27, i32 0, i32 1
  %x = load i32, ptr %28, align 4
  %29 = load i32, ptr %28, align 4
  %30 = call ptr @itos(i32 %29)
  %31 = call ptr @concat_strings(ptr @19, ptr %30)
  %32 = load ptr, ptr @"%s.9", align 8
  call void (ptr, ...) @printf(ptr %32, ptr %31)
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %35 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %k11 = load ptr, ptr %k, align 8
  %37 = load ptr, ptr %k, align 8
  %38 = call ptr @concat_strings(ptr @21, ptr %37)
  %39 = load ptr, ptr @"%s.10", align 8
  call void (ptr, ...) @printf(ptr %39, ptr %38)
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %42 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  br label %returnBlock

checkContinueBlock8:                              ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock7
  %44 = getelementptr inbounds %1, ptr %0, i32 0, i32 0
  %45 = load ptr, ptr %44, align 8
  store i32 23, ptr %45, align 4
  %46 = getelementptr inbounds %1, ptr %0, i32 0, i32 1
  %47 = load ptr, ptr %46, align 8
  store double 3.550000e+01, ptr %47, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %48 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %checkContinueBlock8, label %afterNestedBlock
}

declare !rt !2 void @A.test.1(ptr, ptr, ptr, ptr, ptr)

define internal void @"assign_<Class<A>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  store ptr @1, ptr %1, align 8
  %2 = getelementptr inbounds %A, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %A, ptr %0, i32 0, i32 2
  store ptr @2, ptr %3, align 8
  ret void
}

!0 = !{!"A.init2:rt:pr:27"}
!1 = !{!"A.init1:rt:pr:27"}
!2 = !{!"A.test:rt:pr:31"}
