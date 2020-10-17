extern ___error
extern _ft_strlen
extern _malloc
extern _ft_strcpy
global _ft_strdup

section .text
	_ft_strdup:
		push	rbx
		mov		rbx, rdi
		call	_ft_strlen
		mov		rdi, rax
		add		rdi, 1
		call	_malloc
		cmp		rax, 0
		je		return
		mov		rdi, rax
		mov		rsi, rbx
		call	_ft_strcpy

	return:
		pop		rbx
		ret
