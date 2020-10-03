global start

section .text


start:
	mov rax, 0x2000001 ; asigna 1 a rax (hay que sumarle 0x200000 en MacOSX por motivos que aun no alcanzo a entender)
	mov rdi, 42 ; exit status se guarda en destination index en MacOSX
	syscall ; syscall coge el valor de rax, 0x2000001, que es señal exit. echo $? devuelve exit status del último comando
