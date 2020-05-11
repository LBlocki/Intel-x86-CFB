global _decipher
extern printf
section .text
_decipher:
    push ebp
    mov ebp, esp

    mov esi, 0
    mov ebx, [ebp + 8]
    count:
     inc esi
     inc ebx
     cmp byte[ebx], 0
     jnz count

    mov eax, [ebp + 8]
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

    mov edi, [ecx]
    xor edi, [edx]    ; xor values, we get ciphered block
    mov [ecx], edi
    xor edi, [eax]    ; xor 4 bytes of text with ciphered block
    mov [eax], edi  ; save result in text
    
    add eax, 4  ; go to the next 32 bits
    jmp loop

lastSave:
    mov edi, [ecx]
    xor edi, [edx]    ; xor values, we get ciphered block
    mov [ecx], edi
    xor edi, [eax]    ; xor 4 bytes of text with ciphered block
    mov [eax], edi  ; save result in text


exit:
    mov esp, ebp
    pop ebp
    ret

