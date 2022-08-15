;
; imagine being unmotivated 💀
;


[org 0x7c00]

mov bx, HELLO_MSG 
call print_line

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 5
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex
call newline

mov dx, [0x9000+512]
call print_hex
call newline

mov bx, GOODBYE_MSG
call print_line

jmp $ 

%include "print_string.asm"
%include "read_disk.asm"

; Data
HELLO_MSG :
db 'Hello World!', 0

GOODBYE_MSG :
db 'feur', 0

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xbeef
times 256 dw 0xface