all : nve

nve: nve.o nveTest.o
	gcc -o nve nve.o nveTest.o

nve.o: nve.c
	gcc -c -o nve.o nve.c

nveTest.o: nveTest.c
	gcc -c -o nveTest.o nveTest.c

clean :
	@rm -rf *.o
