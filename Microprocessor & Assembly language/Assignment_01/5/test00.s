    AREA RESET , DATA , READONLY
	DCD 0x10008000	;
	DCD Reset_Handler ; 
		
    AREA MYCODE , CODE , READONLY

ENTRY
Reset_Handler

    mov r0,#3-1
	
	
	ldr r1, =matrix1
	ldr r5, =matrix2
	ldr r4, =NumberInRAM
	ldrb r2 , [r1]; read first data from flash
	ldrb r3 , [r5]; read first data from flash
	mul r8,r2,r3
	add r9,r8
	mov r6,#1
	mov r7,#3

TestNextByte
	
    add r1,r6
	add r5,r7
	
	ldrb r2 , [r1];
	ldrb r3 , [r5];
	
	mul r8,r2,r3
	add r9,r8
	
	subs r0,#1
	bne TestNextByte
	


	
	str r9,[r4]
	add r4,#1
	mov r9,#0
	adds r10,1
	mov r0,#5-1
	subs r0,#1
	
	cmp r10,3
	bge NoExchange

	
	
	ldr r1, =matrix1
	ldr r5, =matrix2
	add r5,r10
	add r1,r11
	ldrb r2 , [r1]; read first data from flash
	ldrb r3 , [r5]; read first data from flash
	
	mul r8,r2,r3
	add r9,r8

	
	
	subs r0,#1
	bne TestNextByte
	
NoExchange

    cmp r11,#6
	beq loop
	
    mov r10,#0
	add r11,#3
	ldr r1, =matrix1
	ldr r5, =matrix2
	add r5,r10
	add r1,r11
	ldrb r2 , [r1]; read first data from flash
	ldrb r3 , [r5]; read first data from flash
	mul r8,r2,r3
	add r9,r8
	b TestNextByte
	
	
loop
    b loop
	
matrix1	DCB 1,3,3,2,1,3,4,2,1
matrix2	DCB 1,3,3,2,1,3,4,2,1
      AREA MYData , DATA , READWRITE
	  COMMON NumberInRAM ,6 ,4
	  end
	  