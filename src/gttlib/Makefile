CC = gcc
CFLAGS = -Wall
PATH_DEST_LIB=../../lib
PATH_DEST_BIN=../../bin
TARGET_LIB=libgtt.so
TEST = gttTest
TEST2 = gttTest2

all : $(TARGET_LIB) $(TEST) $(TEST2)
	@echo "================ NVE ================"
	@echo "Copying library $(TARGET_LIB) to $(PATH_DEST_LIB)"
	cp $(TARGET_LIB) $(PATH_DEST_LIB)
	@echo "Copying binary $(TEST) to $(PATH_DEST_BIN)"
	@echo "Copying binary $(TEST2) to $(PATH_DEST_BIN)"
	cp $(TEST) $(PATH_DEST_BIN)
	cp $(TEST2) $(PATH_DEST_BIN)
	cp default.gtt $(PATH_DEST_BIN)
	@echo "================ DONE ==============="

$(PATH_DEST_LIB):
	make -p $(PATH_DEST_LIB)
$(PATH_DEST_BIN):
	make -p $(PATH_DEST_BIN)

$(TARGET_LIB): gtt_naive.o $(PATH_DEST_LIB)
	$(CC) -shared -Wl -o $@ gtt_naive.o

gtt_naive.o : gtt_naive.c
	$(CC) $(CFLAGS) -c -o $@ $< -fPIC

$(TEST):test.o $(TARGET_LIB) $(PATH_DEST_BIN)
	$(CC) $(CFLAGS) -o $@ test.o -lgtt -L.

$(TEST2):test2.o $(TARGET_LIB) $(PATH_DEST_BIN)
	$(CC) $(CFLAGS) -o $@ test2.o -lgtt -L.


clean :
	rm -rf *.o $(TARGET_LIB) $(TEST) $(TEST2)
	rm -f $(PATH_DEST_LIB)/$(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/$(TEST)
	rm -f $(PATH_DEST_BIN)/$(TEST2)
	rm $(PATH_DEST_BIN)/default.gtt

