@ Dominic Mazza
@ CSE 320
	.global main

        .text
main:   
	push    {lr}

        mov     r4, #0      @ Initialize character count
	mov	r5, #0      @ Initialize newline count
	mov	r6, #0      @ Initialize whitespace count
	mov	r7, #0      @ Initialize alphabetical character count
	mov	r8, #0      @ Initialize decimal digit count
	mov	r9, #0      @ Initialize hexadecimal character count
	mov	r10, #0     @ Initialize arithmetic operator count

loop:   
	bl      getchar     @ Read one character (returned in r0)

        cmp     r0, #-1     @ Compare return value to EOF
        beq     end         @ When EOF found, exit loop
	
	bl	putchar
ifChar:			    @ Checks if the char is an actual ASCII character
	cmp	r0, #0x21
	blt	endifChar
	cmp	r0, #0x7E
	bgt	endifChar
	b	thenChar
thenChar:
	add	r4, r4, #1
endifChar:
	 
ifUpper:		    @ Checks if char is an uppercase alphebtical character
	cmp	r0, #'A'
	blt	endifUpper
	cmp	r0, #'Z'
	bgt	endifUpper
	b	thenUpper
thenUpper:
	add	r7, r7, #1
endifUpper:

ifLower:		    @ Checks if char is a lowercase alphabetical character
	cmp	r0, #'a'
	blt	endifLower
	cmp	r0, #'z'
	bgt	endifLower
	b	thenLower
thenLower:
	add	r7, r7, #1
endifLower:
	
ifHexUpper:		    @ Checks if char is an uppercase hexadecimal character
	cmp	r0, #'A'
	blt	endifHexUpper
	cmp	r0, #'F'
	bgt	endifHexUpper
	b	thenHexUpper
thenHexUpper:
	add	r9, r9, #1
endifHexUpper:
	
ifHexLower:		    @ Checks if char is a lowercase hexadecimal character
	cmp	r0, #'a'
	blt	endifHexLower
	cmp	r0, #'f'
	bgt	endifHexLower
	b	thenHexLower
thenHexLower:
	add	r9, r9, #1
endifHexLower:
	
ifDecimal:		    @ Checks if char is a decimal character
	cmp	r0, #'0'
	blt	endifDecimal
	cmp	r0, #'9'
	bgt	endifDecimal
	b	thenDecimal
thenDecimal:
	add	r8, r8, #1
	add	r9, r9, #1
endifDecimal:

ifNewline:		    @ Checks if char is a newline
	cmp	r0, #0x0A
	beq	thenNewline
	b	endifNewline
thenNewline:
	add	r5, r5, #1
	add	r6, r6, #1
endifNewline:
	
ifWhitespace:		    @ Checks if char is whitespace
	cmp	r0, #' '
	beq	thenWhitespace
	cmp	r0, #'	'
	beq	thenWhitespace
	b	endifWhitespace
thenWhitespace:
	add	r6, r6, #1
endifWhitespace:

ifArithmetic:		    @ Checks if char is an arithmetic symbol
	cmp	r0, #'+'
	beq	thenArithmetic
	cmp	r0, #'-'
	beq	thenArithmetic
	cmp	r0, #'/'
	beq	thenArithmetic
	cmp	r0, #'*'
	beq	thenArithmetic
	b	endifArithmetic
thenArithmetic:
	add	r10, r10, #1
endifArithmetic:
	
	

	
        b       loop        @ Jump to top of loop

end:    ldr     r0, =fmt0   @ Prints out the character counts
        mov     r1, r4
        bl      printf
	
	ldr	r0, =fmt1
	mov	r1, r5
	bl	printf
	
	ldr	r0, =fmt2
	mov	r1, r6
	bl	printf
	
	ldr	r0, =fmt3
	mov	r1, r7
	bl	printf
	
	ldr	r0, =fmt4
	mov	r1, r8
	bl	printf

	ldr	r0, =fmt5
	mov	r1, r9
	bl	printf
	
	ldr	r0, =fmt6
	mov	r1, r10
	bl	printf
	
        pop     {lr}
        bx      lr

fmt0:   .asciz  "\nCharacters = %d\n"
fmt1:	.asciz	"\nNewline = %d\n"
fmt2:	.asciz	"\nWhitespace = %d\n"
fmt3:	.asciz	"\nLetters = %d\n"
fmt4:	.asciz	"\nDecimal Digits = %d\n"
fmt5:	.asciz	"\nHexadecimal = %d\n"
fmt6:	.asciz	"\nArithmetic = %d\n"
