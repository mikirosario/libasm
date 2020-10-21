global	_ft_del
extern	_free

; The ridiculous subject for ft_list_remove_if;
; in the piscine requires you to pass this
; function a single pointer rather than a double
; so you can't use it to NULL the pointer.
; Shameful. I made this thinking I could pass it
; to ft_list_remove_if but since I can't I'm just
; saving this as I want it for my libft.
; It's just a standard-issue del written in ASM.
; It frees and nulls your pointer. :)

section .text
	_ft_del:
		push	rdi
		mov		rdi, [rdi]
		call	_free
		pop		rdi
		mov		qword [rdi], 0
		ret
