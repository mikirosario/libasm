extern ___error
global _ft_read

section .text
	_ft_read:
		mov	rax, 0x2000003
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