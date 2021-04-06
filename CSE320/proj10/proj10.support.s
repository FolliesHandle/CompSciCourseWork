/*****************************************************************************
	Project 10
	Dominic Mazza
	proj10.support.s
*****************************************************************************/

	.global	length
	.text
length:				@ Finds the length of a ch array
	push	{r5, r6}
	mov	r5, #0
	mov	r6, #0
	b	loop_len
loop_len:
	ldrb	r5, [r0, r6]
	cmp	r5, #0x0
	beq	end_loop_len
	add	r6, #1
	b	loop_len
end_loop_len:
	mov	r0, r6
	pop	{r5, r6}
	bx	lr
	

	.global	copy
	.text
copy:				@ Copies contents of whats stored at address in r1 into r0
	push	{lr}
	push	{r5, r6, r7}
	mov	r5, #0
	mov	r6, #0
	b	loop_copy
loop_copy:
	ldrb	r5, [r1, r6]
	strb	r5, [r0, r6]
	add	r6, #1
	cmp	r5, #0x0
	bne	loop_copy
	b	end_loop_copy
end_loop_copy:
	pop	{r5, r6}
	bx	lr

	.global	append
	.text
append:				@ Appends char array inputs together
	push	{r5, r6, r7}
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	b	load_append
load_append:
	ldrb	r5, [r0, r6]
	cmp	r5, #0x0
	beq	load_append_secondary
	strb	r5, [r0, r6]
	add	r6, #1
	b	load_append
load_append_secondary:
	ldrb	r5, [r1, r7]
	strb	r5, [r0, r6]
	add	r6, #1
	add	r7, #1
	cmp	r5, #0x0
	bne	load_append_secondary
	b	end_append
end_append:
	pop	{r5, r6, r7}
	bx	lr

	.global	duplicate
	.text
duplicate:			@ Duplicates input
	push	{r4, lr}
	mov	r4, r0
	bl	length
	add	r0, #1
	bl	malloc
	mov	r1, r4
	bl	copy
	pop	{r4, lr}
	bx	lr

	.global	compare
	.text
compare:			@ Compares two char arrays
	push	{r5, r6, r7}
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r2, r1
	mov	r1, r0
	b	loop_compare
loop_compare:
	ldrb	r5, [r1, r7]
	ldrb	r6, [r2, r7]
	add	r7, #1
	sub	r0, r5, r6
	cmp	r0, #0
	bne	end_compare
	cmp	r5, #0x0
	bne	loop_compare
	cmp	r6, #0x0
	beq	end_compare
	b	loop_compare
end_compare:
	pop	{r5, r6, r7}
	bx	lr
