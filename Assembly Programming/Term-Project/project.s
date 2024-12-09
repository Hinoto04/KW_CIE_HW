    AREA    TermProject2024, CODE, READONLY
    
; Constants
IMG_WIDTH    EQU     20
IMG_HEIGHT   EQU     20
NEW_WIDTH    EQU     80
NEW_HEIGHT   EQU     80

    ENTRY
    
main
;@@@@@@@@ ADD, SUB, MULTIPLY TEST @@@@@@@@@
    ; YOUR CODE HERE
	;LDR		r1, =V1
	;LDR		r1, [r1]
	;LDR		r2, =V2
	;LDR		r2, [r2]
	;B multiply_floats;

;V1 			DCD 	0x406ccccd    ;
;V2				DCD 	0x40a9999a    ;
;@@@@@@@@ ADD, SUB, MULTIPLY TEST @@@@@@@@@

;@@@@@@@@ IEEE 754 Version @@@@@@@@
    ; Load base addresses
    LDR     R9, =source_data     ; Source image
    LDR     R8, =ResultBuffer    ; Destination buffer

	; Initialize loop counters
    MOV     R6, #0              ; i counter
    MOV     R7, #0              ; j counter
	
	; 20*20 Loop
bigloop_i
	CMP		R6, #19				; 1 ~ 19 no padding
	BEQ		bottom_padding
	
	MOV		r7, #0
bigloop_j
	CMP		R7, #19				; 1 ~ 19 no padding
	BEQ		right_padding
	
	MOV 	r0, r9		; V1
	MOV		r1, r8		; Save Address
	
	LDR		r2, [R0], #4		; R2 = V1
	LDR		r3, [R0], #76		; R3 = V2
	LDR		r4, [R0], #4		; R4 = V3
	LDR		r5, [R0]			; R5 = V4
	
	BL		smallloop
	
	ADD		r9, r9, #4
	ADD		r8, r8, #16
	
	ADD		r7, r7, #1
	B		bigloop_j
	
right_padding

	MOV		r2, r3			; V1 = V2
	MOV		r4, r5			; V3 = V4
	ADD		r9, r9, #4
	
	MOV		r1, r8		; Save Address
	BL smallloop
	
	ADD		r8, r8, #16
	ADD		r8, r8, #960
	ADD		r6, r6, #1
	B		bigloop_i

bottom_padding
	MOV		r6, #0
	
bp_i
	CMP		R6, #19				; 1 ~ 19
	BEQ		b_right_padding
	
	MOV 	r0, r9		; V1
	MOV		r1, r8		; Save Address
	
	LDR		r2, [R0], #4		; R2 = V1
	LDR		r3, [R0], #76		; R3 = V2
	MOV		r4, r2				; R4 = V3
	MOV		r5, r3				; R5 = V4
	
	BL		smallloop
	
	ADD		r9, r9, #4
	ADD		r8, r8, #16
	
	ADD		r6, r6, #1
	B		bp_i

b_right_padding
	MOV		r2, r3
	MOV		r4, r5
	ADD		r9, r9, #4
	MOV		r1, r8
	BL		smallloop
	B		end_program

smallloop
	; R2 = V1; R3 = V2; R4 = V3; R5 = V4
	; R1 -> Save Address

	PUSH	{R2-R12, LR}
	
	MOV		R12, R1				; Save Address to R12
	
	MOV		r6, #0
	
smallloop_i
	CMP		r6, #16
	BEQ		smallloop_end

	MOV		r7, #0
	
