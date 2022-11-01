all: main

main: scan.cpp scan_omp.cpp scan_mpi.cpp main.cpp
	mpic++ main.cpp scan.cpp scan_omp.cpp scan_mpi.cpp  -pedantic -Wall -Werror -fopenmp -lpthread -o main

clean:
	rm -rf main

