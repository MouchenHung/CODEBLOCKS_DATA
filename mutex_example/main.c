#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);
//pthread_cond_wait
typedef struct ct_sum
{
    int sum;
    char *TH_NAME;
    pthread_mutex_t lock;
}ct_sum;

pthread_mutex_t MUTEX_SHARE;
sem_t SEM_ENDING_SINGAL, SEM_SHARE;
pthread_cond_t cond;
int flag, counter;

void * add1(void * cnt)
{
    int i;

    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    printf("[lock] get from add1\n");
    for( i=1;i<=50;i++)
    {
        (*(ct_sum*)cnt).sum+=i;
        printf("add1 sum = %d\n", (*(ct_sum*)cnt).sum);
    }
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));

    sem_post(&SEM_ENDING_SINGAL);

    pthread_exit(NULL);
}

void * add2(void *cnt)
{
    int i;

    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    printf("[lock] get from add2\n");
    for( i=1;i<=50;i++)
    {
        (*(ct_sum*)cnt).sum+=i;
        printf("add2 sum = %d\n", (*(ct_sum*)cnt).sum);
    }
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));

    sem_post(&SEM_ENDING_SINGAL);

    pthread_exit(NULL);
}

void *add3(void *cnt)
{
    int i;

    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    if (flag == 0)
        flag = 1;

    printf("[lock] get from add3\n");
    if (flag != 2)
        pthread_cond_wait (&cond, &(((ct_sum*)cnt)->lock));

    for( i=1;i<=50;i++)
    {
        (*(ct_sum*)cnt).sum-=i;
        printf("--> MINUS in thread3, sum = %d\n", (*(ct_sum*)cnt).sum);
    }
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));

    pthread_exit(NULL);
}

void *add4(void *cnt)
{
    int i;

    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    printf("[lock] get from add4\n");
    for( i=1;i<=50;i++)
    {
        (*(ct_sum*)cnt).sum+=i;
        printf("--> PLUS in thread4, sum = %d\n", (*(ct_sum*)cnt).sum);
    }
    if (flag == 0)
        flag = 2;
    else if (flag == 1)
        pthread_cond_signal (&cond);

    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));

    pthread_exit(NULL);
}

void *add5(void *cnt)
{
    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    printf("[lock] ADD5 waiting...\n");
    pthread_cond_wait(&cond, &(((ct_sum*)cnt)->lock));
    printf("[lock] ADD5 complete!\n");
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
    pthread_exit(NULL);
}

void *add6(void *cnt)
{
    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    printf("[lock] ADD6 waiting...\n");
    pthread_cond_wait(&cond, &(((ct_sum*)cnt)->lock));
    printf("[lock] ADD6 complete!\n");
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
    pthread_exit(NULL);
}

void *add7(void *cnt)
{
    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    printf("[lock] ADD7 waiting...\n");
    pthread_cond_wait(&cond, &(((ct_sum*)cnt)->lock));
    printf("[lock] ADD7 complete!\n");
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
    pthread_exit(NULL);
}

void *add8(void *cnt)
{
    pthread_mutex_lock(&(((ct_sum*)cnt)->lock));
    /* Orderly bring back mutex key */
    //pthread_cond_signal(&cond);
    //pthread_cond_signal(&cond);
    //pthread_cond_signal(&cond);
    /* Randomly bring back mutex key one by one */
    pthread_cond_broadcast(&cond);
    printf("--> Signal back\n");
    pthread_mutex_unlock(&(((ct_sum*)cnt)->lock));
    pthread_exit(NULL);
}

void *TH_control(void)
{
    while(counter<30){
        sem_wait(&SEM_SHARE);
        counter+=1;
        sem_post(&SEM_SHARE);
    }
}

void *TH_print_1(void)
{
    while(counter<30){
        sem_wait(&SEM_SHARE);
        printf("TH print[1]: counter=%d\n", counter);
        sem_post(&SEM_SHARE);
    }
}

void *TH_print_2(void)
{
    while(counter<30){
        sem_wait(&SEM_SHARE);
        printf("TH print[2]: counter=%d\n", counter);
        sem_post(&SEM_SHARE);
    }
}

void *TH_print_3(void)
{
    while(counter<30){
        sem_wait(&SEM_SHARE);
        printf("TH print[3]: counter=%d\n", counter);
        sem_post(&SEM_SHARE);
    }
}

