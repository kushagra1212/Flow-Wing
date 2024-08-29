; ModuleID = 'flowmain'
source_filename = "flowmain"

%"Vehicle::VTableType" = type { ptr, ptr }
%"Car::VTableType" = type { ptr, ptr }
%Vehicle = type { ptr, ptr, ptr, i32 }
%Car = type { ptr, ptr, ptr, i32, i32 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.Vehicle.fg = common global %"Vehicle::VTableType" zeroinitializer
@vtable.Car.fg = common global %"Car::VTableType" zeroinitializer
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [2 x i8] c" \00", align 1
@3 = private unnamed_addr constant [2 x i8] c" \00", align 1
@4 = private unnamed_addr constant [10 x i8] c"Vehicle: \00", align 1
@5 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @5
@6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @6
@7 = private unnamed_addr constant [2 x i8] c" \00", align 1
@8 = private unnamed_addr constant [2 x i8] c" \00", align 1
@9 = private unnamed_addr constant [7 x i8] c" with \00", align 1
@10 = private unnamed_addr constant [7 x i8] c" doors\00", align 1
@11 = private unnamed_addr constant [6 x i8] c"Car: \00", align 1
@12 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.2" = private constant ptr @12
@13 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.3" = private constant ptr @13
@14 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@16 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@17 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@18 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [7 x i8] c"Toyota\00", align 1
@22 = private unnamed_addr constant [6 x i8] c"Camry\00", align 1
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@25 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@26 = private unnamed_addr constant [6 x i8] c"Honda\00", align 1
@27 = private unnamed_addr constant [6 x i8] c"Civic\00", align 1
@28 = private unnamed_addr constant [4 x i8] c"Red\00", align 1
@29 = private unnamed_addr constant [5 x i8] c"Blue\00", align 1
@30 = private unnamed_addr constant [6 x i8] c"Green\00", align 1
@31 = private unnamed_addr constant [19 x i8] c"Available colors: \00", align 1
@32 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.4" = private constant ptr @32
@33 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.5" = private constant ptr @33
@34 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket = private constant ptr @34
@35 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.6" = private constant ptr @35
@36 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma = private constant ptr @36
@37 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.7" = private constant ptr @37
@38 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'" = private constant ptr @38
@39 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.8" = private constant ptr @39
@40 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.9" = private constant ptr @40
@41 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'.10" = private constant ptr @41
@42 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.11" = private constant ptr @42
@43 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket = private constant ptr @43
@44 = private unnamed_addr constant [9 x i8] c"Prices: \00", align 1
@45 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.12" = private constant ptr @45
@46 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.13" = private constant ptr @46
@47 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket.14 = private constant ptr @47
@48 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.15" = private constant ptr @48
@49 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma.16 = private constant ptr @49
@50 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.17" = private constant ptr @50
@51 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@"%d" = private constant ptr @51
@52 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.18" = private constant ptr @52
@53 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket.19 = private constant ptr @53
@54 = private unnamed_addr constant [4 x i8] c"Red\00", align 1
@55 = private unnamed_addr constant [8 x i8] c"Primary\00", align 1
@56 = private unnamed_addr constant [5 x i8] c"Blue\00", align 1
@57 = private unnamed_addr constant [10 x i8] c"Secondary\00", align 1
@58 = private unnamed_addr constant [6 x i8] c"Green\00", align 1
@59 = private unnamed_addr constant [9 x i8] c"Tertiary\00", align 1
@60 = private unnamed_addr constant [873 x i8] c"\0A\1B[33m47| \1B[0m\1B[0m  printVehicleDetails(car)\0A\1B[0m\1B[33m48| \1B[0m\1B[0m  print(\22Available colors: \22, colors)\0A\1B[0m\1B[33m49| \1B[0m\1B[0m  print(\22Prices: \22, prices)\0A\1B[0m\1B[33m50| \1B[0m\1B[0m  var colorAssignments: str[3][2] = [[\22Red\22, \22Primary\22], [\22Blue\22, \22Secondary\22], [\22Green\22, \22Tertiary\22]]\0A\1B[0m\1B[33m51| \1B[0m\1B[31m\1B[1m  colorAssignments[1][1]= \22Main\22/; Update color assignment\0A\1B[0m\1B[32m\1B[1m                       \0A   ~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m52| \1B[0m\1B[0m\0A\1B[0m\1B[33m53| \1B[0m\1B[0m  print(\22Updated color assignments: \22, colorAssignments)\0A\1B[0m\1B[33m54| \1B[0m\1B[0m}\0A\1B[0m\1B[33m55| \1B[0m\1B[0mmain()\0A\1B[0m\1B[31mFile: Vehicle.fg [Error] : \1B[1;31mLine 51:23\1B[31m \22Index out of bounds of 'colorAssignments' in index expression, index value should be between 0 and 3\22\1B[0m\0A\1B[33mLocation: /var/folders/1m/ql4hjc5s5_32h16pfp65y5780000gn/T/Users/apple/code/per/Flow-Wing/docs/demo/programs/Vehicle.fg\0A\1B[0m\00", align 1
@61 = private unnamed_addr constant [873 x i8] c"\0A\1B[33m47| \1B[0m\1B[0m  printVehicleDetails(car)\0A\1B[0m\1B[33m48| \1B[0m\1B[0m  print(\22Available colors: \22, colors)\0A\1B[0m\1B[33m49| \1B[0m\1B[0m  print(\22Prices: \22, prices)\0A\1B[0m\1B[33m50| \1B[0m\1B[0m  var colorAssignments: str[3][2] = [[\22Red\22, \22Primary\22], [\22Blue\22, \22Secondary\22], [\22Green\22, \22Tertiary\22]]\0A\1B[0m\1B[33m51| \1B[0m\1B[31m\1B[1m  colorAssignments[1][1]= \22Main\22/; Update color assignment\0A\1B[0m\1B[32m\1B[1m                       \0A   ~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m52| \1B[0m\1B[0m\0A\1B[0m\1B[33m53| \1B[0m\1B[0m  print(\22Updated color assignments: \22, colorAssignments)\0A\1B[0m\1B[33m54| \1B[0m\1B[0m}\0A\1B[0m\1B[33m55| \1B[0m\1B[0mmain()\0A\1B[0m\1B[31mFile: Vehicle.fg [Error] : \1B[1;31mLine 51:23\1B[31m \22Index out of bounds of 'colorAssignments' in index expression, index value should be between 0 and 2\22\1B[0m\0A\1B[33mLocation: /var/folders/1m/ql4hjc5s5_32h16pfp65y5780000gn/T/Users/apple/code/per/Flow-Wing/docs/demo/programs/Vehicle.fg\0A\1B[0m\00", align 1
@62 = private unnamed_addr constant [5 x i8] c"Main\00", align 1
@63 = private unnamed_addr constant [28 x i8] c"Updated color assignments: \00", align 1
@64 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.20" = private constant ptr @64
@65 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.21" = private constant ptr @65
@66 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket.22 = private constant ptr @66
@67 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.23" = private constant ptr @67
@68 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma.24 = private constant ptr @68
@69 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.25" = private constant ptr @69
@70 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket.26 = private constant ptr @70
@71 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.27" = private constant ptr @71
@72 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@openBracket.28 = private constant ptr @72
@73 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.29" = private constant ptr @73
@74 = private unnamed_addr constant [3 x i8] c", \00", align 1
@comma.30 = private constant ptr @74
@75 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.31" = private constant ptr @75
@76 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'.32" = private constant ptr @76
@77 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.33" = private constant ptr @77
@78 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.34" = private constant ptr @78
@79 = private unnamed_addr constant [2 x i8] c"'\00", align 1
@"'.35" = private constant ptr @79
@80 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.36" = private constant ptr @80
@81 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@closeBracket.37 = private constant ptr @81

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
  %make = alloca ptr, align 8
  store ptr @0, ptr %make, align 8
  %model = alloca ptr, align 8
  store ptr @1, ptr %model, align 8
  %year = alloca i32, align 4
  store i32 0, ptr %year, align 4
  %doors = alloca i32, align 4
  store i32 0, ptr %doors, align 4
  call void @main()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

define void @Vehicle.init3(ptr %0, ptr %1, ptr %2, ptr %3) !rt !0 {
entry:
  %4 = load ptr, ptr %3, align 8
  %5 = getelementptr inbounds %Vehicle, ptr %4, i32 0, i32 1
  %6 = getelementptr inbounds %Vehicle, ptr %4, i32 0, i32 2
  %7 = getelementptr inbounds %Vehicle, ptr %4, i32 0, i32 3
  %make = alloca ptr, align 8
  %8 = load ptr, ptr %0, align 8
  store ptr %8, ptr %make, align 8
  %model = alloca ptr, align 8
  %9 = load ptr, ptr %1, align 8
  store ptr %9, ptr %model, align 8
  %year = alloca i32, align 4
  %10 = load i32, ptr %2, align 4
  store i32 %10, ptr %year, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %11 = load ptr, ptr %3, align 8
  %12 = getelementptr inbounds %Vehicle, ptr %11, i32 0, i32 1
  %make5 = load ptr, ptr %12, align 8
  %make6 = load ptr, ptr %make, align 8
  %13 = load ptr, ptr %make, align 8
  store ptr %13, ptr %12, align 8
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %18 = load ptr, ptr %3, align 8
  %19 = getelementptr inbounds %Vehicle, ptr %18, i32 0, i32 2
  %model7 = load ptr, ptr %19, align 8
  %model8 = load ptr, ptr %model, align 8
  %20 = load ptr, ptr %model, align 8
  store ptr %20, ptr %19, align 8
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %25 = load ptr, ptr %3, align 8
  %26 = getelementptr inbounds %Vehicle, ptr %25, i32 0, i32 3
  %year9 = load i32, ptr %26, align 4
  %year10 = load i32, ptr %year, align 4
  %27 = load i32, ptr %year, align 4
  store i32 %27, ptr %26, align 4
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @Vehicle.getDetails(ptr %0, ptr %1) !rt !1 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Vehicle, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Vehicle, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Vehicle, ptr %2, i32 0, i32 3
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %6 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %Vehicle, ptr %6, i32 0, i32 3
  %year = load i32, ptr %7, align 4
  %8 = load i32, ptr %7, align 4
  %9 = call ptr @itos(i32 %8)
  %10 = call ptr @concat_strings(ptr %9, ptr @2)
  %11 = load ptr, ptr %1, align 8
  %12 = getelementptr inbounds %Vehicle, ptr %11, i32 0, i32 1
  %make = load ptr, ptr %12, align 8
  %13 = load ptr, ptr %12, align 8
  %14 = call ptr @concat_strings(ptr %10, ptr %13)
  %15 = call ptr @concat_strings(ptr %14, ptr @3)
  %16 = load ptr, ptr %1, align 8
  %17 = getelementptr inbounds %Vehicle, ptr %16, i32 0, i32 2
  %model = load ptr, ptr %17, align 8
  %18 = load ptr, ptr %17, align 8
  %19 = call ptr @concat_strings(ptr %15, ptr %18)
  store ptr %19, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock, label %afterNestedBlock
}

define void @Vehicle.printDetails(ptr %0) !rt !2 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Vehicle, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Vehicle, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Vehicle, ptr %1, i32 0, i32 3
  %rtPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %5, ptr @4)
  call void @Vehicle.getDetails(ptr %rtPtr, ptr %0)
  %6 = load ptr, ptr %rtPtr, align 8
  %7 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %7, ptr %6)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @Car.init4(ptr %0, ptr %1, ptr %2, ptr %3, ptr %4) !rt !3 {
entry:
  %5 = load ptr, ptr %4, align 8
  %6 = getelementptr inbounds %Car, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds %Car, ptr %5, i32 0, i32 2
  %8 = getelementptr inbounds %Car, ptr %5, i32 0, i32 3
  %9 = getelementptr inbounds %Car, ptr %5, i32 0, i32 4
  %make = alloca ptr, align 8
  %10 = load ptr, ptr %0, align 8
  store ptr %10, ptr %make, align 8
  %model = alloca ptr, align 8
  %11 = load ptr, ptr %1, align 8
  store ptr %11, ptr %model, align 8
  %year = alloca i32, align 4
  %12 = load i32, ptr %2, align 4
  store i32 %12, ptr %year, align 4
  %doors = alloca i32, align 4
  %13 = load i32, ptr %3, align 4
  store i32 %13, ptr %doors, align 4
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %make3 = load ptr, ptr %make, align 8
  %model4 = load ptr, ptr %model, align 8
  %year5 = load i32, ptr %year, align 4
  call void @Vehicle.init3(ptr %make, ptr %model, ptr %year, ptr %4)
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %18 = load ptr, ptr %4, align 8
  %19 = getelementptr inbounds %Car, ptr %18, i32 0, i32 4
  %doors6 = load i32, ptr %19, align 4
  %doors7 = load i32, ptr %doors, align 4
  %20 = load i32, ptr %doors, align 4
  store i32 %20, ptr %19, align 4
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @Car.getDetails(ptr %0, ptr %1) !rt !4 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %Car, ptr %2, i32 0, i32 1
  %4 = getelementptr inbounds %Car, ptr %2, i32 0, i32 2
  %5 = getelementptr inbounds %Car, ptr %2, i32 0, i32 3
  %6 = getelementptr inbounds %Car, ptr %2, i32 0, i32 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %7 = load ptr, ptr %1, align 8
  %8 = getelementptr inbounds %Car, ptr %7, i32 0, i32 3
  %year = load i32, ptr %8, align 4
  %9 = load i32, ptr %8, align 4
  %10 = call ptr @itos(i32 %9)
  %11 = call ptr @concat_strings(ptr %10, ptr @7)
  %12 = load ptr, ptr %1, align 8
  %13 = getelementptr inbounds %Car, ptr %12, i32 0, i32 1
  %make = load ptr, ptr %13, align 8
  %14 = load ptr, ptr %13, align 8
  %15 = call ptr @concat_strings(ptr %11, ptr %14)
  %16 = call ptr @concat_strings(ptr %15, ptr @8)
  %17 = load ptr, ptr %1, align 8
  %18 = getelementptr inbounds %Car, ptr %17, i32 0, i32 2
  %model = load ptr, ptr %18, align 8
  %19 = load ptr, ptr %18, align 8
  %20 = call ptr @concat_strings(ptr %16, ptr %19)
  %21 = call ptr @concat_strings(ptr %20, ptr @9)
  %22 = load ptr, ptr %1, align 8
  %23 = getelementptr inbounds %Car, ptr %22, i32 0, i32 4
  %doors = load i32, ptr %23, align 4
  %24 = load i32, ptr %23, align 4
  %25 = call ptr @itos(i32 %24)
  %26 = call ptr @concat_strings(ptr %21, ptr %25)
  %27 = call ptr @concat_strings(ptr %26, ptr @10)
  store ptr %27, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %28 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %checkContinueBlock, label %afterNestedBlock
}

