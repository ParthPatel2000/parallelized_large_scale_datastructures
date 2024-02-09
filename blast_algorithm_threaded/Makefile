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

main: main.o genome_functions.o queries_reader.o queries_nw.o queries_bl.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

# queries_bl.o: queries_bl.cpp queries_bl.h queries_nw.h
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o *.txt $(all)

# Test and run
runa:
	./main $(genome_file_path) $(query_file_path) NW normal 100

runb:
	./main $(genome_file_path) $(query_file_path) BLAST normal 10000
	