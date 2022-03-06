STACK_TOP EQU 0x20002000

    AREA RESET,CODE
    DCD STACK_TOP
    DCD start
    ENTRY
start
    mov r0,#5
    mov r1,#7
    add r0,r0,r1
	subs r0,r0,r1
	;stm r6!,(r5,r4,r9)
	mov r1,#5
	mov r2,#6
	mov r3,#7
	mov r4,#10
	mla r3,r1,r2,r4  ;r3 = r3 + (r1*r2)
	
loop
    b loop
    end