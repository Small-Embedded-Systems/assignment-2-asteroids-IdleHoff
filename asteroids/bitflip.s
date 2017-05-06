	PRESERVE8			;
						;
	THUMB				;
	AREA 	|.text|, CODE, READONLY		;
	EXPORT flip
	entry
flip	FUNCTION
	PUSH {R1, R2, LR}	; save working registers
	MOV R2, R0			;
	RBIT R1, R2			;
	LSR R0, R1, #24		;
	POP {R1,R2, LR}		; restore saved registers
	BX LR
	ENDFUNC
	END