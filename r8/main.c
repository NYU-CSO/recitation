#include <assert.h>
#include <stdio.h>

#include "list.h"

int n_inserts = 0;
int n_deletes = 0;

int
main(int argc, char **argv)
{
	int n = 100;

	for (int i = 0; i < n; i++) {
		insert(i);
	}
	printf("inserted %d values\n", n);

	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			delete(i);
		}
	}
	printf("deleted %d values\n", n/2);

	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			assert(find(i) == 0);
		}else{
			assert(find(i) != 0);
		}
	}
	printf("checked remaining %d values are correct\n", n/2);

	printf("I performed %d inserts %d deletes \n", n_inserts, n_deletes);
}