define void @Car.printDetails(ptr %0) !rt !5 {
entry:
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Car, ptr %1, i32 0, i32 1
  %3 = getelementptr inbounds %Car, ptr %1, i32 0, i32 2
  %4 = getelementptr inbounds %Car, ptr %1, i32 0, i32 3
  %5 = getelementptr inbounds %Car, ptr %1, i32 0, i32 4
  %rtPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %6 = load ptr, ptr @"%s.2", align 8
  call void (ptr, ...) @printf(ptr %6, ptr @11)
  call void @Car.getDetails(ptr %rtPtr, ptr %0)
  %7 = load ptr, ptr %rtPtr, align 8
  %8 = load ptr, ptr @"%s.3", align 8
  call void (ptr, ...) @printf(ptr %8, ptr %7)
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @printVehicleDetails(ptr %0) !rt !6 {
entry:
  %1 = call ptr @malloc(i64 32)
  %2 = load ptr, ptr %0, align 8
  %3 = load %Vehicle, ptr %2, align 8
  store %Vehicle %3, ptr %1, align 8
  %v = alloca ptr, align 8
  store ptr %1, ptr %v, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %4 = load ptr, ptr %v, align 8
  %5 = getelementptr inbounds %Vehicle, ptr %4, i32 0, i32 0
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %"Vehicle::VTableType", ptr %6, i32 0, i32 1
  %8 = load ptr, ptr %7, align 8
  call void %8(ptr %v)
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @main() !rt !7 {
entry:
  %vehicle = alloca ptr, align 8
  %0 = alloca ptr, align 8
  %1 = alloca ptr, align 8
  %2 = alloca i32, align 4
  %car = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %colors = alloca [3 x ptr], align 8
  call void @"assign_<Array[3]<'String'>>:3,"(ptr %colors)
  %prices = alloca [3 x i32], align 4
  call void @"assign_<Array[3]<'Integer32'>>:3,"(ptr %prices)
  %colorAssignments = alloca [3 x [2 x ptr]], align 8
  call void @"assign_<Array[3]<Array[2]<'String'>>>:3,2,"(ptr %colorAssignments)
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock20, %nestedBlock19, %checkContinueBlock18, %"GlobalIndexExpr::merge24", %checkContinueBlock16, %nestedBlock15, %checkContinueBlock14, %nestedBlock13, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %7 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Vehicle>>"(ptr %7)
  %8 = getelementptr inbounds %Vehicle, ptr %7, i32 0, i32 0
  store ptr @vtable.Vehicle.fg, ptr %8, align 8
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %"Vehicle::VTableType", ptr %9, i32 0, i32 1
  store ptr @Vehicle.printDetails, ptr %10, align 8
  %11 = getelementptr inbounds %"Vehicle::VTableType", ptr %9, i32 0, i32 0
  store ptr @Vehicle.getDetails, ptr %11, align 8
  %12 = getelementptr inbounds %Vehicle, ptr %7, i32 0, i32 1
  store ptr @19, ptr %12, align 8
  %13 = getelementptr inbounds %Vehicle, ptr %7, i32 0, i32 2
  store ptr @20, ptr %13, align 8
  %14 = getelementptr inbounds %Vehicle, ptr %7, i32 0, i32 3
  store i32 0, ptr %14, align 4
  store ptr %7, ptr %vehicle, align 8
  store ptr @21, ptr %0, align 8
  store ptr @22, ptr %1, align 8
  store i32 2020, ptr %2, align 4
  call void @Vehicle.init3(ptr %0, ptr %1, ptr %2, ptr %vehicle)
  %15 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %17 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %19 = call ptr @malloc(i64 32)
  call void @"assign_<Class<Car>>"(ptr %19)
  %20 = getelementptr inbounds %Car, ptr %19, i32 0, i32 0
  store ptr @vtable.Car.fg, ptr %20, align 8
  %21 = load ptr, ptr %20, align 8
  %22 = getelementptr inbounds %"Car::VTableType", ptr %21, i32 0, i32 1
  store ptr @Car.printDetails, ptr %22, align 8
  %23 = getelementptr inbounds %"Car::VTableType", ptr %21, i32 0, i32 0
  store ptr @Car.getDetails, ptr %23, align 8
  %24 = getelementptr inbounds %Car, ptr %19, i32 0, i32 4
  store i32 0, ptr %24, align 4
  store ptr %19, ptr %car, align 8
  store ptr @26, ptr %3, align 8
  store ptr @27, ptr %4, align 8
  store i32 2022, ptr %5, align 4
  store i32 4, ptr %6, align 4
  call void @Car.init4(ptr %3, ptr %4, ptr %5, ptr %6, ptr %car)
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %27 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %29 = getelementptr [3 x ptr], ptr %colors, i32 0, i32 0
  store ptr @28, ptr %29, align 8
  %30 = getelementptr [3 x ptr], ptr %colors, i32 0, i32 1
  store ptr @29, ptr %30, align 8
  %31 = getelementptr [3 x ptr], ptr %colors, i32 0, i32 2
  store ptr @30, ptr %31, align 8
  %32 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %34 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %36 = getelementptr [3 x i32], ptr %prices, i32 0, i32 0
  store i32 20000, ptr %36, align 4
  %37 = getelementptr [3 x i32], ptr %prices, i32 0, i32 1
  store i32 22000, ptr %37, align 4
  %38 = getelementptr [3 x i32], ptr %prices, i32 0, i32 2
  store i32 24000, ptr %38, align 4
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %41 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  call void @printVehicleDetails(ptr %vehicle)
  %43 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %45 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  call void @printVehicleDetails(ptr %car)
  %47 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %49 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  %51 = load ptr, ptr @"%s.4", align 8
  call void (ptr, ...) @printf(ptr %51, ptr @31)
  call void @"print_<Array[3]<'String'>>:3,"(ptr %colors)
  %52 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %53 = icmp eq i32 %52, 0
  br i1 %53, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %54 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %56 = load ptr, ptr @"%s.12", align 8
  call void (ptr, ...) @printf(ptr %56, ptr @44)
  call void @"print_<Array[3]<'Integer32'>>:3,"(ptr %prices)
  %57 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %checkContinueBlock14, label %afterNestedBlock

checkContinueBlock14:                             ; preds = %nestedBlock13
  %59 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %61 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 0, i32 0
  store ptr @54, ptr %61, align 8
  %62 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 0, i32 1
  store ptr @55, ptr %62, align 8
  %63 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 1, i32 0
  store ptr @56, ptr %63, align 8
  %64 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 1, i32 1
  store ptr @57, ptr %64, align 8
  %65 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 2, i32 0
  store ptr @58, ptr %65, align 8
  %66 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 2, i32 1
  store ptr @59, ptr %66, align 8
  %67 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %checkContinueBlock16, label %afterNestedBlock

checkContinueBlock16:                             ; preds = %nestedBlock15
  %69 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  %colorAssignments21 = load [3 x [2 x ptr]], ptr %colorAssignments, align 8
  br i1 true, label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock18:                             ; preds = %"GlobalIndexExpr::merge24"
  %71 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %nestedBlock19, label %afterNestedBlock

nestedBlock19:                                    ; preds = %checkContinueBlock18
  %73 = load ptr, ptr @"%s.20", align 8
  call void (ptr, ...) @printf(ptr %73, ptr @63)
  call void @"print_<Array[3]<Array[2]<'String'>>>:3,2,"(ptr %colorAssignments)
  %74 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %75 = icmp eq i32 %74, 0
  br i1 %75, label %checkContinueBlock20, label %afterNestedBlock

checkContinueBlock20:                             ; preds = %nestedBlock19
  br label %afterNestedBlock

"GlobalIndexExpr::then":                          ; preds = %nestedBlock17
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock17
  call void @raise_exception(ptr @60)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  br i1 true, label %"GlobalIndexExpr::then22", label %"GlobalIndexExpr::else23"

"GlobalIndexExpr::then22":                        ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge24"

"GlobalIndexExpr::else23":                        ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @61)
  br label %"GlobalIndexExpr::merge24"

"GlobalIndexExpr::merge24":                       ; preds = %"GlobalIndexExpr::else23", %"GlobalIndexExpr::then22"
  %76 = getelementptr [3 x [2 x ptr]], ptr %colorAssignments, i32 0, i32 1, i32 1
  %77 = load ptr, ptr %76, align 8
  store ptr @62, ptr %76, align 8
  %78 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %checkContinueBlock18, label %afterNestedBlock
}

define internal void @"assign_<Array[3]<'String'>>:3,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 3
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 3
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [3 x ptr], ptr %0, i32 0, i32 %6
  store ptr @14, ptr %7, align 8
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

define internal void @"assign_<Array[3]<'Integer32'>>:3,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 3
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 3
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [3 x i32], ptr %0, i32 0, i32 %6
  store i32 0, ptr %7, align 4
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

define internal void @"assign_<Array[3]<Array[2]<'String'>>>:3,2,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %"1_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %AssignExpr.loopStart-0

AssignExpr.loopStart-0:                           ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  br label %AssignExpr.loopCmp-0

AssignExpr.loopCmp-0:                             ; preds = %AssignExpr.loopEnd-1, %AssignExpr.loopStart-0
  %1 = load i32, ptr %"0_i", align 4
  %2 = icmp slt i32 %1, 3
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 6
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  br label %AssignExpr.loopStart-1

AssignExpr.loopEnd-0:                             ; preds = %AssignExpr.loopCmp-0
  br label %AssignExpr.exit

AssignExpr.loopStart-1:                           ; preds = %AssignExpr.loopBody-0
  store i32 0, ptr %"1_i", align 4
  br label %AssignExpr.loopCmp-1

AssignExpr.loopCmp-1:                             ; preds = %AssignExpr.loopBody-1, %AssignExpr.loopStart-1
  %6 = load i32, ptr %"1_i", align 4
  %7 = icmp slt i32 %6, 2
  %8 = load i32, ptr %numberOfElementsFilled, align 4
  %9 = icmp slt i32 %8, 6
  %10 = and i1 %7, %9
  br i1 %10, label %AssignExpr.loopBody-1, label %AssignExpr.loopEnd-1

AssignExpr.loopBody-1:                            ; preds = %AssignExpr.loopCmp-1
  %11 = load i32, ptr %"0_i", align 4
  %12 = load i32, ptr %"1_i", align 4
  %13 = getelementptr [3 x [2 x ptr]], ptr %0, i32 0, i32 %11, i32 %12
  store ptr @15, ptr %13, align 8
  %14 = load i32, ptr %"1_i", align 4
  %15 = add i32 %14, 1
  store i32 %15, ptr %"1_i", align 4
  %16 = load i32, ptr %numberOfElementsFilled, align 4
  %17 = add i32 %16, 1
  store i32 %17, ptr %numberOfElementsFilled, align 4
  br label %AssignExpr.loopCmp-1

AssignExpr.loopEnd-1:                             ; preds = %AssignExpr.loopCmp-1
  %18 = load i32, ptr %"0_i", align 4
  %19 = add i32 %18, 1
  store i32 %19, ptr %"0_i", align 4
  br label %AssignExpr.loopCmp-0

AssignExpr.exit:                                  ; preds = %AssignExpr.loopEnd-0
  ret void
}

