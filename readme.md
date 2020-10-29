IMPORTANT! This readme explains the MacOSX versions of these functions that are required for the 42 school project. The Linux versions can be different. Assembly is not known for its portability. xD

FT_STRLEN

This strlen is a bit convoluted to understand, but it avoids branching instructions so it should be much more efficient! It uses x86 processor instructions, though, so perhaps not the most portable.
		
		_ft_strlen:

		mov rcx, -1 	; Sets rcx bits to all 1s / ULONG_MAX.

		xor al, al 	; Sets low byte of rax to 0.

		cld 		; Sets direction flag to 0, so we increment.

		repne scasb 	; scasb raises rdi by 1 y decrements rcx by 1, and repne
				; repeats scasb while the byte pointed to by rdi is not
				; equal to the value we stored in al, which was zero.
				;
				; Remember, scasb decrements rcx by 1 every time it
				; executes! And it will also execute when it finds the
				; zero.
				;
				; So this is just like: do {
				;			    rdi++;
	 			;			    rcx--; } while(*rdi)

		not rcx 	; Inverts all rcx bits. Reversing all bits of a negative
				; number with 'not' yields its absolute value - 1.
				;
				; Hence: not rcx == abs(rcx) - 1. So if we went through
				; the loop three times: rcx == -1 - 3 == -4. Then:
				; not rcx == 3! Since that includes the null, 3 - 1 is
				; our string length.
				;
				; I TOLD you it was convoluted. xD
				;
				; This is easier to understand if we imagine a two bit
				; number and a two-character string "ab". ;p
				;
				; Let's imagine that we have two bit unsigned, two
				; bit signed, and two bit negatives - where we treat
				; every possible two bit value as a negative (That is
				; basically what we're doing here).
				;
				; Unsigned		Signed		Negatives
				; Bin	Dec		Bin   Dec	Bin   Dec
				; 00 == 0		00 == 0		00 == -4
				; 01 == 1		01 == 1		01 == -3
				; 10 == 2		10 == -2	10 == -2
				; 11 == 3		11 == -1	11 == -1
				;
				; Thus: -1 (signed) == 3 (unsigned), that is, MAX_2BIT.
				; Thus: scasb executed 3 times, for 'a', 'b' and NULL.
				; Thus: rcx == -1 - 3.
				; Thus: rcx == -4 == 00 in our 'negatives' universe.
				; Thus: not rcx == 11 (binary) == 3 in our unsigned
				; universe. See that? 4 - 1, so the absolute value
				; of -4 less one.
				;
				; So there you go. This logic scales. Try it. ;)
				;
				; This gives us the number of times scasb executed.
				;
				; That is 3 with the NULL, but we don't want to count
				; NULL for strlen.

		dec rcx 	; Subtract 1, because we don't count the NULL.
				; Thus: rcx - 1 == 2. There are two characters in the
				; example string "ab", so that is the right answer. :)
				;
				; The things we'll do to avoid the jmp instruction! ;)

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

	_ft_strcmp:
		mov		cl, byte [rsi]	; Move the character pointed to by src (rsi)
						; into the lower byte of the rcx register (cl).
	
		cmp		byte [rdi], cl	; Compare that character with the character
						; pointed to by dst (rdi). This really the same as
						; sub [rdi], cl, except we don't store the result,
						; we just set the flags.

		jne		return		; If the result of cmp is not zero it means they
						; are not equal. (Hence, jne and jnz mean the same
						; thing). Then we jump to return, where we'll find
						; the difference and return it.

		cmp		byte [rdi], 0	; If the result of cmp is equal, we want to make
						; sure we haven't reached the end (NULL) of the dst
						; string before continuing, so we compare the
						; character it points to with 0.

		je		returnzero	; Once again, if the result is zero, it means
						; they're equal, and the zero flag will be set.
						; (Hence je and jz mean the same thing). If that
						; happens, it means dst was equal to src, that is,
						; it was equal up to AND INCLUDING the NULL value.
						; So we jump to returnzero to tell the user.

		add		rdi, 1		; If we have nothing to return yet, we raise the
						; the pointer address. We're addressing a string of
						; bytes, so we raise it by one. This is just like
						; dst++.
	
		add		rsi, 1		; We raise the second pointer address too, so
						; this is like src++.

		jmp		_ft_strcmp	; And we go back to the first instruction to
						; start again.

	returnzero:
		mov		rax, 0		; If we need to return zero, well, we move zero
						; into rax...

		ret				; And we return it. ;)

	return:
		mov		al, byte [rdi]	; If we need to return a non-zero result, it
						; will be *dst - *src. First we copy the character
						; pointed to by rdi to the lower byte of rax (al).
						; Note this will do nothing to the higher bytes,
						; which might still hold junk...

		movzx		rax, al		; ...But not after this command. ;) Here we
						; instruct the CPU to clear the rest of the register
						; and store only the value we put into the lower
						; byte. Handy, right? ;)

		movzx		rcx, cl		; Remember, we already stored the character
						; pointed to by src (rsi) in the lower byte of rcx
						; within the loop. Since it is already there, we
						; just need to clear the rest of that register, too.

		sub		eax, ecx	; Now that we know we have the values we want in
						; the registers, we subtract src from dst, storing
						; the result in dst. Note that while we are
						; subtracting two bytes, the function actually
						; returns an int (four bytes). So we do 32 bit
						; subtraction and return the lower 32 bits of the
						; register (eax). Probably not strictly necessary,
						; but it feels cleaner to me this way. Plus, reminds
						; me of the real size of the return value.

		ret				; That's all, folks!

