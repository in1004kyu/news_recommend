CC = nvcc
LINKER = gcc
#CFLAGS = -Wall
# nvcc -o test test.c nvmuldiv_cpu.c nvmuldiv_cuda_thrust.cu
#
#CFLAGS= -g -D__NVMULDIV_ENABLE_VERIFY__
CFLAGS= -g
NVCCFLAGS=-m64 --shared --compiler-options '-fPIC' -g
NVCC=nvcc

# Try MAC OS X
CUDA_LIB_PATH= $(wildcard /usr/local/cuda/lib64)
ifeq ($(CUDA_LIB_PATH), )
CUDA_LIB_PATH= $(wildcard /usr/local/cuda/lib)
endif
ifeq ($(CUDA_LIB_PATH), )
CUDA_LIB_PATH= $(wildcard /usr/local/cuda-5.0/lib)
endif
ifeq ($(CUDA_LIB_PATH), )
CUDA_LIB_PATH=/cannot/find/cuda/lib
endif

OBJS=test.o 

TARGET_LIB=libnvmuldiv.so
LIB_OBJS=nvmuldiv_cpu.o nvmuldiv_cuda_thrust.o nvmuldiv_cuda.o vdiv.o reduce_mul.o
TARGET_BIN=test_nvmuldiv
PUBLIC_HEADERS=nvmuldiv.h

PATH_DEST_LIB=../../lib
PATH_DEST_BIN=../../bin
PATH_DEST_INC=../../include/nvmuldiv

all: $(TARGET_LIB) $(TARGET_BIN) $(PATH_DEST_INC) $(PUBLIC_HEADERS)
	cp $(TARGET_LIB) $(PATH_DEST_LIB)
	cp $(TARGET_BIN) $(PATH_DEST_BIN)
	cp $(PUBLIC_HEADERS) $(PATH_DEST_INC)

$(PATH_DEST_INC):
	mkdir -p $(PATH_DEST_INC)

$(TARGET_BIN): $(OBJS)
	$(LINKER) -o $@ $(OBJS) -lnvmuldiv -L. -lstdc++ -lcudart -L$(CUDA_LIB_PATH)


$(TARGET_LIB): $(LIB_OBJS)
	#$(LINKER) -m64 -shared -fPIC -o $@ $(LIB_OBJS) -lstdc++ -lcuda -lcudart -L$(CUDA_LIB_PATH)
	$(LINKER) -m64 -shared -fPIC -o $@ $(LIB_OBJS) 

test.o: test.c
	$(NVCC) $(NVCCFLAGS) --compile -o $@ $<

nvmuldiv_cpu.o: nvmuldiv_cpu.c
	$(NVCC) $(NVCCFLAGS) --compile -o $@ $<

nvmuldiv_cuda_thrust.o : nvmuldiv_cuda_thrust.cu
	$(NVCC) $(NVCCFLAGS) --compile -o $@ $<

nvmuldiv_cuda.o : nvmuldiv_cuda.cu
	$(NVCC) $(NVCCFLAGS) --compile -o $@ $<

reduce_mul.o : reduce_mul.cu
	$(NVCC) $(NVCCFLAGS) --compile -o $@ $<

vdiv.o : vdiv.cu
	$(NVCC) $(NVCCFLAGS) --compile -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET_BIN)
	rm -f $(TARGET_LIB)
	rm -f $(PATH_DEST_LIB)/$(TARGET_LIB)
	rm -f $(PATH_DEST_BIN)/$(TARGET_BIN)
	rm -f $(PATH_DEST_INC)/*
