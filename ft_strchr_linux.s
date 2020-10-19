extern ft_strlen
global ft_strchr

section .text
	ft_strchr:
	xor		rax, rax
	xor		rcx, rcx
	push	rdi
	push	rsi
	call	ft_strlen
	pop		rsi
	pop		rdi
	mov 	ecx, eax
	mov		eax, esi
	add		ecx, 1
	cld
	repne	scasb
	dec 	rdi
	cmp		ecx, 0
	cmovne	rax, rdi
	cmove	eax, ecx
	ret
