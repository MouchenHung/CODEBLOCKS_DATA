/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);

/* prototype for thread routine */
void handler ( void *ptr );
void TRIGGER_POST(sem_t *, int );
void share_variable_handler( int );
void ASK_SHARE_VARIABLE();
void TASK_A ( void *ptr );
void TASK_B ( void *ptr );
void TASK_C ( void *ptr );

/* global vars */
/* semaphores are declared global so they can be accessed
   in main() and in thread routine,
   here, the semaphore is used as a mutex */
sem_t mutex, sem1, sem2, sem3, sem_share;
int counter; /* shared variable */
int A;
int B;
int C;
int END_SIGNAL = 0;

int main()
{
    int i[2];
    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;

    i[0] = 0; /* argument to threads */
    i[1] = 1;

    counter = 5;
    A=0; B=0; C=0;

    printf("<<     EX1: Semaphore used as mutex     >>\n");
    sem_init(&mutex, 0, 1);      /* initialize mutex to 1 - binary semaphore */
                                 /* second param = 0 - semaphore is local */

    /* Note: you can check if thread has been successfully created by checking return value of
       pthread_create */
    pthread_create (&thread_a, NULL, (void *) &handler, (void *) &i[0]);
    pthread_create (&thread_b, NULL, (void *) &handler, (void *) &i[1]);

    pthread_join(thread_a, NULL); // 特別標註一下，join是表示要等這個thread結束才會繼續執行下去，否則主程式結束了thread還沒結束怎麼行呢XD
    pthread_join(thread_b, NULL);

    sem_destroy(&mutex); /* destroy semaphore */
    PAUSE

    printf("\n<<     EX2: Semaphore used as signal     >>\n");
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    pthread_create (&thread_a, NULL, (void *) &TASK_A, (void *) &i[0]);
    pthread_create (&thread_b, NULL, (void *) &TASK_B, &B);
    pthread_create (&thread_c, NULL, (void *) &TASK_C, &C);

    // Trigger sem1 to start thread_1 task_A and follow a fixed order thread_1 --> thread_2 --> thread_3 --> thread_1 --> ...
    TRIGGER_POST(&sem1, 1);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);

    sem_destroy(&sem1); /* destroy semaphore */
    sem_destroy(&sem2); /* destroy semaphore */
    sem_destroy(&sem3); /* destroy semaphore */
    PAUSE

    printf("<<     EX3: Semaphore used as sys     >>\n");
    counter = 0;
    sem_init(&sem_share, 0, 3);

    pthread_create (&thread_a, NULL, (void *) &share_variable_handler, 1);
    pthread_create (&thread_b, NULL, (void *) &share_variable_handler, 2);
    pthread_create (&thread_c, NULL, (void *) &share_variable_handler, 3);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);

    sem_post(&sem_share);
    ASK_SHARE_VARIABLE();

    sem_destroy(&sem_share); /* destroy semaphore */

    /* exit */
    exit(0);
} /* main() */

void handler ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    printf("Thread %d: Waiting to enter critical region...\n", x);
    sem_wait(&mutex);       /* down semaphore */
    /* START CRITICAL REGION */
    printf("Thread %d: Now in critical region...\n", x);
    printf("Thread %d: Counter Value: %d\n", x, counter);
    printf("Thread %d: Incrementing Counter...\n", x);
    counter++;
    printf("Thread %d: New Counter Value: %d\n", x, counter);
    printf("Thread %d: Exiting critical region...\n", x);
    /* END CRITICAL REGION */
    sem_post(&mutex);       /* up semaphore */

    pthread_exit(0); /* exit thread */
}

void share_variable_handler( int th_num )
{
    sem_wait(&sem_share);
    printf("Thread %d handling share variable, counter=%d\n", th_num, counter);
    counter+=1;
    pthread_exit(0); /* exit thread */
}

void ASK_SHARE_VARIABLE()
{
    sem_wait(&sem_share);
    printf("Share variable counter=%d\n", counter);
}

void TRIGGER_POST(sem_t *SEM_NUM, int th_num )
{
    printf("[trigger] sem post %d with %d\n", th_num, SEM_NUM);
    sem_post(SEM_NUM);
}

void TASK_A ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    while(1)
    {
        printf("Thread 1: Waiting to enter critical region.............\n");
        sem_wait(&sem1);       /* down semaphore */

        /* START CRITICAL REGION */
        printf("Thread 1: Now in critical region\n");
        if (END_SIGNAL == 0)
        {
            A+=1;
        }
        else
        {
            printf("END OF TASK A\n");
            /* TRIGGER NEXT SEMPHORE */
            TRIGGER_POST(&sem2, 2);
            break;
        }
        printf("Thread 1: A: %d\n", A);
        printf("Thread 1: Exiting critical region\n");
        /* END CRITICAL REGION */
        /* TRIGGER NEXT SEMPHORE */
        TRIGGER_POST(&sem2, 2);
    }




    pthread_exit(0); /* exit thread */
}

void TASK_B ( void *ptr )
{
    int x;
    x = *((int *) ptr);
    while(1)
    {
        printf("Thread 2: Waiting to enter critical region.............\n");
        sem_wait(&sem2);       /* down semaphore */

        /* START CRITICAL REGION */
        printf("Thread 2: Now in critical region\n");
        if (END_SIGNAL == 0)
        {
            B+=1;
        }
        else
        {
            printf("END OF TASK B\n");
            break;
        }

        printf("Thread 2: B: %d\n", B);
        printf("Thread 2: Exiting critical region\n");
        /* END CRITICAL REGION */

        /* TRIGGER NEXT SEMPHORE */
        TRIGGER_POST(&sem3, 3);
    }
    pthread_exit(0); /* exit thread */
}

void TASK_C ( void *ptr )
{
    static loop = 0;
    int x;
    x = *((int *) ptr);
    while(1)
    {
        printf("Thread 3: Waiting to enter critical region.............\n");
        sem_wait(&sem3);       /* down semaphore */

        /* START CRITICAL REGION */
        printf("Thread 3: Now in critical region\n");
        C=A-B;
        printf("Thread 3: C: %d\n", C);
        printf("Thread 3: Exiting critical region\n");
        /* END CRITICAL REGION */

        if (loop == 3){
            END_SIGNAL = 1;
            /* TRIGGER NEXT SEMPHORE */
            TRIGGER_POST(&sem1, 1);
            printf("END OF TASK C\n");
            break;
        }


        /* TRIGGER NEXT SEMPHORE */
        TRIGGER_POST(&sem1, 1);
        loop+=1;

    }

    pthread_exit(0); /* exit thread */
}


