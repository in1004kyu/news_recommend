CC = gcc
CFLAGS = -Wall -g
PATH_DEST_LIB=../../lib
PATH_DEST_BIN=../../bin
TARGET_LIB=libpdvl.so
TEST = pdvlTest

all : $(TARGET_LIB) $(TEST)
	@echo "================ PDVL ================"
	@echo "Copying library $(TARGET_LIB) to $(PATH_DEST_LIB)"
	cp $(TARGET_LIB) $(PATH_DEST_LIB)
	@echo "Copying binary $(TEST) to $(PATH_DEST_BIN)"
	cp $(TEST) $(PATH_DEST_BIN)
	cp default.pdvl $(PATH_DEST_BIN)
	@echo "================ DONE ==============="

$(PATH_DEST_LIB):
	make -p $(PATH_DEST_LIB)
$(PATH_DEST_BIN):
	make -p $(PATH_DEST_BIN)


$(TARGET_LIB): pdvl_naive.o $(PATH_DEST_LIB)
	$(CC) -shared -Wl -o $@ pdvl_naive.o

pdvl_naive.o : pdvl_naive.c
	$(CC) $(CFLAGS) -c -o $@ $< -fPIC

$(TEST):test.o $(TARGET_LIB) $(PATH_DEST_BIN)
	$(CC) $(CFLAGS) -o $@ test.o -lpdvl -L.

#test : test.c pdvl_naive.o
#	$(CC) $(CLAGS) -o test test.c pdvl_naive.o

#pdvl_naive.o : pdvl_naive.c
#	$(CC) $(CLAGS) -c pdvl_naive.c

clean :
	rm -rf *.o $(TARGET_LIB) $(TEST)
	rm -f $(PATH_DEST_LIB)/$(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/$(TEST)
	rm -f $(PATH_DEST_BIN)/default.pdvl
#	rm *.o
#	rm test
