;;boot.asm

;nasm directive - 32 bit
bits 32

%define STACK_SIZE 8192 ; 8KB
global _stack_space
global _stack_space_end

section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			;magic
	dd 0x00				;flags
	dd - (0x1BADB002 + 0x00)	;checksum. m+f+c should be zero

global read_port
global write_port
global gdt_flush
global outb
global start

extern main				;main is defined in the c file

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

gdt_flush:
	mov eax, [esp+4]		; Load the address of the GDT descriptor from the stack
	lgdt [eax]			; Load GDT

	mov eax, 0x10			; Load data segment selector into eax
	mov ds, ax			; Load ds with data segment selector
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush			; Jup to flush
.flush:
	ret

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
outb:
    mov al, [esp + 8]    ; move the data to be sent into the al register
    mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
    out dx, al           ; send the data to the I/O port
    ret                  ; return to the calling function

start:
	cli				;block interrupts
	mov esp, _stack_space_end	;set stack pointer
	call main
	hlt				;halt the CPU

section .bss
_stack_space:
	resb STACK_SIZE				;defines the size of the stack see define on top of file
_stack_space_end:
