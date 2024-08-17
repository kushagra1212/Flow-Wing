; ModuleID = 'flowmain'
source_filename = "flowmain"

%"C::VTableType" = type { ptr }
%"B::VTableType" = type { ptr, ptr, ptr }
%"A::VTableType" = type { ptr, ptr, ptr, ptr }
%A = type { ptr, i32, ptr, double, i32, double }
%C = type { ptr, double, ptr }
%B = type { ptr, i32, ptr, double }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.C.fg = common global %"C::VTableType" zeroinitializer
@vtable.B.fg = common global %"B::VTableType" zeroinitializer
@vtable.A.fg = common global %"A::VTableType" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@a = common global ptr null
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @3
@4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @4
@5 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@6 = private unnamed_addr constant [25 x i8] c"C Constructor is Called\0A\00", align 1
@7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @7
@8 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.2" = private constant ptr @8
@9 = private unnamed_addr constant [7 x i8] c"%0.14f\00", align 1
@"%0.14f" = private constant ptr @9
@10 = private unnamed_addr constant [13 x i8] c"Called super\00", align 1
@11 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.3" = private constant ptr @11
@12 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.4" = private constant ptr @12
@13 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.5" = private constant ptr @13
@14 = private unnamed_addr constant [6 x i8] c"world\00", align 1
@15 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.6" = private constant ptr @15
@16 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.7" = private constant ptr @16
@17 = private unnamed_addr constant [7 x i8] c"%0.14f\00", align 1
@"%0.14f.8" = private constant ptr @17
@18 = private unnamed_addr constant [25 x i8] c"B Constructor is Called\0A\00", align 1
@19 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.9" = private constant ptr @19
@20 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.10" = private constant ptr @20
@21 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.11" = private constant ptr @21
@22 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.12" = private constant ptr @22
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@25 = private unnamed_addr constant [8 x i8] c"CalledB\00", align 1
@26 = private unnamed_addr constant [25 x i8] c"A Constructor is Called\0A\00", align 1
@27 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.13" = private constant ptr @27
@28 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.14" = private constant ptr @28
@29 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.15" = private constant ptr @29
@30 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.16" = private constant ptr @30

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
  %z = alloca double, align 8
  store double 0.000000e+00, ptr %z, align 8
  %v = alloca ptr, align 8
  store ptr @0, ptr %v, align 8
  %z1 = alloca i32, align 4
  store i32 0, ptr %z1, align 4
  %j = alloca double, align 8
  store double 0.000000e+00, ptr %j, align 8
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  %y = alloca double, align 8
  store double 0.000000e+00, ptr %y, align 8
  %0 = call ptr @malloc(i64 48)
  call void @"assign_<Class<A>>"(ptr %0)
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  store ptr @vtable.A.fg, ptr %1, align 8
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"A::VTableType", ptr %2, i32 0, i32 3
  store ptr @A.getX, ptr %3, align 8
  %4 = getelementptr inbounds %"A::VTableType", ptr %2, i32 0, i32 1
  store ptr @A.getS, ptr %4, align 8
  %5 = getelementptr inbounds %"A::VTableType", ptr %2, i32 0, i32 2
  store ptr @A.getZ, ptr %5, align 8
  %6 = getelementptr inbounds %"A::VTableType", ptr %2, i32 0, i32 0
  store ptr @C.printW, ptr %6, align 8
  %7 = getelementptr inbounds %A, ptr %0, i32 0, i32 4
  store i32 0, ptr %7, align 4
  %8 = getelementptr inbounds %A, ptr %0, i32 0, i32 5
  store double 0.000000e+00, ptr %8, align 8
  store ptr %0, ptr @a, align 8
  call void @C.init0(ptr @a)
  call void @B.init0(ptr @a)
  call void @A.init0(ptr @a)
  %9 = load ptr, ptr @a, align 8
  %10 = getelementptr inbounds %A, ptr %9, i32 0, i32 1
  %z2 = load i32, ptr %10, align 4
  %11 = load i32, ptr %10, align 4
  %12 = load ptr, ptr @"%s", align 8
  %13 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %13, i32 %11)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @C.init0(ptr %0) !rt !0 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %C, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %C, ptr %1, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %z = load double, ptr %2, align 8
  store double 2.220000e+01, ptr %2, align 8
  %4 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %6 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %v = load ptr, ptr %3, align 8
  store ptr @5, ptr %3, align 8
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %12 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %12, ptr @6)
  %z7 = load double, ptr %2, align 8
  %13 = load double, ptr %2, align 8
  %14 = load ptr, ptr @"%s.2", align 8
  %15 = load ptr, ptr @"%0.14f", align 8
  call void (ptr, ...) @printf(ptr %15, double %13)
  %16 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %18 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %20 = load ptr, ptr %0, align 8
  %21 = getelementptr inbounds %C, ptr %20, i32 0, i32 1
  %z8 = load double, ptr %21, align 8
  %z9 = load double, ptr %2, align 8
  %22 = load double, ptr %2, align 8
  %23 = fadd double %22, 2.200000e+00
  store double %23, ptr %21, align 8
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @C.init1(ptr %0, ptr %1) !rt !1 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %C, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %C, ptr %2, i32 0, i32 2
  %x = alloca i32, align 4
  %5 = load i32, ptr %0, align 4
  store i32 %5, ptr %x, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = load ptr, ptr @"%s.3", align 8
  call void (ptr, ...) @printf(ptr %6, ptr @10)
  %x1 = load i32, ptr %x, align 4
  %7 = load i32, ptr %x, align 4
  %8 = load ptr, ptr @"%s.4", align 8
  %9 = load ptr, ptr @"%d.5", align 8
  call void (ptr, ...) @printf(ptr %9, i32 %7)
  %10 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @C.printW(ptr %0) !rt !2 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %C, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %C, ptr %1, i32 0, i32 2
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr @"%s.6", align 8
  call void (ptr, ...) @printf(ptr %4, ptr @14)
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @B.init0(ptr %0) !rt !3 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %B, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %B, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %B, ptr %1, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %z = load i32, ptr %2, align 4
  store i32 1, ptr %2, align 4
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %j = load double, ptr %4, align 8
  %9 = load double, ptr %4, align 8
  %10 = load ptr, ptr @"%s.7", align 8
  %11 = load ptr, ptr @"%0.14f.8", align 8
  call void (ptr, ...) @printf(ptr %11, double %9)
  %12 = load ptr, ptr @"%s.9", align 8
  call void (ptr, ...) @printf(ptr %12, ptr @18)
  %13 = load ptr, ptr %0, align 8
  %14 = getelementptr inbounds %B, ptr %13, i32 0, i32 1
  %z3 = load i32, ptr %14, align 4
  %15 = load i32, ptr %14, align 4
  %16 = load ptr, ptr @"%s.10", align 8
  %17 = load ptr, ptr @"%d.11", align 8
  call void (ptr, ...) @printf(ptr %17, i32 %15)
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @B.init1(ptr %0, ptr %1) !rt !4 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %B, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %B, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %B, ptr %2, i32 0, i32 3
  %j = alloca ptr, align 8
  %6 = load ptr, ptr %0, align 8
  store ptr %6, ptr %j, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %j1 = load ptr, ptr %j, align 8
  %7 = load ptr, ptr %j, align 8
  %8 = load ptr, ptr @"%s.12", align 8
  call void (ptr, ...) @printf(ptr %8, ptr %7)
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @B.getZ(ptr %0, ptr %1) !rt !5 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %B, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %B, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %B, ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %z = load i32, ptr %3, align 4
  %6 = load i32, ptr %3, align 4
  store i32 %6, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock
}

