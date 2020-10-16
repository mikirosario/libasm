global _ft_strcpy

; char *dst -> rdi
; char *src -> rsi

section .text
	_ft_strcpy:
		xor rcx, rcx ; change to scratch register
		mov rax, rdi ; original ptr s1 in rax
	
	copy:
		cmp byte [rsi], 0
		je return
		mov cl, byte [rsi] ; need to check to make sure this is ok in Calling Convention
		mov byte [rdi], cl
		add rdi, 1
		add rsi, 1
		jmp copy
	
	return:
		mov byte [rdi], 0
		ret