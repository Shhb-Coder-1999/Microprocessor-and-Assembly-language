    AREA RESET , DATA , READONLY
	DCD 0x10008000	;
	DCD Reset_Handler ; 
		
    AREA MYCODE , CODE , READONLY

ENTRY
Reset_Handler
;   mov r0,#8
    mov r1,#-3
	lsl r1,#1
 	mov r2,#-3
	lsr r2,#1
	mov r3,#-3
	asr r3,#1
	


    mov r0,#10-1
	ldr r1, =NumberInROM
	ldr r4, =NumberInRAM
	ldrsb r2 , [r1]; read first data from flash
	ldrb r3 , [r1]; read first data from flash

TestNextByte
    add r1,#1
	ldrsb r3 , [r1];
	str r3,[r4]
	add r4,#4
	cmp r2,r3
	bge NoExchange
	mov r2,r3

NoExchange
    subs r0,#1
	bne TestNextByte
	
	
loop
    b loop
	
NumberInROM	DCB -3,45,-45,111,176,29,23,-34,-78,0x25  
      AREA MYData , DATA , READWRITE
	  COMMON NumberInRAM ,12 ,4
	  end
	  