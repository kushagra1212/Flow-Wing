; ModuleID = 'flowmain'
source_filename = "flowmain"

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@0 = private unnamed_addr constant [32 x i8] c"HTTP/1.1 200 OK\0D\0AContent-Type: \00", align 1
@1 = private unnamed_addr constant [19 x i8] c"\0D\0AContent-Length: \00", align 1
@2 = private unnamed_addr constant [5 x i8] c"\0D\0A\0D\0A\00", align 1
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private unnamed_addr constant [66 x i8] c"HTTP/1.1 200 OK\0D\0AContent-Type: application/json\0D\0AContent-Length: \00", align 1
@5 = private unnamed_addr constant [5 x i8] c"\0D\0A\0D\0A\00", align 1
@6 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@7 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@8 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@11 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@12 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@13 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@14 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@15 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@16 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@17 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@18 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@19 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@20 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@21 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@22 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@24 = private unnamed_addr constant [6 x i8] c"/json\00", align 1
@25 = private unnamed_addr constant [6 x i8] c"/text\00", align 1
@26 = private unnamed_addr constant [28 x i8] c"{\22message\22: \22Hello, JSON!\22}\00", align 1
@27 = private unnamed_addr constant [17 x i8] c"application/json\00", align 1
@28 = private unnamed_addr constant [7 x i8] c"200 OK\00", align 1
@29 = private unnamed_addr constant [17 x i8] c"application/json\00", align 1
@30 = private unnamed_addr constant [14 x i8] c"Hello, World!\00", align 1
@31 = private unnamed_addr constant [11 x i8] c"text/plain\00", align 1
@32 = private unnamed_addr constant [7 x i8] c"200 OK\00", align 1
@33 = private unnamed_addr constant [11 x i8] c"text/plain\00", align 1
@34 = private unnamed_addr constant [10 x i8] c"Not Found\00", align 1
@35 = private unnamed_addr constant [11 x i8] c"text/plain\00", align 1
@36 = private unnamed_addr constant [14 x i8] c"404 Not Found\00", align 1
@37 = private unnamed_addr constant [11 x i8] c"text/plain\00", align 1
@38 = private unnamed_addr constant [10 x i8] c"Request: \00", align 1
@39 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @39
@40 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.1" = private constant ptr @40
@41 = private unnamed_addr constant [4 x i8] c"GET\00", align 1
@42 = private unnamed_addr constant [6 x i8] c"/json\00", align 1
@43 = private unnamed_addr constant [4 x i8] c"GET\00", align 1
@44 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@45 = private unnamed_addr constant [4 x i8] c"GET\00", align 1
@46 = private unnamed_addr constant [6 x i8] c"/text\00", align 1

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

declare !rt !1 void @set_route(ptr, ptr, ptr)

declare !rt !2 void @set_middleware(ptr)

declare !rt !3 void @send_response(i32, ptr, ptr, ptr)

declare !rt !4 void @send(i32, ptr, i32, i32)

declare !rt !5 i32 @strlen(ptr)

define i32 @length(ptr %0) !rt !6 {
entry:
  %s = alloca ptr, align 8
  store ptr %0, ptr %s, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret i32 0

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %s1 = load ptr, ptr %s, align 8
  %1 = load ptr, ptr %s, align 8
  %2 = call i32 @strlen(ptr %1)
  ret i32 %2

mergeBlock:                                       ; No predecessors!
  %3 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %checkContinueBlock, label %afterNestedBlock
}