define void @B.getS(ptr %0, ptr %1) !rt !6 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %B, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %B, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %B, ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  store double 2.400000e+00, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock
}

define void @A.init0(ptr %0) !rt !7 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %A, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %A, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %A, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %A, ptr %1, i32 0, i32 4
  %6 = getelementptr inbounds %A, ptr %1, i32 0, i32 5
  %7 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %8 = call ptr @malloc(i64 32)
  call void @"assign_<Class<B>>"(ptr %8)
  %9 = getelementptr inbounds %B, ptr %8, i32 0, i32 0
  store ptr @vtable.B.fg, ptr %9, align 8
  %10 = load ptr, ptr %9, align 8
  %11 = getelementptr inbounds %"B::VTableType", ptr %10, i32 0, i32 1
  store ptr @B.getS, ptr %11, align 8
  %12 = getelementptr inbounds %"B::VTableType", ptr %10, i32 0, i32 2
  store ptr @B.getZ, ptr %12, align 8
  %13 = getelementptr inbounds %"B::VTableType", ptr %10, i32 0, i32 0
  store ptr @C.printW, ptr %13, align 8
  %14 = getelementptr inbounds %B, ptr %8, i32 0, i32 1
  store i32 0, ptr %14, align 4
  %15 = getelementptr inbounds %B, ptr %8, i32 0, i32 3
  store double 0.000000e+00, ptr %15, align 8
  store ptr %8, ptr %clPtr, align 8
  call void @C.init0(ptr %clPtr)
  store ptr @25, ptr %7, align 8
  call void @B.init1(ptr %7, ptr %clPtr)
  %16 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %18 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %20 = load ptr, ptr @"%s.13", align 8
  call void (ptr, ...) @printf(ptr %20, ptr @26)
  %21 = load ptr, ptr %0, align 8
  %22 = getelementptr inbounds %A, ptr %21, i32 0, i32 1
  %z = load i32, ptr %22, align 4
  %23 = load i32, ptr %22, align 4
  %24 = load ptr, ptr @"%s.14", align 8
  %25 = load ptr, ptr @"%d.15", align 8
  call void (ptr, ...) @printf(ptr %25, i32 %23)
  %26 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %28 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %v = load ptr, ptr %3, align 8
  %30 = load ptr, ptr %3, align 8
  %31 = load ptr, ptr @"%s.16", align 8
  call void (ptr, ...) @printf(ptr %31, ptr %30)
  %32 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @A.getX(ptr %0, ptr %1) !rt !8 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %A, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %A, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %A, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %A, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %A, ptr %2, i32 0, i32 5
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %x = load i32, ptr %6, align 4
  %8 = load i32, ptr %6, align 4
  store i32 %8, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @A.getZ(ptr %0, ptr %1) !rt !9 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %A, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %A, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %A, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %A, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %A, ptr %2, i32 0, i32 5
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %z = load i32, ptr %3, align 4
  %8 = load i32, ptr %3, align 4
  store i32 %8, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @A.getS(ptr %0, ptr %1) !rt !10 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %A, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %A, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %A, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %A, ptr %2, i32 0, i32 4
  %7 = getelementptr inbounds %A, ptr %2, i32 0, i32 5
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  store double 4.520000e+01, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock
}

