global _cipher
extern printf
section .text
_cipher:
    push ebp
    mov ebp, esp

    call _len

    lea eax, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]

loop:
    mov byte bl, [eax]
    cmp byte bl, 0
    je exit

    mov byte bl, [eax + 1]
    cmp byte bl, 0
    je lastSave

    mov byte bl, [eax + 2]
    cmp byte bl, 0
    je lastSave

    mov byte bl, [eax + 3]
    cmp byte bl, 0
    je lastSave

    xor ecx, edx    ; xor values, we get ciphered block
    xor ecx, [eax]    ; xor 4 bytes of text with ciphered block, now vector is ciphered text
    mov [eax], ecx  ; save result in text

    add eax, 4  ; go to the next 32 bits
    jmp loop

lastSave:
    xor  ecx,  edx    ; xor values, we get ciphered block
    xor  ecx,  [eax]    ; xor 4 bytes of text with ciphered block, now vector is ciphered text
    mov [eax], ecx  ; save result in text

exit:
    mov eax, 4
    mov ebx, 1
    lea ecx, [ebp + 8]
    mov edx, edi
    int 0x80
    mov esp, ebp
    pop ebp
    ret

_len:
    mov edi, 0
    lea ebx, [ebp + 8]
    count:
     inc edi
     inc ebx
     cmp byte[ebx], 0
     jnz count
    dec edi
    ret

