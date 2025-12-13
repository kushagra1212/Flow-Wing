Do not store object file in single directory Done
add file test, nested file test Done
organize build system Done
work on cpack (Windows, Linux, Mac)
Add Error Tests Done

MAJOR REFACTORING IN PROGRESS

LLVM Optimization Passes Needed

mem2reg
The "Alloca" code above is inefficient because reading/writing memory is slow.

However, LLVM includes a standard optimization pass called mem2reg (Promote Memory to Register).
