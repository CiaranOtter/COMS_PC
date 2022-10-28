all: serial openMP

serial: scan.cpp
	g++ scan.cpp -pedantic -Wall -Werror -o scan 

openMP: scan_omp.cpp
	g++ scan_omp.cpp -pedantic -Wall -Werror -o scan_omp

clean:
	rm -rf scan

