all: main

clean:
	rm -rf ./main

main: bitonic.cpp bitonic_omp.cpp bitonic_mpi.cpp
	mpic++ main.cpp bitonic.cpp bitonic_omp.cpp bitonic_mpi.cpp -Wall -Werror -fopenmp -lpthread -o main


sequential: main.cpp bitonic.cpp
	g++ main.cpp bitonic.cpp -Wall -Werror -o main

openMP: main.cpp bitonic.cpp bitonic_omp.cpp
	g++ main.cpp bitonic.cpp bitonic_omp.cpp -Wall -Werror -fopenmp -lpthread -o main

