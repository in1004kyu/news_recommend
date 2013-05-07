CC = gcc
CFLAGS = -Wall

test : test.c d2v_naive.o gtt_naive.o
	$(CC) $(CLAGS) -o test test.c d2v_naive.o gtt_naive.o


d2v_naive.o : d2v_naive.c
	$(CC) $(CLAGS) -c d2v_naive.c

gtt_naive.o : ../gttlib/gtt_naive.c
	$(CC) $(CLAGS) -c ../gttlib/gtt_naive.c 

clean :
	rm *.o
	rm test
