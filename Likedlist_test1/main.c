#include <stdio.h>
#include <stdlib.h>


struct LL_node{
        int data;
        struct LL_node *next;
    };
    typedef struct LL_node ll_node;
ll_node *prev_ll=NULL, *cur_ll=NULL, *head_ll=NULL;

void LL_print(int *c){
    cur_ll = head_ll;
    while(cur_ll){
        printf("data=%d ",cur_ll->data); //印出節點的資料
        cur_ll = cur_ll->next;
    }
    printf("totalCNT: %d\n", *c);
    printf("\n");
}

void LL_reverse(int *c){
    ll_node *newhead_ll=NULL;
    //cur_ll = head_ll;
    while(head_ll){
        ll_node *temp = head_ll->next;
        head_ll->next = newhead_ll;
        newhead_ll = head_ll;
        head_ll = temp;
    }
    while(newhead_ll){
        printf("data=%d ",newhead_ll->data); //印出節點的資料
        newhead_ll = newhead_ll->next;
    }
    printf("totalCNT: %d\n", *c);
    printf("\n");
}

void LL(int cmd, int *stop_flag){
    int num;
    static int cnt=0;
    int *CNT=&cnt;


    if(cmd == 0){
        printf("end section!");
        free(cur_ll);
        *stop_flag = 0;
        *CNT=0;
    }
    else if(cmd == 1){
        LL_print(CNT);

    }
    else if(cmd == 2){
        cur_ll=(ll_node *) malloc(sizeof(ll_node));//建立新節點
        printf("enter a new num:");
        scanf("%d", &(cur_ll->data));
        printf("\n");


        if(*CNT == 0){
            //printf("first data adding %d\n\n", cur_ll->data);
            head_ll = cur_ll;
        }

        else{
            //printf("non-empty LL data adding %d\n\n", cur_ll->data);
            prev_ll->next = cur_ll;
        }
        cur_ll->next = NULL;
        prev_ll = cur_ll;
        *CNT+=1;

        LL_print(CNT);
    }

    else if(cmd == 3){
        if(*CNT>0){
            head_ll = head_ll->next;
            (*CNT)--;
            LL_print(CNT);
        }
        else{
            printf("no element in LL!\n");
            *CNT=0;
        }
    }

    else if(cmd == 4){
        if(*CNT == 0){
            printf("no element in LL!\n");
        }
        else if(*CNT == 1)
            printf("no element in LL!\n");
    }

    else if(cmd == 5){
        LL_reverse(CNT);
    }

    else
        printf("error cmd!\n");

}

int main()
{
    int s=1, cmd;
    int *stop_flag = &s;

    while(*stop_flag == 1){
        printf("cmd = ");
        scanf("cmd = %d",&cmd);
        LL(cmd, stop_flag);
    }


    return 0;
}