FT_STRCPY

We receive a pointer to dst in rdi and a pointer to src in rsi, per the Calling
Convention. First I clear rcx by xoring it with itself. Then I move the pointer
to dst into rax, as this is what we will return. Then we go into the copy loop,
which checks the character at *src and jumps to the return code if it's a NULL
character (0), otherwise we copy what is in *src to *dst and increment both
pointers by 1 (as we are running through a string of bytes).

	_ft_strcpy:
		xor	rcx, rcx		; Xoring rcx with itself sets the register to 0.

		mov	rax, rdi		; We move the address in rdi into rax, since we
						; want to return it.
	
	copy:
		cmp	byte [rsi], 0		; Compare the char pointed to by rsi (src)
						; with 0.

		je	return			; If it is equal to zero, jump to return.
						; Otherwise, continue...

		mov	cl, byte [rsi]		; You can't directly move values from one area
						; of memory to another. They must go through the CPU
						; register first. Makes sense if you think about it.
						; So we'll copy the character pointed to by the
						; address in rsi (src) into the low byte of rcx
						; (cl).
	
		mov	byte [rdi], cl		; Then we'll go ahead and copy that byte from cl
						; into the memory pointed to by the address at rdi
						; (dst). This is like *dst = *src in C.

		add	rdi, 1			; Now we increment the rdi pointer by 1, so it
						; points to the next position in the dst string.

		add	rsi, 1			; We increment the rsi pointer by 1, so it
						; points to the next character in the src string.

		jmp	copy			; Finally, we jump back to the cmp byte
						; instruction.
	
	return:
		mov	byte [rdi], 0		; If we're here, then we reached the end (null)
						; of the src string, but we do still need to copy
						; the null to null-terminate the dst string. So we
						; do that with this instruction. Remember, rdi is
						; pointing now to the position in dst after the last
						; position that was copied to in the copy loop.

		ret				; And then we just return. Remember, we put the
						; original dst address into rax at the beginning. So
						; it's still there, pointing to the first byte of
						; dst string, waiting to be reunited with the caller
						; someday. :) <3

FT_STRDUP

We receive a pointer to source in rdi per the Calling Convention, measure its
length with ft_strlen, add 1 for the NULL, call malloc to reserve that amount of
memory, use ft_strcpy to copy the string pointed to by rdi into the memory we
just reserved with malloc. If malloc fails, it sets errno (thanks gbudau for the
heads up!) so we can just return the NULL pointer malloc returns and errno will
be set.

	_ft_strdup:
		push 	rbx			; In the Calling Convention this register is
						; preserved, and I'll be using it, so first I save
						; it on the stack.

		mov	rbx, rdi		; Save poor, defenceless src pointer from
						; ravages of getting clobbered by passing it to the
						; preserved register. This is just copy, so it will
						; still be in the rdi register, which as we know is
						; the first register we assume that an argument is
						; passed into per our Calling Convention...

		call 	_ft_strlen		; There we go, now we should have the strlen in
						; rax...

		mov 	rdi, rax		; I'm about to call malloc and we'll need to
						; pass it basically just strlen + 1 (for NULL) as
						; our size, because strdup just copies char strings.
						; We'll move it to rdi, of course, because that's
						; where malloc will look for its argument per the
						; Calling Convention.

		add 	rdi, 1			; So now let's add that 1...

		call 	_malloc			; And... malloc! If I'd have told myself in the
						; piscine final exam, sweating over the dreaded
						; malloc exercise, that in a year I'd be calling
						; malloc from Assembly... xD Anyway, now we should
						; have a pointer to the malloc'ed memory in rax.
						; Good guy, malloc.	Thanks, malloc. :)

		cmp	rax, 0			; BUT, is that pointer NULL? We can't very well
						; do much with a null pointer, can we?

		je	return			; If it's null, get out of town.

		mov	rdi, rax		; If it's not null, we'll be passing it to
						; strcpy as the dst string. So we move it to
						; rdi.

		mov	rsi, rbx		; And we'll be passing the original src pointer
						; to _ft_strcpy as the src string. Remember we saved
						; that in the preserved register rbx. Now we'll pass
						; it to rsi, the register assumed to contain the
						; second argument, per the Calling Convention.

		call	_ft_strcpy		; Go forth, and multiply! This should leave a
						; pointer to dst in rax. Convenient!

	return:
		pop	rbx			; Get the REAL rbx back from the stack before
						; returning.

		ret				; Return the pointer to the copy - don't forget
						; to free it you naughty runtime caller!

