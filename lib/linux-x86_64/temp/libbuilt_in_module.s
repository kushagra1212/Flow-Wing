	.text
	.file	"built_in_module"
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
	movq	%rsi, %r14
	movq	%rdi, %r15
	callq	strlen@PLT
	movl	%eax, %r13d
	movq	%r14, %rdi
	callq	strlen@PLT
	movl	%eax, %r12d
	leal	(%r13,%r12), %ebp
	leal	1(%r13,%r12), %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	callq	memcpy@PLT
	movslq	%r13d, %rdi
	addq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	callq	memcpy@PLT
	movslq	%ebp, %rax
	movb	$0, (%rbx,%rax)
	movq	%rbx, %rax
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
	.globl	string_length                   # -- Begin function string_length
	.p2align	4, 0x90
	.type	string_length,@function
string_length:                          # @string_length
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	strlen@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	string_length, .Lfunc_end2-string_length
	.cfi_endproc
                                        # -- End function
	.globl	itos                            # -- Begin function itos
	.p2align	4, 0x90
	.type	itos,@function
itos:                                   # @itos
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movl	%edi, %ebp
	movl	$12, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	intFormat@GOTPCREL(%rip), %rdx
	movq	%rax, %rdi
	movl	$12, %esi
	movl	%ebp, %ecx
	xorl	%eax, %eax
	callq	snprintf@PLT
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
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
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movsd	%xmm0, 8(%rsp)                  # 8-byte Spill
	movl	$32, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	doubleFormat@GOTPCREL(%rip), %rdx
	movq	%rax, %rdi
	movl	$32, %esi
	movsd	8(%rsp), %xmm0                  # 8-byte Reload
                                        # xmm0 = mem[0],zero
	movb	$1, %al
	callq	snprintf@PLT
	movq	%rbx, %rax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end4:
	.size	dtos, .Lfunc_end4-dtos
	.cfi_endproc
                                        # -- End function
	.globl	get_malloc_ptr_of_string_constant # -- Begin function get_malloc_ptr_of_string_constant
	.p2align	4, 0x90
	.type	get_malloc_ptr_of_string_constant,@function
get_malloc_ptr_of_string_constant:      # @get_malloc_ptr_of_string_constant
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	.cfi_offset %rbp, -16
	movq	%rdi, %r14
	callq	strlen@PLT
                                        # kill: def $eax killed $eax def $rax
	leal	1(%rax), %ebp
	movl	%ebp, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	%rax, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	callq	memcpy@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end5:
	.size	get_malloc_ptr_of_string_constant, .Lfunc_end5-get_malloc_ptr_of_string_constant
	.cfi_endproc
                                        # -- End function
	.globl	get_malloc_ptr_of_int_constant  # -- Begin function get_malloc_ptr_of_int_constant
	.p2align	4, 0x90
	.type	get_malloc_ptr_of_int_constant,@function
get_malloc_ptr_of_int_constant:         # @get_malloc_ptr_of_int_constant
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movl	%edi, %ebp
	movl	$12, %edi
	callq	malloc@PLT
	movq	%rax, %rbx
	movq	intFormat@GOTPCREL(%rip), %rdx
	movq	%rax, %rdi
	movl	$12, %esi
	movl	%ebp, %ecx
	xorl	%eax, %eax
	callq	snprintf@PLT
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end6:
	.size	get_malloc_ptr_of_int_constant, .Lfunc_end6-get_malloc_ptr_of_int_constant
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
	.globl	get_input                       # -- Begin function get_input
	.p2align	4, 0x90
	.type	get_input,@function
get_input:                              # @get_input
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
	.size	get_input, .Lfunc_end13-get_input
	.cfi_endproc
                                        # -- End function
	.globl	string_to_int                   # -- Begin function string_to_int
	.p2align	4, 0x90
	.type	string_to_int,@function
string_to_int:                          # @string_to_int
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	atoi@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end14:
	.size	string_to_int, .Lfunc_end14-string_to_int
	.cfi_endproc
                                        # -- End function
	.globl	string_to_long                  # -- Begin function string_to_long
	.p2align	4, 0x90
	.type	string_to_long,@function
string_to_long:                         # @string_to_long
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	atoll@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end15:
	.size	string_to_long, .Lfunc_end15-string_to_long
	.cfi_endproc
                                        # -- End function
	.globl	string_to_double                # -- Begin function string_to_double
	.p2align	4, 0x90
	.type	string_to_double,@function
string_to_double:                       # @string_to_double
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	atof@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end16:
	.size	string_to_double, .Lfunc_end16-string_to_double
	.cfi_endproc
                                        # -- End function
	.globl	raise_exception                 # -- Begin function raise_exception
	.p2align	4, 0x90
	.type	raise_exception,@function
raise_exception:                        # @raise_exception
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	puts@PLT
	movl	$1, %edi
	callq	exit@PLT
.Lfunc_end17:
	.size	raise_exception, .Lfunc_end17-raise_exception
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

	.type	formatStrscanf,@object          # @formatStrscanf
	.globl	formatStrscanf
formatStrscanf:
	.asciz	"%1000000s"
	.size	formatStrscanf, 10

	.type	intFormat,@object               # @intFormat
	.globl	intFormat
intFormat:
	.asciz	"%d"
	.size	intFormat, 3

	.type	doubleFormat,@object            # @doubleFormat
	.globl	doubleFormat
doubleFormat:
	.asciz	"%.14f"
	.size	doubleFormat, 6

	.section	".note.GNU-stack","",@progbits
