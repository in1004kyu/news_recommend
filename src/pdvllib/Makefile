CC = gcc
CFLAGS = -Wall

test : test.c pdvl_naive.o
	$(CC) $(CLAGS) -o test test.c pdvl_naive.o

pdvl_naive.o : pdvl_naive.c
	$(CC) $(CLAGS) -c pdvl_naive.c


clean :
	rm *.o
	rm test
