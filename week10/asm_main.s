; ***************** RAM **********************
		AREA DATA
target SPACE 20
; *************************************************

; ***************** ROM **********************

; The following symols are in the CODE section (ROM,Executable, readonly)
    AREA THUMB,CODE,READONLY
; EXPORTED Symbols can be linked against
    EXPORT Reset_Handler
    EXPORT __Vectors
; Minimal interrupt vector table follows
; First entry is initial stack pointer (top of stack)
; second entry is the address of the reset handler
__Vectors
    DCD 0x20000000+8192
    DCD Reset_Handler 

; 'Main' program goes here
; Calling convention : R0 used to pass data to a function
Reset_Handler
	LDR R0,=target		; Destination Address
	LDR R1,=source		; Source Address
	LDR R2,=length		; Length Address
	BL strncpy			; Function Call
stop  B stop
; incoming parameter in R0 i.e. the address of the string
; result should be return in R0
strncpy
	PUSH {R0-R2}		; Push R0 & R1 onto stack
	MOVS R4,#0			; counter = 0
strncpy_loop
	LDRB R3,[R1]		; *src into R2
	CMP R3,#0			; Compare R2 to 0
	BEQ strncpy_exit	; If R2 == 0 then exit loop
	
	LDRB R5,[R2]		; *length i.e. n goes into R5
	CMP R4,R5			; Compare counter to n
	BEQ strncpy_exit	; If counter == n then exit
	
	LDRB R3,[R1]		; *src into R3
	STRB R3,[R0]		; Assign *dest to R3
	ADDS R0,R0,#1		; dest++
	ADDS R1,R1,#1		; src++
	ADDS R4,R4,#1		; counter ++
	B strncpy_loop
strncpy_exit
	MOVS R4,#0			; Counter = 0
	STRB R4,[R0]		; Assign 0 to dest	
	POP {R0-R2}			; Pop R0 & R1 off the stack
	BX LR

; *************************************************
; Constant data is stored in Flash ROM
source DCB "Hello World\0"
length DCD 2
	end