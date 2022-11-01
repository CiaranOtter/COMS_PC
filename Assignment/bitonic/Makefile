all: main

clean:
	rm -rf ./main

main: bitonic.cpp bitonic_mp.cpp bitonic_mpi.cpp
	mpic++ main.cpp bitonic.cpp bitonic_omp.cpp bitonic_mpi.cpp  -pedantic -Wall -Werror -fopenmp -lpthread -o main
