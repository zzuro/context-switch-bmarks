#include <stdio.h>
#include <stdlib.h>

#include "defs.h"


int a = 3;

void foo(){
   a++;
}

int main(){


    threads[0] = (thread*) malloc(sizeof(thread));
    threads[1] = contex_switch(foo, NULL, thread_next);
    threads[2] = contex_switch(foo, NULL, thread_exit);
    
    __jmp_thread_direct(&threads[0]->tf, &threads[1]->tf);

    printf("done, a: %d\n", a);
    return 0;
}