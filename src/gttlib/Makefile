CC = gcc
CFLAGS = -Wall

all : test test2

test : test.c gtt_naive.o
	$(CC) $(CLAGS) -o test test.c gtt_naive.o

test2 : test2.c gtt_naive.o
	$(CC) $(CLAGS) -o test2 test2.c gtt_naive.o

gtt_naive.o : gtt_naive.c
	$(CC) $(CLAGS) -c gtt_naive.c


clean :
	rm *.o
	rm test
	rm test2
