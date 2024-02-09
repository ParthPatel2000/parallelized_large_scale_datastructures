
executable: main.o genome_functions.o
	g++ genome_functions.o main.o -o executable

main.o: main.cpp
	g++ -c main.cpp -o main.o

genome_functions.o: genome_functions.cpp
	g++ -c genome_functions.cpp -o genome_functions.o

clean:	
	rm *.o executable 
