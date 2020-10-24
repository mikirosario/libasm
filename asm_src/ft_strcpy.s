global _ft_strcpy

section .text
	_ft_strcpy:
		xor	rcx, rcx
		mov	rax, rdi
	
	copy:
		cmp	byte [rsi], 0
		je	return
		mov	cl, byte [rsi]
		mov	byte [rdi], cl
		add	rdi, 1
		add	rsi, 1
		jmp	copy
	
	return:
		mov	byte [rdi], 0
		ret