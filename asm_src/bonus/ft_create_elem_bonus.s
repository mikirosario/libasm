global	_ft_create_elem
extern	_malloc

;rdi->void *data
;return(t_list *)

section .text
	_ft_create_elem:
		push	rdi
		xor		rax, rax
		mov		rdi, 16
		call	_malloc
		pop		rdi
		cmp		rax, 0
		je		return
		mov		qword [rax], rdi	; pass data pointer to list->data
		mov		qword [rax + 8], 0	; pass null to list->next

	return:
		ret