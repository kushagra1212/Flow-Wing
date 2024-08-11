; ModuleID = 'flowmain'
source_filename = "flowmain"

%0 = type { ptr, ptr }
%1 = type { ptr, ptr }
%2 = type { ptr, ptr }
%3 = type { ptr, ptr }
%"A::VTableType" = type { ptr }
%A = type { ptr, i32 }
%T.0 = type { i32 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.A.fg = common global %"A::VTableType" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@u = common global i32 0
@b = common global ptr null
@rtStructPtr = common global %0 zeroinitializer
@1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @1
@2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @2
@3 = private unnamed_addr constant [5 x i8] c"Helo\00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.3" = private constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.4" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.5" = private constant ptr @6
@7 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@8 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.6" = private constant ptr @8
@9 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.7" = private constant ptr @9
@10 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.8" = private constant ptr @10
@11 = private unnamed_addr constant [2 x i8] c"e\00", align 1
@12 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.9" = private constant ptr @12
@13 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.10" = private constant ptr @13
@14 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.11" = private constant ptr @14
@15 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.12" = private constant ptr @15
@16 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.13" = private constant ptr @16
@17 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.14" = private constant ptr @17
@18 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.15" = private constant ptr @18
@19 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.16" = private constant ptr @19
@20 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.17" = private constant ptr @20
@21 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.18" = private constant ptr @21
@22 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.19" = private constant ptr @22
@23 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.20" = private constant ptr @23
@24 = private unnamed_addr constant [2 x i8] c"H\00", align 1
@"_fg_i:0" = common global i32 0
@"_fg_numberOfElementsFilled:" = common global i32 0
@25 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1

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
  %g = alloca i32, align 4
  store i32 0, ptr %g, align 4
  %x1 = alloca i32, align 4
  store i32 0, ptr %x1, align 4
  %y = alloca ptr, align 8
  store ptr @0, ptr %y, align 8
  %rtStructPtrForAssignment = alloca %1, align 8
  store i32 0, ptr @u, align 4
  store ptr @u, ptr @rtStructPtr, align 8
  store ptr @b, ptr getelementptr inbounds (%0, ptr @rtStructPtr, i32 0, i32 1), align 8
  br label %nestedBlock

returnBlock:                                      ; preds = %afterNestedBlock
  ret i32 0

afterNestedBlock:                                 ; preds = %checkContinueBlock19, %nestedBlock18, %checkContinueBlock17, %nestedBlock16, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %nestedBlock10, %checkContinueBlock9, %nestedBlock8, %checkContinueBlock7, %nestedBlock6, %checkContinueBlock5, %nestedBlock4, %checkContinueBlock3, %nestedBlock2, %checkContinueBlock, %nestedBlock
  call void @getFAndA(ptr @rtStructPtr)
  %0 = load ptr, ptr @b, align 8
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %"A::VTableType", ptr %2, i32 0, i32 0
  %4 = load ptr, ptr %3, align 8
  call void %4(ptr @b)
  %u = load i32, ptr @u, align 4
  %5 = load i32, ptr @u, align 4
  %6 = load ptr, ptr @"%s.15", align 8
  %7 = load ptr, ptr @"%d.16", align 8
  call void (ptr, ...) @printf(ptr %7, i32 %5)
  %8 = load ptr, ptr @b, align 8
  %9 = getelementptr inbounds %A, ptr %8, i32 0, i32 1
  %x33 = load i32, ptr %9, align 4
  %10 = load i32, ptr %9, align 4
  %11 = load ptr, ptr @"%s.17", align 8
  %12 = load ptr, ptr @"%d.18", align 8
  call void (ptr, ...) @printf(ptr %12, i32 %10)
  br label %returnBlock

nestedBlock:                                      ; preds = %entry
  call void @getX(ptr %g)
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock2, label %afterNestedBlock

nestedBlock2:                                     ; preds = %checkContinueBlock
  %g20 = load i32, ptr %g, align 4
  %17 = load i32, ptr %g, align 4
  %18 = load ptr, ptr @"%s", align 8
  %19 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %19, i32 %17)
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock3, label %afterNestedBlock

checkContinueBlock3:                              ; preds = %nestedBlock2
  %22 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %nestedBlock4, label %afterNestedBlock