define ptr @generate_response(ptr %0, ptr %1) !rt !7 {
entry:
  %content_type = alloca ptr, align 8
  store ptr %0, ptr %content_type, align 8
  %body = alloca ptr, align 8
  store ptr %1, ptr %body, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret ptr @3

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %content_type1 = load ptr, ptr %content_type, align 8
  %2 = load ptr, ptr %content_type, align 8
  %3 = call ptr @concat_strings(ptr @0, ptr %2)
  %4 = call ptr @concat_strings(ptr %3, ptr @1)
  %body2 = load ptr, ptr %body, align 8
  %5 = load ptr, ptr %body, align 8
  %6 = call i32 @strlen(ptr %5)
  %7 = call ptr @itos(i32 %6)
  %8 = call ptr @concat_strings(ptr %4, ptr %7)
  %9 = call ptr @concat_strings(ptr %8, ptr @2)
  %body3 = load ptr, ptr %body, align 8
  %10 = load ptr, ptr %body, align 8
  %11 = call ptr @concat_strings(ptr %9, ptr %10)
  ret ptr %11

mergeBlock:                                       ; No predecessors!
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock, label %afterNestedBlock
}

define void @json_response(ptr %0, ptr %1) !rt !8 {
entry:
  %data = alloca ptr, align 8
  store ptr %1, ptr %data, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %mergeBlock
  ret void

nestedBlock:                                      ; preds = %entry
  br label %returnBlock

checkContinueBlock:                               ; preds = %mergeBlock
  br label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock
  %data1 = load ptr, ptr %data, align 8
  %2 = load ptr, ptr %data, align 8
  %3 = call i32 @strlen(ptr %2)
  %4 = call ptr @itos(i32 %3)
  %5 = call ptr @concat_strings(ptr @4, ptr %4)
  %6 = call ptr @concat_strings(ptr %5, ptr @5)
  %data2 = load ptr, ptr %data, align 8
  %7 = load ptr, ptr %data, align 8
  %8 = call ptr @concat_strings(ptr %6, ptr %7)
  store ptr %8, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock
}

