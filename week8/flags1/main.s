; ***************** RAM **********************
	AREA DATA	

	
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
Reset_Handler
	MOVS R0,#3
	MOVS R1,#0
DO
	SUBS R0,R0,#1
	ADDS R1,R1,R0
	CMP R0,#0
	BHI DO
	BLS stop
stop  B stop
; *************************************************

	end