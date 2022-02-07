#include <stdio.h>
#include <stdlib.h>

#include "task head/task_head.h"

#define TASK_option 5
/*
[0] TASK0-Head and Extern Test   - ed.20200715
[1] TASK1-Stringizing Operator   - ed.20200715
[2] TASK2-Calculator             - ed.20200715
[3] TASK3-Linked List with Stack - ed.20200715
[4] TASK4-Assert while compile   - ed.20200716
[5] TASK5-Binary Search Tree     - ed.20200805
*/
int main()
{
    printf("|******* This is TASK [ %d ] test. *******|\n", TASK_option);
    #if(TASK_option == 0)
    /* TASK0-Head and Extern Test */
    task0_main();

    #elif(TASK_option == 1)
    /* TASK1-Stringizing Operator */
    task1_main();

    #elif(TASK_option == 2)
    /* TASK2-Calculator */
    task2_main();

    #elif(TASK_option == 3)
    /* TASK3-Linked List with Stack */
    task3_main();

    #elif(TASK_option == 4)
    /* TASK4-Assert while compile */
    task4_main();

    #elif(TASK_option == 5)
    /* TASK5-Binary Search Tree */
    task5_main();

    #else
    printf("NO SUCH TASK !");

    #endif

    return 0;
}






