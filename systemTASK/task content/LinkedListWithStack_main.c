/*PROJECT NAME: Linked List operation*/
/*FUNCTION: linked list push element, pop element, print element, limit memory allocate mechanism.*/
/*KEYWORDS: linked list, malloc, queue, stack, struct*/
/*FIRST EDIT: MOUCHEN HUNG 2020.07.08*/

#include <stdio.h>
#include <stdlib.h>
#include "toolbox_h/tool_head.h"
#include "../task head/task_head.h"



/* TASK3-Linked List with Stack */
void task3_main()
{
    int endflag=0, cmd, limit_N=100; //memory limit default 100

    enum Action1 {
        QUIT = 0, NO_BOUND = 1, WITH_BOUND = 2
    };

    message1();
    while(!endflag){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nSelect Linked List memory mode(cmd: MODE[1][2] QUIT[0] , select others for help):");
        scanf("%d", &cmd);
        switch(cmd){
        case QUIT:
            printf("! end section !\n");
            endflag = 1;
            break;

        case NO_BOUND:
            printf("| NO MEMORY-LIMIT mode |\n\n");
            LinkedList_operation_cmd(limit_N);
            break;

        case WITH_BOUND:
            printf("| MEMORY-LIMIT mode |\n");
            printf("-->please enter memory-limit numbers:");
            scanf("%d", &limit_N);
            printf("\n\n");
            LinkedList_operation_cmd(limit_N);
            break;

        default:
            printf("no such command!!\n->HELP:\n");

            break;
        }
    }

}
