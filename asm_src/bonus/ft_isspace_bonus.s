global _ft_isspace

section .text
	_ft_isspace:
		mov 	rax, 0
		mov		rcx, 1
		cmp		rdi, 9
		cmove	rax, rcx
		cmp		rdi, 10
		cmove	rax, rcx
		cmp		rdi, 11
		cmove	rax, rcx
		cmp		rdi, 12
		cmove	rax, rcx
		cmp		rdi, 13
		cmove	rax, rcx
		cmp		rdi, 32
		cmove	rax, rcx
		ret
