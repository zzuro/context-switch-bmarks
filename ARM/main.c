#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#define LOOP 10000


uint64_t start;
uint64_t end;


static inline uint64_t
read_pmccntr(void)
{
	uint64_t val;
	asm volatile("mrs %0, pmccntr_el0" : "=r"(val));
	return val;
}


void workA(){
    uint64_t res = 0;
    uint32_t array[LOOP];

    for(int i = 0; i < LOOP; i++){
        res += array[i];
    }
      
    start = read_pmccntr();
}

int main(){

    threads[0] = (thread*) malloc(sizeof(thread));
    threads[1] = contex_switch(workA, NULL, thread_exit);
    

    //do some work
    uint64_t res = 0;
    uint32_t array[LOOP];

    for(int i = 0; i < LOOP; i++){
        res += array[i];
    }

    //jump to thread and back
    __jmp_thread_direct(&threads[0]->tf, &threads[1]->tf);


    end = read_pmccntr();
   
    FILE *f = fopen("//home//ubuntu//context-switch-bmarks//ARM//result.txt", "w");
    fprintf(f, "%lu\n", end - start);
    fclose(f);

    return 0;
}