define internal void @"assign_<Class<Vehicle>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 0
  store ptr @16, ptr %1, align 8
  %2 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 1
  store ptr @17, ptr %2, align 8
  %3 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 2
  store ptr @18, ptr %3, align 8
  %4 = getelementptr inbounds %Vehicle, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  ret void
}

define internal void @"assign_<Class<Car>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Car, ptr %0, i32 0, i32 0
  store ptr @23, ptr %1, align 8
  %2 = getelementptr inbounds %Car, ptr %0, i32 0, i32 1
  store ptr @24, ptr %2, align 8
  %3 = getelementptr inbounds %Car, ptr %0, i32 0, i32 2
  store ptr @25, ptr %3, align 8
  %4 = getelementptr inbounds %Car, ptr %0, i32 0, i32 3
  store i32 0, ptr %4, align 4
  %5 = getelementptr inbounds %Car, ptr %0, i32 0, i32 4
  store i32 0, ptr %5, align 4
  ret void
}

define internal void @"print_<Array[3]<'String'>>:3,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %con_print.loopStart

con_print.loopStart:                              ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  %1 = load ptr, ptr @"%s.5", align 8
  %2 = load ptr, ptr @openBracket, align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  br label %con_print.loopCmp

con_print.loopCmp:                                ; preds = %Merge, %con_print.loopStart
  %3 = load i32, ptr %"0_i", align 4
  %4 = icmp slt i32 %3, 3
  %5 = icmp sgt i32 %3, 0
  %6 = and i1 %4, %5
  br i1 %6, label %con_print.print.lobby, label %con_print.stage