FT_ISSPACE

I needed this for my ft_atoi_base, so I threw it together. It returns 1 if a
whitespace is found, as isspace is wont to do. We receive the ASCII code to
check in rdi, hereinafter the "char". ;p

	_ft_isspace:
		mov	rax, 0			; Set rax to 0, as it will remain unless we find
						; a whitespace.

		mov	rcx, 1			; For whatever reason, cmov does not work with
						; immediates, so we use rcx to store the 1 we will
						; return if we do find a whitespace.

		cmp	rdi, 9			; Compare the char with 9, ASCII for \t.

		cmove	rax, rcx		; If equal, set rax to rcx (1).

		cmp 	rdi, 10			; Compare the char with 10, ASCII for \n.

		cmove	rax, rcx		; If equal, set rax to rcx (1).

		cmp	rdi, 11			; Compare the char with 11, ASCII for \v.

		cmove	rax, rcx		; If equal, set rax to rcx (1).

		cmp 	rdi, 12			; Compare the char with 12, ASCII for \f.

		cmove 	rax, rcx		; If equal, set rax to rcx (1).

		cmp 	rdi, 13			; Compare the char with 13, ASCII for \r.

		cmove 	rax, rcx		; If equal, set rax to rcx (1).

		cmp 	rdi, 32			; Compare the char with 32, ASCII for ' ' (space).

		cmove 	rax, rcx		; If equal, set rax to rcx (1).

		ret				; Return.

FT_STRCHR

I also needed this for my ft_atoi_base. It behaves as a normal strchr does. It
takes a string and a character (passed as an int) as arguments. It returns a
pointer to the first instance of the character in the string, or a null pointer
if the character is not found anywhere in the string. I insisted on doing it
with scasb, so it took me longer to get it working. But... no branching! Wooo!
My second branch-free function. xD

	_ft_strchr:
	xor		rax, rax 		; Clear rax.

	xor		rcx, rcx		; Clear rcx.

	push		rdi			; Save rdi address *s to stack.

	push		rsi			; Save rsi int c to stack.

	call		_ft_strlen		; Get strlen of *s in rax.

	pop		rsi			; Get rsi int c back from stack in rsi.

	pop		rdi			; Get rdi address *s back from stack in rdi.

	mov 		ecx, eax		; Copy strlen of rdi into ecx. Ecx == 0 is scasb
						; exit condition 1.

	mov		eax, esi		; Copy int c into eax for scasb exit condition 2
						; (We'll just be looking at the low byte, but it's
						; OK, even though it's an int, we're passing ASCII
						; code).

	add		ecx, 2			; Increase ecx by 1 to add the NULL, and another to
						; add 1 more to counter so the counter will be at
						; 0 after the NULL char is checked. :)

	cld					; Clear direction flag so we increment strings.

	repne		scasb			; Repeat scasb to scan the string. While ecx--
						; (strlen--) != 0 and [rdi--] (*s--) != eax/al.

	dec 		rdi			; Scasb raises rdi after every comparison, even if
						; the comparison is false, so rdi ends up one byte
						; higher than it should be.

	cmp		ecx, 0			; If ecx == 0, we left because we checked the whole
						; string...

	cmovne		rax, rdi		; If we didn't leave because of ecx, we left because
						; there was a match with eax (int c), so we found
						; int c in *s, so we return the address to that
						; char in the string, which will be rdi.

	cmove		eax, ecx		; Otherwise, we return 0, which is what ecx should
						; be. Convenient, since we can't cmov immediates. ;)
						; Note that a 32 bit mov zeros the top bytes of a
						; register. Or at least that's what Creel told me.

	ret					; Strchr Returns.


FT_ATOI_BASE

