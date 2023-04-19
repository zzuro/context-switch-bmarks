#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#define LOOP 10000

uint64_t start;
uint64_t end;


//helper function to read process cylcle
static inline uint64_t rdtsc(void)
{
	uint64_t a, d;
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return a | (d << 32);

}

void workA(){
    uint64_t res = 0;
    uint32_t array[LOOP];

    for(int i = 0; i < LOOP; i++){
        res += array[i];
    }
    
    
    start = rdtsc();
}

int main(){



    threads[0] = (thread*) malloc(sizeof(thread));
    threads[1] = contex_switch(workA, NULL, thread_exit);
    

    uint64_t res = 0;
    uint32_t array[LOOP];

    for(int i = 0; i < LOOP; i++){
        res += array[i];
    }

    __jmp_thread_direct(&threads[0]->tf, &threads[1]->tf);
    end = rdtsc();

    printf("time: %lu\n", end - start);
    return 0;
}