	AREA	ARMex, CODE, READONLY;
		ENTRY

start
	MOV r0, #10	; N Value
	MOV r1, #1	; Save Value
	LDR sp, STACKADDR	;STACK ADDR LOADING
	
	BL recursion	;
	B done	;

recursion
	CMP r0, #1	;
	MOVLE r2, #1	; IF LESS THAN 1 -> RETURN 1
	MOVLE r1, r2	; RETURN
	BXLE lr;
	
	STMDB sp!, {r0, lr}	; STORE NOW N VALUE
	SUB r0, r0, #1	; N - 1
	BL recursion	; call recursion
	LDMIA sp!, {r0, lr}	; LOAD NOW N VALUE
	MUL r2, r1, r0	; N * (returned recursion value)
	MOV r1, r2;
	BX lr;

done
	LDR r6, =0x40000000	;
	STR r1, [r6]	; save final value

	MOV r7, #1	; sycall 1
	MOV r0, #0	; return 0
	SVC 0	; execute syscall
	
STACKADDR DCD &40400000
	
	END