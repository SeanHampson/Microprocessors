	
	AREA THUMB,CODE,READONLY
	; Functions that are EXPORTed can be used in other modules
	EXPORT asm_delay

asm_delay
	; delay routine in assembler
	; on entry R0 contains a number
	; this function counts down to zero from this number
	; and then returns
	SUBS R0,R0,#1
	BNE	asm_delay
	bx LR
	
	end