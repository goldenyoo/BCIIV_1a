### --------------------------------------------------------------------
### mydc.s
###
### Desk Calculator (dc)
### --------------------------------------------------------------------

	.equ   ARRAYSIZE, 20
	.equ   EOF, -1
	.equ	OFFSET_4, 4
	.equ	OFFSET_8, 8
	.equ	FALSE, 0
	
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
	addl    $OFFSET_8, %esp

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
	addl $OFFSET_4, %esp
	cmpl $FALSE, %eax
	jne is_digit #if it is digit

	# This part checks if the first letter of buffer is 'p'
	# Check buffer[0] == 'p'
	movl $0, %ecx
	movl $p, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_p

	# This part checks if the first letter of buffer is 'q'
	# Check buffer[0] == 'q'
	movl $0, %ecx
	movl $q, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je quit

	# This part checks if the first letter of buffer is '+'
	# Check buffer[0] == '+'
	movl $0, %ecx
	movl $plus, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_plus

	# This part checks if the first letter of buffer is '-'
	# Check buffer[0] == '-'
	movl $0, %ecx
	movl $minus, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_minus

	# This part checks if the first letter of buffer is '*'
	# Check buffer[0] == '*'
	movl $0, %ecx
	movl $multiply, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_multiply

	# This part checks if the first letter of buffer is '/'
	# Check buffer[0] == '/'
	movl $0, %ecx
	movl $division, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_division

	# This part checks if the first letter of buffer is '%'
	# Check buffer[0] == '%'
	movl $0, %ecx
	movl $modulus, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_modulus

	# This part checks if the first letter of buffer is '^'
	# Check buffer[0] == '^'
	movl $0, %ecx
	movl $exponent, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx	
	je is_exponent

	# This part checks if the first letter of buffer is 'f'
	# Check buffer[0] == 'f'
	movl $0, %ecx
	movl $f, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	movl %esp, %ecx
	je is_f_before

	# This part checks if the first letter of buffer is 'c'
	# Check buffer[0] == 'c'
	movl $0, %ecx
	movl $c, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_c

	# This part checks if the first letter of buffer is 'd'
	# Check buffer[0] == 'd'
	movl $0, %ecx
	movl $d, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_d

	# This part checks if the first letter of buffer is 'r'
	# Check buffer[0] == 'r'
	movl $0, %ecx
	movl $r, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_r

	# This part checks if the first letter of buffer is '_'
	# Check buffer[0] == '_'
	movl $0, %ecx
	movl $underbar, %eax
	movb (%eax), %cl
	cmp %ecx, %ebx
	je is_underbar
	
	# Input has basic error, go back to start
	jmp input


# ----------------------------------------------------------------------------------------
# is_p:
# First, check stack has operand. If stack has no operand to print, go to 'is_empty'.
# If stack do has operand, print it.
# ----------------------------------------------------------------------------------------
is_p:
	cmpl %esp, %ebp
	je is_empty

	pushl (%esp)
	pushl $printfFormat
	call printf
	addl $OFFSET_8, %esp

	jmp input
	
# ----------------------------------------------------------------------------------------
# is_plus:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform plus and push the value to stack.
# ----------------------------------------------------------------------------------------
is_plus:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	addl %ebx, %eax
	pushl %eax

	jmp input


# ----------------------------------------------------------------------------------------
# is_minus:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform subtraction and push the value to stack.
# ----------------------------------------------------------------------------------------
is_minus:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	subl %eax, %ebx
	pushl %ebx

	jmp input

# ----------------------------------------------------------------------------------------
# is_multiply:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform multiplication and push the value to stack.
# ----------------------------------------------------------------------------------------
is_multiply:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	imul %ebx

	pushl %eax

	jmp input


# ----------------------------------------------------------------------------------------
# is_division:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform division and push the value to stack.
# ----------------------------------------------------------------------------------------
is_division:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %eax
	CDQ
	addl $OFFSET_4, %esp


	idiv %ebx

	pushl %eax

	jmp input

