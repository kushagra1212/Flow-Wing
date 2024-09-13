; ModuleID = 'flowmain'
source_filename = "flowmain"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin23.4.0"

%0 = type { ptr, ptr }
%"Vec::Int::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"Vec::Bool::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"Vec::String::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"Vec::Deci::VTableType" = type { ptr, ptr, ptr, ptr, ptr }
%"Str::ComparisonResult.0" = type { i32, i32, i32 }
%DynamicType = type { i32, double, i1, ptr, i8, i64, float }
%HttpRequest.2 = type { ptr, ptr, ptr, %Header.1, ptr }
%Header.1 = type { ptr, ptr, ptr, i1, ptr, i32, ptr, ptr, ptr, ptr, ptr, ptr, i1, ptr, ptr, ptr, ptr, i32 }
%"Vec::String" = type { ptr, ptr }

@flowmain_FLOWWING_GLOBAL_TRUE = constant [5 x i8] c"true\00"
@flowmain_FLOWWING_GLOBAL_FALSE = constant [6 x i8] c"false\00"
@flowmain_FLOWWING_GLOBAL_NULL = external global i8
@flowmain_FLOWWING_BREAK_COUNT = global i32 0
@flowmain_FLOWWING_CONTINUE_COUNT = global i32 0
@flowmain_FLOWWING_GLOBAL_ERROR_COUNT = global i32 0
@"vtable.Vec::Int.fg" = common global %"Vec::Int::VTableType" zeroinitializer
@"vtable.Vec::Bool.fg" = common global %"Vec::Bool::VTableType" zeroinitializer
@"vtable.Vec::String.fg" = common global %"Vec::String::VTableType" zeroinitializer
@"vtable.Vec::Deci.fg" = common global %"Vec::Deci::VTableType" zeroinitializer
@"Str::comparisonResult" = common local_unnamed_addr global %"Str::ComparisonResult.0" zeroinitializer
@0 = private local_unnamed_addr global [32 x i8] c"HTTP/1.1 200 OK\0D\0AContent-Type: \00"
@1 = private local_unnamed_addr global [19 x i8] c"\0D\0AContent-Length: \00"
@2 = private local_unnamed_addr global [5 x i8] c"\0D\0A\0D\0A\00"
@3 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@4 = private local_unnamed_addr global [66 x i8] c"HTTP/1.1 200 OK\0D\0AContent-Type: application/json\0D\0AContent-Length: \00"
@5 = private local_unnamed_addr global [5 x i8] c"\0D\0A\0D\0A\00"
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
@24 = private local_unnamed_addr global [6 x i8] c"/json\00"
@25 = private local_unnamed_addr global [6 x i8] c"/text\00"
@26 = private local_unnamed_addr global [28 x i8] c"{\22message\22: \22Hello, JSON!\22}\00"
@27 = private local_unnamed_addr global [17 x i8] c"application/json\00"
@28 = private local_unnamed_addr global [7 x i8] c"200 OK\00"
@29 = private local_unnamed_addr global [17 x i8] c"application/json\00"
@30 = private local_unnamed_addr global [14 x i8] c"Hello, World!\00"
@31 = private local_unnamed_addr global [11 x i8] c"text/plain\00"
@32 = private local_unnamed_addr global [7 x i8] c"200 OK\00"
@33 = private local_unnamed_addr global [11 x i8] c"text/plain\00"
@34 = private local_unnamed_addr global [10 x i8] c"Not Found\00"
@35 = private local_unnamed_addr global [11 x i8] c"text/plain\00"
@36 = private local_unnamed_addr global [14 x i8] c"404 Not Found\00"
@37 = private local_unnamed_addr global [11 x i8] c"text/plain\00"
@38 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@39 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@40 = private local_unnamed_addr global [1 x i8] zeroinitializer
@41 = private unnamed_addr constant [836 x i8] c"\0A\1B[33m62| \1B[0m\1B[0m  var j: int = 0\0A\1B[0m\1B[33m63| \1B[0m\1B[0m  for var i = 0 to Str::length(s) - 1 {\0A\1B[0m\1B[33m64| \1B[0m\1B[0m    if (Str::int8ToString(Int8(s[i])) == delimiter) {\0A\1B[0m\1B[33m65| \1B[0m\1B[0m      if (Str::length(part)) {\0A\1B[0m\1B[33m66| \1B[0m\1B[31m\1B[1m        result[j] = part\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m67| \1B[0m\1B[0m        j = j + 1 \0A\1B[0m\1B[33m68| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m69| \1B[0m\1B[0m      part = \22\22 \0A\1B[0m\1B[33m70| \1B[0m\1B[0m    } or if (i + 1 < Str::length(s) && String(Str::int8ToString(Int8(s[i])) + Str::int8ToString(Int8(s[i + 1]))) == delimiter) {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 66:16\1B[31m \22Index out of bounds of 'result' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@42 = private local_unnamed_addr global [1 x i8] zeroinitializer
@43 = private unnamed_addr constant [767 x i8] c"\0A\1B[33m68| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m69| \1B[0m\1B[0m      part = \22\22 \0A\1B[0m\1B[33m70| \1B[0m\1B[0m    } or if (i + 1 < Str::length(s) && String(Str::int8ToString(Int8(s[i])) + Str::int8ToString(Int8(s[i + 1]))) == delimiter) {\0A\1B[0m\1B[33m71| \1B[0m\1B[0m      if (Str::length(part)) {\0A\1B[0m\1B[33m72| \1B[0m\1B[31m\1B[1m        result[j] = part\0A\1B[0m\1B[32m\1B[1m                \0A   ~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m73| \1B[0m\1B[0m        j = j + 1 \0A\1B[0m\1B[33m74| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m75| \1B[0m\1B[0m      i = i + 1 \0A\1B[0m\1B[33m76| \1B[0m\1B[0m      part = \22\22 \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 72:16\1B[31m \22Index out of bounds of 'result' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@44 = private local_unnamed_addr global [1 x i8] zeroinitializer
@45 = private unnamed_addr constant [622 x i8] c"\0A\1B[33m78| \1B[0m\1B[0m      part = part + Str::int8ToString(Int8(s[i])) \0A\1B[0m\1B[33m79| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m80| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m81| \1B[0m\1B[0m  if Str::length(part) > 0 {\0A\1B[0m\1B[33m82| \1B[0m\1B[31m\1B[1m    result[j] = part\0A\1B[0m\1B[32m\1B[1m            \0A   ~~~~~~~~~~~^\1B[0m\0A\1B[33m83| \1B[0m\1B[0m  }\0A\1B[0m\1B[33m84| \1B[0m\1B[0m  return result\0A\1B[0m\1B[33m85| \1B[0m\1B[0m}\0A\1B[0m\1B[33m86| \1B[0m\1B[0m\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 82:12\1B[31m \22Index out of bounds of 'result' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@46 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@47 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@48 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@49 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@50 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@51 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@52 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@53 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@54 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@55 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@56 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@57 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@58 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@59 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@60 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@61 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@62 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@63 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@64 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@65 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@66 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@67 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@68 = private local_unnamed_addr global [2 x i8] c"\0D\00"
@69 = private unnamed_addr constant [774 x i8] c"\0A\1B[33m119| \1B[0m\1B[0m  var body: str\0A\1B[0m\1B[33m120| \1B[0m\1B[0m  var hasBody = false\0A\1B[0m\1B[33m121| \1B[0m\1B[0m  var header_map: Header\0A\1B[0m\1B[33m122| \1B[0m\1B[0m  for var i = 0 to 100 - 1 {\0A\1B[0m\1B[33m123| \1B[0m\1B[31m\1B[1m    lines[i] = lines[i] + \22\\n\22\0A\1B[0m\1B[32m\1B[1m           \0A   ~~~~~~~~~~^\1B[0m\0A\1B[33m124| \1B[0m\1B[0m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[33m125| \1B[0m\1B[0m    var first_line: str = sublines[0]\0A\1B[0m\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 123:11\1B[31m \22Index out of bounds of 'lines' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@70 = private unnamed_addr constant [796 x i8] c"\0A\1B[33m119| \1B[0m\1B[0m  var body: str\0A\1B[0m\1B[33m120| \1B[0m\1B[0m  var hasBody = false\0A\1B[0m\1B[33m121| \1B[0m\1B[0m  var header_map: Header\0A\1B[0m\1B[33m122| \1B[0m\1B[0m  for var i = 0 to 100 - 1 {\0A\1B[0m\1B[33m123| \1B[0m\1B[31m\1B[1m    lines[i] = lines[i] + \22\\n\22\0A\1B[0m\1B[32m\1B[1m                      \0A   ~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m124| \1B[0m\1B[0m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[33m125| \1B[0m\1B[0m    var first_line: str = sublines[0]\0A\1B[0m\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 123:22\1B[31m \22Index out of bounds of 'lines' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@71 = private local_unnamed_addr global [2 x i8] c"\0A\00"
@72 = private unnamed_addr constant [928 x i8] c"\0A\1B[33m120| \1B[0m\1B[0m  var hasBody = false\0A\1B[0m\1B[33m121| \1B[0m\1B[0m  var header_map: Header\0A\1B[0m\1B[33m122| \1B[0m\1B[0m  for var i = 0 to 100 - 1 {\0A\1B[0m\1B[33m123| \1B[0m\1B[0m    lines[i] = lines[i] + \22\\n\22\0A\1B[0m\1B[33m124| \1B[0m\1B[31m\1B[1m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[32m\1B[1m                                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m125| \1B[0m\1B[0m    var first_line: str = sublines[0]\0A\1B[0m\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[33m128| \1B[0m\1B[0m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 124:42\1B[31m \22Index out of bounds of 'lines' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@73 = private local_unnamed_addr global [2 x i8] c"\0A\00"
@74 = private unnamed_addr constant [899 x i8] c"\0A\1B[33m121| \1B[0m\1B[0m  var header_map: Header\0A\1B[0m\1B[33m122| \1B[0m\1B[0m  for var i = 0 to 100 - 1 {\0A\1B[0m\1B[33m123| \1B[0m\1B[0m    lines[i] = lines[i] + \22\\n\22\0A\1B[0m\1B[33m124| \1B[0m\1B[0m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[33m125| \1B[0m\1B[31m\1B[1m    var first_line: str = sublines[0]\0A\1B[0m\1B[32m\1B[1m                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[33m128| \1B[0m\1B[0m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[33m129| \1B[0m\1B[0m \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 125:36\1B[31m \22Index out of bounds of 'sublines' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@75 = private local_unnamed_addr global [2 x i8] c" \00"
@76 = private unnamed_addr constant [950 x i8] c"\0A\1B[33m124| \1B[0m\1B[0m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[33m125| \1B[0m\1B[0m    var first_line: str = sublines[0]\0A\1B[0m\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[33m128| \1B[0m\1B[31m\1B[1m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[32m\1B[1m                                         \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m129| \1B[0m\1B[0m \0A\1B[0m\1B[33m130| \1B[0m\1B[0m    } else {\0A\1B[0m\1B[33m131| \1B[0m\1B[0m      var header_parts: str[100] = split(first_line, \22:\22)\0A\1B[0m\1B[33m132| \1B[0m\1B[0m      header_parts[1] = Str::trimInPlace(header_parts[1])\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 128:41\1B[31m \22Index out of bounds of 'parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@77 = private unnamed_addr constant [970 x i8] c"\0A\1B[33m124| \1B[0m\1B[0m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[33m125| \1B[0m\1B[0m    var first_line: str = sublines[0]\0A\1B[0m\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[33m128| \1B[0m\1B[31m\1B[1m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[32m\1B[1m                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m129| \1B[0m\1B[0m \0A\1B[0m\1B[33m130| \1B[0m\1B[0m    } else {\0A\1B[0m\1B[33m131| \1B[0m\1B[0m      var header_parts: str[100] = split(first_line, \22:\22)\0A\1B[0m\1B[33m132| \1B[0m\1B[0m      header_parts[1] = Str::trimInPlace(header_parts[1])\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 128:51\1B[31m \22Index out of bounds of 'parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@78 = private unnamed_addr constant [990 x i8] c"\0A\1B[33m124| \1B[0m\1B[0m    var sublines: str[100] = split(lines[i], \22\\n\22)\0A\1B[0m\1B[33m125| \1B[0m\1B[0m    var first_line: str = sublines[0]\0A\1B[0m\1B[33m126| \1B[0m\1B[0m    if i == 0 {\0A\1B[0m\1B[33m127| \1B[0m\1B[0m      var parts: str[100] = split(first_line, \22 \22)\0A\1B[0m\1B[33m128| \1B[0m\1B[31m\1B[1m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[32m\1B[1m                                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m129| \1B[0m\1B[0m \0A\1B[0m\1B[33m130| \1B[0m\1B[0m    } else {\0A\1B[0m\1B[33m131| \1B[0m\1B[0m      var header_parts: str[100] = split(first_line, \22:\22)\0A\1B[0m\1B[33m132| \1B[0m\1B[0m      header_parts[1] = Str::trimInPlace(header_parts[1])\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 128:61\1B[31m \22Index out of bounds of 'parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@79 = private local_unnamed_addr global [2 x i8] c":\00"
@80 = private unnamed_addr constant [861 x i8] c"\0A\1B[33m128| \1B[0m\1B[0m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[33m129| \1B[0m\1B[0m \0A\1B[0m\1B[33m130| \1B[0m\1B[0m    } else {\0A\1B[0m\1B[33m131| \1B[0m\1B[0m      var header_parts: str[100] = split(first_line, \22:\22)\0A\1B[0m\1B[33m132| \1B[0m\1B[31m\1B[1m      header_parts[1] = Str::trimInPlace(header_parts[1])\0A\1B[0m\1B[32m\1B[1m                    \0A   ~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m133| \1B[0m\1B[0m      if (hasBody) {\0A\1B[0m\1B[33m134| \1B[0m\1B[0m        body = first_line \0A\1B[0m\1B[33m135| \1B[0m\1B[0m        print(\22firstLin\22, first_line)\0A\1B[0m\1B[33m136| \1B[0m\1B[0m        flush()\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 132:20\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@81 = private unnamed_addr constant [931 x i8] c"\0A\1B[33m128| \1B[0m\1B[0m      method, endpoint, version = parts[0], parts[1], parts[2]/; Headers start from the second line onwards\0A\1B[0m\1B[33m129| \1B[0m\1B[0m \0A\1B[0m\1B[33m130| \1B[0m\1B[0m    } else {\0A\1B[0m\1B[33m131| \1B[0m\1B[0m      var header_parts: str[100] = split(first_line, \22:\22)\0A\1B[0m\1B[33m132| \1B[0m\1B[31m\1B[1m      header_parts[1] = Str::trimInPlace(header_parts[1])\0A\1B[0m\1B[32m\1B[1m                                                       \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m133| \1B[0m\1B[0m      if (hasBody) {\0A\1B[0m\1B[33m134| \1B[0m\1B[0m        body = first_line \0A\1B[0m\1B[33m135| \1B[0m\1B[0m        print(\22firstLin\22, first_line)\0A\1B[0m\1B[33m136| \1B[0m\1B[0m        flush()\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 132:55\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@82 = private local_unnamed_addr global [9 x i8] c"firstLin\00"
@83 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s" = private constant ptr @83
@84 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.26" = private constant ptr @84
@85 = private unnamed_addr constant [826 x i8] c"\0A\1B[33m135| \1B[0m\1B[0m        print(\22firstLin\22, first_line)\0A\1B[0m\1B[33m136| \1B[0m\1B[0m        flush()\0A\1B[0m\1B[33m137| \1B[0m\1B[0m        break\0A\1B[0m\1B[33m138| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m139| \1B[0m\1B[31m\1B[1m      if header_parts[0] == \22Host\22 {\0A\1B[0m\1B[32m\1B[1m                       \0A   ~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m140| \1B[0m\1B[0m        header_map.Host = header_parts[1] \0A\1B[0m\1B[33m141| \1B[0m\1B[0m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 139:23\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@86 = private local_unnamed_addr global [5 x i8] c"Host\00"
@87 = private unnamed_addr constant [884 x i8] c"\0A\1B[33m137| \1B[0m\1B[0m        break\0A\1B[0m\1B[33m138| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m139| \1B[0m\1B[0m      if header_parts[0] == \22Host\22 {\0A\1B[0m\1B[33m140| \1B[0m\1B[0m        header_map.Host = header_parts[1] \0A\1B[0m\1B[33m141| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 141:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@88 = private local_unnamed_addr global [11 x i8] c"Connection\00"
@89 = private unnamed_addr constant [981 x i8] c"\0A\1B[33m139| \1B[0m\1B[0m      if header_parts[0] == \22Host\22 {\0A\1B[0m\1B[33m140| \1B[0m\1B[0m        header_map.Host = header_parts[1] \0A\1B[0m\1B[33m141| \1B[0m\1B[0m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 143:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@90 = private local_unnamed_addr global [10 x i8] c"sec-ch-ua\00"
@91 = private unnamed_addr constant [1021 x i8] c"\0A\1B[33m141| \1B[0m\1B[0m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 145:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@92 = private local_unnamed_addr global [17 x i8] c"sec-ch-ua-mobile\00"
@93 = private unnamed_addr constant [1043 x i8] c"\0A\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 147:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@94 = private local_unnamed_addr global [19 x i8] c"sec-ch-ua-platform\00"
@95 = private unnamed_addr constant [1041 x i8] c"\0A\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 149:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@96 = private local_unnamed_addr global [26 x i8] c"Upgrade-Insecure-Requests\00"
@97 = private unnamed_addr constant [1021 x i8] c"\0A\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 151:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@98 = private local_unnamed_addr global [11 x i8] c"User-Agent\00"
@99 = private unnamed_addr constant [1013 x i8] c"\0A\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 153:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@100 = private local_unnamed_addr global [7 x i8] c"Accept\00"
@101 = private unnamed_addr constant [984 x i8] c"\0A\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 155:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@102 = private local_unnamed_addr global [15 x i8] c"Sec-Fetch-Site\00"
@103 = private unnamed_addr constant [1000 x i8] c"\0A\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 157:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@104 = private local_unnamed_addr global [15 x i8] c"Sec-Fetch-Mode\00"
@105 = private unnamed_addr constant [1017 x i8] c"\0A\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 159:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@106 = private local_unnamed_addr global [15 x i8] c"Sec-Fetch-User\00"
@107 = private unnamed_addr constant [1019 x i8] c"\0A\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 161:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@108 = private local_unnamed_addr global [15 x i8] c"Sec-Fetch-Dest\00"
@109 = private unnamed_addr constant [1018 x i8] c"\0A\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 163:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@110 = private local_unnamed_addr global [16 x i8] c"Accept-Encoding\00"
@111 = private unnamed_addr constant [1008 x i8] c"\0A\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[33m169| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 165:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@112 = private local_unnamed_addr global [16 x i8] c"Accept-Language\00"
@113 = private unnamed_addr constant [1005 x i8] c"\0A\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[33m169| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[33m170| \1B[0m\1B[0m        header_map.content_length = Int32(header_parts[1]) + 0 \0A\1B[0m\1B[33m171| \1B[0m\1B[0m      } or if header_parts[0] == \22\22 {\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 167:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@114 = private local_unnamed_addr global [13 x i8] c"Content-Type\00"
@115 = private unnamed_addr constant [930 x i8] c"\0A\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[33m169| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m170| \1B[0m\1B[0m        header_map.content_length = Int32(header_parts[1]) + 0 \0A\1B[0m\1B[33m171| \1B[0m\1B[0m      } or if header_parts[0] == \22\22 {\0A\1B[0m\1B[33m172| \1B[0m\1B[0m        hasBody = true \0A\1B[0m\1B[33m173| \1B[0m\1B[0m      }\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 169:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@116 = private local_unnamed_addr global [15 x i8] c"Content-Length\00"
@117 = private unnamed_addr constant [833 x i8] c"\0A\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[33m169| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[33m170| \1B[0m\1B[0m        header_map.content_length = Int32(header_parts[1]) + 0 \0A\1B[0m\1B[33m171| \1B[0m\1B[31m\1B[1m      } or if header_parts[0] == \22\22 {\0A\1B[0m\1B[32m\1B[1m                            \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m172| \1B[0m\1B[0m        hasBody = true \0A\1B[0m\1B[33m173| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m174| \1B[0m\1B[0m    }\0A\1B[0m\1B[33m175| \1B[0m\1B[0m  }\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 171:28\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@118 = private local_unnamed_addr global [1 x i8] zeroinitializer
@119 = private unnamed_addr constant [870 x i8] c"\0A\1B[33m136| \1B[0m\1B[0m        flush()\0A\1B[0m\1B[33m137| \1B[0m\1B[0m        break\0A\1B[0m\1B[33m138| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m139| \1B[0m\1B[0m      if header_parts[0] == \22Host\22 {\0A\1B[0m\1B[33m140| \1B[0m\1B[31m\1B[1m        header_map.Host = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m141| \1B[0m\1B[0m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 140:40\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@120 = private unnamed_addr constant [969 x i8] c"\0A\1B[33m138| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m139| \1B[0m\1B[0m      if header_parts[0] == \22Host\22 {\0A\1B[0m\1B[33m140| \1B[0m\1B[0m        header_map.Host = header_parts[1] \0A\1B[0m\1B[33m141| \1B[0m\1B[0m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[33m142| \1B[0m\1B[31m\1B[1m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 142:46\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@121 = private unnamed_addr constant [1035 x i8] c"\0A\1B[33m140| \1B[0m\1B[0m        header_map.Host = header_parts[1] \0A\1B[0m\1B[33m141| \1B[0m\1B[0m      } or if header_parts[0] == \22Connection\22 {\0A\1B[0m\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[31m\1B[1m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                             \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 144:45\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@122 = private unnamed_addr constant [1092 x i8] c"\0A\1B[33m142| \1B[0m\1B[0m        header_map.Connection = header_parts[1] \0A\1B[0m\1B[33m143| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua\22 {\0A\1B[0m\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[31m\1B[1m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[32m\1B[1m                                                    \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 146:52\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@123 = private local_unnamed_addr global [3 x i8] c"?1\00"
@124 = private unnamed_addr constant [1097 x i8] c"\0A\1B[33m144| \1B[0m\1B[0m        header_map.sec_ch_ua = header_parts[1] \0A\1B[0m\1B[33m145| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-mobile\22 {\0A\1B[0m\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[31m\1B[1m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                      \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 148:54\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@125 = private unnamed_addr constant [1110 x i8] c"\0A\1B[33m146| \1B[0m\1B[0m        header_map.sec_ch_ua_mobile = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m147| \1B[0m\1B[0m      } or if header_parts[0] == \22sec-ch-ua-platform\22 {\0A\1B[0m\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[31m\1B[1m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[32m\1B[1m                                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 150:67\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@126 = private unnamed_addr constant [1054 x i8] c"\0A\1B[33m148| \1B[0m\1B[0m        header_map.sec_ch_ua_platform = header_parts[1] \0A\1B[0m\1B[33m149| \1B[0m\1B[0m      } or if header_parts[0] == \22Upgrade-Insecure-Requests\22 {\0A\1B[0m\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[31m\1B[1m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                              \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 152:46\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@127 = private unnamed_addr constant [1031 x i8] c"\0A\1B[33m150| \1B[0m\1B[0m        header_map.Upgrade_Insecure_Requests = Int32(header_parts[1]) \0A\1B[0m\1B[33m151| \1B[0m\1B[0m      } or if header_parts[0] == \22User-Agent\22 {\0A\1B[0m\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[31m\1B[1m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                          \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 154:42\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@128 = private unnamed_addr constant [1041 x i8] c"\0A\1B[33m152| \1B[0m\1B[0m        header_map.User_Agent = header_parts[1] \0A\1B[0m\1B[33m153| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept\22 {\0A\1B[0m\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[31m\1B[1m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 156:50\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@129 = private unnamed_addr constant [1053 x i8] c"\0A\1B[33m154| \1B[0m\1B[0m        header_map.Accept = header_parts[1] \0A\1B[0m\1B[33m155| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Site\22 {\0A\1B[0m\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[31m\1B[1m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 158:50\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@130 = private unnamed_addr constant [1063 x i8] c"\0A\1B[33m156| \1B[0m\1B[0m        header_map.Sec_Fetch_Site = header_parts[1] \0A\1B[0m\1B[33m157| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Mode\22 {\0A\1B[0m\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[31m\1B[1m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 160:50\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@131 = private local_unnamed_addr global [3 x i8] c"?1\00"
@132 = private unnamed_addr constant [1065 x i8] c"\0A\1B[33m158| \1B[0m\1B[0m        header_map.Sec_Fetch_Mode = header_parts[1] \0A\1B[0m\1B[33m159| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-User\22 {\0A\1B[0m\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[31m\1B[1m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                  \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 162:50\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@133 = private unnamed_addr constant [1063 x i8] c"\0A\1B[33m160| \1B[0m\1B[0m        header_map.Sec_Fetch_User = header_parts[1] == \22?1\22 \0A\1B[0m\1B[33m161| \1B[0m\1B[0m      } or if header_parts[0] == \22Sec-Fetch-Dest\22 {\0A\1B[0m\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[31m\1B[1m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 164:51\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@134 = private unnamed_addr constant [1066 x i8] c"\0A\1B[33m162| \1B[0m\1B[0m        header_map.Sec_Fetch_Dest = header_parts[1] \0A\1B[0m\1B[33m163| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Encoding\22 {\0A\1B[0m\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[31m\1B[1m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                   \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[33m169| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[33m170| \1B[0m\1B[0m        header_map.content_length = Int32(header_parts[1]) + 0 \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 166:51\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@135 = private unnamed_addr constant [1016 x i8] c"\0A\1B[33m164| \1B[0m\1B[0m        header_map.Accept_Encoding = header_parts[1] \0A\1B[0m\1B[33m165| \1B[0m\1B[0m      } or if header_parts[0] == \22Accept-Language\22 {\0A\1B[0m\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[31m\1B[1m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[32m\1B[1m                                                \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m169| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[33m170| \1B[0m\1B[0m        header_map.content_length = Int32(header_parts[1]) + 0 \0A\1B[0m\1B[33m171| \1B[0m\1B[0m      } or if header_parts[0] == \22\22 {\0A\1B[0m\1B[33m172| \1B[0m\1B[0m        hasBody = true \0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 168:48\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@136 = private unnamed_addr constant [939 x i8] c"\0A\1B[33m166| \1B[0m\1B[0m        header_map.Accept_Language = header_parts[1] \0A\1B[0m\1B[33m167| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Type\22 {\0A\1B[0m\1B[33m168| \1B[0m\1B[0m        header_map.content_type = header_parts[1] \0A\1B[0m\1B[33m169| \1B[0m\1B[0m      } or if header_parts[0] == \22Content-Length\22 {\0A\1B[0m\1B[33m170| \1B[0m\1B[31m\1B[1m        header_map.content_length = Int32(header_parts[1]) + 0 \0A\1B[0m\1B[32m\1B[1m                                                        \0A   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\1B[0m\0A\1B[33m171| \1B[0m\1B[0m      } or if header_parts[0] == \22\22 {\0A\1B[0m\1B[33m172| \1B[0m\1B[0m        hasBody = true \0A\1B[0m\1B[33m173| \1B[0m\1B[0m      }\0A\1B[0m\1B[33m174| \1B[0m\1B[0m    }\0A\1B[0m\1B[31mFile: server.fg [Error] : \1B[1;31mLine 170:56\1B[31m \22Index out of bounds of 'header_parts' in index expression, index value should be between 0 and 100\22\1B[0m\0A\1B[33mLocation: /Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server/server.fg\0A\1B[0m\00", align 1
@137 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@138 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@139 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@140 = private local_unnamed_addr global [11 x i8] c"endpoint: \00"
@141 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.27" = private constant ptr @141
@142 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.28" = private constant ptr @142
@143 = private local_unnamed_addr global [2 x i8] c"\0A\00"
@144 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.29" = private constant ptr @144
@145 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@146 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@"%s.30" = private constant ptr @146
@147 = private local_unnamed_addr global [14 x i8] c"Hello, World!\00"
@148 = private local_unnamed_addr global [7 x i8] c"200 OK\00"
@149 = private local_unnamed_addr global [11 x i8] c"text/plain\00"
@150 = private local_unnamed_addr global [4 x i8] c"GET\00"
@151 = private local_unnamed_addr global [6 x i8] c"/json\00"
@152 = private local_unnamed_addr global [4 x i8] c"GET\00"
@153 = private local_unnamed_addr global [2 x i8] c"/\00"
@154 = private local_unnamed_addr global [4 x i8] c"GET\00"
@155 = private local_unnamed_addr global [6 x i8] c"/text\00"
@156 = private local_unnamed_addr global [5 x i8] c"POST\00"
@157 = private local_unnamed_addr global [8 x i8] c"/submit\00"

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

declare i32 @putchar(i32)

define i32 @flowmain() {
entry:
  call void @"assign_<ObjectStr::ComparisonResult.0>"(ptr @"Str::comparisonResult")
  call void @"assign_<ObjectStr::ComparisonResult.0>"(ptr @"Str::comparisonResult")
  %0 = call i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-flow-wing-server-..-..-..-..-lib-mac-silicon-lib-modules-Str-module()
  %1 = call i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-flow-wing-server-..-..-..-..-lib-mac-silicon-lib-modules-Vec-module()
  call void @main()
  br label %returnBlock

returnBlock:                                      ; preds = %entry
  ret i32 0
}

declare !rt !0 void @"Vec::Int.init0"(ptr)

declare !rt !1 void @"Vec::Int.add"(ptr, ptr)

declare !rt !2 void @"Vec::Int.get"(ptr, ptr, ptr)

declare !rt !3 void @"Vec::Int.remove"(ptr, ptr)

declare !rt !4 void @"Vec::Int.size"(ptr, ptr)

declare !rt !5 void @"Vec::Int.free"(ptr)

declare !rt !6 void @"Vec::Bool.init0"(ptr)

declare !rt !7 void @"Vec::Bool.add"(ptr, ptr)

declare !rt !8 void @"Vec::Bool.get"(ptr, ptr, ptr)

declare !rt !9 void @"Vec::Bool.remove"(ptr, ptr)

declare !rt !10 void @"Vec::Bool.size"(ptr, ptr)

declare !rt !11 void @"Vec::Bool.free"(ptr)

declare !rt !12 void @"Vec::String.init0"(ptr)

declare !rt !13 void @"Vec::String.add"(ptr, ptr)

declare !rt !14 void @"Vec::String.get"(ptr, ptr, ptr)

declare !rt !15 void @"Vec::String.remove"(ptr, ptr)

declare !rt !16 void @"Vec::String.size"(ptr, ptr)

declare !rt !17 void @"Vec::String.free"(ptr)

declare !rt !18 void @"Vec::Deci.init0"(ptr)

declare !rt !19 void @"Vec::Deci.add"(ptr, ptr)

declare !rt !20 void @"Vec::Deci.get"(ptr, ptr, ptr)

declare !rt !21 void @"Vec::Deci.remove"(ptr, ptr)

declare !rt !22 void @"Vec::Deci.size"(ptr, ptr)

declare !rt !23 void @"Vec::Deci.free"(ptr)

declare i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-flow-wing-server-..-..-..-..-lib-mac-silicon-lib-modules-Str-module()

define internal void @"assign_<ObjectStr::ComparisonResult.0>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Str::ComparisonResult.0", ptr %0, i32 0, i32 0
  store i32 0, ptr %1, align 4
  %2 = getelementptr inbounds %"Str::ComparisonResult.0", ptr %0, i32 0, i32 1
  store i32 0, ptr %2, align 4
  %3 = getelementptr inbounds %"Str::ComparisonResult.0", ptr %0, i32 0, i32 2
  store i32 0, ptr %3, align 4
  ret void
}

declare !rt !24 void @"Str::charAt"(ptr, ptr, ptr)

declare !rt !25 void @"Str::indexOfChar"(ptr, ptr, ptr)

declare !rt !26 void @"Str::trimInPlace"(ptr, ptr)

declare !rt !27 void @"Str::subStrIndex"(ptr, ptr, ptr)

declare !rt !28 void @"Str::reverseInPlace"(ptr)

declare !rt !29 ptr @strFindChar(ptr, i32)

declare !rt !30 void @"Str::replaceInPlace"(ptr, ptr, ptr, ptr)

declare !rt !31 void @"Str::subStr"(ptr, ptr, ptr)

declare !rt !32 void @"Str::reverse"(ptr, ptr)

declare !rt !33 void @"Str::length"(ptr, ptr)

declare !rt !34 void @"Str::compare"(ptr, ptr, ptr, ptr)

declare !rt !35 void @"Str::concat"(ptr, ptr, ptr)

declare !rt !36 void @"Str::makeCopy"(ptr, ptr)

declare !rt !37 ptr @strToLower(ptr)

declare !rt !38 ptr @strReverse(ptr)

declare !rt !39 ptr @strFind(ptr, ptr)

declare !rt !40 i32 @strCompare(ptr, ptr)

declare !rt !41 ptr @strTrim(ptr)

declare !rt !42 void @"Str::toLower"(ptr, ptr)

declare !rt !43 ptr @int8ToStr(i8, ptr)

declare !rt !44 i32 @strLength(ptr)

declare !rt !45 void @"Str::int8ToString"(ptr, ptr)

declare !rt !46 ptr @strCharAt(ptr, i32)

declare !rt !47 ptr @strToUpper(ptr)

declare !rt !48 void @"Str::toUpper"(ptr, ptr)

declare !rt !49 ptr @strReplace(ptr, ptr, ptr)

declare !rt !50 void @strCopy(ptr, ptr)

declare i32 @-Users-apple-code-per-Flow-Wing-docs-local-modules-flow-wing-server-..-..-..-..-lib-mac-silicon-lib-modules-Vec-module()

declare !rt !21 void @"Vec::Deci.remove.1"(ptr, ptr)

declare !rt !51 void @string_vector_add(ptr, ptr)

declare !rt !16 void @"Vec::String.size.2"(ptr, ptr)

declare !rt !23 void @"Vec::Deci.free.3"(ptr)

declare !rt !15 void @"Vec::String.remove.4"(ptr, ptr)

declare !rt !14 void @"Vec::String.get.5"(ptr, ptr, ptr)

declare !rt !13 void @"Vec::String.add.6"(ptr, ptr)

declare !rt !11 void @"Vec::Bool.free.7"(ptr)

declare !rt !3 void @"Vec::Int.remove.8"(ptr, ptr)

declare !rt !17 void @"Vec::String.free.9"(ptr)

declare !rt !7 void @"Vec::Bool.add.10"(ptr, ptr)

declare !rt !2 void @"Vec::Int.get.11"(ptr, ptr, ptr)

declare !rt !52 void @int_vector_free(ptr)

declare !rt !1 void @"Vec::Int.add.12"(ptr, ptr)

declare !rt !8 void @"Vec::Bool.get.13"(ptr, ptr, ptr)

declare !rt !0 void @"Vec::Int.init0.14"(ptr)

declare !rt !53 void @double_vector_free(ptr)

declare !rt !54 ptr @int_vector_new()

declare !rt !9 void @"Vec::Bool.remove.15"(ptr, ptr)

declare !rt !5 void @"Vec::Int.free.16"(ptr)

declare !rt !55 void @double_vector_remove(ptr, i32)

declare !rt !56 ptr @double_vector_new()

declare !rt !6 void @"Vec::Bool.init0.17"(ptr)

declare !rt !57 void @string_vector_free(ptr)

declare !rt !4 void @"Vec::Int.size.18"(ptr, ptr)

declare !rt !18 void @"Vec::Deci.init0.19"(ptr)

declare !rt !20 void @"Vec::Deci.get.20"(ptr, ptr, ptr)

declare !rt !58 double @double_vector_get(ptr, i32)

declare !rt !10 void @"Vec::Bool.size.21"(ptr, ptr)

declare !rt !59 i32 @string_vector_size(ptr)

declare !rt !60 i32 @bool_vector_size(ptr)

declare !rt !61 void @string_vector_remove(ptr, i32)

declare !rt !62 void @double_vector_add(ptr, double)

declare !rt !12 void @"Vec::String.init0.22"(ptr)

declare !rt !63 void @bool_vector_free(ptr)

declare !rt !64 void @int_vector_remove(ptr, i32)

declare !rt !22 void @"Vec::Deci.size.23"(ptr, ptr)

declare !rt !65 void @bool_vector_remove(ptr, i32)

declare !rt !66 ptr @string_vector_get(ptr, i32)

declare !rt !67 i32 @int_vector_size(ptr)

declare !rt !68 void @bool_vector_add(ptr, i1)

declare !rt !69 ptr @string_vector_new()

declare !rt !70 ptr @bool_vector_new()

declare !rt !19 void @"Vec::Deci.add.24"(ptr, ptr)

declare !rt !71 i32 @double_vector_size(ptr)

declare !rt !72 i1 @bool_vector_get(ptr, i32)

declare !rt !73 i32 @int_vector_get(ptr, i32)

declare !rt !74 void @int_vector_add(ptr, i32)

declare !rt !75 void @start_server()

declare !rt !76 void @flush()

declare !rt !77 void @set_route(ptr, ptr, ptr)

declare !rt !78 void @set_middleware(ptr)

declare !rt !79 void @send_response(i32, ptr, ptr, ptr)

declare !rt !80 void @send(i32, ptr, i32, i32)

declare !rt !81 i32 @strlen(ptr)

define i32 @len(ptr %0) !rt !82 {
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

define ptr @generate_response(ptr %0, ptr %1) !rt !83 {
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
  %6 = call i32 @len(ptr %5)
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

define void @json_response(ptr %0, ptr %1) !rt !84 {
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
  %3 = call i32 @len(ptr %2)
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

define void @my_request_handler(i32 %0, ptr %1, ptr %2) !rt !85 {
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

define void @split(ptr %0, ptr %1, ptr %2) !rt !86 {
entry:
  %s = alloca ptr, align 8
  %3 = load ptr, ptr %1, align 8
  store ptr %3, ptr %s, align 8
  %delimiter = alloca ptr, align 8
  %4 = load ptr, ptr %2, align 8
  store ptr %4, ptr %delimiter, align 8
  %result = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %result)
  %part = alloca ptr, align 8
  store ptr @39, ptr %part, align 8
  %j = alloca i32, align 4
  store i32 0, ptr %j, align 4
  %i = alloca %DynamicType, align 8
  %rtPtr = alloca i32, align 4
  %rtPtr1 = alloca ptr, align 8
  %5 = alloca i8, align 1
  %rtPtr2 = alloca i32, align 4
  %rtPtr3 = alloca i32, align 4
  %rtPtr4 = alloca ptr, align 8
  %6 = alloca i8, align 1
  %rtPtr5 = alloca ptr, align 8
  %7 = alloca i8, align 1
  %rtPtr6 = alloca i32, align 4
  %rtPtr7 = alloca ptr, align 8
  %8 = alloca i8, align 1
  %9 = alloca i8, align 1
  %10 = alloca i8, align 1
  %11 = alloca i8, align 1
  %12 = alloca i8, align 1
  %13 = alloca i8, align 1
  %14 = alloca i8, align 1
  %15 = alloca i8, align 1
  %16 = alloca i8, align 1
  %rtPtr8 = alloca i32, align 4
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock18, %mergeBlock, %checkContinueBlock16, %afterIfElse85, %checkContinueBlock14, %end_block81, %checkContinueBlock12, %nestedBlock11, %checkContinueBlock10, %nestedBlock9, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %17 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %19 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock
  store ptr @40, ptr %part, align 8
  %21 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  %23 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %nestedBlock11, label %afterNestedBlock

nestedBlock11:                                    ; preds = %checkContinueBlock10
  store i32 0, ptr %j, align 4
  %25 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %checkContinueBlock12, label %afterNestedBlock

checkContinueBlock12:                             ; preds = %nestedBlock11
  %27 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %nestedBlock13, label %afterNestedBlock

nestedBlock13:                                    ; preds = %checkContinueBlock12
  %s19 = load ptr, ptr %s, align 8
  call void @"Str::length"(ptr %rtPtr, ptr %s)
  %29 = load i32, ptr %rtPtr, align 4
  %30 = sub i32 %29, 1
  %31 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %31, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock14:                             ; preds = %end_block81
  %32 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock15, label %afterNestedBlock

nestedBlock15:                                    ; preds = %checkContinueBlock14
  %part82 = load ptr, ptr %part, align 8
  call void @"Str::length"(ptr %rtPtr8, ptr %part)
  %34 = load i32, ptr %rtPtr8, align 4
  %35 = icmp sgt i32 %34, 0
  br i1 %35, label %then83, label %else84

checkContinueBlock16:                             ; preds = %afterIfElse85
  %36 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %nestedBlock17, label %afterNestedBlock

nestedBlock17:                                    ; preds = %checkContinueBlock16
  br label %returnBlock

checkContinueBlock18:                             ; preds = %mergeBlock
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock20, %nestedBlock13
  %38 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock21

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %40 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %end_block81, label %decrement_block80

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %42 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %44 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %45 = sub i32 %44, 1
  store i32 %45, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %46 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %47 = load i32, ptr %46, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %48 = icmp sge i32 %47, %30
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %49 = icmp sle i32 %47, %30
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %50 = phi i1 [ %48, %"ForLoop::Conditon::trueBlock" ], [ %49, %"ForLoop::Conditon::falseBlock" ]
  br i1 %50, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock20:                               ; preds = %checkContinueBlock22, %afterIfElse
  %51 = add i32 %47, 1
  store i32 %51, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock21:                                    ; preds = %"ForLoop::loopBody"
  %52 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %53 = load i32, ptr %52, align 4
  %54 = load ptr, ptr %s, align 8
  %arrayInx = getelementptr inbounds i8, ptr %54, i32 %53
  %55 = load i8, ptr %arrayInx, align 1
  store i8 %55, ptr %13, align 1
  call void @"Str::int8ToString"(ptr %rtPtr1, ptr %13)
  %56 = load ptr, ptr %rtPtr1, align 8
  %delimiter23 = load ptr, ptr %delimiter, align 8
  %57 = load ptr, ptr %delimiter, align 8
  %58 = call i1 @equal_strings(ptr %56, ptr %57)
  %59 = select i1 %58, i1 true, i1 false
  br i1 %59, label %then, label %orIf0

checkContinueBlock22:                             ; preds = %afterIfElse
  br label %afterNestedBlock20

then:                                             ; preds = %nestedBlock21
  br label %nestedBlock29

orIf0:                                            ; preds = %nestedBlock21
  %60 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %61 = load i32, ptr %60, align 4
  %62 = add i32 %61, 1
  %s24 = load ptr, ptr %s, align 8
  call void @"Str::length"(ptr %rtPtr3, ptr %s)
  %63 = load i32, ptr %rtPtr3, align 4
  %64 = icmp slt i32 %62, %63
  %65 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %66 = load i32, ptr %65, align 4
  %67 = load ptr, ptr %s, align 8
  %arrayInx25 = getelementptr inbounds i8, ptr %67, i32 %66
  %68 = load i8, ptr %arrayInx25, align 1
  store i8 %68, ptr %14, align 1
  call void @"Str::int8ToString"(ptr %rtPtr4, ptr %14)
  %69 = load ptr, ptr %rtPtr4, align 8
  %70 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %71 = load i32, ptr %70, align 4
  %72 = add i32 %71, 1
  %73 = load ptr, ptr %s, align 8
  %arrayInx26 = getelementptr inbounds i8, ptr %73, i32 %72
  %74 = load i8, ptr %arrayInx26, align 1
  store i8 %74, ptr %15, align 1
  call void @"Str::int8ToString"(ptr %rtPtr5, ptr %15)
  %75 = load ptr, ptr %rtPtr5, align 8
  %76 = call ptr @concat_strings(ptr %69, ptr %75)
  %delimiter27 = load ptr, ptr %delimiter, align 8
  %77 = load ptr, ptr %delimiter, align 8
  %78 = call i1 @equal_strings(ptr %76, ptr %77)
  %79 = select i1 %78, i1 true, i1 false
  %80 = select i1 %64, i1 %79, i1 false
  br i1 %80, label %orIfThen0, label %else

orIfThen0:                                        ; preds = %orIf0
  br label %nestedBlock48

else:                                             ; preds = %orIf0
  br label %nestedBlock75

afterIfElse:                                      ; preds = %afterNestedBlock74, %afterNestedBlock47, %afterNestedBlock28
  %81 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock22, label %afterNestedBlock20

afterNestedBlock28:                               ; preds = %checkContinueBlock32, %nestedBlock31, %checkContinueBlock30, %afterIfElse36
  br label %afterIfElse

nestedBlock29:                                    ; preds = %then
  %part33 = load ptr, ptr %part, align 8
  call void @"Str::length"(ptr %rtPtr2, ptr %part)
  %83 = load i32, ptr %rtPtr2, align 4
  %84 = icmp ne i32 %83, 0
  br i1 %84, label %then34, label %else35

checkContinueBlock30:                             ; preds = %afterIfElse36
  %85 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %86 = icmp eq i32 %85, 0
  br i1 %86, label %nestedBlock31, label %afterNestedBlock28

nestedBlock31:                                    ; preds = %checkContinueBlock30
  %part46 = load ptr, ptr %part, align 8
  store ptr @42, ptr %part, align 8
  %87 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %88 = icmp eq i32 %87, 0
  br i1 %88, label %checkContinueBlock32, label %afterNestedBlock28

checkContinueBlock32:                             ; preds = %nestedBlock31
  br label %afterNestedBlock28

then34:                                           ; preds = %nestedBlock29
  br label %nestedBlock38

else35:                                           ; preds = %nestedBlock29
  br label %afterIfElse36

afterIfElse36:                                    ; preds = %else35, %afterNestedBlock37
  %89 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %90 = icmp eq i32 %89, 0
  br i1 %90, label %checkContinueBlock30, label %afterNestedBlock28

afterNestedBlock37:                               ; preds = %checkContinueBlock41, %nestedBlock40, %checkContinueBlock39, %"GlobalIndexExpr::merge"
  br label %afterIfElse36

nestedBlock38:                                    ; preds = %then34
  %j42 = load i32, ptr %j, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %j42, 100
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %j42, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock39:                             ; preds = %"GlobalIndexExpr::merge"
  %91 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %92 = icmp eq i32 %91, 0
  br i1 %92, label %nestedBlock40, label %afterNestedBlock37

nestedBlock40:                                    ; preds = %checkContinueBlock39
  %j44 = load i32, ptr %j, align 4
  %j45 = load i32, ptr %j, align 4
  %93 = load i32, ptr %j, align 4
  %94 = add i32 %93, 1
  store i32 %94, ptr %j, align 4
  %95 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %96 = icmp eq i32 %95, 0
  br i1 %96, label %checkContinueBlock41, label %afterNestedBlock37

checkContinueBlock41:                             ; preds = %nestedBlock40
  br label %afterNestedBlock37

"GlobalIndexExpr::then":                          ; preds = %nestedBlock38
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock38
  call void @raise_exception(ptr @41)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %97 = getelementptr [100 x ptr], ptr %result, i32 0, i32 %j42
  %98 = load ptr, ptr %97, align 8
  %part43 = load ptr, ptr %part, align 8
  %99 = load ptr, ptr %part, align 8
  store ptr %99, ptr %97, align 8
  %100 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %checkContinueBlock39, label %afterNestedBlock37

afterNestedBlock47:                               ; preds = %checkContinueBlock53, %nestedBlock52, %checkContinueBlock51, %nestedBlock50, %checkContinueBlock49, %afterIfElse57
  br label %afterIfElse

nestedBlock48:                                    ; preds = %orIfThen0
  %part54 = load ptr, ptr %part, align 8
  call void @"Str::length"(ptr %rtPtr6, ptr %part)
  %102 = load i32, ptr %rtPtr6, align 4
  %103 = icmp ne i32 %102, 0
  br i1 %103, label %then55, label %else56

checkContinueBlock49:                             ; preds = %afterIfElse57
  %104 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %105 = icmp eq i32 %104, 0
  br i1 %105, label %nestedBlock50, label %afterNestedBlock47

nestedBlock50:                                    ; preds = %checkContinueBlock49
  %106 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %107 = load i32, ptr %106, align 4
  %108 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %109 = load i32, ptr %108, align 4
  %110 = add i32 %109, 1
  %111 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 %110, ptr %111, align 4
  %112 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %113 = icmp eq i32 %112, 0
  br i1 %113, label %checkContinueBlock51, label %afterNestedBlock47

checkContinueBlock51:                             ; preds = %nestedBlock50
  %114 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %115 = icmp eq i32 %114, 0
  br i1 %115, label %nestedBlock52, label %afterNestedBlock47

nestedBlock52:                                    ; preds = %checkContinueBlock51
  %part73 = load ptr, ptr %part, align 8
  store ptr @44, ptr %part, align 8
  %116 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %117 = icmp eq i32 %116, 0
  br i1 %117, label %checkContinueBlock53, label %afterNestedBlock47

checkContinueBlock53:                             ; preds = %nestedBlock52
  br label %afterNestedBlock47

then55:                                           ; preds = %nestedBlock48
  br label %nestedBlock59

else56:                                           ; preds = %nestedBlock48
  br label %afterIfElse57

afterIfElse57:                                    ; preds = %else56, %afterNestedBlock58
  %118 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %119 = icmp eq i32 %118, 0
  br i1 %119, label %checkContinueBlock49, label %afterNestedBlock47

afterNestedBlock58:                               ; preds = %checkContinueBlock62, %nestedBlock61, %checkContinueBlock60, %"GlobalIndexExpr::merge66"
  br label %afterIfElse57

nestedBlock59:                                    ; preds = %then55
  %j63 = load i32, ptr %j, align 4
  %"GlobalIndexExpr::isLessThan67" = icmp slt i32 %j63, 100
  %"GlobalIndexExpr::isGreaterThan68" = icmp sge i32 %j63, 0
  %"GlobalIndexExpr::isWithinBounds69" = and i1 %"GlobalIndexExpr::isLessThan67", %"GlobalIndexExpr::isGreaterThan68"
  br i1 %"GlobalIndexExpr::isWithinBounds69", label %"GlobalIndexExpr::then64", label %"GlobalIndexExpr::else65"

checkContinueBlock60:                             ; preds = %"GlobalIndexExpr::merge66"
  %120 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %121 = icmp eq i32 %120, 0
  br i1 %121, label %nestedBlock61, label %afterNestedBlock58

nestedBlock61:                                    ; preds = %checkContinueBlock60
  %j71 = load i32, ptr %j, align 4
  %j72 = load i32, ptr %j, align 4
  %122 = load i32, ptr %j, align 4
  %123 = add i32 %122, 1
  store i32 %123, ptr %j, align 4
  %124 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %125 = icmp eq i32 %124, 0
  br i1 %125, label %checkContinueBlock62, label %afterNestedBlock58

checkContinueBlock62:                             ; preds = %nestedBlock61
  br label %afterNestedBlock58

"GlobalIndexExpr::then64":                        ; preds = %nestedBlock59
  br label %"GlobalIndexExpr::merge66"

"GlobalIndexExpr::else65":                        ; preds = %nestedBlock59
  call void @raise_exception(ptr @43)
  br label %"GlobalIndexExpr::merge66"

"GlobalIndexExpr::merge66":                       ; preds = %"GlobalIndexExpr::else65", %"GlobalIndexExpr::then64"
  %126 = getelementptr [100 x ptr], ptr %result, i32 0, i32 %j63
  %127 = load ptr, ptr %126, align 8
  %part70 = load ptr, ptr %part, align 8
  %128 = load ptr, ptr %part, align 8
  store ptr %128, ptr %126, align 8
  %129 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %130 = icmp eq i32 %129, 0
  br i1 %130, label %checkContinueBlock60, label %afterNestedBlock58

afterNestedBlock74:                               ; preds = %checkContinueBlock76, %nestedBlock75
  br label %afterIfElse

nestedBlock75:                                    ; preds = %else
  %part77 = load ptr, ptr %part, align 8
  %part78 = load ptr, ptr %part, align 8
  %131 = load ptr, ptr %part, align 8
  %132 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %133 = load i32, ptr %132, align 4
  %134 = load ptr, ptr %s, align 8
  %arrayInx79 = getelementptr inbounds i8, ptr %134, i32 %133
  %135 = load i8, ptr %arrayInx79, align 1
  store i8 %135, ptr %16, align 1
  call void @"Str::int8ToString"(ptr %rtPtr7, ptr %16)
  %136 = load ptr, ptr %rtPtr7, align 8
  %137 = call ptr @concat_strings(ptr %131, ptr %136)
  store ptr %137, ptr %part, align 8
  %138 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %139 = icmp eq i32 %138, 0
  br i1 %139, label %checkContinueBlock76, label %afterNestedBlock74

checkContinueBlock76:                             ; preds = %nestedBlock75
  br label %afterNestedBlock74

decrement_block80:                                ; preds = %"ForLoop::afterLoop"
  %140 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %141 = sub i32 %140, 1
  store i32 %141, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block81

end_block81:                                      ; preds = %decrement_block80, %"ForLoop::afterLoop"
  %142 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %143 = icmp eq i32 %142, 0
  br i1 %143, label %checkContinueBlock14, label %afterNestedBlock

then83:                                           ; preds = %nestedBlock15
  br label %nestedBlock87

else84:                                           ; preds = %nestedBlock15
  br label %afterIfElse85

afterIfElse85:                                    ; preds = %else84, %afterNestedBlock86
  %144 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %145 = icmp eq i32 %144, 0
  br i1 %145, label %checkContinueBlock16, label %afterNestedBlock

afterNestedBlock86:                               ; preds = %checkContinueBlock88, %"GlobalIndexExpr::merge92"
  br label %afterIfElse85

nestedBlock87:                                    ; preds = %then83
  %j89 = load i32, ptr %j, align 4
  %"GlobalIndexExpr::isLessThan93" = icmp slt i32 %j89, 100
  %"GlobalIndexExpr::isGreaterThan94" = icmp sge i32 %j89, 0
  %"GlobalIndexExpr::isWithinBounds95" = and i1 %"GlobalIndexExpr::isLessThan93", %"GlobalIndexExpr::isGreaterThan94"
  br i1 %"GlobalIndexExpr::isWithinBounds95", label %"GlobalIndexExpr::then90", label %"GlobalIndexExpr::else91"

checkContinueBlock88:                             ; preds = %"GlobalIndexExpr::merge92"
  br label %afterNestedBlock86

"GlobalIndexExpr::then90":                        ; preds = %nestedBlock87
  br label %"GlobalIndexExpr::merge92"

"GlobalIndexExpr::else91":                        ; preds = %nestedBlock87
  call void @raise_exception(ptr @45)
  br label %"GlobalIndexExpr::merge92"

"GlobalIndexExpr::merge92":                       ; preds = %"GlobalIndexExpr::else91", %"GlobalIndexExpr::then90"
  %146 = getelementptr [100 x ptr], ptr %result, i32 0, i32 %j89
  %147 = load ptr, ptr %146, align 8
  %part96 = load ptr, ptr %part, align 8
  %148 = load ptr, ptr %part, align 8
  store ptr %148, ptr %146, align 8
  %149 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %150 = icmp eq i32 %149, 0
  br i1 %150, label %checkContinueBlock88, label %afterNestedBlock86

returnBlock:                                      ; preds = %nestedBlock17
  %151 = load [100 x ptr], ptr %result, align 8
  store [100 x ptr] %151, ptr %0, align 8
  ret void

mergeBlock:                                       ; No predecessors!
  %152 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %153 = icmp eq i32 %152, 0
  br i1 %153, label %checkContinueBlock18, label %afterNestedBlock
}

define void @parse_request(ptr sret(%HttpRequest.2) %0, ptr %1) {
entry:
  %req_str = alloca ptr, align 8
  store ptr %1, ptr %req_str, align 8
  %lines = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %lines)
  %2 = alloca ptr, align 8
  %method = alloca ptr, align 8
  store ptr @46, ptr %method, align 8
  %endpoint = alloca ptr, align 8
  store ptr @47, ptr %endpoint, align 8
  %version = alloca ptr, align 8
  store ptr @48, ptr %version, align 8
  %method1 = alloca ptr, align 8
  store ptr @49, ptr %method1, align 8
  %endpoint2 = alloca ptr, align 8
  store ptr @50, ptr %endpoint2, align 8
  %version3 = alloca ptr, align 8
  store ptr @51, ptr %version3, align 8
  %body = alloca ptr, align 8
  store ptr @52, ptr %body, align 8
  %hasBody = alloca %DynamicType, align 8
  %header_map = alloca %Header.1, align 8
  call void @"assign_<ObjectHeader.1>"(ptr %header_map)
  %i = alloca %DynamicType, align 8
  %sublines = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %sublines)
  %3 = alloca ptr, align 8
  %first_line = alloca ptr, align 8
  store ptr @67, ptr %first_line, align 8
  %parts = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %parts)
  %4 = alloca ptr, align 8
  %header_parts = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %header_parts)
  %5 = alloca ptr, align 8
  %rtPtr = alloca ptr, align 8
  %parts4 = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %parts4)
  %6 = alloca ptr, align 8
  %header_parts5 = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %header_parts5)
  %7 = alloca ptr, align 8
  %parts6 = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %parts6)
  %8 = alloca ptr, align 8
  %header_parts7 = alloca [100 x ptr], align 8
  call void @"assign_<Array[100]<'String'>>:100,"(ptr %header_parts7)
  %9 = alloca ptr, align 8
  %clPtr = alloca ptr, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock19, %mergeBlock, %checkContinueBlock17, %end_block248, %checkContinueBlock15, %nestedBlock14, %checkContinueBlock13, %nestedBlock12, %checkContinueBlock11, %nestedBlock10, %checkContinueBlock9, %nestedBlock8, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %req_str20 = load ptr, ptr %req_str, align 8
  store ptr @68, ptr %2, align 8
  call void @split(ptr %lines, ptr %req_str, ptr %2)
  %10 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %12 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %nestedBlock8, label %afterNestedBlock

nestedBlock8:                                     ; preds = %checkContinueBlock
  %14 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %checkContinueBlock9, label %afterNestedBlock

checkContinueBlock9:                              ; preds = %nestedBlock8
  %16 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %nestedBlock10, label %afterNestedBlock

nestedBlock10:                                    ; preds = %checkContinueBlock9
  %18 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %checkContinueBlock11, label %afterNestedBlock

checkContinueBlock11:                             ; preds = %nestedBlock10
  %20 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %nestedBlock12, label %afterNestedBlock

nestedBlock12:                                    ; preds = %checkContinueBlock11
  %22 = getelementptr inbounds %DynamicType, ptr %hasBody, i32 0, i32 2
  store i1 false, ptr %22, align 1
  %23 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %checkContinueBlock13, label %afterNestedBlock

checkContinueBlock13:                             ; preds = %nestedBlock12
  %25 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %nestedBlock14, label %afterNestedBlock

nestedBlock14:                                    ; preds = %checkContinueBlock13
  %27 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %checkContinueBlock15, label %afterNestedBlock

checkContinueBlock15:                             ; preds = %nestedBlock14
  %29 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %nestedBlock16, label %afterNestedBlock

nestedBlock16:                                    ; preds = %checkContinueBlock15
  %31 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  store i32 0, ptr %31, align 4
  br label %"ForLoop::loopCondition"

checkContinueBlock17:                             ; preds = %end_block248
  %32 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %33 = icmp eq i32 %32, 0
  br i1 %33, label %nestedBlock18, label %afterNestedBlock

nestedBlock18:                                    ; preds = %checkContinueBlock17
  br label %returnBlock

checkContinueBlock19:                             ; preds = %mergeBlock
  br label %afterNestedBlock

"ForLoop::loopCondition":                         ; preds = %afterNestedBlock21, %nestedBlock16
  %34 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %end_block, label %decrement_block

"ForLoop::loopBody":                              ; preds = %"ForLoop::breakLoop"
  br label %nestedBlock22

"ForLoop::afterLoop":                             ; preds = %"ForLoop::breakLoop", %"ForLoop::Conditon::mergeBlock"
  %36 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %end_block248, label %decrement_block247

"ForLoop::breakLoop":                             ; preds = %"ForLoop::Conditon::mergeBlock"
  %38 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %"ForLoop::loopBody", label %"ForLoop::afterLoop"

decrement_block:                                  ; preds = %"ForLoop::loopCondition"
  %40 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %41 = sub i32 %40, 1
  store i32 %41, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  br label %end_block

end_block:                                        ; preds = %decrement_block, %"ForLoop::loopCondition"
  %42 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %43 = load i32, ptr %42, align 4
  br i1 false, label %"ForLoop::Conditon::trueBlock", label %"ForLoop::Conditon::falseBlock"

"ForLoop::Conditon::trueBlock":                   ; preds = %end_block
  %44 = icmp sge i32 %43, 99
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::falseBlock":                  ; preds = %end_block
  %45 = icmp sle i32 %43, 99
  br label %"ForLoop::Conditon::mergeBlock"

"ForLoop::Conditon::mergeBlock":                  ; preds = %"ForLoop::Conditon::falseBlock", %"ForLoop::Conditon::trueBlock"
  %46 = phi i1 [ %44, %"ForLoop::Conditon::trueBlock" ], [ %45, %"ForLoop::Conditon::falseBlock" ]
  br i1 %46, label %"ForLoop::breakLoop", label %"ForLoop::afterLoop"

afterNestedBlock21:                               ; preds = %checkContinueBlock29, %afterIfElse, %checkContinueBlock27, %"GlobalIndexExpr::merge44", %checkContinueBlock25, %"GlobalIndexExpr::merge38", %checkContinueBlock23, %"GlobalIndexExpr::merge32"
  %47 = add i32 %43, 1
  store i32 %47, ptr %i, align 4
  br label %"ForLoop::loopCondition"

nestedBlock22:                                    ; preds = %"ForLoop::loopBody"
  %48 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %49 = load i32, ptr %48, align 4
  %"GlobalIndexExpr::isLessThan" = icmp slt i32 %49, 100
  %"GlobalIndexExpr::isGreaterThan" = icmp sge i32 %49, 0
  %"GlobalIndexExpr::isWithinBounds" = and i1 %"GlobalIndexExpr::isLessThan", %"GlobalIndexExpr::isGreaterThan"
  br i1 %"GlobalIndexExpr::isWithinBounds", label %"GlobalIndexExpr::then", label %"GlobalIndexExpr::else"

checkContinueBlock23:                             ; preds = %"GlobalIndexExpr::merge32"
  %50 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %51 = icmp eq i32 %50, 0
  br i1 %51, label %nestedBlock24, label %afterNestedBlock21

nestedBlock24:                                    ; preds = %checkContinueBlock23
  %52 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %53 = load i32, ptr %52, align 4
  %"GlobalIndexExpr::isLessThan39" = icmp slt i32 %53, 100
  %"GlobalIndexExpr::isGreaterThan40" = icmp sge i32 %53, 0
  %"GlobalIndexExpr::isWithinBounds41" = and i1 %"GlobalIndexExpr::isLessThan39", %"GlobalIndexExpr::isGreaterThan40"
  br i1 %"GlobalIndexExpr::isWithinBounds41", label %"GlobalIndexExpr::then36", label %"GlobalIndexExpr::else37"

checkContinueBlock25:                             ; preds = %"GlobalIndexExpr::merge38"
  %54 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %55 = icmp eq i32 %54, 0
  br i1 %55, label %nestedBlock26, label %afterNestedBlock21

nestedBlock26:                                    ; preds = %checkContinueBlock25
  br i1 true, label %"GlobalIndexExpr::then42", label %"GlobalIndexExpr::else43"

checkContinueBlock27:                             ; preds = %"GlobalIndexExpr::merge44"
  %56 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %nestedBlock28, label %afterNestedBlock21

nestedBlock28:                                    ; preds = %checkContinueBlock27
  %58 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %59 = load i32, ptr %58, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %then, label %else

checkContinueBlock29:                             ; preds = %afterIfElse
  br label %afterNestedBlock21

"GlobalIndexExpr::then":                          ; preds = %nestedBlock22
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::else":                          ; preds = %nestedBlock22
  call void @raise_exception(ptr @69)
  br label %"GlobalIndexExpr::merge"

"GlobalIndexExpr::merge":                         ; preds = %"GlobalIndexExpr::else", %"GlobalIndexExpr::then"
  %61 = getelementptr [100 x ptr], ptr %lines, i32 0, i32 %49
  %62 = load ptr, ptr %61, align 8
  %63 = getelementptr inbounds %DynamicType, ptr %i, i32 0, i32 0
  %64 = load i32, ptr %63, align 4
  %"GlobalIndexExpr::isLessThan33" = icmp slt i32 %64, 100
  %"GlobalIndexExpr::isGreaterThan34" = icmp sge i32 %64, 0
  %"GlobalIndexExpr::isWithinBounds35" = and i1 %"GlobalIndexExpr::isLessThan33", %"GlobalIndexExpr::isGreaterThan34"
  br i1 %"GlobalIndexExpr::isWithinBounds35", label %"GlobalIndexExpr::then30", label %"GlobalIndexExpr::else31"

"GlobalIndexExpr::then30":                        ; preds = %"GlobalIndexExpr::merge"
  br label %"GlobalIndexExpr::merge32"

"GlobalIndexExpr::else31":                        ; preds = %"GlobalIndexExpr::merge"
  call void @raise_exception(ptr @70)
  br label %"GlobalIndexExpr::merge32"

"GlobalIndexExpr::merge32":                       ; preds = %"GlobalIndexExpr::else31", %"GlobalIndexExpr::then30"
  %65 = getelementptr [100 x ptr], ptr %lines, i32 0, i32 %64
  %66 = load ptr, ptr %65, align 8
  %67 = call ptr @concat_strings(ptr %66, ptr @71)
  store ptr %67, ptr %61, align 8
  %68 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %checkContinueBlock23, label %afterNestedBlock21

"GlobalIndexExpr::then36":                        ; preds = %nestedBlock24
  br label %"GlobalIndexExpr::merge38"

"GlobalIndexExpr::else37":                        ; preds = %nestedBlock24
  call void @raise_exception(ptr @72)
  br label %"GlobalIndexExpr::merge38"

"GlobalIndexExpr::merge38":                       ; preds = %"GlobalIndexExpr::else37", %"GlobalIndexExpr::then36"
  %70 = getelementptr [100 x ptr], ptr %lines, i32 0, i32 %53
  %71 = load ptr, ptr %70, align 8
  store ptr @73, ptr %3, align 8
  call void @split(ptr %sublines, ptr %70, ptr %3)
  %72 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %checkContinueBlock25, label %afterNestedBlock21

"GlobalIndexExpr::then42":                        ; preds = %nestedBlock26
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::else43":                        ; preds = %nestedBlock26
  call void @raise_exception(ptr @74)
  br label %"GlobalIndexExpr::merge44"

"GlobalIndexExpr::merge44":                       ; preds = %"GlobalIndexExpr::else43", %"GlobalIndexExpr::then42"
  %74 = getelementptr [100 x ptr], ptr %sublines, i32 0, i32 0
  %75 = load ptr, ptr %74, align 8
  %76 = load ptr, ptr %74, align 8
  store ptr %76, ptr %first_line, align 8
  %77 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %78 = icmp eq i32 %77, 0
  br i1 %78, label %checkContinueBlock27, label %afterNestedBlock21

then:                                             ; preds = %nestedBlock28
  br label %nestedBlock46

else:                                             ; preds = %nestedBlock28
  br label %nestedBlock64

afterIfElse:                                      ; preds = %afterNestedBlock63, %afterNestedBlock45
  %79 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %80 = icmp eq i32 %79, 0
  br i1 %80, label %checkContinueBlock29, label %afterNestedBlock21

afterNestedBlock45:                               ; preds = %checkContinueBlock49, %"GlobalIndexExpr::merge62", %checkContinueBlock47, %nestedBlock46
  br label %afterIfElse

nestedBlock46:                                    ; preds = %then
  %first_line50 = load ptr, ptr %first_line, align 8
  store ptr @75, ptr %8, align 8
  call void @split(ptr %parts6, ptr %first_line, ptr %8)
  %81 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %82 = icmp eq i32 %81, 0
  br i1 %82, label %checkContinueBlock47, label %afterNestedBlock45

checkContinueBlock47:                             ; preds = %nestedBlock46
  %83 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %84 = icmp eq i32 %83, 0
  br i1 %84, label %nestedBlock48, label %afterNestedBlock45

nestedBlock48:                                    ; preds = %checkContinueBlock47
  %method51 = load ptr, ptr %method1, align 8
  br i1 true, label %"GlobalIndexExpr::then52", label %"GlobalIndexExpr::else53"

checkContinueBlock49:                             ; preds = %"GlobalIndexExpr::merge62"
  br label %afterNestedBlock45

"GlobalIndexExpr::then52":                        ; preds = %nestedBlock48
  br label %"GlobalIndexExpr::merge54"

"GlobalIndexExpr::else53":                        ; preds = %nestedBlock48
  call void @raise_exception(ptr @76)
  br label %"GlobalIndexExpr::merge54"

"GlobalIndexExpr::merge54":                       ; preds = %"GlobalIndexExpr::else53", %"GlobalIndexExpr::then52"
  %85 = getelementptr [100 x ptr], ptr %parts6, i32 0, i32 0
  %86 = load ptr, ptr %85, align 8
  %87 = load ptr, ptr %85, align 8
  store ptr %87, ptr %method1, align 8
  %endpoint55 = load ptr, ptr %endpoint2, align 8
  br i1 true, label %"GlobalIndexExpr::then56", label %"GlobalIndexExpr::else57"

"GlobalIndexExpr::then56":                        ; preds = %"GlobalIndexExpr::merge54"
  br label %"GlobalIndexExpr::merge58"

"GlobalIndexExpr::else57":                        ; preds = %"GlobalIndexExpr::merge54"
  call void @raise_exception(ptr @77)
  br label %"GlobalIndexExpr::merge58"

"GlobalIndexExpr::merge58":                       ; preds = %"GlobalIndexExpr::else57", %"GlobalIndexExpr::then56"
  %88 = getelementptr [100 x ptr], ptr %parts6, i32 0, i32 1
  %89 = load ptr, ptr %88, align 8
  %90 = load ptr, ptr %88, align 8
  store ptr %90, ptr %endpoint2, align 8
  %version59 = load ptr, ptr %version3, align 8
  br i1 true, label %"GlobalIndexExpr::then60", label %"GlobalIndexExpr::else61"

"GlobalIndexExpr::then60":                        ; preds = %"GlobalIndexExpr::merge58"
  br label %"GlobalIndexExpr::merge62"

"GlobalIndexExpr::else61":                        ; preds = %"GlobalIndexExpr::merge58"
  call void @raise_exception(ptr @78)
  br label %"GlobalIndexExpr::merge62"

"GlobalIndexExpr::merge62":                       ; preds = %"GlobalIndexExpr::else61", %"GlobalIndexExpr::then60"
  %91 = getelementptr [100 x ptr], ptr %parts6, i32 0, i32 2
  %92 = load ptr, ptr %91, align 8
  %93 = load ptr, ptr %91, align 8
  store ptr %93, ptr %version3, align 8
  %94 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %checkContinueBlock49, label %afterNestedBlock45

afterNestedBlock63:                               ; preds = %checkContinueBlock71, %afterIfElse99, %checkContinueBlock69, %afterIfElse81, %checkContinueBlock67, %"GlobalIndexExpr::merge78", %checkContinueBlock65, %nestedBlock64
  br label %afterIfElse

nestedBlock64:                                    ; preds = %else
  %first_line72 = load ptr, ptr %first_line, align 8
  store ptr @79, ptr %9, align 8
  call void @split(ptr %header_parts7, ptr %first_line, ptr %9)
  %96 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %97 = icmp eq i32 %96, 0
  br i1 %97, label %checkContinueBlock65, label %afterNestedBlock63

checkContinueBlock65:                             ; preds = %nestedBlock64
  %98 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %nestedBlock66, label %afterNestedBlock63

nestedBlock66:                                    ; preds = %checkContinueBlock65
  br i1 true, label %"GlobalIndexExpr::then73", label %"GlobalIndexExpr::else74"

checkContinueBlock67:                             ; preds = %"GlobalIndexExpr::merge78"
  %100 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %nestedBlock68, label %afterNestedBlock63

nestedBlock68:                                    ; preds = %checkContinueBlock67
  %102 = getelementptr inbounds %DynamicType, ptr %hasBody, i32 0, i32 2
  %103 = load i1, ptr %102, align 1
  br i1 %103, label %then79, label %else80

checkContinueBlock69:                             ; preds = %afterIfElse81
  %104 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %105 = icmp eq i32 %104, 0
  br i1 %105, label %nestedBlock70, label %afterNestedBlock63

nestedBlock70:                                    ; preds = %checkContinueBlock69
  br i1 true, label %"GlobalIndexExpr::then94", label %"GlobalIndexExpr::else95"

checkContinueBlock71:                             ; preds = %afterIfElse99
  br label %afterNestedBlock63

"GlobalIndexExpr::then73":                        ; preds = %nestedBlock66
  br label %"GlobalIndexExpr::merge75"

"GlobalIndexExpr::else74":                        ; preds = %nestedBlock66
  call void @raise_exception(ptr @80)
  br label %"GlobalIndexExpr::merge75"

"GlobalIndexExpr::merge75":                       ; preds = %"GlobalIndexExpr::else74", %"GlobalIndexExpr::then73"
  %106 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %107 = load ptr, ptr %106, align 8
  br i1 true, label %"GlobalIndexExpr::then76", label %"GlobalIndexExpr::else77"

"GlobalIndexExpr::then76":                        ; preds = %"GlobalIndexExpr::merge75"
  br label %"GlobalIndexExpr::merge78"

"GlobalIndexExpr::else77":                        ; preds = %"GlobalIndexExpr::merge75"
  call void @raise_exception(ptr @81)
  br label %"GlobalIndexExpr::merge78"

"GlobalIndexExpr::merge78":                       ; preds = %"GlobalIndexExpr::else77", %"GlobalIndexExpr::then76"
  %108 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %109 = load ptr, ptr %108, align 8
  call void @"Str::trimInPlace"(ptr %106, ptr %108)
  %110 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %111 = icmp eq i32 %110, 0
  br i1 %111, label %checkContinueBlock67, label %afterNestedBlock63

then79:                                           ; preds = %nestedBlock68
  br label %nestedBlock83

else80:                                           ; preds = %nestedBlock68
  br label %afterIfElse81

afterIfElse81:                                    ; preds = %else80, %afterNestedBlock82
  %112 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %113 = icmp eq i32 %112, 0
  br i1 %113, label %checkContinueBlock69, label %afterNestedBlock63

afterNestedBlock82:                               ; preds = %checkContinueBlock90, %nestedBlock89, %checkContinueBlock88, %nestedBlock87, %checkContinueBlock86, %nestedBlock85, %checkContinueBlock84, %nestedBlock83
  br label %afterIfElse81

nestedBlock83:                                    ; preds = %then79
  %body91 = load ptr, ptr %body, align 8
  %first_line92 = load ptr, ptr %first_line, align 8
  %114 = load ptr, ptr %first_line, align 8
  store ptr %114, ptr %body, align 8
  %115 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %116 = icmp eq i32 %115, 0
  br i1 %116, label %checkContinueBlock84, label %afterNestedBlock82

checkContinueBlock84:                             ; preds = %nestedBlock83
  %117 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %118 = icmp eq i32 %117, 0
  br i1 %118, label %nestedBlock85, label %afterNestedBlock82

nestedBlock85:                                    ; preds = %checkContinueBlock84
  %119 = load ptr, ptr @"%s", align 8
  call void (ptr, ...) @printf(ptr %119, ptr @82)
  %first_line93 = load ptr, ptr %first_line, align 8
  %120 = load ptr, ptr %first_line, align 8
  %121 = load ptr, ptr @"%s.26", align 8
  call void (ptr, ...) @printf(ptr %121, ptr %120)
  %122 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %123 = icmp eq i32 %122, 0
  br i1 %123, label %checkContinueBlock86, label %afterNestedBlock82

checkContinueBlock86:                             ; preds = %nestedBlock85
  %124 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %125 = icmp eq i32 %124, 0
  br i1 %125, label %nestedBlock87, label %afterNestedBlock82

nestedBlock87:                                    ; preds = %checkContinueBlock86
  call void @flush()
  %126 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %127 = icmp eq i32 %126, 0
  br i1 %127, label %checkContinueBlock88, label %afterNestedBlock82

checkContinueBlock88:                             ; preds = %nestedBlock87
  %128 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %129 = icmp eq i32 %128, 0
  br i1 %129, label %nestedBlock89, label %afterNestedBlock82

nestedBlock89:                                    ; preds = %checkContinueBlock88
  %130 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %131 = add i32 %130, 1
  store i32 %131, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %132 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %133 = icmp eq i32 %132, 0
  br i1 %133, label %checkContinueBlock90, label %afterNestedBlock82

checkContinueBlock90:                             ; preds = %nestedBlock89
  br label %afterNestedBlock82

"GlobalIndexExpr::then94":                        ; preds = %nestedBlock70
  br label %"GlobalIndexExpr::merge96"

"GlobalIndexExpr::else95":                        ; preds = %nestedBlock70
  call void @raise_exception(ptr @85)
  br label %"GlobalIndexExpr::merge96"

"GlobalIndexExpr::merge96":                       ; preds = %"GlobalIndexExpr::else95", %"GlobalIndexExpr::then94"
  %134 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %135 = load ptr, ptr %134, align 8
  %136 = call i1 @equal_strings(ptr %135, ptr @86)
  %137 = select i1 %136, i1 true, i1 false
  br i1 %137, label %then97, label %orIf0

then97:                                           ; preds = %"GlobalIndexExpr::merge96"
  br label %nestedBlock149

orIf0:                                            ; preds = %"GlobalIndexExpr::merge96"
  br i1 true, label %"GlobalIndexExpr::then100", label %"GlobalIndexExpr::else101"

orIf1:                                            ; preds = %"GlobalIndexExpr::merge102"
  br i1 true, label %"GlobalIndexExpr::then103", label %"GlobalIndexExpr::else104"

orIf2:                                            ; preds = %"GlobalIndexExpr::merge105"
  br i1 true, label %"GlobalIndexExpr::then106", label %"GlobalIndexExpr::else107"

orIf3:                                            ; preds = %"GlobalIndexExpr::merge108"
  br i1 true, label %"GlobalIndexExpr::then109", label %"GlobalIndexExpr::else110"

orIf4:                                            ; preds = %"GlobalIndexExpr::merge111"
  br i1 true, label %"GlobalIndexExpr::then112", label %"GlobalIndexExpr::else113"

orIf5:                                            ; preds = %"GlobalIndexExpr::merge114"
  br i1 true, label %"GlobalIndexExpr::then115", label %"GlobalIndexExpr::else116"

orIf6:                                            ; preds = %"GlobalIndexExpr::merge117"
  br i1 true, label %"GlobalIndexExpr::then118", label %"GlobalIndexExpr::else119"

orIf7:                                            ; preds = %"GlobalIndexExpr::merge120"
  br i1 true, label %"GlobalIndexExpr::then121", label %"GlobalIndexExpr::else122"

orIf8:                                            ; preds = %"GlobalIndexExpr::merge123"
  br i1 true, label %"GlobalIndexExpr::then124", label %"GlobalIndexExpr::else125"

orIf9:                                            ; preds = %"GlobalIndexExpr::merge126"
  br i1 true, label %"GlobalIndexExpr::then127", label %"GlobalIndexExpr::else128"

orIf10:                                           ; preds = %"GlobalIndexExpr::merge129"
  br i1 true, label %"GlobalIndexExpr::then130", label %"GlobalIndexExpr::else131"

orIf11:                                           ; preds = %"GlobalIndexExpr::merge132"
  br i1 true, label %"GlobalIndexExpr::then133", label %"GlobalIndexExpr::else134"

orIf12:                                           ; preds = %"GlobalIndexExpr::merge135"
  br i1 true, label %"GlobalIndexExpr::then136", label %"GlobalIndexExpr::else137"

orIf13:                                           ; preds = %"GlobalIndexExpr::merge138"
  br i1 true, label %"GlobalIndexExpr::then139", label %"GlobalIndexExpr::else140"

orIf14:                                           ; preds = %"GlobalIndexExpr::merge141"
  br i1 true, label %"GlobalIndexExpr::then142", label %"GlobalIndexExpr::else143"

orIf15:                                           ; preds = %"GlobalIndexExpr::merge144"
  br i1 true, label %"GlobalIndexExpr::then145", label %"GlobalIndexExpr::else146"

orIfThen0:                                        ; preds = %"GlobalIndexExpr::merge102"
  br label %nestedBlock155

orIfThen1:                                        ; preds = %"GlobalIndexExpr::merge105"
  br label %nestedBlock161

orIfThen2:                                        ; preds = %"GlobalIndexExpr::merge108"
  br label %nestedBlock167

orIfThen3:                                        ; preds = %"GlobalIndexExpr::merge111"
  br label %nestedBlock173

orIfThen4:                                        ; preds = %"GlobalIndexExpr::merge114"
  br label %nestedBlock179

orIfThen5:                                        ; preds = %"GlobalIndexExpr::merge117"
  br label %nestedBlock185

orIfThen6:                                        ; preds = %"GlobalIndexExpr::merge120"
  br label %nestedBlock191

orIfThen7:                                        ; preds = %"GlobalIndexExpr::merge123"
  br label %nestedBlock197

orIfThen8:                                        ; preds = %"GlobalIndexExpr::merge126"
  br label %nestedBlock203

orIfThen9:                                        ; preds = %"GlobalIndexExpr::merge129"
  br label %nestedBlock209

orIfThen10:                                       ; preds = %"GlobalIndexExpr::merge132"
  br label %nestedBlock215

orIfThen11:                                       ; preds = %"GlobalIndexExpr::merge135"
  br label %nestedBlock221

orIfThen12:                                       ; preds = %"GlobalIndexExpr::merge138"
  br label %nestedBlock227

orIfThen13:                                       ; preds = %"GlobalIndexExpr::merge141"
  br label %nestedBlock233

orIfThen14:                                       ; preds = %"GlobalIndexExpr::merge144"
  br label %nestedBlock239

orIfThen15:                                       ; preds = %"GlobalIndexExpr::merge147"
  br label %nestedBlock245

else98:                                           ; preds = %"GlobalIndexExpr::merge147"
  br label %afterIfElse99

afterIfElse99:                                    ; preds = %else98, %afterNestedBlock244, %afterNestedBlock238, %afterNestedBlock232, %afterNestedBlock226, %afterNestedBlock220, %afterNestedBlock214, %afterNestedBlock208, %afterNestedBlock202, %afterNestedBlock196, %afterNestedBlock190, %afterNestedBlock184, %afterNestedBlock178, %afterNestedBlock172, %afterNestedBlock166, %afterNestedBlock160, %afterNestedBlock154, %afterNestedBlock148
  %138 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %139 = icmp eq i32 %138, 0
  br i1 %139, label %checkContinueBlock71, label %afterNestedBlock63

"GlobalIndexExpr::then100":                       ; preds = %orIf0
  br label %"GlobalIndexExpr::merge102"

"GlobalIndexExpr::else101":                       ; preds = %orIf0
  call void @raise_exception(ptr @87)
  br label %"GlobalIndexExpr::merge102"

"GlobalIndexExpr::merge102":                      ; preds = %"GlobalIndexExpr::else101", %"GlobalIndexExpr::then100"
  %140 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %141 = load ptr, ptr %140, align 8
  %142 = call i1 @equal_strings(ptr %141, ptr @88)
  %143 = select i1 %142, i1 true, i1 false
  br i1 %143, label %orIfThen0, label %orIf1

"GlobalIndexExpr::then103":                       ; preds = %orIf1
  br label %"GlobalIndexExpr::merge105"

"GlobalIndexExpr::else104":                       ; preds = %orIf1
  call void @raise_exception(ptr @89)
  br label %"GlobalIndexExpr::merge105"

"GlobalIndexExpr::merge105":                      ; preds = %"GlobalIndexExpr::else104", %"GlobalIndexExpr::then103"
  %144 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %145 = load ptr, ptr %144, align 8
  %146 = call i1 @equal_strings(ptr %145, ptr @90)
  %147 = select i1 %146, i1 true, i1 false
  br i1 %147, label %orIfThen1, label %orIf2

"GlobalIndexExpr::then106":                       ; preds = %orIf2
  br label %"GlobalIndexExpr::merge108"

"GlobalIndexExpr::else107":                       ; preds = %orIf2
  call void @raise_exception(ptr @91)
  br label %"GlobalIndexExpr::merge108"

"GlobalIndexExpr::merge108":                      ; preds = %"GlobalIndexExpr::else107", %"GlobalIndexExpr::then106"
  %148 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %149 = load ptr, ptr %148, align 8
  %150 = call i1 @equal_strings(ptr %149, ptr @92)
  %151 = select i1 %150, i1 true, i1 false
  br i1 %151, label %orIfThen2, label %orIf3

"GlobalIndexExpr::then109":                       ; preds = %orIf3
  br label %"GlobalIndexExpr::merge111"

"GlobalIndexExpr::else110":                       ; preds = %orIf3
  call void @raise_exception(ptr @93)
  br label %"GlobalIndexExpr::merge111"

"GlobalIndexExpr::merge111":                      ; preds = %"GlobalIndexExpr::else110", %"GlobalIndexExpr::then109"
  %152 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %153 = load ptr, ptr %152, align 8
  %154 = call i1 @equal_strings(ptr %153, ptr @94)
  %155 = select i1 %154, i1 true, i1 false
  br i1 %155, label %orIfThen3, label %orIf4

"GlobalIndexExpr::then112":                       ; preds = %orIf4
  br label %"GlobalIndexExpr::merge114"

"GlobalIndexExpr::else113":                       ; preds = %orIf4
  call void @raise_exception(ptr @95)
  br label %"GlobalIndexExpr::merge114"

"GlobalIndexExpr::merge114":                      ; preds = %"GlobalIndexExpr::else113", %"GlobalIndexExpr::then112"
  %156 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %157 = load ptr, ptr %156, align 8
  %158 = call i1 @equal_strings(ptr %157, ptr @96)
  %159 = select i1 %158, i1 true, i1 false
  br i1 %159, label %orIfThen4, label %orIf5

"GlobalIndexExpr::then115":                       ; preds = %orIf5
  br label %"GlobalIndexExpr::merge117"

"GlobalIndexExpr::else116":                       ; preds = %orIf5
  call void @raise_exception(ptr @97)
  br label %"GlobalIndexExpr::merge117"

"GlobalIndexExpr::merge117":                      ; preds = %"GlobalIndexExpr::else116", %"GlobalIndexExpr::then115"
  %160 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %161 = load ptr, ptr %160, align 8
  %162 = call i1 @equal_strings(ptr %161, ptr @98)
  %163 = select i1 %162, i1 true, i1 false
  br i1 %163, label %orIfThen5, label %orIf6

"GlobalIndexExpr::then118":                       ; preds = %orIf6
  br label %"GlobalIndexExpr::merge120"

"GlobalIndexExpr::else119":                       ; preds = %orIf6
  call void @raise_exception(ptr @99)
  br label %"GlobalIndexExpr::merge120"

"GlobalIndexExpr::merge120":                      ; preds = %"GlobalIndexExpr::else119", %"GlobalIndexExpr::then118"
  %164 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %165 = load ptr, ptr %164, align 8
  %166 = call i1 @equal_strings(ptr %165, ptr @100)
  %167 = select i1 %166, i1 true, i1 false
  br i1 %167, label %orIfThen6, label %orIf7

"GlobalIndexExpr::then121":                       ; preds = %orIf7
  br label %"GlobalIndexExpr::merge123"

"GlobalIndexExpr::else122":                       ; preds = %orIf7
  call void @raise_exception(ptr @101)
  br label %"GlobalIndexExpr::merge123"

"GlobalIndexExpr::merge123":                      ; preds = %"GlobalIndexExpr::else122", %"GlobalIndexExpr::then121"
  %168 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %169 = load ptr, ptr %168, align 8
  %170 = call i1 @equal_strings(ptr %169, ptr @102)
  %171 = select i1 %170, i1 true, i1 false
  br i1 %171, label %orIfThen7, label %orIf8

"GlobalIndexExpr::then124":                       ; preds = %orIf8
  br label %"GlobalIndexExpr::merge126"

"GlobalIndexExpr::else125":                       ; preds = %orIf8
  call void @raise_exception(ptr @103)
  br label %"GlobalIndexExpr::merge126"

"GlobalIndexExpr::merge126":                      ; preds = %"GlobalIndexExpr::else125", %"GlobalIndexExpr::then124"
  %172 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %173 = load ptr, ptr %172, align 8
  %174 = call i1 @equal_strings(ptr %173, ptr @104)
  %175 = select i1 %174, i1 true, i1 false
  br i1 %175, label %orIfThen8, label %orIf9

"GlobalIndexExpr::then127":                       ; preds = %orIf9
  br label %"GlobalIndexExpr::merge129"

"GlobalIndexExpr::else128":                       ; preds = %orIf9
  call void @raise_exception(ptr @105)
  br label %"GlobalIndexExpr::merge129"

"GlobalIndexExpr::merge129":                      ; preds = %"GlobalIndexExpr::else128", %"GlobalIndexExpr::then127"
  %176 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %177 = load ptr, ptr %176, align 8
  %178 = call i1 @equal_strings(ptr %177, ptr @106)
  %179 = select i1 %178, i1 true, i1 false
  br i1 %179, label %orIfThen9, label %orIf10

"GlobalIndexExpr::then130":                       ; preds = %orIf10
  br label %"GlobalIndexExpr::merge132"

"GlobalIndexExpr::else131":                       ; preds = %orIf10
  call void @raise_exception(ptr @107)
  br label %"GlobalIndexExpr::merge132"

"GlobalIndexExpr::merge132":                      ; preds = %"GlobalIndexExpr::else131", %"GlobalIndexExpr::then130"
  %180 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %181 = load ptr, ptr %180, align 8
  %182 = call i1 @equal_strings(ptr %181, ptr @108)
  %183 = select i1 %182, i1 true, i1 false
  br i1 %183, label %orIfThen10, label %orIf11

"GlobalIndexExpr::then133":                       ; preds = %orIf11
  br label %"GlobalIndexExpr::merge135"

"GlobalIndexExpr::else134":                       ; preds = %orIf11
  call void @raise_exception(ptr @109)
  br label %"GlobalIndexExpr::merge135"

"GlobalIndexExpr::merge135":                      ; preds = %"GlobalIndexExpr::else134", %"GlobalIndexExpr::then133"
  %184 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %185 = load ptr, ptr %184, align 8
  %186 = call i1 @equal_strings(ptr %185, ptr @110)
  %187 = select i1 %186, i1 true, i1 false
  br i1 %187, label %orIfThen11, label %orIf12

"GlobalIndexExpr::then136":                       ; preds = %orIf12
  br label %"GlobalIndexExpr::merge138"

"GlobalIndexExpr::else137":                       ; preds = %orIf12
  call void @raise_exception(ptr @111)
  br label %"GlobalIndexExpr::merge138"

"GlobalIndexExpr::merge138":                      ; preds = %"GlobalIndexExpr::else137", %"GlobalIndexExpr::then136"
  %188 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %189 = load ptr, ptr %188, align 8
  %190 = call i1 @equal_strings(ptr %189, ptr @112)
  %191 = select i1 %190, i1 true, i1 false
  br i1 %191, label %orIfThen12, label %orIf13

"GlobalIndexExpr::then139":                       ; preds = %orIf13
  br label %"GlobalIndexExpr::merge141"

"GlobalIndexExpr::else140":                       ; preds = %orIf13
  call void @raise_exception(ptr @113)
  br label %"GlobalIndexExpr::merge141"

"GlobalIndexExpr::merge141":                      ; preds = %"GlobalIndexExpr::else140", %"GlobalIndexExpr::then139"
  %192 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %193 = load ptr, ptr %192, align 8
  %194 = call i1 @equal_strings(ptr %193, ptr @114)
  %195 = select i1 %194, i1 true, i1 false
  br i1 %195, label %orIfThen13, label %orIf14

"GlobalIndexExpr::then142":                       ; preds = %orIf14
  br label %"GlobalIndexExpr::merge144"

"GlobalIndexExpr::else143":                       ; preds = %orIf14
  call void @raise_exception(ptr @115)
  br label %"GlobalIndexExpr::merge144"

"GlobalIndexExpr::merge144":                      ; preds = %"GlobalIndexExpr::else143", %"GlobalIndexExpr::then142"
  %196 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %197 = load ptr, ptr %196, align 8
  %198 = call i1 @equal_strings(ptr %197, ptr @116)
  %199 = select i1 %198, i1 true, i1 false
  br i1 %199, label %orIfThen14, label %orIf15

"GlobalIndexExpr::then145":                       ; preds = %orIf15
  br label %"GlobalIndexExpr::merge147"

"GlobalIndexExpr::else146":                       ; preds = %orIf15
  call void @raise_exception(ptr @117)
  br label %"GlobalIndexExpr::merge147"

"GlobalIndexExpr::merge147":                      ; preds = %"GlobalIndexExpr::else146", %"GlobalIndexExpr::then145"
  %200 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 0
  %201 = load ptr, ptr %200, align 8
  %202 = call i1 @equal_strings(ptr %201, ptr @118)
  %203 = select i1 %202, i1 true, i1 false
  br i1 %203, label %orIfThen15, label %else98

afterNestedBlock148:                              ; preds = %checkContinueBlock150, %"GlobalIndexExpr::merge153"
  br label %afterIfElse99

nestedBlock149:                                   ; preds = %then97
  %204 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 0
  %Host = load ptr, ptr %204, align 8
  br i1 true, label %"GlobalIndexExpr::then151", label %"GlobalIndexExpr::else152"

checkContinueBlock150:                            ; preds = %"GlobalIndexExpr::merge153"
  br label %afterNestedBlock148

"GlobalIndexExpr::then151":                       ; preds = %nestedBlock149
  br label %"GlobalIndexExpr::merge153"

"GlobalIndexExpr::else152":                       ; preds = %nestedBlock149
  call void @raise_exception(ptr @119)
  br label %"GlobalIndexExpr::merge153"

"GlobalIndexExpr::merge153":                      ; preds = %"GlobalIndexExpr::else152", %"GlobalIndexExpr::then151"
  %205 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %206 = load ptr, ptr %205, align 8
  %207 = load ptr, ptr %205, align 8
  store ptr %207, ptr %204, align 8
  %208 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %209 = icmp eq i32 %208, 0
  br i1 %209, label %checkContinueBlock150, label %afterNestedBlock148

afterNestedBlock154:                              ; preds = %checkContinueBlock156, %"GlobalIndexExpr::merge159"
  br label %afterIfElse99

nestedBlock155:                                   ; preds = %orIfThen0
  %210 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 1
  %Connection = load ptr, ptr %210, align 8
  br i1 true, label %"GlobalIndexExpr::then157", label %"GlobalIndexExpr::else158"

checkContinueBlock156:                            ; preds = %"GlobalIndexExpr::merge159"
  br label %afterNestedBlock154

"GlobalIndexExpr::then157":                       ; preds = %nestedBlock155
  br label %"GlobalIndexExpr::merge159"

"GlobalIndexExpr::else158":                       ; preds = %nestedBlock155
  call void @raise_exception(ptr @120)
  br label %"GlobalIndexExpr::merge159"

"GlobalIndexExpr::merge159":                      ; preds = %"GlobalIndexExpr::else158", %"GlobalIndexExpr::then157"
  %211 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %212 = load ptr, ptr %211, align 8
  %213 = load ptr, ptr %211, align 8
  store ptr %213, ptr %210, align 8
  %214 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %215 = icmp eq i32 %214, 0
  br i1 %215, label %checkContinueBlock156, label %afterNestedBlock154

afterNestedBlock160:                              ; preds = %checkContinueBlock162, %"GlobalIndexExpr::merge165"
  br label %afterIfElse99

nestedBlock161:                                   ; preds = %orIfThen1
  %216 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 2
  %sec_ch_ua = load ptr, ptr %216, align 8
  br i1 true, label %"GlobalIndexExpr::then163", label %"GlobalIndexExpr::else164"

checkContinueBlock162:                            ; preds = %"GlobalIndexExpr::merge165"
  br label %afterNestedBlock160

"GlobalIndexExpr::then163":                       ; preds = %nestedBlock161
  br label %"GlobalIndexExpr::merge165"

"GlobalIndexExpr::else164":                       ; preds = %nestedBlock161
  call void @raise_exception(ptr @121)
  br label %"GlobalIndexExpr::merge165"

"GlobalIndexExpr::merge165":                      ; preds = %"GlobalIndexExpr::else164", %"GlobalIndexExpr::then163"
  %217 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %218 = load ptr, ptr %217, align 8
  %219 = load ptr, ptr %217, align 8
  store ptr %219, ptr %216, align 8
  %220 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %221 = icmp eq i32 %220, 0
  br i1 %221, label %checkContinueBlock162, label %afterNestedBlock160

afterNestedBlock166:                              ; preds = %checkContinueBlock168, %"GlobalIndexExpr::merge171"
  br label %afterIfElse99

nestedBlock167:                                   ; preds = %orIfThen2
  %222 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 3
  %sec_ch_ua_mobile = load i1, ptr %222, align 1
  br i1 true, label %"GlobalIndexExpr::then169", label %"GlobalIndexExpr::else170"

checkContinueBlock168:                            ; preds = %"GlobalIndexExpr::merge171"
  br label %afterNestedBlock166

"GlobalIndexExpr::then169":                       ; preds = %nestedBlock167
  br label %"GlobalIndexExpr::merge171"

"GlobalIndexExpr::else170":                       ; preds = %nestedBlock167
  call void @raise_exception(ptr @122)
  br label %"GlobalIndexExpr::merge171"

"GlobalIndexExpr::merge171":                      ; preds = %"GlobalIndexExpr::else170", %"GlobalIndexExpr::then169"
  %223 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %224 = load ptr, ptr %223, align 8
  %225 = call i1 @equal_strings(ptr %224, ptr @123)
  %226 = select i1 %225, i1 true, i1 false
  store i1 %226, ptr %222, align 1
  %227 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %228 = icmp eq i32 %227, 0
  br i1 %228, label %checkContinueBlock168, label %afterNestedBlock166

afterNestedBlock172:                              ; preds = %checkContinueBlock174, %"GlobalIndexExpr::merge177"
  br label %afterIfElse99

nestedBlock173:                                   ; preds = %orIfThen3
  %229 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 4
  %sec_ch_ua_platform = load ptr, ptr %229, align 8
  br i1 true, label %"GlobalIndexExpr::then175", label %"GlobalIndexExpr::else176"

checkContinueBlock174:                            ; preds = %"GlobalIndexExpr::merge177"
  br label %afterNestedBlock172

"GlobalIndexExpr::then175":                       ; preds = %nestedBlock173
  br label %"GlobalIndexExpr::merge177"

"GlobalIndexExpr::else176":                       ; preds = %nestedBlock173
  call void @raise_exception(ptr @124)
  br label %"GlobalIndexExpr::merge177"

"GlobalIndexExpr::merge177":                      ; preds = %"GlobalIndexExpr::else176", %"GlobalIndexExpr::then175"
  %230 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %231 = load ptr, ptr %230, align 8
  %232 = load ptr, ptr %230, align 8
  store ptr %232, ptr %229, align 8
  %233 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %234 = icmp eq i32 %233, 0
  br i1 %234, label %checkContinueBlock174, label %afterNestedBlock172

afterNestedBlock178:                              ; preds = %checkContinueBlock180, %"GlobalIndexExpr::merge183"
  br label %afterIfElse99

nestedBlock179:                                   ; preds = %orIfThen4
  %235 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 5
  %Upgrade_Insecure_Requests = load i32, ptr %235, align 4
  br i1 true, label %"GlobalIndexExpr::then181", label %"GlobalIndexExpr::else182"

checkContinueBlock180:                            ; preds = %"GlobalIndexExpr::merge183"
  br label %afterNestedBlock178

"GlobalIndexExpr::then181":                       ; preds = %nestedBlock179
  br label %"GlobalIndexExpr::merge183"

"GlobalIndexExpr::else182":                       ; preds = %nestedBlock179
  call void @raise_exception(ptr @125)
  br label %"GlobalIndexExpr::merge183"

"GlobalIndexExpr::merge183":                      ; preds = %"GlobalIndexExpr::else182", %"GlobalIndexExpr::then181"
  %236 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %237 = load ptr, ptr %236, align 8
  %238 = call i32 @string_to_int(ptr %237)
  store i32 %238, ptr %235, align 4
  %239 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %240 = icmp eq i32 %239, 0
  br i1 %240, label %checkContinueBlock180, label %afterNestedBlock178

afterNestedBlock184:                              ; preds = %checkContinueBlock186, %"GlobalIndexExpr::merge189"
  br label %afterIfElse99

nestedBlock185:                                   ; preds = %orIfThen5
  %241 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 6
  %User_Agent = load ptr, ptr %241, align 8
  br i1 true, label %"GlobalIndexExpr::then187", label %"GlobalIndexExpr::else188"

checkContinueBlock186:                            ; preds = %"GlobalIndexExpr::merge189"
  br label %afterNestedBlock184

"GlobalIndexExpr::then187":                       ; preds = %nestedBlock185
  br label %"GlobalIndexExpr::merge189"

"GlobalIndexExpr::else188":                       ; preds = %nestedBlock185
  call void @raise_exception(ptr @126)
  br label %"GlobalIndexExpr::merge189"

"GlobalIndexExpr::merge189":                      ; preds = %"GlobalIndexExpr::else188", %"GlobalIndexExpr::then187"
  %242 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %243 = load ptr, ptr %242, align 8
  %244 = load ptr, ptr %242, align 8
  store ptr %244, ptr %241, align 8
  %245 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %246 = icmp eq i32 %245, 0
  br i1 %246, label %checkContinueBlock186, label %afterNestedBlock184

afterNestedBlock190:                              ; preds = %checkContinueBlock192, %"GlobalIndexExpr::merge195"
  br label %afterIfElse99

nestedBlock191:                                   ; preds = %orIfThen6
  %247 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 9
  %Accept = load ptr, ptr %247, align 8
  br i1 true, label %"GlobalIndexExpr::then193", label %"GlobalIndexExpr::else194"

checkContinueBlock192:                            ; preds = %"GlobalIndexExpr::merge195"
  br label %afterNestedBlock190

"GlobalIndexExpr::then193":                       ; preds = %nestedBlock191
  br label %"GlobalIndexExpr::merge195"

"GlobalIndexExpr::else194":                       ; preds = %nestedBlock191
  call void @raise_exception(ptr @127)
  br label %"GlobalIndexExpr::merge195"

"GlobalIndexExpr::merge195":                      ; preds = %"GlobalIndexExpr::else194", %"GlobalIndexExpr::then193"
  %248 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %249 = load ptr, ptr %248, align 8
  %250 = load ptr, ptr %248, align 8
  store ptr %250, ptr %247, align 8
  %251 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %252 = icmp eq i32 %251, 0
  br i1 %252, label %checkContinueBlock192, label %afterNestedBlock190

afterNestedBlock196:                              ; preds = %checkContinueBlock198, %"GlobalIndexExpr::merge201"
  br label %afterIfElse99

nestedBlock197:                                   ; preds = %orIfThen7
  %253 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 10
  %Sec_Fetch_Site = load ptr, ptr %253, align 8
  br i1 true, label %"GlobalIndexExpr::then199", label %"GlobalIndexExpr::else200"

checkContinueBlock198:                            ; preds = %"GlobalIndexExpr::merge201"
  br label %afterNestedBlock196

"GlobalIndexExpr::then199":                       ; preds = %nestedBlock197
  br label %"GlobalIndexExpr::merge201"

"GlobalIndexExpr::else200":                       ; preds = %nestedBlock197
  call void @raise_exception(ptr @128)
  br label %"GlobalIndexExpr::merge201"

"GlobalIndexExpr::merge201":                      ; preds = %"GlobalIndexExpr::else200", %"GlobalIndexExpr::then199"
  %254 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %255 = load ptr, ptr %254, align 8
  %256 = load ptr, ptr %254, align 8
  store ptr %256, ptr %253, align 8
  %257 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %258 = icmp eq i32 %257, 0
  br i1 %258, label %checkContinueBlock198, label %afterNestedBlock196

afterNestedBlock202:                              ; preds = %checkContinueBlock204, %"GlobalIndexExpr::merge207"
  br label %afterIfElse99

nestedBlock203:                                   ; preds = %orIfThen8
  %259 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 11
  %Sec_Fetch_Mode = load ptr, ptr %259, align 8
  br i1 true, label %"GlobalIndexExpr::then205", label %"GlobalIndexExpr::else206"

checkContinueBlock204:                            ; preds = %"GlobalIndexExpr::merge207"
  br label %afterNestedBlock202

"GlobalIndexExpr::then205":                       ; preds = %nestedBlock203
  br label %"GlobalIndexExpr::merge207"

"GlobalIndexExpr::else206":                       ; preds = %nestedBlock203
  call void @raise_exception(ptr @129)
  br label %"GlobalIndexExpr::merge207"

"GlobalIndexExpr::merge207":                      ; preds = %"GlobalIndexExpr::else206", %"GlobalIndexExpr::then205"
  %260 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %261 = load ptr, ptr %260, align 8
  %262 = load ptr, ptr %260, align 8
  store ptr %262, ptr %259, align 8
  %263 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %264 = icmp eq i32 %263, 0
  br i1 %264, label %checkContinueBlock204, label %afterNestedBlock202

afterNestedBlock208:                              ; preds = %checkContinueBlock210, %"GlobalIndexExpr::merge213"
  br label %afterIfElse99

nestedBlock209:                                   ; preds = %orIfThen9
  %265 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 12
  %Sec_Fetch_User = load i1, ptr %265, align 1
  br i1 true, label %"GlobalIndexExpr::then211", label %"GlobalIndexExpr::else212"

checkContinueBlock210:                            ; preds = %"GlobalIndexExpr::merge213"
  br label %afterNestedBlock208

"GlobalIndexExpr::then211":                       ; preds = %nestedBlock209
  br label %"GlobalIndexExpr::merge213"

"GlobalIndexExpr::else212":                       ; preds = %nestedBlock209
  call void @raise_exception(ptr @130)
  br label %"GlobalIndexExpr::merge213"

"GlobalIndexExpr::merge213":                      ; preds = %"GlobalIndexExpr::else212", %"GlobalIndexExpr::then211"
  %266 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %267 = load ptr, ptr %266, align 8
  %268 = call i1 @equal_strings(ptr %267, ptr @131)
  %269 = select i1 %268, i1 true, i1 false
  store i1 %269, ptr %265, align 1
  %270 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %271 = icmp eq i32 %270, 0
  br i1 %271, label %checkContinueBlock210, label %afterNestedBlock208

afterNestedBlock214:                              ; preds = %checkContinueBlock216, %"GlobalIndexExpr::merge219"
  br label %afterIfElse99

nestedBlock215:                                   ; preds = %orIfThen10
  %272 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 13
  %Sec_Fetch_Dest = load ptr, ptr %272, align 8
  br i1 true, label %"GlobalIndexExpr::then217", label %"GlobalIndexExpr::else218"

checkContinueBlock216:                            ; preds = %"GlobalIndexExpr::merge219"
  br label %afterNestedBlock214

"GlobalIndexExpr::then217":                       ; preds = %nestedBlock215
  br label %"GlobalIndexExpr::merge219"

"GlobalIndexExpr::else218":                       ; preds = %nestedBlock215
  call void @raise_exception(ptr @132)
  br label %"GlobalIndexExpr::merge219"

"GlobalIndexExpr::merge219":                      ; preds = %"GlobalIndexExpr::else218", %"GlobalIndexExpr::then217"
  %273 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %274 = load ptr, ptr %273, align 8
  %275 = load ptr, ptr %273, align 8
  store ptr %275, ptr %272, align 8
  %276 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %277 = icmp eq i32 %276, 0
  br i1 %277, label %checkContinueBlock216, label %afterNestedBlock214

afterNestedBlock220:                              ; preds = %checkContinueBlock222, %"GlobalIndexExpr::merge225"
  br label %afterIfElse99

nestedBlock221:                                   ; preds = %orIfThen11
  %278 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 14
  %Accept_Encoding = load ptr, ptr %278, align 8
  br i1 true, label %"GlobalIndexExpr::then223", label %"GlobalIndexExpr::else224"

checkContinueBlock222:                            ; preds = %"GlobalIndexExpr::merge225"
  br label %afterNestedBlock220

"GlobalIndexExpr::then223":                       ; preds = %nestedBlock221
  br label %"GlobalIndexExpr::merge225"

"GlobalIndexExpr::else224":                       ; preds = %nestedBlock221
  call void @raise_exception(ptr @133)
  br label %"GlobalIndexExpr::merge225"

"GlobalIndexExpr::merge225":                      ; preds = %"GlobalIndexExpr::else224", %"GlobalIndexExpr::then223"
  %279 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %280 = load ptr, ptr %279, align 8
  %281 = load ptr, ptr %279, align 8
  store ptr %281, ptr %278, align 8
  %282 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %283 = icmp eq i32 %282, 0
  br i1 %283, label %checkContinueBlock222, label %afterNestedBlock220

afterNestedBlock226:                              ; preds = %checkContinueBlock228, %"GlobalIndexExpr::merge231"
  br label %afterIfElse99

nestedBlock227:                                   ; preds = %orIfThen12
  %284 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 15
  %Accept_Language = load ptr, ptr %284, align 8
  br i1 true, label %"GlobalIndexExpr::then229", label %"GlobalIndexExpr::else230"

checkContinueBlock228:                            ; preds = %"GlobalIndexExpr::merge231"
  br label %afterNestedBlock226

"GlobalIndexExpr::then229":                       ; preds = %nestedBlock227
  br label %"GlobalIndexExpr::merge231"

"GlobalIndexExpr::else230":                       ; preds = %nestedBlock227
  call void @raise_exception(ptr @134)
  br label %"GlobalIndexExpr::merge231"

"GlobalIndexExpr::merge231":                      ; preds = %"GlobalIndexExpr::else230", %"GlobalIndexExpr::then229"
  %285 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %286 = load ptr, ptr %285, align 8
  %287 = load ptr, ptr %285, align 8
  store ptr %287, ptr %284, align 8
  %288 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %289 = icmp eq i32 %288, 0
  br i1 %289, label %checkContinueBlock228, label %afterNestedBlock226

afterNestedBlock232:                              ; preds = %checkContinueBlock234, %"GlobalIndexExpr::merge237"
  br label %afterIfElse99

nestedBlock233:                                   ; preds = %orIfThen13
  %290 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 16
  %content_type = load ptr, ptr %290, align 8
  br i1 true, label %"GlobalIndexExpr::then235", label %"GlobalIndexExpr::else236"

checkContinueBlock234:                            ; preds = %"GlobalIndexExpr::merge237"
  br label %afterNestedBlock232

"GlobalIndexExpr::then235":                       ; preds = %nestedBlock233
  br label %"GlobalIndexExpr::merge237"

"GlobalIndexExpr::else236":                       ; preds = %nestedBlock233
  call void @raise_exception(ptr @135)
  br label %"GlobalIndexExpr::merge237"

"GlobalIndexExpr::merge237":                      ; preds = %"GlobalIndexExpr::else236", %"GlobalIndexExpr::then235"
  %291 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %292 = load ptr, ptr %291, align 8
  %293 = load ptr, ptr %291, align 8
  store ptr %293, ptr %290, align 8
  %294 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %295 = icmp eq i32 %294, 0
  br i1 %295, label %checkContinueBlock234, label %afterNestedBlock232

afterNestedBlock238:                              ; preds = %checkContinueBlock240, %"GlobalIndexExpr::merge243"
  br label %afterIfElse99

nestedBlock239:                                   ; preds = %orIfThen14
  %296 = getelementptr inbounds %Header.1, ptr %header_map, i32 0, i32 17
  %content_length = load i32, ptr %296, align 4
  br i1 true, label %"GlobalIndexExpr::then241", label %"GlobalIndexExpr::else242"

checkContinueBlock240:                            ; preds = %"GlobalIndexExpr::merge243"
  br label %afterNestedBlock238

"GlobalIndexExpr::then241":                       ; preds = %nestedBlock239
  br label %"GlobalIndexExpr::merge243"

"GlobalIndexExpr::else242":                       ; preds = %nestedBlock239
  call void @raise_exception(ptr @136)
  br label %"GlobalIndexExpr::merge243"

"GlobalIndexExpr::merge243":                      ; preds = %"GlobalIndexExpr::else242", %"GlobalIndexExpr::then241"
  %297 = getelementptr [100 x ptr], ptr %header_parts7, i32 0, i32 1
  %298 = load ptr, ptr %297, align 8
  %299 = call i32 @string_to_int(ptr %298)
  %300 = add i32 %299, 0
  store i32 %300, ptr %296, align 4
  %301 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %302 = icmp eq i32 %301, 0
  br i1 %302, label %checkContinueBlock240, label %afterNestedBlock238

afterNestedBlock244:                              ; preds = %checkContinueBlock246, %nestedBlock245
  br label %afterIfElse99

nestedBlock245:                                   ; preds = %orIfThen15
  %303 = getelementptr inbounds %DynamicType, ptr %hasBody, i32 0, i32 2
  %304 = load i1, ptr %303, align 1
  %305 = getelementptr inbounds %DynamicType, ptr %hasBody, i32 0, i32 2
  store i1 true, ptr %305, align 1
  %306 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %307 = icmp eq i32 %306, 0
  br i1 %307, label %checkContinueBlock246, label %afterNestedBlock244

checkContinueBlock246:                            ; preds = %nestedBlock245
  br label %afterNestedBlock244

decrement_block247:                               ; preds = %"ForLoop::afterLoop"
  %308 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %309 = sub i32 %308, 1
  store i32 %309, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  br label %end_block248

end_block248:                                     ; preds = %decrement_block247, %"ForLoop::afterLoop"
  %310 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %311 = icmp eq i32 %310, 0
  br i1 %311, label %checkContinueBlock17, label %afterNestedBlock

returnBlock:                                      ; preds = %nestedBlock18
  %312 = getelementptr inbounds %0, ptr %0, i32 0, i32 0
  %313 = load ptr, ptr %312, align 8
  %314 = getelementptr inbounds %HttpRequest.2, ptr %313, i32 0, i32 0
  %method249 = load ptr, ptr %method1, align 8
  %315 = load ptr, ptr %method1, align 8
  store ptr %315, ptr %314, align 8
  %316 = getelementptr inbounds %HttpRequest.2, ptr %313, i32 0, i32 1
  %endpoint250 = load ptr, ptr %endpoint2, align 8
  %317 = load ptr, ptr %endpoint2, align 8
  store ptr %317, ptr %316, align 8
  %318 = getelementptr inbounds %HttpRequest.2, ptr %313, i32 0, i32 2
  %version251 = load ptr, ptr %version3, align 8
  %319 = load ptr, ptr %version3, align 8
  store ptr %319, ptr %318, align 8
  %320 = getelementptr inbounds %HttpRequest.2, ptr %313, i32 0, i32 3
  %321 = load %Header.1, ptr %header_map, align 8
  store %Header.1 %321, ptr %320, align 8
  %322 = getelementptr inbounds %HttpRequest.2, ptr %313, i32 0, i32 4
  %body252 = load ptr, ptr %body, align 8
  %323 = load ptr, ptr %body, align 8
  store ptr %323, ptr %322, align 8
  %324 = getelementptr inbounds %0, ptr %0, i32 0, i32 1
  %325 = load ptr, ptr %324, align 8
  %326 = call ptr @malloc(i64 16)
  call void @"assign_<Class<Vec::String>>"(ptr %326)
  %327 = getelementptr inbounds %"Vec::String", ptr %326, i32 0, i32 0
  store ptr @"vtable.Vec::String.fg", ptr %327, align 8
  %328 = load ptr, ptr %327, align 8
  %329 = getelementptr inbounds %"Vec::String::VTableType", ptr %328, i32 0, i32 4
  store ptr @"Vec::String.add", ptr %329, align 8
  %330 = getelementptr inbounds %"Vec::String::VTableType", ptr %328, i32 0, i32 2
  store ptr @"Vec::String.remove", ptr %330, align 8
  %331 = getelementptr inbounds %"Vec::String::VTableType", ptr %328, i32 0, i32 3
  store ptr @"Vec::String.get", ptr %331, align 8
  %332 = getelementptr inbounds %"Vec::String::VTableType", ptr %328, i32 0, i32 1
  store ptr @"Vec::String.size", ptr %332, align 8
  %333 = getelementptr inbounds %"Vec::String::VTableType", ptr %328, i32 0, i32 0
  store ptr @"Vec::String.free", ptr %333, align 8
  %334 = getelementptr inbounds %"Vec::String", ptr %326, i32 0, i32 1
  store ptr @139, ptr %334, align 8
  store ptr %326, ptr %325, align 8
  call void @"Vec::String.init0"(ptr %325)
  ret void

mergeBlock:                                       ; No predecessors!
  %335 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %336 = icmp eq i32 %335, 0
  br i1 %336, label %checkContinueBlock19, label %afterNestedBlock
}

declare !rt !87 void @parse_request.25(ptr, ptr)

define void @log_middleware(i32 %0, ptr %1, ptr %2) !rt !88 {
entry:
  %client_socket = alloca i32, align 4
  store i32 %0, ptr %client_socket, align 4
  %req_str = alloca ptr, align 8
  store ptr %1, ptr %req_str, align 8
  %endpoint = alloca ptr, align 8
  store ptr %2, ptr %endpoint, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %3 = load ptr, ptr @"%s.27", align 8
  call void (ptr, ...) @printf(ptr %3, ptr @140)
  %endpoint3 = load ptr, ptr %endpoint, align 8
  %4 = load ptr, ptr %endpoint, align 8
  %5 = load ptr, ptr @"%s.28", align 8
  call void (ptr, ...) @printf(ptr %5, ptr %4)
  %6 = load ptr, ptr @"%s.29", align 8
  call void (ptr, ...) @printf(ptr %6, ptr @143)
  %7 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %9 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  call void @flush()
  %11 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  br label %afterNestedBlock
}

define void @post_request_handler(i32 %0, ptr %1, ptr %2) !rt !89 {
entry:
  %client_socket = alloca i32, align 4
  store i32 %0, ptr %client_socket, align 4
  %req = alloca ptr, align 8
  store ptr %1, ptr %req, align 8
  %endpoint = alloca ptr, align 8
  store ptr %2, ptr %endpoint, align 8
  %plain_text_response = alloca ptr, align 8
  store ptr @145, ptr %plain_text_response, align 8
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
  ret void

nestedBlock:                                      ; preds = %entry
  %req7 = load ptr, ptr %req, align 8
  %3 = load ptr, ptr %req, align 8
  %4 = load ptr, ptr @"%s.30", align 8
  call void (ptr, ...) @printf(ptr %4, ptr %3)
  %5 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %checkContinueBlock, label %afterNestedBlock

checkContinueBlock:                               ; preds = %nestedBlock
  %7 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %nestedBlock1, label %afterNestedBlock

nestedBlock1:                                     ; preds = %checkContinueBlock
  call void @flush()
  %9 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %11 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  store ptr @147, ptr %plain_text_response, align 8
  %13 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %15 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  %client_socket8 = load i32, ptr %client_socket, align 4
  %17 = load i32, ptr %client_socket, align 4
  %plain_text_response9 = load ptr, ptr %plain_text_response, align 8
  %18 = load ptr, ptr %plain_text_response, align 8
  call void @send_response(i32 %17, ptr @148, ptr @149, ptr %18)
  %19 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  br label %afterNestedBlock
}

define void @main() !rt !90 {
entry:
  br label %nestedBlock

afterNestedBlock:                                 ; preds = %checkContinueBlock10, %nestedBlock9, %checkContinueBlock8, %nestedBlock7, %checkContinueBlock6, %nestedBlock5, %checkContinueBlock4, %nestedBlock3, %checkContinueBlock2, %nestedBlock1, %checkContinueBlock, %nestedBlock
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
  call void @set_route(ptr @150, ptr @151, ptr @my_request_handler)
  %4 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %checkContinueBlock2, label %afterNestedBlock

checkContinueBlock2:                              ; preds = %nestedBlock1
  %6 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %nestedBlock3, label %afterNestedBlock

nestedBlock3:                                     ; preds = %checkContinueBlock2
  call void @set_route(ptr @152, ptr @153, ptr @my_request_handler)
  %8 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %checkContinueBlock4, label %afterNestedBlock

checkContinueBlock4:                              ; preds = %nestedBlock3
  %10 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %nestedBlock5, label %afterNestedBlock

nestedBlock5:                                     ; preds = %checkContinueBlock4
  call void @set_route(ptr @154, ptr @155, ptr @my_request_handler)
  %12 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %checkContinueBlock6, label %afterNestedBlock

checkContinueBlock6:                              ; preds = %nestedBlock5
  %14 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %nestedBlock7, label %afterNestedBlock

nestedBlock7:                                     ; preds = %checkContinueBlock6
  call void @set_route(ptr @156, ptr @157, ptr @post_request_handler)
  %16 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %checkContinueBlock8, label %afterNestedBlock

checkContinueBlock8:                              ; preds = %nestedBlock7
  %18 = load i32, ptr @flowmain_FLOWWING_CONTINUE_COUNT, align 4
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %nestedBlock9, label %afterNestedBlock

nestedBlock9:                                     ; preds = %checkContinueBlock8
  call void @start_server()
  %20 = load i32, ptr @flowmain_FLOWWING_BREAK_COUNT, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %checkContinueBlock10, label %afterNestedBlock

checkContinueBlock10:                             ; preds = %nestedBlock9
  br label %afterNestedBlock
}

define internal void @"assign_<Array[100]<'String'>>:100,"(ptr %0) {
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
  %2 = icmp slt i32 %1, 100
  %3 = load i32, ptr %numberOfElementsFilled, align 4
  %4 = icmp slt i32 %3, 100
  %5 = and i1 %2, %4
  br i1 %5, label %AssignExpr.loopBody-0, label %AssignExpr.loopEnd-0

AssignExpr.loopBody-0:                            ; preds = %AssignExpr.loopCmp-0
  %6 = load i32, ptr %"0_i", align 4
  %7 = getelementptr [100 x ptr], ptr %0, i32 0, i32 %6
  store ptr @38, ptr %7, align 8
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

define internal void @"assign_<ObjectHeader.1>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 0
  store ptr @53, ptr %1, align 8
  %2 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 1
  store ptr @54, ptr %2, align 8
  %3 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 2
  store ptr @55, ptr %3, align 8
  %4 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 3
  store i1 false, ptr %4, align 1
  %5 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 4
  store ptr @56, ptr %5, align 8
  %6 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 5
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 6
  store ptr @57, ptr %7, align 8
  %8 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 7
  store ptr @58, ptr %8, align 8
  %9 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 8
  store ptr @59, ptr %9, align 8
  %10 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 9
  store ptr @60, ptr %10, align 8
  %11 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 10
  store ptr @61, ptr %11, align 8
  %12 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 11
  store ptr @62, ptr %12, align 8
  %13 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 12
  store i1 false, ptr %13, align 1
  %14 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 13
  store ptr @63, ptr %14, align 8
  %15 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 14
  store ptr @64, ptr %15, align 8
  %16 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 15
  store ptr @65, ptr %16, align 8
  %17 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 16
  store ptr @66, ptr %17, align 8
  %18 = getelementptr inbounds %Header.1, ptr %0, i32 0, i32 17
  store i32 0, ptr %18, align 4
  ret void
}

define internal void @"assign_<Class<Vec::String>>"(ptr %0) {
entry:
  %1 = getelementptr inbounds %"Vec::String", ptr %0, i32 0, i32 0
  store ptr @137, ptr %1, align 8
  %2 = getelementptr inbounds %"Vec::String", ptr %0, i32 0, i32 1
  store ptr @138, ptr %2, align 8
  ret void
}

!0 = !{!"Vec::Int.init0:rt:pr:27"}
!1 = !{!"Vec::Int.add:rt:pr:27"}
!2 = !{!"Vec::Int.get:rt:pr:28"}
!3 = !{!"Vec::Int.remove:rt:pr:27"}
!4 = !{!"Vec::Int.size:rt:pr:28"}
!5 = !{!"Vec::Int.free:rt:pr:27"}
!6 = !{!"Vec::Bool.init0:rt:pr:27"}
!7 = !{!"Vec::Bool.add:rt:pr:27"}
!8 = !{!"Vec::Bool.get:rt:pr:34"}
!9 = !{!"Vec::Bool.remove:rt:pr:27"}
!10 = !{!"Vec::Bool.size:rt:pr:28"}
!11 = !{!"Vec::Bool.free:rt:pr:27"}
!12 = !{!"Vec::String.init0:rt:pr:27"}
!13 = !{!"Vec::String.add:rt:pr:27"}
!14 = !{!"Vec::String.get:rt:pr:33"}
!15 = !{!"Vec::String.remove:rt:pr:27"}
!16 = !{!"Vec::String.size:rt:pr:28"}
!17 = !{!"Vec::String.free:rt:pr:27"}
!18 = !{!"Vec::Deci.init0:rt:pr:27"}
!19 = !{!"Vec::Deci.add:rt:pr:27"}
!20 = !{!"Vec::Deci.get:rt:pr:31"}
!21 = !{!"Vec::Deci.remove:rt:pr:27"}
!22 = !{!"Vec::Deci.size:rt:pr:28"}
!23 = !{!"Vec::Deci.free:rt:pr:27"}
!24 = !{!"Str::charAt:rt:pr:33"}
!25 = !{!"Str::indexOfChar:rt:pr:28"}
!26 = !{!"Str::trimInPlace:rt:pr:33"}
!27 = !{!"Str::subStrIndex:rt:pr:28"}
!28 = !{!"Str::reverseInPlace:rt:pr:27"}
!29 = !{!"strFindChar:rt:pr:33"}
!30 = !{!"Str::replaceInPlace:rt:pr:33"}
!31 = !{!"Str::subStr:rt:pr:33"}
!32 = !{!"Str::reverse:rt:pr:33"}
!33 = !{!"Str::length:rt:pr:28"}
!34 = !{!"Str::compare:rt:pr:28"}
!35 = !{!"Str::concat:rt:pr:33"}
!36 = !{!"Str::makeCopy:rt:pr:27"}
!37 = !{!"strToLower:rt:pr:33"}
!38 = !{!"strReverse:rt:pr:33"}
!39 = !{!"strFind:rt:pr:33"}
!40 = !{!"strCompare:rt:pr:28"}
!41 = !{!"strTrim:rt:pr:33"}
!42 = !{!"Str::toLower:rt:pr:33"}
!43 = !{!"int8ToStr:rt:pr:33"}
!44 = !{!"strLength:rt:pr:28"}
!45 = !{!"Str::int8ToString:rt:pr:33"}
!46 = !{!"strCharAt:rt:pr:33"}
!47 = !{!"strToUpper:rt:pr:33"}
!48 = !{!"Str::toUpper:rt:pr:33"}
!49 = !{!"strReplace:rt:pr:33"}
!50 = !{!"strCopy:rt:pr:27"}
!51 = !{!"string_vector_add:rt:pr:27"}
!52 = !{!"int_vector_free:rt:pr:27"}
!53 = !{!"double_vector_free:rt:pr:27"}
!54 = !{!"int_vector_new:rt:pr:33"}
!55 = !{!"double_vector_remove:rt:pr:27"}
!56 = !{!"double_vector_new:rt:pr:33"}
!57 = !{!"string_vector_free:rt:pr:27"}
!58 = !{!"double_vector_get:rt:pr:31"}
!59 = !{!"string_vector_size:rt:pr:28"}
!60 = !{!"bool_vector_size:rt:pr:28"}
!61 = !{!"string_vector_remove:rt:pr:27"}
!62 = !{!"double_vector_add:rt:pr:27"}
!63 = !{!"bool_vector_free:rt:pr:27"}
!64 = !{!"int_vector_remove:rt:pr:27"}
!65 = !{!"bool_vector_remove:rt:pr:27"}
!66 = !{!"string_vector_get:rt:pr:33"}
!67 = !{!"int_vector_size:rt:pr:28"}
!68 = !{!"bool_vector_add:rt:pr:27"}
!69 = !{!"string_vector_new:rt:pr:33"}
!70 = !{!"bool_vector_new:rt:pr:33"}
!71 = !{!"double_vector_size:rt:pr:28"}
!72 = !{!"bool_vector_get:rt:pr:34"}
!73 = !{!"int_vector_get:rt:pr:28"}
!74 = !{!"int_vector_add:rt:pr:27"}
!75 = !{!"start_server:rt:pr:27"}
!76 = !{!"flush:rt:pr:27"}
!77 = !{!"set_route:rt:pr:27"}
!78 = !{!"set_middleware:rt:pr:27"}
!79 = !{!"send_response:rt:pr:27"}
!80 = !{!"send:rt:pr:27"}
!81 = !{!"strlen:rt:pr:28"}
!82 = !{!"len:rt:pr:28"}
!83 = !{!"generate_response:rt:pr:33"}
!84 = !{!"json_response:rt:pr:33"}
!85 = !{!"my_request_handler:rt:pr:27"}
!86 = !{!"split:rt:ay:33:sz:100:"}
!87 = !{!"parse_request:rt:ob:Vec::String"}
!88 = !{!"log_middleware:rt:pr:27"}
!89 = !{!"post_request_handler:rt:pr:27"}
!90 = !{!"main:rt:pr:27"}
