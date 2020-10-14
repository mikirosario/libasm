global _ft_strcmp

section .text
	_ft_strcmp:
	push	rdi
	cmp		[rdi], [rsi]
	jne		return ; JMP no actualiza flags
	cmp		[rdi], 0
	je		returnzero
	add		rdi, 1
	add		rsi, 1
	jmp		_ft_strcmp

	returnzero:
		pop rdi
		mov rax, 0
		ret

	return
		cmovl	rax, -1 ; CREO que cmov no actualiza flags
		cmovge	rax, 1
		pop		rdi
		ret