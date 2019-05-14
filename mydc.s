### --------------------------------------------------------------------
### mydc.s
###
### Desk Calculator (dc)
### --------------------------------------------------------------------

	.equ   ARRAYSIZE, 20
	.equ   EOF, -1
	
.section ".rodata"

scanfFormat:
	.asciz "%s"
printfFormat:
	.asciz "%d\n"
printfFormat2:
	.asciz "%x\n"	
printfFormat3:
	.asciz "%c\n"	
emptyErrorMSg:
	.asciz "mydc: stack empty\n"

p:
	.byte 'p'
q:
	.byte 'q'
f:
	.byte 'f'
c:
	.byte 'c'
d:
	.byte 'd'
r:
	.byte 'r'
underbar:
	.byte '_'
plus:
	.byte '+'
minus:
	.byte '-'
multiply:
	.byte '*'
division:
	.byte '/'
modulus:
	.byte '%'
exponent:
	.byte '^'
### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"
buffer:
        .skip  ARRAYSIZE

### --------------------------------------------------------------------

	.section ".text"

	## -------------------------------------------------------------
	## int main(void)
	## Runs desk calculator program.  Returns 0.
	## -------------------------------------------------------------

	.globl  main
	.type   main,@function

main:

	pushl   %ebp
	movl    %esp, %ebp

input:

	## dc number stack initialized. %esp = %ebp
	
	## scanf("%s", buffer)
	pushl	$buffer
	pushl	$scanfFormat
	call    scanf
	addl    $8, %esp

	## check if user input EOF
	cmp	$EOF, %eax
	je	quit
	
	# buffer[0]
	movl $buffer, %eax
	movl $0, %ebx
	movb (%eax), %bl
	
	#isdigit(buffer[0])
	pushl %ebx
	call isdigit
	addl $4, %esp
	cmpl $0, %eax
	jne is_digit #if it is digit

	# buffer[0] == 'p'
	movl $0, %ecx
	movl $p, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_p

	# buffer[0] == 'q'
	movl $0, %ecx
	movl $q, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je quit

	# buffer[0] == '+'
	movl $0, %ecx
	movl $plus, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_plus

	# buffer[0] == '-'
	movl $0, %ecx
	movl $minus, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_minus

	# buffer[0] == '*'
	movl $0, %ecx
	movl $multiply, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_multiply

	# buffer[0] == '/'
	movl $0, %ecx
	movl $division, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_division

	# buffer[0] == '%'
	movl $0, %ecx
	movl $modulus, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_modulus

	# buffer[0] == 'f'
	movl $0, %ecx
	movl $f, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	movl %esp, %ecx
	je is_f_before

	# buffer[0] == 'c'
	movl $0, %ecx
	movl $c, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_c

	# buffer[0] == 'd'
	movl $0, %ecx
	movl $d, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_d

	# buffer[0] == 'r'
	movl $0, %ecx
	movl $r, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_r
	
	jmp quit



is_p:
	cmpl %esp, %ebp
	je is_empty

	pushl (%esp)
	pushl $printfFormat
	call printf
	addl $8, %esp

	jmp input
	# movl $99, %ebx
	# pushl %ebx
	# pushl $printfFormat
	# call printf
	# addl $8, %esp
	# jmp quit

is_plus:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	addl $4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %ebx
	addl $4, %esp

	addl %ebx, %eax
	pushl %eax

	jmp input

is_minus:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	addl $4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %ebx
	addl $4, %esp

	subl %eax, %ebx
	pushl %ebx

	jmp input

is_multiply:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	addl $4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %ebx
	addl $4, %esp

	imul %ebx

	pushl %eax

	jmp input

is_division:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %ebx
	addl $4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %eax
	CDQ
	addl $4, %esp


	idiv %ebx

	pushl %eax

	jmp input

is_modulus:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %ebx
	addl $4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %eax
	CDQ
	addl $4, %esp

	idiv %ebx

	pushl %edx

	jmp input

is_f_before:
	cmpl %esp, %ebp
	je is_empty

	jmp is_f

is_f:
	cmpl  %ecx, %ebp
	jle input

	pushl %ecx
	pushl (%ecx)
	pushl $printfFormat
	call printf
	addl $8, %esp
	popl %ecx

	addl $4, %ecx
	jmp is_f

is_c:
	movl    %ebp, %esp
	jmp input

is_d:
	jmp input

is_r:
	jmp input

is_digit:
	movl $buffer,%ebx
	pushl %ebx
	call atoi
	addl $4, %esp

	pushl %eax

	jmp input


is_incomplete:
	pushl %eax
	pushl $emptyErrorMSg
	call printf
	addl $4, %esp
	jmp input

is_empty:
	pushl $emptyErrorMSg
	call printf
	addl $4, %esp
	jmp input

quit:	
	## return 0
	movl    $0, %eax
	movl    %ebp, %esp
	popl    %ebp
	ret
