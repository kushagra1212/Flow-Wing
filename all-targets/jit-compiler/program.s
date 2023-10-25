	.text
	.file	"Elang"
	.globl	print                           # -- Begin function print
	.p2align	4, 0x90
	.type	print,@function
print:                                  # @print
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rdi, %rax
	testb	$1, %sil
	je	.LBB0_1
# %bb.3:                                # %newline
	movq	formatStrprintfnewline@GOTPCREL(%rip), %rdi
	jmp	.LBB0_2
.LBB0_1:                                # %withoutnewline
	movq	formatStrprintf@GOTPCREL(%rip), %rdi
.LBB0_2:                                # %exit
	movq	%rax, %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	print, .Lfunc_end0-print
	.cfi_endproc
                                        # -- End function
	.globl	concat_strings                  # -- Begin function concat_strings
	.p2align	4, 0x90
	.type	concat_strings,@function
concat_strings:                         # @concat_strings
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	pushq	%rax
	.cfi_def_cfa_offset 64
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rsi, %rbx
	movq	%rdi, %r14
	callq	strlen@PLT
	movq	%rax, %r15
	movq	%rbx, %rdi
	callq	strlen@PLT
	movq	%rax, %r12
	leaq	(%r15,%rax), %r13
	movq	%r13, %rdi
	callq	malloc@PLT
	movq	%rax, %rbp
	movq	%rax, %rdi
	movq	%r14, %rsi
	movq	%r15, %rdx
	xorl	%ecx, %ecx
	callq	memcpy@PLT
	addq	%rbp, %r15
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movq	%r12, %rdx
	xorl	%ecx, %ecx
	callq	memcpy@PLT
	movb	$0, (%rbp,%r13)
	movq	%rbp, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	concat_strings, .Lfunc_end1-concat_strings
	.cfi_endproc
                                        # -- End function
	.globl	stringLength                    # -- Begin function stringLength
	.p2align	4, 0x90
	.type	stringLength,@function
stringLength:                           # @stringLength
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strlen@PLT
                                        # kill: def $eax killed $eax killed $rax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	stringLength, .Lfunc_end2-stringLength
	.cfi_endproc
                                        # -- End function
	.globl	itos                            # -- Begin function itos
	.p2align	4, 0x90
	.type	itos,@function
itos:                                   # @itos
	.cfi_startproc
# %bb.0:
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movl	%edi, %ebx
	movl	$12, %edi
	callq	malloc@PLT
	movq	%rax, %r14
	movq	intFormat@GOTPCREL(%rip), %rdx
	movl	$12, %esi
	movq	%rax, %rdi
	movl	%ebx, %ecx
	callq	snprintf@PLT
	movq	%r14, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	itos, .Lfunc_end3-itos
	.cfi_endproc
                                        # -- End function
	.globl	dtos                            # -- Begin function dtos
	.p2align	4, 0x90
	.type	dtos,@function
dtos:                                   # @dtos
	.cfi_startproc
# %bb.0:
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movl	%edi, %ebx
	movl	$16, %edi
	callq	malloc@PLT
	movq	%rax, %r14
	movq	doubleFormat@GOTPCREL(%rip), %rdx
	movl	$16, %esi
	movq	%rax, %rdi
	movl	%ebx, %ecx
	callq	snprintf@PLT
	movq	%r14, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end4:
	.size	dtos, .Lfunc_end4-dtos
	.cfi_endproc
                                        # -- End function
	.globl	getMallocPtrOfStringConstant    # -- Begin function getMallocPtrOfStringConstant
	.p2align	4, 0x90
	.type	getMallocPtrOfStringConstant,@function
getMallocPtrOfStringConstant:           # @getMallocPtrOfStringConstant
	.cfi_startproc
# %bb.0:
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	movq	%rdi, %rbx
	callq	strlen@PLT
	leaq	1(%rax), %r14
	movq	%r14, %rdi
	callq	malloc@PLT
	movq	%rax, %r15
	movq	%rax, %rdi
	movq	%rbx, %rsi
	movq	%r14, %rdx
	xorl	%ecx, %ecx
	callq	memcpy@PLT
	movq	%r15, %rax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end5:
	.size	getMallocPtrOfStringConstant, .Lfunc_end5-getMallocPtrOfStringConstant
	.cfi_endproc
                                        # -- End function
	.globl	getMallocPtrofIntConstant       # -- Begin function getMallocPtrofIntConstant
	.p2align	4, 0x90
	.type	getMallocPtrofIntConstant,@function