con_print.loopBody:                               ; preds = %con_print.stage, %con_print.print.lobby
  %7 = load i32, ptr %"0_i", align 4
  %8 = getelementptr [3 x ptr], ptr %0, i32 0, i32 %7
  %9 = load ptr, ptr %8, align 8
  %10 = load ptr, ptr @"%s.7", align 8
  %11 = load ptr, ptr @"'", align 8
  call void (ptr, ...) @printf(ptr %10, ptr %11)
  %12 = icmp ne ptr %9, null
  br i1 %12, label %End, label %IsNull

con_print.loopEnd:                                ; preds = %con_print.stage
  %13 = load ptr, ptr @"%s.11", align 8
  %14 = load ptr, ptr @closeBracket, align 8
  call void (ptr, ...) @printf(ptr %13, ptr %14)
  br label %con_print.exit

con_print.print.lobby:                            ; preds = %con_print.loopCmp
  %15 = load ptr, ptr @"%s.6", align 8
  %16 = load ptr, ptr @comma, align 8
  call void (ptr, ...) @printf(ptr %15, ptr %16)
  br label %con_print.loopBody

con_print.stage:                                  ; preds = %con_print.loopCmp
  %17 = load i32, ptr %"0_i", align 4
  %18 = icmp slt i32 %17, 3
  br i1 %18, label %con_print.loopBody, label %con_print.loopEnd

