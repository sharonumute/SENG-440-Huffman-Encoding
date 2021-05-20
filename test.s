	.arch armv7-a
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"test.c"
	.text
	.comm	a,4,4
	.comm	b,4,4
	.section	.rodata
	.align	2
.LC0:
	.ascii	"a + b = %i\012\000"
	.text
	.align	2
	.global	main
	.arch armv7-a
	.syntax unified
	.arm
	.fpu vfpv3-d16
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	movw	r3, #:lower16:a
	movt	r3, #:upper16:a
	mov	r2, #1
	str	r2, [r3]
	movw	r3, #:lower16:b
	movt	r3, #:upper16:b
	mov	r2, #2
	str	r2, [r3]
	movw	r3, #:lower16:a
	movt	r3, #:upper16:a
	ldr	r2, [r3]
	movw	r3, #:lower16:b
	movt	r3, #:upper16:b
	ldr	r3, [r3]
	add	r3, r2, r3
	mov	r1, r3
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	mov	r3, #0
	mov	r0, r3
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
