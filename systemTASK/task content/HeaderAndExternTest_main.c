/*PROJECT NAME: Head and Extern Test*/
/*FUNCTION: Header and Extern(won't be declare here but declare other c file which also include this h file) in C language.*/
/*KEYWORDS: header, extern*/
/*FIRST EDIT: MOUCHEN HUNG 2020.07.15*/

#include <stdio.h>
#include <stdlib.h>
#include "../include.h"

#define ADD 0x32
#define a 0x11
#define b 0x22

/* TASK0-Head and Extern Test */
void task0_main(){
    test1();
    test2();
    test3();
    printf("in main, global_v = %d\n", global_v);
    global_v = 10;
    printf("in main, global_v = %d\n", global_v);
    test4();
    printf("in main, global_v = %d\n\n", global_v);

    (*((volatile int*)(a+b))) = ADD;
    printf("check!");

}