define void @my_request_handler(i32 %0, ptr %1, ptr %2) !rt !9 {
entry:
  %client_socket = alloca i32, align 4
  store i32 %0, ptr %client_socket, align 4
  %req = alloca ptr, align 8
  store ptr %1, ptr %req, align 8
  %endpoint = alloca ptr, align 8
  store ptr %2, ptr %endpoint, align 8
  %json_response_data = alloca ptr, align 8
  store ptr @6, ptr %json_response_data, align 8
  %response = alloca ptr, align 8
  store ptr @7, ptr %response, align 8
  %plain_text_response = alloca ptr, align 8
  store ptr @8, ptr %plain_text_response, align 8
  %response1 = alloca ptr, align 8
  store ptr @9, ptr %response1, align 8
  %not_found_response = alloca ptr, align 8
  store ptr @10, ptr %not_found_response, align 8
  %response2 = alloca ptr, align 8
  store ptr @11, ptr %response2, align 8
  %json_response_data3 = alloca ptr, align 8
  store ptr @12, ptr %json_response_data3, align 8
  %response4 = alloca ptr, align 8
  store ptr @13, ptr %response4, align 8
  %plain_text_response5 = alloca ptr, align 8
  store ptr @14, ptr %plain_text_response5, align 8
  %response6 = alloca ptr, align 8
  store ptr @15, ptr %response6, align 8
  %not_found_response7 = alloca ptr, align 8
  store ptr @16, ptr %not_found_response7, align 8
  %response8 = alloca ptr, align 8
  store ptr @17, ptr %response8, align 8
  %json_response_data9 = alloca ptr, align 8
  store ptr @18, ptr %json_response_data9, align 8
  %response10 = alloca ptr, align 8
  store ptr @19, ptr %response10, align 8
  %plain_text_response11 = alloca ptr, align 8
  store ptr @20, ptr %plain_text_response11, align 8
  %response12 = alloca ptr, align 8
  store ptr @21, ptr %response12, align 8
  %not_found_response13 = alloca ptr, align 8
  store ptr @22, ptr %not_found_response13, align 8
  %response14 = alloca ptr, align 8
  store ptr @23, ptr %response14, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %afterIfElse
  ret void

nestedBlock:                                      ; preds = %entry
  %endpoint15 = load ptr, ptr %endpoint, align 8
  %3 = load ptr, ptr %endpoint, align 8
  %4 = call i1 @equal_strings(ptr %3, ptr @24)
  %5 = select i1 %4, i1 true, i1 false
  br i1 %5, label %then, label %orIf0

checkContinueBlock:                               ; preds = %afterIfElse
  br label %afterNestedBlock

then:                                             ; preds = %nestedBlock
  br label %nestedBlock18

orIf0:                                            ; preds = %nestedBlock
  %endpoint16 = load ptr, ptr %endpoint, align 8
  %6 = load ptr, ptr %endpoint, align 8
  %7 = call i1 @equal_strings(ptr %6, ptr @25)
  %8 = select i1 %7, i1 true, i1 false
  br i1 %8, label %orIfThen0, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock28

else:                                             ; preds = %orIf0
  br label %nestedBlock38

afterIfElse:                                      ; preds = %afterNestedBlock37, %afterNestedBlock27, %afterNestedBlock17
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock, label %afterNestedBlock

afterNestedBlock17:                               ; preds = %checkContinueBlock23, %nestedBlock22, %checkContinueBlock21, %nestedBlock20, %checkContinueBlock19, %nestedBlock18
  br label %afterIfElse

nestedBlock18:                                    ; preds = %then
  store ptr @26, ptr %json_response_data9, align 8
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock19, label %afterNestedBlock17

checkContinueBlock19:                             ; preds = %nestedBlock18
  %13 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %nestedBlock20, label %afterNestedBlock17

nestedBlock20:                                    ; preds = %checkContinueBlock19
  %json_response_data24 = load ptr, ptr %json_response_data9, align 8
  %15 = load ptr, ptr %json_response_data9, align 8
  %16 = call ptr @generate_response(ptr @27, ptr %15)
  store ptr %16, ptr %response10, align 8
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock21, label %afterNestedBlock17

checkContinueBlock21:                             ; preds = %nestedBlock20
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock22, label %afterNestedBlock17

nestedBlock22:                                    ; preds = %checkContinueBlock21
  %client_socket25 = load i32, ptr %client_socket, align 4
  %21 = load i32, ptr %client_socket, align 4
  %json_response_data26 = load ptr, ptr %json_response_data9, align 8
  %22 = load ptr, ptr %json_response_data9, align 8
  call void @send_response(i32 %21, ptr @28, ptr @29, ptr %22)
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock23, label %afterNestedBlock17

checkContinueBlock23:                             ; preds = %nestedBlock22
  br label %afterNestedBlock17

afterNestedBlock27:                               ; preds = %checkContinueBlock33, %nestedBlock32, %checkContinueBlock31, %nestedBlock30, %checkContinueBlock29, %nestedBlock28
  br label %afterIfElse

nestedBlock28:                                    ; preds = %orIfThen0
  store ptr @30, ptr %plain_text_response11, align 8
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock29, label %afterNestedBlock27

checkContinueBlock29:                             ; preds = %nestedBlock28
  %27 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %nestedBlock30, label %afterNestedBlock27

nestedBlock30:                                    ; preds = %checkContinueBlock29
  %plain_text_response34 = load ptr, ptr %plain_text_response11, align 8
  %29 = load ptr, ptr %plain_text_response11, align 8
  %30 = call ptr @generate_response(ptr @31, ptr %29)
  store ptr %30, ptr %response12, align 8
  %31 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %checkContinueBlock31, label %afterNestedBlock27

checkContinueBlock31:                             ; preds = %nestedBlock30
  %33 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %nestedBlock32, label %afterNestedBlock27

nestedBlock32:                                    ; preds = %checkContinueBlock31
  %client_socket35 = load i32, ptr %client_socket, align 4
  %35 = load i32, ptr %client_socket, align 4
  %plain_text_response36 = load ptr, ptr %plain_text_response11, align 8
  %36 = load ptr, ptr %plain_text_response11, align 8
  call void @send_response(i32 %35, ptr @32, ptr @33, ptr %36)
  %37 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %checkContinueBlock33, label %afterNestedBlock27

checkContinueBlock33:                             ; preds = %nestedBlock32
  br label %afterNestedBlock27

afterNestedBlock37:                               ; preds = %checkContinueBlock43, %nestedBlock42, %checkContinueBlock41, %nestedBlock40, %checkContinueBlock39, %nestedBlock38
  br label %afterIfElse

nestedBlock38:                                    ; preds = %else
  store ptr @34, ptr %not_found_response13, align 8
  %39 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %40 = icmp eq i32 %39, 0
  br i1 %40, label %checkContinueBlock39, label %afterNestedBlock37

checkContinueBlock39:                             ; preds = %nestedBlock38
  %41 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %nestedBlock40, label %afterNestedBlock37

nestedBlock40:                                    ; preds = %checkContinueBlock39
  %not_found_response44 = load ptr, ptr %not_found_response13, align 8
  %43 = load ptr, ptr %not_found_response13, align 8
  %44 = call ptr @generate_response(ptr @35, ptr %43)
  store ptr %44, ptr %response14, align 8
  %45 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %46 = icmp eq i32 %45, 0
  br i1 %46, label %checkContinueBlock41, label %afterNestedBlock37

checkContinueBlock41:                             ; preds = %nestedBlock40
  %47 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %nestedBlock42, label %afterNestedBlock37

nestedBlock42:                                    ; preds = %checkContinueBlock41
  %client_socket45 = load i32, ptr %client_socket, align 4
  %49 = load i32, ptr %client_socket, align 4
  %not_found_response46 = load ptr, ptr %not_found_response13, align 8
  %50 = load ptr, ptr %not_found_response13, align 8
  call void @send_response(i32 %49, ptr @36, ptr @37, ptr %50)
  %51 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %52 = icmp eq i32 %51, 0
  br i1 %52, label %checkContinueBlock43, label %afterNestedBlock37

checkContinueBlock43:                             ; preds = %nestedBlock42
  br label %afterNestedBlock37
}

