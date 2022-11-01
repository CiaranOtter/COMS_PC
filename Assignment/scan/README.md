This program will compile three programs into one compiled main out file

this will be run automatically if run.sh is called

it will set the length of the set to 2^x
(where x is equal to 3 to 24 by and increase of 1)

time each of the three functions
    1. Sequential scan
    2. openMP scan
    3. MPI scan

validating each one after it returns its value
it will then log the resutls of the tests to console and save the times to a test file

the time results can be displayed in a graph by running:
python3 plot.py

