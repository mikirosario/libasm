global _ft_strlen

section .text
	_ft_strlen:
		mov rcx, -1
		xor al, al
		cld
		repne scasb
		not rcx
		dec rcx
		mov rax, rcx
		ret