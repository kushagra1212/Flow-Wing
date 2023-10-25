; ModuleID = 'built_in_module'
source_filename = "built_in_module"

@formatStrprintfnewline = global [4 x i8] c"%s\0A\00"
@formatStrprintf = global [3 x i8] c"%s\00"

define void @print(i8* %0, i1 %1) {
entry:
  br i1 %1, label %newline, label %withoutnewline

exit:                                             ; preds = %withoutnewline, %newline
  ret void

withoutnewline:                                   ; preds = %entry
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @formatStrprintf, i32 0, i32 0), i8* %0)
  br label %exit

newline:                                          ; preds = %entry
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @formatStrprintfnewline, i32 0, i32 0), i8* %0)
  br label %exit
}

declare i32 @printf(i8*, ...)


