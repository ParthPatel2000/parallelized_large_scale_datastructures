CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O3
CPPFLAGS = -I.
LDLIBS = -lpthread

# Files
genome_file_path = /common/contrib/classroom/inf503/genomes/human.txt 

query_file_path = /common/contrib/classroom/inf503/human_reads_2_trimmed.fa

ARGS = $(genome_file_path) $(query_file_path)

all = main

# Build
build: $(all)

main: main.o genome_functions.o queries_ht.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o *.txt $(all)

# Test and run
hash:
	./main $(ARGS) 60000000 hash

search:
	./main $(ARGS) 60000000 search 

	