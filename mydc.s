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
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	# Push parameters of the function
	pushl (%esp)
	pushl $printfFormat

	# Call fucntion
	call printf

	#Restore the size of stack
	addl $OFFSET_8, %esp

	jmp input
	
# ----------------------------------------------------------------------------------------
# is_plus:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform plus and push the value to stack.
# ----------------------------------------------------------------------------------------
is_plus:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save the value at EAX and resize the stack
	movl (%esp), %eax
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp # Check stack has only one operand
	je is_incomplete

	#Save the value at EBX and resize the stack
	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	#Add operation
	addl %ebx, %eax

	#Push the value to stack
	pushl %eax

	#Go back to starting point, 'input'
	jmp input


# ----------------------------------------------------------------------------------------
# is_minus:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform subtraction and push the value to stack.
# ----------------------------------------------------------------------------------------
is_minus:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save the value at EAX and resize the stack
	movl (%esp), %eax
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp # Check stack has only one operand
	je is_incomplete

	#Save the value at EBX and resize the stack
	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	#Subtract operation
	subl %eax, %ebx
	
	#Push the value to stack
	pushl %ebx

	#Go back to starting point, 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_multiply:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform multiplication and push the value to stack.
# ----------------------------------------------------------------------------------------
is_multiply:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save the value at EAX and resize the stack
	movl (%esp), %eax
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp # Check stack has only one operand
	je is_incomplete

	#Save the value at EBX and resize the stack
	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	#Multiplaction
	imul %ebx

	#Push the value to stack
	pushl %eax

	#Go back to starting point, 'input'
	jmp input


# ----------------------------------------------------------------------------------------
# is_division:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform division and push the value to stack.
# ----------------------------------------------------------------------------------------
is_division:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save the value at EBX and resize the stack
	movl (%esp), %ebx
	addl $OFFSET_4, %esp


	cmpl %esp, %ebp # Check stack has only one operand
	je is_incomplete

	#Save the value at EAX and resize the stack
	movl (%esp), %eax
	CDQ
	addl $OFFSET_4, %esp

	# Division
	idiv %ebx

	#Push the value to stack
	pushl %eax

	#Go back to starting point, 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_modulus:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# using two operand, perform modulus operation and push the value to stack.
# ----------------------------------------------------------------------------------------
is_modulus:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save the value at EBX and resize the stack
	movl (%esp), %ebx
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete # Check stack has only one operand

	#Save the value at EAX and resize the stack
	movl (%esp), %eax
	CDQ #sign flag
	addl $OFFSET_4, %esp

	#Division
	idiv %ebx

	#push the value of remainder to stack
	pushl %edx

	#Go back to starting point, 'input'
	jmp input


# ----------------------------------------------------------------------------------------
# is_exponent:
# First, check stack has at least two operand. If stack has no operand at all, go to 'is_empty'.
# If stack has only one operand, go to 'is_incomplete. Lastly, if stack has enough operand, 
# go to 'expo_fuction'.
# ----------------------------------------------------------------------------------------
is_exponent:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save the value at ECX and resize the stack
	movl (%esp), %ecx
	addl $OFFSET_4, %esp

	cmpl %esp, %ebp
	je is_incomplete # Check stack has only one operand

	#If the ECX is '1', we don't have to do further consideration.
	# ex) X^(1) = X
	cmpl $1, %ecx
	je input

	#Save the value at EAX and resize the stack
	movl (%esp), %eax
	addl $OFFSET_4, %esp

	#Temporarly save ECX at stack
	pushl %ecx

	#Register initialization
	movl $1, %ecx
	movl %eax, %ebx

	#Go to 'expo_fuction'
	jmp expo_function

# ----------------------------------------------------------------------------------------
# expo_function:
# Using two operand, perform exponential operation and push the value to stack.
# From 'is_exponent', EAX has number value and (%esp) has how many times do we have to 
# do multiplication. ex) 2^(4) -> EAX: 2, (%esp): 4
# Every time we visit 'expo_function', increment ECX. If ECX become equal to (%esp), 
# we stop the multiplication and go to 'input'
# ----------------------------------------------------------------------------------------
expo_function:
	#Multiplication
	imul %ebx

	#Increment ECX
	incl %ecx

	#Compare ECX and (%ESP)
	cmpl (%esp), %ecx
	jne expo_function #Go back to 'expo_function'

	#Remove the value that temporarly saved during 'is_exponent' 
	addl $OFFSET_4, %esp

	#push the value to stack
	pushl %eax

	#Go back to starting point, 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_f_before:
