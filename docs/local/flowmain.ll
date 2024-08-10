; ModuleID = 'flowmain'
source_filename = "flowmain"

%"A::VTableType" = type { ptr }
%T.1 = type { i32, double, %J.0 }
%J.0 = type { ptr }
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
@a = common global i32 0
@b = common global ptr null
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@c = common global double 0.000000e+00
@e = common global i1 false
@g = common global %T.1 zeroinitializer
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@f = common global [10 x %T.1] zeroinitializer
@l = common global i32 0
@aa = common global ptr null
@3 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @4
@5 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @6
@7 = private unnamed_addr constant [3 x i8] c"Hi\00", align 1
@8 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.2" = private constant ptr @8
@9 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.3" = private constant ptr @9
@10 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.4" = private constant ptr @10
@11 = private unnamed_addr constant [2 x i8] c"e\00", align 1
@12 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@13 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.5" = private constant ptr @13
@14 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.6" = private constant ptr @14
@15 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.7" = private constant ptr @15
@16 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket = private constant ptr @16
@17 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.8" = private constant ptr @17
@18 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma = private constant ptr @18
@19 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.9" = private constant ptr @19
@20 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ " = private constant ptr @20
@21 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@22 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.10" = private constant ptr @22
@23 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : " = private constant ptr @23
@24 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.11" = private constant ptr @24
@25 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.12" = private constant ptr @25
@26 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.13" = private constant ptr @26
@27 = private unnamed_addr constant [3 x i8] c", \00", align 1
@" , " = private constant ptr @27
@28 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@29 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.14" = private constant ptr @29
@30 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : .15" = private constant ptr @30
@31 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.16" = private constant ptr @31
@32 = private unnamed_addr constant [7 x i8] c"%0.14f\00", align 1
@"%0.14f" = private constant ptr @32
@33 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.17" = private constant ptr @33
@34 = private unnamed_addr constant [3 x i8] c", \00", align 1
@" , .18" = private constant ptr @34
@35 = private unnamed_addr constant [2 x i8] c"c\00", align 1
@36 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.19" = private constant ptr @36
@37 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : .20" = private constant ptr @37
@38 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.21" = private constant ptr @38
@39 = private unnamed_addr constant [3 x i8] c"{ \00", align 1
@"{ .22" = private constant ptr @39
@40 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@41 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.23" = private constant ptr @41
@42 = private unnamed_addr constant [4 x i8] c" : \00", align 1
@" : .24" = private constant ptr @42
@43 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.25" = private constant ptr @43
@44 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'" = private constant ptr @44
@45 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.26" = private constant ptr @45
@46 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.27" = private constant ptr @46
@47 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'.28" = private constant ptr @47
@48 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.29" = private constant ptr @48
@49 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}" = private constant ptr @49
@50 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.30" = private constant ptr @50
@51 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@"}.31" = private constant ptr @51
@52 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.32" = private constant ptr @52
@53 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket = private constant ptr @53
@54 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.33" = private constant ptr @54
@55 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.34" = private constant ptr @55
@56 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.35" = private constant ptr @56
@57 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.36" = private constant ptr @57
@58 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.37" = private constant ptr @58
@59 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.38" = private constant ptr @59
@60 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.39" = private constant ptr @60
@61 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d.40" = private constant ptr @61

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
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  store i32 0, ptr @a, align 4
  store ptr @1, ptr @b, align 8
  store double 0.000000e+00, ptr @c, align 8
  store i1 false, ptr @e, align 1
  call void @"assign_<Object<T.1>>"(ptr @g)
  call void @"assign_<Array<Object<T.1>>>:10,"(ptr @f)
  store i32 0, ptr @l, align 4
  %0 = alloca i32, align 4
  %1 = alloca i32, align 4
  %clPtr = alloca ptr, align 8
  store i32 2, ptr @x, align 4
  store ptr @3, ptr @y, align 8
  %x1 = load i32, ptr @x, align 4
  %2 = load i32, ptr @x, align 4
  %3 = load ptr, ptr @"%s", align 8
  %4 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %4, i32 %2)
  %y = load ptr, ptr @y, align 8
  %5 = load ptr, ptr @y, align 8
  %6 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %6, ptr %5)
  %y2 = load ptr, ptr @y, align 8
  store ptr @7, ptr @y, align 8
  %x3 = load i32, ptr @x, align 4
  store i32 5, ptr @x, align 4
  %x4 = load i32, ptr @x, align 4
  %7 = load i32, ptr @x, align 4
  %8 = load ptr, ptr @"%s.2", align 8
  %9 = load ptr, ptr @"%d.3", align 8
  call void (ptr, ...) @printf(ptr %9, i32 %7)
  %y5 = load ptr, ptr @y, align 8
  %10 = load ptr, ptr @y, align 8
  %11 = load ptr, ptr @"%s.4", align 8
  call void (ptr, ...) @printf(ptr %11, ptr %10)
  store i32 2, ptr @a, align 4
  store ptr @11, ptr @b, align 8
  store i32 45, ptr @l, align 4
  %12 = call ptr @malloc(i64 16)
  call void @"assign_<Class<A>>"(ptr %12)
  %13 = getelementptr inbounds %A, ptr %12, i32 0, i32 0
  store ptr @vtable.A.fg, ptr %13, align 8
  %14 = load ptr, ptr %13, align 8
  %15 = getelementptr inbounds %"A::VTableType", ptr %14, i32 0, i32 0
  store ptr @A.printX, ptr %15, align 8
  %16 = getelementptr inbounds %A, ptr %12, i32 0, i32 1
  store i32 0, ptr %16, align 4
  store ptr %12, ptr @aa, align 8
  store i32 22, ptr %0, align 4
  call void @A.init1(ptr %0, ptr @aa)
  %c = load double, ptr @c, align 8
  store double 2.300000e+00, ptr @c, align 8
  store double 3.300000e+00, ptr getelementptr inbounds (%T.1, ptr @g, i32 0, i32 1), align 8
  %e = load i1, ptr @e, align 1
  store i1 true, ptr @e, align 1
  store i32 10, ptr @f, align 4
  %e6 = load i1, ptr @e, align 1
  %17 = load i1, ptr @e, align 1
  %18 = load ptr, ptr @"%s.5", align 8
  %19 = load ptr, ptr @"%s.6", align 8
  %20 = select i1 %17, ptr @flowmain_FLOWWING_GLOBAL_TRUE, ptr @flowmain_FLOWWING_GLOBAL_FALSE
  call void (ptr, ...) @printf(ptr %19, ptr %20)
  call void @"print_<Array<Object<T.1>>>:10,"(ptr @f)
  %21 = load ptr, ptr @aa, align 8
  %22 = getelementptr inbounds %A, ptr %21, i32 0, i32 1
  %x7 = load i32, ptr %22, align 4
  %23 = load i32, ptr %22, align 4
  %24 = load ptr, ptr @"%s.33", align 8
  %25 = load ptr, ptr @"%d.34", align 8
  call void (ptr, ...) @printf(ptr %25, i32 %23)
  %26 = load ptr, ptr @aa, align 8
  %27 = getelementptr inbounds %A, ptr %26, i32 0, i32 0
  %28 = load ptr, ptr %27, align 8
  %29 = getelementptr inbounds %"A::VTableType", ptr %28, i32 0, i32 0
  %30 = load ptr, ptr %29, align 8
  call void %30(ptr @aa)
  %l = load i32, ptr @l, align 4
  store i32 12, ptr @l, align 4
  %31 = call ptr @malloc(i64 16)
  call void @"assign_<Class<A>>"(ptr %31)
  %32 = getelementptr inbounds %A, ptr %31, i32 0, i32 0
  store ptr @vtable.A.fg, ptr %32, align 8
  %33 = load ptr, ptr %32, align 8
  %34 = getelementptr inbounds %"A::VTableType", ptr %33, i32 0, i32 0
  store ptr @A.printX, ptr %34, align 8
  %35 = getelementptr inbounds %A, ptr %31, i32 0, i32 1
  store i32 0, ptr %35, align 4
  store ptr %31, ptr @aa, align 8
  store i32 32, ptr %1, align 4
  call void @A.init1(ptr %1, ptr @aa)
  %l8 = load i32, ptr @l, align 4
  %36 = load i32, ptr @l, align 4
  %37 = load ptr, ptr @"%s.35", align 8
  %38 = load ptr, ptr @"%d.36", align 8
  call void (ptr, ...) @printf(ptr %38, i32 %36)
  %39 = load ptr, ptr @aa, align 8
  %40 = getelementptr inbounds %A, ptr %39, i32 0, i32 1
  %x9 = load i32, ptr %40, align 4
  %41 = load i32, ptr %40, align 4
  %42 = load ptr, ptr @"%s.37", align 8
  %43 = load ptr, ptr @"%d.38", align 8
  call void (ptr, ...) @printf(ptr %43, i32 %41)
  %44 = load ptr, ptr @aa, align 8
  %45 = getelementptr inbounds %A, ptr %44, i32 0, i32 0
  %46 = load ptr, ptr %45, align 8
  %47 = getelementptr inbounds %"A::VTableType", ptr %46, i32 0, i32 0
  %48 = load ptr, ptr %47, align 8
  call void %48(ptr @aa)
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
  %4 = load ptr, ptr @"%s.39", align 8
  %5 = load ptr, ptr @"%d.40", align 8
  call void (ptr, ...) @printf(ptr %5, i32 %3)
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define internal void @"assign_<Object<T.1>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %T.1, ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %T.1, ptr %0, i32 0, i32 1
  store double 0.000000e+00, ptr %2, align 8
  %3 = getelementptr inbounds %T.1, ptr %0, i32 0, i32 2
  call void @"assign_<Object<J.0>>"(ptr %3)
  ret void
}