con_print.exit:                                   ; preds = %con_print.loopEnd
  ret void

IsNull:                                           ; preds = %con_print.loopBody
  br label %Merge

End:                                              ; preds = %con_print.loopBody
  %19 = load ptr, ptr @"%s.8", align 8
  call void (ptr, ...) @printf(ptr %19, ptr %9)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %20 = load ptr, ptr @"%s.9", align 8
  %21 = load ptr, ptr @"'.10", align 8
  call void (ptr, ...) @printf(ptr %20, ptr %21)
  %22 = load i32, ptr %"0_i", align 4
  %23 = add i32 %22, 1
  store i32 %23, ptr %"0_i", align 4
  br label %con_print.loopCmp
}

define internal void @"print_<Array[3]<'Integer32'>>:3,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %con_print.loopStart

con_print.loopStart:                              ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  %1 = load ptr, ptr @"%s.13", align 8
  %2 = load ptr, ptr @openBracket.14, align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  br label %con_print.loopCmp

con_print.loopCmp:                                ; preds = %con_print.loopBody, %con_print.loopStart
  %3 = load i32, ptr %"0_i", align 4
  %4 = icmp slt i32 %3, 3
  %5 = icmp sgt i32 %3, 0
  %6 = and i1 %4, %5
  br i1 %6, label %con_print.print.lobby, label %con_print.stage

