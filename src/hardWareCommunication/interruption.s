.set IQR_BASE, 0x20
.section .text
.extern __ZN15InterruptManger15handleInterruptEhj

.macro HandleInterruptRequest num
.global   __ZN15InterruptManger26HandleInterruptRequest\num\()Ev
__ZN15InterruptManger26HandleInterruptRequest\num\()Ev:
    movl $\num + IQR_BASE,(interruptNumber)
    pushl $0
    jmp int_bootom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31


.macro HandleException num
.global   __ZN15InterruptManger19HandleException\num\()Ev
__ZN15InterruptManger19HandleException\num\()Ev:
    movl $\num,(interruptNumber)
    jmp int_bootom
.endm

HandleException 0x00
HandleException 0x01
HandleException 0x02
HandleException 0x03
HandleException 0x04
HandleException 0x05
HandleException 0x06
HandleException 0x07
HandleException 0x08
HandleException 0x09
HandleException 0x0A
HandleException 0x0B
HandleException 0x0C
HandleException 0x0D
HandleException 0x0E
HandleException 0x0F
HandleException 0x10
HandleException 0x11
HandleException 0x12
HandleException 0x13

int_bootom:
    pushl %ebp
    pushl %edi
    pushl %esi

    pushl %edx
    pushl %ecx 
    pushl %ebx 
    pushl %eax 

    pushl %esp

    push (interruptNumber)
    call __ZN15InterruptManger15HandleInterruptEhj

    movl  %eax,%esp


    popl %eax
    popl %ebx
    popl %ecx
    popl %edx 

    popl %esi
    popl %edi
    popl %ebp

    add $4, %esp

.global __ZN15InterruptManger15InterruptIgnoreEv
    __ZN15InterruptManger15InterruptIgnoreEv:
    iret


.section .data
    interruptNumber: .byte 0

