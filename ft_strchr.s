extern _ft_strlen
global _ft_strchr

; rdi -> *s
; rsi -> c

section .text
	_ft_strchr:
	xor		rax, rax 		; clear rax
	xor		rcx, rcx		; clear rcx
	push	rdi				; save rdi address s to stack
	push	rsi				; save rsi char c to stack
	call	_ft_strlen		; get strlen of rdi in rax
	pop		rsi				; get back rsi char c in rsi
	pop		rdi				; get back rdi address s in rdi
	mov 	ecx, eax		; move strlen of rdi into ecx. ecx == 0 is scasb exit condition 1.
	mov		eax, esi		; move int c into eax for the scasb exit condition 2 (we'll just be looking at low byte, but it's OK, we're passing ASCII code)
	add		ecx, 1			; increase ecx by 1 to add the NULL
	cld						; clear direction flag
	repne	scasb			; do scasb while ecx-- (strlen--) != 0 and [rdi--] (*s--) != al
	dec 	rdi				; scasb raises rdi after every comparison, even if the comparison is false, so rdi ends up one byte higher than it should be
	cmp		ecx, 0			; if ecx == 0, we left because we checked whole string ...
							; should add 1 to strlen first??? I think so!! Will test... YEP!
	cmovne	rax, rdi		; if we didn't leave because of ecx, we left becauase there was a
							; match with eax (int c), so we found c in *s, so we return
							; the address to that char.
	cmove	eax, ecx		; Otherwise, we return 0, which is what ecx should be.
	ret