# ----------------------------------------------------------------------------------------
# is_modulus:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform modulus operation and push the value to stack.
# ----------------------------------------------------------------------------------------
is_modulus:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %eax
	CDQ
	addl $OFFSET_4, %esp

	idiv %ebx

	pushl %edx

	jmp input


# ----------------------------------------------------------------------------------------
# is_exponent:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# go to 'expo_fuction'.
# ----------------------------------------------------------------------------------------
is_exponent:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %ecx
	addl $OFFSET_4, %esp

	cmpl $1, %ecx
	je input

	cmpl %esp, %ebp
	je is_incomplete

	movl (%esp), %eax
	addl $OFFSET_4, %esp

	pushl %ecx
	movl $1, %ecx
	movl %eax, %ebx
	jmp expo_fuction

# ----------------------------------------------------------------------------------------
# expo_function:
# Using two operand, perform exponential operation and push the value to stack.
# ----------------------------------------------------------------------------------------
expo_function:
	imul %ebx

	incl %ecx

	cmpl (%esp), %ecx
	jne expo_fuction

	addl $OFFSET_4, %esp

	pushl %eax
	jmp input

# ----------------------------------------------------------------------------------------
# is_f_before:
# Before go to 'is_f', I want to make sure stack is empty or not.
# If stack is empty, go to 'is_empty'. Else go to 'is_f'
# ----------------------------------------------------------------------------------------
is_f_before:
	cmpl %esp, %ebp
	je is_empty

	jmp is_f

# ----------------------------------------------------------------------------------------
# is_f:
# Print the contents of the stack in LIFO order.
# ----------------------------------------------------------------------------------------
is_f:
	cmpl  %ecx, %ebp
	jle input

	pushl %ecx
	pushl (%ecx)
	pushl $printfFormat
	call printf
	addl $OFFSET_8, %esp
	popl %ecx

	addl $OFFSET_4, %ecx
	jmp is_f

# ----------------------------------------------------------------------------------------
# is_c:
# Clears the contents of the stack.
# ----------------------------------------------------------------------------------------
is_c:
	movl %ebp, %esp
	jmp input

# ----------------------------------------------------------------------------------------
# is_d:
# Duplicates the top-most entry.
# ----------------------------------------------------------------------------------------
is_d:
	cmpl %esp, %ebp
	je is_empty

	movl (%esp), %eax
	pushl %eax
	jmp input


# ----------------------------------------------------------------------------------------
# is_r:
# Reverses the order of the top two values on the stack.
# ----------------------------------------------------------------------------------------
is_r:
	cmpl %esp, %ebp
	je is_empty

	popl %ebx
	popl %eax

	pushl %ebx
	pushl %eax

	jmp input

# ----------------------------------------------------------------------------------------
# is_digit:
# From the standard input, we convert input to as number value using function 'atoi'.
# After 'atoi', push the value to stack
# ----------------------------------------------------------------------------------------
is_digit:
	movl $buffer,%ebx
	pushl %ebx
	call atoi
	addl $OFFSET_4, %esp

	pushl %eax

	jmp input

# ----------------------------------------------------------------------------------------
# is_underbar:
# From the standard input, we convert input to as negative number by ignoring the 
# first under-bar character.
# ----------------------------------------------------------------------------------------
is_underbar:
	movl $buffer, %eax
	incl %eax

	pushl %eax
	call atoi
	addl $OFFSET_4, %esp

	negl %eax
	pushl %eax

	jmp input

# ----------------------------------------------------------------------------------------
# is_incomplete:
# stack has only one operand. Therefore printing out error message to standard output.
# Before print out error message, we have to push back the operand to stack.
# ----------------------------------------------------------------------------------------
is_incomplete:
	pushl %eax

	pushl $emptyErrorMSg
	call printf
	addl $OFFSET_4, %esp

	jmp input

# ----------------------------------------------------------------------------------------
# is_empty:
# stack has no operand. Therefore printing out error message to standard output.
# ----------------------------------------------------------------------------------------
is_empty:
	pushl $emptyErrorMSg
	call printf
	addl $OFFSET_4, %esp
	
	jmp input

quit:	
	## return 0
	movl    $0, %eax
	movl    %ebp, %esp
	popl    %ebp
	ret
