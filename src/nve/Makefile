
PATH_DEST_LIB=../../lib
PATH_DEST_BIN=../../bin
TARGET_LIB=libnve.so
NVETEST=nveTest
CC=gcc
CFLAGS=-Wall -g

all : $(TARGET_LIB) $(NVETEST)
	@echo "================ NVE ================"
	@echo "Copying library $(TARGET_LIB) to $(PATH_DEST_LIB)"
	cp $(TARGET_LIB) $(PATH_DEST_LIB)
	@echo "Copying binary $(NVETEST) to $(PATH_DEST_BIN)"
	cp $(NVETEST) $(PATH_DEST_BIN)
	@echo "================ DONE ==============="

$(PATH_DEST_LIB):
	make -p $(PATH_DEST_LIB)

$(PATH_DEST_BIN):
	make -p $(PATH_DEST_BIN)

$(TARGET_LIB): nve.o $(PATH_DEST_LIB)
	$(CC) -shared -Wl -o $@  nve.o

nve.o : nve.c
	$(CC) $(CFLAGS) -c -o $@ $< -fPIC

$(NVETEST):nveTest.o $(TARGET_LIB) $(PATH_DEST_BIN)
	$(CC) $(CFLAGS) -o $@ nveTest.o -lnve -L.
clean :
	rm -rf *.o $(TARGET_LIB) $(NVETEST)
	rm -f $(PATH_DEST_LIB)/$(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/$(NVETEST)
