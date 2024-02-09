#ifndef GENOMEFUNCTIONS_H
#define GENOMEFUNCTIONS_H

#include <fstream>

#define MAX_LINE_LENGTH 82

using namespace std;

class genomeProcessor
{
private:
    char* genome_data;      // Character array to store genome data
    long long int genome_size = 0; // Variable to keep track of genome data array size

public:
    /**
     * Set the genome size to a specified value.
     *
     * @param size The size of the genome to be assigned to the private variable "genome_size."
     */
    void setSize(long long int size);

    /**
     * Get the size of the genome.
     *
     * @return The size of the genome stored in the private variable "genome_size."
     */
    long long int getSize();

    /**
     * Get a reference to the character array containing genome data.
     *
     * @return A reference to the character array holding the genome data.
     */
    char* getGenomeData();

    /**
     * Calculate the size of the genome characters by iterating through the entire file content,
     * skipping the genome headers.
     *
     * @param input_file_pointer Reference to the input file stream.
     * @return The size of the genome characters.
     */
    long long int countGenomeLength(ifstream &input_file_pointer);

    /**
     * Read the human genome file and perform the following tasks:
     * 1. Count the number of scaffolds.
     * 2. Determine the largest and shortest scaffold with names and lengths.
     * 3. Calculate the average scaffold length.
     *
     * @param input_file_pointer Reference to the input file stream.
     */
    void readGenomeData(ifstream &input_file_pointer);

    /**
     * Compute the number of A, G, C, T characters in the human genome and perform the following tasks:
     * 1. Count the total number of characters in the genome.
     * 2. Calculate the runtime in seconds.
     * 3. Determine the percent of GC content.
     *
     * @param input_file_pointer Reference to the input file stream.
     */
    void computeCharacters(ifstream &input_file_pointer);

    /**
     * Destructor for the genomeProcessor class.
     * Deallocates memory used for genome data.
     */
    ~genomeProcessor();
};

#endif
