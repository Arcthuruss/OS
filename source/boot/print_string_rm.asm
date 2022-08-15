[bits 16]
print_string_rm:
	pusha
	mov ah, 0x0e
	
	loopzoop:
		mov al, [bx]
		cmp al, 0
		je print_string_rm_end
		int 0x10
		inc bx
	jmp loopzoop
	
	print_string_rm_end:
	popa
	ret

print_line_rm:
	pusha
	call print_string_rm
	call newline_rm
	popa
	ret

newline_rm:
	pusha
	mov ah, 0x0e
	mov al, 0xa
	int 0x10
	mov al, 0xd
	int 0x10
	popa
	ret
