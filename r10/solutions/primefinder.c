#include <stdio.h>
#include "chan.h"

#define MAXNUM 1000

int numbers[MAXNUM];
int primeFlag = 1;

// channel bringing work requests from main thread to workers
channel requests;

// channel bringing the result of the computation from workers to the result aggregator
channel replies;

// total number of primes found
int prime_count = 0;

/*
 * is_prime returns true if n is a prime number
 */
int is_prime(int n)
{
    if (n <= 3)
    {
        return 1;
    }
    if ((n % 2) == 0)
    {
        return 0;
    }
    for (int i = 3; i < n; i+=2)
    {
        if ((n % i) == 0)
        {
            return 0;
        }
    }
    return 1;
}


void *pfworker_run(void *arg)
{
    /*
     * each worker thread pulls numbers out of "requests" channel and invokes is_prime to
     * determine if it's a prime, if so, it sends the number to "replies" channel.
     * if the channel has been closed (i.e. chan_recv returns null), the thread returns
     */

    int *n = NULL;
    while ((n = (int *)chan_recv(&requests)) != NULL)
    {
        if (is_prime(*n))
        {
            chan_send(&replies, &primeFlag);
        }
    }
    return NULL;
}

void *
result_agg_run(void *arg)
{
    // since we have a single aggregator thread, no need to lock prime count
    int *n = NULL;
    while ((n = (int *)chan_recv(&replies)) != NULL)
    {
        if (*n == 1)
        {
            prime_count ++;
        }
    }
    return NULL;
}

int
main(int argc, char **argv)
{
    // initialize the channels
    chan_init(&replies);
    chan_init(&requests);
    pthread_t threads[11];

    for (int i = 0; i < MAXNUM; i++)
    {
        numbers[i] = i;
    }

    // spawn 10 prime finder threads
    for (int i = 0; i < 10; i++)
    {
        pthread_create(threads+i, NULL, pfworker_run, NULL);
    }

    // spawn the result aggregator thread
    pthread_create(threads+10, NULL, result_agg_run, NULL);

    // send requests to workers
    for (int i = 2; i < MAXNUM; i++)
    {
        // send i to workers via the "request" channel
        chan_send(&requests, numbers + i);
    }

    chan_close(&requests);

    // join prime finder threads
    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }

    chan_close(&replies);

    // join the result aggregator thread
    pthread_join(threads[10], NULL);

    printf("%d\n", prime_count);

    chan_destroy(&requests);
    chan_destroy(&replies);
    return 0;
}