define internal void @"assign_<Object<J.0>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %J.0, ptr %0, i32 0, i32 0
  store ptr @2, ptr %1, align 8
  ret void
}

define internal void @"assign_<Array<Object<T.1>>>:10,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %AssignExpr.loopStart-0

AssignExpr.loopStart-0:                           ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  br label %AssignExpr.loopCmp-0

AssignExpr.loopCmp-0:                             ; preds = %AssignExpr.loopBody-0, %AssignExpr.loopStart-0
  %1 = load i32, ptr %"0_i", align 4
  %2 = icmp slt i32 %1, 10
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 10
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [10 x %T.1], ptr %0, i32 0, i32 %6
  call void @"assign_<Object<T.1>>"(ptr %7)
  %8 = load i32, ptr %"0_i", align 4
  %9 = add i32 %8, 1
  store i32 %9, ptr %"0_i", align 4
  %10 = load i32, ptr %numberOfElementsFilled, align 4
  %11 = add i32 %10, 1
  store i32 %11, ptr %numberOfElementsFilled, align 4
  br label %AssignExpr.loopCmp-0

AssignExpr.loopEnd-0:                             ; preds = %AssignExpr.loopCmp-0
  br label %AssignExpr.exit

AssignExpr.exit:                                  ; preds = %AssignExpr.loopEnd-0
  ret void
}

