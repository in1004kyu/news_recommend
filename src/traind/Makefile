CC = gcc
CFLAGS = -Wall

PATH_DEST_BIN=../../bin

D2VTEST=train_test

all:$(D2VTEST) 
	cp $(D2VTEST) $(PATH_DEST_BIN)

$(D2VTEST): trainingDemon.o  $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $@ trainingDemon.o -lcosine -ld2v -lpdvl -L../../lib -lindex-TEST -liconv

clean :
	rm -f *.o
	rm -f $(D2VTEST)
	rm -f $(PATH_DEST_BIN)/$(D2VTEST)