con_print.loopBody:                               ; preds = %con_print.stage, %con_print.print.lobby
  %7 = load i32, ptr %"0_i", align 4
  %8 = getelementptr [3 x i32], ptr %0, i32 0, i32 %7
  %9 = load i32, ptr %8, align 4
  %10 = load ptr, ptr @"%s.17", align 8
  %11 = load ptr, ptr @"%d", align 8
  call void (ptr, ...) @printf(ptr %11, i32 %9)
  %12 = load i32, ptr %"0_i", align 4
  %13 = add i32 %12, 1
  store i32 %13, ptr %"0_i", align 4
  br label %con_print.loopCmp

con_print.loopEnd:                                ; preds = %con_print.stage
  %14 = load ptr, ptr @"%s.18", align 8
  %15 = load ptr, ptr @closeBracket.19, align 8
  call void (ptr, ...) @printf(ptr %14, ptr %15)
  br label %con_print.exit

con_print.print.lobby:                            ; preds = %con_print.loopCmp
  %16 = load ptr, ptr @"%s.15", align 8
  %17 = load ptr, ptr @comma.16, align 8
  call void (ptr, ...) @printf(ptr %16, ptr %17)
  br label %con_print.loopBody

con_print.stage:                                  ; preds = %con_print.loopCmp
  %18 = load i32, ptr %"0_i", align 4
  %19 = icmp slt i32 %18, 3
  br i1 %19, label %con_print.loopBody, label %con_print.loopEnd

