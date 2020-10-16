extern ___error
extern _ft_strlen
extern _malloc
extern _ft_strcpy
global _ft_strdup

; rdi holds char pointer to src string

section .text
	_ft_strdup:
		push rbx				; I'll be using this preserved register
		mov	rbx, rdi			; Save poor, defenceless src pointer from ravages of getting
								; clobbered. As far as I know this is a copy so it should
								; also still be in the rdi register...
		call _ft_strlen			; There we go, now we should have the strlen in rax...	
		mov rdi, rax			; I'm about to call malloc and we'll need to pass it
								; basically just strlen + 1 (for NULL) as our
								; size, because strdup just copies char strings. :)
		add rdi, 1				; So let's add that 1...
		call _malloc			; And... malloc! If I'd have told myself in the
								; piscine exam, sweating over the dreaded malloc
								; exercise, that in a year I'd be calling
								; malloc from Assembly... xD Anyway, now we
								; will have a pointer in rax. Good guy, malloc.	
								; Thanks, malloc. :)
		cmp rax, 0				; BUT, is that pointer NULL? We can't very well
								; do much with a null pointer, can we?
		je nullreturn			; If it's null, get out of town.
		mov rdi, rax			; If it's not null, we'll be passing it to
								; strcpy as dst
		mov rsi, rbx			; And we'll be passing the original src pointer to _ft_strcpy
								; as src
		call _ft_strcpy			; Go forth, and multiply! This should leave a pointer to dst
								; in rax. Convenient!

	return:
		pop rbx					; Get the REAL rbx back.
		ret						; Return the pointer to the copy - don't forget to free it
								; you naughty runtime caller!
	nullreturn:
		call ___error			; Don't care about rax, we're just going to return 0 anyway
		mov [rax], dword 12		; ENOMEM error
		mov rax, 0				; Set rax back to null
		pop rbx					; Get the REAL rbx back.
		ret						; Return the null