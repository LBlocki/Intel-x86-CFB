global _decipher
extern printf
section .text
_decipher:
    push ebp
    mov ebp, esp

    call _len

    lea eax, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]

_loop:
    mov byte bl, [eax]
    cmp byte bl, 0
    je _exit

    mov byte bl, [eax + 1]
    cmp byte bl, 0
    je _lastSave

    mov byte bl, [eax + 2]
    cmp byte bl, 0
    je _lastSave

    mov byte bl, [eax + 3]
    cmp byte bl, 0
    je _lastSave

    xor ecx, edx    ; xor values, we get ciphered block and new vector
    xor [eax], ecx    ; xor 4 bytes of ciphered text with ciphered block -> we get 32 bits of clean text

    add eax, 4  ; go to the next 32 bits
    jmp _loop

_lastSave:
    xor ecx, edx    ; xor values, we get ciphered block and new vector
    xor [eax], ecx    ; xor 4 bytes of text with ciphered block -> we get 32 bits of clean text

_exit:
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



