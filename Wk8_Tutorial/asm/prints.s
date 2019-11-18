@=================================
@ Function for printing stuff from C/C++
@ EWRAM_CODE void nocash_message();
@ extern EWEAM_DATA char nocash_buffer[80];

.global nocash_message
.global nocash_buffer

;.section .ewram, "ax", %progbits
.thumb_func
.align 2;
.global nocash_message
.type nocash_message STT_FUNC

nocash_message:
	mov 	r12, r12		@first ID
	b		.Lmsg_end		@skip the text section
	.hword	0x6464			@second ID
	.hword 	0				@flags
nocash_buffer:
	.space 82				@message buffer

.Lmsg_end:
	bx		lr
.size nocash_message, .-nocash_message

@=================================