global _start
_start:
	mov eax, 1
	mov ebx, 42
	mov ecx, 2
	sub ebx, ecx
	add ebx, ecx
	mov eax, ebx
	mul ecx
	mov ebx, eax
	mov eax, 1
	add ebx, 1
	int 0x80
