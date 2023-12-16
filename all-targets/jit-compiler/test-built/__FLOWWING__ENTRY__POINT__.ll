; ModuleID = 'FlowWing'
source_filename = "FlowWing"

%DynamicType = type { i32, double, i1, ptr }

@__FLOWWING__ENTRY__POINT___FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@__FLOWWING__ENTRY__POINT___FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@__FLOWWING__ENTRY__POINT___FLOWWING_GLOBAL_NULL = external global i8
@__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT = global i32 0
@__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT = global i32 0
@__FLOWWING__ENTRY__POINT___FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@x = global %DynamicType zeroinitializer
@num = global %DynamicType zeroinitializer
@factorial = global %DynamicType zeroinitializer
@current = global %DynamicType zeroinitializer

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

define i32 @__FLOWWING__ENTRY__POINT__() {
entry:
  %0 = load %DynamicType, ptr @x, align 8
  %1 = insertvalue %DynamicType %0, i32 0, 0
  store %DynamicType %1, ptr @x, align 8
  %2 = load %DynamicType, ptr @num, align 8
  %3 = insertvalue %DynamicType %2, i32 5, 0
  store %DynamicType %3, ptr @num, align 8
  %4 = load %DynamicType, ptr @factorial, align 8
  %5 = insertvalue %DynamicType %4, i32 1, 0
  store %DynamicType %5, ptr @factorial, align 8
  %6 = load %DynamicType, ptr @current, align 8
  %7 = insertvalue %DynamicType %6, i32 1, 0
  store %DynamicType %7, ptr @current, align 8
  br label %loopCondition

returnBlock:                                      ; preds = %end_block23
  ret i32 0

loopCondition:                                    ; preds = %afterNestedBlock, %entry
  %8 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %end_block, label %decrement_block

loopBody:                                         ; preds = %breakLoop
  br label %nestedBlock

afterLoop:                                        ; preds = %breakLoop, %end_block
  %10 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %end_block23, label %decrement_block22

breakLoop:                                        ; preds = %end_block
  %12 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %loopBody, label %afterLoop

decrement_block:                                  ; preds = %loopCondition
  %14 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %15 = sub i32 %14, 1
  store i32 %15, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %loopCondition
  %current = load %DynamicType, ptr @current, align 8
  %16 = extractvalue %DynamicType %current, 0
  %num = load %DynamicType, ptr @num, align 8
  %17 = extractvalue %DynamicType %num, 0
  %18 = icmp sle i32 %16, %17
  br i1 %18, label %breakLoop, label %afterLoop

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %afterIfElse18, %checkContinueBlock4, %afterIfElse, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  br label %loopCondition

nestedBlock:                                      ; preds = %loopBody
  %factorial = load %DynamicType, ptr @factorial, align 8
  %19 = extractvalue %DynamicType %factorial, 0
  %current7 = load %DynamicType, ptr @current, align 8
  %20 = extractvalue %DynamicType %current7, 0
  %21 = mul i32 %19, %20
  %factorial8 = load %DynamicType, ptr @factorial, align 8
  %22 = insertvalue %DynamicType %factorial8, i32 %21, 0
  store %DynamicType %22, ptr @factorial, align 8
  %23 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %25 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %current9 = load %DynamicType, ptr @current, align 8
  %27 = extractvalue %DynamicType %current9, 0
  %28 = add i32 %27, 1
  %current10 = load %DynamicType, ptr @current, align 8
  %29 = insertvalue %DynamicType %current10, i32 %28, 0
  store %DynamicType %29, ptr @current, align 8
  %30 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %32 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %current11 = load %DynamicType, ptr @current, align 8
  %34 = extractvalue %DynamicType %current11, 0
  %35 = icmp eq i32 %34, 3
  br i1 %35, label %then, label %else

checkContinueBlock4:                              ; preds = %afterIfElse
  %36 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %current15 = load %DynamicType, ptr @current, align 8
  %38 = extractvalue %DynamicType %current15, 0
  %39 = icmp sgt i32 %38, 7
  br i1 %39, label %then16, label %else17

checkContinueBlock6:                              ; preds = %afterIfElse18
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock3
  br label %nestedBlock13

else:                                             ; preds = %nestedBlock3
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock12
  %40 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %checkContinueBlock4, label %afterNestedBlock

afterNestedBlock12:                               ; preds = %checkContinueBlock14, %nestedBlock13
  br label %afterIfElse

nestedBlock13:                                    ; preds = %then
  %42 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %43 = add i32 %42, 1
  store i32 %43, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_CONTINUE_COUNT, align 4
  %44 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %checkContinueBlock14, label %afterNestedBlock12

checkContinueBlock14:                             ; preds = %nestedBlock13
  br label %afterNestedBlock12

then16:                                           ; preds = %nestedBlock5
  br label %nestedBlock20

else17:                                           ; preds = %nestedBlock5
  br label %afterIfElse18

afterIfElse18:                                    ; preds = %else17, %afterNestedBlock19
  %46 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %checkContinueBlock6, label %afterNestedBlock

afterNestedBlock19:                               ; preds = %checkContinueBlock21, %nestedBlock20
  br label %afterIfElse18

nestedBlock20:                                    ; preds = %then16
  %48 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %49 = add i32 %48, 1
  store i32 %49, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %50 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %checkContinueBlock21, label %afterNestedBlock19

checkContinueBlock21:                             ; preds = %nestedBlock20
  br label %afterNestedBlock19

decrement_block22:                                ; preds = %afterLoop
  %52 = load i32, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  %53 = sub i32 %52, 1
  store i32 %53, ptr @__FLOWWING__ENTRY__POINT___FLOWWING_BREAK_COUNT, align 4
  br label %end_block23

end_block23:                                      ; preds = %decrement_block22, %afterLoop
  %factorial24 = load %DynamicType, ptr @factorial, align 8
  %54 = extractvalue %DynamicType %factorial24, 0
  %55 = call ptr @itos(i32 %54)
  call void @print(ptr %55, i1 false)
  br label %returnBlock
}
