#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter;

pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer (void* data)
{
    while (1) {
        pthread_mutex_lock (&mutex);
        if (counter > 0)
        {
            pthread_cond_wait (&cond, &mutex);
        }
        counter +=6;
        printf ("Boss makes 6 bento. Left %d bento\n", counter);
        printf ("--> Boss can settle bill.\n\n");
        pthread_mutex_unlock (&mutex);
    }
}

void *consumer (void* data)
{
    while (1) {
        sleep (2);
        pthread_mutex_lock (&mutex);
        if (counter == 2)
        {
            counter -= 2;
            printf ("Consumer buys 2 bento. Left %d bento.\n", counter);
            printf ("--> Call boss to make bento\n\n");
            pthread_cond_signal (&cond);
        }
        else
        {
            counter -= 2;
            printf ("Consumer buys 2 bento. Left %d bento.\n", counter);
        }
        pthread_mutex_unlock (&mutex);
    }
}

int main () {
    pthread_t t1, t2;

    counter = 2;
    pthread_mutex_init (&mutex, 0);
    pthread_create (&t2, NULL, consumer, NULL);
    pthread_create (&t1, NULL, producer, NULL);

    // Main process sleep 30 sec, after it, Every sub-process would stop by force
    sleep (30);
    return 0;
}
