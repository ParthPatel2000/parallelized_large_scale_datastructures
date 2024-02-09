# Build the executable
executable: HW_2.o genome_functions.o queries.o
	g++ HW_2.o genome_functions.o queries.o -o executable

# Compile source files
HW_2.o: HW_2.cpp
	g++ -c HW_2.cpp -o HW_2.o

genome_functions.o: genome_functions.cpp
	g++ -c genome_functions.cpp -o genome_functions.o

queries.o: queries.cpp
	g++ -c queries.cpp -o queries.o

# Define a run target
run:
	./executable /common/contrib/classroom/inf503/genomes/human.txt /common/contrib/classroom/inf503/human_reads_2.fa sorted 10000
