#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <assert.h>

#define MAXLINE 1000000
#define MAXWORDSZ 100

int 
readwords(char **words)
{
	int n_words = 0;
	while (1) {
		char *word = (char *)malloc(MAXWORDSZ);
	        if (!fgets(word, MAXWORDSZ, stdin)) {
			break;
		}
		if (word[strlen(word)-1] != '\n') {
			printf("Warning: word is longer than %d characters\n", MAXWORDSZ);
		}
		words[n_words] = word;
		n_words++;
		assert(n_words < MAXLINE);
	}
	return n_words;
}

int
mergewords(char **l1, int l1_len, char **l2, int l2_len, char *outfile)
{
	int l1_ind = 0;
	int l2_ind = 0;

	FILE *fp = fopen(outfile, "w");
	while (l1_ind < l1_len && l2_ind < l2_len) {
		if (strncmp(l1[l1_ind], l2[l2_ind], MAXWORDSZ) < 0) {
			fprintf(fp, "%s", l1[l1_ind]);
			l1_ind++;
		}else {
			fprintf(fp, "%s", l2[l2_ind]);
			l2_ind++;
		}

	}
	while (l1_ind < l1_len) {
		fprintf(fp, "%s", l1[l1_ind]);
	       	l1_ind++;
	}

	while (l2_ind < l2_len) {
		fprintf(fp, "%s", l2[l2_ind]);
	       	l2_ind++;
	}
	fclose(fp);
}

int
qsort_cmp(const void *a, const void *b)
{
	return strcmp((const char *)a, (const char *)b);
}

int 
main(int argc, char **argv)
{

	if (argc < 2) {
		printf("usage: ./multisort outputfile < inputfile\n");
		exit(1);
	}

	char **words = (char **)malloc(sizeof(char *)*MAXLINE);
	int n_words = readwords(words);

	int start = 0;
	int len = n_words;

	pid_t pid;
	if ((pid = fork()) != 0) {
		//parent sort the first half of the [start, start + len] section of words
		len = len/2;
		qsort(words + start, len, sizeof(char *), qsort_cmp);
		printf("pid-%d has sorted [%d, %d)\n", getpid(), start, start + len);
	} else {
		start = start + len/2;
		len = len - len/2;
		qsort(words + start, len, sizeof(char *), qsort_cmp);
		printf("pid-%d has sorted [%d, %d)\n", getpid(), start, start + len);
		exit(0);
	}

	//parent waits for child
	int status;
	waitpid(pid, &status, 0);

	printf("both sorting has finished\n");

	//merge the two sorted list into one
	mergewords(words, n_words/2, words+(n_words/2), n_words-(n_words/2), argv[1]);
	
	printf("merged two lists into one file %s\n", argv[1]);
}
