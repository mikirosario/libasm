extern ___error
global _ft_write

section .text
	_ft_write:
		cmp edx, 0
		jl reterror
		mov	rax, 0x2000004
		syscall
		jc error ; en MacOSX, si syscall tira error pone Carry Flag a 1 :p
		ret
	
	error:
		push rax
		call ___error
		pop rbx
		mov [eax], ebx
	
	reterror:
		mov rax, -1
		ret