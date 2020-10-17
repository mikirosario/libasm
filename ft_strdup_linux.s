extern ft_strlen
extern malloc
extern ft_strcpy
global ft_strdup

section .text
	ft_strdup:
		push	rbx
		mov		rbx, rdi
		call	ft_strlen
		mov		rdi, rax
		add		rdi, 1
		call	malloc
		cmp		rax, 0
		je		return
		mov		rdi, rax
		mov		rsi, rbx
		call	ft_strcpy

	return:
		pop		rbx
		ret
