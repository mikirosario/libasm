extern ___errno_location
global _ft_write

section .text
	_ft_write:
		mov	rax, 0x4
		int 0x80
		cmp rax, 0
		jl error
		ret
	
	error:
		neg rax
		push rax
		call ___errno_location
		pop rbx
		mov [rax], ebx
		mov rax, -1
		ret