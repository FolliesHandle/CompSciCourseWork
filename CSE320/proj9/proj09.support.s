/************************************************************************
	Project 9
	Dominic Mazza
	proj09.support.s
************************************************************************/

	.global negate
	
	.text
	.balign	4
negate:	push	{lr}
	
	neg	r0, r0
	bvs	negateError
	b	negateEnd
negateError:
	mov	r0, #0x80000000
negateEnd:
	pop	{lr}
	bx	lr

	
	.global absolute
	.text
	.balign	4
absolute:
	push	{lr}
	
	cmp	r0, #0
	blt	absoluteThen
	b	absoluteEnd
absoluteThen:
	neg	r0, r0
	bvs	absoluteError
	b	absoluteEnd
absoluteError:
	mov	r0, #0x80000000
absoluteEnd:
	pop	{lr}
	bx	lr


	.global add
	.text
	.balign 4
add:	push	{lr}
	
	add	r0, r0, r1
	bvs	errorAdd
	b	endAdd
errorAdd:
	mov	r0, #0x80000000
endAdd:	
	pop	{lr}
	bx	lr



	.global sub
	.text
	.balign	4
sub:	push	{lr}
	sub	r0, r0, r1
	bvs	subError
	b	subEnd
subError:
	mov	r0, #0x80000000
subEnd:
	pop	{lr}
	bx	lr



	.global mul
	.text
	.balign	4
mul:	push	{lr}
	smulls	r0, r7, r0, r1
	bvs	mulError
	b	mulEnd
mulError:
	mov	r0, #0x80000000
mulEnd:
	pop	{lr}
	bx	lr



	.global divide
	.text
	.balign	4
divide:
	push	{lr}
	cmp	r1, #0
	beq	divideError
	sdiv	r0, r0, r1
	bvs	divideError
	b	divideEnd
divideError:
	mov	r0, #0x80000000
divideEnd:
	pop	{lr}
	bx	lr



	.global power
	.text
	.balign	4
power:
	push	{lr}
	mov	r4, #1
	mov	r5, r0
	cmp	r1, #1
	blt	powerError
	b	loop
loop:
	cmp	r4, r1
	beq	endLoop
	smulls	r0, r7, r0, r5
	bvs	powerError
	add	r4, r4, #1
	b	loop
powerError:
	cmp	r1, #0
	beq	zero
	mov	r0, #0x80000000
	b	endLoop
zero:
	mov	r0, #1
endLoop:
	pop	{lr}
	bx	lr



	.global factorial
	.text
	.balign	4
factorial:
	push	{lr}
	cmp	r0, #0
	blt	factorialError
	cmp	r0, #0
	beq	zeroFac
	mov	r4, #1
	mov	r5, r0
	b	loop2
loop2:
	cmp	r5, r4
	ble	endLoop2
	sub	r6, r5, r4
	bvs	factorialError
	smulls	r0, r7, r0, r6
	bvs	factorialError
	add	r4, r4, #1
	b	loop2
zeroFac:
	mov	r0, #1
	b	endLoop2
factorialError:
	mov	r0, #0x80000000
endLoop2:
	pop	{lr}
	bx	lr 
