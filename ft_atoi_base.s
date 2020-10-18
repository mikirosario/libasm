global _ft_atoi_base
extern _ft_strchr
extern _ft_isspace
extern _ft_strlen

; ft_atoi_base(char *str, char *base)
; rdi has a pointer to a string containing the number
; rsi has a pointer to a string containing the base

section .text
	_ft_atoi_base

		atoi:
			xor		rax, rax
			push	rsi ; save the pointer to the base (not to be confused with the base pointer xD)
		
		whitespace:
			call	_ft_isspace		; whitespace loop
			add		rdi, 1			; increment pointer
			cmp		rax, 0			; match found (rax not zero)?
			jne		whitespace		; if found, remain in whitespace, otherwise exit
			dec		rdi				; hmm, always exits at one higher than it should... like SCAS ! coincidence???? or something more sinister?
			mov		rcx, 1
			mov		rdx, -1
			xor		r11, r11 		; clear r11

		sign:
			xor		rax, rax		; clear rax
			cmp		byte [rdi], 43 ; check plus sign
			cmove	rax, rcx 		; if plus sign, put a 1 in rax
			cmp		byte [rdi], 45 ; check minus sign
			cmove	rax, rdx		; if minus sign, put a -1 in rax
			add		r11, rax		; add rax to r11. starts at 0 (pos), if a positive sign is found, add 1 to pos counter, if a negative is found, add -1 to pos counter...
			inc		rdi			; increment pointer whether we need it or not :p
			cmp		rax, 0		; if either a minus or plus sign was found, rax will not be zero.
			jne		sign 		; if something was found in rax, repeat sign instruction on next char
			dec		rdi 		; otherwise, decrement rdi pointer, because we didn't need to increment it
		
		atoi:
			cmp		r11, 0		; if r11 is negative, number is negative, else number is positive
			cmovl	r11, rdx	; if negative, r11 is -1
			cmovge	r11, rcx	; if equal to or greater than zero, r11 is 1
			pop		rsi			; Get the pointer to the base back
			push	rdi			; Save the pointer to the number
			mov		rdi, rsi	; pass pointer to the base to _ft_strlen
			push	rsi			; save rsi
			call	_ft_strlen	; strlen will be our base
			pop		rsi			; get rsi back
			pop		rdi			; get the pointer to the number back (pointer to base is still in rsi)
			push	r15			; save r15, as we will use it
			mov		r15, rsi	; put rsi in r15
			push	r14			; save r14, as we will use it
			mov		r14, rdi	; put rdi in r14
			push	r13			; save r13 as we will use it
			mov		r13, rax	; put the base in r13
			xor		rax, rax	; clear rax
			push	r12			; save r12, as we will use it
			mov		r12, rsi	; put pointer to rsi into r12
			push	rbx			; push rbx to stack to save it, as we will use it
			xor		rbx, rbx	; clear rbx, that's our result

		atoiloop:
			mov		rdi, r15	; *s to check against is r15 always
			mov		rsi, byte [r14] ; byte to check is *num [r14]
			call	_ft_strchr	; check *rdi against rsi (base) string for match
			cmp		rax, 0		; if not null, stay in loop
			je		return		; if no match, return
			sub		rdx, rax	; otherwise, subtract pointer returned by strchr from rdx, store in rdx: that's our number
			mov		rax, rbx	; move rbx (result) to rax
			mul		r13			; multiply r13 (base) by result (rax), product stored in rax
			add		rax, rdx	; add rdx (base number)
			mov		rbx, rax	; store result in rbx
			add		r14, 1		; increment r14
		
		return:

