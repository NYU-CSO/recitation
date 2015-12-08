#include "chan.h"

#define MAXNUM 1000000

int numbers[MAXNUM];

channel requests; //channel bringing work requests from main thread to workers
channel results; //channel bringing the result of the computation from workers to the result aggregator

int prime_count = 0; //total number of primes found

//is_prime returns true if n is a prime number
int
is_prime(int n) {
	if (n <= 3) {
		return 1;
	}
	if ((n % 2) == 0) {
		return 0;
	}
	for (int i = 3; i < n; i+=2) {
		if ((n % i) == 0) {
			return 0;
		}
	}
	return 1;
}


void *
pfworker_run(void *arg)
{
	//each worker thread pulls numbers out of "requests" channel and invokes is_prime to 
	//determine if it's a prime, if so, it sends the number to "replies" channel.
	//if the channel has been closed (i.e. chan_recv returns null), the thread returns
}

void *
result_agg_run(void *arg)
{
	//the aggregator thread pulls numbers out of "results" channel and increments 
	//the prime_count. It returns when the channel has been closed.
}

int
main(int argc, char **argv)
{
	//initialize the channels
	
	//spawn 10 worker threads

	//spawn the result aggregator thread

	//send requests to workers	
	for (int i = 2; i < MAXNUM; i++) {
		//send i to workers via the "request" channel
		chan_send(&requests, &numbers[i]);
	}

	//you need to properly close channels and join threads to obtain the correct final count
	
}
