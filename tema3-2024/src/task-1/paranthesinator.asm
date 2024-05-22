; Interpret as 32 bits code
[bits 32]

%include "../include/io.mac"

section .text
; int check_parantheses(char *str)
global check_parantheses
check_parantheses:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8] ; sirul de caractere
    mov edi, 0
    mov ecx, 0
    
    loop:
        cmp byte [eax + ecx], 0
        je give_good_ans

    extract_value:
        cmp byte [eax + ecx], '{'
        je introduce_in_stack
        cmp byte [eax + ecx], '['
        je introduce_in_stack
        cmp byte [eax + ecx], '('
        je introduce_in_stack
        cmp edi, 0
        je give_wrong_ans
        cmp byte [eax + ecx], '}'
        je extract_from_stack_1
        cmp byte [eax + ecx], ']'
        je extract_from_stack_2
        cmp byte [eax + ecx], ')'
        je extract_from_stack_3
        

    introduce_in_stack:
        movzx edx, byte [eax + ecx]
        push edx
        inc edi
        jmp next_char


    extract_from_stack_1:
        dec edi
        cmp edx, '{'
        jne give_wrong_ans
        pop edx
        cmp edi, 0
        jne update_last
        je next_char
    
    extract_from_stack_2:
        dec edi
        cmp edx, '['
        jne give_wrong_ans
        pop edx
        cmp edi, 0
        jne update_last
        je next_char

    extract_from_stack_3:
        dec edi
        cmp edx, '('
        jne give_wrong_ans
        pop edx
        cmp edi, 0
        jne update_last
        je next_char

    update_last:
        pop edx
        jmp next_char


    erase_stack:
        cmp edi, 0
        je give_wrong_ans
        dec edi
        pop edx
        jmp erase_stack
        
    next_char:
        inc ecx
        jmp loop

    give_wrong_ans:
        cmp edi, 0
        jne erase_stack
        mov eax, 0
        jmp done

    give_good_ans:
        mov eax, 1
        jmp done

    return:
        ret

    done:
        leave
        ret
