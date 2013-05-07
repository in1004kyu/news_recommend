CC = gcc
CFLAGS = -Wall

test : test.c d2v_naive.o gtt_naive.o
	gcc -o test test.c d2v_naive.o gtt_naive.o

d2v_naive.o : d2v_naive.c
	gcc -c d2v_naive.c

gtt_naive.o : ../gttlib/gtt_naive.c
	gcc -c ../gttlib/gtt_naive.c 

clean :
	rm *.o
	rm test
