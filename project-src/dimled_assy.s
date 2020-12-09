
	.data
ledState:
	.word 0			;Write static variable ledState to data with a 0
	
	.text
jt:				;Write jump table to text
	.word case0		
	.word case1		
	.word case2		
	.word case3		
	.word case4		
	.word case5		
	.word default		

	
	.local	state
	.balign 2
	.global	dim_rg_led	;Make function callable to other files
dim_rg_led:			;Start of function
	mov.b	&ledState, r12	;Move the address of ledState into r12 r12=ledState
	cmp	#6, r12		;if r12>=0
	jhs	default		;goto default

	add.b	r12,r12		;Index into JT
	mov	jt(r12), r0	;Jump to case indicated by the value in r12 (*2 for offset)
case0:
	mov.b	#0, &red_on
	mov.b	&ledState, r12
	mov.b	#1, r12
	and	#0xff, r12
	mov.b	r12, &ledState
case1:
case2:
case3:
case4:
	jmp	default
case5:
	mov.b	#1, &red_on
	mov.b	#0, &ledState
default:
	mov.b	&ledState, r12
	add.b	#1, r12
	and	#0xff, r12
	mov.b	r12, &ledState
	mov.b	#1, &led_changed
	call	#led_update
	pop 	r0
