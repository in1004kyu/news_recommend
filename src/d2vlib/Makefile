CC = gcc
CFLAGS = -Wall

PATH_DEST_BIN=../../bin
PATH_DEST_LIB=../../lib
PATH_TEST=./test

D2VTEST=d2v_test
TARGET_LIB=libd2v.so

LIB_OBJS=d2v_naive.o gtt_naive.o

all:$(D2VTEST) $(TARGET_LIB)
	cp $(D2VTEST) $(PATH_DEST_BIN)
	mv $(D2VTEST) $(PATH_TEST)
	cp $(TARGET_LIB) $(PATH_DEST_LIB)
	cp test.txt $(PATH_DEST_BIN)

$(D2VTEST): test.o d2v_naive.o gtt_naive.o $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $@ test.o d2v_naive.o gtt_naive.o -ld2v -L. -lindex-TEST

$(TARGET_LIB): $(LIB_OBJS) $(PATH_DEST_LIB)
	$(CC) -shared -Wl -o $@ $(LIB_OBJS)

d2v_naive.o : d2v_naive.c
	$(CC) $(CFLAGS) -c d2v_naive.c -fPIC -o $@

#gtt_naive.o :  ../gttlib/gtt_naive.c
#	$(CC) $(CFLAGS) -c ../gttlib/gtt_naive.c 
gtt_naive.o : ../gttlib/gtt_naive.c
	$(CC) $(CFLAGS) -c ../gttlib/gtt_naive.c -fPIC -o $@ 

clean :
	rm -f *.o
	rm -f $(D2VTEST)
	rm -f $(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/$(D2VTEST)
	rm -f $(PATH_DEST_LIB)/$(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/test.txt
	rm -f $(PATH_TEST)/$(D2VTEST)


#gcc -Wall -c d2v_naive.c
#  gcc -Wall -o test test.c d2v_naive.o gtt_naive.o

