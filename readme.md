IMPORTANT! This readme explains the MacOSX versions of these functions that are required for the 42 school project. The Linux versions can be quite different. Assembly is not known for its portability. xD

FT_STRLEN

This strlen is a bit convoluted to understand, but it avoids branching instructions so it should be much more efficient! It uses x86 processor instructions, though, so perhaps not the most portable.
		
		_ft_strlen:

		mov rcx, -1 	; Sets rcx bits to all 1s / ULONG_MAX.

		xor al, al 	; Sets low byte of rax to 0.

		cld 		; Sets direction flag to 0, so we increment.

		repne scasb 	; scasb raises rdi by 1, repne repeats scasb while the
				; byte pointed to by rdi is not equal to the value we
				; stored in al, which was zero.
				;
				; Importantly, scasb also decrements rcx by 1 every time
				; it executes!
				;
				; So this is like: while(*rdi){
				;			rdi++;
	 			;			rcx--; }

		not rcx 	; Inverts all rcx bits. Reversing all bits of a negative
				; number with 'not' yields its absolute value - 1.
				;
				; Hence: not rcx == abs(rcx) - 1. BUT, since the integer
				; is actually being treated as unsigned, -1 is really
				; just ULONG_MAX, and so not rcx ends up being
				; ULONG_MAX - rcx + 1. xD
				;
				; I TOLD you it was convoluted.
				;
				; This is easier to understand if we imagine a two bit
				; unsigned number and a two-character string "ab". ;p
				;
				; Unsigned		Signed
				; Bin	Dec		Bin   Dec
				; 00 == 0		00 == 0
				; 01 == 1		01 == 1
				; 10 == 2		11 == -1
				; 11 == 3		10 == -2
				;
				; Thus: -1 == 3.
				; Thus: scasb executed twice before NULL was found.
				; Thus: rcx == 1 == 01b.
				; Thus: not rcx == 10b + 01b == 11b == 3.
				; That is 3 with the NULL, but we don't want to count
				; NULL.

		dec rcx 	; Subtract 1, because we don't count the NULL.
				; Thus: rcx - 1 == 2. There are two characters in the
				; string, so that is the right answer.
				;
				; If there had been 3 characters, we'd have subtracted 1
				; from 0, which, of course, equals -1, which as we know
				; in unsigned two bits equals 3, so we'd have gotten 3.
				;
				; The things we'll do to avoid the jmp instruction. ;)

		mov rax, rcx 	; This is our return value. :)

		ret

FT_WRITE

Fairly straightforward syscall, with a couple of caveats. First, we are required to set errno if the syscall fails. MacOSX sets the Carry flag to 1 if syscall fails, rather than returning a negative number like a normal operating system. ;p We indulge the idiosynscrasy. The MacOS function for getting the errno variable address is __error. When called, the desired address is passed to rax.
	
	_ft_write:
		_ft_write:
		mov	rax, 0x2000004	; The code for the write syscall in MacOS.

		clc			; Clear the Carry Flag.

		syscall			; Do it! Apparently, it already knows where to get
					; the parameters per the calling convention. Less
					; for me to worry about!

		jc error		; MacOS will set the Carry Flag if syscall fails.

		ret			; The syscall will put bytes written into rax. How
					; helpful! Now all we need to do is return. :)
					; Unless...
	
	error:
		push rax		; MacOS, following BSD convention, returns
					; the errno on failure (into rax), as indicated by
					; the Carry Flag, so I can just pass it right into
					; the errno variable. (In Linux a negative errno
					; is passed, and needs to be made positive before
					; passing to errno, and the Carry Flag isn't used).
					;
					; First I push rax onto the stack so it is safe from
					; what __error is about to do to my registers...

		call ___error		; rax should now have the pointer to errno.

		pop rcx			; Let's get the syscall return value back, into rcx
					; this time. Used to use rbx, but found out that it's
					; preserved, so now use rcx as it's scratch.

		mov [rax], ecx		; As I understand, errno is a 32 bit int, so I'll
					; pass the errno value as such. Note, even though
					; errno is a 32 bit int, its pointer is still a 64
					; bit pointer, natch. ;)

	reterror:		
		mov rax, -1		; Now we just return -1 to unhelpfully indicate an
					; error to the user. Go look at errno or use perror
					; if you want more info, pitiful user. Mwahahaha. :p

		ret			; Bye!

FT_READ

Practically identical to FT_WRITE, except we use the syscall code 2000003 to
call the read function instead of the write function. These syscall functions
are really just wrappers for, well, the system functions. Not that I'm
complaining! xD

FT_STRCMP

Straightforward implementation. No surprises or fancy tricks here. This is more
or less derived and adapted straight from the C version. ;) We start out with
two pointers per the calling convention, the pointer to src (in rdi), and the
pointer to dst (in rsi). Both pointers are to (presumably) NULL-terminated
character strings of unknown length.

section .text
	_ft_strcmp:
		mov		cl, byte [rsi]	; Move the character pointed to by src (rsi)
							; into the lower byte of the rcx register (cl).
	
		cmp		byte [rdi], cl	; Compare that character with the character
							; pointed to by dst (rdi). this really the same as
							; sub [rdi], cl, except we don't store the result,
							; we just set the flags.

		jne		return			; If the result of cmp is not zero it means they
							; are not equal. (Hence, jne and jnz mean the same
							; thing). Then we jump to return, where we'll find
							; the difference and return it.

		cmp		byte [rdi], 0	; If the result of cmp is equal, we want to make
							; sure we haven't reached the end (NULL) of the dst
							; string before continuing, so we compare the
							; character it points to with 0.

		je		returnzero		; Once again, if the result is zero, it means
							; they're equal, and the zero flag will be set.
							; (Hence je and jz mean the same thing). If that
							; happens, it means dst was equal to src, that is,
							; it was equal up to AND INCLUDING the NULL value.
							; So we jump to returnzero to tell the user.

		add		rdi, 1			; If we have nothing to return yet, we raise the
							; the pointer address. We're addressing a string of
							; bytes, so we raise it by one. This is just like
							; dst++.
	
		add		rsi, 1			; We raise the second pointer address too, so
							; this is like src++.

		jmp		_ft_strcmp		; And we go back to the first instruction to
							; start again.

	returnzero:
		mov		rax, 0			; If we need to return zero, well, we move zero
							; into rax...

		ret						; And we return it. ;)

	return:
		mov		al, byte [rdi]	; If we need to return a non-zero result, it
							; will be *dst - *src. First we copy the character
							; pointer to by rdi to the lower byte of rax (al).
							; Note this will do nothing to the higher bytes,
							; which might still hold junk...

		movzx	rax, al			; ...But not after this command. ;) Here we
							; instruct the CPU to clear the rest of the register
							; and store only the value we put into the lower
							; byte. Handy, right? ;)

		movzx	rcx, cl			; Remember, we already stored the character
							; pointed to by src (rsi) in the lower byte of rcx
							; within the loop. Since it is already there, we
							; just need to clear the rest of that register, too.

		sub		eax, ecx		; Now that we know we have the values we want in
							; the registers, we subtract src from dst, storing
							; the result in dst. Note that while we are
							; subtracting two bytes, the function actually
							; returns an int (four bytes). So we do 32 bit
							; subtraction and return the lower 32 bits of the
							; register (eax). Probably not strictly necessary,
							; but it feels cleaner to me this way. Plus, reminds
							; me of the real size of the return value.

		ret						; That's all, folks!