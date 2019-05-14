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
	cmp %ecx, %ebx
	je quit


	# movl $buffer, %eax
	# pushl %eax
	# call atoi
	# addl $4, %esp

	# pushl %eax

	# pushl $printfFormat
	# call printf
	# addl $8, %esp
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




is_digit:
	movl $buffer,%ebx
	pushl %ebx
	call atoi
	addl $4, %esp

	pushl %eax

	# pushl (%esp)
	# pushl $printfFormat
	# call printf
	# addl $8, %esp
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
