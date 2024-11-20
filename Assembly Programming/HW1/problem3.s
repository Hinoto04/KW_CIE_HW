	AREA	ARMex, CODE, READONLY
		ENTRY

start
	MOV r0, #3	; SAVE 3
	MOV r1, #17	; SAVE 17
	
	MUL r2, r0, r1	; 3 * 17
	MUL r2, r1, r0	; 17 * 3
	
done
	MOV r7, #1	; sycall 1
	MOV r0, #0	; return 0
	SVC 0	; execute syscall
	
	END