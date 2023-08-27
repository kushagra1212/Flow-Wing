; ModuleID = 'built_in_module'
source_filename = "built_in_module"

@.str = private constant [3 x i8] c"%s\00"

define void @print(i8* %0) {
entry:
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i8* %0)
  ret void
}

declare i32 @printf(i8*, ...)