con_print.exit:                                   ; preds = %con_print.loopEnd
  ret void
}

define internal void @"print_<Array[3]<Array[2]<'String'>>>:3,2,"(ptr %0) {
entry:
  %"0_i" = alloca i32, align 4
  %"1_i" = alloca i32, align 4
  %numberOfElementsFilled = alloca i32, align 4
  store i32 0, ptr %numberOfElementsFilled, align 4
  br label %con_print.loopStart

con_print.loopStart:                              ; preds = %entry
  store i32 0, ptr %"0_i", align 4
  %1 = load ptr, ptr @"%s.21", align 8
  %2 = load ptr, ptr @openBracket.22, align 8
  call void (ptr, ...) @printf(ptr %1, ptr %2)
  br label %con_print.loopCmp

con_print.loopCmp:                                ; preds = %con_print.loopEnd4, %con_print.loopStart
  %3 = load i32, ptr %"0_i", align 4
  %4 = icmp slt i32 %3, 3
  %5 = icmp sgt i32 %3, 0
  %6 = and i1 %4, %5
  br i1 %6, label %con_print.print.lobby, label %con_print.stage

con_print.loopBody:                               ; preds = %con_print.stage, %con_print.print.lobby
  br label %con_print.loopStart1

con_print.loopEnd:                                ; preds = %con_print.stage
  %7 = load ptr, ptr @"%s.25", align 8
  %8 = load ptr, ptr @closeBracket.26, align 8
  call void (ptr, ...) @printf(ptr %7, ptr %8)
  br label %con_print.exit

con_print.print.lobby:                            ; preds = %con_print.loopCmp
  %9 = load ptr, ptr @"%s.23", align 8
  %10 = load ptr, ptr @comma.24, align 8
  call void (ptr, ...) @printf(ptr %9, ptr %10)
  br label %con_print.loopBody

con_print.stage:                                  ; preds = %con_print.loopCmp
  %11 = load i32, ptr %"0_i", align 4
  %12 = icmp slt i32 %11, 3
  br i1 %12, label %con_print.loopBody, label %con_print.loopEnd

con_print.loopStart1:                             ; preds = %con_print.loopBody
  store i32 0, ptr %"1_i", align 4
  %13 = load ptr, ptr @"%s.27", align 8
  %14 = load ptr, ptr @openBracket.28, align 8
  call void (ptr, ...) @printf(ptr %13, ptr %14)
  br label %con_print.loopCmp2

con_print.loopCmp2:                               ; preds = %Merge, %con_print.loopStart1
  %15 = load i32, ptr %"1_i", align 4
  %16 = icmp slt i32 %15, 2
  %17 = icmp sgt i32 %15, 0
  %18 = and i1 %16, %17
  br i1 %18, label %con_print.print.lobby5, label %con_print.stage6

con_print.loopBody3:                              ; preds = %con_print.stage6, %con_print.print.lobby5
  %19 = load i32, ptr %"0_i", align 4
  %20 = load i32, ptr %"1_i", align 4
  %21 = getelementptr [3 x [2 x ptr]], ptr %0, i32 0, i32 %19, i32 %20
  %22 = load ptr, ptr %21, align 8
  %23 = load ptr, ptr @"%s.31", align 8
  %24 = load ptr, ptr @"'.32", align 8
  call void (ptr, ...) @printf(ptr %23, ptr %24)
  %25 = icmp ne ptr %22, null
  br i1 %25, label %End, label %IsNull

con_print.loopEnd4:                               ; preds = %con_print.stage6
  %26 = load i32, ptr %"0_i", align 4
  %27 = add i32 %26, 1
  store i32 %27, ptr %"0_i", align 4
  %28 = load ptr, ptr @"%s.36", align 8
  %29 = load ptr, ptr @closeBracket.37, align 8
  call void (ptr, ...) @printf(ptr %28, ptr %29)
  br label %con_print.loopCmp

con_print.print.lobby5:                           ; preds = %con_print.loopCmp2
  %30 = load ptr, ptr @"%s.29", align 8
  %31 = load ptr, ptr @comma.30, align 8
  call void (ptr, ...) @printf(ptr %30, ptr %31)
  br label %con_print.loopBody3

con_print.stage6:                                 ; preds = %con_print.loopCmp2
  %32 = load i32, ptr %"1_i", align 4
  %33 = icmp slt i32 %32, 2
  br i1 %33, label %con_print.loopBody3, label %con_print.loopEnd4

con_print.exit:                                   ; preds = %con_print.loopEnd
  ret void

IsNull:                                           ; preds = %con_print.loopBody3
  br label %Merge

End:                                              ; preds = %con_print.loopBody3
  %34 = load ptr, ptr @"%s.33", align 8
  call void (ptr, ...) @printf(ptr %34, ptr %22)
  br label %Merge

Merge:                                            ; preds = %End, %IsNull
  %35 = load ptr, ptr @"%s.34", align 8
  %36 = load ptr, ptr @"'.35", align 8
  call void (ptr, ...) @printf(ptr %35, ptr %36)
  %37 = load i32, ptr %"1_i", align 4
  %38 = add i32 %37, 1
  store i32 %38, ptr %"1_i", align 4
  br label %con_print.loopCmp2
}

!0 = !{!"Vehicle.init3:rt:pr:27"}
!1 = !{!"Vehicle.getDetails:rt:pr:33"}
!2 = !{!"Vehicle.printDetails:rt:pr:27"}
!3 = !{!"Car.init4:rt:pr:27"}
!4 = !{!"Car.getDetails:rt:pr:33"}
!5 = !{!"Car.printDetails:rt:pr:27"}
!6 = !{!"printVehicleDetails:rt:pr:27"}
!7 = !{!"main:rt:pr:27"}
