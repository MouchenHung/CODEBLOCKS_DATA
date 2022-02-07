#include <stdio.h>
#include <stdlib.h>
#include "../toolbox_h/tool_head.h"

Node *cur, *front_node, *rear_node, *tmp_node, *tfree_node; //for version1.
int ll_size;

void message1(){
    printf("\n=============================\n->HELP:\n");
    printf("->cmd[0]: End section.\n");
    printf("->cmd[1]: NO MEMORY-LIMIT mode.\n");
    printf("->cmd[2]: MEMORY-LIMIT mode.\n");
    printf("->cmd[others]: Call HELP.\n=============================\n\n");
}

void message2(){
    printf("\n======================================================\n->HELP:\n");
    printf("->cmd[0]: End section.\n");
    printf("->cmd[1]: [push] a data in the [front] of Linked list.\n");
    printf("->cmd[2]: [push] a data in the [back] of Linked list.\n");
    printf("->cmd[3]: [pop] a data in the [front] of Linked list.\n");
    printf("->cmd[4]: [pop] a data in the [back] of Linked list.\n");
    printf("->cmd[others]: Call HELP.\n======================================================\n\n");
}


void _push_front1(int v, int LN){ //add a node in front of the Linked List
    cur=(Node *) malloc(sizeof(Node));
    cur->val = v;
    cur->next = NULL;

    if(front_node==NULL){
        front_node = rear_node = cur;
    }
    else{
        cur->next = front_node;
        front_node = cur;
    }
    ll_size++;
    Limit_judge(0, LN); //limit memory
}

void _push_back1(int v, int LN){ //add a node back of the Linked List.
    cur=(Node *) malloc(sizeof(Node));
    cur->val = v;
    cur->next = NULL;

    if(rear_node==NULL){
        rear_node = front_node = cur;
    }
    else{
        rear_node->next = cur;
        rear_node = rear_node->next;
    }
    ll_size++;
    Limit_judge(1, LN); //limit memory
}

void _pop_front(){ //delete a node in front of the Linked List.
    if(front_node){
        tfree_node = front_node;
        printf("-->your pop data: %d\n", front_node->val);
        front_node = front_node->next;
        ll_size--;
        free(tfree_node);
    }
}

void _pop_back(){ //delete a node back of the Linked List.
    tmp_node = front_node;
    tfree_node = rear_node;
    while(tmp_node){
        if(tmp_node->next){

            if(tmp_node->next->next==NULL){
            printf("-->your pop data: %d\n", rear_node->val);
            rear_node = tmp_node;
            rear_node->next = NULL;
            free(tfree_node);
            ll_size--;
            break;
        }
        tmp_node = tmp_node->next;
        }
        else{
            front_node = rear_node = NULL;
            free(tfree_node);
            ll_size--;
            break;
        }
    }
}

void print_LL(){ //print current Linked List.
    tmp_node = front_node;
    if(tmp_node){
        printf("-->Your current Linked List: << ");
        while(tmp_node){
            printf("%d ", tmp_node->val);
            tmp_node = tmp_node->next;
        }
        printf(">> total: %d\n", ll_size);
    }
    else
        printf("-->Your current Linked List: << none >> total: %d\n", ll_size);

}

void memoryFree_all(){ //free current Node, including [cur], [front_node], [rear_node] by dummy node [tfree_node].
    while(cur){
        tfree_node = cur;
        free(tfree_node);
        cur = cur->next;
        //printf("cur\n");
    }
    while(front_node){
        tfree_node = front_node;
        free(tfree_node);
        front_node = front_node->next;
        //printf("front_node\n");
    }
    while(rear_node){
        tfree_node = rear_node;
        free(tfree_node);
        rear_node = rear_node->next;
        //printf("rear_node\n");
    }
    printf("-->Node Memory has been clean !\n");
}

void Limit_judge(int LM, int lm_num){
    if(ll_size > lm_num){
        if(LM == 0){
            _pop_back();
        }
        else if(LM == 1){
            _pop_front();
        }
    }
}

void LinkedList_operation_cmd(int limit_N){
    int endflag1=0, cmd, number;
    cur=NULL, front_node=NULL, rear_node=NULL, tmp_node=NULL;
    ll_size=0;

    enum Action2{
        QUIT = 0, PUSH_FRONT = 1, PUSH_BACK = 2, POPFRONT = 3, POPBACK = 4, PRINT = 5
    };

    message2();
    while(!endflag1){
        printf("----------------------------------------------------------------\nSelect your mode(cmd: PUSH_MODE[1][2] POP_MODE[3][4] , PRINT[5] QUIT[0] , select others for help):");
        scanf("%d", &cmd);
        switch(cmd){
            case QUIT:
                printf("! end section !\n");
                print_LL();
                memoryFree_all();
                endflag1 = 1;
                break;

            case PUSH_FRONT:
                printf("| [push] a data in the [front] of Linked list |\n");
                printf("-->please enter a number:");
                scanf("%d", &number);
                _push_front1(number, limit_N);
                print_LL();
                break;

            case PUSH_BACK:
                printf("| [push] a data in the [back] of Linked list |\n");
                printf("-->please enter a number:");
                scanf("%d", &number);
                _push_back1(number, limit_N);
                print_LL();
                break;

            case POPFRONT:
                printf("| [pop] a data in the [front] of Linked list |\n");
                _pop_front();
                print_LL();
                break;

            case POPBACK:
                printf("| [pop] a data in the [back] of Linked list |\n");
                _pop_back();
                print_LL();
                break;

            case PRINT:
                printf("| show current RESULT of Linked List |\n");
                print_LL();
                break;

            default:
                printf("no such command!!\n");
                message2();
                break;
        }
    }

    printf("\n");
}
