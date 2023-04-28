#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#define LOOP 10000


time_t start;
time_t end;


static inline uint64_t
read_pmccntr(void)
{
	uint64_t val;
	asm volatile("mrs %0, pmccntr_el0" : "=r"(val));
	return val;
}

static inline time_t nanoseconds(void){

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_nsec;
}

void workA(){
    uint64_t res = 0;
    uint32_t array[LOOP];

    for(int i = 0; i < LOOP; i++){
        res += array[i];
    }
      
    start = nanoseconds();
}

int main(){

    
    threads[0] = (thread*) malloc(sizeof(thread));
    threads[1] = contex_switch(workA, NULL, thread_next);
    

    //do some work
    uint64_t res = 0;
    uint32_t array[LOOP];

    for(int i = 0; i < LOOP; i++){
        res += array[i];
    }

    //jump to thread and back
    __jmp_thread_direct(&threads[0]->tf, &threads[1]->tf);

    end =  nanoseconds();
    printf("%lu\n", end - start );
    FILE *f = fopen("//home//ubuntu//context-switch-bmarks//ARM//result.txt", "w");
    fprintf(f,"%lu\n", end - start);
    fclose(f);

    return 0;
}
