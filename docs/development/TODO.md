
LLVM Optimization Passes Needed

- proper lamda function
- passing function as param
- returning function from function
- function as object property

mem2reg
The "Alloca" code above is inefficient because reading/writing memory is slow.

However, LLVM includes a standard optimization pass called mem2reg (Promote Memory to Register).
