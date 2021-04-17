; ***************** RAM **********************
	AREA DATA
X	DCD	 0
Y	DCD	 0
Z	DCD	 0
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
     MOVS R0,#9
     LDR  R1,=X
     STR  R0,[R1]

     MOVS R0,#1
     LDR  R1,=Y
     STR  R0,[R1]

     LDR  R0,=X   ; make a pointer to X
     LDR  R0,[R0] ; read X

     LDR  R1,=Y
     LDR  R1,[R1]    
 
     ANDS R1,R0,R1

     LDR R0,=Z
     STR R2,[R0]
	
stop  B stop
; *************************************************
	end