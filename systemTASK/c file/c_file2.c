#include <stdio.h>
#include <stdlib.h>
#include "../include.h"

int global_v = 8;
void test3(){
    printf("hello\n");
    printf("in greeting, global_v = %d\n", global_v);
}
