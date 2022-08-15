;💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀
;💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀Assembly be like💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀
;💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀

[org 0x7c00]

KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, RM_MSG
call print_line_rm

call load_kernel

call switch_to_protected_mode

jmp $

%include "source/boot/print_string.asm"
%include "source/boot/print_string_rm.asm"
%include "source/boot/gdt.asm"
%include "source/boot/read_disk.asm"
%include "source/boot/protected_mode_handler.asm"

[bits 16]

load_kernel :
	mov bx, MSG_LOAD_KERNEL ; Print a message to say we are loading the kernel
	call print_line_rm
	mov bx, KERNEL_OFFSET ; Set-up parameters for our disk_load routine , so
	mov dh, 15 ; that we load the first 15 sectors ( excluding
	mov dl, [BOOT_DRIVE] ; the boot sector ) from the boot disk ( i.e. our
	call disk_load ; kernel code ) to address KERNEL_OFFSET
ret

[bits 32]

BEGIN_PM:

	mov ebx, PM_MSG
	call print_string

	call KERNEL_OFFSET

	jmp $


; Data
BOOT_DRIVE db 0
RM_MSG db "Started in 16 bits real mode", 0
PM_MSG db "Successfully landed in 32 bits protected mode", 0
MSG_LOAD_KERNEL db " Loading kernel into memory. " , 0

times 510-($-$$) db 0
dw 0xaa55
