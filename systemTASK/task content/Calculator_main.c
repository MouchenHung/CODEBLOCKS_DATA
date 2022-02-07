#include <stdio.h>
#include <stdlib.h>
#include "toolbox_h/tool_head.h"
#include "../task head/task_head.h"


/* TASK2-Calculator */
void task2_main(){
    static int zero=0;
    int *cur = &zero;

    enum cul_mode{
        PLUS,
        MINUS,
        MULT,
        DEVIDE
    };

    task2_cal_operator(cur, 20, PLUS);
    task2_cal_show(cur);
    task2_cal_operator(cur, 5, MINUS);
    task2_cal_show(cur);
    task2_cal_operator(cur, 100, MULT);
    task2_cal_show(cur);
    task2_cal_operator(cur, 10, DEVIDE);
    task2_cal_show(cur);
}
