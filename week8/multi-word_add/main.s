; ***************** RAM **********************
	AREA DATA	
ZLower	DCD 	0
ZUpper	DCD 	0
	
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
	LDR R0,=XLower 	; make pointer to value
	LDR R0,[R0]		; read value
	LDR R1,=YLower	; make pointer to value
	LDR R1,[R1]		; read value
	LDR	R2,=ZLower	; Make pointer 
	SUBS R0,R0,R1	; R0 = R0 + R1
	STR R0,[R2]		; store lower word to memory

	LDR R0,=XUpper 	; make pointer to value
	LDR R0,[R0]		; read value
	LDR R1,=YUpper	; make pointer to value
	LDR R1,[R1]		; read value
	LDR	R2,=ZUpper	; Make pointer 
	SUBS R0,R0,R1	; R0 = R0 + R1 Plus any carry that may be present
	STR R0,[R2]		; store higher word to memory
	
	
stop  B stop
; *************************************************
XLower	DCD 	0x9abcdef1
XUpper	DCD 	0x12345678
YLower	DCD		0x87654321
YUpper	DCD		0x00000001

	end