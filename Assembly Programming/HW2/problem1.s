;===================================

    AREA ARMex, CODE, READONLY
        ENTRY

start
    LDR r0, V1; load V1 -> A
    LDR r1, V2; load V2 -> B
    
    ; LOAD SIGN
    MOV r2, r0, LSR #31;
    MOV r3, r1, LSR #31;
    
    ; LOAD EXPONENT
    MOV r4, r0, LSR #23;
    MOV r5, r1, LSR #23;
    AND r4, r4, #255;
    AND r5, r5, #255;
    
    LDR r6, M_FILTER;
    
    ; LOAD MANTISSA
    AND r7, r0, r6;
    AND r8, r1, r6;
    
    NOP;
    
com_exp
    SUBS r9, r4, r5;
    LDRMI r6, NEGATIVE;
    EORMI r9, r9, r6;
    ADDMI r9, r9, #1;
    ; SHIFT NUM = r9
    
    ORR r7, r7, #0x00800000; MANTISSA MSB 1
    ORR r8, r8, #0x00800000;
   
shift_mantissa
    MOVMI r7, r7, LSR r9; SMALL VALUE MANTISSA SHIFT RIGHT
    MOVPL r8, r8, LSR r9;
	
sign_check_a

	CMP r2, #0;
	BNE a_is_minus;

a_is_plus
	CMP r3, #0; CHECK B SIGN
	BEQ add_A_B; BOTH IS PLUS -> SIGN BIT IS 0
	CMP r4, r5;
	BPL sub_A_B; A GE B -> SIGN BIT IS 0
	MOV r12, #0x80000000; B GE A -> SIGN BIT IS 1
	B sub_B_A;

a_is_minus;
	CMP r3, #0;
	MOVNE r12, #0x80000000; BOTH IS MINUS -> SIGN BIT IS 1
	BNE add_A_B;
	CMP r4, r5;
	MOVPL r12, #0x80000000; A GE B -> SIGN BIT IS 1
	BPL sub_A_B;
	B sub_B_A; B GE A -> SIGN BIT IS 0

add_A_B
    ADD r10, r7, r8;
	B normalize;

sub_A_B
	SUB r10, r7, r8;
	B normalize;

sub_B_A
	SUB r10, r8, r7;
	B normalize;

normalize
	CMP r10, #0;
	BEQ done;
	CMP r10, #0x01000000; Overflow 24bit
	BPL normalize_right;
	CMP r10, #0x00800000; Underflow 22bit
	BMI normalize_left;
	B combine;
	
normalize_right
	LSR r10, r10, #1;
	ADD r11, r11, #1;
	CMP r10, #0x01000000;
	BPL normalize_right
	B combine

normalize_left
	LSL r10, r10, #1;
	SUB r11, r11, #1;
	CMP r10, #0x00800000;
	BMI normalize_left;
	B combine;

combine
	MOV r2, #0;
	LDR r6, M_FILTER;
	AND r10, r10, r6;
	ORR r2, r10, r2;
	CMP r4, r5;
	ADDPL r11, r11, r4; EXP NORMALIZE -> +GREATER VALUE EXP
	ADDMI r11, r11, r5;
	ORR r2, r2, r11, LSL #23;
	ORR r2, r2, r12; SIGN BIT SET
	
	NOP;

done
	LDR r1, TEMPADDR;
	STR r2, [r1];
	;SYSCALL
	MOV r7, #1;
	MOV r0, #0;
	SVC 0;

;====================================

TEMPADDR DCD &40000000
V1 DCD 0x42f93cd6    ;124.6188222
V2 DCD 0x420c8e5c    ;35.13902233
M_FILTER DCD 0x007FFFFF;Mantissa FILTER
NEGATIVE DCD 0xFFFFFFFF;7

    END