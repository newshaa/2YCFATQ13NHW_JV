CXX= g++
CXXFLAGS= -O3
LDFLAGS =
CUDACC = nvcc
CUFLAGS = -O3 -arch=sm_35

all: serial_bitCount 
#omp_bitCount cuda_bitCount

serial_bitCount: serial_bitCount.cpp bitCount_main.o
	$(CXX) $(CXXFLAGS) bitCount_main.o serial_bitCount.cpp -o serial_bitCount $(LDFLAGS)

omp_bitCount: omp_bitCount.cpp bitCount_main.o
	$(CXX) $(CXXFLAGS) -fopenmp bitCount_main.o omp_bitCount.cpp -o omp_bitCount $(LDFLAGS)

cuda_bitCount: bitCount_main.o cuda_bitCount.cu cuda_bitCount_kernels.cu
	$(CUDACC) $(CUFLAGS) bitCount_main.o cuda_bitCount.cu -o cuda_bitCount $(LDFLAGS)

bitCount_main.o: bitCount_main.cpp
	$(CXX) $(CXXFLAGS) bitCount_main.cpp -c -o bitCount_main.o

clean:
	rm -f serial_bitCount
	rm -f omp_bitCount
	rm -f cuda_bitCount
	rm -f bitCount_main.o