ATOI, and not just any ATOI, the ATOI_BASE from the piscine. You remember,
right? The ridiculous one where you had to count all the minus signs and the
plus signs to decide whether a number is positive or not? THAT ATOI. xD Now
brought to you in Assembly Language! Get comfy, this is going to be a long one.

	_ft_atoi_base:
		preliminaries:				; We'll do preparatory stuff here, like
							; saving all our preserved registers on the
							; stack, because I use all of them.

			xor		rax, rax	; Let's clear rax.

			push		r15		; Save r15. We will use it to store the
							; pointer to base (*base).

			push		r14		; Save r14. We will use it to store the
							; pointer to str (*str).

			push		r13		; Save r13. We will use it to store the
							; sign.

			push		r12		; Save r12. We will use it first as a temp
							; pointer, and ultimately to store the base.
							; Not the pointer to the base, the numerical
							; base, as in base 10, base 2, base 16, etc.

			push		rbx		; Save rbx, as we will use it to store the
							; result. ME USE ALL THE PRESERVED REGISTER
							; MWAHAHAHA. Sorry about that, it's very
							; late...

			mov		r15, rsi	; We receive the pointer to the base *base
							; as the second argument, so in rsi. Now
							; that we preserved the registers that fall
							; under our responsibility in the Calling
							; Convention, we will save it to r15.

			mov		r14, rdi	; We receive the pointer to the numerical
							; string *str as the first argument, so in
							; rdi. We will save it to r14.

			xor		rdi, rdi	; With that done, clear rdi.

			xor		r13, r13 	; Clear r13, as we'll need it nice and
							; zeroed.

			xor		rbx, rbx	; Let's set rbx (our result) to zero too.

	; So! The piscine ft_atoi_base subject specifies we need to return 0 in case
	; of an error with the base, such as repeated symbols, use of '+' or '-', or
	; a base of size 1. BOOORING. Note that even though we're to protect ATOI
	; against bad bases... the original ATOI is not actually protected against
	; NULL strings! So I'm guessing FT_ATOI shouldn't be either? What's THAT
	; about anyway? If people deserve a segfault for a null string, why don't
	; they deserve a crazy number for a weird base? :p WHATEVER. Piscine logic.
	; And we ARE talking about a number function that returns 0 for an error.
	; Eh. ANYWAY...

		nullcheck:				; We need to make sure our base doesn't
							; point to a null character. Simple enough.

			cmp		byte [r15], 0	; SO, if r15, our pointer to the base,
							; points to a null... well...

			je		return		; That's all she wrote. Fortunately for
							; us, 0*0 is zero, so when we multiply
							; rbx*r13 for the return value, we are
							; definitely getting a big, fat ZERO, just
							; as the subject demands. ;) Now you see
							; why I insisted on zeroing them right away.

			mov		r12, r15	; Now let's copy the pointer to the *base to
							; r12 for now. It will be a tmp pointer to
							; the base. You'll see why. It is not going
							; to be pretty... You've been warned. xD
		
		badbasechar:				; We need to check the base string for bad
							; chars, like '+', '-' or spaces.

			mov		dil, byte [r12]	; Move the character pointed to by the temp
							; pointer to *base into the lower byte of
							; rdi, to pass it to isspace.

			call		_ft_isspace	; Now for the result...

			cmp		rax, 0		; If it's non-zero, it's a space.

			jne		return		; NO SPACE!!!! SPACE IS A LIE!!!! NASA MEANS
							; RETURN IN HEBREW!! Oops, sorry about that.
							; I don't know what has gotten into me.

			inc		r12		; Increment r12 tmp *base pointer.

			cmp		byte [r12], 0	; Compare the char it points to with 0.

			jne		badbasechar	; If we haven't reached the null termination
							; yet, keep making sure it's not... SPACE.

			mov	 	rdi, r15	; We're only just getting started. EVEN if
							; it's TRUE you don't have spaces... what if
							; you have... a '+' sign or a '-' sign!? o_o
							; Forsooth! Pass the pointer to the *base
							; into rdi pls...

			mov		rsi, 43		; ...and 43, ASCII for '+', into rsi...

			call		_ft_strchr	; Who you gonna call? Sign busters!

			cmp		rax, 0		; If we don't have a zero in rax...

			jne		return		; ...we found a plus! Terminate! Terminate!

			mov		rdi, r15	; Now for the minus...

			mov		rsi, 45		; That's ASCII for '-'...

			call		_ft_strchr	; Bill Murray was funnier in the sequel.

			cmp		rax, 0		; Better be a zero here too...

			jne		return		; ...or else!

			xor		rcx, rcx	; Whew! Let's clear rcx...

			mov		r12, r15	; r12, my old friend, I have need of your
							; services once again... Bearer of the
							; temporary pointer to the *base!

		dupbasechar:				; And now for the best part... we need to
							; make sure there are no DUPLICATE chars in
							; in the base. What kind of villainous
							; pervert would even THINK to put duplicate
							; characters in their base!? Why, it goes
							; against the very essence of what any base
							; should naturally aspire to be! That's even
							; worse than using a minus sign. Whatever
							; will we do? Will no one save us?

			mov		r11, r12	; We need a SECOND temporary pointer for a
							; plot THIS fiendish and dastardly...

			mov		cl, byte [r12]	; We copy the byte pointed to by the first
							; temp pointer to *base to low byte of rcx.

			inc		r12		; Increment the temporary pointer.
			

		dupbaseloop:
			inc		r11		; Increment the second temporary pointer,
							; as we aren't interested in the first
							; ocurrence, only subsequent ocurrences.
							; So in the first instance of the loop, r11
							; will point to the first char after the one
							; we're checking (in cl), in the second
							; instance it will point to the second char
							; after the one in cl, and so on...

			cmp		cl, byte [r11]	; And we cmp that ****! That just means we
							; subtract one from the other without saving
							; the result, but setting the flags. My
							; teacher taught me that any value
							; subtracted from itself SHOULD return 0.
							; ISN'T THAT RIGHT TEACHER? So if we find
							; the same value elsewhere in the string,
							; and we subtract it from itself, we'll get
							; a ZERO, won't we? WON'T WE MADAFAKA? Damn
							; right we will.
							; 
							; Pardon me, I don't know what has come over
							; me. I seem to have gotten a case of the
							; vapours...

			je		return		; Zero flag means when comparing the byte in
							; cl against the byte pointed to by r11, the
							; second temporary *base pointer, they were
							; equal. So we leave! Otherwise, we continue
							; checking cl against the rest of the string
							; until we hit the null termination.

			cmp		byte [r11], 0	; If the second temporary pointer isn't
							; pointing to null yet, we still have
							; characters left to check AGAINST.

			jne		dupbaseloop	; So we go back to the first instruction of
							; the r11 loop (the loop that increments the
							; second temporary pointer) if r11 is not
							; is not pointing to null yet. If it is
							; pointing to null, we continue downward...

			cmp		byte [r12], 0	; If the first temporary pointer, r12, isn't
							; pointing to null yet, we have characters
							; left to check. If it is, it means both
							; pointers are now at the null termination,
							; so we've checked the whole string.

			jne		dupbasechar	; If r11 reached the NULL and r12 has not,
							; we need to get the next char - the one
							; r12 is now pointing to, to check that one
							; for duplicates also by cmping it with
							; every subsequent char. If both r11 and r12
							; reached the NULL, then we made it to the
							; end, and there are no duplicates in the
							; base. So we can continue... finally...
							; I shed a single tear...

		base:
			mov		rdi, r15	; We need to know the base (as in, is it
							; base 10, base 2, base 16, or what?). To
							; see if it's valid (greater than 1), for
							; one thing. But we also need to know it
							; anyway to calculate the number. So, if not
							; now, I ask you, WHEN? Now is the time,
							; surely. Our base will be none other than
							; strlen of *base! So we first pass the
							; pointer to *base to rdi, so _ft_strlen
							; can find it.
							;
							; Remember, we saved the pointer to the base
							; in r15. How fortunate. ^_^

			call		_ft_strlen	; Our base will now be in rax. Joy!

			cmp		rax, 2		; But if it's less than 2, it's UNWORTHY!

			jl		return		; And we CAST IT INTO EXILE! SHAME! SHAME!

			mov		r12, rax	; If it IS worthy, though, we will certainly
							; not want to leave it in rax, as rax is an
							; absolute bedlam of a register. o_o Let's
							; save it to nice, loyal r12, instead. ^_^

			xor		rdi, rdi	; Let's clean up rdi.
			xor		rax, rax

		whitespace:				; We need to skip any whitespace at the
							; beginning of the number string. Remember
							; the number string? The string whose value
							; we mean to calculate? The one we saved
							; to r14 many aeons/CPU cycles ago? Oh never
							; mind. Anyway, there is a number there,
							; you know! It's why we're even here in the
							; first place.

			mov		dil, byte [r14]	; move the byte pointed to by *str into the
							; low byte of rdi. We cleared the rest of it
							; just above this block.
							; Second bug was caused by me confusing the low byte
							; of rdx (dl) with the low byte of rdi (dil). ;)

			call		_ft_isspace	; We can call ft_isspace to see if the byte
							; in dil is a whitespace

			inc		r14		; Increment the numerical *str pointer. This
							; sets the zero flag, so needs to be done
							; before the cmp.

			cmp		rax, 0		; Ft_isspace returns 1 if the byte in dl is
							; a whitespace, otherwise it returns zero.

			jne		whitespace	; If a whitespace is found, loop back to the
							; first whitespace instruction and check
							; next byte in the string.

			dec		r14		; If a whitespace is not found, exit the
							; loop. We always exit with the address
							; higher than it should be... so we do need
							; to decrement it. Coincidence? Or something
							; more sinister? Anyway, now r14 will now
							; point to the first non-whitespace char in
							; the numerical *str. Hooray!

			mov		rcx, 1		; My favourite scratch register! We'll move
							; 1 into it for a cmov we're going to do.
							; Because cmov doesn't get along with
							; immediates.

			mov		rdx, -1		; We'll move -1 into rdx.

		isawthesign:				; I'm still not ready! No me estreeeeses
							; hermano. Me 'tas estresaaaaando. Now for
							; the sign. These are piscine rules so we
							; actually need to count the + signs and the
							; - signs and compare how many of each there
							; are to decide whether the number is
							; positive or negative. xD.

			xor		rax, rax	; First, clear rax.

			cmp		byte [r14], 43	; Check for plus sign in *str.

			cmove		rax, rcx	; If plus sign, put a 1 in rax.

			cmp		byte [r14], 45	; Check for minus sign in *str.

			cmove		rax, rdx	; If minus sign, put a -1 in rax.

			add		r13, rax	; Add rax to r13. You'll remember that we
							; initialized r13 to 0, and it's a preserved
							; register, so it's still 0, because I
							; didn't call YOUR functions. I don't trust
							; you to follow the Calling Convention. ;)
							; So, if a positive sign is found, we add 1
							; to the counter, and if a negative is
							; found, we add -1 to the counter... If
							; there are more negatives than positives at
							; the end, it's negative, otherwise it's
							; positive.

			inc		r14		; Increment the numerical *str pointer
							; whether we need it or not in true ASM
							; fashion.

			cmp		rax, 0		; If either a minus or plus sign was found,
							; then rax will not be zero.

			jne		isawthesign	; If non-zero was found in rax, repeat sign
							; instructions on next char.

			dec		r14 		; Otherwise, decrement *str pointer, because
							; we didn't need to increment it. Now we'll
							; know our sign and have r14 pointing at
							; what should be the first actual number in
							; the str!

			cmp		r13, 0		; if r13 is negative, the number is
							; negative, otherwise the number is
							; positive.

			cmovl		r13, rdx	; So, if negative (i.e. less than 0), r13
							; is -1.

			cmovge		r13, rcx	; If greater than or equal to 0, r13 is 1.
							; Now we can just multiply it by the result
							; to get our sign back. Woohoo!
			xor			rax, rax

		atoi:					; The main event! We'll use strchr to see
							; which number each symbol of the base
							; corresponds to, based on its position in
							; the string. Position 0 == 0, position 1 ==
							; 1, etc.

			cmp		[r14], 0	; So! Very important thing to do that caused me a
								; bug. Of course, we want to know if our number
								; pointer is actually pointing at anything... if
								; it's pointing at a null... well... we'll
								; probably want to leave. xD

			je		return		; Yeah... oops. ;)

			xor		rsi, rsi	; Let's clear rsi. It's good hygiene.

			mov		rdi, r15	; First! We move the pointer to the
							; *base into rdi, as that is strchr's first
							; argument. That is in r15, as I'm SURE you
							; remember. ;)

			mov		sil, byte [r14]	; Next! We move the byte we are checking to
							; rsi, as this is the second argument of
							; strchr. That will be pointed to by the
							; address we're saving in r14, of course!
							; We move it into the low byte of rsi, which
							; is called sil.

			call		_ft_strchr	; NOW! The real game begins... We CHECK
							; to see where in the base (if anywhere)
							; the symbol we are pointing to is located.

			cmp		rax, 0		; If the return address is null, it was not
							; found.

			je		return		; If it was not found, the number is over.
							; Return.

			sub		rax, r15	; We need to subtract the pointer to the
							; first character in the base from the
							; pointer returned by strchr to find the
							; symbol's position in the base! Easy peasy,
							; that's rax - r15. :) Rax now contains...
							; OUR NUMBER! Ooooh.

			mov		rcx, rax	; Let's put it in rcx for a second.

			mov		rax, rbx	; Now we just need a place to store our
							; result. Can you think of any better place
							; than rbx? I can't! Mainly because all the
							; rest of the preserved registers are in
							; use already. :p So let's move rbx (result)
							; into rax.

			mul		r12		; Remember our base (that is, the strlen of
							; the base string)? We stored it in r12 for
							; safekeeping. Time to bring it out of
							; retirement! We multiply our (base) r12 by
							; (result) rax.

			add		rax, rcx	; And then we add OUR NUMBER! Our beautiful
							; innocent, symbolized number!

			mov		rbx, rax	; We store the result back in rbx, where it
							; will be safe.

			inc		r14		; We increment r14, because we don't want to
							; be at this forever...

			jmp		atoi		; And we do it all... over... again...
		
		return:					; We're here! We're finally here!

			mov		rax, rbx	; We move our result into rax.

			mul		r13		; Multiply by 1 or -1, depending on the
							; sign. This should be our final answer.

			pop		rbx		; Not so fast! We have a ton of preserved
							; registers to restore to their former
							; glory...

			pop		r12

			pop		r13

			pop		r14

			pop		r15		; That's better! But why am I suddenly in
							; the mood for popcorn?

			ret				; If I never see another atoi for as long
							; as I live, it will be too soon! Back to
							; you, caller.

