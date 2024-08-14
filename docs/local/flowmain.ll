; ModuleID = 'flowmain'
source_filename = "flowmain"

%"A::VTableType" = type { ptr }
%A = type { ptr, i32 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.A.fg = common global %"A::VTableType" zeroinitializer
@x = common global i32 0
@y = common global ptr null
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@aw = common global ptr null
@2 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @3
@4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"Hi\00", align 1
@7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.2" = private constant ptr @7
@8 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.3" = private constant ptr @8
@9 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.4" = private constant ptr @9
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@11 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.5" = private constant ptr @11
@12 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.6" = private constant ptr @12

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
  store i32 0, ptr @x, align 4
  store ptr @0, ptr @y, align 8
  store i32 0, ptr @x, align 4
  store ptr @1, ptr @y, align 8
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  %0 = alloca i32, align 4
  store i32 2, ptr @x, align 4
  store ptr @2, ptr @y, align 8
  %x1 = load i32, ptr @x, align 4
  %1 = load i32, ptr @x, align 4
  %2 = load ptr, ptr @"%s", align 8
  %3 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %3, i32 %1)
  %y = load ptr, ptr @y, align 8
  %4 = load ptr, ptr @y, align 8
  %5 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %5, ptr %4)
  %y2 = load ptr, ptr @y, align 8
  store ptr @6, ptr @y, align 8
  %x3 = load i32, ptr @x, align 4
  store i32 5, ptr @x, align 4
  %x4 = load i32, ptr @x, align 4
  %6 = load i32, ptr @x, align 4
  %7 = load ptr, ptr @"%s.2", align 8
  %8 = load ptr, ptr @"%d.3", align 8
  call void (ptr, ...) @printf(ptr %8, i32 %6)
  %y5 = load ptr, ptr @y, align 8
  %9 = load ptr, ptr @y, align 8
  %10 = load ptr, ptr @"%s.4", align 8
  call void (ptr, ...) @printf(ptr %10, ptr %9)
  %11 = call ptr @malloc(i64 16)
  call void @"assign_<Class<A>>"(ptr %11)
  %12 = getelementptr inbounds %A, ptr %11, i32 0, i32 0
  store ptr @vtable.A.fg, ptr %12, align 8
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr inbounds %"A::VTableType", ptr %13, i32 0, i32 0
  store ptr @A.printX, ptr %14, align 8
  %15 = getelementptr inbounds %A, ptr %11, i32 0, i32 1
  store i32 0, ptr %15, align 4
  store ptr %11, ptr @aw, align 8
  store i32 23, ptr %0, align 4
  call void @A.init1(ptr %0, ptr @aw)
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
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
  %4 = load ptr, ptr @"%s.5", align 8
  %5 = load ptr, ptr @"%d.6", align 8
  call void (ptr, ...) @printf(ptr %5, i32 %3)
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define internal void @"assign_<Class<A>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  store ptr @10, ptr %1, align 8
  %2 = getelementptr inbounds %A, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  ret void
}

!0 = !{!"A.init1:rt:pr:27"}
!1 = !{!"A.printX:rt:pr:27"}