getMallocPtrofIntConstant:              # @getMallocPtrofIntConstant
	.cfi_startproc
# %bb.0:
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movl	%edi, %ebx
	movl	$12, %edi
	callq	malloc@PLT
	movq	%rax, %r14
	movq	intFormat@GOTPCREL(%rip), %rdx
	movl	$12, %esi
	movq	%rax, %rdi
	movl	%ebx, %ecx
	callq	snprintf@PLT
	movq	%r14, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end6:
	.size	getMallocPtrofIntConstant, .Lfunc_end6-getMallocPtrofIntConstant
	.cfi_endproc
                                        # -- End function
	.globl	compare_strings                 # -- Begin function compare_strings
	.p2align	4, 0x90
	.type	compare_strings,@function
compare_strings:                        # @compare_strings
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strcmp@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end7:
	.size	compare_strings, .Lfunc_end7-compare_strings
	.cfi_endproc
                                        # -- End function
	.globl	less_than_strings               # -- Begin function less_than_strings
	.p2align	4, 0x90
	.type	less_than_strings,@function
less_than_strings:                      # @less_than_strings
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strcmp@PLT
	shrl	$31, %eax
                                        # kill: def $al killed $al killed $eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end8:
	.size	less_than_strings, .Lfunc_end8-less_than_strings
	.cfi_endproc
                                        # -- End function
	.globl	less_than_or_equal_strings      # -- Begin function less_than_or_equal_strings
	.p2align	4, 0x90
	.type	less_than_or_equal_strings,@function
less_than_or_equal_strings:             # @less_than_or_equal_strings
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strcmp@PLT
	testl	%eax, %eax
	setle	%al
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end9:
	.size	less_than_or_equal_strings, .Lfunc_end9-less_than_or_equal_strings
	.cfi_endproc
                                        # -- End function
	.globl	greater_than_strings            # -- Begin function greater_than_strings
	.p2align	4, 0x90
	.type	greater_than_strings,@function
greater_than_strings:                   # @greater_than_strings
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strcmp@PLT
	testl	%eax, %eax
	setg	%al
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end10:
	.size	greater_than_strings, .Lfunc_end10-greater_than_strings
	.cfi_endproc
                                        # -- End function
	.globl	greater_than_or_equal_strings   # -- Begin function greater_than_or_equal_strings
	.p2align	4, 0x90
	.type	greater_than_or_equal_strings,@function
greater_than_or_equal_strings:          # @greater_than_or_equal_strings
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strcmp@PLT
	testl	%eax, %eax
	setns	%al
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end11:
	.size	greater_than_or_equal_strings, .Lfunc_end11-greater_than_or_equal_strings
	.cfi_endproc
                                        # -- End function
	.globl	equal_strings                   # -- Begin function equal_strings
	.p2align	4, 0x90
	.type	equal_strings,@function
equal_strings:                          # @equal_strings
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strcmp@PLT
	testl	%eax, %eax
	sete	%al
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end12:
	.size	equal_strings, .Lfunc_end12-equal_strings
	.cfi_endproc
                                        # -- End function
	.globl	getInput                        # -- Begin function getInput
	.p2align	4, 0x90
	.type	getInput,@function
getInput:                               # @getInput
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$1000001, %edi                  # imm = 0xF4241
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	formatStrscanf@GOTPCREL(%rip), %rdi
	movq	%rax, %rsi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	callq	scanf@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end13:
	.size	getInput, .Lfunc_end13-getInput
	.cfi_endproc
                                        # -- End function
	.globl	stringToInt                     # -- Begin function stringToInt
	.p2align	4, 0x90
	.type	stringToInt,@function
stringToInt:                            # @stringToInt
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	atoi@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end14:
	.size	stringToInt, .Lfunc_end14-stringToInt
	.cfi_endproc
                                        # -- End function
	.globl	stringToLong                    # -- Begin function stringToLong
	.p2align	4, 0x90
	.type	stringToLong,@function
stringToLong:                           # @stringToLong
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	atol@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end15:
	.size	stringToLong, .Lfunc_end15-stringToLong
	.cfi_endproc
                                        # -- End function
	.globl	stringToDouble                  # -- Begin function stringToDouble
	.p2align	4, 0x90
	.type	stringToDouble,@function