FT_LIST_SORT

This function will compare all datasets in the a t_list struct list against each other and reorder
them from lowest to highest numerically. In my test I demonstrate this with a list of character
strings each containing one letter of the alphabet (lower and upper case) or one digit (0-9),
which are then reordered within the list in ascending ASCII order, but this function will, of
course, reorder datasets of any 'type'. Indeed, since completing the Assembly Library project,
I feel compelled to always put 'type' in quotes lest I forget that they're mere abstractions or
categorizations of the same underlying 1s and 0s that we can and will order at our leisure, no
matter how they identify. ;p

The function is passed a pointer to a pointer to the first member of the list and a pointer to
a function that we assume to be ft_strcmp.


	_ft_list_sort:
		nullcheck:						; Step one will be to check the
									; passed arguments for nullity.

			push	r15					; Can a brother get a preserved
									; register or three? We push these
									; preserved registers to the stack
									; so we can use them for our
									; nefarious plans.

			push	r14

			push	r13

			mov		r15, rdi			; r15 = begin_list

			mov		r14, rsi			; r14 = function pointer

			xor		rax, rax			; Set rax to 0.

			cmp		qword [rdi], 0 			; Dereference the double pointer
									; to look at the pointer it is
									; pointing to (the pointer to the
									; first member of the list), which
									; like all pointers on a 64 bit
									; machine, will be a qword, and
									; compare that pointer to 0 (that
									; is, subtract 0 from it, and set
									; flags accordingly).

			je		return				; If the zero flag is set after
									; the comparison, the list pointer
									; is NULL. Go directly to return.
									; Do not pass GO. Do not collect
									; $200.

			mov		rdi, [rdi] 			; Otherwise, change the value in
									; rdi from the pointer to the
									; pointer to the first list member
									; (begin_list) to the pointer to
									; the first list member (that is,
									; *begin_list, or begin_list
									; dereferenced one level).

			cmp		qword [rdi + 8], 0		; Now we want to know if the
									; SECOND list member (rdi->next)
									; is NULL, because if it is... well,
									; there's not much comparing to be
									; done, is there!? So dereference
									; the pointer to the first list
									; member to go directly to its first
									; byte...
									; 
									; The first variable in the t_list
									; struct is a pointer (to the
									; dataset), which is 8 bytes wide.
									; So we add 8 bytes to the address.
									; 
									; The next variable is also a pointer
									; (to the next t_list member, in the
									; struct declaration, this is t_list
									; *next), so it's also 8 bytes wide,
									; that is, it's a qword. That's our
									; target, so we grab a qword-sized chunk
									; of data and subtract 0 from it to
									; do the compare.

			je		return				; If the zero flag is set, the first
									; list member's next pointer is NULL.
									; So there is no second member. So we
									; return, nothing to see here folks.

			mov		rsi, [rdi + 8]			; Otherwise, we copy the pointer address
									; to the next list member into rsi. Hmm...
									; first rdi... then rsi... can you tell
									; I'm about to call an external function? ;)

			mov		rsi, [rsi]			; Now for the next function I'm going to call,
									; I'm not interested in the address of the
									; list member, but rather the address of the
									; dataset it contains. So I dereference the
									; address now contained in rsi (which is
									; *begin_list->next) so I instead get the
									; address of the first byte of data of the
									; list member struct it points to (that is,
									; *begin_list->next->data).

			mov		r13, rdi			; And for good measure, I save the pointer
									; to the first member of the list (which is
									; what we still have in rdi) into r13 for
									; use as an index. That is, r13 = *begin_list.

			jmp		datacmploop			; From here, we jump to the data comparison
									; loop. We don't go from here to swap!
		
		swap: 							; We come here from the datacmploop, not from
									; the nullcheck! If we're here, then rdi == lst
									; and rsi == lst->next.

			mov		rcx, [rdi]			; We save lst->data to rcx as temp pointer.

			mov		rax, [rsi]			; Pass lst->next->data to rax register.

			mov		qword [rdi], rax		; Now we copy rax (lst->next->data) into the
									; memory pointed to by the address in rdi (the
									; first 8 bytes of the struct are the data addr),
									; so: lst->data = lst->next->data.

			mov		qword [rsi], rcx		; Now we copy rcx (the temp pointer to lst->data)
									; into the memory pointer to by the address in rsi
									; (the first 8 bytes of lst->next are
									; list->next->data), so: lst->next->data = lst->data.
									
			mov		r13, [r15]			; If we had to swap datasets because one with a higher
									; value came after one with a lower value, we might
									; also have to swap it with the preceding list member,
									; who knows? So we want to start the loop again from
									; the very first member. So our index, r13, = *begin_list,
									; which, of course, is just r15 (begin_list) dereferenced
									; once.

		datacmploop: 						; If we're here, r13 == lst. All other pointers are
									; derived from this simple fact. :)

			cmp		qword [r13 + 8], 0		; If *lst->next is NULL, we have reached the end of
									; the loop without being diverted into the swap
									; instruction block and resetting r13 to *begin_list,
									; so that means our list must be ordered!

			je		return				; If list->next is NULL all datas are ordered, so our
									; work here is done. Go to return.

			xor		rax, rax			; Clean rax.

			mov		rdi, r13			; The first argument we'll pass to our string compare
									; function, ft_strcmp, will be the address of lst->data.
									; First we need the pointer to lst, so rdi = lst.

			mov		rsi, [rdi + 8]			; The second argument we'll pass to our string compare
									; function is the address of lst->next->data. Since we
									; have the pointer to lst in rdi, we can dereference it
									; to go to the struct it points to, and add 8 bytes to
									; go to the location of the next pointer within that
									; struct, and then copy the address stored there into
									; rsi. Thus: rsi = lst->next, or, in other words:
									; rsi = *(rdi + 8).

			mov		rsi, [rsi]			; Dereference lst->next to get to the first variable in
									; the list member it points to, which is the address to
									; its data (lst->next->data), an 8 byte variable, so, a
									; qword. Move that address into rsi.
									; 
									; So, now: rsi = lst->next->data, or, in other words,
									; rsi = rsi->data

			mov		rdi, [rdi]			; Since we've got rsi set up, we dereference rdi (lst)
									; to get the first variable in the lst struct, which is
									; its data pointer. So, now rdi = lst->data.

			call		r14				; We now call the function (ft_strcmp). At the beginning
									; of the function we saved the function pointer into the
									; r14 register, so we just call up the instructions at
									; that address, with our first argument, rdi, being
									; lst->data, and our second argument, rsi, being
									; lst->next->data.
									;
									; So we're comparing the data in the list member we're
									; analysing to the data in its neighbour.
									;
									; If the compare function finds any difference, it will
									; return the first difference it finds in rax.
									; 
									; If the difference is a positive number, then the second
									; argument is less than the first. (10 - 5 = 5).
									;
									; If the difference is a negative number, then the
									; second argument is greater than the first (5 - 10 = -5).
									;
									; If the difference is 0, then the first and second
									; arguments are equal.
									;
									; If the difference we find is positive (the second
									; argument is less than the first), then they are
									; unordered and we need to swap them, as the purpose of
									; this function is to leave the datasets in ascending order
									; in the list.

			mov		rdi, r13			; We store the original lst pointer in rdi again. rdi = lst

			mov		rsi, [rdi + 8]			; We store the original lst->next pointer in rsi again.
									; rsi = lst->next == *(rdi + 8) Now if we need to swap them
									; we'll be ready.

			cmp		eax, 0				; Is the result positive? (lst->data > lst->next->data?) To
									; determine this we subtract 0 from eax (which, of course,
									; will always return eax, but we do this to set the flags).
									;
									; The CPU knows something is greater or less than by
									; checking the zero flag and the overflow and sign flags.
									;
									; If the zero flag IS set OR the overflow and sign flags are
									; NOT the same, then it's equal to (if ZF) or less than (if
									; (SF != OF).
									;
									; If the zero flag is NOT set AND the overflow and sign
									; flags are the same, then it's greater than.
									; 
									; Bit counterintuitive, but it works! Some examples of how:
									;
									; For example, let eax be -1, and let's ask:
									; Is -1 GREATER than 0?
									;
									; In Assembly, we say cmp eax, 0:		-1 - 0 == -1.
									; -1 is not zero, so: 				ZF = 0.
									; -1 is negative, so: 				SF = 1.
									; -1 didn't change signs (overflow), so:	OF = 0.
									; SF != OF, so eax (-1) is less than 0.
									;
									; For example, let eax be +1, and let's ask:
									; Is +1 greater than 0?
									;
									; In Assembly, we say cmp eax, 0:		1 - 0 == 1.
									; 1 is not zero, so:				ZF = 0.
									; 1 is positive, so: 				SF = 0.
									; 1 didn't change signs (overflow), so:		OF = 0.
									; ZF == 0 AND SF == OF, so it MUST be greater than.
									;
									; *sigh* I <3 Assembly. ;)
									;
									; Finally, we use eax, the 32-bit register here, as ft_strcmp
									; returns an int (that's four bytes, or 32 bits). We don't
									; care about the higher bits, although ft_strcmp should clean
									; tidy them up by zeroing them if it's being properly
									; behaved ;).

			jg		swap				; If eax is greater than 0 (that is, a positive number), then
									; jump to the block of swap instructions to swap these
									; datasets.

			mov		r13, rsi			; If eax is less than or equal to 0, these datasets needn't be
									; be swapped, so we can move onto the next list member and
									; continue the compare loop.
									;
									; Remember we made rsi lst->next again. Now we want our pointer
									; index to point to the next list member. So r13, currently
									; pointing to lst, will be set to lst->next (lst = lst->next).

			jmp		datacmploop			; In that case, no swapping, just jump back to the first
									; datacmploop instruction.

		return:							; The end! This is a void function, so it doesn't return
									; anything. All we need to do is restore our reserved registers,
									; pray to the Gods of Stack Alignment, and be on our way.

			pop		r13				; Restore the preserved registers to their original state.

			pop		r14

			pop		r15

			ret						; Our prayers have been answered!
