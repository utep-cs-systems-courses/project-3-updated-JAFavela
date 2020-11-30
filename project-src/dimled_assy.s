
	.data
ledState:
	.word 0
	
	.text
jt:
	.word case0
	.word case1
	.word case2
	.word case3
	.word case4
	.word case5
	.word default
	
	.local	state
	.balign 2
	.global	dim_rg_led

	
dim_rg_led:
	move.b	&ledState, r12
	cmp	#6, r12
	jhs	default
	add.b	r12,r12
	jmp	jt(r12)	
case0:
	mov.b	#0, &red_on
	mov.b	&ledState, r12
	mov.b	#1, r12
	and	#0xff, r12
	mov.b	r12, &ledState
	jmp	default
case1:
case2:
case3:
case4:
	jmp	default
case5:
	move.b	#1, &red_on
	mov.b	#0, &ledState
default:
	mov.b	&ledState, r12
	add.b	#1, r12
	and	#0xff, r12
	mov.b	r12, &ledState
	mov.b	#1, &led_changed
	call	#led_update
	pop 	r0
