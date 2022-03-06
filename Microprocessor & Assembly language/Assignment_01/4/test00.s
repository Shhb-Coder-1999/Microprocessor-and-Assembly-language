    AREA RESET , DATA , READONLY
	DCD 0x10008000	;
	DCD Reset_Handler ; 
		
    AREA MYCODE , CODE , READONLY

ENTRY
Reset_Handler

    mov r0,#4-1
	ldr r1, =NumberInROMVahed
	ldr r5, =NumberInROMNomre
	ldr r4, =NumberInRAM
	ldrb r2 , [r1]; read first data from flash
	ldrb r3 , [r5]; read first data from flash
	mul r8,r2,r3  ;r8 = r8 + (r1*r2)
	add r6,r2 ; jame vahed ha
	add r9,r8 ; majmoe vahed*nomre hame doros

TestNextByte
	
	
    add r1,#1
	add r5,#1
	ldrsb r2 , [r1];
	ldrsb r3 , [r5];
	
	mul r8,r2,r3  
	add r6,r2 ; jame vahed ha
	add r9,r8 ; majmoe vahed*nomre hame doros
	
	
	str r8,[r4]
	add r4,#4
	
	subs r0,#1
	bne TestNextByte
 
    sdiv r10,r9,r6
	

	
loop
    b loop
	
NumberInROMVahed	DCB 1,3,3,2
NumberInROMNomre	DCB 17,20,18,15
      AREA MYData , DATA , READWRITE
	  COMMON NumberInRAM ,6 ,4
	  end
	  