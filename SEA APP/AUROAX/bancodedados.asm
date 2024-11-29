section .data
    userId db 'user123', 0
    isSubscriber db 1   ; 1 for subscriber, 0 for non-subscriber

section .bss
    userStatus resb 1  ; Space to store user status

section .text
    global _start

_start:
    ; Here you would typically have logic to retrieve user information
    ; For the sake of example, let's just simulate checking subscription status
    mov al, [isSubscriber] ; Load subscription status into AL
    mov [userStatus], al   ; Store the result in userStatus

    ; Exit the program (Linux syscall)
    mov eax, 60           ; syscall: exit
    xor edi, edi          ; status: 0
    syscall
