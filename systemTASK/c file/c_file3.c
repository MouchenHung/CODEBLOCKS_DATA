#include <stdio.h>
#include <stdlib.h>
#include "../include.h"


void test4(){
    global_v = 100;
    printf("hello\n");
    printf("in greeting, global_v = %d\n", global_v);
}
