all : libnve.so.1
	
libnve.so.1 : nve.o
	gcc -shared -Wl -o libnve.so.1 nve.o

nve.o : nve.c
	gcc -Wall -c -o nve.o nve.c -fPIC

clean :
	rm -rf *.o libnve