# Before go to 'is_f', I want to make sure stack is empty or not.
# If stack is empty, go to 'is_empty'. Else go to 'is_f'
# ----------------------------------------------------------------------------------------
is_f_before:
	cmpl %esp, %ebp # Check stack is empty
	je is_empty

	#Save current ESP at ECX
	movl %esp, %ecx

	#Go to 'is_f'
	jmp is_f

# ----------------------------------------------------------------------------------------
# is_f:
# Print the contents of the stack in LIFO order.
# ----------------------------------------------------------------------------------------
is_f:
	#Stop repetition when ECX become same with EBP
	cmpl %ecx, %ebp
	je input

	#Push the variable value to stack
	pushl %ecx

	# Push parameters of the function
	pushl (%ecx)
	pushl $printfFormat

	#Call function
	call printf

	#Restore the size of stack
	addl $OFFSET_8, %esp

	#Pop ECX
	popl %ecx

	#Decrement ECX according to stack offset
	addl $OFFSET_4, %ecx

	#Repeat the process
	jmp is_f

# ----------------------------------------------------------------------------------------
# is_c:
# Clears the contents of the stack.
# ----------------------------------------------------------------------------------------
is_c:
	#Equalize ESP to EBP
	movl %ebp, %esp

	#Go back to starting point 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_d:
# Duplicates the top-most entry.
# ----------------------------------------------------------------------------------------
is_d:
	cmpl %esp, %ebp #Check stack is empty or not
	je is_empty

	#Make a duplicate
	movl (%esp), %eax
	
	#Push the value to stack
	pushl %eax

	#Go back to starting point 'input'
	jmp input


# ----------------------------------------------------------------------------------------
# is_r:
# Reverses the order of the top two values on the stack.
# ----------------------------------------------------------------------------------------
is_r:
	cmpl %esp, %ebp #Check stack is empty or not
	je is_empty

	#Pop two operand from the stack
	popl %ebx
	popl %eax

	#Push two value to stack with reversed order
	pushl %ebx
	pushl %eax

	#Go back to starting point 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_digit:
# From the standard input, we convert input to as number value using function 'atoi'.
# After 'atoi', push the value to stack
# ----------------------------------------------------------------------------------------
is_digit:

	movl $buffer,%ebx

	#Push parameters to the stack
	pushl %ebx

	#Call function
	call atoi

	#Restore the size of stack
	addl $OFFSET_4, %esp

	#Push the value to stack
	pushl %eax

	#Go back to starting point 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_underbar:
# From the standard input, we convert input to as negative number by ignoring the 
# first under-bar character.
# ----------------------------------------------------------------------------------------
is_underbar:
	movl $buffer, %eax
	incl %eax

	#Push parameters to the stack
	pushl %eax

	#Call function
	call atoi

	#Restore the size of stack
	addl $OFFSET_4, %esp

	#Convert the value negatively
	negl %eax

	#Push the value to stack
	pushl %eax

	#Go back to starting point 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_incomplete:
# stack has only one operand. Therefore printing out error message to standard output.
# Before print out error message, we have to push back the operand to stack.
# ----------------------------------------------------------------------------------------
is_incomplete:
	#Re-save the value 
	pushl %eax

	#Push parameters to stack
	pushl $emptyErrorMSg

	#Call function
	call printf

	#Restore the stack size
	addl $OFFSET_4, %esp

	#Go back to starting point 'input'
	jmp input

# ----------------------------------------------------------------------------------------
# is_empty:
# stack has no operand. Therefore printing out error message to standard output.
# ----------------------------------------------------------------------------------------
is_empty:
	#Push parameters to stack
	pushl $emptyErrorMSg

	#Call function
	call printf

	#Restore the stack size
	addl $OFFSET_4, %esp

	#Go back to starting point 'input'
	jmp input

quit:	
	## return 0
	movl    $0, %eax
	movl    %ebp, %esp
	popl    %ebp
	ret