smallloop_j
	CMP		r7, #16
	BEQ		smallloop_i_end
	
	; (1-i)([1-j]V1 + jV2) + i([1-j]V3 + jV4)
	; [1-j]
	LDR		r8, =rquarter
	
	; [1-j]V1
	LDR		r1, [r8, r7]
	MOV		r0, r2		; V1
	BL		multiply_floats
	MOV		r9, r0		; Save to r9
	
	; [1-j]V3
	MOV		r0, r4		; V3
	BL		multiply_floats
	MOV		r10, r0		; Save to r10
	
	; jV2
	LDR		r8, =quarter
	
	LDR		r0, [r8, r7]
	MOV		r1, r3		; V2
	BL		multiply_floats
	
	; add [1-j]V1, jV2
	MOV		r1, r9
	BL		add_floats
	
	; addition result to R11
	MOV		r11, r0
	
	; jV4
	LDR		r0, [r8, r7]
	MOV		r1, r5		; V4
	BL		multiply_floats
	
	; add [1-j]V3, jV4
	MOV		r1, r10
	BL		add_floats
	
	; i * ([1-j]V3 + jV4)
	LDR		r1, [r8, r6]
	BL		multiply_floats
	
	; result to R10
	MOV		r10, r0
	
	; [1-i]
	LDR		r8, =rquarter
	LDR		r0, [r8, r6]
	
	MOV		r1, r11		; [1-j]V1 + jV2
	
	BL		multiply_floats
	
	; (1-i)([1-j]V1 + jV2) + i([1-j]V3 + jV4)
	MOV		r1, r10
	BL		add_floats
	
	; r0 is result value
	; SAVE the Value
	STR		r0, [r12], #4
	
	ADD		r7, r7, #4
	B		smallloop_j

smallloop_i_end
	
	ADD		r12, r12, #304

	ADD		r6, r6, #4
	B		smallloop_i

smallloop_end
	POP		{R2-R12, PC}
;@@@@@@@@ IEEE 754 Version @@@@@@@@


;@@@@@@@@ Integer Version @@@@@@@
;	LDR		R4, =source_data
;	LDR		R5, Buffer
;   LDR		r3, temp_data		; temp save data
;	
;   ; Initialize loop counters
;	
;   MOV     R6, #0              ; i counter
;   MOV     R7, #0              ; j counter
;	
;	; Load constants from memory
;   LDR     R12, =mantissa_mask     ; Load address of mantissa mask
;   LDR     R12, [R12]             ; Load actual value
;	
;toInt ; Float to Int
;	CMP		R6, #400
;	BEQ		pre_interpolation		;
;	
;	LDR		r0, [r4], #4		; Load and R4 += 4
;	
;	MOV		r1, r0, LSR #23		; Copy Exponent Bits <- Sign Bit is Always 0
;	SUB		r1, r1, #127		; Remove Exponent Bias
;	
;	AND		r2, r0, r12			; Copy Fraction Bits
;	ORR		r2, r2, #0x800000	; To Mantissa
;	RSB		r1, r1, #23			; 23 - r1
;	LSR		r2, r2, r1			; To Int
;	
;	STRB	r2, [r3], #1		; Store and R3 += 1
;	
;	ADD		R6, R6, #1
;	B toInt

;pre_interpolation
;	LDR 	r3, temp_data		; temp data start address

