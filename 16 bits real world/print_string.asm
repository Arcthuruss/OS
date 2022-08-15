print_string:
pusha
mov ah, 0x0e

loopzoop:
mov al, [bx]
cmp al, 0
je end
int 0x10
add bx, 1
jmp loopzoop

end:
popa
ret

print_line:
pusha
call print_string
call newline
popa
ret


print_hex:
pusha

mov bx, 0

hexloop:

mov ax, dx
and ax, 0xf
shr dx, 4
add ax, 0x30
cmp ax, '9'
jle number
add ax, 0x27
number:
mov cx, bx
mov bx, 5
sub bx, cx
mov [HEX_OUT+bx], al
mov bx, cx
inc bx

cmp bx, 3
jle hexloop

mov bx, HEX_OUT
call print_string

popa
ret

newline:
pusha
mov ah, 0x0e
mov al, 0xa
int 0x10
mov al, 0xd
int 0x10
popa
ret

;data
HEX_OUT:
db '0x0000', 0