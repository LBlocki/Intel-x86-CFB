global _cipher
extern printf
section .text
_cipher:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8] ;text
    mov ecx, [ebp + 12]	; vector
    mov edx, [ebp + 16]	; key

loop:
    mov byte bl, [eax]	; check if 0 on first byte
    cmp byte bl, 0
    je exit

    mov byte bl, [eax + 1]	; check if 0 on second byte
    cmp byte bl, 0
    je lastSave

    mov byte bl, [eax + 2]	; check if 0 on third byte
    cmp byte bl, 0
    je lastSave

    mov byte bl, [eax + 3]	; check if 0 on fourth byte
    cmp byte bl, 0
    je lastSave

    mov edi, [ecx]
    xor edi, [edx]    	; xor values, we get ciphered block
    xor edi, [eax]    	; xor 4 bytes of text with ciphered block
    mov [eax], edi  	; save result in text
    mov [ecx], edi	; now vector is ciphered text

    add eax, 4  ; go to the next 32 bits
    jmp loop

lastSave:
    mov edi, [ecx]
    xor edi, [edx]    ; xor values, we get ciphered block
    xor edi, [eax]    ; xor 4 bytes of text with ciphered block, now vector is ciphered text
    mov [eax], edi  ; save result in text
    mov [ecx], edi

exit:
    mov esp, ebp
    pop ebp
    ret

