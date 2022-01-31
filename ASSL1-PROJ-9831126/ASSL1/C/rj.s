PIO_PER equ  0x400E0E00	
PIO_OER equ  0x400E0E10 
PIO_SODR equ 0x400E0E30
PIO_CODR equ 0x400E0E34
PIO_SPDR equ 0x400E0E3C
		
	AREA myCode, CODE, READONLY
	export __main
	ENTRY

__main

	bl enable_pio1
	bl enable_pio2
	bl enable_pio3
	
begin

	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2,#2_1000
	beq loop
	b begin
	
	
finish

	bl led_off1
	bl led_off2
	bl led_off3
	b begin

loop
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	;miniLoop1
	bl led_on1
	bl led_on2
	bl led_on3
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl led_off1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	;miniLoop2
	bl led_off2
	bl led_on1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl led_off1
	bl led_off2
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	;miniLoop3
	bl led_on2
	bl led_on1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl led_off1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	;miniLoop4
	bl led_off2
	bl led_on2
	bl led_on1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl led_off1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	;miniLoop5
	bl led_on2
	bl led_on1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl led_off1
	bl led_off3
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	;miniLoop6
	bl led_off2
	bl led_on1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl led_off1
	
	bl delay
	ldr r1, =PIO_SPDR
	ldr r2, [r1]
	cmp r2, #2_10000
	beq finish
	
	bl loop

enable_pio1

	mov r4, #2_1
	ldr r5,=PIO_PER
	str r4, [r5]
	ldr r5,=PIO_OER
	str r4, [r5]
	bx lr
	
enable_pio2

	mov r4, #2_10
	ldr r5,=PIO_PER
	str r4, [r5]	
	ldr r5,=PIO_OER
	str r4, [r5]
	bx lr
	
enable_pio3

	mov r4, #2_100	
	ldr r5,=PIO_PER
	str r4, [r5]
	ldr r5,=PIO_OER
	str r4, [r5]
	bx lr
	
led_on1

	mov r4, #2_1
	ldr r5,=PIO_SODR
	str r4, [r5]
	bx lr
	
led_on2

	mov r4, #2_10
	ldr r5,=PIO_SODR
	str r4, [r5]
	bx lr
	
led_on3

	mov r4, #2_100
	ldr r5,=PIO_SODR
	str r4, [r5]	
	bx lr
	
led_off1

	mov r4, #2_1	
	ldr r5,=PIO_CODR
	str r4, [r5]
	bx lr
	
led_off2

	mov r4, #2_10	
	ldr r5,=PIO_CODR
	str r4, [r5]
	bx lr

led_off3

	mov r4, #2_100	
	ldr r5,=PIO_CODR
	str r4, [r5]
	bx lr
	
delay

	mov r4, #0
	ldr r5, =0x00A0000
	
loop_delay

	ADD r4,r4,#1
	cmp r4,r5
	bne loop_delay
	bx lr
	end