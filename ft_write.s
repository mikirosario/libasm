extern ___error
global _ft_write

section .text
	_ft_write:
		mov	rax, 0x2000004
		clc
		syscall
		jc error
		ret
	
	error:
		push rax
		call ___error
		pop rbx
		mov [rax], ebx
		mov rax, -1
		ret