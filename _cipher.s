global _cipher
section .text
_cipher:
    push rbp
    mov rbp, rsp
        ; on linux rdi is text
        ; on linux rdx is key
        ; on linux rsi is vector
        ; on linux rcx is text length
loop:

    mov r8d, dword [rdx]        ; set r8d to key value
    xor r8d, dword [rsi]    	; xor r8d ( key ) with vector
    xor r8d, dword [rdi]    	; xor cihered block with plain text
    mov dword [rdi], r8d  	    ; modify 4 bytes of plain text as ciphered text
    mov dword [rsi], r8d	    ; set vector to new ciphered text

    add rdi, 4   ; move to the next 32 bytes

    sub rcx, 4   ; substract 4 from amount of text left
    cmp rcx, 0   ; if none left, then exit, otherwise continue the loop
    jg loop

exit:

    mov rsp, rbp
    pop rbp
    ret

