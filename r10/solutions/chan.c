#include "chan.h"

void chan_init(channel *chan)
{
    chan->val = NULL;
    // channel starts out as opened
    chan->closed = 0;
    pthread_mutex_init(&chan->m, NULL);
    pthread_cond_init(&chan->empty, NULL);
    pthread_cond_init(&chan->not_empty, NULL);
}

/*
 * return 0 if successfully sends val to channel
 * return 1 if channel has been closed
 */
int chan_send(channel *chan, void *val)
{
    pthread_mutex_lock(&chan->m);
    if(chan->closed == 1 && chan->val != NULL)
    {
        pthread_mutex_unlock(&chan->m);
        return 1;
    }

    while (chan->val != NULL)
    {
        if (chan->closed == 1)
        {
            pthread_mutex_unlock(&chan->m);
            return 1;
        }
        pthread_cond_wait(&chan->empty, &chan->m);
    }
    if (chan->closed == 1)
    {
        pthread_mutex_unlock(&chan->m);
        return 1;
    }

    chan->val = val;
    pthread_cond_signal(&chan->not_empty);
    pthread_mutex_unlock(&chan->m);
    return 0;
}

/*
 * return channel value if successful
 * return NULL if channel has been closed
 * caveat: if there's data in the channel, process it even if
 * channel is closed
 */
void *chan_recv(channel *chan)
{
    pthread_mutex_lock(&chan->m);
    if(chan->closed == 1 && chan->val == NULL)
    {
        pthread_mutex_unlock(&chan->m);
        return NULL;
    }
    while (chan->val == NULL)
    {
        if (chan->closed == 1 && chan->val == NULL)
        {
            pthread_mutex_unlock(&chan->m);
            return NULL;
        }
        pthread_cond_wait(&chan->not_empty, &chan->m);
    }
    if (chan->closed == 1 && chan->val == NULL)
    {
        pthread_mutex_unlock(&chan->m);
        return NULL;
    }

    void *v = chan->val;
    chan->val = NULL;
    pthread_cond_signal(&chan->empty);
    pthread_mutex_unlock(&chan->m);
    return v;
}

/*
 * close the channel
 */
void chan_close(channel *chan)
{
    pthread_mutex_lock(&chan->m);
    // wake up all the threads that use this channel
    // and have them clean up
    pthread_cond_broadcast(&chan->empty);
    pthread_cond_broadcast(&chan->not_empty);
    chan->closed = 1;
    pthread_mutex_unlock(&chan->m);
}

/*
 * destroy associated data with channel
 * mutexes, condition variables
 */
void chan_destroy(channel *chan)
{
    pthread_cond_destroy(&chan->empty);
    pthread_cond_destroy(&chan->not_empty);
    pthread_mutex_destroy(&chan->m);
}
