Tutorial 10
=========

Exercise 1: Multi-threaded Prime Finder Using Concurrent Channels
-----

The `chan.c` file in this directory implements the channel object discussed the lecture.
The channel APIs are listed in `chan.h` file, which is shown here:

```C
typedef struct {
	pthread_mutex_t m;
	pthread_cond_t not_empty;
	pthread_cond_t empty;
	void *val;
	int closed;
}channel;

void chan_init(channel *chan);
int chan_send(channel *chan, void *val);
void *chan_recv(channel *chan);
void chan_close(channel *chan);
```

You'll notice that the API is slightly different from that shown in the lecture. Specifically, 
we have the additional `chan_close` function which is used to close a channel. Sending 
stuff via a closed channel results in an error (indiciated by `chan_send` returning a non-zero value).
Calling `chan_recv` on a closed channel results in immediate return with a NULL pointer.
Please add your code to `chan.c` to implement the closing of the channel as described.

Exercise 2: Multi-threaded Prime Finder Using Concurrent Channels
----
Next, we'll see how abstractions like the channel can simplify the coding of a
concurrent application.  Specifically, we'll implement a multi-threaded prime
number finder that finds all the prime numbers less than a million and prints
out the total number of primes found.

Here's one potential design.  We'll send work (in the forms of numbers between 1 to a million) from 
the main thread to `n` worker threads via a `requests` channel.  Each worker
thread pulls numbers out of the `requests` channel and checks whether that
number is a prime or not. If so, the worker sends it to the aggregator thread
via the `results` channel.  The aggregator thread pulls (prime) numbers out of
the `results` channel and increments a counter.  This design is reasonable:
determining whether a number is a prime or not is the expensive part of this application
and is done by `n` threads. By contrast, aggregating results (by summing the counts) is
cheap and can be done by one thread.

To implement this design, you should complete the skeleton code in `primefinder.c`. You are 
also welcome to explore other designs.

Note that you should add the `-pthread` when compiling your multi-threaded code, e.g.
```
gcc -std=gnu99 chan.c primefinder.c -pthread
```
