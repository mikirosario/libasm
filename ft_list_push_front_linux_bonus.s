global ft_list_push_front
extern	ft_create_elem

; rdi->**begin_list
; rsi->void *data
;return(void)

section .text
	ft_list_push_front:
		push	rbx
		push	r12
		mov		rbx, rdi
		mov		r12, rsi
		xor		rax, rax
		mov		rdi, r12
		call	ft_create_elem
		cmp		rax, 0	; Un poquiño de seguridad, par diez.
		je		return
		cmp		qword [rbx], 0 ; Does *begin_list exist?
		je		return	; If zero flag, then it does not exist
		mov		rcx, [rbx]
		mov		[rax + 8], rcx
		mov		[rbx], rax

	return:
		pop		r12
		pop		rbx
		ret