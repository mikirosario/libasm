global _ft_list_sort
extern _ft_strcmp

;			void		ft_list_sort(t_list **begin_list, int (*cmp)())
; rdi **begin_list
; rsi ft_strcmp

section .text
	_ft_list_sort:
		nullcheck:
			push	r12					; Por favor Mac, dejame un preservado
			push	rdi					; Save **begin_list to stack
			xor		rax, rax			; rax = 0
			cmp		qword [rdi], 0 		; *begin_list?
			je		return				; If no, return
			mov		rdi, [rdi] 			; rdi = *begin_list
			cmp		qword [rdi + 8], 0	; begin_list->next?
			je		return				; If no, return
			mov		rsi, [rdi + 8]		; rsi = *begin_list->next
			mov		rsi, [rsi]			; rsi = *begin_list->next-data
			mov		r12, rdi			; Save *begin_list to r12
			mov		rdi, [rdi]			; rdi = *begin_list->data
			mov		r11, rsi			; move pointer to function to r11
			jmp		datacmploop
		
		swap: ; If we're here, rsi == func pointer and *begin_list is at top of stack
			mov		

		datacmploop: ; If we're here, rdi == lst->data and rsi == lst->next->data
			cmp		qword [rcx + 8], 0	; If *begin_list->next is NULL, return
			je		return
			push	rcx					; Push *begin_list back onto stack
			push	r11					; Save pointer to function to stack
			mov		rdi, [rcx]			; rdi = *begin_list->data
			mov		rsi, [rcx + 8]		; rsi = *begin_list->next
			mov		rsi, [rsi]			; rsi = rsi->data (*begin_list->next->data)
			push	rdi					; Save lst->data to stack
			push	rsi					; Save lst->next->data to stack
			call	r11					; Call function (ft_strcmp)
			pop		rsi					; Pop lst->next->data back to rsi
			pop		rdi					; Pop lst->data back to rdi
			pop		r11					; Pop pointer to function back to r11
			cmp		eax, 0				; Is result positive? (*begin_list->data > *begin_list->next->data?)
			jg		swap				; Swap datas
										; Else lst = lst->next
		return:
			pop		rdi					; Pop **begin_list from stack
			pop		r12
			ret