define void @log_middleware(i32 %0, ptr %1, ptr %2) !rt !10 {
entry:
  %client_socket = alloca i32, align 4
  store i32 %0, ptr %client_socket, align 4
  %req = alloca ptr, align 8
  store ptr %1, ptr %req, align 8
  %endpoint = alloca ptr, align 8
  store ptr %2, ptr %endpoint, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %3, ptr @38)
  %req1 = load ptr, ptr %req, align 8
  %4 = load ptr, ptr %req, align 8
  %5 = load ptr, ptr @"%s.1", align 8
  call void (ptr, ...) @printf(ptr %5, ptr %4)
  %6 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  br label %afterNestedBlock
}

define void @main() !rt !11 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  call void @set_middleware(ptr @log_middleware)
  %0 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %1 = icmp eq i32 %0, 0
  br i1 %1, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %2 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  call void @set_route(ptr @41, ptr @42, ptr @my_request_handler)
  %4 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %6 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  call void @set_route(ptr @43, ptr @44, ptr @my_request_handler)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  call void @set_route(ptr @45, ptr @46, ptr @my_request_handler)
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %14 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  call void @start_server()
  %16 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  br label %afterNestedBlock
}

!0 = !{!"start_server:rt:pr:27"}
!1 = !{!"set_route:rt:pr:27"}
!2 = !{!"set_middleware:rt:pr:27"}
!3 = !{!"send_response:rt:pr:27"}
!4 = !{!"send:rt:pr:27"}
!5 = !{!"strlen:rt:pr:28"}
!6 = !{!"length:rt:pr:28"}
!7 = !{!"generate_response:rt:pr:33"}
!8 = !{!"json_response:rt:pr:33"}
!9 = !{!"my_request_handler:rt:pr:27"}
!10 = !{!"log_middleware:rt:pr:27"}
!11 = !{!"main:rt:pr:27"}
