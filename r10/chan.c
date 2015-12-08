#include <pthread.h>
#include "chan.h"

void
chan_init(channel *chan) {
	chan->val = NULL;
	chan->closed = 0; //channel starts out as opened
	pthread_mutex_init(&chan->m, NULL);
	pthread_cond_init(&chan->empty, NULL);
	pthread_cond_init(&chan->not_empty, NULL);
}

//return 0 if successfully sends val to channel
//return 1 if channel has been closed
int
chan_send(channel *chan, void *val) {
	pthread_mutex_lock(&chan->m);
	while (chan->val != NULL) 
		pthread_cond_wait(&chan->empty, &chan->m);
	chan->val = val;
	pthread_cond_signal(&chan->not_empty);
	pthread_mutex_unlock(&chan->m);
	return 0;
}

//returns channel value if successful
//return NULL if channel has been closed
void *
chan_recv(channel *chan) {
	void *v;
	pthread_mutex_lock(&chan->m);
	while (chan->val == NULL) 
		pthread_cond_wait(&chan->not_empty, &chan->m);
	v = chan->val;
	chan->val = NULL;
	pthread_cond_signal(&chan->empty);
	pthread_mutex_unlock(&chan->m);
	return v;
}	

//close the channel
void
chan_close(channel *chan) {
}
