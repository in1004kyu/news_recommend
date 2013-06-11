CC = gcc
CFLAGS = -Wall

PATH_DEST_BIN=../../bin

COLLECTTEST=collect_test

all:$(COLLECTTEST) 
	cp $(COLLECTTEST) $(PATH_DEST_BIN)

$(COLLECTTEST): collectData.o 
	$(CC) $(CFLAGS) -o $@ collectData.o -lmysqlclient

clean :
	rm -f *.o
	rm -f $(COLLECTTEST)
	rm -f $(PATH_DEST_BIN)/$(COLLECTTEST)


