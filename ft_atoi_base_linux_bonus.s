global ft_atoi_base
extern ft_strchr
extern ft_isspace
extern ft_strlen

section .text
	ft_atoi_base:
		preliminaries:
			xor		rax, rax
			push	r15
			push	r14
			push	r13
			push	r12
			push	rbx
			push	rbp ; stack alignment?
			mov		r15, rsi
			mov		r14, rdi
			xor		rdi, rdi
			xor		r13, r13
			xor		rbx, rbx

		nullcheck:
			cmp		byte [r15], 0
			je		return
			mov		r12, r15
		
		badbasechar:
			mov		dil, byte [r12]
			call	ft_isspace
			cmp		rax, 0
			jne		return
			inc		r12
			cmp		byte [r12], 0
			jne		badbasechar
			mov 	rdi, r15
			mov		rsi, 43
			call	ft_strchr
			cmp		rax, 0
			jne		return
			mov		rdi, r15
			mov		rsi, 45
			call	ft_strchr
			cmp		rax, 0
			jne		return
			xor		rcx, rcx
			mov		r12, r15

		dupbasechar:
			mov		r11, r12
			mov		cl, byte [r12]
			inc		r12
			
		dupbaseloop:
			inc		r11	
			cmp		cl, byte [r11]
			je		return
			cmp		byte [r11], 0
			jne		dupbaseloop
			cmp		byte [r12], 0
			jne		dupbasechar

		base:
			mov		rdi, r15
			call	ft_strlen
			cmp		rax, 2
			jl		return
			mov		r12, rax
			xor		rdi, rdi

		whitespace:
			mov		dl, byte [r14]
			call	ft_isspace
			inc		r14
			cmp		rax, 0
			jne		whitespace
			dec		r14
			mov		rcx, 1
			mov		rdx, -1

		isawthesign:
			xor		rax, rax
			cmp		byte [r14], 43
			cmove	rax, rcx
			cmp		byte [r14], 45
			cmove	rax, rdx
			add		r13, rax
			inc		r14
			cmp		rax, 0
			jne		isawthesign
			dec		r14
			cmp		r13, 0
			cmovl	r13, rdx
			cmovge	r13, rcx

		atoi:
			xor		rsi, rsi
			mov		rdi, r15
			mov		sil, byte [r14]
			call	ft_strchr
			cmp		rax, 0
			je		return
			sub		rax, r15
			mov		rcx, rax
			mov		rax, rbx
			mul		r12
			add		rax, rcx
			mov		rbx, rax
			inc		r14
			jmp		atoi
		
		return:
			mov		rax, rbx
			mul		r13
			pop		rbp
			pop		rbx
			pop		r12
			pop		r13
			pop		r14
			pop		r15
			ret

