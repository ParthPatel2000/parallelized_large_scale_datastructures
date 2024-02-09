#ifndef genome_functions
#define genome_functions
#include <fstream>

#define MAX_LINE_LENGTH 82

using namespace std;

class genomeProcessor
{
private:
    // Character array to store the genome sequence
    char *genomeString;

    // Size of the genome sequence string
    long long int genomeSize = 0;

public:
    /**
     * @brief Calculate the size of the genome.
     *
     * @param inputFilePointer Input file pointer to the genome file.
     * @return The size of the genome sequence.
     */
    long long int calculateGenomeSize(ifstream &inputFilePointer);

    /**
     * @brief Read the human genome file.
     *
     * Takes inputFilePath and reads the genome data, calculates the scaffolds count,
     * largest and shortest scaffolds with names and lengths,
     * average scaffold length, and then writes the output to outputFilePath.
     *
     * @param inputFilePath Input file path (string).
     * @param outputFilePath Output file path (string).
     *
     */
    // void readHumanGenome(string inputFilePath, string outputFilePath);
    void readHumanGenome(const char* inputFilePath, const char* outputFilePath);

    /**
     * @brief Compute characters in the genome.
     *
     * Takes inputFilePath and reads the genome data, counts the total number of characters in the genome,
     * runtime in terms of seconds, and the percent of content of GC.
     * Writes the output to outputFilePath.
     *
     * @param inputFilePath Input file path (string).
     * @param outputFilePath Output file path (string).
     *
     */
    void computeCharacters(const char* inputFilePath, const char* outputFilePath);

    ~genomeProcessor()
    {
        delete[] genomeString;
    }
};

#endif
