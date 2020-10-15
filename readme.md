IMPORTANT! This readme explains the MacOSX versions of these functions that are required for the 42 school project. The Linux versions can be quite different. Assembly is not known for its portability. xD

FT_STRLEN

This strlen is a bit convoluted to understand, but it avoids branching instructions so it should be much more efficient! It uses x86 processor instructions, though, so perhaps not the most portable.
		
		_ft_strlen:

		mov rcx, -1 	; Sets rcx to all 1s / MAX_INT.

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
				;						rdi++;
				; 						rcx--; }

		not rcx 	; Inverts all rcx bits. Reversing all bits of a negative
				; number with 'not' yields its absolute value - 1.
				;
				; Hence: not rcx == abs(rcx) - 1. BUT, since the integer
				; is actually being treated as unsigned, -1 is really
				; just MAX_INT + 1, and so not rcx ends up being
				; MAX_INT - rcx + 1. xD
				;
				; I TOLD you it was convoluted.
				;
				; This is easier to understand if we imagine a two bit
				; unsigned number and a two-character string "ab". ;p
				;
				; 00b == 0
				; 01b == 1
				; 10b == 2
				; 11b == 3
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

		pop rbx			; Let's get the syscall return value back, into rbx
					; this time.

		mov [rax], ebx		; As I understand, errno is a 32 bit int, so I'll
					; pass the errno value as such. Note, even though
					; errno is a 32 bit int, its pointer is still a 64
					; bit pointer, natch. ;)

	reterror:		
		mov rax, -1		; Now we just return -1 to unhelpfully indicate an
					; error to the user. Go look at errno or use perror
					; if you want more info, pitiful user. Mwahahaha. :p

		ret			; Bye!
