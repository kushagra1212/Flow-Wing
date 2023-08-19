; ModuleID = 'built_in_module'
source_filename = "built_in_module"

define void @print(i8* %0) {
entry:
  %1 = call i32 @puts(i8* %0)
  ret void
}

declare i32 @puts(i8*)