stringToDouble:                         # @stringToDouble
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	atof@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end16:
	.size	stringToDouble, .Lfunc_end16-stringToDouble
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	HELLO_WORLD@GOTPCREL(%rip), %rdi
	xorl	%esi, %esi
	callq	print@PLT
	movl	$5, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end17:
	.size	main, .Lfunc_end17-main
	.cfi_endproc
                                        # -- End function
	.globl	evaluateBlockStatement          # -- Begin function evaluateBlockStatement
	.p2align	4, 0x90
	.type	evaluateBlockStatement,@function
evaluateBlockStatement:                 # @evaluateBlockStatement
	.cfi_startproc
# %bb.0:                                # %entry
	movl	$2, -4(%rsp)
	movq	ELANG_GLOBAL_ERROR_COUNT@GOTPCREL(%rip), %rax
	movl	(%rax), %eax
	retq
.Lfunc_end18:
	.size	evaluateBlockStatement, .Lfunc_end18-evaluateBlockStatement
	.cfi_endproc
                                        # -- End function
	.type	formatStrprintfnewline,@object  # @formatStrprintfnewline
	.data
	.globl	formatStrprintfnewline
formatStrprintfnewline:
	.asciz	"%s\n"
	.size	formatStrprintfnewline, 4

	.type	formatStrprintf,@object         # @formatStrprintf
	.globl	formatStrprintf
formatStrprintf:
	.asciz	"%s"
	.size	formatStrprintf, 3

	.type	intFormat,@object               # @intFormat
	.globl	intFormat
intFormat:
	.asciz	"%d"
	.size	intFormat, 3

	.type	doubleFormat,@object            # @doubleFormat
	.globl	doubleFormat
doubleFormat:
	.asciz	"%.6f"
	.size	doubleFormat, 5

	.type	formatStrscanf,@object          # @formatStrscanf
	.globl	formatStrscanf
formatStrscanf:
	.asciz	"%1000000s"
	.size	formatStrscanf, 10

	.type	ELANG_GLOBAL_TRUE,@object       # @ELANG_GLOBAL_TRUE
	.globl	ELANG_GLOBAL_TRUE
ELANG_GLOBAL_TRUE:
	.asciz	"true"
	.size	ELANG_GLOBAL_TRUE, 5

	.type	ELANG_GLOBAL_FALSE,@object      # @ELANG_GLOBAL_FALSE
	.globl	ELANG_GLOBAL_FALSE
ELANG_GLOBAL_FALSE:
	.asciz	"false"
	.size	ELANG_GLOBAL_FALSE, 6

	.type	ELANG_GLOBAL_NULL,@object       # @ELANG_GLOBAL_NULL
	.bss
	.globl	ELANG_GLOBAL_NULL
	.p2align	3, 0x0
ELANG_GLOBAL_NULL:
	.quad	0
	.size	ELANG_GLOBAL_NULL, 8

	.type	ELANG_BREAK_COUNT,@object       # @ELANG_BREAK_COUNT
	.globl	ELANG_BREAK_COUNT
	.p2align	2, 0x0
ELANG_BREAK_COUNT:
	.long	0                               # 0x0
	.size	ELANG_BREAK_COUNT, 4

	.type	ELANG_CONTINUE_COUNT,@object    # @ELANG_CONTINUE_COUNT
	.globl	ELANG_CONTINUE_COUNT
	.p2align	2, 0x0
ELANG_CONTINUE_COUNT:
	.long	0                               # 0x0
	.size	ELANG_CONTINUE_COUNT, 4

	.type	ELANG_GLOBAL_ZERO,@object       # @ELANG_GLOBAL_ZERO
	.globl	ELANG_GLOBAL_ZERO
	.p2align	2, 0x0
ELANG_GLOBAL_ZERO:
	.long	0                               # 0x0
	.size	ELANG_GLOBAL_ZERO, 4

	.type	ELANG_GLOBAL_ERROR_COUNT,@object # @ELANG_GLOBAL_ERROR_COUNT
	.globl	ELANG_GLOBAL_ERROR_COUNT
	.p2align	2, 0x0
ELANG_GLOBAL_ERROR_COUNT:
	.long	0                               # 0x0
	.size	ELANG_GLOBAL_ERROR_COUNT, 4

	.type	HELLO_WORLD,@object             # @HELLO_WORLD
	.data
	.globl	HELLO_WORLD
HELLO_WORLD:
	.asciz	"Hello, World!"
	.size	HELLO_WORLD, 14

	.section	".note.GNU-stack","",@progbits
