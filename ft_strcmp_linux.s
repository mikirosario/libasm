global ft_strcmp

section .text
	ft_strcmp:
		mov		cl, byte [rsi]
		cmp		byte [rdi], cl
		jne		return
		cmp		byte [rdi], 0
		je		returnzero
		add		rdi, 1
		add		rsi, 1
		jmp		ft_strcmp

	returnzero:
		mov		rax, 0
		ret

	return:
		mov		al, byte [rdi]
		movzx	rax, al
		movzx	rcx, cl
		sub		eax, ecx
		ret
