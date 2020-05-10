section .text
global _cipher
_cipher:
    push ebp
    mov ebp, esp

loop:
    mov dl, byte [ebp + 8]  ; check if the end of string
    cmp dl, byte 0
    je exit

    mov dl, byte [ebp + 9]  ; check if the end of string
    cmp dl, byte 0
    je lastSave

    mov dl, byte [ebp + 10]  ; check if the end of string
    cmp dl, byte 0
    je lastSave

    mov dl, byte [ebp + 11]  ; check if the end of string
    cmp dl, byte 0
    je lastSave

    mov edx, dword [ebp + 16] ; move key do edx
    mov ebx, dword [ebp + 12] ; vector to ebx

    xor edx, ebx    ; xor values, we get ciphered block

    mov ebx, dword [ebp + 8] ; get 4 bytes of text
    xor edx, ebx    ; xor 4 bytes of text with ciphered block

    mov [ebp + 12], dword edx ; save result in vector
    mov [ebp + 8], dword edx  ; save result in text

    lea edx, [ebp + 8]  ; get address of current text pointer
    add edx, dword 4  ; go to the next 32 bits
    lea [ebp + 8], edx ; set address to get new 32 bits in the next loop
    jmp loop

lastSave:
    mov edx, dword [ebp + 16] ; move key do edx
    mov ebx, dword [ebp + 12] ; vector to ebx

    xor edx, ebx    ; xor values
    mov [ebp + 12], dword edx ; save result in vector
    mov [ebp + 8], dword edx  ; save result in text

exit:
    mov esp, ebp
    pop ebp
    ret


