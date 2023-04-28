#ifndef _DEFS_H__
#define _DEFS_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define RUNTIME_STACK_SIZE	256 * 1024
#define RUNTIME_GUARD_SIZE	256 * 1024

#define N 4

struct thread_tf {
	/* argument registers, can be clobbered by callee */
	uint64_t x0; /* first argument */
	uint64_t x1;
	uint64_t x2;
	uint64_t x3;
	uint64_t x4;
	uint64_t x5;
	uint64_t x6;
	uint64_t x7;


	//maybe I have to store here also the other register
	uint64_t x19; //rbx
	uint64_t x29; //rbp
	uint64_t x12;
	uint64_t x13;
	uint64_t x14;
	uint64_t x15;

	uint64_t x16;
	uint64_t x17;
	uint64_t x18;

	uint64_t x30;

	/* special-purpose registers */
	uint64_t pc;	/* instruction pointer */
	uint64_t sp;	/* stack pointer */

	/*additional register used with O3*/
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
};


#define ARG0(tf)        ((tf)->x0)
#define ARG1(tf)        ((tf)->x1)
#define ARG2(tf)        ((tf)->x2)
#define ARG3(tf)        ((tf)->x3)
#define ARG4(tf)        ((tf)->x4)
#define ARG5(tf)        ((tf)->x5)


#define STACK_PTR_SIZE	(RUNTIME_STACK_SIZE / sizeof(uintptr_t))

typedef struct thread {
	struct thread_tf	tf;     //reg
	uintptr_t*	        stack;  //stack
}thread;


thread* threads[N];

/* assembly helper routines from switch.S */
extern void __jmp_thread(struct thread_tf *tf);
extern void __jmp_thread_direct(struct thread_tf *oldtf,
				struct thread_tf *newtf);
/*
void thread_exit(){
    __jmp_thread(&threads[0]->tf);
}
*/
void thread_next(){
	__jmp_thread_direct(&threads[1]->tf, &threads[0]->tf);
}

thread* contex_switch(void (*fn)(void*), void* arg, void (*th_exit)(void)){
    thread* th = (thread*) malloc(sizeof(thread));
	th->stack = malloc(STACK_PTR_SIZE * sizeof(uintptr_t));

    th->stack[STACK_PTR_SIZE - 2] = (uintptr_t)th_exit;
    th->tf.sp = (uintptr_t)&th->stack[STACK_PTR_SIZE - 2];

	th->tf.x30 = (uintptr_t)th_exit;
	th->tf.x0 = (uint64_t)arg;
	th->tf.x29 = (uint64_t)0; /* just in case base pointers are enabled */
	th->tf.pc = (uint64_t)fn;
	
    return th;
}



#endif