define internal void @"assign_<Class<A>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %A, ptr %0, i32 0, i32 0
  store ptr @12, ptr %1, align 8
  %2 = getelementptr inbounds %A, ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  ret void
}

define internal void @"print_<Array<Object<T.1>>>:10,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %con_print.loopStart

con_print.loopStart:                              ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  %1 = load ptr, ptr @"%s.7", align 8
  %2 = load ptr, ptr @openBracket, align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  br label %con_print.loopCmp

con_print.loopCmp:                                ; preds = %con_print.loopBody, %con_print.loopStart
  %3 = load i32, ptr %"0_i", align 4
  %4 = icmp slt i32 %3, 10
  %5 = icmp sgt i32 %3, 0
  %6 = and i1 %4, %5
  br i1 %6, label %con_print.print.lobby, label %con_print.stage

con_print.loopBody:                               ; preds = %con_print.stage, %con_print.print.lobby
  %7 = load i32, ptr %"0_i", align 4
  %8 = getelementptr [10 x %T.1], ptr %0, i32 0, i32 %7
  call void @print_T.1(ptr %8)
  %9 = load i32, ptr %"0_i", align 4
  %10 = add i32 %9, 1
  store i32 %10, ptr %"0_i", align 4
  br label %con_print.loopCmp

con_print.loopEnd:                                ; preds = %con_print.stage
  %11 = load ptr, ptr @"%s.32", align 8
  %12 = load ptr, ptr @closeBracket, align 8
  call void (ptr, ...) @printf(ptr %11, ptr %12)
  br label %con_print.exit

