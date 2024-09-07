; ModuleID = 'flowmain'
source_filename = "flowmain"

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [79 x i8] c"HTTP/1.1 200 OK\0D\0AContent-Type: text/plain\0D\0AContent-Length: 13\0D\0A\0D\0AHello, World!\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @2

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
  call void @main()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 void @start_server()

declare !rt !1 void @set_request_handler(ptr)

declare !rt !2 void @send(i32, ptr, i32, i32)

define void @my_request_handler(i32 %0, ptr %1) !rt !3 {
entry:
  %client_socket = alloca i32, align 4
  store i32 %0, ptr %client_socket, align 4
  %req = alloca ptr, align 8
  store ptr %1, ptr %req, align 8
  %response = alloca ptr, align 8
  store ptr @0, ptr %response, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  store ptr @1, ptr %response, align 8
  %2 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %4 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  %req5 = load ptr, ptr %req, align 8
  %6 = load ptr, ptr %req, align 8
  %7 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %7, ptr %6)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  %client_socket6 = load i32, ptr %client_socket, align 4
  %12 = load i32, ptr %client_socket, align 4
  %response7 = load ptr, ptr %response, align 8
  %13 = load ptr, ptr %response, align 8
  call void @send(i32 %12, ptr %13, i32 100, i32 0)
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  br label %afterNestedBlock
}

define void @main() !rt !4 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @start_server()
  %0 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1 = icmp eq i32 %0, 0
  br i1 %1, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %2 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  call void @set_request_handler(ptr @my_request_handler)
  %4 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

!0 = !{!"start_server:rt:pr:27"}
!1 = !{!"set_request_handler:rt:pr:27"}
!2 = !{!"send:rt:pr:27"}
!3 = !{!"my_request_handler:rt:pr:27"}
!4 = !{!"main:rt:pr:27"}
