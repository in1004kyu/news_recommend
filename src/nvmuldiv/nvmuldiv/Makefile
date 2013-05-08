CC = nvcc
#CFLAGS = -Wall
# nvcc -o test test.c nvmuldiv_cpu.c nvmuldiv_cuda_thrust.cu
#
#CFLAGS= -g -D__NVMULDIV_ENABLE_VERIFY__
CFLAGS= -g

OBJS=test.o nvmuldiv_cpu.o nvmuldiv_cuda_thrust.o nvmuldiv_cuda.o vdiv.o reduce_mul.o

all: test

test: $(OBJS)
	nvcc -o $@ $(OBJS)

test.o: test.c
	$(CC) $(CFLAGS) --compile -o $@ $<

nvmuldiv_cpu.o: nvmuldiv_cpu.c
	$(CC) $(CFLAGS) --compile -o $@ $<

nvmuldiv_cuda_thrust.o : nvmuldiv_cuda_thrust.cu
	$(CC) $(CFLAGS) --compile -o $@ $<

nvmuldiv_cuda.o : nvmuldiv_cuda.cu
	$(CC) $(CFLAGS) --compile -o $@ $<

reduce_mul.o : reduce_mul.cu
	$(CC) $(CFLAGS) --compile -o $@ $<

vdiv.o : vdiv.cu
	$(CC) $(CFLAGS) --compile -o $@ $<

clean:
	rm -f *.o
	rm -f test