define internal void @"assign_<Class<A>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  store ptr @1, ptr %1, align 8
  %2 = getelementptr inbounds %A, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %A, ptr %0, i32 0, i32 2
  store ptr @2, ptr %3, align 8
  %4 = getelementptr inbounds %A, ptr %0, i32 0, i32 3
  store double 0.000000e+00, ptr %4, align 8
  %5 = getelementptr inbounds %A, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %A, ptr %0, i32 0, i32 5
  store double 0.000000e+00, ptr %6, align 8
  ret void
}

define internal void @"assign_<Class<B>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %B, ptr %0, i32 0, i32 0
  store ptr @23, ptr %1, align 8
  %2 = getelementptr inbounds %B, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %B, ptr %0, i32 0, i32 2
  store ptr @24, ptr %3, align 8
  %4 = getelementptr inbounds %B, ptr %0, i32 0, i32 3
  store double 0.000000e+00, ptr %4, align 8
  ret void
}

!0 = !{!"C.init0:rt:pr:27"}
!1 = !{!"C.init1:rt:pr:27"}
!2 = !{!"C.printW:rt:pr:27"}
!3 = !{!"B.init0:rt:pr:27"}
!4 = !{!"B.init1:rt:pr:27"}
!5 = !{!"B.getZ:rt:pr:28"}
!6 = !{!"B.getS:rt:pr:31"}
!7 = !{!"A.init0:rt:pr:27"}
!8 = !{!"A.getX:rt:pr:28"}
!9 = !{!"A.getZ:rt:pr:28"}
!10 = !{!"A.getS:rt:pr:31"}