nestedBlock4:                                     ; preds = %checkContinueBlock3
  call void @getX(ptr %x1)
  store ptr @3, ptr %y, align 8
  %24 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %checkContinueBlock5, label %afterNestedBlock

checkContinueBlock5:                              ; preds = %nestedBlock4
  %26 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %nestedBlock6, label %afterNestedBlock

nestedBlock6:                                     ; preds = %checkContinueBlock5
  %x21 = load i32, ptr %x1, align 4
  %28 = load i32, ptr %x1, align 4
  %29 = load ptr, ptr @"%s.3", align 8
  %30 = load ptr, ptr @"%d.4", align 8
  call void (ptr, ...) @printf(ptr %30, i32 %28)
  %y22 = load ptr, ptr %y, align 8
  %31 = load ptr, ptr %y, align 8
  %32 = load ptr, ptr @"%s.5", align 8
  call void (ptr, ...) @printf(ptr %32, ptr %31)
  %33 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %checkContinueBlock7, label %afterNestedBlock

checkContinueBlock7:                              ; preds = %nestedBlock6
  %35 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock7
  %y23 = load ptr, ptr %y, align 8
  store ptr @7, ptr %y, align 8
  %x24 = load i32, ptr %x1, align 4
  store i32 43, ptr %x1, align 4
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock9, label %afterNestedBlock

checkContinueBlock9:                              ; preds = %nestedBlock8
  %39 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %x25 = load i32, ptr %x1, align 4
  %41 = load i32, ptr %x1, align 4
  %42 = load ptr, ptr @"%s.6", align 8
  %43 = load ptr, ptr @"%d.7", align 8
  call void (ptr, ...) @printf(ptr %43, i32 %41)
  %y26 = load ptr, ptr %y, align 8
  %44 = load ptr, ptr %y, align 8
  %45 = load ptr, ptr @"%s.8", align 8
  call void (ptr, ...) @printf(ptr %45, ptr %44)
  %46 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %48 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %y27 = load ptr, ptr %y, align 8
  store ptr @11, ptr %y, align 8
  %x28 = load i32, ptr %x1, align 4
  call void @getX(ptr %x1)
  %50 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %52 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %x29 = load i32, ptr %x1, align 4
  %54 = load i32, ptr %x1, align 4
  %55 = load ptr, ptr @"%s.9", align 8
  %56 = load ptr, ptr @"%d.10", align 8
  call void (ptr, ...) @printf(ptr %56, i32 %54)
  %y30 = load ptr, ptr %y, align 8
  %57 = load ptr, ptr %y, align 8
  %58 = load ptr, ptr @"%s.11", align 8
  call void (ptr, ...) @printf(ptr %58, ptr %57)
  %59 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %61 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %63 = getelementptr inbounds %1, ptr %rtStructPtrForAssignment, i32 0, i32 0
  store ptr %x1, ptr %63, align 8
  %64 = getelementptr inbounds %1, ptr %rtStructPtrForAssignment, i32 0, i32 1
  store ptr %y, ptr %64, align 8
  call void @get(ptr %rtStructPtrForAssignment)
  %65 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %66 = icmp eq i32 %65, 0
  br i1 %66, label %checkContinueBlock17, label %afterNestedBlock

checkContinueBlock17:                             ; preds = %nestedBlock16
  %67 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  %x31 = load i32, ptr %x1, align 4
  %69 = load i32, ptr %x1, align 4
  %70 = load ptr, ptr @"%s.12", align 8
  %71 = load ptr, ptr @"%d.13", align 8
  call void (ptr, ...) @printf(ptr %71, i32 %69)
  %y32 = load ptr, ptr %y, align 8
  %72 = load ptr, ptr %y, align 8
  %73 = load ptr, ptr @"%s.14", align 8
  call void (ptr, ...) @printf(ptr %73, ptr %72)
  %74 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %checkContinueBlock19, label %afterNestedBlock

checkContinueBlock19:                             ; preds = %nestedBlock18
  br label %afterNestedBlock
}

