/*PROJECT NAME: Assert while compile*/
/*FUNCTION: Assert function is an alert-mechanism that prevent some critical error occur while executing process.*/
/*KEYWORDS: assert.h*/
/*FIRST EDIT: MOUCHEN HUNG 2020.07.16*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../task head/task_head.h"

/* TASK4-Assert while compile */
void task4_main(){
    static int number;
    while(1){
        printf("enter number to try Assert(compile under 5)");
        scanf("%d", &number);
        assert(number < 5);
    }
}
