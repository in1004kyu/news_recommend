CC = gcc
CFLAGS = -Wall

PATH_DEST_BIN=../../bin

EVALTEST=evald_test

all:$(EVALTEST) 
	cp $(EVALTEST) $(PATH_DEST_BIN)

$(EVALTEST): evald.o 
	$(CC) $(CFLAGS) -o $@ evald.o -lcosine -lnve -lpdvl -ld2v -L../../lib -lindex-TEST -liconv

clean :
	rm -f *.o
	rm -f $(EVALTEST)
	rm -f $(PATH_DEST_BIN)/$(EVALTEST)


