    AREA RESET , DATA , READONLY
	DCD 0x10008000	;
	DCD Reset_Handler ; 
		
    AREA MYCODE , CODE , READONLY

ENTRY
Reset_Handler
;    mov r0,#8

    ldr r1, =MyNameInROM
	ldr r4, =MyNameInRAM
	ldr r5, =MyNameInRAM

TestNextByte
    ldrsb r3,[r1]
	
    cmp r3,#32      ;if r2==0 goto loop . why 0 ? couse 0 in our condition to break loop
	beq NoExchange
	;mov r2,#20
	cmp r3,#0      ;if r2==0 goto loop . why 0 ? couse 0 in our condition to break loop
	beq   loop
	sub r3 ,#32
	
NoExchange 
	
	add r1,#1      ;increment pointer
	
	
	
	strb r3,[r4]   ;write data to ram
	strb r3,[r5]   ;write data to ram
	
	add r4,#1      ;add RAM pointer with 1
	add r5,#1      ;add RAM pointer with 1
	b TestNextByte

loop
    b loop
	
MyNameInROM	DCB "shahab shafie",0  
      AREA MYData , DATA , READWRITE
	  COMMON MyNameInRAM ,12 ,4
	  COMMON MyBookInRAM ,12 ,4
	  
	  end
	  