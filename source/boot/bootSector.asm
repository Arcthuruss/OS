;💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀
;💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀Assembly be like💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀
;💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀

[org 0x7c00]
bits 16

boot:
    jmp main
    TIMES 3-($-$$) DB 0x90   ; Support 2 or 3 byte encoded JMPs before BPB.

    ; Dos 4.0 EBPB 1.44MB floppy
    OEMname:           db    "mkfs.fat"  ; mkfs.fat is what OEMname mkdosfs uses
    bytesPerSector:    dw    512
    sectPerCluster:    db    1
    reservedSectors:   dw    1
    numFAT:            db    2
    numRootDirEntries: dw    224
    numSectors:        dw    2880
    mediaType:         db    0xf0
    numFATsectors:     dw    9
    sectorsPerTrack:   dw    18
    numHeads:          dw    2
    numHiddenSectors:  dd    0
    numSectorsHuge:    dd    0
    driveNum:          db    0
    reserved:          db    0
    signature:         db    0x29
    volumeID:          dd    0x2d7e5a1a
    volumeLabel:       db    "NO NAME    "
    fileSysType:       db    "FAT12   "

main:

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
	mov dl, [BOOT_DRIVE] ; the boot sector ) from the boot disk ( i.e. our kernel code ) to address KERNEL_OFFSET
	call disk_load
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
