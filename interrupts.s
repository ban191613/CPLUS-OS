.section .text
.extern __ZN15InterruptManger15handleInterruptEhj

int_bootom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptNumber)
    call __ZN15InterruptManger15handleInterruptEhj

    movl  %eax,%esp
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

    iret


.section .data
    interruptNumber .byte 0
