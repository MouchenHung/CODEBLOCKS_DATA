/*PROJECT NAME: Linked List operation*/
/*FUNCTION: linked list push element, pop element, print element, limit memory allocate mechanism.*/
/*KEYWORDS: linked list, malloc, queue, stack, struct*/
/*FIRST EDIT: MOUCHEN HUNG 2020.07.08*/


#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node *next;
};
typedef struct node Node;
Node *head=NULL, *prev=NULL, *new_node; //for version0.
Node *cur, *front_node, *rear_node, *tmp_node, *tfree_node; //for version1.
int ll_size;
/*
struct queue{
    struct node *front;
    struct node *rear;
    int size;
};
typedef struct queue Queue;
Queue *q=NULL;
*/
void _pop_back();
void _pop_front();


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
        printf("--> Your pop data: %d\n", front_node->val);
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
                printf("--> Your pop data: %d\n", rear_node->val);
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

void get_central(){
    Node *fast_step = front_node;
    Node *slow_step = front_node;

    while(fast_step->next->next) {
        fast_step = fast_step->next->next;
        slow_step = slow_step->next;
    }
    printf("--> Your central element of Linked List: %d\n", slow_step->val);

error:
    printf("--> There should be more then 2 elements in Linked List!\n");
}

void print_LL(int limit_num){ //print current Linked List.
    tmp_node = front_node;
    if(tmp_node){
        printf("--> Your current Linked List: << ");
        while(tmp_node){
            printf("%d ", tmp_node->val);
            tmp_node = tmp_node->next;
        }
        printf(">> total: %d/%d\n", ll_size, limit_num);
    }
    else
        printf("    --> Your current Linked List: << none >> total: %d/%d\n", ll_size, limit_num);
}

void memoryFree_all(){ //free current Node, including [cur], [front_node], [rear_node] by dummy node [tfree_node].
    while(cur){
        tfree_node = cur;
        free(tfree_node);
        cur = cur->next;
    }
    while(front_node){
        tfree_node = front_node;
        free(tfree_node);
        front_node = front_node->next;
    }
    while(rear_node){
        tfree_node = rear_node;
        free(tfree_node);
        rear_node = rear_node->next;
    }
    printf("--> Node Memory has been clean !\n");
}



void message1(){
    printf("\n=============================\nHELP:\n");
    printf("cmd[0]: End section.\n");
    printf("cmd[1]: NO MEMORY-LIMIT mode.\n");
    printf("cmd[2]: MEMORY-LIMIT mode.\n");
    printf("cmd[others]: Call HELP.\n=============================\n\n");
}

void message2(){
    printf("\n======================================================\nHELP:\n");
    printf("cmd[0]: End section.\n");
    printf("cmd[1]: [push] a data in the [front] of Linked List.\n");
    printf("cmd[2]: [push] a data in the [back] of Linked List.\n");
    printf("cmd[3]: [pop] a data in the [front] of Linked List.\n");
    printf("cmd[4]: [pop] a data in the [back] of Linked List.\n");
    printf("cmd[5]: Print out current Linked List.\n");
    printf("cmd[6]: Find central element of Linked List.\n");
    printf("cmd[others]: Call HELP.\n======================================================\n\n");
}

void LinkedList_operation_cmd(int limit_N){
    int endflag1=0, cmd, number;
    cur=NULL, front_node=NULL, rear_node=NULL, tmp_node=NULL;
    ll_size=0;

    enum Action2{
        QUIT = 0,
        PUSH_FRONT,
        PUSH_BACK,
        POPFRONT,
        POPBACK,
        PRINT,
        GET_CENTRAL,
        BB_SORT,
        Q_SORT
    };

    message2();
    while(!endflag1){
        printf("----------------------------------------------------------------\n$Select your mode(cmd: PUSH_MODE[1][2] POP_MODE[3][4] , PRINT[5] QUIT[0] , select others for help): ");
        scanf("%d", &cmd);
        switch(cmd){
            case QUIT:
                printf("--> end section!\n");
                print_LL(limit_N);
                memoryFree_all();
                endflag1 = 1;
                break;

            case PUSH_FRONT:
                printf("* [push] a data in the [front] of Linked List\n");
                printf("$please enter a number: ");
                scanf("%d", &number);
                _push_front1(number, limit_N);
                print_LL(limit_N);
                break;

            case PUSH_BACK:
                printf("* [push] a data in the [back] of Linked List\n");
                printf("$please enter a number: ");
                scanf("%d", &number);
                _push_back1(number, limit_N);
                print_LL(limit_N);
                break;

            case POPFRONT:
                printf("* [pop] a data in the [front] of Linked List\n");
                _pop_front();
                print_LL(limit_N);
                break;

            case POPBACK:
                printf("* [pop] a data in the [back] of Linked List\n");
                _pop_back();
                print_LL(limit_N);
                break;

            case PRINT:
                printf("* show current RESULT of Linked List\n");
                print_LL(limit_N);
                break;

            case GET_CENTRAL:
                printf("* get central element of Linked List\n");
                get_central();
                break;

            default:
                printf("--> no such command!!\n");
                message2();
                break;
        }
        printf("\n");
    }

    printf("\n");
}

int main()
{
    int endflag=0, cmd, limit_N=100; //memory limit default 100

    enum Action1 {
        QUIT = 0,
        NO_BOUND,
        WITH_BOUND
    };

    message1();
    while(!endflag){
        printf("$Select Linked List memory mode(cmd: MODE[1][2] QUIT[0] , select others for help): ");
        scanf("%d", &cmd);
        switch(cmd){
        case QUIT:
            printf("! end section !\n");
            endflag = 1;
            break;

        case NO_BOUND:
            printf("--> you are in [NO MEMORY-LIMIT] mode\n\n");
            LinkedList_operation_cmd(limit_N);
            break;

        case WITH_BOUND:
            printf("--> you are in [MEMORY-LIMIT] mode\n\n");
            printf("$Please enter memory-limit numbers: ");
            scanf("%d", &limit_N);
            printf("\n\n");
            LinkedList_operation_cmd(limit_N);
            break;

        default:
            printf("--> no such command!!\n");
            message1();
            break;
        }
    }



    return 0;
}

