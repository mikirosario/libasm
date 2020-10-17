extern ___error
global _ft_write

section .text
	_ft_write:
		mov		rax, 0x2000004
		clc
		syscall
		jc		error
		ret
	
	error:
		push	rax
		call	___error
		pop		rcx
		mov		[rax], ecx
		mov		rax, -1
		ret