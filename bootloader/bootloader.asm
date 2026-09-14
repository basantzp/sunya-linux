; Sunya Linux Bootloader
; Minimal x86_64 boot code

[BITS 16]
[ORG 0x7C00]

start:
    mov ax, 0x0000
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, msg_boot
    call print_string

    cli
    hlt

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

msg_boot: db "Sunya Linux Bootloader v0.1.0", 0x0D, 0x0A, 0

times 510-($-$$) db 0
dw 0xAA55
