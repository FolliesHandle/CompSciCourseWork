/********************************************
	Dominic Mazza
	CSE 320
	Project 11
	proj11.support.s
*********************************************/

.global search
.global delete
.global insert

.data
.balign	4
stu:		.word	0
.text

search:							@ Searches for student by id in table
	push	{r4, r5, r6, r7, r8, r9, r10, lr}
	ldrh	r4, [r0], #2		@ loading table
	ldrh	r5, [r0], #2
	ldrh	r6, [r0], #4
	ldr 	r7, [r0]
	mov 	r8, #0
	mov		r9, #0

loop_search:
	add		r8, r8, #1			@ searching student list
	str		r7, [r2]
	ldrh 	r10, [r7], #44
	cmp		r10, r1
	bgt		not_found
	cmp		r10, r1
	beq		found
	cmp		r8, r5
	bgt		not_found
	b 		loop_search
found:
	mov		r0, #1
	b 		end
not_found:
	mov		r0, #0
	b 		end
end:
	pop 	{r4, r5, r6, r7, r8, r9, r10, lr}
	bx		lr




delete:							@ Deletes from table
	push	{r4, r5, r6, r7, r8, r9, lr}
	mov 	r9, r0
	ldr 	r2, =stu
	
	bl		search
	cmp		r0, #0
	beq		end_delete

	ldr 	r2, [r2]
	ldrh	r5, [r9, #2]
	mov 	r0, #0
	cmp 	r5, #0
	beq 	end_delete

	ldr 	r6, [r9, #8]
	mov 	r7, #44
	mul 	r8, r7, r5
	add		r8, r6
	mov 	r0, r2
loop_delete:					@ loops through and moves each student up 1
	cmp		r0, r8
	bgt		storage
	add		r1, r0, #44
	mov		r2, #44
	bl		memmove
	add 	r0, r0, #44
	b 		loop_delete
storage:
	sub 	r5, r5, #1
	strh	r5, [r9, #2]
	mov 	r0, #1
end_delete:
	pop 	{r4, r5, r6, r7, r8, r9, lr}
	bx		lr


insert: 						@ Inserts in table
	push	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	mov 	r9, r1
	mov 	r11, r2
	mov 	r10, r3
	mov 	r4, r0
	ldr 	r2, =stu
	bl		search
	cmp		r0, #1
	moveq	r0, #0				
	beq		end_insert
								@ branches if id already exists
	ldr 	r2, [r2]
	ldrh 	r7, [r4]
	ldrh 	r8, [r4, #2]
	cmp		r8, r7
	moveq	r0, #0
	beq		end_insert			

	ldr 	r6, [r4, #8]
	mov 	r7, #44
	mul 	r5, r8, r7
	add 	r5, r6, r5
	mov 	r6, r2
	mov 	r1, r5
loop_insert:					@ branches when insertion point is found
	cmp 	r1, r6
	blt		insert_operation
	add 	r0, r1, #44
	mov 	r2, #44
	bl 		memmove
	sub 	r1, r1, #44
	b 		loop_insert
insert_operation:				@ inserts
	str 	r9, [r6]
	add 	r6, #4
	mov 	r0, r6
	mov 	r1, r11
	mov 	r2, #26
	bl 		memmove
	add 	r6, #26
	mov 	r9, #0
	strh 	r10, [r6]
	add 	r9, r10
	add 	r6, #2

	ldr 	r10, [sp, #36] @
	add 	r9, r10
	strh 	r10, [r6]
	add 	r6, #2

	ldr 	r11, [sp, #40] @
	add 	r9, r10
	strh 	r10, [r6]
	add 	r6, #2

	mov 	r10, r9
	strh 	r10, [r6]
	add 	r6, #4

	ldrh 	r9, [r4, #4]

	fmsr 	s0, r10
	fmsr 	s1, r9
	fdivs 	s2, s0, s1
	fsts 	s2, [r6]

	mov 	r0, #1
	add 	r8, #1
	strh 	r8, [r4, #2]
end_insert:
	pop 	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	bx 		lr