con_print.print.lobby:                            ; preds = %con_print.loopCmp
  %13 = load ptr, ptr @"%s.8", align 8
  %14 = load ptr, ptr @comma, align 8
  call void (ptr, ...) @printf(ptr %13, ptr %14)
  br label %con_print.loopBody

con_print.stage:                                  ; preds = %con_print.loopCmp
  %15 = load i32, ptr %"0_i", align 4
  %16 = icmp slt i32 %15, 10
  br i1 %16, label %con_print.loopBody, label %con_print.loopEnd

con_print.exit:                                   ; preds = %con_print.loopEnd
  ret void
}

define internal void @print_T.1(ptr %0) {
entry:
  %1 = load ptr, ptr @"%s.9", align 8
  %2 = load ptr, ptr @"{ ", align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  call void @print(ptr @21, i1 false)
  %3 = load ptr, ptr @"%s.10", align 8
  %4 = load ptr, ptr @" : ", align 8
  call void (ptr, ...) @printf(ptr %3, ptr %4)
  %5 = getelementptr inbounds %T.1, ptr %0, i32 0, i32 0
  %6 = load i32, ptr %5, align 4
  %7 = load ptr, ptr @"%s.11", align 8
  %8 = load ptr, ptr @"%d.12", align 8
  call void (ptr, ...) @printf(ptr %8, i32 %6)
  %9 = load ptr, ptr @"%s.13", align 8
  %10 = load ptr, ptr @" , ", align 8
  call void (ptr, ...) @printf(ptr %9, ptr %10)
  call void @print(ptr @28, i1 false)
  %11 = load ptr, ptr @"%s.14", align 8
  %12 = load ptr, ptr @" : .15", align 8
  call void (ptr, ...) @printf(ptr %11, ptr %12)
  %13 = getelementptr inbounds %T.1, ptr %0, i32 0, i32 1
  %14 = load double, ptr %13, align 8
  %15 = load ptr, ptr @"%s.16", align 8
  %16 = load ptr, ptr @"%0.14f", align 8
  call void (ptr, ...) @printf(ptr %16, double %14)
  %17 = load ptr, ptr @"%s.17", align 8
  %18 = load ptr, ptr @" , .18", align 8
  call void (ptr, ...) @printf(ptr %17, ptr %18)
  call void @print(ptr @35, i1 false)
  %19 = load ptr, ptr @"%s.19", align 8
  %20 = load ptr, ptr @" : .20", align 8
  call void (ptr, ...) @printf(ptr %19, ptr %20)
  %21 = getelementptr inbounds %T.1, ptr %0, i32 0, i32 2
  call void @print_J.0(ptr %21)
  %22 = load ptr, ptr @"%s.30", align 8
  %23 = load ptr, ptr @"}.31", align 8
  call void (ptr, ...) @printf(ptr %22, ptr %23)
  ret void
}

define internal void @print_J.0(ptr %0) {
entry:
  %1 = load ptr, ptr @"%s.21", align 8
  %2 = load ptr, ptr @"{ .22", align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  call void @print(ptr @40, i1 false)
  %3 = load ptr, ptr @"%s.23", align 8
  %4 = load ptr, ptr @" : .24", align 8
  call void (ptr, ...) @printf(ptr %3, ptr %4)
  %5 = getelementptr inbounds %J.0, ptr %0, i32 0, i32 0
  %6 = load ptr, ptr %5, align 8
  %7 = load ptr, ptr @"%s.25", align 8
  %8 = load ptr, ptr @"'", align 8
  call void (ptr, ...) @printf(ptr %7, ptr %8)
  %9 = icmp ne ptr %6, null
  br i1 %9, label %End, label %IsNull

IsNull:                                           ; preds = %entry
  br label %Merge

End:                                              ; preds = %entry
  %10 = load ptr, ptr @"%s.26", align 8
  call void (ptr, ...) @printf(ptr %10, ptr %6)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %11 = load ptr, ptr @"%s.27", align 8
  %12 = load ptr, ptr @"'.28", align 8
  call void (ptr, ...) @printf(ptr %11, ptr %12)
  %13 = load ptr, ptr @"%s.29", align 8
  %14 = load ptr, ptr @"}", align 8
  call void (ptr, ...) @printf(ptr %13, ptr %14)
  ret void
}

!0 = !{!"A.init1:rt:pr:27"}
!1 = !{!"A.printX:rt:pr:27"}
