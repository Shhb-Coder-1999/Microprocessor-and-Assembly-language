    AREA RESET , DATA , READONLY
	DCD 0x10008000	;
	DCD Reset_Handler ; 
    AREA MYCODE , CODE , READONLY

ENTRY
Reset_Handler
    mov r0,#4
	ldr r1, =NumberInROM
	ldr r4, =0x10007FFF
	add r4,#0x10000000
	mov r5,#2
	sdiv r4,r4,r5
	subs r4,#2
	ldrb r3 , [r1]; read first data from flash

TestNextByte
    
	ldrsb r3 , [r1];
	str r3,[r4]
	add r4,#1
	add r1,#1
    subs r0,#1
	bne TestNextByte
	
	
loop
    b loop
	
NumberInROM	DCB 0x58 ,0x57 ,0x56 ,0x55  
      AREA MYData , DATA , READWRITE
	  COMMON NumberInRAM ,4 ,4
	  end
	  