#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#define LOOP 10000

time_t start;
time_t end;


//helper function to read cpu cycle
static inline uint64_t rdtsc(void)
{
	uint64_t a, d;
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return a | (d << 32);

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
    end = nanoseconds();
    
    FILE *f = fopen("//home//blueadmin//avezzu//context-switch-bmarks//x86//result.txt", "w");
    printf("%lu\n", end - start);
    fprintf(f, "%lu\n", end - start);
    fclose(f);

    return 0;
}