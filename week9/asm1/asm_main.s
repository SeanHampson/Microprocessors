; ***************** RAM **********************
	AREA DATA
X	SPACE 10
I	DCD 0
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
	LDR R0,=X			; Load address of X
	LDR R1,=I			; Load address of Index
FOR
	LDR R2,[R1]			; Load index counter into R2
	CMP R2,#10			; Index counter compared to 10
	BGE stop			; stop if index >= 10
	
	MOVS R3,#0	
	STRB R3,[R0,R2]		; Set contents to 0
	
	ADDS R2,R2,#1		; Increment index counter
	STR R2,[R1]			; Store index counter
	B FOR
stop  B stop
; *************************************************
	end
