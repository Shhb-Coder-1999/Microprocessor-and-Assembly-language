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
    ldrsb r2 ,[r1] ; read first data from flash
	cmp r2,#0      ;if r2==0 goto loop . why 0 ? couse 0 in our condition to break loop
	beq   loop
	add r1,#1      ;increment pointer
	strb r2,[r4]   ;write data to ram
	strb r2,[r5]   ;write data to ram
	
	add r4,#1      ;add RAM pointer with 1
	add r5,#1      ;add RAM pointer with 1
	b TestNextByte

loop
    b loop
	
MyNameInROM	DCB "abbas laki",0  
      AREA MYData , DATA , READWRITE
	  COMMON MyNameInRAM ,12 ,4
	  COMMON MyBookInRAM ,12 ,4
	  
	  end
	  