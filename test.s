global _test

section .text


_test:
	mov rax, 42
	mov rbx, 2
	mov rdx, 0
	div rbx
	mov rdi, rax
	mov rax, 0x2000001 ; asigna 1 a rax (hay que sumarle 0x200000 en MacOSX por motivos que aun no alcanzo a entender)
;	mov rdi, rbx ; exit status se guarda en destination index en MacOSX
	syscall ; syscall coge el valor de rax, 0x2000001, que es señal exit. echo $? devuelve exit status del último comando
