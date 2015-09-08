foo : foo.o main.o
	gcc foo.o main.o -o foo

foo.o : foo.c
	gcc -g -c foo.c

main.o : main.c
	gcc -g -c main.c
clean :
	rm foo.o main.o foo
