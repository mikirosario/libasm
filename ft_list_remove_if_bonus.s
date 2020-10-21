global	_ft_list_remove_if

section .text
	_ft_list_remove_if:
		preliminaries:
			xor		rax, rax		; Clear rax
			push	r15				; push preserved registers
			push	r14
			push	r13
			push	r12
			mov		r15, [rdi]		; r15 = *begin_list == lst
			mov		r14, rsi		; r14 = void *data_ref
			mov		r13, rdx		; r13 = strcmp func pointer
			mov		r12, rcx		; r12 = free_fct func pointer

		datarefnullcheck:			; This checks for a null data_ref POINTER, 
									; not a pointer to null, which IS valid and
									; should delete every string not pointing
									; directly to null.
			cmp		r14, 0			; r14 - 0 (null pointer check)
			je		return			; return if data_ref pointer null

		listnullcheck:				; This checks for a null lst pointer
			mov		rcx, r15		; rcx = lst
			cmp		rcx, 0			; if !lst
			je		return
		
		datanullcheck:				; This checks for a null data pointer. We should
									; just skip to the next list member if we find
									; one. Again, do not confuse with data pointer
									; to null, which WILL be checked, and CAN be
									; freed, even if it is just a one-byte string.
			mov		rdi, [r15]		; rdi = lst->data
			cmp		rdi, 0			; null pointer check
			je		getnextmember	; if !lst->data, check next member
		
		cmpdatasets:				; Compare lst->data to data_ref Remember:
									; rdi == lst->data already coming into this.
			mov		rsi, r14		; rsi = data_ref. This isn't redundant, as
									; rsi is a public register and we don't know
									; what the other functions we are calling
									; will do to it. So we do need to refresh
									; it.
			call	r13				; Call ft_strcmp, which is what really
									; should be used here. ;)
			cmp		rax, 0			; If the result is 0, the strings are the
									; same, which means delete it. If not,
									; then get next member.
			jne		getnextmember	; If strings are not the same, save string
									; and get next member. Otherwise...
			mov		rdi, [r15]		; rdi = lst->data. Again not redundant as
									; rdi is a public register.
			call	r12				; Call free, which is what I pass as
									; free_fct, because they only let you
									; pass single pointer in the subject,
									; otherwise I'd use my ft_del.
			mov		qword [r15], 0	; Since I can't use my ft_del I hardcode
									; lst->data = NULL here. :p

		getnextmember:				; lst = lst->next
			mov		r15, [r15 + 8]	; lst = lst->next
			jmp		listnullcheck

		return:
			pop		r12
			pop		r13
			pop		r14
			pop		r15
			ret