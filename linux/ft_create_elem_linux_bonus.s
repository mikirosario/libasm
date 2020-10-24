global ft_create_elem
extern	malloc

;rdi->void *data
;return(t_list *)

section .text
	ft_create_elem:
		push	rbx
		push	rbp ; stack alignment?
		mov		rbx, rdi
		xor		rax, rax
		mov		rdi, 16
		call	malloc
		cmp		rax, 0
		je		return
		mov		qword [rax], rbx	; pass data pointer to list->data
		mov		qword [rax + 8], 0	; pass null to list->next

	return:
		pop		rbp
		pop		rbx
		ret