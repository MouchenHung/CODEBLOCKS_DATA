//#define _GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<pthread.h>
#include	<signal.h>
#include    <string.h>

void * thr_fun1(void *arg)
{
    /*
	int policy, ret;
	struct sched_param param;
	// Get thread scheduling parameters
	ret = pthread_getschedparam(pthread_self(), &policy, &param);
	if(ret!=0)
	{
		printf("pthread_getschedparam error: %s\n", strerror(ret) );
		exit(1);
	}
	if (policy == SCHED_FIFO)
	{
		printf("policy:SCHED_FIFO\n");
	}
	else if (policy == SCHED_OTHER)
	{
		printf("policy:SCHED_OTHER\n");
	}
	else if (policy == SCHED_RR)
	{
		printf("policy:SCHED_RR\n");
	}
	printf("param:%d\n", param.sched_priority);
    */
    /* looping */
    int i;
	for (i=0; i<=50; i++){
        printf("TH1: counting %d\n", i);
        //sleep(1);
	}

	pthread_exit(NULL);
}

void * thr_fun2(void *arg)
{
    /*
	int policy, ret;
	struct sched_param param;
	// Get thread scheduling parameters
	ret = pthread_getschedparam(pthread_self(), &policy, &param);
	if(ret!=0)
	{
		printf("pthread_getschedparam error: %s\n", strerror(ret) );
		exit(1);
	}
	if (policy == SCHED_FIFO)
	{
		printf("policy:SCHED_FIFO\n");
	}
	else if (policy == SCHED_OTHER)
	{
		printf("policy:SCHED_OTHER\n");
	}
	else if (policy == SCHED_RR)
	{
		printf("policy:SCHED_RR\n");
	}
	printf("param:%d\n", param.sched_priority);
	*/

    /* looping */
    int i;
	for (i=0; i<=50; i++){
        printf("    TH2: counting %d\n", i);
        //sleep(1);
	}

	pthread_exit(NULL);
}



int main(void)
{
	int ret;
	pthread_t tid, tid2;
	pthread_attr_t attr1, attr2;
	int policy, inher;
	struct sched_param param1, param2;

    // Initialize thread properties
	pthread_attr_init(&attr1);

	 // Get the inherited scheduling strategy
	ret = pthread_attr_getinheritsched(&attr1, &inher);
	if (ret!=0)
	{
		printf("pthread_attr_getinheritsched error: %s\n", strerror(ret));
		exit(1);
	}

	if (inher == PTHREAD_EXPLICIT_SCHED)
	{
		printf("Inherit strategy = PTHREAD_EXPLICIT_SCHED\n");
	}
   	else if (inher == PTHREAD_INHERIT_SCHED)
	{
		printf("Inherit strategy = PTHREAD_INHERIT_SCHED\n");
		inher = PTHREAD_EXPLICIT_SCHED;
	}
	 // Set the inherited scheduling strategy
	 // must set the inherit attribute to PTHREAD_EXPLICIT_SCHED, otherwise the priority of the set thread will be ignored
	ret = pthread_attr_setinheritsched(&attr1, inher);
	if (ret!=0)
	{
		printf(" TH1 pthread_attr_setinheritsched error: %s\n", strerror(ret));
		exit(1);
	}

	 policy = SCHED_FIFO;//Requires root privileges on Ubuntu 9.10
	 // Set the thread scheduling strategy
	ret = pthread_attr_setschedpolicy(&attr1, policy);
	if (ret!=0)
	{
		printf(" TH1 pthread_attr_setschedpolicy error: %s\n", strerror(ret));
		exit(1);
	}

	param1.sched_priority = 3;
    // Set the scheduling parameters
	ret = pthread_attr_setschedparam(&attr1, &param1);
	if (ret!=0)
	{
		printf(" TH1 pthread_attr_setschedparam error: %s\n", strerror(ret));
		exit(1);
	}
	// Create a thread
	if ( pthread_create(&tid, &attr1, thr_fun1, NULL) )
	{
		printf(" TH1 pthread_create error: %s\n", strerror(ret));
		exit(1);
	}





	// Initialize thread properties
	pthread_attr_init(&attr2);

	inher = PTHREAD_EXPLICIT_SCHED;
	ret = pthread_attr_setinheritsched(&attr2, inher);
	if (ret!=0)
	{
		printf(" TH2 pthread_attr_setinheritsched error: %s\n", strerror(ret));
		exit(1);
	}

    policy = SCHED_FIFO;
	ret = pthread_attr_setschedpolicy(&attr2, policy);
	if (ret!=0)
	{
		printf(" TH2 pthread_attr_setschedpolicy error: %s\n", strerror(ret));
		exit(1);
	}

	param2.sched_priority = 2;
    // Set the scheduling parameters
	ret = pthread_attr_setschedparam(&attr2, &param2);
	if (ret!=0)
	{
		printf(" TH2 pthread_attr_setschedparam error: %s\n", strerror(ret));
		exit(1);
	}
	// Create a thread
	if ( pthread_create(&tid2, &attr2, thr_fun2, NULL) )
	{
		printf(" TH2 pthread_create error: %s\n", strerror(ret));
		exit(1);
	}

	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);

	pthread_attr_destroy(&attr1);
	pthread_attr_destroy(&attr2);
}
