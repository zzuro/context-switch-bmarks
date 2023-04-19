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
	uint64_t rdi; /* first argument */
	uint64_t rsi;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t r8;
	uint64_t r9;
	uint64_t r10;
	uint64_t r11;

	/* callee-saved registers */
	uint64_t rbx;
	uint64_t rbp;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;

	/* special-purpose registers */
	uint64_t rax;	/* holds return value */
	uint64_t rip;	/* instruction pointer */
	uint64_t rsp;	/* stack pointer */
};

#define ARG0(tf)        ((tf)->rdi)
#define ARG1(tf)        ((tf)->rsi)
#define ARG2(tf)        ((tf)->rdx)
#define ARG3(tf)        ((tf)->rcx)
#define ARG4(tf)        ((tf)->r8)
#define ARG5(tf)        ((tf)->r9)


#define STACK_PTR_SIZE	(RUNTIME_STACK_SIZE / sizeof(uintptr_t))

typedef struct thread {
	struct thread_tf	tf;                     //reg
	uintptr_t	        stack[STACK_PTR_SIZE];  //stack
    void (*fn)(void*);                          //function to execute
}thread;


thread* threads[N];

/* assembly helper routines from switch.S */
extern void __jmp_thread(struct thread_tf *tf);
extern void __jmp_thread_direct(struct thread_tf *oldtf,
				struct thread_tf *newtf);

void thread_exit(){
    __jmp_thread(&threads[0]->tf);
}

void thread_next(){
	__jmp_thread_direct(&threads[1]->tf, &threads[2]->tf);
}

thread* contex_switch(void (*fn)(void*), void* arg, void (*th_exit)(void)){
    thread* th = (thread*) malloc(sizeof(thread));
    th->fn = fn;
    
    th->stack[STACK_PTR_SIZE - 1] = (uintptr_t)th_exit;
    th->tf.rsp = (uintptr_t)&th->stack[STACK_PTR_SIZE - 1];

	th->tf.rdi = (uint64_t)arg;
	th->tf.rbp = (uint64_t)0; 
	th->tf.rip = (uint64_t)fn;
    return th;
}



#endif