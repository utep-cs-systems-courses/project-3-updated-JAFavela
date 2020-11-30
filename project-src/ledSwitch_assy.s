
.text
	.local	state
	.balign 2
	.global	led_switch

led_switch:
	sub	#2, r1

	mov.b	r12, 1(r1)
	cmp.b	#0, 1(r1)
	jne	ls
	mov.b	#1, &red_on
	jmp	end
ls:	
	mov.b	#0, &red_on
end:
	mov.b	#1, &led_changed
	call	#led_update
	
	ADD	#2, r1
	pop	r0