define void @A.init1(ptr %0, ptr %1) !rt !0 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %A, ptr %2, i32 0, i32 1
  %x = alloca i32, align 4
  %4 = load i32, ptr %0, align 4
  store i32 %4, ptr %x, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %1, align 8
  %6 = getelementptr inbounds %A, ptr %5, i32 0, i32 1
  %x1 = load i32, ptr %6, align 4
  %x2 = load i32, ptr %x, align 4
  %7 = load i32, ptr %x, align 4
  store i32 %7, ptr %6, align 4
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @A.printX(ptr %0) !rt !1 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %A, ptr %1, i32 0, i32 1
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %x = load i32, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = load ptr, ptr @"%s.19", align 8
  %5 = load ptr, ptr @"%d.20", align 8
  call void (ptr, ...) @printf(ptr %5, i32 %3)
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @get(ptr %0) {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %1 = getelementptr inbounds %2, ptr %0, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  store i32 2, ptr %2, align 4
  %3 = getelementptr inbounds %2, ptr %0, i32 0, i32 1
  %4 = load ptr, ptr %3, align 8
  store ptr @24, ptr %4, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock
}

declare !rt !2 void @get.1(ptr)

define void @getX(ptr %0) !rt !3 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  store i32 2, ptr %0, align 4
  ret void

mergeBlock:                                       ; No predecessors!
  %1 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %checkContinueBlock, label %afterNestedBlock
}

define void @getFAndA(ptr %0) {
entry:
  %1 = alloca i32, align 4
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %2 = getelementptr inbounds %3, ptr %0, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  store i32 0, ptr @"_fg_i:0", align 4
  store i32 0, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopStart-0

mergeBlock:                                       ; No predecessors!
  %4 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock, label %afterNestedBlock

FillExpr.loopStart-0:                             ; preds = %returnBlock
  store i32 0, ptr @"_fg_i:0", align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopCmp-0:                               ; preds = %FillExpr.loopBody-0, %FillExpr.loopStart-0
  %6 = load i32, ptr @"_fg_i:0", align 4
  %7 = icmp slt i32 %6, 2
  %8 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %9 = icmp slt i32 %8, 2
  %10 = and i1 %7, %9
  br i1 %10, label %FillExpr.loopBody-0, label %FillExpr.loopEnd-0

FillExpr.loopBody-0:                              ; preds = %FillExpr.loopCmp-0
  %11 = load i32, ptr @"_fg_i:0", align 4
  %12 = getelementptr [2 x %T.0], ptr %3, i32 0, i32 %11
  store %T.0 zeroinitializer, ptr %12, align 4
  %13 = load i32, ptr @"_fg_i:0", align 4
  %14 = add i32 %13, 1
  store i32 %14, ptr @"_fg_i:0", align 4
  %15 = load i32, ptr @"_fg_numberOfElementsFilled:", align 4
  %16 = add i32 %15, 1
  store i32 %16, ptr @"_fg_numberOfElementsFilled:", align 4
  br label %FillExpr.loopCmp-0

FillExpr.loopEnd-0:                               ; preds = %FillExpr.loopCmp-0
  br label %FillExpr.exit

FillExpr.exit:                                    ; preds = %FillExpr.loopEnd-0
  %17 = getelementptr inbounds %3, ptr %0, i32 0, i32 1
  %18 = load ptr, ptr %17, align 8
  %19 = call ptr @malloc(i64 16)
  call void @"assign_<Class<A>>"(ptr %19)
  %20 = getelementptr inbounds %A, ptr %19, i32 0, i32 0
  store ptr @vtable.A.fg, ptr %20, align 8
  %21 = load ptr, ptr %20, align 8
  %22 = getelementptr inbounds %"A::VTableType", ptr %21, i32 0, i32 0
  store ptr @A.printX, ptr %22, align 8
  %23 = getelementptr inbounds %A, ptr %19, i32 0, i32 1
  store i32 0, ptr %23, align 4
  store ptr %19, ptr %18, align 8
  store i32 32, ptr %1, align 4
  call void @A.init1(ptr %1, ptr %18)
  ret void
}

declare !rt !4 void @getFAndA.2(ptr)

define internal void @"assign_<Class<A>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  store ptr @25, ptr %1, align 8
  %2 = getelementptr inbounds %A, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  ret void
}

!0 = !{!"A.init1:rt:pr:27"}
!1 = !{!"A.printX:rt:pr:27"}
!2 = !{!"get:rt:pr:33"}
!3 = !{!"getX:rt:pr:28"}
!4 = !{!"getFAndA:rt:ob:A"}
