#include <pthread.h>

typedef struct
{
    pthread_mutex_t m;
    pthread_cond_t not_empty;
    pthread_cond_t empty;
    void *val;
    int closed;
} channel;

void chan_init(channel *chan);
int chan_send(channel *chan, void *val);
void *chan_recv(channel *chan);
void chan_close(channel *chan);
void chan_destroy(channel *chan);
