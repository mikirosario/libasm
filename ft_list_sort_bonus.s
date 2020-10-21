global _ft_list_sort

;			void		ft_list_sort(t_list **begin_list, int (*cmp)())
; rdi **begin_list
; rsi ft_strcmp

section .text
	_ft_list_sort:
		nullcheck:
			push	r15					; Por favor Mac, dejame un preservado
			push	r14
			push	r13
			mov		r15, rdi			; r15 = **begin_list
			mov		r14, rsi			; r14 = func pointer
			xor		rax, rax			; rax = 0
			cmp		qword [rdi], 0 		; *begin_list?
			je		return				; If no, return
			mov		rdi, [rdi] 			; rdi = *begin_list
			cmp		qword [rdi + 8], 0	; begin_list->next?
			je		return				; If no, return
			mov		rsi, [rdi + 8]		; rsi = *begin_list->next
			mov		rsi, [rsi]			; rsi = *begin_list->next-data
			mov		r13, rdi			; r13 = *begin_list
			jmp		datacmploop
		
		swap: ; If we're here, rdi == lst and rsi == lst->next
			mov		rcx, [rdi]			; Save lst-data to rcx as temp pointer
			mov		rax, [rsi]			; Pass lst->next->data to rax register
			mov		qword [rdi], rax	; lst->data = lst->next->data
			mov		qword [rsi], rcx	; lst->next->data = lst->data
			mov		r13, [r15]			; r13 = *begin_list

		datacmploop: ; If we're here, r13 == lst. Other pointers are derived from this.
			cmp		qword [r13 + 8], 0	; If *lst->next is NULL, return
			je		return				; If list->next is NULL all datas are ordered
			xor		rax, rax			; Clean rax
			mov		rdi, r13			; rdi = lst
			mov		rsi, [rdi + 8]		; rsi = lst->next == *(rdi + 8)
			mov		rsi, [rsi]			; rsi = lst->next->data == rsi->data == *rsi
			mov		rdi, [rdi]			; rdi = lst->data
			call	r14					; Call function (ft_strcmp)
			mov		rdi, r13			; rdi = lst
			mov		rsi, [rdi + 8]		; rsi = lst->next == *(rdi + 8)
			cmp		eax, 0				; Is result positive? (lst->data > lst->next->data?)
			jg		swap				; If greater, swap datas
			mov		r13, rsi			; Else lst = lst->next
			jmp		datacmploop

		return:
			pop		r13
			pop		r14
			pop		r15
			ret