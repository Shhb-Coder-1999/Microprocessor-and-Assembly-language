STACK_TOP EQU 0x20002000

    AREA RESET,CODE
    DCD STACK_TOP
    DCD start
    ENTRY
start
    mov r0,#5
    mov r1,#7
    add r0,r1
loop
    b loop
    end