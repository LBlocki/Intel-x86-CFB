global _decipher
section .text
_decipher:
    push rbp
    mov rbp, rsp

        ;rcx is text
        ; r8 is key
        ; rdx is vector
        ; r9 is text length
loop:

    mov edi, dword [r8]      ; set rdi to key value
    xor edi, dword [rdx]    	; xor rdi ( key ) with vector

    mov esi, dword [rcx]
    mov dword [rdx], esi      ; set vector to ciphered text

    xor edi, dword [rcx]    	; xor cihered block with plain text
    mov dword [rcx], edi  	; modify 4 bytes of plain text as ciphered text

    add rcx, 4    ; move to the next 32 bytes

    sub r9, 4   ; substract 4 from amount of text left
    cmp r9, 0   ; if none left, then exit, otherwise continue the loop
    jg loop

exit:
    mov rsp, rbp
    pop rbp
    ret