;interpolation_start
;	LDRB	r8, [r3]			; V1
;	LDRB	r10, [r3, #20]		; V3
;	MOV		r0, #0				; row repeation reset

;interpolation_position
;	CMP		r0, #19				;
;	BEQ		padding_and_pos_set
;	
;	LDRB	r9,	[r3, #1]! 		; V2
;	LDRB	r11, [r3, #20]		; V4
;	
;	MOV		r6, #0				; i = 0
;	
;	ADD		r0, r0, #1			; r0 ++
;	
;interpolation_i
;	CMP		r6, #4				; Loop i
;	BEQ		interpolation_position_end
;	
;	MOV		r7, #0				; j = 0
;	
;interpolation_j
;	CMP		r7, #4				; Loop j
;	BEQ		interpolation_i_end
;	
;	; r8 ~ r11 => V1 ~ V4
;	; Reserved Register : r3 = data, r5 = resultbuf, r6 = i, r7 = j, r0 = 20*20 count
;	; (4-i)( (4-j)V1 + jV2 ) + i( (4-j)V3 + jV4 )
;	MOV		r1, #0				; Local Matrix [i][j]
;	RSB		r2, r7, #4			; 4-j
;	MOV		r4, #0				; Temp Value 0
;	
;	MUL		r12, r2, r10		; r4 += (4-j)V3
;	ADD		r4, r4, r12
;	
;	MUL		r12, r7, r11		; r4 += jV4
;	ADD		r4, r4, r12
;	
;	MUL		r1, r4, r6			; r1 = i( (4-j)V3 + jV4 )
;	
;	MOV		r4, #0				; Temp Value 0
;	MUL		r12, r2, r8			; (4-j)V1 => 4-j don't need
;	ADD		r4, r4, r12			; r4 += (4-j)V1
;	
;	MUL		r12, r7, r9			; r4 += jV2
;	ADD		r4, r4, r12
;	
;	RSB		r2, r6, #4			; r2 = 4-i
;	MUL		r12, r4, r2			; r12 = (4-i)( (4-j)V1 + jV2 )
;	ADD		r1, r1, r12			; r1 += r12
;	
;	MOV		r1, r1, LSR #4		; r1 >> 4 == r1/16
;	
;	; 80*80
;	STRB	r1, [r5], #1		; Save to R5
;	
;	ADD		r7, r7, #1			; j++
;	B		interpolation_j

;interpolation_i_end
;	
;	ADD		r6, r6, #1			; i++
;	ADD		r5, r5, #76
;	
;	; ResultBuf Goto Next Column
;	B		interpolation_i

;interpolation_position_end
;	;Save Pos Set
;	
;	MOV		r8, r9				; V2 -> V1
;	MOV		r10, r11			; V4 -> V3
;	
;	SUB 	r5, r5, #316;
;	B		interpolation_position
;	
;padding_and_pos_set
;	;padding
;	MOV		r1, #0
;	MOV		r2, #0
;	MOV		r4, #0
;	MOV		r6, #0
;	
;padding_i
;	CMP		r6, #4
;	BEQ		padding_i_end
;	
;	;(4-i)V2
;	RSB		r2, r6, #4
;	MUL		r1, r2, r9
;	
;	; iV4
;	MUL		r4, r6, r11
;	ADD		r1, r1, r4
;	
;	MOV		r1, r1, LSR #2		; r1 >> 2 == r1 / 4
;	
;	MOV		r12, #0
;	ADD		r12, r12, r1
;	ADD		r12, r12, r1, LSL #8
;	ADD		r12, r12, r1, LSL #16
;	ADD		r12, r12, r1, LSL #24
;	
;	STR		r12, [r5], #80
;	
;	ADD		r6, r6, #1
;	B		padding_i

;padding_i_end
;	SUB		r5, r5, #76
;	ADD		r3, r3, #1
;	;Is End?
;	LDR		r6, temp_data
;	ADD		r6, r6, #380
;	CMP		r3, r6				; is now is last row
;	BEQ 	pre_bottom_padding
;	B		interpolation_start

;pre_bottom_padding
;	MOV		r0, #0
;	
;bottom_padding
;	CMP		r0, #19
;	BEQ		last_box
;	
;	LDRB	r9, [r3], #1
;	
;	MOV		r2, #0
;	MOV		r4, #0
;	MOV		r6, #0
;	
;bp_i
;	CMP		r6, #4
;	BEQ		bottom_padding_end
;	
;	MOV		r1, #0
;	
;	;(4-i)V1
;	RSB 	r2, r6, #4
;	MUL		r1, r2, r8
;	
;	; iV2
;	MUL		r4, r6, r9
;	ADD		r1, r1, r4
;	
;	MOV		r1, r1, LSR #2
;	
;	MOV		r7, #0

;bp_j
;	CMP		r7, #4
;	BEQ		bp_i_end
;	
;	STRB	r1, [r5], #80
;	ADD		r7, r7, #1
;	B		bp_j

;bp_i_end
;	SUB 	r5, r5, #316;
;	SUB		r5, r5, #3;
;	ADD		r6, r6, #1
;	B		bp_i

;bottom_padding_end
;	ADD		r0, r0, #1
;	MOV 	r8, r9
;	B		bottom_padding

;last_box
;	MOV		r1, #0
;	ADD		r1, r1, r9
;	ADD		r1, r1, r9, LSL #8
;	ADD		r1, r1, r9, LSL #16
;	ADD		r1, r1, r9, LSL #24
;	
;	STR		r1, [r5], #80
;	STR		r1, [r5], #80
;	STR		r1, [r5], #80
;	STR		r1, [r5]

;	NOP;

;toWord
;	LDR 	r6, Buffer
;	LDR		r9, =ResultBuffer
;	
;	MOV		r10, #0 

;loop
;	CMP		r10, #6400
;	BEQ		end_program
;	
;	LDRB	r0, [r6], #1;
;	
;	CMP		r0, #0
;	MOVEQ	r1, #0
;	BEQ		save_float
;	
;	CLZ     r2, r0
;    RSB     r3, r2, #31
;	
;	ADD		r4, r3, #127
;	LSL		r4, r4, #23
;	
;	MOV		r5, r0
;	MOV		r8, #1
;	LSL		r8, r8, r3
;	BIC		r5, r5, r8
;	RSB		r7, r3, #23
;	LSL		r5, r5, r7
;	
;	MOV 	r1, #0
;	ORR		r1, r1, r4
;	ORR		r1, r1, r5

;save_float
;	STR		r1, [r9], #4
;	ADD		r10, r10, #1
;	
;	B loop
;@@@@@@@ Integer Version End @@@@@@@

; Floating point multiplication
multiply_floats
    PUSH    {R2-R12, LR}
	
	CMP		r0, #0
	BEQ		multiply_bx
	
	CMP		r1, #0
	MOVEQ	r0, #0
	BEQ		multiply_bx
    
    ; Load constants from memory
    LDR     R12, =mantissa_mask     ; Load address of mantissa mask
    LDR     R12, [R12]             ; Load actual value
    
    ; YOUR CODE HERE
	MOV		r4, r0, LSR #31		; Sign Bit of V1
	MOV		r5, r1, LSR #31		; Sign Bit of V2
	
	MOV		r6, r0, LSR #23		; Exponent Bits of V1
	MOV 	r7, r1, LSR #23		; Exponent Bits of V2
	AND		r6, r6, #255		; Exponent Filter (Remove Sign Bit)
	AND		r7, r7, #255
	
	AND		r9, r0, r12			; Fraction Bits of V1
	AND		r10, r1, r12		; Fraction Bits of V2
	ORR		r9, r9, #0x800000	; Mantissa Bit add (1.???)
	ORR		r10, r10, #0x800000
	
	MOV		r0, #0				; Reset R0 << Because R0 is Return Value
	
	EOR		r4, r4, r5			; Sign Bit is XOR Value
	ORR		r0, r4, LSL #31		; Set Sign Bit of Result
	
	ADD		r6, r6, r7			; add Exponent Bits
	SUB		r6, r6, #127		; (E0 + 127) + (E1 + 127) - 127 = E0 + E1 + 127
	
	UMULL	r4, r5, r9, r10		; 24-bit x 24-bit = 48bit > 32bit -> UMULL r5:r4

	CMP		r5, #0x00008000
	ADDPL	r6, r6, #1
	MOVMI	r5, r5, LSL #1
	ORRMI	r5, r5, r4, LSR #31
	
	MOV 	r5, r5, LSL #8
	ORR		r5, r5, r4, LSR #24

multiply_done
	AND		r5, r5, r12
	ORR		r0, r0, r5
	ORR		r0, r0, r6, LSL #23;

multiply_bx
    POP     {R2-R12, PC}

; IEEE 754 Addition
; arg values is in R1, R2 (R1 + R2)
; return value move to R0
add_floats
    PUSH    {R2-R12, LR}
	
	CMP		r0, #0
	MOVEQ	r0, r1
	BEQ		add_bx
	
	CMP		r1, #0
	BEQ		add_bx
    
    ; Extract mantissas and add implied 1
    LDR     R8, =mantissa_mask
    LDR     R8, [R8]            ; Load mantissa mask

    ; YOUR CODE HERE
	MOV		r4, r0, LSR #31		; Sign Bit of V1
	MOV		r5, r1, LSR #31		; Sign Bit of V2
	
	MOV		r6, r0, LSR #23		; Exponent Bits of V1
	MOV 	r7, r1, LSR #23		; Exponent Bits of V2
	AND		r6, r6, #255		; Exponent Filter (Remove Sign Bit)
	AND		r7, r7, #255
	
	AND		r9, r0, r8			; Fraction Bits of V1
	AND		r10, r1, r8			; Fraction Bits of V2
	ORR		r9, r9, #0x800000	; Mantissa Bit add (1.???)
	ORR		r10, r10, #0x800000
	
	CMP		r6, r7				; Compare V1 > V2
	BGE		calculate
	
	; IF V1 < V2 -> Swap Values -> Always V1 GE V2
	MOV		r11, r9; Mantissa
	MOV		r9, r10;
	MOV		r10, r11;
	
	MOV 	r11, r6; Exponent
	MOV 	r6, r7;
	MOV 	r7, r11;

	MOV 	r11, r4; Sign
	MOV 	r4, r5;
	MOV 	r5, r11;
	
calculate ; V1 Always GE V2
	MOV 	r0, #0
	ORR		r0, r4, LSL #31		; Set Sign Bit
	SUB		r11, r6, r7			; Align Exponent
	MOV 	r10, r10, LSR r11	; LSR Mantissa of Small Value
	
	CMP		r4, r5				; Compare Sign Bit
	
	; IF Same -> Add
	ADDEQ	r11, r9, r10;
	
	; IF Diff -> Subtract
	SUBNE	r11, r9, r10;
	
	CMP 	r11, #0				; IF r11 is 0
	BEQ 	add_done			; Normalize isn't needed;
	
normalize_right
	CMP		r11, #0x01000000	; ADDS but don't save result to register
	BMI		normalize_left		; IF don't need to right -> left
	MOV		r11, r11, LSR #1	; LSR Mantissa
	ADD		r6, r6, #1			; Increase Exp
	B		normalize_right		; repeat

normalize_left
	CMP		r11, #0x00800000	; 
	BPL		add_done			; IF don't need to left -> done
	MOV		r11, r11, LSL #1	; LSL Mantissa
	SUB		r6, r6, #1;			; Decrease Exp
	B		normalize_left
    
add_done
	AND		r11, r11, r8		; Remove 24th bit
	ORR		r0, r0, r11			; Save Fraction Bits
	
	ORR		r0, r0, r6, LSL #23	; Save Exponent Bits

add_bx
    POP     {R2-R12, PC}

; IEEE 754 Subtraction
subtract_floats
    PUSH    {R2-R12, LR}
	
	; R0 - R1 -> Change R1 Sign Bit
	MOV		r4, #1;
	LSL		r4, r4, #31;
	EOR		r1, r1, r4;
    
    ; Use addition routine
    BL      add_floats
    
    POP     {R2-R12, PC}

; #########################
; DO NOT MODIFY end_program
; #########################
end_program
    MOV     R0, #0             ; Return 0
    MOV     R7, #0x11          ; SWI exit
    SWI     0                   ; Exit program and return 0
; #########################
; DO NOT MODIFY end_program
; #########################

; YOUR CODE HERE

    AREA    ROData, DATA, READONLY
mantissa_mask	DCD     0x007FFFFF          ; Store the large constant here
infinity_const 	DCD		0x7F800000
implied_one     DCD     0x00800000
temp_data 		DCD 	0xFF000000
Buffer			DCD		0xFFF00000
quarter			DCD		0x00000000, 0x3E800000, 0x3F000000, 0x3F400000
rquarter		DCD		0x3F800000, 0x3F400000, 0x3F000000, 0x3E800000

source_data
    INCLUDE data\downsampled\0.txt   ; Include the image data

    AREA    RWData, DATA, READWRITE
ResultBuffer
    SPACE   NEW_WIDTH * NEW_HEIGHT * 4   ; Space for 80x80 result
    
    END
