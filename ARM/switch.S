/*
 * switch.S - assembly routines for switching trap frames
 */

/*
 * Trap Frame Format
 * WARNING: These values reflect the layout of struct thread_tf. Don't change
 * these values without also updating defs.h.
 */

.file "switch.S"
.text

/* arguments registers (can be clobbered) */
#define _X0	#0
#define _X1	#8
#define _X2	#16
#define _X3	#24
#define _X4	#32
#define _X5	#40

/* temporary registers (can be clobbered) */
#define _X6	#48
#define _X7	#56

/* callee-saved registers (can not be clobbered) */
#define _X19 #64
#define _X29 #72
#define _X12 #80
#define _X13 #88
#define _X14 #96
#define _X15 #104 
#define _X16 #112
#define _X17 #120
#define _X18 #128
#define _X30 #136

/* special-purpose registers */
#define _PC	#144	/* instruction pointer */
#define _SP	#152	/* stack pointer */

#define _X20 #160
#define _X21 #168
#define _X22 #176
#define _X23 #184
#define _X24 #192
#define _X25 #200
#define _X26 #208
#define _X27 #216
#define _X28 #224

/**
 * __jmp_thread - executes a thread from the runtime
 * @tf: the trap frame to restore (%rdi)
 *
 * This low-level variant isn't intended to be called directly.
 * Re-enables preemption, parking the kthread if necessary.
 * Does not return.
 */

.align 16
.globl __jmp_thread
.type __jmp_thread, @function
__jmp_thread:
	/* restore ip and stack */
	
	ldr x3, [x0, _SP]
	mov sp, x3
	ldr x2, [x0, _PC]

	/* restore callee regs */
	ldr x19, [x0, _X19]
	ldr x20, [x0, _X20]
	ldr x21, [x0, _X21]
	ldr x22, [x0, _X22]
	ldr x23, [x0, _X23]
	ldr x24, [x0, _X24]
	ldr x25, [x0, _X25]
	ldr x26, [x0, _X26]
	ldr x27, [x0, _X27]
	ldr x28, [x0, _X28]
	ldr x29, [x0, _X29]
	ldr x30, [x0, _X30]

	/* set first argument (in case new thread) */

	ldr x0, [x0, _X0] /* ARG0 */

	/* jump into trap frame */
	br x2
	nop


/**
 * __jmp_thread_direct - directly switches from one thread to the next
 * @oldtf: the trap frame to save (%rdi)
 * @newtf: the trap frame to restore (%rsi)
 * @thread_running: a pointer to whether the thread is still running (%rdx)
 *
 * This low-level variant isn't intended to be called directly.
 * Re-enables preemption, parking the kthread if necessary.
 * Does return.
 */
.align 16
.globl __jmp_thread_direct
.type __jmp_thread_direct, @function
__jmp_thread_direct:

	/* save ip and stack */
	str x30, [x0, _PC]

	mov x4, sp
	str x4, [x0, _SP]

	/* save callee regs */
	
	str x19, [x0, _X19]
	str x20, [x0, _X20]
	str x21, [x0, _X21]
	str x22, [x0, _X22]
	str x23, [x0, _X23]
	str x24, [x0, _X24]
	str x25, [x0, _X25]
	str x26, [x0, _X26]
	str x27, [x0, _X27]
	str x28, [x0, _X28]
	str x29, [x0, _X29]
	str x30, [x0, _X30]

	/* restore ip and stack */
	ldr x5, [x1, _SP]
	mov sp, x5
	ldr x4, [x1, _PC]
	
	/* clear the stack busy flag */
	mov x7, #0
	str x7, [x2]

	/* restore callee regs */
	ldr x19, [x1, _X19]
	ldr x20, [x1, _X20]
	ldr x21, [x1, _X21]
	ldr x22, [x1, _X22]
	ldr x23, [x1, _X23]
	ldr x24, [x1, _X24]
	ldr x25, [x1, _X25]
	ldr x26, [x1, _X26]
	ldr x27, [x1, _X27]
	ldr x28, [x1, _X28]
	ldr x29, [x1, _X29]
	ldr x30, [x1, _X30]

	/* set first argument (in case new thread) */
	ldr x0, [x1, _X0] /* ARG0 */

	/* jump into trap frame */
	br x4
	nop


