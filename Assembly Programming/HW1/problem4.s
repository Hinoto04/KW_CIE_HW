	AREA	ARMex, CODE, READONLY
		ENTRY

start
	MOV r0, #1	; initial
	MOV r1, #2	; 
	MOV r2, #3	;
	MOV r3, #4	;
	MOV r4, #5	;
	MOV r5, #6	;
	MOV r6, #7	;
	MOV r7, #8	;
	
	LDR sp, STK	; stack pointer set

store_to_stack
	STMDB sp!, {r0-r7}	;

load_from_stack
	LDMIA sp!, {r1}	; r0 to r1
	LDMIA sp!, {r6}	; r1 to r6
	LDMIA sp!, {r0}	; r2 to r0
	LDMIA sp!, {r2}	; r3 to r2
	LDMIA sp!, {r7}	; r4 to r7
	LDMIA sp!, {r3-r5}; r5-7 to r3-5

done
	
	
	MOV r7, #1	; sycall 1
	MOV r0, #0	; return 0
	SVC 0	; execute syscall
	
STK DCD &40400000

	END
		