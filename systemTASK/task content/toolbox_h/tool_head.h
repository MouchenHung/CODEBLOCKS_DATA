#ifndef TOOL_HEAD_H_INCLUDED
#define TOOL_HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define STR(s) #s
#define CONS(a,b) a##e##b
#define Addr1 0x12
#define Addr2 0x5e
#define Addr3 0100
#define Addr4 0010
#define a 5

/* TASK2-CALCULATOR */
void task2_cal_operator(int *cur, int num, int mode);
void task2_cal_show(int *cur);

/* TASK3-Linked List with Stack */


typedef struct node{
    int val;
    struct node *next;
}Node;

extern int ll_size;
void message1();
void message2();
void _push_front1(int v, int LN);
void _push_back1(int v, int LN);
void _pop_front();
void _pop_back();
void print_LL();
void memoryFree_all();
void Limit_judge(int LM, int lm_num);
void LinkedList_operation_cmd(int limit_N);

#endif // TOOL_HEAD_H_INCLUDED
