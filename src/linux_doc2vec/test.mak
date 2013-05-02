CURDIR  = ./
SRCDIR  = ./index/src/
OBJDIR  = ../obj/

SUFFIXES = .o .c .h
.SUFFIXES: $(SUFFIXES)

PROJ = ham

CFILES = $(SRCDIR)indexS.c $(SRCDIR)readsent.c
OBJS = $(OBJDIR)indexS.o $(OBJDIR)readsent.o

CC= gcc
CFLAGS= -O3 -Wall

all: ham

tag: $(HDRS) $(CFILES)
	ctags $(HDRS) $(CFILES)
ham: $(OBJS) ../libindex-TEST.a
	$(CC) -o ../EXE/index2 $(OBJS) -L.. ../libindex-TEST.a

$(OBJDIR)indexS.o: $(SRCDIR)indexS.c
	$(CC) $(CFLAGS) -c $(SRCDIR)indexS.c -o $(OBJDIR)indexS.o
$(OBJDIR)readsent.o: $(SRCDIR)readsent.c
	$(CC) $(CFLAGS) -c $(SRCDIR)readsent.c -o $(OBJDIR)readsent.o
