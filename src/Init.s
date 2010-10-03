;---------------------------------------------------------------
;	Position Independ Code initialze for C runtime 
;   MSN : yugr_bj@hotmail.com
;---------------------------------------------------------------



	IMPORT  |Image$$ZI$$Limit|
	IMPORT  |Image$$ZI$$Base|
	IMPORT  |Image$$RW$$Base|
	IMPORT  |Image$$RW$$Limit|
	IMPORT  |Image$$RO$$Base|
	IMPORT  |Image$$RO$$Limit|
	IMPORT   main
	
	EXPORT   GetRoBasePtr
	EXPORT   GetRoEndPtr
	EXPORT   GetRwBasePtr
	EXPORT   GetRwEndPtr
	EXPORT   GetZiBasePtr
	EXPORT   GetZiEndPtr
	EXPORT   Dynamic_entry
	
	;AREA MEMLAYOUT,DATA, READONLY 
	
	;DCD |Image$$RO$$Base|
	;DCD |Image$$RO$$Limit|
	;DCD |Image$$RW$$Base|
	;DCD |Image$$RW$$Limit|

	
	AREA INIT, CODE, READONLY ,ALIGN = 4
	ENTRY; 指定应用程序的入口点
Dynamic_entry
	STMFD   R13!, {R0-R2}
	MOV     R0,  R15
	SUB     R0,  R0 ,#12

	        ;--------------------calculate rw section 
	LDR     R1, = |Image$$RO$$Base|
	LDR     R2, = |Image$$RO$$Limit|
	SUB     R1,R2,R1
	ADD     R9,R0,R1

            ;--------------------clear zi section
	LDR     R0, =|Image$$ZI$$Base|  
	ADD     R0, R0, R9
	LDR     r1, =|Image$$ZI$$Limit|  
	ADD     R1, R1, R9	
	MOV     R2, #0
	
loop_Z	
	CMP   	R0,R1
	STRCC   R2,[R0],#4
	BCC     loop_Z	
			
			;--------------------call main function

	LDMFD   R13!,{R0-R2}
	B       main

	BX      R14



GetRoBasePtr
	LDR     r0, =|Image$$RO$$Base|
	mov     pc,r14
	
GetRoEndPtr
	LDR     r0, =|Image$$RO$$Limit|
	mov     pc,r14
	
GetRwBasePtr
	LDR     r0, =|Image$$RW$$Base|  
	mov     pc,r14
	
GetRwEndPtr
	LDR     r0, =|Image$$RW$$Limit|  
	mov     pc,r14
	
GetZiBasePtr
	LDR     r0, =|Image$$ZI$$Base|  
	mov     pc,r14
	
GetZiEndPtr	
	LDR     r0, =|Image$$ZI$$Limit|  
	mov     pc,r14

	END
