global _cipher
extern printf
section .text
_cipher:
    push ebp
    mov ebp, esp
    lea eax, [ebp + 8]
loop:
    mov dl, byte [eax + 8]  ; check if the end of string
    cmp dl, byte 0
    je exit

    mov dl, byte [eax + 9]  ; check if the end of string
    cmp dl, byte 0
    je lastSave

    mov dl, byte [eax + 10]  ; check if the end of string
    cmp dl, byte 0
    je lastSave

    mov dl, byte [eax + 11]  ; check if the end of string
    cmp dl, byte 0
    je lastSave

    mov edx, dword [ebp + 16] ; move key do edx
    mov ebx, dword [ebp + 12] ; vector to ebx

    xor edx, ebx    ; xor values, we get ciphered block
    xor edx, [eax]    ; xor 4 bytes of text with ciphered block

    mov [ebp + 12], dword edx ; save result in vector
    mov [eax], dword edx  ; save result in text

    add eax, dword 4  ; go to the next 32 bits
    jmp loop

lastSave:
    mov edx, dword [ebp + 16] ; move key do edx
    mov ebx, dword [ebp + 12] ; vector to ebx

    xor edx, ebx    ; xor values, we get ciphered block
    xor edx, [eax]    ; xor 4 bytes of text with ciphered block

    mov [ebp + 12], dword edx ; save result in vector
    mov [eax], dword edx  ; save result in text

exit:
    push dword [ebp + 8]
    call printf
    mov esp, ebp
    pop ebp
    ret



