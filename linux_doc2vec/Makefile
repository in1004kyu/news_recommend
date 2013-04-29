.SUFFIXES : .c .o

CC = gcc

INC = ./header
LIBS = index-TEST
CFLAGS = -g

OBJS = gtt_naive.o
SRCS = gtt_naive.c main.c

TARGET = New_Recommand

all = $(TARGET)

$(TARGET) : $(OBJS)
	      $(CC) -o $@ $(OBJS) $(LIBS)

clean :
	rm -rf $(OBJS) $(TARGET)
