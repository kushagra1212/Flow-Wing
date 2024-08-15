; ModuleID = 'flowmain'
source_filename = "flowmain"

%"a::VTableType" = type {}
%a = type { ptr, i32 }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@vtable.a.fg = common global %"a::VTableType" zeroinitializer
@a = common global ptr null
@0 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @1

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
  %0 = load ptr, ptr @a, align 8
  %1 = icmp ne ptr %0, null
  br i1 %1, label %then, label %else

returnBlock:                                      ; preds = %afterIfElse
  ret i32 0

then:                                             ; preds = %entry
  br label %nestedBlock

else:                                             ; preds = %entry
  br label %afterIfElse

afterIfElse:                                      ; preds = %else, %afterNestedBlock
  br label %returnBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  br label %afterIfElse

nestedBlock:                                      ; preds = %then
  %2 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %2, ptr @0)
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @a.init1(ptr %0, ptr %1) !rt !0 {
entry:
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds %a, ptr %2, i32 0, i32 1
  %x = alloca i32, align 4
  %4 = load i32, ptr %0, align 4
  store i32 %4, ptr %x, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %5 = load ptr, ptr %1, align 8
  %6 = getelementptr inbounds %a, ptr %5, i32 0, i32 1
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

!0 = !{!"a.init1:rt:pr:27"}
