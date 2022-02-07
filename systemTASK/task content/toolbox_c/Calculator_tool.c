#include <stdio.h>
#include <stdlib.h>
#include "../toolbox_h/tool_head.h"

void task2_cal_operator(int *cur, int num, int mode){
    switch(mode){
    case 0: //plus
        *cur+=num;
        break;

    case 1: //minus
        *cur-=num;
        break;

    case 2: //mult
        *cur*=num;
        break;

    case 3:
        *cur/=num;
        break;

    default:
        printf("no such mode!\n");
        break;
    }

}

void task2_cal_show(int *cur){
    printf("-->current sum = %d\n", *cur);
}

