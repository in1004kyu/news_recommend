CURDIR  = ./
SRCDIR  = ./index/src/
OBJDIR  = ../obj/

SUFFIXES = .o .c .h
.SUFFIXES: $(SUFFIXES)

PROJ = index

CFILES = $(SRCDIR)indexT.c
OBJS = $(OBJDIR)indexT.o

CC= gcc
CFLAGS= -O3

all: index

tag: $(HDRS) $(CFILES)
	ctags $(HDRS) $(CFILES)
index: $(OBJS) ../libindex-TEST.a
	$(CC) -o ../EXE/indexT2 $(OBJS) -L.. ../libindex-TEST.a

$(OBJDIR)indexT.o: $(SRCDIR)indexT.c
	$(CC) $(CFLAGS) -c $(SRCDIR)indexT.c -o $(OBJDIR)indexT.o
