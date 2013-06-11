PATH_DEST_LIB=../../lib
PATH_DEST_BIN=../../bin
TARGET_LIB=libcosine.so
COSINETEST=cosineTest
CC=gcc 
CFLAGS=-Wall -g

all : $(TARGET_LIB) $(COSINETEST)
	@echo "================ COSINE ================"
	@echo "Copying library $(TARGET_LIB) to $(PATH_DEST_LIB)"
	cp $(TARGET_LIB) $(PATH_DEST_LIB)
	@echo "Copying binary $(COSINETEST) to $(PATH_DEST_BIN)"
	cp $(COSINETEST) $(PATH_DEST_BIN)
	@echo "================ DONE ==============="


$(TARGET_LIB): cosine.o $(PATH_DEST_LIB)
	$(CC) -shared -Wl -o $@  cosine.o -lm

cosine.o : cosine.c
	$(CC) $(CFLAGS) -c -o $@ $< -fPIC 

$(COSINETEST):cosineTest.o $(TARGET_LIB) $(PATH_DEST_BIN)
	$(CC) $(CFLAGS) -o $@ cosineTest.o -lcosine -L. -lm

clean :
	rm -rf *.o $(TARGET_LIB) $(COSINETEST)
	rm -f $(PATH_DEST_LIB)/$(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/$(COSINETEST)
