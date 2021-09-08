# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	# 
N:	.long 1000	    # 
S:	.long 0		    # 
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# 
.globl main
main:	
	pushl %ebp	    # save base pointer
	movl %esp, %ebp	# ebp = esp

 	# initialize
    movl N, %ebx	# ebx = N

 	# compute sum
L1:
	addl %ebx, S	# S = S + ebx 
	decl %ebx       # ebx--
	cmpl $0, %ebx   # if(ebx<0)
	jng  L2	    	# goto L2
    movl $L1, %eax	# eax take adres of label l=L1
    jmp *%eax   	# jump to L1

L2:
	# print result
	pushl S	    	# push S in the stack
	pushl N	       # push N in stack
	pushl $Msg  	# push Msg in stack
	call printf 	# ektipwnei
	popl %eax   	# restore the content of Msg 
	popl %eax   	# restore the content of N
	popl %eax   	# restore the content of S 

	# exit
	movl $0, %eax  	# eax=0
    leave	    	#Set ESP to EBP, then pop EBP.
 	ret             #return
