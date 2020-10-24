global	_ft_list_push_front
extern	_ft_create_elem

; rdi->**begin_list
; rsi->void *data
;return(void)

section .text
	_ft_list_push_front:
		push	rdi
		push	rsi
		; mov		rbx, rdi
		; mov		r12, rsi
		xor		rax, rax
		mov		rdi, rsi
		call	_ft_create_elem
		pop		rsi
		pop		rdi
		cmp		rax, 0	; Un poquiño de seguridad, par diez.
		je		return
		cmp		qword [rdi], 0 ; Does *begin_list exist?
		je		assignptr	; If zero flag, then it does not exist
		mov		rcx, [rdi]
		mov		[rax + 8], rcx

	assignptr:
		mov		[rdi], rax

	return:
		; pop		r12
		; pop		rbx
		ret