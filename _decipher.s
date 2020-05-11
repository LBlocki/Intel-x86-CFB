global _decipher
extern printf
section .text
_decipher:
    push rbp
    mov rbp, rsp
loop:

    mov byte dil, [rcx + 4]	; check if end of string on first byte
    cmp byte dil, 0
    je exit

    mov byte dil, [rcx + 5]	; check if end of string on second byte
    cmp byte dil, 0
    je lastSave

    mov byte dil, [rcx + 6]	; check if end of string on third byte
    cmp byte dil, 0
    je lastSave

    mov byte dil, [rcx + 7]	; check if end of string on fourth byte
    cmp byte dil, 0
    je lastSave

    mov rdi,  [r8]      ; set rdi to key value
    xor rdi,  [rdx]    	; xor rdi ( key ) with vector

    mov rsi, [rcx]
    mov [rdx], rsi      ; set vector to ciphered text

    xor rdi,  [rcx]    	; xor cihered block with plain text
    mov [rcx], rdi  	; modify 8 bytes of plain text as ciphered text

    add rcx, 8  ; go to the next 32 bits
    jmp loop

lastSave:
    mov rdi,  [r8]      ; set rdi to key value
    xor rdi,  [rdx]    	; xor rdi ( key ) with vector

    mov rsi, [rcx]
    mov [rdx], rsi      ; set vector to ciphered text

    xor rdi,  [rcx]    	; xor cihered block with plain text
    mov [rcx], rdi  	; modify 8 bytes of plain text as ciphered text

exit:
    mov rsp, rbp
    pop rbp
    ret

