global	ft_list_size

section	.text
	ft_list_size:
		zerorax:
			xor	rax, rax
	
		listsize:
			cmp	rdi, 0
			je	return
			inc rax
			mov	rdi, [rdi + 8]
			jmp listsize

		return:
			ret