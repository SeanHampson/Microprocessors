	
	AREA THUMB,CODE,READONLY
	; Functions that are EXPORTed can be used in other modules
	EXPORT asm_delay
	EXPORT asm_setBit
	EXPORT asm_clearBit

asm_delay
	; delay routine in assembler
	; on entry R0 contains a number
	; this function counts down to zero from this number
	; and then returns
	SUBS R0,R0,#1
	BNE	asm_delay
	bx LR
	
; void asm_setBit( volatile uint32_t *dest, uint32_t Mask);
; *dest = *dest | (1u << Mask);
asm_setBit
	; *dest = r0
	; Mask = r1
	PUSH {R2-R3}
	LDR R2,[R0]		; Contents of dest = R2
	MOVS R3,#1		; R3 = 1u
	LSLS R3,R3,R1	; R3 = (1u << Mask)
	ORRS R2,R2,R3	; R2 = *dest | (lu << Mask)
	STR R2,[R0]		; *dest = *dest | (lu << Mask)
	POP {R2-R3}
	bx LR
	
; void asm_clearBit( volatile uint32_t *dest, uint32_t Mask);
; *dest = *dest & ~(1u << Mask);
asm_clearBit
	; *dest = R0
	; Mask = R1
	PUSH {R2-R3}
	LDR R2,[R0]		; Contents of dest = R2
	MOVS R3,#1		; R3 = 1u
	LSLS R3,R3,R1	; R3 = (1u << Mask)
	MVNS R3,R3		; R3 = ~(1u << Mask)
	ANDS R3,R2,R3	; R3 = *dest & ~(1u << Mask)
	STR R3,[R0]		; *dest = *dest & ~(1u << Mask);
	POP {R2-R3}
	bx LR
	
	end