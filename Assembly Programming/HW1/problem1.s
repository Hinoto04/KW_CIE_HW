	AREA	ARMex, CODe, READONLY
			ENTRY
			
start
	MOV r0, #10	; factorial N < N value
	ADD r0, #1	; because of factorial logic in down, add 1 to N
	MOV r1, #1	; factorial save Value
	MOV r3, #1	; non-immediate 1 value
	MOV r4, #0	; LSL ADD VALUE 0 SET
	BL lsl_factorial_loop	;to lsl_factorial_loop

lsl_factorial_loop
	CMP r4, #0	; if r4 is not zero
	MOVNE r1, r4	; update value factorial save value
	SUB r0, r0, #1	; r0 - 1
	CMP r0, #0	; if r0 -> stop loop
	BEQ done	; JUMP TO done
	B lsl_factorial	; else to factorial start
	
lsl_factorial
	MOV r2, #4	; LSL factorial repeation FROM 4th bit
	MOV r4, #0	; LSL ADD VALUE 0 SET
	B lsl_addloop

lsl_addloop
	ANDS r5, r0, r3, LSL r2	; r2th BIT is 1?
	ADDNE r4, r4, r1, LSL r2	; IF r2th BIT is NOT 0
	SUB r2, r2, #1	; LSL BIT -1
	CMP r2, #0	; IF r2 is 0
	BMI lsl_factorial_loop	; TO FACTORIAL_LOOP
	B lsl_addloop	; OR LOOP IS ADDING
	
done
	LDR r6, =0x40000000	;
	STR r1, [r6]	; STORE VALUE
	
	MOV r7, #1	; sycall 1
	MOV r0, #0	; return 0
	SVC 0		; execute syscall

	END