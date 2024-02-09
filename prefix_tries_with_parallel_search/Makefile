CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O3 -fopenmp
CPPFLAGS = -I.
LDLIBS = -lpthread

# Files
genome_file_path = /scratch/pp594/data/human.txt 

query_file_path = /scratch/pp594/data/human_reads_2_trimmed.fa

ARGS = $(genome_file_path) $(query_file_path) 

all = main

# Build
build: $(all)

main: main.o genome_functions.o queries_reader.o prefix_tries.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o *.txt $(all)

# Test and run
runa:
	./main --genome $(genome_file_path) --fragments 5000 --search basic --mismatch 1
	./main --genome $(genome_file_path) --fragments 50000 --search basic --mismatch 1
	./main --genome $(genome_file_path) --fragments 100000 --search basic --mismatch 1
	./main --genome $(genome_file_path) --fragments 1000000 --search basic --mismatch 1

runb:
	./main --genome $(genome_file_path) --fragments 5000 --search mutate --mismatch 1
	./main --genome $(genome_file_path) --fragments 50000 --search mutate --mismatch 1
	./main --genome $(genome_file_path) --fragments 100000 --search mutate --mismatch 1
	./main --genome $(genome_file_path) --fragments 1000000 --search mutate --mismatch 1
	