section .data
    input_data db 0        ; Dado de entrada
    result db 0            ; Resultado

section .text
    global _start

_start:
    ; Carregar dado de entrada para um registrador
    mov al, [input_data]
    
    ; Executar uma operação simples - exemplo: dobrar o valor
    shl al, 1

    ; Armazenar o resultado
    mov [result], al

    ; Encerrar o programa (apenas exemplo)
    mov eax, 60
    xor edi, edi
    syscall
