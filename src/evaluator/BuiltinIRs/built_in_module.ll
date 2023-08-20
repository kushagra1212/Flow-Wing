; ModuleID = 'built_in_module'
source_filename = "built_in_module"

define void @print(i8* %0) {
entry:
  %1 = call i32 @puts(i8* %0)
  ret void
}

define i1 @compareIntegers(i32 %left, i32 %right) {
  %comparisonResult = icmp slt i32 %left, %right
  ret i1 %comparisonResult
}

declare i32 @puts(i8*)
