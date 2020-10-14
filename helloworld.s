global _helloworld

section .data

		hi:		db 'Hello, world!',0xA
		len:	equ $ - hi

section .text
		_helloworld:

		mov		rax, 0x2000004 ; write
		mov		rdi, 1 ; stdout
		mov		rsi, hi ; ptr
		mov		rdx, len
		syscall

		mov		rax, 0x2000001 ; exit
		mov		rdi, 0
		syscall