int main(void)
{
    pthread_t ptid1,ptid2, ptid3, ptid4, ptid5, ptid6, ptid7, ptid8;
    ct_sum cnt;

    // Semaphore as a signal
    sem_init(&SEM_ENDING_SINGAL, 0, 0);

    pthread_mutex_init(&(cnt.lock),NULL);

    cnt.sum=0;

    // Create thread
    if ( pthread_create(&ptid1,NULL,add1,&cnt) )
    {
        exit(0);
    }
    if ( pthread_create(&ptid2,NULL,add2,&cnt) )
    {
        exit(0);
    }

    sem_wait(&SEM_ENDING_SINGAL);
    sem_wait(&SEM_ENDING_SINGAL);

    pthread_mutex_lock(&(cnt.lock));
    printf("[lock] get from sum print\n");
    printf("sum = %d\n",cnt.sum);
    pthread_mutex_unlock(&(cnt.lock));

    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);

    pthread_mutex_destroy(&(cnt.lock));
    sem_destroy(&SEM_ENDING_SINGAL);

    PAUSE
    pthread_mutex_init(&(cnt.lock),NULL);
    pthread_attr_t attr1,attr2;
    struct sched_param param;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    param.sched_priority = 2;
    pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
    pthread_attr_setschedparam(&attr1,&param);
    pthread_attr_setinheritsched(&attr1,PTHREAD_CREATE_JOINABLE);

    param.sched_priority = 1;
    pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
    pthread_attr_setschedparam(&attr2,&param);
    pthread_attr_setinheritsched(&attr2,PTHREAD_CREATE_JOINABLE);

    cnt.sum=0;

    // Create thread
    if ( pthread_create(&ptid1,&attr1,add1,&cnt) )
    {
        printf("[Error] thread1 create failed!\n");
        exit(0);
    }
    if ( pthread_create(&ptid2,&attr2,add2,&cnt) )
    {
        printf("[Error] thread2 create failed!\n");
        exit(0);
    }
    pthread_mutex_lock(&(cnt.lock));
    printf("[lock] get from sum print\n");
    printf("sum = %d\n",cnt.sum);
    pthread_mutex_unlock(&(cnt.lock));

    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);

    pthread_mutex_destroy(&(cnt.lock));

    /*
        Note: Using "pthread_cond_wait" to let thread temporary
        Purpose of EX: To avoid negative number of global variable "sum", means add4 need to have higher priority than add3
        flag
        [0]: haven't get in add3
        [1]: if get in add3 but haven't complete add4
        [2]: if get in add3 and wait there until complete add4, give this flag to bring back key
    */
    PAUSE
    printf("<<<     EX3. Using pthread_cond_wait to temporary give out mutex lock to others who need and give it back by sending pthread_cond_signal     >>>\n");
    pthread_mutex_init(&(cnt.lock),NULL);
    cnt.sum=0;
    flag = 0;

    if ( pthread_create(&ptid3,NULL,add3,&cnt) )
    {
        printf("[Error] thread3 create failed!\n");
        exit(0);
    }
    if ( pthread_create(&ptid4,NULL,add4,&cnt) )
    {
        printf("[Error] thread4 create failed!\n");
        exit(0);
    }
    pthread_join(ptid3,NULL);
    pthread_join(ptid4,NULL);

    pthread_mutex_destroy(&(cnt.lock));

    PAUSE
    printf("<<<     EX4. MultiCast     >>>\n");
    pthread_mutex_init(&(cnt.lock),NULL);

    // Create thread
    cnt.TH_NAME = "PID5";
    if ( pthread_create(&ptid5,NULL,add5,&cnt) )
    {
        exit(0);
    }
    cnt.TH_NAME = "PID6";
    if ( pthread_create(&ptid6,NULL,add6,&cnt) )
    {
        exit(0);
    }
    cnt.TH_NAME = "PID7";
    if ( pthread_create(&ptid7,NULL,add7,&cnt) )
    {
        exit(0);
    }
    sleep(2);
    cnt.TH_NAME = "PID8";
    if ( pthread_create(&ptid8,NULL,add8,&cnt) )
    {
        exit(0);
    }

    pthread_join(ptid5,NULL);
    pthread_join(ptid6,NULL);
    pthread_join(ptid7,NULL);
    pthread_join(ptid8,NULL);
    pthread_mutex_destroy(&(cnt.lock));



    PAUSE
    printf("<<<     EX5. Variable modified sync     >>>\n");
    sem_init(&SEM_SHARE, 0, 3);


    if ( pthread_create(&ptid1,NULL,TH_control, NULL) )
    {
        exit(0);
    }
    if ( pthread_create(&ptid2,NULL,TH_print_1, NULL) )
    {
        exit(0);
    }
    if ( pthread_create(&ptid3,NULL,TH_print_2, NULL) )
    {
        exit(0);
    }

    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);
    pthread_join(ptid3,NULL);

    sem_destroy(&SEM_SHARE);

    return 0;
}

